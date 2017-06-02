/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : EMEM                                                                                            */
/*                                                                                                                    */
/* !Component       : EMEM                                                                                            */
/* !Description     : EMEM unit                                                                                       */
/*                                                                                                                    */
/* !Module          : EMEM                                                                                            */
/* !Description     : API of EMEM unit                                                                                */
/*                                                                                                                    */
/* !File            : EMEM.c                                                                                          */
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
/* 1 / EMEM_vidUnlock                                                                                                 */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/
#include "Std_Types.h"
#include "Emem.h"

#define EMEM_START_SEC_CODE
#include "EMEM_MemMap.h"

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : EMEM_vidUnlock                                                                                      */
/*                                                                                                                    */
/* !Description : Unlock EMEM if available                                                                            */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : Reset                                                                                                  */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void EMEM_vidUnlock(uint32 * pu32Start, uint32 u32Size)
{
   volatile Ifx_EMEM_SBRCTR     *udtLocalSbrctrReg       = &EMEM_SBRCTR;
   volatile Ifx_EMEM_TILECONFIG *udtLocalTileReg         = &EMEM_TILECONFIG;
   uint32 u32LocCurrStt;
	uint32 u32LocMask;
   uint32 u32LocVar;
	sint32 s32LocIdx;
	uint32 u32Start;
	uint16 u16LocPwd;


	COMPILER_UNUSED_PARAMETER(u32LocCurrStt);
   if ((SCU_CHIPID.B.EEA) == 0x01u)
	{
		u16LocPwd = IfxScuWdt_getSafetyWatchdogPassword();
		IfxScuWdt_clearSafetyEndinit(u16LocPwd);
		/* Clock Enable */
		MODULE_EMEM.CLC.U = 0u;
		__dsync();
		IfxScuWdt_setSafetyEndinit(u16LocPwd);
		
		u32Start = EMEM_u32GET_TIMEOUT_START();
		while((MODULE_EMEM.CLC.B.DISS != 0) && (EMEM_bTIMEOUT_ELAPSED(u32Start, 1) == FALSE));

		/* Unlock Sequence */
		udtLocalSbrctrReg->U = 0x2u;
		udtLocalSbrctrReg->U = 0x6u;
		udtLocalSbrctrReg->U = 0xEu;

		/* Wait a Cycle */
		u32LocCurrStt = (uint32)(udtLocalSbrctrReg->U);

		/* Assign part of EMEM to Calibration Memory */
		u32LocMask = 0;
		for (s32LocIdx = 0; s32LocIdx < (sint32)(((u32Size + (EMEM_u32BLOCK_SIZE - 1)) / EMEM_u32BLOCK_SIZE)); s32LocIdx++)
		{
				u32LocMask <<= 2;
				u32LocMask |= 3u;
		}
		u32LocVar = ((uint32)pu32Start & 0x00FFFFFFu);
		u32LocVar = u32LocVar / EMEM_u32BLOCK_SIZE;
		u32LocVar = MATHSRV_udtMIN(u32LocVar, EMEM_u32NB_BLOCK - 1);
		u32LocMask = (u32LocMask << (u32LocVar << 1));
		u32LocMask = (0x55555555u & (~u32LocMask));
		udtLocalTileReg->U = u32LocMask;
		__dsync();
	}
}

#define EMEM_STOP_SEC_CODE
#include "EMEM_MemMap.h"
/*---------------------------------------------------- end of file ---------------------------------------------------*/
