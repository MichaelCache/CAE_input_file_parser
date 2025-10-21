#pragma once

#include "k_card_field.h"
#include "k_trival_grammar.h"
#include "size_field.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

struct k_card_8_field_line
    : peg::seq<peg::rep<10, size_field<k_card_field, 8>>,
               peg::sor<comment, peg::star<peg::space>>, peg::eolf> {};

struct k_card_10_field_line
    : peg::seq<peg::rep<8, size_field<k_card_field, 10>>,
               peg::sor<comment, peg::star<peg::space>>, peg::eolf> {};

struct k_card_content_8_field
    : peg::until<k_card_end, peg::sor<k_card_8_field_line, comment_line>> {};

struct k_card_content_10_field
    : peg::until<k_card_end, peg::sor<k_card_10_field_line, comment_line>> {};

}  // namespace K
