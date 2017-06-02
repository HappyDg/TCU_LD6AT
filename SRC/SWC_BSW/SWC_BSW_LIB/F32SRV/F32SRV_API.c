/******************************************************************************/
/*                                                                            */
/* !Layer :             SRVL                                                  */
/*                                                                            */
/* !Component :         F32SRV                                                */
/* !Description :       Floating points services                              */
/*                                                                            */
/* !Module :            F32SRV                                                */
/* !Description :       API of the Component                                  */
/*                                                                            */
/* !File :              F32SRV_API.C                                          */
/*                                                                            */
/* !Scope :             Public                                                */
/*                                                                            */
/* !Target :            Renesas SH725xx                                       */
/*                                                                            */
/* !Vendor :            Valeo                                                 */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2008 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   I:/PROJETS/LIBEMB/LOG/SRV/F32SRV/LOG/F32SRV_API.c_v          $*/
/* $Revision::   1.0    $$Author::   lvoilmy    $$Date::   29 Oct 2008 10:28:$*/
/******************************************************************************/
/* F32SRV.2 / F32SRV_bIsFinite                                                */
/* F32SRV.4 / F32SRV_u8F32ToUint8                                             */
/* F32SRV.5 / F32SRV_s8F32toSint8                                             */
/* F32SRV.6 / F32SRV_u16F32toUint16                                           */
/* F32SRV.7 / F32SRV_s16F32toSint16                                           */
/* F32SRV.8 / F32SRV_u32F32toUint32                                           */
/* F32SRV.9 / F32SRV_s32F32toSint32                                           */
/******************************************************************************/
/* !CompReq : FLOAT                                                           */
/******************************************************************************/


#include "Std_Types.h"
#include "Std_Limits.h"
#include "F32SRV.h"
#include "F32SRV_E.h"


/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/
#define F32SRV_START_SEC_CODE
#include "F32SRV_MemMap.h"


/******************************************************************************/
/*                                                                            */
/* !Description : Test if the parameter is finite                             */
/* !Number : 2                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/* !Trace_To: VEMS_R_08_06040_002.01                                          */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
FUNC(boolean, F32SRV_CODE) F32SRV_bIsFinite
(
   float32 f32Data /* !Comment: Floating point data to test                   */
)
{
   boolean bLocalReturnValue;

   if (F32SRV_bIsNan(f32Data) != (boolean)TRUE)
   {
      if ( (f32Data >= FLOAT32_MIN) && (f32Data <= FLOAT32_MAX) )
      {
         bLocalReturnValue = TRUE;
      }
      else
      {
         bLocalReturnValue = FALSE;
      }
   }
   else
   {
      bLocalReturnValue = FALSE;
   }

   return(bLocalReturnValue);
}



/******************************************************************************/
/*                                                                            */
/* !Description : Converts float32 to uint8                                   */
/* !Number : 4                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
FUNC(uint8, F32SRV_CODE) F32SRV_u8F32ToUint8
(
   float32 f32Data,          /* !Comment: Floating point value to convert     */
                             /*           into integer value                  */
   uint8   u8UnderflowValue, /* !Comment: Returned value if f32Data is lesser */
                             /*           than the less integer representable */
                             /*           value                               */
   uint8   u8OverflowValue,  /* !Comment: Returned value if f32Data is        */
                             /*           greater than the largest integer    */
                             /*           representable value                 */
   uint8   u8NanValue        /* !Comment: Returned value if f32Data is equal  */
                             /*           to "Not a Number"                   */
)
{
   uint8   u8LocalReturnValue;

   if (F32SRV_bIsNan(f32Data) == (boolean)TRUE)
   {
      /* !Trace_To: VEMS_R_08_06040_004.01                                    */
      u8LocalReturnValue = u8NanValue;
   }
   else
   {
      if (f32Data > (float32)UINT8_MAX)
      {
         /* !Trace_To: VEMS_R_08_06040_005.01                                 */
         u8LocalReturnValue = u8OverflowValue;
      }
      else if (f32Data < (float32)UINT8_MIN)
      {
         /* !Trace_To: VEMS_R_08_06040_006.01                                 */
         u8LocalReturnValue = u8UnderflowValue;
      }
      else
      {
         /* !Trace_To: VEMS_R_08_06040_007.01                                 */
         /* !Comment: add 0.5 because SH2A makes a round to 0 by default      */
         u8LocalReturnValue = (uint8)(f32Data + 0.5f);
      }
   }

   return(u8LocalReturnValue);
}



