# ===========================================================================
# Rebuntu — native C++ foundation (Phase 0.0)
# ===========================================================================
# The C++ implementation is Rebuntu's primary language (see AGENTS.md).
# This is a *conservative* baseline: C++20, CMake, CTest, no external
# dependencies. The goal of Phase 0.0 is a configures-and-builds native
# foundation with a real (small) semantic core, not a speculative runtime.
#
# Layout (conventional):
#   cpp/include/  public headers  (system::core contracts)
#   cpp/src/      implementation  (system::cli, the `rebuntu` entry point)
#   cpp/tests/    unit + integration tests (CTest)
# ===========================================================================
cmake_minimum_required(VERSION 3.16)

project(rebuntu
    VERSION 0.0.0
    DESCRIPTION "Rebuntu — C++-native Linux system-management environment"
    LANGUAGES CXX)

# --- Language standard -----------------------------------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --- Build type ------------------------------------------------------------
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()
string(TOLOWER "${CMAKE_BUILD_TYPE}" REBUNTU_BUILD_CONFIG)

# --- Warnings --------------------------------------------------------------
# Moderate, portable. Warnings are defects; they are not silenced globally.
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Wshadow)
endif()

# --- Shared project definitions -------------------------------------------
add_compile_definitions(REBUNTU_BUILD_CONFIG="${REBUNTU_BUILD_CONFIG}")

# --- IDE / tooling ---------------------------------------------------------
# Expose compile_commands.json so editors (e.g. VS Code C++ extension) resolve
# the correct C++20 standard and include paths.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Testing ---------------------------------------------------------------
include(CTest)
enable_testing()

# --- Subdirectories --------------------------------------------------------
add_subdirectory(src)
add_subdirectory(tests)
