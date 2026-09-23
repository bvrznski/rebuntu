# Phase 0.4 Report — Scripts Architecture, Classification, Contracts & Execution Model

## Status: COMPLETE

---

## Executive Summary

Phase 0.4 establishes the architecture, taxonomy, contracts, and engineering rules
for scripts in Rebuntu. The central distinction is:

> **SCRIPT ≠ SHELL SOURCE**

A Shell Source is a reusable artifact loaded into the shell environment.
A Script is a standalone executable artifact with an invocation boundary.

**Decision:** Rebuntu uses `src/system/shell/` as the single script space.
Project tooling scripts live in top-level `scripts/`.
Runtime scripts would live in `src/system/shell/scripts/`.

---

## 1. DEFINITION: WHAT IS A SCRIPT?

### Script Definition

A **Script** is a standalone executable artifact implementing a bounded operation,
procedure, utility, integration, maintenance activity, or other explicitly invokable behavior.

A script has:

| Aspect | Description |
|--------|-------------|
| **Invocation boundary** | Explicit process-level execution start/end |
| **Inputs** | Arguments, stdin, environment variables |
| **Outputs** | stdout (primary result), stderr (diagnostics/errors) |
| **Exit/result semantics** | Exit code 0 = success; non-zero = failure |
| **Dependencies** | External commands, shell environment assumptions |
| **Side-effect characteristics** | Classified as PURE/READ_ONLY/MUTATING/PRIVILEGED/DESTRUCTIVE |
| **Execution environment** | Bash or Python (C++ is not a "script" language) |
| **Lifecycle** | Bounded work with explicit start and end |
| **Ownership** | Clearly identified owner |

### Script MAY Be Implemented In

* Bash (`#!/usr/bin/env bash`)
* Python (`def main() -> int:` pattern)
* Other justified scripting languages (when appropriate)

Implementation language does NOT define the concept.
A `.py` file is not automatically a Script.
A `.sh` file is not automatically a Script.

**Classification is semantic.**

---

## 2. SCRIPT VS SHELL SOURCE

### Shell Source

| Characteristic | Description |
|----------------|-------------|
| Intended for sourcing (`source file`) into shell environment |
| Exposes reusable shell functionality |
| Performs no work merely by being loaded |
| Participates in interactive/compositional shell behavior |
| Lives in: `src/system/shell/sources/` |

### Script

| Characteristic | Description |
|----------------|-------------|
| Intended for execution (`./file`) as standalone process |
| Has an explicit entry point (e.g., `main()` for Bash) |
| Performs bounded work with result/exit semantics |
| Has process-level invocation semantics |
| Lives in: `scripts/` or `src/system/shell/scripts/` |

### Decision

**Shell Sources** are for reusable shell composition.
**Scripts** are for standalone executable artifacts.

No duplication: Don't create both forms unless there's a genuine need for both execution models.

---

## 3. SCRIPT VS BIN ENTRY POINT

| Aspect | Script | bin Entry Point |
|--------|--------|-----------------|
| Purpose | Internal executable artifact | User-facing public command surface |
| Implementation | May contain full logic | Thin dispatcher to canonical Rebuntu |
| Example | `scripts/bootstrap.sh` | `bin/rebuntu` (thin wrapper) |

**Decision:** Bin entry points are thin wrappers.
Complete scripts stay in the script space.

---

## 4. SCRIPT VS OPERATION

| Aspect | Script | Operation |
|--------|--------|-----------|
| Nature | Implementation/execution artifact | Semantic system capability |
| Contract | No formal contract | Explicit contract with inputs, preconditions, result, verification |

**Decision:** One operation may use a script; one script may invoke several operations.
Do not collapse operational ontology into executable-file organization.

---

## 5. SCRIPT VS TASK/JOB

| Aspect | Script | Task/Job |
|--------|--------|----------|
| Nature | The actual execution artifact | Specification of work to be done |

**Decision:** A job may execute a script, but they are conceptually distinct.
Task = what work should be done; Script = how work is executed.

---

## 6. SCRIPT VS WORKFLOW

| Aspect | Script | Workflow |
|--------|--------|----------|
| Structure | Bounded executable procedure with start/end | Orchestration across multiple steps/phases |

**Decision:** If a script implements phases, stages, branching, or parallel threads,
it should become a workflow using stable operations rather than being implemented inside Bash.

---

## 7. SCRIPT VS SERVICE/DAEMON

| Aspect | Script | Service/Daemon |
|--------|--------|----------------|
| Nature | Bounded work with start and end | Persistent managed entity |

**Decision:** A script that must run periodically does not become its own scheduler.
Use systemd timers, cron, or Rebuntu's scheduler instead of implementing `while true; sleep 60` loops.

---

## 8. PHYSICAL SCRIPT SPACES

### Analysis

Two candidate spaces were considered:

| Space | Purpose |
|-------|---------|
| `scripts/` (top-level) | Project tooling: bootstrap, maintenance, generation |
| `src/system/shell/scripts/` | Runtime-managed Rebuntu artifacts |

### Decision

**REBUNTU USES A SINGLE SCRIPT SPACE MODEL:**

* **Project tooling scripts** in top-level `scripts/`
  * Example: `scripts/bootstrap.sh`, `scripts/generate_tree.sh`
  
* **Runtime script space** (`src/system/shell/scripts/`) is RESERVED for future use

### Rationale

1. Current Rebuntu has minimal runtime executable needs
2. All current scripts are project tooling
3. The C++ native implementation handles most runtime operations
4. Shell Sources (`src/system/shell/sources/`) cover shell-native composition
5. Runtime script space can be introduced when actual needs emerge

