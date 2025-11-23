#pragma once

#include <stdint.h>

#include <ostream>

namespace CAEParser {
/**
 * @brief pretty print progress
 *
 */
class ProgressBar {
 public:
  ProgressBar(uint64_t total, uint64_t bar_length = 80);
  ~ProgressBar() = default;
  ProgressBar& setProgress(double progress);
  ProgressBar& done();

  friend std::ostream& operator<<(std::ostream& os, const ProgressBar& v);

  uint64_t _total;
  uint64_t _bar_length{80};
  double _progress;
};

}  // namespace CAEParser
