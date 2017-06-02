/**********************************************************************************************************************/
/* !Layer           : MCAL                                                                                            */
/* !Component       : PWD                                                                                             */
/* !Description     : Test Code For PWD Component                                                                     */
/*                                                                                                                    */
/* !File            : PWD.h                                                                                           */
/* !Description     : This file is the header file of the PWD component APIs.                                         */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/
/* !VnrOff  : Names imposed by the customer                                                                           */
/**********************************************************************************************************************/

#ifndef PWD_H
#define PWD_H

#include "PWD_DEF.h"
#include "MATHSRV.h"
#include "Std_Types.h" 
#include "STD_Limits.h"
#include "Icu_17_GtmCcu6.h"
#include "Dio.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/

/* Maximum period in the PWD_tudtPeriod type used to return the max value  */
/* with wrong channel ID                                                   */
#define PWD_udtPERIOD_MAX_VALUE       UINT32_MAX

/* Define the Maximum duty cycle decimal value                             */
#define PWD_udtDESIRED_DUTY_CYCLE_MAX 32768

/* Define the maximum of the timeout parameter                             */
#define PWD_udtTIMEOUT_TYPE_MAX       UINT32_MAX

#define LAST_MEASURED TRUE
#define MAXIMUM FALSE
#define HIGH STD_HIGH
#define LOW  STD_LOW

#define PWD_ReadFreqChannel(snChannel)  PWD_udtFreq_##snChannel
#define PWD_ReadTonChannel(snChannel)   PWD_udtActiveDuration_##snChannel
#define PWD_ReadDutyChannel(snChannel)  PWD_udtDuty_##snChannel


#define PWD_START_SEC_CODE
#include "PWD_MemMap.h"

extern void PWD_vidInit(void);
extern void PWD_vidActivationManager(void);
extern void PWD_vidEntry_10ms(void);
extern void PWD_vidEntry_100ms(void);

/**********************************************************************************************************************/
/* !FuncName    : PWD_vidMainFunction                                                                                 */
/* !Description : The periodically called API, to update the signal period and duty cycle values, and monitors the    */
/*                time out of the signal.                                                                             */
/*                                                                                                                    */
/*                                                                                                                    */
/* !LastAuthor  : A. Elkhazragy                                                                                       */
/**********************************************************************************************************************/

