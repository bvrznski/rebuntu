# Rebuntu core contracts and types (Phase 0.0 + 0.13 runtime + 0.16 provider registry + 0.17 results + 0.18 config)
# ===========================================================================================================

add_library(rebuntu-core STATIC)

target_include_directories(rebuntu-core PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/../..
    ${CMAKE_CURRENT_LIST_DIR}/../../src
)

# Add system header path explicitly for lifecycle.cpp includes
target_include_directories(rebuntu-core PRIVATE ${CMAKE_CURRENT_LIST_DIR}/../../include)

# Provider registry implementation (Phase 0.16) - in interfaces directory
set(PROVIDER_REGISTRY_SRCS
    ${CMAKE_SOURCE_DIR}/../src/interfaces/provider_registry.cpp
)
target_sources(rebuntu-core PRIVATE ${PROVIDER_REGISTRY_SRCS})

# Results model implementations (Phase 0.17)
set(RESULTS_MODEL_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/core/results.hpp
)
target_sources(rebuntu-core PRIVATE ${RESULTS_MODEL_SRCS})

# Configuration & Specification Grammar (Phase 0.18)
set(CONFIG_GRAMMAR_SRCS
    ${CMAKE_SOURCE_DIR}/../src/runtime/config.hpp
)
target_sources(rebuntu-core PRIVATE ${CONFIG_GRAMMAR_SRCS})

# Preferences Model (Phase 1.7) - header and implementation
set(PREFERENCES_MODEL_HDRS
    ${CMAKE_SOURCE_DIR}/../src/runtime/preferences.hpp
)
set(PREFERENCES_IO_IMPL
    ${CMAKE_SOURCE_DIR}/../src/runtime/preferences/io.hpp
    ${CMAKE_SOURCE_DIR}/../src/runtime/preferences/io.cpp
)
target_sources(rebuntu-core PRIVATE ${PREFERENCES_MODEL_HDRS} ${PREFERENCES_IO_IMPL})

# Phase 1.11: Lifecycle operations are now in a separate library (rebuntu-lifecycle)
# The implementation is in src/system/lifecycle/

# Phase 3.1-3.2: Semantic provider and subprocess for BitNet CPU-only inference
# Paths relative to cpp/src/core:
# - cpp/include/system/semantic/provider.hpp (two dirs up, then include)
# - cpp/include/system/semantic/subprocess.hpp
# - cpp/src/semantic/subprocess.cpp
# - cpp/src/semantic/bitnet_provider.cpp
set(SEMANTIC_PROVIDER_HDRS
    ${CMAKE_CURRENT_LIST_DIR}/../../include/system/semantic/provider.hpp
    ${CMAKE_CURRENT_LIST_DIR}/../../include/system/semantic/subprocess.hpp
)
set(SEMANTIC_PROVIDER_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/../semantic/subprocess.cpp
    ${CMAKE_CURRENT_LIST_DIR}/../semantic/bitnet_provider.cpp
)
target_sources(rebuntu-core PRIVATE ${SEMANTIC_PROVIDER_HDRS} ${SEMANTIC_PROVIDER_SRCS})
