/**********************************************************************************************************************/
/* !Layer           : MCAL                                                                                            */
/*                                                                                                                    */
/* !Component       : VADC                                                                                            */
/* !Description     : Versatile Analog to Digital Converter Driver                                                    */
/*                                                                                                                    */
/* !Module          : VADC_L                                                                                          */
/* !Description     : Versatile Analog to Digital Converter Driver private declarations/definitions                   */
/*                                                                                                                    */
/* !File            : VADC_L.h                                                                                        */
/*                                                                                                                    */
/* !Target          : AURIX TC2x                                                                                      */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/

#ifndef VADC_L_H
#define VADC_L_H

#include "VADC_Target.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/

#define VADC_u32CONV_CLASSES_NB_MAX 2

/* CLC */
#define VADC_u32CLC_DISR_ON_REQ_MSK  (0u << 0)
#define VADC_u32CLC_DISR_OFF_REQ_MSK (1u << 0)

#define VADC_u32CLC_DISS_MSK         (1u << 1)
#define VADC_u32CLC_DISS_CLK_ON_MSK  (0u << 1)
#define VADC_u32CLC_DISS_CLK_OFF_MSK (1u << 1)

#define VADC_u32CLC_EDIS_SLEEP_ENA_MSK (0u << 3)
#define VADC_u32CLC_EDIS_SLEEP_DIS_MSK (1u << 3)

/* KRST0 */
#define VADC_u32KRST0_RST_NOP_MSK     (0u << 0)
#define VADC_u32KRST0_RST_RST_REQ_MSK (1u << 0)

#define VADC_u32KRST0_RSTSTAT_MSK          (1u << 1)
#define VADC_u32KRST0_RSTSTAT_NO_RST_MSK   (0u << 1)
#define VADC_u32KRST0_RSTSTAT_RST_DONE_MSK (1u << 1)

/* KRST1 */
#define VADC_u32KRST1_RST_NOP_MSK     (0u << 0)
#define VADC_u32KRST1_RST_RST_REQ_MSK (1u << 0)

/* KRSTCLR */
#define VADC_u32KRSTCLR_RST_NOP_MSK     (0u << 0)
#define VADC_u32KRSTCLR_RST_RST_CLR_MSK (1u << 0)

/* GLOBCFG */
#define VADC_u32GLOBCFG_DIVA_DIV_1_MSK  (0u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_2_MSK  (1u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_3_MSK  (2u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_4_MSK  (3u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_5_MSK  (4u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_6_MSK  (5u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_7_MSK  (6u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_8_MSK  (7u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_16_MSK (15u << 0)
#define VADC_u32GLOBCFG_DIVA_DIV_32_MSK (31u << 0)

#define VADC_u32GLOBCFG_DCMSB_1_CLK_MSK (0u << 7)
#define VADC_u32GLOBCFG_DCMSB_2_CLK_MSK (1u << 7)

#define VADC_u32GLOBCFG_DIVD_DIV_1_MSK (0u << 8)
#define VADC_u32GLOBCFG_DIVD_DIV_2_MSK (1u << 8)
#define VADC_u32GLOBCFG_DIVD_DIV_3_MSK (2u << 8)
#define VADC_u32GLOBCFG_DIVD_DIV_4_MSK (3u << 8)

#define VADC_u32GLOBCFG_DIVWC_WR_DISA_MSK (0u << 15)
#define VADC_u32GLOBCFG_DIVWC_WR_ENA_MSK  (1u << 15)

#define VADC_u32GLOBCFG_DPCAL0_NO_POSTCAL_MSK   (1u << 16)
#define VADC_u32GLOBCFG_DPCAL0_AUTO_POSTCAL_MSK (0u << 16)
#define VADC_u32GLOBCFG_DPCAL1_NO_POSTCAL_MSK   (1u << 17)
#define VADC_u32GLOBCFG_DPCAL1_AUTO_POSTCAL_MSK (0u << 17)
#define VADC_u32GLOBCFG_DPCAL2_NO_POSTCAL_MSK   (1u << 18)
#define VADC_u32GLOBCFG_DPCAL2_AUTO_POSTCAL_MSK (0u << 18)
#define VADC_u32GLOBCFG_DPCAL3_NO_POSTCAL_MSK   (1u << 19)
#define VADC_u32GLOBCFG_DPCAL3_AUTO_POSTCAL_MSK (0u << 19)
#define VADC_u32GLOBCFG_DPCAL4_NO_POSTCAL_MSK   (1u << 20)
#define VADC_u32GLOBCFG_DPCAL4_AUTO_POSTCAL_MSK (0u << 20)
#define VADC_u32GLOBCFG_DPCAL5_NO_POSTCAL_MSK   (1u << 21)
#define VADC_u32GLOBCFG_DPCAL5_AUTO_POSTCAL_MSK (0u << 21)
#define VADC_u32GLOBCFG_DPCAL6_NO_POSTCAL_MSK   (1u << 22)
#define VADC_u32GLOBCFG_DPCAL6_AUTO_POSTCAL_MSK (0u << 22)
#define VADC_u32GLOBCFG_DPCAL7_NO_POSTCAL_MSK   (1u << 28)
#define VADC_u32GLOBCFG_DPCAL7_AUTO_POSTCAL_MSK (0u << 28)
#define VADC_u32GLOBCFG_DPCALx_NO_POSTCAL_MSK   (255u << 16)
#define VADC_u32GLOBCFG_DPCALx_AUTO_POSTCAL_MSK (0u << 16)

#define VADC_u32GLOBCFG_SUCAL_START_CAL_MSK (1u << 31)

/* GxICLASS */
#define VADC_u32GxICLASS_STCS_STCE_1_CYC_MSK   (0u << 0)
#define VADC_u32GxICLASS_STCS_STCE_2_CYC_MSK   (1u << 0)
#define VADC_u32GxICLASS_STCS_STCE_3_CYC_MSK   (2u << 0)
#define VADC_u32GxICLASS_STCS_STCE_4_CYC_MSK   (3u << 0)
#define VADC_u32GxICLASS_STCS_STCE_5_CYC_MSK   (4u << 0)
#define VADC_u32GxICLASS_STCS_STCE_16_CYC_MSK  ((0u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_32_CYC_MSK  ((1u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_48_CYC_MSK  ((2u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_64_CYC_MSK  ((3u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_80_CYC_MSK  ((4u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_96_CYC_MSK  ((5u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_112_CYC_MSK ((6u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_128_CYC_MSK ((7u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_208_CYC_MSK ((13u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_240_CYC_MSK ((14u << 0) | (1u << 16))
#define VADC_u32GxICLASS_STCS_STCE_256_CYC_MSK ((15u << 0) | (1u << 16))

