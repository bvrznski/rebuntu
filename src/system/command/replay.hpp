// rebuntu::command::replay — Command Replay Semantics (Phase 6.41)
//
// This module defines command replay semantics:
//
//   * INTENT = Semantic request (typed, semantic, re-resolvable)
//   * PLAN = Concrete execution steps derived from intent
//   * REPLAY = Re-executing with intent (not stale plan)
//
// Core invariant established here:
//   STALE_PLAN != EXECUTABLE_PLAN
//   FRESH_RESOLUTION OR EXPLICIT_STALE_APPROVAL_REQUIRED

#pragma once

#include <system/core/contracts.hpp>
#include <system/core/freshness.hpp>
#include <system/command/model.hpp>

#include <chrono>
#include <map>
#include <optional>
#include <string>
#include <vector>

namespace rebuntu::command::replay {

// ============================================================================
// ReplayKind — What gets replayed
// ============================================================================

enum class ReplayKind {
    kFullReplay,       // Re-resolve intent, get fresh plan, execute
    kIntentOnly,       // Execute with stored intent (no re-resolution)
};

inline std::string to_string(ReplayKind k) {
    switch (k) {
        case ReplayKind::kFullReplay:   return "full_replay";
        case ReplayKind::kIntentOnly:   return "intent_only";
    }
    return "unknown";
}

// ============================================================================
// PlanFreshness — Metadata about plan age and validity
// ============================================================================

struct PlanFreshness {
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::milliseconds> ttl_ms;  // time-to-live
    
    // State snapshot at planning time (for revalidation)
    std::vector<core::Evidence> state_snapshot;
    
    static PlanFreshness now(std::optional<std::chrono::milliseconds> ttl = {}) {
        PlanFreshness f;
        f.created_at = std::chrono::system_clock::now();
        f.ttl_ms = ttl;
        return f;
    }
    
    bool is_stale() const {
        if (!ttl_ms.has_value()) return false;
        auto now = std::chrono::system_clock::now();
        auto age = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - created_at);
        return age > ttl_ms.value();
    }
    
    std::optional<core::VerificationFreshness> get_verification_freshness(
        core::FreshnessThreshold threshold) const {
        
        if (!ttl_ms.has_value()) {
            return core::VerificationFreshness::unknown("no TTL set");
        }
        
        auto now = std::chrono::system_clock::now();
        auto age = std::chrono::duration_cast<std::chrono::milliseconds>(
            now - created_at);
        
        if (age <= ttl_ms.value()) {
            return core::VerificationFreshness::fresh(age, threshold);
        }
        
        return core::VerificationFreshness::stale(
            age, threshold, {"plan_creation_time"});
    }
};

// ============================================================================
// ReplayRequest — Request to replay a command
// ============================================================================

struct ReplayRequest {
    std::string intent_id;           // ID of the original intent
    CommandIntent stored_intent;     // Original typed request
    
    ReplayKind kind{ReplayKind::kFullReplay};
    
    // Freshness constraints
    core::FreshnessThreshold freshness_threshold;
    
    // If true, allow stale plans (caller assumes responsibility)
    bool accept_stale{false};
};

// ============================================================================
// ReplayResult — Result of a replay operation
// ============================================================================

enum class ReplayStatus {
    kSuccessFresh,       // Re-executed with fresh resolution
    kSuccessStale,       // Executed stale plan with explicit approval
    kRejectedStale,      // Stale plan rejected (no revalidation)
    kIntentMismatch,     // Stored intent differs from current context
};

inline std::string to_string(ReplayStatus s) {
    switch (s) {
        case ReplayStatus::kSuccessFresh:  return "success_fresh";
        case ReplayStatus::kSuccessStale:  return "success_stale";
        case ReplayStatus::kRejectedStale: return "rejected_stale";
        case ReplayStatus::kIntentMismatch:return "intent_mismatch";
    }
    return "unknown";
}

struct ReplayResult {
    ReplayStatus status{ReplayStatus::kRejectedStale};
    
