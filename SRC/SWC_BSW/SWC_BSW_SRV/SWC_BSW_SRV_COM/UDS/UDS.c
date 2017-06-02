/******************************************************************************/
/*                                                                            */
/* !Layer           : COM                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     : Diagnostic service management                           */
/*                                                                            */
/* !File            : UDS.c                                                   */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2011 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive:                                                                 $*/
/* $Revision::            $$Author::                  $$Date::               $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/******************************************************************************/

#include "Std_Types.h"
#include "UDS.h"

#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_vidInit                                              */
/* !Description : Management of session changes                               */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
void UDS_vidInit(void)
{
   uint8 u8LocalId;
   uint8 u8LocalDidF17fVal[17] = {"1520013ADU0000H.B"};
   uint8 u8LocalDidF180Val[17] = {"1520013ADU0000B.A"};
   uint8 u8LocalDidF181Val[17] = {"1520013ADU0000A.A"};
   uint8 u8LocalDidF187Val[14] = {"1520013ADU0000"};
   uint8 u8LocalDidF189Val[17] = {"1520013ADU0000S.A"};
   uint8 u8LocalDidF18eVal[14] = {"P-1520000018"};
   uint8 u8LocalDidF197Val[20] = {"GAC-A5H-DCU"};
   uint8 u8LocalDidF1b2Val[17] = {"1520013ADU0000C.A"}; 
   /*DID F100 */
   UDS_u16ActiveDiagInfo = 0x2006;

   /*DID F102 */
   for (u8LocalId = 0; u8LocalId < UDS_U8MTOCNVM_COLS; u8LocalId++)
   {
      UDS_u8MtocNvm[u8LocalId] = 0;
   }   
   
   /*DID F10D */   
   UDS_u8DiagSpecVersion   = 0x18; /* Version of GAC Diagnostic Specification 2.4_release.pdf : v2.4 */
   UDS_u8ReprogReqSpecVers = 0x17; /* Version of GAC Flash Reprogramming Specification 2.3.pdf : v2.3 */ 
   UDS_u8DiagPerfReqStand  = 0x0C; /* Version of VE_A5H_BSWTC26_SIQ_UDS_2016_05_16_V1_2.xls : v1.2 */
   
   /* DID F17F */
   //UDS_u8EcuHardVersNum = {"1520013ADU0000H.B"};
   for (u8LocalId = 0; u8LocalId < UDS_U8ECUHARDVERSNUM_COLS; u8LocalId++)
   {   
      UDS_u8EcuHardVersNum[u8LocalId] = u8LocalDidF17fVal[u8LocalId];
   }   
   
   /* DID F180 */
   //UDS_u8BootSoftId = "1520013ADU0000B.A";
   for (u8LocalId = 0; u8LocalId < UDS_U8BOOTSOFTID_COLS; u8LocalId++)
   {   
      UDS_u8BootSoftId[u8LocalId] = u8LocalDidF180Val[u8LocalId];
   } 
   
   /* DID F181 */
   //UDS_u8AppSoftId = "1520013ADU0000A.A";
   for (u8LocalId = 0; u8LocalId < UDS_U8APPSOFTID_COLS; u8LocalId++)
   {   
      UDS_u8AppSoftId[u8LocalId] = u8LocalDidF181Val[u8LocalId];
   }
   
   /* DID F184 */
   UDS_u8ToolSupplierIdNvm = 0;
   for (u8LocalId = 0; u8LocalId < 6; u8LocalId++)
   {   
      UDS_u8TesterSerialNbNvm[u8LocalId] = 0;
   }  
   UDS_u8ProgFingerPrintDateNvm[0] = 0x00; /* Year  */
   UDS_u8ProgFingerPrintDateNvm[1] = 0x01; /* Month */
   UDS_u8ProgFingerPrintDateNvm[2] = 0x01; /* Day   */

   /* DID F187 */
   //UDS_u8PartNumber = "1520013ADU0000";
   for (u8LocalId = 0; u8LocalId < UDS_U8PARTNUMBER_COLS; u8LocalId++)
   {   
      UDS_u8PartNumber[u8LocalId] = u8LocalDidF187Val[u8LocalId];
   }
   
   /* DID F189 */
   //UDS_u8EcuSoftVersNum = "1520013ADU0000S.A";
   for (u8LocalId = 0; u8LocalId < UDS_U8ECUSOFTVERSNUM_COLS; u8LocalId++)
   {   
      UDS_u8EcuSoftVersNum[u8LocalId] = u8LocalDidF189Val[u8LocalId];
   }   

   
   /* DID F18C */
   UDS_u32ProductSerialNum = 0;
   UDS_u16ProductLineNum = 0;

   UDS_u8ProdDate[0] = 0x00; /* low byte of year */
   UDS_u8ProdDate[1] = 0x01; /* Month */
   UDS_u8ProdDate[2] = 0x01; /* Day */

   /* DID F18E */
   //UDS_u8GACKitAssemPartNb = "P-1520000018";   
   for (u8LocalId = 0; u8LocalId < UDS_U8GACKITASSEMPARTNB_COLS; u8LocalId++)
   {   
      UDS_u8GACKitAssemPartNb[u8LocalId] = u8LocalDidF18eVal[u8LocalId];
   } 
   
   
   /* DID F190 */
   for (u8LocalId = 0; u8LocalId < UDS_U8ECUVINNVM_COLS; u8LocalId++)
   {
      UDS_u8EcuVinNvm[u8LocalId] = 0;
   }   
   
   /* DID F197 */
   //UDS_u8SystemName = "GAC-A5H-DCU";   
   for (u8LocalId = 0; u8LocalId < UDS_U8SYSTEMNAME_COLS; u8LocalId++)
   {   
      UDS_u8SystemName[u8LocalId] = u8LocalDidF197Val[u8LocalId];
   }    

   /* DID F199 */
   UDS_u16ProgYearNvm = 0x2000;
   UDS_u8ProgMonthNvm = 0x01;
   UDS_u8ProgDayNvm = 0x01;   

   /* DID F1B2 */
   //UDS_u8CalibSoftId = "1520013ADU0000C.A";    
   for (u8LocalId = 0; u8LocalId < UDS_U8CALIBSOFTID_COLS; u8LocalId++)
   {   
      UDS_u8CalibSoftId[u8LocalId] = u8LocalDidF1b2Val[u8LocalId];
   }   
}

#define UDS_STOP_SEC_CODE
#include "memmap.h"

/*-------------------------------- end of file -------------------------------*/