/******************************************************************************/
/*                                                                            */
/* !Layer          : Layer                                                    */
/*                                                                            */
/* !Component      : Component                                                */
/* !Description    : Component description                                    */
/*                                                                            */
/* !Module         : MODULE                                                   */
/* !Description    : MODULE description                                       */
/*                                                                            */
/* !File           : MAIN_MSG.H                                               */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : Infineon_tc17                                            */
/*                                                                            */
/* !Vendor         : VALEO                                                    */
/*                                                                            */
/* !Author         : A. Abohassan                                             */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2006 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   $ */
/* $Revision::  $ */
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/

#ifndef MAIN_MSG_H
#define MAIN_MSG_H

#include "F32SRV.h"
#include "Std_Limits.h"
#include "MATHSRV.h"
#include "BSW.h"


/**********************************************************************************************************************/
/* PUBLIC DEFINES                                                                                                     */
/**********************************************************************************************************************/
/* ========================================================================== */
/* CAN Rx MSG Init values                                                     */
/* ========================================================================== */
/* TCU / ABS1 Rx 10 ms  Init & Fail values */
#define MAIN_MSG_WHLSPDFRNTLERAW_TYPE (uint16)
#define MAIN_MSG_WHLSPDFRNTLERAW_INIT ((uint16)0)
#define MAIN_MSG_WHLSPDFRNTLERAW_MINRAW ((uint16)0)
#define MAIN_MSG_WHLSPDFRNTLERAW_MAXRAW ((uint16)4095)
#define MAIN_MSG_WHLSPDFRNTLERAW_ISPHYS ((boolean)true)
#define MAIN_MSG_WHLSPDFRNTLERAW_GAIN ((float)0.05625f)
#define MAIN_MSG_WHLSPDFRNTLERAW_OFFSET ((float)0.0f)
#define MAIN_MSG_WHLSPDFRNTLERAW_NEUTRAL ((float)0.0f)
#define MAIN_MSG_WHLSPDFRNTLERAW_MINPHYS ((float)0.0f)
#define MAIN_MSG_WHLSPDFRNTLERAW_MAXPHYS ((float)230.287f)
#define MAIN_MSG_WHLSPDFRNTRIRAW_TYPE (uint16)
#define MAIN_MSG_WHLSPDFRNTRIRAW_INIT ((uint16)0)
#define MAIN_MSG_WHLSPDFRNTRIRAW_MINRAW ((uint16)0)
#define MAIN_MSG_WHLSPDFRNTRIRAW_MAXRAW ((uint16)4095)
#define MAIN_MSG_WHLSPDFRNTRIRAW_ISPHYS ((boolean)true)
#define MAIN_MSG_WHLSPDFRNTRIRAW_GAIN ((float)0.05625f)
#define MAIN_MSG_WHLSPDFRNTRIRAW_OFFSET ((float)0.0f)
#define MAIN_MSG_WHLSPDFRNTRIRAW_NEUTRAL ((float)0.0f)
#define MAIN_MSG_WHLSPDFRNTRIRAW_MINPHYS ((float)0.0f)
#define MAIN_MSG_WHLSPDFRNTRIRAW_MAXPHYS ((float)230.287f)
#define MAIN_MSG_WHLSPDRELERAW_TYPE (uint16)
#define MAIN_MSG_WHLSPDRELERAW_INIT ((uint16)0)
#define MAIN_MSG_WHLSPDRELERAW_MINRAW ((uint16)0)
#define MAIN_MSG_WHLSPDRELERAW_MAXRAW ((uint16)4095)
#define MAIN_MSG_WHLSPDRELERAW_ISPHYS ((boolean)true)
#define MAIN_MSG_WHLSPDRELERAW_GAIN ((float)0.05625f)
#define MAIN_MSG_WHLSPDRELERAW_OFFSET ((float)0.0f)
#define MAIN_MSG_WHLSPDRELERAW_NEUTRAL ((float)0.0f)
#define MAIN_MSG_WHLSPDRELERAW_MINPHYS ((float)0.0f)
#define MAIN_MSG_WHLSPDRELERAW_MAXPHYS ((float)230.287f)
#define MAIN_MSG_WHLSPDRERIRAW_TYPE (uint16)
#define MAIN_MSG_WHLSPDRERIRAW_INIT ((uint16)0)
#define MAIN_MSG_WHLSPDRERIRAW_MINRAW ((uint16)0)
#define MAIN_MSG_WHLSPDRERIRAW_MAXRAW ((uint16)4095)
#define MAIN_MSG_WHLSPDRERIRAW_ISPHYS ((boolean)true)
#define MAIN_MSG_WHLSPDRERIRAW_GAIN ((float)0.05625f)
#define MAIN_MSG_WHLSPDRERIRAW_OFFSET ((float)0.0f)
#define MAIN_MSG_WHLSPDRERIRAW_NEUTRAL ((float)0.0f)
#define MAIN_MSG_WHLSPDRERIRAW_MINPHYS ((float)0.0f)
#define MAIN_MSG_WHLSPDRERIRAW_MAXPHYS ((float)230.287f)
/* TCU / ABS2 Rx 10 ms  Init & Fail values */
#define MAIN_MSG_ABSCTRLACTV_TYPE (boolean)
#define MAIN_MSG_ABSCTRLACTV_INIT ((boolean)0)
#define MAIN_MSG_ABSCTRLACTV_MINRAW ((boolean)0)
#define MAIN_MSG_ABSCTRLACTV_MAXRAW ((boolean)1)
#define MAIN_MSG_ABSCTRLACTV_ISPHYS ((boolean)false)
#define MAIN_MSG_ABSCTRLACTV_GAIN ((float)1.0f)
#define MAIN_MSG_ABSCTRLACTV_OFFSET ((float)0.0f)
#define MAIN_MSG_ABSCTRLACTV_NEUTRAL
#define MAIN_MSG_ABSCTRLACTV_MINPHYS ((float)0.0f)
#define MAIN_MSG_ABSCTRLACTV_MAXPHYS ((float)0.0f)
#define MAIN_MSG_ABSFLGFLT_TYPE (boolean)
#define MAIN_MSG_ABSFLGFLT_INIT ((boolean)0)
#define MAIN_MSG_ABSFLGFLT_MINRAW ((boolean)0)
#define MAIN_MSG_ABSFLGFLT_MAXRAW ((boolean)1)
#define MAIN_MSG_ABSFLGFLT_ISPHYS ((boolean)false)
#define MAIN_MSG_ABSFLGFLT_GAIN ((float)1.0f)
#define MAIN_MSG_ABSFLGFLT_OFFSET ((float)0.0f)
#define MAIN_MSG_ABSFLGFLT_NEUTRAL
#define MAIN_MSG_ABSFLGFLT_MINPHYS ((float)0.0f)
#define MAIN_MSG_ABSFLGFLT_MAXPHYS ((float)0.0f)
#define MAIN_MSG_EBDFLGFLT_TYPE (boolean)
#define MAIN_MSG_EBDFLGFLT_INIT ((boolean)0)
#define MAIN_MSG_EBDFLGFLT_MINRAW ((boolean)0)
#define MAIN_MSG_EBDFLGFLT_MAXRAW ((boolean)1)
#define MAIN_MSG_EBDFLGFLT_ISPHYS ((boolean)false)
#define MAIN_MSG_EBDFLGFLT_GAIN ((float)1.0f)
#define MAIN_MSG_EBDFLGFLT_OFFSET ((float)0.0f)
#define MAIN_MSG_EBDFLGFLT_NEUTRAL
#define MAIN_MSG_EBDFLGFLT_MINPHYS ((float)0.0f)
#define MAIN_MSG_EBDFLGFLT_MAXPHYS ((float)0.0f)
/* TCU / ECM1 Rx 10 ms  Init & Fail values */
#define MAIN_MSG_ACCRPEDLRAT_TYPE (uint8)
#define MAIN_MSG_ACCRPEDLRAT_INIT ((uint8)0)
#define MAIN_MSG_ACCRPEDLRAT_MINRAW ((uint8)0)
#define MAIN_MSG_ACCRPEDLRAT_MAXRAW ((uint8)255)
#define MAIN_MSG_ACCRPEDLRAT_ISPHYS ((boolean)true)
#define MAIN_MSG_ACCRPEDLRAT_GAIN ((float)0.3937f)
#define MAIN_MSG_ACCRPEDLRAT_OFFSET ((float)0.0f)
#define MAIN_MSG_ACCRPEDLRAT_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ACCRPEDLRAT_MINPHYS ((float)0.0f)
#define MAIN_MSG_ACCRPEDLRAT_MAXPHYS ((float)99.9998f)
#define MAIN_MSG_BRKPEDLPSD_TYPE (uint8)
#define MAIN_MSG_BRKPEDLPSD_INIT ((uint8)0)
#define MAIN_MSG_BRKPEDLPSD_MINRAW ((uint8)0)
#define MAIN_MSG_BRKPEDLPSD_MAXRAW ((uint8)3)
#define MAIN_MSG_BRKPEDLPSD_ISPHYS ((boolean)false)
#define MAIN_MSG_BRKPEDLPSD_GAIN ((float)1.0f)
#define MAIN_MSG_BRKPEDLPSD_OFFSET ((float)0.0f)
#define MAIN_MSG_BRKPEDLPSD_NEUTRAL
#define MAIN_MSG_BRKPEDLPSD_MINPHYS ((float)0.0f)
#define MAIN_MSG_BRKPEDLPSD_MAXPHYS ((float)0.0f)
#define MAIN_MSG_ECM1ALIVECOUNTER_TYPE (uint8)
#define MAIN_MSG_ECM1ALIVECOUNTER_INIT ((uint8)0)
#define MAIN_MSG_ECM1ALIVECOUNTER_MINRAW ((uint8)0)
#define MAIN_MSG_ECM1ALIVECOUNTER_MAXRAW ((uint8)15)
#define MAIN_MSG_ECM1ALIVECOUNTER_ISPHYS ((boolean)true)
#define MAIN_MSG_ECM1ALIVECOUNTER_GAIN ((float)1.0f)
#define MAIN_MSG_ECM1ALIVECOUNTER_OFFSET ((float)0.0f)
#define MAIN_MSG_ECM1ALIVECOUNTER_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ECM1ALIVECOUNTER_MINPHYS ((float)0.0f)
#define MAIN_MSG_ECM1ALIVECOUNTER_MAXPHYS ((float)15.0f)
#define MAIN_MSG_ECM1CHECKSUM_TYPE (uint8)
#define MAIN_MSG_ECM1CHECKSUM_INIT ((uint8)0)
#define MAIN_MSG_ECM1CHECKSUM_MINRAW ((uint8)0)
#define MAIN_MSG_ECM1CHECKSUM_MAXRAW ((uint8)15)
#define MAIN_MSG_ECM1CHECKSUM_ISPHYS ((boolean)true)
#define MAIN_MSG_ECM1CHECKSUM_GAIN ((float)1.0f)
#define MAIN_MSG_ECM1CHECKSUM_OFFSET ((float)0.0f)
#define MAIN_MSG_ECM1CHECKSUM_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ECM1CHECKSUM_MINPHYS ((float)0.0f)
#define MAIN_MSG_ECM1CHECKSUM_MAXPHYS ((float)15.0f)
#define MAIN_MSG_ENGSTACT_TYPE (uint8)
#define MAIN_MSG_ENGSTACT_INIT ((uint8)0)
#define MAIN_MSG_ENGSTACT_MINRAW ((uint8)0)
#define MAIN_MSG_ENGSTACT_MAXRAW ((uint8)7)
#define MAIN_MSG_ENGSTACT_ISPHYS ((boolean)false)
#define MAIN_MSG_ENGSTACT_GAIN ((float)1.0f)
#define MAIN_MSG_ENGSTACT_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGSTACT_NEUTRAL
#define MAIN_MSG_ENGSTACT_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGSTACT_MAXPHYS ((float)0.0f)
#define MAIN_MSG_ENGTQINDACT_TYPE (uint16)
#define MAIN_MSG_ENGTQINDACT_INIT ((uint16)0)
#define MAIN_MSG_ENGTQINDACT_MINRAW ((uint16)0)
#define MAIN_MSG_ENGTQINDACT_MAXRAW ((uint16)2047)
#define MAIN_MSG_ENGTQINDACT_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGTQINDACT_GAIN ((float)0.5f)
#define MAIN_MSG_ENGTQINDACT_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGTQINDACT_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGTQINDACT_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGTQINDACT_MAXPHYS ((float)1023.0f)
#define MAIN_MSG_ENGTQINDDRVDMD_TYPE (uint16)
#define MAIN_MSG_ENGTQINDDRVDMD_INIT ((uint16)0)
#define MAIN_MSG_ENGTQINDDRVDMD_MINRAW ((uint16)0)
#define MAIN_MSG_ENGTQINDDRVDMD_MAXRAW ((uint16)2047)
#define MAIN_MSG_ENGTQINDDRVDMD_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGTQINDDRVDMD_GAIN ((float)0.5f)
#define MAIN_MSG_ENGTQINDDRVDMD_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGTQINDDRVDMD_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGTQINDDRVDMD_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGTQINDDRVDMD_MAXPHYS ((float)1023.0f)
#define MAIN_MSG_ENGTQLOSS_TYPE (uint16)
#define MAIN_MSG_ENGTQLOSS_INIT ((uint16)0)
#define MAIN_MSG_ENGTQLOSS_MINRAW ((uint16)0)
#define MAIN_MSG_ENGTQLOSS_MAXRAW ((uint16)2047)
#define MAIN_MSG_ENGTQLOSS_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGTQLOSS_GAIN ((float)0.5f)
#define MAIN_MSG_ENGTQLOSS_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGTQLOSS_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGTQLOSS_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGTQLOSS_MAXPHYS ((float)1023.0f)
#define MAIN_MSG_HVACCLUSTS_TYPE (boolean)
#define MAIN_MSG_HVACCLUSTS_INIT ((boolean)0)
#define MAIN_MSG_HVACCLUSTS_MINRAW ((boolean)0)
#define MAIN_MSG_HVACCLUSTS_MAXRAW ((boolean)1)
#define MAIN_MSG_HVACCLUSTS_ISPHYS ((boolean)false)
#define MAIN_MSG_HVACCLUSTS_GAIN ((float)1.0f)
#define MAIN_MSG_HVACCLUSTS_OFFSET ((float)0.0f)
#define MAIN_MSG_HVACCLUSTS_NEUTRAL
#define MAIN_MSG_HVACCLUSTS_MINPHYS ((float)0.0f)
#define MAIN_MSG_HVACCLUSTS_MAXPHYS ((float)0.0f)
#define MAIN_MSG_THROTTLECMDPOS_TYPE (uint8)
#define MAIN_MSG_THROTTLECMDPOS_INIT ((uint8)0)
#define MAIN_MSG_THROTTLECMDPOS_MINRAW ((uint8)0)
#define MAIN_MSG_THROTTLECMDPOS_MAXRAW ((uint8)255)
#define MAIN_MSG_THROTTLECMDPOS_ISPHYS ((boolean)true)
#define MAIN_MSG_THROTTLECMDPOS_GAIN ((float)0.3937f)
#define MAIN_MSG_THROTTLECMDPOS_OFFSET ((float)0.0f)
#define MAIN_MSG_THROTTLECMDPOS_NEUTRAL ((float)0.0f)
#define MAIN_MSG_THROTTLECMDPOS_MINPHYS ((float)0.0f)
#define MAIN_MSG_THROTTLECMDPOS_MAXPHYS ((float)99.9998f)
/* TCU / ECM2 Rx 10 ms  Init & Fail values */
#define MAIN_MSG_CRSCTRLCTRLACTV_TYPE (boolean)
#define MAIN_MSG_CRSCTRLCTRLACTV_INIT ((boolean)0)
#define MAIN_MSG_CRSCTRLCTRLACTV_MINRAW ((boolean)0)
#define MAIN_MSG_CRSCTRLCTRLACTV_MAXRAW ((boolean)1)
#define MAIN_MSG_CRSCTRLCTRLACTV_ISPHYS ((boolean)false)
#define MAIN_MSG_CRSCTRLCTRLACTV_GAIN ((float)1.0f)
#define MAIN_MSG_CRSCTRLCTRLACTV_OFFSET ((float)0.0f)
#define MAIN_MSG_CRSCTRLCTRLACTV_NEUTRAL
#define MAIN_MSG_CRSCTRLCTRLACTV_MINPHYS ((float)0.0f)
#define MAIN_MSG_CRSCTRLCTRLACTV_MAXPHYS ((float)0.0f)
#define MAIN_MSG_ECM2ALIVECOUNTER_TYPE (uint8)
#define MAIN_MSG_ECM2ALIVECOUNTER_INIT ((uint8)0)
#define MAIN_MSG_ECM2ALIVECOUNTER_MINRAW ((uint8)0)
#define MAIN_MSG_ECM2ALIVECOUNTER_MAXRAW ((uint8)15)
#define MAIN_MSG_ECM2ALIVECOUNTER_ISPHYS ((boolean)true)
#define MAIN_MSG_ECM2ALIVECOUNTER_GAIN ((float)1.0f)
#define MAIN_MSG_ECM2ALIVECOUNTER_OFFSET ((float)0.0f)
#define MAIN_MSG_ECM2ALIVECOUNTER_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ECM2ALIVECOUNTER_MINPHYS ((float)0.0f)
#define MAIN_MSG_ECM2ALIVECOUNTER_MAXPHYS ((float)15.0f)
#define MAIN_MSG_ECM2CHECKSUM_TYPE (uint8)
#define MAIN_MSG_ECM2CHECKSUM_INIT ((uint8)0)
#define MAIN_MSG_ECM2CHECKSUM_MINRAW ((uint8)0)
#define MAIN_MSG_ECM2CHECKSUM_MAXRAW ((uint8)15)
#define MAIN_MSG_ECM2CHECKSUM_ISPHYS ((boolean)true)
#define MAIN_MSG_ECM2CHECKSUM_GAIN ((float)1.0f)
#define MAIN_MSG_ECM2CHECKSUM_OFFSET ((float)0.0f)
#define MAIN_MSG_ECM2CHECKSUM_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ECM2CHECKSUM_MINPHYS ((float)0.0f)
#define MAIN_MSG_ECM2CHECKSUM_MAXPHYS ((float)15.0f)
#define MAIN_MSG_ENGN_TYPE (uint16)
#define MAIN_MSG_ENGN_INIT ((uint16)0)
#define MAIN_MSG_ENGN_MINRAW ((uint16)0)
#define MAIN_MSG_ENGN_MAXRAW ((uint16)65535)
#define MAIN_MSG_ENGN_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGN_GAIN ((float)0.5f)
#define MAIN_MSG_ENGN_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGN_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGN_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGN_MAXPHYS ((float)32767.0f)
#define MAIN_MSG_ENGNTGTIDLE_TYPE (uint16)
#define MAIN_MSG_ENGNTGTIDLE_INIT ((uint16)0)
#define MAIN_MSG_ENGNTGTIDLE_MINRAW ((uint16)0)
#define MAIN_MSG_ENGNTGTIDLE_MAXRAW ((uint16)65535)
#define MAIN_MSG_ENGNTGTIDLE_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGNTGTIDLE_GAIN ((float)0.5f)
#define MAIN_MSG_ENGNTGTIDLE_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGNTGTIDLE_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGNTGTIDLE_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGNTGTIDLE_MAXPHYS ((float)32767.0f)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_TYPE (uint8)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_INIT ((uint8)0)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_MINRAW ((uint8)0)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_MAXRAW ((uint8)3)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_ISPHYS ((boolean)false)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_GAIN ((float)1.0f)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_OFFSET ((float)0.0f)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_NEUTRAL
#define MAIN_MSG_GEARLMTFORLIGHTOFF_MINPHYS ((float)0.0f)
#define MAIN_MSG_GEARLMTFORLIGHTOFF_MAXPHYS ((float)0.0f)
/* TCU / ESC1 Rx 10 ms  Init & Fail values */
#define MAIN_MSG_ALGT_TYPE (sint16)
#define MAIN_MSG_ALGT_INIT ((sint16)0)
#define MAIN_MSG_ALGT_MINRAW ((sint16)-32768)
#define MAIN_MSG_ALGT_MAXRAW ((sint16)32767)
#define MAIN_MSG_ALGT_ISPHYS ((boolean)true)
#define MAIN_MSG_ALGT_GAIN ((float)0.00098f)
#define MAIN_MSG_ALGT_OFFSET ((float)0.0f)
#define MAIN_MSG_ALGT_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ALGT_MINPHYS ((float)-17.9997f)
#define MAIN_MSG_ALGT_MAXPHYS ((float)17.9987f)
#define MAIN_MSG_ESCFLGFLT_TYPE (boolean)
#define MAIN_MSG_ESCFLGFLT_INIT ((boolean)0)
#define MAIN_MSG_ESCFLGFLT_MINRAW ((boolean)0)
#define MAIN_MSG_ESCFLGFLT_MAXRAW ((boolean)1)
#define MAIN_MSG_ESCFLGFLT_ISPHYS ((boolean)false)
#define MAIN_MSG_ESCFLGFLT_GAIN ((float)1.0f)
#define MAIN_MSG_ESCFLGFLT_OFFSET ((float)0.0f)
#define MAIN_MSG_ESCFLGFLT_NEUTRAL
#define MAIN_MSG_ESCFLGFLT_MINPHYS ((float)0.0f)
#define MAIN_MSG_ESCFLGFLT_MAXPHYS ((float)0.0f)
#define MAIN_MSG_GEARSHIFTPREVN_TYPE (uint8)
#define MAIN_MSG_GEARSHIFTPREVN_INIT ((uint8)0)
#define MAIN_MSG_GEARSHIFTPREVN_MINRAW ((uint8)0)
#define MAIN_MSG_GEARSHIFTPREVN_MAXRAW ((uint8)3)
#define MAIN_MSG_GEARSHIFTPREVN_ISPHYS ((boolean)false)
#define MAIN_MSG_GEARSHIFTPREVN_GAIN ((float)1.0f)
#define MAIN_MSG_GEARSHIFTPREVN_OFFSET ((float)0.0f)
#define MAIN_MSG_GEARSHIFTPREVN_NEUTRAL
#define MAIN_MSG_GEARSHIFTPREVN_MINPHYS ((float)0.0f)
#define MAIN_MSG_GEARSHIFTPREVN_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TCSCTRLACTV_TYPE (boolean)
#define MAIN_MSG_TCSCTRLACTV_INIT ((boolean)0)
#define MAIN_MSG_TCSCTRLACTV_MINRAW ((boolean)0)
#define MAIN_MSG_TCSCTRLACTV_MAXRAW ((boolean)1)
#define MAIN_MSG_TCSCTRLACTV_ISPHYS ((boolean)false)
#define MAIN_MSG_TCSCTRLACTV_GAIN ((float)1.0f)
#define MAIN_MSG_TCSCTRLACTV_OFFSET ((float)0.0f)
#define MAIN_MSG_TCSCTRLACTV_NEUTRAL
#define MAIN_MSG_TCSCTRLACTV_MINPHYS ((float)0.0f)
#define MAIN_MSG_TCSCTRLACTV_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TCSFLGFLT_TYPE (boolean)
#define MAIN_MSG_TCSFLGFLT_INIT ((boolean)0)
#define MAIN_MSG_TCSFLGFLT_MINRAW ((boolean)0)
#define MAIN_MSG_TCSFLGFLT_MAXRAW ((boolean)1)
#define MAIN_MSG_TCSFLGFLT_ISPHYS ((boolean)false)
#define MAIN_MSG_TCSFLGFLT_GAIN ((float)1.0f)
#define MAIN_MSG_TCSFLGFLT_OFFSET ((float)0.0f)
#define MAIN_MSG_TCSFLGFLT_NEUTRAL
#define MAIN_MSG_TCSFLGFLT_MINPHYS ((float)0.0f)
#define MAIN_MSG_TCSFLGFLT_MAXPHYS ((float)0.0f)
/* TCU / ECM3 Rx 20 ms  Init & Fail values */
#define MAIN_MSG_ENGINESOAKTIME_TYPE (uint16)
#define MAIN_MSG_ENGINESOAKTIME_INIT ((uint16)0)
#define MAIN_MSG_ENGINESOAKTIME_MINRAW ((uint16)0)
#define MAIN_MSG_ENGINESOAKTIME_MAXRAW ((uint16)4095)
#define MAIN_MSG_ENGINESOAKTIME_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGINESOAKTIME_GAIN ((float)1.0f)
#define MAIN_MSG_ENGINESOAKTIME_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGINESOAKTIME_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGINESOAKTIME_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGINESOAKTIME_MAXPHYS ((float)4095.0f)
#define MAIN_MSG_ENGPAMBAIR_TYPE (uint8)
#define MAIN_MSG_ENGPAMBAIR_INIT ((uint8)0)
#define MAIN_MSG_ENGPAMBAIR_MINRAW ((uint8)0)
#define MAIN_MSG_ENGPAMBAIR_MAXRAW ((uint8)255)
#define MAIN_MSG_ENGPAMBAIR_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGPAMBAIR_GAIN ((float)1.0f)
#define MAIN_MSG_ENGPAMBAIR_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGPAMBAIR_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGPAMBAIR_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGPAMBAIR_MAXPHYS ((float)254.0f)
#define MAIN_MSG_ENGT_TYPE (uint8)
#define MAIN_MSG_ENGT_INIT ((uint8)0)
#define MAIN_MSG_ENGT_MINRAW ((uint8)0)
#define MAIN_MSG_ENGT_MAXRAW ((uint8)255)
#define MAIN_MSG_ENGT_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGT_GAIN ((float)0.75f)
#define MAIN_MSG_ENGT_OFFSET ((float)-48.0f)
#define MAIN_MSG_ENGT_NEUTRAL ((float)-48.0f)
#define MAIN_MSG_ENGT_MINPHYS ((float)-48.0f)
#define MAIN_MSG_ENGT_MAXPHYS ((float)142.5f)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_TYPE (boolean)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_INIT ((boolean)0)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_MINRAW ((boolean)0)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_MAXRAW ((boolean)1)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_ISPHYS ((boolean)false)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_GAIN ((float)1.0f)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_OFFSET ((float)0.0f)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_NEUTRAL
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_MINPHYS ((float)0.0f)
#define MAIN_MSG_OBDDRIVINGCYCLESTATUS_MAXPHYS ((float)0.0f)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_TYPE (boolean)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_INIT ((boolean)0)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_MINRAW ((boolean)0)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_MAXRAW ((boolean)1)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_ISPHYS ((boolean)false)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_GAIN ((float)1.0f)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_OFFSET ((float)0.0f)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_NEUTRAL
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_MINPHYS ((float)0.0f)
#define MAIN_MSG_OBDWARMUPCYCLESTATUS_MAXPHYS ((float)0.0f)
/* TCU / IP1 Rx 20 ms  Init & Fail values */
#define MAIN_MSG_AMBAIRTEMP_TYPE (uint8)
#define MAIN_MSG_AMBAIRTEMP_INIT ((uint8)0)
#define MAIN_MSG_AMBAIRTEMP_MINRAW ((uint8)0)
#define MAIN_MSG_AMBAIRTEMP_MAXRAW ((uint8)255)
#define MAIN_MSG_AMBAIRTEMP_ISPHYS ((boolean)true)
#define MAIN_MSG_AMBAIRTEMP_GAIN ((float)0.75f)
#define MAIN_MSG_AMBAIRTEMP_OFFSET ((float)-48.0f)
#define MAIN_MSG_AMBAIRTEMP_NEUTRAL ((float)-48.0f)
#define MAIN_MSG_AMBAIRTEMP_MINPHYS ((float)-48.0f)
#define MAIN_MSG_AMBAIRTEMP_MAXPHYS ((float)142.5f)
/* ========================================================================== */
/* CAN Tx MSG Init values                                                     */
/* ========================================================================== */
/* TCU / TCU1 Tx 10 ms  Init & Fail values */
#define MAIN_MSG_ENGNIDLEREQ_TYPE (uint8)
#define MAIN_MSG_ENGNIDLEREQ_INIT ((uint8)0)
#define MAIN_MSG_ENGNIDLEREQ_MINRAW ((uint8)0)
#define MAIN_MSG_ENGNIDLEREQ_MAXRAW ((uint8)255)
#define MAIN_MSG_ENGNIDLEREQ_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGNIDLEREQ_GAIN ((float)2.0f)
#define MAIN_MSG_ENGNIDLEREQ_OFFSET ((float)600.0f)
#define MAIN_MSG_ENGNIDLEREQ_NEUTRAL ((float)600.0f)
#define MAIN_MSG_ENGNIDLEREQ_MINPHYS ((float)600.0f)
#define MAIN_MSG_ENGNIDLEREQ_MAXPHYS ((float)1108.0f)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_TYPE (uint8)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_INIT ((uint8)0)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_MINRAW ((uint8)0)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_MAXRAW ((uint8)255)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_GAIN ((float)2.0f)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGTQINDDECREQDBYTRSM_MAXPHYS ((float)508.0f)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_TYPE (uint8)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_INIT ((uint8)0)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_MINRAW ((uint8)0)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_MAXRAW ((uint8)255)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_GAIN ((float)2.0f)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_MINPHYS ((float)0.0f)
#define MAIN_MSG_ENGTQINDLMTDBYTRSM_MAXPHYS ((float)508.0f)
#define MAIN_MSG_TRSMCLUSTACT_TYPE (uint8)
#define MAIN_MSG_TRSMCLUSTACT_INIT ((uint8)0)
#define MAIN_MSG_TRSMCLUSTACT_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMCLUSTACT_MAXRAW ((uint8)3)
#define MAIN_MSG_TRSMCLUSTACT_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMCLUSTACT_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMCLUSTACT_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMCLUSTACT_NEUTRAL
#define MAIN_MSG_TRSMCLUSTACT_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMCLUSTACT_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMMSGCNT_TYPE (uint8)
#define MAIN_MSG_TRSMMSGCNT_INIT ((uint8)0)
#define MAIN_MSG_TRSMMSGCNT_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMMSGCNT_MAXRAW ((uint8)15)
#define MAIN_MSG_TRSMMSGCNT_ISPHYS ((boolean)true)
#define MAIN_MSG_TRSMMSGCNT_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMMSGCNT_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMMSGCNT_NEUTRAL ((float)0.0f)
#define MAIN_MSG_TRSMMSGCNT_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMMSGCNT_MAXPHYS ((float)15.0f)
#define MAIN_MSG_TRSMNINP_TYPE (uint16)
#define MAIN_MSG_TRSMNINP_INIT ((uint16)0)
#define MAIN_MSG_TRSMNINP_MINRAW ((uint16)0)
#define MAIN_MSG_TRSMNINP_MAXRAW ((uint16)65535)
#define MAIN_MSG_TRSMNINP_ISPHYS ((boolean)true)
#define MAIN_MSG_TRSMNINP_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMNINP_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMNINP_NEUTRAL ((float)0.0f)
#define MAIN_MSG_TRSMNINP_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMNINP_MAXPHYS ((float)65534.0f)
/* TCU / TCU2 Tx 10 ms  Init & Fail values */
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_TYPE (uint8)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_INIT ((uint8)0)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_MINRAW ((uint8)0)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_MAXRAW ((uint8)255)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_ISPHYS ((boolean)true)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_GAIN ((float)2.0f)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_OFFSET ((float)0.0f)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_NEUTRAL ((float)0.0f)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_MINPHYS ((float)2.0f)
#define MAIN_MSG_ENGTQINDINCREQDBYTRSM_MAXPHYS ((float)510.0f)
#define MAIN_MSG_TRSMFLGFLT_TYPE (uint8)
#define MAIN_MSG_TRSMFLGFLT_INIT ((uint8)0)
#define MAIN_MSG_TRSMFLGFLT_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMFLGFLT_MAXRAW ((uint8)3)
#define MAIN_MSG_TRSMFLGFLT_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMFLGFLT_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMFLGFLT_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMFLGFLT_NEUTRAL
#define MAIN_MSG_TRSMFLGFLT_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMFLGFLT_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_TYPE (boolean)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_INIT ((boolean)0)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_MINRAW ((boolean)0)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_MAXRAW ((boolean)1)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_NEUTRAL
#define MAIN_MSG_TRSMFLGSHIFTPROGS_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMFLGSHIFTPROGS_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMGEARACT_TYPE (uint8)
#define MAIN_MSG_TRSMGEARACT_INIT ((uint8)0)
#define MAIN_MSG_TRSMGEARACT_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMGEARACT_MAXRAW ((uint8)15)
#define MAIN_MSG_TRSMGEARACT_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMGEARACT_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMGEARACT_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMGEARACT_NEUTRAL
#define MAIN_MSG_TRSMGEARACT_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMGEARACT_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMGEARTAR_TYPE (uint8)
#define MAIN_MSG_TRSMGEARTAR_INIT ((uint8)0)
#define MAIN_MSG_TRSMGEARTAR_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMGEARTAR_MAXRAW ((uint8)15)
#define MAIN_MSG_TRSMGEARTAR_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMGEARTAR_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMGEARTAR_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMGEARTAR_NEUTRAL
#define MAIN_MSG_TRSMGEARTAR_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMGEARTAR_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMMILREQ_TYPE (boolean)
#define MAIN_MSG_TRSMMILREQ_INIT ((boolean)0)
#define MAIN_MSG_TRSMMILREQ_MINRAW ((boolean)0)
#define MAIN_MSG_TRSMMILREQ_MAXRAW ((boolean)1)
#define MAIN_MSG_TRSMMILREQ_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMMILREQ_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMMILREQ_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMMILREQ_NEUTRAL
#define MAIN_MSG_TRSMMILREQ_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMMILREQ_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMSTGEARLVR_TYPE (uint8)
#define MAIN_MSG_TRSMSTGEARLVR_INIT ((uint8)0)
#define MAIN_MSG_TRSMSTGEARLVR_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMSTGEARLVR_MAXRAW ((uint8)15)
#define MAIN_MSG_TRSMSTGEARLVR_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMSTGEARLVR_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMSTGEARLVR_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMSTGEARLVR_NEUTRAL
#define MAIN_MSG_TRSMSTGEARLVR_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMSTGEARLVR_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMSTGEARMODE_TYPE (uint8)
#define MAIN_MSG_TRSMSTGEARMODE_INIT ((uint8)0)
#define MAIN_MSG_TRSMSTGEARMODE_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMSTGEARMODE_MAXRAW ((uint8)7)
#define MAIN_MSG_TRSMSTGEARMODE_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMSTGEARMODE_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMSTGEARMODE_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMSTGEARMODE_NEUTRAL
#define MAIN_MSG_TRSMSTGEARMODE_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMSTGEARMODE_MAXPHYS ((float)0.0f)
#define MAIN_MSG_TRSMTOIL_TYPE (uint8)
#define MAIN_MSG_TRSMTOIL_INIT ((uint8)0)
#define MAIN_MSG_TRSMTOIL_MINRAW ((uint8)0)
#define MAIN_MSG_TRSMTOIL_MAXRAW ((uint8)255)
#define MAIN_MSG_TRSMTOIL_ISPHYS ((boolean)true)
#define MAIN_MSG_TRSMTOIL_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMTOIL_OFFSET ((float)-40.0f)
#define MAIN_MSG_TRSMTOIL_NEUTRAL ((float)-40.0f)
#define MAIN_MSG_TRSMTOIL_MINPHYS ((float)-40.0f)
#define MAIN_MSG_TRSMTOIL_MAXPHYS ((float)214.0f)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_TYPE (boolean)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_INIT ((boolean)0)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_MINRAW ((boolean)0)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_MAXRAW ((boolean)1)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_ISPHYS ((boolean)false)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_GAIN ((float)1.0f)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_OFFSET ((float)0.0f)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_NEUTRAL
#define MAIN_MSG_TRSMTOILWRNLMPREQ_MINPHYS ((float)0.0f)
#define MAIN_MSG_TRSMTOILWRNLMPREQ_MAXPHYS ((float)0.0f)



