// Rebuntu Runtime — Operation Evidence Bundle Implementation (Phase 6.37)

#include "evidence_bundle.hpp"
#include <algorithm>

namespace rebuntu::runtime::native_command_operation_execution {

OperationEvidenceBundle::OperationEvidenceBundle(EvidenceBundleBounds bounds)
    : bounds_(bounds),
      outcome_(core::SemanticStatus::kUnknown),
      created_at_(std::chrono::system_clock::now()) {
}

void OperationEvidenceBundle::set_request(const core::OperationRequest& req) {
    request_ = req;
}

void OperationEvidenceBundle::record_target_resolution(const std::string& resolved_id) {
    resolved_target_id_ = resolved_id;
}

void OperationEvidenceBundle::record_initial_observations(std::vector<platform::v0040::Evidence> obs) {
    if (initial_observations_.size() + obs.size() > bounds_.max_evidence_records) {
        size_t to_remove = initial_observations_.size() + obs.size() - bounds_.max_evidence_records;
        if (to_remove >= initial_observations_.size()) {
            initial_observations_.clear();
        } else {
            initial_observations_.erase(initial_observations_.begin(), 
                                       initial_observations_.begin() + to_remove);
        }
    }
    std::move(obs.begin(), obs.end(), std::back_inserter(initial_observations_));
}

void OperationEvidenceBundle::set_plan(const platform::v0040::ChangePlan& plan) {
    plan_ = plan;
    has_plan_flag_ = true;
}

void OperationEvidenceBundle::set_validation(const ValidationBundle& validation) {
    validation_ = validation;
    has_validation_flag_ = true;
}

void OperationEvidenceBundle::record_step_result(StepResultBundle step_result) {
    if (step_results_.size() >= bounds_.max_plan_steps) {
        step_results_.erase(step_results_.begin());
    }
    step_results_.push_back(std::move(step_result));
}

void OperationEvidenceBundle::record_verification(
    bool verified,
    std::chrono::system_clock::time_point verified_at,
    std::vector<platform::v0040::Evidence> evidence) {
    
    verification_has_result_ = true;
    verification_result_ = verified;
    if (verified_at.time_since_epoch().count() > 0) {
        verified_at_ = verified_at;
    } else {
        verified_at_ = std::chrono::system_clock::now();
    }
    
    while (verification_evidence_.size() + evidence.size() > bounds_.max_evidence_records && 
           !verification_evidence_.empty()) {
        verification_evidence_.erase(verification_evidence_.begin());
    }
    std::move(evidence.begin(), evidence.end(), std::back_inserter(verification_evidence_));
}

void OperationEvidenceBundle::set_outcome(core::SemanticStatus status, core::Error error) {
    outcome_ = status;
    error_ = error;
}

const StepResultBundle* OperationEvidenceBundle::last_step_result() const noexcept {
    if (step_results_.empty()) {
        return nullptr;
    }
    return &step_results_.back();
}

bool OperationEvidenceBundle::is_overbound() const noexcept {
    size_t total = initial_observations_.size() + step_observations_.size() +
                   verification_evidence_.size();
    for (const auto& sr : step_results_) {
        for (const auto& so : sr.observations) {
            total += so.evidence.size();
        }
    }
    return total > bounds_.max_evidence_records;
}

void OperationEvidenceBundle::trim_old_evidence(std::chrono::system_clock::time_point cutoff) {
    (void)cutoff;
}

size_t OperationEvidenceBundle::evidence_count() const noexcept {
    size_t total = initial_observations_.size() + verification_evidence_.size();
    for (const auto& sr : step_results_) {
        for (const auto& so : sr.observations) {
            total += so.evidence.size();
        }
    }
    return total;
}

EvidenceBundleBuilder::EvidenceBundleBuilder(EvidenceBundleBounds bounds)
    : bounds_(bounds),
      verification_result_{false},
      outcome_(core::SemanticStatus::kUnknown) {
}

EvidenceBundleBuilder& EvidenceBundleBuilder::set_request(const core::OperationRequest& req) {
    request_ = req;
    has_request_ = true;
    return *this;
}

EvidenceBundleBuilder& EvidenceBundleBuilder::record_target_resolution(const std::string& resolved_id) {
    resolved_target_id_ = resolved_id;
    has_resolved_target_ = true;
    return *this;
}

EvidenceBundleBuilder& EvidenceBundleBuilder::record_initial_observations(std::vector<platform::v0040::Evidence> obs) {
    if (initial_observations_.size() + obs.size() > bounds_.max_evidence_records) {
        size_t to_remove = initial_observations_.size() + obs.size() - bounds_.max_evidence_records;
        if (to_remove >= initial_observations_.size()) {
            initial_observations_.clear();
        } else {
            initial_observations_.erase(initial_observations_.begin(), 
                                       initial_observations_.begin() + to_remove);
        }
    }
    std::move(obs.begin(), obs.end(), std::back_inserter(initial_observations_));
    return *this;
}

EvidenceBundleBuilder& EvidenceBundleBuilder::set_plan(const platform::v0040::ChangePlan& plan) {
    plan_ = plan;
    has_plan_flag_ = true;
    return *this;
}

EvidenceBundleBuilder& EvidenceBundleBuilder::set_validation(const ValidationBundle& validation) {
    validation_ = validation;
    has_validation_flag_ = true;
    return *this;
}

EvidenceBundleBuilder& EvidenceBundleBuilder::record_step_result(StepResultBundle step_result) {
    if (step_results_.size() >= bounds_.max_plan_steps) {
        step_results_.erase(step_results_.begin());
    }
    step_results_.push_back(std::move(step_result));
    return *this;
}

EvidenceBundleBuilder& EvidenceBundleBuilder::record_verification(
    bool verified,
    std::vector<platform::v0040::Evidence> evidence) {
    
    verification_result_ = verified;
    verified_at_ = std::chrono::system_clock::now();
    
    while (verification_evidence_.size() + evidence.size() > bounds_.max_evidence_records && 
           !verification_evidence_.empty()) {
        verification_evidence_.erase(verification_evidence_.begin());
    }
    std::move(evidence.begin(), evidence.end(), std::back_inserter(verification_evidence_));
    
    return *this;
}

EvidenceBundleBuilder& EvidenceBundleBuilder::set_outcome(core::SemanticStatus status, core::Error error) {
    outcome_ = status;
    error_ = error;
    return *this;
}

OperationEvidenceBundle EvidenceBundleBuilder::build() {
    OperationEvidenceBundle bundle(bounds_);
    
    if (has_request_) bundle.set_request(request_);
    if (has_resolved_target_) bundle.record_target_resolution(resolved_target_id_);
    bundle.record_initial_observations(std::move(initial_observations_));
    if (has_plan_flag_) bundle.set_plan(plan_);
    if (has_validation_flag_) bundle.set_validation(validation_);
    
    for (auto& sr : step_results_) {
        bundle.record_step_result(std::move(sr));
    }
    
    bundle.record_verification(verification_result_, verified_at_, std::move(verification_evidence_));
    bundle.set_outcome(outcome_, error_);
    
    return bundle;
}

OperationEvidenceBundle create_execution_bundle(
    const core::OperationRequest& request,
    const platform::v0040::ChangePlan& plan,
    const ValidationBundle& validation,
    std::vector<StepResultBundle> step_results,
    bool verification_result,
    core::SemanticStatus final_status,
    EvidenceBundleBounds bounds) {
    
    EvidenceBundleBuilder builder(bounds);
    
    builder.set_request(request)
           .set_plan(plan)
           .set_validation(validation);
    
    for (auto& sr : step_results) {
        builder.record_step_result(std::move(sr));
    }
    
    builder.record_verification(verification_result, {})
           .set_outcome(final_status, {});
    
    return builder.build();
}

std::string evidence_bundle_summary(const OperationEvidenceBundle& bundle) {
    std::string summary = "OperationEvidenceBundle{";
    summary += "request_id=" + bundle.request().operation_id;
    
    if (bundle.has_plan()) {
        platform::v0040::ChangePlan p = bundle.plan_copy();
        summary += ", steps=" + std::to_string(p.steps.size());
    }
    
    summary += ", outcome=" + std::string(rebuntu::core::to_string(bundle.outcome()));
    
    if (bundle.verification_has_result()) {
        summary += ", verified=" + std::string(bundle.verification_result() ? "true" : "false");
    }
    
    summary += ", evidence_count=" + std::to_string(bundle.evidence_count());
    summary += "}";
    
    return summary;
}

}  // namespace rebuntu::runtime::native_command_operation_execution