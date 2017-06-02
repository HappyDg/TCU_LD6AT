/******************************************************************************/
/*                                                                            */
/* !Layer           : SRV                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : UDS_Wdbi.c                                              */
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

#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bWriteIdMTOC                                            */
/* !Description : DID F102                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bWriteIdMTOC(uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
{
   uint8 u8LocalId;
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      UDS_u8MtocNvm[u8LocalId] = *Data;
      Data++;      
   }
   *ErrorCode = E_OK;
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bWriteIdFingerPrinter                                   */
/* !Description : DID F184                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bWriteIdFingerPrinter(uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
{
   uint8 u8LocalId;
   uint16 u8LocalProgYear;
   uint8 u8LocalProgMonth;
   uint8 u8LocalProgDay; 
   uint8 u8LocalToolSupplierId;
   Std_ReturnType bLocalReturnVal;

   u8LocalId = 0;
   u8LocalProgYear = 0;
   u8LocalProgMonth = 0;
   u8LocalProgDay = 0; 
   u8LocalToolSupplierId = 0;
   bLocalReturnVal = E_NOT_OK;
   
   /* Byte 3 : Tool supplier ID */
   u8LocalToolSupplierId = *Data;
   Data++;

   /* Byte 4 : Year */
   u8LocalProgYear = (*Data);
   Data++;

   if (u8LocalProgYear <= 0x99)
   {
      /* Byte 5 : Month (Default value : 1)*/
      u8LocalProgMonth = *Data;
      Data++;      
      if ((u8LocalProgMonth > 0x00) &&
          (u8LocalProgMonth <= 0x12))
      {
         /* Byte 6 : Day (Default value : 1)*/
         u8LocalProgDay = (*Data);
         Data++;
         
         if ((u8LocalProgDay > 0x00) &&
             (u8LocalProgDay <= 0x31))
         {
            bLocalReturnVal = E_OK;
         }
         else
         {
            bLocalReturnVal = E_NOT_OK;
         } 
      }
      else
      {
         bLocalReturnVal = E_NOT_OK;
      }
   }
   else
   {
      bLocalReturnVal = E_NOT_OK;
   }      

   if (bLocalReturnVal != E_NOT_OK)
   {
      /* Byte 3 : Tool supplier ID */
      UDS_u8ToolSupplierIdNvm = u8LocalToolSupplierId;
      
      /* Byte 4 to 6 : programming date */   
      UDS_u8ProgFingerPrintDateNvm[0] = u8LocalProgYear; 
      UDS_u8ProgFingerPrintDateNvm[1] = u8LocalProgMonth; 
      UDS_u8ProgFingerPrintDateNvm[2] = u8LocalProgDay; 
      
      /* Byte 7 to 12 : Tester serial number */   
      for (u8LocalId = 0; u8LocalId < 6; u8LocalId++)
      {
         UDS_u8TesterSerialNbNvm[u8LocalId] = *Data; 
         Data++;
      }
      
      *ErrorCode = E_OK;
   }
   else
   {
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
   }
   
   return bLocalReturnVal;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bWriteIdECUVIN                                        */
/* !Description : DID F190                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bWriteIdECUVIN(uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
{
   
   uint8 u8LocalId;
   /* Byte 3 to 19 : VIN */   
   for (u8LocalId = 0; u8LocalId < 17; u8LocalId++)
   {
      UDS_u8EcuVinNvm[u8LocalId] = *Data;      
      Data++;      
   }
   
   *ErrorCode = E_OK;
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bWriteIdProgDate                                        */
/* !Description : DID F199                                                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bWriteIdProgDate(uint8 *Data, Dcm_OpStatusType OpStatus, Dcm_NegativeResponseCodeType *ErrorCode)
{
   uint16 u16LocalProgYear;
   uint8 u8LocalProgMonth;
   uint8 u8LocalProgDay;
   Std_ReturnType bLocalReturnVal;
   
   u16LocalProgYear = 0;
   u8LocalProgMonth = 0;
   u8LocalProgDay = 0;
   bLocalReturnVal = E_NOT_OK;   
   
   /* Byte 3 to 4 : Year (Default value : 2000)*/
   u16LocalProgYear =  (uint16)((uint16)(*Data) << 8);
   Data++; 
   u16LocalProgYear += (uint16)(*Data);
   Data++;   
   if ((u16LocalProgYear >= 0x2000) &&
       (u16LocalProgYear <= 0x9999))
   {
      /* Byte 5 : Month (Default value : 1)*/
      u8LocalProgMonth = (*Data);
      Data++;     
      if ((u8LocalProgMonth > 0x00) &&
          (u8LocalProgMonth <= 0x12))
      {
         /* Byte 6 : Day (Default value : 1)*/
         u8LocalProgDay = (*Data);
         Data++;     
         if ((u8LocalProgDay > 0x00) &&
             (u8LocalProgDay <= 0x31))
         {
            bLocalReturnVal = E_OK;
         }
         else
         {
            bLocalReturnVal = E_NOT_OK;
         }
      }
      else
      {
         bLocalReturnVal = E_NOT_OK;
      }
   }
   else
   {
      bLocalReturnVal = E_NOT_OK;
   }
   
   if (bLocalReturnVal != E_NOT_OK)
   {
      UDS_u16ProgYearNvm = u16LocalProgYear;
      UDS_u8ProgMonthNvm = u8LocalProgMonth;
      UDS_u8ProgDayNvm = u8LocalProgDay;
      *ErrorCode = E_OK;
   }
   else
   {
      *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
   }
   
   return bLocalReturnVal;
}

#define UDS_STOP_SEC_CODE
#include "MemMap.h"
/*------------------------------- end of file --------------------------------*/

