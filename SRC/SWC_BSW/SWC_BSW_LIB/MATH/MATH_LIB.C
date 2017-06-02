/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_LIB                                                 */
/* !Description    : Mathematical functions : Arithmetic                      */
/*                                                                            */
/* !File           : MATH_LIB.C                                               */
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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_LIB.C_v  $ */
/* $Revision::   1.3       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/* MATH.LIB.1 / MathSquareRoot                                                */
/* MATH.LIB.2 / MathParity                                                    */
/******************************************************************************/

#include "Std_Types.h"

#include "MATH_LIB.H"

#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* !Description : Integer square root calculation                             */
/* !Number      : MATH.LIB.1                                                  */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : O. Garot                                                    */
/*                                                                            */
/******************************************************************************/
uint16 MathSquareRoot(uint32 value)
{
   uint16 localValueLeft;
   uint16 localValueMiddle; 
   uint16 localValueRight;
   uint32 localValueMiddleSquare;

   localValueRight = 65535;
   localValueLeft = 0;
   localValueMiddle = 0;
   localValueMiddleSquare = 0;

/* 16 iterations of MathSquareRootDichotomy() */
/*----------------------------------------------------------------------------*/
#define MathSquareRootDichotomy()\
   localValueMiddle = (uint16)(((uint32)localValueRight + localValueLeft) / 2);\
   localValueMiddleSquare = ((uint32)localValueMiddle * localValueMiddle);\
   if (localValueMiddleSquare > value)\
   {\
      localValueRight = localValueMiddle;\
   }\
   else\
   {\
      localValueLeft = localValueMiddle;\
   }
/*----------------------------------------------------------------------------*/
   MathSquareRootDichotomy(); /*  1 */
   MathSquareRootDichotomy(); /*  2 */
   MathSquareRootDichotomy(); /*  3 */
   MathSquareRootDichotomy(); /*  4 */
   MathSquareRootDichotomy(); /*  5 */
   MathSquareRootDichotomy(); /*  6 */
   MathSquareRootDichotomy(); /*  7 */
   MathSquareRootDichotomy(); /*  8 */
   MathSquareRootDichotomy(); /*  9 */
   MathSquareRootDichotomy(); /* 10 */
   MathSquareRootDichotomy(); /* 11 */
   MathSquareRootDichotomy(); /* 12 */
   MathSquareRootDichotomy(); /* 13 */
   MathSquareRootDichotomy(); /* 14 */
   MathSquareRootDichotomy(); /* 15 */
   MathSquareRootDichotomy(); /* 16 */
/*----------------------------------------------------------------------------*/

   return (localValueLeft);
} 

/******************************************************************************/
/*                                                                            */
/* !Description : Parity calculation                                          */
/* !Number      : MATH.LIB.2                                                  */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : O. Garot                                                    */
/*                                                                            */
/******************************************************************************/
boolean MathParity(uint16 value)
{
   uint16 localParity;

   localParity = value       ^ (value       >> 8);
   localParity = localParity ^ (localParity >> 4);
   localParity = localParity ^ (localParity >> 2);
   localParity = localParity ^ (localParity >> 1);
   
   return (localParity & 0x0001);
} 

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

/*------------------------------ end of file ---------------------------------*/
