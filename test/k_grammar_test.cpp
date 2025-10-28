#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS

#include "parser/k_parser/k_grammar.h"

#include "doctest.h"
#include "parser/base_grammar/int_num.h"
#include "parser/k_parser/k_grammar/k_card_field.h"
#include "parser/k_parser/k_grammar/k_size_field.h"
#include "parser/trace_control.h"
#include "tao/pegtl/parse.hpp"

namespace peg = tao::pegtl;

TEST_CASE("k_size_field") {
  struct test_rule
      : peg::rep<2, K::k_size_field<peg::pad<K::k_card_field, peg::blank>, 8>> {
  };
  CHECK(peg::parse<test_rule>(peg::memory_input("1         asb", "")));
  CHECK_FALSE(peg::parse<test_rule>(peg::memory_input("1   9", "")));
  CHECK(peg::parse<test_rule>(peg::memory_input("1, 9", "")));
}

TEST_CASE("k_special_sci_num") {
  CHECK_FALSE(peg::parse<K::k_sp_sci_num>(peg::memory_input("1.", "")));
  CHECK(peg::parse<K::k_sp_sci_num>(peg::memory_input("1.+3", "")));
  CHECK(peg::parse<K::k_sp_sci_num>(peg::memory_input("2+3", "")));
  CHECK(peg::parse<K::k_sp_sci_num>(peg::memory_input(".2+3", "")));
}

TEST_CASE("k_card_name_option") {
  CHECK_FALSE(
      peg::parse<K::k_card_name_option, peg::nothing, CAEParser::SaveToState>(
          peg::memory_input("*AIRBAG", ""), CAEParser::ParseState(),
          K::KParseState()));

  CHECK(peg::parse<K::k_card_name_option, peg::nothing, CAEParser::SaveToState>(
      peg::memory_input("*AIRBAG_SIMPLE_AIRBAG_MODEL", ""),
      CAEParser::ParseState(), K::KParseState()));
  CHECK(peg::parse<K::k_card_name_option, peg::nothing, CAEParser::SaveToState>(
      peg::memory_input("*AIRBAG_SIMPLE_AIRBAG_MODEL        ", ""),
      CAEParser::ParseState(), K::KParseState()));
  CHECK(peg::parse<K::k_card_name_option, peg::nothing, CAEParser::SaveToState>(
      peg::memory_input("*AIRBAG_SIMPLE_AIRBAG_MODEL_POP", ""),
      CAEParser::ParseState(), K::KParseState()));
}

TEST_CASE("k_card") {
  CAEParser::ParseState state;
  CHECK(peg::parse<K::k_card, peg::nothing, CAEParser::ParseToTree>(
      peg::memory_input(R"(*CONTROL_TERMINATION
$   endtim    endcyc     dtmin    endeng    endmas
      10.0         0       0.0       0.01.000000E8)",
                        ""),
      state, K::KParseState()));
  std::cout << state._ast << std::endl;
}