#pragma once

#include "int_num.h"
#include "tao/pegtl.hpp"

namespace CAEParser {
namespace peg = tao::pegtl;
// match ".1" like as float
struct point_num
    : peg::seq<peg::star<peg::digit>, peg::one<'.'>, peg::plus<peg::digit>> {};

// match "1." like as float
struct num_point
    : peg::seq<peg::plus<peg::digit>, peg::one<'.'>, peg::star<peg::digit>> {};

// match "1.", ".1","1.1" like but not endwith e/E as float
struct real_num
    : peg::seq<peg::opt<peg::one<'-', '+'>>, peg::sor<point_num, num_point>,
               peg::not_at<peg::one<'e', 'E'>>> {};

// sci num
struct exp : peg::seq<peg::one<'e', 'E'>, sign_int_num> {};
struct sci_real_num
    : peg::seq<peg::opt<peg::one<'-', '+'>>,
               peg::sor<peg::seq<peg::plus<peg::digit>, exp>,
                        peg::seq<peg::sor<point_num, num_point>, exp>>> {};
struct float_num : peg::sor<real_num, sci_real_num> {};
}  // namespace CAEParser
