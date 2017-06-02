/*INSERTION_TRADOIL*/
/******************************************************************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCP_CFG_C                                               */
/* !Description     : Template of CCP Configuration C file                    */
/*                                                                            */
/* !File            : CCP_CFG_C.TPL                                           */
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
/* !Module          : CCP_CFG                                                 */
/* !Description     : Configuration of the Component                          */
/*                                                                            */
/* !File            : CCP_CFG.C                                               */
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

#include "CCP_Typ.h"
#include "CCP_L.h"
#include "CCP_Cfg.h"

/******************************************************************************/
/* CONSTANTS DEFINITION                                                       */
/******************************************************************************/
#define CCP_START_SEC_CONST_UNSPECIFIED
#include "CCP_MemMap.h"

/* !Comment: list of activated services                                       */
CONST(CCP_tpfudtSrvFcn, CCP_CONST) CCP_kapfudtSrvFcn[CCP_udtNO_SRVS] =
{
   &CCP_udtFcnNotAvl,
   &CCP_udtCnct,
   &CCP_udtSetMta,
   &CCP_udtDnld,
   &CCP_udtUpld,
`
CCP ONEPERLINE
{
   WHERE (TEST_SERVICE == TRUE)
   {
      "   &CCP_udtTest,"
   }
   WHERE (TEST_SERVICE == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP CONCATE
{
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      "   &CCP_udtStrtStop,"
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
'
   &CCP_udtDcnct,
`
CCP ONEPERLINE
{
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      "   &CCP_udtStrtStopAll,"
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP CONCATE
{
   WHERE (CAL_PAGE_SERVICES == TRUE)
   {
      "   &CCP_udtGetAcvCalPage,"
   }
   WHERE (CAL_PAGE_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
'
   &CCP_udtFcnNotAvl,
   &CCP_udtFcnNotAvl,
`
CCP ONEPERLINE
{
   WHERE (SESSION_STATUS_SERVICES == TRUE)
   {
      "   &CCP_udtSetSsnSts,"
   }
   WHERE (SESSION_STATUS_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (SESSION_STATUS_SERVICES == TRUE)
   {
      "   &CCP_udtGetSsnSts,"
   }
   WHERE (SESSION_STATUS_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (CHECKSUM_SERVICE == TRUE)
   {
      "   &CCP_udtBldCks,"
   }
   WHERE (CHECKSUM_SERVICE == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (SHORT_UPLOAD_SERVICE == TRUE)
   {
      "   &CCP_udtShoUpld,"
   }
   WHERE (SHORT_UPLOAD_SERVICE == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (PROGRAM_SERVICES == TRUE)
   {
      "   &CCP_udtClrMem,"
   }
   WHERE (PROGRAM_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (CAL_PAGE_SERVICES == TRUE)
   {
      "   &CCP_udtSelCalPage,"
   }
   WHERE (CAL_PAGE_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (PROTECTION_SERVICES == TRUE)
   {
      "   &CCP_udtGetSeed,"
   }
   WHERE (PROTECTION_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (PROTECTION_SERVICES == TRUE)
   {
      "   &CCP_udtUnlck,"
   }
   WHERE (PROTECTION_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      "   &CCP_udtGetDaqSize,"
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP ONEPERLINE
{
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      "   &CCP_udtSetDaqPtr,"
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP CONCATE
{
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      "   &CCP_udtWrDaqElmCfg,"
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
'
   &CCP_udtExchId,
`
CCP ONEPERLINE
{
   WHERE (PROGRAM_SERVICES == TRUE)
   {
      "   &CCP_udtProg,"
   }
   WHERE (PROGRAM_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP CONCATE
{
   WHERE (MOVE_SERVICE == TRUE)
   {
      "   &CCP_udtMove,"
   }
   WHERE (MOVE_SERVICE == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
'
   &CCP_udtFcnNotAvl,
   &CCP_udtGetCcpVers,
   &CCP_udtFcnNotAvl,
   &CCP_udtFcnNotAvl,
   &CCP_udtFcnNotAvl,
   &CCP_udtFcnNotAvl,
   &CCP_udtFcnNotAvl,
   &CCP_udtFcnNotAvl,
`
CCP ONEPERLINE
{
   WHERE (PROGRAM_SERVICES == TRUE)
   {
      "   &CCP_udtProg6,"
   }
   WHERE (PROGRAM_SERVICES == FALSE)
   {
      "   &CCP_udtFcnNotAvl,"
   }
}
CCP CONCATE
{
   WHERE (DOWNLOAD6_SERVICE == TRUE)
   {
      "   &CCP_udtDnld6"
   }
   WHERE (DOWNLOAD6_SERVICE == FALSE)
   {
      "   &CCP_udtFcnNotAvl"
   }
}
'
};

/* !Comment: device identifier                                                */
`
CCP ONEPERLINE
{
   WHERE (DEVICE_ID == "INTERNAL_UINT8")
   {
      "CONST(uint8, CCP_CONST) CCP_kaudtDevId[1] = " DEVICE_ID{VALUE} ";"
   }
   WHERE (DEVICE_ID == "INTERNAL_UINT16")
   {
      "CONST(uint16, CCP_CONST) CCP_kaudtDevId[1] = " DEVICE_ID{VALUE} ";"
   }
   WHERE (DEVICE_ID == "INTERNAL_UINT32")
   {
      "CONST(uint32, CCP_CONST) CCP_kaudtDevId[1] = " DEVICE_ID{VALUE} ";"
   }
   WHERE (DEVICE_ID == "INTERNAL_ARRAY_UINT8")
   {
      "CONST(uint8, CCP_CONST) CCP_kaudtDevId[" DEVICE_ID{VALUE COUNT} "] ="'
`     '{
`     "   " DEVICE_ID{VALUE AS val CONCATE {val ", "}} '
`     "};"
   }
   WHERE (DEVICE_ID == "INTERNAL_STRING")
   {
      'CONST(uint8, CCP_CONST) CCP_kaudtDevId[sizeof("` DEVICE_ID{VALUE} '")] = "`
      DEVICE_ID{VALUE} '";`
   }
}
'
/* !Comment: DAQ lists configuration                                          */
`
CCP WHERE (DAQ_LIST_SERVICES == TRUE)
{
'CONST(CCP_tstrDaqListStatCfg, CCP_CONST)
   CCP_kastrDaqListStatCfg[CCP_u8DAQ_NO_LISTS] =
{
`
   .DAQ_LIST AS daqList ORDERBY(FileOrder()) CONCATE
   {
      WHERE (counter() > 0)
      {
         ",
"
      }
      "   {" NUMBER_OF_ODT ", "
      .DAQ_LIST WHERE(counter() < daqList{counter()}) ORDERBY(FileOrder()) SUM
      {
         NUMBER_OF_ODT
      }
      "}"
   }
"
};"
}
'

#define CCP_STOP_SEC_CONST_UNSPECIFIED
#include "CCP_MemMap.h"


/*-------------------------------- end of file -------------------------------*/