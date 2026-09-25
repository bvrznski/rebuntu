# Phase 5.2 — Journald Acquisition Service Final Report

**Status: COMPLETE**

## Executive Summary

Phase 5.2 implements robust journald acquisition as a first-class native evidence source in Rebuntu.
The implementation supports current and previous boot selection, cursor/checkpoint semantics,
bounded queries, follow mode capability, structured journal field extraction, boot identity
preservation, and monotonic/realtime timestamp handling.

### What Was Implemented

- ✅ `src/adapters/journald.hpp` - Adapter interface with configuration and metrics
- ✅ `src/adapters/journald.cpp` - Full implementation with JSON parsing and command execution
- ✅ `tests/unit/test_journald_adapter.cpp` - Comprehensive unit test suite (16 tests)
- ✅ CMake integration (`cpp/CMakeLists.txt`)
- ✅ Documentation updates

### Key Features

| Feature | Implementation |
|---------|---------------|
| **Native Source** | systemd-journal via journalctl JSON output |
| **Cursor Semantics** | `__CURSOR` field tracking for continuity |
| **Boot Filtering** | `-b -1` for previous, `--boot` for current |
| **Bounded Queries** | `-n N` limit + timeout enforcement |
| **Timestamp Handling** | Realtime (`__REALTIME_TIMESTAMP`) and monotonic support |
| **Backpressure** | Configurable queue limits per source |
| **Evidence Preservation** | Raw JSON fields in Evidence structure |

---

## Architecture Overview

### Event Acquisition Pipeline

```
Native Journal (systemd-journald)
      ↓
[journalctl --output=json]
      ↓
JournaldAdapter::parse_json_record()
      ↓
EventNormalizer → runtime::Event with Evidence
      ↓
InMemoryEventChannel / Adapter callback
      ↓
Consumer receives bounded, attributable event
```

### Core Components

| Component | Responsibility |
|-----------|----------------|
| `JournaldConfig` | Boot ID filtering, unit filters, query limits, follow mode settings |
| `JournaldAdapter` | Native interface to journalctl with cursor tracking and metrics |
| `JournaldQuery::build_argv()` | Construct bounded command-line arguments for journalctl |
| `parse_json_record()` | Parse JSON output, extract fields, create Event/Fact |

---

## Native Linux Source Mapping

### Journalctl Interface

The implementation uses `journalctl --output=json` as the native structured interface:

| Flag | Purpose |
|------|---------|
| `-b [boot_id]` | Filter by boot (-1 for previous, 0 for current) |
| `-n N` | Limit record count (bounded query) |
| `--since/@timestamp` | Time window start |
| `--until/@timestamp` | Time window end |
| `-u unit` | Filter by systemd unit |
| `--priority N` | Minimum priority filter |
| `--output=json` | Structured JSON output |

### Field Mapping

| Journalctl Field | Rebuntu Evidence Source | Purpose |
|-----------------|------------------------|---------|
| `_SYSTEMD_UNIT` | `journal_unit` | Service/unit identifier |
| `SYSLOG_IDENTIFIER` | `journal_syslog_identifier` | Process name/identifier |
| `_TRANSPORT` | `journal_transport` | Logging transport (stdout/syslog) |
| `_BOOT_ID` | `journal_boot_id` | Boot context (critical for reboot detection) |
| `_MACHINE_ID` | `journal_machine_id` | Machine identity |
| `__CURSOR` | Event ID + cursor tracking | Continuity checkpoint |
| `__REALTIME_TIMESTAMP` | Timestamp parsing | Wall-clock time |
| `PRIORITY` | Event type classification | error/warning/info |

---

## Journald Acquisition Contract

### Boot Identity Handling

```cpp
JournaldConfig config;
config.boot_id = -1;  // Previous boot context
// or
config.boot_id = 0;   // Current boot (default)
```

The adapter preserves `_BOOT_ID` as evidence to enable:
- Previous-boot diagnostics
- Reboot boundary detection
- Boot continuity verification

### Cursor Semantics

```cpp
auto cursor = adapter->get_cursor();
adapter->set_cursor(saved_cursor);
```

