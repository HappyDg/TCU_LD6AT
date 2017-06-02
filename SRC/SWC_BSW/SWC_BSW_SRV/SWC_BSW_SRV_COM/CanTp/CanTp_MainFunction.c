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

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

/** \brief CanTp_StallHandling()
 **
 ** This function is to reduce the possibility of CF bursts stalling
 ** the transmission of FC frames in concurrent connections
 **
 */
STATIC FUNC(void, CANTP_CODE) CanTp_StallHandling(void);

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

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

/** \brief CanTp_MainFunction()
 **
 ** This API-Service is called cyclically, takes further individual steps for each
 ** channel and checks the timeouts */
FUNC(void, CANTP_CODE) CanTp_MainFunction(void)
#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)
{
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;
  uint8 Channel;  /* counter for channels */
  boolean Notify[CANTP_MAX_TX_CHANNELS] = {FALSE};

  DBG_CANTP_MAINFUNCTION_ENTRY();

  /* only do something in state CANTP_ON */
  if(CanTp_InitVars.State == CANTP_ON)
  {
    CANTP_ENTER_CRITICAL_SECTION();

    /* check counter for every channel, call callback routine if necessary */
    for(Channel = 0U; Channel < CanTp_CfgPtr->NumberOfTxChannels; Channel++)
    {
      ChannelPtr = &CanTp_Channel[Channel];
      Notify[Channel] = FALSE;

      if(ChannelPtr->MfCounterTicks > 0U)
      {
        /* decrease STmin counter and call notification function if 0 */
        ChannelPtr->MfCounterTicks--;
        if(ChannelPtr->MfCounterTicks == 0U)
        {
          Notify[Channel] = TRUE;
        }
      }
    }

    CANTP_LEAVE_CRITICAL_SECTION();

    for(Channel = 0U; Channel < CanTp_CfgPtr->NumberOfTxChannels; Channel++)
    {
      if(Notify[Channel] == TRUE)
      {
        /* call callback routine */
        CanTp_STminCallback(Channel);
      }
    }

    /* Handling stall condition in concurrent connections */
    CanTp_StallHandling();
  } /* if CanTp is on */

  DBG_CANTP_MAINFUNCTION_EXIT();

}/* CanTp_MainFunction() */
#else /* => CANTP_JUMPTABLE_MODE == CANTP_JUMPTABLE_CLIENT */
{

  DBG_CANTP_MAINFUNCTION_ENTRY();
  (CanTp_EntryTablePtr->MainFunction)();

  DBG_CANTP_MAINFUNCTION_EXIT();
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */
#endif /* CANTP_PROVIDE_API_FUNCTIONS == STD_ON */


#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)
FUNC(void, CANTP_CODE) CanTp_TimeoutHandling
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  DBG_CANTP_TIMEOUTHANDLING_ENTRY(ChannelPtr);

/* ---------------------Rx States ------------------*/
  switch(ChannelPtr->State)
  {
    case CANTP_CH_RX_BUFREQ_CF:
    case CANTP_CH_RX_BUFREQ_FF:
    {
      /* CanTp.ASR40.CANTP223.2: Can only be reached if maximum number of wait frames exceeded.
       * -> abort with result NTFRSLT_E_WFT_OVRN
       */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_WFT_OVRN
                       );
      break;
    }
    case CANTP_CH_RX_BUFREQ_SF:
    {
      /* Possible timeout for SF */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_NOT_OK
                       );
      break;
    }
    case CANTP_CH_RX_TRANSMIT_FC_CTS:
    case CANTP_CH_RX_TRANSMIT_FC_OVFLW:
    case CANTP_CH_RX_TRANSMIT_FC_WT:
    case CANTP_CH_RX_CONFIRM_FC_CTS:
    case CANTP_CH_RX_CONFIRM_FC_OVFLW:
    case CANTP_CH_RX_CONFIRM_FC_WT:
    {
      /* CanTp.ASR40.CANTP311: no confirmation for FC frame
         -> abort with NTFRSLT_E_TIMEOUT_A
       */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_TIMEOUT_A
                       );
      break;
    }
    case CANTP_CH_RX_RECEIVE_CF:
    {
      /* CanTp.ASR40.CANTP313: timeout while waiting for CF
         -> abort with NTFRSLT_E_TIMEOUT_CR
       */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_TIMEOUT_CR
                       );
      break;
    }

    /* ---------------------Tx States ------------------*/
    case CANTP_CH_TX_TRANSMIT_SF:
    case CANTP_CH_TX_TRANSMIT_FF:
    case CANTP_CH_TX_TRANSMIT_CF:
    case CANTP_CH_TX_CONFIRM_SF:
    case CANTP_CH_TX_CONFIRM_FF:
    case CANTP_CH_TX_CONFIRM_CF:
    {
      /* CanTp.ASR40.CANTP310: no confirmation from CAN driver
         -> abort with NTFRSLT_E_TIMEOUT_A
       */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_TIMEOUT_A
                       );
      break;
    }
    case CANTP_CH_TX_RECEIVE_FC:
    {
      /* CanTp.ASR40.CANTP316: Timeout between indication of FC WT
         and next FC */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_TIMEOUT_BS
                       );
      break;
    }
    case CANTP_CH_TX_WAITTMR_CF:
    case CANTP_CH_TX_BUFREQ_SF:
    case CANTP_CH_TX_BUFREQ_FF:
    case CANTP_CH_TX_BUFREQ_CF:
    default:
    {
      /* Possible timeout while in buff request */
      CanTp_StopChannel(
                         ChannelPtr,
                         CANTP_ULIND_STATUS,
                         NTFRSLT_E_NOT_OK
                       );
      break;
    }
  }

  DBG_CANTP_TIMEOUTHANDLING_EXIT(ChannelPtr);
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT ) */

