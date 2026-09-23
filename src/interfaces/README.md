# src/interfaces/ — typed contracts and protocol interfaces

This directory contains Rebuntu's typed interface definitions: protocols,
contracts, IPC schemas, and message formats. Interfaces are *static*—they
declare contracts but contain no runtime implementation.

## Categories

| Subdirectory | Responsibility |
|---|---|
| `cli/` | Command-line interface contracts (commands, options, output formats) |
| `ipc/` | Inter-process communication protocols and message types |
| `api/` | HTTP/gRPC API definitions (requests/responses, errors, schemas) |
| `shell/` | Shell-facing command contracts (parsing, IR, intent) |

## Principles

- **No implementation**: interfaces declare *what*, not *how*.
- **No dependencies on consumers**: an interface may be depended upon but must
  not depend on code that consumes it.
- **Stable identifiers**: interface versions and message types are versioned
  contracts, not arbitrary structures.

Status: PREPARED (Phase 0.1 infrastructure). No interfaces defined yet.