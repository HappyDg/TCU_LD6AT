/**
 * \file
 *
 * \brief AUTOSAR CanIf
 *
 * This file contains the implementation of the AUTOSAR
 * module CanIf.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#if (!defined CANIF_API_H)
#define CANIF_API_H

/*
 *  Misra-C:2004 Deviations:
 *
 *  MISRA-1) Deviated Rule: 1.4 (required)
 *    The compiler/linker shall be checked to ensure that 31 character
 *    significance and case sensitivity are supported for external
 *    identifiers.
 *
 *    Reason:
 *    Name defined by AUTOSAR.
 *
 *  MISRA-2) Deviated Rule: 5.1 (required)
 *    Identifiers (internal and external) shall not rely on the significance
 *    of more then 31 characters.
 *
 *    Reason:
 *    Name defined by AUTOSAR.
 */

/*==================[inclusions]=============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR COM types */
#include <CanIf_Version.h>      /* CanIf version declaration */
#include <CanIf_Cfg.h>          /* CanIf configuration */
#include <CanIf_Types.h>        /* CanIf type definitions */
#include <CanIf_Types_Int.h>    /* CanIf PostBuild type definitions */
#if (CANIF_PBCFGM_SUPPORT_ENABLED == STD_ON)

#include <PbcfgM_Api.h>         /* Post build configuration manager */
#endif /* CANIF_PBCFGM_SUPPORT_ENABLED */
/*==================[macros]=================================================*/

/*------------------[API service IDs]----------------------------------------*/

/** \brief CanIf_Init() service ID */
#define CANIF_SID_INIT                      0x01U

/** \brief CanIf_SetControllerMode() service ID */
#define CANIF_SID_SETCONTROLLERMODE         0x03U

/** \brief CanIf_GetControllerMode() service ID */
#define CANIF_SID_GETCONTROLLERMODE         0x04U

/** \brief CanIf_Transmit() service ID */
#define CANIF_SID_TRANSMIT                  0x05U

/** \brief CanIf_CancelTransmit() service ID */
#define CANIF_SID_CANCELTRANSMIT            0x18U

/** \brief CanIf_ReadRxPduData() service ID */
#define CANIF_SID_READRXPDUDATA             0x06U

/** \brief CanIf_ReadTxNotifStatus() service ID */
#define CANIF_SID_READTXNOTIFSTATUS         0x07U

/** \brief CanIf_ReadRxNotifStatus() service ID */
#define CANIF_SID_READRXNOTIFSTATUS         0x08U

/** \brief CanIf_SetPduMode() service ID */
#define CANIF_SID_SETPDUMODE                0x09U

/** \brief CanIf_GetPduMode() service ID */
#define CANIF_SID_GETPDUMODE                0x0aU

/** \brief CanIf_GetVersionInfo() service ID */
#define CANIF_SID_GETVERSIONINFO            0x0bU

/** \brief CanIf_SetDynamicTxId() service ID */
#define CANIF_SID_SETDYNAMICTXID            0x0cU

/** \brief CanIf_SetTrcvMode() service ID */
#define CANIF_SID_SETTRANSCEIVERMODE        0x0dU

/** \brief CanIf_GetTrcvMode() service ID */
#define CANIF_SID_GETTRANSCEIVERMODE        0x0eU

/** \brief CanIf_GetTrcvWakeupReason() service ID */
#define CANIF_SID_GETTRCVWAKEUPREASON       0x0fU

/** \brief CanIf_SetTrcvWakeupMode() service ID */
#define CANIF_SID_SETTRCVWAKEUPMODE         0x10U

/** \brief CanIf_CheckWakeup() service ID */
#define CANIF_SID_CHECKWAKEUP               0x11U

/** \brief CanIf_CheckValidation() service ID */
#define CANIF_SID_CHECKVALIDATION           0x12U

/** \brief CanIf_GetTxConfirmationState() service ID */
#define CANIF_SID_GETTXCONFIRMSTATE         0x19U

