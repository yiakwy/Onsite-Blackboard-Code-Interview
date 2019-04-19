file(GLOB_RECURSE SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "*.cpp")

echo(" DIR:${CMAKE_SOURCE_DIR} SOURCES: ${SOURCES}")

# add shared libraries
add_library(common SHARED
	"log/logging.hpp"
	"log/logging.cpp"
    "random/distribution.hpp"
    "random/distribution.cpp"
    "lambda/lambda.hpp"
    "lambda/lambda.cpp"
	"api.h"
	)

# add links
set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX PRIVATE ${LIB_LINKER_FLAGS})

echo("Dependencies: ${GFLAGS_LIBRARIES}, ${GLOG_LIBRARIES}")

# target_link_libraries(common ${GFLAGS_LIBRARIES} ${GLOG_LIBRARIES})
add_library(libglog SHARED IMPORTED)
set_target_properties(libglog PROPERTIES
	IMPORTED_LOCATION "${GLOG_LIBRARIES}"
	INTERFACE_INCLUDE_DIRECTORIES "${GLOG_INCLUDE_DIRS}")
add_library(libgflags SHARED IMPORTED)
set_target_properties(libgflags PROPERTIES
	IMPORTED_LOCATION "${GFLAGS_LIBRARIES}"
	INTERFACE_INCLUDE_DIRECTORIES "${GFLAGS_INCLUDE_DIRS}")

target_link_libraries(common libglog)
