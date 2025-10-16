#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS

#include "parser/k_parser/k_grammar.h"

#include "doctest.h"
#include "parser/base_grammar/int_num.h"
#include "parser/k_parser/k_grammar/card_field.h"
#include "parser/k_parser/k_grammar/size_field.h"
#include "tao/pegtl/contrib/trace.hpp"
#include "tao/pegtl/parse.hpp"


namespace peg = tao::pegtl;

TEST_CASE("size_field") {
  struct test_rule
      : peg::rep<2, K::size_field<peg::pad<K::k_card_field, peg::blank>, 8>> {};
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