/** \brief CanIf_ClearTrcvWufFlag() service ID */
#define CANIF_SID_CLEARTRCVWUFFLAG          0x1eU

/** \brief CanIf_CheckTrcvWakeFlag() service ID */
#define CANIF_SID_CHECKTRCVWAKEFLAG         0x1fU

/** \brief CanIf_TxConfirmation() service ID */
#define CANIF_SID_TXCONFIRMATION            0x13U

/** \brief CanIf_RxIndication() service ID */
#define CANIF_SID_RXINDICATION              0x14U

/** \brief CanIf_CancelTxConfirmation() service ID */
#define CANIF_SID_CANCELTXCONFIRMATION      0x15U

/** \brief CanIf_ControllerBusOff() service ID */
#define CANIF_SID_CONTROLLERBUSOFF          0x16U

/** \brief CanIf_ControllerModeIndication() service ID */
#define CANIF_SID_CONTROLLERMODEIND         0x17U

/** \brief CanIf_TrcvModeIndication() service ID */
#define CANIF_SID_TRANSCEIVERMODEIND        0x18U

/** \brief CanIf_ConfirmPnAvailability() service ID */
#define CANIF_SID_CONFIRMPNAVAILABILITY     0x1aU

/** \brief CanIf_ClearTrcvWufFlagIndication() service ID */
#define CANIF_SID_CLEARTRCVWUFFLAGIND       0x20U

/** \brief CanIf_CheckTrcvWakeFlagIndication() service ID */
#define CANIF_SID_CHECKTRCVWAKEFLAGIND      0x21U

/*------------------[Development error codes]--------------------------------*/

/** \brief CANIF_E_PARAM_CANID */
#define CANIF_E_PARAM_CANID                 10U

/** \brief CANIF_E_PARAM_DLC */
#define CANIF_E_PARAM_DLC                   11U

/** \brief CANIF_E_PARAM_HRH */
#define CANIF_E_PARAM_HRH                   12U

/** \brief CANIF_E_PARAM_LPDU */
#define CANIF_E_PARAM_LPDU                  13U

/** \brief CANIF_E_PARAM_CONTROLLER */
#define CANIF_E_PARAM_CONTROLLER            14U

/** \brief CANIF_E_PARAM_CONTROLLERID */
#define CANIF_E_PARAM_CONTROLLERID          15U

/** \brief CANIF_E_PARAM_WAKEUPSOURCE */
#define CANIF_E_PARAM_WAKEUPSOURCE          16U

/** \brief CANIF_E_PARAM_TRCV */
#define CANIF_E_PARAM_TRCV                  17U

/** \brief CANIF_E_PARAM_TRCVMODE */
#define CANIF_E_PARAM_TRCVMODE              18U

/** \brief CANIF_E_PARAM_TRCVWAKEUPMODE */
#define CANIF_E_PARAM_TRCVWAKEUPMODE        19U

/** \brief CANIF_E_PARAM_POINTER */
#define CANIF_E_PARAM_POINTER               20U

/** \brief CANIF_E_PARAM_CTRLMODE */
#define CANIF_E_PARAM_CTRLMODE              21U

/** \brief CANIF_E_PARAM_PDUMODE */
#define CANIF_E_PARAM_PDUMODE               22U

/** \brief CANIF_E_UNINIT */
#define CANIF_E_UNINIT                      30U

/** \brief CANIF_E_NOK_NOSUPPORT */
#define CANIF_E_NOK_NOSUPPORT               40U

/** \brief CANIF_E_INVALID_TXPDUID */
#define CANIF_E_INVALID_TXPDUID             50U

/** \brief CANIF_E_INVALID_RXPDUID */
#define CANIF_E_INVALID_RXPDUID             60U

/*==================[type definitions]=======================================*/

