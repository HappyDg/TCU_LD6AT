/******************************************************************************/
/*                                                                            */
/* !Layer          : BSW                                                      */
/*                                                                            */
/* !Module         : BSW                                                      */
/* !Description    : BSW initialization                                       */
/*                                                                            */
/* !File           : BSWSRV.H                                                 */
/*                                                                            */
/* !Target         : All                                                      */
/*                                                                            */
/* !Vendor         : Valeo                                                    */
/*                                                                            */
/* Coding language : H                                                        */
/*                                                                            */
/* COPYRIGHT 2008 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::             $$Author::   ogarot        $$Date::               $*/
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/
     
#ifndef BSWSRV_H
#define BSWSRV_H

#include "CCP.h"
#include "CCPUSR.h"
#include "Dio.h"
#include "DEVHAL.h"
#include "IfxStm.h"
//#include "INTBSL.h"
#include "Os_api.h"
//#include "SCHED.h"
#include "SPY.h"
#include "RSTSRV.h"
#include "RTMCLD.h"
#include "SWFAIL.h"
#include "RTMTSK.h"
#include "EVP.h"
#include "Wdg.h"
#include "Gpt.h"
#include "IOHAL.h"
//#include "DCDCAPI_Api.h"
#include "Vadc.h"
#include "CAN_API.h"

//#include "SWC_MCU.h"

/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/

/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/
     
/* RX timeout callbacks */
FUNC(void, COM_APPL_CODE) BSW_CbkRxTOut_SGVCU_4_RC_438R(void);
#endif  /* BSWSRV_H */

/*-------------------------------- end of file -------------------------------*/
