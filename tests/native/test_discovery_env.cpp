/// Unit tests for rebuntu::environment::discovery (Phase 1.1 + Phase 1.9 extensions)

#include <observation/environment/discovery.hpp>

#include <iostream>
#include <string>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

int main() {
    using rebuntu::environment::discovery::HostDiscovery;

    HostDiscovery discovery;

    auto distro = discovery.discover_distribution();
    CHECK(distro.status == rebuntu::environment::discovery::DiscoveryStatus::kKnown ||
          distro.status == rebuntu::environment::discovery::DiscoveryStatus::kUnknown);

    auto arch = discovery.discover_architecture();
    CHECK(arch.status == rebuntu::environment::discovery::DiscoveryStatus::kKnown);

    auto result = discovery.discover();
    CHECK(!result.facts.empty());
    
    // Phase 1.9: Test new discovery methods
    auto memory = discovery.discover_memory();
    if (memory.status == rebuntu::environment::discovery::DiscoveryStatus::kKnown) {
        CHECK(memory.total_bytes.has_value() && memory.total_bytes.value() > 0);
    }
    
    auto storage = discovery.discover_storage();
    // Storage info should be available on most systems
    if (!storage.mounts.empty()) {
        CHECK(storage.status == rebuntu::environment::discovery::DiscoveryStatus::kKnown);
    }
    
    auto network = discovery.discover_network();
    CHECK(network.has_ipv4.has_value() || network.has_ipv6.has_value());
    
    auto session = discovery.discover_session();
    CHECK(session.display_server != rebuntu::environment::discovery::DisplayServer::kUnknown ||
          session.session_type.has_value());
    
    auto gpu = discovery.discover_gpu();
    // GPU detection may not find devices (headless systems are valid)
    CHECK(gpu.status == rebuntu::environment::discovery::DiscoveryStatus::kKnown);
    
    auto shell = discovery.discover_shell();
    CHECK(shell.primary_shell.has_value() && 
          shell.primary_shell.value() != rebuntu::environment::discovery::ShellType::kUnknown);
    
    // Verify preflight evaluation works with new data
    rebuntu::environment::discovery::PreflightEvaluator evaluator(result);
    auto preflight = evaluator.evaluate();
    CHECK(preflight.discovery.kernel.status == 
          rebuntu::environment::discovery::DiscoveryStatus::kKnown);

    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\\n";
        return 1;
    }
    std::cout << "test_discovery_env: OK\\n";
    return 0;
}