#define VADC_u32GxICLASS_CMS_12BITS_CONV_MSK           (0u << 8)
#define VADC_u32GxICLASS_CMS_10BITS_CONV_MSK           (1u << 8)
#define VADC_u32GxICLASS_CMS_8BITS_CONV_MSK            (2u << 8)
#define VADC_u32GxICLASS_CMS_10BITS_FAST_COMP_CONV_MSK (5u << 8)

#define VADC_u32GxICLASS_CME_12BITS_CONV_MSK           (0u << 24)
#define VADC_u32GxICLASS_CME_10BITS_CONV_MSK           (1u << 24)
#define VADC_u32GxICLASS_CME_8BITS_CONV_MSK            (2u << 24)
#define VADC_u32GxICLASS_CME_10BITS_FAST_COMP_CONV_MSK (5u << 24)

/* GLOBEFLAG */
#define VADC_u32GLOBEFLAG_SEVGLB_NO_SRC_EVT_MSK (0u << 0)
#define VADC_u32GLOBEFLAG_SEVGLB_SRC_EVT_MSK    (1u << 0)
#define VADC_u32GLOBEFLAG_SEVGLB_MSK            (1u << 0)

#define VADC_u32GLOBEFLAG_REVGLB_NO_RES_EVT_MSK (0u << 8)
#define VADC_u32GLOBEFLAG_REVGLB_RES_EVT_MSK    (1u << 8)
#define VADC_u32GLOBEFLAG_REVGLB_MSK            (1u << 8)

#define VADC_u32GLOBEFLAG_SEVGLBCLR_CLR_MSK (1u << 16)
#define VADC_u32GLOBEFLAG_REVGLBCLR_CLR_MSK (1u << 24)

/* BGRSCTRL */
#define VADC_u32BGRSCTRL_GTSEL_GTM_ADC8_TRIG0_MSK (0u << 16)
#define VADC_u32BGRSCTRL_GTSEL_GTM_ADC8_TRIG1_MSK (1u << 16)
#define VADC_u32BGRSCTRL_GTSEL_CCU6061_TRIG0_MSK  (2u << 16)
#define VADC_u32BGRSCTRL_GTSEL_CCU6061_TRIG1_MSK  (3u << 16)
#define VADC_u32BGRSCTRL_GTSEL_CCU6061_TRIG2_MSK  (4u << 16)

#define VADC_u32BGRSCTRL_XTSEL_CCU60_SR3_MSK  (0u << 8)
#define VADC_u32BGRSCTRL_XTSEL_CCU61_SR3_MSK  (1u << 8)
#define VADC_u32BGRSCTRL_XTSEL_ERU_IOUT_3_MSK (6u << 8)
#define VADC_u32BGRSCTRL_XTSEL_ERU_IOUT_4_MSK (7u << 8)
#define VADC_u32BGRSCTRL_XTSEL_ERU_IOUT_6_MSK (8u << 8)
#define VADC_u32BGRSCTRL_XTSEL_ERU_IOUT_7_MSK (9u << 8)
#define VADC_u32BGRSCTRL_XTSEL_VADC_C0SR1_MSK (13u << 8)
#define VADC_u32BGRSCTRL_XTSEL_VADC_C1SR1_MSK (14u << 8)
#define VADC_u32BGRSCTRL_XTSEL_GATE_INPUT_MSK (15u << 8)

/* xRSCTRL */
#define VADC_u32xRSCTRL_SRCRESREG_GxRESREG_MSK (0u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES1_MSK   (1u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES2_MSK   (2u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES3_MSK   (3u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES4_MSK   (4u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES5_MSK   (5u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES6_MSK   (6u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES7_MSK   (7u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES8_MSK   (8u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES9_MSK   (9u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES10_MSK  (10u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES11_MSK  (11u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES12_MSK  (12u << 0
#define VADC_u32xRSCTRL_SRCRESREG_GxRES13_MSK  (13u << 0)
#define VADC_u32xRSCTRL_SRCRESREG_GxRES14_MSK  (14u << 0
#define VADC_u32xRSCTRL_SRCRESREG_GxRES15_MSK  (15u << 0)

#define VADC_u32xRSCTRL_XTLVL_MSK (1u << 12)

#define VADC_u32xRSCTRL_XTMODE_NO_TRIGGER_MSK   (0u << 13)
#define VADC_u32xRSCTRL_XTMODE_FALLING_EDGE_MSK (1u << 13)
#define VADC_u32xRSCTRL_XTMODE_RISING_EDGE_MSK  (2u << 13)
#define VADC_u32xRSCTRL_XTMODE_ANY_EDGE_MSK     (3u << 13)

#define VADC_u32xRSCTRL_XTWC_WR_ENA_MSK  (1u << 15)
#define VADC_u32xRSCTRL_XTWC_WR_DISA_MSK (0u << 15)

#define VADC_u32xRSCTRL_GTLVL_MASK_MSK   (1u << 20)
#define VADC_u32xRSCTRL_GTWC_WR_ENA_MSK  (1u << 23)
#define VADC_u32xRSCTRL_GTWC_WR_DISA_MSK (0u << 23)

/* BRSMR */
#define VADC_u32BRSMR_ENGT_NO_CONV_REQ_MSK           (0u << 0)
#define VADC_u32BRSMR_ENGT_IF_PENDING_MSK            (1u << 0)
#define VADC_u32BRSMR_ENGT_IF_PENDING_AND_GATE_1_MSK (2u << 0)
#define VADC_u32BRSMR_ENGT_IF_PENDING_AND_GATE_0_MSK (3u << 0)

#define VADC_u32BRSMR_ENTR_EXT_TRIG_DISA_MSK (0u << 2)
#define VADC_u32BRSMR_ENTR_EXT_TRIG_ENA_MSK  (1u << 2)

#define VADC_u32BRSMR_ENSI_SRC_INT_DISA_MSK (0u << 3)
#define VADC_u32BRSMR_ENSI_SRC_INT_ENA_MSK  (1u << 3)

#define VADC_u32BRSMR_SCAN_AUTOSCAN_DISA_MSK (0u << 4)
#define VADC_u32BRSMR_SCAN_AUTOSCAN_ENA_MSK  (1u << 4)

