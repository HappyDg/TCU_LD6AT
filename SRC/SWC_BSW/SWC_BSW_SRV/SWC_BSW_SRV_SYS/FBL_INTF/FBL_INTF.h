/******************************************************************************/
/* !Layer           : FLB                                                     */
/* !Component       : FBL_INTF                                                */
/* !Description     : Manage exchange area FBL to Appli                       */
/*                                                                            */
/* !File            : FBL_INTF.h                                              */
/* !Description     : Definition of exchange area                             */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  :  C                                                      */
/*                                                                            */
/* COPYRIGHT VALEO all rights reserved                                        */
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/
#ifndef FBL_INTF_H
#define FBL_INTF_H

#include "Std_Types.h"

/******************************************************************************/
/* CONSTANTS DEFINITION                                                       */
/******************************************************************************/

/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/

#define FBL_INTF_START_SEC_VAR_FBL_INTF
#include "FBL_INTF_MemMap.h"

/* All interface between FBL and BSW shall be defined in this section (Exchange buffer, ...) */

#define FBL_INTF_STOP_SEC_VAR_FBL_INTF
#include "FBL_INTF_MemMap.h"

/******************************************************************************/
/* FUNCTIONS                                                                  */
/******************************************************************************/

#endif

/*------------------------------ end of file ---------------------------------*/
