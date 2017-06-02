/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_FIL                                                 */
/* !Description    : Mathematical functions : Filters                         */
/*                                                                            */
/* !File           : MATH_FIL.C                                               */
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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_FIL.C_v  $ */
/* $Revision::   1.2       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/* MATH.FIL.1 / MathFirstOrderFilterU16                                       */
/* MATH.FIL.2 / MathFirstOrderFilterS16                                       */
/* MATH.FIL.3 / MathMedianFilterU16                                           */
/******************************************************************************/

#include "Std_Types.h"

#include "MATH_FIL.H"
#include "MATH_LIB.H"

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !Description : First order filter uint16                                   */
/* !Number      : MATH.LIB.1                                                  */
/* !Reference   : PON EEM NT 03 1371                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : S. Sebiane                                                  */
/*                                                                            */
/******************************************************************************/
void MathFirstOrderFilterU16(uint16 coef, uint16 value, uint16 *valueFil, sint32 *remainder)
{
   sint32 localDelta;
   sint32 localResult;
   uint16 localOldValue;
   sint32 localremainder;

   localremainder = (sint32)(*remainder);
   localOldValue = *valueFil;
   localDelta = (sint32)((sint32)value - localOldValue);
   localResult = (localDelta * coef) + localremainder;
   
   *valueFil = (uint16)(localResult / 65536) + localOldValue;
   
   *remainder = localResult - (((sint32)localResult / 65536) * 65536);
}

/******************************************************************************/
/*                                                                            */
/* !Description : First order filter sint16                                   */
/* !Number      : MATH.LIB.2                                                  */
/* !Reference   : PON EEM NT 03 1371                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : S. Sebiane                                                  */
/*                                                                            */
/******************************************************************************/
void MathFirstOrderFilterS16(uint16 coef, sint16 value, sint16 *valueFil, sint32 *remainder)
{
   sint32 localDelta;
   sint32 localResult;
   sint16 localOldValue;
   sint32 localremainder;

   localremainder = (sint32)(*remainder);
   localOldValue = *valueFil;
   localDelta = (sint32)((sint32)value - localOldValue);
   localResult = (localDelta * coef) + localremainder;

   *valueFil = (sint16)(localResult / 65536) + localOldValue;

   *remainder = localResult - (((sint32)localResult / 65536) * 65536);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Median filter uint16                                        */
/* !Number      : MATH.LIB.3                                                  */
/* !Reference   : PON EEM NT 03 1371                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : O. Garot                                                    */
/*                                                                            */
/******************************************************************************/
uint16 MathMedianFilterU16(uint16 value , uint16 valueNm1 , uint16 valueNm2)
{
   if (valueNm1 > value)
   {
      if (valueNm2 > valueNm1)
      {
         return (valueNm1);
      }
      if (valueNm2 > value)
      {
         return (valueNm2);
      }
      return (value);
   }
   if (valueNm2 > value)
   {
      return (value);   
   }
   if (valueNm2 > valueNm1)
   {
      return(valueNm2); 
   }
   return (valueNm1);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Ramp filter uint16                                          */
/* !Number      : MATH.LIB.4                                                  */
/* !Reference   : NONE                                                        */
/* !Trace_To    :                                                             */
/* !LastAuthor  : O. Garot                                                    */
/*                                                                            */
/******************************************************************************/
void MathRampFilterU16(uint16 valueStep, uint16 valueTar, uint16 *valueFil)
{
   uint16 u16LocalFil;
   uint16 u16LocalStep;

   if (valueStep != 0)
   {
      u16LocalStep = valueStep;
   }
   else
   {
      u16LocalStep = 1;
   }

   u16LocalFil = *valueFil;
   if (valueTar > u16LocalFil)
   {
      u16LocalFil = (uint16)MATH_MIN(((uint32)u16LocalFil + (uint32)u16LocalStep),
                                     (uint32)valueTar);
   }
   else
   {
      u16LocalFil = (uint16)MATH_MAX(((sint32)(uint32)u16LocalFil - (sint32)(uint32)u16LocalStep),
                                     (sint32)(uint32)valueTar);
   }
   *valueFil = u16LocalFil;
}


#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

/*------------------------------ end of file ---------------------------------*/
