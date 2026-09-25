# events

Events subsystem — Event, Signal, Request, Response types and Channel implementations.

This subsystem implements Rebuntu's communication grammar independently of transport
mechanism. Types are transport-agnostic; implementations may use in-process calls,
file descriptors, Unix sockets, or D-Bus as appropriate.

Architecture:
  - Event: immutable statement that something occurred (e.g., device plugged in)
  - Request: semantic ask for action (e.g., "start service X")
  - Response: reply to a Request
  - Message: transport-neutral envelope carrying typed payload
  - Signal: lightweight control indication (pause/resume/cancel)

Types are defined in `src/system/runtime/contracts.hpp` and `src/runtime/contracts.hpp`.

## Phase 0.15 — Communication Grammar

This phase establishes:
  - Channel interface for sending/receiving messages
  - In-memory channel implementation (`InMemoryChannel`)
  - Backpressure policies for bounded queues
  - Message correlation IDs (request_id, correlation_id, causation_id)

## Phase 4.16 — Native Event Activation Engine

This phase adds event-driven activation without polling-first architecture:

### Components

#### Trigger Registry (`TriggerRegistry`)
- Stores automation definitions with conditions and filters
- Enables registering/disabling triggers by ID
- Queries matching triggers for given events

#### Deduplication Cache (`DeduplicationCache`)
- Tracks recent activations within a time window
- Prevents duplicate work from repeated events (e.g., udev storm)
- Automatic cleanup of expired entries

#### Event Matcher (`EventMatcher`)
- Evaluates whether an event matches a trigger's criteria
- Checks source/type filters and condition evaluation
- Returns match result with decision (Allow/Suppress/Coalesce/Defer/Reject)

#### Activation Engine (`ActivationEngine`)
- Main entry point for processing events through the activation pipeline
- Handles deduplication, authorization checks, and backpressure
- Produces `ActivationRecord` with full provenance when activations occur

### Key Types

```cpp
struct TriggerDefinition {
    std::string id;
    std::optional<std::string> source_filter;   // e.g., "udev", "systemd"
    std::optional<std::string> type_filter;     // event type pattern
    runtime::Condition condition;               // activation trigger condition
    std::optional<std::string> target_kind;     // "task" or "workflow"
    std::optional<std::string> target_id;
};

struct ActivationRecord {
    ActivationId id;                            // unique activation identity
    std::chrono::system_clock::time_point created_at;
    std::string source_event_id;                // original event that triggered this
    std::string trigger_id;                     // which automation fired
    std::optional<std::string> target_kind;     // what will be executed
};

enum class ActivationDecision {
    kAllow,       // activation proceeds
    kSuppress,    // suppressed by policy (cooldown, concurrent)
    kCoalesce,    // deduplicated with existing activation
    kDefer,       // deferred for later processing
    kReject       // rejected by authorization/policy
};
```

### Event-to-Activation Flow

```
Native Linux Events
     ↓
[event source: udev/systemd/inotify/...]
     ↓
Event → normalized Event/Fact → TriggerRegistry
                                    ↓
                         find_matching_triggers(event)
                                    ↓
                              [for each match:]
                                    ↓
                        EventMatcher.match(trigger, event)
                                    ↓
                    [condition evaluated + filters checked]
                                    ↓
                             DeduplicationCache
                                    ↓
                       is_duplicate(key)? → Suppress/Coalesce
                                    ↓
                                  Allow?
                                    ↓
                            ActivationRecord created
                                    ↓
                         Evidence collected (provenance)
                                    ↓
                          Typed work request ready
```

### Usage Example

```cpp
// Create activation engine with default settings
auto engine = rebuntu::events::make_activation_engine();

// Register a trigger for udev device-added events
rebuntu::TriggerDefinition trigger;
trigger.id = "device-attached";
trigger.source_filter = "udev";
trigger.type_filter = "device-added";
trigger.condition.lhs.path = "device.exists";
trigger.condition.op = runtime::ConditionOperator::kExists;
trigger.target_kind = "task";
trigger.target_id = "mount-device";

engine->register_trigger(trigger);

// Process an event
rebuntu::runtime::Event event;
event.id = "evt-123";
event.source = "udev";
event.type = "device-added";

auto result = engine->process_event(event);

if (result.decision == ActivationDecision::kAllow) {
    // Execute the activated work using runtime infrastructure
}
```

### Backpressure

The engine implements backpressure through:
- Configurable window for deduplication cache
- Batch processing limits (`max_batch_size` parameter)
- Metrics tracking for monitoring activation rates

### Native Linux Integration

This phase is designed to integrate with existing native event sources:

| Source | Mechanism | Example Events |
|--------|-----------|----------------|
| udev | netlink socket | device-added, device-removed |
| systemd | D-Bus signals | service-started, unit-failed |
| inotify | filesystem events | file-created, directory-changed |

### Status: IMPLEMENTING

Phase 4.16 establishes the foundation for event-driven activation.
Full integration with native Linux event sources is completed.