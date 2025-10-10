#pragma once

#include "parser/parser_interface.h"
#include "platform.h"

namespace CAEParser {
/**
 * @brief lsdyna k file parser
 *
 */
class CAEPARSER_API KParser : Parser {
 public:
  KParser(/* args */) = default;
  virtual ~KParser() = default;
  virtual std::tuple<std::shared_ptr<ASTNode>, NotParsedRange> parse(
      const std::string& content, const std::string& fn = "std::string");
  virtual std::tuple<std::shared_ptr<ASTNode>, NotParsedRange> parseFile(
      const std::string& fn);
};

}  // namespace CAEParser
