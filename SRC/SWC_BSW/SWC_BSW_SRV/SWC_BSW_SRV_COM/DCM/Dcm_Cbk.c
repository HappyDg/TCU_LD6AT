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

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 12.5 (required)
 *     The operands of a logical && or || shall be primary-expressions.
 *
 *     Reason:
 *     Misra has an exception that whenever an expression consists of either a sequence of only
 *     logical && or a sequence of only logical && or logical ||, extra parentheses are not required
 *
 */

 /*==================[inclusions]=================================================================*/

#include <Dcm_Trace.h>
#include <ComStack_Types.h>                                 /* AUTOSAR Communication Stack types */

#include <Dcm.h>                                                  /* Definition of DCM_MODULE_ID */
#include <Dcm_Cbk.h>                                         /* Declaration of Dcm callback APIs */
#include <Dcm_DspExternal.h>                           /* Callbacks provided by Central Diag SwC */
#include <Dcm_Int.h>                                               /* Module intenal definitions */
#include <Dcm_HsmDcm.h>                                   /* public statechart model definitions */
#include <TSMem.h>                                        /* EB specific memory functions */
#include <SchM_Dcm.h>                                                  /* SchM interface for Dcm */

/*==================[macros]=====================================================================*/

/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/

/** \brief Internal function to copy the requested transmit data from its internal transmit buffer
 ** to the location specified by the PduInfoPtr.
 **
 ** \param[inout] PduInfoPtr    Pointer to a PduInfoType, which indicates the number of bytes to be
 **                             copied (SduLength) and the location where the data
 **                             have to be copied to (SduDataPtr)
 ** \param[inout] RetryInfoPtr  If the transmitted TP I-PDU does not support the retry
 **                             feature a NULL_PTR can be provided. This indicates that the copied
 **                             transmit data can be removed from the buffer after
 **                             it has been copied.
 ** \param[inout] TxDataCntPtr      Remaining Tx data after completion
 ** \param[inout] pNoRetryRequired  Indicates whether retry is required or not
 ** \param[in] instIdx              Current HSM instance Id
 
 ** \retval BUFREQ_OK         Data has been copied to the transmit buffer completely as requested 
 ** \retval BUFREQ_E_NOT_OK   Data has not been copied. Request failed, in case the corresponding
 **                           I-PDU was stopped.
 **/
STATIC FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CbkInternal_CopyTxData(
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr,
  P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) pNoRetryRequired,
  uint8 instIdx);
/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

