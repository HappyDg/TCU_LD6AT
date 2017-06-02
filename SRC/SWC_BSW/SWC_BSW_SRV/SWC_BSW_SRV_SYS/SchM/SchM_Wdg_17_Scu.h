/******************************************************************************/
/* !Layer           : SRV                                                     */
/* !Component       : SchM                                                    */
/* !Description     : BSW Scheduler Module                                    */
/*                                                                            */
/* !File            : SchM_Wdg_17_Scu.h                                       */
/* !Description     : SchM configuration of the Wdg_17_scu component          */
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

#ifndef SCHM_WDG_17_SCU_H
#define SCHM_WDG_17_SCU_H

#include "OS.h"

/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/

#define SchM_Enter_Wdg_17_Scu_TimerHandling() SuspendAllInterrupts()
#define SchM_Enter_Wdg_17_Scu_Trigger() SuspendAllInterrupts()
#define SchM_Enter_Wdg_17_Scu_ChangeMode() SuspendAllInterrupts()

#define SchM_Exit_Wdg_17_Scu_TimerHandling() ResumeAllInterrupts()
#define SchM_Exit_Wdg_17_Scu_Trigger() ResumeAllInterrupts()
#define SchM_Exit_Wdg_17_Scu_ChangeMode() ResumeAllInterrupts()

#endif /* SCHM_WDG_17_SCU_H */

/*-------------------------------- end of file -------------------------------*/

