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
 * MISRA-1) Deviated Rule: 14.6 (required)
 * For any iteration statement there shall be at most one break statement
 * used for loop termination.
 *
 * Reason:
 * Multiple breaks are used to reduce clutter of functions if all of the following
 * conditions take place:
 * a) The immediately abort of the loop is required because data are invalid and
 *    may lead to inconsistent code exection
 * b) The function is highly cluttered with preprocessor statements. Additional branches
 *    might lead to unreadable code.
 *
 * MISRA-2) Deviated Rule: 18.4 (required)
 * "Unions shall not be used."
 *
 * Reason:
 * Is used for endianness conversion.
 *
 * MISRA-3) Deviated Rule: 11.3 (advisory)
 * "A cast should not be performed between a pointer type and an integral type."
 *
 * Reason:
 * Actually this is not a cast between a pointer and a integral type, since 0
 * is null pointer constant.
 *
 * MISRA-4) Deviated Rule: 6.3 (advisory)
 * "'typedefs' that indicate size and signedness should be used in place of the basic types."
 *
 * Reason:
 * In this case variables are casted to a natural integral type since, the value is further used
 * for purposes where natural types are most efficient (e.g. indexing).
 *
 * MISRA-5) Deviated Rule: 17.4 (required)
 * "Array indexing shall be the only allowed form of pointer arithmetic."
 *
 * Reason:
 * Callculation is needed to get the index of the Signal Group to which the
 * Group Signal belongs.
 */

/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* module internal stuff */
#include <Com_Types.h>          /* types of configuration elements */
#include <Com_Filter.h>         /* Filter functions */
#include <Com_Core_RxIPdu.h>    /* RxIPdu functions */

#include <Com_Rules.h>

#include <Com_Core_TxSignalGroup.h>  /* (group)signal(group) functions */

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* Det API */
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */


#if ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON))
#include <Com_Core_TM.h> /* Transmission Mode functions */
#endif /* ((COM_TM_AVAILABLE == STD_ON) || (COM_TMS_ENABLE == STD_ON)) */

#include <Com_Core_TxSignalGroup.h>  /* (group)signal(group) functions */
#include <Com_Core_TxSignal.h>  /* signal functions */


/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

