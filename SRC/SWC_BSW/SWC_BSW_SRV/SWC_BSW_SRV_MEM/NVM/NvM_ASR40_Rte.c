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
/*==================[inclusions]============================================*/

#include <Std_Types.h>                                                 /* AUTOSAR standard types */
#include <TSAutosar.h>                                             /* EB specific standard types */

#define NVM_INTERNAL_USE
#include <NvM_BSW.h>                                              /* Declaration of Nvm BSW APIs */

#if (NVM_INCLUDE_RTE == STD_ON)
#include <Rte_NvM.h>         /* Declaration of Nvm APIs visible to RTE - consistency enforcement */
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

#if (NVM_INCLUDE_RTE == STD_ON)
#if (NVM_ENABLE_ASR40_SERVICE_API == STD_ON)

#if (NVM_SERVICE_PORT_USED == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_ASR40_Rte_GetErrorStatus
(
  NvM_ASR40_BlockIdType BlockId,
  P2VAR( NvM_ASR40_RequestResultType,AUTOMATIC,NVM_APPL_DATA ) RequestResultPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_GetErrorStatus( BlockId, RequestResultPtr );
  return ret;
}

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
FUNC(Std_ReturnType, NVM_CODE) NvM_ASR40_Rte_SetDataIndex
(
  NvM_ASR40_BlockIdType BlockId, uint8 DataIndex
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_SetDataIndex(BlockId, DataIndex);
  return ret;
}

FUNC(Std_ReturnType, NVM_CODE) NvM_ASR40_Rte_GetDataIndex
(
  NvM_ASR40_BlockIdType                        BlockId,
  P2VAR( uint8,AUTOMATIC,NVM_APPL_DATA ) DataIndex
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_GetDataIndex(BlockId, DataIndex);
  return ret;
}
#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#if (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_ASR40_Rte_SetRamBlockStatus
(
  NvM_ASR40_BlockIdType BlockId,
  boolean         BlockChanged
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_SetRamBlockStatus(BlockId, BlockChanged);
  return ret;
}
#endif  /* (NVM_SET_RAM_BLOCK_STATUS_API == STD_ON) */

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)
#if (defined RTE_TYPE_NvM_Mode32_IndicatorType)
FUNC( Std_ReturnType,NVM_CODE ) NvM_ASR40_Rte_ReadBlock
(
  NvM_ASR40_BlockIdType                        BlockId,
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA)  NvM_DstPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_ReadBlock(BlockId, NvM_DstPtr);
  return ret;
}

FUNC( Std_ReturnType,NVM_CODE ) NvM_ASR40_Rte_WriteBlock
(
  NvM_ASR40_BlockIdType                         BlockId,
  P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_WriteBlock(BlockId, NvM_SrcPtr);
  return ret;
}

FUNC( Std_ReturnType,NVM_CODE ) NvM_ASR40_Rte_RestoreBlockDefaults
(
  NvM_ASR40_BlockIdType                       BlockId,
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_RestoreBlockDefaults(BlockId,  NvM_DestPtr);
  return ret;
}

#else
FUNC( Std_ReturnType,NVM_CODE ) NvM_ASR40_Rte_ReadBlock
(
  NvM_ASR40_BlockIdType                        BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA)  NvM_DstPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_ReadBlock(BlockId, NvM_DstPtr);
  return ret;
}

FUNC( Std_ReturnType,NVM_CODE ) NvM_ASR40_Rte_WriteBlock
(
  NvM_ASR40_BlockIdType                         BlockId,
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_WriteBlock(BlockId, NvM_SrcPtr);
  return ret;
}

FUNC( Std_ReturnType,NVM_CODE ) NvM_ASR40_Rte_RestoreBlockDefaults
(
  NvM_ASR40_BlockIdType                       BlockId,
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_RestoreBlockDefaults(BlockId,  NvM_DestPtr);
  return ret;
}
#endif /* #if (defined RTE_TYPE_NvM_Mode32_IndicatorType) */
#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */
#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3)
#if (NVM_SERVICE_PORT_USED == STD_ON)
#if (NVM_JOB_PRIORITIZATION == STD_ON)
FUNC( Std_ReturnType,NVM_CODE ) NvM_ASR40_Rte_EraseNvBlock
(
  NvM_ASR40_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_EraseNvBlock(BlockId);
  return ret;
}
#endif /* #if (NVM_JOB_PRIORITIZATION == STD_ON) */

FUNC( Std_ReturnType,NVM_CODE )NvM_ASR40_Rte_InvalidateNvBlock
(
  NvM_ASR40_BlockIdType BlockId
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_InvalidateNvBlock(BlockId);
  return ret;
}
#endif /* #if (NVM_SERVICE_PORT_USED == STD_ON) */

#if (NVM_ADMIN_PORT_USED == STD_ON)
FUNC(Std_ReturnType, NVM_CODE) NvM_ASR40_Rte_SetBlockProtection
(
  NvM_ASR40_BlockIdType BlockId,
  boolean         ProtectionEnabled
)
{
  Std_ReturnType ret = E_NOT_OK;
  ret = NvM_ASR40_SetBlockProtection(BlockId, ProtectionEnabled);
  return ret;
}
#endif /* #if (NVM_ADMIN_PORT_USED == STD_ON) */

#endif /* #if (NVM_API_CONFIG_CLASS == NVM_API_CONFIG_CLASS_3) */
#endif /* #if (NVM_ENABLE_ASR40_SERVICE_API == STD_ON) */
#endif /* (NVM_INCLUDE_RTE == STD_ON) */

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

#if ((NVM_INCLUDE_RTE == STD_OFF) &&\
     (NVM_ENABLE_ASR40_SERVICE_API == STD_OFF))

#include <TSCompiler.h>           /* usage of macro in TSCompiler_Default.h */

/* Avoid empty translation unit according to ISO C90 */
TS_PREVENTEMPTYTRANSLATIONUNIT

#endif /* ((NVM_INCLUDE_RTE == STD_OFF) && (NVM_ENABLE_ASR40_SERVICE_API == STD_OFF)) */

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