FUNC(BufReq_ReturnType, DCM_CODE) Dcm_StartOfReception(
  PduIdType DcmRxPduId, PduLengthType TpSduLength,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  DBG_DCM_STARTOFRECEPTION_ENTRY(DcmRxPduId,TpSduLength,RxBufferSizePtr);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_STARTOFRECEPTION, DCM_E_UNINIT);
  }
  else if (DcmRxPduId >= DCM_NUM_RX_PDU_ID)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_STARTOFRECEPTION, DCM_E_PARAM);
  }
  else if (RxBufferSizePtr == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_STARTOFRECEPTION, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* pointer Rx Pdu Id configuration for current Rx Pdu Id */
    P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig =
      &Dcm_RxPduIdConfig[DcmRxPduId];
    /* pointer to buffer configuration for current Rx Pdu Id */
    P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curRxBufferConfig =
      &Dcm_BufferConfig[Dcm_RxPduIdConfig[DcmRxPduId].rxBufferId];
    /* pointer to status information for currently used Rx buffer */
    P2VAR(Dcm_BufferInfoType, AUTOMATIC, DCM_VAR) curRxBufferInfo = curRxBufferConfig->bufferInfo;
    /* This is used for getting the currently processing Rxpduid */
    P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curProcessingReqHsmInfo =
      &DCM_HSM_INFO(Dcm_CurProtocolId);

    /* ENTER critical section, make access to PduId and buffer state variables atomic. They may be
     * accessed also by another concurrent call of this function
     */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Check if service request is invoked with TpSduLength equal to 0 */
    if (TpSduLength == 0U)
    {
      /* Dcm.RequestLength.Zero : When the API Dcm_StartOfReception is  invoked with TpSduLength
       * equal to 0, the value BUFREQ_OK shall be returned and RxBufferSizePtr shall be set to the
       * free size of the Rx buffer.
       */
      *RxBufferSizePtr = curRxBufferConfig->size;
      retVal = BUFREQ_OK;
    }
    else if (Dcm_RxEnabled[curRxPduIdConfig->channelIdIndex] == FALSE)
    {
      /* In the NoCom mode the Dcm disables the reception of any request */
      retVal = BUFREQ_E_NOT_OK;
    }
    /* Check if service request fits in RX buffer If not: return error code */
    else if (TpSduLength > (curRxBufferConfig->size))
    {
      /* do not report DET error here as "DCM_E_INTERFACE_BUFFER_OVERFLOW"
       * relates to _application_ interface errors
       */

      /* Dcm444: If the requested size is larger than the buffer available in the DCM, the function
       * Dcm_StartOfReception() shall return BUFREQ_E_OVFL
       */
      retVal = BUFREQ_E_OVFL;
    }
    else if ((Dcm_RxPduIdState[DcmRxPduId] != DCM_RX_PDU_ID_IDLE) ||
             ((Dcm_ROEProcessing != DCM_ROE_NONE) && (Dcm_ROEEnqueueEvent == DCM_ROE_NO_EVENT)) ||
             (((curRxBufferInfo->state != DCM_BUF_IDLE) || (Dcm_ReqProcessing == TRUE))&&
             (curProcessingReqHsmInfo->rxPduId == DcmRxPduId)))
    {
      /* Dcm137: While processing an ROE event, any additional requests (external and internal)
       * shall be rejected with the same or lower priority of its Protocol Table.
       */

      /* Dcm557: When processing a diagnostic request, the DCM module shall reject any new
       * diagnostic request with the same DcmRxPudId until the current processing is over.
       * function Dcm_StartOfReception() shall return BUFREQ_E_NOT_OK
       */

      retVal = BUFREQ_E_NOT_OK;
    }
    /* If current request is in process and If there is a new diagnostic
       request with different Rxpduid */
    else if ((Dcm_ReqProcessing == TRUE) && (curProcessingReqHsmInfo->rxPduId != DcmRxPduId))
    {
      /* When processing a diagnostic request, the DCM module shall reject
       * (Dcm_StartOfReception() shall return BUFREQ_E_NOT_OK) any new request using a different
       * DcmRxPduId until the current diagnostic request processing is over */
      retVal = BUFREQ_E_NOT_OK;
    }
    else
    {
      /* Holds the current HSM information */
      P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo =
        &DCM_HSM_INFO(curRxPduIdConfig->protocolId);
        
      /* Holds the Tx, TxConf information for the current Main Connection */        
      VAR(Dcm_TxPduIdConfigType, DCM_VAR) txConfig = Dcm_TxPduIds[curRxPduIdConfig->connectionId];
      
      /* Update current RxPduId as well as corresponding TxPduId and TxConfirmationPduId in HSM information */
      curHsmInfo->rxPduId = DcmRxPduId;
      curHsmInfo->txPduId = txConfig.txPduId;
      curHsmInfo->txConfirmationPduId = txConfig.txConfirmationPduId;

      /* allocate reception buffer if it is idle and we are potentially able to send a positive
       * or negative response
       */

      /* allocate Rx buffer */
      curRxBufferInfo->state              = DCM_BUF_RX;
      /* store the received DataLength */
      curRxBufferInfo->filledLen          = TpSduLength;
      /* remember rxPduId */
      curRxBufferInfo->originatingRxPduId = DcmRxPduId;
      /* set current dataMark to 0 to signal where to copy new data. */
      curRxBufferInfo->dataMark = 0U;

      /* set Rx Pdu Id state to busy so that ROE or PR cannot interfer with this RxPduId */
      Dcm_RxPduIdState[DcmRxPduId] = DCM_RX_PDU_ID_BUSY;

      /* Update size of the allocated buffer to caller */
      *RxBufferSizePtr = curRxBufferConfig->size;
      /* if S3 timer is running, stop the timer and set the flag s3Restart, to restart timer if
       * reception fails
       */
      if (curHsmInfo->timer3 > 0U)
      {
        curHsmInfo->timer3 = 0U;
        curHsmInfo->s3Restart = TRUE;
      }

      /* Currently Request processing is going on */
      DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(TRUE));
      Dcm_ReqProcessing = TRUE;

      /* Update CurProtocolId */
      DBG_DCM_CURPROTOCOLID((Dcm_CurProtocolId),(curRxPduIdConfig->protocolId));
      Dcm_CurProtocolId = curRxPduIdConfig->protocolId;

      retVal = BUFREQ_OK;
    }
    /* !LINKSTO Dcm.EB.StartOfReception.BUFREQ_E_BUSY,1 */
    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  DBG_DCM_STARTOFRECEPTION_EXIT(retVal,DcmRxPduId,TpSduLength,RxBufferSizePtr);
  return retVal;
}

FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyRxData(
  PduIdType DcmRxPduId, P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  DBG_DCM_COPYRXDATA_ENTRY(DcmRxPduId,PduInfoPtr,RxBufferSizePtr);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_COPYRXDATA, DCM_E_UNINIT);
  }
  else if (DcmRxPduId >= DCM_NUM_RX_PDU_ID)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_COPYRXDATA, DCM_E_PARAM);
  }
  else if ((PduInfoPtr == NULL_PTR) || (RxBufferSizePtr == NULL_PTR))
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_COPYRXDATA, DCM_E_PARAM_POINTER);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* pointer to buffer configuration for current Rx Pdu Id */
    P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curRxBufferConfig =
      &Dcm_BufferConfig[Dcm_RxPduIdConfig[DcmRxPduId].rxBufferId];
    /* pointer to Buffer information for currently used Rx buffer */
    P2VAR(Dcm_BufferInfoType, AUTOMATIC, DCM_VAR) curRxBufferInfo = curRxBufferConfig->bufferInfo;

    /* ENTER critical section, make access to PduId and buffer state variables atomic. They may be
     * accessed also by another concurrent call of this function
     */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* if receive session ongoing for this RxPduId */
    if ((curRxBufferInfo->state) == DCM_BUF_RX)
    {
      /* Check if service request is  invoked with SduLength of PduInfoPtr equal to 0 */
      if ((PduInfoPtr->SduLength == 0U) || (PduInfoPtr->SduDataPtr == NULL_PTR))
      {
        /* Dcm.RequestLength.Zero : When the API Dcm_StartOfReception is invoked with
         * TpSduLength equal to 0, the value BUFREQ_OK shall be returned and RxBufferSizePtr shall
         * be set to the free size of the Rx buffer.
         */
        /* Dcm.CopyRxData.BufferSize: Return remaining free place in receive buffer after
         * completion of this call
         */
        /* Update size of the allocated buffer to caller */
        *RxBufferSizePtr = (curRxBufferConfig->size) - (curRxBufferInfo->dataMark);
        retVal = BUFREQ_OK;
      }
      /* Dcm443: If Dcm_StartOfReception() returns BUFREQ_OK, the further call to
       * Dcm_CopyRxData() shall copy the data from the buffer provided inPduInfoPointer
       * parameter)  to the DCM buffer and update the RxBufferSizePtr parameter with
       * remaining free place in DCM receive buffer after completion of this call.
       */
      else
      {
        /* Checking whether the current requested data length is within the range of total
         * diagnostic request length stored during Dcm_StartOfReception() API . If not, return
         * BUFREQ_E_NOT_OK and wait for the Dcm_RxIndication() call to signal the failure
         * of reception.
         */
        if(((curRxBufferInfo->dataMark)+(PduInfoPtr->SduLength)) <= (curRxBufferInfo->filledLen))
        {
          TS_MemCpy(&(curRxBufferConfig->ptrBuffer[curRxBufferInfo->dataMark]),
              PduInfoPtr->SduDataPtr, (uint16)PduInfoPtr->SduLength);
          /* Update dataMark */
          curRxBufferInfo->dataMark = (curRxBufferInfo->dataMark) + (PduInfoPtr->SduLength);

          /* Return remaining free place in receive buffer after completion of this call */
          *RxBufferSizePtr = (curRxBufferConfig->size) - (curRxBufferInfo->dataMark);

          retVal = BUFREQ_OK;
        }
        else
        {
          /* As Dcm does not support paged buffer reception, this condition will never happen.
           * Instead, an error BUFFREQ_E_NOT_OK might be received since an illegal condition will
           * have been reached (the PduR tries to give the Dcm more data than it notified
           * in Dcm_StartOfReception).
           */
          retVal = BUFREQ_E_NOT_OK;
        }
      }
    }
    else
    {
      /* No reception initiated on this RxPduId */
      *RxBufferSizePtr = 0U;
      /* Dcm342: ReStart of S3 timer is not required in CopyRxData, as for success or failure in
       * reception of data, PduR has to invoke TpRxIndication
       */
    }
    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  DBG_DCM_COPYRXDATA_EXIT(retVal,DcmRxPduId,PduInfoPtr,RxBufferSizePtr);
  return retVal;
}

