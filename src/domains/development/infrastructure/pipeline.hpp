// rebuntu::infrastructure::pipeline — Build/Test/Deployment Pipeline Contracts (Phase 3.10)
//
// This establishes Rebuntu's canonical engineering pipeline across:
//   * Formatting and lint/static analysis
//   * Type checks where configured
//   * Unit tests, integration tests, shell checks
//   * Security-sensitive tests
//   * Package/build artifacts
//   * Isolated native/provider tests
//   * Artifact verification
//
// Key principles:
//   * PROVIDER != CAPABILITY != OPERATION != SERVICE
//   * Pipeline stages are capability-specific assessments
//   * Each stage has its own toolchain dependencies
//   * CI is optional infrastructure (not a production dependency)
//   * Build/test failures must be attributable to specific stages

#pragma once

#include <system/core/contracts.hpp>
#include <domains/development/infrastructure/contracts.hpp>
#include <chrono>
#include <memory>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

namespace rebuntu::infrastructure {

// ============================================================================
// Pipeline Stage Types
// Defines the canonical engineering pipeline stages
// ============================================================================

enum class PipelineStage {
    kEnvironment,        // Environment/bootstrap validation
    kFormatting,         // Code formatting (clang-format)
    kLint,               // Lint/static analysis (clang-tidy, cpplint)
    kTypeCheck,          // Type checking (where configured)
    kUnitTest,           // Unit tests
    kIntegrationTest,    // Integration tests
    kShellCheck,         // Shell script validation
    kSecurityTest,       // Security-sensitive tests
    kPackage,            // Package/build artifacts
    kArtifactVerify,     // Artifact verification
};

inline std::string_view to_string(PipelineStage s) {
    switch (s) {
        case PipelineStage::kEnvironment:      return "environment";
        case PipelineStage::kFormatting:       return "formatting";
        case PipelineStage::kLint:             return "lint";
        case PipelineStage::kTypeCheck:        return "type_check";
        case PipelineStage::kUnitTest:         return "unit_test";
        case PipelineStage::kIntegrationTest:  return "integration_test";
        case PipelineStage::kShellCheck:       return "shell_check";
        case PipelineStage::kSecurityTest:     return "security_test";
        case PipelineStage::kPackage:          return "package";
        case PipelineStage::kArtifactVerify:   return "artifact_verify";
    }
    return "unknown";
}

// ============================================================================
// Pipeline Tool Types
// External tools required for pipeline execution
// ============================================================================

enum class PipelineToolType {
    kFormatter,      // Code formatters (clang-format)
    kLinter,         // Static analyzers (clang-tidy, cpplint)
    kCompiler,       // Compilers (gcc, clang++)
    kBuildSystem,    // Build systems (cmake, make)
    kTesting,        // Test frameworks (ctest, gtest, catch2)
    kShellValidator, // Shell script validators (shellcheck)
};

inline std::string_view to_string(PipelineToolType t) {
    switch (t) {
        case PipelineToolType::kFormatter:     return "formatter";
        case PipelineToolType::kLinter:        return "linter";
        case PipelineToolType::kCompiler:      return "compiler";
        case PipelineToolType::kBuildSystem:   return "build_system";
        case PipelineToolType::kTesting:       return "testing";
        case PipelineToolType::kShellValidator:return "shell_validator";
    }
    return "unknown";
}

// ============================================================================
// Pipeline Stage Result
// Result of executing a single pipeline stage
// ============================================================================

enum class PipelineStageResult {
    kNotRun,          // Stage was skipped (e.g., not enabled)
    kSkipped,         // Stage was explicitly skipped
    kRunning,         // Stage is currently running
    kPassed,          // Stage completed successfully
    kFailed,          // Stage failed (non-zero exit)
    kTimeout,         // Stage timed out
    kCancelled,       // Stage was cancelled
    kError,           // Unexpected error during stage execution
};

inline std::string_view to_string(PipelineStageResult r) {
    switch (r) {
        case PipelineStageResult::kNotRun:     return "not_run";
        case PipelineStageResult::kSkipped:    return "skipped";
        case PipelineStageResult::kRunning:    return "running";
        case PipelineStageResult::kPassed:     return "passed";
        case PipelineStageResult::kFailed:     return "failed";
        case PipelineStageResult::kTimeout:    return "timeout";
        case PipelineStageResult::kCancelled:  return "cancelled";
        case PipelineStageResult::kError:      return "error";
    }
    return "unknown";
}

// ============================================================================
// Pipeline Stage Execution Info
// Information about a pipeline stage execution
// ============================================================================

struct PipelineStageInfo {
    PipelineStage stage;                    // Which stage
    PipelineStageResult result;             // Outcome
    std::optional<std::chrono::milliseconds> duration_ms;
    
    // Tool information for this stage
    std::vector<ToolAssessment> tool_assessments;
    
    // Output/evidence (bounded, no secrets)
    std::optional<std::string> stdout_preview;  // First N chars of stdout
    std::optional<std::string> stderr_preview;  // First N chars of stderr
    
