include(GoogleTest)
enable_testing()

add_executable(test_sort test_sort.cpp)
target_link_libraries(test_sort googletest googletest_main pthread)
add_test(test_sort test_sort)

add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND}
        DEPENDS test_sort)