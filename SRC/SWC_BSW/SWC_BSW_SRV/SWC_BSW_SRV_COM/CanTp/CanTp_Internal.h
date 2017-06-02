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
#if(!defined CANTP_INTERNAL_H)
#define CANTP_INTERNAL_H


/*
 *  Misra-C:2004 Deviations:
 *
 *  MISRA-1) Deviated Rule: 19.7 (advisory)
 *    A function should be used in preference to a function-like macro.
 *
 *    Reason:
 *    Improved speed and readability outweighs using a function.
 *
 *  MISRA-2) Deviated Rule: Rule 16.10 (required)
 *    If a function returns error information, then that error information shall
 *    be tested.
 *
 *    Reason:
 *    No reaction possible on Det return value. Furthermore it shall be E_OK
 *    all the time so it is not really error information that is returned.
 *
 *  MISRA-3) Deviated Rule: 19.6 (required)
 *   #undef shall not be used.
 *
 *   Reason:
 *   In order to modify the behavior of the included file, enclosing the file
 *   inclusion by a special macro definition is required.
 */

/*==================[inclusions]=============================================*/

#include <ComStack_Types.h>       /* typedefs for AUTOSAR com stack */
#include <CanTp_InternalLib.h>    /* internal library definitions */
#include <CanTp_InternalCfg.h>    /* CanTp internal configuration */
#include <CanTp_Cfg.h>            /* CanTp configuration */
#include <CanTp_Types_Int.h>      /* generated CanTp postbuild types */
#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_ExitTable.h>      /* CanTp jumptable definitions */
#endif /* CANTP_JUMPTABLE_SUPPORT == STD_ON */

/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_CanTp.h */
#define PDUR_NO_PBCFG_REQUIRED
#include <PduR_CanTp.h>           /* PduR module API */
/* Deviation MISRA-3 */
#undef PDUR_NO_PBCFG_REQUIRED

/* !LINKSTO CanTp.ASR40.CANTP165,1 */
#include <SchM_CanTp.h>           /* Schedule manager public API */

#define TS_RELOCATABLE_CFG_ENABLE CANTP_RELOCATABLE_CFG_ENABLE
#include <TSPBConfig_Access.h>
/*==================[macros]=================================================*/

/*------------------[the CAN Tp Instance Id]---------------------------------*/

#if(defined CANTP_INSTANCE_ID)
#error CANTP_INSTANCE_ID is already defined
#endif
/* \brief instance id, used for DET */
#define CANTP_INSTANCE_ID     0U




/*------------------------[Defensive programming]----------------------------*/

#if (defined CANTP_PRECONDITION_ASSERT)
#error CANTP_PRECONDITION_ASSERT is already defined
#endif
#if (CANTP_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define CANTP_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), CANTP_MODULE_ID, CANTP_INSTANCE_ID, (ApiId))
#else
#define CANTP_PRECONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined CANTP_POSTCONDITION_ASSERT)
#error CANTP_POSTCONDITION_ASSERT is already defined
#endif
#if (CANTP_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define CANTP_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), CANTP_MODULE_ID, CANTP_INSTANCE_ID, (ApiId))
#else
#define CANTP_POSTCONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined CANTP_INVARIANT_ASSERT)
#error CANTP_INVARIANT_ASSERT is already defined
#endif
#if (CANTP_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define CANTP_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), CANTP_MODULE_ID, CANTP_INSTANCE_ID, (ApiId))
#else
#define CANTP_INVARIANT_ASSERT(Condition, ApiId)
#endif

#if (defined CANTP_STATIC_ASSERT)
# error CANTP_STATIC_ASSERT is already defined
#endif
#if (CANTP_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define CANTP_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define CANTP_STATIC_ASSERT(expr)
#endif

#if (defined CANTP_UNREACHABLE_CODE_ASSERT)
#error CANTP_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (CANTP_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **
 ** \param[in] ApiId Service ID of the API function */