/*==================[internal function definitions]==========================*/

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

STATIC FUNC(void, CANTP_CODE) CanTp_StallHandling
(
void
)
{
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;
  uint8 Channel;

  DBG_CANTP_STALLHANDLING_ENTRY();

  /* check all connection channels */
  /* !LINKSTO CanTp.EB.FullDuplex.1,1 */
  /* Annotation: We are counting down to first traverse the Rx channels,
     followed by the Tx channels. Aim is to reduce the possibility of CF
     bursts stalling the transmission of FC frames in concurrent connections
     (compare the requirement CanTp.EB.FullDuplex.1). */
  Channel = CanTp_CfgPtr->NumberOfChannels;
  do
  {
    boolean StallHandlingFlag = FALSE;

    Channel--;

    CANTP_ENTER_CRITICAL_SECTION();

    ChannelPtr = &CanTp_Channel[Channel];

    /* a timeout is not considered in idle mode */
    if(ChannelPtr->State != CANTP_CH_IDLE)
    {
      /* if channel is locked */
      if(CANTP_IS_CHANNEL_LOCKED(ChannelPtr))
      {
        /* add a post tick to the channel */
        ChannelPtr->PostTicks++;
      }
      else
      {
        /* lock channel */
        CANTP_LOCK_CHANNEL(ChannelPtr);
        /* Setting StallHandlingFlag for Stall Handling */
        StallHandlingFlag = TRUE;
      }/* if(channel locked) */
    }

    /* channel is in IDLE mode or locked: leave critical section */
    CANTP_LEAVE_CRITICAL_SECTION();
    /* Checking StallHandlingFlag for Stall Handling */
    if(StallHandlingFlag == TRUE)
    {
      /* has a timeout occured ? */
      if(ChannelPtr->Ticks == 0U)
      {
        CanTp_TimeoutHandling(ChannelPtr);
      }
      else
      {
        /* countdown ticks */
        ChannelPtr->Ticks--;

        /* Try to bring state machine into next state */
        if(CANTP_CH_GET_MODE(ChannelPtr) == CANTP_CH_MODE_RX)
        {
          CanTp_RxStateHandling(ChannelPtr);
        }
        else
        {
          CanTp_TxStateHandling(ChannelPtr);
        }
      }

      /* unlock the channel again */
      CANTP_UNLOCK_CHANNEL(ChannelPtr);
    }
  } while(Channel > 0U);

  DBG_CANTP_STALLHANDLING_EXIT();
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT ) */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[end of file]============================================*/
