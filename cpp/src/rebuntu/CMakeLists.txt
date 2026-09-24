# Rebuntu CLI entry point (Phase 0.13)
# =======================================

add_executable(rebuntu main.cpp)

target_link_libraries(rebuntu rebuntu-core)

target_include_directories(rebuntu PRIVATE ${CMAKE_SOURCE_DIR}/../src)

# Add subprocess_executor implementation
set(SUBPROCESS_EXECUTOR_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/subprocess_executor.hpp
    ${CMAKE_SOURCE_DIR}/../src/runtime/subprocess_executor.cpp
)
target_sources(rebuntu PRIVATE ${SUBPROCESS_EXECUTOR_SRCS})

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
