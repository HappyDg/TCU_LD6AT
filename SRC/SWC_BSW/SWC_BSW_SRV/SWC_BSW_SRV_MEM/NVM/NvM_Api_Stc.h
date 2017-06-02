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
#if ( !defined NVM_API_STC_H )
#define NVM_API_STC_H

/*==================[inclusions]============================================*/

#include <NvM_Types.h>            /* NVRAM Manager specific type            */
                                  /* definitions.                           */
#include <NvM_Version.h>          /* AUTOSAR and module version number      */
                                  /* definitions.                           */

/*==================[macros]================================================*/

#ifndef NVM_REQ_CANCELLED
/** \brief Value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if NvM_WriteAll() is cancelled by NvM_CancelWriteAll() */
#define NVM_REQ_CANCELLED        6U
#endif

/** \brief Used to mark a block as valid in the NvM_AdminBlockTable. */
#define NVM_BLOCK_VALID          0xA5U

/** \brief Used to mark a block as invalid in the NvM_AdminBlockTable. */
#define NVM_BLOCK_INVALID        0xFFU

/*------------------[definition of development errors]----------------------*/

#if ( defined NVM_E_PARAM_BLOCK_ID ) /* to prevent double declaration */
#error NVM_E_PARAM_BLOCK_ID is already defined
#endif /* if ( defined NVM_E_PARAM_BLOCK_ID ) */
/** \brief API requests called with wrong parameter */
#define NVM_E_PARAM_BLOCK_ID       0x0AU

#if ( defined NVM_E_PARAM_BLOCK_TYPE ) /* to prevent double declaration */
#error NVM_E_PARAM_BLOCK_TYPE is already defined
#endif /* if ( defined NVM_E_PARAM_BLOCK_TYPE ) */
/** \brief API requests called with wrong parameter */
#define NVM_E_PARAM_BLOCK_TYPE     0x0BU

#if ( defined NVM_E_PARAM_BLOCK_DATA_IDX ) /* to prevent double declaration */
#error NVM_E_PARAM_BLOCK_DATA_IDX is already defined
#endif /* if ( defined NVM_E_PARAM_BLOCK_DATA_IDX ) */
/** \brief API requests called with wrong parameter */
#define NVM_E_PARAM_BLOCK_DATA_IDX 0x0CU

#if ( defined NVM_E_PARAM_ADDRESS ) /* to prevent double declaration */
#error NVM_E_PARAM_ADDRESS is already defined
#endif /* if ( defined NVM_E_PARAM_ADDRESS ) */
/** \brief API requests called with wrong parameter */
#define NVM_E_PARAM_ADDRESS        0x0DU

#if ( defined NVM_E_PARAM_DATA ) /* to prevent double declaration */
#error NVM_E_PARAM_DATA is already defined
#endif /* if ( defined NVM_E_PARAM_DATA ) */
/** \brief API requests called with wrong parameter */
#define NVM_E_PARAM_DATA           0x0EU

#if ( defined NVM_E_PARAM_POINTER ) /* to prevent double declaration */
#error NVM_E_PARAM_POINTER is already defined
#endif /* if ( defined NVM_E_PARAM_POINTER ) */
/** \brief API requests called with wrong parameter */
#define NVM_E_PARAM_POINTER        0x0FU

#if ( defined NVM_E_NOT_INITIALIZED ) /* to prevent double declaration */
#error NVM_E_NOT_INITIALIZED is already defined
#endif /* if ( defined NVM_E_NOT_INITIALIZED ) */
/** \brief NVRAM Manager is still uninitialized */
#define NVM_E_NOT_INITIALIZED      0x14U

#if ( defined NVM_E_BLOCK_PENDING ) /* to prevent double declaration */
#error NVM_E_BLOCK_PENDING is already defined
#endif /* if ( defined NVM_E_BLOCK_PENDING ) */
/** \brief API read/write/control request failed */
#define NVM_E_BLOCK_PENDING        0x15U

#if ( defined NVM_E_BLOCK_CONFIG ) /* to prevent double declaration */
#error NVM_E_BLOCK_CONFIG is already defined
#endif /* if ( defined NVM_E_BLOCK_CONFIG ) */
/** \brief API read/write/control request failed */
#define NVM_E_BLOCK_CONFIG         0x18U

#if (defined NVM_E_BLOCK_LOCKED)  /* To prevent double declaration */
#error NVM_E_BLOCK_LOCKED is already defined.
#endif /*  if(defined NVM_E_BLOCK_LOCKED) */
/** \brief API write request failed */
#define  NVM_E_BLOCK_LOCKED        0x19U

