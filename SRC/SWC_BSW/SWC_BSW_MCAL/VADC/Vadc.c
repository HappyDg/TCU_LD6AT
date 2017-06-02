/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : VADC                                                                                            */
/*                                                                                                                    */
/* !Component       : VADC                                                                                            */
/* !Description     : VADC unit                                                                                       */
/*                                                                                                                    */
/* !Module          : VADC                                                                                            */
/* !Description     : API of VADC unit                                                                                */
/*                                                                                                                    */
/* !File            : VADC.c                                                                                          */
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
/* 1 / VADC_vidInit                                                                                                   */
/* 2 / ISR_GRP_0_END_OF_CONV                                                                                          */
/* 3 / ISR_GRP_1_END_OF_CONV                                                                                          */
/* 4 / ISR_GRP_2_END_OF_CONV                                                                                          */
/* 5 / ISR_GRP_3_END_OF_CONV                                                                                          */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/
#include "Std_Types.h"
#include "Mcal.h"
#include "Dio.h"
#include "Evp.h"
//#include "INTBSL.h"
#include "Os_api.h"
#include "IntrinsicsGnuc.h"
#include "MATHSRV.h"
#include "VADC.h"
#include "VADC_Cfg.h"
#include "VADC_L.h"

extern void MAIN_vidAdcCallBackGroup1(void);
extern void MAIN_vidAdcCallBackGroup2(void);
extern void MAIN_vidAdcCallBackGroup3(void);
extern void MAIN_vidAdcCallBackGroup4(void);



