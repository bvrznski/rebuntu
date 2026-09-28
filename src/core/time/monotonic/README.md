# Rebuntu Monotonic Deadline System (Phase 6.30)

## Overview

This module provides monotonic deadline support for Rebuntu's execution system.

## Key Principles

1. **Monotonic Time**: Uses `std::chrono::steady_clock` which is unaffected by wall-clock adjustments
2. **Deadline Propagation**: Deadlines flow through the call stack from callers to callees
3. **Post-Deadline Assessment**: After deadline expiry, assess what state was changed
4. **Time Budget Management**: Distribute deadline across sub-operations

## Core Types

### MonotonicDeadline
An absolute point in monotonic time by which an operation must complete.

```cpp
// Create a deadline 5 seconds from now
auto deadline = MonotonicDeadline::from_duration(std::chrono::seconds(5));

// Check if expired
if (deadline.is_expired()) {
    // Deadline has passed
}
```

### MonotonicContext
A context that carries deadline information through the call stack.

```cpp
// Start with default context (no deadline)
MonotonicContext ctx = default_monotonic_context;

// Add a 10 second deadline
auto ctx_with_deadline = ctx.with_deadline(MonotonicDeadline::from_duration(std::chrono::seconds(10)));

// Create child context with shorter timeout
auto child_ctx = ctx_with_deadline.with_timeout(
    MonotonicTimeout{std::chrono::seconds(3)});
```

### MonotonicResult
A result type that includes deadline tracking information.

```cpp
MonotonicResult<int> result = some_operation();
if (result.is_timeout()) {
    // Operation timed out - assess state changes
}
```

## Integration Points

1. **OperationExecution**: Deadlines attached to operation requests
2. **SubprocessExecutor**: Subprocesses inherit parent context deadline
3. **IPC**: IPC calls carry deadline through the call stack
4. **Provider Calls**: Providers respect caller's deadline context

## Post-Deadline Assessment

When a deadline expires, execution may have partially completed:

```
Execution Plan:
  Step 1: Create resource A
  Step 2: Modify resource B  
  Step 3: Verify state C

Result: Deadline expired at step 2

Assessment:
  - Resource A was created (may need cleanup)
  - Resource B may be in inconsistent state
  - Resource C was not verified

Recovery options:
  - Rollback step 1
  - Leave in partial state for admin review
  - Attempt to complete remaining steps
```

## Usage Example

```cpp
// Create an execution context with deadline
auto start_time = std::chrono::steady_clock::now();
MonotonicContext ctx;
ctx.deadline = MonotonicDeadline::from_duration(std::chrono::seconds(30));

// Run operation with deadline monitoring
auto result = run_operation_with_deadline(ctx, [&]() {
    // Your operation code here
    return perform_work();
});

if (result.is_timeout()) {
    // Handle timeout - assess what changed
    std::cerr << "Deadline expired: " << result.post_deadline_assessment << "\n";
}
```

## API Reference

- `MonotonicDeadline`: Absolute deadline point in monotonic time
- `MonotonicTimeout`: Relative maximum duration for an operation  
- `MonotonicContext`: Context carrying deadline information
- `MonotonicResult<T>`: Result with deadline tracking
- `DeadlineStatus`: kNotSet, kActive, kExpired, kExhausted