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
 *  MISRA-1) Deviated Rule: 11.4 (advisory)
 *    "A cast should not be performed between a pointer to object type and a
 *     different pointer to object type."
 *
 *    Reason: The portion of code is necessary and it has no alignment problems.
 *
 */
 /* !LINKSTO NVM076,1 */
/*==================[inclusions]============================================*/

#include <NvM_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types             */

/* prevent redundant declarations of RTE types */
#define NVM_INTERNAL_USE
#include <TSMem.h>                /* Autosar Module  Base */
/* !LINKSTO NVM554,1 */
#include <MemIf.h>                /* for MemIf_GetStatus() */
/* !LINKSTO NVM554,1 */
#include <SchM_NvM.h>             /* module specific header for             */
                                  /* Schedule Manager services              */
/* !LINKSTO NVM554,1 */
#include <NvM.h>                  /* Extern NVRAM Manager API definitions   */

#include <NvM_FunctionIntern.h>   /* NvM functions which are used           */
                                  /* only within the NvM module.            */
#include <NvM_DataIntern.h>       /* NvM data which is used only            */
                                  /* within the NvM module.                 */
#include <NvM_Queue.h>            /* queue external definitions.            */
#include <NvM_CalcCrc.h>
#include <NvM_StateMachine.h>     /* Contains extern definitions for unit   */
                                  /* 'StateMachine'. It can be included in  */
                                  /* library source code files.             */

#if ( NVM_INCLUDE_RTE == STD_ON )
#include <Rte_NvM.h>             /* Rte type definitions. */
#endif

/* if any DEM event is switched on, include Dem.h */
#if ((NVM_PROD_ERR_HANDLING_INTEGRITY_FAILED == TS_PROD_ERR_REP_TO_DEM) || \
     (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM) || \
     (NVM_PROD_ERR_HANDLING_REQ_FAILED == TS_PROD_ERR_REP_TO_DEM) || \
     (NVM_PROD_ERR_HANDLING_LOSS_OF_REDUNDANCY == TS_PROD_ERR_REP_TO_DEM ))
/* !LINKSTO NVM554,1 */
#include <Dem.h>
#endif

#if ( NVM_DEV_ERROR_DETECT == STD_ON )
/* !LINKSTO NVM556,1 */
#include <Det.h>               /* API of module Det. */
#endif

/* if single block job status reporting is switched on, include BswM_NvM.h */
#if (NVM_BSWM_BLOCK_STATUS_INFO == STD_ON)
#include <BswM_NvM.h>
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/
#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief calls function MemIf_Read
 **
 ** \param[in] DataBufferPtr: address of the data buffer the NVRAM data must
 **                           be copied to.
 **                           range: 0.. size of NVM_APPL_DATA
 ** \param[in] Length: length of the data to be read. range: 0..2^16-1
 **
 **/
STATIC FUNC(void,NVM_CODE) NvM_MemIfRead
(
  P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DataBufferPtr,
  uint16                                   Length
);


/** \brief Sets the Global error status and reports Dem error
 **        in case of Loss of Redundancy.
 **
 **/
STATIC FUNC(void,NVM_CODE) NvM_ReportLossOfRedundancy(void);

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

#define NVM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

STATIC VAR(uint8, NVM_VAR_NOINIT) NvM_StoredCrcBuf[NVM_STORED_CRC_SIZE];

