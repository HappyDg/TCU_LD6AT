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

/* Misra-C:2004 Deviations:
 *
 */

/* !LINKSTO NVM076,1 */
/*==================[inclusions]============================================*/

#include <NvM_Trace.h>
#include <TSAutosar.h>            /* EB specific standard types             */

/* prevent redundant declarations of RTE types */
#define NVM_INTERNAL_USE
/* !LINKSTO NVM554,1 */
#include <MemIf.h>                /* for MemIf_SetMode() */
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

#if ( NVM_DEV_ERROR_DETECT == STD_ON )
/* !LINKSTO NVM556,1 */
#include <Det.h>                  /* API of module Det.                     */
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

/** \brief Forces a block to be written on request NvM_WriteAll()
 **
 **        The status bits of a block are manipulated so that this block is written
 **        on the next call of NvM_WriteAll().
 **/
STATIC FUNC(void,NVM_CODE) NvM_ForceForWriteAll(void);

/** \brief Evaluates Configuration Id which is read from NV memory.
 **/
STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State1(void);

/** \brief Third state of the asynchronous state machine of API function
 **        NvM_ReadAll. Finishes read operation of current block.
 **/
STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State6(void);

#if ( NVM_NUMBER_OF_SELECT_BLOCK_FOR_READALL_BLOCKS > 0U )

/** \brief Compares calculated CRC vs. CRC stored in RAM Block.
 **/
STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State7(void);
/** \brief Checks if ROM default data or NVM data must be copied
 **        to the RAM Block and starts copy process.
 **/
STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State8(void);

#endif /* NVM_NUMBER_OF_SELECT_BLOCK_FOR_READALL_BLOCKS > 0U */

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>
FUNC(void,NVM_CODE) NvM_ReadAll(void)
{
  Std_ReturnType Result = E_NOT_OK;

  DBG_NVM_READALL_ENTRY();

/************** ( NVM_DEV_ERROR_DETECT == STD_ON ) *************/
#if ( NVM_DEV_ERROR_DETECT == STD_ON )

  /* Check if module is initialized by NvM_Init() */
  if ( NVM_CHECK_GLOBAL_GENERIC_STATUS_FALSE( NVM_GENERIC_INIT_FLAG_MASK ) )
  {
    NVM_DET_REPORT_ERROR( NVM_READ_ALL_API_ID, NVM_E_NOT_INITIALIZED );
  }
  else if ( NvM_AdminBlockTable[0U].NvMResult == NVM_REQ_PENDING )
  {
    NVM_DET_REPORT_ERROR( NVM_READ_ALL_API_ID, NVM_E_BLOCK_PENDING );
  }
  else
#endif /* NVM_DEV_ERROR_DETECT == STD_ON */
  {
    /* protect concurrent access to the standard queue */
    SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

    if (NvM_AdminBlockTable[0U].NvMResult != NVM_REQ_PENDING)
    {
      /* Insert the request in the queue.
       * BlockId 0 for Multi Block Request; NULL_PTR as data address
       */
      Result = NvM_Queue_InsertStandard(0U, NULL_PTR, &NvM_ReadAll_Async);
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
      NVM_DET_REPORT_ERROR(NVM_READ_ALL_API_ID, NVM_E_DEMTODET_QUEUE_OVERFLOW);
#endif
    }

    /* Check if read-all queued */
    if (E_OK == Result)
    {
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFO == STD_ON)
      /* ReadAll request staus has changed, report the request status to BswM */
      BswM_NvM_CurrentJobMode(NVM_READ_ALL_API_ID, NVM_REQ_PENDING);
#endif
    }
  }

  DBG_NVM_READALL_EXIT();
}

/*==================[internal function definitions]==========================*/

