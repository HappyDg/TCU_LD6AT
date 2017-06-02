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
#include <TSMem.h>                /* Autosar Module  Base */
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
#include <NvM_CalcCrc.h> /* Contains extern definitions for unit 'CalcCrc'. */
#include <NvM_StateMachine.h>     /* Contains extern definitions for unit   */
                                  /* 'StateMachine'. It can be included in  */
                                  /* library source code files.             */

#if ( NVM_INCLUDE_RTE == STD_ON )
#include <Rte_NvM.h>           /* Rte type definitions. */
#endif
#if ( NVM_DEV_ERROR_DETECT == STD_ON )
/* !LINKSTO NVM556,1 */
#include <Det.h>               /* API of module Det. */
#endif

/* if any DEM event is switched on, include Dem.h */
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM)
/* !LINKSTO NVM554,1 */
#include <Dem.h>
#endif

/* if single block job status reporting is switched on, include BswM_NvM.h */
#if (NVM_BSWM_BLOCK_STATUS_INFO == STD_ON)
#include <BswM_NvM.h>
#endif

/*==================[macros]================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]========================*/
#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief Copies default data from default ROM block to user RAM block.
 **
 ** \param[in] None
 **/
STATIC FUNC(void,NVM_CODE) NvM_CopyBlockRom2Ram(void);

#define NVM_STOP_SEC_CODE
#include <MemMap.h>
/*==================[external function definitions]=========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

FUNC(Std_ReturnType,NVM_CODE) NvM_ASR40_RestoreBlockDefaults
(
  NvM_BlockIdType                       BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr
)
{
  Std_ReturnType Result = E_NOT_OK;   /* Result of this function        */
  uint16 NumberOfNvPlusRomBlocks;     /* Number of NV Blocks + number of ROM Blocks */
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
  boolean ReportQueueOverflow = FALSE; /* To check queue overflow DEM/DET error reporting */
#endif

  DBG_NVM_ASR40_RESTOREBLOCKDEFAULTS_ENTRY(BlockId, NvM_DestPtr);

/************** ( NVM_DEV_ERROR_DETECT == STD_ON ) *************/
#if ( NVM_DEV_ERROR_DETECT == STD_ON )

  /* Check if Block Id is within valid range */
  if ( ( BlockId < 1U ) || ( BlockId>= NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS ) )
  {
    NVM_DET_REPORT_ERROR( NVM_RESTORE_BLOCK_DEFAULTS_API_ID, NVM_E_PARAM_BLOCK_ID );
  }
  /* Check if module is initialized by NvM_Init() */
  else if ( NVM_CHECK_GLOBAL_GENERIC_STATUS_FALSE( NVM_GENERIC_INIT_FLAG_MASK ) )
  {
    NVM_DET_REPORT_ERROR( NVM_RESTORE_BLOCK_DEFAULTS_API_ID, NVM_E_NOT_INITIALIZED );
  }
  /* Check if an other request for block BlockId is already pending. */
  else if ( NvM_AdminBlockTable[BlockId].NvMResult == NVM_REQ_PENDING )
  {
    NVM_DET_REPORT_ERROR( NVM_RESTORE_BLOCK_DEFAULTS_API_ID, NVM_E_BLOCK_PENDING );
  }
  /* Check if no permanent RAM block is defined and the NvM_DestPtr is equal
   * to NULL.
   */
  else if ( ( NvM_BlockDescriptorTable[BlockId].ramBlockDataAddress == NULL_PTR ) &&
            ( NvM_DestPtr == NULL_PTR )
          )
  {
    /* No Permanent RAM Data Block defined and also there is no
     * Temporary RAM Data Block.
     */
    NVM_DET_REPORT_ERROR( NVM_RESTORE_BLOCK_DEFAULTS_API_ID, NVM_E_PARAM_ADDRESS );
  }
  /* Check if no permanent ROM block and no InitBlockCallback is defined
   */
  else if ( ( NvM_BlockDescriptorTable[BlockId].romBlockDataAddress == NULL_PTR ) &&
            ( NvM_BlockDescriptorTable[BlockId].initBlockCallback == NULL_PTR )
          )
  {
    /* No ROM Block containig default data is defined and no
     * InitBlockCallback function.
     */
    NVM_DET_REPORT_ERROR( NVM_RESTORE_BLOCK_DEFAULTS_API_ID, NVM_E_BLOCK_CONFIG );
  }
  else
