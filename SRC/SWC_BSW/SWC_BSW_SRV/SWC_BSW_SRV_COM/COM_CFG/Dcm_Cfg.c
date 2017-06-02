/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

 /* MISRA-C:2004 Deviation List
  *
  * MISRA-1) Deviated Rule: 12.4 (required)
  *     The right-hand operand of a logical '&&' or '||' operator
  *     shall not contain side effects.
  *
  *     Reason:
  *     Logical operators '&&' and '||' are used here purposefully. The sub-expression shall not be
  *      evaluated if the first expression of a '&&' operation is FALSE. Similarly the
  *      sub-expression shall not be evaluated if the first expression of a '||' operation is TRUE.
  *      There is no side effects.
  *
  * MISRA-2) Deviated Rule: 11.4 (advisory)
  *     A cst shouldnot be performed between a pointer to object type and a
  *     different pointer to object type.
  *
  *     Reason:
  *     A cast to unsigned is necessary here to copy data bit by bit and
  *     there is no alignment issues.
  */

/*==================[inclusions]=================================================================*/
#include <ComStack_Types.h>                                            /* AUTOSAR standard types */
#include <Dcm_Cfg.h>                                           /* Generated configuration header */
#include <Dcm_API_Cfg.h>                                  /*  Configurable function declarations */
#include <Dcm_Hsm.h>                                                        /* Dcm State Machine */
#include <Dcm_Int.h>                                       /* Module internal header static part */
#include <Dcm_DspExternal.h>                          /* Callbacks provided by Central Diag SwC  */









/*==================[macros]=====================================================================*/
/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/

/*==================[internal function declarations]=============================================*/
#define DCM_START_SEC_CODE
#include <MemMap.h>



#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal constants]=========================================================*/

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/* Array of session types for all Subservices */
STATIC CONST(Dcm_SesCtrlType,DCM_CONST) Dcm_SubSidTabSesLevels[2] =
{
  0x01U, /* DCM_DEFAULT_SESSION of CommunicationControl referred by its subservice enableRxAndTx */
  0x01U, /* DCM_DEFAULT_SESSION of CommunicationControl referred by its subservice disableRxAndTx */
};


/* Array of session types for all services */
STATIC CONST(Dcm_SesCtrlType,DCM_CONST) Dcm_SidTabSesLevels[6] =
{
  0xffU, /* DCM_ALL_SESSION_LEVEL referred to by EcuReset */
  0xffU, /* DCM_ALL_SESSION_LEVEL referred to by ClearDiagnosticInformation */
  0xffU, /* DCM_ALL_SESSION_LEVEL referred to by ReadDTCInformation */
  0xffU, /* DCM_ALL_SESSION_LEVEL referred to by CommunicationControl */
  0xffU, /* DCM_ALL_SESSION_LEVEL referred to by TesterPresent */
  0xffU, /* DCM_ALL_SESSION_LEVEL referred to by ControlDTCSetting */
};



