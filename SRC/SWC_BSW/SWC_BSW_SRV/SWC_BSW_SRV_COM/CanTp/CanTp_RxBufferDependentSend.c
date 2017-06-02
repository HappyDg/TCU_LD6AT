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

/*==================[inclusions]============================================*/

#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_InternalLib.h> /* internal macros and variables */
#include <CanTp_Internal.h>    /* internal macros and variables */
/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_CanTp.h */
#define PDUR_NO_PBCFG_REQUIRED
#include <PduR_CanTp.h>        /* PduR module API */
#include <TSMem.h>             /* TS_MemCpy */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)


FUNC(Std_ReturnType, CANTP_CODE) CanTp_ProcessStartOfReception
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  Std_ReturnType Ret;
  BufReq_ReturnType Ret_StartOfReception;
  PduLengthType UL_BufferSize;

  DBG_CANTP_PROCESSSTARTOFRECEPTION_ENTRY(ChannelPtr);

  /* CANTP079v4.0.0 Inform upper layer about Rx frame*/
  Ret_StartOfReception = CANTP_PDUR_START_OF_RECEPTION
    (
      CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId).IPduId,
      ChannelPtr->TotalLength,
      &UL_BufferSize
    );

  switch(Ret_StartOfReception){
    case BUFREQ_OK:
    {
      /* Reception started */
      if(CANTP_MAX_MESSAGE_LENGTH < UL_BufferSize)
      {
        ChannelPtr->ActualBufferSize = CANTP_MAX_MESSAGE_LENGTH;
      }
      else
      {
        ChannelPtr->ActualBufferSize = (uint16) UL_BufferSize;
      }
      Ret = E_OK;
      break;
    }
    case BUFREQ_E_NOT_OK:
    {
      /* Stop channel and don't inform upper layer (send no flow control
         CanTp.ASR40.CANTP081).
       */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_NONE,
                         NTFRSLT_E_NOT_OK
                       );
      Ret = E_NOT_OK;
      break;
    }
    case BUFREQ_E_OVFL:
    {
      ChannelPtr->ActualBufferSize = 0U;

      DBG_CANTP_CHANNEL_STATE_GRP(
                                  DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                  ChannelPtr->State,
                                  CANTP_CH_RX_TRANSMIT_FC_OVFLW
                                 );

      ChannelPtr->State = CANTP_CH_RX_TRANSMIT_FC_OVFLW;
      CanTp_PrepareFCovflw(ChannelPtr);
      /* channel will be closed automatically after FC frame is sent correctly
         or timeout.
       */
      Ret = E_NOT_OK;
      break;
    }
    case BUFREQ_E_BUSY:
    {
      /* Wait for free buffer */
      /* BUFREQ_E_BUSY will be removed in future (see RFC52007)*/
      /* The value of upper layer buffer size is undefined for this return value */
      ChannelPtr->ActualBufferSize = 0U;
      Ret = E_OK;
      break;
    }
    default:
    {
      /* unknown return value -> Abort reception */
      CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
      Ret = E_NOT_OK;
      break;
    }
  }
  DBG_CANTP_PROCESSSTARTOFRECEPTION_EXIT(Ret, ChannelPtr);
  return Ret;
}

FUNC(BufReq_ReturnType, CANTP_CODE) CanTp_ProcessStartOfReceptionData
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) NPduDataPtr,
  uint8 NSduDataLength
)
{
  BufReq_ReturnType Ret_ReqRxBuffer;

  DBG_CANTP_PROCESSSTARTOFRECEPTIONDATA_ENTRY(ChannelPtr, NPduDataPtr, NSduDataLength);

  if(NSduDataLength == 0U)
  {
    /* All data are already copied but bigger buffer required. */
    Ret_ReqRxBuffer = CanTp_RxProcessData(ChannelPtr, NULL_PTR, 0U);
  }
  else
  {
    if(ChannelPtr->ActualBufferSize < NSduDataLength)
    {
      /* Actual buffer is smaller as received data. Request bigger buffer. */
      Ret_ReqRxBuffer = CanTp_RxProcessData(ChannelPtr, NULL_PTR, 0U);
    }
    else
    {
      Ret_ReqRxBuffer = BUFREQ_OK; /* Enough buffer from last call available */
    }

    if(BUFREQ_OK == Ret_ReqRxBuffer)
    {
      if(ChannelPtr->ActualBufferSize >= NSduDataLength)
      {
        Ret_ReqRxBuffer = CanTp_RxProcessData(ChannelPtr, NPduDataPtr, NSduDataLength);
      }
      else
      {
        /* Not enough buffer available. Set return value to BUFREQ_E_BUSY to indicate
           that no data have been copied.
         */
        Ret_ReqRxBuffer = BUFREQ_E_BUSY;
      }
    }
  }

  DBG_CANTP_PROCESSSTARTOFRECEPTIONDATA_EXIT(
                                             Ret_ReqRxBuffer,
                                             ChannelPtr,
                                             NPduDataPtr,
                                             NSduDataLength
                                            );
  return Ret_ReqRxBuffer;
}

