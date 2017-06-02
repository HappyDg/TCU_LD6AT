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
#if ( !defined NVM_DATA_INTERN_H )
#define NVM_DATA_INTERN_H
/*==================[inclusions]============================================*/
#include <TSAutosar.h>            /* AUTOSAR standard types                 */
#include <NvM_Int_Types.h>        /* NvM specific internal types            */
#include <NvM_Cfg.h>              /* Contains generated configuration       */
                                  /* data.                                  */

/*==================[macros]================================================*/

/*------------------[the NvM Instance Id]---------------------------------*/

#if(defined NVM_INSTANCE_ID)
#error NVM_INSTANCE_ID is already defined
#endif
/** \brief Defines the instance number of this NVRAM manager.
 **        Since multiple instances of a NVRAM manager are not supported
 **        the Instance Id is always zero.
 **/
#define NVM_INSTANCE_ID     0x00U




/*------------------------[Defensive programming]----------------------------*/

#if (defined NVM_PRECONDITION_ASSERT)
#error NVM_PRECONDITION_ASSERT is already defined
#endif
#if (NVM_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define NVM_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_PRECONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined NVM_POSTCONDITION_ASSERT)
#error NVM_POSTCONDITION_ASSERT is already defined
#endif
#if (NVM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define NVM_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_POSTCONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined NVM_INVARIANT_ASSERT)
#error NVM_INVARIANT_ASSERT is already defined
#endif
#if (NVM_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define NVM_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_INVARIANT_ASSERT(Condition, ApiId)
#endif

#if (defined NVM_STATIC_ASSERT)
# error NVM_STATIC_ASSERT is already defined
#endif
#if (NVM_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define NVM_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define NVM_STATIC_ASSERT(expr)
#endif

#if (defined NVM_UNREACHABLE_CODE_ASSERT)
#error NVM_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (NVM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **
 ** \param[in] ApiId Service ID of the API function */
#define NVM_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId))
#else
#define NVM_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined NVM_INTERNAL_API_ID)
#error NVM_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define NVM_INTERNAL_API_ID DET_INTERNAL_API_ID


/* \brief Report development error if DET is enabled
 */

#if ( NVM_DEV_ERROR_DETECT == STD_ON )
#define NVM_DET_REPORT_ERROR( ApiId,ErrorId )    \
    (void)Det_ReportError( NVM_MODULE_ID, NVM_INSTANCE_ID, ( ApiId ), ( ErrorId ) )
#else
#define NVM_DET_REPORT_ERROR( ApiId,ErrorId )
#endif

/** \brief Reports production error for a configured Dem event Id
 *
 *  \param[in] Dem Event Id
 *  \param[in] Dem Event Status
 */
#define NVM_DEM_REPORT_ERROR(EventId, EventStatus) \
  (void)Dem_ReportErrorStatus((EventId), (EventStatus))

#define NVM_INVERT_DATAINDEX(Index) (((Index) == 0U) ? (1U) : (0U))

/** \brief offset of CRC bits in the bit pattern */
#define NVM_BD_CRCTYPE_OFFSET        0U

/** \brief NVM_BD_CRCTYPE: extracts the CRC type from the given
 **                              bit pattern
 ** \param[in]   value : bit pattern from which the CRC type has
 **                         to be extracated
 **/
#define NVM_BD_CRCTYPE(value) (((uint8)((value) >> NVM_BD_CRCTYPE_OFFSET)) & 0x07U)

/** \brief No CRC */
#define NVM_BD_CRCTYPE_NONE          0U

/** \brief 8 bit CRC */
#define NVM_BD_CRCTYPE_CRC8          1U

/** \brief 16 bit CRC */
#define NVM_BD_CRCTYPE_CRC16         2U

/** \brief 32 bit CRC */
#define NVM_BD_CRCTYPE_CRC32         3U

/** \brief mask for RAM block CRC bit */
#define NVM_BD_CALCRAMBLOCKCRC_BIT 0x08U

/** \brief NVM_BD_CALCRAMBLOCKCRC: Check whether the RAM block CRC is present.
 **
 ** \param[in]  value : bit pattern from which the RAM block CRC
 **                         is present status is extracted
 **/
#define NVM_BD_CALCRAMBLOCKCRC(value) (((value) & NVM_BD_CALCRAMBLOCKCRC_BIT) != 0U)

/** \brief mask for Write block protection bit */
#define NVM_BD_WRITEBLOCKPROTECTION_BIT 0x10U

/** \brief NVM_BD_WRITEBLOCKPROTECTION: Check whether the write block protection is enabled
 **
 ** \param[in]  value : bit pattern from which the write block protection
 **                         status is extracted
 **/
#define NVM_BD_WRITEBLOCKPROTECTION(value) (((value) & NVM_BD_WRITEBLOCKPROTECTION_BIT) != 0U)

/** \brief mask for Write once bit */
#define NVM_BD_WRITEONCE_BIT 0x20U

/** \brief NVM_BD_WRITEONCE: Check whether the write block once is enabled
 **
 ** \param[in]  value : bit pattern from which the write block once
 **                         status is extracted
 **/
#define NVM_BD_WRITEONCE(value) (((value) & NVM_BD_WRITEONCE_BIT) != 0U)

/** \brief mask for Resistant to change bit */
#define NVM_BD_RESISTANTTOCHANGE_BIT 0x40U

