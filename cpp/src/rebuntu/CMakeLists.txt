# Rebuntu CLI entry point (Phase 0.0)
# ====================================

add_executable(rebuntu main.cpp)

target_include_directories(rebuntu PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(rebuntu rebuntu-core)

install(TARGETS rebuntu RUNTIME DESTINATION bin)