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

#define Idx_B1_SOL   0
#define Idx_C1_SOL   1
#define Idx_C2_SOL   2
#define Idx_C3_SOL   3
#define Idx_C4_SOL   4
#define Idx_LP_SOL   5
#define Idx_TC_SOL   6
#define Idx_RES_SOL  7

#define Idx_OUT0_8242   0
#define Idx_OUT1_8242   1
#define Idx_OUT2_8242   2
#define Idx_OUT3_8242   3
#define Idx_OUT4_8242   4
#define Idx_OUT5_8242   5
#define Idx_OUT6_8242   6
#define Idx_OUT7_8242   7




extern void ShrExp_Set_SolCarrierFreq(uint8 idx,uint16 fCarrier);
extern void ShrExp_Set_Solenoid(uint8 idx, uint8 mode, uint16 iout, uint16 iDth, uint16 fDth);
extern void ShrExp_Get_Solenoid(uint8 idx, uint16 *iln, uint8 *stDiaRdy, uint8 *stDiaDsbc);

#endif /* TLE8242_h */
