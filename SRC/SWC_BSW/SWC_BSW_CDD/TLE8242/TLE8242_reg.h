/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : TLE8242                                                                                           */
/*                                                                                                                    */
/* !Component       : TLE8242                                                                                           */
/* !Description     : TLE8242_reg    unit                                                                                    */
/*                                                                                                                    */
/* !Module          : TLE8242                                                                                           */
/* !Description     : TLE8242 register definition file                                                                          */
/*                                                                                                                    */
/* !File            : TLE8242_reg.h                                                                                  */
/*                                                                                                                    */
/* !Target          : IFX Tc27                                                                                     */
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
/* Author::   gsun5                               Date::   Jan 10, 2017                               */
/**********************************************************************************************************************/
#ifndef TLE8242_reg_h
#define TLE8242_reg_h
#include "std_types.h"

#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
typedef union
{
        struct
        {
                uint32 unused :24;
                const uint32 MsgID :7;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} ICVersionManufacturerTx;
typedef union
{
        struct
        {
                uint32 unused :8;
                uint32 VersionNumber :8;
                uint32 ICManufID :8;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
} ICVersionManufacturerRx;
typedef union
{
        struct
        {
                uint32 unused :4;
                uint32 DIAG_TMR :2;
                uint32 FME :1;
                uint32 FMR :1;
                uint32 FM :8;
                uint32 CM :8;
                const uint32 MsgID :7;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} ControlMethodandFaultMaskConfigurationTx;
typedef union
{
        struct
        {
                uint32 unused :4;
                uint32 DIAG_TMR :2;
                uint32 FME :1;
                uint32 FMR :1;
                uint32 FM :8;
                uint32 CM :8;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
} ControlMethodandFaultMaskConfigurationRx;
typedef union
{
        struct
        {
                uint32 SB_RETRY3 :4;
                uint32 SB3 :2;
                uint32 SB_RETRY2 :4;
                uint32 SB2 :2;
                uint32 SB_RETRY1 :4;
                uint32 SB1 :2;
                uint32 SB_RETRY0 :4;
                uint32 SB0 :2;
                const uint32 MsgID :7;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} DiagnosticConfigurationchannelTx;
typedef union
{
        struct
        {
                uint32 SB_RETRY3 :4;
                uint32 SB3 :2;
                uint32 SB_RETRY2 :4;
                uint32 SB2 :2;
                uint32 SB_RETRY1 :4;
                uint32 SB1 :2;
                uint32 SB_RETRY0 :4;
                uint32 SB0 :2;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
} DiagnosticConfigurationchannelRx;
typedef union
{
        struct
        {
                uint32 SB_RETRY7 :4;
                uint32 SB7 :2;
                uint32 SB_RETRY6 :4;
                uint32 SB6 :2;
                uint32 SB_RETRY5 :4;
                uint32 SB5 :2;
                uint32 SB_RETRY4 :4;
                uint32 SB4 :2;
                const uint32 MsgID :7;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} DiagnosticConfigurationchannel4_7Tx;
typedef union
{
        struct
        {
                uint32 SB_RETRY3 :4;
                uint32 SB7 :2;
                uint32 SB_RETRY6 :4;
                uint32 SB6 :2;
                uint32 SB_RETRY5 :4;
                uint32 SB5 :2;
                uint32 SB_RETRY4 :4;
                uint32 SB4 :2;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
} DiagnosticConfigurationchannel4_7Rx;
typedef union
{
        struct
        {
                uint32 unused :24;
                const uint32 MsgID :7;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} DiagnosticReadchannelTx;
typedef union
{

        struct
        {
                uint32 OL_ON3 :1;
                uint32 OL_OFF3 :1;
                uint32 SB_TST3 :1;
                uint32 SB3 :1;
                uint32 OFF_TST3 :1;
                uint32 SG3 :1;
                uint32 OL_ON2 :1;
                uint32 OL_OFF2 :1;
                uint32 SB_TST2 :1;
                uint32 SB2 :1;
                uint32 OFF_TST2 :1;
                uint32 SG2 :1;
                uint32 OL_ON1 :1;
                uint32 OL_OFF1 :1;
                uint32 SB_TST1 :1;
                uint32 SB1 :1;
                uint32 OFF_TST1 :1;
                uint32 SG1 :1;
                uint32 OL_ON0 :1;
                uint32 OL_OFF0 :1;
                uint32 SB_TST0 :1;
                uint32 SB0 :1;
                uint32 OFF_TST0 :1;
                uint32 SG0 :1;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
}DiagnosticReadchannelRx;

typedef union
{
        struct
        {
                uint32 OFFSET3 :5;
                uint32 OFFSET2 :5;
                uint32 OFFSET1 :5;
                uint32 OFFSET0 :5;
                uint32 unused :4;
                const uint32 MsgID :7;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} PWMOffsetchannel0_3Tx;
typedef union
{
        struct
        {
                uint32 OFFSET3 :5;
                uint32 OFFSET2 :5;
                uint32 OFFSET1 :5;
                uint32 OFFSET0 :5;
                uint32 unused :4;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
} PWMOffsetchannel0_3Rx;
typedef union
{
        struct
        {
                uint32 OFFSET7 :5;
                uint32 OFFSET6 :5;
                uint32 OFFSET5 :5;
                uint32 OFFSET4 :5;
                uint32 unused :4;
                const uint32 MsgID :7;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} PWMOffsetchannel4_7Tx;
typedef union
{
        struct
        {
                uint32 OFFSET7 :5;
                uint32 OFFSET6 :5;
                uint32 OFFSET5 :5;
                uint32 OFFSET4 :5;
                uint32 unused :4;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
} PWMOffsetchannel4_7Rx;
typedef union
{
        struct
        {
                uint32 DividerN :14;
                uint32 DividerM :2;
                uint32 SAM :1;
                uint32 unused :7;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} MainPeriodSetTx;
typedef union
{
        struct
        {
                uint32 DividerN :14;
                uint32 DividerM :2;
                uint32 SAM :1;
                uint32 unused :7;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} MainPeriodSetRx;
typedef union
{
        struct
        {
                uint32 ki :12;
                uint32 kp :12;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} ControlVariableSetKPandKITx;
typedef union
{
        struct
        {
                uint32 ki :12;
                uint32 kp :12;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} ControlVariableSetKPandKIRx;
typedef union
{
        struct
        {
                uint32 Currentsetpoint :11;

                uint32 Ditherstepsize :11;
                uint32 unused :1;
                uint32 EN :1;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentandDitherAmplitudeSetTx;
typedef union
{
        struct
        {
                uint32 Currentsetpoint :11;

                uint32 Ditherstepsize :11;
                uint32 unused :1;
                uint32 EN :1;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentandDitherAmplitudeSetRx;
typedef union
{
        struct
        {
                uint32 Numberofsteps :5;
                uint32 unused :19;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} DitherPeriodSetTx;
typedef union
{
        struct
        {
                uint32 Numberofsteps :5;
                uint32 unused :19;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} DitherPeriodSetRx;
typedef union
{
        struct
        {
                uint32 unused :24;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} MaxMinCurrentReadTx;
typedef union
{
        struct
        {
                uint32 Min :11;
                uint32 Max :11;
                uint32 Valid :1;
                uint32 unused :1;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} MaxMinCurrentReadRx;
typedef union
{
        struct
        {
                uint32 unused :24;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} AverageCurrentReadOverDitherPeriodTx;
typedef union
{
        struct
        {
                uint32 AverageDitherCurrent :20;
                uint32 Valid :1;
                uint32 unused :3;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} AverageCurrentReadOverDitherPeriodRx;
typedef union
{
        struct
        {
                uint32 unused :24;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} AutozeroTriggerReadTx;
typedef union
{
        struct
        {
                uint32 AZoffvalue :8;
                uint32 AZonvalue :8;
                uint32 AZoff :1;
                uint32 AZon :1;
                uint32 unused :6;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} AutozeroTriggerReadRx;
typedef union
{
        struct
        {
                uint32 Pwmdutycycle :19;
                uint32 unused :5;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} PWMDutyCycleTx;
typedef union
{
        struct
        {
                uint32 Pwmdutycycle :21;
                uint32 unused :3;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} PWMDutyCycleRx;
typedef union
{
        struct
        {
                uint32 Count1 :4;
                uint32 Count2 :4;
                uint32 Count3 :4;
                uint32 Threshold1 :4;
                uint32 Threshold2 :4;
                uint32 Threshold3 :4;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentProfileDetectionSetup1Tx;
typedef union
{
        struct
        {
                uint32 Count1 :4;
                uint32 Count2 :4;
                uint32 Count3 :4;
                uint32 Threshold1 :4;
                uint32 Threshold2 :4;
                uint32 Threshold3 :4;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentProfileDetectionSetup1Rx;
typedef union
{
        struct
        {
                uint32 ZONE3SET :2;
                uint32 unused :2;
                uint32 Timeout :6;
                uint32 unused1 :14;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentProfileDetectionSetup2Tx;
typedef union
{
        struct
        {
                uint32 ZONE3SET :2;
                uint32 unused :2;
                uint32 Timeout :6;
                uint32 unused1 :14;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentProfileDetectionSetup2Rx;
typedef union
{
        struct
        {
                uint32 unused :24;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentProfileDetectionFeedbackTx;
typedef union
{
        struct
        {
                uint32 PASS :1;
                uint32 Time_out :1;
                uint32 DetectIntrpt :1;
                uint32 unused :21;
                uint32 Chan :3;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} CurrentProfileDetectionFeedbackRx;
typedef union
{
        struct
        {
                uint32 unused :24;
                uint32 Chan :3;
                const uint32 MsgID :4;
                const uint32 r_w :1;
        } bits;
        uint32 data;
} ReadGenericFlagBitsTx;
typedef union
{
        struct
        {
                uint32 RB_L :1;
                uint32 EN_L :1;
                uint32 PS :1;
                uint32 OV :1;
                uint32 unused :23;
                uint32 MsgID :4;
                uint32 r_w :1;
        } bits;
        uint32 data;
} ReadGenericFlagBitsRx;

typedef union
{
        struct
        {
                uint32 unused :24;
                uint32 MsgID :7;
                uint32 r_w :1;
        } bits;
        uint32 data;
} Tle8242DummyMsgID;
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#endif /* TLE8242_reg_h */
