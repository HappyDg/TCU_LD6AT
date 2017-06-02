/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined PDUR_CANTP_H)
#define PDUR_CANTP_H

/*==================[includes]==============================================*/
#include <TSAutosar.h> /* EB specific standard types */
#include <ComStack_Types.h> /* AUTOSAR Communication Stack types */
/* Exclude post-build-time configuration include file if requested to do so */
#if (!defined PDUR_NO_PBCFG_REQUIRED) && (!defined PDUR_NO_CFG_REQUIRED)
#include <PduR_SymbolicNames_PBcfg.h>
#endif /* PDUR_NO_PBCFG_REQUIRED */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function declarations]========================*/
#define PDUR_START_SEC_CODE
#include <MemMap.h>

/**
 ** \brief This service is called by the receiving CanTp module requesting a TP-buffer.
 **
 ** \param[in]  RxPduId             Identification of the received I-PDU.
 ** \param[in]  TpSduLength         Total length of the PDU to be received.
 ** \param[out] BufferSizePtr       Available receive buffer in the receiving module.
 **                                 This parameter will be used to compute the Block Size (BS) in
 **                                 the transport protocol module.
 **
 ** \return Result of buffer request
 ** \retval BUFREQ_OK        Connection has been accepted.
 **                          BufferSizePtr indicates the available receive buffer.
 **                          Reception is continued.
 ** \retval BUFREQ_E_OVFL    No Buffer of the required length can be provided. Reception is aborted.
 **                          BufferSizePtr remains unchanged.
 ** \retval BUFREQ_E_NOT_OK  Connection has been rejected. Reception is aborted.
 **                          BufferSizePtr remains unchanged.
 **
 ** \ServiceID{0x34}
 ** \Reentrancy{Reentrant for different PduIds. Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception
(
    PduIdType RxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
);

/**
 ** \brief This service is called by the receiving CanTp module requesting a TP-buffer.
 **
 ** \param[in]  RxPduId             Identification of the received I-PDU.
 ** \param[in]  PduInfoPtr          Pointer to the buffer (SduDataPtr) and its length (SduLength)
 **                                 containing the data to be copied by PDU Router module in
 **                                 case of gateway or upper layer module in case of reception.
 ** \param[out] BufferSizePtr       Available receive buffer after data has been copied.
 **
 ** \return Result of buffer request
 ** \retval BUFREQ_OK        Data copied successfully.
 ** \retval BUFREQ_E_NOT_OK  Data was not copied because an error occurred.
 **
 ** \ServiceID{0x32}
 ** \Reentrancy{Reentrant for different PduIds. Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
);

/**
 ** \brief This service is called by the sending CanTp module requesting a TP-buffer.
 **
 ** \param[in]  TxPduId             Identification of the transmitted I-PDU.
 ** \param[out] PduInfoPtr          Provides destination buffer and the number of bytes to copy.
 **                                 In case of gateway the PDU Router module will copy,
 **                                 otherwise the source upper layer module will copy the data.
 **                                 If not enough transmit data is available, no data is copied.
 **                                 The transport protocol module will retry.
 **                                 A copy size of 0 can be used to indicate state changes in the
 **                                 retry parameter.
 ** \param[in]  RetryInfoPtr        This parameter is used to retransmit data because problems
 **                                 during the last service call.
 **                                 If the I-PDU is transmitted from a local module (e.g. DCM) the
 **                                 PDU router module will just forward the parameter value
 **                                 without check. If the I-PDU is gatewayed from another bus,
 **                                 the PDU Router module will make the following interpretation:
 **                                 If the transmitted TP I-PDU does not support the retry feature
 **                                 a NULL_PTR is provided. It indicates that the copied transmit
 **                                 data can be removed from the buffer after it has been copied.
 **                                 If the retry feature is used by the Tx I-PDU, RetryInfoPtr must
 **                                 point to a valid RetryInfoType element.
 **                                 If TpDataState indicates TP_CONFPENDING, the previously
 **                                 copied data must remain in the TP buffer to be available for
 **                                 error recovery.
 **                                 TP_DATACONF indicates that all data that have been copied
 **                                 so far are confirmed and can be removed from the TP buffer.
 **                                 Data copied by this API call are excluded and will be
 **                                 confirmed later.
 **                                 TP_DATARETRY indicates that this API call shall copy
 **                                 already copied data in order to recover from an error. In this
 **                                 case AvailableDataPtr specifies the offset of the first byte to be
 **                                 copied by the API call.
 ** \param[out] AvailableDataPtr    Indicates the remaining number of bytes that are available in
 **                                 the PduR Tx buffer. AvailableDataPtr can be used by
 **                                 TP modules that support dynamic payload lengths (e.g. FlexRay
 **                                 ISO Transport Layer) to determine the size of the following CFs.
 **
 ** \return Result of buffer request
 ** \retval BUFREQ_OK        Data has been copied to the transmit buffer completely as requested.
 ** \retval BUFREQ_E_BUSY    Request could not be fulfilled, because the required amount of
 **                          Tx data is not available. TP layer might retry later on.
 **                          No data has been copied.
 ** \retval BUFREQ_E_NOT_OK  Data has not been copied. Request failed.
 **
 ** \ServiceID{0x36}
 ** \Reentrancy{Reentrant for different PduIds. Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableDataPtr
);

/**
 ** \brief This service is called by the CanTp module after an I-PDU has been received
 ** successfully or when an error occurred. It is also used to confirm cancellation of an I-PDU.
 **
 ** \param[in]  RxPduId   Identification of the received I-PDU.
 ** \param[in]  Result    Result of the reception.
 **
 ** \ServiceID{0x33}
 ** \Reentrancy{Reentrant for different PduIds. Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous}
 **/
extern FUNC(void, PDUR_CODE) PduR_CanTpRxIndication
(
    PduIdType    RxPduId,
    NotifResultType  Result
);

/**
 ** \brief This service is called by the CanTp module after the I-PDU has been
 ** transmitted on its network, the result will reveal if the transmission was successful or not.
 **
 ** \param[in]  TxPduId  Identification of the transmitted I-PDU.
 ** \param[in]  Result   Result of the transmission of the I-PDU.
 **
 ** \ServiceID{0x37}
 ** \Reentrancy{Reentrant for different PduIds. Non reentrant for the same PduId.}
 ** \Synchronicity{Synchronous }
 **/
extern FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation
(
    PduIdType    TxPduId,
    NotifResultType  Result
);

#define PDUR_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

#endif /* if !defined( PDUR_CANTP_H ) */
/*==================[end of file]===========================================*/
