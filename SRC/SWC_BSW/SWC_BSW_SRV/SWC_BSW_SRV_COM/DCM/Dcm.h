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
#if (!defined DCM_H)
#define DCM_H

/*==================[inclusions]=================================================================*/

#include <ComStack_Types.h>                                           /* AUTOSAR Com Stack types */

#include <Dcm_Version.h>                                          /* Module version declarations */
#include <Dcm_Types.h>                                                    /* DCM type definition */

/*==================[macros]=====================================================================*/

#if (defined DCM_NUMBER_OF_ROE_EVENTS)
#error DCM_NUMBER_OF_ROE_EVENTS already defined
#endif /* if (defined DCM_NUMBER_OF_ROE_EVENTS) */

/** \brief Value of number of ROE Events supported. **/
#define DCM_NUMBER_OF_ROE_EVENTS 0x02U

/*==================[type definitions]===========================================================*/

/** \brief This type contains the information needed while processing ResponseOnEvent Service (0x86)
 **/
typedef struct
{
  /** \brief Structure element to hold RxPduId on which Start ROE service request is received **/
  PduIdType DcmRxPduId;
  /** \brief Structure element indicating the number of identified ROE events **/
  uint8 NoOfIdentifiedEvents[2];
  /** \brief Structure element holding ServiceToRespond data from request for 0x01 subfunction **/
  uint8 Dcm_EventRecord_0x01[6];
  /** \brief Structure element holding ServiceToRespond data from request for 0x03 subfunction **/
  uint8 Dcm_EventRecord_0x03[8];
  /** \brief Global variable holding the status information of ROE Event Type **/
  uint8 Dcm_RoeEventLogic[DCM_NUMBER_OF_ROE_EVENTS];
  /** \brief Element indicating the event for which final ROE response needs to be sent **/
  uint8 FinalRoeResponse[DCM_NUMBER_OF_ROE_EVENTS];
  /** \brief Structure element indicating whether persistence bit set or not **/
  boolean RoeStoreBit[2];
#if (DCM_ROE_PERSISTENCE == STD_ON)
  /** \brief Element indicating the NvM write was successful before reading **/
  boolean NvMWriteFlag;
#endif
}
Dcm_RoeDataType;

/*==================[external function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

/** \brief Initialze Dcm
 ** Service for basic initialization of DCM module.The Initialization function will initialize all
 ** DCM global variables with the values of the configuration.
 **/
extern FUNC(void, DCM_CODE) Dcm_Init(
  P2CONST(Dcm_ConfigType, AUTOMATIC, DCM_APPL_CONST) ConfigPtr);

#if (DCM_VERSION_INFO_API == STD_ON)
/** \brief Get Version Information
 **
 ** \param versioninfo Pointer to location where version info is written to
 **/
extern FUNC(void, DCM_CODE) Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) versioninfo);
#endif /* DCM_VERSION_INFO_API */

/* hide declaration in own header if included by DCM itself and RTE is
 * enabled */
#if (DCM_INCLUDE_RTE == STD_OFF)

/** \brief DCM provides with this the active Protocol name
 **
 ** \param[out] ActiveProtocol Active diagnostic protocol (::DCM_UDS_ON_CAN, ::DCM_OBD_ON_CAN, ...)
 **
 ** \return Success status
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol(
  P2VAR(Dcm_ProtocolType, AUTOMATIC, DCM_APPL_DATA) ActiveProtocol);

/** \brief Provides the active session control type value.
 **
 ** This function Provides the active session control type value.
 **
 ** \param[out] SesCtrlType  Active Session Control Type value Content is according to
 ** "diagnosticSessionType" parameter of DiagnosticSessionControl request
 **
 ** \return Active Session Control Type value
 **
 ** \ServiceID{::DCM_SERVID_GETSESCTRLTYPE}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
  P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SesCtrlType);

/** \brief Provides the active security level value.
 **
 ** This function Provides the active security level value.
 **
 ** \param[out] SecLevel  Active Security Level value
 ** Conversion formula to calculate SecurityLevel out of tester requested
 ** SecurityAccessType parameter:
 ** SecurityLevel = (SecurityAccessType + 1) / 2
 ** Content of SecurityAccessType is according to "securityAccessType"
 ** parameter of SecurityAccess request
 **
 ** \return Active Security Level value
 **
 ** \ServiceID{::DCM_SERVID_GETSECURITYLEVEL}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel(
  P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel);

/** \brief Provides the ResetToDefaultSession interface for user.
 **  When this function is called current session will be swicted to default
 **  session. If current session is default session, E_OK is returned without any session change.
 **  BswM is not informed of the transition to default session.
 **
 ** \return Always return E_OK.
 **
 ** \ServiceID{::DCM_SERVID_RESETTODEFAULTSESSION}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(void);

/** \brief Allows to notify Dcm that a event has been triggered (for service RoE).
 **
 ** When this function is called, Dcm executes the service requested in subfunction
 ** serviceToRespondTo.
 **
 ** \param[in] RoeEventId Identifier of the event that is triggered
 **
 ** \return Validity of the event identifier RoeEventId
 **
 ** \ServiceID{::DCM_SERVID_TRIGGERONEVENT}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Asynchronous}
 **/
