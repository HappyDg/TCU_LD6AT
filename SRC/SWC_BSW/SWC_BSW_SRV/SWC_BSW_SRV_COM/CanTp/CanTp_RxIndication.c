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
#include <TSAtomic_Assign.h>   /* Header for atomic assignment macros */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_Api.h>         /* Module public API */
#include <CanTp_Cbk.h>         /* CanTp callback declarations */
#include <CanTp_Internal.h>    /* internal macros and variables */
#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_EntryTable.h>  /* CanTp entry jumptable */
#endif /* CANTP_JUMPTABLE_SUPPORT == STD_ON */
#include <TSMem.h>             /* TS_MemCpy */

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/
#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

/** \brief CanTp_ProcessReceivedSF()
 **
 ** This function receives a SF from CanIf
 ** - PDU length code will be checked
 ** - SF length code will be checked
 ** - Data will be stored in temp buffer
 ** - RxBufferRequest will be called
 **
 ** Preconditions:
 ** - channel must be in state CANTP_CH_IDLE and reserved
 ** - frame must be a SF and addressing must be correct (no check again)
 ** - ChannelPtr must correspond to the incoming frame
 ** - parameters must be valid
 ** - N-Pdu length must be within the minimum and maximum range
 ** - N-Pdu length must be CANTP_NPDU_LENGTH_MAX if padding is enabled
 **
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 */
STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedSF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief CanTp_ProcessReceivedFF()
 **
 ** This function receives a FF from CanIf
 ** - PDU length code will be checked
 ** - FF length code will be checked
 ** - Data will be stored in temp buffer
 ** - RxBufferRequest will be called
 **
 ** Preconditions:
 ** - channel must be in state CANTP_CH_IDLE and reserved
 ** - frame must be a FF and addressing must be correct (no check again)
 ** - ChannelPtr must correspond to the incoming frame
 ** - parameters must be valid
 ** - N-Pdu length must be within the minimum and maximum range
 **
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 */
STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedFF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief CanTp_ProcessReceivedCF()
 **
 ** This function receives a CF from CanIf
 ** - sequence number will be checked
 ** - PDU length code will be checked
 ** - Data will be stored in data or temp buffer
 ** - RxBufferRequest will be called or
 **   FC (CTS) will be transmitted or
 **   NSdu will be finished and channel will be freed
 **
 ** Preconditions:
 ** - channel must be in state CANTP_CH_RX_RECEIVE_CF
 ** - frame must be a CF and addressing must be correct
 ** - ChannelPtr must correspond to the incoming frame
 ** - parameters must be valid
 ** - N-Pdu length must be within the minimum and maximum range
 ** - N-Pdu length must be CANTP_NPDU_LENGTH_MAX if padding is enabled
 **
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 */
STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedCF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief CanTp_ProcessReceivedIntermediateCF()
 **
 ** Part of CanTp_ProcessReceivedCF that handles intermediate consecutive frames.
 **
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] ChannelPtr     pointer to channel data structure in RAM
 ** \param[in] Delta          Remaining bytes of this reception
 */
STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedIntermediateCF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief CanTp_ProcessReceivedIntermediateCF()
 **
 ** Part of CanTp_ProcessReceivedCF that handles final consecutive frames.
 **
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] ChannelPtr     pointer to channel data structure in RAM
 ** \param[in] DataLength     Remaining bytes of this reception (Data length in last CF)
 */
STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedLastCF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  uint8 DataLength
);

/** \brief CanTp_ProcessReceivedFC()
 **
 ** This function receives a FC from CanIf
 ** - length code will be checked
 ** - on CTS: take BS, request for buffer or transmit data
 ** - on WT: count down and close channel on timeout
 ** - on OVFL: close channel
 **
 ** Preconditions:
 ** - channel must be in state CANTP_CH_TX_RECEIVE_FC
 ** - frame must be a FC and addressing must be correct
 ** - ChannelPtr must correspond to the incoming frame
 ** - parameters must be valid
 ** - N-Pdu length must be within the minimum and maximum range
 ** - N-Pdu length must be CANTP_NPDU_LENGTH_MAX if padding is enabled
 **
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 */
STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedFC
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief CanTp_FindNSduId()
 **
 ** Searched for an N-Sdu matching the received addressing information (N-Pdu Id
 ** for standard addressing, N-Pdu Id and N_SA byte for extended addressing).
 **
 ** \param[in] CanTpRxPduId  Id of N-Pdu received
 ** \param[in] CanDataPtr  pointer to received data
 ** \param[out] NSduId  N-Sdu Id found
 ** \param[out] FrameType  Type of frame form N_PCI byte found
 **
 ** \retval FALSE: no matching N-Sdu found, output parameters are invalid
 ** \retval TRUE: N-Sdu found, corresponding NSduId and FrameType set
 */
STATIC FUNC(boolean, CANTP_CODE) CanTp_FindNSduId
(
  PduIdType CanTpRxPduId,
  P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) CanDataPtr,
  P2VAR(PduIdType, AUTOMATIC, CANTP_APPL_DATA) NSduId,
  P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) FrameType
);

/** \brief CanTp_RxChannelCleanup()
 **
 ** Tries to free the requested channel. In case of usage, a current receive
 ** will be terminated.
 **
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 */
STATIC FUNC(void, CANTP_CODE) CanTp_RxChannelCleanup
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief CanTp_ProcessRxFrame()
 **
 ** Handles the processing of Received frame.
 **
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] NSduId  corresponding N-Sdu of the incoming frame
 ** \param[in] FrameType  contains the information of frame type from N_PCI
 **
 */
STATIC FUNC(void, CANTP_CODE) CanTp_ProcessRxFrame
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  PduIdType NSduId,
  uint8 FrameType
);

/** \brief CanTp_PostponeRxFrame()
 **
 ** Handles the reception when the channel is locked.
 **
 ** Preconditions:
 ** - CanTpRxPduPtr->SduLength shall be < 256
 **
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 ** \param[in] CanTpRxPduPtr  pointer to received data and length
 ** \param[in] NSduId  corresponding N-Sdu of the incoming frame
 ** \param[in] FrameType  contains the information of frame type from N_PCI

 **
 */
