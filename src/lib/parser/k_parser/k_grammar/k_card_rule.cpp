#include "k_card_rule.h"

#include "k_card_content.h"

namespace K {

std::unordered_map<std::string_view, std::shared_ptr<KCardPatternBase>>
    k_card_rule{
        {"*AIRBAG",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content_8_field>(
                 "*AIRBAG",
                 {KOptions(
                      {"SIMPLE_PRESSURE_VOLUME", "SIMPLE_AIRBAG_MODEL",
                       "ADIABATIC_GAS_MODEL", "WANG_NEFSKE",
                       "WANG_NEFSKE_JETTING", "WANG_NEFSKE_MULTIPLE_JETTING",
                       "LOAD_CURVE", "LINEAR_FLUID", "HYBRID", "HYBRID_JETTING",
                       "HYBRID_CHEMKIN", "FLUID_AND_GAS"},
                      true),
                  {"POP"},
                  {" CM "},
                  {" ID "}}))}};
}  // namespace K