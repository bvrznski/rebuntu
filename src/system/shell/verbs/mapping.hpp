// rebuntu::shell::verbs::mapping — Verb to Operation Mapping (Phase 6.8)
//
// This module defines the canonical mapping from shell verbs to Phase 0/4
// Operations and Queries.
//
// Design Philosophy:
//   * Shell is a PRESENTATION SURFACE, not an independent runtime
//   * All commands map to canonical Rebuntu Operations

#pragma once

#include "../types.hpp"
#include <string>
#include <vector>
#include <map>

namespace rebuntu::shell::verbs {

struct VerbMapping {
    std::string verb;
    IntentKind kind{IntentKind::kUnknown};
    std::optional<std::string> subject_type;
    std::optional<std::string> mapped_operation_id;
    SideEffectClass side_effect{SideEffectClass::NONE};
    std::string description;
};

class VerbMappingRegistry {
public:
    VerbMappingRegistry();
    
    std::optional<VerbMapping> find(const std::string& verb) const;
    std::vector<VerbMapping> all() const;
    bool is_known_verb(const std::string& verb) const;
    
    // Get all verbs (for completion and listing)
    std::vector<std::string> get_verb_list() const;

private:
    void register_builtin_mappings_();
    std::map<std::string, VerbMapping> mappings_;
};

std::vector<std::string> get_shell_verb_list();

}  // namespace rebuntu::shell::verbs
