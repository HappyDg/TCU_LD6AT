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

/* !LINKSTO ComM503_Refine,1 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>    /* AUTOSAR standard types */

/* prevent RTE symbols defined in ComM.h to be visible for ComM's .c files */
#define COMM_INTERNAL_USAGE

#include <ComM_BSW.h>         /* public API symbols */
#include <ComM_Rte_Cfg.h>    /* internal Rte config dependent header */

#if (COMM_INCLUDE_RTE == STD_ON)
/* Functions defined by RTE: Rte_Mode_UM_*_currentMode() */
/* !LINKSTO ComM506_Refine_Rte,1 */
#include <Rte_ComM.h>
#endif

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

/*==================[external constants]====================================*/

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if (COMM_INCLUDE_RTE == STD_ON)
CONST(ComM_RteSwitchCbkType, COMM_CONST) ComM_RteSwitchCbk[COMM_NUM_USERS] =
{
  /* user ComMUser_0, ID=0 */
  &Rte_Switch_UM_ComMUser_0_currentMode,
};

#if (COMM_CURRENTCHANNELREQUEST_ENABLED == STD_ON)
CONST(ComM_RteWriteCbkType, COMM_CONST) ComM_RteWriteCbk[COMM_NUM_CHANNELS] =
{
  /* channel ComMChannel_0, ID=0 */
  NULL_PTR, /* ComM_CurrentChannelRequest not used for this channel */
};
#endif /* COMM_CURRENTCHANNELREQUEST_ENABLED */
#endif /* COMM_INCLUDE_RTE */

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external data]=========================================*/

#if (COMM_INCLUDE_RTE == STD_ON)

#define COMM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>



VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_RteModeUser[COMM_NUM_USERS];

#define COMM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
