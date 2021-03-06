#if !defined(SCHM_PDUR_H)
#define SCHM_PDUR_H

/**
 * \file
 *
 * \brief AUTOSAR Rte
 *
 * This file contains the implementation of the AUTOSAR
 * module Rte.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

 /*
  * This file is the Module Interlink Header which contains the declarations relevant for that instance of a basic software module.
  *
  * This file has been automatically generated by
  * EB tresos AutoCore Rte Generator Version 6.1.53
  * on Mon Feb 16 10:44:19 GMT+02:00 2015. !!!IGNORE-LINE!!!
  */

 /* \addtogroup Rte Runtime Environment
  * @{ */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "Os.h"
/*==================[inclusions]=============================================*/

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#define SchM_Enter_PduR_CANTP_ACCESS_001() 

#define SchM_Exit_PduR_CANTP_ACCESS_001() ResumeAllInterrupts()

#define SchM_Enter_PduR_CANTP_ACCESS_002() SuspendAllInterrupts()

#define SchM_Exit_PduR_CANTP_ACCESS_002() ResumeAllInterrupts()

#define SchM_Enter_PduR_CANTP_ACCESS_003() SuspendAllInterrupts()

#define SchM_Exit_PduR_CANTP_ACCESS_003() ResumeAllInterrupts()

#define SchM_Enter_PduR_CANTP_ACCESS_004() SuspendAllInterrupts()

#define SchM_Exit_PduR_CANTP_ACCESS_004() ResumeAllInterrupts()

#define SchM_Enter_PduR_CANTP_ACCESS_005() SuspendAllInterrupts()

#define SchM_Exit_PduR_CANTP_ACCESS_005() ResumeAllInterrupts()

#define SchM_Enter_PduR_CANTP_ACCESS_006() SuspendAllInterrupts()

#define SchM_Exit_PduR_CANTP_ACCESS_006() ResumeAllInterrupts()

#define SchM_Enter_PduR_LINTP_ACCESS_001() SuspendAllInterrupts()

#define SchM_Exit_PduR_LINTP_ACCESS_001() ResumeAllInterrupts()

#define SchM_Enter_PduR_LINTP_ACCESS_002() SuspendAllInterrupts()

#define SchM_Exit_PduR_LINTP_ACCESS_002() ResumeAllInterrupts()

#define SchM_Enter_PduR_LINTP_ACCESS_003() SuspendAllInterrupts()

#define SchM_Exit_PduR_LINTP_ACCESS_003() ResumeAllInterrupts()

#define SchM_Enter_PduR_LINTP_ACCESS_004() SuspendAllInterrupts()

#define SchM_Exit_PduR_LINTP_ACCESS_004() ResumeAllInterrupts()

#define SchM_Enter_PduR_LINTP_ACCESS_005() SuspendAllInterrupts()

#define SchM_Exit_PduR_LINTP_ACCESS_005() ResumeAllInterrupts()

#define SchM_Enter_PduR_LINTP_ACCESS_006() SuspendAllInterrupts()

#define SchM_Exit_PduR_LINTP_ACCESS_006() ResumeAllInterrupts()

#define SchM_Enter_PduR_COM_ACCESS_001() SuspendAllInterrupts()

#define SchM_Exit_PduR_COM_ACCESS_001() ResumeAllInterrupts()

#define SchM_Enter_PduR_COM_ACCESS_002() SuspendAllInterrupts()

#define SchM_Exit_PduR_COM_ACCESS_002() ResumeAllInterrupts()

#define SchM_Enter_PduR_COM_ACCESS_003() SuspendAllInterrupts()

#define SchM_Exit_PduR_COM_ACCESS_003() ResumeAllInterrupts()

#define SchM_Enter_PduR_COM_ACCESS_004() SuspendAllInterrupts()

#define SchM_Exit_PduR_COM_ACCESS_004() ResumeAllInterrupts()

#define SchM_Enter_PduR_COM_ACCESS_005() SuspendAllInterrupts()

#define SchM_Exit_PduR_COM_ACCESS_005() ResumeAllInterrupts()

#define SchM_Enter_PduR_DCM_ACCESS_001() SuspendAllInterrupts()

#define SchM_Exit_PduR_DCM_ACCESS_001() ResumeAllInterrupts()

#define SchM_Enter_PduR_DCM_ACCESS_002() SuspendAllInterrupts()

#define SchM_Exit_PduR_DCM_ACCESS_002() ResumeAllInterrupts()

#define SchM_Enter_PduR_DCM_ACCESS_003() SuspendAllInterrupts()

#define SchM_Exit_PduR_DCM_ACCESS_003() ResumeAllInterrupts()

#define SchM_Enter_PduR_DCM_ACCESS_004() SuspendAllInterrupts()

#define SchM_Exit_PduR_DCM_ACCESS_004() ResumeAllInterrupts()

#define SchM_Enter_PduR_DCM_ACCESS_005() SuspendAllInterrupts()

#define SchM_Exit_PduR_DCM_ACCESS_005() ResumeAllInterrupts()

#define SchM_Enter_PduR_IPDUM_ACCESS_001() SuspendAllInterrupts()

#define SchM_Exit_PduR_IPDUM_ACCESS_001() ResumeAllInterrupts()

#define SchM_Enter_PduR_IPDUM_ACCESS_002() SuspendAllInterrupts()

#define SchM_Exit_PduR_IPDUM_ACCESS_002() ResumeAllInterrupts()

#define SchM_Enter_PduR_IPDUM_ACCESS_003() SuspendAllInterrupts()

#define SchM_Exit_PduR_IPDUM_ACCESS_003() ResumeAllInterrupts()

#define SchM_Enter_PduR_IPDUM_ACCESS_004() SuspendAllInterrupts()

#define SchM_Exit_PduR_IPDUM_ACCESS_004() ResumeAllInterrupts()

#define SchM_Enter_PduR_IPDUM_ACCESS_005() SuspendAllInterrupts()

#define SchM_Exit_PduR_IPDUM_ACCESS_005() ResumeAllInterrupts()

#define SchM_Enter_PduR_TP_BUFF_CTRL_COPYRX() SuspendAllInterrupts()

#define SchM_Exit_PduR_TP_BUFF_CTRL_COPYRX() ResumeAllInterrupts()

#define SchM_Enter_PduR_TP_BUFF_CTRL_COPYTX() SuspendAllInterrupts()

#define SchM_Exit_PduR_TP_BUFF_CTRL_COPYTX() ResumeAllInterrupts()

#define SchM_Enter_PduR_TP_BUFF_CTRL_START_OF_RX() SuspendAllInterrupts()

#define SchM_Exit_PduR_TP_BUFF_CTRL_START_OF_RX() ResumeAllInterrupts()

#define SchM_Enter_PduR_TX_BUFF_CTRL_RX() SuspendAllInterrupts()

#define SchM_Exit_PduR_TX_BUFF_CTRL_RX() ResumeAllInterrupts()

#define SchM_Enter_PduR_TX_BUFF_CTRL_TX() SuspendAllInterrupts()

#define SchM_Exit_PduR_TX_BUFF_CTRL_TX() ResumeAllInterrupts()

#define PDUR_START_SEC_CODE
#include "MemMap.h"
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
 

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#ifdef __cplusplus
} /* extern "C" */
#endif /* __cplusplus */
/** @} doxygen end group definition */
#endif /* !defined(SCHM_PDUR_H) */
/*==================[end of file]============================================*/

