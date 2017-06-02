/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined COMM_BSW_CFG_H)
#define COMM_BSW_CFG_H

/*==================[inclusions]============================================*/

#include <ComStack_Types.h>  /* AUTOSAR Com Stack standard types */
#include <TSAutosar.h>       /* TS_PROD_* symbols */

#include <ComM_BSW.h>        /* public dependent header */

#include <ComM_Hsm.h>           /* New state machine generic API header */
#include <ComM_HsmComM.h>       /* New state machine custom part */
#include <ComM_HsmComMInt.h>    /* internal statechart model definitions */
#include <ComM_HsmComMPnc.h>    /* Pnc state machine */
#include <ComM_HsmComMPncInt.h> /* Internal statechart of Pnc model definitions */

/*==================[macros]================================================*/

/** \brief Nm variant types used for values of COMM_NM_VARIANT_OF_CHANNEL(). */
#define COMM_NM_FULL_VARIANT                  0U
#define COMM_NM_LIGHT_VARIANT                 1U
#define COMM_NM_NONE_VARIANT                  2U
#define COMM_NM_PASSIVE_VARIANT               3U

/** \brief Bus types used as values for COMM_BUSTYPE_OF_CHANNEL(). */
#define COMM_BUS_TYPE_CAN                     0U
#define COMM_BUS_TYPE_ETH                     1U
#define COMM_BUS_TYPE_FR                      2U
#define COMM_BUS_TYPE_INTERNAL                3U
#define COMM_BUS_TYPE_LIN                     4U

/** \brief Macros for Communication Inhibition. */
#define COMM_LIMIT_NOCOMM                     2U
#define COMM_LIMIT_NOCOMM_MASK              253U
#define COMM_PREVENT_WAKEUP                   1U
#define COMM_PREVENT_WAKEUP_MASK            254U

#define COMM_NUM_CHANNELS_BYTES  (((COMM_NUM_CHANNELS - 1U) / 8U) + 1U)
#define COMM_NUM_PNC_BYTES  (((COMM_NUM_PNC - 1U) / 8U) + 1U)

#if (defined COMM_DET_REPORT_ERROR)
#error COMM_DET_REPORT_ERROR already defined
#endif
/* define function like macro for development error reporting,
 * if development error detection is enabled */
#if (COMM_DEV_ERROR_DETECT == STD_ON)

/** \brief Macro for reporting an error to DET
 **
 ** \param[in] InstanceId Instance ID of the API function
 ** \param[in] ApiId Service ID of the API function
 ** \param[in] ErrorId Error code reported to Det module */
#define COMM_DET_REPORT_ERROR(InstanceId, ApiId, ErrorId)    \
  ((void)Det_ReportError(COMM_MODULE_ID, (InstanceId), (ApiId), (ErrorId)))
#else
#define COMM_DET_REPORT_ERROR(InstanceId, ApiId, ErrorId)
#endif /* if (COMM_DEV_ERROR_DETECT == STD_ON) */

/*==================[type definitions]======================================*/

#if (COMM_NUM_TX_EIRA_SIGNALS > 0U)
/** \brief Type for PNC to EIRA Signal mapping */
typedef struct
{
  P2CONST(uint8, TYPEDEF, COMM_APPL_CONST) TxSignalList;
  uint8 NumTxSignal;
}ComM_PncTxEiraSigMapType;
#endif

/*==================[external function declarations]========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Evaluate NoCom Inhibition for ComM Channels
 ** This function checks the ComM channel NoCom Inhibition
 ** is set.
 ** \param[in] instIdx index of state machine instance
 **
 ** \return Status of NoCom inhibition setting.
 ** \retval TRUE if inhibition is set.
 ** \retval FALSE if inhibition is not set. */
extern FUNC(boolean, COMM_CODE) ComM_ChannelNoComInhibitionStatus
(
  const uint8 instIdx
);
#endif

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief Evaluate WakeUp Inhibition for ComM Channels
 ** This function checks the ComM channel WakeUp Inhibition
 ** is set.
 ** \param[in] instIdx index of state machine instance
 **
 ** \return Status of WakeUp inhibition setting.
 ** \retval TRUE if inhibition is set.
 ** \retval FALSE if inhibition is not set. */
extern FUNC(boolean, COMM_CODE) ComM_ChannelWakeUpInhibitionStatus
(
  const uint8 instIdx
);
#endif

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/** \brief Set Inhibition status for ComM Channels
 ** This function set and resets the ComM channel Inhibition
 ** \param[in] instIdx index of state machine instance
 ** \param[in] Inhibitiontype Inhibition type of ComM channel.
 ** \param[in] Status to be set. */
