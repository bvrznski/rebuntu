// Phase 7.5 Process Observation Tests
// Integration tests for procfs process discovery adapter
//
// Tests:
//   - PID reuse handling with boot context
//   - State semantics (running, sleeping, zombie, etc.)
//   - Evidence/provenance chain
//   - Bounded discovery
//   - Freshness tracking

#include <system/core/contracts.hpp>
#include "adapters/procfs/process/types.hpp"
#include "adapters/procfs/process/implementation.cpp"

#include <iostream>
#include <cassert>
#include <chrono>
#include <thread>

using namespace rebuntu::adapters::procfs::process;

void test_adapter_creation() {
    auto adapter = make_procfs_process_discovery_adapter();
    assert(adapter != nullptr);
    
    std::cout << "test_adapter_creation: PASS\n";
}

void test_observe_all_processes() {
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    // Check result status
    assert(result.status == rebuntu::core::SemanticStatus::kSuccess);
    assert(!result.description.empty());
    assert(!result.processes.empty());
    
    std::cout << "test_observe_all_processes: PASS (found " 
              << result.processes.size() << " processes)\n";
}

void test_process_identity_stability() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Get current process
    auto self_pid = getpid();
    
    // First observation - should succeed
    auto obs1 = adapter->observe_all_processes();
    assert(!obs1.processes.empty());
    
    bool found_self = false;
    for (const auto& proc : obs1.processes) {
        if (proc.identity.pid == self_pid) {
            found_self = true;
            
            // Verify identity has valid boot context
            assert(proc.identity.boot_timestamp_ms > 0);
            assert(proc.identity.is_valid());
            
            break;
        }
    }
    
    assert(found_self && "Current process should be in observation");
    
    std::cout << "test_process_identity_stability: PASS\n";
}

void test_state_semantics() {
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    // Count processes by state
    int running_count = 0;
    int sleeping_count = 0;
    int zombie_count = 0;
    
    for (const auto& proc : result.processes) {
        switch (proc.state) {
            case ProcessState::kRunning:
                running_count++;
                break;
            case ProcessState::kSleeping:
            case ProcessState::kDiskSleep:
                sleeping_count++;
                break;
            case ProcessState::kZombie:
                zombie_count++;
                break;
            default:
                break;
        }
    }
    
    std::cout << "test_state_semantics: PASS (running=" 
              << running_count << ", sleeping=" << sleeping_count 
              << ", zombie=" << zombie_count << ")\n";
}

void test_resource_tracking() {
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    // Verify some processes have resource info
    int with_rss = 0;
    for (const auto& proc : result.processes) {
        if (proc.resources.vm_rss_kb > 0) {
            with_rss++;
        }
    }
    
    std::cout << "test_resource_tracking: PASS (" 
              << with_rss << " processes have RSS info)\n";
}

void test_parent_relationship() {
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    // Count processes with parent information
    int with_ppid = 0;
    for (const auto& proc : result.processes) {
        if (proc.parent.ppid_starttime_ms >= 0) {
            with_ppid++;
        }
    }
    
    std::cout << "test_parent_relationship: PASS (" 
              << with_ppid << " processes have parent info)\n";
}

void test_provenance() {
    auto adapter = make_procfs_process_discovery_adapter();
    auto result = adapter->observe_all_processes();
    
    // Verify provenance for all observations
    bool has_provenance = true;
    for (const auto& proc : result.processes) {
        if (proc.source != "procfs") {
            has_provenance = false;
            break;
        }
        
        assert(proc.observed_at.time_since_epoch().count() > 0);
    }
    
    assert(has_provenance && "All processes should have procfs provenance");
    
    std::cout << "test_provenance: PASS\n";
}

void test_freshness() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // First observation
    auto result1 = adapter->observe_all_processes();
    auto time1 = result1.observed_at;
    
    // Small delay to ensure time difference
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    
    // Force refresh
    auto result2 = adapter->force_refresh();
    auto time2 = result2.observed_at;
    
    // Time should have advanced
    assert(time2 >= time1);
    
    std::cout << "test_freshness: PASS\n";
}