/* ========================================================================== */
/* TCU CAN API define                                                 */
/* ========================================================================== */
//Message 0x211: ABS1 , Direction Rx , signal Read
#define CANAPI_udtRead_WhlSpdFrntLeRaw() MAIN_MSGf32WhlSpdFrntLeRawPhys
#define CANAPI_udtRead_WhlSpdFrntRiRaw() MAIN_MSGf32WhlSpdFrntRiRawPhys
#define CANAPI_udtRead_WhlSpdReLeRaw() MAIN_MSGf32WhlSpdReLeRawPhys
#define CANAPI_udtRead_WhlSpdReRiRaw() MAIN_MSGf32WhlSpdReRiRawPhys

//Message 0x221: ABS2 , Direction Rx , signal Read
#define CANAPI_udtRead_AbsCtrlActv() MAIN_MSGbAbsCtrlActv
#define CANAPI_udtRead_AbsFlgFlt() MAIN_MSGbAbsFlgFlt
#define CANAPI_udtRead_EbdFlgFlt() MAIN_MSGbEbdFlgFlt

//Message 0x111: ECM1 , Direction Rx , signal Read
#define CANAPI_udtRead_AccrPedlRat() MAIN_MSGf32AccrPedlRatPhys
#define CANAPI_udtRead_BrkPedlPsd() MAIN_MSGu8BrkPedlPsd
#define CANAPI_udtRead_ECM1AliveCounter() MAIN_MSGu8ECM1AliveCounter
#define CANAPI_udtRead_ECM1Checksum() MAIN_MSGu8ECM1Checksum
#define CANAPI_udtRead_EngStAct() MAIN_MSGu8EngStAct
#define CANAPI_udtRead_EngTqIndAct() MAIN_MSGf32EngTqIndActPhys
#define CANAPI_udtRead_EngTqIndDrvDmd() MAIN_MSGf32EngTqIndDrvDmdPhys
#define CANAPI_udtRead_EngTqLoss() MAIN_MSGf32EngTqLossPhys
#define CANAPI_udtRead_HvacCluSts() MAIN_MSGbHvacCluSts
#define CANAPI_udtRead_ThrottleCmdPos() MAIN_MSGf32ThrottleCmdPosPhys

