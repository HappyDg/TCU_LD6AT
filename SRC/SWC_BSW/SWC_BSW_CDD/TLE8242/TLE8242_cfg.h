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

#include "Std_Types.h"

#include "TLE8242_reg.h"
#include "TLE8242_interface.h"
#include "Dem.h"


// maybe those configs need to move out the tle8242 cdd folder to cdd cfg.
#define TLE8242_u8CH_NR       1
#define TLE8242_u8MAX_CH_NR   8
#define RSENSE                  (0.16)
#define TLE8242_u32FCLKIPT             (20000000)

#define TLE8242_bUSE_INT_BUF         1

#define TLE8242_u8MAX_FRM_INIT_CH_1     6
#define TLE8242_u8MAX_FRM_CTRL_CH_1     57
#define TLE8242_u8MAX_FRM_DIAG_CH_1     12
#if TLE8242_u8CH_NR > 1
#define TLE8242_u8MAX_FRM_INIT_CH_2     6
#define TLE8242_u8MAX_FRM_CTRL_CH_2     50
#define TLE8242_u8MAX_FRM_DIAG_CH_2     4
#endif

#define TLE8242_u8MAX_NR_FLT			6



#define TLE8242_u8DITHER_SETPOINT_TO_CURRENT_POINT           (4)



#define TLE8242_u8CRNT_MOD     0
#define TLE8242_u8_DIRECT_MOD   1
#define TLE8242_u8_FLT_NOT_TRIG_PIN  0
#define TLE8242_u8_FLT_TRIG_PIN     1


#define TLE8242_u8_CH_0CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_1CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_2CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_3CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_4CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_5CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_6CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_7CMINIT TLE8242_u8CRNT_MOD
#if TLE8242_u8CH_NR> 1
#define TLE8242_u8_CH_8CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_9CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_10CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_11CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_12CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_13CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_14CMINIT TLE8242_u8CRNT_MOD
#define TLE8242_u8_CH_15CMINIT TLE8242_u8CRNT_MOD
#endif

#define ControlModeData TLE8242_u8_CH_0CMINIT | \
                        TLE8242_u8_CH_1CMINIT | \
                        TLE8242_u8_CH_2CMINIT | \
                        TLE8242_u8_CH_3CMINIT | \
                        TLE8242_u8_CH_4CMINIT | \
                        TLE8242_u8_CH_5CMINIT | \
                        TLE8242_u8_CH_6CMINIT | \
                        TLE8242_u8_CH_7CMINIT
#if TLE8242_u8CH_NR> 1
#define ControlModeData1 TLE8242_u8_CH_8CMINIT | \
                        TLE8242_u8_CH_9CMINIT | \
                        TLE8242_u8_CH_10CMINIT | \
                        TLE8242_u8_CH_11CMINIT | \
                        TLE8242_u8_CH_12CMINIT | \
                        TLE8242_u8_CH_13CMINIT | \
                        TLE8242_u8_CH_14CMINIT | \
                        TLE8242_u8_CH_15CMINIT
#endif

#define TLE8242_u8_CH_0FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_1FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_2FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_3FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_4FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_5FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_6FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_7FMINIT TLE8242_u8_FLT_TRIG_PIN
#if TLE8242_u8CH_NR> 1
#define TLE8242_u8_CH_8FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_9FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_10FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_11FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_12FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_13FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_14FMINIT TLE8242_u8_FLT_TRIG_PIN
#define TLE8242_u8_CH_15FMINIT TLE8242_u8_FLT_TRIG_PIN
#endif

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



#define TLE8242_u8_FLT_SC_BIT      (5)
#define TLE8242_u8_FLT_OFF_TST_BIT           (4)
#define TLE8242_u8_FLT_SCS_BIT         (3)
#define TLE8242_u8_FLT_SCS_TST_BIT      (2)
#define TLE8242_u8_FLT_OL_OFF_BIT            (1)
#define TLE8242_u8_FLT_OL_ON_BIT             (0)


#define TLE8242_u8_IC_VERS_MSG_ID 0
#define TLE8242_u8_CTRL_MOD_FLT_MASK_MSG_ID 1
#define TLE8242_u8_DIAGC_CFG_03_MSG_ID 2
#define TLE8242_u8_DIAGC_CFG_47_MSG_ID 3
#define TLE8242_u8_DIAGC_READ_CH_03_MSG_ID 4
#define TLE8242_u8_DIAGC_READ_CH_47_MSG_ID 5
#define TLE8242_u8_PWM_OFFS_03_MSG_ID 6
#define TLE8242_u8_PWM_OFFS_47_MSG_ID 7
#define TLE8242_u8_MAI_PERD_MSG_ID 1
#define TLE8242_u8_KP_KI_MSG_ID 2
#define TLE8242_u8_CRNT_DITHER_MSG_ID 3
#define TLE8242_u8_DITHER_PERD_MSG_ID 4
#define TLE8242_u8_MAX_MIN_CRNT_READ_MSG_ID 5
#define TLE8242_u8_AVRG_CRNT_READ_MSG_ID 6
#define TLE8242_u8_ATUO_ZERO_MSG_ID 7
#define TLE8242_u8_PWM_DUTY_CYCLE_MSG_ID 8
#define TLE8242_u8_CRNT_PROF_DETN_MSG_ID 9
#define TLE8242_u8_CRNT_PROF_DETN_1_MSG_ID 10
#define TLE8242_u8_CRNT_PROF_DETN_FB_MSG_ID 11
#define TLE8242_u8_READ_GEN_FLG_MSG_ID 15