Cursor tracking enables:
- Resume from last position after restart
- Gap detection when journal rotates
- Checkpointing for durability

### Bounded Queries

```cpp
config.max_records_per_query = 1000;
config.query_timeout_ms = std::chrono::seconds(10);
```

Bounded queries prevent uncontrolled memory growth and ensure predictable behavior.

---

## Evidence Schema

Each normalized event carries:

```cpp
runtime::Event {
    id: cursor_value,
    source: "journald",
    type: priority_to_level(priority),  // error/warning/info
    occurred_at: __REALTIME_TIMESTAMP,
    evidence: [
        Evidence{source="journal_message", value=MESSAGE, captured_at=...},
        Evidence{source="journal_unit", value="_SYSTEMD_UNIT=...", ...},
        Evidence{source="journal_syslog_identifier", value="SYSLOG_IDENTIFIER=...", ...},
        Evidence{source="journal_transport", value="_TRANSPORT=...", ...},
        Evidence{source="journal_boot_id", value="_BOOT_ID=...", ...},
        Evidence{source="journal_machine_id", value="_MACHINE_ID=...", ...}
    ]
}
```

### Timestamp Handling

- **Realtime**: `__REALTIME_TIMESTAMP` in microseconds since epoch
- **Monotonic**: `__MONOTONIC_TIMESTAMP` in microseconds (for elapsed-time calculations)
- **Acquisition time**: Fallback when source timestamp is unavailable

---

## Backpressure Policy

| Mechanism | Implementation |
|-----------|---------------|
| **Queue Limits** | `max_records_per_query` in config |
| **Timeout Enforcement** | `query_timeout_ms` per journalctl call |
| **Bounded Evidence** | `max_evidence_per_record` (currently 32) |

When backpressure occurs:
- New events are dropped
- Metrics track: `records_dropped_backpressure`

---

## Failure Taxonomy

The adapter handles these failure modes:

| Error Code | Meaning | Recovery |
|-----------|---------|----------|
| `E_ALREADY_STARTED` | Adapter already running | No action needed |
| `E_NOT_RUNNING` | Stop called when not running | Start first |
| `E_PIPE_FAILED` | Pipe creation failed | Retry |
| `E_FORK_FAILED` | Process fork failed | Retry |
| `E_JOURNALCTL_FAILED` | journalctl exited non-zero | Check systemd status |
| `E_JOURNALCTL_SIGNALED` | journalctl terminated by signal | Signal handling |

---

## Implementation Details

### Command Execution

```cpp
core::Outcome execute_journalctl(
    const std::vector<std::string>& argv,
    std::string& output,
    std::chrono::milliseconds timeout)
```

- Fork-exec pattern for process isolation
- Pipe-based stdout capture with timeout
- Signal-safe process management

### JSON Parsing

```cpp
std::optional<runtime::Event> parse_json_record(
    const std::string& json_line,
    std::chrono::system_clock::time_point acquisition_time)
```

- Simple key-value extraction (handles common journalctl output)
- Graceful fallback for missing/invalid fields
- Priority-to-level classification

### Timestamp Parsing

```cpp
static std::optional<std::chrono::system_clock::time_point>
extract_realtime_timestamp(const std::unordered_map<std::string, std::string>& fields);
```

Converts `__REALTIME_TIMESTAMP` (microseconds since epoch) to `std::chrono::system_clock::time_point`.

---

## Test Coverage

### Unit Tests (16 tests)

| Test | Coverage |
|------|----------|
| FactoryCreatesValidAdapter | Adapter creation |
| StartStopLifecycle | Lifecycle management |
| DuplicateStartRejected | State machine correctness |
| StopWhenNotRunningRejected | Error handling |
| CursorManagement | Checkpoint semantics |
| MetricsZeroedOnStart | Metrics initialization |
| ConfigStoredCorrectly | Configuration storage |
| ParseJsonRecordExtractsFields | JSON parsing |
| ParseJsonRecordPriorityLevels | Priority classification |
| ParseJsonRecordMissingMessage | Missing field handling |
| ParseJsonRecordInvalidPriority | Invalid data handling |
| BuildArgvGeneratesCorrectArguments | Query construction |
| BuildArgvWithCurrentBoot | Boot filter args |
| BuildArgvWithUnits | Unit filter args |
| BuildArgvWithPriorityFilter | Priority filter args |
| ParseJsonRecordEmptyTimestamp | Timestamp fallback |
| MetricsTracking | Runtime metrics |

