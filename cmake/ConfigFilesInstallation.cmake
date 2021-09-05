#-----------------------------------------------------------------------------
#
# Configuration and supporting files installation
#
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# data/templates/ (*.xml) supporting files
#-----------------------------------------------------------------------------
install (DIRECTORY "${CMAKE_HOME_DIRECTORY}/data/templates/"
    DESTINATION "${APPLICATION_SHARE_DIRECTORY}/templates"
    FILES_MATCHING PATTERN "*.xml"
)
