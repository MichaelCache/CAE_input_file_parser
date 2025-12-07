#pragma once

#include "config/runtime_config.h"
#include "k_control_tag.h"
#include "parser/parse_control.h"
#include "parser/parse_state.h"
#include "utils/progress.h"

namespace K {

struct k_card_field;

template <typename Rule>
struct KParseControl : public CAEParser::ParseToTree<Rule> {
  template <typename ParseInput, typename... States>
  static void failure(const ParseInput& in, CAEParser::ParseState& state,
                      States&&... st) noexcept {
    CAEParser::ParseToTree<Rule>::failure(in, state, st...);
    // mark match faield kcard field to not parsed content
    if (std::is_same_v<Rule, k_card_field>) {
      auto&& pos = in.position();
      state._not_parsed.addMarker(pos.source, pos.line, pos.column);
    }
  }
};

template <typename Rule>
  requires CAEParser::DerivedFromBase<Rule, CAEParser::savenode_tag>
struct KParseControl<Rule> : CAEParser::ParseToTree<Rule> {
  template <typename ParseInput, typename... States>
  static void success(const ParseInput& in, CAEParser::ParseState& state,
                      States&&... st) noexcept {
    auto node = state._stack.top();
    CAEParser::ParseToTree<Rule>::success(in, state, st...);
    if (std::is_base_of_v<trim_tag, Rule>) {
      size_t start = node->_content.find_first_not_of(" \t");
      if (start != std::string::npos) {
        node->_content = node->_content.substr(start);
        node->_start._byte_pos += start;
        node->_start._colum += start;
      }
      size_t end = node->_content.find_last_not_of(" \t");
      if (end != std::string::npos) {
        auto offset = node->_content.size() - end;
        node->_content = node->_content.substr(0, end + 1);
        node->_end._byte_pos -= offset;
        node->_end._colum -= offset;
      }
    }

    if (std::is_base_of_v<to_upper_tag, Rule>) {
      std::transform(node->_content.begin(), node->_content.end(),
                     node->_content.begin(),
                     [](char& c) { return std::toupper(c); });
    }
  }
};
}  // namespace K
