// rebuntu::shell::semi_natural — Semi-Natural Command Grammar Implementation (Phase 6.16)
//
// This module implements the semi-natural grammar parser for Rebuntu's shell language.
// It extends deterministic parsing to support controlled semi-natural expressions while
// maintaining the principle that the shell is a presentation surface, not an independent runtime.
//
// Design Philosophy:
//   * Shell is a PRESENTATION SURFACE, not an independent runtime
//   * Typed IR ensures deterministic parsing before execution
//   * Semi-natural sugar is canonicalized to the same IR as concise syntax
//   * Ambiguity in interpretation must be detected and reported

#include "semi_natural.hpp"
#include "types.hpp"
#include <algorithm>
#include <cctype>
#include <sstream>

namespace rebuntu::shell {

// ============================================================================
// GrammarRule implementation
// ============================================================================

std::optional<std::string> GrammarRule::default_subject_for_verb(std::string_view verb) const {
    // Default subject inference based on verb semantics
    static const std::map<std::string, std::string> verb_to_subject = {
        {"install", "package"},
        {"remove", "package"},
        {"uninstall", "package"},
        {"start", "service"},
        {"stop", "service"},
        {"restart", "service"},
        {"enable", "service"},
        {"disable", "service"},
        {"status", "service"},
    };
    
    auto it = verb_to_subject.find(std::string(verb));
    if (it != verb_to_subject.end()) {
        return it->second;
    }
    return std::nullopt;
}

// ============================================================================
// SemiNaturalParser implementation
// ============================================================================

SemiNaturalParser::SemiNaturalParser(const CommandRegistry& registry)
    : registry_(&registry) {}

ParseResult SemiNaturalParser::parse(const std::vector<std::string>& tokens) const {
    ParseResult result;
    
    if (tokens.empty()) {
        result.diagnostics.push_back("empty token list");
        return result;
    }
    
    // First, try concise parsing
    result = parse_concise_(tokens);
    
    // If concise parsing didn't find a known verb, try semi-natural forms
    if (!result.has_ambiguity && registry_ && !registry_->find(result.intent.verb)) {
        ParseResult semi_result = parse_semi_natural_(tokens);
        if (semi_result.kind != GrammarKind::kConcise) {
            // Semi-natural parsing found something
            result = semi_result;
        }
    }
    
    return result;
}

ParseResult SemiNaturalParser::parse_concise_(const std::vector<std::string>& tokens) const {
    ParseResult result;
    result.kind = GrammarKind::kConcise;
    
    // First token should be the verb
    if (tokens.empty()) {
        result.diagnostics.push_back("empty command");
        return result;
    }
    
    CommandIntent intent;
    
    // Use the registry to get command metadata
    auto cmd_meta_opt = registry_->find(tokens[0]);
    if (!cmd_meta_opt.has_value()) {
        result.diagnostics.push_back("unknown verb: " + tokens[0]);
        return result;
    }
    
    intent.verb = tokens[0];
    intent.kind = IntentKind::kVerb;
    intent.subject = cmd_meta_opt->subject_type;
    
    // Remaining tokens are arguments/targets
    for (size_t i = 1; i < tokens.size(); ++i) {
        if (!intent.target.has_value()) {
            intent.target = tokens[i];
        } else {
            // Multiple targets - store in arguments for now
            intent.arguments.emplace_back("target", tokens[i]);
        }
    }
    
    result.intent = std::move(intent);
    return result;
}

ParseResult SemiNaturalParser::parse_semi_natural_(const std::vector<std::string>& tokens) const {
    ParseResult result;
    result.kind = GrammarKind::kSemiNatural;
    
    if (tokens.empty()) {
        result.diagnostics.push_back("empty command");
        return result;
    }
    
    CommandIntent intent;
    std::optional<std::string> subject;
    std::optional<std::string> target;
    
    // Find the first token that matches a known verb
    size_t verb_idx = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        if (registry_->find(tokens[i])) {
            verb_idx = i;
            break;
        }
    }
    
