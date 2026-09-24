# Phase 0.20 Deferred Work Ledger

## Work Intentionally Deferred to Later Phases

### Phase 1-3: Foundation
- Full production execution runtime (Phase 4) - infrastructure exists, not yet fully deployed
- Foundational monitoring services (Phase 5) - observation contracts exist, full implementation deferred
- Complete shell language (Phase 6) - shell integration contracts established
- Unified observation framework (Phase 7) - event/observation contracts defined
- Production event/assertion runtime (Phase 8) - runtime contracts present
- Production automation runtime (Phase 9) - automation contracts exist
- Production workflow runtime (Phase 10) - workflow contracts exist

### Phase 4: Runtime
- Complete runtime implementation across all domains
- Full provider registry with dynamic discovery
- Advanced scheduling policies beyond basic RetryPolicy/TimeoutPolicy

### Phase 5-6: Observation & Shell
- Production monitoring services
- Complete shell language grammar and parser
- Full operator interface (CLI/Gui)

### Phase 7-8: Events & Automation
- Production event runtime infrastructure
- Assertion engine for verification
- Full automation execution engine

### Phase 9-10: Workflows & Domain Logic
- Production workflow runtime
- Complete domain implementations (filesystem, package, service management)
- Native Linux integration providers

### Phase 11-13: Profiles, Resilience, Security
- Full profiles system
- Resilience/recovery infrastructure
- Complete security system (policy, authorization, audit)

### Phase 14-19: Advanced Features
- Resource control (cgroups, limits)
- Environment/device coordination
- Maintenance operations
- Semantic administration
- Controlled capability extension
- Reconciliation systems

## Unimplemented but Contractually Defined

| Concept | Status |
|---------|--------|
| OperationRegistry full implementation | Deferred to Phase 10+ |
| ComponentRegistry population | Deferred to later phases |
| ServiceRegistry population | Deferred to domain implementation |
| Full provider discovery system | Deferred to runtime phase |

## Notes on Deferment Criteria

Work is deferred when:
1. The contract/interface exists but implementation has no current consumers
2. Native Linux mechanisms provide sufficient functionality
3. Consumer demand justifies deferring to later phases
4. Implementation depends on earlier phases' foundational work