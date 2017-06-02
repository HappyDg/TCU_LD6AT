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


/*
 *  Possible Misra-C:2004 Deviations:
 *
 *  MISRA-1) Deviated Rule: 11.3 (advisory)
 *    A cast should not be performed between a pointer type and an integral
 *    type.
 *
 *    Reason:
 *    Implicit conversion of the NULL_PTR #define to other pointer types.
 *
 */

/*==================[inclusions]=============================================*/

#define CANIF_NO_CFGCLASSMIX_REQUIRED
#define CANIF_NO_PBCFG_REQUIRED
#include <CanIf.h>                /* CanIf Types */
#include <CanIf_Int.h>



/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_CanIf.h */
#define PDUR_NO_PBCFG_REQUIRED

#include <CanNm_Cbk.h>             /* CanNm callback function declarations */
#include <CanTp_Cbk.h>             /* CanTp callback function declarations */
#include <PduR_CanIf.h>            /* PduR callback function declarations */

#include <Ccp_Cbk.h>   /* CDD header file */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[internal constants]=====================================*/

/*==================[external constants]=====================================*/

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>



#if (CANIF_ANY_UL_CBK_SUPPORT == STD_ON)
/** \brief Configuration of upper layer callback function pointers */
CONST( CanIf_CbkFctPtrTblType, CANIF_APPL_CONST ) CanIf_CbkFctPtrTbl[] =
{
  {
     /* CAN_NM */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
  {
     /* CAN_TP */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    &CanTp_RxIndication,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    &CanTp_TxConfirmation,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
  {
     /* PDUR */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    &PduR_CanIfRxIndication,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    &PduR_CanIfTxConfirmation,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
  {
     /* CCP_DTO */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    &Ccp_TxConfirmation_DTO,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
  {
     /* CCP_100ms */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    &Ccp_TxConfirmation_100ms,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
  {
     /* CCP_1ms */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    &Ccp_TxConfirmation_1ms,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
  {
     /* CCP_10ms */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    &Ccp_TxConfirmation_10ms,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
  {
     /* CCP_CRO */
#if (CANIF_UL_RX_INDICATION_SUPPORT == STD_ON)
    &Ccp_RxIndication_CRO,
#endif /* CANIF_UL_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_CDD_RX_INDICATION_SUPPORT == STD_ON */
#if (CANIF_TX_CONFIRMATION_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_TX_CONFIRMATION_SUPPORT == STD_ON */
#if (CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif /* CANIF_DLC_ERROR_NOTIF_SUPPORT == STD_ON */
#if (CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON)
    NULL_PTR,
#endif  /* CANIF_DLC_PASSED_NOTIF_SUPPORT == STD_ON */
  },
};
#endif /* CANIF_ANY_UL_CBK_SUPPORT == STD_ON */

#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]==========================================*/


#define CANIF_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

VAR( CanIf_ControllerModeType, CANIF_VAR )
  CanIf_CanControllerMode[3U];

/** \brief PDU modes
 **
 ** This array contains the PDU mode of all configured controllers.
 */
VAR( CanIf_PduGetModeType, CANIF_VAR )
  CanIf_PduMode[3U];

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
VAR( uint8, CANIF_VAR )
  CanIf_CanControllerFlags[3U];

#endif /* ( CANIF_WAKEUP_VALIDATION_API == STD_ON ) || \
          ( CANIF_PUBLIC_TXCONFIRM_POLLING_SUPPORT == STD_ON ) */

#if( CANIF_READTXPDU_NOTIF_STATUS_API == STD_ON )
/** \brief Bit-array of Tx notification flags (if enabled) */
VAR( uint8, CANIF_VAR )
  CanIf_TxLPduNotifyFlags[(1U+7U)/8U];
#endif /* CANIF_READTXPDU_NOTIF_STATUS_API == STD_ON */

#if( CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON )
/** \brief Bit-array of Rx notification flags (if enabled) */
VAR( uint8, CANIF_VAR )
  CanIf_RxLPduNotifyFlags[(1U+7U)/8U];
#endif /* CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON */

#if( CANIF_READRXPDU_DATA_API == STD_ON )
/** \brief Array of Rx buffers */
VAR( uint8, CANIF_VAR ) CanIf_RxBuffer[1U];
#endif /* CANIF_READRXPDU_NOTIF_STATUS_API == STD_ON */

#define CANIF_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_16
#include <MemMap.h>

#if CANIF_PUBLIC_TX_BUFFERING == STD_ON
/** \brief Array of a HTH's number of pending Tx requests */
VAR( CanIf_TxBufferIndexType, CANIF_VAR )
  CanIf_NrOfPendingTxRequests[21U];

/** \brief Pending transmit request buffers
 **
 ** This array stores pending transmit request IDs. It is named as array (8)
 ** in the CAN interface design.
 */
VAR( CanIf_LPduIndexType, CANIF_VAR )
  CanIf_PendingTxBuffers[21U];
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
 VAR( uint32, CANIF_VAR )
  CanIf_DynamicTxLPduCanIds[1U];
#endif /* CANIF_SETDYNAMICTXID_API == STD_ON */

#define CANIF_STOP_SEC_VAR_NO_INIT_32
#include <MemMap.h>

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if CANIF_PUBLIC_TX_BUFFERING == STD_ON
/** \brief Array of Tx buffers
 **
 ** This is the array of Tx buffers used during message transmission if Tx
 ** buffering is enabled.
 */
VAR( CanIf_TxBufferType, CANIF_VAR )
  CanIf_TxBuffer[21U];
#endif /* CANIF_PUBLIC_TX_BUFFERING */

#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>


/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
