#include "Std_Types.h"
#include "DIO_WrapAPI.h"
#include "Dio.h"
#include "TLE8242_wrapper.h"
#include "Trim_8242_App.h"
#include "Trim_8242.h"


#define TLE8242_START_SEC_CODE
#include "MemMap.h"


/*****************************************************************/
/*************feedback_trim_current*********************************/
EOL_DATA Feedback_ParaForGainAndOffset[8];
GainOfset Feedback_GainAndOffset[8];

void Trim_Feedback_InitGainAndOffset(void)
{
	uint8 index;
	
	for(index = 0;index < 8; index++)
	{
		Feedback_ParaForGainAndOffset[index].grd_grd = Flash_trimDataBuf[index][0];
		Feedback_ParaForGainAndOffset[index].grd_ofs = Flash_trimDataBuf[index][1];
		Feedback_ParaForGainAndOffset[index].ofs_grd = Flash_trimDataBuf[index][2];
		Feedback_ParaForGainAndOffset[index].ofs_ofs = Flash_trimDataBuf[index][3];
		Feedback_ParaForGainAndOffset[index].scale_factor = 0;
	}
	
}

uint16 Trim_Feedback_CalculateGainAndOffset(uint8 index,uint16 feedback_current)
{
	sint16 PCB_temprature = 0;
	sint32 feedback_trim_current = 0;
	sint32 feedback_current_temp = 0;
	uint16 feedback_return_current = 0;
	
	feedback_current_temp = (sint32)feedback_current;
	if(index >= 8)
	{
		 feedback_return_current = 0;

		 return feedback_return_current;
	}
	else
	{
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
			
			Feedback_GainAndOffset[index].gain = PCB_temprature*Feedback_ParaForGainAndOffset[index].grd_grd+Feedback_ParaForGainAndOffset[index].grd_ofs;
			Feedback_GainAndOffset[index].offset = PCB_temprature*Feedback_ParaForGainAndOffset[index].ofs_grd+Feedback_ParaForGainAndOffset[index].ofs_ofs;
			
            if(Feedback_GainAndOffset[index].gain == 0)
            {
				feedback_trim_current = ((((feedback_current_temp*1.024)*32768) - Feedback_GainAndOffset[index].offset)/32768);	

				if(feedback_trim_current < 0)
					feedback_trim_current = 0;				
			}
			else
			{
				feedback_trim_current = ((((feedback_current_temp*1.024)*32768) - Feedback_GainAndOffset[index].offset)/Feedback_GainAndOffset[index].gain);	

				if(feedback_trim_current < 0)
					feedback_trim_current = 0;			
			}

			feedback_return_current = (uint16)feedback_trim_current;

			return feedback_return_current;

		}			
	}
}

#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"


