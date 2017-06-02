/**************************************************************************************************/
/*                                                                                                                    */
/* !Layer           :     Wrapper layer for APP                                                                                       */
/*                                                                                                                    */
/* !Component       :                                                                                             */
/* !Description     :     unit                                                                                    */
/*                                                                                                                    */
/* !Module          :                                                                                             */
/* !Description     :                                                                           */
/*                                                                                                                    */
/* !File            : DIO_WrapAPI.c                                                                                  */
/*                                                                                                                    */
/* !Target          :                                                                                      */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2017 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/


#include "Std_Types.h"
#include "Dio.h"
#include "IOHAL.h"
#include "Icu_17_GtmCcu6.h"
#include "DIO_WrapAPI.h"



extern uint32 RTMCLD_u32Load4SR;
extern uint32 RTMCLD_u32MaxLoad4SR;


uint8 ShrExp_SolenoidFeed_s[2] = {0xFF, 0xFF};
uint8 ShrExp_Pos_stPos;
uint8 ShrExp_Pos_stQual;
uint8 Gear_Speed[3];


void Dio_WrapAPI_Init(void)
{
	ShrExp_SolenoidFeed_s[0] = 0xFF;
	ShrExp_SolenoidFeed_s[1] = 0xFF;
	Gear_Speed[0] = 0;
	Gear_Speed[1] = 0;
	Gear_Speed[2] = 0;
}

/****************************************************

  DIO input wrapper for APP

***************************************************/
void ShrExp_Get_Switch(uint8 idx, uint8 *b)
{
	uint8 Temp_PinValue = 0xFF;
	
	if ((idx > 10)||(b == NULL_PTR))
	{
		return;
	}
	else
	{
	      switch(idx)
		{
			case 0:
				*b = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_MANUAL_MODE);
				break;
				
			case 1:
				*b = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_MANUAL_UP);
				break;
				
			case 2:
				*b = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_MANUAL_DOWN);
				break;
				
			case 3:
				*b = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_FOOT_BRAKE);
				break;
				
			case 4:
				Temp_PinValue = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_SNOW_MODE);
				if(Temp_PinValue == 1)
				{
					*b = 0;
				}
				else
				{
					*b = 1;
				}
				break;
				
			case 5:
				Temp_PinValue = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_HAND_BRAKE);
				if(Temp_PinValue == 1)
				{
					*b = 0;
				}
				else
				{
					*b = 1;
				}
				break;
				
			case 6:
				Temp_PinValue = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_SPORT_MODE);
				if(Temp_PinValue == 1)
				{
					*b = 0;
				}
				else
				{
					*b = 1;
				}
				 break;
				 
			case 7:
				Temp_PinValue = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_1);
				if(Temp_PinValue == 1)
				{
					*b = 0;
				}
				else
				{
					*b = 1;
				}
				break;
				
			case 8:
				Temp_PinValue = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_2);
				if(Temp_PinValue == 1)
				{
					*b = 0;
				}
				else
				{
					*b = 1;
				}
				break;
				
			case 9:
				Temp_PinValue = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_3);
				if(Temp_PinValue == 1)
				{
					*b = 0;
				}
				else
				{
					*b = 1;
				}
				break;
				
			case 10:
				Temp_PinValue = (uint8)Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_4);
				if(Temp_PinValue == 1)
				{
					*b = 0;
				}
				else
				{
					*b = 1;
				}
				break;

			default:
			return;
		}
	}
}


/****************************************************

  PWM input wrapper for APP

***************************************************/ 

