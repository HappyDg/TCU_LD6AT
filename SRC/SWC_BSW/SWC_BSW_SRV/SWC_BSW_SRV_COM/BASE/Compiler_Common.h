#if (!defined COMPILER_COMMON_H)
#define COMPILER_COMMON_H

/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*------------------[AUTOSAR vendor identification]-------------------------*/

#if (defined COMPILER_VENDOR_ID)
#error COMPILER_VENDOR_ID is already defined
#endif
/** \brief AUTOSAR vendor identification: Elektrobit Automotive GmbH */
#define COMPILER_VENDOR_ID         1U

/*------------------[AUTOSAR module identification]-------------------------*/

#if (defined COMPILER_MODULE_ID)
#error COMPILER_MODULE_ID already defined
#endif
/** \brief AUTOSAR module identification */
#define COMPILER_MODULE_ID       198U

/*------------------[AUTOSAR release version identification]----------------*/

#if (defined COMPILER_AR_RELEASE_MAJOR_VERSION)
#error COMPILER_AR_RELEASE_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR release major version */
#define COMPILER_AR_RELEASE_MAJOR_VERSION     4U

#if (defined COMPILER_AR_RELEASE_MINOR_VERSION)
#error COMPILER_AR_RELEASE_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR release minor version */
#define COMPILER_AR_RELEASE_MINOR_VERSION     0U

#if (defined COMPILER_AR_RELEASE_REVISION_VERSION)
#error COMPILER_AR_RELEASE_REVISION_VERSION already defined
#endif
/** \brief AUTOSAR release revision version */
#define COMPILER_AR_RELEASE_REVISION_VERSION  3U

/*------------------[AUTOSAR module version identification]------------------*/

#if (defined COMPILER_SW_MAJOR_VERSION)
#error COMPILER_SW_MAJOR_VERSION already defined
#endif
/** \brief AUTOSAR module major version */
#define COMPILER_SW_MAJOR_VERSION    3U

#if (defined COMPILER_SW_MINOR_VERSION)
#error COMPILER_SW_MINOR_VERSION already defined
#endif
/** \brief AUTOSAR module minor version */
#define COMPILER_SW_MINOR_VERSION    2U

#if (defined COMPILER_SW_PATCH_VERSION)
#error COMPILER_SW_PATCH_VERSION already defined
#endif
/** \brief AUTOSAR module patch version */
#define COMPILER_SW_PATCH_VERSION    0U

/*------------------[AUTOSAR module vendor API infix]------------------------*/

#if (defined COMPILER_VENDOR_API_INFIX)
#error COMPILER_VENDOR_API_INFIX already defined
#endif
/** \brief Vendor API infix
 *
 * Left empty as this header does not belong to any module */
#define COMPILER_VENDOR_API_INFIX

/*------------------[storage classes]----------------------------------------*/

#if (defined AUTOMATIC)
#error AUTOMATIC already defined
#endif

/* COMPILER046 */
/** \brief definition of an automatic memory class
 **
 ** To be used for local non static variables */
#define AUTOMATIC

#if (defined TYPEDEF)
#error TYPEDEF already defined
#endif

/* COMPILER059 */
/** \brief definition of an type-definition memory class
 **
 ** To be used within type definitions only */
#define TYPEDEF

#if (defined STATIC)
#error STATIC already defined
#endif

/** \brief abstraction of compiler keyword 'static
 **
 ** values: 'static' or empty */
#define STATIC static

#if (defined _STATIC_)
#error _STATIC_ already defined
#endif

/** \brief map _STATIC_ to value of STATIC for Autosar 2.1 backward compatibility */
#define _STATIC_ static

/*------------------[null pointer constant]----------------------------------*/

#if (defined NULL_PTR)
#error NULL_PTR already defined
#endif

/* COMPILER051 */
/** \brief abstraction of the null pointer constant */
#define NULL_PTR ((void *)0)

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
#endif /* if !defined( COMPILER_COMMON_H ) */
