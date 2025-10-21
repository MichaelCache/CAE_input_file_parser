#include "cut_options.h"

namespace K {

std::tuple<std::string_view, std::string_view> cutLastSegment(
    const std::string_view& str) {
  size_t last_under_score = str.find_last_of('_');
  if (last_under_score != std::string_view::npos) {
    return std::make_tuple(str.substr(0, last_under_score),
                           str.substr(last_under_score));
  }
  return std::make_tuple(str, std::string_view());
}

}  // namespace K
