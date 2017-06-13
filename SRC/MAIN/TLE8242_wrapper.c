/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           :                                                                                            */
/*                                                                                                                    */
/* !Component       :                                                                                             */
/* !Description     :     unit                                                                                    */
/*                                                                                                                    */
/* !Module          :                                                                                             */
/* !Description     :                                                                           */
/*                                                                                                                    */
/* !File            : TLE8242_wrapper.c                                                                                  */
/*                                                                                                                    */
/* !Target          :                                                                                      */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* 1 /                                                                                    */
/* 2 /                                                                                        */
/* 3 /                                                                                           */
/* 4 /                                                                                           */
/* 5 /                                                                                          */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* Archive::                        */
/* Revision::   0.1                                                                                                */
/* Author::   Liping                               Date::   Feb 22, 2017                                   */
/**********************************************************************************************************************/
#include "TLE8242_wrapper.h"
#include "BSW.h"
#include "Trim_8242.h"
#include "Trim_8242_App.h"
#include "TLE8242_cfg.h"
#include "TLE8242_def.h"
#include "TLE8242.h"

/**********************************************************************************************************************/
/* !FuncName    : ShrExp_Set_Solenoid                                                                                    */
/* !Description :                                                                                                     */
/* TLE8242 Wrapper function for customer                                                                          */
/* !LastAuthor  : Liping                                                                                          */
/**********************************************************************************************************************/
void ShrExp_Set_SolCarrierFreq(uint8 idx,uint16 fCarrier)
{
	uint16 fCarrier_temp = 0;
	uint8  idx_temp = 0;
	
	if (idx < TLE8242_u8MAX_CH_NR) // idx just for solenoid 
	{
		if(idx == Idx_B1_SOL)
		{
			idx_temp = Idx_OUT4_8242;
		}
		else if(idx == Idx_C1_SOL)
		{
			idx_temp = Idx_OUT3_8242;
		}
		else if(idx == Idx_C2_SOL)
		{
			idx_temp = Idx_OUT2_8242;
		}
		else if(idx == Idx_C3_SOL)
		{
			idx_temp = Idx_OUT1_8242;
		}
		else if(idx == Idx_C4_SOL)
		{
			idx_temp = Idx_OUT0_8242;
		}
		else if(idx == Idx_LP_SOL)
		{
			idx_temp = Idx_OUT6_8242;
		}
		else if(idx == Idx_TC_SOL)
		{
			idx_temp = Idx_OUT7_8242;
		}
		else if(idx == Idx_RES_SOL)
		{
			idx_temp = Idx_OUT5_8242;
		}
		else
		{}
		
		if(Idx_OUT3_8242 != idx_temp) // current solenoid mode
		{
			/*do set PWM frequency function*/
			TLE8242_au16PwmFrq[idx_temp] = fCarrier;
		
			/*backup the data*/
			BSW_f32TLE8242_PWMFrq_Temp = fCarrier;
		}

	}
	else
	{
		/* do nothing*/
	}

}


