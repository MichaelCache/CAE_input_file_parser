#pragma once
#include "parser/k_parser/k_grammar/k_card_content.h"
#include "parser/k_parser/k_grammar/k_card_field.h"
#include "tao/pegtl.hpp"
namespace K {
namespace peg = tao::pegtl;

struct points_field_line
    : peg::seq<k_size_field<k_int_field, 20>, k_size_field<k_real_field, 20>,
               k_size_field<k_real_field, 20>, peg::star<peg::blank>,
               peg::eolf>,
      CAEParser::astnode_tag {};

struct ale_structured_mesh_control_points {
  using rule_t = ale_structured_mesh_control_points;
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

    result =
        result &&
        Control<peg::pad<k_card_8_field_line, comment_line>>::template match<
            A, m_t::next_rewind_mode, Action, Control>(in, state, kstate,
                                                       st...);
    if (result) {
      result = result &&
               Control<peg::until<k_card_end,
                                  peg::sor<points_field_line, comment_line>>>::
                   template match<A, m_t::next_rewind_mode, Action, Control>(
                       in, state, kstate, st...);
    }
    return marker(result);
  }
};
}  // namespace K
