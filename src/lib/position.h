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
  uint64_t byte_pos{0};  //
  uint64_t line{0};
  uint64_t colum{0};
};
}  // namespace CAEParser