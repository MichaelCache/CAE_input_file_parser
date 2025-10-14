#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#define DOCTEST_CONFIG_NO_EXCEPTIONS

#include "parser/k_parser/k_grammar.h"

#include "doctest.h"
#include "parser/base_grammar/int_num.h"
#include "parser/k_parser/k_grammar/size_field.h"
#include "tao/pegtl/contrib/trace.hpp"
#include "tao/pegtl/parse.hpp"

namespace peg = tao::pegtl;

TEST_CASE("size_field") {
  struct test_rule
      : peg::rep<2, K::size_field<
                        peg::pad<CAEParser::unsign_int_num, peg::blank>, 8>> {};
  CHECK(peg::parse<test_rule>(peg::memory_input("1         9", "")));
  CHECK_FALSE(peg::parse<test_rule>(peg::memory_input("1   9", "")));
  CHECK(peg::parse<test_rule>(peg::memory_input("1, 9", "")));
}