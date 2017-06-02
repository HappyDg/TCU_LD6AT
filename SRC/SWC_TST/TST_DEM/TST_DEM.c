/**********************************************************************************************************************/
/* !Layer           : TST                                                                                             */
/* !Component       : TST_Dem                                                                                         */
/* !Description     : Test Code For PWM Component                                                                     */
/*                                                                                                                    */
/* !File            : TST_Dem.c                                                                                       */
/* !Description     : TST_Dem test APIs                                                                               */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/

#include "Std_Types.h"
#include "STD_LIMITS.h"
#include "TST_DEM.h"
#include "SWTST.h"
#include "BSW.h"
#include "IOHAL.h"
#include "Dem.h"
#include "FiM.h"
#include "Nvm.h"
#include "SWTST.h"
#include "SWTST_L.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

/**********************************************************************************************************************/
/* !Runnable    : TST_DEM_vidInit                                                                                     */
/* !Trigger     : Reset                                                                                               */
/* !Description : Initializes the TST_DEM data                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Liping.Liu                                                                                         */
/**********************************************************************************************************************/
void TST_DEM_vidInit(void)
{
   SWTST_u16DemCase         = 0;
   SWTST_u16NvmCase         = 0;
   SWTST_u16FiMPermision1   = 0;
   SWTST_u16FiMPermision2   = 0;
}

/**********************************************************************************************************************/
/* !Runnable    : TST_DEM_vidMainFunction                                                                             */
/* !Trigger     : 1000ms                                                                                               */
/* !Description :                                                                            */
/*                                                                                                                    */
/* !LastAuthor  : Liping.Liu                                                                                         */
/**********************************************************************************************************************/
void TST_DEM_vidMainFunction(void)
{
	if( SWTST_kbDemTstEnaC == TRUE)
	{
		switch (SWTST_u16DemCase)
	   {
		  case 1:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HVLowVoltage, DEM_EVENT_STATUS_FAILED);
			 break;
		  case 2:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HVLowVoltage, DEM_EVENT_STATUS_PASSED);
			 break;
		  case 3:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HVHighVoltage, DEM_EVENT_STATUS_FAILED);
			 break;
		  case 4:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HVHighVoltage, DEM_EVENT_STATUS_PASSED);
			 break;
		  case 5:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HiOVPPermanentFauSts, DEM_EVENT_STATUS_FAILED);
			 break;
		  case 6:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HiOVPPermanentFauSts, DEM_EVENT_STATUS_PASSED);
			 break;
		  case 7:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HiUVPPermanentFauSts, DEM_EVENT_STATUS_FAILED);
			 break;
		  case 8:
	            Dem_ReportErrorStatus(DemConf_DemEventParameter_APPL_E_DDVFD_HiUVPPermanentFauSts, DEM_EVENT_STATUS_PASSED);
			 break;
		  default:
			 /* Do nothing */
			 break;
	   }
	   
	   /* Save to memory */
		if (SWTST_u16NvmCase == 1)
		{
			SWTST_u16DemCase = 0;
			(void)NvM_SetRamBlockStatus(NvM_DEM, TRUE);
			NvM_WriteAll();
			SWTST_u16NvmCase = 0;
		}
		/* Read from memory */
		if (SWTST_u16NvmCase == 2)
		{
			SWTST_u16DemCase = 0;
			
			NvM_SetRamBlockStatus(NvM_DEM, FALSE);
			
			NvM_ReadAll();
			
			SWTST_u16NvmCase = 0;
		}
		
		/* Fim Permission */
	    FiM_GetFunctionPermission( FiMConf_FiMFID_FID_DDVFD_HVLowVoltage, (boolean* )(& SWTST_u16FiMPermision1) );
        FiM_GetFunctionPermission( FiMConf_FiMFID_FID_DDVFD_HVHighVoltage, (boolean* )(& SWTST_u16FiMPermision2) );		
		FiM_GetFunctionPermission( FiMConf_FiMFID_FID_DDVFD_HVDerating, (boolean* )(& SWTST_u16FiMPermision3) );
        FiM_GetFunctionPermission( FiMConf_FiMFID_FID_DDVFD_HiOVPPermanentFauSts, (boolean* )(& SWTST_u16FiMPermision4) );
		FiM_GetFunctionPermission( FiMConf_FiMFID_FID_DDVFD_HiUVPPermanentFauSts, (boolean* )(& SWTST_u16FiMPermision5) );

	}

}

#define TST_STOP_SEC_TST_CODE
#include"TST_MemMap.h"

/*----------------------------------------------------endoffile---------------------------------------------------*/