/** \brief NVM_BD_RESISTANTTOCHANGE_BIT_FALSE: Check whether the write block once is disabled
 **
 ** \param[in]  value : bit pattern from which the resistant to change
 **                         status is extracted
 **/
#define NVM_BD_RESISTANTTOCHANGE_BIT_FALSE(value) (((value) & NVM_BD_RESISTANTTOCHANGE_BIT) == 0U)

/** \brief offset of block management type bits in the bit pattern */
#define NVM_BD_BLOCKMNGTTYPE_OFFSET 7U

/** \brief NVM_BD_BLOCKMNGTTYPE: extracts the block management type from the given
 **                              bit pattern
 ** \param[in]  value : bit pattern from which the block management type has
 **                         to be extracated
 **/
#define NVM_BD_BLOCKMNGTTYPE(value) (((uint8)((value) >> NVM_BD_BLOCKMNGTTYPE_OFFSET)) & 0x03U)

/**  \brief Native Block */
#define NVM_BD_BLOCKMNGTTYPE_NATIVE    0U

/**  \brief Redundant Block */
#define NVM_BD_BLOCKMNGTTYPE_REDUNDANT 1U

/**  \brief Dataset Block */
#define NVM_BD_BLOCKMNGTTYPE_DATASET   2U

/** \brief mask for Read all bit */
#define NVM_BD_READALL_BIT 0x0200U

/** \brief NVM_BD_READALL: Check whether the read all is enabled
 **
 ** \param[in]  value : bit pattern from which the read all
 **                         status is extracted
 **/
#define NVM_BD_READALL(value) (((value) & NVM_BD_READALL_BIT) != 0U)

/** \brief offset of block management type bits in the bit pattern */
#define NVM_BD_DEVICEID_OFFSET 10U

/** \brief NVM_BD_BLOCKMNGTTYPE: extracts the device ID from the given
 **                              bit pattern
 ** \param[in]  value : bit pattern from which the device ID has
 **                         to be extracated
 **/
#define NVM_BD_DEVICEID(value) (((uint8)((value) >> NVM_BD_DEVICEID_OFFSET)) & 0x07U)

/** \brief mask for 'Use internal buffer' bit */
#define NVM_BD_USEINTERNALBUFFER_BIT 0x2000U

/** \brief NVM_BD_USEINTERNALBUFFER: Check whether the usage of internal buffer is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Use internal buffer'
 **                         status is extracted
 **/
#define NVM_BD_USEINTERNALBUFFER(value) (((value) & NVM_BD_USEINTERNALBUFFER_BIT) != 0U)

/** \brief mask for 'Nvm Advanced Recovery' bit */
#define NVM_BD_ADVANCED_RECOVERY_BIT 0x4000U

/** \brief NVM_BD_ADVANCED_RECOVERY: Check whether 'Advanced Recovery' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Advanced Recovery'
 **                     status is extracted
 **/
#define NVM_BD_ADVANCED_RECOVERY(value) (((value) & NVM_BD_ADVANCED_RECOVERY_BIT) != 0U)

/** \brief mask for 'NvM Write Verification' bit */
#define NVM_BD_WRITE_VERIFICATION_BIT 0x8000U

/** \brief NVM_BD_WRITE_VERIFICATION: Check whether 'Write Verification' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Write Verification'
 **                     status is extracted
 **/
#define NVM_BD_WRITE_VERIFICATION(value) (((value) & NVM_BD_WRITE_VERIFICATION_BIT) != 0U)

/** \brief mask for 'Static Block Id' bit */
#define NVM_BD_STATICBLOCKID_BIT 0x10000U

/** \brief NVM_BD_USESTATICBLOCKID: Check whether 'Static Block Id' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Static Block Id'
 **                     status is extracted
 **/
#define NVM_BD_USESTATICBLOCKID(value) (((value) & NVM_BD_STATICBLOCKID_BIT) != 0U)

/** \brief mask for 'Use Mirror' bit */
#define NVM_BD_USEMIRROR_BIT 0x20000U

/** \brief NVM_BD_USEMIRROR: Check whether 'Use Mirror' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'Use Mirror'
 **                     status is extracted
 **/
#define NVM_BD_USEMIRROR(value) (((value) & NVM_BD_USEMIRROR_BIT) != 0U)

/** \brief mask for 'WriteAll enabled' bit */
#define NVM_BD_WRITEALL_BIT 0x40000U

/** \brief NVM_BD_WRITEALL: Check whether 'WriteAll' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'WriteAll enable'
 **                     status is extracted
 **/
#define NVM_BD_WRITEALL(value) (((value) & NVM_BD_WRITEALL_BIT) != 0U)

/** \brief mask for 'BlockStatusInfo' enabled bit */
#define NVM_BD_BLOCKSTATUSINFO_BIT  0x80000U

/** \brief NVM_BD_BLOCKSTATUSINFO: Check whether 'BlockStatusInfo' is enabled
 **
 ** \param[in]  value : bit pattern from which the 'BlockStatusInfo'
 **                     status is extracted
 **/
#define NVM_BD_BLOCKSTATUSINFO(value) (((value) & NVM_BD_BLOCKSTATUSINFO_BIT) != 0U)

/** \brief mask for 'UserProvidesSpaceForBlockAndCrc' enabled bit */
#define NVM_BD_USERPROVIDESSPACEFORCRC_BIT  0x100000U

