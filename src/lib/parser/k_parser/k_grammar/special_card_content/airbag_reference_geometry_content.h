#pragma once
#include "parser/k_parser/k_grammar/k_card_content.h"
#include "parser/k_parser/k_grammar/k_card_field.h"
#include "tao/pegtl.hpp"
namespace K {
namespace peg = tao::pegtl;

struct airbag_reference_geometry_content {
  using rule_t = airbag_reference_geometry_content;
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
    auto has_birth =
        std::find_if(kstate._options.begin(), kstate._options.end(),
                     [](const std::string& op) { return op == "BIRTH"; });
    //  AIRBAG_REFERENCE_GEOMETRY's id line has 8 field
    if (kstate._has_id) {
      result =
          result &&
          Control<peg::pad<k_card_8_field_line, comment_line>>::template match<
              A, m_t::next_rewind_mode, Action, Control>(in, state, kstate,
                                                         st...);
    }
    if (result && has_birth != kstate._options.end()) {
      result =
          result &&
          Control<peg::pad<k_card_8_field_line, comment_line>>::template match<
              A, m_t::next_rewind_mode, Action, Control>(in, state, kstate,
                                                         st...);
    }
    if (result) {
      result =
          result &&
          Control<peg::until<k_card_end, peg::sor<k_card_8_3x16_char_field_line,
                                                  comment_line>>>::
              template match<A, m_t::next_rewind_mode, Action, Control>(
                  in, state, kstate, st...);
    }
    return marker(result);
  }
};
}  // namespace K
