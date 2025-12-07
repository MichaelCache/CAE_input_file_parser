#include "not_parsed.h"

#include <format>
#include <sstream>

namespace CAEParser {

NotParsedContent::NotParsedContent(const std::string& s, const Position& start,
                                   const Position& end)
    : _content(s), _start(start), _end(end) {}

void NotParsedRange::addContent(const std::string& filename, const char& c,
                                uint64_t pos, uint64_t line, uint64_t col) {
  // TODO:check data valid
  if (!_not_parsed_range.count(filename)) {
    _not_parsed_range[filename];
  }

  auto& file_range = _not_parsed_range.at(filename);
  if (file_range.count(line)) {
    // merge content nearby char in same line
    auto& last_range = file_range.at(line).back();
    if (last_range._end._colum + 1 == col) {
      last_range._content += c;
      last_range._end._colum++;
      last_range._end._byte_pos++;
    }
    // new not parsed range
    else {
      NotParsedContent new_range(std::string(1, c), {pos, line, col},
                                 {pos, line, col});
      file_range.at(line).emplace_back(std::move(new_range));
    }
  } else {
    // new not parsed range
    NotParsedContent new_range(std::string(1, c), {pos, line, col},
                               {pos, line, col});
    file_range[line].emplace_back(std::move(new_range));
  }
}

void NotParsedRange::addMarker(const std::string& filename, uint64_t line,
                               uint64_t col) {
  _error_marker[filename][line].insert(col);
}

bool NotParsedRange::empty() const { return _not_parsed_range.empty(); }

std::ostream& operator<<(std::ostream& os, const NotParsedRange not_parsed) {
  size_t count = not_parsed._not_parsed_range.size();
  size_t i = 1;
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
      bool end_line = false;
      for (auto&& content : line_content.second) {
        os << std::string(content._start._colum - last_col, ' ')
           << content._content;
        last_col = content._end._colum;
        if (content._content.ends_with('\n')) {
          end_line = true;
        }
      }
      if (!end_line) os << std::endl;
      // get a error mark on current file, current line, show a marker
      if (not_parsed._error_marker.count(f_l.first) &&
          not_parsed._error_marker.at(f_l.first).count(line_content.first) &&
          !not_parsed._error_marker.at(f_l.first)
               .at(line_content.first)
               .empty()) {
        auto& marker_content =
            not_parsed._error_marker.at(f_l.first).at(line_content.first);
        auto string_len = *(marker_content.rbegin());
        std::string marker(string_len + 1, ' ');
        for (auto&& i : marker_content) {
          // col start from 1, minus 1 is the index
          marker[i - 1] = '^';
        }
        os << std::string(lineno_width + 1, ' ') << marker << '\n';
      }
    }

    os << "--------------------------------------------------------------------"
          "------------";
    if (i < count) {
      os << "\n";
    }
    i++;
  }

  return os;
}

}  // namespace CAEParser
