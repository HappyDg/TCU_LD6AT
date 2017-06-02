/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_SPI                                                 */
/* !Description     : Demo Software to Test SPI APIs                          */
/*                                                                            */
/* !File            : TST_SPI.h                                               */
/* !Description     : Test of SPI component APIs                              */
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

#ifndef TST_SPI_H
#define TST_SPI_H

#include "Std_Types.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

extern void TST_SPI_vidInit(void);
extern void TST_SPI_vidMainFunction(void);

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_SPI_H */

/*------------------------------- end of file --------------------------------*/