#define NVM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/*==================[external function definitions]==========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType,NVM_CODE) NvM_ASR40_ReadBlock
(
  NvM_BlockIdType                       BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr
)
{
  Std_ReturnType Result = E_NOT_OK; /* Result of this function */
  DBG_NVM_ASR40_READBLOCK_ENTRY(BlockId, NvM_DstPtr);
/************** ( NVM_DEV_ERROR_DETECT == STD_ON ) *************/
#if ( NVM_DEV_ERROR_DETECT == STD_ON )

  /* Check if Block Id is within valid range */
  if ( ( BlockId < 1U ) || ( BlockId >= NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS ) )
  {
    NVM_DET_REPORT_ERROR( NVM_READ_BLOCK_API_ID, NVM_E_PARAM_BLOCK_ID );
  }
  /* Check if module is initialized by NvM_Init() */
  else if ( NVM_CHECK_GLOBAL_GENERIC_STATUS_FALSE( NVM_GENERIC_INIT_FLAG_MASK ) )
  {
    NVM_DET_REPORT_ERROR( NVM_READ_BLOCK_API_ID, NVM_E_NOT_INITIALIZED );
  }
  /* Check if an other request for block BlockId is already pending. */
  else if ( NvM_AdminBlockTable[BlockId].NvMResult == NVM_REQ_PENDING )
  {
    NVM_DET_REPORT_ERROR( NVM_READ_BLOCK_API_ID, NVM_E_BLOCK_PENDING );
  }
  /* Check if no permanent RAM block is defined and the NvM_DstPtr is equal
   * to NULL.
   */
  else if ( ( NvM_BlockDescriptorTable[BlockId].ramBlockDataAddress == NULL_PTR ) &&
            ( NvM_DstPtr == NULL_PTR )
          )
  {
    /* No Permanent RAM Data Block defined and also there is no
     * Temporary RAM Data Block.
     */
    NVM_DET_REPORT_ERROR( NVM_READ_BLOCK_API_ID,NVM_E_PARAM_ADDRESS );
  }
  else
#endif
/************** ( NVM_DEV_ERROR_DETECT == STD_ON ) *************/
  {
    /* protect concurrent access to the standard queue and
     * admin block
     */
    SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

    if (NvM_AdminBlockTable[BlockId].NvMResult != NVM_REQ_PENDING)
    {
      Result = NvM_Queue_InsertStandard( BlockId, NvM_DstPtr, &NvM_ReadBlock_Async);
    }

    if (E_OK == Result)
    {
      /* Insert the API ID into NvM_AdminBlockTable.
       * The information shall be available in case the request has only been queued,
       * but the processing has not been started and a cancel request was issued.
       */
      NvM_AdminBlockTable[BlockId].NvMCurrentServiceId = NVM_READ_BLOCK_API_ID;
    }

    SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
  if (E_OK != Result)
  {
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM)
#if (NVM_QUEUE_OVERFLOW_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
        NVM_DEM_REPORT_ERROR(NVM_QUEUE_OVERFLOW_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DET)
        NVM_DET_REPORT_ERROR(NVM_READ_BLOCK_API_ID, NVM_E_DEMTODET_QUEUE_OVERFLOW);
#endif
  }
#endif

#if (NVM_BSWM_BLOCK_STATUS_INFO == STD_ON)
    /* Check if block status changed and block status reporting to BswM is
     * enabled for this block */
    if ((E_OK == Result) &&
        (NVM_BD_BLOCKSTATUSINFO(NvM_BlockDescriptorTable[BlockId].blockDesc)))
    {
      /* Block status changed due to queuing read request, report the
       * block status to BswM */
      BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
    }
#endif

  }
 DBG_NVM_ASR40_READBLOCK_EXIT(Result, BlockId, NvM_DstPtr); 
 return Result;
}/* end of function NvM_ReadBlock */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async(void)
{
  DBG_NVM_READBLOCK_ASYNC_ENTRY();

  /* Since the processing of NvM_ReadBlock() has
   * been started, NvM_CurrentServiceId needs to be set
   */
  NvM_CurrentServiceId = NVM_READ_BLOCK_API_ID;

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_RAMBLOCK_CRC_BUFFER_SIZE > 0U))

   if ((NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMExtendedStatus &
   	  NVM_ES_RAM_BLOCK_CRC_CALC_MASK
   	 ) == NVM_ES_RAM_BLOCK_CRC_CALC_MASK
      )
  {
     /* Reset the RAM block CRC calculation flag */
    NVM_CLEAR_EXT_STATUS(NVM_ES_RAM_BLOCK_CRC_CALC_MASK);

    /* Ram block CRC will be recalculated again */
    NvM_RamBlockCrcCalcCount--;
  }
