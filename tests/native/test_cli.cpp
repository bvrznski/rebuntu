// Integration tests for the `rebuntu` CLI dispatch (Phase 0.0).
#include "cli.hpp"

#include <cstddef>
#include <iostream>
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

int run_cli(std::vector<std::string> args) {
    std::vector<const char*> c;
    c.reserve(args.size());
    for (auto& a : args) c.push_back(a.c_str());
    return rebuntu::cli::run(std::span<const char* const>(c.data(), c.size()));
}
}  // namespace

int main() {
    // Known commands succeed (exit 0).
    CHECK(run_cli({"help"}) == 0);
    CHECK(run_cli({"version"}) == 0);
    CHECK(run_cli({"--version"}) == 0);
    CHECK(run_cli({"components"}) == 0);

    // A bare invocation prints help (exit 0).
    CHECK(run_cli({}) == 0);

    // Unknown command is a typed failure (exit 1), not a crash.
    CHECK(run_cli({"definitely-not-a-command"}) == 1);

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_cli: OK\n";
    return 0;
}
