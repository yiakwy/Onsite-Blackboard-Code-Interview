add_executable(test_lucky_draw_suites
    "testMain.cpp"
    "test_lucky_draw_benchmark.cpp"
    )

echo ("GTEST_LIBRARIES: ${GTEST_LIBRARIES}")
target_link_libraries(test_lucky_draw_suites
    lucky_draw
    ${GTEST_LIBRARIES}
    )

# this will go away once we get rid of catkin
add_test(test_suites
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/test_lucky_draw_suites)
