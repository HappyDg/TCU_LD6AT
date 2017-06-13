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
    TLE8242_CRNT_CTRL_MOD = 0,
    TLE8242_DIRECT_PWM_MOD
} Tle8242CtrlModTyp;

typedef enum
{
    TLE8242_FLT_NOT_TRIG_FLT_PIN = 0,
    TLE8242_FLT_TRIG_FLT_PIN
}Tle8242FaultMaskType;


typedef enum
{
    TLE8242_DIAG_TMR_DIV_128 = 0,
    TLE8242_DIAG_TMR_DIV_192,
    TLE8242_DIAG_TMR_DIV_128_1,
    TLE8242_DIAG_TMR_DIV_256
}Tle8242DiagTmrDivTyp;



typedef enum{
TLE8242_CRNT_ALL_VAL_SAMPLE = 0,
TLE8242_CRNT_THROW_OUT_FIRST_ONE
}
Tle8242SampleSummMethodType;
typedef uint32 DividerMType;
typedef uint32 DividerNType;

typedef enum{
    TLE8242_DEACTIVE_DISABLE=0,
    TLE8242_DEACTIVE_REMAIN_LAST_SETPOINT
}
Tle8242OptEnableDeactiveType;
typedef uint16 DitherstepsizeType;
typedef float32 CurrentsetpointType;
typedef uint32 KIType;
typedef uint32 KPType;
typedef enum{
    TLE8242_GENERIC_OVER_VOL=0,
    TLE8242_GENERIC_PHASE_SYNC,
    TLE8242_GENERIC_ENABLE,
    TLE8242_GENERIC_RESET
}
Tle8242GenericFlagType;

typedef enum{
    TLE8242_CRNT_FB_INVALID=0,
    TLE8242_CRNT_FB_VALID
}
Tle8242ValidType;

typedef enum{
    TLE8242_MIN_CRNT=0,
    TLE8242_MAX_CRNT,
    TLE8242_AVG_CRNT
}
Tle8242CurrentType;

typedef enum{
    TLE8242_IC_MANUF_IFX=193,
}
Tle8242ICManufIDTyp;
typedef enum{
    TLE8242_VERS_B21=2,
}
Tle8242VersNrTyp;



