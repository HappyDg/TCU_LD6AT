/******************************************************************************/
/* !Layer           : TST                                                     */
/* !Component       : TST_GPT                                                 */
/* !Description     : Test of Gpt component                                   */
/*                                                                            */
/* !File            : GPT_TST_Cfg.h                                           */
/* !Description     : Configuration of Gpt Component                          */
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

#ifndef TST_GPT_CFG_H
#define TST_GPT_CFG_H

#include "Std_Types.h"
#include "Std_Limits.h"

#define GPT_u16TIMER_RESOLUTION  2560U /* Gpt timer resolution equal 2560 nsec */
#define GPT_u32RELOAD_VALUE  3906U /* Gpt will count initially until 10 msec */

#endif /* TST_GPT_CFG_H */

/*------------------------------- end of file --------------------------------*/