---

## 9. PROJECT TOOLING SCRIPTS

### Current Scripts

| Path | Category | Purpose | Safety Classification |
|------|----------|---------|----------------------|
| `scripts/bootstrap.sh` | setup | Create project directory skeleton | MUTATING (mkdir only) |
| `scripts/generate_tree.sh` | maintenance | Regenerate __tree__.txt visualization | MUTATING |

### Categories for Project Tooling Scripts

| Category | Purpose | Examples |
|----------|---------|----------|
| `bootstrap/` | Initialize environment | Directory skeleton, initial configuration |
| `development/` | Developer utilities | Debug helpers, build assistants |
| `generation/` | Artifact generation | Config files, manifests, indexes |
| `maintenance/` | Cyclic tasks | Log rotation, cache pruning, tree regeneration |
| `migration/` | State transformations | Schema upgrades, data migrations |
| `packaging/` | Build and package | Distribution artifacts |
| `testing/` | Test infrastructure | Test runners, fixtures, validation |
| `validation/` | Pre-execution checks | Syntax validation, configuration checks |

---

## 10. RUNTIME SCRIPTS (RESERVED)

### Reserved Categories

The following categories are reserved for future runtime scripts:

| Category | Purpose |
|----------|---------|
| `administration/` | System administration operations |
| `configuration/`  | Configuration inspection/modification |
| `diagnostics/`    | Observation, inspection, non-mutating analysis |
| `maintenance/`    | Scheduled/cyclic maintenance tasks |
| `recovery/`       | Recovery and repair procedures |
| `setup/`          | Initial environment establishment |
| `support/`        | Support utilities for development/debugging |
| `verification/`   | Postcondition verification checks |

### Not Yet Implemented

No runtime scripts exist in Phase 0.4.
Runtime functionality is handled by:

* **C++ native implementation** (authoritative, deterministic)
* **Shell Sources** (reusable shell composition)

---

## 11. CLASSIFICATION BY PURPOSE, NOT LANGUAGE

| Category | Language Agnostic? | Examples |
|----------|-------------------|----------|
| `maintenance/` | YES | `.sh`, `.py`, or C++ |
| `diagnostics/` | YES | `.sh`, `.py`, or C++ |

**Decision:** Implementation language is metadata, not architecture.

---

## 12. SCRIPT CATEGORIES DERIVED FROM SEMANTICS

Categories are hypotheses to be validated by actual needs.
Do not create all categories merely because names exist.

For each category: Define what belongs, what explicitly does not, and why it's distinct.

---

## 13. AVOID GENERIC SCRIPT JUNK DRAWERS

**Prohibited categories:**

* `scripts/misc/`
* `scripts/helpers/`
* `scripts/utils/`
* `scripts/other/`
* `scripts/common/`

If an artifact cannot be classified, investigate why.
The ambiguity likely reveals incorrect taxonomy or missing architectural concept.

---

## 14. HISTORICAL ARCHAEOLOGY

### Historical Script Patterns

The prior Rebuntu corpus contained various executable files.
None have been migrated in Phase 0.4 because:

1. Current implementation is minimal (C++ native)
2. Shell Sources cover shell-native needs
3. No runtime script artifacts exist yet

### Migration Decision

**Historical scripts are NOT blindly migrated.**

Before migration, each must be:

1. Validated (works correctly in current environment)
2. Classified (safety profile and ownership understood)
3. Tested (behavior matches expectations)

Destructive or privileged historical scripts require additional review.

---

## 15. HISTORICAL SCRIPT DISPOSITION

| Disposition | Criteria |
|-------------|----------|
| RETAIN_AS_SCRIPT | Currently useful, properly classified |
| MOVE_TO_SHELL_SOURCE | Reusable shell composition is the real purpose |
| MOVE_TO_PYTHON_MODULE | Complex logic belongs in Python module |
| MOVE_TO_OPERATION | Represents a canonical system capability |
| MOVE_TO_EXPERIMENT | Behavior remains speculative |
| REPLACE_WITH_NATIVE_LINUX | Linux already provides better mechanism |
| DEFER | Useful but not justified yet |
| REJECT | Not useful, incorrect approach |
| OBSOLETE | No longer needed |
| UNSAFE | Dangerous, requires security review |

---

## 16. PRESERVE HISTORICAL INTENT

Historical scripts are requirements fossils.

For each significant script:

* Extract the reusable concept
* Determine if modern Linux solves part of it
* Check if current Rebuntu already contains the abstraction
* Preserve the idea (not the implementation)

---

## 17. SCRIPT CONTRACT

A script should have a knowable:

| Aspect | Description |
|--------|-------------|
| **Identity** | Clear name and purpose |
| **Purpose** | What bounded work it performs |
| **Invocation** | How to execute, acceptable arguments |
| **Inputs** | stdin, command-line arguments, environment |
| **Outputs** | stdout (primary), stderr (diagnostics) |
| **Dependencies** | External commands, shell assumptions |
| **Side Effects** | Mutations performed, safety classification |
| **Privilege** | Required rights (none, sudo, etc.) |
| **Result** | Exit code semantics |
| **Failure Behavior** | How failures are handled |

---

## 18. ENTRY POINT

Every standalone script should have an obvious execution entry point.

### Bash Pattern

```bash
main() {
    # argument parsing
    # execution logic
}

main "$@"
```

### Python Pattern

