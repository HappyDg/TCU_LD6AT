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
#if(!defined CANTP_INTERNALLIB_H)
#define CANTP_INTERNALLIB_H


/*
 *  Misra-C:2004 Deviations:
 *
 *  MISRA-1) Deviated Rule: 19.7 (advisory)
 *    A function should be used in preference to a function-like macro.
 *
 *    Reason:
 *    Improved speed and readability outweighs using a function.
 */

/*==================[inclusions]=============================================*/

#include <ComStack_Types.h>    /* typedefs for AUTOSAR com stack */
#include <CanTp_Version.h>     /* CanTp version declarations */
#include <CanTp_Cfg.h>         /* DET configuration */
#include <CanTp_Types.h>       /* Module internal global types */

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
#endif

/*==================[macros]=================================================*/
/** \brief Define for CanTp N-SDU direction (Tx N_SDU). */
#define CANTP_PDU_DIR_TRANSMIT 0U

/** \brief Define for CanTp N-SDU direction (Rx N_SDU). */
#define CANTP_PDU_DIR_RECEIVE  1U

/** \brief Macro to indicate that no FC Tx PDU is used */
#define CANTP_FC_FRAME_NOT_USED  ((PduIdType)0xFFFFU)

/** \brief Maximal length of segmented CAN message (12 bit). */
#define CANTP_MAX_MESSAGE_LENGTH 4095U

/*------------------[list of error codes]------------------------------------*/

/** \brief no config provided */
#define CANTP_E_PARAM_CONFIG       0x01U
/** \brief ID parameter not valid */
#define CANTP_E_PARAM_ID           0x02U
/** \brief API service called with a NULL pointer */
#define CANTP_E_PARAM_POINTER      0x03U
/** \brief CanTp not initialized */
#define CANTP_E_UNINIT             0x20U
/** \brief invalid transmit ID */
#define CANTP_E_INVALID_TX_ID      0x30U
/** \brief invalid receive ID */
#define CANTP_E_INVALID_RX_ID      0x40U
/** \brief invalid Tx length */
#define CANTP_E_INVALID_TX_LENGTH  0x70U
/** \brief invalid Rx length */
#define CANTP_E_INVALID_RX_LENGTH  0x80U
/** \brief invalid communication type */
#define CANTP_E_INVALID_TATYPE     0x90U
/** \brief invalid direction parameter */
#define CANTP_E_PARAM_DIRECTION    0xA1U
/** \brief Invalid Requested operation */
#define CANTP_E_OPER_NOT_SUPPORTED 0xA0U

/*------------------[list of AUTOSAR API Ids]--------------------------------*/

/** \brief service ID for an unspecific API */
#define CANTP_API_UNSPECIFIC               0x00U
/** \brief service ID for function CanTp_Init() */
#define CANTP_API_INIT                     0x01U
/** \brief service ID for function CanTp_Transmit() */
#define CANTP_API_TRANSMIT                 0x03U
/** \brief service ID for function CanTp_RxIndication() */
#define CANTP_API_RXINDICATION             0x42U
/** \brief service ID for function CanTp_TxConfirmation() */
#define CANTP_API_TXCONFIRMATION           0x40U
/** \brief service ID for function CanTp_MainFunction() */
#define CANTP_API_MAINFUNCTION             0x06U
/** \brief service ID for function CanTp_GetVersionInfo() */
#define CANTP_API_GETVERSIONINFO           0x07U
/** \brief service ID for function CanTp_CancelTransmit() */
#define CANTP_API_CANCELTRANSMIT           0x08U
/** \brief service ID for function CanTp_CancelReceive() */
#define CANTP_API_CANCELRECEIVE            0x09U
/** \brief service ID for function CanTp_ChangeParameter() */
#define CANTP_API_CHANGEPARAMETER          0x0AU
/** \brief service ID for function CanTp_SetNSa() */
#define CANTP_API_SETNSA                   0x1EU
/** \brief service ID for function CanTp_GetNSa() */
#define CANTP_API_GETNSA                   0x1FU

