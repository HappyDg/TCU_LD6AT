/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : EVP                                                                                             */
/*                                                                                                                    */
/* !Component       : EVP                                                                                             */
/* !Description     : EVP unit                                                                                        */
/*                                                                                                                    */
/* !Module          : EVP                                                                                             */
/* !Description     : Internal defines of EVP unit                                                                    */
/*                                                                                                                    */
/* !File            : EVP_I.h                                                                                         */
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

#ifndef EVP_I_H
#define EVP_I_H

#include "Std_Types.h"
#include "Gtm.h"
#include "Evp_cfg.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
#define EVP_u8NB_GROUP              1
#define EVP_u8NB_CH_MAX_BY_GROUP    6
#define EVP_u8NB_CHAN_BY_GROUPID_0  0  
#define EVP_u8NB_CHAN_BY_GROUPID_1  1
#define EVP_u8NB_CHAN_BY_GROUPID_2  2
#define EVP_u8NB_CHAN_BY_GROUPID_3  3
#define EVP_u8NB_CHAN_BY_GROUPID_4  4
#define EVP_u8NB_CHAN_BY_GROUPID_5  5

//#define EVP_u32NB_INTERNAL_CHAN  (3u) /* Period channel + Diagnosis channel + ADC trigger channel */

#define EVP_u8GRP_0_TOM_IDX 1

#define EVP_u8TRIG_0_TOM_IDX 1
#define EVP_u8TRIG_1_TOM_IDX 1


#define GTM_TOM_CHx_CTRL_SL_LOW_LEVEL                  (0u << 11)
#define GTM_TOM_CHx_CTRL_SL_HIGH_LEVEL                 (1u << 11)
#define GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL           (0u << 12)
#define GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL_DIV16     (1u << 12)
#define GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL_DIV256    (2u << 12)
#define GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL_DIV4096   (3u << 12)
#define GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL_DIV16384  (4u << 12)
#define GTM_TOM_CHx_CTRL_CLK_SRC_SR_NO_CLOCK           (7u << 12)
#define GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_CM0_MATCH     (0u << 20)
#define GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_TRIG_NM1      (1u << 20)
#define GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_NM1              (0u << 24)
#define GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_CCU0             (1u << 24)
#define GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_DISA        (0u << 26)
#define GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_ENA         (1u << 26)
#define GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_DISA            (0u << 28)
#define GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_ENA             (1u << 28)
#define GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_DISA   (0u << 29)
#define GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_ENA    (1u << 29)

#define GTM_TOM_TGC_GLB_CTRL_HOST_TRIG_NOP          (0u << 0)
#define GTM_TOM_TGC_GLB_CTRL_HOST_TRIG_SET_TRIG_REQ (1u << 0)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH0_NOP        (0u << 8)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH0_SW_RST (1u << 8)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH1_NOP    (0u << 9)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH1_SW_RST (1u << 9)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH2_NOP    (0u << 10)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH2_SW_RST (1u << 10)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH3_NOP    (0u << 11)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH3_SW_RST (1u << 11)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH4_NOP    (0u << 12)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH4_SW_RST (1u << 12)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH5_NOP    (0u << 13)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH5_SW_RST (1u << 13)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH6_NOP    (0u << 14)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH6_SW_RST (1u << 14)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH7_NOP    (0u << 15)
#define GTM_TOM_TGC_GLB_CTRL_RST_CH7_SW_RST (1u << 15)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_NOP      (0u << 16)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_UPD_DISA (1u << 16)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL0_UPD_ENA  (2u << 16)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL1_NOP      (0u << 18)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL1_UPD_DISA (1u << 18)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL1_UPD_ENA  (2u << 18)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL2_NOP      (0u << 20)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL2_UPD_DISA (1u << 20)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL2_UPD_ENA  (2u << 20)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL3_NOP      (0u << 22)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL3_UPD_DISA (1u << 22)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL3_UPD_ENA  (2u << 22)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL4_NOP      (0u << 24)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL4_UPD_DISA (1u << 24)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL4_UPD_ENA  (2u << 24)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL5_NOP      (0u << 26)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL5_UPD_DISA (1u << 26)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL5_UPD_ENA  (2u << 26)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL6_NOP      (0u << 28)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL6_UPD_DISA (1u << 28)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL6_UPD_ENA  (2u << 28)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL7_NOP      (0u << 30)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL7_UPD_DISA (1u << 30)
#define GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL7_UPD_ENA  (2u << 30)

