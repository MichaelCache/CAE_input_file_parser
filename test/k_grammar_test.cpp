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
  CAEParser::ParseState state;
  CHECK(peg::parse<K::k_card_name_option, peg::nothing, CAEParser::ParseToTree>(
      peg::memory_input("*AIRBAG_SIMPLE_AIRBAG_MODEL_POP", ""), state,
      K::KParseState()));
  std::cout << state._ast << std::endl;
  CHECK_EQ(state._ast->childreSize(), 1);
  auto card_name_option_node = state._ast->at(0);
  CHECK_EQ(card_name_option_node->childreSize(), 3);
  CHECK_EQ(card_name_option_node->at(0)->_content, "*AIRBAG");
  CHECK_EQ(card_name_option_node->at(1)->_content, "SIMPLE_AIRBAG_MODEL");
  CHECK_EQ(card_name_option_node->at(2)->_content, "POP");
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
  CHECK_EQ(state._ast->childreSize(), 1);
  auto card_node = state._ast->at(0);
  // 2 children: card name option and card line
  CHECK_EQ(card_node->childreSize(), 2);
  auto card_name_option_node = card_node->at(0);
  CHECK_EQ(card_name_option_node->childreSize(), 1);
  CHECK_EQ(card_name_option_node->at(0)->_content, "*CONTROL_TERMINATION");
  auto card_line_node = card_node->at(1);
  CHECK_EQ(card_line_node->childreSize(), 8);
  CHECK_EQ(card_line_node->at(0)->_content, "10.0");
  CHECK_EQ(card_line_node->at(1)->_content, "0");
  CHECK_EQ(card_line_node->at(2)->_content, "0.0");
  CHECK_EQ(card_line_node->at(3)->_content, "0.0");
  CHECK_EQ(card_line_node->at(4)->_content, "1.000000E8");
  CHECK_EQ(card_line_node->at(5)->_content, "");
  CHECK_EQ(card_line_node->at(6)->_content, "");
  CHECK_EQ(card_line_node->at(7)->_content, "");
}