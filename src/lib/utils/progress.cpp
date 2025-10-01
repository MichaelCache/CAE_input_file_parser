#include "progress.h"

namespace CAEParser {
Progress& Progress::ins() {
  static Progress obj;
  return obj;
}
void Progress::setTotal(uint64_t total) { _total = total; }
void Progress::addCount(uint64_t c) {
  _tick += c;
  if (_tick > _total) _tick = _total;
}
void Progress::setCount(uint64_t c) {
  _tick = c;
  if (_tick > _total) _tick = _total;
}
double Progress::progress() const {
  if (_total == 0) return 0;
  return double(_tick) / double(_total);
}
}  // namespace CAEParser
