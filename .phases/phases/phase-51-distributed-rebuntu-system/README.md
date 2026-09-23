# Rebuntu Phase 51 — Distributed Rebuntu System

Phase 51 turns multiple Rebuntu nodes in one administrative domain into one coherent distributed fabric by extending the existing Task, Context, Policy, Capability, Timeline, Knowledge Graph, Workflow and Control Plane architectures.

```text
                    REBUNTU FABRIC
                         |
          +--------------+--------------+
          |              |              |
        node A          node B         node C
          |              |              |
    local domains   local domains   local domains
          \              |              /
           \------ typed fabric --------/
                         |
              placement / coordination
                         |
              Phase 45 authority path
```

Hard invariants:

- Distributed Rebuntu is not SSH orchestration.
- No arbitrary remote shell authority.
- `hostname != identity`; `IP != identity`.
- `reachability != membership`; `membership != authorization`.
- Target nodes revalidate consequential work locally.
- Placement does not grant authority.
- Remote observations carry provenance and freshness.
- Network partitions and indeterminate outcomes are first-class.
- Never claim exactly-once execution.
- Phase 39/40/41/42/43/44/45/46/47/48/49/50 ownership remains intact.
- C++ owns deterministic distributed machinery.
- Phase 52 cross-owner association/federation remains a future boundary.

Read `AGENT_HANDOFF.md`, `INDEX.md`, all architecture files and every numbered prompt.
