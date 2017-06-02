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
 *  MISRA-2) Deviated Rule: 11.4 (advisory)
 *    "A cast should not be performed between a pointer to object type and a
 *     different pointer to object type."
 *
 *    Reason: The portion of code is necessary and it has no alignment problems.
 *  
 *  MISRA-3) Deviated Rule: 11.5 (required)
 *    "A cast shall not be performed that removes any 'const' or 'volatile'
 *     qualification from the type addressed by a pointer."
 *
 *    Reason: For memory optimization the portion of code is necessary and it has
 *            no side effects.
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
#include <SchM_NvM.h>             /* module specific header for             */
                                  /* Schedule Manager services              */
/* !LINKSTO NVM554,1 */
#include <MemIf.h>                /* for MemIf_GetStatus()                  */

/* !LINKSTO NVM554,1 */
#include <NvM.h>                  /* Extern NVRAM Manager API               */
                                  /* definitions                            */
#include <NvM_FunctionIntern.h>   /* NvM functions which are used           */
                                  /* only within the NvM module.            */
#include <NvM_DataIntern.h>       /* NvM data which is used only            */
                                  /* within the NvM module.                 */
#include <NvM_Queue.h>            /* Extern definitions of the unit         */
                                  /* 'Queue'.                               */
#include <NvM_CalcCrc.h>
#include <NvM_StateMachine.h>     /* Contains extern definitions for unit   */
                                  /* 'StateMachine'. It can be included in  */
                                  /* library source code files.             */

#if ( NVM_INCLUDE_RTE == STD_ON )
#include <Rte_NvM.h>           /* Rte type definitions. */
#endif

/* if any DEM event is switched on, include Dem.h */
#if ((NVM_PROD_ERR_HANDLING_REQ_FAILED == TS_PROD_ERR_REP_TO_DEM) || \
    (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM) || \
    (NVM_PROD_ERR_HANDLING_VERIFY_FAILED == TS_PROD_ERR_REP_TO_DEM) || \
    (NVM_PROD_ERR_HANDLING_WRITE_PROTECTED == TS_PROD_ERR_REP_TO_DEM))
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

/** \brief Prepares the state machine function pointers for processing
 **        redandant blocks. Used by NvM_WriteBlock().
 **/
STATIC FUNC(void,NVM_CODE) NvM_WriteBlock_ProcessRedundantBlock
(
  NvM_CurrentFunctionPtrType NextState
);

/** \brief Performs error handling by reporting the error to Dem.
 **        It is used by NvM_WriteBlock().
 **/
STATIC FUNC(void,NVM_CODE) NvM_WriteBlock_RedundantBlockError(void);

#if (NVM_WRITE_VERIFICATION == STD_ON)

/** \brief Reads data for write verification.
 **        This function checks the status of MemIf and
 **        calls MemIf_Read to read the next data to verify.
 **
 **/
STATIC FUNC(void, NVM_CODE) NvM_MemIfReadToVerify(void);

/** \brief Returns the length of the data to be write verified.
 **
 ** \revtal length of data of current block. range 0..2^16-1
 **
 **/
STATIC FUNC(uint16,NVM_CODE) NvM_GetVerifyDataSize(void);

#endif

/** \brief Copies the data and Block Id (if required) to the Internal Buffer.
 **        If Internal Buffer is enabled, this function copies
 **        block data from the user Ram block to the Internal Buffer.
 **        If Static Block Id is enabled, the Block Id also is copied.
 **
 **/
STATIC FUNC(void, NVM_CODE) NvM_FillInternalBuffer(void);

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/
#if (NVM_WRITE_VERIFICATION == STD_ON)
#define NVM_START_SEC_VAR_INIT_8
#include <MemMap.h>
/**  \brief Internal buffer used for write verification.
 **/
STATIC VAR( uint8, NVM_VAR ) WriteVerificationBuffer[NVM_WRITE_VERIFICATION_BUFFER_SIZE];

#define NVM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>

#define NVM_START_SEC_VAR_INIT_16
#include <MemMap.h>
/**  \brief The number of bytes for write verification.
 **/