extern Tle8242ICManufIDTyp TLE8242_stGetIcManufID (uint8 u8LocChIdx);
extern Tle8242VersNrTyp TLE8242_stGetVersNr (uint8 u8LocChIdx);
extern boolean TLE8242_bGetFltMaskEna (uint8 u8LocChIdx);
extern void TLE8242_vidSetFltMaskEna (uint8 u8LocChIdx, boolean bLocfme);
extern void TLE8242_vidSetFltMask (uint8 u8LocChIdx, Tle8242FaultMaskType enuLocfm);
extern Tle8242FaultMaskType TLE8242_bGetFltMask (uint8 u8LocChIdx);
extern boolean TLE8242_bGetFltMaskRstB (uint8 u8LocChIdx);
extern void TLE8242_vidSetFltMaskRstB (uint8 u8LocChIdx, boolean bLocfmr);
extern void TLE8242_vidSetCtrlMod (uint8 u8LocChIdx, Tle8242CtrlModTyp enuLocCm);
extern Tle8242CtrlModTyp TLE8242_stGetCtrlMod (uint8 u8LocChIdx);
extern void TLE8242_vidSetDisgTmr(uint8 u8LocChIdx, Tle8242DiagTmrDivTyp enuLocTmr);
extern Tle8242DiagTmrDivTyp TLE8242_stGetDisgTmr(uint8 u8LocChIdx );
extern void TLE8242SetScsRetry (uint8 u8LocChIdx, uint8 u8LocScsRetry);
extern boolean TLE8242_bGetScFlt (uint8 u8LocChIdx);
extern boolean TLE8242_bGetScsFlt (uint8 u8LocChIdx);
extern boolean TLE8242_bGetOffTst (uint8 u8LocChIdx);
extern boolean TLE8242_bGetScsTst (uint8 u8LocChIdx);
extern boolean TLE8242_bGetOpenLoadGateOn (uint8 u8LocChIdx);
extern boolean TLE8242_bGetOpenLoadGateOff (uint8 u8LocChIdx);
extern Tle8242SampleSummMethodType TLE8242_stGetSampleSummaryMethod (uint8 u8LocChIdx);
extern void TLE8242_vidSetSampleSummMethod (uint8 u8LocChIdx, Tle8242SampleSummMethodType enuLocSAM);
extern void TLE8242_vidSetPWMFrq(uint8 u8LocChIdx, float32 f32LocFrq);
extern float32 TLE8242_f32GetPwmFrq(uint8 u8LocChIdx);
extern void TLE8242_vidSetDivN (uint8 u8LocChIdx, DividerNType u32LocDivN);
extern DividerNType TLE8242_u32GetDivN (uint8 u8LocChIdx);
extern void TLE8242_vidSetDivM (uint8 u8LocChIdx, DividerMType u32LocDivM);
extern DividerMType TLE8242_u32GetDivM (uint8 u8LocChIdx);
extern KPType TLE8242_u32GetKP (uint8 u8LocChIdx);
extern void TLE8242_vidSetKP (uint8 u8LocChIdx, KPType u32Lockp);
extern KIType TLE8242_u32GetKI (uint8 u8LocChIdx);
extern void TLE8242_vidSetKI (uint8 u8LocChIdx, KIType u32Locki);
extern void TLE8242_vidSetDitherStepSize (uint8 u8LocChIdx, DitherstepsizeType u16LocSize);
extern void TLE8242_vidSetOptEnaDeactive (uint8 u8LocChIdx, Tle8242OptEnableDeactiveType enuLocen);
extern void TLE8242_vidSetCrntTarBuf (uint8 u8LocChIdx, CurrentsetpointType f32LocCnrt);
extern CurrentsetpointType TLE8242_f32GetCrntTar (uint8 u8LocChIdx);
extern void TLE8242_vidSetDitherAmpBuf(uint8 u8LocChIdx, float32 f32LocCnrt);
extern float32 TLE8242_f32GetDitherAmp(uint8 u8LocChIdx);
extern DitherstepsizeType TLE8242_u16GetDitherStepSize (uint8 u8LocChIdx);
extern Tle8242OptEnableDeactiveType TLE8242GetOptEnableDeactive (uint8 u8LocChIdx);
extern void TLE8242_vidSetDitherFrqBuf(uint8 u8LocChIdx, float32 f32LocFrq);
extern float32 TLE8242GetDitherFrq(uint8 u8LocChIdx);
extern uint8 TLE8242_u16GetStepsNr(uint8 u8LocChIdx);
extern void TLE8242SetNumberOfSteps(uint8 u8LocChIdx, uint8 numberofsteps);
extern boolean TLE8242GetDitherEnabled(uint8 u8LocChIdx);
extern float32 TLE8242_f32GetCrntFb(uint8 u8LocChIdx, Tle8242CurrentType enuLocType);
extern Tle8242ValidType TLE8242_bGetCrntVld(uint8 u8LocChIdx, Tle8242CurrentType enuLocType);
extern boolean TLE8242_bGetGenericFalg(uint8 u8LocChIdx, Tle8242GenericFlagType enuLocType);
extern float32 TLE8242_f32GetPwmDutyCycle(uint8 u8LocChIdx);
extern void TLE8242_vidSetPwmDutyCycle(uint8 u8LocChIdx, float32 f32LocDuty);
extern uint32 TLE8242_u32CnvCrntToSetPoint(float32 f32LocCnrt);
extern float32 TLE8242_f32CnvpointToCrnt(uint32 u32LocSetPoint);

extern boolean TLE8242_bGetChOpenLoadFlt(uint8 u8LocChIdx);
extern boolean TLE8242_bGetChOverLoadFlt(uint8 u8LocChIdx);
extern boolean TLE8242_bGetChUnderLoadFlt(uint8 u8LocChIdx);
extern boolean TLE8242_bGetChGenFlt(uint8 u8LocChIdx);

#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#endif /* TLE8242_h */
