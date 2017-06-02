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
#include "TST_VADC.h"
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
void TST_ADC_vidInit(void)
{
	SWTST_kbADCTstEnaC = 0;
}

/**********************************************************************************************************************/
/* !Runnable    : TST_PWM_vidMainFunction                                                                             */
/* !Trigger     : 10ms                                                                                               */
/* !Description : To Read the ICU channels                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Doha Yousri                                                                                         */
/**********************************************************************************************************************/
void TST_ADC_vidMainFunction(void)
{
	uint8 bSply;

   if (SWTST_kbADCTstEnaC == TRUE)
   {
        IOHAL_f32Read_AN_DIAG_SOL_SW_2();
	  IOHAL_u16Read_AN_DIAG_SOL_SW_1();
	  IOHAL_u16Read_AN_TOSS();
	  IOHAL_u16Read_AN_C4_SPD_SNS();
	  IOHAL_u16Read_AN_RESERVED_TEMP_1();
	  IOHAL_u16Read_AN_PRI_OIL_TEMP();
	  IOHAL_u16Read_AN_TMP_PCB();
	  IOHAL_u16Read_AN_G4_SPD_SNS();
	  IOHAL_u16Read_AN_P5V_INTERNAL();
	  IOHAL_u16Read_AN_P5V_SNS_SUP_1();
	  IOHAL_u16Read_AN_VCC_3V3_SUP();
	  IOHAL_u16Read_AN_P9V_SNS_SUP();
	  IOHAL_u16Read_AN_VBAT_P_SW_SUP();
	  IOHAL_u16Read_AN_T15_IGN();
	  IOHAL_u16Read_AN_RESERVED_2();
	  IOHAL_u16Read_AN_RESERVED_1();
	  IOHAL_u16Read_AN_PRI_OIL_PRES();
	  IOHAL_u16Read_AN_T30_BATT();


	  ShrExp_Get_ADValue(SWTST_kbADCAdValueTstIdx, &SWTST_kbADCAdValueAdValue, &bSply);

	  ShrExp_Get_Battery(&SWTST_kbADCAdValueT30);

	  ShrExp_Get_Ignition(&SWTST_kbADCAdValueIG,&SWTST_kbADCAdIGONOFF);

	  ShrExp_Get_PressureAD(&SWTST_kbADCPressOil, &SWTST_kbADCPressOilDiag);

	  ShrExp_Get_ResistanceValue(&SWTST_kbADCResistValue, &SWTST_kbADCResistDiag);

	  Dio_Get_PCBTemp(&SWTST_kbADCPCBTemp);

	  
   }
}

#define TST_STOP_SEC_TST_CODE
#include"TST_MemMap.h"

/*----------------------------------------------------endoffile---------------------------------------------------*/
