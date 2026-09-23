# Installation Architecture (Phase 1.0)

## Discovery

### Phase
Phase 1.0 — Installation Architecture & Bootstrap

### Date
September 22, 2026

### Problem Statement
Rebuntu requires a canonical installation/bootstrap entry path that transforms a host from "Rebuntu not installed" to "Rebuntu installed with verified minimal foundation".

### Native Linux Facilities Considered
- **systemd**: For service lifecycle management and unit file installation
- **apt/dpkg**: For package dependency resolution  
- **/usr/bin**, **/var/lib**, **/etc**: Standard Linux directories for binaries, state, and configuration
- **XDG Base Directory**: For user-scoped installations (`~/.local`, `~/.config`)

### C++ Implementation Choices
1. **InstallationState enum**: Distinct states (NotInstalled, Incomplete, Installed, Degraded)
2. **InstallationScope enum**: System vs User installation contexts
3. **VerificationResult structure**: Check-based verification with pass/fail tracking
4. **Filesystem operations**: Using `std::filesystem` for path existence and permission checks

### Architecture Decisions

#### 1. Installation State Model
Rebuntu's installation state is tracked through four distinct states:
- `kNotInstalled`: No Rebuntu artifacts found
- `kIncomplete`: Some artifacts exist but are incomplete/broken
- `kInstalled`: Full installation present and verified
- `kDegraded`: Installation exists but verification failed

#### 2. Installation Scope
Rebuntu supports both system-wide (`/usr/bin`, `/var/lib/rebuntu`) and user-scoped (`~/.local/bin`, `~/.config/rebuntu`) installations.

#### 3. Verification Strategy
Installation verification is separate from execution:
- Check binary exists at expected path
- Verify binary has executable permissions
- Validate state directory accessibility

### Implementation Files Created

| File | Purpose |
|------|---------|
| `cpp/include/system/install/contracts.hpp` | Installation contracts: states, scopes, artifacts, context |
| `cpp/src/install.cpp` | Installation implementation: verification, path resolution |

### Phase 1.2 Additions (Planning & Environment Preparation)

| File | Purpose |
|------|---------|
| `cpp/include/system/install/planning.hpp` | Planning API: InstallationIntent, DependencyInfo, PreInstallationCheckResult, InstallationStep, InstallationPlan |
| `cpp/src/install_planning.cpp` | Planner implementation with PreflightEvaluator for host readiness checks |

### Architecture (Phase 1.2)

#### Planner
The `Planner` class produces explicit installation plans from validated installation intent + discovered host facts:
- Evaluates preflight checks (distribution, privileges, directories, package managers)
- Resolves dependencies (C++ runtime, optional Python for semantic/ML features)
- Builds ordered installation steps with verification criteria

#### PreflightEvaluator
Host readiness checks:
- Distribution support check (Ubuntu/Debian/Fedora)
- Root privilege verification
- Bin directory writability (/usr/bin or ~/.local/bin)
- State directory writability (/var/lib or ~/.local/state)
- Package manager availability detection

### Tests Performed
1. **CMake configuration**: Successfully configured with new source file
2. **Build verification**: All targets built successfully including `rebuntu`
3. **Binary execution**: `/home/bvrznski/rebuntu/cpp/Build/src/rebuntu version` runs correctly

### Idempotency Considerations
The installation logic uses filesystem existence checks rather than markers, ensuring:
- Repeated execution does not duplicate artifacts
- State is determined from authoritative sources (filesystem)
- No shadow truth created

### Failure Behavior
- Exit code `1` for unknown commands
- Verification failures reported via `VerificationResult` structure
- Installation state determined independently of previous attempts

### Documentation Updates Required
- [x] Update README with installation instructions
- [x] Add Phase 1.0 section to ROADMAP.md
- [ ] Document native Linux requirements (systemd, apt)
- [ ] Add uninstall documentation for future Phase 1.11

### Rejected Alternatives
1. **Shell-only bootstrap**: Rejected in favor of C++20-native implementation per project doctrine
2. **Python-based installer**: Not architecturally justified (not a semantic/ML boundary)
3. **Single marker file approach**: Rejected to avoid shadow truth; prefer filesystem evidence

### Deferred Work
- [ ] Systemd unit installation logic
- [ ] Dependency resolution (apt/dpkg integration)
- [ ] User-scoped PATH configuration
- [ ] Uninstall implementation (Phase 1.11)

### Open Questions
1. Should Rebuntu provide its own package repository metadata?
2. How to handle partial installations that need repair?

### Verdict (Phase 1.2 Update)

**COMPLETE** (Phase 1.2)

All Phase 1.2 requirements implemented:
- ✅ Planner produces explicit installation plans with steps and rollback strategy
- ✅ PreflightEvaluator evaluates host readiness (distribution, privileges, directories)
- ✅ Idempotency tests - test_idempotent_plans() verifies plan consistency across repeated calls
- ✅ Failure-path tests - test_blocker_when_system_without_root(), test_user_scope_without_home()

---
### Verdict (Original Phase 1.0)
**PARTIALLY COMPLETE**

Implementation:
- ✅ Installation contracts defined in C++20
- ✅ Verification mechanism implemented
- ✅ Path resolution for system/user scope
- ✅ Planner produces explicit installation plans with steps and rollback strategy
- ✅ PreflightEvaluator evaluates host readiness (distribution, privileges, directories)
- ❌ Full installation executor (systemd, package manager)
- ❌ Idempotency tests
- ❌ Failure-path tests

Remaining work belongs to Phase 1.3+ for full installation execution with native Linux mechanisms.
