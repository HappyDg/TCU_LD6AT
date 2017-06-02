/*INSERTION_TRADOIL*/
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer           : BSW                                                                                             */
/*                                                                                                                    */
/* !Component       : HAL                                                                                             */
/* !Description     : IOHAL Configuration                                                                             */
/*                                                                                                                    */
/* !File            : donnee_IOHAL_txt.tpl                                                                            */
/*                                                                                                                    */
/* !Scope           : Public                                                                                          */
/*                                                                                                                    */
/* !Target          : Genecode Tool                                                                                   */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : Genecode                                                                                        */
/*                                                                                                                    */
/* COPYRIGHT 2013 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_Onduleur_Gen1_Michelin/LOG/60_ComponentArchive/Archives                                        $*/
/* $Revision::   1.1      $$Author::   vbecquet       $$Date::   10 Jun 2010                                         $*/
/**********************************************************************************************************************/
'Nom_donnée|Type|Nom_module|Public|Nb_lignes|Nb_colonnes|Label_père|Offset|Masque_accès|Affichage|Unité|Fonction_transfert_ades|Coefficient_a|Coefficient_b|Groupe|Groupe_1|Groupe_2|Alias_1|Alias_2|Genre|Variable_indice_ligne|Variable_indice_colonne|Fonction_transfert_ligne|Fonction_transfert_colonne|Table_breakpoint_ligne|Table_breakpoint_colonne|Référence_spécification|Recuperable|Modifiable|Fournisseur|Responsable|Valeurs|Visualisable_ADES|Donnée_a_supprimer|Validation|Commentaires|Volatile|MinDecValue|MaxDecValue|MinPhysValue|MaxPhysValue|Def_Eval|MemSec
`
IOHAL_CHANNEL AS ChannelName WHERE(DISPLAY = ON) ORDERBY(INDEX) CONCATE
{
   WHERE(LINKTO{MCAL_READ_FUNCTION_NAME} != "")
   {
      "IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarRead_" ChannelName "|" LINKTO{RETURN_TYP.TYPE_NAME} "|IOHAL|1|0|0|IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarRead_" ChannelName "|0|0|Phys|" DISPLAY.UNIT "|1|" DISPLAY.COEFA "|" DISPLAY.COEFB "|Acquisitions|Acquisitions||IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarRead_" ChannelName "||1|||||||NONE|0|0||||1|0|0||0||||||
"
   }
   WHERE((DIRECTION = OUTPUT) and (LINKTO{MCAL_WRITE_FUNCTION_NAME} != ""))
   {
      "IOHAL_" LINKTO{PARAM_TYP.TYPE_ABBR} "VarWrite_" ChannelName "|" LINKTO{PARAM_TYP.TYPE_NAME} "|IOHAL|1|0|0|IOHAL_" LINKTO{PARAM_TYP.TYPE_ABBR} "VarWrite_" ChannelName "|0|0|Phys|" DISPLAY.UNIT "|1|" DISPLAY.COEFA "|" DISPLAY.COEFB "|Acquisitions|Acquisitions||IOHAL_" LINKTO{PARAM_TYP.TYPE_ABBR} "VarWrite_" ChannelName "||1|||||||NONE|0|0||||1|0|0||0||||||
"
   }
}

/*--------------------------------------------------- end of file ----------------------------------------------------*/