/* Array of Subservices for Service 'DiagnosticSessionControl' */
STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig0_SubSidTabEntryConfig16[3] =
{

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x01U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x02U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x03U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },
};
/* Array of Subservices for Service 'EcuReset' */
STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig0_SubSidTabEntryConfig17[5] =
{

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_HardReset_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x01U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_KeyOffOnReset_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x02U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_SoftReset_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x03U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_EnableRapidPowerShutDown_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x04U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_DisableRapidPowerShutDown_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x05U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },
};
/* Array of Subservices for Service 'ReadDTCInformation' */
STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig0_SubSidTabEntryConfig25[6] =
{

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_reportNumberOfDTCByStatusMask_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x01U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_ReportDTCByStatusMask_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x02U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_ReportDtcSnapshotRecordIdentification_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x03U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_ReportDtcSnapshotRecordByDtcNumber_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x04U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_ReportDtcExtendedDataRecordByDtcNumber_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x06U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_ReportSupportedDtcs_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x0aU, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },
};
/* Array of Subservices for Service 'CommunicationControl' */
STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig0_SubSidTabEntryConfig40[4] =
{

  {
    &( Dcm_SubSidTabSesLevels[0]), /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    &UDS_bEnableRxAndTx,  /* Pointer to Subservice function */
    NULL_PTR,
    NULL_PTR,
    0x00U, /* SubServiceId */
    1U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_EnableRxAndDisableTx_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x01U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_DisableRxAndEnableTx_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x02U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    &( Dcm_SubSidTabSesLevels[1]), /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    &UDS_bDisableRxAndTx,  /* Pointer to Subservice function */
    NULL_PTR,
    NULL_PTR,
    0x03U, /* SubServiceId */
    1U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },
};
/* Array of Subservices for Service 'ControlDTCSetting' */
STATIC CONST(Dcm_SubSidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig0_SubSidTabEntryConfig133[2] =
{

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_DTCSettingTypeOn_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x01U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },

  {
    NULL_PTR,  /* Pointer to subservice sessions */
    NULL_PTR,/* Pointer to subservice security levels */
    NULL_PTR,
    &Dcm_DspInternal_DTCSettingTypeOff_SSvcH,  /* Pointer to Subservice function */
    NULL_PTR,
    0x02U, /* SubServiceId */
    0U, /* Number of sub service session levels*/
    0U, /* Number of sub service security levels */
  },
};
/* Array of services for Service table 'DcmDsdServiceTable_0' (id 0) */
STATIC CONST(Dcm_SidTabEntryConfigType, DCM_CONST) Dcm_SidTabEntryConfig0[7] =
{
  {
    NULL_PTR,
    NULL_PTR,
    (Dcm_SidTabEntryConfig0_SubSidTabEntryConfig16), /*Pointer to subservices array. */
    NULL_PTR,
    &Dcm_DspInternal_DiagnosticSessionControl_SvcH,  /* Pointer to service function */
    NULL_PTR,
    0x10U, /* ServiceId */
    0U, /* Number of sessions */
    0U, /* Number of security levels */
    3U, /*Number of subservices */
    TRUE, /* Subfunction available */
    FALSE /* AsyncServiceExecution available */
  },
  {
    &( Dcm_SidTabSesLevels[0]), /* Pointer to sessions */
    NULL_PTR,
    (Dcm_SidTabEntryConfig0_SubSidTabEntryConfig17), /*Pointer to subservices array. */
    NULL_PTR,
    &Dcm_DspInternal_ECUReset_SvcH,  /* Pointer to service function */
    NULL_PTR,
    0x11U, /* ServiceId */
    1U, /* Number of sessions */
    0U, /* Number of security levels */
    5U, /*Number of subservices */
    TRUE, /* Subfunction available */
    FALSE /* AsyncServiceExecution available */
  },
  {
    &( Dcm_SidTabSesLevels[1]), /* Pointer to sessions */
    NULL_PTR,
    NULL_PTR, /*Pointer to subservices array. */
    NULL_PTR,
    &Dcm_DspInternal_ClearDiagnosticInformation_SvcH,  /* Pointer to service function */
    NULL_PTR,
    0x14U, /* ServiceId */
    1U, /* Number of sessions */
    0U, /* Number of security levels */
    0U, /*Number of subservices */
    FALSE, /* Subfunction available */
    FALSE /* AsyncServiceExecution available */
  },
  {
    &( Dcm_SidTabSesLevels[2]), /* Pointer to sessions */
    NULL_PTR,
    (Dcm_SidTabEntryConfig0_SubSidTabEntryConfig25), /*Pointer to subservices array. */
    NULL_PTR,
    &Dcm_DspInternal_ReadDTCInformation_SvcH,  /* Pointer to service function */
    NULL_PTR,
    0x19U, /* ServiceId */
    1U, /* Number of sessions */
    0U, /* Number of security levels */
    6U, /*Number of subservices */
    TRUE, /* Subfunction available */
    FALSE /* AsyncServiceExecution available */
  },
  {
    &( Dcm_SidTabSesLevels[3]), /* Pointer to sessions */
    NULL_PTR,
    (Dcm_SidTabEntryConfig0_SubSidTabEntryConfig40), /*Pointer to subservices array. */
    NULL_PTR,
    &Dcm_DspInternal_CommunicationControl_SvcH,  /* Pointer to service function */
    NULL_PTR,
    0x28U, /* ServiceId */
    1U, /* Number of sessions */
    0U, /* Number of security levels */
    4U, /*Number of subservices */
    TRUE, /* Subfunction available */
    FALSE /* AsyncServiceExecution available */
  },
  {
    &( Dcm_SidTabSesLevels[4]), /* Pointer to sessions */
    NULL_PTR,
    NULL_PTR, /*Pointer to subservices array. */
    NULL_PTR,
    &Dcm_DspInternal_TesterPresent_SvcH,  /* Pointer to service function */
    NULL_PTR,
    0x3eU, /* ServiceId */
    1U, /* Number of sessions */
    0U, /* Number of security levels */
    0U, /*Number of subservices */
    TRUE, /* Subfunction available */
    FALSE /* AsyncServiceExecution available */
  },
  {
    &( Dcm_SidTabSesLevels[5]), /* Pointer to sessions */
    NULL_PTR,
    (Dcm_SidTabEntryConfig0_SubSidTabEntryConfig133), /*Pointer to subservices array. */
    NULL_PTR,
    &Dcm_DspInternal_ControlDTCSetting_SvcH,  /* Pointer to service function */
    NULL_PTR,
    0x85U, /* ServiceId */
    1U, /* Number of sessions */
    0U, /* Number of security levels */
    2U, /*Number of subservices */
    TRUE, /* Subfunction available */
    FALSE /* AsyncServiceExecution available */
  },
};