/*==================[internal function declarations]=========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

#if (COM_SIGNAL_GW_ENABLE == STD_ON)


/** \brief Com_EB_RouteSignalHelper - routes a signal (or signal described
 * with GWDescription)
 * This function checks if the signal is invalidated. If yes the invalid value
 * of the source object is sent. If not it copies the value from source and
 * sends the object.
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * - the signal must be ready to be gated (has to be updated)
 * \param[in] SrcSignalPtr - reference to the configuration of the source object
 * \param[in] SrcIPduPtr - reference to the configuration of the source I-Pdu
 * \param[in] GWSourcePtr - reference to routing source configuration
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSignalHelper
(
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SrcSignalPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) SrcIPduPtr,
   P2CONST(ComGWSourceType, AUTOMATIC, COM_APPL_CONST) GWSourcePtr
);


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_RouteSG_2_SG - routes a signal group to a signal group
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * \param[in] GWDestinationPtr - reference to the configuration of the destination
 * \param[in] PosInSrcIPdu - index in RAM where buffer of source SG starts
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSG_2_SG
(
   P2CONST(ComGWDestinationType, AUTOMATIC, COM_APPL_CONST) GWDestinationPtr,
   ComRAMIdxType PosInSrcIPdu
);
/** \brief Com_EB_RouteSignalGroup - routes a signal group
 * This function checks if the signal group is is updated. If no update bit is configured
 * this is always the case, otherwise the update bit is checked. If signal groups
 * shall routed, the destination is updated.
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * \param[in] SrcIPduPtr - reference to the configuration of the source I-Pdu
 * \param[in] GWSourcePtr - reference to routing source configuration
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSignalGroup
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) SrcIPduPtr,
   P2CONST(ComGWSourceType, AUTOMATIC, COM_APPL_CONST) GWSourcePtr
);
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

/** \brief Com_EB_RouteSignal - routes a signal
 * This function checks if the signal is invalidated. If yes the invalid value
 * of the source object is sent. If not it copies the value from source and
 * sends the object.
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * - the signal must be ready to be gated (has to be updated)
 * \param[in] SrcIPduPtr - reference to the configuration of the source I-Pdu
 * \param[in] GWSourcePtr - reference to routing source configuration
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSignal
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) SrcIPduPtr,
   P2CONST(ComGWSourceType, AUTOMATIC, COM_APPL_CONST) GWSourcePtr
);

#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

#if (COM_SIGNAL_GW_ENABLE == STD_ON)

/** \brief Com_EB_RouteSignalHelper - routes a signal (or signal described
 * with GWDescription)
 * This function checks if the signal is invalidated. If yes the invalid value
 * of the source object is sent. If not it copies the value from source and
 * sends the object.
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * - the signal must be ready to be gated (has to be updated)
 * \param[in] SrcSignalPtr - reference to the configuration of the source object
 * \param[in] SrcIPduPtr - reference to the configuration of the source I-Pdu
 * \param[in] GWSourcePtr - reference to routing source configuration
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSignalHelper
(
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SrcSignalPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) SrcIPduPtr,
   P2CONST(ComGWSourceType, AUTOMATIC, COM_APPL_CONST) GWSourcePtr
)
{
#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
   boolean proceedProcessing = TRUE;
#endif

   /* pointer to the configuration of the IPdu to which the destination signal (Tx) belongs */
   P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) DestIPduPtr;

   ComIPduRefType DestPduId; /* Id of the IPdu to which the the destination signal belongs */

   /* union for the holding the value of the source signal */
   /* Deviation MISRA-2 */
   union valueuniontype
   {
      uint32 valuint32;
      uint16 valuint16;
      uint8 valuint8;
      boolean valboolean;
   } valueunion;

   /* Pointer to the source data */
   P2VAR(void, AUTOMATIC, COM_VAR_NOINIT) SignalDataPtr = &valueunion.valuint8;

   ComGWDestinationRefType i; /* iteration variable for destination object */

   /* reference to the configuration of the destination object */
   P2CONST(ComGWDestinationType, AUTOMATIC, COM_APPL_CONST) GWDestinationPtr;

   /* Get the signal type of the source signal */
   Com_TS_SignalTypeType SignalType = COM_GET_RX_SIGNAL_SIGNAL_TYPE(SrcSignalPtr);

   DBG_COM_EB_ROUTESIGNALHELPER_ENTRY(SrcSignalPtr,SrcIPduPtr,GWSourcePtr);

#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
   if (SignalType != COM_UINT8_N)
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */
   {

      ComCommonReadPropType ComReadProp;
      Com_EB_CreateReadProp(
         &ComReadProp,
         SrcSignalPtr,
         SrcIPduPtr
#if (COM_VALUE_INIT_REPLACE == STD_ON)
         ,FALSE
#endif /* (COM_VALUE_INIT_REPLACE == STD_ON) */
      );

      /* read the value from the I-Pdu */
      valueunion.valuint32 = Com_EB_ReadFromPduOrShadowBuffer(&ComReadProp);

      /* get the address of the value */
      switch (SignalType)
      {
      case COM_BOOLEAN:
         valueunion.valboolean = (boolean) valueunion.valuint32;
         SignalDataPtr = &valueunion.valboolean;
         break;

      case COM_UINT8:
      case COM_SINT8:
         valueunion.valuint8 = (uint8) valueunion.valuint32;
         SignalDataPtr = &valueunion.valuint8;
         break;

      case COM_UINT16:
      case COM_SINT16:
         valueunion.valuint16 = (uint16) valueunion.valuint32;
         SignalDataPtr = &valueunion.valuint16;
         break;

      case COM_UINT32:
      case COM_SINT32:
         SignalDataPtr = &valueunion.valuint32;
         break;

         /* CHECK: NOPARSE */
      default:
      {
#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
         COM_UNREACHABLE_CODE_ASSERT(COMServiceId_MainFunctionRouteSignals);
         proceedProcessing = FALSE;
#endif /* (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON) */
         break;
      }
         /* CHECK: PARSE */
      }                /* switch (SignalType) */


   }                         /* if (SignalType != COM_UINT8_N) */
