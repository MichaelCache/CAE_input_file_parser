#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS
#include "doctest.h"
#include "parser/base_grammar/float_num.h"
#include "parser/base_grammar/int_num.h"
#include "parser/parse_control.h"
#include "tao/pegtl/parse.hpp"

namespace peg = tao::pegtl;

TEST_CASE("save_content_to_tree") {
  struct save_grammar : CAEParser::unsign_int_num, CAEParser::savenode_tag {};
  CAEParser::ParseState state;
  peg::parse<peg::seq<save_grammar>, peg::nothing, CAEParser::SaveToState>(
      peg::memory_input("34", ""), state);
  std::cout << state._ast << std::endl;
}