/** \brief States for a controller in the CAN interface
 **
 ** CAN controller states: Initially CANIF_CS_UNINIT, then switch between
 ** CANIF_CS_STOPPED, CANIF_CS_STARTED and CANIF_CS_SLEEP.
 */
typedef enum
{
  CANIF_CS_UNINIT = 0U,  /**<Controller is not initialized */
  CANIF_CS_SLEEP,        /**<Controller is in sleep mode */
  CANIF_CS_STARTED,      /**<Controller is active/running */
  CANIF_CS_STOPPED       /**<Controller is stopped */
} CanIf_ControllerModeType;



/** \brief Type for PDU channel mode requests
 **
 ** This type defines the possible mode requests that can be stated for a
 ** PDU channel.
 */
typedef enum
{
  CANIF_SET_OFFLINE = 0U, /**<Transmission and Reception shall be disabled*/
  CANIF_SET_ONLINE,       /**<Transmission and reception shall be enabled*/
  CANIF_SET_RX_OFFLINE,   /**<Reception shall be Disabled */
  CANIF_SET_RX_ONLINE,    /**<Reception shall be Enabled*/
  CANIF_SET_TX_OFFLINE,   /**<Transmission shall be Disabled*/
  CANIF_SET_TX_OFFLINE_ACTIVE,   /**<Offline active mode for transmission */
  CANIF_SET_TX_ONLINE     /**<Transmission shall be Enabled*/
} CanIf_PduSetModeType;



/** \brief Type for current PDU channel mode
 **
 ** This type defines the PDU channel modes that a channel can currently have.
 */
typedef enum
{
  CANIF_GET_OFFLINE = 0U,       /**<Transmission and Reception are disabled*/
  CANIF_GET_OFFLINE_ACTIVE,     /**<Tx offline active, Reception is disabled */
  /* Deviation MISRA-1 */
  /* Deviation MISRA-2 */
  CANIF_GET_OFFLINE_ACTIVE_RX_ONLINE,   /**<Tx offline active, Reception is enabled */
  CANIF_GET_ONLINE,             /**<Transmission and Reception are enabled */
  CANIF_GET_RX_ONLINE,          /**<Transmission is disabled, Reception is enabled */
  CANIF_GET_TX_ONLINE           /**<Transmission is enabled, Reception is disabled */
} CanIf_PduGetModeType;



/** \brief Notification status type
 **
 ** This type defines the values that the "read Rx/Tx notification status"
 ** API functions return if they are activated via configuration.
 */
typedef enum
{
  CANIF_NO_NOTIFICATION = 0U,  /**<No new event since the last read attempt*/
  CANIF_TX_RX_NOTIFICATION    /**<New Rx/Tx event since the last read*/
} CanIf_NotifStatusType;


/*==================[external function declarations]=========================*/

#if CANIF_ISVALIDCONFIG_MMAP_ENABLED == STD_ON
#define CANIF_START_SEC_CODE_CC_BLOCK
#else
#define CANIF_START_SEC_CODE
#endif
#include <MemMap.h>

