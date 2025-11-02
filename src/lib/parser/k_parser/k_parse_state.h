#pragma once

#include <string>
#include <vector>

#include "parser/parse_state.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;
/**
 * @brief internal temp state to store card name options and matched card
 * content rule
 *
 */
struct KParseState {
  std::vector<std::string> _options;
  bool _has_title{false};
  bool _has_id{false};
  bool (*_match_func)(peg::memory_input<>&, CAEParser::ParseState&,
                      K::KParseState&);
  bool (*_match_func_trace)(peg::memory_input<>&, CAEParser::ParseState&,
                            K::KParseState&);
};

}  // namespace K
