#include "k_card_pattern.h"

#include <ranges>

namespace K {

KOptions::KOptions(const std::initializer_list<std::string_view>& options,
                   bool required) {
  if (options.size()) {
    regex_str += "(";
    for (auto&& op : options) {
      regex_str += "_" + std::string(op) + "|";
    }
    regex_str.pop_back();
    regex_str += ")";
    if (!required) {
      regex_str += "{0,1}";
    }
  }
}

KOptions::KOptions(const std::initializer_list<std::string_view>& options,
                   const std::string_view& repeat) {
  if (options.size()) {
    regex_str += "(";
    for (auto&& op : options) {
      regex_str += "_" + std::string(op) + "|";
    }
    regex_str.pop_back();
    regex_str += ")" + std::string(repeat);
  }
}

KCardPatternBase::KCardPatternBase(
    const std::string_view& card_name,
    const std::initializer_list<KOptions>& options) {
  std::string regex;
  if (card_name.front() == '*') {
    regex += "\\";
  }
  regex += card_name;

  for (auto&& op : options) {
    regex += op.regex_str;
  }
  _pattern = regex;
}
}  // namespace K