#define CANTP_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(CANTP_MODULE_ID, CANTP_INSTANCE_ID, (ApiId))
#else
#define CANTP_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if (defined CANTP_INTERNAL_API_ID)
#error CANTP_INTERNAL_API_ID is already defined
#endif
/** \brief API ID of module internal functions to be used in assertions */
#define CANTP_INTERNAL_API_ID DET_INTERNAL_API_ID



/*------------------[critical section protection]----------------------------*/

/** \brief macro CANTP_ENTER_CRITICAL_SECTION
 **
 ** Calls the SchM to enter a critical section.
 */
/* Deviation MISRA-1 */
#define CANTP_ENTER_CRITICAL_SECTION()  do                                  \
  {                                                                         \
    CANTP_SCHM_ENTER_CANTP(); \
  } while(0U)

/** \brief macro CANTP_LEAVE_CRITICAL_SECTION
 **
 ** Calls the SchM to leave a critical section.
 */
/* Deviation MISRA-1 */
#define CANTP_LEAVE_CRITICAL_SECTION()  do                                 \
  {                                                                        \
    CANTP_SCHM_EXIT_CANTP(); \
  } while(0U)



/*--------------[access macros for external functions]-----------------------*/

/** \brief Macro to call external function Det_ReportError() */
/* Deviation MISRA-2 <START> */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_DET_REPORT_ERROR          (void)(CanTp_InitVars.ExitTablePtr->DetReportError)
#else
#define CANTP_DET_REPORT_ERROR          (void)Det_ReportError
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */
/* Deviation MISRA-2 <STOP> */


/** \brief Macro to call external function CanIf_Transmit() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_CANIF_TRANSMIT            (CanTp_InitVars.ExitTablePtr->CanIfTransmit)
#else
#define CANTP_CANIF_TRANSMIT            CanIf_Transmit
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

/** \brief Macro to call external function PduR_CanTpRxIndication() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_PDUR_RX_INDICATION        (CanTp_InitVars.ExitTablePtr->PduRCanTpRxIndication)
#else
#define CANTP_PDUR_RX_INDICATION        PduR_CanTpRxIndication
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

/** \brief Macro to call external function PduR_CanTpStartOfReception() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_PDUR_START_OF_RECEPTION    (CanTp_InitVars.ExitTablePtr->PduRCanTpStartOfReception)
#else
#define CANTP_PDUR_START_OF_RECEPTION    PduR_CanTpStartOfReception
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

/** \brief Macro to call external function PduR_CanTpCopyRxData() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_PDUR_COPY_RX_DATA    (CanTp_InitVars.ExitTablePtr->PduRCanTpCopyRxData)
#else
#define CANTP_PDUR_COPY_RX_DATA    PduR_CanTpCopyRxData
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */


/** \brief Macro to call external function PduR_CanTpCopyTxData() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_PDUR_COPY_TX_DATA    (CanTp_InitVars.ExitTablePtr->PduRCanTpCopyTxData)
#else
#define CANTP_PDUR_COPY_TX_DATA    PduR_CanTpCopyTxData
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

/** \brief Macro to call external function PduR_CanTpTxConfirmation() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_PDUR_TX_CONFIRMATION      (CanTp_InitVars.ExitTablePtr->PduRCanTpTxConfirmation)
#else
#define CANTP_PDUR_TX_CONFIRMATION      PduR_CanTpTxConfirmation
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

/** \brief Macro to call external function SchM_Enter_CanTp() */
#if(CANTP_EXIT_JUMPTABLE_WITH_SCHM == STD_ON)
#define CANTP_SCHM_ENTER_CANTP          (CanTp_InitVars.ExitTablePtr->SchMEnterCanTp)
#else
#define CANTP_SCHM_ENTER_CANTP          SchM_Enter_CanTp_SCHM_CANTP_EXCLUSIVE_AREA_0
#endif /* CANTP_EXIT_JUMPTABLE_WITH_SCHM == STD_ON */

