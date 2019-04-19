file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

add_executable(diff_tree_cli
    diff_tree.hpp
    diff_tree.cpp)

set_target_properties(diff_tree_cli PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(diff_tree_cli PRIVATE "./")
target_link_libraries(diff_tree_cli graph common)
