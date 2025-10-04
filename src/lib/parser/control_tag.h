#pragma once

namespace CAEParser {
// tag to mark save current grammar to ast node
struct astnode_tag {};
// tag to mark save current grammar and matched content to ast node
struct savenode_tag : astnode_tag {};
// mark not supported part
struct not_parsed {};
}  // namespace CAEParser
