#pragma once

#include <iostream>

#include "parse_control.h"
#include "tao/pegtl.hpp"

namespace CAEParser {
namespace peg = tao::pegtl;
/**
 * @brief trace grammar parse process and print to stdout
 *
 * @tparam Rule
 */
template <typename Rule, template <typename...> class Base>
struct Trace : public Base<Rule> {
  template <typename ParseInput, typename... States>
  static void start(const ParseInput& in, States&&... st /*unused*/) noexcept {
    std::cout << "start " << peg::demangle<Rule>() << ":" << in.position()
              << std::endl;
    Base<Rule>::start(in, st...);
  }

  template <typename ParseInput, typename... States>
  static void success(const ParseInput& in, States&&... st) noexcept {
    std::cout << "success " << peg::demangle<Rule>() << ":" << in.position()
              << std::endl;
    Base<Rule>::success(in, st...);
  }

  template <typename ParseInput, typename... States>
  static void failure(const ParseInput& in, States&&... st) noexcept {
    std::cout << "failure " << peg::demangle<Rule>() << ":" << in.position()
              << std::endl;
    Base<Rule>::failure(in, st...);
  }
};

template <typename Rule>
using TraceParseToTree = Trace<Rule, ParseToTree>;

}  // namespace CAEParser
