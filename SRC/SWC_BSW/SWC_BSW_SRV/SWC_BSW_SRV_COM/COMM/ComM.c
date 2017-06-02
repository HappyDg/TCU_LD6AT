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


/* !LINKSTO ComM463_Refine_ComMc,1 */

/* MISRA-C:2004 Deviation List
 *
 * MISRA-1) Deviated Rule: 12.4 (required)
 *     The right-hand operand of a logical '&&' or '||' operator shall
 *     not contain side effects.
 *
 *     Reason:
 *     The functions which are called to calculate the operands do not
 *     have side effects.
 *
 * MISRA-2) Deviated Rule: 13.7 (required)
 *     Boolean operations whose results are invariant shall not be permitted.
 *
 *     Reason:
 *     This is not a programming error. This approach has been deliberately
 *     selected to apply a common method to access the channel configuration
 *     data in all configuration possibilities.
 *
 * MISRA-3) Deviated Rule: 16.7 (required)
 *     A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the addressed
 *     object.
 *
 *     Reason:
 *     The parameter 'ComMode' in the function prototype of
 *     'ComM_BusSM_ModeIndication' is declared as specified in the AUTOSAR
 *     Specification of Communication Manager V4.0.0. An AUTOSAR Bugzilla
 *     RFC (http://www.autosar.org/bugzilla/show_bug.cgi?id=58167) has been
 *     created to fix this issue in the specification.
 */

 /*==================[inclusions]============================================*/

#include <ComM_Trace.h>
/* !LINKSTO ComM466,1 */
#include <Std_Types.h>          /* AUTOSAR standard types */
#include <TSAutosar.h>          /* EB specific standard types */
#include <TSMem.h>

#include <ComM_BSW.h>           /* Module specific public APIs */

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
#include <ComM_Nm.h>            /* NM callback APIs */
#endif

#if (COMM_DCM_ENABLED == STD_ON)
#include <ComM_Dcm.h>           /* DCM callback APIs */
#endif

#include <ComM_EcuMBswM.h>      /* ECUM and BSWM callback APIs */
#include <ComM_BusSm.h>         /* Bus State manager callback APIs */

#include <ComM_BSW_Cfg.h>      /* Module internal BSW specific interface */
#include <ComM_Int.h>           /* Internal Rte proxy function declarations */

#if (COMM_NVM_ENABLED == STD_ON)
/* !LINKSTO ComM506_Refine_NvM,1 */
#include <NvM.h>                /* Memory Access APIs */
#endif

#if (COMM_DEV_ERROR_DETECT == STD_ON)
/* !LINKSTO ComM506_Refine_Det,1 */
#include <Det.h>                /* Det API */
#endif

#if (COMM_INCLUDE_RTE == STD_ON)
#include <ComM_Rte_Cfg.h>  /* internal Rte config dependent header */
#endif

/* for the case COMM_INCLUDE_RTE == STD_OFF these symbols are provided via
 * ComM.h. */

/*==================[macros]================================================*/

/* !LINKSTO ComM.Version.Check,1 */
/*------------------[AUTOSAR vendor identification check]-------------------*/

#if (!defined COMM_VENDOR_ID) /* configuration check */
#error COMM_VENDOR_ID must be defined
#endif

#if (COMM_VENDOR_ID != 1U) /* vendor check */
#error COMM_VENDOR_ID has wrong vendor id
#endif

/*------------------[AUTOSAR release version identification check]----------*/

#if (!defined COMM_AR_RELEASE_MAJOR_VERSION) /* configuration check */
#error COMM_AR_RELEASE_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (COMM_AR_RELEASE_MAJOR_VERSION != 4U)
#error COMM_AR_RELEASE_MAJOR_VERSION wrong (!= 4U)
#endif

#if (!defined COMM_AR_RELEASE_MINOR_VERSION) /* configuration check */
#error COMM_AR_RELEASE_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (COMM_AR_RELEASE_MINOR_VERSION != 0U )
#error COMM_AR_RELEASE_MINOR_VERSION wrong (!= 0U)
#endif

#if (!defined COMM_AR_RELEASE_REVISION_VERSION) /* configuration check */
#error COMM_AR_RELEASE_REVISION_VERSION must be defined
#endif

/* revision version check */
#if (COMM_AR_RELEASE_REVISION_VERSION != 3U )
#error COMM_AR_RELEASE_REVISION_VERSION wrong (!= 3U)
#endif

/*------------------[AUTOSAR module version identification check]-----------*/

#if (!defined COMM_SW_MAJOR_VERSION) /* configuration check */
#error COMM_SW_MAJOR_VERSION must be defined
#endif

/* major version check */
#if (COMM_SW_MAJOR_VERSION != 5U)
#error COMM_SW_MAJOR_VERSION wrong (!= 5U)
#endif

#if (!defined COMM_SW_MINOR_VERSION) /* configuration check */
#error COMM_SW_MINOR_VERSION must be defined
#endif

/* minor version check */
#if (COMM_SW_MINOR_VERSION < 6U)
#error COMM_SW_MINOR_VERSION wrong (< 6U)
#endif

#if (!defined COMM_SW_PATCH_VERSION) /* configuration check */
#error COMM_SW_PATCH_VERSION must be defined
#endif

/* patch version check */
#if (COMM_SW_PATCH_VERSION < 4U)
#error COMM_SW_PATCH_VERSION wrong (< 4U)
#endif

/*--------------------------------------------------------------------------*/
/* !LINKSTO ComM103_Refine,1 */
#if ((COMM_NVM_ENABLED == STD_ON) &&                \
     ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)))
#define COMM_PERS_DATA_MODIFIED()                                      \
        ((void) NvM_SetRamBlockStatus(COMM_NVM_BLOCK_DESCRIPTOR, TRUE))
#else
#define COMM_PERS_DATA_MODIFIED()
#endif

/** \brief ID for the invalid event */
#define COMM_EVENT_INVALID                  255U

/** \brief Set an event for a specific ComM channel */
#define COMM_EMIT(a,b) (void)COMM_HSMEMITINST(&ComM_HsmScComM, a, b)

/** \brief Set an event for a specific ComM PN Channel */
#define COMM_PNC_EMIT(a,b) (void)COMM_HSMEMITINST(&ComM_HsmScComMPnc, a, b)

/*--------------------------------------------------------------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
#define COMM_NCI_OR_FALSE(Channel)                             \
        (TRUE == ComM_ChannelNoComInhibitionStatus(Channel))
#define COMM_NCI_OR_TRUE(Channel)                              \
        (TRUE == ComM_ChannelNoComInhibitionStatus(Channel))
#endif

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
#define COMM_WUI_OR_FALSE(Channel)                             \
        (TRUE == ComM_ChannelWakeUpInhibitionStatus(Channel))
#define COMM_WUI_OR_TRUE(Channel)                              \
        (TRUE == ComM_ChannelWakeUpInhibitionStatus(Channel))
#define COMM_WUINOCOM_OR_FALSE(Channel)                                \
        ((TRUE == ComM_ChannelWakeUpInhibitionStatus(Channel))  &&     \
         (COMM_NO_COMMUNICATION == ComM_ChannelMode[(Channel)])        \
        )
#endif

/*--------------------------------------------------------------------------*/

/* Macro for Det checks of channel identifier as function argument */
#if ((COMM_NM_VARIANT_NONE_NEEDED == STD_ON) && (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON))
#define COMM_IS_CHANNEL_INVALID(Channel)                               \
        ((((Channel) >= COMM_NUM_CHANNELS) ||                                   \
          (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_NONE_VARIANT)       \
         ) ||                                                                 \
         (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_LIGHT_VARIANT)       \
        )
