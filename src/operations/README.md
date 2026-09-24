# Rebuntu Operations (Phase 0.10)

## Overview

This directory contains Rebuntu's canonical Operation implementations.

An **Operation** is a reusable, explicitly contracted system capability that:
- Observes, queries, changes, constructs, removes, transforms, or controls system state
- Has typed inputs and outputs
- Documents preconditions (must hold before execution)
- Documents expected effects and postconditions (must hold for success verification)
- Provides verification strategy (how success is independently confirmed)
- Carries Evidence supporting the result

## Directory Structure

Operations are organized by domain:

```
src/operations/
├── filesystem/      # Filesystem operations (copy, move, delete, verify)
├── service/         # Service lifecycle operations (start, stop, restart, status)
├── package/         # Package management operations (install, remove, update)
├── storage/         # Storage operations (mount, umount, format)
└── system/          # System-level operations (hostname, uptime, health check)
```

## Operation Contract

See `src/runtime/core/contracts.hpp` for the canonical Operation contract definitions:

- **OperationDefinition**: Full contract metadata including preconditions, postconditions
- **OperationRequest**: Concrete execution request with parameters
- **OperationResult**: Result with status, verification, evidence
- **SideEffectKind**: NONE, OBSERVATION, MUTATING, PRIVILEGED, DESTRUCTIVE
- **Idempotency**: IDEMPOTENT, CONDITIONALLY_IDEMPOTENT, NON_IDEMPOTENT, UNKNOWN
- **Reversibility**: REVERSIBLE, CONDITIONALLY_REVERSIBLE, IRREVERSIBLE, UNKNOWN

## Architecture

```
Operation (contract)
    ↓
Concrete Implementation
    ↓
Executor/Provider
    ↓
Native Linux Mechanism (systemd, procfs, D-Bus, etc.)
```

## Execution Flow

```
DISCOVER
    ↓
RESOLVE TARGET
    ↓
OBSERVE CURRENT STATE
    ↓
EVALUATE PRECONDITIONS
    ↓
PLAN (if mutating)
    ↓
EXECUTE
    ↓
OBSERVE RESULTING STATE
    ↓
VERIFY POSTCONDITIONS
    ↓
GENERATE EVIDENCE
    ↓
RESULT
```

## Implementation Requirements

1. Operations must use typed inputs/outputs (no shell command strings)
2. Precondition failure should be detected before mutation
3. Verification must be independent from execution success
4. Evidence must carry provenance information
5. Idempotency/reversibility metadata must be accurate