/*------------------[defines signaling alternatives]-------------------------*/

/** \brief defines for global CanTp state machine */
#define CANTP_OFF   0U     /* = 0 for implementation purposes */
#define CANTP_ON    1U     /* = 1 for implementation purposes */

/* Defines for CanTp addressing formats */
/** \brief Standard addressing format */
#define CANTP_STANDARD  0U
/** \brief Extended addressing format */
#define CANTP_EXTENDED  1U
/** \brief Mixed addressing format */
#define CANTP_MIXED     2U

/** \brief defines for CanTp communication type */
#define CANTP_PHYSICAL   0U /* physical for 1 to 1 connections */
#define CANTP_FUNCTIONAL 1U /* function for 1 to n connections */

/*------------------[NPDU header sizes and NSDU length]---------------------*/

/** \brief Number of bytes required for SF N_PCI */
#define CANTP_SF_NPCI_SIZE         1U

/** \brief Number of bytes required for FF N_PCI */
#define CANTP_FF_NPCI_SIZE         2U

/** \brief Number of bytes required for CF N_PCI */
#define CANTP_CF_NPCI_SIZE         1U

/** \brief Number of bytes required for FC N_PCI */
#define CANTP_FC_NPCI_SIZE         3U

/** \brief Maximum number of bytes from upper layer fitting into a SF NPdu
 *
 * This macro defines the maximum number of upper layer data bytes (NSdu size)
 * which fits into a single frame NPdu. The maximum number can only be transmitted
 * if addressing format is set to normal addressing (N_PCI = 1 byte and NSdu =
 * 7 bytes).
 */
#define CANTP_SF_MAX_NSDU_LENGTH         7U

/** \brief Maximum number of bytes from upper layer fitting into a FF NPdu
 *
 * This macro defines the maximum number of upper layer data bytes (NSdu size)
 * which fits into a first frame NPdu. The maximum number can only be transmitted
 * if addressing format is set to normal addressing (N_PCI = 2 byte and NSdu =
 * 6 bytes).
 */
#define CANTP_FF_MAX_NSDU_LENGTH         6U

/** \brief Maximum number of bytes from upper layer fitting into a CF NPdu
 *
 * This macro defines the maximum number of upper layer data bytes (NSdu size)
 * which fits into a consecutive frame NPdu. The maximum number can only be transmitted
 * if addressing format is set to normal addressing (N_PCI = 1 byte and NSdu =
 * 7 bytes).
 */
#define CANTP_CF_MAX_NSDU_LENGTH         7U

/*------------------[channel state machine]----------------------------------*/

/** \brief defines for CanTp channel state machine
 **
 ** These defines contain all possible channel states for CanTp
 **
 ** Naming: CANTP_CH_<mode>_<action>_<frametype>
 **
 **  <mode>:      RX, TX or IDLE
 **  <action>:    BUFREQ,   poll the upper layer to get a buffer
 **               TRANSMIT, try to transmit using CanIf_Transmit
 **               CONFIRM,  wait for TxConfirmation of transmitted frame
 **               RECEIVE,  wait for RxIndication (answer from remote)
 **               WAITTMR   wait for STmin timeout
 **  <frametype>: SF, FF, CF, FC_CTS, FC_OVFLW, FC_WT
 **
 ** Not all combinations of all substates are possible. The following scheme
 ** is used to pack the states into an uint8 (CanTp_ChStateType):
 ** bits [7|6|5|4|3|2|1|0]
 **      `0^mod^act^frame'
 ** <mod> 00 idle  <act> 00 BUFREQ    <frame> 000 SF  100 FC_CTS
 **       10 rx          01 TRANSMIT          001 FF  101 FC_OVFLW
 **       11 tx          10 CONFIRM*          010 CF  110 FC_WT
 **                      10 RECEIVE*
 **                      11 WAITTMR
 ** Notes:
 **   * as CONFIRM and RECEIVE can be distinguished by direction and frame
 **     type, they share the same encoding.
 */