STATIC FUNC(void, CANTP_CODE) CanTp_PostponeRxFrame
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  PduIdType NSduId,
  uint8 FrameType
);

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if(CANTP_PROVIDE_API_FUNCTIONS == STD_ON)

/** \brief CanTp_RxIndication()
 **
 ** This function receives any N-PDU from CanIf
 ** - checks if a configured N-SDU exists for this N-PDU
 ** - For SF or FF it verifies that channel is available and starts reception
 ** - For CF or FC it verifies that channel is waiting for this N-PDU
 **   and processes the reception
 **
 ** \param[in] CanTpRxPduId, N-Pdu Id that was received
 ** \param[in] CanTpRxPduPtr, pointer to received data and length
 */
FUNC(void, CANTP_CODE) CanTp_RxIndication
(
  PduIdType CanTpRxPduId,
  P2VAR(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr
)
#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)
{
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;
  P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) CanDataPtr; /* ptr to can data */
  PduIdType               NSduId;           /* affected N-Sdu Id */
  uint8                   Channel;          /* counter for channels */
  uint8                   FrameType;        /* frame type from N_PCI frame header */

  DBG_CANTP_RXINDICATION_ENTRY(CanTpRxPduId, CanTpRxPduPtr);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  /* check CanTp state - possible DET and return on error */
  if(CanTp_InitVars.State != CANTP_ON)
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_UNINIT
                          );
  }

  /* check null pointer - possible DET and return on error */
  else if((CanTpRxPduPtr == NULL_PTR) || (CanTpRxPduPtr->SduDataPtr == NULL_PTR))
  {
    /* call DET with error ERRORCODE */
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_PARAM_POINTER
                          );
  }

  /* check N-PDU Id range - possible DET and return on error */
  else if(CanTpRxPduId >= CanTp_CfgPtr->NumberRxNPdus)
  {
    /* call DET with error ERRORCODE */
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_INVALID_RX_ID
                          );
  }

  /* length must be at least 2 bytes and smaller as CANTP_NPDU_LENGTH_MAX */
  else if(
           (CANTP_NPDU_LENGTH_MIN > CanTpRxPduPtr->SduLength)
           || (CANTP_NPDU_LENGTH_MAX < CanTpRxPduPtr->SduLength)
         )
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_INVALID_RX_LENGTH
                          );
  }
  else
#endif
  {
    /* init */
    CanDataPtr = CanTpRxPduPtr->SduDataPtr;

    /* Initialize NSduId and NPCIIndex to prevent false uninitialized warnings
       from code verification tools and compilers - values are overwritten with
       the correct values by CanTp_FindNSduId() if the function succeeds.
     */
    NSduId = 0U;
    FrameType = 0U;

    /* search for the corresponding NSdu */
    if(CanTp_FindNSduId(CanTpRxPduId, CanDataPtr, &NSduId, &FrameType))
    {
      boolean RxProcessFlag = FALSE;
      uint8 PaddingActivation;

      /* If an NSdu for an FC was found it must be Tx, otherwise it's Rx */
      if(FrameType == CANTP_N_PCI_TYPE_FC)
      {
        Channel = CANTP_CFG_GET_TXNSDU_CONFIG(NSduId).Channel;
        PaddingActivation = CANTP_CFG_GET_TXNSDU_CONFIG(NSduId).PaddingActivation;
      }
      else
      {
        Channel = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).Channel;
        PaddingActivation = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).PaddingActivation;
      }
      ChannelPtr = &CanTp_Channel[Channel];

      /* If padding is enabled the NPdu length shall be filled with padding bytes to
         the maximum.
       */
      if(
          (CANTP_OFF == PaddingActivation)
          ||(
              (CANTP_ON == PaddingActivation)
              && (CanTpRxPduPtr->SduLength == CANTP_NPDU_LENGTH_MAX)
            )
        )
      {
        CANTP_ENTER_CRITICAL_SECTION();

        /* lock channel if possible */
        if(CANTP_IS_CHANNEL_LOCKED(ChannelPtr))
        {
          /* Postponing Rx Frame when channel is locked*/
          CanTp_PostponeRxFrame(
                                 ChannelPtr,
                                 CanTpRxPduPtr,
                                 NSduId,
                                 FrameType
                               );
        }
        else
        {
          CANTP_LOCK_CHANNEL(ChannelPtr);
          /* Setting RxProcessFlag to process the received frame */
          RxProcessFlag = TRUE;
        }
        CANTP_LEAVE_CRITICAL_SECTION();
        /* Checking RxProcessFlag to process the received frame */
        if(RxProcessFlag == TRUE)
        {
          /* Processing the received frame. */
          CanTp_ProcessRxFrame(
                                ChannelPtr,
                                CanTpRxPduPtr,
                                NSduId,
                                FrameType
                              );
          CANTP_UNLOCK_CHANNEL(ChannelPtr);
        }
      }
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
      else
      {
        /* length is wrong - call DET and ignore frame*/
        CANTP_DET_REPORT_ERROR(
                                CANTP_MODULE_ID,
                                CANTP_INSTANCE_ID,
                                CANTP_API_RXINDICATION,
                                CANTP_E_INVALID_RX_LENGTH
                              );
      }
