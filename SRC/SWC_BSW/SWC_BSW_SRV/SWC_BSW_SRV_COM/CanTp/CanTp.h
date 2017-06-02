/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 19.6 (required)
 *   #undef shall not be used.
 *
 *   Reason:
 *   Macro CANTP_NO_PBCFG_REQUIRED may be defined in 
 *   more than one instance which will cause compile
 *   warning.
 */
#if(!defined CANTP_H)
#define CANTP_H
/*==================[inclusions]============================================*/

#include <CanTp_Version.h>        /* CanTp version declarations */
#include <CanTp_Cfg.h>            /* CanTp configuration */

#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_EntryTableApi.h>  /* CanTp entry jumptable */
#else
#include <CanTp_Api.h>            /* CanTp public API */
#endif

/* Exclude post-build-time config include file if requested to do so */ 
#if(!defined CANTP_NO_PBCFG_REQUIRED)
#include <CanTp_PBcfg.h>          /* get AUTOSAR CanTp post build configuration */
#endif /* CANTP_NO_PBCFG_REQUIRED */

/* !LINKSTO CanTp.ASR40.CANTP264,1 */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */

/* !LINKSTO CanTp.ASR40.CANTP264,1 */
#if(CANTP_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/* Deviation MISRA-1 */
#undef CANTP_NO_PBCFG_REQUIRED

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( CANTP_H ) */
/*==================[end of file]===========================================*/
