cmake_minimum_required(VERSION 3.3)
project(CpperoMQLearnin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


# These are things that I got from a CMake File made by jship on github
# https://github.com/jship/CpperoMQ-examples/blob/master/CMakeLists.txt

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

SET(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/Modules)

INCLUDE(InstallRequiredSystemLibraries)

find_package(SODIUM REQUIRED)
include_directories(${SODIUM_INCLUDE_DIR})

find_package(ZEROMQ REQUIRED)
include_directories(${ZEROMQ_INCLUDE_DIR})

#find_package(CPPEROMQ REQUIRED)
#include_directories(${CPPEROMQ_INCLUDE_DIR})

include_directories(~/Projects/CpperoMQ/include/)


set(SOURCE_FILES main.cpp)
add_executable(CpperoMQLearnin ${SOURCE_FILES})
target_link_libraries(CpperoMQLearnin ${ZEROMQ_LIBRARIES})
