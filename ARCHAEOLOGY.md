# Rebuntu — Archaeology (Phase 0.0)

Historical Rebuntu is a **source** of terminology, problems, requirements,
design ideas, failed experiments, and useful abstractions. It is **not**
implementation authority.

## The corpus

- `.phases/PHASES/` — ~thousands of phase specification files (0.0 → 45.x),
  including `0.0.md`, `0.1.md` (structural taxonomy), `1.x` (installation /
  user definition), `2.x` (system foundation), `3.x` (semantic / BitNet /
  containers), `4.x` (core runtime & coordination), and per-domain systems
  (5.x observation, 12.x process, 31.x service, 32.x storage, 33.x network,
  36.x configuration, 37.x secrets, 39.x event timeline, 40.x–45.x
  search/automation/knowledge-graph/control-plane).
- `.phases/roadmap` — the full historical phase plan.
- `.phases/TASK`, `.phases/shell.md` — migration and shell-language material.
- `.phases/*.zip` and `.phases/PHASES/BACKUP/` — archived / backup material.

## The archaeology rules

**Status is not the same thing. Do not conflate them:**

```
IDEA EXISTS
   !=  STUB EXISTS
   !=  IMPLEMENTATION EXISTS
   !=  IMPLEMENTATION VERIFIED
   !=  PRODUCTION-WORTHY CAPABILITY
```

A historical spec describing a system does **not** mean that system exists,
works, or is desired in the current architecture.

**Preserve the problem; re-evaluate the implementation.**

When mining the corpus:
1. Extract the *problem* being solved and the *evidence* for it.
2. Re-derive the solution against the **current** architecture (C++20, native,
   the `system` package) and the current AGENTS.md invariants.
3. Record any architectural discovery in `docs/discoveries/` with a
   DISCOVERY / CANDIDATE / ACCEPTED / DEFERRED / REJECTED / SUPERSEDED
   disposition.
4. **Do not** mechanically port a historical implementation.
5. **Do not** treat a historical directory layout as the current layout.

## Terminology mining

Historical terms (Setup / Configuration / Setting / Option / Preference /
Property / Attribute / Policy; Service vs Daemon; Task vs Job vs Operation vs
Procedure; Workflow / Phase / Stage / Step; Thread; Fact / Assertion /
Condition; Health vs Readiness) are **carried into VOCABULARY.md** as
evidence-backed starting hypotheses — preserved because they express distinct
concepts, not because they are old.

## What to do with the corpus

- Use it for **vocabulary**, **problem discovery**, and **native-mechanism
  mapping** (which Linux primitive underlies each historical capability).
- Keep it **read-only**. Do not modify, clean, or "fix" the corpus in Phase
  0.0. It is a primary source.
- If a future phase re-implements a historical capability, cite the source
  phase in a discovery record.

## Disposition

Phase 0.0 **records** the corpus as HISTORICAL and establishes how to use it.
It does **not** reconstruct historical Rebuntu.

## Historical Unit Architecture (Phase 0.1 → Phase 0.7)

### Historical Concepts

Historical Rebuntu had a `Unit` concept based on:
- File-based discovery (`main.sh`, `main.py`) in specific directories
- State machine with states: `locked`, `disabled`, `inactive`, `guarded`, `active`, `stop`
- Chain relationships between Units for composed execution
- `pass/register/activate` lifecycle phases

### Translation to Phase 0.7

| Historical State/Concept | Modern Equivalent |
|--------------------------|-------------------|
| `locked` | Mutual exclusion / policy check |
| `disabled` | Configuration availability (off) |
| `inactive` | No active execution pending |
| `guarded` | Policy/precondition checks |
| `active` | Execution currently running |
| `stop` | Cancellation request |
| `pass/register/activate` | Discovery → Validation → Registration |
| `chain` | Workflow / Pipeline |

### Historical Unit → Phase 0.7 Mapping

- **Unit as executable plugin** → Deprecated
- **Unit as Task** → Deprecated (Task is now parameterized work specification)
- **Unit as process** → Process lifecycle managed by systemd/daemon, Unit is semantic contract
- **Unit as Automaton** → Merged into Workflow semantics
- **Unit as Service** → Service remains separate with availability/lifecycle
- **Unit as Script container** → Scripts remain separate; Unit may invoke Scripts

### Discovery Mechanism

| Historical | Modern |
|------------|--------|
| `main.sh` / `main.py` files in directories | ComponentRegistry with kUnit kind, stable IDs |

### Implementation Language Neutrality

Historical Rebuntu experimented with:
- SH/PY units (hybrid execution)
- Bilingual execution

The modern Phase 0.7 architecture preserves the useful principle that **Unit semantics should not depend on implementation language**, while standardizing on C++20 for authoritative runtime.

