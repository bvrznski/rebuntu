# src/system/environment — Host Environment Discovery (Phase 1.9, 2.1)
# User identity module for C++20 native Rebuntu runtime

set(SOURCES
    user_identity.cpp
)

add_library(rebuntu_environment_user_identity STATIC ${SOURCES})
target_include_directories(rebuntu_environment_user_identity PUBLIC 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)
target_link_libraries(rebuntu_environment_user_identity PUBLIC 
    rebuntu_core
    stdc++fs
)

# Install rules
install(TARGETS rebuntu_environment_user_identity
    EXPORT RebuntuTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
)