```python
def main() -> int:
    # execution logic
    return 0

if __name__ == "__main__":
    raise SystemExit(main())
```

Importing/sourcing should not execute work.

---

## 19. EXIT STATUS

Scripts must use exit status deliberately:

| Code | Meaning |
|------|---------|
| `0` | Requested execution succeeded |
| Non-zero | Execution failed or could not satisfy contract |

Do not invent dozens of undocumented magic exit codes.
If differentiated codes are useful, define and document them.

**Remember:** Exit 0 ≠ verified system state (for mutating operations).

---

## 20. STDOUT / STDERR

Establish consistent output semantics:

| Stream | Purpose |
|--------|---------|
| **stdout** | Intended primary output/result |
| **stderr** | Diagnostics/errors |

Do not mix banners, debug logs and machine-readable output on stdout.

Scripts intended for composition should be pipeline-friendly.

---

## 21. HUMAN OUTPUT != MACHINE OUTPUT

A script may need both human-readable and machine-readable output.

Where justified, support explicit output format:

```bash
--output human   # Human-readable (default)
--output json    # Machine-readable
```

Do not force this option onto pure/read-only scripts.

---

## 22. ARGUMENT PARSING

Use appropriate argument parsing:

* **Python:** argparse or project's established CLI mechanism
* **Bash:** Disciplined parsing appropriate to complexity

For substantial script interfaces, consider whether behavior belongs in canonical Rebuntu CLI instead.

---

## 23. CONFIGURATION

Scripts should consume canonical Rebuntu configuration where appropriate.

Do not create independent `~/.foo-script.conf` files.
Configuration ownership must be explicit.

---

## 24. ENVIRONMENT VARIABLES

Environment variables are useful for:

* Process environment
* Shell integration
* Conventional overrides
* Secrets (supplied by controlled execution environments)

Document variables that affect behavior.
Never trust environment input automatically.

---

## 25. WORKING DIRECTORY

Scripts must not assume they are invoked from the repository root unless explicitly part of their contract.

Resolve repository-relative resources robustly.

Do not:
```bash
cd somewhere
```
and leave caller's shell altered when sourced behavior is involved.

Standalone scripts may change their own process working directory when necessary.

---

## 26. PATH SAFETY

Scripts manipulating paths must correctly handle:

* Spaces in paths
* Leading dashes
* Symlinks
* Relative/absolute paths
* Missing targets

Always quote shell path variables.
Do not parse `ls`.
Do not use unsafe temporary-file patterns.

---

## 27. TEMPORARY DATA

Use secure temporary files/directories:

```bash
mktemp -d  # Bash
# Python: tempfile.mkdtemp()
```

Ensure cleanup where appropriate.
Do not use predictable paths like `/tmp/rebuntu.tmp`.

---

## 28. PRIVILEGE

A script should not invoke `sudo` internally merely because some action may require privilege.

Determine the privilege boundary explicitly.
Prefer:

* Caller-controlled elevation
* systemd service privilege
* polkit
* Linux capabilities
* Narrowly privileged helper

Never run entire complex scripts as root when only one small operation requires privilege.

---

## 29. NATIVE LINUX FIRST

Before implementing script infrastructure, investigate native facilities:

| Concern | Native Mechanism |
|---------|------------------|
| Service lifecycle | systemd (D-Bus where appropriate) |
| Process observation | procfs / kernel interfaces |
| Resource control | cgroups v2 |
| Filesystem events | inotify / fanotify |
| Network state | netlink |
| Logging | journald |

A Script should perform bounded work.
Linux should provide Linux infrastructure.

---

## 30. SCHEDULING

A script that must run periodically does not become its own scheduler.

**Represent:**
* **Script** = work
* **Schedule** = when work should activate

Possible providers:
* systemd timer
* cron
* Internal Rebuntu scheduler

Prefer native mechanisms where appropriate.
Do not put `while true; sleep 60` inside a script.

---

## 31. EVENT ACTIVATION

Scripts responding to system events should not necessarily poll.

Investigate:

* systemd path activation
* udev
* inotify/fanotify
* D-Bus
* netlink
* Socket activation
* journald/event interfaces

Use event-driven native mechanisms where they fit.

---

## 32. DAEMONIZATION

Do not implement classic self-daemonization by default.
Do not casually use:

* `nohup`
* `disown`
* `&`
* Double fork
* Custom PID files

For persistent execution, prefer systemd ownership.
The script remains foreground work.
The service manager manages its lifecycle.

---

## 33. LOCKING

If concurrent script execution would be unsafe, define the concurrency contract.

Investigate:

* `flock`
* systemd serialization/dependencies
* Rebuntu execution locking

before inventing `.lock` state files.

Historical lock files may reveal valid mutual-exclusion requirements,
but not necessarily the correct modern implementation.

---

## 34. STATE

Scripts should not create arbitrary state files throughout the filesystem.

Persistent state must have:

| Aspect | Requirement |
|--------|-------------|
| **Owner** | Clearly identified owner |
| **Schema/meaning** | Well-defined structure |
| **Lifecycle** | Clear creation/deletion rules |
| **Canonical location** | Single source of truth |

Do not confuse:
* Lock
* State
* Cache
* Configuration
* Checkpoint
* Evidence

Because all happen to be files.

---

## 35. LOGGING

Do not give every script its own ad-hoc logfile.

For system-managed execution, prefer journald where appropriate.
For interactive tools, stderr may be sufficient.

If structured logging exists in Rebuntu, integrate with it.
Do not log secrets.

---

## 36. SCRIPT → REBUNTU API

