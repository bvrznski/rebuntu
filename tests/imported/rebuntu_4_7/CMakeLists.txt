# CTest-registered native tests (Phase 0.2).
# Zero external dependencies; a minimal assertion harness is used.

# Unit tests: the core contracts (header-only semantic primitives).
add_executable(test_contracts test_contracts.cpp)
target_link_libraries(test_contracts PRIVATE system)
add_test(NAME unit.contracts COMMAND test_contracts)

# Unit tests: the runtime contracts (Phase 0.2 operational grammar).
add_executable(test_runtime_contracts test_runtime_contracts.cpp)
target_link_libraries(test_runtime_contracts PRIVATE system)
add_test(NAME unit.runtime_contracts COMMAND test_runtime_contracts)

# Unit tests: core initialization (Phase 4.1).
add_executable(test_initialization test_initialization.cpp)
target_link_libraries(test_initialization PRIVATE system)
add_test(NAME unit.initialization COMMAND test_initialization)

# Integration tests: the `rebuntu` CLI dispatch and structured output.
add_executable(test_cli test_cli.cpp)
target_link_libraries(test_cli PRIVATE system)
add_test(NAME integration.cli COMMAND test_cli)

# Unit tests: the Operation contracts (Phase 0.10).
add_executable(test_operations test_operations.cpp)
target_link_libraries(test_operations PRIVATE system)

add_executable(test_results test_results.cpp)
target_link_libraries(test_results PRIVATE system)
add_test(NAME unit.results COMMAND test_results)
add_test(NAME unit.operations COMMAND test_operations)

# Unit tests: the work ontology (Phase 0.8).
add_executable(test_work test_work.cpp)
target_link_libraries(test_work PRIVATE system)
add_test(NAME unit.work COMMAND test_work)

# Unit tests: the workflow contracts (Phase 0.11).
add_executable(test_workflow test_workflow.cpp)
target_link_libraries(test_workflow PRIVATE system)
add_test(NAME unit.workflow COMMAND test_workflow)

# Unit tests: state provider interface (Phase 0.14).
add_executable(test_state_provider test_state_provider.cpp)
target_link_libraries(test_state_provider PRIVATE system)
add_test(NAME unit.state_provider COMMAND test_state_provider)

# Unit tests: the automation contracts (Phase 0.12).
add_executable(test_automation test_automation.cpp)
target_link_libraries(test_automation PRIVATE system)
add_test(NAME unit.automation COMMAND test_automation)

# Unit tests: the executor runtime (Phase 0.13).
add_executable(test_executor test_executor.cpp)
target_link_libraries(test_executor PRIVATE system)
add_test(NAME unit.executor COMMAND test_executor)

# Integration tests: the executor runtime (Phase 0.13).
add_executable(test_executor_integration test_executor_integration.cpp)
target_link_libraries(test_executor_integration PRIVATE system)
add_test(NAME integration.executor COMMAND test_executor_integration)

add_executable(test_discovery test_discovery.cpp)
target_link_libraries(test_discovery PRIVATE system)
add_test(NAME unit.discovery COMMAND test_discovery)

# Unit tests: environment discovery (Phase 1.1)
add_executable(test_discovery_env test_discovery_env.cpp)
target_link_libraries(test_discovery_env PRIVATE system)
add_test(NAME unit.discovery_env COMMAND test_discovery_env)

# Unit tests: configuration grammar (Phase 0.18).