#elif ((COMM_NM_VARIANT_NONE_NEEDED == STD_ON) && (COMM_NM_VARIANT_LIGHT_NEEDED == STD_OFF))
#define COMM_IS_CHANNEL_INVALID(Channel)                               \
        (((Channel) >= COMM_NUM_CHANNELS) ||                                    \
         (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_NONE_VARIANT)        \
        )
#elif ((COMM_NM_VARIANT_NONE_NEEDED == STD_OFF) && (COMM_NM_VARIANT_LIGHT_NEEDED == STD_ON))
#define COMM_IS_CHANNEL_INVALID(Channel)                               \
        (((Channel) >= COMM_NUM_CHANNELS) ||                                    \
         (COMM_NM_VARIANT_OF_CHANNEL(Channel) == COMM_NM_LIGHT_VARIANT)       \
        )
#else
#define COMM_IS_CHANNEL_INVALID(Channel) ((Channel) >= COMM_NUM_CHANNELS)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

#if (COMM_PNC_SUPPORT == STD_ON)
/** \brief Evaluate ComM Partial Network Cluster
 ** This function checks the ComM PNC mode and emits specific event
 ** related to the mode of the PNC.
 ** \param[in] Pnc Partial Network Cluster  on which the mode transition
 **                    has occurred.
 ** \param[in] ComMode Maximum allowed communication mode. */
STATIC FUNC(void, COMM_CODE) ComM_EvaluatePnc
(
  const uint8 Pnc,
  ComM_ASR40_ModeType ComMode
);
#endif

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

#define COMM_START_SEC_CONST_8
#include <MemMap.h>

#if (COMM_BUSTYPE_OF_CHANNEL_DYNAMIC == STD_ON)
CONST(uint8, COMM_CONST) ComM_BusTypeOfChannel[COMM_NUM_CHANNELS]
  = COMM_BUSTYPE_OF_CHANNEL_INIT;
#endif

#if (COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC == STD_ON)
CONST(uint8, COMM_CONST) ComM_NmVariantOfChannel[COMM_NUM_CHANNELS]
  = COMM_NM_VARIANT_OF_CHANNEL_INIT;
#endif

#define COMM_STOP_SEC_CONST_8
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define COMM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#if (COMM_DCM_ENABLED == STD_ON)
VAR(uint8, COMM_VAR)         ComM_DcmActiveStatus[COMM_NUM_CHANNELS_BYTES];
#endif /* if (COMM_DCM_ENABLED == STD_ON) */

VAR(uint8, COMM_VAR) ComM_Communication_Allowed[COMM_NUM_CHANNELS_BYTES];

VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_RequestedComMode[COMM_NUM_CHANNELS];

VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_ChannelMode[COMM_NUM_CHANNELS];

VAR(ComM_StateType, COMM_VAR)  ComM_ChanState[COMM_NUM_CHANNELS];

VAR(ComM_ASR40_ModeType, COMM_VAR)   ComM_UserRequestedComMode[COMM_NUM_USERS];

#if (COMM_PNC_SUPPORT == STD_ON)

VAR(uint8, COMM_VAR) ComM_TxEira[COMM_PN_INFO_LENGTH];
VAR(uint8, COMM_VAR) ComM_RxEira[COMM_PN_INFO_LENGTH];

VAR(boolean, COMM_VAR) ComM_RxEiraSignalStatus;

VAR(uint8, COMM_VAR) ComM_ChannelActiveStatus[COMM_NUM_CHANNELS_BYTES];

VAR(uint8, COMM_VAR) ComM_PncActiveStatus[COMM_NUM_PNC_BYTES];

#endif /* if (COMM_PNC_SUPPORT == STD_ON) */

#define COMM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define COMM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

VAR(ComM_InitStatusType, COMM_VAR) ComM_InitStatus = COMM_UNINIT;

#define COMM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
VAR(ComM_NvDataType, COMM_VAR) ComM_EB_NvRAM;
#endif

#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

#define COMM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/** \brief Array to store NoCom Inhibition status of ComM Channels. */
STATIC VAR(uint8, COMM_VAR) ComM_ChannelNoComInhibition[COMM_NUM_BYTES_NVM];
#endif

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/** \brief Array to store WakeUp Inhibition status of ComM Channels. */
STATIC VAR(uint8, COMM_VAR) ComM_ChannelWakeUpInhibition[COMM_NUM_BYTES_NVM];
#endif

#define COMM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/*==================[external function definitions]=========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/*------------------[ComM_Init]----------------------------------------------*/

FUNC(void, COMM_CODE) ComM_Init(void)
{
  uint8_least i;

  DBG_COMM_INIT_ENTRY();

  for (i = 0U; i < COMM_NUM_CHANNELS; ++i)
  {
    /* Requested communication mode for each channel */
    ComM_RequestedComMode[i]    = COMM_NO_COMMUNICATION;

    /* Initialize ComM Channel State */
    ComM_ChanState[i]          = COMM_NO_COM_NO_PENDING_REQUEST;

    /* Initialize ComM Channel Mode */
    ComM_ChannelMode[i]         = COMM_NO_COMMUNICATION;

    /* The persistent storage is supported we don't
     * to react on a NvM callback after the initialization as the
     * the Read All and Write All will called in EcuM_Init(). */
  }

  /* Requested communication mode of each user */
  TS_MemSet(ComM_UserRequestedComMode, COMM_NO_COMMUNICATION, COMM_NUM_USERS);

  /* Initialize ComM state machine, perform initial transitions */
  ComM_HsmInit(&ComM_HsmScComM);

  /* Initializing the Channel communication status and Dcm request status */
  for (i = 0U; i < COMM_NUM_CHANNELS_BYTES; ++i)
  {
    ComM_Communication_Allowed[i] = 0U;

#if (COMM_DCM_ENABLED == STD_ON)
    ComM_DcmActiveStatus[i] = 0U;
#endif

#if (COMM_PNC_SUPPORT == STD_ON)
    ComM_ChannelActiveStatus[i] = 0U;
#endif
  }

#if (COMM_PNC_SUPPORT == STD_ON)
  for (i = 0U; i < COMM_NUM_PNC_BYTES; ++i)
  {
    ComM_PncActiveStatus[i] = 0U;
  }

#endif

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))

/* !LINKSTO ComM864,1 */
#if (COMM_NVM_ENABLED == STD_OFF)
  /* NvM storage disabled, re-initialize RAM data */
  ComM_EB_NvRAM = ComM_EB_NvROM;
#endif

  /* Initializing the Channel Inhibition status */
  for (i = 0U; i < COMM_NUM_BYTES_NVM; ++i)
  {

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
    ComM_ChannelNoComInhibition[i] = ComM_ChannelInhibitionStatusInit[i];
#endif

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    ComM_ChannelWakeUpInhibition[i] = ComM_EB_NvRAM.ChannelWakeUpInhibition[i];
#endif
  }
#endif
#if (COMM_PNC_SUPPORT == STD_ON)
  /* Initializing the pnc */
  ComM_HsmInit(&ComM_HsmScComMPnc);

  for (i = 0U; i < COMM_PN_INFO_LENGTH; i++)
  {
    ComM_RxEira[i] = 0U;
    ComM_TxEira[i] = 0U;
  }

  ComM_RxEiraSignalStatus = FALSE;
#endif

