#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS
#include "doctest.h"
#include "parser/base_grammar/int_num.h"
#include "tao/pegtl/contrib/trace.hpp"
#include "tao/pegtl/parse.hpp"

TEST_CASE("base_grammar_int_num") {
  namespace peg = tao::pegtl;
  peg::standard_trace<CAEParser::unsign_int_num>(peg::memory_input("1.", ""));
  CHECK_FALSE(
      peg::parse<CAEParser::unsign_int_num>(peg::memory_input("1.", "")));
}