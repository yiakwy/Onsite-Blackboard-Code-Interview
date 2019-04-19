file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

add_library(graph SHARED
    graph.h
    graph.cc   
)

set_target_properties(graph PROPERTIES LINKER_LANGUAGE CXX PRIVATE ${LIB_LINKER_FLAGS})
target_link_libraries(graph common)
