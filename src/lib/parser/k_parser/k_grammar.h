#pragma once

#include "k_grammar/k_card.h"
#include "k_grammar/k_trival_grammar.h"
#include "parser/base_grammar/ikeyword.h"
#include "parser/control_tag.h"
#include "tao/pegtl.hpp"


namespace K {
namespace peg = tao::pegtl;

struct k_grammar
    : peg::seq<peg::pad<peg::sor<empty_line, comment_line>, k_keyword>,
               peg::until<peg::sor<k_end, peg::eolf>, k_card, comment_line,
                          empty_line, not_parsed>> {};

}  // namespace K