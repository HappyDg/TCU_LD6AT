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
#if (!defined CANIF_INT_H)
#define CANIF_INT_H

/*
 * Misra-C:2004 Deviations:
 *
 * MISRA-1) Deviated Rule: 8.12 (required)
 * When an array is declared with external linkage, its size shall be stated explicitely or defined implicitely by initialisation.
 *
 * Reason:
 * Since this is a link-time configuration parameter, the size of the array depends on the configuration.
 *
 * MISRA-2) Deviated Rule: 19.6 (required)
 * #undef shall not be used.
 *
 * Reason:
 * In order to modify the behavior of the included file, enclosing the file
 * inclusion by a special macro definition is required.
 *
 * MISRA-3) Deviated Rule: 19.10 (required)
 * Parameter instance shall be enclosed in parentheses.
 *
 * Reason:
 * Enclosing the paramter in parentheses is not possible, because it results in compiler syntax error.
 */

 /*==================[inclusions]=============================================*/

#include <CanIf_Cfg.h>          /* Generated PreCompile configuration */
#include <CanIf_Types_Int.h>    /* Generated PostBuild configuration types */
#include <CanIf.h>              /* CAN interface types */

#define TS_RELOCATABLE_CFG_ENABLE CANIF_RELOCATABLE_CFG_ENABLE

#include <TSPBConfig_Access.h>
#include <TSPBConfig_Signature.h>           /* relocatable post-build macros */
/*==================[macros]=================================================*/

  /* --- CanIf instance ID ----------------------------------------------- */

/** \brief CAN interface instance id
 **
 ** Instance ID of the CAN interface.
 */
#define CANIF_INSTANCE_ID                   0U



  /* --- CanIf state ----------------------------------------------------- */

/** \brief CanIf is uninitialized */
#define CANIF_UNINITIALIZED                 0U

/** \brief CanIf is initialized */
#define CANIF_INITIALIZED                   1U



  /* --- controller flags ------------------------------------------------ */

/** \brief Mask for CAN controller wakeup flag */
#define CANIF_WAKEUP_MASK                   0x01U

/** \brief Mask for CAN controller wakeup validation flag */
#define CANIF_WAKEUP_VALIDATION_MASK        0x02U

/** \brief Mask for CAN controller Tx confirmation flag */
#define CANIF_TX_CONFIRMATION_MASK          0x04U

/** \brief Mask for CAN controller partial networking filter flag */
#define CANIF_PN_FILTER_ACTIVE_MASK         0x08U



  /* --- software filtering ---------------------------------------------- */

/** \brief Binary software filtering used for this L-PDU */
#define CANIF_BINARY_SOFTWARE_FILTERING     0U

/** \brief No software filtering used for this L-PDU */
#define CANIF_NO_SOFTWARE_FILTERING         255U



  /* --- dynamic Tx L-PDU type ------------------------------------------- */

/** \brief Dynamic Tx L-PDU standard CAN ID */
#define CANIF_STANDARD_CAN_ID               0U

/** \brief Dynamic Tx L-PDU extended CAN ID */
#define CANIF_EXTENDED_CAN_ID               1U


  /* --- Det Error Ids ---------------------------------------------- */

#define CANIF_E_INVALID_DLC                 61U

#define CANIF_E_NOT_SLEEP                   71U
  /* --- partial networking ---------------------------------------------- */

/** \brief Block the Tx PDU by the partial networking filter */
#define CANIF_PN_FILTER_BLOCK_PDU           0U

/** \brief Allow the Tx PDU by teh partial networking filter */
#define CANIF_PN_FILTER_ALLOW_PDU           1U



  /* --- miscellaneous --------------------------------------------------- */

/** \brief User type for upper layers for which no callback function shall
 **        be called.
 */
#define CANIF_NO_UPPER_LAYER_CALLBACK       255U

/** \brief Rx buffer DLC initialization value (invalid) */
#define CANIF_INVALID_DLC                   0xFFU

/** \brief Index value to indicate direct link to L-PDU ID */
#define CANIF_LPDU_ID_DIRECT                0U

/** \brief Symbol to indicate no wakeup source */
#define CANIF_NO_WAKEUP_SOURCE              0U



