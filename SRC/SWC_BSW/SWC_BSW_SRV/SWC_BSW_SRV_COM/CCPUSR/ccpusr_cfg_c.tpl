/*INSERTION_TRADOIL*/
/******************************************************************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCPUSR_CFG_C                                            */
/* !Description     : Template of CCP Configuration C file (user part)        */
/*                                                                            */
/* !File            : CCPUSR_CFG_C.TPL                                        */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : Genecode Tool                                           */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : OIL                                                     */
/*                                                                            */
/* COPYRIGHT 2009 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::                                                               $*/
/* $Author::                                          $$Date::               $*/
/******************************************************************************/
'/***************************** <AUTO_FILE_HEADER> *****************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCPUSR_CFG                                              */
/* !Description     : Configuration of the user part                          */
/*                                                                            */
/* !File            : CCPUSR_CFG.C                                            */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2009 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/**************************** </AUTO_FILE_HEADER> *****************************/
/* PVCS Information                                                           */
/* $Arc`'hive::                                                                $*/
/* $Rev`'ision::                                                               $*/
/* $Aut`'hor::                                          $$Da`'te::               $*/
/******************************************************************************/
/* Generated on `Date()' by Genecode `Version()'                       */
/******************************************************************************/

#include "CCP.h"
#include "CCPUSR_Cfg.h"
#include "ComStack_Types.h"
#include "CanIf_Cbk.h"
`
CCP CONCATE
{
   INCLUDE_FILES AS incFile ONEPERLINE
   {
      '#include "` incFile '"`
   }
}
'
/******************************************************************************/
/* CONSTANTS DEFINITION                                                       */
/******************************************************************************/
#define CCP_START_SEC_CONST_UNSPECIFIED
#include "Ccp_MemMap.h"

`
CCP WHERE (DAQ_LIST_SERVICES == TRUE) ONEPERLINE
{
   "/* !Comment: CAN ID for all DAQ lists                                         */
"  "CONST(PduIdType, CCP_CONST) CCPUSR_kaudtDaqMsgID[CCP_u8DAQ_NO_LISTS] =
"  "{
"  .DAQ_LIST ORDERBY(FileOrder()) CONCATE
   {
      WHERE (counter() > 0)
      {
         ",
"
      }
      "   " CANIF_TX_ID
   }
   "
"  "};

/* !Comment: CAN ID for all DAQ lists for DEVAID                                        */
"  "CONST(PduIdType, CCP_CONST) CCPUSR_kaudtDevaidDaqMsgID[CCP_u8DAQ_NO_LISTS] =
"  "{
"  .DAQ_LIST ORDERBY(FileOrder()) CONCATE
   {
      WHERE (counter() > 0)
      {
         ",
"
      }
      "   " CANIF_DEVAID_TX_ID
   }
   "
"  "};"

}
'
const uint32 CCPUSR_kau32WritableMemoryZone[2*CCPUSR_NB_WRITABLE_ZONE] =
{
`
CCP_WRITABLE_MEMORY_ZONE AS Def_Zones ONEPERLINE
{
   "   " ADDRESS_START "," ADDRESS_STOP ", /* " Def_Zones " */"
}
'};

const uint32 CCPUSR_kau32ReadOnlyMemoryZone[2*CCPUSR_NB_READ_ONLY_ZONE] =
{
`
CCP_READ_ONLY_MEMORY_ZONE AS Def_Zones ONEPERLINE
{
   "   " ADDRESS_START "," ADDRESS_STOP ", /* " Def_Zones " */"
}
'};

#define CCP_STOP_SEC_CONST_UNSPECIFIED
#include "Ccp_MemMap.h"

#define CCP_START_SEC_CODE
#include "Ccp_MemMap.h"

/**********************************************************************************************************************/
/* !Description: Called by CanIf on CCP DAQ List frame transmission. We must send the next DAQ List frame             */
/**********************************************************************************************************************/

`
CCP WHERE (DAQ_LIST_SERVICES == TRUE) ONEPERLINE
{
   .DAQ_LIST AS DaqName ORDERBY(FileOrder()) CONCATE
   {
      "void CCP_vidUsrTxConfirmation_" DaqName " (void)
"     "{
"     "   CCP_vidDaqListTxMgr(CCP_u8DAQ_LST_" DaqName ");
"     "}

"
   }
}
'

#define CCP_STOP_SEC_CODE
#include "Ccp_MemMap.h"


/*-------------------------------- end of file -------------------------------*/