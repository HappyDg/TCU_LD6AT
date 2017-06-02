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

/*==================[includes]==============================================*/


#include <TSAutosar.h> /* EB specific standard types */
#include <ComStack_Types.h> /* AUTOSAR Communication Stack types */
#include <PduR_Internal_Static.h> /* Internal API (static part) */
#define PDUR_NO_PBCFG_REQUIRED /* This prevents the inclusion of the symbolic name value header */
#include <PduR_CanIf.h> /* Header provided to Generic Upper Layer */
#define PDUR_NO_PBCFG_REQUIRED /* This prevents the inclusion of the symbolic name value header */
#include <PduR_CanTp.h> /* Header provided to Generic Upper Layer */
#define PDUR_NO_PBCFG_REQUIRED /* This prevents the inclusion of the symbolic name value header */
#include <PduR_Com.h> /* Header provided to Generic Upper Layer */
#define PDUR_NO_PBCFG_REQUIRED /* This prevents the inclusion of the symbolic name value header */
#include <PduR_Dcm.h> /* Header provided to Generic Upper Layer */
#include <PduR_Lcfg.h> /* Link-time configurable data */
#include <PduR_Types.h> /* PduR specific types */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/* AUTOSAR Memory Mapping - start section for code */
#define PDUR_START_SEC_CODE
#include <MemMap.h>

/*****************************************************************************
    IF API for generic layer CanIf
*****************************************************************************/

FUNC(void, PDUR_CODE) PduR_CanIfRxIndication
(
    PduIdType    RxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA)   PduInfoPtr
)
{
    /* Call generic RxIndication function with index PduR_CanIfRTabLoIfConfigIdx for
     * selecting the proper configuration */
    PduR_GenericIfRxIndication(RxPduId, PduInfoPtr, PduR_CanIfRTabLoIfConfigIdx);
}

FUNC(void, PDUR_CODE) PduR_CanIfTxConfirmation
(
    PduIdType    TxPduId
)
{
    /* Call generic TxConfirmation function with index PduR_CanIfRTabLoIfConfigIdx
     * to select the proper configuration */
    PduR_GenericIfTxConfirmation(TxPduId, PduR_CanIfRTabLoIfConfigIdx);
}

/*****************************************************************************
    TP API for generic layer CanTp
*****************************************************************************/

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpStartOfReception
(
    PduIdType RxPduId,
    PduLengthType TpSduLength,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
    BufReq_ReturnType RetVal;

    /* Call generic StartOfReception function with index PduR_CanTpRTabLoTpConfigIdx
     * to select the proper configuration */
    RetVal = PduR_GenericTpStartOfReception(RxPduId, TpSduLength, BufferSizePtr, PduR_CanTpRTabLoTpConfigIdx);

    return RetVal;
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyRxData
(
    PduIdType RxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_CONST) PduInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) BufferSizePtr
)
{
    /* Call generic CopyRxData function with index PduR_CanTpRTabLoTpConfigIdx for
     * selecting the proper configuration */
    return PduR_GenericTpCopyRxData(RxPduId, PduInfoPtr, BufferSizePtr, PduR_CanTpRTabLoTpConfigIdx);
}

FUNC(BufReq_ReturnType, PDUR_CODE) PduR_CanTpCopyTxData
(
    PduIdType TxPduId,
    P2VAR(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr,
    P2VAR(RetryInfoType, AUTOMATIC, PDUR_APPL_DATA) RetryInfoPtr,
    P2VAR(PduLengthType, AUTOMATIC, PDUR_APPL_DATA) AvailableDataPtr
)
{
    /* Call generic CopyTxData function with index PduR_CanTpRTabLoTpConfigIdx
     * for selecting the proper configuration */
    return PduR_GenericTpCopyTxData(TxPduId, PduInfoPtr, RetryInfoPtr, AvailableDataPtr, PduR_CanTpRTabLoTpConfigIdx);
}

FUNC(void, PDUR_CODE) PduR_CanTpRxIndication
(
    PduIdType    RxPduId,
    NotifResultType  Result
)
{
    /* Call generic RxIndication function with index PduR_CanTpRTabLoTpConfigIdx
     * to select the proper configuration */
    PduR_GenericTpRxIndication(RxPduId, Result, PduR_CanTpRTabLoTpConfigIdx);
}

FUNC(void, PDUR_CODE) PduR_CanTpTxConfirmation
(
    PduIdType    TxPduId,
    NotifResultType  Result
)
{
    /* Call generic TxConfirmation function with index PduR_CanTpRTabLoTpConfigIdx
     * for selecting the proper configuration */
    PduR_GenericTpTxConfirmation(TxPduId, Result, PduR_CanTpRTabLoTpConfigIdx);
}

/*****************************************************************************
    IF API for generic layer Com
*****************************************************************************/

FUNC(Std_ReturnType, PDUR_CODE) PduR_ComTransmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
    Std_ReturnType RetVal;

    /* Call generic Transmit function with index PduR_ComRTabUpIfTxConfigIdx
     * to select the proper configuration */
    RetVal = PduR_GenericIfTransmit((PduR_PduIdType) TxPduId, PduInfoPtr, PduR_ComRTabUpIfTxConfigIdx);

    return RetVal;
}

/*****************************************************************************
    TP API for generic layer Dcm
*****************************************************************************/

FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit
(
    PduIdType TxPduId,
    P2CONST(PduInfoType, AUTOMATIC, PDUR_APPL_DATA) PduInfoPtr
)
{
    Std_ReturnType RetVal;

    /* Call generic Transmit function with index PduR_DcmRTabUpTpConfigIdx
     * to select the proper configuration */
    RetVal = PduR_GenericTpTransmit((PduR_PduIdType) TxPduId, PduInfoPtr, PduR_DcmRTabUpTpConfigIdx);

    return RetVal;
}
/* AUTOSAR Memory Mapping - end section for code */
#define PDUR_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
