# Failure, Consistency and Reconciliation

Networks partition. Nodes disappear. Messages duplicate, reorder and arrive late. Clocks differ.

Do not claim exactly-once execution.

Use explicit operation/task identities, idempotency where possible, leases where appropriate, bounded retries, durable state, reconciliation and explicit UNKNOWN/INDETERMINATE outcomes.

A coordinator losing contact must not reinterpret unknown remote execution as failure or success.