STATIC VAR( uint16, NVM_VAR ) NvM_VerifyOffset = 0U;
#define NVM_STOP_SEC_VAR_INIT_16
#include <MemMap.h>
#endif /* (NVM_WRITE_VERIFICATION == STD_ON) */

/*==================[external function definitions]==========================*/
#define NVM_START_SEC_CODE
#include <MemMap.h>

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType, NVM_CODE) NvM_ASR40_WriteBlock
(
  NvM_BlockIdType                         BlockId,
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  Std_ReturnType Result = E_NOT_OK; /* Result of this function */
#if (NVM_PROD_ERR_HANDLING_WRITE_PROTECTED != TS_PROD_ERR_DISABLE)
  boolean ReportWriteProtected = FALSE; /* To check write protected DEM/DET error reporting */
#endif
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
  boolean ReportQueueOverflow = FALSE; /* To check whether Det/Dem error shall be reported */
#endif
  DBG_NVM_ASR40_WRITEBLOCK_ENTRY(BlockId, NvM_SrcPtr);

/************** ( NVM_DEV_ERROR_DETECT == STD_ON ) *************/
#if ( NVM_DEV_ERROR_DETECT == STD_ON )

  /* Check if Block Id is within valid range */
  if ( ( BlockId < 1U ) || ( BlockId >= NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS ) )
  {
    NVM_DET_REPORT_ERROR( NVM_WRITE_BLOCK_API_ID, NVM_E_PARAM_BLOCK_ID );
  }
  /* Check if module is initialized by NvM_Init() */
  else if ( NVM_CHECK_GLOBAL_GENERIC_STATUS_FALSE( NVM_GENERIC_INIT_FLAG_MASK ) )
  {
    NVM_DET_REPORT_ERROR( NVM_WRITE_BLOCK_API_ID, NVM_E_NOT_INITIALIZED );
  }
  /* Check if an other request for block BlockId is already pending. */
  else if ( NvM_AdminBlockTable[BlockId].NvMResult == NVM_REQ_PENDING )
  {
    NVM_DET_REPORT_ERROR( NVM_WRITE_BLOCK_API_ID, NVM_E_BLOCK_PENDING );
  }
  /* Check if block is locked. */
  else if (NVM_CHECK_DYN_STATUS(BlockId, NVM_DYN_LOCK_MASK))
  {
    NVM_DET_REPORT_ERROR(NVM_WRITE_BLOCK_API_ID, NVM_E_BLOCK_LOCKED);
  }
  /* Check if no permanent RAM block is defined and the NvM_SrcPtr is equal
   * to NULL.
   */
  else if ( ( NvM_BlockDescriptorTable[BlockId].ramBlockDataAddress == NULL_PTR ) &&
            ( NvM_SrcPtr == NULL_PTR )
          )
  {
    /* No Permanent RAM Data Block defined and also there is no
     * Temporary RAM Data Block.
     */
    NVM_DET_REPORT_ERROR( NVM_WRITE_BLOCK_API_ID, NVM_E_PARAM_ADDRESS );
  }
  else
#endif /* NVM_DEV_ERROR_DETECT == STD_ON */
  {
    /* protect concurrent access to the standard, immediate queues and
     * concurrent access to write protection flag and data set index
     */
    SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

    /* Check also dynamic write protection flag which can be set by
     * NvM_SetBlockProtection(). If block is write protected report production error.
     * This check must be done always and independently of the Det checks.
     * Also the check if a Dataset ROM Block is specified must be done
     * always.
     */
    if (NvM_CheckWriteProtection(BlockId) == TRUE)
    {
#if (NVM_PROD_ERR_HANDLING_WRITE_PROTECTED != TS_PROD_ERR_DISABLE)
     /* Write protected DEM/DET error needs to be reported */
      ReportWriteProtected = TRUE;
#endif
    }
    else if ((NvM_CheckDataSetRomBlock(BlockId) == FALSE) &&
             /* Locked NV blocks shall not be written */
             (!NVM_CHECK_DYN_STATUS(BlockId, NVM_DYN_LOCK_MASK))
            )
    {
      /* The Request is accepted */
      if (NvM_AdminBlockTable[BlockId].NvMResult != NVM_REQ_PENDING)
      {
#if ( ( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) )
        /* Compiler warning explanation: Because of memory optimization,
           the same pointer type uint8* is used for storing NvM_SrcPtr (of type const void *)
           and NvM_DstPtr (of type void *).
           As a consequence, a casting of NvM_SrcPtr is needed. */
        /* Deviation MISRA-3 */
        Result = NvM_Queue_InsertImmediate(BlockId, (P2VAR(uint8, AUTOMATIC,
                             NVM_APPL_DATA))NvM_SrcPtr, &NvM_WriteBlock_Async);
#else
        /* Compiler warning explanation: Because of memory optimization,
           the same pointer type uint8* is used for storing NvM_SrcPtr (of type const void *)
           and NvM_DstPtr (of type void *).
           As a consequence, a casting of NvM_SrcPtr is needed. */
        /* Deviation MISRA-3 */
        Result = NvM_Queue_InsertStandard(BlockId, (P2VAR(uint8, AUTOMATIC,
                             NVM_APPL_DATA))NvM_SrcPtr, &NvM_WriteBlock_Async);
#endif

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
        if (E_OK != Result)
        {
          ReportQueueOverflow = TRUE;
        }
#endif
      }
    }
    else
    {
    }
    SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

    if (E_OK == Result)
    {
      /* Insert the API ID into NvM_AdminBlockTable.
       * The information shall be available in case the request has only been queued,
       * but the processing has not been started and a cancel request was issued.
       */
      NvM_AdminBlockTable[BlockId].NvMCurrentServiceId = NVM_WRITE_BLOCK_API_ID;
    }

#if (NVM_PROD_ERR_HANDLING_WRITE_PROTECTED != TS_PROD_ERR_DISABLE)
    if (ReportWriteProtected == TRUE)
    {
#if (NVM_PROD_ERR_HANDLING_WRITE_PROTECTED == TS_PROD_ERR_REP_TO_DEM)
#if (NVM_WRITE_PROT_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
      NVM_DEM_REPORT_ERROR(NVM_WRITE_PROT_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif (NVM_PROD_ERR_HANDLING_WRITE_PROTECTED == TS_PROD_ERR_REP_TO_DET)
      NVM_DET_REPORT_ERROR(NVM_WRITE_BLOCK_API_ID, NVM_E_DEMTODET_WRITE_PROTECTED);
#endif
    }
#endif

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
    if (ReportQueueOverflow == TRUE)
    {
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM)
#if (NVM_QUEUE_OVERFLOW_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
       NVM_DEM_REPORT_ERROR(NVM_QUEUE_OVERFLOW_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DET)
          NVM_DET_REPORT_ERROR(NVM_WRITE_BLOCK_API_ID, NVM_E_DEMTODET_QUEUE_OVERFLOW);
#endif
    }
#endif


#if (NVM_BSWM_BLOCK_STATUS_INFO == STD_ON)
    /* Check if block status changed and block status reporting to BswM is
     * enabled for this block */
    if ((E_OK == Result) &&
        (NVM_BD_BLOCKSTATUSINFO(NvM_BlockDescriptorTable[BlockId].blockDesc)))
    {
      /* Block status changed due to queuing write request, report the
       * block status to BswM */
      BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
    }
#endif
  }

  DBG_NVM_ASR40_WRITEBLOCK_EXIT(Result, BlockId, NvM_SrcPtr);
  return Result;

}/* end of function NvM_WriteBlock */

