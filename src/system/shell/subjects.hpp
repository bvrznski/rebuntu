// rebuntu::shell::subjects — Object/Subject Vocabulary (Phase 6.3)
//
// This module defines the canonical nouns/subjects that Rebuntu commands
// operate on:
//   - services
//   - processes
//   - packages
//   - files
//   - mounts
//   - devices
//   - GPUs
//   - displays
//   - networks
//   - operations
//   - workflows
//
// Design Principles:
//   * Subject vocabulary is canonical and bounded (no free-form nouns)
//   * Each subject has a stable identity type
//   * Subject resolution maps concrete targets to domain entities
//   * Subjects align with established Rebuntu ontology

#pragma once

#include "types.hpp"
#include <string>
#include <vector>
#include <map>

namespace rebuntu::shell {

enum class SubjectKind {
    kUnknown,
    kService,
    kProcess,
    kPackage,
    kFile,
    kDirectory,
    kMount,
    kDevice,
    kGpu,
    kDisplay,
    kNetwork,
    kOperation,
    kWorkflow,
    kUser,
    kGroup,
};

enum class StableIdentityType {
    kNone,
    kHardware,
    kGenerated,
    kSemantic,
};

struct SubjectDefinition {
    SubjectKind kind;
    
    std::string name;
    std::string plural_name;
    
    StableIdentityType identity_type;
    
    std::vector<std::string> accepted_verbs;
    
    bool supports_user_scope;
    bool supports_system_scope;
    
    size_t min_length;
    size_t max_length;
    
    std::string summary;
};

enum class SubjectResolutionStatus {
    kSuccess,
    kUnknownTarget,
    kAmbiguous,
    kPermissionDenied,
    kNotFound,
};

struct SubjectResolution {
    SubjectResolutionStatus status;
    
    std::string subject_id;
    
    std::vector<std::string> candidates;
    
    std::string diagnostic;
};

class SubjectRegistry {
public:
    void register_subject(SubjectDefinition def) {
        subjects_[def.kind] = std::move(def);
    }
    
    SubjectDefinition find_by_kind(SubjectKind kind) const;
    
    bool verb_accepted(SubjectKind kind, std::string verb) const;

private:
    std::map<SubjectKind, SubjectDefinition> subjects_;
    
public:
    // Get the registry instance (singleton pattern)
    static SubjectRegistry& instance() {
        static SubjectRegistry inst;
        return inst;
    }
};

class SubjectResolver {
public:
    explicit SubjectResolver(const SubjectRegistry* registry);
    
    // Returns true if resolution succeeded
    bool resolve(
        SubjectKind kind,
        const std::string& target,
        int scope,
        SubjectResolution& out_resolution
    ) const;
    
    void find_candidates(
        SubjectKind kind,
        const std::string& prefix,
        int scope,
        std::vector<std::pair<std::string, std::string>>& out_candidates
    ) const;

private:
    const SubjectRegistry* registry_;
};

namespace error {
    constexpr const char* kUnknownSubject = "E_UNKNOWN_SUBJECT";
    constexpr const char* kInvalidSubjectTarget = "E_INVALID_SUBJECT_TARGET";
    constexpr const char* kAmbiguousSubjectTarget = "E_AMBIGUOUS_SUBJECT_TARGET";
    constexpr const char* kSubjectNotFound = "E_SUBJECT_NOT_FOUND";
}

}  // namespace rebuntu::shell