#define TLE8242_u8_READ_GEN_FLG_MSG_ID_7BIT        0x78
#define TLE8242_u8_READ_GEN_FLG_MSG_OFFS    0x60
#define TLE8242_u8_MAX_VALID_MSG_ID            (95)//0b1011111

#define TLE8242_u32_MAX_VALID_KP                4095
#define TLE8242_u32_MAX_VALID_KI                4095
#define TLE8242_u8_MAX_VALID_DITHER_STEPS      31
#define TLE8242_u32_MAX_VALID_CRNT_SETPOINT  2047
#define TLE8242_u8_MAX_VALID_DIV_N             16383
#define TLE8242_u8_MAX_VALID_DIV_M             3

typedef struct
{
   Dem_EventIdType    audtIdxType[TLE8242_u8MAX_NR_FLT];
} TLE8242_tstFlt;

typedef bool (*TLE9242_tstFltFct) (uint8);

typedef struct
{

	TLE9242_tstFltFct astFltFct[TLE8242_u8MAX_NR_FLT];
	TLE8242_tstFlt astChDemID[TLE8242_u8MAX_CH_NR];

}TLE8242_tstFltCfg_s;



/*#define TLE8242_stDECL_FLT(func, typ0, typ1, typ2, typ3, typ4, typ5) \
   { \
         DemConf_DemEventParameter_##func##_##typ0, \
         DemConf_DemEventParameter_##func##_##typ1, \
         DemConf_DemEventParameter_##func##_##typ2,  \
         DemConf_DemEventParameter_##func##_##typ3, \
         DemConf_DemEventParameter_##func##_##typ4, \
         DemConf_DemEventParameter_##func##_##typ5  \
   }


typedef enum
{
  TLE8242_GENERAL_FAULT,
  TLE8242_OPEN,
  TLE8242_OVERLOAD,
  TLE8242_UNDERLOAD,
  TLE8242_SHORT_TO_GND,
  TLE8242_SHORT_TO_BATT
}TLE8242_Flt_type;*/
	
#define TLE8242_stDECL_FLT(func, typ0, typ1, typ2, typ3, typ4, typ5) \
   { \
         TLE8242_CHANNEL_##func##_##typ0, \
         TLE8242_CHANNEL_##func##_##typ1, \
         TLE8242_CHANNEL_##func##_##typ2,  \
         TLE8242_CHANNEL_##func##_##typ3, \
         TLE8242_CHANNEL_##func##_##typ4, \
         TLE8242_CHANNEL_##func##_##typ5  \
   }

   /*just define for test, need delete later*/
