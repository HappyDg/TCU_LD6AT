/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           :                                                                                            */
/*                                                                                                                    */
/* !Component       :                                                                                             */
/* !Description     :     unit                                                                                    */
/*                                                                                                                    */
/* !Module          :                                                                                             */
/* !Description     :                                                                           */
/*                                                                                                                    */
/* !File            : TLE8242_cfg.c                                                                                  */
/*                                                                                                                    */
/* !Target          :                                                                                      */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* 1 /                                                                                    */
/* 2 /                                                                                        */
/* 3 /                                                                                           */
/* 4 /                                                                                           */
/* 5 /                                                                                          */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* Archive::                        */
/* Revision::   0.1                                                                                                */
/* Author::   gsun5                               Date::   Jan 16, 2017                               */
/**********************************************************************************************************************/

#include "TLE8242_cfg.h"
#include "TLE8242_interface.h"


#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
TLE8242_Tx TLE8242_astSpiTx[TLE8242_u8CH_NR]  = {
//TLE8242_Tx
        {
                { .bits.udtMsgID = TLE8242_u8_IC_VERS_MSG_ID, .bits.bRW = 1, },
                { .bits.udtMsgID = TLE8242_u8_CTRL_MOD_FLT_MASK_MSG_ID, .bits.bRW = 1, .bits.udtCM=ControlModeData, .bits.udtDIAG_TMR=TLE8242_DIAG_TMR_DIV_128_1},
                {
                    { .bits.udtMsgID = TLE8242_u8_DIAGC_CFG_03_MSG_ID, .bits.bRW = 1, },
                    { .bits.udtMsgID = TLE8242_u8_DIAGC_CFG_47_MSG_ID, .bits.bRW = 1, }
                },
                {
                    { .bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_03_MSG_ID, .bits.bRW = 1, },
                    { .bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_47_MSG_ID, .bits.bRW = 1, }
                },

                    { .bits.udtMsgID = TLE8242_u8_PWM_OFFS_03_MSG_ID, .bits.bRW = 1, .bits.OFFSET0 = 0, .bits.OFFSET1=4, .bits.OFFSET2=9, .bits.OFFSET3=13},
                    { .bits.udtMsgID = TLE8242_u8_PWM_OFFS_47_MSG_ID, .bits.bRW = 1, .bits.OFFSET4 = 17, .bits.OFFSET5=21, .bits.OFFSET6=25, .bits.OFFSET7=29},

                {
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=7}
                },
                {
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=7}
                },
                {

                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=7}
                },
                {
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=7}
                },
                {
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                },
                {
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                },
                {
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                },
                {
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                    { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                },
                {
                { .bits.udtMsgID = TLE8242_u8_CRNT_PROF_DETN_MSG_ID, .bits.bRW = 0, }
                },
                {
                { .bits.udtMsgID = TLE8242_u8_CRNT_PROF_DETN_1_MSG_ID, .bits.bRW = 0, },
                },
                {
                { .bits.udtMsgID = TLE8242_u8_CRNT_PROF_DETN_FB_MSG_ID, .bits.bRW = 0, },
                },
                { .bits.udtMsgID = TLE8242_u8_READ_GEN_FLG_MSG_ID, .bits.bRW = 0,}
        }
#if TLE8242_u8CH_NR > 1
        ,          {
                        { .bits.udtMsgID = TLE8242_u8_IC_VERS_MSG_ID, .bits.bRW = 1, },
                        { .bits.udtMsgID = TLE8242_u8_CTRL_MOD_FLT_MASK_MSG_ID, .bits.bRW = 1, .bits.udtCM=ControlModeData, .bits.udtDIAG_TMR=TLE8242_DIAG_TMR_DIV_128_1},
                        {
                            { .bits.udtMsgID = TLE8242_u8_DIAGC_CFG_03_MSG_ID, .bits.bRW = 1, },
                            { .bits.udtMsgID = TLE8242_u8_DIAGC_CFG_47_MSG_ID, .bits.bRW = 1, }
                        },
                        {
                            { .bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_03_MSG_ID, .bits.bRW = 1, },
                            { .bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_47_MSG_ID, .bits.bRW = 1, }
                        },

                            { .bits.udtMsgID = TLE8242_u8_PWM_OFFS_03_MSG_ID, .bits.bRW = 1, .bits.OFFSET0 = 0, .bits.OFFSET1=4, .bits.OFFSET2=9, .bits.OFFSET3=13},
                            { .bits.udtMsgID = TLE8242_u8_PWM_OFFS_47_MSG_ID, .bits.bRW = 1, .bits.OFFSET4 = 17, .bits.OFFSET5=21, .bits.OFFSET6=25, .bits.OFFSET7=29},

                        {
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_MAI_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=7}
                        },
                        {
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_KP_KI_MSG_ID, .bits.bRW = 1,  .bits.udtChan=7}
                        },
                        {

                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_CRNT_DITHER_MSG_ID, .bits.bRW = 1, .bits.udtChan=7}
                        },
                        {
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_DITHER_PERD_MSG_ID, .bits.bRW = 1, .bits.udtChan=7}
                        },
                        {
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                        },
                        {
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_AVRG_CRNT_READ_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                        },
                        {
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_ATUO_ZERO_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                        },
                        {
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=0},
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=1},
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=2},
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=3},
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=4},
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=5},
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=6},
                            { .bits.udtMsgID = TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID, .bits.bRW = 0, .bits.udtChan=7}
                        },
                        {
                        { .bits.udtMsgID = TLE8242_u8_CRNT_PROF_DETN_MSG_ID, .bits.bRW = 0, }
                        },
                        {
                        { .bits.udtMsgID = TLE8242_u8_CRNT_PROF_DETN_1_MSG_ID, .bits.bRW = 0, },
                        },
                        {
                        { .bits.udtMsgID = TLE8242_u8_CRNT_PROF_DETN_FB_MSG_ID, .bits.bRW = 0, },
                        },
                        { .bits.udtMsgID = TLE8242_u8_READ_GEN_FLG_MSG_ID, .bits.bRW = 0,}
                }
