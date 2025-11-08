#include <iostream>

#include "CLI/CLI.hpp"
#include "config/runtime_config.h"
#include "parser/k_parser/k_parser.h"
#include "version.h"

enum class InputFileType {
  None,
  K,
};

int main(int argc, char const* argv[]) {
  CLI::App app{
      "CAE input file parser, print parsed abstract syntax tree to stdout for "
      "default"};
  app.set_version_flag("-v,--version", CAE_PARSER_VERSION_STRING);
  InputFileType file_type{InputFileType::None};

  auto input_file_optgroup = app.add_option_group("input file");
  input_file_optgroup->require_option(1);
  std::string input_file;
  input_file_optgroup->add_option("--k", input_file, "LS-DYNA k file");
  // TODO:more file parse supported in further

  std::string output_file;
  app.add_option("-o,--output", output_file, "save ast to file");
  app.add_flag("-d,--debug",
               "enable parse debug, will print parse processing to stdout");

  try {
    app.parse(argc, argv);
  } catch (const CLI::ParseError& e) {
    return app.exit(e);
  }

  if (app.count("--k") > 0) {
    file_type = InputFileType::K;
  }

  if (app.count("-d") > 0) {
    CAEParser::RuntimeConfig::ins()._trace_parser = true;
  }

  std::shared_ptr<CAEParser::ASTNode> tree = nullptr;
  CAEParser::NotParsedRange not_parsed_content;
  switch (file_type) {
    case InputFileType::K: {
      auto kparser = K::KParser();
      auto [root, not_parsed] = kparser.parseFile(input_file);
      tree = root;
      not_parsed_content = not_parsed;
      break;
    }
    default:
      break;
  }

  if (!not_parsed_content.empty()) {
    std::cout << not_parsed_content << std::endl;
  }

  if (input_file.empty()) {
    return app.exit(CLI::CallForHelp());
  }
  if (output_file.empty()) {
    std::cout << tree << std::endl;
  } else {
    std::ofstream f(output_file);
    f << tree;
    f.close();
  }

  return 0;
}
