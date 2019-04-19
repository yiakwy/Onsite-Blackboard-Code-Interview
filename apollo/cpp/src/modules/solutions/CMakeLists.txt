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
target_link_libraries(linear_scanning_cli graph common)
