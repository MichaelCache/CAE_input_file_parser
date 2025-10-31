#pragma once

#include "k_card.h"
#include "k_card_field.h"
#include "k_size_field.h"
#include "k_title_id.h"
#include "k_trival_grammar.h"
#include "parser/control_tag.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

struct k_card_8_field_line
    : peg::seq<peg::rep<8, k_size_field<k_card_field, 10>>,
               peg::sor<comment, peg::star<peg::space>>, peg::eolf>,
      CAEParser::astnode_tag {};

struct k_card_10_field_line
    : peg::seq<peg::rep<10, k_size_field<k_card_field, 8>>,
               peg::sor<comment, peg::star<peg::space>>, peg::eolf>,
      CAEParser::astnode_tag {};

struct k_card_content_8_field
    : peg::until<k_card_end, peg::sor<k_card_8_field_line, comment_line>> {};
struct k_card_content_10_field
    : peg::until<k_card_end, peg::sor<k_card_10_field_line, comment_line>> {};

template <typename CardLine, typename TitleLine = title_line,
          typename IdLine = id_line>
struct k_card_content {
  using rule_t = k_card_content;
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

    if (kstate._has_id) {
      result = result &&
               peg::pad<IdLine, comment_line>::template match<
                   A, m_t::next_rewind_mode, Action, Control>(in, state, st...);
    } else if (kstate._has_title) {
      result = result &&
               peg::pad<TitleLine, comment_line>::template match<
                   A, m_t::next_rewind_mode, Action, Control>(in, state, st...);
    }

    if (result) {
      result =
          result &
          CardLine::template match<A, m_t::next_rewind_mode, Action, Control>(
              in, state, kstate, st...);
    }
    return marker(result);
  }
};

}  // namespace K
