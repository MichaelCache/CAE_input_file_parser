#include "k_card_rule.h"

#include "k_card_content.h"
#include "special_card_content/airbag_particle.h"
#include "special_card_content/airbag_reference_geometry_content.h"

namespace K {

/**
 * @note KCardPatternBase will add tail ID/TITLE options as default,
 * so if options end with ID/TITLE can be omitted
 */
std::unordered_map<std::string_view, std::shared_ptr<KCardPatternBase>>
    k_card_rule{
        // ---- A ----
        {"*AIRBAG",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*AIRBAG",
                 {KOptions(
                      {"SIMPLE_PRESSURE_VOLUME", "SIMPLE_AIRBAG_MODEL",
                       "ADIABATIC_GAS_MODEL", "WANG_NEFSKE",
                       "WANG_NEFSKE_JETTING", "WANG_NEFSKE_MULTIPLE_JETTING",
                       "LOAD_CURVE", "LINEAR_FLUID", "HYBRID", "HYBRID_JETTING",
                       "HYBRID_CHEMKIN", "FLUID_AND_GAS"},
                      true),
                  {"POP"},
                  {"CM"}}))},
        {"*AIRBAG_ALE",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*AIRBAG_ALE"))},
        {"*AIRBAG_INTERACTION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*AIRBAG_INTERACTION"))},
        // for AIRBAG_PARTICLE, ID/TITLE option is same
        {"*AIRBAG_PARTICLE",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<
                 k_card_content<airbag_particle, peg::success, peg::success>>(
                 "*AIRBAG_PARTICLE", {{"MPP"},
                                      {"DECOMPOSITION"},
                                      {"ID", "TITLE"},
                                      {"MOLEFRACTION", "INFLATION", "JET"},
                                      {"SEGMENT"},
                                      {"TIME"}}))},
        {"*AIRBAG_REFERENCE_GEOMETRY",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<airbag_reference_geometry_content,
                                             title_line, peg::success>>(
                 "*AIRBAG_REFERENCE_GEOMETRY", {{"BIRTH"}, {"RDT"}}))},
        {"*CONTROL_TERMINATION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*CONTROL_TERMINATION"))}};
}  // namespace K