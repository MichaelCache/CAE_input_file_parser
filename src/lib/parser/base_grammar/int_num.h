#pragma once

#include "tao/pegtl.hpp"

namespace CAEParser {
namespace peg = tao::pegtl;
// we treat number endwith e/E as float number, not int, as C++ syntax
struct unsign_int_num
    : peg::seq<peg::plus<peg::digit>,
               peg::not_at<peg::sor<peg::one<'e', 'E', '.'>, peg::digit>>> {};
struct sign_int_num : peg::seq<peg::opt<peg::one<'-', '+'>>, unsign_int_num> {};
}  // namespace CAEParser