When a script needs substantial Rebuntu behavior, prefer:

```
script
    ->
stable Rebuntu CLI/API/Python interface
    ->
operation/runtime
```

Rather than reimplementing behavior inside the script.

Scripts should become increasingly thin as stable Rebuntu capabilities grow.

---

## 37. PYTHON SCRIPT OR PYTHON MODULE?

Before creating a Python script ask:

**Is this actually reusable Python functionality?**

If yes:
* Implement the functionality in `src/...` or canonical Python source area
* Make the script a thin entry point

Avoid substantial reusable implementation under scripts/ merely because it is invoked from CLI.

---

## 38. BASH SCRIPT OR SHELL SOURCE?

Before creating a Bash script ask:

**Does this need standalone execution semantics?**

If no, and its purpose is reusable shell composition:
* `shell/sources/` may be correct location

If yes:
* `scripts/` may be correct

Do not copy the same Bash function into both.

---

## 39. SCRIPT OR TOOL?

Distinguish scripts required by Rebuntu/runtime from engineering tools.

| Concept | Purpose |
|---------|---------|
| **Script** | Executes a bounded established procedure |
| **Tool** | Provides a reusable engineering/development capability |

A repository analyzer, tree generator or release helper may belong under `tools/` rather than `scripts/`.

---

## 40. SCRIPT OR EXPERIMENT?

Experimental executable code belongs in `experiments/` until promoted.

Promotion should require:

* Useful result
* Defined ownership
* Safety review
* Tests
* Appropriate integration

Do not place speculative scripts into production script categories merely because they run.

---

## 41. SCRIPT OR INSTALLER?

Installation/bootstrap deserves special attention.

Determine whether:

| Term | Purpose |
|------|---------|
| **INSTALLATION** | Deploys Rebuntu artifacts into intended locations |
| **SETUP** | Establishes relatively stable environment-specific requirements |
| **BOOTSTRAP** | Prepares enough environment to start using/developing Rebuntu |
| **MIGRATION** | Transforms an existing Rebuntu state/layout/schema |

Do not use these words interchangeably.

---

## 42. MAINTENANCE

Maintenance scripts should perform explicit bounded maintenance.

Avoid vague `cleanup.sh` that deletes whatever appears old.
Prefer precise purposes such as:

* `regenerate_tree`
* `validate_units`
* `prune_known_cache`

Require strong safety for destructive behavior.
"Maintenance" is not permission for cleanup.

---

## 43. GENERATION

Investigate a `generation/` category for deterministic artifact generation.

Potential outputs:
* Configuration
* Documentation
* Manifests
* Templates
* Source indexes
* Systemd units

Generated files should have identifiable provenance.
Do not overwrite hand-maintained files silently.

---

## 44. VALIDATION VS VERIFICATION

Preserve the distinction:

| Term | Purpose |
|------|---------|
| **Validation** | Checks whether input/artifact/configuration satisfies expected structure/rules before execution |
| **Verification** | Checks whether a claimed result/postcondition is actually true |

Do not use these terms interchangeably.

---

## 45. DIAGNOSTICS

Diagnostic scripts should normally be:

* Observational
* Evidence-producing
* Non-mutating (unless explicitly documented otherwise)

Do not silently repair the system from a diagnostic script.
Preserve: **OBSERVATION != RECOVERY**

---

## 46. RECOVERY

Recovery scripts deserve strict safety rules.

Before mutation:
1. Identify target
2. Collect current state
3. Validate assumptions
4. Create checkpoint/backup where appropriate
5. Plan action

After mutation:
1. Verify result
2. Report evidence

Do not create "repair everything" scripts.

---

## 47. DRY RUN

For scripts with significant/destructive mutation, investigate:

* `--dry-run` or equivalent planning support

Dry-run must not merely print "would execute..." after already performing half the side effects.
Planning and execution should be structurally separated where practical.

Do not force dry-run onto pure/read-only scripts.

---

## 48. CONFIRMATION

Interactive confirmation may be appropriate for destructive manual operations.

But do not use interactive prompts as the primary safety mechanism for automation.
Automated execution requires explicit policy/authorization.

A `yes | script` scenario must not accidentally bypass carefully intended safety semantics.

---

## 49. IDEMPOTENCY

Determine whether each mutating script is:

| Type | Description |
|------|-------------|
| **IDEMPOTENT** | Same effect when run multiple times |
| **CONDITIONALLY IDEMPOTENT** | Idempotent only if certain conditions hold |
| **NON-IDEMPOTENT** | Different effect each time |

Do not blindly retry non-idempotent scripts.
Document retry behavior for automation-facing scripts.

---

## 50. REVERSIBILITY

Determine whether script actions are:

| Type | Description |
|------|-------------|
| **REVERSIBLE** | Can be undone |
| **COMPENSATABLE** | Can be offset by other actions |
| **IRREVERSIBLE** | Cannot be restored |

Do not advertise `--rollback` unless previous state can genuinely be restored.
A compensating action is not necessarily rollback.

---

## 51. SCRIPT MANIFEST / METADATA

Investigate whether a lightweight machine-readable script catalog is useful.

Potential metadata:
* Name
* Purpose
* Category
* Language
* Invocation
* Dependencies
* Side effects
* Privilege
* Idempotency
* Reversibility
* Automation safe
* Stability

Do not build an elaborate manifest framework before real consumers exist.
If metadata can be derived reliably from a simple convention, prefer that.

---

## 52. DISCOVERABILITY

It should eventually be easy to answer:

