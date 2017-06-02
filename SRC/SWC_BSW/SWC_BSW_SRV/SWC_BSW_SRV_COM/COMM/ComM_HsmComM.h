/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#ifndef COMM_HSMCOMM_H
#define COMM_HSMCOMM_H

/* Public interface for the ComM
 * state machine.
 *
 * This file defines the public symbols and functions to use the
 * ComM state machine.
 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>                            /* AUTOSAR standard types */

/* include state machine driver interface */
#include <ComM_Hsm.h>

/*==================[macros]================================================*/

/* Events/signal defined in the ComM state machine. */
#define COMM_HSM_COMM_EV_LIMIT_TO_NO_COM 0U
#define COMM_HSM_COMM_EV_PNC_NM_REQUEST 1U
#define COMM_HSM_COMM_EV_TIMEOUT 2U
#define COMM_HSM_COMM_EV_NM_TIMEOUT 3U
#define COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE 4U
#define COMM_HSM_COMM_EV_BUSSM_RETRY_COUNT_LIMIT 5U
#define COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM 6U
#define COMM_HSM_COMM_EV_ECUM_WAKEUP_IND 7U
#define COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION 8U
#define COMM_HSM_COMM_EV_NM_RESTART_IND 9U
#define COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM 10U
#define COMM_HSM_COMM_EV_COMALLOWED_CHANGED 11U
#define COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE 12U
#define COMM_HSM_COMM_EV_REQ_STATUS_CHANGED 13U
#define COMM_HSM_COMM_EV_NM_NETWORK_MODE 14U
#define COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM 15U
#define COMM_HSM_COMM_EV_BUSSM_TIMEOUT 16U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Initialization data for the statechart statechart ComM */
extern CONST(ComM_HsmStatechartType, COMM_CONST)
 ComM_HsmScComM;

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* defined COMM_HSMCOMM_H */
/*==================[end of file]===========================================*/
