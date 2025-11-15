#include "ast.h"

namespace CAEParser {

void ASTNode::setType(const std::type_index& t) { _node_type = t; }

std::type_index ASTNode::type() const { return _node_type; }

void ASTNode::addChildren(std::shared_ptr<ASTNode> node) {
  _children.push_back(node);
  node->_parent = weak_from_this();
}

std::shared_ptr<ASTNode> ASTNode::parent() const {
  if (_parent.expired()) {
    return nullptr;
  } else {
    return _parent.lock();
  }
}

ASTNode::iterator ASTNode::begin() { return _children.begin(); }
ASTNode::iterator ASTNode::end() { return _children.end(); }

ASTNode::reverse_iterator ASTNode::rbegin() { return _children.rbegin(); }
ASTNode::reverse_iterator ASTNode::rend() { return _children.rend(); }

ASTNode::const_iterator ASTNode::begin() const { return _children.begin(); }
ASTNode::const_iterator ASTNode::end() const { return _children.end(); }

ASTNode::const_reverse_iterator ASTNode::rbegin() const {
  return _children.rbegin();
}
ASTNode::const_reverse_iterator ASTNode::rend() const {
  return _children.rend();
}

bool ASTNode::childEmpty() const { return _children.empty(); }
size_t ASTNode::childreSize() const { return _children.size(); }

std::shared_ptr<ASTNode> ASTNode::at(uint64_t idx) const {
  return _children.at(idx);
}

// ----------------------------------------------------------------------------
void streamOutHelper(std::ostream& os, const std::shared_ptr<ASTNode> node,
                     uint64_t indent_level) {
  os << std::string(indent_level * 2, ' ');
  auto type_id = node->type();
  if (std::type_index(typeid(void)) == type_id && indent_level == 0) {
    os << "ROOT";
  } else {
    os << demangle_type_index(type_id);
  }
  os << "(" << node->_start._line << ":" << node->_start._colum << "-"
     << node->_end._line << ":" << node->_end._colum << ")" << ":"
     << node->_content;
  for (auto&& c : *node) {
    os << "\n";
    streamOutHelper(os, c, indent_level + 1);
  }
}
std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<ASTNode> node) {
  streamOutHelper(os, node, 0);
  return os;
}

}  // namespace CAEParser
