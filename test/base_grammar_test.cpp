#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS
#include "doctest.h"
#include "parser/base_grammar/float_num.h"
#include "parser/base_grammar/int_num.h"
#include "tao/pegtl/contrib/trace.hpp"
#include "tao/pegtl/parse.hpp"

namespace peg = tao::pegtl;

TEST_CASE("base_grammar_int_num") {
  CHECK_FALSE(
      peg::parse<CAEParser::unsign_int_num>(peg::memory_input("1.", "")));
  CHECK_FALSE(
      peg::parse<CAEParser::unsign_int_num>(peg::memory_input(".4", "")));
  CHECK_FALSE(
      peg::parse<CAEParser::unsign_int_num>(peg::memory_input("4e1", "")));
  CHECK_FALSE(
      peg::parse<CAEParser::unsign_int_num>(peg::memory_input("5.6", "")));
  CHECK_FALSE(
      peg::parse<CAEParser::unsign_int_num>(peg::memory_input("34er", "")));

  CHECK(peg::parse<CAEParser::unsign_int_num>(peg::memory_input("34", "")));
  CHECK(peg::parse<CAEParser::sign_int_num>(peg::memory_input("34", "")));
  CHECK(peg::parse<CAEParser::sign_int_num>(peg::memory_input("-34", "")));
}

TEST_CASE("base_grammar_float_num") {
  CHECK_FALSE(peg::parse<CAEParser::float_num>(peg::memory_input("1", "")));
  CHECK(peg::parse<CAEParser::float_num>(peg::memory_input(".4", "")));
  CHECK(peg::parse<CAEParser::float_num>(peg::memory_input("4e-1", "")));
  CHECK_FALSE(
      peg::parse<CAEParser::float_num>(peg::memory_input("4e-1.2", "")));
  CHECK(peg::parse<CAEParser::float_num>(peg::memory_input("+5.6", "")));
  CHECK(peg::parse<CAEParser::float_num>(peg::memory_input("5.", "")));
  CHECK_FALSE(peg::parse<CAEParser::float_num>(peg::memory_input("34er", "")));
  CHECK_FALSE(peg::parse<CAEParser::float_num>(peg::memory_input("34", "")));
}
