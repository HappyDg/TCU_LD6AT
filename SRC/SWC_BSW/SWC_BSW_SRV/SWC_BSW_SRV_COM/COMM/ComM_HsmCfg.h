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

#ifndef COMM_HSMCFG_H
#define COMM_HSMCFG_H

/* this file must be provided by the user
 *
 * It sets configuration options for the hsm */

/*==================[inclusions]============================================*/
#include <ComM_Cfg.h>       /* Generated module configuration */
/*==================[macros]================================================*/

/** \brief Enable multiple instances of the same statemachine */
#if ((COMM_NUM_CHANNELS > 1U) || (COMM_NUM_PNC > 1U))
#define COMM_HSM_INST_MULTI_ENABLED STD_ON
#else
#define COMM_HSM_INST_MULTI_ENABLED STD_OFF
#endif

/* *** Individual settings for each Hsm model *** */

/** \brief Number of instances of hsm <HSM_NAME>
 *
 * Definition is only needed if COMM_HSM_INST_MULTI_ENABLED==STD_ON */
#define COMM_HSM_COMM_NUM_INST         COMM_NUM_CHANNELS

/* !LINKSTO ComM909,1 */
/** \brief Number of instances of hsm <HSM_NAME>
 *
 * Definition is only needed if COMM_HSM_INST_MULTI_ENABLED==STD_ON */
/* !LINKSTO ComM909,1 */
#define COMM_HSM_COMMPNC_NUM_INST      COMM_NUM_PNC

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif
/*==================[end of file]===========================================*/