#endif
    } /* if a configured N-SDU was found */
  }

  DBG_CANTP_RXINDICATION_EXIT(CanTpRxPduId, CanTpRxPduPtr);

} /* CanTp_RxIndication() */
#else /* => CANTP_JUMPTABLE_MODE == CANTP_JUMPTABLE_CLIENT */
{

  DBG_CANTP_RXINDICATION_ENTRY(CanTpRxPduId, CanTpRxPduPtr);
  (CanTp_EntryTablePtr->RxIndication)(CanTpRxPduId, CanTpRxPduPtr);

  DBG_CANTP_RXINDICATION_EXIT(CanTpRxPduId, CanTpRxPduPtr);
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#endif /* CANTP_PROVIDE_API_FUNCTIONS == STD_ON */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)
FUNC(void, CANTP_CODE) CanTp_PostRxIndication
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  PduInfoType CanTpNPdu; /* to store NPdu data pointer and length */
  uint8 NPduData[CANTP_NPDU_LENGTH_MAX]; /* to store NPdu data */
  PduIdType NSduId;
  uint8 FrameType; /* frame type of postponed frame */
  uint8_least Loop;
  boolean PendingFrame = FALSE; /* indicates if a frame is postponed */

  DBG_CANTP_POSTRXINDICATION_ENTRY(ChannelPtr);

  /* Initialization required to avoid "usage of uninitialized variables" warning. */
  NSduId = 0U;
  FrameType = 0U;
  CanTpNPdu.SduDataPtr = NULL_PTR;
  CanTpNPdu.SduLength = 0U;

  CANTP_ENTER_CRITICAL_SECTION();
  if(ChannelPtr->PostRxIndFlag)
  {
    /* Copy the postponed frame data to local variables. */
    for(Loop = 0U; Loop < CANTP_NPDU_LENGTH_MAX; Loop++)
    {
      NPduData[Loop] = ChannelPtr->PostRxIndData[Loop];
    }
    CanTpNPdu.SduDataPtr = &NPduData[0U];
    CanTpNPdu.SduLength = ChannelPtr->PostRxIndLength;
    NSduId = ChannelPtr->PostRxIndNSduId;
    FrameType = ChannelPtr->PostRxIndFrameType;

    /* Free postponed frame memory. */
    ChannelPtr->PostRxIndFlag = FALSE;
    PendingFrame = TRUE;
  }
  CANTP_LEAVE_CRITICAL_SECTION();

  if(PendingFrame)
  {
    CanTp_ProcessRxFrame(
                          ChannelPtr,
                          &CanTpNPdu,
                          NSduId,
                          FrameType
                        );
  }

  DBG_CANTP_POSTRXINDICATION_EXIT(ChannelPtr);
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

/*==================[internal function definitions]==========================*/

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

STATIC FUNC(void, CANTP_CODE) CanTp_PostponeRxFrame
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  PduIdType NSduId,
  uint8 FrameType
)
{
  DBG_CANTP_POSTPONERXFRAME_ENTRY(ChannelPtr, CanTpRxPduPtr, NSduId, FrameType);
  /* memorize Rx indication */
  TS_MemCpy(ChannelPtr->PostRxIndData, CanTpRxPduPtr->SduDataPtr, CANTP_NPDU_LENGTH_MAX);
  ChannelPtr->PostRxIndFlag = TRUE;
  ChannelPtr->PostRxIndNSduId = NSduId;
  ChannelPtr->PostRxIndLength = (uint8) CanTpRxPduPtr->SduLength;
  ChannelPtr->PostRxIndFrameType = FrameType;

  DBG_CANTP_POSTPONERXFRAME_EXIT(ChannelPtr, CanTpRxPduPtr, NSduId, FrameType);
}

STATIC FUNC(void, CANTP_CODE) CanTp_ProcessRxFrame
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  PduIdType NSduId,
  uint8 FrameType
)
{
  DBG_CANTP_PROCESSRXFRAME_ENTRY(ChannelPtr, CanTpRxPduPtr, NSduId, FrameType);

  switch(FrameType)
  {
    case CANTP_N_PCI_TYPE_SF: /* single frame handling */
    {
      CanTp_RxChannelCleanup(ChannelPtr);
      if(ChannelPtr->State == CANTP_CH_IDLE)
      {
        ChannelPtr->NSduId = NSduId; /* take this channel */
        CanTp_ProcessReceivedSF(CanTpRxPduPtr, ChannelPtr);
      }
      break;
    }
    case CANTP_N_PCI_TYPE_FF: /* First frame handling */
    {
      CanTp_RxChannelCleanup(ChannelPtr);
      if(ChannelPtr->State == CANTP_CH_IDLE)
      {
        ChannelPtr->NSduId = NSduId; /* take this channel */
        CanTp_ProcessReceivedFF(CanTpRxPduPtr, ChannelPtr);
      }
      break;
    }
    case CANTP_N_PCI_TYPE_CF: /* Consecutive frame handling */
    {
      /* Check NSdu id & actual channel mode, ignore frame if not correct */
      if((ChannelPtr->NSduId == NSduId)
         && (CANTP_CH_MODE_RX == CANTP_CH_GET_MODE(ChannelPtr))
        )
      {
        CanTp_ProcessReceivedCF(CanTpRxPduPtr, ChannelPtr);
      }
      break;
    }
    case CANTP_N_PCI_TYPE_FC: /* Flow control frame handling */
    {
      /* Check NSdu id, ignore frame if not correct */
      if(ChannelPtr->NSduId == NSduId)
      {
        CanTp_ProcessReceivedFC(CanTpRxPduPtr, ChannelPtr);
      }
      break;
    }
    default:
    {
      /* ignore unknown frame type */
      break;
    }
  }
  DBG_CANTP_PROCESSRXFRAME_EXIT(ChannelPtr, CanTpRxPduPtr, NSduId, FrameType);
}