//Message 0x121: ECM2 , Direction Rx , signal Read
#define CANAPI_udtRead_CrsCtrlCtrlActv() MAIN_MSGbCrsCtrlCtrlActv
#define CANAPI_udtRead_ECM2AliveCounter() MAIN_MSGu8ECM2AliveCounter
#define CANAPI_udtRead_ECM2Checksum() MAIN_MSGu8ECM2Checksum
#define CANAPI_udtRead_EngN() MAIN_MSGf32EngNPhys
#define CANAPI_udtRead_EngNTgtIdle() MAIN_MSGf32EngNTgtIdlePhys
#define CANAPI_udtRead_GearLmtForLightOff() MAIN_MSGu8GearLmtForLightOff

//Message 0x231: ESC1 , Direction Rx , signal Read
#define CANAPI_udtRead_Algt() MAIN_MSGf32AlgtPhys
#define CANAPI_udtRead_EscFlgFlt() MAIN_MSGbEscFlgFlt
#define CANAPI_udtRead_GearShiftPrevn() MAIN_MSGu8GearShiftPrevn
#define CANAPI_udtRead_TcsCtrlActv() MAIN_MSGbTcsCtrlActv
#define CANAPI_udtRead_TcsFlgFlt() MAIN_MSGbTcsFlgFlt

