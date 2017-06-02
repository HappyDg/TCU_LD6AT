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

/*==================[inclusions]=============================================*/
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_Types.h>        /* Module public types */
#include <CanTp_Api.h>         /* Module public API */
#include <CanTp_Internal.h>    /* internal macros and variables */
#include <CanTp_InternalCfg.h> /* CanTp internal configuration */


#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_EntryTable.h>  /* CanTp entry jumptable */
#endif /* CANTP_JUMPTABLE_SUPPORT == STD_ON */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/


#define CANTP_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>


#if(CANTP_DYNAMIC_NSA_ENABLED == STD_ON)
/** \brief If dynamic setting of N_SA values is enabled, the N_SA values are
 *         stored in following array.
 */
VAR(uint8, CANTP_VAR) CanTp_NSaValues[CANTP_MAX_RX_NSDUS + CANTP_MAX_FC_PDUS];
#endif

#define CANTP_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>




#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

VAR(CanTp_ChannelType, CANTP_VAR) CanTp_Channel[CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS];

#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>


#define CANTP_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>
/** \brief Internal CanTp variables to be initialized by the C startup code */
/* !LINKSTO CanTp.JTM_0023, 1, CanTp.EB.JTM_11579, 1 */
VAR(CanTp_InitVariableType, CANTP_VAR) CanTp_InitVars =
  {
    CANTP_OFF,                /* default state */
  };
#define CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#define CANTP_START_SEC_CODE
#include <MemMap.h>


#define CANTP_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/


