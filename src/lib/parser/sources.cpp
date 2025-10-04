#include "sources.h"

namespace CAEParser {
Sources& Sources::ins() {
  static Sources obj;
  return obj;
}
void Sources::reset() { Sources::ins()._sources_file.clear(); }
void Sources::add(const std::string& s) {
  if (_sources_file.count(s)) {
    // pass
  } else {
    _sources_file.insert(s);
  }
  _current = *(_sources_file.find(s));
}
std::string_view Sources::current() const { return _current; }
}  // namespace CAEParser
