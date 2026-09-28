// rebuntu::shell::context — Contextual Command Resolution (Phase 6.15)
//
// This module provides bounded contextual resolution where explicit shell context
// can disambiguate subjects, scope or omitted qualifiers without making behavior
// magical:
//
//   - Session-wide context that persists between commands
//   - Inspectable, deterministic, resettable
//   - Cannot widen privilege/scope silently
//   - Explicit arguments always take precedence over context

#pragma once

#include <string>
#include <vector>
#include <map>

namespace rebuntu::shell {

enum class ContextKind {
    kSubject,
    kScope,
    kOutputMode,
    kQualifier,
    kTargetCache
};

struct ContextEntry {
    ContextKind kind;
    std::string key;
    std::string value;
    bool is_explicit{false};
};

class Context {
public:
    static Context make_empty();
    static Context& instance();

    void set(ContextKind kind, const std::string& key, const std::string& value);
    void set_explicit(ContextKind kind, const std::string& key, const std::string& value);
    
    bool get(ContextKind kind, const std::string& key, std::string& out_value) const;
    void remove(ContextKind kind, const std::string& key);

    std::vector<ContextEntry> get_all(ContextKind kind) const;
    std::vector<ContextEntry> all() const;
    bool empty() const;

    void reset_kind(ContextKind kind);
    void reset_all();

    void set_subject(const std::string& subject);
    bool get_subject(std::string& out_value) const;

    void set_scope(int scope);
    int get_scope() const;

    void set_output_mode(int mode);
    int get_output_mode() const;

private:
    std::map<ContextKind, std::map<std::string, ContextEntry>> entries_;
};

struct ContextInspection {
    bool has_context{false};
    std::vector<std::string> active_kinds;
    int scope{-1};
    std::string subject;
    int output_mode{-1};
};

std::string to_string(ContextKind k);
ContextInspection inspect_context();

class ContextManager {
public:
    static ContextInspection get_inspection();
    static void reset_kind(ContextKind kind);
    static void reset_all();
    static void set_explicit(ContextKind kind, const std::string& key, const std::string& value);
    static int get_scope_with_resolution(int explicit_scope, bool has_explicit);
};

}  // namespace rebuntu::shell