/** \brief Macro to call external function SchM_Exit_CanTp() */
#if(CANTP_EXIT_JUMPTABLE_WITH_SCHM == STD_ON)
#define CANTP_SCHM_EXIT_CANTP           (CanTp_InitVars.ExitTablePtr->SchMExitCanTp)
#else
#define CANTP_SCHM_EXIT_CANTP           SchM_Exit_CanTp_SCHM_CANTP_EXCLUSIVE_AREA_0
#endif /* CANTP_EXIT_JUMPTABLE_WITH_SCHM == STD_ON */



#if(CANTP_USE_GPT == STD_ON)

/** \brief Macro to call external function Gpt_EnableNotification() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_GPT_ENABLE_NOTIFICATION   (CanTp_InitVars.ExitTablePtr->GptEnableNotification)
#else
#define CANTP_GPT_ENABLE_NOTIFICATION   Gpt_EnableNotification
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

/** \brief Macro to call external function Gpt_StartTimer() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_GPT_START_TIMER           (CanTp_InitVars.ExitTablePtr->GptStartTimer)
#else
#define CANTP_GPT_START_TIMER           Gpt_StartTimer
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

/** \brief Macro to call external function Gpt_StopTimer() */
#if(CANTP_PROVIDE_JUMPTABLE == STD_ON)
#define CANTP_GPT_STOP_TIMER            (CanTp_InitVars.ExitTablePtr->GptStopTimer)
#else
#define CANTP_GPT_STOP_TIMER            Gpt_StopTimer
#endif /* CANTP_PROVIDE_JUMPTABLE == STD_ON */

#endif /* CANTP_USE_GPT == STD_ON */


/*--------------[optimization related macros ]-------------------------------*/

/** \brief Byte index in CAN frame for first N_PCI byte
 **
 ** This macro delivers the index of the first N_PCI byte of the N-PDU given
 ** as a pointer as parameter. It is used for length calculations throughout
 ** the module.
 **
 ** \param[in] PduPtr Pointer to element of type CanTp_RxNPduTableType,
 **            CanTp_RxNSduConfigType or CanTp_TxNSduConfigType
 **
 ** \return Index of first N_PCI byte.
 ** \retval 0U if the N-PDU uses standard addressing format
 ** \retval 1U if the N-PDU uses mixed or extended addressing format
 */
#define CANTP_GET_FIRST_N_PCI_BYTE( PduPtr )   \
  ( (CANTP_GET_ADDR_FORMAT((PduPtr)) == CANTP_STANDARD) ? 0U : 1U )

/*--------------[relocatable postbuild related macros]-----------------------*/
#define CANTP_PBCFG_ACCESS(type, element) \
    (TS_UNCHECKEDGETCFG(CanTp_CfgPtr, type, CANTP, (element)))

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

#define CANTP_CFG_GET_RXNPDU_LOOKUPTABLE(Index)   \
    (CANTP_PBCFG_ACCESS(CanTp_RxNPduLookupEntryType, CanTp_CfgPtr->RxNPduLookupTablePtr)[(Index)])

#define CANTP_CFG_GET_RXNPDU_TABLE(Index)   \
    (CANTP_PBCFG_ACCESS(CanTp_RxNPduTableType, CanTp_CfgPtr->RxNPduTablePtr)[(Index)])

#define CANTP_CFG_GET_RXNSDU_CONFIG(Index)   \
    (CANTP_PBCFG_ACCESS(CanTp_RxNSduConfigType, CanTp_CfgPtr->RxNSduConfigPtr)[(Index)])

#define CANTP_CFG_GET_TXNSDU_CONFIG(Index)   \
    (CANTP_PBCFG_ACCESS(CanTp_TxNSduConfigType, CanTp_CfgPtr->TxNSduConfigPtr)[(Index)])

