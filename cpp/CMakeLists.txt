# Rebuntu native C++20 foundation (Phase 0.0)
# ==================================================
#
# This is the Phase 0.0 repository architecture bootstrap.
# No runtime implementation exists yet - only structural skeleton
# and build configuration to verify the foundation.
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
# Subdirectories
# =============================================================================

# Core contracts and types (required by all other components)
add_subdirectory(src/core)

# Add src as an include directory for headers in src/ (repo root level)
target_include_directories(rebuntu-core INTERFACE ${CMAKE_CURRENT_LIST_DIR}/../src)

# Add src/system as include directory for headers in src/system/ (Phase 1 modules)
target_include_directories(rebuntu-core INTERFACE ${CMAKE_CURRENT_LIST_DIR}/../src)

# Phase 1.0-1.2: Installation module - add sources directly to rebuntu-core
set(INSTALL_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/../src/system/install)

add_library(rebuntu-install STATIC
    ${INSTALL_SRC_ROOT}/contracts.hpp
    ${INSTALL_SRC_ROOT}/planning.hpp
    ${INSTALL_SRC_ROOT}/install_planning.cpp
    ${INSTALL_SRC_ROOT}/discovery.hpp
    ${INSTALL_SRC_ROOT}/discovery.cpp
    ${INSTALL_SRC_ROOT}/bootstrap.cpp
)

target_include_directories(rebuntu-install PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-install)

# Phase 1.4 / 2.1: User identity module (Native Linux/NSS lookup)
set(USER_IDENTITY_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/../src/system/environment)

add_library(rebuntu-user-identity STATIC
    ${USER_IDENTITY_SRC_ROOT}/user_identity.cpp
)

target_include_directories(rebuntu-user-identity PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-user-identity)

# Phase 2.2: Group membership module (groups, membership & roles)
add_library(rebuntu-group-membership STATIC
    ${USER_IDENTITY_SRC_ROOT}/group_membership.cpp
)

target_include_directories(rebuntu-group-membership PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-group-membership)

# Phase 2.3: Ownership & permissions module (uid/gid/mode bits/umask)
add_library(rebuntu-ownership STATIC
    ${USER_IDENTITY_SRC_ROOT}/ownership.cpp
)

target_include_directories(rebuntu-ownership PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-ownership)

# Phase 2.4: Privilege & elevation module (uid/elevation/scope context)
add_library(rebuntu-privilege STATIC
    ${USER_IDENTITY_SRC_ROOT}/privilege.cpp
)

target_include_directories(rebuntu-privilege PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-privilege)

# Phase 2.5: Linux Capabilities module (CapPrm/CapEff/CapInh/CapBnd/CapAmb)
add_library(rebuntu-capability-state STATIC
    ${USER_IDENTITY_SRC_ROOT}/capability_state.cpp
)

target_include_directories(rebuntu-capability-state PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-capability-state)

# Phase 2.6: Authorization & scope module (policy decisions)
add_library(rebuntu-authorization STATIC
    ${USER_IDENTITY_SRC_ROOT}/authorization.cpp
)

target_include_directories(rebuntu-authorization PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-authorization)

# Phase 2.7: System/User/Session Scope module (scope resolution, XDG paths)
add_library(rebuntu-scope STATIC
    ${USER_IDENTITY_SRC_ROOT}/scope.hpp
    ${USER_IDENTITY_SRC_ROOT}/scope.cpp
)

target_include_directories(rebuntu-scope PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-scope)

# Phase 1.9: Environment discovery module (Hardware/Software environment)
add_library(rebuntu-environment-discovery STATIC
    ${USER_IDENTITY_SRC_ROOT}/environment_discovery.cpp
)

target_include_directories(rebuntu-environment-discovery PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-environment-discovery)

# Phase 2.8: Sessions & Runtime Identity module
add_library(rebuntu-sessions STATIC
    ${USER_IDENTITY_SRC_ROOT}/sessions.hpp
    ${USER_IDENTITY_SRC_ROOT}/sessions.cpp
)

target_include_directories(rebuntu-sessions PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-sessions)

# Phase 2.9: Directories module (Operational Directory Layout)
add_library(rebuntu-directories STATIC
    ${USER_IDENTITY_SRC_ROOT}/directories.hpp
    ${USER_IDENTITY_SRC_ROOT}/directories.cpp
)

target_include_directories(rebuntu-directories PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-directories)

# Phase 2.11: Secrets module (Secret Reference Model)
add_library(rebuntu-secrets STATIC
    ${USER_IDENTITY_SRC_ROOT}/secrets.hpp
    ${USER_IDENTITY_SRC_ROOT}/secrets.cpp
)

