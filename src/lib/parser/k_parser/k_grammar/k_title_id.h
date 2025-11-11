#pragma once

#include "k_size_field.h"
#include "parser/base_grammar/int_num.h"
#include "parser/control_tag.h"
#include "parser/k_parser/k_control_tag.h"
#include "tao/pegtl.hpp"

namespace K {
namespace peg = tao::pegtl;

struct title : public CAEParser::savenode_tag, public trim_tag {
  using rule_t = title;
  using subs_t = peg::empty_list;

  template <peg::apply_mode A, peg::rewind_mode M,
            template <typename...> class Action,
            template <typename...> class Control, typename ParseInput,
            typename ParseState, typename... States>
  [[nodiscard]] static bool match(ParseInput& in, ParseState& state,
                                  States&&... st) {
    auto cur = in.current();
    // get cardname line
    while (cur != in.end()) {
      if (*cur == '\n' || *cur == '\r') {
        break;
      }
      cur++;
    }
    // get title line
    std::string_view title_sv(in.current(), cur);
    // title can be emtpy
    in.bump(title_sv.size());
    return true;
  }
};

struct title_line
    : peg::seq<k_size_field<title, 80>, peg::star<peg::blank>, peg::eolf>,
      CAEParser::astnode_tag {};

struct id : public CAEParser::unsign_int_num, public CAEParser::savenode_tag {};
struct heading : public title {};

struct id_line : peg::seq<k_size_field<id, 10>, k_size_field<heading, 70>,
                          peg::star<peg::blank>, peg::eolf>,
                 CAEParser::astnode_tag {};
}  // namespace K