/* masks */
#define CANTP_CH_MODE_MASK        0x60U   /* 0110 0000 */
#define CANTP_CH_ACTION_MASK      0x18U   /* 0001 1000 */
#define CANTP_CH_FRAME_MASK       0x07U   /* 0000 0111 */

/* access macros for substates */
#define CANTP_CH_MODE_IDLE        0x00U   /* 0000 0000 */
#define CANTP_CH_MODE_RX          0x40U   /* 0100 0000 */
#define CANTP_CH_MODE_TX          0x60U   /* 0110 0000 */

#define CANTP_CH_ACTION_BUFREQ    0x00U   /* 0000 0000 */
#define CANTP_CH_ACTION_TRANSMIT  0x08U   /* 0000 1000 */
#define CANTP_CH_ACTION_CONFIRM   0x10U   /* 0001 0000 */
#define CANTP_CH_ACTION_RECEIVE   0x10U   /* 0001 0000 */
#define CANTP_CH_ACTION_WAITTMR   0x18U   /* 0001 1000 */

#define CANTP_CH_FRAME_SF         0x00U   /* 0000 0000 */
#define CANTP_CH_FRAME_FF         0x01U   /* 0000 0001 */
#define CANTP_CH_FRAME_CF         0x02U   /* 0000 0010 */
#define CANTP_CH_FRAME_FC_CTS     0x04U   /* 0000 0100 */
#define CANTP_CH_FRAME_FC_OVFLW   0x05U   /* 0000 0101 */
#define CANTP_CH_FRAME_FC_WT      0x06U   /* 0000 0110 */

/* possible state combinations */

/** \brief channel is free */
#define CANTP_CH_IDLE             CANTP_CH_MODE_IDLE


/** \brief rx channel - request rx buffer for SF */
#define CANTP_CH_RX_BUFREQ_SF \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_BUFREQ   | CANTP_CH_FRAME_SF)

/** \brief rx channel - request rx buffer for FF */
#define CANTP_CH_RX_BUFREQ_FF \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_BUFREQ   | CANTP_CH_FRAME_FF)

/** \brief rx channel - request rx buffer for CF */
#define CANTP_CH_RX_BUFREQ_CF \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_BUFREQ   | CANTP_CH_FRAME_CF)

/** \brief rx channel - transmit FC next */
#define CANTP_CH_RX_TRANSMIT_FC_CTS \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_TRANSMIT | CANTP_CH_FRAME_FC_CTS)

/** \brief rx channel - transmit FC next */
#define CANTP_CH_RX_TRANSMIT_FC_OVFLW \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_TRANSMIT | CANTP_CH_FRAME_FC_OVFLW)

/** \brief rx channel - transmit FC next */
#define CANTP_CH_RX_TRANSMIT_FC_WT \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_TRANSMIT | CANTP_CH_FRAME_FC_WT)

/** \brief rx channel - wait for FC cts confirmation */
#define CANTP_CH_RX_CONFIRM_FC_CTS \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_CONFIRM  | CANTP_CH_FRAME_FC_CTS)

/** \brief rx channel - wait for FC ovflw confirmation */
#define CANTP_CH_RX_CONFIRM_FC_OVFLW \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_CONFIRM  | CANTP_CH_FRAME_FC_OVFLW)

/** \brief rx channel - wait for FC wt confirmation */
#define CANTP_CH_RX_CONFIRM_FC_WT \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_CONFIRM  | CANTP_CH_FRAME_FC_WT)

/** \brief rx channel - wait for CF reception */
#define CANTP_CH_RX_RECEIVE_CF \
    (uint8)(CANTP_CH_MODE_RX | CANTP_CH_ACTION_RECEIVE  | CANTP_CH_FRAME_CF)


/** \brief tx channel - request tx buffer for SF */
#define CANTP_CH_TX_BUFREQ_SF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_BUFREQ   | CANTP_CH_FRAME_SF)

/** \brief tx channel - request tx buffer for FF */
#define CANTP_CH_TX_BUFREQ_FF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_BUFREQ   | CANTP_CH_FRAME_FF)

