file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

if (APPLE)
    # https://gitlab.kitware.com/cmake/community/wikis/doc/cmake/platform_dependent_issues/HowToUseExistingOSXFrameworks
    find_library(COCOA_LIBRARY Cocoa)
endif()

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
    "Camera.hpp"
    "Camera.cpp"
    "FirstPersonControls.hpp"
    "FirstPersonControls.cpp"
    "Renderer.hpp"
    "Renderer.cpp"
    "primitives/Axis.h"
    "primitives/Axis.cpp"
    )

echo ("OPENGL_LIBRARIES: ${OPENGL_LIBRARIES}")
echo ("GLUT_LIBRARIES: ${GLUT_LIBRARIES}")
echo ("COCOA_LIBRARY: ${COCOA_LIBRARY}")

set_target_properties(glviewer PROPERTIES LINKER_LANGUAGE CXX PRIVATE ${LIB_LINKER_FLAGS})
# see https://cmake.org/pipermail/cmake/2012-August/051607.html

add_library(libgflags SHARED IMPORTED)
set_target_properties(libgflags PROPERTIES
IMPORTED_LOCATION "${GFLAGS_LIBRARIES}"
INTERFACE_INCLUDE_DIRECTORIES "${GFLAGS_INCLUDE_DIRS}")

echo ("GFLAGS_LIBRARIES: ${GFLAGS_LIBRARIES}")

target_link_libraries(glviewer common libgflags ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${COCOA_LIBRARY})