FUNC(void, DCM_CODE) Dcm_TpRxIndication(PduIdType DcmRxPduId, NotifResultType Result)
{
  DBG_DCM_TPRXINDICATION_ENTRY(DcmRxPduId,Result);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_TPRXINDICATION, DCM_E_UNINIT);
  }
  else if ((DcmRxPduId >= DCM_NUM_RX_PDU_ID) || (Result > DCM_INVALID_NTFRSLT))
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_TPRXINDICATION, DCM_E_PARAM);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    /* pointer Rx Pdu Id configuration for this Rx Pdu Id */
    P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig;

    /* pointer to status information for currently used Rx buffer */
    P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curRxBufferConfig;

    /* Holds the current HSM information */
    P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo;

    /* pointer Rx Pdu Id configuration for this Rx Pdu Id */
    curRxPduIdConfig  = &Dcm_RxPduIdConfig[DcmRxPduId];
    /* pointer to status information for currently used Rx buffer */
    curRxBufferConfig = &Dcm_BufferConfig[curRxPduIdConfig->rxBufferId];

    /* pointer to HsmInfo for this Tx Pdu Id (Protocol) */
    curHsmInfo = &DCM_HSM_INFO(curRxPduIdConfig->protocolId);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if((Result == NTFRSLT_OK) && ((curRxBufferConfig->bufferInfo->filledLen) !=
      (curRxBufferConfig->bufferInfo->dataMark)))
    {
      DCM_DET_REPORT_ERROR(DCM_SVCID_TPRXINDICATION, DCM_E_INVALID_REQLEN);
    }
    else if((curRxBufferConfig->bufferInfo->state) != DCM_BUF_RX)
    {
      DCM_DET_REPORT_ERROR(DCM_SVCID_TPRXINDICATION, DCM_E_PARAM);
    }
    else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
    {
      /* ENTER critical section */
      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      /* if receive session ongoing for this RxPduId */
      if ((curRxBufferConfig->bufferInfo->state) == DCM_BUF_RX)
      {
        /* if there is any error in reception or there is an ongoing ROE processing [Dcm137]
         * or received request is 'TesterPresent' service with suppress positive response
         */
        if ((Result != NTFRSLT_OK) ||
            ((Dcm_ROEProcessing != DCM_ROE_NONE) && (Dcm_ROEEnqueueEvent == DCM_ROE_NO_EVENT)) ||
            ((curRxBufferConfig->bufferInfo->filledLen == DCM_TESTER_PRESENT_REQ_LEN) &&
             (curRxBufferConfig->ptrBuffer[DCM_DIAG_REQ_SID_IND] == DCM_SID_TESTER_PRESENT) &&
             (curRxBufferConfig->ptrBuffer[DCM_DIAG_REQ_SUBFUNC_IND] == DCM_SUPPOSRES_BITMASK)
             /* Deviation MISRA-1 */
            )
           )
        {
          /* Release the reception buffer only if it was allocated for the RxPdu */
          if (Dcm_RxPduIdState[DcmRxPduId] != DCM_RX_PDU_ID_IDLE)
          {
            curRxBufferConfig->bufferInfo->state = DCM_BUF_IDLE;

            /* Current Request processing is finished */
            DBG_DCM_REQPROCESSING((Dcm_ReqProcessing),(FALSE));
            Dcm_ReqProcessing = FALSE;
          }

          /* ReStart S3 timer if was stopped in Dcm_StartOfReception()*/
          if (curHsmInfo->s3Restart == TRUE)
          {
            curHsmInfo->timer3 = DCM_S3SERVER_TICK_DEFAULT;
          }
        }

        /* Free Rx Pdu ID */
        Dcm_RxPduIdState[DcmRxPduId] = DCM_RX_PDU_ID_IDLE;
        /* Reset the data index  dataMark */
        curRxBufferConfig->bufferInfo->dataMark = 0U;
      }

      if ( ((curRxBufferConfig->bufferInfo->state) == DCM_BUF_RX) && (Result == NTFRSLT_OK) )
      {
        /* enqueue rx indication event on successful reception */
        (void) DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, curRxPduIdConfig->protocolId, DCM_HSM_DCM_EV_RX_IND_OK);
      }

      /* LEAVE critical section */
      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    }
  }

  DBG_DCM_TPRXINDICATION_EXIT(DcmRxPduId,Result);
}

FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CopyTxData(
  PduIdType DcmTxPduId, P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;

  DBG_DCM_COPYTXDATA_ENTRY(DcmTxPduId,PduInfoPtr,RetryInfoPtr,TxDataCntPtr);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_COPYTXDATA, DCM_E_UNINIT);
  }
  /* DcmTxPduId is TxConfirmationPduId, therefore the check verifies its
   * validity against the total number of Transmission(Tx) Confirmation Pdu Ids  
   */
  else if (DcmTxPduId >= DCM_NUM_CONF_PDU_ID)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_COPYTXDATA, DCM_E_PARAM);
  }
  else if ((PduInfoPtr == NULL_PTR) || (TxDataCntPtr == NULL_PTR))
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_COPYTXDATA, DCM_E_PARAM_POINTER);
  }
  /* Shortcut processing allows us to check whether the pointer is NULL
     before dereferencing it */
  else if((RetryInfoPtr != NULL_PTR) &&
          (RetryInfoPtr->TpDataState != TP_CONFPENDING) &&
          (RetryInfoPtr->TpDataState != TP_DATARETRY) &&
          (RetryInfoPtr->TpDataState != TP_DATACONF))
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_COPYTXDATA, DCM_E_PARAM);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */

  { 
    /* context information for the current instance */
    P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo;
    
    uint8 instIdx = 0U;
    uint16_least i;
    boolean noRetryRequired = FALSE;

    for (i = 0U; i < DCM_NUM_RX_PDU_ID; i++)
    {
      /* !LINKSTO Dcm.EB.Dcm_CopyTxData.DcmTxPduId,1 */
      if( DcmTxPduId == Dcm_TxPduIds[ Dcm_RxPduIdConfig[i].connectionId ].txConfirmationPduId)
      {
        /* Get the index for the protocol that has a Main connection with this 'TxConfirmationPduId' configured */
        instIdx = Dcm_RxPduIdConfig[i].protocolId;
      }
    }

    /* get the context information current instance */
    curHsmInfo = &DCM_HSM_INFO(instIdx);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(instIdx);
#endif

    /* ENTER critical section to access data for the current Tx Pdu Id and BufferInfo */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* check if an error occured while providing data */
    if (DCM_TX_DATA_STATE(instIdx) == DCM_TX_DATA_NOT_OK)
    {
      /* Do nothing as retVal already set */
    }

    /* Check if enough data is ready to be transmitted */
    else if (DCM_TX_DATA_STATE(instIdx) != DCM_TX_DATA_READY)
    {
      /* emit event outside of critical section  so that the application is notified to provide the
       * next page
       */

      *TxDataCntPtr = 0U;
      if (PduInfoPtr->SduLength != 0U)
      {
        /* Dcm.CopyTxData.NoData
         * return "BUFREQ_E_BUSY" and wait for the next call from the PduR
         */
        retVal = BUFREQ_E_BUSY;
      }
      else
      {
        /* Dcm.CopyTxData.AvailableData
         * the PduR may still inquire about the amount of data available in the Tx buffer,
         * therefore, if this API is called with PduInfoPtr->SduLength == 0U, return BUFREQ_OK
         */
        retVal = BUFREQ_OK;
      }
    }

    /* condition here: data is avaiable to be transmitted.
     *
     * dataState == DCM_TX_DATA_READY */
    else
    {
      retVal = Dcm_CbkInternal_CopyTxData(PduInfoPtr, RetryInfoPtr, TxDataCntPtr,
                &noRetryRequired, DCM_CUR_INST_ID(instIdx));
    }

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Outside of critical region */
    if (( DCM_HSM_INFO(instIdx).sentLength  < (curHsmInfo->msgContext.resDataLen + 1U)) &&
        (noRetryRequired == TRUE))
    {
      /* emit event so that the application is notified to provide the next
       * page */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROVIDE_TX_BUF);
    }
  }

  DBG_DCM_COPYTXDATA_EXIT(retVal,DcmTxPduId,PduInfoPtr,RetryInfoPtr,TxDataCntPtr);
  return retVal;
}

