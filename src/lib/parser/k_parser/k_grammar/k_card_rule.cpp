#include "k_card_rule.h"

#include "k_card_content.h"
#include "special_card_content/airbag_particle.h"
#include "special_card_content/airbag_reference_geometry_content.h"
#include "special_card_content/airbag_shell_reference_geometry_content.h"

namespace K {

/**
 * @note KCardPatternBase will add tail ID/TITLE options as default,
 * so if options end with ID/TITLE can be omitted
 */
std::unordered_map<std::string_view, std::shared_ptr<KCardPatternBase>>
    k_card_rule{
        // ---- AIRBAG ----
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
        {"*AIRBAG_SHELL_REFERENCE_GEOMETRY",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<
                 k_card_content<airbag_shell_reference_geometry_content,
                                title_line, peg::success>>(
                 "*AIRBAG_SHELL_REFERENCE_GEOMETRY", {{"RDT"}}))},
        // ---- ALE ----
        {"*ALE_AMBIENT_HYDROSTATIC",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_AMBIENT_HYDROSTATIC"))},
        {"*ALE_BURN_SWITCH_MMG",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_BURN_SWITCH_MMG"))},
        // TITLE has same card with ID
        {"*ALE_COUPLING_NODAL_CONSTRAINT",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field, id_line>>(
                 "*ALE_COUPLING_NODAL_CONSTRAINT"))},
        // TITLE has same card with ID
        {"*ALE_COUPLING_NODAL_DRAG",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field, id_line>>(
                 "*ALE_COUPLING_NODAL_DRAG"))},
        // TITLE has same card with ID
        {"*ALE_COUPLING_NODAL_PENALTY",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field, id_line>>(
                 "*ALE_COUPLING_NODAL_PENALTY"))},
        {"*ALE_COUPLING_RIGID_BODY",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_COUPLING_RIGID_BODY"))},
        {"*ALE_ESSENTIAL_BOUNDARY",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_ESSENTIAL_BOUNDARY"))},
        // TITLE has same card with ID
        {"*ALE_FAIL_SWITCH_MMG",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field, id_line>>(
                 "*ALE_FAIL_SWITCH_MMG"))},
        {"*ALE_FRAGMENTATION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_FRAGMENTATION"))},
        {"*ALE_FSI_PROJECTION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_FSI_PROJECTION"))},
        // TITLE has same card with ID
        {"*ALE_FSI_SWITCH_MMG",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field, id_line>>(
                 "*ALE_FSI_SWITCH_MMG"))},
        // TODO:ALE_FSI_TO_LOAD_NODE
        {"*ALE_INJECTION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_INJECTION"))},
        {"*ALE_MAPPING",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_MAPPING"))},
        {"*ALE_MAPPING_FROM_LAGRANGIAN",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_MAPPING_FROM_LAGRANGIAN"))},
        {"*ALE_MESH_INTERFACE",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_MESH_INTERFACE"))},
        {"*ALE_MULTI-MATERIAL_GROUP",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_MULTI-MATERIAL_GROUP"))},
        {"*ALE_PRESCRIBED_MOTION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_PRESCRIBED_MOTION"))},
        {"*ALE_REFERENCE_SYSTEM_CURVE",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_REFERENCE_SYSTEM_CURVE"))},
        {"*ALE_REFERENCE_SYSTEM_GROUP",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_REFERENCE_SYSTEM_GROUP"))},
        {"*ALE_REFERENCE_SYSTEM_NODE",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_REFERENCE_SYSTEM_NODE"))},
        {"*ALE_REFERENCE_SYSTEM_SWITCH",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_REFERENCE_SYSTEM_SWITCH"))},
        {"*ALE_SMOOTHING",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_SMOOTHING"))},
        {"*ALE_STRUCTURED_FSI",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field, id_line>>(
                 "*ALE_STRUCTURED_FSI"))},
        {"*ALE_STRUCTURED_MESH",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_STRUCTURED_MESH"))},
        //  TODO:ALE_STRUCTURED_MESH_CONTROL_POINTS
        {"*ALE_STRUCTURED_MESH_JOIN",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_STRUCTURED_MESH_JOIN"))},
        {"*ALE_STRUCTURED_MESH_MOTION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_STRUCTURED_MESH_MOTION"))},
        {"*ALE_STRUCTURED_MESH_REFINE",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_STRUCTURED_MESH_REFINE", {{"REGION"}}))},
        {"*ALE_STRUCTURED_MESH_TRIM",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_STRUCTURED_MESH_TRIM"))},
        {"*ALE_STRUCTURED_MESH_VOLUME_FILLING",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_STRUCTURED_MESH_VOLUME_FILLING"))},
        {"*ALE_STRUCTURED_MULTI-MATERIAL_GROUP",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_STRUCTURED_MULTI-MATERIAL_GROUP",
                 {{"PLNEPS", "AXISYM"}}))},
        {"*ALE_SWITCH_MMG",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_SWITCH_MMG"))},
        {"*ALE_TANK_TEST",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_TANK_TEST"))},
        {"*ALE_UP_SWITCH",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*ALE_UP_SWITCH"))},
        {"*CONTROL_TERMINATION",
         std::shared_ptr<KCardPatternBase>(
             new KCardPattern<k_card_content<k_card_content_8_field>>(
                 "*CONTROL_TERMINATION"))}};
}  // namespace K