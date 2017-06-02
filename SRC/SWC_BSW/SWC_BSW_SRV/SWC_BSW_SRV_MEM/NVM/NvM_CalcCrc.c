/**
 * \file
 *
 * \brief AUTOSAR NvM
 *
 * This file contains the implementation of the AUTOSAR
 * module NvM.
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
 *    "The operands of a logical '&&' or '||' shall be
 *           'primary-expressions'"
 *
 *    Reason: The operands are only primary-expressions.
 *
 *  MISRA-2) Deviated Rule: 11.4 (advisory)
 *    "A cast should not be performed between a pointer to object type and a
 *     different pointer to object type."
 *
 *    Reason: The portion of code is necessary and it has no alignment problems.
 */
/* !LINKSTO NVM076,1 */
/*==================[inclusions]=============================================*/

/* prevent redundant declarations of RTE types */
#define NVM_INTERNAL_USE
/* !LINKSTO NVM554,1 */
#include <NvM_Trace.h>
#include <NvM.h>                  /* Extern NVRAM Manager API definitions   */
#include <NvM_FunctionIntern.h>   /* Contains external function definitions */
                                  /* which are used only inside NvM.        */
#include <NvM_DataIntern.h>       /* NvM data which is used only            */
                                  /* within the NvM module.                 */
#include <NvM_CalcCrc.h>          /* Extern definitions of unit CalcCrc.    */
#include <NvM_StateMachine.h>     /* Contains extern definitions for unit   */
                                  /* 'StateMachine'. It can be included in  */
                                  /* library source code files.             */
/* !LINKSTO NVM555,1 */
#include <Crc.h>

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief Function to calculate CRC with interruption.
 **        If CRC shall be calculated with interruption, this function is
 **        called cyclically by NvM_MainFunction() until calculation is
 **        completed.
 **
 ** \pre   NvM_CalculateCrc must be executed prior to this call.
 **/
STATIC FUNC(void, NVM_CODE) NvM_CalcCrc_AsyncState(void);

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]=====================================*/
/*==================[internal constants]=====================================*/
/*==================[external data]==========================================*/
/*==================[internal data]==========================================*/

#if (NVM_RAMBLOCK_CRC_BUFFER_SIZE > 0U)
#define NVM_START_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>

/**  \brief The RAM buffer for storing the calculated CRC values
 **         for all blocks which are configured to have CRC calculated
 **         for their permanent RAM blocks (with parameter NvMCalcRamBlockCrc).
 **/
STATIC VAR(uint8, NVM_VAR_POWER_ON_INIT) NvM_RamBlockCrcValues[NVM_RAMBLOCK_CRC_BUFFER_SIZE];

#define NVM_STOP_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>
#endif

#define NVM_START_SEC_VAR_INIT_32
#include <MemMap.h>

/**  \brief The remaining number of bytes for CRC calculation.
 **         If CRC calculation must be interrupted it is used to store the
 **         length of the data block which must still be CRC calculated.
 **/
STATIC VAR(uint32, NVM_VAR) NvM_CalcCrc_RemainingLength = 0U;

#define NVM_STOP_SEC_VAR_INIT_32
#include <MemMap.h>

#define NVM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Intermediate address for CRC calculation.
 **        If CRC calculation must be interrupted this is used to store data
 **        address at which CRC calculation must continue after interruption.
 **/
STATIC NvM_PtrToApplDataType NvM_CalcCrc_Address;

#define NVM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]==========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

FUNC(uint32, NVM_CODE) NvM_CalcCrc_UpdateLength(void)
{
  uint32 NvMCurrentCrcLength = 0U;

  DBG_NVM_CALCCRC_UPDATELENGTH_ENTRY();

  if (NvM_CalcCrc_RemainingLength > NVM_CRC_NUM_OF_BYTES)
  {
    NvM_CalcCrc_RemainingLength -= NVM_CRC_NUM_OF_BYTES;
    NvMCurrentCrcLength = NVM_CRC_NUM_OF_BYTES;
    /* MainFunction must terminate after first call */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }
  else
  {
    NvMCurrentCrcLength = NvM_CalcCrc_RemainingLength;
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_StateMachine_TerminateCurrentLevel;

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_OK));
    NvM_GlobalErrorStatus = NVM_REQ_OK;
  }

  /* Update calculation address for this cycle */
  NvM_CalcCrc_Address = &(NvM_CalcCrc_Address[NVM_CRC_NUM_OF_BYTES]);


  DBG_NVM_CALCCRC_UPDATELENGTH_EXIT(NvMCurrentCrcLength);
  return NvMCurrentCrcLength;
}