/** \brief NVM_BD_USERPROVIDESSPACEFORCRC: Check whether 'NvMUserProvidesSpaceForBlockAndCrc' 
 ** is enabled
 **
 ** \param[in]  value : bit pattern from which the 'NvMUserProvidesSpaceForBlockAndCrc'
 **                     status is extracted
 **/
#define NVM_BD_USERPROVIDESSPACEFORCRC(value) (((value) & NVM_BD_USERPROVIDESSPACEFORCRC_BIT) != 0U)

/************** Bit definitions of the dynamic status variable  *************/

/** \brief Macro to extract the ChangeFlag flag
 **        from bit 0 of NvM_DynamicStatusType
 **
 **        value 0: RAM data has not been changed during read
 **        value 1: RAM data has been changed during read
 **/
#define NVM_DYN_CHANGE_MASK                0x0001U

/** \brief Macro to extract the WriteProtectionFlag
 **        from bit 1 of NvM_DynamicStatusType
 **
 **        value 0: block is not write protected
 **        value 1: block is write protected
 **/
#define NVM_DYN_WPF_MASK                   0x0002U

/** \brief Macro to extract the BlockReadValidErrorFlag
 **        from bit 2 of NvM_DynamicStatusType
 **
 **        value 0: The NVM Block is valid
 **        value 1: The NVM Block is invalidated
 **/
#define NVM_DYN_BRVE_MASK                  0x0004U

/** \brief Macro to extract the 'Block Locked' Flag
 **        from bit 3 of NvM_DynamicStatusType
 **
 **        value 0: The RAM block is marked as unlocked.
 **        value 1: The RAM block is marked as locked.
 **/
#define NVM_DYN_LOCK_MASK                  0x0008U

/** \brief Macro to extract the RomDataLoadedFlag
 **        from bit 4 of NvM_DynamicStatusType
 **
 **        value 0: ROM data was not loaded by NvM_RestorBlockDefaults.
 **        value 1: ROM data loaded by NvM_RestorBlockDefaults.
 **/
#define NVM_DYN_RDL_MASK                   0x0010U

/** \brief Macro to extract the WriteProtectionPermanentFlag
 **        from bit 5 of NvM_DynamicStatusType
 **
 **        value 0: permanent write protection disabled.
 **        value 1: permanent write protection enabled.
 **/
#define NVM_DYN_WPPF_MASK                  0x0020U

/** \brief Macro to extract the ExtentedRuntimeBlockFlag
 **        from bit 6 of NvM_DynamicStatusType
 **
 **        value 0: block address not changed in case Dynamic Configuration is enabled
 **        value 1: block address is changed in case Dynamic Configuration is enabled
 **/
#define NVM_ERBF_MASK                      0x0040U

/** \brief Macro to extract the 'Loss of Redundancy' Flag
 **        from bit 7 of NvM_DynamicStatusType
 **
 **        value 0: Loss of Redundancy.
 **        value 1: No Loss of Redundancy.
 **/
#define NVM_DYN_REDUNDANCY_MASK                 0x0080U

/** \brief Macro to extract the CrcCheckedUnequalFlag
 **        from bit 8 of NvM_DynamicStatusType
 **
 **        value 0: CRC match
 **        value 1: CRC mismatch
 **/
#define NVM_DYN_CCU_MASK                   0x0100U


/** \brief Macro to extract the UsePermanentRamBlock
 **        from bit 9 of NvM_DynamicStatusType
 **
 **        value 0: Current service uses the Permanent RAM Block
 **        value 1: Current service uses the Temporary RAM Block.
 **/
#define NVM_DYN_UPRB_MASK                  0x0200U

/** \brief Macro to extract the BlockReadBlockInconsistentFlag
 **        from bit 10 of NvM_DynamicStatusType
 **
 **        value 0: MemIf job result is unequal to MEMIF_BLOCK_INCONSISTENT
 **        value 1: MemIf job result is equal to MEMIF_BLOCK_INCONSISTENT
 **/
#define NVM_DYN_BRBI_MASK                  0x0400U

/** \brief Macro to extract the WrongBlockIdFlag
 **        from bit 11 of NvM_DynamicStatusType
 **
 **        value 0: Static Block Id check has been successful
 **        value 1: Static Block Id check has failed
 **/
#define NVM_DYN_WBID_MASK                  0x0800U

/** \brief Macro to extract the 'Use Mirror' Flag
 **        from bit 12 of NvM_DynamicStatusType
 **
 **        value 0: User RAM block or Internal buffer shall be used.
 **        value 1: NvM Mirror shall be used to read and write data.
 **/
#define NVM_DYN_MIRROR_MASK                0x1000U


/** \brief Macro to extract the SetRamBlockStatusChangedFlag
 **        from bit 13 of NvM_DynamicStatusType
 **
 **        value 0: SetRamBlockStatus was not called or it was called with
 **                 BlockChanged=FALSE
 **        value 1: SetRamBlockStatus was called with BlockChanged=TRUE
 **
 ** Note: SetRamBlockStatusChangedFlag is merely set and cleared.
 ** The value of this flag is not evaluated within the code.
 ** This status information might be useful for integration and debugging.
 **/
#define NVM_DYN_SRBSC_MASK            0x2000U


