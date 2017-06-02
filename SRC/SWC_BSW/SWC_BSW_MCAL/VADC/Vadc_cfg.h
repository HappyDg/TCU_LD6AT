/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : VADC                                                                                            */
/*                                                                                                                    */
/* !Component       : VADC                                                                                            */
/* !Description     : VADC unit                                                                                       */
/*                                                                                                                    */
/* !Module          : VADC                                                                                            */
/* !Description     : API of ADC                                                                                      */
/*                                                                                                                    */
/* !File            : VADC.h                                                                                          */
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

#ifndef VADC_CFG_H
#define VADC_CFG_H

#include "Std_Types.h"
#include "VADC_L.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/

#define VADC_snAN_DIAG_SOL_SW_1_CH                             AN03

#define VADC_snAN_DIAG_SOL_SW_2_CH                               AN02

#define VADC_snAN_TOSS_CH                                 AN04

#define VADC_snAN_C4_SPD_SNS_CH                             AN06

#define VADC_snAN_RESERVED_TEMP_1_CH            AN08

#define VADC_snAN_PRI_OIL_TEMP_CH                   AN09

#define VADC_snAN_TMP_PCB_CH                     AN10

#define VADC_snAN_G4_SPD_SNS_CH                  AN11

#define VADC_snAN_P5V_INTERNAL_CH                              AN12

#define VADC_snAN_P5V_SNS_SUP_1_CH                                AN13

#define VADC_snAN_VCC_3V3_SUP_CH                              AN14

#define VADC_snAN_P9V_SNS_SUP_CH                            AN15

#define VADC_snAN_VBAT_P_SW_SUP_CH                  AN17

#define VADC_snAN_T15_IGN_CH                              AN18

#define VADC_snAN_T30_BATT_CH                              AN19

#define VADC_snAN_RESERVED_1_CH                            AN22

#define VADC_snAN_RESERVED_2_CH                            AN21

#define VADC_snAN_PRI_OIL_PRES_CH                            AN23


#define VADC_u32SYSTEM_CLOCK_MHZ 100

#define VADC_u8AN_DIAG_SOL_SW_1_RES_IDX                       1
#define VADC_u8AN_DIAG_SOL_SW_2_RES_IDX                               0
#define VADC_u8AN_TOSS_RES_IDX                             2
#define VADC_u8AN_C4_SPD_SNS_RES_IDX                               3
#define VADC_u8AN_RESERVED_TEMP_1_RES_IDX              4
#define VADC_u8AN_PRI_OIL_TEMP_RES_IDX                                 5
#define VADC_u8AN_TMP_PCB_RES_IDX                       6
#define VADC_u8AN_G4_SPD_SNS_RES_IDX                             7
#define VADC_u8AN_P5V_INTERNAL_RES_IDX                               8
#define VADC_u8AN_P5V_SNS_SUP_1_RES_IDX                                9
#define VADC_u8AN_VCC_3V3_SUP_RES_IDX                                10
#define VADC_u8AN_P9V_SNS_SUP_RES_IDX                              11
#define VADC_u8AN_VBAT_P_SW_SUP_RES_IDX                          12
#define VADC_u8AN_T30_BATT_RES_IDX                                13
#define VADC_u8AN_T15_IGN_RES_IDX                  14
#define VADC_u8AN_RESERVED_1_RES_IDX                   16
#define VADC_u8AN_RESERVED_2_RES_IDX            15
#define VADC_u8AN_PRI_OIL_PRES_RES_IDX            17




#define VADC_u8NB_CONV_RES                                   30
#define VADC_u32SYSTEM_CLOCK_MHZ 100

#define VADC_u32CFG_TIMEOUT_TMR_CLK_MHZ (100)
#define VADC_u32CFG_TIMEOUT_TMR         (MODULE_STM0.TIM0.U)

#define VADC_u32CFG_GLOBEVNP (0) /* Not used */

/**********************************************************************************************************************/
/* TYPES DEFINITION                                                                                                   */
/**********************************************************************************************************************/
typedef struct
{
   uint8          u8Queue0NbCh;
   const uint16 * pku16Queue0Cfg;
   uint32         u32ScanCfg;
   uint32         u32BckgScanCfg;
   uint8          u8Queue3NbCh;
   const uint16 * pku16Queue3Cfg;
}
VADC_tstrGroupSources;


/**********************************************************************************************************************/
/* CONSTANTS DECLARATION                                                                                              */
/**********************************************************************************************************************/
#define VADC_START_SEC_CONST_UNSPECIFIED
#include "VADC_MemMap.h"

extern const VADC_tstrGroupSources VADC_kastrGroupSources[VADC_u8GROUP_NB_MAX];

extern const uint32 VADC_kau32QCtrl0[VADC_u8GROUP_NB_MAX];
extern const uint32 VADC_kau32Synctr[VADC_u8GROUP_NB_MAX];
extern const uint32 VADC_kau32Alias[VADC_u8GROUP_NB_MAX];
extern const uint32 VADC_kau32GlbIClass[VADC_u32CONV_CLASSES_NB_MAX];
extern const uint32 VADC_kau32GroupsIClass[VADC_u8GROUP_NB_MAX][VADC_u32CONV_CLASSES_NB_MAX];
extern const uint32 VADC_kau32Chctr[VADC_u8GROUP_NB_MAX][VADC_u32CHANNELS_NB_MAX];
extern const uint16 VADC_kau16ChAsgntReg[VADC_u8GROUP_NB_MAX];
extern const uint16 VADC_kau16ResAsgntReg[VADC_u8GROUP_NB_MAX];
extern const uint32 VADC_kau32ArbnPrioReg[VADC_u8GROUP_NB_MAX];
extern const uint16 VADC_kau16ArbnCfgReg[VADC_u8GROUP_NB_MAX];
extern const uint32 VADC_kau32SrcEveToSrvReqLine[VADC_u8GROUP_NB_MAX];
extern const uint32 VADC_kau32ChEveToSrvReqLine[VADC_u8GROUP_NB_MAX][(VADC_u32CHANNELS_NB_MAX + 7) / 8];
extern const uint32 VADC_kau32ResEveToSrvReqLine[VADC_u8GROUP_NB_MAX][2];
extern const uint16 VADC_ku16MaxThrdGlobal;
extern const uint16 VADC_ku16MinThrdGlobal;
extern const uint16 VADC_kau16MaxThrdGrp[VADC_u8GROUP_NB_MAX];
extern const uint16 VADC_kau16MinThrdGrp[VADC_u8GROUP_NB_MAX];

#define VADC_STOP_SEC_CONST_UNSPECIFIED
#include "VADC_MemMap.h"


/**********************************************************************************************************************/
/* DATA DECLARATION                                                                                                   */
/**********************************************************************************************************************/
#define VADC_START_SEC_VAR_UNSPECIFIED
#include "VADC_MemMap.h"

extern uint16 VADC_au16ConvRes[VADC_u8NB_CONV_RES];
extern uint32 VADC_au32IsrPeriod[4];
extern uint32 VADC_au32IsrTimeStamp[4];

#define VADC_STOP_SEC_VAR_UNSPECIFIED
#include "VADC_MemMap.h"


/**********************************************************************************************************************/
/* FUNCTIONS DECLARATION                                                                                              */
/**********************************************************************************************************************/
#define VADC_START_SEC_CODE
#include "VADC_MemMap.h"

extern void VADC_vidUpdate10ms(void);

#define VADC_STOP_SEC_CODE
#include "VADC_MemMap.h"

#endif /* VADC_CFG_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
