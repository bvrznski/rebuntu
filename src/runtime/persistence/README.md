# Rebuntu Runtime Persistence Module

## Overview

The `rebuntu::runtime::persistence` module provides execution record persistence for restart/reconciliation/audit functionality in Phase 6.

## Purpose

Persist only the minimal execution facts required for:

1. **Restart** - Recover in-flight executions after a crash
2. **Reconciliation** - Compare observed vs desired state
3. **Audit** - Complete execution history for compliance/debugging

## Minimal Execution Facts

Each `ExecutionRecord` persists:
- Request-level identity (`request_id`)
- Execution-level identity (`execution_id`, `parent_execution_id`)
- Timing information (`started_at`, `finished_at`)
- Outcome (`outcome`, `verification_successful`)
- Retry tracking (`attempt_number`)
- Cancellation/timeout flags
- Optional result summary and evidence references

## Interface

### FilesystemPersistence

Simple file-based implementation that stores records in a directory.

```cpp
rebuntu::runtime::persistence::FilesystemPersistence persist("/var/log/rebuntu/executions");

// Save a record
persist.save(record);

// Load by execution_id
auto record = persist.load(exec_id);

// List recent records (for audit)
auto recent = persist.list_recent(100);
```

## Usage Pattern

```cpp
#include <system/runtime/persistence/integration.hpp>
#include <system/core/contracts.hpp>

void example() {
    // Create persistence instance
    auto executor = std::make_unique<rebuntu::runtime::persistence::FilesystemPersistence>(
        "/var/log/rebuntu/executions"
    );
    
    // Execute operation...
    // After completion, save record:
    rebuntu::runtime::persistence::ExecutionRecord record;
    record.request_id = "req-123";
    record.execution_id = "exec-456";
    record.started_at = std::chrono::system_clock::now();
    // ... populate other fields ...
    
    executor->save(record);
}
```

## File Format

Records are stored as simple key=value files with `.exec` extension:
```
request_id=req-123
execution_id=exec-456
parent_execution_id=
started_at=1727520000000
finished_at=1727520001234
outcome=0
verification_successful=1
attempt_number=1
was_cancelled=0
timed_out=0