#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL0_NOP        (0u << 0)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL0_FORCE_DISA (1u << 0)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL0_FORCE_ENA  (2u << 0)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL1_NOP        (0u << 2)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL1_FORCE_DISA (1u << 2)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL1_FORCE_ENA  (2u << 2)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL2_NOP        (0u << 4)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL2_FORCE_DISA (1u << 4)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL2_FORCE_ENA  (2u << 4)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL3_NOP        (0u << 6)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL3_FORCE_DISA (1u << 6)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL3_FORCE_ENA  (2u << 6)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL4_NOP        (0u << 8)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL4_FORCE_DISA (1u << 8)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL4_FORCE_ENA  (2u << 8)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL5_NOP        (0u << 10)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL5_FORCE_DISA (1u << 10)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL5_FORCE_ENA  (2u << 10)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL6_NOP        (0u << 12)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL6_FORCE_DISA (1u << 12)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL6_FORCE_ENA  (2u << 12)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL7_NOP        (0u << 14)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL7_FORCE_DISA (1u << 14)
#define GTM_TOM_TGC_FUPD_CTRL_FUPD_CTRL7_FORCE_ENA  (2u << 14)

#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH0_NOP             (0u << 16)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH0_NO_RST_ON_FORCE (1u << 16)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH0_RST_ON_FORCE    (2u << 16)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH1_NOP             (0u << 18)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH1_NO_RST_ON_FORCE (1u << 18)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH1_RST_ON_FORCE    (2u << 18)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH2_NOP             (0u << 20)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH2_NO_RST_ON_FORCE (1u << 20)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH2_RST_ON_FORCE    (2u << 20)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH3_NOP             (0u << 22)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH3_NO_RST_ON_FORCE (1u << 22)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH3_RST_ON_FORCE    (2u << 22)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH4_NOP             (0u << 24)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH4_NO_RST_ON_FORCE (1u << 24)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH4_RST_ON_FORCE    (2u << 24)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH5_NOP             (0u << 26)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH5_NO_RST_ON_FORCE (1u << 26)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH5_RST_ON_FORCE    (2u << 26)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH6_NOP             (0u << 28)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH6_NO_RST_ON_FORCE (1u << 28)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH6_RST_ON_FORCE    (2u << 28)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH7_NOP             (0u << 30)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH7_NO_RST_ON_FORCE (1u << 30)
#define GTM_TOM_TGC_FUPD_CTRL_RSTCN0_CH7_RST_ON_FORCE    (2u << 30)

#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL0_NOP              (0u << 0)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL0_DISA_ON_UPD_TRIG (1u << 0)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL0_ENA_ON_UPD_TRIG  (2u << 0)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL1_NOP              (0u << 2)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL1_DISA_ON_UPD_TRIG (1u << 2)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL1_ENA_ON_UPD_TRIG  (2u << 2)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL2_NOP              (0u << 4)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL2_DISA_ON_UPD_TRIG (1u << 4)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL2_ENA_ON_UPD_TRIG  (2u << 4)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL3_NOP              (0u << 6)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL3_DISA_ON_UPD_TRIG (1u << 6)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL3_ENA_ON_UPD_TRIG  (2u << 6)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL4_NOP              (0u << 8)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL4_DISA_ON_UPD_TRIG (1u << 8)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL4_ENA_ON_UPD_TRIG  (2u << 8)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL5_NOP              (0u << 10)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL5_DISA_ON_UPD_TRIG (1u << 10)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL5_ENA_ON_UPD_TRIG  (2u << 10)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL6_NOP              (0u << 12)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL6_DISA_ON_UPD_TRIG (1u << 12)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL6_ENA_ON_UPD_TRIG  (2u << 12)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL7_NOP              (0u << 14)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL7_DISA_ON_UPD_TRIG (1u << 14)
#define GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL7_ENA_ON_UPD_TRIG  (2u << 14)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_NOP       (0u << 0)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_CHAN_DISA (1u << 0)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT0_CHAN_ENA  (2u << 0)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT1_NOP       (0u << 2)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT1_CHAN_DISA (1u << 2)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT1_CHAN_ENA  (2u << 2)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT2_NOP       (0u << 4)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT2_CHAN_DISA (1u << 4)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT2_CHAN_ENA  (2u << 4)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT3_NOP       (0u << 6)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT3_CHAN_DISA (1u << 6)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT3_CHAN_ENA  (2u << 6)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT4_NOP       (0u << 8)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT4_CHAN_DISA (1u << 8)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT4_CHAN_ENA  (2u << 8)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT5_NOP       (0u << 10)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT5_CHAN_DISA (1u << 10)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT5_CHAN_ENA  (2u << 10)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT6_NOP       (0u << 12)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT6_CHAN_DISA (1u << 12)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT6_CHAN_ENA  (2u << 12)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT7_NOP       (0u << 14)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT7_CHAN_DISA (1u << 14)
#define GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT7_CHAN_ENA  (2u << 14)

