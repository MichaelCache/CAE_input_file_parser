#include "k_card_pattern.h"

#include <ranges>

namespace K {

KOptions::KOptions(const std::initializer_list<std::string_view>& options,
                   bool required) {
  if (options.size()) {
    _regex_str += "(";
    for (auto&& op : options) {
      _regex_str += "_" + std::string(op) + "|";
    }
    _regex_str.pop_back();
    _regex_str += ")";
    if (!required) {
      _regex_str += "{0,1}";
    }
  }
}

KOptions::KOptions(const std::initializer_list<std::string_view>& options,
                   const std::string_view& repeat) {
  if (options.size()) {
    _regex_str += "(";
    for (auto&& op : options) {
      _regex_str += "_" + std::string(op) + "|";
    }
    _regex_str.pop_back();
    _regex_str += ")" + std::string(repeat);
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
    regex += op._regex_str;
  }
  _pattern = regex;
}

bool KCardPatternBase::match(const std::string& s) {
  if (_card_name_option_cache != s) {
    bool res = std::regex_match(s, _match_result_cache, _pattern);
    if (res) {
      _card_name_option_cache = s;
      return true;
    } else {
      return false;
    }
  } else {
    // s == _card_name_option_cache and _card_name_option_cache not empty
    return !_card_name_option_cache.empty();
  }
}

std::vector<std::string> KCardPatternBase::options(const std::string& s) {
  std::vector<std::string> options;
  if (_card_name_option_cache != s) {
    std::regex_match(s, _match_result_cache, _pattern);
    _card_name_option_cache = s;
  }
  // index start from 1, jump over the whole match string
  for (size_t i = 1; i < _match_result_cache.size(); i++) {
    auto ss = _match_result_cache[i];
    if (ss.matched) {
      options.push_back(ss);
    }
  }
  return options;
}
}  // namespace K