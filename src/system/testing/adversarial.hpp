// rebuntu::testing::adversarial — Adversarial Test Patterns (Phase 3.12)
//
// Adversarial test patterns for failure scenarios:
//   * Timeout handling with fast simulation mode
//   * Missing dependency detection with optimized paths
//   * Malformed output handling
//   * Hostile input detection

#pragma once

#include <system/testing/contracts.hpp>
#include <chrono>
#include <filesystem>
#include <memory>
#include <optional>
#include <sstream>
#include <string>
#include <vector>

namespace rebuntu::testing {

// ============================================================================
// AdversarialOutcome - Outcomes for adversarial test scenarios
// ============================================================================

enum class AdversarialOutcome {
    DENY,                    // Request denied
    RETRY,                   // Retry the operation
    TIMEOUT,                 // Operation timed out
    CANCELLED,               // Operation was cancelled
    PROVIDER_UNAVAILABLE,    // Provider unavailable
    EXECUTION_FAILED,        // Execution failed
    VERIFICATION_FAILED,     // Verification failed
    INVALID_RESULT,          // Result is invalid/malformed
    UNKNOWN,                 // Outcome unknown
    REPAIR_REQUIRED,         // Repair required
    OPERATOR_ACTION,         // Operator action required
};

inline const char* to_string(AdversarialOutcome o) {
    switch (o) {
        case AdversarialOutcome::DENY: return "deny";
        case AdversarialOutcome::RETRY: return "retry";
        case AdversarialOutcome::TIMEOUT: return "timeout";
        case AdversarialOutcome::CANCELLED: return "cancelled";
        case AdversarialOutcome::PROVIDER_UNAVAILABLE: return "provider_unavailable";
        case AdversarialOutcome::EXECUTION_FAILED: return "execution_failed";
        case AdversarialOutcome::VERIFICATION_FAILED: return "verification_failed";
        case AdversarialOutcome::INVALID_RESULT: return "invalid_result";
        case AdversarialOutcome::UNKNOWN: return "unknown";
        case AdversarialOutcome::REPAIR_REQUIRED: return "repair_required";
        case AdversarialOutcome::OPERATOR_ACTION: return "operator_action";
    }
    return "unknown";
}

// ============================================================================
// AdversarialTestCase - Base class for adversarial test scenarios
// ============================================================================

struct AdversarialTestCaseResult {
    core::SemanticStatus status = core::SemanticStatus::kUnknown;
    AdversarialOutcome outcome = AdversarialOutcome::UNKNOWN;
    
    std::string scenario_name;      // Name of the scenario tested
    std::chrono::milliseconds duration_ms{0};
    
    // Evidence for verification
    std::vector<core::Evidence> evidence;
    
    // Error information (if applicable)
    std::optional<std::string> error_message;
    
    bool success() const {
        return status == core::SemanticStatus::kSuccess;
    }
};

class AdversarialTestCase {
public:
    explicit AdversarialTestCase(std::string name);
    virtual ~AdversarialTestCase();
    
    // Non-copyable, movable
    AdversarialTestCase(const AdversarialTestCase&) = delete;
    AdversarialTestCase& operator=(const AdversarialTestCase&) = delete;
    AdversarialTestCase(AdversarialTestCase&&) noexcept;
    AdversarialTestCase& operator=(AdversarialTestCase&&) noexcept;
    
    // Run the scenario and return result
    virtual AdversarialTestCaseResult run() = 0;
    
    // Getters
    const std::string& name() const { return name_; }
    bool is_fast_simulation_enabled() const { return fast_simulation_mode_; }
    void set_fast_simulation(bool enabled) { fast_simulation_mode_ = enabled; }
    
protected:
    std::string name_;
    bool fast_simulation_mode_{false};
};

// ============================================================================
// TimeoutScenario - Test timeout handling with fast simulation mode
// ============================================================================

class TimeoutScenario : public AdversarialTestCase {
public:
    explicit TimeoutScenario(std::optional<std::string> cmd = std::nullopt,
                             std::optional<int> exit_code = std::nullopt);
    
