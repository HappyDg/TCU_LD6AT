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
/* Author::   gsun5                               Date::   Jan 18, 2017                               */
/**********************************************************************************************************************/
#ifndef TLE8242_h
#define TLE8242_h

#include "tle8242_cfg.h"
#include "tle8242_def_i.h"
#include "tle8242_interface.h"
#include "Trim_8242.h"

#define TLE8242_START_SEC_CODE
#include "MemMap.h"
extern void TLE8242_VidInit(void);
extern void TLE8242_VidParseResponse(void);
extern void TLE8242_vidCtrlManagement(void);
extern void TLE8242_vidFaultDet(void);
#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"

#endif /* TLE8242_h */
