cmake_minimum_required(VERSION 3.7)

project(ProducerConsumer)

set(CMAKE_C_COMPILER /usr/bin/gcc)
set(CMAKE_CXX_COMPILER /usr/bin/g++)

# It sets default to Release build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")
else()
    message(STATUS "CMake Build Type: ${CMAKE_BUILD_TYPE}")
endif()

# It defines the common flags to all compilation builds no matter the mode
# https://caiorss.github.io/C-Cpp-Notes/compiler-flags-options.html
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wextra -Wall -Wpedantic -fpic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} \
        -g -fprofile-arcs -ftest-coverage -rdynamic \
        -g -O0 -Wshadow -Wunused-parameter -Wunused-variable -Wdelete-non-virtual-dtor -Wfatal-errors \
        -Woverloaded-virtual -Wunreachable-code -Wno-unused -Wundef -Wl,--no-undefined -Wl,--no-allow-shlib-undefined")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -w -Wl,--discard-all")

#-----------------------------------------------------------------------------
# It defines Cmake supporting scripts path available.
#-----------------------------------------------------------------------------
set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# It removes the prefix "lib" from the .so and .a files
set(CMAKE_SHARED_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_PREFIX "")

# Application's modules prefix
set(APPLICATION_MODULE_PREFIX ProducerConsumer)

#-----------------------------------------------------------------------------
# Put the libaries and binaries built into directories at the
# top of the build tree rather than in hard-to-find leaf directories.
# This simplifies manual testing and the use of the build tree.
#-----------------------------------------------------------------------------
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

#-----------------------------------------------------------------------------
# Application optional features
#-----------------------------------------------------------------------------
set(ENABLE_TESTS
        "Set to OFF|ON (default: ON) to control build of EPP API tests" ON)

#-----------------------------------------------------------------------------
# Add application modules
#-----------------------------------------------------------------------------
add_subdirectory(Foundation)
add_subdirectory(ConsumerDaemon)
add_subdirectory(Consumer)
add_subdirectory(Producer)

#-----------------------------------------------------------------------------
# It configures documentation
#-----------------------------------------------------------------------------
include(DocumentationSettings)