# Unit tests: installation planning (Phase 1.2)
add_executable(test_install_planning
    test_install_planning.cpp
    ../src/install_planning.cpp
    ../src/environment_discovery.cpp
    ../src/user_identity.cpp
)
target_include_directories(test_install_planning PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Unit tests: settings model (Phase 1.5)
add_executable(test_settings test_settings.cpp)
target_link_libraries(test_settings PRIVATE system)
target_include_directories(test_settings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.settings COMMAND test_settings)

# Unit tests: forms infrastructure (Phase 1.3)
add_executable(test_forms test_forms.cpp)
target_link_libraries(test_forms PRIVATE system)
target_include_directories(test_forms PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.forms COMMAND test_forms)

# Unit tests: preferences model (Phase 1.7)
add_executable(test_preferences test_preferences.cpp)
target_link_libraries(test_preferences PRIVATE system)
target_include_directories(test_preferences PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.preferences COMMAND test_preferences)

# Unit tests: setup & configuration machinery (Phase 1.8)
add_executable(test_setup test_setup.cpp)
target_link_libraries(test_setup PRIVATE system)
target_include_directories(test_setup PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.setup COMMAND test_setup)

# Unit tests: profile generation & application (Phase 1.10)
add_executable(test_profile test_profile.cpp)
target_link_libraries(test_profile PRIVATE system)
target_include_directories(test_profile PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.profile COMMAND test_profile)

# Unit tests: lifecycle operations (Phase 1.11)
add_executable(test_lifecycle test_lifecycle.cpp)
target_link_libraries(test_lifecycle PRIVATE system)
target_include_directories(test_lifecycle PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.lifecycle COMMAND test_lifecycle)

# Unit tests: host foundation contracts (Phase 2.0)
add_executable(test_host_foundation test_host_foundation.cpp)
target_link_libraries(test_host_foundation PRIVATE system)
target_include_directories(test_host_foundation PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.host_foundation COMMAND test_host_foundation)

# Unit tests: privilege & elevation contracts (Phase 2.4)
add_executable(test_privilege test_privilege.cpp)
target_link_libraries(test_privilege PRIVATE system)
target_include_directories(test_privilege PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.privilege COMMAND test_privilege)

# Unit tests: Linux capabilities (Phase 2.5)
add_executable(test_capability_state test_capability_state.cpp)
target_link_libraries(test_capability_state PRIVATE system)
target_include_directories(test_capability_state PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.capability_state COMMAND test_capability_state)

# Unit tests: Authorization & Scope (Phase 2.6)
add_executable(test_authorization test_authorization.cpp)
target_link_libraries(test_authorization PRIVATE system)
target_include_directories(test_authorization PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.authorization COMMAND test_authorization)

# Unit tests: System/User/Session Scope (Phase 2.7)
add_executable(test_scope test_scope.cpp)
target_link_libraries(test_scope PRIVATE system)
target_include_directories(test_scope PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.scope COMMAND test_scope)

# Unit tests: Sessions & Runtime Identity (Phase 2.8)
add_executable(test_sessions test_sessions.cpp)
target_link_libraries(test_sessions PRIVATE system)
target_include_directories(test_sessions PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.sessions COMMAND test_sessions)

# Unit tests: Operational Directory Layout (Phase 2.9)
add_executable(test_directories test_directories.cpp)
target_link_libraries(test_directories PRIVATE system)
target_include_directories(test_directories PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.directories COMMAND test_directories)

# Unit tests: Secure Temporary Files (Phase 2.12)
add_executable(test_temp_files test_temp_files.cpp)
target_link_libraries(test_temp_files PRIVATE system)
target_include_directories(test_temp_files PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.temp_files COMMAND test_temp_files)

# Unit tests: Configuration & Secrets Locations (Phase 2.11)
add_executable(test_config_storage test_config_storage.cpp)
target_link_libraries(test_config_storage PRIVATE system)
target_include_directories(test_config_storage PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.config_storage COMMAND test_config_storage)

# Unit tests: Locking Primitives (Phase 2.13)
add_executable(test_locks test_locks.cpp)
target_link_libraries(test_locks PRIVATE system)
target_include_directories(test_locks PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.locks COMMAND test_locks)

# Unit tests: IPC Mechanisms (Phase 2.13) - TODO: Add test_ipc.cpp
# add_executable(test_ipc test_ipc.cpp)
# target_link_libraries(test_ipc PRIVATE system)
# target_include_directories(test_ipc PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
# add_test(NAME unit.ipc COMMAND test_ipc)

# Unit tests: Engineering Infrastructure Foundation (Phase 3.0)
add_executable(test_infrastructure test_infrastructure.cpp)
target_link_libraries(test_infrastructure PRIVATE system)
target_include_directories(test_infrastructure PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.infrastructure COMMAND test_infrastructure)

# Unit tests: Container Runtime Contracts (Phase 3.6)
add_executable(test_container_runtime test_container_runtime.cpp)
target_link_libraries(test_container_runtime PRIVATE system)
target_include_directories(test_container_runtime PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.container_runtime COMMAND test_container_runtime)

# Unit tests: Docker Provider (Phase 3.5)
add_executable(test_docker_provider test_docker_provider.cpp)
target_link_libraries(test_docker_provider PRIVATE system)
target_include_directories(test_docker_provider PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.docker_provider COMMAND test_docker_provider)

# Unit tests: Semantic Provider Interface (Phase 3.1)
add_executable(test_semantic_provider test_semantic_provider.cpp)
target_link_libraries(test_semantic_provider PRIVATE system)
target_include_directories(test_semantic_provider PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.semantic_provider COMMAND test_semantic_provider)

# Unit tests: Semantic IPC Protocol (Phase 3.4) - Basic serialization tests
add_executable(test_ipc_protocol test_ipc_protocol.cpp)
target_link_libraries(test_ipc_protocol PRIVATE system)
target_include_directories(test_ipc_protocol PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.ipc_protocol COMMAND test_ipc_protocol)

# Unit tests: Ansible Provider (Phase 3.7)
add_executable(test_ansible_provider test_ansible_provider.cpp)
target_link_libraries(test_ansible_provider PRIVATE system)
target_include_directories(test_ansible_provider PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.ansible_provider COMMAND test_ansible_provider)

# Unit tests: Pipeline Provider (Phase 3.10)
add_executable(test_pipeline_provider test_pipeline_provider.cpp)
target_link_libraries(test_pipeline_provider PRIVATE system)
target_include_directories(test_pipeline_provider PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.pipeline_provider COMMAND test_pipeline_provider)

# Unit tests: Package Metadata & Environment Reproducibility (Phase 3.11)
add_executable(test_packages test_packages.cpp)
target_link_libraries(test_packages PRIVATE system)
target_include_directories(test_packages PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.packages COMMAND test_packages)

# Unit tests: Testing Infrastructure Foundation (Phase 3.12)
add_executable(test_testing_infrastructure test_testing_infrastructure.cpp)
target_link_libraries(test_testing_infrastructure PRIVATE system)
target_include_directories(test_testing_infrastructure PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.testing_infra COMMAND test_testing_infrastructure)

# Unit tests: Provider Selection (Phase 3.13)
add_executable(test_provider_selection test_provider_selection.cpp)
target_link_libraries(test_provider_selection PRIVATE system)
target_include_directories(test_provider_selection PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.provider_selection COMMAND test_provider_selection)

# Unit tests: Engine Runtime (Phase 4.2)
add_executable(test_engine test_engine.cpp)
target_link_libraries(test_engine PRIVATE system)
target_include_directories(test_engine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)

# Unit tests: Runner Runtime (Phase 4.4)
add_executable(test_runner test_runner.cpp)
target_link_libraries(test_runner PRIVATE system)
target_include_directories(test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.runner COMMAND test_runner)

    # Unit tests: Controller Runtime (Phase 4.6)
    add_executable(test_controller test_controller.cpp)
    target_link_libraries(test_controller PRIVATE system)
    target_include_directories(test_controller PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
    add_test(NAME unit.controller COMMAND test_controller)

    # Unit tests: Dispatcher Runtime (Phase 4.5)
    add_executable(test_dispatcher test_dispatcher.cpp)
target_link_libraries(test_dispatcher PRIVATE system)
target_include_directories(test_dispatcher PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../include)
add_test(NAME unit.dispatcher COMMAND test_dispatcher)
