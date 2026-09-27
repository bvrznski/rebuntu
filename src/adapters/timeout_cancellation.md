# Timeout and Cancellation Support (Phase 5.49)

## Overview

All discovery adapters now support bounded execution with configurable timeouts and cooperative cancellation.

## Key Components

### AdapterBase

The base class for all adapters that provides:

- **Timeout configuration**: Set fixed duration or absolute deadline
- **Cooperative cancellation**: Checkable cancellation flag
- **Deadline tracking**: Track when operations started relative to timeout

```cpp
class MyAdapter : public rebuntu::adapters::AdapterBase {
public:
    // Use default 10 second timeout
    MyAdapter() : AdapterBase(std::chrono::seconds(10)) {}
    
    void some_operation() {
        if (is_cancelled()) return;
        
        record_operation_start();
        auto timeout = get_timeout();
        
        // ... do work ...
        
        if (is_past_deadline()) {
            // Time's up, abort
            return;
        }
    }
};
```

### TimeoutResult

A result wrapper that includes timing and cancellation metadata:

```cpp
template<typename T>
struct TimeoutResult {
    core::SemanticStatus status;      // kSuccess/kFailure/kCancelled
    std::string description;
    
    std::optional<T> value;           // The actual result (if successful)
    
    std::chrono::milliseconds elapsed_ms;
    bool is_timeout;                  // True if operation timed out
    bool is_cancelled;                // True if cancelled
    
    core::Error err;                  // Error details (where applicable)
};
```

### BoundedAdapter

A template base class that automatically wraps operations with timeout/cancellation:

```cpp
class MyBoundedAdapter : public rebuntu::adapters::BoundedAdapter<MyResultType> {
public:
    auto execute() -> TimeoutResult<MyResultValue> {
        return execute_with_timeout([this]() {
            // Your actual implementation here
            return perform_work();
        });
    }
};
```

## Usage Examples

### Example 1: Basic Timeout Configuration

```cpp
auto adapter = make_my_adapter();

// Set a 5 second timeout for subsequent operations
adapter->set_timeout(std::chrono::seconds(5));

// Or set an absolute deadline
adapter->set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(10));
```

### Example 2: Cooperative Cancellation

```cpp
auto adapter = make_my_adapter();

// Request cancellation from another thread
std::thread t([&adapter]() {
    std::this_thread::sleep_for(std::chrono::seconds(3));
    adapter->cancel();
});

// Main thread checks for cancellation
while (true) {
    if (adapter->is_cancelled()) {
        // Gracefully abort current operation
        break;
    }
    // ... do work ...
}
```

### Example 3: Using BoundedAdapter

```cpp
class MyDiscoveryAdapter 
    : public rebuntu::adapters::BoundedAdapter<MyResultType> {
public:
    auto observe_all() -> TimeoutResult<MyObservation> {
        return execute_with_timeout([this]() {
            // Operation runs with configured timeout
            // is_cancelled() is checked automatically
            // Returns TimeoutResult<T> with timing info
            return do_observation();
        });
    }
};
```

## Implementation Guidelines

1. **Always check cancellation**: Periodically call `is_cancelled()` in long operations
2. **Record operation start**: Call `record_operation_start()` before expensive work
3. **Use relative timeout**: Prefer `set_timeout()` over absolute deadlines when possible
4. **Return TimeoutResult**: Use the wrapper type instead of raw results
5. **Don't hard terminate**: Cancellation is cooperative, not强制

## Design Principles

- **Timeout ≠ Cancellation**: Timeout is a deadline; cancellation is external request
- **Cooperative only**: No forced thread termination - implementations must check flag
- **Adapter-level**: Timeouts apply to all operations on an adapter instance
- **Bounded by default**: All blocking operations should have a timeout