#endif /* NVM_DEV_ERROR_DETECT == STD_ON */
  {

    NumberOfNvPlusRomBlocks =
       ( uint16 ) NvM_BlockDescriptorTable[BlockId].romBlockNum
     + ( uint16 ) NvM_BlockDescriptorTable[BlockId].nvBlockNum;
    /* protect concurrent access to the standard queue and dataset index */
    SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();
/* !LINKSTO NVM150,1 */
#if( NVM_NUMBER_OF_DATASET_BLOCKS > 0U )
    /* In case block management type NVM_BLOCK_DATASET
     * NvM_RestoreBockDefaults shall return with E_NOT_OK if at least one
     * ROM block is configured and the data index points at a NV block.
     * NVM353.
     */
    if ( ( NVM_BD_BLOCKMNGTTYPE(NvM_BlockDescriptorTable[BlockId].blockDesc) ==
           NVM_BD_BLOCKMNGTTYPE_DATASET
         ) &&
         ( NvM_BlockDescriptorTable[BlockId].romBlockNum > 0U ) &&
         ( NvM_AdminBlockTable[BlockId].NvMDatasetBlockIndex
              < NvM_BlockDescriptorTable[BlockId].nvBlockNum
         )
         /* Deviation MISRA-1 */
       )
    {
      Result = E_NOT_OK;
    }
    else
#endif /* NVM_NUMBER_OF_DATASET_BLOCKS > 0U */
    {
      /* Additionally check if the Data Index is greater than the number of
       * NVM blocks plus number of ROM blocks.
       */
      if ( NvM_AdminBlockTable[BlockId].NvMDatasetBlockIndex >= NumberOfNvPlusRomBlocks )
      {
        Result = E_NOT_OK;
      }
      else
      {
        if (NvM_AdminBlockTable[BlockId].NvMResult != NVM_REQ_PENDING)
        {
          Result = NvM_Queue_InsertStandard(BlockId, NvM_DestPtr, &NvM_RestoreBlockDefaults_Async);

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
          if (E_OK != Result)
          {
            /* Queue overflow DEM/DET error needs to be reported */
            ReportQueueOverflow = TRUE;
          }
#endif
          if (E_OK == Result)
          {
            /* Insert the API ID into NvM_AdminBlockTable.
             * The information shall be available in case the request has only been queued,
             * but the processing has not been started and a cancel request was issued.
             */
            NvM_AdminBlockTable[BlockId].NvMCurrentServiceId = NVM_RESTORE_BLOCK_DEFAULTS_API_ID;
          }
        }
      }/* if ( ( NvM_BlockDescriptorTable[BlockId].blockDesc  ... */
    }

    SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0();

#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW != TS_PROD_ERR_DISABLE)
  if(ReportQueueOverflow == TRUE)
  {
#if (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DEM)
#if (NVM_QUEUE_OVERFLOW_DEM_EVENT_ID != NVM_INVALID_DEM_EVENTID )
            NVM_DEM_REPORT_ERROR(NVM_QUEUE_OVERFLOW_DEM_EVENT_ID, DEM_EVENT_STATUS_FAILED);
#endif
#elif (NVM_PROD_ERR_HANDLING_QUEUE_OVERFLOW == TS_PROD_ERR_REP_TO_DET)
            NVM_DET_REPORT_ERROR(NVM_RESTORE_BLOCK_DEFAULTS_API_ID, NVM_E_DEMTODET_QUEUE_OVERFLOW);
#endif
  }
#endif

#if (NVM_BSWM_BLOCK_STATUS_INFO == STD_ON)
    /* Check if block status changed and block status reporting to BswM is
     * enabled for this block */
    if ((E_OK == Result) &&
        (NVM_BD_BLOCKSTATUSINFO(NvM_BlockDescriptorTable[BlockId].blockDesc)))
    {
      /* Block status changed due to queuing restore block default
       * request, report the block status to BswM */
      BswM_NvM_CurrentBlockMode(BlockId, NVM_REQ_PENDING);
    }
#endif
  } /* end else */

  DBG_NVM_ASR40_RESTOREBLOCKDEFAULTS_EXIT(Result, BlockId, NvM_DestPtr);

  return Result;

}/* end of function NvM_RestoreBlockDefaults */

FUNC(void,NVM_CODE) NvM_RestoreBlockDefaults_Async(void)
{
  /* Since the processing of NvM_RestoreBlockDefaults() has
   * been started, NvM_CurrentServiceId needs to be set
   */
  NvM_CurrentServiceId = NVM_RESTORE_BLOCK_DEFAULTS_API_ID;

  /* if a permanent RAM block is used then it must be set invalid
   * and unchanged.
   */
  NvM_SetPermanentRamBlockInvalid();
  NvM_SetPermanentRamBlockUnchanged();

  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State0;

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

}/* end of function NvM_RestoreBlockDefaults_Async  */

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

