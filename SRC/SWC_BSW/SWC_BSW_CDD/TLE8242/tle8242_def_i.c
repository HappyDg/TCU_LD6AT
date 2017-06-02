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
/* !File            : tle8242_def.c                                                                                  */
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
/* Author::   gsun5                               Date::   Jan 18, 2017                               */
/**********************************************************************************************************************/


#include "tle8242_def_i.h"

/********************************************************************************/
/* tle8242 control parameters                                                   */
/********************************************************************************/
// variable
#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
float TLE8242Target[NUMBER_OF_TLE8242_CHANNEL];
float TLE8242PWMFrq[NUMBER_OF_TLE8242_CHANNEL]={3000,3000,3000,3000,3000,3000,3000,3000};
uint16 TLE8242KP[NUMBER_OF_TLE8242_CHANNEL] = {4095,4095,4095,4095,4095,4095,4095,4095};
uint16 TLE8242KI[NUMBER_OF_TLE8242_CHANNEL] = {700,700,700,700,700,700,700,700};
float TLE8242DitherAmpl[NUMBER_OF_TLE8242_CHANNEL];
float TLE8242DitherFreq[NUMBER_OF_TLE8242_CHANNEL];
float TLE8242DutyCycle[NUMBER_OF_TLE8242_CHANNEL];

// calibration

uint8 TLE8242OpenLoopC[NUMBER_OF_TLE8242_CHANNEL];
float TLE8242DutyCycleC[NUMBER_OF_TLE8242_CHANNEL];
/********************************************************************************/
/* tle8242 read back value                                                      */
/********************************************************************************/
//
float TLE8242AvgCurma[NUMBER_OF_TLE8242_CHANNEL];
float TLE8242MaxCurma[NUMBER_OF_TLE8242_CHANNEL];
float TLE8242MinCurma[NUMBER_OF_TLE8242_CHANNEL];
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
const float TLE8242ChopperFrqMinC = 1000;
const float TLE8242ChopperFrqMaxC = 6000;
#define TLE8242_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* #define TLE8242_START_SEC_CALIB_UNSPECIFIED
#include "MemMap.h"
const float TLE8242Target_test = 0;
#define TLE8242_STOP_SEC_CALIB_UNSPECIFIED
#include "MemMap.h" */



/********************************************************************************/
/* tle8242 read back value                                                      */
/********************************************************************************/
// tle8242