STATIC FUNC(void, CANTP_CODE) CanTp_RxChannelCleanup
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  DBG_CANTP_RXCHANNELCLEANUP_ENTRY(ChannelPtr);
  /* CANTP290: Terminate current Rx but continue Tx */
  switch(CANTP_CH_GET_MODE(ChannelPtr))
  {
    case CANTP_CH_MODE_TX:
    {
      /* don't interrupt when channel is in Tx mode */
      break;
    }
    case CANTP_CH_MODE_IDLE:
    {
      /* channel is already idle -> Nothing to do. */
      break;
    }
    case CANTP_CH_MODE_RX:
    {
      if(
          CANTP_GET_CH_MODE(&CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId))
          == CANTP_MODE_FULL_DUPLEX
        )
      {
        /* !LINKSTO CanTp.ASR40.CANTP057_FullDuplex_6, 1, CanTp.ASR40.CANTP057_FullDuplex_7, 1 */
        /* Stop channel as SF/FF arrived while a reception is already going on in FULL DUPLEX channel
           and notify upper layer
         */
        CanTp_StopChannel(
                           ChannelPtr,
                           CANTP_ULIND_STATUS,
                           NTFRSLT_E_NOT_OK
                         );
      }
      else
      {
        /* !LINKSTO CanTp.ASR40.CANTP057_HalfDuplex_6, 2, CanTp.ASR40.CANTP057_HalfDuplex_7, 2 */
        /* Stop channel as SF/FF arrived while a reception is already going on in HALF DUPLEX channel
           and notify upper layer
         */
        CanTp_StopChannel(
                           ChannelPtr,
                           CANTP_ULIND_STATUS,
                           NTFRSLT_E_UNEXP_PDU
                         );
      }
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
  DBG_CANTP_RXCHANNELCLEANUP_EXIT(ChannelPtr);
}


STATIC FUNC(boolean, CANTP_CODE) CanTp_FindNSduId
(
  PduIdType CanTpRxPduId,
  P2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) CanDataPtr,
  P2VAR(PduIdType, AUTOMATIC, CANTP_APPL_DATA) NSduId,
  P2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) FrameType
)
{
  P2CONST(CanTp_RxNPduTableType, AUTOMATIC, CANTP_APPL_CONST)
    RxNPduTableEntry = &(CANTP_CFG_GET_RXNPDU_TABLE(CANTP_CFG_GET_RXNPDU_LOOKUPTABLE(CanTpRxPduId)));
  boolean FoundFlag;        /* found something? */
  uint8  SearchDirection;  /* N-Sdu direction */
  /* addressing format */
  const uint8  AddressingFormat= CANTP_GET_ADDR_FORMAT(RxNPduTableEntry);
  /* index of first N_PCI byte */
  const uint8  FirstNPCIByte = CANTP_GET_FIRST_N_PCI_BYTE(RxNPduTableEntry);
  uint8  N_SA_AE;          /* N_SA (extended adr.) or N_AE (mixed adr.) */
#if(CANTP_DYNAMIC_NSA_ENABLED == STD_ON)
  CanTp_RxNPduLookupEntryType  Index;   /* Index for CanTp_NSaValues[] */
#endif

  DBG_CANTP_FINDNSDUID_ENTRY(CanTpRxPduId, CanDataPtr, NSduId, FrameType);

  FoundFlag = FALSE;

  /* find out the direction of the search (based on frame type) */

#if(CANTP_DYNAMIC_NSA_ENABLED == STD_ON)
  /* Get first index out of Lookup Table */
  Index = CANTP_CFG_GET_RXNPDU_LOOKUPTABLE(CanTpRxPduId);
#endif

  /* a FC frame belongs to an Tx-Connection */
  if(CANTP_IS_N_PCI_TYPE_FC(CanDataPtr[FirstNPCIByte]))
  {
    SearchDirection = CANTP_PDU_DIR_TRANSMIT;
  }
  else
  {
    SearchDirection = CANTP_PDU_DIR_RECEIVE;
  }

  /* find the configured N-SDU */
  do
  {
    /* if direction is correct */
    if(RxNPduTableEntry->Direction == SearchDirection)
    {
      /* Get N_SA/N_AE value */
#if(CANTP_DYNAMIC_NSA_ENABLED == STD_ON)
      if(AddressingFormat == CANTP_EXTENDED)
      {
        /* get N_SA value which was set at runtime */
        TS_AtomicAssign8(N_SA_AE,CanTp_NSaValues[Index]);
      }
      else
      {
        /* get dummy N_SA/N_AE (standard adr.) or N_AE (mixed adr.) value */
        N_SA_AE = RxNPduTableEntry->N_SA_AE;
      }
#else
      /* get configured N_SA/N_AE value */
      N_SA_AE = RxNPduTableEntry->N_SA_AE;
#endif

      /* if addressing format is standard or
       * addressing format is extended and N_SA (first byte) is correct or
       * addressing format is mixed and N_AE (first byte) is correct
       */
      if((AddressingFormat == CANTP_STANDARD) || (CanDataPtr[0] == N_SA_AE))
      {
        /* this is the correct NSdu */
        FoundFlag = TRUE;
        *NSduId = RxNPduTableEntry->Index;
        *FrameType = CANTP_GET_N_PCI_TYPE(CanDataPtr[FirstNPCIByte]);
      }
    }

    /* get next element */
    if(RxNPduTableEntry->Next != 0U)
    {
#if(CANTP_DYNAMIC_NSA_ENABLED == STD_ON)
      /* get next index */
      Index = RxNPduTableEntry->Next;
#endif
      RxNPduTableEntry = &(CANTP_CFG_GET_RXNPDU_TABLE(RxNPduTableEntry->Next));
    }
    else
    {
      /* no more matching N-PDUs - quit the search */
      break;
    }
  } while(FoundFlag == FALSE);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  if((AddressingFormat == CANTP_STANDARD) && (FoundFlag == FALSE))
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_INVALID_RX_ID
                          );
  }
#endif

  DBG_CANTP_FINDNSDUID_EXIT(FoundFlag, CanTpRxPduId, CanDataPtr, NSduId, FrameType);

  return FoundFlag;
}


STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedSF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  /* Pointer  to N-Sdu config */
  CONSTP2CONST(CanTp_RxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) RxNSduCfgPtr
                            = &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId);

  /* Start position of first N_PCI byte within the NPdu. */
  const uint8 StartPosition_SF_N_PCI = CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr);

  /* Encoded TP length from N_PCI data field of the Can frame: */
  const uint8 DataLength = CanTpRxPduPtr->SduDataPtr[StartPosition_SF_N_PCI]
                           & CANTP_N_PCI_SF_DL_MASK;

  /* Minimum number of bytes required (Header + data length) */
  const uint8 MinSduLength = StartPosition_SF_N_PCI
                             + CANTP_SF_NPCI_SIZE
                             + DataLength;

  boolean ValidFrameLength; /* Indication for valid the data length. */

  DBG_CANTP_PROCESSRECEIVEDSF_ENTRY(CanTpRxPduPtr, ChannelPtr);

  /* Check data length encoded from N_PCI */
  if(DataLength == 0U)
  {
    /* A single frame shall at least contain one byte of data. */
    ValidFrameLength = FALSE;
  }
  else if(CanTpRxPduPtr->SduLength < MinSduLength)
  {
    /* Frame length (NPdu) shall at least be big enough to hold the
       header and the encoded data length of N_PCI
     */
    ValidFrameLength = FALSE;
  }
  else
  {
    ValidFrameLength = TRUE; /* all checks passed */
  }

  /* quick check if length is as expected */
  if(ValidFrameLength)
  {
    /* Data length is okay */
    Std_ReturnType Ret;

    /* Pointer to upper layer data */
    CONSTP2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) NSduDataPtr
        = &(CanTpRxPduPtr->SduDataPtr[StartPosition_SF_N_PCI + CANTP_SF_NPCI_SIZE]);

    /* setup channel and request buffer */
    ChannelPtr->TotalLength = DataLength;
    ChannelPtr->Ticks = CANTP_GET_RX_PDU_N_BR(RxNSduCfgPtr);

    DBG_CANTP_CHANNEL_STATE_GRP(
                                DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                ChannelPtr->State,
                                CANTP_CH_RX_BUFREQ_SF
                               );

    ChannelPtr->State = CANTP_CH_RX_BUFREQ_SF; /* set to first state */

     Ret = CanTp_ProcessStartOfReception(ChannelPtr);

     if(Ret == E_OK)
     {
       /* Reception started. Try to copy FF data. */
       BufReq_ReturnType Ret_ReqRxBuffer;

       Ret_ReqRxBuffer = CanTp_ProcessStartOfReceptionData
                                  (
                                    ChannelPtr,
                                    NSduDataPtr,
                                    DataLength
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
           /* Store data and wait in state CANTP_CH_RX_BUFREQ_SF (already set) until
              buffer is available or timeout occurs.
            */
           TS_MemCpy(ChannelPtr->TempBuffer, NSduDataPtr, DataLength);
           ChannelPtr->TempLength = DataLength;

           break;
         }
         default:
         {
           /* Unexpected return value. Close channel. */
           CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
           break;
         }
       }
     }
  }
  else /* N-PDU has an invalid rx length */
  {
    /* Data length is not okay -> Free channel */
    CanTp_StopChannel(ChannelPtr, CANTP_ULIND_NONE, NTFRSLT_E_NOT_OK);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_INVALID_RX_LENGTH
                          );
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
  }

  DBG_CANTP_PROCESSRECEIVEDSF_EXIT(CanTpRxPduPtr, ChannelPtr);

}/* CanTp_ProcessReceivedSF() */


STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedFF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  /* Pointer to N-Sdu config */
  CONSTP2CONST(CanTp_RxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) RxNSduCfgPtr =
      &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId);

  boolean ValidFirstFrame; /* Indication for valid first frame. */
  uint16 MessageLength;

  /* Start position of first N_PCI byte within the NPdu. */
  const uint8 StartPosition_FF_N_PCI = CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr);

  /* For checking whether the data can fit in a SF */
  const uint8 FFValidLength = CANTP_SF_MAX_NSDU_LENGTH - CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr);

  DBG_CANTP_PROCESSRECEIVEDFF_ENTRY(CanTpRxPduPtr, ChannelPtr);

  /* Calculate the total length of the whole message.
     Total length: 12 bits (lower 4 bits of N_PCI byte 0 + all
     8 bits of N_PCI byte 1) The position of N_PCI depends on the addressing format.
   */
  MessageLength = ((uint16) (CanTpRxPduPtr->SduDataPtr[StartPosition_FF_N_PCI]) &
                             CANTP_N_PCI_FF_DL_MASK
                  );
  MessageLength = MessageLength << 8U;
  MessageLength = MessageLength | ((uint16) (CanTpRxPduPtr->SduDataPtr[StartPosition_FF_N_PCI + 1U]));


  if(RxNSduCfgPtr->Tatype != CANTP_PHYSICAL)
  {
    /* FF is only allowed for physical addressing (functional addressing is only allowed for SF) */
    ValidFirstFrame = FALSE;
  }
  else if(CanTpRxPduPtr->SduLength != CANTP_NPDU_LENGTH_MAX)
  {
    /* The FF shall not be smaller than the maximum frame length (NPdu) */
    ValidFirstFrame = FALSE;
  }
  else if(MessageLength <= FFValidLength)
  {
    /* The total message length shall fit into a single frame, no need of FF. */
    ValidFirstFrame = FALSE;
  }
  else
  {
    /* Store calculated message length. */
    ChannelPtr->TotalLength = MessageLength;

    /* All data and message length checks passed. */
    ValidFirstFrame = TRUE;
  }

  /* check if length is as expected and communication is not functional */
  if(ValidFirstFrame)
  {
    Std_ReturnType Ret;

    /* NSdu data length of first frame */
    const uint8 DataLength_FF = CANTP_NPDU_LENGTH_MAX
                                - StartPosition_FF_N_PCI
                                - CANTP_FF_NPCI_SIZE;
    /* Pointer to upper layer data */
    CONSTP2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) NSduDataPtr
        = &(CanTpRxPduPtr->SduDataPtr[StartPosition_FF_N_PCI + CANTP_FF_NPCI_SIZE]);

    /* setup channel and request for buffer */
    ChannelPtr->ProcessedLength = 0U;
    ChannelPtr->WftCounter = CANTP_GET_RX_PDU_WFT_MAX(RxNSduCfgPtr);
    /* N_Br is the waiting time for the FC(WT) frame, N_Ar is the timeout,
       so buffer request and transmission must be finished after N_Br+N_Ar
     */
    ChannelPtr->Ticks = CANTP_GET_RX_PDU_N_BR(RxNSduCfgPtr) +
                        CANTP_GET_RX_PDU_N_AR(RxNSduCfgPtr);

    DBG_CANTP_CHANNEL_STATE_GRP(
                                DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                ChannelPtr->State,
                                CANTP_CH_RX_BUFREQ_FF
                               );

    ChannelPtr->State = CANTP_CH_RX_BUFREQ_FF;

    Ret = CanTp_ProcessStartOfReception(ChannelPtr);

    if(Ret == E_OK)
    {
      /* Reception started. Try to copy FF data. */
      BufReq_ReturnType Ret_ReqRxBuffer;

      Ret_ReqRxBuffer = CanTp_ProcessStartOfReceptionData
                                 (
                                   ChannelPtr,
                                   NSduDataPtr,
                                   DataLength_FF
                                 );
      switch(Ret_ReqRxBuffer)
      {
        case BUFREQ_OK:
        {
          Std_ReturnType BSCalc_Ok; /* Indication of the actual BS calculation */

          /* Data of FF processed */
          ChannelPtr->ProcessedLength = DataLength_FF;

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
            /* Wait in state CANTP_CH_RX_BUFREQ_FF (already set) until
               enough buffer for BS is available or timeout occurs.
            */
            /* Send wait frame if timeout already elapsed */
            CanTp_CheckAndHandleWaitFrameTimeOut(ChannelPtr);
          }
          break;
        }
        case BUFREQ_E_BUSY:
        {
          /* Store data and wait in state CANTP_CH_RX_BUFREQ_FF (already set) until
             buffer is available or timeout occurs.
           */
          TS_MemCpy(ChannelPtr->TempBuffer, NSduDataPtr, DataLength_FF);
          ChannelPtr->TempLength = DataLength_FF;

          /* Send wait frame if timeout already elapsed */
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
    }
  }
  else
  {
    /* FF is invalid */
    CanTp_StopChannel(ChannelPtr, CANTP_ULIND_NONE, NTFRSLT_E_NOT_OK);

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
    if(RxNSduCfgPtr->Tatype == CANTP_FUNCTIONAL)
    {
      /* wrong TA Type */
      CANTP_DET_REPORT_ERROR(
                              CANTP_MODULE_ID,
                              CANTP_INSTANCE_ID,
                              CANTP_API_RXINDICATION,
                              CANTP_E_INVALID_TATYPE
                            );
    }
    else
    {
      /* wrong length */
      CANTP_DET_REPORT_ERROR(
                              CANTP_MODULE_ID,
                              CANTP_INSTANCE_ID,
                              CANTP_API_RXINDICATION,
                              CANTP_E_INVALID_RX_LENGTH
                            );
    }
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
  }

  DBG_CANTP_PROCESSRECEIVEDFF_EXIT(CanTpRxPduPtr, ChannelPtr);
} /* CanTp_ProcessReceivedFF() */



STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedCF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  DBG_CANTP_PROCESSRECEIVEDCF_ENTRY(CanTpRxPduPtr, ChannelPtr);
  /* Check for expected state and ignore frame if its state is not expected. */
  if((ChannelPtr->State == CANTP_CH_RX_RECEIVE_CF) || (ChannelPtr->State == CANTP_CH_RX_CONFIRM_FC_CTS))
  {
    /* ptr to N-Sdu config */
    CONSTP2CONST(CanTp_RxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) RxNSduCfgPtr
        = &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId);

    /* Start position of first N_PCI byte within the NPdu. */
    const uint8 StartPosition_CF_N_PCI = CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr);

    /* if this is the wrong sequence number - stop channel */
    if(
         ChannelPtr->SequenceNumber !=
         (CanTpRxPduPtr->SduDataPtr[StartPosition_CF_N_PCI] & CANTP_N_PCI_CF_SN_MASK)
       )
    {
      /* CanTp.ASR40.CANTP314: check correctness of SN, abort with
         NTFRSLT_E_WRONG_SN if wrong.
       */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_WRONG_SN
                       );
    }
    else
    {
      /* calculate remaining bytes / Delta needed for this N-Sdu */
      uint16 Delta = (ChannelPtr->TotalLength - ChannelPtr->ProcessedLength);
      const uint8 SingleFrameLength = (
                                        CANTP_NPDU_LENGTH_MAX
                                        - StartPosition_CF_N_PCI
                                        - CANTP_SF_NPCI_SIZE
                                      );

      /* is this the last CF for the N-Sdu / does the Delta fit in a frame? */
      if(Delta <= SingleFrameLength)
      {
        CanTp_ProcessReceivedLastCF(
                                     CanTpRxPduPtr,
                                     ChannelPtr,
                                     (uint8) Delta
                                   );
      }
      else
      {
        CanTp_ProcessReceivedIntermediateCF(
                                             CanTpRxPduPtr,
                                             ChannelPtr
                                           );
      }
    }
  }
  else
  {
    /* According to ISO15765 table 18 ignore unexpected CF */
  }

  DBG_CANTP_PROCESSRECEIVEDCF_EXIT(CanTpRxPduPtr, ChannelPtr);
} /* CanTp_ProcessReceivedCF() */


STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedIntermediateCF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  DBG_CANTP_PROCESSRECEIVEDINTERMEDIATECF_ENTRY(CanTpRxPduPtr, ChannelPtr);
  /* this is an intermediate CF - length must be 8 */
  if(CanTpRxPduPtr->SduLength == CANTP_NPDU_LENGTH_MAX)
  {
    BufReq_ReturnType Ret_CopyRxData;

    /* ptr to N-Sdu config */
    CONSTP2CONST(CanTp_RxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) RxNSduCfgPtr
        = &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId);

    /* Start position of first N_PCI byte within the NPdu. */
    const uint8 StartPosition_CF_N_PCI = CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr);

    /* Pointer to upper layer data */
    CONSTP2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) NSduDataPtr
        = &(CanTpRxPduPtr->SduDataPtr[StartPosition_CF_N_PCI + CANTP_CF_NPCI_SIZE]);

    const uint8 DataLength = CANTP_NPDU_LENGTH_MAX
                             - CANTP_CF_NPCI_SIZE
                             - StartPosition_CF_N_PCI;

    /* valid frame - increment sequence number to be correct for next CF */
    ChannelPtr->SequenceNumber++;

    /* wrap around sequence number */
    ChannelPtr->SequenceNumber &= CANTP_N_PCI_CF_SN_MASK;

    Ret_CopyRxData = CanTp_RxProcessData(ChannelPtr, NSduDataPtr, DataLength);

    if(BUFREQ_OK == Ret_CopyRxData)
    {
      /* one more frame of the actual block received successfully */
      ChannelPtr->ProcessedLength += (uint16) DataLength;

      if(0U == ChannelPtr->BlockSize)
      {
        /* Message will be sent within a big single block. No block checking required */
        /* Set ChannelPtr->ProcessedBlockFrames to a value != 0U (end of block indication)
            to avoid sending wait frames while waiting for a buffer.
         */
        ChannelPtr->ProcessedBlockFrames = 0x0FU;
      }
      else
      {
        ChannelPtr->ProcessedBlockFrames++;
      }

      if(ChannelPtr->ProcessedBlockFrames == ChannelPtr->BlockSize)
      {
        boolean ContinueWithNextBlock;

        /* this was the last block in this session */
        ChannelPtr->ProcessedBlockFrames = 0U;

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
          /* Not enough buffer for the next block available. Request for buffer at next
             main function call.
           */

          /* N_Br is the waiting time for the FC(WT) frame, N_Ar is the
             timeout, so buffer request and transmission must be finished
             after N_Br+N_Ar
           */
          ChannelPtr->Ticks = CANTP_GET_RX_PDU_N_BR(&CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId)) +
                              CANTP_GET_RX_PDU_N_AR(&CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId));

          /* reset FC(WT) counter */
          ChannelPtr->WftCounter = CANTP_GET_RX_PDU_WFT_MAX(&CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId));

          DBG_CANTP_CHANNEL_STATE_GRP(
                                      DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                      ChannelPtr->State,
                                      CANTP_CH_RX_BUFREQ_CF
                                     );

          ChannelPtr->State = CANTP_CH_RX_BUFREQ_CF; /* Set state to request buffer for next block. */

          /* Send wait frame if timeout already elapsed */
          CanTp_CheckAndHandleWaitFrameTimeOut(ChannelPtr);
        }
      }
      else
      {
        /* CF within a block received. Wait for next CF */
        ChannelPtr->Ticks = CANTP_GET_RX_PDU_N_CR(&CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId));

        DBG_CANTP_CHANNEL_STATE_GRP(
                                    DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                    ChannelPtr->State,
                                    CANTP_CH_RX_RECEIVE_CF
                                   );

        ChannelPtr->State = CANTP_CH_RX_RECEIVE_CF;
      }
    }
    else
    {
      /* Error during processing of CF data. */
      CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
    }
  }
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  else /* if SDU length was wrong */
  {
    /* length is invalid -> ignore frame but DET */
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_INVALID_RX_LENGTH
                          );
  }
#endif
  DBG_CANTP_PROCESSRECEIVEDINTERMEDIATECF_EXIT(CanTpRxPduPtr, ChannelPtr);
}

STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedLastCF
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  uint8 DataLength
)
{
  boolean ValidFrameLength; /* Indication if last CF length is in valid range. */

  /* ptr to N-Sdu config */
  CONSTP2CONST(CanTp_RxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) RxNSduCfgPtr
      = &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId);

  /* Start position of first N_PCI byte within the NPdu. */
  const uint8 StartPosition_CF_N_PCI = CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr);

  /* Minimum required Sdu length to hold header and data */
  const uint8 MinReqSduLength = StartPosition_CF_N_PCI + CANTP_CF_NPCI_SIZE + DataLength;

  DBG_CANTP_PROCESSRECEIVEDLASTCF_ENTRY(CanTpRxPduPtr, ChannelPtr, DataLength);

  /* Function shall never be called with nod data. This indicates a bug. */
  CANTP_PRECONDITION_ASSERT((DataLength > 0U), CANTP_INTERNAL_API_ID);

  if(CanTpRxPduPtr->SduLength < MinReqSduLength)
  {
    /* SduLength shall be at least big enough to hold the
       header and the encoded data length of N_PCI
     */
    ValidFrameLength = FALSE;
  }
  else
  {
    ValidFrameLength = TRUE; /* all checks passed */
  }

  /* Only process if last CF length is valid */
  if(ValidFrameLength)
  {
    BufReq_ReturnType Ret_CopyRxData;

    /* Pointer to upper layer data */
    CONSTP2VAR(uint8, AUTOMATIC, CANTP_APPL_DATA) NSduDataPtr
        = &(CanTpRxPduPtr->SduDataPtr[StartPosition_CF_N_PCI + CANTP_CF_NPCI_SIZE]);

    Ret_CopyRxData = CanTp_RxProcessData(ChannelPtr, NSduDataPtr, DataLength);

    if(BUFREQ_OK == Ret_CopyRxData)
    {
      /* Message reception completed. The whole message was copied to
         upper layer successfully.
       */
      CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_OK);
    }
    else
    {
      /* Error during processing of last CF data. */
      CanTp_StopChannel(ChannelPtr, CANTP_ULIND_STATUS, NTFRSLT_E_NOT_OK);
    }
  }
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
  else
  {
    /* length is invalid -> ignore frame but DET */
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_RXINDICATION,
                            CANTP_E_INVALID_RX_LENGTH
                          );
  }
