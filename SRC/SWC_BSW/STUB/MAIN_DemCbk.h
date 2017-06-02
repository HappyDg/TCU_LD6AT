/******************************************************************************/
/*                                                                            */
/* !Layer          : Layer                                                    */
/*                                                                            */
/* !Component      : Component                                                */
/* !Description    : Component description                                    */
/*                                                                            */
/* !Module         : MODULE                                                   */
/* !Description    : MODULE description                                       */
/*                                                                            */
/* !File           : MAIN_DemCbk.H                                               */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : Infineon_tc27                                            */
/*                                                                            */
/* !Vendor         : VALEO                                                    */
/*                                                                            */
/* !Author         : A. Abohassan                                             */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2006 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   $ */
/* $Revision::  $ */
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/

#ifndef MAIN_DEMCBK_H
#define MAIN_DEMCBK_H

#include "Dem.h"

#define MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"
/**********************************************************************************************************************/
/* PUBLIC DEFINES                                                                                                     */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* PRIVATE MACRO FUNCTIONS                                                                                            */
/**********************************************************************************************************************/
extern Std_ReturnType MAIN_DemDidElementReadApmElecValU14( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);
extern Std_ReturnType MAIN_DemDidElementReadApmElecValI14( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);
extern Std_ReturnType MAIN_DemDidElementReadApmElecValUHV( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);
extern Std_ReturnType MAIN_DemDidElementReadApmElecValIHV( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);
extern Std_ReturnType MAIN_DemDidElementReadApmElecValTemp( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);


#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"

#endif /* MAIN_DEMCBK_H */
/*------------------------------ end of file ------------------------------*/