/************** Bit definitions of NvMExtendedStatus *************************/

/** \brief Macro to extract bit 0 of NvMExtendedStatus which indicates whether
 **        block data could be recovered from redundant block or ROM block.
 **        value 0: Block could not be recovered
 **        value 1: Block could be recovered from redundant or ROM block.
 **/
#define NVM_ES_ADVANCED_RECOVERY_MASK        0x01U

/** \brief Macro to extract bit 1 of NvMExtendedStatus which indicates whether
 **        RAM block CRC shall be calculated.
 **        value 0: RAM Block CRC could not be calculated
 **        value 1: RAM Block CRC could be calculated.
 **/
#define NVM_ES_RAM_BLOCK_CRC_CALC_MASK        0x02U

/** \brief Macro to extract bit 1 of NvMExtendedStatus which indicates whether
 **        Native block or redundant block contains invalid data.
 **        value 0: Native block is corrupt
 **        value 1: Redundant block is corrupt
 **/
#define NVM_ES_REDUNDANT_ERROR_MASK          0x04U

/************** Bit definitions of the global generic status byte ***********/

/** \brief Init flag
 **        Macro to extract bit 0 of NvM_GlobalGenericStatus
 **        Indicates whether NvM module has been initialized
 **        value 0: NvM not initialized
 **        value 1: NvM initialized
 **/
#define NVM_GENERIC_INIT_FLAG_MASK           0x01U

/** \brief Cancel Write All flag
 **        Macro to extract bit 1 of NvM_GlobalGenericStatus
 **        Indicates whether NvM_CancelWriteAll was called
 **        value 0: NvM_WriteAll() must NOT be cancelled
 **        value 1: NvM_WriteAll() must be cancelled
 **/
#define NVM_GENERIC_CWA_MASK                 0x02U

/** \brief Main Function Processing flag
 **        Macro to extract bit 2 of NvM_GlobalGenericStatus
 **        Indicates whether main function is being processed
 **        value 0: NvM_Mainfunction is currently not running
 **        value 1: NvM_Mainfunction is currently running
 **/
#define NVM_GENERIC_MFP_MASK                 0x04U

/** \brief Polling Mode Ignore flag
 **        Macro to extract bit 3 of NvM_GlobalGenericStatus
 **        Indicates whether polling mode is enabled
 **        value 0: Polling Mode enabled  --> not ignored
 **        value 1: Polling Mode disabled --> ignore
 **/
#define NVM_GENERIC_DPM_MASK                 0x08U

/** \brief Dynamic Cofiguration flag
 **        Macro to extract bit 4 of NvM_GlobalGenericStatus
 **        Indicates whether dynamic configuration must be applied
 **        value 0: Dynamic Configuration must NOT be applied by ReadAll
 **        value 1: Dynamic Configuration must be applied by ReadAll
 **/
#define NVM_GENERIC_DC_MASK                  0x10U

/** \brief Multi Request Keep Job Pending flag
 **        Macro to extract bit 5 of NvM_GlobalGenericStatus
 **        Indicates whether the single block request must be kept pending
 **        value 0: A multi block request must set the ErrorStatus to
 **                 NvM_GlobalErrorStatus after a single block
 **                 was processed.
 **        value 1: A multi block request must keep the value of ErrorStatus
 **                 by NVM_REQ_PENDING after a single block was processed.
 **                 was processed. This happens in case a single block
 **                 request was inserted into the queue while a multi block
 **                 request is processing.
 **/
#define NVM_GENERIC_MRKJP_MASK               0x20U

/** \brief Block request Canceled Flag
 **        Macro to extract bit 6 of NvM_GlobalGenericStatus
 **        Indicates that during a multi-block request, a single block request
 **        for the same block is present in the queue, but it must be canceled.
 **        Therefore, after the block was processed by NvM_WriteAll() or NvM_ReadAll()
 **        the ErrorStatus must remain NVM_REQ_CANCELED.
 **/
#define NVM_GENERIC_CANCEL_MASK              0x40U

/******************  Miscellaneous macros  **********************************/

/** \brief Defines the variable which is used to store the interim result of
 **        a multi block request. The location
 **        NvM_AdminBlockTable[0].NvMDatasetBlockIndex can be used for this
 **        purpose because for block the block type is obsolete and not used.
 **/
#define NVM_REQUEST_INTERIM_RESULT \
        NvM_AdminBlockTable[0].NvMDatasetBlockIndex

/** \brief Defines the variable which is used to store
 **        the interim result of a redundant block request.
 **        The location NvM_AdminBlockTable[0].NvMValid can be used for this
 **        purpose because for block 0 the block validattion is obsolete and
 **        not used.
 **/
#define NVM_REDUNDANT_ERROR_COUNTER \
        NvM_AdminBlockTable[0].NvMValid

/** \brief Masks the 32Bit CRC type used by a block.
 **/
#define NVM_BLOCK_USE_32BITCRC_MASK          0x05U

/** \brief Masks the 16Bit CRC type used by a block.
 **/
#define NVM_BLOCK_USE_16BITCRC_MASK          0x01U

/** \brief Defines the length of the Static Block Id.
 **/
#define NVM_BLOCKID_LENGTH                   0x02U

/******************** API IDs ***********************************************/

/** \brief Defines API id of function NvM_SetDataIndex().
 **/
