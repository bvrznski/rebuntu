// Unit tests for rebuntu::core contracts (Phase 0.0).
// Minimal, dependency-free assertion harness.
#include <runtime/core/contracts.hpp>

#include <cstddef>
#include <iostream>
#include <string>

namespace {
int g_failures = 0;
#define CHECK(cond)                                                              \
    do {                                                                         \
        if (!(cond)) {                                                           \
            std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__      \
                      << ")\n";                                                  \
            ++g_failures;                                                        \
        }                                                                        \
    } while (0)
}  // namespace

int main() {
    using rebuntu::core::Component;
    using rebuntu::core::ComponentKind;
    using rebuntu::core::ComponentRegistry;
    using rebuntu::core::Outcome;
    using rebuntu::core::Result;
    using rebuntu::core::SemanticStatus;
    using rebuntu::core::to_string;

    // SemanticStatus mapping.
    CHECK(to_string(SemanticStatus::kSuccess) == "success");
    CHECK(to_string(SemanticStatus::kCompleted) == "completed");
    CHECK(to_string(SemanticStatus::kFailure) == "failure");
    CHECK(to_string(SemanticStatus::kUnknown) == "unknown");
    CHECK(to_string(SemanticStatus::kCancelled) == "cancelled");

    // Outcome: success is verified; completed is not.
    auto ok = Outcome::success();
    CHECK(ok.is_success());
    CHECK(ok.verified);
    CHECK(!ok.is_error());

    auto done = Outcome::completed();
    CHECK(done.is_completed());
    CHECK(!done.is_success());  // completed != verified success
    CHECK(!done.verified);

    // Failure carries a typed error, not a boolean.
    auto fail = Outcome::failure("E_UNSUPPORTED", "not implemented");
    CHECK(fail.is_error());
    CHECK(!fail.is_success());
    CHECK(fail.error.has_value());
    CHECK(fail.error->code == "E_UNSUPPORTED");
    CHECK(fail.error->message == "not implemented");

    // Unknown is an error-ish state but explicitly NOT a negative observation.
    auto unk = Outcome::unknown("could not determine outcome");
    CHECK(unk.status == SemanticStatus::kUnknown);
    CHECK(!unk.is_success());

    // Result<T> carries a value + verified success.
    auto r = Result<int>::success(42);
    CHECK(r.has_value());
    CHECK(*r.value == 42);
    CHECK(r.is_success());

    auto rok = Result<std::string>::ok("v");
    CHECK(rok.has_value());
    CHECK(!rok.verified);  // ok() == completed, not verified

    // ComponentRegistry: structural integrity.
    ComponentRegistry reg;
    reg.register_component(
        {"system.core", ComponentKind::kModule, "Core", "p", "", {}});
    reg.register_component(
        {"system.state", ComponentKind::kModule, "State", "p", "", {"system.core"}});
    CHECK(reg.size() == 2);
    CHECK(reg.contains("system.core"));
    CHECK(reg.find("system.state").has_value());
    CHECK(reg.find("system.state")->id == "system.state");
    CHECK(reg.validate().empty());  // valid: no dups, deps resolved

    // Duplicate ids are a structural defect.
    ComponentRegistry dup;
    dup.register_component({"x", ComponentKind::kModule, "X", "p", "", {}});
    dup.register_component({"x", ComponentKind::kModule, "X", "p", "", {}});
    CHECK(!dup.validate().empty());

    // Unknown dependencies are a structural defect.
    ComponentRegistry orph;
    orph.register_component({"y", ComponentKind::kModule, "Y", "p", "", {"missing"}});
    CHECK(!orph.validate().empty());

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_contracts: OK\n";
    return 0;
}