FUNC(BufReq_ReturnType, CANTP_CODE) CanTp_RxProcessData
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) NPduDataPtr,
  uint8 NSduDataLength
)
{
  BufReq_ReturnType Ret_CopyRxData;
  PduLengthType UL_BufferSize;
  PduInfoType PduInfo; /* info structure for next buffer */

  DBG_CANTP_RXPROCESSDATA_ENTRY(ChannelPtr, NPduDataPtr, NSduDataLength);

  PduInfo.SduLength = NSduDataLength;
  PduInfo.SduDataPtr = NPduDataPtr;

  Ret_CopyRxData = CANTP_PDUR_COPY_RX_DATA
    (
      CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId).IPduId,
      &PduInfo,
      &UL_BufferSize
    );
  if(Ret_CopyRxData == BUFREQ_OK)
  {
    /* Limit the UL buffer size to the maximal message length. */
    if(CANTP_MAX_MESSAGE_LENGTH < UL_BufferSize)
    {
      ChannelPtr->ActualBufferSize = CANTP_MAX_MESSAGE_LENGTH;
    }
    else
    {
      ChannelPtr->ActualBufferSize = (uint16) UL_BufferSize;
    }
  }
  else
  {
    /* The value of upper layer buffer size is undefined for this return value */
    ChannelPtr->ActualBufferSize = 0U;
  }

  DBG_CANTP_RXPROCESSDATA_EXIT(Ret_CopyRxData, ChannelPtr, NPduDataPtr, NSduDataLength);
  return Ret_CopyRxData;
}