void ShrExp_Get_Speed( uint8 idx, uint16 *n, uint8 *sDir, uint8 *bSply, uint8 *stDiaRdy, uint8 *stDiaDsbc)
{

	uint32 PWM_Freq_Speed;
	uint32 PWM_Freq_Speed_Org;
	
	uint32 PWM_Duty_Speed;

	uint8 ret = 0;
	uint32  u32LocalDutyCycle_Time = 0;

	//uint8 Gear_Count[3];
	 
	uint32 PWM_Time = 0;
	uint8 PWM_Channel = 0xFF;
	float TempDuty;

	
	    if((idx > 2) || (n == NULL_PTR) || (sDir == NULL_PTR) || (bSply == NULL_PTR) ||(stDiaRdy == NULL_PTR) ||(stDiaDsbc == NULL_PTR))
	    	{
			*bSply = 0;
			return;
	    	}
		else
		{

		}
		
		switch(idx)
		{
			case 0:
				if(Gear_Speed[0] == 0)
				{
					Gear_Speed[0] = 30;
				} 
				 PWM_Freq_Speed_Org = IOHWABS_udtREAD_CHANNEL(M_G4_SPD_SNS_PWM_FRQ);
				 PWM_Duty_Speed = IOHWABS_udtREAD_CHANNEL(M_G4_SPD_SNS_PWM_DUTYCYC);
				 PWM_Freq_Speed =(uint32)(PWM_Freq_Speed_Org << 2);
				 *n = (uint16)((uint32)(PWM_Freq_Speed *60)/Gear_Speed[0]); 
				 ret = 1;
				 break;
			case 1:
				if(Gear_Speed[1] == 0)
				{
					Gear_Speed[1] = 40;
				} 
				PWM_Freq_Speed_Org = IOHWABS_udtREAD_CHANNEL(M_C4_SPD_SNS_PWM_FRQ);
	     			PWM_Duty_Speed = IOHWABS_udtREAD_CHANNEL(M_C4_SPD_SNS_PWM_DUTYCYC);
				PWM_Freq_Speed =(uint32)(PWM_Freq_Speed_Org << 2);
				*n = (uint16)((uint32)(PWM_Freq_Speed *60)/Gear_Speed[1]); 
				ret = 1;
				break;
			case 2:
				if(Gear_Speed[2] == 0)
				{
					Gear_Speed[2] = 89;
				} 
				PWM_Freq_Speed_Org = IOHWABS_udtREAD_CHANNEL(M_TOSS_PWM_FRQ);
				PWM_Duty_Speed = IOHWABS_udtREAD_CHANNEL(M_TOSS_PWM_DUTYCYC);
				PWM_Freq_Speed =(uint32)(PWM_Freq_Speed_Org << 2);
				*n = (uint16)((uint32)(PWM_Freq_Speed *60)/Gear_Speed[2]); 
				 ret = 1;
				break;
				
			default:
			break;
		}	
		
	   if(ret == 1)
	   {
		    TempDuty = (float32)((float32)100-(float32)((float32) PWM_Duty_Speed*100/16384));
		    u32LocalDutyCycle_Time = (float32)(10000*TempDuty)/PWM_Freq_Speed_Org;
			
		    PWM_Time = u32LocalDutyCycle_Time;

		   if ((PWM_Time >= 50) && (PWM_Time <= 70))
		   {
		   	*sDir = 1;
		   }
		   else if((PWM_Time >= 102) && (PWM_Time <= 138))
	   	   {
			*sDir = 2;
	   	   }
		   else
		   {
			*sDir = 0;
		   }
		   *bSply = 1;
	   }
	   	
}



void Shrexp_set_Speed ( uint8 nPlsPerRe[])
{
	Gear_Speed[0] = *nPlsPerRe;
	Gear_Speed[1] = *(nPlsPerRe + 1);
	Gear_Speed[2] = *(nPlsPerRe + 2);
}

			
void ShrExp_Get_Position(uint8 idx, uint16 *rDuty, uint8 *bSply, uint8 *stDiaRdy, uint8 *stDiaDsbc)
{
      uint32 PWM_Freq;
      uint32 PWM_Duty;
	float TempDuty;
	  
	if ((idx > 1) || (rDuty == NULL_PTR) || (bSply == NULL_PTR) || (stDiaRdy == NULL_PTR) || (stDiaDsbc == NULL_PTR))
	{
		return;
	}
	else
	{
		
	}

	if(idx == 0)
	{
		PWM_Freq =  IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_PWM_FRQ);
		PWM_Duty = IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_PWM_DUTYCYC);
		if((PWM_Freq >= 234) && (PWM_Freq <=  286))
		{
		   TempDuty = (float32)((float32)1000-(float32)((float32) PWM_Duty*1000/16384));
		   *rDuty = (uint16)TempDuty;
			*bSply = 1;
		}
	}
	else
	{
		PWM_Freq =  IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_CHECK_PWM_FRQ);
		PWM_Duty = IOHWABS_udtREAD_CHANNEL(M_GEAR_POS_CHECK_PWM_DUTYCYC);
		if((PWM_Freq >= 234) && (PWM_Freq <= 286))
		{
		 	TempDuty = (float32)((float32)1000-(float32)((float32) PWM_Duty*1000/16384));
			*rDuty = (uint16)TempDuty;
			*bSply = 1;
		}
	}
	return;

}


void ShrExp_Set_Position(uint8 stPos, uint8 stQual)
{
	//set the gobal variable dangwei xinxi
	if((stPos > 11) || (stPos == 0) || (stQual > 2))
	{
		return;
	}
	else
	{

	}

	ShrExp_Pos_stPos = stPos;
	ShrExp_Pos_stQual = stQual;
}


