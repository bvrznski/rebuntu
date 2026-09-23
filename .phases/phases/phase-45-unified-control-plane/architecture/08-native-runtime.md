# Native Runtime Contract

The deterministic control plane is C++-first under canonical architecture-first `src/`. Runtime/state/concurrency/eventing/IPC/privilege/control logic must not fall back to a Python-owned parallel plane.

Python remains only at explicit semantic/ML, research/experimental or narrow justified interoperability boundaries.
