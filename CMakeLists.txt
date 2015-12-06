cmake_minimum_required(VERSION 3.3)
project(CpperoMQLearnin)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(THREADS_PREFER_PTHREAD_FLAG ON)

# These are things that I got from a CMake File made by jship on github
# https://github.com/jship/CpperoMQ-examples/blob/master/CMakeLists.txt

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)

SET(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR})

LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake/Modules)

INCLUDE(InstallRequiredSystemLibraries)

find_package(Sodium REQUIRED)
include_directories(${SODIUM_INCLUDE_DIR})

find_package(ZeroMQ REQUIRED)
include_directories(${ZEROMQ_INCLUDE_DIR})

find_package(ZeroMQPP REQUIRED)
include_directories(${ZZeroMQPP_INCLUDE_DIR})

find_package(CpperoMQ REQUIRED)
include_directories(${CPPEROMQ_INCLUDE_DIR})

find_package(Threads)

include_directories(~/Projects/CpperoMQ/include/)

INCLUDE(FindPkgConfig)
pkg_check_modules(MODBUS REQUIRED libmodbus)
include_directories(${MODBUS_INCLUDE_DIRS})
link_directories(${MODBUS_LIBRARY_DIRS})


set(SOURCE_FILES main.cpp modbusServer.cpp modbusServer.h)
add_executable(CpperoMQLearnin ${SOURCE_FILES} modbusServer.cpp modbusServer.h)
target_link_libraries(CpperoMQLearnin ${ZEROMQ_LIBRARIES} ${ZeroMQPP_LIBRARY} Threads::Threads ${MODBUS_LIBRARIES})
