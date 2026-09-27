# Rebuntu Agent Guidance

## Project Identity

THIS PROJECT IS **REBUNTU**.

THERE IS ONE REBUNTU.

REBUNTU IS **C++-NATIVE**.

ARCHITECTURE DEFINES SOURCE OWNERSHIP;
LANGUAGE DOES NOT DEFINE ARCHITECTURE.

C++ OWNS AUTHORITATIVE DETERMINISTIC SYSTEM MACHINERY.

PYTHON EXISTS ONLY AT EXPLICIT, JUSTIFIED:

* SEMANTIC;
* ML;
* RESEARCH;
* TESTING;
* DEVELOPMENT;

BOUNDARIES.

DO NOT RECREATE RETIRED PYTHON ARCHITECTURE.

The conservative implementation baseline is:

> **C++20 + Linux + CMake + CTest**

Unless a task or an established external boundary provides a strong and explicit reason otherwise, new production Rebuntu functionality SHALL be implemented in C++20.

---

# 1. Core Engineering Doctrine

Follow these rules throughout the repository:

> **SEARCH BEFORE IMPLEMENTING.**

> **UNDERSTAND BEFORE MODIFYING.**

> **COMPOSE BEFORE GENERATING.**

> **DISCOVER BEFORE CREATING.**

> **USE EXISTING REBUNTU ARCHITECTURE BEFORE INVENTING NEW ARCHITECTURE.**

> **USE LINUX BEFORE EMULATING LINUX.**

> **VALIDATE BEFORE AUTHORIZING.**

> **AUTHORIZE BEFORE MUTATING.**

> **OBSERVE BEFORE CLAIMING STATE.**

> **VERIFY BEFORE REPORTING SUCCESS.**

> **PRESERVE UNKNOWN HONESTLY.**

> **WORKING IMPLEMENTATION OVER SCAFFOLDING.**

> **ARCHITECTURE DEFINES OWNERSHIP; LANGUAGE DOES NOT.**

---

# 2. C++-Native Architecture

Rebuntu's authoritative deterministic runtime is written in C++.

This includes:

* runtime execution engine;
* authoritative state management;
* concurrency and task orchestration;
* event infrastructure;
* typed command machinery;
* policy enforcement;
* security enforcement;
* validation;
* authorization;
* execution;
* verification;
* recovery infrastructure;
* native OS integration;
* IPC;
* deterministic providers;
* platform providers;
* canonical control-plane machinery.

C++ code is deterministic, type-safe and production-authoritative.

Do not implement missing C++ functionality in Python merely because doing so is faster.

Convenience is NOT sufficient architectural justification.

---

# 3. Python's Limited Role

Python exists ONLY at explicitly justified architectural boundaries, including where appropriate:

* semantic/ML inference;
* BitNet integration;
* Gordon integration;
* embeddings;
* reranking;
* experimental ML;
* model evaluation;
* research prototyping;
* data preparation;
* narrow development tooling;
* testing infrastructure.

Python must NOT become:

* a second runtime;
* a second control plane;
* an authoritative state owner;
* an orchestration layer parallel to C++;
* an alternate implementation of deterministic Rebuntu machinery.

Before creating ANY production Python, answer:

1. Why is Python architecturally justified here?
2. Does this functionality actually belong in deterministic C++?
3. Does an approved Python boundary already exist?
4. Can the functionality be added to that boundary?
5. What is the authority ceiling of the Python component?
6. Who owns authoritative state?
7. What typed boundary separates Python from authoritative C++?

If these questions do not produce a compelling justification:

> USE C++20.

---

# 4. Historical Python Specifications

Rebuntu underwent a major architectural migration from Python to C++.

Historical phase specifications and documentation may still contain Python-oriented implementation assumptions.

Therefore:

> **INSTEAD OF PYTHON, USE C++20 AS THE PRIMARY IMPLEMENTATION LANGUAGE.**

This instruction overrides Python-specific implementation-language assumptions in historical Rebuntu tasks.

Preserve the task's:

* semantic requirements;
* architecture;
* behavior;
* invariants;
* safety requirements;
* tests;
* acceptance criteria;
* Linux integration.

Translate Python-specific mechanisms according to **SEMANTIC PURPOSE**, not mechanical syntax.

Do NOT blindly translate:

`Python module -> C++ class`

`Python package -> CMake library`

`dict -> std::unordered_map`

`asyncio -> std::thread`

`async def -> std::async`

`Protocol -> abstract base class`

`decorator -> macro`

`exception -> C++ exception`

Determine what the original mechanism was intended to accomplish first.

Then implement the appropriate native C++20 design.

Historical documentation is requirements archaeology.

It is NOT authoritative for current implementation decisions where it conflicts with the current architecture.

External Python components explicitly required by a task may remain Python-based at their justified boundary.

---

# 5. Architecture-First Source Organization

Source placement follows the narrowest stable architectural owner, not language.

Prefer:

```text
src/
    <architectural subsystem>/
        ...
```

NOT:

```text
cpp/src/
python/
```

as competing architecture roots.

A `cpp/` directory may exist for native build/toolchain purposes but must NOT become a parallel architecture tree.

Likewise, an approved Python boundary must remain attached to the architectural subsystem it serves rather than creating an independent Python version of Rebuntu.

Phase numbers are history.

They are NOT architecture.

Do NOT create structures such as:

```text
src/phase45/
src/phase47/
src/phase53/
```

merely because functionality originated in those phases.

---

# 6. Repository-First Discovery

Before implementing ANYTHING:

1. inspect `git status`;
2. locate all applicable `AGENTS.md` files;
3. inspect the relevant source tree recursively;
4. read applicable architecture documentation;
5. inspect relevant phase specifications;
6. search semantically for existing functionality;
7. inspect types and interfaces;
8. inspect providers/adapters;
9. identify callers;
10. identify state ownership;
11. inspect configuration;
12. inspect tests;
13. inspect native OS mechanisms;
14. inspect security boundaries;
15. determine acceptance evidence.

**NEVER infer absence from filenames alone.**

A feature with a different historical name may already exist.

A capability may be distributed across several components.

Search behavior and semantics, not merely names.

---

# 7. Duplicate Implementation Guard

Before creating a new:

* class;
* interface;
* registry;
* provider;
* executor;
* runtime;
* queue;
* state store;
* event bus;
* process runner;
* filesystem helper;
* authorization layer;
* Operation abstraction;
* IPC abstraction;
* parser;
* command model;

search for existing functionality first.

Prefer:

```text
DISCOVER
    ↓
EXTEND
    ↓
COMPOSE
    ↓
REFACTOR
    ↓
MIGRATE
    ↓
REMOVE
```

over:

```text
CREATE PARALLEL IMPLEMENTATION
```

Duplicate implementation is an architectural defect unless explicitly justified.

---

# 8. Aggregational Morphing

Rebuntu evolves primarily by extending, composing and restructuring existing machinery.

Use:

```text
DISCOVER → EXTEND → COMPOSE → REFACTOR → MIGRATE → REMOVE
```

