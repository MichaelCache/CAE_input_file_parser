#pragma once

#include <regex>

#include "config/runtime_config.h"
#include "parser/k_parser/k_parse_state.h"
#include "parser/parse_control.h"
#include "parser/parse_state.h"
#include "parser/trace_control.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

/**
 * @brief regex make hepler
 *
 */
struct KOptions {
  KOptions(const std::initializer_list<std::string_view>& options,
           bool required = false);
  KOptions(const std::initializer_list<std::string_view>& options,
           const std::string_view& repeat);
  std::string _regex_str;
};

class KCardPatternBase {
 public:
  KCardPatternBase(const std::string_view& card_name,
                   const std::initializer_list<KOptions>& options = {});
  virtual ~KCardPatternBase() = default;
  virtual bool match(const std::string& s);
  virtual std::vector<std::string> options(const std::string& s);

  std::regex _pattern;
  bool (*_match_func)(peg::memory_input<>&, CAEParser::ParseState&,
                      K::KParseState&) = nullptr;

 private:
  //  cache card name option and regex result impove performance
  std::string _card_name_option_cache;
  std::smatch _match_result_cache;
};

template <typename Rule>
class KCardPattern : public KCardPatternBase {
 public:
  KCardPattern(const std::string_view& card_name,
               const std::initializer_list<KOptions>& options = {})
      : KCardPatternBase(card_name, options) {
    // explicit instantiation Rule::template match function
    if (CAEParser::RuntimeConfig::ins()._trace_parser) {
      _match_func = &Rule::template match<
          peg::apply_mode::action, peg::rewind_mode::active, peg::nothing,
          CAEParser::TraceParseToTree, peg::memory_input<>&,
          CAEParser::ParseState&, K::KParseState&>;
    } else {
      _match_func =
          &Rule::template match<peg::apply_mode::action,
                                peg::rewind_mode::active, peg::nothing,
                                CAEParser::ParseToTree, peg::memory_input<>&,
                                CAEParser::ParseState&, K::KParseState&>;
    }
  }
};

}  // namespace K