target_include_directories(rebuntu-secrets PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-secrets)

# Phase 2.12: Temporary files module (Secure Temp Files)
add_library(rebuntu-temp-files STATIC
    ${USER_IDENTITY_SRC_ROOT}/temp_files.hpp
    ${USER_IDENTITY_SRC_ROOT}/temp_files.cpp
)

target_include_directories(rebuntu-temp-files PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-temp-files)

# Phase 2.12: Locks module (Locking Primitives)
add_library(rebuntu-locks STATIC
    ${USER_IDENTITY_SRC_ROOT}/locks.hpp
    ${USER_IDENTITY_SRC_ROOT}/locks.cpp
)

target_include_directories(rebuntu-locks PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-locks)

# Phase 2.12: IPC module (Inter-Process Communication)
add_library(rebuntu-ipc STATIC
    ${USER_IDENTITY_SRC_ROOT}/ipc.hpp
    ${USER_IDENTITY_SRC_ROOT}/ipc.cpp
)

target_include_directories(rebuntu-ipc PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-ipc)

# Phase 1.8: Setup & configuration module (Phase 1.8)
set(SETUP_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/../src/system/setup)

add_library(rebuntu-setup STATIC
    ${SETUP_SRC_ROOT}/contracts.hpp
    ${SETUP_SRC_ROOT}/profile.cpp
    ${SETUP_SRC_ROOT}/profile.hpp
    ${SETUP_SRC_ROOT}/setup.cpp
)

target_include_directories(rebuntu-setup PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-setup)

# Phase 1.11: Lifecycle operations module (reconfigure, repair, upgrade, uninstall)
set(LIFECYCLE_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/../src/system/lifecycle)

add_library(rebuntu-lifecycle STATIC
    ${LIFECYCLE_SRC_ROOT}/contracts.hpp
    ${LIFECYCLE_SRC_ROOT}/lifecycle.cpp
)

target_include_directories(rebuntu-lifecycle PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)

target_link_libraries(rebuntu-core PUBLIC rebuntu-lifecycle)

# Phase 2.0: Linux Host Foundation module
set(HOST_FOUNDATION_SRC_ROOT ${CMAKE_CURRENT_LIST_DIR}/../src/system/host_foundation)
add_library(rebuntu-host-foundation STATIC
    ${HOST_FOUNDATION_SRC_ROOT}/contracts.hpp
    ${HOST_FOUNDATION_SRC_ROOT}/host_foundation.cpp
)
target_include_directories(rebuntu-host-foundation PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/../src
)
target_link_libraries(rebuntu-core PUBLIC rebuntu-host-foundation)

# Phase 3.9: Jenkins infrastructure provider (CI/CD integration)
set(JENKINS_SRC_ROOT "/home/bvrznski/rebuntu/src/system/infrastructure")

add_library(rebuntu-jenkins-provider STATIC
    ${JENKINS_SRC_ROOT}/jenkins.hpp
    ${JENKINS_SRC_ROOT}/jenkins_provider.cpp
)

target_include_directories(rebuntu-jenkins-provider PUBLIC
    /home/bvrznski/rebuntu/src
)
target_link_libraries(rebuntu-core PUBLIC rebuntu-jenkins-provider)

# Phase 3.10: Pipeline infrastructure provider (Build/Test/Deployment)
set(PIPELINE_SRC_ROOT "/home/bvrznski/rebuntu/src/system/infrastructure")

add_library(rebuntu-pipeline-provider STATIC
    ${PIPELINE_SRC_ROOT}/pipeline.hpp
    ${PIPELINE_SRC_ROOT}/pipeline_provider.cpp
)

target_include_directories(rebuntu-pipeline-provider PUBLIC
    /home/bvrznski/rebuntu/src
)
target_link_libraries(rebuntu-core PUBLIC rebuntu-pipeline-provider)

# Phase 3.11: Package metadata & environment reproducibility module
set(PACKAGES_HDRS "/home/bvrznski/rebuntu/src/domains/development/infrastructure/packages.hpp")
set(PACKAGES_SRCS "/home/bvrznski/rebuntu/src/domains/development/infrastructure/native/packages.cpp")

add_library(rebuntu-packages STATIC
    ${PACKAGES_HDRS}
    ${PACKAGES_SRCS}
)

target_include_directories(rebuntu-packages PUBLIC
    /home/bvrznski/rebuntu/src
)
target_link_libraries(rebuntu-core PUBLIC rebuntu-packages)

# SHA256 hashing implemented using pure C++ (FNV-1a algorithm) - no external dependencies required

# Tests subdirectory
add_subdirectory(tests)

# CLI entry point
add_subdirectory(src/rebuntu)
