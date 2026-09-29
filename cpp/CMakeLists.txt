# Rebuntu native C++20 foundation (Phase 0.0)
# ==================================================
#
# This is the Phase 4.18 Startup, Init & Dependency Chains update.
#

cmake_minimum_required(VERSION 3.22)

project(rebuntu-native
    VERSION 0.0.0
    DESCRIPTION "Rebuntu native C++20 foundation"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Build type defaults to Release for production, allows Debug for development
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build Type: ${CMAKE_BUILD_TYPE}")

# =============================================================================
# Compiler warnings (GCC/Clang)
# =============================================================================

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Wformat=2
        -Wnull-dereference
        -Wshift-overflow
        -Wduplicated-cond
        -Wduplicated-branches
        -Wlogical-op
        -Wcast-qual
        -Wcast-align
        -Wconversion
    )
endif()

# =============================================================================
# CTest integration
# =============================================================================

enable_testing()
include(CTest)

# =============================================================================
# Rebuntu uses a flat source structure with src/ at repository root
# The CMakeLists.txt is in cpp/ so we reference ../src for sources
# =============================================================================

add_library(rebuntu-core STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/interfaces/provider_registry.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/interfaces/discovery_resync.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/interfaces/inventory_index.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/services/contracts.cpp
)

target_include_directories(rebuntu-core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)

# Phase 5.52: Observation Memory Bounds module
add_library(rebuntu-observation-bounds STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/bounds.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/bounds.cpp
)
target_include_directories(rebuntu-observation-bounds PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-observation-bounds)

# Phase 7.1: Facts & Observations Model module (core types and interfaces)
# Header-only library - included via rebuntu-core
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/model.hpp
)

# Phase 7.2: State Acquisition Service module
add_library(rebuntu-state-acquisition STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/snapshot_builder.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/state_acquisition_service.cpp
)
target_include_directories(rebuntu-state-acquisition PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-state-acquisition rebuntu-observation-bounds)

# Phase 7.3: State Normalization module (normalizer registry and domain-specific normalizers)
add_library(rebuntu-state-normalizer STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/state_normalizer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/state_normalizer.cpp
)
target_include_directories(rebuntu-state-normalizer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-state-normalizer rebuntu-state-acquisition)

# Phase 6.0: Shell Language Foundation module
add_library(rebuntu-shell STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/parser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/parser.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/predicates.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/predicates.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/values.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/verbs/list.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/verbs/list.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/verbs/mapping.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/verbs/mapping.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/context.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/context.cpp
)

# Phase 6.16: Semi-Natural Command Grammar module
add_library(rebuntu-shell-semi-natural STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/semi_natural.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/semi_natural.cpp
)

target_include_directories(rebuntu-shell-semi-natural PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell-semi-natural)

# Phase 6.15: Contextual Command Resolution module
add_library(rebuntu-shell-context STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/context.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/context.cpp
)

target_include_directories(rebuntu-shell-context PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell-context)

# Phase 6.15: Contextual Command Resolution unit tests
add_executable(rebuntu-context-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/shell_context_test.cpp
)
target_include_directories(rebuntu-context-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-context-test PRIVATE rebuntu-core rebuntu-shell)
add_test(NAME context_test COMMAND rebuntu-context-test)

# Phase 6.17: Semantic Boundary module (shell command language interpretation boundary)
add_library(rebuntu-shell-boundary STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/boundary/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/boundary/integration.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/boundary/integration.cpp
)

target_include_directories(rebuntu-shell-boundary PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell-boundary)

# Phase 6.14: Command Collision Detection module
add_library(rebuntu-shell-collision STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/collision_scanner.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/collision_scanner.cpp
)
target_include_directories(rebuntu-shell-collision PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell-collision)

# Phase 6.10: Pipeline Semantics module (shell stream processing)
add_library(rebuntu-shell-pipeline STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/pipeline.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/pipeline.cpp
)

target_include_directories(rebuntu-shell-pipeline PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell-pipeline)

# Phase 6.4: Qualifiers & Modifiers module (header-only, included via rebuntu-shell)
# The qualifiers are header-only and used directly by parser.hpp

# Phase 6.3: Subject Vocabulary module (header-only library)
add_library(rebuntu-shell-subjects INTERFACE)
target_include_directories(rebuntu-shell-subjects INTERFACE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core INTERFACE rebuntu-shell-subjects)
target_include_directories(rebuntu-shell PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell)

# Phase 6.11: Structured Output module
add_library(rebuntu-shell-output STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/output/contract.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/output/contract.cpp
)
target_include_directories(rebuntu-shell-output PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell-output)

# Phase 6.19: Output Capture Semantics module
add_library(rebuntu-shell-output-capture STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/output/capture.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/output/capture.cpp
)
target_include_directories(rebuntu-shell-output-capture PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-shell-output-capture)

# Phase 6.1: Typed Command Model module (header-only, included via rebuntu-core)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/model.hpp
)

# Phase 6.28: Execution Plan Explain-Plan Output module
add_library(rebuntu-command-explain STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/explain.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/explain.cpp
)
target_include_directories(rebuntu-command-explain PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-command-explain)

# Phase 6.22: Verification Freshness module (header-only)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/core/freshness.hpp
)

# Phase 6.23: Idempotency Classification System
add_library(rebuntu-idempotency STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/idempotency/classifier.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/idempotency/classifier.cpp
)
target_include_directories(rebuntu-idempotency PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-idempotency)

# Add common runtime source files for Phase 4.18 and 6.21 verification
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/production.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/native/production_runtime.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/contracts.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/work.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/engine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/runner.cpp
)

# Phase 4.8: Resolver module - target resolution without execution
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/resolver.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/resolver.cpp
)

# Phase 6.69: Read File Operation (vertical slice)
add_library(rebuntu-read-file-operation STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/read_file.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/read_file.cpp
)
target_include_directories(rebuntu-read-file-operation PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-read-file-operation)

# Phase 6.27: Dry-Run Semantics module
add_library(rebuntu-dry-run STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/dry_run.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/dry_run.cpp
)
target_include_directories(rebuntu-dry-run PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-dry-run)

# Phase 0.10: Filesystem Operations module
add_library(rebuntu-filesystem STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/filesystem.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/filesystem.cpp
)
target_include_directories(rebuntu-filesystem PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-filesystem)

