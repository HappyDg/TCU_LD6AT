/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : VADC                                                                                            */
/*                                                                                                                    */
/* !Component       : VADC                                                                                            */
/* !Description     : VADC unit                                                                                       */
/*                                                                                                                    */
/* !Module          : VADC                                                                                            */
/* !Description     : Definitions of VADC unit                                                                        */
/*                                                                                                                    */
/* !File            : VADC_DEF.c                                                                                      */
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
//#include "INTBSL.h"
#include "Mcal.h"
#include "Dio.h"
#include "EVP.h"
#include "Os_api.h"
#include "VADC.h"
#include "VADC_Cfg.h"
#include "VADC_L.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
#define VADC_u8GROUP0_QUEUE0_NB_CH 1
#define VADC_u8GROUP1_QUEUE0_NB_CH 1

/**********************************************************************************************************************/
/* MACRO FUNCTIONS DEFINITION                                                                                         */
/**********************************************************************************************************************/
#define VADC_u32QINR0_CFG(snStart, snIt, snRefill, snCh) \
   ( (VADC_u32GxQINR0_EXTR_##snStart##_MSK) \
   | (VADC_u32GxQINR0_ENSI_##snIt##_MSK) \
   | (VADC_u32GxQINR0_RF_##snRefill##_MSK) \
   | (VADC_u8##snCh##_IDX))
  

/**********************************************************************************************************************/
/* CONSTANTS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define VADC_START_SEC_CONST_UNSPECIFIED
#include "VADC_MemMap.h"
#if 0
static const uint16 VADC_kau16Group0Queue0[VADC_u8GROUP0_QUEUE0_NB_CH] =
{
   VADC_u32QINR0_CFG(WAIT4TRIGGER, NO_REQ_SRC_INT, AUTO_REFILL, AN01 /* G0=ADC_SIN_1_P          / G1=ADC_SIN_1_N          */),
   VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN02 /* G0=ADC_COS_1_P          / G1=ADC_COS_1_N          */),
   VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN03 /* G0=ADC_PHASE_CURRENT_V1 / G1=ADC_PHASE_CURRENT_U1 */),
   VADC_u32QINR0_CFG(AUTO_START,   REQ_SRC_INT,    AUTO_REFILL, AN06 /* G0=                     / G1=ADC_PHASE_CURRENT_W  */),
};

static const uint16 VADC_kau16Group1Queue0[VADC_u8GROUP1_QUEUE0_NB_CH] =
{
   VADC_u32QINR0_CFG(WAIT4TRIGGER, NO_REQ_SRC_INT, AUTO_REFILL, AN05 /* G1=ADC_SIN_1_P          / AN17          */),
   VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN06 /* G1=ADC_COS_1_P          / AN18         */),
   VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN07 /* G1=ADC_PHASE_CURRENT_V1 / AN19 */),
   VADC_u32QINR0_CFG(AUTO_START,   REQ_SRC_INT,    AUTO_REFILL, AN08 /* G1=                     / AN20 */),
};
#endif

static const uint16 VADC_kau16Group0Queue0[VADC_u8GROUP0_QUEUE0_NB_CH] =
{
   VADC_u32QINR0_CFG(WAIT4TRIGGER, NO_REQ_SRC_INT, AUTO_REFILL, AN09 /* G0=ADC_SIN_1_P          / G1=ADC_SIN_1_N          */),
   //VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN02 /* G0=ADC_COS_1_P          / G1=ADC_COS_1_N          */),
   //VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN03 /* G0=ADC_PHASE_CURRENT_V1 / G1=ADC_PHASE_CURRENT_U1 */),
   //VADC_u32QINR0_CFG(AUTO_START,   REQ_SRC_INT,    AUTO_REFILL, AN06 /* G0=                     / G1=ADC_PHASE_CURRENT_W  */),
};