    // Freshness information
    PlanFreshness plan_freshness;
    std::optional<core::VerificationFreshness> verification_freshness;
    
    // Resolution info (for fresh replays)
    std::optional<std::string> re_resolution_reason;  // why re-resolve was needed
    
    // Execution result (if executed)
    std::optional<CommandResult> execution_result;
    
    // Evidence chain
    std::vector<core::Evidence> evidence;
    
    static ReplayResult success_fresh(const PlanFreshness& freshness) {
        ReplayResult r;
        r.status = ReplayStatus::kSuccessFresh;
        r.plan_freshness = freshness;
        return r;
    }
    
    static ReplayResult success_stale(const PlanFreshness& freshness,
                                       const CommandResult& result) {
        ReplayResult r;
        r.status = ReplayStatus::kSuccessStale;
        r.plan_freshness = freshness;
        r.execution_result = result;
        return r;
    }
    
    static ReplayResult rejected_stale(const PlanFreshness& freshness,
                                        const std::string& reason) {
        ReplayResult r;
        r.status = ReplayStatus::kRejectedStale;
        r.plan_freshness = freshness;
        r.re_resolution_reason = reason;
        return r;
    }
    
    static ReplayResult intent_mismatch(const std::string& stored_id,
                                         const CommandIntent& current_intent) {
        ReplayResult r;
        r.status = ReplayStatus::kIntentMismatch;
        r.evidence.push_back(core::Evidence{
            "intent_id", stored_id, 
            "replay_rejected"});
        return r;
    }
    
    bool is_success() const {
        return status == ReplayStatus::kSuccessFresh ||
               status == ReplayStatus::kSuccessStale;
    }
};

// ============================================================================
// PlanReplayer — Executes replays according to semantics
// ============================================================================

class PlanReplayer {
public:
    explicit PlanReplayer(core::FreshnessPolicy policy = {});
    
    ~PlanReplayer() = default;
    
    // Non-copyable, non-movable for safety
    PlanReplayer(const PlanReplayer&) = delete;
    PlanReplayer& operator=(const PlanReplayer&) = delete;
    
    // Replay a command with freshness validation
    ReplayResult replay(const ReplayRequest& request);
    
    // Re-resolve intent to get fresh plan (called during full replay)
    CommandResolution re_resolve_intent(const CommandIntent& intent);
    
private:
    core::FreshnessPolicy policy_;
    
    // Check if stored state matches current observation
    bool validate_state_consistency(
        const std::vector<core::Evidence>& stored_evidence,
        core::FreshnessThreshold threshold) const;
};

// ============================================================================
// IntentStorage — Stores intents for replay (data structure, no runtime)
// ============================================================================

struct StoredIntent {
    std::string id;                    // Unique ID for this intent
    CommandIntent intent;              // The actual intent
    std::chrono::system_clock::time_point created_at;
    
    // Plan association (if a plan was previously generated)
    std::optional<std::string> latest_plan_id;
    std::optional<PlanFreshness> freshness;
};

class IntentStorage {
public:
    void store(const StoredIntent& intent);
    
    std::optional<StoredIntent> find(std::string_view id) const;
    
    // Get intents by semantic kind for batch operations
    std::vector<StoredIntent> by_kind(SemanticKind kind) const;
    
    size_t count() const { return intents_.size(); }
    
private:
    std::map<std::string, StoredIntent> intents_;
};

// ============================================================================
// ReplayPolicy — User-configurable replay behavior
// ============================================================================

struct ReplayPolicy {
    // Default freshness threshold for plans (if not specified)
    core::FreshnessThreshold default_freshness_threshold{
        std::chrono::minutes(5)  // Plans are fresh for 5 minutes by default
    };
    
    // Whether stale plans require explicit user approval
    bool require_stale_approval{true};
    
    // Maximum age of a plan before it's considered unusable (hard limit)
    std::optional<std::chrono::milliseconds> max_plan_age{
        std::chrono::hours(24)  // Plans older than 24h are never valid
    };
};

}  // namespace rebuntu::command::replay
