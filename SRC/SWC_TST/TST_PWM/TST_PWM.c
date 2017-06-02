/**********************************************************************************************************************/
/* !Layer           : TST                                                                                             */
/* !Component       : TST_PWM                                                                                         */
/* !Description     : Test Code For PWM Component                                                                     */
/*                                                                                                                    */
/* !File            : TST_PWM.c                                                                                       */
/* !Description     : TST_PWM test APIs                                                                               */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/

#include "Std_Types.h"
#include "STD_LIMITS.h"
#include "TST_PWM.h"
#include "SWTST.h"
#include "BSW.h"
#include "IOHAL.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

/**********************************************************************************************************************/
/* !Runnable    : TST_PWM_vidInit                                                                                     */
/* !Trigger     : Reset                                                                                               */
/* !Description : Initializes the PWM data                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Doha Yousri                                                                                         */
/**********************************************************************************************************************/
void TST_PWM_vidInit(void)
{
	TST_PWM_f32PWM_FRQ_M_TLE8242_CLK						   = 0.1f;
	TST_PWM_s16PWM_DUTY_M_TLE8242_CLK                         = 0u;
	TST_PWM_bPWM_ENA_M_TLE8242_CLK                            = FALSE;

#if 0
   TST_PWM_f32PWM_FRQ_DCDC_ISETD                          = 0.1f;
   TST_PWM_f32PWM_FRQ_DCDC_SYNC                           = 0.1f;
   TST_PWM_f32PWM_FRQ_ACCUMULATOR_SOLENOID_DRIVE          = 0.1f;

   TST_PWM_s16PWM_DUTY_DCDC_ISETD                         = 0u;
   TST_PWM_s16PWM_DUTY_DCDC_SYNC                          = 0u;
   TST_PWM_s16PWM_DUTY_ACCUMULATOR_SOLENOID_DRIVE         = 0u;

   TST_PWM_bPWM_ENA_DCDC_ISETD                            = FALSE;
   TST_PWM_bPWM_ENA_DCDC_SYNC                             = FALSE;
   TST_PWM_bPWM_ENA_ACCUMULATOR_SOLENOID_DRIVE            = FALSE;
 #endif
}

/**********************************************************************************************************************/
/* !Runnable    : TST_PWM_vidMainFunction                                                                             */
/* !Trigger     : 10ms                                                                                               */
/* !Description : To Read the ICU channels                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Doha Yousri                                                                                         */
/**********************************************************************************************************************/
void TST_PWM_vidMainFunction(void)
{

   if (SWTST_kbPwmTstEnaC == TRUE)
   {

   //IOHWABS_udtWRITE_CHANNEL(PWM_FRQ_M_TLE8242_CLK_TST, TST_PWM_f32PWM_FRQ_M_TLE8242_CLK);
   //IOHWABS_udtWRITE_CHANNEL(PWM_DUTY_M_TLE8242_CLK_TST, TST_PWM_s16PWM_DUTY_M_TLE8242_CLK);
   //IOHWABS_udtWRITE_CHANNEL(PWM_ENA_M_TLE8242_CLK_TST, TST_PWM_bPWM_ENA_M_TLE8242_CLK);

   IOHWABS_udtWRITE_CHANNEL(PWM_FRQ_M_TLE8242_CLK, TST_PWM_f32PWM_FRQ_M_TLE8242_CLK);
   IOHWABS_udtWRITE_CHANNEL(PWM_DUTY_M_TLE8242_CLK, TST_PWM_s16PWM_DUTY_M_TLE8242_CLK);
   IOHWABS_udtWRITE_CHANNEL(PWM_ENA_M_TLE8242_CLK, TST_PWM_bPWM_ENA_M_TLE8242_CLK);
   #if 0
      IOHWABS_udtWRITE_CHANNEL(PWM_FRQ_DCDC_ISETD,TST_PWM_f32PWM_FRQ_DCDC_ISETD);
      IOHWABS_udtWRITE_CHANNEL(PWM_FRQ_DCDC_SYNC,TST_PWM_f32PWM_FRQ_DCDC_SYNC);
	  IOHWABS_udtWRITE_CHANNEL(PWM_FRQ_ACCUMULATOR_SOLENOID_DRIVE,TST_PWM_f32PWM_FRQ_ACCUMULATOR_SOLENOID_DRIVE);

   
      IOHWABS_udtWRITE_CHANNEL(PWM_DUTY_DCDC_ISETD,TST_PWM_s16PWM_DUTY_DCDC_ISETD);
      IOHWABS_udtWRITE_CHANNEL(PWM_DUTY_DCDC_SYNC,TST_PWM_s16PWM_DUTY_DCDC_SYNC);
	  IOHWABS_udtWRITE_CHANNEL(PWM_DUTY_ACCUMULATOR_SOLENOID_DRIVE,TST_PWM_s16PWM_DUTY_ACCUMULATOR_SOLENOID_DRIVE);
     
      IOHWABS_udtWRITE_CHANNEL(PWM_ENA_DCDC_ISETD,TST_PWM_bPWM_ENA_DCDC_ISETD);
      IOHWABS_udtWRITE_CHANNEL(PWM_ENA_DCDC_SYNC,TST_PWM_bPWM_ENA_DCDC_SYNC);
	  IOHWABS_udtWRITE_CHANNEL(PWM_ENA_ACCUMULATOR_SOLENOID_DRIVE,TST_PWM_bPWM_ENA_ACCUMULATOR_SOLENOID_DRIVE);

	#endif
   }
}

#define TST_STOP_SEC_TST_CODE
#include"TST_MemMap.h"

/*----------------------------------------------------endoffile---------------------------------------------------*/