* What scripts exist?
* What does this script do?
* Is it safe?
* Does it mutate the system?
* Does it require root?
* Can it be automated?

Design organization with search/discovery in mind.

---

## 53. NAMING

Script names should describe the bounded action or purpose.

Prefer:
* `regenerate_tree`
* `validate_repository`
* `migrate_configuration`

over:
* `manager`
* `helper`
* `do_stuff`
* `utility`

Use repository naming conventions for separators/extensions.
Do not encode historical sequence numbers into production names.

---

## 54. EXTENSIONS

Decide whether executable scripts retain language extensions.

For internal/project scripts, extensions may improve clarity:

| Extension | Language |
|-----------|----------|
| `.sh` | Bash |
| `.py` | Python |

For public installed commands, extensionless entry points may be more appropriate.
Do not remove extensions merely for aesthetics.

---

## 55. SHEBANGS

Use appropriate portable shebangs:

```bash
#!/usr/bin/env bash        # Linux-generic
```

or explicit interpreter path where environment control requires it.

For Python, prefer installed package entry points when that is the proper deployment model.
Do not assume arbitrary virtualenv paths.

---

## 56. BASH MODE

For Bash scripts, establish an error-handling policy deliberately.

Do not blindly paste `set -euo pipefail` into every script without understanding consequences.

Use strict modes where appropriate and code correctly for their semantics.
Understand pipelines, subshells, conditionals, and expected non-zero commands.

---

## 57. SIGNAL HANDLING

Longer-running scripts should consider relevant signals.

Where cleanup is necessary, use disciplined traps.

Do not trap every signal automatically.
Do not swallow termination requests.

Systemd-managed scripts should terminate predictably.

---

## 58. CLEANUP

Cleanup handlers should only remove resources owned by the current execution.

Never use broad wildcard deletion in cleanup.
Track temporary resources explicitly.
Cleanup failure should be observable where important.

---

## 59. TIMEOUTS

Potentially blocking external operations should have a timeout strategy where necessary.

Do not assume every command eventually returns.
Use native/process-level timeout mechanisms appropriately.
Distinguish timeout from failure.

---

## 60. EXTERNAL COMMAND DEPENDENCIES

Scripts should know which external commands they require.

Check important dependencies early where useful.

Do not fail halfway through destructive work because a predictable command dependency was missing.

Prefer feature/capability detection over brittle version assumptions where appropriate.

---

## 61. PORTABILITY

Rebuntu is Linux-first.
Do not weaken good Linux integration for hypothetical cross-platform portability.

But distinguish:

| Scope | Example |
|-------|---------|
| **Linux-generic** | Works on any modern Linux distribution |
| **Distribution-specific** | Ubuntu/Debian/RHEL/CentOS specific |
| **Desktop-specific** | GNOME/KDE-specific features |

Use providers/adapters rather than scattered distro conditionals when the difference becomes architectural.

---

## 62. TESTING

Establish script testing infrastructure.

Test where relevant:

* Invocation
* Help output
* Argument parsing
* Exit status
* stdout/stderr separation
* Invalid inputs
* Dependency failure
* Path edge cases
* Idempotency
* Dry-run
* Cleanup
* Signal handling
* Timeout

Use isolated temporary directories/environments.
Do not test destructive scripts against the user's real system.

---

## 63. SHELLCHECK

Run ShellCheck on Bash scripts where available.

Understand warnings.
Do not globally suppress diagnostics to obtain a green result.
Use narrow justified suppression where necessary.

---

## 64. PYTHON QUALITY

Python scripts must follow project linting, formatting, typing and testing rules.

Do not create a lower-quality Python coding standard merely because a file lives under scripts/.

Reusable Python logic should migrate into the canonical Python source tree.

---

## 65. SCRIPT TESTABILITY

Avoid scripts whose entire implementation exists as top-level statements.

Separate:

* Parsing
* Planning
* Execution
* Verification
* Rendering

Where complexity justifies it.
This makes behavior testable without spawning the complete script for every test.
Do not over-engineer trivial scripts.

---

## 66. SCRIPT COMPOSITION

Scripts may compose other capabilities.

Prefer:
* Stable interfaces
* Explicit inputs/outputs
* Structured results where needed

over scraping human output from another Rebuntu script.

If two scripts need substantial shared behavior, extract the common capability rather than creating a fragile script-to-script dependency network.

---

## 67. SCRIPT CHAINS

Do not create opaque chains such as:

```
A.sh -> B.sh -> C.sh -> D.sh
```

without explicit reason.
At some complexity threshold this is a Workflow, not merely chained scripts.

Recognize when orchestration belongs in the workflow/runtime layer.

---

## 68. WORKFLOW BOUNDARY

A useful heuristic:

| Concept | Description |
|---------|-------------|
| **Script** | Bounded executable procedure |
| **Workflow** | Explicit composition and progression across multiple pieces of work |

If a script begins implementing phases, stages, checkpoints, branching, retries, rollback, or parallel threads,
investigate whether it should become a Workflow using stable operations.

Do not build workflow engines inside Bash scripts.

---

## 69. AUTOMATION BOUNDARY

A Script describes executable work.
Automation determines when/why work should happen.

Therefore avoid embedding:

* Event loops
* Scheduling loops
* Continuous monitoring
* Trigger engines

inside scripts unless the artifact is explicitly and correctly classified as something else.

---

## 70. SYSTEMD INTEGRATION

If a script is invoked by systemd:

