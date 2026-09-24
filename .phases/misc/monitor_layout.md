TASK: Implement native persistent monitor-layout management for Rebuntu.

Repository:
    /home/bvrznski/rebuntu

GOAL

Implement a production-quality Rebuntu service/component that manages persistent
logical monitor layouts on top of the native Linux display stack.

This is NOT a replacement for X11, XRandR, NVIDIA, DRM/KMS, udev, systemd, or
Wayland. Those mechanisms remain authoritative.

Rebuntu is responsible only for the additional semantics that the native display
stack does not provide conveniently:

- stable physical-monitor identity;
- persistent logical placement;
- remembering preferred layouts;
- matching a known layout against currently available physical monitors;
- preserving logical positions when monitors disappear;
- surviving connector/GPU/cable-route changes;
- recognizing intentional manual layout changes;
- reconciling desired state with the native display configuration.

Do not implement a shadow display server or shadow DRM/KMS state machine.

============================================================
0. MANDATORY REPOSITORY ARCHAEOLOGY
============================================================

Before changing ANY code:

1. Read:
   - /home/bvrznski/rebuntu/AGENTS.md
   - every applicable nested AGENTS.md
   - applicable __tree__, __base__, __meta__, __load__, STRUCTURE.md files
   - relevant phase TASK.md files.

2. Search the entire repository for existing implementations/contracts involving:

   monitor
   display
   screen
   output
   connector
   EDID
   XRandR
   X11
   Wayland
   DRM
   KMS
   NVIDIA
   udev
   hotplug
   topology
   desired state
   reconciliation
   identity
   hardware identity
   device identity
   persistence
   configuration
   runtime services
   service lifecycle
   event handling
   observation/evidence
   systemd

3. Reuse and extend canonical Rebuntu contracts.

DO NOT introduce a second:
- Service abstraction;
- Runtime;
- Event model;
- Result/Error model;
- Evidence model;
- Identity model;
- desired-state model;
- configuration system;
- persistence subsystem;
- subprocess execution framework;
- logging framework.

If functionality already exists, integrate with it.

4. DO NOT DELETE EXISTING FILES OR IMPLEMENTATIONS.

If something needs relocation/refactoring:
- preserve behavior;
- migrate callers;
- update metadata/tree files;
- verify references;
- only then retire obsolete structure if repository rules explicitly permit it.

Default disposition is preservation.

============================================================
1. ARCHITECTURAL MODEL
============================================================

The implementation must explicitly distinguish at least:

    PhysicalMonitor
    LogicalMonitorPlacement
    DisplayConnector
    DisplayRoute
    ObservedDisplayState
    DesiredDisplayState
    DisplayLayoutProfile

Names may be adapted to existing canonical Rebuntu vocabulary.

CRITICAL:

Physical monitor identity MUST NOT equal connector identity.

For example:

    Dell monitor
        != DP-1-4
        != HDMI-1
        != NVIDIA provider
        != DRM connector

The same physical monitor moved from:

    GPU A / DP-1

to:

    GPU C / HDMI-0

must retain its logical identity and preferably its logical desktop position.

============================================================
2. STABLE MONITOR IDENTITY
============================================================

Use EDID-derived information where available.

Capture useful fields such as:

- manufacturer;
- product/model;
- serial number;
- product code;
- EDID fingerprint/hash;
- physical dimensions;
- supported modes where useful.

Construct identity conservatively.

Serial number should be preferred when trustworthy.

If serial is missing/duplicated/unreliable, use a deterministic fingerprint from
stable EDID fields.

Do not make connector name part of the physical identity.

Store connector and GPU/provider only as current routing information.

Handle ambiguous identical monitors explicitly.

Do NOT silently pretend two indistinguishable identical monitors can always be
uniquely identified.

============================================================
3. OBSERVED STATE
============================================================

Do NOT model monitor state as only:

    connected = true/false

The implementation must distinguish concepts equivalent to:

    physically_detected
    connector_connected
    logically_enabled
    mode_configured
    signal/path healthy
    present_in_desktop_topology

This requirement comes from real NVIDIA/XRandR behavior where a connector may
report "connected" and EDID may remain readable while the physical monitor has
already lost usable display signal.

Do not infer health solely from XRandR's "connected" flag.

============================================================
4. LAYOUT MODEL
============================================================

Persist logical geometry independently from physical cable routing.

For every monitor placement preserve, where applicable:

- logical x/y;
- width/height;
- orientation;
- scale;
- refresh preference;
- primary status;
- enabled/disabled preference.

A disconnected monitor MUST NOT cause remaining monitors to collapse into a new
layout automatically.

Example:

Canonical layout:

    A B C
    D E F

If B disappears:

    A . C
    D E F

The hole remains.

Do NOT transform it automatically into:

    A C .
    D E F

unless the user explicitly changes the layout.

============================================================
5. PROFILE MATCHING
============================================================

Maintain persistent layout profiles.

When topology changes, select the best compatible known profile.

Ranking should incorporate:

1. explicit/manual canonical preference;
2. compatibility with currently identified physical monitors;
3. largest known profile whose monitor set contains the currently available set;
4. identity confidence;
5. historical usage/frequency;
6. recency as a lower-priority tie breaker.

Do not blindly treat the most recently observed transient layout as canonical.

A temporary monitor failure must not overwrite a known seven-monitor layout with
a six-monitor canonical layout.

============================================================
6. MANUAL CHANGE DETECTION
============================================================

The daemon must distinguish:

    Rebuntu applying desired layout

from:

    user manually changing layout