/** \brief Invalid CAN controller ID
 **
 ** This constant defines an invalid controller index.
 */
#define CANIF_INVALID_CONTROLLER_ID           255U

/** \brief Internal index of a single CAN controller
 **
 ** This constant defines the internal controller index of a single CAN
 ** controller. As the internal indices are always zero-based and consecutive
 ** (dense) it is always 0U.
 */
#define CANIF_SINGLE_CAN_CTRL_INDEX           0U

/** \brief Internal Id of a single CAN controller within Can
 */
#define CANIF_SINGLE_CAN_CTRL_ID              0U

/** \brief Invalid HOH ID index
 **
 ** This value is used to mark invalid HOH IDs in the translation array.
 */
#define CANIF_INVALID_HOH_ID                  0xFFFFU

/** \brief Mask to identify HTHs
 **
 ** This value is added to the CanIf internal index of each HTH to be able to
 ** verify, that this is a HTH. This is used for DET reporting only.
 ** It is set to 0 if DET reporting is disabled.
 */
#if CANIF_DEV_ERROR_DETECT == STD_ON
#define CANIF_HTH_ID_MASK                     0x8000U
#else /* CANIF_DEV_ERROR_DETECT */
#define CANIF_HTH_ID_MASK                     0x0000U
#endif /* CANIF_DEV_ERROR_DETECT */

/** \brief invalid index for Tx L-PDU buffers
 **
 ** This constant defines the index used for the state "no Tx L-PDU buffer"
 ** assigned.
 */
#define CANIF_INVALID_TX_BUFFER_INDEX         0xFFFFU

/** \brief invalid index for Rx L-PDU buffers
 **
 ** This constant defines the index used for the state "no Rx L-PDU buffer"
 ** assigned.
 */
#define CANIF_INVALID_RX_BUFFER_INDEX         0xFFFFU

/** \brief Invalid L-PDU index constant
 **
 ** This constant defines an index value which is interpreted as "invalid
 ** index".
 */
#define CANIF_INVALID_LPDU_INDEX              0xFFFFU


/** \brief Invalid transceiver index constant
 **
 ** This constant defines an index value which is interpreted as "invalid
 ** index".
 */
#define CANIF_INVALID_TRCV_INDEX              0xFFU

/** \brief "No range configuration" index
 **
 ** This constant is used for Rx L-PDUs that have no reception range assigned.
 */
#define CANIF_NO_RANGE_CONFIG                 0xFFFFFFFFUL

/* relocatable post build elements access macros. */

/* Deviation MISRA-3 <START> */
#define CANIF_PBCFG_ACCESS(type, element) \
    (TS_UNCHECKEDGETCFG(CanIf_ConfigPtr, type, CANIF, CanIf_ConfigPtr->element))

#define CANIF_PBCFG_ACCESS_DRIVER(type, element) \
    (TS_UNCHECKEDGETCFG(CanIf_ConfigPtr, type, CANIF, CANIF_PBCFG_ACCESS(CanIf_CanDriverConfigType,driverConfigPtr)->element))
/* Deviation MISRA-3 <STOP> */

#define CANIF_CFG_GET_TXLPDU_CFG(Index)   \
    (CANIF_PBCFG_ACCESS(CanIf_TxLPduConfigType, txLPduConfigPtr)[(Index)])

#define CANIF_CFG_GET_RXLPDU_CFG(Index)   \
    (CANIF_PBCFG_ACCESS(CanIf_RxLPduConfigType, rxLPduConfigPtr)[(Index)])

#define CANIF_CFG_GET_SORTEDRXLPDU_CFG(Index)   \
    (CANIF_PBCFG_ACCESS(CanIf_LPduIndexType, sortedRxLPduConfigPtr)[(Index)])

#define CANIF_CFG_GET_DRIVER_CFG(Index)   \
    (CANIF_PBCFG_ACCESS(CanIf_CanDriverConfigType, driverConfigPtr)[(Index)])

#define CANIF_CFG_GET_TRCV_CFG(Index)   \
    (CANIF_PBCFG_ACCESS(CanIf_CanTrcvChnlConfigType, trcvChnlConfigPtr)[(Index)])

#define CANIF_CFG_GET_CTRL_CFG(Index)   \
    (CANIF_PBCFG_ACCESS_DRIVER(CanIf_CanControllerConfigType, ctrlConfigPtr)[(Index)])