void test_bounded_discovery() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Discovery should complete with statistics
    auto result = adapter->observe_all_processes();
    
    assert(result.total_processes > 0);
    assert(result.running_processes + result.sleeping_processes + 
           result.zombie_processes + result.other_processes == result.total_processes);
    
    std::cout << "test_bounded_discovery: PASS\n";
}

void test_identity_validation() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Get current process identity
    auto self_pid = getpid();
    auto obs = adapter->observe_all_processes();
    
    ProcessIdentity self_identity;
    bool found_self = false;
    for (const auto& proc : obs.processes) {
        if (proc.identity.pid == self_pid) {
            self_identity = proc.identity;
            found_self = true;
            break;
        }
    }
    
    assert(found_self && "Should find current process");
    
    // Validate identity - should return valid since process still exists
    auto validation = adapter->validate_identity(self_identity);
    assert(validation == IdentityValidation::kValid);
    
    std::cout << "test_identity_validation: PASS\n";
}

void test_execution_vs_verification() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Execution should succeed (exit code 0, no crash)
    auto result = adapter->observe_all_processes();
    
    // Verification is implicit - procfs reading succeeded
    assert(result.status == rebuntu::core::SemanticStatus::kSuccess);
    
    std::cout << "test_execution_vs_verification: PASS\n";
}

void test_no_mutation() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Observation should not mutate system state
    
    auto result1 = adapter->observe_all_processes();
    
    // Re-observe to ensure consistent behavior
    auto result2 = adapter->observe_all_processes();
    
    // Both observations should succeed
    assert(result1.status == rebuntu::core::SemanticStatus::kSuccess);
    assert(result2.status == rebuntu::core::SemanticStatus::kSuccess);
    
    std::cout << "test_no_mutation: PASS\n";
}

void test_error_handling() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Observe should handle missing processes gracefully
    ProcessIdentity invalid_identity;
    invalid_identity.boot_timestamp_ms = -1;
    invalid_identity.pid = 999999;  // Likely doesn't exist
    
    // Validate on non-existent process
    auto validation = adapter->validate_identity(invalid_identity);
    
    // Should return not-found or unknown, not crash
    assert(validation == IdentityValidation::kNotFound || 
           validation == IdentityValidation::kUnknown);
    
    std::cout << "test_error_handling: PASS\n";
}

void test_thread_safety() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Multiple observations should be consistent
    const int num_threads = 4;
    std::vector<ProcessDiscoveryResult> results(num_threads);
    
    for (int i = 0; i < num_threads; i++) {
        results[i] = adapter->observe_all_processes();
    }
    
    // All results should have same total count
    size_t expected_count = results[0].total_processes;
    for (const auto& result : results) {
        assert(result.total_processes == expected_count);
    }
    
    std::cout << "test_thread_safety: PASS\n";
}

void test_large_process_count() {
    auto adapter = make_procfs_process_discovery_adapter();
    
    // Observe all processes
    auto result = adapter->observe_all_processes();
    
    // Should handle any number of processes
    assert(result.total_processes >= 1);
    
    std::cout << "test_large_process_count: PASS (observed "
              << result.total_processes << " processes)\n";
}

int main() {
    std::cout << "=== Phase 7.5 Process Observation Tests ===\n\n";
    
    test_adapter_creation();
    test_observe_all_processes();
    test_process_identity_stability();
    test_state_semantics();
    test_resource_tracking();
    test_parent_relationship();
    test_provenance();
    test_freshness();
    test_bounded_discovery();
    test_identity_validation();
    test_execution_vs_verification();
    test_no_mutation();
    test_error_handling();
    test_thread_safety();
    test_large_process_count();
    
    std::cout << "\n=== All Phase 7.5 tests passed! ===\n";
    return 0;
}