#define NVM_SET_DATA_INDEX_API_ID            0x01U

/** \brief Defines API id of function NvM_GetDataIndex().
 **/
#define NVM_GET_DATA_INDEX_API_ID             0x02U

/** \brief Defines API id of function NvM_SetBlockProtection().
 **/
#define NVM_SET_BLOCK_PROTECTION_API_ID       0x03U

/** \brief Defines API id of function NvM_GetErrorStatus().
 **/
#define NVM_GET_ERROR_STATUS_API_ID           0x04U

/** \brief Defines API id of function NvM_SetRamBlockStatus().
 **/
#define NVM_SET_RAM_BLOCK_STATUS_API_ID       0x05U

/** \brief Defines API id of function NvM_ReadBlock().
 **/
#define NVM_READ_BLOCK_API_ID                 0x06U

/** \brief Defines API id of function NvM_WriteBlock().
 **/
#define NVM_WRITE_BLOCK_API_ID                0x07U

/** \brief Defines API id of function NvM_RestoreBlockDefaults().
 **/
#define NVM_RESTORE_BLOCK_DEFAULTS_API_ID     0x08U

/** \brief Defines API id of function NvM_EraseNvBlock().
 **/
#define NVM_ERASE_NV_BLOCK_API_ID             0x09U

/** \brief Defines API id of function NvM_CancelWriteAll().
 **/
#define NVM_CANCEL_WRITE_ALL_API_ID           0x0AU

/** \brief Defines API id of function NvM_InvalidateNvBlock().
 **/
#define NVM_INVALIDATE_NV_BLOCK_API_ID        0x0BU

/** \brief Defines API id of function NvM_ReadAll().
 **/
#define NVM_READ_ALL_API_ID                   0x0CU

/** \brief Defines API id of function NvM_WriteAll().
 **/
#define NVM_WRITE_ALL_API_ID                  0x0DU

/** \brief Defines API id of function NvM_GetVersionInfo().
 **/
#define NVM_GET_VERSION_INFO_API_ID           0x0FU

/** \brief Defines API id of function NvM_CancelJobs().
 **/
#define NVM_CANCEL_JOBS_API_ID                0x10U

/** \brief Defines API id of function NvM_SetBlockLockStatus().
 **/
#define NVM_SET_BLOCK_LOCK_STATUS_API_ID      0x13U

/** \brief Defines id of function check for ram block size.
 **/
#define NVM_CHECK_RAM_BLOCK_SIZES            0x80U

/** \brief Defines id of function check for rom block size.
 **/
#define NVM_CHECK_ROM_BLOCK_SIZES            0x81U

/** \brief Defines API id in case no service is currently processed.
 **/
#define NVM_NO_API_ID                        0xFFU

/** \brief Defines the total number of implemented asynchronous API
 **        functions.
 **/
#define NVM_NUMBER_OF_ASYNC_FUNCTIONS        6U

/** \brief Defines the total number of NvM API functions.
 **/
#define NVM_NUMBER_OF_FUNCTIONS             15U

/************************  Block 0, Block 1 and Block 2 IDs *****************/

/** \brief Defines the block ID of block 0 used to manage multi block
 **        requests.
 **/
#define NVM_MULTI_REQUEST_BLOCK_0_ID   0U

/** \brief Defines the block ID of the block 1 used to store the
 **        configuration ID.
 **/
#define NVM_BLOCK_CONFIG_ID            1U

/** \brief Defines the block ID of the first user block. The blocks 0 and 1
 **        are reserved for NvM internal management.
 **/
#define NVM_FIRST_USER_BLOCK_2_ID      2U


/** \brief Defines "immediate priority" of blocks. blocks with priority "0"
 **        are considered "immediate priority" blocks and are given
 **        precedence compared to blocks with "standard prioriry" ( priority > 0 )
 **        while proessing requests.
 **/
#define NVM_BLOCK_IMMEDIATE_PRIORITY   0U

/** \brief Defines "Queue Empty" condition of standard and immediate queues.
 **        Queue index is initialized to this value.
 **        When the first request is inserted into the queue, this value is reset to 0
 **        and is incremented thereafter for each enqueued requests.
 **/
#define NVM_QUEUE_INDEX_RESET   0xFFU

#if (NVM_INTERNAL_BUFFER_SIZE != 0U)
/** \brief Returns address of NVM internal buffer for temporary block data/crc storage.
 ** \return Starting address of NVM internal buffer
 **/
#define NVM_GET_INTERNAL_BUFFER() ((NvM_PtrToApplDataType)NvM_InternalBuffer)

/** \brief Returns address in the NVM internal buffer for static block id storage.
 ** \return Address in NVM internal buffer where static block id is stored.
 **/
#define NVM_BLOCKID_BUFADDR() ((NvM_PtrToApplDataType)(&NvM_InternalBuffer[NVM_BLOCKID_LENGTH]))
#endif

#if (NVM_MIRROR_SIZE != 0U)
/** \brief Returns address of NVM Mirror when explicit synchronization is enabled.
 ** \return Starting address of NVM Mirror
 **/
#define NVM_GET_MIRROR_ADDR() NVM_GET_INTERNAL_BUFFER()
#endif

/** \brief Returns the address of the static block id for the current block.
 ** \return Address of the static block id for the current block.
 **/
#define NVM_STATIC_BLOCKID()  ((NvM_PtrToVarType)&NvM_GlobalBlockNumber)

