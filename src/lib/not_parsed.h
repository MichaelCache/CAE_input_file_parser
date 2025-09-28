#pragma once

#include <string>
#include <unordered_map>

#include "platform.h"
#include "position.h"

namespace CAEParser {

struct CAEPARSER_API NotParsedRange {
  Position _start;
  Position _end;
};

struct CAEPARSER_API NotParsedContent {
  using FileName = std::string;
  std::unordered_map<FileName, std::vector<NotParsedRange>> _not_parsed_range;
};

}  // namespace CAEParser
