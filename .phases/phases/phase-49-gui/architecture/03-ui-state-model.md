# UI State Model

Distinguish authoritative system state, observed snapshot, derived presentation state, pending plan, authorization state, execution progress, verification result and historical state.

The GUI must never make stale cached UI state appear authoritative. UNKNOWN, stale, partial, degraded and unavailable states require explicit representation.
