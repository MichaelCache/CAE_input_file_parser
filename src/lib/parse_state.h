#pragma once

#include <stack>

#include "ast.h"
#include "platform.h"

namespace CAEParser {
class CAEPARSER_API ParseState {
 public:
  ParseState(/* args */) = default;
  ~ParseState() = default;

  std::shared_ptr<ASTNode> _ast{std::make_shared<ASTNode>()};
  std::stack<std::shared_ptr<ASTNode>> _stack;
};

}  // namespace CAEParser
