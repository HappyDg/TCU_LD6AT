/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : SCU                                                                                             */
/*                                                                                                                    */
/* !Component       : SCU                                                                                             */
/* !Description     : SCU unit                                                                                        */
/*                                                                                                                    */
/* !Module          : SCU                                                                                             */
/* !Description     : API of SCU unit                                                                                 */
/*                                                                                                                    */
/* !File            : SCU.c                                                                                           */
/*                                                                                                                    */
/* !Target          : Aurix_TC27x                                                                                     */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* 1 / SCU_vidInit                                                                                                    */
/* 2 / SCU_vidUpdate50ms                                                                                              */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcal.h"
#include "Scu.h"
#include "Scu_l.h"
#include "IfxScu_reg.h"


#define SCU_START_SEC_CODE
#include "SCU_MemMap.h"

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SCU_vidInit                                                                                         */
/*                                                                                                                    */
/* !Description : Initializes SCU                                                                                     */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : Reset                                                                                                  */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void SCU_vidInit(void)
{
   Mcal_ResetENDINIT();
   MODULE_SCU.DTSCON.B.PWD = 0;

   MODULE_SCU.DTSLIM.B.LOWER = SCU_ku16MinDieTempThrd;
   MODULE_SCU.DTSLIM.B.UPPER = SCU_ku16MaxDieTempThrd;
   MODULE_SCU.DTSLIM.B.LLU = 0;
   MODULE_SCU.DTSLIM.B.UOF = 0;
   MODULE_SCU.DTSCON.B.START = 1;
 
   Mcal_SetENDINIT();
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SCU_vidUpdate50ms                                                                                   */
/*                                                                                                                    */
/* !Description : Updates DIE temperature and restarts the measurement                                                */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : TASK 50 ms                                                                                             */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void SCU_vidUpdate50ms(void)
{
   Ifx_SCU_DTSSTAT udtLocTemp;


   udtLocTemp = MODULE_SCU.DTSSTAT;
   if ((udtLocTemp.B.RDY != 0) && (udtLocTemp.B.BUSY == 0))
   {
      SCU_u16DieTemp = udtLocTemp.B.RESULT;
      MODULE_SCU.DTSCON.B.START = 1;
   }
}
/*---------------------------------------------------- end of file ---------------------------------------------------*/