# Phase 6.77: User Management Operations module
add_library(rebuntu-users STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/users.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/operations/users.cpp
)
target_include_directories(rebuntu-users PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-users)

# Phase 6.24: Retry Mechanics Integration module
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/retry_mechanics.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/retry_mechanics.cpp
)

# Phase 6.48: IPC Command Boundary module (process-separated callers)
add_library(rebuntu-ipc-command-boundary STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/ipc/command_boundary.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/ipc/command_boundary.cpp
)
target_include_directories(rebuntu-ipc-command-boundary PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-ipc-command-boundary)

# Phase 6.41: Command Replay Semantics module (intent vs stale plan semantics)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/replay.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/replay.cpp
)

# Phase 6.40: Crash Reconciliation module
# Types header is included via runtime/contracts.hpp dependency chain
# Detector is header-only, added to rebuntu-core source list
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/reconciliation/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/reconciliation/detector.hpp
)

# Phase 1.0-1.2: Installation module
add_library(rebuntu-install STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/install/contracts.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/install/planning.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/install/install_planning.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/install/discovery.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/install/discovery.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/install/bootstrap.cpp
)

target_include_directories(rebuntu-install PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-install)

# Phase 1.4 / 2.1: User identity module (Native Linux/NSS lookup)
add_library(rebuntu-user-identity STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/user_identity.cpp
)
target_include_directories(rebuntu-user-identity PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-user-identity)

# Phase 2.2: Group membership module (groups, membership & roles)
add_library(rebuntu-group-membership STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/group_membership.cpp
)
target_include_directories(rebuntu-group-membership PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-group-membership)

# Phase 2.3: Ownership & permissions module (uid/gid/mode bits/umask)
add_library(rebuntu-ownership STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/ownership.cpp
)
target_include_directories(rebuntu-ownership PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-ownership)

# Phase 2.4: Privilege & elevation module (uid/elevation/scope context)
add_library(rebuntu-privilege STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/privilege.cpp
)
target_include_directories(rebuntu-privilege PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-privilege)

# Phase 2.5: Linux Capabilities module
add_library(rebuntu-capability-state STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/capability_state.cpp
)
target_include_directories(rebuntu-capability-state PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-capability-state)

# Phase 2.6: Authorization & scope module (policy decisions)
add_library(rebuntu-authorization STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/authorization.cpp
)
target_include_directories(rebuntu-authorization PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-authorization)

# Phase 2.7: System/User/Session Scope module (scope resolution, XDG paths)
add_library(rebuntu-scope STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/scope.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/scope.cpp
)
target_include_directories(rebuntu-scope PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-scope)

# Phase 1.9: Environment discovery module (Hardware/Software environment)
add_library(rebuntu-environment-discovery STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/environment_discovery.cpp
)
target_include_directories(rebuntu-environment-discovery PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-environment-discovery)

# Phase 2.8: Sessions & Runtime Identity module
add_library(rebuntu-sessions STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/sessions.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/sessions.cpp
)
target_include_directories(rebuntu-sessions PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-sessions)

# Phase 2.9: Directories module (Operational Directory Layout)
add_library(rebuntu-directories STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/directories.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/directories.cpp
)
target_include_directories(rebuntu-directories PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-directories)

# Phase 2.11: Secrets module (Secret Reference Model)
add_library(rebuntu-secrets STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/secrets.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/secrets.cpp
)
target_include_directories(rebuntu-secrets PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-secrets)

# Phase 2.12: Temporary files module (Secure Temp Files)
add_library(rebuntu-temp-files STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/temp_files.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/temp_files.cpp
)
target_include_directories(rebuntu-temp-files PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-temp-files)

# Phase 2.12: Locks module (Locking Primitives)
add_library(rebuntu-locks STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/locks.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/locks.cpp
)
target_include_directories(rebuntu-locks PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-locks)

# Phase 2.12: IPC module (Inter-Process Communication)
add_library(rebuntu-ipc STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/ipc.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment/ipc.cpp
)
target_include_directories(rebuntu-ipc PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-ipc)

# Phase 1.8: Setup & configuration module (Phase 1.8)
add_library(rebuntu-setup STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/setup/contracts.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/setup/profile.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/setup/profile.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/setup/setup.cpp
)
target_include_directories(rebuntu-setup PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-setup)

# Phase 1.11: Lifecycle operations module (reconfigure, repair, upgrade, uninstall)
add_library(rebuntu-lifecycle STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/lifecycle/contracts.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/lifecycle/lifecycle.cpp
)
target_include_directories(rebuntu-lifecycle PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-lifecycle)

# Phase 5.1: System Event Collector module
add_library(rebuntu-events-collector STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/events/collector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/events/collector.cpp
)
target_include_directories(rebuntu-events-collector PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-events-collector)

# Phase 5.12: Evidence Collector module (bounded provenance-rich diagnostic evidence collection)
add_library(rebuntu-evidence-collector STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/evidence/collector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/evidence/collector.cpp
)
target_include_directories(rebuntu-evidence-collector PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-evidence-collector)

# Phase 5.41: Evidence Deduplication module (typed observation deduplication with provenance preservation)
add_library(rebuntu-evidence-deduplication STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/evidence/deduplication.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/evidence/deduplication.cpp
)
target_include_directories(rebuntu-evidence-deduplication PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-evidence-deduplication)

# Phase 5.44: Observation Query Foundation module (narrow typed queries over observations)
# NOTE: This library is header-only and causes CMake to fail to determine linker language
# Temporarily disabled until proper implementation is added
# add_library(rebuntu-observation-query STATIC
#     ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/observation/query_types.hpp
# )
# target_include_directories(rebuntu-observation-query PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-core PUBLIC rebuntu-observation-query)

# Phase 5.61: Observation Output Schema (machine-readable output with versioning)
add_library(rebuntu-observation-output STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/output/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/observation/output/json_serializer.cpp
)
target_include_directories(rebuntu-observation-output PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-observation-output)

# Snapshot Service (types only - no implementation yet, interface is in types.hpp)
# Phase 5.13: Snapshot Service module (diagnostic snapshot creation and storage)
add_library(rebuntu-snapshot-service STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot/error.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot/evidence.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot/service.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot/service.cpp
)
target_include_directories(rebuntu-snapshot-service PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot)
target_include_directories(rebuntu-snapshot-service PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-snapshot-service)

