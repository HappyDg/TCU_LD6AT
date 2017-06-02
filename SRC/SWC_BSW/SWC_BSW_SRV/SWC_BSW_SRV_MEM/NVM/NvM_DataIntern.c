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
 *  MISRA-1) Deviated Rule: 12.4 (required)
 *    "The right-hand operand of a logical '&&' or '||' operator shall
 *            not contain side effects."
 *
 *    Reason: The portion of code is necessary and has no side effects.
 *
 *  MISRA-2) Deviated Rule: 12.5 (required)
 *    "The operands of a logical '&&' or '||' shall be
 *           'primary-expressions'."
 *
 *    Reason: These operands are only primary-expressions.
 */

/*==================[inclusions]============================================*/

#include <NvM_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types             */
#include <TSMem.h>                /* EB specific memory functions */
/* !LINKSTO NVM554,1 */
#include <SchM_NvM.h>             /* module specific header for             */
                                  /* Schedule Manager services              */
/* !LINKSTO NVM554,1 */
#include <MemIf.h>                /* Contains extern definition of function */
                                  /* MemIf_Cancel().                        */

/* prevent redundant declarations of RTE types */
#define NVM_INTERNAL_USE

/* !LINKSTO NVM554,1 */
#include <NvM.h>                  /* Extern NVRAM Manager API definitions   */
#include <NvM_FunctionIntern.h>   /* NvM functions which are used           */
                                  /* only within the NvM module.            */
#include <NvM_UsrHdr.h>           /* indirect incl. of usr supplied header  */
#include <NvM_DataIntern.h>       /* NvM data which is used only            */
                                  /* within the NvM module.                 */
#include <NvM_StateMachine.h>     /* External defintions for unit           */
                                  /* StateMachine                           */
#include <NvM_Queue.h>            /* Extern definitions of unit queue.      */
#include <NvM_CalcCrc.h>          /* Extern definitions of unit CalcCrc.    */

/*==================[macros]================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief Function to be called when a fatal error is detected.
 **
 ** Currently this function does not handle errors, the function block
 ** is empty.
 **/
STATIC FUNC(void,NVM_CODE) NvM_FatalError(void);

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

#if (NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS > 0U)
#define NVM_START_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>

/** \brief Stores the status of the NvM blocks.
 **/
/* !LINKSTO NVM134,1, NVM138,1, NVM135,1 */
VAR( NvM_AdminBlockType,NVM_VAR_POWER_ON_INIT ) NvM_AdminBlockTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#define NVM_STOP_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>
#endif

/***************************  variables normal uint8 section ****************/
#define NVM_START_SEC_VAR_INIT_8
#include <MemMap.h>

VAR( uint8,NVM_VAR ) NvM_GlobalErrorStatus = 0;

VAR( uint8,NVM_VAR ) NvM_GlobalCallLevel = 0;

VAR( uint8,NVM_VAR ) NvM_GlobalGenericStatus = 0U;

#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
VAR( uint8,NVM_VAR ) NvM_WriteRetryCount = 0U;
#endif

#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
VAR( uint8,NVM_VAR ) NvM_ReadRetryCount = 0U;
#endif

#define NVM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>

/***************************  uninitialized variables uint8 section ****************/
#define NVM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

VAR( uint8,NVM_VAR_NOINIT ) NvM_CurrentServiceId;

#if (NVM_SYNC_MECHANISM == STD_ON)
VAR(uint8, NVM_VAR_NOINIT) NvM_MirrorRetryCount;
#endif

#define NVM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/***************************  uninitialized variables uint16 section ****************/
#define NVM_START_SEC_VAR_NO_INIT_16
#include <MemMap.h>

VAR( uint16, NVM_VAR_NOINIT ) NvM_RamBlockCrcCalcCount;

#define NVM_STOP_SEC_VAR_NO_INIT_16
#include <MemMap.h>

/***************************  uninitialized variables unspecified section ****************/
#define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

VAR( NvM_DynamicStatusType,NVM_VAR_NOINIT ) NvM_GlobalWorkingStatus;

#define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/**********************  variables user application data section ************/
#define NVM_START_SEC_VAR_APPL_DATA
#include <MemMap.h>

P2VAR(uint8, NVM_VAR_NOINIT, NVM_APPL_DATA) NvM_TempRamBlockAddress;