/** \brief tx channel - request tx buffer for CF */
#define CANTP_CH_TX_BUFREQ_CF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_BUFREQ   | CANTP_CH_FRAME_CF)

/** \brief tx channel - transmit SF next */
#define CANTP_CH_TX_TRANSMIT_SF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_TRANSMIT | CANTP_CH_FRAME_SF)

/** \brief tx channel - transmit FF next */
#define CANTP_CH_TX_TRANSMIT_FF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_TRANSMIT | CANTP_CH_FRAME_FF)

/** \brief tx channel - transmit CF next */
#define CANTP_CH_TX_TRANSMIT_CF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_TRANSMIT | CANTP_CH_FRAME_CF)

/** \brief tx channel - wait for tx SF confirmation */
#define CANTP_CH_TX_CONFIRM_SF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_CONFIRM  | CANTP_CH_FRAME_SF)

/** \brief tx channel - wait for tx FF confirmation */
#define CANTP_CH_TX_CONFIRM_FF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_CONFIRM  | CANTP_CH_FRAME_FF)

/** \brief tx channel - wait for tx CF confirmation */
#define CANTP_CH_TX_CONFIRM_CF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_CONFIRM  | CANTP_CH_FRAME_CF)

/** \brief tx channel - receive FC next */
#define CANTP_CH_TX_RECEIVE_FC \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_RECEIVE  | CANTP_CH_FRAME_FC_CTS)

/** \brief tx channel - wait StMin before transmit CF */
#define CANTP_CH_TX_WAITTMR_CF \
    (uint8)(CANTP_CH_MODE_TX | CANTP_CH_ACTION_WAITTMR  | CANTP_CH_FRAME_CF)


/* access macros to retrieve substate information */

/** \brief get mode substate for ChannelPtr */
#define CANTP_CH_GET_MODE(ChannelPtr) \
    ((uint8) ((ChannelPtr)->State & CANTP_CH_MODE_MASK))

/** \brief get action substate for ChannelPtr */
#define CANTP_CH_GET_ACTION(ChannelPtr) \
    ((uint8) ((ChannelPtr)->State & CANTP_CH_ACTION_MASK))

/** \brief set state bits */
#define CANTP_CH_SET_STATEBITS(ChannelPtr, BitMask, BitsToSet)              \
  do                                                                        \
  {                                                                         \
    CanTp_ChStateType NextState;                                            \
    NextState = (CanTp_ChStateType) (ChannelPtr)->State;                    \
    NextState =  NextState                                                  \
                 & (CanTp_ChStateType)(~(CanTp_ChStateType)(BitMask));      \
    NextState = NextState | ((CanTp_ChStateType) (BitsToSet));              \
    DBG_CANTP_CHANNEL_STATE_GRP(                                            \
                                DBG_CANTP_GET_CHANNEL_INDEX((ChannelPtr)),  \
                                (ChannelPtr)->State,                        \
                                NextState                                   \
                               );                                           \
    (ChannelPtr)->State = NextState;                                        \
  } while(0U)


/** \brief set mode substate of ChannelPtr to dir */
#define CANTP_CH_SET_MODE(ChannelPtr, dir)                                    \
    do                                                                        \
    {                                                                         \
      CANTP_CH_SET_STATEBITS((ChannelPtr)->State, CANTP_CH_MODE_MASK, (dir)); \
    } while(0U)

/** \brief set action substate of ChannelPtr to act */
#define CANTP_CH_SET_ACTION(ChannelPtr, act)                                  \
  do                                                                          \
  {                                                                           \
    CANTP_CH_SET_STATEBITS((ChannelPtr), CANTP_CH_ACTION_MASK, (act)); \
  } while(0U)

/*------------------[frame types]--------------------------------------------*/

