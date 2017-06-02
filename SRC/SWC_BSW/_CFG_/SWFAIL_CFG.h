/******************************************************************************/
/* !Layer           : SRV                                                     */
/* !Component       : SWFAIL                                                  */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : SWFAIL_CFG.h                                            */
/* !Description     : Configuration of SWFAIL Component                       */
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

#ifndef SWFAIL_CFG_H
#define SWFAIL_CFG_H

//#include "OS_TYP.h"
#include "Os.h"

/******************************************************************************/
/* TYPES                                                                      */
/******************************************************************************/
typedef TaskType SWFAIL_tudtStackIdxType;

/******************************************************************************/
/*                         Exported prototypes                                */
/******************************************************************************/

#define SWFAIL_START_SEC_CODE
#include "SWFAIL_MemMap.h"

extern void SWFAIL_vidPerformManualReset(void);

#define SWFAIL_STOP_SEC_CODE
#include "SWFAIL_MemMap.h"

#endif /* SWFAIL_CFG_H */

/*-------------------------------- end of file -------------------------------*/
