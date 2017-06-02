/*INSERTION_TRADOIL*/
/**********************************************************************************************************************/
/* !Layer           : MCAL                                                                                            */
/* !Component       : PWD                                                                                             */
/* !Description     : Test Code For PWD Component                                                                     */
/*                                                                                                                    */
/* !File            : DONNEE_PWD_TXT.TPL                                                                              */
/* !Description     : Configuration files                                                                             */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
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

'Nom_donnée|Type|Nom_module|Public|Nb_lignes|Nb_colonnes|Label_père|Offset|Masque_accès|Affichage|Unité|Fonction_transfert_ades|Coefficient_a|Coefficient_b|Groupe|Groupe_1|Groupe_2|Alias_1|Alias_2|Genre|Variable_indice_ligne|Variable_indice_colonne|Fonction_transfert_ligne|Fonction_transfert_colonne|Table_breakpoint_ligne|Table_breakpoint_colonne|Référence_spécification|Recuperable|Modifiable|Fournisseur|Responsable|Valeurs|Visualisable_ADES|Donnée_a_supprimer|Validation|Commentaires|Volatile|MinDecValue|MaxDecValue|MinPhysValue|MaxPhysValue|Def_Eval|MemSec
PWD_bEnableAll|boolean|PWD|0|0|0|PWD_bEnableAll|0|0|Phys|bool|2|0||Commandes|Commandes||PWD_bEnableAll||1||||||||0|1||||1|0|0||0|||||0||
PWD_u16UpdateDisable|uint16|PWD|0|0|0|PWD_u16UpdateDisable|0|0|Phys|-|0|||MCAL|MCAL||PWD_u16UpdateDisable||1||||||||0|1||||1|0|0||0|||||0|
`
PWD_CHANNEL AS FunctionalName CONCATE
{
   WHERE (FunctionalName == "")
   {
'PWD_kudtTout_`FunctionalName'|uint32|PWD|1|0|0|PWD_kudtTout_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.TIMEOUT_PARAM_RESOL_IN_NS'/1000000|0|MCAL|MCAL||PWD_kudtTout_`FunctionalName'||2|||||||NONE|1|1||||1|0|0|Initial value of timeout of DF PLUG PWM channel|0|||||0
PWD_udtDuty_`FunctionalName'|PWD_tudtDutyCycle|PWD|1|0|0|PWD_udtDuty_`FunctionalName'|0|0|Phys|%|1|100/`FunctionalName.DUTY_CYCLE_DECIMAL_VALUE_OF_100_PERCENT'|0|MCAL|MCAL||PWD_udtDuty_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0
PWD_udtActiveDuration_`FunctionalName'|PWD_tudtActiveDuration|PWD|1|0|0|PWD_udtActiveDuration_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.DESIRED_PERIOD_RESOL_IN_NS'/1000000|0|MCAL||PWD_udtActiveDuration_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0
PWD_udtPer_`FunctionalName'|PWD_tudtPeriod|PWD|1|0|0|PWD_udtPer_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.DESIRED_PERIOD_RESOL_IN_NS'/1000000|0|MCAL|MCAL||PWD_udtPer_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0
PWD_udtTout_`FunctionalName'|uint32|PWD|1|0|0|PWD_udtTout_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.TIMEOUT_PARAM_RESOL_IN_NS'/1000000|0|MCAL|MCAL||PWD_udtTout_`FunctionalName'||1|||||||NONE|0|1||||1|0|0|Value of timeout of DF PLUG PWM channel|0|||||0
PWD_udtToutSt_`FunctionalName'|Std_ReturnType|PWD|1|0|0|PWD_udtToutSt_`FunctionalName'|0|0|Phys|-|0|||MCAL|MCAL||PWD_udtToutSt_`FunctionalName'||1|||||||NONE|0|1||||1|0|0|Status of Write timeout API for DF PLUG PWM Channel|0|||||0
PWD_bEna_`FunctionalName'|boolean|PWD|0|0|0|PWD_bEna_`FunctionalName'|0|0|Phys|bool|2|0||Commandes|Commandes||PWD_bEna_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0|
`
   }
   WHERE (FunctionalName != "")
   {
'PWD_kudtTout_`FunctionalName'|uint32|PWD|1|0|0|PWD_kudtTout_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.TIMEOUT_PARAM_RESOL_IN_NS'/1000000|0|MCAL|MCAL||PWD_kudtTout_`FunctionalName'||2|||||||NONE|1|1||||1|0|0|Initial value of timeout of DF PLUG PWM channel|0|||||0
PWD_udtDuty_`FunctionalName'|PWD_tudtDutyCycle|PWD|1|0|0|PWD_udtDuty_`FunctionalName'|0|0|Phys|%|1|100/`FunctionalName.DUTY_CYCLE_DECIMAL_VALUE_OF_100_PERCENT'|0|MCAL|MCAL||PWD_udtDuty_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0
PWD_udtActiveDuration_`FunctionalName'|PWD_tudtActiveDuration|PWD|1|0|0|PWD_udtActiveDuration_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.DESIRED_PERIOD_RESOL_IN_NS'/1000000|0|MCAL||PWD_udtActiveDuration_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0
PWD_udtPer_`FunctionalName'|PWD_tudtPeriod|PWD|1|0|0|PWD_udtPer_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.DESIRED_PERIOD_RESOL_IN_NS'/1000000|0|MCAL|MCAL||PWD_udtPer_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0
PWD_udtTout_`FunctionalName'|uint32|PWD|1|0|0|PWD_udtTout_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName.TIMEOUT_PARAM_RESOL_IN_NS'/1000000|0|MCAL|MCAL||PWD_udtTout_`FunctionalName'||1|||||||NONE|0|1||||1|0|0|Value of timeout of DF PLUG PWM channel|0|||||0
PWD_udtToutSt_`FunctionalName'|Std_ReturnType|PWD|1|0|0|PWD_udtToutSt_`FunctionalName'|0|0|Phys|-|0|||MCAL|MCAL||PWD_udtToutSt_`FunctionalName'||1|||||||NONE|0|1||||1|0|0|Status of Write timeout API for DF PLUG PWM Channel|0|||||0
PWD_bEna_`FunctionalName'|boolean|PWD|0|0|0|PWD_bEna_`FunctionalName'|0|0|Phys|bool|2|0||Commandes|Commandes||PWD_bEna_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0|
PWD_bFirstPerOccured_`FunctionalName'|boolean|PWD|0|0|0|PWD_bFirstPerOccured_`FunctionalName'|0|0|Phys|bool|2|0||Commandes|Commandes||PWD_bFirstPerOccured_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0|
PWD_bCurrentLvlIsActive_`FunctionalName'|boolean|PWD|0|0|0|PWD_bCurrentLvlIsActive_`FunctionalName'|0|0|Phys|bool|2|0||Commandes|Commandes||PWD_bCurrentLvlIsActive_`FunctionalName'||1||||||||0|1||||1|0|0||0|||||0|
PWD_udtToutRloadVal_`FunctionalName'|uint32|PWD|1|0|0|PWD_udtToutRloadVal_`FunctionalName'|0|0|Phys|ms|1|`FunctionalName'|0|MCAL|MCAL||PWD_udtToutRloadVal_`FunctionalName'||1|||||||NONE|0|1||||1|0|0|Value of timeout of DF PLUG PWM channel|0|||||0
`
   }
}

/*---------------------------------------------------- end of file ---------------------------------------------------*/