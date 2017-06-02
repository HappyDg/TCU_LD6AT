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
**  FILENAME  : SchM_Dem.h                                              **
**                                                                            **
**  VERSION   : 0.0.2                                                         **
**                                                                            **
**  DATE      : 2012.11.29                                                    **
**                                                                            **
**  PLATFORM  : Infineon Aurix                                                **
**                                                                            **
**  COMPILER  : Tasking                                                       **
**                                                                            **                                                                   **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
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
 * V0.0.2: 2012.11.29, Updated for AS4.0 support
 * V0.0.1: 2009.05.07, Initial version
 *
 */
#ifndef SCHM_DEM_H
#define SCHM_DEM_H

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

#define SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0() SuspendAllInterrupts()
#define SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0()  ResumeAllInterrupts()

#endif /* SCHM_DEM_H */