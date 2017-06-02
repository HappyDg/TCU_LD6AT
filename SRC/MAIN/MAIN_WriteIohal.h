/* *****************************************************************************/
/*                                                                             */
/* !Layer          : Layer                                                    */
/*                                                                            */
/* !Component      : Component                                                */
/* !Description    : Component description                                    */
/*                                                                            */
/* !Module         : MODULE                                                   */
/* !Description    : MODULE description                                       */
/*                                                                            */
/* !File           : MAIN_WriteIohal.h                                        */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : Infineon_tc27x                                           */
/*                                                                            */
/* !Vendor         : VALEO                                                    */
/*                                                                            */
/* !Author         : J. ZHANG                                                 */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2016 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/* ****************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   $                                                             */
/* $Revision::  $                                                             */
/* ****************************************************************************/
/* !VnrOff :                                                                  */
/* ****************************************************************************/
#ifndef MAIN_WRITE_IOHAL_H
#define MAIN_WRITE_IOHAL_H

#include "IOHAL_Api.h"


#define  MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"

//extern boolean ACCUMULATOR_SOLENOID_DRIVE;
extern boolean MCU_TORQUE_ENABLE_OUTPUT_DRIVE;
extern boolean PWR_LATCH;
 
/* ****************************************************************************/
/*                                                                            */
/* !$item_header $item_name                                                   */
/* !Trigger     :                                                             */
/* !Description :                                                             */
/* !Number      :                                                             */
/* !Reference   : NONE                                                        */
/*                                                                            */
/* ****************************************************************************/
inline void Main_vidIOHAL_SngSetVle(void)
{
   //IOHAL_vidWriteUdt_ACCUMULATOR_SOLENOID_DRIVE(ACCUMULATOR_SOLENOID_DRIVE);
   //IOHAL_vidWriteUdt_MCU_TORQUE_ENABLE_OUTPUT_DRIVE(MCU_TORQUE_ENABLE_OUTPUT_DRIVE);
   //IOHAL_vidWriteUdt_PWR_LATCH(PWR_LATCH);
}

#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"

#endif /* MAIN_WRITE_IOHAL_H */
/*------------------------------ end of file ------------------------------*/