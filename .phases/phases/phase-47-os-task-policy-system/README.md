# Rebuntu Phase 47 — OS Task Policy System

Complete executable specification.

Phase 47 provides a common deterministic policy layer for operating-system tasks originating from humans, `ask`, workflows, automations, services and agents.

Canonical lifecycle:

`request → normalize → contextualize → classify → policy evaluate → plan → re-evaluate → authorize → execute → verify → outcome → record`

Core rule:

**A task's origin, context, capability composition, data-flow effects and delegated authority are part of the policy decision.**

A task is not a shell command. Policy is not arbitrary executable code. Model advice is not authority. Missing context is not permission.

Read `AGENT_HANDOFF.md`, `INDEX.md`, every architecture document and all numbered prompts. Finish only after recursive fixed-point rediscovery and adversarial closure.
