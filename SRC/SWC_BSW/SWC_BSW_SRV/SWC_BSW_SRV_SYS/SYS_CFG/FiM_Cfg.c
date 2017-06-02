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

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.FiM.IncludeStr,1 */

#include <Std_Types.h>         /* AUTOSAR standard types */

#include <Dem.h>               /* Dem event IDs */

#include <FiM.h>               /* Module public API */
#include <FiM_Int.h>           /* Module internal interface */

/*==================[macros]================================================*/

/* bit masks for the inhibition mask configuration part of the event link
 * configuration */

#if (defined FIM_LAST_FAILED_CFG_MASK)
#error FIM_LAST_FAILED_CFG_MASK already defined
#endif
/** \brief FiM last failed configuration mask */
#define FIM_LAST_FAILED_CFG_MASK       (0U << 14U)

#if (defined FIM_NOT_TESTED_CFG_MASK)
#error FIM_NOT_TESTED_CFG_MASK already defined
#endif
/** \brief FiM not tested configuration mask */
#define FIM_NOT_TESTED_CFG_MASK        (1U << 14U)

#if (defined FIM_TESTED_CFG_MASK)
#error FIM_TESTED_CFG_MASK already defined
#endif
/** \brief FiM tested configuration mask */
#define FIM_TESTED_CFG_MASK            (2U << 14U)

#if (defined FIM_TESTED_AND_FAILED_CFG_MASK)
#error FIM_TESTED_AND_FAILED_CFG_MASK already defined
#endif
/** \brief FiM tested and failed configuration mask */
#define FIM_TESTED_AND_FAILED_CFG_MASK (3U << 14U)

/*------------------[Event configuration sizes]-----------------------------*/

/* number of associated events (single and events as part of event summaries)
 * for each FID */

#if (defined FIM_EVENT_CFG_FID_DDVFD_HVLowVoltage_SIZE)
#error FIM_EVENT_CFG_FID_DDVFD_HVLowVoltage_SIZE already defined
#endif
/** \brief Number of associated events for FiM FID_DDVFD_HVLowVoltage */
#define FIM_EVENT_CFG_FID_DDVFD_HVLowVoltage_SIZE 1U

#if (defined FIM_EVENT_CFG_FID_DDVFD_HVHighVoltage_SIZE)
#error FIM_EVENT_CFG_FID_DDVFD_HVHighVoltage_SIZE already defined
#endif
/** \brief Number of associated events for FiM FID_DDVFD_HVHighVoltage */
#define FIM_EVENT_CFG_FID_DDVFD_HVHighVoltage_SIZE 1U

#if (defined FIM_EVENT_CFG_FID_DDVFD_HVDerating_SIZE)
#error FIM_EVENT_CFG_FID_DDVFD_HVDerating_SIZE already defined
#endif
/** \brief Number of associated events for FiM FID_DDVFD_HVDerating */
#define FIM_EVENT_CFG_FID_DDVFD_HVDerating_SIZE 2U

#if (defined FIM_EVENT_CFG_FID_DDVFD_HiOVPPermanentFauSts_SIZE)
#error FIM_EVENT_CFG_FID_DDVFD_HiOVPPermanentFauSts_SIZE already defined
#endif
/** \brief Number of associated events for FiM FID_DDVFD_HiOVPPermanentFauSts */
#define FIM_EVENT_CFG_FID_DDVFD_HiOVPPermanentFauSts_SIZE 1U

#if (defined FIM_EVENT_CFG_FID_DDVFD_HiUVPPermanentFauSts_SIZE)
#error FIM_EVENT_CFG_FID_DDVFD_HiUVPPermanentFauSts_SIZE already defined
#endif
/** \brief Number of associated events for FiM FID_DDVFD_HiUVPPermanentFauSts */
#define FIM_EVENT_CFG_FID_DDVFD_HiUVPPermanentFauSts_SIZE 1U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[internal constants]====================================*/

#define FIM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array of calibrated inhibition mask and Dem events for the FID with
 ** symbolic name "FID_DDVFD_HVLowVoltage" */
STATIC CONST(FiM_EventCfgType, FIM_CONST)
  FiM_EventCfgFID_DDVFD_HVLowVoltage[FIM_EVENT_CFG_FID_DDVFD_HVLowVoltage_SIZE] =
{
  /* single Dem event link */
  FIM_LAST_FAILED_CFG_MASK | DemConf_DemEventParameter_APPL_E_DDVFD_HVLowVoltage,
};

