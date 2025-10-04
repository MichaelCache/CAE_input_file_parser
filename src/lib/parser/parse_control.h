#pragma once

#include <concepts>
#include <type_traits>

#include "ast.h"
#include "control_tag.h"
#include "parse_state.h"
#include "sources.h"
#include "tao/pegtl.hpp"

namespace CAEParser {

template <typename Rule, typename T = void>
struct SaveToState : peg::normal<Rule> {};

// template<typename T>
// concept DerivedFromBase = std::is_base_of_v<savenode_tag, T>;

template <typename Rule>
struct SaveToState<Rule, typename std::enable_if<
                             std::is_base_of<savenode_tag, Rule>::value>::type>
    : peg::normal<Rule> {
  template <typename ParseInput, typename... States>
  static void start(const ParseInput& in, ParseState& state,
                    States&&... /*unused*/) noexcept {
    auto node = std::make_shared<ASTNode>();
    node->setType(std::type_index(typeid(Rule)));
    auto&& pos = in.position();
    node->_start._byte_pos = pos.byte;
    node->_start._line = pos.line;
    node->_start._colum = pos.column;
    Sources::ins().add(in.source());
    node->_source_file = Sources::ins().current();
    state._stack.push(node);
  }

  template <typename ParseInput, typename... States>
  static void success(const ParseInput& in, ParseState& state,
                      States&&... /*unused*/) noexcept {
    auto node = state._stack.top();
    auto&& pos = in.position();
    node->_end._byte_pos = pos.byte;
    node->_end._line = pos.line;
    node->_end._colum = pos.column;
    state._stack.pop();
    state._stack.top()->addChildren(node);
  }

  template <typename ParseInput, typename... States>
  static void failure(const ParseInput& /*unused*/, ParseState& state,
                      States&&... /*unused*/) noexcept {
    state._stack.pop();
  }
};

template <typename Rule>
struct SaveToState<
    Rule, typename std::enable_if<std::is_base_of<not_parsed, Rule>::value,
                                  void>::type> : peg::normal<Rule> {
  template <typename ParseInput, typename... States>
  static void success(const ParseInput& in, ParseState& state,
                      States&&... /*unused*/) noexcept {
    auto&& pos = in.position();
    state._not_parsed.addContent(in.source(), *in.current(), pos.byte, pos.line,
                                 pos.colum);
  }
};

}  // namespace CAEParser