#endif

  /* if a permanent RAM block is used then it must be set invalid
   * and unchanged.
   */
  NvM_SetPermanentRamBlockInvalid();
  NvM_SetPermanentRamBlockUnchanged();

  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State0;
  DBG_NVM_READBLOCK_ASYNC_EXIT();
}/* end of function NvM_ReadBlock_Async */

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_State0(void)
{
  DBG_NVM_READBLOCK_ASYNC_STATE0_ENTRY();

#if (NVM_SYNC_MECHANISM == STD_ON)
  NvM_MirrorRetryCount = 0U;

  if (NVM_BD_USEMIRROR(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    NVM_SET_WORKING_STATUS(NVM_DYN_MIRROR_MASK);
  }
#endif

/* !LINKSTO NVM150,1 */
#if ( NVM_NUMBER_OF_DATASET_BLOCKS > 0U )
  if ( ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
         NVM_BD_BLOCKMNGTTYPE_DATASET) &&
       ( NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex
           >= NvM_CurrentBlockDescriptorPtr->nvBlockNum
       )
     )
  {
    /* A dataset block is requested whereas the NvBlock is located in ROM.
     * This is a job for NvM_RestoreBlockDefaults.
     */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State0;
  }
  else
#endif /* NVM_NUMBER_OF_DATASET_BLOCKS > 0U */

  {
    if ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
         NVM_BD_BLOCKMNGTTYPE_REDUNDANT )
    {
      /* if a redundant block is requested then set the dataset index
       * to zero.
       */
      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex = 0U;
      /* every time a redundant NvM block is being read the bit 
       * indicating redundancy failure is cleared 
       */
      NVM_CLEAR_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK);
    }
    /* Set CRC calculation or block copy state */
    NvM_ReadBlock_Async_State2();

    DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
    NvM_GlobalCallLevel++;
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State10;

#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
    /* Reset Read Retry Count to perform block read retry */
    NvM_ReadRetryCount = 1U;
#endif
  }

  DBG_NVM_READBLOCK_ASYNC_STATE0_EXIT();
}/* end of function NvM_ReadBlock_Async_State0 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_State2(void)
{
  /* !LINKSTO NVM127,1 */

  DBG_NVM_READBLOCK_ASYNC_STATE2_ENTRY();
  if (NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) != NVM_BD_CRCTYPE_NONE)
  {
    /* CRC must be calculated */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State4;
  }
  else
  {
    /* CRC must not be calculated */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State6;
  }


  DBG_NVM_READBLOCK_ASYNC_STATE2_EXIT();
}/* end of function NvM_ReadBlock_Async_State2 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_State4(void)
{

  DBG_NVM_READBLOCK_ASYNC_STATE4_ENTRY();
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State5;

  /* calculate CRC */
  NvM_CalculateCrc(NvM_GetDataAddress());

  DBG_NVM_READBLOCK_ASYNC_STATE4_EXIT();
}/* end of function NvM_ReadBlock_Async_State4 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_State5(void)
{
  /* Do CRC check */

  DBG_NVM_READBLOCK_ASYNC_STATE5_ENTRY();
  NvM_GlobalErrorStatus = NvM_CheckCrc(NvM_CalcCrc_GetBlockCrcAddress());

  if (NvM_GlobalErrorStatus == NVM_REQ_OK)
  {
    /* CRC check successfull
     * Set the state machine pointer of this level to State6
     * to copy the read data to user ram block
     */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State6;

    /* Compare CRC of both blocks additionally for Redundant blocks */
    if ( ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
           NVM_BD_BLOCKMNGTTYPE_REDUNDANT
         ) &&
         (!NVM_CHECK_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK))
       )
    {
      /* checks if the current CRC calculation finished is of first redundant block */
      if ( NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex == 0U )
      {
        /* Copies the CRC value of the first redundant block */
        NvM_CopyCrc(NvM_StoredCrcBuf);
      }
      else
      {
        /* compares the CRC values of the second redundant block with the stored first block CRC */
        if (NvM_CheckCrc(NvM_StoredCrcBuf) != NVM_REQ_OK)
        {
          /* Report Production error */
          NvM_ReportLossOfRedundancy();
        }
#if (( NVM_PROD_ERR_HANDLING_LOSS_OF_REDUNDANCY == TS_PROD_ERR_REP_TO_DEM ) && \
     ( NVM_REDUNDANCY_LOSS_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID ) \
    )
        else
        {
          /* Report Dem error as passed */
          NVM_DEM_REPORT_ERROR(NVM_REDUNDANCY_LOSS_DEM_EVENT_ID, DEM_EVENT_STATUS_PASSED);
        }
#endif
      }
    }
  }/* if ( NvM_GlobalErrorStatus == NVM_REQ_OK ) */
  else
  {
    /* Set Crc Check Unequal flag to indicate a Crc mismatch. */
    NVM_SET_WORKING_STATUS(NVM_DYN_CCU_MASK);
    /* Set CRC calculation or block copy state */
    NvM_ReadBlock_Async_State2();
    /* The error handling runs on the next level above */

    DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
    NvM_GlobalCallLevel++;
    /* Do read retry */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_Retry;
  }/* NvM_GlobalErrorStatus == NVM_REQ_OK */

  DBG_NVM_READBLOCK_ASYNC_STATE5_EXIT();
}/* end of function NvM_ReadBlock_Async_State5 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_State6(void)
{
  NvM_PtrToApplDataType DataBufPtr = NvM_GetBufferAddress();
#if (NVM_SYNC_MECHANISM == STD_ON)
  Std_ReturnType ReturnVal = E_OK;

  DBG_NVM_READBLOCK_ASYNC_STATE6_ENTRY();
#endif

  /* If Static Block Id is enabled, check the read
   * Block Id against the Current Block Id.
   */
