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

/*This file contains the implementation of the Diagnostic Session
  * Layer (DSL) in Dcm. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 12.5 (required)
 *     The operands of a logical && or || shall be primary-expressions.
 *
 *     Reason:
 *     Misra has an exception that whenever an expression consists of either a sequence of only
 *     logical && or a sequence of only logical && or logical ||, extra parentheses are not required
 *
 * MISRA-2) Deviated Rule: 16.7 (required)
 *     A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the addressed
 *     object.
 *
 *     Reason:
 *     Signature of functions defined by AUTOSAR 4.0.3 and this violations become obsolete
 *     when AUTOSAR updated the corresponding function signatures
 */
/*===============================[includes]======================================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSMem.h>                                                /* EB specific memory functions */

#include <Dcm.h>                                                      /* Declaration of Dcm APIs */
#include <Dcm_Int.h>                                             /* Internal declarations of Dcm */
#include <Dcm_HsmDcm.h>                                   /* public statechart model definitions */

#include <SchM_Dcm.h>                                                  /* SchM interface for Dcm */

/*===========================[macro definitions]=================================================*/

/*=====================[external constants declarations]=========================================*/

/*=====================[internal constants declarations]=========================================*/

/*==================[internal function declarations]=============================================*/

/*=======================[external data declarations]============================================*/

/*=======================[internal data declarations]============================================*/

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>
#if(DCM_ROE_ENABLED == STD_ON)
/* Deviation MISRA-2 <+2> */
FUNC(Dcm_StatusType, DCM_CODE) Dcm_DslInternal_ResponseOnOneEvent(
  P2CONST(Dcm_MsgItemType, AUTOMATIC, DCM_CONST) MsgPtr,
  PduLengthType                 MsgLen,
  PduIdType                     DcmRxPduId)
{
  Dcm_StatusType retVal = DCM_E_ROE_NOT_ACCEPTED;

  DBG_DCM_DSLINTERNAL_RESPONSEONONEEVENT_ENTRY(MsgPtr,MsgLen,DcmRxPduId);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSL_RESPONSEONONEEVENT, DCM_E_UNINIT);
    retVal = DCM_E_ROE_NOT_ACCEPTED;
  }
  else if (MsgPtr == NULL_PTR)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSL_RESPONSEONONEEVENT, DCM_E_PARAM_POINTER);
    retVal = DCM_E_ROE_NOT_ACCEPTED;
  }
  else if(MsgLen == 0U)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSL_RESPONSEONONEEVENT, DCM_E_PARAM);
    retVal = DCM_E_ROE_NOT_ACCEPTED;
  }
  else if ( DcmRxPduId >= DCM_NUM_RX_PDU_ID )
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSL_RESPONSEONONEEVENT, DCM_E_PARAM);
    retVal = DCM_E_ROE_NOT_ACCEPTED;
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    P2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig;
    P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST)  curRxBufferConfig;
    P2VAR(Dcm_BufferInfoType, AUTOMATIC, DCM_VAR)        curRxBufferInfo;

    /* get configuration of current Rx Pdu Id */
    curRxPduIdConfig  = &Dcm_RxPduIdConfig[DcmRxPduId];
    /* configuration of current Rx buffer */
    curRxBufferConfig = &Dcm_BufferConfig[curRxPduIdConfig->rxBufferId];
    /* current Rx buffer information */
    curRxBufferInfo   = curRxBufferConfig->bufferInfo;

    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Deviation MISRA-1 */
    /* Dcm133, Dcm134, Dcm135, Dcm137, Dcm601 */
    if ((curRxBufferInfo->state == DCM_BUF_IDLE) &&
        (Dcm_TxEnabled[curRxPduIdConfig->channelIdIndex] == TRUE) &&
        (Dcm_ROEProcessing == DCM_ROE_NONE) &&
        (Dcm_RoeInterMsgTime == 0U))
    {
      /* allocate and set up buffer info */
      curRxBufferInfo->state              = DCM_BUF_ROE;
      curRxBufferInfo->filledLen          = MsgLen;
      curRxBufferInfo->originatingRxPduId = DcmRxPduId;

      /* Dcm132: synchronously copy req msg into rx buffer
       *
       * we cannot assume that the application keeps the provided request data untouched after
       * returning from this function, therefore we have to copy the data */
      TS_MemCpy(curRxBufferConfig->ptrBuffer, MsgPtr, (uint16)MsgLen);

      retVal = DCM_E_OK;

      /* Dcm137: While processing an ROE TYPE1 event, any additional
       * requests (external and internal) shall be rejected with the same or lower priority of its
       * Protocol Table.

       * As protocol preemption is not supported, enable the flag signaling that a request is
       * currently being serviced */

      DBG_DCM_ROEPROCESSING((Dcm_ROEProcessing),(DCM_ROE_QUEUED));
      Dcm_ROEProcessing = DCM_ROE_QUEUED;
    }
    /* else: no buffer available or transmission not allowed, let retVal be set to
     * DCM_E_ROE_NOT_ACCEPTED */

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    if (retVal == DCM_E_OK)
    {
      if (Dcm_ReqProcessing == TRUE)
      {
        /* if there is an ongoing request, set the event flag */
        DBG_DCM_ROEENQUEUEEVENT((Dcm_ROEEnqueueEvent), (DCM_ROE_NORMAL_EVENT))
        Dcm_ROEEnqueueEvent = DCM_ROE_NORMAL_EVENT;
      }
      else
      {
        /* if there is no ongoing request, enqueue ROE event */
        (void)DCM_HSMEMITINST_WRAPPER(
          &Dcm_HsmScDcm, curRxPduIdConfig->protocolId, DCM_HSM_DCM_EV_ROE);
      }
    }
  }

  DBG_DCM_DSLINTERNAL_RESPONSEONONEEVENT_EXIT(retVal,MsgPtr,MsgLen,DcmRxPduId);
  return retVal;
}
#endif /* (DCM_ROE_ENABLED == STD_ON) */
#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]================================================================*/

