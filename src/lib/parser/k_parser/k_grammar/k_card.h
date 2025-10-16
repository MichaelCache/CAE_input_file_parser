#pragma once

#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;
// TODO:

struct k_card_end
    : peg::sor<peg::seq<peg::bol, peg::at<peg::one<'*'>>>, peg::eof> {};

struct k_card_name_option {
  using rule_t = k_card_name_option;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename... States>
  [[nodiscard]] static bool match(ParseInput& in, States&&... st) {
    auto cur = in.current();
    if (*cur != "*") {
      return false;
    }
    // get cardname line
    while (cur != in.end) {
      if (*cur == '\n' || *cur == '\r') {
        break;
      }
      cur++;
    }
    // get temp input for card_name match
    std::string_view card_name_option(in.current(), cur);
  }
};

struct k_card : peg::any {};
}  // namespace K