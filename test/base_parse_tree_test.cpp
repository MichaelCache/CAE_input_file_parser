#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS
#include "doctest.h"
#include "parser/base_grammar/float_num.h"
#include "parser/base_grammar/int_num.h"
#include "parser/parse_control.h"
#include "tao/pegtl/contrib/trace.hpp"
#include "tao/pegtl/parse.hpp"

namespace peg = tao::pegtl;
struct save_grammar : CAEParser::unsign_int_num, CAEParser::savenode_tag {};
struct not_parsed : peg::any, CAEParser::not_parsed_tag {};
struct grammar : peg::until<peg::eolf, peg::sor<save_grammar, not_parsed>> {};

TEST_CASE("save_content_to_tree") {
  CAEParser::ParseState state;
  peg::parse<grammar, peg::nothing, CAEParser::ParseToTree>(
      peg::memory_input("34", "memory"), state);
  CHECK_EQ(state._ast->childreSize(), 1);
  // if all content can be parsed, not_parsed will be empty
  CHECK(state._not_parsed.empty());
  auto first_child_node = *state._ast->begin();
  CHECK_EQ(first_child_node->_content, "34");
  CHECK_EQ(first_child_node->_start._line, 1);
  CHECK_EQ(first_child_node->_end._line, 1);
  CHECK_EQ(first_child_node->_start._colum, 1);
  CHECK_EQ(first_child_node->_end._colum, 3);
  std::cout << state._ast << std::endl;
}

TEST_CASE("show_not_parsed_content") {
  CAEParser::ParseState state;
  peg::parse<grammar, peg::nothing, CAEParser::ParseToTree>(
      peg::memory_input("34.", "memory"), state);
  std::cout << state._ast << std::endl;
  CHECK_EQ(state._ast->childreSize(), 0);
  CHECK_FALSE(state._not_parsed.empty());
  std::cout << state._not_parsed << std::endl;
}