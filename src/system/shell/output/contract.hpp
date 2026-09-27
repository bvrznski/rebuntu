// rebuntu::shell::output — Structured Output Contract (Phase 6.11)
//
// This module defines the canonical structured output contract for shell commands:
//
//   * CommandResult: Typed result with status, evidence, verification
//   * PredicateResult: Truth value for predicates (TRUE/FALSE/UNKNOWN) - already in types.hpp
//   * RenderMode: Human vs machine rendering modes
//   * OutputSchema: JSON/JSONL serialization contract
//
// Key Principles:
//   * Structured output is primary; human output is a renderer
//   * Machine consumers get stable, parseable data structures
//   * Humans get prose with proper formatting and context
//   * TRUE/FALSE/UNKNOWN are always distinguishable for predicates

#pragma once

#include <string>
#include <vector>
#include <optional>

#include "../types.hpp"

namespace rebuntu::shell {

enum class RenderMode {
    AUTO,
    HUMAN,
    STRUCTURED,
    SILENT,
};

inline std::string to_string(RenderMode m) {
    switch (m) {
        case RenderMode::AUTO:     return "auto";
        case RenderMode::HUMAN:    return "human";
        case RenderMode::STRUCTURED:return "structured";
        case RenderMode::SILENT:   return "silent";
    }
    return "unknown";
}

struct OutputContext {
    RenderMode mode{RenderMode::AUTO};
    bool color_enabled{true};
    size_t max_width{80};
    bool include_timestamps{false};
    bool compact{false};
    
    static OutputContext from_env();
};

using SemanticStatus = core::SemanticStatus;
using Evidence = core::Evidence;
using Error = core::Error;

struct StructuredResult {
    static constexpr const char* SCHEMA_VERSION = "1.0";
    
    SemanticStatus status{SemanticStatus::kUnknown};
    std::optional<bool> is_true;
    std::string command_id;
    std::string verb;
    std::optional<std::string> subject_type;
    std::optional<std::string> target;
    bool changed{false};
    bool verified{false};
    int64_t elapsed_ms{0};
    std::vector<Evidence> evidence;
    std::optional<Error> error;
    std::vector<std::string> warnings;
    std::optional<std::string> output_value;
    std::optional<int> exit_code;
    
    std::string to_json() const;
    
    static constexpr const char* schema_version = SCHEMA_VERSION;
};

struct RenderedOutput {
    std::string text;
    bool is_structured{false};
    int exit_code{0};
    
    static RenderedOutput success(std::string t, bool structured = false) {
        RenderedOutput r;
        r.text = std::move(t);
        r.is_structured = structured;
        r.exit_code = 0;
        return r;
    }
    
    static RenderedOutput failure(std::string m, int code = 1) {
        RenderedOutput r;
        r.text = std::move(m);
        r.exit_code = code;
        return r;
    }
};

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual RenderedOutput render(const StructuredResult& result, const OutputContext& ctx) const = 0;
    virtual bool supports_mode(RenderMode m) const { (void)m; return true; }
};

class HumanRenderer : public Renderer {
public:
    RenderedOutput render(const StructuredResult& result, const OutputContext& ctx) const override;
    
private:
    std::string format_status(SemanticStatus s) const;
    std::string format_duration(int64_t ms) const;
};

class JSONRenderer : public Renderer {
public:
    RenderedOutput render(const StructuredResult& result, const OutputContext& ctx) const override;
    
private:
    std::string escape_string(const std::string& s) const;
    std::string to_json_value(const Evidence& e) const;
};

class JSONLRenderer : public Renderer {
public:
    RenderedOutput render(const StructuredResult& result, const OutputContext& ctx) const override;
};

class CollectionRenderer : public Renderer {
public:
    CollectionRenderer() = default;
    
    void add_result(StructuredResult r);
    RenderedOutput render() const;
    
private:
    std::vector<StructuredResult> results_;
};

}  // namespace rebuntu::shell