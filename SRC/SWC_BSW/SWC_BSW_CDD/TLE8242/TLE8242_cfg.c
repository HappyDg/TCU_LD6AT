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

#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
TLE8242_Tx TLE8242_au32SpiTx[NUMBER_OF_TLE8242] = {
//TLE8242_Tx
        {
                { .bits.MsgID = ICVersionManufacturer_MSG_ID, .bits.r_w = 1, },
                { .bits.MsgID = ControlMethodandFaultMaskConfiguration_MSG_ID, .bits.r_w = 1, .bits.CM=ControlModeData, .bits.DIAG_TMR=DiagTimerDiv128_1},
                {
                    { .bits.MsgID = DiagnosticConfigurationchannel0_3_MSG_ID, .bits.r_w = 1, },
                    { .bits.MsgID = DiagnosticConfigurationchannel4_7_MSG_ID, .bits.r_w = 1, }
                },
                {
                    { .bits.MsgID = DiagnosticReadchannel0_3_MSG_ID, .bits.r_w = 1, },
                    { .bits.MsgID = DiagnosticReadchannel4_7_MSG_ID, .bits.r_w = 1, }
                },

                    { .bits.MsgID = PWMOffsetchannel0_3_MSG_ID, .bits.r_w = 1, .bits.OFFSET0 = 0, .bits.OFFSET1=4, .bits.OFFSET2=9, .bits.OFFSET3=13},
                    { .bits.MsgID = PWMOffsetchannel4_7_MSG_ID, .bits.r_w = 1, .bits.OFFSET4 = 17, .bits.OFFSET5=21, .bits.OFFSET6=25, .bits.OFFSET7=29},

                {
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=0},
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=1},
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=2},
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=3},
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=4},
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=5},
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=6},
                    { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=7}
                },
                {
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=0},
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=1},
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=2},
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=3},
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=4},
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=5},
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=6},
                    { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=7}
                },
                {

                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=0},
                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=1},
                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=2},
                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=3},
                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=4},
                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=5},
                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=6},
                    { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=7}
                },
                {
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=0},
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=1},
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=2},
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=3},
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=4},
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=5},
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=6},
                    { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=7}
                },
                {
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                    { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                },
                {
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                    { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                },
                {
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                    { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                },
                {
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                    { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                },
                {
                    { .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=0 },
					{ .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=1 },
					{ .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=2 },
					{ .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=3 },
					{ .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=4 },
					{ .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=5 },
					{ .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=6 },
					{ .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 1,.bits.Chan=7 }
                },
                {
                    { .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=0 },
					{ .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=1 },
					{ .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=2 },
					{ .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=3 },
					{ .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=4 },
					{ .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=5 },
					{ .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=6 },
					{ .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 1, .bits.Chan=7 }
                },
                {
                    { .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=0 },
					{ .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=1 },
					{ .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=2 },
					{ .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=3 },
					{ .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=4 },
					{ .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=5 },
					{ .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=6 },
					{ .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, .bits.Chan=7 }
                },
                { .bits.MsgID = ReadGenericFlagBits_MSG_ID, .bits.r_w = 0,}
        }
#if NUMBER_OF_TLE8242 > 1
        ,          {
                        { .bits.MsgID = ICVersionManufacturer_MSG_ID, .bits.r_w = 1, },
                        { .bits.MsgID = ControlMethodandFaultMaskConfiguration_MSG_ID, .bits.r_w = 1, .bits.CM=ControlModeData, .bits.DIAG_TMR=DiagTimerDiv128_1},
                        {
                            { .bits.MsgID = DiagnosticConfigurationchannel0_3_MSG_ID, .bits.r_w = 1, },
                            { .bits.MsgID = DiagnosticConfigurationchannel4_7_MSG_ID, .bits.r_w = 1, }
                        },
                        {
                            { .bits.MsgID = DiagnosticReadchannel0_3_MSG_ID, .bits.r_w = 1, },
                            { .bits.MsgID = DiagnosticReadchannel4_7_MSG_ID, .bits.r_w = 1, }
                        },

                            { .bits.MsgID = PWMOffsetchannel0_3_MSG_ID, .bits.r_w = 1, .bits.OFFSET0 = 0, .bits.OFFSET1=4, .bits.OFFSET2=9, .bits.OFFSET3=13},
                            { .bits.MsgID = PWMOffsetchannel4_7_MSG_ID, .bits.r_w = 1, .bits.OFFSET4 = 17, .bits.OFFSET5=21, .bits.OFFSET6=25, .bits.OFFSET7=29},

                        {
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=0},
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=1},
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=2},
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=3},
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=4},
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=5},
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=6},
                            { .bits.MsgID = MainPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=7}
                        },
                        {
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=0},
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=1},
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=2},
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=3},
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=4},
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=5},
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=6},
                            { .bits.MsgID = ControlVariableSetKPandKI_MSG_ID, .bits.r_w = 1,  .bits.Chan=7}
                        },
                        {

                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=0},
                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=1},
                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=2},
                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=3},
                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=4},
                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=5},
                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=6},
                            { .bits.MsgID = CurrentandDitherAmplitudeSet_MSG_ID, .bits.r_w = 1, .bits.Chan=7}
                        },
                        {
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=0},
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=1},
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=2},
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=3},
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=4},
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=5},
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=6},
                            { .bits.MsgID = DitherPeriodSet_MSG_ID, .bits.r_w = 1, .bits.Chan=7}
                        },
                        {
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                            { .bits.MsgID = MaxMinCurrentRead_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                        },
                        {
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                            { .bits.MsgID = AverageCurrentReadOverDitherPeriod_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                        },
                        {
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                            { .bits.MsgID = AutozeroTriggerRead_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                        },
                        {
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=0},
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=1},
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=2},
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=3},
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=4},
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=5},
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=6},
                            { .bits.MsgID = PWMDutyCycle_MSG_ID, .bits.r_w = 0, .bits.Chan=7}
                        },
                        {
                        { .bits.MsgID = CurrentProfileDetectionSetup1_MSG_ID, .bits.r_w = 0, }
                        },
                        {
                        { .bits.MsgID = CurrentProfileDetectionSetup2_MSG_ID, .bits.r_w = 0, },
                        },
                        {
                        { .bits.MsgID = CurrentProfileDetectionFeedback_MSG_ID, .bits.r_w = 0, },
                        },
                        { .bits.MsgID = ReadGenericFlagBits_MSG_ID, .bits.r_w = 0,}
                }
