/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : EVP                                                                                             */
/*                                                                                                                    */
/* !Component       : EVP                                                                                             */
/* !Description     : EVP unit                                                                                        */
/*                                                                                                                    */
/* !Module          : EVP                                                                                             */
/* !Description     : API of EVP unit                                                                                 */
/*                                                                                                                    */
/* !File            : EVP_API.h                                                                                       */
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
/* 1 / EVP_u32GET_TIMEOUT_START                                                                                       */
/* 2 / EVP_bTIMEOUT_ELAPSED                                                                                           */
/* 3 / EVP_vidSET_OUTPUT                                                                                              */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/

#ifndef EVP_API_H
#define EVP_API_H

#include "Std_Types.h"
#include "EVP_i.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/

#define EVP_SetDuty(Channel,Duty)        EVP_SetDuty_##Channel(Duty)
#define EVP_SetDuty_GRP_0_IDX_0(Duty)    EVP_au16Duty[EVP_u8GRP_0_IDX][0]=Duty
#define EVP_SetDuty_GRP_0_IDX_1(Duty)    EVP_au16Duty[EVP_u8GRP_0_IDX][1]=Duty
#define EVP_SetDuty_GRP_0_IDX_2(Duty)    EVP_au16Duty[EVP_u8GRP_0_IDX][2]=Duty
#define EVP_SetDuty_GRP_1_IDX_0(Duty)    EVP_au16Duty[EVP_u8GRP_1_IDX][0]=Duty
#define EVP_SetDuty_GRP_1_IDX_1(Duty)    EVP_au16Duty[EVP_u8GRP_1_IDX][1]=Duty
#define EVP_SetDuty_GRP_1_IDX_2(Duty)    EVP_au16Duty[EVP_u8GRP_1_IDX][2]=Duty
#define EVP_SetDuty_GRP_2_IDX_0(Duty)    EVP_au16Duty[EVP_u8GRP_2_IDX][0]=Duty
#define EVP_SetDuty_GRP_2_IDX_1(Duty)    EVP_au16Duty[EVP_u8GRP_2_IDX][1]=Duty
#define EVP_SetDuty_GRP_2_IDX_2(Duty)    EVP_au16Duty[EVP_u8GRP_2_IDX][2]=Duty
#define EVP_SetDuty_GRP_3_IDX_0(Duty)    EVP_au16Duty[EVP_u8GRP_3_IDX][0]=Duty
#define EVP_SetDuty_GRP_3_IDX_1(Duty)    EVP_au16Duty[EVP_u8GRP_3_IDX][1]=Duty
#define EVP_SetDuty_GRP_3_IDX_2(Duty)    EVP_au16Duty[EVP_u8GRP_3_IDX][2]=Duty

#define EVP_SetPrd(Channel,Prd)          EVP_SetPrd_##Channel(Prd)
#define EVP_SetPrd_GRP_0(Prd)            EVP_au32Prd[0]=Prd
#define EVP_SetPrd_GRP_1(Prd)            EVP_au32Prd[1]=Prd
#define EVP_SetPrd_GRP_2(Prd)            EVP_au32Prd[2]=Prd
#define EVP_SetPrd_GRP_3(Prd)            EVP_au32Prd[3]=Prd

#define EVP_u32TOM_CTRL_CFG_PERIOD \
   ( GTM_TOM_CHx_CTRL_SL_LOW_LEVEL | GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL \
   | GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_CM0_MATCH | GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_CCU0 \
   | GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_DISA | GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_DISA \
   | GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_DISA)

#define EVP_u32TOM_CTRL_CFG_PWM \
   ( GTM_TOM_CHx_CTRL_SL_LOW_LEVEL | GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL \
   | GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_TRIG_NM1 | GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_NM1 \
   | GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_DISA | GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_DISA \
   | GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_DISA)

#define EVP_u32TOM_CTRL_CFG_DIAG \
   ( GTM_TOM_CHx_CTRL_SL_LOW_LEVEL | GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL \
   | GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_TRIG_NM1 | GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_NM1 \
   | GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_DISA | GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_DISA \
   | GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_DISA)
   
#define EVP_u32TOM_CTRL_CFG_ADC_TRIG \
   ( GTM_TOM_CHx_CTRL_SL_HIGH_LEVEL | GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL \
   | GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_TRIG_NM1 | GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_NM1 \
   | GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_DISA | GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_DISA \
   | GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_DISA)
   
#define EVP_u32TOM_CTRL_CFG_ADC_TRIG_0 \
   ( GTM_TOM_CHx_CTRL_SL_HIGH_LEVEL | GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL \
   | GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_CM0_MATCH | GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_CCU0 \
   | GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_DISA | GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_DISA \
   | GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_DISA)
   
 #define EVP_u32TOM_CTRL_CFG_ADC_TRIG_1 \
   ( GTM_TOM_CHx_CTRL_SL_LOW_LEVEL | GTM_TOM_CHx_CTRL_CLK_SRC_SR_FXCLKSEL \
   | GTM_TOM_CHx_CTRL_RST_CCU0_RST_ON_TRIG_NM1 | GTM_TOM_CHx_CTRL_TRIGOUT_TRIG_NM1 \
   | GTM_TOM_CHx_CTRL_OSM_ONE_SHOT_MODE_DISA | GTM_TOM_CHx_CTRL_SPEM_SPE_MODE_DISA \
   | GTM_TOM_CHx_CTRL_GCM_GATED_COUNTER_MODE_DISA)

#define EVP_u16CLOCK_MHZ        100u
#define EVP_u16DELAY_1MICROS    EVP_u16CLOCK_MHZ
#define EVP_u16DELAY_2MICROS    (2u * EVP_u16DELAY_1MICROS)
#define EVP_u16DELAY_5MICROS    (5u * EVP_u16DELAY_1MICROS)   
#define EVP_u16DEFAULT_PERIOD   (200u * (EVP_u16DELAY_1MICROS))
#define EVP_u16DIAG_DLY_TO_DIAG (90u * EVP_u16DELAY_1MICROS)


/**********************************************************************************************************************/
/* TYPEDEF                                                                                                            */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/
  
/******************************************************************************/
/* CONSTANTS DECLARATION                                                      */
/******************************************************************************/

/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/

/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/
/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description : Get the start value for a timeout                                                                   */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
#define EVP_u32GET_TIMEOUT_START() ((uint32)MODULE_STM0.TIM0.U)

/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description : Checks if the specified timeout is elapsed                                                          */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
/* !Comment: Wait for the specified time (in us) */
#define EVP_bTIMEOUT_ELAPSED(u32Start, u32Dur)  \
   ( (((uint32)((uint32)MODULE_STM0.TIM0.U  - (u32Start))) < ((uint32)(EVP_u32SYSTEM_CLOCK_MHZ * (u32Dur)))) \
   ? FALSE \
   : TRUE)

/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/
#define EVP_START_SEC_CODE
#include "EVP_MemMap.h"

//extern boolean EVP_bSetPwm(uint8 u8GrpIdx, uint32 u32Prd, const uint16 * pu16Duty);

#define EVP_STOP_SEC_CODE
#include "EVP_MemMap.h"

#endif /* EVP_API_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
