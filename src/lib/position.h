#pragma once

#include <cstdint>

#include "platform.h"

namespace CAEParser {

/**
 * @brief AST node content postion in file
 *
 */
struct CAEPARSER_API Position {
  // TODO: source file
  uint64_t _byte_pos{0};  //
  uint64_t _line{0};
  uint64_t _colum{0};
};
}  // namespace CAEParser