/** \brief Validate configuration
 **
 ** Checks if the post build configuration fits to the link time configuration part.
 **
 ** \return E_OK if the given module configurations is valid otherwise E_NOT_OK.
 **
 ** \ServiceID{0x60}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC( Std_ReturnType, CANIF_CODE) CanIf_IsValidConfig
  (
    P2CONST(void,AUTOMATIC,CANIF_APPL_CONST) voidConfigPtr
  );

#if CANIF_ISVALIDCONFIG_MMAP_ENABLED == STD_ON
#define CANIF_STOP_SEC_CODE_CC_BLOCK
#include <MemMap.h>

#define CANIF_START_SEC_CODE
#include <MemMap.h>
#endif

/** \brief CAN interface initialization function
 **
 ** This function initializes the CAN interface.
 **
 ** Caution:
 ** - CanIf_Init() shall not preempt any other CanIf function.
 ** - No other CanIf function shall interrupt CanIf_Init().
 **
 ** \param[in] ConfigPtr Pointer to the interface configuration
 **
 ** \ServiceID{0x01}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( void, CANIF_CODE ) CanIf_Init
  (
    P2CONST( CanIf_ConfigType, AUTOMATIC, CANIF_APPL_CONST ) ConfigPtr
  );



/** \brief Controller mode setting function
 **
 ** This function performs a mode transition of the controller given in \p
 ** ControllerId to the mode \p ControllerMode
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - The parameter \p ControllerId must address a valid controller
 ** - The parameter \p ControllerMode must be a valid mode
 **
 ** \param[in] ControllerId   Target controller
 ** \param[in] ControllerMode Requested mode transition
 **
 ** \return Result of operation
 ** \retval E_OK      Controller mode request has been accepted
 ** \retval E_NOT_OK  Controller mode request has not been accepted
 **
 ** \ServiceID{0x03}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_SetControllerMode
  (
    uint8 ControllerId,
    CanIf_ControllerModeType ControllerMode
  );



/** \brief Get controller mode
 **
 ** This function queries the mode of the controller given in \p ControllerId.
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - The parameter \p ControllerId must address a valid controller
 ** - The parameter \p ControllerModePtr must be a valid pointer
 **
 ** \param[in]  ControllerId      CAN controller
 ** \param[out] ControllerModePtr Pointer for returning the current mode
 **
 ** \return Result of operation
 ** \retval E_OK      The returned mode is valid
 ** \retval E_NOT_OK  An error occurred during function execution
 **
 ** \ServiceID{0x04}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_GetControllerMode
  (
    uint8 ControllerId,
    P2VAR( CanIf_ControllerModeType, AUTOMATIC, CANIF_APPL_DATA )
      ControllerModePtr
  );



/** \brief Transmit an L-PDU
 **
 ** This function transmits the data given through \p PduInfoPtr through the
 ** L-PDU given by \p CanTxPduId.
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - The parameter \p CanTxPduId must be a valid Tx L-PDU
 ** - The parameter \p PduInfoPtr must be a valid pointer
 **
 ** \param[in] CanTxPduId Tx L-PDU handle
 ** \param[in] PduInfoPtr Message content to be transmitted
 **
 ** \return Result of operation
 ** \retval E_OK      Transmit request has been accepted
 ** \retval E_NOT_OK  Transmit request has not been accepted
 **
 ** \ServiceID{0x05}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_Transmit
  (
    PduIdType CanTxPduId,
    P2CONST( PduInfoType, AUTOMATIC, CANIF_APPL_DATA ) PduInfoPtr
  );



#if( CANIF_CANCEL_TRANSMIT_SUPPORT == STD_ON )
/** \brief Cancel transmit dummy function
 **
 ** This function has no functionality and is called by the AUTOSAR PduR to
 ** achieve bus agnostic behavior.
 **
 ** Preconditions:
 ** - The parameter \p CanTxPduId must be a valid Tx L-PDU
 **
 ** \param[in] CanTxPduId Tx L-PDU handle
 **
 ** \return Always return E_OK
 **
 ** \ServiceID{0x18}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Asynchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_CancelTransmit
  (
    PduIdType CanTxPduId
  );
#endif /* CANIF_CANCEL_TRANSMIT_SUPPORT == STD_ON */



#if( CANIF_READRXPDU_DATA_API == STD_ON )
/** \brief Read received data
 **
 ** This function reads data previously received and stored in an internal
 ** buffer.
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - This API must be enabled by configuration
 ** - The parameter \p CanRxPduId must be a valid Rx L-PDU
 ** - The parameter \p PduInfoPtr must be a valid pointer
 **
 ** \param[in]  CanRxPduId  Rx L-PDU handle
 ** \param[out] PduInfoPtr  Memory pointer to store received data
 **
 ** \return Result of operation
 ** \retval E_OK      Request has been accepted
 ** \retval E_NOT_OK  Request has not been accepted
 **
 ** \ServiceID{0x06}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_ReadRxPduData
  (
    PduIdType CanRxPduId,
    P2VAR( PduInfoType, AUTOMATIC, CANIF_APPL_DATA ) PduInfoPtr
  );
#endif /* CANIF_READRXPDU_DATA_API == STD_ON */