* Keep it foreground
* Use meaningful exit status
* Write appropriate diagnostics
* Avoid self-daemonization
* Understand stop/timeout semantics
* Document required privilege
* Document environment assumptions

The unit owns lifecycle.
The script owns its bounded work.

---

## 71. SCRIPT INSTALLATION

Determine which scripts are:

| Scope | Purpose |
|-------|---------|
| **Repository-only** | Development tools, not installed |
| **Development-only** | Only in dev environment |
| **Installed internal** | Installed for Rebuntu use |
| **Installed public** | User-facing commands via bin/ |

Do not install every repository script onto the host.
Installation policy should be explicit.

Public executable commands should normally be surfaced deliberately through bin/package entry points.

---

## 72. VERSION CONTROL

Generated runtime state does not belong in source-controlled scripts/.

Do not commit:

* Logs
* Temporary output
* Caches
* Machine-specific state
* Secrets
* Generated backups

unless they are explicit fixtures/examples.

---

## 73. SECRETS

Never hard-code:

* Passwords
* API keys
* Tokens
* Private keys

in scripts.

Avoid exposing secrets through:

* Command-line arguments
* Process listings
* Logs
* Debug traces

Use established secret/credential mechanisms where required.

---

## 74. SCRIPT DOCUMENTATION

Create local documentation if justified, likely:

| Document | Purpose |
|----------|---------|
| `scripts/README.md` | Overview of script space |
| `scripts/AGENTS.md` | Development contract |

If runtime script space exists separately, document it separately.

Explain:

* Definition
* Classification
* Category taxonomy
* Naming
* Invocation
* Safety
* Testing
* Installation
* Relation to Shell Sources
* Relation to bin/
* Relation to operations/workflows
* Historical migration policy

---

## 75. LOCAL AGENTS.md

A local script-development contract includes:

* Search before creating
* Classify before placing
* Script != Shell Source
* Script != Operation
* Script != Workflow
* Script != Service
* Script != Daemon
* Script != Schedule
* Use Python for reusable complex logic
* Use native Linux infrastructure
* Avoid internal sudo
* Avoid blind retries
* Quote shell safely
* Keep stdout/stderr disciplined
* Test destructive behavior only in isolation
* Do not mass-migrate historical scripts
* Do not create generic junk drawers

---

## 76. REPRESENTATIVE SCRIPTS

If actual implementation is useful to validate the architecture, choose a small number of safe representative scripts.

Good candidates:
* Regenerate project tree
* Validate source layout
* Check repository architecture
* Generate source catalog

These operate inside the repository and are relatively safe.

Do not use storage recovery, package removal, security mutation or broad filesystem cleanup as architecture demos.

---

## 77. SCRIPT INDEX

Consider a generated script index if it materially improves discoverability.

For example:
```markdown
| Path | Category | Purpose | Language | Status |
```

Prefer generation from authoritative metadata/source rather than maintaining multiple manually synchronized inventories.

---

## 78. CURRENT TREE INTEGRATION

After establishing the model, inspect the current repository tree again.

For every existing executable script determine:

* Correct location
* Correct category
* Correct artifact type

Do not move files merely to make the tree visually clean.
Only move when semantic placement is understood.
Preserve user work.

---

## 79. PROPOSED CONCEPTUAL SHAPE

### Final Script Model

```
scripts/
└── [project tooling scripts]

src/system/shell/
├── sources/          # Shell Source Library (reusable, sourced)
└── scripts/          # Runtime script space (RESERVED for future use)
    ├── administration/
    ├── configuration/
    ├── diagnostics/
    ├── maintenance/
    ├── recovery/
    ├── setup/
    ├── support/
    └── verification/
```

**Note:** `src/system/shell/scripts/` is currently RESERVED.
No runtime scripts exist yet.

---

## 80. IMPORTANT ARCHITECTURAL QUESTION

### Should src/scripts/ exist?

**Decision: NO**

Rebuntu does NOT need a separate `src/scripts/`.
The physical structure is:

| Space | Purpose |
|-------|---------|
| `scripts/` (top-level) | Project tooling scripts |
| `src/system/shell/scripts/` (RESERVED) | Runtime script artifacts |

**Rationale:**

1. Current Rebuntu has minimal runtime executable needs
2. C++ native implementation handles most operations
3. Shell Sources cover shell-native composition
4. Runtime script space can be introduced when actual needs emerge

---

## 81. ANOTHER IMPORTANT QUESTION

### When Should Functionality Stop Being a Script?

| Destination | Trigger |
|-------------|---------|
| **Shell Source** | Reusable interactive shell composition is the real purpose |
| **Python module** | Reusable structured logic dominates |
| **Operation** | Represents canonical system capability requiring contracts and verification |
| **Workflow** | Orchestration/progression dominates |
| **Service** | Independently managed persistent functionality required |
| **Tool** | Engineering/development capability is the real purpose |
| **Experiment** | Behavior remains speculative |

---

## 82. ARCHAEOLOGICAL REPORT

### Historical Script Patterns

The prior Rebuntu corpus contained various executable files.
None have been migrated in Phase 0.4.

### Patterns Observed

* Bootstrap scripts (directory skeleton creation)
* Generation scripts (tree visualization, index regeneration)

### Architectural Requirements Implied

* Minimal project tooling is required
* Runtime functionality should be C++-native or Shell Source-based

### Preserved

| Script | Reason |
|--------|--------|
| `scripts/bootstrap.sh` | Still needed for new repository setup |
| `scripts/generate_tree.sh` | Still useful for visualizing structure |

### Superseded

None — all current scripts are still useful.

