#pragma once

#include <regex>

#include "parser/k_parser/k_parse_state.h"
#include "parser/parse_control.h"
#include "parser/parse_state.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;
class KCardPatternBase {
 public:
  KCardPatternBase(const std::string_view& pattern);
  virtual ~KCardPatternBase() = default;
  std::regex _pattern;

  bool (*_match_func)(peg::memory_input<>&, CAEParser::ParseState&,
                      K::KParseState&) = nullptr;
};

template <typename Rule>
class KCardPattern : public KCardPatternBase {
 public:
  KCardPattern(const std::string_view& pattern) : KCardPatternBase(pattern) {
    _match_func =
        &Rule::template match<peg::apply_mode::action,
                              peg::rewind_mode::required, peg::nothing,
                              CAEParser::ParseToTree, peg::memory_input<>&,
                              CAEParser::ParseState&, K::KParseState&>;
  }
};

}  // namespace K