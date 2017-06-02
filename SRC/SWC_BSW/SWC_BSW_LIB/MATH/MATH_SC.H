/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_SC                                                  */
/* !Description    : Mathematical functions : Interpolation                   */
/*                                                                            */
/* !File           : MATH_SC.H                                                */
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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_SC.H_v  $ */
/* $Revision::   1.3       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/

#ifndef MATH_SC_H
#define MATH_SC_H

/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/
#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

extern uint16 MathCalcBkptU8(const uint8 *tabPtr, uint8 value, uint8 nbBkptNM1);
extern uint16 MathCalcBkptU16(const uint16 *tabPtr, uint16 value, uint8 nbBkptNM1);
extern uint8 MathInterp1dU8(const uint8 *tabPtr, uint16 siteInterp);
extern sint8 MathInterp1dS8(const sint8 *tabPtr, uint16 siteInterp);
extern uint16 MathInterp1dU16(const uint16 *tabPtr, uint16 siteInterp);
extern sint16 MathInterp1dS16(const sint16 *tabPtr, uint16 siteInterp);
extern uint16 MathInterp2dU16 (const uint16 *tabPtr, uint16 siteInterpY, uint16 siteInterpX, uint8 nbBkptX);
extern void MathScalingU16(uint16 *output, uint16 input, sint16 offset, sint16 factor, uint16 shift);
extern void MathScalingS16(sint16 *output, sint16 input, sint16 offset, sint16 factor, uint16 shift);
extern void MathScalingUnsignedOffsetU16(uint16 *output, uint16 input, uint16 offset, sint16 factor, uint16 shift);

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

#endif /* MATH_SC_H */

/*-------------------------------- end of file -------------------------------*/
