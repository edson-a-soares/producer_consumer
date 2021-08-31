SET(TEST_TYPE "Integration")
SET(TEST_UNIT ${COMPONENT_NAME}${TEST_TYPE}Tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

if(NOT GTEST_FOUND)
    message(WARNING "Failed to find the GTest libraries.")
endif()

# It makes fake implementations available to the testing code
set(TESTS_INCLUDE_FILES ${CMAKE_HOME_DIRECTORY}/${COMPONENT_NAME}/test/${TEST_TYPE}/)

file(GLOB_RECURSE TEST_SOURCE_FILES ${CMAKE_HOME_DIRECTORY}/${COMPONENT_NAME}/test/${TEST_TYPE}/*.cpp)

# It makes tests constants available.
# See.: /cmake/TestsConstants.cmake
include(TestsConstants)

add_executable(${TEST_UNIT} ${TEST_SOURCE_FILES})
target_link_libraries(${TEST_UNIT} gtest gtest_main pthread ${COMPONENT_BINARY_NAME})
target_include_directories(${TEST_UNIT} PUBLIC ${TESTS_INCLUDE_FILES})

add_test(NAME ${TEST_UNIT} COMMAND ${TEST_UNIT})