#if (CANIF_HOH_TRANSLATION_OPT == STD_OFF)
#define CANIF_CFG_GET_HOHID2CANIF_IDX(Index)   \
    (CANIF_PBCFG_ACCESS_DRIVER(uint16, hohIdToCanIfIdxPtr)[(Index)])
#endif /* (CANIF_HOH_TRANSLATION_OPT == STD_OFF) */

#define CANIF_CFG_GET_HTH_CFG(Index)   \
    (CANIF_PBCFG_ACCESS_DRIVER(CanIf_HthConfigType, hthConfigPtr)[(Index)])

#define CANIF_CFG_GET_HRH_CFG(Index)   \
    (CANIF_PBCFG_ACCESS_DRIVER(CanIf_HrhConfigType, hrhConfigPtr)[(Index)])

  /* --- function like macros -------------------------------------------- */

/** \brief Get a notification flag
 **
 ** This macro shall be used ro a notification flag.
 **
 ** \param[in] FlagArray Pointer to the notification flag array
 ** \param[in] Index     Index of the bit to be set
 **
 ** \return 0 if flag was not set, another value otherwise
 **
 ** \remarks Please note that the caller must make sure that this macro is
 **          executed in a critical section.
 */
#define CANIF_GET_NOTIFICATION_FLAG( FlagArray, Index ) \
  ((FlagArray)[(Index)>>3U] & (uint8)(1U<<((Index) & 0x07U)))



/** \brief Set a notification flag
 **
 ** This macro shall be used for setting a notification flag.
 **
 ** \param[in/out] FlagArray Pointer to the notification flag array
 ** \param[in]     Index     Index of the bit to be set
 **
 ** \remarks Please note that the caller must make sure that this macro is
 **          executed in a critical section.
 */
#define CANIF_SET_NOTIFICATION_FLAG( FlagArray, Index ) \
  ((FlagArray)[(Index)>>3U] |= (uint8)(1U << ((Index) & 0x07U)))



/** \brief Clear a notification flag
 **
 ** This macro shall be used for clearing a notification flag.
 **
 ** \param[in/out] FlagArray Pointer to the notification flag array
 ** \param[in]     Index     Index of the bit to be set
 **
 ** \remarks Please note that the caller must make sure that this macro is
 **          executed in a critical section.
 */
#define CANIF_CLEAR_NOTIFICATION_FLAG( FlagArray, Index ) \
  ((FlagArray)[(Index)>>3U] &= (uint8)(~(uint8)(1U<<((Index) & 0x07U))))



/** \brief Checks the given CAN ID
 **
 ** This macro performs a check of the given CAN ID to be a correct CAN ID
 ** according to the definition of the type Can_IdType. It can be used in C
 ** conditions and evaluates to "true" if the given CAN ID is invalid.
 **
 ** \param[in] CanId CAN ID to be checked
 **
 ** \returns Result of the check
 ** \retval 0 if the CAN ID is valid
 ** \retval !=0 if the CAN ID is invalid
 */
#define CANIF_CHECK_FOR_INVALID_CAN_ID( CanId ) \
  ( ( ((uint32)(CanId) & 0x60000000UL) != 0U ) || \
    ( ( ((uint32)(CanId) & 0x80000000UL) == 0U ) && \
      ( ((uint32)(CanId) & 0x7FFFF800UL) != 0U ) ) )


/** \brief Get number of CAN controllers
 **
 ** This macro can be used, to read the number of CAN controllers from the
 ** driver configuration.
 */
#if CANIF_SINGLE_CAN_CTRL_OPT == STD_OFF
#define CANIF_GET_NR_OF_CAN_CTRLS()  (CanIf_DriverConfigPtr->nrOfControllers)
#else /* CANIF_SINGLE_CAN_CTRL_OPT */
#define CANIF_GET_NR_OF_CAN_CTRLS()  1U
#endif /* CANIF_SINGLE_CAN_CTRL_OPT */



/** \brief Get CAN controller assigned to an HOH
 **
 ** This macro is used to get the controller ID of a CAN controller assigned
 ** to an HOH.
 **
 ** \param[in] HohCfg HOH configuration (both, HRH and HTH)
 */
