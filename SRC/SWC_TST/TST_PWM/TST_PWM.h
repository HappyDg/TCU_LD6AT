/**********************************************************************************************************************/
/* !Layer           : TST                                                                                             */
/* !Component       : TST_PWM                                                                                         */
/* !Description     : Test Code For TST_PWM Component                                                                 */
/*                                                                                                                    */
/* !File            : TST_PWM.h                                                                                       */
/* !Description     : This file is the header file of the TST_PWM component APIs.                                     */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/
/* !VnrOff  : Names imposed by the customer                                                                           */
/**********************************************************************************************************************/

#ifndef TST_PWM_H
#define TST_PWM_H

#include "Std_Types.h" 

/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/


#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

extern void TST_PWM_vidInit(void);
extern void TST_PWM_vidMainFunction(void);


#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_PWM_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/