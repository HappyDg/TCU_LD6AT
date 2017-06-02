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
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */
#include <Com_Core_TxIPdu.h>    /* Header TxIPdu functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>
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

/** \brief Send an IPDU
 ** The function triggers sending of an IPDU
 ** Preconditions:
 ** - The COM must be initialized
 ** - The function must only be called from callouts
 ** \param[in] ComTxPduId ID of the PDU to be sent
 ** \retval None
 */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

FUNC(void, COM_CODE) Com_TriggerIPDUSend
(
   PduIdType ComTxPduId
)
{
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
    uint8 BitRes;
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */

    DBG_COM_TRIGGERIPDUSEND_ENTRY(ComTxPduId);

#if (COM_DEV_ERROR_DETECT == STD_ON)

    /* check whether Com is initialized */
    if (Com_InitStatus == COM_EB_UNINIT)
    {
        COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_TriggerIPDUSend);
    }
    /* check if ComTxPduId is valid */
    else if (Com_gConfigPtr->ComTxIPduArraySize <= ComTxPduId)
    {
        COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_TriggerIPDUSend);
    }
    else

#endif /* COM_DEV_ERROR_DETECT */

    {
        /* If the PDU cannot be sent now (because the minimum delay time has not
        * passed by yet)... */
#if (COM_MDT_QUEUE_AVAILABLE == STD_ON)
        TS_GetBit(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + ComTxPduId)],
                  COM_TXPDU_MDTQUEUED, uint8, BitRes);
        if (BitRes == TRUE)
        {
            /* If Mdt-queued, schedule for sending asap. */
            TS_AtomicSetBit_8(&Com_gDataMemPtr[(Com_gConfigPtr->ComTxIPduStatusBase + ComTxPduId)],
                              COM_TXPDU_SENDIMMEDIATELY);
        }
        else
#endif /* (COM_MDT_QUEUE_AVAILABLE == STD_ON) */
        {
            /* Deviation MISRA-1 */
            /* Deviation MISRA-2 */
            CONSTP2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr =
                    COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, ComTxPduId);
            /* send the Pdu out */
            Com_EB_Send_Pdu((ComIPduRefType)ComTxPduId, IPduPtr);
        }
    }

    DBG_COM_TRIGGERIPDUSEND_EXIT(ComTxPduId);
}                               /* Com_TriggerIPDUSend */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