# Phase 5.13: FileStorage for snapshot persistence
add_library(rebuntu-snapshot-storage STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot/file_storage.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot/file_storage.cpp
)
target_include_directories(rebuntu-snapshot-storage PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/system/diagnostics/snapshot)
target_include_directories(rebuntu-snapshot-storage PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-snapshot-storage)

# Phase 5.2: Journald acquisition adapter module
add_library(rebuntu-journald-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/journald.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/journald.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/subprocess_utility.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/subprocess_utility.cpp
)
target_include_directories(rebuntu-journald-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-journald-adapter)

# Phase 6.38: Execution Journald Diagnostics Emitter module
add_library(rebuntu-exec-diag STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/exec_diag.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/exec_diag.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/subprocess_utility.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/subprocess_utility.cpp
)
target_include_directories(rebuntu-exec-diag PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-exec-diag)

# Phase 6.38: Execution Journald Diagnostics unit tests - test file missing
# add_executable(rebuntu-exec-diag-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/exec_diag_test.cpp
# )
# target_link_libraries(rebuntu-exec-diag-test PRIVATE rebuntu-exec-diag rebuntu-core)
# add_test(NAME exec_diag_test COMMAND rebuntu-exec-diag-test)

# Phase 5.17: Procfs Mounts Observation Adapter module
add_library(rebuntu-procfs-mounts STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/mounts/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/mounts/implementation.cpp
)
target_include_directories(rebuntu-procfs-mounts PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-procfs-mounts)

# Phase 5.54: Procfs Error Types and Adversarial Audit module
add_library(rebuntu-procfs-errors STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/error.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/error.cpp
)
target_include_directories(rebuntu-procfs-errors PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-procfs-errors)

# Phase 5.19: Encrypted Storage Observation Adapter module (LUKS/device-mapper)
add_library(rebuntu-encrypted-storage-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/encrypted_storage/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/encrypted_storage/implementation.cpp
)
target_include_directories(rebuntu-encrypted-storage-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-encrypted-storage-adapter)

# Phase 5.20: md RAID Observation Adapter module (Software RAID)
add_library(rebuntu-md-raid-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/md_raid/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/md_raid/implementation.cpp
)
target_include_directories(rebuntu-md-raid-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-md-raid-adapter)

# Phase 5.34: Power Supply Observation Adapter module
add_library(rebuntu-power-supply-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/power/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/power/implementation.cpp
)
target_include_directories(rebuntu-power-supply-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-power-supply-adapter)

# Phase 5.34: Thermal Zone Observation Adapter module
add_library(rebuntu-thermal-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/thermal/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/sysfs/thermal/implementation.cpp
)
target_include_directories(rebuntu-thermal-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-thermal-adapter)

# Phase 5.36: Udev/Sysfs Peripheral Discovery Adapter module
add_library(rebuntu-peripherals STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/peripherals/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/peripherals/implementation.cpp
)
target_include_directories(rebuntu-peripherals PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-peripherals)

# Phase 5.48: Hotplug Device State Management module
add_library(rebuntu-hotplug STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/hotplug/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/hotplug/implementation.cpp
)
target_include_directories(rebuntu-hotplug PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-hotplug)

# Phase 5.21: Netlink Link/Interface Discovery Adapter module
add_library(rebuntu-netlink-link STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/link/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/link/implementation.cpp
)
target_include_directories(rebuntu-netlink-link PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-netlink-link)

# Netlink Link Discovery unit tests - test file missing
# add_executable(rebuntu-netlink-link-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/netlink_link_test.cpp
# )
# target_link_libraries(rebuntu-netlink-link-test PRIVATE rebuntu-netlink-link rebuntu-core)
# add_test(NAME netlink_link_test COMMAND rebuntu-netlink-link-test)

# Phase 5.22: Netlink Route Observation Adapter module
add_library(rebuntu-netlink-route STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/route/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/route/implementation.cpp
)
target_include_directories(rebuntu-netlink-route PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-netlink-route)

# Netlink Route Discovery unit tests - test file missing
# add_executable(rebuntu-netlink-route-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/netlink_route_test.cpp
# )
# target_link_libraries(rebuntu-netlink-route-test PRIVATE rebuntu-netlink-route rebuntu-core)
# add_test(NAME netlink_route_test COMMAND rebuntu-netlink-route-test)

# Phase 5.23: Netlink Socket/Listener Observation Adapter module
add_library(rebuntu-netlink-socket STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/socket/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/socket/implementation.cpp
)
target_include_directories(rebuntu-netlink-socket PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-netlink-socket)

# Netlink Socket Discovery unit tests - test file missing
# add_executable(rebuntu-netlink-socket-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/netlink_socket_test.cpp
# )
# target_link_libraries(rebuntu-netlink-socket-test PRIVATE rebuntu-netlink-socket rebuntu-core)
# add_test(NAME netlink_socket_test COMMAND rebuntu-netlink-socket-test)

# Phase 5.35: DRM/KMS Display Topology Observation Adapter module
add_library(rebuntu-drm-topology STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/drm/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/drm/implementation.cpp
)
target_include_directories(rebuntu-drm-topology PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-drm-topology)

# DRM Display Topology Discovery unit tests - test file missing
# add_executable(rebuntu-drm-topology-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/drm_topology_test.cpp
# )
# target_link_libraries(rebuntu-drm-topology-test PRIVATE rebuntu-drm-topology rebuntu-core)
# add_test(NAME drm_topology_test COMMAND rebuntu-drm-topology-test)

# Phase 5.24: Procfs Process Discovery Adapter module
add_library(rebuntu-procfs-process STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/process/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/process/implementation.cpp
)
target_include_directories(rebuntu-procfs-process PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-procfs-process)

# Phase 7.5: Procfs Process Discovery Integration Tests
add_executable(rebuntu-procfs-process-integration-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/procfs_process_integration_test.cpp
)
target_include_directories(rebuntu-procfs-process-integration-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-procfs-process-integration-test PRIVATE rebuntu-core rebuntu-procfs-process)
add_test(NAME procfs_process_integration_test COMMAND rebuntu-procfs-process-integration-test)

# Phase 6.56: PID Reuse and Transient Identity Adversarial Tests - test file missing
# add_executable(rebuntu-pid-reuse-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/pid_reuse_adversarial_test.cpp
# )
# target_include_directories(rebuntu-pid-reuse-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-pid-reuse-test PRIVATE rebuntu-procfs-process rebuntu-core)
# add_test(NAME pid_reuse_test COMMAND rebuntu-pid-reuse-test)