extern FUNC(Std_ReturnType, DCM_CODE)  Dcm_TriggerOnEvent(
  uint8 RoeEventId );

/** \brief main loop within the DSD part of the DCM module **/
extern FUNC(void, DCM_CODE) Dcm_MainFunction(void);

#endif

/** \brief Allows Dem to notify Dcm on status change of a DTC (for service RoE).
 **
 ** When this function is called, Dcm verifies the DTC against the status mask in
 ** the diagnostic request and if the verification is positive, executes the associated
 ** service (serviceToRespondTo).
 **
 ** \param[in] DTC Identifier of the DTC
 ** \param[in] DTCStatusOld Status of the DTC before the change
 ** \param[in] DTCStatusNew Status of the DTC after the change
 **
 ** \return Always return E_OK.
 **
 ** \ServiceID{::DCM_SERVID_DEMTRIGGERONDTC}
 ** \Reentrancy{Non-Reentrant}
 ** \Synchronicity{Synchronous}
 **/
 extern FUNC(Std_ReturnType, DCM_CODE)  Dcm_DemTriggerOnDTCStatus(
  uint32 DTC,
  uint8 DTCStatusOld,
  uint8 DTCStatusNew);

/** \brief Send a response
 **
 ** When this function is called, a response will be sent based on the data contained in
 ** pMsgContext. If Dcm_ExternalSetNegResponse() was called before, a negative response is sent,
 ** otherwise a positive response will be sent. The application does not have to care about
 ** any timing requirement to process a request.
 **
 ** For diagnostic experts:
 ** Between the arrival of a request (XXX_Dcm<DiagnosticService>) and finishing the corresponding
 ** response (Dcm_Processing_Done), busy-acknowledges (negative response with response code 0x78)
 ** are sent automatically.
 **
 ** \param[in] pMsgContext Message-related information for one one diagnostic protocol identifier.
 **/
