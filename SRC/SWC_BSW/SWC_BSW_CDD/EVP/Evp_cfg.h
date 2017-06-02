/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : EVP                                                                                             */
/*                                                                                                                    */
/* !Component       : EVP                                                                                             */
/* !Description     : EVP unit                                                                                        */
/*                                                                                                                    */
/* !Module          : EVP_CFG                                                                                         */
/* !Description     : Configuration of EVP unit                                                                       */
/*                                                                                                                    */
/* !File            : EVP_Cfg.h                                                                                       */
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

#ifndef EVP_CFG_H
#define EVP_CFG_H

#include "Std_Types.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
#define EVP_snM_SOLENOID_HS_DEN_2_TOUT               TOUT20
#define EVP_snM_CLUTCH_1_VALVE_CMD_TOUT              TOUT21
#define EVP_snM_BRAKE_3_VALVE_CMD_TOUT               TOUT102
#define EVP_snM_TORQ_CONV_LOCK_CLUTCH_VALVE_CMD_TOUT TOUT110
#define EVP_snM_SOLENOID_HS_DEN_3_TOUT               TOUT10
#define EVP_snM_CLUTCH_2_VALVE_CMD_TOUT              TOUT12
#define EVP_snM_BRAKE_2_VALVE_CMD_TOUT               TOUT13
#define EVP_snM_LINE_PRS_VALVE_CMD_TOUT              TOUT14
#define EVP_snM_SOLENOID_HS_DEN_1_TOUT               TOUT71
#define EVP_snM_RETARDER_CTRL_VALVE_CMD_TOUT         TOUT39
#define EVP_snM_AUXILIARIES_VALVE_CMD_TOUT           TOUT41
#define EVP_snM_SOLENOID_HS_DEN_4_TOUT               TOUT2
#define EVP_snM_BRAKE_1_VALVE_CMD_TOUT	              TOUT3
#define EVP_snM_BRAKE_4_VALVE_CMD_TOUT	              TOUT4

#define EVP_snM_SOLENOID_HS_DEN_2_TIMER               TIMER_A
#define EVP_snM_CLUTCH_1_VALVE_CMD_TIMER              TIMER_A
#define EVP_snM_BRAKE_3_VALVE_CMD_TIMER               TIMER_A
#define EVP_snM_TORQ_CONV_LOCK_CLUTCH_VALVE_CMD_TIMER TIMER_A
#define EVP_snM_SOLENOID_HS_DEN_3_TIMER               TIMER_A
#define EVP_snM_CLUTCH_2_VALVE_CMD_TIMER              TIMER_A
#define EVP_snM_BRAKE_2_VALVE_CMD_TIMER               TIMER_A
#define EVP_snM_LINE_PRS_VALVE_CMD_TIMER              TIMER_A
#define EVP_snM_SOLENOID_HS_DEN_1_TIMER               TIMER_A
#define EVP_snM_RETARDER_CTRL_VALVE_CMD_TIMER         TIMER_B
#define EVP_snM_AUXILIARIES_VALVE_CMD_TIMER           TIMER_B
#define EVP_snM_SOLENOID_HS_DEN_4_TIMER               TIMER_B
#define EVP_snM_BRAKE_1_VALVE_CMD_TIMER               TIMER_B
#define EVP_snM_BRAKE_4_VALVE_CMD_TIMER               TIMER_B

#define EVP_u8TIMER_A_IDX 0
#define EVP_u8TIMER_B_IDX 1
#define EVP_u8TIMER_C_IDX 2
#define EVP_u8TIMER_D_IDX 3

