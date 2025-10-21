file(GLOB_RECURSE PARSER_SRC *.cpp)
add_library(caeparser SHARED ${PARSER_SRC})
target_link_libraries(caeparser PUBLIC pegtl)
target_include_directories(
  caeparser PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                   $<INSTALL_INTERFACE:${PROJECT_INSTALL_INCLUDE_DIR}>)
target_compile_definitions(caeparser PRIVATE -DEXPORT_DLL)

install(TARGETS caeparser DESTINATION ${PROJECT_INSTALL_LIB_DIR})
