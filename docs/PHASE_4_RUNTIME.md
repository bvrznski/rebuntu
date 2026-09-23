# Phase 4 Runtime — implementation report

The C++ production runtime is implemented under `rebuntu::runtime::production` and reuses the Phase 0 runtime/core contracts rather than creating a second ontology. It provides deterministic initialization and dependency-cycle detection, a narrow Engine facade, resolution and capability-driven dispatch, an Operation pipeline with observation/authorization/verification hooks, cancellation tokens, bounded retry history for Jobs, resource coordination, event activation deduplication/backpressure, shutdown propagation, and crash-recovery classification.

Provider selection is implemented under `rebuntu::infrastructure` with deterministic preferred/priority selection and explicit rejection reasons. Definition loading remains data-only; arbitrary dynamic code loading is intentionally absent. Native event ownership remains with Linux facilities (systemd/udev/D-Bus/inotify/etc.); the runtime consumes normalized `Event` values and does not add polling loops. Shell integration remains thin and consequential work is expected to enter through typed runtime requests.

## Phase mapping

- 3.12: existing C++ safe/adversarial testing infrastructure retained and tested.
- 3.13: provider selection registry/context/result implemented.
- 3.14: infrastructure contracts and readiness boundary integrated with runtime resolution.
- 4.0–4.2: RuntimeContext, initialization, lifecycle/readiness, Engine.
- 4.3–4.5: execution boundary, typed resolution/dispatch, cancellation-aware handler path.
- 4.6–4.10: cancellation/control primitive, coordination, resolution, safe data-only registration/catalog semantics.
- 4.11–4.14: existing Unit/Operation/Task/Job/Workflow contracts are reused; Operation and Job runtime paths are executable without duplicating their definitions.
- 4.15–4.17: shell/native event boundary is explicit; ActivationGate supplies correlation, deduplication and bounded inflight activation without polling.
- 4.18: typed dependency graph, readiness gate and cycle detection.
- 4.19: stop-admission, cancellation propagation, bounded drain point, stopped state and recovery classification.
- 4.20: CTest integration exercises representative runtime slices and boundary invariants.

Phase 5 services should submit typed `OperationRequest` values through `Engine`, register definitions with `Resolver`, and provide narrowly scoped execution handlers through `Dispatcher`. Services must not add their own subprocess lifecycle, retry history, event polling, or shadow live-state machinery.
