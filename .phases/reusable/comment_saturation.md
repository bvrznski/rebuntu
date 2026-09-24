TASK: REPEATABLE C++ SOURCE COMMENT SATURATION PASS

Repository:
    /home/bvrznski/rebuntu

Scope:
    /home/bvrznski/rebuntu/src

This is a REPEATABLE saturation pass.

It is explicitly designed to be executed many times over the lifetime of the
repository.

Each execution must inspect the CURRENT implementation and improve explanatory
commentary wherever important semantics still require reverse-engineering.

The pass MUST converge.

Repeated execution must NOT blindly add more comments to already well-documented
code.

======================================================================
PRIMARY OBJECTIVE
======================================================================

Transform Rebuntu's C++ source into an "executable engineering document":

    implementation
    +
    locally recoverable architecture
    +
    invariants
    +
    authority boundaries
    +
    evidence semantics
    +
    state transitions
    +
    concurrency assumptions
    +
    failure semantics
    +
    platform constraints
    +
    supported historical rationale
    +
    warnings against incorrect simplifications

The purpose is NOT:

    maximize comment count

The purpose IS:

    minimize semantic knowledge that exists only implicitly in code or in the
    original author's head.

A competent engineer opening an unfamiliar source file months later should be
able to understand the major design and behavioral constraints without first
reverse-engineering every implementation detail.

======================================================================
0. READ THE RULES FIRST
======================================================================

Before editing anything:

1. Read repository root AGENTS.md.

2. Recursively discover and read every applicable nested AGENTS.md for the
   source subtree being processed.

3. Read applicable repository structural metadata, including where present:

       __tree__
       __base__
       __meta__
       __load__
       STRUCTURE.md
       README
       architecture documentation
       relevant TASK.md
       relevant tests

4. Locate and obey the project's canonical:

       C++ COMMENTING, EXPLANATION, AND LOCAL DOCUMENTATION STANDARD

The standard is binding.

This task operationalizes that standard; it does not replace or weaken it.

======================================================================
1. THIS IS NOT AN IMPLEMENTATION-CHANGE PASS
======================================================================

The primary operation permitted by this task is:

    ADD / IMPROVE / CORRECT / RELOCATE COMMENTS

Do NOT intentionally change runtime behavior.

Do NOT:

- redesign APIs;
- rename public symbols merely for style;
- change algorithms;
- change state machines;
- alter synchronization;
- change persistence behavior;
- change system calls;
- change policy;
- change security behavior;
- "clean up" unrelated implementation;
- delete source files;
- move source files;
- introduce new abstractions merely to make comments easier.

Minimal non-behavioral edits are allowed only where required to keep comments
correctly attached to their code.

If inspection reveals an implementation bug:

    DO NOT silently fix it as part of this pass.

Instead:

    document the finding in the final report;

and, where appropriate and truthful, add a TODO/FIXME only if repository policy
allows it.

The comment saturation diff should remain overwhelmingly commentary.

======================================================================
2. PROCESS THE REAL IMPLEMENTATION, NOT FILE NAMES
======================================================================

Recursively inspect C++ implementation under src/.

At minimum consider:

    *.hpp
    *.hh
    *.hxx
    *.h
    *.cpp
    *.cc
    *.cxx
    *.ipp
    *.inl
    C++20 module files if present

Exclude:

- generated files;
- vendored/third-party code;
- build directories;
- external dependencies;
- generated bindings;

unless repository metadata explicitly identifies them as maintained Rebuntu
source.

Do not assume every file requires modification.

A sufficiently documented file should be left unchanged.

======================================================================
3. BUILD A SEMANTIC MODEL BEFORE COMMENTING
======================================================================

Before adding comments to a non-trivial file, understand it.

Inspect as necessary:

- corresponding header/implementation pair;
- callers;
- callees;
- base classes/interfaces;
- implementations of interfaces;
- tests;
- configuration;
- state definitions;
- neighboring components;
- native API contracts;
- applicable architecture documentation.