#if (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON)
   else
   {                         /* signal has type UINT8_N */
      /* no need to convert endianness UINT8_N is Opaque */
#if (COM_SIGNAL_BYTE_ALIGN == STD_ON)
      SignalDataPtr =
            &Com_gDataMemPtr[(SrcIPduPtr->ComIPduValueRef +
                  SrcSignalPtr->RxBasicParam.ComSignalPositionInByte)];
#elif (COM_SIGNAL_BYTE_ALIGN == STD_OFF)
      /* signal UINT8_N is byte aligned, there is no need to copy it */
      SignalDataPtr =
            &Com_gDataMemPtr[(SrcIPduPtr->ComIPduValueRef +
                  SrcSignalPtr->RxBasicParam.ComSignalPositionInBit)];
#endif /* (COM_SIGNAL_BYTE_ALIGN == STD_ON) */

   }                         /* signal has type UINT8_N */
#endif /* (COM_SIGNAL_TYPE_UINT8_N_ENABLE == STD_ON) */


#if (COM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
   /* CHECK: NOPARSE */
   if (TRUE == proceedProcessing)
   /* CHECK: PARSE */
#endif
   {
      /* loop over all destination  */
      for (i = GWSourcePtr->ComGWDestinationFirstRef;
            (i < (GWSourcePtr->ComGWDestinationFirstRef + GWSourcePtr->ComGWDestinationNumRef));
            i++)
      {
         /* get the configuration of the destination object */
         /* Deviation MISRA-3 */
         /* Deviation MISRA-4 */
         GWDestinationPtr = COM_GET_CONFIG_ELEMENT(ComGWDestinationType,
               (Com_gConfigPtr->ComGWDestinationRef), i);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         /* check the configuration */
         if (NULL_PTR == GWDestinationPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == GWDestinationPtr),
                  COMServiceId_MainFunctionRouteSignals);
            break;
         }
         if (GWDestinationPtr->ComConfigCheckData != COM_CONFIG_CHECK_GW_DESTINATION)
         {
            COM_PRECONDITION_ASSERT(
                  (GWDestinationPtr->ComConfigCheckData == COM_CONFIG_CHECK_GW_DESTINATION),
                  COMServiceId_MainFunctionRouteSignals);
            /* Deviation MISRA-1 */
            break;
         }
         /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

         /* GWDestinationPtr is valid */
         switch (GWDestinationPtr->ComGWDestinationSelect)
         {
         case COM_GW_SIGNAL:
         {
            /* set the configuration of the destination signal */
            /* Deviation MISRA-3 */
            /* Deviation MISRA-4 */
            CONSTP2CONST(ComTxSignalType, AUTOMATIC, COM_APPL_CONST) DestSignalPtr =
                  COM_GET_CONFIG_ELEMENT(ComTxSignalType, GWDestinationPtr->ComGWDestinationRef, 0U);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
            /* CHECK: NOPARSE */
            /* Check the configuration */
            if (NULL_PTR == DestSignalPtr)
            {
               COM_PRECONDITION_ASSERT(
                     (NULL_PTR == DestSignalPtr),
                     COMServiceId_MainFunctionRouteSignals);
               break;
            }
            if (DestSignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIGNAL)
            {
               COM_PRECONDITION_ASSERT(
                     (DestSignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_SIGNAL),
                     COMServiceId_MainFunctionRouteSignals);
               /* Deviation MISRA-1 */
               break;
            }
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

            /* DestSignalPtr is valid */

            /* get the Id and the reference of the I-Pdu to which the destination signal belongs */
            DestPduId = DestSignalPtr->TxBasicParam.ComIPduRef;

            /* get the configuration of the destination I-Pdu */
            /* Deviation MISRA-3 */
            /* Deviation MISRA-4 */
            DestIPduPtr =
                  COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, DestPduId);


            /* Send the signal; ignore the error; error could be
             * COM_SERVICE_NOT_AVAILABLE in case the I-Pdu is stopped */
            (void)Com_EB_SendSignal(
                  DestSignalPtr,
                  DestIPduPtr,
                  DestPduId,
                  SignalDataPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
                  ,TRUE
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
            );

            break;
         }                   /* case COM_GW_SIGNAL */

         /* CHECK: NOPARSE */
         default:
            COM_UNREACHABLE_CODE_ASSERT(COMServiceId_MainFunctionRouteSignals);
            break;
            /* CHECK: PARSE */
         }                   /* switch (GWDestinationPtr->ComGWDestinationType) */
      } /* for (i = GWSourcePtr->ComGWDestinationFirstRef;
              (i < GWSourcePtr->ComGWDestinationFirstRef + GWSourcePtr->ComGWDestinationNumRef);
              i++) */
   }                            /* (TRUE == proceedProcessing) */


   DBG_COM_EB_ROUTESIGNALHELPER_EXIT(SrcSignalPtr,SrcIPduPtr,GWSourcePtr);
}                               /* Com_EB_RouteSignalHelper */


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)