#define VADC_u32BRSMR_LDM_OVERWR_MODE_MSK  (0u << 5)
#define VADC_u32BRSMR_LDM_COMBINE_MODE_MSK (1u << 5)

#define VADC_u32BRSMR_REQGT_GATE_LEVEL_MSK (1u << 7)

#define VADC_u32BRSMR_CLRPND_NOP_MSK (0u << 8)
#define VADC_u32BRSMR_CLRPND_CLR_MSK (1u << 8)

#define VADC_u32BRSMR_LDEV_NOP_MSK          (0u << 9)
#define VADC_u32BRSMR_LDEV_GEN_LOAD_EVT_MSK (1u << 9)

#define VADC_u32BRSMR_RPTDIS_REPEAT_CANCELLED_DISA_MSK (1u << 4)
#define VADC_u32BRSMR_RPTDIS_REPEAT_CANCELLED_ENA_MSK  (0u << 4)

/* GLOBRCR */
#define VADC_u32GLOBRCR_DRCTR_DATA_REDUC_DISA_MSK (0u << 16)
#define VADC_u32GLOBRCR_DRCTR_ACC_2_RES_MSK       (1u << 16)
#define VADC_u32GLOBRCR_DRCTR_ACC_3_RES_MSK       (2u << 16)
#define VADC_u32GLOBRCR_DRCTR_ACC_4_RES_MSK       (3u << 16)

#define VADC_u32GLOBRCR_WFR_OVERWR_MSK  (0u << 24)
#define VADC_u32GLOBRCR_WFR_WAIT4RD_MSK (1u << 24)

#define VADC_u32GLOBRCR_SRGEN_SERV_REQ_ENA_MSK  (1u << 31)
#define VADC_u32GLOBRCR_SRGEN_SERV_REQ_DISA_MSK (0u << 31)

/* GxARBPR */
#define VADC_u32GxARBPR_PRIO0_LOW_PRIO_MSK         (0u << 0)
#define VADC_u32GxARBPR_PRIO0_MEDIUM_LOW_PRIO_MSK  (1u << 0)
#define VADC_u32GxARBPR_PRIO0_MEDIUM_HIGH_PRIO_MSK (2u << 0)
#define VADC_u32GxARBPR_PRIO0_HIGH_PRIO_MSK        (3u << 0)

#define VADC_u32GxARBPR_PRIO1_LOW_PRIO_MSK         (0u << 4)
#define VADC_u32GxARBPR_PRIO1_MEDIUM_LOW_PRIO_MSK  (1u << 4)
#define VADC_u32GxARBPR_PRIO1_MEDIUM_HIGH_PRIO_MSK (2u << 4)
#define VADC_u32GxARBPR_PRIO1_HIGH_PRIO_MSK        (3u << 4)

#define VADC_u32GxARBPR_PRIO2_LOW_PRIO_MSK         (0u << 8)
#define VADC_u32GxARBPR_PRIO2_MEDIUM_LOW_PRIO_MSK  (1u << 8)
#define VADC_u32GxARBPR_PRIO2_MEDIUM_HIGH_PRIO_MSK (2u << 8)
#define VADC_u32GxARBPR_PRIO2_HIGH_PRIO_MSK        (3u << 8)

#define VADC_u32GxARBPR_PRIO3_LOW_PRIO_MSK         (0u << 12)
#define VADC_u32GxARBPR_PRIO3_MEDIUM_LOW_PRIO_MSK  (1u << 12)
#define VADC_u32GxARBPR_PRIO3_MEDIUM_HIGH_PRIO_MSK (2u << 12)
#define VADC_u32GxARBPR_PRIO3_HIGH_PRIO_MSK        (3u << 12)

#define VADC_u32GxARBPR_CSM0_WAIT4START_MSK     (0u << 3)
#define VADC_u32GxARBPR_CSM0_CANCEL_INJ_REP_MSK (1u << 3)
#define VADC_u32GxARBPR_CSM1_WAIT4START_MSK     (0u << 7)
#define VADC_u32GxARBPR_CSM1_CANCEL_INJ_REP_MSK (1u << 7)
#define VADC_u32GxARBPR_CSM2_WAIT4START_MSK     (0u << 11)
#define VADC_u32GxARBPR_CSM2_CANCEL_INJ_REP_MSK (1u << 11)
#define VADC_u32GxARBPR_CSM3_WAIT4START_MSK     (0u << 15)
#define VADC_u32GxARBPR_CSM3_CANCEL_INJ_REP_MSK (1u << 15)

#define VADC_u32GxARBPR_ASEN0_ARB_SLOT_DISA_MSK (0u << 24)
#define VADC_u32GxARBPR_ASEN0_ARB_SLOT_ENA_MSK  (1u << 24)
#define VADC_u32GxARBPR_ASEN1_ARB_SLOT_DISA_MSK (0u << 25)
#define VADC_u32GxARBPR_ASEN1_ARB_SLOT_ENA_MSK  (1u << 25)
#define VADC_u32GxARBPR_ASEN2_ARB_SLOT_DISA_MSK (0u << 26)
#define VADC_u32GxARBPR_ASEN2_ARB_SLOT_ENA_MSK  (1u << 26)
#define VADC_u32GxARBPR_ASEN3_ARB_SLOT_DISA_MSK (0u << 27)
#define VADC_u32GxARBPR_ASEN3_ARB_SLOT_ENA_MSK  (1u << 27)

/* ALIAS */
#define VADC_u32ALIAS_ALIAS0_CH_MSK(u8Ch) ((u8Ch) << 0)
#define VADC_u32ALIAS_ALIAS1_CH_MSK(u8Ch) ((u8Ch) << 8)
#define VADC_u32ALIAS_ALIAS0_DFLT_MSK     VADC_u32ALIAS_ALIAS0_CH_MSK(0u)
#define VADC_u32ALIAS_ALIAS1_DFLT_MSK     VADC_u32ALIAS_ALIAS1_CH_MSK(1u)

/* GxSYNCTR */
#define VADC_u32GxSYNCTR_STSEL_KRN_MASTER_MSK    (0u << 0)
#define VADC_u32GxSYNCTR_STSEL_KRN_SLAVE_CI1_MSK (1u << 0)
#define VADC_u32GxSYNCTR_STSEL_KRN_SLAVE_CI2_MSK (2u << 0)
#define VADC_u32GxSYNCTR_STSEL_KRN_SLAVE_CI3_MSK (3u << 0)

