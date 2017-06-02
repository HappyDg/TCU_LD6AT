/***************************** <AUTO_FILE_HEADER> *****************************/
/*                                                                            */
/* !Layer           : APPLI                                                   */
/*                                                                            */
/* !Component       : MAIN                                                    */
/* !Description     :                                                         */
/*                                                                            */
/* !Module          : MAIN                                                    */
/* !Description     : API of the Component                                    */
/*                                                                            */
/* !File            : SWC_BSW_MAIN.H                                          */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2008 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/**************************** </AUTO_FILE_HEADER> *****************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::                                                               $*/
/* $Author::                                          $$Date::               $*/
/******************************************************************************/
/* !VnrOff  : Names imposed by the customer                                   */
/* !CompReq :                                                                 */
/******************************************************************************/

#ifndef SWC_BSW_MAIN_H
#define SWC_BSW_MAIN_H

#include "Std_Limits.h"
#include "Std_Types.h"

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/


/******************************************************************************/
/* TYPES                                                                      */
/******************************************************************************/


/******************************************************************************/
/* CALIBRATIONS DECLARATION                                                   */
/******************************************************************************/


/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/


/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/
FUNC(void, MAIN_CODE) MAIN_vidAdcCallBackGroup1(void);
FUNC(void, MAIN_CODE) MAIN_vidAdcCallBackGroup2(void);
FUNC(void, MAIN_CODE) MAIN_vidAdcCallBackGroup3(void);
FUNC(void, MAIN_CODE) MAIN_vidAdcCallBackGroup4(void);


#endif /* SWC_BSW_MAIN_H */

/*-------------------------------- end of file -------------------------------*/
