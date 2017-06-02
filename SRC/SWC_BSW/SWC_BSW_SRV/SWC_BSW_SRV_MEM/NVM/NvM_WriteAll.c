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
 *    Reason: The operands are only primary-expressions.
 */
/* !LINKSTO NVM076,1 */

/*==================[inclusions]============================================*/

#include <NvM_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types             */

/* prevent redundant declarations of RTE types */
#define NVM_INTERNAL_USE

/* !LINKSTO NVM554,1 */
#include <SchM_NvM.h>
/* !LINKSTO NVM554,1 */
#include <MemIf.h>

/* !LINKSTO NVM554,1 */
#include <NvM.h>                  /* Extern NVRAM Manager API definitions   */

#include <NvM_FunctionIntern.h>   /* NvM functions which are used           */
                                  /* only within the NvM module.            */
#include <NvM_DataIntern.h>       /* NvM data which is used only            */
                                  /* within the NvM module.                 */
#include <NvM_Queue.h>            /* queue external definitions.            */
#include <NvM_StateMachine.h>     /* External defintions for unit           */
                                  /* StateMachine                           */

#if ( NVM_DEV_ERROR_DETECT == STD_ON )
/* !LINKSTO NVM556,1 */
#include <Det.h>                 /* API of module Det.                     */
#endif

/* if any DEM event is switched on, include Dem.h */
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM)
/* !LINKSTO NVM554,1 */
#include <Dem.h>
#endif

/* if multi block job status reporting is switched on, include BswM_NvM.h */
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFO == STD_ON)
#include <BswM_NvM.h>
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief Third state of the asynchronous state machine of API function
 **        NvM_WriteAll().
 **
 **        Call PostService_Function() for last block write operation.
 **/
STATIC FUNC(void,NVM_CODE) NvM_WriteAll_Async_State2(void);

/** \brief Fourth state of the asynchronous state machine of API function
 **        NvM_WriteAll().
 **
 **        Terminates the NvM_WriteAll().
 **/
STATIC FUNC(void,NVM_CODE) NvM_WriteAll_Async_State3(void);

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

FUNC(void,NVM_CODE) NvM_WriteAll(void)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_NVM_WRITEALL_ENTRY();

#if ( NVM_DEV_ERROR_DETECT == STD_ON )
  /* Check if module is initialized by NvM_Init() */
  if ( NVM_CHECK_GLOBAL_GENERIC_STATUS_FALSE( NVM_GENERIC_INIT_FLAG_MASK ) )
  {
    NVM_DET_REPORT_ERROR( NVM_WRITE_ALL_API_ID, NVM_E_NOT_INITIALIZED );
  }
  else if ( NvM_AdminBlockTable[0U].NvMResult == NVM_REQ_PENDING )
  {
    NVM_DET_REPORT_ERROR( NVM_WRITE_ALL_API_ID, NVM_E_BLOCK_PENDING );
  }
  else
#endif
  {
    /* protect concurrent access to the standard queue */
    SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

    if (NvM_AdminBlockTable[0U].NvMResult != NVM_REQ_PENDING)
    {
      /* Insert the request in the queue.
       * BlockId 0 for Multi Block Request; NULL_PTR as data address
       */
      Result = NvM_Queue_InsertStandard(0U, NULL_PTR, &NvM_WriteAll_Async);
    }

    SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

    /* Check if standard queue is already full */
    if (E_OK != Result)
    {
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM)
#if (NVM_QUEUE_OVERFLOW_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
      NVM_DEM_REPORT_ERROR(NVM_QUEUE_OVERFLOW_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DET)
      NVM_DET_REPORT_ERROR(NVM_WRITE_ALL_API_ID, NVM_E_DEMTODET_QUEUE_OVERFLOW);
#endif
    }


    /* Check if write-all queued */
    if (E_OK == Result)
    {
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFO == STD_ON)
      /* WriteAll request status has changed, report the request status to BswM */
      BswM_NvM_CurrentJobMode(NVM_WRITE_ALL_API_ID, NVM_REQ_PENDING);
#endif
    }
  }

  DBG_NVM_WRITEALL_EXIT();
}

