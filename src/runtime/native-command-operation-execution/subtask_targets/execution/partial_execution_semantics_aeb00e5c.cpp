#include "partial_execution_semantics_aeb00e5c.hpp"

// Phase 6.25 - Partial execution semantics implementation
//
// This implementation represents partial mutation explicitly without collapsing
// partial execution into generic failure or success. It preserves completed
// steps/evidence and required recovery/verification.
//
// Key additions to contracts:
//   * SemanticStatus::kPartial - explicit status for partial execution
//   * PartialExecutionStep - record of a single executed step with state snapshots
//   * PartialExecutionInfo - aggregate information about partial execution
//   * Outcome::partial() and OperationResult::partial() factory methods
//   * is_partial() predicates on all result types
//
// Implementation notes:
//   * Helper functions to_string(PartialExecutionStep) and 
//     to_string(const PartialExecutionInfo&) are defined in contracts.hpp
//     within the rebuntu::core namespace

namespace rebuntu::src::runtime::native_command_operation_execution::subtask_targets::execution {

// No additional implementation needed - all types and helpers are in core contracts

} // namespace rebuntu::src::runtime::native_command_operation_execution::subtask_targets::execution
