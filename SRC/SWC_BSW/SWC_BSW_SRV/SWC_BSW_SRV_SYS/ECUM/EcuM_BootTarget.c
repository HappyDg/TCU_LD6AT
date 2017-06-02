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

/* !LINKSTO EcuM3023,1 */
/*==================[inclusions]============================================*/

#include <EcuM_Trace.h>
#include <Std_Types.h>          /* AUTOSAR standard types */

/* define guard symbol to prevent redundant declaration of RTE symbols */
#define ECUM_INTERNAL_USE

/* no dependency to EcuM.h: EcuM_BootTarget.c may be used in the boot loader
 * or boot manager were the full EcuM implementation is not available. */
#include <EcuM_BootTarget.h>    /* own API */

# include <EcuM_Int.h>          /* symbols for SchM wrappers and Det checks */

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
# include <Det.h>               /* Det API */
#endif

/* see comments in EcuM_BootTarget.h if you use this file in your bootloader
 * or boot manager */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#if (ECUM_USE_BOOTTARGET_SEC == STD_ON)
#define ECUM_START_SEC_ECUM_BOOTTARGET
#else
#define ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#endif
#include <MemMap.h>

/* Boot target */
VAR(EcuM_BootTargetInternalType, ECUM_VAR_BOOTTARGET) EcuM_BootTarget;

#if (ECUM_USE_BOOTTARGET_SEC == STD_ON)
#define ECUM_STOP_SEC_ECUM_BOOTTARGET
#else
#define ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#endif
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

#define ECUM_START_SEC_CODE
#include <MemMap.h>

/*------------------[EcuM_SelectBootTarget]---------------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_SelectBootTarget
(
    EcuM_ASR40_BootTargetType target
)
{
  Std_ReturnType ret = E_NOT_OK;

  DBG_ECUM_SELECTBOOTTARGET_ENTRY(target);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SEL_BOOT_TAR, ECUM_E_UNINIT);
  }
  else if (
    ((target != ECUM_BOOT_TARGET_APP) &&
     (target != ECUM_BOOT_TARGET_OEM_BOOTLOADER)) &&
    (target != ECUM_BOOT_TARGET_SYS_BOOTLOADER))
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_SEL_BOOT_TAR, ECUM_E_INVALID_PAR);
  }
  else
#endif /* (ECUM_DEV_ERROR_DETECT == STD_ON) */
  {
    ret = E_OK;
    EcuM_Enter_SCHM_ECUM_EXCLUSIVE_AREA_0();

    /* !LINKSTO EcuM2247,1 */
    if (target == ECUM_BOOT_TARGET_OEM_BOOTLOADER)
    {
      EcuM_BootTarget[0] = ECUM_BOOT_TARGET_OEM_BOOTLOADER_INTERNAL_0;
      EcuM_BootTarget[1] = ECUM_BOOT_TARGET_OEM_BOOTLOADER_INTERNAL_1;
    }
    else if (target == ECUM_BOOT_TARGET_SYS_BOOTLOADER)
    {
      EcuM_BootTarget[0] = ECUM_BOOT_TARGET_SYS_BOOTLOADER_INTERNAL_0;
      EcuM_BootTarget[1] = ECUM_BOOT_TARGET_SYS_BOOTLOADER_INTERNAL_1;
    }
    else
    {
      EcuM_BootTarget[0] = ECUM_BOOT_TARGET_APP;
      EcuM_BootTarget[1] = ECUM_BOOT_TARGET_APP;
    }

    EcuM_Exit_SCHM_ECUM_EXCLUSIVE_AREA_0();
  }

  DBG_ECUM_SELECTBOOTTARGET_EXIT(ret,target);
  return ret;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_SelectBootTarget
(
    EcuM_ASR32_BootTargetType target
)
{
  Std_ReturnType ret = E_NOT_OK;

  /* EcuM_ASR32_BootTargetType and EcuM_ASR40_BootTargetType are referencing to
   * the same base type. Therefore no argument type mapping is done. */
  ret = EcuM_ASR40_SelectBootTarget(target);

  return ret;
}
#endif
/*------------------[EcuM_GetBootTarget]------------------------------------*/
/* !LINKSTO EcuM.EB.ASR32.EcuM106,1 */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR40_GetBootTarget
(
  P2VAR(EcuM_ASR40_BootTargetType, AUTOMATIC, RTE_APPL_DATA) target
)
{
  Std_ReturnType ret = E_NOT_OK;

  DBG_ECUM_GETBOOTTARGET_ENTRY(target);

#if (ECUM_DEV_ERROR_DETECT == STD_ON)
  if (EcuM_State == ECUM_STATE_UNINIT)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_BOOT_TAR, ECUM_E_UNINIT);
  }
  else if (target == NULL_PTR)
  {
    ECUM_DET_REPORT_ERROR(ECUM_SID_GET_BOOT_TAR, ECUM_E_NULL_POINTER);
  }
  else
#endif
  {
    ret = E_OK;

    /* Translate internal boot target type */
    if ((EcuM_BootTarget[0] == ECUM_BOOT_TARGET_OEM_BOOTLOADER_INTERNAL_0)
        && (EcuM_BootTarget[1] == ECUM_BOOT_TARGET_OEM_BOOTLOADER_INTERNAL_1))
    {
      *target = ECUM_BOOT_TARGET_OEM_BOOTLOADER;
    }
    else if (
      (EcuM_BootTarget[0] == ECUM_BOOT_TARGET_SYS_BOOTLOADER_INTERNAL_0)
      && (EcuM_BootTarget[1] == ECUM_BOOT_TARGET_SYS_BOOTLOADER_INTERNAL_1))
    {
      *target = ECUM_BOOT_TARGET_SYS_BOOTLOADER;
    }
    else
    {
      *target = ECUM_BOOT_TARGET_APP;
    }
  }


  DBG_ECUM_GETBOOTTARGET_EXIT(ret,target);
  return ret;
}

/* !LINKSTO EcuM.EB.ASR32.EcuM107,1 */
#if ((ECUM_EB_ENABLE_ASR32_SERVICE_API == STD_ON) || \
    (ECUM_EB_DEFAULT_ASR_SERVICE_API == ECUM_EB_SERVICE_API_ASR32))
FUNC(Std_ReturnType, ECUM_CODE) EcuM_ASR32_GetBootTarget
(
  P2VAR(EcuM_ASR32_BootTargetType, AUTOMATIC, RTE_APPL_DATA) target
)
{
  Std_ReturnType ret = E_NOT_OK;

  /* EcuM_ASR32_BootTargetType and EcuM_ASR40_BootTargetType are referencing to
   * the same base type. Therefore no argument type mapping is done. */
  ret = EcuM_ASR40_GetBootTarget(target);

  return ret;
}
#endif

#define ECUM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
