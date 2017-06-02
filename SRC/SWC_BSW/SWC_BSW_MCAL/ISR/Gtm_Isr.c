/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : ISR                                                     */
/* !Description     : ISR Management                                          */
/*                                                                            */
/* !File            : Gtm_Isr.c                                               */
/* !Description     : ISR definition of Gtm component                         */
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

#include "Std_Types.h"
#include "Gtm.h"
//#include "INTBSL.h"
#include "OS.h"

/******************************************************************************/
/* !Comment: Declaration of ISR linked to TOM, ATOM and TIM                   */
/*           Except for TIM0_0 and TIM0_1 reserved for CRKHAL component       */
/******************************************************************************/

#define ISR_START_SEC_CODE
#include "ISR_MemMap.h"

/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_0_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_0 & TOM0_1  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_0_ISR
INT(SRC_GTM_GTM0_TOM0_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 0);
}
#endif /* if (SRC_GTM_GTM0_TOM0_0_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_1_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_2 & TOM0_3  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_1_ISR
INT(SRC_GTM_GTM0_TOM0_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 2);
}
#endif /* if (SRC_GTM_GTM0_TOM0_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_2_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_4 & TOM0_5  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_2_ISR
INT(SRC_GTM_GTM0_TOM0_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 4);
}
#endif /* if (SRC_GTM_GTM0_TOM0_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_3_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_6 & TOM0_7  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_3_ISR
INT(SRC_GTM_GTM0_TOM0_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 6);
}
#endif /* if (SRC_GTM_GTM0_TOM0_3_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_4_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_8 & TOM0_9  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_4_ISR
INT(SRC_GTM_GTM0_TOM0_4_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 8);
}
#endif /* if (SRC_GTM_GTM0_TOM0_4_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_5_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_10 & TOM0_11*/
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_5_ISR
INT(SRC_GTM_GTM0_TOM0_5_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 10);
}
#endif /* if (SRC_GTM_GTM0_TOM0_5_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_6_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_12 & TOM0_13*/
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_6_ISR
INT(SRC_GTM_GTM0_TOM0_6_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 12);
}
#endif /* if (SRC_GTM_GTM0_TOM0_6_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM0_7_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM0_14 & TOM0_15*/
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM0_7_ISR
ISR(SRC_GTM_GTM0_TOM0_7_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 14);
}
#else
#ifdef Os_Cat1_SRC_GTM_GTM0_TOM0_7_ISR
CAT1_ISR(SRC_GTM_GTM0_TOM0_7_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(0, 14);
}
#endif
#endif /* ifndef SRC_GTM_GTM0_TOM0_7_ISR */

