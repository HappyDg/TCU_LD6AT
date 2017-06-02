/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined DCM_API_CFG_H)
#define DCM_API_CFG_H

/*==================[includes]===================================================================*/

#include <Dcm_Types.h>
/*==================[macros]=====================================================================*/


#define DCM_USERSSVC_0X28_0X00
#define DCM_USERSSVC_0X28_0X03
/*==================[type definitions]===========================================================*/

/*==================[external function declarations]=============================================*/
#define DCM_START_SEC_CALLOUT_CODE
#include <MemMap.h>






extern FUNC(Std_ReturnType, DCM_APPL_CODE) UDS_bEnableRxAndTx(
Dcm_OpStatusType OpStatus,
P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

extern FUNC(Std_ReturnType, DCM_APPL_CODE) UDS_bDisableRxAndTx(
Dcm_OpStatusType OpStatus,
P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);


#define DCM_STOP_SEC_CALLOUT_CODE
#include <MemMap.h>
/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* if !defined( DCM_API_CFG_H ) */
/*==================[end of file]================================================================*/