/** \brief Com_EB_RouteSG_2_SG - routes a signal group to a signal group
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * \param[in] GWDestinationPtr - reference to the configuration of the destination
 * \param[in] PosInSrcIPdu - index in RAM where buffer of source SG starts
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSG_2_SG
(
   P2CONST(ComGWDestinationType, AUTOMATIC, COM_APPL_CONST) GWDestinationPtr,
   ComRAMIdxType PosInSrcIPdu
)
{
   /* Pointer to the configuration destination signal */
   P2CONST(ComTxSignalGroupType, AUTOMATIC, COM_APPL_CONST) DestSignalGPtr;

   /* set configuration destination signal */
   /* Deviation MISRA-3 */
   /* Deviation MISRA-4 */
   DestSignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComTxSignalGroupType,
               GWDestinationPtr->ComGWDestinationRef, 0U);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   /* CHECK: NOPARSE */
   /* Check the configuration */
   if (NULL_PTR == DestSignalGPtr)
   {
      COM_PRECONDITION_ASSERT(
            (NULL_PTR == DestSignalGPtr),
            COMServiceId_MainFunctionRouteSignals);
   }
   else if (DestSignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_TX_SIG_GROUP)
   {
      COM_PRECONDITION_ASSERT(
            (DestSignalGPtr->ComConfigCheckData == COM_CONFIG_CHECK_TX_SIG_GROUP),
            COMServiceId_MainFunctionRouteSignals);
   }
   else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
   {
      /* DestSignalGPtr is valid */

      /* Id of the signal group */
      ComSignalGroupRefType SignalGId;

      /* Id of the IPdu to which the the destination signal belongs */
      ComIPduRefType DestPduId;

      /* pointer to the configuration of the IPdu to which the destination signal (Tx) belongs */
      P2CONST(ComTxIPduType, AUTOMATIC, COM_APPL_CONST) DestIPduPtr;

      /* calculate the Id of the Signal Group */
      /* Deviation MISRA-3 */
      /* Deviation MISRA-4 */
      /* Deviation MISRA-5 */
      COM_GET_TX_SG_ID(SignalGId, DestSignalGPtr);

      /* get the Id and the reference of the I-Pdu to which the destination signal belongs */
      DestPduId = DestSignalGPtr->ComIPduRef;

      /* get the configuration of the destination I-Pdu */
      /* Deviation MISRA-3 */
      /* Deviation MISRA-4 */
      DestIPduPtr =
            COM_GET_CONFIG_ELEMENT(ComTxIPduType, Com_gConfigPtr->ComTxIPduRef, DestPduId);


      (void)Com_EB_SendSignalGroupArray(
            &Com_gDataMemPtr[(PosInSrcIPdu)],
#if (COM_TMS_ENABLE == STD_ON)
            SignalGId,
#endif /* (COM_TMS_ENABLE == STD_ON) */
            DestSignalGPtr,
            DestPduId,
            DestIPduPtr
#if (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON)
            ,TRUE
#endif /* (COM_SENDUPONAPICALL_AND_SIGGW == STD_ON) */
            );

   }             /* DestSignalGPtr is valid */

}                               /* Com_EB_RouteSG_2_SG */