#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL0_NOP                  (0u << 0)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL0_DISA_OUT_ON_UPD_TRIG (1u << 0)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL0_ENA_OUT_ON_UPD_TRIG  (2u << 0) 
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL1_NOP                  (0u << 2)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL1_DISA_OUT_ON_UPD_TRIG (1u << 2)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL1_ENA_OUT_ON_UPD_TRIG  (2u << 2) 
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL2_NOP                  (0u << 4)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL2_DISA_OUT_ON_UPD_TRIG (1u << 4)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL2_ENA_OUT_ON_UPD_TRIG  (2u << 4) 
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL3_NOP                  (0u << 6)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL3_DISA_OUT_ON_UPD_TRIG (1u << 6)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL3_ENA_OUT_ON_UPD_TRIG  (2u << 6) 
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL4_NOP                  (0u << 8)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL4_DISA_OUT_ON_UPD_TRIG (1u << 8)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL4_ENA_OUT_ON_UPD_TRIG  (2u << 8) 
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL5_NOP                  (0u << 10)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL5_DISA_OUT_ON_UPD_TRIG (1u << 10)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL5_ENA_OUT_ON_UPD_TRIG  (2u << 10) 
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL6_NOP                  (0u << 12)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL6_DISA_OUT_ON_UPD_TRIG (1u << 12)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL6_ENA_OUT_ON_UPD_TRIG  (2u << 12) 
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL7_NOP                  (0u << 14)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL7_DISA_OUT_ON_UPD_TRIG (1u << 14)
#define GTM_TOM_OUTEN_CTRL_OUTEN_CTRL7_ENA_OUT_ON_UPD_TRIG  (2u << 14)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT0_NOP           (0u << 0)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT0_DISA_OUT_CHAN (1u << 0)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT0_ENA_OUT_CHAN  (2u << 0) 
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT1_NOP           (0u << 2)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT1_DISA_OUT_CHAN (1u << 2)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT1_ENA_OUT_CHAN  (2u << 2)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT2_NOP           (0u << 4)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT2_DISA_OUT_CHAN (1u << 4)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT2_ENA_OUT_CHAN  (2u << 4)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT3_NOP           (0u << 6)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT3_DISA_OUT_CHAN (1u << 6)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT3_ENA_OUT_CHAN  (2u << 6)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT4_NOP           (0u << 8)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT4_DISA_OUT_CHAN (1u << 8)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT4_ENA_OUT_CHAN  (2u << 8)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT5_NOP           (0u << 10)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT5_DISA_OUT_CHAN (1u << 10)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT5_ENA_OUT_CHAN  (2u << 10)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT6_NOP           (0u << 12)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT6_DISA_OUT_CHAN (1u << 12)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT6_ENA_OUT_CHAN  (2u << 12)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT7_NOP           (0u << 14)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT7_DISA_OUT_CHAN (1u << 14)
#define GTM_TOM_OUTEN_STAT_OUTEN_STAT7_ENA_OUT_CHAN  (2u << 14) 

#define EVP_u32GRP_0_SW_RST \
  ( GTM_TOM_TGC_GLB_CTRL_RST_CH1_SW_RST \
  | GTM_TOM_TGC_GLB_CTRL_RST_CH2_SW_RST)

#define EVP_u32GRP_0_UPDATE_DISABLE \
  ( GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL1_UPD_DISA \
  | GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL2_UPD_DISA )

#define EVP_u32GRP_0_UPDATE_ENABLE \
  ( GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL1_UPD_ENA \
  | GTM_TOM_TGC_GLB_CTRL_UPEN_CTRL2_UPD_ENA)
 
