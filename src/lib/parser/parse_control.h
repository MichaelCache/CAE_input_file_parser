#pragma once

#include <concepts>
#include <type_traits>

#include "ast.h"
#include "control_tag.h"
#include "parse_state.h"
#include "sources.h"
#include "tao/pegtl.hpp"

namespace CAEParser {
namespace peg = tao::pegtl;

template <typename T, typename Base>
concept DerivedFromBase = std::is_base_of_v<Base, T>;

/**
 * @brief save astnode to CAEParser::ParseState
 *
 * @tparam Rule
 */
template <typename Rule>
struct SaveToState : peg::normal<Rule> {};

template <typename Rule>
  requires DerivedFromBase<Rule, astnode_tag>
struct SaveToState<Rule> : peg::normal<Rule> {
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
  requires DerivedFromBase<Rule, not_parsed_tag>
struct SaveToState<Rule> : peg::normal<Rule> {
  template <typename ParseInput, typename... States>
  static void start(const ParseInput& in, ParseState& state,
                    States&&... /*unused*/) noexcept {
    auto&& pos = in.position();
    state._not_parsed.addContent(in.source(), *in.current(), pos.byte, pos.line,
                                 pos.column);
  }
};

/**
 * @brief save astnode to CAEParser::ParseState, and save content
 *
 * @tparam Rule
 */
template <typename Rule>
struct ParseToTree : SaveToState<Rule> {};

template <typename Rule>
  requires DerivedFromBase<Rule, savenode_tag>
struct ParseToTree<Rule> : SaveToState<Rule> {
  template <typename ParseInput, typename... States>
  static void success(const ParseInput& in, ParseState& state,
                      States&&... /*unused*/) noexcept {
    auto node = state._stack.top();
    node->_content =
        std::string(in.begin() + node->_start._byte_pos, in.current());
    SaveToState<Rule>::success(in, state);
  }
};

}  // namespace CAEParser
