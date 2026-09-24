# Phase 0.20 Rejected Patterns Ledger

## Patterns That Were Considered and Rejected

### Giant Manager Objects
**Rejected because:** Violates single responsibility principle and creates tight coupling. Rebuntu uses composition over inheritance.

### Custom Init/Supervisor
**Rejected because:** systemd already provides process lifecycle management. Native mechanisms should be used rather than reimplementing them.

### Generic Message Broker
**Rejected because:** Native IPC mechanisms (Unix sockets, D-Bus) are sufficient for Rebuntu's needs. A universal bus adds unnecessary complexity.

### Marker Files as Process Truth
**Rejected because:** Process state is owned by the kernel/systemd. Using marker files creates shadow state that can become inconsistent with actual system state.

### Arbitrary Root Executor
**Rejected because:** Privilege escalation must go through proper authorization channels (sudo policy, polkit). Arbitrary root execution bypasses security boundaries.

### LLM -> sudo bash Pattern
**Rejected because:** Model output is UNTRUSTED input. It should never directly become privileged shell commands. All model-generated text must pass through:
- Parse → Validate → Provenance → Context → Capability → Policy → Authorization → Typed Operation

### Universal State Enum
**Rejected because:** Multiple orthogonal state dimensions exist (lifecycle, work, control, readiness, health, recovery). A single enum collapses distinct concerns.

### Universal BaseSpec
**Rejected because:** Different entities have different specification requirements. Generic specs lose semantic precision.

### Directories for Every Noun
**Rejected because:** Structural directories encode *what kind of thing* something is (System/Module/Unit), not every concept. Roles are metadata, not directory names.

### Process per Semantic Role
**Rejected because:** Semantic modularity ≠ process modularity. Too many processes create IPC overhead and complexity.

### Polling Where Native Events Exist
**Rejected because:** Linux provides inotify/fanotify for filesystem events, udev/netlink for device events, signalfd/pidfd for signals. Polling wastes CPU and creates race conditions.

### Hidden Retries
**Rejected because:** Retry behavior should be explicit via RetryPolicy with configurable backoff. Silent retries hide failures and create debugging difficulty.

### Fake Rollback
**Rejected because:** Rollback must be a real recovery mechanism (actual undo operation or checkpoint restore). Marking something "rollbackable" without actual implementation is dangerous.

### Fake Exactly-Once Delivery
**Rejected because:** True exactly-once requires idempotent operations with proper deduplication. Claiming exactly-once without evidence of idempotency is incorrect.

## Patterns That Were Verified as Appropriate

| Pattern | Status |
|---------|--------|
| C++20 native implementation | ✅ APPROVED |
| Linux native mechanisms (systemd, D-Bus, procfs) | ✅ PREFERRED |
| Typed Result/Evidence models | ✅ REQUIRED |
| Contract-based interfaces | ✅ REQUIRED |
| Orthogonal state dimensions | ✅ APPLIED |

## Design Principles That Were Maintained

1. **ARCHITECTURE DEFINES OWNERSHIP; LANGUAGE DOES NOT**
2. **EXECUTION SUCCESS != VERIFIED SUCCESS**
3. **UNKNOWN != FALSE != FAILED**
4. **DATA != CONTROL**
5. **SECRET MATERIAL NEVER IN EVIDENCE/ERRORS/RESULT**
6. **NATIVE LINUX FIRST**
7. **WORKING IMPLEMENTATION OVER SCAFFOLDING**