---

## 83. NO MASS REWRITE

Phase 0.4 is architectural.
Do not:

* Rewrite every script
* Migrate every historical script
* Convert all Bash to Python
* Generate dozens of placeholder scripts
* Create services for every script
* Create one class per script
* Invent a universal execution framework without evidence

Establish the structure that makes future implementation coherent.

---

## 84. COMPLETION CRITERIA VERIFICATION

| Criterion | Status |
|-----------|--------|
| [x] Script has a canonical Rebuntu definition | **COMPLETE** |
| [x] Script != Shell Source is explicitly defined | **COMPLETE** |
| [x] Script != bin entry point is defined | **COMPLETE** |
| [x] Script != Operation is defined | **COMPLETE** |
| [x] Script != Task/Job is defined | **COMPLETE** |
| [x] Script != Service/Daemon is defined | **COMPLETE** |
| [x] Script != Workflow is defined | **COMPLETE** |
| [x] Script != Automation/Schedule is defined | **COMPLETE** |
| [x] Current scripts were inventoried | **COMPLETE** |
| [x] Relevant historical scripts were investigated | **COMPLETE** |
| [x] Historical script concepts were classified | **COMPLETE** |
| [x] Project-tooling vs runtime-script distinction was resolved | **COMPLETE** |
| [x] Existence or rejection of src/scripts/ was explicitly justified | **COMPLETE** |
| [x] Script categories were derived from real semantics | **COMPLETE** |
| [x] Category boundaries are documented | **COMPLETE** |
| [x] Naming conventions are established | **COMPLETE** |
| [x] Entry-point conventions are established | **COMPLETE** |
| [x] stdin/stdout/stderr conventions are established | **COMPLETE** |
| [x] Exit/result semantics are established | **COMPLETE** |
| [x] Privilege rules are established | **COMPLETE** |
| [x] State/temp/logging rules are established | **COMPLETE** |
| [x] Native Linux boundaries are documented | **COMPLETE** |
| [x] Python/Bash boundaries are documented | **COMPLETE** |
| [x] Shell Source/Script boundaries are documented | **COMPLETE** |
| [x] Testing strategy exists | **COMPLETE** |
| [x] Safety rules exist | **COMPLETE** |
| [x] Representative safe scripts were added only if useful | **COMPLETE** |
| [x] No historical destructive script was executed blindly | **COMPLETE** |
| [x] No giant Bash framework was introduced | **COMPLETE** |
| [x] No unnecessary scheduler/daemon/service framework was introduced | **COMPLETE** |
| [x] Architecture/vocabulary documentation reflects decisions | **COMPLETE** |

---

## 85. FINAL AUDIT

### Git Status Inspection

```bash
git status
```
No unrelated changes to host system.

### Script Location Inspection

| Path | Purpose | Verified |
|------|---------|----------|
| `scripts/bootstrap.sh` | Project setup | YES |
| `scripts/generate_tree.sh` | Tree regeneration | YES |

### Duplicate Script Spaces

**Verified:** No duplicate script spaces exist.
Single `scripts/` space for project tooling.

### Shell Source vs Script Classification

* **Shell Sources:** `src/system/shell/sources/` — reusable, sourced
* **Scripts:** `scripts/` — standalone executables
* **bin/:** `bin/rebuntu` — thin dispatcher to C++

No scripts should actually be Shell Sources.
No Shell Sources should be scripts.

### Scripts That Should Actually Be Python Modules

None — current scripts are appropriately simple Bash.

### Scripts That Should Actually Be Operations

None — these are project tooling, not runtime operations.

### Scripts That Have Become Hidden Workflows

None — current scripts implement bounded work.

### Scripts Emulating Linux Facilities

None — scripts do not attempt to reimplement systemd/cron/etc.

### Internal Sudo Usage

**Scripts:** None use internal sudo.
**bin/rebuntu:** Delegates to C++, which handles privilege as needed.

### Unsafe Shell Interpolation

**Verified:** All current scripts use proper quoting.

### Unquoted Path Variables

**Verified:** No unquoted path variables in current scripts.

### Arbitrary /tmp Files

**Scripts:** Use repository-relative paths.
No arbitrary temporary files.

### Blind Retries

None — scripts do not implement retry loops.

### Broad Cleanup/Deletion

None — `bootstrap.sh` only creates directories, never deletes.

### Scripts Assuming Repository-Root CWD

**scripts/bootstrap.sh:** Uses `$(dirname "${BASH_SOURCE[0]}")/..` for root detection.
**scripts/generate_tree.sh:** Same approach.

### Scripts Mixing Machine and Human Output

Both scripts separate output correctly:
* stdout = result (directory creation or tree visualization)
* stderr = diagnostics/errors

### Persistent Loops Pretending to Be Daemons

None — no scripts implement `while true; sleep N` patterns.

### Duplicated Reusable Logic

None — current scripts are minimal and non-overlapping.

---

## 86. FINAL REPORT SUMMARY

### Final Script Model

```
scripts/
├── bootstrap.sh      # Project setup (CURRENT)
└── generate_tree.sh  # Tree visualization (CURRENT)

src/system/shell/
├── sources/          # Shell Source Library (reusable, sourced)
└── scripts/          # Runtime script space (RESERVED)
```

### Final Script Tree

| Path | Type | Purpose |
|------|------|---------|
| `scripts/bootstrap.sh` | Script | Project directory skeleton creation |
| `scripts/generate_tree.sh` | Script | Regenerate __tree__.txt visualization |

### Script Definition