FUNC(void,NVM_CODE) NvM_CancelWriteAll(void)
{
  uint8 Index;                       /* Index in the standard queue */

  DBG_NVM_CANCELWRITEALL_ENTRY();

#if ( NVM_DEV_ERROR_DETECT == STD_ON )
  /* Check if module is initialized by NvM_Init() */
  if ( NVM_CHECK_GLOBAL_GENERIC_STATUS_FALSE( NVM_GENERIC_INIT_FLAG_MASK ) )
  {
    NVM_DET_REPORT_ERROR( NVM_CANCEL_WRITE_ALL_API_ID, NVM_E_NOT_INITIALIZED );
  }
  else
#endif
  {
    /* protect concurrent access to NvM_AdminBlockTable[BlockId].NvMResult and
     * the queues */
    SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

    /* check if NvM_WriteAll() is currently pending. */
    if ( ( NvM_CurrentServiceId == NVM_WRITE_ALL_API_ID ) ||
         ( NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] == &NvM_WriteAll_Async )
       )
    {
      /* Current API is NvM_WriteAll -> set Cancel Write All flag */
        NVM_SET_GLOBAL_GENERIC_STATUS( NVM_GENERIC_CWA_MASK );
        DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),
           (NvM_GlobalGenericStatus | NVM_GENERIC_CWA_MASK));
    }

    /* Check if NvM_WriteAll() or NvM_ReadAll() is currently enqueued   */
    else if ( NvM_AdminBlockTable[0U].NvMResult == NVM_REQ_PENDING )
    {
      /* Search item in Queue by checking the function pointer;
       * Remove item by moving all other queued items one position
       */
      /* Start from the value of Queue Index and search inwards */
      Index = NvM_Queue_IndexStandard;

      /* Search each request in the queue until we find the NvM_WriteAll request
       * Or until all elements have been searched.
       */
      while ( ( Index != NVM_QUEUE_INDEX_RESET ) &&
              ( NvM_Queue_Standard[Index].NvMRequestAsyncPtr != &NvM_WriteAll_Async )
            )
      {
        /* Move the index inwards */
        Index--;
      }

      /* If Index reaches 0xFF, we know that the WriteAll request
       * is not found in the queue
       */
      if ( Index != NVM_QUEUE_INDEX_RESET )
      {
        /* A WriteAll request is found; move the remaining requests
         * inwards replacing the WriteAll request
         */
        while ( Index < NvM_Queue_IndexStandard )
        {
          /* Move the next queue item to the current index */
          NvM_Queue_Standard[Index] = NvM_Queue_Standard[Index + 1U];
          /* Compare with the next request in the queue */
          Index++;
        }
        /* To remove the WriteAll request from the standard queue,
         * decrement current value of standard Queue Index.
         * In case the value is 0, set it to uninitialized (0xFF).
         */
        NVM_STANDARD_QUEUE_DOWN();

        /* Set state of block request to cancelled */
        NvM_AdminBlockTable[0U].NvMResult = NVM_REQ_CANCELLED;

        /* NvM_WriteAll request removed from queue -> set Cancel Write All flag */
        NVM_SET_GLOBAL_GENERIC_STATUS( NVM_GENERIC_CWA_MASK );
        DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),
           (NvM_GlobalGenericStatus | NVM_GENERIC_CWA_MASK));
      }
    }
    else
    {
      /* else: No WriteAll or ReadAll requests pending or enqueued */
    }

    SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();
  }

  DBG_NVM_CANCELWRITEALL_EXIT();
}

/*==================[internal function definitions]==========================*/

FUNC(void,NVM_CODE) NvM_WriteAll_Async(void)
{
  DBG_NVM_WRITEALL_ASYNC_ENTRY();

  /* STEP_1: set service ID of NvM_WriteAll */
  /* Since the processing of NvM_WriteAll() has
   * been started, NvM_CurrentServiceId needs to be set
   */
  NvM_CurrentServiceId = NVM_WRITE_ALL_API_ID;

  /* STEP_2: start with last configured block Id.
   * Block ID 1 (configuration ID) shall be written only at the end (NVM733).
   */
  NvM_GlobalBlockNumber = NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS;

  /* STEP_3: set interim result of write all to NVM_REQ_OK.
   *         Note: the real result is set to NVM_REQ_PENDING.
   */
  NVM_REQUEST_INTERIM_RESULT = NVM_REQ_OK;

  /* STEP_4: switch to fast mode if configured */
#if ( NVM_DRV_MODE_SWITCH == STD_ON )

  MemIf_SetMode( MEMIF_MODE_FAST );

#endif

  /* proceed with state 1 */
  NvM_WriteAll_Async_State1();

  DBG_NVM_WRITEALL_ASYNC_EXIT();
}

