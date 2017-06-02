/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_WDG                                                 */
/* !Description     : Demo Software to Test WDG APIs                          */
/*                                                                            */
/* !File            : TST_WDG.h                                               */
/* !Description     : Test of WDG component APIs                              */
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

#ifndef TST_WDG_H
#define TST_WDG_H

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

void TST_WDG_vidInit(void);
void TST_WDG_vidRefreshWdgCore0Tst(void);
void TST_WDG_vidRefreshWdgCore1Tst(void);

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_WDG_H */

/*------------------------------- end of file --------------------------------*/