#if CANIF_SINGLE_CAN_CTRL_OPT == STD_OFF
#define CANIF_GET_HOH_INT_CTRL_IDX(HohCfg)  ((HohCfg).intCtrlIdx)
#else /* CANIF_SINGLE_CAN_CTRL_OPT */
#define CANIF_GET_HOH_INT_CTRL_IDX(HohCfg)  0U
#endif /* CANIF_SINGLE_CAN_CTRL_OPT */



/** \brief Get CanIf internal index of an HOH
 **
 ** This macro is used to translate a given HOH ID into the CanIf internal
 ** index to its HRH or HTH configuration array.
 **
 ** \param[in] HohId CAN Driver HOH ID
 **
 ** \return CanIf internal HOH index representation
 ** \retval HRH configuration array index in case of a receive object
 ** \retval HTH configuration array index + HTH mask for Tx objects
 ** \retval CANIF_INVALID_HOH_ID in case of an invalid HOH ID
 */
#define CANIF_GET_INT_HOH_IDX(HohId)        (CANIF_CFG_GET_HOHID2CANIF_IDX(HohId))


/** \brief Translate controller ID to the index configured in CanIf
 **
 ** This macro is used to translate a CAN controller ID defined by the CAN
 ** Driver into the CanIf ID of that controller.
 */
#if CANIF_SINGLE_CAN_CTRL_OPT == STD_OFF
#define CANIF_GET_CANIF_CTRL_ID(CtrlId)  (CanIf_GetCanIfIdFromCtrlIdx(CtrlId))
#else /* CANIF_SINGLE_CAN_CTRL_OPT */
#define CANIF_GET_CANIF_CTRL_ID(CtrlId)  CANIF_SINGLE_CAN_CTRL_INDEX
#endif /* CANIF_SINGLE_CAN_CTRL_OPT */


/** \brief Translate ID configured in the CanIf to the ID used by CAN Driver
 **
 ** This macro is used to translate a CanIf controller ID into
 ** the CAN controller ID defined and used by the CAN Driver.
 */
#define CANIF_GET_CANDRV_CTRL_ID(CanIfCtrlIdx)   \
              (CANIF_CFG_GET_CTRL_CFG(CanIfCtrlIdx).controllerId)


/** \brief Call the DLC error notification function
 **
 ** This macro is used to call the DLC error notification function of the
 ** given Rx PDU. It checks if one is configured and calls it in this case.
 **
 ** \param[in] RxLPduConfig Configuration container of the Rx L-PDU
 */
#if( CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON )
#define CANIF_DLC_ERROR_NOTIFICATION( RxLPduConfig )                                                                                                    \
  do                                                                                                                                                    \
  {                                                                                                                                                     \
    if( ((RxLPduConfig)->userType != CANIF_NO_UPPER_LAYER_CALLBACK) && (CanIf_CbkFctPtrTbl[(RxLPduConfig)->userType].DlcErrorNotifFctPtr != NULL_PTR )) \
    {                                                                                                                                                   \
      (CanIf_CbkFctPtrTbl[(RxLPduConfig)->userType].DlcErrorNotifFctPtr)( (RxLPduConfig)->targetPduId );                                                \
    }                                                                                                                                                   \
  } while( 0 )
#else /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#define CANIF_DLC_ERROR_NOTIFICATION( RxLPduConfig )
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */


/** \brief Call the DLC check passed notification function
 **
 ** This macro is used to call the DLC check passed notification function of
 ** the given Rx PDU. It checks if one is configured and calls it in this
 ** case.
 **
 ** \param[in] RxLPduConfig Configuration container of the Rx L-PDU
 */
#if( CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON )
#define CANIF_DLC_PASSED_NOTIFICATION( RxLPduConfig )                                                                                                    \
  do                                                                                                                                                     \
  {                                                                                                                                                      \
    if( ((RxLPduConfig)->userType != CANIF_NO_UPPER_LAYER_CALLBACK) && (CanIf_CbkFctPtrTbl[(RxLPduConfig)->userType].DlcPassedNotifFctPtr != NULL_PTR )) \
    {                                                                                                                                                    \
      (CanIf_CbkFctPtrTbl[(RxLPduConfig)->userType].DlcPassedNotifFctPtr)( (RxLPduConfig)->targetPduId );                                                \
    }                                                                                                                                                    \
  } while( 0 )
