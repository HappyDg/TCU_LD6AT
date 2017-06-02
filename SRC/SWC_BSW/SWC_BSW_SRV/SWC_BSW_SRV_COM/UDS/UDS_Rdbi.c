/******************************************************************************/
/*                                                                            */
/* !Layer           : SRV                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : UDS_Rdbi.c                                              */
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
#include "Dcm_Types.h" 
#include "UDS.h"
#include "Dcm.h"

#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdProtocolVer                                      */
/* !Description : DID F100                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdProtocolVer(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   /* Byte 3 to 4 : Active Diag Info */
   *Data = (uint8)((UDS_u16ActiveDiagInfo & 0xFF00) >> 8);
   Data++;   
   *Data = (uint8)(UDS_u16ActiveDiagInfo & 0x00FF);
   Data++;  
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdMTOC                                             */
/* !Description : DID F102                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdMTOC(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   uint8 u8LocalId;
   
   /* Byte 3 to 19 : MTOC */
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      *Data = UDS_u8MtocNvm[u8LocalId];  
      Data++;
   }  
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdGACDiagSpecVer                                   */
/* !Description : DID F10D                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdGACDiagSpecVer(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   /* Byte 3 : GAC Diagnostic Specification Version */
   *Data = UDS_u8DiagSpecVersion;
   Data++;
   /* Byte 4 : ECU Reprogramming requirements_Specification version */
   *Data = UDS_u8ReprogReqSpecVers;
   Data++;   
   /* Byte 5 : Diagnostic Performance Requirements Standard */
   *Data = UDS_u8DiagPerfReqStand;
   Data++;     

   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdGACECUHWVer                                      */
/* !Description : DID F17F                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdGACECUHWVer(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   uint8 u8LocalId;
   /* Byte 3 to 19 : Hardware version number */   
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      *Data = UDS_u8EcuHardVersNum[u8LocalId];   
      Data++;      
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdBootSWIdent                                      */
/* !Description : DID F180                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdBootSWIdent(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   uint8 u8LocalId;
   /* Byte 3 to 19 : Boot identifier */
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      *Data = UDS_u8BootSoftId[u8LocalId];  
      Data++;
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdAppSw                                            */
/* !Description : DID F181                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdAppSw(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   uint8 u8LocalId;
   
   /* Byte 3 to 19 : Application software identifier */
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      *Data = UDS_u8AppSoftId[u8LocalId];  
      Data++;
   }  
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdFingerPrint                                      */
/* !Description : DID F184                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdFingerPrint(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   uint8 u8LocalId;
   
   /* Byte 3 : Tool supplier ID */
   *Data = UDS_u8ToolSupplierIdNvm;
   Data++;
      
   /* Byte 4 to 6 : Tester serial number */
   for (u8LocalId = 0; u8LocalId < 3; u8LocalId++)
   {
      *Data = UDS_u8ProgFingerPrintDateNvm[u8LocalId];
      Data++;      
   }
   
   /* Byte 7 to 12 : Tester serial number */
   for (u8LocalId = 0; u8LocalId < 6; u8LocalId++)
   {
      *Data = UDS_u8TesterSerialNbNvm[u8LocalId];  
      Data++;
   } 
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdActSession                                       */
/* !Description : DID F186                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdActSession(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   Dcm_SesCtrlType bLocalActiveSession;
   Std_ReturnType bLocalReturnVal;

   Dcm_GetSesCtrlType(&bLocalActiveSession);
   
   /* Byte3 */
   switch (bLocalActiveSession)
   {
      case DCM_DEFAULT_SESSION:
      case DCM_EXTENDED_DIAGNOSTIC_SESSION:
      case DCM_PROGRAMMING_SESSION:
         *Data = (uint8)bLocalActiveSession;
         Data++;
         bLocalReturnVal = E_OK;
         break;
      default:
         bLocalReturnVal = E_NOT_OK;
         break;
   }
   return bLocalReturnVal;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdGACPartNum                                       */