extern FUNC(void, COMM_CODE) ComM_SetChannelComMInhibitionStatus
(
  const uint8 instIdx,
  const ComM_ASR40_InhibitionStatusType Inhibitiontype,
  const boolean Status
);
#endif

/** \brief Processes the timer for a channel.
 *
 * This function decreases the timer of the specified channel and emits an event, when the timer
 * expires.
 *
 * \param[in] Channel Channel for which the timers are processed
 */
extern FUNC(void, COMM_CODE) ComM_ProcessTimers(
  const uint8 Channel);

/** \brief Set the x-th bit in a bit array
 * \param[in] arr array of uint8
 * \param[in] idx number of bit to be set to 1 */
extern FUNC(void, COMM_CODE) ComM_BitArraySet
(
  CONSTP2VAR(uint8, AUTOMATIC, COMM_VAR) arr,
  const uint16                           idx
);

/** \brief Clear the x-th bit in a bit array
 * \param[in] arr array of uint8
 * \param[in] idx number of bit to be set to 0 */
extern FUNC(void, COMM_CODE) ComM_BitArrayClear
(
  CONSTP2VAR(uint8, AUTOMATIC, COMM_VAR) arr,
  const uint16                           idx
);

/** \brief Test the x-th bit in a bit array
 * \param[in] arr array of uint8
 * \param[in] idx number of bit to be tested
 * \return TRUE or FALSE whether x-th bit is set or not. */
extern FUNC(boolean, COMM_CODE) ComM_BitArrayIsBitSet
(
  CONSTP2CONST(uint8, AUTOMATIC, COMM_VAR) arr,
  const uint16                             idx
);


#if (COMM_PNC_SUPPORT == STD_ON)
/** \brief Main processing function of PNC */
extern FUNC(void, COMM_CODE) ComM_PncMainFunction(void);

/** \brief Timer processing function of PNC */
extern FUNC(void, COMM_CODE) ComM_PncProcessTimers(void);

#endif

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define COMM_START_SEC_CONST_8
#include <MemMap.h>

#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON)
/** \brief Bus type of channel given by index */
extern CONST(uint8, COMM_CONST) ComM_BusTypeOfChannel[COMM_NUM_CHANNELS];
#endif

#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
/** \brief NM variant of channel given by index */
extern CONST(uint8, COMM_CONST) ComM_NmVariantOfChannel[COMM_NUM_CHANNELS];
#endif

#if (COMM_NUM_CHANNELS > 1U)
/** \brief Number of users of channel given by index */
extern CONST(uint8, COMM_CONST) ComM_NumUsersOfChannel[COMM_NUM_CHANNELS];

/** \brief Nm channel handle associated to ComM channel given by index */
extern CONST(NetworkHandleType, COMM_CONST)
  ComM_NmChannelOfChannel[COMM_NUM_CHANNELS];
#endif

/** \brief Number of channels of user given by index */
extern CONST(uint8, COMM_CONST) ComM_NumChannelsOfUser[COMM_NUM_USERS];

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief Persistent storage of WakeUp inhibition status of channels in NvM */
extern CONST(uint8, COMM_CONST) ComM_EB_NoWakeupNvStorage[COMM_NUM_BYTES_NVM];
#endif

#if (COMM_NUM_PNC > 0U)
/** \brief Number of Pncs needed by any user */
extern CONST(uint8, COMM_CONST) ComM_NumPncOfUser[COMM_NUM_USERS];

/** \brief Number of users mapped to any pnc */
extern CONST(uint8, COMM_CONST) ComM_NumUsersOfPnc[COMM_NUM_PNC];

/** \brief Number of channels mapped to each Pnc */
extern CONST(uint8, COMM_CONST) ComM_NumChannelsOfPnc[COMM_NUM_PNC];

/** \brief Number of PNCs required for each Channel */
extern CONST(uint8, COMM_CONST) ComM_NumPncOfCh[COMM_NUM_CHANNELS];

/** \brief IDs of all configured Pnc */
extern CONST(PNCHandleType, COMM_CONST) ComM_PncID[COMM_NUM_PNC];

/** \brief Request the network every time when entering Pnc_Requested state if
 *  configured as TRUE */
extern CONST(boolean, COMM_CONST) ComM_PncNmRequest[COMM_NUM_CHANNELS];

#endif

#define COMM_STOP_SEC_CONST_8
#include <MemMap.h>

#define COMM_START_SEC_CONST_16
#include <MemMap.h>

/** \brief Main function period in ms for each channel in ms. */
extern CONST(uint16, COMM_CONST) ComM_MainFunctionPeriodMs[COMM_NUM_CHANNELS];