STATIC FUNC(void,NVM_CODE) NvM_ForceForWriteAll(void)
{
  /* set bit 1 to 0: WriteProtectionFlag  ( WPF )           */
  /* set bit 5 to 0: WriteProtectionPermanentFlag ( WPPF )  */

  DBG_NVM_FORCEFORWRITEALL_ENTRY();
  NvM_GlobalWorkingStatus &=
    ( NvM_DynamicStatusType )(~( NvM_DynamicStatusType )
      ( NVM_DYN_WPF_MASK|NVM_DYN_WPPF_MASK ) );

  /* set bit 6 to 1: ExtentedRuntimeBlockFlag ( ERBF )     */

  DBG_NVM_GLOBALWORKINGSTATUS((NvM_GlobalWorkingStatus),((NvM_GlobalWorkingStatus)|(NVM_ERBF_MASK)));
  NvM_GlobalWorkingStatus |= NVM_ERBF_MASK;

  /* set block to valid and changed */
  NvM_SetPermanentRamBlockValid();
  NvM_SetPermanentRamBlockChanged();

  /* NOTE: the high byte of 'NvM_GlobalWorkingStatus gets lost. The  */
  /*       high byte contains information which is only required     */
  /*       while processing the request und need not be stored       */
  /*       permanently in the 'NvM_AdminBlockTable'.                 */
  NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDynStatus
   = ( uint8 )NvM_GlobalWorkingStatus;

  DBG_NVM_FORCEFORWRITEALL_EXIT();
}


FUNC(void,NVM_CODE) NvM_ReadAll_Async(void)
{

  DBG_NVM_READALL_ASYNC_ENTRY();

  /* Since the processing of NvM_ReadAll() has
   * been started, NvM_CurrentServiceId needs to be set
   */
  NvM_CurrentServiceId = NVM_READ_ALL_API_ID;

  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State0;

  DBG_NVM_READALL_ASYNC_EXIT();
}

FUNC(void,NVM_CODE) NvM_ReadAll_Async_State0(void)
{
  DBG_NVM_READALL_ASYNC_STATE0_ENTRY();

  /* Restore the function pointer and block number in the queue entry because
   * NvM_ReadAll() might have been interrupted by an immediate write request.
   */
  NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMRequestAsyncPtr = &NvM_ReadAll_Async;
  NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMBlockIdentifier = NVM_BLOCK_MULTI;

  /* Switch to fast mode if configured */
#if ( NVM_DRV_MODE_SWITCH == STD_ON )

  MemIf_SetMode( MEMIF_MODE_FAST );

#endif

  /* Read Configuration Id from block 1 */
  NvM_GlobalBlockNumber = NVM_BLOCK_CONFIG_ID;
  /* NvM_PreService_Function must be called after the NvM_GlobalBlockNumber
   * is set. Else the initialization of the global variables is incorrect. */
  NvM_PreService_Function();

  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State1;

  DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
  NvM_GlobalCallLevel++;
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State0;

  DBG_NVM_READALL_ASYNC_STATE0_EXIT();
}

STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State1(void)
{
  /* Evaluate result of Configuration Id read operation */

  boolean RestoreBlockDefaultsIndicator = FALSE;

  DBG_NVM_READALL_ASYNC_STATE1_ENTRY();

  if ( NvM_GlobalErrorStatus == NVM_REQ_NV_INVALIDATED )
  {
    RestoreBlockDefaultsIndicator = TRUE;
  }
  else
  {
    if ((NvM_GlobalErrorStatus == NVM_REQ_OK) || (NvM_GlobalErrorStatus == NVM_REQ_REDUNDANCY_FAILED))
    {
      /* compare read Configuration Id versus Compiled Configuration Id.
       */
      if ( NvM_ConfigurationId[0] != NvM_CompiledConfigurationId )
      {
        /* The Configuration Ids does NOT match --> set error/status to
         * to NVM_REQ_NOT_OK ( NVM307 )
         */

        DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_NOT_OK));
        NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;
#if ( NVM_DYNAMIC_CONFIGURATION != STD_ON )
        /* NVM248: Configuration ID mismatch and
         *         NvM_DynamicConfiguration == FALSE --> proceed with
         *         normal behaviour --> don't write Compiled
         *         Configuration Id automatically --> set block 1
         *         to unchanged.
         */
        NvM_SetPermanentRamBlockUnchanged();
#endif
      }
      else
      {
        /* NVM313: The Configuration Ids are equal --> the Compiled
         *         Configuration Id must not be written --> set block to
         *         unchanged ( NVM313 )
         */
        NvM_SetPermanentRamBlockUnchanged();
      }

    } /* if ( NvM_GlobalErrorStatus == NVM_REQ_OK ) */
    else
    {
      /* NVM305: Configuration cannot be read because of an error
       *         was detetected by the underlying SW layers.
       */

      DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_INTEGRITY_FAILED));
      NvM_GlobalErrorStatus = NVM_REQ_INTEGRITY_FAILED;
    }
