# Placement and Resource Semantics

Phase 51 integrates Phase 29 workload and Phase 30 resource models across nodes.

Placement reasons over required capabilities, CPU/RAM/GPU/VRAM, topology, data locality, accelerator identity, reservations, contention, affinity/anti-affinity, operator policy, health and freshness.

Never hard-code GPU indices or assume homogeneous nodes.

Placement recommendation != authorization.
