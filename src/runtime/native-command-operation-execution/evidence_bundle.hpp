// Rebuntu Runtime — Operation Evidence Bundle (Phase 6.37)
//
// Bounded evidence tying request, resolved target, observations, plan,
// validation, execution result and verification together.
//
// Key principles:
//   - Evidence is bounded: limited in size and scope
//   - No giant serialized object graphs
//   - Evidence is DATA, not CONTROL
//   - Provenance-bearing observations supporting claims

#pragma once

#include <system/core/contracts.hpp>
#include <runtime/phases_0_40_complete.hpp>
#include <chrono>
#include <string>
#include <vector>

namespace rebuntu::runtime::native_command_operation_execution {

struct EvidenceBundleBounds {
    size_t max_evidence_records = 100;
    size_t max_plan_steps = 50;
    size_t max_observations_per_step = 10;
    std::chrono::milliseconds max_bundle_age_ms{60000};
};

struct StepObservation {
    int step_index;
    std::string description;
    platform::v0040::Fields before_state;
    platform::v0040::Fields after_state;
    std::vector<platform::v0040::Evidence> evidence;
};

struct StepResultBundle {
    int step_index;
    std::string description;
    bool succeeded;
    std::vector<StepObservation> observations;
    std::chrono::system_clock::time_point started_at;
    std::chrono::system_clock::time_point finished_at;
};

struct ValidationBundle {
    bool preconditions_satisfied = false;
    bool authorization_granted = false;
    std::vector<std::string> precondition_checks;
    platform::v0040::Authorization authorization_decision;
    std::vector<platform::v0040::Evidence> auth_evidence;
    std::vector<std::string> expected_postconditions;
};

class EvidenceBundleBuilder;

// OperationEvidenceBundle - holds evidence for an operation execution
class OperationEvidenceBundle {
public:
    explicit OperationEvidenceBundle(EvidenceBundleBounds bounds);
    
    // Setters
    void set_request(const core::OperationRequest& req);
    void record_target_resolution(const std::string& resolved_id);
    void record_initial_observations(std::vector<platform::v0040::Evidence> obs);
    void set_plan(const platform::v0040::ChangePlan& plan);
    void set_validation(const ValidationBundle& validation);
    void record_step_result(StepResultBundle step_result);
    void record_verification(bool verified, 
                            std::chrono::system_clock::time_point verified_at = {},
                            std::vector<platform::v0040::Evidence> evidence = {});
    void set_outcome(core::SemanticStatus status, core::Error error = {});
    
    // Getters
    const std::vector<platform::v0040::Evidence>& evidence() const noexcept { return verification_evidence_; }
    bool has_plan() const noexcept { return has_plan_flag_; }
    platform::v0040::ChangePlan plan_copy() const noexcept { return plan_; }
    const core::OperationRequest& request() const noexcept { return request_; }
    const StepResultBundle* last_step_result() const noexcept;
    bool is_overbound() const noexcept;
    void trim_old_evidence(std::chrono::system_clock::time_point cutoff);
    size_t evidence_count() const noexcept;
    
    // Additional getters for private members
    core::SemanticStatus outcome() const noexcept { return outcome_; }
    bool verification_has_result() const noexcept { return verification_has_result_; }
    bool verification_result() const noexcept { return verification_result_; }

private:
    EvidenceBundleBounds bounds_;
    core::OperationRequest request_;
    std::string resolved_target_id_;
    std::vector<platform::v0040::Evidence> initial_observations_;
    std::vector<StepObservation> step_observations_;
    platform::v0040::ChangePlan plan_{};
    bool has_plan_flag_ = false;
    ValidationBundle validation_{};
    bool has_validation_flag_ = false;
    std::vector<StepResultBundle> step_results_;
    bool verification_has_result_ = false;
    bool verification_result_ = false;
    std::chrono::system_clock::time_point verified_at_{};
    std::vector<platform::v0040::Evidence> verification_evidence_;
    core::SemanticStatus outcome_ = core::SemanticStatus::kUnknown;
    core::Error error_{};
    std::chrono::system_clock::time_point created_at_;
};

class EvidenceBundleBuilder {
public:
    explicit EvidenceBundleBuilder(EvidenceBundleBounds bounds = {});
    
    EvidenceBundleBuilder& set_request(const core::OperationRequest& req);
    EvidenceBundleBuilder& record_target_resolution(const std::string& resolved_id);
    EvidenceBundleBuilder& record_initial_observations(std::vector<platform::v0040::Evidence> obs);
    EvidenceBundleBuilder& set_plan(const platform::v0040::ChangePlan& plan);
    EvidenceBundleBuilder& set_validation(const ValidationBundle& validation);
    EvidenceBundleBuilder& record_step_result(StepResultBundle step_result);
    EvidenceBundleBuilder& record_verification(bool verified, std::vector<platform::v0040::Evidence> evidence = {});
    EvidenceBundleBuilder& set_outcome(core::SemanticStatus status, core::Error error = {});
    
    OperationEvidenceBundle build();

private:
    EvidenceBundleBounds bounds_;
    core::OperationRequest request_;
    bool has_request_ = false;
    std::string resolved_target_id_;
    bool has_resolved_target_ = false;
    std::vector<platform::v0040::Evidence> initial_observations_;
    platform::v0040::ChangePlan plan_{};
    bool has_plan_flag_ = false;
    ValidationBundle validation_{};
    bool has_validation_flag_ = false;
    std::vector<StepResultBundle> step_results_;
    bool verification_result_{false};
    std::chrono::system_clock::time_point verified_at_{};
    std::vector<platform::v0040::Evidence> verification_evidence_;
    core::SemanticStatus outcome_ = core::SemanticStatus::kUnknown;
    core::Error error_{};
};

OperationEvidenceBundle create_execution_bundle(
    const core::OperationRequest& request,
    const platform::v0040::ChangePlan& plan,
    const ValidationBundle& validation,
    std::vector<StepResultBundle> step_results,
    bool verification_result,
    core::SemanticStatus final_status,
    EvidenceBundleBounds bounds = {});

std::string evidence_bundle_summary(const OperationEvidenceBundle& bundle);

}  // namespace rebuntu::runtime::native_command_operation_execution