static const uint16 VADC_kau16Group1Queue0[VADC_u8GROUP1_QUEUE0_NB_CH] =
{
   VADC_u32QINR0_CFG(WAIT4TRIGGER, NO_REQ_SRC_INT, AUTO_REFILL, AN11 /* G1=AN_PRI_OIL_PRES          / AN23          */),
   //VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN06 /* G1=ADC_COS_1_P          / AN18         */),
   //VADC_u32QINR0_CFG(AUTO_START,   NO_REQ_SRC_INT, AUTO_REFILL, AN07 /* G1=ADC_PHASE_CURRENT_V1 / AN19 */),
   //VADC_u32QINR0_CFG(AUTO_START,   REQ_SRC_INT,    AUTO_REFILL, AN08 /* G1=                     / AN20 */),
};
const VADC_tstrGroupSources VADC_kastrGroupSources[VADC_u8GROUP_NB_MAX] =
{
   /* slave */
   {
      /* Queue 0 */
      VADC_u8GROUP0_QUEUE0_NB_CH,
      &VADC_kau16Group0Queue0[0],
      /* Scan */
      0,
      /* Background Scan */
      VADC_u16AN02_MSK | VADC_u16AN03_MSK | VADC_u16AN04_MSK | VADC_u16AN06_MSK |VADC_u16AN08_MSK|VADC_u16AN10_MSK|VADC_u16AN11_MSK,
      /* Queue 3 */
      0,
      NULL_PTR
   },
   /* master */
{
      /* Queue 0 */
      VADC_u8GROUP1_QUEUE0_NB_CH,
      &VADC_kau16Group1Queue0[0],
      /* Scan */
      0,
      /* Background Scan */
      VADC_u16AN00_MSK | VADC_u16AN01_MSK | VADC_u16AN02_MSK | VADC_u16AN03_MSK | VADC_u16AN05_MSK | VADC_u16AN06_MSK | VADC_u16AN07_MSK |VADC_u16AN09_MSK|VADC_u16AN10_MSK|VADC_u16AN11_MSK,
      /* Queue 3 */
      0,
      NULL_PTR
   }
};

const uint32 VADC_kau32QCtrl0[VADC_u8GROUP_NB_MAX] =
{
   ( VADC_u32GxQCTRL0_SRCRESREG_GxRESREG_MSK | VADC_u32GxQCTRL0_GTSEL_GTM_ADCx_TRIG1_MSK
   | VADC_u32GxQCTRL0_XTSEL_GATE_INPUT_MSK | VADC_u32GxQCTRL0_XTMODE_FALLING_EDGE_MSK
   | VADC_u32GxQCTRL0_XTWC_WR_ENA_MSK | VADC_u32GxQCTRL0_GTWC_WR_ENA_MSK
   | VADC_u32GxQCTRL0_TMEN_NO_TIMER_MODE_MSK | VADC_u32GxQCTRL0_TMWC_TMEN_WR_ENA_MSK),
   ( VADC_u32GxQCTRL0_SRCRESREG_GxRESREG_MSK | VADC_u32GxQCTRL0_GTSEL_GTM_ADCx_TRIG1_MSK
   | VADC_u32GxQCTRL0_XTSEL_GATE_INPUT_MSK | VADC_u32GxQCTRL0_XTMODE_FALLING_EDGE_MSK
   | VADC_u32GxQCTRL0_XTWC_WR_ENA_MSK | VADC_u32GxQCTRL0_GTWC_WR_ENA_MSK
   | VADC_u32GxQCTRL0_TMEN_NO_TIMER_MODE_MSK | VADC_u32GxQCTRL0_TMWC_TMEN_WR_ENA_MSK)
};

/* Masters shall have a higher group index than their linked slaves */
/* (mandatory for initialization which is done in the index order,  */
/* masters needing to be activated after their linked slaves)       */
const uint32 VADC_kau32Synctr[VADC_u8GROUP_NB_MAX] =
{
   ( VADC_u32GxSYNCTR_STSEL_KRN_MASTER_MSK | VADC_u32GxSYNCTR_EVALR1_RDY_INOUT_DISA_MSK
   | VADC_u32GxSYNCTR_EVALR2_RDY_INOUT_DISA_MSK | VADC_u32GxSYNCTR_EVALR3_RDY_INOUT_DISA_MSK),
   ( VADC_u32GxSYNCTR_STSEL_KRN_MASTER_MSK | VADC_u32GxSYNCTR_EVALR1_RDY_INOUT_DISA_MSK
   | VADC_u32GxSYNCTR_EVALR2_RDY_INOUT_DISA_MSK | VADC_u32GxSYNCTR_EVALR3_RDY_INOUT_DISA_MSK)
};

