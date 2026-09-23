// Unit tests for rebuntu::state provider (Phase 0.14).
#include <system/state/provider.hpp>

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
    using rebuntu::state::ProviderId;
    
    // ProviderId tests
    ProviderId pid1{"systemd"};
    CHECK(pid1.value == "systemd");
    CHECK(std::string(pid1) == "systemd");
    
    ProviderId pid2{"procfs"};
    CHECK(pid1 != pid2);
    
    ProviderId pid3{"systemd"};
    CHECK(pid1 == pid3);
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\n";
        return 1;
    }
    std::cout << "test_state_provider: OK\n";
    return 0;
}