/******************************************************************************/
/*                                                                            */
/* !Description : Converts float32 to sint8                                   */
/* !Number : 5                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
FUNC(sint8, F32SRV_CODE) F32SRV_s8F32ToSint8
(
   float32 f32Data,          /* !Comment: Floating point value to convert     */
                             /*           into integer value                  */
   sint8   s8UnderflowValue, /* !Comment: Returned value if f32Data is lesser */
                             /*           than the less integer representable */
                             /*           value                               */
   sint8   s8OverflowValue,  /* !Comment: Returned value if f32Data is        */
                             /*           greater than the largest integer    */
                             /*           representable value                 */
   sint8   s8NanValue        /* !Comment: Returned value if f32Data is equal  */
                             /*           to "Not a Number"                   */
)
{
   sint8   s8LocalReturnValue;

   if (F32SRV_bIsNan(f32Data) == (boolean)TRUE)
   {
      /* !Trace_To: VEMS_R_08_06040_008.01                                    */
      s8LocalReturnValue = s8NanValue;
   }
   else
   {
      if (f32Data > (float32)SINT8_MAX)
      {
         /* !Trace_To: VEMS_R_08_06040_009.01                                 */
         s8LocalReturnValue = s8OverflowValue;
      }
      else if (f32Data < (float32)SINT8_MIN)
      {
         /* !Trace_To: VEMS_R_08_06040_010.01                                 */
         s8LocalReturnValue = s8UnderflowValue;
      }
      else
      {
         /* !Trace_To: VEMS_R_08_06040_011.01                                 */
         if (f32Data < 0.0f)
         {
            /* !Comment: minus 0.5 because SH2A makes a round to 0 by default */
            s8LocalReturnValue = (sint8)(f32Data - 0.5f);
         }
         else if (f32Data > 0.0f)
         {
            /* !Comment: add 0.5 because SH2A makes a round to 0 by default   */
            s8LocalReturnValue = (sint8)(f32Data + 0.5f);
         }
         else
         {
            /* !Comment: case where f32Data = 0.0f                            */
            s8LocalReturnValue = 0;
         }
      }
   }

   return(s8LocalReturnValue);
}



/******************************************************************************/
/*                                                                            */
/* !Description : Converts float32 to uint16                                  */
/* !Number : 6                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
FUNC(uint16, F32SRV_CODE) F32SRV_u16F32ToUint16
(
   float32  f32Data,           /* !Comment: Floating point value to convert   */
                               /*           into integer value                */
   uint16   u16UnderflowValue, /* !Comment: Returned value if f32Data is      */
                               /*           lesser than the less integer      */
                               /*           representable value               */
   uint16   u16OverflowValue,  /* !Comment: Returned value if f32Data is      */
                               /*           greater than the largest integer  */
                               /*           representable value               */
   uint16   u16NanValue        /* !Comment: Returned value if f32Data is      */
                               /*           equal to "Not a Number"           */
)
{
   uint16   u16LocalReturnValue;

   if (F32SRV_bIsNan(f32Data) == (boolean)TRUE)
   {
      /* !Trace_To: VEMS_R_08_06040_012.01                                    */
      u16LocalReturnValue = u16NanValue;
   }
   else
   {
      if (f32Data > (float32)UINT16_MAX)
      {
         /* !Trace_To: VEMS_R_08_06040_013.01                                 */
         u16LocalReturnValue = u16OverflowValue;
      }
      else if (f32Data < (float32)UINT16_MIN)
      {
         /* !Trace_To: VEMS_R_08_06040_014.01                                 */
         u16LocalReturnValue = u16UnderflowValue;
      }
      else
      {
         /* !Trace_To: VEMS_R_08_06040_015.01                                 */
         /* !Comment: add 0.5 because SH2A makes a round to 0 by default      */
         u16LocalReturnValue = (uint16)(f32Data + 0.5f);
      }
   }

   return(u16LocalReturnValue);
}


