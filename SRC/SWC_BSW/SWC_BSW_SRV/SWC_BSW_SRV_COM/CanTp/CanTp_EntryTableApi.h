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
#if(!defined CANTP_ENTRYTABLEAPI_H)
#define CANTP_ENTRYTABLEAPI_H

/*==================[inclusions]=============================================*/

#include <TSAutosar.h>              /* EB specific standard types */
#include <ComStack_Types.h>         /* typedefs for AUTOSAR com stack */

#include <CanTp_Version.h>          /* CanTp version declarations */
#include <CanTp_Cfg.h>              /* CanTp configuration */

#if(CANTP_PROVIDE_API_FUNCTIONS == STD_OFF)
#include <CanTp_EntryTable.h>       /* CanTp entry jumptable */
#endif

#include <CanTp_Api.h>              /* CanTp public API */

/*==================[macros]=================================================*/

#if(CANTP_PROVIDE_API_FUNCTIONS == STD_OFF)

#if(CANTP_VERSION_INFO_API == STD_ON)
/** \brief Wrapper macro for API function CanTp_GetVersionInfo() */
#define CanTp_GetVersionInfo  (CanTp_EntryTablePtr->GetVersionInfo)
#endif /* CANTP_VERSION_INFO_API == STD_ON */

/** \brief Wrapper macro for API function CanTp_Transmit() */
#define CanTp_Transmit        (CanTp_EntryTablePtr->Transmit)

#if(CANTP_TX_CANCELLATION_API == STD_ON)
/** \brief Wrapper macro for API function CanTp_CancelTransmit() */
#define CanTp_CancelTransmit   (CanTp_EntryTablePtr->CancelTransmit)
#endif /* CANTP_TX_CANCELLATION_API == STD_ON */

/** \brief Wrapper macro for API function CanTp_MainFunction() */
#define CanTp_MainFunction    (CanTp_EntryTablePtr->MainFunction)

#if(CANTP_DYNAMIC_NSA_API == STD_ON)
/** \brief Wrapper macro for API function CanTp_GetNSa() */
#define CanTp_GetNSa          (CanTp_EntryTablePtr->GetNSa)

/** \brief Wrapper macro for API function CanTp_SetNSa() */
#define CanTp_SetNSa          (CanTp_EntryTablePtr->SetNSa)
#endif /* CANTP_DYNAMIC_NSA_API == STD_ON */

#if(CANTP_CHANGE_PARAMETER_REQ_API == STD_ON)
/** \brief Wrapper macro for API function CanTp_ChangeParameter() */
#define CanTp_ChangeParameter (CanTp_EntryTablePtr->ChangeParameter)
#endif /* CANTP_CHANGE_PARAMETER_REQ_API == STD_ON */

#if(CANTP_RX_CANCELLATION_API == STD_ON)
/** \brief Wrapper macro for API function CanTp_CancelReceive() */
#define CanTp_CancelReceive   (CanTp_EntryTablePtr->CancelReceive)
#endif /* CANTP_RX_CANCELLATION_API == STD_ON */

#endif /*if(CANTP_PROVIDE_API_FUNCTIONS == STD_OFF) */
/*==================[type definitions]=======================================*/

/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[external function declarations]=========================*/

#endif /* if !defined( CANTP_ENTRYTABLEAPI_H ) */
/*==================[end of file]============================================*/
