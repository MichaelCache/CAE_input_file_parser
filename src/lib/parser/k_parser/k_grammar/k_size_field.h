#pragma once
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

/**
 * @brief Match give sized field in k card
 *
 * @tparam Rule field content rule
 * @tparam size field max length
 */
template <typename Rule, size_t size>
struct k_size_field {
  using rule_t = k_size_field;
  using subs_t = peg::type_list<Rule>;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename... States>
  [[nodiscard]] static bool match(ParseInput& in, States&&... st) {
    auto cur = in.current();
    size_t char_count = 0;
    // find size length content before new line
    // also consider k file free style use comma split field
    for (size_t i = 0; i < size && cur != in.end(); i++) {
      if (*cur == '\n' || *cur == '\r' || *cur == ',') {
        break;
      }
      cur++;
      char_count++;
    }
    if ((cur != in.end() && *cur == ',') ||
        (cur + 1 != in.end() && *(cur + 1) == ',')) {
      char_count++;
    }

    // create a temp input for Rule match
    peg::memory_input tmp(in.begin(), cur, in.source());
    tmp.iterator() = in.iterator();
    if (peg::seq<peg::pad<Rule, peg::blank>,
                 peg::eof>::template match<A, M, Action, Control>(tmp, st...)) {
      // only all k_size_field content match, return true
      in.bump(char_count);
      return true;
    } else {
      return false;
    }
  }
};
}  // namespace  K