/*==================[external function declarations]========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief Initiates a multi block write request
 **
 ** NvM_WriteAll() copies the data of all configured blocks except block
 ** 0 from the RAMDataBlock to the corresponding NVM Block if the
 ** following conditions are true:
 ** - if a block has assigned a permanent RAM data block
 ** - if the block was marked as changed by function NvM_SetRamBlockStatus()
 ** - if the block is not write protected
 ** - if the block is valid
 **
 ** If one of these conditions is false the block is skipped. The status of
 ** a skipped block is set to NVM_REQ_SKIPPED. If a block is configured
 ** with NvMWriteBlockOnce the block is marked as write protected
 ** after the data is written. If NvM_WriteAll() is cancelled by
 ** NvM_CancelWriteAll() the data of the currently processed NVRAM
 ** block will still be written and afterwards NvM_WriteAll() terminates
 ** and sets the multi request job result to NVM_REQ_CANCELLED. If
 ** one of the processed blocks can not be written successfully the multi
 ** request job result of NvM_WriteAll() is set to NVM_REQ_NOT_OK.
 **
 ** \ProductionError{NVM_E_QUEUE_OVERFLOW, thrown\, if a new NVM request
 ** cannot be processed because the NVM queue is full.}
 **
 ** \ServiceID{13}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC( void,NVM_CODE ) NvM_WriteAll( void );

/** \brief Service to cancel a running NvM_WriteAll request
 **
 ** This function cancels an ongoing NvM_WriteAll(). After the data of
 ** the currently processed NVRAM block has been written
 ** Description
 ** NvM_WriteAll() terminates and sets the multi request job result to
 ** NVM_REQ_CANCELLED. If NvM_WriteAll() is not running at the
 ** time NvM_CancelWriteAll() is called this request has no effect on
 ** the execution of the next NvM_WriteAll() request.
 **
 ** Remarks:
 ** In contrast to the AUTOSAR NVRAM Manager specification the
 ** function NvM_CancelWriteAll is implemented as a synchronous
 ** function instead of an asynchronous one. Since NvM_WriteAll()
 ** must not be queued (requirement NVM420) NvM_Cancel-WriteAll()
 ** need not to be queued too and therefore it need not
 ** to be asynchronous.
 **
 ** \ServiceID{10}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC( void,NVM_CODE ) NvM_CancelWriteAll( void );

/** \brief Initiates a multi block read request
 **
 ** NvM_ReadAll() copies the data of all configured NVM Blocks from
 ** Non Volatile Memory to the corresponding RAM Data Blocks if the
 ** following conditions are achieved for a NVRAM Block
 ** - a permanent RAM block is configured
 ** - the configuration parameter NvMSelectBlockForReadAll is enabled
 ** - the RAM Block Status is a:) invalid b:) valid and inconsistent
 **   and CRC calculation is enabled
 **
 ** A RAM Block is consistent when a block specific RAM Crc Block is
 ** assigned to the RAM Block, and the CRC calculated from the RAM
 ** Data Block is equal to the CRC stored in the RAM Crc Block. This
 ** means if the RAM Block already contains valid and consistent data
 ** then it is not overwritten by the NVM Block data. To invalidate a RAM
 ** Block X the service NvM_SetRamBlockStatus(X,FALSE) must be
 ** used. The advantage of this approach is that after a hot reset the
 ** NVM data is not copied again when the RAM Block data is still valid
 ** and consistent. Also Dataset Blocks are processed by
 ** NvM_ReadAll(). The user is responsible that the DataIndex is set
 ** correctly previous to calling NvM_ReadAll(). By default the DataIndex
 ** is set to zero by NvM_Init(). Before the data is copied NvM_ReadAll()
 ** reads the ConfigurationId which is stored in NVRAM Block number
 ** 1 (NvMNvBlockIdentifier=1) and compares this value with the Compiled
 ** Configuration Id. Depending on the result of this comparison
 ** and other configuration parameters 4 different cases can occur:
 ** - If the Configuration IDs match then NvM_ReadAll() continues
 **   with copying the data from NVRAM to RAM. In this case it can
 **   be assumed that the NVRAM data layout has not changed and
 **   the data stored last in NVRAM can be copied successfully.
 ** - If the Configuration IDs do not match and parameter
 **   NvMDynamicConfigurationis disabled then NvM_ReadAll() also continues
 **   with copying the data. In this case it can be assumed that the NVRAM
 **   data layout has changed (e.g. new NVRAM Blocks were added or blocks were
 **   deleted or the length of a block was changed) and that the data stored
 **   last in NVRAM can not be copied successfully for all NVRAM Blocks. First
 **   NvM_ReadAll() tries to copy the data from NVRAM to RAM for each block
 **   which must be processed by NvM_ReadAll(). If an error is detected the
 **   ROM default data is loaded or the error status is set according the
 **   specification of NvM_ReadBlock().  The new Compiled Configuration ID is
 **   not written automatically by the next invocation of
 **   NvM_WriteAll(). Note: it should be avoided that a configuration ID is
 **   changed when NvMDynamic- Configuration is disabled as there is the risk
 **   that incorrect data could be interpreted as valid. If the read data is
 **   interpreted as valid and if NvMWriteBlockOnce is enabled too then the
 **   write protection is set automatically and valid data can not be written
 **   at all ! Therefore if the configuration ID is changed,
 **   NvMDynamicConfiguration should be enabled.
 ** - If the Configuration IDs do not match and parameter
 **   NvMDynamicConfiguration is enabled then NvM_ReadAll() also continues
 **   with copying the data. In this case also the block specific
 **   configuration parameter NvMResistantToChangedSw is evaluated for each
 **   block. If it is disabled then ROM default data is loaded immediately and
 **   the block is not set to write protected even if NvMWriteBlockOnce was
 **   enabled. This means the data can be written again. If
 **   NvMResistantToChangedSw is enabledNvM_ ReadAll() first tries to copy the
 **   data from NVRAM to RAM assuming that the address of this block in NVRAM
 **   has not changed. The new Compiled Configuration ID is written
 **   automatically by the next invocation of NvM_WriteAll().  - If the
 **   Configuration IDs do not match because the NVRAM Block of the
 **   Configuration ID is invalid (this can happens for example when the
 **   Configuration ID is read for the first time from an uninitialized NVRAM
 **   device) then NvM_ReadAll() continues with copying the data from NVRAM to
 **   RAM. If an error is detected the ROM default data is loaded or the error
 **   status is set according to the specification of NvM_ReadBlock(). The new
 **   Compiled Configuration ID is written automatically by the next
 **   invocation of NvM_WriteAll().
 **
 ** NOTE: A mismatch of the Configuration IDs can be caused also by
 ** an error in reading the Configuration ID from NVRAM. This leads to
 ** the same behavior as that of NvM_ReadAll() when a mismatch of
 ** Compiled Configuration ID occurs.
 **
 ** Block specific Error-Status after service finished
 ** - NVM_REQ_OK : The NVM Block was copied successfully or
 **   the ROM Block was copied successfully if a Dataset Block was
 **   requested and the DataIndex selects a ROM Block. The ROM
 **   Block was copied successfully in case the Configuration Id's
 **   don't match and NvMDynamicConfiguration is enabled and
 **   NvMResistantToChangedSw is disabled.
 ** - NVM_REQ_INVALIDATED : The job result of an underlying
 **   abstraction module is MEMIF_BLOCK_INVALID.
 ** - NVM_REQ_INTEGRITY_FAILED : If a CRC mismatch occurs
 **   or if the job result of the underlying memory abstraction module
 **   is MEMIF_BLOCK_INCONSISTENT.
 ** - NVM_REQ_CANCELLED: An underlying memory abstraction
 **   module reports MEMIF_JOB_CANCELED. In this case
 **   NvM_ReadAll() is not terminated completely, the service proceeds
 **   copying the next block.
 ** - NVM_REQ_NOT_OK: The job result of the underlying memory
 **   abstraction module is MEMIF_JOB_FAILED or the ROM Block
 **   was not copied successfully if a Dataset Block was requested
 **   and the DataIndex selects a ROM Block.
 ** - NVM_REQ_BLOCK_SKIPPED: The block was not processed
 **   because the conditions listed above were not achieved.
 **
 ** If an error is detected during processing NvM_ReadBlock() and the
 ** ROM default data must be copied by NvM_RestoreBlockDefaults()
 ** the ErrorStatus set by NvM_RestoreBlockDefaults() is ignored and
 ** the above ErrorStatus applies nevertheless.
 **
 ** Multi request ErrorStatus after service finished (stored in NVRAM Block 0)
 ** - NVM_REQ_OK: Each Block specific ErrorStatus is NVM_REQ_OK or
 **   NVM_REQ_SKIPPED.
 ** - NVM_REQ_NOT_OK: The Block specific ErrorStatus of at least one NVRAM
 **   Block is neither NVM_REQ_OK nor NVM_REQ_BLOCK_SKIPPED.
 **
 ** Block specific RAMBlock-Status after service finished (applies only for
 ** permanent RAM Blocks)
 ** - VALID / UNCHANGED: A NVM Block was copied successfully to the RAM Block.
 ** - VALID / CHANGED: A ROM Block was copied successfully to the RAM Block.
 ** - INVALID / UNCHANGED: An error was detected during copying the NVM Block
 **   to the RAM Block and no ROM Block is configured.
 ** - INVALID / CHANGED: Can not occur.
 **
 ** A ROM Block is copied if a Dataset Block is requested and the
 ** DataIndex selects a ROM Block, or an error is detected during
 ** copying the NVM Block and the default ROM Block data is copied,
 ** or the Configuration Id's don't match and NvMDynamicConfiguration
 ** is enabled and NvMResistantToChangedSw is disabled.
 **
 ** \ProductionError{NVM_E_QUEUE_OVERFLOW, thrown\, if a new NVM request cannot
 ** be processed because the NVM queue is full.}
 **
 ** \ServiceID{12}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Asynchronous} */
extern FUNC( void,NVM_CODE ) NvM_ReadAll( void );

/** \brief Initializes the NvM module.
 **
 ** This service initializes the NVRAM manager. The time consuming
 ** NVRAM block initialization and set-up according to the block
 ** descriptor is done by the NvM_ReadAll request.
 **
 ** \ServiceID{0}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC( void,NVM_CODE ) NvM_Init( void );

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( NVM_API_STC_H ) */

/*==================[end of file NvM_Api_Stc.h]=============================*/