#define VADC_u32GxSYNCTR_EVALR1_RDY_INOUT_DISA_MSK (0u << 4)
#define VADC_u32GxSYNCTR_EVALR1_RDY_INOUT_ENA_MSK  (1u << 4)
#define VADC_u32GxSYNCTR_EVALR2_RDY_INOUT_DISA_MSK (0u << 5)
#define VADC_u32GxSYNCTR_EVALR2_RDY_INOUT_ENA_MSK  (1u << 5)
#define VADC_u32GxSYNCTR_EVALR3_RDY_INOUT_DISA_MSK (0u << 6)
#define VADC_u32GxSYNCTR_EVALR3_RDY_INOUT_ENA_MSK  (1u << 6)

/* GxBFL */
#define VADC_u32GxBFL_BFL0_PASSIVE_STT_MSK (0u << 0)
#define VADC_u32GxBFL_BFL0_ACTIVE_STT_MSK  (1u << 0)
#define VADC_u32GxBFL_BFL0_MSK             (1u << 0)
#define VADC_u32GxBFL_BFL1_PASSIVE_STT_MSK (0u << 1)
#define VADC_u32GxBFL_BFL1_ACTIVE_STT_MSK  (1u << 1)
#define VADC_u32GxBFL_BFL1_MSK             (1u << 1)
#define VADC_u32GxBFL_BFL2_PASSIVE_STT_MSK (0u << 2)
#define VADC_u32GxBFL_BFL2_ACTIVE_STT_MSK  (1u << 2)
#define VADC_u32GxBFL_BFL2_MSK             (1u << 2)
#define VADC_u32GxBFL_BFL3_PASSIVE_STT_MSK (0u << 3)
#define VADC_u32GxBFL_BFL3_ACTIVE_STT_MSK  (1u << 3)
#define VADC_u32GxBFL_BFL3_MSK             (1u << 3)

/* GxBFLS */
#define VADC_u32GxBFLS_BFC0_CLR_BFL_MSK (1u << 0)
#define VADC_u32GxBFLS_BFC1_CLR_BFL_MSK (1u << 1)
#define VADC_u32GxBFLS_BFC2_CLR_BFL_MSK (1u << 2)
#define VADC_u32GxBFLS_BFC3_CLR_BFL_MSK (1u << 3)

#define VADC_u32GxBFLS_BFS0_SET_BFL_MSK (1u << 16)
#define VADC_u32GxBFLS_BFS1_SET_BFL_MSK (1u << 17)
#define VADC_u32GxBFLS_BFS2_SET_BFL_MSK (1u << 18)
#define VADC_u32GxBFLS_BFS3_SET_BFL_MSK (1u << 19)

/* GxBFLC */
#define VADC_u32GxBFLC_BFM0_BOUND_FLAG_DISA_MSK          (0u << 0)
#define VADC_u32GxBFLC_BFM0_BOUND_FLAG_ENA_MSK           (1u << 0)
#define VADC_u32GxBFLC_BFM0_BOUND_FLAG_ENA_GATE_SRC1_MSK (2u << 0)
#define VADC_u32GxBFLC_BFM0_BOUND_FLAG_ENA_GATE_SRC2_MSK (3u << 0)
#define VADC_u32GxBFLC_BFM1_BOUND_FLAG_DISA_MSK          (0u << 4)
#define VADC_u32GxBFLC_BFM1_BOUND_FLAG_ENA_MSK           (1u << 4)
#define VADC_u32GxBFLC_BFM1_BOUND_FLAG_ENA_GATE_SRC1_MSK (2u << 4)
#define VADC_u32GxBFLC_BFM1_BOUND_FLAG_ENA_GATE_SRC2_MSK (3u << 4)
#define VADC_u32GxBFLC_BFM2_BOUND_FLAG_DISA_MSK          (0u << 8)
#define VADC_u32GxBFLC_BFM2_BOUND_FLAG_ENA_MSK           (1u << 8)
#define VADC_u32GxBFLC_BFM2_BOUND_FLAG_ENA_GATE_SRC1_MSK (2u << 8)
#define VADC_u32GxBFLC_BFM2_BOUND_FLAG_ENA_GATE_SRC2_MSK (3u << 8)
#define VADC_u32GxBFLC_BFM3_BOUND_FLAG_DISA_MSK          (0u << 12)
#define VADC_u32GxBFLC_BFM3_BOUND_FLAG_ENA_MSK           (1u << 12)
#define VADC_u32GxBFLC_BFM3_BOUND_FLAG_ENA_GATE_SRC1_MSK (2u << 12)
#define VADC_u32GxBFLC_BFM3_BOUND_FLAG_ENA_GATE_SRC2_MSK (3u << 12)

/* GxBFLNP */
#define VADC_u32GxBFLNP_BFL0NP_COM_FLAG_OUT0_MSK    (0u << 0)
#define VADC_u32GxBFLNP_BFL0NP_COM_FLAG_OUT1_MSK    (1u << 0)
#define VADC_u32GxBFLNP_BFL0NP_COM_FLAG_OUT2_MSK    (2u << 0)
#define VADC_u32GxBFLNP_BFL0NP_COM_FLAG_OUT3_MSK    (3u << 0)
#define VADC_u32GxBFLNP_BFL0NP_SHARED_REQ_LINE0_MSK (4u << 0)
#define VADC_u32GxBFLNP_BFL0NP_SHARED_REQ_LINE1_MSK (5u << 0)
#define VADC_u32GxBFLNP_BFL0NP_SHARED_REQ_LINE2_MSK (6u << 0)
#define VADC_u32GxBFLNP_BFL0NP_SHARED_REQ_LINE3_MSK (7u << 0)
#define VADC_u32GxBFLNP_BFL0NP_OUT_DISA_MSK         (15u << 0)

#define VADC_u32GxBFLNP_BFL1NP_COM_FLAG_OUT0_MSK    (0u << 4)
#define VADC_u32GxBFLNP_BFL1NP_COM_FLAG_OUT1_MSK    (1u << 4)
#define VADC_u32GxBFLNP_BFL1NP_COM_FLAG_OUT2_MSK    (2u << 4)
#define VADC_u32GxBFLNP_BFL1NP_COM_FLAG_OUT3_MSK    (3u << 4)
#define VADC_u32GxBFLNP_BFL1NP_SHARED_REQ_LINE0_MSK (4u << 4)
#define VADC_u32GxBFLNP_BFL1NP_SHARED_REQ_LINE1_MSK (5u << 4)
#define VADC_u32GxBFLNP_BFL1NP_SHARED_REQ_LINE2_MSK (6u << 4)
#define VADC_u32GxBFLNP_BFL1NP_SHARED_REQ_LINE3_MSK (7u << 4)
#define VADC_u32GxBFLNP_BFL1NP_OUT_DISA_MSK         (15u << 4)

