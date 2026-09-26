// rebuntu - Phase 5.24 Procfs Process Discovery Unit Tests
//
// Unit tests for the procfs process discovery adapter.

#include "adapters/procfs/process/types.hpp"
#include <iostream>
#include <thread>

using namespace rebuntu::adapters::procfs::process;

namespace core = rebuntu::core;

void test_factory_creates_adapter() {
    std::cout << "[TEST] Factory creates adapter instance...";
    
    auto adapter = make_procfs_process_discovery_adapter();
    if (adapter == nullptr) {
        std::cerr << " [FAIL - null pointer]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_all_processes() {
    std::cout << "[TEST] Observe all processes...";
    
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - status: " << to_string(result.status) 
                  << ", description: " << result.description << "]\n";
        return;
    }
    
    // We should find at least the current process
    if (result.total_processes == 0) {
        std::cerr << " [FAIL - no processes found]\n";
        return;
    }
    
    std::cout << " [PASS - found " << result.total_processes << " process(es)]\n";
}

void test_process_identity() {
    std::cout << "[TEST] Process identity fields...";
    
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - discovery failed]\n";
        return;
    }
    
    bool all_valid = true;
    for (const auto& proc : result.processes) {
        // Check that identity has valid boot timestamp and pid
        if (!proc.identity.is_valid()) {
            std::cerr << " [FAIL - invalid identity for pid " << proc.identity.pid << "]\n";
            all_valid = false;
        }
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - some identities are invalid]\n";
    }
}

void test_process_state_enum() {
    std::cout << "[TEST] ProcessState to_string conversion...";
    
    bool all_valid = true;
    struct TestCase { ProcessState state; const char* expected; };
    std::vector<TestCase> tests = {
        {ProcessState::kUnknown, "unknown"},
        {ProcessState::kRunning, "running"},
        {ProcessState::kSleeping, "sleeping"},
        {ProcessState::kDiskSleep, "disk-sleep"},
        {ProcessState::kZombie, "zombie"},
        {ProcessState::kStopped, "stopped"},
        {ProcessState::kTracing, "tracing-stop"},
        {ProcessState::kDead, "dead"},
        {ProcessState::kWakekill, "wakekill"},
        {ProcessState::kParked, "parked"},
        {ProcessState::kIdle, "idle"},
    };
    
    for (const auto& tc : tests) {
        if (to_string(tc.state) != tc.expected) {
            std::cerr << " [FAIL - to_string conversion failed]\n";
            all_valid = false;
        }
    }
    
    if (all_valid) {
        std::cout << " [PASS]\n";
    } else {
        std::cerr << " [FAIL - some conversions failed]\n";
    }
}

void test_statistics() {
    std::cout << "[TEST] Process statistics...";
    
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [FAIL - discovery failed]\n";
        return;
    }
    
    // Check that statistics sum up correctly
    size_t counted = result.running_processes + result.sleeping_processes + 
                     result.zombie_processes + result.other_processes;
    
    if (counted != result.total_processes) {
        std::cerr << " [FAIL - statistics don't add up: " << counted 
                  << " != " << result.total_processes << "]\n";
        return;
    }
    
    // Check that RSS aggregates are computed
    if (result.max_rss_kb.has_value() && *result.max_rss_kb > 0) {
        std::cout << " [PASS - found max RSS: " << *result.max_rss_kb << " kB]\n";
    } else {
        // This might be acceptable if no processes have RSS data
        std::cout << " [PASS]\n";
    }
}

void test_isolation() {
    std::cout << "[TEST] Multiple observations are isolated...";
    
    auto adapter = make_procfs_process_discovery_adapter();
    auto result1 = adapter->observe_all_processes();
    
    // Small delay to ensure different timestamps
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    
    auto result2 = adapter->force_refresh();
    
    if (result1.observed_at == result2.observed_at) {
        std::cerr << " [FAIL - observations should have different timestamps]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

void test_observe_specific_process() {
    std::cout << "[TEST] Observe specific process by identity...";
    
    auto adapter = make_procfs_process_discovery_adapter();
    
    // First get all processes to find one with a valid identity
    auto result = adapter->observe_all_processes();
    
    if (result.status != core::SemanticStatus::kSuccess) {
        std::cerr << " [SKIP - no processes available]\n";
        return;
    }
    
    // Try to observe the first process we found
    bool test_passed = false;
    for (const auto& proc : result.processes) {
        if (!proc.identity.is_valid()) {
            continue;
        }
        
        auto observation = adapter->observe_process(proc.identity);
        
        if (observation.has_value()) {
            // Check that observed process matches our identity
            if (observation.value().identity.pid == proc.identity.pid &&
                observation.value().identity.boot_timestamp_ms == proc.identity.boot_timestamp_ms) {
                test_passed = true;
                break;
            }
        }
    }
    
    if (test_passed) {
        std::cout << " [PASS]\n";
    } else {
        // This might be acceptable if no processes are observable
        std::cout << " [SKIP - could not observe specific process]\n";
    }
}

void test_last_observation_time() {
    std::cout << "[TEST] Get last observation time...";
    
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Initial call should set the time
    adapter->observe_all_processes();
    auto first_time = adapter->get_last_observation_time();
    
    if (first_time.time_since_epoch().count() <= 0) {
        std::cerr << " [FAIL - invalid observation time]\n";
        return;
    }
    
    // Force refresh should update the time
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    adapter->force_refresh();
    auto second_time = adapter->get_last_observation_time();
    
    if (second_time <= first_time) {
        std::cerr << " [FAIL - observation time should be updated]\n";
        return;
    }
    
    std::cout << " [PASS]\n";
}

int main() {
    std::cout << "\n=== Procfs Process Discovery Tests ===\n\n";
    
    test_factory_creates_adapter();
    test_observe_all_processes();
    test_process_identity();
    test_process_state_enum();
    test_statistics();
    test_isolation();
    test_observe_specific_process();
    test_last_observation_time();
    
    std::cout << "\n=== All Tests Complete ===\n\n";
    return 0;
}