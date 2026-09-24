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

# Phase 1.8: Setup & configuration sources are added to rebuntu target directly

# Tests subdirectory
add_subdirectory(tests)

# CLI entry point
add_subdirectory(src/rebuntu)
