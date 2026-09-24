# Test configuration for Rebuntu runtime module (Phase 0.13-0.17)
add_executable(runtime_runner_test runtime_runner_test.cpp)
target_link_libraries(runtime_runner_test rebuntu-core)
target_include_directories(runtime_runner_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

add_executable(automation_test automation_test.cpp)
target_link_libraries(automation_test rebuntu-core)
target_include_directories(automation_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# State provider tests (Phase 0.14)
add_executable(test_runtime_contracts ../../tests/native/test_runtime_contracts.cpp)
target_link_libraries(test_runtime_contracts rebuntu-core)
target_include_directories(test_runtime_contracts PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

add_executable(test_state_provider ../../tests/native/test_state_provider.cpp)
target_link_libraries(test_state_provider rebuntu-core)
target_include_directories(test_state_provider PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Event communication tests (Phase 0.15)
add_executable(events_test events_test.cpp)
target_link_libraries(events_test rebuntu-core)
target_include_directories(events_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Results model tests (Phase 0.17)
add_executable(results_test results_test.cpp)
target_link_libraries(results_test rebuntu-core)
target_include_directories(results_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Settings Model tests (Phase 1.5)
add_executable(settings_test settings_test.cpp)
target_link_libraries(settings_test rebuntu-core)
target_include_directories(settings_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Preferences Model tests (Phase 1.7)
add_executable(preferences_test ../../tests/native/test_preferences.cpp)
target_link_libraries(preferences_test rebuntu-core)
target_include_directories(preferences_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Config & Specification Grammar tests (Phase 0.18)
add_executable(config_test config_test.cpp)
target_link_libraries(config_test rebuntu-core)
target_include_directories(config_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Installation planning tests (Phase 1.2)
add_executable(install_planning_test install_planning_test.cpp
    ${CMAKE_SOURCE_DIR}/../src/system/install/planning.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/install/install_planning.cpp
)
target_link_libraries(install_planning_test rebuntu-core)
target_include_directories(install_planning_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME install_planning_test COMMAND install_planning_test)
# Discovery tests (Phase 0.19)
set(DISCOVERY_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/discovery.hpp
    ${CMAKE_SOURCE_DIR}/../src/runtime/discovery.cpp
)

add_executable(test_discovery
    ../../tests/native/test_discovery.cpp
    ${DISCOVERY_SRCS}
)
target_link_libraries(test_discovery rebuntu-core)
target_include_directories(test_discovery PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Add tests to CTest
add_test(NAME runtime_runner_test COMMAND runtime_runner_test)
add_test(NAME automation_test COMMAND automation_test)
add_test(NAME test_runtime_contracts COMMAND test_runtime_contracts)
add_test(NAME test_state_provider COMMAND test_state_provider)
add_test(NAME events_test COMMAND events_test)
add_test(NAME results_test COMMAND results_test)
add_test(NAME test_discovery COMMAND test_discovery)
add_test(NAME settings_test COMMAND settings_test)
add_test(NAME config_test COMMAND config_test)
add_test(NAME preferences_test COMMAND preferences_test)

# Structured setup forms test (Phase 1.3)
add_executable(structured_setup_test ../../tests/rebuntu/test_structured_setup.cpp)
target_link_libraries(structured_setup_test rebuntu-core)
target_include_directories(structured_setup_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME structured_setup_test COMMAND structured_setup_test)

# Profile Generation & Application tests (Phase 1.10)
# Setup sources are added directly to rebuntu target in cpp/src/rebuntu/CMakeLists.txt
add_executable(profile_test ../../tests/native/test_profile.cpp)
target_link_libraries(profile_test rebuntu-core)
target_include_directories(profile_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME profile_test COMMAND profile_test)

# User identity tests (Phase 1.4 / 2.1)
add_executable(user_identity_test user_identity_test.cpp)
target_link_libraries(user_identity_test rebuntu-core)
target_include_directories(user_identity_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME user_identity_test COMMAND user_identity_test)

# Capability state tests (Phase 2.5)
add_executable(capability_state_test capability_state_test.cpp)
target_link_libraries(capability_state_test rebuntu-core rebuntu-capability-state)
target_include_directories(capability_state_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME capability_state_test COMMAND capability_state_test)

# Group membership tests (Phase 2.2)
add_executable(group_membership_test group_membership_test.cpp)
target_link_libraries(group_membership_test rebuntu-core rebuntu-group-membership)
target_include_directories(group_membership_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME group_membership_test COMMAND group_membership_test)

# Ownership & permissions tests (Phase 2.3)
add_executable(ownership_test ownership_test.cpp)
target_link_libraries(ownership_test rebuntu-core rebuntu-ownership)
target_include_directories(ownership_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME ownership_test COMMAND ownership_test)

# Phase 1.11: Lifecycle operations tests (reconfigure, repair, upgrade, uninstall)
add_executable(lifecycle_test lifecycle_test.cpp)
target_link_libraries(lifecycle_test rebuntu-core rebuntu-lifecycle)
target_include_directories(lifecycle_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME lifecycle_test COMMAND lifecycle_test)

# Phase 2.0: Host foundation tests
add_executable(host_foundation_test ../../tests/native/test_host_foundation.cpp
    ${CMAKE_SOURCE_DIR}/../src/system/host_foundation/contracts.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/host_foundation/host_foundation.cpp
)
target_link_libraries(host_foundation_test rebuntu-core rebuntu-host-foundation)
target_include_directories(host_foundation_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME host_foundation_test COMMAND host_foundation_test)

# Phase 2.7: Scope module tests
add_executable(test_scope test_scope.cpp)
target_link_libraries(test_scope rebuntu-core rebuntu-scope)
target_include_directories(test_scope PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_scope COMMAND test_scope)

# Phase 2.8: Sessions & Runtime Identity module tests
add_executable(test_sessions test_sessions.cpp)
target_link_libraries(test_sessions rebuntu-core rebuntu-sessions)
target_include_directories(test_sessions PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_sessions COMMAND test_sessions)

# Phase 2.9: Directories module tests (Operational Directory Layout)
add_executable(test_directories test_directories.cpp)
target_link_libraries(test_directories rebuntu-core rebuntu-directories rebuntu-scope)
target_include_directories(test_directories PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_directories COMMAND test_directories)

# Phase 1.9: Environment discovery tests (pending integration with testing framework)