#define TLE8242_CHANNEL_C4_SOL_GENERAL_FAULT     112
#define TLE8242_CHANNEL_C4_SOL_OPEN              113
#define TLE8242_CHANNEL_C4_SOL_OVERLOAD          114
#define TLE8242_CHANNEL_C4_SOL_SHORT_TO_BATT     115
#define TLE8242_CHANNEL_C4_SOL_SHORT_TO_GND      116
#define TLE8242_CHANNEL_C4_SOL_STUCK_OFF         117
#define TLE8242_CHANNEL_C4_SOL_STUCK_ON          118
#define TLE8242_CHANNEL_C4_SOL_UNDERLOAD         119
#define TLE8242_CHANNEL_C3_SOL_GENERAL_FAULT     120
#define TLE8242_CHANNEL_C3_SOL_OPEN              121
#define TLE8242_CHANNEL_C3_SOL_OVERLOAD          122
#define TLE8242_CHANNEL_C3_SOL_SHORT_TO_BATT     123
#define TLE8242_CHANNEL_C3_SOL_SHORT_TO_GND      124
#define TLE8242_CHANNEL_C3_SOL_UNDERLOAD         125
#define TLE8242_CHANNEL_C2_SOL_GENERAL_FAULT     126
#define TLE8242_CHANNEL_C2_SOL_OPEN              127
#define TLE8242_CHANNEL_C2_SOL_OVERLOAD          128
#define TLE8242_CHANNEL_C2_SOL_SHORT_TO_BATT     129
#define TLE8242_CHANNEL_C2_SOL_SHORT_TO_GND      130
#define TLE8242_CHANNEL_C2_SOL_STUCK_OFF         131
#define TLE8242_CHANNEL_C2_SOL_STUCK_ON          132
#define TLE8242_CHANNEL_C2_SOL_UNDERLOAD         133
#define TLE8242_CHANNEL_C1_SOL_GENERAL_FAULT     134
#define TLE8242_CHANNEL_C1_SOL_OPEN              135
#define TLE8242_CHANNEL_C1_SOL_OVERLOAD          136
#define TLE8242_CHANNEL_C1_SOL_SHORT_TO_BATT     137
#define TLE8242_CHANNEL_C1_SOL_SHORT_TO_GND      138
#define TLE8242_CHANNEL_C1_SOL_STUCK_OFF         139
#define TLE8242_CHANNEL_C1_SOL_STUCK_ON          140
#define TLE8242_CHANNEL_C1_SOL_UNDERLOAD         141
#define TLE8242_CHANNEL_B1_SOL_GENERAL_FAULT     142
#define TLE8242_CHANNEL_B1_SOL_OPEN              143
#define TLE8242_CHANNEL_B1_SOL_OVERLOAD          144
#define TLE8242_CHANNEL_B1_SOL_SHORT_TO_BATT     145
#define TLE8242_CHANNEL_B1_SOL_SHORT_TO_GND      146
#define TLE8242_CHANNEL_B1_SOL_STUCK_OFF         147
#define TLE8242_CHANNEL_B1_SOL_STUCK_ON          148
#define TLE8242_CHANNEL_B1_SOL_UNDERLOAD         149
#define TLE8242_CHANNEL_RES_SOL_GENERAL_FAULT     150
#define TLE8242_CHANNEL_RES_SOL_OPEN              151
#define TLE8242_CHANNEL_RES_SOL_OVERLOAD          152
#define TLE8242_CHANNEL_RES_SOL_SHORT_TO_BATT     153
#define TLE8242_CHANNEL_RES_SOL_SHORT_TO_GND      154
#define TLE8242_CHANNEL_RES_SOL_STUCK_OFF         155
#define TLE8242_CHANNEL_RES_SOL_STUCK_ON          156
#define TLE8242_CHANNEL_RES_SOL_UNDERLOAD         157
#define TLE8242_CHANNEL_PRI_OIL_GENERAL_FAULT     158
#define TLE8242_CHANNEL_PRI_OIL_OPEN              159
#define TLE8242_CHANNEL_PRI_OIL_OVERLOAD          160
#define TLE8242_CHANNEL_PRI_OIL_SHORT_TO_BATT     161
#define TLE8242_CHANNEL_PRI_OIL_SHORT_TO_GND      162
#define TLE8242_CHANNEL_PRI_OIL_STUCK_OFF         163
#define TLE8242_CHANNEL_PRI_OIL_STUCK_ON          164
#define TLE8242_CHANNEL_PRI_OIL_UNDERLOAD         165
#define TLE8242_CHANNEL_TC_LOCK_GENERAL_FAULT     166
#define TLE8242_CHANNEL_TC_LOCK_OPEN              167
#define TLE8242_CHANNEL_TC_LOCK_OVERLOAD          168
#define TLE8242_CHANNEL_TC_LOCK_SHORT_TO_BATT     169
#define TLE8242_CHANNEL_TC_LOCK_SHORT_TO_GND      170
#define TLE8242_CHANNEL_TC_LOCK_STUCK_OFF         171
#define TLE8242_CHANNEL_TC_LOCK_STUCK_ON          172
#define TLE8242_CHANNEL_TC_LOCK_UNDERLOAD         173

#define TLE8242_SG_FAULT                           0
#define TLE8242_SGOP_FAULT                         1
#define TLE8242_SB_FAULT                           2
#define TLE8242_SBOP_FAULT                         3
#define TLE8242_OP_FAULT                           4
#define TLE8242_LOW_FAULT                          5
#define TLE8242_HIGH_FAULT                         6
#define TLE8242_GEN_FAULT                          7





#define TLE8242_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern const uint8 TLE8242_kau8ChBufSizeCfg[TLE8242_u8CH_NR*3];
extern const uint8 TLE8242_kau8ChNrPerChip[TLE8242_u8CH_NR];
extern const TLE8242_DummyMsgID TLE8242_kastDiagTxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_DIAG_CH_1];
extern const TLE8242_tstFltCfg_s TLE8242_tstFltDev;
#define TLE8242_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
extern TLE8242_Tx TLE8242_astSpiTx[TLE8242_u8CH_NR];
extern TLE8242_Rx TLE8242_astSpiRx[TLE8242_u8CH_NR];
extern TLE8242_DummyMsgID TLE8242_astCtrlTxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_CTRL_CH_1];
extern TLE8242_DummyMsgID TLE8242_astInitTxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_INIT_CH_1];
extern TLE8242_DummyMsgID TLE8242_astDiagRxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_DIAG_CH_1];
extern TLE8242_DummyMsgID TLE8242_astCtrlRxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_CTRL_CH_1];
extern TLE8242_DummyMsgID TLE8242_astInitRxBuf[TLE8242_u8CH_NR][TLE8242_u8MAX_FRM_INIT_CH_1];
#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"




#endif /* TLE8242_cfg_h */
