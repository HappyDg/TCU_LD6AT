/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*This file contains the implementation of the Diagnostic Service
  * Dispatcher module in Dcm. */

/*  MISRA-C:2004 Deviation List
 *
 * MISRA-1) Deviated Rule: 16.7 (required)
 *     A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the addressed
 *     object.
 *
 *     Reason:
 *     These function prototypes are defined by AUTOSAR 4.0.3 and thus can not be modified
 */

/*===============================[includes]======================================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */

#include <Dcm.h>                                                      /* Declaration of Dcm APIs */
#include <Dcm_Int.h>                                             /* Internal declarations of Dcm */
#include <Dcm_HsmDcm.h>                                   /* public statechart model definitions */
#include <Dcm_DspExternal.h>                           /* Callbacks provided by Central Diag SwC */

#include <ComM_Dcm.h>                                                  /* ComM interface for Dcm */
#include <SchM_Dcm.h>                                                  /* SchM interface for Dcm */

/*===========================[macro definitions]=================================================*/

/*=====================[external constants declarations]=========================================*/

/*=====================[internal constants declarations]=========================================*/

/*==================[internal function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

/** \brief Used to validate the input service request
 **
 ** \param[in] instIdx Current HSM instance Id
 ** \param[in] curSidConfig Current ServiceId config
 **
 ** \retval DCM_E_SERVICENOTSUPPORTED Service not supported in the current Protocol
 ** \retval DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION Service not supported in the current Session
 ** \retval DCM_E_SECURITYACCESSDENIED Service not supported in the current Security Level
 ** \retval DCM_E_BUSYREPEATREQUEST Tx buffer is not available in order to process the request
 **/
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DsdInternal_ValidateSvcReq(
  uint8 instIdx,
  P2VAR(Dcm_SidTabEntryConfigPtrType, AUTOMATIC, DCM_APPL_DATA) curSidConfig);

/** \brief Used to validate the input subservice request
 **
 ** \param[in] instIdx Current HSM instance Id
 ** \param[in] curSidConfig Current ServiceId config
 **
 ** \retval DCM_E_SUBFUNCTIONNOTSUPPORTED Subservice not supported in the current Protocol
 ** \retval DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION Subservice not supported in the current
 ** Session
 ** \retval DCM_E_SECURITYACCESSDENIED Subservice not supported in the current Security Level
 ** \retval DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT Incorrect message length in order to
 ** process the request
 **/
STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DsdInternal_ValidateSubSvcReq(
  uint8 instIdx,
  P2CONST(Dcm_SidTabEntryConfigType, AUTOMATIC, DCM_APPL_DATA) curSidConfig);

/** \brief Try to allocate the transmission(Tx) buffer allocated for a respective Tx Pdu Id.
 **
 ** This function has to be called from within the Hsm !
 **
 ** \retval E_OK Buffer is available
 ** \retval E_NOT_OK Buffer is already occupied
 **
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DsdInternal_AllocateTxBuffer(
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_APPL_DATA) CurHsmInfo);

#if (DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED == STD_ON )
/** \brief Used to verify the permissions from manufactrer notification
 ** functions
 **
 ** \param[in] instIdx Current HSM instance Id
 **
 ** \retval E_OK Permission is granted
 ** \retval E_NOT_OK Permission is not granted.Nrc has been returned from Notification function.
 ** \retval DCM_E_REQUEST_NOT_ACCEPTED Permission is not granted. Reject the diagnostic request.
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DsdInternal_ManufacturerNotification(uint8 instIdx);
#endif

#if (DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED == STD_ON )
/** \brief Used to verify the permissions from Supplier notification
 ** functions
 **
 ** \param[in] instIdx Current HSM instance Id
 **
 ** \retval E_OK Permission is granted
 ** \retval E_NOT_OK Permission is not granted.Nrc has been returned from Notification function.
 ** \retval DCM_E_REQUEST_NOT_ACCEPTED Permission is not granted. Reject the diagnostic request.
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DsdInternal_SupplierNotification(uint8 instIdx);
#endif
#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*=======================[external data declarations]============================================*/

/*=======================[internal data declarations]============================================*/

