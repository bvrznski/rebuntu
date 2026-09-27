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
    ${CMAKE_CURRENT_LIST_DIR}/../src/system/services/contracts.cpp
)

target_include_directories(rebuntu-core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_include_directories(rebuntu-core PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../cpp/include)

# Add common runtime source files for Phase 4.18
target_sources(rebuntu-core PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/production.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/native/production_runtime.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/contracts.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/work.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/runtime/engine.cpp
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
)
target_include_directories(rebuntu-journald-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-journald-adapter)

# Phase 5.17: Procfs Mounts Observation Adapter module
add_library(rebuntu-procfs-mounts STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/mounts/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/mounts/implementation.cpp
)
target_include_directories(rebuntu-procfs-mounts PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-procfs-mounts)

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

# Phase 5.21: Netlink Link/Interface Discovery Adapter module
add_library(rebuntu-netlink-link STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/link/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/link/implementation.cpp
)
target_include_directories(rebuntu-netlink-link PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-netlink-link)

# Netlink Link Discovery unit tests
add_executable(rebuntu-netlink-link-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/netlink_link_test.cpp
)
target_link_libraries(rebuntu-netlink-link-test PRIVATE rebuntu-netlink-link rebuntu-core)
add_test(NAME netlink_link_test COMMAND rebuntu-netlink-link-test)

# Phase 5.22: Netlink Route Observation Adapter module
add_library(rebuntu-netlink-route STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/route/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/route/implementation.cpp
)
target_include_directories(rebuntu-netlink-route PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-netlink-route)

# Netlink Route Discovery unit tests
add_executable(rebuntu-netlink-route-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/netlink_route_test.cpp
)
target_link_libraries(rebuntu-netlink-route-test PRIVATE rebuntu-netlink-route rebuntu-core)
add_test(NAME netlink_route_test COMMAND rebuntu-netlink-route-test)

# Phase 5.23: Netlink Socket/Listener Observation Adapter module
add_library(rebuntu-netlink-socket STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/socket/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/netlink/socket/implementation.cpp
)
target_include_directories(rebuntu-netlink-socket PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-netlink-socket)

# Netlink Socket Discovery unit tests
add_executable(rebuntu-netlink-socket-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/netlink_socket_test.cpp
)
target_link_libraries(rebuntu-netlink-socket-test PRIVATE rebuntu-netlink-socket rebuntu-core)
add_test(NAME netlink_socket_test COMMAND rebuntu-netlink-socket-test)

# Phase 5.35: DRM/KMS Display Topology Observation Adapter module
add_library(rebuntu-drm-topology STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/drm/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/drm/implementation.cpp
)
target_include_directories(rebuntu-drm-topology PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-drm-topology)

# DRM Display Topology Discovery unit tests
add_executable(rebuntu-drm-topology-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/drm_topology_test.cpp
)
target_link_libraries(rebuntu-drm-topology-test PRIVATE rebuntu-drm-topology rebuntu-core)
add_test(NAME drm_topology_test COMMAND rebuntu-drm-topology-test)

# Phase 5.24: Procfs Process Discovery Adapter module
add_library(rebuntu-procfs-process STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/process/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/procfs/process/implementation.cpp
)
target_include_directories(rebuntu-procfs-process PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-procfs-process)

# Procfs Process Discovery unit tests
add_executable(rebuntu-procfs-process-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/procfs_process_test.cpp
)
target_link_libraries(rebuntu-procfs-process-test PRIVATE rebuntu-procfs-process rebuntu-core)
add_test(NAME procfs_process_test COMMAND rebuntu-procfs-process-test)

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


# Phase 5.26: Systemd Service Discovery Adapter module
add_library(rebuntu-systemd-service-adapter STATIC
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/systemd/service/types.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../src/adapters/systemd/service/implementation.cpp
)
target_include_directories(rebuntu-systemd-service-adapter PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../src)
target_link_libraries(rebuntu-core PUBLIC rebuntu-systemd-service-adapter)

# Systemd Service Discovery unit tests
add_executable(rebuntu-systemd-service-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/systemd_service_test.cpp
)
target_link_libraries(rebuntu-systemd-service-test PRIVATE rebuntu-systemd-service-adapter rebuntu-core)
add_test(NAME systemd_service_test COMMAND rebuntu-systemd-service-test)

# Phase 5.32: Kernel Module Discovery unit tests
add_executable(rebuntu-procfs-modules-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/procfs_modules_test.cpp
)
target_link_libraries(rebuntu-procfs-modules-test PRIVATE rebuntu-procfs-modules rebuntu-core)
add_test(NAME procfs_modules_test COMMAND rebuntu-procfs-modules-test)

# Phase 5.28: Cgroup v2 Hierarchy Discovery unit tests

add_executable(rebuntu-cgroup-hierarchy-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/cgroup_hierarchy_test.cpp
)
target_link_libraries(rebuntu-cgroup-hierarchy-test PRIVATE rebuntu-cgroup-hierarchy-adapter rebuntu-core)
add_test(NAME cgroup_hierarchy_test COMMAND rebuntu-cgroup-hierarchy-test)

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

# Stall Detector unit tests
add_executable(rebuntu-hang-stall-jam-detector-test
    ${CMAKE_CURRENT_LIST_DIR}/tests/unit/hang_stall_jam_detector_test.cpp
)
target_link_libraries(rebuntu-hang-stall-jam-detector-test PRIVATE rebuntu-hang-stall-jam-detector rebuntu-core)
add_test(NAME hang_stall_jam_detector_test COMMAND rebuntu-hang-stall-jam-detector-test)

# Phase 5.27: Session Observation Adapter unit tests
# add_executable(rebuntu-session-utmp-test
#     ${CMAKE_CURRENT_LIST_DIR}/tests/unit/session_utmp_test.cpp
# )
# target_link_libraries(rebuntu-session-utmp-test PRIVATE rebuntu-session-utmp rebuntu-core gtest_main)
# add_test(NAME session_utmp_test COMMAND rebuntu-session-utmp-test)

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