/** \brief Checks if the standard job processing queue is empty.
 ** \return Empty status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_EMPTY() \
  ( NvM_Queue_IndexStandard == NVM_QUEUE_INDEX_RESET )

/** \brief Checks if the immediate job processing queue is empty.
 ** \return Empty status of the immediate job processing queue
 **/
#define NVM_IMMEDIATE_QUEUE_EMPTY() \
  ( NvM_Queue_CountImmediate == 0U )

/** \brief Checks if the standard job processing queue is NOT empty.
 ** \return Not-empty status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_NOT_EMPTY() \
  ( NvM_Queue_IndexStandard != NVM_QUEUE_INDEX_RESET )

/** \brief Checks if the immediate job processing queue is NOT empty.
 ** \return Not-empty status of the immediate job processing queue
 **/
#define NVM_IMMEDIATE_QUEUE_NOT_EMPTY() \
  ( NvM_Queue_CountImmediate != 0 )

/** \brief Checks if the standard job processing queue is NOT full.
 **        (not including the reserved entry for for multiblock requests).
 ** \return Not-full status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_NOT_FULL() \
  ( NvM_Queue_IndexStandard < ( NVM_SIZE_STANDARD_JOB_QUEUE - 2U ) )

/** \brief Checks if the standard job processing queue is NOT full
 **        (including the reserved entry for for multiblock requests).
 ** \return Not-full status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_NOT_FULL_MULTI() \
  ( NvM_Queue_IndexStandard < ( NVM_SIZE_STANDARD_JOB_QUEUE - 1U ) )

/** \brief Checks if the immediate job processing queue is NOT full.
 ** \return Not-full status of the immediate job processing queue
 **/
#define NVM_IMMEDIATE_QUEUE_NOT_FULL() \
  ( NvM_Queue_CountImmediate < NVM_SIZE_IMMEDIATE_JOB_QUEUE )

/** \brief Checks if the immediate job processing queue contains
 **        more than one request.
 ** \return Multiple-requests status of the immediate job processing queue
 **/
#define NVM_IMMEDIATE_QUEUE_MULTIPLE_JOBS() (NvM_Queue_CountImmediate > 1U)

/** \brief Checks if the standard job processing queue contains
 **        more than one request.
 ** \return Multiple-requests status of the standard job processing queue
 **/
#define NVM_STD_QUEUE_MULTIPLE_JOBS() (NVM_STD_QUEUE_NOT_EMPTY() && (NvM_Queue_IndexStandard > 0U))

/** \brief Represents the Block Identifier of the immediate request
 **        to be or currently being processed.
 **/
#define NVM_IMMEDIATE_QUEUE_BLOCKID \
  ( NvM_Queue_Immediate[NvM_Queue_IndexImmediate].NvMBlockIdentifier )

/** \brief Represents the Block Identifier of the standard request
 **        to be or currently being processed.
 **/
#define NVM_STD_QUEUE_BLOCKID \
  (NvM_Queue_Standard[NvM_Queue_IndexStandard].NvMBlockIdentifier)

/** \brief Advance the Immediate Queue by one after inserting a new element
 **
 **        The macro increments the value of Immediate Queue Count by 1
 **        after a new job request is queued in the Queue.
 **/
#define NVM_IMMEDIATE_QUEUE_UP()                                         \
  do                                                                     \
  {                                                                      \
    NvM_Queue_CountImmediate++;                                          \
  } while (0)

/** \brief Remove an element from the Immediate Queue
 **
 **        The macro circularly increments the value of Immediate Queue Front by 1
 **        and decreases Immediate Queue Count by 1 so that the job request
 **        at Immediate Queue Front is removed from the queue.
 **/
#define NVM_IMMEDIATE_QUEUE_DOWN()                                                              \
  do                                                                                            \
  {                                                                                             \
    NvM_Queue_IndexImmediate = (NvM_Queue_IndexImmediate + 1U) % NVM_SIZE_IMMEDIATE_JOB_QUEUE;  \
    NvM_Queue_CountImmediate--;                                                                 \
  } while (0)

/** \brief Returns the index of the element passed as argument (x)
 **        from the immediate queue, wrapped around the queue size
 **/
#define NVM_IMMEDIATE_QUEUE_GET_INDEX_MOD_SIZE(x)  ((x) % NVM_SIZE_IMMEDIATE_JOB_QUEUE)

/** \brief Advance the Standard Queue by one position
 **
 **        The macro increments the value of Standard Queue Index by 1
 **        so that a new job request can be queued in the Index position.
 **        In case of Index is uninitialized(0xFF), it is set to 0.
 **/
#define NVM_STANDARD_QUEUE_UP()                                          \
  do                                                                     \
  {                                                                      \
    NvM_Queue_IndexStandard = (uint8)( NvM_Queue_IndexStandard + 1U );   \
  } while (0)

/** \brief Reduce the Standard Queue Index by 1
 **
 **        The macro decrements the value of Standard Queue Index by 1
 **        so that the job request at Index position is removed from the queue.
 **        When all elements are removed, Index is set to uninitialized(0xFF).
 **/
#define NVM_STANDARD_QUEUE_DOWN()                                        \
  do                                                                     \
  {                                                                      \
    NvM_Queue_IndexStandard = (uint8)( NvM_Queue_IndexStandard - 1U );   \
  } while (0)

