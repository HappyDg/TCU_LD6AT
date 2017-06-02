/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : STARTUP                                                 */
/* !Description     : Start-up                                                */
/*                                                                            */
/* !File            : STARTUP.h                                               */
/* !Description     : Start-up software                                       */
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

#ifndef STARTUP_H_
#define STARTUP_H_

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/

#define STACK_ALIGN (0xfffffff8U)


/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/
/* STARTUP_bAllRamClearAtInitReq shall have a fixed address in uncleared RAM  */
#define STARTUP_START_SEC_ALL_RAM_CLEAR_AT_INIT_FLAG
#include "STARTUP_MemMap.h"

extern boolean STARTUP_bAllRamClearAtInitReq;

#define STARTUP_STOP_SEC_ALL_RAM_CLEAR_AT_INIT_FLAG
#include "STARTUP_MemMap.h"


/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/

#define STARTUP_START_SEC_CODE
#include "STARTUP_MemMap.h"

extern void cstart(void);
extern void STARTUP_Core0_start(void);
/* extern void STARTUP_Core1_start(void); */
/* extern void STARTUP_Core2_start(void); */
extern void STARTUP_vidReqAllRamClearAtInit(void);

#define STARTUP_STOP_SEC_CODE
#include "STARTUP_MemMap.h"

#endif /* STARTUP_H_ */

/*-------------------------------- end of file -------------------------------*/
