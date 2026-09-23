# 0010 — Operation contract and abstraction (Phase 0.10)

- disposition: **ACCEPTED**
- status: **CURRENT** (contracts defined, implementation pending)
- authors: Phase 0.10
- related: `0004-structural-families.md`, `0005-operational-grammar.md`

## Observation

Rebuntu needed a canonical abstraction for system capabilities that:

1. Defines WHAT can be done (semantic capability), not HOW it's implemented
2. Documents preconditions, postconditions, and verification strategy
3. Carries Evidence supporting results
4. Distinguishes between execution success and semantic verification success
5. Supports planning, dry-run, rollback, and compensation

## Decision

Introduce `Operation` as Rebuntu's canonical abstraction for system capabilities.

### Operation != Unit
- **Unit** = structural execution definition (what can be done)
- **Operation** = semantic contract describing the action

### Operation != Task
- **Task** = parameterized work specification for concrete work
- **Operation** = reusable capability definition

### Operation != Provider
- **Provider** = implementation capable of satisfying a capability
- **Operation** = semantic contract defining the capability

## Architecture

```
DISCOVER -> RESOLVE TARGET -> OBSERVE CURRENT STATE -> 
EVALUATE PRECONDITIONS -> PLAN (if mutating) -> AUTHORIZE ->
EXECUTE -> OBSERVE RESULTING STATE -> VERIFY POSTCONDITIONS ->
GENERATE EVIDENCE -> RESULT
```

## Contracts

### OperationDefinition (Phase 0.10)
The canonical contract for an Operation with fields for id, description,
preconditions, postconditions, verification strategy, side effects, etc.

### OperationRequest (Phase 0.10)
A request to execute an Operation with concrete parameters.

### OperationResult (Phase 0.10)
The result of executing an Operation including status, verification, evidence.

## Side Effect Classification
NONE, OBSERVATION, MUTATING, PRIVILEGED, DESTRUCTIVE

## Idempotency Classification  
IDEMPOTENT, CONDITIONALLY_IDEMPOTENT, NON_IDEMPOTENT, UNKNOWN

## Reversibility Classification
REVERSIBLE, CONDITIONALLY_REVERSIBLE, IRREVERSIBLE, UNKNOWN

## Files

- `cpp/include/system/core/contracts.hpp` — Operation contracts and types (CURRENT)
- `docs/discoveries/0010-operation-contract.md` — This discovery document

## See Also

- Phase 0.11: Workflows
- Phase 0.7: Unit architecture
