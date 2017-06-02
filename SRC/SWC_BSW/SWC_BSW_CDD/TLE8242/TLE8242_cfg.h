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
/* !File            : TLE8242_cfg.h                                                                                  */
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
#ifndef TLE8242_cfg_h
#define TLE8242_cfg_h

#include "tle8242_reg.h"
#include "tle8242_interface.h"


#define NUMBER_OF_TLE8242       1
#define NUMBER_OF_TLE8242_CHANNEL   8
#define RSENSE                  (0.16)
#define TLE8242FCLK             (20000000)


#define MAX_FRAME_NUM_OF_INIT_CHANNEL_1     6
#define MAX_FRAME_NUM_OF_CTRL_CHANNEL_1     57
#define MAX_FRAME_NUM_OF_DIAG_CHANNEL_1     4
#if NUMBER_OF_TLE8242 > 1
#define MAX_FRAME_NUM_OF_INIT_CHANNEL_2     6
#define MAX_FRAME_NUM_OF_CTRL_CHANNEL_2     50
#define MAX_FRAME_NUM_OF_DIAG_CHANNEL_2     4
#endif



#define ConvertCurTatToSetPoint(target)             (uint32)((target*2048*RSENSE)/320)
#define ConvertSetPointToCurTar(setpoint)           ((setpoint*320)/(2048*RSENSE))

#define ConvertCurTatToSetPointAvgDitherEN(target)             (uint32)((target*32768*RSENSE)/320)
#define ConvertSetPointToCurTarAvgDitherEN(setpoint)           ((setpoint*320)/(32768*RSENSE))

#define ConvertCurTatToSetPointAvgDitherDis(target)             (uint32)((target*8192*RSENSE)/320)
#define ConvertSetPointToCurTarAvgDitherDis(setpoint)           ((setpoint*320)/(8192*RSENSE))

#define ConvertCurTatToSetPoint_DPWM(target)             (uint32)((target*8192*RSENSE)/320)
#define ConvertSetPointToCurTar_DPWM(setpoint)           ((setpoint*320)/(8192*RSENSE))

#define ConvertCurTatToSetPointAvgDitherEN_DPWM(target)             (uint32)((target*131072*RSENSE)/320)
#define ConvertSetPointToCurTarAvgDitherEN_DPWM(setpoint)           ((setpoint*320)/(131072*RSENSE))

#define ConvertCurTatToSetPointAvgDitherDis_DPWM(target)             (uint32)((target*32768*RSENSE)/320)
#define ConvertSetPointToCurTarAvgDitherDis_DPWM(setpoint)           ((setpoint*320)/(32768*RSENSE))

#define ConvertCurTatToSetPoint2(target)             (uint32)((target*8192*RSENSE)/(320*2))
#define ConvertSetPointToCurTar2(setpoint)           ((setpoint*320*2)/(8192*RSENSE))

#define DitherStepRatioToCurrentStepPoint           (4)



#define CurrentMode     0
#define DirectPWMMode   1
#define FaultNotTriPIN  0
#define FaultTriPIN     1


#define Channel0CMINIT CurrentMode
#define Channel1CMINIT CurrentMode
#define Channel2CMINIT CurrentMode
#define Channel3CMINIT CurrentMode
#define Channel4CMINIT CurrentMode
#define Channel5CMINIT CurrentMode
#define Channel6CMINIT CurrentMode
#define Channel7CMINIT CurrentMode
#if NUMBER_OF_TLE8242> 1
#define Channel8CMINIT CurrentMode
#define Channel9CMINIT CurrentMode
#define Channel10CMINIT CurrentMode
#define Channel11CMINIT CurrentMode
#define Channel12CMINIT CurrentMode
#define Channel13CMINIT CurrentMode
#define Channel14CMINIT CurrentMode
#define Channel15CMINIT CurrentMode
#endif

