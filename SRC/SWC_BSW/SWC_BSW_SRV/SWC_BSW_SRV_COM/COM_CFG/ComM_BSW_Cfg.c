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

#include <ComM_BSW.h>                   /* public API symbols */
#include <ComM_BSW_Cfg.h>               /* internal BSW config dependent header */

#if (COMM_CANSM_ACCESS_NEEDED == STD_ON)
#include <CanSM_ComM.h>                 /* Can state manager */
#endif

#if (COMM_FRSM_ACCESS_NEEDED == STD_ON)
#include <FrSm.h>                       /* Flexray state manager */
#endif

#if (COMM_LINSM_ACCESS_NEEDED == STD_ON)
#include <LinSM.h>                      /* Lin state manager */
#endif

/*==================[macros]================================================*/


/** \brief Number of ComM channels needed by user ComMUser_0,
 * ID=0 */
#define COMM_NUM_CHANNELS_OF_USER_0 1U



/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

#define COMM_START_SEC_CONST_8
#include <MemMap.h>

/** \brief User IDs for ComM channel ComMChannel_0, ID=0 */
STATIC CONST(uint8, COMM_CONST)
ComM_UsersOfChannel_0[COMM_NUM_USERS_OF_CHANNEL_0] =
{
  0U, /* user ComMUser_0 */
};


/** \brief  Channel IDs of channels needed by
 * user ComMUser_0, ID=0 */
STATIC CONST(uint8, COMM_CONST)
 ComM_ChannelsOfUser_0[COMM_NUM_CHANNELS_OF_USER_0] =
{
  0U, /* channel ComMChannel_0 */
};

/*---------------[Partial Network Cluster (PNC)]-----------------*/

/*--------[ComM_PncOfUser_X]---------*/

/*--------[ComM_UsersOfPnc_X]---------*/

/*--------[ComM_ChannelsOfPnc_X]---------*/







#define COMM_STOP_SEC_CONST_8
#include <MemMap.h>


/*==================[external constants]====================================*/

#define COMM_START_SEC_CONST_8
#include <MemMap.h>


CONST(uint8, COMM_CONST) ComM_NumChannelsOfUser[COMM_NUM_USERS] =
{
  COMM_NUM_CHANNELS_OF_USER_0, /* for user ComMUser_0 */
};


/*--------[ ComM_NumPncOfUser[ ] ]---------*/
/** \brief Number of Pncs needed by any user */
CONST(uint8, COMM_CONST) ComM_NumPncOfUser[COMM_NUM_USERS] =
{
  COMM_NUM_PNC_OF_USER_0, /* for user ComMUser_0 */
};

/*--------[ ComM_NumUsersOfPnc[ ] ]---------*/

#define COMM_STOP_SEC_CONST_8
#include <MemMap.h>

#define COMM_START_SEC_CONST_16
#include <MemMap.h>

/* Main function period in ms for each channel */
CONST(uint16, COMM_CONST) ComM_MainFunctionPeriodMs[COMM_NUM_CHANNELS] =
{
  20U, /* for channel ComMChannel_0 */
};

#if ((COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)      \
     || (COMM_NM_VARIANT_NONE_NEEDED == STD_ON))
/* Timeout after which state "NetReqNoNm" is left when ComMNmVariant='LIGHT' or
 * 'NONE' */
CONST(uint16, COMM_CONST) ComM_NetReqNoNmTimeoutMs[COMM_NUM_CHANNELS] =
{
  /* for channel ComMChannel_0 */
  250U, /* Nm variant 'LIGHT' or 'NONE' */
};
#endif

#if (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)
/* Timeout after which state "ready sleep" is left in ComMNmVariant=LIGHT */
CONST(uint16, COMM_CONST) ComM_ReadySleepNoNmTimeoutMs[COMM_NUM_CHANNELS] =
{
  /* for channel ComMChannel_0 */
  0U,    /* Nm variant NONE, "ready sleep" state is instantly left */
};
#endif

/* Maximum number of ComM Mainfunction Cycles that the ComM waits for
 * the indication of the requested mode from the State Manager.
 */
CONST(uint16, COMM_CONST) ComM_BusSMIndicationTimeout[COMM_NUM_CHANNELS] =
{
  65535U, /* ComMChannel_0 */
};


#define COMM_STOP_SEC_CONST_16
#include <MemMap.h>

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* !LINKSTO ComM795,1, ComM796,1, ComM797,1, ComM798,1 */
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_ChannelsOfUser[COMM_NUM_USERS] =
{
  ComM_ChannelsOfUser_0, /* for user ComMUser_0 */
};

/* !LINKSTO ComM795,1, ComM796,1, ComM797,1, ComM798,1 */
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_UsersOfChannel[COMM_NUM_CHANNELS] =
{
  ComM_UsersOfChannel_0, /* for channel ComMChannel_0 */
};

CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_PNCsOfChannel[COMM_NUM_CHANNELS] =
{

  NULL_PTR,
};




/*--------[ComM_PncOfUser]---------*/
/** \brief Index of Pnc needed by any user */
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_PncOfUser[COMM_NUM_USERS] =
{
  NULL_PTR, /* No Pnc needed by User[0]. */
};

#if (COMM_NUM_PNC > 0)
/*--------[ComM_UsersOfPnc]---------*/
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_UsersOfPnc[COMM_NUM_PNC] =
{
};

/*--------[ComM_ChannelsOfPnc]---------*/
CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_ChannelsOfPnc[COMM_NUM_PNC] =
{
};

#endif


#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/*==================[internal data]=========================================*/

/*==================[external data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