#if ( NVM_DYNAMIC_CONFIGURATION == STD_ON )
    if ((NvM_GlobalErrorStatus != NVM_REQ_OK) && (NvM_GlobalErrorStatus != NVM_REQ_REDUNDANCY_FAILED))
    {

       /* Indicate that dynamic configuration must be applied to all
        * blocks processed by NvM_ReadAll.
        */
       NVM_SET_GLOBAL_GENERIC_STATUS( NVM_GENERIC_DC_MASK );
       DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus | NVM_GENERIC_DC_MASK));
       RestoreBlockDefaultsIndicator = TRUE;
    }
    else
#endif
    {
       /* Indicate that normal processing of all blocks must be
        * applied.
        */
       NVM_CLEAR_GLOBAL_GENERIC_STATUS( NVM_GENERIC_DC_MASK );
       DBG_NVM_GLOBALGENERICSTATUS((NvM_GlobalGenericStatus),(NvM_GlobalGenericStatus & (uint8)((uint8)(~(NVM_GENERIC_DC_MASK)) & 0xFFU)));
    }

  }/* else - if ( NvM_GlobalErrorStatus == NVM_REQ_NV_INVALIDATED ) */

  /* Write error status of Configuration Id block */
  NvM_PostService_Function();

#if ( NVM_NUMBER_OF_SINGLE_BLOCK_CALLBACK > 0U )
  /* !LINKSTO NVM176,1 */
  /* Invoke block specific callback function */
  NvM_InvokeSingleBlockCallback(NvM_GlobalBlockNumber,
                                NvM_CurrentServiceId, 
                                NvM_GlobalErrorStatus);
#endif

  /* When an error occured while processing the ConfigurationId Block the
   * the multi block job result must be set to NVM_REQ_NOT_OK ( NVM301 ).
   */
  if ((NvM_GlobalErrorStatus != NVM_REQ_OK) && (NvM_GlobalErrorStatus != NVM_REQ_REDUNDANCY_FAILED))
  {
    NVM_REQUEST_INTERIM_RESULT = NVM_REQ_NOT_OK;
  }
  else
  {
    NVM_REQUEST_INTERIM_RESULT = NVM_REQ_OK;
  }
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State5;
  if ( RestoreBlockDefaultsIndicator == TRUE )
  {
    /* Copy Compiled Configuration Id to Configuration Id RAM buffer
     * and set valid and changed bits so that it is written by
     * next NvM_WriteAll().
     */
    NvM_ForceForWriteAll();

    DBG_NVM_GLOBALCALLLEVEL((NvM_GlobalCallLevel),((NvM_GlobalCallLevel)+1U));
    NvM_GlobalCallLevel++;
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State0;
  }

  DBG_NVM_READALL_ASYNC_STATE1_EXIT();
}

