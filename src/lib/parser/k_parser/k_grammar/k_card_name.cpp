#include "k_card_name.h"

#include "k_card_content.h"

namespace K {

std::unordered_map<std::string_view, std::shared_ptr<KCardPatternBase>>
    k_card_name{{"*AIRBAG",
                 std::make_shared<KCardPattern<k_card_content_8_field>>(
                     "\\*AIRBAG(_SIMPLE_PRESSURE_VOLUME|_SIMPLE_AIRBAG_MODEL|_"
                     "ADIABATIC_GAS_MODEL|_WANG_NEFSKE|_WANG_NEFSKE_JETTING|_"
                     "WANG_NEFSKE_MULTIPLE_JETTING|_LOAD_CURVE|_LINEAR_FLUID|_"
                     "HYBRID|_HYBRID_JETTING|_HYBRID_CHEMKIN|_FLUID_AND_GAS)(_"
                     "POP){0,1}(_CM){0,1}(_ID){0,1}")}};
}  // namespace K