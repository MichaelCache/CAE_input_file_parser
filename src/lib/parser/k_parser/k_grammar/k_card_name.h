#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "k_card_pattern.h"

namespace K {
std::unordered_map<std::string, std::shared_ptr<KCardPatternBase> > k_card_name;

}  // namespace K
