/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined PDUR_API_DEPEND_H)
#define PDUR_API_DEPEND_H
/*==================[inclusions]============================================*/

#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* AUTOSAR Communication Stack types */
#include <PduR_Cfg.h>          /* Generated header of  PDU Router */
#include <PduR_Types.h>        /* types of PduR module */

/* Include zero cost header file if fully handled by zero cost operation.
   This comprises also cases like configuring solely communication interface modules or
   solely transport protocol modules. */
#if (PDUR_ZERO_COST_OPERATION_FULL == STD_ON)
#include <PduR_Zc_Cfg.h>
#else /* (PDUR_ZERO_COST_OPERATION_FULL == STD_OFF) */
/*==================[macros]================================================*/

/*------------------[PDU Router 'Post Build Config']------------------------*/
#if (PDUR_CONST_CFG_ADDRESS_ENABLE == STD_ON)

#ifdef PduR_gConfigPtr
#error PduR_gConfigPtr already defined!
#endif
/** \brief define PduR_gConfigPtr
 * root config pointer is replaced by absolute address that is given via
 * pre-compile-time switch PDUR_CONST_CONFIG_ADDRESS
 */
#define PduR_gConfigPtr \
    ((P2CONST(PduR_PBConfigType, PDUR_VAR_FAST, PDUR_APPL_CONST)) \
    PDUR_CONST_CFG_ADDRESS)

#endif /* PDUR_CONST_CFG_ADDRESS_ENABLE */


#ifdef PDUR_INVALID_CONFIGURATION_ID
#error PDUR_INVALID_CONFIGURATION_ID already defined!
#endif
/** \brief Macro definition for the invalid configuration Id returned by
 * PduR_GetConfigurationId if the PduR is not initialized.
 */
#define PDUR_INVALID_CONFIGURATION_ID          0xFFFFFFFFU

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/
#define PDUR_START_SEC_CODE
#include <MemMap.h>

/** \brief Get version information.
 **
 ** This service returns the version information of this module.
 **
 ** \param[out]  versionInfo  Pointer to where to store the version
 **                           information of this module (Module Id,
 **                           Vendor Id, Instance Id, Vendor specific version numbers)
 **
 ** \ServiceID{0x02}
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
#if (PDUR_VERSION_INFO_API == STD_ON)
extern FUNC(void,PDUR_CODE) PduR_GetVersionInfo
(
   P2VAR(Std_VersionInfoType,AUTOMATIC,PDUR_APPL_DATA) versionInfo
);
#elif (PDUR_VERSION_INFO_API == STD_OFF)
/*
 * PduR_GetVersionInfo() API function is disabled -
 * provide macro implementation
 */
#define PduR_GetVersionInfo(versionInfo) \
   do \
   { \
      /* get version info of PduR module */ \
      (versionInfo)->vendorID = PDUR_VENDOR_ID; \
      (versionInfo)->moduleID = PDUR_MODULE_ID; \
      (versionInfo)->sw_major_version = PDUR_SW_MAJOR_VERSION; \
      (versionInfo)->sw_minor_version = PDUR_SW_MINOR_VERSION; \
      (versionInfo)->sw_patch_version = PDUR_SW_PATCH_VERSION; \
   } while(0)
#endif /*  #if (PDUR_VERSION_INFO_API == STD_ON) */


/** \brief PduR_Init - Initializes the PDU Router.
 ** Function to initialize the PduR module. First function to be called of PduR.
 ** The module calling the function PduR_Init has to include PduR_PBcfg.h. The
 ** invocation of the PduR_Init function is
 ** PduR_Init(&(PDUR_CONFIG_NAME.PduR_RootConfig));
 **
 ** \param[in] ConfigPtr Pointer to post build configuration.
 **
 ** \ServiceID{0x01}
 ** \Reentrancy{Non Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, PDUR_CODE) PduR_Init
(
   P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_APPL_CONST) ConfigPtr
);


/** \brief Get configuration ID
 **
 ** Returns the unique identifier of the post-build time configuration of the PDU Router.
 **
 ** \return Identifier of the post-build time configuration.
 **         For enabled DET the invalid configuration Id 'PDUR_INVALID_CONFIGURATION_ID'
 **         is returned.
 **
 ** \ServiceID{0x10}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(PduR_PBConfigIdType, PDUR_CODE) PduR_GetConfigurationId
(
   void
);


/** \brief Validate configuration
 **
 ** Checks if the post build configuration is valid.
 ** A configuration is invalid if
 ** - the platform signature does not match.
 ** - the published information signature does not match.
 ** - the link time signature does not match.
 ** - the compile time signature does not match.
 ** - the function is called with a null pointer.
 **
 ** \param[in] ConfigPtr Pointer to configuration structure that holds the
 **                      PduR module post-build-time configuration data.
 **
 ** \return Function execution success status
 ** \retval E_OK  the provided module configuration is valid
 ** \retval E_NOT_OK  the provided module configuration is invalid
 **
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
 
#if PDUR_ISVALIDCONFIG_MMAP_ENABLED == STD_ON
#define PDUR_STOP_SEC_CODE
#include <MemMap.h>
#define PDUR_START_SEC_CODE_CC_BLOCK
#include <MemMap.h>
#endif

extern FUNC(Std_ReturnType, PDUR_CODE) PduR_IsValidConfig
(
    P2CONST(void, AUTOMATIC, PDUR_APPL_CONST) ConfigPtr
);

#if PDUR_ISVALIDCONFIG_MMAP_ENABLED == STD_ON
#define PDUR_STOP_SEC_CODE_CC_BLOCK
#include <MemMap.h>

#define PDUR_START_SEC_CODE
#include <MemMap.h>
#endif

#define PDUR_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/
#if (PDUR_CONST_CFG_ADDRESS_ENABLE == STD_OFF)
/*
 * if not a constant configuration address is used - define pointer variable
 */
#define PDUR_START_SEC_VAR_FAST_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief PduR_gConfigPtr
 * global variable for the pointer to the config of PduR
 */
extern P2CONST(PduR_PBConfigType, PDUR_VAR_FAST, PDUR_APPL_CONST) PduR_gConfigPtr;


#define PDUR_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
#include <MemMap.h>

#endif /* PDUR_CONST_CFG_ADDRESS_ENABLE == STD_OFF */
/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if (PDUR_ZERO_COST_OPERATION_FULL == STD_ON) */
#endif /* if !defined( PDUR_API_DEPEND_H ) */
/*==================[end of file]===========================================*/
