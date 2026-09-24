TASK: Implement evidence-driven display stall watchdog and controlled recovery for Rebuntu.

Repository:
    /home/bvrznski/rebuntu

PRECONDITION

The persistent monitor-layout task should already be implemented and committed.

Read that implementation before doing anything.

GOAL

Implement a production-quality Rebuntu watchdog for catastrophic display-stack
stalls.

The watchdog exists to solve this real operational problem:

- NVIDIA/X11/DRM may freeze the entire visible desktop;
- mouse movement may stop;
- all displays may appear frozen;
- Linux kernel, networking and unrelated services may still remain alive;
- manually reaching the physical reset button is inconvenient;
- reboot should therefore be possible automatically after a sufficiently
  well-established persistent display failure.

THIS MUST NOT BE A HAIR-TRIGGER REBOOT DAEMON.

A 1-3 second compositor/flip stall must NEVER by itself reboot the machine.

The design must be:

    observe
      -> correlate
      -> confirm
      -> capture evidence
      -> attempt bounded safe recovery where appropriate
      -> verify
      -> escalate
      -> reboot only as last resort

============================================================
0. MANDATORY REPOSITORY ARCHAEOLOGY
============================================================

Before changing code:

Read all applicable AGENTS.md and structural metadata.

Search the complete repository for:

    watchdog
    health
    monitor
    stability
    hang
    stall
    jam
    heartbeat
    journal
    journald
    DRM
    NVIDIA
    X11
    XRandR
    display
    GPU
    recovery
    reboot
    shutdown
    operation
    evidence
    diagnostic snapshot
    systemd watchdog
    /dev/watchdog
    RuntimeWatchdogSec
    task/job/workflow runtime

Reuse canonical Rebuntu:

- service lifecycle;
- events;
- evidence;
- health;
- results/errors;
- operation execution;
- subprocess execution;
- configuration;
- persistence;
- logging;
- privileges;
- shutdown/reboot mechanisms.

Do not create duplicate ontologies.

DO NOT DELETE EXISTING IMPLEMENTATIONS.

============================================================
1. SEPARATION OF RESPONSIBILITIES
============================================================

Keep at least these conceptual responsibilities separate:

    DisplayHealthObserver
    StallDetector
    StallCorrelator
    DiagnosticSnapshot
    RecoveryPolicy
    RecoveryExecutor

Names should follow existing repository vocabulary.

Observation must not itself perform reboot.

Detection must not itself perform reboot.

Policy decides whether escalation is allowed.

Execution must go through canonical privileged operation mechanisms.

============================================================
2. MULTI-SIGNAL HEALTH DETECTION
============================================================

Never decide:

    "X command timed out once => reboot"

Use multiple independent signals.

Useful signals may include, where available:

A. X11/session responsiveness
B. XRandR query responsiveness
C. display backend event progress
D. NVIDIA management responsiveness
E. recent DRM/NVIDIA kernel events
F. display topology consistency
G. desktop/session heartbeat
H. system/kernel/network liveness

The watchdog must explicitly distinguish:

    display stack dead

from:

    entire machine dead

and:

    temporary display stall

from:

    persistent failure.

============================================================
3. TEMPORAL MODEL
============================================================

Use CLOCK_MONOTONIC / std::chrono::steady_clock for elapsed-time decisions.

Wall-clock changes must not trigger recovery.

Use configurable thresholds.

Initial conservative defaults should be approximately:

    suspect_after       = 5 s
    evidence_after      = 10 s
    recovery_after      = 20 s
    reboot_after        = 30 s

These are defaults, not hardcoded constants.

A single successful health cycle should normally clear transient suspicion.

Use hysteresis/debounce so the state does not oscillate.

Conceptual state machine:

    Healthy
      -> Suspected
      -> Confirming
      -> Failed
      -> Recovering
      -> Verifying
      -> Healthy

or:

      -> Escalating
      -> RebootRequested

Adapt to canonical Rebuntu state/lifecycle vocabulary.

============================================================
4. KNOWN NVIDIA FAILURE EVIDENCE
============================================================

The watchdog must be capable of recognizing/correlating kernel evidence including:

    Flip event timeout

    Failed to grab modeset ownership

    nv_drm_handle_hotplug_event

    NVRM: Xid

    GPU has fallen off the bus

    NVIDIA DRM/KMS errors

Do NOT treat every occurrence as grounds for reboot.

For example:

    Failed to grab modeset ownership

may occur transiently during DRM master transitions.

It becomes useful evidence when correlated with persistent loss of display/session
responsiveness.

