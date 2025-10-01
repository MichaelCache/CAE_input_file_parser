#pragma once

#include "pegtl.hpp"

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
    if(current != in.begin()){
      ParseInput pre_char()
    }
  }
};

}  // namespace CAEParser
