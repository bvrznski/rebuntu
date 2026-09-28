# compensation

Responsibility within `automation`. This component implements **compensation semantics** for Phase 6.26.

## Compensation vs Rollback

Compensation is a recovery pattern with important semantic distinctions:

| Concept | Description |
|---------|-------------|
| **Rollback** | Return to exact prior known state (deterministic undo) |
| **Compensation** | Attempt to reach a valid/acceptable state (best-effort) |

### Key Principles

1. **Implement compensation only where truthful** - Compensation must be based on actual observed state, not assumptions
2. **Best-effort compensation is NOT rollback** - There's semantic distinction: true rollback returns to exact prior state; compensation attempts to reach valid state
3. **Verify compensation effects separately** - Compensation outcome verification must be independent from original operation execution

## Implementation

- `types.hpp`: Typed interfaces for compensation strategies, plans, and results
  - `CompensationStrategy`: kNone, kRollback, kCompensate, kFallback
  - `RollbackKind`: kExact, kCheckpointRestore, kBestEffort
  - `CompensationPlan`: Typed plan with verification requirements
  - `CompensationResult`: Outcome with separate verification status

## Verification Model

```
Original Operation
    ↓ (fails)
Compensation Plan
    ↓
Execute Compensation Actions
    ↓
Re-observe State
    ↓
Verify Compensation Effects (separately from execution)
    ↓
Return Result with independent verification status