#if(CANTP_USE_GPT == STD_ON)
#define CANTP_CFG_GET_GPT_CHANNEL(Index)   \
    (CANTP_PBCFG_ACCESS(CanTp_GptChannelType, CanTp_CfgPtr->GptChannelPtr)[(Index)])
#endif /* CANTP_USE_GPT == STD_ON */

#define CANTP_CFG_GET_MFCTR_CONFIG(Index)   \
    (CANTP_PBCFG_ACCESS(CanTp_MfCtrConfigType, CanTp_CfgPtr->MfCtrConfigPtr)[(Index)])

#define CANTP_CFG_GET_TXNPDU_TPCHANNEL(Index)   \
    (CANTP_PBCFG_ACCESS(uint8, CanTp_CfgPtr->TxNPduToTpChannelPtr)[(Index)])

#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

/*==================[type definitions]=======================================*/

/*==================[external constants]=====================================*/

#define CANTP_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>


/** \brief CanTp global configuration */
extern P2CONST(CanTp_ConfigType, CANTP_VAR, CANTP_APPL_CONST) CanTp_CfgPtr;


#define CANTP_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]==========================================*/

/*==================[external function declarations]=========================*/

#define CANTP_START_SEC_CODE
#include <MemMap.h>

#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)

/** \brief Initialization of channel pointer
 **
 ** This function prepares the channel pointer for the next transmission
 ** and makes a clean up from the last transmission.
 **
 ** \param[in] ChannelPtr  pointer to channel data structure which will be cleaned
 */
extern FUNC(void, CANTP_CODE) CanTp_InitChannelPtr
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Request buffer for an I-PDU to transmit and continue transmission
 **
 ** This function handles the internal TX states. A transition from one state
 ** to another shall be performed by calling this state periodically. In
 ** addition CanTp_Transmit, CanTp_Rxindication(), CanTp_TxConfirmation() and
 ** timeouts may also initiate a transition.
 **
 ** Preconditions:
 ** - the given channel mode is CANTP_CH_MODE_TX.
 **
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to ease lookups
 */
FUNC(void, CANTP_CODE) CanTp_TxStateHandling
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Start of reception
 **
 ** This function indicates the upper layer about a new incoming reception. And
 ** handles the return value of the upper layer.
 **
 ** Preconditions:
 ** - the given channel is in state CANTP_CH_RX_BUFREQ_SF or
 **   CANTP_CH_RX_BUFREQ_FF
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to ease lookups
 **
 ** \return Result of last buffer request
 */
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_ProcessStartOfReception
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Copying received N-SDU data and requesting block size
 **
 ** This function requests buffer from upper layer to copy the received data
 ** of a SF or FF. In case that all data are already copied this function requests
 ** buffer from the upper layer to be used for block size calculation.
 **
 ** \pre The given channel is in state CANTP_CH_RX_BUFREQ_SF or
 **      CANTP_CH_RX_BUFREQ_FF. It is allowed to request a bigger buffer
 **      using NSduDataLength = 0U.
 **
 ** \param[in] ChannelPtr  Pointer to channel data structure to ease lookups
 ** \param[in] NPduDataPtr Pointer to the received data for the upper layer.
 ** \param[in] NSduDataLength Length of the received data indicated by NPduDataPtr
 **
 ** \return The function returns the status of the data copy request.
 **
 ** \retval BUFREQ_OK The function will return BUFREQ_OK, all data are copied to
 **                   upper layer.
 */
extern FUNC(BufReq_ReturnType, CANTP_CODE) CanTp_ProcessStartOfReceptionData
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) NPduDataPtr,
  uint8 NSduDataLength
);


/** \brief Rx state handling
 **
 ** This function handles the internal RX states. A transition from one state
 ** to another shall be performed by calling this state periodically. In
 ** addition CanTp_Rxindication(), CanTp_TxConfirmation() and timeouts may also
 ** initiate a transition.
 **
 **  ** Preconditions:
 ** - the given channel mode is CANTP_CH_MODE_RX.
 **
 ** \param[in] ChannelPtr  Pointer to channel data structure to ease lookups
 */