/******************************************************************************/
/*                                                                            */
/* !Description : Converts float32 to sint16                                  */
/* !Number : 7                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
FUNC(sint16, F32SRV_CODE) F32SRV_s16F32ToSint16
(
   float32  f32Data,           /* !Comment: Floating point value to convert   */
                               /*           into integer value                */
   sint16   s16UnderflowValue, /* !Comment: Returned value if f32Data is      */
                               /*           lesser than the less integer      */
                               /*           representable value               */
   sint16   s16OverflowValue,  /* !Comment: Returned value if f32Data is      */
                               /*           greater than the largest integer  */
                               /*           representable value               */
   sint16   s16NanValue        /* !Comment: Returned value if f32Data is      */
                               /*           equal to "Not a Number"           */
)
{
   sint16   s16LocalReturnValue;

   if (F32SRV_bIsNan(f32Data) == (boolean)TRUE)
   {
      /* !Trace_To: VEMS_R_08_06040_016.01                                    */
      s16LocalReturnValue = s16NanValue;
   }
   else
   {
      if (f32Data > (float32)SINT16_MAX)
      {
         /* !Trace_To: VEMS_R_08_06040_017.01                                 */
         s16LocalReturnValue = s16OverflowValue;
      }
      else if (f32Data < (float32)SINT16_MIN)
      {
         /* !Trace_To: VEMS_R_08_06040_018.01                                 */
         s16LocalReturnValue = s16UnderflowValue;
      }
      else
      {
         /* !Trace_To: VEMS_R_08_06040_019.01                                 */
         if (f32Data < 0.0f)
         {
            /* !Comment: minus 0.5 because SH2A makes a round to 0 by default */
            s16LocalReturnValue = (sint16)(f32Data - 0.5f);
         }
         else if (f32Data > 0.0f)
         {
            /* !Comment: add 0.5 because SH2A makes a round to 0 by default   */
            s16LocalReturnValue = (sint16)(f32Data + 0.5f);
         }
         else
         {
            /* !Comment: case where f32Data = 0.0f                            */
            s16LocalReturnValue = 0;
         }
      }
   }

   return(s16LocalReturnValue);
}


/******************************************************************************/
/*                                                                            */
/* !Description : Converts float32 to uint32                                  */
/* !Number : 8                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
FUNC(uint32, F32SRV_CODE) F32SRV_u32F32ToUint32
(
   float32  f32Data,           /* !Comment: Floating point value to convert   */
                               /*           into integer value                */
   uint32   u32UnderflowValue, /* !Comment: Returned value if f32Data is      */
                               /*           lesser than the less integer      */
                               /*           representable value               */
   uint32   u32OverflowValue,  /* !Comment: Returned value if f32Data is      */
                               /*           greater than the largest integer  */
                               /*           representable value               */
   uint32   u32NanValue        /* !Comment: Returned value if f32Data is      */
                               /*           equal to "Not a Number"           */
)
{
   uint32   u32LocalReturnValue;

   if (F32SRV_bIsNan(f32Data) == (boolean)TRUE)
   {
      /* !Trace_To: VEMS_R_08_06040_020.01                                    */
      u32LocalReturnValue = u32NanValue;
   }
   else
   {
      /* !Comment: F32SRV_f32UINT32_OVERFLOW_VALUE is used because it is a    */
      /*           float readable value                                       */
      if (f32Data >= F32SRV_f32UINT32_OVERFLOW_VALUE)
      {
         /* !Trace_To: VEMS_R_08_06040_021.01                                 */
         u32LocalReturnValue = u32OverflowValue;
      }
      else if (f32Data < (float32)UINT32_MIN)
      {
         /* !Trace_To: VEMS_R_08_06040_022.01                                 */
         u32LocalReturnValue = u32UnderflowValue;
      }
      else
      {
         /* !Comment: add 0.5 until 8388608.0 excluded because SH2A makes a   */
         /*           round to 0 by default. For greater data, the rounding   */
         /*           is correctly done because of the imprecision of floats  */
         /* !Trace_To: VEMS_R_08_06040_023.01                                 */
         if (f32Data < F32SRV_f32_ARE_INT_MIN_VALUE)
         {
            u32LocalReturnValue = (uint32)(f32Data + 0.5f);
         }
         else
         {
            u32LocalReturnValue = (uint32)f32Data;
         }
      }
   }

   return(u32LocalReturnValue);
}


