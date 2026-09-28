// rebuntu::shell::boundary — Semantic Boundary Implementation (Phase 6.17)
//
// This module implements:
//   - DeterministicFallbackBoundary: Primary fallback mechanism
//   - ExplicitModeSemanticBoundary: Explicit-only semantic mode
//   - Validation against canonical vocabulary

#include "integration.hpp"
#include "../parser.hpp"
#include "../types.hpp"
#include <semantics/provider.hpp>
#include <chrono>

namespace rebuntu::shell::boundary {

using namespace std::chrono_literals;

// ============================================================================
// Helper function: Request intent candidate from semantic provider
// ============================================================================

static std::optional<rebuntu::semantic::IntentCandidate> request_semantic_candidate(
    const std::shared_ptr<rebuntu::semantic::SemanticProvider>& provider,
    const std::string& raw_text,
    const std::vector<std::string>& allowed_operations,
    std::chrono::milliseconds timeout) {
    
    if (!provider || !provider->is_ready()) {
        return std::nullopt;
    }
    
    auto result = provider->generate_intent_candidate(raw_text, allowed_operations, timeout);
    
    if (result.status != core::SemanticStatus::kSuccess) {
        return std::nullopt;
    }
    
    if (!result.response.has_value()) {
        return std::nullopt;
    }
    
    auto& resp = *result.response;
    if (!resp.intent_candidate.has_value()) {
        return std::nullopt;
    }
    
    return resp.intent_candidate.value();
}

// ============================================================================
// DeterministicFallbackBoundary
// ============================================================================

DeterministicFallbackBoundary::DeterministicFallbackBoundary(
    std::shared_ptr<rebuntu::semantic::SemanticProvider> provider)
    : provider_(std::move(provider)) {}

DeterministicFallbackBoundary::~DeterministicFallbackBoundary() = default;

void DeterministicFallbackBoundary::set_fallback_mode(SemanticFallbackMode mode) {
    fallback_mode_ = mode;
}

SemanticFallbackMode DeterministicFallbackBoundary::fallback_mode() const {
    return fallback_mode_;
}

void DeterministicFallbackBoundary::set_allowed_operations(const std::vector<std::string>& ops) {
    allowed_operations_ = ops;
}

void DeterministicFallbackBoundary::set_timeout(std::chrono::milliseconds timeout) {
    timeout_ms_ = timeout;
}

std::chrono::milliseconds DeterministicFallbackBoundary::timeout() const {
    return timeout_ms_;
}

FallbackResult DeterministicFallbackBoundary::fallback_interpret(
    const std::string& raw_text,
    const CommandRegistry& registry
) {
    auto start = std::chrono::system_clock::now();
    
    FallbackResult result;
    result.evidence.deterministic_parse_attempted = true;
    
    parser::ParseError dummy_error{};
    CommandIntent intent{};
    
    auto tokens = parser::tokenize(raw_text);
    
    if (!tokens.empty()) {
        std::vector<std::string> argv;
        for (const auto& t : tokens) {
            argv.push_back(t);
        }
        
        CommandResult cmd_result = parser::parse_argv(argv, registry, intent, dummy_error);
        
        if (cmd_result.status == core::SemanticStatus::kSuccess) {
            result.evidence.semantic_service_used = false;
            result.evidence.request_duration_ms =
                std::chrono::duration_cast<std::chrono::milliseconds>(
                    std::chrono::system_clock::now() - start);
            
            result.status = SemanticFallbackStatus::kNoFallbackNeeded;
            return result;
        }
    }
    
    if (fallback_mode_ == SemanticFallbackMode::kDisabled) {
        result.evidence.semantic_service_used = false;
        result.status = SemanticFallbackStatus::kFallbackRejected;
        result.diagnostic = "semantic fallback disabled";
        return result;
    }
    
    auto semantic_start = std::chrono::system_clock::now();
    result.evidence.semantic_service_used = true;
    
    std::vector<std::string> allowed_verbs;
    for (const auto& cmd : registry.all()) {
        allowed_verbs.push_back(cmd.canonical_name);
    }
    if (allowed_operations_.empty()) {
        allowed_operations_ = allowed_verbs;
    }
    
    auto candidate_opt = request_semantic_candidate(provider_, raw_text, allowed_operations_, timeout_ms_);
    
    if (!candidate_opt) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - semantic_start);
        
