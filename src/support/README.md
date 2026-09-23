# src/support/ — reusable utilities

Support modules provide cross-cutting, non-semantic functionality: logging,
configuration, validation, serialization, and common algorithms.

## Categories

| Subdirectory | Responsibility |
|---|---|
| `logging/` | structured log emission, sinks, formatting |
| `config/` | configuration parsing, resolution, validation |
| `validation/` | input/value validation (types, ranges, schemas) |
| `serialization/` | JSON/YAML/TOML encoding and decoding |
| `algorithms/` | generic algorithms used across modules |

## Principles

- **Stateless or minimal state**: support utilities avoid becoming stateful
  singletons.
- **No dependency on Rebuntu semantics**: they may depend on contracts but not
  on high-level domain concepts.
- **Testable in isolation**: every utility should be unit-testable without
  mocking the entire Rebuntu ecosystem.

Status: PREPARED (Phase 0.1 infrastructure). No support modules defined yet.