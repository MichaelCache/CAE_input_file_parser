#pragma once

#include <stack>

#include "ast.h"
#include "not_parsed.h"
#include "platform.h"

namespace CAEParser {
class CAEPARSER_API ParseState {
 public:
  ParseState(/* args */) ;
  ~ParseState() = default;

  std::shared_ptr<ASTNode> _ast{std::make_shared<ASTNode>()};
  std::stack<std::shared_ptr<ASTNode>> _stack;
  NotParsedRange _not_parsed;
};

}  // namespace CAEParser
