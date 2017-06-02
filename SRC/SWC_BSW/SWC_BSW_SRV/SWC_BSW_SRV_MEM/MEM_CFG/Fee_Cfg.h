/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2013)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Fee_Cfg.h $                                                **
**                                                                           **
**  $CC VERSION : \main\21 $                                                 **
**                                                                           **
**  DATE, TIME: 2016-12-15, 16:41:20                                         **
**                                                                           **
**  GENERATOR : Build b141014-0350                                           **
**                                                                           **
**  AUTHOR    : DL-AUTOSAR-Engineering                                       **
**                                                                           **
**  VENDOR    : Infineon Technologies                                        **
**                                                                           **
**  DESCRIPTION  : FEE configuration generated out of ECU configuration      **
**                   file (Fee.bmd)                                          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

#ifndef  FEE_CFG_H
#define  FEE_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* Typedefs Imported from Memory Abstract Interface */ 
#include "MemIf_Types.h"

/* Callback functions imported from NvM Module */
#include "NvM_Cbk.h"

/* Functions imported from Fls Module */
#include "Fls_17_Pmu.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/* FEE AS version information */
#define FEE_AS_VERSION (403)
#define FEE_AR_RELEASE_MAJOR_VERSION  (4U)
#define FEE_AR_RELEASE_MINOR_VERSION  (0U)
#define FEE_AR_RELEASE_REVISION_VERSION  (3U)

/* Vendor specific implementation version information */
#define FEE_SW_MAJOR_VERSION  (2U)
#define FEE_SW_MINOR_VERSION  (3U)
#define FEE_SW_PATCH_VERSION  (2U)

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
                        
/*******************************************************************************
**                    Static configuration parameters                         **
*******************************************************************************/

/* Development error detection enabled/disabled */
#define FEE_DEV_ERROR_DETECT       (STD_OFF)

/* Fee_GetVersionInfo API enabled/disabled */
#define FEE_VERSION_INFO_API       (STD_ON)

/* Fee_GetCycleCount API enabled/disabled */
#define FEE_GET_CYCLE_COUNT_API    (STD_OFF)

/* Fee_SetMode API enabled/disabled */
#define FEE_SET_MODE_SUPPORTED     (STD_ON)

/* Fee_17_GetPrevData API enabled/disabled */
#define FEE_GET_PREV_DATA_API      (STD_OFF)

/* FEE programs state pages upon detection of virgin flash */
#define FEE_VIRGIN_FLASH_ILLEGAL_STATE      (STD_OFF)

/* Enable/Disable Debug support  */
#define FEE_DEBUG_SUPPORT     (STD_OFF)

/* Erase suspend/resume feature supported in FLS */
#define FEE_FLS_SUPPORTS_ERASE_SUSPEND  (STD_ON)

/* DFlash WordLine size */
#define FEE_DFLASH_WORDLINE_SIZE     (512U)

#define FEE_CONTINUE          (0U)
#define FEE_STOP_AT_GC        (1U)

#define FEE_UNCFG_BLK_OVERFLOW_HANDLE    (FEE_CONTINUE)

/* Virtual page size, i.e., DF_EEPROM page size */
#define FEE_VIRTUAL_PAGE_SIZE      (8U)

/* Logical block's overhead in bytes */
#define FEE_BLOCK_OVERHEAD         (17U)

/* Logical block's data page overhead in bytes */
#define FEE_PAGE_OVERHEAD          (1U)

/* Maximum blocking (delay) time in ms */
#define FEE_MAXIMUM_BLOCKING_TIME  (10U)

/* Maximum number of configured blocks to be handled */
#define FEE_MAX_BLOCK_COUNT        (50U)

/* Symbolic names of logical blocks */
#ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID already defined
#else 
#define FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID ((uint16)16)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID */

#ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID1 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID1 already defined
#else 
#define FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID1 ((uint16)17)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_ConfigID1 */

#ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_Dem 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_FeeBlock_NvM_Dem already defined
#else 
#define FeeConf_FeeBlockConfiguration_FeeBlock_NvM_Dem ((uint16)32)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_Dem */

#ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NVM_HCU_DTC 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_FeeBlock_NVM_HCU_DTC already defined
#else 
#define FeeConf_FeeBlockConfiguration_FeeBlock_NVM_HCU_DTC ((uint16)48)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NVM_HCU_DTC */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_DCDC_DTC 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_DCDC_DTC already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_DCDC_DTC ((uint16)64)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_DCDC_DTC */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_CALIB 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_CALIB already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_CALIB ((uint16)80)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_CALIB */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_1 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_1 already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_1 ((uint16)96)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_1 */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_2 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_2 already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_2 ((uint16)112)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_2 */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_3 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_3 already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_3 ((uint16)128)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_3 */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_4 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_4 already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_4 ((uint16)144)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_4 */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_5 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_5 already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_5 ((uint16)160)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_5 */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_6 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_6 already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_6 ((uint16)176)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_6 */

#ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_7 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_7 already defined
#else 
#define FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_7 ((uint16)192)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_Feeblock_NVM_APPRSV_7 */

#ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_DCM 
/* to prevent double declaration */
#error FeeConf_FeeBlockConfiguration_FeeBlock_NvM_DCM already defined
#else 
#define FeeConf_FeeBlockConfiguration_FeeBlock_NvM_DCM ((uint16)208)
#endif /* #ifdef FeeConf_FeeBlockConfiguration_FeeBlock_NvM_DCM */


#define FEE_DISABLE_DEM_REPORT   (0U)
#define FEE_ENABLE_DEM_REPORT    (1U)

/* DEM Configurations */
#define FEE_GC_INIT_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
#define FEE_WRITE_DEM_REPORT         (FEE_DISABLE_DEM_REPORT)
#define FEE_READ_DEM_REPORT          (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_WRITE_DEM_REPORT      (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_READ_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_ERASE_DEM_REPORT      (FEE_DISABLE_DEM_REPORT)
#define FEE_INVALIDATE_DEM_REPORT    (FEE_DISABLE_DEM_REPORT)
#define FEE_WRITE_CYCLES_DEM_REPORT  (FEE_DISABLE_DEM_REPORT)
#define FEE_GC_TRIG_DEM_REPORT       (FEE_DISABLE_DEM_REPORT)
#define FEE_UNCFG_BLK_DEM_REPORT     (FEE_DISABLE_DEM_REPORT)
#define FEE_DEM_ENABLED              (STD_OFF)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

#define FEE_CONFIG_PTR      (Fee_CfgPtr)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#endif /* #ifndef FEE_CFG_H */
