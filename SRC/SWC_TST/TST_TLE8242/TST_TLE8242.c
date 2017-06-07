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
#include "TST_TLE8242.h"
#include "SWTST.h"
#include "BSW.h"
#include "IOHAL.h"
#include "TLE8242_def.h"
#include "Trim_8242.h"
#include "SWTST_L.h"
#include "TLE8242_wrapper.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"


uint8 SW_TST_TLE8242_Idx = 0;
uint16 SW_TST_TLE8242_PWMFreq[8] = {3000};
uint16 SW_TST_TLE8242_Iout[8] = {0};
uint8 SW_TST_TLE8242_Mode[8] = {0};
uint16 SW_TST_TLE8242_DitherAmp[8] = {0};
uint16 SW_TST_TLE8242_DitherFreq[8] = {0};

/**********************************************************************************************************************/
/* !Runnable    : TST_TLE8242_vidInit                                                                                     */
/* !Trigger     : Reset                                                                                               */
/* !Description : Initializes the TLE8242 data                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Liping.Liu                                                                                         */
/**********************************************************************************************************************/
void TST_TLE8242_vidInit(void)
{

}

/**********************************************************************************************************************/
/* !Runnable    : TST_TLE8242_vidMainFunction                                                                             */
/* !Trigger     : 10ms                                                                                               */
/* !Description :                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Liping.Liu                                                                                          */
/**********************************************************************************************************************/
void TST_TLE8242_vidMainFunction(void)
{
	uint8 u8LocTstCase;
	static uint16 fb_ilin = 0;
	static uint8 stDiaRdy = 0;
	static uint8 stDiaDsbc = 0;

	#if 0
	if(SWTST_kbTle8242TstEnaC == TRUE)
	{
		u8LocTstCase = SWTST_u8TLE8242TstCase;
		
		switch (u8LocTstCase)
        {
			case 2:
         /* do some actions */

/* 				for(i = 0; i < NUMBER_OF_TLE8242_CHANNEL; ++i)
				{
					TLE8242Target[i] = TST_f32TLE8242Target[i];
					TLE8242PWMFrq[i] = TST_f32TLE8242PWMFrq[i];
					TLE8242KP[i] = TST_u16TLE8242KP[i];
					TLE8242KI[i] = TST_u16TLE8242KI[i];
					TLE8242DitherAmpl[i] = TST_f32TLE8242DitherAmpl[i];
					TLE8242DitherFreq[i] = TST_f32TLE8242DitherFreq[i];
					TLE8242DutyCycle[i] = TST_f32TLE8242DutyCycle[i];
					TLE8242DutyCycleC[i] = TST_f32TLE8242DutyCycleC[i];
					TLE8242OpenLoopC[i] = TST_u8TLE8242OpenLoopC[i];
				} */
			break;
			
			case 1:
			/* do some actions */
			    if((BSW_u8TLE8242CHIndex_Temp != TST_u8TLE8242CHIndex)||(BSW_f32TLE8242_Target_Temp != TST_f32TLE8242_Target)||(BSW_f32TLE8242_DitherAmpl_Temp != TST_f32TLE8242_DitherAmpl)||(BSW_f32TLE8242_DitherFreq_Temp != TST_f32TLE8242_DitherFreq))
				{
					BSW_bTle8242Flag = 1;
				}
				else
				{
					BSW_bTle8242Flag = 0;
				}
				/* do the trim function*/
				TLE8242Target[TST_u8TLE8242CHIndex] = Trim_CalculateGainAndOffset(TST_u8TLE8242CHIndex,(uint16)TST_f32TLE8242_Target);
				TLE8242PWMFrq[TST_u8TLE8242CHIndex] = TST_f32TLE8242_PWMFrq;
				TLE8242KP[TST_u8TLE8242CHIndex] = TST_u16TLE8242_KP;
				TLE8242KI[TST_u8TLE8242CHIndex] = TST_u16TLE8242_KI;
				TLE8242DitherAmpl[TST_u8TLE8242CHIndex] = TST_f32TLE8242_DitherAmpl;
				TLE8242DitherFreq[TST_u8TLE8242CHIndex] = TST_f32TLE8242_DitherFreq;
				TLE8242DutyCycle[TST_u8TLE8242CHIndex] = TST_f32TLE8242_DutyCycle;
				TLE8242DutyCycleC[TST_u8TLE8242CHIndex] = TST_f32TLE8242_DutyCycleC;
				TLE8242OpenLoopC[TST_u8TLE8242CHIndex] = TST_u8TLE8242_OpenLoopC;
			
				/*backup the data*/
				BSW_u8TLE8242CHIndex_Temp = TST_u8TLE8242CHIndex;
				BSW_f32TLE8242_Target_Temp = TST_f32TLE8242_Target;
				BSW_f32TLE8242_DitherAmpl_Temp = TST_f32TLE8242_DitherAmpl;
				BSW_f32TLE8242_DitherFreq_Temp = TST_f32TLE8242_DitherFreq;
				
				
			
			break;

			default:
         /* Do nothing */
			break;
   		}

	}
	#endif

	
	ShrExp_Set_SolenoidFeed(SWTST_kbDioWr_Set_SolenoidFeedIdx, SWTST_kbDioWr_Set_SolenoidFeedOnOff);

	ShrExp_Set_SolCarrierFreq(SW_TST_TLE8242_Idx,SW_TST_TLE8242_PWMFreq[SW_TST_TLE8242_Idx]);
	ShrExp_Set_Solenoid(SW_TST_TLE8242_Idx,SW_TST_TLE8242_Mode[SW_TST_TLE8242_Idx], \
		                                   SW_TST_TLE8242_Iout[SW_TST_TLE8242_Idx], \
		                                   SW_TST_TLE8242_DitherAmp[SW_TST_TLE8242_Idx],\ 
		                                   SW_TST_TLE8242_DitherFreq[SW_TST_TLE8242_Idx]);
	ShrExp_Get_Solenoid(SW_TST_TLE8242_Idx,fb_ilin,stDiaRdy,stDiaDsbc);

}

#define TST_STOP_SEC_TST_CODE
#include"TST_MemMap.h"

/*----------------------------------------------------endoffile---------------------------------------------------*/
