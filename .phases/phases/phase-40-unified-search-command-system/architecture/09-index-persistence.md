# Index & Persistence Policy

Prefer authoritative live provider queries where latency permits. Persistent indexes are derived acceleration structures, never shadow authorities.

Every persisted index declares source, schema version, generation/freshness, invalidation strategy, rebuild path and sensitive-field policy. Index loss must be recoverable by rebuild without losing authoritative system state.
