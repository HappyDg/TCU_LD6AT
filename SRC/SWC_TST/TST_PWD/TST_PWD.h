/**********************************************************************************************************************/
/* !Layer           : TST                                                                                             */
/* !Component       : TST_PWD                                                                                         */
/* !Description     : Test Code For TST_PWD Component                                                                 */
/*                                                                                                                    */
/* !File            : TST_PWD.h                                                                                       */
/* !Description     : This file is the header file of the TST_PWD component APIs.                                     */
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

#ifndef TST_PWD_H
#define TST_PWD_H

#include "Std_Types.h" 

/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/


#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

extern void TST_PWD_vidInit(void);
extern void TST_PWD_vidMainFunction(void);

//extern void Shrexp_set_Speed ( uint8 nPlsPerRe[]);


#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_PWD_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/