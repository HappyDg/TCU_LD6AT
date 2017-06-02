/******************************************************************************/
/* !Layer           : TST                                                     */
/* !Component       : TST_GPT                                                 */
/* !Description     : Test of Gpt component                                   */
/*                                                                            */
/* !File            : GPT_TST.c                                               */
/* !Description     : Test of Gpt component                                   */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT VALEO all rights reserved                                        */
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#include "Gpt.h"
#include "Dio.h"
//#include "INTBSL.h"
#include "TST_GPT.h"
#include "TST_GPT_Cfg.h"
#include "IOHAL.h"
#include "SWTST_L.h"

#define TST_START_SEC_TST_VAR
#include "TST_MemMap.h"

uint8 TST_GPT_u8StartTimer;
uint32 TST_GPT_u32TimerVal;
uint32 TST_GPT_u32DesiredPeriod;
uint32 TST_GPT_u32LastPeriod;

#define TST_STOP_SEC_TST_VAR
#include "TST_MemMap.h"

/******************************************************************************/
/* GLOBAL FUNCTIONS DEFINITION                                                */
/******************************************************************************/

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

/******************************************************************************/
/* !FuncName    : TST_GPT_vidInit                                             */
/* !Description : Initialization of TST_GPT internal variables                */
/* !LastAuthor  : D. Yousri                                                   */
/******************************************************************************/
void TST_GPT_vidInit(void)
{
 
}

/******************************************************************************/
/* !FuncName    : TST_GPT_StartTimer                                          */
/* !Description : Start both the One-shot and continous Gpt timers            */
/*              : with TST_GPT_u32TimerVal                                    */
/* !LastAuthor  : D. Yousri                                                   */
/******************************************************************************/
void TST_GPT_StartTimer(void)
{
 
}

/******************************************************************************/
/* !FuncName    : TST_GPT_StopTimer                                           */
/* !Description : Stop both the One-shot and continous Gpt timers             */
/* !LastAuthor  : D. Yousri                                                   */
/******************************************************************************/
void TST_GPT_StopTimer(void)
{

}

/******************************************************************************/
/* !FuncName    : TST_GPT_vidMainFunction                                     */
/* !Description : Main function for the GPT test file.                        */
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
void TST_GPT_vidMainFunction(void)
{ 

}

/******************************************************************************/
/* !FuncName    : TST_GPT_vidOneShotNotification                              */
/* !Description : Notification function to be called at timer event/end       */
/*              : of period for One-shot channels.                            */
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
void TST_GPT_vidOneShotNotification(void)
{
 
}

/******************************************************************************/
/* !FuncName    : TST_GPT_TestApi                            */
/* !Description :       */
/* !LastAuthor  :                                                */
/******************************************************************************/
void TST_GPT_TestApi(void)
{
   if(TST_kbFrtEnable)
   {
      TST_u32TM1msGlbCnt   = IOHWABS_udtREAD_CHANNEL(TM1msGlbCnt); 
      TST_u32TM5msGlbCnt   = IOHWABS_udtREAD_CHANNEL(TM5msGlbCnt); 
      
      TST_u32TM10msGlbCnt = IOHWABS_udtREAD_CHANNEL(TM10msGlbCnt);
      TST_u32TM30msGlbCnt = IOHWABS_udtREAD_CHANNEL(TM30msGlbCnt);
      
      TST_u32TM100msGlbCnt = IOHWABS_udtREAD_CHANNEL(TM100msGlbCnt);
      TST_u32TM500msGlbCnt = IOHWABS_udtREAD_CHANNEL(TM500msGlbCnt);
      TST_u32TM1sGlbCnt = IOHWABS_udtREAD_CHANNEL(TM1sGlbCnt);
   }

}

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

/*------------------------------- end of file --------------------------------*/