#if (NVM_STATIC_BLOCKID_CHECK == STD_ON)
  if (NVM_BD_USESTATICBLOCKID(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    /* Deviation MISRA-1 */
    if (TS_MemCmp(DataBufPtr, NVM_STATIC_BLOCKID(), NVM_BLOCKID_LENGTH) != E_OK)
    {
      /* Set Wrong Block Id Flag to indicate Static Block Id check has failed */
      NVM_SET_WORKING_STATUS(NVM_DYN_WBID_MASK);
      /* The error handling runs on the next level above */

      DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
      NvM_GlobalCallLevel++;
      /* Read retry */
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_Retry;
    }
    /* Data after the Block Header shall be copied */
    DataBufPtr = &(DataBufPtr[NVM_BLOCKID_LENGTH]);
  }
  #endif
  if (!NVM_CHECK_WORKING_STATUS(NVM_DYN_WBID_MASK))
  {
#if (NVM_SYNC_MECHANISM == STD_ON)
    /* For single block read job, call the callback function to
     * copy data from NvM module's mirror to RAM block
     */
    if (NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK))
    {
      ReturnVal = NvM_MirrorCopy(NvM_CurrentBlockDescriptorPtr->readRamFromNvCallback, NULL_PTR, DataBufPtr);
    }
    else
#endif
    {
#if (NVM_INTERNAL_BUFFER_SIZE != 0U)
      /* If internal buffer is used,
       * Copy data from internal buffer to user RAM block.
       */
      if (NVM_BD_USEINTERNALBUFFER(NvM_CurrentBlockDescriptorPtr->blockDesc))
      {
        if (NVM_BD_USERPROVIDESSPACEFORCRC(NvM_CurrentBlockDescriptorPtr->blockDesc))
        {
          /* Copy both data and CRC to the RAM buffer */
          TS_MemCpy(NvM_GetUserRamBlockAddress(), DataBufPtr,
            (uint16)(NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockLength + NvM_GetBlockCRCLength()));
        }
        else
        {
          /* Copy only the data to the RAM buffer */ 
          TS_MemCpy(NvM_GetUserRamBlockAddress(), DataBufPtr,
            NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockLength);
        }
      }
#endif
    }

#if (NVM_SYNC_MECHANISM == STD_ON)
    if (E_OK == ReturnVal)
#endif
    {
      /* Check if the permanent RAM Block must be used by read request */
      if (NVM_CHECK_WORKING_STATUS(NVM_DYN_UPRB_MASK))
      {
        /* After the data was successfully copied from NVM to RAM set permanent
         * RAM Block valid and unchanged. NVM200, ( Autosar Bugzilla #20953 ),
         * NVM251.
         * NOTE: The RAM Block was already set to unchanged at the start of
         *       NvM_ReadBlock().
         */
        NvM_SetPermanentRamBlockValid();

        /* Hook function for ReadBlock */
        NVM_READ_BLOCK_HOOK(NvM_GlobalBlockNumber,
          NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].ramBlockDataAddress,
          NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockLength
        );
      }
      /* Check if the finished Read operation is of a redundant block and also whether
       * the last read block is redundant block 0
       */
      if ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
             NVM_BD_BLOCKMNGTTYPE_REDUNDANT
         )
      {
        if ( NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex == 0U )
        {
          /*  Block 0 is read; initiate read of block 1. This is needed to check
           *  Redundancy even though data has been retrieved from block 0.
           */
          NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex = 1U;
          /* Set return state */
          NvM_ReadBlock_Async_State2();
          /* Read operation runs on one level above */

          DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
          NvM_GlobalCallLevel++;
          NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State10;
        }
        /* Check whether the first block of redundant block is corrupted */
        else
        {
          if ( NVM_CHECK_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK) )
          {
            /* Report Production error */
            NvM_ReportLossOfRedundancy();
          }
          else
          {
            /* NvM_ReadBlock is finished */
            NvM_StateMachine_TerminateCurrentLevel();
          }
        }
      }
      else
      {
        /* NvM_ReadBlock is finished */
        NvM_StateMachine_TerminateCurrentLevel();
      }
    }
  }

  DBG_NVM_READBLOCK_ASYNC_STATE6_EXIT();
}/* end of function NvM_ReadBlockAsync_State6 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_State10(void)
{
  CONST( MemIf_StatusType, AUTOMATIC ) Status
    = MemIf_GetStatus( NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc) );

  DBG_NVM_READBLOCK_ASYNC_STATE10_ENTRY();

  if ( ( MEMIF_BUSY != Status ) && ( MEMIF_BUSY_INTERNAL != Status ) )
  {
    uint16 Length = NvM_GetBlockLength() + (uint16)NvM_GetBlockCRCLength();

    /* Reset Block Read Valid Error flag, Crc Check Unequal flag,
     * Block Read Block Inconsistent flag and Wrong Block Id Flag.
     * These flags are also set to zero in the NvM_PreService_Function(),
     * which runs previously, but if the block 1 a Redundant Block is
     * read they must be reset again.
     */
    NVM_CLEAR_WORKING_STATUS( NVM_DYN_BRVE_MASK | NVM_DYN_CCU_MASK |
      NVM_DYN_BRBI_MASK | NVM_DYN_WBID_MASK );

    NvM_MemIfRead(NvM_GetBufferAddress(), Length);
  }
  else
  {
    /* If the MemIf returns busy, return from MainFunction */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }

  DBG_NVM_READBLOCK_ASYNC_STATE10_EXIT();
}/* end of function NvM_ReadBlock_Async_State10 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_State12(void)
{
  const MemIf_JobResultType Result
    = MemIf_GetJobResult( NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc) );

  DBG_NVM_READBLOCK_ASYNC_STATE12_ENTRY();


#if (NVM_WRITE_BLOCK_ONCE == STD_ON)
  if (NVM_BD_WRITEONCE(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    /* set WriteProtectionFlag and WriteProtectionPermanentFlag */
    NVM_SET_WORKING_STATUS( NVM_DYN_WPF_MASK | NVM_DYN_WPPF_MASK );
  }
