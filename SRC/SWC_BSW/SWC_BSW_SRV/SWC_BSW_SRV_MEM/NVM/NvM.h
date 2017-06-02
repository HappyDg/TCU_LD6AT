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
#if ( !defined NVM_H )
#define NVM_H
/*==================[inclusions]============================================*/

#include <TSAutosar.h>        /* EB specific standard types                 */

/* Generated configuration data. Defines NVM_INCLUDE_RTE. */
/* !LINKSTO NVM553,1 */
#include <NvM_Cfg.h>
#include <NvM_Api_Stc.h>
#include <NvM_BSW.h>                /* NvM's common API */


#if ( NVM_INCLUDE_RTE == STD_ON )
# include <Rte_NvM_Type.h>         /* Rte type definitions. */
#endif

/*==================[macros]================================================*/

#if ((NVM_INCLUDE_RTE == STD_OFF) || (NVM_SERVICE_PORT_USED == STD_OFF))
/* These macros are also defined in Rte_NvM_Type.h */
/* !LINKSTO NVM470,1 */
#ifndef NVM_REQ_OK
/** \brief value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if the last API request has finished without error. */
#define NVM_REQ_OK                  0U
#endif

#ifndef NVM_REQ_NOT_OK
/** \brief value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if the last API request has finished with an error. */
#define NVM_REQ_NOT_OK              1U
#endif

#ifndef NVM_REQ_PENDING
/** \brief Value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if the last API request has still not finished. */
#define NVM_REQ_PENDING             2U
#endif

#ifndef NVM_REQ_INTEGRITY_FAILED
/** \brief Value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if for e.g. the CRC check of the last API request has finished. */
#define NVM_REQ_INTEGRITY_FAILED    3U
#endif

#ifndef NVM_REQ_BLOCK_SKIPPED
/** \brief Value of type NvM_RequestResultType returned by
 ** NvM_GetErrorStatus. */
#define NVM_REQ_BLOCK_SKIPPED       4U
#endif

#ifndef NVM_REQ_NV_INVALIDATED
/** \brief Value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if the requested NvM block is invalid. */
#define NVM_REQ_NV_INVALIDATED      5U
#endif

#ifndef NVM_REQ_CANCELED
/** \brief Value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if the request has been cancelled. */
#define NVM_REQ_CANCELED            6U
#endif

#ifndef NVM_REQ_REDUNDANCY_FAILED
/** \brief Value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if the required redundancy of the referenced NV block is lost. */
#define NVM_REQ_REDUNDANCY_FAILED   7U
#endif

#ifndef NVM_REQ_RESTORED_FROM_ROM
/** \brief Value of type NvM_RequestResultType returned by NvM_GetErrorStatus
 ** if the referenced NV block has been restored from ROM. */
#define NVM_REQ_RESTORED_FROM_ROM   8U
#endif

#endif  /* ((NVM_INCLUDE_RTE == STD_OFF) || (NVM_SERVICE_PORT_USED == STD_OFF)) */

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_GetErrorStatus NvM_ASR40_GetErrorStatus

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_SetDataIndex NvM_ASR40_SetDataIndex

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_GetDataIndex NvM_ASR40_GetDataIndex

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_SetRamBlockStatus NvM_ASR40_SetRamBlockStatus

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_ReadBlock NvM_ASR40_ReadBlock

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_WriteBlock NvM_ASR40_WriteBlock

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_RestoreBlockDefaults NvM_ASR40_RestoreBlockDefaults

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_EraseNvBlock NvM_ASR40_EraseNvBlock

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_InvalidateNvBlock NvM_ASR40_InvalidateNvBlock

/** \brief Wrapping macro to provide AUTOSAR 4.0 API as default to other
 ** BSW modules */
#define NvM_SetBlockProtection NvM_ASR40_SetBlockProtection

/*==================[external function declarations]========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

#if ( NVM_VERSION_INFO_API == STD_ON )
/** \brief Service to get the version information of the NvM module.
 **
 ** This service returns the version information of this module. The version
 ** information includes:
 ** - Module ID
 ** - Vendor ID
 ** - Vendor specific version numbers
 **
 ** Remarks:
 ** - This function can be invoked by the user application although
 **   NvM_Init was not invoked yet.
 **
 ** \param[out] versionInfoPtr Pointer to where to store the version
 **                  information of this module.
 **
 ** \ServiceID{15}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC( void, NVM_CODE ) NvM_GetVersionInfo
(
  P2VAR( Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA ) versionInfoPtr
);
#endif

/** \brief Service for setting the lock status of the NV block
 **        of an NVRAM block.
 **
 ** If the API is called with parameter Locked as TRUE, the NV contents
 ** associated to the NVRAM block identified by BlockId cannot be modified
 ** by any other requests. The Block is skipped during NvM_WriteAll and
 ** other requests such as NvM_WriteBlock, NvM_InvalidateNvBlock and
 ** NvM_EraseNvBlock are rejected. At next start-up, during processing
 ** of NvM_ReadAll, this NVRAM block will be loaded from NV memory.
 **
 ** If the API is called with parameter Locked as FALSE, this NVRAM block
 ** will be processed normally.
 **
 ** Note 1:  The setting made using this service cannot be changed by
 ** NvM_SetRamBlockStatus or NvM_SetBlockProtection.
 **
 ** Note 2: This service can only be used by BSW Components.
 ** It cannot be accessed via RTE.
 **
 ** \param[in] BlockId The block identifier. Selects the block whose
 **            configuration parameter NvMNvBlockIdentifier is equal to
 **            BlockId.
 ** \param[in] BlockLocked TRUE: Mark the NV block as locked.
 **            FALSE: Mark the NV block as unlocked.
 **
 ** \ServiceID{19}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, NVM_CODE) NvM_SetBlockLockStatus
(
  NvM_BlockIdType BlockId,
  boolean         BlockLocked
);

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

/** \brief Service to cancel all pending job requests for an NVRAM Block
 **
 ** This service cancels all queued single block requests(Read, Write,
 ** Erase, Invalidate or Restore) for the NVRAM block referenced by BlockId.
 ** It does not cancel an ongoing job processing.
 **
 ** \param[in] BlockId The Block indentifier. Selects the block whose
 **            configuration parameter NvMNvBlockIdentifier is equal to
 **            BlockId
 ** \return    Std_returnType
 ** \retval    E_OK Request has been accepted
 ** \retval    E_OK Request has not been accepted
 **
 ** ServiceID{16}
 ** Reentrancy{Reentrant}
 ** Synchronicity(Asynchronous} */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_CancelJobs
(
  NvM_BlockIdType BlockId
);

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( NVM_H ) */

/*==================[end of file NvM.h]=====================================*/
