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

/*This file contains the implementation of the Diagnostic Service
  * Processing module in Dcm. */

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 17.4 (required)
 *     Array indexing shall be the only allowed form of pointer arithmetic.
 *
 *     Reason:
 *     This operation will not cause any problem and reduce the need for extra index variable
 *
 *  MISRA-2) Deviated Rule: 12.5 (required)
 *     The operands of a logical && or || shall be primary-expressions.
 *
 *     Reason:
 *     Misra has an exception that whenever an expression consists of either a sequence of only
 *     logical && or a sequence of only logical && or logical ||, extra parentheses are not required
 *
 *  MISRA-3) Deviated Rule: 15.2 (required)
 *     An unconditional break statement shall terminate every non-empty switch clause.
 *
 *     Reason:
 *     The break is removed. Because the following actions has to be done in the same state.
 *     So in order to avoid repeating the same code again, the break statement is removed.
 *     This will reduce the code size.
 *
 * MISRA-4) Deviated Rule: 16.7 (required)
 *     A pointer parameter in a function prototype should be declared as
 *     pointer to const if the pointer is not used to modify the addressed
 *     object.
 *
 *     Reason:
 *     a) Service and sub-service handlers shares a common signature. It may not be possible to use
 *     constants since the functional use of these pointer parameters is different in different
 *     service and sub-service handlers
 *     b) The pointer can be modified in a routine that is called from the function
 *
 * MISRA-5) Deviated Rule: 14.6 (required)
 *     For any iteration statement there shall be at most one break statement used
 *     for loop termination
 *
 *     Reason:
 *     The iteration needs to be terminated when some particular conditions are satisfied.
 *     Adapting such algorithm optimizes the code.
 *
 * MISRA-6) Deviated Rule: 19.10 (required)
 *     Parameter instance shall be enclosed in parentheses.
 *
 *     Reason:
 *     The macro is used in function parameter declarations and definitions
 *     where the number of parentheses matter.
 */

/*===============================[includes]======================================================*/

#include <Dcm_Trace.h>
#include <Std_Types.h>                                                 /* AUTOSAR standard types */

#include <Dcm.h>                                                      /* Declaration of Dcm APIs */
#include <Dcm_HsmDcm.h>                                   /* public statechart model definitions */
#include <Dcm_DspExternal.h>                           /* Callbacks provided by Central Diag SwC */
#include <Dcm_Int.h>                                               /* Module intenal definitions */

#include <Dem.h>
#if (DCM_BSWM_API_ENABLED == STD_ON)
#include <BswM_DCM.h>                                                  /* BswM interface for Dcm */
#endif
#include <ComM_Dcm.h>                                                  /* ComM interface for Dcm */
#include <SchM_Dcm.h>                                                  /* SchM interface for Dcm */
#include <TSMem.h>                                               /* EB specific memory functions */
/*===========================[macro definitions]=================================================*/

/* The number of bits to be shifted right to get the byte position */
#define DCM_BYTE_POSITION_SHIFTS            (0x03U)
/* The mask to determine the bit position within a byte */
#define DCM_BIT_POSITION_MASK               (0x07U)
/* The maximum number of bits to be copied in a byte */
#define DCM_MAX_BIT_POSITION                (0x07U)
/* Macro to extract lowest nibble from a byte data */
#define DCM_MASK_NIBBLE                     (0x0FU)
/* Macro to extract lowest byte from a data */
#define DCM_MASK_BYTE                       (0xFFU)
/* Macro for number of bits in a nibble */
#define DCM_NIBBLE_BITS                     (0x04U)
/* Macro for number of bits in a byte */
#define DCM_BYTE_BITS                       (0x08U)
/* Macro for maximum number of bytes in an address */
#define DCM_MAX_ADDRESS_BYTES               (0x04U)
/* Macro for maximum number of bytes in an address */
#define DCM_MAX_MEMSIZE_BYTES               (0x04U)
/* Macro for All supported DTC's  */
#define DCM_REPORT_ALLSUPPORTEDDTC          (0x00U)
/* Macro for ControlDtcSetting service ID */
#define DCM_DSP_SERVICE_0X85                (0x85U)
/* Control Mask for 0x2F to parse 'controlEnableMaskRecord' */
#define DCM_CONTROL_MASK_MSB                (0x80U)
/* Macro for CommunicationControl service ID */
#define DCM_DSP_SERVICE_0X28                (0x28U)

/* 0x10 service response length with timing values in response */
#define DCM_0x10_RESPONSELENGTH_TIMING_VALUES      (5U)
/* 0x10 service response length without timing values in response */
#define DCM_0x10_RESPONSELENGTH_NO_TIMING_VALUES   (1U)

/* Size of AddressAndLengthFormatIdentifier in bytes */
#define DCM_ADDRESSANDLENGTHFORMATID_SIZE   (0x01U)

/* Macros for InputOutputControlParameter */
#define DCM_RETURNCONTROLTOECU              (0x00U)
#define DCM_RESETTODEFAULT                  (0x01U)
#define DCM_FREEZECURRENTSTATE              (0x02U)
#define DCM_SHORTTERMADJUSTMENT             (0x03U)
#define DCM_0x2F_REQUESTLENGTH              (0x03U)

/* Macro for DID bit mask */
#define DCM_DID_BLOCK_MASK_NUM  ((DCM_NUM_DID / 8U) + 1U)
/*=====================[external constants declarations]=========================================*/

/*=====================[internal constants declarations]=========================================*/

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

#if((DCM_0X28_SVC_ENABLED == STD_ON) && \
    ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)))
STATIC CONST(Dcm_CommunicationModeType, DCM_CONST) Dcm_CommunicationModes[4][4] =
  {{DCM_0X28_COMM_MODE_INVALID, DCM_0X28_COMM_MODE_INVALID, DCM_0X28_COMM_MODE_INVALID,
    DCM_0X28_COMM_MODE_INVALID},
   {DCM_ENABLE_RX_TX_NORM, DCM_ENABLE_RX_DISABLE_TX_NORM, DCM_DISABLE_RX_ENABLE_TX_NORM,
    DCM_DISABLE_RX_TX_NORM},
   {DCM_ENABLE_RX_TX_NM, DCM_ENABLE_RX_DISABLE_TX_NM, DCM_DISABLE_RX_ENABLE_TX_NM,
    DCM_DISABLE_RX_TX_NM},
   {DCM_ENABLE_RX_TX_NORM_NM, DCM_ENABLE_RX_DISABLE_TX_NORM_NM, DCM_DISABLE_RX_ENABLE_TX_NORM_NM,
    DCM_DISABLE_RX_TX_NORM_NM}};

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
STATIC CONST(Dcm_CommunicationModeType, DCM_CONST) Dcm_RteCommunicationModes[4][4] =
  {{DCM_0X28_COMM_MODE_INVALID, DCM_0X28_COMM_MODE_INVALID,
    DCM_0X28_COMM_MODE_INVALID, DCM_0X28_COMM_MODE_INVALID},
   {RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM,
    RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM,
    RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM,
    RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM},
   {RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NM,
    RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NM,
    RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NM,
    RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NM},
   {RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM,
    RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_DISABLE_TX_NORM_NM,
    RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_ENABLE_TX_NORM_NM,
    RTE_MODE_DcmCommunicationControl_DCM_DISABLE_RX_TX_NORM_NM}};
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */
#endif /* #if((DCM_0X28_SVC_ENABLED == STD_ON) && \
              ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))) */

#if(DCM_0X87_SVC_ENABLED == STD_ON)
/* Dcm_LinkControlBaudrateTable is used to fetch BaudrateRecord for the service
 * LinkControl(0x87) */
STATIC CONST(Dcm_LinkControlBaudrateType, DCM_CONST) Dcm_LinkControlBaudrateTable[9] = {
    {0x01, {0x00, 0x25, 0x80}}, {0x02, {0x00, 0x4B, 0x00}}, {0x03, {0x00, 0x96, 0x00}},
    {0x04, {0x00, 0xE1, 0x00}}, {0x05, {0x01, 0xC2, 0x00}}, {0x10, {0x01, 0xE8, 0x48}},
    {0x11, {0x03, 0xD0, 0x90}}, {0x12, {0x07, 0xA1, 0x20}}, {0x13, {0x0F, 0x42, 0x40}}
  };
#endif /* #if(DCM_0X87_SVC_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
STATIC FUNC(void, DCM_CODE) Dcm_TriggerServiceAsync(void);
#endif /* #if (DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X10 == STD_ON)
/** \brief UDS service 0x10
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControl_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x10
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControl_SvcCont(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
/** \brief Internal handler for Jump to Bootloader
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] OpStatus Status of the service processing
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_JumpToBL(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_OpStatusType OpStatus);

/** \brief Internal handler to process SetProgConditions() call-out
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessSetProgConditions(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_JUMP_TO_BL_ENABLED == STD_ON) */
#endif /* #if(DCM_DSP_USE_SERVICE_0X10 == STD_ON) */

#if((DCM_EXTSVC_ENABLED == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X10 == STD_ON))
/** \brief Function for setting session variable to requested session
 **
 ** \param[in] instIdx  Current HSM instance Id
 **
 **/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_SetSessionState(
  uint8 instIdx);
#endif /* #if((DCM_EXTSVC_ENABLED == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X10 == STD_ON)) */

#if(DCM_DSP_USE_SERVICE_0X11 == STD_ON)
/** \brief UDS service 0x11 internal service handler
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ECUReset_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x11 internal service handler
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ECUReset_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if ((DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON))

#if ((DCM_MODEDECLARATION_SUPPORT == STD_OFF) && (DCM_BSWM_API_ENABLED == STD_ON))
/** \brief Internal handler for Setting ResetMode
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval None
 **/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_SetResetMode(
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif  /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_OFF) && (DCM_BSWM_API_ENABLED == STD_ON)) */

#endif  /* #if ((DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON))  */

#endif /* #if(DCM_DSP_USE_SERVICE_0X11 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X14 == STD_ON)
/** \brief Implementation of UDS service 0x14
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDTCInfo_SvcStart (
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* (DCM_DSP_USE_SERVICE_0X14 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X19 == STD_ON)

/** \brief UDS service 0x19
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDTCInformation_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x19
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDTCInformation_SvcCont(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
#if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON))
 /** \brief UDS service 0x19-0x02 and 0x0A
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDTCByStatusMask (
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)
/** \brief UDS service 0x19-0x03
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDTCSnapshotByIdentification (
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
/** \brief UDS service 0x19-0x04
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDtcSnapshotRecord
(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
);
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
 /** \brief UDS service 0x19-x06
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDtcExtDataRecord
(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
);
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) */
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

#if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON))
/** \brief Used by UDS service 0x19-0x04 0x19-0x06
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] DTC
 **
 ** \retval DCM_E_OK Status retrivel of DEM successful
 ** \retval DCM_E_REQUESTOUTOFRANGE If DTC, DTCOrigin, DTCKind are not correct
 ** \retval DCM_E_GENERALREJECT Any other error occured in DEM
 **/
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemReportStatusByte(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC);
#endif /*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04) ||
             (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
/** \brief Used by UDS service 0x19-0x06
 **
 ** \param[in] DTC
 ** \param[in] ExtendedDataRecordNumber Extended Data Record to be retrived
 ** \param[in] sizeRemainingBuffer Remaining size of response buffer
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[out] resDataLengthPtr Number of bytes filled in response buffer
 **
 ** \retval DCM_E_OK Readout of Extended Data Record successful
 ** \retval DCM_E_REQUESTOUTOFRANGE any other error occured during read out
 **/
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetExtDataRecord(
  uint32 DTC,
  uint8 ExtendedDataRecordNumber,
  PduLengthType sizeRemainingBuffer,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) resDataLengthPtr);
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
/** \brief Used by UDS service 0x19-0x04
 **
 ** \param[in] DTC
 ** \param[in] SnapShotRecordNumber Number of SnapShot Record to be retrived
 ** \param[in] sizeRemainingBuffer Remaining size of response buffer
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[out] resDataLengthPtr Number of bytes filled in response buffer
 **
 ** \retval DCM_E_OK Readout of Extended Data Record successful
 ** \retval DCM_E_REQUESTOUTOFRANGE any other error occured during read out
 **/
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetSnapShotRecord(
  uint32 DTC,
  uint8 SnapShotRecordNumber,
  PduLengthType sizeRemainingBuffer,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) resDataLengthPtr);

#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
/** \brief Enables DTC record update
 **
 ** \param[in] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval None
 **/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_DemEnableDTCRecordUpdate(
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Disables DTC record update
 **
 ** \param[in] DTC
 ** \param[in] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_OK DTC record update disable successful
 ** \retval DCM_E_PENDING DTC record update disable pending
 ** \retval DCM_E_DONE DTC record update disable failed and error is set
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DemDisableDTCRecordUpdate(
 uint32 DTC,
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_OFF) */
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) */

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)

#if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON) )
/** \brief Used to enable process page function to be called from Call Service function of DSP SM
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] processPageFuncId Process page function id
 **
 ** \retval None
 **/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_EnableProcessPage (
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 processPageFuncId);

#endif /* #if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)) */

/** \brief This function is used to update the response buffer pointer and the data length
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol.
 **
 ** \retval None
 **/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_UpdateResponseBuffer (
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
/** \brief The function for getting the total data length of freeze frame corresponding
 **        to the snapshot record number
 **
 ** \param[in] DTC
 ** \param[in] SnapShotRecNum Snapshot record number
 ** \param[in] DataLength Data length
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval None
 **/
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetSizeOfFreezeFrame (
  uint32 DTC,
  uint8  SnapShotRecNum,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) DataLength,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
/** \brief The function for getting the total data length of Extended Data record
 **        corresponding to the extended data record number
 **
 ** \param[in] DTC
 ** \param[in] ExtDataRecNum Extended data record number
 ** \param[in] DataLength Data length
 **
 ** \retval None
 **/
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetSizeOfExtDataRecord (
  uint32 DTC,
  uint8  ExtDataRecNum,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) DataLength);

#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
/** \brief The function for getting all the Extended Data records when requested with 0xFF
 **
 ** \param[in] DTC
 ** \param[in] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE      Operation completed
 ** \retval DCM_E_PENDING   Operation did not complete, it must be called again
 ** \retval DCM_E_ABORT     Operation failed
 **/
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetAllExtDataRecordsPageOff(
  uint32 DTC,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
);
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_OFF) */
#endif /*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06) */
#endif /* (DCM_DSP_USE_SERVICE_0X19 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X27 == STD_ON)

/** \brief UDS service 0x27
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE                  Operation completed
 ** \retval DCM_E_PENDING            Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP    A "response pending" message shall be sent immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x27
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE                  Operation completed
 ** \retval DCM_E_PENDING            Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Handles the Request seed subfunction of SecurityAccess service
 **
 ** \param[in] secTabIdx Security table index
 ** \param[in] OpStatus Status of the service processing
 ** \param[in] newSecLevel Security level requested
 ** \param[in] nrc Negative reponse code
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier
 **
 ** \retval DCM_E_DONE                  Operation completed
 ** \retval DCM_E_PENDING            Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessRequestSeed_SSvcH(
  uint8 secTabIdx,
  Dcm_OpStatusType OpStatus,
  Dcm_SecLevelType newSecLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Handles the GetSeed operation.
 **
 ** \param[in] OpStatus Status of the service processing
 ** \param[in] nrc Negative reponse code
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier
 ** \param[in] newSecTabEntry pointer to configuration information of requested security level
 ** \retval DCM_E_DONE                  Operation completed
 ** \retval DCM_E_PENDING            Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetSeed_Operation(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2CONST(Dcm_SecTabEntryConfigType, AUTOMATIC, DCM_CONST) newSecTabEntry,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Handles the Send Key subfunction of SecurityAccess service
 **
 ** \param[in] secTabIdx Security table index
 ** \param[in] OpStatus Status of the service processing
 ** \param[in] numAttemptsToCopy number of failed attempts
 ** \param[in] newSecLevel Security level requested
 ** \param[in] nrc Negative reponse code
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier
 **
 ** \retval DCM_E_DONE                  Operation completed
 ** \retval DCM_E_PENDING            Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessSendKey_SSvcH(
  uint8 secTabIdx,
  Dcm_OpStatusType OpStatus,
  uint8 numAttemptsToCopy,
  Dcm_SecLevelType newSecLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* (DCM_DSP_USE_SERVICE_0X27 == STD_ON) */

#if(DCM_0X23_SVC_ENABLED == STD_ON)
/** \brief Performs the Memory range validity checks for 'ReadMemory' service
 **
 ** \param[out] memRangeIndex Index to memoryRangeInfo.
 ** \param[out] memIdIndex Index to MemoryIdInfo.
 ** \param[in]   readMemAddress Starting Memory Address to be read.
 ** \param[in]   readMemSize size of memory to be read.
 **
 **/
STATIC FUNC(uint8, DCM_CODE) Dcm_DspInternal_ReadMemoryRangeChk(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memRangeIndex,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memIdIndex,
  uint32 readMemAddress, uint32 readMemSize);
#endif /* #if(DCM_0X23_SVC_ENABLED == STD_ON) */

#if(DCM_0X3D_SVC_ENABLED == STD_ON)
/** \brief Performs the Memory range validity checks for 'WriteMemory' service
 **
 ** \param[out] memRangeIndex Index to memoryRangeInfo.
 ** \param[out] memIdIndex Index to MemoryIdInfo.
 ** \param[in]   readMemAddress Starting Memory Address to be write.
 ** \param[in]   writeMemSize size of memory to be write.
 **
 **/
STATIC FUNC(uint8, DCM_CODE) Dcm_DspInternal_WriteMemoryRangeChk(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memRangeIndex,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memIdIndex,
  uint32 writeMemAddress, uint32 writeMemSize);
#endif /* #if(DCM_0X3D_SVC_ENABLED == STD_ON) */

#if((DCM_0X23_SVC_ENABLED == STD_ON) || \
    (DCM_0X34_SVC_ENABLED == STD_ON) || \
    (DCM_0X35_SVC_ENABLED == STD_ON) || \
    (DCM_0X3D_SVC_ENABLED == STD_ON))
 /** \brief Extracts the Memory address and the size of memory to be read
   **
   ** \param[in] reqData Pointer to 'addressAndLengthFormatIdentifier'.
   ** \param[in] memAddLength length (In bytes) of the memoryAddress parameter.
   ** \param[in] memSizeLength length (In bytes) of the memorySize parameter.
   ** \param[out] memAddress Starting Memory Address to be read.
   ** \param[out] memSize size of memory to be read.
   **
   ** \retval E_OK                Conditions are ok
   ** \retval E_NOT_OK            Conditions are not ok
   **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetMemoryAddressAndSize(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) reqData,
  uint8 memAddLength, uint8 memSizeLength,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) memAddress,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) memSize );

#endif /* #if((DCM_0X23_SVC_ENABLED == STD_ON) || \
    (DCM_0X34_SVC_ENABLED == STD_ON) || \
    (DCM_0X35_SVC_ENABLED == STD_ON) || \
    (DCM_0X3D_SVC_ENABLED == STD_ON)) */

#if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
/** \brief Handles Different condition checks for the service ReadDataByIdentifier 0x22,
    WriteDataByIdentifier: 0x2E and IOCOntrolByIdentifier: 0x2F
 **
 ** \param[in] reqDid Requestd Did
 ** \param[in] DidOp Service is 0x22 or ox2E
 ** \param[out] nrc NRC occured due to condition checks
 ** \param[out] didIntex Index of the Did in the table Dcm_DidTable
 ** \param[in] instIdx Current HSM instance Id
 **
 ** \retval E_OK                Conditions are ok
 ** \retval E_NOT_OK            Conditions are not ok
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DidConditionChecks(
  uint16 reqDid,
  Dcm_DidOpType DidOp,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) didIndex,
  uint8 instIdx);

  /** \brief This function checks the validity of Did signal with respect to the configured Dids
 ** and if the Did is valid then return its index from the Dcm_DidTable
 **
 ** \param[in]  reqDid    Requestd Did
 ** \param[out] didIndex  Index of the Did in the table Dcm_DidTable
 **
 ** \retval E_OK                Conditions are ok
 ** \retval E_NOT_OK            Conditions are not ok
 **/
STATIC FUNC(boolean, DCM_CODE) Dcm_DspInternal_ValidateDidIndex
(
  uint16 reqDid,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) didIndex
);

/** \brief This function checks whether the DID can be read in the current session level
 **
 ** \param[in] instIdx Current HSM instance Id
** \param[in]  AccessInfo Refer to session and security information
 **
 ** \retval E_OK                Conditions are ok
 ** \retval E_NOT_OK            Conditions are not ok
 **/
STATIC FUNC(boolean, DCM_CODE)Dcm_DspInternal_DidConditionChecksSesLevel
(
  uint8 instIdx,
  P2CONST(Dcm_DidAccessInfoType, AUTOMATIC, DCM_CONST) AccessInfo
);

/** \brief This function checks whether the DID can be read in the current security level
 **
 ** \param[in] instIdx Current HSM instance Id
** \param[in]  AccessInfo Refer to session and security information
 **
 ** \retval E_OK                Conditions are ok
 ** \retval E_NOT_OK            Conditions are not ok
 **/
STATIC FUNC(boolean, DCM_CODE)Dcm_DspInternal_DidConditionChecksSecLevel
(
  uint8 instIdx,
  P2CONST(Dcm_DidAccessInfoType, AUTOMATIC, DCM_CONST) AccessInfo
);

#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
/** \brief Handles Endianness conversion of currently copying data based on datatype for the service
    ReadDataByIdentifier: 0x22, WriteDataByIdentifier: 0x2E and IOCOntrolByIdentifier: 0x2F
 **
 ** \param[inout] inBuffer Pointer to source buffer
 ** \param[in]    holds dataType of signal being processed
 **
 **/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_Endianness_Conversion(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) inBuffer,
  Dcm_DidDataByteType dataType);
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */
#endif /* #if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
/** \brief Handles Reading of signals in a Did for the service ReadDataByIdentifier: 0x22
 **
 ** \param[in] DidIndex Index of the Did in the table Dcm_DidTable
 ** \param[in] instIdx Current HSM instance Id
 ** \param[in] OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK                Readig is ok
 ** \retval E_NOT_OK            Reading is not ok
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid(
  uint16 DidIndex,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Reads data of a signal mapped to a Did
 **
 ** \param[in] DidIndex Index of the Did in the table Dcm_DidTable
 ** \param[in] instIdx Current HSM instance Id
 ** \param[in] OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] nrc NRC occured due to condition checks.
 ** \param[in] didDataPosn Starting bit position of signal after the DID.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK                Reading is ok
 ** \retval E_NOT_OK            Reading is not ok
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid_Signal(
  uint16 DidIndex,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc,
  P2CONST(uint16, AUTOMATIC, AUTOMATIC) didDataPosn,
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Calls 'ConditionCheckRead' Async operations and handles return values
 **
 ** \param[in] dataCfg Configuration of the signal being processed
 ** \param[in] instIdx Current HSM instance Id
 ** \param[in] OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] nrc NRC reported during condition checks.
 **
 ** \retval E_OK                'ConditionCheckRead' is ok
 ** \retval E_NOT_OK            'ConditionCheckRead' is not ok
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid_ConditionCheckAsync(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc);

/** \brief Calls 'ConditionCheckRead' Sync operations and handles return values
 **
 ** \param[in] dataCfg Configuration of the signal being processed
 ** \param[in] instIdx Current HSM instance Id
 ** \param[inout] nrc NRC reported during condition checks.
 **
 ** \retval E_OK                'ConditionCheckRead' is ok
 ** \retval E_NOT_OK            'ConditionCheckRead' is not ok
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid_ConditionCheckSync(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint8 instIdx,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc);

/** \brief Reads data length of a signal mapped to a Did
 **
 ** \param[in] DidIndex Index of the Did in the table Dcm_DidTable
 ** \param[in] instIdx Current HSM instance Id
 ** \param[inout] nrc NRC occured due to condition checks.
 ** \param[in] didDataPosn Starting bit position of signal after the DID.
 ** \param[inout] preadSignalLength Maximum length of the signal to read.
 **
 ** \retval E_OK                Reading is ok
 ** \retval E_NOT_OK            Reading is not ok
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidSignalDataLength
(
  uint16 DidIndex,
  uint8 instIdx,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) preadSignalLength
);
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
/** \brief Handles reading a signalLength or didDataPosn if Endianness Conversion is enabled for
    the service ReadDataByIdentifier: 0x22 and IOControlByIdentifier: 0x2F
 **
 ** \param[inout] dataConfig the Current signal Data in the table Dcm_DidDataTable[]
 ** \param[in]    dataPosition bit-position of signal data in request buffer
 ** \boolean      select selects signalLength or dataPosition
 **
 **/
STATIC FUNC(uint16, DCM_CODE) Dcm_DspInternal_SignalLengthOrDataPosition(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataConfig,
  uint16 dataPosition,
  boolean select);
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON)*/

#endif /* #if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if(DCM_DSP_USE_SERVICE_0X22 == STD_ON)
/** \brief UDS service 0x22
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDataByIdentifier_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Internal function to set the status of Did signals.  This function is called from
 **  Dcm_DspInternal_ReadDataByIdentifier_SvcStart()
 **
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 ** \param[in]    reqDid requested DID from request buffer
 ** \param[in]    instIdx Current HSM instance Id.
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReqDidSetStatus(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 reqDid, uint8 instIdx);

#if (DCM_DID_REF_COUNT > 0)
/** \brief Internal function to set the status of Did signals, when reading referenced DIDs.
 **  This function is called from Dcm_DspInternal_ReadDataByIdentifier_SvcStart()
 **
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 ** \param[in]    refDid referenced DID from the reference table
 ** \param[in]    instIdx Current HSM instance Id.
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RefDidSetStatus(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 refDid, uint8 instIdx);
#endif /* #if (DCM_DID_REF_COUNT > 0) */
#endif /* #if(DCM_DSP_USE_SERVICE_0X22 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)

/** \brief Validates the UDS service 0x2F request received
 **
 ** \param[in] opState Status of the service processing
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlByIdentifier_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x2F internal service handler
 **
 ** \param[in] opState Status of the service processing
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlByIdentifier_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Gets the status whether the 'ControlMask' is enabled for the current signal
 **
 ** \param[inout] reqData Pointer to the 'ControlMask'.
 ** \param[inout] pIOControlDIDContext holds the context information of currently processed DID.
 ** \param[in] numSignals Holds number of signals configured for DID.
 **
 ** \retval TRUE     Signal value shall be controlled
 ** \retval FALSE    Signal value should not be controlled
 **/
STATIC FUNC(boolean, DCM_CODE) Dcm_DspInternal_IOControl_CheckControlMask(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) reqData,
  P2CONST(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext,
  uint16 numSignals);

/** \brief The function for checking the request data length of IOControl request
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlDidRequestLengthChk(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x2F 'returnControlToEcu' handler to request to application
 **          to return control to ECU
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] instIdx Current HSM instance Id.
 ** \param[in] opState Status of the service processing
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOReturnControlToECU_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus);

/** \brief UDS service 0x2F 'resetToDefault' handler to request to application
 **          to reset an IOControl to default value
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] instIdx Current HSM instance Id.
 ** \param[in] opState Status of the service processing.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOResetToDefault_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus);

/** \brief UDS service 0x2F 'FreezeCurrentState' handler to request to application
 **          to freeze the current state of an IOControl
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] instIdx Current HSM instance Id.
 ** \param[in] opState Status of the service processing.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOFreezeCurrentState_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus);

/** \brief UDS service 0x2F 'ShortTermAdjustment' handler to request to application
 **         to adjust the IO signal
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] instIdx Current HSM instance Id.
 ** \param[in] opState Status of the service processing.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOShortTermAdjustment_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus);

/** \brief Copies the data of currently processed signal to signalBuffer
 **
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] dataCfg holds the configuration of signal being processed.
 ** \param[in] didDataPosition Position in bits of the DID data.
 ** \param[out] signalBuffer Status of the service processing.
 ** \param[in] instIdx Current HSM instance Id.
 **
 **/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_SignalDataCopying(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint16 didDataPosition,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint8 instIdx);

/** \brief Reads the signal data
 **
 ** \param[in] OpStatus Status of the service processing
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[in] instIdx Current HSM instance Id.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControl_ReadSignals(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx);

/** \brief Validates the return values of 'IOControl' interface calls
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[inout] pIOControlDIDContext holds the context information of currently processed DID.
 ** \param[in] dataCfg holds the configuration of signal being processed.
 ** \param[in] nrc NRC occured during condition checks.
 ** \param[in] interfaceRetVal holds interface function return value.
 ** \param[in] interfaceID holds interface ID value
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControl_InterfaceRetValCheck(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext,
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint8 nrc, uint8 interfaceRetVal, uint8 interfaceID);

#endif /* #if(DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X2E == STD_ON)
/** \brief The function for implementation of UDS service 0x2E
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDataByIdentifier_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief The function for checking the request data length of WriteDid request
 **
 ** \param[in] didIndex Index in the Did configuration table.
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 ** \retval DCM_E_PENDING Operation not completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidRequestLengthChk(
  uint16 didIndex,
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief The function for writing DID signal data
 **
 ** \param[in] DidIndex Index in the Did configuration table.
 ** \param[in] instIdx  Instance id of the currently processed request.
 ** \param[in] OpStatus Operation status of Dcm.
 ** \param[in] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 ** \retval DCM_E_PENDING Operation not completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDid(
  uint16 DidIndex,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief The function for writing a signal data
 **
 ** \param[in] dataIndex Index of the Did data configuration table.
 ** \param[in] writeSignalBuffer buffer for temporarily holding the signgal data.
 ** \param[in] signalLength Input signal data length.
 ** \param[in] instIdx  Instance id of the currently processed request.
 ** \param[in] OpStatus Operation status of Dcm.
 ** \param[in] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 ** \retval DCM_E_PENDING Operation not completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidSignal(
  uint16 dataIndex,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) writeSignalBuffer,
  uint16 signalLength,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if (DCM_INCLUDE_RTE == STD_ON)
/** \brief The function for writing a signal data via RTE asynchronous interface
 **
 ** \param[in] dataCfg        Configuration of signal being processed
 ** \param[in] signalBuffer   Holds the signal data.
 ** \param[in] signalLength   Signal length
 ** \param[in] OpStatus       Operation status of Dcm.
 ** \param[in] nrc
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 ** \retval DCM_E_PENDING Operation not completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidAsyncClientServer
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
);
/** \brief The function for writing a signal data via RTE synchronous interface
 **
 ** \param[in] dataCfg        Configuration of signal being processed
 ** \param[in] signalBuffer   Holds the signal data.
 ** \param[in] signalLength   Signal length
 ** \param[in] nrc
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 ** \retval DCM_E_PENDING Operation not completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidSyncClientServer
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
);
#endif
/** \brief The function for writing data via user functions(Synchronous)
 **
 ** \param[in] dataCfg        Configuration of signal being processed
 ** \param[in] signalBuffer   Holds the signal data.
 ** \param[in] signalLength   Signal length
 ** \param[in] nrc
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 ** \retval DCM_E_PENDING Operation not completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidSyncFunc
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
);

/** \brief The function for writing data via user functions(Asynchronous)
 **
 ** \param[in] dataCfg        Configuration of signal being processed
 ** \param[in] signalBuffer   Holds the signal data.
 ** \param[in] signalLength   Signal length.
 ** \param[in] OpStatus       Operation status of Dcm.
 ** \param[in] nrc
 **
 ** \retval E_OK      Operation completed successfully
 ** \retval E_NOT_OK  Operation completed with errors
 ** \retval DCM_E_PENDING Operation not completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidAsyncFunc
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
);

#if(DCM_WRITE_DID_BLOCK_ID_CONFIGURED == STD_ON)
/** \brief The function for writing data to NVM block
 **
 ** \param[in] instIdx TxPdu instance for which Nvm data should be written
 ** \param[in] OpStatus Operation status of Dcm.
 ** \param[in] didDataCfg Configuration information related to NVM data
 ** \param[out] signalBuffer Buffer containing the data to be written
 **
 ** \retval E_OK                Write is ok
 ** \retval E_NOT_OK            Write is not ok
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteNvmData(
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DidDataType, AUTOMATIC, DCM_CONST) didDataCfg,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) signalBuffer);
#endif /* #if(DCM_WRITE_DID_BLOCK_ID_CONFIGURED == STD_ON) */
#endif /* #if(DCM_DSP_USE_SERVICE_0X2E == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X31 == STD_ON)
/** \brief Validates the UDS service 0x31 request received
 **
 ** \param[in] OpStatus Status of the service processing
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RoutineControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x31 internal service handler
 **
 ** \param[in] OpStatus Status of the service processing
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RoutineControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_DSP_USE_SERVICE_0X31 == STD_ON) */

#if(DCM_0X34_SVC_ENABLED == STD_ON)
/** \brief UDS service 0x34
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestDownload_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x34
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestDownload_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_0X34_SVC_ENABLED == STD_ON) */

#if(DCM_0X35_SVC_ENABLED == STD_ON)
/** \brief UDS service 0x35
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestUpload_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x35
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestUpload_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_0X35_SVC_ENABLED == STD_ON) */

#if(DCM_0X36_SVC_ENABLED == STD_ON)
/** \brief UDS service 0x36
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransferData_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x36
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, It must be called again. */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransferData_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief For handling Download operation in the service 0x36
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[inout] pTranContext Context information for transfer service.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DownloadTransferData(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pTranContext,
  Dcm_OpStatusType OpStatus);

/** \brief For handling Upload operation in the service 0x36
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 ** \param[inout] pTranContext Context information for transfer service.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_UploadTransferData(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pTranContext,
  Dcm_OpStatusType OpStatus);

#endif /* #if(DCM_0X36_SVC_ENABLED == STD_ON) */

#if(DCM_0X37_SVC_ENABLED == STD_ON)

/** \brief UDS service 0x37
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestTransferExit_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x37 internal service handler
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestTransferExit_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_0X37_SVC_ENABLED == STD_ON) */

#if(DCM_0X28_SVC_ENABLED == STD_ON)
/** \brief UDS service 0x28 internal service handler
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CommunicationControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x28 internal service handler
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CommunicationControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if (((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) && \
     ((DCM_0X28_0X00_SSVC_ENABLED == STD_ON) || \
      (DCM_0X28_0X01_SSVC_ENABLED == STD_ON) || \
      (DCM_0X28_0X02_SSVC_ENABLED == STD_ON) || \
      (DCM_0X28_0X03_SSVC_ENABLED == STD_ON )))

/** \brief Internal handler to set communication mode
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval E_OK         Operation completed
 ** \retval E_NOT_OK     Configured subnetNumber values do not match the requested value
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SetCommunicationMode(
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if (((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) && \
                ((DCM_0X28_0X00_SSVC_ENABLED == STD_ON) || \
                 (DCM_0X28_0X01_SSVC_ENABLED == STD_ON) || \
                 (DCM_0X28_0X02_SSVC_ENABLED == STD_ON) || \
                 (DCM_0X28_0X03_SSVC_ENABLED == STD_ON ))) */

#endif /* #if(DCM_0X28_SVC_ENABLED == STD_ON) */

#if(DCM_0X87_SVC_ENABLED == STD_ON)
/** \brief UDS service 0x87
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_LinkControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x87
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, It must be called again. */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_LinkControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if((DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON) || \
    (DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON) || \
    (DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON))
/** \brief UDS Subservice function for service 0x87
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[in]    BaudrateRecord Pointer to the array which holds the baudrate
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, It must be called again. */

STATIC FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_DspInternal_LinkControl_Execution(
  Dcm_OpStatusType  OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR)  baudrateRecord,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if((DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON) || \
              (DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON) || \
              (DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON)) */

#endif /* #if(DCM_0X87_SVC_ENABLED == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X86 == STD_ON)
/** \brief UDS service 0x86
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ResponseOnEvent_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x86
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ResponseOnEvent_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 == STD_ON)
/** \brief UDS service 0x86-0x05
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StartROE_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 == STD_ON)
/** \brief UDS service 0x86-0x00
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StopROE_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 == STD_ON)
/** \brief UDS service 0x86-0x06
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearROE_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 == STD_ON)
/** \brief UDS service 0x86-0x01
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnDTCStatusChange_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 == STD_ON)
/** \brief UDS service 0x86-0x03
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnChangeOfDataIdentifier_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03)*/

#if (DCM_ROE_PERSISTENCE == STD_ON)
/** \brief Operation for handling write operation of ROE data
 **
 ** \retval E_OK                Operation Success
 ** \retval E_NOT_OK            Operation Failed
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE)Dcm_DspInternal_ROEWriteToNvM(void);
#endif

#endif /* #if(DCM_DSP_USE_SERVICE_0X86 == STD_ON) */

#if (DCM_READ_DID_BLOCK_ID_CONFIGURED == STD_ON)
/** \brief The function for reading data from NVM block
 **
 ** \param[in] OpStatus Operation state for internal Dcm Service function.
 ** \param[in] didDataCfg Configuration information related to NVM data
 ** \param[inout] didNvmReadDataSt Information related to NVM Read Data state
 ** \param[out] signalBuffer Buffer for updating the read data
 **
 ** \retval E_OK                Reading is ok
 ** \retval E_NOT_OK            Reading is not ok
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadNvmData(
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DidDataType, AUTOMATIC, DCM_CONST) didDataCfg,
  P2VAR(Dcm_DidAsynchSignalStType, AUTOMATIC, DCM_VAR) didNvmReadDataSt,
  P2VAR(NvM_RequestResultType, AUTOMATIC, DCM_VAR) result,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) signalBuffer);
#endif /* #if (DCM_READ_DID_BLOCK_ID_CONFIGURED == STD_ON) */

#if(DCM_0X85_SVC_ENABLED == STD_ON)
/** \brief UDS service 0x85 internal service handler
 **
 ** \param[inout] pMsgContext Message related information for one diagnostic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ControlDTCSetting_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief UDS service 0x85 internal service handler
 **
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete
 **/

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ControlDTCSetting_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_0X85_SVC_ENABLED == STD_ON) */

#if (((DCM_0X23_SVC_ENABLED == STD_ON) || \
     (DCM_0X34_SVC_ENABLED == STD_ON) || \
     (DCM_0X35_SVC_ENABLED == STD_ON) || \
     (DCM_0X3D_SVC_ENABLED == STD_ON )) && \
     (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON))

/** \brief Handles verification of AddressLengthIdentifier in the request.
 **
 ** \param[in]    AddressLengthIdentifier holds number of bytes occupied by memoryAddress[]
 **               and memorySize[] in the request
 **
 ** \retval E_OK                Operation Success
 ** \retval E_NOT_OK            Operation Failed
 **
 **/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_AddressLengthAndFormat_Verification(
  uint8 AddressLengthIdentifier);

#endif /* #if (((DCM_0X23_SVC_ENABLED == STD_ON) || \
               (DCM_0X34_SVC_ENABLED == STD_ON) || \
               (DCM_0X35_SVC_ENABLED == STD_ON) || \
               (DCM_0X3D_SVC_ENABLED == STD_ON )) && \
               (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON)) */

#if (DCM_ROE_ENABLED == STD_ON)
STATIC FUNC(boolean, DCM_CODE) Dcm_PostponeROEFromPollingDIDData (uint16  didIndex);
STATIC FUNC(void, DCM_CODE) Dcm_AllowROEToPollDIDData (void);
#endif

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*=======================[external data declarations]============================================*/

#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)

VAR(Dcm_SignalBufferContextType, DCM_VAR) Dcm_SignalBufferContext;

#endif /* #if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
#define DCM_START_SEC_VAR_INIT_8
#include <MemMap.h>

VAR(boolean, DCM_VAR) Dcm_CancelPagedProcessing = FALSE;

#define DCM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/*=======================[internal data declarations]============================================*/

#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if(DCM_DSP_USE_SERVICE_0X19 == STD_ON)
#if (((DCM_PAGEDBUFFER_ENABLED == STD_ON) && \
      ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
      (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)  || \
      (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)  || \
      (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)))|| \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON))
/* Dcm_ReadDTCInfoContext is used to hold information regarding the processing of
 * the service ReadDTCInformation(0x19).
 */
/* Rationale for mapping Dcm_ReadDTCInfoContext to NOINIT section.
 *
 * Members of Dcm_ReadDTCInfoContext are initialized and accessed as described below:
 * ReqRecNum : Initialized in Dcm_DspInternal_ReportDtc<Functions> before being
 *             accessed from Dcm_DspInternal_ProcessPageDtc<Functions>.
 * DTCRecNum : Initialized in Dcm_DspInternal_ReportDtc<Functions> before being
 *             accessed from Dcm_DspInternal_ProcessPageDtc<Functions>.
 * DTCCount  : Initialized in Dcm_DspInternal_ReportDTCByStatusMask_SSvcH() before
 *             being accessed from the same function.
 */
STATIC VAR(Dcm_ReadDTCInfoContextType, DCM_VAR) Dcm_ReadDTCInfoContext[DCM_NUM_PROTOCOL];

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
/* Deviation MISRA-6 */
#define DCM_READ_DTC_INFO_CONTEXT(instIdx) Dcm_ReadDTCInfoContext[instIdx]
#else
#define DCM_READ_DTC_INFO_CONTEXT(instIdx) Dcm_ReadDTCInfoContext[0]
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */

#endif /* #if ((DCM_PAGEDBUFFER_ENABLED == STD_ON && \
              ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
              (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON) || \
              (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
              (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)))|| \
              (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)) */

#endif /* #if (DCM_DSP_USE_SERVICE_0X19 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X22 == STD_ON)

#if (DCM_COMMON_BUFF_CONFIGURED == STD_ON)
/* Dcm_ReadDIDBuffer is used to store the recieved Dids, if a single buffer is configured as Rx and
  Tx buffer. */
STATIC VAR(Dcm_MsgItemType, DCM_VAR) Dcm_ReadDIDBuffer[2U*DCM_READ_DID_MAX];
#endif /* #if(DCM_COMMON_BUFF_CONFIGURED == STD_ON) */

#endif /* #if(DCM_DSP_USE_SERVICE_0X22 == STD_ON) */

#if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
/** \brief Array to hold information regarding the processing of 0x22 Service. */
VAR(Dcm_ReadDIDContextType, DCM_VAR) Dcm_ReadDIDContext[DCM_NUM_PROTOCOL];

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
/* Deviation MISRA-6 */
#define DCM_READDIDCONTEXT(instIdx) Dcm_ReadDIDContext[instIdx]
#else
#define DCM_READDIDCONTEXT(instIdx) Dcm_ReadDIDContext[0]
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */

#endif /* #if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
          (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if(DCM_DSP_USE_SERVICE_0X2E == STD_ON)

/* Holds the context information of a WriteDid request */
/* Rationale for mapping Dcm_WriteDIDContext to NOINIT section.
 *
 * Members of Dcm_WriteDIDContextType are initialized and accessed as described below:
 * RequestProcessingSt : Initialized in Dcm_DspInternal_WriteDataByIdentifier_SvcH() before
 *                       being accessed from Dcm_DspInternal_WriteDataByIdentifier_SvcStart().
 * DidAsynchSignalSt : Initialized in Dcm_DspInternal_WriteDataByIdentifier_SvcStart() before
 *                     being accessed from Dcm_DspInternal_WriteDid().
 * SignalInd  : Initialized in Dcm_DspInternal_WriteDataByIdentifier_SvcStart() before being
 *              accessed from the Dcm_DspInternal_WriteDid().
 */
STATIC VAR(Dcm_WriteDIDContextType, DCM_VAR) Dcm_WriteDIDContext[DCM_NUM_PROTOCOL];

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
/* Deviation MISRA-6 */
#define DCM_WRITE_DID_CONTEXT(instIdx) Dcm_WriteDIDContext[instIdx]
#else
#define DCM_WRITE_DID_CONTEXT(instIdx) Dcm_WriteDIDContext[0]
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */

#endif /* #if(DCM_DSP_USE_SERVICE_0X2E == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)

/* Holds the context information of a IOControl request */
/* Rationale for mapping Dcm_IOControlDIDContext to NOINIT section.
 *
 * Members of Dcm_IOControlDIDContextType are initialized and accessed as described below:
 * RequestProcessingSt : Initialized in Dcm_DspInternal_InputOutputControlByIdentifier_SvcH() before
 *                       being accessed from Dcm_DspInternal_IOControlByIdentifier_SvcStart().
 * SignalInd  : Initialized in Dcm_DspInternal_IOControlByIdentifier_SvcStart() before being
 *              accessed from the Dcm_DspInternal_IOShortTermAdjustment_Data().
 */
STATIC VAR(Dcm_IOControlDIDContextType, DCM_VAR) Dcm_IOControlDIDContext[DCM_NUM_PROTOCOL];

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
/* Deviation MISRA-6 */
#define DCM_IO_CONTROL_DID_CONTEXT(instIdx) Dcm_IOControlDIDContext[instIdx]
#else
#define DCM_IO_CONTROL_DID_CONTEXT(instIdx) Dcm_IOControlDIDContext[0]
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */

#endif /* #if(DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X86 == STD_ON)
/* Dcm_RoeTempBuffer is used to temporarily store the request data of maximum possible size */
STATIC VAR(Dcm_MsgItemType, DCM_VAR) Dcm_RoeTempBuffer[10];
#endif /* #if(DCM_DSP_USE_SERVICE_0X86 == STD_ON) */

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if (DCM_ROE_ENABLED == STD_ON)
#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/* Array for blocking parallel signal access for DIDs by asynchronous service */
STATIC VAR(uint8, DCM_VAR) RoeDidBlockFlags[DCM_DID_BLOCK_MASK_NUM];

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>
#endif /* #if (DCM_ROE_ENABLED == STD_ON) */

/* If at least one routine is configured */
#if (DCM_NUM_ROUTINES > 0U)

#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Global array holding the status information of each routines **/
VAR(uint8, DCM_CONST) Dcm_DspRoutineStatus[DCM_NUM_ROUTINES];

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#endif /* #if (DCM_NUM_ROUTINES > 0U) */

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief State machine instance in the context of which the service request is processed
 ** asynchronously **/
STATIC VAR(uint8, DCM_VAR) Dcm_InstanceIndex;

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#endif /* #if (DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

#if(DCM_0X34_SVC_ENABLED == STD_ON) || \
   (DCM_0X35_SVC_ENABLED == STD_ON) || \
   (DCM_0X36_SVC_ENABLED == STD_ON) || \
   (DCM_0X37_SVC_ENABLED == STD_ON)

#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/* Dcm_DataTransferContext is used to hold information regarding the processing of
 * the service RequestDownload(0x34),RequestUpload(0x35).*/
VAR(Dcm_DataTransferType, DCM_VAR) Dcm_DataTransferContext[DCM_NUM_PROTOCOL];

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
/* Deviation MISRA-6 */
#define DCM_DATA_TRANSFER_CONTEXT(instIdx) Dcm_DataTransferContext[instIdx]
#else
#define DCM_DATA_TRANSFER_CONTEXT(instIdx) Dcm_DataTransferContext[0]
#endif /* #if (DCM_HSM_INST_MULTI_ENABLED == STD_ON) */

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#endif

#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
/** \brief Dcm_ReturnControlToEcuContext is used to hold information regarding the processing of
 * returning control to ECU for signals */
VAR(Dcm_IOReturnControlToEcuStatusType, DCM_VAR) Dcm_ReturnControlToEcuContext;
#endif

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#if(DCM_0X87_SVC_ENABLED == STD_ON)
#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Global variable holding the status information of LinkControl service Request Status **/
VAR(boolean, DCM_VAR) Dcm_DspLinkControlRequestStatus;

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#endif

#if(DCM_0X3D_SVC_ENABLED == STD_ON)
#define DCM_START_SEC_VAR_INIT_8
#include <MemMap.h>

/** \brief Global variable holding the length (number of bytes) of the memoryAddress parameter **/
VAR(uint8, DCM_VAR) writeMemAddLength = 0U;

/** \brief Global variable holding the length (number of bytes) of the memorySize parameter **/
VAR(uint8, DCM_VAR) writeMemSizeLength = 0U;

#define DCM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>
#endif  /* #if(DCM_0X3D_SVC_ENABLED == STD_ON) */

#define DCM_START_SEC_VAR_INIT_16
#include <MemMap.h>

/** \brief Global variable holding the index of the currently processed DID in the
 ** configuration array **/
VAR(uint16, DCM_VAR) readDidIndex = 0U;

#if (DCM_DID_REF_COUNT > 0)
/** \brief Global variable holding the index of the currently processed referenced
 ** DID in the configuration array **/
VAR(uint16, DCM_VAR) refDidIndex = 0U;
#endif

/** \brief Global variable holding the index of the currently processed DID
           in the configuration array **/
VAR(uint16, DCM_VAR) writeDidIndex = 0U;

/** \brief Global variable holding the length of the signal in bits **/
VAR(uint16, DCM_VAR) readSignalLength = 0U;

#define DCM_STOP_SEC_VAR_INIT_16
#include <MemMap.h>

#if(DCM_0X23_SVC_ENABLED == STD_ON)
#define DCM_START_SEC_VAR_INIT_32
#include <MemMap.h>

/** \brief Global variable holding the size of the memory (number of bytes) to be read **/
VAR(uint32, DCM_VAR) Dcm_ReadMemorySize = 0U;

#define DCM_STOP_SEC_VAR_INIT_32
#include <MemMap.h>
#endif  /* #if(DCM_0X23_SVC_ENABLED == STD_ON) */

#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Global variable holding the global NRC for the currently processed read DID request **/
VAR(Dcm_NegativeResponseCodeType, DCM_VAR) nrcCondtions = 0U;

#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[external function definitions]==============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

FUNC(void, DCM_CODE) Dcm_DspInternal_SvcFunc(
  uint8 instIdx,
  Dcm_OpStatusType  OpStatus)
{
  Std_ReturnType retVal = DCM_E_ABORT;

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get pointer to current message context */
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) curMsgContext = &curHsmInfo->msgContext;

  DBG_DCM_DSPINTERNAL_SVCFUNC_ENTRY(DCM_INST(instIdx),OpStatus);

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
  {
    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    curHsmInfo->asyncServiceOpState = OpStatus;

    Dcm_InstanceIndex = instIdx;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* Trigger asynchronous service. */
    Dcm_TriggerServiceAsync();
  }
  else
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
  {
    /* depending on the configuration, an internal or user provided service handler
     * function will be called */
    if ((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).IntSrvHandler != NULL_PTR)
    {
      /* Call internal service function */
      retVal = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).IntSrvHandler(OpStatus,
                                                                                  curMsgContext);
      if (OpStatus == DCM_CANCEL)
      {
        retVal = DCM_E_DONE;
      }
    }
    else
    {
      if ((OpStatus == DCM_FORCE_RCRRP_OK) || (OpStatus == DCM_PENDING))
      {
        /* invoke the configured user function with 'OpStatus' DCM_PENDING [Dcm738] */
        retVal = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).ExtSrvHandler(DCM_PENDING,
                                                                                    curMsgContext);
      }
      else
      {
        /* invoke the configured user function */
        retVal = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).ExtSrvHandler(OpStatus,
                                                                                    curMsgContext);
      }
    }

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(instIdx);
#endif

    switch( retVal )
    {
      case DCM_E_FORCE_RCRRP:
        /* tigger sending of immediate rep pending */
        (void) DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_FORCE_RCRRP);
        break;

      case DCM_E_PENDING:
        /* try again after timeout */
        DCM_HSM_INFO(instIdx).retryTimer = 1U;
        break;

      case DCM_E_PROCESS_PAGE:
        /* do nothing, wait for event UPDATE_PAGE and subsequent service function call with
         * OpStatus == UPDATE_PAGE or OpStatus == CONFIRMED */
        /* DsdInternal_ProcessPage() must have been called within the service function */
        break;

      case DCM_E_ABORT:
        (void) DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                       DCM_HSM_DCM_EV_PROC_ABORT);
        break;

      case E_OK:
        break;

      case DCM_E_DONE:
      default:
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if ((TRUE == Dcm_CancelPagedProcessing) &&
            (DCM_CANCEL == OpStatus))
        {
          /* This is a paged-buffered cancellation, we need to wait until
             the TP layer ends transmission by a call to Dcm_TpTxConfirmation(), in case
             of an unsuppressed transmission or the transmission will be immediately
             ended for a suppressed transmission. When this finally does happen, the
             asynchronous service processor shall be unblocked with the DCM_CONFIRMED_NOK
             OpStatus, resulting in processing being terminated. We therefore do not emit
             an extra DONE state machine event. */
        }
        else
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
        {
          /* a regular cancellation shall not wait for the TP layer to end transmission
             as it has not actually begun to send any data, therefore this state machine
             event needs to be emitted here */
          (void) DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROC_DONE);
        }

        break;
    }
  }

  DBG_DCM_DSPINTERNAL_SVCFUNC_EXIT(DCM_INST(instIdx),OpStatus);
}

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)

FUNC(void, DCM_CODE)  Dcm_ProcessServiceAsync(void)
{
  uint8 instIdx;
  boolean externalServiceCancellation = FALSE;

  Std_ReturnType retVal = DCM_E_ABORT;

  /* configuration of current service table */
  P2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig;

  Dcm_OpStatusType localOpStatus;

  /* context information of the current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo;

  /* pointer to current message context */
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) curMsgContext;

  DBG_DCM_INTERNAL_PROCESSSERVICEASYNC_ENTRY();

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  instIdx = Dcm_InstanceIndex;

  /* get the context information current instance */
  curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* fetch the curHsmInfo->asyncServiceOpState variable into a local copy to
   * prevent threading issues
   */
  localOpStatus = curHsmInfo->asyncServiceOpState;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  curSidTabConfig = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get pointer to current message context */
  curMsgContext = &curHsmInfo->msgContext;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized == FALSE)
  {
    DCM_DET_REPORT_ERROR(DCM_SVCID_PROCESSSERVICEASYNC, DCM_E_UNINIT);
    retVal = E_NOT_OK;
  }
  else
#endif
  {
    while(localOpStatus != DCM_ASYNC_PROCESSING_DONE)
    {
      if (localOpStatus != DCM_ASYNC_PROCESSING_WAIT)
      {
        Dcm_OpStatusType newOpStatus = DCM_OPSTATUS_INVALID;
        Dcm_HsmEventType event = DCM_HSM_DCM_EV_INVALID;
        boolean processingComplete = FALSE;

        /* depending on the configuration, an internal or user provided service handler
         * function will be called
         */
        if ((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).IntSrvHandler != NULL_PTR)
        {
          /* Call internal service function */
          retVal = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).IntSrvHandler(
            localOpStatus, curMsgContext);

          if (localOpStatus == DCM_CANCEL)
          {
            retVal = DCM_E_DONE;
          }
        }
        else
        {
          /* For external service handlers operation status
             DCM_FORCE_RCRRP_OK is not valid */
          if ((localOpStatus == DCM_FORCE_RCRRP_OK) ||
              (localOpStatus == DCM_PENDING))
          {
              localOpStatus = DCM_PENDING;
          }

          /* Don't call external service handlers if the transmission of the
             response has been confirmed */
          if ((localOpStatus != DCM_CONFIRMED_OK) &&
              (localOpStatus != DCM_CONFIRMED_NOK))
          {
              /* Call external service function */
              retVal = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).ExtSrvHandler(
              localOpStatus, curMsgContext);
          }

          /* in case of cancellation stop processing immediately */
          if (localOpStatus == DCM_CANCEL)
          {
            retVal = DCM_E_DONE;
            /* since this service handler is external, the final PROC_DONE event shall be
               emitted from the service handler itself, therefore we don't need to emit it
               here */
            externalServiceCancellation = TRUE;
          }
        }

        /* determine new operation status according to return value of service
           handler function */
        switch (retVal)
        {
          case DCM_E_FORCE_RCRRP:
            /* trigger sending of immediate resp pending */
            event = DCM_HSM_DCM_EV_FORCE_RCRRP;
            newOpStatus = DCM_FORCE_RCRRP_OK;
            break;

          case DCM_E_PENDING:
            /* call the service handler function again */
            newOpStatus = DCM_PENDING;
            break;

          case DCM_E_PROCESS_PAGE:
            /* do nothing, wait for event UPDATE_PAGE and subsequent setting of the
             * asyncServiceOpState DCM_UPDATE_PAGE so the service handler may be called once more.
             * DsdInternal_ProcessPage() must have been called within the service function
             * And update the global OpStatus variable
             */
            break;

          case DCM_E_ABORT:
            /* Immediately terminate all processing */
            event = DCM_HSM_DCM_EV_PROC_ABORT;
            newOpStatus = DCM_ASYNC_PROCESSING_DONE;

            break;

          case DCM_E_OK:
            /* Processing of service is finished for now, wait until
             * there is more to do (e.g. after the response has been sent)
             */
            newOpStatus = DCM_ASYNC_PROCESSING_WAIT;

              /* If the opStatus is DCM_CANCEL in the Dcm main task, we will not wait
               * for any further processing to complete, since processing has been
               * cancelled already. Therefore, we don't set the 'processingComplete' flag.*/
            break;

          case DCM_E_DONE:
            /* Service handling for internal services is different, i.e there
             * is an additional call to the service handler for transmitting
             * the negative or positive confirmation that the response has
             * been sent.
             */
            if ((localOpStatus == DCM_CONFIRMED_OK) ||
                (localOpStatus == DCM_CONFIRMED_NOK) ||
                (localOpStatus == DCM_CANCEL))
            {
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
              if ((TRUE == Dcm_CancelPagedProcessing) &&
                  (DCM_CANCEL == localOpStatus))

              {
                /* This is a paged-buffered cancellation, we need to wait until
                   the TP layer ends transmission by a call to Dcm_TpTxConfirmation(). When
                   this finally does happen, the asynchronous service processor shall be
                   unblocked with the DCM_CONFIRMED_NOK OpStatus, resulting in processing
                   being terminated. */
                localOpStatus = DCM_ASYNC_PROCESSING_WAIT;
              }
              else
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
              {
                /* a regular cancellation shall not wait for the TP layer to end transmission
                   as it has not actually begun to send any data, therefore this state machine
                   event needs to be emitted here */

                newOpStatus = DCM_ASYNC_PROCESSING_DONE;

                /* There is no risk of a timeout happening here since this is the final
                 * execution of the service handler
                 */
                processingComplete = TRUE;
              }
            }
            else
            {
              newOpStatus = DCM_ASYNC_PROCESSING_WAIT;

              /* If the opStatus is DCM_CANCEL in the Dcm main task, we will not emit
               * the PROC_DONE event anymore since service processing has been cancelled already.
               * Therefore, we don't set the 'processingComplete' flag.
               */
              event = DCM_HSM_DCM_EV_PROC_DONE;
            }
            break;

          default:
            newOpStatus = DCM_ASYNC_PROCESSING_WAIT;

            /* If the opStatus is DCM_CANCEL in the Dcm main task, we will not emit
             * the PROC_DONE event anymore since service processing has been cancelled already.
             * Therefore, we don't set the 'processingComplete' flag.
             */
            event = DCM_HSM_DCM_EV_PROC_DONE;
            break;
        }

        /* ENTER critical section */
        SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

        /* In case processing was already cancelled, don't emit any state machine events
         * as this means that they would ultimately be ignored */
        if ((event != DCM_HSM_DCM_EV_INVALID)  &&
            (curHsmInfo->asyncServiceOpState != DCM_CANCEL))
        {
          (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),event);
        }

        /* In case processing was already cancelled, don't change the opStatus, but allow
         * cancellation to proceed. Only change it to DCM_ASYNC_PROCESSING_DONE in case
         * of the final call to the service handler in order to cancel processing (a call
         * with an opStatus of DCM_CANCEL)
         */
        if ((newOpStatus != DCM_OPSTATUS_INVALID) &&
            ((curHsmInfo->asyncServiceOpState != DCM_CANCEL) ||
             (processingComplete)) &&
            (curHsmInfo->asyncServiceOpState != DCM_ASYNC_PROCESSING_DONE))
        {
          curHsmInfo->asyncServiceOpState = newOpStatus;
        }

        /* LEAVE critical section */
        SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
      }

      TS_AtomicAssign8(localOpStatus,curHsmInfo->asyncServiceOpState);
    }
  }

  /* Emit PROC_DONE event from here as task has been terminated either with CONFIRMING_OK or
   * CONFIRMING_NOK or DCM_CANCEL
   */

  /* Do not set DCM_HSM_DCM_EV_PROC_DONE if the service is external and opStatus is DCM_CANCEL */
  /* Deviation MISRA-2 */
  if ((localOpStatus == DCM_ASYNC_PROCESSING_DONE) &&
      (retVal != DCM_E_ABORT) && (FALSE == externalServiceCancellation))
  {
    (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                  DCM_HSM_DCM_EV_PROC_DONE);
  }

  DBG_DCM_INTERNAL_PROCESSSERVICEASYNC_EXIT();
}

STATIC FUNC(void, DCM_CODE) Dcm_TriggerServiceAsync(void)
{
  DBG_DCM_INTERNAL_TRIGGERPROCESSSERVICEASYNC_ENTRY();
  SchM_ActMainFunction_Dcm_Dcm_InternalTriggerServiceAsync();
  DBG_DCM_INTERNAL_TRIGGERPROCESSSERVICEASYNC_EXIT();
}
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

/*==================[Service and Sub-Service Handler definitions]=================================*/

#if(DCM_DSP_USE_SERVICE_0X10 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
  /* indicates whether the requested session is a boot session */
  boolean isBootSession = FALSE;

  uint8_least i;
  uint8 sesTabIdxNew = 0U;
#endif

  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig = &DCM_SES_TAB_CONFIG(instIdx);
#endif

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:

#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
      curHsmInfo->confirmedResetMode = DCM_NO_RESET;
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

      curHsmInfo->jumpToBLInhibited = FALSE;

#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
      /* get requested session index in current protocol session table */
      for (i = 0U; i < sesTabConfig->NumEntries; ++i)
      {
        if ((sesTabConfig->SessionEntries[i]).SesCtrl == curHsmInfo->newSesCtrl)
        {
          sesTabIdxNew = (uint8)i;
          break;
        }
      }

      if ((sesTabConfig->SessionEntries[sesTabIdxNew].SessionForBoot == DCM_OEM_BOOT ) ||
          (sesTabConfig->SessionEntries[sesTabIdxNew].SessionForBoot == DCM_SYS_BOOT))
      {
        isBootSession = TRUE;
      }

      if ((isBootSession == TRUE) && (Dcm_InhibitJmpToBL == TRUE))
      {
        serviceProcessStatus = DCM_E_PENDING;

        curHsmInfo->jumpToBLInhibited = TRUE;
      }
      else
#endif
      {
        curHsmInfo->jumpToBLSupport = FALSE;
        curHsmInfo->jumpToBLExecution = DCM_PREPARE_JUMP;

        serviceProcessStatus = Dcm_DspInternal_DiagnosticSessionControl_SvcStart(pMsgContext);

        curHsmInfo->jumpToBLInhibited = FALSE;
      }

      break;

      /* If _SvcStart() has returned PENDING before
          or _SvcStart() call was inhibited by a still pending SetProgConditions() call */
    case DCM_PENDING:

#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
      /* if _SvcStart() call was inhibited by a still pending SetProgConditions() call */
      if (curHsmInfo->jumpToBLInhibited == TRUE)
      {
        /* if the previous SetProgConditions() call is still pending */
        if (Dcm_InhibitJmpToBL == TRUE)
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          /* the previous SetProgConditions() call has completed, call _SvcStart() */

          curHsmInfo->jumpToBLSupport = FALSE;
          curHsmInfo->jumpToBLExecution = DCM_PREPARE_JUMP;
          curHsmInfo->jumpToBLInhibited = FALSE;

          serviceProcessStatus = Dcm_DspInternal_DiagnosticSessionControl_SvcStart(pMsgContext);
        }
      }
      else
#endif
      {
        /* if bootloader support is not configured, service normal SessionControl request */
        if ( curHsmInfo->jumpToBLSupport != TRUE )
        {
          /* Session change request not yet accepted */
          serviceProcessStatus = Dcm_DspInternal_DiagnosticSessionControl_SvcCont(pMsgContext);
        }
#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
        else
        {
          /* Service the Jump to BL request */
          serviceProcessStatus = Dcm_DspInternal_JumpToBL(pMsgContext, OpStatus);
        }
#endif /* #if(DCM_JUMP_TO_BL_ENABLED == STD_ON) */
      }

      break;

    /* successful transmission of the response */
    case DCM_CONFIRMED_OK:

      /* if bootloader support is not configured, service normal SessionControl request */
      if ( curHsmInfo->jumpToBLSupport != TRUE )
      {
        /* set session state of current HSM to requested session */
        Dcm_DspInternal_SetSessionState(instIdx);
#if (DCM_DSP_USE_SERVICE_0X2F == STD_ON)
        /* if requested session is default */
        if( (curHsmInfo->newSesCtrl == DCM_DEFAULT_SESSION) &&
            (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus != DCM_RET_CTRL_PENDING)
          )
        {
          /* Dcm628: On a session transition to default session (from non-default session), the
             DCM shall stop all the control in progress  */
          /* Because the state of the DIDs is undefined until control has been returned to ECU for
             all. So it is not required to invoke returnControlToECU interface for signals */
          /* Will be done via Dcm_MainFunction */
          Dcm_DspInternal_ReturnControlToEcuforallSignals();
        }
#endif
        serviceProcessStatus = DCM_E_DONE;
      }
#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
      else
      {
        /* Service the Jump to BL request */
        serviceProcessStatus = Dcm_DspInternal_JumpToBL(pMsgContext, OpStatus);
      }
#endif /* #if(DCM_JUMP_TO_BL_ENABLED == STD_ON) */
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      curHsmInfo->jumpToBLSupport = FALSE;
      curHsmInfo->jumpToBLInhibited = FALSE;
      curHsmInfo->jumpToBLExecution = DCM_PREPARE_JUMP;
      /* reset the request mode parameters */
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
      curHsmInfo->confirmedResetMode = DCM_NO_RESET;
      curHsmInfo->requestedResetMode = DCM_NO_RESET;
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

      break;
  }

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControl_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_INIT_ON_DSC == STD_ON))
  P2CONST(Dcm_DidServicesType, TYPEDEF, DCM_CONST) didCfg =
    &Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]];
  Std_ReturnType retVal;
#endif

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCSTART_ENTRY(pMsgContext);

#if ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_INIT_ON_DSC == STD_ON))
  /* Dcm597 : On Reception of 0x10 service, if ROE event is active and
   * DcmDspRoeInitOnDSC is set to TRUE, STOP ROE event
   */
  if((Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] ==
      DCM_ROE_EVENT_STARTED) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED))
  {
    /* Verify presence of DcmDspDidExtRoe for requested DID */
    if( didCfg->ExtRoeSupport == TRUE )
    {
      /* Invoke xxx_ActivateEvent with DCM_ROE_UNACTIVE */
      retVal = didCfg->RoeActivateFnc(didCfg->RoeEventId, DCM_ROE_UNACTIVE);
      if(retVal != E_OK)
      {
        /* Simply register a DET error and move on with service handling */
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        DCM_DET_REPORT_ERROR(DCM_SVCID_ACTIVATEEVENT, DCM_E_ROE_ACTIVATE_EVENT_FAIL);
#endif
      }
    }
    Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_SETUP;
    Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_SETUP;
  }
#endif

  /* check request length */
  if (pMsgContext->reqDataLen != 1U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    /* assign the data from msgcontext for service to that of sub-function.*/
    /* set request data pointer to received data without service and subservice Ids */
    pMsgContext->reqData = &pMsgContext->reqData[1];
    /* decrement the reqData length as sub-function is removed */
    pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;
    /* Call common subservice handler */
    serviceProcessStatus = Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH(DCM_INITIAL,
      pMsgContext);
  }

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8_least instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig = &DCM_SES_TAB_CONFIG(instIdx);
  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  uint8_least i;
  Dcm_SesCtrlType newSesCtrl = curHsmInfo->newSesCtrl;
  /* Initialize with max value + 1 */
  uint8 sesTabIdxNew = sesTabConfig->NumEntries;

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROLCOMMON_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED (OpStatus);

  /* get requested session index in current protocol session table */
  for (i = 0U; i < sesTabConfig->NumEntries; ++i)
  {
    if ((sesTabConfig->SessionEntries[i]).SesCtrl == newSesCtrl)
    {
      sesTabIdxNew = (uint8)i;
      break;
    }
  }

  if (sesTabIdxNew < sesTabConfig->NumEntries)
  {
    /* set new session type. Active session type is set during post processing */
    curHsmInfo->sesTabIdxNew = sesTabIdxNew;

    /* set context id for post processing a session change*/
    pMsgContext->idContext = DCM_SID_SESSION_CONTROL;
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
    /* Set confirmed diagnostics session to invalid */
    DCM_HSM_INFO(instIdx).confirmedDiagSession = DCM_INVALID_SESSION;

#if (DCM_BSWM_API_ENABLED == STD_ON)
    /* invoke BswM with the requested session as parameter */
    BswM_Dcm_RequestSessionMode(newSesCtrl);
#endif
#endif  /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

    /* Set return value to PENDING status, so that the service handler is called again in
    the next main function cycle */
    serviceProcessStatus = DCM_E_PENDING;
  }
  else
  {
    /* requested session is not configured for the current protocol, return an error */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROLCOMMON_SSVCH_EXIT(serviceProcessStatus,
                                                                OpStatus,
                                                                pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControl_SvcCont(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

#if (DCM_TIMING_VALUES_IN_POSITIVE_RESPONSE == STD_ON)
  uint16 P2StarTime;
#endif

#if((DCM_JUMP_TO_BL_ENABLED == STD_ON) || \
    (DCM_TIMING_VALUES_IN_POSITIVE_RESPONSE == STD_ON) || \
    (DCM_MODEDECLARATION_SUPPORT == STD_OFF))

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig = &DCM_SES_TAB_CONFIG(instIdx);

#endif /* #if((DCM_JUMP_TO_BL_ENABLED == STD_ON) || \
              (DCM_TIMING_VALUES_IN_POSITIVE_RESPONSE == STD_ON) || \
              (DCM_MODEDECLARATION_SUPPORT == STD_OFF)) */

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCCONT_ENTRY(pMsgContext);

#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
  /* check if a ModeEntry confirmation is received from BswM */
  if ( curHsmInfo->confirmedDiagSession != DCM_INVALID_SESSION )
  {
    /* check if the session transition is accepted by BswM.
      ie requested mode is same as mode entered */
    if ( (sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].SesCtrl) ==
         (curHsmInfo->confirmedDiagSession) )
    {
#endif
#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
      if (((sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].SessionForBoot) ==
          DCM_OEM_BOOT ) ||
          ((sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].SessionForBoot) ==
          DCM_SYS_BOOT))
      {
        curHsmInfo->jumpToBLSupport = TRUE;

        /* Initiate the Jump to BL request */
        serviceProcessStatus = Dcm_DspInternal_JumpToBL(pMsgContext, DCM_INITIAL);
      }
      else
      {
#endif  /* DCM_JUMP_TO_BL_ENABLED */
        /* !LINKSTO Dcm222,1 */
        pMsgContext->resData[0] = curHsmInfo->newSesCtrl;
#if (DCM_TIMING_VALUES_IN_POSITIVE_RESPONSE == STD_ON)
        /* Assemble positive response for DiagnosticSessionControl request */
        P2StarTime = (uint16)((sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].P2StarMaxTime*
                                                    DCM_TASK_TIME) / DCM_P2STARTIME_RESOLUTION);

        pMsgContext->resData[1] =
               (uint8)((sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].P2MaxTime *
                                                             DCM_TASK_TIME) >> DCM_BYTE_SWAPPING);
        pMsgContext->resData[2] =
          (uint8)(sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].P2MaxTime * DCM_TASK_TIME);
        pMsgContext->resData[3] = (uint8)(P2StarTime >> DCM_BYTE_SWAPPING);
        pMsgContext->resData[4] = (uint8)(P2StarTime);
        pMsgContext->resDataLen = DCM_0x10_RESPONSELENGTH_TIMING_VALUES;
#else
        pMsgContext->resDataLen = DCM_0x10_RESPONSELENGTH_NO_TIMING_VALUES;
#endif
        serviceProcessStatus = DCM_E_DONE;
#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
      }
#endif
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
    }
    else
    {
      /* Session transition not accepted. Set negative response */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
      serviceProcessStatus = DCM_E_DONE;
    }

    /* Reset confirmed diagnostic session */
    curHsmInfo->confirmedDiagSession = DCM_INVALID_SESSION;
  }
  else
  {
    serviceProcessStatus = DCM_E_PENDING;
  }
#endif

  DBG_DCM_DSPINTERNAL_DIAGNOSTICSESSIONCONTROL_SVCCONT_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

#if(DCM_JUMP_TO_BL_ENABLED == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_JumpToBL(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  Dcm_OpStatusType OpStatus)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig = &DCM_SES_TAB_CONFIG(instIdx);

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
    = &DCM_HSM_CONFIG(instIdx);

  DBG_DCM_DSPINTERNAL_JUMPTOBL_ENTRY(pMsgContext,OpStatus);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      /* If the session is used to jump to OEM bootloader */
      if ( (sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].SessionForBoot) ==
            DCM_OEM_BOOT )
      {
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
        /* Invoke BswM and set the 'requestedResetMode' */
        BswM_Dcm_RequestResetMode(DCM_BOOTLOADER_RESET);
        curHsmInfo->requestedResetMode = DCM_BOOTLOADER_RESET;
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
#if (DCM_MODE_DECLARATION_OEM_BL == STD_ON)
          /* Dcm532 */
        (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER);
#endif /* #if (DCM_MODE_DECLARATION_OEM_BL == STD_ON) */
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
      }
      /* If the session is used to jump to System Supplier bootloader */
      else
      {
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
        /* Invoke BswM and set the 'requestedResetMode' */
        BswM_Dcm_RequestResetMode(DCM_SS_BOOTLOADER_RESET);
        curHsmInfo->requestedResetMode = DCM_SS_BOOTLOADER_RESET;
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
#if (DCM_MODE_DECLARATION_SYS_BL == STD_ON)
        /* Dcm592 */
        (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER);
#endif /* #if (DCM_MODE_DECLARATION_SYS_BL == STD_ON) */
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
      }

      curHsmInfo->jumpToBLExecution = DCM_PREPARE_JUMP;

      serviceProcessStatus = DCM_E_PENDING;

      break;

    case DCM_PENDING:

#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
      /* check if a reset mode entry confirmation is received from BswM */
      if ( curHsmInfo->confirmedResetMode != DCM_NO_RESET )
      {
        /* check if the reset request is accepted by BswM. ie requested reset mode
           is same as the reset mode entered */
        if ((curHsmInfo->confirmedResetMode) == (curHsmInfo->requestedResetMode))
        {
#endif
          if (curHsmInfo->jumpToBLExecution == DCM_PREPARE_JUMP)
        {
          /* Check if a 'ResponsePending' needs to be transmitted */
          if (curHsmConfig->sendRespPendOnTransToBoot == TRUE)
          {
            /* Set status to indicate that Response pending Tx confirmation is Pending */
            curHsmInfo->responsePendingTxStatus = DCM_RP_PENDING_CONF;
              curHsmInfo->jumpToBLExecution = DCM_FIRST_RCRRP_PENDING;

            /* Forcefully emitting the event TIMEOUT2 to trigger the transmission of
               'Response Pending' message */

            /* ENTER critical section
               Protect timer2 from preemption */
            SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

            DCM_HSM_INFO(instIdx).timer2 = 0U;
            (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                      DCM_HSM_DCM_EV_TIMEOUT2);

            /* LEAVE critical section */
            SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

            serviceProcessStatus = DCM_E_PENDING;
          }
          else
          {
              curHsmInfo->jumpToBLExecution = DCM_JUMP_IN_PROGRESS;

            /* [Dcm720]: If the jump to bootloader is requested and the configuration parameter
            DcmSendRespPendOnTransToBoot is set to FALSE, the DCM shall call
            Dcm_SetProgConditions() immediately */
            serviceProcessStatus = Dcm_DspInternal_ProcessSetProgConditions(pMsgContext);

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
              /* !LINKSTO Dcm.EB.ModeSwitch.JumpToBL.SetProgConditions,1 */
              if(serviceProcessStatus == DCM_E_OK)
              {
                /* Dcm719 */
                (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
                /* Retrun ABORT since there is no response to send */
                serviceProcessStatus = DCM_E_ABORT;
              }
#endif
          }
        }
          else if (curHsmInfo->jumpToBLExecution == DCM_JUMP_IN_PROGRESS)
          {
            /* [Dcm535]: If the jump to bootloader is requested and the configuration parameter
            DcmSendRespPendOnTransToBoot is set to TRUE, the DCM shall call Dcm_SetProgConditions()
            after confirmation of the transmission of NRC 0x78 (Response pending) */
            serviceProcessStatus = Dcm_DspInternal_ProcessSetProgConditions(pMsgContext);

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
            /* !LINKSTO Dcm.EB.ModeSwitch.JumpToBL.SetProgConditions,1 */
            if(serviceProcessStatus == DCM_E_OK)
            {
              /* Dcm719 */
              (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
              /* Retrun ABORT since there is no response to send */
              serviceProcessStatus = DCM_E_ABORT;
            }
#endif
          }
          else
          {
            /* waiting for the confirmation to the RCRRP, we do nothing */
            serviceProcessStatus = DCM_E_PENDING;
          }
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
        }
        else
        {
          curHsmInfo->jumpToBLSupport = FALSE;
          /* reset the jump to bootloader state */
          curHsmInfo->jumpToBLExecution = DCM_PREPARE_JUMP;
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
          /* reset the request mode parameters */
          curHsmInfo->confirmedResetMode = DCM_NO_RESET;
          curHsmInfo->requestedResetMode = DCM_NO_RESET;
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
          /* Jump to bootloader mode is not accepted, trigger the transmission of
             NRC 0x22 (Conditions not correct) */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
          serviceProcessStatus = DCM_E_PENDING;
        }
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

      break;

    default:
      /* Do Nothing */
      break;
  }

  DBG_DCM_DSPINTERNAL_JUMPTOBL_EXIT(serviceProcessStatus,pMsgContext,OpStatus);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessSetProgConditions(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType SetProgConditionsReturn = E_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) curMsgContext = &curHsmInfo->msgContext;

  /* Get tester source address */
  uint16 testerSourceAddr = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].TesterSourceAddr;

  DBG_DCM_DSPINTERNAL_PROCESSSETPROGCONDITIONS_ENTRY(pMsgContext);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(instIdx);
#endif

  ProgConditions.ProtocolId = DCM_HSM_CONFIG(instIdx).protocolType;
  ProgConditions.Sid = DCM_SID_SESSION_CONTROL;
  ProgConditions.SubFncId = curHsmInfo->subServiceId;
  ProgConditions.TesterSourceAddr = testerSourceAddr;
  ProgConditions.ReprogramingRequest = TRUE;

  /* Check if response required flag is set */
  if (curMsgContext->msgAddInfo.suppressPosResponse == TRUE)
  {
    ProgConditions.ResponseRequired = FALSE;
  }
  else
  {
    ProgConditions.ResponseRequired = TRUE;
  }

  /* Call Dcm_SetProgConditions() to store all relevant information,
     prior to jumping to the bootloader */
  SetProgConditionsReturn = Dcm_SetProgConditions(&ProgConditions);

  if( SetProgConditionsReturn == DCM_E_PENDING )
  {
    /* Set the variable to indicate 'SetProgConditions' returned Pending status */
    curHsmInfo->jumpToBLExecution = DCM_JUMP_IN_PROGRESS;

    serviceProcessStatus = DCM_E_PENDING;
  }
  else
  {
    if( SetProgConditionsReturn == DCM_E_OK )
    {
      /* Service execution finished. Now return E_OK to perform the RESET */
      serviceProcessStatus = DCM_E_OK;
#if ((DCM_MODEDECLARATION_SUPPORT == STD_OFF) && (DCM_BSWM_API_ENABLED == STD_ON))
      /* Invoke the BswM interface to perform the jump to bootloader */
      BswM_Dcm_RequestResetMode(DCM_RESET_EXECUTION);
#endif
    }
    else
    {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      if ( SetProgConditionsReturn == DCM_E_NOT_OK )
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_SETPROGCONDITIONS, DCM_E_SET_PROG_CONDITIONS_FAIL);
      }
      else
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_SETPROGCONDITIONS, DCM_E_INTERFACE_RETURN_VALUE);
      }
#endif
      /* Dcm_SetProgConditions() failed; trigger the transmission of
         NRC 0x22 (Conditions not correct) */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
      serviceProcessStatus = DCM_E_DONE;
    }

    /* In case of successful or failed BL Jump, Reset the variables */
    curHsmInfo->jumpToBLSupport = FALSE;
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
    /* reset the request mode parameters */
    curHsmInfo->confirmedResetMode = DCM_NO_RESET;
    curHsmInfo->requestedResetMode = DCM_NO_RESET;
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
    curHsmInfo->jumpToBLExecution = DCM_PREPARE_JUMP;
  }

  DBG_DCM_DSPINTERNAL_PROCESSSETPROGCONDITIONS_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if(DCM_JUMP_TO_BL_ENABLED == STD_ON) */
#endif /* (DCM_DSP_USE_SERVICE_0X10 == STD_ON) */

#if((DCM_EXTSVC_ENABLED == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X10 == STD_ON))
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_SetSessionState(
  uint8 instIdx)
{
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig = &DCM_SES_TAB_CONFIG(instIdx);

  Dcm_SesCtrlType oldSesCtrl;
  Dcm_SesCtrlType newSesCtrl = 0U;
  uint8 sesTabIdxNew = 0U;
  uint8_least i;
#if(DCM_0X85_SVC_ENABLED == STD_ON)
  boolean  ControlDTCSupport = FALSE;
#endif

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  DBG_DCM_DSPINTERNAL_SETSESSIONSTATE_ENTRY(DCM_INST(instIdx));

  /* if a positive response was transmitted for previous SessionControl request */
  if ( curHsmInfo->negativeResponseCode == DCM_E_OK )
  {
    oldSesCtrl = sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl;

    /* Change in Security level on session transitions (as per Dcm139)
      Default -> Default : No change
      Default -> Non-default : No change
      Non-Default -> Default : Reset to 0x00
      Non-Default -> Non-Default : Reset to 0x00
    */
    if (oldSesCtrl != DCM_DEFAULT_SESSION)
    {
      /* reset security level */
      curHsmInfo->secTabIdx = DCM_SEC_TAB_ENTRY_IDX_LOCKED;
    }
    /* set new active session for internal service handler */
    if(DCM_HSM_INFO(instIdx).dspService)
    {
      curHsmInfo->sesTabIdx = curHsmInfo->sesTabIdxNew;
#if(DCM_0X85_SVC_ENABLED == STD_ON)
      {
        /* get configuration for current HSM instance */
        CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig =
                                                                          &DCM_HSM_CONFIG(instIdx);
        /* get configuration for current service table */
        CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
                = &Dcm_SidTabConfig[curHsmConfig->sidTabId];
        P2CONST(Dcm_SidTabEntryConfigType, AUTOMATIC, DCM_CONST) SidConfig = NULL_PTR;
        uint8_least sidIdxExt = 0U;

        if(curHsmInfo->dtcDisableStatus == TRUE)
        {
          /* search list of configured services */
          while ( sidIdxExt < curSidTabConfig->NumEntries )
          {
            if ((curSidTabConfig->Entries[sidIdxExt]).ServiceId == DCM_DSP_SERVICE_0X85)
            {
              break;
            }
            sidIdxExt++;
          }
          /* set configuration entry of 0x85 service Id */
          SidConfig = &(curSidTabConfig->Entries[sidIdxExt]);
          /* Enabling DTC setting, if 0x85 service is not supported in the requested session */
          if(sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl != DCM_DEFAULT_SESSION)
          {
            for (i = 0U; i < SidConfig->NumSesCtrls; ++i)
            {
              if ((SidConfig->SesCtrls[i] == DCM_ALL_SESSION_LEVEL) ||
                  ((sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl) ==
                    SidConfig->SesCtrls[i]))
              {
                ControlDTCSupport = TRUE;
                break;
              }
            }
          }

          if (ControlDTCSupport == FALSE)
          {
            /* Enables the DTC setting for the DTC group */
            (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
            /* Dcm751 */
            (void)SchM_Switch_Dcm_DcmControlDTCSetting(
                        RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
          }
        }
      }
#endif
    }
    /* set new active session for external service handler */
    else
    {
      newSesCtrl = curHsmInfo->newSesCtrl;

      /* Check if the requested session is supported */
      for (i = 0U; i < sesTabConfig->NumEntries; ++i)
      {
        if ((sesTabConfig->SessionEntries[i]).SesCtrl == newSesCtrl)
        {
          sesTabIdxNew = (uint8)i;
          break;
        }
      }
      curHsmInfo->sesTabIdx = sesTabIdxNew;
    }

#if(DCM_0X28_SVC_ENABLED == STD_ON)
    {
      /* get configuration for current HSM instance */
      CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig =
                                                                        &DCM_HSM_CONFIG(instIdx);
      /* get configuration for current service table */
      CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
              = &Dcm_SidTabConfig[curHsmConfig->sidTabId];
      P2CONST(Dcm_SidTabEntryConfigType, AUTOMATIC, DCM_CONST) SidConfig = NULL_PTR;
      uint8_least sidIdxExt = 0U;
      boolean  CommunicationControlSupport = FALSE;
      /* get current session type */
      const Dcm_SesCtrlType curSesCtrl =
                sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl;

      /* search list of configured services for CommunicationControl 0x28 */
      while ( sidIdxExt < curSidTabConfig->NumEntries )
      {
        if ((curSidTabConfig->Entries[sidIdxExt]).ServiceId == DCM_DSP_SERVICE_0X28)
        {
          break;
        }
        sidIdxExt++;
      }
      /* set configuration entry of 0x28 service Id */
      SidConfig = &(curSidTabConfig->Entries[sidIdxExt]);

      /*
       * check if service request is allowed in current session
       */

      /* If a switch to the DefaultSession shall be made or
       * if service communication control is not provided in the new session,
       * the flag CommunicationControlSupport shall be stay at FALSE otherwise TRUE */
      if ((curSesCtrl != DCM_DEFAULT_SESSION) &&
          (SidConfig->NumSesCtrls > 0U))
      {
        /* check if CommunicationControl service 0x28 is supported in the requested session */
        for (i = 0U; i < SidConfig->NumSesCtrls; ++i)
        {
          if ((SidConfig->SesCtrls[i] == DCM_ALL_SESSION_LEVEL) ||
              (SidConfig->SesCtrls[i] == curSesCtrl))
          {
            CommunicationControlSupport = TRUE;
            break;
          }
        }
      }

      /* set communication mode to DCM_ENABLE_RX_TX_NORM_NM if CommunicationControl service 0x28 is
         not supported in the new session
         !LINKSTO Dcm.EB.CommunicationModeSwitch.DcmEnableRxTxNormNm,1
         !LINKSTO Dcm.EB.CommunicationModeSwitch.DcmEnableRxTxNormNm_2,1 */
      if (CommunicationControlSupport == FALSE)
      {
        for (i = 0U; i < DCM_NUM_CHANNELID; i++)
        {
          if (Dcm_ChannelId[i].communicationMode != DCM_ENABLE_RX_TX_NORM_NM)
          {
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
            uint8_least j = 0U;
            /* Search for SchM switch index */
            /* Please note that a Dcm 'NetworkId' is exactly the same thing as a ComM 'ChannelId' */
            while ((j < DCM_COMCONTROL_LOOKUP_SIZE) &&
                   (Dcm_ComControlLookUpTable[j].ComMChannelId != Dcm_ChannelId[i].networkId))
            {
              j++;
            }
            (void)Dcm_ComControlLookUpTable[j].SchMSwitchComControl(
                      RTE_MODE_DcmCommunicationControl_DCM_ENABLE_RX_TX_NORM_NM);

#if (DCM_BSWM_API_ENABLED == STD_ON)
            /* Invoke the BswM interface to notify the Communication Mode change */
            BswM_Dcm_CommunicationMode_CurrentState(Dcm_ChannelId[i].networkId,
                                                    DCM_ENABLE_RX_TX_NORM_NM);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */
#if (DCM_BSWM_API_ENABLED == STD_ON)
            /* Invoke the BswM interface to request the Communication Mode change */
            BswM_Dcm_RequestCommunicationMode(Dcm_ChannelId[i].networkId, DCM_ENABLE_RX_TX_NORM_NM);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */

            Dcm_ChannelId[i].communicationMode = DCM_ENABLE_RX_TX_NORM_NM;
          }
        }
      }
    }
#endif /* #if (DCM_0X28_SVC_ENABLED == STD_ON) */

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
    /* set to new session */
    /* Dcm311 */
    (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(
      sesTabConfig->SessionEntries[curHsmInfo->sesTabIdxNew].RteSesMode);
#endif

    /* reset security access state handling */
    curHsmInfo->requestedSecLevel = DCM_SEC_IDLE;
  }

  DBG_DCM_DSPINTERNAL_SETSESSIONSTATE_EXIT(DCM_INST(instIdx));
}
#endif /* #if((DCM_EXTSVC_ENABLED == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X10 == STD_ON)) */

#if(DCM_DSP_USE_SERVICE_0X11 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ECUReset_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);

  DBG_DCM_DSPINTERNAL_ECURESET_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_ECUReset_SvcStart(DCM_INITIAL, pMsgContext);
      break;

    /* Consecutive call after the function returned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_ECUReset_SvcCont(DCM_PENDING, pMsgContext);
      break;

      /* Cancel the ongoing service processing */
      case DCM_CANCEL:
        serviceProcessStatus = Dcm_DspInternal_ECUReset_SvcCont(DCM_CANCEL, pMsgContext);
        break;

    /* actions performed on successful sending of the response */
    case DCM_CONFIRMED_OK:

      /* if a positive response was transmitted for previous 'ECUReset' request */
      if ( curHsmInfo->negativeResponseCode == DCM_E_OK )
      {
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
        /* Invoke the BswM interface for reset execution */
        BswM_Dcm_RequestResetMode(DCM_RESET_EXECUTION);
#endif
#else
        /* Dcm594 */
        (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

        if(curHsmInfo->dtcDisableStatus == TRUE)
        {
          /* If a successful ECUReset is performed, then DCM module shall call
             Dem_EnableDTCSetting() to re-enable the setting of DTCs. */
          (void)Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
          /* Dcm751 */
          (void)SchM_Switch_Dcm_DcmControlDTCSetting(
                    RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
        }
      }
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_ECURESET_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ECUReset_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(curProtocolId).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  /* get number of subservices */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  /* loop variable */
  uint8_least i;

  TS_PARAM_UNUSED(OpStatus);

  DBG_DCM_DSPINTERNAL_ECURESET_SVCSTART_ENTRY(pMsgContext);

  if (pMsgContext->reqDataLen == 1U)
  {
    for (i = 0U; i < numSubServ; i++)
    {
      /* Search for the index in subservices table for the requested subservice */
      if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
      {
        /* assign the data from msgcontext for service to that of sub-function.*/
        /* set request data pointer to received data without service and subservice Ids */
        pMsgContext->reqData = &pMsgContext->reqData[1];

        /* decrement the reqData length as sub-function is removed */
        pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;

        if (curSsConfig[i].IntSrvHandler != NULL_PTR)
        {
          /* Call internal sub-service handler */
          serviceProcessStatus = curSsConfig[i].IntSrvHandler(DCM_INITIAL, pMsgContext);
        }
        else
        {
          /* Call External sub-service handler */
          serviceProcessStatus = curSsConfig[i].ExtSrvHandler(DCM_INITIAL, pMsgContext);

          /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
          if (serviceProcessStatus == E_OK)
          {
            serviceProcessStatus = DCM_E_DONE;
          }
        }

        break;
      }
    }
  }
  else
  {
    /* check request length */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_ECURESET_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ECUReset_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(curProtocolId).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  /* get number of subservices */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  /* loop variable */
  uint8 i;

  DBG_DCM_DSPINTERNAL_ECURESET_SVCCONT_ENTRY(pMsgContext);

  for (i = 0U; i < numSubServ; i++)
  {
    /* Search for the index in subservices table for the requested subservice */
    if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
    {
      if (curSsConfig[i].IntSrvHandler != NULL_PTR)
      {
        if(OpStatus != DCM_CANCEL)
        {
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
          /* check if a reset mode entry confirmation is received from BswM */
          if ( curHsmInfo->confirmedResetMode != DCM_NO_RESET )
          {
            /* check if the reset request is accepted by BswM. ie requested reset mode
               is same as the reset mode entered */
            if ((curHsmInfo->confirmedResetMode) == (curHsmInfo->requestedResetMode))
            {
              /* if the confirmed mode is 'enableRapidPowerShutDown' */
              if (curHsmInfo->confirmedResetMode == DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET )
              {
                /* assemble positive response */
                pMsgContext->resDataLen = 2U;

                /* set the powerDownTime in response */
                pMsgContext->resData[1] = DCM_DSP_POWER_DOWN_TIME;
              }
              else
              {
                /* assemble positive response */
                pMsgContext->resDataLen = 1U;
              }
              pMsgContext->resData[0] = curHsmInfo->subServiceId;
            }
            else
            {
              /* reset request not accepted. Set negative response */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
            }
            /* reset the request mode parameters */
            curHsmInfo->confirmedResetMode = DCM_NO_RESET;
            curHsmInfo->requestedResetMode = DCM_NO_RESET;
            serviceProcessStatus = DCM_E_DONE;
          }
          else
          {
            serviceProcessStatus = DCM_E_PENDING;
          }
#else
          if (curHsmInfo->subServiceId == DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET)
          {
            /* assemble positive response */
            pMsgContext->resDataLen = 2U;
            /* set the powerDownTime in response */
            pMsgContext->resData[1] = DCM_DSP_POWER_DOWN_TIME;
          }
          else
          {
            /* assemble positive response */
            pMsgContext->resDataLen = 1U;
          }
          pMsgContext->resData[0] = curHsmInfo->subServiceId;
         serviceProcessStatus = DCM_E_DONE;
#endif
        }
        else
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /* Call External sub-service handler */
        serviceProcessStatus = curSsConfig[i].ExtSrvHandler(OpStatus, pMsgContext);

        /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
        if (serviceProcessStatus == E_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }

      break;
    }
  }

  DBG_DCM_DSPINTERNAL_ECURESET_SVCCONT_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

#if (DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON)
/* This is the UDS service 0x11-0x01 handler */
/* Deviation MISRA-4 <+3> */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_HardReset_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  DBG_DCM_DSPINTERNAL_HARDRESET_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
  /* Set Reset Mode */
  Dcm_DspInternal_SetResetMode(pMsgContext);
#else /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
  TS_PARAM_UNUSED(pMsgContext);
  /* Dcm373 */
  (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_HARD);
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

  DBG_DCM_DSPINTERNAL_HARDRESET_SSVCH_EXIT(DCM_E_PENDING,OpStatus,pMsgContext);
  return DCM_E_PENDING;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON)
/* This is the UDS service 0x11-0x02 handler */
/* Deviation MISRA-4 <+3> */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_KeyOffOnReset_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  DBG_DCM_DSPINTERNAL_KEYOFFONRESET_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
  /* Set Reset Mode */
  Dcm_DspInternal_SetResetMode(pMsgContext);
#else /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
  TS_PARAM_UNUSED(pMsgContext);
  /* Dcm373 */
  (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_KEYOFFON);
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

  DBG_DCM_DSPINTERNAL_KEYOFFONRESET_SSVCH_EXIT(DCM_E_PENDING,OpStatus,pMsgContext);
  return DCM_E_PENDING;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON)
/* This is the UDS service 0x11-0x03 handler */
/* Deviation MISRA-4 <+3> */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SoftReset_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  DBG_DCM_DSPINTERNAL_SOFTRESET_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
  /* Set Reset Mode */
  Dcm_DspInternal_SetResetMode(pMsgContext);
#else /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
  TS_PARAM_UNUSED(pMsgContext);
  /* Dcm373 */
  (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_SOFT);
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

  DBG_DCM_DSPINTERNAL_SOFTRESET_SSVCH_EXIT(DCM_E_PENDING,OpStatus,pMsgContext);
  return DCM_E_PENDING;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON)
/* This is the UDS service 0x11-0x04 handler */
/* Deviation MISRA-4 <+3> */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_EnableRapidPowerShutDown_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  DBG_DCM_DSPINTERNAL_ENABLERAPIDPOWERSHUTDOWN_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
  /* Set Reset Mode */
  Dcm_DspInternal_SetResetMode(pMsgContext);
#else /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
  TS_PARAM_UNUSED(pMsgContext);
  /* Dcm818 */
  (void)SchM_Switch_Dcm_DcmRapidPowerShutdown(
            RTE_MODE_DcmRapidPowerShutdown_ENABLE_RAPIDPOWERSHUTDOWN);
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

  DBG_DCM_DSPINTERNAL_ENABLERAPIDPOWERSHUTDOWN_SSVCH_EXIT(DCM_E_PENDING,OpStatus,pMsgContext);
  return DCM_E_PENDING;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON)
/* This is the UDS service 0x11-0x05 handler */
/* Deviation MISRA-4 <+3> */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DisableRapidPowerShutDown_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  DBG_DCM_DSPINTERNAL_DISABLERAPIDPOWERSHUTDOWN_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
#if (DCM_BSWM_API_ENABLED == STD_ON)
  /* Set Reset Mode */
  Dcm_DspInternal_SetResetMode(pMsgContext);
#else /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
  TS_PARAM_UNUSED(pMsgContext);
  /* Dcm818 */
  (void)SchM_Switch_Dcm_DcmRapidPowerShutdown(
            RTE_MODE_DcmRapidPowerShutdown_DISABLE_RAPIDPOWERSHUTDOWN);
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

  DBG_DCM_DSPINTERNAL_DISABLERAPIDPOWERSHUTDOWN_SSVCH_EXIT(DCM_E_PENDING,OpStatus,pMsgContext);
  return DCM_E_PENDING;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON) */

#if ((DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON))

#if ((DCM_MODEDECLARATION_SUPPORT == STD_OFF) && (DCM_BSWM_API_ENABLED == STD_ON))
/* this function is to set & perform request reset mode */
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_SetResetMode(
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);

  /* store softReset value to local buffer*/
  Dcm_ResetModeType resetModeType = curHsmInfo->subServiceId;

  DBG_DCM_DSPINTERNAL_SETRESETMODE_ENTRY(pMsgContext);

#if ((DCM_HSM_INST_MULTI_ENABLED == STD_OFF) && (DCM_DBG_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(pMsgContext);
#endif

  /* Update the requested Reset Mode and reset confirmed Reset Mode */
  curHsmInfo->requestedResetMode = resetModeType;
  curHsmInfo->confirmedResetMode = DCM_NO_RESET;

  /* Invoke the BswM interface with requested Reset Mode as parameter */
  BswM_Dcm_RequestResetMode(resetModeType);

  DBG_DCM_DSPINTERNAL_SETRESETMODE_EXIT(pMsgContext);
}
#endif /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_OFF) && (DCM_BSWM_API_ENABLED == STD_ON)) */

#endif  /* #if ((DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON))  */

#endif /* #if (DCM_DSP_USE_SERVICE_0X11 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X14 == STD_ON)
/* This is the generic service handler for UDS service 0x14 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:

    /* _SvcStart has returned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_ClearDTCInfo_SvcStart(pMsgContext);
      break;

    /* Cancel the pending 'ClearDTC' operation started from Dcm */
    case DCM_CANCEL:
      Dem_DcmCancelOperation();
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
      /* no need of any processing for all the
          remaining operation states */
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_CLEARDIAGNOSTICINFORMATION_SVCH_EXIT(serviceProcessStatus,
                                                           OpStatus,
                                                           pMsgContext);
  return serviceProcessStatus;
}

/* This is the implementation of UDS service 0x14 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDTCInfo_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint32 reqDTC;
  Dem_ReturnClearDTCType resultClrDTC;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_CLEARDTCINFO_SVCSTART_ENTRY(pMsgContext);

  /* If length of request data is correct */
  if (pMsgContext->reqDataLen == 3U)
  {
    reqDTC = ((uint32)pMsgContext->reqData[0] << 16U) |
             ((uint32)pMsgContext->reqData[1] << 8U)  |
             ((uint32)pMsgContext->reqData[2]);
#if (DCM_INCLUDE_RTE == STD_ON)
    /* !LINKSTO Dcm.ClearDTC.RteUsageTrue.Prototype,2 */
    resultClrDTC = Rte_Call_DcmIf_ClearDTC(reqDTC, DEM_DTC_FORMAT_UDS,
      DEM_DTC_ORIGIN_PRIMARY_MEMORY);
#else
    /* !LINKSTO Dcm.Dem_ClearDTC.Prototype,2 */
    resultClrDTC = Dem_ClearDTC(reqDTC, DEM_DTC_FORMAT_UDS, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
#endif

    switch (resultClrDTC)
    {
      case DEM_CLEAR_OK:
        serviceProcessStatus = DCM_E_DONE;
        break;
      case DEM_CLEAR_FAILED:
        /* DTC clearance failed */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        serviceProcessStatus = DCM_E_DONE;
        break;
      case DEM_CLEAR_PENDING:
        /* DTC clearance pending */
        serviceProcessStatus = DCM_E_PENDING;
        break;
      case DEM_CLEAR_WRONG_DTC:
        /* Wrong DTC */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
        break;
      case DEM_CLEAR_WRONG_DTCORIGIN:
        /* Wrong DTC origin */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
        break;

      default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        DCM_DET_REPORT_ERROR(DCM_SVCID_CLEARDTC, DCM_E_INTERFACE_RETURN_VALUE);
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
        serviceProcessStatus = DCM_E_DONE;
        break;
    }
  }
  else
  {
    /* invalid request length */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_CLEARDTCINFO_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_DSP_USE_SERVICE_0X14 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X19 == STD_ON)
/* This is the generic service handler for UDS service 0x19 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDTCInformation_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* Get the current context info */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  STATIC CONST(Dcm_ProcessPageFuncType, DCM_CONST) Dcm_ReadDTC_ProcPageFunc[4] =
  {
#if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON))
    &Dcm_DspInternal_ProcessPageDTCByStatusMask,
#else
    NULL_PTR,
#endif /* #if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
    &Dcm_DspInternal_ProcessPageDtcSnapshotRecord,
#else
    NULL_PTR,
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
    &Dcm_DspInternal_ProcessPageDtcExtDataRecord,
#else
    NULL_PTR,
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)
    &Dcm_DspInternal_ProcessPageDTCSnapshotByIdentification
#else
    NULL_PTR
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON) */
  };

  DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCH_ENTRY(OpStatus,pMsgContext);

#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_ReadDTCInformation_SvcStart(pMsgContext);
      /* first page of data is being filled from here, if paged processing has been enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if (curHsmInfo->processPageFuncId != DCM_PROCESS_PAGE_ID_INVALID)
      {
        /* update the response buffer pointer and the response length */
        Dcm_DspInternal_UpdateResponseBuffer(pMsgContext);

        if (Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId] != NULL_PTR)
        {
          /* fill a page of data */
          serviceProcessStatus =
            Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId](pMsgContext);
        }
      }
#endif
      break;

    /* consecutive call after the function retuned PENDING before */
    case DCM_PENDING:
      /* Depending on whether the paged processing is started or not,
         the corresponding service handler function or pagedprocessing function
         needs to be called from here */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if (curHsmInfo->processPageFuncId != DCM_PROCESS_PAGE_ID_INVALID)
      {
        if (Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId] != NULL_PTR)
        {
          /* fill a page of data */
          serviceProcessStatus =
            Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId](pMsgContext);
        }
        else
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
#endif
      {
        serviceProcessStatus = Dcm_DspInternal_ReadDTCInformation_SvcCont(pMsgContext);
        /* first page of data is being filled from here, if paged processing has been enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        if (curHsmInfo->processPageFuncId != DCM_PROCESS_PAGE_ID_INVALID)
        {
          /* update the response buffer pointer and the response length */
          Dcm_DspInternal_UpdateResponseBuffer(pMsgContext);

          if (Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId] != NULL_PTR)
          {
            /* fill a page of data */
            serviceProcessStatus =
                Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId](pMsgContext);
          }
        }
#endif
      }
      break;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* cancel any ongoing service processing, during paged processing */
    case DCM_CANCEL:
    case DCM_CONFIRMED_OK:
    case DCM_CONFIRMED_NOK:
      /* reset the paged buffer function id */
      curHsmInfo->processPageFuncId = DCM_PROCESS_PAGE_ID_INVALID;
      serviceProcessStatus = DCM_E_DONE;
      break;

    /* update the next page in paged buffer processing */
    case DCM_UPDATE_PAGE:
      /* call the corresponding paged processing function, if process page id is valid */
      if (curHsmInfo->processPageFuncId != DCM_PROCESS_PAGE_ID_INVALID)
      {
        if (Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId] != NULL_PTR)
        {
          serviceProcessStatus =
            Dcm_ReadDTC_ProcPageFunc[curHsmInfo->processPageFuncId](pMsgContext);
        }
        else
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
          serviceProcessStatus = DCM_E_DONE;
      }
      break;
#endif

   default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

/* This will be called internally for accessing the DEM via UDS service 0x19. This function is used
 * as dispatcher for the sub-services.
 */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDTCInformation_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* loop variable */
  uint8_least i;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* get protocol instance index */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  /* get number of subservices */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Get the pointer to filled length in response buffer */
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
    &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);
#endif/* #if DCM_PAGEDBUFFER_ENABLED */

  DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCSTART_ENTRY(pMsgContext);

  /* check if sub-function is supported */
  if (pMsgContext->reqDataLen == 0U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    /* copy subfunction value to response buffer */
    pMsgContext->resData[0] = curHsmInfo->subServiceId;
    pMsgContext->resDataLen = 1U;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    /* buffer is now filled with the subfunction ID;
       So buffer fill length is now 2 (response ID was already filled) */
    *FilledLengthPtr = 2U;
#endif
    for (i = 0U; i < numSubServ; i++)
    {
      /* Search for the index in subservices table for the requested subservice */
      if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
      {
        /* assign the data from msgcontext for service to that of sub-function.*/
        /* To avoid pMsgContext change when OpStatus is DCM_PENDING */
        /* decrement the reqData length as sub-function is removed */
        pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;
        /* point the reqData behind the sub-function */
        pMsgContext->reqData = &pMsgContext->reqData[1];
        /* Store the Subservice Id index */
        curHsmInfo->subServiceIdIdx = (uint8)i;

        serviceProcessStatus = Dcm_DspInternal_ReadDTCInformation_SvcCont(pMsgContext);
        break;
      }
    }
  }

  DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDTCInformation_SvcCont(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* get protocol instance index */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /* Get the pointer to filled length in response buffer */
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
    &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);

  /* buffer is now filled with the subfunction ID;
  So buffer fill length is now 2 (response ID was already filled) */
  *FilledLengthPtr = 2U;
#endif

  DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCCONT_ENTRY(pMsgContext);

  pMsgContext->resDataLen = 1U;

  if (curSsConfig[curHsmInfo->subServiceIdIdx].IntSrvHandler != NULL_PTR)
  {
    /* Call internal sub-service handler */
    serviceProcessStatus =
            curSsConfig[curHsmInfo->subServiceIdIdx].IntSrvHandler(DCM_INITIAL, pMsgContext);
  }
  else
  {
    /* Call External sub-service handler */
    serviceProcessStatus =
            curSsConfig[curHsmInfo->subServiceIdIdx].ExtSrvHandler(DCM_INITIAL, pMsgContext);

    /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
    if (serviceProcessStatus == E_OK)
    {
      serviceProcessStatus = DCM_E_DONE;
    }
  }

  DBG_DCM_DSPINTERNAL_READDTCINFORMATION_SVCCONT_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#if (DCM_0X19_0X01_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x19-0x01 handler */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_reportNumberOfDTCByStatusMask_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REPORTNUMBEROFDTCBYSTATUSMASK_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

  /* check the request data length */
  /* reqData consists of 1 byte DTCStatusMask */
  if (pMsgContext->reqDataLen == 1U)
  {
    uint8 StatusMask;
    Std_ReturnType resultGetStatusMask = E_OK;
    Dem_DTCTranslationFormatType resultTranslationFormatType;
    /* reqData points behind sub-function i.e points to DTCStatusMask */
    uint8 ReqStatusMask = pMsgContext->reqData[0];

    resultGetStatusMask = Dem_GetDTCStatusAvailabilityMask(&StatusMask);

    if (resultGetStatusMask == E_OK)
    {
       resultTranslationFormatType = Dem_GetTranslationType();
      /* Buffer is big enough to hold DTCStatusAvailabilityMask,
               DTCFormatIdentifier and DTCCount as min Buffer size is 8 */
      /* Update response data with Status Mask */
      /* !LINKSTO Dcm222,1 */
      pMsgContext->resData[1] = StatusMask;
      /* Update response data with TranslationFormatType */
      pMsgContext->resData[2] = resultTranslationFormatType;
      /* update the total response length for the Status Mask and TranslationFormatType */
      pMsgContext->resDataLen += (PduLengthType)2U;

      if ((ReqStatusMask & StatusMask) == 0U)
      {
        /* Update DTCCountHighByte */
        pMsgContext->resData[3] = 0x00;
        /* Update DTCCountLowByte */
        pMsgContext->resData[4] = 0x00;
        /* update the total response length for the filtered DTCs */
        pMsgContext->resDataLen += (PduLengthType)2U;
        serviceProcessStatus = DCM_E_DONE;
      }
      else
      {
        Dem_ReturnSetFilterType resultSetDtcFilter;
        resultSetDtcFilter = Dem_SetDTCFilter(
                               (uint8)(ReqStatusMask & StatusMask),
                               DEM_DTC_KIND_ALL_DTCS,
                               DEM_DTC_FORMAT_UDS,
                               DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                               DEM_FILTER_WITH_SEVERITY_NO,
                               DEM_SEVERITY_NO_SEVERITY,
                               DEM_FILTER_FOR_FDC_NO);

        if ( resultSetDtcFilter == DEM_FILTER_ACCEPTED )
        {
          Dem_ReturnGetNumberOfFilteredDTCType resultFilteredDTC;
          uint16 numFilteredDTCs;
          /* Get the number of filtered DTCs */
          resultFilteredDTC = Dem_GetNumberOfFilteredDTC(&numFilteredDTCs);
          if ( resultFilteredDTC == DEM_NUMBER_OK )
          {
            /* Update DTCCountHighByte */
            pMsgContext->resData[3] =(uint8)(numFilteredDTCs >> 8U);
            /* Update DTCCountLowByte */
            pMsgContext->resData[4] = (uint8)(numFilteredDTCs);
            /* update the total response length for the filtered DTCs */
            pMsgContext->resDataLen += (PduLengthType)2U;

            serviceProcessStatus = DCM_E_DONE;
          }
          else if ( resultFilteredDTC == DEM_NUMBER_PENDING )
          {
            serviceProcessStatus = DCM_E_PENDING;
          }
          else /* Get number of filtered DTC failed */
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        else /* Wrong Filter */
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
    }
    /* error occured while getting DTCStatusAvailabiityMask */
    else
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  /* request data length is invalid */
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REPORTNUMBEROFDTCBYSTATUSMASK_SSVCH_EXIT(serviceProcessStatus,
                                                               OpStatus,
                                                               pMsgContext);
  return serviceProcessStatus;
}
#endif  /* #if (DCM_0X19_0X01_SSVC_ENABLED == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON)
/* This is the UDS service 0x19-0x02 handler */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDTCByStatusMask_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType resultGetStatusMask = E_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
    &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);

   /* Get the current context info */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
#endif/* #if DCM_PAGEDBUFFER_ENABLED */

  DBG_DCM_DSPINTERNAL_REPORTDTCBYSTATUSMASK_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);

  /* check the request data length */
  /* reqData consists of 1 byte DTCStatusMask */
  if (pMsgContext->reqDataLen == 1U)
  {
    uint8 StatusMask;
    uint8 ReqStatusMask = pMsgContext->reqData[0];
    resultGetStatusMask = Dem_GetDTCStatusAvailabilityMask(&StatusMask);
    if (resultGetStatusMask == E_OK)
    {
      /* If DTCStatusAvailabilityMask is equal to 0 the Dcm shall response positively with 0 DTC */
      if ((ReqStatusMask & StatusMask) == 0U)
      {
        /* update response data with Status Mask */
        pMsgContext->resData[1] = StatusMask;
        pMsgContext->resDataLen++;
        serviceProcessStatus = DCM_E_DONE;
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        (*FilledLengthPtr)++;
#endif
      }
      else
      {
        /* check the buffer is big enough to hold DTCStatusAvailabiityMask  */
        if ((pMsgContext->resDataLen + (PduLengthType)1U) <= pMsgContext->resMaxDataLen)
        {
          Dem_ReturnSetFilterType resultSetDtcFilter;
          /* cache data pointer */
          Dcm_MsgType dataPtr = &pMsgContext->resData[1];

          /* add status mask to response buffer and update the response length and filled length of
           * buffer */
          /* Deviation MISRA-1 */
          *dataPtr = (uint8)StatusMask;
          dataPtr++;
          pMsgContext->resDataLen += (PduLengthType)1U;
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
          (*FilledLengthPtr)++;
#endif
          resultSetDtcFilter = Dem_SetDTCFilter(
                                 (uint8)(ReqStatusMask & StatusMask),
                                 DEM_DTC_KIND_ALL_DTCS,
                                 DEM_DTC_FORMAT_UDS,
                                 DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                 DEM_FILTER_WITH_SEVERITY_NO,
                                 DEM_SEVERITY_NO_SEVERITY,
                                 DEM_FILTER_FOR_FDC_NO);

          if ( resultSetDtcFilter == DEM_FILTER_ACCEPTED )
          {
            Dem_ReturnGetNumberOfFilteredDTCType resultFilteredDTC;

/* if Paged buffer handling enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)

            /* Get the number of filtered DTCs */
            resultFilteredDTC = Dem_GetNumberOfFilteredDTC(
                                  &DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount);
            if (resultFilteredDTC == DEM_NUMBER_OK)
            {
              /* update the total response length for the filtered DTCs */
              pMsgContext->resDataLen +=
                (PduLengthType) (DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount *
                DCM_DTC_AND_STATUS_SNGL_RCD_LEN);
              serviceProcessStatus = DCM_E_DONE;
            }
            /* if response is pending */
            else if (resultFilteredDTC == DEM_NUMBER_PENDING)
            {
              serviceProcessStatus = DCM_E_PENDING;
            }
            else /* Getting the number of DTCs failed */
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
              serviceProcessStatus = DCM_E_DONE;
            }

            /* if no error occured till now and filled length is less than total response length */
            /* Deviation MISRA-2 */
            if ((serviceProcessStatus == DCM_E_DONE)
               && ((curHsmInfo->negativeResponseCode == DCM_E_OK)
               && (*FilledLengthPtr < pMsgContext->resDataLen)))
            {
              /* set the paged processing status to ON */
              Dcm_DspInternal_EnableProcessPage(pMsgContext,
                                                DCM_PROCESS_PAGE_DTC_BY_STATUS_MASK_FUNC_ID);

              /* indicate start of paged processing */
              Dcm_DsdInternal_StartPagedProcessing(pMsgContext);

              /* set serviceProcessStatus to pending so that DSP state machine
              will stay in state 'ApplQueried', so that CallStdService() will be
              called to continue paged processing */
              serviceProcessStatus = DCM_E_PROCESS_PAGE;
            }

#else

            Dem_ReturnGetNextFilteredDTCType resultGetNextDtc = DEM_FILTERED_NO_MATCHING_DTC;
            uint8 dtcStatusMask;
            uint32 reqDtc;
            uint16 numFilteredDTCs;
            uint16_least loopCnt = 0U;

            resultFilteredDTC = Dem_GetNumberOfFilteredDTC(&numFilteredDTCs);

            if ( resultFilteredDTC == DEM_NUMBER_OK )
            {
              /* loop until no further matching DTC is returned or response buffer becomes too
              * small */
              do
              {
                /* check if buffer size suffices */
              if ((pMsgContext->resDataLen + (PduLengthType)4U) <= pMsgContext->resMaxDataLen)
                {
                  /* gather DTC informations */
                  resultGetNextDtc = Dem_GetNextFilteredDTC(&reqDtc, &dtcStatusMask);

                  if (resultGetNextDtc == DEM_FILTERED_OK)
                  {
                    /* append 4 bytes to the response buffer */
                    /* Deviation MISRA-1 */
                    *dataPtr = (uint8)(reqDtc >> 16U);
                    dataPtr++;
                    /* Deviation MISRA-1 */
                    *dataPtr = (uint8)(reqDtc >> 8U);
                    dataPtr++;
                    /* Deviation MISRA-1 */
                    *dataPtr = (uint8)(reqDtc);
                    dataPtr++;
                    /* Deviation MISRA-1 */
                    *dataPtr = (Dcm_MsgItemType)dtcStatusMask;
                    dataPtr++;

                    /* update response length */
                    pMsgContext->resDataLen += (PduLengthType)4U;
                  }
                }
                else
                {
                  Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
                }

                ++loopCnt;
              }
              while ((resultGetNextDtc != DEM_FILTERED_NO_MATCHING_DTC)
                      && (loopCnt < numFilteredDTCs));
              serviceProcessStatus = DCM_E_DONE;
            }
            else if ( resultFilteredDTC == DEM_NUMBER_PENDING )
            {
              serviceProcessStatus = DCM_E_PENDING;
            }
            else /* Get number of filtered DTC failed */
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
              serviceProcessStatus = DCM_E_DONE;
            }
#endif /* #if DCM_PAGEDBUFFER_ENABLED */
          }
          else /* Wrong Filter */
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        /* if buffer is too small for the response data */
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
    }
    /* error occured while getting DTCStatusAvailabiityMask */
    else
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  /* request data length is invalid */
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REPORTDTCBYSTATUSMASK_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)
/* This is the UDS service 0x19-0x03 handler */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDtcSnapshotRecordIdentification_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
   /* Get the current context info */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDIDENTIFICATION_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);

  /* Check the request data length */
  if ( pMsgContext->reqDataLen == 0U )
  {
    Dem_ReturnSetFilterType resultFreezeRecord;

    /* if Paged buffer handling enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
    P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
    &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);

    /* Get the number of filtered freeze frame records */
    resultFreezeRecord = Dem_SetFreezeFrameRecordFilter(DEM_DTC_FORMAT_UDS,
                         &DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount);
    if (resultFreezeRecord == DEM_FILTER_ACCEPTED)
    {
      /* update the total response length for the filtered DTCs */
      pMsgContext->resDataLen +=
                (PduLengthType) (DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount *
                DCM_DTC_SNAPSHOT_SNGL_RCD_LEN);
      serviceProcessStatus = DCM_E_DONE;
    }
    /* Getting the number of filtered freeze frame records failed */
    else
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }

    /* if no error occured till now and filled length is less than total response length */
    /* Deviation MISRA-2 */
    if ((serviceProcessStatus == DCM_E_DONE)
        && ((curHsmInfo->negativeResponseCode == DCM_E_OK)
        && (*FilledLengthPtr < pMsgContext->resDataLen)))
    {
      /* set the paged processing status to ON */
      Dcm_DspInternal_EnableProcessPage(pMsgContext,
                                        DCM_PROCESS_PAGE_DTC_SNAPSHOT_IDENTIFICATION);

      /* indicate start of paged processing */
      Dcm_DsdInternal_StartPagedProcessing(pMsgContext);

      /* set serviceProcessStatus to pending so that DSP state machine
      will stay in state 'ApplQueried', so that CallStdService() will be
      called to continue paged processing */
      serviceProcessStatus = DCM_E_PROCESS_PAGE;
    }
#else
    Dem_ReturnGetNextFilteredDTCType resultGetNextRecord = 0U;
    /* cache data pointer */
    Dcm_MsgType dataPtr = &pMsgContext->resData[1];
    uint32 reqDTC = 0U;
    uint8 dtcSnapShotRecordNum = 0U;
    resultFreezeRecord =
      Dem_SetFreezeFrameRecordFilter(DEM_DTC_FORMAT_UDS,
                                     &DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount);
    if ( resultFreezeRecord == DEM_FILTER_ACCEPTED )
    {
      /* loop until no further freeze frame record is returned or response buffer becomes too
       * small */
      do
      {
        /* check if buffer size suffices */
        if ((pMsgContext->resDataLen + (PduLengthType)4U) <= pMsgContext->resMaxDataLen)
        {
          /* gather DTC record informations */
          resultGetNextRecord = Dem_GetNextFilteredRecord(&reqDTC, &dtcSnapShotRecordNum);
          if(resultGetNextRecord == DEM_FILTERED_OK)
          {
            /* copy DTC value to diagnostic response data */
            /* append 4 bytes to the response buffer */
            /* Deviation MISRA-1 */
            *dataPtr = (uint8)(reqDTC >> 16U);
            dataPtr++;
            /* Deviation MISRA-1 */
            *dataPtr = (uint8)(reqDTC >> 8U);
            dataPtr++;
            /* Deviation MISRA-1 */
            *dataPtr = (uint8)(reqDTC);
            dataPtr++;
            /* Deviation MISRA-1 */
            *dataPtr = (Dcm_MsgItemType)dtcSnapShotRecordNum;
            dataPtr++;

            /* update response length */
            pMsgContext->resDataLen += (PduLengthType)DCM_DTC_SNAPSHOT_SNGL_RCD_LEN;
            serviceProcessStatus = DCM_E_DONE;
            /* update the remaining DTC count to be sent as response */
            DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount--;
          }
          else
          {
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
        }
      }
      /* Deviation MISRA-2 */
      while ((resultGetNextRecord == DEM_FILTERED_OK) &&
             (DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount > 0)
              && (curHsmInfo->negativeResponseCode == DCM_E_OK));

      if (resultGetNextRecord == DEM_FILTERED_PENDING)
      {
        serviceProcessStatus = DCM_E_PENDING;
      }
    }
    else /* Sets a freeze frame record filter failed */
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
#endif
  }
  /* if diagnostic request data length is invalid */
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDIDENTIFICATION_SSVCH_EXIT(serviceProcessStatus,
                                                                       OpStatus,
                                                                       pMsgContext);
  return serviceProcessStatus;
}
#endif  /*  #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)  */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
/* This is the UDS service 0x19-0x04 handler */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDtcSnapshotRecordByDtcNumber_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

  /* Check the request data length */
  if ( pMsgContext->reqDataLen == 4U )
  {
    Dcm_StatusType errorCode;
    uint32 DTC;

    /* Get Snapshot Record number from request */
    uint8 snapShotRecNum = pMsgContext->reqData[3];

    /* Update response buffer with DTC and DTC status */
    errorCode = Dcm_DspInternal_DemReportStatusByte(pMsgContext, &DTC);

    if ( errorCode == DCM_E_OK )
    {
/* if Paged buffer handling enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      /* Total size of freeze frame records */
      PduLengthType TotalFFSize = 0U;

      /* if record number = 0xFF , Total size of all available freeze frame
         records will be calculated */
      /* if snapshot record number >= 0x00 &&  < 0xFF individual freeze frame size will be
         calculated */
      /* Get the size of freeze frame */
      errorCode = Dcm_DspInternal_DemGetSizeOfFreezeFrame(
                    DTC,
                    snapShotRecNum,
                    &TotalFFSize,
                    pMsgContext);
      /* if response is pending */
      if ( errorCode == DCM_E_PENDING )
      {
        serviceProcessStatus = DCM_E_PENDING;
      }
      else
      {
        serviceProcessStatus = DCM_E_DONE;
            /* do nothing. NRC is allready set in
                    Dcm_DspInternal_DemGetSizeOfFreezeFrame() */
      }

      {
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
        uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

        P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
          &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);

        /* Get the current context info */
        CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

        /* if total size of all the freeze frames are calculated successfully */
        if ((serviceProcessStatus == DCM_E_DONE)
           && (curHsmInfo->negativeResponseCode == DCM_E_OK))
        {
          /* update the response length */
          pMsgContext->resDataLen += TotalFFSize;

          /* if filled length is less than total response length */
          if (*FilledLengthPtr < pMsgContext->resDataLen)
          {
            /* set the paged processing status to ON */
            Dcm_DspInternal_EnableProcessPage(pMsgContext,
                                              DCM_PROCESS_PAGE_DTC_SNAPSHOT_RECORD);
            /* Indicate to start paged processing */
            Dcm_DsdInternal_StartPagedProcessing(pMsgContext);

            /* Set the DTC record number from which processing needs to be done
               while reading all freeze frame Records */
            DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum = 0x00U;

            /* Store the requested DTC Snapshot record number for paged processing */
            DCM_READ_DTC_INFO_CONTEXT(instIdx).ReqRecNum = snapShotRecNum;

            /* set serviceProcessStatus to 'PENDING' so that DSP state machine
            will stay in state 'ApplQueried', so that CallStdService() will be
            called to continue paged processing */
            serviceProcessStatus = DCM_E_PROCESS_PAGE;
          }
        }
      }

#else
      /* Total size of freeze frame records */
      PduLengthType TotalFFSize = 0U;
      /* disable DTC record update */
      serviceProcessStatus = Dcm_DspInternal_DemDisableDTCRecordUpdate(DTC, pMsgContext);

      if ( serviceProcessStatus == DCM_E_OK )
      {
        /* if record number = 0xFF , Total size of all available freeze frame
           records will be calculated */
        /* if snapshot record number >= 0x00 &&  < 0xFF individual freeze frame size will be
           calculated */

        /* Get the size of freeze frame */
        errorCode = Dcm_DspInternal_DemGetSizeOfFreezeFrame(
                      DTC,
                      snapShotRecNum,
                      &TotalFFSize,
                      pMsgContext);
        if ( errorCode == DCM_E_OK )
        {
          if (TotalFFSize < (pMsgContext->resMaxDataLen - pMsgContext->resDataLen))
          {
            /* Read all UDS Snapshot Records */
            if ( snapShotRecNum == 0xFFU )
            {
              uint8_least curSnapShotRecNum;
              /* Process all freeze frames 0x00 to 0xFE */
              for ( curSnapShotRecNum = 0x00U; curSnapShotRecNum < 0xFFU; curSnapShotRecNum++ )
              {
                errorCode = Dcm_DspInternal_DemGetSnapShotRecord(DTC,
                                       (uint8)curSnapShotRecNum,
                                       pMsgContext->resMaxDataLen - pMsgContext->resDataLen,
                                       pMsgContext,
                                       &pMsgContext->resDataLen);

                if ( errorCode == DCM_E_PENDING )
                {
                  serviceProcessStatus = DCM_E_PENDING;
                  break;
                }
                /* If Dcm_DspInternal_DemGetSnapShotRecord() returns wrong record number,
                 * execution should continue, since a valid record may exist after this.
                 * For all other errors, exit loop. */
                else if (( errorCode != DCM_E_OK ) && (errorCode != DCM_E_WRONG_RECORD_NUM))
                {
                  serviceProcessStatus = DCM_E_DONE;
                  /* Deviation MISRA-5 */
                  break;
                }
                else
                {
                  serviceProcessStatus = DCM_E_DONE;
                  /* do nothing */
                }
              }
            }
            /* Read one specific UDS SnapShot Record */
            else
            {
              errorCode = Dcm_DspInternal_DemGetSnapShotRecord(DTC,
                                       snapShotRecNum,
                                       pMsgContext->resMaxDataLen - pMsgContext->resDataLen,
                                       pMsgContext,
                                       &pMsgContext->resDataLen);
              /* if response is pending */
              if ( errorCode == DCM_E_PENDING )
              {
                serviceProcessStatus = DCM_E_PENDING;
              }
              else if (errorCode == DCM_E_WRONG_RECORD_NUM)
              {
                /* if wrong record number was passed */
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
                serviceProcessStatus = DCM_E_DONE;
              }
              else
              {
                serviceProcessStatus = DCM_E_DONE;
              }
            }
          }
          else
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        else if (errorCode == DCM_E_PENDING)
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }

        if (errorCode != DCM_E_PENDING)
        {
          /* Enable DTC record update */
          Dcm_DspInternal_DemEnableDTCRecordUpdate(pMsgContext);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /* Do nothing as return value is already set */
      }

#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
    }
    else if (errorCode == DCM_E_PENDING)
    {
      serviceProcessStatus = DCM_E_PENDING;
    }
    else
    {
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  /* if diagnostic request data length is invalid */
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REPORTDTCSNAPSHOTRECORDBYDTCNUMBER_SSVCH_EXIT(serviceProcessStatus,
                                                                    OpStatus,
                                                                    pMsgContext);
  return serviceProcessStatus;
}

#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
/* Enables DTC record update */
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_DemEnableDTCRecordUpdate(
            P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType resultEnableDTCUpdate = E_OK;
  DBG_DCM_DSPINTERNAL_DEMENABLEDTCRECORDUPDATE_ENTRY(pMsgContext);

  /* Enable DTC record update */
  resultEnableDTCUpdate = Dem_EnableDTCRecordUpdate();

  if (E_OK != resultEnableDTCUpdate)
  {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if (E_NOT_OK != resultEnableDTCUpdate)
    {
      DCM_DET_REPORT_ERROR(DCM_SVCID_ENABLEDTCRECORDUPDATE,
                           DCM_E_INTERFACE_RETURN_VALUE);
    }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
  }

  DBG_DCM_DSPINTERNAL_DEMENABLEDTCRECORDUPDATE_EXIT(pMsgContext);
}

/* Disables DTC record update */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DemDisableDTCRecordUpdate(
 uint32 DTC,
 P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Dem_ReturnDisableDTCRecordUpdateType resultDisableDTCUpdate;
  DBG_DCM_DSPINTERNAL_DEMDISABLEDTCRECORDUPDATE_ENTRY(DTC,pMsgContext);

  /* disable DTC record update */
  resultDisableDTCUpdate = Dem_DisableDTCRecordUpdate(DTC, DEM_DTC_ORIGIN_PRIMARY_MEMORY);

  if ( resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_OK )
  {
    serviceProcessStatus = DCM_E_OK;
  }
  else if(resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_PENDING)
  {
    serviceProcessStatus = DCM_E_PENDING;
  }
  else
  {
    /* wrong DTC or Wrong DTC origin */
    if((resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_WRONG_DTC) ||
       (resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN))
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
    /* error occured while disabling DTC record update */
    else
    {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      DCM_DET_REPORT_ERROR(DCM_SVCID_DISABLEDTCRECORDUPDATE, DCM_E_INTERFACE_RETURN_VALUE);
#endif
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
      serviceProcessStatus = DCM_E_DONE;
    }
  }

  DBG_DCM_DSPINTERNAL_DEMDISABLEDTCRECORDUPDATE_EXIT(DTC,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_OFF) */
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
/* This is the UDS service 0x19-0x06 handler */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDtcExtendedDataRecordByDtcNumber_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

  /* check if the request data length is valid */
  if ( pMsgContext->reqDataLen == 4U )
  {
    uint32 DTC;
    Dcm_StatusType errorCode;

    /* Get Extended Data Record number from request */
    uint8 extRecNum = pMsgContext->reqData[3];

    /* update the response buffer with DTC and status */
    errorCode = Dcm_DspInternal_DemReportStatusByte(pMsgContext, &DTC);

    if ( errorCode == DCM_E_OK )
    {
      PduLengthType TotalExtDataSize = 0U;

    /* if Paged buffer handling enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
      if (extRecNum == 0xFFU)
      {
#if (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF)
        /* Read all Extended Data Records from 0x01..0xEF */
        uint8_least curExtRecNum;
        PduLengthType ExtDataSize = 0U;

       /* Process Extended Data Records from 0x01..0xEF. 0xF0 to 0xFE are reserved */
        for (curExtRecNum = 0x01U; curExtRecNum < 0xF0U; curExtRecNum++)
        {
          errorCode = Dcm_DspInternal_DemGetSizeOfExtDataRecord(DTC, (uint8)curExtRecNum,
                                                                &ExtDataSize);
          if (errorCode == DCM_E_OK)
          {
            /* Increment ExtDataSize, since in response message for each DTCExtendedDataRecord[]
             * there is a DTCExtendedDataRecordNumber (1 byte). Be aware that if the DTC is not
             * stored in error memory there still will be a positive response but the ExtDataSize
             * will be set to zero. Do not account for the DTCExtendedDataRecordNumber byte in that
             * case as it is not present.
             * (see comment on on Dem076 in AUTOSAR_SWS_DiagnosticEventManager.reqm) */
            if (ExtDataSize > 0U)
            {
              ExtDataSize++;
            }

            if (ExtDataSize <= pMsgContext->resMaxDataLen)
            {
              TotalExtDataSize += ExtDataSize;
            }
            else
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
              serviceProcessStatus = DCM_E_DONE;
              /* Deviation MISRA-5 */
              break;
            }
          }
          /* if response pending */
          else if (errorCode == DCM_E_PENDING)
          {
            serviceProcessStatus = DCM_E_PENDING;
            /* Deviation MISRA-5 */
            break;
          }
           /* If errorCode == DCM_E_NOT_OK. This occures when
            * either DEM_GET_SIZEOFEDRBYDTC_W_DTCOR or  DEM_GET_SIZEOFEDRBYDTC_W_DTC
            * has been retuned from Dem_GetSizeOfExtendedDataRecordByDTC().
            *
            * Set negative response and indicate process as finished */
          else if (errorCode != DCM_E_WRONG_RECORD_NUM)
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;
            /* Deviation MISRA-5 */
            break;
          }
          else
          {
            /* Here the error code = DCM_E_WRONG_RECORD_NUM, continue the loop,
             * there may exist other records which has correct record numbers. */
          }
        }
         /* If recieved all records, indicate processing status finished */
        if (0xF0U == curExtRecNum)
        {
          serviceProcessStatus = DCM_E_DONE;
        }
#else /* (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF) */
        /* If Optimization is enabled */
        errorCode = Dcm_DspInternal_DemGetSizeOfExtDataRecord(DTC, extRecNum, &TotalExtDataSize);
        if (DCM_E_OK == errorCode)
        {
          serviceProcessStatus = DCM_E_DONE;
        }
        else if (DCM_E_PENDING == errorCode)
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
#endif  /* (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF) */
      }
      else if ( (extRecNum > 0x00U) && (extRecNum < 0xF0U) )
      {
        /* get size of extended data record */
        errorCode = Dcm_DspInternal_DemGetSizeOfExtDataRecord(DTC, extRecNum, &TotalExtDataSize);
        if ( errorCode == DCM_E_OK )
        {
#if (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF)
          /* Increment ExtDataSize, since in response message for each DTCExtendedDataRecord[]
           * there is a DTCExtendedDataRecordNumber (1 byte). Be aware that if the DTC is not
           * stored in error memory there still will be a positive response but the ExtDataSize
           * will be set to zero. Do not account for the DTCExtendedDataRecordNumber byte in that
           * case as it is not present.
           * (see comment on on Dem076 in AUTOSAR_SWS_DiagnosticEventManager.reqm) */
          if (TotalExtDataSize > 0U)
          {
            TotalExtDataSize++;
          }
#endif /* (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF) */
          if (TotalExtDataSize > pMsgContext->resMaxDataLen)
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
            serviceProcessStatus = DCM_E_DONE;
          }
          else
          {
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        else if ( errorCode == DCM_E_PENDING )
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      /* Requested Extended Data Record Number is not within allowed range */
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
      }

      {
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
        uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
        /* Get the current context info */
        CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

        /* if total size of all the freeze frames are calculated successfully */
        if ((serviceProcessStatus == DCM_E_DONE)
            && (curHsmInfo->negativeResponseCode == DCM_E_OK))
        {
          /* filled length in response buffer */
          P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
            &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);

          /* Update the response length */
          pMsgContext->resDataLen += TotalExtDataSize;

          /* if filled length is less than total response length */
          if (*FilledLengthPtr < pMsgContext->resDataLen)
          {
            /* Set process page enable flag and function the needs to be called
               during paged processing */
            Dcm_DspInternal_EnableProcessPage(pMsgContext,
                                              DCM_PROCESS_PAGE_DTC_EXT_DATA_RECORD);
            /* Start paged processing */
            Dcm_DsdInternal_StartPagedProcessing(pMsgContext);

            /* Set the DTC record number from which processing needs to be done
               while reading all Extended Data Records */
            DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum = 0x01U;

            /* Stores the requested Extended data record for paged processing */
            DCM_READ_DTC_INFO_CONTEXT(instIdx).ReqRecNum = extRecNum;

            /* set serviceProcessStatus to 'PENDING' so that DSP state machine
            will stay in state 'ApplQueried', so that CallStdService() will be
            called to continue paged processing */
            serviceProcessStatus = DCM_E_PROCESS_PAGE;
          }
        }
      }
#else   /* If Page buffering disabled */
      Dcm_StatusType resGetExtDataRecord;

      /* Disable DTC record update */
      Dem_ReturnDisableDTCRecordUpdateType resultDisableDTCUpdate =
                                    Dem_DisableDTCRecordUpdate(DTC, DEM_DTC_ORIGIN_PRIMARY_MEMORY);

      if (resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_OK )
      {
        Std_ReturnType resultEnableDTCUpdate = E_OK;

        if (extRecNum == 0xFFU)
        {
          serviceProcessStatus = Dcm_DspInternal_DemGetAllExtDataRecordsPageOff(DTC, pMsgContext);
        }
        else if ( (extRecNum > 0x00U) && (extRecNum < 0xF0U) )
        {
          /* get size of extended data record */
          errorCode = Dcm_DspInternal_DemGetSizeOfExtDataRecord(DTC, extRecNum, &TotalExtDataSize);
          if (errorCode == DCM_E_OK)
          {
#if (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF)
            /* Increment ExtDataSize, since in response message for each DTCExtendedDataRecord[]
             * there is a DTCExtendedDataRecordNumber (1 byte). Be aware that if the DTC is not
             * stored in error memory there still will be a positive response but the ExtDataSize
             * will be set to zero. Do not account for the DTCExtendedDataRecordNumber byte in that
             * case as it is not present.
             * (see comment on on Dem076 in AUTOSAR_SWS_DiagnosticEventManager.reqm) */
            if (TotalExtDataSize > 0U)
            {
              TotalExtDataSize++;
            }
#endif /* #if (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF) */
            /* check if buffer size suffices */
            if (TotalExtDataSize < (pMsgContext->resMaxDataLen - pMsgContext->resDataLen))
            {
              resGetExtDataRecord = Dcm_DspInternal_DemGetExtDataRecord(
                                       DTC,
                                       extRecNum,
                                       pMsgContext->resMaxDataLen - pMsgContext->resDataLen,
                                       pMsgContext,
                                       &pMsgContext->resDataLen);
              /* if response is pending */
              if (resGetExtDataRecord == DCM_E_PENDING)
              {
                serviceProcessStatus = DCM_E_PENDING;
              }
              else if (resGetExtDataRecord == DCM_E_WRONG_RECORD_NUM)
              {
                /* if wrong record number was passed */
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
                serviceProcessStatus = DCM_E_DONE;
              }
              else
              {
                serviceProcessStatus = DCM_E_DONE;
              }
            }
            else
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
              serviceProcessStatus = DCM_E_DONE;
            }
          }
          else if (errorCode == DCM_E_PENDING)
          {
            serviceProcessStatus = DCM_E_PENDING;
          }
          else
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        /* Requested Extended Data Record Number is not within allowed range */
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }

        resultEnableDTCUpdate = Dem_EnableDTCRecordUpdate();

        if (E_OK != resultEnableDTCUpdate)
        {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
          if (E_NOT_OK != resultEnableDTCUpdate)
          {
            DCM_DET_REPORT_ERROR(DCM_SVCID_ENABLEDTCRECORDUPDATE,
                                                                DCM_E_INTERFACE_RETURN_VALUE);
          }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else if(resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_PENDING)
      {
        serviceProcessStatus = DCM_E_PENDING;
      }
      else
      {
        /* wrong DTC or Wrong DTC origin */
        if((resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_WRONG_DTC) ||
           (resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN))
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
        /* error occured while disabling DTC record update */
        else
        {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
          DCM_DET_REPORT_ERROR(DCM_SVCID_DISABLEDTCRECORDUPDATE, DCM_E_INTERFACE_RETURN_VALUE);
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */
    }
    else if (errorCode == DCM_E_PENDING)
    {
      serviceProcessStatus = DCM_E_PENDING;
    }
    else
    {
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REPORTDTCEXTENDEDDATARECORDBYDTCNUMBER_SSVCH_EXIT(serviceProcessStatus,
                                                                        OpStatus,
                                                                        pMsgContext);
  return serviceProcessStatus;
}

#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetAllExtDataRecordsPageOff(
  uint32 DTC,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
  uint8_least curExtRecNum;
  PduLengthType TotalExtDataSize = 0U;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Dcm_StatusType errorCode;
  Dcm_StatusType resGetExtDataRecord;
#if (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF)
  PduLengthType ExtDataSize = 0U;
#endif

  DBG_DCM_DSPINTERNAL_DEMGETALLEXTDATARECORDSPAGEOFF_ENTRY(DTC, pMsgContext);

#if (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF)
  /* Process Extended Data Records from 0x01..0xEF. 0xF0 to 0xFE are reserved */
  for (curExtRecNum = 0x01U; curExtRecNum < 0xF0U; curExtRecNum++ )
  {
    /* Get size of extended data record. If optimization has disabled in Dcm and Dem
     * then, Dem provides the size of Extended data record number which doesnot
     * contains the extended data bytes size (According to AUTOSAR R4.0.3). */
    errorCode = Dcm_DspInternal_DemGetSizeOfExtDataRecord(DTC, (uint8)curExtRecNum, &ExtDataSize);
    if (errorCode == DCM_E_OK)
    {
      /* Increment ExtDataSize, since in response message for each DTCExtendedDataRecord[]
       * there is a DTCExtendedDataRecordNumber (1 byte). Be aware that if the DTC is not
       * stored in error memory there still will be a positive response but the ExtDataSize
       * will be set to zero. Do not account for the DTCExtendedDataRecordNumber byte in that
       * case as it is not present.
       * (see comment on on Dem076 in AUTOSAR_SWS_DiagnosticEventManager.reqm) */
      if (ExtDataSize > 0U)
      {
        ExtDataSize++;
      }

      if (ExtDataSize <= pMsgContext->resMaxDataLen )
      {
        TotalExtDataSize += ExtDataSize;
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
        serviceProcessStatus = DCM_E_DONE;
        break;
      }
    }
    /* if response pending */
    else if (errorCode == DCM_E_PENDING )
    {
      serviceProcessStatus = DCM_E_PENDING;
      /* Deviation MISRA-5 */
      break;
    }
     /* If errorCode == DCM_E_NOT_OK. This occures when
      * either DEM_GET_SIZEOFEDRBYDTC_W_DTCOR or  DEM_GET_SIZEOFEDRBYDTC_W_DTC
      * has been retuned from Dem_GetSizeOfExtendedDataRecordByDTC(). */
    else if (errorCode == DCM_E_NOT_OK)
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
      /* Deviation MISRA-5 */
      break;
    }
    else
    {
      /* Here the error code = DCM_E_WRONG_RECORD_NUM, continue the loop,
       * there may exist other records which has correct record numbers. */
    }
  }
   /* Traversed all records, proceed to process the individual record
    * by calling Dcm_DspInternal_DemGetExtDataRecord() */
  if ( (curExtRecNum == 0xF0U ) && (serviceProcessStatus == DCM_E_ABORT) )
  {
    /* 0xF0 to 0xFD are reserved; 0xFE = all OBD records; */
    for (curExtRecNum = 0x01U; curExtRecNum < 0xF0U; curExtRecNum++)
    {
      resGetExtDataRecord = Dcm_DspInternal_DemGetExtDataRecord(
                               DTC,
                               (uint8)curExtRecNum,
                               pMsgContext->resMaxDataLen - pMsgContext->resDataLen,
                               pMsgContext,
                               &pMsgContext->resDataLen);

      /* if response is pending */
      if (resGetExtDataRecord == DCM_E_PENDING)
      {
        serviceProcessStatus = DCM_E_PENDING;
        /* Deviation MISRA-5 */
        break;
      }
      /* If Dcm_DspInternal_DemGetExtDataRecord() returns wrong
       * record number, execution should continue, since a valid record
       * may exist after this. All other case Dcm_DspInternal_DemGetExtDataRecord
       * returns DCM_E_NOT_OK and a negative response was sent already in wrapper
       * Dcm_DspInternal_DemGetExtDataRecord(), so break the loop and set the process
       * as finished */
      else if (resGetExtDataRecord == DCM_E_NOT_OK)
      {
        serviceProcessStatus = DCM_E_DONE;
        /* Deviation MISRA-5 */
        break;
      }
      else
      {
        /* do nothing: Continue the loop for DCM_E_OK and
         * DCM_E_WRONG_RECORD_NUM return
         * from Dcm_DspInternal_DemGetExtDataRecord() */
      }
    }
    /* Recieved all records succesfully */
    if (curExtRecNum == 0xF0U)
    {
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    /* Do nothing:
     * Dcm_DspInternal_DemGetSizeOfExtDataRecord() might have
     * returned a PENDING or DCM_E_NOT_OK or insufficient buffer size.
     * 1. returned a PENDING : serviceProcessStatus was set to PENDING so
     *    nothing to do here
     * 2. DCM_E_NOT_OK or insufficient buffer size: The negative response flag
     *    should have set and the response will be send at a common place.
     *    So nothig to do here */
  }
#else  /* #if (DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION == STD_OFF) */
  /* Get size of extended data record. If optimization has enabled in Dcm and Dem
   * then, Dem provides the size of Extended data record number along with the extended
   * data bytes size (According to AUTOSAR R4.1). */
  errorCode = Dcm_DspInternal_DemGetSizeOfExtDataRecord(DTC, (uint8)0xFFU, &TotalExtDataSize);

  if (errorCode == DCM_E_OK)
  {
    /* check if buffer size suffices */
    if (TotalExtDataSize < (pMsgContext->resMaxDataLen - pMsgContext->resDataLen))
    {
      /* 0xF0 to 0xFD are reserved; 0xFE = all OBD records; */
      for (curExtRecNum = 0x01U; curExtRecNum < 0xF0U; curExtRecNum++)
      {
        resGetExtDataRecord = Dcm_DspInternal_DemGetExtDataRecord(
                                 DTC,
                                 (uint8)curExtRecNum,
                                 pMsgContext->resMaxDataLen - pMsgContext->resDataLen,
                                 pMsgContext,
                                 &pMsgContext->resDataLen);

        /* if response is pending */
        if (resGetExtDataRecord == DCM_E_PENDING)
        {
          serviceProcessStatus = DCM_E_PENDING;
          /* Deviation MISRA-5 */
          break;
        }
        /* If Dcm_DspInternal_DemGetExtDataRecord() returns wrong
         * record number, execution should continue, since a valid record
         * may exist after this. All other case Dcm_DspInternal_DemGetExtDataRecord
         * returns DCM_E_NOT_OK and a negative response was sent already in wrapper
         * Dcm_DspInternal_DemGetExtDataRecord(), so break the loop and set the process
         * as finished */
        else if (resGetExtDataRecord == DCM_E_NOT_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
          /* Deviation MISRA-5 */
          break;
        }
        else
        {
          /* do nothing: Continue the loop for DCM_E_OK and
           * DCM_E_WRONG_RECORD_NUM return
           * from Dcm_DspInternal_DemGetExtDataRecord() */
        }
      }
      /* Recieved all records succesfully */
      if (curExtRecNum == 0xF0U)
      {
        serviceProcessStatus = DCM_E_DONE;
      }
    }
    else    /* buffer size exceeds */
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else if ( errorCode == DCM_E_PENDING )
  {
    serviceProcessStatus = DCM_E_PENDING;
  }
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
#endif

  DBG_DCM_DSPINTERNAL_DEMGETALLEXTDATARECORDSPAGEOFF_EXIT(serviceProcessStatus, DTC, pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_OFF) */
#endif /*#if DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)
/* This is the UDS service 0x19-0x0A handler */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportSupportedDtcs_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType resultGetStatusMask = E_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
    &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);

   /* Get the current context info */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
#endif/* #if DCM_PAGEDBUFFER_ENABLED */

  DBG_DCM_DSPINTERNAL_REPORTSUPPORTEDDTCS_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);
  /* check the request data length */
  if (pMsgContext->reqDataLen == 0U)
  {
    uint8 StatusMask;
    resultGetStatusMask = Dem_GetDTCStatusAvailabilityMask(&StatusMask);
    if (resultGetStatusMask == E_OK)
    {
      /* If DTCStatusAvailabilityMask is equal to 0 the Dcm shall response positively with 0 DTC */
      if (StatusMask == 0U)
      {
        /* update response data with Status Mask */
        pMsgContext->resData[1] = StatusMask;
        pMsgContext->resDataLen++;
        serviceProcessStatus = DCM_E_DONE;
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        (*FilledLengthPtr)++;
#endif
      }
      else
      {
        /* check the buffer is big enough to hold DTCStatusAvailabilityMask  */
        if ((pMsgContext->resDataLen + (PduLengthType)1U) <= pMsgContext->resMaxDataLen)
        {
          Dem_ReturnSetFilterType resultSetDtcFilter;
          /* cache data pointer */
          Dcm_MsgType dataPtr = &pMsgContext->resData[1];

          /* add status mask to response buffer and update the response length and filled length of
           * buffer */
          /* Deviation MISRA-1 */
          *dataPtr = (uint8)StatusMask;
          dataPtr++;
          pMsgContext->resDataLen += (PduLengthType)1U;
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
          (*FilledLengthPtr)++;
#endif
          resultSetDtcFilter = Dem_SetDTCFilter(
                                 (uint8)(DCM_REPORT_ALLSUPPORTEDDTC),
                                 DEM_DTC_KIND_ALL_DTCS,
                                 DEM_DTC_FORMAT_UDS,
                                 DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                                 DEM_FILTER_WITH_SEVERITY_NO,
                                 DEM_SEVERITY_NO_SEVERITY,
                                 DEM_FILTER_FOR_FDC_NO);

          if ( resultSetDtcFilter == DEM_FILTER_ACCEPTED )
          {
            Dem_ReturnGetNumberOfFilteredDTCType resultFilteredDTC;

  /* if Paged buffer handling enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)

            /* Get the number of filtered DTCs */
            resultFilteredDTC = Dem_GetNumberOfFilteredDTC(
                                  &DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount);
            if (resultFilteredDTC == DEM_NUMBER_OK)
            {
              /* update the total response length for the filtered DTCs */
              pMsgContext->resDataLen +=
                (PduLengthType) (DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount *
                DCM_DTC_AND_STATUS_SNGL_RCD_LEN);
              serviceProcessStatus = DCM_E_DONE;
            }
            /* if response is pending */
            else if (resultFilteredDTC == DEM_NUMBER_PENDING)
            {
              serviceProcessStatus = DCM_E_PENDING;
            }
            else /* Getting the number of DTCs failed */
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
              serviceProcessStatus = DCM_E_DONE;
            }

            /* if no error occured till now and filled length is less than total response length */
            /* Deviation MISRA-2 */
            if ((serviceProcessStatus == DCM_E_DONE)
               && ((curHsmInfo->negativeResponseCode == DCM_E_OK)
               && (*FilledLengthPtr < pMsgContext->resDataLen)))
            {
              /* set the paged processing status to ON */
              Dcm_DspInternal_EnableProcessPage(pMsgContext,
                                                DCM_PROCESS_PAGE_DTC_BY_STATUS_MASK_FUNC_ID);

              /* indicate start of paged processing */
              Dcm_DsdInternal_StartPagedProcessing(pMsgContext);

              /* set serviceProcessStatus to pending so that DSP state machine
              will stay in state 'ApplQueried', so that CallStdService() will be
              called to continue paged processing */
              serviceProcessStatus = DCM_E_PROCESS_PAGE;
            }

#else

            Dem_ReturnGetNextFilteredDTCType resultGetNextDtc = DEM_FILTERED_NO_MATCHING_DTC;
            uint8 dtcStatusMask;
            uint32 reqDtc;
            uint16 numFilteredDTCs;
            uint16_least loopCnt = 0U;

            resultFilteredDTC = Dem_GetNumberOfFilteredDTC(&numFilteredDTCs);

            if ( resultFilteredDTC == DEM_NUMBER_OK )
            {
              /* loop until no further matching DTC is returned or response buffer becomes too
              * small */
              do
              {
                /* check if buffer size suffices */
                if ((pMsgContext->resDataLen + (PduLengthType)4U) <= pMsgContext->resMaxDataLen)
                {
                  /* gather DTC informations */
                  resultGetNextDtc = Dem_GetNextFilteredDTC(&reqDtc, &dtcStatusMask);

                  if (resultGetNextDtc == DEM_FILTERED_OK)
                  {
                    /* append 4 bytes to the response buffer */
                    /* Deviation MISRA-1 */
                    *dataPtr = (uint8)(reqDtc >> 16U);
                    dataPtr++;
                    /* Deviation MISRA-1 */
                    *dataPtr = (uint8)(reqDtc >> 8U);
                    dataPtr++;
                    /* Deviation MISRA-1 */
                    *dataPtr = (uint8)(reqDtc);
                    dataPtr++;
                    /* Deviation MISRA-1 */
                    *dataPtr = (Dcm_MsgItemType)dtcStatusMask;
                    dataPtr++;

                    /* update response length */
                    pMsgContext->resDataLen += (PduLengthType)4U;
                  }
                }
                else
                {
                  /* Response too long */
                  Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
                }

                ++loopCnt;
              }
              while ((resultGetNextDtc != DEM_FILTERED_NO_MATCHING_DTC)
                      /* Deviation MISRA-2 */
                      && (loopCnt < numFilteredDTCs));
              serviceProcessStatus = DCM_E_DONE;
            }
            else if ( resultFilteredDTC == DEM_NUMBER_PENDING )
            {
              serviceProcessStatus = DCM_E_PENDING;
            }
            else /* Get number of filtered DTC failed */
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
              serviceProcessStatus = DCM_E_DONE;
            }
#endif /* #if DCM_PAGEDBUFFER_ENABLED */
          }
          else /* Wrong Filter */
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        /* if buffer is too small for the response data */
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
    }
    /* error occured while getting DTCStatusAvailabiityMask */
    else
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  /* request data length is invalid */
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REPORTSUPPORTEDDTCS_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*#if DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A */

#endif /* (DCM_DSP_USE_SERVICE_0X19 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X22 == STD_ON)
/* This is the generic service handler for UDS service 0x22 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDataByIdentifier_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
                                                    &DCM_READDIDCONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCH_ENTRY(OpStatus,pMsgContext);
  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      /* calculate the number of Dids in the diagnostic request */
      pReadDIDContextType->DidCount = (pMsgContext->reqDataLen)/2U;
      /* Check if the request lenth is even number and greater the zero */
      if ((pMsgContext->reqDataLen == 0x00) || (((pMsgContext->reqDataLen) & 0x01U) != 0x00U))
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        serviceProcessStatus = DCM_E_DONE;
        break;
      }
      /*if DCM_READ_DID_MAX is zero no need to check the request Dids limit.*/
      /* Check if the no.of requested Dids not exceeding the allowed limits.*/
      else if(pReadDIDContextType->DidCount > DCM_READ_DID_MAX)
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
        break;
      }
      else
      {
        /* Initialising the status to read the */
        pReadDIDContextType->DidReadProcessingSt = DCM_DID_READ_CONDITION;
        pReadDIDContextType->RefDidProcessingSt = DCM_DID_REF_READ_CONDITION;
        pReadDIDContextType->DidInd = 0U;
        pReadDIDContextType->NrcCondtions = DCM_E_SECURITYACCESSDENIED;
#if (DCM_COMMON_BUFF_CONFIGURED == STD_ON)
        /*If RX and TX buffer is common*/
        if(pMsgContext->reqData == pMsgContext->resData)
        {
          /*Copy the Dids to the buffer Dcm_ReadDIDBuffer[]*/
          TS_MemCpy(Dcm_ReadDIDBuffer, pMsgContext->reqData, (uint16)pMsgContext->reqDataLen);
          pReadDIDContextType->BuffPtr = Dcm_ReadDIDBuffer;
        }
        else
#endif
        {
          pReadDIDContextType->BuffPtr = pMsgContext->reqData;
        }
      serviceProcessStatus = Dcm_DspInternal_ReadDataByIdentifier_SvcStart(OpStatus, pMsgContext);
      }

      break;

    /* consecutive call after the function returned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_ReadDataByIdentifier_SvcStart(OpStatus, pMsgContext);
      break;

    /* cancel any ongoing service processing */
    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_ReadDataByIdentifier_SvcStart(OpStatus, pMsgContext);
      break;

    /* update the next page in paged buffer processing */
    case DCM_UPDATE_PAGE:
      serviceProcessStatus = DCM_E_DONE;
      /* call corresponding update page function */
      break;

    /* actions performed on sucessful sending of the response */
    case DCM_CONFIRMED_OK:
      serviceProcessStatus = DCM_E_DONE;
      /* do nothing */
      break;

    /* actions performed on failure in sending of the response */
    case DCM_CONFIRMED_NOK:
      serviceProcessStatus = DCM_E_DONE;
      /* do nothing */
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDataByIdentifier_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
  /* get the current context info used by Tx Pdu Id */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  /* holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
                                                    &DCM_READDIDCONTEXT(instIdx);
  Std_ReturnType ReturnVal = E_OK;
  Dcm_NegativeResponseCodeType nrcChecks = DCM_E_OK;

  DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCSTART_ENTRY(OpStatus,pMsgContext);

  /* Loops over the requested Dids while nrc not set and return value is not pending */
  while((pReadDIDContextType->DidInd < pReadDIDContextType->DidCount) &&
        /* Deviation MISRA-2 */
        (ReturnVal != DCM_E_PENDING) &&
        ((curHsmInfo->negativeResponseCode == DCM_E_OK) ||
        ((curHsmInfo->negativeResponseCode == DCM_E_GENERALREJECT) && (OpStatus == DCM_CANCEL))))
  {
    uint16 reqDid;
    switch(pReadDIDContextType->DidReadProcessingSt)
    {
      /* Deviation MISRA-3 */
      case DCM_DID_READ_CONDITION:
        /* Getting the requested DID from request buffer */
        reqDid = (uint16)((uint16)((uint16)pReadDIDContextType->BuffPtr[2U *
                    pReadDIDContextType->DidInd] << 8U) +
                    ((uint16)pReadDIDContextType->BuffPtr[(2U * pReadDIDContextType->DidInd)+1U]));

        /* Check if the Did can be read in the current coditions as per the configuration */
        ReturnVal = Dcm_DspInternal_DidConditionChecks(reqDid, DCM_DID_OP_READ, &nrcChecks,
                                                        &readDidIndex,instIdx);
        if (ReturnVal == E_OK)
        {
          ReturnVal = Dcm_DspInternal_ReqDidSetStatus(pMsgContext, reqDid, instIdx);
        }

        if (ReturnVal != E_OK)
        {
          /* increment DID */
          pReadDIDContextType->DidInd++;
          if((pReadDIDContextType->NrcCondtions != E_OK) && (nrcChecks == DCM_E_REQUESTOUTOFRANGE))
          {
            pReadDIDContextType->NrcCondtions = nrcChecks;
          }
          serviceProcessStatus = DCM_E_DONE;
          break;
        }
        /* continue reading the DID */

      /* Deviation MISRA-3 */
      case DCM_DID_READ:
        ReturnVal = Dcm_DspInternal_ReadDid(readDidIndex, instIdx, OpStatus, pMsgContext);
        if (ReturnVal == E_OK)
        {
#if (DCM_DID_REF_COUNT > 0)
          pReadDIDContextType->DidReadProcessingSt = DCM_DID_READ_REF;
          pReadDIDContextType->RefDidProcessingSt = DCM_DID_REF_READ_CONDITION;
          pReadDIDContextType->RefDidInd = 0U;
#else
          /* increment DID index */
          pReadDIDContextType->DidInd++;
          pReadDIDContextType->DidReadProcessingSt = DCM_DID_READ_CONDITION;
          serviceProcessStatus = DCM_E_DONE;
          break;
#endif
          /* fall through to processing of referenced DIDs */
        }
        else
        {
          if (ReturnVal == DCM_E_PENDING)
          {
            serviceProcessStatus = DCM_E_PENDING;
          }
          else
          {
            serviceProcessStatus = DCM_E_DONE;
          }
          break;
        }
#if (DCM_DID_REF_COUNT > 0)
      /* Deviation MISRA-3 */
      case DCM_DID_READ_REF:

        while(((pReadDIDContextType->RefDidInd < Dcm_DidTable[readDidIndex].NumRefDids) &&
              (ReturnVal != DCM_E_PENDING)) &&
              ((curHsmInfo->negativeResponseCode == DCM_E_OK) ||
              ((curHsmInfo->negativeResponseCode == DCM_E_GENERALREJECT) &&
               (OpStatus == DCM_CANCEL)
              )))
        {
          uint16 refDid;
          switch(pReadDIDContextType->RefDidProcessingSt)
          {
            /* Deviation MISRA-3 */
            case DCM_DID_REF_READ_CONDITION:
              refDid = Dcm_DidTable[readDidIndex].DidReferences[pReadDIDContextType->RefDidInd];
              /* Check if the Did can be read in the current coditions as per the configuration */
              ReturnVal = Dcm_DspInternal_DidConditionChecks(refDid, DCM_DID_OP_READ, &nrcChecks,
                                                             &refDidIndex, instIdx );
              if (ReturnVal == E_OK)
              {
                ReturnVal = Dcm_DspInternal_RefDidSetStatus(pMsgContext, refDid, instIdx);
              }

              if (ReturnVal != E_OK)
              {
                pReadDIDContextType->RefDidInd++;
                if((pReadDIDContextType->NrcCondtions != E_OK) &&
                   (nrcChecks == DCM_E_REQUESTOUTOFRANGE))
                {
                  pReadDIDContextType->NrcCondtions = nrcChecks;
                }
                serviceProcessStatus = DCM_E_DONE;
                break;
              }
              /* continue reading the DID */

            /* Deviation MISRA-3 */
            case DCM_DID_REF_READ:
              ReturnVal = Dcm_DspInternal_ReadDid(refDidIndex, instIdx, OpStatus, pMsgContext);
              if (ReturnVal == E_OK)
              {
                /* fall through to processing of referenced DIDs */
                pReadDIDContextType->RefDidProcessingSt = DCM_DID_REF_READ_CONDITION;
                /* increment referenced DID index */
                pReadDIDContextType->RefDidInd++;
                serviceProcessStatus = DCM_E_DONE;
              }
              else
              {
                if (ReturnVal == DCM_E_PENDING)
                {
                  serviceProcessStatus = DCM_E_PENDING;
                }
                else
                {
                  serviceProcessStatus = DCM_E_DONE;
                }
              }
              break;
            default:
              serviceProcessStatus = DCM_E_DONE;
              break;
          }

          if (OpStatus == DCM_CANCEL)
          {
            serviceProcessStatus = DCM_E_DONE;
            break;
          }
        }
        if ((pReadDIDContextType->RefDidInd == Dcm_DidTable[readDidIndex].NumRefDids) &&
        (pReadDIDContextType->DidReadSigConditionSt != DCM_DID_SIG_READ_CANCEL))
        {
          /* increment DID index */
          pReadDIDContextType->DidInd++;
          pReadDIDContextType->DidReadProcessingSt = DCM_DID_READ_CONDITION;
          serviceProcessStatus = DCM_E_DONE;
        }
        break;
#endif
      default:
        serviceProcessStatus = DCM_E_DONE;
        break;
    }

    if (OpStatus == DCM_CANCEL)
    {
      serviceProcessStatus = DCM_E_DONE;
      break;
    }
  }

  if (((pReadDIDContextType->DidInd == pReadDIDContextType->DidCount) &&
      (pReadDIDContextType->NrcCondtions != DCM_E_OK)) &&
      (OpStatus != DCM_CANCEL))
  {
    Dcm_ExternalSetNegResponse(pMsgContext, pReadDIDContextType->NrcCondtions);
      serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_READDATABYIDENTIFIER_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReqDidSetStatus(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 reqDid, uint8 instIdx)
{
  Std_ReturnType retVal;
  /* Pointer for storing the DID and signals */
  Dcm_MsgType dataPtr = &pMsgContext->resData[pMsgContext->resDataLen];
  /* holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
                                                    &DCM_READDIDCONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_REQDIDSETSTATUS_ENTRY(pMsgContext, reqDid, instIdx);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* check if buffer has free space for the DID */
  if ((pMsgContext->resDataLen + DCM_DID_ID_SIZE) <= pMsgContext->resMaxDataLen)
  {
    /* Changing the state to read DID*/
    pReadDIDContextType->DidReadProcessingSt = DCM_DID_READ;
    /* Initialising Signal index to start from from reading of first signal*/
    pReadDIDContextType->SignalInd = 0U;
    /* Initialising total bytes occupied by signals to zero*/
    pReadDIDContextType->NumSignalTotalBytes = 0U;
    /* Initialising the status of Async Signal state to process the next async signal*/
    pReadDIDContextType->DidAsynchSignalSt = DCM_DID_SIGNAL_CALL;
    pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_CONDITION_CALL;
    pReadDIDContextType->NrcCondtions = E_OK;
    /* Assemble the Did in response.*/
    dataPtr[0] = (uint8)(reqDid >> 8U);
    dataPtr[1] = (uint8)(reqDid);
    pMsgContext->resDataLen += DCM_DID_ID_SIZE; /* DID size + IOControl Parameter byte */

    retVal = E_OK;
    /* continue reading the DID */
  }
  else
  {
    /* Buffer is too small for the response data; Set NRC */
    pReadDIDContextType->NrcCondtions = DCM_E_GENERALREJECT;

    retVal = E_NOT_OK;
  }

  DBG_DCM_DSPINTERNAL_REQDIDSETSTATUS_EXIT(retVal, pMsgContext, reqDid, instIdx);

  return retVal;
}

#if (DCM_DID_REF_COUNT > 0)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RefDidSetStatus(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint16 refDid, uint8 instIdx)
{
  Std_ReturnType retVal;
  /* Pointer for storing the DID and signals */
  Dcm_MsgType dataPtr = &pMsgContext->resData[pMsgContext->resDataLen];
  /* holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
                                                    &DCM_READDIDCONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_REFDIDSETSTATUS_ENTRY(pMsgContext, refDid, instIdx);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* check if buffer has free space for the DID */
  if ((pMsgContext->resDataLen + DCM_DID_ID_SIZE) <= pMsgContext->resMaxDataLen)
  {
    pReadDIDContextType->RefDidProcessingSt = DCM_DID_REF_READ;
    pReadDIDContextType->SignalInd = 0U;
    pReadDIDContextType->NumSignalTotalBytes = 0U;
    /* Initialising the status of Async Signal state to process the next async signal*/
    pReadDIDContextType->DidAsynchSignalSt = DCM_DID_SIGNAL_CALL;
    pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_CONDITION_CALL;
    pReadDIDContextType->NrcCondtions = E_OK;
    /* Assemble the Did in response.*/
    dataPtr[0] = (uint8)(refDid >> 8U);
    dataPtr[1] = (uint8)(refDid);
    pMsgContext->resDataLen += DCM_DID_ID_SIZE;

    retVal = E_OK;
  }
  else
  {
    /* Buffer is too small for the response data; Set NRC */
    pReadDIDContextType->NrcCondtions = DCM_E_GENERALREJECT;

    retVal = E_NOT_OK;
  }

  DBG_DCM_DSPINTERNAL_REFDIDSETSTATUS_EXIT(retVal, pMsgContext, refDid, instIdx);

  return retVal;
}
#endif /* #if (DCM_DID_REF_COUNT > 0) */
#endif /* (DCM_DSP_USE_SERVICE_0X22 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X27 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
     serviceProcessStatus = Dcm_DspInternal_SecurityAccessControl_SvcStart(OpStatus, pMsgContext);
     break;

    /* Consecutive call after the function returned PENDING before */
    case DCM_PENDING:
     serviceProcessStatus = Dcm_DspInternal_SecurityAccessControl_SvcCont(OpStatus, pMsgContext);
     break;

    /* cancel any ongoing service processing */
    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_SecurityAccessControl_SvcCont(OpStatus, pMsgContext);
      break;

    /* next call after a "response pending" was forced to be sent immediately  */
    case DCM_FORCE_RCRRP_OK:
      serviceProcessStatus = DCM_E_DONE;
      break;

    /* actions performed on sucessful sending of the response */
    case DCM_CONFIRMED_OK:
      serviceProcessStatus = DCM_E_DONE;
      break;

    /* actions performed on failure in sending of the response */
    case DCM_CONFIRMED_NOK:
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint8_least i;                         /* loop variable */
  Dcm_SecLevelType newSecLevel = 0U; /* security level requested */
  Dcm_SecStateType secState = 0U;   /* state of security access */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* pointer to configuration information of requested security level */
  P2CONST(Dcm_SecTabEntryConfigType, AUTOMATIC, DCM_CONST) newSecTabEntry = NULL_PTR;

  /* negative reponse code */
  Dcm_NegativeResponseCodeType nrc = DCM_E_OK;

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(curProtocolId);

  DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCSTART_ENTRY(OpStatus,pMsgContext);

  /* check request length */
  if (pMsgContext->reqDataLen < 1U)
  {
    nrc = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }
  else
  {
    /* store type of request */
    secState = (Dcm_SecStateType) (curHsmInfo->subServiceId % 2U);

    /* Dcm338: get security level by computing the next smallest odd number */
    newSecLevel = (Dcm_SecLevelType) ((curHsmInfo->subServiceId + 1U) / 2U);

    /* Check if requested security level is supported */
    for (i = 0U; i < Dcm_SecTabConfig.NumEntries; ++i)
    {
      if (Dcm_SecTabConfig.Entries[i].SecLevel == newSecLevel)
      {
        newSecTabEntry = &(Dcm_SecTabConfig.Entries[i]);
        curHsmInfo->reqSecTabIdx = (uint8)i;
        break;
      }
    }
    /* requested security level not found */
    if ((Dcm_SecTabConfig.NumEntries == 0x00) || (i >= Dcm_SecTabConfig.NumEntries))
    {
      nrc = DCM_E_SUBFUNCTIONNOTSUPPORTED;

#if (DCM_SECURITYACCESS_STRICT == STD_ON)
      /* reset security access state handling */
      curHsmInfo->requestedSecLevel = DCM_SEC_IDLE;
#endif
    }

    /* Seed was not requested */
    else
    {
      if ((secState == DCM_SEC_SEND_KEY)
               && (curHsmInfo->subServiceId != (curHsmInfo->requestedSecLevel * 2U)))
      {
        nrc = DCM_E_REQUESTSEQUENCEERROR;

#if (DCM_SECURITYACCESS_STRICT == STD_ON)
        /* reset security access state handling */
        curHsmInfo->requestedSecLevel = DCM_SEC_IDLE;
#endif
      }
    }
  }

  {
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* current instance index */
  const uint8 instIdx = curProtocolId;
#endif
    /* Check failed attempts, delay counter and seed/key size */
    if (nrc == DCM_E_OK)
    {
      /* Check if no of security access attempts have exceeded the limit */
      if (DCM_EXCEED_NO_OF_ATTEMPTS(instIdx) == TRUE)
      {
        nrc = DCM_E_EXCEEDNUMBEROFATTEMPTS;

        /* Clear the flag */
        DCM_EXCEED_NO_OF_ATTEMPTS(instIdx) =  FALSE;
      }
      /* Check delay counter is active */
      else if (DCM_SEC_DELAY_COUNTER(instIdx) > 0U)
      {
        nrc = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
      }
      /* Check length of key */
      else if ((secState == DCM_SEC_SEND_KEY)
               && (pMsgContext->reqDataLen != ((PduLengthType)(newSecTabEntry->KeySize +
                                                                      (PduLengthType)1U))))
      {
        nrc = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
      }
      /* Check length of securityAccessDataRecord in the seed request */
      else
      {
        if ((secState == DCM_SEC_REQ_SEED)
                 && (pMsgContext->reqDataLen != ((PduLengthType)(newSecTabEntry->ADRSize +
                                                                      (PduLengthType)1U))))
        {
          nrc = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        }
      }
    }
  }

    /* Preconditions OK */
  if (nrc == DCM_E_OK)
  {
    /* setup response data (value of security level) */
    pMsgContext->resData[0] = curHsmInfo->subServiceId;

    /* assign the data from msgcontext for service to that of sub-function.*/
    /* To avoid pMsgContext change when OpStatus is DCM_PENDING */
    /* point the reqData behind the sub-function */
    pMsgContext->reqData = &pMsgContext->reqData[1];
    /* decrement the reqData length as sub-function is removed */
    pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;

    serviceProcessStatus = Dcm_DspInternal_SecurityAccessControl_SvcCont( OpStatus, pMsgContext);
  }
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, nrc);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCSTART_EXIT(serviceProcessStatus,
                                                          OpStatus,
                                                          pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);
  /* State of security access */
  Dcm_SecStateType secState = (Dcm_SecStateType) (curHsmInfo->subServiceId % 2U);
  /* get security level by computing the next smallest odd number */
  Dcm_SecLevelType newSecLevel = Dcm_SecTabConfig.Entries[curHsmInfo->reqSecTabIdx].SecLevel;
  /* negative reponse code */
  Dcm_NegativeResponseCodeType nrc = DCM_E_OK;
  uint8 numAttempts = Rte_DcmSecGetNumAtt(newSecLevel);    /* number of failed attempts */

  DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCCONT_ENTRY(OpStatus,pMsgContext);

  /* Request Seed */
  if (secState == DCM_SEC_REQ_SEED)
  {
    serviceProcessStatus = Dcm_DspInternal_SecurityAccessRequestSeed_SSvcH(
                            curHsmInfo->reqSecTabIdx, OpStatus, newSecLevel, &nrc, pMsgContext);
  }
  /* Authenticate the key */
  else
  {
    serviceProcessStatus = Dcm_DspInternal_SecurityAccessSendKey_SSvcH(
                  curHsmInfo->reqSecTabIdx, OpStatus, numAttempts, newSecLevel, &nrc, pMsgContext);
  }

  if (nrc != DCM_E_OK)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, nrc);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_SECURITYACCESSCONTROL_SVCCONT_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

/* Added the function to reduce the cyclomatic complexity of
   Dcm_DspInternal_SecurityAccessControl_SvcH() */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessRequestSeed_SSvcH(
  uint8 secTabIdx,
  Dcm_OpStatusType OpStatus,
  Dcm_SecLevelType newSecLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint32_least i = 0U; /* loop variable */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Std_ReturnType getSeedStatus = E_OK;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(curProtocolId);

  /* pointer to configuration information of requested security level */
  P2CONST(Dcm_SecTabEntryConfigType, AUTOMATIC, DCM_CONST) newSecTabEntry
    = &(Dcm_SecTabConfig.Entries[secTabIdx]);

  DBG_DCM_DSPINTERNAL_SECURITYACCESSREQUESTSEED_SSVCH_ENTRY(secTabIdx,OpStatus,
                                                            newSecLevel,nrc,pMsgContext);

  /* check if requested security level is already active */
  if ((curHsmInfo->secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
      && (newSecLevel == Dcm_SecTabConfig.Entries[curHsmInfo->secTabIdx].SecLevel))
  {
    /* setup response data (if seed value is 0 level is already unlocked) */
    for (i = 1U; i <= newSecTabEntry->SeedSize; ++i)
    {
      pMsgContext->resData[i] = 0U;
    }
    pMsgContext->resDataLen = (PduLengthType)(newSecTabEntry->SeedSize + (PduLengthType)1U);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    /* set security state to requested security level */
    curHsmInfo->requestedSecLevel = (Dcm_SecLevelType) ((curHsmInfo->subServiceId + 1U) / 2U);

    /* Process getSeed request */
    getSeedStatus = Dcm_DspInternal_GetSeed_Operation(OpStatus, nrc, newSecTabEntry,
      pMsgContext);
    if (getSeedStatus == E_OK)
    {
      /* setup response data */
      pMsgContext->resDataLen += (PduLengthType)(newSecTabEntry->SeedSize + (PduLengthType)1U);
      serviceProcessStatus = DCM_E_DONE;
    }
    else if (getSeedStatus == DCM_E_PENDING)
    {
      /* Pending status should be returned to the service handler. */
      serviceProcessStatus = DCM_E_PENDING;
    }
    else
    {
      /*No operation shall be done here, since error code is captured
      in 'nrc' and negative response is sent from the service handler.*/
      serviceProcessStatus = DCM_E_DONE;
    }
  }

  DBG_DCM_DSPINTERNAL_SECURITYACCESSREQUESTSEED_SSVCH_EXIT(serviceProcessStatus,secTabIdx,OpStatus,
                                                           newSecLevel,nrc,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetSeed_Operation(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2CONST(Dcm_SecTabEntryConfigType, AUTOMATIC, DCM_CONST) newSecTabEntry,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType getSeedStatus = E_NOT_OK;

  DBG_DCM_DSPINTERNAL_GETSEED_OPERATION_ENTRY(OpStatus,nrc,newSecTabEntry,pMsgContext);

  if (newSecTabEntry->ADRSize > 0U)
  {
    /* Point to the SecurityAccessDataRecord from the request message, as subfunction removed before
       calling subservice handler
     */
    P2VAR(uint8, AUTOMATIC, DCM_VAR) SecurityAccessDataRecord = &(pMsgContext->reqData[0]);

    /* For  USE_DATA_SYNCH_FNC, USE_DATA_ASYNCH_FNC,USE_DATA_SYNCH_CLIENT_SERVER,
       USE_DATA_ASYNCH_CLIENT_SERVER call the DcmDspSecurityGetSeedFnc operation when
       DcmDspSecurityADRSize is present */
    if((newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_ASYNCH_FUNC) ||
       (newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_ASYNCH_CLIENT_SERVER))
    {
      /* Calling the GetSeed operation  */
      getSeedStatus = newSecTabEntry->SecurityGetSeedFncADRAsync(SecurityAccessDataRecord,
                                             OpStatus, &(pMsgContext->resData[1]), nrc);
      if(OpStatus != DCM_CANCEL)
      {
        if(getSeedStatus != E_OK)
        {
          if((getSeedStatus == DCM_E_NO_DATA)||(getSeedStatus == DCM_E_PENDING))
          {
            getSeedStatus = DCM_E_PENDING;
          }
          else if(getSeedStatus == E_NOT_OK)
          {
            /*In this case nrc will be set from the GetSeed operation*/
          }
          else
          {
            *nrc = DCM_E_GENERALREJECT;
          }
        }
        else
        {
          /*If the GetSeed returns E_OK , set the nrc  to E_OK */
          *nrc = E_OK;
        }
      }
      else
      {
        getSeedStatus = E_NOT_OK;
      }
    }
    else if ((newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_SYNCH_FUNC) ||
             (newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_SYNCH_CLIENT_SERVER))
    {
      /* Calling the GetSeed operation */
      getSeedStatus = newSecTabEntry->SecurityGetSeedFncADRSync(SecurityAccessDataRecord,
                                                  &(pMsgContext->resData[1]), nrc);
      if(getSeedStatus != E_OK)
      {
        if(getSeedStatus != E_NOT_OK)
        {
          /*In case getSeedStatus == E_NOT_OK nrc will be set from the GetSeed operation*/
          *nrc = DCM_E_GENERALREJECT;
        }
      }
      else
      {
        /*If the GetSeed returns E_OK , set the nrc  to E_OK */
        *nrc = E_OK;
      }
    }
    else
    {
      getSeedStatus = E_OK;
    }
  }
  else
  {
    /* For  USE_DATA_SYNCH_FNC, USE_DATA_ASYNCH_FNC,USE_DATA_SYNCH_CLIENT_SERVER,
       USE_DATA_ASYNCH_CLIENT_SERVER call the DcmDspSecurityGetSeedFnc operation when
       DcmDspSecurityADRSize is not present */
    if((newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_ASYNCH_FUNC) ||
       (newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_ASYNCH_CLIENT_SERVER))
    {
      /* Calling the GetSeed operation */
      getSeedStatus = newSecTabEntry->SecurityGetSeedFncAsync(OpStatus,
                                                           &(pMsgContext->resData[1]), nrc);
      if(OpStatus != DCM_CANCEL)
      {
        if(getSeedStatus != E_OK)
        {
          if((getSeedStatus == DCM_E_NO_DATA)||(getSeedStatus == DCM_E_PENDING))
          {
            getSeedStatus = DCM_E_PENDING;
          }
          else if(getSeedStatus == E_NOT_OK)
          {
            /*In this case nrc will be set from the GetSeed operation*/
          }
          else
          {
            *nrc = DCM_E_GENERALREJECT;
          }
        }
        else
        {
          /*If the GetSeed returns E_OK , set the nrc  to E_OK */
          *nrc = E_OK;
        }
      }
      else
      {
        getSeedStatus = E_NOT_OK;
      }
    }
    else if ((newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_SYNCH_FUNC) ||
             (newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_SYNCH_CLIENT_SERVER))
    {
      /* Calling the GetSeed operation */
      getSeedStatus = newSecTabEntry->SecurityGetSeedFncSync(&(pMsgContext->resData[1]), nrc);
      if(getSeedStatus != E_OK)
      {
        if(getSeedStatus != E_NOT_OK)
        {
          /*In case getSeedStatus == E_NOT_OK nrc will be set from the GetSeed operation*/
          *nrc = DCM_E_GENERALREJECT;
        }
      }
      else
      {
        /*If the GetSeed read returns E_OK , set the nrc  to E_OK */
        *nrc = E_OK;
      }
    }
    else
    {
      getSeedStatus = E_OK;
    }
  }

  DBG_DCM_DSPINTERNAL_GETSEED_OPERATION_EXIT(getSeedStatus,OpStatus,nrc,newSecTabEntry,pMsgContext);
  return getSeedStatus;
}

/* Added the function to reduce the cyclomatic complexity of
   Dcm_DspInternal_SecurityAccessControl_SvcH() */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessSendKey_SSvcH(
  uint8 secTabIdx,
  Dcm_OpStatusType OpStatus,
  uint8 numAttemptsToCopy,
  Dcm_SecLevelType newSecLevel,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Std_ReturnType sendKeyStatus = E_OK;
  uint8 numAttempts = numAttemptsToCopy;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* current instance index */
  const uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(instIdx);

  /* pointer to configuration information of requested security level */
  P2CONST(Dcm_SecTabEntryConfigType, AUTOMATIC, DCM_CONST) newSecTabEntry
    = &(Dcm_SecTabConfig.Entries[secTabIdx]);

  DBG_DCM_DSPINTERNAL_SECURITYACCESSSENDKEY_SSVCH_ENTRY(secTabIdx,OpStatus,numAttempts,
                                                        newSecLevel,nrc,pMsgContext);

  /* For  USE_DATA_SYNCH_FNC, USE_DATA_ASYNCH_FNC,USE_DATA_SYNCH_CLIENT_SERVER,
     USE_DATA_ASYNCH_CLIENT_SERVER call the DcmDspSecurityCompareKeyFnc operation */
  if((newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_ASYNCH_FUNC) ||
     (newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_ASYNCH_CLIENT_SERVER))
  {
    /* Calling the CompareKey operation  */
    sendKeyStatus = newSecTabEntry->SecurityCompareKeyFncAsync(&(pMsgContext->reqData[0]),
                                                              OpStatus);
    if(OpStatus != DCM_CANCEL)
    {
      if(sendKeyStatus != E_OK)
      {
        if(sendKeyStatus == DCM_E_PENDING)
        {
          sendKeyStatus = DCM_E_PENDING;
        }
        else if(sendKeyStatus == E_NOT_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
          /*In this case nrc will be set from the CompareKey operation*/
        }
        else
        {
          *nrc = DCM_E_GENERALREJECT;
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /*If the CompareKey returns E_OK , set the nrc  to E_OK */
        *nrc = E_OK;
      }
    }
    else
    {
      sendKeyStatus = E_NOT_OK;
    }
  }
  else
  {
    if ((newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_SYNCH_FUNC) ||
             (newSecTabEntry->SecAccessInterface == DCM_USE_SECURITY_SYNCH_CLIENT_SERVER))
    {
      /* Calling the CompareKey operation */
      sendKeyStatus = newSecTabEntry->SecurityCompareKeyFncSync(&(pMsgContext->reqData[0]));
      if(sendKeyStatus != E_OK)
      {
        if(sendKeyStatus == E_NOT_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
          /*In this case nrc will be set from the CompareKey operation*/
        }
        else
        {
          *nrc = DCM_E_GENERALREJECT;
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /*If the CompareKey returns E_OK , set the nrc  to E_OK */
        *nrc = E_OK;
      }
    }
  }
  /* Authentication suceeded */
  if (sendKeyStatus == E_OK)
  {
    curHsmInfo->secTabIdx = (uint8)secTabIdx;

    /* reset number of failed attempts */
    if (numAttempts > 0U)
    {
      Rte_DcmSecSetNumAtt(newSecLevel, 0U);
    }

    /* setup response data */
    pMsgContext->resDataLen = 1U;

    /* reset security access state handling */
    curHsmInfo->requestedSecLevel = DCM_SEC_IDLE;
    serviceProcessStatus = DCM_E_DONE;
  }

  else if (sendKeyStatus == DCM_E_PENDING)
  {
    serviceProcessStatus = DCM_E_PENDING;
  }

  /* Authentication failed */
  else
  {
    if (OpStatus != DCM_CANCEL)
    {
      /* NRC should be invalidKey if the operation CompareKey() return value
         DCM_E_COMPARE_KEY_FAILED or DCM_E_NOT_OK. */
      *nrc = DCM_E_INVALIDKEY;

      if (newSecTabEntry->AttDelay > 0U)
      {
        /* Increment and store the number of failed attempts */
        ++numAttempts;
        Rte_DcmSecSetNumAtt(newSecLevel, (uint8)numAttempts);

        /* Load the delay counter and set the flag for exceeding number of permitted attempts */
        if (numAttempts >= newSecTabEntry->AttDelay)
        {
          DCM_SEC_DELAY_COUNTER(instIdx) = newSecTabEntry->DelayTime;

          DCM_EXCEED_NO_OF_ATTEMPTS(instIdx) = TRUE;
        }
      }
      /* reset security access state handling */
      curHsmInfo->requestedSecLevel = DCM_SEC_IDLE;
   }
   else
   {
      serviceProcessStatus = DCM_E_DONE;
   }
  }

  DBG_DCM_DSPINTERNAL_SECURITYACCESSSENDKEY_SSVCH_EXIT(serviceProcessStatus,secTabIdx,OpStatus,
                                                       numAttempts,newSecLevel,nrc,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_DSP_USE_SERVICE_0X27 == STD_ON) */

#if(DCM_0X28_SVC_ENABLED == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CommunicationControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_CommunicationControl_SvcStart(DCM_INITIAL,
                                                                           pMsgContext);
      break;

    /* Consecutive call after the function retuned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_CommunicationControl_SvcCont(DCM_PENDING,
                                                                          pMsgContext);
      break;

      /* cancel any ongoing service processing */
      case DCM_CANCEL:
        serviceProcessStatus = Dcm_DspInternal_CommunicationControl_SvcCont(DCM_CANCEL,
                                                                            pMsgContext);
        break;

   default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CommunicationControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* get configuration for current Rx Pdu Id */
  CONSTP2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig
    = &Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId];

  /* Get current protocol id */
  uint8_least curProtocolId = curRxPduIdConfig->protocolId;
#endif

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(curProtocolId).sidTabId];

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  /* get number of subservices */
  uint8_least numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  /* Get the Communication message type from request data */
  uint8 messageType = (pMsgContext->reqData[1] & DCM_MESSAGE_TYPE_MASK);

  TS_PARAM_UNUSED(OpStatus);

  DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCSTART_ENTRY(pMsgContext);

  if (pMsgContext->reqDataLen == 2U)
  {
    /* loop variable */
    uint8_least i;

    for (i = 0U; i < numSubServ; i++)
    {
      /* Search for the index in subservices table for the requested subservice */
      if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
      {
        break;
      }
    }
    if ( messageType == 0U )
    {
      /* Request received is out of range */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
    else
    {
      /* set request data pointer to received data without service and subservice Ids */
      pMsgContext->reqData = &pMsgContext->reqData[1];

      /* decrement the reqData length as sub-function is removed */
      pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;

      if (curSsConfig[i].IntSrvHandler != NULL_PTR)
      {
        /* Call internal sub-service handler */
        serviceProcessStatus = curSsConfig[i].IntSrvHandler(DCM_INITIAL, pMsgContext);
      }
      else
      {
        /* Call External sub-service handler */
        serviceProcessStatus = curSsConfig[i].ExtSrvHandler(DCM_INITIAL, pMsgContext);

        /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
        if (serviceProcessStatus == E_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
    }
  }
  else
  {
    /* check request length */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CommunicationControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#else
  Std_ReturnType serviceProcessStatus = DCM_E_DONE;
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8_least curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(curProtocolId).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  /* get number of subservices */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  /* loop variable */
  uint8 i;

  DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCCONT_ENTRY(pMsgContext);

  for (i = 0U; i < numSubServ; i++)
  {
    /* Search for the index in subservices table for the requested subservice */
    if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
    {
      if (curSsConfig[i].IntSrvHandler != NULL_PTR)
      {
        if(OpStatus != DCM_CANCEL)
        {
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
          /* check if a mode transition confirmation is received from BswM */
          if (curHsmInfo->confirmedCommunicationMode != DCM_0X28_COMM_MODE_INVALID)
          {
            /* check if the mode transition request is accepted by BswM. ie requested communication
               mode is same as the communication mode entered */
            if (curHsmInfo->confirmedCommunicationMode == curHsmInfo->requestedCommunicationMode)
            {
              /* reset the mode transition parameters */
              curHsmInfo->confirmedCommunicationMode = DCM_0X28_COMM_MODE_INVALID;
              curHsmInfo->requestedCommunicationMode = DCM_0X28_COMM_MODE_INVALID;
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
              /* assemble positive response */
              pMsgContext->resDataLen = 1U;
              pMsgContext->resData[0] = curHsmInfo->subServiceId;
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
            }
            else
            {
              /* mode transition request not accepted. Set negative response */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
            }
            serviceProcessStatus = DCM_E_DONE;
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */

#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
            serviceProcessStatus = DCM_E_DONE;
          }
          else
          {
          serviceProcessStatus = DCM_E_PENDING;
          }
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_OFF) */
        }
        else
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        serviceProcessStatus = curSsConfig[i].ExtSrvHandler(OpStatus, pMsgContext);

        /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
        if (serviceProcessStatus == E_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      break;
    }
  }

  DBG_DCM_DSPINTERNAL_COMMUNICATIONCONTROL_SVCCONT_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

#if (DCM_0X28_0X00_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x28-0x00 handler */
/* Deviation MISRA-4 <+3> */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_EnableRxAndTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_PENDING;
#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  Std_ReturnType setComModeRes = E_OK;
#endif

  DBG_DCM_DSPINTERNAL_ENABLERXANDTX_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  /* Set communication mode */
  setComModeRes = Dcm_DspInternal_SetCommunicationMode(pMsgContext);

  if ( E_NOT_OK == setComModeRes )
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
#else /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */

  DBG_DCM_DSPINTERNAL_ENABLERXANDTX_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_0X28_0X00_SSVC_ENABLED == STD_ON) */

#if (DCM_0X28_0X01_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x28-0x01 handler */
/* Deviation MISRA-4 <+3> */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_EnableRxAndDisableTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_PENDING;
#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  Std_ReturnType setComModeRes = E_OK;
#endif

  DBG_DCM_DSPINTERNAL_ENABLERXANDDISABLETX_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  /* Set communication mode */
  setComModeRes = Dcm_DspInternal_SetCommunicationMode(pMsgContext);

  if ( E_NOT_OK == setComModeRes )
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
#else /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */

  DBG_DCM_DSPINTERNAL_ENABLERXANDDISABLETX_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_0X28_0X01_SSVC_ENABLED == STD_ON) */

#if (DCM_0X28_0X02_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x28-0x02 handler */
/* Deviation MISRA-4 <+3> */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DisableRxAndEnableTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_PENDING;
#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  Std_ReturnType setComModeRes = E_OK;
#endif

  DBG_DCM_DSPINTERNAL_DISABLERXANDENABLETX_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  /* Set communication mode */
  setComModeRes = Dcm_DspInternal_SetCommunicationMode(pMsgContext);

  if ( E_NOT_OK == setComModeRes )
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
#else /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */

  DBG_DCM_DSPINTERNAL_DISABLERXANDENABLETX_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_0X28_0X02_SSVC_ENABLED == STD_ON) */

#if (DCM_0X28_0X03_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x28-0x03 handler */
/* Deviation MISRA-4 <+3> */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DisableRxAndTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_PENDING;
#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  Std_ReturnType setComModeRes = E_OK;
#endif

  DBG_DCM_DSPINTERNAL_DISABLERXANDTX_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

#if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON))
  /* Set communication mode */
  setComModeRes = Dcm_DspInternal_SetCommunicationMode(pMsgContext);

  if ( E_NOT_OK == setComModeRes )
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
#else /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */
  TS_PARAM_UNUSED(pMsgContext);
#endif /* #if ((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) */

  DBG_DCM_DSPINTERNAL_DISABLERXANDTX_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_0X28_0X03_SSVC_ENABLED == STD_ON) */

#if (((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) && \
     ((DCM_0X28_0X00_SSVC_ENABLED == STD_ON) || \
      (DCM_0X28_0X01_SSVC_ENABLED == STD_ON) || \
      (DCM_0X28_0X02_SSVC_ENABLED == STD_ON) || \
      (DCM_0X28_0X03_SSVC_ENABLED == STD_ON )))
/* This function is to set & perform request communication mode */
 STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SetCommunicationMode(
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType subnetRes = E_OK;
  NetworkHandleType networkId;
  Dcm_CommunicationModeType requestedCommunicationMode;
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
  uint8 modeSwitchCallbackIndex = 0U;
  Dcm_CommunicationModeType rteCommunicationMode = 0U;
#if ((DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL > 0U) || (DCM_NUM_COMCONTROL_ALL_CHANNEL > 0U))
  uint8 comCtrlChIdx = 0U;
#endif
#if (DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL > 0U)
  boolean subnetMismatch = TRUE;
#endif
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */
  /* get configuration for current Rx Pdu Id */
  CONSTP2CONST(Dcm_RxPduIdConfigType, AUTOMATIC, DCM_CONST) curRxPduIdConfig
    = &Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId];

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8_least curProtocolId = curRxPduIdConfig->protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(curProtocolId);

  /* Get the Control type, Communication message type and the subnet
     number from request data */
  uint8 messageType = pMsgContext->reqData[0] & DCM_MESSAGE_TYPE_MASK;
  uint8 subnetNumber = (pMsgContext->reqData[0] & DCM_SUBNET_NUMBER_MASK)>> 4U;

  DBG_DCM_DSPINTERNAL_SETCOMMUNICATIONMODE_ENTRY(pMsgContext);

  /* Get the requested Communication Mode from the look-up table */
  requestedCommunicationMode = Dcm_CommunicationModes[messageType][curHsmInfo->subServiceId];
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
  rteCommunicationMode = Dcm_RteCommunicationModes[messageType][curHsmInfo->subServiceId];
#endif

  if ( subnetNumber == 0x0FU )
  {
    /* Set 'networkId' with the 'ChannelId' value associated to the received PduId */
    networkId = Dcm_ChannelId[curRxPduIdConfig->channelIdIndex].networkId;

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
    while ( (modeSwitchCallbackIndex < DCM_COMCONTROL_LOOKUP_SIZE) &&
            (Dcm_ComControlLookUpTable[modeSwitchCallbackIndex].ComMChannelId != networkId) )
    {
      modeSwitchCallbackIndex++;
    }

    (void)Dcm_ComControlLookUpTable[modeSwitchCallbackIndex].SchMSwitchComControl(
      rteCommunicationMode );

#if (DCM_BSWM_API_ENABLED == STD_ON)
    /* Invoke the BswM interface to notify the Communication Mode change */
    BswM_Dcm_CommunicationMode_CurrentState(networkId, requestedCommunicationMode);
#endif  /* #if (DCM_BSWM_API_ENABLED == STD_ON) */

     Dcm_ChannelId[curRxPduIdConfig->channelIdIndex].communicationMode = requestedCommunicationMode;

#endif  /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */
  }
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
  else if((subnetNumber > 0x00U) && (subnetNumber < 0x0FU))
  {
#if (DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL > 0U)
    /* Loop through all CommunicationControl Specific channels */
    for (comCtrlChIdx = 0U; comCtrlChIdx < DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL;
         comCtrlChIdx++ )
    {
      if ( subnetNumber == Dcm_ComControlSpecificChannel[comCtrlChIdx].SubnetNumber )
      {
        subnetMismatch = FALSE;
        modeSwitchCallbackIndex = 0U;

        while ( (modeSwitchCallbackIndex < DCM_COMCONTROL_LOOKUP_SIZE) &&
              (Dcm_ComControlLookUpTable[modeSwitchCallbackIndex].ComMChannelId !=
                Dcm_ComControlSpecificChannel[comCtrlChIdx].ComMChannelId) )
        {
          modeSwitchCallbackIndex++;
        }

        (void)Dcm_ComControlLookUpTable[modeSwitchCallbackIndex].SchMSwitchComControl(
          rteCommunicationMode );
#if (DCM_BSWM_API_ENABLED == STD_ON)
        BswM_Dcm_CommunicationMode_CurrentState(
          Dcm_ComControlSpecificChannel[comCtrlChIdx].ComMChannelId,
          requestedCommunicationMode);
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
        {
          uint8_least ComMChannelIndex = 0U;

          for (ComMChannelIndex = 0U; ComMChannelIndex < DCM_NUM_CHANNELID; ComMChannelIndex++)
          {
            if (Dcm_ChannelId[ComMChannelIndex].networkId
                == Dcm_ComControlSpecificChannel[comCtrlChIdx].ComMChannelId)
            {
              Dcm_ChannelId[ComMChannelIndex].communicationMode = requestedCommunicationMode;
              break;
            }
          }
        }
      }
    }
    /* As none of the configured subnetNumber values matched the requested
     * value, NRC 0x31 shall be sent */
    if (subnetMismatch == TRUE)
    {
      subnetRes = E_NOT_OK;
    }
#endif /* #if (DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL > 0U) */
  }
  else /* subnetNumber = 0x00U */
  {
#if (DCM_NUM_COMCONTROL_ALL_CHANNEL > 0U)
    /* Loop through all CommunicationControl channels */
    for (comCtrlChIdx = 0U; comCtrlChIdx < DCM_NUM_COMCONTROL_ALL_CHANNEL;
         comCtrlChIdx++ )
    {
      modeSwitchCallbackIndex = 0U;
      while ( (modeSwitchCallbackIndex < DCM_COMCONTROL_LOOKUP_SIZE) &&
              (Dcm_ComControlLookUpTable[modeSwitchCallbackIndex].ComMChannelId !=
                Dcm_ComControlAllChannel[comCtrlChIdx]) )
      {
        modeSwitchCallbackIndex++;
      }

      (void)Dcm_ComControlLookUpTable[modeSwitchCallbackIndex].SchMSwitchComControl(
        rteCommunicationMode );
#if (DCM_BSWM_API_ENABLED == STD_ON)
      /* Invoke the BswM interface to request the Communication Mode change */
      BswM_Dcm_CommunicationMode_CurrentState(
        Dcm_ComControlAllChannel[comCtrlChIdx],
        requestedCommunicationMode);
#endif  /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
      {
        uint8_least ComMChannelIndex;

        for (ComMChannelIndex = 0U; ComMChannelIndex < DCM_NUM_CHANNELID; ComMChannelIndex++)
        {
          if (Dcm_ChannelId[ComMChannelIndex].networkId
              == Dcm_ComControlAllChannel[comCtrlChIdx])
          {
            Dcm_ChannelId[ComMChannelIndex].communicationMode = requestedCommunicationMode;
            break;
          }
        }
      }
    }
#endif /* #if (DCM_NUM_COMCONTROL_ALL_CHANNEL > 0U) */
  }
#else /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */
  else
  {
    /* If the subnet parameter is different from 0x0F :'networkId' is the
       copy of the subnetNumber parameter from the CommunicationControl request */
    networkId = subnetNumber;
  }
#if (DCM_BSWM_API_ENABLED == STD_ON)
  /* Invoke the BswM interface to request the Communication Mode change */
  BswM_Dcm_RequestCommunicationMode(networkId, requestedCommunicationMode);

  curHsmInfo->requestedCommunicationMode = requestedCommunicationMode;
#endif /* #if (DCM_BSWM_API_ENABLED == STD_ON) */
  {
    uint8_least ComMChannelIndex;

    for (ComMChannelIndex = 0U; ComMChannelIndex < DCM_NUM_CHANNELID; ComMChannelIndex++)
    {
      if (Dcm_ChannelId[ComMChannelIndex].networkId == networkId)
      {
        Dcm_ChannelId[ComMChannelIndex].communicationMode = requestedCommunicationMode;
        break;
      }
    }
  }
#endif /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */

  DBG_DCM_DSPINTERNAL_SETCOMMUNICATIONMODE_EXIT(subnetRes, pMsgContext);
  return subnetRes;
}
#endif /* #if (((DCM_MODEDECLARATION_SUPPORT == STD_ON) || (DCM_BSWM_API_ENABLED == STD_ON)) && \
                ((DCM_0X28_0X00_SSVC_ENABLED == STD_ON) || \
                 (DCM_0X28_0X01_SSVC_ENABLED == STD_ON) || \
                 (DCM_0X28_0X02_SSVC_ENABLED == STD_ON) || \
                 (DCM_0X28_0X03_SSVC_ENABLED == STD_ON ))) */

#endif /* (DCM_0X28_SVC_ENABLED == STD_ON) */

#if (DCM_DSP_USE_SERVICE_0X2E == STD_ON)
/* The generic service handler for UDS service 0x2E */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDataByIdentifier_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      /* if request data length is lessthan DID id size */
      if (pMsgContext->reqDataLen < DCM_DID_ID_SIZE)
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        serviceProcessStatus = DCM_E_DONE;
      }
      else
      {
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
        /* set the WriteDid processing status to request data validation */
        uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
        DCM_WRITE_DID_CONTEXT(instIdx).RequestProcessingSt = DCM_DID_REQUEST_CHECK;

        /* call WriteDID internal service handler */
        serviceProcessStatus = Dcm_DspInternal_WriteDataByIdentifier_SvcStart(OpStatus,
                                                                              pMsgContext);
      }
      break;

    /* consecutive call after the function retuned PENDING before */
    case DCM_PENDING:
      /* call WriteDID internal service handler */
      serviceProcessStatus = Dcm_DspInternal_WriteDataByIdentifier_SvcStart(OpStatus,
                                                                            pMsgContext);
      break;

    /* cancel any ongoing service processing */
    /* Deviation MISRA-3 */
    case DCM_CANCEL:
       serviceProcessStatus = Dcm_DspInternal_WriteDataByIdentifier_SvcStart(OpStatus,
                                                                            pMsgContext);

    /* actions performed on sucessful sending of the response */
    /* Deviation MISRA-3 */
    case DCM_CONFIRMED_OK:
      /* fall through */

    /* actions performed on failure in sending of the response */
    case DCM_CONFIRMED_NOK:
    {
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
      /* set the WriteDid processing status to request data validation */
      uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
      /* reset the WriteDID request processing status */
      DCM_WRITE_DID_CONTEXT(instIdx).RequestProcessingSt = DCM_DID_REQUEST_INVALID;
      DCM_WRITE_DID_CONTEXT(instIdx).DidAsynchSignalSt = DCM_DID_SIGNAL_INVALID;
      serviceProcessStatus = DCM_E_DONE;
      break;
    }

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

/* The function for implementation of UDS service 0x2E */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDataByIdentifier_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
  /* holds the return value */
  Std_ReturnType ReturnVal = E_OK;
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  /* holds the context information of currently processed DID */
  P2VAR(Dcm_WriteDIDContextType, AUTOMATIC, DCM_VAR) pWriteDIDContext =
                                                    &DCM_WRITE_DID_CONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCSTART_ENTRY(OpStatus,pMsgContext);

  /* request processing status */
  switch(pWriteDIDContext->RequestProcessingSt)
  {
    /* request data verification */
    /* Deviation MISRA-3 */
    case DCM_DID_REQUEST_CHECK:
      {
        /* calculate the requested DID */
        uint16 reqDid = (uint16)((uint16)((uint16)pMsgContext->reqData[0U] << 8U) +
                        ((uint16)pMsgContext->reqData[1U]));

        /* check the did range, write access, session and security */
        ReturnVal = Dcm_DspInternal_DidConditionChecks(reqDid, DCM_DID_OP_WRITE, &nrcCondtions,
                                                       &writeDidIndex, instIdx);
        if (ReturnVal == E_OK)
        {
          /* check the request data length */
          ReturnVal = Dcm_DspInternal_WriteDidRequestLengthChk(writeDidIndex, pMsgContext);
          if (ReturnVal == E_OK)
          {
            /* initialize the WriteDID context for starting the signal processing */

            /* initialize the signal to be processed next */
            pWriteDIDContext->SignalInd = 0U;
            /* update the processing status of WriteDID request to request processing */
            pWriteDIDContext->RequestProcessingSt = DCM_DID_REQUEST_PROCESSING;
            /* initialize the processing status of asynchronous signal within a DID to
               call Rte_Call_Xxx() interface */
            pWriteDIDContext->DidAsynchSignalSt = DCM_DID_SIGNAL_CALL;
            /* initialize the processing status of NVM data to call Nvm_WriteBlock() */
            pWriteDIDContext->DidNvmDataSt = DCM_DID_SIGNAL_CALL;
            /* Update status to indicate that the signal is being processed for the first time */
            pWriteDIDContext->InitSignalProcessing = TRUE;
          }
          else
          {
            /* set NRC and exit processing */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            serviceProcessStatus = DCM_E_DONE;
            break;
          }
        }
        else
        {
          /* set NRC and exit processing */
          Dcm_ExternalSetNegResponse(pMsgContext, nrcCondtions);
          serviceProcessStatus = DCM_E_DONE;
          break;
        }
      }
      /* fall through to request data processing */

    /* request data processing */
    /* Deviation MISRA-3 */
    case DCM_DID_REQUEST_PROCESSING:
      /* process the WriteDID data */
      if (pWriteDIDContext->InitSignalProcessing == TRUE)
      {
        ReturnVal = Dcm_DspInternal_WriteDid(writeDidIndex, instIdx, DCM_INITIAL, pMsgContext);
      }
      else
      {
        ReturnVal = Dcm_DspInternal_WriteDid(writeDidIndex, instIdx, OpStatus, pMsgContext);
      }

      if(OpStatus != DCM_CANCEL)
      {
        if (ReturnVal == E_OK)
        {
          /* Assemble the Did in response and update the response length.*/
          pMsgContext->resData[0] = pMsgContext->reqData[0];
          pMsgContext->resData[1] = pMsgContext->reqData[1];
          pMsgContext->resDataLen = DCM_DID_ID_SIZE;
          serviceProcessStatus = DCM_E_DONE;
        }
        /* if response data needs further processing */
        else if (ReturnVal == DCM_E_PENDING)
        {
          serviceProcessStatus = DCM_E_PENDING;
          pWriteDIDContext->InitSignalProcessing = FALSE;
        }
        else
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        serviceProcessStatus = DCM_E_DONE;
      }
      break;

    default:
        serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_WRITEDATABYIDENTIFIER_SVCSTART_EXIT(serviceProcessStatus,
                                                          OpStatus,
                                                          pMsgContext);
  return serviceProcessStatus;
}

#endif /* (DCM_DSP_USE_SERVICE_0X2E == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_InputOutputControlByIdentifier_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
  )
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  DBG_DCM_DSPINTERNAL_INPUTOUTPUTCONTROLBYIDENTIFIER_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* First call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_IOControlByIdentifier_SvcStart(OpStatus, pMsgContext);
      break;

    case DCM_FORCE_RCRRP_OK:
    /* fall through to next state */
    /* Deviation MISRA-3 */
    /* Sub-sequent call to the service function after FORCE_RCRRP */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_IOControlByIdentifier_SvcCont(OpStatus, pMsgContext);
      break;

    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_IOControlByIdentifier_SvcCont(OpStatus, pMsgContext);
      break;
    /* Actions performed on sucessful sending of the response */
    case DCM_CONFIRMED_OK:
      /* do nothing */

    /* fall through to next state */
    /* Deviation MISRA-3 */
    /* Actions performed on failure in sending of the response */
    case DCM_CONFIRMED_NOK:
      /* Reset the IOControl request processing status */
      DCM_IO_CONTROL_DID_CONTEXT(instIdx).RequestProcessingSt = DCM_DID_REQUEST_INVALID;
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_INPUTOUTPUTCONTROLBYIDENTIFIER_SVCH_EXIT(serviceProcessStatus,
                                                               OpStatus,
                                                               pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlByIdentifier_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* Holds the index of the currently processed DID in the configuration array */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCSTART_ENTRY(OpStatus,pMsgContext);

  /* Check request length (min. length check) */
  if (pMsgContext->reqDataLen < DCM_0x2F_REQUESTLENGTH)
  {
    /* Incorrect request length */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  else if ((pMsgContext->reqData[2U] == DCM_RETURNCONTROLTOECU) ||
           (pMsgContext->reqData[2U] == DCM_RESETTODEFAULT) ||
           (pMsgContext->reqData[2U] == DCM_FREEZECURRENTSTATE) ||
           (pMsgContext->reqData[2U] == DCM_SHORTTERMADJUSTMENT))
  {
    Std_ReturnType ReturnVal = E_OK;
    Dcm_NegativeResponseCodeType nrc = DCM_E_OK;
    /* Holds the instance id */
    uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
    /* Calculate the requested DID */
    uint16 reqDid = (uint16)((uint16)((uint16)pMsgContext->reqData[0U] << 8U) +
                        ((uint16)pMsgContext->reqData[1U]));

    /* Holds the context information of the IOControl request */
    P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_VAR) pIOControlDIDContext =
                                                    &DCM_IO_CONTROL_DID_CONTEXT(instIdx);

    /* Check if the Did can be controlled in the current conditions as per the configuration */
    ReturnVal = Dcm_DspInternal_DidConditionChecks(reqDid, DCM_DID_OP_IOCONTROL, &nrc,
                &pIOControlDIDContext->DidIndex, instIdx);

    if(ReturnVal == DCM_E_OK)
    {
      /* Verifying whether requested 'inputOutputControlParameter' is enabled or not */
      /* Deviation MISRA-2 */
      if ( ((pMsgContext->reqData[2] == DCM_RETURNCONTROLTOECU) &&
            (Dcm_DidTable[pIOControlDIDContext->DidIndex].ReturnControlToEcuEnable == TRUE)) ||
           ((pMsgContext->reqData[2] == DCM_RESETTODEFAULT) &&
            (Dcm_DidTable[pIOControlDIDContext->DidIndex].ResetToDefaultEnable == TRUE)) ||
           ((pMsgContext->reqData[2] == DCM_FREEZECURRENTSTATE) &&
            (Dcm_DidTable[pIOControlDIDContext->DidIndex].FreezeCurrentStateEnable == TRUE)) ||
           ((pMsgContext->reqData[2] == DCM_SHORTTERMADJUSTMENT) &&
            (Dcm_DidTable[pIOControlDIDContext->DidIndex].ShortTermAdjustmentEnable == TRUE)) )
      {
        /* Check the request data length (total length check) */
        ReturnVal = Dcm_DspInternal_IOControlDidRequestLengthChk(pMsgContext);

        if (ReturnVal == E_OK)
        {
          /* Holds the context information of currently processed DID */
          P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_APPL_DATA) pReadDIDContext =
                        &DCM_READDIDCONTEXT(instIdx);
          /* Pointer for storing the DID and signals */
          Dcm_MsgType dataPtr = &pMsgContext->resData[pMsgContext->resDataLen];
          /* Initialize the IOControl context for starting the signal processing */
          pIOControlDIDContext->SignalInd = 0U;
          /* Update the processing status of IOControl request to 'request processing' */
          pIOControlDIDContext->RequestProcessingSt = DCM_DID_REQUEST_PROCESSING;
          /* Update status to indicate initial signal processing */
          pIOControlDIDContext->InitSignalProcessing = TRUE;
          /* Update the IOControl request received */
          pIOControlDIDContext->IOControlParameter = pMsgContext->reqData[2];
          /* Assemble the DID in the response.*/
          dataPtr[0] = pMsgContext->reqData[0];
          dataPtr[1] = pMsgContext->reqData[1];
          /* Copy IOControl value to response buffer */
          dataPtr[2] = pMsgContext->reqData[2];
          pMsgContext->resDataLen += DCM_DID_ID_SIZE + 1U; /* DID size + IOControl Parameter byte */
          pReadDIDContext->DidReadSigConditionSt = DCM_DID_SIG_CONDITION_CALL;
          pReadDIDContext->SignalInd = 0U;
          pReadDIDContext->NumSignalTotalBytes = 0U;

          /* Fall through to request data processing */
          serviceProcessStatus = Dcm_DspInternal_IOControlByIdentifier_SvcCont(OpStatus,
                                                                               pMsgContext);
        }
        else
        {
          /* Set NRC and exit processing */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /* Requested 'inputOutputControlParameter' not enabled, send nrc */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
      }
    }
    else
    {
      /* Verification failed; set the respective error code */
      Dcm_ExternalSetNegResponse(pMsgContext, nrc);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    /* !LINKSTO Dcm.EB.IOControl.InvalidParameter,1 */
    /*  the value contained in the inputOuptputControlParameter is invalid */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCSTART_EXIT(serviceProcessStatus,
                                                          OpStatus,
                                                          pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlByIdentifier_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  /* Holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;

  DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCCONT_ENTRY(OpStatus,pMsgContext);

  /* Request data processing */
  switch (DCM_IO_CONTROL_DID_CONTEXT(instIdx).IOControlParameter)
  {
    case DCM_RETURNCONTROLTOECU:
      /* Call 'returnControlToEcu' handler to request to application to return control to ECU */
      serviceProcessStatus = Dcm_DspInternal_IOReturnControlToECU_Data(pMsgContext,
                                                              instIdx, OpStatus);
      break;

    case DCM_RESETTODEFAULT:
      /* Call 'resetToDefault' handler to request to application to reset an IOControl
         to default value */
      serviceProcessStatus = Dcm_DspInternal_IOResetToDefault_Data(pMsgContext,
                                                              instIdx, OpStatus);
      break;

    case DCM_FREEZECURRENTSTATE:
      /* Call 'FreezeCurrentState' handler to request to application to freeze the
         current state of an IOControl */
      serviceProcessStatus = Dcm_DspInternal_IOFreezeCurrentState_Data(pMsgContext,
                                                              instIdx, OpStatus);
      break;

    case DCM_SHORTTERMADJUSTMENT:
      /* Call 'ShortTermAdjustment' handler to request to application to adjust the IO signal */
      serviceProcessStatus = Dcm_DspInternal_IOShortTermAdjustment_Data(pMsgContext,
                                                              instIdx, OpStatus);
      break;

    default:
      break;
  }

  DBG_DCM_DSPINTERNAL_IOCONTROLBYIDENTIFIER_SVCCONT_EXIT(serviceProcessStatus,
                                                         OpStatus,
                                                         pMsgContext);
  return serviceProcessStatus;
}

/* Sub-handler for IOControl 'ReturnControlToECU' */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOReturnControlToECU_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext =
                                                    &DCM_IO_CONTROL_DID_CONTEXT(instIdx);
  /* Holds the number of signals in the DID */
  uint16 numSignals = Dcm_DidTable[pIOControlDIDContext->DidIndex].NumSignals;
  boolean controlMaskStatus = FALSE;
  Dcm_NegativeResponseCodeType nrc = E_OK;

  DBG_DCM_DSPINTERNAL_IORETURNCONTROLTOECU_DATA_ENTRY(pMsgContext,DCM_INST(instIdx),OpStatus);

  /* Dcm581: In case of more than one supported I/O signal per DataIdentifier, the DCM shall
     internally consider the parameter controlEnableMaskRecord and control only the included signals
     in the request message */
  while ((pIOControlDIDContext->SignalInd < numSignals) &&
          /* Deviation MISRA-2 */
         (serviceProcessStatus != DCM_E_PENDING) && (serviceProcessStatus != DCM_E_NOT_OK) &&
         (pIOControlDIDContext->RequestProcessingSt != DCM_DID_READ_PENDING))
  {
    /* Holds the configuration of the signal being processed */
    P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg =
    &Dcm_DidDataTable[Dcm_DidTable[pIOControlDIDContext->DidIndex].
    Signals[pIOControlDIDContext->SignalInd].DspDataIndex];

    controlMaskStatus = Dcm_DspInternal_IOControl_CheckControlMask(&(pMsgContext->reqData[3]),
                                                            pIOControlDIDContext, numSignals);

    /* The interface type of the currently processed signal data */
    switch (dataCfg->AccessInterface)
    {
#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
#endif /* DCM_INCLUDE_RTE == STD_ON */
      case DCM_USE_DATA_SYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          /* Call the interface function 'ReturnControlToEcu' for sync operation */
          RetVal = dataCfg->ReturnControlToEcuSync(&nrc);
        }
        else
        {
          RetVal = E_OK;
        }
        break;

#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
#endif /* DCM_INCLUDE_RTE == STD_ON */
      case DCM_USE_DATA_ASYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          if (pIOControlDIDContext->InitSignalProcessing == TRUE)
          {
            /* Call the interface function 'ReturnControlToEcu' for async operation */
            RetVal = dataCfg->ReturnControlToEcuAsync(DCM_INITIAL, &nrc);
            pIOControlDIDContext->InitSignalProcessing = FALSE;
          }
          else
          {
            /* Call the interface function 'ReturnControlToEcu' for async operation */
            RetVal = dataCfg->ReturnControlToEcuAsync(OpStatus, &nrc);
          }
        }
        else
        {
          RetVal = E_OK;
        }
        break;

      default:
        break;
    }

    serviceProcessStatus = Dcm_DspInternal_IOControl_InterfaceRetValCheck(pMsgContext,
                         pIOControlDIDContext, dataCfg, nrc, RetVal, DCM_SVCID_RETURNCONTROLTOECU);
  }

  if ((((serviceProcessStatus == DCM_E_OK) && (RetVal == DCM_E_OK)) && (OpStatus != DCM_CANCEL)) ||
      (pIOControlDIDContext->RequestProcessingSt == DCM_DID_READ_PENDING))
  {
    /* NRC is already set from inside the function if the signal reading fails */
    serviceProcessStatus = Dcm_DspInternal_IOControl_ReadSignals(OpStatus, pMsgContext, instIdx);
  }
  else
  {
    /* Do Nothing */
  }

  DBG_DCM_DSPINTERNAL_IORETURNCONTROLTOECU_DATA_EXIT(serviceProcessStatus,
                                                     pMsgContext,
                                                     DCM_INST(instIdx),
                                                     OpStatus);
  return serviceProcessStatus;
}

/* Sub-handler for IOControl 'ResetToDefault' */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOResetToDefault_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  /* holds the context information of currently processed DID */
  P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext =
                                                    &DCM_IO_CONTROL_DID_CONTEXT(instIdx);
  /* holds the number of signals in the DID */
  uint16 numSignals = Dcm_DidTable[pIOControlDIDContext->DidIndex].NumSignals;
  boolean controlMaskStatus = FALSE;
  Dcm_NegativeResponseCodeType nrc = E_OK;

  DBG_DCM_DSPINTERNAL_IORESETTODEFAULT_DATA_ENTRY(pMsgContext,DCM_INST(instIdx),OpStatus);

  /* Dcm581: In case of more than one supported I/O signal per DataIdentifier, the DCM shall
     internally consider the parameter controlEnableMaskRecord and control only the included signals
     in the request message */
  while ((pIOControlDIDContext->SignalInd < numSignals) &&
          /* Deviation MISRA-2 */
         (serviceProcessStatus != DCM_E_PENDING) && (serviceProcessStatus != DCM_E_NOT_OK) &&
         (pIOControlDIDContext->RequestProcessingSt != DCM_DID_READ_PENDING))
  {
    /* holds the configuration of signal being processed */
    P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg =
    &Dcm_DidDataTable[Dcm_DidTable[pIOControlDIDContext->DidIndex].
    Signals[pIOControlDIDContext->SignalInd].DspDataIndex];

    controlMaskStatus = Dcm_DspInternal_IOControl_CheckControlMask(&(pMsgContext->reqData[3]),
                                                            pIOControlDIDContext, numSignals);
    /* As per the Data interface of the signal Data*/
    switch (dataCfg->AccessInterface)
    {
#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
#endif /*DCM_INCLUDE_RTE == STD_ON*/
      case DCM_USE_DATA_SYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          /* Call the interface function 'ResetToDefault' for sync operation */
          RetVal = dataCfg->ResetToDefaultSync(&nrc);
        }
        else
        {
          RetVal = E_OK;
        }
        break;

#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
#endif /*DCM_INCLUDE_RTE == STD_ON*/
      case DCM_USE_DATA_ASYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          if (pIOControlDIDContext->InitSignalProcessing == TRUE)
          {
            /* Call the interface function 'ResetToDefault' for async operation */
            RetVal = dataCfg->ResetToDefaultAsync(DCM_INITIAL, &nrc);
            pIOControlDIDContext->InitSignalProcessing = FALSE;
          }
          else
          {
            /* Call the interface function 'ResetToDefault' for async operation */
            RetVal = dataCfg->ResetToDefaultAsync(OpStatus, &nrc);
          }
        }
        else
        {
          RetVal = E_OK;
        }
        break;

      default:
        break;
    }

    serviceProcessStatus = Dcm_DspInternal_IOControl_InterfaceRetValCheck(pMsgContext,
                           pIOControlDIDContext, dataCfg, nrc, RetVal, DCM_SVCID_RESETTODEFAULT);
  }

  if ((((serviceProcessStatus == DCM_E_OK) && (RetVal == DCM_E_OK)) && (OpStatus != DCM_CANCEL)) ||
      (pIOControlDIDContext->RequestProcessingSt == DCM_DID_READ_PENDING))
  {
    /* NRC is already set from inside the function if the signal reading fails */
    serviceProcessStatus = Dcm_DspInternal_IOControl_ReadSignals(OpStatus, pMsgContext, instIdx);
  }
  else
  {
    /* Do Nothing */
  }

  DBG_DCM_DSPINTERNAL_IORESETTODEFAULT_DATA_EXIT(serviceProcessStatus,
                                                 pMsgContext,
                                                 DCM_INST(instIdx),
                                                 OpStatus);
  return serviceProcessStatus;
}

/* Sub-handler for IOControl 'FreezeCurrentState' */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOFreezeCurrentState_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext =
                                                    &DCM_IO_CONTROL_DID_CONTEXT(instIdx);
  /* Holds the number of signals in the DID */
  uint16 numSignals = Dcm_DidTable[pIOControlDIDContext->DidIndex].NumSignals;
  boolean controlMaskStatus = FALSE;
  Dcm_NegativeResponseCodeType nrc = E_OK;

  DBG_DCM_DSPINTERNAL_IOFREEZECURRENTSTATE_DATA_ENTRY(pMsgContext,DCM_INST(instIdx),OpStatus);

  /* Dcm581: In case of more than one supported I/O signal per DataIdentifier, the DCM shall
     internally consider the parameter controlEnableMaskRecord and control only the included signals
     in the request message */
  while ((pIOControlDIDContext->SignalInd < numSignals) &&
          /* Deviation MISRA-2 */
         (serviceProcessStatus != DCM_E_PENDING) && (serviceProcessStatus != DCM_E_NOT_OK) &&
         (pIOControlDIDContext->RequestProcessingSt != DCM_DID_READ_PENDING))
  {
    /* holds the configuration of signal being processed */
    P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg =
    &Dcm_DidDataTable[Dcm_DidTable[pIOControlDIDContext->DidIndex].
    Signals[pIOControlDIDContext->SignalInd].DspDataIndex];

    controlMaskStatus = Dcm_DspInternal_IOControl_CheckControlMask(&(pMsgContext->reqData[3]),
                                                            pIOControlDIDContext, numSignals);
    /* As per the Data interface of the signal Data*/
    switch (dataCfg->AccessInterface)
    {
#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
#endif /*DCM_INCLUDE_RTE == STD_ON*/
      case DCM_USE_DATA_SYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          /* Call the interface function 'FreezeCurrentState' for sync operation */
          RetVal = dataCfg->FreezeCurrentStateSync(&nrc);
        }
        else
        {
          RetVal = E_OK;
        }
        break;

#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
#endif /*DCM_INCLUDE_RTE == STD_ON*/
      case DCM_USE_DATA_ASYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          if (pIOControlDIDContext->InitSignalProcessing == TRUE)
          {
            /* Call the interface function 'FreezeCurrentState' for async operation */
            RetVal = dataCfg->FreezeCurrentStateAsync(DCM_INITIAL, &nrc);
            pIOControlDIDContext->InitSignalProcessing = FALSE;
          }
          else
          {
            /* Call the interface function 'FreezeCurrentState' for async operation */
            RetVal = dataCfg->FreezeCurrentStateAsync(OpStatus, &nrc);
          }
        }
        else
        {
          RetVal = E_OK;
        }
        break;

      default:
        break;
    }

    serviceProcessStatus = Dcm_DspInternal_IOControl_InterfaceRetValCheck(pMsgContext,
                        pIOControlDIDContext, dataCfg, nrc, RetVal, DCM_SVCID_FREEZECURRENTSTATE);
  }

  if ((((serviceProcessStatus == DCM_E_OK) && (RetVal == DCM_E_OK)) && (OpStatus != DCM_CANCEL)) ||
      (pIOControlDIDContext->RequestProcessingSt == DCM_DID_READ_PENDING))
  {
    /* NRC is already set from inside the function if the signal reading fails */
    serviceProcessStatus = Dcm_DspInternal_IOControl_ReadSignals(OpStatus, pMsgContext, instIdx);
  }
  else
  {
    /* Do Nothing */
  }

  DBG_DCM_DSPINTERNAL_IOFREEZECURRENTSTATE_DATA_EXIT(serviceProcessStatus,
                                                     pMsgContext,
                                                     DCM_INST(instIdx),
                                                     OpStatus);
  return serviceProcessStatus;
}

/* Sub-handler for IOControl 'ShortTermAdjustment' */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOShortTermAdjustment_Data(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Std_ReturnType RetVal = E_NOT_OK;
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext =
                                                    &DCM_IO_CONTROL_DID_CONTEXT(instIdx);
  /* Holds the number of signals in the DID */
  uint16 numSignals = Dcm_DidTable[pIOControlDIDContext->DidIndex].NumSignals;
  /* Holds the confguration table of signals in the DID */
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg =
          Dcm_DidTable[pIOControlDIDContext->DidIndex].Signals;

  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) LastSignalCfg =
          &(Dcm_DidTable[pIOControlDIDContext->DidIndex].Signals[numSignals - 1U]);
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) LastSignaldataCfg =
                                           &Dcm_DidDataTable[LastSignalCfg->DspDataIndex];
  uint16 DidDataLength = DCM_GET_BYTES(LastSignalCfg->DataPos + LastSignaldataCfg->DataLength);
  boolean controlMaskStatus = FALSE;
  uint16 signalLength = 0U;
  Dcm_NegativeResponseCodeType nrc = E_OK;

  DBG_DCM_DSPINTERNAL_IOSHORTTERMADJUSTMENT_DATA_ENTRY(pMsgContext,DCM_INST(instIdx),OpStatus);

  /* Dcm581: In case of more than one supported I/O signal per DataIdentifier, the DCM shall
     internally consider the parameter controlEnableMaskRecord and control only the included signals
     in the request message */
  while ((pIOControlDIDContext->SignalInd < numSignals) &&
          /* Deviation MISRA-2 */
         (serviceProcessStatus != DCM_E_PENDING) && (serviceProcessStatus != DCM_E_NOT_OK) &&
         (pIOControlDIDContext->RequestProcessingSt != DCM_DID_READ_PENDING))
  {
    /* buffer for temporarily holding the signgal data */
    uint8 signalBuffer[DCM_DATA_MAX_SIZE];
    uint16_least j;
    /* bit-position of signal data in request buffer */
    uint16 didDataPosn = SignalCfg[pIOControlDIDContext->SignalInd].DataPos;
    /* holds the configuration of signal being processed */
    P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg =
    &Dcm_DidDataTable[SignalCfg[pIOControlDIDContext->SignalInd].DspDataIndex];

    for (j = 0; j < DCM_DATA_MAX_SIZE ; j++)
    {
      signalBuffer[j] = 0x00U;
    }
    controlMaskStatus = Dcm_DspInternal_IOControl_CheckControlMask(
             &(pMsgContext->reqData[3U + DidDataLength]), pIOControlDIDContext, numSignals);

    /* the length of the signal is the length of the request, minus the DID identifier size
    (2 bytes), minus one byte of ControlOptionRecord. */
    signalLength = pMsgContext->reqDataLen - (DCM_DID_ID_SIZE + 1U);

    /* The interface type of the currently processed signal data */
    switch (dataCfg->AccessInterface)
    {
#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
#endif /*DCM_INCLUDE_RTE == STD_ON*/
      case DCM_USE_DATA_SYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          Dcm_DspInternal_SignalDataCopying(pMsgContext, dataCfg, didDataPosn, signalBuffer,
                                            instIdx);
          /* Call the interface function of 'ShortTermAdjustment' for sync operation */

          if (dataCfg->FixedLength == TRUE)
          {
            RetVal = dataCfg->ShortTermAdjustmentFixedSync(signalBuffer, &nrc);
          }
          else
          {
            RetVal = dataCfg->ShortTermAdjustmentVariableSync(signalBuffer,
                                                              signalLength,
                                                              &nrc);
          }
        }
        else
        {
          RetVal = E_OK;
        }
        break;

#if (DCM_INCLUDE_RTE == STD_ON)
      case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
#endif /*DCM_INCLUDE_RTE == STD_ON*/
      case DCM_USE_DATA_ASYNCH_FUNC:
        if(controlMaskStatus == TRUE)
        {
          Dcm_DspInternal_SignalDataCopying(pMsgContext, dataCfg, didDataPosn, signalBuffer,
                                            instIdx);
          /* Call the interface function of 'ShortTermAdjustment' for async operation */
          if (dataCfg->FixedLength == TRUE)
          {
            if (pIOControlDIDContext->InitSignalProcessing == TRUE)
            {
              RetVal = dataCfg->ShortTermAdjustmentFixedAsync(signalBuffer, DCM_INITIAL, &nrc);
              pIOControlDIDContext->InitSignalProcessing = FALSE;
            }
            else
            {
              RetVal = dataCfg->ShortTermAdjustmentFixedAsync(signalBuffer, OpStatus, &nrc);
            }
          }
          else
          {
            if (pIOControlDIDContext->InitSignalProcessing == TRUE)
            {
              RetVal = dataCfg->ShortTermAdjustmentVariableAsync(signalBuffer,
                                                                 signalLength,
                                                                 DCM_INITIAL,
                                                                 &nrc);
              pIOControlDIDContext->InitSignalProcessing = FALSE;
            }
            else
            {
              RetVal = dataCfg->ShortTermAdjustmentVariableAsync(signalBuffer,
                                                                 signalLength,
                                                                 OpStatus,
                                                                 &nrc);
            }
          }
        }
        else
        {
          RetVal = E_OK;
        }
        break;

      default:
        break;
    }

    serviceProcessStatus = Dcm_DspInternal_IOControl_InterfaceRetValCheck(pMsgContext,
                       pIOControlDIDContext, dataCfg, nrc, RetVal, DCM_SVCID_SHORTTERMADJUSTMENT);
  }

  if ((((serviceProcessStatus == DCM_E_OK) && (RetVal == DCM_E_OK)) && (OpStatus != DCM_CANCEL)) ||
      (pIOControlDIDContext->RequestProcessingSt == DCM_DID_READ_PENDING))
  {
    /* NRC is already set from inside the function if the signal reading fails */
    serviceProcessStatus = Dcm_DspInternal_IOControl_ReadSignals(OpStatus, pMsgContext, instIdx);
  }
  else
  {
    /* Do Nothing */
  }

  DBG_DCM_DSPINTERNAL_IOSHORTTERMADJUSTMENT_DATA_EXIT(serviceProcessStatus,
                                                      pMsgContext,
                                                      DCM_INST(instIdx),
                                                      OpStatus);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControl_InterfaceRetValCheck(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext,
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint8 nrc, uint8 interfaceRetVal, uint8 interfaceID)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_IOCONTROL_INTERFACERETVALCHECK_ENTRY(pMsgContext,
                                                           pIOControlDIDContext,
                                                           dataCfg,
                                                           nrc,
                                                           interfaceRetVal,
                                                           interfaceID);

#if (DCM_DEV_ERROR_DETECT == STD_OFF)
  TS_PARAM_UNUSED(interfaceID);
#endif
  /* If the currently processed signal was controlled successfully, increment the signal index */
  if (interfaceRetVal == DCM_E_OK)
  {
    pIOControlDIDContext->SignalInd++;
    pIOControlDIDContext->InitSignalProcessing = TRUE;
    serviceProcessStatus = DCM_E_OK;
  }
  else if(interfaceRetVal == DCM_E_NOT_OK)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, nrc);
    serviceProcessStatus = DCM_E_NOT_OK;
  }
  else if ((interfaceRetVal == DCM_E_PENDING) &&
           ((dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_FUNC) ||
            (dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_CLIENT_SERVER)
           ))
  {
    serviceProcessStatus = DCM_E_PENDING;
  }
  else
  {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    /* Report Develpment Error */
    DCM_DET_REPORT_ERROR(interfaceID, DCM_E_INTERFACE_RETURN_VALUE);
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
    serviceProcessStatus = DCM_E_NOT_OK;
#endif
  }

  DBG_DCM_DSPINTERNAL_IOCONTROL_INTERFACERETVALCHECK_EXIT(serviceProcessStatus,
                                                          pMsgContext,
                                                          pIOControlDIDContext,
                                                          dataCfg,
                                                          nrc,
                                                          interfaceRetVal,
                                                          interfaceID);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControl_ReadSignals(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 instIdx)
{
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext =
                                                    &DCM_IO_CONTROL_DID_CONTEXT(instIdx);
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_IOCONTROL_READSIGNALS_ENTRY(OpStatus,pMsgContext,DCM_INST(instIdx));

  serviceProcessStatus = Dcm_DspInternal_ReadDid(pIOControlDIDContext->DidIndex,
                                                 instIdx, OpStatus, pMsgContext);
  /* If response data needs further processing */
  if(serviceProcessStatus == DCM_E_PENDING)
  {
    pIOControlDIDContext->RequestProcessingSt = DCM_DID_READ_PENDING;
  }
  else
  {
    /* Set the 'RequestProcessingSt' to INVALID indicating that signal reading is over */
    pIOControlDIDContext->RequestProcessingSt = DCM_DID_REQUEST_INVALID;
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_IOCONTROL_READSIGNALS_EXIT(serviceProcessStatus,
                                                 OpStatus,
                                                 pMsgContext,
                                                 DCM_INST(instIdx));
  return serviceProcessStatus;
}

STATIC FUNC(boolean, DCM_CODE) Dcm_DspInternal_IOControl_CheckControlMask(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) reqData,
  P2CONST(Dcm_IOControlDIDContextType, AUTOMATIC, DCM_APPL_DATA) pIOControlDIDContext,
  uint16 numSignals)
{
  boolean controlMaskStatus = FALSE;

  DBG_DCM_DSPINTERNAL_IOCONTROL_CHECKCONTROLMASK_ENTRY(reqData,pIOControlDIDContext,numSignals);

  /* This checks if the bit position corresponding to the signal
     is set in the 'controlEnableMaskRecord' */
  if ((((reqData[pIOControlDIDContext->SignalInd / 8])&
       (DCM_CONTROL_MASK_MSB >> (pIOControlDIDContext->SignalInd % 0x08U))) != 0U) ||
       (numSignals == 1U))
  {
    /* Control mask for the corresponding signal is set */
    controlMaskStatus = TRUE;
  }

  DBG_DCM_DSPINTERNAL_IOCONTROL_CHECKCONTROLMASK_EXIT(controlMaskStatus,
                                                      reqData,
                                                      pIOControlDIDContext,
                                                      numSignals);
  return controlMaskStatus;
}

STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_SignalDataCopying(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint16 didDataPosition,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint8 instIdx)
{
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
  /* Get configuration for current HSM instance */
  CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig = &DCM_HSM_CONFIG(instIdx);
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */

  DBG_DCM_DSPINTERNAL_SIGNALDATACOPYING_ENTRY(pMsgContext,dataCfg,didDataPosition,
                                              signalBuffer,DCM_INST(instIdx));

#if ((DCM_HSM_INST_MULTI_ENABLED == STD_OFF) || (DCM_ENDIANNESS_CONVERSION == STD_OFF))
  TS_PARAM_UNUSED(instIdx);
#endif

  /* If signal data length is fixed */
  if (dataCfg->FixedLength == TRUE)
  {
    /* Copy the data of currently processed signal to signalBuffer */
    Dcm_DspInternal_CopySignalData(&pMsgContext->reqData[DCM_DID_ID_SIZE + 1U], signalBuffer,
                                   didDataPosition, 0U, dataCfg->DataLength);
  }
  else
  {
    uint16 signalLength = pMsgContext->reqDataLen - (DCM_DID_ID_SIZE + 1U);

    /* Copy all the data in the request, after DID, to signalBuffer */
    Dcm_DspInternal_CopySignalData(&pMsgContext->reqData[DCM_DID_ID_SIZE + 1U], signalBuffer,
                                   didDataPosition, 0U, DCM_GET_BITS(signalLength));
  }
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
  if(((dataCfg->DataType == DCM_TYPE_SINT16) || (dataCfg->DataType == DCM_TYPE_UINT16) ||
      /* Deviation MISRA-2 */
      (dataCfg->DataType == DCM_TYPE_SINT32) || (dataCfg->DataType == DCM_TYPE_UINT32)) &&
      (curHsmConfig->endianessConversion == TRUE)
    )
  {
    Dcm_DspInternal_Endianness_Conversion(signalBuffer, dataCfg->DataType);
  }
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */

  DBG_DCM_DSPINTERNAL_SIGNALDATACOPYING_EXIT(pMsgContext,dataCfg,didDataPosition,
                                             signalBuffer,DCM_INST(instIdx));
}

/* The function for checking the request data length of IOControl request */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_IOControlDidRequestLengthChk(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)

{
  Std_ReturnType RetVal = E_NOT_OK;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* Index of DID currently being processed */
  uint16 didIndex = DCM_IO_CONTROL_DID_CONTEXT(instIdx).DidIndex;
  uint16 numSignals = Dcm_DidTable[didIndex].NumSignals;
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg =
                                               &(Dcm_DidTable[didIndex].Signals[numSignals - 1]);
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg =
                                               &Dcm_DidDataTable[SignalCfg->DspDataIndex];
  /* Calculate the total number of data bytes needed for all the signals configured in the DID.
   * The signals corresponding to a DID are stored in the order of starting position of signal
   * data in response buffer. So the total number of data bytes needed for all the signals in a
   * DID can be calculated by adding the position and size of the last signal configured for the
   * DID.
   */
  uint16 DidSignalsDataLength;

  DBG_DCM_DSPINTERNAL_IOCONTROLDIDREQUESTLENGTHCHK_ENTRY(pMsgContext);

  /* The controlEnableMaskRecord is only present, if the DataIdentifer supports morethan
     one signal */
  if (numSignals > 1U)
  {
    if(pMsgContext->reqData[2] == DCM_SHORTTERMADJUSTMENT)
    { /* Incase of ShortTermAdjustment IOControl parameter total number of data bytes in request can
      be calculated by adding the position and size of the last signal configured for the DID and
      controlMask bytes. Number of control mask bytes in a request depends on number of signal
      configured for the DID  */
      DidSignalsDataLength = DCM_GET_BYTES(SignalCfg->DataPos + dataCfg->DataLength) +
                           DCM_GET_BYTES(numSignals); /* Signal data bytes + ControlMask bytes */
    }
    else
    {
      /* If IOControl parameter is other than ShortTermAdjustment then total number of bytes
      (ControlMAsk byte) in request depends on number of signal configured for the DID. No data
      bytes present in request in this case. */
      DidSignalsDataLength = DCM_GET_BYTES(numSignals); /* ControlMask bytes */
    }
  }
  else
  {
    if(pMsgContext->reqData[2] == DCM_SHORTTERMADJUSTMENT)
    { /* Incase of ShortTermAdjustment IOControl parameter, if only one signal is configured for the
      DID then total number of data bytes in request can be calculated by adding the position and
      size of the signal configured for the DID and no controlMask bytes present in request. */
      DidSignalsDataLength = DCM_GET_BYTES(SignalCfg->DataPos + dataCfg->DataLength);
    }
    else
    { /* If IOControl parameter is other than ShortTermAdjustment, if only one signal is configured
      for the DID then no data byte present in request. */
      DidSignalsDataLength = 0U;
    }
  }

  /* if data length for the signal is fixed, total length configured for the DID should be equal
     to the (length of request data - (size of DID[2 bytes] + 1)) */
  if (dataCfg->FixedLength == TRUE)
  {
    if (DidSignalsDataLength == (pMsgContext->reqDataLen - (DCM_DID_ID_SIZE + 1U)))
    {
      RetVal = E_OK;
    }
  }
  /* if data length for the signal is dynamic, total length configured for the DID should be
     greater than or equal to the (length of request data - (size of DID[2 bytes] + 1)) */
  else
  {
    if (DidSignalsDataLength >= (pMsgContext->reqDataLen - (DCM_DID_ID_SIZE + 1U)))
    {
      RetVal = E_OK;
    }
  }

  DBG_DCM_DSPINTERNAL_IOCONTROLDIDREQUESTLENGTHCHK_EXIT(RetVal,pMsgContext);
  return RetVal;
}

FUNC(void, DCM_CODE) Dcm_DspInternal_ReturnControlToEcuforallSignals(void)
{
  DBG_DCM_DSPINTERNAL_RETURNCONTROLTOECUFORALLSIGNALS_ENTRY();

  while(Dcm_ReturnControlToEcuContext.didIndex < DCM_NUM_DID)
  {
    Std_ReturnType RetVal = E_OK;
    if(Dcm_DidTable[Dcm_ReturnControlToEcuContext.didIndex].ControlAccess.Enabled == TRUE)
    {
      /* Process all the signals in the DID */
      while( (RetVal != DCM_E_PENDING) && (Dcm_ReturnControlToEcuContext.returnToEcuSigInd <
              Dcm_DidTable[Dcm_ReturnControlToEcuContext.didIndex].NumSignals) )
      {
        if( (Dcm_DidTable[Dcm_ReturnControlToEcuContext.didIndex].
                FreezeCurrentStateEnable == TRUE) ||
            (Dcm_DidTable[Dcm_ReturnControlToEcuContext.didIndex].
                ResetToDefaultEnable == TRUE) ||
            (Dcm_DidTable[Dcm_ReturnControlToEcuContext.didIndex].
                ShortTermAdjustmentEnable == TRUE)
          )
        {
          /* Holds the confguration table of signals in the DID */
          P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg =
                Dcm_DidTable[Dcm_ReturnControlToEcuContext.didIndex].Signals;
          /* Holds the configuration of signal being processed */
          P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg =
              &Dcm_DidDataTable[SignalCfg[Dcm_ReturnControlToEcuContext.returnToEcuSigInd].
                  DspDataIndex];
          Dcm_NegativeResponseCodeType curNrc = DCM_E_OK;
          /* Validate the coditions to stop all the control in progress and return control to ECU.*/
          if( (dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_FUNC) ||
              (dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_CLIENT_SERVER))
          {
            /* Call configured interfaces regardless whether the User has enabled
               DcmDspDidReturnControlToEcu for this DID's signals */
            if(dataCfg->ReturnControlToEcuAsync != NULL_PTR)
            {
              /* Call the user function to return control to ECU of an IOControl */
              RetVal = dataCfg->ReturnControlToEcuAsync(DCM_INITIAL, &curNrc);
              if(RetVal == E_OK)
              {
                /* Status will be set to DCM_RET_CTRL_FINISHED at the end of the function, after
                   completion of processing all the signals for all DID's */
              }
              else if(RetVal == DCM_E_PENDING)
              {
                Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus = DCM_RET_CTRL_PENDING;
#if (DCM_DSP_RETURN_CONTROLTOECU_TIMEOUT_REPORT == STD_ON)
                /* returnControlToEcu operation returns PENDING, so increment the timeoutCount */
                Dcm_ReturnControlToEcuContext.timeoutCount++;
#endif
              }
              else
              {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
                if(RetVal != E_NOT_OK)
                {
                  /* Report Development Error for invalid return value */
                  DCM_DET_REPORT_ERROR(DCM_SVCID_RETURNCONTROLTOECU,
                                       DCM_E_INTERFACE_RETURN_VALUE);
                }
                else
                {
                  /* Report Development Error */
                  DCM_DET_REPORT_ERROR(DCM_SVCID_RETURNCONTROLTOECU,
                                       DCM_E_RETURNCONTROLTOECU_FAIL);
                }
#endif
              }
            }
          }
          else
          {
            if( (dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_FUNC) ||
                (dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_CLIENT_SERVER))
            {
              /* Call configured interfaces regardless whether the User has enabled
                 DcmDspDidReturnControlToEcu for this DID's signals */
              if(dataCfg->ReturnControlToEcuSync != NULL_PTR)
              {
                /* Call the user function to return control to ECU of an IOControl */
                RetVal = dataCfg->ReturnControlToEcuSync(&curNrc);
#if (DCM_DEV_ERROR_DETECT == STD_ON)
                if(RetVal == E_NOT_OK)
                {
                  /* Report Development Error */
                  DCM_DET_REPORT_ERROR(DCM_SVCID_RETURNCONTROLTOECU,
                                       DCM_E_RETURNCONTROLTOECU_FAIL);
                }
                else
                {
                  if(RetVal != E_OK)
                  {
                    /* Report Development Error for invalid return value */
                    DCM_DET_REPORT_ERROR(DCM_SVCID_RETURNCONTROLTOECU,
                                         DCM_E_INTERFACE_RETURN_VALUE);
                  }
                }
#endif
              }
            }
          }
          /* Proceed with next signal if interface returns other than DCM_E_PENDING */
          if(RetVal != DCM_E_PENDING)
          {
            Dcm_ReturnControlToEcuContext.returnToEcuSigInd++;
          }
        }
        else
        {
          Dcm_ReturnControlToEcuContext.returnToEcuSigInd++;
        }
      }
      if( Dcm_ReturnControlToEcuContext.returnToEcuSigInd ==
         Dcm_DidTable[Dcm_ReturnControlToEcuContext.didIndex].NumSignals
        )
      {
        Dcm_ReturnControlToEcuContext.returnToEcuSigInd = 0U;
        Dcm_ReturnControlToEcuContext.didIndex++;
      }
      else
      {
        /* One of the signal returns PENDING, hence exit DID loop */
        break;
      }
    }
    else
    {
      Dcm_ReturnControlToEcuContext.returnToEcuSigInd = 0U;
      Dcm_ReturnControlToEcuContext.didIndex++;
    }
  }
  if(Dcm_ReturnControlToEcuContext.didIndex == DCM_NUM_DID)
  {
    /* Processing for all signals and DIS's completed. Set the finished status finally */
    Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus = DCM_RET_CTRL_FINISHED;
    Dcm_ReturnControlToEcuContext.didIndex = 0U;
    /* returnControlToEcu operation completed, so reset the timeoutCount */
    Dcm_ReturnControlToEcuContext.timeoutCount = 0U;
  }

  DBG_DCM_DSPINTERNAL_RETURNCONTROLTOECUFORALLSIGNALS_EXIT();
}
#endif  /* #if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)  */

#if(DCM_DSP_USE_SERVICE_0X31 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RoutineControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_RoutineControl_SvcStart(OpStatus, pMsgContext);
      break;

    case DCM_FORCE_RCRRP_OK:
      /* Sub-sequent call to the service function after FORCE_RCRRP */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_RoutineControl_SvcCont(OpStatus, pMsgContext);
      break;
    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_RoutineControl_SvcCont(OpStatus, pMsgContext);
      break;
    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RoutineControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint8_least i;
  uint16_least ridTabIndex = 0U;
  Dcm_NegativeResponseCodeType curNrc = DCM_E_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  uint16 routineID;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
         &DCM_SES_TAB_CONFIG(instIdx);

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get pointer to routine configuration table  */
  P2CONST(Dcm_DspRoutineServicesType, AUTOMATIC, DCM_CONST) curRoutineConfig
    = Dcm_DspRoutineConfig;

  /* get pointer to routine configuration info table  */
  P2CONST(Dcm_DspRoutineServicesInfoType, AUTOMATIC, DCM_CONST) curRoutineConfigInfo
    = NULL_PTR;

  DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCSTART_ENTRY(OpStatus,pMsgContext);

  /* check request length */
  if (pMsgContext->reqDataLen >= 3U)
  {
    /* Get current routine id */
    routineID = (uint16)((uint16)((uint16)pMsgContext->reqData[1U] << 8U) +
                ((uint16)pMsgContext->reqData[2U]));

    /* search list of configured routines */
    while ( ridTabIndex < DCM_NUM_ROUTINES )
    {
      if ((curRoutineConfig[ridTabIndex].Identifier) == routineID)
      {
        /* Rotine identifier is valid; update pointer to routine configuration table */
        curRoutineConfig = &Dcm_DspRoutineConfig[ridTabIndex];

        /* Update pointer to routine configuration info table */
        curRoutineConfigInfo = curRoutineConfig->RoutineInfoRef;

        break;
      }
      else
      {
        ridTabIndex++;
      }
    }

    /* if the Routine is not supported, DCM module shall send NRC 0x31 */
    if ( ridTabIndex >= DCM_NUM_ROUTINES )
    {
      curNrc = DCM_E_REQUESTOUTOFRANGE;
    }
    else
    {
      /*
       * check if the Routine can be executed in the current session
       */

      /* If no session control configuration is provided for the routine,
         no check of session level shall be done */
      if ( curRoutineConfigInfo->NumSesLevels > 0U )
      {
        /* get current session type */
        const Dcm_SesCtrlType curSesCtrl =
        sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl;

        /*
         * check if routine is allowed in current session
         */
        for (i = 0U; i < curRoutineConfigInfo->NumSesLevels; ++i)
        {
          if ((curRoutineConfigInfo->SessionRef[i] == DCM_ALL_SESSION_LEVEL) ||
               (curRoutineConfigInfo->SessionRef[i] == curSesCtrl))
          {
            break;
          }
        }
        /* Dcm570 : If the Routine can't be executed in the current session, DCM module shall send
           NRC 0x31 */
        if ( i >= curRoutineConfigInfo->NumSesLevels )
        {
          curNrc = DCM_E_REQUESTOUTOFRANGE;
        }
      }

      /*
       * check if the Routine can be executed in the current security level
       */
      if ((curNrc == DCM_E_OK) && (curRoutineConfigInfo->NumSecLevels > 0U))
      {
        /* if DCM is in unlocked state */
        if (curHsmInfo->secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
        {
          /* get current security level */
          Dcm_SecLevelType curSecLevel = Dcm_SecTabConfig.Entries[curHsmInfo->secTabIdx].SecLevel;

          /*
           * check if Routine is allowed with current security level
           */
          for (i = 0U; i < curRoutineConfigInfo->NumSecLevels; ++i)
          {
            if (curRoutineConfigInfo->SecurityLevelRef[i] == curSecLevel)
            {
              break;
            }
          }
          /* if the Routine can be executed in the current security level, DCM module shall
             send NRC 0x33 */
          if (i >= curRoutineConfigInfo->NumSecLevels)
          {
            curNrc = DCM_E_SECURITYACCESSDENIED;
          }
        }
        else
        {
          curNrc = DCM_E_SECURITYACCESSDENIED;
        }
      }
    }
  }
  else
  {
    curNrc = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
  }

  /* If all verifications have been successfull, call the Routine handler */
  if ( curNrc == DCM_E_OK )
  {
    serviceProcessStatus = Dcm_DspInternal_RoutineControl_SvcCont(OpStatus, pMsgContext);
  }
  else
  {
    /* Verification failed; set the respective error code */
    Dcm_ExternalSetNegResponse(pMsgContext, curNrc);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RoutineControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint16_least ridTabIndex = 0U;
  /* local msgcontext variable to be used for sub-function handler */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Std_ReturnType retVal = E_NOT_OK;
  Dcm_NegativeResponseCodeType ErrorCode;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get instIdx */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get pointer to routine configuration table  */
  P2CONST(Dcm_DspRoutineServicesType, AUTOMATIC, DCM_CONST) curRoutineConfig
    = Dcm_DspRoutineConfig;
  uint16 routineID ;

  /* Get the sub-function ID */
  uint8 SubFunction = curHsmInfo->subServiceId;

  DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCCONT_ENTRY(OpStatus,pMsgContext);

  if(OpStatus == DCM_INITIAL)
  {
    /* Get current routine id */
    routineID = (uint16)((uint16)((uint16)pMsgContext->reqData[1] << 8U) +
                     ((uint16)pMsgContext->reqData[2]));
    /* assign the data from msgcontext for service to that of sub-function.*/
    /* point the reqData behind the sub-function */
    pMsgContext->reqData = &pMsgContext->reqData[1];

    /* decrement the reqData length as sub-function is removed */
    pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;
  }
  /* SubFunction is removed when OpStatus is DCM_INITIAL */
  else
  {
    /* Get current routine id */
  routineID = (uint16)((uint16)((uint16)pMsgContext->reqData[0] << 8U) +
                     ((uint16)pMsgContext->reqData[1]));
  }

  /* search list of configured routines */
  while ( ridTabIndex < DCM_NUM_ROUTINES )
  {
    if ((curRoutineConfig[ridTabIndex].Identifier) == routineID)
    {
      /* Rotine identifier is valid; update pointer to routine configuration table */
      curRoutineConfig = &Dcm_DspRoutineConfig[ridTabIndex];

      break;
    }
    else
    {
      ridTabIndex++;
    }
  }

  switch (SubFunction)
  {
    case 0x01:

      /* Call function handler for request to application to start a routine */
      retVal = curRoutineConfig->StartFncHandler(OpStatus, pMsgContext, &ErrorCode);

       /* Set the routine status as DCM_ROUTINE_STARTED only when the start routine interface
        * function returns E_OK */
      if ( retVal == E_OK )
      {
        Dcm_DspRoutineStatus[ridTabIndex] = DCM_ROUTINE_STARTED;
      }
      break;

    case 0x02:
      if ( curRoutineConfig->StopFncHandler != NULL_PTR )
      {
        if ( Dcm_DspRoutineStatus[ridTabIndex] == DCM_ROUTINE_STARTED )
        {
          /* Call function handler for request to application to stop a routine */
          retVal = curRoutineConfig->StopFncHandler(OpStatus, pMsgContext, &ErrorCode);

           /* Set the routine status as DCM_ROUTINE_STOPPED only when the stop routine interface
            * function returns E_OK otherwise the status remains 'DCM_ROUTINE_STARTED' */
          if (retVal == E_OK)
          {
            Dcm_DspRoutineStatus[ridTabIndex] = DCM_ROUTINE_STOPPED;
          }
        }
        else
        {
          ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        }
      }
      else
      {
        ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
      }
      break;

    case 0x03:
      if ( curRoutineConfig->RequestResultsFncHandler != NULL_PTR )
      {
        if ( Dcm_DspRoutineStatus[ridTabIndex] != DCM_ROUTINE_INACTIVE )
        {
          /* Call function handler for request to application, the results of a routine  */
          retVal = curRoutineConfig->RequestResultsFncHandler(OpStatus, pMsgContext,
            &ErrorCode);
        }
        else
        {
          ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
        }
      }
      else
      {
        /* No function handler configured to request the results of the routine  */
        ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
      }
      break;

    default:
      /* The requested sub-function is not supported */
      ErrorCode = DCM_E_SUBFUNCTIONNOTSUPPORTED;
      break;
  }

  if(OpStatus != DCM_CANCEL)
  {
    if ( retVal == DCM_E_PENDING )
    {
      serviceProcessStatus = DCM_E_PENDING;
    }

    else if ( retVal == DCM_E_FORCE_RCRRP )
    {
      serviceProcessStatus = DCM_E_FORCE_RCRRP;
    }

    else if ( retVal == E_OK )
    {
      /* !LINKSTO Dcm222,1 */
      pMsgContext->resData[0] = curHsmInfo->subServiceId;
      pMsgContext->resData[1] = pMsgContext->reqData[0];
      pMsgContext->resData[2] = pMsgContext->reqData[1];
      serviceProcessStatus = DCM_E_DONE;
    }

    else
    {
      Dcm_ExternalSetNegResponse(pMsgContext, ErrorCode);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_ROUTINECONTROL_SVCCONT_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_DSP_USE_SERVICE_0X31 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X3E == STD_ON)
/* This is the handler implementation for UDS service 0x3E */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TesterPresent_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_TESTERPRESENT_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      /* check request length */
      if (pMsgContext->reqDataLen != 1U)
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      }
      /* check subfunctions */
      else if (pMsgContext->reqData[0] != 0U)
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SUBFUNCTIONNOTSUPPORTED);
      }
      else                          /* everything is ok now */
      {
        /* assemble response */
        pMsgContext->resData[0] = 0U;
        pMsgContext->resDataLen = 1U;
      }
      serviceProcessStatus = DCM_E_DONE;
      break;

    /* actions performed on sucessful sending of the response */
    case DCM_CONFIRMED_OK:
      serviceProcessStatus = DCM_E_DONE;
      break;

    /* actions performed on failure in sending of the response */
    case DCM_CONFIRMED_NOK:
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_TESTERPRESENT_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* (DCM_DSP_USE_SERVICE_0X3E == STD_ON) */

#if(DCM_0X85_SVC_ENABLED == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ControlDTCSetting_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_ControlDTCSetting_SvcStart(DCM_INITIAL, pMsgContext);
      break;

    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_ControlDTCSetting_SvcCont(DCM_PENDING, pMsgContext);
      break;

    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_ControlDTCSetting_SvcCont(DCM_CANCEL, pMsgContext);
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ControlDTCSetting_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* loop variable */
  uint8_least i;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8_least instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  Std_ReturnType serviceProcessStatus = DCM_E_DONE;

  /* get number of subservices */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  TS_PARAM_UNUSED(OpStatus);

  DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_ENTRY(pMsgContext);

  /* check request length */
  if (pMsgContext->reqDataLen >= 1U)
  {
    /* copy subfunction value to response buffer */
    pMsgContext->resData[0] = curHsmInfo->subServiceId;
    pMsgContext->resDataLen = 1U;

    for (i = 0U; i < numSubServ; i++)
    {
      /* Search for the index in subservices table for the requested subservice */
      if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
      {
        /* assign the data from msgcontext for service to that of sub-function.*/
        /* set request data pointer to received data without service and subservice Ids */
        pMsgContext->reqData = &pMsgContext->reqData[1];

        /* decrement the reqData length as sub-function is removed */
        pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;

        if (curSsConfig[i].IntSrvHandler != NULL_PTR)
        {
          /* Call internal sub-service handler*/
          serviceProcessStatus = curSsConfig[i].IntSrvHandler(DCM_INITIAL, pMsgContext);
        }
        else
        {
          /* Call External sub-service handler*/
          serviceProcessStatus = curSsConfig[i].ExtSrvHandler(DCM_INITIAL, pMsgContext);

          /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
          if (serviceProcessStatus == E_OK)
          {
            serviceProcessStatus = DCM_E_DONE;
          }
        }
      break;
      }
    }
  }
  else
  {
    /* The length of the message is wrong */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
  }

  DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ControlDTCSetting_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* loop variable */
  uint8 i;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  Std_ReturnType serviceProcessStatus = DCM_E_DONE;

  /* get number of subservices */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_ENTRY(pMsgContext);

  for (i = 0U; i < numSubServ; i++)
  {
    /* Search for the index in subservices table for the requested subservice */
    if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
    {
      if (curSsConfig[i].IntSrvHandler == NULL_PTR)
      {
        /* Call External sub-service handler*/
        serviceProcessStatus = curSsConfig[i].ExtSrvHandler(OpStatus, pMsgContext);

        /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
        if (serviceProcessStatus == E_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /* This code is unreachable */
      }
    break;
    }
  }

  DBG_DCM_DSPINTERNAL_CONTROLDTCSETTING_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

#if (DCM_0X85_0X01_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x85-0x01 handler */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DTCSettingTypeOn_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8_least instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* Used to return the status of Dem_EnableDTCSetting() */
  Dem_ReturnControlDTCSettingType DTCSettingStatus;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEON_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);

  /* Enables the DTC setting for the DTC group */
  DTCSettingStatus = Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);

  /* Deviation MISRA-2 */
  if( (DTCSettingStatus != DEM_CONTROL_DTC_SETTING_OK) &&
    (DTCSettingStatus != DEM_CONTROL_DTC_SETTING_N_OK) &&
    (DTCSettingStatus != DEM_CONTROL_DTC_WRONG_DTCGROUP) )
  {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
  DCM_DET_REPORT_ERROR(DCM_SVCID_DTCSETTINGON, DCM_E_INTERFACE_RETURN_VALUE);

  /* DTC setting control not successful because DEM returns development report error */
  Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
  }
  else if (DTCSettingStatus == DEM_CONTROL_DTC_SETTING_OK)
  {
    /* Set the Status of DTCDisable Status */
    curHsmInfo->dtcDisableStatus = FALSE;

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
    /* Dcm783 */
    (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
  }
  else if (DTCSettingStatus == DEM_CONTROL_DTC_SETTING_N_OK)
  {
    /* DTC setting control not successful */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
  }
  else
  {
    /* DTC setting control not successful because group of DTC was wrong */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  }

  DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEON_SSVCH_EXIT(DCM_E_DONE,OpStatus,pMsgContext);
  return DCM_E_DONE;
}
#endif  /* #if ( DCM_0X85_0X01_SSVC_ENABLED == STD_ON) */

#if (DCM_0X85_0X02_SSVC_ENABLED == STD_ON)
/* This is the UDS service 0x85-0x02 handler */
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DTCSettingTypeOff_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8_least instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* Used to return the status of Dem_DisableDTCSetting() */
  Dem_ReturnControlDTCSettingType DTCSettingStatus = DEM_CONTROL_DTC_SETTING_N_OK;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEOFF_SSVCH_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);

  /* Disables the DTC setting for the DTC group */
  DTCSettingStatus = Dem_DisableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);

  /* Deviation MISRA-2 */
  if( (DTCSettingStatus != DEM_CONTROL_DTC_SETTING_OK) &&
    (DTCSettingStatus != DEM_CONTROL_DTC_SETTING_N_OK) &&
    (DTCSettingStatus != DEM_CONTROL_DTC_WRONG_DTCGROUP) )
  {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    DCM_DET_REPORT_ERROR(DCM_SVCID_DTCSETTINGOFF, DCM_E_INTERFACE_RETURN_VALUE);

    /* DTC setting control not successful because DEM returns development report error */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
  }
  else if (DTCSettingStatus == DEM_CONTROL_DTC_SETTING_OK)
  {
    /* Set the Status of DTCDisable Status */
    curHsmInfo->dtcDisableStatus = TRUE;

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
    /* Dcm784 */
    (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING);
#endif
  }
  else if (DTCSettingStatus == DEM_CONTROL_DTC_SETTING_N_OK)
  {
    /* DTC setting control not successful */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
  }
  else
  {
    /* DTC setting control not successful because group of DTC was wrong */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  }

  DBG_DCM_DSPINTERNAL_DTCSETTINGTYPEOFF_SSVCH_EXIT(DCM_E_DONE,OpStatus,pMsgContext);
  return DCM_E_DONE;
}
#endif  /* #if ( DCM_0X85_0X02_SSVC_ENABLED == STD_ON) */

#endif /* #if(DCM_0X85_SVC_ENABLED == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X86 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ResponseOnEvent_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCH_ENTRY(OpStatus,pMsgContext);
  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      /*Copy the request to the buffer Dcm_RoeTempBuffer[]*/
      TS_MemCpy(Dcm_RoeTempBuffer, pMsgContext->reqData, (uint16)pMsgContext->reqDataLen);
      serviceProcessStatus = Dcm_DspInternal_ResponseOnEvent_SvcStart(OpStatus, pMsgContext);
      break;

    /* next call after a "response pending" was forced to be sent immediately  */
    case DCM_FORCE_RCRRP_OK:

    /* _SvcStart has returned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_ResponseOnEvent_SvcCont(OpStatus, pMsgContext);
      break;

    /* actions performed on sucessful sending of the response */
    case DCM_CONFIRMED_OK:
      /* do nothing */

    /* actions performed on failure in sending of the response */
    case DCM_CONFIRMED_NOK:
      /* do nothing */

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ResponseOnEvent_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* loop variable */
  uint8_least i;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get instIdx */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  /* get number of sub-services configured */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCSTART_ENTRY(OpStatus,pMsgContext);

  /* check if sub-function is supported */
  if (pMsgContext->reqDataLen == 0U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    /* mask persistence bit  */
    uint8 SubFunction = (uint8)(curHsmInfo->subServiceId & (uint8)(~DCM_ROE_PERSISTENCE_BIT));
    /* echo of bits 6 - 0 of the sub-function parameter of the request message */
    pMsgContext->resData[0] = (uint8)((curHsmInfo->subServiceId) & (uint8)(~0x80U));
    pMsgContext->resDataLen = 1U;

    for (i = 0U; i < numSubServ; i++)
    {
      /* Search for the index in subservices table for the requested subservice */
      if (curSsConfig[i].SubServiceId == SubFunction)
      {
        /* assign the data from msgcontext for service to that of sub-function.*/
        /* To avoid pMsgContext change when OpStatus is DCM_PENDING */
        /* decrement the reqData length as sub-function is removed */
        pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;
        pMsgContext->reqData = &pMsgContext->reqData[1];
        curHsmInfo->subServiceIdIdx = (uint8)i;
        serviceProcessStatus = Dcm_DspInternal_ResponseOnEvent_SvcCont(OpStatus, pMsgContext);
        break;
      }
    }
  }

  DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ResponseOnEvent_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get instIdx */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];
  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCCONT_ENTRY(OpStatus,pMsgContext);

  if (curSsConfig[curHsmInfo->subServiceIdIdx].IntSrvHandler != NULL_PTR)
  {
    /* Call internal sub-service handler*/
    serviceProcessStatus =
              curSsConfig[curHsmInfo->subServiceIdIdx].IntSrvHandler(OpStatus, pMsgContext);
  }
  else
  {
    /* Call External sub-service handler*/
    serviceProcessStatus =
              curSsConfig[curHsmInfo->subServiceIdIdx].ExtSrvHandler(OpStatus, pMsgContext);

    /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
    if (serviceProcessStatus == E_OK)
    {
      serviceProcessStatus = DCM_E_DONE;
    }
  }

  DBG_DCM_DSPINTERNAL_RESPONSEONEVENT_SVCCONT_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 == STD_ON)
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnDTCStatusChange_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_ROE_PERSISTENCE == STD_ON)
  VAR(NvM_RequestResultType, DCM_VAR ) RequestResult;
#endif

  DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SSVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_OnDTCStatusChange_SvcStart(pMsgContext);
      break;
    case DCM_PENDING:
#if (DCM_ROE_PERSISTENCE == STD_ON)
      if( NvM_GetErrorStatus(DCM_ROE_NVM_BLOCK_ID, &RequestResult) == E_OK )
      {
        if( RequestResult == NVM_REQ_OK )
        {
          /* Initial Positive response Event type already filled in response buffer */
          pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
          pMsgContext->resData[2] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX];
          pMsgContext->resData[3] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX];
          pMsgContext->resData[4] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND0_0x01_IDX];
          pMsgContext->resData[5] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND1_0x01_IDX];
          pMsgContext->resData[6] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND2_0x01_IDX];
          pMsgContext->resDataLen = 7U;
          serviceProcessStatus = DCM_E_DONE;
        }
        else if( RequestResult == NVM_REQ_PENDING )
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          /* In case there was an error writing to Nv */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        serviceProcessStatus = DCM_E_DONE;
      }
      if(serviceProcessStatus == DCM_E_DONE)
      {
        /* Lock the NVRAM block on operation failure/Success for further operations */
        NvM_SetBlockLockStatus(DCM_ROE_NVM_BLOCK_ID, TRUE);
      }
#endif
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 )*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 == STD_ON)
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnChangeOfDataIdentifier_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_ROE_PERSISTENCE == STD_ON)
  VAR(NvM_RequestResultType, DCM_VAR ) RequestResult;
#endif

  DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SSVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_OnChangeOfDataIdentifier_SvcStart(pMsgContext);
      break;

    case DCM_PENDING:
#if (DCM_ROE_PERSISTENCE == STD_ON)
      if( NvM_GetErrorStatus(DCM_ROE_NVM_BLOCK_ID, &RequestResult) == E_OK )
      {
        if( RequestResult == NVM_REQ_OK )
        {
          /* Initial Positive response Event type already filled in response buffer */
          /* !LINKSTO Dcm222,1 */
          pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
          pMsgContext->resData[2] =
                       Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX];
          pMsgContext->resData[3] =
                       Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD0_0x03_IDX];
          pMsgContext->resData[4] =
                       Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD1_0x03_IDX];
          pMsgContext->resData[5] =
                       Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX];
          pMsgContext->resData[6] =
                       Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND1_0x03_IDX];
          pMsgContext->resData[7] =
                       Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND2_0x03_IDX];
          pMsgContext->resDataLen = 8U;
          serviceProcessStatus = DCM_E_DONE;
        }
        else if( RequestResult == NVM_REQ_PENDING )
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          /* In case there was an error writing to Nv */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        serviceProcessStatus = DCM_E_DONE;
      }
      if(serviceProcessStatus == DCM_E_DONE)
      {
        /* Lock the NVRAM block on operation failure/Success for further operations */
        NvM_SetBlockLockStatus(DCM_ROE_NVM_BLOCK_ID, TRUE);
      }
#endif
      break;

     default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SSVCH_EXIT(serviceProcessStatus,
                                                          OpStatus,
                                                          pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 )*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StartROE_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_ROE_PERSISTENCE == STD_ON)
  VAR(NvM_RequestResultType, DCM_VAR ) RequestResult;
  uint8 eventWindowTime = Dcm_RoeTempBuffer[1];
#endif

  DBG_DCM_DSPINTERNAL_STARTROE_SSVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_StartROE_SvcStart(pMsgContext);
      break;
    case DCM_PENDING:
#if (DCM_ROE_PERSISTENCE == STD_ON)
      if( NvM_GetErrorStatus(DCM_ROE_NVM_BLOCK_ID, &RequestResult) == E_OK )
      {
        if( RequestResult == NVM_REQ_OK )
        {
          /* Initial Positive Response, Event type already filled in response buffer */
          pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
          pMsgContext->resData[2] = eventWindowTime; /* eventWindowTime */
          pMsgContext->resDataLen = 3U;
          serviceProcessStatus = DCM_E_DONE;
        }
        else if( RequestResult == NVM_REQ_PENDING )
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          /* In case there was an error writing to Nv */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        serviceProcessStatus = DCM_E_DONE;
      }
      if(serviceProcessStatus == DCM_E_DONE)
      {
        /* Lock the NVRAM block on operation failure/Success for further operations */
        NvM_SetBlockLockStatus(DCM_ROE_NVM_BLOCK_ID, TRUE);
      }
#else
      serviceProcessStatus = DCM_E_DONE;
#endif
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_STARTROE_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 )*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StopROE_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_ROE_PERSISTENCE == STD_ON)
  VAR(NvM_RequestResultType, DCM_VAR ) RequestResult;
#endif

  DBG_DCM_DSPINTERNAL_STOPROE_SSVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_StopROE_SvcStart(pMsgContext);
      break;
    case DCM_PENDING:
#if (DCM_ROE_PERSISTENCE == STD_ON)
      if( NvM_GetErrorStatus(DCM_ROE_NVM_BLOCK_ID, &RequestResult) == E_OK )
      {
        if( RequestResult == NVM_REQ_OK )
        {
          /* Initial Positive Response, Event type already filled in response buffer */
          pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
          pMsgContext->resData[2] = Dcm_RoeTempBuffer[1]; /* eventWindowTime */
          pMsgContext->resDataLen = 3U;
          serviceProcessStatus = DCM_E_DONE;
        }
        else if( RequestResult == NVM_REQ_PENDING )
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        serviceProcessStatus = DCM_E_DONE;
      }
      if(serviceProcessStatus == DCM_E_DONE)
      {
        /* Lock the NVRAM block on operation failure/Success for further operations */
        NvM_SetBlockLockStatus(DCM_ROE_NVM_BLOCK_ID, TRUE);
      }
#endif
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_STOPROE_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 )*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 == STD_ON)

FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearROE_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_ROE_PERSISTENCE == STD_ON)
  VAR(NvM_RequestResultType, DCM_VAR ) RequestResult;
#endif

  DBG_DCM_DSPINTERNAL_CLEARROE_SSVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_ClearROE_SvcStart(pMsgContext);
      break;
    case DCM_PENDING:
#if (DCM_ROE_PERSISTENCE == STD_ON)
      if( NvM_GetErrorStatus(DCM_ROE_NVM_BLOCK_ID, &RequestResult) == E_OK )
      {
        if( RequestResult == NVM_REQ_OK )
        {
          /* Initial Positive Response Event type already filled in response buffer */
          pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
          pMsgContext->resData[2] = Dcm_RoeTempBuffer[1]; /* eventWindowTime */
          pMsgContext->resDataLen = 3U;
          serviceProcessStatus = DCM_E_DONE;
        }
        else if( RequestResult == NVM_REQ_PENDING )
        {
          serviceProcessStatus = DCM_E_PENDING;
        }
        else
        {
          /* In case there was an error writing to Nv */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        serviceProcessStatus = DCM_E_DONE;
      }
      if(serviceProcessStatus == DCM_E_DONE)
      {
        /* Lock the NVRAM block on operation failure/Success for further operations */
        NvM_SetBlockLockStatus(DCM_ROE_NVM_BLOCK_ID, TRUE);
      }
#endif
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_CLEARROE_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 )*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04 == STD_ON)
 FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportActivatedEvents_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  uint8 resLength = 2U;
  uint8 events = 0U;

  DBG_DCM_DSPINTERNAL_REPORTACTIVATEDEVENTS_SSVCH_ENTRY(OpStatus,pMsgContext);
  TS_PARAM_UNUSED(OpStatus);

  /* Request Length Verification */
  if(pMsgContext->reqDataLen == 1U)
  {
    /* For onDTCStatusChange Event */
    if( Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED )
    {
      uint8 roeStoreBit = (uint8)Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX];

      /* Initial Positive response, Event type already filled in response buffer */
      /* For onDTCStatusChange Event */
      pMsgContext->resData[resLength] = (Dcm_MsgItemType)(DCM_ROE_ONDTC_STATUS_CHANGE |
                    (uint8)(roeStoreBit << 0x06U));
      resLength++;
      /* Remaining time for this event to be active */
      /* eventWindowTime */
      if (Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U)
      {
        pMsgContext->resData[resLength] =
        (Dcm_MsgItemType)(Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX]);
        resLength++;
      }
      else
      {
        pMsgContext->resData[resLength] = 0x02U;
        resLength++;
      }
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX];
      resLength++;
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND0_0x01_IDX];
      resLength++;
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND1_0x01_IDX];
      resLength++;
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND2_0x01_IDX];
      resLength++;

      events++;
    }
    /* For onChangeOfDataIdentifier Event */
    if( Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED )
    {
      uint8 roeStoreBit = (uint8)Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX];

      /* Initial Positive response, Event type already filled in response buffer */
      pMsgContext->resData[resLength] = (Dcm_MsgItemType)(DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER |
               (uint8)(roeStoreBit << 0x06));
      resLength++;

#if (DCM_ROE_PRECONF_SUPPORT == STD_ON)
      /* If event onChangeOfDataIdentifier (0x03) is preconfigured, simulate a persistent
         setup request to have taken place */
      pMsgContext->resData[resLength - 1] |= (boolean)(DCM_ROE_PERSISTENCE_BIT);
#endif /* #if (DCM_ROE_PRECONF_SUPPORT == STD_ON) */

      /* Remaining time for this event to be active */
      /* eventWindowTime */
      if (Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U)
      {
        pMsgContext->resData[resLength] =
        (Dcm_MsgItemType)(Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX]);
        resLength++;
      }
      else
      {
        pMsgContext->resData[resLength] = 0x02U;
        resLength++;
      }
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD0_0x03_IDX];
      resLength++;
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD1_0x03_IDX];
      resLength++;
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX];
      resLength++;
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND1_0x03_IDX];
      resLength++;
      pMsgContext->resData[resLength] =
                   Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND2_0x03_IDX];
      resLength++;
      events++;
    }
    pMsgContext->resData[1] = events; /* numberOfActivatedEvents */
    pMsgContext->resDataLen = resLength;
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    /* Request length invalid - send negative response! */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REPORTACTIVATEDEVENTS_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04 )*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnDTCStatusChange_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(curProtocolId);

#if (DCM_ROE_PERSISTENCE == STD_ON)
  Std_ReturnType RetVal;
#endif
  uint8 eventWindowTime = Dcm_RoeTempBuffer[1];

  DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SVCSTART_ENTRY(pMsgContext);

  /* Request Length Verification */
  if(pMsgContext->reqDataLen == 5U)
  {
    /* Deviation MISRA-2 */
    if ( (pMsgContext->reqData[2] == 0x19U) &&
      ((pMsgContext->reqData[3] == 2U) || (pMsgContext->reqData[3] == 4U) ||
      (pMsgContext->reqData[3] == 6U)) )
    {
      if( (eventWindowTime > 1U) && (eventWindowTime < 0x7FU) )
      {
        /* If tester tries to set event of same type without clearing the event */
        if( Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_CLEARED )
        {
          /* Copy subfunction to a global array */
          Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPE_IDX] = DCM_ROE_ONDTC_STATUS_CHANGE;
          /* Copy eventWindowTime to a global array */
          Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX] = eventWindowTime;
          /* Copy eventTypeRecord to a global array */
          Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX] =
                                          pMsgContext->reqData[1];
          /* Copy serviceToRespondToRecord to a global array */
          Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND0_0x01_IDX] =
                                          pMsgContext->reqData[2];
          Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND1_0x01_IDX] =
                                          pMsgContext->reqData[3];
          Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND2_0x01_IDX] =
                                          pMsgContext->reqData[4];

          /* init the number of identified events */
          Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x01_IDX]= 0x00U;

          /* Load ROE persistence bit into a global structure */
          if((curHsmInfo->subServiceId & DCM_ROE_PERSISTENCE_BIT) != 0U)
          {
            Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] = TRUE;
          }
          else
          {
            Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] = FALSE;
          }

          /* Dcm599: Set EventLogic Flag for OnDTCStatusChange to DCM_ROE_EVENT_SETUP */
          Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_SETUP;

#if (DCM_ROE_PERSISTENCE == STD_ON)
          if( Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE )
          {
            RetVal = Dcm_DspInternal_ROEWriteToNvM();
            if( RetVal == E_OK)
            {
              serviceProcessStatus = DCM_E_PENDING;
            }
            else
            {
              /* Failure in NvM_WriteBlock */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
              serviceProcessStatus = DCM_E_DONE;
            }
          }
          else
          {
            /* Initial Positive response Event type already filled in response buffer */
            pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
            pMsgContext->resData[2] =
                         Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX];
            pMsgContext->resData[3] =
                         Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX];
            pMsgContext->resData[4] =
                         Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND0_0x01_IDX];
            pMsgContext->resData[5] =
                         Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND1_0x01_IDX];
            pMsgContext->resData[6] =
                         Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND2_0x01_IDX];
            pMsgContext->resDataLen = 7U;
            serviceProcessStatus = DCM_E_DONE;
          }
#else
          /* Initial Positive response Event type already filled in response buffer */
          pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
          pMsgContext->resData[2] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX];
          pMsgContext->resData[3] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPERECORD0_0x01_IDX];
          pMsgContext->resData[4] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND0_0x01_IDX];
          pMsgContext->resData[5] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND1_0x01_IDX];
          pMsgContext->resData[6] =
                       Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SERVICETORESPOND2_0x01_IDX];
          pMsgContext->resDataLen = 7U;
          serviceProcessStatus = DCM_E_DONE;
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
        }
        else
        {
          /* without ClearEvent request, SetEvent Logic requested */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /* Invalid eventWindowTime */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
      }
    }
    else
    {
      /* For 0x19 - subfunctions 0x02, 0x04, 0x06 are only supported currently */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_ONDTCSTATUSCHANGE_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 */

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnChangeOfDataIdentifier_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_ROE_PERSISTENCE == STD_ON)
  Std_ReturnType RetVal;
#endif

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
    /* Get current protocol id */
  uint8 curProtocolId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* get information */
  CONSTP2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo
    = &DCM_HSM_INFO(curProtocolId);
  /* To get DID signals configuration */
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg;
  /* To get DID signals data configuration */
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg;
  /* To store number of signals in DID */
  uint16 numSignals;
  /* To store length of the signals in DID */
  uint16 DidSignalsDataLength;

  uint16 reqDid;
  uint8 eventWindowTime = pMsgContext->reqData[0];
  uint16_least i;

  DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SVCSTART_ENTRY(pMsgContext);

  /* Request Length Verification */
  if( pMsgContext->reqDataLen == 6U )
  {
    if( pMsgContext->reqData[3] == 0x22U )
    {
      if( (eventWindowTime > 1U) && (eventWindowTime < 0x7FU) )
      {
        /* validate if same DID values are used in eventTypeRecord and Service parameters */
        if( (pMsgContext->reqData[1] == pMsgContext->reqData[4]) &&
          (pMsgContext->reqData[2] == pMsgContext->reqData[5]) )
        {
          reqDid = (uint16)((uint16)((uint16)pMsgContext->reqData[1] << 8U) +
            ((uint16)pMsgContext->reqData[2]));

          /* Check if Did is Configured*/
          for (i = 0U; i < DCM_NUM_DID ; ++i)
          {
            if (reqDid == Dcm_DidTable[i].Did)
            {
              break;
            }
          }
          /* validate DID received in the request */
          if(i < DCM_NUM_DID)
          {
            /* Store Did Index for future use */
            Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX] = (uint8)i;
            Dcm_DspInternal_GetCommonDidSignalMask((uint8)i);
            /* Get the number of signals configured for this DID */
            numSignals = Dcm_DidTable[i].NumSignals;
            /* Store the Signal configuration of the last signal configured for this DID */
            SignalCfg = &(Dcm_DidTable[i].Signals[numSignals - 1]);
            /* Get the Data configuration of the last signal configured */
            dataCfg = &Dcm_DidDataTable[SignalCfg->DspDataIndex];
            /* Store the sum of signals of DID by adding last signal position and data length */
            DidSignalsDataLength = DCM_GET_BYTES(SignalCfg->DataPos + dataCfg->DataLength) ;
            /* Validation of DID signal length */
            if(DidSignalsDataLength > DCM_ROE_DID_BUF_SIZE)
            {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
              DCM_DET_REPORT_ERROR(DCM_SVCID_ROEONCHANGEOFDID, DCM_E_ROE_BUFFER_CONFIG_FAIL);
#endif /* DCM_DEV_ERROR_DETECT */
              /* Did Signals length is greater than the Roebuffer configured,
                 causing buffer overflow */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
              serviceProcessStatus = DCM_E_DONE;
            }
            else
            {
#if(DCM_ROE_PRECONF_ONCHANGEOFDID_SUPPORT == STD_ON)
              if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] ==
                  DCM_ROE_EVENT_SETUP) ||
                  (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] ==
                  DCM_ROE_EVENT_CLEARED) )
#else
              /* If tester tries to set event of same type without clearing the event */
              if( Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] ==
                  DCM_ROE_EVENT_CLEARED )
#endif
              {
                /* Copy eventTypeRecord to a global array */
                Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPE_IDX] =
                            DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER;
                Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] =
                            eventWindowTime;
                Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD0_0x03_IDX] =
                            pMsgContext->reqData[1];
                Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD1_0x03_IDX] =
                            pMsgContext->reqData[2];
                Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX] =
                            pMsgContext->reqData[3];
                Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND1_0x03_IDX] =
                            pMsgContext->reqData[4];
                Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND2_0x03_IDX] =
                            pMsgContext->reqData[5];

                /* Dcm599: Set EventLogic Flag for OnChangeOfDataIdentifier to
                   DCM_ROE_EVENT_SETUP */
                Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_SETUP;

                /* init the number of identified events */
                Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x03_IDX]= 0x00U;

                /* Load ROE persistence bit into a global structure */
                if((curHsmInfo->subServiceId & DCM_ROE_PERSISTENCE_BIT) != 0U)
                {
                  Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] = TRUE;
                }
                else
                {
                  Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] = FALSE;
                }

                /* Write into NvM if
                   Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE */
#if (DCM_ROE_PERSISTENCE == STD_ON)
                if( Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE )
                {
                  RetVal = Dcm_DspInternal_ROEWriteToNvM();
                  if( RetVal == E_OK)
                  {
                    serviceProcessStatus = DCM_E_PENDING;
                  }
                  else
                  {
                    /* Failure in NvM_WriteBlock */
                    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
                    serviceProcessStatus = DCM_E_DONE;
                  }
                }
                else
                {
                  /* Initial Positive response Event type already filled in response buffer */
                  pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
                  pMsgContext->resData[2] =
                               Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX];
                  pMsgContext->resData[3] =
                               Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD0_0x03_IDX];
                  pMsgContext->resData[4] =
                               Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD1_0x03_IDX];
                  pMsgContext->resData[5] =
                               Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX];
                  pMsgContext->resData[6] =
                               Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND1_0x03_IDX];
                  pMsgContext->resData[7] =
                               Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND2_0x03_IDX];
                  pMsgContext->resDataLen = 8U;
                  serviceProcessStatus = DCM_E_DONE;
                }
#else
                /* Initial Positive response Event type already filled in response buffer */
                pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
                pMsgContext->resData[2] =
                             Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX];
                pMsgContext->resData[3] =
                             Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD0_0x03_IDX];
                pMsgContext->resData[4] =
                             Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPERECORD1_0x03_IDX];
                pMsgContext->resData[5] =
                             Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND0_0x03_IDX];
                pMsgContext->resData[6] =
                             Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND1_0x03_IDX];
                pMsgContext->resData[7] =
                             Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SERVICETORESPOND2_0x03_IDX];
                pMsgContext->resDataLen = 8U;
                serviceProcessStatus = DCM_E_DONE;
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
              }
              else
              {
                /* without ClearEvent request, SetEvent Logic requested */
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
                serviceProcessStatus = DCM_E_DONE;
              }
            }
          }
          else
          {
            /* Invalid DID */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
        else
        {
          /* Invalid request */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
      }
      else
      {
        /* Invalid eventWindowTime */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
      }
    }
    else
    {
      /* Otherthan 0x22 service is requested */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_ONCHANGEOFDATAIDENTIFIER_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 */

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StartROE_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* To fetch roeTransmissionType */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  P2CONST(Dcm_DidServicesType, TYPEDEF, DCM_CONST) didCfg =
    &Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]];
  Std_ReturnType RetVal;
  uint8 eventWindowTime = Dcm_RoeTempBuffer[1];

  DBG_DCM_DSPINTERNAL_STARTROE_SVCSTART_ENTRY(pMsgContext);

  /* Request Length Verification */
  if ( pMsgContext->reqDataLen == 1U )
  {
    /* Deviation MISRA-2 */
    /* Restart of cleared events, start stopped events which are already setup */
    if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_SETUP) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_SETUP) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED) )
    {
      /* Initial Positive Response, Event type already filled in response buffer */
      pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
      pMsgContext->resData[2] = eventWindowTime; /* eventWindowTime */
      pMsgContext->resDataLen = 3U;

      /* !LINKSTO Dcm.StartResponseOnEvent.StoreRxPduId,1 */
      if(DCM_HSM_CONFIG(instIdx).roeTransmissionType == DCM_ROE_TYPE1)
      {
        Dcm_RoeData.DcmRxPduId = pMsgContext->dcmRxPduId;
      }

      /* Dcm599: OnDTCStatusChange Event */
      if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_SETUP) ||
          (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED) )
      {
        Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_STARTED;
        /* if eventWindowTime is set to 02, then the response time is infinite.
         * EventWindow timer needs to be started only if eventWindowTime is not 2
         */
        if(Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U)
        {
          Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] =
            (((uint32)Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTWINDOWTIME_IDX]) * 1000U) /
            DCM_TASK_TIME;
        }
        else
        {
          Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] = 0U;
        }
        serviceProcessStatus = DCM_E_DONE;
#if (DCM_ROE_PERSISTENCE == STD_ON)
        if(((Dcm_RoeTempBuffer[0]) & DCM_ROE_PERSISTENCE_BIT) != 0U)
        {
          /* if Persistence bit of StartRoe is set to '1' (1) atleast one persistent setup event is
             present */
          if( (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE) ||
            (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE) )
          {
            RetVal = Dcm_DspInternal_ROEWriteToNvM();
            if( RetVal == E_OK )
            {
              serviceProcessStatus = DCM_E_PENDING;
            }
            else
            {
              /* Failure in NvM_WriteBlock */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
              serviceProcessStatus = DCM_E_DONE;
            }
          }
          else
          {
            /* StartRoe (persistent) is requested without atleast one persistent setup event */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
      }

      if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_SETUP) ||
          (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED) )
      {
        /* Verify presence of DcmDspDidExtRoe for requested DID */
        if(didCfg->ExtRoeSupport == TRUE)
        {
          /* Dcm524: Invoke xxx_ActivateEvent with DCM_ROE_ACTIVE. */
          RetVal = didCfg->RoeActivateFnc(didCfg->RoeEventId, DCM_ROE_ACTIVE);

          if(RetVal == E_OK)
          {
            Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_STARTED;
            Dcm_RoePollAsyncState = ROE_POLLING_IDLE;

            /* if eventWindowTime is set to 02, then the response time is infinite.
             * EventWindow timer needs to be started only if eventWindowTime is not 2
             */
            if(Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U)
            {
              Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] =
                ((uint32)(Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX]) * 1000U)
                / DCM_TASK_TIME;
            }
            else
            {
              Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] = 0U;
            }
            serviceProcessStatus = DCM_E_DONE;
#if (DCM_ROE_PERSISTENCE == STD_ON)
            if(((Dcm_RoeTempBuffer[0]) & DCM_ROE_PERSISTENCE_BIT) != 0U)
            {
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
            /* if Persistence bit of StartRoe is set to '1' and atleast one persistent setup event
              is present*/
              if( (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE) ||
                  (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE) )
#endif
              {
                RetVal = Dcm_DspInternal_ROEWriteToNvM();
                if( RetVal == E_OK)
                {
                  serviceProcessStatus = DCM_E_PENDING;
                }
                else
                {
                  /* Failure in NvM_WriteBlock */
                  Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
                }
              }
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
              else
              {
                /* StartRoe (persistent) is requested without atleast one persistent setup event */
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
              }
#endif
            }
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
          }
          else
          {
            /* Dcm679 */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;

#if (DCM_DEV_ERROR_DETECT == STD_ON)
            DCM_DET_REPORT_ERROR(DCM_SVCID_ACTIVATEEVENT, DCM_E_ROE_ACTIVATE_EVENT_FAIL);
#endif
          }
        }
        else
        {
          Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_STARTED;
          Dcm_RoePollAsyncState = ROE_POLLING_IDLE;

          /* Start the EventWindow timer. If eventWindowTime is 02, EventWindow timer need not
          * start EventWindow timer as the response time is infinite
          */
          if(Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX] != 2U)
          {
            Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] =
              ((uint32)(Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTWINDOWTIME_IDX]) * 1000U)
              / DCM_TASK_TIME;
          }
          else
          {
            Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] = 0U;
          }
          serviceProcessStatus = DCM_E_DONE;
#if (DCM_ROE_PERSISTENCE == STD_ON)
          if(((Dcm_RoeTempBuffer[0]) & DCM_ROE_PERSISTENCE_BIT) != 0U)
          {
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
            /* if Persistence bit of StartRoe is set to '1' and atleast one persistent setup event
               is present */
            if( (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE) ||
                (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE))
#endif
            {
              RetVal = Dcm_DspInternal_ROEWriteToNvM();
              if( RetVal == E_OK)
              {
                serviceProcessStatus = DCM_E_PENDING;
              }
              else
              {
                /* Failure in NvM_WriteBlock */
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
                serviceProcessStatus = DCM_E_DONE;
              }
            }
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
            else
            {
              /* StartRoe (persistent) is requested without atleast one persistent setup event */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
              serviceProcessStatus = DCM_E_DONE;
            }
#endif
          }
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
        }
      }
    }
    else
    {
      /* without EventSetup request, EventStarted */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    /* Request length invalid - send negative response! */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_STARTROE_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearROE_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_ROE_PERSISTENCE == STD_ON)
  Std_ReturnType RetVal;
#endif

  uint8 eventWindowTime = pMsgContext->reqData[0];

  DBG_DCM_DSPINTERNAL_CLEARROE_SVCSTART_ENTRY(pMsgContext);

  /* Request Length Verification */
  if ( pMsgContext->reqDataLen == 1U )
  {
    /* Deviation MISRA-2 */
    if ( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_SETUP) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED) ||
      (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_SETUP) )
    {
      if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_STARTED) ||
          (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_EVENT_SETUP) )
      {
        /* Clear event logic for the onDTCStatusChange event that has been set up */
        Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_CLEARED;
        /* Stop the ROE event window time */
        Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] = 0U;
        serviceProcessStatus = DCM_E_DONE;
      }
      else
      {
        /* Clear event logic for the events that has been set up for onChangeOfDataIdentifier */
        Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_CLEARED;
        /* Stop the ROE event window time */
        Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] = 0U;
        Dcm_RoePollAsyncState = ROE_POLLING_IDLE;
        serviceProcessStatus = DCM_E_DONE;
      }
#if (DCM_ROE_PERSISTENCE == STD_ON)
      if(((Dcm_RoeTempBuffer[0]) & DCM_ROE_PERSISTENCE_BIT) != 0U)
      {
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
        /* if Persistence bit of ClearRoe is set to '1' and atleast one persistent setup event
           is present or StartRoe is received with persistent bit set */
        if( (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE) ||
            (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE))
#endif
        {
          RetVal = Dcm_DspInternal_ROEWriteToNvM();
          if( RetVal == E_OK )
          {
            serviceProcessStatus = DCM_E_PENDING;
          }
          else
          {
            /* Failure in NvM_WriteBlock */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
          }
        }
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
        else
        {
          /* No persistent setup event request or StartRoe is received with persistent bit set is
             received previously */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        }
#endif
      }
      else
      {
        /* Initial Positive Response Event type already filled in response buffer */
        pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
        pMsgContext->resData[2] = eventWindowTime; /* eventWindowTime */
        pMsgContext->resDataLen = 3U;
      }
#else
        /* Initial Positive Response Event type already filled in response buffer */
        pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
        pMsgContext->resData[2] = eventWindowTime; /* eventWindowTime */
        pMsgContext->resDataLen = 3U;
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
    }
    else
    {
      /* Event Logic is not setup */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    /* Request length invalid - send negative response! */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_CLEARROE_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StopROE_SvcStart(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  P2CONST(Dcm_DidServicesType, TYPEDEF, DCM_CONST) didCfg =
    &Dcm_DidTable[Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_REQUESTEDDID_0x03_IDX]];
  Std_ReturnType RetVal;
#if (DCM_ROE_PERSISTENCE == STD_ON)
  Std_ReturnType RetValPeristence;
#endif
  uint8 eventWindowTime = pMsgContext->reqData[0];

  DBG_DCM_DSPINTERNAL_STOPROE_SVCSTART_ENTRY(pMsgContext);

  /* Request Length Verification */
  if ( pMsgContext->reqDataLen == 1U )
  {
    /* Deviation MISRA-2 */
    /* Transition from Start or Stop (Repeated stop request) */
    if( ((Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX]== DCM_ROE_EVENT_SETUP) ||
        (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX]== DCM_ROE_EVENT_SETUP)) ||
        ((Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX]== DCM_ROE_EVENT_STARTED) ||
        (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX]== DCM_ROE_EVENT_STARTED)) )
    {
      /* Initial Positive Response, Event type already filled in response buffer */
      pMsgContext->resData[1] = 0U; /* numberOfIdentifiedEvents */
      pMsgContext->resData[2] = eventWindowTime; /* eventWindowTime */
      pMsgContext->resDataLen = 3U;

      /* Dcm600 */
      /* if ROE event of onDTCStatusChange is not active */
      if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX]== DCM_ROE_EVENT_STARTED) ||
          (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX]== DCM_ROE_EVENT_SETUP) )
      {
        Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x01_IDX] = DCM_ROE_EVENT_SETUP;
        /* Stop the ROE event window time */
        Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x01_IDX] = 0U;
#if (DCM_ROE_PERSISTENCE == STD_ON)
        if(((Dcm_RoeTempBuffer[0]) & DCM_ROE_PERSISTENCE_BIT) != 0U)
        {
          /* At least one persistent or preconfigured ROE event must be present */
          if( (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE) ||
              (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE) )
          {
            RetValPeristence = Dcm_DspInternal_ROEWriteToNvM();
            if( RetValPeristence == E_OK)
            {
              serviceProcessStatus = DCM_E_PENDING;
            }
            else
            {
              /* Failure in NvM_WriteBlock */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
              serviceProcessStatus = DCM_E_DONE;
            }
          }
          else
          {
            /* StartRoe with persistence bit set is not received previously */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
#else
      serviceProcessStatus = DCM_E_DONE;
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
      }
      else
      {
        serviceProcessStatus = DCM_E_DONE;
      }

      /* Verify presence of DcmDspDidExtRoe for requested DID */
      if( (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_STARTED) ||
          (Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] == DCM_ROE_EVENT_SETUP))
      {
        if(didCfg->ExtRoeSupport == TRUE)
        {
          /* Dcm526: Invoke xxx_ActivateEvent with DCM_ROE_UNACTIVE. */
          RetVal = didCfg->RoeActivateFnc(didCfg->RoeEventId, DCM_ROE_UNACTIVE);

          if(RetVal == E_OK)
          {
            Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_SETUP;
            Dcm_RoePollAsyncState = ROE_POLLING_IDLE;

            /* Stop the ROE event window time */
            Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] = 0U;
#if (DCM_ROE_PERSISTENCE == STD_ON)
            if(((Dcm_RoeTempBuffer[0]) & DCM_ROE_PERSISTENCE_BIT) != 0U)
            {
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
              /* At least one persistent or preconfigured ROE event must be present */
              if( (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE) ||
                  (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE))
#endif
              {
                RetValPeristence = Dcm_DspInternal_ROEWriteToNvM();
                if( RetValPeristence == E_OK)
                {
                  serviceProcessStatus = DCM_E_PENDING;
                }
                else
                {
                  /* Failure in NvM_WriteBlock */
                  Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
                }
              }
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
              else
              {
                /* StartRoe with persistence bit set is not received previously */
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
              }
#endif
            }
#else
        serviceProcessStatus = DCM_E_DONE;
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
          }
          else
          {
            /* Dcm679 */
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;

#if (DCM_DEV_ERROR_DETECT == STD_ON)
            DCM_DET_REPORT_ERROR(DCM_SVCID_ACTIVATEEVENT, DCM_E_ROE_ACTIVATE_EVENT_FAIL);
#endif
          }
        }
        else
        {
          Dcm_RoeData.Dcm_RoeEventLogic[DCM_ROE_SUBFUNCTION_0x03_IDX] = DCM_ROE_EVENT_SETUP;
          Dcm_RoePollAsyncState = ROE_POLLING_IDLE;

          /* Stop the ROE event window time */
          Dcm_RoeEventWindowTime[DCM_ROE_SUBFUNCTION_0x03_IDX] = 0U;
#if (DCM_ROE_PERSISTENCE == STD_ON)
          if(((Dcm_RoeTempBuffer[0]) & DCM_ROE_PERSISTENCE_BIT) != 0U)
          {
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
           /* At least one persistent or preconfigured ROE event must be present */
            if( (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x01_IDX] == TRUE) ||
                (Dcm_RoeData.RoeStoreBit[DCM_ROE_SUBFUNCTION_0x03_IDX] == TRUE) )
#endif
            {
              RetValPeristence = Dcm_DspInternal_ROEWriteToNvM();
              if( RetValPeristence == E_OK)
              {
                serviceProcessStatus = DCM_E_PENDING;
              }
              else
              {
                /* Failure in NvM_WriteBlock */
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
              }
            }
#if (DCM_ROE_PRECONF_SUPPORT == STD_OFF)
            else
            {
              /* StartRoe with persistence bit set is not received previously */
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
            }
#endif
          }
#else
        serviceProcessStatus = DCM_E_DONE;
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */
        }
      }
      else
      {
        serviceProcessStatus = DCM_E_DONE;
      }
    }
    else
    {
      /* startResponseOnEvent is not received */
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    /* Request length invalid - send negative response! */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_STOPROE_SVCSTART_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /*(#if DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00)*/

#endif /* (DCM_DSP_USE_SERVICE_0X86 == STD_ON) */

/*==================[internal function definitions]==============================================*/

/* if Paged buffer handling enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_UpdatePage(
    Dcm_MsgType PagedBufPtr,
    PduLengthType PageLen)
{
  DBG_DCM_DSPINTERNAL_UPDATEPAGE_ENTRY(PagedBufPtr,PageLen);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSD_UPDATEPAGE, DCM_E_UNINIT);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
  /* get HSM instance which corresponds to the Tx Pdu Id used by current protocol
   *
   * This is ugly but from the function argument we cannot derive the current HSM instance. */
    uint8 instIdx = Dcm_CurProtocolId;
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    /* get configuration for current service table */
    CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
      = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

    /* get the context information current instance */
    P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

    /* Update the response data buffer with PagedBufPtr */
    DCM_HSM_INFO(instIdx).msgContext.resData = PagedBufPtr;

    /* Update the response data buffer size */
    DCM_HSM_INFO(instIdx).msgContext.resMaxDataLen = PageLen;
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
    {
      /* if handling is asynchronous, signal the asynchronous service dispatcher that the next
         invocation of the service handler function should be done with an OpStatus of
         DCM_UPDATE_PAGE */
        /* ENTER critical section */
      SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

      /* curHsmInfo->asyncServicePagingOperation = DCM_UPDATE_PAGE_READY; */
      curHsmInfo->asyncServiceOpState = DCM_UPDATE_PAGE;

      /* LEAVE critical section */
      SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
    }
    else
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
    {
      Dcm_DspInternal_SvcFunc(instIdx, DCM_UPDATE_PAGE);
    }
  }

  DBG_DCM_DSPINTERNAL_UPDATEPAGE_EXIT(PagedBufPtr,PageLen);
}

FUNC(void, DCM_APPL_CODE) Dcm_DspInternal_CancelPagedBufferProcessing(void)
{
  /* get HSM instance which corresponds to the Tx Pdu Id used by current protocol
   *
   * This is ugly but there is no function argument to derive the current HSM instance. */
  uint8 instIdx = Dcm_CurProtocolId;

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
      = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

  DBG_DCM_DSPINTERNAL_CANCELPAGEDBUFFERPROCESSING_ENTRY();

  /* Signal to all service handlers that the cancellation is a paged-buffering transmission
     cancellation */
  Dcm_CancelPagedProcessing = TRUE;

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
  {
    /* if handling is asynchronous, signal the asynchronous service dispatcher that the next
     * invocation of the service handler function should be done with an OpStatus of
     * DCM_CANCEL
     */

    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    curHsmInfo->asyncServiceOpState = DCM_CANCEL;

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }
  else
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
  {
    /* only for internal services */
    Dcm_DspInternal_SvcFunc(instIdx, DCM_CANCEL);
  }

  DBG_DCM_DSPINTERNAL_CANCELPAGEDBUFFERPROCESSING_EXIT();
}
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

FUNC(void, DCM_APPL_CODE) Dcm_DspInternal_CancelProcessing(void)
{
  uint8 instIdx = Dcm_CurProtocolId;

  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext = &curHsmInfo->msgContext;

  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  DBG_DCM_DSPINTERNAL_CANCELPROCESSING_ENTRY();

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
  if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
  {
    /* if handling is asynchronous, signal the asynchronous service dispatcher that the next
     * invocation of the service handler function should be done with an OpStatus of DCM_CANCEL
     */

    /* ENTER critical section */
    SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

    /* If the service handler is not longer active just emit PROC_DONE to make the HSM move out
     * of the CancelProcessing state to the OutOfService state.
     */
    if (curHsmInfo->asyncServiceOpState == DCM_PENDING)
    {
      curHsmInfo->asyncServiceOpState = DCM_CANCEL;
    }
    else
    {
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_CUR_INST_ID(instIdx),
                                    DCM_HSM_DCM_EV_PROC_DONE);
    }

    /* LEAVE critical section */
    SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  }
  else
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
  {
    /* if internal service, call the service handler function */
    if (DCM_HSM_INFO(instIdx).dspService)
    {
      Dcm_DspInternal_SvcFunc(instIdx, DCM_CANCEL);
    }
    else
    {
      /* Inform external service handler that Dcm has cancelled processing of the service */
      (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).ExtSrvHandler(DCM_CANCEL,
                                                                           pMsgContext);
    }
  }

  DBG_DCM_DSPINTERNAL_CANCELPROCESSING_EXIT();
}

FUNC(void, DCM_CODE) Dcm_DspInternal_DcmConfirmation(
  Dcm_IdContextType          idContext,
  PduIdType                  dcmRxPduId,
  Dcm_ConfirmationStatusType status)
{
  DBG_DCM_DSPINTERNAL_DCMCONFIRMATION_ENTRY(idContext,dcmRxPduId,status);

#if (DCM_DEV_ERROR_DETECT == STD_ON)
  if (Dcm_Initialized != TRUE)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSP_DCMCONFIRMATION, DCM_E_UNINIT);
  }
  else if (dcmRxPduId >= DCM_NUM_RX_PDU_ID)
  {
    DCM_DET_REPORT_ERROR(DCM_SERVID_DSP_DCMCONFIRMATION, DCM_E_PARAM);
  }
  else
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */
  {
    uint8_least i;
    uint8 Sid;
    uint8 ReqType;
    uint16 SourceAddress;
    Dcm_SesCtrlType newSesCtrl = 0U;
    P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig;

    /* get HSM instance which corresponds to the RxPdu id. */
    uint8 instIdx = Dcm_RxPduIdConfig[dcmRxPduId].protocolId;

  /* get the context information current instance */
    P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
    /* get configuration for current service table */
    CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */

    Sid = curHsmInfo->serviceId;
    ReqType = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].addrType;
    SourceAddress = Dcm_RxPduIdConfig[curHsmInfo->rxPduId].TesterSourceAddr;

#if ((DCM_INCLUDE_RTE == STD_ON) && \
    ((DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED == STD_ON) || \
    (DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED == STD_ON)) )
    {
#if (DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED == STD_ON)
    for (i = 0U; i < DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE; ++i)
      {
        (void)(Dcm_RteManufacturerNotificationTable[i].Confirmation
                                        (Sid, ReqType, SourceAddress, status));
      }
#endif
#if (DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED == STD_ON)
    for (i = 0U; i < DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE; ++i)
      {
        (void)(Dcm_RteSupplierNotificationTable[i].Confirmation
                                        (Sid, ReqType, SourceAddress, status));
      }
#endif
    }
#else
    Rte_DcmConfirmation(Sid, ReqType, SourceAddress, status);
#endif /*(DCM_INCLUDE_RTE == STD_ON) && \
         ((DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED == STD_ON) || \
         (DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED == STD_ON)) */

    if (Dcm_BLInitStatus == DCM_TX_CONF_PENDING)
    {
      /* Response successfully transmitted; set the active session */
      newSesCtrl = ProgConditions.SubFncId;

      /* Get SesTabConfig info */
      sesTabConfig = &DCM_SES_TAB_CONFIG(Dcm_CurProtocolId);

      /* Get active session index */
      for (i = 0U; i < sesTabConfig->NumEntries; ++i)
      {
        if ((sesTabConfig->SessionEntries[i]).SesCtrl == newSesCtrl)
        {
          uint16_least j; /* loop variable */

          /* Get the 'RxPduId' corresponding to the tester 'SourceAddress' */
          for (j = 0U; j < DCM_NUM_RX_PDU_ID; j++)
          {
            if (Dcm_RxPduIdConfig[j].TesterSourceAddr == ProgConditions.TesterSourceAddr)
            {
              break;
            }
          }

          /* set new active session */
          DCM_HSM_INFO(Dcm_RxPduIdConfig[(PduIdType)j].protocolId).sesTabIdx = (uint8)i;
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
          /* inform SchM about session change */
          /* !LINKSTO Dcm.EB.DiagnosticSessionControl.SchM_Switch,1
             Dcm311 */
          (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(
            sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].RteSesMode);
#endif
        }
      }

      /* Emit PROC_DONE after the confirmation */
      (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROC_DONE);

      DBG_DCM_BLINITSTATUS((Dcm_BLInitStatus),(DCM_RES_TX_CONF_OK));
      Dcm_BLInitStatus = DCM_RES_TX_CONF_OK;
    }
    else
    {
      /* Provide confirmation for internal service */
      if (DCM_HSM_INFO(instIdx).dspService)
      {
        Dcm_OpStatusType OpStatus;
        if((status == DCM_RES_POS_OK) || (status == DCM_RES_NEG_OK))
        {
          OpStatus = DCM_CONFIRMED_OK;
        }
        else
        {
          OpStatus = DCM_CONFIRMED_NOK;
        }
        /* service handler should not be invoked in case of failures during service validation */
        if(DCM_HSM_INFO(instIdx).requestValidationStatus == TRUE)
        {
          /* No failures during service request validation */
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
          if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
          {
            /* if handling is asynchronous, signal to the asynchronous service dispatcher the new
             * OpStatus
             */

            /* ENTER critical section */
            SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

            curHsmInfo->asyncServiceOpState = OpStatus;

            /* LEAVE critical section */
            SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
          }
          else
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
          {
            Dcm_DspInternal_SvcFunc(instIdx, OpStatus);
          }
        }
        else
        {
          /* Emit PROC_DONE event here as there is failure in validation  */
          (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROC_DONE);
        }
      }
#if(DCM_EXTSVC_ENABLED == STD_ON)
      else
      {
        /* For user configured services, Confirmation callout will be invoked */
        Dcm_Confirmation(idContext, dcmRxPduId, status);

        /* Set Session state to requested session after successful transmission of Confirmation */
        if( (idContext == DCM_SID_SESSION_CONTROL) && (status == DCM_RES_POS_OK) )
        {
          /* set session state of current HSM to requested session */
          Dcm_DspInternal_SetSessionState(instIdx);
#if (DCM_DSP_USE_SERVICE_0X2F == STD_ON)
          if( (curHsmInfo->newSesCtrl == DCM_DEFAULT_SESSION) &&
              (Dcm_ReturnControlToEcuContext.returnCtrlToECUStatus != DCM_RET_CTRL_PENDING)
            )
          {
              /* Dcm628: On a session transition to default session (from non-default session), the
                 DCM shall stop all the control in progress */
              /* Because the state of the DIDs is undefined until control has been returned to ECU
                 for all. So it is not required to invoke returnControlToECU interface for
                 signals */
              /* Will be done via Dcm_MainFunction */
              Dcm_DspInternal_ReturnControlToEcuforallSignals();
          }
#endif
        }

        /* For external service handlers, PROC_DONE is emitted after the confirmation */
#if (DCM_ASYNC_SERVICE_HANDLER == STD_ON)
        if((curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).AsyncServiceExecution == TRUE)
        {
          DCM_HSM_INFO(instIdx).asyncServiceOpState = DCM_ASYNC_PROCESSING_DONE;
        }
        else
#endif /* #if(DCM_ASYNC_SERVICE_HANDLER == STD_ON) */
        {
          (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, instIdx, DCM_HSM_DCM_EV_PROC_DONE);
        }
      }
#else
    TS_PARAM_UNUSED(idContext);
#endif /* #if(DCM_EXTSVC_ENABLED == STD_ON) */
    }

    /* Reload ROE Transmission cycle after successful transmission */
#if(DCM_ROE_ENABLED == STD_ON)
    {
      /* get pointer to current message context */
      CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) pMsgContext = &curHsmInfo->msgContext;

      /* start the intermessage time if an ROE message was transmitted */
      if ((pMsgContext->msgAddInfo.messageType == DCM_ROE) ||
          (pMsgContext->msgAddInfo.messageType == DCM_ROE_FINAL))
      {
        Dcm_RoeInterMsgTime = DCM_ROE_INTER_MSG_TIME;
      }
    }
#endif
  }

  DBG_DCM_DSPINTERNAL_DCMCONFIRMATION_EXIT(idContext,dcmRxPduId,status);
}

#if(DCM_DSP_USE_SERVICE_0X19 == STD_ON)

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)

/* Function is used by Dcm_DspInternal_ReportDtcSnapshotRecordByDtcNumber_SSvcH() to simplify DEM
 * readout */
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetSnapShotRecord(
  uint32 DTC,
  uint8 SnapShotRecordNumber,
  PduLengthType sizeRemainingBuffer,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) resDataLengthPtr
)
{
  Dcm_StatusType resultGetSSRecord = DCM_E_NOT_OK;

  DBG_DCM_DSPINTERNAL_DEMGETSNAPSHOTRECORD_ENTRY(DTC,SnapShotRecordNumber,sizeRemainingBuffer,
                                                 pMsgContext,resDataLengthPtr);

  /* if buffer is not full */
  if (sizeRemainingBuffer > 0U)
  {
    Dem_ReturnGetFreezeFrameDataByDTCType resultGetFreezeFrameData;
    uint16 sizeRemainingBuffer16;

    /* calculate the buffer size in 16bits */
    if (sizeRemainingBuffer < 0xFFFFU)
    {
      sizeRemainingBuffer16 = (uint16) sizeRemainingBuffer;
    }
    else
    {
      sizeRemainingBuffer16 = 0xFFFFU;
    }

    /* Get the freeze frame data */
    resultGetFreezeFrameData = Dem_GetFreezeFrameDataByDTC(
      (uint32)DTC,
      DEM_DTC_ORIGIN_PRIMARY_MEMORY,
      (uint8)SnapShotRecordNumber,
      &pMsgContext->resData[*resDataLengthPtr], /* Destination buffer */
      &sizeRemainingBuffer16);

    if ( resultGetFreezeFrameData == DEM_GET_FFDATABYDTC_OK )
    {
      /* update the response length */
      (*resDataLengthPtr) += (PduLengthType)sizeRemainingBuffer16;
      resultGetSSRecord = DCM_E_OK;
    }
    /* if buffer is not enough */
    else if (resultGetFreezeFrameData == DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE)
    {
#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
#endif
    }
    /* if wrong record number passed */
    else if (resultGetFreezeFrameData == DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER)
    {
      resultGetSSRecord = DCM_E_WRONG_RECORD_NUM;
    }
    /* if response is pending */
    else if (resultGetFreezeFrameData == DEM_GET_FFDATABYDTC_PENDING)
    {
      resultGetSSRecord = DCM_E_PENDING;
    }
    /* all other errors */
    else
    {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* Deviation MISRA-2 */
      if((resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_OK) &&
      (resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_WRONG_DTC) &&
      (resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_WRONG_DTCORIGIN) &&
      (resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_WRONG_RECORDNUMBER) &&
      (resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_WRONG_BUFFERSIZE) &&
      (resultGetFreezeFrameData != DEM_GET_FFDATABYDTC_PENDING))
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_GETFREEZEFRAMEDATABYDTC, DCM_E_INTERFACE_RETURN_VALUE);
      }
#endif
#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
    }
  }
  /* wrong buffer size */
  else
  {
#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
#endif
  }

  DBG_DCM_DSPINTERNAL_DEMGETSNAPSHOTRECORD_EXIT(resultGetSSRecord,DTC,SnapShotRecordNumber,
                                                sizeRemainingBuffer,pMsgContext,resDataLengthPtr);
  return resultGetSSRecord;
}
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
/* Function is used by Dcm_DspInternal_ReportDtcExtendedDataRecordByDtcNumber_SSvcH()
 * to simplify DEM readout */
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetExtDataRecord(
  uint32 DTC,
  uint8 ExtendedDataRecordNumber,
  PduLengthType sizeRemainingBuffer,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) resDataLengthPtr
)
{
  Dcm_StatusType resultGetExtRec = DCM_E_NOT_OK;

  DBG_DCM_DSPINTERNAL_DEMGETEXTDATARECORD_ENTRY(DTC,ExtendedDataRecordNumber,sizeRemainingBuffer,
                                                pMsgContext,resDataLengthPtr);

  /* if buffer is not full */
  if (sizeRemainingBuffer > DCM_DTC_EXT_RECORD_NUM_LEN)
  {
    Dem_ReturnGetExtendedDataRecordByDTCType resultGetExtendedData;
    /* max buffer size for DEM is 255 byte */
    /* calculate the size remaining in response buffer after the size for holding record number.
       one byte is subtracted from remaining buffer size for holding extended record number */
    uint16 bufferSize = 0U;

    if(sizeRemainingBuffer > 0xFFU)
    {
      bufferSize = (uint16)0xFFU;
    }
    else
    {
      bufferSize = (uint16)(sizeRemainingBuffer - DCM_DTC_EXT_RECORD_NUM_LEN);
    }

    resultGetExtendedData = Dem_GetExtendedDataRecordByDTC(
      (uint32)DTC,
      DEM_DTC_ORIGIN_PRIMARY_MEMORY,
      (uint8)ExtendedDataRecordNumber,
      /* one byte is left in response buffer for copying extended record number */
      &pMsgContext->resData[*resDataLengthPtr + DCM_DTC_EXT_RECORD_NUM_LEN],
      &bufferSize);

    if ( resultGetExtendedData == DEM_RECORD_OK )
    {
      /* Check if there are no extended records for the DTC requested */
      if(bufferSize != 0U)
      {
        /* copy the extended record number to response buffer */
        pMsgContext->resData[*resDataLengthPtr] = (Dcm_MsgItemType)ExtendedDataRecordNumber;
        /* update the response length */
        *resDataLengthPtr += (PduLengthType)(bufferSize + DCM_DTC_EXT_RECORD_NUM_LEN);
      }
      resultGetExtRec = DCM_E_OK;
    }
    /* if response is pending */
    else if ( resultGetExtendedData == DEM_RECORD_PENDING )
    {
      resultGetExtRec = DCM_E_PENDING;
    }
    /* if wrong buffer size */
    else if ( resultGetExtendedData == DEM_RECORD_WRONG_BUFFERSIZE )
    {
#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
#endif
    }
    /* if wrong record number passed */
    else if (resultGetExtendedData == DEM_RECORD_WRONG_NUMBER)
    {
      resultGetExtRec = DCM_E_WRONG_RECORD_NUM;
    }
    else
    {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      /* Deviation MISRA-2 */
      if((resultGetExtendedData != DEM_RECORD_OK) &&
      (resultGetExtendedData != DEM_RECORD_WRONG_DTC) &&
      (resultGetExtendedData != DEM_RECORD_WRONG_DTCORIGIN) &&
      (resultGetExtendedData != DEM_RECORD_WRONG_NUMBER) &&
      (resultGetExtendedData != DEM_RECORD_WRONG_BUFFERSIZE) &&
      (resultGetExtendedData != DEM_RECORD_PENDING))
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_GETEXTENDEDDATABYDTC, DCM_E_INTERFACE_RETURN_VALUE);
      }
#endif
#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
    }
  }
  /* wrong buffer size */
  else
  {
#if (DCM_PAGEDBUFFER_ENABLED == STD_OFF)
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
#endif
  }

  DBG_DCM_DSPINTERNAL_DEMGETEXTDATARECORD_EXIT(resultGetExtRec,DTC,ExtendedDataRecordNumber,
                                               sizeRemainingBuffer,pMsgContext,resDataLengthPtr);
  return resultGetExtRec;
}
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) */

#if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON))
/* Used by UDS service 0x19-0x04 and 0x19-0x06 for getting status of one specific DEM DTC */
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemReportStatusByte(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC)
{
  Dcm_StatusType resultReportStatusByte = DCM_E_NOT_OK;
  uint8 DTCStatus;
  Dem_ReturnGetStatusOfDTCType returnGetStatus;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* Get the pointer to filled length in response buffer */
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) FilledLengthPtr =
    &(Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen);
#endif/* #if DCM_PAGEDBUFFER_ENABLED */

  DBG_DCM_DSPINTERNAL_DEMREPORTSTATUSBYTE_ENTRY(pMsgContext,DTC);

  /* calculate DTC value from diagnostic request data */
  *DTC = ((uint32)pMsgContext->reqData[0] << 16U) |
         ((uint32)pMsgContext->reqData[1] << 8U) |
         ((uint32)pMsgContext->reqData[2]);

  /* check whether buffer has enough space to hold the DTC code and the status */
  if ((pMsgContext->resDataLen + DCM_DTC_AND_STATUS_SNGL_RCD_LEN) <=
                                                                pMsgContext->resMaxDataLen)
  {
    returnGetStatus = Dem_GetStatusOfDTC(
      *DTC,
      DEM_DTC_ORIGIN_PRIMARY_MEMORY,
      &DTCStatus);

    switch ( returnGetStatus )
    {
      case DEM_STATUS_OK:
        /* no shared buffer */
        pMsgContext->resData[1] = pMsgContext->reqData[0];
        pMsgContext->resData[2] = pMsgContext->reqData[1];
        pMsgContext->resData[3] = pMsgContext->reqData[2];

        pMsgContext->resData[4] = (Dcm_MsgItemType)DTCStatus;

        /* update the response length */
        pMsgContext->resDataLen    += 4U;
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
        (*FilledLengthPtr)         += 4U;
#endif
        resultReportStatusByte = DCM_E_OK;
        break;

      case DEM_STATUS_FAILED:
        /* just failed - conditions are not correct */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
        break;

      case DEM_STATUS_PENDING:
        resultReportStatusByte = DCM_E_PENDING;
        break;

      default:
        /* wrong DTC */
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        break;
    }
  }
  else
  {
    /* Response Too long */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
  }

  DBG_DCM_DSPINTERNAL_DEMREPORTSTATUSBYTE_EXIT(resultReportStatusByte,pMsgContext,DTC);
  return resultReportStatusByte;
}

#endif /* #if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)) */

/* if Paged buffer handling enabled */
#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
#if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON) )
/* Used to enable process page function to be called from Call Service function of DSP SM*/
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_EnableProcessPage (
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  uint8 processPageFuncId
)
{
  DBG_DCM_DSPINTERNAL_ENABLEPROCESSPAGE_ENTRY(pMsgContext,processPageFuncId);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
    TS_PARAM_UNUSED(pMsgContext);
#endif
  /* set process page function id */
  DCM_HSM_INFO(Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId).processPageFuncId
    = (uint8)processPageFuncId;

  DBG_DCM_DSPINTERNAL_ENABLEPROCESSPAGE_EXIT(pMsgContext,processPageFuncId);
}
#endif /* #if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) || \
               (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)) */

STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_UpdateResponseBuffer(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* configuration of current Tx buffer */
  P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig;

  /* length of data already stored in buffer */
  PduLengthType curTxBufferLen;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  DBG_DCM_DSPINTERNAL_UPDATERESPONSEBUFFER_ENTRY(pMsgContext);

  /* get configuration of current transmission buffer */
  curTxBufferConfig = &Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId];

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* get length of data already stored in buffer */
  curTxBufferLen = curTxBufferConfig->bufferInfo->filledLen;

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* Update the response data buffer with PagedBufPtr */
  pMsgContext->resData = &curTxBufferConfig->ptrBuffer[curTxBufferLen];

  /* Update the response data buffer size */
  pMsgContext->resMaxDataLen = curTxBufferConfig->size - curTxBufferLen;

  DBG_DCM_DSPINTERNAL_UPDATERESPONSEBUFFER_EXIT(pMsgContext);
}

#if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
     (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON))
/* Page processing function of service report DTC by status mask */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDTCByStatusMask (
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  PduLengthType FilledLength = 0U;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  Dem_ReturnGetNextFilteredDTCType resultGetNextDtc = DEM_FILTERED_OK;
  uint8 dtcStatusMask;
  uint32 reqDtc;

  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCBYSTATUSMASK_ENTRY(pMsgContext);

  /* loop until no further matching DTC is returned or response buffer becomes
     too small or maximum no. of filtered DTC count is reached */
  do
  {
    /* gather DTC informations */
    resultGetNextDtc = Dem_GetNextFilteredDTC(&reqDtc, &dtcStatusMask);

    if (resultGetNextDtc == DEM_FILTERED_OK)
    {
      /* append DTC(3 byte) and DTCStatus(1 byte) to the response buffer */
      pMsgContext->resData[FilledLength] = (uint8)(reqDtc >> 16U);
      FilledLength++;
      pMsgContext->resData[FilledLength] = (uint8)(reqDtc >> 8U);
      FilledLength++;
      pMsgContext->resData[FilledLength] = (uint8)(reqDtc);
      FilledLength++;
      pMsgContext->resData[FilledLength] = (Dcm_MsgItemType)dtcStatusMask;
      FilledLength++;

      /* update the remaining DTC count to be sent as response */
        DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount--;
    }
  }
  /* Deviation MISRA-2 */
  while ((resultGetNextDtc == DEM_FILTERED_OK) &&
         (DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount > 0U) &&
          /* Deviation MISRA-2 */
         ((FilledLength + (PduLengthType)DCM_DTC_AND_STATUS_SNGL_RCD_LEN) <=
          pMsgContext->resMaxDataLen));

  /* if total response sent is less than actual response to be sent,
       then fill remaining bytes with 0 */
  if (resultGetNextDtc == DEM_FILTERED_NO_MATCHING_DTC)
  {
    while ((DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount > 0U) &&
           ((FilledLength + (PduLengthType)DCM_DTC_AND_STATUS_SNGL_RCD_LEN) <=
           pMsgContext->resMaxDataLen))
    {
      pMsgContext->resData[FilledLength] = 0U;
      FilledLength++;
      pMsgContext->resData[FilledLength] = 0U;
      FilledLength++;
      pMsgContext->resData[FilledLength] = 0U;
      FilledLength++;
      pMsgContext->resData[FilledLength] = 0U;
      FilledLength++;
      DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount--;
    }
  }

  /* if response buffer is filled with data */
  if (((FilledLength) +
    (Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen)) > 0U)
  {
    /* Indicate to start processing of the page, by passing the total number of bytes filled in
       this call of Dcm_DspInternal_ProcessPageDTCByStatusMask() */
    Dcm_DsdInternal_ProcessPage(FilledLength);

    serviceProcessStatus = DCM_E_PROCESS_PAGE;
  }
  else
  {
    /* if no data is filled, the processign function is called again */
    serviceProcessStatus = DCM_E_PENDING;
  }

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCBYSTATUSMASK_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if ((DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON) || \
                (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)
/* Page processing function of service report DTC Snapshot Record by Identification */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDTCSnapshotByIdentification (
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  PduLengthType FilledLength = 0U;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  Dem_ReturnGetNextFilteredDTCType resultGetNextRecord = DEM_FILTERED_OK;
  uint8 dtcSnapShotRecordNum;
  uint32 reqDtc;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTBYIDENTIFICATION_ENTRY(pMsgContext);

  /* loop until no further freezed frame record is returned or response buffer becomes
     too small or maximum no. of filtered DTC count is reached */
  do
  {
    /* gather DTC informations */
    resultGetNextRecord = Dem_GetNextFilteredRecord(&reqDtc, &dtcSnapShotRecordNum);

    if (resultGetNextRecord == DEM_FILTERED_OK)
    {
      /* append DTC(3 byte) and DTCStatus(1 byte) to the response buffer */
      pMsgContext->resData[FilledLength] = (uint8)(reqDtc >> 16U);
      FilledLength++;
      pMsgContext->resData[FilledLength] = (uint8)(reqDtc >> 8U);
      FilledLength++;
      pMsgContext->resData[FilledLength] = (uint8)(reqDtc);
      FilledLength++;
      pMsgContext->resData[FilledLength] = (Dcm_MsgItemType)dtcSnapShotRecordNum;
      FilledLength++;

      /* update the remaining DTC count to be sent as response */
      DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount--;
    }
  }
  while ((resultGetNextRecord == DEM_FILTERED_OK) &&
         (DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount > 0U) &&
         ((FilledLength + (PduLengthType)DCM_DTC_SNAPSHOT_SNGL_RCD_LEN) <=
          pMsgContext->resMaxDataLen));
  if (resultGetNextRecord == DEM_FILTERED_PENDING)
  {
    serviceProcessStatus = DCM_E_PENDING;
  }
  else
  {
    /* if total response sent is less than actual response to be sent,
       then fill remaining bytes with 0 */
    if (resultGetNextRecord == DEM_FILTERED_NO_MATCHING_DTC)
    {
    while ((DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount > 0U) &&
           ((FilledLength + (PduLengthType)DCM_DTC_SNAPSHOT_SNGL_RCD_LEN) <=
           pMsgContext->resMaxDataLen))
      {
        pMsgContext->resData[FilledLength] = 0U;
        FilledLength++;
        pMsgContext->resData[FilledLength] = 0U;
        FilledLength++;
        pMsgContext->resData[FilledLength] = 0U;
        FilledLength++;
        pMsgContext->resData[FilledLength] = 0U;
        FilledLength++;
        DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCCount--;
      }
    }

    /* if response buffer is filled with data */
    if (((FilledLength) +
    (Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen)) > 0U)
    {
      /* Indicate to start processing of the page, by passing the total number of bytes filled in
         this call of Dcm_DspInternal_ProcessPageDTCSnapshotByIdentification() */
      Dcm_DsdInternal_ProcessPage(FilledLength);

      serviceProcessStatus = DCM_E_PROCESS_PAGE;
    }
    else
    {
      /* if no data is filled, the processign function is called again */
      serviceProcessStatus = DCM_E_PENDING;
    }
  }

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTBYIDENTIFICATION_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
/* Page processing function of service report DTC snapshot record by DTC number */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDtcSnapshotRecord
(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  PduLengthType FilledLength = 0U;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  /* Calculate the DTC value from request data */
  uint32 DTC = ((uint32)pMsgContext->reqData[0] << 16U) |
                ((uint32)pMsgContext->reqData[1] << 8U) |
                ((uint32)pMsgContext->reqData[2]);

  Dem_ReturnDisableDTCRecordUpdateType resultDisableDTCUpdate;

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTRECORD_ENTRY(pMsgContext);

  /* disable DTC record update */
  resultDisableDTCUpdate = Dem_DisableDTCRecordUpdate(DTC, DEM_DTC_ORIGIN_PRIMARY_MEMORY );

  if ( resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_OK )
  {
    /* if Paged buffer handling enabled */
    Dcm_StatusType resGetSnapShotRecord = DCM_E_OK;
    Std_ReturnType resultEnableDTCUpdate = E_OK;

    /* Read all UDS Snapshot Records */
    if ( DCM_READ_DTC_INFO_CONTEXT(instIdx).ReqRecNum == 0xFFU )
    {
      /* process DTC records from 0x00 to 0xFE */
      while ( DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum < 0xFFU )
      {
        /* update the response buffer with snapshot record */
        resGetSnapShotRecord =
          Dcm_DspInternal_DemGetSnapShotRecord(DTC,
                                               DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum,
                                               pMsgContext->resMaxDataLen - FilledLength,
                                               pMsgContext,
                                               &FilledLength);
        /* If Dcm_DspInternal_DemGetSnapShotRecord() returns wrong record number,
           execution should continue, since a valid record may exist after this.
           For all other errors, exit loop.
           */
        if (( resGetSnapShotRecord != DEM_GET_FFDATABYDTC_OK ) &&
            ( resGetSnapShotRecord != DCM_E_WRONG_RECORD_NUM ))
        {
          break;
        }

        /* update processed DTC record count */
        DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum++;
      }
     }
    /* if snapshot record number >= 0x00 &&  < 0xFF */
    else
    {
      /* update the buffer with snapshot record */
      resGetSnapShotRecord = Dcm_DspInternal_DemGetSnapShotRecord(DTC,
                                             DCM_READ_DTC_INFO_CONTEXT(instIdx).ReqRecNum,
                                             pMsgContext->resMaxDataLen - FilledLength,
                                             pMsgContext,
                                             &FilledLength);

      TS_PARAM_UNUSED(resGetSnapShotRecord);
    }

    /* enable DTC record update */
    resultEnableDTCUpdate = Dem_EnableDTCRecordUpdate();
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if((resultEnableDTCUpdate != E_OK) && (resultEnableDTCUpdate != E_NOT_OK))
    {
      DCM_DET_REPORT_ERROR(DCM_SVCID_ENABLEDTCRECORDUPDATE, DCM_E_INTERFACE_RETURN_VALUE);
    }
    else
#endif
    {
      TS_PARAM_UNUSED(resultEnableDTCUpdate);
    }
  }
  else
  {
    if (resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_PENDING)
    {
      serviceProcessStatus = DCM_E_PENDING;
    }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* Deviation MISRA-2 */
      if((resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_WRONG_DTC) &&
       (resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN) &&
       (resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_PENDING))
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_DISABLEDTCRECORDUPDATE, DCM_E_INTERFACE_RETURN_VALUE);
      }
    }
#endif
  }

  /* if response buffer is filled with data and no error occured */
  if ((((FilledLength)
    + (Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen)) > 0U) &&
      (resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_PENDING))
  {
    /* Start processing of the page, by passing the total number of bytes filled in
       this call of Dcm_DspInternal_ProcessPageDTCByStatusMask() */
    Dcm_DsdInternal_ProcessPage(FilledLength);

    serviceProcessStatus = DCM_E_PROCESS_PAGE;
  }
  else
  {
    serviceProcessStatus = DCM_E_PENDING;
  }

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCSNAPSHOTRECORD_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}

#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
/* Page processing function of service report DTC extended data record by DTC number */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ProcessPageDtcExtDataRecord
(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* Holds the number of bytes filled in response buffer */
  PduLengthType FilledLength = 0U;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  /* Calculate the DTC value from request data */
  uint32 DTC = ((uint32)pMsgContext->reqData[0] << 16U) |
                ((uint32)pMsgContext->reqData[1] << 8U) |
                ((uint32)pMsgContext->reqData[2]);

  /* disable DTC record update */
  Dem_ReturnDisableDTCRecordUpdateType resultDisableDTCUpdate =
                                  Dem_DisableDTCRecordUpdate(DTC, DEM_DTC_ORIGIN_PRIMARY_MEMORY);

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCEXTDATARECORD_ENTRY(pMsgContext);

  if ( resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_OK )
  {
    Dcm_StatusType resGetExtDataRecord = DCM_E_OK;
    Std_ReturnType resultEnableDTCUpdate = E_OK;

    /* if requested to read all UDS Snapshot Records */
    if ( DCM_READ_DTC_INFO_CONTEXT(instIdx).ReqRecNum == 0xFFU )
    {
      /* Process ExtDataRecord from 0x01..0xEF. ExtDataRecord 0xF0 to 0xFE are reserved */
      while ( DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum < 0xF0U )
      {
        resGetExtDataRecord =
          Dcm_DspInternal_DemGetExtDataRecord(DTC,
              DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum,
              pMsgContext->resMaxDataLen - FilledLength,
              pMsgContext,
              &FilledLength);

        /* If Dcm_DspInternal_DemGetExtDataRecord() returns wrong record number,
           execution should continue, since a valid record may exist after this.
           Errors such as Wrong DTC, Wrong DTC kind and Wrong DTC Origin will not be coming here,
           since these errors would have handled before starting paged processing.
           If the error is Wrong buffer size, the loop shall be exited and shall continue
           processing extended data records in next call of this function.
           */
        if (( resGetExtDataRecord != DCM_E_OK ) &&
            ( resGetExtDataRecord != DCM_E_WRONG_RECORD_NUM ))
        {
          break;
        }

        DCM_READ_DTC_INFO_CONTEXT(instIdx).DTCRecNum++;
      }
    }
    /* if requested to read specific UDS snapshot records */
    else
    {
      resGetExtDataRecord = Dcm_DspInternal_DemGetExtDataRecord(DTC,
              DCM_READ_DTC_INFO_CONTEXT(instIdx).ReqRecNum,
              pMsgContext->resMaxDataLen - FilledLength,
              pMsgContext,
              &FilledLength);

      TS_PARAM_UNUSED(resGetExtDataRecord);
    }

    /* enable DTC record update */
    resultEnableDTCUpdate = Dem_EnableDTCRecordUpdate();
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    if((resultEnableDTCUpdate != E_OK) && (resultEnableDTCUpdate != E_NOT_OK))
    {
      DCM_DET_REPORT_ERROR(DCM_SVCID_ENABLEDTCRECORDUPDATE, DCM_E_INTERFACE_RETURN_VALUE);
    }
    else
#endif
    {
      TS_PARAM_UNUSED(resultEnableDTCUpdate);
    }
  }
  else
  {
    if (resultDisableDTCUpdate == DEM_DISABLE_DTCRECUP_PENDING)
    {
      serviceProcessStatus = DCM_E_PENDING;
    }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
    else
    {
      /* Deviation MISRA-2 */
      if((resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_WRONG_DTC) &&
       (resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_WRONG_DTCORIGIN) &&
       (resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_PENDING))
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_DISABLEDTCRECORDUPDATE, DCM_E_INTERFACE_RETURN_VALUE);
      }
    }
#endif
  }
  /* if response bufer is filled with data */
  if ((((FilledLength) +
    (Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].bufferInfo->filledLen)) > 0U ) &&
    (resultDisableDTCUpdate != DEM_DISABLE_DTCRECUP_PENDING))
  {
    /* Start processing of the page, by passing the total number of bytes filled in
       this call of Dcm_DspInternal_ProcessPageDTCByStatusMask() */
    Dcm_DsdInternal_ProcessPage(FilledLength);

    serviceProcessStatus = DCM_E_PROCESS_PAGE;
  }
  else
  {
    serviceProcessStatus = DCM_E_PENDING;
  }

  DBG_DCM_DSPINTERNAL_PROCESSPAGEDTCEXTDATARECORD_EXIT(serviceProcessStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) */
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
/* The function for getting the total data length of freeze frame corresponding
   to the snapshot record number */
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetSizeOfFreezeFrame (
  uint32 DTC,
  uint8  SnapShotRecNum,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) DataLength,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Dcm_StatusType returnErrorCode = DCM_E_NOT_OK;
  Dem_ReturnGetSizeOfFreezeFrameByDTCType resultGetSizeOfFF;
  uint16 SizeOfFreezeFrame = 0U;

  DBG_DCM_DSPINTERNAL_DEMGETSIZEOFFREEZEFRAME_ENTRY(DTC,SnapShotRecNum,DataLength,pMsgContext);

  /* Call Dem_GetSizeOfFreezeFrameByDTC() to get the size of freeze frame. It will return the
     size of the  requested freeze frame record , including freeze frame header information.*/
  resultGetSizeOfFF = Dem_GetSizeOfFreezeFrameByDTC(
                        (uint32)DTC,
                        DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                        (uint8)SnapShotRecNum,
                        &SizeOfFreezeFrame);

  if (resultGetSizeOfFF == DEM_GET_SIZEOFFF_OK)
  {
    *DataLength = (PduLengthType) (SizeOfFreezeFrame);
    returnErrorCode = DCM_E_OK;
  }
  /* if response is pending */
  else if (resultGetSizeOfFF == DEM_GET_SIZEOFFF_PENDING)
  {
    returnErrorCode = DCM_E_PENDING;
  }
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  }

  DBG_DCM_DSPINTERNAL_DEMGETSIZEOFFREEZEFRAME_EXIT(returnErrorCode,DTC,SnapShotRecNum,
                                                   DataLength,pMsgContext);
  return returnErrorCode;
}
#endif  /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON) */

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
 /* The function for getting the total length of [Extended Data record + Record Number]
    corresponding to the extended data record number */
STATIC FUNC(Dcm_StatusType, DCM_CODE) Dcm_DspInternal_DemGetSizeOfExtDataRecord (
  uint32 DTC,
  uint8  ExtDataRecNum,
  P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) DataLength)
{
  Dcm_StatusType returnGetSizeExtData = DCM_E_NOT_OK;
  Dem_ReturnGetSizeOfExtendedDataRecordByDTCType resultGetSizeOfExtData;
  uint16 SizeOfExtDataRec = 0U;

  DBG_DCM_DSPINTERNAL_DEMGETSIZEOFEXTDATARECORD_ENTRY(DTC,ExtDataRecNum,DataLength);

  /* Get the size of [Extended Data record + Record Number] */
  resultGetSizeOfExtData = Dem_GetSizeOfExtendedDataRecordByDTC(
                        (uint32)DTC,
                        DEM_DTC_ORIGIN_PRIMARY_MEMORY,
                        (uint8)ExtDataRecNum,
                        &SizeOfExtDataRec);

  if (resultGetSizeOfExtData == DEM_GET_SIZEOFEDRBYDTC_OK)
  {
    *DataLength = (PduLengthType) SizeOfExtDataRec;
    returnGetSizeExtData = DCM_E_OK;
  }
  /* if wrong record number passed */
  else if (resultGetSizeOfExtData == DEM_GET_SIZEOFEDRBYDTC_W_RNUM)
  {
    returnGetSizeExtData = DCM_E_WRONG_RECORD_NUM;
  }
  /* if response is pending */
  else
  {
    if (resultGetSizeOfExtData == DEM_GET_SIZEOFEDRBYDTC_PENDING)
    {
      returnGetSizeExtData = DCM_E_PENDING;
    }
  }

  DBG_DCM_DSPINTERNAL_DEMGETSIZEOFEXTDATARECORD_EXIT(returnGetSizeExtData,DTC,
                                                     ExtDataRecNum,DataLength);
  return returnGetSizeExtData;
}
#endif /* #if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON) */

#endif /* (DCM_DSP_USE_SERVICE_0X19 == STD_ON) */

#if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
 /* This function is for reading all the signals configured in a DID */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid(
  uint16 DidIndex,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* Total number of signals configured for the DID*/
  uint16 numSignals = Dcm_DidTable[DidIndex].NumSignals;
  /* Pointer to the signal table for the DID */
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg = Dcm_DidTable[DidIndex].Signals;
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
    &DCM_READDIDCONTEXT(instIdx);
  uint16 didDataPosn = 0U ;
  Dcm_NegativeResponseCodeType nrc = E_OK;
  Std_ReturnType RetVal = E_NOT_OK;
  boolean SignalReadingPending = FALSE;

  DBG_DCM_DSPINTERNAL_READDID_ENTRY(DidIndex,DCM_INST(instIdx),OpStatus,pMsgContext);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

#if (DCM_ROE_ENABLED == STD_ON)
  /* check whether DID is already handled by signal polling in case of ROE started */
  SignalReadingPending =  Dcm_PostponeROEFromPollingDIDData(DidIndex);
#endif

  if ( SignalReadingPending == TRUE )
  {
    /* The operation needs to be called again. Exit the loop */
    RetVal = DCM_E_PENDING;
  }
  else
  {
    if( OpStatus == DCM_CANCEL )
    {
      (void) Dcm_DspInternal_ReadDid_Signal(DidIndex, instIdx, OpStatus, &nrc, &didDataPosn,
                                               pMsgContext);
      RetVal = E_NOT_OK;
    }
    else
    {
      /* If there are any signals in this DID to process, begin processing, otherwise
         return OK */

      if (numSignals != 0)
      {
        /* Loops over the signals in a DID while nrc not set and return value is not pending */
        while((pReadDIDContextType->SignalInd < numSignals)
              && (nrc == E_OK)
              /* Deviation MISRA-2 */
              && (RetVal != DCM_E_PENDING))
        {
          /* Starting bit position of signal after the DID in the response data */
          didDataPosn = SignalCfg[pReadDIDContextType->SignalInd].DataPos;
          /* Get configuration for current HSM instance */
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
          if(pReadDIDContextType->SignalInd >= 1U)
          {
            /* get configuration for current HSM instance */
            uint16 dataIndexPrev = SignalCfg[(pReadDIDContextType->SignalInd -1U)].DspDataIndex;
            CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
             = &DCM_HSM_CONFIG(instIdx);
            P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg_Prev =
               &Dcm_DidDataTable[dataIndexPrev];
            if(curHsmConfig->endianessConversion == TRUE)
            {
              didDataPosn = Dcm_DspInternal_SignalLengthOrDataPosition(dataCfg_Prev,
                                                                       didDataPosn,
                                                                       TRUE);
            }
          }
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */

          /* Check if the signal is being processed for the first time */
          if (pReadDIDContextType->InitSignalProcessing == TRUE)
          {
             RetVal = Dcm_DspInternal_ReadDid_Signal(DidIndex, instIdx, DCM_INITIAL,
                                                     &nrc, &didDataPosn, pMsgContext);
          }
          else
          {
             RetVal = Dcm_DspInternal_ReadDid_Signal(DidIndex, instIdx, OpStatus,
                                                     &nrc, &didDataPosn, pMsgContext);
          }
        }
      }
      else
      {
        /* This DID contains no signals of its own, therefore just return. */
        RetVal = E_OK;
      }

      if(nrc != E_OK)
      {
        Dcm_ExternalSetNegResponse(pMsgContext, nrc);
      }
      /* If all the signals are read, update the resDataLen to hold the next DID and signals.*/
      else
      {
        if (pReadDIDContextType->SignalInd == numSignals)
        {
          /* Respons buffer is now filled with DID(2bytes) and Signals(NumSignalTotalBytes)*/
          pMsgContext->resDataLen += (PduLengthType)(pReadDIDContextType->NumSignalTotalBytes);
        }
      }
   }

#if (DCM_ROE_ENABLED == STD_ON)
  if ((RetVal == E_OK) || (RetVal == E_NOT_OK))
  {
    Dcm_AllowROEToPollDIDData ();
  }
#endif
  }

  DBG_DCM_DSPINTERNAL_READDID_EXIT(RetVal,DidIndex,DCM_INST(instIdx),OpStatus,pMsgContext);
  return RetVal;
}

/* This function is for reading signal data configured for a DID */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid_Signal(
  uint16 DidIndex,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc,
  P2CONST(uint16, AUTOMATIC, AUTOMATIC) didDataPosn,
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
  {
    /* Pointer to the signal table for the DID */
    P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg = Dcm_DidTable[DidIndex].Signals;
    /* Holds the context information of currently processed DID */
    P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
    &DCM_READDIDCONTEXT(instIdx);
    /* Holds the no of Bytes occupied by one signal in a Did */
    uint16 numSignalBytes = 0U;
    Std_ReturnType RetVal = E_NOT_OK;
    /* Index of the signal Data in the table Dcm_DidDataTable[] */
    uint16 dataIndex = SignalCfg[pReadDIDContextType->SignalInd].DspDataIndex;
    P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg = &Dcm_DidDataTable[dataIndex];
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
    /* Get configuration for current HSM instance */
    CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
        = &DCM_HSM_CONFIG(instIdx);
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON)*/
    /* Pointer for storing the DID and signals */
    Dcm_MsgType dataPtr = &pMsgContext->resData[pMsgContext->resDataLen];

    DBG_DCM_DSPINTERNAL_READDID_SIGNAL_ENTRY(DidIndex,DCM_INST(instIdx),OpStatus,nrc,
                                             didDataPosn,pMsgContext);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

    switch(pReadDIDContextType->DidReadSigConditionSt)
    {
      /* Deviation MISRA-3 */
      case DCM_DID_SIG_CONDITION_CALL:
        readSignalLength = dataCfg->DataLength;
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
        if(curHsmConfig->endianessConversion == TRUE)
        {
          readSignalLength = Dcm_DspInternal_SignalLengthOrDataPosition(dataCfg, 0U, FALSE);
        }
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON)*/
        /* For  USE_DATA_SYNCH_FNC, USE_DATA_ASYNCH_FNC,USE_DATA_SYNCH_CLIENT_SERVER,
           USE_DATA_ASYNCH_CLIENT_SERVER call the ConditionCheckRead operation and
           ReadDataLength operation. Dcm439 , Dcm436 */
        if((dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_FUNC) ||
           (dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_CLIENT_SERVER))
        {
          /* Call the ConditionCheckRead Async operation and handle the return values */
          RetVal = Dcm_DspInternal_ReadDid_ConditionCheckAsync(dataCfg, DCM_INST(instIdx),
                                                               OpStatus, nrc);
        }
        else if ((dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_FUNC) ||
                 (dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_CLIENT_SERVER))
        {
          /* Call the ConditionCheckRead Sync operation and handle the return values */
          RetVal = Dcm_DspInternal_ReadDid_ConditionCheckSync(dataCfg, DCM_INST(instIdx), nrc);
        }
        else
        {
          /* continue to read the data */
          pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_READ;
          /* Initialising the status of Nvm data state to read */
          pReadDIDContextType->DidNvmDataSt = DCM_DID_SIGNAL_CALL;
        }

        if(RetVal != E_OK)
        {
          break;
        }
        else
        {
          /* fall through to next state */
        }
        /* Deviation MISRA-3 */
      case DCM_DID_SIG_READDATA_LEN_CALL:

        RetVal = Dcm_DspInternal_ReadDidSignalDataLength(DidIndex, DCM_INST(instIdx),
                                                         nrc, &readSignalLength);

        if(RetVal != E_OK)
        {
          break;
        }
         /* fall through to next state */
      /* Deviation MISRA-3 */
      case DCM_DID_SIG_READ:
        /* Check if the signal buffer is available */
        if (Dcm_SignalBufferContext.NvMService == DCM_DIDNVMOPERATION_NONE)
        {
          /* Getting the total number of bytes occupied by the data bits*/
          numSignalBytes = (uint16)DCM_GET_BYTES(*didDataPosn + readSignalLength );
           /* Whether buffer is free to hold signal data*/
          if ((pMsgContext->resDataLen + numSignalBytes) <= pMsgContext->resMaxDataLen)
          {
            if (pReadDIDContextType->InitSignalProcessing == TRUE)
            {
              RetVal = Dcm_DspInternal_ReadDidSignalData(dataIndex,
                                                       &pReadDIDContextType->DidNvmDataSt,
                                                       Dcm_SignalBufferContext.SignalBuffer,
                                                       nrc, DCM_INITIAL);
            }
            else
            {
              RetVal = Dcm_DspInternal_ReadDidSignalData(dataIndex,
                                                       &pReadDIDContextType->DidNvmDataSt,
                                                       Dcm_SignalBufferContext.SignalBuffer,
                                                       nrc, OpStatus);
            }

            if(OpStatus != DCM_CANCEL)
            {
              if(RetVal == E_OK)
              {
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
                if(((dataCfg->DataType == DCM_TYPE_SINT16) ||
                  (dataCfg->DataType == DCM_TYPE_UINT16) ||
                  /* Deviation MISRA-2 */
                  (dataCfg->DataType == DCM_TYPE_SINT32) ||
                  (dataCfg->DataType == DCM_TYPE_UINT32)) &&
                  (curHsmConfig->endianessConversion == TRUE))
                {
                  Dcm_DspInternal_Endianness_Conversion(Dcm_SignalBufferContext.SignalBuffer,
                                                        dataCfg->DataType);
                }
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */
                /* Copying signals to response buffer as per configured */
                Dcm_DspInternal_CopySignalData(Dcm_SignalBufferContext.SignalBuffer, dataPtr, 0U,
                  *didDataPosn, readSignalLength);
                /* One signal read succesfully. So incrementing index to read next signal */
                pReadDIDContextType->SignalInd++;
                /* Initialising the status of Async Signal state to process the next async signal*/
                pReadDIDContextType->DidAsynchSignalSt = DCM_DID_SIGNAL_CALL;
                pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_CONDITION_CALL;
                pReadDIDContextType->InitSignalProcessing = TRUE;
                /* This is for updating resDataLen after all signals read in a Did */
                if(numSignalBytes > pReadDIDContextType->NumSignalTotalBytes)
                {
                  pReadDIDContextType->NumSignalTotalBytes = numSignalBytes;
                }
              }
              else if (RetVal == DCM_E_PENDING)
              {
                pReadDIDContextType->InitSignalProcessing = FALSE;
              }
              else
              {
                /* Do Nothing */
              }
            }
            else
            {
              pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_READ_CANCEL;
            }
          }
          /* If buffer is too small for the response data */
          else
          {
            *nrc = DCM_E_GENERALREJECT;
            RetVal = E_OK;
          }
        }
        else
        {
          *nrc = DCM_E_CONDITIONSNOTCORRECT;
          RetVal = E_NOT_OK;
        }

        break;

        default:
        RetVal = E_OK;
        break;
    }

  DBG_DCM_DSPINTERNAL_READDID_SIGNAL_EXIT(RetVal,DidIndex,DCM_INST(instIdx),OpStatus,nrc,
                                          didDataPosn,pMsgContext);
  return RetVal;
}

/* Calls the ConditionCheckRead Async operation and handles the return values */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid_ConditionCheckAsync(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc)
{
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
  &DCM_READDIDCONTEXT(instIdx);
  Std_ReturnType RetVal;

  DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKASYNC_ENTRY(dataCfg, DCM_INST(instIdx), OpStatus, nrc);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* Calling the condition check read operation */
  RetVal = dataCfg->ConditionCheckReadAsync(OpStatus, nrc);
  if(OpStatus != DCM_CANCEL)
  {
    if(RetVal != E_OK)
    {
      if((RetVal == DCM_E_NO_DATA)||(RetVal == DCM_E_PENDING))
      {
        RetVal = DCM_E_PENDING;
         /* Make sure that any value written to the nrc parameter is ignored
           for a DCM_E_PENDING return value*/
        *nrc = DCM_E_POSITIVERESPONSE;
        pReadDIDContextType->InitSignalProcessing = FALSE;
      }
      else if(RetVal == E_NOT_OK)
      {
        /* In this case nrc will be set from the Condition check operation */
      }
      else
      {
        *nrc = DCM_E_GENERALREJECT;
      }
    }
    else
    {
      pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_READDATA_LEN_CALL;
      pReadDIDContextType->InitSignalProcessing = TRUE;
      /*If the Condition check read returns E_OK , set the nrc  to E_OK */
      *nrc = E_OK;
    }
  }
  else
  {
    pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_READ_CANCEL;
    RetVal = E_NOT_OK;
  }

  DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKASYNC_EXIT(dataCfg, DCM_INST(instIdx), OpStatus, nrc);
  return RetVal;
}

/* Calls the ConditionCheckRead Sync operation and handles the return values */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDid_ConditionCheckSync(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  uint8 instIdx,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc)
{
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
  &DCM_READDIDCONTEXT(instIdx);
  Std_ReturnType RetVal;

  DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKSYNC_ENTRY(dataCfg, DCM_INST(instIdx), nrc);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* Calling the condition check read operation */
  RetVal = dataCfg->ConditionCheckReadSync(nrc);
  if(RetVal != E_OK)
  {
    if(RetVal == E_NOT_OK)
    {
      /* In this case nrc will be set from the Condition check operation*/
    }
    else
    {
      *nrc = DCM_E_GENERALREJECT;
    }
  }
  else
  {
    pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_READDATA_LEN_CALL;
    /* If the Condition check read returns E_OK , set the nrc  to E_OK */
    *nrc = E_OK;
  }

  DBG_DCM_DSPINTERNAL_READDID_CONDITIONCHECKSYNC_EXIT(dataCfg, DCM_INST(instIdx), nrc);
  return RetVal;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidSignalDataLength
(
  uint16 DidIndex,
  uint8 instIdx,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc,
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) preadSignalLength
)
{
  /* Pointer to the signal table for the DID */
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg = Dcm_DidTable[DidIndex].Signals;
  /* Holds the context information of currently processed DID */
  P2VAR(Dcm_ReadDIDContextType, AUTOMATIC, DCM_VAR) pReadDIDContextType =
  &DCM_READDIDCONTEXT(instIdx);
  /* Index of the signal Data in the table Dcm_DidDataTable[] */
  uint16 dataIndex = SignalCfg[pReadDIDContextType->SignalInd].DspDataIndex;
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg = &Dcm_DidDataTable[dataIndex];

  Std_ReturnType RetVal = E_OK;
  uint16 readSignalDataLength = *preadSignalLength;

  DBG_DCM_DSPINTERNAL_READDIDSIGNALDATALENGTH_ENTRY(DidIndex, DCM_INST(instIdx),
                                                    nrc, preadSignalLength);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* In this state we call the Rte_Call of ReadDataLength.*/
  if((dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_FUNC) ||
     (dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_FUNC) ||
     ((dataCfg->AccessInterface == DCM_USE_DATA_SYNCH_CLIENT_SERVER) ||
     /* Deviation MISRA-2 */
      (dataCfg->AccessInterface == DCM_USE_DATA_ASYNCH_CLIENT_SERVER)))
  {
    /* If the length is not fixed call the ReadDataLength operation.*/
    if(dataCfg->FixedLength == FALSE)
    {
      RetVal = dataCfg->ReadDataLength(&readSignalDataLength);
      /* Signal length will be updated in bytes. Converting to no. of bits */
      readSignalDataLength = DCM_GET_BITS(readSignalDataLength);
      if(RetVal != E_OK)
      {
        *nrc = DCM_E_GENERALREJECT;
      }
      else
      {
        pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_READ;
      }
    }
    else
    {
      /* Continue to read the data */
      pReadDIDContextType->DidReadSigConditionSt = DCM_DID_SIG_READ;
    }
  }

  *preadSignalLength = readSignalDataLength;

  DBG_DCM_DSPINTERNAL_READDIDSIGNALDATALENGTH_EXIT(RetVal, DidIndex, DCM_INST(instIdx),
                                                   nrc, preadSignalLength);
  return RetVal;
}

#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
/* This function is for reading a signalLength or didDataPosn if Endianness Conversion is enabled*/
STATIC FUNC(uint16, DCM_CODE) Dcm_DspInternal_SignalLengthOrDataPosition(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataConfig,
  uint16 dataPosition,
  boolean select)
{
  uint16 sigLength = 0U;

  DBG_DCM_DSPINTERNAL_SIGNALLENGTHORDATAPOSITION_ENTRY(dataConfig,dataPosition,select);

  if(select == TRUE)
  {
    sigLength = (uint16)dataPosition;
  }
  else
  {
    sigLength = dataConfig->DataLength;
  }
  if((dataConfig->DataType == DCM_TYPE_SINT16) || (dataConfig->DataType == DCM_TYPE_UINT16))
  {
    if ( (dataConfig->DataLength / 16U) != 0U)
    {
      sigLength += (uint16)((((dataConfig->DataLength / 16U) + 1U) * 16U) -
                                    dataConfig->DataLength);
    }
    else
    {
      sigLength += (uint16)(16U - dataConfig->DataLength);
    }
  }
  else
  {
    if((dataConfig->DataType == DCM_TYPE_SINT32) || (dataConfig->DataType == DCM_TYPE_UINT32))
    {
      if ((dataConfig->DataLength / 32U) != 0U)
      {
        sigLength += (uint16)((((dataConfig->DataLength / 32U) + 1U) * 32U) -
                                    dataConfig->DataLength);
      }
      else
      {
        sigLength += (uint16)(32U - dataConfig->DataLength);
      }
    }
  }

  DBG_DCM_DSPINTERNAL_SIGNALLENGTHORDATAPOSITION_EXIT(sigLength,dataConfig,dataPosition,select);
  return sigLength;
}
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */
#endif /* #if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X2F == STD_ON)*/

#if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
/* Deviation MISRA-4 <+4> */
/* This function is for reading a signal*/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidSignalData(
  uint16 dataIndex,
  P2VAR(Dcm_DidAsynchSignalStType, AUTOMATIC, DCM_VAR) didNvmReadDataSt,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) signalBuffer,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc,
  Dcm_OpStatusType OpStatus)
{
  P2CONST(Dcm_DidDataType, AUTOMATIC, DCM_CONST) dataCfg = &Dcm_DidDataTable[dataIndex];
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_DCM_DSPINTERNAL_READDIDSIGNALDATA_ENTRY(dataIndex,didNvmReadDataSt,signalBuffer,
                                              nrc,OpStatus);

#if(DCM_READ_DID_BLOCK_ID_CONFIGURED == STD_OFF)
  TS_PARAM_UNUSED(didNvmReadDataSt);
#endif
  /* As per the Data interface of the signal Data*/
  switch (dataCfg->AccessInterface)
  {
#if(DCM_READ_DID_BLOCK_ID_CONFIGURED == STD_ON)

    case DCM_USE_BLOCK_ID:
    {
      NvM_RequestResultType Result = NVM_REQ_NOT_OK;

      /* Call the NVRam read with the block id configured */
      RetVal = Dcm_DspInternal_ReadNvmData(OpStatus, dataCfg, didNvmReadDataSt,
                                           &Result, signalBuffer);
      if (RetVal == E_NOT_OK)
      {
        if(Result == NVM_REQ_NV_INVALIDATED)
        {
          *nrc = DCM_E_CONDITIONSNOTCORRECT;
        }
        else
        {
          *nrc = DCM_E_GENERALREJECT;
        }
        *didNvmReadDataSt = DCM_DID_SIGNAL_CALL;
      }
    }
      break;
#endif /* (DCM_READ_DID_BLOCK_ID_CONFIGURED == STD_ON) */

    case DCM_USE_DATA_SYNCH_FUNC:
      RetVal = dataCfg->ReadDataFncSync(signalBuffer);
      if(RetVal != E_OK)
      {
        *nrc = DCM_E_GENERALREJECT;
      }
      break;

    case DCM_USE_DATA_ASYNCH_FUNC:
      RetVal = dataCfg->ReadDataFncAsync(OpStatus, signalBuffer);
      if(RetVal != E_OK)
      {
        if((RetVal == DCM_E_NO_DATA)||(RetVal == DCM_E_PENDING))
        {
          RetVal = DCM_E_PENDING;
        }
        else
        {
          *nrc = DCM_E_GENERALREJECT;
        }
      }
      break;

    case DCM_USE_ECU_SIGNAL:
      /* ECU signal reading is not supported currently */
      *nrc = DCM_E_GENERALREJECT;
      break;

#if (DCM_INCLUDE_RTE == STD_ON)
    case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
      /* In the case of Async signal,call the read operation. If pending is
         retuened again call the same operation with OpStatus is PENDING */
      RetVal = dataCfg->ReadDataFncAsync(OpStatus, signalBuffer);
      if(RetVal != E_OK)
      {
        if((RetVal == DCM_E_NO_DATA)||(RetVal == DCM_E_PENDING))
        {
          RetVal = DCM_E_PENDING;
        }
        else
        {
          *nrc = DCM_E_GENERALREJECT;
        }
      }
      break;

    case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
      RetVal = dataCfg->ReadDataFncSync(signalBuffer);
      if (RetVal != E_OK)
      {
        *nrc = DCM_E_GENERALREJECT;
      }
      break;
#endif /*DCM_INCLUDE_RTE == STD_ON*/
    default:
      break;
  }

  DBG_DCM_DSPINTERNAL_READDIDSIGNALDATA_EXIT(RetVal,dataIndex,didNvmReadDataSt,
                                             signalBuffer,nrc,OpStatus);
  return RetVal;
}

#if(DCM_READ_DID_BLOCK_ID_CONFIGURED == STD_ON)
/* This function is for reading data from NVM block */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadNvmData(
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DidDataType, AUTOMATIC, DCM_CONST) didDataCfg,
  P2VAR(Dcm_DidAsynchSignalStType, AUTOMATIC, DCM_VAR) didNvmReadDataSt,
  P2VAR(NvM_RequestResultType, AUTOMATIC, DCM_VAR) result,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) signalBuffer)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_DCM_DSPINTERNAL_READNVMDATA_ENTRY(didDataCfg,didNvmReadDataSt,result,signalBuffer);

  switch(*didNvmReadDataSt)
  {
    case DCM_DID_SIGNAL_CALL:
      /* Call the NVM read with the configured block id */
      RetVal = NvM_ReadBlock(didDataCfg->NvRamBlockId, signalBuffer);

      if(RetVal == E_OK)
      {
        /* if the request is accepted, set the state to call NvM_GetErrorStatus() in next
           invocation and return pending */
        *didNvmReadDataSt = DCM_DID_SIGNAL_RESULT;
        RetVal = DCM_E_PENDING;
      }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      else if (RetVal == E_NOT_OK)
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMREADDATA, DCM_E_NVM_READ_FAIL);
      }
      else
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMREADBLOCK, DCM_E_INTERFACE_RETURN_VALUE);
      }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

      break;

    case DCM_DID_SIGNAL_RESULT:
      /* check status of NVM read operation */
      RetVal = NvM_GetErrorStatus(didDataCfg->NvRamBlockId, result);

      if(RetVal == E_OK)
      {
        if (OpStatus != DCM_CANCEL)
        {
          /* if the data is successfully read */
          /* Deviation MISRA-2 */
          if( (*result == NVM_REQ_OK) || (*result == NVM_REQ_RESTORED_FROM_ROM) ||
              (*result == NVM_REQ_REDUNDANCY_FAILED) )
          {
            *didNvmReadDataSt = DCM_DID_SIGNAL_CALL;
          }
          /* if the operation is still going on */
          else if (*result == NVM_REQ_PENDING)
          {
            RetVal = DCM_E_PENDING;
          }
          /* if any error occured */
          else
          {
            RetVal = E_NOT_OK;
          }
        }
        else
        {
          if (*result == NVM_REQ_PENDING)
          {
            /* Call NvM_CancelJobs() to cancel all jobs pending in the queue for the NV Block */
            RetVal = NvM_CancelJobs(didDataCfg->NvRamBlockId);

#if (DCM_ASYNC_DID_SERVICES == STD_ON)
            /* ENTER critical section
               Only use critical sections if either of services 0x22 or 0x2e or 0x2f use an Async
               service handler, for performance reasons. Only a preemption by the MainFunction can
               have an impact on the Dcm_SignalBufferContext. */
            SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

            /* Mark SignalBuffer as busy and memorize the BlockId which is keeping it locked*/
            Dcm_SignalBufferContext.BlockId = didDataCfg->NvRamBlockId;
            Dcm_SignalBufferContext.NvMService = DCM_DIDNVMOPERATION_READNVMDATA;

#if (DCM_ASYNC_DID_SERVICES == STD_ON)
            /* LEAVE critical section */
            SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
            if (RetVal != E_OK)
            {
              /* if NvM_CancelJobs() failed */
              if (RetVal == E_NOT_OK)
              {
                DCM_DET_REPORT_ERROR(DCM_SVCID_NVMREADDATA, DCM_E_NVM_CANCEL_JOBS_FAILED);
              }
              else
              {
                DCM_DET_REPORT_ERROR(DCM_SVCID_NVMCANCELJOBS, DCM_E_INTERFACE_RETURN_VALUE);
              }
            }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
          }
        }
      }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      else if (RetVal == E_NOT_OK)
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMREADDATA, DCM_E_NVM_READ_FAIL);
      }
      else
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMGETERRORSTATUS, DCM_E_INTERFACE_RETURN_VALUE);
      }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
      break;

    default:
      /* do nothing */
      break;
  }

  /* replace all errors different from E_OK, E_NOT_OK and DCM_E_PENDING with E_NOT_OK
     in order to preserve the function interface */
  if ((RetVal != E_OK) && (RetVal != DCM_E_PENDING))
  {
    RetVal = E_NOT_OK;
  }

  DBG_DCM_DSPINTERNAL_READNVMDATA_EXIT(RetVal,didDataCfg,didNvmReadDataSt,result,signalBuffer);
  return RetVal;
}
#endif /* (DCM_READ_DID_BLOCK_ID_CONFIGURED == STD_ON) */
#endif /* #if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X2F == STD_ON))

/*This function checks all the conditions for a requested Did.
  Did must be configured and it should have read/write/control access,
  session access and security access*/
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DidConditionChecks(
  uint16 reqDid,
  Dcm_DidOpType DidOp,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) didIndex,
  uint8 instIdx)
{
  Std_ReturnType ReturnVal = E_NOT_OK;
  uint16 DidTableIndex = *didIndex;
  P2CONST(Dcm_DidAccessInfoType, AUTOMATIC, DCM_CONST) AccessInfo = NULL_PTR;

  DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKS_ENTRY(reqDid,DidOp,nrc,didIndex,DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* Initialize the nrcChecks to ok */
  *nrc = DCM_E_OK;

  /* If the requested Did is in valid range
     - for ReadDID and IOControlDID, the range is 0x00FF..0xF1FF and 0xF900..0xFEFF
     - for WriteDID, the range is 0x00FF..0xF1FF and 0xFD00..0xFEFF
   */
  if (((reqDid >= DCM_DID_STD_RW_LOW_LIMIT) && (reqDid <= DCM_DID_STD_RW_UP_LIMIT)) ||
      /* system supplier specific record data identifiers */
      ((reqDid >= DCM_DID_SUP_LOW_LIMIT) && (reqDid <= DCM_DID_SUP_UP_LIMIT)) ||
      (((DCM_DID_OP_READ == DidOp) || (DCM_DID_OP_IOCONTROL == DidOp)) &&
       /* Deviation MISRA-2 */
       (reqDid >= DCM_DID_STD_READ_LOW_LIMIT) && (reqDid <= DCM_DID_STD_READ_UP_LIMIT)))
  {
    /* Check if Did is Configured */
    if (Dcm_DspInternal_ValidateDidIndex(reqDid, &DidTableIndex) == FALSE)
    {
      *nrc = DCM_E_REQUESTOUTOFRANGE;
    }

    /* Check for read/write/control access */
    if (*nrc == DCM_E_OK)
    {
      if (DCM_DID_OP_READ == DidOp)
      {
        AccessInfo =  &Dcm_DidTable[DidTableIndex].ReadAccess;
      }
      else if (DCM_DID_OP_WRITE == DidOp)
      {
        AccessInfo =  &Dcm_DidTable[DidTableIndex].WriteAccess;
      }
      else
      {
        AccessInfo =  &Dcm_DidTable[DidTableIndex].ControlAccess;
      }

      if (AccessInfo->Enabled == FALSE)
      {
        *nrc = DCM_E_REQUESTOUTOFRANGE;
      }
    }

    /* Check for Session access, whether the DID can be read in the current session level */
    if ( (*nrc == DCM_E_OK) &&
         (AccessInfo->NumSesCtrls > 0U))
    {
      if (Dcm_DspInternal_DidConditionChecksSesLevel(DCM_INST(instIdx), AccessInfo) == FALSE)
      {
        *nrc = DCM_E_REQUESTOUTOFRANGE;
      }
    }

    /* Check for security access , If the DID can be read in the current security level*/
    if ( (*nrc == DCM_E_OK) &&
         (AccessInfo->NumSecLevels > 0U))
    {
      if (Dcm_DspInternal_DidConditionChecksSecLevel(DCM_INST(instIdx), AccessInfo) == FALSE)
      {
        *nrc = DCM_E_SECURITYACCESSDENIED;
      }
    }
  }
  else
  {
    *nrc = DCM_E_REQUESTOUTOFRANGE;
  }

  if(*nrc != DCM_E_OK)
  {
    ReturnVal = E_NOT_OK;
  }
  else
  {
    ReturnVal = E_OK;
  }

  *didIndex = DidTableIndex;

  DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKS_EXIT(ReturnVal,reqDid,DidOp,nrc,
                                              didIndex,DCM_INST(instIdx));
  return ReturnVal;
}

/* Check if Did is Configured*/
STATIC FUNC(boolean, DCM_CODE) Dcm_DspInternal_ValidateDidIndex
(
  uint16 reqDid,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) didIndex
)
{
  uint8_least i;
  boolean retVal = FALSE;

  DBG_DCM_DSPINTERNAL_VALIDATEDIDINDEX_ENTRY(reqDid, didIndex);

  for (i = 0U; i < DCM_NUM_DID ; ++i)
  {
    if (reqDid == Dcm_DidTable[i].Did)
    {
      *didIndex = (uint16)i;
      retVal    = TRUE;
      break;
    }
  }

  DBG_DCM_DSPINTERNAL_VALIDATEDIDINDEX_EXIT(retVal, reqDid, didIndex);
  return retVal;
}

STATIC FUNC(boolean, DCM_CODE)Dcm_DspInternal_DidConditionChecksSesLevel
(
  uint8 instIdx,
  P2CONST(Dcm_DidAccessInfoType, AUTOMATIC, DCM_CONST) AccessInfo
)
{
  boolean retVal = FALSE;
  uint8_least i;

  /* Get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  /* Get SesTabConfig info */
  P2CONST(Dcm_SesTabConfigType, AUTOMATIC, DCM_CONST) sesTabConfig =
        &Dcm_SesTabConfig[DCM_INST(instIdx)];

  Dcm_SesCtrlType curSesCtrl = sesTabConfig->SessionEntries[curHsmInfo->sesTabIdx].SesCtrl;

  DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSESLEVEL_ENTRY(DCM_INST(instIdx), AccessInfo);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  for (i = 0U; i < AccessInfo->NumSesCtrls ; ++i)
  {
    if ( (curSesCtrl == AccessInfo->SesCtrls[i]) ||
         (AccessInfo->SesCtrls[i] == DCM_ALL_SESSION_LEVEL))
    {
      retVal = TRUE;
      break;
    }
  }

  DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSESLEVEL_EXIT(retVal, DCM_INST(instIdx), AccessInfo);
  return retVal;
}

/* Check for security access , If the DID can be read in the current security level*/
STATIC FUNC(boolean, DCM_CODE)Dcm_DspInternal_DidConditionChecksSecLevel
(
  uint8 instIdx,
  P2CONST(Dcm_DidAccessInfoType, AUTOMATIC, DCM_CONST) AccessInfo
)
{
  uint8_least i;
  boolean retVal = FALSE;

  /* Get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSECLEVEL_ENTRY(DCM_INST(instIdx), AccessInfo);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* if DCM is in unlocked state */
  if (curHsmInfo->secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
  {
    Dcm_SecLevelType curSecLevel = Dcm_SecTabConfig.Entries[curHsmInfo->secTabIdx].SecLevel;
    /* Check for security level */
    for (i = 0U; i < AccessInfo->NumSecLevels ; ++i)
    {
      if (curSecLevel == AccessInfo->SecLevels[i])
      {
        retVal = TRUE;
        break;
      }
    }
  }
  DBG_DCM_DSPINTERNAL_DIDCONDITIONCHECKSSECLEVEL_EXIT(retVal, DCM_INST(instIdx), AccessInfo);
  return retVal;
}

#endif /* #if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if (DCM_DSP_USE_SERVICE_0X31 == STD_ON)

/* This function moves an arbitrary number of bits present in a buffer (noOfBits),
 * starting from a given position (fromPosition) to a given position (toPosition).
 * If clearJunkBits is TRUE, this function will behave like a SHIFT function,
 * i.e. all bits "traversed" by the moved chunk of data will be cleared.
*/
FUNC(void, DCM_CODE) Dcm_DspInternal_ShiftBitsInBuffer(
  P2VAR(Dcm_MsgItemType, AUTOMATIC, DCM_APPL_DATA) buffer,
  uint16 fromPosition, uint16 toPosition, uint16 noOfBits , boolean clearJunkBits)
{
  uint16_least i;
  uint16 InClearByte;
  uint8_least destBitPos,sourceBitPos;
  uint16 destBytePos,sourceBytePos;
  /* Rightwise shift */
  if (fromPosition < toPosition)
  {
    sourceBytePos = ((fromPosition + noOfBits)  - 1 )/ 8U;
    sourceBitPos  = ((fromPosition + noOfBits)  - 1 )% 8U;
    destBytePos   = ((toPosition + noOfBits)    - 1 )/ 8U;
    destBitPos    = ((toPosition + noOfBits)    - 1 )% 8U;

    /*right shifting of buffer */
    for( i = 0U; i < noOfBits ; i++)
    {
      if (DCM_IS_BIT_SET(buffer[sourceBytePos], (uint8)sourceBitPos))
      {
        DCM_SET_BIT(buffer[destBytePos], (uint8)destBitPos);
      }
      else
      {
        DCM_CLEAR_BIT(buffer[destBytePos], (uint8)destBitPos);
      }

      if(sourceBitPos == 0U)
      {
        sourceBytePos--;
        sourceBitPos = 7U ;
      }
      else
      {
        sourceBitPos--;
      }
      if(destBitPos == 0U)
      {
        destBytePos--;
        destBitPos= 7U;
      }
      else
      {
        destBitPos--;
      }
    }
  }
  /* leftwise shift */
  else
  {
    /* Initilisation of source and destination bit and byte positions for left shift */
    destBitPos = (uint8)(toPosition % 8U);
    destBytePos = toPosition / 8U;
    sourceBitPos = (uint8)(fromPosition % 8U);
    sourceBytePos = fromPosition / 8U;

    for( i = 0U; i < noOfBits ; i++)
    {
      if (DCM_IS_BIT_SET(buffer[sourceBytePos], (uint8)sourceBitPos))
      {
        DCM_SET_BIT(buffer[destBytePos], (uint8)destBitPos);
      }
      else
      {
        DCM_CLEAR_BIT(buffer[destBytePos], (uint8)destBitPos);
      }

      if(sourceBitPos == 7U)
      {
        sourceBytePos++;
        sourceBitPos = 0U;
      }
      else
      {
        sourceBitPos++;
      }
      if(destBitPos == 7U)
      {
        destBytePos++;
        destBitPos = 0U;
      }
      else
      {
        destBitPos++;
      }
    }
  }

  /* Clearing Junk bits */
  if(clearJunkBits == TRUE)
  {
    /* clearing junk bits left in front of the moved chunk of data */
    if (fromPosition < toPosition)
    {
      InClearByte = fromPosition / 8;
      buffer[InClearByte] = buffer[InClearByte] & (uint8)(~(uint8)(0xFFU << (fromPosition % 8)));
    }
    /* clearing junk bits left behind the moved chunk of data */
    else
    {
      if( destBitPos != 0U )
      {
        buffer[destBytePos] = buffer[destBytePos] & (uint8)(0xFFU >> (8U - (uint8)destBitPos));
      }
    }
  }
}

#endif /* DCM_DSP_USE_SERVICE_0X31 == STD_ON  */

#if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
(DCM_DSP_USE_SERVICE_0X86 == STD_ON) || (DCM_DSP_USE_SERVICE_0X31 == STD_ON) || \
 (DCM_DSP_USE_SERVICE_0X2F == STD_ON))

/* The function for copying bits from one buffer to another */
FUNC(void, DCM_CODE) Dcm_DspInternal_CopySignalData(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) SourceBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer,
  uint16 SourceStartPosition, uint16 DestStartPosition,
  uint16 SizeToCopy)
{
  uint8 SourceDataMask = 0x00U;
  uint8 DestByteSpace = 0x00U;
  uint16 Size = SizeToCopy;

  /* Initialize required bits to extract into Source data mask */
  uint8 SourceMaskBitsReq = 0x00U;

  /* Initialize the byte and bit position of source buffer from which data needs to be copied */
  /* The first 3 bits(Bit position 0..2) indicates the bit position and the rest of the bits
  indicate the byte index(Bit position 3..15) */
  uint8 SourceBitPos  = (uint8)(SourceStartPosition & DCM_BIT_POSITION_MASK);
  uint16 SourceBytePos = (uint16)(SourceStartPosition >> DCM_BYTE_POSITION_SHIFTS);

  /* Initialize the byte and bit position of destination buffer to which data needs to be copied */
  /* The first 3 bits(Bit position 0..2) indicates the bit position and the rest of the bits
  indicate the byte index(Bit position 3..15) */
  uint8 DestBitPos    = (uint8)(DestStartPosition & DCM_BIT_POSITION_MASK);
  uint16 DestBytePos   = (uint16)(DestStartPosition >> DCM_BYTE_POSITION_SHIFTS);

  DBG_DCM_DSPINTERNAL_COPYSIGNALDATA_ENTRY(SourceBuffer,DestBuffer,SourceStartPosition,
                                           DestStartPosition,Size);

  /* Process the buffer until all data bits are copied */
  while(Size > 0U)
  {
    /* Extract bits required for the source data mask */
    if(Size < ((uint16)DCM_BYTE_BITS - DestBitPos))
    {
      SourceMaskBitsReq = (uint8)Size;
    }
    else
    {
      SourceMaskBitsReq = DCM_BYTE_BITS - DestBitPos;
    }

    /* Extract required bits from the Source Buffer and store in Data mask */
    SourceDataMask = SourceBuffer[SourceBytePos] >> SourceBitPos;
    if(SourceMaskBitsReq > (DCM_BYTE_BITS - SourceBitPos))
    {
      SourceDataMask = SourceDataMask |
                      (uint8)(SourceBuffer[(SourceBytePos+1)] << (DCM_BYTE_BITS - SourceBitPos));
    }

    /* Check the current destination bit position is the start of the current destination byte */
    if(DestBitPos == 0U)
    {
      /* Check whether the number of bits to transfer is more than byte size */
      if(Size >= DCM_BYTE_BITS)
      {
        /* Do one byte transfer */
        DestBuffer[DestBytePos] = SourceDataMask;
        /* Decrement the number of bits to be copied by 8 */
        DestBytePos++;
        /* Increment the source Byte position */
        SourceBytePos++;
        Size = Size - DCM_BYTE_BITS;
      }
      else
      {
        /* Clear the bits that has to transfer in destination byte */
        DestBuffer[DestBytePos] = (DestBuffer[DestBytePos] & (uint8)(DCM_MASK_BYTE << Size));
        /* Transfer the number of remaining bits to current Dest byte */
        DestBuffer[DestBytePos] = DestBuffer[DestBytePos] |
                                  (SourceDataMask & (DCM_MASK_BYTE >> (DCM_BYTE_BITS-Size)));
        break;
      }
    }
    /* If current Destination Bit Position is not start of current byte */
    else
    {
      /* Count space in current destination byte to data storage */
      DestByteSpace = DCM_BYTE_BITS - DestBitPos;
      if( Size <= DestByteSpace)
      {
        /* Clear the bits that has to transfer in destination buffer */
        DestBuffer[DestBytePos] = DestBuffer[DestBytePos] &
                                  (uint8)(~((uint8)((uint8)(DCM_MASK_BYTE
                                  << (DCM_BYTE_BITS - Size)) >> (DestByteSpace - Size))));
        /* Transfer the number of remaining bits to current DestBuffer */
        DestBuffer[DestBytePos] = DestBuffer[DestBytePos] |
                                  ((uint8)(SourceDataMask <<DestBitPos)
                                  & (DCM_MASK_BYTE >> (DestByteSpace - Size)));

        /* Deviation MISRA-5 */
        break;
      }
      else
      {
        /* Clear the bits that has to transfer in destination buffer */
        DestBuffer[DestBytePos] = DestBuffer[DestBytePos] &
                                                  (uint8)(~(uint8)(DCM_MASK_BYTE << DestBitPos));
        /* Fill the current byte of DestBuffer using SourceDataMask*/
        DestBuffer[DestBytePos] = DestBuffer[DestBytePos] | (uint8)(SourceDataMask <<DestBitPos);

        /* Increment the source Byte and Bit Positions accordingly */
        if(DestByteSpace > (DCM_BYTE_BITS - SourceBitPos))
        {
          SourceBytePos++;
          SourceBitPos = (SourceBitPos - DestBitPos) - 1U;
        }
        else if(DestByteSpace < (DCM_BYTE_BITS - SourceBitPos))
        {
          SourceBitPos = SourceBitPos + DestByteSpace;
        }
        else
        {
          SourceBytePos++;
          SourceBitPos = 0U;
        }
        /* Increment the Destination Byte and Bit Positions accordingly */
        DestBytePos++;
        DestBitPos = 0U;
        /* Decrement the Size by DestByteSpace */
        Size = Size - DestByteSpace;
      }
    }
  }

  DBG_DCM_DSPINTERNAL_COPYSIGNALDATA_EXIT(SourceBuffer,DestBuffer,SourceStartPosition,
                                          DestStartPosition,Size);
}
#endif /* #if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
(DCM_DSP_USE_SERVICE_0X86 == STD_ON) || (DCM_DSP_USE_SERVICE_0X31 == STD_ON) || \
 (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if(DCM_DSP_USE_SERVICE_0X2E == STD_ON)

/* The function for checking the request data length of WriteDid request */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidRequestLengthChk(
  uint16 didIndex,
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)

{
  Std_ReturnType RetVal = E_NOT_OK;
  uint16 numSignals = Dcm_DidTable[didIndex].NumSignals;

  DBG_DCM_DSPINTERNAL_WRITEDIDREQUESTLENGTHCHK_ENTRY(didIndex,pMsgContext);

  if (numSignals > 0U)
  {
    P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg =
                                               &(Dcm_DidTable[didIndex].Signals[numSignals - 1U]);
    P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg =
                                               &Dcm_DidDataTable[SignalCfg->DspDataIndex];
    /* Calculate the total number of data bytes needed for all the signals configured in the DID.
     * The signals corresponding to a DID are stored in the order of starting position of signal
     * data in response buffer. So the total number of data bytes needed for all the signals in a
     * DID can be calculated by adding the position and size of the last signal configured for the
     * DID.
     */
    uint16 DidDataLength = (uint16)DCM_GET_BYTES(SignalCfg->DataPos + dataCfg->DataLength);

    /* if data length for the signal is fixed, total length configured for the DID should be equal
       to the (length of request data - size of DID[2 bytes]) */
    if (dataCfg->FixedLength == TRUE)
    {
      if (DidDataLength == (pMsgContext->reqDataLen - DCM_DID_ID_SIZE))
      {
        RetVal = E_OK;
      }
    }
    /* if data length for the signal is dynamic, total length configured for the DID should be
       greater than or equal to the (length of request data - size of DID[2 bytes]) */
    else
    {
      if (DidDataLength >= (pMsgContext->reqDataLen - DCM_DID_ID_SIZE))
      {
        RetVal = E_OK;
      }
    }
  }
  /* if number of signals is zero */
  else
  {
    /* if request data contains more data apart from DID */
    if (pMsgContext->reqDataLen <= DCM_DID_ID_SIZE)
    {
      RetVal = E_OK;
    }
  }

  DBG_DCM_DSPINTERNAL_WRITEDIDREQUESTLENGTHCHK_EXIT(RetVal,didIndex,pMsgContext);
  return RetVal;
}

/* The function is for writing the DID signal data */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDid(
  uint16 DidIndex,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType RetVal = E_NOT_OK;
  /* holds the number of signals in the DID */
  uint16 numSignals = Dcm_DidTable[DidIndex].NumSignals;
  /* holds the confguration table of signals in the DID */
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) SignalCfg = Dcm_DidTable[DidIndex].Signals;
  /* holds the context information of currently processed DID */
  P2VAR(Dcm_WriteDIDContextType, AUTOMATIC, DCM_VAR) WriteDIDContext =
                                                    &DCM_WRITE_DID_CONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_WRITEDID_ENTRY(DidIndex,DCM_INST(instIdx),OpStatus,pMsgContext);

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  /* Check if the signal buffer is available */
  if (Dcm_SignalBufferContext.NvMService == DCM_DIDNVMOPERATION_NONE)
  {
    /* process all the signals in the DID */
    do
    {
      if (WriteDIDContext->SignalInd < numSignals)
      {
        uint16_least i;
        /* bit-position of signal data in request buffer */
        uint16 didDataPosn = SignalCfg[WriteDIDContext->SignalInd].DataPos;
        /* index of the current signal in signal configuration table */
        uint16 dataIndex = SignalCfg[WriteDIDContext->SignalInd].DspDataIndex;
        /* holds the configuration of signal being processed */
        P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg = &Dcm_DidDataTable[dataIndex];
        /* Size of data in bytes, when signal length is dynamic */
        uint16 signalLength = 0U;

        /* Do NOT overwrite the data if it's written asynchronously in the NVM until
         * the write operation succeeds. */
        if (!((dataCfg->AccessInterface == DCM_USE_BLOCK_ID) &&
            (WriteDIDContext->DidNvmDataSt == DCM_DID_SIGNAL_RESULT)))
        {
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
          /* get configuration for current HSM instance */
          CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
            = &DCM_HSM_CONFIG(instIdx);
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */

          for (i = 0U; i < DCM_DATA_MAX_SIZE ; i++)
          {
            Dcm_SignalBufferContext.SignalBuffer[i] = 0x00U;
          }
          /* if signal data length is fixed */
          if (dataCfg->FixedLength == TRUE)
          {
            /* Copy the data of currently processed signal to writeSignalBuffer */
            Dcm_DspInternal_CopySignalData(&pMsgContext->reqData[DCM_DID_ID_SIZE],
                            Dcm_SignalBufferContext.SignalBuffer, didDataPosn, 0U,
                            dataCfg->DataLength);
          }
          else
          {
            signalLength = pMsgContext->reqDataLen - DCM_DID_ID_SIZE;
            /* Copy all the data in the request, after DID, to writeSignalBuffer */
            Dcm_DspInternal_CopySignalData(&pMsgContext->reqData[DCM_DID_ID_SIZE],
                          Dcm_SignalBufferContext.SignalBuffer, didDataPosn, 0U,
                          DCM_GET_BITS(signalLength));
          }
#if(DCM_ENDIANNESS_CONVERSION == STD_ON)
          if (((dataCfg->DataType == DCM_TYPE_SINT16) || (dataCfg->DataType == DCM_TYPE_UINT16) ||
            /* Deviation MISRA-2 */
            (dataCfg->DataType == DCM_TYPE_SINT32) || (dataCfg->DataType == DCM_TYPE_UINT32)) &&
            (curHsmConfig->endianessConversion == TRUE))
          {
            Dcm_DspInternal_Endianness_Conversion(Dcm_SignalBufferContext.SignalBuffer,
                                                  dataCfg->DataType);
          }
#endif /* #if(DCM_ENDIANNESS_CONVERSION == STD_ON) */
        }

        /* Call with OpStatus 'DCM_INITIAL' if the signal is being processed for the first time */
        if (WriteDIDContext->InitSignalProcessing == TRUE)
        {
          RetVal = Dcm_DspInternal_WriteDidSignal(dataIndex, Dcm_SignalBufferContext.SignalBuffer,
                                                  signalLength, instIdx, DCM_INITIAL, pMsgContext);
        }
        else
        {
          RetVal = Dcm_DspInternal_WriteDidSignal(dataIndex, Dcm_SignalBufferContext.SignalBuffer,
                                                  signalLength, instIdx, OpStatus, pMsgContext);
        }

        /* the interface type of the currently processed signal data */

        if (OpStatus == DCM_CANCEL)
        {
           RetVal = E_NOT_OK;
           break;
        }
        else if (RetVal == E_OK)
        {
          /* if the currently processed signal was written successfully,
               increment the signal index */
          WriteDIDContext->SignalInd++;
          WriteDIDContext->InitSignalProcessing = TRUE;
        }
        else
        {
          /* Do Nothing */
        }
      }
      else
      {
        /* Deviation MISRA-5 */
        break;
      }
    } while(RetVal== E_OK);
  }
  else
  {
    /* Signal buffer busy with another DID operation. Set NRC */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);

    RetVal = E_NOT_OK;
  }

  DBG_DCM_DSPINTERNAL_WRITEDID_EXIT(RetVal,DidIndex,DCM_INST(instIdx),OpStatus,pMsgContext);
  return RetVal;
}

/* The function is for writing a signal data */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidSignal(
  uint16 dataIndex,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) writeSignalBuffer,
  uint16 signalLength,
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType RetVal = E_NOT_OK;
  Dcm_NegativeResponseCodeType nrc = E_OK;
  /* holds the configuration of signal being processed */
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg = &Dcm_DidDataTable[dataIndex];
  DBG_DCM_DSPINTERNAL_WRITEDIDSIGNAL_ENTRY(dataIndex, writeSignalBuffer, signalLength,
                                           DCM_INST(instIdx), OpStatus, pMsgContext);
#if (DCM_WRITE_DID_BLOCK_ID_CONFIGURED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  switch (dataCfg->AccessInterface)
  {
#if(DCM_WRITE_DID_BLOCK_ID_CONFIGURED == STD_ON)
    /* if the data needs to be written via NVRAM interface */
    case DCM_USE_BLOCK_ID:

      RetVal = Dcm_DspInternal_WriteNvmData(instIdx, OpStatus, dataCfg, writeSignalBuffer);
      if(RetVal != E_OK)
      {
        nrc = DCM_E_GENERALPROGRAMMINGFAILURE;
      }
      break;
#endif /* (DCM_WRITE_DID_BLOCK_ID_CONFIGURED == STD_ON) */
/* if RTE enabled */
#if (DCM_INCLUDE_RTE == STD_ON)

    /* if the data needs to be written via RTE asynchronous interface */
    case DCM_USE_DATA_ASYNCH_CLIENT_SERVER:
      RetVal = Dcm_DspInternal_WriteDidAsyncClientServer(dataCfg, writeSignalBuffer,
                                                          signalLength, OpStatus, &nrc);
      break;

    /* if the data needs to be written via RTE synchronous interface */
    case DCM_USE_DATA_SYNCH_CLIENT_SERVER:
      RetVal = Dcm_DspInternal_WriteDidSyncClientServer(dataCfg,
                                                        writeSignalBuffer, signalLength, &nrc);
      break;

#endif /* #if (DCM_INCLUDE_RTE == STD_ON) */

    /* if the data needs to be written via IO-H/w abstraction interface */
    case DCM_USE_ECU_SIGNAL:
      /* This feature is not currently supported */
      RetVal = E_NOT_OK;
      nrc = DCM_E_GENERALREJECT;
      break;

    /* if the data needs to be written via user function */
    case DCM_USE_DATA_SYNCH_FUNC:
      RetVal = Dcm_DspInternal_WriteDidSyncFunc(dataCfg, writeSignalBuffer, signalLength, &nrc);
      break;

    /* if the data needs to be written via user function */
    case DCM_USE_DATA_ASYNCH_FUNC:
       RetVal = Dcm_DspInternal_WriteDidAsyncFunc(dataCfg, writeSignalBuffer, signalLength,
                                                  OpStatus, &nrc);
      break;

    default:
      /* do nothing */
      break;
  }

  /* if any error occured during processing, set the NRC */
  if(RetVal == E_NOT_OK)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, nrc);
  }
  DBG_DCM_DSPINTERNAL_WRITEDIDSIGNAL_EXIT(RetVal, dataIndex, writeSignalBuffer, signalLength,
                                          DCM_INST(instIdx), OpStatus, pMsgContext);
  return RetVal;
}

#if (DCM_INCLUDE_RTE == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidAsyncClientServer
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  DBG_DCM_DSPINTERNAL_WRITEDIDASYNCCLIENTSERVER_ENTRY(
                                dataCfg, signalBuffer, signalLength, OpStatus, nrc);

  /* check the processing stage of asynchronous signal */
  /* Call the Rte_Call_Xxx() interface to write the signal data */
  if (dataCfg->FixedLength == TRUE)
  {
    RetVal = dataCfg->WriteFixedLengthDataAsync(signalBuffer, OpStatus, nrc);
  }
  else
  {
    RetVal = dataCfg->WriteVarLengthDataAsync(signalBuffer,
                                         signalLength,
                                         OpStatus,
                                         nrc);
  }

  /* if writing of signal is not completed */
  if (RetVal == DCM_E_NO_DATA)
  {
    RetVal = DCM_E_PENDING;
  }
  /* any other errors */
  /* Deviation MISRA-2 */
  else
  {
    if ((RetVal != DCM_E_PENDING) && (RetVal != E_NOT_OK) && (RetVal != E_OK))
    {
      RetVal = E_NOT_OK;
      *nrc = DCM_E_GENERALREJECT;
    }
  }
  DBG_DCM_DSPINTERNAL_WRITEDIDASYNCCLIENTSERVER_EXIT(
                    RetVal, dataCfg, signalBuffer, signalLength, OpStatus, nrc);
  return RetVal;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidSyncClientServer
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
)
{
  Std_ReturnType RetVal = E_NOT_OK;
  DBG_DCM_DSPINTERNAL_WRITEDIDSYNCCLIENTSERVER_ENTRY(dataCfg, signalBuffer, signalLength, nrc);

 /* Call the synchronous interface for writing the signal data */
  if (dataCfg->FixedLength == TRUE)
  {
    RetVal = dataCfg->WriteFixedDataSync(signalBuffer, nrc);
  }
  else
  {
    RetVal = dataCfg->WriteVariableDataSync(signalBuffer,
                                        signalLength,
                                        nrc);
  }

  /* any return value other than Ok and NotOk */
  /* Deviation MISRA-2 */
  if ((RetVal != E_OK) && (RetVal != E_NOT_OK))
  {
    RetVal = E_NOT_OK;
    *nrc = DCM_E_GENERALREJECT;
  }
  DBG_DCM_DSPINTERNAL_WRITEDIDSYNCCLIENTSERVER_EXIT(RetVal, dataCfg, signalBuffer,
                                                    signalLength, nrc);
  return RetVal;
}
#endif

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidSyncFunc
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_DCM_DSPINTERNAL_WRITEDIDSYNCFUNC_ENTRY(dataCfg, signalBuffer, signalLength, nrc);

  /* Call the user function for writing the signal data */
  if (dataCfg->FixedLength == TRUE)
  {
    RetVal = dataCfg->WriteFixedDataSync(signalBuffer, nrc);
  }
  else
  {
    RetVal = dataCfg->WriteVariableDataSync(signalBuffer,
                                        signalLength,
                                        nrc);
  }

  /* any return value other than Ok and NotOk */
  /* Deviation MISRA-2 */
  if ((RetVal != E_OK) && (RetVal != E_NOT_OK))
  {
    RetVal = E_NOT_OK;
    *nrc = DCM_E_GENERALREJECT;
  }

  DBG_DCM_DSPINTERNAL_WRITEDIDSYNCFUNC_EXIT(RetVal, dataCfg, signalBuffer, signalLength, nrc);
  return RetVal;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDidAsyncFunc
(
  P2CONST(Dcm_DidDataType, TYPEDEF, DCM_CONST) dataCfg,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) signalBuffer,
  uint16 signalLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) nrc
)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_DCM_DSPINTERNAL_WRITEDIDASYNCFUNC_ENTRY(dataCfg, signalBuffer, signalLength, OpStatus, nrc);
  /* Call the user function for writing the signal data */
  if (dataCfg->FixedLength == TRUE)
  {
    RetVal = dataCfg->WriteFixedLengthDataAsync(signalBuffer, OpStatus, nrc);
  }
  else
  {
    RetVal = dataCfg->WriteVarLengthDataAsync(signalBuffer,
                                         signalLength,
                                         OpStatus,
                                         nrc);
  }

  /* if writing of signal is not completed */
  if (RetVal == DCM_E_NO_DATA)
  {
    RetVal = DCM_E_PENDING;
  }
  /* any other errors */
  /* Deviation MISRA-2 */
  else
  {
    if ((RetVal != DCM_E_PENDING) && (RetVal != E_NOT_OK) && (RetVal != E_OK))
    {
      RetVal = E_NOT_OK;
      *nrc = DCM_E_GENERALREJECT;
    }
  }
  DBG_DCM_DSPINTERNAL_WRITEDIDASYNCFUNC_EXIT(RetVal, dataCfg, signalBuffer,
                                             signalLength, OpStatus, nrc);
  return RetVal;
}

#if(DCM_WRITE_DID_BLOCK_ID_CONFIGURED == STD_ON)
/* This function is for writing data to NVM block */
/* Deviation MISRA-4 <+5> */
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteNvmData(
  uint8 instIdx,
  Dcm_OpStatusType OpStatus,
  P2CONST(Dcm_DidDataType, AUTOMATIC, DCM_CONST) didDataCfg,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) signalBuffer)
{
  P2VAR(Dcm_WriteDIDContextType, AUTOMATIC, DCM_VAR) pWriteDIDContextType =
        &DCM_WRITE_DID_CONTEXT(instIdx);
  Std_ReturnType RetVal = E_NOT_OK;
  NvM_RequestResultType Result = NVM_REQ_NOT_OK;
  boolean NvmOperationPending = FALSE;

  DBG_DCM_DSPINTERNAL_WRITENVMDATA_ENTRY(DCM_INST(instIdx),didDataCfg,signalBuffer);

#if ((DCM_HSM_INST_MULTI_ENABLED == STD_OFF) && (DCM_DBG_ENABLED == STD_OFF))
  TS_PARAM_UNUSED(instIdx);
#endif

  switch(pWriteDIDContextType->DidNvmDataSt)
  {
    case DCM_DID_SIGNAL_CALL:

      /* Unlock the NVRAM block */
      NvM_SetBlockLockStatus(didDataCfg->NvRamBlockId, FALSE);
      /* Call the NVM write with the configured block id */
      RetVal = NvM_WriteBlock(didDataCfg->NvRamBlockId, signalBuffer);
      if(RetVal == E_OK)
      {
        /* if the request is accepted, set the state to call NvM_GetErrorStatus() in next
           invocation and return pending */
        pWriteDIDContextType->DidNvmDataSt = DCM_DID_SIGNAL_RESULT;
        RetVal = DCM_E_PENDING;
      }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      else if (RetVal == E_NOT_OK)
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMWRITEDATA, DCM_E_NVM_WRITE_FAIL);
      }
      else
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMWRITEBLOCK, DCM_E_INTERFACE_RETURN_VALUE);
      }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

      break;

  case DCM_DID_SIGNAL_RESULT:
      /* check result of NVM write operation */
      RetVal = NvM_GetErrorStatus(didDataCfg->NvRamBlockId, &Result);
      if(RetVal == E_OK)
      {
        if (OpStatus != DCM_CANCEL)
        {
          /* if the data is successfully written */
          if (Result == NVM_REQ_OK)
          {
            pWriteDIDContextType->DidNvmDataSt = DCM_DID_SIGNAL_INVALID;
          }
          /* if the operation is still going on */
          else if (Result == NVM_REQ_PENDING)
          {
            RetVal = DCM_E_PENDING;
          }
          /* if any error occured */
          else
          {
            RetVal = E_NOT_OK;
          }
        }
        else
        {
          if (Result == NVM_REQ_PENDING)
          {
            /* Call NvM_CancelJobs() to cancel all jobs pending in the queue for the NV Block */
            RetVal = NvM_CancelJobs(didDataCfg->NvRamBlockId);

            NvmOperationPending = TRUE;

#if (DCM_ASYNC_DID_SERVICES == STD_ON)
            /* ENTER critical section
               Only use critical sections if either of services 0x22 or 0x2e or 0x2f use an Async
               service handler, for performance reasons. Only a preemption by the MainFunction can
               have an impact on the Dcm_SignalBufferContext. */
            SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

            /* Mark SignalBuffer as busy and memorize the BlockId which is keeping it locked*/
            Dcm_SignalBufferContext.BlockId = didDataCfg->NvRamBlockId;
            Dcm_SignalBufferContext.NvMService = DCM_DIDNVMOPERATION_WRITENVMDATA;

#if (DCM_ASYNC_DID_SERVICES == STD_ON)
            /* LEAVE critical section */
            SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
#endif

#if (DCM_DEV_ERROR_DETECT == STD_ON)
            if (RetVal != E_OK)
            {
              if (RetVal == E_NOT_OK)
              {
                DCM_DET_REPORT_ERROR(DCM_SVCID_NVMWRITEDATA, DCM_E_NVM_CANCEL_JOBS_FAILED);
              }
              else
              {
                DCM_DET_REPORT_ERROR(DCM_SVCID_NVMCANCELJOBS, DCM_E_INTERFACE_RETURN_VALUE);
              }
            }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */
          }
        }
      }
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      else if (RetVal == E_NOT_OK)
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMWRITEDATA, DCM_E_NVM_WRITE_FAIL);
      }
      else
      {
        DCM_DET_REPORT_ERROR(DCM_SVCID_NVMGETERRORSTATUS, DCM_E_INTERFACE_RETURN_VALUE);
      }
#endif /* #if (DCM_DEV_ERROR_DETECT == STD_ON) */

      break;

    default:
    /* do nothing */
      break;
  }

  /* if the write operation successfully completed or there is any error while writing to NVM */
  if ((RetVal != DCM_E_PENDING) && (NvmOperationPending == FALSE))
  {
    /* Lock the NVRAM block */
    NvM_SetBlockLockStatus(didDataCfg->NvRamBlockId, TRUE);
  }

  /* replace all errors different from E_OK, E_NOT_OK and DCM_E_PENDING with E_NOT_OK
     in order to preserve the function interface */
  if ((RetVal != E_OK) && (RetVal != DCM_E_PENDING))
  {
    RetVal = E_NOT_OK;
  }

  DBG_DCM_DSPINTERNAL_WRITENVMDATA_EXIT(RetVal,DCM_INST(instIdx),didDataCfg,signalBuffer);
  return RetVal;
}
#endif /* #if(DCM_WRITE_DID_BLOCK_ID_CONFIGURED == STD_ON) */
#endif /* #if(DCM_DSP_USE_SERVICE_0X2E == STD_ON) */

#if (((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
      (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) && (DCM_ENDIANNESS_CONVERSION == STD_ON))
/* the Endianness conversion of currently copying data */
STATIC FUNC(void, DCM_CODE) Dcm_DspInternal_Endianness_Conversion(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) inBuffer,
  Dcm_DidDataByteType dataType)
{
  uint16_least i;
  DBG_DCM_DSPINTERNAL_ENDIANNESS_CONVERSION_ENTRY(inBuffer,dataType);

  switch(dataType)
  {
    /* if the data type is SINT16 or UINT16 */
    case DCM_TYPE_SINT16:
    case DCM_TYPE_UINT16:
      for (i = 0U; i < DCM_DATA_MAX_SIZE; i += 2U)
      {
        /* the assignment is byte-wise, as we don't rely on a
         * specific alignment */
        const uint8 tmpByte = inBuffer[i];

        inBuffer[i] = inBuffer[i+1];
        inBuffer[i+1] = tmpByte;
      }
      break;

    /* if the data type is SINT32 ot UINT32 */
    case DCM_TYPE_SINT32:
    case DCM_TYPE_UINT32:
      for (i = 0U; i < DCM_DATA_MAX_SIZE; i += 4U)
      {
        /* the assignment is byte-wise, as we don't rely on a
         * specific alignment */
        uint8 tmpByte;

        tmpByte = inBuffer[i+3];
        inBuffer[i+3] = inBuffer[i];
        inBuffer[i] = tmpByte;

        tmpByte = inBuffer[i+2];
        inBuffer[i+2] = inBuffer[i+1];
        inBuffer[i+1] = tmpByte;
      }
      break;

    default:
      /* do nothing */
      break;
  }

  DBG_DCM_DSPINTERNAL_ENDIANNESS_CONVERSION_EXIT(inBuffer,dataType);
}

#endif /* #if (((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X22 == STD_ON)) && (DCM_ENDIANNESS_CONVERSION == STD_ON)) */

#if(DCM_0X34_SVC_ENABLED == STD_ON)
/* This is the generic service handler for UDS service 0x34 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestDownloadHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REQUESTDOWNLOADHANDLER_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_RequestDownload_SvcStart(OpStatus, pMsgContext);
      break;

    /* consecutive call after the function retuned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_RequestDownload_SvcCont(OpStatus, pMsgContext);
      break;

    /* Cancel the ongoing service processing */
    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_RequestDownload_SvcCont(OpStatus, pMsgContext);
      break;
    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_REQUESTDOWNLOADHANDLER_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestDownload_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Std_ReturnType retVal = E_NOT_OK;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);
  /* holds format Identifier from the request*/
  uint8 formatId = pMsgContext->reqData[0];

  DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCSTART_ENTRY(OpStatus,pMsgContext);

#if (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON)
  /* Verify that the AddressLengthFormatIdentifier is valid or not */
  retVal = Dcm_DspInternal_AddressLengthAndFormat_Verification(pMsgContext->reqData[1]);
  if(retVal != E_OK)
  {
    /* Send Nrc 0x31 */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
#endif
  {
    /* holds the number of bytes occupied by memoryAddress[] in the request*/
    uint8 memAddBytes = (pMsgContext->reqData[1]) & DCM_MASK_NIBBLE ;
    /* holds the number of bytes occupied by memorySize[] in the request*/
    uint8 memSizeBytes = (uint8)((pMsgContext->reqData[1]) >> DCM_NIBBLE_BITS);

    /*If already registered with an upload or download request*/
    if(pDataTranContextType->TransState != DCM_TRANSFER_IDLE)
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
      serviceProcessStatus = DCM_E_DONE;
    }
    /*The data recieved should be dataFormatIdentifier,addressAndLengthFormatIdentifier ->(2bytes)
      memoryAddress[], memorySize[] -> (memAddBytes + memSizeBytes bytes) */
    else if ((pMsgContext->reqDataLen) != (PduLengthType)(2UL + memAddBytes + memSizeBytes))
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      serviceProcessStatus = DCM_E_DONE;
    }
    else
    {
      /*Holds address field from request*/
      uint32 memAddress = 0U;
      /*Holds memory size field from request*/
      uint32 memSize = 0U;
      Std_ReturnType retGetMemoryAddressAndSize;
      Dcm_NegativeResponseCodeType nrc = E_OK;

      /* Get the Memory address and the size of memory to be read */
      retGetMemoryAddressAndSize =
              Dcm_DspInternal_GetMemoryAddressAndSize(&(pMsgContext->reqData[1]),
                                                      memAddBytes, memSizeBytes,
                                                      &memAddress, &memSize);
      if( retGetMemoryAddressAndSize == E_OK )
      {
        /*Memory size should be greater than zero.*/
        if(memSize == 0U)
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
        else
        {
          /*id of the buffer used for reception*/
          uint8 rxBuffId = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].rxBufferId;
          /*size of Rx buffer*/
          uint32 buffSize = Dcm_BufferConfig[rxBuffId].size;
          /*Response data contains 'lengthFormatIdentifier' .Its highest nibble contains
          the number of bytes in the following field (maxNumberOfBlockLength).
          Loweset nibble is zero*/
          uint8_least blockBytes = DCM_MAX_ADDRESS_BYTES;

          pMsgContext->resData[0] = (uint8)(blockBytes << DCM_NIBBLE_BITS);
          pMsgContext->resDataLen++;
          /*Assembling maxNumberOfBlockLength[] in the response.*/
          while(blockBytes > 0U)
          {
            pMsgContext->resData[blockBytes] = (uint8)(buffSize & DCM_MASK_BYTE);
            pMsgContext->resDataLen++;
            buffSize = (uint32)buffSize >> DCM_BYTE_BITS;
            blockBytes--;
          }

          /*Storing the memory address to download in the transfer request*/
          pDataTranContextType->MemAddres = memAddress;
          /*Storing the size of memory to be downloaded in the transfer request*/
          pDataTranContextType->MemSize = memSize;
          retVal = Dcm_ProcessRequestDownload(
                                               OpStatus,
                                               formatId,
                                               memAddress,
                                               memSize,
                                               Dcm_BufferConfig[rxBuffId].size,
                                               &nrc
                                             );
          switch(retVal)
          {
            case E_OK:
              /*Registering Download Request*/
              pDataTranContextType->TransState = DCM_TRANSFER_DOWNLOAD;
              /*The blockSequenceCounter shall be initialized to one, when receiving a
                RequestDownload */
              pDataTranContextType->BlockSequenceCounter = 1U;
              /* Setting the total data transfered to zero*/
              pDataTranContextType->MemTransfered = 0U;
              serviceProcessStatus = DCM_E_DONE;
              break;

            case E_NOT_OK:
              Dcm_ExternalSetNegResponse(pMsgContext, nrc);
              serviceProcessStatus = DCM_E_DONE;
              break;

            case DCM_E_PENDING:
              serviceProcessStatus = DCM_E_PENDING;
              break;

            default:
              serviceProcessStatus = DCM_E_DONE;
    #if (DCM_DEV_ERROR_DETECT == STD_ON)
              DCM_DET_REPORT_ERROR(DCM_SVCID_REQUESTDOWNLOAD, DCM_E_INTERFACE_RETURN_VALUE);
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    #endif
              break;
          }
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
      }
    }
  }

  DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestDownload_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);
  Dcm_NegativeResponseCodeType nrc = E_OK;
  Std_ReturnType retVal;
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCCONT_ENTRY(OpStatus,pMsgContext);

  retVal = Dcm_ProcessRequestDownload(
                                       OpStatus,
                                       0U,
                                       0U,
                                       0U,
                                       0U,
                                       &nrc
                                     );
  if( OpStatus != DCM_CANCEL)
  {
    switch(retVal)
    {
      case E_OK:
        /*Registering Download Request*/
        pDataTranContextType->TransState = DCM_TRANSFER_DOWNLOAD;
        /*The blockSequenceCounter shall be initialized to one, when receiving a RequestDownload */
        pDataTranContextType->BlockSequenceCounter = 1U;
        /* Setting the total data transfered to zero*/
        pDataTranContextType->MemTransfered = 0U;
        serviceProcessStatus = DCM_E_DONE;
        break;

      case E_NOT_OK:
        Dcm_ExternalSetNegResponse(pMsgContext, nrc);
        serviceProcessStatus = DCM_E_DONE;
        break;

      case DCM_E_PENDING:
        serviceProcessStatus = DCM_E_PENDING;
        break;

      default:
        serviceProcessStatus = DCM_E_DONE;
  #if (DCM_DEV_ERROR_DETECT == STD_ON)
            DCM_DET_REPORT_ERROR(DCM_SVCID_REQUESTDOWNLOAD, DCM_E_INTERFACE_RETURN_VALUE);
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  #endif
        break;
    }
  }
  else
  {
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_REQUESTDOWNLOAD_SVCCONT_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

#endif /* #if(DCM_0X34_SVC_ENABLED == STD_ON) */

#if(DCM_0X35_SVC_ENABLED == STD_ON)
/* This is the generic service handler for UDS service 0x35 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestUploadHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REQUESTUPLOADHANDLER_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_RequestUpload_SvcStart(OpStatus, pMsgContext);
      break;

    /* consecutive call after the function retuned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_RequestUpload_SvcCont(OpStatus, pMsgContext);
      break;

    /* Cancel the ongoing service processing */
    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_RequestUpload_SvcCont(OpStatus, pMsgContext);
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_REQUESTUPLOADHANDLER_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestUpload_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Std_ReturnType retVal = E_NOT_OK;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);
  /* holds format Identifier from the request*/
  uint8 formatId = pMsgContext->reqData[0];

  DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCSTART_ENTRY(OpStatus,pMsgContext);

#if (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON)

  /* Verify that the AddressLengthFormatIdentifier is valid or not */
  retVal = Dcm_DspInternal_AddressLengthAndFormat_Verification(pMsgContext->reqData[1]);

  if(retVal != E_OK)
  {
    /* Send Nrc 0x31 */
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
#endif
  {
    /* holds the number of bytes occupied by memoryAddress[] in the request*/
    uint8 memAddBytes = (pMsgContext->reqData[1]) & DCM_MASK_NIBBLE ;
    /* holds the number of bytes occupied by memorySize[] in the request*/
    uint8 memSizeBytes = (uint8)((pMsgContext->reqData[1]) >> DCM_NIBBLE_BITS);

    /*If already registered with an upload or download request*/
    if(pDataTranContextType->TransState != DCM_TRANSFER_IDLE)
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
      serviceProcessStatus = DCM_E_DONE;
    }
    /*The data recieved should be dataFormatIdentifier,addressAndLengthFormatIdentifier ->(2bytes)
      memoryAddress[], memorySize[] -> (memAddBytes + memSizeBytes bytes) */
    else if ((pMsgContext->reqDataLen) != ((PduLengthType)memAddBytes +  memSizeBytes + 2U))
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      serviceProcessStatus = DCM_E_DONE;
    }
    else
    {
      /*Holds address field from request*/
      uint32 memAddress = 0U;
      /*Holds memory size field from request*/
      uint32 memSize = 0U;
      Dcm_NegativeResponseCodeType nrc = E_OK;
      Std_ReturnType retGetMemoryAddressAndSize;

      /* Get the Memory address and the size of memory to be read */
      retGetMemoryAddressAndSize =
            Dcm_DspInternal_GetMemoryAddressAndSize(&(pMsgContext->reqData[1]),
                                                    memAddBytes, memSizeBytes,
                                                    &memAddress, &memSize);
      if( retGetMemoryAddressAndSize == E_OK )
      {
        /*Memory size should be greater than zero.*/
        if(memSize == 0U)
        {
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
        else
        {
          /*size of Tx buffer*/
          uint32 txbuffSize = Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].size;
          uint32 blockLength = 0U;
          /*Response data contains 'lengthFormatIdentifier'.
           Its highest nibble contains the number of bytes in the following
           field (maxNumberOfBlockLength).Loweset nibble is zero*/
          uint8_least blockBytes = DCM_MAX_ADDRESS_BYTES;

          if((memSize + 2U) < txbuffSize)
          {
            blockLength = memSize + 2U;
          }
          else
          {
            blockLength = txbuffSize;
          }
          pMsgContext->resData[0] = (uint8)(blockBytes << DCM_NIBBLE_BITS);
          pMsgContext->resDataLen++;
          /*Assembling maxNumberOfBlockLength[] in the response.*/
          while(blockBytes > 0U)
          {
            pMsgContext->resData[blockBytes] = (uint8)(blockLength & DCM_MASK_BYTE);
            pMsgContext->resDataLen++;
            blockLength = (uint32)blockLength >> DCM_BYTE_BITS;
            blockBytes--;
          }

          /*Storing the memory address to download in the transfer request*/
          pDataTranContextType->MemAddres = memAddress;
          /*Storing the size of memory to be downloaded in the transfer request*/
          pDataTranContextType->MemSize = memSize;
          retVal = Dcm_ProcessRequestUpload(
                                             OpStatus,
                                             formatId,
                                             memAddress,
                                             memSize,
                                             &nrc
                                           );
          switch(retVal)
          {
            case E_OK:
              /*Registering Upload Request*/
              pDataTranContextType->TransState = DCM_TRANSFER_UPLOAD;
              /* The blockSequenceCounter shall be initialized to one,
                 when receiving a RequestUpload */
              pDataTranContextType->BlockSequenceCounter = 1U;
              /* Setting the total data transfered to zero*/
              pDataTranContextType->MemTransfered = 0U;
              serviceProcessStatus = DCM_E_DONE;
              break;

            case E_NOT_OK:
              Dcm_ExternalSetNegResponse(pMsgContext, nrc);
              serviceProcessStatus = DCM_E_DONE;
              break;

            case DCM_E_PENDING:
              serviceProcessStatus = DCM_E_PENDING;
              break;

            default:
              serviceProcessStatus = DCM_E_DONE;
#if (DCM_DEV_ERROR_DETECT == STD_ON)
              DCM_DET_REPORT_ERROR(DCM_SVCID_REQUESTUPLOAD, DCM_E_INTERFACE_RETURN_VALUE);
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
              break;
          }
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
        serviceProcessStatus = DCM_E_DONE;
      }
    }
  }

  DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestUpload_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);
  Dcm_NegativeResponseCodeType nrc = E_OK;
  Std_ReturnType retVal;
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REQUESTUPLOAD_SVCCONT_ENTRY(OpStatus,pMsgContext);

  retVal = Dcm_ProcessRequestUpload(
                                     OpStatus,
                                     0U,
                                     0U,
                                     0U,
                                     &nrc
                                   );
  if(OpStatus != DCM_CANCEL)
  {
    switch(retVal)
    {
      case E_OK:
        /*Registering Upload Request*/
        pDataTranContextType->TransState = DCM_TRANSFER_UPLOAD;
        /*The blockSequenceCounter shall be initialized to one, when receiving a RequestUpload */
        pDataTranContextType->BlockSequenceCounter = 1U;
        /*Setting the total data transfered to zero*/
        pDataTranContextType->MemTransfered = 0U;
        serviceProcessStatus = DCM_E_DONE;
        break;

      case E_NOT_OK:
        Dcm_ExternalSetNegResponse(pMsgContext, nrc);
        serviceProcessStatus = DCM_E_DONE;
        break;

      case DCM_E_PENDING:
        serviceProcessStatus = DCM_E_PENDING;
        break;

      default:
        serviceProcessStatus = DCM_E_DONE;
        break;
    }
  }
  else
  {
    serviceProcessStatus = DCM_E_DONE;
  }
  return serviceProcessStatus;
}

#endif /* #if(DCM_0X35_SVC_ENABLED == STD_ON) */

#if(DCM_0X36_SVC_ENABLED == STD_ON)
/* This is the generic service handler for UDS service 0x36 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransferDataHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_TRANSFERDATAHANDLER_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_TransferData_SvcStart(OpStatus, pMsgContext);
      break;

    /* Sub-sequent call to the service function after FORCE_RCRRP */
    case DCM_FORCE_RCRRP_OK:
    /* second call when PENDING is returned */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_TransferData_SvcCont(OpStatus, pMsgContext);
      break;
    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_TransferData_SvcCont(OpStatus, pMsgContext);
      break;
    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_TRANSFERDATAHANDLER_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransferData_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCSTART_ENTRY(OpStatus,pMsgContext);

  if ((pMsgContext->reqDataLen) == 0U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    uint8 blockSeqCounter = pMsgContext->reqData[0];
    /*If does not registered with an upload or download request*/
    if((pDataTranContextType->TransState == DCM_TRANSFER_IDLE) ||
    /*If already transfered the data determined by the memorySize parameter the request 0x34/0x35*/
           (pDataTranContextType->MemTransfered == pDataTranContextType->MemSize))
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
      serviceProcessStatus = DCM_E_DONE;
    }
    /*For the first transferRequest the block sequence counter should be one*/
    else if( ((pDataTranContextType->MemTransfered == 0U) && (blockSeqCounter != 1U)) ||
    /*The request with repeated block sequence count is also supported.
      So block sequence counter shall be equal to the internal count or
      shall be one less than the internal count */
             ((blockSeqCounter != pDataTranContextType->BlockSequenceCounter) &&
             (blockSeqCounter != (pDataTranContextType->BlockSequenceCounter - 1U))) )
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_WRONGBLOCKSEQUENCECOUNTER);
      serviceProcessStatus = DCM_E_DONE;
    }
    else
    {
      if(pDataTranContextType->TransState == DCM_TRANSFER_DOWNLOAD)
      {
        serviceProcessStatus = Dcm_DspInternal_DownloadTransferData(pMsgContext,
          pDataTranContextType, OpStatus);
      }
      else
      {
        serviceProcessStatus = Dcm_DspInternal_UploadTransferData(pMsgContext,
          pDataTranContextType, OpStatus);
      }
    }
  }

  DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransferData_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCCONT_ENTRY(OpStatus,pMsgContext);

  if(pDataTranContextType->TransState == DCM_TRANSFER_DOWNLOAD)
  {
    Dcm_ReturnWriteMemoryType retVal = Dcm_WriteMemory(
                                                        OpStatus,
                                                        0U,
                                                        0U,
                                                        0U,
                                                        &(pMsgContext->reqData[1])
                                                      );
    if(OpStatus != DCM_CANCEL)
    {
      switch (retVal)
      {
        case DCM_WRITE_OK:
          /*Data downloaded succesfully. So update internal record of Data written*/
          pDataTranContextType->MemTransfered += pDataTranContextType->CurrMemTransfered;
          /*Data downloaded succesfully.Increment block
          sequence counter to recieve the next message*/
          pDataTranContextType->BlockSequenceCounter++;
          serviceProcessStatus = DCM_E_DONE;
          break;

        case DCM_WRITE_PENDING:
          serviceProcessStatus = DCM_E_PENDING;
          break;

        case DCM_WRITE_FORCE_RCRRP:
          serviceProcessStatus = DCM_E_FORCE_RCRRP;
          break;

        case DCM_WRITE_FAILED:
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
          serviceProcessStatus = DCM_E_DONE;
          break;

        default:
  #if (DCM_DEV_ERROR_DETECT == STD_ON)
          DCM_DET_REPORT_ERROR(DCM_SVCID_WRITEMEMORY, DCM_E_INTERFACE_RETURN_VALUE);
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  #endif
          serviceProcessStatus = DCM_E_DONE;
          break;
      }
    }
    else
    {
      serviceProcessStatus = DCM_E_DONE;
    }
  }
  else
  {
    Dcm_ReturnReadMemoryType retVal =
    Dcm_ReadMemory(
                    OpStatus,
                    0U,
                    0U,
                    0U,
                    &(pMsgContext->resData[1])
                  );

    if(OpStatus != DCM_CANCEL)
    {
      switch (retVal)
      {
        case DCM_READ_OK:
          /*Data uploaded succesfully. So update internal record of Data uploaded*/
          pDataTranContextType->MemTransfered += pDataTranContextType->CurrMemTransfered;
          /*Data uploaded succesfully.Increment block
          sequence counter to recieve the next message*/
          pDataTranContextType->BlockSequenceCounter++;
          /*Updating the response data filled*/
          pMsgContext->resDataLen += (PduLengthType)pDataTranContextType->CurrMemTransfered;

          serviceProcessStatus = DCM_E_DONE;
          break;

        case DCM_READ_PENDING:
          serviceProcessStatus = DCM_E_PENDING;
          break;

        case DCM_READ_FORCE_RCRRP:
          serviceProcessStatus = DCM_E_FORCE_RCRRP;
          break;

        case DCM_READ_FAILED:
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
          serviceProcessStatus = DCM_E_DONE;
          break;

        default:
  #if (DCM_DEV_ERROR_DETECT == STD_ON)
          DCM_DET_REPORT_ERROR(DCM_SVCID_READMEMORY, DCM_E_INTERFACE_RETURN_VALUE);
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
  #endif
          serviceProcessStatus = DCM_E_DONE;
          break;
      }
    }
    else
    {
      serviceProcessStatus = DCM_E_DONE;
    }
  }

  DBG_DCM_DSPINTERNAL_TRANSFERDATA_SVCCONT_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DownloadTransferData(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pTranContext,
  Dcm_OpStatusType OpStatus)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_DOWNLOADTRANSFERDATA_ENTRY(pMsgContext,pTranContext,OpStatus);

  /* The first data will be an echo of blocksequence counter value recieved.*/
  pMsgContext->resData[0] = pMsgContext->reqData[0];
  pMsgContext->resDataLen++;
  /* Updating the data to be transferred in the current request. Needs to keep this to
     update 'MemTransfered' after data transfered*/
  pTranContext->CurrMemTransfered = ((uint32)pMsgContext->reqDataLen - 1U);

  /*Call write memory only if block sequence count recieved is equal to the internal
    BlockSequenceCounter. If the request is having block sequence count of previous,
    send positive respons without writing to memory.*/
  if (pMsgContext->reqData[0] == pTranContext->BlockSequenceCounter)
  {
    /*If the data to be transfered exeeds memorySize parameter from the requestDownload (0x34)*/
    if((((uint32)pMsgContext->reqDataLen - 1U) +
              pTranContext->MemTransfered) > pTranContext->MemSize)
    {
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
      serviceProcessStatus = DCM_E_DONE;
    }
    else
    {
      Dcm_ReturnWriteMemoryType retVal;
      retVal = Dcm_WriteMemory(
                                OpStatus,
                                0U,
                                pTranContext->MemAddres + pTranContext->MemTransfered,
                                pTranContext->CurrMemTransfered,
                                &(pMsgContext->reqData[1])
                              );
      switch (retVal)
      {
        case DCM_WRITE_OK:
          /*Data downloaded succesfully. So update internal record of Data written*/
          pTranContext->MemTransfered += pTranContext->CurrMemTransfered;
          /*Data downloaded succesfully.Increment block sequence counter to recieve next message*/
          pTranContext->BlockSequenceCounter++;
          serviceProcessStatus = DCM_E_DONE;
          break;

        case DCM_WRITE_PENDING:
          serviceProcessStatus = DCM_E_PENDING;
          break;

        case DCM_WRITE_FORCE_RCRRP:
          serviceProcessStatus = DCM_E_FORCE_RCRRP;
          break;

        case DCM_WRITE_FAILED:
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
          serviceProcessStatus = DCM_E_DONE;
          break;

        default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
          DCM_DET_REPORT_ERROR(DCM_SVCID_WRITEMEMORY, DCM_E_INTERFACE_RETURN_VALUE);
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
          serviceProcessStatus = DCM_E_DONE;
          break;
      }
    }
  }
  else
  {
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_DOWNLOADTRANSFERDATA_EXIT(serviceProcessStatus,pMsgContext,
                                                pTranContext,OpStatus);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_UploadTransferData(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pTranContext,
  Dcm_OpStatusType OpStatus)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /*size of Tx buffer*/
  uint32 txbuffSize = Dcm_BufferConfig[DCM_HSM_CONFIG(instIdx).txBufferId].size;
  Dcm_ReturnReadMemoryType retVal;

  DBG_DCM_DSPINTERNAL_UPLOADTRANSFERDATA_ENTRY(pMsgContext,pTranContext,OpStatus);

  /* The first data will be an echo of blocksequence counter value recieved.*/
  pMsgContext->resData[0] = pMsgContext->reqData[0];
  pMsgContext->resDataLen++;
  /*If request is with the previous block sequence count*/
  if (pMsgContext->reqData[0] == (pTranContext->BlockSequenceCounter -1U))
  {
    pTranContext->BlockSequenceCounter = pMsgContext->reqData[0];
    /*Subtracting the memory transferd in the previous request to the total transfered.
      Since the same is expected in the current request */
    pTranContext->MemTransfered -= pTranContext->CurrMemTransfered;
  }
  /* Updating the data to be transferred in the current request. Needs to keep this to
  update 'MemTransfered' after data transfered*/

  if((txbuffSize - 2U) <= (pTranContext->MemSize - pTranContext->MemTransfered))
  {
    pTranContext->CurrMemTransfered = (txbuffSize - 2U);
  }
  else
  {
    pTranContext->CurrMemTransfered = (pTranContext->MemSize -
                                                              pTranContext->MemTransfered);
  }

  retVal = Dcm_ReadMemory(
                            OpStatus,
                            0U,
                            pTranContext->MemAddres + pTranContext->MemTransfered,
                            pTranContext->CurrMemTransfered,
                            &(pMsgContext->resData[1])
                          );
  switch (retVal)
  {
    case DCM_READ_OK:
      /*Data uploaded succesfully. So update internal record of Data uploaded*/
      pTranContext->MemTransfered += pTranContext->CurrMemTransfered;
      /*Data uploaded succesfully.Increment block sequence counter to recieve the next message*/
      pTranContext->BlockSequenceCounter++;
      /*Updating the response data filled*/
      pMsgContext->resDataLen += (PduLengthType)pTranContext->CurrMemTransfered;
      serviceProcessStatus = DCM_E_DONE;
      break;

    case DCM_READ_PENDING:
      serviceProcessStatus = DCM_E_PENDING;
      break;

    case DCM_READ_FORCE_RCRRP:
      serviceProcessStatus = DCM_E_FORCE_RCRRP;
      break;

    case DCM_READ_FAILED:
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      DCM_DET_REPORT_ERROR(DCM_SVCID_READMEMORY, DCM_E_INTERFACE_RETURN_VALUE);
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_UPLOADTRANSFERDATA_EXIT(serviceProcessStatus,pMsgContext,
                                              pTranContext,OpStatus);
  return serviceProcessStatus;
}

#endif /* #if(DCM_0X36_SVC_ENABLED == STD_ON) */

#if(DCM_0X37_SVC_ENABLED == STD_ON)
/* This is the generic service handler for UDS service 0x37 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestTransferExitHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXITHANDLER_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_RequestTransferExit_SvcStart(OpStatus, pMsgContext);
      break;

    /* consecutive call after the function retuned PENDING before */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_RequestTransferExit_SvcCont(OpStatus, pMsgContext);
      break;

    /* Cancel the ongoing service processing */
    case DCM_CANCEL:
      serviceProcessStatus = Dcm_DspInternal_RequestTransferExit_SvcCont(OpStatus, pMsgContext);
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXITHANDLER_SVCH_EXIT(serviceProcessStatus,
                                                           OpStatus,
                                                           pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestTransferExit_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
  )
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);

  DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCSTART_ENTRY(OpStatus,pMsgContext);

  /* Only the service id is expected in the request. The other parameters are not supported */
  if ((pMsgContext->reqDataLen) != 0U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  /* If an upload or download request is not active */
  else if(pDataTranContextType->TransState == DCM_TRANSFER_IDLE)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    serviceProcessStatus = Dcm_DspInternal_RequestTransferExit_SvcCont(OpStatus, pMsgContext);
  }

  DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestTransferExit_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
  )
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Dcm_NegativeResponseCodeType nrc = E_OK;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* holds the instance id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* holds the context information transfer services */
  P2VAR(Dcm_DataTransferType, AUTOMATIC, DCM_VAR) pDataTranContextType =
                                                    &DCM_DATA_TRANSFER_CONTEXT(instIdx);

  Std_ReturnType retVal = Dcm_ProcessRequestTransferExit(OpStatus, NULL_PTR, 0U, &nrc);

  DBG_DCM_DSPINTERNAL_REQUESTTRANSFEREXIT_SVCCONT_ENTRY(OpStatus,pMsgContext);

  if(OpStatus != DCM_CANCEL)
  {
    switch(retVal)
    {
      case E_OK:
        /*Registering Transfer Exit Request*/
        pDataTranContextType->TransState = DCM_TRANSFER_IDLE;
        serviceProcessStatus = DCM_E_DONE;
        break;

      case E_NOT_OK:
        Dcm_ExternalSetNegResponse(pMsgContext, nrc);
        serviceProcessStatus = DCM_E_DONE;
        break;

      case DCM_E_PENDING:
        serviceProcessStatus = DCM_E_PENDING;
        break;

      default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        DCM_DET_REPORT_ERROR(DCM_SVCID_REQUESTTRANSFEREXIT, DCM_E_INTERFACE_RETURN_VALUE);
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
        serviceProcessStatus = DCM_E_DONE;
        break;
    }
  }
  else
  {
    serviceProcessStatus = DCM_E_DONE;
  }
  return serviceProcessStatus;
}
#endif /* #if(DCM_0X37_SVC_ENABLED == STD_ON) */

#if(DCM_0X87_SVC_ENABLED == STD_ON)
/* This is the generic service handler for UDS service 0x87 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_LinkControlHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_LINKCONTROLHANDLER_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* first call of service function */
    case DCM_INITIAL:
      serviceProcessStatus = Dcm_DspInternal_LinkControl_SvcStart(OpStatus, pMsgContext);
      break;
   /* second call when PENDING is returned */
    case DCM_PENDING:
      serviceProcessStatus = Dcm_DspInternal_LinkControl_SvcCont(OpStatus, pMsgContext);
      break;
    /* communicate to callout of service cancellation */
    case DCM_CANCEL:
      (void)Dcm_LinkControl( OpStatus, 0U, NULL_PTR, NULL_PTR);
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_LINKCONTROLHANDLER_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_LinkControl_SvcStart(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
  )
{
  /* loop variable */
  uint8_least i;
#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);
  /* get configuration for current service table */
  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
    = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];

  /* get corresponding sub-service array configuration */
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
    = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;

  /* get number of subservices */
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;

  /* Holds processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCSTART_ENTRY(OpStatus,pMsgContext);

  TS_PARAM_UNUSED(OpStatus);

  /* To check whether subfunction is available or not */
  if (pMsgContext->reqDataLen > 0U)
  {
    /* copy subfunction value to response buffer */
    pMsgContext->resData[0] = curHsmInfo->subServiceId;
    pMsgContext->resDataLen = 1U;

    for (i = 0U; i < numSubServ; i++)
    {
      /* Search for the index in subservices table for the requested subservice */
      if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
      {
        /* assign the data from msgcontext for service to that of sub-function.*/
        /* decrement the reqData length as sub-function is removed */
        pMsgContext->reqDataLen = pMsgContext->reqDataLen - 1U;

        if (pMsgContext->reqDataLen == 0U)
        {
          /* as no parameters exist after the sub-function, point the reqData to NULL */
          pMsgContext->reqData = NULL_PTR;
        }
        else
        {
          /* set request data pointer to received data without service and subservice Ids */
          pMsgContext->reqData = &pMsgContext->reqData[1];
        }

        if (curSsConfig[i].IntSrvHandler != NULL_PTR)
        {
          /* Call internal sub-service handler*/
          serviceProcessStatus = curSsConfig[i].IntSrvHandler(DCM_INITIAL, pMsgContext);
        }
        else
        {
          /* Call External sub-service handler*/
          serviceProcessStatus = curSsConfig[i].ExtSrvHandler(DCM_INITIAL, pMsgContext);

          /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
          if (serviceProcessStatus == E_OK)
          {
            serviceProcessStatus = DCM_E_DONE;
          }
        }
      break;
      }
    }
  }
  /* subfunction is not available */
  else
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }

  DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCSTART_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_LinkControl_SvcCont(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* holds the processing status of the service function */
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Dcm_NegativeResponseCodeType nrc = E_OK;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* Get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  Std_ReturnType retVal;

  CONSTP2CONST(Dcm_SidTabConfigType, AUTOMATIC, DCM_CONST) curSidTabConfig
          = &Dcm_SidTabConfig[DCM_HSM_CONFIG(instIdx).sidTabId];
  CONSTP2CONST(Dcm_SubSidTabEntryConfigType, AUTOMATIC, DCM_CONST) curSsConfig
          = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).SubServices;
  uint8 numSubServ = (curSidTabConfig->Entries[curHsmInfo->sidTabEntryInd]).NumSubServices;
  uint8 i;

  TS_PARAM_UNUSED(OpStatus);

  DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCCONT_ENTRY(OpStatus,pMsgContext);

  for (i = 0U; i < numSubServ; i++)
  {
    if (curSsConfig[i].SubServiceId == curHsmInfo->subServiceId)
    /* Search for the index in subservices table for the requested subservice */
    {
      if (curSsConfig[i].IntSrvHandler != NULL_PTR)
      {
          retVal = Dcm_LinkControl(
                                    OpStatus,
                                    0U,
                                    NULL_PTR,
                                    &nrc
                                  );
          switch (retVal)
         {
           case E_OK:
              if((curHsmInfo->subServiceId == 1U) || (curHsmInfo->subServiceId == 2U))
              {
               Dcm_DspLinkControlRequestStatus = TRUE;
              }
              else
              {
                Dcm_DspLinkControlRequestStatus = FALSE;
              }
              /* Assemble positive response for LinkControl request */
              pMsgContext->resDataLen = (PduLengthType)1U;
              pMsgContext->resData[0] = curHsmInfo->subServiceId;
              serviceProcessStatus = DCM_E_DONE;
              break;

            case DCM_E_PENDING:
              serviceProcessStatus = DCM_E_PENDING;
              break;

            /* Incase of validation of linkBaudrateRecord nrc will
            be updated with requestOutOfRange */
            case E_NOT_OK:
              /* nrc updated with DCM_E_CONDITIONSNOTCORRECT from Dcm_LinkControl callout */
              Dcm_ExternalSetNegResponse(pMsgContext, nrc);
              serviceProcessStatus = DCM_E_DONE;
              break;

            default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
              DCM_DET_REPORT_ERROR(DCM_SVCID_LINKCONTROL, DCM_E_INTERFACE_RETURN_VALUE);
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
              serviceProcessStatus = DCM_E_DONE;
              break;
          }
      }
      else
      {
        serviceProcessStatus = curSsConfig[i].ExtSrvHandler(OpStatus, pMsgContext);

        /* Sub-service handlers return E_OK or E_NOT_OK, so we must convert to DCM_E_DONE */
        if (serviceProcessStatus == E_OK)
        {
          serviceProcessStatus = DCM_E_DONE;
        }
      }
    break;
    }
  }

  DBG_DCM_DSPINTERNAL_LINKCONTROL_SVCCONT_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

#if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_FixedBaudrateVerification_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  uint8 idx = 0U;
  /* Holds the baud rate value to be filled for the callout */
  uint8 baudrateRecord[3];
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_FIXEDBAUDRATEVERIFICATION_SSVCH_ENTRY(OpStatus,pMsgContext);

  /* Request Length Verification */
  if (pMsgContext->reqDataLen != 1U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  /* Validation of baudrateIdentifier */
  /* Deviation MISRA-2 */
  else if ( (pMsgContext->reqData[0] < 0x01U) || ((pMsgContext->reqData[0] > 0x05U) &&
            (pMsgContext->reqData[0] < 0x10U)) || (pMsgContext->reqData[0] > 0x13U) )
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    if(pMsgContext->reqData[0] <= 5U)
    {
      idx = pMsgContext->reqData[0] - 1U;
    }
    else
    {
      idx = pMsgContext->reqData[0] - 0x0BU;
    }
    if (pMsgContext->reqData[0] == Dcm_LinkControlBaudrateTable[idx].baudrateIdentifier)
    {
      /* Fetch baudrate from Baudrate table with baudrateIdentifier as index */
      baudrateRecord[0] = Dcm_LinkControlBaudrateTable[idx].linkBaudrateRecord[0];
      baudrateRecord[1] = Dcm_LinkControlBaudrateTable[idx].linkBaudrateRecord[1];
      baudrateRecord[2] = Dcm_LinkControlBaudrateTable[idx].linkBaudrateRecord[2];
    }

    serviceProcessStatus = Dcm_DspInternal_LinkControl_Execution(OpStatus, baudrateRecord,
                                                                 pMsgContext);
  }

  DBG_DCM_DSPINTERNAL_FIXEDBAUDRATEVERIFICATION_SSVCH_EXIT(serviceProcessStatus,
                                                           OpStatus,
                                                           pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON) */

#if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SpecificBaudrateVerification_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* Holds the baud rate value to be filled for the callout */
  uint8 baudrateRecord[3];
  Std_ReturnType serviceProcessStatus;

  DBG_DCM_DSPINTERNAL_SPECIFICBAUDRATEVERIFICATION_SSVCH_ENTRY(OpStatus,pMsgContext);

  /* Request Length Verification */
  if (pMsgContext->reqDataLen != 3U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    baudrateRecord[0] = pMsgContext->reqData[0];
    baudrateRecord[1] = pMsgContext->reqData[1];
    baudrateRecord[2] = pMsgContext->reqData[2];

    serviceProcessStatus = Dcm_DspInternal_LinkControl_Execution(OpStatus, baudrateRecord,
                                                               pMsgContext);
  }

  DBG_DCM_DSPINTERNAL_SPECIFICBAUDRATEVERIFICATION_SSVCH_EXIT(serviceProcessStatus,
                                                              OpStatus,
                                                              pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON) */

#if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransitionBaudrate_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  /* Holds the baud rate value to be filled for the callout */
  uint8 baudrateRecord[3];
  Std_ReturnType serviceProcessStatus;

  DBG_DCM_DSPINTERNAL_TRANSITIONBAUDRATE_SSVCH_ENTRY(OpStatus,pMsgContext);

  /* Request Length Verification */
  if (pMsgContext->reqDataLen > 0U)
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
    serviceProcessStatus = DCM_E_DONE;
  }
  /* Validation of Sequence of service Request */
  else if ( Dcm_DspLinkControlRequestStatus == FALSE )
  {
    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTSEQUENCEERROR);
    serviceProcessStatus = DCM_E_DONE;
  }
  else
  {
    serviceProcessStatus = Dcm_DspInternal_LinkControl_Execution(OpStatus,
                                                                 baudrateRecord,
                                                                 pMsgContext);
  }

  DBG_DCM_DSPINTERNAL_TRANSITIONBAUDRATE_SSVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON) */

#if((DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON) || \
    (DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON) || \
    (DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON))
STATIC FUNC(Std_ReturnType, DCM_APPL_CODE) Dcm_DspInternal_LinkControl_Execution(
  Dcm_OpStatusType  OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR)  baudrateRecord,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType retVal;

#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
  /* Get current protocol id */
  uint8 instIdx = Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId;
#endif

  /* Get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* Subfunction of Link Control Request */
  Dcm_LinkControlRequestType linkControlType = curHsmInfo->subServiceId;
  Dcm_NegativeResponseCodeType nrc = E_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;

  DBG_DCM_DSPINTERNAL_LINKCONTROL_EXECUTION_ENTRY(OpStatus,baudrateRecord,pMsgContext);

  retVal = Dcm_LinkControl(
                           OpStatus,
                            linkControlType,
                            baudrateRecord,
                            &nrc
                          );
  switch (retVal)
  {
    case E_OK:
      if((linkControlType == 1U) || (linkControlType == 2U))
      {
        Dcm_DspLinkControlRequestStatus =  TRUE;
      }
      else
      {
        Dcm_DspLinkControlRequestStatus =  FALSE;
      }

      /* Assemble positive response for LinkControl request */
      pMsgContext->resDataLen = 1U;
      pMsgContext->resData[0] = curHsmInfo->subServiceId;
      serviceProcessStatus = DCM_E_DONE;
      break;

    case DCM_E_PENDING:
      serviceProcessStatus = DCM_E_PENDING;
      break;

    /* Incase of validation of linkBaudrateRecord nrc will be updated with requestOutOfRange */
    case E_NOT_OK:
      /* nrc updated with DCM_E_CONDITIONSNOTCORRECT from Dcm_LinkControl callout */
      Dcm_ExternalSetNegResponse(pMsgContext, nrc);
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      DCM_DET_REPORT_ERROR(DCM_SVCID_LINKCONTROL, DCM_E_INTERFACE_RETURN_VALUE);
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
#endif
      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  DBG_DCM_DSPINTERNAL_LINKCONTROL_EXECUTION_EXIT(serviceProcessStatus,OpStatus,
                                                 baudrateRecord,pMsgContext);
  return serviceProcessStatus;
}
#endif /* #if((DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON) || \
              (DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON) || \
              (DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON)) */

#endif /* #if(DCM_0X87_SVC_ENABLED == STD_ON) */

#if(DCM_ROE_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_FinalRoeResponse(
  uint8 instIdx)
{
  uint8_least i;
  /* get the context information current instance */
  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo = &DCM_HSM_INFO(instIdx);

  /* get configuration for current HSM instance */
  CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
    = &DCM_HSM_CONFIG(instIdx);

  /* get pointer to current message context */
  CONSTP2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_VAR) curMsgContext = &curHsmInfo->msgContext;

  /* get configuration of current transmission(Tx) buffer */
  P2CONST(Dcm_BufferConfigType, AUTOMATIC, DCM_CONST) curTxBufferConfig
    = &Dcm_BufferConfig[curHsmConfig->txBufferId];

  /* Holds the event record of the ROE event */
  P2VAR(uint8, AUTOMATIC, DCM_VAR) EventRecPtr;

  DBG_DCM_DSPINTERNAL_FINALROERESPONSE_ENTRY(DCM_INST(instIdx));

#if (DCM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(instIdx);
#endif

  curHsmInfo->serviceId = DCM_UDS_SID_ROE;

  /* initialize with service id */
  curMsgContext->idContext = curHsmInfo->serviceId;

  /* set request data pointer to received data without service Id (needed in DcmConfirmation()
   * of pos and neg. responses) */
  curMsgContext->dcmRxPduId = curHsmInfo->rxPduId;

  /* set response ID in first byte of Tx curHsmInfo */
  curTxBufferConfig->ptrBuffer[0] = curHsmInfo->serviceId | DCM_SID_RESPONSE_BIT;

  /* reset length of reponse data */
  curMsgContext->resDataLen = 0U;

  /* set response buffer of current message context to allocated transmission buffer increase
   * address by one, as the filled length is already 1 */
  curMsgContext->resData = &curTxBufferConfig->ptrBuffer[1];

  /* if ROE event is OnDTCStatusChange */
  if (Dcm_RoeData.FinalRoeResponse[DCM_ROE_SUBFUNCTION_0x01_IDX] == DCM_ROE_ONDTC_STATUS_CHANGE)
  {
    /* fill response data */
    /* ROE subfunction */
    curMsgContext->resData[0] = Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_SUBFUNCTION_0x01_IDX];
    /* Number of identified ROE events*/
    curMsgContext->resData[1] = Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x01_IDX];
    /* total response data length */
    curMsgContext->resDataLen = DCM_ROE_ONDTC_STATUS_CHANGE_RES_LEN - 1U;
    /* get the event record of the ROE event */
    EventRecPtr = &Dcm_RoeData.Dcm_EventRecord_0x01[DCM_ROE_EVENTTYPE_IDX];
  }
  /* if ROE event is onChangeOfDataIdentifier */
  else
  {
    /* fill response data */
    /* ROE subfunction */
    curMsgContext->resData[0] = Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_SUBFUNCTION_0x03_IDX];
    /* Number of identified ROE events*/
    curMsgContext->resData[1] = Dcm_RoeData.NoOfIdentifiedEvents[DCM_ROE_SUBFUNCTION_0x03_IDX];
    /* total response data length */
    curMsgContext->resDataLen = DCM_ROE_ON_CHANGE_DID_RES_LEN - 1U;
    /* get the event record of the ROE event */
    EventRecPtr = &Dcm_RoeData.Dcm_EventRecord_0x03[DCM_ROE_EVENTTYPE_IDX];
  }

  /* First 2 bytes of response is already filled
   * Fill the response buffer with EventWindowTime, EventTypeRecord and ServiceToRespondToRecord
   */
  for (i = 2U; i < curMsgContext->resDataLen; i++)
  {
    curMsgContext->resData[i] = EventRecPtr[i-1];
  }

  /* emit diagnostic request processing done event */
  (void)DCM_HSMEMITINST_WRAPPER(&Dcm_HsmScDcm, DCM_INST(instIdx), DCM_HSM_DCM_EV_PROC_DONE);

  DBG_DCM_DSPINTERNAL_FINALROERESPONSE_EXIT(instIdx);
}

#if (DCM_ROE_PERSISTENCE == STD_ON)
STATIC FUNC(Std_ReturnType, DCM_CODE)Dcm_DspInternal_ROEWriteToNvM(void)
{
  Std_ReturnType RetVal = E_NOT_OK;

  DBG_DCM_DSPINTERNAL_ROEWRITETONVM_ENTRY();

  /* Set Write Flag to TRUE, to indicate data write into NvM */
  Dcm_RoeData.NvMWriteFlag = TRUE;

  /* Unlock the NVRAM block */
  NvM_SetBlockLockStatus(DCM_ROE_NVM_BLOCK_ID, FALSE);
  RetVal = NvM_WriteBlock(DCM_ROE_NVM_BLOCK_ID, &Dcm_RoeData);
  /* if the queuing of data for writing failed */
  if(RetVal != E_OK)
  {
    /* Lock the NVRAM block */
    NvM_SetBlockLockStatus(DCM_ROE_NVM_BLOCK_ID, TRUE);
  }

  DBG_DCM_DSPINTERNAL_ROEWRITETONVM_EXIT(RetVal);
  return RetVal;
}
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */

#endif /* #if(DCM_ROE_ENABLED == STD_ON) */

#if(DCM_0X23_SVC_ENABLED == STD_ON)
/* This is the generic service handler for UDS service 0x23 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadMemoryByAddress_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType retVal = E_NOT_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Dcm_ReturnReadMemoryType ReadMemoryStatus = DCM_READ_FAILED;

  DBG_DCM_DSPINTERNAL_READMEMORYBYADDRESS_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* First call to the service function */
    case DCM_INITIAL:
    {
      /* Variable holding the memory address to be read */
      uint32 readMemAddress = 0U;
      /* Variable holding the size of the memory (number of bytes) to be read */
      uint32 readMemSize = 0U;

      /* Check if 'addressAndLengthFormatIdentifier' parameter is present */
      if ((pMsgContext->reqDataLen) >= 1U)
      {
#if (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON)
        /* Verify that the AddressLengthFormatIdentifier is valid or not */
        retVal = Dcm_DspInternal_AddressLengthAndFormat_Verification(pMsgContext->reqData[0]);
        if(retVal != E_OK)
        {
          /* Send Nrc 0x31 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
        else
#endif
        {
          /* Holds the length (number of bytes) of the memoryAddress parameter */
          uint8 memAddLength = (pMsgContext->reqData[0]) & DCM_MASK_NIBBLE;
          /* Holds the length (number of bytes) of the memorySize parameter */
          uint8 memSizeLength = (uint8)((pMsgContext->reqData[0]) >> DCM_NIBBLE_BITS);

          /*The data recieved should be addressAndLengthFormatIdentifier ->(1byte),
                 memoryAddress[], memorySize[] -> (memAddLength + memSizeLength bytes) */
          if ((pMsgContext->reqDataLen) !=
                ((PduLengthType)memAddLength + memSizeLength + DCM_ADDRESSANDLENGTHFORMATID_SIZE))
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
            serviceProcessStatus = DCM_E_DONE;
          }
          else
          {
            /* Get the Memory address and the size of memory to be read */
            retVal = Dcm_DspInternal_GetMemoryAddressAndSize(&(pMsgContext->reqData[0]),
              memAddLength, memSizeLength, &readMemAddress, &readMemSize);
            if(retVal == E_OK)
            {
              /* Variable holding the index of MemoryRangeInfo table */
              uint16 memRangeIndex = 0U;
              /* Variable holding the index of MemoryIdInfo table */
              uint16 memIdIndex = 0U;

              /* Check if adequate buffer is configured to read the data */
              if ((pMsgContext->resDataLen + readMemSize) <= pMsgContext->resMaxDataLen)
              {
                /* Perform checks to ensure that requested Memory falls within 'configured ranges'*/
                retVal = Dcm_DspInternal_ReadMemoryRangeChk(&memRangeIndex, &memIdIndex,
                                                            readMemAddress, readMemSize);
                Dcm_ReadMemorySize = readMemSize;

                if(retVal != DCM_E_NOT_OK)
                {
                  /* Holds the context information For Read memory by address service */
                  P2CONST(Dcm_MemoryRangeInfoType, AUTOMATIC, DCM_APPL_DATA)
                      pReadMemoryAddressType =
                          &Dcm_MemoryIdInfoAndIdValueTable[memIdIndex].
                                ReadMemoryRangeInfo[memRangeIndex];
                  /* Get the context information current instance */
                  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo =
                  &DCM_HSM_INFO(Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId);

                  /* Check for security access , If the complete memory range can be read in the
                   * current security level
                   */
                  if(pReadMemoryAddressType->NumMemSecLevels > 0U)
                  {
                    /* If DCM is in unlocked state */
                    if (curHsmInfo->secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
                    {
                      uint8_least k;
                      Dcm_SecLevelType curSecLevel =
                        Dcm_SecTabConfig.Entries[curHsmInfo->secTabIdx].SecLevel;

                      /* Check for security level */
                      for (k = 0U; k < pReadMemoryAddressType->NumMemSecLevels ; ++k)
                      {
                        if (curSecLevel == pReadMemoryAddressType->MemSecLevels[k])
                        {
                          break;
                        }
                      }
                      if(k >= pReadMemoryAddressType->NumMemSecLevels)
                      {
                        retVal = DCM_E_NOT_OK;
                      }
                    }
                    else
                    {
                      retVal = DCM_E_NOT_OK;
                    }
                  }
                  if(retVal == DCM_E_OK)
                  {
#if (DCM_DSP_USE_MEMORY_ID == STD_ON)
                    /* Call the Dcm_ReadMemory() callouts with the MemoryIdentifier parameter */
                    ReadMemoryStatus = Dcm_ReadMemory(OpStatus,
                      Dcm_MemoryIdInfoAndIdValueTable[memIdIndex].MemoryIDValue, readMemAddress,
                      readMemSize, &(pMsgContext->resData[0]));
#else
                    /* Call the Dcm_ReadMemory() callouts without (Set to 0) MemoryIdentifier */
                    ReadMemoryStatus = Dcm_ReadMemory(OpStatus, 0U, readMemAddress, readMemSize,
                                               &(pMsgContext->resData[0]));
#endif
                  }
                  else
                  {
                    /* Security Access denied; Set NRC */
                    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SECURITYACCESSDENIED);
                    serviceProcessStatus = DCM_E_DONE;
                  }
                }
                else
                {
                  /* Memory Range Check failed; Set NRC */
                  Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
                  serviceProcessStatus = DCM_E_DONE;
                }
              }
              else
              {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
                DCM_DET_REPORT_ERROR(DCM_SVCID_READMEMORY, DCM_E_INTERFACE_BUFFER_OVERFLOW);
#endif
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
                serviceProcessStatus = DCM_E_DONE;
              }
            }
            else
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
              serviceProcessStatus = DCM_E_DONE;
            }
          }
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        serviceProcessStatus = DCM_E_DONE;
      }
      break;
    }

    /* Subsequent call to the service function after FORCE_RCRRP, DCM_PENDING or DCM_CANCEL */
    case DCM_FORCE_RCRRP_OK:
    case DCM_PENDING:
    case DCM_CANCEL:

      /* Call the Dcm_ReadMemory() callouts with all In-parameters set to 0x0 */
      ReadMemoryStatus = Dcm_ReadMemory(OpStatus, 0U, 0U, 0U, &(pMsgContext->resData[0]));
      break;

    default:

      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  if (serviceProcessStatus != DCM_E_DONE)
  {
    switch (ReadMemoryStatus)
    {
      case DCM_READ_OK:
        /* Read Memory successful; Update the response data length */
        pMsgContext->resDataLen += (PduLengthType)Dcm_ReadMemorySize;
        serviceProcessStatus = DCM_E_DONE;
        break;

      case DCM_READ_PENDING:
        serviceProcessStatus = DCM_E_PENDING;
        break;

      case DCM_READ_FAILED:
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
        serviceProcessStatus = DCM_E_DONE;
        break;

      default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
        DCM_DET_REPORT_ERROR(DCM_SVCID_READMEMORY, DCM_E_INTERFACE_RETURN_VALUE);
#endif
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
        serviceProcessStatus = DCM_E_DONE;
        break;
    }
  }

  DBG_DCM_DSPINTERNAL_READMEMORYBYADDRESS_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(uint8, DCM_CODE) Dcm_DspInternal_ReadMemoryRangeChk(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memRangeIndex,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memIdIndex,
  uint32 readMemAddress, uint32 readMemSize)
{
  uint8 RetVal = DCM_E_NOT_OK;
  uint8_least i = 0U;
  uint8_least j = 0U;

  DBG_DCM_DSPINTERNAL_READMEMORYRANGECHK_ENTRY(memRangeIndex,memIdIndex,readMemAddress,readMemSize);

  /* Check if Read Memory is supported in the requested address range */
  for (i = 0U; ((i < DCM_NUM_MEMORY_IDINFO) && (RetVal != DCM_E_OK)) ; ++i)
  {
    for (j = 0U; j < Dcm_MemoryIdInfoAndIdValueTable[i].numberofReadRangeInfo; ++j)
    {
      if ((readMemAddress >=
           (Dcm_MemoryIdInfoAndIdValueTable[i].ReadMemoryRangeInfo[j]).MemoryRangeLow) &&
          (readMemAddress <=
           (Dcm_MemoryIdInfoAndIdValueTable[i].ReadMemoryRangeInfo[j]).MemoryRangeHigh) &&
          (((readMemAddress + readMemSize) - 1) <=
           (Dcm_MemoryIdInfoAndIdValueTable[i].ReadMemoryRangeInfo[j]).MemoryRangeHigh))
      {
        *memIdIndex = (uint16)i;
        *memRangeIndex = (uint16)j;
        RetVal = DCM_E_OK;
        break;
      }
    }
  }

  DBG_DCM_DSPINTERNAL_READMEMORYRANGECHK_EXIT(RetVal,memRangeIndex,memIdIndex,
                                              readMemAddress,readMemSize);
  return RetVal;
}
#endif  /* #if(DCM_0X23_SVC_ENABLED == STD_ON) */

#if(DCM_0X3D_SVC_ENABLED == STD_ON)
/* This is the generic service handler for UDS service 0x3D */
FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteMemoryByAddress_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext)
{
  Std_ReturnType retVal = E_NOT_OK;
  Std_ReturnType serviceProcessStatus = DCM_E_ABORT;
  Dcm_ReturnWriteMemoryType WriteMemoryStatus = DCM_WRITE_FAILED;

  DBG_DCM_DSPINTERNAL_WRITEMEMORYBYADDRESS_SVCH_ENTRY(OpStatus,pMsgContext);

  switch (OpStatus)
  {
    /* First call to the service function */
    case DCM_INITIAL:
    {
      /* Variable holding the memory address to be written to */
      uint32 writeMemAddress = 0U;
      /* Variable holding the size of the memory (number of bytes) to be written */
      uint32 writeMemSize = 0U;

      /* Check if 'addressAndLengthFormatIdentifier' parameter is present */
      if ((pMsgContext->reqDataLen) >= 1U)
      {
        /* The data recieved should be addressAndLengthFormatIdentifier ->(1byte),
           memoryAddress[], memorySize[] ->
           (writeMemAddLength + writeMemSizeLength bytes) dataRecord[] */
        /* Holds the length (number of bytes) of the memoryAddress parameter */
#if (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON)
        /* Verify that the AddressLengthFormatIdentifier is valid or not */
        retVal = Dcm_DspInternal_AddressLengthAndFormat_Verification(pMsgContext->reqData[0]);
        if(retVal != E_OK)
        {
          /* Send Nrc 0x31 */
          Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
          serviceProcessStatus = DCM_E_DONE;
        }
        else
#endif
        {
          writeMemAddLength = (pMsgContext->reqData[0]) & DCM_MASK_NIBBLE;
          /* Holds the length (number of bytes) of the memorySize parameter */
          writeMemSizeLength = (uint8)((pMsgContext->reqData[0]) >> DCM_NIBBLE_BITS);

          /* Get the Memory address and the size of memory to be write */
          retVal = Dcm_DspInternal_GetMemoryAddressAndSize(&(pMsgContext->reqData[0]),
                                                           writeMemAddLength,
                                                           writeMemSizeLength,
                                                           &writeMemAddress,
                                                           &writeMemSize);
          if(retVal == E_OK)
          {
            if ((pMsgContext->reqDataLen) !=
                    (writeMemSize + writeMemAddLength +
                        writeMemSizeLength + DCM_ADDRESSANDLENGTHFORMATID_SIZE))
            {
              Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
              serviceProcessStatus = DCM_E_DONE;
            }
            else
            {
              /* Get configuration for current HSM instance */
              CONSTP2CONST(Dcm_HsmConfigType, AUTOMATIC, DCM_CONST) curHsmConfig
                = &DCM_HSM_CONFIG(Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId);

              /* Check if adequate buffer is configured to write the data */
              if (((uint32)(pMsgContext->resDataLen) + writeMemAddLength + writeMemSize + 1U) <=
                   (uint32)(Dcm_BufferConfig[curHsmConfig->txBufferId].size))
              {
                /* Variable holding the index of MemoryRangeInfo table */
                uint16 memRangeIndex = 0U;
                /* Variable holding the index of MemoryIdInfo table */
                uint16 memIdIndex = 0U;

                /* Perform checks to ensure that requested Memory falls within 'configured ranges'*/
                retVal = Dcm_DspInternal_WriteMemoryRangeChk(&memRangeIndex, &memIdIndex,
                                                           writeMemAddress, writeMemSize);
                if(retVal != DCM_E_NOT_OK)
                {
                  /* Holds the context information For write memory by address service */
                  P2CONST(Dcm_MemoryRangeInfoType, AUTOMATIC, DCM_APPL_DATA)
                    pWriteMemoryAddressType =
                        &Dcm_MemoryIdInfoAndIdValueTable[memIdIndex].
                            WriteMemoryRangeInfo[memRangeIndex];
                  /* Get the context information current instance */
                  P2VAR(Dcm_HsmInfoType, AUTOMATIC, DCM_VAR) curHsmInfo =
                    &DCM_HSM_INFO(Dcm_RxPduIdConfig[pMsgContext->dcmRxPduId].protocolId);

                  /* Check for security access , If the complete memory range can be Write in the
                   * current security level
                   */
                  if(pWriteMemoryAddressType->NumMemSecLevels > 0U)
                  {
                    /* If DCM is in unlocked state */
                    if (curHsmInfo->secTabIdx != DCM_SEC_TAB_ENTRY_IDX_LOCKED)
                    {
                      uint8_least k;
                      Dcm_SecLevelType curSecLevel =
                        Dcm_SecTabConfig.Entries[curHsmInfo->secTabIdx].SecLevel;

                      /* Check for security level */
                      for (k = 0U; k < pWriteMemoryAddressType->NumMemSecLevels; ++k)
                      {
                        if (curSecLevel == pWriteMemoryAddressType->MemSecLevels[k])
                        {
                          break;
                        }
                      }
                      if(k >= pWriteMemoryAddressType->NumMemSecLevels)
                      {
                        retVal = DCM_E_NOT_OK;
                      }
                    }
                    else
                    {
                      retVal = DCM_E_NOT_OK;
                    }
                  }
                  if(retVal == DCM_E_OK)
                  {
#if (DCM_DSP_USE_MEMORY_ID == STD_ON)
                    /* Call the Dcm_WriteMemory() callouts with the MemoryIdentifier parameter */
                    WriteMemoryStatus =
                        Dcm_WriteMemory(OpStatus,
                                        Dcm_MemoryIdInfoAndIdValueTable[memIdIndex].MemoryIDValue,
                                        writeMemAddress,
                                        writeMemSize,
                                        &(pMsgContext->reqData[writeMemAddLength +
                                            writeMemSizeLength + 1U]));
#else
                    /* Call the Dcm_WriteMemory() callouts without (Set to 0) MemoryIdentifier */
                    WriteMemoryStatus = Dcm_WriteMemory(OpStatus, 0U,
                                                        writeMemAddress, writeMemSize,
                                                        &(pMsgContext->reqData[writeMemAddLength +
                                                            writeMemSizeLength + 1U]));
#endif
                  }
                  else
                  {
                    /* Security Access denied; Set NRC */
                    Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_SECURITYACCESSDENIED);
                    serviceProcessStatus = DCM_E_DONE;
                  }
                }
                else
                {
                  /* Memory Range Check failed; Set NRC */
                  Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
                  serviceProcessStatus = DCM_E_DONE;
                }
              }
              else
              {
#if (DCM_DEV_ERROR_DETECT == STD_ON)
                DCM_DET_REPORT_ERROR(DCM_SVCID_WRITEMEMORY, DCM_E_INTERFACE_BUFFER_OVERFLOW);
#endif
                Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALREJECT);
                serviceProcessStatus = DCM_E_DONE;
              }
            }
          }
          else
          {
            Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_REQUESTOUTOFRANGE);
            serviceProcessStatus = DCM_E_DONE;
          }
        }
      }
      else
      {
        Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT);
        serviceProcessStatus = DCM_E_DONE;
      }
      break;
    }

    /* Subsequent call to the service function after FORCE_RCRRP, DCM_PENDING or DCM_CANCEL */
    case DCM_FORCE_RCRRP_OK:
    case DCM_PENDING:
    case DCM_CANCEL:

      /* Call the Dcm_WriteMemory() callouts with all In-parameters set to 0x0 */
      WriteMemoryStatus = Dcm_WriteMemory(OpStatus, 0U, 0U, 0U,
                                          &(pMsgContext->reqData[writeMemAddLength +
                                              writeMemSizeLength + 1U]));
      break;

    default:

      serviceProcessStatus = DCM_E_DONE;
      break;
  }

  if (serviceProcessStatus != DCM_E_DONE)
  {
    uint8_least i = 0U;

    switch (WriteMemoryStatus)
    {
    case DCM_WRITE_OK:

      pMsgContext->resDataLen += ((PduLengthType)writeMemAddLength + writeMemSizeLength +
                                    DCM_ADDRESSANDLENGTHFORMATID_SIZE);
      for(i = 0; i <= (uint8)(writeMemAddLength + writeMemSizeLength); i++)
      {
        pMsgContext->resData[i] = pMsgContext->reqData[i];
      }
      serviceProcessStatus = DCM_E_DONE;
      break;

    case DCM_WRITE_PENDING:
      serviceProcessStatus = DCM_E_PENDING;
      break;

    case DCM_WRITE_FAILED:
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_GENERALPROGRAMMINGFAILURE);
      serviceProcessStatus = DCM_E_DONE;
      break;

    default:
#if (DCM_DEV_ERROR_DETECT == STD_ON)
      DCM_DET_REPORT_ERROR(DCM_SVCID_WRITEMEMORY, DCM_E_INTERFACE_RETURN_VALUE);
#endif
      Dcm_ExternalSetNegResponse(pMsgContext, DCM_E_CONDITIONSNOTCORRECT);
      serviceProcessStatus = DCM_E_DONE;
      break;
    }
  }

  DBG_DCM_DSPINTERNAL_WRITEMEMORYBYADDRESS_SVCH_EXIT(serviceProcessStatus,OpStatus,pMsgContext);
  return serviceProcessStatus;
}

STATIC FUNC(uint8, DCM_CODE) Dcm_DspInternal_WriteMemoryRangeChk(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memRangeIndex,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) memIdIndex,
  uint32 writeMemAddress, uint32 writeMemSize)
{
  uint8 RetVal = DCM_E_NOT_OK;
  uint8_least i = 0U;
  uint8_least j = 0U;

  DBG_DCM_DSPINTERNAL_WRITEMEMORYRANGECHK_ENTRY(memRangeIndex,memIdIndex,
                                                writeMemAddress,writeMemSize);

  /* Check if Read Memory is supported in the requested address range */
  for (i = 0U; ((i < DCM_NUM_MEMORY_IDINFO) && (RetVal != DCM_E_OK)) ; ++i)
  {
    for (j = 0U; j < Dcm_MemoryIdInfoAndIdValueTable[i].numberofWriteRangeInfo; ++j)
    {
      if ((writeMemAddress >=
           (Dcm_MemoryIdInfoAndIdValueTable[i].WriteMemoryRangeInfo[j]).MemoryRangeLow) &&
          (writeMemAddress <=
           (Dcm_MemoryIdInfoAndIdValueTable[i].WriteMemoryRangeInfo[j]).MemoryRangeHigh) &&
          (((writeMemAddress + writeMemSize) - 1) <=
           (Dcm_MemoryIdInfoAndIdValueTable[i].WriteMemoryRangeInfo[j]).MemoryRangeHigh))
      {
        *memIdIndex = (uint16)i;
        *memRangeIndex = (uint16)j;
        RetVal = DCM_E_OK;
        break;
      }
    }
  }

  DBG_DCM_DSPINTERNAL_WRITEMEMORYRANGECHK_EXIT(RetVal,memRangeIndex,memIdIndex,
                                               writeMemAddress,writeMemSize);
  return RetVal;
}
#endif  /* #if(DCM_0X3D_SVC_ENABLED == STD_ON) */

#if((DCM_0X23_SVC_ENABLED == STD_ON) || \
    (DCM_0X34_SVC_ENABLED == STD_ON) || \
    (DCM_0X35_SVC_ENABLED == STD_ON) || \
    (DCM_0X3D_SVC_ENABLED == STD_ON))
STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_GetMemoryAddressAndSize(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) reqData,
  uint8 memAddLength, uint8 memSizeLength,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) memAddress,
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) memSize )
{
  uint8_least i;
  Std_ReturnType retVal;

  DBG_DCM_DSPINTERNAL_GETMEMORYADDRESSANDSIZE_ENTRY(reqData,memAddLength,memSizeLength,
                                                    memAddress,memSize);

  /* Verifying if the specified addressAndLengthFormatIdentifier is valid;
     Expected number of bytes in address and memory size field is from 1 to 4*/

  if((memAddLength < 1U) ||(memSizeLength < 1U) ||
     (memAddLength > DCM_MAX_ADDRESS_BYTES) || (memSizeLength > DCM_MAX_MEMSIZE_BYTES))
  {
    retVal = E_NOT_OK;
  }
  else
  {
    /* Fetch the Memory Address to be read */
    for (i = 1U; i <= memAddLength; ++i)
    {
      *memAddress = (uint32)(*memAddress << DCM_BYTE_BITS) |
                    (uint32)(reqData[i]);
    }
    /* Fetch the Size of Memory to be read */
    for (i = 1U; i <= memSizeLength; ++i)
    {
      *memSize = (uint32)(*memSize << DCM_BYTE_BITS) |
                 (uint32)(reqData[i + memAddLength]);
    }
    retVal = E_OK;
  }

  DBG_DCM_DSPINTERNAL_GETMEMORYADDRESSANDSIZE_EXIT(retVal,reqData,memAddLength,memSizeLength,
                                                   memAddress,memSize);
  return retVal;
}
#if (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON)

STATIC FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_AddressLengthAndFormat_Verification(
  uint8 AddressLengthIdentifier)
{
  uint8_least j;
  Std_ReturnType retVal = E_NOT_OK;

  DBG_DCM_DSPINTERNAL_ADDRESSLENGTHANDFORMAT_VERIFICATION_ENTRY(AddressLengthIdentifier);

  /* Search the list of supported addressAndLengthFormatIdentifiers */
  for(j = 0U; j < DCM_NUM_ADDR_LENGTH_FORMAT_IDENTIFIER; j++)
  {
    if(Dcm_SupportedAddAndLenFormatIds[j] == AddressLengthIdentifier)
    {
      retVal = E_OK;
      break;
    }
  }

  DBG_DCM_DSPINTERNAL_ADDRESSLENGTHANDFORMAT_VERIFICATION_EXIT(retVal,AddressLengthIdentifier);
  return retVal;
}

#endif /* #if (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON) */

#endif /* #if ((DCM_0X23_SVC_ENABLED == STD_ON) || \
               (DCM_0X34_SVC_ENABLED == STD_ON) || \
               (DCM_0X35_SVC_ENABLED == STD_ON) || \
               (DCM_0X3D_SVC_ENABLED == STD_ON )) */

#if (DCM_ROE_ENABLED == STD_ON)
FUNC(void, DCM_CODE) Dcm_DspInternal_GetCommonDidSignalMask(uint16 DidIdx)
{
  uint16_least RoeDidSignalIdx;
  uint16_least DidSignalIdx;
  uint16_least DidTableIdx;
  uint16_least BlockMaskIdx;
  uint16 SignalIdx;
  P2CONST(Dcm_DidSignalType, AUTOMATIC, DCM_CONST) SignalCfg;

  /* Reset flags for blocking asynchronous access to to DidData by ROE and read service */
  for (BlockMaskIdx=0U; BlockMaskIdx < DCM_DID_BLOCK_MASK_NUM ; BlockMaskIdx++)
  {
    RoeDidBlockFlags[BlockMaskIdx] = 0x00U;
  }

  /* Check all signals used by Did specified by function parameter DidIdx */
  for (RoeDidSignalIdx=0U; RoeDidSignalIdx < Dcm_DidTable[DidIdx].NumSignals ; RoeDidSignalIdx++)
  {
    /* Get index of currently checked signal in signal reference table for
       DID passed by function parameter                                      */
    SignalIdx = Dcm_DidTable[DidIdx].Signals[RoeDidSignalIdx].DspDataIndex;

    /* Check all specified DIDs for commonly used signals with DID
       passed by function parameter                                */
    for (DidTableIdx=0U; DidTableIdx < DCM_NUM_DID ; DidTableIdx++)
    {
      SignalCfg = &(Dcm_DidTable[DidTableIdx].Signals[0U]);

      for (DidSignalIdx=0U; DidSignalIdx < Dcm_DidTable[DidTableIdx].NumSignals ; DidSignalIdx++)
      {
        if (SignalCfg->DspDataIndex == SignalIdx)
        {
           /* Did use same signal as used by ROE onChangeofDataIDentifier Did */
           RoeDidBlockFlags[DidTableIdx / 8U] |= (uint8)(1U <<(DidTableIdx % 8U));
           break; /* continue with next Did */
        }
        SignalCfg = &(Dcm_DidTable[DidTableIdx].Signals[DidSignalIdx + 1U]);
      }
    }
  }
}

STATIC FUNC(boolean, DCM_CODE) Dcm_PostponeROEFromPollingDIDData (
  uint16  didIndex )
{
  boolean RoeCommonSignal = FALSE; /* continue state: TRUE:  reading signal must be postponed */
                                   /*                 FALSE: continue reading anyway.         */

  /* Optimizations: */
#if ((DCM_ROE_PRECONF_SUPPORT == STD_OFF) && \
     (DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 == STD_OFF) && \
     (DCM_ROE_PERSISTENCE == STD_OFF))
  boolean RetVal = FALSE;
  return RetVal;
#else
  /* check whether DID is already handled by signal polling in case of ROE started */
  if ( (RoeDidBlockFlags[didIndex / 8U] & (uint8)(1U <<(didIndex % 8U))) != 0U )
  {
    /* common signal used by ROE signal polling and read access for DID */
    RoeCommonSignal = TRUE;
  }

  /* ENTER critical section */
  SchM_Enter_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();

  /* if Dcm_RoePollAsyncState is idle no conflict, polling can start in parallel
     if Dcm_RoePollAsyncState = Postponed Polling is blocked anyway               */
  if (Dcm_RoePollAsyncState != ROE_POLLING_ACTIVE)
  { /* Idle or postponed */
    if ( TRUE == RoeCommonSignal )
    {
      RoeCommonSignal = FALSE; /* continue; also if state is already postponed */
    }
    Dcm_RoePollAsyncState = ROE_POLLING_POSTPONED; /* start reading postpone polling possible */
  }

  /* LEAVE critical section */
  SchM_Exit_Dcm_SCHM_DCM_EXCLUSIVE_AREA_0();
  return RoeCommonSignal;
#endif
}

STATIC FUNC(void, DCM_CODE) Dcm_AllowROEToPollDIDData (void)
{
  Dcm_RoePollAsyncState = ROE_POLLING_IDLE;
}
#endif /* #if (DCM_ROE_ENABLED == STD_ON) */

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[end of file]================================================================*/
