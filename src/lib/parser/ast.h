#pragma once

#include <memory>
#include <ostream>
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
  /**
   * @brief get node's parent, maybe nullptr
   *
   * @return std::shared_ptr<ASTNode>
   */
  std::shared_ptr<ASTNode> parent() const;

  // iterator for children
  iterator begin();
  iterator end();

  const_iterator begin() const;
  const_iterator end() const;

  size_t childreSize() const;

  /**
   * @brief check node grammar type
   *
   * @tparam T
   * @return true
   * @return false
   */
  template <typename T>
  bool is() const {
    return typeid(T) == _node_type;
  }

  CAEPARSER_API friend std::ostream& operator<<(
      std::ostream& os, const std::shared_ptr<ASTNode> node);

 public:
  void streamOut(std::ostream& os, uint64_t indent_level) const;

  std::string _content;
  Position _start;
  Position _end;
  std::string_view _source_file;

 private:
  std::type_index _node_type{typeid(void)};
  std::vector<std::shared_ptr<ASTNode>> _children;
  std::weak_ptr<ASTNode> _parent;
};

}  // namespace CAEParser
