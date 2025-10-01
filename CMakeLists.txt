cmake_minimum_required(VERSION 3.12)

# ##############################################################################
# get version from version.h                                                   #
# ##############################################################################
file(STRINGS "${CMAKE_CURRENT_LIST_DIR}/src/version.h" CAEPARSER_VERSION_DEFINES
     REGEX "#define[ \t]+CAE_PARSER_VERSION_(MAJOR|MINOR|PATCH) ")

foreach(ver ${CAEPARSER_VERSION_DEFINES})
  if(ver MATCHES
     [[#define[ \t]+CAE_PARSER_VERSION_(MAJOR|MINOR|PATCH)[ \t]+([^ ]+)$]])
    set(CAE_PARSER_VERSION_${CMAKE_MATCH_1} ${CMAKE_MATCH_2})
  endif()
endforeach()

set(CAE_PARSER_VERSION
    "${CAE_PARSER_VERSION_MAJOR}.${CAE_PARSER_VERSION_MINOR}.${CAE_PARSER_VERSION_PATCH}"
)

project(
  CAEParser
  VERSION ${CAE_PARSER_VERSION}
  LANGUAGES CXX)

# ##############################################################################
# installation directories                                                     #
# ##############################################################################
set(PROJECT_INSTALL_INCLUDE_DIR "${CMAKE_INSTALL_PREFIX}/include/CAEParser")
set(PROJECT_INSTALL_BIN_DIR "${CMAKE_INSTALL_PREFIX}/bin")
set(PROJECT_INSTALL_LIB_DIR "${CMAKE_INSTALL_PREFIX}/lib/CAEParser")
set(PROJECT_INSTALL_CMAKE_DIR "${CMAKE_INSTALL_PREFIX}/lib/cmake")

set(CMAKE_CXX_STANDARD 20)
set(EXPORT_COMPILE_COMMANDS True)

if(CMAKE_CURRENT_SOURCE_DIR STREQUAL CMAKE_SOURCE_DIR)
  set(CAEPARSER_IS_MAIN_PROJECT ON)
endif()

add_subdirectory(src)

if(CAEPARSER_IS_MAIN_PROJECT)
  add_subdirectory(test)
endif()