#if (DCM_DEV_ERROR_DETECT == STD_ON)
#define DCM_START_SEC_CONST_32
#include <MemMap.h>
/** \brief Global array holding the Negative Response Code information. Each bit position in the
 ** array element represents NRC code. Bit '1' represents valid NRC and Bit '0' represents
 ** ISO reserved NRC. The number '32U' in expression represents number of bits in one array element.
**/
STATIC CONST(uint32, DCM_CONST) Dcm_ValidNegativeResponseCodeMask[8] = {
    (1UL << DCM_E_GENERALREJECT)             | (1UL << DCM_E_SERVICENOTSUPPORTED) |
    (1UL << DCM_E_SUBFUNCTIONNOTSUPPORTED)   | (1UL << DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT) |
    (1UL << DCM_E_RESPONSETOOLONG),
    (1UL << (DCM_E_BUSYREPEATREQUEST % 32U)) | (1UL << (DCM_E_CONDITIONSNOTCORRECT % 32U)) |
    (1UL << (DCM_E_REQUESTSEQUENCEERROR % 32U)) |
    (1UL << (DCM_E_NORESPONSEFROMSUBNETCOMPONENT % 32U)) |
    (1UL << (DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION % 32U)) |
    (1UL << (DCM_E_REQUESTOUTOFRANGE % 32U)) | (1UL << (DCM_E_SECURITYACCESSDENIED % 32U)) |
    (1UL << (DCM_E_INVALIDKEY % 32U))        | (1UL << (DCM_E_EXCEEDNUMBEROFATTEMPTS % 32U)) |
    (1UL << (DCM_E_REQUIREDTIMEDELAYNOTEXPIRED % 32U)),
    0x00000000UL,
    (1UL << (DCM_E_UPLOADDOWNLOADNOTACCEPTED % 32U)) | (1UL << (DCM_E_TRANSFERDATASUSPENDED % 32U)) |
    (1UL << (DCM_E_GENERALPROGRAMMINGFAILURE % 32U)) |
    (1UL << (DCM_E_WRONGBLOCKSEQUENCECOUNTER % 32U)) |
    (1UL << (DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING % 32U)) |
    (1UL << (DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION % 32U))  |
    (1UL << (DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION % 32U)),
    (1UL << (DCM_E_RPMTOOHIGH % 32U))            | (1UL << (DCM_E_RPMTOOLOW % 32U)) |
    (1UL << (DCM_E_ENGINEISRUNNING % 32U))       | (1UL << (DCM_E_ENGINEISNOTRUNNING % 32U))    |
    (1UL << (DCM_E_ENGINERUNTIMETOOLOW % 32U))   | (1UL << (DCM_E_TEMPERATURETOOHIGH % 32U))    |
    (1UL << (DCM_E_TEMPERATURETOOLOW % 32U))     | (1UL << (DCM_E_VEHICLESPEEDTOOHIGH % 32U))   |
    (1UL << (DCM_E_VEHICLESPEEDTOOLOW % 32U))    | (1UL << (DCM_E_THROTTLE_PEDALTOOHIGH % 32U)) |
    (1UL << (DCM_E_THROTTLE_PEDALTOOLOW % 32U))  |
    (1UL << (DCM_E_TRANSMISSIONRANGENOTINNEUTRAL % 32U)) |
    (1UL << (DCM_E_TRANSMISSIONRANGENOTINGEAR % 32U)) |
    (1UL << (DCM_E_BRAKESWITCH_NOTCLOSED % 32U)) | (1UL << (DCM_E_SHIFTERLEVERNOTINPARK % 32U)) |
    (1UL << (DCM_E_TORQUECONVERTERCLUTCHLOCKED % 32U)) | (1UL << (DCM_E_VOLTAGETOOHIGH % 32U))  |
    (1UL << (DCM_E_VOLTAGETOOLOW % 32U)),
    0x00000000UL,
    0x00000000UL,
    0x00000000UL
  };
#define DCM_STOP_SEC_CONST_32
#include <MemMap.h>

#endif  /* DCM_DEV_ERROR_DETECT == STD_ON */

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