FUNC(void,NVM_CODE) NvM_WriteBlock_Async(void)
{
  DBG_NVM_WRITEBLOCK_ASYNC_ENTRY();

  /* Since the processing of NvM_WriteBlock() has
   * been started, NvM_CurrentServiceId needs to be set
   */
  NvM_CurrentServiceId = NVM_WRITE_BLOCK_API_ID;

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

  /* Proceed with state 1 */
  NvM_WriteBlock_Async_State1();
  DBG_NVM_WRITEBLOCK_ASYNC_EXIT();
}/* end of function NvM_WriteBlock_Async */

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

FUNC(void,NVM_CODE) NvM_WriteBlock_Async_CopyCrc(void)
{
  /* Copy the calculated CRC copied to the currently used write buffer
   * (internal buffer or user RAM block) so that user data and CRC can be written
   * in a single call of the underlying MemIf module.
   */

  DBG_NVM_WRITEBLOCK_ASYNC_COPYCRC_ENTRY();
  NvM_CopyCrc( NvM_CalcCrc_GetBlockCrcAddress() );

  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_State3;


  DBG_NVM_WRITEBLOCK_ASYNC_COPYCRC_EXIT();
}/* end of function NvM_WriteBlock_Async_CalcCrc_1 */

FUNC(void,NVM_CODE) NvM_WriteBlock_Async_Error(void)
{
  DBG_NVM_WRITEBLOCK_ASYNC_ERROR_ENTRY();
#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
  if ( NvM_WriteRetryCount < NvM_CurrentBlockDescriptorPtr->writeRetryLimit )
  {
    /* try to write same block again */
    NvM_WriteRetryCount++;
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_State3;
  }
  else
#endif
  {
    /* if a redundant block is configured then try to write the second
     * block else terminate service.
     * The entrance point of the next state is stored on the state stack
     * in both cases.
     */
#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
    NvM_WriteRetryCount = 1U;
#endif

    NvM_WriteBlock_RedundantBlockError();

  }/* if ( NvM_WriteRetryCount < NvM_CurrentBlockDescriptorPtr->writeRetryLimit ) */


  DBG_NVM_WRITEBLOCK_ASYNC_ERROR_EXIT();
}/* end of function NvM_WriteBlock_Async_Error */

