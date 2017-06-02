/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2012)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : SchM_NvM.h                                              **
**                                                                            **
**  VERSION   : 0.0.1                                                         **
**                                                                            **
**  DATE      : 2016.08.05                                                    **
**                                                                            **
**  PLATFORM  : Infineon Aurix                                                **
**                                                                            **
**  COMPILER  : Tasking                                                       **
**                                                                            **                                                                   **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Valeo                                         **
**                                                                            **
**  DESCRIPTION  : This header file exports the exclusive area                **
**                  functions.                                                **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: yes                                      **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Revision Control History                              **
*******************************************************************************/
/*
 *
 * V0.0.1: 2016.08.05, Updated for AS4.0 support
 *
 */

#ifndef SCHM_NVM_H
#define SCHM_NVM_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "Std_Types.h"

#include "Os.h"
/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*==================[external function declarations]=========================*/
#define SchM_Enter_NvM_SCHM_NVM_EXCLUSIVE_AREA_0() SuspendAllInterrupts()
#define SchM_Exit_NvM_SCHM_NVM_EXCLUSIVE_AREA_0()  ResumeAllInterrupts()

//#define SchM_Enter_Fls_17_Pmu_Init() SuspendAllInterrupts()
//#define SchM_Exit_Fls_17_Pmu_Init()  ResumeAllInterrupts()

//#define SchM_Enter_Fls_17_Pmu_Erase() SuspendAllInterrupts()
//#define SchM_Exit_Fls_17_Pmu_Erase()  ResumeAllInterrupts()

//#define SchM_Enter_Fls_17_Pmu_Write() SuspendAllInterrupts()
//#define SchM_Exit_Fls_17_Pmu_Write()  ResumeAllInterrupts()

//#define SchM_Enter_Fls_17_Pmu_Main() SuspendAllInterrupts()
//#define SchM_Exit_Fls_17_Pmu_Main()  ResumeAllInterrupts()

//#define SchM_Enter_Fls_17_Pmu_ResumeErase() SuspendAllInterrupts()
//#define SchM_Exit_Fls_17_Pmu_ResumeErase()  ResumeAllInterrupts()

#endif /* SCHM_FLS_LOADER_H */
