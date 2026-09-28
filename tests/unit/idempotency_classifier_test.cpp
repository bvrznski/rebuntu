// Rebuntu Idempotency Classifier Unit Tests (Phase 6.23)
//
// Test the automatic idempotency classification system.

#include <system/core/contracts.hpp>
#include <system/idempotency/classifier.hpp>
#include <cassert>
#include <iostream>

using namespace rebuntu::core;
using namespace rebuntu::idempotency;

void test_observation_operation_idempotent() {
    OperationDefinition op;
    op.id = "filesystem.exists";
    op.title = "Check if file exists";
    op.description = "Query whether a path exists";
    op.subject_type = "filesystem.path";
    op.side_effect = SideEffectKind::OBSERVATION;
    
    IdempotencyClassifier classifier;
    auto result = classifier.classify(op);
    
    assert(result.idempotency == Idempotency::IDEMPOTENT);
    std::cout << "PASS: Observation operation classified as IDEMPOTENT\n";
}

void test_mutating_operation_conditional() {
    OperationDefinition op;
    op.id = "filesystem.copy";
    op.title = "Copy file";
    op.description = "Copy a file from source to destination";
    op.subject_type = "filesystem.path";
    op.side_effect = SideEffectKind::MUTATING;
    
    IdempotencyClassifier classifier;
    auto result = classifier.classify(op);
    
    // Mutating operations are conditionally idempotent
    assert(result.idempotency == Idempotency::CONDITIONALLY_IDEMPOTENT);
    std::cout << "PASS: Mutating operation classified as CONDITIONALLY_IDEMPOTENT\n";
}

void test_destructive_operation_non_idempotent() {
    OperationDefinition op;
    op.id = "filesystem.remove";
    op.title = "Remove file";
    op.description = "Delete a file permanently";
    op.subject_type = "filesystem.path";
    op.side_effect = SideEffectKind::DESTRUCTIVE;
    
    IdempotencyClassifier classifier;
    auto result = classifier.classify(op);
    
    assert(result.idempotency == Idempotency::NON_IDEMPOTENT);
    std::cout << "PASS: Destructive operation classified as NON_IDEMPOTENT\n";
}

void test_none_side_effect() {
    OperationDefinition op;
    op.id = "system.info";
    op.title = "Get system info";
    op.description = "Query current system state";
    op.subject_type = "system.state";
    op.side_effect = SideEffectKind::NONE;
    
    IdempotencyClassifier classifier;
    auto result = classifier.classify(op);
    
    assert(result.idempotency == Idempotency::IDEMPOTENT);
    std::cout << "PASS: NONE side effect classified as IDEMPOTENT\n";
}

void test_retry_safety() {
    OperationDefinition op;
    op.id = "filesystem.read";
    op.title = "Read file";
    op.description = "Read file contents";
    op.subject_type = "filesystem.path";
    op.side_effect = SideEffectKind::OBSERVATION;
    
    IdempotencyClassifier classifier;
    auto safety = classifier.get_retry_safety(op);
    
    assert(safety == RetrySafety::RETRY_SAFE);
    std::cout << "PASS: Observation operation retry-safe\n";
}

void test_explicit_classification_respected() {
    OperationDefinition op;
    op.id = "custom.operation";
    op.title = "Custom operation";
    op.description = "Test custom idempotency setting";
    op.subject_type = "test.object";
    op.side_effect = SideEffectKind::MUTATING;
    op.idempotency = Idempotency::IDEMPOTENT;  // Explicitly set
    op.reversibility = Reversibility::REVERSIBLE;  // Explicitly set
    
    IdempotencyClassifier classifier;
    auto result = classifier.classify(op);
    
    assert(result.idempotency == Idempotency::IDEMPOTENT);
    assert(result.reversibility == Reversibility::REVERSIBLE);
    std::cout << "PASS: Explicit idempotency setting respected\n";
}

void test_evidence_collection() {
    OperationDefinition op;
    op.id = "test.create";
    op.title = "Test create";
    op.description = "Create a resource";
    op.subject_type = "test.object";
    op.side_effect = SideEffectKind::MUTATING;
    op.postconditions.emplace_back("resource created");
    
    IdempotencyClassifier classifier;
    auto result = classifier.classify(op);
    
    // Should have evidence
    assert(!result.evidence.empty());
    std::cout << "PASS: Evidence collected for classification\n";
}

void test_default_idempotency_by_kind() {
    assert(get_default_idempotency(SideEffectKind::NONE) == Idempotency::IDEMPOTENT);
    assert(get_default_idempotency(SideEffectKind::OBSERVATION) == Idempotency::IDEMPOTENT);
    assert(get_default_idempotency(SideEffectKind::MUTATING) == Idempotency::CONDITIONALLY_IDEMPOTENT);
    assert(get_default_idempotency(SideEffectKind::DESTRUCTIVE) == Idempotency::NON_IDEMPOTENT);
    
    std::cout << "PASS: Default idempotency by side effect kind\n";
}

void test_default_reversibility_by_kind() {
    assert(get_default_reversibility(SideEffectKind::NONE) == Reversibility::REVERSIBLE);
    assert(get_default_reversibility(SideEffectKind::OBSERVATION) == Reversibility::REVERSIBLE);
    assert(get_default_reversibility(SideEffectKind::MUTATING) == Reversibility::CONDITIONALLY_REVERSIBLE);
    assert(get_default_reversibility(SideEffectKind::DESTRUCTIVE) == Reversibility::IRREVERSIBLE);
    
    std::cout << "PASS: Default reversibility by side effect kind\n";
}

void test_max_retries_by_idempotency() {
    assert(RetryPolicyFromClassification::max_retries_for_idempotent(Idempotency::IDEMPOTENT) == 3);
    assert(RetryPolicyFromClassification::max_retries_for_idempotent(Idempotency::CONDITIONALLY_IDEMPOTENT) == 2);
    assert(RetryPolicyFromClassification::max_retries_for_idempotent(Idempotency::NON_IDEMPOTENT) == 0);
    
    std::cout << "PASS: Max retries by idempotency\n";
}

int main() {
    std::cout << "=== Idempotency Classifier Unit Tests ===\n\n";
    
    test_observation_operation_idempotent();
    test_mutating_operation_conditional();
    test_destructive_operation_non_idempotent();
    test_none_side_effect();
    test_retry_safety();
    test_explicit_classification_respected();
    test_evidence_collection();
    test_default_idempotency_by_kind();
    test_default_reversibility_by_kind();
    test_max_retries_by_idempotency();
    
    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}