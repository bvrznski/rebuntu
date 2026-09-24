# Phase 1.1 — Host Discovery & Installation Preconditions Final Report

## Summary

This phase implements the authoritative pre-install host discovery and precondition layer for Rebuntu installation.

### What was implemented:
1. **Host Discovery module** (`src/system/install/discovery.hpp`, `.cpp`):
   - `HostFacts`: Machine-readable host environment observations (OS, kernel, architecture, user context, filesystems, package managers)
   - `PreflightCheckResult`: Result of a preflight evaluation with severity level
   - `DiscoveryResult`: Complete host discovery and preflight evaluation result
   - `HostDiscovery`: Main interface for discovering host facts and evaluating preconditions
   - `PreflightEvaluator`: Simplified interface for preflight evaluation

2. **Native Linux facilities integrated**:
   - `/etc/os-release` — OS distribution facts (ID, VERSION_ID)
   - `uname(2)` — kernel version and architecture
   - `statvfs(2)` — filesystem capacity and writability
   - `/proc/1/cgroup` — container environment detection (Docker/Podman)
   - `geteuid()` — effective user ID for privilege determination

3. **Preflight checks**:
   - supported distribution (ubuntu, debian, fedora, arch, centos)
   - root privileges
   - bin directory writable (/usr/bin or ~/.local/bin)
   - state directory writable (/var/lib/rebuntu or ~/.local/state/rebuntu)
   - package manager availability (apt, dnf, pacman)
   - home directory accessible
   - sufficient free space (>50MB)

### Test Results:
```
Test project /home/bvrznski/rebuntu/cpp/Build
    Start 1: install_planning_test
1/9 Test #1: install_planning_test ............   Passed    0.00 sec
    Start 2: runtime_runner_test
2/9 Test #2: runtime_runner_test ..............   Passed    0.00 sec
    Start 3: automation_test
3/9 Test #3: automation_test ..................   Passed    0.00 sec
    Start 4: test_runtime_contracts
4/9 Test #4: test_runtime_contracts ...........   Passed    0.00 sec
    Start 5: test_state_provider
5/9 Test #5: test_state_provider ..............   Passed    0.00 sec
    Start 6: events_test
6/9 Test #6: events_test ......................   Passed    0.05 sec
    Start 7: results_test
7/9 Test #7: results_test .....................   Passed    0.00 sec
    Start 8: test_discovery
8/9 Test #8: test_discovery ...................   Passed    0.00 sec
    Start 9: config_test
9/9 Test #9: config_test ......................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 9
```

## Archaeology Findings

### Existing Implementation Survey:
- `src/system/install/` — Contains Phase 1.0 bootstrap/planning infrastructure
- `cpp/tests/install_planning_test.cpp` — Existing planning tests
- No existing host discovery module found - this is new implementation

### Native Linux Facilities Identified:
- **OS release**: `/etc/os-release` provides distribution facts (ID, VERSION_ID, etc.)
- **Kernel info**: `uname(2)` system call for kernel version and machine architecture
- **Filesystem**: `statvfs(2)` for capacity, free space, and writability checks
- **Container detection**: `/proc/1/cgroup`, `/.dockerenv`, `/run/.containerenv`
- **User context**: `geteuid()`, `getgid()` for privilege determination
- **Package managers**: Shell command discovery via `which`

## Architecture Decisions

### 1. C++20 Native Implementation
Host discovery is implemented in native C++20 using standard Linux system calls and APIs.
No Python or shell execution except for package manager detection (which requires external tools).

### 2. Fact vs Configuration Separation
Discovery produces **observations/facts**, not configuration:
- Facts: What the host *is* (distribution, version, kernel)
- Preflight checks: Derived from facts + supported rules
- Precondition blockers: Facts + rules → blockers

### 3. Evidence Chain Preservation
Each check result preserves source/provenance for traceability:
```cpp
PreflightCheckResult {
    std::string name;      // "supported-distribution"
    bool passed;
    PreflightCheckLevel level;  // kInfo, kWarning, kBlocker
    std::optional<std::string> message;
    std::string source;    // "/etc/os-release"  ← provenance
}
```

### 4. Severity Levels
- `kBlocker` — Cannot proceed without resolution (e.g., no home directory)
- `kWarning` — Can proceed but with caution (e.g., unsupported distribution)
- `kInfo` — Informational only (e.g., detected package managers)

## Implementation Details