/** \brief Com_EB_RouteSignalGroup - routes a signal group
 * This function checks if the signal group is is updated. If no update bit is configured
 * this is always the case, otherwise the update bit is checked. If signal groups
 * shall routed, the destination is updated.
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * \param[in] SrcIPduPtr - reference to the configuration of the source I-Pdu
 * \param[in] GWSourcePtr - reference to routing source configuration
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSignalGroup
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) SrcIPduPtr,
   P2CONST(ComGWSourceType, AUTOMATIC, COM_APPL_CONST) GWSourcePtr
)
{
   /* reference to the source (Rx) signal group */
   /* Deviation MISRA-3 */
   /* Deviation MISRA-4 */
   CONSTP2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SrcSignalGPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalGroupType, GWSourcePtr->ComGWSourceRef, 0U);

   ComGWDestinationRefType i; /* iteration variable for destination object */

   /* reference to the configuration of the destination object */
   P2CONST(ComGWDestinationType, AUTOMATIC, COM_APPL_CONST) GWDestinationPtr;

   /* The starting position of the value of the signal group is the position
    * of source signal group within the source I-Pdu
    * plus the starting position of the source I-Pdu in the RAM */
   const ComRAMIdxType PosInSrcIPdu =
         (ComRAMIdxType)(SrcSignalGPtr->ComSignalPositionInByte + SrcIPduPtr->ComIPduValueRef);

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
   uint8 SignalUpdated = 1U; /* value of update bit (if no update bit is
   configured, the signal shall always be gated) */
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */
   DBG_COM_EB_ROUTESIGNALGROUP_ENTRY(SrcIPduPtr,GWSourcePtr);
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   /* CHECK: NOPARSE */
   /* Check the configuration */
   if (NULL_PTR == SrcSignalGPtr)
   {
      COM_PRECONDITION_ASSERT(
            (NULL_PTR == SrcSignalGPtr),
            COMServiceId_MainFunctionRouteSignals);
   }
   else if (SrcSignalGPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_SIG_GROUP)
   {
      COM_PRECONDITION_ASSERT(
            (SrcSignalGPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_SIG_GROUP),
            COMServiceId_MainFunctionRouteSignals);
   }
   else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
   {

      /* SrcSignalGPtr is valid */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if(COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)
      /* check if the update bit is configured */
      if (COM_GET_RX_SIGNAL_GROUP_UPDATE_BIT(SrcSignalGPtr) == COM_UPDATE_BIT_PRESENT)
#endif /* (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
      {

         /* The signal group has the update bit configured -> read it */
         TS_GetBit(
               &Com_gDataMemPtr[(SrcIPduPtr->ComIPduValueRef +
                     (SrcSignalGPtr->ComUpdateBitPositionInBit / 8U))],
                     (SrcSignalGPtr->ComUpdateBitPositionInBit % 8U),
                     uint8,
                     SignalUpdated);
      }

      if (1U == SignalUpdated)
#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */
      {                            /* signal group is gated */
         /* either no update bit is configured or the update bit is set */


         /* loop over all destination  */
         for (i = GWSourcePtr->ComGWDestinationFirstRef;
               (i < (GWSourcePtr->ComGWDestinationFirstRef + GWSourcePtr->ComGWDestinationNumRef));
               i++)
         {
            /* get the configuration of the destination object */
            /* Deviation MISRA-3 */
            /* Deviation MISRA-4 */
            GWDestinationPtr = COM_GET_CONFIG_ELEMENT(ComGWDestinationType,
                  (Com_gConfigPtr->ComGWDestinationRef), i);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
            /* CHECK: NOPARSE */
            /* check the configuration */
            if (NULL_PTR == GWDestinationPtr)
            {
               COM_PRECONDITION_ASSERT(
                     (NULL_PTR == GWDestinationPtr),
                     COMServiceId_MainFunctionRouteSignals);
            }
            else if (GWDestinationPtr->ComConfigCheckData != COM_CONFIG_CHECK_GW_DESTINATION)
            {
               COM_PRECONDITION_ASSERT(
                     (GWDestinationPtr->ComConfigCheckData == COM_CONFIG_CHECK_GW_DESTINATION),
                     COMServiceId_MainFunctionRouteSignals);
            }
            else
               /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
            {
               /* GWDestinationPtr is valid */

               switch (GWDestinationPtr->ComGWDestinationSelect)
               {
               case COM_GW_SIGNAL_GROUP:
               {
                  Com_EB_RouteSG_2_SG(GWDestinationPtr, PosInSrcIPdu);
                  break;
               }                /* case COM_GW_SIGNAL_GROUP: */

               /* CHECK: NOPARSE */
               default:
                  COM_UNREACHABLE_CODE_ASSERT(COM_INTERNAL_API_ID);
                  break;
                  /* CHECK: PARSE */
               }                /* switch (GWDestinationPtr->ComGWDestinationType) */

            }                   /* GWDestinationPtr is valid */

         } /* for (i = GWSourcePtr->ComGWDestinationFirstRef;
               (i < GWSourcePtr->ComGWDestinationFirstRef + GWSourcePtr->ComGWDestinationNumRef);
               i++) */
      }                         /* signal group is gated */
   }                            /* SrcSignalGPtr is valid */

   DBG_COM_EB_ROUTESIGNALGROUP_EXIT(SrcIPduPtr,GWSourcePtr);
}                               /* Com_EB_RouteSignalGroup */

