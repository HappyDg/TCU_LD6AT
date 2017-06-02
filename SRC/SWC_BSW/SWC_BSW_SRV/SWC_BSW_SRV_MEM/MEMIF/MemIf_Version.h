/* !LINKSTO MemIf64,1 */
/**
 * \file
 *
 * \brief AUTOSAR MemIf
 *
 * This file contains the implementation of the AUTOSAR
 * module MemIf.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined MEMIF_VERSION_H)
#define MEMIF_VERSION_H

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined MEMIF_VENDOR_ID)
#error MEMIF_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define MEMIF_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined MEMIF_MODULE_ID)
#error MEMIF_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define MEMIF_MODULE_ID         22U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined MEMIF_AR_RELEASE_MAJOR_VERSION)
#error MEMIF_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define MEMIF_AR_RELEASE_MAJOR_VERSION     4U

#if (defined MEMIF_AR_RELEASE_MINOR_VERSION)
#error MEMIF_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define MEMIF_AR_RELEASE_MINOR_VERSION     0U

#if (defined MEMIF_AR_RELEASE_REVISION_VERSION)
#error MEMIF_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define MEMIF_AR_RELEASE_REVISION_VERSION  3U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined MEMIF_SW_MAJOR_VERSION)
#error MEMIF_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define MEMIF_SW_MAJOR_VERSION             5U

#if (defined MEMIF_SW_MINOR_VERSION)
#error MEMIF_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define MEMIF_SW_MINOR_VERSION             3U

#if (defined MEMIF_SW_PATCH_VERSION)
#error MEMIF_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define MEMIF_SW_PATCH_VERSION             5U

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( MEMIF_VERSION_H ) */
/*==================[end of file]============================================*/
