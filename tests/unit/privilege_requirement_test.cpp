// rebuntu::tests - PrivilegeRequirement Metadata Tests (Task 6.34)
//
// Test that PrivilegeRequirement metadata is properly integrated into
// OperationDefinition and correctly represents operation privilege requirements.
//
// Key principles tested:
//   - PrivilegeRequirement is an enum with distinct values (kNone, kUserContext, kElevated)
//   - PrivilegeRequirement can be assigned as a member of OperationDefinition
//   - PrivilegeRequirement default value is kNone (no special privilege needed)

#include <cassert>
#include <string>

#include <system/core/contracts.hpp>

void test_privilege_requirement_enum_values() {
    // Test that the enum values are distinct
    rebuntu::core::OperationDefinition::PrivilegeRequirement none = 
        rebuntu::core::OperationDefinition::PrivilegeRequirement::kNone;
    rebuntu::core::OperationDefinition::PrivilegeRequirement user_ctx = 
        rebuntu::core::OperationDefinition::PrivilegeRequirement::kUserContext;
    rebuntu::core::OperationDefinition::PrivilegeRequirement elevated = 
        rebuntu::core::OperationDefinition::PrivilegeRequirement::kElevated;

    // Enum values should be different (0, 1, 2 in order)
    assert(none != user_ctx);
    assert(user_ctx != elevated);
    assert(none != elevated);

    // kNone should be the default
    rebuntu::core::OperationDefinition op;
    assert(op.privilege_requirement == rebuntu::core::OperationDefinition::PrivilegeRequirement::kNone);
}

void test_operation_definition_privilege_metadata() {
    // Test that OperationDefinition has privilege_requirement field
    rebuntu::core::OperationDefinition op;

    // Default should be kNone
    assert(op.privilege_requirement == 
           rebuntu::core::OperationDefinition::PrivilegeRequirement::kNone);

    // Can be set to elevated for privileged operations
    op.privilege_requirement = 
        rebuntu::core::OperationDefinition::PrivilegeRequirement::kElevated;
    assert(op.privilege_requirement == 
           rebuntu::core::OperationDefinition::PrivilegeRequirement::kElevated);

    // Can be set to user_context (rare case)
    op.privilege_requirement = 
        rebuntu::core::OperationDefinition::PrivilegeRequirement::kUserContext;
    assert(op.privilege_requirement == 
           rebuntu::core::OperationDefinition::PrivilegeRequirement::kUserContext);
}

void test_privilege_vs_side_effect_distinction() {
    // Verify that privilege_requirement is separate from side_effect
    rebuntu::core::OperationDefinition op;

    // An operation can have various side effects but different privilege requirements
    op.side_effect = rebuntu::core::SideEffectKind::OBSERVATION;
    op.privilege_requirement = rebuntu::core::OperationDefinition::PrivilegeRequirement::kNone;
    assert(op.side_effect == rebuntu::core::SideEffectKind::OBSERVATION);
    assert(op.privilege_requirement == 
           rebuntu::core::OperationDefinition::PrivilegeRequirement::kNone);

    op.side_effect = rebuntu::core::SideEffectKind::MUTATING;
    op.privilege_requirement = rebuntu::core::OperationDefinition::PrivilegeRequirement::kElevated;
    assert(op.side_effect == rebuntu::core::SideEffectKind::MUTATING);
    assert(op.privilege_requirement == 
           rebuntu::core::OperationDefinition::PrivilegeRequirement::kElevated);
}

int main() {
    test_privilege_requirement_enum_values();
    test_operation_definition_privilege_metadata();
    test_privilege_vs_side_effect_distinction();

    return 0;
}