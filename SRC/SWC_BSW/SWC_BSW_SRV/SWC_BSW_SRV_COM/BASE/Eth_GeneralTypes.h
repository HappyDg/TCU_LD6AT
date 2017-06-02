/**
 * \file
 *
 * \brief AUTOSAR Base
 *
 * This file contains the implementation of the AUTOSAR
 * module Base.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#if !defined ETH_GENERAL_TYPES
#define ETH_GENERAL_TYPES

/*==================[inclusions]=============================================*/

#include <ComStack_Types.h> /* basic AUTOSAR type definitions */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/* === Ethernet Driver Types === */

/** \brief Definition of Eth_ModeType **/
#define ETH_OK 0U
#define ETH_E_NOT_OK 1U
#define ETH_E_NO_ACCESS 2U
typedef uint8 Eth_ReturnType;

/** \brief Definition of Eth_ModeType **/
#define ETH_MODE_DOWN 0U
#define ETH_MODE_ACTIVE 1U
typedef uint8 Eth_ModeType;

/** \brief Definition of Eth_StateType **/
#define ETH_STATE_UNINIT 0U
#define ETH_STATE_INIT 1U
#define ETH_STATE_ACTIVE 2U
typedef uint8 Eth_StateType;

/** \brief Definition of Eth_FrameType **/
typedef uint16 Eth_FrameType;

/** \brief Definition of Eth_DataType
 *
 * \note This type is defined as 8 bit wide unsigned integer because
 *       this definition is available on all CPU types.
 **/
typedef uint8 Eth_DataType;

/** \brief Definition of Eth_FilterActionType **/
#define ETH_RECEIVED 0U
#define ETH_NOT_RECEIVED 1U
#define ETH_RECEIVED_MORE_DATA_AVAILABLE 2U
#define ETH_RECEIVED_FRAMES_LOST 3U
typedef uint8 Eth_RxStatusType;

/** \brief Definition of Eth_FilterActionType **/
#define ETH_ADD_TO_FILTER 0U
#define ADD_TO_FILTER 0U /* Compatibility with AUTOSAR 4.1.0 */
#define ETH_REMOVE_FROM_FILTER 1U
#define REMOVE_FROM_FILTER 1U /* Compatibility with AUTOSAR 4.1.0 */
typedef uint8 Eth_FilterActionType;

/* === Ethernet Transceiver Types === */

/** \brief Definition of EthTrcv_ModeType */
#define ETHTRCV_MODE_DOWN 0U
#define ETHTRCV_MODE_ACTIVE 1U
typedef uint8 EthTrcv_ModeType;

/** \brief Definition of EthTrcv_LinkStateType */
#define ETHTRCV_LINK_STATE_DOWN 0U
#define ETHTRCV_LINK_STATE_ACTIVE 1U
typedef uint8 EthTrcv_LinkStateType;

/** \brief Definition of EthTrcv_StateType */
#define ETHTRCV_STATE_UNINIT 0U
#define ETHTRCV_STATE_INIT 1U
#define ETHTRCV_STATE_ACTIVE 2U
typedef uint8 EthTrcv_StateType;

/** \brief Definition of EthTrcv_BaudRateType */
#define ETHTRCV_BAUD_RATE_10MBIT 0U
#define ETHTRCV_BAUD_RATE_100MBIT 1U
#define ETHTRCV_BAUD_RATE_1000MBIT 2U
typedef uint8 EthTrcv_BaudRateType;

/** \brief Definition of EthTrcv_DuplexModeType */
#define ETHTRCV_DUPLEX_MODE_HALF 0U
#define ETHTRCV_DUPLEX_MODE_FULL 1U
typedef uint8 EthTrcv_DuplexModeType;

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
#endif /* ETH_GENERAL_TYPES */
