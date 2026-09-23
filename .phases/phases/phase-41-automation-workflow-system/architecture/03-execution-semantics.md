# Execution Semantics
Separate definition, validated plan, run, node attempt and action execution. Persist transitions durably. Restart/recovery must be deterministic. Never claim exactly-once external effects; use idempotency keys, deduplication, reconciliation and domain verification.
