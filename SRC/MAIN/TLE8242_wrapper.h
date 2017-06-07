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
/* !File            : TLE8242_wrapper.h                                                                                  */
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
/* Author::   Liping                               Date::   Feb 22, 2017                                         */
/**********************************************************************************************************************/
#ifndef TLE8242_wrapper_h
#define TLE8242_wrapper_h

#include "Std_Types.h"
#include "TLE8242_reg.h"
#include "TLE8242_cfg.h"
#include "TLE8242.h"




extern void ShrExp_Set_SolCarrierFreq(uint8 idx,uint16 fCarrier);
extern void ShrExp_Set_Solenoid(uint8 idx, uint8 mode, uint16 iout, uint16 iDth, uint16 fDth);
extern void ShrExp_Get_Solenoid(uint8 idx, uint16 *iln, uint8 *stDiaRdy, uint8 *stDiaDsbc);

#endif /* TLE8242_h */