const uint32 VADC_kau32Alias[VADC_u8GROUP_NB_MAX] =
{
   (VADC_u32ALIAS_ALIAS0_DFLT_MSK | VADC_u32ALIAS_ALIAS1_DFLT_MSK),
   (VADC_u32ALIAS_ALIAS0_DFLT_MSK | VADC_u32ALIAS_ALIAS1_DFLT_MSK)
};

const uint32 VADC_kau32GlbIClass[VADC_u32CONV_CLASSES_NB_MAX] =
{
   (VADC_u32GxICLASS_STCS_STCE_1_CYC_MSK | VADC_u32GxICLASS_CMS_12BITS_CONV_MSK | VADC_u32GxICLASS_CME_12BITS_CONV_MSK),
   (VADC_u32GxICLASS_STCS_STCE_1_CYC_MSK | VADC_u32GxICLASS_CMS_12BITS_CONV_MSK | VADC_u32GxICLASS_CME_12BITS_CONV_MSK)
};

const uint32 VADC_kau32GroupsIClass[VADC_u8GROUP_NB_MAX][VADC_u32CONV_CLASSES_NB_MAX] =
{
   {
      (VADC_u32GxICLASS_STCS_STCE_1_CYC_MSK | VADC_u32GxICLASS_CMS_12BITS_CONV_MSK | VADC_u32GxICLASS_CME_12BITS_CONV_MSK),
      (VADC_u32GxICLASS_STCS_STCE_1_CYC_MSK | VADC_u32GxICLASS_CMS_12BITS_CONV_MSK | VADC_u32GxICLASS_CME_12BITS_CONV_MSK)
   },
{
      (VADC_u32GxICLASS_STCS_STCE_1_CYC_MSK | VADC_u32GxICLASS_CMS_12BITS_CONV_MSK | VADC_u32GxICLASS_CME_12BITS_CONV_MSK),
      (VADC_u32GxICLASS_STCS_STCE_1_CYC_MSK | VADC_u32GxICLASS_CMS_12BITS_CONV_MSK | VADC_u32GxICLASS_CME_12BITS_CONV_MSK)
   }
};

const uint32 VADC_kau32Chctr[VADC_u8GROUP_NB_MAX][VADC_u32CHANNELS_NB_MAX] =
{
   {
       VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 0, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 1, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 2, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 3, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 4, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 5, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 6, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 7, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 8, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 9, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 10, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 11, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER)
   },
   {
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 0, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 1, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 2, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 3, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 4, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 5, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 6, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 7, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 8, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 9, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 10, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER),
      VADC_u32GxCHCTR_CALC_MSK(ICLSEL_GLB_CLASS_0, BNDSELL_GLB_BNDRY_0, BNDSELU_GLB_BNDRY_0, CHEVMODE_NEVER, SYNC_DIS,
                               REFSEL_STD, BNDSELX_USE_BNDSELX, 11, RESTBS_GRP_REG, RESPOS_LEFT_ALGND,
                               BWDCH_VAREF, BWDEN_NORM_OPER)
   }
};

/* These constants depend on VADC_kau16Group1Queue0, VADC_kastrGroupSources, VADC_kau32Alias and VADC_kau32Chctr */
const uint16 VADC_kau16ChAsgntReg[VADC_u8GROUP_NB_MAX] =
{
   (VADC_u16AN09_MSK),
   (VADC_u16AN23_MSK)
};
const uint16 VADC_kau16ResAsgntReg[VADC_u8GROUP_NB_MAX] =
{
   (VADC_u16AN09_MSK ),
   (VADC_u16AN23_MSK )
};

