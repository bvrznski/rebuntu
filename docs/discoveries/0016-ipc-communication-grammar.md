# Discovery 0016 — IPC & Communication Grammar (Phase 0.15)

## Status
ACCEPTED

## Executive Summary

This discovery establishes Rebuntu's communication grammar independently of transport.

The architecture must distinguish what information means from how bytes move between processes/components.

---

## 1. Core Distinction: Semantics vs Transport

SEMANTIC TYPE -> MEANS (what information represents)
TRANSPORT MECHANISM -> BYTES (how information is delivered)

Key Principle: Semantic types must survive transport changes.

| Concept | Semantic Meaning | Possible Transports |
|---------|------------------|---------------------|
| Message | Typed envelope/payload | Unix socket, D-Bus, pipe, shared memory, in-process call |
| Event | Immutable statement something occurred | inotify, udev, systemd journal, journald |
| Request | Semantic ask for capability | D-Bus method call, Unix socket, inline call |
| Response | Reply to Request | D-Bus return, socket response, inline return |

---

## 2. Canonical Definitions

### 2.1 Message

Message is a transport-neutral communication envelope/payload.

A Message:
- Has a kind/type (event, request, response, command)
- Contains typed payload
- Carries correlation metadata (request_id, correlation_id, causation_id)
- May be serialized to JSON, CBOR, or binary format for transport

Not: A specific wire protocol. Not JSON. Not pickle.

### 2.2 Event

Event is an immutable statement that something relevant was observed to have happened.

An Event:
- Is evidence-backed (who, what, when)
- Is not necessarily a log record
- May trigger Automation
- Is NOT a request for action

Distinction: Event != Signal
- Event: "something happened" (observation)
- Signal: "do something" (control instruction)

### 2.3 Request

Request is a structured expression asking a capability/component to perform or query something.

A Request:
- Has semantic operation identifier
- Has target (subject) and parameters
- May have timeout, priority, origin
- Is NOT a shell command string

Distinction: Request != Command
- Request: abstract semantic intent (filesystem.copy)
- Command: shell representation ("cp /a /b")

### 2.4 Response

Response is communication replying to a Request.

A Response:
- Has request_id for correlation
- Has status (success, failure, unknown)
- May have value or error
- Is NOT automatically the final semantic Result

Distinction: Response != Result
- Response: IPC-level reply
- Result: semantic outcome with verification status and evidence

### 2.5 Signal

Signal is a lightweight control/notification indication.

A Signal:
- Tells component to change behavior (pause, resume, cancel, reconfigure)
- Is NOT a POSIX signal (those remain native OS mechanism)
- May be delivered via D-Bus, Unix socket, or in-process

Distinction: Signal != POSIX Signal
- Signal: Rebuntu control protocol
- SIGTERM/SIGINT: Native Linux process signals

### 2.6 Command

Command is an imperative semantic request.

A Command:
- Expresses intent to perform an action
- Is NOT a shell command string
- May be converted to Request for execution

Decision: Retain only if Command adds value beyond Request.

### 2.7 Trigger

Trigger is activation semantics, not a transport packet.

A Trigger:
- Is produced when condition evaluation yields true
- Activates Workflow/Operation
- Carries provenance (which event, which automation)

Distinction: Trigger != Event
- Event: observation ("device added")
- Trigger: decision ("start workflow for new device")

---

## 3. Transport Independence Matrix

| Use Case | Recommended Transport | Rebuntu Type |
|----------|----------------------|--------------|
| In-process call (same process) | Direct function call | Request/Response via inline |
| Local IPC (bounded host) | Unix domain socket, D-Bus | Message via IPC adapter |
| Kernel events | inotify/fanotify/udev | Event adapter -> Rebuntu Event |
| Network IPC | Not recommended by default | Only if explicitly justified |

Key Principle: Default to in-process when components live in same process.

---

## 4. Native Linux Mechanisms

| Requirement | Native Mechanism | Rebuntu Integration |
|-------------|------------------|---------------------|
| Service control | systemd D-Bus API | SystemdAdapter provides Signal/Request |
| Device events | udev netlink | UdevAdapter -> Event |
| Filesystem events | inotify/fanotify | FsEventAdapter -> Event |
| Process lifecycle | procfs, pidfd | ProcAdapter -> Event |
| Timers | systemd timers | Schedule adapter |

Do not recreate: Polling daemons when native Linux mechanisms exist.

---

## 5. Delivery Guarantees

State guarantees honestly:

| Guarantee | Description | When to use |
|-----------|-------------|-------------|
| Best effort | No retry, no persistence | Fire-and-forget events |
| At-most-once | Retry on transient failures | Idempotent operations |
| Retryable request | Client can retry safely | Read-only queries |
| Durable delivery | Store and forward | Critical state changes |