/*==================[type definitions]======================================*/

/** \brief User configuration information for NvM blocks
 **
 ** Each configured block has assigned one realization of this type. */
typedef struct
{
  /** \brief  start address of the permanent user data RAM block. */
  P2VAR(void, TYPEDEF, NVM_APPL_DATA) ramBlockDataAddress;

  /** \brief start address of the user data ROM block which contains the default
   ** data */
  P2CONST(void, TYPEDEF, NVM_APPL_CONST) romBlockDataAddress;

  /** \brief pointer to initialization function. Can be used alternatively to copy
   ** default data into the RAM block. */
  NvM_InitBlockCallbackType initBlockCallback;

  /** \brief error status call back function. Called after an asynchronous request has
   ** finished. */
  NvM_SingleBlockCallbackType singleBlockCallback;

#if (NVM_SYNC_MECHANISM == STD_ON)

  /**  \brief Pointer to NvM to RAM copy callback function. Called by NvM in order to let
   **         the application copy data from NvM module's mirror to RAM block.
   **/
  NvM_NvToRamCopyCallbackType readRamFromNvCallback;

  /**  \brief Pointer to RAM to NvM copy callback function. Called by NvM in order to let
   **         the application copy data from RAM block to NvM module's mirror.
   **/
  NvM_RamToNvCopyCallbackType writeRamToNvCallback;

#endif

  /** \brief Bit encoded NV block description
   *
   * Bit pattern: xxxx xxxx xxxx qwsd vebi iiam msow rccc
   * - c: crcType, enum: no crc, CRC8, CRC16, CRC32
   * - r: RAM block CRC, boolean
   * - w: write protection, boolean
   * - o: write once, boolean
   * - s: resistant to changed SW, boolean
   * - m: management type, enum: native, redundant, dataset
   * - a: read all, boolean
   * - i: deviceId, 0-7
   * - b: use internal buffer, boolean
   * - e: enable advanced error recovery, boolean
   * - v: enable write verification, boolean
   *
   * - d: enable static block id check, boolean
   * - s: use mirror for explicit synchronization, boolean
   * - w: write all enabled, boolean
   * - q: block status info enabled, boolean
   *
   * Only use NVM_BD_*() macros to access contents.
   */
  uint32 blockDesc;

  /** \brief block base number. */
  uint16 nvBlockBaseNum;

  /** \brief length of the user data in bytes. */
  uint16 nvBlockLength;

  /** \brief Index of the stored CRC for the block. */
  uint16 ramBlockCrcIndex;

#if (NVM_WRITE_VERIFICATION == STD_ON)
  /** \brief NV block verification data size */
  uint16 verifyDataSize;
#endif

  /** \brief number of user data areas. 1 for native blocks, 2 for redundant blocks, n
   ** for dataset blocks */
  uint8 nvBlockNum;

  /** \brief number of user ROM Blocks */
  uint8 romBlockNum;
#if ( NVM_JOB_PRIORITIZATION == STD_ON )
  /* Priority of the NvM blocks. Priority is classified into "immediate
   * priority" and "standard priority". Immediate priority jobs have priority
   * over standard priority jobs. All standard priority jobs are processed in
   * first-come-first-served manner. i.e. no prioritisation is done for
   * several standard priority jobs which are in the queue at a time */
  uint8 blockJobPriority;
#endif

#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
  /** \brief Maximum number of block write retry */
  uint8 writeRetryLimit;
#endif

#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
  /** \brief Maximum number of times the read operation is retried */
  uint8 readRetryLimit;
#endif
} NvM_BlockDescriptorType;
/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]==========================================*/

#if (NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS > 0U)
#define NVM_START_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>

/** \brief Stores the status of the NvM blocks.
 **/
extern VAR( NvM_AdminBlockType,NVM_VAR_POWER_ON_INIT ) NvM_AdminBlockTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#define NVM_STOP_SEC_VAR_POWER_ON_INIT_8
#include <MemMap.h>
#endif

/***************************  variables normal uint8 section ****************/
#define NVM_START_SEC_VAR_INIT_8
#include <MemMap.h>
/* !LINKSTO NVM506,1, NVM508,1 */
/** \brief used to store the interim value of the error status of a single
 ** block API function while this function is processed. */
extern VAR( uint8,NVM_VAR ) NvM_GlobalErrorStatus;

/** \brief used as index ( 'stack pointer' ) for array NvM_CurrentFunctionPtr to
 ** store the call level of the currently processed state machine. */
extern VAR( uint8,NVM_VAR ) NvM_GlobalCallLevel;

/** \brief stores status information concerning all blocks. */
extern VAR( uint8,NVM_VAR ) NvM_GlobalGenericStatus;
#if (NVM_NUMBER_OF_WRITE_RETRY_BLOCKS > 0U)
/** \brief counts the number of write retries. If the value reaches
 ** 'NvMMaxNumOfWriteRetries' NvM_WriteBlock() terminates with an error. */
extern VAR( uint8,NVM_VAR ) NvM_WriteRetryCount;
#endif

#if (NVM_NUMBER_OF_READ_RETRY_BLOCKS > 0U)
/** \brief counts the number of read retries. If the value reaches
 ** 'NvMaxNumOfReadRetries' NvM_ReadBlock() starts copy redundant/ROM block . */
