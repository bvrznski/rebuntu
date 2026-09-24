# Rebuntu core contracts and types (Phase 0.0 + 0.13 runtime + 0.16 provider registry + 0.17 results + 0.18 config)
# ===========================================================================================================

add_library(rebuntu-core STATIC)

target_include_directories(rebuntu-core PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/../../../include
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

# Lifecycle Operations Implementation (Phase 1.11)
set(LIFECYCLE_SRCS
    ${CMAKE_CURRENT_LIST_DIR}/lifecycle.cpp
)
target_sources(rebuntu-core PRIVATE ${LIFECYCLE_SRCS})