FUNC(void,NVM_CODE) NvM_WriteBlock_Async_State1(void)
{
  /* Check if the permanent RAM Block must be used by write request */

  DBG_NVM_WRITEBLOCK_ASYNC_STATE1_ENTRY();
  
#if (NVM_SYNC_MECHANISM == STD_ON)
  NvM_MirrorRetryCount = 0U;

  if (NVM_BD_USEMIRROR(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    NVM_SET_WORKING_STATUS(NVM_DYN_MIRROR_MASK);
  }
#endif

  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_UPRB_MASK))
  {
    /* Hook function for WriteBlock */
    NVM_WRITE_BLOCK_HOOK(NvM_GlobalBlockNumber,
      NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].ramBlockDataAddress,
      NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockLength
    );

    /* Set permanent RAM Block valid if it is currently used */
    NvM_SetPermanentRamBlockValid();
  }

#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
  /* Reset Write Retry Counter */
  NvM_WriteRetryCount = 1U;
#endif

  /* Prepare state machine for next state */
  NvM_WriteBlock_ProcessRedundantBlock( &NvM_WriteBlock_Async_State3 );

  /* Set the state function for explicit synchronization */
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_State2;

  /* Check if write request is for block 1.
   * Restore configured Compiled Configuration Id to RAM block.
   */
  if (NvM_GlobalBlockNumber == NVM_BLOCK_CONFIG_ID)
  {

    DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
    NvM_GlobalCallLevel++;
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State0;
  }

  DBG_NVM_WRITEBLOCK_ASYNC_STATE1_EXIT();
}/* end of function NvM_WriteBlock_Async_State1 */

FUNC(void,NVM_CODE) NvM_WriteBlock_Async_State2(void)
{
  NvM_PtrToApplDataType BufferAddr = NvM_GetDataAddress();

#if (NVM_SYNC_MECHANISM == STD_ON)
  Std_ReturnType ReturnVal = E_OK;
#endif

  DBG_NVM_WRITEBLOCK_ASYNC_STATE2_ENTRY();

#if (NVM_SYNC_MECHANISM == STD_ON)
  /* For single block write job, call the callback function to
   * copy data from the RAM block to NvM module's mirror
   */
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK))
  {
    ReturnVal = NvM_MirrorCopy(NULL_PTR, NvM_CurrentBlockDescriptorPtr->writeRamToNvCallback, BufferAddr);
  }

  if (E_OK == ReturnVal)
