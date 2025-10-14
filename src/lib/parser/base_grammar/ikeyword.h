#pragma once

#include "tao/pegtl.hpp"

namespace CAEParser {
namespace peg = tao::pegtl;
template <char... Cs>
struct ikeyword {
  template <peg::apply_mode, peg::rewind_mode,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename... States>
  [[nodiscard]] static bool match(ParseInput& in, States&&... st) {
    auto current = in.current();
    if (current != in.begin()) {
      // if pre byte is identifier return false
      ParseInput pre_char(in.iterator() - 1, in.end(), in.source());
      if (peg::identifier_other::template match(pre_char)) {
        return false;
      }
    }
    return peg::istring<Cs...>::template match(in, st...);
  }
};

template <char... Cs>
struct keyword {
  template <peg::apply_mode, peg::rewind_mode,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename... States>
  [[nodiscard]] static bool match(ParseInput& in, States&&... st) {
    auto current = in.current();
    if (current != in.begin()) {
      // if pre byte is identifier return false
      peg::memory_input pre_char(in.current() - 1, in.end(), in.source());
      if (peg::identifier_other::template match(pre_char)) {
        return false;
      }
    }
    return peg::string<Cs...>::template match(in);
  }
};

#define EXTEND_PEGTL_KEYWORD(x) \
  TAO_PEGTL_INTERNAL_STRING(CAEParser::ikeyword, x)

#define EXTEND_PEGTL_IKEYWORD(x) \
  TAO_PEGTL_INTERNAL_STRING(CAEParser::keyword, x)

}  // namespace CAEParser