#endif
  DBG_CANTP_PROCESSRECEIVEDLASTCF_EXIT(CanTpRxPduPtr, ChannelPtr, DataLength);
}

STATIC FUNC(void, CANTP_CODE) CanTp_ProcessReceivedFC
(
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_DATA) CanTpRxPduPtr,
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  /* ptr to N-Sdu config */
  CONSTP2CONST(CanTp_TxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) TxNSduCfgPtr
      = &CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId);

  /* Start position of first N_PCI byte within the NPdu. */
  const uint8 StartPosition_FC_N_PCI = CANTP_GET_FIRST_N_PCI_BYTE(TxNSduCfgPtr);

  DBG_CANTP_PROCESSRECEIVEDFC_ENTRY(CanTpRxPduPtr, ChannelPtr);

  /* check for correct channel state and ignore frame if it is not */
  switch(ChannelPtr->State)
  {
    case CANTP_CH_TX_RECEIVE_FC: /* Fall through */
    case CANTP_CH_TX_CONFIRM_FF: /* Fall through */
    case CANTP_CH_TX_CONFIRM_CF:
    {
      boolean ValidFrameLength; /* Indication if FC frame length is in valid range. */
      boolean ExpectedFrame; /* Verify if frame is expected */
      const uint8 HeaderBytes = StartPosition_FC_N_PCI + CANTP_FC_NPCI_SIZE;

      /* NSdu length must be at minimum equal to the required header bytes */
      if(CanTpRxPduPtr->SduLength < HeaderBytes)
      {
        /* Frame length (NPdu) must be at minimum equal to the required header bytes */
        ValidFrameLength = FALSE;
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
        /* length is wrong - call DET */
        CANTP_DET_REPORT_ERROR(
                                CANTP_MODULE_ID,
                                CANTP_INSTANCE_ID,
                                CANTP_API_RXINDICATION,
                                CANTP_E_INVALID_RX_LENGTH
                              );
#endif
      }
      else
      {
        ValidFrameLength = TRUE; /* all checks passed */
      }

      if(ChannelPtr->BlockSize == 0U)
      {
        ExpectedFrame = FALSE; /* No FC needed. */
      }
      else if(ChannelPtr->BlockSize != ChannelPtr->ProcessedBlockFrames)
      {
        ExpectedFrame = FALSE; /* Not at the end of a block or after a FF. */
      }
      else if(ChannelPtr->TotalLength == ChannelPtr->ProcessedLength)
      {
        ExpectedFrame = FALSE; /* All data are processed. */
      }
      else
      {
        ExpectedFrame = TRUE; /* All checks passed. */
      }

      /* Only process if FC length is valid */
      if(ValidFrameLength && ExpectedFrame)
      {
        /* ptr to can data */
        CONSTP2CONST(uint8, AUTOMATIC, CANTP_APPL_DATA) CanDataPtr
                                                     = CanTpRxPduPtr->SduDataPtr;

        /* check flow status */
        switch(CanDataPtr[StartPosition_FC_N_PCI])
        {
          case CANTP_N_PCI_FC_CTS:
          {
            const CanTp_ChStateType CurrentState = ChannelPtr->State;
            uint8 DataIndex = StartPosition_FC_N_PCI;  /* Can data index */

            DataIndex++; /* next byte after N_PCI is BS */
            ChannelPtr->BlockSize = CanDataPtr[DataIndex];
            ChannelPtr->ProcessedBlockFrames = 0U; /* Reset frame counter within a block */

            /* if this is the first FC, indicated by StMin = 0xFF (reserved) */
            if(ChannelPtr->StMin == 0xFFU)
            {
              DataIndex++; /* next byte after BS is StMin*/
              ChannelPtr->StMin = CanDataPtr[DataIndex];

              /* if StMin is not valid */
              if(
                  (
                    (ChannelPtr->StMin >= 0x80U)
                     && (ChannelPtr->StMin <= 0xF0U)
                  )
                  || (ChannelPtr->StMin >= 0xFAU)
                )
              {
                /* set StMin to max value as specified by ISO */
                ChannelPtr->StMin = 0x7FU;
              }
            }

            ChannelPtr->Ticks = CANTP_GET_TX_PDU_N_CS(TxNSduCfgPtr);

            DBG_CANTP_CHANNEL_STATE_GRP(
                                        DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                        ChannelPtr->State,
                                        CANTP_CH_TX_BUFREQ_CF
                                       );

            ChannelPtr->State = CANTP_CH_TX_BUFREQ_CF;

            /* Send next frame immediately if FC(CTS) is received. In case that
               Tx confirmation is outstanding, delay the transmission until next main function. */
            if(CurrentState == CANTP_CH_TX_RECEIVE_FC)
            {
              CanTp_TxStateHandling(ChannelPtr);
            }
            break;
          }
          case CANTP_N_PCI_FC_WT:
          {
            /* wait; restart N_Bs timeout */
            ChannelPtr->Ticks = CANTP_GET_TX_PDU_N_BS(TxNSduCfgPtr);
            break;
          }
          case CANTP_N_PCI_FC_OVFLW:
          {
            /* CanTp.ASR40.CANTP309: FC OVFLW received -> report to PduR
               with result NTFRSLT_E_NO_BUFFER
             */
            CanTp_StopChannel(
                               ChannelPtr,
                               CANTP_ULIND_STATUS,
                               NTFRSLT_E_NO_BUFFER
                             );
            break;
          }
          default:
          {
            /* CanTp.ASR40.CANTP317: on invalid flow control status, stop channel
               and report result NTFRSLT_E_INVALID_FS
             */
            CanTp_StopChannel(
                               ChannelPtr,
                               CANTP_ULIND_STATUS,
                               NTFRSLT_E_INVALID_FS
                             );
            break;
          }
        }
      }
      break;
    }
    default:
    {
      /* Ignore FC frame if not expected. */
      break;
    }
  }

  DBG_CANTP_PROCESSRECEIVEDFC_EXIT(CanTpRxPduPtr, ChannelPtr);
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[end of file]============================================*/
