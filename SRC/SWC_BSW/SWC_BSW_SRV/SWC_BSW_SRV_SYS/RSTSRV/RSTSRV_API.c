/******************************************************************************/
/* !Layer           : SRVL                                                    */
/* !Component       : RSTSRV                                                  */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : RSTSRV_API.c                                            */
/* !Description     : APIs of RSTSRV Component                                */
/*                                                                            */
/* !Reference       : V03 NT 07 02929                                         */
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

#include "Std_Types.h"
#include "Std_Limits.h"
#include "DEVHAL.h"
#include "Mcu.h"
#include "SchM_RSTSRV.h"
#include "RSTSRV.h"
#include "RSTSRV_Private.h"
#include "STARTUP.h"
#include "SUPSRV.h"
#include "SWFAIL.h"

#define RSTSRV_START_SEC_CODE
#include "RSTSRV_MemMap.h"

/******************************************************************************/
/* !FuncName    : RSTSRV_vidInit                                              */
/* !Description :                                                             */
/*                                                                            */
/* !LastAuthor  : L. Voilmy                                                   */
/******************************************************************************/
void RSTSRV_vidInit(void)
{
   Mcu_ResetType udtLocalResetIndicator;


   udtLocalResetIndicator = Mcu_GetResetReason();

   if (  (udtLocalResetIndicator == MCU_POWER_ON_RESET)
      || (udtLocalResetIndicator == MCU_EVR13_RESET)
      || (udtLocalResetIndicator == MCU_EVR33_RESET)
      || (udtLocalResetIndicator == MCU_SUPPLY_WDOG_RESET)
      || (udtLocalResetIndicator == MCU_RESET_UNDEFINED) )
   {
      RSTSRV_bSWResetDetected = FALSE;
   }
   else
   {
      RSTSRV_bSWResetDetected = TRUE;
   }

   RSTSRV_u32ResetReason             = (uint32)udtLocalResetIndicator;
   RSTSRV_bSWResetDoneByPerformReset = RSTSRV_bSWResetRequested;
   RSTSRV_bSWResetRequested          = FALSE;
   RSTSRV_u16TimeAfterInit           = 0;
   RSTSRV_vidInitEntry();
}

/******************************************************************************/
/* !FuncName    : RSTSRV_udtReadResetState                                    */
/* !Description :                                                             */
/*                                                                            */
/* !TraceTo     : VEES_R_07_02929_001.01                                      */
/* !TraceTo     : VEES_R_07_02929_002.01                                      */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
RSTSRV_tudtResetType RSTSRV_udtReadResetState(void)
{
   RSTSRV_tudtResetType udtLocalResetType;


   if (RSTSRV_bSWResetDetected == TRUE)
   {
      udtLocalResetType = RSTSRV_udtSOFTWARE_RESET;
   }
   else
   {
      if (((sint32)RSTSRV_u16HotResetCtr) <= 1)
      {
         udtLocalResetType = RSTSRV_udtNORMAL_STARTUP_RESET;
      }
      else
      {
         udtLocalResetType = RSTSRV_udtHARDWARE_RESET;
      }
   }
   return(udtLocalResetType);
}

/******************************************************************************/
/* !FuncName    : RSTSRV_vidPerformReset                                      */
/* !Description :                                                             */
/*                                                                            */
/* !TraceTo     : VEES_R_07_02929_003.01                                      */
/* !TraceTo     : VEES_R_07_02929_004.01                                      */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void RSTSRV_vidPerformReset(RSTSRV_tudtResetType udtRequestedResetType)
{
   RSTSRV_bSWResetRequested = TRUE;

   switch(udtRequestedResetType)
   {
   case RSTSRV_udtSOFTWARE_RESET:
      SchM_Enter_RSTSRV_ACCESS_001();
      Mcu_PerformReset();
      while (1);
      break;

   case RSTSRV_udtHARDWARE_RESET:
      SchM_Enter_RSTSRV_ACCESS_001();
      STARTUP_vidReqAllRamClearAtInit();
      Mcu_PerformReset();
      while (1);
      break;

   case RSTSRV_udtNORMAL_STARTUP_RESET:
   default:
      SWFAIL_vidSoftwareErrorHook();
      break;
   }
}

/******************************************************************************/
/* !FuncName    : RSTSRV_vidPermanentResetProtect                             */
/* !Description : In case the software resets continuously, jump to loader    */
/*                to be able to download a new software                       */
/*                                                                            */
/* !LastAuthor  : J. Soufflet                                                 */
/******************************************************************************/
void RSTSRV_vidPermanentResetProtect(void)
{
   if (  (RSTSRV_u16ConsecutiveRstCtr < RSTSRV_ku16ConsecutiveRstMaxNbC)
      || (RSTSRV_ku16ConsecutiveRstMaxNbC == 0) )
   {
      RSTSRV_u16ConsecutiveRstCtr++;
   }
   else
   {
      SUPSRV_vidJumpToLoader();
   }
}

#define RSTSRV_STOP_SEC_CODE
#include "RSTSRV_MemMap.h"

/*------------------------------- end of file --------------------------------*/
