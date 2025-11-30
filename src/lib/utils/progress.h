#pragma once

#include <cstdint>
#include "platform.h"

namespace CAEParser {
/**
 * @brief save and calculate progress
 *
 */
class CAEPARSER_API Progress {
 public:
  static Progress& ins();
  void setTotal(uint64_t);
  void addCount(uint64_t);
  void setCount(uint64_t);
  double progress() const;
  void done();
  uint64_t step() const;
  void setStep(uint64_t);

 private:
  Progress(/* args */) = default;
  ~Progress() = default;
  uint64_t _total{0};
  uint64_t _tick{0};
  uint64_t _step{1};
};

}  // namespace CAEParser
