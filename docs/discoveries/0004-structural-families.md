# 0004 — Structural families: interfaces, adapters, support

- phase: 0.1
- disposition: **ACCEPTED**
- observation: Phase 0.0 established SYSTEM/MODULE/UNIT taxonomy but lacks first-class
  structural areas for cross-cutting concerns.
- evidence: Rebuntu's architecture separates *what* (structural type) from *how*
  (implementation pattern). Cross-cutting mechanisms (interfaces, adapters,
  support utilities) appear throughout the system but were not encoded as
  primary directories.
- decision: Add three additional structural families under `src/`:
    - `src/interfaces/` — typed contracts, protocol definitions, IPC interfaces
    - `src/adapters/` — native/external mechanism integration (systemd, procfs,
      D-Bus, shell commands)
    - `src/support/` — reusable utilities (logging, configuration, validation,
      serialization)
- rationale: These are *structural* categories with distinct semantics:
    interfaces expose contracts; adapters isolate mechanisms; support provides
    utilities. They cut across modules but deserve first-class structure.
- reconsideration trigger: if a different organization (e.g., module-local
  adapters) proves more coherent.