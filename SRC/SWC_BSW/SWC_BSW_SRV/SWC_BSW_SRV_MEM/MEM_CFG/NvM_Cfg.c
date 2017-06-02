/**
 * \file
 *
 * \brief AUTOSAR NvM
 *
 * This file contains the implementation of the AUTOSAR
 * module NvM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 19.1 (advisory)
 *           "#include statements in a file should only be preceded by other
 *           preprocessor directives or comments."
 *
 *           Reason:
 *           The statements '#define NVM_STOP_SEC_CODE - #include <MemMap.>' at
 *           the end of a code section are required by the AUTOSAR memory mapping
 *           specification which must be implemented for NvM.
 *
 *  MISRA-2) Deviated Rule: 11.1 (required)
 *           "Conversions shall not be performed between a pointer to a function
 *           and any type other than an integral type."
 *
 *           Reason:
 *           The conversion is necessary to initialize the constants with
 *           NULL_PTR.
 *
 *  MISRA-3) Deviated Rule: 19.13 (advisory)
 *           "The # and ## preprocessor operators should not be used."
 *
 *           Reason:
 *           Concatenation(##) operator is used by pre compile time parameter. It doesn't 
 *           have any negative impact on code. 
 *
 *  MISRA-4) Deviated Rule: 13.7 (required)
 *           "Boolean operations whose results are invariant shall not be permitted."
 *
 *           Reason:
 *           The portion of code is necessary and has no side effects.
 *
 */

/*==================[inclusions]=============================================*/

#include <TSAutosar.h>

/* prevent redundant declarations of RTE types */
#define NVM_INTERNAL_USE
/* !LINKSTO NVM554,1 */
#include <NvM.h>
#include <NvM_FunctionIntern.h> /* for initialization of NvM_CalcCrc */
#include <NvM_DataIntern.h>   /* extern definition of NvM_ConfigurationId */
#include <NvM_CalcCrc.h>      /* Extern definitions of unit 'CalcCrc'. */
#include <NvM_UsrHdr.h>

#if (NVM_INCLUDE_RTE == STD_ON)
# include <Rte_NvM.h>
# include <Rte_NvMData.h>
#endif

/*==================[macros]================================================*/


/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

#define NVM_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>
/* !LINKSTO NVM138,1, NVM143,1, NVM443,1, NVM321,1 ,NVM140,1 */
CONST(NvM_BlockDescriptorType,NVM_CONST) NvM_BlockDescriptorTable[NVM_TOTAL_NUMBER_OF_NVRAM_BLOCKS]=
{
  /** \brief  block 0:  NvM internal block, used to manage multi block requests. */
  {
    NULL_PTR,    /* ramBlockDataAddress */
    NULL_PTR,    /* romBlockDataAddress */
    NULL_PTR,    /* initBlockCallback */
    NULL_PTR,    /* singleBlockCallback */
    0U,  /* blockDesc */
    0U,  /* BlockBaseNumber */
    0U,  /* nvBlockLength */
    0xFFFFU,  /* ramBlockCrcIndex */
    0U,  /* nvBlockNum */
    0U,  /* romBlockNum */
    0U,  /* writeRetryLimit */
  },

  /* NVM_BLOCK_NvMBlock_ConfigID */
  {
    &NvM_ConfigurationId[0], /* ramBlockDataAddress */
    &NvM_CompiledConfigurationId, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x0004228aU,  /* blockDesc */
    1U,  /* nvBlockBaseNumber */
    2U,  /* nvBlockLength */
    0U, /* ramBlockCrcIndex */
    
    2U, /* nvBlockNum */
    1U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NvM_DEM */
  {
    &Dem_NvData, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x0004220bU,  /* blockDesc */
    2U,  /* nvBlockBaseNumber */
    108U,  /* nvBlockLength */
    2U, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_HCU_DTC_BLOCK */
  {
    Native_HCU_DTC_Block_RAMAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x0004220bU,  /* blockDesc */
    3U,  /* nvBlockBaseNumber */
    1024U,  /* nvBlockLength */
    6U, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_DCDC_DTC_BLOCK */
  {
    Native_DCDC_DTC_Block_RAMAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x0004220bU,  /* blockDesc */
    4U,  /* nvBlockBaseNumber */
    1024U,  /* nvBlockLength */
    10U, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_CALIB_BLOCK */
  {
    Native_Calib_Block_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x0004220bU,  /* blockDesc */
    5U,  /* nvBlockBaseNumber */
    2048U,  /* nvBlockLength */
    14U, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_APPRESERVED_BLOCK1 */
  {
    Native_AppReserved_Block1_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x0004220bU,  /* blockDesc */
    6U,  /* nvBlockBaseNumber */
    64U,  /* nvBlockLength */
    18U, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_APPRESERVED_BLOCK2 */
  {
    Native_AppReserved_Block2_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x00040200U,  /* blockDesc */
    7U,  /* nvBlockBaseNumber */
    64U,  /* nvBlockLength */
    0xFFFFU, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_APPRESERVED_BLOCK3 */
  {
    Native_AppReserved_Block3_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x00040200U,  /* blockDesc */
    8U,  /* nvBlockBaseNumber */
    128U,  /* nvBlockLength */
    0xFFFFU, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_APPRESERVED_BLOCK4 */
  {
    Native_AppReserved_Block4_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x00040200U,  /* blockDesc */
    9U,  /* nvBlockBaseNumber */
    128U,  /* nvBlockLength */
    0xFFFFU, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_APPRESERVED_BLOCK5 */
  {
    Native_AppReserved_Block5_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x00040200U,  /* blockDesc */
    10U,  /* nvBlockBaseNumber */
    512U,  /* nvBlockLength */
    0xFFFFU, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_APPRESERVED_BLOCK6 */
  {
    Native_AppReserved_Block6_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x00040200U,  /* blockDesc */
    11U,  /* nvBlockBaseNumber */
    1024U,  /* nvBlockLength */
    0xFFFFU, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NVM_NATIVE_APPRESERVED_BLOCK7 */
  {
    Native_AppReserved_Block7_RamAddress, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x00040200U,  /* blockDesc */
    12U,  /* nvBlockBaseNumber */
    2048U,  /* nvBlockLength */
    0xFFFFU, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  },

  /* NVM_BLOCK_NvM_DCM */
  {
    Dcm_NvData, /* ramBlockDataAddress */
    NULL_PTR, /* romBlockDataAddress */
    NULL_PTR, /* initBlockCallback */
    NULL_PTR, /* singleBlockCallback */
    0x00040200U,  /* blockDesc */
    13U,  /* nvBlockBaseNumber */
    128U,  /* nvBlockLength */
    0xFFFFU, /* ramBlockCrcIndex */
    
    1U, /* nvBlockNum */
    0U, /* romBlockNum */
    3U,  /* writeRetryLimit */
    
  }
}; /* NvM_BlockDescriptorTable */

#define NVM_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

#define NVM_START_CONFIG_DATA_APPL_DATA
#include <MemMap.h>


VAR(uint32,NVM_APPL_DATA) NvM_CalcCrc_CalcBuffer;


#define NVM_STOP_CONFIG_DATA_APPL_DATA
#include <MemMap.h>

#define NVM_START_CONFIG_DATA_APPL_CONST
#include <MemMap.h>
/* !LINKSTO NVM034,1 */
CONST(uint16,NVM_APPL_CONST) NvM_CompiledConfigurationId = 0x1U;

#define NVM_STOP_CONFIG_DATA_APPL_CONST
#include <MemMap.h>

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