/******************************************************************************/
/*                                                                            */
/* !Description : Converts float32 to sint32                                  */
/* !Number : 9                                                                */
/* !Reference : V01 NT 08 06040 #1                                            */
/*                                                                            */
/* !LastAuthor : J. Perochon                                                  */
/******************************************************************************/
FUNC(sint32, F32SRV_CODE) F32SRV_s32F32ToSint32
(
   float32  f32Data,           /* !Comment: Floating point value to convert   */
                               /*           into integer value                */
   sint32   s32UnderflowValue, /* !Comment: Returned value if f32Data is      */
                               /*           lesser than the less integer      */
                               /*           representable value               */
   sint32   s32OverflowValue,  /* !Comment: Returned value if f32Data is      */
                               /*           greater than the largest integer  */
                               /*           representable value               */
   sint32   s32NanValue        /* !Comment: Returned value if f32Data is      */
                               /*           equal to "Not a Number"           */
)
{
   sint32   s32LocalReturnValue;

   if (F32SRV_bIsNan(f32Data) == (boolean)TRUE)
   {
      /* !Trace_To: VEMS_R_08_06040_024.01                                    */
      s32LocalReturnValue = s32NanValue;
   }
   else
   {
      /* !Comment: F32SRV_f32SINT32_OVERFLOW_VALUE is used because it is a    */
      /*            float readable value                                      */
      if (f32Data >= F32SRV_f32SINT32_OVERFLOW_VALUE)
      {
         /* !Trace_To: VEMS_R_08_06040_025.01                                 */
         s32LocalReturnValue = s32OverflowValue;
      }
      else if (f32Data < (float32)SINT32_MIN)
      {
         /* !Trace_To: VEMS_R_08_06040_026.01                                 */
         s32LocalReturnValue = s32UnderflowValue;
      }
      else
      {
         /* !Trace_To: VEMS_R_08_06040_027.01                                 */
         if ( (f32Data < 0.0f) && (f32Data > -F32SRV_f32_ARE_INT_MIN_VALUE) )
         {
            /* !Comment: minus 0.5 because SH2A makes a round to 0 by default */
            s32LocalReturnValue = (sint32)(f32Data - 0.5f);
         }
         else if ((f32Data > 0.0f) && (f32Data < F32SRV_f32_ARE_INT_MIN_VALUE))
         {
            /* !Comment: add 0.5 because SH2A makes a round to 0 by default   */
            s32LocalReturnValue = (sint32)(f32Data + 0.5f);
         }
         else
         {
            /* !Comment: case where f32Data = 0.0f or greater than 8388608.0f */
            /*           F32SRV_f32_ARE_INT_MIN_VALUE or smaller than         */
            /*           -F32SRV_f32_ARE_INT_MIN_VALUE                        */
            s32LocalReturnValue = (sint32)f32Data;
         }
      }
   }

   return(s32LocalReturnValue);
}


#define F32SRV_STOP_SEC_CODE
#include "F32SRV_MemMap.h"


/*-------------------------------- END OF FILE -------------------------------*/
