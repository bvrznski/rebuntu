#Cancellation Points (Phase 6.29)

## Overview

This module defines cancellation points and semantics for Rebuntu operations.

## Key Principles

1. **Cancellation is cooperative** - Operations check for cancellation at defined points and respond appropriately
2. **No automatic rollback** - Cancellation does NOT imply rollback; state may be left in a partially modified state
3. **Re-observation required** - After cancellation, the system must re-observe potentially affected state before retrying
4. **Cancellation is a signal** - It's not an execution model change but a request to terminate early

## Cancellation Points

Operations can be cancelled at these logical boundaries:

| Point | Description |
|-------|-------------|
| `kNone` | No cancellation point (execution complete) |
| `kPreconditionCheck` | Before any state mutation |
| `kPlanGeneration` | During operation planning |
| `kExecutionStart` | Just before native action begins |
| `kExecutionPhase` | During native action execution |
| `kVerificationStart` | Just before postcondition verification |
| `kVerificationPhase` | During postcondition verification |

## Cancellation Effects

The effect of cancellation depends on the point at which it occurs:

| Effect | Description |
|--------|-------------|
| `kNone` | No meaningful work done, safe to retry |
| `kPartial` | Some progress made; idempotent operations can be retried safely |
| `kUncertain` | State may be inconsistent; must re-observe before retrying |

## Cancellation Semantics

Each operation type declares its cancellation behavior via `CancellationSemantics`:

```cpp
struct CancellationSemantics {
    bool cancellable = true;
    std::vector<CancellationPoint> cancellable_points;
    std::map<CancellationPoint, CancellationEffect> effect_at_point;
    CancellationPolicy default_policy;
    bool always_requires_verification = true;
};
```

## Policy Configuration

Operations can configure cancellation behavior:

```cpp
struct CancellationPolicy {
    bool fail_fast = false;  // Stop immediately without cleanup?
    
    enum class CleanupStrategy {
        kNone,            // No cleanup (leave state as-is)
        kIdempotentRetry, // Safe to retry idempotent operations
        kManualVerify,    // Must re-observe before determining next step
    } cleanup_strategy;
    
    bool requires_verification = true;  // Must verify postconditions?
    
    enum class PostCancelAction {
        kRetry,           // Try the operation again
        kRollForward,     // Attempt to complete original intent
        kAbandon,         // Mark as failed, no further action
    } post_cancel_action;
};
```

## Cancellation Result

When cancelled, operations return `CancellationResult<T>` with full context:

```cpp
template <typename T>
struct CancellationResult {
    core::SemanticStatus status = core::SemanticStatus::kCancelled;
    std::optional<T> value;  // May be partial
    
    CancellationPoint point_of_cancel;
    std::string cancellation_reason;
    
    CancellationContext context;
    CancellationPolicy policy;
    
    std::vector<core::Evidence> post_cancel_evidence;
    VerificationStatus verification_status = VerificationStatus::kNotVerified;
};
```

## Integration with Existing Infrastructure

Cancellation integrates with:
- `CancellationToken` - Thread-safe cancellation token for propagation
- `RuntimeContext` - Execution context with timeout and retry policies
- `WorkState` - Runtime state including `kCancelled`
- `SemanticStatus` - Outcome includes `kCancelled`

## Example Usage

```cpp
// Define cancellation semantics for an operation type
CancellationSemantics semantics;
semantics.cancellable = true;
semantics.cancellable_points = {
    CancellationPoint::kPreconditionCheck,
    CancellationPoint::kExecutionStart,
    CancellationPoint::kExecutionPhase
};
semantics.effect_at_point[CancellationPoint::kPreconditionCheck] = 
    CancellationEffect::kNone;
semantics.effect_at_point[CancellationPoint::kExecutionPhase] = 
    CancellationEffect::kUncertain;

// Register with the registry
registry.register_operation("filesystem.copy", semantics);

// Check for cancellation during operation execution
if (cancellation_token.is_cancelled()) {
    return CancellationResult<void>::cancelled_at(
        CancellationPoint::kExecutionPhase,
        "Operation was cancelled"
    );
}
```

## Verification After Cancellation

After any cancellation:
1. Re-observe potentially affected state from native sources
2. Compare to expected postconditions
3. Determine if partial progress needs recovery
4. Generate evidence of final state for audit

**Important**: A cancelled operation is NOT considered a success. The system must independently verify the current state.