    // Error information (if not success)
    std::optional<rebuntu::core::Error> error;
    
    // Verification status
    bool verified = false;
};

// ============================================================================
// Pipeline Execution Result
// Complete result of a pipeline run
// ============================================================================

struct PipelineResult {
    rebuntu::core::SemanticStatus overall_status;           // Overall pipeline outcome
    
    // Individual stage results (ordered by execution)
    std::vector<PipelineStageInfo> stages;
    
    // Total execution time
    std::optional<std::chrono::milliseconds> total_duration_ms;
    
    // Summary counts
    size_t passed_stages = 0;
    size_t failed_stages = 0;
    size_t skipped_stages = 0;
    size_t total_stages = 0;
    
    // Error information (if not success)
    std::optional<rebuntu::core::Error> error;
    
    static PipelineResult success(std::vector<PipelineStageInfo> stages) {
        PipelineResult r;
        r.overall_status = rebuntu::core::SemanticStatus::kSuccess;
        r.stages = std::move(stages);
        for (const auto& s : r.stages) {
            if (s.result == PipelineStageResult::kPassed) r.passed_stages++;
            else if (s.result == PipelineStageResult::kSkipped || s.result == PipelineStageResult::kNotRun)
                r.skipped_stages++;
            else r.failed_stages++;
        }
        r.total_stages = r.stages.size();
        return r;
    }
    
    static PipelineResult failure(std::vector<PipelineStageInfo> stages, std::string code, std::string message) {
        PipelineResult r;
        r.overall_status = rebuntu::core::SemanticStatus::kFailure;
        r.stages = std::move(stages);
        for (const auto& s : r.stages) {
            if (s.result == PipelineStageResult::kPassed) r.passed_stages++;
            else if (s.result == PipelineStageResult::kSkipped || s.result == PipelineStageResult::kNotRun)
                r.skipped_stages++;
            else r.failed_stages++;
        }
        r.total_stages = r.stages.size();
        r.error = rebuntu::core::Error{std::move(code), std::move(message)};
        return r;
    }
    
    static PipelineResult cancelled(std::string message) {
        PipelineResult r;
        r.overall_status = rebuntu::core::SemanticStatus::kCancelled;
        r.error = rebuntu::core::Error{"E_PIPELINE_CANCELLED", std::move(message)};
        return r;
    }
};

// ============================================================================
// Pipeline Provider Interface
// Interface for executing pipeline stages
// ============================================================================

class PipelineProvider {
public:
    virtual ~PipelineProvider() = default;
    
    // Get provider identity
    virtual std::string provider_id() const = 0;
    
    // Check if this provider is available
    virtual bool is_available() const = 0;
    
    // Execute a single pipeline stage
    virtual PipelineStageInfo execute_stage(
        PipelineStage stage,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) = 0;
    
    // Execute the entire pipeline
    virtual PipelineResult execute_pipeline(
        const std::vector<PipelineStage>& stages,
        std::optional<std::chrono::milliseconds> global_timeout = std::nullopt
    ) = 0;
    
    // Get available stages for this provider
    virtual std::vector<PipelineStage> get_available_stages() const = 0;
};

// ============================================================================
// Native Pipeline Providers (using subprocess execution)
// ============================================================================

namespace pipeline_native {

// Configuration for the native pipeline provider
struct Config {
    std::optional<std::string> clang_format_path;      // Path to clang-format
    std::optional<std::string> clang_tidy_path;        // Path to clang-tidy
    std::optional<std::string> cpplint_path;           // Path to cpplint (Python)
    std::optional<std::string> cmake_path;             // Path to cmake
    std::optional<std::string> make_path;              // Path to make
    std::optional<std::string> ctest_path;             // Path to ctest
    std::optional<std::string> gcc_compiler_path;      // Path to g++ compiler
    std::optional<std::string> shellcheck_path;        // Path to shellcheck
    
    // Paths to source files/directories
    std::vector<std::string> source_dirs;
    std::vector<std::string> header_dirs;
    
    bool cpu_only = true;  // CPU-only execution (policy)
};

// The native pipeline provider executes stages via subprocess
class Provider : public PipelineProvider {
public:
    explicit Provider(Config config);
    ~Provider() override;
    
    // Disable copy/move for resource management
    Provider(const Provider&) = delete;
    Provider& operator=(const Provider&) = delete;
    
    // PipelineProvider interface
    std::string provider_id() const override;
    bool is_available() const override;
    
    PipelineStageInfo execute_stage(
        PipelineStage stage,
        std::optional<std::chrono::milliseconds> timeout = std::nullopt
    ) override;
    
    PipelineResult execute_pipeline(
        const std::vector<PipelineStage>& stages,
        std::optional<std::chrono::milliseconds> global_timeout = std::nullopt
    ) override;
    
    std::vector<PipelineStage> get_available_stages() const override;

private:
    class Impl;
    std::unique_ptr<Impl> pimpl_;
};

}  // namespace pipeline_native

}  // namespace rebuntu::infrastructure