extern VAR( uint8,NVM_VAR ) NvM_ReadRetryCount;
#endif

#define NVM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>

/***************************  uninitialized variables uint8 section ****************/
#define NVM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief holds the ID of the currently executed service. It is used to
 ** determine the currently running operation and to pass it as parameter
 ** to the callback function if the currently executed service has finished.
 **/
extern VAR( uint8,NVM_VAR_NOINIT ) NvM_CurrentServiceId;

#if (NVM_SYNC_MECHANISM == STD_ON)
/** \brief Counts the number of retries to let the application copy data
 **        between the RAM block and NvM module's mirror before postponing
 **        the current job.
 **/
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MirrorRetryCount;
#endif

#define NVM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/***************************  uninitialized variables uint16 section ****************/
#define NVM_START_SEC_VAR_NO_INIT_16
#include <MemMap.h>

#if ((NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) && (NVM_RAMBLOCK_CRC_BUFFER_SIZE > 0U))

/**  \brief The number of RAM block CRC Calculation pending request.
 **/
extern VAR( uint16, NVM_VAR_NOINIT ) NvM_RamBlockCrcCalcCount;
#endif

#define NVM_STOP_SEC_VAR_NO_INIT_16
#include <MemMap.h>

/***************************  uninitialized variables unspecified section ****************/
#define NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO NVM506,1 */
/** \brief Stores the current status of the currently processed
 **        NvM Block.
 **/
extern VAR( NvM_DynamicStatusType,NVM_VAR_NOINIT )  NvM_GlobalWorkingStatus;

#define NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/***********************  variables user application data section ***********/

#define NVM_START_SEC_VAR_APPL_DATA
#include <MemMap.h>

/** \brief Stores the address of the temporary RAM block to be used
 **        while a request with a temporary RAM block is in progress.
 **        This value is initialized when the request is fetched from
 **        the queue and processing is started.
 **/
extern P2VAR(uint8, NVM_VAR_NOINIT, NVM_APPL_DATA) NvM_TempRamBlockAddress;

#if (NVM_INTERNAL_BUFFER_SIZE != 0U)
/** \brief NVM internal buffer for temporary data storage.
 ** This buffer is used for blocks with CRC for storing block data and CRC
 ** while reading from and writing to NV memory. */
extern VAR(uint8, NVM_APPL_DATA) NvM_InternalBuffer[NVM_INTERNAL_BUFFER_SIZE];
#endif

#define NVM_STOP_SEC_VAR_APPL_DATA
#include <MemMap.h>

/***********************  variables user application data section ***********/
#define NVM_START_CONFIG_DATA_APPL_DATA
#include <MemMap.h>

/** \brief The RAM data buffer for the configuration ID (Block 1).
 **/
extern VAR( uint16,NVM_APPL_DATA ) NvM_ConfigurationId[NVM_CONFIGURATIONID_SIZE];

#define NVM_STOP_CONFIG_DATA_APPL_DATA
#include <MemMap.h>
/******************** end of variables user application data section ********/
/**************************  variables normal uin16 section *****************/
#define NVM_START_SEC_VAR_INIT_16
#include <MemMap.h>

/** \brief Stores the number of the currently processed NvM block.
 **/
extern VAR( uint16,NVM_VAR )        NvM_GlobalBlockNumber;

#define NVM_STOP_SEC_VAR_INIT_16
#include <MemMap.h>
/**************************  end of variables normal uin16 section **********/
/**************************  variables normal unspecified section ***********/
#define NVM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Stores the function pointers to the currently processed
 **        state of the state machine of an asynchronous function.
 **/
extern VAR( NvM_CurrentFunctionPtrType,NVM_VAR ) NvM_CurrentFunctionPtr[6U];

/** \brief Pointer to the block descriptor of currently processed NvM block.
 **/
extern P2CONST( NvM_BlockDescriptorType,NVM_VAR,NVM_CONST ) NvM_CurrentBlockDescriptorPtr;

#define NVM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>
/**************************  end of variables normal unspecified section ****/
/***************** configurated constants uint8 section *********************/
/***************************  end of constants uint8 section ****************/
/**************************  constants uint8 section ************************/
/**************************  end of constants uint8 section *****************/
/***********************  constants user application section ****************/
#define NVM_START_CONFIG_DATA_APPL_CONST
#include <MemMap.h>

/** \brief Stores the value of the configuration ID set by the user.
 **/
extern CONST( uint16,NVM_CONST ) NvM_CompiledConfigurationId;

#define NVM_STOP_CONFIG_DATA_APPL_CONST
#include <MemMap.h>
/********************* end of constants user application section ************/
/***************************  constants unspecified section *****************/
#define NVM_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/** \brief Array storing the block configuration for each block.
 **/
extern CONST( NvM_BlockDescriptorType,NVM_CONST )
          NvM_BlockDescriptorTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS];

#define NVM_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>
/***************************  end of constants unspecified section **********/
/***************************  constants unspecified section *****************/
/***************************  end of constants unspecified section **********/
/***************************  constants unspecified section *****************/
/***************************  end of constants unspecified section **********/
/***************************  constants uint8 section ***********************/
/***************************  end of constants uint8 section ****************/
/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/
#endif /* NVM_DATA_INTERN_H */

/*======================[end of file NvM_DataIntern.h]======================*/
