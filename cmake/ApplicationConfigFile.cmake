#-----------------------------------------------------------------------------
# This Cmake script reads the constants available in the application.txt file
# and makes them available in the build environment as CMake constants.
#-----------------------------------------------------------------------------
set(APPLICATION_FILE "${CMAKE_HOME_DIRECTORY}/data/settings/application.txt")
set(ALLOWED_CONSTANTS installation_directory_name)

if(NOT EXISTS "${APPLICATION_FILE}")
    message(FATAL_ERROR "${APPLICATION_FILE} is missing.")
endif()

# I reads the configuration file and puts the available constants in a variable
file(STRINGS ${APPLICATION_FILE} APPLICATION_FILE_CONSTANTS)


# It creates a list with only the names of the configuration file constants
# for validating if there are no constants missing.
set(ONLY_NAME_FILE_CONSTANTS "")
foreach(constantsList ${APPLICATION_FILE_CONSTANTS})

    string(REGEX REPLACE "^[ ]+" "" constantsList ${constantsList})     # Strip leading spaces
    string(REGEX MATCH "^[^=]+" constantName ${constantsList})          # Find variable key (name)
    list(APPEND ONLY_NAME_FILE_CONSTANTS ${constantName})

endforeach()

# It checks if all the constants are in the file
foreach(constant ${ALLOWED_CONSTANTS})

    if (NOT "${constant}" IN_LIST ONLY_NAME_FILE_CONSTANTS)
        message(FATAL_ERROR "${constant} is missing on the application.txt file.")
    endif()

endforeach()


# It makes the file constants available for the building process
message(STATUS "application.txt file constants: ")
foreach(constantAndValue ${APPLICATION_FILE_CONSTANTS})

    string(REGEX REPLACE "^[ ]+" "" ConstantAndValue ${constantAndValue})   # Strip leading spaces
    string(REGEX MATCH "^[^=]+" constant ${constantAndValue})               # Find variable key (name)
    string(REPLACE "${constant}=" "" value ${constantAndValue})             # Find the value

    message(STATUS "    ${constant}: ${value}")
    set(${constant} "${value}")

endforeach()
