#pragma once

#include <string_view>
#include <tuple>

#include "platform.h"


namespace K {
/**
 * @brief cut options in k card name with option
 *
 * @param str
 * @return std::tuple<std::string_view, std::string_view>
 * first is card name with last option cut off
 * second is the cutted option
 */
CAEPARSER_API std::tuple<std::string_view, std::string_view> cutLastSegment(
    const std::string_view& str);

}  // namespace K
