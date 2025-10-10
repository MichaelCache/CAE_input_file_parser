#pragma once

#include "tao/pegtl.hpp"

namespace CAEParser {
namespace peg = tao::pegtl;

struct k_grammar : peg::until<peg::eolf> {};

}  // namespace CAEParser