# Phase 5.50: Provider Isolation and Degradation unit tests (Task 5.50) - test file missing
# add_executable(rebuntu-isolated-provider-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/isolated_provider_test.cpp
# )
# target_link_libraries(rebuntu-isolated-provider-test PRIVATE rebuntu-core)
# add_test(NAME isolated_provider_test COMMAND rebuntu-isolated-provider-test)

# Phase 6.52: Provider Result Distrust unit tests (ProviderEvidence, ProviderResult types) - test file missing
# add_executable(rebuntu-provider-evidence-test
#     ${CMAKE_CURRENT_LIST_DIR}/../tests/provider_evidence_test.cpp
# )
# target_include_directories(rebuntu-provider-evidence-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-provider-evidence-test PRIVATE rebuntu-core)
# add_test(NAME provider_evidence_test COMMAND rebuntu-provider-evidence-test)

# Phase 6.1: Typed Command Model unit tests - test file missing
# add_executable(rebuntu-command-model-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/command_model_test.cpp
# )
# target_link_libraries(rebuntu-command-model-test PRIVATE rebuntu-core)
# add_test(NAME command_model_test COMMAND rebuntu-command-model-test)

# Phase 6.14: Command Collision Scanner unit tests - test file missing
# add_executable(rebuntu-collision-scanner-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/collision_scanner_test.cpp
# )
# target_link_libraries(rebuntu-collision-scanner-test PRIVATE rebuntu-core rebuntu-shell-collision)
# target_include_directories(rebuntu-collision-scanner-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# add_test(NAME collision_scanner_test COMMAND rebuntu-collision-scanner-test)

# Phase 6.2: Predicate Dictionary unit tests - test file missing
# add_executable(rebuntu-predicates-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/predicates_test.cpp
# )
# target_link_libraries(rebuntu-predicates-test PRIVATE rebuntu-core rebuntu-shell)
# target_include_directories(rebuntu-predicates-test PRIVATE ${CMAKE_SOURCE_DIR})
# add_test(NAME predicates_test COMMAND rebuntu-predicates-test)

# Phase 6.5: Scope Grammar unit tests - test file missing
# add_executable(rebuntu-scope-grammar-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/shell_scope_grammar_test.cpp
# )
# target_link_libraries(rebuntu-scope-grammar-test PRIVATE rebuntu-core rebuntu-shell)
# target_include_directories(rebuntu-scope-grammar-test PRIVATE ${CMAKE_SOURCE_DIR})
# add_test(NAME scope_grammar_test COMMAND rebuntu-scope-grammar-test)

# Phase 6.10: Pipeline Semantics unit tests - test file missing
# add_executable(rebuntu-pipeline-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/pipeline_test.cpp
# )
# target_link_libraries(rebuntu-pipeline-test PRIVATE rebuntu-core rebuntu-shell rebuntu-shell-pipeline)
# target_include_directories(rebuntu-pipeline-test PRIVATE ${CMAKE_SOURCE_DIR})
# add_test(NAME pipeline_test COMMAND rebuntu-pipeline-test)

# Phase 6.6: Value Parsers unit tests - test file missing
# add_executable(rebuntu-value-parsers-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/value_parsers_test.cpp
# )
# target_link_libraries(rebuntu-value-parsers-test PRIVATE rebuntu-core rebuntu-shell)
# target_include_directories(rebuntu-value-parsers-test PRIVATE ${CMAKE_SOURCE_DIR})
# add_test(NAME value_parsers_test COMMAND rebuntu-value-parsers-test)

# Phase 5.32: Kernel Module Observation Adapter module (procfs modules)
add_library(rebuntu-procfs-modules STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/modules/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/modules/implementation.cpp
)
target_include_directories(rebuntu-procfs-modules PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-procfs-modules)

# Phase 5.33: Firmware Observation Adapter module (sysfs DMI/SMBIOS)
add_library(rebuntu-firmware-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/firmware/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/firmware/implementation.cpp
)
target_include_directories(rebuntu-firmware-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-firmware-adapter)

# Phase 5.31: DPKG Package Inventory Adapter module
add_library(rebuntu-dpkg-package-inventory STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/package_managers/dpkg/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/package_managers/dpkg/implementation.cpp
)
target_include_directories(rebuntu-dpkg-package-inventory PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-dpkg-package-inventory)

# DPKG Package Inventory unit tests (disabled - gtest not available)
# add_executable(rebuntu-dpkg-package-inventory-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/dpkg_package_inventory_test.cpp
# )
# target_link_libraries(rebuntu-dpkg-package-inventory-test PRIVATE rebuntu-dpkg-package-inventory rebuntu-core)
# add_test(NAME dpkg_package_inventory_test COMMAND rebuntu-dpkg-package-inventory-test)


# Phase 5.43: Semantic Annotation Boundary module
add_library(rebuntu-semantic-annotation STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/semantic/annotation.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/semantic/annotation.cpp
)
target_include_directories(rebuntu-semantic-annotation PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-semantic-annotation)

# Phase 5.26: Systemd Service Discovery Adapter module
add_library(rebuntu-systemd-service-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/systemd/service/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/systemd/service/implementation.cpp
)
target_include_directories(rebuntu-systemd-service-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-systemd-service-adapter)

# Systemd Service Discovery unit tests - test file missing
# add_executable(rebuntu-systemd-service-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/systemd_service_test.cpp
# )
# target_link_libraries(rebuntu-systemd-service-test PRIVATE rebuntu-systemd-service-adapter rebuntu-core)
# add_test(NAME systemd_service_test COMMAND rebuntu-systemd-service-test)

# Phase 5.32: Kernel Module Discovery unit tests - test file missing
# add_executable(rebuntu-procfs-modules-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/procfs_modules_test.cpp
# )
# target_link_libraries(rebuntu-procfs-modules-test PRIVATE rebuntu-procfs-modules rebuntu-core)
# add_test(NAME procfs_modules_test COMMAND rebuntu-procfs-modules-test)

# Phase 5.28: Cgroup v2 Hierarchy Discovery unit tests - test file missing
# add_executable(rebuntu-cgroup-hierarchy-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/cgroup_hierarchy_test.cpp
# )
# target_link_libraries(rebuntu-cgroup-hierarchy-test PRIVATE rebuntu-cgroup-hierarchy-adapter rebuntu-core)
# add_test(NAME cgroup_hierarchy_test COMMAND rebuntu-cgroup-hierarchy-test)

