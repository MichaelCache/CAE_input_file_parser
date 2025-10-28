#pragma once

#include "parser/base_grammar/ikeyword.h"
#include "parser/control_tag.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

struct not_parsed : peg::any, CAEParser::not_parsed_tag {};
struct empty_line : peg::seq<peg::bol, peg::star<peg::blank>, peg::eolf> {};
struct comment : peg::seq<peg::one<'$'>, peg::until<peg::at<peg::eolf>>> {};
struct comment_line : peg::seq<peg::bol, comment, peg::eolf> {};

struct k_keyword : peg::seq<peg::bol, EXTEND_PEGTL_IKEYWORD("*KEYWORD"),
                            peg::until<peg::eolf>> {};
struct k_end
    : peg::seq<peg::bol, EXTEND_PEGTL_IKEYWORD("*END"), peg::until<peg::eolf>> {
};

}  // namespace K