#include "Std_Types.h"
#include "DIO_WrapAPI.h"
#include "Dio.h"
#include "TLE8242_wrapper.h"
#include "Trim_8242.h"


#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"														
EOL_DATA ParaForGainAndOffset[8];
GainOfset GainAndOffset[8];
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_CODE
#include "MemMap.h"
void Trim_InitGainAndOffset(void)
{
	uint8 index;
	
	for(index = 0;index < 8; index++)
	{
		ParaForGainAndOffset[index].grd_grd = Flash_trimDataBuf[index][0];
		ParaForGainAndOffset[index].grd_ofs = Flash_trimDataBuf[index][1];
		ParaForGainAndOffset[index].ofs_grd = Flash_trimDataBuf[index][2];
		ParaForGainAndOffset[index].ofs_ofs = Flash_trimDataBuf[index][3];
		ParaForGainAndOffset[index].scale_factor = 0;
	}
	
}

uint16 Trim_CalculateGainAndOffset(uint8 index,uint16 target_current)
{
	sint32 ADC_current = 0;
	sint16 PCB_temprature = 0;
	uint16 Trim_current;
	sint32 target_current_temp = 0;
	
	target_current_temp = target_current;
	if(index >= 8)
	{
		 Trim_current = 0;;
	}
	else
	{
		 if(target_current >= 2000)
		{
			 Trim_current = 2000;
		}
		else if(target_current == 0)
		{
			 Trim_current = 0;
		}
		else
		{
			//PCB_temprature = 25;
			Dio_Get_PCBTemp(&PCB_temprature);
			if(PCB_temprature < 0)
			{
			  PCB_temprature = 0-PCB_temprature;
			  
			  if(PCB_temprature > 45)
				{
				PCB_temprature = 45;
				}
			}
			else if(PCB_temprature > 105)
			{
				PCB_temprature = 105;
			}
			else
			{
			}
			
			GainAndOffset[index].gain = PCB_temprature*ParaForGainAndOffset[index].grd_grd+ParaForGainAndOffset[index].grd_ofs;
			GainAndOffset[index].offset = PCB_temprature*ParaForGainAndOffset[index].ofs_grd+ParaForGainAndOffset[index].ofs_ofs;
			
			ADC_current = (((sint32)((target_current_temp )* GainAndOffset[index].gain + GainAndOffset[index].offset))/32768);//2^15 = 32768
			
			if(ADC_current > 2048)
			{
				ADC_current = 2048;
			}
			
			Trim_current = (uint16)(ADC_current * CurrentPerLSB);
		}
			

	}

	return (Trim_current);
}
#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"