extern FUNC(void, DCM_CODE) Dcm_ExternalProcessingDone(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if (DCM_ROE_ENABLED == STD_ON)
/** \brief Send Response of one Event
 ** This function provides the processing of one event, requested by the Central Diagnostic
 ** Software Component.
 **
 ** \return Permission of DCM
 **   - ::DCM_E_OK: ResponseOnOneEvent request is accepted by DCM and the request data is copied
 **                 into internal reception buffer,
 **   - ::DCM_E_ROE_NOT_ACCEPTED: ResponseOnOneEvent request is not accepted by DCM
 **                               (e.g. current pending request is not finished)
 **
 ** \param[in] MsgPtr Content of requested service
 ** \param[in] MsgLen Length in bytes
 ** \param[in] DcmRxPduId PDU ID through which ROE service request is received
 **/
extern FUNC(Dcm_StatusType, DCM_CODE) Dcm_DslInternal_ResponseOnOneEvent(
  P2CONST(Dcm_MsgItemType, AUTOMATIC, DCM_CONST) MsgPtr,
  PduLengthType                 MsgLen,
  PduIdType                     DcmRxPduId);
#endif

#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
/** \brief Notification of Reset Mode entered
 **
 ** This provides a confirmation for a 'HardReset' request received from tester  */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_HardResetModeEntry(void);

/** \brief Notification of Reset Mode entered
 **
 ** This provides a confirmation for a 'KeyOnOffReset' request received from tester  */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_KeyOnOffResetModeEntry(void);

/** \brief Notification of Reset Mode entered
 **
 ** This provides a confirmation for a 'SoftReset' request received from tester  */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SoftResetModeEntry(void);

/** \brief Notification of Reset Mode entered
 **
 ** This provides a confirmation for a 'EnableRapidPowerShutdownReset' request received from tester
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRapidPowerShutdownResetModeEntry(void);

/** \brief Notification of Reset Mode entered
 **
 ** This provides a confirmation for a 'DisableRapidPowerShutdownReset' request received from tester
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRapidPowerShutdownResetModeEntry(void);

/** \brief Notification of Reset Mode entered
 **
 ** This provides a confirmation for a 'BootloaderReset' request received from tester  */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_BootloaderResetModeEntry(void);

/** \brief Notification of Reset Mode entered
 **
 ** This provides a confirmation for a 'SsBootloaderReset' request received from tester  */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SsBootloaderResetModeEntry(void);
#endif

#if(DCM_0X28_SVC_ENABLED == STD_ON)

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for an 'EnableRxTx' request for normalCommunicationMessages
 ** received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxTxNormModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for an 'EnableRxDisableTx' request for normalCommunicationMessages
 ** received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxDisableTxNormModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'DisableRxEnableTx' request for normalCommunicationMessages
 ** received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxEnableTxNormModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'DisableRxTx' request for normalCommunicationMessages
 ** received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxTxNormModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'EnableRxTx' request for
 ** networkManagementCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxTxNmModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'EnableRxDisableTx' request for
 ** networkManagementCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxDisableTxNmModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'DisableRxEnableTx' request for
 ** networkManagementCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxEnableTxNmModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'DisableRxTx' request for
 ** networkManagementCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxTxNmModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'EnableRxTx' request for
 ** networkManagementCommunicationMessages and normalCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxTxNormNmModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'EnableRxDisableTx' request for
 ** networkManagementCommunicationMessages and normalCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_EnableRxDisableTxNormNmModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'DisableRxEnableTx' request for
 ** networkManagementCommunicationMessages and normalCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxEnableTxNormNmModeEntry(void);

/** \brief Notification of Communication Mode entered
 **
 ** This provides a confirmation for a 'DisableRxTx' request for
 ** networkManagementCommunicationMessages and normalCommunicationMessages received from tester
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DisableRxTxNormNmModeEntry(void);

#endif /* #if(DCM_0X28_SVC_ENABLED == STD_ON) */

/*------------------[Callouts functions]-----------------------------*/

/** \brief Callout for RequestDownload
 **
 **  This callout allows the user to implement the negotiation of a data transfer
 ** from the tester to the ECU.
 **
 ** \param[in]    OpStatus Operation status
 ** \param[in]    DataFormatIdentifier Format identifier from the request
 ** \param[in]    MemoryAddress Memory address to download
 ** \param[in]    MemorySize Size of memory to be downloaded
 ** \param[in]    BlockLength Maximum number of bytes for a write operation
 ** \param[in,out] ErrorCode NRC if the request for download fails.
 **
 ** \return E_OK, E_NOT_OK or DCM_E_PENDING.
 */
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ProcessRequestDownload(
  Dcm_OpStatusType  OpStatus,
  uint8 DataFormatIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  uint32 BlockLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Callout for RequestUpload.
 **
 **  This callout allows the user to implement the negotiation of a data transfer
 ** from the ECU to the tester.
 **
 ** \param[in]    OpStatus Operation status
 ** \param[in]    DataFormatIdentifier Format identifier from the request
 ** \param[in]    MemoryAddress Memory address to upload
 ** \param[in]    MemorySize Size of memory to be uploaded
 ** \param[in,out] ErrorCode NRC if the request for upload fails.
 **
 ** \return E_OK, E_NOT_OK or DCM_E_PENDING.
 */
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ProcessRequestUpload(
  Dcm_OpStatusType  OpStatus,
  uint8 DataFormatIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/* !LINKSTO Dcm.EB.ReadMemory.WriteMemory.CallbacksNotDefined,1 */
#if ((DCM_0X23_SVC_ENABLED == STD_ON) || \
     (DCM_0X36_SVC_ENABLED == STD_ON))
/** \brief Callout for upload of data (used for service TransferData).
 **
 ** This callout allows the user to transfer data from the ECU to the tester, after
 ** successful execution of a RequestUpload service.
 **
 ** \param[in]    OpStatus Operation status
 ** \param[in]    MemoryIdentifier Identifier of the memory device (optional)
 ** \param[in]    MemoryAddress Start address of the memory from which data is to be retrieved
 ** \param[in]    MemorySize Number of bytes to be read
 ** \param[in,out] MemoryData Pointer to the buffer in Dcm
 **
 ** \return DCM_READ_OK, DCM_READ_PENDING or DCM_READ_FAILED.
 */
extern FUNC(Dcm_ReturnReadMemoryType, DCM_APPL_CODE) Dcm_ReadMemory(
  Dcm_OpStatusType  OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) MemoryData);

#endif/*#if ((DCM_0X23_SVC_ENABLED == STD_ON) || \
             (DCM_0X36_SVC_ENABLED == STD_ON))*/

