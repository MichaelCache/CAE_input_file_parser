#pragma once

#include <iostream>

#include "progress_bar.h"

namespace CAEParser {

class OstreamWrapper {
 private:
  bool _progress_mod{false};
  std::ostream& _ost{std::cout};

 public:
  OstreamWrapper() = default;
  virtual ~OstreamWrapper() = default;

  template <typename T>
  OstreamWrapper& operator<<(T&& v) {
    if (_progress_mod) {
      _ost << "\n";
      _progress_mod = false;
    }
    _ost << std::forward<T>(v);
    return *this;
  }

  OstreamWrapper& operator<<(ProgressBar& v);
};

extern OstreamWrapper cout_wrapper;
}  // namespace CAEParser