Never infer architectural rationale merely from a symbol name.

Search the repository when necessary.

The task is:

    recover semantics
        THEN
    document semantics

not:

    guess semantics
        THEN
    manufacture plausible comments.

======================================================================
4. FILE-LEVEL DOCUMENTATION
======================================================================

For every architecture-significant source/header file, determine whether a
reader can quickly answer:

    Why does this file exist?
    Which subsystem owns this responsibility?
    What is authoritative here?
    What is deliberately outside its responsibility?
    Which invariants does it preserve?
    Which native Linux mechanism remains authoritative underneath it?
    Which other Rebuntu layer consumes its output?
    What are the important failure semantics?

Where these answers are non-obvious, add a concise file-level engineering
comment.

Do not paste generic project descriptions into every file.

The comment must describe THIS file.

======================================================================
5. MAJOR SECTION HEADERS
======================================================================

Identify important conceptual regions and make them visually discoverable.

Use the project's preferred form, for example:

// ---------------------------------------------------------------------------
// Reconciliation decision
//
// Explanation...
// ---------------------------------------------------------------------------

Good candidates include:

- state models;
- identity models;
- validation;
- acquisition;
- normalization;
- reconciliation;
- planning;
- authorization;
- execution;
- verification;
- persistence;
- recovery;
- synchronization;
- lifecycle;
- native integration;
- protocol handling;
- parser stages;
- provider boundaries;
- failure handling.

Do not mechanically create a header every N lines.

Headers represent semantic regions, not formatting intervals.

======================================================================
6. PUBLIC TYPE AND INTERFACE CONTRACTS
======================================================================

Inspect important:

    classes
    structs
    interfaces
    abstract bases
    public functions
    important internal functions

Document non-obvious contracts.

Where applicable make recoverable:

    purpose
    ownership
    inputs
    outputs
    preconditions
    postconditions
    side effects
    lifetime
    authority
    synchronization
    cancellation
    failure semantics

Do not write boilerplate documentation for obvious trivial getters/setters.

======================================================================
7. STRUCT / CLASS STATE SEMANTICS
======================================================================

Inspect important fields.

Comment fields whose meaning is not fully conveyed by type and name.

Especially document:

- timestamps;
- IDs;
- generation numbers;
- cached observations;
- optional values;
- tri-state values;
- evidence references;
- provenance;
- ownership handles;
- native handles;
- persistent vs ephemeral identity;
- desired vs observed values;
- authoritative vs derived values;
- retry counters;
- state-machine state;
- synchronization fields.

Explicitly preserve semantic distinctions such as:

    absent
    unknown
    unavailable
    false
    stale
    incomplete
    unsupported

when the implementation distinguishes them.

Do not collapse these concepts in commentary.

======================================================================
8. FUNCTION PIPELINE COMMENTS
======================================================================

For every sufficiently non-trivial function, ask whether its algorithm can be
understood before reading individual statements.

If not, add a pre-body pipeline/contract comment.

Describe:

    starting assumptions
        ↓
    acquisition / validation
        ↓
    decision gates
        ↓
    operation
        ↓
    verification
        ↓
    resulting state / failure semantics

Do not restate every line.

Explain the decision structure.

======================================================================
9. DECISION GATES
======================================================================

Inspect important:

    if
    switch
    return
    break
    continue
    exception/error exits
    expected/error result propagation

Comment gates where the semantic meaning is not obvious.

In particular distinguish:

    SUCCESS
    FAILURE
    REFUSAL
    UNSUPPORTED
    UNKNOWN
    DEFERRAL
    RETRY-LATER
    CANCELLATION
    STALE EVIDENCE
    POLICY DENIAL
    SECURITY DENIAL
    ALREADY COMPLETE

A reader should not have to reverse-engineer what an early return means.

