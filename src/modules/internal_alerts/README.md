# rebuntu::modules::internal_alerts — Internal Alert Service (Phase 5.14)

This module implements Rebuntu's canonical internal alert service.

## Purpose

Internal alerts are structured operational signals generated from evidence-backed conditions.
They feed later reporting, automation, and recovery phases.

**Key Distinction:** Internal alerts ≠ user notifications. They are:
- Not human-facing panic messages
- Structured reductions of facts/assertions/conditions
- Deduplicatable and correlatable
- Stateful where necessary
- Evidence-linked with severity-awareness without fake numeric precision

## Alert Lifecycle

```
OPEN → UPDATED → ACKNOWLEDGED → CLEARED → CLOSED
```

### States

| State | Description |
|-------|-------------|
| kOpen | Condition is currently satisfied, needs attention |
| kUpdated | Recurrence of same condition (within deduplication window) |
| kAcknowledged | Human/automation has seen this alert |
| kCleared | Condition no longer satisfied |
| kClosed | Lifecycle complete (retention period passed) |

## Deduplication

Alerts with the same `dedupe_key` (category + subject_type + subject_id) are deduplicated
within a configurable time window to prevent alert storms while preserving recurrence
detection after clear.

## Correlation

Related alerts (same subject, close in time) are tracked together without merging.
This enables understanding context without losing individual identity.

## Evidence Linkage

Each alert carries provenance-bearing evidence:
- Direct cause
- Contributing factors  
- Corroborating signals
- Contextual information

## Configuration

### DeduplicationConfig
- `deduplication_window`: How long to wait before treating recurrence as new
- `max_occurrences_per_dedupe_key`: Maximum occurrences to track
- `retention_after_clear`: How long to keep alerts after clearing

### CorrelationConfig
- `correlation_window`: Temporal window for correlating related alerts
- `max_correlated_per_alert`: Maximum correlated alerts per alert
- `correlate_by_subject`: Whether to correlate by subject
- `correlate_by_time`: Whether to correlate by time window

## API

```cpp
std::unique_ptr<AlertProcessor> make_alert_processor();

class AlertProcessor {
    core::Outcome configure(
        const AlertDeduplicationConfig&,
        const AlertCorrelationConfig&);
    
    core::Outcome start();
    core::Outcome stop();
    bool is_running() const;
    
    AlertResult process_event(
        const runtime::Event&,
        const std::vector<core::Evidence>&);
    
    AlertResult create_or_update_alert(...);
    
    core::Outcome acknowledge_alert(const std::string& alert_id);
    core::Outcome clear_alert(const std::string& alert_id);
    
    std::vector<InternalAlert> get_alerts(
        std::optional<AlertState> = std::nullopt,
        std::optional<SeverityCategory> = std::nullopt,
        std::optional<AlertCategory> = std::nullopt);
    
    AlertMetrics metrics() const;
};
```

## Severity Categories (Qualitative, not numeric)

| Category | Description |
|----------|-------------|
| kInfo | Informational only |
| kLow | Minor issue |
| kMedium | Noticeable issue |
| kHigh | Significant issue |
| kCritical | Critical failure |

## Alert Categories

- ServiceFailure: Service entered failed state or crash loop
- ResourceExhaustion: Resource limit exceeded (memory, CPU, disk)
- HealthDegradation: Component health degraded but not failed
- PerformanceIssue: Performance below acceptable threshold
- SecurityEvent: Security-relevant event
- ConfigurationDrift: Configuration deviated from expected state
- HardwareFault: Hardware fault or predicted failure
- SystemEvent: System-level event (reboot, crash, panic)

## Implementation Notes

- Thread-safe with mutex protection
- Metrics available via `metrics()` call
- Evidence always preserved (provenance-bearing observations)
- No automatic recovery actions (monitoring only, no repair)