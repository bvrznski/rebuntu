# Provider Contract

Domain systems expose search through a common native provider interface describing capabilities, fields, filters, projections, freshness, cost and cancellation.

Providers return typed result envelopes and evidence refs. They remain owners of their data. Phase 40 may maintain derived indexes only when the persistence/freshness policy explicitly permits it.

Provider timeout/failure produces partial-search metadata, not an empty successful result set.