FUNC(void,NVM_CODE) NvM_RestoreBlockDefaults_Async_State0(void)
{
  /* Result of the Init block callback function. */
  Std_ReturnType  InitCallbackResult = E_NOT_OK;

  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE0_ENTRY();

#if (NVM_SYNC_MECHANISM == STD_ON)
  NvM_MirrorRetryCount = 0U;

  if (NVM_BD_USEMIRROR(NvM_CurrentBlockDescriptorPtr->blockDesc))
  {
    NVM_SET_WORKING_STATUS(NVM_DYN_MIRROR_MASK);
  }
#endif

  /* reset Rom Data Loaded Flag */
  NVM_CLEAR_WORKING_STATUS( NVM_DYN_RDL_MASK );
  NvM_CopyBlockRom2Ram();

#if ( NVM_NUMBER_OF_INIT_BLOCK_CALLBACK > 0U )

  /* NOTE: NvM_GlobalErrorStatus is set to NVM_REQ_NOT_OK at the beginning
   *       of NvM_CopyBlockRom2Ram.
   */
  if ( ( NvM_GlobalErrorStatus != NVM_REQ_OK ) &&
       ( NvM_CurrentBlockDescriptorPtr->initBlockCallback != NULL_PTR )
     )
  {
    /* ROM data could not be copied successfully but a user init callback
     * function is defined --> invoke it
     * If the default data are copied successfully the job result shall
     * be set to NVM_REQ_OK. NVM354.
     */
    InitCallbackResult = NvM_CurrentBlockDescriptorPtr->initBlockCallback();
  }

#endif /* NVM_NUMBER_OF_INIT_BLOCK_CALLBACK > 0U */

  if ( ( NvM_GlobalErrorStatus == NVM_REQ_OK ) ||
       ( InitCallbackResult == E_OK )
     )
  {
    /* NvM_GlobalErrorStatus must be set to NVM_REQ_RESTORED_FROM_ROM because in case the
     * InitBlockCallback() was called successfully it is still set to
     * NVM_REQ_NOT_OK.
     */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_RESTORED_FROM_ROM));
    NvM_GlobalErrorStatus = NVM_REQ_RESTORED_FROM_ROM;
    /* Default data could be copied successfully. */
    if ( NVM_BD_CALCRAMBLOCKCRC(NvM_CurrentBlockDescriptorPtr->blockDesc) )
    {
      /* CRC must be calculated */
      NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State1;
    }
    else
    {
    /* CRC must not be calculated */
    NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State3;
    }
  }/* if ( NvM_GlobalErrorStatus == NVM_REQ_OK ) */
  else
  {
    NvM_StateMachine_TerminateCurrentLevel();
  }/* end of else-if ( NvM_GlobalErrorStatus == NVM_REQ_OK ) */


  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE0_EXIT();
}/* end of function NvM_RestoreBlockDefaults_Async_State0  */

FUNC(void,NVM_CODE) NvM_RestoreBlockDefaults_Async_State1(void)
{

  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE1_ENTRY();
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State2;
  /* NOTE: NvM_GlobalCallLevel must not be incremented here, it's done in
   *       NvM_CalculateCrc()
   */
  NvM_CalculateCrc( NvM_GetUserRamBlockAddress() );


  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE1_EXIT();
}/* end of NvM_RestoreBlockDefaults_Async_State1 */

FUNC(void,NVM_CODE) NvM_RestoreBlockDefaults_Async_State2(void)
{

  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE2_ENTRY();
  NvM_CurrentFunctionPtr[NvM_GlobalCallLevel] = &NvM_RestoreBlockDefaults_Async_State3;

  /* Copy calculated CRC from CRC to User Buffer */
  NvM_CopyCrc( NvM_GetStoredRamCRCAddress());


  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE2_EXIT();
}/* end of function NvM_RestoreBlockDefaults_Async_State2 */

