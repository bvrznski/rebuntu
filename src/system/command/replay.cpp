// rebuntu::command::replay — Command Replay Semantics Implementation (Phase 6.41)
//
// This module implements command replay semantics:
//
//   * INTENT = Semantic request (typed, semantic, re-resolvable)
//   * PLAN = Concrete execution steps derived from intent
//   * REPLAY = Re-executing with intent (not stale plan)

#include <system/command/replay.hpp>

namespace rebuntu::command::replay {

// ============================================================================
// PlanReplayer implementation
// ============================================================================

PlanReplayer::PlanReplayer(core::FreshnessPolicy /*policy*/)
    : policy_{} {}

CommandResolution PlanReplayer::re_resolve_intent(const CommandIntent& intent) {
    // For Phase 6.41, re-resolution simply returns success with the same capability
    // In a full implementation, this would:
    //   1. Re-look up the command definition
    //   2. Validate the target still exists
    //   3. Re-check scope permissions
    //   4. Return a fresh resolution result
    
    CommandResolution r;
    r.status = ResolutionStatus::kSuccess;
    
    // Create a capability reference based on intent verb
    // This is simplified - full implementation would look up actual command registry
    CapabilityReference cap;
    cap.domain = "command";
    cap.operation = intent.verb;
    
    r.capability = std::move(cap);
    return r;
}

bool PlanReplayer::validate_state_consistency(
    const std::vector<core::Evidence>& /*stored_evidence*/,
    core::FreshnessThreshold /*threshold*/) const {
    
    // In a full implementation, this would:
    //   1. Compare stored evidence with current observations
    //   2. Check if any critical conditions have changed
    //   3. Return true only if the state is still consistent enough to use
    
    // For Phase 6.41: assume stale plans need re-resolution (conservative)
    return false;
}

ReplayResult PlanReplayer::replay(const ReplayRequest& request) {
    ReplayResult result;
    
    // Get current time for freshness calculations
    auto now = std::chrono::system_clock::now();
    
    // Build plan freshness from stored intent metadata
    PlanFreshness freshness;
    freshness.created_at = request.stored_intent.id.empty() 
        ? now 
        : std::chrono::system_clock::from_time_t(0);  // Placeholder
    
    if (request.stored_intent.execution_policy.timeout.count() > 0) {
        freshness.ttl_ms = request.stored_intent.execution_policy.timeout;
    } else {
        // Default TTL from FreshnessThreshold
        freshness.ttl_ms = std::chrono::minutes(5);
    }
    
    result.plan_freshness = freshness;
    
    // Check if plan is stale
    bool is_stale = freshness.is_stale();
    
    // Handle stale plans - always require re-resolution for safety
    if (is_stale) {
        // Stale plan rejected - need re-resolution
        result.status = ReplayStatus::kRejectedStale;
        result.re_resolution_reason = 
            "plan is stale; re-resolution required";
        
        auto vfreshness = freshness.get_verification_freshness(
            request.freshness_threshold);
        if (vfreshness.has_value()) {
            result.verification_freshness = *vfreshness;
        }
        
        return result;
    }
    
    // Fresh plan - full replay with re-resolution
    CommandResolution resolution = re_resolve_intent(request.stored_intent);
    
    if (resolution.status != ResolutionStatus::kSuccess) {
        result.status = ReplayStatus::kRejectedStale;
        result.re_resolution_reason = "re-resolution failed: " + to_string(resolution.status);
        return result;
    }
    
    // Re-resolution succeeded - plan is fresh
    result.status = ReplayStatus::kSuccessFresh;
    result.verification_freshness = freshness.get_verification_freshness(
        request.freshness_threshold);
    
    // In a full implementation, this would:
    //   1. Build fresh execution plan from resolution
    //   2. Execute the new plan
    //   3. Verify postconditions
    //   4. Return successful result
    
    return result;
}

// ============================================================================
// IntentStorage implementation (inline in header)
// ============================================================================

}  // namespace rebuntu::command::replay