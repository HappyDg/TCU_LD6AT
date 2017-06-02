/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_LIB                                                 */
/* !Description    : Mathematical functions : Arithmetic                      */
/*                                                                            */
/* !File           : MATH_LIB.H                                               */
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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_LIB.H_v  $ */
/* $Revision::   1.3       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/

#ifndef MATH_LIB_H
#define MATH_LIB_H

/******************************************************************************/
/* MACRO FUNCTIONS                                                            */
/******************************************************************************/
/* !comment : Macro-function which return the lesser value beetween a and b   */
#define MATH_MIN(a,b)      (((a)>(b))?(b):(a))

/* !comment : Macro-function which return the greater value beetween a and b  */
#define MATH_MAX(a,b)      (((a)>(b))?(a):(b))

/* !comment : Macro-function which return the absolute value of a             */
#define MATH_ABS(a)        (((a)<0)?(-(sint32)(a)):(a))

/* !comment : Macro-function which clamp the value a beetween b and c         */
#define MATH_CLAMP(a,b,c)  (((a)<(b))?(b):(((a)>(c))?(c):(a)))

/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/
#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

extern uint16 MathSquareRoot(uint32 value);
extern boolean MathParity(uint16 value);

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

#endif /* MATH_LIB_H */

/*-------------------------------- end of file -------------------------------*/
