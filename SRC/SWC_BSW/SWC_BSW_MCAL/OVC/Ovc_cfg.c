/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : OVC                                                                                             */
/*                                                                                                                    */
/* !Component       : OVC                                                                                             */
/* !Description     : OVC unit                                                                                        */
/*                                                                                                                    */
/* !Module          : OVC                                                                                             */
/* !Description     : API of OVC unit                                                                                 */
/*                                                                                                                    */
/* !File            : OVC_CFG.c                                                                                       */
/*                                                                                                                    */
/* !Target          : Aurix_TC27x                                                                                     */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcal.h"
#include "Ovc.h"
#include "DEVHAL_Cfg.h"


#define OVC_START_SEC_CONST_UNSPECIFIED
#include "OVC_MemMap.h"

const uint8 OVC_aku8GetMemId[16] =
{
	255,
	255,
	255,
	255,
	255,
   2, /* Redirection to Core 2 DSPR/PSPR memory */
   1, /* Redirection to Core 1 DSPR/PSPR memory */
   0, /* Redirection to Core 0 DSPR/PSPR memory */
   255,
   6, /* Redirection to LMU */
   7, /* Redirection to EMEM */
   255,
   6, /* Redirection to LMU */
   7, /* Redirection to EMEM */	
	255,
	255
};

const OVC_tstBlk OVC_akstCfg[OVC_u8NB_CFG][1] =
{
	/* No calibration */
   {
		{
			(uint32 *)0,
		   (uint32 *)0,
			0,
			FALSE,
			0,
			FALSE		
		}
	},
	/* Devaid in EMEM */
   {
		{
			(uint32 *)DEVHAL_u32CALIB_START_ADDRESS,
		   (uint32 *)DEVHAL_OVERLAY_RAM_START_ADDRESS,
			(DEVHAL_u32CALIB_END_ADDRESS - DEVHAL_u32CALIB_START_ADDRESS),
			TRUE,
			OVC_u8CORE_0,
			TRUE		
		}
	},
	/* Devaid in RAM */
	{
		{
			(uint32 *)DEVHAL_u32CALIB_START_ADDRESS,
         (uint32 *)DEVHAL_OVERLAY_INT_RAM_START_ADDRESS,
			(DEVHAL_u32CALIB_END_ADDRESS - DEVHAL_u32CALIB_START_ADDRESS),
			TRUE,
			OVC_u8CORE_0,
			TRUE			
		}
	}
};
#define OVC_STOP_SEC_CONST_UNSPECIFIED
#include "OVC_MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
