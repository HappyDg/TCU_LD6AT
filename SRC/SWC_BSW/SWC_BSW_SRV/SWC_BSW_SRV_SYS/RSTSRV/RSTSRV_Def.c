/******************************************************************************/
/* !Layer           : SRVL                                                    */
/* !Component       : RSTSRV                                                  */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : RSTSRV_Def.c                                            */
/* !Description     : Data of RSTSRV Component                                */
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

#include "Std_Types.h"
#include "RSTSRV_Typ.h"
#include "RSTSRV.h"
#include "RSTSRV_Private.h"

/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/

#define RSTSRV_START_SEC_VAR_CLEARED_32BIT
#include "RSTSRV_MemMap.h"

uint32 RSTSRV_u32ResetReason;

#define RSTSRV_STOP_SEC_VAR_CLEARED_32BIT
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

uint16 RSTSRV_u16HotResetCtr;
uint16 RSTSRV_u16TimeAfterInit;

#define RSTSRV_STOP_SEC_VAR_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

boolean RSTSRV_bSWResetDetected;
boolean RSTSRV_bSWResetDoneByPerformReset;

#define RSTSRV_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

boolean RSTSRV_bSWResetRequested;

#define RSTSRV_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_VAR_POWER_ON_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

uint16 RSTSRV_u16ConsecutiveRstCtr;

#define RSTSRV_STOP_SEC_VAR_POWER_ON_CLEARED_16BIT
#include "RSTSRV_MemMap.h"

#define RSTSRV_START_SEC_CALIB_16BIT
#include "RSTSRV_MemMap.h"

const uint16 RSTSRV_ku16ConsecutiveRstMaxNbC = 0;

#define RSTSRV_STOP_SEC_CALIB_16BIT
#include "RSTSRV_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