#if (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)
/** \brief Ready Sleep Timeout
 **
 ** These variables hold the timeout value for ready sleep state in ms.  After
 ** this time the ready sleep state is left and the the transition to the
 ** state "no communication" is performed.  This timeout is only relevant and
 ** used for channels of Nm variant NONE and LIGHT.  For channels of NmVariant
 ** LIGHT the timeout value is given by the configuration parameter
 ** ComMNmLightTimeout. */
extern CONST(uint16, COMM_CONST)
  ComM_ReadySleepNoNmTimeoutMs[COMM_NUM_CHANNELS];
#endif

/** \brief Maximum number of times that ComM can retry requesting the BusSM for
 ** communication mode
 ** */
extern CONST(uint16, COMM_CONST)
  ComM_BusSMMaxRetryCount[COMM_NUM_CHANNELS];

#if ((COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON)           \
     || (COMM_NM_VARIANT_NONE_NEEDED == STD_ON))
/** \brief NetReqNoNmTimeout
 **
 ** These variables hold the timeout value for Full Com Network Request state
 ** in ms.  After this time the Full Com Network Request state is left and the
 ** the transition to the state "ready sleep" is performed.  This timeout is
 ** only relevant and used for channels of Nm variant NONE and LIGHT. */
extern CONST(uint16, COMM_CONST)
  ComM_NetReqNoNmTimeoutMs[COMM_NUM_CHANNELS];
#endif


#if (COMM_PNC_SUPPORT == STD_ON)
/** \brief Array of Rx EIRA ComSignal Handle Ids
 **        sorted in the ascending order */
extern CONST(Com_SignalIdType, COMM_CONST) ComM_RxComSignalCfg[COMM_NUM_RX_EIRA_SIGNALS];

/** \brief Array of Tx EIRA ComSignal Handle Ids
 **        sorted in the ascending order */
extern CONST(Com_SignalIdType, COMM_CONST) ComM_TxComSignalCfg[COMM_NUM_TX_EIRA_SIGNALS];

#endif

#define COMM_STOP_SEC_CONST_16
#include <MemMap.h>

#define COMM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array of ptr to arrays containing the ComM network channel ID of a
 * user
 *
 * The ComM user ID acts as index to this array. */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_ChannelsOfUser[COMM_NUM_USERS];

/** \brief Array of ptr to arrays containing the user IDs of a channel
 *
 * The ComM network channel ID acts as index to this array. */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_UsersOfChannel[COMM_NUM_CHANNELS];


/** \brief Array of ptr to arrays containing the PNC IDs of a channel
 *
 * The ComM network channel ID acts as index to this array. */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
  ComM_PNCsOfChannel[COMM_NUM_CHANNELS];

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Default ComMNoCom
 **
 ** Default value configured for ComMNoCom */
extern CONST(ComM_ASR40_InhibitionStatusType, COMM_CONST)
  ComM_ChannelInhibitionStatusInit[COMM_NUM_BYTES_NVM];
#endif


#if (COMM_PNC_SUPPORT == STD_ON)

/** \brief Index of pnc needed by any user */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
                                   ComM_PncOfUser[COMM_NUM_USERS];

/** \brief Index of user needed by any pnc */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST)
                                    ComM_UsersOfPnc[COMM_NUM_PNC];

/** \brief  The ComM channels mapped to the Pnc. */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST) ComM_ChannelsOfPnc[COMM_NUM_PNC];

/** \brief List of Tx EIRA Com signals associated with each PNC */
extern CONST(ComM_PncTxEiraSigMapType, COMM_CONST) ComM_PncTxEiraSignalMap[COMM_NUM_PNC];

/** \brief Bit array of Rx Eira Com signal masks
 *
 * A PNC may not have references to all RX EIRA Com signals.
 * Therefore, the bits corresponding to PNCs which do not
 * reference a Com signal have to be masked out from
 * the newly received EIRA before being merged to the
 * existing EIRA bits.
 * This array contains references to bit arrays
 * for each RX EIRA Com signal.
 * If a Com Signal is associated to a PNC, then the bit
 * corresponding to that PNC in the bit array will be set to 1.
 * If a Com Signal is not associated to a PNC, then the
 * corresponding bit in the bit array will be set to 0.
 */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST) ComM_PncRxEiraMask[COMM_NUM_RX_EIRA_SIGNALS];