#if (NVM_INTERNAL_BUFFER_SIZE != 0U)
VAR(uint8, NVM_APPL_DATA) NvM_InternalBuffer[NVM_INTERNAL_BUFFER_SIZE];
#endif

#define NVM_STOP_SEC_VAR_APPL_DATA
#include <MemMap.h>

/***************************  variables normal uint16 section ***************/
#define NVM_START_SEC_VAR_INIT_16
#include <MemMap.h>

VAR( uint16,NVM_VAR ) NvM_GlobalBlockNumber = 0U;

#define NVM_STOP_SEC_VAR_INIT_16
#include <MemMap.h>

/***************************  variables normal unspecified section **********/
#define NVM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

P2CONST( NvM_BlockDescriptorType,NVM_VAR,NVM_CONST )
  NvM_CurrentBlockDescriptorPtr = NULL_PTR;

VAR( NvM_CurrentFunctionPtrType,NVM_VAR )NvM_CurrentFunctionPtr[6];

#define NVM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]==========================================*/

#define NVM_START_CONFIG_DATA_APPL_DATA
#include <MemMap.h>

VAR( uint16,NVM_APPL_DATA ) NvM_ConfigurationId[NVM_CONFIGURATIONID_SIZE];

#define NVM_STOP_CONFIG_DATA_APPL_DATA
#include <MemMap.h>

/*==================[external function definitions]==========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

FUNC(void,NVM_CODE) NvM_SetPermanentRamBlockInvalid(void)
{
  /* Check if the permanent RAM Block must be used by this service */

  DBG_NVM_SETPERMANENTRAMBLOCKINVALID_ENTRY();
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_UPRB_MASK))
  {
    /* data must be copied to permanent RAM block -->  */
    /* set permanent RAM block invalid                 */
    NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMValid = NVM_BLOCK_INVALID;
  }

  DBG_NVM_SETPERMANENTRAMBLOCKINVALID_EXIT();
}

FUNC(void,NVM_CODE) NvM_SetPermanentRamBlockValid(void)
{
  /* Check if the permanent RAM Block must be used by this service */

  DBG_NVM_SETPERMANENTRAMBLOCKVALID_ENTRY();
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_UPRB_MASK))
  {
    /* data must be copied to permanent RAM block -->  */
    /* set permanent RAM block valid                   */
    NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMValid = NVM_BLOCK_VALID;
  }

  DBG_NVM_SETPERMANENTRAMBLOCKVALID_EXIT();
}

FUNC(void,NVM_CODE) NvM_SetPermanentRamBlockUnchanged(void)
{
  /* Check if the permanent RAM Block must be used by this service */

  DBG_NVM_SETPERMANENTRAMBLOCKUNCHANGED_ENTRY();
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_UPRB_MASK))
  {
    /* Permanent RAM Block must be used.                          */
    /* Set block unchanged --> it's NOT written by NvM_WriteAll() */
    NVM_CLEAR_WORKING_STATUS(NVM_DYN_CHANGE_MASK);
  }

  DBG_NVM_SETPERMANENTRAMBLOCKUNCHANGED_EXIT();
}

FUNC(void,NVM_CODE) NvM_SetPermanentRamBlockChanged(void)
{
  /* Check if the permanent RAM Block must be used by this service */

  DBG_NVM_SETPERMANENTRAMBLOCKCHANGED_ENTRY();
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_UPRB_MASK))
  {
    /* set block changed --> it's written by NvM_WriteAll() */
    NVM_SET_WORKING_STATUS(NVM_DYN_CHANGE_MASK);
  }

  DBG_NVM_SETPERMANENTRAMBLOCKCHANGED_EXIT();
}/* end of function NvM_SetPermanentRamBlockChanged */

FUNC(NvM_PtrToApplDataType,NVM_CODE) NvM_GetUserRamBlockAddress(void)
{
  NvM_PtrToApplDataType UserRamBlockAddress = NULL_PTR;

  DBG_NVM_GETUSERRAMBLOCKADDRESS_ENTRY();

#if (NVM_SYNC_MECHANISM == STD_ON)
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK))
  {
    UserRamBlockAddress = NVM_GET_MIRROR_ADDR();
  }
  else
