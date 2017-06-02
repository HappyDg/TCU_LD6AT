/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer          : BSW                                                                                              */
/*                                                                                                                    */
/* !Component      : HAL                                                                                              */
/*                                                                                                                    */
/* !Module         : IOHAL                                                                                            */
/* !Description    : Configuration of the IOHAL component.                                                            */
/*                                                                                                                    */
/* !File           : IOHAL_Cfg.h                                                                                      */
/*                                                                                                                    */
/* !Target         : All                                                                                              */
/*                                                                                                                    */
/* !Vendor         : Valeo                                                                                            */
/*                                                                                                                    */
/* Coding language : C                                                                                                */
/*                                                                                                                    */
/* COPYRIGHT 2015 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
**********************************************************************************************************************/

#ifndef IOHAL_CFG_H
#define IOHAL_CFG_H

#include "Std_Types.h"

#include "BSW.h"

#define IOHAL_MIN_U16 0u
#define IOHAL_MAX_U16 65535u
#define IOHAL_MIN_S16 -32768
#define IOHAL_MAX_S16 32767


/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Description: Custom  interfaces                                                                                   */
/*                                                                                                                    */
/**********************************************************************************************************************/
#define IOHAL_fSCAL_PRD_kHz(Period) ((float32)100000.0f/Period)
#define IOHAL_fSCAL_PRD_Hz(Period) ((float32)6250000.0f/Period)

#define IOHAL_fSCAL_PRD_EVP_Hz(Period) ((uint32)100000000u/Period)
#define IOHAL_fSCAL_ACCEL_g(Accel)     (((float32)(Accel)) / 16384.0f)
/**********************************************************************************************************************/
#define IOHAL_vidStubWrite(Channel,Value)
#define IOHAL_udtStubRead(Channel) 0

/**********************************************************************************************************************/

#define Pwm_17_Gtm_Stub(Channel,Value)
#define Pwm_17_Gtm_SetEnablePeriodAndDuty(Channel, Enable,Period,Duty) \
  do                                                                   \
  {                                                                    \
     if(Enable!=FALSE)                                                 \
     {                                                                 \
        Pwm_17_Gtm_SetPeriodAndDuty(Channel,Period,Duty);              \
     }                                                                 \
     else                                                              \
     {                                                                 \
        Pwm_17_Gtm_SetOutputToIdle(Channel);                           \
     }                                                                 \
  } while( 0 )

#define SCU_Read(Channel) SCU_u16##Channel

/**********************************************************************************************************************/
#define FRT_u32Read_VALUE(snChannel)  BSW_u32Frt##snChannel
  
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Description:                                                                                                      */
/*                                                                                                                    */
/**********************************************************************************************************************/

static inline uint16 IOHAL_u16MathScalingU16(uint16 input, sint16 factor, sint16 shift, sint16 offset)
{
   sint32 localResult;
   uint16 localOutput;

   localResult = (((sint32)input * factor) << shift) + (sint32)offset;
   localOutput = (uint16)localResult;

   if (localResult < (sint32)IOHAL_MIN_U16)
   {
      localOutput = IOHAL_MIN_U16;
   }
   else if (localResult > (sint32)IOHAL_MAX_U16)
   {
      localOutput = IOHAL_MAX_U16;
   }
   return(localOutput);
}

static inline uint16 IOHAL_u16MathScalingS16(sint16 input, sint16 factor, sint16 shift, sint16 offset)
{
   sint32 localResult;
   uint16 localOutput;

   localResult = (((sint32)input * factor) << shift) + (sint32)offset;
   localOutput = (uint16)localResult;

   if (localResult < (sint32)IOHAL_MIN_U16)
   {
      localOutput = IOHAL_MIN_U16;
   }
   else if (localResult > (sint32)IOHAL_MAX_U16)
   {
      localOutput = IOHAL_MAX_U16;
   }
   return(localOutput);
}

static inline sint16 IOHAL_s16MathScalingU16(uint16 input, sint16 factor, uint16 shift, sint16 offset)
{
   sint32 localResult;
   sint16 localOutput;

   localResult = (((sint32)input * factor) << shift) + (sint32)offset;
   localOutput = (sint16)localResult;

   if (localResult < (sint32)IOHAL_MIN_S16)
   {
      localOutput = IOHAL_MIN_S16;
   }
   else if (localResult > (sint32)IOHAL_MAX_S16)
   {
      localOutput = IOHAL_MAX_S16;
   }
   return(localOutput);
}

static inline sint16 IOHAL_s16MathScalingS16(sint16 input, sint16 factor, uint16 shift, sint16 offset)
{
   sint32 localResult;
   sint16 localOutput;

   localResult = (((sint32)input * factor) << shift) + (sint32)offset;
   localOutput = (sint16)localResult;

   if (localResult < (sint32)IOHAL_MIN_S16)
   {
      localOutput = IOHAL_MIN_S16;
   }
   else if (localResult > (sint32)IOHAL_MAX_S16)
   {
      localOutput = IOHAL_MAX_S16;
   }
   return(localOutput);
}


#endif /* IOHAL_CFG_H */
/*------------------------------ end of file -------------------------------------------------------------------------*/
