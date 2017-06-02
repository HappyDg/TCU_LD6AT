/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_Api.h>         /* CanTp API declarations */
#include <CanTp_Internal.h>    /* internal macros and variables */
#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_EntryTable.h>  /* CanTp entry jumptable */
#endif /* CANTP_JUMPTABLE_SUPPORT == STD_ON */

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_PROVIDE_API_FUNCTIONS == STD_ON)

/** \brief CanTp_Transmit()
 **
 ** This API-Service is used to request the transfer of segmented data.
 **
 ** \param[in] CanTpTxSduId  N-Sdu Id, which shall be used for sending
 ** \param[in] CanTpTxInfoPtr  pointer with length information of the frame
 **
 ** \retval E_NOT_OK transmit request failed
 ** \retval E_OK transmit request successful
 */
FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit
(
  PduIdType CanTpTxSduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpTxInfoPtr
)
#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)
{
  Std_ReturnType  Ret = E_NOT_OK; /* return value */

  DBG_CANTP_TRANSMIT_ENTRY(CanTpTxSduId, CanTpTxInfoPtr);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  /* check CanTp state - possible DET and return on error */
  if(CanTp_InitVars.State != CANTP_ON)
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_TRANSMIT,
                            CANTP_E_UNINIT
                          );
  }

  /* check PduId range - possible DET and return on error */
  else if(CanTpTxSduId >= CanTp_CfgPtr->NumberTxNSdus)
  {
    /* call DET with error ERRORCODE */
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_TRANSMIT,
                            CANTP_E_PARAM_ID
                          );
  }

  /* check for Null pointer - possible DET and return on error */
  /* if pointer is null */
  else if(CanTpTxInfoPtr == NULL_PTR)
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_TRANSMIT,
                            CANTP_E_PARAM_POINTER
                          );
  }

  /* check length */
  /* if sdu length is 0 or greater 0x0FFF */
  else if(
           (CanTpTxInfoPtr->SduLength == 0U)
           || (CanTpTxInfoPtr->SduLength > CANTP_MAX_MESSAGE_LENGTH)
         )
  {
    /* call DET with error CANTP_E_INVALID_TX_LENGTH */
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_TRANSMIT,
                            CANTP_E_INVALID_TX_LENGTH
                          );
  }
  else
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
  {
    P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;

    /* counter for channels */
    const uint8 Channel = CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId).Channel;

    ChannelPtr = &CanTp_Channel[Channel];

    /* verify that configured Tx channel is free */
    CANTP_ENTER_CRITICAL_SECTION();

    /* lock channel if channel is IDLE and not currently locked */
    if(
        (ChannelPtr->State != CANTP_CH_IDLE)
        || (CANTP_IS_CHANNEL_LOCKED(ChannelPtr))
      )
    {
      Ret = E_NOT_OK;
    }
    else
    {
      CANTP_LOCK_CHANNEL(ChannelPtr);
      Ret = E_OK;
    }

    CANTP_LEAVE_CRITICAL_SECTION();

    if(Ret == E_OK)
    {
      /* For checking whether data will fit in a SF or segmented Tx is required */
      const uint8 MaxUnSegMsgLength = CANTP_SF_MAX_NSDU_LENGTH
                   - CANTP_GET_FIRST_N_PCI_BYTE(&CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId));

      /* setup channel correctly */
      ChannelPtr->NSduId = CanTpTxSduId;
      ChannelPtr->TotalLength = (uint16) CanTpTxInfoPtr->SduLength;

      /* timeout to request for a buffer is Cs */
      ChannelPtr->Ticks = CANTP_GET_TX_PDU_N_CS(&CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId));

      /* set new state */
      if(CanTpTxInfoPtr->SduLength <= MaxUnSegMsgLength)
      {
        DBG_CANTP_CHANNEL_STATE_GRP(Channel, ChannelPtr->State, CANTP_CH_TX_BUFREQ_SF);

        /* this is a single frame */
        ChannelPtr->State = CANTP_CH_TX_BUFREQ_SF;
      }
      else
      {
        /* check if functional addressing is used with long frames */
        if(CANTP_CFG_GET_TXNSDU_CONFIG(CanTpTxSduId).Tatype != CANTP_FUNCTIONAL)
        {
          DBG_CANTP_CHANNEL_STATE_GRP(Channel, ChannelPtr->State, CANTP_CH_TX_BUFREQ_FF);

          /* this is a long frame */
          ChannelPtr->State = CANTP_CH_TX_BUFREQ_FF;
        }
        else
        {
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
          CANTP_DET_REPORT_ERROR(
                                  CANTP_MODULE_ID,
                                  CANTP_INSTANCE_ID,
                                  CANTP_API_TRANSMIT,
                                  CANTP_E_INVALID_TATYPE
                                );
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
          /* segmented frames are not allowed for functional addressing */
          Ret = E_NOT_OK;
        }
      }
      CANTP_UNLOCK_CHANNEL(ChannelPtr);
    }
  }

  DBG_CANTP_TRANSMIT_EXIT(Ret, CanTpTxSduId, CanTpTxInfoPtr);

  return Ret;
} /* CanTp_Transmit() */
#else /* => CANTP_JUMPTABLE_MODE == CANTP_JUMPTABLE_CLIENT */
{
  Std_ReturnType  Ret = E_NOT_OK;
  DBG_CANTP_TRANSMIT_ENTRY(CanTpTxSduId, CanTpTxInfoPtr);
  Ret = (CanTp_EntryTablePtr->Transmit)(CanTpTxSduId, CanTpTxInfoPtr);
  DBG_CANTP_TRANSMIT_EXIT(Ret, CanTpTxSduId, CanTpTxInfoPtr);
  return Ret;
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#endif /* CANTP_PROVIDE_API_FUNCTIONS == STD_ON */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