FUNC(void,NVM_CODE) NvM_ReadAll_Async_State5(void)
{
  /* check if there are more blocks to process */

  DBG_NVM_READALL_ASYNC_STATE5_ENTRY();

  if ( NvM_GlobalBlockNumber < ( NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS - 1U ) )
  {
    /* In case NvM_ReadAll() was interrupted by an immediate write job, the multi-block
     * request shall be resumed from the current block number. Otherwise NvM_ReadAll()
     * must proceed with the next block.
     */
    if (NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMBlockIdentifier == NVM_BLOCK_MULTI)
    {
      /* proceed with next block */
      NvM_GlobalBlockNumber++;
    }

    /* NOTE: NvM_PreService_Function() must be called before
     *       NVM_CHECK_CONST_BLOCK_STATUS is used else the
     *       BlockDescriptorPointer is not set correctly.
     */
    NvM_PreService_Function();

    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State6;

#if ( NVM_NUMBER_OF_SELECT_BLOCK_FOR_READALL_BLOCKS > 0U )

    /* Process only blocks who have a permanent RAM block ( NVM356,NVM718 )
     * and configuration parameter 'SelectBlockForReadAll' is enabled
     * ( NVM118 ).
     * All block management types are processed.
     */
    if ( ( NvM_CurrentBlockDescriptorPtr->ramBlockDataAddress != NULL_PTR ) &&
         ( NVM_BD_READALL(NvM_CurrentBlockDescriptorPtr->blockDesc) )
       )
    {
      /* Check if another job is pending or cancelled for the processing
       * block ID and set the Multi Request Keep Job Pending flag and
       * Block request Canceled Flag accordingly. */
      NvM_CheckBlockStatus();

      /* Status of currently processed block must be set to
       * NVM_REQ_PENDING.
       */
      NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMResult = NVM_REQ_PENDING;
      NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;

      /* !LINKSTO NVM128,1, NVM133,1 */
      if ( NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMValid != NVM_BLOCK_VALID )
      {
        /* Current block RAMBlockStatus is INVALID
         * --> copy data from NVM Block or ROM Block ( NVM362,NVM363 ).
         */
        NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State8;

      }/* if ( NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMValid .. */
      else
      {

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_RAMBLOCK_CRC_BUFFER_SIZE > 0U))
         if ( (NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMExtendedStatus &
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

        /* Current block RAMBlockStatus is VALID
         * --> Check if CRC must be recalculated and checked
         */
        if(NVM_BD_CALCRAMBLOCKCRC(NvM_CurrentBlockDescriptorPtr->blockDesc))
        {
          /* parameter NVM_CALC_RAM_BLOCK_CRC is TRUE.
           * --> recalculate CRC and verify with CRC stored in block
           *     specific RAM CRC buffer ( NVM362 ).
           */
          NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State7;

          /* Calculate CRC of the Permanent RAM Data Block */
          NvM_CalculateCrc(
            NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].ramBlockDataAddress );

        }/* if ( NVM_CHECK_CONST_BLOCK_STATUS( NVM_CALCRAMBLOCKCRC_MASK ) )  */
        else
        {
          /* RAM Block Status is valid and CRC need not to be
           * recalculated
           * --> The NvM data must not be loaded by NvM_ReadAll()
           * --> Set specific block result to NVM_REQ_BLOCK_SKIPPED
           *     ( NVM287 ).
           */
          NvM_GlobalErrorStatus = NVM_REQ_BLOCK_SKIPPED;
        }/* else-if ( NVM_CHECK_CONST_BLOCK_STATUS( NVM_CALCRAMBLOCKCRC_MASK ) )  */

      }/* else-if ( NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMValid    */

    }/* end of if ( current block is processed ) */
    else
#endif /* NVM_NUMBER_OF_SELECT_BLOCK_FOR_READALL_BLOCKS > 0U */
    {
      /* Check if another job is pending or cancelled for the processing
       * block ID and set the Multi Request Keep Job Pending flag and
       * Block request Canceled Flag accordingly. */
      NvM_CheckBlockStatus();

      /* Current block must not be processed --> set error status
       * to NVM_REQ_BLOCK_SKIPPED
       */
      if (NVM_BD_READALL(NvM_CurrentBlockDescriptorPtr->blockDesc))
      {
        DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_BLOCK_SKIPPED));
        NvM_GlobalErrorStatus = NVM_REQ_BLOCK_SKIPPED;
      }
    }
  }/* if ( NvM_GlobalBlockNumber < ( NvM_TotalNumberOfNvramBlocks - 1 ) ) */
  else
  {
    /* All blocks finished */
    /* Set final result of multi block request */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQUEST_INTERIM_RESULT));
    NvM_GlobalErrorStatus = NVM_REQUEST_INTERIM_RESULT;
    NvM_MultiPostService_Function();
  }/* else-if ( NvM_GlobalBlockNumber < ( NvM_TotalNumberOfNvramBlocks - 1 ) ) */

  /* Restore the function pointer and block number in the queue entry because
   * NvM_ReadAll() might have been interrupted by an immediate write request.
   */
  NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMRequestAsyncPtr = &NvM_ReadAll_Async;
  NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMBlockIdentifier = NVM_BLOCK_MULTI;

  DBG_NVM_READALL_ASYNC_STATE5_EXIT();
}

STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State6(void)
{
  /* Set error status of finished block and internal management data. */

  DBG_NVM_READALL_ASYNC_STATE6_ENTRY();
  if (NVM_BD_READALL(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    NvM_MultiRequestFinishedSingleBlock( &NvM_ReadAll_Async_State5 );
  }
  else
  {
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
       * in the queue, but it must be canceled. Therefore the ErrorStatus
       * must remain NVM_REQ_CANCELED after the block was processed by
       * NvM_WriteAll() or NvM_ReadAll().
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
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State5;
  }

  DBG_NVM_READALL_ASYNC_STATE6_EXIT();
}

#if ( NVM_NUMBER_OF_SELECT_BLOCK_FOR_READALL_BLOCKS > 0U )

STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State7(void)
{
  DBG_NVM_READALL_ASYNC_STATE7_ENTRY();

  /* Verify calculated CRC vs. CRC stored in user RAM CRC Buffer */
  NvM_GlobalErrorStatus = NvM_CheckCrc( NvM_GetStoredRamCRCAddress() );

  if ( NvM_GlobalErrorStatus == NVM_REQ_OK )
  {
    /* CRC verification successfull
     * --> RAMBlockStatus is already valid and consistent
     * --> Don't copy NVM or ROM Block ( NVM364 ).
     */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State6;
  }
  else
  {
    /* CRC verification failed
     * --> RAMBlockStatus is valid and inconsistent
     * --> Copy NVM or ROM Block ( NVM363 ).
     */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State8;
  }/* if ( NvM_GlobalErrorStatus == NVM_REQ_OK ) */

  DBG_NVM_READALL_ASYNC_STATE7_EXIT();
}

STATIC FUNC(void,NVM_CODE) NvM_ReadAll_Async_State8(void)
{
  DBG_NVM_READALL_ASYNC_STATE8_ENTRY();
  /* Set return state of the NvM_ReadAll state machine */
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadAll_Async_State6;
  NvM_GlobalCallLevel++;

  /* Check whether NvM Dynamic Configuration is enabled and block
   * address has changed.
   */
#if ( NVM_NUMBER_OF_RESISTANT_TO_CHANGED_SW_BLOCKS > 0U )
  if ( ( NVM_BD_RESISTANTTOCHANGE_BIT_FALSE(NvM_CurrentBlockDescriptorPtr->blockDesc) ) &&
       ( NVM_CHECK_GLOBAL_GENERIC_STATUS( NVM_GENERIC_DC_MASK ) )
     )
  {
    /* NvM Dynamic Configuration is enabled AND block address has
     * changed. --->
     * Extented runtime preparation. Copy block default data from
     * ROM to RAM using NvM_RestoreBlockDefaults(). Also mark block
     * to be written by next NvM_WriteAll().
     */
    NvM_ForceForWriteAll();
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State0;
  }
  else
#endif /* NVM_NUMBER_OF_RESISTANT_TO_CHANGED_SW_BLOCKS > 0U */
  {
    /* NvM Dynamic Configuration is disabled OR block address if fix
     * --->
     * Normal runtime preparation. Copy data from Non Volatile Memory
     * to RAM using NvM_ReadBlock().
     */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_ReadBlock_Async_State0;
  }
  DBG_NVM_READALL_ASYNC_STATE8_EXIT();
}

#endif /* NVM_NUMBER_OF_SELECT_BLOCK_FOR_READALL_BLOCKS > 0U */

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]============================================*/
