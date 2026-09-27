// rebuntu::shell::subjects — Subject Resolution Implementation (Phase 6.3)
//
// This module implements the subject resolution machinery for Rebuntu's
// shell language.

#include "subjects.hpp"
#include <algorithm>

namespace rebuntu::shell {

// ============================================================================
// SubjectRegistry Implementation
// ============================================================================

SubjectDefinition SubjectRegistry::find_by_kind(SubjectKind kind) const {
    auto it = subjects_.find(kind);
    if (it == subjects_.end()) {
        return SubjectDefinition{};
    }
    return it->second;
}

bool SubjectRegistry::verb_accepted(SubjectKind kind, std::string verb) const {
    auto it = subjects_.find(kind);
    if (it == subjects_.end()) {
        return false;
    }
    
    const auto& def = it->second;
    return std::find(def.accepted_verbs.begin(), def.accepted_verbs.end(), verb)
           != def.accepted_verbs.end();
}

// ============================================================================
// SubjectResolver Implementation
// ============================================================================

SubjectResolver::SubjectResolver(const SubjectRegistry* registry)
    : registry_(registry) {}

bool SubjectResolver::resolve(
    SubjectKind kind,
    const std::string& target,
    int scope,
    SubjectResolution& out_resolution
) const {
    // Basic validation: check if the subject kind is known in the registry
    auto def = registry_->find_by_kind(kind);
    
    if (def.kind == SubjectKind::kUnknown) {
        out_resolution.status = SubjectResolutionStatus::kNotFound;
        out_resolution.diagnostic = "subject type not found in registry";
        return false;
    }
    
    // Validate target length
    if (target.length() < def.min_length) {
        out_resolution.status = SubjectResolutionStatus::kUnknownTarget;
        out_resolution.diagnostic = "target too short (minimum: " + std::to_string(def.min_length) + ")";
        return false;
    }
    
    if (target.length() > def.max_length) {
        out_resolution.status = SubjectResolutionStatus::kUnknownTarget;
        out_resolution.diagnostic = "target too long (maximum: " + std::to_string(def.max_length) + ")";
        return false;
    }
    
    // In a real implementation, this would:
    // - Query the appropriate provider (systemd, dpkg, procfs, etc.)
    // - Resolve the target to its stable identity
    // - Check scope permissions
    
    out_resolution.status = SubjectResolutionStatus::kSuccess;
    out_resolution.subject_id = target;  // In this simplified version, target == identity
    
    return true;
}

void SubjectResolver::find_candidates(
    SubjectKind kind,
    const std::string& prefix,
    int scope,
    std::vector<std::pair<std::string, std::string>>& out_candidates
) const {
    // In a real implementation, this would query the appropriate provider
    // to find all subjects matching the prefix
    
    out_candidates.clear();
}

}  // namespace rebuntu::shell