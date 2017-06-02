/**
 * \file
 *
 * \brief AUTOSAR EcuM
 *
 * This file contains the implementation of the AUTOSAR
 * module EcuM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/* !LINKSTO ECUM121_Conf,1 */

/*==================[inclusions]============================================*/

#include <Std_Types.h>    /* AUTOSAR standard types            */

#include <Mcu.h>          /* MCU module types                  */
#include <EcuM_Int.h>     /* EcuM private header               */
#include <EcuM_Cbk.h>

#include <Port.h>
#include <Dem.h>
#include <Dio.h>
#include <Can_17_MCanP.h>
#include <Icu_17_GtmCcu6.h>
#include <Pwm_17_Gtm.h>
#include <Spi.h>
#include <Wdg.h>
#include <Gpt.h>
#include <bswsrv.h>



/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/
#define ECUM_START_SEC_CONST_8
#include <MemMap.h>

/* Wake-up Source ID mapping */
CONST(uint8, ECUM_CONST) EcuM_WksMapping[ECUM_WKS_ID_MAXVAL + 1U] =
{
  0U,
  1U,
  2U,
  3U,
  4U,
  5U,
  6U,
};

#define ECUM_STOP_SEC_CONST_8
#include <MemMap.h>


#define ECUM_START_SEC_CONST_16
#include <MemMap.h>

/* !LINKSTO EcuM4004,1 */
/* timeout for wakeup source */
CONST(uint16, ECUM_CONST) EcuM_WksValTimeout[ECUM_WKSCONFIGNUM] =
{
  0U, /* Timeout for wakeup source ECUM_WKSOURCE_POWER */
  0U, /* Timeout for wakeup source ECUM_WKSOURCE_RESET */
  0U, /* Timeout for wakeup source ECUM_WKSOURCE_INTERNAL_RESET */
  0U, /* Timeout for wakeup source ECUM_WKSOURCE_INTERNAL_WDG */
  0U, /* Timeout for wakeup source ECUM_WKSOURCE_EXTERNAL_WDG */
  0U, /* Timeout for wakeup source EcuMWakeupSource1 */
  0U, /* Timeout for wakeup source EcuMWakeupSource2 */
};

#define ECUM_STOP_SEC_CONST_16
#include <MemMap.h>

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/*------------------[Wakeup Sources]----------------------------------------*/

/* configurations of Wakeup Sources */
CONST(EcuM_WksConfigType, ECUM_CONST) EcuM_WksConfigList[ECUM_WKSCONFIGNUM] =
{
/* !LINKSTO EcuM2166,1 */
  /* ECUM_WKSOURCE_POWER */
  {
    ECUM_NO_COMM_CH,   /* No associated ComM Channel */
    MCU_POWER_ON_RESET,   /* Reset Reason */
    0U   /* Wakeup Source Id */
  },
  /* ECUM_WKSOURCE_RESET */
  {
    ECUM_NO_COMM_CH,   /* No associated ComM Channel */
    MCU_SW_RESET,   /* Reset Reason */
    1U   /* Wakeup Source Id */
  },
  /* ECUM_WKSOURCE_INTERNAL_RESET */
  {
    ECUM_NO_COMM_CH,   /* No associated ComM Channel */
    MCU_SW_RESET,   /* Reset Reason */
    2U   /* Wakeup Source Id */
  },
  /* ECUM_WKSOURCE_INTERNAL_WDG */
  {
    ECUM_NO_COMM_CH,   /* No associated ComM Channel */
    MCU_SUPPLY_WDOG_RESET,   /* Reset Reason */
    3U   /* Wakeup Source Id */
  },
  /* ECUM_WKSOURCE_EXTERNAL_WDG */
  {
    ECUM_NO_COMM_CH,   /* No associated ComM Channel */
    MCU_SUPPLY_WDOG_RESET,   /* Reset Reason */
    4U   /* Wakeup Source Id */
  },
  /* EcuMWakeupSource1 */
  {
    ECUM_NO_COMM_CH,   /* No associated ComM Channel */
    MCU_POWER_ON_RESET,   /* Reset Reason */
    5U   /* Wakeup Source Id */
  },
  /* EcuMWakeupSource2 */
  {
    ECUM_NO_COMM_CH,   /* No associated ComM Channel */
    MCU_POWER_ON_RESET,   /* Reset Reason */
    6U   /* Wakeup Source Id */
  },
};

