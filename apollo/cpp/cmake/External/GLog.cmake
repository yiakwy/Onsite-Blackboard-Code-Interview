include ("cmake/External/GFlags.cmake")

if (NOT __GLOG_INCLUDED)
set (__GLOG_INCLUDED TRUE)

find_package(Glog)
echo("Before setting, GLOG_INCUDE_DIRS: ${GLOG_INCLUDE_DIRS}")

if (APPLE)
set (GLOG_INCLUDE_DIRS /usr/local/include/glog)
echo("After setting, GLOG_INCUDE_DIRS is set to ${GLOG_INCLUDE_DIRS}")
elseif (CMAKE_OS_NAME EQUAL "Ubuntu")
# set (GLOG_INCLUDE_DIRS /usr/include/glog)
endif()

include_directories(
	${GLOG_INCLUDE_DIRS}
	)

echo("GLOG_LIBRARIES: ${GLOG_LIBRARIES}")
link_libraries(${GLOG_LIBRARIES})

endif()