#endif

  switch( Result )
  {
    case MEMIF_JOB_PENDING:

      DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
      NvM_GlobalErrorStatus = NVM_REQ_PENDING;
      break;

    case MEMIF_JOB_CANCELED:

      DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_CANCELLED));
      NvM_GlobalErrorStatus = NVM_REQ_CANCELLED;
      /* set CallLevel to zero to terminate this service completely */

      DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),(0U));
      NvM_GlobalCallLevel = 0U;
      break;

    case MEMIF_JOB_OK:

      DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_OK));
      NvM_GlobalErrorStatus = NVM_REQ_OK;
      NvM_StateMachine_TerminateCurrentLevel();
      break;

    case MEMIF_BLOCK_INCONSISTENT:
      /* Memif delivered MEMIF_BLOCK_INCONSISTENT --> Set the
       * corresponding bit in the dynamic status word.
       * Read Retry shall be performed (if configured).
       * NOTE: the bit NVM_DYN_BRBI must be reset before a Redundant
       *       Block would be read.
       */
      NVM_SET_WORKING_STATUS( NVM_DYN_BRBI_MASK );
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_Retry;
      break;
      
    case MEMIF_BLOCK_INVALID:
      /* Memif delivered MEMIF_BLOCK_INVALID --> Set the
      * corresponding bit in the dynamic status word.
      * Read Retry shall be performed (if configured).
      * NOTE: the bit NVM_DYN_BRVE must be reset before a Redundant
      *       Block would be read.
      */
      NVM_SET_WORKING_STATUS( NVM_DYN_BRVE_MASK );
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_Retry;
      break;

    default:
      /* In case MemIf delivered an other error e.g. MEMIF_JOB_FAILED,
       * Read Retry shall be performed (if configured).
       */
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_Retry;
      break;
  }/* end of switch( Result ) */

  DBG_NVM_READBLOCK_ASYNC_STATE12_EXIT();
}/* end of function NvM_ReadBlock_Async_State12 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_Retry(void)
{
  DBG_NVM_READBLOCK_ASYNC_RETRY_ENTRY();
#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
  /* check the block for read retry  */
  if ( NvM_ReadRetryCount < NvM_CurrentBlockDescriptorPtr->readRetryLimit )
  {
    /* try to read the same block again */
    NvM_ReadRetryCount++;
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State10;
  }
  else