#if (COMM_INCLUDE_RTE == STD_ON)
  for (i = 0U; i < COMM_NUM_USERS; ++i)
  {
#if (COMM_ENABLE_ASR32_SERVICE_API == STD_ON)
    ComM_ASR32_RteModeUser[i] = COMM_NO_COMMUNICATION;
#endif
#if (COMM_ENABLE_ASR40_SERVICE_API == STD_ON)
    ComM_ASR40_RteModeUser[i] = COMM_NO_COMMUNICATION;
#endif
#if (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE)
    ComM_RteModeUser[i] = COMM_NO_COMMUNICATION;
#endif
  }
#endif /* #if (COMM_INCLUDE_RTE == STD_ON) */

  /* Set initialization status in global variable */
  ComM_InitStatus      = COMM_INIT;

  DBG_COMM_INIT_EXIT();
}

/*------------------[ComM_DeInit]--------------------------------------------*/

FUNC(void, COMM_CODE) ComM_DeInit(void)
{
  uint8_least i;

  DBG_COMM_DEINIT_ENTRY();

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_DEINIT, COMM_E_NOT_INITED);
  }
  else
#endif
  {
    /* Check whether all the channels are in the 'NoCommunication' state */
    for (i = 0U; i < COMM_NUM_CHANNELS; i++)
    {
      /* get locally cached com mode, the BusSm of channels of BusType=Internal
       * cannot be queried */
      if (ComM_ChanState[i] != COMM_NO_COM_NO_PENDING_REQUEST)
      {
        break;
      }
    }

    /* De-init module only if all channels are in no communication state */
    if (COMM_NUM_CHANNELS == i)
    {
      /* deinit module global init status variable */
      ComM_InitStatus = COMM_UNINIT;
    }
  }

  DBG_COMM_DEINIT_EXIT();
}

/*------------------[ComM_GetState]-----------------------------------------*/

FUNC(Std_ReturnType, COMM_CODE) ComM_GetState
(
  NetworkHandleType                                Channel,
  P2VAR(ComM_StateType, AUTOMATIC, COMM_APPL_DATA) State
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_GETSTATE_ENTRY(Channel,State);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_STATE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == State) || (Channel >= COMM_NUM_CHANNELS))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_STATE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    *State = ComM_ChanState[Channel];
    RetVal = E_OK;
  }

  DBG_COMM_GETSTATE_EXIT(RetVal,Channel,State);

  return RetVal;
}

/*------------------[ComM_GetStatus]-----------------------------------------*/

FUNC(Std_ReturnType, COMM_CODE) ComM_GetStatus
(
  P2VAR(ComM_InitStatusType, AUTOMATIC, COMM_APPL_DATA) Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_GETSTATUS_ENTRY(Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == Status)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_STATUS, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    *Status = ComM_InitStatus;
    RetVal = E_OK;
  }

  DBG_COMM_GETSTATUS_EXIT(RetVal,Status);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetInhibitionStatus]-------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetInhibitionStatus
(
  NetworkHandleType                                           Channel,
  P2VAR(ComM_ASR32_InhibitionStatusType, AUTOMATIC, COMM_APPL_DATA) Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETINHIBITIONSTATUS_ENTRY(Channel,Status);

  RetVal = ComM_ASR40_GetInhibitionStatus(Channel, Status);

  DBG_COMM_ASR32_GETINHIBITIONSTATUS_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_GetInhibitionStatus]-------------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetInhibitionStatus
(
  NetworkHandleType                                           Channel,
  P2VAR(ComM_ASR40_InhibitionStatusType, AUTOMATIC, COMM_APPL_DATA) Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  ComM_ASR40_InhibitionStatusType ChannelInhibitionStatus = 0U;

  DBG_COMM_ASR40_GETINHIBITIONSTATUS_ENTRY(Channel,Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_INHIBITION_STATUS, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == Status) || (Channel >= COMM_NUM_CHANNELS))
  {
    COMM_DET_REPORT_ERROR(
      COMM_INSTANCE_ID, COMM_SID_GET_INHIBITION_STATUS, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    /* assemble bit encoded channel inhibition status */
    if (TRUE == ComM_ChannelWakeUpInhibitionStatus(Channel))
    {
      ChannelInhibitionStatus |= COMM_PREVENT_WAKEUP;
    }
#endif
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
    if (TRUE == ComM_ChannelNoComInhibitionStatus(Channel))
    {
      ChannelInhibitionStatus |= COMM_LIMIT_NOCOMM;
    }
#endif

    *Status = ChannelInhibitionStatus;
    RetVal  = E_OK;
  }

  DBG_COMM_ASR40_GETINHIBITIONSTATUS_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_RequestComMode]------------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_RequestComMode
(
  ComM_ASR32_UserHandleType User,
  ComM_ASR32_ModeType       ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_REQUESTCOMMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_RequestComMode(User, ComMode);

  DBG_COMM_ASR32_REQUESTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}
#endif

/*------------------[ComM_RequestComMode]------------------------------------*/

FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_RequestComMode
(
  ComM_ASR40_UserHandleType User,
  ComM_ASR40_ModeType       ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8_least ChannelPos;
#if (COMM_PNC_SUPPORT == STD_ON)
  uint8_least PncPos;
#endif

  DBG_COMM_ASR40_REQUESTCOMMODE_ENTRY(User,ComMode);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_REQUEST_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (User >= COMM_NUM_USERS)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_REQUEST_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else if ((ComMode != COMM_NO_COMMUNICATION) && (ComMode != COMM_FULL_COMMUNICATION))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_REQUEST_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    RetVal = E_OK;
    /* The SchM functions can't be called direct because it's not possible
       to include the Rte files here. Thus the SchM wrapper functions from
       the Rte specific compilation unit must be called. */
    ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
    /* store user requested mode */
    ComM_UserRequestedComMode[User] = ComMode;
    ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();

#if (COMM_PNC_SUPPORT == STD_ON)
    /* Get all pnc for a specific user and set ComMode  */
    for (PncPos = 0U; PncPos < ComM_NumPncOfUser[User]; PncPos++)
    {
       const uint8 Pnc = ComM_PncOfUser[User][PncPos];
       ComM_EvaluatePnc(Pnc, ComMode);
    }
#endif

    /* Get all channels for a specific user and set ComMode  */
    for (ChannelPos = 0U; ChannelPos < ComM_NumChannelsOfUser[User]; ChannelPos++)
    {
      const uint8 Channel = ComM_ChannelsOfUser[User][ChannelPos];
      boolean EmitEventReqStatusChanged = TRUE;
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)  || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
      boolean InhibitionStatus = FALSE;
#endif

      if (COMM_FULL_COMMUNICATION == ComM_UserRequestedComMode[User])
      {
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
        if (COMM_NCI_OR_FALSE(Channel))
        {
          InhibitionStatus = TRUE;
        }
#endif
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
        if (COMM_WUINOCOM_OR_FALSE(Channel))
        {
          InhibitionStatus = TRUE;
        }
#endif
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
        /* Inhibit user request if "Limit to No Comm Mode" is on OR "Wake up
         * inhibition" is on, AND current user state is No Comm */
        if (TRUE == InhibitionStatus)
        {
          /* Return COMM_E_MODE_LIMITATION when inhibition is enabled for
           * any channel of a user */
          RetVal = COMM_E_MODE_LIMITATION;

          if(ComM_EB_NvRAM.InhibitionCounter < 0xFFFFU)
          {
            /* Count the number of FULL Communication requests ignored */
            ComM_EB_NvRAM.InhibitionCounter++ ;
            /* Set NvRAM modified */
            COMM_PERS_DATA_MODIFIED();
          }
          /* Do not emit event 'REQ_STATUS_CHANGED' if inhibition is active */
          EmitEventReqStatusChanged = FALSE;
        }
        else
#endif
        {
          ComM_EvaluateChannel(Channel);
        }
      }
      else
      {
        ComM_EvaluateChannel(Channel);
      }
      /* Emit event 'REQ_STATUS_CHANGED' if request is accepted */
      if (TRUE == EmitEventReqStatusChanged)
      {
        /* Set Event REQ_STATUS_CHANGED */
        COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
      }
    }
  }

  DBG_COMM_ASR40_REQUESTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetMaxComMode]-------------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetMaxComMode
(
  ComM_ASR32_UserHandleType                             User,
  P2VAR(ComM_ASR32_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETMAXCOMMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_GetMaxComMode(User, ComMode);

  DBG_COMM_ASR32_GETMAXCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}
#endif

/*------------------[ComM_GetMaxComMode]-------------------------------------*/

FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetMaxComMode
(
  ComM_ASR40_UserHandleType                             User,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8_least i;
  uint8 Channel;

  DBG_COMM_ASR40_GETMAXCOMMODE_ENTRY(User,ComMode);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_MAX_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == ComMode) || (User >= COMM_NUM_USERS))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_MAX_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Check for limitations, see extended functionality */
    *ComMode = COMM_FULL_COMMUNICATION;

    /* Get all channels for a specific user and check for
     * limitations/inhibitions */
    for (i = 0U; i < ComM_NumChannelsOfUser[User]; i++)
    {
      boolean NoComInhibitionStatus = FALSE;
      boolean WkUpInhibitionStatus = FALSE;

      Channel = (ComM_ChannelsOfUser[User])[i];
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
        if (COMM_NCI_OR_TRUE(Channel))
        {
          NoComInhibitionStatus = TRUE;
        }
#endif
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
        if (COMM_WUI_OR_TRUE(Channel))
        {
          WkUpInhibitionStatus = TRUE;
        }
#endif
      /* If any one channel has inhibition on and currently is in No Com
       * mode, set the lowest possible mode */
      if (((COMM_NO_COM_NO_PENDING_REQUEST == ComM_ChanState[Channel]) ||
           (COMM_NO_COM_REQUEST_PENDING    == ComM_ChanState[Channel])
          ) &&
          /* Deviation MISRA-1 <+3> */
          ((TRUE == NoComInhibitionStatus                                ) ||
           (TRUE == WkUpInhibitionStatus                                 ) ||
           (!(ComM_BitArrayIsBitSet(ComM_Communication_Allowed, Channel)))
          )
         )
      {
        *ComMode = COMM_NO_COMMUNICATION;
        break;
      }
      /* If current state of channel is Silent Com and inhibition is active,
       * the max available mode for user is Silent Communication */
      else if ((COMM_SILENT_COM == ComM_ChanState[Channel]                       ) &&
               /* Deviation MISRA-1 */
               ((TRUE == NoComInhibitionStatus) || (TRUE == WkUpInhibitionStatus))
              )
      {
        *ComMode = COMM_SILENT_COMMUNICATION;
      }
      else
      {
        /* do nothing */
      }
    }

    RetVal = E_OK;
  }

  DBG_COMM_ASR40_GETMAXCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetRequestedComMode]-------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetRequestedMode
(
  ComM_ASR32_UserHandleType                             User,
  P2VAR(ComM_ASR32_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETREQUESTEDMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_GetRequestedComMode(User, ComMode);

  DBG_COMM_ASR32_GETREQUESTEDMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}
#endif

/*------------------[ComM_GetRequestedComMode]-------------------------------*/

FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetRequestedComMode
(
  ComM_ASR40_UserHandleType                             User,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_ASR40_GETREQUESTEDCOMMODE_ENTRY(User,ComMode);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_REQUESTED_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == ComMode) || (User >= COMM_NUM_USERS))
  {
    COMM_DET_REPORT_ERROR(
      COMM_INSTANCE_ID, COMM_SID_GET_REQUESTED_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Call the SchM wrapper functions */
    ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
    *ComMode = ComM_UserRequestedComMode[User];
    ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();

    RetVal = E_OK;
  }

  DBG_COMM_ASR40_GETREQUESTEDCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_GetCurrentComMode]---------------------------*/

/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_GetCurrentComMode
(
  ComM_ASR32_UserHandleType                             User,
  P2VAR(ComM_ASR32_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_GETCURRENTCOMMODE_ENTRY(User,ComMode);

  RetVal = ComM_ASR40_GetCurrentComMode(User, ComMode);

  DBG_COMM_ASR32_GETCURRENTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}
#endif

/*------------------[ComM_GetCurrentComMode]---------------------------------*/

FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_GetCurrentComMode
(
  ComM_ASR40_UserHandleType                             User,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8_least    i;

  DBG_COMM_ASR40_GETCURRENTCOMMODE_ENTRY(User,ComMode);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_CURRENT_COM_MODE, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if ((NULL_PTR == ComMode) || (User >= COMM_NUM_USERS))
  {
    COMM_DET_REPORT_ERROR(
      COMM_INSTANCE_ID, COMM_SID_GET_CURRENT_COM_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    ComM_ASR40_ModeType ResultComMode = COMM_FULL_COMMUNICATION;
    /* Get all channels for a specific user and set ComMode  */
    for (i = 0U; i < ComM_NumChannelsOfUser[User]; i++)
    {
      /* get locally cached com mode, the BusSm of channels of BusType=Internal
       * cannot be queried */
      const ComM_ASR40_ModeType localComMode = ComM_ChannelMode[ComM_ChannelsOfUser[User][i]];

      /* get the lowest communication mode possible */
      if (localComMode < ResultComMode)
      {
        ResultComMode = localComMode;
      }
    }

    *ComMode = ResultComMode;
    RetVal   = E_OK;
  }

  DBG_COMM_ASR40_GETCURRENTCOMMODE_EXIT(RetVal,User,ComMode);

  return RetVal;
}

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_PreventWakeUp]---------------------------*/

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_PreventWakeUp
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_PREVENTWAKEUP_ENTRY(Channel,Status);

  RetVal = ComM_ASR40_PreventWakeUp(Channel, Status);

  DBG_COMM_ASR32_PREVENTWAKEUP_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_PreventWakeUp]-------------------------------------*/

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_PreventWakeUp
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_ASR40_PREVENTWAKEUP_ENTRY(Channel,Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_PREVENT_WAKE_UP, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_PREVENT_WAKE_UP, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* If ECU group classification has bit 0 set, allow Prevent wake up */
    if (COMM_PREVENT_WAKEUP == (ComM_EB_NvRAM.ECUGroupClassification & COMM_PREVENT_WAKEUP))
    {
      if (TRUE == Status)
      {
        if (TRUE != ComM_ChannelWakeUpInhibitionStatus(Channel))
        {
          /* Set inhibition status of channel as Wake Up Inhibition */
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_PREVENT_WAKEUP, TRUE);
        }
      }
      else
      {
        /* Reset Bit 0 Request of Wake Up Inhibition */
        ComM_SetChannelComMInhibitionStatus(Channel, COMM_PREVENT_WAKEUP, FALSE);

        /* Re-evaluate mode requests if inhibition get deactivated */
        ComM_EvaluateChannel(Channel);
      }
      /* Set return value to E_OK only if ECU group classification allowed
       * access */
      RetVal = E_OK;
    }
  }

  DBG_COMM_ASR40_PREVENTWAKEUP_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_LimitChannelToNoComMode]---------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_LimitChannelToNoComMode
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_ENTRY(Channel,Status);

  RetVal = ComM_ASR40_LimitChannelToNoComMode(Channel, Status);

  DBG_COMM_ASR32_LIMITCHANNELTONOCOMMODE_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_LimitChannelToNoComMode]---------------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_LimitChannelToNoComMode