A new implementation is not complete merely because it exists.

Production callers must actually use it.

Do not leave:

```text
old implementation
+
new implementation
+
ambiguous ownership
```

---

# 9. Fixed-Point Caller Migration

When replacing or materially changing implementation:

```text
modify canonical implementation
  ↓
find callers
  ↓
migrate callers
  ↓
find callers of callers where relevant
  ↓
update tests/config/docs
  ↓
rediscover references
  ↓
repeat until fixed point
```

Do not stop after adding the replacement.

A migration is incomplete while production paths still depend unintentionally on the retired implementation.

---

# 10. Concepts Are Not Automatically Classes

Rebuntu has a rich ontology.

That does NOT imply every concept deserves:

* a class;
* an abstract base class;
* a directory;
* a process;
* a service;
* a thread;
* a CMake target.

Remember:

> **CONCEPT != CLASS**

> **CONCEPT != DIRECTORY**

> **CONCEPT != PROCESS**

> **CONCEPT != THREAD**

> **SEMANTIC MODULARITY != PROCESS MODULARITY**

Prefer composition and narrow cohesive types.

Avoid Java-style architecture expressed in C++.

---

# 11. Core Semantic Distinctions

Preserve established distinctions.

## State

Lifecycle, activity, control, readiness, health and outcome are different dimensions.

Do not collapse them into a single generic status.

## Execution and verification

> **EXECUTION SUCCESS != VERIFIED SEMANTIC SUCCESS**

Exit status `0` proves only what the exit status actually proves.

Consequential operations require postcondition observation and verification where applicable.

## Knowledge

```text
UNKNOWN != FALSE
UNKNOWN != FAILED
UNKNOWN != PASS
INCOMPLETE SEARCH != NO MATCH
MISSING EVIDENCE != SUCCESS
```

Absence of evidence is not automatically evidence of absence.

Acquisition failure is not a negative observation.

## Desired and observed state

> **DESIRED STATE != OBSERVED STATE**

Never present desired configuration as confirmed runtime reality.

## Domain distinctions

Preserve:

```text
service != daemon

Task != Job != Execution != Attempt

Automation != Workflow

Schedule != Automation

Privilege != Authorization

Execution != Verification

Model output != authority
```

Do not collapse these distinctions for implementation convenience.

---

# 12. State Ownership — No Shadow Truth

DO NOT CREATE SHADOW TRUTH.

For every important state determine its authoritative owner.

Examples:

```text
kernel
    → process/device state

systemd
    → managed service state

filesystem
    → filesystem state

Rebuntu domain owner
    → Rebuntu-specific durable state
```

Cached or interpreted state must retain provenance.

Do not create a second authoritative copy merely because it is convenient.

---

# 13. DATA != CONTROL — Phase 53

Data, including model output and configuration, is not automatically control.

Use:

```text
DATA
  ↓
parse
  ↓
validate
  ↓
provenance
  ↓
context
  ↓
capability
  ↓
policy
  ↓
authorization
  ↓
typed operation
  ↓
execution
  ↓
verification
```

Model output is UNTRUSTED input.

It may become:

* `SEMANTIC_ANNOTATION`;
* `HYPOTHESIS`;
* `RECOMMENDATION`;
* `IntentCandidate`.

It does NOT become merely by being generated:

* `OBSERVED_FACT`;
* policy decision;
* authorization;
* capability;
* verified state.

---

# 14. Confidentiality Lattice — Phase 53

```text
JAWNY
  <
POUFNY
  <
TAJNY
  <
SEKRETNY
```

Plus orthogonal compartments/categories.

Bell–LaPadula applies:

> **NO READ UP**

> **NO WRITE DOWN**

Trusted declassification must be explicit, authorized, bounded and documented.

Do not bypass classification because two components happen to execute in the same process.

---

# 15. Control-Integrity Lattice

Control influence follows:

```text
L0 UNTRUSTED
  <
L1 CONSTRAINED
  <
L2 TRUSTED
  <
L3 AUTHORITATIVE
```

This governs CONTROL INFLUENCE, not ordinary evidence flow.

Upward reports may skip levels when transferring information/evidence.

Downward control moves exactly one level at a time.

Direct:

```text
L3 → L1
```

or:

```text
L3 → L0
```

requires UNANIMOUS approval of ALL L3 authorities.

Do not confuse high confidentiality with high control integrity.

They are separate dimensions.

---

# 16. Clark–Wilson Transformation

Consequential state changes follow the equivalent of:

```text
authorized decision
  ↓
certified / validated transformation procedure
  ↓
invariant checks
  ↓
bounded typed capability
  ↓
execution
  ↓
postcondition verification
  ↓
audit evidence
```

Authorization does not grant arbitrary bytes or arbitrary root execution.

Even unanimous L3 approval does NOT mean:

```text
execute arbitrary privileged shell
```

The transformation remains typed and bounded.

---

# 17. Phase 45 Control-Plane Lifecycle

Consequential mutations follow:

```text
intent
  ↓
resolve authority
  ↓
observe
  ↓
plan
  ↓
validate
  ↓
authorize
  ↓
execute
  ↓
verify
  ↓
record
```

No subsystem-specific bypasses.

This is compatible with the more operational form:

```text
DISCOVER
  ↓
RESOLVE TARGET
  ↓
VALIDATE
  ↓
PLAN
  ↓
AUTHORIZE
  ↓
CHECKPOINT / BACKUP IF WARRANTED
  ↓
EXECUTE
  ↓
OBSERVE
  ↓
VERIFY
  ↓
EVIDENCE
  ↓
RESULT
```

Not every trivial action requires each stage to exist as a separate class or function.

The semantic guarantees matter.

---

# 18. Phase 47 Task-Policy Ownership

OS task legality belongs to the canonical task-policy system:

```text
TaskIntent
  ↓
TaskDefinition
  ↓
TaskInstance
  ↓
TaskPlan
  ↓
TaskPolicyDecision
  ↓
TaskExecutionRef
  ↓
TaskOutcome
```

A typed task is NOT a shell command.

Do not bypass task policy by constructing command strings.

---

# 19. Phase 48 Context Rule

> **CONTEXT IS EVIDENCE, NOT AUTHORITY.**

Remember:

```text
Recent != relevant

Graph proximity != operational relevance

BEFORE != CAUSED_BY

Semantic candidate != fact

UNKNOWN != PASS
```

Context may inform resolution and analysis.

It must not silently create capability, authorization or verified truth.

---

# 20. Distributed Systems — Phase 51

Preserve:

```text
hostname != durable node identity

IP != identity

reachability != membership

membership != authorization
```

Remote execution must be revalidated at the target.

Do NOT implement distributed Rebuntu as SSH command fan-out.

Transport success does not prove remote semantic success.

Remote evidence must preserve node identity and provenance.

---

# 21. Associated Systems — Phase 52

Preserve:

```text
authentication != association != authorization

connectivity != trust

association != unrestricted trust

transport != trust
```

