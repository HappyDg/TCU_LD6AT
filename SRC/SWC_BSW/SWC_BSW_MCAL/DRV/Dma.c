/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : DMA                                                                                             */
/*                                                                                                                    */
/* !Component       : DMA                                                                                             */
/* !Description     : DMA unit                                                                                        */
/*                                                                                                                    */
/* !Module          : DMA_API                                                                                         */
/* !Description     : API of DMA unit                                                                                 */
/*                                                                                                                    */
/* !File            : DMA.h                                                                                           */
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
#include "Std_Limits.h"
#include "micro.h"
#include "Os_api.h"

#define DMA_u32TIMEOUT_DEINIT_MICROS 10
#define DMA_u32SYSTEM_CLOCK_MHZ      100

#define DMA_u32GET_TIMEOUT_START() ((uint32)MODULE_STM0.TIM0.U)

#define DMA_bTIMEOUT_ELAPSED(u32Start, u32Dur)  \
   ( (((uint32)((uint32)MODULE_STM0.TIM0.U  - (u32Start))) < ((uint32)(DMA_u32SYSTEM_CLOCK_MHZ * (u32Dur)))) \
   ? FALSE \
   : TRUE)

/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/
#define DRV_START_SEC_CODE
#include "DRV_MemMap.h"
/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/
/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description : Resets all DMA channels                                                                             */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
void DMA_vidStartDeInit(void)
{
   uint32 u32LocIdx;


	for (u32LocIdx = 0; u32LocIdx < sizeof(MODULE_DMA.TSR) / sizeof(Ifx_DMA_TSR); u32LocIdx++)
	{
		MODULE_DMA.TSR[u32LocIdx].B.DCH = 1;
		__dsync();
		MODULE_DMA.TSR[u32LocIdx].B.RST = 1;
	}	
}

/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description : Waits for the end of the deinit request                                                             */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
boolean DMA_vidChckDeInit(void)
{
   uint32  u32LocIdx;
	boolean bDone;
	uint32  u32TimeStamp;


   u32TimeStamp = DMA_u32GET_TIMEOUT_START();
	do
	{
		bDone = TRUE;
		for (u32LocIdx = 0; u32LocIdx < sizeof(MODULE_DMA.TSR) / sizeof(Ifx_DMA_TSR); u32LocIdx++)
		{
			if (MODULE_DMA.TSR[u32LocIdx].B.RST != 0)
			{
				bDone = FALSE;
			}
		}
	} while ((bDone == FALSE) && (DMA_bTIMEOUT_ELAPSED(u32TimeStamp, DMA_u32TIMEOUT_DEINIT_MICROS) == FALSE));
	return(bDone);
}
#define DRV_STOP_SEC_CODE
#include "DRV_MemMap.h"
/*---------------------------------------------------- end of file ---------------------------------------------------*/
