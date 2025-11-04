#pragma once

#include "k_control_tag.h"
#include "parser/parse_control.h"
#include "parser/parse_state.h"

namespace K {
template <typename Rule>
struct KParseControl : public CAEParser::SaveToState<Rule> {};

template <typename Rule>
  requires CAEParser::DerivedFromBase<Rule, CAEParser::savenode_tag>
struct KParseControl<Rule> : CAEParser::SaveToState<Rule> {
  template <typename ParseInput, typename... States>
  static void success(const ParseInput& in, CAEParser::ParseState& state,
                      States&&... /*unused*/) noexcept {
    auto node = state._stack.top();
    node->_content =
        std::string(in.begin() + node->_start._byte_pos, in.current());
    auto&& pos = in.position();
    node->_end._byte_pos = pos.byte;
    node->_end._line = pos.line;
    node->_end._colum = pos.column;
    state._stack.pop();
    state._stack.top()->addChildren(node);
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
