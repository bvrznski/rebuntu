# rebuntu::install - Installation architecture (Phase 1.0-1.2)
# =============================================================

add_library(rebuntu-install STATIC
    contracts.hpp
    discovery.hpp
    discovery.cpp
    forms.hpp
    install.cpp
    install_planning.cpp
    planning.hpp
)

target_include_directories(rebuntu-install PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_SOURCE_DIR}/../src
)

target_link_libraries(rebuntu-install PUBLIC rebuntu-core)
