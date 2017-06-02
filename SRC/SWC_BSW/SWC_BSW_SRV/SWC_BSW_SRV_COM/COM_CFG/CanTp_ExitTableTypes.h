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
#if(!defined CANTP_EXITTABLETYPES_H)
#define CANTP_EXITTABLETYPES_H

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 19.6 (required)
 *   #undef shall not be used.
 *
 *   Reason:
 *   In order to modify the behavior of the included file, enclosing the file
 *   inclusion by a special macro definition is required.
 */

/*==================[inclusions]=============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* typedefs for AUTOSAR com stack */

#include <CanTp_Cfg.h>          /* CanTp configuration */

#if(CANTP_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* AUTOSAR Development Error Tracer */
#endif /* CANTP_DEV_ERROR_DETECT == STD_ON */
#include <CanIf.h>              /* AUTOSAR Can Interface */
/* do not indirectly include PduR_SymbolicNames_PBcfg.h via PduR_CanTp.h */

#define PDUR_NO_PBCFG_REQUIRED
#include <PduR_CanTp.h>         /* AUTOSAR PDU Router */
/* Deviation MISRA-1 */
#undef PDUR_NO_PBCFG_REQUIRED


/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[external function declarations]=========================*/

#endif /* if !defined( CANTP_EXITTABLETYPES_H ) */
/*==================[end of file]============================================*/