/* ASEN3_ARB_SLOT_DISA(X=4)/DISA(X=8) shall be consistent with ARBRND_ARB_X_SLOTS */
const uint32 VADC_kau32ArbnPrioReg[VADC_u8GROUP_NB_MAX] =
{
   ( VADC_u32GxARBPR_PRIO0_HIGH_PRIO_MSK | VADC_u32GxARBPR_PRIO1_MEDIUM_LOW_PRIO_MSK
   | VADC_u32GxARBPR_PRIO2_LOW_PRIO_MSK | VADC_u32GxARBPR_PRIO3_LOW_PRIO_MSK
   | VADC_u32GxARBPR_CSM0_WAIT4START_MSK | VADC_u32GxARBPR_CSM1_WAIT4START_MSK
   | VADC_u32GxARBPR_CSM2_WAIT4START_MSK | VADC_u32GxARBPR_CSM3_WAIT4START_MSK
   | VADC_u32GxARBPR_ASEN0_ARB_SLOT_ENA_MSK | VADC_u32GxARBPR_ASEN1_ARB_SLOT_ENA_MSK
   | VADC_u32GxARBPR_ASEN2_ARB_SLOT_ENA_MSK | VADC_u32GxARBPR_ASEN3_ARB_SLOT_DISA_MSK),
   ( VADC_u32GxARBPR_PRIO0_HIGH_PRIO_MSK | VADC_u32GxARBPR_PRIO1_MEDIUM_LOW_PRIO_MSK
   | VADC_u32GxARBPR_PRIO2_LOW_PRIO_MSK | VADC_u32GxARBPR_PRIO3_LOW_PRIO_MSK
   | VADC_u32GxARBPR_CSM0_WAIT4START_MSK | VADC_u32GxARBPR_CSM1_WAIT4START_MSK
   | VADC_u32GxARBPR_CSM2_WAIT4START_MSK | VADC_u32GxARBPR_CSM3_WAIT4START_MSK
   | VADC_u32GxARBPR_ASEN0_ARB_SLOT_ENA_MSK | VADC_u32GxARBPR_ASEN1_ARB_SLOT_ENA_MSK
   | VADC_u32GxARBPR_ASEN2_ARB_SLOT_ENA_MSK | VADC_u32GxARBPR_ASEN3_ARB_SLOT_DISA_MSK)
};
/* ARBRND_ARB_X_SLOTS shall be consistent with ASEN3_ARB_SLOT_DISA(X=4)/DISA(X=8) */
const uint16 VADC_kau16ArbnCfgReg[VADC_u8GROUP_NB_MAX] =
{
   (VADC_u32GxARBCFG_ARBM_PERM_RUNNING_MSK | VADC_u32GxARBCFG_ARBRND_ARB_4_SLOTS_MSK | VADC_u32GxARBCFG_ANONC_NORMAL_OP_MSK),
   (VADC_u32GxARBCFG_ARBM_PERM_RUNNING_MSK | VADC_u32GxARBCFG_ARBRND_ARB_4_SLOTS_MSK | VADC_u32GxARBCFG_ANONC_NORMAL_OP_MSK)
};

const uint32 VADC_kau32SrcEveToSrvReqLine[VADC_u8GROUP_NB_MAX] =
{
   VADC_u32GxSEVNP_CALC_MSK(QUEUE0, GROUPX_LINE_0),
   VADC_u32GxSEVNP_CALC_MSK(QUEUE0, GROUPX_LINE_0)
};
const uint32 VADC_kau32ChEveToSrvReqLine[VADC_u8GROUP_NB_MAX][2] =
{
   {
      0, /* Not used */
      0  /* Not used */
   },
   {
      0, /* Not used */
      0  /* Not used */
   }
};
const uint32 VADC_kau32ResEveToSrvReqLine[VADC_u8GROUP_NB_MAX][2] =
{
   {
      0, /* Not used */
      0  /* Not used */
   },
   {
      0, /* Not used */
      0  /* Not used */
   }
};

const uint16 VADC_ku16MaxThrdGlobal = 3900;
const uint16 VADC_ku16MinThrdGlobal = 200;
const uint16 VADC_kau16MaxThrdGrp[VADC_u8GROUP_NB_MAX] =
{
   3900, 3900
};
const uint16 VADC_kau16MinThrdGrp[VADC_u8GROUP_NB_MAX] =
{
   200, 200
};
    
#define VADC_STOP_SEC_CONST_UNSPECIFIED
#include "VADC_MemMap.h"

/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/
#define VADC_START_SEC_VAR_UNSPECIFIED
#include "VADC_MemMap.h"

uint16 VADC_au16ConvRes[VADC_u8NB_CONV_RES];
uint16 SWTST_au16AdcRes[30];
sint32 VADC_as32IsrDelay[4][3];
uint32 VADC_au32IsrPeriod[4];
uint32 VADC_au32IsrTimeStamp[4];

