# Test configuration for Rebuntu runtime module (Phase 0.13)
add_executable(runtime_runner_test runtime_runner_test.cpp)
target_link_libraries(runtime_runner_test rebuntu-core)
target_include_directories(runtime_runner_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

add_executable(automation_test automation_test.cpp)
target_link_libraries(automation_test rebuntu-core)
target_include_directories(automation_test PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}
)

# Add tests to CTest
add_test(NAME runtime_runner_test COMMAND runtime_runner_test)
add_test(NAME automation_test COMMAND automation_test)