#define EVP_u8TOUT0_IDX 0
#define EVP_u8TOUT1_IDX 1
#define EVP_u8TOUT2_IDX 2
#define EVP_u8TOUT3_IDX 3
#define EVP_u8TOUT4_IDX 4
#define EVP_u8TOUT5_IDX 5
#define EVP_u8TOUT6_IDX 6
#define EVP_u8TOUT7_IDX 7
#define EVP_u8TOUT8_IDX 8
#define EVP_u8TOUT9_IDX 9
#define EVP_u8TOUT10_IDX 10
#define EVP_u8TOUT11_IDX 11
#define EVP_u8TOUT12_IDX 12
#define EVP_u8TOUT13_IDX 13
#define EVP_u8TOUT14_IDX 14
#define EVP_u8TOUT15_IDX 15
#define EVP_u8TOUT16_IDX 16
#define EVP_u8TOUT17_IDX 17
#define EVP_u8TOUT18_IDX 18
#define EVP_u8TOUT19_IDX 19
#define EVP_u8TOUT20_IDX 20
#define EVP_u8TOUT21_IDX 21
#define EVP_u8TOUT22_IDX 22
#define EVP_u8TOUT23_IDX 23
#define EVP_u8TOUT24_IDX 24
#define EVP_u8TOUT25_IDX 25
#define EVP_u8TOUT26_IDX 26
#define EVP_u8TOUT27_IDX 27
#define EVP_u8TOUT28_IDX 28
#define EVP_u8TOUT29_IDX 29
#define EVP_u8TOUT30_IDX 30
#define EVP_u8TOUT31_IDX 31
#define EVP_u8TOUT32_IDX 32
#define EVP_u8TOUT33_IDX 33
#define EVP_u8TOUT34_IDX 34
#define EVP_u8TOUT35_IDX 35
#define EVP_u8TOUT36_IDX 36
#define EVP_u8TOUT37_IDX 37
#define EVP_u8TOUT38_IDX 38
#define EVP_u8TOUT39_IDX 39
#define EVP_u8TOUT40_IDX 40
#define EVP_u8TOUT41_IDX 41
#define EVP_u8TOUT42_IDX 42
#define EVP_u8TOUT43_IDX 43
#define EVP_u8TOUT44_IDX 44
#define EVP_u8TOUT45_IDX 45
#define EVP_u8TOUT46_IDX 46
#define EVP_u8TOUT47_IDX 47
#define EVP_u8TOUT48_IDX 48
#define EVP_u8TOUT49_IDX 49
#define EVP_u8TOUT50_IDX 50
#define EVP_u8TOUT51_IDX 51
#define EVP_u8TOUT52_IDX 52
#define EVP_u8TOUT53_IDX 53
#define EVP_u8TOUT54_IDX 54
#define EVP_u8TOUT55_IDX 55
#define EVP_u8TOUT56_IDX 56
#define EVP_u8TOUT57_IDX 57
#define EVP_u8TOUT58_IDX 58
#define EVP_u8TOUT59_IDX 59
#define EVP_u8TOUT60_IDX 60
#define EVP_u8TOUT61_IDX 61
#define EVP_u8TOUT62_IDX 62
#define EVP_u8TOUT63_IDX 63
#define EVP_u8TOUT64_IDX 64
#define EVP_u8TOUT65_IDX 65
#define EVP_u8TOUT66_IDX 66
#define EVP_u8TOUT67_IDX 67
#define EVP_u8TOUT68_IDX 68
#define EVP_u8TOUT69_IDX 69
#define EVP_u8TOUT70_IDX 70
#define EVP_u8TOUT71_IDX 71
#define EVP_u8TOUT72_IDX 72
#define EVP_u8TOUT73_IDX 73
#define EVP_u8TOUT74_IDX 74
#define EVP_u8TOUT75_IDX 75
#define EVP_u8TOUT76_IDX 76
#define EVP_u8TOUT77_IDX 77
#define EVP_u8TOUT78_IDX 78
#define EVP_u8TOUT79_IDX 79
#define EVP_u8TOUT80_IDX 80
#define EVP_u8TOUT81_IDX 81
#define EVP_u8TOUT82_IDX 82
#define EVP_u8TOUT83_IDX 83
#define EVP_u8TOUT84_IDX 84
#define EVP_u8TOUT85_IDX 85
#define EVP_u8TOUT86_IDX 86
#define EVP_u8TOUT87_IDX 87
#define EVP_u8TOUT88_IDX 88
#define EVP_u8TOUT89_IDX 89
#define EVP_u8TOUT90_IDX 90
#define EVP_u8TOUT91_IDX 91
#define EVP_u8TOUT92_IDX 92
#define EVP_u8TOUT93_IDX 93
#define EVP_u8TOUT94_IDX 94
#define EVP_u8TOUT95_IDX 95
#define EVP_u8TOUT96_IDX 96
#define EVP_u8TOUT97_IDX 97
#define EVP_u8TOUT98_IDX 98
#define EVP_u8TOUT99_IDX 99
#define EVP_u8TOUT100_IDX 100
#define EVP_u8TOUT101_IDX 101
#define EVP_u8TOUT102_IDX 102
#define EVP_u8TOUT103_IDX 103
#define EVP_u8TOUT104_IDX 104
#define EVP_u8TOUT105_IDX 105
#define EVP_u8TOUT106_IDX 106
#define EVP_u8TOUT107_IDX 107
#define EVP_u8TOUT108_IDX 108
#define EVP_u8TOUT109_IDX 109
#define EVP_u8TOUT110_IDX 110
#define EVP_u8TOUT111_IDX 111
#define EVP_u8TOUT112_IDX 112
#define EVP_u8TOUT113_IDX 113
#define EVP_u8TOUT114_IDX 114
#define EVP_u8TOUT115_IDX 115
#define EVP_u8TOUT116_IDX 116
#define EVP_u8TOUT117_IDX 117
#define EVP_u8TOUT118_IDX 118
#define EVP_u8TOUT119_IDX 119
#define EVP_u8TOUT120_IDX 120