Remote trust does not automatically transfer local Phase 53 labels or authority.

Association must remain explicit and bounded.

---

# 22. Secret Discipline — Phase 37

> **SecretRef != SecretMaterial**

Never place plaintext secrets in:

* logs;
* timeline;
* diffs;
* prompts;
* model context;
* GUI diagnostics;
* IPC traces;
* audit reports;
* error messages;
* test output;

unless an isolated test fixture explicitly requires synthetic secret material.

Prefer references and controlled retrieval.

Do not accidentally turn diagnostic evidence into a secret exfiltration path.

---

# 23. C++ Engineering Expectations

## Language Standard

C++20 is the conservative baseline for the Ubuntu/GCC environment.

## Principles

Prefer:

* RAII;
* deterministic destruction;
* value semantics where appropriate;
* const correctness;
* explicit ownership;
* strong domain types;
* `enum class`;
* typed identifiers;
* narrow interfaces;
* composition;
* bounded concurrency;
* cancellation;
* backpressure;
* typed errors/results;
* testable providers;
* deterministic cleanup.

Use where appropriate:

* `std::unique_ptr`;
* `std::shared_ptr` only for genuine shared ownership;
* `std::weak_ptr`;
* `std::optional`;
* `std::variant`;
* `std::span`;
* `std::string_view`;
* `std::filesystem`;
* `std::chrono`;
* `std::jthread`;
* `std::stop_token`.

Do not use sophisticated C++ merely because it is available.

Prefer the simplest design preserving the required semantics.

## Avoid

* raw ownership ambiguity;
* manual `new/delete`;
* pervasive `shared_ptr`;
* global mutable state;
* uncontrolled singletons;
* unbounded queues;
* detached uncontrolled threads;
* stringly typed system operations;
* arbitrary shell execution;
* giant manager objects;
* unnecessary inheritance;
* hidden ownership;
* unnecessary heap allocation;
* parallel replacement architectures.

---

# 24. Resource Ownership

All native resources require explicit ownership and deterministic cleanup.

This includes:

* file descriptors;
* sockets;
* subprocesses;
* threads;
* locks;
* mappings;
* temporary files;
* IPC resources;
* D-Bus handles;
* provider handles;
* registrations.

Prefer RAII wrappers.

Failure paths must clean up correctly.

No resource should depend on reaching a successful happy-path return for cleanup.

Consider:

* partial construction;
* cancellation;
* exceptions where used;
* process termination;
* shutdown ordering.

---

# 25. Concurrency

Do not introduce concurrency merely because a task mentions asynchronous behavior.

Classify the requirement first:

* synchronous;
* blocking I/O;
* asynchronous I/O;
* event-driven;
* CPU-parallel;
* background worker;
* persistent service;
* externally supervised process.

Reuse existing Rebuntu runtime facilities.

Where native C++ concurrency is appropriate, prefer:

* `std::jthread`;
* `std::stop_token`;
* bounded queues;
* explicit backpressure;
* condition variables;
* atomics where justified;
* deterministic shutdown.

Avoid detached threads.

Cancellation must be explicit.

Queues must be bounded unless an unbounded structure has a demonstrated and documented justification.

---

# 26. Native Linux Philosophy

> **USE THE LOWEST APPROPRIATE NATIVE ABSTRACTION.**

Investigate before inventing.

Consider as appropriate:

* systemd;
* D-Bus;
* procfs;
* sysfs;
* configfs;
* cgroups v2;
* namespaces;
* Linux capabilities;
* seccomp;
* Unix sockets;
* signals;
* inotify;
* fanotify;
* epoll;
* eventfd;
* signalfd;
* netlink;
* journald;
* audit;
* perf;
* eBPF;
* native libraries;
* syscalls.

Native does NOT necessarily mean direct syscall.

It means choosing the correct stable Linux abstraction.

Do not parse command output when an appropriate reliable structured API exists.

---

# 27. Shell Execution Policy

DO NOT replace migrated Python system-management code with:

```cpp
std::system(...);
popen(...);
```

or:

```text
/bin/sh -c
bash -c
dynamically assembled command strings
eval
```

A C++ program that merely constructs Bash is NOT a successful native migration.

Prefer:

1. native API;
2. established library;
3. D-Bus;
4. kernel interface;
5. typed provider;
6. controlled external process only when appropriate.

When external process execution is appropriate, use the canonical Rebuntu process execution abstraction.

Require where applicable:

* explicit executable;
* structured argv;
* no shell interpolation;
* bounded stdout;
* bounded stderr;
* timeout;
* cancellation;
* exit-status capture;
* signal capture;
* process cleanup;
* process-group handling where needed;
* evidence;
* semantic postcondition verification.

Do not create another subprocess abstraction when one already exists.

---

# 28. Filesystem Safety

Consequential filesystem operations must be:

* explicit;
* narrowly scoped;
* validated;
* bounded;
* independently verified where appropriate.

Consider:

* symlinks;
* path traversal;
* TOCTOU;
* permissions;
* ownership;
* atomic replacement;
* temporary-file placement;
* fsync requirements;
* directory boundaries;
* descriptor-relative operations.

Prefer race-resistant Linux APIs where warranted.

DO NOT USE BROAD DELETION AS ARCHITECTURE.

Misplaced code must first be inspected.

If useful:

1. migrate it;
2. integrate it;
3. preserve functionality;
4. migrate callers;
5. verify replacement;

then consider retiring the old location.

Never recursively delete something merely because its path string appears correct.

---

# 29. Privilege and Authorization

Privilege is a mechanism.

Authorization is a policy decision.

> **PRIVILEGE != AUTHORIZATION**

Do not equate:

```text
running as root
```

with:

```text
authorized
```

Do not introduce hidden privilege escalation.

Never construct architecture equivalent to:

```text
user input
  ↓
shell
  ↓
sudo
```

or:

```text
model output
  ↓
sudo
```

Authorization must occur at the canonical deterministic Rebuntu boundary.

Scope must never silently widen from user/session context to system scope.

---

# 30. Operations and Canonical Runtime

Use canonical Rebuntu Operations/capabilities for consequential system actions where appropriate.

Do not bypass them from:

* CLI;
* GUI;
* shell language;
* semantic services;
* providers;
* automation;
* workflows;
* monitoring;
* external integrations.

Frontends express typed intent.

The canonical runtime performs authoritative execution.

---

# 31. GUI / CLI / Panel Guidance

Use:

```text
GUI / CLI / Panel / ask
  ↓
typed intent/request
  ↓
canonical Rebuntu capabilities/control plane
```

Never:

```text
GUI / CLI / Panel / ask
  ↓
privileged shell
  ↓
independent domain implementation
```

Presentation surfaces must not become independent system controllers.

---

# 32. Shell Language

The Rebuntu shell language is a frontend to Rebuntu.

It is NOT a second runtime.

Maintain:

