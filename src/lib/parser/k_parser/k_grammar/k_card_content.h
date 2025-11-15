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

// ------------------------------ card line -----------------------------------
struct k_card_8_3x16_char_field_line
    : peg::seq<k_size_field<k_card_field, 8>,
               peg::rep<3, k_size_field<k_card_field, 16>>,
               peg::star<peg::blank>, peg::eolf>,
      CAEParser::astnode_tag {};

struct k_card_8_field_line
    : peg::seq<peg::rep<8, k_size_field<k_card_field, 10>>,
               peg::star<peg::blank>, peg::eolf>,
      CAEParser::astnode_tag {};
struct k_card_10_field_line
    : peg::seq<peg::rep<10, k_size_field<k_card_field, 8>>,
               peg::star<peg::blank>, peg::eolf>,
      CAEParser::astnode_tag {};

template <typename Rule>
struct k_card_not_all_empty_line {
  using rule_t = k_card_not_all_empty_line;
  using subs_t = peg::empty_list;
  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename ParseState, typename KParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& state,
                                  KParseState& kstate, States&&... st) {
    auto marker = in.template mark<M>();
    using m_t = decltype(marker);

    bool result =
        Control<Rule>::template match<A, m_t::next_rewind_mode, Action,
                                      Control>(in, state, kstate, st...);

    if (result) {
      // at least has one non empty field return true
      result = false;
      auto cur_node = state._stack.top();
      for (auto it = cur_node->rbegin(); it != cur_node->rend(); it++) {
        if ((*it)->template is<k_real_field>() ||
            (*it)->template is<k_str_field>() ||
            (*it)->template is<k_int_field>()) {
          result = true;
          break;
        } else if ((*it)->template is<k_empty_field>()) {
          // continue
        } else {
          break;
        }
      }
    }
    return marker(result);
  }
};

struct k_card_8_field_line_not_all_empty
    : k_card_not_all_empty_line<
          peg::seq<peg::rep<8, k_size_field<k_card_field, 10>>,
                   peg::star<peg::blank>, peg::eolf>>,
      CAEParser::astnode_tag {};

struct k_card_10_field_line_not_all_empty
    : k_card_not_all_empty_line<
          peg::seq<peg::rep<10, k_size_field<k_card_field, 8>>,
                   peg::star<peg::blank>, peg::eolf>>,
      CAEParser::astnode_tag {};
// ------------------------------ card line -----------------------------------

// ----------------------------- card content ---------------------------------
struct k_card_content_8_field
    : peg::until<k_card_end, peg::sor<k_card_8_field_line, comment_line>> {};

struct k_card_content_8_field_not_all_empty
    : peg::until<k_card_end, peg::sor<k_card_8_field_line_not_all_empty,
                                      comment_line, empty_line>> {};

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
               Control<peg::pad<IdLine, comment_line>>::template match<
                   A, m_t::next_rewind_mode, Action, Control>(in, state, st...);
    } else if (kstate._has_title) {
      result = result &&
               Control<peg::pad<TitleLine, comment_line>>::template match<
                   A, m_t::next_rewind_mode, Action, Control>(in, state, st...);
    }

    if (result) {
      result =
          result &&
          Control<CardLine>::template match<A, m_t::next_rewind_mode, Action,
                                            Control>(in, state, kstate, st...);
    }
    return marker(result);
  }
};

}  // namespace K