FUNC(void, DCM_CODE) Dcm_DsdInternal_DispatchSvcReq(
  DCM_PDL_DISPATCH_SERVICE_REQ(uint8 instIdx))
{
  Dcm_NegativeResponseCodeType curNrc = DCM_E_OK;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current HSM instance */
  CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
    = &DCM_HSM_CONFIG(instIdx);

  /* get configuration for current Rx Pdu Id */
  CONSTP2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig
    = &Dcm_RxPduIdConfig[curHsmInfo->rxPduId];

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) curMsgContext = &curHsmInfo->msgContext;

  /* get configuration of current transmission(Tx) buffer */
  P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig
    = &Dcm_BufferConfig[curHsmConfig->txBufferId];

  /* current ServiceId config */
  P2CONST(Dcm_SidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSidConfig = NULL_PTR;


  DBG_DCM_DSDINTERNAL_DISPATCHSVCREQ_ENTRY();

  /* set addressing type (functional, physical) */
  curMsgContext->msgAddInfo.reqType = curRxPduIdConfig->addrType;

  /* in default diagnostics session notify ComM about ongoing service request,
    * SWS Dcm163, Dcm139 sect. 9.2.7.1 */
  if ( Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)].
      SessionEntries[curHsmInfo->sesTabIdx].SesCtrl == DCM_DEFAULT_SESSION)
  {
    NetworkHandleType networkId = Dcm_ChannelId[curRxPduIdConfig->channelIdIndex].networkId;
    ComM_DCM_ActiveDiagnostic(networkId);
  }

  /* check if Tx buffer is available in order to process this request
   * and mark it as 'in use' */

  if (Dcm_DsdInternal_AllocateTxBuffer(curHsmInfo) != E_OK)
  {
    curHsmInfo->negativeResponseCode = DCM_E_BUSYREPEATREQUEST;
    
    /* as we don't call any service, we have to send the 'processing done' signal ourselves */
    (void) DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
      DCM_HSM_DCM_EV_PROC_DONE);
  }
  else
  {
#if (DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED == STD_ON )
    /* If manufacturer notification is enabled, calling these functions for getting permissions*/
    if(Dcm_DsdInternal_ManufacturerNotification(DCM_CUR_INST_ID(instIdx)) == E_OK)
#endif
    {
      /* Set current response code */
      curHsmInfo->negativeResponseCode = DCM_E_OK;

      /* Validate the input service request */
      curNrc = Dcm_DsdInternal_ValidateSvcReq(DCM_CUR_INST_ID(instIdx), &curSidConfig);

        
      /*
       * setup part of message context which is required for service AND error handling
       */
      /* verify if request data contains something other than ServiceId */
      if(Dcm_BufferConfig[curRxPduIdConfig->rxBufferId].bufferInfo->filledLen > 1U)
      {
        /* set request data pointer to received data without service Id */
        curMsgContext->reqData =
          &Dcm_BufferConfig[curRxPduIdConfig->rxBufferId].ptrBuffer[1];
      }
      else
      {
        /* place NULL_PTR in reqData pointer as there is no data after ServiceId */
        curMsgContext->reqData = NULL_PTR;
      }

      /* initialize with service id */
      curMsgContext->idContext = curHsmInfo->serviceId;

      /* set request data pointer to received data without service Id (needed in DcmConfirmation()
       * of pos and neg. responses) */
      curMsgContext->dcmRxPduId = curHsmInfo->rxPduId;

      /* if any precondition is not ok set the respective error code */
      if (curNrc != DCM_E_OK)
      {
        curHsmInfo->negativeResponseCode = curNrc;
        /* as we don't call any service, we have to send the 'processing done' signal ourselves */
        (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
          DCM_HSM_DCM_EV_PROC_DONE);
      }
      /* all preconditions are fulfilled */
      else
      {
        /* ENTER critical section */
        SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        /* set Protocol used from now on. In future version probably the handling of more than one
         * protocol at a time will be supported */
        Dcm_CurHsmConfig = curHsmConfig;

        /* LEAVE critical section */
        SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


        /* setup message context for diagnostic service function */

        /* set response ID in first byte of Tx curHsmInfo */
        curTxBufferConfig->ptrBuffer[0] = curHsmInfo->serviceId | DCM_SID_RESPONSE_BIT;

        /* ENTER critical section */
        SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        /* set reqDataLen of MsgContext to length of data in reception buffer without the
         * service Id (1 Byte) */
        curMsgContext->reqDataLen
          = Dcm_BufferConfig[curRxPduIdConfig->rxBufferId].bufferInfo->filledLen - 1U;

        /* buffer is already filled with the response ID.  So buffer fill is already 1 */
        curTxBufferConfig->bufferInfo->filledLen = 1U;

        /* LEAVE critical section */
        SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        /* set response buffer of current message context to allocated transmission buffer increase
         * address by one, as the filled length is already 1 */
        curMsgContext->resData = &curTxBufferConfig->ptrBuffer[1];

        /* reset length of reponse data */
        curMsgContext->resDataLen = 0U;

        /* if service request is configured to have a subfunction parameter handle
         * 'suppress positive response bit' and assign value for subServiceId */
        if ( (curSidConfig->SubfuncAvail == TRUE) && (curMsgContext->reqDataLen > 0U) )
        {
          if((curMsgContext->reqData[0] & DCM_SUPPOSRES_BITMASK) != 0U)
          {
            /* set suppress positive response information */
            curMsgContext->msgAddInfo.suppressPosResponse = TRUE;

            /* clear 'suppress positive message response' bit from subfunction parameter */
            curMsgContext->reqData[0] &= DCM_CLEAR_SUPPOSRES_BIT;
          }
          else
          {
            /* Subfunction supported for the service, but not requested in the current request */
            curMsgContext->msgAddInfo.suppressPosResponse = FALSE;
          }
          /*
           * If a service has subservice support update subservice Id into HsmInfoType irrespective of
           * other checks. The SubServiceId shall contain the ROE persistence bit.
           */
            curHsmInfo->subServiceId = curMsgContext->reqData[0];
        }
        else
        {
          /* Subfunction not supported for the requested service */
          curMsgContext->msgAddInfo.suppressPosResponse = FALSE;
        }

        /* set size of transmission buffer of current message context */
        curMsgContext->resMaxDataLen = curTxBufferConfig->size - 1U;

#if (DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED == STD_ON )
       /*If Supplier notification is enabled, calling these functions for getting permissions*/
        if( Dcm_DsdInternal_SupplierNotification(DCM_CUR_INST_ID(instIdx)) == E_OK )
#endif
        {
          /* Validate the subservice request */
          if ( (curSidConfig->ExtSrvHandler == NULL_PTR) && ( curSidConfig->NumSubServices > 0U ) &&
               (curSidConfig->SubfuncAvail == TRUE) )
          {
            curNrc = Dcm_DsdInternal_ValidateSubSvcReq(DCM_CUR_INST_ID(instIdx), curSidConfig);
          }

          /* if any precondition is not ok set the respective error code */
          if (curNrc != DCM_E_OK)
          {
            curHsmInfo->negativeResponseCode = curNrc;
            /* as we don't call any subservice, we have to send the 'processing done' signal ourselves */
            (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
              DCM_HSM_DCM_EV_PROC_DONE);
          }
          else
          {
            /* No failures during initial validation of service request */
            curHsmInfo->requestValidationStatus = TRUE;
            if (curSidConfig->ExtSrvHandler != NULL_PTR)
            {
              /* Set the service type to User implementation */
              curHsmInfo->dspService = FALSE;
            }

            if(curHsmInfo->serviceId == DCM_SID_SESSION_CONTROL)
            {
              /* value of Sub function */
              curHsmInfo->newSesCtrl = curMsgContext->reqData[0];
            }
#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
            if ( ( (curHsmInfo->serviceId == 0x22) || (curHsmInfo->serviceId == 0x2E) ||
                   (curHsmInfo->serviceId == 0x2F) ) &&
                  (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus != DCM_RET_CTRL_INACTIVE)
                )
            {
              if (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus == DCM_RET_CTRL_PENDING)
              {
                /* Because the state of the DIDs is undefined until control has been returned to ECU
                   for all, wait and return NRC REQUESTCORRECTLYRECEIVEDRESPONSEPENDING to tester */
                /* try again after timeout */
                DCM_HSM_INFO(instIdx).retryTimer = 1U;
              }
              else
              {
                /* Reset the flag to DCM_RET_CTRL_INACTIVE, as the state of DIDs is now known. */
                Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus = DCM_RET_CTRL_INACTIVE;
                /* !LINKSTO Dcm527,1, Dcm221,1 */
                /* Call the service processing function for service handlers */
                Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx) , DCM_INITIAL);
              }
            }
            else
#endif
            {
              /* !LINKSTO Dcm527,1, Dcm221,1 */
              /* Call the service processing function for service handlers */
              Dcm_DspInternal_SvcFunc(DCM_CUR_INST_ID(instIdx) , DCM_INITIAL);
            }
          }
        }
      }
    }
  }

  DBG_DCM_DSDINTERNAL_DISPATCHSVCREQ_EXIT();
}

