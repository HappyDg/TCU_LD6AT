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
#if (!defined NVM_CALC_CRC_H)
#define NVM_CALC_CRC_H

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 8.12 (required)
 *    "When an array is declared with external linkage, its size shall be
 *           stated explicitely or defined implicitely by initialisation."
 *
 *    Reason: The size is not explicitely stated because it depends on the user
 *           configuration and is unknown when the library is built. Also the
 *           library must work for different user configurations without
 *           rebuild.
 */

/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* EB specific standard types             */
                                  /* standard types                         */
#include <NvM_Int_Types.h>        /* NvM specific internal types            */
#include <NvM_Cfg.h>              /* Generated extern definitions of        */
                                  /* configuration data.                    */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief Calculates remaining CRC data length.
 **        In case of interrupted CRC calculation this function determines the
 **        number of data bytes which must be included in the CRC calculation
 **        in the next step.
 **
 **
 ** \return Number of bytes to be calulated in the next step,
 **         range: 0 .. (2^32)-1
 **
 ** \remarks
 ** - The function is called by NvM_CalcCrc_AsyncState.
 */
extern FUNC(uint32, NVM_CODE) NvM_CalcCrc_UpdateLength(void);

/** \brief Returns the start address in the internal buffer where the CRC is stored.
 **
 ** \revtal address of the CRC buffer which must currently used by the
 **         NvM_ReadBlock() function.
 **         range: 0 .. size of NVM_APPL_DATA
 **
 **/
extern FUNC(NvM_PtrToApplDataType, NVM_CODE) NvM_CalcCrc_GetBlockCrcAddress(void);

/** \brief Returns address of stored RAM CRC.
 **        This function returns the address where the CRC is
 **        stored in RAM for the current NVRAM block.
 **/
extern FUNC(NvM_PtrToApplDataType, NVM_CODE) NvM_GetStoredRamCRCAddress(void);

/** \brief Calculates the CRC for the NVRAM Block.
 **        For the current block defined by NvM_CurrentBlockDescriptorPtr,
 **        CRC is calculated starting from DataAddress.
 **
 ** \param[in]  DataAddress: Start address of the data
 **/
extern FUNC(void, NVM_CODE) NvM_CalculateCrc
(
  NvM_PtrToApplDataType DataAddress
);


/** \brief Copies the CRC for the current NVRAM Block.
 **        For the current block defined by NvM_CurrentBlockDescriptorPtr,
 **        CRC is copied from NvM_SourceAddress to NvM_TargetAddress.
 **
 ** \param[in]  DataAddress: Start address to load CRC
 **/
extern FUNC(void, NVM_CODE) NvM_CopyCrc
(
  NvM_PtrToApplDataType DataAddress
);

/** \brief Verifies calculated CRC with the stored CRC.
 **        For the current block defined by NvM_CurrentBlockDescriptorPtr,
 **        the calculated CRC is compared with the CRC stored at DataAddress.
 **
 ** \param[in]  DataAddress: Start address of the stored CRC
 **
 ** \return    NvM_RequestResultType
 ** \retval    NVM_REQ_OK     Comparison successful
 ** \retval    NVM_REQ_NOT_OK Comparison failed
 **/
extern FUNC(NvM_RequestResultType, NVM_CODE) NvM_CheckCrc
(
  P2CONST(uint8, AUTOMATIC, NVM_APPL_DATA) DataAddress
);

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#endif /* if !defined(NVM_CALC_CRC_H) */
/*==================[end of file]===========================================*/
