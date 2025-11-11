#pragma once
#include "parser/k_parser/k_grammar/k_card_content.h"
#include "parser/k_parser/k_grammar/k_card_field.h"
#include "tao/pegtl.hpp"
namespace K {
namespace peg = tao::pegtl;
struct airbag_particle {
  using rule_t = airbag_particle;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename ParseState, typename KParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& state,
                                  KParseState& kstate, States&&... st) {
    bool result = true;
    auto marker = in.template mark<M>();
    using m_t = decltype(marker);
    auto has_mpp =
        std::find_if(kstate._options.begin(), kstate._options.end(),
                     [](const std::string& op) { return op == "MPP"; });
    if (has_mpp != kstate._options.end()) {
      result =
          result &&
          Control<peg::pad<k_card_8_field_line, comment_line>>::template match<
              A, m_t::next_rewind_mode, Action, Control>(in, state, st...);
    }

    if (result) {
      // for AIRBAG_PARTICLE, ID/TITLE option have same fomat, link id line
      if (kstate._has_id || kstate._has_title) {
        result =
            result &&
            Control<peg::pad<id_line, comment_line>>::template match<
                A, m_t::next_rewind_mode, Action, Control>(in, state, st...);
      }
    }

    if (result) {
      result = result && Control<k_card_content_8_field>::template match<
                             A, m_t::next_rewind_mode, Action, Control>(
                             in, state, kstate, st...);
    }

    return marker(result);
  }
};
}  // namespace K