/***********************************************

  ADC wrapper for APP

************************************************/
void ShrExp_Get_ADValue(uint8 idx, uint16 *p, uint8 *bSply)
{
	uint16 Temp_VADC_value;
	uint32 Temp_Voltage;
	float32 Temp;
	
	if ((idx > 2) || (p == NULL_PTR) || (bSply == NULL_PTR))
	{
		return;
	}
	else
	{

	}
	
	switch(idx)
	{
		case 0:
			 Temp_VADC_value = IOHAL_u16Read_AN_RESERVED_1(); 
			 Temp = (float32)((5000*Temp_VADC_value)/4095);
			 //Temp_Voltage = (uint32) (uint32)((5000*Temp_VADC_value)/4095);   // 5V*1000*sample value/4095
			 *p = (uint16)Temp;
			break;

		case 1:
			Temp_VADC_value = IOHAL_u16Read_AN_RESERVED_2();
			Temp = (float32)((5000*Temp_VADC_value)/4095);
			//Temp_Voltage = 5000*Temp_VADC_value/4095;   // 5V*1000*sample value/4095
			 *p = (uint16)Temp;
			break;

		case 2:
			 Temp_VADC_value = IOHAL_u16Read_AN_RESERVED_TEMP_1();
			 Temp = (float32)((5000*Temp_VADC_value)/4095);
			 //Temp_Voltage = 5000*Temp_VADC_value/4095;   // 5V*1000*sample value/4095
			 *p = (uint16)Temp;
			break;

		default:
			break;
	}
	*bSply = 1;
}

void ShrExp_Get_ResistanceValue(uint32 *p, uint8 *bSply)
{
	uint32 Temp_VADC_value;
	uint32 Temp_Voltage;
	
	if((p == NULL_PTR) || (bSply == NULL_PTR))
	{
		return;
	}
	else
	{

	}

	//IOHAL_u16Read_AN_PRI_OIL_TEMP();
	Temp_VADC_value = (uint32)IOHAL_u16Read_AN_PRI_OIL_TEMP();
	//Temp_Voltage=(((5000*Temp_VADC_value)/4095)*(1000+261))/261;
	Temp_Voltage = (uint32)(Temp_VADC_value*2610)/(4095-Temp_VADC_value);
	
	*p = Temp_Voltage;
	*bSply = 1;
	return;
}


void ShrExp_Get_Battery(uint16 *u)
{
	uint32 Temp_VADC_value;
	uint32 Temp_Voltage;
	
	if (u == NULL_PTR)
	{
		return;
	}
	else
	{

	}
	
	Temp_VADC_value = (uint32)IOHAL_u16Read_AN_T30_BATT();
	Temp_Voltage=(((5000*Temp_VADC_value)/4095)*(1000+261))/261;
	
	*u = (uint16)Temp_Voltage;
	return;
}


void ShrExp_Get_Ignition(uint16 *u, uint8 *b)
{
	//IOHAL_u16Read_AN_T15_IGN();
	uint32 Temp_VADC_value;
	uint32 Temp_Voltage;
	
	if ((u == NULL_PTR) || (b == NULL_PTR))
	{
		return;
	}
	else
	{

	}
	
	Temp_VADC_value = (uint32)IOHAL_u16Read_AN_T15_IGN();
	Temp_Voltage=(((5000*Temp_VADC_value)/4095)*(3160+825))/825;
	
	*u = (uint16)Temp_Voltage;

	if(Temp_Voltage >= 5500)
	{
		*b = 1;
	}
	else
	{
		*b = 0;
	}
	return;
}



//uint16 Temp_PressureAD_orignal;
void ShrExp_Get_PressureAD(uint16 *p, uint8 *bSply)
{
	uint32 Temp_VADC_value;
	uint32 Temp_Voltage;
	float32 Temp;
	
	//IOHAL_u16Read_AN_PRI_OIL_PRES();
	if((p == NULL_PTR) || (bSply == NULL_PTR))
	{
		return;
	}
	else
	{

	}
#if 0
	Temp_VADC_value = (uint32)IOHAL_u16Read_AN_PRI_OIL_PRES();
	Temp = (float32)((5000*Temp_VADC_value)/4095);
#endif

#if 1
	Temp_VADC_value = (uint32)IOHAL_u16Read_AN_PRI_OIL_PRES();
       Temp_Voltage = (uint32)IOHAL_u16Read_AN_P5V_INTERNAL();
	//Temp = (float32)((5000*Temp_VADC_value)/4095);
	Temp = (float32)((2500*Temp_VADC_value)/Temp_Voltage);
	//Temp_PressureAD_orignal = (float32)((5000*Temp_VADC_value)/4095);
#endif
	*p = (uint16)Temp;
	*bSply = 1;
}

