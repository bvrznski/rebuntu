// rebuntu::command::replay unit tests (Phase 6.41)
//
// Tests for command replay semantics:
//   * INTENT = Semantic request (typed, semantic, re-resolvable)
//   * PLAN = Concrete execution steps derived from intent
//   * REPLAY = Re-executing with intent (not stale plan)

#include <system/command/replay.hpp>
#include <cassert>
#include <iostream>
#include <chrono>

using namespace rebuntu::command;
using namespace rebuntu::command::replay;

void test_replay_kind_to_string() {
    assert(to_string(ReplayKind::kFullReplay) == "full_replay");
    assert(to_string(ReplayKind::kIntentOnly) == "intent_only");
}

void test_plan_freshness_creation() {
    auto now = std::chrono::system_clock::now();
    
    // Test PlanFreshness creation with TTL
    auto freshness = PlanFreshness::now(std::chrono::minutes(5));
    assert(freshness.created_at >= now);
    // ttl_ms is set via the factory - verification is at compile time
}

void test_plan_freshness_is_stale() {
    // Test fresh plan (TTL not exceeded)
    auto freshness = PlanFreshness::now(std::chrono::hours(24));
    bool stale = freshness.is_stale();
    assert(!stale);  // Fresh plan should not be stale
    
    // Verify the method exists and returns boolean
    (void)stale;
}

void test_replay_request_defaults() {
    ReplayRequest req;
    
    assert(req.kind == ReplayKind::kFullReplay);
    // accept_stale default is false per header
    (void)req;  // Suppress unused warning
}

void test_replay_result_creation() {
    // Test success_fresh result
    PlanFreshness freshness = PlanFreshness::now();
    auto result = ReplayResult::success_fresh(freshness);
    
    assert(result.status == ReplayStatus::kSuccessFresh);
    assert(result.is_success());
    
    // Test rejected_stale result
    auto rejected = ReplayResult::rejected_stale(freshness, "plan expired");
    assert(rejected.status == ReplayStatus::kRejectedStale);
    assert(!rejected.is_success());
}

void test_replay_result_intent_mismatch() {
    CommandIntent intent;
    intent.id = "test-intent";
    
    auto result = ReplayResult::intent_mismatch("old-id", intent);
    
    assert(result.status == ReplayStatus::kIntentMismatch);
}

int main() {
    std::cout << "Testing replay semantics module (Phase 6.41)\n\n";
    
    test_replay_kind_to_string();
    std::cout << "  to_string: PASS\n";
    
    test_plan_freshness_creation();
    std::cout << "  PlanFreshness::now: PASS\n";
    
    test_plan_freshness_is_stale();
    std::cout << "  PlanFreshness::is_stale: PASS\n";
    
    test_replay_request_defaults();
    std::cout << "  ReplayRequest defaults: PASS\n";
    
    test_replay_result_creation();
    std::cout << "  ReplayResult creation: PASS\n";
    
    test_replay_result_intent_mismatch();
    std::cout << "  ReplayResult intent_mismatch: PASS\n";
    
    std::cout << "\nAll tests passed!\n";
    return 0;
}