Otherwise it will learn its own writes as user preferences.

Implement a bounded state machine equivalent to:

    Idle
      -> Applying
      -> Settling
      -> Idle

During Applying/Settling:

- observe resulting native state;
- correlate it with the operation Rebuntu requested;
- do not classify expected consequences as manual edits.

Outside that window:

A stable externally initiated geometry/configuration change should be eligible to
become a new preferred layout.

Require a settling/debounce interval before persisting it.

============================================================
7. NATIVE BACKEND
============================================================

Current machine is:

    Ubuntu 22.04
    X11
    NVIDIA proprietary/open kernel driver stack
    multi-GPU
    XRandR providers

Implement X11/XRandR support first.

Prefer direct native/library interfaces where appropriate.

Do not build the entire service around shell parsing of:

    xrandr

if libXrandr/native APIs already provide the required information.

A bounded subprocess adapter may be used only where necessary and should use the
canonical Rebuntu execution facilities.

Design the backend boundary so Wayland support can be added later without
rewriting monitor identity/profile/reconciliation logic.

For example conceptually:

    DisplayBackend
        XRandRBackend
        future WaylandBackend

Adapt names to repository conventions.

============================================================
8. HOTPLUG
============================================================

Integrate with native event mechanisms.

Prefer event-driven detection via appropriate XRandR/udev/native mechanisms.

Do not busy-poll unnecessarily.

Debounce hotplug storms.

NVIDIA may emit multiple events for one physical operation.

The reconciler must be idempotent.

============================================================
9. SAFETY
============================================================

A failed layout application must not leave the system permanently unusable.

Implement:

- validation before application;
- bounded application timeout;
- verification after application;
- rollback where practical;
- failure evidence;
- no infinite retry loop;
- exponential/bounded retry where appropriate.

Never repeatedly hammer DRM/XRandR when the driver is already stalled.

A display backend failure must be surfaced as a health/evidence condition rather
than triggering unbounded configuration attempts.

============================================================
10. CURRENT REAL-WORLD TEST CASE
============================================================

Ensure the design can represent this actual configuration:

Desktop framebuffer:

    11520x4320

Six stable active monitors:

             TOP

    DP-1-4      DP-3-0      DP-3-4
    3840x2160   3840x2160   3840x2160
    +0+0        +3840+0      +7680+0

             BOTTOM

    DP-1-2      DP-3-2      DP-1-0
    3840x2160   3840x2160   3840x2160
    +0+2160     +3840+2160   +7680+2160

DP-3-2 is primary and may operate at 144 Hz.

There is additionally a seventh HDMI monitor currently represented by HDMI-1.

The service must NOT hardcode these connector names.

They are a test fixture/example only.

The seventh monitor has demonstrated the pathological state:

    EDID readable
    connector reported connected
    temporary image appears
    physical display then loses signal

The data model must be capable of representing this without declaring the
monitor healthy merely because connector_connected=true.

============================================================
11. PERSISTENCE
============================================================

Use existing Rebuntu paths/config/state facilities.

Do not invent random dotfiles.

Persist:

- physical identities;
- profiles;
- profile membership;
- logical placement;
- profile preference;
- observation/use statistics;
- manual approval/change provenance;
- last successful application;
- identity confidence where relevant.

Writes must be atomic.

Corrupt state must fail safely.

============================================================
12. SERVICE INTEGRATION
============================================================

Integrate into the existing Rebuntu service/runtime lifecycle.

Do not create a private daemon framework if Rebuntu already has one.

Provide appropriate systemd integration if consistent with repository architecture.

Determine from the existing architecture whether this belongs to:

    system service
    user service
    session service

Do not guess before repository archaeology.

Because X11 display ownership/session environment is user-session-specific,
strongly consider the existing per-user/session runtime model if one exists.

============================================================
13. TESTS
============================================================

Implement real tests.

At minimum cover:

- stable EDID identity;
- same monitor on different connector;
- connector rename;
- one monitor removed;
- multiple monitors removed;
- monitor restored;
- hole preservation;
- profile subset matching;
- manual change detection;
- self-generated change suppression;
- ambiguous identical monitors;
- transient hotplug storm;
- connected-but-not-healthy monitor;
- failed layout application;
- rollback;
- persistence reload;
- corrupted persistence;
- idempotent reconciliation.

Use mocks/fakes only at the native backend boundary.

Core matching/reconciliation logic must be testable without a live X server.

============================================================
14. DOCUMENTATION / TREE METADATA
============================================================

Update all applicable:

- AGENTS.md
- __tree__
- __base__
- __meta__
- __load__
- STRUCTURE.md
- CMake/build manifests

according to repository conventions.

Update the appropriate phase aggregate TASK.md implementation ledger with:

- paths implemented;
- requirements satisfied;
- tests;
- remaining limitations;
- implementation depth;
- evidence/verification.

============================================================
15. VERIFICATION
============================================================

Build the affected project.

Run relevant unit/integration tests.

Run static/lint checks required by the repository.

Do not claim completion when code does not build.

Do not require changing the live monitor configuration to verify basic correctness.

Do NOT intentionally provoke the known NVIDIA freeze during tests.

============================================================
16. COMMIT
============================================================

After successful implementation and verification:

    git status
    git diff
    git diff --check

Review for accidental deletion or unrelated modification.

Then create ONE dedicated git commit for this task.

Commit message should describe the functionality, not a phase number.

Do not include unrelated working-tree changes.

At the end report:

- architectural location;
- files added;
- files modified;
- tests added;
- commands/tests run;
- remaining limitations;
- commit hash.