/****************************************************

  DIO output wrapper for APP

***************************************************/
void ShrExp_Set_SolenoidFeed(uint8 idx, uint8 b)
{
		//M_SOL_HS_CMD_1;
		//M_SOL_HS_CMD_2;
	if((idx > 1) || (b > 1))
	{
		return;
	}
	else
	{

	}

	if(idx == 0) 		//M_SOL_HS_CMD_2
	{
		Dio_WriteChannel(DioConf_DioChannel_M_SOL_HS_CMD_2, 	b); 
		if(b == 0)
		{
			ShrExp_SolenoidFeed_s[0] = 4;
		}
		else
		{
			ShrExp_SolenoidFeed_s[0] = 5;
		}
	}
	else if(idx == 1)   //M_SOL_HS_CMD_1
	{
		Dio_WriteChannel(DioConf_DioChannel_M_SOL_HS_CMD_1, 	b); 
		if(b == 0)
		{
			ShrExp_SolenoidFeed_s[1] = 4;
		}
		else
		{
			ShrExp_SolenoidFeed_s[1] = 5;
		}
		
	}
}

void ShrExp_Get_SolenoidFeed( uint8 idx, uint8 *s, uint16 *u, uint8 *stDiaRdy, uint8 *stDiaDsbc)
{
	if((idx > 1) || (s == NULL_PTR) || (stDiaRdy == NULL_PTR) || (stDiaDsbc == NULL_PTR))
	{
		return;
	}
	else
	{

	}

	if(idx == 0)
	{
		*s = ShrExp_SolenoidFeed_s[0];
	}
	else
	{
		*s = ShrExp_SolenoidFeed_s[1];
	}
	
}

void ShrExp_Set_StartEnable(uint8 b)
{
	//M_STARTER_REL_CMD;
	if(b > 1)
	{
		return;
	}
	else
	{

	}

	Dio_WriteChannel(DioConf_DioChannel_M_STARTER_REL_CMD, b);
}

//just implement the API
void ShrExp_Get_StartEnable( uint8 * stDiaRdy, uint8 *stDiaDsbc)
{

}


void ShrExp_Set_Relay(uint8 b)
{
	//M_REV_LAMP_REL_CMD;
	if(b > 1)
	{
		return;
	}
	else
	{

	}

	Dio_WriteChannel(DioConf_DioChannel_M_REV_LAMP_REL_CMD, b);
}

//just implement the API
void ShrExp_Get_Relay(uint8 * stDiaRdy, uint8 *stDiaDsbc)
{

}

void ShrExp_Set_OnOffSolenoid(uint8 idx, uint8 b)
{
	//M_KEY_LOCK_CMD;
	//M_SHIFT_LOCK_CMD
	if((idx > 1) || (b > 1))
	{
		return;
	}
	else
	{

	}

	if(idx == 0)
	{
		Dio_WriteChannel(DioConf_DioChannel_M_KEY_LOCK_CMD, b);
	}
	else if(idx == 1)
	{
		Dio_WriteChannel(DioConf_DioChannel_M_SHIFT_LOCK_CMD, b);
	}
	
}

void ShrExp_Get_OnOffSolenoid( uint8 idx, uint8 * stDiaRdy, uint8 *stDiaDsbc)
{

}

//uint16 Temp_CpuLoad;
void Shrexp_get_CpuLd( uint16 *rCpuLd, uint16 *rCpuLdMax )
{
	 uint32 loadCup, MaxLoadCup;

	loadCup = RTMCLD_u32Load4SR;
	MaxLoadCup = RTMCLD_u32MaxLoad4SR;
	
	*rCpuLd = (uint16)loadCup;
	*rCpuLdMax = (uint16)MaxLoadCup;
}