# Phase 5.3: Journal filtering and normalization module
add_library(rebuntu-journal-normalizer STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/journal_normalizer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/journal_normalizer.cpp
)
target_include_directories(rebuntu-journal-normalizer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-journal-normalizer)

# Phase 5.4: Journal analyzer module
add_library(rebuntu-journal-analyzer STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/journal_analyzer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/journal_analyzer.cpp
)
target_include_directories(rebuntu-journal-analyzer PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-journal-analyzer)

# Phase 5.6: Process & Service Health Monitor module
add_library(rebuntu-health-monitor STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/health_monitor/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/health_monitor/health_monitor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/health_monitor/health_monitor.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/health_monitor/adapters/journald_observer.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/health_monitor/adapters/journald_observer.cpp
)
target_include_directories(rebuntu-health-monitor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-health-monitor)

# Phase 5.7: Kernel / Driver Fault Monitor module
add_library(rebuntu-kernel-fault-detector STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/kernel_fault_detector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/kernel_fault_detector.cpp
)
target_include_directories(rebuntu-kernel-fault-detector PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-kernel-fault-detector)

# Phase 5.8: Storage & Filesystem Health Monitor module
add_library(rebuntu-storage-health-monitor STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/storage_health_monitor/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/storage_health_monitor/storage_health_monitor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/storage_health_monitor/storage_health_monitor.cpp
)
target_include_directories(rebuntu-storage-health-monitor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/modules/storage_health_monitor)
target_include_directories(rebuntu-storage-health-monitor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-storage-health-monitor)

# Phase 5.9: CPU / Memory / Thermal Monitor module
add_library(rebuntu-cpu-memory-thermal-monitor STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/cpu_memory_thermal_monitor/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/cpu_memory_thermal_monitor/monitor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/cpu_memory_thermal_monitor/monitor.cpp
)
target_include_directories(rebuntu-cpu-memory-thermal-monitor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/modules/cpu_memory_thermal_monitor)
target_include_directories(rebuntu-cpu-memory-thermal-monitor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-cpu-memory-thermal-monitor)

# Phase 5.10: GPU Health Monitor module
add_library(rebuntu-gpu-health-monitor STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/gpu_health_monitor/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/gpu_health_monitor/monitor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/gpu_health_monitor/monitor.cpp
)
target_include_directories(rebuntu-gpu-health-monitor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/modules/gpu_health_monitor)
target_include_directories(rebuntu-gpu-health-monitor PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-gpu-health-monitor)

# Phase 5.14: Internal Alert Service module
add_library(rebuntu-internal-alerts STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/internal_alerts/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/internal_alerts/processor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/internal_alerts/processor.cpp
)
target_include_directories(rebuntu-internal-alerts PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/modules/internal_alerts)
target_include_directories(rebuntu-internal-alerts PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-internal-alerts)

# Phase 5.27: Session Observation Adapter (utmp/wtmp/btmp)
add_library(rebuntu-session-utmp STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/session/utmp/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/session/utmp/implementation.cpp
)
target_include_directories(rebuntu-session-utmp PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-session-utmp)

# Phase 5.28: Cgroup v2 Hierarchy Observation Adapter module
add_library(rebuntu-cgroup-hierarchy-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/cgroups/hierarchy/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/cgroups/hierarchy/implementation.cpp
)
target_include_directories(rebuntu-cgroup-hierarchy-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-cgroup-hierarchy-adapter)

# Phase 5.15: Reporting & Notification module
add_library(rebuntu-reporting STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/reporting/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/reporting/generator.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/reporting/generator.cpp
)
target_include_directories(rebuntu-reporting PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/modules/reporting)
target_include_directories(rebuntu-reporting PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-reporting)

# Phase 5.41: Evidence Deduplication unit tests - test file missing
# add_executable(rebuntu-evidence-deduplication-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/evidence_deduplication_test.cpp
# )
# target_link_libraries(rebuntu-evidence-deduplication-test PRIVATE rebuntu-evidence-deduplication rebuntu-core)
# target_include_directories(rebuntu-evidence-deduplication-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# add_test(NAME evidence_deduplication_test COMMAND rebuntu-evidence-deduplication-test)

# Phase 5.15: Reporting & Notification unit tests (disabled - gtest not available)
# add_executable(rebuntu-reporting-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/reporting_test.cpp
# )
# target_link_libraries(rebuntu-reporting-test PRIVATE rebuntu-reporting rebuntu-core gtest_main)
# add_test(NAME reporting_test COMMAND rebuntu-reporting-test)

# Phase 5.11: Hang / Stall / Jam Detection module
add_library(rebuntu-hang-stall-jam-detector STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/hang_stall_jam/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/hang_stall_jam/stall_detector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/modules/hang_stall_jam/stall_detector.cpp
)
target_include_directories(rebuntu-hang-stall-jam-detector PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src/modules/hang_stall_jam)
target_include_directories(rebuntu-hang-stall-jam-detector PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-hang-stall-jam-detector)

# Stall Detector unit tests - test file missing
# add_executable(rebuntu-hang-stall-jam-detector-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/hang_stall_jam_detector_test.cpp
# )
# target_link_libraries(rebuntu-hang-stall-jam-detector-test PRIVATE rebuntu-hang-stall-jam-detector rebuntu-core)
# add_test(NAME hang_stall_jam_detector_test COMMAND rebuntu-hang-stall-jam-detector-test)

# Phase 5.51: Parallel Discovery Infrastructure (header-only library)
# The implementation is entirely in parallel_discovery.hpp as a header-only template library
# Include the header directly via rebuntu-core's include path

# Phase 5.51: Parallel Discovery Infrastructure unit tests - test file missing
# add_executable(rebuntu-parallel-discovery-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/parallel_discovery_test.cpp
# )
# target_link_libraries(rebuntu-parallel-discovery-test PRIVATE rebuntu-core)
# add_test(NAME parallel_discovery_test COMMAND rebuntu-parallel-discovery-test)

# Phase 5.40: Discovery Resynchronization Interface unit tests - test file missing
# add_executable(rebuntu-discovery-resync-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/discovery_resync_test.cpp
# )
# target_include_directories(rebuntu-discovery-resync-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-discovery-resync-test PRIVATE rebuntu-core)
# add_test(NAME discovery_resync_test COMMAND rebuntu-discovery-resync-test)

