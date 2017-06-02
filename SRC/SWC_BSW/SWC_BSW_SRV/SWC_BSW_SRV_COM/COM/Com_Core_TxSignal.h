/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef COM_CORE_TXSIGNAL_H_
#define COM_CORE_TXSIGNAL_H_
/*==================[inclusions]============================================*/


#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Api.h>                /* get module interface */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* get development error tracer interface */
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

/*==================[version check]=========================================*/

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#define COM_START_SEC_CODE
#include <MemMap.h>




/** \brief Com_EB_SendSignal - send a signal
 * The service Com_SendSignal updates the signal object identified by SignalId
 * with the signal referenced by the SignalDataPtr parameter.
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalPtr - reference to configuration of signal
 * \param[in] IPduPtr - reference to configuration of I-Pdu to which the
 * signal belongs
 * \param[in] PduId - ID of I-Pdu to which the signal belongs
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \retval E_OK - success
 * \retval COM_SERVICE_NOT_AVAILABLE - failure (corresponding I-PDU group was
 * stopped)
 */

TS_MOD_PRIV_DECL FUNC(uint8, COM_CODE) Com_EB_SendSignal
(
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   ComIPduRefType PduId,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
);


#define COM_STOP_SEC_CODE
#include <MemMap.h>



#endif /* COM_CORE_TXSIGNAL_H_ */
/*==================[end of file]===========================================*/

