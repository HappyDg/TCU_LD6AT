/******************************************************************************/
/* !Layer           : TST                                                     */
/* !Component       : TST_GPT                                                 */
/* !Description     : Test of Gpt component                                   */
/*                                                                            */
/* !File            : GPT_TST.h                                               */
/* !Description     : Test of Gpt component                                   */
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

#ifndef TST_GPT_H
#define TST_GPT_H

#include "Std_Types.h"
#include "Std_Limits.h"

/******************************************************************************/
/* GLOBAL FUNCTIONS DECLARATION                                               */
/******************************************************************************/

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

void TST_GPT_vidInit(void);
void TST_GPT_StartTimer(void);
void TST_GPT_vidMainFunction(void);
void TST_GPT_StopTimer(void);
void TST_GPT_TestApi(void);

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_GPT_H */

/*------------------------------- end of file --------------------------------*/