#if ((DCM_0X3D_SVC_ENABLED == STD_ON) || \
     (DCM_0X36_SVC_ENABLED == STD_ON))

/** \brief Callout for download of data (used for service TransferData).
 **
 ** This callout allows the user to transfer data from the tester to the ECU, after
 ** successful execution of a RequestDownload service.
 **
 ** \param[in]    OpStatus Operation status
 ** \param[in]    MemoryIdentifier Identifier of the memory device (optional)
 ** \param[in]    MemoryAddress Start address of the memory from which data is to be retrieved
 ** \param[in]    MemorySize Number of bytes to be read
 ** \param[in,out] MemoryData Pointer to the buffer in Dcm
 **
 ** \return DCM_WRITE_OK, DCM_WRITE_PENDING or DCM_WRITE_FAILED.
 */
extern FUNC(Dcm_ReturnWriteMemoryType, DCM_APPL_CODE) Dcm_WriteMemory(
  Dcm_OpStatusType  OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) MemoryData);

#endif /*#if ((DCM_0X3D_SVC_ENABLED == STD_ON) || \
             (DCM_0X36_SVC_ENABLED == STD_ON))*/

/** \brief Callout for termination of an upload or download process.
 **
 ** This callout allows the user to terminate the data transfer between the ECU and the tester.
 **
 ** \param[in]    OpStatus Operation status
 ** \param[in]    ParameterRecord Pointer to vehicle/manufacturer specific data (optional)
 ** \param[in]    ParameterRecordSize Length of ParameterRecord in bytes (optional)
 ** \param[in,out] ErrorCode NRC if the request for termination fails.
 **
 ** \return E_OK, E_NOT_OK or DCM_E_PENDING.
 */
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_ProcessRequestTransferExit(
  Dcm_OpStatusType  OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) ParameterRecord,
  uint32 ParameterRecordSize,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Callout for service LinkControl.
 **
 ** This callout allows the user to control the communication baud rate of the ECU.
 **
 ** \param[in]    OpStatus Operation status
 ** \param[in]    LinkControlRequestType Sub-function identifier.
 ** \param[in]    BaudrateRecord Pointer to the array which holds the baudrate
 ** \param[in,out] ErrorCode NRC if the request for baudrate change fails.
 **
 ** \return E_OK, E_NOT_OK or DCM_E_PENDING.
 */
extern FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_LinkControl(
  Dcm_OpStatusType  OpStatus,
  Dcm_LinkControlRequestType LinkControlRequestType,
  P2VAR(uint8, AUTOMATIC, DCM_VAR)  BaudrateRecord,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Callout for storing the program conditions.
 **
 ** This callout allows the user to store the programing environment in a
 ** non-volatile memory before jumping to bootloader.
 **
 ** \param[in]  ProgConditions Pointer to the structure which holds the program conditions
 **
 ** \return E_OK, E_NOT_OK or DCM_E_PENDING.
 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SetProgConditions(
  P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions);

/** \brief Callout for retrieving the stored program conditions.
 **
 ** This callout allows the user to retrieve the stored programing environment from the
 ** non-volatile memory after jumping from bootloader.
 **
 ** \param[in,out]  ProgConditions Pointer to the structure which holds the program conditions
 **
 ** \return DCM_COLD_START or DCM_WARM_START.
 */
extern FUNC(Dcm_EcuStartModeType, DCM_CODE) Dcm_GetProgConditions(
  P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions);

/** \brief Send a negative response instead of a positive response
 ** The negative response code is taken from the first call - duplicate calls are allowed but the
 ** errorCode transmitted is ignored. The transmission of the negative response will be performed
 ** after emiting PROC_DONE.
 **
 ** \param[in] pMsgContext Message-related information for one diagnostic protocol identifier.
 **
 ** \param[in] errorCode Error code to be set. This error code will be taken as negative response
 ** code (NRC) (see description).(::DCM_E_GENERALREJECT, ::DCM_E_SERVICENOTSUPPORTED,
 ** ::DCM_E_SUBFUNCTIONNOTSUPPORTED, ::DCM_E_REQUESTCORRECTLYRECEIVEDRESPONSEPENDING, ...)
 **/
extern FUNC(void, DCM_CODE) Dcm_ExternalSetNegResponse(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_NegativeResponseCodeType errorCode);

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/
#if (DCM_ROE_ENABLED == STD_ON)
#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Global variable holding the status information of ROE Service **/
extern VAR(Dcm_RoeDataType, DCM_VAR) Dcm_RoeData;

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#endif /* #if (DCM_ROE_ENABLED == STD_ON) */
/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* if !defined( DCM_H ) */
/*==================[end of file]================================================================*/
