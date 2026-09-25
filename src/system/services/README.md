# rebuntu::system::services — Foundational Services Framework (Phase 5.0)

## Overview

This module establishes the foundational contracts for Rebuntu's service framework. It provides common abstractions that all Phase 5+ services can use without creating a parallel runtime or microservice platform.

## Design Philosophy

- **Service = Managed functionality** with lifecycle, health, interface, availability
- **Service ≠ Daemon** (process/runtime characteristic)
- **Service ≠ systemd unit** (deployment mechanism)  
- Services are composed into one Rebuntu runtime, not isolated processes
- Use native Linux mechanisms; don't emulate them

## Key Distinctions

| Dimension | Purpose |
|-----------|---------|
| `LifecycleState` | Stage of existence (created → failed) |
| `WorkState` | What it's doing now (idle, processing, waiting, paused, jammed) |
| `ControlState` | Admin status (enabled, disabled, paused, frozen, locked) |
| `ReadinessState` | Can accept work (ready, not_ready) |
| `HealthState` | Sustained quality (unknown, healthy, degraded, unhealthy) |

## Service Lifecycle

```
created → initializing → ready → active → stopping → stopped/failed
```

## Backpressure & Resource Management

- All services have bounded queues with explicit backpressure policy
- Cancellation is cooperative via CancellationToken
- Shutdown has timeout enforcement and forced termination fallback

## Architecture

### ServiceBase

Abstract base class that provides:
- Lifecycle management (created → initializing → ready → active → stopping → stopped/failed)
- Evidence publication interface
- Metrics collection
- Configuration interface

### ServiceConfig

Typed configuration for services at construction time, including:
- Service identity
- Backpressure policy
- Resource budget (max queue size, max concurrent tasks)
- Health check interval
- Cancellation behavior

### ServiceBuilder

Fluent builder pattern for configuring ServiceBase instances with optional parameters.

### EvidencePublisher

Interface for services to publish observations/evidence that can be consumed by monitoring, logging, and alerting systems.

### Observation

Evidence-backed statement about the system containing:
- Identity (unique ID)
- Timestamp
- Domain (e.g., "health", "queue_depth")
- Key-value data
- Source/provenance
- Quality indicators

## Backpressure Policy

| Policy | Behavior |
|--------|----------|
| `kBlock` | Block sender until space is available |
| `kDropNewest` | Drop newest message when queue is full |
| `kDropOldest` | Drop oldest message to make room for newest |

## Implementation Notes

- Services are NOT microservices - they don't have their own process lifecycle
- systemd owns the native service lifecycle; Rebuntu services integrate with it
- No duplicate functionality - use existing Phase 4 runtime capabilities
- Evidence is first-class; never mutate raw observations

## Files

| File | Purpose |
|------|---------|
| `contracts.hpp` | Header with type definitions and interfaces |
| `contracts.cpp` | Implementation of base classes |

## Future Work (Phase 5.x)

Later phases will implement:
- Health monitoring service
- Queue depth monitoring service  
- Log aggregation service
- Metrics collection service

Each will reuse the common ServiceBase foundation.

## See Also

- Phase 0: Core contracts (SemanticStatus, Error, Outcome)
- Phase 4: Runtime (Engine, Cancellation, Shutdown)
- Phase 5.x: Specific services building on this framework