add_executable(parse_file parse_file.cpp)
target_include_directories(parse_file PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(parse_file PUBLIC CLI11 caeparser)