```text
shell tokens / argv / stdin
  ↓
lexical + grammatical parsing
  ↓
typed intent / command IR
  ↓
subject + scope resolution
  ↓
validation
  ↓
authorization / policy
  ↓
canonical Operation / query / capability
  ↓
runtime
  ↓
observation / verification / evidence
  ↓
structured result
  ↓
renderer
```

Parsing and resolution must not execute consequential operations.

Do not hide providers or domain implementations inside giant Bash functions.

Do not parse human output back into authoritative state.

---

# 33. ML / Semantic Boundaries

Model output is not authoritative.

> **MODEL OUTPUT != AUTHORITY**

A model may produce:

* interpretation candidates;
* semantic annotations;
* hypotheses;
* recommendations;
* summaries;
* classifications;
* structured candidate intent.

It may not bypass:

* canonical vocabulary;
* parsing;
* target resolution;
* validation;
* scope rules;
* capability checks;
* policy;
* authorization;
* Operation schemas;
* runtime;
* verification.

Never implement:

```text
free text
  ↓
LLM
  ↓
sudo bash
```

or equivalent architecture.

Model-generated shell text must not become execution authority.

For every approved Python/ML boundary document:

1. why Python is allowed;
2. authority ceiling;
3. typed IPC/API contract;
4. authoritative state owner;
5. failure semantics;
6. security classification;
7. model-output validation requirements.

---

# 34. Communication and IPC

Choose communication mechanisms according to actual architectural need.

Options include:

* direct in-process calls;
* typed bounded queues;
* Unix sockets;
* D-Bus;
* pipes;
* shared memory where justified;
* eventfd;
* netlink for kernel interfaces.

Do NOT invent a universal bus.

Do not introduce process boundaries merely for conceptual modularity.

Process boundaries should correspond to genuine:

* privilege;
* isolation;
* lifecycle;
* resource;
* fault-containment;
* deployment;

requirements.

---

# 35. Error and Result Semantics

Distinguish where applicable:

* invalid input;
* unsupported capability;
* unavailable capability;
* acquisition failure;
* permission failure;
* authorization denial;
* timeout;
* cancellation;
* execution failure;
* verification failure;
* UNKNOWN observation;
* invariant violation;
* programming error.

Do not collapse operational results into booleans.

Do not use exceptions for ordinary state signaling where the established typed Result model is appropriate.

Preserve:

* evidence;
* provenance;
* verification status;
* uncertainty.

---

# 36. Platform Guidance — Phase 50

Rebuntu's mature reference implementation is deeply Linux-native.

However:

> **PLATFORM DOES NOT DEFINE ARCHITECTURE**

Portable semantic contracts should remain platform-neutral where required.

Native providers supply platform mechanisms.

Do NOT create:

* Windows as translated Linux commands;
* WSL as portability architecture;
* one giant `Platform` interface;
* `#ifdef` forests in domain logic.

Keep domain semantics separate from platform mechanism.

---

# 37. Templates and Generators

Templates can regenerate stale architecture.

Audit generators and templates when architectural conventions change.

If repository templates generate:

* Python-first production modules;
* Python service skeletons;
* obsolete directory layouts;
* obsolete `AGENTS.md`;
* parallel runtime architecture;

update or retire them.

Do not fix generated instances while leaving the generator capable of recreating the defect.

---

# 38. CI and Developer Automation

CI must build and test the canonical native runtime.

Do not allow green Python-only CI to imply Rebuntu production health.

Canonical CI should exercise as appropriate:

* CMake configure;
* native build;
* CTest;
* static analysis;
* sanitizer configurations;
* integration tests;
* security-sensitive tests.

Approved Python boundaries should retain their own appropriate tests.

---

# 39. Testing Requirements

A feature is NOT complete merely because it compiles.

Required test categories where applicable include:

* unit tests;
* integration tests;
* contract tests;
* property tests;
* regression tests;
* negative/failure tests;
* security tests;
* concurrency tests;
* crash/restart tests;
* malformed-input tests;
* cancellation tests;
* timeout tests;
* lifecycle tests;
* idempotency tests;
* postcondition verification tests;
* resource-cleanup tests.

For C++ use where practical:

* ASan;
* UBSan;
* TSan;
* compiler warnings;
* static analysis;
* fuzzing for exposed parsers/protocols.

Do NOT weaken tests to obtain green output.

Do NOT replace real safe integration tests entirely with mocks.

---

# 40. Developer Host Safety

Tests must not mutate the real developer workstation configuration.

Do not modify real:

* `/etc`;
* users;
* groups;
* system services;
* firewall;
* networking;
* disks;
* filesystems;
* mounts;
* boot configuration;
* GPU configuration;
* unrelated processes.

Prefer:

* temporary roots;
* fixtures;
* fake filesystem trees;
* dependency injection;
* controlled subprocesses;
* isolated sockets;
* controlled provider fixtures.

Read-only host observation may be used where safe and useful.

---

# 41. Acceptance Criteria Are Binding

When implementing a phase/task:

1. read the complete specification;
2. extract its requirements;
3. inspect existing implementation;
4. search for overlap;
5. implement the requirements;
6. integrate callers;
7. add tests;
8. build;
9. run tests;
10. compare implementation against the original acceptance criteria;
11. perform the required audits;
12. document genuine deferrals.

Do not silently implement a small subset of a large phase and report the phase as complete.

Use honest states:

* `COMPLETE`;
* `PARTIALLY COMPLETE`;
* `BLOCKED`.

Explain partial completion precisely.

---

# 42. No Placeholder Completion

"Code exists" is NOT completion.

Do not satisfy implementation requirements with:

* empty classes;
* placeholder methods;
* TODO-only scaffolding;
* fake interfaces;
* hardcoded success;
* `return true`;
* architecture-only skeletons;
* mocks presented as production implementation.

Mocks/stubs are acceptable only where genuinely necessary and must be clearly identified.

A requested implementation means:

> **working implementation integrated into Rebuntu**

unless the task explicitly asks only for design/scaffolding.

---

# 43. Completion Checklist

Before declaring implementation complete verify:

1. implementation exists in C++ or an explicitly approved boundary;
2. production callers use it;
3. build integration is complete;
4. runtime reachability is verified;
5. tests cover the relevant behavior;
6. postconditions are verified where required;
7. security compatibility is preserved;
8. documentation matches reality;
9. no ambiguous shadow implementation remains;
10. no duplicate canonical implementation remains;
11. acceptance criteria were reviewed individually.

---

# 44. Build Verification

After relevant C++ changes normally perform:

```text
CMake configure
  ↓
build
  ↓
relevant tests
  ↓
full CTest where practical
```

Do not leave the repository knowingly uncompilable.

Warnings introduced by the current task should be treated as defects unless explicitly justified.

Do not silence warnings globally merely to produce a clean build.

---

# 45. Git Safety

Inspect Git state before substantial modifications.

Never discard unrelated user changes.

The following destructive operations are prohibited unless the user explicitly authorizes the exact operation with full understanding of its consequences:

```text
git reset --hard
git clean -fd
git clean -fdx
git checkout -- .
git restore .
```

