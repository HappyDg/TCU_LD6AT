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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_PRK.C_v  $ */
/* $Revision::   1.1       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/* MATH.PRK.1 / MathRotation                                                  */
/******************************************************************************/

#include "Std_Types.h"

#include "MATH_SC.H"
#include "MATH_PRK.H"

#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* !Description : Rotation matrix 2 * 2                                       */
/* !Number      : MATH.PRK.1                                                  */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
void MathRotation(sint16 cosinus, sint16 sinus, sint16 dValue, sint16 qValue, sint16 *alphaValue, sint16 *betaValue)
{
   sint32 localParkDCos;
   sint32 localParkDSin;
   sint32 localParkQCos;
   sint32 localParkQSin;
   sint32 localAlpha;
   sint32 localBeta;

   localParkDCos = (sint32)((sint32)(dValue) * cosinus);
   localParkDSin = (sint32)((sint32)(dValue) * sinus);

   localParkQCos = (sint32)((sint32)(qValue) * cosinus);
   localParkQSin = (sint32)((sint32)(qValue) * sinus);

   localAlpha  = (localParkDCos + localParkQSin) / 32768;
   localBeta   = (localParkQCos - localParkDSin) / 32768;

   if (localAlpha > 32767)
   {
      localAlpha = 32767;
   }
   else
   {
      if (localAlpha < -32768)
      {
         localAlpha = -32768;
      }
   }

   if (localBeta > 32767)
   {
      localBeta = 32767;
   }
   else
   {
      if (localBeta < -32768)
      {
         localBeta = -32768;
      }
   }

   *alphaValue = (sint16)(localAlpha);
   *betaValue  = (sint16)(localBeta); 
}

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

/*------------------------------ end of file ---------------------------------*/
