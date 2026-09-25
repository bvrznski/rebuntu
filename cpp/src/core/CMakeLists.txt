# Rebuntu core contracts and types (Phase 0.0 + 0.13 runtime + 0.16 provider registry + 0.17 results + 0.18 config)
# ===========================================================================================================

add_library(rebuntu-core STATIC)

# Interface includes point to src where core contracts (SemanticStatus) are defined
# For cpp/Build builds, we use CMAKE_CURRENT_LIST_DIR instead of CMAKE_SOURCE_DIR
set(REBUNTU_ROOT ${CMAKE_CURRENT_LIST_DIR}/../../..)
target_include_directories(rebuntu-core PUBLIC 
    ${REBUNTU_ROOT}
)

# Include paths for semantic headers in cpp/include/
target_include_directories(rebuntu-core PUBLIC 
    ${REBUNTU_ROOT}/cpp/include
)

# Phase 3.1-3.2: Semantic provider and subprocess for BitNet CPU-only inference

# Provider registry implementation (Phase 0.16) - in interfaces directory
set(PROVIDER_REGISTRY_SRCS
    ${REBUNTU_ROOT}/src/interfaces/provider_registry.cpp
)
target_sources(rebuntu-core PRIVATE ${PROVIDER_REGISTRY_SRCS})

# Results model implementations (Phase 0.17)
set(RESULTS_MODEL_SRCS
    ${REBUNTU_ROOT}/src/runtime/core/results.hpp
)
target_sources(rebuntu-core PRIVATE ${RESULTS_MODEL_SRCS})

# Configuration & Specification Grammar (Phase 0.18)
set(CONFIG_GRAMMAR_SRCS
    ${REBUNTU_ROOT}/src/runtime/config.hpp
)
target_sources(rebuntu-core PRIVATE ${CONFIG_GRAMMAR_SRCS})

# Preferences Model (Phase 1.7) - header and implementation
set(PREFERENCES_MODEL_HDRS
    ${REBUNTU_ROOT}/src/runtime/preferences.hpp
)
set(PREFERENCES_IO_IMPL
    ${REBUNTU_ROOT}/src/runtime/preferences/io.hpp
    ${REBUNTU_ROOT}/src/runtime/preferences/io.cpp
)
target_sources(rebuntu-core PRIVATE ${PREFERENCES_MODEL_HDRS} ${PREFERENCES_IO_IMPL})

# Phase 1.11: Lifecycle operations are now in a separate library (rebuntu-lifecycle)
# The implementation is in src/system/lifecycle/

# Phase 3.1-3.2: Semantic provider and subprocess for BitNet CPU-only inference
set(SEMANTIC_PROVIDER_HDRS
    ${REBUNTU_ROOT}/cpp/include/system/semantic/provider.hpp
    ${REBUNTU_ROOT}/cpp/include/system/semantic/subprocess.hpp
)
set(SEMANTIC_PROVIDER_SRCS
    ${REBUNTU_ROOT}/cpp/src/semantic/subprocess.cpp
    ${REBUNTU_ROOT}/cpp/src/semantic/bitnet_provider.cpp
)
target_sources(rebuntu-core PRIVATE ${SEMANTIC_PROVIDER_HDRS} ${SEMANTIC_PROVIDER_SRCS})

# Phase 4.2: Engine Facade for typed work submission and runtime coordination
set(ENGINE_HDRS
    ${REBUNTU_ROOT}/src/runtime/engine.hpp
)
set(ENGINE_IMPL
    ${REBUNTU_ROOT}/src/runtime/engine.cpp
)

# Phase 4.3: Executor - unified interface for subprocess, systemd, dbus execution mechanisms
# Phase 4.4: Runner - execution state machine and retry management

set(RUNNER_HDRS
    ${REBUNTU_ROOT}/src/runtime/runner.hpp
)

target_sources(rebuntu-core PRIVATE ${RUNNER_HDRS})

# Phase 4.3: Executor - unified interface for subprocess, systemd, dbus execution mechanisms
# The executor implementation is in src/system/runtime/
set(EXECUTOR_HDRS
    ${REBUNTU_ROOT}/src/system/runtime/executor.hpp
)
set(EXECUTOR_IMPL
    ${REBUNTU_ROOT}/src/system/runtime/executor.cpp
)

# Phase 4.5: Dispatcher - execution routing mechanism
# The dispatcher implementation is in src/system/runtime/
set(DISPATCHER_HDRS
    ${REBUNTU_ROOT}/src/system/runtime/dispatcher.hpp
)
set(DISPATCHER_IMPL
    ${REBUNTU_ROOT}/src/system/runtime/dispatcher.cpp
)

target_sources(rebuntu-core PRIVATE 
    ${ENGINE_HDRS} ${ENGINE_IMPL}
    ${EXECUTOR_HDRS} ${EXECUTOR_IMPL}
    ${DISPATCHER_HDRS} ${DISPATCHER_IMPL}
)