Likewise:

    nv_drm_handle_hotplug_event ... hogged CPU for >10000us

means a >10 ms workqueue warning.

Do NOT incorrectly interpret that warning as proof of a multi-second freeze.

============================================================
5. CURRENT INCIDENT FIXTURE
============================================================

Add test fixtures representing this actual observed incident:

At approximately 11:46:08:

    [GPU ID 0x00000b00] Failed to grab modeset ownership
    [GPU ID 0x00000c00] Failed to grab modeset ownership
    [GPU ID 0x00004300] Failed to grab modeset ownership
    [GPU ID 0x00004400] Failed to grab modeset ownership

Immediately afterwards the kernel continued logging network/UFW activity.

Interpretation for the watchdog:

    graphics/display subsystem failure suspected
    kernel/system liveness still demonstrated

NOT:

    kernel dead

The watchdog should be able to classify/correlate this distinction.

Also create fixture(s) for:

    nvidia-drm Flip event timeout on multiple heads

without assuming every timeout requires reboot.

============================================================
6. EVIDENCE SNAPSHOT
============================================================

Before destructive recovery/reboot, capture a bounded diagnostic snapshot.

Use canonical Rebuntu evidence facilities.

Where available collect minimally:

- boot ID;
- monotonic/realtime timestamps;
- watchdog state transitions;
- reason for escalation;
- relevant recent kernel journal window;
- relevant NVIDIA/DRM messages;
- GPU status;
- display topology/status;
- active X11/display backend state;
- system load;
- kernel liveness indicators;
- service/session status.

DO NOT collect:

- browser contents;
- clipboard;
- keystrokes;
- user documents;
- unrelated process environment;
- secrets.

Every diagnostic command must have a strict timeout.

A hung diagnostic collector must not prevent recovery indefinitely.

Snapshot failure must be recorded but must not deadlock escalation.

============================================================
7. RECOVERY POLICY
============================================================

Recovery must be staged.

Do NOT immediately:

    kill Xorg
    reset GPU
    reboot

Potential stages:

Stage 0:
    observation only

Stage 1:
    collect evidence and wait for spontaneous recovery

Stage 2:
    use an existing safe display/session recovery mechanism IF the repository
    already provides one and it is known to be bounded/safe

Stage 3:
    controlled system reboot

Do not invent dangerous GPU reset behavior.

Do not blindly unload NVIDIA modules while Xorg owns them.

Do not kill arbitrary processes.

Do not attempt PCI remove/rescan.

Do not manipulate sysfs reset interfaces as part of this task.

A controlled reboot is preferable to experimental destructive GPU recovery.

============================================================
8. REBOOT CONDITIONS
============================================================

Reboot may occur ONLY when all configured policy requirements are met.

At minimum require:

- failure persisted beyond reboot threshold;
- multiple failed health observations;
- transient recovery did not occur;
- sufficient confidence that visible/session display stack is unusable;
- reboot policy explicitly enabled;
- cooldown/rate-limit permits reboot.

Default implementation should support:

    reboot_enabled = false

for safe installation/testing.

Activation should require explicit configuration.

Once enabled, it can operate autonomously according to policy.

============================================================
9. REBOOT STORM PROTECTION
============================================================

CRITICAL.

Persist reboot/escalation history across boots.

Prevent:

    boot
      -> NVIDIA problem
      -> reboot
      -> NVIDIA problem
      -> reboot
      -> ...

Implement configurable limits such as:

    max_watchdog_reboots_per_window
    reboot_window
    post_boot_grace_period

Example conservative semantics:

    no watchdog reboot during first 120 s after boot

and:

    maximum 2 watchdog-triggered reboots within 30 minutes

If the limit is exceeded:

- stop automatic reboot escalation;
- preserve evidence;
- mark degraded/failure state;
- require manual intervention.

Use existing Rebuntu persistence facilities.

============================================================
10. INTERACTION WITH MONITOR LAYOUT SERVICE
============================================================

Integrate with the monitor-layout component from the previous task.

When display health is degraded:

    monitor-layout reconciler MUST NOT repeatedly reapply layouts.

The watchdog should expose a canonical health/degraded state that allows the
layout reconciler to suspend potentially harmful modesets.

Likewise:

    layout application in progress

must be visible to the watchdog so that an expected short modeset transition is
not immediately interpreted as a catastrophic stall.

Avoid circular dependencies.

Use existing event/state/service contracts.

============================================================
11. SYSTEMD / HARDWARE WATCHDOG
============================================================

Investigate existing Rebuntu/systemd watchdog integration.

