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
	
	if (idx < NUMBER_OF_TLE8242_CHANNEL)
	{

		if(idx == 0)
		{
			idx_temp = 4;
		}
		else if(idx == 1)
		{
			idx_temp = 3;
		}
		else if(idx == 2)
		{
			idx_temp = 2;
		}
		else if(idx == 3)
		{
			idx_temp = 1;
		}
		else if(idx == 4)
		{
			idx_temp = 0;
		}
		else if(idx == 5)
		{
			idx_temp = 6;
		}
		else if(idx == 6)
		{
			idx_temp = 7;
		}
		else if(idx == 7)
		{
			idx_temp = 5;
		}
		else
		{}
		

		if((BSW_u8TLE8242CHIndex_Temp != idx)||(BSW_u8TLE8242Mode_Temp != mode)||(BSW_f32TLE8242_Target_Temp != iout)||(BSW_f32TLE8242_DitherAmpl_Temp != iDth)||(BSW_f32TLE8242_DitherFreq_Temp != fDth))
		{
			BSW_bTle8242Flag = 1;
		}
		else
		{
			BSW_bTle8242Flag = 0;
		}

        iout_temp = iout/10; // resolution 0.1mA/bit
		iDth_temp = iDth/10;
		
		/*do trim function*/
		TLE8242Target[idx_temp] = Trim_CalculateGainAndOffset(idx_temp,iout_temp);
	
		TLE8242OpenLoopC[idx_temp] = mode;
		TLE8242DitherAmpl[idx_temp] = iDth_temp*2;
		TLE8242DitherFreq[idx_temp] = fDth;
		
		/*backup the data*/
		BSW_u8TLE8242CHIndex_Temp       = idx;
		BSW_u8TLE8242Mode_Temp          = mode;
		BSW_f32TLE8242_Target_Temp      = iout;
		BSW_f32TLE8242_DitherAmpl_Temp  = iDth;
		BSW_f32TLE8242_DitherFreq_Temp  = fDth;
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
    uint16 feedback_current_temp = 0;
	uint16 iln_temp = 0;
	uint16 avg_iln_temp = 0;
	uint8  idx_temp = 0;
	static uint16 feedback_iln_table[8][10] = {{0}};
	uint8 i;

	if ((idx >= NUMBER_OF_TLE8242_CHANNEL)|| (stDiaRdy == NULL_PTR) || (stDiaDsbc == NULL_PTR))
	{
		return;
	}
	else
	{
		if(idx == 0)
		{
			idx_temp = 4;
		}
		else if(idx == 1)
		{
			idx_temp = 3;
		}
		else if(idx == 2)
		{
			idx_temp = 2;
		}
		else if(idx == 3)
		{
			idx_temp = 1;
		}
		else if(idx == 4)
		{
			idx_temp = 0;
		}
		else if(idx == 5)
		{
			idx_temp = 6;
		}
		else if(idx == 6)
		{
			idx_temp = 7;
		}
		else if(idx == 7)
		{
			idx_temp = 5;
		}
		else
		{}

		//*iln = TLE8242AvgCurma[idx];
		feedback_current_temp = (uint16)(TLE8242AvgCurma[idx_temp]);
		iln_temp = Trim_Feedback_CalculateGainAndOffset(idx_temp,feedback_current_temp);

		for(i = 9 ;i>0;i--)
		{
			feedback_iln_table[idx_temp][i] = feedback_iln_table[idx_temp][i-1];
	}
		feedback_iln_table[idx_temp][0] = iln_temp;

		for(i = 0;i<10;i++)
		{
			avg_iln_temp +=	feedback_iln_table[idx_temp][i];
		}

		
		*iln = (avg_iln_temp/10)*10;   // resolution 0.1mA/bit
}

}


