/**********************************************************************************************************************/
/* !Layer           : TST                                                                                             */
/* !Component       : TST_PWD                                                                                         */
/* !Description     : Test Code For PWD Component                                                                     */
/*                                                                                                                    */
/* !File            : TST_PWD.c                                                                                       */
/* !Description     : TST_PWD test APIs                                                                               */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/

#include "Std_Types.h"
#include "STD_LIMITS.h"
#include "TST_PWD.h"
#include "SWTST.h"
#include "BSW.h"
#include "IOHAL.h"
#include "Icu_17_GtmCcu6.h"


#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

/**********************************************************************************************************************/
/* !Runnable    : TST_PWD_vidInit                                                                                     */
/* !Trigger     : Reset                                                                                               */
/* !Description : Initializes the PWD data                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Doha Yousri                                                                                         */
/**********************************************************************************************************************/
void TST_PWD_vidInit(void)
{
	uint8 Speed[3] = {20, 30, 60};
	
	TST_PWD_u32_M_GEAR_POS_PWM_FRQ = 0;
	TST_PWD_u32_M_GEAR_POS_PWM_DUTYCYC = 0;
	TST_PWD_u32_M_GEAR_POS_CHECK_PWM_FRQ = 0;
	TST_PWD_u32_M_GEAR_POS_CHECK_PWM_DUTYCYC = 0;
	TST_PWD_u32_M_TOSS_PWM_FRQ = 0;
	TST_PWD_u32_M_TOSS_PWM_DUTYCYC = 0;
	TST_PWD_u32_M_G4_SPD_SNS_PWM_FRQ = 0;
	TST_PWD_u32_M_G4_SPD_SNS_PWM_DUTYCYC = 0;
	TST_PWD_u32_M_C4_SPD_SNS_PWM_FRQ = 0;
	TST_PWD_u32_M_C4_SPD_SNS_PWM_DUTYCYC = 0;

	Shrexp_set_Speed(&(Speed[0]));

}

/**********************************************************************************************************************/
/* !Runnable    : TST_PWD_vidMainFunction                                                                             */
/* !Trigger     : 10ms                                                                                               */
/* !Description : To Read the ICU channels                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Doha Yousri                                                                                         */
/**********************************************************************************************************************/


void TST_PWD_vidMainFunction(void)
{
#if 1
	uint8 idx;
	uint16 n;
	uint8 sDir;
	uint8 bSply;
	uint8 stDiaRdy;
	uint8 stDiaDsbc;
	
	uint32 Temp;
#endif
   if (SWTST_kbPwdTstEnaC == TRUE)
	{
	
		TST_PWD_u32_M_GEAR_POS_PWM_FRQ		   =		IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_PWM_FRQ);
	      TST_PWD_u32_M_GEAR_POS_PWM_DUTYCYC		=		 IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_PWM_DUTYCYC);

	      TST_PWD_u32_M_GEAR_POS_CHECK_PWM_FRQ		  = 	   IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_CHECK_PWM_FRQ);
		TST_PWD_u32_M_GEAR_POS_CHECK_PWM_DUTYCYC	   =		IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_CHECK_PWM_DUTYCYC);
	
	      TST_PWD_u32_M_TOSS_PWM_FRQ		  = 	   IOHWABS_udtREAD_CHANNEL(M_TOSS_PWM_FRQ);
		TST_PWD_u32_M_TOSS_PWM_DUTYCYC	   =		IOHWABS_udtREAD_CHANNEL(M_TOSS_PWM_DUTYCYC);

	      TST_PWD_u32_M_G4_SPD_SNS_PWM_FRQ          =        IOHWABS_udtREAD_CHANNEL(M_G4_SPD_SNS_PWM_FRQ);
            TST_PWD_u32_M_G4_SPD_SNS_PWM_DUTYCYC      =        IOHWABS_udtREAD_CHANNEL(M_G4_SPD_SNS_PWM_DUTYCYC);

	     TST_PWD_u32_M_C4_SPD_SNS_PWM_FRQ 	 =  IOHWABS_udtREAD_CHANNEL(M_C4_SPD_SNS_PWM_FRQ);
	     TST_PWD_u32_M_C4_SPD_SNS_PWM_DUTYCYC = IOHWABS_udtREAD_CHANNEL(M_C4_SPD_SNS_PWM_DUTYCYC);

	    //ShrExp_Get_Speed(SWTST_kbPwdSpeedTstIdx,&SWTST_kbPwdSpeedTstRPM, &SWTST_kbPwdSpeedTstDir, &bSply, &stDiaRdy, &stDiaDsbc);
	    //ShrExp_Get_Position(SWTST_kbPwdPositionTstIdx, &SWTST_kbPwdPositionTstDuty, &bSply, &stDiaRdy, &stDiaDsbc);

	   
	}
    if(SWTST_kbPwdTstWrapperEnaC == TRUE)
	{
		ShrExp_Get_Speed(SWTST_kbPwdSpeedTstIdx,&SWTST_kbPwdSpeedTstRPM, &SWTST_kbPwdSpeedTstDir, &bSply, &stDiaRdy, &stDiaDsbc);
	      ShrExp_Get_Position(SWTST_kbPwdPositionTstIdx, &SWTST_kbPwdPositionTstDuty, &bSply, &stDiaRdy, &stDiaDsbc);
	}
}

#if 0
void Shrexp_set_Speed ( uint8 nPlsPerRe[])
{
	*nPlsPerRe = 20;
	*(nPlsPerRe+1) = 30;
	*(nPlsPerRe+2) = 60;
}
#endif

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