/** \brief Array of calibrated inhibition mask and Dem events for the FID with
 ** symbolic name "FID_DDVFD_HVHighVoltage" */
STATIC CONST(FiM_EventCfgType, FIM_CONST)
  FiM_EventCfgFID_DDVFD_HVHighVoltage[FIM_EVENT_CFG_FID_DDVFD_HVHighVoltage_SIZE] =
{
  /* single Dem event link */
  FIM_LAST_FAILED_CFG_MASK | DemConf_DemEventParameter_APPL_E_DDVFD_HVHighVoltage,
};

/** \brief Array of calibrated inhibition mask and Dem events for the FID with
 ** symbolic name "FID_DDVFD_HVDerating" */
STATIC CONST(FiM_EventCfgType, FIM_CONST)
  FiM_EventCfgFID_DDVFD_HVDerating[FIM_EVENT_CFG_FID_DDVFD_HVDerating_SIZE] =
{
  /* Dem event links of the event summary EVENT_SUMMARY_DDVFD_HVDerating */
  FIM_LAST_FAILED_CFG_MASK | DemConf_DemEventParameter_APPL_E_DDVFD_HVLowVoltage,
  FIM_LAST_FAILED_CFG_MASK | DemConf_DemEventParameter_APPL_E_DDVFD_HVHighVoltage,
};

/** \brief Array of calibrated inhibition mask and Dem events for the FID with
 ** symbolic name "FID_DDVFD_HiOVPPermanentFauSts" */
STATIC CONST(FiM_EventCfgType, FIM_CONST)
  FiM_EventCfgFID_DDVFD_HiOVPPermanentFauSts[FIM_EVENT_CFG_FID_DDVFD_HiOVPPermanentFauSts_SIZE] =
{
  /* single Dem event link */
  FIM_LAST_FAILED_CFG_MASK | DemConf_DemEventParameter_APPL_E_DDVFD_HiOVPPermanentFauSts,
};

/** \brief Array of calibrated inhibition mask and Dem events for the FID with
 ** symbolic name "FID_DDVFD_HiUVPPermanentFauSts" */
STATIC CONST(FiM_EventCfgType, FIM_CONST)
  FiM_EventCfgFID_DDVFD_HiUVPPermanentFauSts[FIM_EVENT_CFG_FID_DDVFD_HiUVPPermanentFauSts_SIZE] =
{
  /* single Dem event link */
  FIM_LAST_FAILED_CFG_MASK | DemConf_DemEventParameter_APPL_E_DDVFD_HiUVPPermanentFauSts,
};

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external constants]====================================*/

#define FIM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

CONST(FiM_ConfigType, FIM_CONST) FiM_Config_0 = 0U;

CONST(FiM_FidConfigType, FIM_CONST) FiM_FidConfig[FIM_FID_NUM] =
{
  /* dummy entry for FID 0 (invalid) */
  {
    NULL_PTR,
    0U
  },
  /* FID: FID_DDVFD_HVLowVoltage */
  {
    FiM_EventCfgFID_DDVFD_HVLowVoltage,
    FIM_EVENT_CFG_FID_DDVFD_HVLowVoltage_SIZE
  },
  /* FID: FID_DDVFD_HVHighVoltage */
  {
    FiM_EventCfgFID_DDVFD_HVHighVoltage,
    FIM_EVENT_CFG_FID_DDVFD_HVHighVoltage_SIZE
  },
  /* FID: FID_DDVFD_HVDerating */
  {
    FiM_EventCfgFID_DDVFD_HVDerating,
    FIM_EVENT_CFG_FID_DDVFD_HVDerating_SIZE
  },
  /* FID: FID_DDVFD_HiOVPPermanentFauSts */
  {
    FiM_EventCfgFID_DDVFD_HiOVPPermanentFauSts,
    FIM_EVENT_CFG_FID_DDVFD_HiOVPPermanentFauSts_SIZE
  },
  /* FID: FID_DDVFD_HiUVPPermanentFauSts */
  {
    FiM_EventCfgFID_DDVFD_HiUVPPermanentFauSts,
    FIM_EVENT_CFG_FID_DDVFD_HiUVPPermanentFauSts_SIZE
  },
};

#define FIM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
