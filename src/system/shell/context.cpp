// rebuntu::shell::context — Contextual Command Resolution Implementation (Phase 6.15)
//
// This module implements bounded contextual resolution where explicit shell context
// can disambiguate subjects, scope or omitted qualifiers without making behavior
// magical.

#include "context.hpp"
#include <algorithm>

namespace rebuntu::shell {

// ============================================================================
// to_string — Convert ContextKind to string
// ============================================================================

std::string to_string(ContextKind k) {
    switch (k) {
        case ContextKind::kSubject:    return "subject";
        case ContextKind::kScope:      return "scope";
        case ContextKind::kOutputMode: return "output_mode";
        case ContextKind::kQualifier:  return "qualifier";
        case ContextKind::kTargetCache:return "target_cache";
    }
    return "unknown";
}

// ============================================================================
// Context — Session-wide contextual resolution state
// ============================================================================

Context Context::make_empty() {
    return Context{};
}

Context& Context::instance() {
    static Context instance;
    return instance;
}

void Context::set(ContextKind kind, const std::string& key, const std::string& value) {
    entries_[kind][key] = {kind, key, value, false};
}

void Context::set_explicit(ContextKind kind, const std::string& key, const std::string& value) {
    entries_[kind][key] = {kind, key, value, true};
}

bool Context::get(ContextKind kind, const std::string& key, std::string& out_value) const {
    auto it_kind = entries_.find(kind);
    if (it_kind == entries_.end()) {
        return false;
    }
    
    auto it_entry = it_kind->second.find(key);
    if (it_entry == it_kind->second.end()) {
        return false;
    }
    
    out_value = it_entry->second.value;
    return true;
}

void Context::remove(ContextKind kind, const std::string& key) {
    auto it_kind = entries_.find(kind);
    if (it_kind == entries_.end()) {
        return;
    }
    
    it_kind->second.erase(key);
    
    // Clean up empty map entry
    if (it_kind->second.empty()) {
        entries_.erase(it_kind);
    }
}

std::vector<ContextEntry> Context::get_all(ContextKind kind) const {
    std::vector<ContextEntry> result;
    
    auto it = entries_.find(kind);
    if (it == entries_.end()) {
        return result;
    }
    
    for (const auto& [k, entry] : it->second) {
        result.push_back(entry);
    }
    
    return result;
}

std::vector<ContextEntry> Context::all() const {
    std::vector<ContextEntry> result;
    
    for (const auto& [kind, entries_by_key] : entries_) {
        for (const auto& [key, entry] : entries_by_key) {
            result.push_back(entry);
        }
    }
    
    return result;
}

bool Context::empty() const {
    return entries_.empty();
}

void Context::reset_kind(ContextKind kind) {
    entries_.erase(kind);
}

void Context::reset_all() {
    entries_.clear();
}

void Context::set_subject(const std::string& subject) {
    set(ContextKind::kSubject, "current", subject);
}

bool Context::get_subject(std::string& out_value) const {
    return get(ContextKind::kSubject, "current", out_value);
}

void Context::set_scope(int scope) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", scope);
    set(ContextKind::kScope, "default", std::string(buf));
}

int Context::get_scope() const {
    std::string val;
    if (get(ContextKind::kScope, "default", val)) {
        try {
            return std::stoi(val);
        } catch (...) {
            return 0;  // Default to USER scope on parse error
        }
    }
    return 0;  // Default to USER scope
}

void Context::set_output_mode(int mode) {
    char buf[32];
    snprintf(buf, sizeof(buf), "%d", mode);
    set(ContextKind::kOutputMode, "preferred", std::string(buf));
}

int Context::get_output_mode() const {
    std::string val;
    if (get(ContextKind::kOutputMode, "preferred", val)) {
        try {
            return std::stoi(val);
        } catch (...) {
            return 0;  // Default to AUTO mode on parse error
        }
    }
    return 0;  // Default to AUTO mode
}

// ============================================================================
// inspect_context — Utility for inspecting current context state
// ============================================================================

ContextInspection inspect_context() {
    auto& ctx = Context::instance();
    
    ContextInspection inspection;
    inspection.has_context = !ctx.empty();
    
    // Collect active kinds
    auto all_entries = ctx.all();
    for (const auto& entry : all_entries) {
        inspection.active_kinds.push_back(to_string(entry.kind));
    }
    
    // Get scope
    std::string scope_val;
    if (ctx.get(ContextKind::kScope, "default", scope_val)) {
        try {
            inspection.scope = std::stoi(scope_val);
        } catch (...) {
            inspection.scope = -1;  // Invalid value, no scope set
        }
    } else {
        inspection.scope = -1;  // No scope set
    }
    
    // Get subject (as std::string, don't try to convert to int)
    inspection.subject = "";
    bool subject_found = ctx.get(ContextKind::kSubject, "current", inspection.subject);
    if (!subject_found) {
        inspection.subject = "";  // Clear if not found
    }
    
    // Get output mode
    std::string mode_val;
    if (ctx.get(ContextKind::kOutputMode, "preferred", mode_val)) {
        try {
            inspection.output_mode = std::stoi(mode_val);
        } catch (...) {
            inspection.output_mode = -1;  // Invalid value, no output mode set
        }
    } else {
        inspection.output_mode = -1;  // No output mode set
    }
    
    return inspection;
}

// ============================================================================
// ContextManager — Utility for context management operations
// ============================================================================

ContextInspection ContextManager::get_inspection() {
    return inspect_context();
}

void ContextManager::reset_kind(ContextKind kind) {
    Context::instance().reset_kind(kind);
}

void ContextManager::reset_all() {
    Context::instance().reset_all();
}

void ContextManager::set_explicit(ContextKind kind, const std::string& key, const std::string& value) {
    Context::instance().set_explicit(kind, key, value);
}

int ContextManager::get_scope_with_resolution(int explicit_scope, bool has_explicit) {
    if (has_explicit) {
        return explicit_scope;  // Explicit wins
    }
    
    auto ctx = Context::instance();
    return ctx.get_scope();  // Fall back to context default
}

}  // namespace rebuntu::shell
