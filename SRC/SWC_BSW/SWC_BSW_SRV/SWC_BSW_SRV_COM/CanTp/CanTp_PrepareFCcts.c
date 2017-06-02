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

FUNC(void, CANTP_CODE) CanTp_PrepareFCcts
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  /* pointer to CAN frame data to ease lookups */
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) FrameData;

  /* affected N-Sdu */
  const PduIdType NSduId = ChannelPtr->NSduId;
  uint8     DataIndex;         /* index to help prepare data */

  DBG_CANTP_PREPAREFCCTS_ENTRY(ChannelPtr);

  /* init */
  FrameData = ChannelPtr->CanIfData;

  /* set N_TA/N_AE value on extended/mixed addressing */
  if(CANTP_GET_ADDR_FORMAT(&CANTP_CFG_GET_RXNSDU_CONFIG(NSduId)) != CANTP_STANDARD)
  {
    FrameData[0] = CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).N_TA_AE;
    DataIndex = 1U;
  }
  else
  {
    DataIndex = 0U;
  }

  /* set N_PCI */
  FrameData[DataIndex] = CANTP_N_PCI_FC_CTS;
  DataIndex++;

  /* set BS */
  FrameData[DataIndex] = ChannelPtr->BlockSize;
  DataIndex++;

  /* set StMin */
  FrameData[DataIndex] = CANTP_GET_RX_PDU_ST_MIN(NSduId);
  DataIndex++;
  ChannelPtr->CanIfDLC = DataIndex;

  /* set DLC */
  if(CANTP_GET_PDU_PADDING(&CANTP_CFG_GET_RXNSDU_CONFIG(NSduId)) == CANTP_ON)
  {
    CANTP_PREPAREPADDING(ChannelPtr);
  }

  /* transmit frame */
  ChannelPtr->Ticks = CANTP_GET_RX_PDU_N_AR(&CANTP_CFG_GET_RXNSDU_CONFIG(NSduId));
  CanTp_TransmitFrame(ChannelPtr);

  DBG_CANTP_PREPAREFCCTS_EXIT(ChannelPtr);
}


FUNC(Std_ReturnType, CANTP_CODE) CanTp_CalculateBlockSize
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) BlockSizePtr
)
{
  const PduIdType NSduId = ChannelPtr->NSduId;            /* affected N-Sdu */
  const uint16 RemainingBytes = ChannelPtr->TotalLength - ChannelPtr->ProcessedLength;
  uint16 BlockSizeTmp;         /* Temporary block size value for calculation */
  Std_ReturnType Ret_BSCalc; /* Indication of the actual BS calculation */

  /* Pointer  to N-Sdu config */
  CONSTP2CONST(CanTp_RxNSduConfigType, AUTOMATIC, CANTP_APPL_CONST) RxNSduCfgPtr =
      &CANTP_CFG_GET_RXNSDU_CONFIG(ChannelPtr->NSduId);

  /* Data frame length for calculating block (depending on addressing format) */
  const uint8 NSduMaxSize = CANTP_NPDU_LENGTH_MAX
                            - CANTP_GET_FIRST_N_PCI_BYTE(RxNSduCfgPtr)
                            - CANTP_CF_NPCI_SIZE;

  DBG_CANTP_CALCULATEBLOCKSIZE_ENTRY(ChannelPtr, BlockSizePtr);

  if(ChannelPtr->ActualBufferSize >= RemainingBytes)
  {
    /* Use configured value if whole frame fits in buffer. */
    BlockSizeTmp = CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId);
    Ret_BSCalc = E_OK;
  }
  else
  {
    /* ------------- calculate BlockSize -------------- */
    /* BS = Number of frames that fit into UL buffer */
    BlockSizeTmp = (uint16) (ChannelPtr->ActualBufferSize / NSduMaxSize);

    if(BlockSizeTmp > 0U)
    {
      /* Calculation returns valid result. There is enough UL buffer available */
      Ret_BSCalc = E_OK;

      /* if calculated BS is larger than configured BS */
      if(
          (BlockSizeTmp > CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId))
          && (CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId) != 0U)
        )
      {
        /* Use configured BS if configured BS is smaller and not 0U (no config limit). */
        BlockSizeTmp = CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId);
      }

      /* BS must be an 8 bit value - if it's bigger than that, use the maximum */
      if(BlockSizeTmp > 0xFFU)
      {
        /* Limit the BS to the maximum */
        BlockSizeTmp = 0xFFU;
      }
    }
    else
    {
      /* Calculation result indicates that not enough UL buffer available */
      Ret_BSCalc = E_NOT_OK;
    }
  }

  (*BlockSizePtr) = (uint8) BlockSizeTmp;

  DBG_CANTP_CALCULATEBLOCKSIZE_EXIT(Ret_BSCalc, ChannelPtr, BlockSizePtr);
  return Ret_BSCalc;
}


FUNC(boolean, CANTP_CODE) CanTp_VerifyBlockSize
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
)
{
  boolean Ret_BS_Ok;
  const uint16 RemainingBytes = ChannelPtr->TotalLength - ChannelPtr->ProcessedLength;

  DBG_CANTP_VERIFYBLOCKSIZE_ENTRY(ChannelPtr);

  if(ChannelPtr->ActualBufferSize >= RemainingBytes)
  {
    /* There is enough UL buffer available for the whole message. Continue sending. */
    Ret_BS_Ok = TRUE;
  }
  else
  {
    Std_ReturnType BSCalc_Ok; /* Indication of the actual BS calculation */
    uint8 ActualBlockSize; /* Actual upper layer BS */

    BSCalc_Ok = CanTp_CalculateBlockSize(ChannelPtr, &ActualBlockSize);

    if(BSCalc_Ok == E_OK)
    {
      if(ActualBlockSize >= ChannelPtr->BlockSize)
      {
        /* The UL buffer is big enough for receiving the next block. Continue sending. */
        Ret_BS_Ok = TRUE;
      }
      /* CHECK: NOPARSE */
      /* This decision branch can not be reached. The valid return value
         ActualBlockSize == 0U only occurs if ChannelPtr->ActualBufferSize >= RemainingBytes
         which is already handled at the beginning of this function.
       */
      else if(ActualBlockSize == 0U)
      {
        /* There is enough UL buffer available for the whole message. Continue sending. */
        Ret_BS_Ok = TRUE;
      }
      /* CHECK: PARSE */
      else
      {
        /* The UL buffer is not big enough for receiving the next block. */
        Ret_BS_Ok = FALSE;
      }
    }
    else
    {
      /* Not enough UL buffer available. The required BS is not reached for this block. */
      Ret_BS_Ok = FALSE;
    }
  }

  DBG_CANTP_VERIFYBLOCKSIZE_EXIT(Ret_BS_Ok, ChannelPtr);
  return Ret_BS_Ok;
}

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
