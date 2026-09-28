# Idempotency Classification System (Phase 6.23)

## Overview

This module provides automatic idempotency classification for operations in Rebuntu's execution system.

Idempotency is a crucial property that determines whether an operation can be safely retried when failures occur:

- **IDEMPOTENT**: Multiple executions have the same effect as one execution (safe to retry)
- **CONDITIONALLY_IDEMPOTENT**: Idempotent only under certain conditions (retry with caution)
- **NON_IDEMPOTENT**: Each execution has distinct effects (should not be retried automatically)

## Classification Categories

### 1. Idempotency Status

| Category | Description | Retry Behavior |
|----------|-------------|----------------|
| `IDEMPOTENT` | Same result on repeated calls with same inputs | Safe to retry multiple times |
| `CONDITIONALLY_IDEMPOTENT` | May be idempotent depending on context/conditions | Limited retries recommended |
| `NON_IDEMPOTENT` | Each call produces distinct state change | Should not be retried automatically |
| `UNKNOWN` | Cannot determine without analysis | Conservative approach |

### 2. Reversibility Status

| Category | Description |
|----------|-------------|
| `REVERSIBLE` | Can be undone by applying inverse operation |
| `CONDITIONALLY_REVERSIBLE` | Reversible only with specific rollback mechanism |
| `IRREVERSIBLE` | Cannot be undone once executed |
| `UNKNOWN` | Cannot determine reversibility |

### 3. Retry Safety

| Category | Description |
|----------|-------------|
| `RETRY_SAFE` | Safe to retry without side effects |
| `RETRY_CONDITIONAL` | Safe only under certain conditions |
| `NOT_RETRY_SAFE` | Should not be retried automatically |

## Classifier API

```cpp
#include <system/idempotency/classifier.hpp>

rebuntu::idempotency::IdempotencyClassifier classifier;

// Classify an operation
auto result = classifier.classify(operation_def);

// Get retry safety
auto safety = classifier.get_retry_safety(operation_def);
bool is_safe = classifier.is_retry_safe(operation_def);
```

## Default Classification Rules

| Side Effect Kind | Idempotency | Reversibility |
|------------------|-------------|---------------|
| `NONE` / `OBSERVATION` | IDEMPOTENT | REVERSIBLE (N/A) |
| `MUTATING` | CONDITIONALLY_IDEMPOTENT | CONDITIONALLY_REVERSIBLE |
| `PRIVILEGED` | CONDITIONALLY_IDEMPOTENT | CONDITIONALLY_REVERSIBLE |
| `DESTRUCTIVE` | NON_IDEMPOTENT | IRREVERSIBLE |

## Usage in Retry/Recovery

The classification is used to determine retry behavior:

1. **Idempotent operations**: Can be safely retried up to 3 times
2. **Conditionally idempotent**: Limited retries (up to 2)
3. **Non-idempotent**: No automatic retries

## Integration Points

- `core::OperationDefinition`: Has explicit `idempotency` and `reversibility` fields
- `automation/retries`: Uses classification for retry policy decisions
- `control/recovery`: Uses classification to determine if rollback is needed