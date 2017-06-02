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

/* Misra-C:2004 Deviations:
 *
 * MISRA-1) Deviated Rule: 11.3 (advisory)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is null pointer constant.
 *
 * MISRA-2) Deviated Rule: 6.3 (advisory)
 * "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 * Reason:
 * In this case variables are casted to a natural integral type since, the value is further used
 * for purposes where natural types are most efficient (e.g. indexing).
 *
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */
#include <Com_Defs.h>           /* COM_SERVICE_NOT_AVAILABLE */

#include <Com_Core_TxSignal.h>  /* signal functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif


/** \brief Com_SendSignal - send a signal see COM197
 * The service Com_SendSignal updates the signal object identified by SignalId
 * with the signal referenced by the SignalDataPtr parameter.
 * Preconditions:
 * COM must be initialized.
 * \param[in] SignalId - ID of the signal to be sent
 * \param[in] SignalDataPtr - place in memory to copy the data from
 * \retval E_OK - success
 * \retval COM_SERVICE_NOT_AVAILABLE - failure (Com not initialized,
 * corresponding I-PDU group was stopped or
 * service failed due to development error)
 */
FUNC(uint8, COM_CODE) Com_SendSignal
(
   Com_SignalIdType SignalId,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
   uint8 retval = COM_SERVICE_NOT_AVAILABLE;

   /* pointer to the configuration of the signal */
   P2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr;

   /* pointer to the configuration of the IPdu to which the signal belongs */
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;
   ComIPduRefType PduId;             /* Id of the IPdu to which the the signal belongs */

   DBG_COM_SENDSIGNAL_ENTRY(SignalId,SignalDataPtr);


#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether Com is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_SendSignal);
   }
   /* check SignalDataPtr */
   else if (SignalDataPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_SendSignal);
   }
   /* Check if the SignalId is within the range of the ComTxSignalArraySize */
   else if (Com_gConfigPtr->ComTxSignalArraySize <= SignalId)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_SendSignal);
   }
   else

      /* The check whether the signal is a Tx signal or not is done below with the check of the
       * configuration of the signal */

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

   {
      /* get the configuration of the signal identified by the signal Id and check the
       * configuration */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      SignalPtr=COM_GET_CONFIG_ELEMENT(ComTxSignalType, Com_gConfigPtr->ComTxSignalRef, SignalId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == SignalPtr)
      {
         COM_PRECONDITION_ASSERT(
               (NULL_PTR == SignalPtr),
               COMServiceId_SendSignal);
      }
      else if (SignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIGNAL)
      {
         COM_PRECONDITION_ASSERT(
               (SignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_SIGNAL),
               COMServiceId_SendSignal);
      }
      else
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      {
         /* get the IPdu Id to which the signal belongs */
         PduId = SignalPtr->TxBasicParam.ComIPduRef;


         /* get IPdu to which the the signal belongs and check if the IPdu is valid */
         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         IPduPtr = COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, PduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         if (NULL_PTR == IPduPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == IPduPtr),
                  COMServiceId_SendSignal);
         }
         else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_IPDU)
         {
            COM_PRECONDITION_ASSERT(
                  (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_IPDU),
                  COMServiceId_SendSignal);
         }
         else
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

         {
            retval = Com_EB_SendSignal(SignalPtr,
                  IPduPtr,
                  PduId,
                  SignalDataPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
                  ,FALSE
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
            );
         }
      }
   }


   DBG_COM_SENDSIGNAL_EXIT(retval,SignalId,SignalDataPtr);
   return retval;
}

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
