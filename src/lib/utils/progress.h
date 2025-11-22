#pragma once

#include <cstdint>

namespace CAEParser {
class Progress {
 public:
  static Progress& ins();
  void setTotal(uint64_t);
  void addCount(uint64_t);
  void setCount(uint64_t);
  double progress() const;
  void done();

 private:
  Progress(/* args */) = default;
  ~Progress() = default;
  uint64_t _total{0};
  uint64_t _tick{0};
};

}  // namespace CAEParser
