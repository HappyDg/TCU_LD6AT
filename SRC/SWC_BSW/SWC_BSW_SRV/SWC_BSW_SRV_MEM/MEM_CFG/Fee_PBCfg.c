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
**  $FILENAME   : Fee_PBCfg.c $                                              **
**                                                                           **
**  $CC VERSION : \main\18 $                                                 **
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

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Include Fee Module Header File */
#include "Fee.h"

/*******************************************************************************
**                      Imported Compiler Switch Checks                       **
*******************************************************************************/

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/* Allocate space for state data variables in RAM */
#define FEE_START_SEC_VAR_FAST_UNSPECIFIED
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is
 allowed only for MemMap.h*/
#include "MemMap.h"

/* Fee State Variable structure */
static Fee_StateDataType Fee_StateVar;

#define FEE_STOP_SEC_VAR_FAST_UNSPECIFIED
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is
 allowed only for MemMap.h*/
#include "MemMap.h"


/* User configured logical block initialization structure */
#define FEE_START_SEC_CONST_UNSPECIFIED
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is
 allowed only for MemMap.h*/
#include "MemMap.h"

static const Fee_BlockType Fee_BlockConfig[] =
{
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    16U, /* Block number */
    4U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    17U, /* Block number */
    4U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    32U, /* Block number */
    112U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    48U, /* Block number */
    1028U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    64U, /* Block number */
    1028U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    80U, /* Block number */
    2052U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    96U, /* Block number */
    68U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    112U, /* Block number */
    64U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    128U, /* Block number */
    128U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    144U, /* Block number */
    128U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    160U, /* Block number */
    512U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    176U, /* Block number */
    1024U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    192U, /* Block number */
    2048U /* Fee Block Size */
  },
  {
    0U, /* Block Cycle Count */
    (uint8)FEE_NORMAL_DATA,     /* Block type is Normal */
    208U, /* Block number */
    128U /* Fee Block Size */
  }
};

/* Fee Global initialization structure. */
const Fee_ConfigType Fee_ConfigRoot[] =
{
  {
    /* Fee State Data Structure */
    &Fee_StateVar,
    /* Pointer to logical block configurations */
    &Fee_BlockConfig[0],
    /* Fee Job end notification API */
    &NvM_JobEndNotification,
    /* Fee Job error notification API */
    &NvM_JobErrorNotification,
    /* Fee threshold value */
    200U,
    /* Number of blocks configured */
    14U,

    {
      /* Keep the unconfigured blocks */
      FEE_UNCONFIG_BLOCK_KEEP,
      /* Restart Garbage Collection during initialization */
      FEE_GC_RESTART_INIT,
      /* Erase Suspend feature is enabled */
      FEE_ERASE_SUSPEND_ENABLED,
      /* Reserved */
      0U
    },

    /* Fee Illegal State notification */
    (Fee_NotifFunctionPtrType)NULL_PTR,
    /* Erase All feature is enabled */
    (boolean)TRUE
  }
};

#define FEE_STOP_SEC_CONST_UNSPECIFIED
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is
 allowed only for MemMap.h*/
#include "MemMap.h"

#define FEE_START_SEC_SPL_VAR_32BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is
 allowed only for MemMap.h*/
#include "MemMap.h"
const Fee_ConfigType * Fee_CfgPtr = &Fee_ConfigRoot[0];
#define FEE_STOP_SEC_SPL_VAR_32BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is
 allowed only for MemMap.h*/
#include "MemMap.h"

