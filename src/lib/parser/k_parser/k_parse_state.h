#pragma once

#include <string>
#include <vector>


namespace K {
struct KParseState {
  std::vector<std::string> _options;
  bool _has_title;
  bool _has_id;
};

}  // namespace K