//Message 0x261: ECM3 , Direction Rx , signal Read
#define CANAPI_udtRead_EngineSoakTime() MAIN_MSGu16EngineSoakTime
#define CANAPI_udtRead_EngPAmbAir() MAIN_MSGu8EngPAmbAir
#define CANAPI_udtRead_EngT() MAIN_MSGf32EngTPhys
#define CANAPI_udtRead_OBDDrivingCycleStatus() MAIN_MSGbOBDDrivingCycleStatus
#define CANAPI_udtRead_OBDWarmUpCycleStatus() MAIN_MSGbOBDWarmUpCycleStatus

//Message 0x281: IP1 , Direction Rx , signal Read
#define CANAPI_udtRead_AmbAirTemp() MAIN_MSGf32AmbAirTempPhys

//Message 0x141: TCU1 , Direction Tx , signal Write
#define CANAPI_udtWrite_EngNIdleReq(udtValue) (MAIN_MSGf32EngNIdleReqPhys=udtValue)
#define CANAPI_udtWrite_EngTqIndDecReqdByTrsm(udtValue) (MAIN_MSGf32EngTqIndDecReqdByTrsmPhys=udtValue)
#define CANAPI_udtWrite_EngTqIndLmtdByTrsm(udtValue) (MAIN_MSGf32EngTqIndLmtdByTrsmPhys=udtValue)
#define CANAPI_udtWrite_TrsmCluStAct(udtValue) (MAIN_MSGu8TrsmCluStAct=udtValue)
#define CANAPI_udtWrite_TrsmMsgCnt(udtValue) (MAIN_MSGf32TrsmMsgCntPhys=udtValue)
#define CANAPI_udtWrite_TrsmNInp(udtValue) (MAIN_MSGf32TrsmNInpPhys=udtValue)

