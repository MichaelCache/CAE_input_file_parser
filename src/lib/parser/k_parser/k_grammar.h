#pragma once

#include "k_grammar/k_card.h"
#include "k_grammar/k_trival_grammar.h"
#include "parser/base_grammar/ikeyword.h"
#include "parser/control_tag.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

struct k_grammar
    : peg::seq<
          peg::pad<k_keyword, peg::sor<comment_line, empty_line>>,
          peg::pad<k_title_card, peg::sor<comment_line, empty_line>>,
          peg::until<peg::sor<k_end, peg::eof>,
                     peg::sor<k_card, comment_line, empty_line, not_parsed>>> {
};

}  // namespace K