uint16  An_u8PCBTmpVoltage[191] = 
{
	4961,	4959,	4957,	4955,	4952,	4949,	4947,	4944,	4941,	4938,	4934,
	4931,	4927,	4923,	4919,	4915,	4911,	4907,	4902,	4897,	4892,	4887,
	4881,	4876,	4870,	4864,	4857,	4850,	4844,	4836,	4829,	4821,	4813,
	4805,	4796,	4788,	4778,	4769,	4759,	4749,	4738,	4728,	4716,	4705,
	4693,	4681,	4668,	4655,	4641,	4628,	4613,	4599,	4584,	4568,	4552,
	4536,	4519,	4502,	4484,	4466,	4447,	4428,	4409,	4389,	4368,	4347,
	4326,	4304,	4282,	4259,	4235,	4212,	4187,	4163,	4137,	4112,	4086,
	4059,	4032,	4005,	3977,	3948,	3920,	3890,	3861,	3831,	3800,	3769,
	3738,	3707,	3675,	3642,	3610,	3577,	3543,	3510,	3476,	3442,	3408,
	3373,	3338,	3304,	3269,	3234,	3199,	3164,	3129,	3094,	3058,	3023,
	2987,	2952,	2916,	2881,	2845,	2809,	2774,	2738,	2703,	2668,	2632,
	2598,	2563,	2528,	2493,	2459,	2425,	2391,	2357,	2323,	2290,	2257,
	2223,	2191,	2158,	2125,	2093,	2062,	2030,	1999,	1968,	1937,	1907,
	1877,	1848,	1819,	1790,	1761,	1733,	1706,	1678,	1651,	1624,	1598,
	1571,	1546,	1520,	1495,	1470,	1446,	1422,	1398,	1375,	1352,	1329,
	1307,	1285,	1263,	1242,	1221,	1200,	1180,	1160,	1140,	1121,	1102,
	1083,	1065,	1047,	1029,	1012,	994,	       977,	961,	        945,	  929,	913,
	897,	       882,	867,	       852
};


void Dio_Get_PCBTemp( sint16 *Temp)
{
	uint32 ADC_u32PCBTempValue;
	uint32 ADC_u32Value_temp;
	uint16 ADC_u16PCBTempVoltage;	
	uint16 ADC_u8LowIndex;
	uint16 ADC_u8HighIndex;
	uint16 ADC_u8indexValue = 0xFF;

	ADC_u32PCBTempValue = IOHAL_u16Read_AN_TMP_PCB();
	ADC_u16PCBTempVoltage = (uint16)((5000*ADC_u32PCBTempValue)/4095);

	
	if(ADC_u16PCBTempVoltage > 3543)
	{
		ADC_u8HighIndex = 95;
		ADC_u8LowIndex = 94;
		ADC_u8indexValue = 0xFF;
		
		while(ADC_u8indexValue == 0xFF)
		{
			if ((ADC_u16PCBTempVoltage <= An_u8PCBTmpVoltage[ADC_u8LowIndex]) && (ADC_u16PCBTempVoltage >= An_u8PCBTmpVoltage[ADC_u8HighIndex]))
			{
				ADC_u32Value_temp = An_u8PCBTmpVoltage[ADC_u8HighIndex] + An_u8PCBTmpVoltage[ADC_u8LowIndex];
				ADC_u16PCBTempVoltage = (ADC_u16PCBTempVoltage <<1);
				if(ADC_u16PCBTempVoltage <= ADC_u32Value_temp)
				{
					ADC_u8indexValue = ADC_u8LowIndex;
				}
				else
				{
					ADC_u8indexValue = ADC_u8HighIndex;
				}
			}
			else if(ADC_u8LowIndex != 0)
			{
				
				ADC_u8HighIndex = (ADC_u8HighIndex - 1);
				ADC_u8LowIndex = (ADC_u8LowIndex - 1);
			}
			else
			{
				ADC_u8indexValue = 0;
			}
		}
	}
	else
	{
		ADC_u8HighIndex = 96;
		ADC_u8LowIndex = 95;
		ADC_u8indexValue = 0xFF;
		
		while(ADC_u8indexValue == 0xFF)
		{
			if ((ADC_u16PCBTempVoltage <= An_u8PCBTmpVoltage[ADC_u8LowIndex]) && (ADC_u16PCBTempVoltage >= An_u8PCBTmpVoltage[ADC_u8HighIndex]))
			{
				ADC_u32Value_temp = An_u8PCBTmpVoltage[ADC_u8HighIndex] + An_u8PCBTmpVoltage[ADC_u8LowIndex];
				ADC_u16PCBTempVoltage = (ADC_u16PCBTempVoltage << 1);
				if(ADC_u16PCBTempVoltage <= ADC_u32Value_temp)
				{
					ADC_u8indexValue = ADC_u8HighIndex;
				}
				else
				{
					ADC_u8indexValue = ADC_u8LowIndex;
				}
			}
			else if(ADC_u8LowIndex != 190)
			{
				
				ADC_u8LowIndex = ADC_u8HighIndex;
				ADC_u8HighIndex = ADC_u8HighIndex + 1;
			}
			else
			{
				ADC_u8indexValue = 190;
			}
		}
	}
	
	
	*Temp = (sint16)ADC_u8indexValue + (-40);

}

