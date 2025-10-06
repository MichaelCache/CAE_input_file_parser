#include "ast.h"

namespace CAEParser {

void ASTNode::setType(const std::type_index& t) { _node_type = t; }

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

ASTNode::const_iterator ASTNode::begin() const { return _children.begin(); }
ASTNode::const_iterator ASTNode::end() const { return _children.end(); }

size_t ASTNode::childreSize() const { return _children.size(); }

std::ostream& operator<<(std::ostream& os,
                         const std::shared_ptr<ASTNode> node) {
  node->streamOut(os, 0);
  return os;
}

void ASTNode::streamOut(std::ostream& os, uint64_t indent_level) const {
  os << std::string(indent_level * 2, ' ');
  if (std::type_index(typeid(void)) == _node_type && indent_level == 0) {
    os << "ROOT";
  } else {
    os << demangle_type_index(_node_type);
  }
  os << "(" << _start._line << ":" << _start._colum << "-" << _end._line << ":"
     << _end._colum << ")" << ":" << _content;
  if (!_children.empty()) {
    for (auto&& c : _children) {
      os << "\n";
      c->streamOut(os, indent_level + 1);
    }
  }
}
}  // namespace CAEParser
