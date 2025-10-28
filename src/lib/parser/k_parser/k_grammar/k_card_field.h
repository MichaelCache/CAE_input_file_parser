#pragma once

#include "parser/base_grammar/float_num.h"
#include "parser/base_grammar/int_num.h"
#include "parser/control_tag.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;
// for special sci num in k file like 1.+3, 1.3+3, .3+3, 2+4
struct k_sp_sci_num
    : peg::seq<
          peg::opt<peg::one<'-', '+'>>,
          peg::sor<
              peg::seq<peg::plus<peg::digit>, peg::one<'-', '+'>, peg::digit>,
              peg::seq<peg::sor<CAEParser::point_num, CAEParser::num_point>,
                       peg::one<'-', '+'>, peg::digit>>> {};

struct k_real_field : peg::seq<peg::sor<k_sp_sci_num, CAEParser::float_num>,
                               peg::not_at<peg::alpha>>,
                      CAEParser::savenode_tag {};

struct k_str_field : peg::plus<peg::sor<peg::alpha, peg::one<'&'>>>,
                     CAEParser::savenode_tag {};
struct k_int_field : peg::seq<CAEParser::sign_int_num, peg::not_at<peg::alpha>>,
                     CAEParser::savenode_tag {};

/**
 * @brief k card field may empty, means use default value, we called it emtpy
 * field
 *
 */
struct k_empty_field : CAEParser::savenode_tag {
  using rule_t = k_empty_field;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename... States>
  [[nodiscard]] static bool match(ParseInput& in, States&&... st) {
    if (in.current() == in.end()) {
      // no more char in sized field, it's empty field too
      return true;
    } else {
      // all char in sized field if space ro tab
      return peg::plus<peg::blank>::template match<A, M, Action, Control>(
          in, st...);
    }
  }
};

struct k_card_field
    : peg::sor<k_int_field, k_real_field, k_str_field, k_empty_field> {};
}  // namespace  K