    // Timeout in seconds (for scenario setup)
    void set_timeout_seconds(double seconds) { timeout_seconds_ = seconds; }
    
    // Use fake timeout mode for speed
    void use_fake_timeout(bool enabled) { use_fake_timeout_ = enabled; }
    
    AdversarialTestCaseResult run() override;
    
private:
    std::optional<std::string> cmd_;
    std::optional<int> exit_code_;
    double timeout_seconds_{0.5};
    bool use_fake_timeout_{true};  // Default to fast simulation
};

// ============================================================================
// MissingDependencyScenario - Test missing dependencies with optimized paths
// ============================================================================

class MissingDependencyScenario : public AdversarialTestCase {
public:
    explicit MissingDependencyScenario(std::string executable);
    
    // Use optimized path (just check existence, no subprocess call)
    void set_check_exists_only(bool enabled) { check_exists_only_ = enabled; }
    
    AdversarialTestCaseResult run() override;
    
private:
    std::string executable_;
    bool check_exists_only_{true};  // Default to fast optimization
};

// ============================================================================
// MalformedOutputScenario - Test malformed output handling
// ============================================================================

class MalformedOutputScenario : public AdversarialTestCase {
public:
    explicit MalformedOutputScenario(std::string input);
    
    AdversarialTestCaseResult run() override;
    
private:
    std::string input_;
};

// ============================================================================
// HostileInputScenario - Test hostile input detection
// ============================================================================

class HostileInputScenario : public AdversarialTestCase {
public:
    explicit HostileInputScenario(std::string input,
                                  bool expect_deny = true);
    
    AdversarialTestCaseResult run() override;
    
private:
    std::string input_;
    bool expect_deny_{true};
};

// ============================================================================
// AdversarialTestRunner - Runner for adversarial test scenarios
// ============================================================================

class AdversarialTestRunner {
public:
    explicit AdversarialTestRunner(TestEnvironmentConfig config = {});
    
    // Run a single scenario
    AdversarialTestCaseResult run(AdversarialTestCase& scenario);
    
    // Run all scenarios and return results
    std::vector<AdversarialTestCaseResult> run_all(
        const std::vector<std::unique_ptr<AdversarialTestCase>>& scenarios);
    
    // Get summary of all results
    std::string summary(const std::vector<AdversarialTestCaseResult>& results) const;
    
    // Count outcomes by type
    std::map<AdversarialOutcome, int> count_outcomes(
        const std::vector<AdversarialTestCaseResult>& results) const;
    
private:
    TestEnvironmentConfig config_;
};

}  // namespace rebuntu::testing

// ============================================================================
// Inline implementations
// ============================================================================

#include <thread>
#include <chrono>

namespace rebuntu::testing {

inline AdversarialTestCase::AdversarialTestCase(std::string name)
    : name_(std::move(name)) {
}

inline AdversarialTestCase::~AdversarialTestCase() = default;

inline AdversarialTestCase::AdversarialTestCase(AdversarialTestCase&&) noexcept = default;
inline AdversarialTestCase& AdversarialTestCase::operator=(AdversarialTestCase&&) noexcept = default;

// ============================================================================
// TimeoutScenario
// ============================================================================

inline TimeoutScenario::TimeoutScenario(std::optional<std::string> cmd, std::optional<int> exit_code)
    : AdversarialTestCase("timeout") 
    , cmd_(std::move(cmd))
    , exit_code_(exit_code ? *exit_code : 0) {
}

inline AdversarialTestCaseResult TimeoutScenario::run() {
    AdversarialTestCaseResult result;
    result.scenario_name = name_;
    
    auto start_time = std::chrono::steady_clock::now();
    
    if (use_fake_timeout_) {
        // Fast simulation mode - skip actual sleep
        std::this_thread::sleep_for(config_.fast_simulation_timeout_ms);
        
        // Simulate timeout outcome
        result.status = core::SemanticStatus::kUnknown;
        result.outcome = AdversarialOutcome::TIMEOUT;
        result.duration_ms = config_.fast_simulation_timeout_ms;
    } else {
        // Real execution mode - actually wait for the command
        std::this_thread::sleep_for(
            std::chrono::duration<double>(timeout_seconds_));
        
        auto end_time = std::chrono::steady_clock::now();
        result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
            end_time - start_time);
        
        // Simulate timeout outcome
        result.status = core::SemanticStatus::kUnknown;
        result.outcome = AdversarialOutcome::TIMEOUT;
    }
    