#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
#if (DCM_NUM_COMCONTROL_ALL_CHANNEL > 0U)
/* Array of configuration information for Com Control All Channels */
CONST(Dcm_ComControlAllChannelType, DCM_CONST) Dcm_ComControlAllChannel[DCM_NUM_COMCONTROL_ALL_CHANNEL] =
{
};
#endif

#if (DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL > 0U)
/* Array of configuration information for Com Control All Channels */
CONST(Dcm_ComControlSpecificChannelType, DCM_CONST) Dcm_ComControlSpecificChannel[DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL] =
{
};
#endif

#if (DCM_COMCONTROL_LOOKUP_SIZE > 0U)
/* Array of ComMChannels and SchM Switch pointers for CommunicationControl */
CONST(Dcm_ComControlLookupType, DCM_CONST) Dcm_ComControlLookUpTable[DCM_COMCONTROL_LOOKUP_SIZE] =
{
  {
    0U, /* Network Id */
    &SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_0, /* pointer to SchM Switch for DcmCommunicationControl */
  },


};
#endif /* #if (DCM_COMCONTROL_LOOKUP_SIZE > 0U) */
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if DCM_DID_REF_COUNT > 0
#define DCM_START_SEC_CONST_16
#include <MemMap.h>

/* Array for Dids which is referred from other Dids. */
STATIC CONST(uint16,DCM_CONST) Dcm_DidRefers[DCM_DID_REF_COUNT] =
{
};
#define DCM_STOP_SEC_CONST_16
#include <MemMap.h>
#endif

/*==================[internal data]==============================================================*/

#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/* Allocate memory of buffers configured for the Dcm module */










STATIC uint8 Dcm_Buffer[768];

STATIC uint8 Dcm_NRCBuffer[3];

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/* Array holding the channel identifiers configured and the current state the channel is in */
VAR (Dcm_ChannelTabEntryType, DCM_VAR) Dcm_ChannelId[DCM_NUM_CHANNELID] =
{
  {
    0U,
    DCM_ENABLE_RX_TX_NORM
  },
};
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external constants]=========================================================*/
#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Configuration structure */
CONST(Dcm_ConfigType, DCM_CONST) DcmConfigSet_0 = {0U};



/* Array of configuration information for diagnostic sessions */
CONST(Dcm_SesTabEntryConfigType, DCM_CONST) Dcm_SesTabEntryConfig0[4] =
{
  {
    500U,/*P2StarMaxTime*/
    DCM_NO_BOOT,/*specifies whether this session allows to jump to Bootloader */
    5U, /*P2MaxTime*/
    1U,/* Session type */
  },
  {
    200U,/*P2StarMaxTime*/
    DCM_NO_BOOT,/*specifies whether this session allows to jump to Bootloader */
    10U, /*P2MaxTime*/
    3U,/* Session type */
  },
  {
    700U,/*P2StarMaxTime*/
    DCM_NO_BOOT,/*specifies whether this session allows to jump to Bootloader */
    50U, /*P2MaxTime*/
    2U,/* Session type */
  },
  {
    500U,/*P2StarMaxTime*/
    DCM_NO_BOOT,/*specifies whether this session allows to jump to Bootloader */
    50U, /*P2MaxTime*/
    255U,/* Session type */
  },
};

/* Holds configuration information for diagnostic sessions */
CONST(Dcm_SesTabConfigType, DCM_CONST) Dcm_SesTabConfig[DCM_NUM_PROTOCOL] =
{
  {
    Dcm_SesTabEntryConfig0, /* Pointer to session configurations */
    4U, /* Number of configured sessions */
    0U /* Index of default session */
  },
};


/* Holds configuration information for security levels */
CONST(Dcm_SecTabConfigType, DCM_CONST) Dcm_SecTabConfig =
{
  NULL_PTR,
  0U /* Number of configured security levels */
};


