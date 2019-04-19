file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})

find_package(GLUT REQUIRED)
include_directories(${GLUT_INCLUDE_DIR})

add_library(glviewer SHARED
    "IMPROVED_MESH.h"
    "IMPROVED_MESH.cpp"
    "viewer.hpp"
    "viewer.cpp"
    "MeshViewer.hpp"
    "MeshViewer.cpp"
    )
set_target_properties(glviewer PROPERTIES LINKER_LANGUAGE CXX PRIVATE ${LIB_LINKER_FLAGS})
# see https://cmake.org/pipermail/cmake/2012-August/051607.html
target_link_libraries(glviewer ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