#if( CANIF_READTXPDU_NOTIF_STATUS_API == STD_ON )
/** \brief Read Tx notification status
 **
 ** This function provides the Tx L-PDU transmit notification status of L-PDU
 ** \p CanTxPduId.
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - Transmit notification API must be enabled
 ** - The parameter \p CanTxPduId must be a valid Tx L-PDU.
 **
 ** \param[in] CanTxPduId Tx L-PDU handle
 **
 ** \return Current notification status of the corresponding Tx L-PDU
 **
 ** \ServiceID{0x07}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( CanIf_NotifStatusType, CANIF_CODE ) CanIf_ReadTxNotifStatus
  ( PduIdType CanTxPduId );
#endif /* CANIF_READTXPDU_NOTIF_STATUS_API == STD_ON */



#if( CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON )
/** \brief Read Rx notification status
 **
 ** This function provides the Rx L-PDU receive notification status of L-PDU
 ** \p CanRxPduId.
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - Transmit notification API must be enabled
 ** - The parameter \p CanRxPduId must be a valid Rx L-PDU.
 **
 ** \param[in] CanRxPduId Rx L-PDU handle
 **
 ** \return Current notification status of the corresponding Rx L-PDU
 **
 ** \ServiceID{0x08}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( CanIf_NotifStatusType, CANIF_CODE ) CanIf_ReadRxNotifStatus
  ( PduIdType CanRxPduId );
#endif /* CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON */



/** \brief Set requested L-PDU channel mode
 **
 ** This function sets the L-PDU channel mode for the requested controller (\p
 ** ControllerId) to the requested mode (\p PduModeRequest).
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - The parameter \p ControllerId must be a valid CAN controller.
 ** - The parameter \p PduModeRequest must be a valid PDU mode.
 **
 ** \param[in] ControllerId   CAN controller
 ** \param[in] PduModeRequest Requested PDU mode
 **
 ** \return Result of operation
 ** \retval E_OK      Request for mode transition has been accepted
 ** \retval E_NOT_OK  Request for mode transition has not been accepted
 **
 ** \ServiceID{0x09}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_SetPduMode
  (
    uint8 ControllerId,
    CanIf_PduSetModeType PduModeRequest
  );



/** \brief Read a L-PDU channel mode
 **
 ** This function returns the current PDU mode of the requested controller
 ** (\p ControllerId) at the memory location referenced by \p PduModePtr.
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - The parameter \p ControllerId must be a valid CAN controller
 ** - The parameter \p PduModePtr must be a valid pointer
 **
 ** \param[in]  ControllerId CAN controller
 ** \param[out] PduModePtr Pointer to return the current mode
 **
 ** \return Result of operation
 ** \retval E_OK      Channel mode request has been accepted
 ** \retval E_NOT_OK  Channel mode request has not been accepted
 **
 ** \ServiceID{0x0a}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_GetPduMode
  (
    uint8 ControllerId,
    P2VAR( CanIf_PduGetModeType, AUTOMATIC, CANIF_APPL_DATA ) PduModePtr
  );


#if( CANIF_VERSION_INFO_API == STD_ON )
/** \brief Return module version information
 **
 ** This function returns the CAN interface version information in the memory
 ** area \p Versioninfo references.
 **
 ** Preconditions:
 ** - The parameter \p Versioninfo may not be a NULL pointer
 **
 ** \param[out] Versioninfo Version information
 **
 ** \ServiceID{0x0b}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( void, CANIF_CODE ) CanIf_GetVersionInfo
  ( P2VAR( Std_VersionInfoType, AUTOMATIC, CANIF_APPL_DATA ) Versioninfo );
#endif


#if( CANIF_SETDYNAMICTXID_API == STD_ON )
/** \brief Set CAN ID of dynamic Tx L-PDU
 **
 ** This function sets the CAN ID of Tx L-PDU \p CanTxPduId to the new value
 ** \p CanId.
 **
 ** Preconditions:
 ** - The CAN interface must already be initialized by CanIf_Init()
 ** - Dynamic Tx L-PDUs are used in the current configuration
 ** - The parameter \p CanTxPduId is a valid dynamic Tx L-PDU
 ** - The parameter \p CanId is a valid CAN ID
 **
 ** \param[in] CanTxPduId Tx L-PDU handle
 ** \param[in] CanId New CAN ID
 **
 ** \ServiceID{0x0c}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( void, CANIF_CODE ) CanIf_SetDynamicTxId
  (
    PduIdType CanTxPduId,
    Can_IdType CanId
  );
#endif /* CANIF_SETDYNAMICTXID_API == STD_ON */



