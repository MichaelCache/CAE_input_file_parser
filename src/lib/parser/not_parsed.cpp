#include "not_parsed.h"

#include <format>
#include <sstream>

namespace CAEParser {

NotParsedContent::NotParsedContent(const std::string& s, const Position& start,
                                   const Position& end)
    : _content(s), _start(start), _end(end) {}

void NotParsedRange::addContent(const std::string& filename, const char& c,
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

bool NotParsedRange::empty() const { return _not_parsed_range.empty(); }

std::ostream& operator<<(std::ostream& os, const NotParsedRange not_parsed) {
  for (auto&& f_l : not_parsed._not_parsed_range) {
    // step.1 find longest colum num tostring width
    auto& l_map = f_l.second;
    auto& longest_lineno = l_map.rbegin()->first;
    auto lineno_width = std::to_string(longest_lineno).size();
    auto lineno_width_str = std::to_string(lineno_width);
    auto lineno_format = "{:" + lineno_width_str + "}";
    // step.2 stream out not parsed content;
    os << "Not Parsed content in " << f_l.first << " :\n";
    os << "--------------------------------------------------------------------"
          "------------\n";
    for (auto&& line_content : l_map) {
      // MSVC std::format only accept constexpr format string, so we use
      // std::vformat
      os << std::vformat(lineno_format,
                         std::make_format_args(line_content.first))
         << ":";
      uint64_t last_col = 1;
      for (auto&& content : line_content.second) {
        os << std::string(content._start._colum - last_col, ' ')
           << content._content;
        last_col = content._end._colum;
      }
      os << std::endl;
    }

    os << "--------------------------------------------------------------------"
          "------------\n";
  }

  return os;
}

}  // namespace CAEParser
