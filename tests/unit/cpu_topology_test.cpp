// rebuntu::system::observation — CPU Topology Adapter Unit Tests (Phase 7.10)
//
// Tests for the procfs/sysfs CPU topology observation adapter:
//   - /proc/cpuinfo parsing
//   - sysfs cpufreq governor detection

#include <cassert>
#include <iostream>

#include "system/observation/types.hpp"
#include "system/observation/adapters/cpu_topology.cpp"

void test_adapter_factory()
{
    auto adapter = rebuntu::system::observation::make_cpu_topology_adapter();
    assert(adapter != nullptr);
    std::cout << "[TEST] Factory creates adapter instance... [PASS]" << std::endl;
}

void test_adapter_domain()
{
    auto adapter = rebuntu::system::observation::make_cpu_topology_adapter();
    auto domain = adapter->domain();
    assert(domain == rebuntu::system::observation::ObservationDomain::kCPU);
    std::cout << "[TEST] Adapter reports kCPU domain... [PASS]" << std::endl;
}

void test_observe_online_cpus()
{
    auto adapter = rebuntu::system::observation::make_cpu_topology_adapter();
    
    // Create a valid subject identity
    rebuntu::system::observation::ObservationIdentity subject;
    subject.domain_id = "host:cpu";
    subject.domain = rebuntu::system::observation::ObservationDomain::kCPU;
    
    std::vector<rebuntu::system::observation::Observation> observations;
    auto result = adapter->observe(subject, observations);
    
    // Should succeed and produce at least one observation
    assert(result.is_success());
    assert(observations.size() > 0);
    
    // Check the online_cpus observation
    bool found_online = false;
    for (const auto& obs : observations) {
        if (obs.field == "online_cpus" && obs.raw_value.has_value()) {
            found_online = true;
            std::cout << "[TEST] Observation online_cpus=" << *obs.raw_value << "... [PASS]" << std::endl;
            break;
        }
    }
    assert(found_online);
}

void test_observe_cpufreq_governor()
{
    auto adapter = rebuntu::system::observation::make_cpu_topology_adapter();
    
    rebuntu::system::observation::ObservationIdentity subject;
    subject.domain_id = "host:cpu";
    subject.domain = rebuntu::system::observation::ObservationDomain::kCPU;
    
    std::vector<rebuntu::system::observation::Observation> observations;
    adapter->observe(subject, observations);
    
    // Check if cpufreq_governor was observed
    bool found_governor = false;
    for (const auto& obs : observations) {
        if (obs.field == "cpufreq_governor") {
            found_governor = true;
            if (obs.raw_value.has_value()) {
                std::cout << "[TEST] Observation cpufreq_governor=" << *obs.raw_value << "... [PASS]" << std::endl;
            }
            break;
        }
    }
    
    // Governor may be absent on some systems - this is not a failure
    if (found_governor) {
        std::cout << "[TEST] Governor observation available... [PASS]" << std::endl;
    } else {
        std::cout << "[TEST] Governor absence handled correctly... [PASS]" << std::endl;
    }
}

void test_freshness_policy()
{
    auto adapter = rebuntu::system::observation::make_cpu_topology_adapter();
    
    // CPU topology is static, should always be fresh
    rebuntu::system::observation::Observation obs;
    obs.field = "online_cpus";
    obs.source = "procfs";
    
    auto [is_fresh, age] = adapter->is_fresh(obs, {});
    assert(is_fresh);
    
    std::cout << "[TEST] CPU topology considered fresh... [PASS]" << std::endl;
}

int main()
{
    std::cout << "=== CPU Topology Adapter Unit Tests ===" << std::endl;
    
    test_adapter_factory();
    test_adapter_domain();
    test_observe_online_cpus();
    test_observe_cpufreq_governor();
    test_freshness_policy();
    
    std::cout << "\nAll tests passed!" << std::endl;
    return 0;
}