#endif
  {
    /* NOTE: if no permanent RAM buffer is defined and no temporary RAM      */
    /*       buffer is available then an fatal error occured                 */
    /*       Availability of temporary RAM block must be checked first       */
    /*       because if it is provided by the user it must be preferred to   */
    /*       the permanent RAM block.                                        */
    if ( NvM_TempRamBlockAddress != NULL_PTR )
    {
      UserRamBlockAddress = NvM_TempRamBlockAddress;
    }
    else if ( NvM_CurrentBlockDescriptorPtr->ramBlockDataAddress != NULL_PTR)
    {
      /* return address of permanent RAM block */
      UserRamBlockAddress =
        NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].ramBlockDataAddress;
    }
    else
    {
      /* no user data block available --> fatal error */
      /* This code must never be reached */
      /* NvM_ReadAll is performed only for blocks having permanent RAM block   */
      /* NvM_WriteAll is performed only for blocks having permanent RAM block  */
      /* Error recovery (write back to Nv memory) is perfomed only for blocks  */
      /* having permanent RAM block */
      /* NvM_WriteBlock, NvM_ReadBlock, and NvM_RestoreBlockDefaults APIs      */
      /* have DET check to detect error when there is no permanent or          */
      /* temporary RAM block available */
      /* NvM_SetRamBlockStatus() also checks for permanent RAM block */
      /* Therefore, this code shall not be reached unless user disables DET    */
      /* check and uses block without a permanent or temporary RAM block */

      NvM_FatalError();
    }
  }


  DBG_NVM_GETUSERRAMBLOCKADDRESS_EXIT(UserRamBlockAddress);
  return UserRamBlockAddress;
}



FUNC(uint16,NVM_CODE)NvM_GetMergedBlockNumber(void)
{
  uint16 ret = 0;
  DBG_NVM_GETMERGEDBLOCKNUMBER_ENTRY();
  ret = ( uint16 )( ( uint16 )
    ( ( NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockBaseNum ) <<
      NVM_DATASET_SELECTION_BITS ) |
    ( ( uint16 )NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex ) );
  DBG_NVM_GETMERGEDBLOCKNUMBER_EXIT(ret);
  return ret;
}

FUNC(void,NVM_CODE) NvM_ResetRedundantBlockDataIndex(void)
{

  DBG_NVM_RESETREDUNDANTBLOCKDATAINDEX_ENTRY();
  if ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
         NVM_BD_BLOCKMNGTTYPE_REDUNDANT
     )
  {
    /* start service with second block */
    NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex = 0U;
  }

  DBG_NVM_RESETREDUNDANTBLOCKDATAINDEX_EXIT();
}

FUNC(void,NVM_CODE) NvM_MultiRequestFinishedSingleBlock( NvM_CurrentFunctionPtrType NextState )
{
  /* write status of finished block operation to block administration
   * table.
   */

  DBG_NVM_MULTIREQUESTFINISHEDSINGLEBLOCK_ENTRY(NextState);
  NvM_PostService_Function();

#if ( NVM_NUMBER_OF_SINGLE_BLOCK_CALLBACK > 0U )
  /* !LINKSTO NVM176,1 */
  /* Invoke block specific callback function */
  NvM_InvokeSingleBlockCallback(NvM_GlobalBlockNumber,
                                NvM_CurrentServiceId,
                                NvM_GlobalErrorStatus);
#endif

  if ( ( NvM_GlobalErrorStatus != NVM_REQ_OK ) &&
       ( NvM_GlobalErrorStatus != NVM_REQ_BLOCK_SKIPPED )
     )
  {
    NVM_REQUEST_INTERIM_RESULT = NVM_REQ_NOT_OK;
  }

  /* set pointer to next state */
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = NextState;


  DBG_NVM_MULTIREQUESTFINISHEDSINGLEBLOCK_EXIT(NextState);
}/* end of function NvM_MultiRequestFinishedSingleBlock() */

