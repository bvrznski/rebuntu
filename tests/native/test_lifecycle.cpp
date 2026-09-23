// Unit tests for lifecycle operations contracts (Phase 1.11).
#include "cli.hpp"

#include <runtime/lifecycle/contracts.hpp>

#include <cstddef>
#include <iostream>
#include <map>
#include <span>
#include <string>
#include <vector>

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

int run_rebuntu(std::vector<std::string> args) {
    std::vector<const char*> c;
    c.reserve(args.size());
    for (auto& a : args) c.push_back(a.c_str());
    return rebuntu::cli::run(std::span<const char* const>(c.data(), c.size()));
}

void test_reconfigure_contract() {
    // Test the contract directly
    rebuntu::lifecycle::LifecycleContext ctx;
    ctx.dry_run = true;

    std::map<std::string, std::string> config = {
        {"key1", "value1"},
        {"key2", "value2"}
    };

    auto result = rebuntu::lifecycle::reconfigure(ctx, config);
    
    CHECK(result.operation == rebuntu::lifecycle::LifecycleOperation::kReconfigure);
    CHECK(result.success == true);
}

void test_repair_contract() {
    // Test the contract directly
    rebuntu::lifecycle::LifecycleContext ctx;
    ctx.dry_run = true;

    auto result = rebuntu::lifecycle::repair(ctx, {});
    
    CHECK(result.operation == rebuntu::lifecycle::LifecycleOperation::kRepair);
}

void test_upgrade_contract() {
    // Test the contract directly
    rebuntu::lifecycle::LifecycleContext ctx;
    
    auto result = rebuntu::lifecycle::upgrade(ctx, "1.0.0");
    
    CHECK(result.operation == rebuntu::lifecycle::LifecycleOperation::kUpgrade);
    CHECK(result.success == true);
}

void test_uninstall_contract() {
    // Test the contract directly
    rebuntu::lifecycle::LifecycleContext ctx;
    ctx.dry_run = true;

    auto result = rebuntu::lifecycle::uninstall(ctx);
    
    CHECK(result.operation == rebuntu::lifecycle::LifecycleOperation::kUninstall);
}

void test_purge_contract() {
    // Test the contract directly
    rebuntu::lifecycle::LifecycleContext ctx;
    ctx.dry_run = true;

    auto result = rebuntu::lifecycle::purge(ctx);
    
    CHECK(result.operation == rebuntu::lifecycle::LifecycleOperation::kPurge);
}

void test_to_string_functions() {
    // Test to_string for all enum types
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::LifecycleOperation::kReconfigure) == "reconfigure");
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::LifecycleOperation::kRepair) == "repair");
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::LifecycleOperation::kUpgrade) == "upgrade");
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::LifecycleOperation::kUninstall) == "uninstall");
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::LifecycleOperation::kPurge) == "purge");

    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::LifecycleStatus::kCompleted) == "completed");
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::LifecycleStatus::kFailed) == "failed");
    
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::ArtifactOperation::Action::kCreated) == "created");
    CHECK(rebuntu::lifecycle::to_string(rebuntu::lifecycle::ArtifactOperation::Action::kDeleted) == "deleted");
}

}  // namespace

int main() {
    // Test direct contract API
    test_reconfigure_contract();
    test_repair_contract();
    test_upgrade_contract();
    test_uninstall_contract();
    test_purge_contract();
    
    // Test to_string functions
    test_to_string_functions();

    // Lifecycle operations exist as commands and help works
    CHECK(run_rebuntu({"reconfigure", "--help"}) == 0);
    CHECK(run_rebuntu({"repair", "--help"}) == 0);
    CHECK(run_rebuntu({"upgrade", "--help"}) == 0);
    CHECK(run_rebuntu({"uninstall", "--help"}) == 0);

    // Help works for lifecycle subcommands
    CHECK(run_rebuntu({"reconfigure", "config", "--help"}) == 0);
    CHECK(run_rebuntu({"repair", "paths", "--help"}) == 0);
    CHECK(run_rebuntu({"upgrade", "version", "--help"}) == 0);

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_lifecycle: OK\n";
    return 0;
}