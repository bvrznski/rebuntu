// rebuntu::testing — Testing Infrastructure Contracts (Phase 3.12)
//
// This establishes Rebuntu's canonical testing infrastructure foundation:
//   * Safe temporary file/directory management for tests
//   * Provider execution harnesses with timeouts and output limits
//   * Adversarial test patterns for failure scenarios
//   * Integration markers for opt-in integration tests
//
// Key principles:
//   * PROVIDER != TEST FIXTURE != ADVERSARIAL SCENARIO
//   * Tests MUST NOT mutate live host filesystem by default
//   * Timeout and output limits prevent hung processes/resource exhaustion
//   * Evidence collection enables traceability without secrets

#pragma once

#include <system/core/contracts.hpp>
#include <system/environment/temp_files.hpp>
#include <chrono>
#include <filesystem>
#include <optional>
#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <thread>

namespace rebuntu::testing {

// ============================================================================
// TestCategory - Classification of test purpose and scope
// ============================================================================

enum class TestCategory {
    kUnit,           // Fast, isolated unit tests (no external dependencies)
    kIntegration,    // Tests requiring external infrastructure (Docker, Ansible)
    kAdversarial,    // Failure scenario testing (timeouts, missing deps, etc.)
    kPerformance,    // Speed/throughput measurements
    kSmoke,          // Quick smoke tests for critical paths
};

inline const char* to_string(TestCategory c) {
    switch (c) {
        case TestCategory::kUnit:       return "unit";
        case TestCategory::kIntegration:return "integration";
        case TestCategory::kAdversarial:return "adversarial";
        case TestCategory::kPerformance:return "performance";
        case TestCategory::kSmoke:      return "smoke";
    }
    return "unknown";
}

// ============================================================================
// TestClassification - Metadata about a test
// ============================================================================

struct TestClassification {
    std::string name;                // Human-readable test name
    std::vector<TestCategory> categories;
    bool requires_host_mutation = false;  // Does this need to touch real host?
    std::optional<std::chrono::milliseconds> expected_duration_ms;
    
    bool is_integration() const {
        return std::any_of(categories.begin(), categories.end(),
            [](TestCategory cat) { return cat == TestCategory::kIntegration; });
    }
    
    bool is_adversarial() const {
        return std::any_of(categories.begin(), categories.end(),
            [](TestCategory cat) { return cat == TestCategory::kAdversarial; });
    }
};

// ============================================================================
// TestEnvironmentConfig - Configuration for test execution
// ============================================================================

struct TestEnvironmentConfig {
    // Path configuration
    std::filesystem::path temp_root = std::filesystem::temp_directory_path() / "rebuntu-test";
    
    // Timeout defaults
    std::chrono::milliseconds default_timeout_ms = std::chrono::seconds(30);
    std::chrono::milliseconds fast_simulation_timeout_ms = std::chrono::milliseconds(10);  // ~0.01s
    
    // Resource limits
    size_t max_output_size = 65536;  // 64KB default, matches Python version
    
    // Control flags
    bool host_mutation_allowed = false;  // Must be explicitly enabled
    bool fast_simulation_mode = true;    // Skip actual sleeps for speed
    
    // Environment variable names (for discovery)
    inline static const char* kEnvTempRoot = "REBUNTU_TEST_TEMP_ROOT";
    inline static const char* kEnvHostMutation = "REBUNTU_ALLOW_HOST_MUTATION";
    inline static const char* kEnvFastSimulation = "REBUNTU_TEST_FAST_SIMULATION";
    
