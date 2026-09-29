// Test for Phase 7 Observation Architecture
// Tests core types, interfaces, and basic functionality

#include <system/core/contracts.hpp>
#include "system/observation/types.hpp"
#include "adapters/procfs/process/types.hpp"
#include "adapters/systemd/service/types.hpp"
#include <cassert>
#include <iostream>
#include <chrono>

using namespace rebuntu::system::observation;

void test_observation_domain() {
    assert(to_string(ObservationDomain::kProcess) == "process");
    assert(to_string(ObservationDomain::kService) == "service");
    assert(to_string(ObservationDomain::kUnknown) == "unknown");
    std::cout << "test_observation_domain: PASS\n";
}

void test_observation_identity() {
    ObservationIdentity id;
    id.domain_id = "nginx.service";
    id.domain = ObservationDomain::kService;
    
    assert(id.is_valid());
    assert(id.domain == ObservationDomain::kService);
    assert(id.domain_id == "nginx.service");
    
    // Test equality
    ObservationIdentity id2{id};
    assert(id == id2);
    
    // Test less-than
    id2.domain_id = "apache2.service";
    assert((id < id2) != (id2 < id));
    
    std::cout << "test_observation_identity: PASS\n";
}

void test_observation_quality() {
    assert(to_string(ObservationQuality::kUnknown) == "unknown");
    assert(to_string(ObservationQuality::kPartial) == "partial");
    assert(to_string(ObservationQuality::kObserved) == "observed");
    assert(to_string(ObservationQuality::kAuthoritative) == "authoritative");
    std::cout << "test_observation_quality: PASS\n";
}

void test_freshness_policy() {
    FreshnessPolicy policy;
    assert(policy.max_age_ms.count() == 30000);  // Default is 30 seconds
    assert(!policy.allow_stale);
    assert(!policy.fail_on_stale);
    
    policy.max_age_ms = std::chrono::milliseconds(1000);
    policy.allow_stale = true;
    assert(policy.max_age_ms.count() == 1000);
    assert(policy.allow_stale);
    
    std::cout << "test_freshness_policy: PASS\n";
}

void test_observation_factory() {
    ObservationIdentity id;
    id.domain_id = "proc:1234";
    id.domain = ObservationDomain::kProcess;
    
    // Test make_state
    auto obs1 = Observation::make_state(id, "state", "running", "procfs");
    assert(obs1.subject == id);
    assert(obs1.field == "state");
    assert(obs1.raw_value.has_value());
    assert(*obs1.raw_value == "running");
    assert(obs1.source == "procfs");
    
    // Test make_property with optional value
    auto obs2 = Observation::make_property(id, "memory_kb", std::optional<std::string>("4096"), "procfs");
    assert(obs2.field == "memory_kb");
    assert(obs2.raw_value.has_value());
    assert(*obs2.raw_value == "4096");
    
    std::cout << "test_observation_factory: PASS\n";
}

void test_truth_value() {
    assert(to_string(TruthValue::kTrue) == "true");
    assert(to_string(TruthValue::kFalse) == "false");
    assert(to_string(TruthValue::kUnknown) == "unknown");
    std::cout << "test_truth_value: PASS\n";
}

void test_fact() {
    Fact fact;
    fact.subject.domain_id = "service:test";
    fact.subject.domain = ObservationDomain::kService;
    fact.predicate = "is_active";
    fact.truth = TruthValue::kTrue;
    fact.canonical_value = "running";
    
    assert(fact.subject.is_valid());
    assert(fact.predicate == "is_active");
    assert(fact.truth == TruthValue::kTrue);
    
    std::cout << "test_fact: PASS\n";
}

void test_snapshot_state() {
    assert(to_string(SnapshotState::kUnknown) == "unknown");
    assert(to_string(SnapshotState::kComplete) == "complete");
    assert(to_string(SnapshotState::kPartial) == "partial");
    assert(to_string(SnapshotState::kEmpty) == "empty");
    std::cout << "test_snapshot_state: PASS\n";
}

void test_truncation() {
    Truncation t1 = Truncation::no_truncation();
    assert(!t1.was_truncated);
    
    Truncation t2 = Truncation::with_reason("Too many records");
    assert(t2.was_truncated);
    assert(t2.reason.has_value());
    assert(*t2.reason == "Too many records");
    
    std::cout << "test_truncation: PASS\n";
}

void test_snapshot() {
    Snapshot s = Snapshot::make();
    assert(!s.snapshot_id.empty());
    assert(s.state == SnapshotState::kUnknown);
    
    // Test make_empty
    Snapshot s2 = Snapshot::make_empty("Test reason");
    assert(s2.state == SnapshotState::kEmpty);
    assert(!s2.errors.empty());
    
    // Test add_observation
    ObservationIdentity id;
    id.domain_id = "test";
    id.domain = ObservationDomain::kUnknown;
    Observation o = Observation::make_state(id, "field", "value", "source");
    s.add_observation(o);
    
    assert(s.observations.size() == 1);
    assert(!s.observed_domains.empty());
    
    // Test add_fact
    Fact f;
    f.subject.domain_id = "test";
    f.subject.domain = ObservationDomain::kUnknown;
    f.predicate = "is_true";
    s.add_fact(f);
    
    assert(s.facts.size() == 1);
    
    std::cout << "test_snapshot: PASS\n";
}

void test_factory_functions_exist() {
    // Just verify the functions are declared
    auto builder = make_snapshot_builder();
    auto view = make_current_state_view();
    
    assert(builder != nullptr);
    assert(view != nullptr);
    
    std::cout << "test_factory_functions_exist: PASS\n";
}

int main() {
    test_observation_domain();
    test_observation_identity();
    test_observation_quality();
    test_freshness_policy();
    test_observation_factory();
    test_truth_value();
    test_fact();
    test_snapshot_state();
    test_truncation();
    test_snapshot();
    test_factory_functions_exist();
    
    std::cout << "\n=== All observation architecture tests passed! ===\n";
    return 0;
}