/*------------------[Sleep Modes]-------------------------------------------*/
CONST(EcuM_SleepModeConfigType, ECUM_CONST) EcuM_SleepModeConfigList[ECUM_SLEEPMODECONFIGNUM] =
{

  {
    
    /* Sleep mode: EcuMSleepMode, ID: 0 */
    #if (defined McuConf_McuModeSettingConf_McuModeSettingConf_0)
    McuConf_McuModeSettingConf_McuModeSettingConf_0,
    #else
    McuModeSettingConf_0,
    #endif
    TRUE, /* Suspend flag */
    ECUM_EcuMSleepMode_WKUP_MASK /* Wakeup event mask of sleep mode EcuMSleepMode */
  },

};

/*------------------[Errors reporting to Dem]-------------------------------------------*/

  /* Errors cannot be reported to DEM since DEM is not includded */

/*------------------[EcuMShutdownCause]-------------------------------------------*/

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
/* Array holding the configured values of Shutdown Causes */
CONST(EcuM_ShutdownCauseType, ECUM_CONST)
   EcuM_ValidShutdownCause[ECUM_SHUTDOWNCAUSECONFIGNUM] =
{
  EcuMConf_EcuMShutdownCause_EcuMShutdownCause,
  EcuMConf_EcuMShutdownCause_ECUM_CAUSE_ECU_STATE,
  EcuMConf_EcuMShutdownCause_ECUM_CAUSE_WDGM,
  EcuMConf_EcuMShutdownCause_ECUM_CAUSE_DCM,
};
#endif

#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>
/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/
#define ECUM_START_SEC_CODE
#include <MemMap.h>
/*------------------[Callouts from STARTUP state]---------------------------*/

/* No content for EcuM_AL_DriverInitZero() configured */

/* Configured Initialization List One items */
FUNC(void, ECUM_CODE) EcuM_DefaultInitListOne(void)
{
  /* *** Call service PreInit of module Dem *** */
  Dem_PreInit(&DemConfigSet_0);
  /* *** Call service Init of module Mcu *** */
  Mcu_Init(&Mcu_ConfigRoot[0]);
  /* *** Call service Init of module Port *** */
  Port_Init(&Port_ConfigRoot[0]);
  /* *** Call service Init of module Dio *** */
  Dio_Init(&Dio_ConfigRoot[0]);
  /* *** Call service Init of module Can_17_MCanP *** */
  Can_17_MCanP_Init(&Can_17_MCanP_ConfigRoot[0]);
  /* *** Call service Init of module Icu_17_GtmCcu6 *** */
  Icu_17_GtmCcu6_Init(&Icu_ConfigRoot[0]);
  /* *** Call service Init of module Pwm_17_Gtm *** */
  Pwm_17_Gtm_Init(&Pwm_ConfigRoot[0]);
  /* *** Call service Init of module Spi *** */
  Spi_Init(&Spi_ConfigRoot[0]);
  /* *** Call service Init of module Wdg *** */
  Wdg_Init(&Wdg_ConfigRoot[0]);
  /* *** Call service Init of module Gpt *** */
  Gpt_Init(&Gpt_ConfigRoot[0]);
  /* *** Call service vidInit of module BSW *** */
  BSW_vidInit();
}

/*------------------[Callouts from SLEEP state]--------------------------*/
/* Configured Driver Restart List items */
FUNC(void, ECUM_CODE) EcuM_DefaultRestartList(void)
{
  /* *** Call service Init of module Mcu *** */
  Mcu_Init(&Mcu_ConfigRoot[0]);
  /* *** Call service Init of module Port *** */
  Port_Init(&Port_ConfigRoot[0]);
}
#define ECUM_STOP_SEC_CODE
#include <MemMap.h>
/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
