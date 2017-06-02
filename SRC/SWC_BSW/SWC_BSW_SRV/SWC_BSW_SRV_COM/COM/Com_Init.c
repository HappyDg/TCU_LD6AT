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
 * MISRA-4) Deviated Rule: 14.2 (required)
 * "All non-null statements shall either:
 *                        a) have at least one side effect however executed, or
 *                        b) cause control flow to change."
 *
 * Reason:
 * If constant configuration address is used Com_ConfigPtr is not used. To
 * avoid compiler warnings on most compilers this cast with no side-effect
 * is implemented.
 *
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Rules.h>          /* Generated configuration + derived rules */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* public intra module API */

#include <Com_Core_TxIPdu.h>    /* Header TxIPdu functions */
#include <Com_Core_RxIPdu.h>    /* Header RxIPdu functions */

#if (COM_PBCFGM_SUPPORT_ENABLED == STD_ON)
#include <PbcfgM_Api.h>             /* Post build configuration manager */
#endif /* (COM_PBCFGM_SUPPORT_ENABLED == STD_ON) */


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


/* start code section declaration */
#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

/** \brief Com_Init - initialize the COM
 * function to initialize the COM; checks the configuration and sets
 * everything back to start positions
 * \param[in] config - pointer to configurations structure
 * \retval None
 * \remarks This function stops all PDU-groups, re-initializes the send-
 * and minimum-delay-time-"queues", and sets the initial values for all
 ** internal and external signals.
 */
FUNC(void, COM_CODE) Com_Init
(
   P2CONST(Com_ConfigType, AUTOMATIC,COM_APPL_CONST) Com_ConfigPtr
)
{

   ComIPduRefType pdu;

   /*
    * local configuration pointer
    */
   P2CONST(Com_ConfigType, AUTOMATIC, COM_APPL_CONST) TmpCfgPtr =
         /*
          * check for constant configuration address
          */
#if (COM_CONST_CFG_ADDRESS_ENABLE == STD_OFF)
         Com_ConfigPtr;

   DBG_COM_INIT_ENTRY(Com_ConfigPtr);

#if (COM_PBCFGM_SUPPORT_ENABLED == STD_ON)

   /* If the initialization function is called with an null pointer get the configuration from the
    * post build configuration manager */
   if (TmpCfgPtr == NULL_PTR)
   {
      PbcfgM_ModuleConfigPtrType PbcfgMConfigPtr = NULL_PTR;

      (void)PbcfgM_GetConfig(
            COM_MODULE_ID,
            0U,
            &PbcfgMConfigPtr);

      TmpCfgPtr = (P2CONST(Com_ConfigType, AUTOMATIC, COM_APPL_CONST)) PbcfgMConfigPtr;

   }

#endif /* (COM_PBCFGM_SUPPORT_ENABLED == STD_ON) */

#else /* COM_CONST_CFG_ADDRESS_ENABLE == STD_OFF */
         Com_gConfigPtr;

   DBG_COM_INIT_ENTRY(Com_ConfigPtr);

   /* Deviation MISRA-4 */
   TS_PARAM_UNUSED(Com_ConfigPtr);
#endif /* COM_CONST_CFG_ADDRESS_ENABLE */

#if (COM_DEV_ERROR_DETECT == STD_ON)

   /* check that configuration pointer is valid */
   /* Deviation MISRA-1 */
   if (E_OK != Com_IsValidConfig(TmpCfgPtr))
   {
      COM_DET_REPORTERROR(COM_E_PARAM_POINTER, COMServiceId_Init);
   }
   else

#endif /* COM_DEV_ERROR_DETECT */

   {

      uint8 hlp_retval = E_OK;

#if (COM_CONST_CFG_ADDRESS_ENABLE == STD_OFF)
      /* save configuration pointer */
      Com_gConfigPtr = TmpCfgPtr;
#endif /* COM_CONST_CONFIG_ADDRESS */

      /* Initialize Rx-Pdus */
      for (pdu = 0; (pdu < TmpCfgPtr->ComRxIPduArraySize); pdu++)
      {
         hlp_retval |= Com_EB_InitRxIPdu(pdu);
      }

      /* Initialize Tx-Pdus */
      for (pdu = 0; (pdu < TmpCfgPtr->ComTxIPduArraySize); pdu++)
      {
         hlp_retval |= Com_EB_InitTxIPdu(pdu);
      }


#if (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON)
      {
         ComIPduRefType i;

         ComIPduRefType numBytes = ((Com_gConfigPtr->ComCbkTxAckDeferredListMax + 7U) / 8U);

         /* Check for deferred confirmations */
         for (i = Com_gConfigPtr->ComCbkTxAckDeferredStatusBase;
               i < (Com_gConfigPtr->ComCbkTxAckDeferredStatusBase + numBytes);
               i++)
         {
            /* clear the byte */
            Com_gDataMemPtr[i] = 0U;
         }
      }
#endif /* (COM_TX_CONFIRMATIONS_DEFERED_AVAILABLE == STD_ON) */

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_OFF)
      TS_PARAM_UNUSED(hlp_retval);
#else
      /* CHECK: NOPARSE */
      if (E_OK == hlp_retval)
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
      {
         /*
          * tag module as initialized
          */
         Com_InitStatus = COM_EB_INIT;
      }

   }

   DBG_COM_INIT_EXIT(Com_ConfigPtr);
}                               /* Com_Init */


/* stop code section declaration */
#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif


/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

