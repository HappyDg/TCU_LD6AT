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

#include <Com_Core_TxSignalGroup.h>  /* (group)signal(group) functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

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

FUNC(void, COM_CODE) Com_UpdateShadowSignal
(
   Com_SignalIdType SignalId,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
)
{
#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

   /* pointer to the configuration of the signal */
   P2CONST(ComTxGroupSignalType, AUTOMATIC, COM_APPL_CONST) GSignalPtr;

   /* id of the SignalGroup to which the group signal belongs to */
   ComSignalGroupRefType SignalGId;
   /* configuration of the SignalGroup to which the group signal belongs to */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr;

   DBG_COM_UPDATESHADOWSIGNAL_ENTRY(SignalId,SignalDataPtr);

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check whether Com is initialized */
   if (Com_InitStatus == COM_EB_UNINIT)
   {
      COM_DET_REPORTERROR(COM_E_UNINIT, COMServiceId_UpdateShadowSignal);
   }
   /* check SignalDataPtr */
   else if (SignalDataPtr == NULL_PTR)
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_UpdateShadowSignal);
   }
   /* Check if the SignalId is within the range of the ComTxGroupSignalArraySize */
   else if (Com_gConfigPtr->ComTxGroupSignalArraySize <= SignalId)
   {
      COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_UpdateShadowSignal);
   }
   else
      /* The check whether the signal is a Tx group signal or not is done below with the check of the
       * configuration of the group signal */

#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

   {
      /* get the configuration of the group signal identified by the group signal Id and check the
       * configuration */
      /* Deviation MISRA-1 */
      /* Deviation MISRA-2 */
      GSignalPtr = COM_GET_CONFIG_ELEMENT(ComTxGroupSignalType,
            Com_gConfigPtr->ComTxGroupSignalRef,
            SignalId
      );

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
      /* CHECK: NOPARSE */
      if (NULL_PTR == GSignalPtr)
      {
         COM_PRECONDITION_ASSERT(
               (NULL_PTR == GSignalPtr),
               COMServiceId_UpdateShadowSignal);
      }
      else if (GSignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_GROUP_SIG)
      {
         COM_PRECONDITION_ASSERT(
               (GSignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_GROUP_SIG),
               COMServiceId_UpdateShadowSignal);
      }
      else
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

      {
         /* get the Group Signal Id to which the signal belongs */
         SignalGId = GSignalPtr->ComSignalGroupRef;

         /* get the configuration of the Group Signal to which this group signal belongs to */
         /* Deviation MISRA-1 */
         /* Deviation MISRA-2 */
         SignalGPtr = COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType,
               Com_gConfigPtr->ComTxSignalGroupRef,
               SignalGId
         );

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         if (NULL_PTR == SignalGPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == SignalGPtr),
                  COMServiceId_UpdateShadowSignal);
         }
         if (SignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIG_GROUP)
         {
            COM_PRECONDITION_ASSERT(
                  (SignalGPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_SIG_GROUP),
                  COMServiceId_UpdateShadowSignal);
         }
         else
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

         {
#if (COM_DEV_ERROR_DETECT == STD_ON)
#if (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON)
            if (SignalGPtr->ComSignalGroupValueRef == COM_RAM_SIZE_MAX)
            {
               /* the signal group has no shadow buffer assigned an shall
                * only be used with the Com_SendSignalGroupArray() */
               COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_UpdateShadowSignal);
            }
            else
#endif /* (COM_BASED_TRANSFORMER_SUPPORT_TX == STD_ON) */
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */
            {
               Com_EB_UpdateShadowSignal
               (
                     GSignalPtr,
#if (COM_TMS_ENABLE == STD_ON)
                     (ComSignalGroupRefType)SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
                     SignalGPtr,
                     SignalDataPtr
               );
            }
         }
      }
   }

#else

   DBG_COM_UPDATESHADOWSIGNAL_ENTRY(SignalId,SignalDataPtr);

   TS_PARAM_UNUSED(SignalId);
   TS_PARAM_UNUSED(SignalDataPtr);

#if (COM_DEV_ERROR_DETECT == STD_ON)
   COM_DET_REPORTERROR(COM_E_PARAM, COMServiceId_UpdateShadowSignal);
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

   DBG_COM_UPDATESHADOWSIGNAL_EXIT(SignalId,SignalDataPtr);
}                               /* Com_UpdateShadowSignal */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
