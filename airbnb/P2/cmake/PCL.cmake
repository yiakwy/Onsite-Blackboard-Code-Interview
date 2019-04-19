# Finds PCL library and targets

# we currently only use it in MacOS platform. Other system will be supported soon.
if ( "${CMAKE_OS_NAME}" STREQUAL "Ubuntu")
	set (PCL_INCLUDE_DIRS /usr/include/pcl-1.8)
endif()

if ( "${CMAKE_OS_NAME}" STREQUAL "OSX")
	set (PCL_INCLUDE_DIRS /usr/local/include/pcl-1.8)
endif()

find_package(PCL 1.8 REQUIRED)
find_package(Eigen3 REQUIRED)

include_directories (
	${PCL_INCLUDE_DIRS}
	${Eigen_INCLUDE_DIRS}
	)

# find_package(PCL 1.8 REQUIRED COMPONENTS io features visualization)
echo("PCL_INCLUDE_DIRS: ${PCL_INCLUDE_DIRS}, PCL_LIBRARY_DIRS: ${PCL_LIBRARY_DIRS}")
link_directories(${PCL_LIBRARY_DIRS})
add_definitions(${PCL_DEFINITIONS} 
	-DOPENNI_INCLUDE_DIRS=/usr/local/include/ni 
	-DOPENNI_INCLUDE_DIR=/usr/local/include/ni2 )