FUNC(void,NVM_CODE) NvM_WriteAll_Async_State1(void)
{
#if (NVM_NUMBER_OF_SELECT_BLOCK_FOR_WRITEALL > 0U)
  boolean ExecuteWriteAllAsyncState1 = FALSE;  /* Flag used to check whether all the
                                                  condition for Write All is satisfied. */
#endif
  DBG_NVM_WRITEALL_ASYNC_STATE1_ENTRY();


  /* Check if NvM_CancelWriteAll() was invoked */
  if ((NVM_CHECK_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CWA_MASK)) &&
      /* In case NvM_CancelWriteAll() was called and at the same time an immediate write job
       * interrupted the currently processed block, NvM must finish the processing of the
       * current block in a non-destructive way. */
      /* !LINKSTO NVM238,1 */
      (NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMRequestAsyncPtr == &NvM_WriteAll_Async))
  {
    NVM_CLEAR_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CWA_MASK);
    DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus & (uint8)((uint8)(~(NVM_GENERIC_CWA_MASK)) & 0xFFU)));

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_CANCELLED));
    NvM_GlobalErrorStatus = NVM_REQ_CANCELLED;
    NvM_MultiPostService_Function();
  }
  else
  {
    /* In case NvM_WriteAll() was interrupted by an immediate write job, the multi-block
     * request shall be resumed from the current block number. Otherwise NvM_WriteAll()
     * must proceed with the next block.
     */
    if (NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMBlockIdentifier == NVM_BLOCK_MULTI)
    {
      /* proceed with next block */
      NvM_GlobalBlockNumber--;
    }

    /* NOTE: NvM_PreService_Function() must be invoked before
     *       NVM_CHECK_CONST_BLOCK_STATUS else the BlockDescriptorPointer
     *       is not set correctly. Also the global working status is not
     *       set.
     */
    NvM_PreService_Function();

    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteAll_Async_State2;

#if (NVM_NUMBER_OF_SELECT_BLOCK_FOR_WRITEALL > 0U)

    /* check whether the current block has an assigned permanent
     * RAMDataBlock and the block is valid and the data has changed and the
     * block is not write protected or locked and also WriteAll is enabled for that
     * particular block.
     * NOTE: If an erroneous block could be recovered with informations from
     *       the redundant block, the block will be also written (independent
     *       of the write protection).
     * The data change flag can be set by NvM_RestoreBlock_Defaults() and
     * NvM_SetRamBlockStatus().
     */
    /* check if the current block is selected for WriteAll */
    if (NVM_BD_WRITEALL(NvM_CurrentBlockDescriptorPtr->blockDesc))
    {
      /* !LINKSTO NVM128,1, NVM133,1 */
      if ((NvM_CurrentBlockDescriptorPtr->ramBlockDataAddress != NULL_PTR) &&
           (NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMValid == NVM_BLOCK_VALID) &&
            (!NVM_CHECK_WORKING_STATUS(NVM_DYN_LOCK_MASK)))
      {
        if (((NVM_CHECK_WORKING_STATUS(NVM_DYN_CHANGE_MASK)) &&
              /* Deviation MISRA-1 */
             ((NvM_CheckWriteProtection(NvM_GlobalBlockNumber)) == FALSE)
              /* Deviation MISRA-1 */
            ) || (NVM_CHECK_WORKING_STATUS(NVM_DYN_REDUNDANCY_MASK))
           )
        {
          ExecuteWriteAllAsyncState1 = TRUE;
        }
#if (NVM_ADVANCED_RECOVERY == STD_ON)
        else if (NVM_CHECK_EXT_STATUS(NVM_ES_ADVANCED_RECOVERY_MASK))
        {
          ExecuteWriteAllAsyncState1 = TRUE;
        }
        else
        {
          /* Nothing to do (MISRA) */
        }
#endif
      }
    }

    /* Check if write-all condition satisfied */
    if (ExecuteWriteAllAsyncState1 == TRUE)
    {
      NVM_CLEAR_EXT_STATUS(NVM_ES_ADVANCED_RECOVERY_MASK);

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

      /* The data in the permanent RAMDataBlock has changed */
      /* --> copy data to Non Volatile Memory.              */

      /* Check if another job is pending or cancelled for the processing
       * block ID and set the Multi Request Keep Job Pending flag and
       * Block request Cancelled Flag accordingly. */
      NvM_CheckBlockStatus();

      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult = NVM_REQ_PENDING;

      NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;

      NvM_GlobalCallLevel++;
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteBlock_Async_State1;
    }
    else
#endif /* NVM_NUMBER_OF_SELECT_BLOCK_FOR_WRITEALL > 0U */
    {
      /* Check if another job is pending or cancelled for the processing
       * block ID and set the Multi Request Keep Job Pending flag and
       * Block request Cancelled Flag accordingly. */
      NvM_CheckBlockStatus();

      if (NVM_BD_WRITEALL(NvM_CurrentBlockDescriptorPtr->blockDesc))
      {
        DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_BLOCK_SKIPPED));

        /* only blocks selected for WriteAll shall be marked as NVM_REQ_BLOCK_SKIPPED */
        NvM_GlobalErrorStatus = NVM_REQ_BLOCK_SKIPPED;
      }
    }
  }

  /* Restore the function pointer and block number in the queue entry because
   * NvM_WriteAll() might have been interrupted by an immediate write request.
   */
  NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMRequestAsyncPtr = &NvM_WriteAll_Async;
  NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMBlockIdentifier = NVM_BLOCK_MULTI;

  DBG_NVM_WRITEALL_ASYNC_STATE1_EXIT();
}

