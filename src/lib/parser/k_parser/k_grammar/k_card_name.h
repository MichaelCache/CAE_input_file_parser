#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "k_card_pattern.h"
#include "platform.h"

namespace K {

extern CAEPARSER_API
    std::unordered_map<std::string_view, std::shared_ptr<KCardPatternBase>>
        k_card_name;

}  // namespace K