Keep changes scoped to the task.

Prefer a commit after each completed task/phase unless the user specifies another workflow.

Before committing:

* inspect the diff;
* build;
* run relevant tests;
* check for accidental files;
* check generated artifacts;
* ensure unrelated modifications are preserved.

Do not commit knowingly broken states merely to satisfy commit cadence.

---

# 46. Documentation

Documentation must describe actual behavior.

Do not document planned functionality as already implemented.

When implementation is partial, say so.

Keep architecture documentation synchronized with canonical implementation.

Avoid creating competing architectural documents that independently claim authority.

---

# 47. Local AGENTS.md Files

This root file defines repository-wide rules.

More specific `AGENTS.md` files may exist deeper in the tree.

When working in a subtree:

1. read this root contract;
2. discover all applicable nested `AGENTS.md`;
3. apply local rules in addition to this document.

Scope matters.

Local rules may specialize this contract.

They must not silently overturn fundamental:

* safety;
* verification;
* security;
* state-ownership;
* architectural;

invariants.

---

# 48. Agent Discovery Checklist

Before implementation verify:

1. `git status`;
2. applicable `AGENTS.md`;
3. relevant subtree;
4. architecture documentation;
5. applicable phase specifications;
6. semantic search for existing patterns;
7. capability inventory;
8. types/contracts;
9. providers/adapters;
10. callers;
11. authoritative state ownership;
12. native OS mechanism;
13. security boundary;
14. tests;
15. configuration;
16. acceptance evidence requirements.

Do not start generating architecture before completing enough discovery to understand the existing system.

---

# 49. Agent Completion Checklist

After implementation verify:

1. implementation is real and complete to the claimed extent;
2. production callers are integrated;
3. build system is integrated;
4. runtime reachability is verified;
5. relevant tests pass;
6. postcondition verification exists where required;
7. security compatibility is preserved;
8. documentation is updated;
9. duplicate implementations were removed or explicitly accounted for;
10. shadow state was not created;
11. resources have deterministic ownership;
12. cancellation/shutdown semantics are correct;
13. phase acceptance criteria were reviewed;
14. remaining limitations are explicitly reported.

---

# 50. Source Tree Placement Rules

Before adding any source component, determine:

1. **What kind of entity is this?**
   - Is it a System, Module, Unit, Interface, Adapter, Script, or something else?
   - Does it represent a top-level responsibility (System)?
   - Does it provide reusable functionality within a system (Module)?
   - Does it implement specific behavior (Unit)?

2. **Is the proposed name actually a ROLE rather than a structural type?**
   - `Monitor`, `Scheduler`, `Validator` are ROLES
   - Roles may be expressed as metadata or in registries, not necessarily directory names

3. **What domain does it operate on?**
   - Domain (storage, network, process) is orthogonal to structure
   - Avoid embedding domains in primary path hierarchy

4. **Does an equivalent abstraction already exist?**
   - Search semantically before creating new directories/classes
   - Prefer extending existing abstractions over creating new ones

5. **Is this specification or runtime realization?**
   - Definitions (TaskDefinition) vs Instances (Job, OperationInstance)
   - Keep these distinct conceptually and structurally

6. **What may depend on it? What may it depend on?**
   - Units should not own system lifecycle
   - System/core must not depend arbitrarily on optional modules
   - Scripts should invoke stable functionality rather than duplicate it

7. **Is this implementation or integration?**
   - Native Linux integration belongs in adapters/providers
   - Core runtime logic belongs in core/system modules

8. **What is the authority ceiling of this component?**
   - Who owns authoritative state?
   - What verification is required for state changes?

If placement is unclear:

> **DO NOT CREATE A CONVENIENT RANDOM DIRECTORY.**

Investigate and document the ambiguity.

Consult:

# 51. Final Engineering Principle

This is the one Rebuntu.

It is C++-native.

Architecture defines source ownership, not language.

For every implementation decision ask:

1. What semantic requirement are we satisfying?
2. Does Rebuntu already implement all or part of it?
3. Who owns the authoritative state?
4. What is the narrowest correct abstraction?
5. What does Linux already provide?
6. Why does this need a new component?
7. Who owns every resource?
8. How is cancellation handled?
9. How does shutdown behave?
10. How is failure represented?
11. What authority does this component actually possess?
12. How is success independently verified?
13. What evidence supports the result?
14. How will this be tested safely?
15. Have all production callers reached the canonical implementation?

Prefer:

> **CORRECT SEMANTICS OVER CONVENIENT SHORTCUTS**

> **EXISTING ARCHITECTURE OVER DUPLICATION**

> **NATIVE LINUX INTERFACES OVER TEXTUAL EMULATION**

> **TYPED C++ CONTRACTS OVER STRINGLY-TYPED BEHAVIOR**

> **COMPOSITION OVER UNNECESSARY INHERITANCE**

> **EXPLICIT OWNERSHIP OVER IMPLICIT LIFETIME**

> **BOUNDED CONCURRENCY OVER UNCONTROLLED PARALLELISM**

> **VERIFIED OUTCOMES OVER OPTIMISTIC SUCCESS**

> **WORKING IMPLEMENTATION OVER SCAFFOLDING**

> **ONE AUTHORITATIVE REBUNTU OVER PARALLEL ARCHITECTURES**

---

# 52. Operational Reasoning Rules (Phase 0.2)

Before implementing runtime functionality, ask these questions:

## 1. Specification vs Instance

1. Is this a static specification or runtime instance?
   - If specification: is it reusable, immutable, and stable?
   - If instance: does it have identity, lifecycle state, and temporal existence?

2. What is the distinction between:
   - TaskDefinition (specification) → Job (instance)?
   - ServiceConfig (specification) → ServiceInstance (instance)?

## 2. State Dimensions

3. Which orthogonal state dimension applies?
   - LifecycleState: stage of existence?
   - WorkState: current activity type?
   - ControlState: administrative control?
   - ReadinessState: can accept work now?
   - HealthState: sustained quality?
   - RecoveryState: corrective action in progress?

4. Does ready() = (readiness == kReady) AND (health == kHealthy)?

## 3. Execution Model

5. What is the execution chain for this entity?
   - Unit + parameters → Task → submit → Job → execute → Result
   - Does it have a Runner? Executor? Dispatcher?

6. How do we distinguish:
   - Execution success (exit code, no crash) vs Verification success (postconditions met)?

## 4. Request/Event/Signal/Trigger

7. What communication pattern applies?
   - Request: semantic ask for action (operation + target + parameters)?
   - Event: immutable statement that something occurred (evidence-backed)?
   - Signal: lightweight control indication (pause/resume/cancel/reconfigure)?
   - Trigger: Event + Condition → activation decision?

8. Is this a control instruction or an observation? Don't confuse:
   - Signal (control) vs Event (observation)
   - Request (ask) vs Event (report)

## 5. Retry & Timeout

9. What retry policy applies?
   - max_attempts, exponential_backoff, retryable_error_codes?