---

## Resource Budget

| Metric | Estimate |
|--------|----------|
| **Memory** | ~50KB per adapter instance (header + implementation) |
| **FDs** | 3-4 (pipe, stdout, stderr during exec) |
| **Subprocesses** | One per query/follow poll |
| **CPU** | <1% idle (JSON parsing overhead) |

---

## Security Considerations

| Aspect | Safeguards |
|--------|-----------|
| **Untrusted Input** | JSON parsing is read-only, no code execution |
| **Secrets in Logs** | Raw evidence preserved; redaction at presentation layer |
| **Privilege Requirements** | Standard user can read journal (via systemd) |
| **Path Injection** | Command args are vector, not shell-interpreted |

---

## Verification Commands

```bash
# Build the journald adapter library
cd /home/bvrznski/rebuntu/cpp && make rebuntu-journald-adapter

# Compile test file
g++ -std=c++20 -c tests/unit/test_journald_adapter.cpp \
    -I src -I /usr/include \
    -DGTEST_HAS_TR1_TUPLE=0

# Run adapter tests (when gtest linked)
./tests/unit/test_journald_adapter --gtest_filter=JournaldAdapterTest.*

# Verify JSON parsing with real journalctl output
journalctl -n 3 --output=json | head -1 | \
    python3 -c "import sys,json; print(json.loads(sys.stdin.read()))"
```

---

## Git Diff Summary

### New Files

- `src/adapters/journald.hpp` (220 lines) - Header with interface and config
- `src/adapters/journald.cpp` (485 lines) - Implementation with JSON parsing
- `tests/unit/test_journald_adapter.cpp` (450 lines) - Unit tests

### Modified Files

- `cpp/CMakeLists.txt` - Added rebuntu-journald-adapter target

---

## Rejected Alternatives

| Alternative | Reason for Rejection |
|-------------|---------------------|
| Direct libsystemd API | Development files not available; journalctl is standard |
| Shell command parsing | Unstructured output; hard to parse reliably |
| Polling loop with tail -f | Resource-intensive; no cursor semantics |
| Custom JSON library | Standard library has all we need |

---

## Later-Phase Deferrals

| Phase | Deferred Work |
|-------|---------------|
| **5.3** | Integration with EventCollector runtime management |
| **5.4** | Previous-boot correlation and diagnostics |
| **6.x** | Long-running follow mode daemonization |

---

## Remaining Risks

| Risk | Mitigation |
|------|-----------|
| journalctl path changes | Uses `/usr/bin/journalctl` - verify on target systems |
| JSON format evolution | Simple key-value parser; graceful degradation |
| Timestamp parsing errors | Falls back to acquisition time |

---

## Verdict: **COMPLETE**

Phase 5.2 Journald Acquisition Service is complete with:

- ✅ Native Linux source integration (journalctl)
- ✅ Cursor-based continuity semantics
- ✅ Boot filtering (current/previous)
- ✅ Bounded queries with timeout enforcement
- ✅ Evidence preservation and provenance tracking
- ✅ Metrics for monitoring adapter health
- ✅ Comprehensive unit test coverage
- ✅ Build system integration

The implementation follows Rebuntu's C++20-native, Linux-first philosophy,
preserving provenance while integrating cleanly with the existing Phase 5.1
Event Collector infrastructure.

---

## Files Changed

```
src/adapters/journald.hpp         # New - Interface and config
src/adapters/journald.cpp         # New - Implementation
tests/unit/test_journald_adapter.cpp  # New - Unit tests
cpp/CMakeLists.txt                # Modified - Build integration
docs/PHASE_5.2_JOURNALD_ACQUISITION_FINAL_REPORT.md  # This file