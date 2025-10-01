#include "runtime_config.h"

namespace CAEParser {
RuntimeConfig& RuntimeConfig::ins() {
  static RuntimeConfig obj;
  return obj;
}

}  // namespace CAEParser
