# Test configuration for Rebuntu automation module
add_executable(automation_test automation_test.cpp)
target_link_libraries(automation_test rebuntu-core)
target_include_directories(automation_test PRIVATE ${CMAKE_SOURCE_DIR}/src)

# Add tests to CTest
add_test(NAME automation_test COMMAND automation_test)