#endif
}
;

TLE8242_Rx TLE8242_au32SpiRx[NUMBER_OF_TLE8242] ;
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
const Tle8242DummyMsgID TLE8242_au32DiagTxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_DIAG_CHANNEL_1] =
                {

                                {
                                                //
                                                {.bits.MsgID = DiagnosticReadchannel0_3_MSG_ID, .bits.r_w = 0},
                                                {.bits.MsgID = DiagnosticReadchannel4_7_MSG_ID, .bits.r_w = 0},
                                                {.bits.MsgID = ReadGenericFlagBits_MSG_ID<<3, .bits.r_w = 0}

                                },
#if NUMBER_OF_TLE8242 > 1
                                {
                                                //
                                                {.bits.MsgID = DiagnosticReadchannel0_3_MSG_ID, .bits.r_w = 0},
                                                {.bits.MsgID = DiagnosticReadchannel4_7_MSG_ID, .bits.r_w = 0},
                                                {.bits.MsgID = ReadGenericFlagBits_MSG_ID<<3, .bits.r_w = 0}

                                }
#endif
                };

#define TLE8242_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
Tle8242DummyMsgID TLE8242_au32CtrlTxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_CTRL_CHANNEL_1];
Tle8242DummyMsgID TLE8242_au32InitTxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_INIT_CHANNEL_1];

Tle8242DummyMsgID TLE8242_au32DiagRxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_DIAG_CHANNEL_1];
Tle8242DummyMsgID TLE8242_au32CtrlRxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_CTRL_CHANNEL_1];
Tle8242DummyMsgID TLE8242_au32InitRxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_INIT_CHANNEL_1];
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
const uint8 TLE8242_au8_channel_buff_deepth_cfg[NUMBER_OF_TLE8242*3]=
{
                //TLE8242_1_INIT_CH
                MAX_FRAME_NUM_OF_INIT_CHANNEL_1,
#if NUMBER_OF_TLE8242 > 1
                //TLE8242_2_INIT_CH
                MAX_FRAME_NUM_OF_INIT_CHANNEL_2,
#endif
//TLE8242_1_CTRL_CH
                MAX_FRAME_NUM_OF_CTRL_CHANNEL_1,
#if NUMBER_OF_TLE8242 > 1
                //TLE8242_2_CTRL_CH
                MAX_FRAME_NUM_OF_CTRL_CHANNEL_2,
#endif
                //TLE8242_1_DIAG_CH
                MAX_FRAME_NUM_OF_DIAG_CHANNEL_1,
#if NUMBER_OF_TLE8242 > 1
                //TLE8242_2_DIAG_CH
                MAX_FRAME_NUM_OF_DIAG_CHANNEL_2

#endif
};


const uint8 TLE8242_au8ChanNumPerChip[NUMBER_OF_TLE8242] = {
                8,
#if NUMBER_OF_TLE8242 > 1
        7
#endif
                };

#define TLE8242_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