/* Deviation MISRA-1 <+2> */
FUNC(void, DCM_CODE) Dcm_ExternalSetNegResponse(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NegativeResponseCodeType errorCode)
{
  DBG_DCM_EXTERNALSETNEGRESPONSE_ENTRY(pMsgContext,errorCode);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_SETNEGRESPONSE, DCM_E_UNINIT);
  }
  else if (pMsgContext == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_SETNEGRESPONSE, DCM_E_PARAM_POINTER);
  }
  /* Validating the range of errorCode*/
  else if(( Dcm_ValidNegativeResponseCodeMask[errorCode / 32U] & (1UL << (errorCode % 32U))) == 0U )
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_SETNEGRESPONSE, DCM_E_PARAM);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* Get the current context info used by Rx Pdu Id */
    CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
      = &DCM_HSM_INFO(Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(pMsgContext);
#endif

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    /* In case of async service execution this function is accessing
     * negativeResponseCode from a different task context other than the HSM */

    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

    /* if no error occured yet set negative response code of current Hsm */
    if (curHsmInfo->negativeResponseCode == DCM_E_OK)
    {
      curHsmInfo->negativeResponseCode = errorCode;
    }

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif
  }

  DBG_DCM_EXTERNALSETNEGRESPONSE_EXIT(pMsgContext,errorCode);
}

/* Deviation MISRA-1 <+2> */
FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  DBG_DCM_EXTERNALPROCESSINGDONE_ENTRY(pMsgContext);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_PROCESSINGDONE, DCM_E_UNINIT);
  }
  else if (pMsgContext == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_PROCESSINGDONE, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
    uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#else
#if (DCM_DEV_ERROR_DETECT == STD_OFF)
    TS_PARAM_UNUSED(pMsgContext);
#endif
#endif

    /* !LINKSTO Dcm762,1, Dcm.ExternalProcessingDone.ExternalServices,2 */
    /* Emit PROC_DONE here for external services (only external services use
      Dcm_ExternalProcessingDone according to the current design). */
    (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROC_DONE);
  }

  DBG_DCM_EXTERNALPROCESSINGDONE_EXIT(pMsgContext);
}
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)

FUNC(void, DCM_CODE) Dcm_DsdInternal_StartPagedProcessing(
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  DBG_DCM_DSDINTERNAL_STARTPAGEDPROCESSING_ENTRY(pMsgContext);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_STARTPAGEDPROCESSING, DCM_E_UNINIT);
  }
  else if (pMsgContext == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_STARTPAGEDPROCESSING, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* get length of data already stored in buffer */
    PduLengthType curTxBufferLen;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
    /* HSM instance */
    uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
    /* get configuration of current transmission(Tx) buffer */
    P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig =
                                             &Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId];

#if ((DCM_HSM_INST_MULTI_ENABLED == STD_OFF) && (DCM_DEV_ERROR_DETECT == STD_OFF))
    TS_PARAM_UNUSED(pMsgContext);
#endif

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    /* get configuration for current service table */
    CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
      = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

    /* get the context information current instance */
    P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* get length of data already stored in buffer */
    curTxBufferLen = curTxBufferConfig->bufferInfo->filledLen;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* init length information for keeping track of response total length */
    DCM_HSM_INFO(instIdx).sentLength = curTxBufferLen;
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
    {
      /* if handling is asynchronous, signal the asynchronous service dispatcher that the next
       * invocation of the service handler function should be done with an OpStatus of
       * DCM_UPDATE_PAGE only after all data has been processed/sent
       */
      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      curHsmInfo->asyncServiceOpState = DCM_ASYNC_PROCESSING_WAIT;

      /* LEAVE critical section */
      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    }
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
  }

  DBG_DCM_DSDINTERNAL_STARTPAGEDPROCESSING_EXIT(pMsgContext);
}

FUNC(void, DCM_CODE) Dcm_DsdInternal_ProcessPage(PduLengthType FilledPageLen)
{
  DBG_DCM_DSDINTERNAL_PROCESSPAGE_ENTRY(FilledPageLen);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_PROCESSPAGE, DCM_E_UNINIT);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
    /* get HSM instance which corresponds to the Tx Pdu Id used by current protocol
     *
     * This is ugly but from the function argument we cannot derive the current HSM instance. */
    uint8 instIdx = Dcm_CurProtocolId;
#endif

    /* get Tx buffer information used by current protocol */
    P2VAR(Dcm_BufferInfoType, AUTOMATIC, DCM_VAR) curTxBufInfo =
                                  Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo;
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    /* get the context information current instance */
    P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

    /* get configuration for current service table */
    CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
      = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

    /* update length information of response total length */
    DCM_HSM_INFO(instIdx).sentLength += FilledPageLen;

    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* update length information of transmission buffer */
    curTxBufInfo->filledLen += FilledPageLen;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Trigger the HSM to process the page. The dataState will be set to DCM_TX_DATA_READY in the
     * HSM as reaction to this event. */

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
    {
      /* if handling is asynchronous, signal the asynchronous service dispatcher that the next
       * invocation of the service handler function should be done with an OpStatus of
       * DCM_UPDATE_PAGE only after all data has been processed/sent
       */
      /* ENTER critical section */
      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      curHsmInfo->asyncServiceOpState = DCM_ASYNC_PROCESSING_WAIT;

      /* LEAVE critical section */
      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    }
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
    (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROCESS_PAGE);
  }

  DBG_DCM_DSDINTERNAL_PROCESSPAGE_EXIT(FilledPageLen);
}
#endif

