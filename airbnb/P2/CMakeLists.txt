cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(airbnb_P2 C CXX)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (USE_DOCKER OFF)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

# used by xcode
if ( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
    execute_process( COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
        ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json )
endif()

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (UNIX OR APPLE)
    set ( CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -fPIC -Wall")
    set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    set (LIB_LINKER_FLAGS "-dynamiclib")
    set (CMAKE_OS_NAME "MacOS" CACHE STRING "Operating system name" FORCE)
endif()

## Other OS Begin

if (USE_LIBSTDCPP)
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libstdc++")
  echo ("Using libstdc++ (controled by USE_LIBSTDCPP option)")
endif()

find_file (UBUNTU_EXTRA legal issue PATHS /etc)
if (UBUNTU_EXTRA)
  file (STRINGS ${UBUNTU_EXTRA} UBUNTU_FOUND REGEX Ubuntu)
  set (LIB_LINKER_FLAGS "-so")
  set (CMAKE_OS_NAME "Ubuntu" CACHE STRING "Operating system name" FORCE)
  echo ("Ubuntu")
endif(UBUNTU_EXTRA)

if (EXISTS "/etc/redhat-release")
  set (LIB_LINKER_FLAGS "-so")
  set (CMAKE_OS_NAME "CentOS" CACHE STRING "Operating system name" FORCE)
  echo ("CentOS")
endif()

## Other OS End

include(cmake/Utils.cmake)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake/Modules)

include(cmake/Relies.cmake)

set (SRCS_ROOT "${PROJECT_SOURCE_DIR}/src/modules")
set ( LOG_DIR "${PROJECT_SOURCE_DIR}/log")

configure_file(config/cmake_config.h.in
    ${PROJECT_SOURCE_DIR}/config/cmake_config.h)

include_directories(config)
include_directories(${SRCS_ROOT})

add_subdirectory(${SRCS_ROOT}/graph)
add_subdirectory(${SRCS_ROOT}/solutions)
add_subdirectory(${SRCS_ROOT}/utils)

if (TEST)
   add_subdirectory(tests/gtest)
endif()
