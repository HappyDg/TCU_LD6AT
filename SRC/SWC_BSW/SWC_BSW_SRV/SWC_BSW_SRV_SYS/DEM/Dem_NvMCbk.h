/**
 * \file
 *
 * \brief AUTOSAR Dem
 *
 * This file contains the implementation of the AUTOSAR
 * module Dem.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if ( !defined DEM_NVMCBK_H )
#define DEM_NVMCBK_H

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <Std_Types.h>                            /* AUTOSAR standard types */

#include <Dem_Version.h>                      /* Module version declaration */

#include <Dem_Cfg.h>                     /* Module public generated symbols */

#if (DEM_USE_PERMANENT_STORAGE == STD_ON)
#include <NvM_Types.h>                                         /* NvM types */
#endif

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

#if ((DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH) || \
     (DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_TRIGGER))

/** \brief No-OP Callback-Function from NvM for default data block to request
 ** the data to be copied from the NvM RAM mirror during NvM_ReadBlock()
 **
 ** As the Dem module will not use NvM_ReadBlock() for the status block,
 ** this callback function is implementation as "No-OP".
 **
 ** \param[in] NvMBuffer  Pointer to NvM RAM mirror
 **
 ** \return returns always E_OK
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvMReadCopyEventStatusBlock(
  P2CONST(void, NVM_APPL_DATA, NVM_VAR_NOINIT) NvMBuffer);

/** \brief Callback-Function from NvM for default data block to request
 ** the data to be copied into the NvM RAM mirror during NvM_WriteBlock()
 **
 ** \param[in] NvMBuffer  Pointer to NvM RAM mirror
 **
 ** \return returns always E_OK
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvMWriteCopyEventStatusBlock(
  P2VAR(void, NVM_APPL_DATA, NVM_VAR_NOINIT) NvMBuffer);

/** \brief Callback-Function from NvM for default data block
 ** notifying successful completion of single block request
 **
 ** \param[in] ServiceId
 ** \param[in] JobResult
 **
 ** \return returns always E_OK
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvMEventStatusBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult);

#endif /* DEM_CLEAR_DTC_BEHAVIOR == DEM_CLRRESP_NONVOLATILE_FINISH/TRIGGER */

#if (DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON)

/** \brief Callback-Function from NvM for primary NV gate-entry data block
 ** notifying successful completion of single block request
 **
 ** \param[in] ServiceId
 ** \param[in] JobResult
 **
 ** \return returns always E_OK
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryPrimaryBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult);

#if (DEM_MAX_NUMBER_EVENT_ENTRY_SEC != 0U)
/** \brief Callback-Function from NvM for secondary NV gate-entry data block
 ** notifying successful completion of single block request
 **
 ** \param[in] ServiceId
 ** \param[in] JobResult
 **
 ** \return returns always E_OK
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntrySecondaryBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult);
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_MIR != 0U)
/** \brief Callback-Function from NvM for mirror NV gate-entry data block
 ** notifying successful completion of single block request
 **
 ** \param[in] ServiceId
 ** \param[in] JobResult
 **
 ** \return returns always E_OK
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryMirrorBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult);
#endif

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER != 0U)
/** \brief Callback-Function from NvM for permanent NV gate-entry data block
 ** notifying successful completion of single block request
 **
 ** \param[in] ServiceId
 ** \param[in] JobResult
 **
 ** \return returns always E_OK
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DEM_CODE) Dem_NvMGateEntryPermanentBlockCallback(
  uint8                 ServiceId,
  NvM_RequestResultType JobResult);
#endif

#endif /* DEM_USE_IMMEDIATE_NV_STORAGE == STD_ON */

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( DEM_NVMCBK_H ) */
/*==================[end of file]===========================================*/
