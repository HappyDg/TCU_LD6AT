/**********************************************************************************************************************/
/* !Layer           : APPLI                                                                                           */
/* !Component       : TST_DET                                                                                         */
/* !Description     : Code to be able to test the Det component                                                       */
/*                                                                                                                    */
/* !File            : TST_DET.h                                                                                       */
/* !Description     : Code to be able to test the Det component                                                       */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* !Target          : ALL                                                                                             */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/

#ifndef TST_DET_H
#define TST_DET_H


#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

void TST_DET_vidInit(void);
void TST_DET_vidMainFunction(void);

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_DET_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