#endif
  {
    /* If internal buffer is used, Copy data from user RAM block
     * and Block Id (if required) to internal buffer.
     */
    if ((NVM_BD_USEINTERNALBUFFER(NvM_CurrentBlockDescriptorPtr->blockDesc)) ||
        (NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK))
       )
    {
      NvM_FillInternalBuffer();
    }

    /* Calculate CRC if it is configured for this NVRAM Block */
    /* !LINKSTO NVM127,1 */
    if (NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) != NVM_BD_CRCTYPE_NONE)
    {

      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_CopyCrc;
      NvM_CalculateCrc(BufferAddr);
    }
    else
    {
      /* Continue with write operation */
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_State3;
    }
  }

  DBG_NVM_WRITEBLOCK_ASYNC_STATE2_EXIT();
}

FUNC(void,NVM_CODE) NvM_WriteBlock_Async_State3(void)
{
  boolean ExecuteWriteBlockAsyncState3 = FALSE;  /* Flag used to check if write job
                                                    can be started. */

  CONST( MemIf_StatusType, AUTOMATIC ) Status
   = MemIf_GetStatus( NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc) );

  DBG_NVM_WRITEBLOCK_ASYNC_STATE3_ENTRY();

  /* For blocks with standard or immediate priority,
   * job cannot be started if MemIf is busy.
   */
  if ((MEMIF_BUSY != Status) && (MEMIF_BUSY_INTERNAL != Status))
  {
    ExecuteWriteBlockAsyncState3 = TRUE;
  }
#if ( ( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ) )

  /* For blocks with immediate priority, job can be started even if
   * MemIf is internally busy. But for blocks with standard priority,
   * job cannot be started if MemIf is internally busy.
   */
  else if ((NVM_BLOCK_IMMEDIATE_PRIORITY == NvM_CurrentBlockDescriptorPtr->blockJobPriority) &&
           (MEMIF_BUSY_INTERNAL == Status))
  {
    ExecuteWriteBlockAsyncState3 = TRUE;
  }
  else
  {
  }
#endif

  /* Check if write-block condition satisfied */
  if (ExecuteWriteBlockAsyncState3 == TRUE)
  {
    /* call MemIf_Write() and evaluate result. */
    if ( MemIf_Write(
          NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc),
          NvM_GetMergedBlockNumber(),
          NvM_GetBufferAddress()) == E_OK
       )
    {
#if (NVM_WRITE_VERIFICATION == STD_ON)
#if (NVM_STATIC_BLOCKID_CHECK == STD_ON)
      if (NVM_BD_USESTATICBLOCKID(NvM_CurrentBlockDescriptorPtr->blockDesc))
      {
        /* Reset Write verification data offset to start of data */
        NvM_VerifyOffset = NVM_BLOCKID_LENGTH;
      }
      else
#endif
      {
        /* Reset Write verification data offset */
        NvM_VerifyOffset = 0U;
      }
#endif

      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_ProcessJobResult_Async_State;
    }
    else
    {
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_Error;
    }
  }
  else
  {
    /* If the MemIf returns busy, return from MainFunction */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }

  DBG_NVM_WRITEBLOCK_ASYNC_STATE3_EXIT();
}/* end of function NvM_WriteBlock_Async_State2 */

FUNC(void,NVM_CODE) NvM_WriteBlock_ProcessJobResult_Async_State(void)
{
  const MemIf_JobResultType Result =
    MemIf_GetJobResult(NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc));

  DBG_NVM_WRITEBLOCK_PROCESSJOBRESULT_ASYNC_STATE_ENTRY();

  /* evaluate Result */
  if (Result == MEMIF_JOB_OK)
  {
#if (NVM_WRITE_VERIFICATION == STD_ON)
    /* Check write verification required */
    if (NVM_BD_WRITE_VERIFICATION(NvM_CurrentBlockDescriptorPtr->blockDesc))
    {
      /* Write Verification */
      NvM_MemIfReadToVerify();
    }
    else
#endif
    {
      /* Skip Write Verification and process Job Result */
      NvM_WriteBlock_ProcessJobResult();
    }
  }
  else if ( Result == MEMIF_JOB_CANCELED )
  {

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_CANCELLED));
    NvM_GlobalErrorStatus = NVM_REQ_CANCELLED;
    /* set CallLevel to zero to terminate this service completely */

    DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),(0U));
    NvM_GlobalCallLevel = 0U;

    NvM_ResetRedundantBlockDataIndex();
  }
  else if (Result == MEMIF_JOB_PENDING)
  {

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }
  else
  {
    NvM_WriteBlock_Async_Error();
  }/* evaluate Result */

  DBG_NVM_WRITEBLOCK_PROCESSJOBRESULT_ASYNC_STATE_EXIT();
}/* end of function NvM_WriteBlock_ProcessJobResult_Async_State */

