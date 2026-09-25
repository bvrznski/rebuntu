# Rebuntu CLI entry point (Phase 0.13)
# =======================================

add_executable(rebuntu main.cpp)

target_link_libraries(rebuntu rebuntu-core)

# Add include directories for semantic subprocess headers (src before include to resolve Outcome correctly)
target_include_directories(rebuntu PRIVATE 
    ${CMAKE_SOURCE_DIR}/../src
    ${CMAKE_CURRENT_LIST_DIR}/../../include
)

# Add subprocess_executor implementation (original minimal proof for Phase 0.13)
set(SUBPROCESS_EXECUTOR_MINIMAL_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/subprocess_executor.hpp
    ${CMAKE_SOURCE_DIR}/../src/runtime/subprocess_executor.cpp
)
target_sources(rebuntu PRIVATE ${SUBPROCESS_EXECUTOR_MINIMAL_SRCS})

# Add semantic subprocess executor for bitnet.cpp (timeout, I/O capture, CPU-only policy)
set(SEMANTIC_SUBPROCESS_HDRS
    ${CMAKE_CURRENT_LIST_DIR}/../../include/system/semantic/subprocess.hpp
)
set(SEMANTIC_SUBPROCESS_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/../../src/semantic/subprocess.cpp
)
target_sources(rebuntu PRIVATE ${SEMANTIC_SUBPROCESS_HDRS} ${SEMANTIC_SUBPROCESS_SRCS})

# Add bitnet provider implementation (Phase 3.1-3.2)
set(BITNET_PROVIDER_HDRS
    ${CMAKE_CURRENT_LIST_DIR}/../../include/system/semantic/provider.hpp
)
set(BITNET_PROVIDER_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/../../src/semantic/bitnet_provider.cpp
)
target_sources(rebuntu PRIVATE ${BITNET_PROVIDER_HDRS} ${BITNET_PROVIDER_SRCS})

# Add semantic service implementation (Phase 3.3)
set(SEMANTIC_SERVICE_HDRS
    ${CMAKE_CURRENT_LIST_DIR}/../../include/system/semantic/service.hpp
)
set(SEMANTIC_SERVICE_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/../../src/semantic/service.cpp
)
target_sources(rebuntu PRIVATE ${SEMANTIC_SERVICE_HDRS} ${SEMANTIC_SERVICE_SRCS})

# Add semantic IPC implementation (Phase 3.4) - use cpp/src/semantic which has complete implementations
set(SEMANTIC_IPC_HDRS
    ${CMAKE_CURRENT_LIST_DIR}/../../include/system/semantic/ipc.hpp
)
set(SEMANTIC_IPC_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/../../src/semantic/ipc_transport.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../../src/semantic/ipc_client.cpp
)
target_sources(rebuntu PRIVATE ${SEMANTIC_IPC_HDRS} ${SEMANTIC_IPC_SRCS})

# Add Docker provider implementation (Phase 3.5)
set(DOCKER_PROVIDER_HDRS
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/docker.hpp
)
set(DOCKER_PROVIDER_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/docker_provider.cpp
)
target_sources(rebuntu PRIVATE ${DOCKER_PROVIDER_HDRS} ${DOCKER_PROVIDER_SRCS})

# Add Container runtime contracts implementation (Phase 3.6)
set(CONTAINER_RUNTIME_HDRS
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/container.hpp
)
set(CONTAINER_RUNTIME_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/container_runtime.cpp
)
target_sources(rebuntu PRIVATE ${CONTAINER_RUNTIME_HDRS} ${CONTAINER_RUNTIME_SRCS})

# Add Ansible provider implementation (Phase 3.7)
set(ANSIBLE_PROVIDER_HDRS
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/ansible.hpp
)
set(ANSIBLE_PROVIDER_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/infrastructure/ansible_provider.cpp
)
target_sources(rebuntu PRIVATE ${ANSIBLE_PROVIDER_HDRS} ${ANSIBLE_PROVIDER_SRCS})

# Add systemd_executor implementation (minimal proof for Phase 0.13)
set(SYSTEMD_EXECUTOR_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/systemd_executor.hpp
    ${CMAKE_SOURCE_DIR}/../src/runtime/systemd_executor.cpp
)
target_sources(rebuntu PRIVATE ${SYSTEMD_EXECUTOR_SRCS})

# Add dbus_executor implementation (minimal proof for Phase 0.13)
set(DBUS_EXECUTOR_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/dbus_executor.hpp
    ${CMAKE_SOURCE_DIR}/../src/runtime/dbus_executor.cpp
)
target_sources(rebuntu PRIVATE ${DBUS_EXECUTOR_SRCS})

# Add timeout_enforcement implementation with native Linux timerfd
set(TIMEOUT_ENFORCEMENT_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/timeout_enforcement.hpp
    ${CMAKE_SOURCE_DIR}/../src/runtime/timeout_enforcement.cpp
)
target_sources(rebuntu PRIVATE ${TIMEOUT_ENFORCEMENT_SRCS})

# Add Phase 2.7 scope module (System/User/Session scope resolution)
set(SCOPE_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/environment/scope.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/environment/scope.cpp
)
target_sources(rebuntu PRIVATE ${SCOPE_SRCS})

# Add Phase 2.8 sessions module (Sessions & Runtime Identity)
set(SESSIONS_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/environment/sessions.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/environment/sessions.cpp
)
target_sources(rebuntu PRIVATE ${SESSIONS_SRCS})

# Add Phase 2.12 temporary files module (Secure Temp Files)
set(TEMP_FILES_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/environment/temp_files.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/environment/temp_files.cpp
)
target_sources(rebuntu PRIVATE ${TEMP_FILES_SRCS})

# Add Phase 2.12 locks module (Locking Primitives)
set(LOCKS_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/environment/locks.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/environment/locks.cpp
)
target_sources(rebuntu PRIVATE ${LOCKS_SRCS})

# Add Phase 2.12 IPC module (Inter-Process Communication)
set(IPC_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/environment/ipc.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/environment/ipc.cpp
)
target_sources(rebuntu PRIVATE ${IPC_SRCS})

# Add Phase 1 installation architecture (Phase 1.0-1.2)
set(INSTALL_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/install/contracts.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/install/forms.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/install/install.cpp
    ${CMAKE_SOURCE_DIR}/../src/system/install/install_planning.cpp
    ${CMAKE_SOURCE_DIR}/../src/system/install/planning.hpp
)
target_sources(rebuntu PRIVATE ${INSTALL_SRCS})

# Add Phase 1 setup & configuration machinery (Phase 1.8)
set(SETUP_SRCS
    ${CMAKE_SOURCE_DIR}/../src/system/setup/contracts.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/setup/profile.cpp
    ${CMAKE_SOURCE_DIR}/../src/system/setup/profile.hpp
    ${CMAKE_SOURCE_DIR}/../src/system/setup/setup.cpp
)
target_sources(rebuntu PRIVATE ${SETUP_SRCS})
