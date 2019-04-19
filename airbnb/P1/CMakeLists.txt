cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(airbnb C CXX)

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

if ( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
    execute_process( COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json )
endif()

include(cmake/Utils.cmake)
include_directories(python/lib)
include_directories(cpp/src/modules/)

add_subdirectory(tests/gtest)
add_subdirectory(cpp)
add_subdirectory(python)
