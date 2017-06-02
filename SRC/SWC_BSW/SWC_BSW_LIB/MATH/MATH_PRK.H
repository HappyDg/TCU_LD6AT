/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_PRK                                                 */
/* !Description    : Mathematical functions : Park                            */
/*                                                                            */
/* !File           : MATH_PRK.C                                               */
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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_PRK.H_v  $ */
/* $Revision::   1.1       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/

#ifndef MATH_PRK_H
#define MATH_PRK_H

/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/
#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

extern void MathRotation(sint16 cosinus, sint16 sinus, sint16 dValue, sint16 qValue, sint16 *alphaValue, sint16 *betaValue);

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

#endif /* MATH_PRK_H */

/*-------------------------------- end of file -------------------------------*/
