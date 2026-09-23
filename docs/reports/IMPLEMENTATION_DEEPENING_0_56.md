# Implementation deepening — phases 0–56

This pass replaces generic phase-shaped coverage with reusable runtime semantics in the canonical `src/rebuntu` tree.

Implemented:
- canonical evidence/entity/desired-state/native-operation/plan/verification types;
- narrow systemd provider boundary (systemd remains native authority);
- service semantic controller: observe, plan, verify, reconcile;
- generic closed-loop reconciler for observe→plan→apply→re-observe→verify;
- typed operation policy gate;
- executable service reconciliation test with a fake provider.

Architectural rule: Rebuntu does not reproduce service lifecycle mechanics. It reasons about desired service state and delegates lifecycle operations to systemd through a narrow provider.