FUNC(void,NVM_CODE) NvM_WriteBlock_ProcessJobResult(void)
{
  /* Write was successful */

  DBG_NVM_WRITEBLOCK_PROCESSJOBRESULT_ENTRY();
  NvM_GlobalErrorStatus = NVM_REQ_OK;

  if ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
         NVM_BD_BLOCKMNGTTYPE_REDUNDANT
     )
  {
    NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex =
      NVM_INVERT_DATAINDEX(NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex);
  }

  /* Fill the internal buffer/RAM Mirror with data from the RAM block */
  NvM_FillInternalBuffer();
  
  /* Set permanent RAM Block to unchanged so that the data is not
   * written again by NvM_WriteAll().
   */
  NvM_SetPermanentRamBlockUnchanged();

#if (NVM_WRITE_BLOCK_ONCE == STD_ON)
  if ( NVM_BD_WRITEONCE(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    /* Set WriteProtectionFlag and WriteProtectionPermanentFlag */
    NVM_SET_WORKING_STATUS( NVM_DYN_WPF_MASK|NVM_DYN_WPPF_MASK );
    /* The Extented Runtime Block Flag must be reset. It indicates
     * that the block address changed in case NvM Dynamic
     * Configuration is enabled. Now the data is written to the new
     * address and therefore the flag can be reset.
     */
    NVM_CLEAR_WORKING_STATUS( NVM_ERBF_MASK );
  }
#endif

  NvM_StateMachine_TerminateCurrentLevel();


  DBG_NVM_WRITEBLOCK_PROCESSJOBRESULT_EXIT();
}/* end of function NvM_WriteBlock_ProcessJobResult */


STATIC FUNC(void,NVM_CODE) NvM_WriteBlock_ProcessRedundantBlock
(
  NvM_CurrentFunctionPtrType NextState
)
{
  /* Set the next state function for processing a block */

  DBG_NVM_WRITEBLOCK_PROCESSREDUNDANTBLOCK_ENTRY(NextState);
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = NextState;

  if ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
         NVM_BD_BLOCKMNGTTYPE_REDUNDANT
     )
  {
    /* reset error counter */
    NVM_REDUNDANT_ERROR_COUNTER = 0U;

    /* If the first NV block of a redundnat block was previously read successfully,
     * start with the second NV block. Otherwise, start with the first block itself.
     * The current value of dynamic redundancy flag indicates which block has been already
     * read. This is needed since the current DatasetBlockIndex will always be 1 since
     * both blocks are read during Read operation.
     */
    if ((NVM_CHECK_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK)) &&
        (NVM_CHECK_EXT_STATUS(NVM_ES_REDUNDANT_ERROR_MASK))
       )
    {
      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex = 1U;
    }
    else
    {
      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex = 0U;
    }

    /* If a previous read attempt on one of the two NV blocks has failed
     * and if the block data has been recovered from the redundant block,
     * Write-all should write only the failed block.
     * But if the block has been marked as changed, write both blocks.
     * However, write-block should always write both blocks.
     */
    if ( ( NVM_WRITE_ALL_API_ID != NvM_CurrentServiceId ) ||
         ( ( NVM_CHECK_WORKING_STATUS( NVM_DYN_CHANGE_MASK ) ) ||
           ( !NVM_CHECK_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK) )
         )
       )
    {
      /* Write both NV blocks.
       * Set the state function again for processing redundant block.
       */

      DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
      NvM_GlobalCallLevel++;
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = NextState;
    }
  }

  DBG_NVM_WRITEBLOCK_PROCESSREDUNDANTBLOCK_EXIT(NextState);
}/* end of function NvM_WriteBlock_ProcessRedundantBlock */