Example desired reasoning:

    // No authoritative observation exists yet.
    //
    // This is a deferral rather than a negative result. A later provider event
    // may supply the missing evidence and cause reconciliation to run again.
    if (!observation)
        return;

Do not comment obvious guard clauses unless their semantics matter.

======================================================================
10. AUTHORITY BOUNDARIES
======================================================================

This is HIGH PRIORITY in Rebuntu.

Search for code where multiple representations of reality coexist.

Locally document distinctions such as:

    observation != inference
    inference != authorization

    capability != permission

    desired state != observed state

    plan != execution

    execution success != verified effect

    expected effect != observed effect

    cache != live authority

    connector/path/index/name != durable identity

    missing evidence != evidence of absence

    UNKNOWN != PASS
    UNKNOWN != FALSE

    discovered capability != authorized operation

    provider result != policy decision

When one source wins over another, explain WHY it is authoritative.

======================================================================
11. NATIVE LINUX AUTHORITY
======================================================================

Rebuntu is NOT a Linux reimplementation.

Inspect integration code and document the native authority boundary where it
could otherwise become ambiguous.

Examples include:

    systemd
    cgroups
    namespaces
    procfs
    sysfs
    udev
    D-Bus
    Netlink
    NetworkManager
    nftables
    PAM/NSS
    polkit/sudo
    package managers
    mount/filesystem APIs
    process management
    scheduler
    DRM/KMS
    X11/XRandR
    hardware/driver APIs

Comments should make clear when Rebuntu:

    observes
    composes
    correlates
    persists additional semantics
    plans
    requests

rather than becoming the source of truth for native state.

Do not repeat this generic statement everywhere.

Document it locally where an incorrect future refactor could blur the boundary.

======================================================================
12. CONCURRENCY SATURATION
======================================================================

Give concurrency-heavy code special attention.

For every important synchronization region determine whether comments explain:

    which lock protects which state;
    who acquires it;
    whether caller must already hold it;
    which values are atomic;
    why they are atomic;
    what can race;
    what cannot race;
    which fields must transition together;
    callback/reentrancy hazards;
    validity after unlocking;
    cancellation/shutdown interaction;
    memory ordering when non-default ordering matters.

Comment lock ordering where multiple locks can interact.

Explicitly document why callbacks are or are not invoked while locks are held.

Do not invent guarantees unsupported by implementation.

======================================================================
13. STATE MACHINE SATURATION
======================================================================

Locate:

- explicit state enums;
- lifecycle state;
- implicit state machines;
- staged pipelines;
- recovery sequences;
- retries;
- reconciliation loops;
- async workflows.

Where useful, add compact state-transition documentation.

ASCII diagrams are encouraged.

Example:

// ---------------------------------------------------------------------------
// Reconciliation lifecycle
//
//      idle
//       |
//       v
//    observe
//       |
//       v
//    compare ------> no-op
//       |
//       v
//     plan
//       |
//       v
//    execute ------> failed/unknown
//       |
//       v
//    verify
//       |
//       +----------> degraded
//       |
//       v
//    converged
//
// Execution success is not treated as proof of convergence. Verification
// re-observes the native authority.
// ---------------------------------------------------------------------------

The diagram MUST match actual implementation.

Do not invent transitions merely to produce a nice diagram.

======================================================================
14. FAILURE SEMANTICS
======================================================================

Inspect error paths particularly aggressively.

Document where relevant:

    what failed;
    what remains valid;
    whether external side effects may already have occurred;
    whether state is known or unknown;
    whether retry is safe;
    whether retry requires re-observation;
    whether compensation exists;
    whether operator intervention may be required;
    whether failure is terminal or transient.

Particularly document timeout semantics.

A timeout frequently means:

    result unknown

not:

    operation definitely did not occur.

Make this distinction explicit wherever implementation depends on it.

======================================================================
15. NEGATIVE KNOWLEDGE
======================================================================

Search for code where a future engineer might make an attractive but incorrect
"simplification".

Record supported negative knowledge.