/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_0_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_0 & TOM1_1  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_0_ISR
INT(SRC_GTM_GTM0_TOM1_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 0);
}
#endif /* if (SRC_GTM_GTM0_TOM1_0_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_1_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_2 & TOM1_3  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_1_ISR
INT(SRC_GTM_GTM0_TOM1_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 2);
}
#endif /* if (SRC_GTM_GTM0_TOM1_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_2_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_4 & TOM1_5  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_2_ISR
INT(SRC_GTM_GTM0_TOM1_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 4);
}
#endif /* if (SRC_GTM_GTM0_TOM1_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_3_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_6 & TOM1_7  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_3_ISR
INT(SRC_GTM_GTM0_TOM1_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 6);
}
#endif /* if (SRC_GTM_GTM0_TOM1_3_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_4_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_8 & TOM1_9  */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_4_ISR
INT(SRC_GTM_GTM0_TOM1_4_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 8);
}
#endif /* if (SRC_GTM_GTM0_TOM1_4_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_5_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_10 & TOM1_11*/
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_5_ISR
INT(SRC_GTM_GTM0_TOM1_5_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 10);
}
#endif /* if (SRC_GTM_GTM0_TOM1_5_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_6_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_12 & TOM1_13*/
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_6_ISR
INT(SRC_GTM_GTM0_TOM1_6_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 12);
}
#endif /* if (SRC_GTM_GTM0_TOM1_6_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TOM1_7_ISR)                                */
/* !Description : Interrupt for GTM TOM modules for channels TOM1_14 & TOM1_15*/
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TOM1_7_ISR
INT(SRC_GTM_GTM0_TOM1_7_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTomModule(1, 14);
}
#endif /* if (SRC_GTM_GTM0_TOM1_7_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM0_0_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM0_0 & ATOM0_1      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM0_0_ISR
ISR(SRC_GTM_GTM0_ATOM0_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(0, 0);
}
#else
#ifdef Os_Cat1_SRC_GTM_GTM0_ATOM0_0_ISR
CAT1_ISR(SRC_GTM_GTM0_ATOM0_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(0, 0);
}
#endif
#endif /* ifndef SRC_GTM_GTM0_ATOM0_0_ISR */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM0_1_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM0_2 & ATOM0_3      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM0_1_ISR
INT(SRC_GTM_GTM0_ATOM0_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(0, 2);
}
#endif /* if (SRC_GTM_GTM0_ATOM0_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM0_2_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM0_4 & ATOM0_5      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM0_2_ISR
INT(SRC_GTM_GTM0_ATOM0_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(0, 4);
}
#endif /* if (SRC_GTM_GTM0_ATOM0_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM0_3_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM0_6 & ATOM0_7      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM0_3_ISR
INT(SRC_GTM_GTM0_ATOM0_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(0, 6);
}
#endif /* if (SRC_GTM_GTM0_ATOM0_3_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM1_0_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM1_0 & ATOM1_1      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM1_0_ISR
INT(SRC_GTM_GTM0_ATOM1_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(1, 0);
}
#endif /* if (SRC_GTM_GTM0_ATOM1_0_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM1_1_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM1_2 & ATOM1_3      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM1_1_ISR
INT(SRC_GTM_GTM0_ATOM1_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(1, 2);
}
#endif /* if (SRC_GTM_GTM0_ATOM1_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM1_2_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM1_4 & ATOM1_5      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM1_2_ISR
INT(SRC_GTM_GTM0_ATOM1_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(1, 4);
}
#endif /* if (SRC_GTM_GTM0_ATOM1_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM1_3_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM1_6 & ATOM1_7      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM1_3_ISR
INT(SRC_GTM_GTM0_ATOM1_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(1, 6);
}
#endif /* if (SRC_GTM_GTM0_ATOM1_3_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM2_0_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM2_0 & ATOM2_1      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM2_0_ISR
INT(SRC_GTM_GTM0_ATOM2_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(2, 0);
}
#endif /* if (SRC_GTM_GTM0_ATOM2_0_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM2_1_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM2_2 & ATOM2_3      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM2_1_ISR
INT(SRC_GTM_GTM0_ATOM2_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(2, 2);
}
#endif /* if (SRC_GTM_GTM0_ATOM2_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM2_2_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM2_4 & ATOM2_5      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM2_2_ISR
INT(SRC_GTM_GTM0_ATOM2_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(2, 4);
}
#endif /* if (SRC_GTM_GTM0_ATOM2_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM2_3_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM2_6 & ATOM2_7      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM2_3_ISR
INT(SRC_GTM_GTM0_ATOM2_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(2, 6);
}
#endif /* if (SRC_GTM_GTM0_ATOM2_3_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM3_0_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM3_0 & ATOM3_1      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_ATOM3_0_ISR
INT(SRC_GTM_GTM0_ATOM3_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(3, 0);
}
#endif /* if (SRC_GTM_GTM0_ATOM3_0_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM3_1_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM3_2 & ATOM3_3      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_ATOM3_1_USED == STD_ON)
INT(SRC_GTM_GTM0_ATOM3_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(3, 2);
}
#endif /* if (SRC_GTM_GTM0_ATOM3_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM3_2_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM3_4 & ATOM3_5      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_ATOM3_2_USED == STD_ON)
INT(SRC_GTM_GTM0_ATOM3_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(3, 4);
}
#endif /* if (SRC_GTM_GTM0_ATOM3_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_ATOM3_3_ISR)                               */
/* !Description : IT for GTM ATOM modules for channels ATOM3_6 & ATOM3_7      */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_ATOM3_3_USED == STD_ON)
INT(SRC_GTM_GTM0_ATOM3_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrAtomModule(3, 6);
}
#endif /* if (SRC_GTM_GTM0_ATOM3_3_USED == STD_ON) */

/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_0_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_0             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM0_0_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM0_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 0);
}
#endif /* if (SRC_GTM_GTM0_TIM0_0_USED == STD_ON) */

