file(GLOB_RECURSE TEST_SRC *.cpp)
foreach(CPP_FILE ${TEST_SRC})
  get_filename_component(EXECUTABLE_NAME ${CPP_FILE} NAME_WE)
  add_executable(${EXECUTABLE_NAME} ${CPP_FILE})
  target_link_directories(${EXECUTABLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} PUBLIC caeparser)
  add_custom_command(
  TARGET ${EXECUTABLE_NAME}
  POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:caeparser>
          $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
  COMMENT "Copying caeparser.dll to executable directory")
endforeach()