10. What timeout policy applies?
    - operation_timeout, verification_timeout?
    - cancel_on_timeout? retry_on_timeout?

## 6. Coordination & Dependencies

11. Does this have dependencies on other entities?
    - Structural (code-level)
    - Implementation (runtime needs)
    - Runtime (lifecycle ordering)
    - Ordering (A before B)
    - Readiness (B can start when A ready)
    - Resource (shared lock/queue/buffer)?

## 7. Recovery Patterns

12. Which recovery pattern applies if this fails?
    - Retry: same operation again
    - Rollback: return to prior state
    - Restore: recreate from preserved source
    - Repair: modify to valid state
    - Failover: switch to alternate
    - Degrade: continue with reduced functionality?

## 8. Evidence & Verification

13. What evidence will verify success?
    - Observation (what was observed)
    - Fact (observed statement with provenance)
    - Assertion/Condition (evaluated proposition)
    - Evidence (provenance-bearing observation supporting claims)

14. Is verification separate from execution?
    - Operation may complete but verification may fail
    - Exit code 0 proves only exit code, not desired state achieved

## 9. Native Linux Integration

15. What native mechanism does this use?
    - systemd for lifecycle/timers/scheduling?
    - inotify/fanotify for filesystem events?
    - udev/netlink for device events?
    - D-Bus for IPC/controls?
    - signalfd/pidfd for cancellation?

## 10. Automation vs Workflow

16. Is this automation or workflow?
    - Automation: when/why activation happens (triggers on conditions)
    - Workflow: how execution progresses after activation (phases/steps)

## 11. Runtime Ownership

17. What does runtime own vs what belongs elsewhere?
    - Lifecycle management → runtime
    - State persistence → state management
    - Policy enforcement → policy engine
    - Security authorization → security subsystem

---

**REMEMBER:**

**THIS PROJECT IS REBUNTU.**

**THERE IS ONE REBUNTU.**

**REBUNTU IS C++-NATIVE.**

**C++ OWNS AUTHORITATIVE DETERMINISTIC SYSTEM MACHINERY.**

**PYTHON EXISTS ONLY AT EXPLICIT, JUSTIFIED BOUNDARIES.**

**DO NOT RECREATE RETIRED PYTHON ARCHITECTURE.**

**DO NOT CREATE SHADOW TRUTH.**

**DATA IS NOT CONTROL.**

**MODEL OUTPUT IS NOT AUTHORITY.**

**UNKNOWN IS NOT SUCCESS.**

**EXECUTION IS NOT VERIFICATION.**

# SOURCE TREE PRESERVATION — CRITICAL

`src/` IS ALREADY THE REBUNTU ARCHITECTURE ROOT.

DO NOT CREATE:

    src/
    src/src/
    src/cpp/
    src/python/
    cpp/src/
    python/src/

as a new umbrella architecture root.

The fact that the project is named Rebuntu does NOT imply that source code belongs
under `src/`.

The fact that C++ is the primary language does NOT imply that source code belongs
under a language-specific subtree.

Existing architectural ownership under `src/` is authoritative.

Before creating ANY new top-level directory under `src/`:

1. recursively inspect the existing `src/` tree;
2. identify the narrowest existing architectural owner;
3. search for semantically equivalent functionality;
4. place the implementation into that existing owner whenever possible;
5. create a new top-level subsystem ONLY when no existing subsystem can correctly
   own the functionality and the architectural need is demonstrated.

NEVER create an umbrella directory merely to "organize" existing Rebuntu code.

In particular:

    src/

is PROHIBITED as an architecture root.

If `src/` already exists as the result of an incorrect migration, DO NOT
simply delete it.

Instead:

    INVENTORY
      ↓
    CLASSIFY EACH FILE BY SEMANTIC OWNERSHIP
      ↓
    FIND EXISTING CANONICAL DESTINATION
      ↓
    MIGRATE / MERGE IMPLEMENTATION
      ↓
    MIGRATE CALLERS / INCLUDES / CMAKE / TESTS
      ↓
    VERIFY BUILD AND TESTS
      ↓
    REDISCOVER REFERENCES
      ↓
    REMOVE EMPTY OBSOLETE WRAPPER ONLY AFTER FIXED POINT

No useful implementation may be lost merely to restore the directory structure.

---

## Phase 0.0 addendum (binding for this repository)

- **Primary structural package is `src/system/`** (not `src/`). Rebuntu
  is the project; `system` is the structural package. See
  `docs/discoveries/0001-primary-package-system.md`.
- **C++ namespace is `rebuntu::`** (e.g. `rebuntu::core`), not `system::`
  (hard C++ constraint: `::system()` from `<cstdlib>`). See
  `docs/discoveries/0002-system-namespace.md`.
- **Roles are not directories.** Monitor/Scheduler/Controller/Engine are roles a
  component performs, not structural kinds. See
  `docs/discoveries/0003-role-vs-structural-type.md`.
- **Record architectural discoveries** in `docs/discoveries/` using the
  DISCOVERY / CANDIDATE / ACCEPTED / DEFERRED / REJECTED / SUPERSEDED
  vocabulary (format in `docs/discoveries/README.md`). Generalize only when two
  or more independent uses justify it.
- **Statuses are honest:** every capability claim must be CURRENT / RESERVED /
  PLANNED / CANDIDATE / HISTORICAL. A directory is not a capability.

## Phase 0.1 addendum (Structural Taxonomy Expansion)

### Structural families (directories)

---

## 52. Operational Reasoning Rules

Before implementing runtime functionality, ask these questions:

1. **Is this specification or runtime state?**
   - Specification: static declaration of what something is (immutable, reusable)
   - Runtime instance: concrete occurrence with identity, lifecycle, temporal existence
   - Examples: TaskDefinition vs Job, ServiceConfig vs ServiceInstance

2. **What activates it?**
   - Request (semantic ask for action)
   - Event (immutable statement that something occurred)
   - Schedule (temporal activation)
   - Trigger (activation decision when criteria satisfied)

3. **Who owns its lifecycle?**
   - Runtime manages instantiation, initialization, activation, termination
   - Native Linux mechanisms own their native lifecycles (systemd for services, etc.)

4. **Does Linux/systemd already own that lifecycle?**
   - If yes: query/observe rather than control
   - If no: Rebuntu runtime may manage it

5. **Is it synchronous or asynchronous?**
   - Synchronous: caller waits for completion
   - Asynchronous: execution continues independently, result observed later

6. **What is the Result?**
   - Structured outcome with:
     * Outcome (SUCCESS/FAILURE/CANCELLED/TIMED_OUT)
     * Evidence (provenance-bearing observations)
     * Timing information
     * Verification status

7. **How is success verified?**
   - Execution success ≠ Verification success
   - Exit code 0 proves only exit code, not desired state achieved
   - Postcondition verification required for consequential operations

8. **What Evidence supports the result?**
   - Observed values with source provenance
   - Command/API results
   - Before/after snapshots
   - Timestamps and measurements

