#pragma once

#include "platform.h"

namespace CAEParser {
class CAEPARSER_API RuntimeConfig {
 public:
  static RuntimeConfig& ins();

  bool _show_progress{true};
  bool _trace_parser{false};

 private:
  RuntimeConfig(/* args */) = default;
  ~RuntimeConfig() = default;
};

}  // namespace CAEParser
