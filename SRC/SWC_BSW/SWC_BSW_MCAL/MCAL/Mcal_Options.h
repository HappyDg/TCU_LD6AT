/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2014)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Mcal_Options.h $                                           **
**                                                                           **
**  $CC VERSION : \main\4 $                                                  **
**                                                                           **
**  $DATE       : 2014-11-07 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION  : This header file configures pre-compile switches          **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                           **
******************************************************************************/

#ifndef MCAL_OPTIONS_H
#define MCAL_OPTIONS_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* 
   Configuration:
   IFX_MCAL_USED :
   Pre-Compile switch to enable stand alone Mcal
   IFX_SAFETLIB_USED:
   Pre-Compile switch to enable Standalone safeTlib
*/

#define IFX_MCAL_USED          (STD_ON)
#define IFX_SAFETLIB_USED      (STD_OFF)
/* Pre-Compile switch to enable/disable DEM module version check */
#define IFX_DEM_VERSION_CHECK  (STD_ON)
/* Pre-Compile switch to enable/disable DET module version check */
#define IFX_DET_VERSION_CHECK  (STD_ON)
/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/


/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/



#endif /* MCAL_OPTIONS_H */