/**********************************************************************************************************************/
/* !FuncName    : ShrExp_Set_Solenoid                                                                                    */
/* !Description :                                                                                                     */
/* TLE8242 Wrapper function for customer                                                                          */
/* !LastAuthor  : Liping                                                                                          */
/**********************************************************************************************************************/
void ShrExp_Set_Solenoid(uint8 idx, uint8 mode, uint16 iout, uint16 iDth, uint16 fDth)
{
	uint16 iout_temp = 0;
	uint16 iDth_temp = 0;
	uint8  idx_temp = 0;
	
	if (idx < TLE8242_u8MAX_CH_NR)
	{
		if(idx == Idx_B1_SOL)
		{
			idx_temp = Idx_OUT4_8242;
		}
		else if(idx == Idx_C1_SOL)
		{
			idx_temp = Idx_OUT3_8242;
		}
		else if(idx == Idx_C2_SOL)
		{
			idx_temp = Idx_OUT2_8242;
		}
		else if(idx == Idx_C3_SOL)
		{
			idx_temp = Idx_OUT1_8242;
		}
		else if(idx == Idx_C4_SOL)
		{
			idx_temp = Idx_OUT0_8242;
		}
		else if(idx == Idx_LP_SOL)
		{
			idx_temp = Idx_OUT6_8242;
		}
		else if(idx == Idx_TC_SOL)
		{
			idx_temp = Idx_OUT7_8242;
		}
		else if(idx == Idx_RES_SOL)
		{
			idx_temp = Idx_OUT5_8242;
		}
		else
		{}


		if(0 == mode) //current solenoid mode
		{
	        iout_temp = iout/10; // resolution 0.1mA/bit
			iDth_temp = iDth/10;
			
			/*do trim function*/
			TLE8242_af32TarCnrtMa[idx_temp] = Trim_CalculateGainAndOffset(idx_temp,iout_temp);
		
			TLE8242_au8OpenLoop[idx_temp] = mode;
			TLE8242_af32DitherAmplMa[idx_temp] = iDth_temp*2;
			TLE8242_af32DitherFrq[idx_temp] = fDth;
			
			/*backup the data*/
			BSW_u8TLE8242CHIndex_Temp       = idx;
			BSW_u8TLE8242Mode_Temp          = mode;
			BSW_f32TLE8242_Target_Temp      = iout;
			BSW_f32TLE8242_DitherAmpl_Temp  = iDth;
			BSW_f32TLE8242_DitherFreq_Temp  = fDth;
		}
		else
		{
			/*do set PWM frequency function*/
			TLE8242_au8OpenLoop[idx_temp] = mode;
			TLE8242_au16PwmFrq[idx_temp] = fDth;
			TLE8242_af32DutyCycle[idx_temp] = (float32)iDth/100.0;
		
		}
	}
	else
	{
		/* do nothing*/
	}

}

/**********************************************************************************************************************/
/* !FuncName    : ShrExp_Get_Solenoid                                                                                    */
/* !Description :                                                                                                     */
/* TLE8242 Wrapper function for customer                                                                          */
/* !LastAuthor  : Liping                                                                                          */
/**********************************************************************************************************************/

void ShrExp_Get_Solenoid(uint8 idx, uint16 *iln, uint8 *stDiaRdy, uint8 *stDiaDsbc)
{
    static uint16 feedback_current_temp = 0;
	uint16 iln_temp = 0;
	uint8  idx_temp = 0;

	if ((idx >= TLE8242_u8MAX_CH_NR)|| (stDiaRdy == NULL_PTR) || (stDiaDsbc == NULL_PTR))
	{
		return;
	}
	else
	{
		if(idx == Idx_B1_SOL)
		{
			idx_temp = Idx_OUT4_8242;
		}
		else if(idx == Idx_C1_SOL)
		{
			idx_temp = Idx_OUT3_8242;
		}
		else if(idx == Idx_C2_SOL)
		{
			idx_temp = Idx_OUT2_8242;
		}
		else if(idx == Idx_C3_SOL)
		{
			idx_temp = Idx_OUT1_8242;
		}
		else if(idx == Idx_C4_SOL)
		{
			idx_temp = Idx_OUT0_8242;
		}
		else if(idx == Idx_LP_SOL)
		{
			idx_temp = Idx_OUT6_8242;
		}
		else if(idx == Idx_TC_SOL)
		{
			idx_temp = Idx_OUT7_8242;
		}
		else if(idx == Idx_RES_SOL)
		{
			idx_temp = Idx_OUT5_8242;
		}
		else
		{}

		if(Idx_OUT3_8242 != idx_temp)
		{
			//*iln = TLE8242AvgCurma[idx];
			feedback_current_temp = (uint16)(TLE8242_af32AvgCrntMa[idx_temp]);
			iln_temp = Trim_Feedback_CalculateGainAndOffset(idx_temp,feedback_current_temp);
			
			*iln = iln_temp*10;   // resolution 0.1mA/bit
		}
		else
		{
			*iln = (uint16)(TLE8242_af32PwmDutyFb[idx_temp] * 1000); // resolution 0.1%/bit	
		}

		*stDiaRdy = (uint8)((1 << TLE8242_SG_FAULT) + (1 << TLE8242_SB_FAULT) + (1 << TLE8242_OP_FAULT));

		*stDiaDsbc = (uint8)((TLE8242_su16FltSts[idx_temp][4] << TLE8242_SG_FAULT) + \
			                 (TLE8242_su16FltSts[idx_temp][5] << TLE8242_SB_FAULT) + \
			                 (TLE8242_su16FltSts[idx_temp][1] << TLE8242_OP_FAULT));
		 
	}
}


