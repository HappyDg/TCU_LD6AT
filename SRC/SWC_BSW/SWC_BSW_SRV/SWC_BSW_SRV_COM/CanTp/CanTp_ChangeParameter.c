/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include <CanTp_Trace.h>
#include <TSAutosar.h>         /* EB specific standard types */
#include <ComStack_Types.h>    /* ComStack types */
#include <CanTp_Api.h>         /* Module public API, config dependent */
#include <CanTp_Cfg.h>         /* CANTP_DEV_ERROR_DETECT, CANTP_CHANGE_PARAMETER_REQ_API */
#include <CanTp_Internal.h>    /* internal macros and variables */
#if(CANTP_JUMPTABLE_SUPPORT == STD_ON)
#include <CanTp_EntryTable.h>  /* CanTp entry jumptable */
#endif /* CANTP_JUMPTABLE_SUPPORT == STD_ON */

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
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

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_START_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

#if(CANTP_PROVIDE_API_FUNCTIONS == STD_ON)

#if(CANTP_CHANGE_PARAMETER_REQ_API == STD_ON)

FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter
(
  PduIdType Id,
  TPParameterType Parameter,
  uint16 Value
)
#if(CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT)
{
  Std_ReturnType ret_result = E_NOT_OK;

  DBG_CANTP_CHANGEPARAMETER_ENTRY(Id, Parameter, Value);
#if(CANTP_DEV_ERROR_DETECT == STD_ON)

  if(CanTp_InitVars.State != CANTP_ON)
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_CHANGEPARAMETER,
                            CANTP_E_UNINIT
                          );
  }
  /* Check Id range - possible DET and return on error */
  else if(Id >= CanTp_CfgPtr->NumberRxNSdus)
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_CHANGEPARAMETER,
                            CANTP_E_PARAM_ID
                          );
  }
  else if((Parameter != TP_STMIN) && (Parameter != TP_BS))
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_CHANGEPARAMETER,
                            CANTP_E_PARAM_ID
                          );
  }
  /* !LINKSTO CanTp.ASR40.CANTP305_3, 1 */
  /* BS has a valid range of 0 - 255. STmin has a valid range of 0-127 and 241 - 249. */
  else if(((Parameter == TP_BS) && (Value > 255U))
          || ((Parameter == TP_STMIN)
              && ((Value > 249U) || ((Value > 127U) && (Value < 241U)))
             )
         )
  {
    CANTP_DET_REPORT_ERROR(
                            CANTP_MODULE_ID,
                            CANTP_INSTANCE_ID,
                            CANTP_API_CHANGEPARAMETER,
                            CANTP_E_PARAM_ID
                          );
  }
  else
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
  {
    const uint8  Channel = CANTP_CFG_GET_RXNSDU_CONFIG(Id).Channel;
    P2VAR(CanTp_ChannelType, AUTOMATIC, CANTP_VAR) ChannelPtr;

    /* verify that configured Rx channel is free - get the channel pointer first */
    ChannelPtr = &CanTp_Channel[Channel];

    CANTP_ENTER_CRITICAL_SECTION();

    if(CANTP_CH_GET_MODE(ChannelPtr) == CANTP_CH_MODE_RX)
    {
      /* Check if the actual N-Sdu on the channel is the requested N-Sdu to be
         changed.
       */
      if(ChannelPtr->NSduId == Id)
      {
        /* !LINKSTO CanTp.ASR40.CANTP304_1, 1 */
        /* Don't change parameter when reception is in progress.*/
        ret_result = E_NOT_OK;
      }
      else
      {
        /* Channel is in Rx mode for another N-Sdu. Continue.*/
        ret_result = E_OK;
      }
    }
    else
    {
      /* Change parameter when no reception is in progress. */
      ret_result = E_OK;
    }

    if(E_OK == ret_result)
    {
      /* All validation checks done.
         Now it is possible to change the requested parameter.
       */
      if(Parameter == TP_BS)
      {
        /* Change Block size. Id = NSduId */
        CANTP_SET_RX_PDU_BLOCK_SIZE(Id, Value);
      }
      else
      {
        /* Change separation time. Id = NSduId */
        CANTP_SET_RX_PDU_ST_MIN(Id, Value);
      }
    }
    CANTP_LEAVE_CRITICAL_SECTION();
  }

  DBG_CANTP_CHANGEPARAMETER_EXIT(ret_result, Id, Parameter, Value);

  return ret_result;
}/* CanTp_ChangeParameter() */

#else /* => CANTP_JUMPTABLE_MODE == CANTP_JUMPTABLE_CLIENT */
{
  Std_ReturnType ret_result = E_NOT_OK;
  DBG_CANTP_CHANGEPARAMETER_ENTRY(Id, Parameter, Value);
  ret_result = (CanTp_EntryTablePtr->ChangeParameter)(Id, Parameter, Value);
  DBG_CANTP_CHANGEPARAMETER_EXIT(ret_result, Id, Parameter, Value);
  return ret_result;
}
#endif /* CANTP_JUMPTABLE_MODE != CANTP_JUMPTABLE_CLIENT */

#endif /* CANTP_CHANGE_PARAMETER_REQ_API == STD_ON */

#endif /* CANTP_PROVIDE_API_FUNCTIONS == STD_ON */

#if(TS_MERGED_COMPILE == STD_OFF)
#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
#endif /* TS_MERGED_COMPILE == STD_OFF */

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/
