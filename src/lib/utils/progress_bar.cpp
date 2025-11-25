#include "progress_bar.h"

#include <math.h>

#include <format>

namespace CAEParser {

ProgressBar::ProgressBar(uint64_t bar_length) : _bar_length(bar_length) {}

ProgressBar& ProgressBar::setProgress(double progress) {
  if (progress < 0) {
    _progress = 0;
  } else if (progress > 1) {
    _progress = 1;
  } else {
    _progress = progress;
  }
  return *this;
}

ProgressBar& ProgressBar::done() {
  _progress = 1;
  return *this;
}

std::ostream& operator<<(std::ostream& os, const ProgressBar& v) {
  auto bar_count = int(floor(v._bar_length * v._progress));
  os << '\r' << '[';
  for (size_t i = 0; i < bar_count; i++) {
    os << '=';
  }
  for (size_t i = 0; i < v._bar_length - bar_count; i++) {
    os << ' ';
  }
  os << ']' << std::format(" {:>5.2f}%", v._progress * 100);
  os.flush();
  return os;
}

}  // namespace CAEParser
