/**********************************************************************************************************************/
/* !Layer           : TST                                                                                             */
/* !Component       : TST_VADC                                                                                         */
/* !Description     : Test Code For TST_VADC Component                                                                 */
/*                                                                                                                    */
/* !File            : TST_VADC.h                                                                                       */
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

#ifndef TST_VADC_H
#define TST_VADC_H

#include "Std_Types.h" 

/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/


#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

extern void TST_ADC_vidInit(void);
extern void TST_ADC_vidMainFunction(void);


#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_PWM_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/