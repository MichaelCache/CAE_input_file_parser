#include "sources.h"

#include <algorithm>


namespace CAEParser {
Sources& Sources::ins() {
  static Sources obj;
  return obj;
}

void Sources::reset() { Sources::ins()._sources_file.clear(); }

void Sources::add(const std::string& s) {
  auto it = std::find_if(
      _sources_file.begin(), _sources_file.end(),
      [&](const std::shared_ptr<std::string>& sf) { return *sf == s; });
  if (it != _sources_file.end()) {
    _current = *(it);
  } else {
    _current = std::make_shared<std::string>(s);
    _sources_file.push_back(_current);
  }
}

std::shared_ptr<std::string> Sources::current() const { return _current; }
}  // namespace CAEParser
