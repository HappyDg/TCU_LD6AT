/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_SC                                                  */
/* !Description    : Mathematical functions : Interpolation                   */
/*                                                                            */
/* !File           : MATH_SC.C                                                */
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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_SC.C_v  $ */
/* $Revision::   1.3       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/* MATH.SC.1  / MathCalcBkptU8                                                */
/* MATH.SC.2  / MathCalcBkptU16                                               */
/* MATH.SC.3  / MathInterp1dU8                                                */
/* MATH.SC.4  / MathInterp1dS8                                                */
/* MATH.SC.5  / MathInterp1dU16                                               */
/* MATH.SC.6  / MathInterp1dS16                                               */
/* MATH.SC.7  / MathInterp2dU16                                               */
/* MATH.SC.8  / MathScalingU16                                                */
/* MATH.SC.9  / MathScalingS16                                                */
/* MATH.SC.10 / MathScalingUnsignedOffsetU16                                  */
/******************************************************************************/

#include "Std_Types.h"

#include "MATH_SC.H"

#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* !Description : Break point calculation uint8                               */
/* !Number      : MATH.SC.1                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
uint16 MathCalcBkptU8(const uint8 *tabPtr, uint8 value, uint8 nbBkptNM1)
{
   uint16 localPivot;
   uint16 localSite;
   uint16 localInterp;
   uint16 localTabPtrSite;
   uint16 localNbBkptNM1;

   if (value >= tabPtr[nbBkptNM1])
   {
      return((uint16)nbBkptNM1 << 8);
   }
   if (value < tabPtr[0])
   {
      return(0);
   }
   localSite = 0;
   localNbBkptNM1 = (uint16)nbBkptNM1;
   while (localNbBkptNM1 > 2)
   {
      localPivot = localSite + (localNbBkptNM1 >> 1);
      if (value < tabPtr[localPivot])
      {
         localNbBkptNM1 = localPivot - localSite;
      }
      else
      {
         localNbBkptNM1 = localSite + localNbBkptNM1 - localPivot;
         localSite = localPivot;
      }
   }
   if (value >= tabPtr[localSite + 1])
   {
      localSite++;
   }
   
   localTabPtrSite = tabPtr[localSite];
   localPivot      = value - localTabPtrSite;
   localPivot      = localPivot << 8;
   localInterp     = tabPtr[localSite + 1] - localTabPtrSite;
   localInterp     = localPivot / localInterp;
   localSite       = localSite << 8;
   localInterp     = localSite + localInterp;
   return(localInterp); 
}
                       
/******************************************************************************/
/*                                                                            */
/* !Description : Break point calculation uint16                              */
/* !Number      : MATH.SC.2                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
uint16 MathCalcBkptU16(const uint16 *tabPtr, uint16 value, uint8 nbBkptNM1)
{
   uint32 localPivot;
   uint32 localSite;
   uint32 localInterp;
   uint32 localTabPtrSite;
   uint32 localNbBkptNM1;

   if (value >= tabPtr[nbBkptNM1])
   {
      return(nbBkptNM1 << 8);
   }
   if (value < tabPtr[0])
   {
      return(0);
   }
   localSite = 0;
   localNbBkptNM1 = (uint32)nbBkptNM1;
   while (localNbBkptNM1 > 2)
   {
      localPivot = localSite + (localNbBkptNM1 >> 1);
      if (value < tabPtr[localPivot])
      {
         localNbBkptNM1 = localPivot - localSite;
      }
      else
      {
         localNbBkptNM1 = localSite + localNbBkptNM1 - localPivot;
         localSite = localPivot;
      }
   }
   if (value >= tabPtr[localSite + 1])
   {
      localSite++;
   }
   
   localTabPtrSite = tabPtr[localSite];
   localPivot      = value - localTabPtrSite;
   localPivot      = localPivot << 8;
   localInterp     = tabPtr[localSite + 1] - localTabPtrSite;
   localInterp     = localPivot / localInterp;
   localSite       = localSite << 8;
   localInterp     = localSite + localInterp;
   return((uint16)localInterp); 
}

/******************************************************************************/
/*                                                                            */
/* !Description : Interpolation 1D uint8                                      */
/* !Number      : MATH.SC.3                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
uint8 MathInterp1dU8(const uint8 *tabPtr, uint16 siteInterp)
{
   sint16 localSw;
   uint8 localUb;
   
   localSw = siteInterp;
   localSw = localSw >> 8;
   tabPtr  = tabPtr + localSw;
   localSw = *(tabPtr + 1);
   localUb = *tabPtr;
   localSw = localSw - localUb;
   siteInterp = siteInterp & 0x00FF;
   localSw = localSw * siteInterp;
   localSw = localSw + 0x80;
   localSw = localSw >> 8;
   localSw = localSw + localUb;
   return((uint8)localSw);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Interpolation 1D sint8                                      */