STATIC FUNC(void,NVM_CODE) NvM_WriteBlock_RedundantBlockError(void)
{
  /* In case of redundant blocks, if the error counter is 0,
   * retry the write operation with the other block.
   * Otherwise report the Dem error.
   * In case of other block types, report the error straightaway.
   */

  DBG_NVM_WRITEBLOCK_REDUNDANTBLOCKERROR_ENTRY();
  if ( ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
           NVM_BD_BLOCKMNGTTYPE_REDUNDANT
       ) &&
       ( NVM_REDUNDANT_ERROR_COUNTER == 0U )
     )
  {
      /* Write the other block also */
      NVM_REDUNDANT_ERROR_COUNTER++;

      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex =
        NVM_INVERT_DATAINDEX(NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex);
  }
  else
  {
#if ( NVM_PROD_ERR_HANDLING_REQ_FAILED == TS_PROD_ERR_REP_TO_DEM )
#if (NVM_REQ_FAILED_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
    NVM_DEM_REPORT_ERROR(NVM_REQ_FAILED_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif ( NVM_PROD_ERR_HANDLING_REQ_FAILED == TS_PROD_ERR_REP_TO_DET )
    NVM_DET_REPORT_ERROR( NvM_CurrentServiceId, NVM_E_DEMTODET_REQ_FAILED );
#endif

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_NOT_OK));
    NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;
  }

  NvM_StateMachine_TerminateCurrentLevel();


  DBG_NVM_WRITEBLOCK_REDUNDANTBLOCKERROR_EXIT();
}/* end of function NvM_WriteBlock_RedundantBlockError */

#if (NVM_WRITE_VERIFICATION == STD_ON)

FUNC(void,NVM_CODE) NvM_WriteBlock_Verify_Async_State(void)
{
  boolean ExecuteBlockVerifyDefault = TRUE;  /* Flag used to identify the
                                                correct verification address*/

  const MemIf_JobResultType Result =
    MemIf_GetJobResult(NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc));

  DBG_NVM_WRITEBLOCK_VERIFY_ASYNC_STATE_ENTRY();

  /* Evaluate the read result */
  if (Result == MEMIF_JOB_OK)
  {
    NvM_PtrToApplDataType VerifyAddress = NvM_GetUserRamBlockAddress();

#if (NVM_STATIC_BLOCKID_CHECK == STD_ON)
    if (NVM_BD_USESTATICBLOCKID(NvM_CurrentBlockDescriptorPtr->blockDesc))
    {
#if (NVM_SYNC_MECHANISM == STD_ON)
      if (!(NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK)))
#endif
      {
        VerifyAddress = &(VerifyAddress[NvM_VerifyOffset - NVM_BLOCKID_LENGTH]);
        ExecuteBlockVerifyDefault = FALSE;
      }
    }
#endif
    if (ExecuteBlockVerifyDefault == TRUE)
    {
      VerifyAddress = &(VerifyAddress[NvM_VerifyOffset]);
    }

    /* Compare RAM data and read back data */
    if (TS_MemCmp(VerifyAddress, WriteVerificationBuffer, NvM_GetVerifyDataSize()) != E_OK)
    {
#if ( NVM_PROD_ERR_HANDLING_VERIFY_FAILED == TS_PROD_ERR_REP_TO_DEM )
#if (NVM_VERIFY_FAILED_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
      NVM_DEM_REPORT_ERROR(NVM_VERIFY_FAILED_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif ( NVM_PROD_ERR_HANDLING_VERIFY_FAILED == TS_PROD_ERR_REP_TO_DET )
      NVM_DET_REPORT_ERROR( NvM_CurrentServiceId, NVM_E_DEMTODET_VERIFY_FAILED );
#endif

      /* Write verification failed. Do write retry */
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_Error;
    }
    else
    {
      /* Next data size to verify */
      NvM_VerifyOffset += NvM_CurrentBlockDescriptorPtr->verifyDataSize;

      if (NvM_VerifyOffset < NvM_GetBlockLength())
      {
        /* Do Write Verification for the remaining data */
        NvM_MemIfReadToVerify();
      }
      else
      {
        /* write verification successfully finished */
        NvM_WriteBlock_ProcessJobResult();
      }
    }
  }
  else if ( Result == MEMIF_JOB_PENDING)
  {

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }
  else
  {
    /* write verification skipped due to read failure */
    NvM_WriteBlock_ProcessJobResult();
  }

  DBG_NVM_WRITEBLOCK_VERIFY_ASYNC_STATE_EXIT();
}/* end of function NvM_WriteBlock_Verify_Async_State */


