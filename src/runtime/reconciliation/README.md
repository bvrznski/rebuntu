# Rebuntu Runtime Crash Reconciliation (Phase 6.40)

## Overview

The crash reconciliation system enables Rebuntu to discover and reconcile interrupted operations after a restart or crash. It combines durable operation records with fresh Phase-5 observations to safely recover without blindly replaying potentially harmful operations.

## Key Principles

1. **Never blindly replay**: Operations are not automatically re-executed after a restart. Each pending operation must be analyzed to determine the correct recovery action.

2. **Durable + Fresh**: Reconciliation uses:
   - Durable records from disk (what was in progress when interrupted)
   - Fresh Phase-5 observations (current system state)

3. **Typed integration**: The reconciliation engine integrates with Rebuntu's typed operation machinery, not arbitrary shell commands.

## Architecture

```
┌─────────────────────────────────────────────────────────────┐
│                    Crash Detection                           │
│  - /proc/uptime analysis                                     │
│  - Shutdown marker file                                      │
│  - Boot time comparison                                      │
└────────────────┬────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────┐
│              Pending Operation Detection                     │
│  - Scan operation record directory                           │
│  - Parse operation record files                              │
│  - Identify interrupted operations                           │
└────────────────┬────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────┐
│              Reconciliation Engine                           │
│  For each pending operation:                                 │
│    1. Analyze interruption point                             │
│    2. Query current system state (Phase-5)                   │
│    3. Determine recovery action:                             │
│       - Retry from start                                     │
│       - Resume from interruption point                       │
│       - Rollback partial changes                             │
│       - Verify postconditions only                           │
│    4. Execute recovery action                                │
│    5. Update record status                                   │
└────────────────┬────────────────────────────────────────────┘
                 │
                 ▼
┌─────────────────────────────────────────────────────────────┐
│              Reconciliation Report                           │
│  - Summary of all reconciliation actions                     │
│  - Success/failure counts                                    │
│  - Detailed results for each operation                       │
└─────────────────────────────────────────────────────────────┘
```

## Operation Record Structure

```cpp
struct OperationRecord {
    std::string record_id;                    // Unique identifier
    std::string original_request_id;          // Original request that triggered this
    
    std::chrono::system_clock::time_point created_at;
    std::optional<std::chrono::system_clock::time_point> interrupted_at;
    
    std::string operation_id;                 // e.g., "filesystem.copy"
    std::string subject_type;                 // What the operation acts upon
    std::optional<std::string> subject;       // Specific target
    
    ExecutionState execution_state;           // Where it was interrupted
    int steps_completed;                      // Progress before interruption
    int total_steps;                          // Total steps in plan
    
    std::vector<core::Evidence> evidence;     // Evidence collected so far
    std::optional<core::PartialExecutionInfo> partial_execution_info;
    
    OperationRecordStatus record_status;      // Current status
    RecoveryAction recovery_action;           // What to do to recover
};
```

## Execution State Machine

```
Created → Dispatched → Executing → Observing → Verifying → Completed
                                    ↑
                                    └─── (crash/interruption here)
```

After restart, pending operations are in various states and require different recovery:

- **Dispatched**: Can retry from the beginning
- **Executing**: May have partial effects; analyze before deciding
- **Observing/Verifying**: Usually safe to verify again

## Recovery Actions

| Action | Description | When Used |
|--------|-------------|-----------|
| `kNone` | No action needed (already complete) | Record already marked completed |
| `kRetry` | Start from step 1 | Operation never started executing |
| `kResume` | Continue from interruption point | Execution partially done, safe to continue |
| `kRollback` | Undo partial changes | Operation made partial changes that need undoing |
| `kVerifyOnly` | Only verify postconditions | Execution may have completed, just needs verification |

## Integration with Phase-5

The reconciliation system leverages Phase-5 observation infrastructure:

```cpp
// Example integration point
auto fresh_state = evidence_collector.collect({
    .timeout_ms = std::chrono::seconds(30),
    .max_records = 100
});

// Use fresh state to analyze what needs recovery
```

## Usage

### Initialization

```cpp
#include <runtime/reconciliation/types.hpp>
#include <runtime/reconciliation/detector.hpp>

namespace rrecon = rebuntu::runtime::reconciliation;

// Create crash indicator (tracks shutdown state)
auto crash_indicator = rrecon::CrashIndicator{"/var/lib/rebuntu/state"};

// Create pending operation detector
auto detector = rrecon::PendingOperationDetector{
    "/var/lib/rebuntu/operations"
};
```

### Detection

```cpp
// Check if restart occurred
if (crash_indicator.detect_restart()) {
    // Restart detected - proceed with reconciliation
    
    // Scan for pending operations
    auto pending = detector.scan_pending();
    
    // Process each pending operation...
}
```

### Cleanup

After successful reconciliation:

```cpp
// Clear the shutdown marker to indicate clean recovery
crash_indicator.clear_marker();
```

## Directory Layout

```
/var/lib/rebuntu/
├── state/                    # State for crash detection
│   └── rebuntu_shutdown_marker  # Clean shutdown indicator
└── operations/               # Operation record storage
    ├── op-abc123.json        # Operation records (JSON format)
    ├── op-def456.rec         # Alternative .rec extension
    └── ...
```

## Security Considerations

1. **Evidence is untrusted**: All evidence from disk must be re-verified against current state
2. **Authorization required**: Recovery actions still require proper authorization
3. **No secret material**: Records must not contain secret material (enforced by Evidence model)
4. **Bounded recovery**: Resource limits prevent denial-of-service during recovery

## Future Enhancements

1. **Operation record serialization**: JSON/YAML format for human-readable records
2. **Recovery policies**: Configurable behavior for different operation types
3. **Interactive review**: UI for reviewing and approving recovery actions
4. **Rollback planning**: Automatic generation of rollback plans for mutating operations
5. **Audit logging**: Comprehensive log of all reconciliation decisions

## Phase Context

- **Phase 0.x**: Foundational contracts and state models
- **Phase 1.x**: Installation and discovery
- **Phase 2.x**: Environment foundation (authorization, scope, ownership)
- **Phase 3.x**: Semantic boundary and ML integration
- **Phase 4.x**: Runtime foundation
- **Phase 5.x**: Observation and evidence collection
- **Phase 6.40** ← This module: Crash reconciliation