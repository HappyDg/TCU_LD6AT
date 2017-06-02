/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : EVP                                                                                             */
/*                                                                                                                    */
/* !Component       : EVP                                                                                             */
/* !Description     : VADC unit                                                                                       */
/*                                                                                                                    */
/* !Module          : EVP                                                                                             */
/* !Description     : API of EVP unit                                                                                 */
/*                                                                                                                    */
/* !File            : EVP.c                                                                                           */
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
/* 1 / EVP_vidInit                                                                                                    */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/
#include "Std_Types.h"
#include "Std_Limits.h"
#include "micro.h"
#include "Gtm.h"
#include "Dio.h"
#include "MATHSRV.h"
#include "EVP.h"
#include "EVP_L.h"
#include "Evp_api.h"
#include "EVP_Cfg.h"


#define EVP_START_SEC_CODE
#include "EVP_MemMap.h"

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : EVP_vidInit                                                                                         */
/*                                                                                                                    */
/* !Description : Initializes proportional solenoids                                                                  */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : Reset                                                                                                  */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void EVP_vidInit(void)
{

   Ifx_GTM_TOM_CH_TYPE  * pstLocPtr;
   const EVP_tstCfgChan * pstLocCfgPtr;
 


   EVP_akstGrp[EVP_u8GRP_0_IDX].pstTgc->GLB_CTRL.U = EVP_u32GRP_0_SW_RST;
   
//   pstLocPtr    = (&((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[EVP_u8TRIG_0_TOM_IDX].CH[EVP_u8ADC_TRIG_0_CHAN]));
   pstLocPtr    = EVP_akstGrp[EVP_u8GRP_0_IDX].pstCh;
   EVP_akstGrp[EVP_u8GRP_0_IDX].pstTgc->GLB_CTRL.U = EVP_akstGrp[EVP_u8GRP_0_IDX].u32UpdDisa;
   
   pstLocCfgPtr = &(EVP_akstGrp[EVP_u8GRP_0_IDX].astCfgChan[0]);
   pstLocPtr->SR0.U  = pstLocCfgPtr->SR0.U;
   pstLocPtr->SR1.U  = pstLocCfgPtr->SR1.U;
   pstLocPtr->CN0.U  = pstLocCfgPtr->CN0.U;
   pstLocPtr->CTRL.U = pstLocCfgPtr->CTRL.U;
   
   pstLocPtr++;
   //pstLocPtr    = (&((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[EVP_u8TRIG_1_TOM_IDX].CH[EVP_u8ADC_TRIG_1_CHAN]));
   //EVP_akstGrp[EVP_u8TRIG_0_IDX].pstTgc->GLB_CTRL.U = EVP_akstGrp[EVP_u8TRIG_0_IDX].u32UpdDisa;
   
   pstLocCfgPtr++;// = &(EVP_akstGrp[EVP_u8GRP_0_IDX].astCfgChan[EVP_u8NB_CHAN_BY_GROUPID_1]);
   pstLocPtr->SR0.U  = pstLocCfgPtr->SR0.U;
   pstLocPtr->SR1.U  = pstLocCfgPtr->SR1.U;
   pstLocPtr->CN0.U  = pstLocCfgPtr->CN0.U;
   pstLocPtr->CTRL.U = pstLocCfgPtr->CTRL.U;

  
   EVP_akstGrp[EVP_u8GRP_0_IDX].pstTgc->GLB_CTRL.U = EVP_akstGrp[EVP_u8GRP_0_IDX].u32UpdEna;

   EVP_akstGrp[EVP_u8GRP_0_IDX].pstTgc->OUTEN_CTRL.U = EVP_u32GRP_0_OUTEN_CTRL;


   EVP_akstGrp[EVP_u8GRP_0_IDX].pstTgc->OUTEN_STAT.U = EVP_u32GRP_0_OUTEN_STAT;


   EVP_akstGrp[EVP_u8GRP_0_IDX].pstTgc->ENDIS_CTRL.U = EVP_u32GRP_0_ENDIS_CTRL;


   EVP_akstGrp[EVP_u8GRP_0_IDX].pstTgc->ENDIS_STAT.U = EVP_u32GRP_0_ENDIS_STAT_CHAN_ENA;

}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : EVP_bSetPwm                                                                                         */
/*                                                                                                                    */
/* !Description : Set period and duty cycles                                                                          */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : ISR                                                                                                    */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/

boolean EVP_bSetPwm(uint8 u8GrpIdx, uint32 u32Prd, const uint16 * pu16Duty)
{
   Ifx_GTM_TOM_CH_TYPE * pstLocPtr;
   const EVP_tstGrp    * pkstGrp;
   boolean               bStatus;
   uint32                u32Ton;


   bStatus = TRUE;
   if (u8GrpIdx < EVP_u8NB_GROUP)
   {      
      pkstGrp = &EVP_akstGrp[u8GrpIdx];
      pkstGrp->pstTgc->GLB_CTRL.U = pkstGrp->u32UpdDisa;

      pstLocPtr             = pkstGrp->pstCh;
      //u32Prd = MATHSRV_udtCLAMP(u32Prd, EVP_u16PRD_MIN, EVP_u16PRD_MAX);
      pstLocPtr->SR0.U      = u32Prd;
	  u32Ton = (((u32Prd * (uint32)(*pu16Duty)) + (1u << 13)) >> 14);
	  u32Ton = MATHSRV_udtMIN(u32Ton, u32Prd);
	  pstLocPtr->SR1.U      = u32Ton;
	 pstLocPtr++;
	 pstLocPtr->SR1.U      = u32Ton;
	 u32Ton = u32Ton + EVP_u16DELAY_5MICROS;
	 u32Ton = MATHSRV_udtMIN(u32Ton, u32Prd);
	 pstLocPtr->SR0.U       = u32Ton;
      
	  pkstGrp->pstTgc->GLB_CTRL.U = pkstGrp->u32UpdEna;
   }
   else
   {
      bStatus = FALSE;
   }
   return(bStatus);
}

#define EVP_STOP_SEC_CODE
#include "EVP_MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