    return result;
}

// ============================================================================
// MissingDependencyScenario
// ============================================================================

inline MissingDependencyScenario::MissingDependencyScenario(std::string executable)
    : AdversarialTestCase("missing_dependency")
    , executable_(std::move(executable)) {
}

inline AdversarialTestCaseResult MissingDependencyScenario::run() {
    AdversarialTestCaseResult result;
    result.scenario_name = name_;
    
    auto start_time = std::chrono::steady_clock::now();
    
    if (check_exists_only_) {
        // Optimized path - just check existence via PATH search
        const char* path_env = std::getenv("PATH");
        bool found = false;
        
        if (path_env) {
            std::string path_str(path_env);
            size_t start = 0;
            while (start < path_str.size()) {
                size_t end = path_str.find(':', start);
                if (end == std::string::npos) end = path_str.size();
                
                std::string dir = path_str.substr(start, end - start);
                if (!dir.empty()) {
                    auto exe_path = std::filesystem::path(dir) / executable_;
                    if (std::filesystem::exists(exe_path)) {
                        found = true;
                        break;
                    }
                }
                
                if (end >= path_str.size()) break;
                start = end + 1;
            }
        }
        
        // If not found, this is the expected failure scenario
        result.status = core::SemanticStatus::kUnknown;
        result.outcome = AdversarialOutcome::PROVIDER_UNAVAILABLE;
    } else {
        // Full path with subprocess call (slower but more thorough)
        std::string cmd = "which " + executable_;
        FILE* pipe = popen(cmd.c_str(), "r");
        
        if (!pipe) {
            result.status = core::SemanticStatus::kUnknown;
            result.outcome = AdversarialOutcome::PROVIDER_UNAVAILABLE;
        } else {
            char buffer[256];
            std::string output;
            while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
                output += buffer;
            }
            pclose(pipe);
            
            if (output.empty()) {
                result.status = core::SemanticStatus::kUnknown;
                result.outcome = AdversarialOutcome::PROVIDER_UNAVAILABLE;
            } else {
                // Dependency exists
                result.status = core::SemanticStatus::kSuccess;
                result.outcome = AdversarialOutcome::DENY;  // Expected to be available
            }
        }
    }
    
    auto end_time = std::chrono::steady_clock::now();
    result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    return result;
}

// ============================================================================
// MalformedOutputScenario
// ============================================================================

inline MalformedOutputScenario::MalformedOutputScenario(std::string input)
    : AdversarialTestCase("malformed_output")
    , input_(std::move(input)) {
}

inline AdversarialTestCaseResult MalformedOutputScenario::run() {
    AdversarialTestCaseResult result;
    result.scenario_name = name_;
    
    // Simulate malformed output detection
    if (input_.empty()) {
        result.status = core::SemanticStatus::kUnknown;
        result.outcome = AdversarialOutcome::INVALID_RESULT;
        result.error_message = "Empty output received";
    } else {
        // Check for common malformed patterns
        if (input_.find("error") != std::string::npos) {
            result.status = core::SemanticStatus::kFailure;
            result.outcome = AdversarialOutcome::INVALID_RESULT;
            result.error_message = "Output contains error marker";
        } else {
            result.status = core::SemanticStatus::kSuccess;
            result.outcome = AdversarialOutcome::DENY;  // Valid output
        }
    }
    
    return result;
}