#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


/** \brief Com_EB_RouteSignal - routes a signal
 * This function checks if the signal is invalidated. If yes the invalid value
 * of the source object is sent. If not it copies the value from source and
 * sends the object.
 * Preconditions:
 * - COM must be initialized
 * - SoureType of the GWSource has to be a signal
 * \param[in] SrcIPduPtr - reference to the configuration of the source I-Pdu
 * \param[in] GWSourcePtr - reference to routing source configuration
 * \retval None
 */
_COM_STATIC_ FUNC(void, COM_CODE) Com_EB_RouteSignal
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) SrcIPduPtr,
   P2CONST(ComGWSourceType, AUTOMATIC, COM_APPL_CONST) GWSourcePtr
)
{
   /* reference to the source (Rx) signal */
   /* Deviation MISRA-3 */
   /* Deviation MISRA-4 */
   CONSTP2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SrcSignalPtr =
         COM_GET_CONFIG_ELEMENT(ComRxSignalType, GWSourcePtr->ComGWSourceRef, 0);


#if ((COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) || \
      (COM_SIGGW_RX_FILTER_ENABLE == STD_ON))
   /* Signal shall be gated if:
    * - the update bit is set (when update bits are enabled and configured)
    * - the the filter evaluates to TRUE (when SigGWFilter is enabled)
    * - if neither an update bit nor a GW Filter is configured */
   uint8 GateSignal = 1U;


#endif /* ((COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) || \
      (COM_SIGGW_RX_FILTER_ENABLE == STD_ON)) */
   DBG_COM_EB_ROUTESIGNAL_ENTRY(SrcIPduPtr,GWSourcePtr);
#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
   /* CHECK: NOPARSE */
   /* Check the configuration */
   if (NULL_PTR == SrcSignalPtr)
   {
      COM_PRECONDITION_ASSERT(
            (NULL_PTR == SrcSignalPtr),
            COMServiceId_MainFunctionRouteSignals);
   }
   else if (SrcSignalPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_SIGNAL)
   {
      COM_PRECONDITION_ASSERT(
            (SrcSignalPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_SIGNAL),
            COMServiceId_MainFunctionRouteSignals);
   }
   else
      /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */

   {

#if (COM_FILTER_RECEIVER_ENABLE == STD_ON)
#if (COM_SIGGW_RX_FILTER_ENABLE == STD_ON)
      if (SrcSignalPtr->ComSignalSigGWFlagBit != COM_SIGNAL_INVALID)
      {
         /* check if the signal shall be routed (filter evaluates to TRUE) */
         TS_GetBit(COM_RX_SIGNAL_SIG_GW_FLAG_ADDRESS(SrcSignalPtr),
               COM_RX_SIGNAL_SIG_GW_FLAG_BIT(SrcSignalPtr), uint8, GateSignal);

         /* clear the flag */
         TS_AtomicClearBit_8(COM_RX_SIGNAL_SIG_GW_FLAG_ADDRESS(SrcSignalPtr),
            COM_RX_SIGNAL_SIG_GW_FLAG_BIT(SrcSignalPtr));

      }
      else
#endif /* (COM_SIGGW_RX_FILTER_ENABLE == STD_ON) */
#endif /* (COM_FILTER_RECEIVER_ENABLE == STD_ON) */
      {
         /* the signal has no filter configured/enabled -> check the update bit */
#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)
#if (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL)

         /* check if signal has update bit */
         if (COM_GET_RX_SIGNAL_UPDATE_BIT(SrcSignalPtr) == COM_UPDATE_BIT_PRESENT)
#endif /* (COM_UPDATE_BIT_RX_CONFIG == COM_UPDATE_BIT_INDIVIDUAL) */
         {

            /* get the value of the update bit */
            TS_GetBit(&Com_gDataMemPtr[(SrcIPduPtr->ComIPduValueRef +
                  (SrcSignalPtr->RxBasicParam.ComUpdateBitPositionInBit / 8U))],
                  (SrcSignalPtr->RxBasicParam.ComUpdateBitPositionInBit % 8U),
                  uint8,
                  GateSignal);

         }

#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */

      }



#if ((COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) || \
      (COM_SIGGW_RX_FILTER_ENABLE == STD_ON))
      /* check if the signal shall be gated */
      if (GateSignal == 1U)