FUNC(void,NVM_CODE) NvM_PreService_Function(void)
{

  DBG_NVM_PRESERVICE_FUNCTION_ENTRY();
  NvM_CurrentBlockDescriptorPtr = &( NvM_BlockDescriptorTable[NvM_GlobalBlockNumber] );


  DBG_NVM_GLOBALWORKINGSTATUS((NvM_GlobalWorkingStatus),(( uint16 )NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDynStatus));
  NvM_GlobalWorkingStatus = ( uint16 )NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDynStatus;
  /* clear dynamic status bits except 'WriteProtectionFlag',     */
  /* 'WriteProtectionPermanentFlag', 'Block Locked' flag and the changed flags          */
  NVM_CLEAR_WORKING_STATUS(
     (NvM_DynamicStatusType)(~(NvM_DynamicStatusType)( NVM_DYN_WPF_MASK    |
                                                       NVM_DYN_WPPF_MASK   |
                                                       NVM_DYN_CHANGE_MASK |
                                                       NVM_DYN_SRBSC_MASK  |
                                                       NVM_DYN_LOCK_MASK   |
                                                       NVM_DYN_MIRROR_MASK |
                                                       NVM_DYN_WBID_MASK |
                                                       NVM_DYN_REDUNDANCY_MASK
                                                     )
                             )
                     );
  if ( ( NvM_CurrentBlockDescriptorPtr->ramBlockDataAddress != NULL_PTR ) &&
       ( NvM_TempRamBlockAddress == NULL_PTR )
       /* Deviation MISRA-1 */
     )
  {
    /* This services must use the permanent RAM block -->
     * Set the NVM_DYN_UPRB_MASK flag in the dynamic status word.
     */
    NVM_SET_WORKING_STATUS( NVM_DYN_UPRB_MASK );
  }

  DBG_NVM_PRESERVICE_FUNCTION_EXIT();
}

FUNC(void,NVM_CODE) NvM_PostService_Function(void)
{
  /* Protect concurrent access to administrative data */

  DBG_NVM_POSTSERVICE_FUNCTION_ENTRY();
  SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

  /* the following data must always be set when processing of job is */
  /* interrupted.                                                    */
  /* NOTE: the high byte of 'NvM_GlobalWorkingStatus gets lost. The  */
  /*       high byte contains information which is only required     */
  /*       while processing the request and need not be stored       */
  /*       permanently in the 'NvM_AdminBlockTable'.                 */
  NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDynStatus
    = ( uint8 )NvM_GlobalWorkingStatus;

  if ( (NVM_CHECK_GLOBAL_GENERIC_STATUS( NVM_GENERIC_MRKJP_MASK )) &&
       (!NVM_CHECK_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CANCEL_MASK))
     )
  {
    /* Another request for this block was inserted in the queue.
     * Therefore the ErrorStatus must remain NVM_REQ_PENDING
     * after the block was processed by NvM_WriteAll() or NvM_ReadAll().
     */
    NVM_CLEAR_GLOBAL_GENERIC_STATUS( NVM_GENERIC_MRKJP_MASK );
    DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus & (uint8)((uint8)(~(NVM_GENERIC_MRKJP_MASK)) & 0xFFU)));
    NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult = NVM_REQ_PENDING;
  }
  else if (NVM_CHECK_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CANCEL_MASK))
  {
    /* A single block request for the same block is present
     * in the queue, but it must be cancelled. Therefore the ErrorStatus
     * must remain NVM_REQ_CANCELED after the block was processed by
     * NvM_WriteAll() or NvM_ReadAll().
     */
    NVM_CLEAR_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CANCEL_MASK);
    DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus & (uint8)((uint8)(~(NVM_GENERIC_CANCEL_MASK)) & 0xFFU)));
    NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult = NVM_REQ_CANCELED;
  }
  else
  {
    NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult = NvM_GlobalErrorStatus;
  }
  SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

  /* Reset the temporary RAM block address */
  NvM_TempRamBlockAddress = NULL_PTR;


  DBG_NVM_POSTSERVICE_FUNCTION_EXIT();
}/* end of function  NvM_PostService_Function */

FUNC(void,NVM_CODE) NvM_MultiPostService_Function(void)
{
  DBG_NVM_MULTIPOSTSERVICE_FUNCTION_ENTRY();

#if ( NVM_DRV_MODE_SWITCH == STD_ON )

  MemIf_SetMode( MEMIF_MODE_SLOW );

#endif

  /* Block number of multi block request is zero.      */
  NvM_GlobalBlockNumber = 0x0U;
  NvM_CurrentBlockDescriptorPtr = &(NvM_BlockDescriptorTable[0x0]);

  NvM_StateMachine_TerminateCurrentLevel();

  DBG_NVM_MULTIPOSTSERVICE_FUNCTION_EXIT();
}