/* Initialize global array holding the configuration for each buffer */
CONST(Dcm_BufferConfigType, DCM_CONST) Dcm_BufferConfig[3] =
{
  {
    &Dcm_Buffer[0], /* Pointer to buffer */
    &Dcm_BufferInfo[0], /* Pointer to buffer status information */
    256U /* Size of buffer*/
  },
  {
    &Dcm_Buffer[256], /* Pointer to buffer */
    &Dcm_BufferInfo[1], /* Pointer to buffer status information */
    256U /* Size of buffer*/
  },
  {
    &Dcm_Buffer[512], /* Pointer to buffer */
    &Dcm_BufferInfo[2], /* Pointer to buffer status information */
    256U /* Size of buffer*/
  },
};

/* Initialize global array holding the configuration for each NRC buffer */
CONST(Dcm_BufferConfigType, DCM_CONST) Dcm_NRCBufferConfig[1] =
{
  {
    &Dcm_NRCBuffer[0], /* Pointer to buffer */
    &Dcm_NRCBufferInfo[0], /* Pointer to buffer status information */
    3U /* Size of buffer*/
  },
};


/* Initialize global array holding the configuration for the service Id table */
CONST(Dcm_SidTabConfigType, DCM_CONST) Dcm_SidTabConfig[1] =
{
  {
    Dcm_SidTabEntryConfig0, /* Pointer to array of service table entries */
    7U /* Number of service entries within this table */
  },
};


/* Initialize global array holding the protocol configuration */
CONST(Dcm_HsmConfigType, DCM_CONST) Dcm_HsmConfig[1] =
{
  {
    DCM_ROE_TYPE1, /* Protocol transmission type */
    0U, /*P2ServerAdjustTime*/
    0U, /*P2StarServerAdjustTime */      DCM_UDS_ON_CAN, /* Protocol type */
    0U, /* Priority */
    /* !LINKSTO Dcm.LinktoServiceTable.ProtocolInit,1 */
    0U, /* Dcm_SidTabConfigType */
    2U, /* Tx buffer Id */
    FALSE, /* endianness Conversion */
    TRUE /* Send RP OnTransToBoot */
  },
};

/* Initialize global array holding the protocol configuration for each Rx Pdu Id */
CONST(Dcm_RxPduIdConfigType, DCM_CONST) Dcm_RxPduIdConfig[DCM_NUM_RX_PDU_ID] =
{
  {
    0U, /* Tester source address configured per protocol */
    DCM_PHYSICAL_TYPE, /* Addressing Type for this Pdu Id */
    1U, /* ID of buffer used for this Rx Pdu Id */
    0U, /* ID of protocol for this Rx Pdu Id */
    0U, /* ID of connection for this Rx Pdu Id */
    0U /* Index of Channel Identifier in Dcm_ChannelId[] */
  },
  {
    0U, /* Tester source address configured per protocol */
    DCM_FUNCTIONAL_TYPE, /* Addressing Type for this Pdu Id */
    0U, /* ID of buffer used for this Rx Pdu Id */
    0U, /* ID of protocol for this Rx Pdu Id */
    0U, /* ID of connection for this Rx Pdu Id */
    0U /* Index of Channel Identifier in Dcm_ChannelId[] */
  },
};


/* Initialize global array holding the TxPduId and TxConfirmationPduId configuration for Main connection configuration **/
CONST(Dcm_TxPduIdConfigType, DCM_CONST) Dcm_TxPduIds[DCM_NUM_TX_PDU_ID] =
{
  {
    0U,
    0U,
  },
};








#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[external data]==============================================================*/

/*==================[external function definitions]==============================================*/
#define DCM_START_SEC_CODE
#include <MemMap.h>

FUNC(Std_ReturnType, DCM_CODE) Dcm_DefaultSessionModeEntry(void)
{
  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);
  if (curHsmInfo->msgContext.idContext == DCM_SID_SESSION_CONTROL)
  {
    curHsmInfo->confirmedDiagSession = DCM_DEFAULT_SESSION;
  }
  return E_OK;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtendedDiagnosticSessionModeEntry(void)
{
  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);
  if (curHsmInfo->msgContext.idContext == DCM_SID_SESSION_CONTROL)
  {
    curHsmInfo->confirmedDiagSession = DCM_EXTENDED_DIAGNOSTIC_SESSION;
  }
  return E_OK;
}
FUNC(Std_ReturnType, DCM_CODE) Dcm_ProgrammingSessionModeEntry(void)
{
  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(Dcm_CurProtocolId);
  if (curHsmInfo->msgContext.idContext == DCM_SID_SESSION_CONTROL)
  {
    curHsmInfo->confirmedDiagSession = DCM_PROGRAMMING_SESSION;
  }
  return E_OK;
}









#define DCM_STOP_SEC_CODE
#include <MemMap.h>
/*==================[internal function definitions]==============================================*/


/*==================[end of file]================================================================*/
