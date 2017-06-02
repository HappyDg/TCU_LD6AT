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
#include <CanTp_Internal.h>    /* internal macros and variables */
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

FUNC(void, CANTP_CODE) CanTp_PreparexF
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  uint8 DataIndex;   /* index in CAN frame */

  DBG_CANTP_PREPAREXF_ENTRY(ChannelPtr);

  /* init */
  DataIndex = 0U;

  /* set N_TA/N_AE value on extended/mixed frame */
  /* no N_TA/N_AE in standard addressing case */
  if(CANTP_GET_ADDR_FORMAT(&CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId)) != CANTP_STANDARD)
  {
    ChannelPtr->CanIfData[0U] = CANTP_CFG_GET_TXNSDU_CONFIG(ChannelPtr->NSduId).N_TA_AE;
    DataIndex = 1U;
  }

  /* write frame dependent header */
  switch (ChannelPtr->State)
  {
    case CANTP_CH_TX_BUFREQ_SF:
    {
      /* set N_PCI data: (CANTP_N_PCI_TYPE_SF is 0, lower 4 bits: length */
      ChannelPtr->CanIfData[DataIndex] = (uint8) (ChannelPtr->TotalLength & 0x000FU);
      DataIndex++;
      break;
    }
    case CANTP_CH_TX_BUFREQ_FF:
    {
      /* set N_PCI data: 4 bit frame type + 12 bit length */
      ChannelPtr->CanIfData[DataIndex] =
                              (uint8)(
                                       CANTP_N_PCI_TYPE_FF
                                       | (uint8)(ChannelPtr->TotalLength >> 8U)
                                     );
      DataIndex++;
      ChannelPtr->CanIfData[DataIndex] = (uint8)(ChannelPtr->TotalLength & 0x00FFU);
      DataIndex++;

      /* Set ProcessedBlockFrames and BlockSize to same value for FF. */
      ChannelPtr->ProcessedBlockFrames = 1U;
      ChannelPtr->BlockSize = 1U;
      break;
    }
    case CANTP_CH_TX_BUFREQ_CF:
    {
      /* set N_PCI data: 4 bit type + 4 bit sequence number */
      ChannelPtr->CanIfData[DataIndex] = ChannelPtr->SequenceNumber
                                         | CANTP_N_PCI_TYPE_CF;
      DataIndex++;

      /* handle sequence number and processed block count */
      ChannelPtr->SequenceNumber++;
      ChannelPtr->SequenceNumber &= CANTP_N_PCI_CF_SN_MASK;
      ChannelPtr->ProcessedBlockFrames++;
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

  /* Set DLC to the header size. */
  ChannelPtr->CanIfDLC = DataIndex;

  DBG_CANTP_PREPAREXF_EXIT(ChannelPtr);
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