//Message 0x151: TCU2 , Direction Tx , signal Write
#define CANAPI_udtWrite_EngTqIndIncReqdByTrsm(udtValue) (MAIN_MSGf32EngTqIndIncReqdByTrsmPhys=udtValue)
#define CANAPI_udtWrite_TrsmFlgFlt(udtValue) (MAIN_MSGu8TrsmFlgFlt=udtValue)
#define CANAPI_udtWrite_TrsmFlgShiftProgs(udtValue) (MAIN_MSGbTrsmFlgShiftProgs=udtValue)
#define CANAPI_udtWrite_TrsmGearAct(udtValue) (MAIN_MSGu8TrsmGearAct=udtValue)
#define CANAPI_udtWrite_TrsmGearTar(udtValue) (MAIN_MSGu8TrsmGearTar=udtValue)
#define CANAPI_udtWrite_TrsmMILReq(udtValue) (MAIN_MSGbTrsmMILReq=udtValue)
#define CANAPI_udtWrite_TrsmStGearLvr(udtValue) (MAIN_MSGu8TrsmStGearLvr=udtValue)
#define CANAPI_udtWrite_TrsmStGearMode(udtValue) (MAIN_MSGu8TrsmStGearMode=udtValue)
#define CANAPI_udtWrite_TrsmTOil(udtValue) (MAIN_MSGf32TrsmTOilPhys=udtValue)
#define CANAPI_udtWrite_TrsmTOilWrnLmpReq(udtValue) (MAIN_MSGbTrsmTOilWrnLmpReq=udtValue)