Do not claim: Exactly-once semantics (impossible to guarantee without coordination).

---

## 6. Correlation & Causation

Support multi-step activity across boundaries:

correlation_id: traces request through system
causation_id: links related events/requests
origin: who initiated the chain
timestamp: when it started

Do not require: Distributed tracing bureaucracy for local calls.

---

## 7. Schema Requirements

Durable/public IPC contracts require typed schemas:

- Message kind (event, request, response)
- Version (for compatibility)
- Typed payload
- Required fields
- Bounds validation
- Unknown-field policy
- Validation errors

Never deserialize untrusted pickle.

---

## 8. Backpressure

Streams and queues require bounded behavior:

- Bounded buffers
- Producer blocking or dropping policy
- Coalescing where appropriate
- Rejection when overwhelmed

Do not allow: Unbounded memory growth.

---

## 9. Response vs Result

Request -> IPC -> Response (transport-level)
         ->
     Parse & Validate
         ->
      Operation
         ->
    Outcome/Result (semantic with verification, evidence)

- Response: Transport envelope (did it arrive?)
- Result: Semantic outcome (was the desired state achieved?)

---

## 10. In-process vs IPC Decision

Use in-process when:
- Components are in same process
- No lifecycle isolation needed
- No privilege boundary needed
- Performance is critical

Use IPC when:
- Cross-process/isolation required
- Native mechanism available (D-Bus, Unix socket)
- Lifecycle management needed

Decision matrix:

| Factor | In-process | IPC |
|--------|-----------|-----|
| Same process? | YES | NO |
| Isolation needed? | NO | YES |
| Native mechanism? | N/A | Yes (D-Bus, socket) |
| Performance priority? | Yes | Secondary |

---

## 11. Security Considerations

For privileged IPC determine:

- Peer identity (for Unix socket, who is caller?)
- Authorization (does caller have permission?)
- Socket permissions (file mode)
- D-Bus policy (service-specific)
- Capability scope (what can this component do?)

A local socket is NOT automatically trusted.

---

## 12. Logs vs Events

- journald: Excellent for logs, can be observation source
- Do not turn every log line into semantic Event
- Normalize only records that matter to Rebuntu semantics

---

## 13. Implementation Plan (Phase 0.15)

### 13.1 C++ Contracts

Add to cpp/include/system/runtime/:

ipc.hpp              # Message envelope, Channel interface
streams.hpp          # Stream, Buffer interfaces for backpressure
channels.hpp         # Typed channel abstractions
transport.hpp        # Transport mechanism selection

### 13.2 Smallest Coherent Proof

Produce:
1. Message type with kind/payload/correlation
2. Channel interface for communication conduit
3. Stream with bounded buffer and backpressure policy
4. Buffer with droppable/coalescing policies
5. TransportSelector deciding IPC vs in-process

### 13.3 Tests

- Contract validation tests
- Channel/Stream behavior tests
- Backpressure handling tests
- Correlation ID propagation tests

---

## 14. Files to Create/Modify

| File | Action |
|------|--------|
| docs/discoveries/0016-ipc-communication-grammar.md | This discovery document |
| cpp/include/system/runtime/ipc.hpp | NEW - Message type, Channel interface |
| cpp/include/system/runtime/streams.hpp | NEW - Stream with backpressure |

---

## 15. Rejected Alternatives

### Giant Event Bus

Rejected: Universal EventBus without demonstrated consumers.

Reason: Creates unneeded indirection; in-process calls are simpler when appropriate.

### Arbitrary JSON Blobs

Rejected: Generic message payloads without schemas.

Reason: Loses type safety, validation, and documentation.

### Network Listener by Default

Rejected: Opening TCP listener for all IPC.

Reason: Unix domain socket/D-Bus sufficient for local; network adds attack surface.

---

## 16. Deferred Work

- Full D-Bus adapter (Phase 5+ after daemon architecture)
- Network IPC support (only if explicitly justified)
- Persistent message queues (Phase 6+ after state system)
- Message broker pattern (defer unless evidence justifies)

---

## 17. Native Linux Mapping Summary

| Rebuntu Concept | Native Mechanism |
|-----------------|------------------|
| Message transport | Unix domain socket, D-Bus |
| Event observation | inotify/fanotify/udev/netlink |
| Signal delivery | D-Bus signals, Unix sockets |
| Stream flow | Pipes, FIFOs (bounded) |

---

## 18. Status

**Phase 0.15 Status**: COMPLETE

The communication grammar has been established with:

- Clear semantic distinctions between Message/Event/Request/Response/Signal
- Transport independence (semantic types survive transport changes)
- In-process vs IPC decision framework
- Backpressure and bounded behavior policies
- Native Linux mechanism mapping
