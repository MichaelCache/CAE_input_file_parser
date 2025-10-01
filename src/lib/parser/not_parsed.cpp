#include "not_parsed.h"

#include <sstream>


namespace CAEParser {

NotParsedContent::NotParsedContent(const std::string& s, const Position& start,
                                   const Position& end)
    : _content(s), _start(start), _end(end) {}

void NotParsedRange::addContent(const std::string& filename, char& c,
                                uint64_t pos, uint64_t line, uint64_t row) {
  // TODO:check data valid
  if (!_not_parsed_range.count(filename)) {
    _not_parsed_range[filename];
  }

  auto& file_range = _not_parsed_range.at(filename);
  if (file_range.count(line)) {
    // merge content nearby char in same line
    auto& last_range = file_range.at(line).back();
    if (last_range._end._colum + 1 == row) {
      last_range._content += c;
      last_range._end._colum++;
      last_range._end._byte_pos++;
    }
    // new not parsed range
    else {
      NotParsedContent new_range(std::string(1, c), {pos, line, row},
                                 {pos, line, row});
      file_range.at(line).emplace_back(std::move(new_range));
    }
  } else {
    // new not parsed range
    NotParsedContent new_range(std::string(1, c), {pos, line, row},
                               {pos, line, row});
    file_range[line].emplace_back(std::move(new_range));
  }
}

std::string NotParsedRange::toString() const {
  std::stringstream ss;
  // TODO:
  return ss.str();
}

}  // namespace CAEParser
