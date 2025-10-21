#include "k_card_pattern.h"
namespace K {
KCardPatternBase::KCardPatternBase(const std::string_view& pattern)
    : _pattern(pattern.data()) {}

}  // namespace K