/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           :                                                                                            */
/*                                                                                                                    */
/* !Component       :                                                                                             */
/* !Description     :     unit                                                                                    */
/*                                                                                                                    */
/* !Module          :                                                                                             */
/* !Description     :                                                                           */
/*                                                                                                                    */
/* !File            : TLE8242.h                                                                                  */
/*                                                                                                                    */
/* !Target          :                                                                                      */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* 1 /                                                                                    */
/* 2 /                                                                                        */
/* 3 /                                                                                           */
/* 4 /                                                                                           */
/* 5 /                                                                                          */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* Archive::                        */
/* Revision::   0.1                                                                                                */
/* Author::   gsun5                               Date::   Jan 10, 2017                               */
/**********************************************************************************************************************/
#ifndef TLE8242_interface_h
#define TLE8242_interface_h

#include "Std_Types.h"
#include "TLE8242_reg.h"
#include "TLE8242_cfg.h"


#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
 typedef enum
{
    CurrentControl = 0,
    DirectPWM
} Tle8242ControlModeType;

typedef enum
{
    FaultNotTriggerFault = 0,
    FaultTriggerFault
}Tle8242FaultMaskType;


typedef enum
{
    DiagTimerDiv128 = 0,
    DiagTimerDiv192,
    DiagTimerDiv128_1,
    DiagTimerDiv256
}Tle8242DiagTimerDivType;



typedef enum{
AllValueOfSample = 0,
ThrowOutFirstOne
}
Tle8242SampleSummMethodType;
typedef uint32 DividerMType;
typedef uint32 DividerNType;

typedef enum{
    Disable=0,
    RemainLastSetPoint
}
Tle8242OptEnableDeactiveType;
typedef uint8 DitherstepsizeType;
typedef float CurrentsetpointType;
typedef uint32 KIType;
typedef uint32 KPType;
typedef enum{
    GenericOverVol=0,
    GenericPhaseSync,
    GenericEnable,
    GenericReset
}
Tle8242GenericFlagType;

typedef enum{
    Invalid=0,
    Valid
}
Tle8242ValidType;

typedef enum{
    MinCurrent=0,
    MaxCurrent,
    AvgCurrent
}
Tle8242CurrentType;

typedef enum{
    IFX=193,
}
Tle8242ICManufIDType;
typedef enum{
    B21=2,
}
Tle8242VersionNumberType;



extern Tle8242ICManufIDType TLE8242GetICManufID (uint8 channel);
extern Tle8242VersionNumberType TLE8242GetVersionNumber (uint8 channel);
extern bool TLE8242GetFaultMaskEnable (uint8 channel);
extern void TLE8242SetFaultMaskEnable (uint8 channel, bool fme);
extern void TLE8242SetFaultMask (uint8 channel, Tle8242FaultMaskType fm);
extern Tle8242FaultMaskType TLE8242GetFaultMask (uint8 channel);
extern bool TLE8242GetFaultMaskResetb (uint8 channel);
extern void TLE8242SetFaultMaskResetb (uint8 channel, bool fmr);
extern void TLE8242SetControlMode (uint8 channel, Tle8242ControlModeType cm);
extern Tle8242ControlModeType TLE8242GetControlMode (uint8 channel);
extern void TLE8242SetDIAG_TMR(uint8 channel, Tle8242DiagTimerDivType diag_tmr);
extern Tle8242DiagTimerDivType TLE8242GetDIAG_TMR(uint8 channel );
extern void TLE8242SetShortBatRetry (uint8 channel, uint8 sb_retry);
extern bool TLE8242GetShortGround (uint8 channel);
extern bool TLE8242GetShortBat (uint8 channel);
extern bool TLE8242GetOFF_TST (uint8 channel);
extern bool TLE8242GetSB_TST (uint8 channel);
extern bool TLE8242GetOpenLoadGateOn (uint8 channel);
extern bool TLE8242GetOL_OFF (uint8 channel);
extern Tle8242SampleSummMethodType TLE8242GetSampleSummMethod (uint8 channel);
extern void TLE8242SetSampleSummMethod (uint8 channel, Tle8242SampleSummMethodType sam);
extern void TLE8242SetPWMFrq(uint8 channel, float frq);
extern float TLE8242GetPWMFrq(uint8 channel);
extern void TLE8242SetDividerN (uint8 channel, DividerNType dividern);
extern DividerNType TLE8242GetDividerN (uint8 channel);
extern void TLE8242SetDividerM (uint8 channel, DividerMType dividerm);
extern DividerMType TLE8242GetDividerM (uint8 channel);
extern KPType TLE8242GetKP (uint8 channel);
extern void TLE8242SetKP (uint8 channel, KPType kp);
extern KIType TLE8242GetKI (uint8 channel);
extern void TLE8242SetKI (uint8 channel, KIType ki);
extern void TLE8242SetDitherstepsize (uint8 channel, DitherstepsizeType ditherstepsize);
extern void TLE8242SetOptEnableDeactive (uint8 channel, Tle8242OptEnableDeactiveType en);
extern void TLE8242SetCurrentTarget (uint8 channel, CurrentsetpointType targetCurrent);
extern CurrentsetpointType TLE8242GetCurrentTarget (uint8 channel);
extern void TLE8242SetDitherAMPL(uint8 channel, float target);
extern float TLE8242GetDitherAMPL(uint8 channel);
extern DitherstepsizeType TLE8242GetDitherstepsize (uint8 channel);
extern Tle8242OptEnableDeactiveType TLE8242GetOptEnableDeactive (uint8 channel);
extern void TLE8242SetDitherFrq(uint8 channel, float frq);
extern float TLE8242GetDitherFrq(uint8 channel);
extern uint8 TLE8242GetNumberOfSteps(uint8 channel);
extern void TLE8242SetNumberOfSteps(uint8 channel, uint8 numberofsteps);
extern bool TLE8242GetDitherEnabled(uint8 channel);
extern float TLE8242GetCurrentFeedback(uint8 channel, Tle8242CurrentType type);
extern Tle8242ValidType TLE8242GetCurValid(uint8 channel, Tle8242CurrentType type);
extern bool TLE8242GetGenericFalg(uint8 channel, Tle8242GenericFlagType type);
extern void TLE8242SetPWMDutyCycle(uint8 channel, float duty);
extern float TLE8242GetPWMDutyCycle(uint8 channel);

#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#endif /* TLE8242_h */
