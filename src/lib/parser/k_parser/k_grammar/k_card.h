#pragma once

#include <algorithm>
#include <cctype>

#include "cut_options.h"
#include "k_card_rule.h"
#include "parser/k_parser/k_parse_state.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

struct k_card_name : peg::plus<peg::any>, CAEParser::savenode_tag {};
struct k_card_option : peg::plus<peg::any>, CAEParser::savenode_tag {};

struct k_card_end
    : peg::sor<peg::seq<peg::bol, peg::at<peg::one<'*'>>>, peg::eof> {};

struct k_card_name_option : CAEParser::astnode_tag {
  using rule_t = k_card_name_option;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename ParseState, typename KParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& state,
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

    std::string_view card_name(card_name_option);
    do {
      if (k_card_rule.count(card_name)) {
        auto pattern = k_card_rule.at(card_name);
        std::smatch match_result;
        if (pattern->match(card_name_option)) {
          peg::memory_input tmp_card_name(
              in.begin(), in.current() + card_name.size(), in.source());
          tmp_card_name.iterator() = in.iterator();
          auto res =
              Control<k_card_name>::template match<A, M, Action, Control>(
                  tmp_card_name, state);
          in.bump(card_name.size());
          auto options = pattern->options(card_name_option);
          for (auto& i : options) {
            kstate._options.push_back(i);
            if (i == "_TITLE") {
              kstate._has_title = true;
            } else if (i == "_ID") {
              kstate._has_id = true;
            }
            peg::memory_input tmp_card_option(
                in.begin(), in.current() + i.size(), in.source());
            tmp_card_option.iterator() = in.iterator();
            auto res =
                Control<peg::seq<peg::one<'_'>, k_card_option>>::template match<
                    A, M, Action, Control>(tmp_card_option, state);
            in.bump(i.size());
          }

          kstate._match_func = pattern->_match_func;
          kstate._match_func_trace = pattern->_match_func_trace;
          return true;
        }
      }
      // ontinue loop, cut last options until no more option
      auto [new_card_name, option] = cutLastSegment(card_name);
      if (option.data() == nullptr) {
        // no more options found, break loop
        break;
      }
      card_name = new_card_name;
    } while (true);

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
  [[nodiscard]] static bool match(ParseInput& in, ParseState& state,
                                  States&&... st) {
    KParseState kstate;
    bool result = true;
    auto marker = in.template mark<M>();
    using m_t = decltype(marker);
    result = result &&
             peg::seq<k_card_name_option, peg::star<peg::blank>, peg::eol>::
                 template match<A, m_t::next_rewind_mode, Action, Control>(
                     in, state, kstate, st...);
    if (result) {
      if (CAEParser::RuntimeConfig::ins()._trace_parser) {
        result = result && kstate._match_func_trace(in, state, kstate);
      } else {
        result = result && kstate._match_func(in, state, kstate);
      }
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