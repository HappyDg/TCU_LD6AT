#if !defined(BSWM_CFG_H)
#define BSWM_CFG_H

/**
 * \file
 *
 * \brief AUTOSAR BswM
 *
 * This file contains the implementation of the AUTOSAR
 * module BswM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

 /* \addtogroup Mode Management Stack
  * @{ */

#include <TSAutosar.h>        /* EB specific standard types*/
#include <Std_Types.h>        /* AUTOSAR standard types    */

/* BswMGeneral */

/* Switches related to ModeRequestPorts */
#define BSWM_DEV_ERROR_DETECT STD_OFF
#define BSWM_VERSION_INFO_API STD_ON
#define BSWM_LINSM_API_ENABLED STD_OFF
#define BSWM_LINTP_API_ENABLED STD_OFF
#define BSWM_CANSM_API_ENABLED STD_OFF
#define BSWM_DCM_API_ENABLED STD_ON
#define BSWM_ETHSM_API_ENABLED STD_OFF
#define BSWM_ECUM_API_ENABLED STD_OFF
#define BSWM_COMM_API_ENABLED STD_ON
#define BSWM_WDGM_API_ENABLED STD_OFF
#define BSWM_FRSM_API_ENABLED STD_OFF
#define BSWM_NVM_API_ENABLED STD_OFF
#define BSWM_SD_API_ENABLED STD_OFF
#define BSWM_GENERIC_REQUEST_API_ENABLED STD_OFF

#define BSWM_RTE_ENABLED STD_OFF
#define BSWM_SCHM_ENABLED STD_OFF
#define BSWM_DEM_ENABLED STD_OFF

/* Switches related to actions */
#define BSWM_COM_ACTION_USED STD_OFF
#define BSWM_PDUR_ACTION_USED STD_OFF
#define BSWM_NM_ACTION_USED STD_OFF

#define BSWM_MAX_MODE_ID 0U
#define BSWM_MAX_USER_ID 0U
#define BSWM_CHECK_MAX_USER STD_ON
#define BSWM_CHECK_MAX_MODE STD_ON

/* Type definitions */

/** @} doxygen end group definition */
#endif /* !defined(BSWM_CFG_H) */
/*==================[end of file]============================================*/

