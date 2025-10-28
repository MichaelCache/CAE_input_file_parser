#pragma once

#include "k_card.h"
#include "k_card_field.h"
#include "k_size_field.h"
#include "k_title_id.h"
#include "k_trival_grammar.h"
#include "tao/pegtl.hpp"


namespace K {
namespace peg = tao::pegtl;

struct k_card_8_field_line
    : peg::seq<peg::rep<10, k_size_field<k_card_field, 8>>,
               peg::sor<comment, peg::star<peg::space>>, peg::eolf> {};

struct k_card_10_field_line
    : peg::seq<peg::rep<8, k_size_field<k_card_field, 10>>,
               peg::sor<comment, peg::star<peg::space>>, peg::eolf> {};

template <typename CardLine>
struct k_card_content {
  using rule_t = k_card_content;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename ParseState, typename KParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& stat,
                                  KParseState& kstate, States&&... st) {
    bool result = true;
    auto marker = in.mark<M>();
    using m_t = decltype(marker);

    if (kstate._has_id) {
      result = result &&
               peg::pad<id_line, comment_line>::template match<
                   A, m_t::next_rewind_mode, Action, Control>(in, stat, st...);
    }
    if (!result) {
      return marker(false);
    }
    if (kstate._has_title) {
      result = result &&
               peg::pad<title_line, comment_line>::template match<
                   A, m_t::next_rewind_mode, Action, Control>(in, stat, st...);
    }
    if (!result) {
      return marker(false);
    }

    result = result &
             peg::until<k_card_end, peg::sor<CardLine, comment_line>>::
                 template match<A, m_t::next_rewind_mode, Action, Control>(
                     in, stat, kstate, st...);
    return marker(result);
  }
};

struct k_card_content_10_field
    : peg::until<k_card_end, peg::sor<k_card_10_field_line, comment_line>> {};

}  // namespace K