Examples:

    // Do not use PID as durable identity.

    // Do not convert UNKNOWN into false.

    // Do not retry before re-observing the native target.

    // Do not use connector name as physical monitor identity.

    // Do not infer successful external effect from successful request
    // submission.

    // Do not hold this lock across provider callbacks.

These comments are extremely valuable.

Do not invent hypothetical hazards unsupported by the implementation or known
platform semantics.

======================================================================
16. PLATFORM-SPECIFIC BEHAVIOR
======================================================================

Inspect code interacting with:

    Linux
    systemd
    kernel APIs
    filesystems
    DRM/KMS
    GPUs
    drivers
    D-Bus
    Netlink
    udev
    native process APIs
    external libraries

Where implementation contains non-obvious behavior caused by platform semantics,
document it locally.

Explain:

    what the platform actually guarantees;
    what it does NOT guarantee;
    what Rebuntu therefore has to do.

Do not claim guarantees without repository/specification evidence.

======================================================================
17. HISTORICAL / EMPIRICAL KNOWLEDGE
======================================================================

Preserve known reasons for unusual implementation.

Sources may include:

- existing comments;
- tests;
- issue references;
- TASK.md;
- repository documentation;
- commit-visible context available to the agent;
- explicit implementation requirements;
- known observed failures recorded in the repository.

If code exists because of a known real failure, explain that briefly where it
helps prevent regression.

NEVER invent historical stories.

If the reason cannot be established:

    do not fabricate one.

======================================================================
18. PERSISTENCE AND DURABILITY
======================================================================

Give persistence code special attention.

Document distinctions between:

    memory update
    cache update
    file write
    flush
    fsync
    directory fsync
    rename/publication
    durable commit

Do not describe atomic rename as equivalent to power-loss durability unless the
actual implementation provides the required durability semantics.

Explain crash-recovery assumptions where they matter.

======================================================================
19. SECURITY / POLICY BOUNDARIES
======================================================================

Where code handles:

    authorization
    privilege
    policy
    credentials
    identity
    trust
    privileged operations

make the authority boundary locally obvious.

Explicitly distinguish:

    technical capability

from:

    permission to perform the operation.

Do not imply that successful discovery or planning grants authorization.

Document fail-open/fail-closed behavior where it actually exists.

======================================================================
20. ASYNCHRONOUS / EVENT-DRIVEN CODE
======================================================================

For event loops, callbacks, futures, tasks, subscriptions, watchers and async
pipelines document where non-obvious:

    event ownership;
    ordering assumptions;
    duplicate events;
    stale events;
    cancellation;
    shutdown;
    callback lifetime;
    reentrancy;
    event coalescing;
    backpressure;
    retry;
    delivery semantics.

If events are hints requiring re-observation rather than authoritative state,
say so explicitly.

======================================================================
21. EXTERNAL DATA / PARSERS
======================================================================

For parsers of:

    procfs
    sysfs
    journal
    JSON
    D-Bus
    Netlink
    command output
    hardware metadata
    external service responses

document:

    trust boundary;
    malformed-data behavior;
    incomplete-data behavior;
    version tolerance;
    UNKNOWN semantics;
    validation boundary.

Never imply external input is trusted merely because it is local.

======================================================================
22. ASCII ARCHITECTURE DIAGRAMS
======================================================================

Where a source file contains an important flow/state machine that is difficult to
understand linearly, add a compact ASCII diagram.

Good examples:

    observation pipelines
    reconciliation
    state machines
    recovery
    lifecycle
    request -> authorization -> execution -> verification
    provider relationships
    synchronization ownership

Do NOT add decorative diagrams.

Every diagram must encode useful architecture.

Prefer diagrams that remain readable in an ordinary terminal/editor.

======================================================================
23. PRESERVE GOOD EXISTING COMMENTS
======================================================================

Existing useful comments are engineering knowledge.

Do not delete them merely to rewrite them in your preferred style.

If still correct:

    preserve them.