9. **What happens on timeout?**
   - Timeout ≠ failure (could be retryable)
   - Cancel? Retry? Continue in degraded mode?
   - Separate operation_timeout and verification_timeout policies

10. **What happens on cancellation?**
    - Cooperative cancellation preferred
    - Native: signalfd/pidfd for signals
    - Bounded operations that can clean up

11. **Is retry safe?**
    - Idempotent operations are retry-safe
    - Non-idempotent may need compensation/rollback
    - RetryPolicy with exponential backoff

12. **Is the operation idempotent?**
    - Repeating is safe and produces same result
    - Critical for recovery and automation reliability

13. **Is it reversible?**
    - Naturally reversible: yes
    - Rollback-supported: requires undo mechanism
    - Compensatable: can counteract effect with another action
    - Irreversible: must avoid or use with extreme caution

14. **What resources does it require?**
    - CPU, memory, disk I/O, network bandwidth
    - Device access (GPU, storage path)
    - Resource constraints must be declared upfront

15. **What is the authoritative source of state?**
    - Linux kernel: process/device state
    - systemd: service lifecycle state
    - filesystem: file/directory state
    - Rebuntu: Rebuntu-specific durable state
    - No shadow state - query authoritative sources directly

16. **Does this require IPC?**
    - Local in-process calls preferred when possible
    - Unix sockets, D-Bus for cross-process
    - Native Linux mechanisms where appropriate

17. **Does a native Linux primitive already provide the mechanism?**
    - Use systemd timers instead of custom scheduler
    - Use inotify/fanotify instead of polling filesystems
    - Use udev/netlink for device events
    - Use signalfd/pidfd for cancellation
    - Use cgroups for resource limits

18. **Is a new abstraction actually necessary?**
    - Extend existing abstractions first
    - Avoid creating duplicate mechanisms

---

## Phase 0.2 addendum (Operational Grammar)

Before adding any new source component, identify which structural family it
belongs to:

| Directory | Responsibility | When to use |
|---|---|---|
| `src/interfaces/` | Typed contracts and protocols | Declaring *what* without implementation |
| `src/adapters/` | Native mechanism integration | Translating between Rebuntu and Linux APIs |
| `src/support/` | Reusable utilities | Logging, config, validation, serialization |
| `src/system/units/` | Unit architecture (Phase 0.7) | Structural catalog for executable operational definitions |

### Source tree placement checklist

Before adding a new source component, determine:

1. **What kind of entity is this?**
   - Is it a System, Module, Unit, Interface, Adapter, Support module, or
     something not yet represented?
   - Does it represent a top-level responsibility (System)?
   - Does it provide reusable functionality within a system (Module)?

2. **Is the proposed name actually a ROLE rather than a structural type?**
   - `Monitor`, `Scheduler`, `Validator` are ROLES
   - Roles may be expressed as metadata or in registries, not necessarily directory names

3. **What domain does it operate on?**
   - Domain (storage, network, process) is orthogonal to structure
   - Avoid embedding domains in primary path hierarchy

4. **Does an equivalent abstraction already exist?**
   - Search semantically before creating new directories/classes
   - Prefer extending existing abstractions over creating new ones

5. **Is this specification or runtime realization?**
   - Definitions (TaskDefinition) vs Instances (Job, OperationInstance)
   - Keep these distinct conceptually and structurally

6. **What may depend on it? What may it depend on?**
   - Units should not own system lifecycle
   - System/core must not depend arbitrarily on optional modules
   - Support must not depend on high-level semantics
   - Interfaces must not contain runtime implementation

7. **Is this implementation or integration?**
   - Native Linux integration belongs in adapters/providers
   - Core runtime logic belongs in core/system modules

8. **What is the authority ceiling of this component?**
   - Who owns authoritative state?
   - What verification is required for state changes?

If placement is unclear:

> **DO NOT CREATE A CONVENIENT RANDOM DIRECTORY.**

Investigate and document the ambiguity.

Consult:
- `docs/VOCABULARY.md` — term definitions and categories
- `docs/ONTOLOGY.md` — relationships between concepts
- `docs/ARCHITECTURE.md` — dependency directions and structural principles

Phase 0.1 must land inside this structure without an architectural exception.

---

## Phase 5 Observation/Discovery — C++-Native System Inventory

Rebuntu's observation and discovery system is **C++-native**. All system state
acquisition, inventory assembly, hardware enumeration, process/service discovery,
and host-fact collection belongs in C++ adapters/providers, not Python or shell.

### 53.1 Observation != Inference

> **OBSERVATION PRODUCES EVIDENCE; INFERENCE PRODUCES HYPOTHESES**

Observation is reading native Linux state directly from authoritative sources.
Inference is deriving additional facts from observations using computation.

```text
Native Source (procfs/sysfs/udev/D-Bus/netlink)
    ↓ direct read
OBSERVED STATE (Fact with Evidence)
    ↓ bounded computation
INFERENCE (Hypothesis / Annotation / Recommendation)
```

**Rules:**

- Observation produces **Evidence** (provenance-bearing, bounded, secret-free)
- Inference produces **Annotations**, **Hypotheses**, or **Recommendations**
- Model output is UNTRUSTED input until validated by deterministic mechanisms
- No inference chain may bypass canonical vocabulary/parsing/authorization

### 53.2 Stable Identity Rules

> **NAME != IDENTITY; PATH != IDENTITY; PID != DURABLE PROCESS IDENTITY**

Linux process/file identifiers have temporal existence only. Rebuntu must use
stable semantic identifiers for authoritative inventory.

| Concept | Linux Source | Durability | Rebuntu Rule |
|---------|--------------|------------|--------------|
| PID | `/proc/[pid]` | Reused after exit | **NOT durable** |
| Process name | `comm`, `cmdline` | Changes at exec() | **NOT durable** |
| Path | VFS path | Changes on rename/move | **NOT durable** |
| MAC address | sysfs/netlink | May change on hardware swap | **May be stable** |
| Serial number | sysfs/DMI | Hardware permanent | **DURABLE** |
| UUID/GUID | filesystem/device | Persistent | **DURABLE** |

**Rules:**

- PIDs are ephemeral runtime handles; never use as authoritative identity
- Process names can change during lifetime; not stable identifiers
- File paths can be renamed/symlinked; not stable references
- Use hardware serial numbers, UUIDs, DMI IDs for durable device identification
- When a stable identifier doesn't exist, create one (e.g., generate a Rebuntu ID)

### 53.3 Native Provider Preference

> **USE NATIVE LINUX MECHANISMS DIRECTLY; NO SHELL COMMAND PARSING FOR SYSTEM STATE**

System observation must use the appropriate native Linux interface:

