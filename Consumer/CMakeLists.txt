#-----------------------------------------------------------------------------
# It defines basic component information.
#-----------------------------------------------------------------------------
set(COMPONENT_NAME "Consumer")

# Component's binary name.
set(COMPONENT_BINARY_NAME ${APPLICATION_MODULE_PREFIX}_${COMPONENT_NAME})

#-----------------------------------------------------------------------------
# Component source code handling
#-----------------------------------------------------------------------------
set(PROJECT_INCLUDE_DIR ${CMAKE_HOME_DIRECTORY}/${COMPONENT_NAME}/include)
set(PROJECT_SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/${COMPONENT_NAME}/src)

file(GLOB_RECURSE CONSUMER_SOURCE_FILES ${PROJECT_SOURCE_DIR}/*.cpp)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")

add_library(${COMPONENT_BINARY_NAME} SHARED ${CONSUMER_SOURCE_FILES})
target_include_directories(${COMPONENT_BINARY_NAME} PUBLIC ${PROJECT_INCLUDE_DIR})

#-----------------------------------------------------------------------------
# Handle application dependencies
#-----------------------------------------------------------------------------
set(DEPENDENCIES_LIBS ${DEPENDENCIES_LIBS} "${APPLICATION_MODULE_PREFIX}_Foundation")

# Poco library setup
find_library(POCO_FOUNDATION PocoFoundation)
find_library(POCO_UTIL PocoUtil)
find_library(POCO_JSON PocoJSON)
find_library(POCO_NET PocoNet)

include_directories(${Poco_INCLUDE_DIRS})
set(DEPENDENCIES_LIBS ${DEPENDENCIES_LIBS} ${POCO_FOUNDATION} ${POCO_UTIL} ${POCO_XML} ${POCO_JSON} ${POCO_NET})

# Threads
find_package(Threads REQUIRED)

# It links the dependencies to the application
target_link_libraries(${COMPONENT_BINARY_NAME} ${DEPENDENCIES_LIBS} -lpthread -lrt)

if (ENABLE_TESTS)
    add_subdirectory(test)
    message(STATUS "Building ${COMPONENT_NAME} with tests")

elseif ()
    message(STATUS "Building ${COMPONENT_NAME} without tests")

endif ()

set(CONSUMER_CLI_EXECUTABLE_NAME ConsumerManagement)
add_executable(${CONSUMER_CLI_EXECUTABLE_NAME} ${CONSUMER_SOURCE_FILES})
target_link_libraries(${CONSUMER_CLI_EXECUTABLE_NAME} ${COMPONENT_BINARY_NAME})
