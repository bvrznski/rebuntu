# rebuntu::setup - Setup & Configuration machinery (Phase 1.8)
# ===============================================================

add_library(rebuntu-setup STATIC
    contracts.hpp
    profile.cpp
    profile.hpp
    setup.cpp
)

target_include_directories(rebuntu-setup PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/../src
)

target_link_libraries(rebuntu-setup PUBLIC rebuntu-core)