/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_TRI                                                 */
/* !Description    : Mathematical functions : Trigonometry                    */
/*                                                                            */
/* !File           : MATH_TRI.C                                               */
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
/* $Archive:   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_TRI.C_v  $ */
/* $Revision::   1.4       $$Author::   ogarot        $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/* MATH.TRI.1  / LIBTRIG_Sin_Outputs_wrapper                                  */
/* MATH.TRI.2  / MathSinus                                                    */
/* MATH.TRI.3  / LIBTRIG_Cos_Outputs_wrapper                                  */
/* MATH.TRI.4  / MathCosinus                                                  */
/* MATH.TRI.5  / MathArcsinus                                                 */
/* MATH.TRI.6  / MathArccosinus                                               */
/* MATH.TRI.7  / LIBTRIG_SinCos_Outputs_wrapper                               */
/* MATH.TRI.8  / MathSinusCosinus                                             */
/* MATH.TRI.9  / Mathtangente                                                 */
/* MATH.TRI.10 / LIBTRIG_Arctan_Outputs_wrapper                               */
/* MATH.TRI.11 / MathArctangente                                              */
/******************************************************************************/

#include "Std_Types.h"

#include "MATH_SC.H"
#include "MATH_TRI.H"

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

/******************************************************************************/
/*                                                                            */
/* !Description : Sinus calculation (wrapper)                                 */
/* !Number      : MATH.TRI.1                                                  */
/* !Reference   : PONEEMNT060027.001                                          */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
void LIBTRIG_Sin_Outputs_wrapper(const int16_T *Theta, int16_T *Sin)
{
   uint16 localIndexAngle;
   sint16 localInterpResult;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   uint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   const sint16 *localAddOfTable;

   localIndexAngle   = (uint16)((uint16)*Theta >> MATH_SINUS_SHIFT);
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = (uint16)*Theta & MATH_SINUS_MODULO;
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   localInterpResult = (localBkptLow + localRatio);

   *Sin              = (sint16)(localInterpResult / 2);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Sinus calculation                                           */
/* !Number      : MATH.TRI.2                                                  */
/* !Reference   : PONEEMNT060027.001                                          */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
sint16 MathSinus(uint16 angle)
{
   uint16 localIndexAngle;
   sint16 localInterpResult;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   uint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   const sint16 *localAddOfTable;

   localIndexAngle   = (uint16)(angle >> MATH_SINUS_SHIFT);
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = angle & MATH_SINUS_MODULO;
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   localInterpResult = (localBkptLow + localRatio);

   return(localInterpResult);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Cosine calculation (wrapper)                                */
/* !Number      : MATH.TRI.3                                                  */
/* !Reference   : PONEEMNT060027.001                                          */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
void LIBTRIG_Cos_Outputs_wrapper(const int16_T *Theta, int16_T *Cos)
{
   uint16 localIndexAngle;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   uint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   uint32 localAngle;
   const sint16 *localAddOfTable;

   localAngle = (uint16)*Theta + MATH_PI_DIV_2;

   localIndexAngle   = (uint16)(localAngle) >> MATH_SINUS_SHIFT;
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = (sint16)(localAngle) & MATH_SINUS_MODULO;
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   *Cos              = ((localBkptLow + localRatio) / 2);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Cosine calculation                                          */
/* !Number      : MATH.TRI.4                                                  */
/* !Reference   : PONEEMNT060027.001                                          */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
sint16 MathCosinus(uint16 angle)
{
   uint16 localIndexAngle;
   sint16 localInterpResult;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   uint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   uint32 localAngle;
   const sint16 *localAddOfTable;

   localAngle = angle + MATH_PI_DIV_2;
   if (localAngle > MATH_2_PI)
   {
      localAngle -= MATH_2_PI;
   }

   localIndexAngle   = (uint16)(localAngle) >> MATH_SINUS_SHIFT;
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = (sint16)(localAngle) & MATH_SINUS_MODULO;
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   localInterpResult = (sint16)(localBkptLow + localRatio);
   
   return(localInterpResult);
}                       

/******************************************************************************/
/*                                                                            */
/* !Description : ArcSinus calculation                                        */
/* !Number      : MATH.TRI.5                                                  */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
sint16 MathArcsinus(sint16 argument)
{
   uint16 localIndexAngle;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   sint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   sint16 localAngle;
   uint16 localArgument;
   const sint16 *localAddOfTable;

   localArgument     = argument + (uint16)32768;
   localIndexAngle   = localArgument >> MATH_ARCSINUS_SHIFT;
   localAddOfTable   = &mathArcsinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = localArgument & MATH_ARCSINUS_MODULO;
   localRatio        = (uint16)(((uint32)localDelta * localReste) >> 8);
   localAngle        = localBkptLow + localRatio;
   
   return(localAngle);
}

/******************************************************************************/
/*                                                                            */
/* !Description : ArcCosine calculation                                       */
/* !Number      : MATH.TRI.6                                                  */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
sint16 MathArccosinus(sint16 argument)
{
   uint16 localIndexAngle;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   sint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   sint16 localAngle;
   uint16 localArgument;
   const sint16 *localAddOfTable;

   localArgument     = argument + (uint16)MATH_SINUS_OF_PI_DIV_2;
   localIndexAngle   = localArgument >> MATH_ARCSINUS_SHIFT;
   localAddOfTable   = &mathArcsinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = localArgument & MATH_ARCSINUS_MODULO;
   localRatio        = (uint16)(((uint32)localDelta * localReste) >> 8);
   
   localAngle        = localBkptLow + localRatio;
   localAngle        = MATH_PI_DIV_2 - localAngle;
   if (localAngle > MATH_PI_DIV_2)
   {
      localAngle -= MATH_PI_DIV_2;
   }
   
   return(localAngle);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Sinus and Cosine calculation (wrapper)                      */
/* !Number      : MATH.TRI.7                                                  */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
void LIBTRIG_SinCos_Outputs_wrapper(const int16_T *Theta, int16_T *Sin, int16_T *Cos)
{
   uint16 localIndexAngle;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   sint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   uint32 localAngle;
   const sint16 *localAddOfTable;

   localIndexAngle   = (uint16)*Theta >> MATH_SINUS_SHIFT;
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = (sint16)((uint16)*Theta & MATH_SINUS_MODULO);
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   *Sin              = (localBkptLow + localRatio)/2;

   localAngle        = (uint16)*Theta + MATH_PI_DIV_2;
   localIndexAngle   = (uint16)(localAngle) >> MATH_SINUS_SHIFT;
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = (sint16)(localAngle) & MATH_SINUS_MODULO;
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   *Cos              = ((localBkptLow + localRatio) / 2);
}

/******************************************************************************/
/*                                                                            */
/* !Description : Sinus and Cosine calculation                                */
/* !Number      : MATH.TRI.8                                                  */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
void MathSinusCosinus(uint16 angle, sint16 *sinResult, sint16 *cosResult)
{
   uint16 localIndexAngle;
   sint16 localBkptHigh;
   sint16 localBkptLow;
   sint16 localReste;
   sint16 localDelta;
   sint16 localRatio;
   uint32 localAngle;
   const sint16 *localAddOfTable;

   localIndexAngle   = angle >> MATH_SINUS_SHIFT;
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = (sint16)(angle & MATH_SINUS_MODULO);
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   *sinResult        = localBkptLow + localRatio;

   localAngle = angle + MATH_PI_DIV_2;

   localIndexAngle   = (uint16)(localAngle) >> MATH_SINUS_SHIFT;
   localAddOfTable   = &mathSinusTable[localIndexAngle];
   localBkptLow      = *localAddOfTable++;
   localBkptHigh     = *localAddOfTable;
   localDelta        = localBkptHigh - localBkptLow;

   localReste        = (sint16)(localAngle) & MATH_SINUS_MODULO;
   localRatio        = (sint16)(((sint32)localDelta * localReste) >> 8);
   *cosResult        = localBkptLow + localRatio;
}

/******************************************************************************/
/*                                                                            */
/* !Description : Tangent calculation                                         */
/* !Number      : MATH.TRI.9                                                  */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
sint32 MathTangente(sint16 sinus, sint16 cosinus)
{
   sint32 localSinus;
   sint32 localTangente;

   localSinus = ((sint16)sinus * 65536);
   if (cosinus != 0)
   {
      localTangente = ((sint32)localSinus / (sint16)cosinus);
      return(localTangente);
   }
   else
   {
      if (localSinus < 0)
      {
         if (cosinus > 0)
         {
            return(- (sint32)MATH_TANGENTE_1024);
         }
         else
         {
            return(MATH_TANGENTE_1024);
         }
      }
      else
      {
         if (cosinus > 0)
         {
            return(MATH_TANGENTE_1024);
         }
         else
         {
            return(- (sint32)MATH_TANGENTE_1024);
         }
      }
   }
}

/******************************************************************************/
/*                                                                            */
/* !Description : ArcTangent calculation (wrapper)                            */
/* !Number      : MATH.TRI.10                                                 */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
void LIBTRIG_Arctan_Outputs_wrapper(const int32_T *Tangente, int16_T *Theta)
{
   uint16 localIndexTan;
   uint16 localBkptHigh;
   uint16 localBkptLow;
   uint16 localReste;
   uint16 localDelta;
   uint16 localRatio;
   uint32 localTangente;
   sint16 localAngle;
   const uint16 *localAddOfTable;

   if (*Tangente < 0)
   {
      localTangente =  (uint32)(-(*Tangente));
   }
   else
   {
      localTangente =  (uint32)*Tangente;
   }

   if (localTangente < MATH_TANGENTE_1)
   {
      localIndexTan   = (uint16)(localTangente >> 8);
      localAddOfTable = &mathArctangenteTable1[localIndexTan];
      localReste      = (uint16)(localTangente) & MATH_TANGENTE_MODULO;
   }
   else
   {
      if (localTangente < MATH_TANGENTE_8)
      {
         localIndexTan   = (uint16)(localTangente >> MATH_TANGENTE_8_SHIFT_INDEX);
         localIndexTan  -= MATH_TANGENTE_8_INDEX_OFFSET;

         localAddOfTable = &mathArctangenteTable2[localIndexTan];
         localReste      = (sint16)(localTangente >> MATH_TANGENTE_8_SHIFT_RESTE) & MATH_TANGENTE_MODULO;
      }
      else
      {
         if (localTangente > MATH_TANGENTE_1024)
         {
            localTangente  = MATH_TANGENTE_1024;
         }
         localIndexTan   = (uint16)(localTangente >> MATH_TANGENTE_1024_SHIFT_INDEX);
         localIndexTan  -= MATH_TANGENTE_1024_INDEX_OFFSET;

         localAddOfTable = &mathArctangenteTable3[localIndexTan];
         localReste      = (uint16)(localTangente >> MATH_TANGENTE_1024_SHIFT_RESTE) & MATH_TANGENTE_MODULO;
      }
   }

   localBkptLow  = *localAddOfTable++;
   localBkptHigh = *localAddOfTable;
   localDelta    = localBkptHigh - localBkptLow;

   localRatio    = (sint16)(((sint32)localDelta * localReste) >> 8);
   localAngle    = (localBkptLow + localRatio);
   
   if (*Tangente < 0)
   {
      localAngle =  -localAngle;
   }

   *Theta = localAngle;
}

/******************************************************************************/
/*                                                                            */
/* !Description : ArcTangent calculation                                      */
/* !Number      : MATH.TRI.11                                                 */
/* !Reference   : PONEEMNT062252.001                                          */
/* !Trace_To    :                                                             */
/* !LastAuthor  : B. Bouchez                                                  */
/*                                                                            */
/******************************************************************************/
sint16 MathArctangente(sint32 tangente)
{
   uint16 localIndexTan;
   uint16 localBkptHigh;
   uint16 localBkptLow;
   uint16 localReste;
   uint16 localDelta;
   uint16 localRatio;
   uint32 localTangente;
   sint16 localAngle;
   const uint16 *localAddOfTable;

   if (tangente < 0)
   {
      localTangente =  (uint32)(-tangente);
   }
   else
   {
      localTangente =  (uint32)tangente;
   }

   if (localTangente < MATH_TANGENTE_1)
   {
      localIndexTan   = (uint16)(localTangente >> 8);
      localAddOfTable = &mathArctangenteTable1[localIndexTan];
      localReste      = (uint16)(localTangente) & MATH_TANGENTE_MODULO;
   }
   else
   {
      if (localTangente < MATH_TANGENTE_8)
      {
         localIndexTan   = (uint16)(localTangente >> MATH_TANGENTE_8_SHIFT_INDEX);
         localIndexTan  -= MATH_TANGENTE_8_INDEX_OFFSET;

         localAddOfTable = &mathArctangenteTable2[localIndexTan];
         localReste      = (sint16)(localTangente >> MATH_TANGENTE_8_SHIFT_RESTE) & MATH_TANGENTE_MODULO;
      }
      else
      {
         if (localTangente > MATH_TANGENTE_1024)
         {
            localTangente  = MATH_TANGENTE_1024;
         }
         localIndexTan   = (uint16)(localTangente >> MATH_TANGENTE_1024_SHIFT_INDEX);
         localIndexTan  -= MATH_TANGENTE_1024_INDEX_OFFSET;

         localAddOfTable = &mathArctangenteTable3[localIndexTan];
         localReste      = (uint16)(localTangente >> MATH_TANGENTE_1024_SHIFT_RESTE) & MATH_TANGENTE_MODULO;
      }
   }

   localBkptLow  = *localAddOfTable++;
   localBkptHigh = *localAddOfTable;
   localDelta    = localBkptHigh - localBkptLow;

   localRatio    = (sint16)(((sint32)localDelta * localReste) >> 8);
   localAngle    = (localBkptLow + localRatio);
   
   if (tangente < 0)
   {
      localAngle =  -localAngle;
   }

   return(localAngle);
}

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

/*------------------------------ end of file ---------------------------------*/