#if( CANIF_TRCV_SUPPORT == STD_ON )

/** \brief Set transceiver mode
 **
 ** This function is used to set the mode of the transceiver assigned to
 ** transceiver channel \a TransceiverId to the mode given in
 ** \a TransceiverMode.
 **
 ** \param[in] TransceiverId CAN transceiver ID
 ** \param[in] TransceiverMode Requested transceiver mode
 **
 ** \return Result of operation
 ** \retval E_OK Transceiver mode was changed as requested
 ** \retval E_NOT_OK Transceiver mode change failed; previous mode is still
 **         valid
 **
 ** \ServiceID{0x0d}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_SetTrcvMode
  (
    uint8 TransceiverId,
    CanTrcv_TrcvModeType TransceiverMode
  );



/** \brief Get transceiver mode
 **
 ** This function is used to read the mode of the transceiver assigned to
 ** transceiver channel \a TransceiverId to the memory location
 ** \a TransceiverModePtr.
 **
 ** \param[in] TransceiverModePtr Pointer to mode variable
 ** \param[in] TransceiverId CAN transceiver ID
 **
 ** \return Result of operation
 ** \retval E_OK Transceiver mode was changed as requested
 ** \retval E_NOT_OK Transceiver mode change failed; previous mode is still
 **         valid
 **
 ** \ServiceID{0x0e}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_GetTrcvMode
  (
    P2VAR( CanTrcv_TrcvModeType, AUTOMATIC, CANIF_APPL_DATA )
      TransceiverModePtr,
    uint8 TransceiverId
  );



/** \brief Get transceiver wakeup reason
 **
 ** This function is used to read the last wakeup reason of the transceiver
 ** assigned to transceiver channel \a TransceiverId into \a TrcvWuReasonPtr.
 **
 ** \param[in] TransceiverId CAN transceiver channel ID
 ** \param[in] TrcvWuReasonPtr Address to write wakeup reason to
 **
 ** \return Result of operation
 ** \retval E_OK Wakeup reason was correctly read
 ** \retval E_NOT_OK Wakeup reason could not be read
 **
 ** \ServiceID{0x0f}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_GetTrcvWakeupReason
  (
    uint8 TransceiverId,
    P2VAR( CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANIF_APPL_DATA )
      TrcvWuReasonPtr
  );



/** \brief Set transceiver wakeup mode
 **
 ** This function is used to set the wakeup mode/event \a TrcvWakeupMode of
 ** the transceiver assigned to transceiver channel \a TransceiverId.
 **
 ** \param[in] TransceiverId CAN transceiver channel ID
 ** \param[in] TrcvWakeupMode Wakeup mode/event to set
 **
 ** \return Result of operation
 ** \retval E_OK Wakeup state has been changed
 ** \retval E_NOT_OK Wakeup state change has failed
 **
 ** \ServiceID{0x10}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_SetTrcvWakeupMode
  (
    uint8 TransceiverId,
    CanTrcv_TrcvWakeupModeType TrcvWakeupMode
  );

#endif /* CANIF_TRCV_SUPPORT == STD_ON */



