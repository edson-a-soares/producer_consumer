# Check if Doxygen is installed
find_package(Doxygen)
if(NOT DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen must be installed to build the documentation.")
endif()

# Set input and output files
# See.: https://www.doxygen.nl/manual/config.html
set(DOXYGEN_IN ${CMAKE_HOME_DIRECTORY}/cmake/Doxygen.in)
set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxygen)

# Request to configure the file
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

message("Doxygen build started")
add_custom_target(
    docs ALL
    COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${CMAKE_HOME_DIRECTORY}/docs
    COMMENT "Generating API documentation with Doxygen"
    VERBATIM
)