#endif
  
  {
#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
    /* Reset Read Retry Count for redundant block (if configured) */
    NvM_ReadRetryCount = 1U;
#endif

    /* Report the error or process the redundant block (if exists). */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_StateError1;
  }/* if ( NvM_ReadRetryCount < NvM_CurrentBlockDescriptorPtr->readRetryLimit ) */

  DBG_NVM_READBLOCK_ASYNC_RETRY_EXIT();
}/* end of function NvM_ReadBlock_Async_Retry */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_StateError1(void)
{
  /* check if the error state entered as a result of redundant block */

  DBG_NVM_READBLOCK_ASYNC_STATEERROR1_ENTRY();
  if ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
       NVM_BD_BLOCKMNGTTYPE_REDUNDANT
     )
  {
    /* initiate read of second redundant block */
    if (NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex == 0U)
    {
      /* Set Loss of Redundancy flag */
      NVM_SET_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK);

      /* Read block 1 */
      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex = 1U;
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State10;
    }
    else
    {
      /* Check if first block has been failed */
      if (NVM_CHECK_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK))
      {
        /* Both blocks failed */
        /* Clear the flag so that read failure is handled the normal way */
        NVM_CLEAR_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK);
        /* Handle read failure */
        NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_StateError2;
      }
      else
      {
        /* Set Loss of Redundancy flag */
        NVM_SET_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK);
        /* Set the Redundnat Error flag to indicate that redundant block has been failed */
        NVM_SET_EXT_STATUS(NVM_ES_REDUNDANT_ERROR_MASK);
        /* Only block 1 failed; Handle Loss of redundancy */
        NvM_ReportLossOfRedundancy();
        /* Read operation must be terminated completely */
        NvM_StateMachine_TerminateCurrentLevel();
      }
    }
  }
  else
  {
    /* proceed with error handling */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_StateError2;
  }


  DBG_NVM_READBLOCK_ASYNC_STATEERROR1_EXIT();
}/* end of function NvM_ReadBlock_Async_StateError1 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_StateError2(void)
{

  DBG_NVM_READBLOCK_ASYNC_STATEERROR2_ENTRY();
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_StateError3;
  /* reset Rom Data Loaded Flag */
  NVM_CLEAR_WORKING_STATUS( NVM_DYN_RDL_MASK );

  DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_NOT_OK));
  NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;
  if ( NvM_GlobalBlockNumber > 1U )
  {
    /* For block 1 the Compiled Configuration Id which is set as default
     * data must not be read automatically by NvM_ReadBlock()
     */

    DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
    NvM_GlobalCallLevel++;
#if (NVM_ADVANCED_RECOVERY == STD_ON)
    if (NVM_BD_ADVANCED_RECOVERY(NvM_CurrentBlockDescriptorPtr->blockDesc))
    {
      /* mark block for re-writting */
      NVM_SET_EXT_STATUS(NVM_ES_ADVANCED_RECOVERY_MASK);
    }
#endif
    NvM_RestoreBlockDefaults_Async_State0();
  }


  DBG_NVM_READBLOCK_ASYNC_STATEERROR2_EXIT();
}/* end of NvM_ReadBlock_Async_StateError2 */