(
  NetworkHandleType Channel,
  boolean           Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_ENTRY(Channel,Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_LIMIT_CHANNEL_TO_NO_COM, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(
      COMM_INSTANCE_ID, COMM_SID_LIMIT_CHANNEL_TO_NO_COM, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* If ECU group classification has bit 1 set, allow Limit to No Comm */
    if (COMM_LIMIT_NOCOMM == (ComM_EB_NvRAM.ECUGroupClassification & COMM_LIMIT_NOCOMM))
    {
      if (TRUE == Status)
      {
        /* Set Event for limit to no com */
        COMM_EMIT(Channel, COMM_HSM_COMM_EV_LIMIT_TO_NO_COM);
      }
      else
      {
        /* Reset Bit 1 Request of Limit to No Com */
        ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, FALSE);

        /* Re-evaluate mode requests if inhibition get deactivated */
        ComM_EvaluateChannel(Channel);
      }
      /* Set return value to E_OK only if ECU group classification allowed
       * access */
      RetVal = E_OK;
    }
  }

  DBG_COMM_ASR40_LIMITCHANNELTONOCOMMODE_EXIT(RetVal,Channel,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_LimitECUToNoComMode]-------------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_LimitECUToNoComMode
(
  boolean Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_LIMITECUTONOCOMMODE_ENTRY(Status);

  RetVal = ComM_ASR40_LimitECUToNoComMode(Status);

  DBG_COMM_ASR32_LIMITECUTONOCOMMODE_EXIT(RetVal,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_LimitECUToNoComMode]-------------------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_LimitECUToNoComMode
(
  boolean Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  uint8 Channel;

  DBG_COMM_ASR40_LIMITECUTONOCOMMODE_ENTRY(Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_LIMIT_ECU_TO_NO_COM, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
#endif
  {
    /* If ECU group classification has bit 1 set, allow Limit to No Comm */
    if (COMM_LIMIT_NOCOMM == (ComM_EB_NvRAM.ECUGroupClassification & COMM_LIMIT_NOCOMM))
    {
      for (Channel = 0U; Channel < COMM_NUM_CHANNELS; Channel++)
      {
        if (TRUE == Status)
        {
          /* Set Event for limit to no com */
          COMM_EMIT(Channel, COMM_HSM_COMM_EV_LIMIT_TO_NO_COM);
        }
        else
        {
          /* Reset Bit 1 Request of Limit to No Com */
          ComM_SetChannelComMInhibitionStatus(Channel, COMM_LIMIT_NOCOMM, FALSE);

          /* Re-evaluate mode requests if inhibition get deactivated */
          ComM_EvaluateChannel(Channel);
        }
      }
      /* Set return value to E_OK only if ECU group classification allowed
       * access */
      RetVal = E_OK;
    }
  }

  DBG_COMM_ASR40_LIMITECUTONOCOMMODE_EXIT(RetVal,Status);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_ReadInhibitCounter]--------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_ReadInhibitCounter
(
  P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_READINHIBITCOUNTER_ENTRY(CounterValue);

  RetVal = ComM_ASR40_ReadInhibitCounter(CounterValue);

  DBG_COMM_ASR32_READINHIBITCOUNTER_EXIT(RetVal,CounterValue);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_ReadInhibitCounter]--------------------------------*/
#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_ReadInhibitCounter
(
  P2VAR(uint16, AUTOMATIC, COMM_APPL_DATA) CounterValue
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_ASR40_READINHIBITCOUNTER_ENTRY(CounterValue);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_READ_INHIBIT_COUNTER, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else if (NULL_PTR == CounterValue)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_READ_INHIBIT_COUNTER, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    *CounterValue = ComM_EB_NvRAM.InhibitionCounter;
    RetVal = E_OK;
  }

  DBG_COMM_ASR40_READINHIBITCOUNTER_EXIT(RetVal,CounterValue);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_ResetInhibitCounter]-------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_ResetInhibitCounter
(
  void
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_RESETINHIBITCOUNTER_ENTRY();

  RetVal = ComM_ASR40_ResetInhibitCounter();

  DBG_COMM_ASR32_RESETINHIBITCOUNTER_EXIT(RetVal);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_ResetInhibitCounter]-------------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_ResetInhibitCounter
(
  void
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_ASR40_RESETINHIBITCOUNTER_ENTRY();

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_RESET_INHIBIT_COUNTER, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
#endif
  {
    ComM_EB_NvRAM.InhibitionCounter = 0U;
    /* Set NvRAM modified */
    COMM_PERS_DATA_MODIFIED();
    RetVal = E_OK;
  }

  DBG_COMM_ASR40_RESETINHIBITCOUNTER_EXIT(RetVal);

  return RetVal;
}
#endif

#if ((COMM_ENABLE_ASR32_SERVICE_API == STD_ON) || (COMM_DEFAULT_ASR_SERVICE_API == COMM_SERVICE_API_ASR32))
/*------------------[ComM_ASR32_SetECUGroupClassification]-------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
/* !LINKSTO ComM.EB.ASR32.ComM107,1 */
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR32_SetECUGroupClassification
(
  ComM_ASR32_InhibitionStatusType Status
)
{
  Std_ReturnType RetVal;

  DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_ENTRY(Status);

  RetVal = ComM_ASR40_SetECUGroupClassification(Status);

  DBG_COMM_ASR32_SETECUGROUPCLASSIFICATION_EXIT(RetVal,Status);

  return RetVal;
}
#endif
#endif

/*------------------[ComM_SetECUGroupClassification]-------------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON)           \
     || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(Std_ReturnType, COMM_CODE) ComM_ASR40_SetECUGroupClassification
(
  ComM_ASR40_InhibitionStatusType Status
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_ENTRY(Status);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_SET_ECU_GROUP_CLASS, COMM_E_NOT_INITED);
    RetVal = COMM_E_UNINIT;
  }
  else
#endif
  {
    /* Change variable (in NvRAM mirror) */
    ComM_EB_NvRAM.ECUGroupClassification = Status;

    /* Set NvRAM modified */
    COMM_PERS_DATA_MODIFIED();
    RetVal = E_OK;
  }

  DBG_COMM_ASR40_SETECUGROUPCLASSIFICATION_EXIT(RetVal,Status);

  return RetVal;
}
#endif

/*------------------[ComM_GetVersionInfo]------------------------------------*/

#if (COMM_VERSION_INFO_API == STD_ON)
FUNC(void, COMM_CODE) ComM_GetVersionInfo(
  CONSTP2VAR(Std_VersionInfoType, AUTOMATIC, COMM_APPL_DATA) VersionInfoPtr)
{
  DBG_COMM_GETVERSIONINFO_ENTRY(VersionInfoPtr);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (NULL_PTR == VersionInfoPtr)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_GET_VERSION_INFO, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    VersionInfoPtr->vendorID         = COMM_VENDOR_ID;
    VersionInfoPtr->moduleID         = COMM_MODULE_ID;
    VersionInfoPtr->sw_major_version = COMM_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = COMM_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = COMM_SW_PATCH_VERSION;
  }

  DBG_COMM_GETVERSIONINFO_EXIT(VersionInfoPtr);
}
#endif

/*------------------[ComM_ChannelNoComInhibitionStatus]----------------------*/

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
FUNC(boolean, COMM_CODE) ComM_ChannelNoComInhibitionStatus(
  const uint8 instIdx)
{
  boolean RetVal;

  DBG_COMM_CHANNELNOCOMINHIBITIONSTATUS_ENTRY(instIdx);

  RetVal = ComM_BitArrayIsBitSet(ComM_ChannelNoComInhibition, instIdx);

  DBG_COMM_CHANNELNOCOMINHIBITIONSTATUS_EXIT(RetVal,instIdx);

  return RetVal;
}
#endif