#if ( NVM_NUMBER_OF_SINGLE_BLOCK_CALLBACK > 0U )
FUNC(void,NVM_CODE) NvM_InvokeSingleBlockCallback
(
  NvM_BlockIdType BlockId,
  uint8 ServiceId,
  uint8 ErrorStatus
)
{
  DBG_NVM_INVOKESINGLEBLOCKCALLBACK_ENTRY(BlockId, ServiceId, GlobalErrorStatus);

  if (NvM_BlockDescriptorTable[BlockId].singleBlockCallback != NULL_PTR)
  {
    /* Call block specific callback function, ignore return value
     * as we do not treat failures in this case
     */
    (void)NvM_BlockDescriptorTable[BlockId].singleBlockCallback(ServiceId, ErrorStatus);
  }

  DBG_NVM_INVOKESINGLEBLOCKCALLBACK_EXIT(BlockId, ServiceId, GlobalErrorStatus);
}
#endif /* NVM_NUMBER_OF_SINGLE_BLOCK_CALLBACK > 0U  */

FUNC(boolean, NVM_CODE) NvM_CheckWriteProtection(NvM_BlockIdType BlockId)
{
  boolean Result = FALSE;

  DBG_NVM_CHECKWRITEPROTECTION_ENTRY(BlockId);

  /* Check whether the write protection flag is set or the permanent write
   * protection flag is set  */
  if ((NVM_CHECK_DYN_STATUS(BlockId, NVM_DYN_WPF_MASK)) ||
      (NVM_CHECK_DYN_STATUS(BlockId, NVM_DYN_WPPF_MASK)))
  {
    /* block is write protected --> TRUE */
    Result = TRUE;
  }
/* !LINKSTO NVM150,1 */
#if (NVM_NUMBER_OF_DATASET_BLOCKS > 0U)
  /* Check whether a ROM Block of a Dataset Block is requested */
  else if (NvM_CheckDataSetRomBlock(BlockId) == TRUE)
  {
    /* block is write protected --> TRUE */
    Result = TRUE;
  }
  else
  {
    /* Nothing to do (MISRA) */
  }
#endif /* NVM_NUMBER_OF_DATASET_BLOCKS > 0U */

  DBG_NVM_CHECKWRITEPROTECTION_EXIT(Result,BlockId);
  return Result;
}

FUNC(boolean,NVM_CODE) NvM_CheckDataSetRomBlock( NvM_BlockIdType BlockId )
{
  boolean Result = FALSE;
/* !LINKSTO NVM150,1 */

  DBG_NVM_CHECKDATASETROMBLOCK_ENTRY(BlockId);
#if ( NVM_NUMBER_OF_DATASET_BLOCKS > 0U )
  if ( ( NVM_BD_BLOCKMNGTTYPE(NvM_BlockDescriptorTable[BlockId].blockDesc) ==
         NVM_BD_BLOCKMNGTTYPE_DATASET
       ) &&
       ( NvM_AdminBlockTable[BlockId].NvMDatasetBlockIndex
          >= NvM_BlockDescriptorTable[BlockId].nvBlockNum
       )
     )
  {
    /* The specified NVRAM Block is a Dataset Block and the Dataset Index
     * specifies a ROM Data Block.
     */
    Result = TRUE;
  }
#else
    TS_PARAM_UNUSED(BlockId);
#endif /* NVM_NUMBER_OF_DATASET_BLOCKS > 0U */

  DBG_NVM_CHECKDATASETROMBLOCK_EXIT(Result,BlockId);
  return Result;
}

FUNC(uint8, NVM_CODE) NvM_GetBlockCRCLength(void)
{
  uint8 NvMCrcLength;

  DBG_NVM_GETBLOCKCRCLENGTH_ENTRY();

  /* If current block use 32bit crc */
  if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC32)
  {
    NvMCrcLength = 4U;
  }
  /* If current block use 16bit crc */
  else if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC16)
  {
    NvMCrcLength = 2U;
  }
  /* If current block use 8bit crc */
  else if(NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) == NVM_BD_CRCTYPE_CRC8)
  {
    NvMCrcLength = 1U;
  }
  /* If current block dont use any crc */
  else
  {
    NvMCrcLength = 0U;
  }


  DBG_NVM_GETBLOCKCRCLENGTH_EXIT(NvMCrcLength);
  return NvMCrcLength;
}