# Phase 5.27: Session Observation Adapter unit tests
# add_executable(rebuntu-session-utmp-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/session_utmp_test.cpp
# )
# target_link_libraries(rebuntu-session-utmp-test PRIVATE rebuntu-session-utmp rebuntu-core gtest_main)
# add_test(NAME session_utmp_test COMMAND rebuntu-session-utmp-test)

# Phase 5.60: CLI inventory inspection module
add_library(rebuntu-cli-inventory STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/cli/inventory/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/cli/inventory/query.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/cli/inventory/query.cpp
)
target_include_directories(rebuntu-cli-inventory PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-cli-inventory PUBLIC rebuntu-core rebuntu-dpkg-package-inventory)

# Rebuntu CLI inventory tests - test file missing
# add_executable(rebuntu-cli-inventory-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/cli_inventory_test.cpp
# )
# target_link_libraries(rebuntu-cli-inventory-test PRIVATE rebuntu-core rebuntu-dpkg-package-inventory rebuntu-cli-inventory)
# target_include_directories(rebuntu-cli-inventory-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# add_test(NAME cli_inventory_test COMMAND rebuntu-cli-inventory-test)

# Rebuntu CLI binary (includes parser boundary from Task 6.46)
add_executable(rebuntu-bin
    ${CMAKE_CURRENT_LIST_DIR}/../src/cli/main.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/cli/parser.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/cli/parser.cpp
)
target_include_directories(rebuntu-bin PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-bin PRIVATE rebuntu-core rebuntu-cli-inventory rebuntu-shell)

# Phase 6.20: Exit Result Semantics unit tests
add_executable(rebuntu-exit-result-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/exit_result_test.cpp
)
target_include_directories(rebuntu-exit-result-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-exit-result-test PRIVATE rebuntu-core)
add_test(NAME exit_result_test COMMAND rebuntu-exit-result-test)

# Phase 6.23: Idempotency Classifier unit tests
add_executable(rebuntu-idempotency-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/idempotency_classifier_test.cpp
)
target_include_directories(rebuntu-idempotency-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-idempotency-test PRIVATE rebuntu-core rebuntu-idempotency)
add_test(NAME idempotency_classifier_test COMMAND rebuntu-idempotency-test)

# Phase 6.24: Retry Mechanics Integration unit tests
add_executable(rebuntu-retry-mechanics-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/retry_mechanics_test.cpp
)
target_include_directories(rebuntu-retry-mechanics-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-retry-mechanics-test PRIVATE rebuntu-core)
add_test(NAME retry_mechanics_test COMMAND rebuntu-retry-mechanics-test)

# Phase 6.30: Monotonic Deadline System unit tests
add_executable(rebuntu-monotonic-deadline-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/monotonic_deadline_test.cpp
)
target_include_directories(rebuntu-monotonic-deadline-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-monotonic-deadline-test PRIVATE rebuntu-core)
add_test(NAME monotonic_deadline_test COMMAND rebuntu-monotonic-deadline-test)

# Phase 6.60: Malformed Provider Output Tests (Task 6.60) - test file missing
# add_executable(rebuntu-provider-malformed-output-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/provider_malformed_output_test.cpp
# )
# target_include_directories(rebuntu-provider-malformed-output-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-provider-malformed-output-test PRIVATE rebuntu-core rebuntu-procfs-process)
# add_test(NAME provider_malformed_output_test COMMAND rebuntu-provider-malformed-output-test)

# Phase 5.61: Observation Output unit tests (disabled - gtest not available in CTest)
# add_executable(rebuntu-observation-output-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/observation_output_test.cpp
# )
# target_link_libraries(rebuntu-observation-output-test PRIVATE rebuntu-core rebuntu-observation-output)
# add_test(NAME observation_output_test COMMAND rebuntu-observation-output-test)

# Phase 5.29: Namespace Observation Adapter module
add_library(rebuntu-namespaces-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/namespaces/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/namespaces/implementation.cpp
)
target_include_directories(rebuntu-namespaces-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-namespaces-adapter)

# Phase 5.30: Container Runtime Discovery Adapter module
add_library(rebuntu-container-discovery STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/container/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/container/implementation.cpp
)
target_include_directories(rebuntu-container-discovery PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-container-discovery)

# Phase 2.0: Linux Host Foundation module
add_library(rebuntu-host-foundation STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/host_foundation/contracts.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/host_foundation/host_foundation.cpp
)
target_include_directories(rebuntu-host-foundation PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-host-foundation)

# Phase 5.46: Cross-Domain Entity References module (types + stub implementation)
add_library(rebuntu-cross-domain-references STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/interfaces/cross_domain_references.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/interfaces/cross_domain_references.cpp
)
target_include_directories(rebuntu-cross-domain-references PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-cross-domain-references)

# Phase 5.47: Relationship Evidence module (provenance tracking for discovered relationships)
add_library(rebuntu-relationship-evidence STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/observation/system-observation-inventory-discovery/relationships/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/observation/system-observation-inventory-discovery/relationships/implementation.cpp
)
target_include_directories(rebuntu-relationship-evidence PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-relationship-evidence)

# Cross-Domain References unit tests (disabled - gtest not available in CTest)
# add_executable(rebuntu-cross-domain-references-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/cross_domain_references_test.cpp
# )
# target_link_libraries(rebuntu-cross-domain-references-test PRIVATE rebuntu-cross-domain-references rebuntu-core gtest_main)
# add_test(NAME cross_domain_references_test COMMAND rebuntu-cross-domain-references-test)

# Phase 5.48: Hotplug Device State Management unit tests - test file missing
# add_executable(rebuntu-hotplug-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/hotplug_test.cpp
# )
# target_link_libraries(rebuntu-hotplug-test PRIVATE rebuntu-hotplug rebuntu-core)
# add_test(NAME hotplug_test COMMAND rebuntu-hotplug-test)

# Phase 5.55: Netlink/Udev Adversarial Audit unit tests - test file missing
# add_executable(rebuntu-netlink-adversarial-audit-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/netlink_adversarial_audit_test.cpp
# )
# target_link_libraries(rebuntu-netlink-adversarial-audit-test PRIVATE rebuntu-core)
# add_test(NAME netlink_adversarial_audit_test COMMAND rebuntu-netlink-adversarial-audit-test)