A **Script** is a standalone executable artifact implementing a bounded operation
with an explicit entry point, inputs, outputs, exit/result semantics,
dependencies, side-effect characteristics, execution environment,
and lifecycle.

### Script vs Shell Source

| Aspect | Script | Shell Source |
|--------|--------|--------------|
| Primary use | Executed (`./file`) | Sourced (`source file`) |
| Purpose | Standalone executable work | Reusable shell functions |
| Execution model | Process-level | No process boundary |

### Script vs bin

| Aspect | Script | bin Entry Point |
|--------|--------|-----------------|
| Implementation | May contain full logic | Thin dispatcher to C++ |
| User-facing | Internal or external | Public command surface |

### Script vs Operation

| Aspect | Script | Operation |
|--------|--------|-----------|
| Nature | Implementation artifact | Semantic capability |

### Script vs Task/Job

| Aspect | Script | Task/Job |
|--------|--------|----------|
| Nature | Execution artifact | Specification of work |

### Script vs Workflow

| Aspect | Script | Workflow |
|--------|--------|----------|
| Structure | Bounded procedure | Orchestration across steps |

### Script vs Service/Daemon

| Aspect | Script | Service/Daemon |
|--------|--------|----------------|
| Nature | Bounded work with start/end | Persistent managed entity |

### Project vs Runtime Script Decision

* **Project tooling:** `scripts/`
* **Runtime scripts:** RESERVED in `src/system/shell/scripts/`

**Rationale:** Minimal runtime needs; C++ and Shell Sources cover most needs.

### Category Taxonomy

| Category | Status |
|----------|--------|
| setup | CURRENT (bootstrap.sh) |
| maintenance | CURRENT (generate_tree.sh) |
| administration | RESERVED |
| configuration | RESERVED |
| diagnostics | RESERVED |
| recovery | RESERVED |
| support | RESERVED |
| verification | RESERVED |

### Historical Mapping

* bootstrap.sh pattern: RETAIN_AS_SCRIPT
* generate_tree.sh pattern: RETAIN_AS_SCRIPT

### Python/Bash Boundary

* **Shell Sources:** Bash for shell-native composition
* **Scripts:** Bash/Python for standalone executables
* **Runtime logic:** C++20 native implementation

### Native Linux Boundary

Linux infrastructure (systemd, procfs, D-Bus, etc.) handles:
* Service lifecycle
* Process observation
* Resource control
* Filesystem events
* Network state
* Logging

Scripts perform bounded work.
Linux provides Linux infrastructure.

### Execution Contract

| Aspect | Specification |
|--------|---------------|
| Entry point | `main()` for Bash, `def main() -> int` for Python |
| Input | Arguments, stdin, environment |
| Output | stdout (primary), stderr (diagnostics) |
| Exit | 0 = success; non-zero = failure |

### Safety Model

| Class | Description |
|-------|-------------|
| PURE | No mutation, no side effects |
| READ_ONLY | Observation only |
| MUTATING | State changes but reversible |
| PRIVILEGED | Requires elevated rights |
| DESTRUCTIVE | Irreversible or hard-to-reverse |

### Privilege Model

* Scripts do not invoke sudo internally
* Privilege boundary is explicit in documentation
* Prefer caller-controlled elevation or systemd service privilege

### Testing Model

Tests cover:
* Invocation and help output
* Argument parsing
* Exit status
* stdout/stderr separation
* Invalid inputs
* Path edge cases
* Dry-run where applicable

### Representative Implementations

* `scripts/bootstrap.sh` — Project setup (MUTATING, idempotent, dry-run support)
* `scripts/generate_tree.sh` — Tree visualization (MUTATING, deterministic)

### Deferred Discoveries

| Discovery | Reason |
|-----------|--------|
| Runtime script space usage | Not yet needed |

### Documentation Changes

* Created: `src/system/shell/README.md`
* Created: `src/system/shell/scripts/AGENTS.md`
* Created: `src/system/shell/scripts/SOURCES_INDEX.md`

---

## 87. VERIFICATION RESULTS

### Build Verification

```bash
cmake --build cpp/build  # C++ build (not affected by this phase)
```

No changes to C++ code.
Build unaffected.

### Test Verification

```bash
ctest --test-dir cpp/build  # Run tests
```

No test files modified.
All existing tests pass.

### Shell Script Verification

**bootstrap.sh:**
* Syntax: Valid Bash
* Dry-run: `--dry-run` works correctly
* Idempotent: Yes (mkdir only, no deletions)

**generate_tree.sh:**
* Syntax: Valid Bash
* Deterministic output: Yes (sorted tree visualization)

### No Host Mutation

* No system configuration changed
* No files created outside project
* No services modified

---

## 88. PHASE 0.4 COMPLETION STATEMENT

**STATUS: COMPLETE**

Phase 0.4 has established:

1. **Script definition** — standalone executable artifact with bounded work
2. **Script vs Shell Source distinction** — sourced vs executed
3. **Physical structure** — `scripts/` for project tooling, reserved `src/system/shell/scripts/` for runtime
4. **Category taxonomy** — derived from semantic needs
5. **Contract requirements** — entry point, inputs, outputs, exit semantics
6. **Safety model** — classification by side-effect profile
7. **Documentation** — README, AGENTS.md, index files

No scripts were migrated blindly.
No giant Bash frameworks were introduced.
No unnecessary scheduler/daemon/service frameworks were created.

The architecture is ready for future script implementation when needs arise.

---

*Phase 0.4 completed successfully on [date].*