extern FUNC(void, CANTP_CODE) CanTp_RxStateHandling
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Prepares a SF, FF or a CF
 **
 ** This function prepares a SF, FF or a CF to transmit via CanIf. It fills
 ** the header according to the frame type and copies the payload from the
 ** temporary buffer.
 **
 ** Preconditions:
 ** - Channel must be in state CANTP_CH_TX_TRANSMIT_SF,
 **   CANTP_CH_TX_TRANSMIT_FF, or CANTP_CH_TX_TRANSMIT_CF.
 ** - The temporary buffer must hold the payload suitable for the next frame.
 ** - note: the channel state is not checked to be one of the above states!
 **   if the function is called while the channel is in a wrong state,
 **   random/corrupt data may be sent!
 **
 ** \param[in] ChannelPtr  pointer to channel that should prepare the xF
 **
 ** Note that PayloadSize shall already be calculated by the caller.
 */
extern FUNC(void, CANTP_CODE) CanTp_PreparexF
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief Prepares a FC continue to send
 **
 ** This function transmits a flow control frame with continue to send msg.
 ** The Blocksize is calculated automatically
 **
 ** \param[in] ChannelPtr  pointer to Rx channel that should prepare the FC cts
 */
extern FUNC(void, CANTP_CODE) CanTp_PrepareFCcts
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);

/** \brief Prepares a FC wait
 **
 ** This function prepares a flow control frame with wait msg.
 **
 ** \param[in] ChannelPtr  pointer to channel that should prepare the FC
 */
extern FUNC(void, CANTP_CODE) CanTp_PrepareFCwt
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Prepares a FC overflow
 **
 ** This function transmits a flow control frame with overflow msg.
 **
 ** \param[in] ChannelPtr  pointer to channel that should prepare the FC
 */
extern FUNC(void, CANTP_CODE) CanTp_PrepareFCovflw
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Transmits a CAN frame via CanIf
 **
 ** This function transmits a frame via CanIf
 ** - on busy the transmit will be repeated later
 ** - on error the whole transmission will be stopped
 **
 ** Preconditions:
 ** - data must be prepared for transmission
 ** - Channel must be in a state with action TRANSMIT.
 **
 ** \param[in] ChannelPtr  pointer to channel data structure in RAM
 */
extern FUNC(void, CANTP_CODE) CanTp_TransmitFrame
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Indirect callback function for STmin timeout
 **
 ** This callback function is called indirectly either by the General Purpose
 ** Timer or by the CanTp_MainFunction (depending on configuration).
 ** The function is called when STmin for the next CF is over. The CF is sent
 ** immediately.
 **
 ** \param[in] Channel  Channel to send next consecutive frame
 */
extern FUNC(void, CANTP_CODE) CanTp_STminCallback
(
  uint8 Channel
);


/** \brief Stops a connection channel
 **
 ** This function brings the given channel to idle mode
 ** If ULIndication is CANTP_ULIND_STATUS, the upper layer will be informed of
 ** the stopped transmission or reception.
 **
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to ease lookups
 ** \param[in] ULIndication  info if upper layer shall be informed or not
 ** \param[in] Result  result of the connection
 */
extern FUNC(void, CANTP_CODE) CanTp_StopChannel
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  CanTp_ULIndicationType ULIndication,
  NotifResultType Result
);


/** \brief Unlock a channel
 **
 ** This function releases a connection channel and takes care of any
 ** postticks.
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to simplify lookups
 */
extern FUNC(void, CANTP_CODE) CanTp_UnlockChannel
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Handles Timeouts
 **
 ** This function handles different timeout conditions and notifies PduR with
 ** corresponding timeout errors
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to simplify lookups
 */