# Phase 5.59: Journald evidence integration - journal slice collector
add_library(rebuntu-evidence-journal-slice STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/evidence/journal_slice_collector.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/evidence/journal_slice_collector.cpp
)
target_include_directories(rebuntu-evidence-journal-slice PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-evidence-journal-slice)

# Journald evidence integration unit tests (test file missing - placeholder)
# add_executable(rebuntu-evidence-journal-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/evidence_journal_test.cpp
# )
# target_link_libraries(rebuntu-evidence-journal-test PRIVATE rebuntu-evidence-journal-slice rebuntu-core)
# add_test(NAME evidence_journal_test COMMAND rebuntu-evidence-journal-test)

# Phase 5.63: Unit and Provider Test Matrix (comprehensive test coverage) - test file missing
# add_executable(rebuntu-provider-test-matrix
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/provider_test_matrix.cpp
# )
# target_link_libraries(rebuntu-provider-test-matrix PRIVATE rebuntu-core)
# add_test(NAME provider_test_matrix COMMAND rebuntu-provider-test-matrix)

# Phase 6.35: Privileged Helper System for native command operation execution
add_library(rebuntu-privileged-helpers STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/native-command-operation-execution/security/privileged_helper.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/native-command-operation-execution/security/privileged_helper.cpp
)
target_include_directories(rebuntu-privileged-helpers PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-privileged-helpers)

# Privileged Helper unit tests (tests the validation and execution logic) - test file missing
# add_executable(rebuntu-privilege-requirement-test
#     ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/native-command-operation-execution/security/test_privileged_helpers.cpp
# )
# target_include_directories(rebuntu-privilege-requirement-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-privilege-requirement-test PRIVATE rebuntu-core rebuntu-privileged-helpers)
# add_test(NAME privilege_helper_test COMMAND rebuntu-privilege-requirement-test)

# Phase 6.13: Bash completion script (shell sourceable artifact)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/../src/system/shell/completion/bash_completion.sh
    DESTINATION share/rebuntu/bash-completion.d
)

# Phase 6.31: Execution Concurrency Control module (narrow locking by stable identity)
add_library(rebuntu-concurrency-control STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/concurrency/control.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/concurrency/control.cpp
)
target_include_directories(rebuntu-concurrency-control PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-concurrency-control)

# Phase 6.31: Concurrency Control unit tests (disabled - gtest not available in CTest)
# add_executable(rebuntu-concurrency-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/concurrency_control_test.cpp
# )
# target_link_libraries(rebuntu-concurrency-test PRIVATE rebuntu-concurrency-control rebuntu-core)
# add_test(NAME concurrency_control_test COMMAND rebuntu-concurrency-test)

# Phase 6.17: Semantic Boundary unit tests - test file missing
# add_executable(rebuntu-shell-boundary-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/shell_boundary_test.cpp
# )
# target_link_libraries(rebuntu-shell-boundary-test PRIVATE rebuntu-core rebuntu-shell-boundary)
# target_include_directories(rebuntu-shell-boundary-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# add_test(NAME shell_boundary_test COMMAND rebuntu-shell-boundary-test)

# Phase 6.51: Semantic Service Absence Behavior unit tests - test file missing
# add_executable(rebuntu-semantic-service-absence-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/semantic_service_absence_test.cpp
# )
# target_link_libraries(rebuntu-semantic-service-absence-test PRIVATE rebuntu-core rebuntu-shell rebuntu-shell-boundary)
# target_include_directories(rebuntu-semantic-service-absence-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# add_test(NAME semantic_service_absence_test COMMAND rebuntu-semantic-service-absence-test)

# Phase 6.19: Output capture semantics unit tests - test file missing
# add_executable(rebuntu-shell-output-capture-test
#     /home/bvrznski/rebuntu/tests/unit/shell_output_capture_test.cpp
# )
# target_link_libraries(rebuntu-shell-output-capture-test PRIVATE rebuntu-core rebuntu-shell-output-capture)
# target_include_directories(rebuntu-shell-output-capture-test PRIVATE /home/bvrznski/rebuntu/src)
# add_test(NAME shell_output_capture_test COMMAND rebuntu-shell-output-capture-test)

# Phase 6.34: Privilege Requirement Metadata unit tests (duplicate - covered by privileged helper test above)
# Phase 6.29: Operation Cancellation Points module
add_library(rebuntu-cancellation-points STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/cancellation/points.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/cancellation/points.cpp
)
target_include_directories(rebuntu-cancellation-points PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-cancellation-points)

# Phase 6.41: Command Replay Semantics unit tests - test file missing
# add_executable(rebuntu-replay-test
#     /home/bvrznski/rebuntu/tests/unit/replay_test.cpp
# )
# target_link_libraries(rebuntu-replay-test PRIVATE rebuntu-core)
# add_test(NAME replay_test COMMAND rebuntu-replay-test)

# Phase 6.13: Shell output contract unit tests (disabled - gtest not available in CTest)
# add_executable(rebuntu-shell-output-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/shell_output_contract_test.cpp
# )
# target_link_libraries(rebuntu-shell-output-test PRIVATE rebuntu-core rebuntu-shell-output)
# add_test(NAME shell_output_test COMMAND rebuntu-shell-output-test)

# Phase 6.42: Typed Batch Command Boundary module (header-only, included via rebuntu-core)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/batch.hpp
)

# Phase 6.42: Batch Command Boundary unit tests - test file missing
# add_executable(rebuntu-batch-command-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/batch_command_test.cpp
# )
# target_link_libraries(rebuntu-batch-command-test PRIVATE rebuntu-core)
# add_test(NAME batch_command_test COMMAND rebuntu-batch-command-test)

# Phase 6.43: Typed Sequential Composition module (header-only, included via rebuntu-core)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/sequential.hpp
)

# Phase 6.44: Typed Parallel Composition module (header-only, included via rebuntu-core)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/parallel.hpp
)

# Phase 6.43: Typed Sequential Composition unit tests - test file missing
# add_executable(rebuntu-sequential-composition-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/sequential_composition_test.cpp
# )
# target_link_libraries(rebuntu-sequential-composition-test PRIVATE rebuntu-core)
# add_test(NAME sequential_composition_test COMMAND rebuntu-sequential-composition-test)