/* !Number      : MATH.SC.4                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
sint8 MathInterp1dS8(const sint8 *tabPtr, uint16 siteInterp)
{
   sint16 localSw;
   sint8 localSb;
   
   localSw = siteInterp;
   localSw = localSw >> 8;
   tabPtr  = tabPtr + localSw;
   localSw = *(tabPtr + 1);
   localSb = *tabPtr;
   localSw = localSw - localSb;
   siteInterp = siteInterp & 0x00FF;
   localSw = localSw * siteInterp;
   localSw = localSw + 0x80;
   localSw = localSw >> 8;
   localSw = localSw + localSb;
   return((sint8)localSw);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Interpolation 1D uint16                                     */
/* !Number      : MATH.SC.5                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
uint16 MathInterp1dU16(const uint16 *tabPtr, uint16 siteInterp)
{
   sint32 localS4;
   uint16 localUw;

   localS4 = siteInterp;
   localS4 = localS4 >> 8;
   tabPtr  = tabPtr + localS4;
   localS4 = *(tabPtr + 1);
   localUw = *tabPtr;
   localS4 = localS4 - localUw;
   siteInterp = siteInterp & 0x00FF;
   localS4 = localS4 * siteInterp;
   localS4 = localS4 + 0x80;
   localS4 = localS4 >> 8;
   localS4 = localS4 + localUw;
   return((uint16)localS4);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Interpolation 1D sint16                                     */
/* !Number      : MATH.SC.6                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
sint16 MathInterp1dS16(const sint16 *tabPtr, uint16 siteInterp)
{
   sint32 localS4;
   sint16 localSw;

   localS4 = siteInterp;
   localS4 = localS4 >> 8;
   tabPtr  = tabPtr + localS4;
   localS4 = *(tabPtr + 1);
   localSw = *tabPtr;
   localS4 = localS4 - localSw;
   siteInterp = siteInterp & 0x00FF;
   localS4 = localS4 * siteInterp;
   localS4 = localS4 + 0x80;
   localS4 = localS4 >> 8;
   localS4 = localS4 + localSw;
   return((sint16)localS4);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Interpolation 2D uint16                                     */
/* !Number      : MATH.SC.7                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
uint16 MathInterp2dU16 (const uint16 *tabPtr, uint16 siteInterpY, uint16 siteInterpX, uint8 nbBkptX)
{
   uint16 localSiteY;
   uint16 localInterpY;
   uint16 localValue1;
   uint16 localValue2;
   sint32 localValue;

   localSiteY = (siteInterpY >> 8);
   localInterpY = (siteInterpY & 0x00FF);

   localValue1 = MathInterp1dU16 (&tabPtr[(localSiteY * nbBkptX)], siteInterpX);
   localValue2 = MathInterp1dU16 (&tabPtr[((localSiteY + 1) * nbBkptX)], siteInterpX);

   localValue = (((sint32)localValue2 - localValue1) * localInterpY) + 0x80;
   localValue = (localValue / 256);

   return (localValue1 + (sint16)localValue);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Scaling uint16                                              */
/* !Number      : MATH.SC.8                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
void MathScalingU16(uint16 *output, uint16 input, sint16 offset, sint16 factor, uint16 shift)
{
   uint16 localOutput;

   localOutput =(sint16) (((sint32)input * factor) >> shift);
   *output=localOutput + offset;
   if (offset >= 0)
   {
      if (*output < localOutput)
      {
         *output = 0xFFFF;
      }
   }
   else
   {
      if (*output > localOutput)
      {
         *output = 0;
      }
   }
}

/******************************************************************************/
/*                                                                            */
/* !Description : Scaling sint16                                              */
/* !Number      : MATH.SC.9                                                   */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
void MathScalingS16(sint16 *output, sint16 input, sint16 offset, sint16 factor, uint16 shift)
{
   sint16 localOutput;

   localOutput =(sint16) (((sint32)input * factor) >> shift);
   *output=localOutput + offset;
   if (offset >= 0)
   {
      if (*output < localOutput)
      {
         *output = 0x7FFF;
      }
   }
   else
   {
      if (*output > localOutput)
      {
         *output = 0x8000;
      }
   }
}

/******************************************************************************/
/*                                                                            */
/* !Description : Scaling uint16 (offset unsigned)                            */
/* !Number      : MATH.SC.10                                                  */
/* !Reference   :                                                             */
/* !Trace_To    :                                                             */
/* !LastAuthor  : V. Becquet                                                  */
/*                                                                            */
/******************************************************************************/
void MathScalingUnsignedOffsetU16(uint16 *output, uint16 input, uint16 offset, sint16 factor, uint16 shift)
{
   sint16 localOutput;

   localOutput =(sint16) (((sint32)input * factor) >> shift);
   *output=localOutput + offset;
}

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
