# src/system/environment — Host Environment Discovery (Phase 1.9, 2.1)
# User identity module for C++20 native Rebuntu runtime

set(ENVIRONMENT_SOURCES
    user_identity.cpp
    environment_discovery.cpp
    temp_files.cpp
    locks.cpp
    ipc.cpp
)

add_library(rebuntu_environment STATIC ${ENVIRONMENT_SOURCES})
target_include_directories(rebuntu_environment PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(rebuntu_environment PUBLIC 
    rebuntu_core
    stdc++fs
)

# Install rules
install(TARGETS rebuntu_environment
    EXPORT RebuntuTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)

# Add environment tests if enabled
option(REBUNTU_BUILD_TESTS "Build Rebuntu tests" ON)
if(REBUNTU_BUILD_TESTS)
    add_subdirectory(tests)
endif()