STATIC FUNC(void, NVM_CODE) NvM_MemIfReadToVerify(void)
{
  CONST (MemIf_StatusType, AUTOMATIC) Status =
    MemIf_GetStatus(NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc));

  DBG_NVM_MEMIFREADTOVERIFY_ENTRY();

  if (MEMIF_IDLE == Status)
  {
    /* Read data for write verification */
    if ( MemIf_Read(
          NVM_BD_DEVICEID(NvM_CurrentBlockDescriptorPtr->blockDesc),
          NvM_GetMergedBlockNumber(),
          NvM_VerifyOffset,
          WriteVerificationBuffer,
          NvM_GetVerifyDataSize()) == E_OK
       )
    {
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Verify_Async_State;
    }
    else
    {
      /* Write verification skipped due to read failure */
      NvM_WriteBlock_ProcessJobResult();
    }
  }
  else
  {
    /* If the MemIf returns busy, return from MainFunction */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }

  DBG_NVM_MEMIFREADTOVERIFY_EXIT();
}/* end of function NvM_MemIfReadToVerify */

STATIC FUNC(uint16, NVM_CODE) NvM_GetVerifyDataSize(void)
{
  uint16 TotalDataSize = NvM_GetBlockLength();
  uint16 VerifyDataSize = NvM_VerifyOffset + NvM_CurrentBlockDescriptorPtr->verifyDataSize;

  DBG_NVM_GETVERIFYDATASIZE_ENTRY();

  if (TotalDataSize >= VerifyDataSize)
  {
    VerifyDataSize = NvM_CurrentBlockDescriptorPtr->verifyDataSize;
  }
  else
  {
    VerifyDataSize = TotalDataSize - NvM_VerifyOffset;
  }

  DBG_NVM_GETVERIFYDATASIZE_EXIT(VerifyDataSize);
  return VerifyDataSize;
}/* end of function NvM_GetVerifyDataSize */

#endif

STATIC FUNC(void, NVM_CODE) NvM_FillInternalBuffer(void)
{
  NvM_PtrToApplDataType DataAddress = NvM_GetDataAddress();
#if (NVM_STATIC_BLOCKID_CHECK == STD_ON)
  NvM_PtrToApplDataType BufAddress = NvM_GetBufferAddress();
#endif
  DBG_NVM_FILLINTERNALBUFFER_ENTRY();

#if (NVM_INTERNAL_BUFFER_SIZE != 0U)
  /* Copy data from user RAM block to internal buffer */
  /* In case mirror is used data has already been copied to internal buffer */
  if ((NVM_BD_USEINTERNALBUFFER(NvM_CurrentBlockDescriptorPtr->blockDesc)) &&
     (!(NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK))))
  {
    TS_MemCpy(DataAddress, NvM_GetUserRamBlockAddress(),
             NvM_CurrentBlockDescriptorPtr->nvBlockLength);
  }

  if (NVM_BD_CRCTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) != NVM_BD_CRCTYPE_NONE)
  {
    DataAddress = &(DataAddress[NvM_CurrentBlockDescriptorPtr->nvBlockLength]);
    /* Copy CRC from the CRC Buffer */
    NvM_CopyCrc(DataAddress);
  }
#endif

#if (NVM_STATIC_BLOCKID_CHECK == STD_ON)
  /* If Static Block Id is enabled,
   * Copy the Block Identifier to internal buffer (NVM522, NVM523).
   */
  if (NVM_BD_USESTATICBLOCKID(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    /* Deviation MISRA-2 */
    TS_MemCpy(BufAddress, NVM_STATIC_BLOCKID(), NVM_BLOCKID_LENGTH);
    BufAddress = NVM_BLOCKID_BUFADDR();
  }
#endif

  DBG_NVM_FILLINTERNALBUFFER_EXIT();
}

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file NvM_WriteBlock.c]==========================*/
