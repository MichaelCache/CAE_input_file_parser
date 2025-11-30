#pragma once
#include "parser/k_parser/k_grammar/k_card_content.h"
#include "parser/k_parser/k_grammar/k_card_field.h"
#include "tao/pegtl.hpp"
namespace K {
namespace peg = tao::pegtl;

struct path_field_line
    : peg::seq<k_size_field<peg::plus<peg::range<33, 126>>, 80>,
               peg::star<peg::blank>, peg::eolf>,
      CAEParser::astnode_tag {};

struct ale_fsi_to_load_node {
  using rule_t = ale_fsi_to_load_node;
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

    result = result && Control<peg::pad<k_card_8_field_line, comment_line>>::template match<
                           A, m_t::next_rewind_mode, Action, Control>(
                           in, state, kstate, st...);
    if (result) {
      result = result &&
               Control<peg::pad<peg::opt<path_field_line>, comment_line>>::
                   template match<A, m_t::next_rewind_mode, Action, Control>(
                       in, state, kstate, st...);
    }
    return marker(result);
  }
};
}  // namespace K