#endif
}
;

TLE8242_Rx TLE8242_astSpiRx[TLE8242_u8CH_NR] ;



TLE8242_DummyMsgID TLE8242_astCtrlTxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_CTRL_CH_1];
TLE8242_DummyMsgID TLE8242_astInitTxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_INIT_CH_1];

TLE8242_DummyMsgID TLE8242_astDiagRxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_DIAG_CH_1];
TLE8242_DummyMsgID TLE8242_astCtrlRxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_CTRL_CH_1];
TLE8242_DummyMsgID TLE8242_astInitRxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_INIT_CH_1];

#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

const TLE8242_DummyMsgID TLE8242_kastDiagTxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_DIAG_CH_1] =
                {

                                {
                                                //
                                                {.bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_03_MSG_ID, .bits.bRW = 0},
                                                {.bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_47_MSG_ID, .bits.bRW = 0},
                                                {.bits.udtMsgID = TLE8242_u8_READ_GEN_FLG_MSG_ID<<3, .bits.bRW = 0}

                                },
#if TLE8242_u8CH_NR > 1
                                {
                                                //
                                                {.bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_03_MSG_ID, .bits.bRW = 0},
                                                {.bits.udtMsgID = TLE8242_u8_DIAGC_READ_CH_47_MSG_ID, .bits.bRW = 0},
                                                {.bits.udtMsgID = TLE8242_u8_READ_GEN_FLG_MSG_ID<<3, .bits.bRW = 0}

                                }
#endif
                };


const uint8 TLE8242_kau8ChBufSizeCfg[TLE8242_u8CH_NR*3]=
{
                //TLE8242_1_INIT_CH
                TLE8242_u8MAX_FRM_INIT_CH_1,
#if TLE8242_u8CH_NR > 1
                //TLE8242_2_INIT_CH
                TLE8242_u8MAX_FRM_INIT_CH_2,
#endif
//TLE8242_1_CTRL_CH
                TLE8242_u8MAX_FRM_CTRL_CH_1,
#if TLE8242_u8CH_NR > 1
                //TLE8242_2_CTRL_CH
                TLE8242_u8MAX_FRM_CTRL_CH_2,
#endif
                //TLE8242_1_DIAG_CH
                TLE8242_u8MAX_FRM_DIAG_CH_1,
#if TLE8242_u8CH_NR > 1
                //TLE8242_2_DIAG_CH
                TLE8242_u8MAX_FRM_DIAG_CH_2

#endif
};


const uint8 TLE8242_kau8ChNrPerChip[TLE8242_u8CH_NR] = {
                8,
#if TLE8242_u8CH_NR > 1
        7
#endif
                };
const TLE8242_tstFltCfg_s TLE8242_tstFltDev=
{
		{
				TLE8242_bGetChGenFlt,
				TLE8242_bGetChOpenLoadFlt,
				TLE8242_bGetChOverLoadFlt,
				TLE8242_bGetChUnderLoadFlt,
				TLE8242_bGetScFlt,
				TLE8242_bGetScsFlt
		},
		{
				TLE8242_stDECL_FLT(C4_SOL, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT),
				TLE8242_stDECL_FLT(C3_SOL, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT),
				TLE8242_stDECL_FLT(C2_SOL, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT),
				TLE8242_stDECL_FLT(C1_SOL, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT),
				TLE8242_stDECL_FLT(B1_SOL, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT),
				TLE8242_stDECL_FLT(RES_SOL, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT),
				TLE8242_stDECL_FLT(PRI_OIL, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT),
				TLE8242_stDECL_FLT(TC_LOCK, GENERAL_FAULT, OPEN, OVERLOAD, UNDERLOAD, SHORT_TO_GND, SHORT_TO_BATT)

		}

}; 


#define TLE8242_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