#else /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
#define CANIF_DLC_PASSED_NOTIFICATION( RxLPduConfig )
#endif /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */

 /** \def CanIf_AtomicAssignCanId(CanId)
  **
  ** \brief Provide a macro for atomic assigning CanIDs
  **
  ** This macro is used to atomic assign CanIDs. Depending on whether they are 16 bit or 32 bit the
  ** respective TS-macro is used.
  **
  ** \param[in] to   CanId is written to in atomic fashion
  ** \param[in] from CanId is read from in tomic fashion
  */
#define CanIf_AtomicAssignCanId(to,from) TS_AtomicAssign32((to),(from))

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#define CANIF_START_SEC_CODE
#include <MemMap.h>

#if( CANIF_PUBLIC_PN_SUPPORT == STD_ON )
/** \brief Helper function for transceiver without partial network
 **
 ** If partial network is enabled, but an underlying transceiver
 ** driver does not support partial network (disabled by config
 ** or no capability), then this function is linked to the
 ** CanTrcv function pointer table in place of the API function
 ** CanTrcv_ClearTrcvWufFlag().
 **
 ** \param[in] TransceiverId designated CAN transceiver
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_ClearTrcvWufFlag_HlpNoPn
  (
    uint8 TransceiverId
  );

/** \brief Helper function for transceiver without partial network
 **
 ** If partial network is enabled, but an underlying transceiver
 ** driver does not support partial network (disabled by config
 ** or no capability), then this function is linked to the
 ** CanTrcv function pointer table in place of the API function
 ** CanTrcv_CheckWakeFlag().
 **
 ** \param[in] TransceiverId designated CAN transceiver
 */
extern FUNC( Std_ReturnType, CANIF_CODE ) CanIf_CheckWakeFlag_HlpNoPn
  (
    uint8 TransceiverId
  );
#endif /* CANIF_PUBLIC_PN_SUPPORT == STD_ON */

#define CANIF_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

#if (CANIF_ANY_UL_CBK_SUPPORT == STD_ON)
/** \brief Configuration of upper layer callback functions
 **
 ** This array contains the function pointers for all upper layer callback
 ** functions.
 */
/* Deviation MISRA-1 */
extern CONST( CanIf_CbkFctPtrTblType, CANIF_APPL_CONST ) CanIf_CbkFctPtrTbl[];
#endif /* CANIF_ANY_UL_CBK_SUPPORT == STD_ON */


#if (CANIF_TRCV_SUPPORT == STD_ON)
/** \brief Configuration of CanTrcv function pointers
 **
 ** This array contains the CanTrcv driver configurations meaning the
 ** function pointers for accessing the driver functionality.
 */
/* Deviation MISRA-1 */
extern CONST( CanIf_CanTrcvConfigType, CANIF_APPL_CONST )
  CanIf_CanTrcvConfig[];


/** \brief Configuration of CanTrcv channels */
/* Deviation MISRA-1 */
extern CONST( CanIf_CanTrcvChnlConfigType, CANIF_APPL_CONST )
  CanIf_CanTrcvChnlConfig[];
#endif /* CANIF_TRCV_SUPPORT == STD_ON */


#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#if( CANIF_READTXPDU_NOTIF_STATUS_API == STD_ON )
/** \brief Bit-array of Tx notification flags (if enabled)
 **
 ** This array contains a Tx notification flag for each Tx L-PDU for which
 ** this feature is enabled.
 */
/* Deviation MISRA-1 */
extern VAR( uint8, CANIF_VAR )
  CanIf_TxLPduNotifyFlags[];
#endif /* CANIF_READTXPDU_NOTIF_STATUS_API == STD_ON */

#if( CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON )
/** \brief Bit-array of Rx notification flags (if enabled)
 **
 ** This array contains a Rx notification flag for each Rx L-PDU for which
 ** this feature is enabled.
 */
/* Deviation MISRA-1 */
extern VAR( uint8, CANIF_VAR )
  CanIf_RxLPduNotifyFlags[];
#endif /* CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON */

#if( CANIF_READRXPDU_DATA_API == STD_ON )
/** \brief Array of Rx buffers
 **
 ** This is an array which is used for buffering of Rx messages.
 */
/* Deviation MISRA-1 */
extern VAR( uint8, CANIF_VAR ) CanIf_RxBuffer[];

#endif /* CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON */

/* Deviation MISRA-1 */
extern VAR( CanIf_ControllerModeType, CANIF_VAR )
  CanIf_CanControllerMode[];

#if( ( CANIF_WAKEUP_VALIDATION_API == STD_ON ) || \
     ( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON )  || \
     ( CANIF_PUBLIC_PN_SUPPORT == STD_ON) )

/** \brief Controller flags
 **
 ** This array contains the wakeup flags of all configured
 ** controllers. If a bit/flag has the value 1 it is set.
 ** Bit masks are:
 ** CANIF_WAKEUP_MASK             Wakeup flag
 ** CANIF_WAKEUP_VALIDATION_MASK  Wakeup validation flag
 ** CANIF_TX_CONFIRMATION_MASK    Tx confirmation flag
 ** CANIF_PN_FILTER_ACTIVE_MASK   Partial networking filter flag
 */
/* Deviation MISRA-1 */
extern VAR( uint8, CANIF_VAR )
  CanIf_CanControllerFlags[];

#endif /* ( CANIF_WAKEUP_VALIDATION_API == STD_ON ) || \
          ( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON ) */


/** \brief PDU modes
 **
 ** This array contains the PDU mode of all configured controllers.
 */
/* Deviation MISRA-1 */
extern VAR( CanIf_PduGetModeType, CANIF_VAR )
  CanIf_PduMode[];

#define CANIF_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_16
#include <MemMap.h>

#if CANIF_PUBLIC_TX_BUFFERING == STD_ON

/** \brief Array of a HTH's number of pending Tx requests */
/* Deviation MISRA-1 */
extern VAR( CanIf_TxBufferIndexType, CANIF_VAR )
  CanIf_NrOfPendingTxRequests[];

/** \brief Pending transmit request buffers
 **
 ** This array stores pending transmit request IDs. It is named as array (8)
 ** in the CAN interface design.
 */
/* Deviation MISRA-1 */
extern VAR( CanIf_LPduIndexType, CANIF_VAR )
  CanIf_PendingTxBuffers[];

#endif /* CANIF_PUBLIC_TX_BUFFERING */

#define CANIF_STOP_SEC_VAR_NO_INIT_16
#include <MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_32
#include <MemMap.h>

#if( CANIF_SETDYNAMICTXID_API == STD_ON )
/** \brief Array for dynamic CAN IDs
 **
 ** This array contains the current set CAN ID for dynamic Tx L-PDUs.
 */
/* Deviation MISRA-1 */
 extern VAR( uint32, CANIF_VAR )
  CanIf_DynamicTxLPduCanIds[];
#endif /* CANIF_SETDYNAMICTXID_API == STD_ON */

#define CANIF_STOP_SEC_VAR_NO_INIT_32
#include <MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>


/** \brief Global Tx L-PDU configuration
 **
 ** This is a pointer to the current global Tx L-PDU configuration.
 */
extern P2CONST( CanIf_TxLPduConfigType, CANIF_VAR, CANIF_APPL_CONST )
  CanIf_TxPduConfigPtr;

/** \brief Global CanIf configuration
 **
 ** This is a pointer to the current CanIf configuration.
 */
extern P2CONST( CanIf_ConfigType, CANIF_VAR, CANIF_APPL_CONST )
  CanIf_ConfigPtr;

#if CANIF_PUBLIC_TX_BUFFERING == STD_ON

/** \brief Array of Tx buffers
 **
 ** This is the array of Tx buffers used during message transmission if Tx
 ** buffering is enabled.
 */
/* Deviation MISRA-1 */
extern VAR( CanIf_TxBufferType, CANIF_VAR )
  CanIf_TxBuffer[];

#endif /* CANIF_PUBLIC_TX_BUFFERING */

#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/* Deviation MISRA-2 */
#undef TS_RELOCATABLE_CFG_ENABLE

#endif /* if !defined( CANIF_INT_H ) */
/*==================[end of file]============================================*/