#define VADC_u32GxBFLNP_BFL2NP_COM_FLAG_OUT0_MSK    (0u << 8)
#define VADC_u32GxBFLNP_BFL2NP_COM_FLAG_OUT1_MSK    (1u << 8)
#define VADC_u32GxBFLNP_BFL2NP_COM_FLAG_OUT2_MSK    (2u << 8)
#define VADC_u32GxBFLNP_BFL2NP_COM_FLAG_OUT3_MSK    (3u << 8)
#define VADC_u32GxBFLNP_BFL2NP_SHARED_REQ_LINE0_MSK (4u << 8)
#define VADC_u32GxBFLNP_BFL2NP_SHARED_REQ_LINE1_MSK (5u << 8)
#define VADC_u32GxBFLNP_BFL2NP_SHARED_REQ_LINE2_MSK (6u << 8)
#define VADC_u32GxBFLNP_BFL2NP_SHARED_REQ_LINE3_MSK (7u << 8)
#define VADC_u32GxBFLNP_BFL2NP_OUT_DISA_MSK         (15u << 8)

#define VADC_u32GxBFLNP_BFL3NP_COM_FLAG_OUT0_MSK    (0u << 12)
#define VADC_u32GxBFLNP_BFL3NP_COM_FLAG_OUT1_MSK    (1u << 12)
#define VADC_u32GxBFLNP_BFL3NP_COM_FLAG_OUT2_MSK    (2u << 12)
#define VADC_u32GxBFLNP_BFL3NP_COM_FLAG_OUT3_MSK    (3u << 12)
#define VADC_u32GxBFLNP_BFL3NP_SHARED_REQ_LINE0_MSK (4u << 12)
#define VADC_u32GxBFLNP_BFL3NP_SHARED_REQ_LINE1_MSK (5u << 12)
#define VADC_u32GxBFLNP_BFL3NP_SHARED_REQ_LINE2_MSK (6u << 12)
#define VADC_u32GxBFLNP_BFL3NP_SHARED_REQ_LINE3_MSK (7u << 12)
#define VADC_u32GxBFLNP_BFL3NP_OUT_DISA_MSK         (15u << 12)