If incomplete:

    extend them.

If architecture changed:

    update them.

If demonstrably obsolete:

    correct/remove the obsolete claim while preserving still-valid knowledge.

Avoid comment churn.

======================================================================
24. REMOVE / CORRECT BAD COMMENTS
======================================================================

The saturation pass may correct comments that are:

    stale
    misleading
    contradicted by implementation
    speculative
    duplicated excessively
    narrating obvious syntax
    referring to removed architecture

Do not preserve misinformation merely because it already exists.

A wrong explanatory comment is worse than no comment.

======================================================================
25. DO NOT COMMENT TRIVIA
======================================================================

Avoid:

    // Increment i.
    ++i;

Avoid paragraph comments for:

- trivial getters;
- obvious constructors;
- straightforward forwarding;
- self-explanatory assignments;
- standard container operations.

Comment semantic complexity, not syntax complexity.

COMMENT SEMANTIC DENSITY SHOULD TRACK IMPLEMENTATION COMPLEXITY.

======================================================================
26. HEADER / IMPLEMENTATION BALANCE
======================================================================

Avoid duplicating identical essays in .hpp and .cpp.

Prefer:

HEADER:
    public contract
    externally relevant semantics
    ownership/lifetime
    important invariants

IMPLEMENTATION:
    algorithmic rationale
    platform behavior
    local synchronization
    failure handling
    implementation-specific negative knowledge

If both require commentary, make them complementary.

======================================================================
27. TEST CODE
======================================================================

Tests are also engineering documentation.

Do not saturate every assertion with comments.

But comment important test scenarios when the reason for the test is not obvious.

Especially preserve:

    regression reason;
    boundary being tested;
    surprising expected behavior;
    UNKNOWN/failure distinction;
    historical bug being prevented.

Test names should carry as much meaning as possible.

======================================================================
28. IDEMPOTENCE / CONVERGENCE REQUIREMENT
======================================================================

THIS IS CRITICAL.

This task will be run repeatedly.

Before adding any comment ask:

    Is this semantic fact already documented sufficiently close to the relevant
    implementation?

If YES:

    do not add another version.

Do not create:

    comment duplication;
    progressively longer restatements;
    multiple ASCII diagrams of the same state machine;
    repeated file introductions;
    repeated warnings.

A second execution should find fewer useful additions than the first.

Eventually an execution may legitimately produce:

    no changes

because the selected code is already sufficiently documented.

That is SUCCESS, not failure.

======================================================================
29. SATURATION PRIORITY
======================================================================

When the repository is too large for one context/pass, prioritize in this order:

P0:
    security / authorization / privilege
    recovery
    persistence
    concurrency
    state machines
    reconciliation
    native OS integration

P1:
    runtime lifecycle
    providers
    hardware integration
    event pipelines
    planning/execution/verification boundaries
    identity
    configuration/state management

P2:
    complex domain logic
    parsers
    adapters
    integration

P3:
    simple data types
    boilerplate
    obvious forwarding code

Never sacrifice semantic accuracy merely to cover more files.

======================================================================
30. BOUNDED ITERATION
======================================================================

Process the repository systematically.

If the entire src/ tree fits comfortably in one pass, inspect all of it.

If it does not:

1. inventory candidate files;
2. rank by semantic complexity and documentation deficit;
3. process the highest-value coherent subset;
4. record exactly what was processed;
5. record what remains;
6. allow the next invocation of THIS SAME TASK to continue saturation.

Do not pretend full-tree completion if context/time limits prevented it.

======================================================================
31. COMMENT QUALITY REVIEW
======================================================================

Before considering each modified file complete, ask:

