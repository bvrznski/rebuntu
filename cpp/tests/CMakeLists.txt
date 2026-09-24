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

# User identity tests (Phase 1.4 / 2.1)
add_executable(user_identity_test user_identity_test.cpp)
target_link_libraries(user_identity_test rebuntu-core)
target_include_directories(user_identity_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME user_identity_test COMMAND user_identity_test)

# Phase 1.9: Environment discovery tests (pending integration with testing framework)
