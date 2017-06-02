/*INSERTION_TRADOIL*/
/**********************************************************************************************************************/
/* !Layer           : SRVL                                                                                            */
/* !Component       : RTMCLD                                                                                          */
/* !Description     : Real time measurement of CPU load                                                               */
/*                                                                                                                    */
/* !File            : RTMCLD_DONNEE_TXT.TPL                                                                           */
/* !Description     : configurations of the RTMCLD component                                                          */
/*                                                                                                                    */
/* !Reference       : PTS_DOC_5385380                                                                                 */
/*                                                                                                                    */
/* Coding language  : OIL                                                                                             */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/


'Nom_donnée|Type|Nom_module|Public|Nb_lignes|Nb_colonnes|Label_père|Offset|Masque_accès|Affichage|Unité|Fonction_transfert_ades|Coefficient_a|Coefficient_b|Groupe|Groupe_1|Groupe_2|Alias_1|Alias_2|Genre|Variable_indice_ligne|Variable_indice_colonne|Fonction_transfert_ligne|Fonction_transfert_colonne|Table_breakpoint_ligne|Table_breakpoint_colonne|Référence_spécification|Recuperable|Modifiable|Fournisseur|Responsable|Valeurs|Visualisable_ADES|Donnée_a_supprimer|Validation|Commentaires|Volatile|MinDecValue|MaxDecValue|MinPhysValue|MaxPhysValue|Def_Eval
`
.RTMCLD_CFG WHERE((CPU_LOAD_MEASUREMENT_PERIOD_CONFIG_TYPE = POSTBUILD) or (CPU_LOAD_MEASUREMENT_PERIOD_CONFIG_TYPE = RUNTIME))
{
"RTMCLD_u32Load|uint32|RTMCLD|0|0|0|RTMCLD_u32Load|0|0|Phys|%|1|1/100|0|Miscellaneous|Miscellaneous||RTMCLD_u32Load||4||||||||0|1||||1|0|0||0|||||0
RTMCLD_u32MeasurementPeriodMs|uint32|RTMCLD|0|0|0|RTMCLD_u32MeasurementPeriodMs|0|0|Déci|-||||Miscellaneous|Miscellaneous||RTMCLD_u32MeasurementPeriodMs||4||||||||0|1||||1|0|0||0|||||0
"
}
.RTMCLD_CFG WHERE(CPU_LOAD_MEASUREMENT_PERIOD_CONFIG_TYPE = PREBUILD)
{
"RTMCLD_u32Load|uint32|RTMCLD|0|0|0|RTMCLD_u32Load|0|0|Phys|%|1|-"ENDLESS_LOOP_EXECUTION_TIME_NS"*100/("
     CPU_LOAD_MEASUREMENT_PERIOD_MS
"*1000000)|100|Miscellaneous|Miscellaneous||RTMCLD_u32Load||4||||||||0|1||||1|0|0||0|||||0
"
}
.RTMCLD_CFG AS params WHERE(LOOP_DURATION_MEASURE = ENABLE)
{
"RTMCLD_u32MeasuredValue|uint32|RTMCLD|1|0|0|RTMCLD_u32MeasuredValue|0|0|Déci|-||||Miscellaneous|Miscellaneous||RTMCLD_u32MeasuredValue||4||||||||0|1||||1|0|0||0|||||0
RTMCLD_u8TestDone|uint8|RTMCLD|1|0|0|RTMCLD_u8TestDone|0|0|Déci|-||||Miscellaneous|Miscellaneous||RTMCLD_u8TestDone||4||||||||0|1||||1|0|0||0|||||0
"
}

/*----------------------------------------------------- end of file --------------------------------------------------*/

