# Rebuntu core contracts and types (Phase 0.0 + 0.13 runtime)
# ===========================================================

add_library(rebuntu-core INTERFACE)

target_include_directories(rebuntu-core INTERFACE 
    ${CMAKE_CURRENT_LIST_DIR}/../../../include
    ${CMAKE_CURRENT_LIST_DIR}/../../src
)
