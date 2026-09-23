# Changelog

All notable changes to Rebuntu are recorded here. Format follows [Keep a
Changelog](https://keepachangelog.com) with semantic-versioning intent.

## [2.7.0] — Phase 2.7 (System/User/Session Scope) - UNRELEASED

### Added
- **scope module**: Canonical scope model for System, User, and Session boundaries
  - `rebuntu::environment::scope` namespace with contracts and implementation
  - `ExecutionScope` enum: kSystem, kUser, kSession context types
  - `ScopeContext` struct: full scope boundary state including paths
  - `XDGBases` struct: XDG Base Directory observation with POSIX fallbacks

### Added
- **Cross-scope mediation API**:
  - `mediate_cross_scope_request()`: Decision engine for cross-scope requests
  - `CrossScopeAction` enum: Allow, RequireElevation, RedirectToUser, SessionOnly, Deny
  - Human-readable explanations for each decision type

### Added
- **Path validation API**:
  - `validate_path_for_scope()`: Verify path belongs to expected scope
  - `PathValidationResultDetails`: Structured result with expectation tracking

### Changed
- Core contracts (`cpp/include/system/environment/scope.hpp`):
  - New scope header with ExecutionScope, ScopeContext, XDGBases types
  - Mediation and validation APIs with structured decision types

### Added
- **XDG Base Directory integration**:
  - `$XDG_CONFIG_HOME`, `$XDG_STATE_HOME`, `$XDG_CACHE_HOME`, `$XDG_DATA_HOME`
  - POSIX fallbacks ( ~/.config, ~/.local/state, etc. ) when env vars absent

## [2.0.0] — Phase 2.0 (Linux Host Foundation) - UNRELEASED

### Added
- **host_foundation module**: Canonical host foundation observer for Linux hosts
  - `rebuntu::host_foundation` namespace with contracts and implementation
  - `HostFoundation` class: observes host capabilities without side effects
  - `FoundationObservation`: typed evidence about host resources
  - `SupportDecision`: policy-driven evaluation of host support status

### Added
- **Nine foundation types** for Linux hosts:
  - kOsRelease (/etc/os-release for distro identification)
  - kKernel (Linux kernel availability via /proc/version)
  - kFilesystem (Unix ownership semantics via /etc/passwd)
  - kProcessModel (fork/exec/pipe system calls via /proc)
  - kSystemd (systemd manager availability)
  - kRuntimeDirectories (XDG_RUNTIME_DIR or /run fallbacks)
  - kUserNamespace (user namespace support via /proc/sys)
  - kNativeIdentity (NSS facilities via getpwnam/getpwuid)
  - kUmaskSupport (permission control via umask(2))

### Added
- **Three operational modes** with different capability requirements:
  - kMinimal: Basic CLI operations (no systemd required)
  - kServiceManaged: Service lifecycle via systemd
  - kFullFeature: All Rebuntu features including isolation

### Changed
- Core contracts (`cpp/include/system/core/contracts.hpp`):
  - Added new foundation types, status enums, and result structures

### Fixed
- Multiple namespace scoping issues in `lifecycle.cpp`

## [1.11.0] — Phase 1.11 (Lifecycle Management) - UNRELEASED

### Added
- **RECONFIGURE**: Change configuration without reinstalling
  - `rebuntu reconfigure <key=value> [key2=value2...]` command
  - Configuration file creation and updates at managed paths
  - Dry-run support (`--dry-run`)
  - Idempotent operations with verification

### Added
- **REPAIR**: Restore Rebuntu-owned installation invariants
  - `rebuntu repair [path1 path2...]` command
  - Detects missing artifacts, wrong permissions/types
  - Creates missing Rebuntu-owned directories and config files
  - Skips user-modified files (no silent overwrites)

### Added
- **UPGRADE**: Version-aware migration between schema versions
  - `rebuntu upgrade <target-version>` command  
  - Target version specification
  - Placeholder for future schema migrations

### Added
- **UNINSTALL/PURGE**: Remove Rebuntu-owned artifacts
  - `rebuntu uninstall [--dry-run] [--force]` command (standard mode)
  - `rebuntu purge [--dry-run]` command (removes everything including user config)
  - Only removes Rebuntu-owned artifacts by default
  - Idempotent operations

### Added
- **Artifact Manifest**: Lifecycle-owned inventory of managed files
  - Classifies artifacts as Rebuntu-owned, user-modified, external, or unknown
  - Supports verification and integrity checks
  - Used by repair/uninstall/purge to determine scope

### Changed
- Enhanced CLI (`cpp/src/cli.cpp`):
  - Full lifecycle command implementations with structured result output
  - Help flags (`--help`, `-h`) work for all lifecycle commands
  - Structured JSON-like output showing operations, created/deleted paths

### Changed
- Lifecycle contracts (`cpp/include/system/lifecycle/contracts.hpp`):
  - Added `to_string()` overload for `ArtifactOperation::Action`
  - All enum types now have string representations

### Fixed
- Multiple namespace scoping issues in `lifecycle.cpp`

## [0.0.0] — Phase 0.0 (Architectural Bootstrap)

### Added
- Repository skeleton: `src/system/` (primary structural package: core, shell,
  runtime, state, environment — reserved), `cpp/`, `bin/`, `tests/`, `scripts/`,
  `config/`, `systemd/`, `examples/`, `experiments/`, `tools/`, `schemas/`,
  `packaging/`, `docs/` (incl. `docs/discoveries/`).
- C++20 native foundation (CMake + CTest, no external deps):
  - `rebuntu::core` contracts: `Result`/`Outcome`/`Evidence`/`Error`,
    `SemanticStatus`, `OperationStatus`, `ComponentRegistry`.
  - `rebuntu::cli` and the `rebuntu` executable (`help`, `version`, `components`).
- Root documentation: README, AGENTS (updated), ARCHITECTURE, VOCABULARY,
  ONTOLOGY, SAFETY, DEVELOPMENT, ROADMAP, ARCHAEOLOGY, CHANGELOG, CONTRIBUTING,
  SECURITY.
- Tooling: `scripts/bootstrap.sh` (safe skeleton materializer),
  `scripts/generate_tree.sh` (regenerates `__tree__.txt`), `bin/rebuntu`
  (thin wrapper), `.gitignore`.
- Discovery mechanism: `docs/discoveries/` with initial records.

### Notes
- No system-management capability is implemented; no host-system changes; no
  services installed; no sudo required.
- `src/` is intentionally NOT created (the primary package is
  `src/system/`); the C++ namespace is `rebuntu::` (see
  `docs/discoveries/0002-system-namespace.md`).