/** \brief Bit array of Tx Eira Com signal masks
 *
 * A PNC may not have references to all TX EIRA Com signals.
 * Therefore, the bits corresponding to PNCs which do not
 * reference a Com signal have to be masked out from
 * the EIRA before being sent via the Com signal.
 * This array contains references to bit arrays
 * for each TX EIRA Com signal.
 * If a Com Signal is associated to a PNC, then the bit
 * corresponding to that PNC in the bit array will be set to 1.
 * If a Com Signal is not associated to a PNC, then the
 * corresponding bit in the bit array will be set to 0.
 */
extern CONSTP2CONST(uint8, COMM_CONST, COMM_CONST) ComM_PncTxEiraMask[COMM_NUM_TX_EIRA_SIGNALS];

#endif /* if (COMM_PNC_SUPPORT == STD_ON) */

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief Storage for NoWakeUpInhibition in the NvM block
 *  pointed by ComMGlobalNvmBlockDescriptor */
extern CONST(ComM_ASR40_InhibitionStatusType, COMM_CONST)
  ComM_StoreNoWakeUpInhibition[COMM_NUM_CHANNELS];
#endif

#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define COMM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#if (COMM_DCM_ENABLED == STD_ON)
/** \brief Flag to be set if DCM indicated active communication */
extern VAR(uint8, COMM_VAR) ComM_DcmActiveStatus[COMM_NUM_CHANNELS_BYTES];
#endif

/** \brief number of bytes needed to store CommunicationAllowed flags  */
extern VAR(uint8, COMM_VAR) ComM_Communication_Allowed[COMM_NUM_CHANNELS_BYTES];

/** \brief ComM Requested Mode
 **
 ** This variable holds the currently requested mode. */
extern VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_RequestedComMode[COMM_NUM_CHANNELS];

/** \brief ComM Channel Mode
 **
 ** This variable holds the current mode of the ComM Channel. */
extern VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_ChannelMode[COMM_NUM_CHANNELS];

/** \brief ComM Channel State
 **
 ** This variable holds the current state of the ComM Channel. */
extern VAR(ComM_StateType, COMM_VAR) ComM_ChanState[COMM_NUM_CHANNELS];

/** \brief ComM User Requested Mode
 **
 ** This variable holds the current user requested mode. */
extern VAR(ComM_ASR40_ModeType, COMM_VAR) ComM_UserRequestedComMode[COMM_NUM_USERS];

#if (COMM_PNC_SUPPORT == STD_ON)
/** \brief This variable holds data for sending Eira signal */
extern VAR(uint8, COMM_VAR) ComM_TxEira[COMM_PN_INFO_LENGTH];

/** \brief This variable holds the received EIRA signal  */
extern VAR(uint8, COMM_VAR) ComM_RxEira[COMM_PN_INFO_LENGTH];

/** \brief Holds the Status flag indicating changes in the EIRA signals */
extern VAR(boolean, COMM_VAR) ComM_RxEiraSignalStatus;

/** \brief Active Status of ComM Channels
 *
 * This array holds a bit for each ComM channel and it represents
 * whether or not the channel is still actively used by at least
 * one PNC via an internal request.
 * The corresponding bit for the channel is set to 1 when
 * entering the PNC_REQUESTED state.
 * The corresponding bit is set to 0 when there is no other active 
 * PNC using this channel.
 */
extern VAR(uint8, COMM_VAR) ComM_ChannelActiveStatus[COMM_NUM_CHANNELS_BYTES];

/** \brief Active status of ComM PNC's
 * This array holds a bit for each PNC and it represents whether or not
 * it's considered to be active.
 * If the PNC is internally requested via a Full Communication request by
 * a ComM user, the corresponding bit in this array is set to 1 when 
 * A PNC is considered not to be active anymore depending on the 
 * ComMPncReleaseChannel configuration parameter.
 * In case this is set to COMM_NO_INTERNAL_AND_EXTERNAL_REQUESTS,
 * a PNC is not active anymore only when reaching the PNC_NO_COMMUNICATION state.
 * In case this is set to COMM_NO_INTERNAL_REQUESTS, a PNC is not active
 * anymore when leaving the PNC_REQUESTED state.
 * Note: A PNC which is only externally requested is not considered to 
 * be active in case ComMPncReleaseChannel is set to 
 * COMM_NO_INTERNAL_AND_EXTERNAL_REQUESTS.
 */
extern VAR(uint8, COMM_VAR) ComM_PncActiveStatus[COMM_NUM_PNC_BYTES];

#endif /* if (COMM_PNC_SUPPORT == STD_ON) */

#define COMM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define COMM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief ComM Initialization status
 **
 ** This variable holds the current initialization status of the ComM
 ** module. */
extern VAR(ComM_InitStatusType, COMM_VAR) ComM_InitStatus;

#define COMM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( COMM_BSW_CFG_H ) */
/*==================[end of file]===========================================*/
