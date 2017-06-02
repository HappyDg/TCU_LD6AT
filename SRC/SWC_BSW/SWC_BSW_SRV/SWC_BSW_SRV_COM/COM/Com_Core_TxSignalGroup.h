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
#ifndef COM_CORE_TXSIGNALGROUP_H_
#define COM_CORE_TXSIGNALGROUP_H_
/*==================[inclusions]============================================*/


#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Api.h>                /* get module interface */

#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
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


/** \brief Com_EB_UpdateShadowSignal - updates a group signal
 * The service Com_EB_UpdateShadowSignal updates the shadow signal object
 * identified by SignalId with the signal referenced by the SignalDataPtr
 * parameter.
 * Preconditions:
 * COM must be initialized.
 * \param[in] GSignalPtr - reference to configuration of group signal
 * \param[in] SignalGId - Id of signal group to which the group signal belongs
 * \param[in] SignalGPtr - reference to configuration of signal group to
 * which the group signal belongs
 * \param[in] SignalDataPtr - place in memory to copy the data from (RAM)
 * \retval none
 */

TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_UpdateShadowSignal(
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);


/** \brief Com_EB_SendSignalGroup - internal function for sending a signal group
 * The service Com_EB_SendSignalGroup sends a signal group. It evaluates the
 * TMS flags of the group signals and calculates the TMS for the signal group
 * Preconditions:
 * - COM must be initialized.
 * \param[in] SGArrayPtr - not used
 * \param[in] SGArrayPtrLength - not used
 * \param[in] SignalGId - Id of signal group
 * \param[in] SignalGPtr - reference to configuration of signal group
 * \param[in] PduId - id of I-Pdu to which the signal group belongs
 * \param[in] IPduPtr - reference to the configuration of I-Pdu
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \retval E_OK if signal group could be copied to the I-Pdu
 * \retval COM_SERVICE_NOT_AVAILABLE if corresponding I-PDU group was stopped
 * (or service failed due to development error)
 */
TS_MOD_PRIV_DECL FUNC(uint8, COM_CODE) Com_EB_SendSignalGroup
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   uint16 SGArrayPtrLength,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
);


#if (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)

/** \brief Com_EB_SendSignalGroupArray_DETCheck - internal function for updating and
 * sending a signal group and DET checks for signal group array
 * The service Com_EB_SendSignalGroupArray_DETCheck updates and sends a signal group.
 * It evaluates the
 * TMS flags of the group signals and calculates the TMS for the signal group
 * Performs DET checks for signal group array parameter
 * Preconditions:
 * - COM must be initialized.
 * \param[in] SGArrayPtr - Reference to the signal group array to be transmitted
 * \param[in] SGArrayLength - Length of the signal group array
 * \param[in] SignalGId - Id of signal group
 * \param[in] SignalGPtr - reference to configuration of signal group
 * \param[in] PduId - id of I-Pdu to which the signal group belongs
 * \param[in] IPduPtr - reference to the configuration of I-Pdu
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \retval E_OK if signal group could be copied to the I-Pdu
 * \retval COM_SERVICE_NOT_AVAILABLE if corresponding I-PDU group was stopped
 * (or service failed due to development error)
 */
TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_SendSignalGroupArray_DETCheck
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
   uint16 SGArrayLength,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
);

#endif /* (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) */

#if ((COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) || \
      ((COM_SIGNAL_GW_ENABLE == STD_ON)))

/** \brief Com_EB_SendSignalGroupArray - internal function for updating and
 * sending a signal group
 * The service Com_EB_SendSignalGroupArray updates and sends a signal group.
 * It evaluates the
 * TMS flags of the group signals and calculates the TMS for the signal group
 * Preconditions:
 * - COM must be initialized.
 * \param[in] SGArrayPtr - Reference to the signal group array to be transmitted
 * \param[in] SignalGId - Id of signal group
 * \param[in] SignalGPtr - reference to configuration of signal group
 * \param[in] PduId - id of I-Pdu to which the signal group belongs
 * \param[in] IPduPtr - reference to the configuration of I-Pdu
 * \param[in] SendInMainFunctionTx - if TRUE, the Pdu is sent not now but
 * during the next Com_MainfunctionTx(), otherwise immediately
 * \retval E_OK if signal group could be copied to the I-Pdu
 * \retval COM_SERVICE_NOT_AVAILABLE if corresponding I-PDU group was stopped
 */
TS_MOD_PRIV_DEFN FUNC(uint8, COM_CODE) Com_EB_SendSignalGroupArray
(
   P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) SGArrayPtr,
#if (COM_TMS_ENABLE == STD_ON)
   ComSignalGroupRefType SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   ComIPduRefType PduId,
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
   ,boolean SendInMainFunctionTx
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
);

#endif /* ((COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) || \
      ((COM_SIGNAL_GW_ENABLE == STD_ON))) */


#if (COM_TMS_ENABLE == STD_ON)
/** \brief Com_EB_CalculateGroupSignalTM - calculates the transmission mode of
 * a group signal
 * The service Com_EB_CalculateGroupSignalTM evaluates the filter of the group
 * signal and sets the TMS flags
 * Preconditions:
 * - COM must be initialized.
 * - signal type COM_UINT8_N not allowed
 * \param[in] GSignalPtr - reference to configuration of group signal
 * \param[in] SignalGId - Id of signal group to which the group signal belongs
 * \param[in] SignalGPtr - reference to configuration of signal group to
 * which the group signal belongs
 * \param[in] TMSResult - result of filter
 * \param[in] SignalType - type of the group signal
 * \retval none
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_CalculateGroupSignalTM
(
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr,
   ComSignalGroupRefType SignalGId,
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   boolean TMSResult
);

#endif /* (COM_TMS_ENABLE == STD_ON) */

#define COM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

#endif /* COM_CORE_TXSIGNALGROUP_H_ */
/*==================[end of file]===========================================*/