| Observation | Native Mechanism | PROHIBITED |
|-------------|------------------|------------|
| Process list | `/proc` filesystem (not `ps aux`) | `ps`, `top`, `htop` parsing |
| Service state | systemd D-Bus API (not `systemctl status`) | shell systemctl parsing |
| Device info | sysfs udev properties | `lshw`, `hwinfo`, `lsusb -v` |
| Mount points | `/proc/mounts` or `/proc/self/mountinfo` | `mount` command output |
| Network interfaces | netlink RTNETLINK (not `ip addr`) | `ip`, `ifconfig` parsing |
| Kernel logs | `/dev/kmsg` or journald D-Bus | `dmesg` parsing |
| Disk info | sysfs block attributes | `lsblk`, `fdisk`, `parted` |
| CPU topology | `/proc/cpuinfo`, sysfs topology | `lscpu` parsing |
| Memory info | `/proc/meminfo` | `free`, `vmstat` |

**Rules:**

- Use direct file reads from procfs/sysfs where possible
- Use systemd D-Bus API for service lifecycle queries
- Use udev/netlink for device enumeration and properties
- Native interfaces are **authoritative**, parsed output is **derived evidence**
- If native interface doesn't expose required data, request addition to Linux kernel

### 53.4 Discovery Freshness Semantics

> **DISCOVERY MUST BE BOUNDED, CANCELLABLE AND FRESHNESS-AWARE**

Discovery is not a one-time activity; it's continuous state acquisition with
freshness requirements and bounded resource usage.

```text
Discovery Request
    ↓
Freshness Check (cache expiry, TTL)
    ↓
Cache Hit? → return cached evidence with timestamp
    ↓
Cache Miss? → execute acquisition (bounded by timeout/limits)
    ↓
Produce Observation + Freshness Evidence
```

**Freshness Dimensions:**

- `freshness_timestamp` — when observation was made (system_clock::now())
- `cache_ttl_ms` — how long result is considered fresh
- `acquisition_duration_ms` — time spent collecting

**Rules:**

- Every observation must include acquisition timestamp
- Consumers decide freshness tolerance; do not assume cache validity
- Discovery requests must have explicit timeouts and cancellation support
- Discovery may be bounded (max processes, max services, max evidence records)
- UNKNOWN state ≠ PASS; UNKNOWN means "no valid evidence available"

### 53.5 Evidence Chain Principles

> **EVIDENCE IS DATA, NOT CONTROL**

The evidence chain establishes trust without conferring authority:

```text
Observed Value (procfs/sysfs reading)
    ↓
Evidence Record (provenance + timestamp + source reference)
    ↓
Assertion/Condition Evaluation
    ↓
Verification Result (PASS/FAIL/NONE_APPLICABLE)
```

**Rules:**

- Evidence records must preserve **provenance**: who, what, when, how
- Evidence is never sufficient to authorize; it only informs decisions
- Authorization requires explicit policy evaluation against evidence
- No evidence may be generated without an authorization decision first

### 53.6 C++-Native Discovery Ownership

> **NO PYTHON/SHELL INVENTORY SYSTEMS**

System inventory and discovery is part of Rebuntu's authoritative runtime,
implemented in C++. This includes:

**C++-Owned Discovery:**
- Process enumeration and metadata
- Service/unit state and properties
- Device/hardware inventory (CPU, memory, storage, GPU, network)
- Filesystem/mount topology
- Network interfaces and configuration
- Systemd unit states
- Kernel module information

**Prohibited Python/Shells for Discovery:**
- Inventory managers or hardware scanners in Python
- Shell scripts parsing `lshw`, `dmidecode`, `nvidia-smi`
- Python-based network topology discovery
- Custom service enumeration daemons

**Python may be used only at explicit boundaries:**

- ML/semantic classification of observed state (after C++ acquisition)
- Experimental research prototypes (not production authority)
- Testing fixtures and test infrastructure
- Development tooling that doesn't affect production state

### 53.7 Discovery Boundedness

> **DISCOVERY MUST NOT PRODUCE EVENT STORMS OR RESOURCE EXHAUSTION**

Discovery operations must be bounded:

```cpp
struct DiscoveryBounds {
    size_t max_processes = 1000;           // Maximum processes to enumerate
    size_t max_services = 500;             // Maximum systemd units
    size_t max_devices = 1000;             // Maximum devices
    size_t max_evidence_per_request = 100; // Maximum evidence records
    
    std::chrono::milliseconds timeout_ms{30000};     // Total discovery timeout
    std::chrono::milliseconds per_source_timeout_ms{5000}; // Per-source limit
};
```

**Rules:**

- Discovery must respect resource limits (process count, record counts)
- Timeouts apply at both overall and per-source levels
- Discovery may be cancelled partway through; partial results must be valid
- Backpressure mechanisms prevent discovery storms from overwhelming consumers

### 53.8 Identity Resolution Flow

Before making authoritative decisions based on system state:

```text
1. OBSERVE (from native source)
   ↓
2. RESOLVE IDENTIFIERS (map ephemeral to stable where possible)
   ↓
3. NORMALIZE (apply canonical naming, deduplicate)
   ↓
4. VALIDATE (check constraints, invariants)
   ↓
5. AUTHORIZE (policy decision based on validated state)
   ↓
6. EXECUTE (with typed capability, not arbitrary shell)
```

**Identity Resolution Rules:**

- PIDs → ephemeral handles only; use for observation windowing
- Process names → transient attributes; never authoritative
- Device serials/UUIDs → durable identifiers; prefer where available
- Generate Rebuntu IDs for entities lacking stable Linux identity

---

## 54. Phase 5 Observation/Discovery Completion Checklist

### Acceptance Criteria for Discovery Systems:
- [x] Native Linux source access (procfs/sysfs/udev/systemd D-Bus)
- [ ] No Python/shell inventory implementation
- [ ] Stable identity resolution (PID != durable ID)
- [ ] Bounded discovery (limits on processes, records, time)
- [ ] Freshness tracking with timestamps and TTLs
- [ ] Cancellation support for long-running discovery
- [ ] Evidence chain: observation → evidence → verification
- [ ] Backpressure mechanisms to prevent storms
- [ ] Unknown state handling (not treated as success)

### Files Reference

| File | Purpose |
|------|---------|
| `src/system/observation/bounds.hpp` | Memory bounds configuration |
| `src/system/evidence/collector.hpp` | Evidence collection interface |
| `src/adapters/procfs/*` | Process filesystem native access |
| `src/adapters/sysfs/*` | System filesystem native access |
| `src/adapters/udev/*` | udev device enumeration |
| `src/adapters/systemd/service/*` | systemd D-Bus service queries |

---

## 55. Phase 0.2 Status

**Status: COMPLETE**
- ✅ Six orthogonal state dimensions (lifecycle, work, control, readiness, health, recovery)
- ✅ Clear semantic distinctions between all key concepts
- ✅ Lifecycle transitions documented
- ✅ Verification model with evidence chain
- ✅ RetryPolicy and TimeoutPolicy specified
- ✅ Execution chain: Unit → Task → Job → Execution → Result
- ✅ Request/Event/Signal/Trigger distinctions clear
- ✅ Automation vs Workflow distinction established
- ✅ Reconciliation vs Recovery distinction established

**Ready for:** Phase 0.3+ implementation of native semantic model service and domain-specific units.
