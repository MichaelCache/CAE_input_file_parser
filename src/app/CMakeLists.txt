add_executable(parse_file parse_file.cpp)
target_include_directories(parse_file PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(parse_file PUBLIC CLI11 caeparser)
if(WIN32)
  # for windows, copy dll to app  dir in runtime
  add_custom_command(
    TARGET parse_file
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:caeparser>
            $<TARGET_FILE_DIR:parse_file>
    COMMENT "Copying caeparser.dll to app directory")
endif()
