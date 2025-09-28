#pragma once

#include <memory>
#include <string>
#include <typeindex>
#include <vector>

#include "platform.h"
#include "position.h"

namespace CAEParser {

/**
 * @brief Abstract Syntax Tree Node
 *
 */
class CAEPARSER_API ASTNode : public std::enable_shared_from_this<ASTNode> {
 public:
  ASTNode(/* args */) = default;
  ~ASTNode() = default;

  using iterator = typename std::vector<std::shared_ptr<ASTNode>>::iterator;
  using const_iterator =
      typename std::vector<std::shared_ptr<ASTNode>>::const_iterator;

  void setType(const std::type_index&);
  void addChildren(std::shared_ptr<ASTNode> node);
  std::shared_ptr<ASTNode> parent() const;

  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  template <typename T>
  bool is() const {
    return typeid(T) == _node_type;
  }

  /**
   * @brief recurse convert ast to string
   *
   * @param depth recurse depth level, -1 means recursly dump all
   * @return std::string
   */
  std::string toString(int depth = -1) const;

 public:
  std::string _content;
  Position _start;
  Position _end;

 private:
  std::type_index _node_type{typeid(void)};
  std::vector<std::shared_ptr<ASTNode>> _children;
  std::weak_ptr<ASTNode> _parent;
};

}  // namespace CAEParser
