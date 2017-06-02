/**
 * \file
 *
 * \brief AUTOSAR FiM
 *
 * This file contains the implementation of the AUTOSAR
 * module FiM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined FIM_INT_H)
#define FIM_INT_H

/*==================[includes]===============================================*/
/* !LINKSTO dsn.FiM.IncludeStr,1 */

#include <FiM.h>     /* public dependent header */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*------------------[types for "on request" support]-------------------------*/
/* !LINKSTO dsn.FiM.StaticData,1 */

/** \brief Dem Event Id and inhibition mask map */
typedef uint16 FiM_EventCfgType;

/** \brief Configuration structure for FiM "on request" support */
typedef struct
{
  /** \brief ptr to array of assigned events and inh. masks */
  P2CONST(FiM_EventCfgType, TYPEDEF, FIM_CONST) EventCfg;
  /** \brief number of assigned events and masks */
  uint8                                         numEventCfg;
} FiM_FidConfigType;

/*------------------[types for "on event changed" support]-------------------*/
/* !LINKSTO dsn.FiM.StaticData,1 */

/** \brief FID and inhibition mask map */
typedef uint16 FiM_FidCfgType;

/** \brief Configuration structure for FiM "on event changed" support */
typedef struct
{
  /** \brief Event ID */
  Dem_EventIdType                             EventID;
  /** \brief ptr to array of assigned FIDs and inh. masks */
  P2CONST(FiM_FidCfgType, TYPEDEF, FIM_CONST) FidCfg;
  /** \brief number of FIDs and mask assigned to event */
  uint8                                       numFids;
} FiM_EvtConfigType;

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

#define FIM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if (FIM_EVENT_UPDATE_TRIGGERED_BY_DEM == STD_OFF)
/** \brief FiM configuration
 **
 ** It contains the FID (= index) / EventID / inhibition mask relations. */
extern CONST(FiM_FidConfigType, FIM_CONST) FiM_FidConfig[FIM_FID_NUM];

#else

/** \brief FiM configuration
 **
 ** It conatins the EventID / FID / inhibition mask relations. */
extern CONST(FiM_EvtConfigType, FIM_CONST) FiM_EvtConfig[FIM_EVENT_NUM];
#endif

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( FIM_INT_H ) */
/*==================[end of file]============================================*/
