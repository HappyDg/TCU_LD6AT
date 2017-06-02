/******************************************************************************/
/* !Layer           : SRVL                                                    */
/* !Component       : RSTSRV                                                  */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : RSTSRV_Private.h                                        */
/* !Description     : Private Declaration of RSTSRV Component                 */
/*                                                                            */
/* !Reference       : V03 NT 07 02929                                         */
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

#ifndef RSTSRV_PRIVATE_H
#define RSTSRV_PRIVATE_H

#include "Std_Types.h"

/******************************************************************************/
/* DATA DECLARATIONS                                                          */
/******************************************************************************/

#define RSTSRV_START_SEC_VAR_CLEARED_32BIT
#include "RSTSRV_MemMap.h"

extern uint32 RSTSRV_u32ResetReason;

#define RSTSRV_STOP_SEC_VAR_CLEARED_32BIT
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

extern uint16 RSTSRV_u16TimeAfterInit;

#define RSTSRV_STOP_SEC_VAR_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

extern boolean RSTSRV_bSWResetDetected;
extern boolean RSTSRV_bSWResetDoneByPerformReset;

#define RSTSRV_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

extern boolean RSTSRV_bSWResetRequested;

#define RSTSRV_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_POWER_ON_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

extern uint16 RSTSRV_u16ConsecutiveRstCtr;

#define RSTSRV_STOP_SEC_VAR_POWER_ON_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_CALIB_16BIT
#include "RSTSRV_MemMap.h"

extern const uint16 RSTSRV_ku16ConsecutiveRstMaxNbC;

#define RSTSRV_STOP_SEC_CALIB_16BIT
#include "RSTSRV_MemMap.h"


/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/

#define RSTSRV_START_SEC_CODE
#include "RSTSRV_MemMap.h"

extern void RSTSRV_vidInitEntry(void);

#define RSTSRV_STOP_SEC_CODE
#include "RSTSRV_MemMap.h"

#endif /* RSTSRV_PRIVATE_H */

/*-------------------------------- end of file -------------------------------*/
