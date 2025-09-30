add_library(parser_base SHARED ast.cpp)
target_link_libraries(parser_base PUBLIC pegtl)