#define ControlModeData Channel0CMINIT | \
                        Channel1CMINIT | \
                        Channel2CMINIT | \
                        Channel3CMINIT | \
                        Channel4CMINIT | \
                        Channel5CMINIT | \
                        Channel6CMINIT | \
                        Channel7CMINIT
#if NUMBER_OF_TLE8242> 1
#define ControlModeData1 Channel8CMINIT | \
                        Channel9CMINIT | \
                        Channel10CMINIT | \
                        Channel11CMINIT | \
                        Channel12CMINIT | \
                        Channel13CMINIT | \
                        Channel14CMINIT | \
                        Channel15CMINIT
#endif

#define Channel0FMINIT FaultTriPIN
#define Channel1FMINIT FaultTriPIN
#define Channel2FMINIT FaultTriPIN
#define Channel3FMINIT FaultTriPIN
#define Channel4FMINIT FaultTriPIN
#define Channel5FMINIT FaultTriPIN
#define Channel6FMINIT FaultTriPIN
#define Channel7FMINIT FaultTriPIN
#if NUMBER_OF_TLE8242> 1
#define Channel8FMINIT FaultTriPIN
#define Channel9FMINIT FaultTriPIN
#define Channel10FMINIT FaultTriPIN
#define Channel11FMINIT FaultTriPIN
#define Channel12FMINIT FaultTriPIN
#define Channel13FMINIT FaultTriPIN
#define Channel14FMINIT FaultTriPIN
#define Channel15FMINIT FaultTriPIN
#endif

#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
typedef struct
{
        ICVersionManufacturerTx ICVersionManufacturer;
        ControlMethodandFaultMaskConfigurationTx ControlMethodandFaultMaskConfiguration;
        DiagnosticConfigurationchannelTx DiagnosticConfigurationchannel[2];
        DiagnosticReadchannelTx DiagnosticReadchannel[2];
        PWMOffsetchannel0_3Tx PWMOffsetchannel0_3;
        PWMOffsetchannel4_7Tx PWMOffsetchannel4_7;
        MainPeriodSetTx MainPeriodSet[8];
        ControlVariableSetKPandKITx ControlVariableSetKPandKI[8];
        CurrentandDitherAmplitudeSetTx CurrentandDitherAmplitudeSet[8];
        DitherPeriodSetTx DitherPeriodSet[8];
        MaxMinCurrentReadTx MaxMinCurrentRead[8];
        AverageCurrentReadOverDitherPeriodTx AverageCurrentReadOverDitherPeriod[8];
        AutozeroTriggerReadTx AutozeroTriggerRead[8];
        PWMDutyCycleTx PWMDutyCycle[8];
        CurrentProfileDetectionSetup1Tx CurrentProfileDetectionSetup1[8];
        CurrentProfileDetectionSetup2Tx CurrentProfileDetectionSetup2[8];
        CurrentProfileDetectionFeedbackTx CurrentProfileDetectionFeedback[8];
        ReadGenericFlagBitsTx ReadGenericFlagBits;
} TLE8242_Tx;

typedef struct
{
        ICVersionManufacturerRx ICVersionManufacturer;
        ControlMethodandFaultMaskConfigurationRx ControlMethodandFaultMaskConfiguration;
        DiagnosticConfigurationchannelRx DiagnosticConfigurationchannel[2];
        DiagnosticReadchannelRx DiagnosticReadchannel[2];
        PWMOffsetchannel0_3Rx PWMOffsetchannel0_3;
        PWMOffsetchannel4_7Rx PWMOffsetchannel4_7;
        MainPeriodSetRx MainPeriodSet[8];
        ControlVariableSetKPandKIRx ControlVariableSetKPandKI[8];
        CurrentandDitherAmplitudeSetRx CurrentandDitherAmplitudeSet[8];
        DitherPeriodSetRx DitherPeriodSet[8];
        MaxMinCurrentReadRx MaxMinCurrentRead[8];
        AverageCurrentReadOverDitherPeriodRx AverageCurrentReadOverDitherPeriod[8];
        AutozeroTriggerReadRx AutozeroTriggerRead[8];
        PWMDutyCycleRx PWMDutyCycle[8];
        CurrentProfileDetectionSetup1Rx CurrentProfileDetectionSetup1[8];
        CurrentProfileDetectionSetup2Rx CurrentProfileDetectionSetup2[8];
        CurrentProfileDetectionFeedbackRx CurrentProfileDetectionFeedback[8];
        ReadGenericFlagBitsRx ReadGenericFlagBits;
} TLE8242_Rx;





