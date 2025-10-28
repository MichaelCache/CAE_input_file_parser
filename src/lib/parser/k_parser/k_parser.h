#pragma once

#include "parser/parser_interface.h"
#include "platform.h"

namespace K {
/**
 * @brief LS-DYNA k file parser
 *
 */
class CAEPARSER_API KParser : CAEParser::Parser {
 public:
  KParser(/* args */) = default;
  virtual ~KParser() = default;
  virtual std::tuple<std::shared_ptr<CAEParser::ASTNode>,
                     CAEParser::NotParsedRange>
  parse(const std::string& content, const std::string& fn = "std::string");
  virtual std::tuple<std::shared_ptr<CAEParser::ASTNode>,
                     CAEParser::NotParsedRange>
  parseFile(const std::string& fn);
};

}  // namespace K
