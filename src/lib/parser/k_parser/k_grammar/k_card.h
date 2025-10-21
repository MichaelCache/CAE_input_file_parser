#pragma once

#include <algorithm>
#include <cctype>

#include "cut_options.h"
#include "k_card_name.h"
#include "parser/k_parser/k_parse_state.h"
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
            typename ParseState, typename KParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& stat,
                                  KParseState& kstate, States&&... st) {
    auto cur = in.current();
    if (*cur != '*') {
      return false;
    }
    // get cardname line
    while (cur != in.end()) {
      if (*cur == '\n' || *cur == '\r') {
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

    auto [_, option] = cutLastSegment(card_name_option);
    if (option == "_TITLE") {
      kstate._has_title = true;
    } else if (option == "_ID") {
      kstate._has_id = true;
    }

    std::string_view card_name(card_name_option);
    while (true) {
      auto [new_card_name, option] = cutLastSegment(card_name);
      card_name = new_card_name;
      if (k_card_name.count(card_name)) {
        auto pattern = k_card_name.at(card_name);
        std::smatch match_result;
        if (std::regex_match(card_name_option, match_result,
                             pattern->_pattern)) {
          return true;
        }
      } else {
        // do nothing continue loop
      }
      if (option.data() == nullptr) {
        break;
      }
    }
    return false;
  }
};

struct k_card : peg::any {};
}  // namespace K