FUNC(void, DCM_CODE) Dcm_TpTxConfirmation(PduIdType DcmTxPduId, NotifResultType Result)
{
  Dcm_HsmEventType txStatus;

  DBG_DCM_TPTXCONFIRMATION_ENTRY(DcmTxPduId,Result);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_TPTXCONFIRMATION, DCM_E_UNINIT);
  }
  else if ((DcmTxPduId >= DCM_NUM_CONF_PDU_ID) || (Result > DCM_INVALID_NTFRSLT))
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_TPTXCONFIRMATION, DCM_E_PARAM);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    uint8 instIdx = 0U;
    uint16_least i;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(DcmTxPduId);
#endif /* (DCM_HSM_INST_MULTI_ENABLED == STD_OFF) */

    for (i = 0U; i < DCM_NUM_RX_PDU_ID; i++)
    {
      if( DcmTxPduId == Dcm_TxPduIds[ Dcm_RxPduIdConfig[i].connectionId ].txConfirmationPduId)
      {
        /* Get the index for the protocol that has a Main connection with this 'TxConfirmationPduId' configured */
        instIdx = Dcm_RxPduIdConfig[i].protocolId;
      }
    }

    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    if ((DCM_HSM_INFO(instIdx).responsePendingTxStatus == DCM_RP_PENDING_CONF) &&
        (Result == NTFRSLT_OK))
    {
        /* Set flag to indicate successful transmission of 'Response Pending' */
        DCM_HSM_INFO(instIdx).responsePendingTxStatus = DCM_RP_CONFIRMED_TX;

        if (DCM_HSM_INFO(instIdx).jumpToBLExecution == DCM_FIRST_RCRRP_PENDING)
        {
          /* If a jump to the bootloader is waiting for a RCRRP, confirm that the RCRRP has been sent */
          DCM_HSM_INFO(instIdx).jumpToBLExecution = DCM_JUMP_IN_PROGRESS;
        }

        /* Release NRC buffer */
        DCM_NR_BUFFER(instIdx).bufferInfo->state = DCM_BUF_IDLE;

        /* reset filled buffer length */
        DCM_NR_BUFFER(instIdx).bufferInfo->filledLen = 0;

        /* reset buffer data marking variables */
        DCM_NR_BUFFER(instIdx).bufferInfo->confirmedDataMark = 0U;
        DCM_NR_BUFFER(instIdx).bufferInfo->dataMark = 0U;
    }
    else
    {
      /* get pointer to current message context */
      CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext = &(DCM_HSM_INFO(instIdx).msgContext);

      /* Release rx and tx buffers */
      Dcm_ReleaseRxTxBuffers((uint8) instIdx);

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

      /* Stop the retry timer */
      DCM_HSM_INFO(instIdx).retryTimer = (uint16)0U;

      /* Set flag to indicate unsuccessful transmission of 'Response Pending' */
      DCM_HSM_INFO(instIdx).responsePendingTxStatus = DCM_RP_NO_DATA;
      DCM_HSM_INFO(instIdx).jumpToBLSupport = FALSE;
      DCM_HSM_INFO(instIdx).jumpToBLExecution = DCM_PREPARE_JUMP;

      /* Reset the state of the Tx PduId to indicate that there is no Tx session
       * in progress for it
       */
      DCM_TX_DATA_STATE(instIdx) = DCM_TX_DATA_NOT_OK;
    }

    if(Result == NTFRSLT_OK)
    {
      txStatus = (Dcm_HsmEventType)DCM_HSM_DCM_EV_TX_CONF_OK;
    }
    else
    {
      txStatus = (Dcm_HsmEventType)DCM_HSM_DCM_EV_TX_CONF_NOT_OK;
    }
    /* check if transmission has not succesfully been finished and set the appropriate signal */
    (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, txStatus);

    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }

  DBG_DCM_TPTXCONFIRMATION_EXIT(DcmTxPduId,Result);
}

FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(uint8 NetworkId)
{
  uint8_least i;

  DBG_DCM_COMM_NOCOMMODEENTERED_ENTRY(NetworkId);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_COMMNOCOMMODEENTERED, DCM_E_UNINIT);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    for (i = 0U; i < DCM_NUM_CHANNELID; ++i)
    {
      if(Dcm_ChannelId[i].networkId == NetworkId)
      {
        /* ENTER critical section 
           The paired writing of Dcm_TxEnabled and Dcm_RxEnabled must be protected from preemption */
        SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        Dcm_TxEnabled[i] = FALSE;
        Dcm_RxEnabled[i] = FALSE;

        /* LEAVE critical section */
        SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        break;
      }
    }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (i == DCM_NUM_CHANNELID)
    {
      DCM_DET_REPORT_ERROR(DCM_SERVID_COMMNOCOMMODEENTERED, DCM_E_PARAM);
    }
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  }
  DBG_DCM_COMM_NOCOMMODEENTERED_EXIT(NetworkId);
}

FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(uint8 NetworkId)
{
  uint8_least i;

  DBG_DCM_COMM_SILENTCOMMODEENTERED_ENTRY(NetworkId);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_COMMSILENTCOMMODEENTERED, DCM_E_UNINIT);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    for (i = 0U; i < DCM_NUM_CHANNELID; ++i)
    {
      if(Dcm_ChannelId[i].networkId == NetworkId)
      {
        /* ENTER critical section 
           The paired writing of Dcm_TxEnabled and Dcm_RxEnabled must be protected from preemption */
        SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        Dcm_TxEnabled[i] = FALSE;
        Dcm_RxEnabled[i] = TRUE;

        /* LEAVE critical section */
        SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        break;
      }
    }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (i == DCM_NUM_CHANNELID)
    {
      DCM_DET_REPORT_ERROR(DCM_SERVID_COMMSILENTCOMMODEENTERED, DCM_E_PARAM);
    }
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  }
  DBG_DCM_COMM_SILENTCOMMODEENTERED_EXIT(NetworkId);
}

FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(uint8 NetworkId)
{
  uint8_least i;

  DBG_DCM_COMM_FULLCOMMODEENTERED_ENTRY(NetworkId);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_COMMFULLCOMMODEENTERED, DCM_E_UNINIT);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    for (i = 0U; i < DCM_NUM_CHANNELID; ++i)
    {
      if(Dcm_ChannelId[i].networkId == NetworkId)
      {
        /* ENTER critical section 
           The paired writing of Dcm_TxEnabled and Dcm_RxEnabled must be protected from preemption */
        SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        Dcm_TxEnabled[i] = TRUE;
        Dcm_RxEnabled[i] = TRUE;

        /* LEAVE critical section */
        SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        break;
      }
    }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (i == DCM_NUM_CHANNELID)
    {
      DCM_DET_REPORT_ERROR(DCM_SERVID_COMMFULLCOMMODEENTERED, DCM_E_PARAM);
    }
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  }

  DBG_DCM_COMM_FULLCOMMODEENTERED_EXIT(NetworkId);
}


#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]==============================================*/