/*------------------[ComM_ChannelWakeUpInhibitionStatus]---------------------*/

#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
FUNC(boolean, COMM_CODE) ComM_ChannelWakeUpInhibitionStatus(
  const uint8 instIdx)
{
  boolean RetVal;

  DBG_COMM_CHANNELWAKEUPINHIBITIONSTATUS_ENTRY(instIdx);

  RetVal = ComM_BitArrayIsBitSet(ComM_ChannelWakeUpInhibition, instIdx);

  DBG_COMM_CHANNELWAKEUPINHIBITIONSTATUS_EXIT(RetVal,instIdx);

  return RetVal;
}
#endif

/*------------------[ComM_Nm_NetworkStartIndication]-------------------------*/

#if (COMM_NM_ACCESS_NEEDED == STD_ON)
FUNC(void, COMM_CODE) ComM_Nm_NetworkStartIndication
(
  NetworkHandleType Channel
)
{
  DBG_COMM_NM_NETWORKSTARTINDICATION_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_NETWORK_START_IND, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_NETWORK_START_IND, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Set Event for network start indication */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_NETWORK_START_INDICATION);
  }

  DBG_COMM_NM_NETWORKSTARTINDICATION_EXIT(Channel);
}

/*------------------[ComM_Nm_NetworkMode]------------------------------------*/

FUNC(void, COMM_CODE) ComM_Nm_NetworkMode
(
  NetworkHandleType Channel
)
{
  DBG_COMM_NM_NETWORKMODE_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_NETWORK_MODE, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_NETWORK_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Set Event for network mode indication */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_NETWORK_MODE);
  }

  DBG_COMM_NM_NETWORKMODE_EXIT(Channel);
}

/*------------------[ComM_Nm_PrepareBusSleepMode]----------------------------*/

FUNC(void, COMM_CODE) ComM_Nm_PrepareBusSleepMode
(
  NetworkHandleType Channel
)
{
  DBG_COMM_NM_PREPAREBUSSLEEPMODE_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_PREPARE_BUS_SLEEP, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_PREPARE_BUS_SLEEP, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Set Event for prepare bus sleep mode indication */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_PREP_BUS_SLEEP_MODE);
  }

  DBG_COMM_NM_PREPAREBUSSLEEPMODE_EXIT(Channel);
}

/*------------------[ComM_Nm_BusSleepMode]-----------------------------------*/

FUNC(void, COMM_CODE) ComM_Nm_BusSleepMode
(
  NetworkHandleType Channel
)
{
  DBG_COMM_NM_BUSSLEEPMODE_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_BUS_SLEEP_MODE, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_BUS_SLEEP_MODE, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Set Event for bus sleep mode indication */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_BUS_SLEEP_MODE);
  }

  DBG_COMM_NM_BUSSLEEPMODE_EXIT(Channel);
}

/*------------------[ComM_Nm_RestartIndication]------------------------------*/

FUNC(void, COMM_CODE) ComM_Nm_RestartIndication
(
  NetworkHandleType Channel
)
{
  DBG_COMM_NM_RESTARTINDICATION_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_RESTART_IND, COMM_E_NOT_INITED);
  }
  else if (COMM_IS_CHANNEL_INVALID(Channel))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_NM_RESTART_IND, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* Set Event for Nm restart indication */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_NM_RESTART_IND);
  }

  DBG_COMM_NM_RESTARTINDICATION_EXIT(Channel);
}

#endif /* (COMM_NM_ACCESS_NEEDED == STD_ON) */

#if (COMM_DCM_ENABLED == STD_ON)
/*------------------[ComM_DCM_ActiveDiagnostic]------------------------------*/

FUNC(void, COMM_CODE) ComM_DCM_ActiveDiagnostic
(
  NetworkHandleType Channel
)
{
  DBG_COMM_DCM_ACTIVEDIAGNOSTIC_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_DCM_ACTIVE_DIAGNOSTIC, COMM_E_NOT_INITED);
  }
  else
#endif
  {
    /* Diagnostic session on a Passive channel is not possible.
     * See RFC #56661 */
    /* Deviation MISRA-2 */
    if (COMM_NM_VARIANT_OF_CHANNEL(Channel) != COMM_NM_PASSIVE_VARIANT)
    {
      /* Set the bit (active diagnostic request) for the corresponding
       * channel in the bit array */
      ComM_BitArraySet(ComM_DcmActiveStatus, Channel);

      /* notify state machine about changed diagnostics communication state */
      COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
    else
    {
      /* Call has no effect */
    }
  }

  DBG_COMM_DCM_ACTIVEDIAGNOSTIC_EXIT(Channel);
}

/*------------------[ComM_DCM_InactiveDiagnostic]----------------------------*/

FUNC(void, COMM_CODE) ComM_DCM_InactiveDiagnostic
(
  NetworkHandleType Channel
)
{
  DBG_COMM_DCM_INACTIVEDIAGNOSTIC_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_DCM_INACTIVE_DIAGNOSTIC, COMM_E_NOT_INITED);
  }
  else
#endif
  {
    /* Diagnostic session on a Passive channel is not possible.
     * See RFC #56661 */
     /* Deviation MISRA-2 */
    if (COMM_NM_VARIANT_OF_CHANNEL(Channel) != COMM_NM_PASSIVE_VARIANT)
    {
      /* Clear the bit (active diagnostic request) for the corresponding
       * channel in the bit array */
      ComM_BitArrayClear(ComM_DcmActiveStatus, Channel);

      /* notify state machine about changed diagnostics communication state */
      COMM_EMIT(Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
    else
    {
      /* Call has no effect */
    }
  }

  DBG_COMM_DCM_INACTIVEDIAGNOSTIC_EXIT(Channel);
}
#endif  /* (COMM_DCM_ENABLED == STD_ON) */

/*------------------[ComM_EcuM_WakeUpIndication]-----------------------------*/

FUNC(void, COMM_CODE) ComM_EcuM_WakeUpIndication
(
  NetworkHandleType Channel
)
{
  DBG_COMM_ECUM_WAKEUPINDICATION_ENTRY(Channel);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_ECUM_WAKE_UP_INDICATION, COMM_E_NOT_INITED);
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(
      COMM_INSTANCE_ID, COMM_SID_ECUM_WAKE_UP_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    /* If COMM_SYNCHRONOUS_WAKE_UP is enabled, indicate all channels
     * a passive wakeup */
#if (COMM_SYNCHRONOUS_WAKE_UP == STD_ON)
    /* Set Event for EcuM wakeup indication */
    (void)ComM_HsmEmit(&ComM_HsmScComM, COMM_HSM_COMM_EV_ECUM_WAKEUP_IND);
    TS_PARAM_UNUSED(Channel);
#if (COMM_PNC_SUPPORT == STD_ON)
    (void)ComM_HsmEmit(&ComM_HsmScComMPnc, COMM_HSM_COMMPNC_EV_ECUM_WAKEUP_IND);
#endif
#else
    /* Set Event for EcuM wakeup indication */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_ECUM_WAKEUP_IND);
#endif
  }

  DBG_COMM_ECUM_WAKEUPINDICATION_EXIT(Channel);
}

/*------------------[ComM_CommunicationAllowed]-----------------------------*/

FUNC(void, COMM_CODE) ComM_CommunicationAllowed
(
  NetworkHandleType Channel,
  boolean           Allowed
)
{
  DBG_COMM_COMMUNICATIONALLOWED_ENTRY(Channel,Allowed);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_COMMUNICATIONALLOWED, COMM_E_NOT_INITED);
  }
  else if (Channel >= COMM_NUM_CHANNELS)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_COMMUNICATIONALLOWED, COMM_E_WRONG_PARAMETERS);
  }
  else