    // Load from environment (returns self for chaining)
    TestEnvironmentConfig& load_from_environment() {
        if (const char* root = std::getenv(kEnvTempRoot)) {
            temp_root = std::filesystem::path{root};
        }
        
        if (std::getenv(kEnvHostMutation)) {
            host_mutation_allowed = true;
        }
        
        // Fast simulation defaults to true for speed
        if (const char* val = std::getenv(kEnvFastSimulation)) {
            fast_simulation_mode = (std::string(val) != "0" && 
                                    std::string(val) != "false");
        }
        
        return *this;
    }
};

// ============================================================================
// ProviderExecutorResult - Result of provider execution
// ============================================================================

enum class ProviderExecutionOutcome {
    kSuccess,           // Command ran and completed with expected output
    kTimeout,           // Command exceeded timeout limit
    kOutputLimit,       // Output exceeded max_output_size
    kExecutionFailed,   // Process failed to start or crashed
    kCancelled,         // Execution was cancelled
};

inline const char* to_string(ProviderExecutionOutcome o) {
    switch (o) {
        case ProviderExecutionOutcome::kSuccess:      return "success";
        case ProviderExecutionOutcome::kTimeout:      return "timeout";
        case ProviderExecutionOutcome::kOutputLimit:  return "output_limit";
        case ProviderExecutionOutcome::kExecutionFailed:return "execution_failed";
        case ProviderExecutionOutcome::kCancelled:    return "cancelled";
    }
    return "unknown";
}

struct ProviderExecutorResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    ProviderExecutionOutcome outcome = ProviderExecutionOutcome::kSuccess;
    
    std::string stdout_data;     // Captured stdout (truncated to max_output_size)
    std::string stderr_data;     // Captured stderr
    int exit_code = -1;          // Process exit code (-1 if not applicable)
    
    std::chrono::milliseconds duration_ms{0};
    bool timed_out = false;
    bool output_truncated = false;
    
    // Evidence for verification (non-sensitive observations only)
    std::vector<core::Evidence> evidence;
    
    // Error information
    std::optional<std::string> error_message;
    
    bool is_success() const {
        return status == core::SemanticStatus::kSuccess && !timed_out && !output_truncated;
    }
};

// ============================================================================
// FakeProvider - Test provider for creating executable fixtures
// ============================================================================

class FakeProvider {
public:
    // Create a fake provider that exits with specified code
    static std::filesystem::path create_exit_provider(
        const std::filesystem::path& dir,
        int exit_code,
        const std::string& name = "fake-exit");
    
    // Create a fake provider that writes output to stdout
    static std::filesystem::path create_output_provider(
        const std::filesystem::path& dir,
        const std::string& output,
        int exit_code = 0,
        const std::string& name = "fake-output");
    
    // Create a fake provider that sleeps for specified duration
    static std::filesystem::path create_sleep_provider(
        const std::filesystem::path& dir,
        double seconds,
        const std::string& name = "fake-sleep");
};

// ============================================================================
// TestContext - RAII context for test execution
// ============================================================================

class TestContext {
public:
    explicit TestContext(TestEnvironmentConfig config);
    ~TestContext();
    
    // Move semantics only
    TestContext(TestContext&&) = default;
    TestContext& operator=(TestContext&&) = default;
    
    // Delete copy semantics
    TestContext(const TestContext&) = delete;
    TestContext& operator=(const TestContext&) = delete;
    
    // Accessors
    const std::filesystem::path& temp_root() const { return temp_dir_.path(); }
    const TestEnvironmentConfig& config() const { return config_; }
    
    // Create a temporary file in this context
    environment::temp_files::TempFileResult create_temp_file(
        const std::string& prefix = "test-",
        mode_t permissions = 0600);
    
    // Create a temporary directory in this context
    environment::temp_files::TempFileResult create_temp_dir(
        const std::string& prefix = "test-",
        mode_t permissions = 0700);
    
private:
    TestEnvironmentConfig config_;
    environment::temp_files::SecureTempDir temp_dir_;
};

// ============================================================================
// FakeProvider implementations
// ============================================================================