/* GxCHCTR */
#define VADC_u32GxCHCTR_CALC_MSK(snICLSEL, snBNDSELL, snBNDSELU, snCHEVMODE, snSYNC, snREFSEL, \
                                 snBNDSELX, u8RESREG, snRESTBS, snRESPOS, snBWDCH, snBWDEN) \
   ( VADC_u32GxCHCTR_##snICLSEL##_MSK \
   | VADC_u32GxCHCTR_##snBNDSELL##_MSK \
   | VADC_u32GxCHCTR_##snBNDSELU##_MSK \
   | VADC_u32GxCHCTR_##snCHEVMODE##_MSK \
   | VADC_u32GxCHCTR_##snSYNC##_MSK \
   | VADC_u32GxCHCTR_##snREFSEL##_MSK \
   | VADC_u32GxCHCTR_##snBNDSELX##_MSK \
   | VADC_u8GxCHCTR_RESREG_CALC_MSK(u8RESREG) \
   | VADC_u32GxCHCTR_##snRESTBS##_MSK \
   | VADC_u32GxCHCTR_##snRESPOS##_MSK \
   | VADC_u32GxCHCTR_##snBWDCH##_MSK \
   | VADC_u32GxCHCTR_##snBWDEN##_MSK)

#define VADC_u32GxCHCTR_ICLSEL_GRP_CLASS_0_MSK (0u << 0)
#define VADC_u32GxCHCTR_ICLSEL_GRP_CLASS_1_MSK (1u << 0)
#define VADC_u32GxCHCTR_ICLSEL_GLB_CLASS_0_MSK (2u << 0)
#define VADC_u32GxCHCTR_ICLSEL_GLB_CLASS_1_MSK (3u << 0)

#define VADC_u32GxCHCTR_BNDSELL_GRP_BNDRY_0_MSK (0u << 4)
#define VADC_u32GxCHCTR_BNDSELL_GRP_BNDRY_1_MSK (1u << 4)
#define VADC_u32GxCHCTR_BNDSELL_GLB_BNDRY_0_MSK (2u << 4)
#define VADC_u32GxCHCTR_BNDSELL_GLB_BNDRY_1_MSK (3u << 4)

#define VADC_u32GxCHCTR_BNDSELU_GRP_BNDRY_0_MSK (0u << 6)
#define VADC_u32GxCHCTR_BNDSELU_GRP_BNDRY_1_MSK (1u << 6)
#define VADC_u32GxCHCTR_BNDSELU_GLB_BNDRY_0_MSK (2u << 6)
#define VADC_u32GxCHCTR_BNDSELU_GLB_BNDRY_1_MSK (3u << 6)

#define VADC_u32GxCHCTR_CHEVMODE_NEVER_MSK         (0u << 8)
#define VADC_u32GxCHCTR_CHEVMODE_NCM_IN_BNDRY_MSK  (1u << 8)
#define VADC_u32GxCHCTR_CHEVMODE_NCM_OUT_BNDRY_MSK (2u << 8)
#define VADC_u32GxCHCTR_CHEVMODE_NCM_ALWAYS_MSK    (3u << 8)
#define VADC_u32GxCHCTR_CHEVMODE_FCM_ABV_THD_MSK   (1u << 8)
#define VADC_u32GxCHCTR_CHEVMODE_FCM_BLW_THD_MSK   (2u << 8)
#define VADC_u32GxCHCTR_CHEVMODE_FCM_CHG_LVL_MSK   (3u << 8)

#define VADC_u32GxCHCTR_SYNC_DIS_MSK (0u << 10)
#define VADC_u32GxCHCTR_SYNC_ENA_MSK (1u << 10)

#define VADC_u32GxCHCTR_REFSEL_STD_MSK  (0u << 11)
#define VADC_u32GxCHCTR_REFSEL_ALTV_MSK (1u << 11)

#define VADC_u32GxCHCTR_BNDSELX_USE_BNDSELX_MSK (0u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_01_MSK  (1u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_02_MSK  (2u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_03_MSK  (3u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_04_MSK  (4u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_05_MSK  (5u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_06_MSK  (6u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_07_MSK  (7u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_08_MSK  (8u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_09_MSK  (9u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_10_MSK  (10u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_11_MSK  (11u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_12_MSK  (12u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_13_MSK  (13u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_14_MSK  (14u << 12)
#define VADC_u32GxCHCTR_BNDSELX_USE_RES_15_MSK  (15u << 12)

#define VADC_u8GxCHCTR_RESREG_SHIFT 16
#define VADC_u8GxCHCTR_RESREG_CALC_MSK(u8RESREG) (((u8RESREG) & 0x0Fu) << VADC_u8GxCHCTR_RESREG_SHIFT)

#define VADC_u32GxCHCTR_RESTBS_GRP_REG_MSK (0u << 20)
#define VADC_u32GxCHCTR_RESTBS_GLB_REG_MSK (1u << 20)

#define VADC_u32GxCHCTR_RESPOS_LEFT_ALGND_MSK  (0u << 21)
#define VADC_u32GxCHCTR_RESPOS_RIGHT_ALGND_MSK (1u << 21)

#define VADC_u32GxCHCTR_BWDCH_VAREF_MSK (0u << 28)
#define VADC_u32GxCHCTR_BWDCH_VAGND_MSK (1u << 28)

#define VADC_u32GxCHCTR_BWDEN_NORM_OPER_MSK    (0u << 30)
#define VADC_u32GxCHCTR_BWDEN_PREP_PHA_ENA_MSK (1u << 30)

/* GxQCTRL0 */
#define VADC_u32GxQCTRL0_SRCRESREG_GxRESREG_MSK (0u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES1_MSK   (1u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES2_MSK   (2u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES3_MSK   (3u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES4_MSK   (4u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES5_MSK   (5u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES6_MSK   (6u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES7_MSK   (7u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES8_MSK   (8u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES9_MSK   (9u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES10_MSK  (10u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES11_MSK  (11u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES12_MSK  (12u << 0
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES13_MSK  (13u << 0)
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES14_MSK  (14u << 0
#define VADC_u32GxQCTRL0_SRCRESREG_GxRES15_MSK  (15u << 0)

#define VADC_u32GxQCTRL0_GTSEL_GTM_ADCx_TRIG0_MSK (0u << 16)
#define VADC_u32GxQCTRL0_GTSEL_GTM_ADCx_TRIG1_MSK (1u << 16)
#define VADC_u32GxQCTRL0_GTSEL_CCU6061_TRIG0_MSK  (2u << 16)
#define VADC_u32GxQCTRL0_GTSEL_CCU6061_TRIG1_MSK  (3u << 16)
#define VADC_u32GxQCTRL0_GTSEL_CCU6061_TRIG2_MSK  (4u << 16)
#define VADC_u32GxQCTRL0_GTSEL_ERU_PDOUT_Y_MSK    (12u << 16)

#define VADC_u32GxQCTRL0_XTSEL_CCU60_SR3_MSK  (0u << 8)
#define VADC_u32GxQCTRL0_XTSEL_CCU61_SR3_MSK  (1u << 8)
#define VADC_u32GxQCTRL0_XTSEL_ERU_IOUT_Y_MSK (7u << 8)
#define VADC_u32GxQCTRL0_XTSEL_VADC_GxSR1_MSK (12u << 8)
#define VADC_u32GxQCTRL0_XTSEL_VADC_C0SR1_MSK (13u << 8)
#define VADC_u32GxQCTRL0_XTSEL_VADC_C1SR1_MSK (14u << 8)
#define VADC_u32GxQCTRL0_XTSEL_GATE_INPUT_MSK (15u << 8)

#define VADC_u32GxQCTRL0_XTLVL_MSK (1u << 12)

#define VADC_u32GxQCTRL0_XTMODE_NO_TRIGGER_MSK   (0u << 13)
#define VADC_u32GxQCTRL0_XTMODE_FALLING_EDGE_MSK (1u << 13)
#define VADC_u32GxQCTRL0_XTMODE_RISING_EDGE_MSK  (2u << 13)
#define VADC_u32GxQCTRL0_XTMODE_ANY_EDGE_MSK     (3u << 13)

#define VADC_u32GxQCTRL0_XTWC_WR_ENA_MSK  (1u << 15)
#define VADC_u32GxQCTRL0_XTWC_WR_DISA_MSK (0u << 15)

#define VADC_u32GxQCTRL0_GTLVL_MSK (1u << 20)

#define VADC_u32GxQCTRL0_GTWC_WR_ENA_MSK  (1u << 23)
#define VADC_u32GxQCTRL0_GTWC_WR_DISA_MSK (0u << 23)

#define VADC_u32GxQCTRL0_TMEN_NO_TIMER_MODE_MSK (0u << 28)
#define VADC_u32GxQCTRL0_TMEN_TIMER_MODE_MSK    (1u << 28)

#define VADC_u32GxQCTRL0_TMWC_TMEN_WR_ENA_MSK  (1u << 31)
#define VADC_u32GxQCTRL0_TMWC_TMEN_WR_DISA_MSK (0u << 31)

/* GxQMR0 */
#define VADC_u32GxQMR0_ENGT_NO_CONV_REQ_MSK           (0u << 0)
#define VADC_u32GxQMR0_ENGT_IF_PENDING_MSK            (1u << 0)
#define VADC_u32GxQMR0_ENGT_IF_PENDING_AND_GATE_1_MSK (2u << 0)
#define VADC_u32GxQMR0_ENGT_IF_PENDING_AND_GATE_0_MSK (3u << 0)

#define VADC_u32GxQMR0_ENTR_EXT_TRIG_DISA_MSK (0u << 2)
#define VADC_u32GxQMR0_ENTR_EXT_TRIG_ENA_MSK  (1u << 2)

#define VADC_u32GxQMR0_CLRV_NOP_MSK           (0u << 8)
#define VADC_u32GxQMR0_CLRV_CLR_NXT_ENTRY_MSK (1u << 8)

#define VADC_u32GxQMR0_TREV_NOP_MSK          (0u << 9)
#define VADC_u32GxQMR0_TREV_GEN_TRIG_EVT_MSK (1u << 9)

#define VADC_u32GxQMR0_FLUSH_NOP_MSK             (0u << 10)
#define VADC_u32GxQMR0_FLUSH_CLR_ALL_ENTRIES_MSK (1u << 10)

#define VADC_u32GxQMR0_CEV_NOP_MSK        (0u << 11)
#define VADC_u32GxQMR0_CEV_CLR_BIT_EV_MSK (1u << 11)

#define VADC_u32GxQMR0_RPTDIS_REPEAT_CANCELLED_DISA_MSK (1u << 16)
#define VADC_u32GxQMR0_RPTDIS_REPEAT_CANCELLED_ENA_MSK  (0u << 16)

/* GxQINR0 */
#define VADC_u32GxQINR0_REQCHNR_CHAN_00_MSK (0u << 0)
#define VADC_u32GxQINR0_REQCHNR_CHAN_01_MSK (1u << 0)
#define VADC_u32GxQINR0_REQCHNR_CHAN_02_MSK (2u << 0)
#define VADC_u32GxQINR0_REQCHNR_CHAN_03_MSK (3u << 0)
#define VADC_u32GxQINR0_REQCHNR_CHAN_04_MSK (4u << 0)
#define VADC_u32GxQINR0_REQCHNR_CHAN_05_MSK (5u << 0)
#define VADC_u32GxQINR0_REQCHNR_CHAN_06_MSK (6u << 0)
#define VADC_u32GxQINR0_REQCHNR_CHAN_07_MSK (7u << 0)

#define VADC_u32GxQINR0_RF_NO_REFILL_MSK   (0u << 5)
#define VADC_u32GxQINR0_RF_AUTO_REFILL_MSK (1u << 5)

#define VADC_u32GxQINR0_ENSI_NO_REQ_SRC_INT_MSK (0u << 6)
#define VADC_u32GxQINR0_ENSI_REQ_SRC_INT_MSK    (1u << 6)

#define VADC_u32GxQINR0_EXTR_AUTO_START_MSK   (0u << 7)
#define VADC_u32GxQINR0_EXTR_WAIT4TRIGGER_MSK (1u << 7)

/* GxARBCFG */
#define VADC_u32GxARBCFG_ANONC_CONV_OFF_MSK      (0u << 0)
#define VADC_u32GxARBCFG_ANONC_LOW_STBY_MSK      (1u << 0)
#define VADC_u32GxARBCFG_ANONC_FAST_STBY_MSK     (2u << 0)
#define VADC_u32GxARBCFG_ANONC_NORMAL_OP_MSK     (3u << 0)
#define VADC_u32GxARBCFG_ARBRND_ARB_4_SLOTS_MSK  (0u << 4)
#define VADC_u32GxARBCFG_ARBRND_ARB_8_SLOTS_MSK  (1u << 4)
#define VADC_u32GxARBCFG_ARBRND_ARB_16_SLOTS_MSK (2u << 4)
#define VADC_u32GxARBCFG_ARBRND_ARB_20_SLOTS_MSK (3u << 4)
#define VADC_u32GxARBCFG_ARBM_PERM_RUNNING_MSK   (0u << 7)
#define VADC_u32GxARBCFG_ARBM_RUN_IF_PENDING_MSK (1u << 7)

/* GLOBEFLAG */
#define VADC_u32GLOBEFLAG_SRC_BACKGND_FLAG_CLR_MSK (1u << 16)
#define VADC_u32GLOBEFLAG_GBL_RES_FLAG_CLR_MSK     (1u << 24)

#define VADC_u32GLOBEFLAG_ALL_FLAG_CLR_MSK (0x01010000u)

/* GLOBEVNP */
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP0_SHARED_LINE_0 (0u)
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP0_SHARED_LINE_1 (1u)
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP0_SHARED_LINE_2 (2u)
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP0_SHARED_LINE_3 (3u)
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP1_SHARED_LINE_0 (4u)
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP1_SHARED_LINE_1 (5u)
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP1_SHARED_LINE_2 (6u)
#define VADC_u32GLOBEVNP_SRV_REQ_GROUP1_SHARED_LINE_3 (7u)

#define VADC_u8GLOBEVNP_SRC_BACKGND_SHIFT (0)
#define VADC_u8GLOBEVNP_GBL_RES_SHIFT     (0)

#define VADC_u32GLOBEVNP_CALC_MSK(snCh, snSrvReqLine) \
   ((VADC_u32GLOBEVNP_SRV_REQ_##snSrvReqLine) << (VADC_u8GLOBEVNP_##snCh##_SHIFT))

/* GxSEFCLR */
#define VADC_u16GxSEFCLR_SRC_QUEUE0_FLAG_CLR_MSK (1u << 0)
#define VADC_u16GxSEFCLR_SRC_SCAN_FLAG_CLR_MSK   (1u << 1)
#define VADC_u16GxSEFCLR_SRC_QUEUE3_FLAG_CLR_MSK (1u << 3)

#define VADC_u16GxSEFCLR_SRC_ALL_FLAG_CLR_MSK (0x000Bu)

/* GxCEFCLR */
#define VADC_u16GxCEFCLR_AN00_FLAG_CLR_MSK (1u << 0)
#define VADC_u16GxCEFCLR_AN01_FLAG_CLR_MSK (1u << 1)
#define VADC_u16GxCEFCLR_AN02_FLAG_CLR_MSK (1u << 2)
#define VADC_u16GxCEFCLR_AN03_FLAG_CLR_MSK (1u << 3)
#define VADC_u16GxCEFCLR_AN04_FLAG_CLR_MSK (1u << 4)
#define VADC_u16GxCEFCLR_AN05_FLAG_CLR_MSK (1u << 5)
#define VADC_u16GxCEFCLR_AN06_FLAG_CLR_MSK (1u << 6)
#define VADC_u16GxCEFCLR_AN07_FLAG_CLR_MSK (1u << 7)
#define VADC_u16GxCEFCLR_AN08_FLAG_CLR_MSK (1u << 8)
#define VADC_u16GxCEFCLR_AN09_FLAG_CLR_MSK (1u << 9)
#define VADC_u16GxCEFCLR_AN10_FLAG_CLR_MSK (1u << 10)
#define VADC_u16GxCEFCLR_AN11_FLAG_CLR_MSK (1u << 11)

#define VADC_u16GxCEFCLR_AN_ALL_FLAG_CLR_MSK (0xFFFFu)

/* GxREFCLR */
#define VADC_u16GxREFCLR_AN00_FLAG_CLR_MSK (1u << 0)
#define VADC_u16GxREFCLR_AN01_FLAG_CLR_MSK (1u << 1)
#define VADC_u16GxREFCLR_AN02_FLAG_CLR_MSK (1u << 2)
#define VADC_u16GxREFCLR_AN03_FLAG_CLR_MSK (1u << 3)
#define VADC_u16GxREFCLR_AN04_FLAG_CLR_MSK (1u << 4)
#define VADC_u16GxREFCLR_AN05_FLAG_CLR_MSK (1u << 5)
#define VADC_u16GxREFCLR_AN06_FLAG_CLR_MSK (1u << 6)
#define VADC_u16GxREFCLR_AN07_FLAG_CLR_MSK (1u << 7)
#define VADC_u16GxREFCLR_AN08_FLAG_CLR_MSK (1u << 8)
#define VADC_u16GxREFCLR_AN09_FLAG_CLR_MSK (1u << 9)
#define VADC_u16GxREFCLR_AN10_FLAG_CLR_MSK (1u << 10)
#define VADC_u16GxREFCLR_AN11_FLAG_CLR_MSK (1u << 11)

#define VADC_u16GxREFCLR_AN_ALL_FLAG_CLR_MSK (0xFFFFu)

/* GxSEVNP */
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_LINE_0        (0u)
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_LINE_1        (1u)
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_LINE_2        (2u)
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_LINE_3        (3u)
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_SHARED_LINE_0 (4u)
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_SHARED_LINE_1 (5u)
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_SHARED_LINE_2 (6u)
#define VADC_u32GxSEVNP_SRV_REQ_GROUPX_SHARED_LINE_3 (7u)

#define VADC_u8GxSEVNP_SRC_QUEUE0_SHIFT (0)
#define VADC_u8GxSEVNP_SRC_SCAN_SHIFT   (4)
#define VADC_u8GxSEVNP_SRC_QUEUE3_SHIFT (12)

#define VADC_u32GxSEVNP_CALC_MSK(snSrc, snSrvReqLine) \
   ((VADC_u32GxSEVNP_SRV_REQ_##snSrvReqLine) << (VADC_u8GxSEVNP_SRC_##snSrc##_SHIFT))

/* GxCEVNP0/1 */
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_LINE_0        (0u)
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_LINE_1        (1u)
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_LINE_2        (2u)
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_LINE_3        (3u)
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_SHARED_LINE_0 (4u)
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_SHARED_LINE_1 (5u)
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_SHARED_LINE_2 (6u)
#define VADC_u32GxCEVNP_SRV_REQ_GROUPX_SHARED_LINE_3 (7u)

#define VADC_u8GxCEVNP0_AN00_SHIFT (0)
#define VADC_u8GxCEVNP0_AN01_SHIFT (4)
#define VADC_u8GxCEVNP0_AN02_SHIFT (8)
#define VADC_u8GxCEVNP0_AN03_SHIFT (12)
#define VADC_u8GxCEVNP0_AN04_SHIFT (16)
#define VADC_u8GxCEVNP0_AN05_SHIFT (20)
#define VADC_u8GxCEVNP0_AN06_SHIFT (24)
#define VADC_u8GxCEVNP0_AN07_SHIFT (28)
#define VADC_u8GxCEVNP1_AN08_SHIFT (0)
#define VADC_u8GxCEVNP1_AN09_SHIFT (4)
#define VADC_u8GxCEVNP1_AN10_SHIFT (8)
#define VADC_u8GxCEVNP1_AN11_SHIFT (12)

#define VADC_u32GxCEVNP0_CALC_MSK(snCh, snSrvReqLine) \
   ((VADC_u32GxCEVNP_SRV_REQ_##snSrvReqLine) << (VADC_u8GxCEVNP0_##snCh##_SHIFT))
#define VADC_u32GxCEVNP1_CALC_MSK(snCh, snSrvReqLine) \
   ((VADC_u32GxCEVNP_SRV_REQ_##snSrvReqLine) << (VADC_u8GxCEVNP1_##snCh##_SHIFT))

/* GxREVNP0/1 */
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_LINE_0        (0u)
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_LINE_1        (1u)
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_LINE_2        (2u)
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_LINE_3        (3u)
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_SHARED_LINE_0 (4u)
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_SHARED_LINE_1 (5u)
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_SHARED_LINE_2 (6u)
#define VADC_u32GxREVNP_SRV_REQ_GROUPX_SHARED_LINE_3 (7u)

#define VADC_u8GxREVNP0_AN00_SHIFT (0)
#define VADC_u8GxREVNP0_AN01_SHIFT (4)
#define VADC_u8GxREVNP0_AN02_SHIFT (8)
#define VADC_u8GxREVNP0_AN03_SHIFT (12)
#define VADC_u8GxREVNP0_AN04_SHIFT (16)
#define VADC_u8GxREVNP0_AN05_SHIFT (20)
#define VADC_u8GxREVNP0_AN06_SHIFT (24)
#define VADC_u8GxREVNP0_AN07_SHIFT (28)
#define VADC_u8GxREVNP1_AN08_SHIFT (0)
#define VADC_u8GxREVNP1_AN09_SHIFT (4)
#define VADC_u8GxREVNP1_AN10_SHIFT (8)
#define VADC_u8GxREVNP1_AN11_SHIFT (12)

#define VADC_u32GxREVNP0_CALC_MSK(snCh, snSrvReqLine) \
   ((VADC_u32GxREVNP_SRV_REQ_##snSrvReqLine) << (VADC_u8GxREVNP0_##snCh##_SHIFT))
#define VADC_u32GxREVNP1_CALC_MSK(snCh, snSrvReqLine) \
   ((VADC_u32GxREVNP_SRV_REQ_##snSrvReqLine) << (VADC_u8GxREVNP1_##snCh##_SHIFT))

#define VADC_u32TIMEOUT_1MICROS  1


/**********************************************************************************************************************/
/* MACRO FUNCTIONS DEFINITION                                                                                         */
/**********************************************************************************************************************/
#define VADC_u32GET_TIMEOUT_START() ((uint32)VADC_u32CFG_TIMEOUT_TMR)

#define VADC_bTIMEOUT_ELAPSED(u32Start, u32Dur /* in us */)  \
   ( (((uint32)((uint32)VADC_u32CFG_TIMEOUT_TMR  - (u32Start))) < ((uint32)(VADC_u32CFG_TIMEOUT_TMR_CLK_MHZ * (u32Dur)))) \
   ? FALSE \
   : TRUE)

#endif /* VADC_L_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