    if (verb_idx >= tokens.size()) {
        result.diagnostics.push_back("no known verb found in command");
        return result;
    }
    
    intent.verb = tokens[verb_idx];
    
    // Determine subject and target based on token positions
    auto cmd_meta_opt = registry_->find(intent.verb);
    
    if (cmd_meta_opt.has_value() && cmd_meta_opt->subject_type.has_value()) {
        subject = cmd_meta_opt->subject_type.value();
    } else {
        // Try to infer subject from verb
        GrammarRule default_rule;
        auto inferred_subject = default_rule.default_subject_for_verb(intent.verb);
        if (inferred_subject.has_value()) {
            subject = inferred_subject.value();
        }
    }
    
    intent.subject = subject;
    
    // Target is usually after the subject or at the end
    for (size_t i = verb_idx + 1; i < tokens.size(); ++i) {
        target = tokens[i];
    }
    
    if (target.has_value()) {
        intent.target = target.value();
    }
    
    result.intent = std::move(intent);
    return result;
}

ParseResult SemiNaturalParser::parse_predicate_style_(const std::string& input) const {
    ParseResult result;
    result.kind = GrammarKind::kPredicateStyle;
    result.diagnostics.push_back("predicate-style input detected");
    return result;
}

CommandIntent SemiNaturalParser::canonicalize(const CommandIntent& intent) const {
    // Apply normalization rules:
    // - Ensure verb is in canonical form
    // - Normalize subject inference if needed
    // - Standardize target representation
    
    // For now, just return the intent as-is since we use standard IR
    return intent;
}

std::vector<GrammarRule> SemiNaturalParser::get_rules() const {
    std::vector<GrammarRule> rules;
    
    GrammarRule concise_rule;
    concise_rule.name = "concise";
    concise_rule.kind = GrammarKind::kConcise;
    concise_rule.priority = 10;
    concise_rule.require_all_arguments = true;
    rules.push_back(std::move(concise_rule));
    
    GrammarRule semi_natural_rule;
    semi_natural_rule.name = "semi-natural";
    semi_natural_rule.kind = GrammarKind::kSemiNatural;
    semi_natural_rule.priority = 5;
    semi_natural_rule.require_all_arguments = false;
    rules.push_back(std::move(semi_natural_rule));
    
    return rules;
}

// ============================================================================
// GrammarAnalyzer implementation
// ============================================================================

GrammarAnalyzer::DeterminismAnalysis GrammarAnalyzer::analyze_phrase(
    const std::vector<std::string>& tokens,
    const CommandRegistry& registry
) {
    DeterminismAnalysis analysis;
    
    if (tokens.empty()) {
        analysis.is_deterministic = false;
        analysis.reason_for_ambiguity = "empty command";
        return analysis;
    }
    
    // Check if first token is a known verb
    auto cmd_meta_opt = registry.find(tokens[0]);
    
    if (!cmd_meta_opt.has_value()) {
        analysis.is_deterministic = false;
        analysis.reason_for_ambiguity = "unknown verb: " + tokens[0];
        return analysis;
    }
    
    // If verb is known, the phrase is deterministic
    analysis.candidate_count = 1;
    analysis.is_deterministic = true;
    
    return analysis;
}

// ============================================================================
// SemiNaturalGrammarBuilder implementation
// ============================================================================

void SemiNaturalGrammarBuilder::add_verb_rule(
    std::string verb,
    GrammarKind kind,
    int priority,
    std::optional<std::string> default_subject
) {
    GrammarRule rule;
    rule.name = verb;
    rule.kind = kind;
    rule.priority = priority;
    
    // Store for later use in parsing
    rules_.push_back(std::move(rule));
}

std::vector<GrammarRule> SemiNaturalGrammarBuilder::build() const {
    return rules_;
}

}  // namespace rebuntu::shell