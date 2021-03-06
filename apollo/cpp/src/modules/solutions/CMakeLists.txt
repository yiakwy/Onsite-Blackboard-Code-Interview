file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

add_executable(find_path_cli
    find_path.hpp
    find_path.cpp)

set_target_properties(find_path_cli PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(find_path_cli PRIVATE "./")
target_link_libraries(find_path_cli graph common)

add_executable(linear_scanning_cli
    "linear_scanning_cli.cpp"
    "algorithms/linear_scanning.hpp"
    "algorithms/linear_scanning.cpp"
    )

set_target_properties(linear_scanning_cli PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(linear_scanning_cli PRIVATE "./")
target_link_libraries(linear_scanning_cli common graph glviewer)

add_executable(find_sum_cli
    "algorithms/segment_tree.hpp"
    "algorithms/segment_tree.cpp"
    )
set_target_properties(find_sum_cli PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(find_sum_cli PRIVATE "./")
target_link_libraries(find_sum_cli graph common)

add_executable(find_circles_cli
    "find_circles.cpp"
    )
set_target_properties(find_circles_cli PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(find_circles_cli PRIVATE "./")
target_link_libraries(find_circles_cli graph)

add_executable(quick_sort
    "quick_sort.cpp"
)
set_target_properties(quick_sort PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(quick_sort PRIVATE "./")
target_link_libraries(quick_sort)

add_executable(kway_sort
    "kway-sorting.cpp"
)
set_target_properties(kway_sort PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(kway_sort PRIVATE "./")
target_link_libraries(kway_sort)

add_executable(fast_four_sum
    "FastFourSum.hpp"
    "FastFourSum.cpp"
)
target_include_directories(fast_four_sum PRIVATE "./")
target_link_libraries(fast_four_sum)

add_executable(twenty_four_game
    "twenty_four.cpp"
)

add_executable(the_maze
    "the_maze.cpp"
)

add_executable(unique_path
    "unique_path.cpp"
)

add_executable(floyd_path_tp
    "floyd_path_tp.cpp"
)

add_executable(string_mtch
    "string_mtch.cpp"
)

add_library(lucky_draw
    "lucky_draw_stone_tech.hpp"
    "lucky_draw_stone_tech.cpp"
)
target_link_libraries(
    lucky_draw
)
set_target_properties(lucky_draw PROPERTIES LINKER_LANGUAGE CXX PRIVATE ${LIB_LINKER_FLAGS})

add_executable(integral_map
    "integral_map.cpp"
)

add_executable(quick_linked_sort
    "quick_linked_sort.cpp"
)
