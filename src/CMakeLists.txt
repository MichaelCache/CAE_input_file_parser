# ##############################################################################
# get version from version.h                                                   #
# ##############################################################################
file(READ ${PROJECT_SOURCE_DIR}/src/version.h VERSION_HEADER_CONTENT)
string(REGEX MATCH "#define[ \t]+CAE_PARSER_VERSION_MAJOR[ \t]+([0-9]+)" _
             ${VERSION_HEADER_CONTENT})
set(PROJECT_VERSION_MAJOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#define[ \t]+CAE_PARSER_VERSION_MINOR[ \t]+([0-9]+)" _
             ${VERSION_HEADER_CONTENT})
set(PROJECT_VERSION_MINOR ${CMAKE_MATCH_1})
string(REGEX MATCH "#define[ \t]+CAE_PARSER_VERSION_PATCH[ \t]+([0-9]+)" _
             ${VERSION_HEADER_CONTENT})
set(PROJECT_VERSION_PATCH ${CMAKE_MATCH_1})
set(PROJECT_VERSION
    "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}"
)
