#pragma once

#include <algorithm>
#include <cctype>

#include "cut_options.h"
#include "k_card_rule.h"
#include "parser/k_parser/k_parse_state.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

struct k_card_end
    : peg::sor<peg::seq<peg::bol, peg::at<peg::one<'*'>>>, peg::eof> {};

struct k_card_name_option {
  using rule_t = k_card_name_option;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename ParseState, typename KParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& stat,
                                  KParseState& kstate, States&&... st) {
    auto cur = in.current();
    if (*cur != '*') {
      return false;
    }
    // get cardname line
    while (cur != in.end()) {
      if (*cur == '\n' || *cur == '\r' || *cur == ' ' || *cur == '\t') {
        break;
      }
      cur++;
    }
    // get temp input for card_name match
    std::string card_name_option(in.current(), cur);
    // to upper
    std::transform(card_name_option.begin(), card_name_option.end(),
                   card_name_option.begin(),
                   [](char& c) { return std::toupper(c); });

    if (k_card_rule.count(card_name_option)) {
      auto pattern = k_card_rule.at(card_name_option);
      std::smatch match_result;
      if (std::regex_match(card_name_option, match_result, pattern->_pattern)) {
        kstate._match_func = pattern->_match_func;
        in.bump(card_name_option.size());
        return true;
      }
    }

    auto [_, option] = cutLastSegment(card_name_option);
    if (option == "_TITLE") {
      kstate._has_title = true;
    } else if (option == "_ID") {
      kstate._has_id = true;
    }

    std::string_view card_name(card_name_option);
    while (true) {
      // cut last options until no more option
      auto [new_card_name, option] = cutLastSegment(card_name);
      card_name = new_card_name;
      if (k_card_rule.count(card_name)) {
        auto pattern = k_card_rule.at(card_name);
        std::smatch match_result;
        if (std::regex_match(card_name_option, match_result,
                             pattern->_pattern)) {
          kstate._match_func = pattern->_match_func;
          in.bump(card_name_option.size());
          return true;
        }
      } else {
        // do nothing, continue loop cut last segment
      }
      if (option.data() == nullptr) {
        // no more options founc, break loop
        break;
      }
    }
    return false;
  }
};

struct k_card : public CAEParser::astnode_tag {
  using rule_t = k_card;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename ParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& stat,
                                  States&&... st) {
    KParseState kstate;
    bool result = true;
    auto marker = in.mark<M>();
    using m_t = decltype(marker);
    result = result &&
             peg::seq<k_card_name_option, peg::star<peg::blank>, peg::eol>::
                 template match<A, m_t::next_rewind_mode, Action, Control>(
                     in, stat, kstate, st...);
    if (result) {
      result = result && kstate._match_func(in, stat, kstate);
      if (result) {
        return marker(true);
      } else {
        return marker(false);
      }
    } else {
      return marker(false);
    }
  }
};
}  // namespace K