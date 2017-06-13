/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           :TLE8242                                                                                            */
/*                                                                                                                    */
/* !Component       :TLE8242                                                                                             */
/* !Description     :TLE8242 api                                                                                    */
/*                                                                                                                    */
/* !Module          :TLE8242                                                                                             */
/* !Description     :                                                                           */
/*                                                                                                                    */
/* !File            : TLE8242_api.h                                                                                  */
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
#ifndef TLE8242_api_h
#define TLE8242_api_h



 #define TLE8242_vidSetCrntTar(snChannel, snValue) \
   TLE8242_au16CrntChg |= (1<<snChannel);\
   TLE8242_af32TarCnrtMa[snChannel] = (f32Value)

 #define TLE8242_vidSetDitherFrq(snChannel, snValue) \
   TLE8242_au16DitherFrqChg |= (1<<snChannel);\
   TLE8242_af32DitherFrq[snChannel] = (f32Value)

 #define TLE8242_vidSetDitherAmp(snChannel, snValue) \
   TLE8242_au16DitherAmpChg |= (1<<snChannel);\
   TLE8242_af32DitherAmplMa[snChannel] = (f32Value)

#define TLE8242_vidSetPwmDuty(snChannel, snValue) \
   TLE8242_au16DutyCycleChg |= (1<<snChannel);\
   TLE8242_af32DutyCycle[snChannel] = (f32Value)


#define TLE8242_f32GetAvgCrnt(snChannel) \
		TLE8242_af32AvgCrntMa[snChannel]

#define TLE8242_f32GetMaxCrnt(snChannel) \
	TLE8242_af32MaxCnrtMa[snChannel]

#define TLE8242_f32GetMinCrnt(snChannel) \
	TLE8242_af32MinCnrtMa[snChannel]

#define TLE8242_f32GetPwmDutyFb(snChannel) \
    TLE8242_af32PwmDutyFb[snChannel]
#endif /* TLE8242_api_h */
