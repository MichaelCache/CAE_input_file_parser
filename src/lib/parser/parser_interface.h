#pragma once

#include <string>
#include <tuple>

#include "ast.h"
#include "not_parsed.h"
#include "platform.h"

namespace CAEParser {
/**
 * @brief Parser interface
 *
 */
class CAEPARSER_API Parser {
 public:
  Parser(/* args */) = default;
  virtual ~Parser() = default;
  virtual std::tuple<std::shared_ptr<ASTNode>, NotParsedRange> parse(
      const std::string& content, const std::string& fn = "std::string") = 0;
  virtual std::tuple<std::shared_ptr<ASTNode>, NotParsedRange> parseFile(
      const std::string& fn) = 0;
};

}  // namespace CAEParser