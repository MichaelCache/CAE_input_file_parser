#include "k_parser.h"

#include <tuple>

#include "config/runtime_config.h"
#include "k_grammar.h"
#include "parser/parse_control.h"
#include "parser/parse_state.h"
#include "tao/pegtl.hpp"
#include "tao/pegtl/contrib/analyze.hpp"
#include "tao/pegtl/contrib/trace.hpp"

namespace CAEParser {
namespace peg = tao::pegtl;

std::tuple<std::shared_ptr<ASTNode>, NotParsedRange> KParser::parse(
    const std::string& content, const std::string& fn) {
  peg::string_input input(content, fn);

#ifdef NDEBUG
  // check grammar has no problem
  auto problems = peg::analyze<k_grammar>();
  if (problems) {
    throw std::runtime_error("k_grammar has problem");
  }
#endif
  if (RuntimeConfig::ins()._trace_parser) {
    peg::string_input trace_input(content, fn);
    peg::standard_trace<k_grammar>(trace_input);
  }

  ParseState state;
  peg::parse<k_grammar, peg::nothing, ParseToTree>(input, state);
  return std::make_tuple(state._ast, state._not_parsed);
}

std::tuple<std::shared_ptr<ASTNode>, NotParsedRange> KParser::parseFile(
    const std::string& fn) {
  peg::file_input input(fn);

#ifdef NDEBUG
  // check grammar has no problem
  auto problems = peg::analyze<k_grammar>();
  if (problems) {
    throw std::runtime_error("k_grammar has problem");
  }
#endif
  if (RuntimeConfig::ins()._trace_parser) {
    peg::file_input trace_input(fn);
    peg::standard_trace<k_grammar>(trace_input);
  }

  ParseState state;
  peg::parse<k_grammar, peg::nothing, ParseToTree>(input, state);
  return std::make_tuple(state._ast, state._not_parsed);
}

}  // namespace CAEParser