#endif
  {
    if(TRUE == Allowed)
    {
      /* Set the bit for the corresponding channel */
      ComM_BitArraySet(ComM_Communication_Allowed, Channel);
    }
    else
    {
      /* Clear the bit for the corresponding channel */
      ComM_BitArrayClear(ComM_Communication_Allowed, Channel);
    }
    /* Set Event for communication allowed */
    COMM_EMIT(Channel, COMM_HSM_COMM_EV_COMALLOWED_CHANGED);
  }

  DBG_COMM_COMMUNICATIONALLOWED_EXIT(Channel,Allowed);
}

/*------------------[ComM_BusSM_ModeIndication]------------------------------*/
/* Deviation MISRA-3 <+4> */
FUNC(void, COMM_CODE) ComM_BusSM_ModeIndication
(
  NetworkHandleType                               Channel,
  P2VAR(ComM_ASR40_ModeType, AUTOMATIC, COMM_APPL_DATA) ComMode
)
{
  ComM_HsmEventType Event;

  DBG_COMM_BUSSM_MODEINDICATION_ENTRY(Channel,ComMode);

#if (COMM_DEV_ERROR_DETECT == STD_ON)
  if (COMM_INIT != ComM_InitStatus)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_BUS_SM_INDICATION, COMM_E_NOT_INITED);
  }
  else if ((NULL_PTR == ComMode) || (Channel >= COMM_NUM_CHANNELS))
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_BUS_SM_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
#if (COMM_BUSTYPE_INTERNAL_NEEDED == STD_ON)
  else if (COMM_BUSTYPE_OF_CHANNEL(Channel) == COMM_BUS_TYPE_INTERNAL)
  {
    COMM_DET_REPORT_ERROR(COMM_INSTANCE_ID, COMM_SID_BUS_SM_INDICATION, COMM_E_WRONG_PARAMETERS);
  }
#endif
  else
#endif
  {
    switch (*ComMode)
    {
      /* if no communication mode */
      case COMM_NO_COMMUNICATION:
        /* Set event for no communication */
        Event = COMM_HSM_COMM_EV_BUSSM_MODE_IND_NO_COM;
        break;

      /* if silent communication mode */
      case COMM_SILENT_COMMUNICATION:
        /* Set event for no communication */
        Event = COMM_HSM_COMM_EV_BUSSM_MODE_IND_SILENT_COM;
        break;

      /* if full communication mode */
      case COMM_FULL_COMMUNICATION:
        /* Set event for no communication */
        Event = COMM_HSM_COMM_EV_BUSSM_MODE_IND_FULL_COM;
        break;

      default:
        /* Set invalid event */
        Event = COMM_EVENT_INVALID;
        break;
    }

    if (COMM_EVENT_INVALID != Event)
    {
      /* Set Bus Mode indication for corresponding channel */
      COMM_EMIT(Channel, Event);
    }
  }

  DBG_COMM_BUSSM_MODEINDICATION_EXIT(Channel,ComMode);
}

/*==================[internal function definitions]=========================*/

/*------------------[ComM_EB_GetNumUsersOfChannel]----------------------------------*/
FUNC(uint8, COMM_CODE) ComM_EB_GetNumUsersOfChannel
(
  const uint8 Channel
)
{
  uint8 ret;
#if (COMM_NUM_CHANNELS <= 1)
  /* avoid 'unused parameter' compiler warning*/
  TS_PARAM_UNUSED(Channel);
#endif
  DBG_COMM_EB_GETNUMUSERSOFCHANNEL_ENTRY(Channel);

  ret = COMM_NUM_USERS_OF_CHANNEL(Channel);

  DBG_COMM_EB_GETNUMUSERSOFCHANNEL_EXIT(ret, Channel);
  return ret;
}

/*------------------[ComM_EB_GetUsersOfChannel]----------------------------------*/
FUNC(uint8, COMM_CODE) ComM_EB_GetUsersOfChannel
(
  const uint8 Channel,
  const uint8 User
)
{
  uint8 ret;
  DBG_COMM_EB_GETUSERSOFCHANNEL_ENTRY(Channel,User);

  ret = ComM_UsersOfChannel[Channel][User];

  DBG_COMM_EB_GETUSERSOFCHANNEL_EXIT(ret,Channel,User);
  return ret;
}

/*------------------[ComM_EB_GetUserRequestedComMode]----------------------------------*/
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetUserRequestedComMode
(
  const uint8 User
)
{
  ComM_ASR40_ModeType ret;
  DBG_COMM_EB_GETUSERREQUESTEDCOMMODE_ENTRY(User);

  ret = ComM_UserRequestedComMode[User];
  DBG_COMM_EB_GETUSERREQUESTEDCOMMODE_EXIT(ret,User);
  return ret;
}

/*------------------[ComM_EB_SetRequestedComMode]----------------------------------*/
FUNC(void, COMM_CODE) ComM_EB_SetRequestedComMode
(
  const uint8 Channel,
  ComM_ASR40_ModeType ComMode
)
{
  DBG_COMM_EB_SETREQUESTEDCOMMODE_ENTRY(Channel,ComMode);

  ComM_RequestedComMode[Channel] = ComMode;

  DBG_COMM_EB_SETREQUESTEDCOMMODE_EXIT(Channel,ComMode);
}

/*------------------[ComM_EvaluatePnc]----------------------------------*/

#if (COMM_PNC_SUPPORT == STD_ON)
STATIC FUNC(void, COMM_CODE) ComM_EvaluatePnc
(
  const uint8 Pnc,
  ComM_ASR40_ModeType ComMode
)
{
  const uint8_least NumUser = COMM_NUM_USERS_OF_PNC(Pnc);
  uint8_least       UserPos;

  DBG_COMM_EVALUATEPNC_ENTRY(Pnc,ComMode);

  ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();

  /* Search highest mode requested by users of a PNC */
  for (UserPos = 0U; UserPos < NumUser; UserPos++)
  {
    const uint8 UserOfPnc = ComM_UsersOfPnc[Pnc][UserPos];

    if (ComMode < ComM_UserRequestedComMode[UserOfPnc])
    {
      ComMode = ComM_UserRequestedComMode[UserOfPnc];
    }
  }

  ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();

  /* if users request full communication mode or diagnostics request full
  * com */
  if (COMM_FULL_COMMUNICATION == ComMode)
  {
    /* Set Event for full communication mode */
    COMM_PNC_EMIT(Pnc, COMM_HSM_COMMPNC_EV_FULL_COM_REQ_BY_COMM_USER);
  }
  else /* no user needs full com */
  {
    /* Set Event for ready sleep mode */
    COMM_PNC_EMIT(Pnc, COMM_HSM_COMMPNC_EV_NO_COM_REQ_BY_ALL_COMM_USER);
  }

  DBG_COMM_EVALUATEPNC_EXIT(Pnc,ComMode);
}
#endif

/*------------------[ComM_SetChannelComMInhibitionStatus]--------------------*/