/** \brief defines for first N_PCI byte in TP frames */
#define CANTP_N_PCI_TYPE_MASK   0xF0U /* mask for N_PCItype */
#define CANTP_N_PCI_TYPE_SF     0x00U /* N_PCItype = 0: SF */
#define CANTP_N_PCI_TYPE_FF     0x10U /* N_PCItype = 0: FF */
#define CANTP_N_PCI_TYPE_CF     0x20U /* N_PCItype = 0: CF */
#define CANTP_N_PCI_TYPE_FC     0x30U /* N_PCItype = 0: FC */
#define CANTP_N_PCI_FC_CTS      0x30U /* N_PCItype FC and FlowStatus CTS */
#define CANTP_N_PCI_FC_WT       0x31U /* N_PCItype FC and FlowStatus WT */
#define CANTP_N_PCI_FC_OVFLW    0x32U /* N_PCItype FC and FlowStatus OVFLW */
#define CANTP_N_PCI_CF_SN_MASK  0x0FU /* N_PCItype CF: mask for SN */
#define CANTP_N_PCI_SF_DL_MASK  0x0FU /* N_PCItype SF: mask for DL */
#define CANTP_N_PCI_FF_DL_MASK  0x0FU /* N_PCItype FF: mask for DL (first 4 bits) */

/* macros to distinguish N_PCI byte */

/** \brief return true if npci has frametype FC */
#define CANTP_IS_N_PCI_TYPE_FC(npci) \
    (((npci) & CANTP_N_PCI_TYPE_MASK) == CANTP_N_PCI_TYPE_FC)

/** \brief returns frame type */
#define CANTP_GET_N_PCI_TYPE(npci) \
    ((npci) & CANTP_N_PCI_TYPE_MASK)

/*------------------[critical sections]--------------------------------------*/

/** \brief macro CANTP_LOCK_CHANNEL
 **
 ** Locks a channel to ensure reentrancy protection for channel specific state
 ** machine. Concurrent events occuring while a channel is locked will be
 ** saved and executed when unlocking the channel.
 */
/* Deviation MISRA-1 */
#define CANTP_LOCK_CHANNEL(chptr)  do  \
  {                                    \
    (chptr)->ChannelLockFlag = 1U;     \
  } while(0U)

/** \brief macro CANTP_IS_CHANNEL_LOCKED
 **
 ** Returns true if the specified channel is locked, false otherwise.
 ** if the channel is locked, the caller has to save its event data in the
 ** channel structure.
 */
/* Deviation MISRA-1 */
#define CANTP_IS_CHANNEL_LOCKED(chptr)  ((chptr)->ChannelLockFlag != 0U)

/** \brief macro CANTP_UNLOCK_CHANNEL
 **
 ** Unlocks a previously locked channel and executes notification functions
 ** for channel specific events that occured in the meanwhile.
 **
 ** Note: implementation is done in the CanTp_UnlockChannel function
 */
/* Deviation MISRA-1 */
#define CANTP_UNLOCK_CHANNEL(chptr)  do  \
  {                                            \
    CanTp_UnlockChannel((chptr));      \
  } while(0U)

/*------------------[miscelleanous definitions]---------------------------------*/

/** \brief macro CANTP_PREPAREPADDING
 **
 ** Sets \a ChannelPtr->DLC to 8 and all bytes from
 ** ChannelPtr->DLC to end of frame to configured
 ** padding value (\a CANTP_PADDING_BYTE).
 */
/* Deviation MISRA-1 */
#define CANTP_PREPAREPADDING(ChannelPtr) do                     \
  {                                                             \
    uint8_least prepad_cnt;                                     \
    for(prepad_cnt = (ChannelPtr)->CanIfDLC ; prepad_cnt < CANTP_NPDU_LENGTH_MAX ; prepad_cnt++) \
    {                                                           \
      (ChannelPtr)->CanIfData[prepad_cnt] = CANTP_PADDING_BYTE; \
    }                                                           \
    (ChannelPtr)->CanIfDLC = CANTP_NPDU_LENGTH_MAX;             \
  } while(0)




/*==================[type definitions]=======================================*/

/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[external function declarations]=========================*/

#endif /* if !defined( CANTP_INTERNALLIB_H ) */
/*==================[end of file]============================================*/
