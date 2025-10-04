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

std::string ASTNode::toString(int depth) const { return ""; }

}  // namespace CAEParser