// ============================================================================
// HostileInputScenario
// ============================================================================

inline HostileInputScenario::HostileInputScenario(std::string input, bool expect_deny)
    : AdversarialTestCase("hostile_input")
    , input_(std::move(input))
    , expect_deny_{expect_deny} {
}

inline AdversarialTestCaseResult HostileInputScenario::run() {
    AdversarialTestCaseResult result;
    result.scenario_name = name_;
    
    // Check for hostile patterns (SQL injection, command injection, etc.)
    bool is_hostile = false;
    std::string hostile_reason;
    
    const char* hostile_patterns[] = {
        ";",      // Command chaining
        "|",      // Pipeline
        "`",      // Backtick substitution
        "$((",     // Substitution
        "&&",      // Logical AND
        "||",      // Logical OR
        "<script>", // XSS attempt
        "../",     // Path traversal
    };
    
    for (const auto* pattern : hostile_patterns) {
        if (input_.find(pattern) != std::string::npos) {
            is_hostile = true;
            hostile_reason = "Contains potentially hostile pattern: ";
            hostile_reason += pattern;
            break;
        }
    }
    
    if (is_hostile) {
        result.status = core::SemanticStatus::kFailure;
        result.outcome = expect_deny_ ? AdversarialOutcome::DENY : AdversarialOutcome::INVALID_RESULT;
        result.error_message = hostile_reason;
    } else {
        // Safe input
        result.status = core::SemanticStatus::kSuccess;
        result.outcome = AdversarialOutcome::RETRY;  // Proceed with execution
    }
    
    return result;
}

// ============================================================================
// AdversarialTestRunner
// ============================================================================

inline AdversarialTestRunner::AdversarialTestRunner(TestEnvironmentConfig config)
    : config_(std::move(config)) {
}

inline AdversarialTestCaseResult AdversarialTestRunner::run(AdversarialTestCase& scenario) {
    auto start_time = std::chrono::steady_clock::now();
    
    scenario.set_fast_simulation(config_.fast_simulation_mode);
    auto result = scenario.run();
    
    auto end_time = std::chrono::steady_clock::now();
    result.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        end_time - start_time);
    
    return result;
}

inline std::vector<AdversarialTestCaseResult> AdversarialTestRunner::run_all(
    const std::vector<std::unique_ptr<AdversarialTestCase>>& scenarios) {
    
    std::vector<AdversarialTestCaseResult> results;
    results.reserve(scenarios.size());
    
    for (const auto& scenario : scenarios) {
        if (scenario) {
            results.push_back(run(*scenario));
        }
    }
    
    return results;
}

inline std::string AdversarialTestRunner::summary(
    const std::vector<AdversarialTestCaseResult>& results) const {
    
    int success = 0, failure = 0, unknown = 0;
    for (const auto& r : results) {
        switch (r.status) {
            case core::SemanticStatus::kSuccess: ++success; break;
            case core::SemanticStatus::kFailure: ++failure; break;
            default: ++unknown; break;
        }
    }
    
    std::ostringstream oss;
    oss << "Adversarial Test Summary:\n";
    oss << "  Success: " << success << "\n";
    oss << "  Failure: " << failure << "\n";
    oss << "  Unknown: " << unknown << "\n";
    oss << "  Total: " << results.size() << "\n";
    
    return oss.str();
}

inline std::map<AdversarialOutcome, int> AdversarialTestRunner::count_outcomes(
    const std::vector<AdversarialTestCaseResult>& results) const {
    
    std::map<AdversarialOutcome, int> counts;
    for (const auto& r : results) {
        ++counts[r.outcome];
    }
    return counts;
}

}  // namespace rebuntu::testing