/*==================[internal function definitions]==============================================*/

STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DsdInternal_ValidateSvcReq(
  uint8 instIdx,
  P2VAR(Dcm_SidTabEntryConfigPtrType, AUTOMATIC, DCM_APPL_DATA) curSidConfig)
{
  uint8_least i = 0U;
  uint8 sidIdxExt = 0U;
  uint8 modeRuleNrc;
  Dcm_NegativeResponseCodeType curNrc = DCM_E_OK;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current HSM instance */
  CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
    = &DCM_HSM_CONFIG(instIdx);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[curHsmConfig->sidTabId];

  P2CONST(Dcm_SidTabEntryConfigType, AUTOMATIC, DCM_CONST) sidConfig = NULL_PTR;

  DBG_DCM_DSDINTERNAL_VALIDATESVCREQ_ENTRY(DCM_INST(instIdx),curSidConfig);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* !LINKSTO Dcm193,1 */
  /* search list of configured services */
  while ( sidIdxExt < curSidTabConfig->NumEntries )
  {
    if ((curSidTabConfig->Entries[sidIdxExt]).ServiceId == curHsmInfo->serviceId)
    {
      curHsmInfo->sidTabEntryInd = sidIdxExt;

      break;
    }
    sidIdxExt++;
  }
  /* If service was not found in table of service functions configured for the current running
   * protocol, we have to send an appropriate negative response */
  if ( sidIdxExt >= curSidTabConfig->NumEntries )
  {
    curNrc = DCM_E_SERVICENOTSUPPORTED;
  }

  /*
   * check if service request is allowed in current session and security levels
   * and mode rule has not failed
   */
  if (curNrc == DCM_E_OK)
  {
    /* set configuration entry of this service Id */
    sidConfig = &(curSidTabConfig->Entries[sidIdxExt]);
    *curSidConfig  = sidConfig;

    /*
     * check if service request is allowed in current session
     */

    /* If no session control configuration is provided for the service,
       no check of session level shall be done */
    if (sidConfig->NumSesCtrls > 0U )
    {
      /* get current session type */
      const Dcm_SesCtrlType curSesCtrl = Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)].
      SessionEntries[curHsmInfo->sesTabIdx].SesCtrl;

      /*
       * check if service request is allowed in current session
       */
      for (i = 0U; i < sidConfig->NumSesCtrls; ++i)
      {
        if ((sidConfig->SesCtrls[i] == DCM_ALL_SESSION_LEVEL) ||
            (sidConfig->SesCtrls[i] == curSesCtrl))
        {
          break;
        }
      }
      if (i >= sidConfig->NumSesCtrls)
      {
        curNrc = DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION;
      }
    }

    /* check if service request is allowed in current security level
       If no security level configuration is provided for the service,
       no check of security level shall be done */
    if ((curNrc == DCM_E_OK) && (sidConfig->NumSecLevels > 0U ))
    {
      if (curHsmInfo->secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
      {
        /* get current security level */
        Dcm_SecLevelType curSecLevel = Dcm_SecTabConfig.Entries[curHsmInfo->secTabIdx].SecLevel;

        /*
         * check if service request is allowed with current security level
         */
        for (i = 0U; i < sidConfig->NumSecLevels; ++i)
        {
          if (sidConfig->SecLevels[i] == curSecLevel)
          {
            break;
          }
        }
        if (i >= sidConfig->NumSecLevels)
        {
          curNrc = DCM_E_SECURITYACCESSDENIED;
        }
      }
      else
      {
        curNrc = DCM_E_SECURITYACCESSDENIED;
      }
    }

    if ((curNrc == DCM_E_OK) && (sidConfig->ModeRuleSrvFunction != NULL_PTR))
    {
      /* invoke the mode rule function for the service */
      sidConfig->ModeRuleSrvFunction(&modeRuleNrc);

      /* if the mode rule resulted in failure modeRuleNrc will have the calculated nrc,
         else zero which implies there is no failure */
      curNrc = modeRuleNrc;
    }
  }

  DBG_DCM_DSDINTERNAL_VALIDATESVCREQ_EXIT(curNrc,DCM_INST(instIdx),curSidConfig);
  return curNrc;
}

STATIC FUNC(Dcm_NegativeResponseCodeType, DCM_CODE) Dcm_DsdInternal_ValidateSubSvcReq(
  uint8 instIdx,
  P2CONST(Dcm_SidTabEntryConfigType, AUTOMATIC, DCM_APPL_DATA) curSidConfig)
{
  uint8_least i = 0U;
  uint8 subSidIdxExt = 0U;
  uint8 subServiceId = 0U;
  uint8 modeRuleNrc;
  Dcm_NegativeResponseCodeType curNrc = DCM_E_OK;
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) curMsgContext = &curHsmInfo->msgContext;

  DBG_DCM_DSDINTERNAL_VALIDATESUBSVCREQ_ENTRY(DCM_INST(instIdx),curSidConfig);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(instIdx);
