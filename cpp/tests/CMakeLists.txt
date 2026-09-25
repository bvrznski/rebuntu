# Test configuration for Rebuntu runtime module (Phase 0.13-0.17)
add_executable(runtime_runner_test runtime_runner_test.cpp)
target_link_libraries(runtime_runner_test rebuntu-core)
target_include_directories(runtime_runner_test PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../include
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

# Phase 3.11: Package Metadata & Environment Reproducibility tests
add_executable(test_packages ../../tests/native/test_packages.cpp)
target_link_libraries(test_packages rebuntu-core rebuntu-packages)
target_include_directories(test_packages PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_packages COMMAND test_packages)

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

# Phase 2.11: Secrets module tests (Secret Reference Model)
add_executable(test_secrets test_secrets.cpp)
target_link_libraries(test_secrets rebuntu-core rebuntu-secrets rebuntu-scope)
add_test(NAME test_secrets COMMAND test_secrets)

# Phase 2.9: Directories module tests (Operational Directory Layout)
add_executable(test_directories test_directories.cpp)
target_link_libraries(test_directories rebuntu-core rebuntu-directories rebuntu-scope)
target_include_directories(test_directories PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_directories COMMAND test_directories)

# Phase 2.12: Locks module tests (Locking Primitives)
add_executable(test_locks test_locks.cpp)
target_link_libraries(test_locks rebuntu-core rebuntu-locks)
target_include_directories(test_locks PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_locks COMMAND test_locks)

# Phase 2.12: IPC module tests (Inter-Process Communication)
add_executable(test_ipc test_ipc.cpp)
target_link_libraries(test_ipc rebuntu-core rebuntu-ipc)
target_include_directories(test_ipc PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_ipc COMMAND test_ipc)

# Phase 2.12: Temp files module tests (Secure Temporary Files)
add_executable(test_temp_files test_temp_files.cpp)
target_link_libraries(test_temp_files rebuntu-core rebuntu-temp-files)
target_include_directories(test_temp_files PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME test_temp_files COMMAND test_temp_files)

# Phase 3.1: BitNet semantic provider tests (CPU-only)
add_executable(semantic_provider_test semantic_provider_test.cpp)
target_link_libraries(semantic_provider_test rebuntu-core)
target_include_directories(semantic_provider_test PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME semantic_provider_test COMMAND semantic_provider_test)

# Phase 3.2: Subprocess executor tests (timeout, I/O capture, CPU-only policy)
add_executable(subprocess_executor_test subprocess_executor_test.cpp)
target_link_libraries(subprocess_executor_test rebuntu-core)
target_include_directories(subprocess_executor_test PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME subprocess_executor_test COMMAND subprocess_executor_test)

# Phase 3.3: Native semantic service tests (lifecycle, readiness, health management)
add_executable(semantic_service_test semantic_service_test.cpp)
target_link_libraries(semantic_service_test rebuntu-core)
target_include_directories(semantic_service_test PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../include
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
# Add service implementation source directly to test target
target_sources(semantic_service_test PRIVATE
    ${CMAKE_SOURCE_DIR}/src/semantic/service.cpp
)
add_test(NAME semantic_service_test COMMAND semantic_service_test)

# Phase 3.4: IPC Protocol tests (frame serialization, validation, adversarial cases)
add_executable(test_ipc_protocol test_ipc_protocol.cpp)
target_link_libraries(test_ipc_protocol rebuntu-core)
target_include_directories(test_ipc_protocol PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/../include
)
# Add IPC transport sources for serialization/deserialization functions
target_sources(test_ipc_protocol PRIVATE
    ${CMAKE_SOURCE_DIR}/src/semantic/ipc_transport.cpp
)
add_test(NAME test_ipc_protocol COMMAND test_ipc_protocol)

# Phase 3.0: Infrastructure foundation tests
add_executable(infrastructure_test infrastructure_test.cpp)
target_link_libraries(infrastructure_test rebuntu-core)
target_include_directories(infrastructure_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
add_test(NAME infrastructure_test COMMAND infrastructure_test)

# Phase 3.6: Container runtime contracts tests
add_executable(test_container_runtime test_container_runtime.cpp)
target_link_libraries(test_container_runtime rebuntu-core)
target_include_directories(test_container_runtime PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
# Include container provider sources directly in the test target
target_sources(test_container_runtime PRIVATE
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/container.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/container_runtime.cpp
)
add_test(NAME test_container_runtime COMMAND test_container_runtime)

# Phase 3.5: Docker provider tests (Docker container runtime integration)
add_executable(test_docker_provider test_docker_provider.cpp)
target_link_libraries(test_docker_provider rebuntu-core)
target_include_directories(test_docker_provider PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
# Include docker provider sources directly in the test target
target_sources(test_docker_provider PRIVATE
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/docker.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/docker_provider.cpp
)
add_test(NAME test_docker_provider COMMAND test_docker_provider)

# Phase 3.7: Ansible provider tests (Ansible configuration management integration)
add_executable(test_ansible_provider test_ansible_provider.cpp)
target_link_libraries(test_ansible_provider rebuntu-core)
target_include_directories(test_ansible_provider PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
# Include ansible provider sources directly in the test target
target_sources(test_ansible_provider PRIVATE
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/ansible.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/ansible_provider.cpp
)
add_test(NAME test_ansible_provider COMMAND test_ansible_provider)

# Phase 3.9: Jenkins provider tests (Jenkins CI integration)
add_executable(test_jenkins_provider test_jenkins_provider.cpp)
target_link_libraries(test_jenkins_provider rebuntu-core)
# Include src first so <system/core/contracts.hpp> finds the correct header
target_include_directories(test_jenkins_provider PRIVATE 
    ${CMAKE_CURRENT_LIST_DIR}/../../src
    ${CMAKE_CURRENT_LIST_DIR}/../include
)
# Include jenkins provider sources directly in the test target (from src/system/infrastructure)
# CMAKE_SOURCE_DIR is /home/bvrznski/rebuntu/cpp, so ../src = /home/bvrznski/rebuntu/src
target_sources(test_jenkins_provider PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../src/system/infrastructure/jenkins.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../../src/system/infrastructure/jenkins_provider.cpp
)
add_test(NAME test_jenkins_provider COMMAND test_jenkins_provider)

# Phase 3.10: Pipeline provider tests (Build/Test/Deployment pipeline)
add_executable(test_pipeline_provider test_pipeline_provider.cpp)
target_link_libraries(test_pipeline_provider rebuntu-core)
target_include_directories(test_pipeline_provider PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)
# Include pipeline provider sources directly in the test target (from src/system/infrastructure)
target_sources(test_pipeline_provider PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/../../src/system/infrastructure/pipeline.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../../src/system/infrastructure/pipeline_provider.cpp
)
add_test(NAME test_pipeline_provider COMMAND test_pipeline_provider)

# Phase 1.9: Environment discovery tests (pending integration with testing framework)