#define VADC_START_SEC_CODE
#include "VADC_MemMap.h"

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : VADC_vidInit                                                                                        */
/*                                                                                                                    */
/* !Description : Initializes both VADC                                                                               */
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
void VADC_vidInit(void)
{
   uint32          u32LocCnt;
   volatile uint32 u32Start;
   Ifx_VADC_G    * pstLocGrp;
   uint32          u32LocGrpIdx;
   boolean         bBckModStarted;
   uint32          u32LocMsk;
   uint32          u32LocEnd;


   Mcal_ResetENDINIT();
   MODULE_VADC.CLC.U   = VADC_u32CLC_EDIS_SLEEP_DIS_MSK;
   MODULE_VADC.KRST1.U = VADC_u32KRST0_RST_RST_REQ_MSK;
   MODULE_VADC.KRST0.U = VADC_u32KRST1_RST_RST_REQ_MSK;

   u32Start = VADC_u32GET_TIMEOUT_START();
   while (  ((MODULE_VADC.KRST0.U & VADC_u32KRST0_RSTSTAT_MSK) != VADC_u32KRST0_RSTSTAT_RST_DONE_MSK)
         && (VADC_bTIMEOUT_ELAPSED(u32Start, VADC_u32TIMEOUT_1MICROS) == FALSE));
   Mcal_SetENDINIT();

   Mcal_ResetENDINIT();
   MODULE_VADC.KRSTCLR.U = VADC_u32KRSTCLR_RST_RST_CLR_MSK;
   u32Start = VADC_u32GET_TIMEOUT_START();
   while (  ((MODULE_VADC.KRST0.U & VADC_u32KRST0_RSTSTAT_MSK) != VADC_u32KRST0_RSTSTAT_NO_RST_MSK)
         && (VADC_bTIMEOUT_ELAPSED(u32Start, VADC_u32TIMEOUT_1MICROS) == FALSE));
   Mcal_SetENDINIT();

   Mcal_ResetENDINIT();
   MODULE_VADC.GLOBCFG.U       = VADC_u32GLOBCFG_DIVA_DIV_5_MSK | VADC_u32GLOBCFG_DCMSB_1_CLK_MSK
                               | VADC_u32GLOBCFG_DPCALx_AUTO_POSTCAL_MSK | VADC_u32GLOBCFG_DIVWC_WR_ENA_MSK
                               | VADC_u32GLOBCFG_SUCAL_START_CAL_MSK;
   MODULE_VADC.GLOBICLASS[0].U = VADC_kau32GlbIClass[0];
   MODULE_VADC.GLOBICLASS[1].U = VADC_kau32GlbIClass[1];
   Mcal_SetENDINIT();

   Mcal_ResetENDINIT();
   u32Start = VADC_u32GET_TIMEOUT_START();
   while ((MODULE_VADC.G[0].ARBCFG.B.CAL != 0) && (VADC_bTIMEOUT_ELAPSED(u32Start, VADC_u32TIMEOUT_1MICROS) == FALSE));
   while ((MODULE_VADC.G[1].ARBCFG.B.CAL != 0) && (VADC_bTIMEOUT_ELAPSED(u32Start, VADC_u32TIMEOUT_1MICROS) == FALSE));

   MODULE_VADC.GLOBBOUND.B.BOUNDARY0 = VADC_ku16MaxThrdGlobal;
   MODULE_VADC.GLOBBOUND.B.BOUNDARY1 = VADC_ku16MinThrdGlobal;

   MODULE_VADC.GLOBEFLAG.U = VADC_u32GLOBEFLAG_SEVGLBCLR_CLR_MSK | VADC_u32GLOBEFLAG_REVGLBCLR_CLR_MSK;

   for (u32LocGrpIdx = 0; u32LocGrpIdx < VADC_u8GROUP_NB_MAX; u32LocGrpIdx++)
   {
      MODULE_VADC.BRSPND[u32LocGrpIdx].U = 0u;
      MODULE_VADC.BRSSEL[u32LocGrpIdx].U = VADC_kastrGroupSources[u32LocGrpIdx].u32BckgScanCfg;
   }

   MODULE_VADC.BRSCTRL.U = VADC_u32xRSCTRL_XTMODE_NO_TRIGGER_MSK | VADC_u32BGRSCTRL_GTSEL_GTM_ADC8_TRIG0_MSK
                         | VADC_u32BGRSCTRL_XTSEL_CCU60_SR3_MSK | VADC_u32xRSCTRL_XTWC_WR_ENA_MSK
                         | VADC_u32xRSCTRL_GTWC_WR_ENA_MSK;
   MODULE_VADC.BRSMR.U   = VADC_u32BRSMR_ENGT_NO_CONV_REQ_MSK | VADC_u32BRSMR_ENTR_EXT_TRIG_DISA_MSK
                         | VADC_u32BRSMR_ENSI_SRC_INT_DISA_MSK | VADC_u32BRSMR_SCAN_AUTOSCAN_DISA_MSK
                         | VADC_u32BRSMR_LDM_OVERWR_MODE_MSK | VADC_u32BRSMR_CLRPND_NOP_MSK
                         | VADC_u32BRSMR_LDEV_NOP_MSK | VADC_u32BRSMR_RPTDIS_REPEAT_CANCELLED_ENA_MSK;

   MODULE_VADC.GLOBRCR.U = VADC_u32GLOBRCR_DRCTR_DATA_REDUC_DISA_MSK | VADC_u32GLOBRCR_WFR_OVERWR_MSK
                         | VADC_u32GLOBRCR_SRGEN_SERV_REQ_DISA_MSK;

   for (u32LocGrpIdx = 0; u32LocGrpIdx < VADC_u8GROUP_NB_MAX; u32LocGrpIdx++)
   {
      pstLocGrp = &MODULE_VADC.G[u32LocGrpIdx];

      pstLocGrp->ARBPR.U = VADC_kau32ArbnPrioReg[u32LocGrpIdx];

      pstLocGrp->CHASS.U = VADC_kau16ChAsgntReg[u32LocGrpIdx];
      pstLocGrp->RRASS.U = VADC_kau16ResAsgntReg[u32LocGrpIdx];

      pstLocGrp->ICLASS[0].U       = VADC_kau32GroupsIClass[u32LocGrpIdx][0];
      pstLocGrp->ICLASS[1].U       = VADC_kau32GroupsIClass[u32LocGrpIdx][1];
      pstLocGrp->ALIAS.U           = VADC_kau32Alias[u32LocGrpIdx];
      pstLocGrp->BOUND.B.BOUNDARY0 = VADC_kau16MaxThrdGrp[u32LocGrpIdx];
      pstLocGrp->BOUND.B.BOUNDARY1 = VADC_kau16MinThrdGrp[u32LocGrpIdx];

      pstLocGrp->SYNCTR.U = VADC_kau32Synctr[u32LocGrpIdx];
      pstLocGrp->BFL.U    = VADC_u32GxBFL_BFL0_PASSIVE_STT_MSK | VADC_u32GxBFL_BFL1_PASSIVE_STT_MSK
                          | VADC_u32GxBFL_BFL2_PASSIVE_STT_MSK | VADC_u32GxBFL_BFL3_PASSIVE_STT_MSK;
      pstLocGrp->BFLS.U   = VADC_u32GxBFLS_BFC0_CLR_BFL_MSK | VADC_u32GxBFLS_BFC1_CLR_BFL_MSK
                          | VADC_u32GxBFLS_BFC2_CLR_BFL_MSK | VADC_u32GxBFLS_BFC3_CLR_BFL_MSK;
      pstLocGrp->BFLC.U   = VADC_u32GxBFLC_BFM0_BOUND_FLAG_DISA_MSK | VADC_u32GxBFLC_BFM1_BOUND_FLAG_DISA_MSK
                          | VADC_u32GxBFLC_BFM2_BOUND_FLAG_DISA_MSK | VADC_u32GxBFLC_BFM3_BOUND_FLAG_DISA_MSK;
      pstLocGrp->BFLNP.U  = VADC_u32GxBFLNP_BFL0NP_OUT_DISA_MSK | VADC_u32GxBFLNP_BFL1NP_OUT_DISA_MSK
                          | VADC_u32GxBFLNP_BFL2NP_OUT_DISA_MSK | VADC_u32GxBFLNP_BFL3NP_OUT_DISA_MSK;

      if (VADC_kastrGroupSources[u32LocGrpIdx].u8Queue0NbCh != 0)
      {
         pstLocGrp->QCTRL0.U = VADC_kau32QCtrl0[u32LocGrpIdx];
      }
      pstLocGrp->QMR0.U = VADC_u32GxQMR0_ENGT_NO_CONV_REQ_MSK | VADC_u32GxQMR0_ENTR_EXT_TRIG_DISA_MSK
                        | VADC_u32GxQMR0_CLRV_CLR_NXT_ENTRY_MSK | VADC_u32GxQMR0_TREV_NOP_MSK
                        | VADC_u32GxQMR0_FLUSH_CLR_ALL_ENTRIES_MSK | VADC_u32GxQMR0_CEV_CLR_BIT_EV_MSK
                        | VADC_u32GxQMR0_RPTDIS_REPEAT_CANCELLED_ENA_MSK;
		
      for (u32LocCnt = 0; u32LocCnt < VADC_kastrGroupSources[u32LocGrpIdx].u8Queue0NbCh; u32LocCnt++)
         {
         pstLocGrp->QINR0.U = VADC_kastrGroupSources[u32LocGrpIdx].pku16Queue0Cfg[u32LocCnt];
      }

      for (u32LocCnt = 0; u32LocCnt < VADC_u32CHANNELS_NB_MAX; u32LocCnt++)
      {
         pstLocGrp->CHCTR[u32LocCnt].U = VADC_kau32Chctr[u32LocGrpIdx][u32LocCnt];
         pstLocGrp->RCR[u32LocCnt].U   = 0;
      }
      if (VADC_kastrGroupSources[u32LocGrpIdx].u32ScanCfg != 0)
      {
         pstLocGrp->ASPND.U = 0u;
         pstLocGrp->ASSEL.U = VADC_kastrGroupSources[u32LocGrpIdx].u32ScanCfg;
         pstLocGrp->ASPND.U = VADC_kastrGroupSources[u32LocGrpIdx].u32ScanCfg;
      }
   }

   /* Configuration of interrupts */
   MODULE_VADC.GLOBEFLAG.U = VADC_u32GLOBEFLAG_ALL_FLAG_CLR_MSK;
   MODULE_VADC.GLOBEVNP.U  = VADC_u32CFG_GLOBEVNP;
   for (u32LocGrpIdx = 0; u32LocGrpIdx < VADC_u8GROUP_NB_MAX; u32LocGrpIdx++)
   {
      pstLocGrp = &MODULE_VADC.G[u32LocGrpIdx];

      pstLocGrp->SEFCLR.U = VADC_u16GxSEFCLR_SRC_ALL_FLAG_CLR_MSK;
      pstLocGrp->CEFCLR.U = VADC_u16GxCEFCLR_AN_ALL_FLAG_CLR_MSK;
      pstLocGrp->REFCLR.U = VADC_u16GxREFCLR_AN_ALL_FLAG_CLR_MSK;

      pstLocGrp->SEVNP.U  = VADC_kau32SrcEveToSrvReqLine[u32LocGrpIdx];
      pstLocGrp->CEVNP0.U = VADC_kau32ChEveToSrvReqLine[u32LocGrpIdx][0];
#if VADC_u32CHANNELS_NB_MAX > 8
      pstLocGrp->CEVNP1.U = VADC_kau32ChEveToSrvReqLine[u32LocGrpIdx][1];
#endif
      pstLocGrp->REVNP0.U = VADC_kau32ResEveToSrvReqLine[u32LocGrpIdx][0];
      pstLocGrp->REVNP1.U = VADC_kau32ResEveToSrvReqLine[u32LocGrpIdx][1];
   }

   bBckModStarted = FALSE;
   for (u32LocGrpIdx = 0; u32LocGrpIdx < VADC_u8GROUP_NB_MAX; u32LocGrpIdx++)
   {
      if (  (VADC_kastrGroupSources[u32LocGrpIdx].u32ScanCfg != 0)
         || (VADC_kastrGroupSources[u32LocGrpIdx].u8Queue0NbCh != 0)
         || (VADC_kastrGroupSources[u32LocGrpIdx].u32BckgScanCfg != 0))
      {
         MODULE_VADC.G[u32LocGrpIdx].ARBCFG.U = VADC_kau16ArbnCfgReg[u32LocGrpIdx];
         if (VADC_kastrGroupSources[u32LocGrpIdx].u8Queue0NbCh != 0)
         {
            MODULE_VADC.G[u32LocGrpIdx].QMR0.U |= (VADC_u32GxQMR0_ENGT_IF_PENDING_MSK | VADC_u32GxQMR0_ENTR_EXT_TRIG_ENA_MSK);
         }
         if (VADC_kastrGroupSources[u32LocGrpIdx].u32ScanCfg != 0)
         {
            MODULE_VADC.G[u32LocGrpIdx].ASMR.U |= (VADC_u32BRSMR_ENGT_IF_PENDING_MSK | VADC_u32BRSMR_SCAN_AUTOSCAN_ENA_MSK);
         }
         if (VADC_kastrGroupSources[u32LocGrpIdx].u32BckgScanCfg != 0)
         {
            bBckModStarted = TRUE;
         }
      }
   }
   if (bBckModStarted != FALSE)
   {
      for (u32LocGrpIdx = 0; u32LocGrpIdx < VADC_u8GROUP_NB_MAX; u32LocGrpIdx++)
      {
         MODULE_VADC.BRSPND[u32LocGrpIdx].U = MODULE_VADC.BRSSEL[u32LocGrpIdx].U;
      }
      MODULE_VADC.BRSMR.U |= (VADC_u32BRSMR_ENGT_IF_PENDING_MSK | VADC_u32BRSMR_SCAN_AUTOSCAN_ENA_MSK);
   }
   Mcal_SetENDINIT();
}

/*---------------------------------------------------- end of file ---------------------------------------------------*/