STATIC FUNC(void,NVM_CODE) NvM_WriteAll_Async_State2(void)
{
  /* Set error status of finished block and internal management data. */

  DBG_NVM_WRITEALL_ASYNC_STATE2_ENTRY();

  if (NVM_BD_WRITEALL(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    /* update the status for blocks processed by NvM_WriteAll() */
    NvM_MultiRequestFinishedSingleBlock( &NvM_WriteAll_Async_State1 );
  }
  else
  {
    /* Clear the global generic status */
    if ((NVM_CHECK_GLOBAL_GENERIC_STATUS( NVM_GENERIC_MRKJP_MASK )) &&
        (!NVM_CHECK_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CANCEL_MASK)))
    {
      /* Another request for this block was inserted in the queue.
       * Therefore the ErrorStatus must remain NVM_REQ_PENDING
       * after the block was processed by NvM_WriteAll().
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
       * NvM_WriteAll().
       */
      NVM_CLEAR_GLOBAL_GENERIC_STATUS(NVM_GENERIC_CANCEL_MASK);
      DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus & (uint8)((uint8)(~(NVM_GENERIC_CANCEL_MASK)) & 0xFFU)));
      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult = NVM_REQ_CANCELED;
    }
    else
    {
      /* Nothing to do (MISRA) */
    }

    /* set pointer to next state */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteAll_Async_State1;
  }

  /* Check if last block is written then NvM_WriteAll must be terminated. */
  if (NvM_GlobalBlockNumber == NVM_BLOCK_CONFIG_ID)
  {
    /* set pointer to next state */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_WriteAll_Async_State3;
  }

  DBG_NVM_WRITEALL_ASYNC_STATE2_EXIT();
}

STATIC FUNC(void,NVM_CODE) NvM_WriteAll_Async_State3(void)
{
  MemIf_StatusType Result;

  DBG_NVM_WRITEALL_ASYNC_STATE3_ENTRY();

  /* get status of underlying drivers */
  Result = MemIf_GetStatus(MEMIF_BROADCAST_ID);

  if ((Result != MEMIF_BUSY) && (Result != MEMIF_BUSY_INTERNAL))
  {
    /* The underlying drivers are all idle */
    /* --> WriteAll() can be terminated    */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQUEST_INTERIM_RESULT));
    NvM_GlobalErrorStatus = NVM_REQUEST_INTERIM_RESULT;
    NvM_MultiPostService_Function();
  }
  else
  {
    /* If the MemIf returns busy, return from MainFunction */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_PENDING));
    NvM_GlobalErrorStatus = NVM_REQ_PENDING;
  }

  DBG_NVM_WRITEALL_ASYNC_STATE3_EXIT();
}

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]============================================*/
