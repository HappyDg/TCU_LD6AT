/******************************************************************************/
/* !Layer           : SRV                                                     */
/* !Component       : SchM                                                    */
/* !Description     : BSW Scheduler Module                                    */
/*                                                                            */
/* !File            : SchM_RSTSRV.h                                           */
/* !Description     : SchM configuration of the RSTSRV component              */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT VALEO all rights reserved                                        */
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#ifndef SCHM_RSTSRV_H
#define SCHM_RSTSRV_H

#include "KRN_E.h"
#include "OS.h"

/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/

#define SchM_Enter_RSTSRV_ACCESS_001() \
do \
{ \
   if (KRN_bReadOsAccessAuthorized() != FALSE) \
   { \
      SuspendAllInterrupts(); \
   } \
} \
while (0)


#endif /* SCHM_RSTSRV_H */


/*-------------------------------- end of file -------------------------------*/
