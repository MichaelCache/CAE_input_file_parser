#include "parse_state.h"

namespace CAEParser {
ParseState::ParseState() { _stack.push(_ast); }

}  // namespace CAEParser