inline std::filesystem::path FakeProvider::create_exit_provider(
    const std::filesystem::path& dir,
    int exit_code,
    const std::string& name) {
    
    auto source_path = dir / (name + ".cpp");
    auto binary_path = dir / name;
    
    std::ofstream source(source_path);
    source << "#include <cstdlib>\n"
           << "int main() { return " << exit_code << "; }\n";
    source.close();
    
    // Compile the program
    std::string compile_cmd = 
        "g++ -o " + binary_path.string() + " " + source_path.string();
    int result = std::system(compile_cmd.c_str());
    
    if (result != 0) {
        throw std::runtime_error("Failed to create fake provider executable");
    }
    
    // Make it executable
    chmod(binary_path.c_str(), 0755);
    
    return binary_path;
}

inline std::filesystem::path FakeProvider::create_output_provider(
    const std::filesystem::path& dir,
    const std::string& output,
    int exit_code,
    const std::string& name) {
    
    auto source_path = dir / (name + ".cpp");
    auto binary_path = dir / name;
    
    // Escape the output string for C++
    std::string escaped_output;
    for (char c : output) {
        switch (c) {
            case '\n': escaped_output += "\\n"; break;
            case '"':  escaped_output += "\\\""; break;
            case '\\': escaped_output += "\\\\"; break;
            default:   escaped_output += c;
        }
    }
    
    std::ofstream source(source_path);
    source << "#include <iostream>\n"
           << "int main() { \n"
           << "  std::cout << \"" << escaped_output << "\";\n"
           << "  return " << exit_code << "; \n"
           << "}\n";
    source.close();
    
    // Compile the program
    std::string compile_cmd = 
        "g++ -o " + binary_path.string() + " " + source_path.string();
    int result = std::system(compile_cmd.c_str());
    
    if (result != 0) {
        throw std::runtime_error("Failed to create fake provider executable");
    }
    
    // Make it executable
    chmod(binary_path.c_str(), 0755);
    
    return binary_path;
}

inline std::filesystem::path FakeProvider::create_sleep_provider(
    const std::filesystem::path& dir,
    double seconds,
    const std::string& name) {
    
    auto source_path = dir / (name + ".cpp");
    auto binary_path = dir / name;
    
    std::ofstream source(source_path);
    source << "#include <thread>\n"
           << "#include <chrono>\n"
           << "int main() { \n"
           << "  std::this_thread::sleep_for(std::chrono::duration<double>(" 
           << seconds << "));\n"
           << "  return 0; \n"
           << "}\n";
    source.close();
    
    // Compile the program
    std::string compile_cmd = 
        "g++ -std=c++17 -o " + binary_path.string() + " " + source_path.string();
    int result = std::system(compile_cmd.c_str());
    
    if (result != 0) {
        throw std::runtime_error("Failed to create fake provider executable");
    }
    
    // Make it executable
    chmod(binary_path.c_str(), 0755);
    
    return binary_path;
}

// ============================================================================
// TestContext implementations
// ============================================================================

inline TestContext::TestContext(TestEnvironmentConfig config)
    : config_(std::move(config))
    , temp_dir_([this]() -> std::filesystem::path {
        static int counter = 0;
        auto dir = (config_.temp_root / "ctx-").string() + std::to_string(counter++);
        std::error_code ec;
        std::filesystem::create_directories(dir, ec);
        return dir;
    }()) {
}

inline TestContext::~TestContext() {
    // temp_dir_ destructor will clean up automatically
}

inline environment::temp_files::TempFileResult TestContext::create_temp_file(
    const std::string& prefix,
    mode_t permissions) {
    environment::temp_files::SecureTempDir temp_dir(temp_dir_.path());
    return temp_dir.create_file(prefix, permissions);
}

inline environment::temp_files::TempFileResult TestContext::create_temp_dir(
    const std::string& prefix,
    mode_t permissions) {
    return environment::temp_files::SecureTempDir(temp_dir_.path()).create_in_directory(
        temp_dir_.path(), prefix, permissions);
}

}  // namespace rebuntu::testing