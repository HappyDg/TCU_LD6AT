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
#include <CanTp_InternalCfg.h> /* CanTp internal configuration */
#include <CanTp_Internal.h>    /* internal macros and variables */

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

FUNC(void, CANTP_CODE) CanTp_PrepareFCwt
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  /* affected N-Sdu */
  const PduIdType NSduId = ChannelPtr->NSduId;
  uint8     DataIndex; /* index to help prepare data */

  DBG_CANTP_PREPAREFCWT_ENTRY(ChannelPtr);

  DataIndex = 0U;

  /* set N_TA/N_AE value on extended/mixed addressing */
  /* no N_TA/N_AE in standard addressing case */
  if(CANTP_GET_ADDR_FORMAT(&CANTP_CFG_GET_RXNSDU_CONFIG(NSduId)) != CANTP_STANDARD)
  {
    ChannelPtr->CanIfData[0U] = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).N_TA_AE;
    DataIndex = 1U;
  }

  /* set N_PCI */
  ChannelPtr->CanIfData[DataIndex] = CANTP_N_PCI_FC_WT;
  DataIndex++;

  /* set BS */
  ChannelPtr->CanIfData[DataIndex] = CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId);
  DataIndex++;

  /* set StMin */
  ChannelPtr->CanIfData[DataIndex] = CANTP_GET_RX_PDU_ST_MIN(NSduId);

  /* set DLC */
  if(CANTP_GET_PDU_PADDING(&CANTP_CFG_GET_RXNSDU_CONFIG(NSduId)) == CANTP_ON)
  {
    ChannelPtr->CanIfDLC = DataIndex + 1U;
    CANTP_PREPAREPADDING(ChannelPtr);
  }
  else
  {
    ChannelPtr->CanIfDLC = DataIndex + 1U;
  }

  /* transmit frame (N_Ar timer already running) */
  CanTp_TransmitFrame(ChannelPtr);

  DBG_CANTP_PREPAREFCWT_EXIT(ChannelPtr);
}

FUNC(void, CANTP_CODE) CanTp_CheckAndHandleWaitFrameTimeOut
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{

  DBG_CANTP_CHECKANDHANDLEWAITFRAMETIMEOUT_ENTRY(ChannelPtr);

  if(ChannelPtr->WftCounter > 0U)
  {
    /* initial tick count is (N_Br+N_Ar). if tick count equals or is smaller
       than N_Ar, N_Br is elapsed -> send a wait frame
     */
    if(ChannelPtr->Ticks <= CANTP_GET_RX_PDU_N_AR
                             (
                               &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId)
                             )
       )
    {
      DBG_CANTP_CHANNEL_STATE_GRP(
                                  DBG_CANTP_GET_CHANNEL_INDEX(ChannelPtr),
                                  ChannelPtr->State,
                                  CANTP_CH_RX_TRANSMIT_FC_WT
                                 );

      /* set new state, timeout remains */
      ChannelPtr->State = CANTP_CH_RX_TRANSMIT_FC_WT;
      CanTp_PrepareFCwt(ChannelPtr);
    }
  } /* else timeout occurs which will be handled in main function */

  DBG_CANTP_CHECKANDHANDLEWAITFRAMETIMEOUT_EXIT(ChannelPtr);
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
