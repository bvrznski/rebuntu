# Phase 40 System Boundary

Phase 40 is the unified **discovery + query + command-intent plane**.

```text
                       Human / Agent-safe client
                               |
                      CLI / Fish / Panel / API
                               |
                +--------------+--------------+
                |                             |
          Unified Search                 Command Plane
                |                             |
          Query AST/Plan              Typed CommandIntent
                |                             |
         Federated Providers          Registry / applicability
                |                             |
     +----------+-----------+           Plan handoff
     |          |           |                 |
 domain systems Phase 39  indexes       domain owner
     |          |           |                 |
 authoritative state/evidence       validate/authorize/execute
```

Phase 40 does not become a universal database and does not own domain mutations.
