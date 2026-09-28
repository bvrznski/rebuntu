# src/system/path_safety/tests — Path Safety Unit Tests

add_executable(rebuntu-path-safety-test
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../../tests/unit/path_safety_test.cpp
)

target_include_directories(rebuntu-path-safety-test PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(rebuntu-path-safety-test 
    rebuntu_path_safety
    rebuntu_core
    GTest::gtest_main
    stdc++fs
)

# Enable test discovery if CTest is enabled
if(REBUNTU_BUILD_TESTS)
    add_test(
        NAME path_safety
        COMMAND rebuntu-path-safety-test
    )
endif()