/**********************************************************************************************************************/
/* PUBLIC MACRO FUNCTIONS                                                                                             */
/**********************************************************************************************************************/
#define MAIN_MSG_SCALE_SIGNAL_RAW2PHYS(snSignalName, signalValue)\
   MAIN_MSG_SCALE_SIGNAL_RAW2PHYS_I(                             \
      snSignalName,                                              \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, GAIN),             \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, OFFSET),           \
      signalValue)

#define MAIN_MSG_SCALE_SIGNAL_PHYS2RAW(snSignalName, signalValue)\
   MAIN_MSG_SCALE_SIGNAL_PHYS2RAW_I(                             \
      snSignalName,                                              \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, GAIN),             \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, OFFSET),           \
      signalValue)

#define MAIN_MSG_CLAMP_SIGNAL_PHYS(snSignalName, signalValue)\
   MAIN_MSG_CLAMP_SIGNAL_I(                                      \
      snSignalName,                                              \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, MINPHYS),          \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, MAXPHYS),          \
      signalValue)

#define MAIN_MSG_CLAMP_SIGNAL_RAW(snSignalName, signalValue)     \
   MAIN_MSG_CLAMP_SIGNAL_I(                                      \
      snSignalName,                                              \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, MINRAW),           \
      MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, MAXRAW),           \
      signalValue)