#define EVP_u32GRP_0_OUTEN_CTRL \
   ( GTM_TOM_OUTEN_CTRL_OUTEN_CTRL1_NOP \
   | GTM_TOM_OUTEN_CTRL_OUTEN_CTRL2_NOP)

#define EVP_u32GRP_0_OUTEN_STAT \
   ( GTM_TOM_OUTEN_STAT_OUTEN_STAT1_ENA_OUT_CHAN \
   | GTM_TOM_OUTEN_STAT_OUTEN_STAT2_ENA_OUT_CHAN )

#define EVP_u32GRP_0_ENDIS_CTRL \
   ( GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL1_NOP \
   | GTM_TOM_TGC_ENDIS_CTRL_ENDIS_CTRL2_NOP)
 
#define EVP_u32GRP_0_ENDIS_STAT_CHAN_ENA \
   ( GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT1_CHAN_ENA \
   | GTM_TOM_TGC_ENDIS_STAT_ENDIS_STAT2_CHAN_ENA)


 
#define EVP_u8GRP_0_IDX  0
#define EVP_u8TRIG_0_IDX 0
#define EVP_u8TRIG_1_IDX 0


/**********************************************************************************************************************/
/* TYPEDEF                                                                                                            */
/**********************************************************************************************************************/

typedef volatile struct
{
   Ifx_GTM_TOM_CH_CTRL CTRL;
   Ifx_GTM_TOM_CH_SR0 SR0;
   Ifx_GTM_TOM_CH_SR1 SR1;
   Ifx_GTM_TOM_CH_CN0 CN0;
} EVP_tstCfgChan;

typedef struct
{
   Ifx_GTM_TOM_TGC_TYPE * pstTgc;
   Ifx_GTM_TOM_CH_TYPE  * pstCh;
   EVP_tstCfgChan         astCfgChan[EVP_u8NB_CH_MAX_BY_GROUP];
   uint32                 u32UpdEna;
   uint32                 u32UpdDisa;
   uint8                  u8Size;
} EVP_tstGrp;


/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/
  
/******************************************************************************/
/* CONSTANTS DECLARATION                                                      */
/******************************************************************************/

#define EVP_START_SEC_CONST_UNSPECIFIED
#include "EVP_MemMap.h"
extern const EVP_tstGrp EVP_akstGrp[EVP_u8NB_GROUP];

#define EVP_STOP_SEC_CONST_UNSPECIFIED
#include "EVP_MemMap.h"

/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/


/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/

#define EVP_stCH_INIT_CFG(snChannel) M1_EVP_stCH_INIT_CFG(snChannel)

#define M1_EVP_stCH_INIT_CFG(snChannel) M2_EVP_stCH_INIT_CFG(snChannel, EVP_sn##snChannel##_TYP)
#define M2_EVP_stCH_INIT_CFG(snChannel, snType) M3_EVP_stCH_INIT_CFG(snChannel, snType)

#define M3_EVP_stCH_INIT_CFG(snChannel, snType) M1_EVP_stCH_INIT_CFG_##snType(snChannel)