#endif

  if(curMsgContext->reqDataLen > 0U)
  {
    /* Mask the ROE Persistence bit. */
    if(curHsmInfo->serviceId == DCM_UDS_SID_ROE)
    {
      subServiceId = curMsgContext->reqData[0] & DCM_CLEAR_ROE_PERSISTENCE_BIT;
    }
    else
    {
      subServiceId = curMsgContext->reqData[0];
    }

    /* search list of configured subservices */
    while ( subSidIdxExt < curSidConfig->NumSubServices )
    {
      if (curSidConfig->SubServices[subSidIdxExt].SubServiceId == subServiceId)
      {
        break;
      }
      subSidIdxExt++;
    }
    /* If subservice was not found for the current running
     * service, we have to send an appropriate negative response */
    if ( subSidIdxExt >= curSidConfig->NumSubServices )
    {
      curNrc = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
  }
  else
  {
    curNrc = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  /* If no session control configuration is provided for the subservice of current ,
   *  running service , no check of session level shall be done 
   * The verification done only if service contains sub services 
   * Also if no session control configuration is provided for the subservice, no check of session
   * level shall be done */
  if (((curNrc == DCM_E_OK) && (curSidConfig->ServiceId != DCM_SID_SESSION_CONTROL)) &&
      (curSidConfig->SubServices[subSidIdxExt].NumSubSesCtrls > 0U ))
  {
    /* get the current session type */
    const Dcm_SesCtrlType curSesCtrl = Dcm_SesTabConfig[DCM_CUR_INST_ID(instIdx)].
    SessionEntries[curHsmInfo->sesTabIdx].SesCtrl;

    /* check if sub-service request is allowed in current session */
    for (i = 0U; i < curSidConfig->SubServices[subSidIdxExt].NumSubSesCtrls; ++i)
    {
      if ( (curSidConfig->SubServices[subSidIdxExt].SubSesCtrls[i] == DCM_ALL_SESSION_LEVEL) ||
           (curSidConfig->SubServices[subSidIdxExt].SubSesCtrls[i] == curSesCtrl) )
      {
        break;
      }
    }
    if (i >= curSidConfig->SubServices[subSidIdxExt].NumSubSesCtrls)
    {
      curNrc = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
    }
  }

  /* check if subservice request is allowed in current security level
     If no security level configuration is provided for the service,
     check for sub-service security level */
  if ((curNrc == DCM_E_OK) && (curSidConfig->SubServices[subSidIdxExt].NumSubSecLevels > 0U))
  {
    if (curHsmInfo->secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
    {
      /* get current security level */
      Dcm_SecLevelType curSecLevel =
                 Dcm_SecTabConfig.Entries[curHsmInfo->secTabIdx].SecLevel;
      /*
       * check if service request is allowed with current security level
       */
      for (i = 0U; i < curSidConfig->SubServices[subSidIdxExt].NumSubSecLevels; ++i)
      {
        if (curSidConfig->SubServices[subSidIdxExt].SubSecLevels[i] == curSecLevel)
        {
          break;
        }
      }
      if (i >= curSidConfig->SubServices[subSidIdxExt].NumSubSecLevels)
      {
        curNrc = DCM_E_SECURITYACCESSDENIED;
      }
    }
    else
    {
      curNrc = DCM_E_SECURITYACCESSDENIED;
    }
  }

  if ((curNrc == DCM_E_OK) &&
      (curSidConfig->SubServices[subSidIdxExt].ModeRuleSubSrvFunction != NULL_PTR))
  {
    /* invoke the mode rule function for the sub-service */
    curSidConfig->SubServices[subSidIdxExt].ModeRuleSubSrvFunction(&modeRuleNrc);

    /* if the mode rule resulted in failure modeRuleNrc will have the calculated nrc,
       else zero which implies there is no failure */
    curNrc = modeRuleNrc;
  }

  DBG_DCM_DSDINTERNAL_VALIDATESUBSVCREQ_EXIT(curNrc,DCM_INST(instIdx),curSidConfig);
  return curNrc;
}

/* try to allocate a transmission buffer */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DsdInternal_AllocateTxBuffer(
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_APPL_DATA) CurHsmInfo)
{
  Std_ReturnType retVal = E_NOT_OK;

  /* get configuration for current Rx Pdu Id */
  P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig
    = &Dcm_RxPduIdConfig[CurHsmInfo->rxPduId];

  /* get configuration of current transmission(Tx) buffer */
  P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig =
    &Dcm_BufferConfig[DCM_HSM_CONFIG(curRxPduIdConfig->protocolId).txBufferId];

  /* get status information of current transmission(Tx) buffer */
  P2VAR(Dcm_BufferInfoType, AUTOMATIC, DCM_VAR) curTxBufInfo = curTxBufferConfig->bufferInfo;

  /* get configuration of current reception(Rx) buffer */
  P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curRxBufferConfig =
    &Dcm_BufferConfig[curRxPduIdConfig->rxBufferId];

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo =
    &DCM_HSM_INFO(curRxPduIdConfig->protocolId);

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) curMsgContext = &curHsmInfo->msgContext;

  DBG_DCM_DSDINTERNAL_ALLOCATETXBUFFER_ENTRY(CurHsmInfo);

  /*
   * ENTER critical section
   */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* check if transmission(Tx) buffer is IDLE or identical to reception(Rx) buffer */
  if ((curTxBufInfo->state == DCM_BUF_IDLE) || (curTxBufferConfig == curRxBufferConfig))
  {
    /* allocate buffer and make it available to the application by setting the appropriate
     * information within the message context */
    if (curRxBufferConfig->bufferInfo->state == DCM_BUF_ROE)
    {
      curTxBufInfo->state = DCM_BUF_ROE;
      curMsgContext->msgAddInfo.messageType = DCM_ROE;
    }
    else
    {
      curTxBufInfo->state = DCM_BUF_TX;
      curMsgContext->msgAddInfo.messageType = DCM_NORMAL;
    }
    retVal = E_OK;
  }

  /*
   * LEAVE critical section
   */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();


  DBG_DCM_DSDINTERNAL_ALLOCATETXBUFFER_EXIT(retVal,CurHsmInfo);
  return retVal;
}