#define CANAPI_udtRead(snSignalName) \
   (CANAPI_udtRead_##snSignalName())

#define CANAPI_udtWrite(snSignalName, udtValue) \
   CANAPI_udtWrite_##snSignalName(udtValue)

/**********************************************************************************************************************/
/* PRIVATE MACRO FUNCTIONS                                                                                            */
/**********************************************************************************************************************/
#define MAIN_MSG_SCALE_SIGNAL_RAW2PHYS_I(snSignalName, signalGain, signalOffset, signalValue)\
   ((float32) ((signalValue) * (signalGain)) + (signalOffset))

#define MAIN_MSG_SCALE_SIGNAL_PHYS2RAW_I(snSignalName, signalGain, signalOffset, signalValue)\
   ((float32) (signalValue - signalOffset) * (1/signalGain))

#define MAIN_MSG_CLAMP_SIGNAL_I(snSignalName, signalMin, signalMax, signalValue)\
   MATHSRV_udtCLAMP(signalValue, signalMin, signalMax)

#define MAIN_MSG_GET_SIGNAL_PARAM(snSignalName, snParam)\
   (MAIN_MSG_##snSignalName##_##snParam)



/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/
#define MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"

void MAIN_MSGvidInit(void);

/******************************************************************************/
/******************************************************************************/
/******************************************************************************/
/* FUNCTIONS DECLARATION                                                      */
/******************************************************************************/
/* ========================================================================== */
/* CAN TCU/ Functions Rx                                                   */
/* ========================================================================== */
void MAIN_MSGvidRxABS1(
   float   *Arg_f32WhlSpdFrntLeRawPhys,
   uint16  *Arg_u16WhlSpdFrntLeRawRaw,
   float   *Arg_f32WhlSpdFrntRiRawPhys,
   uint16  *Arg_u16WhlSpdFrntRiRawRaw,
   float   *Arg_f32WhlSpdReLeRawPhys,
   uint16  *Arg_u16WhlSpdReLeRawRaw,
   float   *Arg_f32WhlSpdReRiRawPhys,
   uint16  *Arg_u16WhlSpdReRiRawRaw);


void MAIN_MSGvidRxABS2(
   boolean *Arg_bAbsCtrlActvRaw,
   boolean *Arg_bAbsFlgFltRaw,
   boolean *Arg_bEbdFlgFltRaw);


void MAIN_MSGvidRxECM1(
   float   *Arg_f32AccrPedlRatPhys,
   uint8   *Arg_u8AccrPedlRatRaw,
   uint8   *Arg_u8BrkPedlPsdRaw,
   float   *Arg_f32ECM1AliveCounterPhys,
   uint8   *Arg_u8ECM1AliveCounterRaw,
   float   *Arg_f32ECM1ChecksumPhys,
   uint8   *Arg_u8ECM1ChecksumRaw,
   uint8   *Arg_u8EngStActRaw,
   float   *Arg_f32EngTqIndActPhys,
   uint16  *Arg_u16EngTqIndActRaw,
   float   *Arg_f32EngTqIndDrvDmdPhys,
   uint16  *Arg_u16EngTqIndDrvDmdRaw,
   float   *Arg_f32EngTqLossPhys,
   uint16  *Arg_u16EngTqLossRaw,
   boolean *Arg_bHvacCluStsRaw,
   float   *Arg_f32ThrottleCmdPosPhys,
   uint8   *Arg_u8ThrottleCmdPosRaw);


void MAIN_MSGvidRxECM2(
   boolean *Arg_bCrsCtrlCtrlActvRaw,
   float   *Arg_f32ECM2AliveCounterPhys,
   uint8   *Arg_u8ECM2AliveCounterRaw,
   float   *Arg_f32ECM2ChecksumPhys,
   uint8   *Arg_u8ECM2ChecksumRaw,
   float   *Arg_f32EngNPhys,
   uint16  *Arg_u16EngNRaw,
   float   *Arg_f32EngNTgtIdlePhys,
   uint16  *Arg_u16EngNTgtIdleRaw,
   uint8   *Arg_u8GearLmtForLightOffRaw);


void MAIN_MSGvidRxESC1(
   float   *Arg_f32AlgtPhys,
   sint16  *Arg_s16AlgtRaw,
   boolean *Arg_bEscFlgFltRaw,
   uint8   *Arg_u8GearShiftPrevnRaw,
   boolean *Arg_bTcsCtrlActvRaw,
   boolean *Arg_bTcsFlgFltRaw);


void MAIN_MSGvidRxECM3(
   float   *Arg_f32EngineSoakTimePhys,
   uint16  *Arg_u16EngineSoakTimeRaw,
   float   *Arg_f32EngPAmbAirPhys,
   uint8   *Arg_u8EngPAmbAirRaw,
   float   *Arg_f32EngTPhys,
   uint8   *Arg_u8EngTRaw,
   boolean *Arg_bOBDDrivingCycleStatusRaw,
   boolean *Arg_bOBDWarmUpCycleStatusRaw);


void MAIN_MSGvidRxIP1(
   float   *Arg_f32AmbAirTempPhys,
   uint8   *Arg_u8AmbAirTempRaw);


/* ========================================================================== */
/* CAN TCU/ Functions Tx                                                   */
/* ========================================================================== */
void MAIN_MSGvidTxTCU1(
   float   Arg_f32EngNIdleReqPhys,
   uint8  *Arg_u8EngNIdleReqRaw,
   float   Arg_f32EngTqIndDecReqdByTrsmPhys,
   uint8  *Arg_u8EngTqIndDecReqdByTrsmRaw,
   float   Arg_f32EngTqIndLmtdByTrsmPhys,
   uint8  *Arg_u8EngTqIndLmtdByTrsmRaw,
   uint8   Arg_u8TrsmCluStActRaw,
   float   Arg_f32TrsmMsgCntPhys,
   uint8  *Arg_u8TrsmMsgCntRaw,
   float   Arg_f32TrsmNInpPhys,
   uint16 *Arg_u16TrsmNInpRaw);


void MAIN_MSGvidTxTCU2(
   float   Arg_f32EngTqIndIncReqdByTrsmPhys,
   uint8  *Arg_u8EngTqIndIncReqdByTrsmRaw,
   uint8   Arg_u8TrsmFlgFltRaw,
   boolean Arg_bTrsmFlgShiftProgsRaw,
   uint8   Arg_u8TrsmGearActRaw,
   uint8   Arg_u8TrsmGearTarRaw,
   boolean Arg_bTrsmMILReqRaw,
   uint8   Arg_u8TrsmStGearLvrRaw,
   uint8   Arg_u8TrsmStGearModeRaw,
   float   Arg_f32TrsmTOilPhys,
   uint8  *Arg_u8TrsmTOilRaw,
   boolean Arg_bTrsmTOilWrnLmpReqRaw);


void MAIN_MSGvidRx_Tsk10ms( void );
void MAIN_MSGvidRx_Tsk20ms( void );
void MAIN_MSGvidRx_Tsk50ms( void );
void MAIN_MSGvidRx_Tsk100ms( void );
void MAIN_MSGvidRx_Tsk200ms( void );
void MAIN_MSGvidRx_Tsk1000ms( void );
void MAIN_MSGvidTx_Tsk10ms( void );
void MAIN_MSGvidTx_Tsk20ms( void );
void MAIN_MSGvidTx_Tsk50ms( void );
void MAIN_MSGvidTx_Tsk100ms( void );
void MAIN_MSGvidTx_Tsk200ms( void );
void MAIN_MSGvidTx_Tsk1000ms( void );


#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"

#endif /* MAIN_MSG_H */
/*------------------------------ end of file ------------------------------*/