# Phase 6.44: Typed Parallel Composition unit tests - test file missing
# add_executable(rebuntu-parallel-composition-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/parallel_composition_test.cpp
# )
# target_link_libraries(rebuntu-parallel-composition-test PRIVATE rebuntu-core)
# add_test(NAME parallel_composition_test COMMAND rebuntu-parallel-composition-test)

# Phase 6.45: Dependency-Aware Execution module (header-only, included via rebuntu-core)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/command/dependencies.hpp
)

# Phase 6.45: Dependency-Aware Execution unit tests - test file missing
# add_executable(rebuntu-dependency-aware-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/dependency_aware_execution_test.cpp
# )
# target_link_libraries(rebuntu-dependency-aware-test PRIVATE rebuntu-core)
# add_test(NAME dependency_aware_test COMMAND rebuntu-dependency-aware-test)

# Phase 6.39: Execution Record Persistence module
add_library(rebuntu-exec-persistence STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/persistence/integration.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/persistence/integration.cpp
)
target_include_directories(rebuntu-exec-persistence PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-exec-persistence)

# Phase 6.47: Machine-readable command boundary module (versioned structured input)
add_library(rebuntu-command-input STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/interfaces/cli/input.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/interfaces/cli/input.cpp
)
target_include_directories(rebuntu-command-input PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-command-input)

# Phase 6.47: Machine-readable command boundary unit tests (disabled - gtest not available in CTest)
# add_executable(rebuntu-command-input-test
#     /home/bvrznski/rebuntu/tests/unit/command_input_test.cpp
# )
# target_link_libraries(rebuntu-command-input-test PRIVATE rebuntu-core rebuntu-command-input)
# add_test(NAME command_input_test COMMAND rebuntu-command-input-test)

# Phase 6.54: Stale-plan adversarial tests - test file missing
# add_executable(rebuntu-stale-plan-adversarial-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/stale_plan_adversarial_test.cpp
# )
# target_include_directories(rebuntu-stale-plan-adversarial-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-stale-plan-adversarial-test PRIVATE rebuntu-core)
# add_test(NAME stale_plan_adversarial_test COMMAND rebuntu-stale-plan-adversarial-test)

# Phase 6.55: Ambiguous-target adversarial tests - test file missing
# add_executable(rebuntu-ambiguous-target-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/ambiguous_target_adversarial_test.cpp
# )
# target_include_directories(rebuntu-ambiguous-target-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-ambiguous-target-test PRIVATE rebuntu-core)
# add_test(NAME ambiguous_target_test COMMAND rebuntu-ambiguous-target-test)

# Phase 6.57: Device Reorder Tests - test file missing
# add_executable(rebuntu-device-reorder-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/device_reorder_test.cpp
# )
# target_include_directories(rebuntu-device-reorder-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-device-reorder-test PRIVATE rebuntu-core rebuntu-drm-topology rebuntu-peripherals rebuntu-hotplug)
# add_test(NAME device_reorder_test COMMAND rebuntu-device-reorder-test)

# Phase 6.58: Command Injection Adversarial Tests - test file missing
# add_executable(rebuntu-command-injection-adversarial-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/command_injection_adversarial_test.cpp
# )
# target_include_directories(rebuntu-command-injection-adversarial-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
# target_link_libraries(rebuntu-command-injection-adversarial-test PRIVATE rebuntu-core rebuntu-shell)
# add_test(NAME command_injection_adversarial_test COMMAND rebuntu-command-injection-adversarial-test)

# Phase 6.64: Privilege Escalation Adversarial Tests
add_executable(rebuntu-privilege-escalation-adversarial-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/privilege_escalation_adversarial_test.cpp
)
target_include_directories(rebuntu-privilege-escalation-adversarial-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-privilege-escalation-adversarial-test PRIVATE rebuntu-core)
add_test(NAME privilege_escalation_adversarial_test COMMAND rebuntu-privilege-escalation-adversarial-test)

# Phase 6.61: Execution Storm and Backpressure Tests
add_executable(rebuntu-execution-storm-backpressure-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/execution_storm_backpressure_test.cpp
)
target_include_directories(rebuntu-execution-storm-backpressure-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-execution-storm-backpressure-test PRIVATE rebuntu-core)
add_test(NAME execution_storm_backpressure_test COMMAND rebuntu-execution-storm-backpressure-test)

# Phase 6.30: SubprocessExecutor implementation (Phase 4.17)
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/subprocess_executor.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/subprocess_executor.cpp
)

# Phase 6.62: Cancellation Race Condition Tests
add_executable(rebuntu-cancellation-race-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/cancellation_race_test.cpp
)
target_include_directories(rebuntu-cancellation-race-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-cancellation-race-test PRIVATE rebuntu-core)
add_test(NAME cancellation_race_test COMMAND rebuntu-cancellation-race-test)

# Phase 6.69: Read File Operation Tests
add_executable(rebuntu-read-file-operation-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/read_file_operation_test.cpp
)
target_include_directories(rebuntu-read-file-operation-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-read-file-operation-test PRIVATE rebuntu-core rebuntu-read-file-operation)
add_test(NAME read_file_operation_test COMMAND rebuntu-read-file-operation-test)

# Phase 6.70: Contained Mutation Integration Test
# Tests for filesystem.copy operation with before/after observation + verification
add_executable(rebuntu-mutation-integration-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/filesystem_mutation_integration_test.cpp
)
target_include_directories(rebuntu-mutation-integration-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-mutation-integration-test PRIVATE rebuntu-core rebuntu-filesystem)
add_test(NAME mutation_integration_test COMMAND rebuntu-mutation-integration-test)

# Phase 6.71: Read-Only Command Integration Tests
# Tests for QUERY/OBSERVE commands with UNKNOWN/partial/freshness handling
add_executable(rebuntu-read-only-command-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/read_only_command_integration_test.cpp
)
target_include_directories(rebuntu-read-only-command-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-read-only-command-test PRIVATE rebuntu-core rebuntu-filesystem)
add_test(NAME read_only_command_test COMMAND rebuntu-read-only-command-test)

# Phase 6.63: Timeout Ambiguity Tests (Task 6.63)
add_executable(rebuntu-timeout-ambiguity-test
    ${CMAKE_CURRENT_LIST_DIR}/../tests/unit/timeout_after_commit_test.cpp
)
target_include_directories(rebuntu-timeout-ambiguity-test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-timeout-ambiguity-test PRIVATE rebuntu-core)
add_test(NAME timeout_ambiguity_test COMMAND rebuntu-timeout-ambiguity-test)