### Files Created/Modified:
| File | Purpose |
|------|---------|
| `src/system/install/discovery.hpp` | Header with HostFacts, PreflightCheckResult, DiscoveryResult, HostDiscovery, PreflightEvaluator classes |
| `src/system/install/discovery.cpp` | Implementation of host discovery and preflight checks |
| `src/system/install/CMakeLists.txt` | Added discovery files to build |

### Key Types:

**HostFacts**
```cpp
struct HostFacts {
    // OS/Distribution facts
    std::string os_id;           // e.g., "ubuntu", "debian"
    std::string os_version;      // e.g., "22.04"
    
    // Kernel facts
    std::string kernel_version;
    std::string architecture;
    
    // User context
    uid_t effective_uid;
    bool is_root;
    std::optional<std::string> home_dir;
    
    // Filesystem facts
    std::optional<FileSystemInfo> root_filesystem;
    std::optional<FileSystemInfo> home_filesystem;
    
    // Package manager facts
    struct PackageManager { std::string name; bool available; };
    std::vector<PackageManager> package_managers;
    
    // Environment type
    enum class EnvironmentType { kPhysicalMachine, kContainer, kVirtualMachine, kUnknown };
};
```

**DiscoveryResult**
```cpp
struct DiscoveryResult {
    HostFacts facts;
    std::vector<PreflightCheckResult> preflight_checks;
    DiscoveryStatus status;  // kReady, kWarningOnly, kBlocked
    
    std::vector<core::Evidence> evidence;  // Provenance-bearing observations
};
```

## Testing

### Test Results:
All existing tests pass. The implementation compiles and links correctly.

### Build Command:
```bash
cd /home/bvrznski/rebuntu/cpp
cmake -S . -B Build && make -j4
```

### Run Tests:
```bash
ctest --output-on-failure
```

## Safety Considerations

### Host Mutation Policy:
- **No destructive actions** — Discovery only reads host state
- **Read-only operations** — Uses native APIs without side effects
- **Evidence preservation** — All observations include source/provenance

### Failure Handling:
```cpp
enum class DiscoveryStatus {
    kReady,        // All blockers passed, ready for installation
    kWarningOnly,  // Some warnings but no blockers
    kBlocked       // Has blockers that must be resolved
};
```

### Verification:
- Preflight checks have explicit `passed` status
- Blockers prevent installation until resolved
- Evidence chain preserves provenance for auditability

## Rejected Alternatives

1. **Shell-based discovery**: Would create "shell gateway" anti-pattern; native Linux APIs are available and more reliable.

2. **Python replication**: Phase 0 architecture established C++ as authoritative runtime for system management.

3. **Mock-only testing**: Discovery uses actual native mechanisms (`uname`, `statvfs`) which are deterministic and testable.

4. **Hardcoded values**: Distribution and environment detection uses actual host state, not configuration files.

## Deferred Work

| Phase | Task |
|-------|------|
| 1.2 | Real plan execution (currently simulated) |
| 1.3 | Package manager integration (apt, snap, pip) |
| 1.4 | Binary installation (actual file copying) |
| 1.5 | Service registration (systemd unit files) |
| 1.6 | PATH configuration updates |
| 1.7 | Configuration file generation |
| 1.8 | Post-install verification improvements |
| 1.9 | Rollback/recovery support |
| 1.10 | Idempotency enforcement |
| 1.11 | Uninstall functionality |

## Remaining Risks

1. **Container detection**: Currently checks for Docker/Podman via cgroup; may miss other container runtimes.

2. **Limited distribution support**: Only ubuntu, debian, fedora, arch, centos are explicitly supported; others produce warnings but not blockers.

3. **Filesystem checks**: Use `/` or `$HOME` as targets; multi-mount scenarios not fully handled.

## Verdict: COMPLETE

The Phase 1.1 host discovery and preflight evaluation system is complete:
- ✅ C++20 native implementation using Linux APIs
- ✅ Machine-readable HostFacts structure with all required fields
- ✅ PreflightCheckResult with severity levels (info/warning/blocker)
- ✅ DiscoveryResult with evidence chain preservation
- ✅ All tests pass (9/9)
- ✅ Build integration complete

**Note**: The implementation follows Phase 0 architecture principles:
- C++20 authoritative runtime
- Native Linux mechanisms preferred over emulation
- Evidence chain for traceability and verification
- Clear separation of facts vs configuration