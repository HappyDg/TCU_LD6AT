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
#if (!defined COMM_RTE_CFG_H)
#define COMM_RTE_CFG_H

/*==================[inclusions]============================================*/

#include <ComStack_Types.h>  /* AUTOSAR Com Stack standard types */
#include <TSAutosar.h>       /* TS_PROD_* symbols */



/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

#if (COMM_INCLUDE_RTE == STD_ON)

/** \brief Type for Rte mode switch callback functions */
typedef P2FUNC(Std_ReturnType, RTE_CODE, ComM_RteSwitchCbkType)(
  Rte_ModeType_ComMMode mode);



/** \brief Type for Rte data write callback functions */
typedef P2FUNC(Std_ReturnType, RTE_CODE, ComM_RteWriteCbkType)(
  P2CONST(ComM_UserHandleArrayType, AUTOMATIC, RTE_APPL_CONST) data);




#endif
/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if (COMM_INCLUDE_RTE == STD_ON)

/** \brief Rte switch mode callbacks for each user */
extern CONST(ComM_RteSwitchCbkType, COMM_CONST)
  ComM_RteSwitchCbk[COMM_NUM_USERS];



/** \brief Rte data write callbacks for each user */
extern CONST(ComM_RteWriteCbkType, COMM_CONST)
  ComM_RteWriteCbk[COMM_NUM_CHANNELS];




#endif

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#if (COMM_INCLUDE_RTE == STD_ON)

#define COMM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>






/**
 * \brief Communication mode, which was last succeessuflly reported to each user via the default
 *        interface of the Rte.
 */
extern VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_RteModeUser[COMM_NUM_USERS];


#define COMM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( COMM_RTE_CFG_H ) */
/*==================[end of file]===========================================*/
