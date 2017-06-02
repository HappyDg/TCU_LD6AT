/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_CANAPI                                                 */
/* !Description     : Test of CAN component                                   */
/*                                                                            */
/* !File            : TST_CANAPI.h                                               */
/* !Description     : Test of CAN component APIs                              */
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

#ifndef TST_CANAPI_H
#define TST_CANAPI_H

/******************************************************************************/
/* DEFINE DECLARATIONS                                                        */
/******************************************************************************/


/******************************************************************************/
/* FUNCTION DECLARATIONS                                                      */
/******************************************************************************/

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

void TST_CANAPI_vidInit();
void TST_vidTestCanApi( void );

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_CANAPI_H */

/*------------------------------- end of file --------------------------------*/
