# 0003 — Roles are not directories

- phase: 0.0
- disposition: **ACCEPTED**
- observation: words like `Monitor`, `Scheduler`, `Controller`, `Engine` risk
  becoming a directory per verb/noun.
- evidence: historical `PHASES/0.1.md` §4: "Monitor is a role that a Service can
  perform rather than a structural kind of Module."
- decision: physical structure encodes strong STRUCTURAL distinctions
  (SYSTEM/MODULE/UNIT). Operational roles are represented by metadata,
  registries, or classification when justified — not by creating a directory
  per role.
- reconsideration trigger: if a role requires its own lifecycle/ownership.
