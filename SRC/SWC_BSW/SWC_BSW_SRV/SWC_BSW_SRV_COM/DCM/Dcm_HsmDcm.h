/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef DCM_HSMDCM_H
#define DCM_HSMDCM_H

/* Public interface for the Dcm
 * state machine.
 *
 * This file defines the public symbols and functions to use the
 * Dcm state machine.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

/* include state machine driver interface */
#include <Dcm_Hsm.h>

/*==================[macros]================================================*/

/** \brief Events/signal defined in the Dcm state machine. */
#define DCM_HSM_DCM_EV_BL_TX_RESPONSE 0U
#define DCM_HSM_DCM_EV_RETURN_FROM_BL 1U
#define DCM_HSM_DCM_EV_TIMEOUT3 2U
#define DCM_HSM_DCM_EV_RX_IND_OK 3U
#define DCM_HSM_DCM_EV_ROE 4U
#define DCM_HSM_DCM_EV_ROE_FINAL_RES 5U
#define DCM_HSM_DCM_EV_RST2DFLTSESS 6U
#define DCM_HSM_DCM_EV_RETRY 7U
#define DCM_HSM_DCM_EV_TIMEOUTPGBUF 8U
#define DCM_HSM_DCM_EV_PROVIDE_TX_BUF 9U
#define DCM_HSM_DCM_EV_PROC_ABORT 10U
#define DCM_HSM_DCM_EV_TX_CONF_NOT_OK 11U
#define DCM_HSM_DCM_EV_TX_CONF_OK 12U
#define DCM_HSM_DCM_EV_FORCE_RCRRP 13U
#define DCM_HSM_DCM_EV_TIMEOUT2 14U
#define DCM_HSM_DCM_EV_RETRY_TX 15U
#define DCM_HSM_DCM_EV_PROCESS_PAGE 16U
#define DCM_HSM_DCM_EV_PROC_DONE 17U
#define DCM_HSM_DCM_EV_TIMEOUTTX 18U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Initialization data for the statechart statechart Dcm */
extern CONST(Dcm_HsmStatechartType, DCM_CONST)
 Dcm_HsmScDcm;

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* defined DCM_HSMDCM_H */
/*==================[end of file]===========================================*/
