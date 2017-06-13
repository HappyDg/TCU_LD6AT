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
                uint32 udtUnused :24;
                const uint32 udtMsgID :7;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} ICVersionManufacturerTx;
typedef union
{
        struct
        {
                uint32 udtUnused :8;
                uint32 udtVersionNumber :8;
                uint32 udtICManufID :8;
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} ICVersionManufacturerRx;
typedef union
{
        struct
        {
                uint32 udtUnused :4;
                uint32 udtDIAG_TMR :2;
                uint32 bFME :1;
                uint32 bFMR :1;
                uint32 udtFM :8;
                uint32 udtCM :8;
                const uint32 udtMsgID :7;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} ControlMethodandFaultMaskConfigurationTx;
typedef union
{
        struct
        {
                uint32 udtUnused :4;
                uint32 udtDIAG_TMR :2;
                uint32 bFME :1;
                uint32 bFMR :1;
                uint32 udtFM :8;
                uint32 udtCM :8;
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
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
                const uint32 udtMsgID :7;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
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
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
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
                const uint32 udtMsgID :7;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
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
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} DiagnosticConfigurationchannel4_7Rx;
typedef union
{
        struct
        {
                uint32 udtUnused :24;
                const uint32 udtMsgID :7;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
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
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
}DiagnosticReadchannelRx;

typedef union
{
        struct
        {
                uint32 OFFSET3 :5;
                uint32 OFFSET2 :5;
                uint32 OFFSET1 :5;
                uint32 OFFSET0 :5;
                uint32 udtUnused :4;
                const uint32 udtMsgID :7;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} PWMOffsetchannel0_3Tx;
typedef union
{
        struct
        {
                uint32 OFFSET3 :5;
                uint32 OFFSET2 :5;
                uint32 OFFSET1 :5;
                uint32 OFFSET0 :5;
                uint32 udtUnused :4;
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} PWMOffsetchannel0_3Rx;
typedef union
{
        struct
        {
                uint32 OFFSET7 :5;
                uint32 OFFSET6 :5;
                uint32 OFFSET5 :5;
                uint32 OFFSET4 :5;
                uint32 udtUnused :4;
                const uint32 udtMsgID :7;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} PWMOffsetchannel4_7Tx;
typedef union
{
        struct
        {
                uint32 OFFSET7 :5;
                uint32 OFFSET6 :5;
                uint32 OFFSET5 :5;
                uint32 OFFSET4 :5;
                uint32 udtUnused :4;
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} PWMOffsetchannel4_7Rx;
typedef union
{
        struct
        {
                uint32 DividerN :14;
                uint32 DividerM :2;
                uint32 SAM :1;
                uint32 udtUnused :7;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} MainPeriodSetTx;
typedef union
{
        struct
        {
                uint32 DividerN :14;
                uint32 DividerM :2;
                uint32 SAM :1;
                uint32 udtUnused :7;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} MainPeriodSetRx;
typedef union
{
        struct
        {
                uint32 ki :12;
                uint32 kp :12;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} ControlVariableSetKPandKITx;
typedef union
{
        struct
        {
                uint32 ki :12;
                uint32 kp :12;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} ControlVariableSetKPandKIRx;
typedef union
{
        struct
        {
                uint32 Currentsetpoint :11;

                uint32 Ditherstepsize :11;
                uint32 udtUnused :1;
                uint32 EN :1;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} CurrentandDitherAmplitudeSetTx;
typedef union
{
        struct
        {
                uint32 Currentsetpoint :11;

                uint32 Ditherstepsize :11;
                uint32 udtUnused :1;
                uint32 EN :1;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} CurrentandDitherAmplitudeSetRx;
typedef union
{
        struct
        {
                uint32 Numberofsteps :5;
                uint32 udtUnused :19;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} DitherPeriodSetTx;
typedef union
{
        struct
        {
                uint32 Numberofsteps :5;
                uint32 udtUnused :19;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} DitherPeriodSetRx;
typedef union
{
        struct
        {
                uint32 udtUnused :24;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} MaxMinCurrentReadTx;
typedef union
{
        struct
        {
                uint32 Min :11;
                uint32 Max :11;
                uint32 Valid :1;
                uint32 udtUnused :1;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} MaxMinCurrentReadRx;
typedef union
{
        struct
        {
                uint32 udtUnused :24;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} AverageCurrentReadOverDitherPeriodTx;
typedef union
{
        struct
        {
                uint32 AverageDitherCurrent :20;
                uint32 Valid :1;
                uint32 udtUnused :3;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} AverageCurrentReadOverDitherPeriodRx;
typedef union
{
        struct
        {
                uint32 udtUnused :24;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} AutozeroTriggerReadTx;
typedef union
{
        struct
        {
                uint32 AZoffvalue :8;
                uint32 AZonvalue :8;
                uint32 AZoff :1;
                uint32 AZon :1;
                uint32 udtUnused :6;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} AutozeroTriggerReadRx;
typedef union
{
        struct
        {
                uint32 Pwmdutycycle :19;
                uint32 udtUnused :5;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} PWMDutyCycleTx;
typedef union
{
        struct
        {
                uint32 Pwmdutycycle :21;
                uint32 udtUnused :3;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
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
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
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
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} CurrentProfileDetectionSetup1Rx;
typedef union
{
        struct
        {
                uint32 ZONE3SET :2;
                uint32 udtUnused :2;
                uint32 Timeout :6;
                uint32 unused1 :14;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} CurrentProfileDetectionSetup2Tx;
typedef union
{
        struct
        {
                uint32 ZONE3SET :2;
                uint32 udtUnused :2;
                uint32 Timeout :6;
                uint32 unused1 :14;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} CurrentProfileDetectionSetup2Rx;
typedef union
{
        struct
        {
                uint32 udtUnused :24;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} CurrentProfileDetectionFeedbackTx;
typedef union
{
        struct
        {
                uint32 bPASS :1;
                uint32 bTimeOut :1;
                uint32 bDetectIntrpt :1;
                uint32 udtUnused :21;
                uint32 udtChan :3;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} CurrentProfileDetectionFeedbackRx;
typedef union
{
        struct
        {
                uint32 udtUnused :24;
                uint32 udtChan :3;
                const uint32 udtMsgID :4;
                const uint32 bRW :1;
        } bits;
        uint32 u32Data;
} ReadGenericFlagBitsTx;
typedef union
{
        struct
        {
                uint32 RB_L :1;
                uint32 EN_L :1;
                uint32 PS :1;
                uint32 OV :1;
                uint32 udtUnused :23;
                uint32 udtMsgID :4;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} ReadGenericFlagBitsRx;

typedef union
{
        struct
        {
                uint32 udtUnused :24;
                uint32 udtMsgID :7;
                uint32 bRW :1;
        } bits;
        uint32 u32Data;
} TLE8242_DummyMsgID;
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#endif /* TLE8242_reg_h */