#define PWD_vidMainFunction(snChannel) \
do \
{ \
   Dio_LevelType                  bLocalCurrentLevelIsActive; \
   Icu_17_GtmCcu6_ValueType       udtLocalPeriodRaw; \
   uint32                         udtLocalFreq; \
   Icu_17_GtmCcu6_ValueType       udtLocalActiveDurationRaw; \
   Icu_17_GtmCcu6_DutyCycleType   strLocPeriodAndActiveTime; \
/*   uint32                         u32LocalPeriod; */ \
   uint32                         u32LocalDutyCycle; \
 \
 \
   if (PWD_bEna_##snChannel != FALSE) \
   { \
      Icu_17_GtmCcu6_GetDutyCycleValues(IcuConf_IcuChannel_##snChannel, &strLocPeriodAndActiveTime); \
 \
      /* !Comment: Calculate the state of the pin, for timeout management            */ \
      bLocalCurrentLevelIsActive = Dio_ReadChannel(DioConf_DioChannel_##snChannel); \
 \
      /* If period is null, that means that no new measurement has been done => no new period occured */ \
      if(strLocPeriodAndActiveTime.PeriodTime != 0) \
      { \
 \
         udtLocalPeriodRaw         = strLocPeriodAndActiveTime.PeriodTime; \
         udtLocalActiveDurationRaw = strLocPeriodAndActiveTime.ActiveTime; \
 \
 \
         /* !Comment: DownCounter is refreshed each new valid period    */ \
         PWD_udtTout_##snChannel = PWD_udtToutRloadVal_##snChannel; \
 \
         udtLocalFreq = (uint32)(PWD_PERIOD_TO_FREQ_##snChannel / ((uint32)(udtLocalPeriodRaw))); \
         PWD_udtPer_##snChannel = udtLocalPeriodRaw; \
         PWD_udtFreq_##snChannel = udtLocalFreq; \
 \
         if (PWD_udtPer_##snChannel != PWD_udtPERIOD_MAX_VALUE) \
         { \
            PWD_bFirstPerOccured_##snChannel = TRUE; \
 \
               PWD_udtActiveDuration_##snChannel = (uint32)udtLocalActiveDurationRaw; \
               u32LocalDutyCycle = (uint32)((((uint32)udtLocalActiveDurationRaw \
                                   * 4096) / ((uint32)udtLocalPeriodRaw)) << 3); \
               PWD_udtDuty_##snChannel = u32LocalDutyCycle; \
 \
         } \
         else \
         { \
            PWD_udtActiveDuration_##snChannel = 0; \
            PWD_udtDuty_##snChannel = 0; \
         } \
      } \
      else \
      { \
         /* We may have a 0 or 100% duty cycle signal here .... or a too low frequency */ \
 \
         /* !Comment: DownCounter is refreshed each pin state change       */ \
         if (bLocalCurrentLevelIsActive != PWD_bCurrentLvlIsActive_##snChannel) \
         { \
            /* if the pin states changed, then we are in the case of a too low frequency */ \
            PWD_udtTout_##snChannel = PWD_udtToutRloadVal_##snChannel; \
         } \
         else \
         { \
            if (PWD_udtTout_##snChannel != 0) \
            { \
               PWD_udtTout_##snChannel = PWD_udtTout_##snChannel - 1; \
            } \
            else \
            { \
               /* A timeout occurs without any edge, so the input is freeze to HIGH */ \
               /*(ducty = 100%) or to LOW (duty = 0%)                               */ \
               PWD_udtTout_##snChannel = PWD_udtToutRloadVal_##snChannel; \
 \
               /* restart the measurement, to prevent to have a icu timer overflow */ \
               Icu_17_GtmCcu6_StopSignalMeasurement(IcuConf_IcuChannel_##snChannel); \
               Icu_17_GtmCcu6_StartSignalMeasurement(IcuConf_IcuChannel_##snChannel); \
 \
               if (PWD_PERIOD_AT_TIMEOUT_##snChannel == FALSE) \
               { \
                  PWD_udtPer_##snChannel = PWD_PERIOD_DESIRED_MAX_##snChannel; \
               } \
 \
               if (bLocalCurrentLevelIsActive == PWD_ACTIVE_STATE_##snChannel) \
               { \
                  PWD_udtActiveDuration_##snChannel = PWD_PERIOD_DESIRED_MAX_##snChannel; \
                  PWD_udtDuty_##snChannel = PWD_udtDESIRED_DUTY_CYCLE_MAX; \
               } \
               else \
               { \
                  PWD_udtActiveDuration_##snChannel = 0; \
                  PWD_udtDuty_##snChannel = 0; \
               } \
            } \
         } \
      } \
      /* !Comment: pin state is refreshed each 2ms                         */ \
      PWD_bCurrentLvlIsActive_##snChannel = bLocalCurrentLevelIsActive; \
   } \
} \
while(0)

/**********************************************************************************************************************/
/* !FuncName    : PWD_udtWriteTimeoutValue                                                                            */
/* !Description :                                                                                                     */
/*                                                                                                                    */
/*                                                                                                                    */
/* !LastAuthor  : A. ELKHAZRAGY                                                                                       */
/**********************************************************************************************************************/

#define PWD_udtWriteTimeoutValue(snChannel, u32TimeoutValue) \
do \
{ \
   uint32             u32LocalResult; \
   uint32             u32LocalTimeoutParam; \
   uint32             u32LocalSamplRate; \
 \
   u32LocalTimeoutParam = (uint32)(u32TimeoutValue); \
 \
    /* Scale the time out parameter */ \
    /* ScaledTimeOut = u32TimeoutValue *  PWD_aku32TimeoutParamResNs */ \
                                /*   / PWD_aku32SamplingRateNs */ \
    u32LocalResult = Mfx_Mul_u32u32_u32(u32LocalTimeoutParam, PWD_TIMEOUT_PARAM_RESOL_IN_NS_##snChannel); \
 \
    if (u32LocalResult > 0) \
    { \
     /* If overflow occurs return E_NOT_OK else E_OK */ \
     u32LocalSamplRate = PWD_SAMPLING_RATE_NS_##snChannel; \
 \
     if (  (u32LocalResult < PWD_udtTIMEOUT_TYPE_MAX) \
        && (u32LocalSamplRate > 0) ) \
     { \
        if ( (u32LocalResult % u32LocalSamplRate) == 0) \
        { \
           u32LocalResult = (u32LocalResult / u32LocalSamplRate) - 1; \
        } \
        else \
        { \
           u32LocalResult = (u32LocalResult / u32LocalSamplRate); \
        } \
     } \
     else \
     { \
        u32LocalResult = PWD_udtTIMEOUT_TYPE_MAX; \
     } \
    } \
    else \
    { \
     u32LocalResult = 0; \
    } \
 \
    /* Cast the final result according to the timeout parameter type */ \
    PWD_udtToutRloadVal_##snChannel = (uint32)u32LocalResult; \
    if (PWD_bEna_##snChannel == FALSE) \
    { \
     PWD_udtTout_##snChannel = PWD_udtToutRloadVal_##snChannel; \
    } \
} \
while(0)

#define PWD_STOP_SEC_CODE
#include "PWD_MemMap.h"

#endif /* PWD_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