#if (DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DsdInternal_ManufacturerNotification(uint8 instIdx)
{
  Std_ReturnType MftNotifStatus;
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) CurHsmInfo= &DCM_HSM_INFO(instIdx);
  uint8 Sid = CurHsmInfo->serviceId;
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
    = &DCM_HSM_INFO(instIdx).msgContext;
  /* get configuration for current Rx Pdu Id */
  CONSTP2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig
    = &Dcm_RxPduIdConfig[CurHsmInfo->rxPduId];
  uint16 DataSize = Dcm_BufferConfig[curRxPduIdConfig->rxBufferId].bufferInfo->filledLen - 1U;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RequestData =
                                       &Dcm_BufferConfig[curRxPduIdConfig->rxBufferId].ptrBuffer[1];
  uint8 ReqType = Dcm_RxPduIdConfig[CurHsmInfo->rxPduId].addrType;
  uint16 SourceAddress = Dcm_RxPduIdConfig[CurHsmInfo->rxPduId].TesterSourceAddr;
  Dcm_NegativeResponseCodeType curNrc = DCM_E_OK;
  Dcm_NegativeResponseCodeType aggregatedNrc = DCM_E_GENERALREJECT;
                                     /* default value in case no Indication() operation or */
                                     /* Rte_DcmManufacturerNotification() function sets a */
                                     /* proper NRC */

/*Verification of the Manufacturer Application environment/permission*/
#if (DCM_INCLUDE_RTE == STD_ON)
  uint8_least i;
  Std_ReturnType NotificationRetVal = E_OK;

  DBG_DCM_DSDINTERNAL_MANUFACTURERNOTIFICATION_ENTRY(DCM_INST(instIdx));

  MftNotifStatus = E_OK;
  /* Execute the  Xxx_ManufacturerIndication() for all configured ports */
  for (i = 0U; i < DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE; ++i)
  {
    NotificationRetVal =
    Dcm_RteManufacturerNotificationTable[i].Indication
                                      (Sid, RequestData, DataSize, ReqType, SourceAddress, &curNrc);

    /* If at least one of the Xxx_ManufacturerIndication() functions returns
        DCM_E_REQUEST_NOT_ACCEPTED, the Request Indication Status shall be
        DCM_E_REQUEST_NOT_ACCEPTED */
    if ( NotificationRetVal == DCM_E_REQUEST_NOT_ACCEPTED )
    {
      MftNotifStatus = DCM_E_REQUEST_NOT_ACCEPTED;
      break;
    }

    else
    {
      if (NotificationRetVal == E_NOT_OK)
      {
        /* check if we have a misbehaving Indication() operation that violates Dcm463 and Dcm694 ...
        */
        if (curNrc == DCM_E_OK)
        {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
          DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_MANUFACTURERNOTIFICATION,
            DCM_E_INTERFACE_RETURN_VALUE);
#endif
        }
        else
        {
          aggregatedNrc = curNrc;
        }

        MftNotifStatus = E_NOT_OK;
      }
      /* If RequestIndicationRetVal == E_OK, then the previous value of
      RequestIndicationStatus shall not be modified. */
    }
  }
#else
  DBG_DCM_DSDINTERNAL_MANUFACTURERNOTIFICATION_ENTRY(DCM_INST(instIdx));

  MftNotifStatus = Rte_DcmManufacturerNotification(Sid, RequestData, DataSize, ReqType,
                    SourceAddress, &curNrc);

  /* check if we have a misbehaving Rte_DcmManufacturerNotification() function that violates Dcm463
   * and Dcm694 ... */
  if ((MftNotifStatus == E_NOT_OK) && (curNrc == DCM_E_OK))
  {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_MANUFACTURERNOTIFICATION,
      DCM_E_INTERFACE_RETURN_VALUE);
#endif
  }
  else
  {
    aggregatedNrc = curNrc;
  }
#endif /* DCM_INCLUDE_RTE == STD_ON */

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  switch (MftNotifStatus)
  {
    case DCM_E_REQUEST_NOT_ACCEPTED:
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_PROC_ABORT);


      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      if (pMsgContext->msgAddInfo.messageType == DCM_NORMAL)
      {
        /* Current Request processing is finished */
        DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
        Dcm_ReqProcessing = FALSE;
      }
      else if ((pMsgContext->msgAddInfo.messageType == DCM_ROE) || (pMsgContext->msgAddInfo.messageType == DCM_ROE_FINAL))
      {
        /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
        DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
        Dcm_ROEProcessing = DCM_ROE_NONE;
      }
      /* CHECK: NOPARSE */
      else
      {
       /* Do nothing */
      }
      /* CHECK: PARSE */

      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      break;

    case E_NOT_OK:
      if (CurHsmInfo->negativeResponseCode == DCM_E_OK)
      {
        CurHsmInfo->negativeResponseCode = aggregatedNrc;
      }
      /* CHECK: NOPARSE */
      else
      {
        /* Do nothing if another NRC has previously been set. This is a defensive branch. */
      }
      /* CHECK: PARSE */

      (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
        DCM_HSM_DCM_EV_PROC_DONE);
      break;

    default:
      /* Do Nothing */
      break;
  }

  DBG_DCM_DSDINTERNAL_MANUFACTURERNOTIFICATION_EXIT(MftNotifStatus,DCM_INST(instIdx));
  return MftNotifStatus;
}
#endif/*(DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED == STD_ON )*/

