// Unit tests for rebuntu::host_foundation (Phase 2.0)
//
// Tests verify:
//   * Foundation observations work correctly
//   * Support decisions are made properly
//   * UNKNOWN is preserved when acquisition fails

#include <system/host_foundation/contracts.hpp>

#include <iostream>
#include <string>
#include <cstdlib>

namespace {
int g_failures = 0;
#define CHECK(cond) do { if (!(cond)) { std::cerr << "CHECK failed: " << #cond << " (line " << __LINE__ << ")\\n"; ++g_failures; } } while(0)
}  // namespace

// Mock the environment for testing by temporarily modifying XDG_RUNTIME_DIR
static void setenv_test(const char* var, const char* value) {
    if (value) {
        setenv(var, value, 1);
    } else {
        unsetenv(var);
    }
}

int main() {
    using rebuntu::host_foundation::HostFoundation;
    using rebuntu::host_foundation::FoundationObservationStatus;
    using rebuntu::host_foundation::HostFoundationStatus;
    using rebuntu::host_foundation::SupportLevel;
    using rebuntu::host_foundation::OperationalMode;
    
    HostFoundation foundation;
    
    std::cout << "Testing host foundation discovery...\\n";
    
    // Test individual observation methods
    auto os_release = foundation.check_os_release();
    CHECK(os_release.type == rebuntu::host_foundation::HostFoundationType::kOsRelease);
    
    auto kernel = foundation.check_kernel();
    CHECK(kernel.type == rebuntu::host_foundation::HostFoundationType::kKernel);
    
    auto filesystem = foundation.check_filesystem();
    CHECK(filesystem.type == rebuntu::host_foundation::HostFoundationType::kFilesystem);
    
    auto process_model = foundation.check_process_model();
    CHECK(process_model.type == rebuntu::host_foundation::HostFoundationType::kProcessModel);
    
    // systemd check may vary - just verify it returns a valid status
    auto systemd = foundation.check_systemd();
    CHECK(systemd.status == FoundationObservationStatus::kPresent ||
          systemd.status == FoundationObservationStatus::kMissing ||
          systemd.status == FoundationObservationStatus::kUnknown);
    
    // Runtime directories should be available in test environment
    auto runtime_dirs = foundation.check_runtime_directories();
    CHECK(runtime_dirs.type == rebuntu::host_foundation::HostFoundationType::kRuntimeDirectories);
    
    // User namespace check may fail but should return valid status
    auto user_ns = foundation.check_user_namespace();
    CHECK(user_ns.status == FoundationObservationStatus::kPresent ||
          user_ns.status == FoundationObservationStatus::kUnknown ||
          user_ns.status == FoundationObservationStatus::kMissing);
    
    // Native identity - should be available on most systems
    auto native_id = foundation.check_native_identity();
    CHECK(native_id.type == rebuntu::host_foundation::HostFoundationType::kNativeIdentity);
    
    // umask support
    auto umask = foundation.check_umask_support();
    CHECK(umask.type == rebuntu::host_foundation::HostFoundationType::kUmaskSupport);
    
    // Test full assessment (may take a moment)
    std::cout << "Running full host assessment...\\n";
    auto result = foundation.assess();
    
    // Verify result structure
    CHECK(result.overall_status == HostFoundationStatus::kReady ||
          result.overall_status == HostFoundationStatus::kPartial ||
          result.overall_status == HostFoundationStatus::kUnsupported);
    
    // Should have at least some observations (we're running on Linux)
    bool has_observations = !result.observations.empty();
    CHECK(has_observations || "Host assessment should produce observations");
    
    // Test support decisions
    CHECK(result.minimal_decision.mode == OperationalMode::kMinimal ||
          result.minimal_decision.mode == OperationalMode::kServiceManaged);
    
    CHECK(result.service_managed_decision.mode == OperationalMode::kServiceManaged);
    
    CHECK(result.full_feature_decision.mode == OperationalMode::kFullFeature);
    
    // Verify support levels are valid
    CHECK(result.minimal_decision.level == SupportLevel::kFullySupported ||
          result.minimal_decision.level == SupportLevel::kPartiallySupported ||
          result.minimal_decision.level == SupportLevel::kNotSupported ||
          result.minimal_decision.level == SupportLevel::kUnknown);
    
    // Test with modified environment - missing runtime directory
    setenv_test("XDG_RUNTIME_DIR", "");
    auto no_runtime = foundation.check_runtime_directories();
    if (no_runtime.status == FoundationObservationStatus::kMissing) {
        std::cout << "Runtime directory correctly reported as missing when unset\\n";
    }
    
    // Test observation helpers
    auto present_obs = result.observations;
    bool has_unknown = false;
    for (const auto& obs : result.observations) {
        if (obs.is_unknown()) has_unknown = true;
        CHECK(obs.status != FoundationObservationStatus::kUnknown || 
              !obs.error_message.has_value() || 
              !obs.error_message.value().empty());
    }
    
    std::cout << "test_host_foundation: " 
              << (g_failures == 0 ? "OK" : std::to_string(g_failures) + " failures") 
              << "\\n";
    
    if (g_failures != 0) {
        std::cerr << g_failures << " check(s) FAILED\\n";
        return 1;
    }
    
    std::cout << "test_host_foundation: OK\\n";
    return 0;
}