FUNC(NvM_PtrToApplDataType, NVM_CODE) NvM_CalcCrc_GetBlockCrcAddress(void)
{
  NvM_PtrToApplDataType ret = NULL_PTR;
  DBG_NVM_CALCCRC_GETBLOCKCRCADDRESS_ENTRY();
  ret = &(NvM_GetDataAddress()[NvM_CurrentBlockDescriptorPtr->nvBlockLength]);
  DBG_NVM_CALCCRC_GETBLOCKCRCADDRESS_EXIT(ret);
  return ret;
}

FUNC(NvM_PtrToApplDataType, NVM_CODE) NvM_GetStoredRamCRCAddress(void)
{
  NvM_PtrToApplDataType ret = NULL_PTR;
  DBG_NVM_GETSTOREDRAMCRCADDRESS_ENTRY();
#if (NVM_RAMBLOCK_CRC_BUFFER_SIZE > 0U)
  /* return address of stored crc value */
  ret = (NvM_PtrToApplDataType)
   (&(NvM_RamBlockCrcValues[NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].ramBlockCrcIndex]));
#else
  ret = NULL_PTR;
#endif
  DBG_NVM_GETSTOREDRAMCRCADDRESS_EXIT(ret);
  return ret;
}

FUNC(void, NVM_CODE) NvM_CalculateCrc(NvM_PtrToApplDataType DataAddress)
{
  uint32 Length = NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockLength;

  DBG_NVM_CALCULATECRC_ENTRY(DataAddress);

  /* Check if Crc should be calculated in parts */
  if (Length > NVM_CRC_NUM_OF_BYTES)
  {
    /* Save the remaining length to continue Crc calculation */
    NvM_CalcCrc_RemainingLength = Length - NVM_CRC_NUM_OF_BYTES;
    /* Use only the configured size for this calculation */
    Length = NVM_CRC_NUM_OF_BYTES;

    /* Save the start address of data block */
    NvM_CalcCrc_Address = DataAddress;

    /* Set state function to continue Crc calculation */

    DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
    NvM_GlobalCallLevel++;
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_CalcCrc_AsyncState;
    /* MainFunction must terminate after first call */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }

#if (NVM_NUMBER_OF_CALC_CRC32_BLOCKS > 0U)
  /* If current block use 32 bit crc */
  if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC32)
  {
    /* Start CRC32 calculation with the given address, length and start value 0.
     * Crc_IsFirstCall should be set to TRUE since this is the first call.
     */
    NvM_CalcCrc_CalcBuffer = Crc_CalculateCRC32(DataAddress, Length, 0U, TRUE);
  }
#endif
#if (NVM_NUMBER_OF_CALC_CRC16_BLOCKS > 0U)
  /* If current block use 16 bit crc */
  if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC16)
  {
    P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) CrcBufPtr16 =
      /* Deviation MISRA-2 */
      (P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA))&NvM_CalcCrc_CalcBuffer;

    /* Start CRC16 calculation with the given address, length and start value 0.
     * Crc_IsFirstCall should be set to TRUE since this is the first call.
     */
    *CrcBufPtr16 = Crc_CalculateCRC16(DataAddress, Length, 0U, TRUE);
  }
#endif
#if (NVM_NUMBER_OF_CALC_CRC8_BLOCKS > 0U)
  /* If current block use 8 bit crc */
  if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC8)
  {
    P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) CrcBufPtr8 =
      /* Deviation MISRA-2 */
      (P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA))&NvM_CalcCrc_CalcBuffer;

    /* Start CRC8 calculation with the given address, length and start value 0.
     * Crc_IsFirstCall should be set to TRUE since this is the first call.
     */
    *CrcBufPtr8 = Crc_CalculateCRC8(DataAddress, Length, 0U, TRUE);
  }
#endif

  DBG_NVM_CALCULATECRC_EXIT(DataAddress);
}