        result.evidence.request_duration_ms = elapsed;
        
        if (provider_ && !provider_->is_ready()) {
            result.status = SemanticFallbackStatus::kFallbackUnavailable;
            result.diagnostic = "semantic provider not available";
        } else {
            result.status = SemanticFallbackStatus::kFallbackRejected;
            result.diagnostic = "deterministic parser failed, semantic fallback returned no candidate";
        }
        
        return result;
    }
    
    CommandIntent intent_from_candidate{};
    intent_from_candidate.id = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    intent_from_candidate.kind = IntentKind::kVerb;
    intent_from_candidate.verb = candidate_opt->operation_id;
    
    if (candidate_opt->subject.has_value()) {
        intent_from_candidate.subject = *candidate_opt->subject;
    }
    
    for (const auto& [key, value] : candidate_opt->parameters) {
        intent_from_candidate.arguments.emplace_back(key, value);
    }
    
    intent_from_candidate.scope = ScopeContext::USER;
    
    if (!validate_candidate(intent_from_candidate, registry)) {
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now() - semantic_start);
        
        result.evidence.request_duration_ms = elapsed;
        result.status = SemanticFallbackStatus::kFallbackRejected;
        result.diagnostic = "semantic candidate failed validation";
        return result;
    }
    
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now() - start);
    
    result.evidence.request_duration_ms = elapsed;
    result.status = SemanticFallbackStatus::kFallbackSuccess;
    result.diagnostic = "semantic fallback produced valid candidate";
    
    last_diagnostics_.raw_input = raw_text;
    last_diagnostics_.deterministic_parse_attempted = true;
    last_diagnostics_.semantic_service_used = true;
    last_diagnostics_.semantic_status = SemanticFallbackStatus::kFallbackSuccess;
    last_diagnostics_.total_duration_ms = elapsed;
    
    return result;
}

bool DeterministicFallbackBoundary::validate_candidate(
    const CommandIntent& intent,
    const CommandRegistry& registry
) {
    if (!registry.find(intent.verb).has_value()) {
        return false;
    }
    
    auto cmd_meta = registry.find(intent.verb);
    if (cmd_meta.has_value() && cmd_meta->subject_type.has_value()) {
        if (!intent.subject.has_value() || *intent.subject != *cmd_meta->subject_type) {
            return false;
        }
    }
    
    if (intent.scope != ScopeContext::USER &&
        intent.scope != ScopeContext::SYSTEM &&
        intent.scope != ScopeContext::SESSION &&
        intent.scope != ScopeContext::RUNTIME) {
        return false;
    }
    
    for (const auto& [key, value] : intent.qualifiers) {
        if (value.empty()) continue;
    }
    
    return true;
}

FallbackDiagnostics DeterministicFallbackBoundary::get_last_diagnostics() const {
    return last_diagnostics_;
}

// ============================================================================
// ExplicitModeSemanticBoundary
// ============================================================================

ExplicitModeSemanticBoundary::ExplicitModeSemanticBoundary(
    std::shared_ptr<rebuntu::semantic::SemanticProvider> provider)
    : provider_(std::move(provider)) {}

ExplicitModeSemanticBoundary::~ExplicitModeSemanticBoundary() = default;

void ExplicitModeSemanticBoundary::set_fallback_mode(SemanticFallbackMode mode) {
    if (mode != SemanticFallbackMode::kExplicitOnly &&
        mode != SemanticFallbackMode::kEnabled) {
        fallback_mode_ = SemanticFallbackMode::kExplicitOnly;
    } else {
        fallback_mode_ = mode;
    }
}

SemanticFallbackMode ExplicitModeSemanticBoundary::fallback_mode() const {
    return fallback_mode_;
}

void ExplicitModeSemanticBoundary::set_allowed_operations(const std::vector<std::string>& ops) {
    allowed_operations_ = ops;
}

void ExplicitModeSemanticBoundary::set_timeout(std::chrono::milliseconds timeout) {
    timeout_ms_ = timeout;
}

std::chrono::milliseconds ExplicitModeSemanticBoundary::timeout() const {
    return timeout_ms_;
}