#endif /* ((COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) || \
      (COM_SIGGW_RX_FILTER_ENABLE == STD_ON)) */
      {
         /* the signal has to be gated */
         /* call the signal routing function */
         Com_EB_RouteSignalHelper(SrcSignalPtr, SrcIPduPtr, GWSourcePtr);
      }
   }

   DBG_COM_EB_ROUTESIGNAL_EXIT(SrcIPduPtr,GWSourcePtr);
}                               /* Com_EB_RouteSignal */


#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */

/** \brief Com_MainFunctionTx - handle cyclic Signal Gateway tasks
 * This function handles cyclic receiving and sending (group)signals(group)
 * for the Signal Gateway functionality (SigGW).
 * Preconditions:
 * - COM must be initialized
 * \param[in] None
 * \retval None
 */

FUNC(void, COM_CODE) Com_MainFunctionRouteSignals
(
   void
)
{

   DBG_COM_MAINFUNCTIONROUTESIGNALS_ENTRY();
#if (COM_SIGNAL_GW_ENABLE == STD_ON)
   if (Com_InitStatus == COM_EB_INIT)
   {

      uint16 sigGWRxPduRef; /* iteration variable */
      ComGWSourceRefType sigGWSourceRef; /* iteration variable */
      ComIPduRefType IPduId; /* id of an Rx I-Pdu with gated (group)signal (group) */
      /* reference to the configuration of Rx-Ipdu */
      P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr;

      /* reference to a routing table entry */
      P2CONST(ComGWSourceType, AUTOMATIC, COM_APPL_CONST) GWSourcePtr;

      uint8 BitRes; /* variable for SigGW Flags */

      for (sigGWRxPduRef = 0U;
            sigGWRxPduRef < Com_gConfigPtr->ComSigGWRxIPduArraySize;
            sigGWRxPduRef++)
      {
         /* get Id of IPdu */
         /* Deviation MISRA-3, MISRA-4 <+7> */
         IPduId = (ComIPduRefType) * (COM_GET_CONFIG_ELEMENT
               (ComIPduRefType,(Com_gConfigPtr->ComSigGWRxIPduListRef), sigGWRxPduRef));

         /* get RxPduId configuration reference */
         /* Deviation MISRA-3 */
         /* Deviation MISRA-4 */
         IPduPtr = COM_GET_CONFIG_ELEMENT(ComRxIPduType, (Com_gConfigPtr->ComRxIPduRef), IPduId);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
         /* CHECK: NOPARSE */
         /* Check the configuration */
         if (NULL_PTR == IPduPtr)
         {
            COM_PRECONDITION_ASSERT(
                  (NULL_PTR == IPduPtr),
                  COMServiceId_MainFunctionRouteSignals);
         }
         else if (IPduPtr->ComConfigCheckData != COM_CONFIG_CHECK_RX_IPDU)
         {
            COM_PRECONDITION_ASSERT(
                  (IPduPtr->ComConfigCheckData == COM_CONFIG_CHECK_RX_IPDU),
                  COMServiceId_MainFunctionRouteSignals);
         }
         else
            /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
         {
            /* IPduPtr is valid */

            /* check if SigGWFlag is set */
            TS_GetBit(COM_RX_IPDU_SIG_GW_FLAG_ADDRESS(IPduPtr),
                  COM_RX_IPDU_SIG_GW_FLAG_BIT(IPduPtr), uint8, BitRes);

            if(BitRes == 1U)
            {
               /* the I-Pdu has (group)signals(group) which have to be gated now */
               /* get the Routing Table */

               /* clear the SigGWFlag*/
               TS_AtomicClearBit_8(COM_RX_IPDU_SIG_GW_FLAG_ADDRESS(IPduPtr),
                     COM_RX_IPDU_SIG_GW_FLAG_BIT(IPduPtr));

               for (sigGWSourceRef = IPduPtr->ComIPduGWSourceRefFirst;
                     sigGWSourceRef < (IPduPtr->ComIPduGWSourceRefFirst + IPduPtr->ComIPduGWSourceRefNum);
                     sigGWSourceRef++)
               {
                  /* get routing information */
                  /* Deviation MISRA-3 */
                  /* Deviation MISRA-4 */
                  GWSourcePtr = COM_GET_CONFIG_ELEMENT(ComGWSourceType,
                        (Com_gConfigPtr->ComGWSourceRef), sigGWSourceRef);

#if (COM_PRECONDITION_ASSERT_ENABLED == STD_ON)
                  /* CHECK: NOPARSE */
                  /* Check the configuration */
                  if (NULL_PTR == GWSourcePtr)
                  {
                     COM_PRECONDITION_ASSERT(
                           (NULL_PTR == GWSourcePtr),
                           COMServiceId_MainFunctionRouteSignals);
                  }
                  else if (GWSourcePtr->ComConfigCheckData != COM_CONFIG_CHECK_GW_SOURCE)
                  {
                     COM_PRECONDITION_ASSERT(
                           (GWSourcePtr->ComConfigCheckData == COM_CONFIG_CHECK_GW_SOURCE),
                           COMServiceId_MainFunctionRouteSignals);
                  }
                  else
                     /* CHECK: PARSE */
#endif /* (COM_PRECONDITION_ASSERT_ENABLED == STD_ON) */
                  {
                     /* GWSourcePtr is valid */

                     switch (GWSourcePtr->ComGWSourceSelect)
                     {
                     case COM_GW_SIGNAL:
                     {
                        /* the gated object is a signal, handle it */
                        Com_EB_RouteSignal(IPduPtr, GWSourcePtr);
                        break;
                     }                   /* case COM_GW_SIGNAL */
#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
                     case COM_GW_SIGNAL_GROUP:
                     {
                        /* the gated object is a signal group, handle it */
                        Com_EB_RouteSignalGroup(IPduPtr, GWSourcePtr);
                        break;
                     }                   /* case COM_GW_SIGNAL_GROUP */
#endif /* (COM_TX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */
                     /* CHECK: NOPARSE */
                     default:
                        COM_UNREACHABLE_CODE_ASSERT(COMServiceId_MainFunctionRouteSignals);
                        break;
                        /* CHECK: PARSE */
                     }          /* switch (GWSourcePtr->ComGWSourceSelect) */

                  }             /* GWSourcePtr is valid */

               } /* for (j = IPduPtr->ComIPduGwRoutingRefFirst;
                 j < (IPduPtr->ComIPduGwRoutingRefFirst + IPduPtr->ComIPduGwRoutingRefNum);
                 j++) */

            }                   /* if(BitRes == 1U) */

         }                      /* IPduPtr is valid */

      }                         /* (      for (sigGWRxPduRef = 0;
           sigGWRxPduRef < Com_gConfigPtr->ComSigGWRxIPduArraySize;
           sigGWRxPduRef++) */
   }                            /* if (Com_Status == COM_EB_INIT) */
#endif /* (COM_SIGNAL_GW_ENABLE == STD_ON) */

   DBG_COM_MAINFUNCTIONROUTESIGNALS_EXIT();
}                               /* Com_MainFunctionRouteSignals */

#if (TS_MERGED_COMPILE == STD_OFF)
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