FUNC(uint16, NVM_CODE) NvM_GetBlockLength(void)
{
  uint16 Length = NvM_CurrentBlockDescriptorPtr->nvBlockLength;

  DBG_NVM_GETBLOCKLENGTH_ENTRY();

#if (NVM_STATIC_BLOCKID_CHECK == STD_ON)
  /* If current block has static block id enabled */
  if (NVM_BD_USESTATICBLOCKID(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    Length += NVM_BLOCKID_LENGTH;
  }
#endif


  DBG_NVM_GETBLOCKLENGTH_EXIT(Length);
  return Length;
}

FUNC(NvM_PtrToApplDataType, NVM_CODE) NvM_GetBufferAddress(void)
{
  NvM_PtrToApplDataType DataBufPtr;

  DBG_NVM_GETBUFFERADDRESS_ENTRY();

#if ((NVM_INTERNAL_BUFFER_SIZE != 0U) || (NVM_SYNC_MECHANISM == STD_ON))
  /* If 'Use internal buffer' or 'Use Mirror' flags are set */
  if ((NVM_BD_USEINTERNALBUFFER(NvM_CurrentBlockDescriptorPtr->blockDesc))||
      (NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK)))
  {
    DataBufPtr = NVM_GET_INTERNAL_BUFFER();
  }
  else
#endif /* ((NVM_INTERNAL_BUFFER_SIZE != 0U) || (NVM_SYNC_MECHANISM == STD_ON)) */
  {
    DataBufPtr = NvM_GetUserRamBlockAddress();
  }


  DBG_NVM_GETBUFFERADDRESS_EXIT(DataBufPtr);
  return DataBufPtr;
}

FUNC(NvM_PtrToApplDataType, NVM_CODE) NvM_GetDataAddress(void)
{
  NvM_PtrToApplDataType DataBufPtr = NvM_GetBufferAddress();

  DBG_NVM_GETDATAADDRESS_ENTRY();

#if (NVM_STATIC_BLOCKID_CHECK == STD_ON)
#if ((NVM_SYNC_MECHANISM == STD_ON) || (NVM_INTERNAL_BUFFER_SIZE != 0U))
  if ((NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK)) ||
      (NVM_BD_USEINTERNALBUFFER(NvM_CurrentBlockDescriptorPtr->blockDesc)))
  {
    /* If Static Block Id is enabled, exclude Block Header. */
    if (NVM_BD_USESTATICBLOCKID(NvM_CurrentBlockDescriptorPtr->blockDesc))
    {
      DataBufPtr = &(DataBufPtr[NVM_BLOCKID_LENGTH]);
    }
  }
#endif
#endif

  DBG_NVM_GETDATAADDRESS_EXIT(DataBufPtr);
  return DataBufPtr;
}

#if (NVM_SYNC_MECHANISM == STD_ON)