- Can a new engineer understand WHY the major code exists?
- Are major invariants locally visible?
- Are authority boundaries visible?
- Are observation/inference/authorization separated?
- Are desired/observed state separated?
- Are UNKNOWN/failure/deferral distinctions understandable?
- Are important early returns understandable?
- Are concurrency assumptions documented?
- Are state transitions recoverable?
- Are timeout semantics clear?
- Are native platform behaviors explained?
- Are dangerous simplifications warned against?
- Is negative knowledge preserved?
- Are historical explanations actually supported?
- Are comments synchronized with implementation?
- Would a compact ASCII diagram materially improve comprehension?
- Did we accidentally comment trivial syntax?
- Did we duplicate commentary already present nearby?

If important semantics still require reverse-engineering:

    continue the pass.

======================================================================
32. BUILD / TEST SAFETY
======================================================================

Because this pass should not alter runtime behavior:

1. inspect git diff carefully;

2. verify that modifications are comment-only wherever possible;

3. run:

       git diff --check

4. build affected targets where practical;

5. run relevant tests where practical.

If runtime behavior changed unexpectedly:

    STOP.

Determine why before committing.

Do not hide implementation changes inside a documentation commit.

======================================================================
33. DIFF REVIEW
======================================================================

Before commit, inspect:

    git status --short
    git diff --stat
    git diff
    git diff --check

Explicitly look for:

- accidental code deletion;
- code movement;
- whitespace damage;
- malformed comments;
- comments attached to wrong code;
- duplicate comments;
- speculative statements;
- stale claims;
- generated/vendor modifications.

The final diff should clearly look like a documentation/comment saturation pass.

======================================================================
34. UPDATE REPOSITORY DOCUMENTATION ONLY WHEN REQUIRED
======================================================================

Do NOT mechanically modify every TASK.md or structural file merely because
comments were added.

Update structural metadata only if repository conventions explicitly require
recording this kind of pass.

If a phase TASK.md acts as a living implementation ledger and repository rules
require every implementation pass to update it, update only the relevant
aggregate TASK.md entries.

Record:

    COMMENT SATURATION PASS
    scope inspected
    scope modified
    important semantic documentation added
    remaining saturation areas

Do not falsely mark implementation requirements complete merely because their
code received comments.

======================================================================
35. COMMIT
======================================================================

If the pass produced useful changes and verification succeeds:

create ONE dedicated commit.

Suggested commit subject:

    Saturate C++ implementation with engineering rationale and invariants

Alternative:

    Expand local C++ documentation across runtime and system boundaries

Do not use phase numbers as the primary commit description.

Do not include unrelated changes.

If the working tree already contains unrelated modifications:

    preserve them;
    stage only files/hunks belonging to this task.

If the pass legitimately produces no changes:

    do not create an empty commit.

Report that the inspected scope is already saturated according to the current
standard.

======================================================================
36. FINAL REPORT
======================================================================

Report:

    files inspected
    files modified
    comment lines added/changed
    major semantic areas documented
    state machines documented
    concurrency regions documented
    authority boundaries documented
    failure/recovery semantics documented
    native-platform behavior documented
    negative knowledge documented
    unsupported/speculative comments removed or corrected
    build/tests executed
    git diff --check result
    remaining high-value saturation candidates
    commit hash

Also give a qualitative saturation assessment for each major processed subtree:

    LOW
    PARTIAL
    GOOD
    SATURATED

These labels describe COMMENT/DOCUMENTATION saturation only.

They MUST NOT be interpreted as implementation completeness.

======================================================================
37. REPEATABILITY CONTRACT
======================================================================

On every future invocation of this exact task:

    re-read current code
        ↓
    re-read current comments
        ↓
    identify remaining semantic documentation deficits
        ↓
    improve only genuine deficits
        ↓
    verify truthfulness against current implementation
        ↓
    stop adding commentary where saturation has already been reached

Never assume the previous pass was correct merely because it was previously
committed.

Never assume a previously saturated file remains saturated after implementation
changes.

The implementation is authoritative.

Comments must follow the implementation.

The desired convergence condition is:

    important semantics are locally recoverable
    AND
    additional comments would mostly duplicate existing knowledge.

At that point:

    LEAVE THE FILE ALONE.