FUNC(void, CANTP_CODE) CanTp_RxStateHandling
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  DBG_CANTP_RXSTATEHANDLING_ENTRY(ChannelPtr);

  switch(ChannelPtr->State)
  {
    case CANTP_CH_RX_BUFREQ_SF:
    {
      BufReq_ReturnType Ret_ReqRxBuffer;

      Ret_ReqRxBuffer = CanTp_ProcessStartOfReceptionData
                                 (
                                   ChannelPtr,
                                   ChannelPtr->TempBuffer,
                                   ChannelPtr->TempLength
                                 );
      switch(Ret_ReqRxBuffer)
      {
        case BUFREQ_OK:
        {
          /* single frame reception completed. The whole message was copied to
             upper layer successfully.
           */
          CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_OK);

          break;
        }
        case BUFREQ_E_BUSY:
        {
          /* Wait until buffer is available or timeout occurs.*/
          break;
        }
        default:
        {
          /* Unexpected return value. Close channel. */
          CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
          break;
        }
      }
      break;
    }
    case CANTP_CH_RX_BUFREQ_FF:
    {
      BufReq_ReturnType Ret_ReqRxBuffer;

      Ret_ReqRxBuffer = CanTp_ProcessStartOfReceptionData
                                 (
                                   ChannelPtr,
                                   ChannelPtr->TempBuffer,
                                   ChannelPtr->TempLength
                                 );
      switch(Ret_ReqRxBuffer)
      {
        case BUFREQ_OK:
        {
          /* Data are copied to UL if not already done with CanTP_RxIndication().
             In this case ChannelPtr->TempLength was already zero.
           */
          Std_ReturnType BSCalc_Ok; /* Indication of the actual BS calculation */

          ChannelPtr->ProcessedLength += (uint16) ChannelPtr->TempLength;
          ChannelPtr->TempLength = 0U;

          /* Only calculate actual block size if FF data already processed. */
          BSCalc_Ok = CanTp_CalculateBlockSize(ChannelPtr, &(ChannelPtr->BlockSize));

         if(BSCalc_Ok == E_OK)
         {
            DBG_CANTP_CHANNEL_STATE_GRP(
                                        DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                        ChannelPtr->State,
                                        CANTP_CH_RX_TRANSMIT_FC_CTS
                                       );

            ChannelPtr->State = CANTP_CH_RX_TRANSMIT_FC_CTS;
            /* CanTp_TxConfirmation will set state to CANTP_CH_RX_RECEIVE_CF */
            CanTp_PrepareFCcts(ChannelPtr);
          }
          else
          {
            /* Send wait frame if timeout elapsed */
            CanTp_CheckAndHandleWaitFrameTimeOut(ChannelPtr);
          }
          break;
        }
        case BUFREQ_E_BUSY:
        {
          /* Wait until buffer is available or timeout occurs.*/
          /* Send wait frame if timeout elapsed */
          CanTp_CheckAndHandleWaitFrameTimeOut(ChannelPtr);
          break;
        }
        default:
        {
          /* Unexpected return value. Close channel. */
          CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
          break;
        }
      }
      break;
    }
    case CANTP_CH_RX_BUFREQ_CF:
    {
      /* This state the channel waits for enough buffer to request the next block. */
      BufReq_ReturnType Ret_ReqRxBuffer;

      Ret_ReqRxBuffer = CanTp_RxProcessData(ChannelPtr, NULL_PTR, 0U);

      switch(Ret_ReqRxBuffer)
      {
        case BUFREQ_OK:
        {
          boolean ContinueWithNextBlock;

          ContinueWithNextBlock = CanTp_VerifyBlockSize(ChannelPtr);

          if(ContinueWithNextBlock)
          {
            DBG_CANTP_CHANNEL_STATE_GRP(
                                        DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                        ChannelPtr->State,
                                        CANTP_CH_RX_TRANSMIT_FC_CTS
                                       );

            /* Expected BS fits into available UL buffer. */
            ChannelPtr->State = CANTP_CH_RX_TRANSMIT_FC_CTS;
            /* CanTp_TxConfirmation will set state to CANTP_CH_RX_RECEIVE_CF */
            CanTp_PrepareFCcts(ChannelPtr);
          }
          else
          {
            /* Send wait frame if timeout elapsed */
            CanTp_CheckAndHandleWaitFrameTimeOut(ChannelPtr);
          }
          break;
        }
        case BUFREQ_E_BUSY:
        {
          /* Wait until buffer is available or timeout occurs.*/
          /* Send wait frame if timeout elapsed */
          CanTp_CheckAndHandleWaitFrameTimeOut(ChannelPtr);
          break;
        }
        default:
        {
          /* Unexpected return value. Close channel. */
          CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
          break;
        }
      }
      break;
    }
    case CANTP_CH_RX_TRANSMIT_FC_CTS:
    case CANTP_CH_RX_TRANSMIT_FC_OVFLW:
    case CANTP_CH_RX_TRANSMIT_FC_WT:
    {
      /* If still in this state try to send again until timeout occurs.
         CanTp_TransmitFrame shall change to the corresponding CONFIRM state
         automatically.
       */
      CanTp_TransmitFrame(ChannelPtr);
      break;
    }
    case CANTP_CH_RX_CONFIRM_FC_CTS:
    case CANTP_CH_RX_CONFIRM_FC_OVFLW:
    case CANTP_CH_RX_CONFIRM_FC_WT:
    {
      /* Wait for confirm. CanTp_TxConfirmation() or timeout will take care of
         changing state. */
      break;
    }
    case CANTP_CH_RX_RECEIVE_CF:
    {
      /* wait for next CF or timeout */
      break;
    }
    /* CHECK: NOPARSE */
    default:
    {
      /* unexpected state - should never be reached */
      CANTP_UNREACHABLE_CODE_ASSERT(CANTP_INTERNAL_API_ID);
      break;
    }
    /* CHECK: PARSE */
  }

  DBG_CANTP_RXSTATEHANDLING_EXIT(ChannelPtr);
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