FUNC(Std_ReturnType, NVM_CODE) NvM_MirrorCopy
(
  NvM_NvToRamCopyCallbackType ReadCallback,
  NvM_RamToNvCopyCallbackType WriteCallback,
  NvM_PtrToApplDataType DataBufPtr
)
{
  Std_ReturnType ReturnVal = E_NOT_OK;
  /* flag used to indicate if the mirror copy operation should be postponed */
  VAR(boolean, NVM_CODE) MirrorPostponeFlag = FALSE;

  DBG_NVM_MIRRORCOPY_ENTRY(ReadCallback,WriteCallback,DataBufPtr);

  /* This function will be called only when explicit synchronization is used.
   * According to requirement NvM.ExplicitSynch.CallbackFunctions, it shall always 
   * be assured in configuration phase that the callback functions are defined if 
   * explicit synchronization is used.
   *
   * NvM_MirrorCopy is an internal function that will be called only by the NvM module.
   * At each function call, one of the function pointers passed as arguments will be NOT NULL.
   * Call block specific callback function in order to let the application
   * copy data between the RAM block and NvM module's mirror.
   */
    if (ReadCallback != NULL_PTR)
    {
      if (NvM_CurrentServiceId == NVM_READ_ALL_API_ID)
      {
         /* !LINKSTO NvM.ExplicitSynch.ReadCallback.Multi,1 */
         /* In case of ReadAll request:
          * If permanent RAM is configured, copy the data from internal
          * buffer to permanent RAM.
          * According to NVM117_Conf a permanent RAM block shall always
          * be configured in order to process a block during NvM_ReadAll
          */
         TS_MemCpy(NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].ramBlockDataAddress, DataBufPtr,
            NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockLength);

        ReturnVal = E_OK;
      }
      else
      {
        /* !LINKSTO NvM.ExplicitSynch.ReadCallback.Single,1 */
        /* In case of ReadBlock request:
         * Let the user's callback function copy the data.
         */
        ReturnVal = ReadCallback(DataBufPtr);
      }
    }
    else
    {
      if (NvM_CurrentServiceId == NVM_WRITE_ALL_API_ID)
      {
        /* !LINKSTO NvM.ExplicitSynch.WriteCallback.Multi,1 */
        /* In case of WriteAll request:
         * If permanent RAM is configured, copy the data from permanent RAM to 
         * internal buffer.
         * According to NVM549_Conf a permanent RAM block shall always
         * be configured in order to process a block during NvM_WriteAll
         */
        TS_MemCpy(DataBufPtr, NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].ramBlockDataAddress,
            NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockLength);

        ReturnVal = E_OK;
      }
      else
      {
        /* !LINKSTO  NvM.ExplicitSynch.WriteCallback.Single,1 */
        /* In case of WriteBlock request:
         * Let the user's callback function copy the data.
         */
        ReturnVal = WriteCallback(DataBufPtr);
      }
    }

  if (E_OK != ReturnVal)
  {
    /* If the callback returns E_NOT_OK, the process has to be repeated
     * the configured number of times (by NvMRepeatMirrorOperations).
     */
    if (NVM_REPEAT_MIRROR_OPERATIONS > 0U)
    {
      NvM_MirrorRetryCount++;

      if (NvM_MirrorRetryCount == NVM_REPEAT_MIRROR_OPERATIONS)
      {
        /* number of mirror copy retries was reached, set the postpone flag */
        MirrorPostponeFlag = TRUE;
      }
      else
      {
        /* number of mirror copy retries was not reached, clear the postpone flag */
        MirrorPostponeFlag = FALSE;
      }
    }
    else
    {
      /* NVM_REPEAT_MIRROR_OPERATIONS is equal to 0, postpone the operation without any retries */
      MirrorPostponeFlag = TRUE;
    }

    /* After repeating the callback the configured number of times
     * the next job in the queue shall be processed.
     */
    if (MirrorPostponeFlag == TRUE)
    {
      NvM_MirrorRetryCount = 0U;

      /* The current job is exchanged with the next job in the queue */
      if (NvM_Queue_PullDownFirstItem() == E_OK)
      {
        /* After the current job is exchanged with the next job
         * set the new job to be processed.
         */
        NvM_StateMachine_SetNextRequest();
        NvM_PreService_Function();
      }
    }
  }
  else
  {
    /* If the callback returns E_OK, stop the counter and
     * reset the counter value.
     */
    NvM_MirrorRetryCount = 0U;
  } /* if (E_OK != ReturnVal) */


  DBG_NVM_MIRRORCOPY_EXIT(ReturnVal,ReadCallback,WriteCallback,DataBufPtr);
  return ReturnVal;
} /* NvM_PerformMirrorOperation */

#endif

FUNC(void, NVM_CODE) NvM_CheckBlockStatus(void)
{

  DBG_NVM_CHECKBLOCKSTATUS_ENTRY();

  if (NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult == NVM_REQ_PENDING)
  {
    /* Another request for this block was inserted in the queue.
     * Therefore the ErrorStatus must remain NVM_REQ_PENDING
     * after the block was written by NvM_ReadAll()/NvM_WriteAll().
     */
    NVM_SET_GLOBAL_GENERIC_STATUS(NVM_GENERIC_MRKJP_MASK);
    DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus | NVM_GENERIC_MRKJP_MASK));
  }

  if (NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult == NVM_REQ_CANCELED)
  {
    /* A single block request for the same block is present
     * in the queue, but it must be cancelled. Therefore the ErrorStatus
     * must remain NVM_REQ_CANCELED after the block was processed by
     * NvM_ReadAll()/NvM_WriteAll().
     */
    NVM_SET_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CANCEL_MASK);
    DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus | NVM_GENERIC_CANCEL_MASK));
  }

  DBG_NVM_CHECKBLOCKSTATUS_EXIT();
}

/*==================[internal function definitions]==========================*/

STATIC FUNC(void,NVM_CODE) NvM_FatalError(void)
{
  /* terminate complete request */

  DBG_NVM_FATALERROR_ENTRY();
  NvM_GlobalCallLevel = 0x0U;

  DBG_NVM_FATALERROR_EXIT();
}

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]============================================*/