#if (DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DsdInternal_SupplierNotification(uint8 instIdx)
{
  Std_ReturnType SupplNotifStatus;
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) CurHsmInfo= &DCM_HSM_INFO(instIdx);
  uint8 Sid = CurHsmInfo->serviceId;
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
    = &DCM_HSM_INFO(instIdx).msgContext;
  uint16 DataSize = (uint16)(pMsgContext->reqDataLen);
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RequestData = pMsgContext->reqData;
  uint8 ReqType = Dcm_RxPduIdConfig[CurHsmInfo->rxPduId].addrType;
  uint16 SourceAddress = Dcm_RxPduIdConfig[CurHsmInfo->rxPduId].TesterSourceAddr;
  Dcm_NegativeResponseCodeType curNrc = DCM_E_OK;
  Dcm_NegativeResponseCodeType aggregatedNrc = DCM_E_GENERALREJECT;
                                     /* default value in case no Indication() operation or */
                                     /* Rte_DcmManufacturerNotification() function sets a */
                                     /* proper NRC */

/*Verification of the Supplier Application environment/permission */
#if (DCM_INCLUDE_RTE == STD_ON)
  uint8_least i;
  Std_ReturnType NotificationRetVal = E_OK;

  DBG_DCM_DSDINTERNAL_SUPPLIERNOTIFICATION_ENTRY(DCM_INST(instIdx));

  SupplNotifStatus = E_OK;
  /* Execute the  Xxx_SupplierIndication() for all configured ports */
  for (i = 0U; i < DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE; ++i)
  {
    NotificationRetVal =
    Dcm_RteSupplierNotificationTable[i].Indication
                                    (Sid, RequestData, DataSize, ReqType, SourceAddress, &curNrc);

    /* If at least one of the Xxx_SupplierIndication() functions returns DCM_E_REQUEST_NOT_ACCEPTED,
       the Request Indication Status shall be DCM_E_REQUEST_NOT_ACCEPTED */
    if ( NotificationRetVal == DCM_E_REQUEST_NOT_ACCEPTED )
    {
      SupplNotifStatus = DCM_E_REQUEST_NOT_ACCEPTED;
      break;
    }

    else
    {
      if (NotificationRetVal == E_NOT_OK)
      {
        /* check if we have a misbehaving Indication() operation that violates Dcm518 and Dcm693 ...
        */
        if (curNrc == DCM_E_OK)
        {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
          DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_SUPPLIERNOTIFICATION,
            DCM_E_INTERFACE_RETURN_VALUE);
#endif
        }
        else
        {
          aggregatedNrc = curNrc;
        }
        SupplNotifStatus = E_NOT_OK;
      }
      /* If RequestIndicationRetVal == E_OK, then the previous value of
      NotificationStatus shall not be modified. */
    }
  }
#else
  DBG_DCM_DSDINTERNAL_SUPPLIERNOTIFICATION_ENTRY(DCM_INST(instIdx));

  SupplNotifStatus = Rte_DcmSupplierNotification(Sid, RequestData, DataSize, ReqType, SourceAddress,
                      &curNrc);

  /* check if we have a misbehaving Rte_DcmSupplierNotification() function that violates Dcm518 and
     Dcm693 ... */
  if ((SupplNotifStatus == E_NOT_OK) && (curNrc == DCM_E_OK))
  {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_SUPPLIERNOTIFICATION, DCM_E_INTERFACE_RETURN_VALUE);
#endif
  }
  else
  {
    aggregatedNrc = curNrc;
  }
#endif /* DCM_INCLUDE_RTE == STD_ON */

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  switch (SupplNotifStatus)
  {
    case DCM_E_REQUEST_NOT_ACCEPTED:
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx), DCM_HSM_DCM_EV_PROC_ABORT);

      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      if (pMsgContext->msgAddInfo.messageType == DCM_NORMAL)
      {
        /* Current Request processing is finished */
        DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
        Dcm_ReqProcessing = FALSE;
      }
      else if ((pMsgContext->msgAddInfo.messageType == DCM_ROE) || (pMsgContext->msgAddInfo.messageType == DCM_ROE_FINAL))
      {
        /* If currently stopping Request processing operation was ROE, unset ROE processing flag */
        DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_NONE));
        Dcm_ROEProcessing = DCM_ROE_NONE;
      }
      /* CHECK: NOPARSE */
      else
      {
       /* Do nothing */
      }
      /* CHECK: PARSE */

      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      break;

    case E_NOT_OK:
      if (CurHsmInfo->negativeResponseCode == DCM_E_OK)
      {
        CurHsmInfo->negativeResponseCode = aggregatedNrc;
      }
      /* CHECK: NOPARSE */
      else
      {
        /* Do nothing if another NRC has previously been set. This is a defensive branch. */
      }
      /* CHECK: PARSE */

      (void)DCM_HSMEMITTOSELFINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
        DCM_HSM_DCM_EV_PROC_DONE);
      break;

    default:
      /* Do Nothing */
      break;
  }

  DBG_DCM_DSDINTERNAL_SUPPLIERNOTIFICATION_EXIT(SupplNotifStatus,DCM_INST(instIdx));
  return SupplNotifStatus;
}
#endif/*(DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED == STD_ON )*/

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]================================================================*/