FUNC(void,NVM_CODE) NvM_ReadBlock_Async_StateError3(void)
{

  /* Check if CRC is configured and CRC does not match
   * or block was reported as inconsistent
   */

 DBG_NVM_READBLOCK_ASYNC_STATEERROR3_ENTRY();
  if ( ( ( NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) != NVM_BD_CRCTYPE_NONE ) &&
         ( NVM_CHECK_WORKING_STATUS( NVM_DYN_CCU_MASK ) )
       ) ||
      ( NVM_CHECK_WORKING_STATUS( NVM_DYN_BRBI_MASK ) )
     )
  {
    /* Either CRC calculation configured and CRC check negative
     * or the Block Read Block Inconsistent flag is set (MemIf
     * job result was MEMIF_BLOCK_INCONSISTENT). Therefore job result
     * must be set to NVM_REQ_INTEGRITY_FAILED. (NVM358, NVM204, NVM360, NVM295).
     */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_INTEGRITY_FAILED));
    NvM_GlobalErrorStatus = NVM_REQ_INTEGRITY_FAILED;

    /* The error must be reported to DEM (NVM360, NVM358, NVM203) */
#if ( NVM_PROD_ERR_HANDLING_INTEGRITY_FAILED == TS_PROD_ERR_REP_TO_DEM )
#if (NVM_INTEGRITY_FAILED_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
    NVM_DEM_REPORT_ERROR(NVM_INTEGRITY_FAILED_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif ( NVM_PROD_ERR_HANDLING_INTEGRITY_FAILED == TS_PROD_ERR_REP_TO_DET )
    NVM_DET_REPORT_ERROR( NvM_CurrentServiceId, NVM_E_DEMTODET_INTEGRITY_FAILED );
#endif
  }/* if ( NVM_CHECK_CONST_BLOCK_STATUS( NVM_CALCRAMBLOCKCRC_MASK ) ) */
  else if ( NVM_CHECK_WORKING_STATUS( NVM_DYN_BRVE_MASK ) )
  {
    /* The Block Read Valid Error flag is set. This means the NVM Block is
     * invalidated. Therefore NVM_REQ_NV_INVALIDATED must set as
     * job result. NVM341, NVM342, NVM299.
    */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_NV_INVALIDATED));
    NvM_GlobalErrorStatus = NVM_REQ_NV_INVALIDATED;
  }
  else if (NVM_CHECK_WORKING_STATUS(NVM_DYN_WBID_MASK))
  {
    /* The Static Block Id check has failed */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_NOT_OK));
    NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;

    /* The error must be reported to DEM */
