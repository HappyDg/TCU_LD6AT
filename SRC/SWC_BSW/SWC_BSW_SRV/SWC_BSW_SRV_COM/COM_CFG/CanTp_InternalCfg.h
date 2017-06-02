/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#if(!defined CANTP_INTERNALCFG_H)
#define CANTP_INTERNALCFG_H

/*==================[includes]===============================================*/
#include <TSAutosar.h>              /* EB specific standard types */
#include <CanTp_InternalLib.h>      /* internal macros and variables */
#include <CanTp_Cfg.h>              /* CanTp configuration */

/*==================[macros]=================================================*/

/** \brief defines padding value for unused bytes */
#define CANTP_PADDING_BYTE                0U

/** \def CANTP_GET_ADDR_FORMAT(PduPtr)
 **
 ** \brief Macro to read the addressing format of N-PDUs
 **
 ** This macro is used to read the addressing format of the N-PDU given
 ** as a pointer as parameter.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNPduTableType,
 **            CanTp_RxNSduConfigType or CanTp_TxNSduConfigType
 **
 ** \return CanTp addressing format
 */
#define CANTP_GET_ADDR_FORMAT(PduPtr)         ((PduPtr)->AddressingFormat)

/** \def CANTP_GET_CH_MODE(PduPtr)
 **
 ** \brief Macro to read the channel mode
 **
 ** This macro is used to read the mode of channel corresponding to N-PDU given
 ** as a pointer as parameter.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNPduTableType,
 **            CanTp_RxNSduConfigType or CanTp_TxNSduConfigType
 **
 ** \return CanTp Channel mode
 */
#define CANTP_GET_CH_MODE(PduPtr)             ((PduPtr)->ChannelMode)

/** \def CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId)
 **
 ** \brief Macro to read the block size format of Rx N-PDUs
 **
 ** This macro is used to read the block size (BS)
 **
 ** \param[in] NSduId N-SDU ID of the Rx PDU
 **
 ** \return Block size of the Rx N-SDU
 */
#define CANTP_GET_RX_PDU_BLOCK_SIZE(NSduId)   (CANTP_CFG_GET_RXNSDU_CONFIG(NSduId).BS)

/** \brief Macro to write the block size format of Rx N-PDUs
 **
 ** This macro is used to write the block size (BS) of the Rx N-PDU given
 ** as N-SduId. This macro is only active if the API CanTp_ChangeParameter() is
 ** enabled and therefore it is allowed to change the block size during runtime.
 ** Otherwise the block size is a read-only parameter.
 **
 ** \param[in] NSduId N-SDU ID of the Rx PDU
 ** \param[in] value new value for the block size
 **
 ** \return Block size of the Rx N-SDU
 */


/** \def CANTP_GET_PDU_PADDING(PduPtr)
 **
 ** \brief Macro to read the padding configuration of all N-PDUs
 **
 ** This macro is used to read the padding configuration of the N-PDU given
 ** as a pointer as parameter.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNSduConfigType or
 **                   CanTp_TxNSduConfigType
 **
 ** \return Padding configuration of the N-SDU
 */
#define CANTP_GET_PDU_PADDING(PduPtr)         ((PduPtr)->PaddingActivation)


/** \brief Get N_Ar for a Rx PDU
 **
 ** This macro is used to read the N_Ar TP parameter for the given Rx N-SDU.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNSduConfigType
 */
#define CANTP_GET_RX_PDU_N_AR(PduPtr)         ((PduPtr)->N_Ar)



/** \brief Get N_Br for a Rx PDU
 **
 ** This macro is used to read the N_Br TP parameter for the given Rx N-SDU.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNSduConfigType
 */
#define CANTP_GET_RX_PDU_N_BR(PduPtr)         ((PduPtr)->N_Br)



/** \brief Get N_Cr for a Rx PDU
 **
 ** This macro is used to read the N_Cr TP parameter for the given Rx N-SDU.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNSduConfigType
 */
#define CANTP_GET_RX_PDU_N_CR(PduPtr)         ((PduPtr)->N_Cr)



/** \brief Get maximum number of wait frames for a Rx PDU
 **
 ** This macro is used to read the WftMax parameter for the given Rx N-SDU.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNSduConfigType
 */
#define CANTP_GET_RX_PDU_WFT_MAX(PduPtr)      ((PduPtr)->WftMax)



/** \brief Get minimum separation time (STmin) for a Rx PDU
 **
 ** This macro is used to read the STmin parameter for the given Rx N-SDU.
 **
 ** \param[in] NSduId N-SDU ID of the Rx PDU
 */
#define CANTP_GET_RX_PDU_ST_MIN(NSduId)       CANTP_CFG_GET_RXNSDU_CONFIG((NSduId)).STmin;




/** \brief Get N_As for a Tx PDU
 **
 ** This macro is used to read the N_As TP parameter for the given Tx N-SDU.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_TxNSduConfigType
 */
#define CANTP_GET_TX_PDU_N_AS(PduPtr)         ((PduPtr)->N_As)



/** \def CANTP_GET_TX_PDU_N_BS(PduPtr)
 **
 ** \brief Get N_Bs for a Tx PDU
 **
 ** This macro is used to read the N_Bs TP parameter for the given Tx N-SDU.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_TxNSduConfigType
 */
#define CANTP_GET_TX_PDU_N_BS(PduPtr)         ((PduPtr)->N_Bs)



/** \def CANTP_GET_TX_PDU_N_CS(PduPtr)
 **
 ** \brief Get N_Cs for a Tx PDU
 **
 ** This macro is used to read the N_Cs TP parameter for the given Tx N-SDU.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_TxNSduConfigType
 */
#define CANTP_GET_TX_PDU_N_CS(PduPtr)         ((PduPtr)->N_Cs)

/*==================[type definitions]=======================================*/

/** \brief Type for CanTp internal variables that shall be initialized during
 **        startup. */
typedef struct
{
  uint8 State;    /**< CanTp state (CANTP_ON/CANTP_OFF) */
} CanTp_InitVariableType;

/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/
#define CANTP_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>


#if(CANTP_DYNAMIC_NSA_ENABLED == STD_ON)
/** \brief If dynamic setting of N_SA values is enabled, the N_SA values are
 *         stored in following array
 */
extern VAR(uint8, CANTP_VAR) CanTp_NSaValues[CANTP_MAX_RX_NSDUS + CANTP_MAX_FC_PDUS];
#endif

#define CANTP_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>


#define CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief CanTp channel state(s) */
extern VAR(CanTp_ChannelType, CANTP_VAR) CanTp_Channel[CANTP_MAX_TX_CHANNELS + CANTP_MAX_RX_CHANNELS];


#define CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>


#define CANTP_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Internal CanTp variables to be initialized by the C startup code */
extern VAR(CanTp_InitVariableType, CANTP_VAR) CanTp_InitVars;

#define CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function declarations]=========================*/

/*==================[end of file]============================================*/
#endif /* if !defined( CANTP_INTERNALCFG_H ) */