Support systemd service watchdog notification if consistent with architecture.

Separately investigate:

    /dev/watchdog
    RuntimeWatchdogSec=
    RebootWatchdogSec=

Do NOT assume hardware watchdog exists.

Do NOT enable hardware watchdog automatically.

Expose capability/evidence indicating whether one is available.

A hardware watchdog addresses a different failure class:

    userspace/display watchdog
        -> kernel alive, display dead

versus:

    hardware watchdog
        -> kernel/system itself stops servicing watchdog

Keep these mechanisms conceptually separate.

============================================================
12. PRIVILEGE BOUNDARY
============================================================

Monitoring should run with minimum privilege.

Do not make the whole observer run permanently as root merely because reboot
eventually requires privilege.

Use existing Rebuntu privileged operation/execution mechanisms.

If systemd/polkit/sudo integration already exists, reuse it.

No embedded passwords.

No broad unrestricted sudo rule.

============================================================
13. CONFIGURATION
============================================================

Use canonical Rebuntu configuration facilities.

Expose at least equivalents of:

    enabled
    reboot_enabled
    probe_interval
    suspect_after
    evidence_after
    recovery_after
    reboot_after
    post_boot_grace_period
    max_watchdog_reboots_per_window
    reboot_window
    diagnostic_command_timeout
    recovery_enabled

Validate relationships, e.g.:

    suspect_after
      < evidence_after
      <= recovery_after
      < reboot_after

Reject nonsensical configurations.

============================================================
14. TESTING
============================================================

Implement extensive deterministic tests.

No test may reboot the development machine.

The actual reboot operation MUST be injectable/mockable.

Tests must cover at least:

- healthy operation;
- one slow probe;
- 2-second temporary freeze;
- temporary 5-second freeze;
- recovery before threshold;
- persistent X11 failure;
- X11 dead but kernel alive;
- NVIDIA query dead;
- X alive but NVIDIA kernel errors present;
- modeset ownership errors without stall;
- modeset ownership errors + persistent stall;
- flip timeout correlation;
- hotplug warning without stall;
- post-boot grace period;
- reboot disabled;
- reboot enabled;
- reboot rate limiting;
- persisted reboot history;
- diagnostic command timeout;
- partial diagnostic failure;
- layout application suppression;
- layout reconciler suspension during degraded display state.

Use fake clocks.

Do NOT make tests sleep for 30 real seconds.

============================================================
15. FAILURE INJECTION
============================================================

Provide a safe developer/test-only failure injection mechanism.

It should allow simulation of:

    X probe timeout
    NVIDIA probe timeout
    display backend stall
    kernel evidence patterns

without touching the real NVIDIA driver.

It MUST NOT be enabled in production accidentally.

This is important because we do not want validation of the watchdog to require
reproducing the real machine freeze.

============================================================
16. OBSERVABILITY
============================================================

Expose useful state such as:

    display_health
    current_watchdog_state
    suspicion_duration
    failed_probes
    last_successful_probe
    last_incident
    last_recovery_attempt
    automatic_reboot_allowed
    reboot_budget_remaining

Do not spam journald every second during healthy operation.

Log state transitions and meaningful incidents.

============================================================
17. DOCUMENTATION / TREE / PHASE LEDGER
============================================================

Update applicable:

- AGENTS.md
- __tree__
- __base__
- __meta__
- __load__
- STRUCTURE.md
- build manifests
- service manifests

Update the appropriate phase aggregate TASK.md implementation ledger.

Record:

- architecture;
- implementation paths;
- runtime integration;
- evidence model;
- tests;
- safety properties;
- remaining limitations;
- verification status.

============================================================
18. VERIFICATION
============================================================

Build everything affected.

Run unit tests.

Run integration tests that do NOT alter the live display configuration.

Run static/lint checks required by repository.

Run:

    git diff --check

Inspect the diff for:

- accidental deletion;
- unrelated formatting;
- duplicated infrastructure;
- unsafe root execution;
- unbounded shell calls;
- accidental reboot paths.

The watchdog MUST be testable with:

    reboot_enabled=false

and must remain non-destructive during verification.

============================================================
19. COMMIT
============================================================

After successful verification create a dedicated commit.

Do not combine it with the monitor-layout commit.

Use a descriptive commit message such as:

    Add evidence-driven display stall watchdog and bounded recovery

Do not use a phase number as the primary commit description.

At completion report:

- architecture location;
- reused canonical infrastructure;
- new files;
- modified files;
- tests;
- exact verification performed;
- default safety configuration;
- how to explicitly enable automatic reboot;
- commit hash.