#if( CANIF_WAKEUP_SUPPORT_API == STD_ON )
/** \brief Check for Can and CanTrcv wakeups
 **
 ** This function is used to check whether an underlying CAN driver or CAN
 ** transceiver driver signals a wakeup event.
 **
 ** \param[in] WakeupSource Bitfield of wakeup sources to be checked
 **
 ** \return Result of operation
 ** \retval E_OK The validation request was accepted and executed
 ** \retval E_NOT_OK The validation request was not accepted
 **
 ** \ServiceID{0x11}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_CheckWakeup
  (
    EcuM_WakeupSourceType WakeupSource
  );



#if( CANIF_WAKEUP_VALIDATION_API == STD_ON )
/** \brief Check for validated wakeup events
 **
 ** This function is used to validate previous wakeup events.
 **
 ** \param[in] WakeupSource Bitfield of wakeup sources to be validated
 **
 ** \return Result of operation
 ** \retval E_OK The validation request was accepted and executed
 ** \retval E_NOT_OK The validation request was not accepted
 **
 ** \ServiceID{0x12}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_CheckValidation
  (
    EcuM_WakeupSourceType WakeupSource
  );
#endif /* CANIF_WAKEUP_VALIDATION_API == STD_ON */
#endif /* CANIF_WAKEUP_SUPPORT_API == STD_ON */



#if( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON )
/** \brief Report controller Tx confirmation state
 **
 ** This function reports, if any Tx confirmation has been received for the
 ** whole CAN controller since the last controller start.
 **
 ** Preconditions:
 ** - The parameter \p ControllerId must be a valid CanIf controller ID
 **
 ** \param[in] ControllerId Abstracted CanIf controller ID which is assigned
 **                         to the CAN controller
 **
 ** \return Notification status of the controller
 ** \retval CANIF_NO_NOTIFICATION     No notification was received
 ** \retval CANIF_TX_RX_NOTIFICATION  A Tx confirmation was received
 **
 ** \ServiceID{0x19}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC( CanIf_NotifStatusType, CANIF_CODE ) CanIf_GetTxConfirmationState
  (
    uint8 ControllerId
  );
#endif /* CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON */

#if ((CANIF_PUBLIC_PN_SUPPORT == STD_ON) && (CANIF_TRCV_SUPPORT == STD_ON ))
/** \brief Clear WUF flag of the designated CAN transceiver
 **
 ** \param[in] TransceiverId  designated CAN transceiver
 ** \return Result of operation
 ** \retval E_OK      Request has been accepted
 ** \retval E_NOT_OK  Request has not been accepted
 **
 ** \ServiceId{0x1e}
 ** \Reentrancy{Reentrant for different CAN transceiver}
 ** \Synchronicity{Asnychronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_ClearTrcvWufFlag
  (
    uint8 TransceiverId
  );

/** \brief Check the wake flag of the designated CAN transceiver
 **
 ** \param[in] TransceiverId  designated CAN transceiver
 ** \return Result of operation
 ** \retval E_OK      Request has been accepted
 ** \retval E_NOT_OK  Request has not been accepted
 **
 ** \ServiceId{0x1f}
 ** \Reentrancy{Reentrant for different CAN transceiver}
 ** \Synchronicity{Asnychronous}
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_CheckTrcvWakeFlag
  (
    uint8 TransceiverId
  );
#endif /* #if (CANIF_PUBLIC_PN_SUPPORT == STD_ON) && (CANIF_TRCV_SUPPORT == STD_ON )) */

#define CANIF_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( CANIF_API_H ) */
/*==================[end of file]============================================*/