#if ((COMM_MODE_LIMITATION_ENABLED == STD_ON) || (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON))
FUNC(void, COMM_CODE) ComM_SetChannelComMInhibitionStatus
(
  const uint8                           instIdx,
  const ComM_ASR40_InhibitionStatusType Inhibitiontype,
  const boolean                         Status
)
{
  DBG_COMM_SETCHANNELCOMMINHIBITIONSTATUS_ENTRY(instIdx,Inhibitiontype,Status);
/* !LINKSTO ComM690,1 */
#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
  if (COMM_LIMIT_NOCOMM == Inhibitiontype)
  {
    if (TRUE == Status)
    {
      /* Set inhibition status of channel as Limit to No Com */
      ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
      ComM_BitArraySet(ComM_ChannelNoComInhibition, instIdx);
      ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();
    }
    else
    {
      /* Reset Bit Request of Limit to No Com */
      ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
      ComM_BitArrayClear(ComM_ChannelNoComInhibition, instIdx);
      ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();

      /* [ComM839,ComM840]
       * emit event 'REQ_STATUS_CHANGED'. This triggers the required
       * transitions if there are user requests when inhibition was active */
      COMM_EMIT(instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
  }
  else
#else
  TS_PARAM_UNUSED(Inhibitiontype);
#endif
  {
#if (COMM_WAKEUP_INHIBITION_ENABLED == STD_ON)
    /* Find out if storing in NvRAM is allowed */
    const boolean changeNvRamAllowed = ComM_BitArrayIsBitSet(ComM_EB_NoWakeupNvStorage, instIdx);

    /* Modify Wakeup inhibition */
    if (TRUE == Status)
    {
      /* Enable inhibition */

      /* Set runtime variable */
      ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
      ComM_BitArraySet(ComM_ChannelWakeUpInhibition, instIdx);
      ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();

      /* Check setting NvRAM */
      if (TRUE == changeNvRamAllowed)
      {
        /* Set value in NvRAM */
        ComM_BitArraySet(ComM_EB_NvRAM.ChannelWakeUpInhibition, instIdx);
        /* Set NvRAM modified */
        COMM_PERS_DATA_MODIFIED();
      }
    }
    else
    {
      /* Take back inhibition */

      /* Clear runtime value */
      ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
      ComM_BitArrayClear(ComM_ChannelWakeUpInhibition, instIdx);
      ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();

      /* Check setting NvRAM */
      if (TRUE == changeNvRamAllowed)
      {
        /* Clear value in NvRAM */
        ComM_BitArrayClear(ComM_EB_NvRAM.ChannelWakeUpInhibition, instIdx);
        /* Set NvRAM modified */
        COMM_PERS_DATA_MODIFIED();
      }

      /* [ComM839,ComM840]
       * emit event 'REQ_STATUS_CHANGED'. This triggers the required
       * transitions if there are user requests when inhibition was active */
      COMM_EMIT(instIdx, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
    }
#endif
  }

  DBG_COMM_SETCHANNELCOMMINHIBITIONSTATUS_EXIT(instIdx,Inhibitiontype,Status);
}
#endif

FUNC(void, COMM_CODE) ComM_BitArraySet
(
  CONSTP2VAR(uint8, AUTOMATIC, COMM_VAR) arr,
  const uint16                           idx
)
{
  DBG_COMM_BITARRAYSET_ENTRY(arr,idx);

  arr[idx / 8U] |= (uint8)(1U << (idx % 8U));

  DBG_COMM_BITARRAYSET_EXIT(arr,idx);
}

FUNC(void, COMM_CODE) ComM_BitArrayClear
(
  CONSTP2VAR(uint8, AUTOMATIC, COMM_VAR) arr,
  const uint16                           idx
)
{
  DBG_COMM_BITARRAYCLEAR_ENTRY(arr,idx);

  arr[idx / 8U] &= (uint8)(~(uint8)(1U << (idx % 8U)));

  DBG_COMM_BITARRAYCLEAR_EXIT(arr,idx);
}

FUNC(boolean, COMM_CODE) ComM_BitArrayIsBitSet
(
  CONSTP2CONST(uint8, AUTOMATIC, COMM_VAR) arr,
  const uint16                             idx
)
{
  boolean RetVal;

  DBG_COMM_BITARRAYISBITSET_ENTRY(arr,idx);

  RetVal = ((((uint8)(arr[idx / 8U] >> (idx % 8U))) & 1U) != 0U) ? TRUE : FALSE;

  DBG_COMM_BITARRAYISBITSET_EXIT(RetVal,arr,idx);

  return RetVal;
}

#if (COMM_PNC_SUPPORT == STD_ON)
FUNC(void, COMM_CODE) ComM_PncMainFunction
(
void
)
{
  /* No *_least type for a loop variable as the variable is also used as
     an argument whose underlying type is uint8  */
  uint8 PncIdx;
  uint16 Index;
  uint8 RecvSn = E_NOT_OK;
  uint8 i;
  uint8 RxEiraMerged[COMM_PN_INFO_LENGTH] = {0U};
  /* Flag to indicate if at least one signal is received successfully */
  boolean EiraStatus = FALSE;

  DBG_COMM_PNCMAINFUNCTION_ENTRY();
  if(ComM_RxEiraSignalStatus == TRUE)
  {
    ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
    /* EIRA change has been notified by Com, reset flag */
    ComM_RxEiraSignalStatus = FALSE;
    ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();

    for (Index = 0U; Index < COMM_NUM_RX_EIRA_SIGNALS; Index++)
    {
      uint8 RxEiraReceived[COMM_PN_INFO_LENGTH];
      /* Read EIRA signal into a temporary buffer */
      RecvSn = Com_ReceiveSignal(ComM_RxComSignalCfg[Index], RxEiraReceived);

      if (E_OK == RecvSn)
      {
        /* Update the flag if at least one signal is received */
        EiraStatus = TRUE;
        /* Data from multiple signals may be available at the same time;
         * So, merge the contents of the newly received signal into
         * another buffer.
         */
        for (i = 0U; i < COMM_PN_INFO_LENGTH; i++)
        {
          /* Some PNCs may not reference this RX EIRA Com signal.
           * Therefore, the bits corresponding to PNCs which do not
           * reference this Com signal have to be masked out before
           * copying into the global EIRA bit vector.
           */
          RxEiraMerged[i] |= (uint8)(RxEiraReceived[i] & ComM_PncRxEiraMask[Index][i]);
        }
      }
    }
  }

  for (PncIdx = 0U; PncIdx < COMM_NUM_PNC; PncIdx++)
  {
    uint8 EiraMask;

    /* Each bit of EIRA stands for one PNC.
     * For example bit 0 of Byte 0 stands for PNC_0 and bit 0 of Byte 1
     * stands for PNC_8
     */

    /* If at least one signal is received */
    if (TRUE == EiraStatus)
    {
      /* Calculate the byte index from PncID */
      Index = (uint8)(ComM_PncID[PncIdx] >> 3U);
      /* Calculate the byte mask based on bit position of this Pnc */
      EiraMask = (uint8)(1U << (ComM_PncID[PncIdx] & 7U));
      if((ComM_RxEira[Index] & EiraMask) != (RxEiraMerged[Index] & EiraMask))
      {
        /* There is a change in EIRA, append the EIRA event to the queue */
        COMM_PNC_EMIT(PncIdx, COMM_HSM_COMMPNC_EV_COMCBK);
      }
    }
  }

  /* If at least one signal is received */
  if (TRUE == EiraStatus)
  {

    ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0();
    /* Copy new EIRA to old EIRA for next evaluation */
    for (Index = 0U; Index < COMM_PN_INFO_LENGTH; Index++)
    {
      ComM_RxEira[Index] = RxEiraMerged[Index];
    }
    ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0();
  }

  for (PncIdx = 0U; PncIdx < COMM_NUM_PNC; PncIdx++)
  {
    /* Schedule the pnc state machine */
    (void) COMM_HSMMAININST(&ComM_HsmScComMPnc, PncIdx);
  }


  DBG_COMM_PNCMAINFUNCTION_EXIT();
}
#endif

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]===========================================*/
