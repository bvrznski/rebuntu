# src/system/path_safety — Path Safety Audit Library (Phase 6.59)
# Path safety validation utilities for filesystem operations

set(PATH_SAFETY_SOURCES
    path_safety.cpp
)

add_library(rebuntu_path_safety STATIC ${PATH_SAFETY_SOURCES})
target_include_directories(rebuntu_path_safety PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(rebuntu_path_safety PUBLIC 
    rebuntu_core
    stdc++fs
)

# Install rules
install(TARGETS rebuntu_path_safety
    EXPORT RebuntuTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)