#if (NVM_PROD_ERR_HANDLING_WRONG_BLOCK_ID == TS_PROD_ERR_REP_TO_DEM)
#if (NVM_WRONG_BLOCK_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
    NVM_DEM_REPORT_ERROR(NVM_WRONG_BLOCK_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif (NVM_PROD_ERR_HANDLING_WRONG_BLOCK_ID == TS_PROD_ERR_REP_TO_DET)
    NVM_DET_REPORT_ERROR(NvM_CurrentServiceId, NVM_E_DEMTODET_REQ_FAILED);
#endif
  }
  else
  {
    /* In all other cases, e.g. the MemIf job result was MEMIF_JOB_FAILED,
     * the request result is set to NVM_REQ_NOT_OK. NVM359, NVM361.
     * The job result of NvM_RestoreBlockDefaults() is completely
     * ignored.
     */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_NOT_OK));
    NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;

    /* The error must be reported to DEM */
#if (NVM_PROD_ERR_HANDLING_REQ_FAILED == TS_PROD_ERR_REP_TO_DEM)
#if (NVM_REQ_FAILED_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
    NVM_DEM_REPORT_ERROR(NVM_REQ_FAILED_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif (NVM_PROD_ERR_HANDLING_REQ_FAILED == TS_PROD_ERR_REP_TO_DET)
    NVM_DET_REPORT_ERROR(NvM_CurrentServiceId, NVM_E_DEMTODET_REQ_FAILED);
#endif
  }/* else */

   /* If ROM Block default data is loaded then the job result is also
    *  set to NVM_REQ_RESTORED_FROM_ROM.
    */
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_RDL_MASK))
  {

  DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_RESTORED_FROM_ROM));
  NvM_GlobalErrorStatus = NVM_REQ_RESTORED_FROM_ROM;
  }
  else
  {
  }
  /* Terminate complete NvM_ReadBlock() function -->  */
  /* no more error handling possible                  */
  NvM_StateMachine_TerminateSubLevel();


  DBG_NVM_READBLOCK_ASYNC_STATEERROR3_EXIT();
}/* end of NvM_ReadBlock_Async_StateError3 */

/*==================[internal function definitions]==========================*/

STATIC FUNC(void,NVM_CODE) NvM_MemIfRead
(
  P2VAR( uint8, AUTOMATIC, NVM_APPL_DATA ) DataBufferPtr,
  uint16 Length
)
{
  /* evaluate Result of MemIf_Read() */

  DBG_NVM_MEMIFREAD_ENTRY(DataBufferPtr,Length);
  if ( MemIf_Read(
        NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc),
        NvM_GetMergedBlockNumber(), 0U, DataBufferPtr, Length ) == E_OK )
  {
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State12;
  }
  else
  {
    /* Perform the Read Retry (if exists). */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_Retry;
  }

  DBG_NVM_MEMIFREAD_EXIT(DataBufferPtr,Length);
}

STATIC FUNC(void,NVM_CODE) NvM_ReportLossOfRedundancy(void)
{

  DBG_NVM_REPORTLOSSOFREDUNDANCY_ENTRY();
  NvM_GlobalErrorStatus = NVM_REQ_REDUNDANCY_FAILED;

  /* Report Dem error as failed (NVM360, NVM358, NVM203) since
   * one block is damaged.
   */
#if ( NVM_PROD_ERR_HANDLING_LOSS_OF_REDUNDANCY == TS_PROD_ERR_REP_TO_DEM )
#if (NVM_REDUNDANCY_LOSS_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
  NVM_DEM_REPORT_ERROR(NVM_REDUNDANCY_LOSS_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif ( NVM_PROD_ERR_HANDLING_LOSS_OF_REDUNDANCY == TS_PROD_ERR_REP_TO_DET )
  NVM_DET_REPORT_ERROR( NvM_CurrentServiceId, NVM_E_DEMTODET_LOSS_OF_REDUNDANCY );
#endif

  /* Read operation must be terminated here. */
  NvM_StateMachine_TerminateCurrentLevel();

  DBG_NVM_REPORTLOSSOFREDUNDANCY_EXIT();
}

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]============================================*/