/* !Description : DID F187                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdGACPartNum(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   uint8 u8LocalId;
   /* Byte 3 to 16 : Part Number */
   for (u8LocalId = 0; u8LocalId < 14; u8LocalId++)
   {
      *Data = UDS_u8PartNumber[u8LocalId];
      Data++;
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdGACECUSWVer                                      */
/* !Description : DID F189                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdGACECUSWVer(Dcm_OpStatusType OpStatus, uint8 *Data)
{
   uint8 u8LocalId;
   /* Byte 3 to 19 : Software version number */   
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      *Data = UDS_u8EcuSoftVersNum[u8LocalId];
      Data++;      
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdECUSN                                            */
/* !Description : DID F18C                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdECUSN(Dcm_OpStatusType OpStatus, uint8 *Data)
{
    uint8 u8LocalId;
    
   /* Byte 3 to 5 : Product Serial Number */
   *Data = (uint8)((UDS_u32ProductSerialNum & 0x00FF0000) >> 16);
   Data++;
   *Data = (uint8)((UDS_u32ProductSerialNum & 0x0000FF00) >> 8);
   Data++;   
   *Data = (uint8)(UDS_u32ProductSerialNum & 0x000000FF);
   Data++;  
   /* Byte 6 to 7 : Production Line Number */
   *Data = (uint8)((UDS_u16ProductLineNum & 0xFF00) >> 8);
   Data++;   
   *Data = (uint8)(UDS_u16ProductLineNum & 0x00FF);
   Data++;    
   /* Byte 8 to 10 : Prod date */
   for (u8LocalId = 0; u8LocalId < 3; u8LocalId++)
   {
      *Data = UDS_u8ProdDate[u8LocalId];
      Data++;      
   }

   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdGacKitAsPartNb                                           */
/* !Description : DID F18E                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdGacKitAsPartNb(Dcm_OpStatusType OpStatus, uint8 *Data)
{              
   uint8 u8LocalId;
   /* Byte 3 to 19 : VIN */   
   for (u8LocalId = 0; u8LocalId < 14; u8LocalId++)
   {
      *Data = UDS_u8GACKitAssemPartNb[u8LocalId];      
      Data++;      
   }
   
   return E_OK;
}
/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdECUVIN                                           */
/* !Description : DID F190                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdECUVIN(Dcm_OpStatusType OpStatus, uint8 *Data)
{              
   uint8 u8LocalId;
   /* Byte 3 to 19 : VIN */   
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      *Data = UDS_u8EcuVinNvm[u8LocalId];      
      Data++;      
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdSystemName                                       */
/* !Description : DID F197                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdSystemName(Dcm_OpStatusType OpStatus, uint8 *Data)
{              
   uint8 u8LocalId;
   /* Byte 3 to 22 : System name */   
   for (u8LocalId = 0; u8LocalId < 20; u8LocalId++)
   {
      *Data = UDS_u8SystemName[u8LocalId];      
      Data++;      
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdProgDate                                         */
/* !Description : DID F199                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdProgDate(Dcm_OpStatusType OpStatus, uint8 *Data)
{              

   /* Byte 3 to 4 : Year (Default value : 2000)*/
   *Data = (uint8)((UDS_u16ProgYearNvm & 0xFF00) >> 8);
   Data++;   
   *Data = (uint8)(UDS_u16ProgYearNvm & 0x00FF);
   Data++;   
 
   /* Byte 5 : Month (Default value : 1)*/
   *Data = UDS_u8ProgMonthNvm;
   Data++;   
 
   /* Byte 6 : Day (Default value : 1)*/
   *Data = UDS_u8ProgDayNvm;
   Data++;

   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReadIdCalibSoft                                        */
/* !Description : DID F1B2                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReadIdCalibSoft(Dcm_OpStatusType OpStatus, uint8 *Data)
{              
   uint8 u8LocalId;
   /* Byte 3 to 19 : Calibration software identification */   
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      *Data = UDS_u8CalibSoftId[u8LocalId];      
      Data++;      
   }
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdProtocolVer                                     */
/* !Description : Check function for DID F100                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdProtocolVer (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdMTOC                                            */
/* !Description : Check function for DID F102                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdMTOC (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdGACDiagSpecVer                                  */
/* !Description : Check function for DID F10D                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdGACDiagSpecVer (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdGACECUHWVer                                     */
/* !Description : Check function for DID F17F                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdGACECUHWVer (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdBootSWIdent                                     */
/* !Description : Check function for DID F180                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdBootSWIdent (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdAppSw                                           */
/* !Description : Check function for DID F181                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdAppSw (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdFingerPrint                                     */
/* !Description : Check function for DID F184                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdFingerPrint (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdActSession                                      */
/* !Description : Check function for DID F186                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
FUNC(Std_ReturnType, RTE_APPL_CODE) UDS_bChkRdIdActSession(P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
   /* No specific conditions defined */
   *ErrorCode = E_OK;
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdGACPartNum                                      */
/* !Description : Check function for DID F187                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdGACPartNum (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdGACECUSWVer                                     */
/* !Description : Check function for DID F189                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdGACECUSWVer (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdECUSN                                           */
/* !Description : Check function for DID F18C                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdECUSN (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdGacKitAsPartNb                                  */
/* !Description : Check function for DID F18E                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdGacKitAsPartNb (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdECUVIN                                          */
/* !Description : Check function for DID F190                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdECUVIN (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdSystemName                                      */
/* !Description : Check function for DID F197                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdSystemName (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdProgDate                                        */
/* !Description : Check function for DID F199                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdProgDate (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bChkRdIdCalibSoft                                       */
/* !Description : Check function for DID F1B2                                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bChkRdIdCalibSoft (P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
    /* No specific conditions defined */
    *ErrorCode = E_OK;
    return E_OK;
}

#define UDS_STOP_SEC_CODE
#include "MemMap.h"
/*------------------------------- end of file --------------------------------*/