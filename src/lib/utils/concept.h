#pragma once

#include <type_traits>

namespace CAEParser {

template <typename T, typename Base>
concept DerivedFromBase = std::is_base_of_v<Base, T>;
}  // namespace CAEParser