FallbackResult ExplicitModeSemanticBoundary::fallback_interpret(
    const std::string& raw_text,
    const CommandRegistry& registry
) {
    auto start = std::chrono::system_clock::now();
    
    FallbackResult result;
    result.evidence.deterministic_parse_attempted = false;
    
    if (!provider_ || !provider_->is_ready()) {
        result.evidence.semantic_service_used = true;
        result.status = SemanticFallbackStatus::kFallbackUnavailable;
        result.diagnostic = "semantic provider not available";
        return result;
    }
    
    std::vector<std::string> allowed_verbs;
    for (const auto& cmd : registry.all()) {
        allowed_verbs.push_back(cmd.canonical_name);
    }
    if (allowed_operations_.empty()) {
        allowed_operations_ = allowed_verbs;
    }
    
    auto candidate_opt = request_semantic_candidate(provider_, raw_text, allowed_operations_, timeout_ms_);
    
    if (!candidate_opt) {
        result.evidence.semantic_service_used = true;
        result.status = SemanticFallbackStatus::kFallbackRejected;
        result.diagnostic = "semantic service did not produce valid candidate";
        return result;
    }
    
    CommandIntent intent_from_candidate{};
    intent_from_candidate.id = std::to_string(std::chrono::system_clock::now().time_since_epoch().count());
    intent_from_candidate.kind = IntentKind::kVerb;
    intent_from_candidate.verb = candidate_opt->operation_id;
    
    if (candidate_opt->subject.has_value()) {
        intent_from_candidate.subject = *candidate_opt->subject;
    }
    
    for (const auto& [key, value] : candidate_opt->parameters) {
        intent_from_candidate.arguments.emplace_back(key, value);
    }
    
    intent_from_candidate.scope = ScopeContext::USER;
    
    if (!validate_candidate(intent_from_candidate, registry)) {
        result.evidence.semantic_service_used = true;
        result.status = SemanticFallbackStatus::kFallbackRejected;
        result.diagnostic = "semantic candidate failed validation";
        return result;
    }
    
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now() - start);
    
    result.evidence.semantic_service_used = true;
    result.evidence.request_duration_ms = elapsed;
    result.status = SemanticFallbackStatus::kFallbackSuccess;
    result.diagnostic = "semantic mode produced valid candidate";
    
    return result;
}

bool ExplicitModeSemanticBoundary::validate_candidate(
    const CommandIntent& intent,
    const CommandRegistry& registry
) {
    if (!registry.find(intent.verb).has_value()) {
        return false;
    }
    
    auto cmd_meta = registry.find(intent.verb);
    if (cmd_meta.has_value() && cmd_meta->subject_type.has_value()) {
        if (!intent.subject.has_value() || *intent.subject != *cmd_meta->subject_type) {
            return false;
        }
    }
    
    if (intent.scope != ScopeContext::USER &&
        intent.scope != ScopeContext::SYSTEM &&
        intent.scope != ScopeContext::SESSION &&
        intent.scope != ScopeContext::RUNTIME) {
        return false;
    }
    
    for (const auto& [key, value] : intent.qualifiers) {
        if (value.empty()) continue;
    }
    
    return true;
}

// ============================================================================
// SemanticBoundaryFactory
// ============================================================================

std::unique_ptr<SemanticBoundary> SemanticBoundaryFactory::make_boundary(
    SemanticFallbackMode mode,
    std::shared_ptr<rebuntu::semantic::SemanticProvider> provider
) {
    switch (mode) {
        case SemanticFallbackMode::kDisabled:
            return std::make_unique<DeterministicFallbackBoundary>(nullptr);
        
        case SemanticFallbackMode::kExplicitOnly:
            return std::make_unique<ExplicitModeSemanticBoundary>(provider);
        
        case SemanticFallbackMode::kOnFailure:
        case SemanticFallbackMode::kEnabled:
        default:
            return std::make_unique<DeterministicFallbackBoundary>(provider);
    }
}

std::unique_ptr<SemanticBoundary> SemanticBoundaryFactory::make_default_boundary(
    std::shared_ptr<rebuntu::semantic::SemanticProvider> provider
) {
    return make_boundary(SemanticFallbackMode::kOnFailure, provider);
}

}  // namespace rebuntu::shell::boundary