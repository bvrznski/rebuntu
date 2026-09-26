# rebuntu::modules::reporting — Reporting & Notification Service (Phase 5.15)

## Overview

The reporting module implements Rebuntu's canonical reporting and notification service that:
- Transforms verified diagnostic/stability information into useful human-readable reports
- Separates internal alert state from presentation/delivery
- Provides pluggable notification delivery mechanisms with rate limiting

## Architecture

```
Assessment → Report → Renderer → Delivery/Notification
    ↑              ↓           ↓
Internal Alerts  Reports     Notifications
```

### Key Distinctions

| Concept | Description |
|---------|-------------|
| **Alert** | Internal signal from evidence-backed conditions (no UI, no human-facing panic messages) |
| **Report** | Structured diagnostic assessment with evidence, timeline, uncertainty, recommendations |
| **Notification** | Bounded delivery of reports via pluggable mechanisms (log, D-Bus, file, webhook) |
| **Renderer** | Converts report objects to different formats (human-readable, JSON) |

## Data Model

### Report Types
- `kDiagnostic` — Diagnostic snapshot with timeline and evidence
- `kAlertSummary` — Summary of active alerts with correlation
- `kIncidentReport` — Incident assessment with causal analysis
- `kHealthSnapshot` — Current system health status
- `kPeriodic` — Regular scheduled status report

### Notification Destinations
- `kLog` — Write to system log (journald)
- `kDBus` — Send via D-Bus signal
- `kStdout` — Print to stdout (for CLI tools)
- `kFile` — Write to file
- `kWebhook` — HTTP webhook delivery

## Features

### Report Generation
- Evidence-backed summary with overview and recommendations
- Timeline of events with timestamps and subjects
- Causal analysis with hypotheses and alternative explanations
- Impact assessment on subsystems
- Uncertainty notes where evidence is incomplete

### Notification Delivery
- Rate limiting per destination (per-minute, per-hour, daily)
- Deduplication of identical content within windows
- Per-destination configuration
- Success/failure tracking and metrics

## Usage

```cpp
#include <modules/reporting/generator.hpp>
#include <modules/reporting/types.hpp>

using namespace rebuntu::modules::reporting;

// Create generator with options
ReportGeneratorOptions options;
options.rate_limits.max_notifications_per_window = 100;
options.delivery_configs.push_back({
    .destination = NotificationDestination::kLog,
    .enabled = true,
});

auto generator = make_report_generator();
generator->configure(options);
generator->start();

// Generate a report
AssessmentSummary summary;
summary.overview = "Service failed due to resource exhaustion";

std::vector<core::Evidence> evidence = { /* ... */ };

auto report = generator->generate_report(
    ReportKind::kIncidentReport,
    summary,
    evidence,
    std::chrono::system_clock::now()
);

if (report) {
    // Render for human consumption
    auto renderer = make_report_renderer();
    std::cout << renderer->render_human(*report);
    
    // Send notification
    Notification notification;
    // ... populate notification ...
    auto result = generator->send_notification(notification);
}
```

## Rate Limiting

Rate limiting is configurable per destination:
```cpp
NotificationRateLimitConfig config;
config.max_notifications_per_window = 100;  // Per window
config.window_size_minutes = 1;             // 1 minute
config.deduplicate_identical_content = true;
config.deduplication_window_minutes = 5;
```

## Metrics

```cpp
ReportGeneratorMetrics metrics = generator->metrics();
// reports_generated: Total reports created
// notifications_sent: Successfully delivered notifications
// notifications_failed: Failed delivery attempts
// notifications_suppressed: Suppressed due to rate limiting
```

## Testing

Tests verify:
- Report generation from assessment data
- Renderer output (human-readable and JSON)
- Notification rate limiting
- Deduplication within time windows
- Metrics tracking

## Integration Points

The reporting module integrates with:
- **Phase 5.14 internal_alerts**: Receives alerts and generates reports
- **Phase 5.12 evidence_collector**: Uses collected evidence in reports
- **Phase 0 contracts**: Uses core::Evidence, Outcome types

## Implementation Notes

- Reports never contain actual secret material (only references)
- Causal analysis distinguishes between observations, correlations, and hypotheses
- Rate limiting prevents notification storms while preserving important events
- Renderers preserve raw evidence while providing human-readable summaries