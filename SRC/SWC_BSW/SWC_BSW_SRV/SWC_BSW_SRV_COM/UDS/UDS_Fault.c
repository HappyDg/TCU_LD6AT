/******************************************************************************/
/*                                                                            */
/* !Layer           : SRV                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : UDS_Fault.c                                             */
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
/******************************************************************************/

#include "Std_Types.h"
#include "Dcm.h" 
//#include "DSM_Drv.h"
//#include "DSM_Nvm.h"
//#include "FAULT_Data.h"
#include "Dem.h"

#define UDS_DTC_AVAILABILITYMASK 0x39

#define UDS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

static const uint16 UDS_FreezeFrameDid[15] = {0x1111,
                                                                     0x2222,
                                                                     0x3333,
                                                                     0x4444,
                                                                     0x5555,
                                                                     0x6666,
                                                                     0x7777,
                                                                     0x8888,
                                                                     0x9999,
                                                                     0xAAAA,
                                                                     0xBBBB,
                                                                     0xCCCC,
                                                                     0xDDDD,
                                                                     0xEEEE,
                                                                     0xFFFF
                                                                    };

#define UDS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"    

#define UDS_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReportDtcSnapshotRecordByDtcNb                         */
/* !Description : Function to read freeze frame $19 $04                       */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReportDtcSnapshotRecordByDtcNb(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{
//  uint32 u32LocalDtcNumber;
//  uint8 u8LocalNvmFaultId;
//  uint8 u8LocalSnapshotRecNum;
//  uint8 u8LocalFreezeFrameId;
//  Dcm_MsgType dataPtr;
//  boolean bLocalDtcSupported;
//  boolean bLocalDtcLogged;
//  Std_ReturnType serviceProcessStatus;     
//  
//  u32LocalDtcNumber = 0;
//  u8LocalNvmFaultId = 0;
//  bLocalDtcSupported = 0;
//  bLocalDtcLogged = 0;
//  u8LocalFreezeFrameId = 0;
//  
//  if ( pMsgContext->reqDataLen == 4U )
//  {
//     if (OpStatus == DCM_INITIAL)
//     {
//
//        /* Get Snapshot Record number from request */
//        u8LocalSnapshotRecNum = pMsgContext->reqData[3];  
//        
//        if (u8LocalSnapshotRecNum == 0xFF)
//        {
//           u32LocalDtcNumber = ((uint32)pMsgContext->reqData[0] << 16U) |
//                               ((uint32)pMsgContext->reqData[1] << 8U) |
//                               ((uint32)pMsgContext->reqData[2]);   
//                               
//           bLocalDtcSupported = DSM_bDtcSupported(u32LocalDtcNumber);
//
//           if (0 != bLocalDtcSupported)
//           {
//              /* cache data pointer */
//              dataPtr = &pMsgContext->resData[1];
//           
//              *dataPtr = (uint8)((u32LocalDtcNumber & 0xFF0000) >> 16);
//              dataPtr++;   
//              *dataPtr = (uint8)((u32LocalDtcNumber & 0x00FF00) >> 8);
//              dataPtr++; 
//              *dataPtr = (uint8) (u32LocalDtcNumber & 0x0000FF);
//              dataPtr++; 
//              
//              pMsgContext->resDataLen += 3;
//         
//              bLocalDtcLogged = DSM_bDtcLogged(u32LocalDtcNumber, &u8LocalNvmFaultId);
//              if (0 != bLocalDtcLogged)
//              {
//                 /* DTC status */
//                 *dataPtr = DSM_DtcStatusNvm[u8LocalNvmFaultId];         
//                 dataPtr++;
//                 /* DTC snapshot record number : copy received value */
//                 *dataPtr = u8LocalNvmFaultId;         
//                 dataPtr++;
//                 /* DTC snapshot record number of identifiers */
//                 *dataPtr = DSM_DTC_FREEZE_FRAME_SIZE;         
//                 dataPtr++;               
//                 
//                 for (u8LocalFreezeFrameId = 0; u8LocalFreezeFrameId < DSM_DTC_FREEZE_FRAME_SIZE; u8LocalFreezeFrameId++)
//                 {
//                    *dataPtr = (uint8)((UDS_FreezeFrameDid[u8LocalFreezeFrameId] & 0xFF00) >> 8);
//                    dataPtr++;   
//                    *dataPtr = (uint8) (UDS_FreezeFrameDid[u8LocalFreezeFrameId] & 0x00FF);
//                    dataPtr++;  
//                    
//                    *dataPtr = (uint8)((DSM_DtcSavedFreezeFrameNvm[u8LocalNvmFaultId].DtcFreezeFrame[u8LocalFreezeFrameId] & 0xFF00) >> 8);         
//                    dataPtr++;  
//                    *dataPtr = (uint8) (DSM_DtcSavedFreezeFrameNvm[u8LocalNvmFaultId].DtcFreezeFrame[u8LocalFreezeFrameId] & 0x00FF); 
//                    dataPtr++;
//                 }
//
//                 pMsgContext->resDataLen += (4 * DSM_DTC_FREEZE_FRAME_SIZE) + 3;               
//              }
//              else
//              {
//                 /* DTC status */
//                 *dataPtr = 0x00;
//                 dataPtr++;      
//                 /* Snapshot record number : copy received value */
//                 *dataPtr = 0x00;
//                 dataPtr++;   
//                 
//                 pMsgContext->resDataLen += 2; 
//              }
//           }
//           else
//           {
//              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE); 
//           }
//        }
//        else
//        {
//           Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE); 
//        }        
//     }
//     else
//     {
//        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
//     }
//  }
//  else
//  {
//     Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
//  }
//  
//  serviceProcessStatus = DCM_E_DONE; 
//  return serviceProcessStatus;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReportDtcExtDataRecordByDtcNb                          */
/* !Description : Function to read environmental Data $19 $06                 */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReportDtcExtDataRecordByDtcNb(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{
 //  uint8 u8LocalNvmFaultId;
 //  uint8 u8LocalExtRecNum;
 //  boolean bLocalDtcSupported;
 //  uint32 u32LocalDtcNumber;
 //  boolean bLocalDtcLogged;
 //  Dcm_MsgType dataPtr;  
 //  Std_ReturnType serviceProcessStatus;   
 //  
 //  u32LocalDtcNumber = 0;
 //  u8LocalNvmFaultId = 0;
 //  bLocalDtcSupported = 0;
 //  bLocalDtcLogged = 0;
 //  u8LocalExtRecNum = 0;
 //  
 //  /* check if the request data length is valid */
 //  if ( pMsgContext->reqDataLen == 4U )
 //  {
 //     if (OpStatus == DCM_INITIAL)
 //     {
 //        /* Get Snapshot Record number from request */
 //        u8LocalExtRecNum = pMsgContext->reqData[3];  
 //
 //        if (u8LocalExtRecNum == 0xFF)
 //        {
 //           u32LocalDtcNumber = ((uint32)pMsgContext->reqData[0] << 16U) |
 //                               ((uint32)pMsgContext->reqData[1] << 8U) |
 //                               ((uint32)pMsgContext->reqData[2]);  
 //                               
 //           bLocalDtcSupported = DSM_bDtcSupported(u32LocalDtcNumber);
 //
 //           if (0 != bLocalDtcSupported)
 //           {
 //              /* cache data pointer */
 //              dataPtr = &pMsgContext->resData[1];
 //           
 //              *dataPtr = (uint8)((u32LocalDtcNumber & 0xFF0000) >> 16);
 //              dataPtr++;   
 //              *dataPtr = (uint8)((u32LocalDtcNumber & 0x00FF00) >> 8);
 //              dataPtr++; 
 //              *dataPtr = (uint8) (u32LocalDtcNumber & 0x0000FF);
 //              dataPtr++;    
 //
 //              pMsgContext->resDataLen += 3;
 //              
 //              bLocalDtcLogged = DSM_bDtcLogged(u32LocalDtcNumber, &u8LocalNvmFaultId);
 //              if (0 != bLocalDtcLogged)
 //              {
 //                 /* DTC status */
 //                 *dataPtr = DSM_DtcStatusNvm[u8LocalNvmFaultId];         
 //                 dataPtr++;
 //                 
 //                 /* DTC extended data record number */
 //                 *dataPtr = 0x00;      
 //                 dataPtr++;
 //                 /* Environmental datas */
 //                 *dataPtr = DSM_DtcEnvDataNvm[u8LocalNvmFaultId].u8DtcAgingCycleCnt;
 //                 dataPtr++;
 //
 //                 /* DTC extended data record number */
 //                 *dataPtr = 0x01;      
 //                 dataPtr++; 
 //                 /* Environmental datas */
 //                 *dataPtr = DSM_DtcEnvDataNvm[u8LocalNvmFaultId].u8DtcOccurCnt;
 //                 dataPtr++;
 //                 
 //                 pMsgContext->resDataLen += 5;
 //              }
 //              else
 //              {
 //                 /* DTC status */
 //                 *dataPtr = 0x00;         
 //                 dataPtr++;
 //                
 //                 pMsgContext->resDataLen += 1;        
 //              }
 //           }
 //           else
 //           {
 //              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
 //           }            
 //        }
 //        else
 //        {
 //           Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
 //        }
 //     }
 //     else
 //     {
 //        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
 //     }         
 //  }
 //  else
 //  {
 //     Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
 //  } 
 //  
 //  serviceProcessStatus = DCM_E_DONE;   
 //  return serviceProcessStatus;   
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReportSupportedDtcs                                    */
/* !Description : Function to return supported DTC $19 $0A                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReportSupportedDtcs(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{              
 //  uint32 u32LocalDtcNumber;
 //  uint8 u8LocalFaultOffset;
 //  uint8 u8LocalNvmFaultId;
 //  boolean bLocalDtcLogged;
 //  Dcm_MsgType dataPtr; 
 //  Std_ReturnType serviceProcessStatus;   
 //  
 //  u32LocalDtcNumber = 0;
 //  u8LocalNvmFaultId = 0;
 //  bLocalDtcLogged = 0;
 //
 //  /* check if the request data length is valid */
 //  if ( pMsgContext->reqDataLen == 0U )
 //  {
 //     if (OpStatus == DCM_INITIAL)
 //     {   
 //        /* DTC status availability mask */
 //        pMsgContext->resData[1] = 0x39;         
 //        pMsgContext->resDataLen += 1; 
 //
 //        dataPtr = &pMsgContext->resData[2];
 //        
 //     for (u8LocalFaultOffset = 0; u8LocalFaultOffset < NB_FAULT_FUNCTION_TYPE ; u8LocalFaultOffset++)
 //        {
 //           u32LocalDtcNumber = FaultFunctionTypeDtcNbTable[u8LocalFaultOffset];
 //           *dataPtr = (uint8)((u32LocalDtcNumber & 0xFF0000) >> 16);
 //           dataPtr++;
 //           *dataPtr = (uint8)((u32LocalDtcNumber & 0x00FF00) >> 8);
 //           dataPtr++;
 //           *dataPtr = (uint8) (u32LocalDtcNumber & 0x0000FF);
 //           dataPtr++;
 //
 //           pMsgContext->resDataLen += 3; 
 //           
 //           bLocalDtcLogged = DSM_bDtcLogged(u32LocalDtcNumber, &u8LocalNvmFaultId);
 //           if (0 != bLocalDtcLogged)
 //           {
 //              *dataPtr = DSM_DtcStatusNvm[u8LocalNvmFaultId];         
 //           }
 //           else
 //           {
 //              *dataPtr = 0x00;
 //           }
 //           dataPtr++; 
 //           
 //           pMsgContext->resDataLen += 1; 
 //        }
 //     }
 //     else
 //     {
 //        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
 //     }
 //  }
 //  else
 //  {
 //     Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
 //  }   
 //  
 //  serviceProcessStatus = DCM_E_DONE;  
 //  return serviceProcessStatus;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReportNumberOfDtcByStatusMask                          */
/* !Description : Function to return number of DTC by status mask $19 $01     */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReportNumberOfDtcByStatusMask(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{
//   uint32 u32LocalDtcNumber;
//
//   uint8 u8LocalNumberDtc;
//   uint8 u8LocalNvmFaultId;
//   uint8 u8LocalFaultOffset;
//   uint8 u8LocalDtcStatus;
//   uint8 u8LocalReqStatusMask;
//   
//   boolean bLocalDtcLogged;
//   Std_ReturnType serviceProcessStatus;     
//   
//   u32LocalDtcNumber = 0;
//   u8LocalNvmFaultId = 0;
//   u8LocalFaultOffset = 0;
//   bLocalDtcLogged = 0;
//   u8LocalDtcStatus = 0;
//   u8LocalNumberDtc = 0;
//   
//   if (OpStatus == DCM_INITIAL)
//   {   
//      if (pMsgContext->reqDataLen == 1U)
//      {   
//         u8LocalReqStatusMask = pMsgContext->reqData[0];
//         
//         /* DTC status availability mask */
//         pMsgContext->resData[1] = ((uint8)UDS_DTC_AVAILABILITYMASK);         
//         
//         /* DTC format identifier : 3Bytes */
//         pMsgContext->resData[2] = 0x01;    
//         
//         pMsgContext->resDataLen += (PduLengthType)2U;
//         
//         if ((u8LocalReqStatusMask & ((uint8)UDS_DTC_AVAILABILITYMASK)) == 0U)
//         {
//            /* Update DTCCountHighByte */
//            pMsgContext->resData[3] = 0x00;
//            /* Update DTCCountLowByte */
//            pMsgContext->resData[4] = 0x00;
//            /* update the total response length for the filtered DTCs */
//            pMsgContext->resDataLen += (PduLengthType)2U;
//         }
//         else
//         {
//            for (u8LocalFaultOffset = 0; u8LocalFaultOffset < NB_FAULT_FUNCTION_TYPE ; u8LocalFaultOffset++)
//            {
//               u32LocalDtcNumber = FaultFunctionTypeDtcNbTable[u8LocalFaultOffset];
//               bLocalDtcLogged = DSM_bDtcLogged(u32LocalDtcNumber, &u8LocalNvmFaultId);
//               if ((0 != bLocalDtcLogged) && (u32LocalDtcNumber != 0))
//               {
//                  u8LocalDtcStatus = DSM_DtcStatusNvm[u8LocalNvmFaultId];
//                  if ((u8LocalReqStatusMask & u8LocalDtcStatus) != 0)
//                  {
//                     u8LocalNumberDtc++;
//                  }
//               }
//            }
//            
//            /* Update DTCCountHighByte */
//            pMsgContext->resData[3] = 0x00;
//            /* Update DTCCountLowByte */
//            pMsgContext->resData[4] = u8LocalNumberDtc;
//            /* update the total response length for the filtered DTCs */
//            pMsgContext->resDataLen += (PduLengthType)2U;
//         }
//      }
//      else
//      {
//         /* Negative response */
//         Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
//      }
//   }
//   else
//   {
//      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
//   }
//   
//   serviceProcessStatus = DCM_E_DONE;   
//   return serviceProcessStatus;   
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bReportDtcByStatusMask                                  */
/* !Description : Function to return DTC value by status mask $19 $02         */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bReportDtcByStatusMask(Dcm_OpStatusType OpStatus, Dcm_MsgContextType *pMsgContext)
{
 //  uint32 u32LocalDtcNumber;
 //  
 //  uint8 u8LocalNvmFaultId;
 //  uint8 u8LocalFaultOffset;
 //  uint8 u8LocalDtcStatus;
 //  uint8 u8LocalReqStatusMask;
 //  
 //  boolean bLocalDtcLogged;
 //  Dcm_MsgType dataPtr;
 //  Std_ReturnType serviceProcessStatus;     
 //  
 //  u8LocalNvmFaultId = 0;
 //  u8LocalFaultOffset = 0;
 //  bLocalDtcLogged = 0;
 //  u8LocalDtcStatus = 0;
 //  u32LocalDtcNumber = 0;
 //  u8LocalReqStatusMask = 0;
 //
 // if (pMsgContext->reqDataLen == 1U)
 // {   
 //     if (OpStatus == DCM_INITIAL)
 //     { 
 //        u8LocalReqStatusMask = pMsgContext->reqData[0];
 //       
 //        if ((u8LocalReqStatusMask & ((uint8)UDS_DTC_AVAILABILITYMASK)) == 0U)
 //        {
 //           /* update response data with Status Mask */
 //           pMsgContext->resData[1] = ((uint8)UDS_DTC_AVAILABILITYMASK);
 //           pMsgContext->resDataLen++;
 //           serviceProcessStatus = DCM_E_DONE;
 //        }
 //        else
 //        {
 //           /* cache data pointer */
 //           dataPtr = &pMsgContext->resData[1];
 //
 //           /* add status mask to response buffer and update the response length and filled length of
 //           * buffer */
 //           /* Deviation MISRA-1 */
 //            *dataPtr = ((uint8)UDS_DTC_AVAILABILITYMASK);
 //            dataPtr++;
 //            pMsgContext->resDataLen += (PduLengthType)1U;
 //           
 //           for (u8LocalFaultOffset = 0; u8LocalFaultOffset < NB_FAULT_FUNCTION_TYPE ; u8LocalFaultOffset++)
 //           {
 //              u32LocalDtcNumber = FaultFunctionTypeDtcNbTable[u8LocalFaultOffset];
 //              bLocalDtcLogged = DSM_bDtcLogged(u32LocalDtcNumber, &u8LocalNvmFaultId);
 //              if ((0 != bLocalDtcLogged) && (u32LocalDtcNumber != 0))
 //              {
 //                 u8LocalDtcStatus = DSM_DtcStatusNvm[u8LocalNvmFaultId];
 //                 if ((u8LocalReqStatusMask & u8LocalDtcStatus) != 0)
 //                 {
 //                    /* DTC */
 //                    *dataPtr = (uint8)(u32LocalDtcNumber >> 16U);
 //                    dataPtr++;
 //                    /* Deviation MISRA-1 */
 //                    *dataPtr = (uint8)(u32LocalDtcNumber >> 8U);
 //                    dataPtr++;
 //                    /* Deviation MISRA-1 */
 //                    *dataPtr = (uint8)(u32LocalDtcNumber);
 //                    dataPtr++;
 //
 //                    /* DTC status */
 //                    *dataPtr = u8LocalDtcStatus;         
 //                    dataPtr++;
 //                    
 //                    /* update response length */
 //                    pMsgContext->resDataLen += (PduLengthType)4U;
 //                 }
 //              }
 //           }
 //           serviceProcessStatus = DCM_E_DONE;         
 //        }
 //     }
 //     else
 //     {
 //        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
 //     }      
 //  }
 //  else
 //  {
 //     /* Negative response */
 //     Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
 //     serviceProcessStatus = DCM_E_DONE;
 //  } 
 //  return serviceProcessStatus;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bClearFault                                             */
/* !Description : Function to clear all DTC by UDS service                    */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
boolean UDS_bClearFault(uint32 DtcNumber) 
{
//   Dem_ReturnClearDTCType  bLocalClearStatus;
//
//   if (DtcNumber == 0xFFFFFF)
//   {
//      /* Clear all faults */
//      FaultClear();
//      bLocalClearStatus = DEM_CLEAR_OK;
//   }
//   else
//   {
//      bLocalClearStatus = DEM_CLEAR_WRONG_DTC;
//      /* Negative response managed by DCM */         
//   }
//   return bLocalClearStatus;
}

#define UDS_STOP_SEC_CODE
#include "MemMap.h"
/*------------------------------- end of file --------------------------------*/
