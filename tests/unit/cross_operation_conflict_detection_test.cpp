// Rebuntu Cross-Operation Conflict Detection Unit Tests (Phase 6.32)
//
// Test the cross-operation conflict detection system.

#include <system/core/contracts.hpp>
#include <runtime/native-command-operation-execution/subtask_targets/execution/cross_operation_conflict_detection_b2dd627a.hpp>

#include <cassert>
#include <iostream>

using namespace rebuntu::runtime::native_command_operation_execution;

void test_different_targets_no_conflict() {
    CrossOperationConflictDetection::TargetIdentity target_a{.target_id = "/tmp/a", .subject_type = "filesystem.path"};
    CrossOperationConflictDetection::TargetIdentity target_b{.target_id = "/tmp/b", .subject_type = "filesystem.path"};
    
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target_a,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target_b,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    assert(!CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: Different targets do not conflict\n";
}

void test_same_target_mutating_mutating_conflict() {
    CrossOperationConflictDetection::TargetIdentity target{
        .target_id = "/tmp/file",
        .subject_type = "filesystem.path"
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    assert(CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: Same target with MUTATING+MUTATING conflicts\n";
}

void test_same_target_privileged_mutating_conflict() {
    CrossOperationConflictDetection::TargetIdentity target{
        .target_id = "/etc/passwd",
        .subject_type = "filesystem.path"
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::PRIVILEGED
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    assert(CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: Same target with PRIVILEGED+MUTATING conflicts\n";
}

void test_same_target_destructive_mutating_conflict() {
    CrossOperationConflictDetection::TargetIdentity target{
        .target_id = "/data/file",
        .subject_type = "filesystem.path"
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::DESTRUCTIVE
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    assert(CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: Same target with DESTRUCTIVE+MUTATING conflicts\n";
}

void test_same_target_destructive_anything_conflict() {
    CrossOperationConflictDetection::TargetIdentity target{
        .target_id = "/data/file",
        .subject_type = "filesystem.path"
    };
    
    // Destructive + observation should conflict
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::DESTRUCTIVE
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::OBSERVATION
    };
    
    assert(CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: Same target with DESTRUCTIVE+OBSERVATION conflicts\n";
}

void test_observation_no_conflict() {
    CrossOperationConflictDetection::TargetIdentity target{
        .target_id = "/tmp/file",
        .subject_type = "filesystem.path"
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::OBSERVATION
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::OBSERVATION
    };
    
    assert(!CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: OBSERVATION operations on same target do not conflict\n";
}

void test_none_side_effect_no_conflict() {
    CrossOperationConflictDetection::TargetIdentity target{
        .target_id = "/tmp/file",
        .subject_type = "filesystem.path"
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::NONE
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    assert(!CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: NONE side effect does not conflict with MUTATING\n";
}

void test_observation_plus_mutating_no_conflict() {
    CrossOperationConflictDetection::TargetIdentity target{
        .target_id = "/tmp/file",
        .subject_type = "filesystem.path"
    };
    
    // Observation + MUTATING is compatible (observation doesn't change state)
    CrossOperationConflictDetection::ActiveOperationRecord op_a{
        .operation_id = "op1",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::OBSERVATION
    };
    
    CrossOperationConflictDetection::ActiveOperationRecord op_b{
        .operation_id = "op2",
        .target = target,
        .side_effect = rebuntu::core::SideEffectKind::MUTATING
    };
    
    assert(!CrossOperationConflictDetection::would_conflict(op_a, op_b));
    std::cout << "PASS: OBSERVATION + MUTATING on same target do not conflict\n";
}

void test_execution_detector_begin_end() {
    ExecutionConflictDetector detector;
    
    rebuntu::core::OperationDefinition op_def;
    op_def.id = "filesystem.exists";
    op_def.subject_type = "filesystem.path";
    op_def.side_effect = rebuntu::core::SideEffectKind::OBSERVATION;
    
    // Should start without conflict (no active operations)
    auto result = detector.check_conflict("op1", op_def, "/tmp/test");
    assert(!result.has_value());
    
    detector.begin_execution("op1", op_def, "/tmp/test");
    assert(detector.active_count() == 1);
    
    // Same operation with same target should not conflict (same operation)
    result = detector.check_conflict("op1", op_def, "/tmp/test");
    assert(!result.has_value());
    
    detector.end_execution("op1", "/tmp/test");
    assert(detector.active_count() == 0);
    
    std::cout << "PASS: ExecutionConflictDetector begin/end\n";
}

void test_execution_detector_mutating_conflict() {
    ExecutionConflictDetector detector;
    
    rebuntu::core::OperationDefinition op_def_a;
    op_def_a.id = "filesystem.write";
    op_def_a.subject_type = "filesystem.path";
    op_def_a.side_effect = rebuntu::core::SideEffectKind::MUTATING;
    
    // First mutating operation
    detector.begin_execution("op1", op_def_a, "/tmp/file");
    
    rebuntu::core::OperationDefinition op_def_b;
    op_def_b.id = "filesystem.write2";
    op_def_b.subject_type = "filesystem.path";
    op_def_b.side_effect = rebuntu::core::SideEffectKind::MUTATING;
    
    // Second mutating operation on same target should conflict
    auto result = detector.check_conflict("op2", op_def_b, "/tmp/file");
    assert(result.has_value());
    assert(result->operation_a_id == "op2");
    assert(result->operation_b_id == "op1");
    assert(result->target.target_id == "/tmp/file");
    
    std::cout << "PASS: ExecutionConflictDetector detects mutating conflict\n";
}

void test_execution_detector_different_targets_no_conflict() {
    ExecutionConflictDetector detector;
    
    rebuntu::core::OperationDefinition op_def_a;
    op_def_a.id = "filesystem.write1";
    op_def_a.subject_type = "filesystem.path";
    op_def_a.side_effect = rebuntu::core::SideEffectKind::MUTATING;
    
    detector.begin_execution("op1", op_def_a, "/tmp/file1");
    
    rebuntu::core::OperationDefinition op_def_b;
    op_def_b.id = "filesystem.write2";
    op_def_b.subject_type = "filesystem.path";
    op_def_b.side_effect = rebuntu::core::SideEffectKind::MUTATING;
    
    // Same operation type but different targets - no conflict
    auto result = detector.check_conflict("op2", op_def_b, "/tmp/file2");
    assert(!result.has_value());
    
    std::cout << "PASS: ExecutionConflictDetector different targets no conflict\n";
}

void test_get_mutating_operations() {
    CrossOperationConflictDetection::ActiveOperationRecord records[] = {
        {"op1", {"/tmp/a", "filesystem.path"}, rebuntu::core::SideEffectKind::OBSERVATION},
        {"op2", {"/tmp/b", "filesystem.path"}, rebuntu::core::SideEffectKind::MUTATING},
        {"op3", {"/tmp/c", "filesystem.path"}, rebuntu::core::SideEffectKind::DESTRUCTIVE},
        {"op4", {"/tmp/d", "filesystem.path"}, rebuntu::core::SideEffectKind::NONE}
    };
    
    std::vector<CrossOperationConflictDetection::ActiveOperationRecord> all_records(
        std::begin(records), std::end(records)
    );
    
    auto mutating = CrossOperationConflictDetection::get_mutating_operations(all_records);
    
    assert(mutating.size() == 2);
    assert(mutating[0].operation_id == "op2");
    assert(mutating[1].operation_id == "op3");
    
    std::cout << "PASS: get_mutating_operations returns correct count\n";
}

void test_get_active_targets() {
    CrossOperationConflictDetection::ActiveOperationRecord records[] = {
        {"op1", {"/tmp/a", "filesystem.path"}, rebuntu::core::SideEffectKind::OBSERVATION},
        {"op2", {"/tmp/b", "filesystem.path"}, rebuntu::core::SideEffectKind::MUTATING},
        {"op3", {"/tmp/c", "filesystem.path"}, rebuntu::core::SideEffectKind::DESTRUCTIVE}
    };
    
    std::vector<CrossOperationConflictDetection::ActiveOperationRecord> all_records(
        std::begin(records), std::end(records)
    );
    
    auto targets = CrossOperationConflictDetection::get_active_targets(all_records);
    
    // Should only include mutating targets (not OBSERVATION)
    assert(targets.size() == 2);
    
    std::cout << "PASS: get_active_targets returns correct count\n";
}

void test_has_mutating_operation_on_target() {
    CrossOperationConflictDetection::ActiveOperationRecord records[] = {
        {"op1", {"/tmp/a", "filesystem.path"}, rebuntu::core::SideEffectKind::OBSERVATION},
        {"op2", {"/tmp/b", "filesystem.path"}, rebuntu::core::SideEffectKind::MUTATING}
    };
    
    std::vector<CrossOperationConflictDetection::ActiveOperationRecord> all_records(
        std::begin(records), std::end(records)
    );
    
    CrossOperationConflictDetection::TargetIdentity target_b{"/tmp/b", "filesystem.path"};
    assert(CrossOperationConflictDetection::has_mutating_operation_on_target(target_b, all_records));
    
    CrossOperationConflictDetection::TargetIdentity target_c{"/tmp/c", "filesystem.path"};
    assert(!CrossOperationConflictDetection::has_mutating_operation_on_target(target_c, all_records));
    
    std::cout << "PASS: has_mutating_operation_on_target works correctly\n";
}

int main() {
    std::cout << "=== Cross-Operation Conflict Detection Unit Tests ===\n\n";
    
    test_different_targets_no_conflict();
    test_same_target_mutating_mutating_conflict();
    test_same_target_privileged_mutating_conflict();
    test_same_target_destructive_mutating_conflict();
    test_same_target_destructive_anything_conflict();
    test_observation_no_conflict();
    test_none_side_effect_no_conflict();
    test_observation_plus_mutating_no_conflict();
    
    std::cout << "\n";
    
    test_execution_detector_begin_end();
    test_execution_detector_mutating_conflict();
    test_execution_detector_different_targets_no_conflict();
    
    std::cout << "\n";
    
    test_get_mutating_operations();
    test_get_active_targets();
    test_has_mutating_operation_on_target();
    
    std::cout << "\n=== All tests passed! ===\n";
    return 0;
}