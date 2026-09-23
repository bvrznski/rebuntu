# src/system/deferred — Deferred Implementations

Implementations that are documented but not yet part of the active Phase 0.1 structure.

## Premature Implementations (Deferred)

The following files were found in `src/system/` with implementation content that belongs to later phases:

| File | Claimed Phase | Reason for Deferral |
|------|--------------|---------------------|
| runtime/controller.cpp | 4.6 | Runtime controller subsystem - deferred until operational architecture phase |
| runtime/discovery.cpp | 4.x | Discovery infrastructure - deferred until runtime phase |
| runtime/dispatcher.cpp | 4.x | Command dispatcher - deferred until operational architecture phase |
| runtime/engine.cpp | 4.2 | Runtime engine - deferred until operational architecture phase |
| runtime/executor.cpp | 4.x | Execution subsystem - deferred until operational architecture phase |
| runtime/initialization.cpp | 4.x | Initialization logic - deferred until runtime phase |
| runtime/runner.cpp | 4.x | Execution runner - deferred until operational architecture phase |
| state/provider_*.cpp | 4.x | Native state providers - deferred until state management phase |

## Deferral Rationale

Per Phase 0.1 structural taxonomy expansion:
- **Phase 0.0** established repository structure and skeleton
- **Phase 0.1** expands formalizes the structural taxonomy (SYSTEM/MODULE/UNIT/INTERFACE/ADAPTER/SUPPORT)
- **Phase 0.2+** implements operational architecture

Implementations claiming Phase 4.x belong in their respective phases, not in Phase 0.1 structural expansion.

## Re-instatement Criteria

These implementations may be re-instated when:
1. The corresponding phase is actively being implemented
2. CMakeLists.txt files are updated to include these sources
3. Tests exist for the functionality
4. Documentation matches the implementation level

See: docs/discoveries/0005-operational-grammar.md