FUNC(void,NVM_CODE) NvM_RestoreBlockDefaults_Async_State3(void)
{
#if (NVM_SYNC_MECHANISM == STD_ON)
  Std_ReturnType ReturnVal = E_OK;
#endif

  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE3_ENTRY();

  #if (NVM_SYNC_MECHANISM == STD_ON)
  /* Call the callback function to copy data from NvM module's mirror to RAM block */
  if (NVM_CHECK_WORKING_STATUS(NVM_DYN_MIRROR_MASK))
  {
    ReturnVal = NvM_MirrorCopy(NvM_CurrentBlockDescriptorPtr->readRamFromNvCallback, NULL_PTR,
      NVM_GET_MIRROR_ADDR());
  }

  if (E_OK == ReturnVal)
#endif
  {
    /* set ROM data loaded flag */
    NVM_SET_WORKING_STATUS( NVM_DYN_RDL_MASK );

    /* Default data was copied successfully from ROM to RAM. Set permanent
     * RAM Block valid and changed. NVM366,NVM228,NVM367.
     */
    NvM_SetPermanentRamBlockValid();
    NvM_SetPermanentRamBlockChanged();

    NvM_StateMachine_TerminateCurrentLevel();
  }

  DBG_NVM_RESTOREBLOCKDEFAULTS_ASYNC_STATE3_EXIT();
}/* NvM_RestoreBlockDefaults_Async_State3 */

/*==================[internal function definitions]=========================*/

STATIC FUNC(void,NVM_CODE) NvM_CopyBlockRom2Ram(void)
{
  uint8  NvMDatasetBlockIndex = 0U;
  /* Number of NVM Blocks plus number of ROM Blocks of current block. */
  uint16 NumberOfNvPlusRomBlocks = 0U;
  /* CurrentRamAddress: address of the target user RAM data buffer */
  P2VAR( uint8,AUTOMATIC,NVM_APPL_DATA ) CurrentRamAddress =
  NvM_GetUserRamBlockAddress();

  P2CONST(uint8,AUTOMATIC,NVM_APPL_CONST) CurrentRomAddress
    = NvM_CurrentBlockDescriptorPtr->romBlockDataAddress;
/* !LINKSTO NVM150,1 */
  DBG_NVM_COPYBLOCKROM2RAM_ENTRY();

#if ( NVM_NUMBER_OF_DATASET_BLOCKS > 0U )
  if ( NVM_BD_BLOCKMNGTTYPE(NvM_CurrentBlockDescriptorPtr->blockDesc) ==
       NVM_BD_BLOCKMNGTTYPE_DATASET
     )
  {
    /* A Dataset Block uses the ROM Block specified by the current
     * value of the Data Index.
     */
    NvMDatasetBlockIndex = NvM_AdminBlockTable[NvM_GlobalBlockNumber].NvMDatasetBlockIndex;
  }
  else
#endif /* NVM_NUMBER_OF_DATASET_BLOCKS > 0U */
  {
    /* NvM_RestoreBlockDefaults() always uses the first ROM data block */
    NvMDatasetBlockIndex = NvM_CurrentBlockDescriptorPtr->nvBlockNum;
  }


  DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_NOT_OK));
  NvM_GlobalErrorStatus = NVM_REQ_NOT_OK;

  NumberOfNvPlusRomBlocks =
     ( uint16 ) NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].romBlockNum
   + ( uint16 ) NvM_BlockDescriptorTable[NvM_GlobalBlockNumber].nvBlockNum;

  /* In case the Data Index does not specify a valid ROM Block default data
   * must not be copied. NVM355.
   */
  if ( ( CurrentRomAddress != NULL_PTR ) &&
       ( NvMDatasetBlockIndex >= NvM_CurrentBlockDescriptorPtr->nvBlockNum ) &&
       ( NvMDatasetBlockIndex < NumberOfNvPlusRomBlocks )
       /* Deviation MISRA-1 */
     )
  {
    /* CurrentRomAddress: address of the source ROM data buffer which
     * contains the default data.
     * It must be calculated from the basic Rom block data address plus the
     * offset of the current dataset indicated by parameter
     * NvMDatasetBlockIndex.
     */
    CurrentRomAddress =
      &( CurrentRomAddress[ NvM_CurrentBlockDescriptorPtr->nvBlockLength
                        *((uint16)NvMDatasetBlockIndex - NvM_CurrentBlockDescriptorPtr->nvBlockNum )
                          ]
       );

    TS_MemCpy( CurrentRamAddress,
               CurrentRomAddress,
               NvM_CurrentBlockDescriptorPtr->nvBlockLength
             );

    /* If the default data are copied successfully the job result shall
     * be set to NVM_REQ_OK. NVM354.
     */

    DBG_NVM_GLOBALERRORSTATUS((NvM_GlobalErrorStatus),(NVM_REQ_OK));
    NvM_GlobalErrorStatus = NVM_REQ_OK;

  }/* end of if ( ... ) */


  DBG_NVM_COPYBLOCKROM2RAM_EXIT();
}/* end of function NvM_CopyBlockRom2Ram  */

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