STATIC FUNC(BufReq_ReturnType, DCM_CODE) Dcm_CbkInternal_CopyTxData(
  P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
  P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr,
  P2VAR(boolean, AUTOMATIC, DCM_APPL_DATA) pNoRetryRequired,
  uint8 instIdx)
{
  BufReq_ReturnType retVal = BUFREQ_E_NOT_OK;
  boolean noRetryRequired = *pNoRetryRequired;

  /* pointer to buffer information for current protocol instance  */   
  P2VAR(Dcm_BufferInfoType, AUTOMATIC, DCM_VAR) curTxBufferInfo;

  /* context information for the current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo;

  /* pointer to buffer information for current protocol instance  */
  curTxBufferInfo = DCM_HSM_INFO(instIdx).curTxBuffer->bufferInfo;
  /* get the context information current instance */
  curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_CBKINTERNAL_COPYTXDATA_ENTRY(PduInfoPtr, RetryInfoPtr, TxDataCntPtr, pNoRetryRequired, instIdx);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(instIdx);
#endif

  if(PduInfoPtr->SduLength != 0U)
  {
    /* Flag to avoid copy of Tx data to PduInfoPtr when invalid retry length error occurs */
    boolean dataToCopy = TRUE;

    if(RetryInfoPtr != NULL_PTR)
    {
      switch (RetryInfoPtr->TpDataState)
      {
        case TP_DATARETRY:
          if (RetryInfoPtr->TxTpDataCnt != 0U)
          {
        /* If RetryInfoPtr->TpDataState is TP_RETRY, and RetryInfoPtr->TxTpDataCnt is larger
         * than the available payload data prior to the current transmitted data mark
         * Dcm_CopyTxData() shall return BUFREQ_E_NOT_OK.
         */
        if(RetryInfoPtr->TxTpDataCnt > (curTxBufferInfo->dataMark -
          curTxBufferInfo->confirmedDataMark))
        {
          curTxBufferInfo->dataMark = 0U;
          curTxBufferInfo->confirmedDataMark = 0U;
          dataToCopy = FALSE;
          retVal = BUFREQ_E_NOT_OK;
        }
        else
        {
          /* Seting buffer variables when Retry of data is required */
          curTxBufferInfo->dataMark -= RetryInfoPtr->TxTpDataCnt;
        }
      }
      else
      {
            /* if we call a retry for 0 bytes, it is equivalent to a confirmation */
          curTxBufferInfo->confirmedDataMark = curTxBufferInfo->dataMark;
        }
          break;
        case TP_DATACONF:
          curTxBufferInfo->confirmedDataMark = curTxBufferInfo->dataMark;
          break;
        case TP_CONFPENDING:
          /* The lower layer asks us to not confirm the data previously sent */
          break;
        /* CHECK: NOPARSE */
        default:
          /* Unreachable code as this error condition was captured in the preamble
             of this function . This is required by MISRA.*/
          break;
        /* CHECK: PARSE */
      }
    }
    else
    {
      curTxBufferInfo->confirmedDataMark = curTxBufferInfo->dataMark;
    }

    /* Ensuring last call of CopyTxData is successful and no retry of data is required */
    if(curTxBufferInfo->confirmedDataMark == curTxBufferInfo->filledLen)
    {
      noRetryRequired = TRUE;
      dataToCopy = FALSE;
    }

    /* If available payload data within the tx-buffer measured from the mark of transmitted
     * payload is smaller than PduInfoPtr->SduLength, write the available data length to
     * AvailableDataPtr and return BUFREQ_E_BUSY.
     */
    if((curTxBufferInfo->filledLen - curTxBufferInfo->dataMark) < PduInfoPtr->SduLength)
    {
      *TxDataCntPtr = curTxBufferInfo->filledLen - curTxBufferInfo->dataMark;
      retVal = BUFREQ_E_BUSY;
    }
    else
    {
      if(dataToCopy == TRUE)
      {
        /* Copying Tx data of length 'SduLength' from Tx buffer to the pointer 'SduDataPtr' */
        TS_MemCpy(PduInfoPtr->SduDataPtr,
          &curHsmInfo->curTxBuffer->ptrBuffer[curTxBufferInfo->dataMark],
          (uint16)PduInfoPtr->SduLength);

        /* Marking the position of payload data already transmitted within the tx-buffer */
        curTxBufferInfo->dataMark += PduInfoPtr->SduLength;
        /* Remaining Tx data in buffer after completion of copy operation */
        *TxDataCntPtr = curTxBufferInfo->filledLen - curTxBufferInfo->dataMark;
        retVal = BUFREQ_OK;
      }
    }
  }

  else
  {
    /* Dcm.CopyTxData.AvailableData */
    /* If SduLength is 0 then returning the available transmit data count. In this case no data
     * are to be copied and SduDataPtr might be invalid.
     */
    *TxDataCntPtr = curTxBufferInfo->filledLen - curTxBufferInfo->dataMark;

    if((RetryInfoPtr == NULL_PTR) || (RetryInfoPtr->TpDataState != TP_CONFPENDING))
    {
    curTxBufferInfo->confirmedDataMark = curTxBufferInfo->dataMark;
    }

    if(curTxBufferInfo->confirmedDataMark == curTxBufferInfo->filledLen)
    {
      noRetryRequired = TRUE;
    }

    retVal = BUFREQ_OK;
  }

  /* Data has now been provided to lower layer the TxPduId status is changed. On the next call
   * to Dcm_CopyTxData() we know that the current page was sent and the application is notified
   * to provide the next page
   */
  if (noRetryRequired == TRUE)
  {
    DCM_TX_DATA_STATE(instIdx) = DCM_NO_TX_DATA;
    /* reset filled buffer length */
    curTxBufferInfo->filledLen = 0;
    /* reset buffer data marking variables */
    curTxBufferInfo->confirmedDataMark = 0U;
    curTxBufferInfo->dataMark = 0U;
  }

  *pNoRetryRequired = noRetryRequired;

  DBG_DCM_CBKINTERNAL_COPYTXDATA_EXIT(retVal, PduInfoPtr, RetryInfoPtr, TxDataCntPtr,
                                       pNoRetryRequired, instIdx);
  return retVal;
}

/*==================[end of file]================================================================*/