#define EVP_vidSET_OUT_CFG(snChannel) \
   M1_EVP_vidSET_OUT_CFG(EVP_sn##snChannel##_TOUT, EVP_sn##snChannel##_TIMER)
#define M1_EVP_vidSET_OUT_CFG(snTout, snTimer) M2_EVP_vidSET_OUT_CFG(snTout, snTimer)

#define M2_EVP_vidSET_OUT_CFG(snTout, snTimer) M3_EVP_vidSET_OUT_CFG(EVP_u8##snTout##_IDX / 16, EVP_u8##snTout##_IDX % 16, EVP_u8##snTimer##_IDX)

#define M3_EVP_vidSET_OUT_CFG(u8Idx, u8Pos, u8Timer) M4_EVP_vidSET_OUT_CFG(u8Idx, u8Pos, u8Timer)

#define M4_EVP_vidSET_OUT_CFG(u8Idx, u8Pos, u8Timer) \
 MODULE_GTM.INOUTSEL.T.OUTSEL[u8Idx].U = (MODULE_GTM.INOUTSEL.T.OUTSEL[u8Idx].U & (~(3u << ((u8Pos) * 2)))) | ((u8Timer) << ((u8Pos) * 2))

/* GROUPE 0 */
#define EVP_u8PERIOD_GRP_0_CHAN                     EVP_u8ADC_TRIG_0_CHAN
#define EVP_snPERIOD_GRP_0_GRP                      GRP_0
#define EVP_u32PERIOD_GRP_0_PERIOD                  (EVP_u32ADC_TRIG_0_PERIOD)

#define EVP_u8ADC_TRIG_0_CHAN                   1
#define EVP_snADC_TRIG_0_GRP                    GRP_0
#define EVP_u32ADC_TRIG_0_DEFAULT_DUTY          50
#define EVP_snADC_TRIG_0_TYP                    ADC_TRIG_0
#define EVP_u16ADC_TRIG_0_CNT_INIT              0
#define EVP_u32ADC_TRIG_0_PERIOD                4000

#define EVP_u8ADC_TRIG_1_CHAN                   2
#define EVP_snADC_TRIG_1_GRP                    GRP_0
#define EVP_u32ADC_TRIG_1_DEFAULT_DUTY          50
#define EVP_snADC_TRIG_1_TYP                    ADC_TRIG_1
#define EVP_u16ADC_TRIG_1_CNT_INIT              0
#define EVP_u32ADC_TRIG_1_PERIOD                EVP_u32ADC_TRIG_0_PERIOD



#define EVP_u32GRP_0_SIZE 2

#define EVP_u32GRP_SIZE_MAX 3

#define EVP_u16PRD_MIN (200 * EVP_u16DELAY_1MICROS) 
#define EVP_u16PRD_MAX (655 * EVP_u16DELAY_1MICROS)


/**********************************************************************************************************************/
/* TYPEDEF                                                                                                            */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/


#endif /* EVP_CFG_H */

/*-------------------------------- end of file -------------------------------*/
