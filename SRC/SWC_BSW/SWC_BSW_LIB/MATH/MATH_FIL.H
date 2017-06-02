/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_FIL                                                 */
/* !Description    : Mathematical functions : Filters                         */
/*                                                                            */
/* !File           : MATH_FIL.H                                               */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : All                                                      */
/*                                                                            */
/* !Vendor         : Valeo                                                    */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2006 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_FIL.H_v  $ */
/* $Revision::   1.2       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/

#ifndef MATH_FIL_H
#define MATH_FIL_H

/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/

#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

extern void MathFirstOrderFilterU16(uint16 coef, uint16 value, uint16 *valueFil, sint32 *remainder);
extern void MathFirstOrderFilterS16(uint16 coef, sint16 value, sint16 *valueFil, sint32 *remainder);
extern uint16 MathMedianFilterU16(uint16 value, uint16 valueNm1, uint16 valueNm2);
extern void MathRampFilterU16(uint16 valueStep, uint16 valueTar, uint16 *valueFil);

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/
#define MathFirstOrderFastFilter(new_value, old_value, gain)\
   (sint16)(((sint32)(new_value - old_value) * (sint32)gain) / (sint32)65536) + old_value

#endif /* MATH_FIL_H */

/*-------------------------------- end of file -------------------------------*/