extern FUNC(void, CANTP_CODE) CanTp_TimeoutHandling
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Calculate the block size
 **
 ** This function calculates the block size based on the available buffer.
 **
 ** \pre The block size shall only be calculated before sending FC(CTS) of a
 **      received first frame.
 **
 ** \param[in] ChannelPtr Pointer to Rx channel which needs block size calculation.
 ** \param[out] BlockSizePtr Parameter pointer returns the result of the block size calculation.
 **
 ** \return The function returns the result of the calculation.
 **
 ** \retval E_OK The calculation was successful. The block size is provided via
 **              output parameter.
 ** \retval E_NOT_OK Provided buffer is too small. Output parameter shall not be used.
 **
 */
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_CalculateBlockSize
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) BlockSizePtr
);


/** \brief Verify the block size
 **
 ** This function compares the block size of the channel with the provided available buffer
 ** of the upper layer.
 **
 **
 ** \param[in] ChannelPtr  Pointer to Rx channel which needs block size verification.
 **
 ** \return The function returns the result of the comparison
 **
 ** \retval TRUE The function will return TRUE, if the the available buffer suits
 **         the actual block size requirement.
 ** \retval FALSE The function will return FALSE, if the available buffer is smaller
 **               than the actual block size.
 */
extern FUNC(boolean, CANTP_CODE) CanTp_VerifyBlockSize
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Copy N-Sdu data to upper layer.
 **
 ** This function tries to copy the provided data to the upper layer. Depending on
 ** the return value of the copy process the available upper layer buffer will be
 ** provided through the channel structure.
 **
 ** \pre The data to copy shall fit into the available buffer. It is allowed to
 **      request a bigger buffer using NPduDataPtr = NULL_PTR and NSduDataLength = 0U.
 **
 ** \param[in] ChannelPtr  Pointer to the channel structure.
 ** \param[in] NPduDataPtr Pointer to the received data for the upper layer.
 ** \param[in] NSduDataLength Length of the received data indicated by NPduDataPtr
 **
 ** \return The function returns the status of the data copy request.
 **
 */
extern FUNC(BufReq_ReturnType, CANTP_CODE) CanTp_RxProcessData
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr,
  P2VAR(uint8, AUTOMATIC, CANTP_VAR) NPduDataPtr,
  uint8 NSduDataLength
);


/** \brief Check and handle wait frame timeout.
 **
 ** This function checks the timeout N_Br and starts the sending
 ** process of the wait frame if timeout has elapsed.
 **
 ** \pre Shall be used if timeout N_Br is set and wait frame sending is required.
 **
 ** \param[in] ChannelPtr  Pointer to the channel structure.
 **
 */
extern FUNC(void, CANTP_CODE) CanTp_CheckAndHandleWaitFrameTimeOut
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Processes postponed Rx indication
 **
 ** This function processes postponed Rx indication which occurs during
 ** channel lock.
 **
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to ease lookups
 */
extern FUNC(void, CANTP_CODE) CanTp_PostRxIndication
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Processes postponed Tx confirmation
 **
 ** This function processes postponed Tx confirmation which occurs during
 ** channel lock.
 **
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to ease lookups
 */
extern FUNC(void, CANTP_CODE) CanTp_PostTxConfirmation
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


/** \brief Processes postponed STmin timeout
 **
 ** This function processes postponed STmin timeout which occurs during
 ** channel lock.
 **
 **
 ** \param[in] ChannelPtr  pointer to channel data structure to ease lookups
 */
extern FUNC(void, CANTP_CODE) CanTp_PostSTminCallback
(
  P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr
);


#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#define CANTP_STOP_SEC_CODE
#include <MemMap.h>

/* Deviation MISRA-3 */
#undef TS_RELOCATABLE_CFG_ENABLE

#endif /* if !defined( CANTP_INTERNAL_H ) */
/*==================[end of file]============================================*/