extern TLE8242_Tx TLE8242_au32SpiTx[NUMBER_OF_TLE8242];
extern TLE8242_Rx TLE8242_au32SpiRx[NUMBER_OF_TLE8242];
extern Tle8242DummyMsgID TLE8242_au32CtrlTxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_CTRL_CHANNEL_1];
extern Tle8242DummyMsgID TLE8242_au32InitTxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_INIT_CHANNEL_1];
extern Tle8242DummyMsgID TLE8242_au32DiagRxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_DIAG_CHANNEL_1];
extern Tle8242DummyMsgID TLE8242_au32CtrlRxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_CTRL_CHANNEL_1];
extern Tle8242DummyMsgID TLE8242_au32InitRxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_INIT_CHANNEL_1];
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const uint8 TLE8242_au8_channel_buff_deepth_cfg[NUMBER_OF_TLE8242*3];
extern const uint8 TLE8242_au8ChanNumPerChip[NUMBER_OF_TLE8242];
extern const Tle8242DummyMsgID TLE8242_au32DiagTxBuff[NUMBER_OF_TLE8242][MAX_FRAME_NUM_OF_DIAG_CHANNEL_1];
#define TLE8242_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"



#define ShortGroundBit      (1<<5)
#define OFFTSTBit           (1<<4)
#define ShortBatBit         (1<<3)
#define ShortBatTstBit      (1<<2)
#define OLOFFBit            (1<<1)
#define OLONBit             (1<<0)


#define ICVersionManufacturer_MSG_ID 0
#define ControlMethodandFaultMaskConfiguration_MSG_ID 1
#define DiagnosticConfigurationchannel0_3_MSG_ID 2
#define DiagnosticConfigurationchannel4_7_MSG_ID 3
#define DiagnosticReadchannel0_3_MSG_ID 4
#define DiagnosticReadchannel4_7_MSG_ID 5
#define PWMOffsetchannel0_3_MSG_ID 6
#define PWMOffsetchannel4_7_MSG_ID 7
#define MainPeriodSet_MSG_ID 1
#define ControlVariableSetKPandKI_MSG_ID 2
#define CurrentandDitherAmplitudeSet_MSG_ID 3
#define DitherPeriodSet_MSG_ID 4
#define MaxMinCurrentRead_MSG_ID 5
#define AverageCurrentReadOverDitherPeriod_MSG_ID 6
#define AutozeroTriggerRead_MSG_ID 7
#define PWMDutyCycle_MSG_ID 8
#define CurrentProfileDetectionSetup1_MSG_ID 9
#define CurrentProfileDetectionSetup2_MSG_ID 10
#define CurrentProfileDetectionFeedback_MSG_ID 11
#define ReadGenericFlagBits_MSG_ID 15



#define ReadGenericFlagMsgID        0x78
#define ReadGenericFlagMSgOFFSET    0x60
#define MAX_VALID_MSG_ID            (95)//0b1011111

#define MAX_VALID_KP                4095
#define MAX_VALID_KI                4095
#define MAX_VALID_DITHER_STEPS      31
#define MAX_VALID_CURRENT_SETPOINT  4095
#define MAX_VALID_DIV_N             16383
#define MAX_VALID_DIV_M             3




#endif /* TLE8242_cfg_h */