#define M1_EVP_stCH_INIT_CFG_PERIOD(snChannel) \
   M2_EVP_stCH_INIT_CFG_PERIOD(EVP_u32##snChannel##_PERIOD, EVP_u32##snChannel##_DEFAULT_DUTY, EVP_u16##snChannel##_CNT_INIT)
#define M2_EVP_stCH_INIT_CFG_PERIOD(u32Period, u32Duty, u16Cnt) \
  { \
     EVP_u32TOM_CTRL_CFG_PERIOD, \
    (uint16)(((u32Period) * EVP_u16DELAY_1MICROS + 500) / 1000), \
    (uint16)(((((u32Period) * EVP_u16DELAY_1MICROS + 500) / 1000) * (u32Duty) + 50) / 100), \
    (u16Cnt)\
  }

   
#define M1_EVP_stCH_INIT_CFG_DIAG_CMD(snChannel) \
   M2_EVP_stCH_INIT_CFG_DIAG_CMD(EVP_u32##snChannel##_PERIOD, EVP_u32##snChannel##_DEFAULT_DUTY, EVP_u16##snChannel##_CNT_INIT)

#define M2_EVP_stCH_INIT_CFG_DIAG_CMD(u32Period, u32Duty, u16Cnt) \
  { \
     EVP_u32TOM_CTRL_CFG_DIAG, \
    (uint16)(((u32Period) * (100 + (u32Duty))) * EVP_u16DELAY_1MICROS),\
    (uint16)((u32Period) * (100 - ((u32Duty))) * EVP_u16DELAY_1MICROS), \
    (u16Cnt)\
  }
#define M1_EVP_stCH_INIT_CFG_PWM_CMD(snChannel) \
   M2_EVP_stCH_INIT_CFG_PWM_CMD(EVP_u32##snChannel##_PERIOD, EVP_u32##snChannel##_DEFAULT_DUTY, EVP_u16##snChannel##_CNT_INIT)
#define M2_EVP_stCH_INIT_CFG_PWM_CMD(u32Period, u32Duty, u16Cnt) \
  { \
     EVP_u32TOM_CTRL_CFG_PWM, \
    (uint16)(0),\
    (uint16)(0), \
    (u16Cnt)\
  }
#define M1_EVP_stCH_INIT_CFG_ADC_TRIG(snChannel) \
   M2_EVP_stCH_INIT_CFG_ADC_TRIG(EVP_u32##snChannel##_PERIOD, EVP_u32##snChannel##_DEFAULT_DUTY, EVP_u16##snChannel##_CNT_INIT)

#define M2_EVP_stCH_INIT_CFG_ADC_TRIG(u32Period, u32Duty, u16Cnt) \
  { \
     EVP_u32TOM_CTRL_CFG_ADC_TRIG, \
    (uint16)(((u32Period) * EVP_u16DELAY_1MICROS + 500) / 1000),\
    (uint16)(((u32Period) * EVP_u16DELAY_1MICROS + 1000) / 2000), \
    (u16Cnt)\
  }

#define M1_EVP_stCH_INIT_CFG_ADC_TRIG_0(snChannel) \
   M2_EVP_stCH_INIT_CFG_ADC_TRIG_0(EVP_u32##snChannel##_PERIOD, EVP_u32##snChannel##_DEFAULT_DUTY, EVP_u16##snChannel##_CNT_INIT)

#define M2_EVP_stCH_INIT_CFG_ADC_TRIG_0(u32Period, u32Duty, u16Cnt) \
  { \
     EVP_u32TOM_CTRL_CFG_ADC_TRIG_0, \
    (uint16)(u32Period) ,\
    (uint16)(EVP_u16DELAY_1MICROS), \
    (u16Cnt)\
  }  
  
#define M1_EVP_stCH_INIT_CFG_ADC_TRIG_1(snChannel) \
   M2_EVP_stCH_INIT_CFG_ADC_TRIG_1(EVP_u32##snChannel##_PERIOD, EVP_u32##snChannel##_DEFAULT_DUTY, EVP_u16##snChannel##_CNT_INIT)

#define M2_EVP_stCH_INIT_CFG_ADC_TRIG_1(u32Period, u32Duty, u16Cnt) \
  { \
     EVP_u32TOM_CTRL_CFG_ADC_TRIG_1, \
    (uint16)(EVP_u16DELAY_1MICROS + EVP_u16DELAY_5MICROS),\
    (uint16)(EVP_u16DELAY_1MICROS), \
    (u16Cnt)\
  }  
  
#define EVP_pstGET_TGC_PTR(snGroup) \
   (&(((*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_TGC[EVP_u8##snGroup##_TOM_IDX]).TGC[EVP_u8PERIOD_##snGroup##_CHAN / 8]))
#define EVP_pstGET_CH_PTR(snGroup)  \
   (&((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[EVP_u8##snGroup##_TOM_IDX].CH[EVP_u8PERIOD_##snGroup##_CHAN]))

#define EVP_pstGET_TGC_PTR_1(snGroup) \
   (&(((*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_TGC[EVP_u8##snGroup##_TOM_IDX]).TGC[EVP_u8ADC_##snGroup##_CHAN / 8]))
#define EVP_pstGET_CH_PTR_1(snGroup)  \
   (&((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[EVP_u8##snGroup##_TOM_IDX].CH[EVP_u8ADC_##snGroup##_CHAN]))   
/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/

#endif /* EVP_I_H */

/*-------------------------------- end of file -------------------------------*/
