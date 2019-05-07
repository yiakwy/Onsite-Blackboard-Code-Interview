if (NOT __GFLAGS_INCLUDED)
set (__GFLAGS_INCLUDED TRUE)

find_package(GFlags)
echo("Before setting, GFLAGS_INCLUDE_DIRS: ${GFLAGS_INCLUDE_DIRS}")

if (APPLE)
set (GFLAGS_INCLUDE_DIRS /usr/local/include/gflags)
echo("After setting, GFLAGS_INCLUDE_DIRS is set to ${GFLAGS_INCLUDE_DIRS}")
elseif (CMAKE_OS_NAME EQUAL "Ubuntu")
# set (GFLAGS_INCLUDE_DIRS /usr/include/gflags)
endif()

include_directories (
	${GFLAGS_INCLUDE_DIRS}
	)

echo("GFLAGS_LIBRARY: ${GFLAGS_LIBRARIES}")
link_libraries(${GFLAGS_LIBRARIES})

endif()
