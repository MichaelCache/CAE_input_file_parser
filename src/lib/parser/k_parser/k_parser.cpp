#include "k_parser.h"

#include <chrono>
#include <future>
#include <tuple>

#include "config/runtime_config.h"
#include "k_grammar.h"
#include "parser/k_parser/k_parse_control.h"
#include "parser/parse_state.h"
#include "tao/pegtl.hpp"
#include "tao/pegtl/contrib/analyze.hpp"
#include "tao/pegtl/contrib/trace.hpp"
#include "utils/cout_wrapper.h"

namespace K {
namespace peg = tao::pegtl;

std::tuple<std::shared_ptr<CAEParser::ASTNode>, CAEParser::NotParsedRange>
KParser::parse(const std::string& content, const std::string& fn) {
  peg::string_input input(content, fn);

#ifdef NDEBUG
  // check grammar has no problem
  auto problems = peg::analyze<k_grammar>();
  if (problems) {
    throw std::runtime_error("k_grammar has problem");
  }
#endif
  if (CAEParser::RuntimeConfig::ins()._trace_parser) {
    // trace parse if enable
    peg::string_input trace_input(content, fn);
    CAEParser::ParseState trace_state;
    peg::parse<k_grammar, peg::nothing, CAEParser::TraceParseToTree>(
        trace_input, trace_state);
  }

  CAEParser::Progress::ins().setTotal(input.size());

  CAEParser::ParseState state;
  auto future = std::async(std::launch::async, [&]() {
    peg::parse<k_grammar, peg::nothing, KParseControl>(input, state);
  });

  if (CAEParser::RuntimeConfig::ins()._show_progress) {
    CAEParser::ProgressBar bar(input.size());
    CAEParser::cout_wrapper << "Parsing...\n";
    while (future.wait_for(std::chrono::seconds(1)) !=
           std::future_status::ready) {
      CAEParser::cout_wrapper
          << bar.setProgress(CAEParser::Progress::ins().progress());
    }
    CAEParser::cout_wrapper << bar.done();
  }

  future.get();
  return std::make_tuple(state._ast, state._not_parsed);
}

std::tuple<std::shared_ptr<CAEParser::ASTNode>, CAEParser::NotParsedRange>
KParser::parseFile(const std::string& fn) {
  peg::file_input input(fn);

#ifdef NDEBUG
  // check grammar has no problem
  auto problems = peg::analyze<k_grammar>();
  if (problems) {
    throw std::runtime_error("k_grammar has problem");
  }
#endif
  if (CAEParser::RuntimeConfig::ins()._trace_parser) {
    peg::file_input trace_input(fn);
    CAEParser::ParseState trace_state;
    peg::parse<k_grammar, peg::nothing, CAEParser::TraceParseToTree>(
        trace_input, trace_state);
  }

  CAEParser::Progress::ins().setTotal(input.size());
  CAEParser::ParseState state;
  auto future = std::async(std::launch::async, [&]() {
    peg::parse<k_grammar, peg::nothing, KParseControl>(input, state);
  });

  if (CAEParser::RuntimeConfig::ins()._show_progress) {
    CAEParser::ProgressBar bar(input.size());
    CAEParser::cout_wrapper << "Parsing...\n";
    while (future.wait_for(std::chrono::seconds(0)) !=
           std::future_status::ready) {
      CAEParser::cout_wrapper
          << bar.setProgress(CAEParser::Progress::ins().progress());
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    CAEParser::cout_wrapper << bar.done();
  }

  future.get();
  return std::make_tuple(state._ast, state._not_parsed);
}

}  // namespace K
