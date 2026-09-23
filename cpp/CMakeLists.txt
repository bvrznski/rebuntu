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

# CLI entry point
add_subdirectory(src/rebuntu)