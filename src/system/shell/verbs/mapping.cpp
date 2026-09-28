// rebuntu::shell::verbs::mapping — Verb to Operation Mapping Implementation (Phase 6.8)
//
// This module implements the verb-to-operation mapping functionality.

#include "mapping.hpp"
#include <system/core/contracts.hpp>
#include <system/shell/collision_scanner.hpp>

namespace rebuntu::shell::verbs {

VerbMappingRegistry::VerbMappingRegistry() {
    register_builtin_mappings_();
}

void VerbMappingRegistry::register_builtin_mappings_() {
    // Get collision scanner to populate collision status
    rebuntu::shell::collision::CollisionScanner collision_scanner;
    
    auto get_collision_status_string = [](std::string_view verb) -> std::optional<std::string> {
        auto status = rebuntu::shell::collision::get_collision_status(verb);
        if (status == rebuntu::shell::collision::CollisionClass::kNone) {
            return std::nullopt;
        }
        return rebuntu::shell::collision::to_string(status);
    };
    
    // Filesystem operations
    mappings_["copy"] = VerbMapping{
        .verb = "copy",
        .kind = IntentKind::kVerb,
        .subject_type = "filesystem.path",
        .mapped_operation_id = "filesystem.copy",
        .side_effect = SideEffectClass::MUTATING,
        .description = "Copy a file from source to destination"
    };
    
    // Package operations (placeholder - would be implemented by package manager)
    mappings_["install"] = VerbMapping{
        .verb = "install",
        .kind = IntentKind::kVerb,
        .subject_type = "package",
        .side_effect = SideEffectClass::MUTATING,
        .description = "Install a package"
    };
    
    mappings_["remove"] = VerbMapping{
        .verb = "remove",
        .kind = IntentKind::kVerb,
        .subject_type = "package",
        .side_effect = SideEffectClass::DESTRUCTIVE,
        .description = "Remove a package"
    };
    
    // Service operations
    mappings_["restart"] = VerbMapping{
        .verb = "restart",
        .kind = IntentKind::kVerb,
        .subject_type = "service",
        .side_effect = SideEffectClass::MUTATING,
        .description = "Restart a service"
    };
    
    mappings_["start"] = VerbMapping{
        .verb = "start",
        .kind = IntentKind::kVerb,
        .subject_type = "service",
        .side_effect = SideEffectClass::MUTATING,
        .description = "Start a service"
    };
    
    mappings_["stop"] = VerbMapping{
        .verb = "stop",
        .kind = IntentKind::kVerb,
        .subject_type = "service",
        .side_effect = SideEffectClass::MUTATING,
        .description = "Stop a service"
    };
    
    // Query operations
    mappings_["list"] = VerbMapping{
        .verb = "list",
        .kind = IntentKind::kQuery,
        .subject_type = std::nullopt,
        .side_effect = SideEffectClass::OBSERVATION,
        .description = "List resources"
    };
    
    mappings_["status"] = VerbMapping{
        .verb = "status",
        .kind = IntentKind::kQuery,
        .subject_type = std::nullopt,
        .side_effect = SideEffectClass::OBSERVATION,
        .description = "Show status of a resource"
    };
    
    // Predicates
    mappings_["installed"] = VerbMapping{
        .verb = "installed",
        .kind = IntentKind::kPredicate,
        .subject_type = "package",
        .side_effect = SideEffectClass::OBSERVATION,
        .description = "Check if a package is installed"
    };
    
    mappings_["running"] = VerbMapping{
        .verb = "running",
        .kind = IntentKind::kPredicate,
        .subject_type = "service",
        .side_effect = SideEffectClass::OBSERVATION,
        .description = "Check if a service is running"
    };
    
    // Add collision status for all verbs
    std::vector<std::string> verbs_to_check = {
        "copy", "install", "remove", "restart", "start", "stop",
        "list", "status", "installed", "running"
    };
    
    for (const auto& verb : verbs_to_check) {
        auto it = mappings_.find(verb);
        if (it != mappings_.end()) {
            it->second.collision_status = get_collision_status_string(verb);
        }
    }
}

std::optional<VerbMapping> VerbMappingRegistry::find(const std::string& verb) const {
    auto it = mappings_.find(verb);
    if (it == mappings_.end()) return std::nullopt;
    return it->second;
}

std::vector<VerbMapping> VerbMappingRegistry::all() const {
    std::vector<VerbMapping> result;
    for (const auto& [name, mapping] : mappings_) {
        result.push_back(mapping);
    }
    std::sort(result.begin(), result.end(),
              [](const VerbMapping& a, const VerbMapping& b) { return a.verb < b.verb; });
    return result;
}

bool VerbMappingRegistry::is_known_verb(const std::string& verb) const {
    return mappings_.find(verb) != mappings_.end();
}

std::vector<std::string> get_shell_verb_list() {
    VerbMappingRegistry registry;
    return registry.get_verb_list();
}

std::vector<std::string> VerbMappingRegistry::get_verb_list() const {
    std::vector<std::string> verbs;
    for (const auto& [name, mapping] : mappings_) {
        verbs.push_back(mapping.verb);
    }
    std::sort(verbs.begin(), verbs.end());
    return verbs;
}

}  // namespace rebuntu::shell::verbs