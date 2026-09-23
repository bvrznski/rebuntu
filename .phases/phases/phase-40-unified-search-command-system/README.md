# Rebuntu — Phase 40: Unified Search & Command System

Full implementation specification for Phase 40.

**Entry point:** `40.0-unified-search-command-system-foundation.md`

Before implementation, the coding agent must discover and obey repository `AGENTS.md`, read this README, `AGENT_HANDOFF.md`, `INDEX.md`, **all `architecture/*.md`**, and the relevant numbered prompt. Architecture documents are normative.

This phase assumes the Rebuntu Native C++ Migration has established the repository's C++-first runtime policy.

## Scope

Phase 40 creates one typed, federated discovery/query plane and one typed command-intent plane across Rebuntu. It does **not** create a universal shadow database or a second mutation authority.

## Size

- 80 full numbered prompts (`40.0`–`40.79`)
- 12 normative architecture documents