/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_1_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_1             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM0_2_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM0_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 1);
}
#endif /* if (SRC_GTM_GTM0_TIM0_1_USED == STD_ON) */

/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_2_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_2             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM0_2_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM0_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 2);
}
#endif /* if (SRC_GTM_GTM0_TIM0_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_3_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_3             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TIM0_3_ISR
ISR(SRC_GTM_GTM0_TIM0_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 3);
}
#else
#ifdef Os_Cat1_SRC_GTM_GTM0_TIM0_3_ISR
CAT1_ISR(SRC_GTM_GTM0_TIM0_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 3);
}
#endif
#endif /* ifndef SRC_GTM_GTM0_TIM0_3_ISR *

/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_4_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_4             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM0_4_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM0_4_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 4);
}
#endif /* if (SRC_GTM_GTM0_TIM0_4_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_5_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_5             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM0_5_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM0_5_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 5);
}
#endif /* if (SRC_GTM_GTM0_TIM0_5_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_6_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_6             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM0_6_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM0_6_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 6);
}
#endif /* if (SRC_GTM_GTM0_TIM0_6_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM0_7_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM0_7             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM0_7_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM0_7_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 7);
}
#endif /* if (SRC_GTM_GTM0_TIM0_7_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_0_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_0             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_0_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 0);
}
#endif /* if (SRC_GTM_GTM0_TIM1_0_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_1_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_1             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_1_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 1);
}
#endif /* if (SRC_GTM_GTM0_TIM1_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_2_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_2             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_2_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 2);
}
#endif /* if (SRC_GTM_GTM0_TIM1_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_3_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_3             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_3_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 3);
}
#endif /* if (SRC_GTM_GTM0_TIM1_3_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_4_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_4             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_4_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_4_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 4);
}
#endif /* if (SRC_GTM_GTM0_TIM1_4_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_5_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_5             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_5_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_5_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 5);
}
#endif /* if (SRC_GTM_GTM0_TIM1_5_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_6_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_6             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_6_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_6_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 6);
}
#endif /* if (SRC_GTM_GTM0_TIM1_6_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM1_7_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM1_7             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM1_7_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM1_7_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(1, 7);
}
#endif /* if (SRC_GTM_GTM0_TIM1_7_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_0_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_0             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_0_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_0_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 0);
}
#endif /* if (SRC_GTM_GTM0_TIM2_0_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_1_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_1             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_1_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_1_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 1);
}
#endif /* if (SRC_GTM_GTM0_TIM2_1_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_2_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_2             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_2_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_2_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 2);
}
#endif /* if (SRC_GTM_GTM0_TIM2_2_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_3_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_3             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_3_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 3);
}
#endif /* if (SRC_GTM_GTM0_TIM2_3_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_4_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_4             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_4_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_4_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 4);
}
#endif /* if (SRC_GTM_GTM0_TIM2_4_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_5_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_5             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_5_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_5_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 5);
}
#endif /* if (SRC_GTM_GTM0_TIM2_5_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_6_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_6             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_6_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_6_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 6);
}
#endif /* if (SRC_GTM_GTM0_TIM2_6_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM2_7_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM2_7             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#if (SRC_GTM_GTM0_TIM2_7_USED == STD_ON)
INT(SRC_GTM_GTM0_TIM2_7_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(2, 7);
}
#endif /* if (SRC_GTM_GTM0_TIM2_7_USED == STD_ON) */


/******************************************************************************/
/* !FuncName    : INT(SRC_GTM_GTM0_TIM3_5_ISR)                                */
/* !Description : Interrupt for GTM TIM module for channel TIM3_5             */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
#ifdef SRC_GTM_GTM0_TIM3_5_ISR
ISR(SRC_GTM_GTM0_TIM3_5_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(3, 5);
}
#else
#ifdef Os_Cat1_SRC_GTM_GTM0_TIM3_5_ISR
CAT1_ISR(SRC_GTM_GTM0_TIM0_3_ISR)
{
   /* Parameter is Channel Number */
   Gtm_IsrTimModule(0, 3);
}
#endif
#endif /* ifndef SRC_GTM_GTM0_TIM3_5_ISR */
#define ISR_STOP_SEC_CODE
#include "ISR_MemMap.h"

/*-------------------------------- END OF FILE -------------------------------*/
