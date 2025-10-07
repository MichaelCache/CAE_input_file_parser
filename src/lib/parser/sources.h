#pragma once
#include <memory>
#include <string>
#include <vector>

#include "platform.h"

namespace CAEParser {
class CAEPARSER_API Sources {
 public:
  static Sources& ins();
  void reset();
  void add(const std::string&);
  std::shared_ptr<std::string> current() const;

 private:
  Sources(/* args */) = default;
  ~Sources() = default;

  // use std::shared_ptr to hold std::string
  // share with astnode, reduce memory uesage
  // auto manage memory even _sources_file.clear()
  std::vector<std::shared_ptr<std::string>> _sources_file;
  std::shared_ptr<std::string> _current{nullptr};
};

}  // namespace CAEParser