#define VADC_STOP_SEC_VAR_UNSPECIFIED
#include "VADC_MemMap.h"


/**********************************************************************************************************************/
/* FUNCTIONS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define VADC_START_SEC_CODE
#include "VADC_MemMap.h"

void VADC_vidEna(void)
{
   MODULE_GTM.ADCTRIG0OUT0.U  = 0x0000;
   MODULE_GTM.ADCTRIG1OUT0.U  = 0x00000021;

   //INTBSL_vidENA_IT(ISR_GRP_0_END_OF_CONV);
   Os_Enable_ISR_GRP_0_END_OF_CONV();
}


/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : ISR_GRP_3_END_OF_CONV                                                                               */
/*                                                                                                                    */
/* !Description : Interrupt trigged by the last element of queue of group 3                                           */
/* !Number      : 5                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : isr                                                                                                    */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void VADC_vidUpdate10ms(void)
{
   VADC_au16ConvRes[VADC_u8AN_DIAG_SOL_SW_2_RES_IDX]                          = VADC_u16GET_VALUE(AN_DIAG_SOL_SW_2);
   VADC_au16ConvRes[VADC_u8AN_DIAG_SOL_SW_1_RES_IDX]                = VADC_u16GET_VALUE(AN_DIAG_SOL_SW_1);
   VADC_au16ConvRes[VADC_u8AN_TOSS_RES_IDX]                         = VADC_u16GET_VALUE(AN_TOSS);
   VADC_au16ConvRes[VADC_u8AN_C4_SPD_SNS_RES_IDX]                     = VADC_u16GET_VALUE(AN_C4_SPD_SNS);
   VADC_au16ConvRes[VADC_u8AN_RESERVED_TEMP_1_RES_IDX]                       = VADC_u16GET_VALUE(AN_RESERVED_TEMP_1);
   VADC_au16ConvRes[VADC_u8AN_PRI_OIL_TEMP_RES_IDX]                         = VADC_u16GET_VALUE(AN_PRI_OIL_TEMP);
   VADC_au16ConvRes[VADC_u8AN_TMP_PCB_RES_IDX]                         = VADC_u16GET_VALUE(AN_TMP_PCB);
   VADC_au16ConvRes[VADC_u8AN_G4_SPD_SNS_RES_IDX]                     = VADC_u16GET_VALUE(AN_G4_SPD_SNS);
   VADC_au16ConvRes[VADC_u8AN_P5V_INTERNAL_RES_IDX]                     = VADC_u16GET_VALUE(AN_P5V_INTERNAL);
   VADC_au16ConvRes[VADC_u8AN_P5V_SNS_SUP_1_RES_IDX]                = VADC_u16GET_VALUE(AN_P5V_SNS_SUP_1);
   VADC_au16ConvRes[VADC_u8AN_VCC_3V3_SUP_RES_IDX]                    = VADC_u16GET_VALUE(AN_VCC_3V3_SUP);
   VADC_au16ConvRes[VADC_u8AN_P9V_SNS_SUP_RES_IDX]           = VADC_u16GET_VALUE(AN_P9V_SNS_SUP);
   VADC_au16ConvRes[VADC_u8AN_VBAT_P_SW_SUP_RES_IDX]           = VADC_u16GET_VALUE(AN_VBAT_P_SW_SUP);
   VADC_au16ConvRes[VADC_u8AN_T30_BATT_RES_IDX]           = VADC_u16GET_VALUE(AN_T30_BATT);
   VADC_au16ConvRes[VADC_u8AN_T15_IGN_RES_IDX]     = VADC_u16GET_VALUE(AN_T15_IGN);
   VADC_au16ConvRes[VADC_u8AN_RESERVED_1_RES_IDX]     = VADC_u16GET_VALUE(AN_RESERVED_1);
   VADC_au16ConvRes[VADC_u8AN_RESERVED_2_RES_IDX]     = VADC_u16GET_VALUE(AN_RESERVED_2);
   VADC_au16ConvRes[VADC_u8AN_PRI_OIL_PRES_RES_IDX]     = VADC_u16GET_VALUE(AN_PRI_OIL_PRES);
}

#define VADC_STOP_SEC_CODE
#include "VADC_MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/