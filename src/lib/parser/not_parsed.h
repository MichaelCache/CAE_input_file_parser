#pragma once

#include <map>
#include <string>
#include <unordered_map>

#include "platform.h"
#include "position.h"

namespace CAEParser {

struct CAEPARSER_API NotParsedContent {
  NotParsedContent(const std::string& s, const Position& start,
                   const Position& end);
  std::string _content;
  Position _start;
  Position _end;
};

struct CAEPARSER_API NotParsedRange {
  using FileName = std::string;
  using LineNo = uint64_t;

  void addContent(const std::string& filename, char& c, uint64_t pos,
                  uint64_t line, uint64_t row);

  std::string toString() const;

  std::unordered_map<FileName, std::map<LineNo, std::vector<NotParsedContent>>>
      _not_parsed_range;
};

}  // namespace CAEParser