FUNC(void, NVM_CODE) NvM_CopyCrc
(
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataAddress
)
{
  /* Deviation MISRA-2 */
  NvM_PtrToApplDataType CrcBufPtr8 = (NvM_PtrToApplDataType)(&NvM_CalcCrc_CalcBuffer);

  DBG_NVM_COPYCRC_ENTRY(DataAddress);

  /* Perform byte copy of the CRC data from CRC buffer to the target address */
  DataAddress[0U] = CrcBufPtr8[0U];

#if ((NVM_NUMBER_OF_CALC_CRC16_BLOCKS > 0U) || (NVM_NUMBER_OF_CALC_CRC32_BLOCKS > 0U))
/* If current block use 16/32 bit crc */
  if ((NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC16) ||
      (NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC32)
     )
  {
    DataAddress[1U] = CrcBufPtr8[1U];
  }
#endif

#if (NVM_NUMBER_OF_CALC_CRC32_BLOCKS > 0U)
  /* If current block use 32 bit crc */
  if (NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC32)
  {
    DataAddress[2U] = CrcBufPtr8[2U];
    DataAddress[3U] = CrcBufPtr8[3U];
  }
#endif

  DBG_NVM_COPYCRC_EXIT(DataAddress);
}

FUNC(NvM_RequestResultType, NVM_CODE) NvM_CheckCrc
(
  P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) DataAddress
)
{
  /* Deviation MISRA-2 */
  NvM_PtrToApplDataType CrcBufPtr8 = (NvM_PtrToApplDataType)(&NvM_CalcCrc_CalcBuffer);

  NvM_RequestResultType Result = NVM_REQ_OK;

  DBG_NVM_CHECKCRC_ENTRY(DataAddress);

  if ((CrcBufPtr8[0] != DataAddress[0]))
  {
    Result = NVM_REQ_NOT_OK;
  }
#if ((NVM_NUMBER_OF_CALC_CRC16_BLOCKS > 0U) || (NVM_NUMBER_OF_CALC_CRC32_BLOCKS > 0U))
  /* If current block use 16/32 bit crc */
  else if (((NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC16) ||
            (NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC32)
            ) &&
           (CrcBufPtr8[1] != DataAddress[1])
          )
  {
    Result = NVM_REQ_NOT_OK;
  }
#endif
  else
  {
#if (NVM_NUMBER_OF_CALC_CRC32_BLOCKS > 0U)
    /* If current block use 32 bit crc */
    if ((NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC32) &&
        ((CrcBufPtr8[2] != DataAddress[2]) || (CrcBufPtr8[3] != DataAddress[3]))
      )
    {
      Result = NVM_REQ_NOT_OK;
    }
#endif
  }


  DBG_NVM_CHECKCRC_EXIT(Result,DataAddress);
  return Result;
}

/*==================[internal function definitions]==========================*/

STATIC FUNC(void, NVM_CODE) NvM_CalcCrc_AsyncState(void)
{
  /* Update the remaining length */
  uint32 Length = NvM_CalcCrc_UpdateLength();

  DBG_NVM_CALCCRC_ASYNCSTATE_ENTRY();

#if (NVM_NUMBER_OF_CALC_CRC32_BLOCKS > 0U)

  /* If current block use 32 bit crc */
  if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC32)
  {
    /* Calculate CRC32 and store the result in the CRC buffer as a 32-bit value.
     * Crc_IsFirstCall should be set to FALSE since this is a subsequent call
     * in a call sequence.
     */
    NvM_CalcCrc_CalcBuffer =
      Crc_CalculateCRC32(NvM_CalcCrc_Address, Length, NvM_CalcCrc_CalcBuffer, FALSE);
  }
#endif
#if (NVM_NUMBER_OF_CALC_CRC16_BLOCKS > 0U)

  /* If current block use 16 bit crc */
  if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC16)
  {
    P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) CrcBufPtr16 =
      /* Deviation MISRA-2 */
      (P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA))&NvM_CalcCrc_CalcBuffer;

    /* Calculate CRC16 and store the result in the CRC buffer as a 16-bit value.
     * As this is a subsequent call in a call sequence, set Crc_IsFirstCall to FALSE
     */
    *CrcBufPtr16 = Crc_CalculateCRC16(NvM_CalcCrc_Address, Length, *CrcBufPtr16, FALSE);
  }
#endif
#if (NVM_NUMBER_OF_CALC_CRC8_BLOCKS > 0U)

  /* If current block use 8 bit crc */
  if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC8)
  {
    P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) CrcBufPtr8 =
      /* Deviation MISRA-2 */
      (P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA))&NvM_CalcCrc_CalcBuffer;

    /* Calculate CRC8 and store the result in the CRC buffer as a 8-bit value.
     * As this is a subsequent call in a call sequence, set Crc_IsFirstCall to FALSE
     */
    *CrcBufPtr8 = Crc_CalculateCRC8(NvM_CalcCrc_Address, Length, *CrcBufPtr8, FALSE);
  }
#endif

  DBG_NVM_CALCCRC_ASYNCSTATE_EXIT();
}

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]============================================*/
