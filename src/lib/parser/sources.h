#pragma once
#include <set>
#include <string>

#include "platform.h"

namespace CAEParser {
class CAEPARSER_API Sources {
 public:
  static Sources& ins();
  void reset();
  void add(const std::string&);
  std::string_view current() const;

 private:
  Sources(/* args */) = default;
  ~Sources() = default;

  std::set<std::string> _sources_file;
  std::string_view _current;
};

}  // namespace CAEParser
