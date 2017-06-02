#if (!defined COM_SYMBOLIC_NAMES_PB_CFG_H)
#define COM_SYMBOLIC_NAMES_PB_CFG_H

/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
/*==================[includes]==============================================*/

/*==================[macros]================================================*/

/* IPDU group ID defines */
#if (defined ComConf_ComIPduGroup_RXPDUS_GLOBAL) /* To prevent double declaration */
#error ComConf_ComIPduGroup_RXPDUS_GLOBAL already defined
#endif /* #if (defined ComConf_ComIPduGroup_RXPDUS_GLOBAL) */

#define ComConf_ComIPduGroup_RXPDUS_GLOBAL 0U


#if (defined ComConf_ComIPduGroup_TXPDUS_GLOBAL) /* To prevent double declaration */
#error ComConf_ComIPduGroup_TXPDUS_GLOBAL already defined
#endif /* #if (defined ComConf_ComIPduGroup_TXPDUS_GLOBAL) */

#define ComConf_ComIPduGroup_TXPDUS_GLOBAL 1U


#if (defined ComConf_ComIPduGroup_RGCanNetwork) /* To prevent double declaration */
#error ComConf_ComIPduGroup_RGCanNetwork already defined
#endif /* #if (defined ComConf_ComIPduGroup_RGCanNetwork) */

#define ComConf_ComIPduGroup_RGCanNetwork 2U


#if (defined ComConf_ComIPduGroup_TGCanNetwork) /* To prevent double declaration */
#error ComConf_ComIPduGroup_TGCanNetwork already defined
#endif /* #if (defined ComConf_ComIPduGroup_TGCanNetwork) */

#define ComConf_ComIPduGroup_TGCanNetwork 3U


/* External Rx IPdus defines */
#if (defined ComConf_ComIPdu_PDECM1_273R) /* To prevent double declaration */
#error ComConf_ComIPdu_PDECM1_273R already defined
#endif /* #if (defined ComConf_ComIPdu_PDECM1_273R) */

#define ComConf_ComIPdu_PDECM1_273R 0U


#if (defined ComConf_ComIPdu_PDECM2_289R) /* To prevent double declaration */
#error ComConf_ComIPdu_PDECM2_289R already defined
#endif /* #if (defined ComConf_ComIPdu_PDECM2_289R) */

#define ComConf_ComIPdu_PDECM2_289R 1U


#if (defined ComConf_ComIPdu_PDABS1_529R) /* To prevent double declaration */
#error ComConf_ComIPdu_PDABS1_529R already defined
#endif /* #if (defined ComConf_ComIPdu_PDABS1_529R) */

#define ComConf_ComIPdu_PDABS1_529R 2U


#if (defined ComConf_ComIPdu_PDABS2_545R) /* To prevent double declaration */
#error ComConf_ComIPdu_PDABS2_545R already defined
#endif /* #if (defined ComConf_ComIPdu_PDABS2_545R) */

#define ComConf_ComIPdu_PDABS2_545R 3U


#if (defined ComConf_ComIPdu_PDESC1_561R) /* To prevent double declaration */
#error ComConf_ComIPdu_PDESC1_561R already defined
#endif /* #if (defined ComConf_ComIPdu_PDESC1_561R) */

#define ComConf_ComIPdu_PDESC1_561R 4U


#if (defined ComConf_ComIPdu_PDECM3_609R) /* To prevent double declaration */
#error ComConf_ComIPdu_PDECM3_609R already defined
#endif /* #if (defined ComConf_ComIPdu_PDECM3_609R) */

#define ComConf_ComIPdu_PDECM3_609R 5U


#if (defined ComConf_ComIPdu_PDIP1_641R) /* To prevent double declaration */
#error ComConf_ComIPdu_PDIP1_641R already defined
#endif /* #if (defined ComConf_ComIPdu_PDIP1_641R) */

#define ComConf_ComIPdu_PDIP1_641R 6U


/* External Tx IPdu defines */
#if (defined ComConf_ComIPdu_PDTCU1_321T) /* To prevent double declaration */
#error ComConf_ComIPdu_PDTCU1_321T already defined
#endif /* #if (defined ComConf_ComIPdu_PDTCU1_321T) */

#define ComConf_ComIPdu_PDTCU1_321T 0U


#if (defined ComConf_ComIPdu_PDTCU2_337T) /* To prevent double declaration */
#error ComConf_ComIPdu_PDTCU2_337T already defined
#endif /* #if (defined ComConf_ComIPdu_PDTCU2_337T) */

#define ComConf_ComIPdu_PDTCU2_337T 1U


/* External Rx Signal IDs (no group signals) defines */
#if (defined ComConf_ComSignal_SGAccrPedlRat_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGAccrPedlRat_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGAccrPedlRat_273R) */

#define ComConf_ComSignal_SGAccrPedlRat_273R 0U


#if (defined ComConf_ComSignal_SGBrkPedlPsd_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGBrkPedlPsd_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGBrkPedlPsd_273R) */

#define ComConf_ComSignal_SGBrkPedlPsd_273R 1U


#if (defined ComConf_ComSignal_SGECM1AliveCounter_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGECM1AliveCounter_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGECM1AliveCounter_273R) */

#define ComConf_ComSignal_SGECM1AliveCounter_273R 2U


#if (defined ComConf_ComSignal_SGECM1Checksum_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGECM1Checksum_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGECM1Checksum_273R) */

#define ComConf_ComSignal_SGECM1Checksum_273R 3U


#if (defined ComConf_ComSignal_SGEngStAct_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngStAct_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngStAct_273R) */

#define ComConf_ComSignal_SGEngStAct_273R 4U


#if (defined ComConf_ComSignal_SGEngTqIndAct_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngTqIndAct_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngTqIndAct_273R) */

#define ComConf_ComSignal_SGEngTqIndAct_273R 5U


#if (defined ComConf_ComSignal_SGEngTqIndDrvDmd_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngTqIndDrvDmd_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngTqIndDrvDmd_273R) */

#define ComConf_ComSignal_SGEngTqIndDrvDmd_273R 6U


#if (defined ComConf_ComSignal_SGEngTqLoss_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngTqLoss_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngTqLoss_273R) */

#define ComConf_ComSignal_SGEngTqLoss_273R 7U


#if (defined ComConf_ComSignal_SGHvacCluSts_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGHvacCluSts_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGHvacCluSts_273R) */

#define ComConf_ComSignal_SGHvacCluSts_273R 8U


#if (defined ComConf_ComSignal_SGThrottleCmdPos_273R) /* To prevent double declaration */
#error ComConf_ComSignal_SGThrottleCmdPos_273R already defined
#endif /* #if (defined ComConf_ComSignal_SGThrottleCmdPos_273R) */

#define ComConf_ComSignal_SGThrottleCmdPos_273R 9U


#if (defined ComConf_ComSignal_SGCrsCtrlCtrlActv_289R) /* To prevent double declaration */
#error ComConf_ComSignal_SGCrsCtrlCtrlActv_289R already defined
#endif /* #if (defined ComConf_ComSignal_SGCrsCtrlCtrlActv_289R) */

#define ComConf_ComSignal_SGCrsCtrlCtrlActv_289R 10U


#if (defined ComConf_ComSignal_SGECM2AliveCounter_289R) /* To prevent double declaration */
#error ComConf_ComSignal_SGECM2AliveCounter_289R already defined
#endif /* #if (defined ComConf_ComSignal_SGECM2AliveCounter_289R) */

#define ComConf_ComSignal_SGECM2AliveCounter_289R 11U


#if (defined ComConf_ComSignal_SGECM2Checksum_289R) /* To prevent double declaration */
#error ComConf_ComSignal_SGECM2Checksum_289R already defined
#endif /* #if (defined ComConf_ComSignal_SGECM2Checksum_289R) */

#define ComConf_ComSignal_SGECM2Checksum_289R 12U


#if (defined ComConf_ComSignal_SGEngN_289R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngN_289R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngN_289R) */

#define ComConf_ComSignal_SGEngN_289R 13U


#if (defined ComConf_ComSignal_SGEngNTgtIdle_289R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngNTgtIdle_289R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngNTgtIdle_289R) */

#define ComConf_ComSignal_SGEngNTgtIdle_289R 14U


#if (defined ComConf_ComSignal_SGGearLmtForLightOff_289R) /* To prevent double declaration */
#error ComConf_ComSignal_SGGearLmtForLightOff_289R already defined
#endif /* #if (defined ComConf_ComSignal_SGGearLmtForLightOff_289R) */

#define ComConf_ComSignal_SGGearLmtForLightOff_289R 15U


#if (defined ComConf_ComSignal_SGWhlSpdFrntLeRaw_529R) /* To prevent double declaration */
#error ComConf_ComSignal_SGWhlSpdFrntLeRaw_529R already defined
#endif /* #if (defined ComConf_ComSignal_SGWhlSpdFrntLeRaw_529R) */

#define ComConf_ComSignal_SGWhlSpdFrntLeRaw_529R 16U


#if (defined ComConf_ComSignal_SGWhlSpdFrntRiRaw_529R) /* To prevent double declaration */
#error ComConf_ComSignal_SGWhlSpdFrntRiRaw_529R already defined
#endif /* #if (defined ComConf_ComSignal_SGWhlSpdFrntRiRaw_529R) */

#define ComConf_ComSignal_SGWhlSpdFrntRiRaw_529R 17U


#if (defined ComConf_ComSignal_SGWhlSpdReLeRaw_529R) /* To prevent double declaration */
#error ComConf_ComSignal_SGWhlSpdReLeRaw_529R already defined
#endif /* #if (defined ComConf_ComSignal_SGWhlSpdReLeRaw_529R) */

#define ComConf_ComSignal_SGWhlSpdReLeRaw_529R 18U


#if (defined ComConf_ComSignal_SGWhlSpdReRiRaw_529R) /* To prevent double declaration */
#error ComConf_ComSignal_SGWhlSpdReRiRaw_529R already defined
#endif /* #if (defined ComConf_ComSignal_SGWhlSpdReRiRaw_529R) */

#define ComConf_ComSignal_SGWhlSpdReRiRaw_529R 19U


#if (defined ComConf_ComSignal_SGAbsCtrlActv_545R) /* To prevent double declaration */
#error ComConf_ComSignal_SGAbsCtrlActv_545R already defined
#endif /* #if (defined ComConf_ComSignal_SGAbsCtrlActv_545R) */

#define ComConf_ComSignal_SGAbsCtrlActv_545R 20U


#if (defined ComConf_ComSignal_SGAbsFlgFlt_545R) /* To prevent double declaration */
#error ComConf_ComSignal_SGAbsFlgFlt_545R already defined
#endif /* #if (defined ComConf_ComSignal_SGAbsFlgFlt_545R) */

#define ComConf_ComSignal_SGAbsFlgFlt_545R 21U


#if (defined ComConf_ComSignal_SGEbdFlgFlt_545R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEbdFlgFlt_545R already defined
#endif /* #if (defined ComConf_ComSignal_SGEbdFlgFlt_545R) */

#define ComConf_ComSignal_SGEbdFlgFlt_545R 22U


#if (defined ComConf_ComSignal_SGAlgt_561R) /* To prevent double declaration */
#error ComConf_ComSignal_SGAlgt_561R already defined
#endif /* #if (defined ComConf_ComSignal_SGAlgt_561R) */

#define ComConf_ComSignal_SGAlgt_561R 23U


#if (defined ComConf_ComSignal_SGEscFlgFlt_561R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEscFlgFlt_561R already defined
#endif /* #if (defined ComConf_ComSignal_SGEscFlgFlt_561R) */

#define ComConf_ComSignal_SGEscFlgFlt_561R 24U


#if (defined ComConf_ComSignal_SGGearShiftPrevn_561R) /* To prevent double declaration */
#error ComConf_ComSignal_SGGearShiftPrevn_561R already defined
#endif /* #if (defined ComConf_ComSignal_SGGearShiftPrevn_561R) */

#define ComConf_ComSignal_SGGearShiftPrevn_561R 25U


#if (defined ComConf_ComSignal_SGTcsCtrlActv_561R) /* To prevent double declaration */
#error ComConf_ComSignal_SGTcsCtrlActv_561R already defined
#endif /* #if (defined ComConf_ComSignal_SGTcsCtrlActv_561R) */

#define ComConf_ComSignal_SGTcsCtrlActv_561R 26U


#if (defined ComConf_ComSignal_SGTcsFlgFlt_561R) /* To prevent double declaration */
#error ComConf_ComSignal_SGTcsFlgFlt_561R already defined
#endif /* #if (defined ComConf_ComSignal_SGTcsFlgFlt_561R) */

#define ComConf_ComSignal_SGTcsFlgFlt_561R 27U


#if (defined ComConf_ComSignal_SGEngPAmbAir_609R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngPAmbAir_609R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngPAmbAir_609R) */

#define ComConf_ComSignal_SGEngPAmbAir_609R 28U


#if (defined ComConf_ComSignal_SGEngT_609R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngT_609R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngT_609R) */

#define ComConf_ComSignal_SGEngT_609R 29U


#if (defined ComConf_ComSignal_SGEngineSoakTime_609R) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngineSoakTime_609R already defined
#endif /* #if (defined ComConf_ComSignal_SGEngineSoakTime_609R) */

#define ComConf_ComSignal_SGEngineSoakTime_609R 30U


#if (defined ComConf_ComSignal_SGOBDDrivingCycleStatus_609R) /* To prevent double declaration */
#error ComConf_ComSignal_SGOBDDrivingCycleStatus_609R already defined
#endif /* #if (defined ComConf_ComSignal_SGOBDDrivingCycleStatus_609R) */

#define ComConf_ComSignal_SGOBDDrivingCycleStatus_609R 31U


#if (defined ComConf_ComSignal_SGOBDWarmUpCycleStatus_609R) /* To prevent double declaration */
#error ComConf_ComSignal_SGOBDWarmUpCycleStatus_609R already defined
#endif /* #if (defined ComConf_ComSignal_SGOBDWarmUpCycleStatus_609R) */

#define ComConf_ComSignal_SGOBDWarmUpCycleStatus_609R 32U


#if (defined ComConf_ComSignal_SGAmbAirTemp_641R) /* To prevent double declaration */
#error ComConf_ComSignal_SGAmbAirTemp_641R already defined
#endif /* #if (defined ComConf_ComSignal_SGAmbAirTemp_641R) */

#define ComConf_ComSignal_SGAmbAirTemp_641R 33U


/* External Tx Signal IDs (no group signals) defines */
#if (defined ComConf_ComSignal_SGEngNIdleReq_321T) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngNIdleReq_321T already defined
#endif /* #if (defined ComConf_ComSignal_SGEngNIdleReq_321T) */

#define ComConf_ComSignal_SGEngNIdleReq_321T 0U


#if (defined ComConf_ComSignal_SGEngTqIndDecReqdByTrsm_321T) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngTqIndDecReqdByTrsm_321T already defined
#endif /* #if (defined ComConf_ComSignal_SGEngTqIndDecReqdByTrsm_321T) */

#define ComConf_ComSignal_SGEngTqIndDecReqdByTrsm_321T 1U


#if (defined ComConf_ComSignal_SGEngTqIndLmtdByTrsm_321T) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngTqIndLmtdByTrsm_321T already defined
#endif /* #if (defined ComConf_ComSignal_SGEngTqIndLmtdByTrsm_321T) */

#define ComConf_ComSignal_SGEngTqIndLmtdByTrsm_321T 2U


#if (defined ComConf_ComSignal_SGTrsmCluStAct_321T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmCluStAct_321T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmCluStAct_321T) */

#define ComConf_ComSignal_SGTrsmCluStAct_321T 3U


#if (defined ComConf_ComSignal_SGTrsmMsgCnt_321T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmMsgCnt_321T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmMsgCnt_321T) */

#define ComConf_ComSignal_SGTrsmMsgCnt_321T 4U


#if (defined ComConf_ComSignal_SGTrsmNInp_321T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmNInp_321T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmNInp_321T) */

#define ComConf_ComSignal_SGTrsmNInp_321T 5U


#if (defined ComConf_ComSignal_SGEngTqIndIncReqdByTrsm_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGEngTqIndIncReqdByTrsm_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGEngTqIndIncReqdByTrsm_337T) */

#define ComConf_ComSignal_SGEngTqIndIncReqdByTrsm_337T 6U


#if (defined ComConf_ComSignal_SGTrsmFlgFlt_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmFlgFlt_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmFlgFlt_337T) */

#define ComConf_ComSignal_SGTrsmFlgFlt_337T 7U


#if (defined ComConf_ComSignal_SGTrsmFlgShiftProgs_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmFlgShiftProgs_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmFlgShiftProgs_337T) */

#define ComConf_ComSignal_SGTrsmFlgShiftProgs_337T 8U


#if (defined ComConf_ComSignal_SGTrsmGearAct_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmGearAct_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmGearAct_337T) */

#define ComConf_ComSignal_SGTrsmGearAct_337T 9U


#if (defined ComConf_ComSignal_SGTrsmGearTar_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmGearTar_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmGearTar_337T) */

#define ComConf_ComSignal_SGTrsmGearTar_337T 10U


#if (defined ComConf_ComSignal_SGTrsmMILReq_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmMILReq_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmMILReq_337T) */

#define ComConf_ComSignal_SGTrsmMILReq_337T 11U


#if (defined ComConf_ComSignal_SGTrsmStGearLvr_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmStGearLvr_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmStGearLvr_337T) */

#define ComConf_ComSignal_SGTrsmStGearLvr_337T 12U


#if (defined ComConf_ComSignal_SGTrsmStGearMode_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmStGearMode_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmStGearMode_337T) */

#define ComConf_ComSignal_SGTrsmStGearMode_337T 13U


#if (defined ComConf_ComSignal_SGTrsmTOil_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmTOil_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmTOil_337T) */

#define ComConf_ComSignal_SGTrsmTOil_337T 14U


#if (defined ComConf_ComSignal_SGTrsmTOilWrnLmpReq_337T) /* To prevent double declaration */
#error ComConf_ComSignal_SGTrsmTOilWrnLmpReq_337T already defined
#endif /* #if (defined ComConf_ComSignal_SGTrsmTOilWrnLmpReq_337T) */

#define ComConf_ComSignal_SGTrsmTOilWrnLmpReq_337T 15U


/* External Rx Group Signal IDs defines */
/* External Tx Group Signal IDs defines */
/* External Rx Signal Group IDs defines */
/* External Tx Signal Group IDs defines */

/*------------------[symbols without prefix for backward compatibility]-----*/
#if (!defined COM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)

/* IPDU group ID defines */
#if (defined RXPDUS_GLOBAL) /* To prevent double declaration */
#error RXPDUS_GLOBAL already defined
#endif /* #if (defined RXPDUS_GLOBAL) */

#define RXPDUS_GLOBAL ComConf_ComIPduGroup_RXPDUS_GLOBAL

#if (defined Com_RXPDUS_GLOBAL) /* To prevent double declaration */
#error Com_RXPDUS_GLOBAL already defined
#endif /* #if (defined Com_RXPDUS_GLOBAL) */

#define Com_RXPDUS_GLOBAL ComConf_ComIPduGroup_RXPDUS_GLOBAL


#if (defined TXPDUS_GLOBAL) /* To prevent double declaration */
#error TXPDUS_GLOBAL already defined
#endif /* #if (defined TXPDUS_GLOBAL) */

#define TXPDUS_GLOBAL ComConf_ComIPduGroup_TXPDUS_GLOBAL

#if (defined Com_TXPDUS_GLOBAL) /* To prevent double declaration */
#error Com_TXPDUS_GLOBAL already defined
#endif /* #if (defined Com_TXPDUS_GLOBAL) */

#define Com_TXPDUS_GLOBAL ComConf_ComIPduGroup_TXPDUS_GLOBAL


#if (defined RGCanNetwork) /* To prevent double declaration */
#error RGCanNetwork already defined
#endif /* #if (defined RGCanNetwork) */

#define RGCanNetwork ComConf_ComIPduGroup_RGCanNetwork

#if (defined Com_RGCanNetwork) /* To prevent double declaration */
#error Com_RGCanNetwork already defined
#endif /* #if (defined Com_RGCanNetwork) */

#define Com_RGCanNetwork ComConf_ComIPduGroup_RGCanNetwork


#if (defined TGCanNetwork) /* To prevent double declaration */
#error TGCanNetwork already defined
#endif /* #if (defined TGCanNetwork) */

#define TGCanNetwork ComConf_ComIPduGroup_TGCanNetwork

#if (defined Com_TGCanNetwork) /* To prevent double declaration */
#error Com_TGCanNetwork already defined
#endif /* #if (defined Com_TGCanNetwork) */

#define Com_TGCanNetwork ComConf_ComIPduGroup_TGCanNetwork


/* External Rx IPdus defines */
#if (defined PDECM1_273R) /* To prevent double declaration */
#error PDECM1_273R already defined
#endif /* #if (defined PDECM1_273R) */

#define PDECM1_273R ComConf_ComIPdu_PDECM1_273R

#if (defined Com_PDECM1_273R) /* To prevent double declaration */
#error Com_PDECM1_273R already defined
#endif /* #if (defined Com_PDECM1_273R) */

#define Com_PDECM1_273R ComConf_ComIPdu_PDECM1_273R


#if (defined PDECM2_289R) /* To prevent double declaration */
#error PDECM2_289R already defined
#endif /* #if (defined PDECM2_289R) */

#define PDECM2_289R ComConf_ComIPdu_PDECM2_289R

#if (defined Com_PDECM2_289R) /* To prevent double declaration */
#error Com_PDECM2_289R already defined
#endif /* #if (defined Com_PDECM2_289R) */

#define Com_PDECM2_289R ComConf_ComIPdu_PDECM2_289R


#if (defined PDABS1_529R) /* To prevent double declaration */
#error PDABS1_529R already defined
#endif /* #if (defined PDABS1_529R) */

#define PDABS1_529R ComConf_ComIPdu_PDABS1_529R

#if (defined Com_PDABS1_529R) /* To prevent double declaration */
#error Com_PDABS1_529R already defined
#endif /* #if (defined Com_PDABS1_529R) */

#define Com_PDABS1_529R ComConf_ComIPdu_PDABS1_529R


#if (defined PDABS2_545R) /* To prevent double declaration */
#error PDABS2_545R already defined
#endif /* #if (defined PDABS2_545R) */

#define PDABS2_545R ComConf_ComIPdu_PDABS2_545R

#if (defined Com_PDABS2_545R) /* To prevent double declaration */
#error Com_PDABS2_545R already defined
#endif /* #if (defined Com_PDABS2_545R) */

#define Com_PDABS2_545R ComConf_ComIPdu_PDABS2_545R


#if (defined PDESC1_561R) /* To prevent double declaration */
#error PDESC1_561R already defined
#endif /* #if (defined PDESC1_561R) */

#define PDESC1_561R ComConf_ComIPdu_PDESC1_561R

#if (defined Com_PDESC1_561R) /* To prevent double declaration */
#error Com_PDESC1_561R already defined
#endif /* #if (defined Com_PDESC1_561R) */

#define Com_PDESC1_561R ComConf_ComIPdu_PDESC1_561R


#if (defined PDECM3_609R) /* To prevent double declaration */
#error PDECM3_609R already defined
#endif /* #if (defined PDECM3_609R) */

#define PDECM3_609R ComConf_ComIPdu_PDECM3_609R

#if (defined Com_PDECM3_609R) /* To prevent double declaration */
#error Com_PDECM3_609R already defined
#endif /* #if (defined Com_PDECM3_609R) */

#define Com_PDECM3_609R ComConf_ComIPdu_PDECM3_609R


#if (defined PDIP1_641R) /* To prevent double declaration */
#error PDIP1_641R already defined
#endif /* #if (defined PDIP1_641R) */

#define PDIP1_641R ComConf_ComIPdu_PDIP1_641R

#if (defined Com_PDIP1_641R) /* To prevent double declaration */
#error Com_PDIP1_641R already defined
#endif /* #if (defined Com_PDIP1_641R) */

#define Com_PDIP1_641R ComConf_ComIPdu_PDIP1_641R


/* External Tx IPdu defines */
#if (defined PDTCU1_321T) /* To prevent double declaration */
#error PDTCU1_321T already defined
#endif /* #if (defined PDTCU1_321T) */

#define PDTCU1_321T ComConf_ComIPdu_PDTCU1_321T

#if (defined Com_PDTCU1_321T) /* To prevent double declaration */
#error Com_PDTCU1_321T already defined
#endif /* #if (defined Com_PDTCU1_321T) */

#define Com_PDTCU1_321T ComConf_ComIPdu_PDTCU1_321T


#if (defined PDTCU2_337T) /* To prevent double declaration */
#error PDTCU2_337T already defined
#endif /* #if (defined PDTCU2_337T) */

#define PDTCU2_337T ComConf_ComIPdu_PDTCU2_337T

#if (defined Com_PDTCU2_337T) /* To prevent double declaration */
#error Com_PDTCU2_337T already defined
#endif /* #if (defined Com_PDTCU2_337T) */

#define Com_PDTCU2_337T ComConf_ComIPdu_PDTCU2_337T


/* External Rx Signal IDs (no group signals) defines */
#if (defined SGAccrPedlRat_273R) /* To prevent double declaration */
#error SGAccrPedlRat_273R already defined
#endif /* #if (defined SGAccrPedlRat_273R) */

#define SGAccrPedlRat_273R ComConf_ComSignal_SGAccrPedlRat_273R

#if (defined Com_SGAccrPedlRat_273R) /* To prevent double declaration */
#error Com_SGAccrPedlRat_273R already defined
#endif /* #if (defined Com_SGAccrPedlRat_273R) */

#define Com_SGAccrPedlRat_273R ComConf_ComSignal_SGAccrPedlRat_273R


#if (defined SGBrkPedlPsd_273R) /* To prevent double declaration */
#error SGBrkPedlPsd_273R already defined
#endif /* #if (defined SGBrkPedlPsd_273R) */

#define SGBrkPedlPsd_273R ComConf_ComSignal_SGBrkPedlPsd_273R

#if (defined Com_SGBrkPedlPsd_273R) /* To prevent double declaration */
#error Com_SGBrkPedlPsd_273R already defined
#endif /* #if (defined Com_SGBrkPedlPsd_273R) */

#define Com_SGBrkPedlPsd_273R ComConf_ComSignal_SGBrkPedlPsd_273R


#if (defined SGECM1AliveCounter_273R) /* To prevent double declaration */
#error SGECM1AliveCounter_273R already defined
#endif /* #if (defined SGECM1AliveCounter_273R) */

#define SGECM1AliveCounter_273R ComConf_ComSignal_SGECM1AliveCounter_273R

#if (defined Com_SGECM1AliveCounter_273R) /* To prevent double declaration */
#error Com_SGECM1AliveCounter_273R already defined
#endif /* #if (defined Com_SGECM1AliveCounter_273R) */

#define Com_SGECM1AliveCounter_273R ComConf_ComSignal_SGECM1AliveCounter_273R


#if (defined SGECM1Checksum_273R) /* To prevent double declaration */
#error SGECM1Checksum_273R already defined
#endif /* #if (defined SGECM1Checksum_273R) */

#define SGECM1Checksum_273R ComConf_ComSignal_SGECM1Checksum_273R

#if (defined Com_SGECM1Checksum_273R) /* To prevent double declaration */
#error Com_SGECM1Checksum_273R already defined
#endif /* #if (defined Com_SGECM1Checksum_273R) */

#define Com_SGECM1Checksum_273R ComConf_ComSignal_SGECM1Checksum_273R


#if (defined SGEngStAct_273R) /* To prevent double declaration */
#error SGEngStAct_273R already defined
#endif /* #if (defined SGEngStAct_273R) */

#define SGEngStAct_273R ComConf_ComSignal_SGEngStAct_273R

#if (defined Com_SGEngStAct_273R) /* To prevent double declaration */
#error Com_SGEngStAct_273R already defined
#endif /* #if (defined Com_SGEngStAct_273R) */

#define Com_SGEngStAct_273R ComConf_ComSignal_SGEngStAct_273R


#if (defined SGEngTqIndAct_273R) /* To prevent double declaration */
#error SGEngTqIndAct_273R already defined
#endif /* #if (defined SGEngTqIndAct_273R) */

#define SGEngTqIndAct_273R ComConf_ComSignal_SGEngTqIndAct_273R

#if (defined Com_SGEngTqIndAct_273R) /* To prevent double declaration */
#error Com_SGEngTqIndAct_273R already defined
#endif /* #if (defined Com_SGEngTqIndAct_273R) */

#define Com_SGEngTqIndAct_273R ComConf_ComSignal_SGEngTqIndAct_273R


#if (defined SGEngTqIndDrvDmd_273R) /* To prevent double declaration */
#error SGEngTqIndDrvDmd_273R already defined
#endif /* #if (defined SGEngTqIndDrvDmd_273R) */

#define SGEngTqIndDrvDmd_273R ComConf_ComSignal_SGEngTqIndDrvDmd_273R

#if (defined Com_SGEngTqIndDrvDmd_273R) /* To prevent double declaration */
#error Com_SGEngTqIndDrvDmd_273R already defined
#endif /* #if (defined Com_SGEngTqIndDrvDmd_273R) */

#define Com_SGEngTqIndDrvDmd_273R ComConf_ComSignal_SGEngTqIndDrvDmd_273R


#if (defined SGEngTqLoss_273R) /* To prevent double declaration */
#error SGEngTqLoss_273R already defined
#endif /* #if (defined SGEngTqLoss_273R) */

#define SGEngTqLoss_273R ComConf_ComSignal_SGEngTqLoss_273R

#if (defined Com_SGEngTqLoss_273R) /* To prevent double declaration */
#error Com_SGEngTqLoss_273R already defined
#endif /* #if (defined Com_SGEngTqLoss_273R) */

#define Com_SGEngTqLoss_273R ComConf_ComSignal_SGEngTqLoss_273R


#if (defined SGHvacCluSts_273R) /* To prevent double declaration */
#error SGHvacCluSts_273R already defined
#endif /* #if (defined SGHvacCluSts_273R) */

#define SGHvacCluSts_273R ComConf_ComSignal_SGHvacCluSts_273R

#if (defined Com_SGHvacCluSts_273R) /* To prevent double declaration */
#error Com_SGHvacCluSts_273R already defined
#endif /* #if (defined Com_SGHvacCluSts_273R) */

#define Com_SGHvacCluSts_273R ComConf_ComSignal_SGHvacCluSts_273R


#if (defined SGThrottleCmdPos_273R) /* To prevent double declaration */
#error SGThrottleCmdPos_273R already defined
#endif /* #if (defined SGThrottleCmdPos_273R) */

#define SGThrottleCmdPos_273R ComConf_ComSignal_SGThrottleCmdPos_273R

#if (defined Com_SGThrottleCmdPos_273R) /* To prevent double declaration */
#error Com_SGThrottleCmdPos_273R already defined
#endif /* #if (defined Com_SGThrottleCmdPos_273R) */

#define Com_SGThrottleCmdPos_273R ComConf_ComSignal_SGThrottleCmdPos_273R


#if (defined SGCrsCtrlCtrlActv_289R) /* To prevent double declaration */
#error SGCrsCtrlCtrlActv_289R already defined
#endif /* #if (defined SGCrsCtrlCtrlActv_289R) */

#define SGCrsCtrlCtrlActv_289R ComConf_ComSignal_SGCrsCtrlCtrlActv_289R

#if (defined Com_SGCrsCtrlCtrlActv_289R) /* To prevent double declaration */
#error Com_SGCrsCtrlCtrlActv_289R already defined
#endif /* #if (defined Com_SGCrsCtrlCtrlActv_289R) */

#define Com_SGCrsCtrlCtrlActv_289R ComConf_ComSignal_SGCrsCtrlCtrlActv_289R


#if (defined SGECM2AliveCounter_289R) /* To prevent double declaration */
#error SGECM2AliveCounter_289R already defined
#endif /* #if (defined SGECM2AliveCounter_289R) */

#define SGECM2AliveCounter_289R ComConf_ComSignal_SGECM2AliveCounter_289R

#if (defined Com_SGECM2AliveCounter_289R) /* To prevent double declaration */
#error Com_SGECM2AliveCounter_289R already defined
#endif /* #if (defined Com_SGECM2AliveCounter_289R) */

#define Com_SGECM2AliveCounter_289R ComConf_ComSignal_SGECM2AliveCounter_289R


#if (defined SGECM2Checksum_289R) /* To prevent double declaration */
#error SGECM2Checksum_289R already defined
#endif /* #if (defined SGECM2Checksum_289R) */

#define SGECM2Checksum_289R ComConf_ComSignal_SGECM2Checksum_289R

#if (defined Com_SGECM2Checksum_289R) /* To prevent double declaration */
#error Com_SGECM2Checksum_289R already defined
#endif /* #if (defined Com_SGECM2Checksum_289R) */

#define Com_SGECM2Checksum_289R ComConf_ComSignal_SGECM2Checksum_289R


#if (defined SGEngN_289R) /* To prevent double declaration */
#error SGEngN_289R already defined
#endif /* #if (defined SGEngN_289R) */

#define SGEngN_289R ComConf_ComSignal_SGEngN_289R

#if (defined Com_SGEngN_289R) /* To prevent double declaration */
#error Com_SGEngN_289R already defined
#endif /* #if (defined Com_SGEngN_289R) */

#define Com_SGEngN_289R ComConf_ComSignal_SGEngN_289R


#if (defined SGEngNTgtIdle_289R) /* To prevent double declaration */
#error SGEngNTgtIdle_289R already defined
#endif /* #if (defined SGEngNTgtIdle_289R) */

#define SGEngNTgtIdle_289R ComConf_ComSignal_SGEngNTgtIdle_289R

#if (defined Com_SGEngNTgtIdle_289R) /* To prevent double declaration */
#error Com_SGEngNTgtIdle_289R already defined
#endif /* #if (defined Com_SGEngNTgtIdle_289R) */

#define Com_SGEngNTgtIdle_289R ComConf_ComSignal_SGEngNTgtIdle_289R


#if (defined SGGearLmtForLightOff_289R) /* To prevent double declaration */
#error SGGearLmtForLightOff_289R already defined
#endif /* #if (defined SGGearLmtForLightOff_289R) */

#define SGGearLmtForLightOff_289R ComConf_ComSignal_SGGearLmtForLightOff_289R

#if (defined Com_SGGearLmtForLightOff_289R) /* To prevent double declaration */
#error Com_SGGearLmtForLightOff_289R already defined
#endif /* #if (defined Com_SGGearLmtForLightOff_289R) */

#define Com_SGGearLmtForLightOff_289R ComConf_ComSignal_SGGearLmtForLightOff_289R


#if (defined SGWhlSpdFrntLeRaw_529R) /* To prevent double declaration */
#error SGWhlSpdFrntLeRaw_529R already defined
#endif /* #if (defined SGWhlSpdFrntLeRaw_529R) */

#define SGWhlSpdFrntLeRaw_529R ComConf_ComSignal_SGWhlSpdFrntLeRaw_529R

#if (defined Com_SGWhlSpdFrntLeRaw_529R) /* To prevent double declaration */
#error Com_SGWhlSpdFrntLeRaw_529R already defined
#endif /* #if (defined Com_SGWhlSpdFrntLeRaw_529R) */

#define Com_SGWhlSpdFrntLeRaw_529R ComConf_ComSignal_SGWhlSpdFrntLeRaw_529R


#if (defined SGWhlSpdFrntRiRaw_529R) /* To prevent double declaration */
#error SGWhlSpdFrntRiRaw_529R already defined
#endif /* #if (defined SGWhlSpdFrntRiRaw_529R) */

#define SGWhlSpdFrntRiRaw_529R ComConf_ComSignal_SGWhlSpdFrntRiRaw_529R

#if (defined Com_SGWhlSpdFrntRiRaw_529R) /* To prevent double declaration */
#error Com_SGWhlSpdFrntRiRaw_529R already defined
#endif /* #if (defined Com_SGWhlSpdFrntRiRaw_529R) */

#define Com_SGWhlSpdFrntRiRaw_529R ComConf_ComSignal_SGWhlSpdFrntRiRaw_529R


#if (defined SGWhlSpdReLeRaw_529R) /* To prevent double declaration */
#error SGWhlSpdReLeRaw_529R already defined
#endif /* #if (defined SGWhlSpdReLeRaw_529R) */

#define SGWhlSpdReLeRaw_529R ComConf_ComSignal_SGWhlSpdReLeRaw_529R

#if (defined Com_SGWhlSpdReLeRaw_529R) /* To prevent double declaration */
#error Com_SGWhlSpdReLeRaw_529R already defined
#endif /* #if (defined Com_SGWhlSpdReLeRaw_529R) */

#define Com_SGWhlSpdReLeRaw_529R ComConf_ComSignal_SGWhlSpdReLeRaw_529R


#if (defined SGWhlSpdReRiRaw_529R) /* To prevent double declaration */
#error SGWhlSpdReRiRaw_529R already defined
#endif /* #if (defined SGWhlSpdReRiRaw_529R) */

#define SGWhlSpdReRiRaw_529R ComConf_ComSignal_SGWhlSpdReRiRaw_529R

#if (defined Com_SGWhlSpdReRiRaw_529R) /* To prevent double declaration */
#error Com_SGWhlSpdReRiRaw_529R already defined
#endif /* #if (defined Com_SGWhlSpdReRiRaw_529R) */

#define Com_SGWhlSpdReRiRaw_529R ComConf_ComSignal_SGWhlSpdReRiRaw_529R


#if (defined SGAbsCtrlActv_545R) /* To prevent double declaration */
#error SGAbsCtrlActv_545R already defined
#endif /* #if (defined SGAbsCtrlActv_545R) */

#define SGAbsCtrlActv_545R ComConf_ComSignal_SGAbsCtrlActv_545R

#if (defined Com_SGAbsCtrlActv_545R) /* To prevent double declaration */
#error Com_SGAbsCtrlActv_545R already defined
#endif /* #if (defined Com_SGAbsCtrlActv_545R) */

#define Com_SGAbsCtrlActv_545R ComConf_ComSignal_SGAbsCtrlActv_545R


#if (defined SGAbsFlgFlt_545R) /* To prevent double declaration */
#error SGAbsFlgFlt_545R already defined
#endif /* #if (defined SGAbsFlgFlt_545R) */

#define SGAbsFlgFlt_545R ComConf_ComSignal_SGAbsFlgFlt_545R

#if (defined Com_SGAbsFlgFlt_545R) /* To prevent double declaration */
#error Com_SGAbsFlgFlt_545R already defined
#endif /* #if (defined Com_SGAbsFlgFlt_545R) */

#define Com_SGAbsFlgFlt_545R ComConf_ComSignal_SGAbsFlgFlt_545R


#if (defined SGEbdFlgFlt_545R) /* To prevent double declaration */
#error SGEbdFlgFlt_545R already defined
#endif /* #if (defined SGEbdFlgFlt_545R) */

#define SGEbdFlgFlt_545R ComConf_ComSignal_SGEbdFlgFlt_545R

#if (defined Com_SGEbdFlgFlt_545R) /* To prevent double declaration */
#error Com_SGEbdFlgFlt_545R already defined
#endif /* #if (defined Com_SGEbdFlgFlt_545R) */

#define Com_SGEbdFlgFlt_545R ComConf_ComSignal_SGEbdFlgFlt_545R


#if (defined SGAlgt_561R) /* To prevent double declaration */
#error SGAlgt_561R already defined
#endif /* #if (defined SGAlgt_561R) */

#define SGAlgt_561R ComConf_ComSignal_SGAlgt_561R

#if (defined Com_SGAlgt_561R) /* To prevent double declaration */
#error Com_SGAlgt_561R already defined
#endif /* #if (defined Com_SGAlgt_561R) */

#define Com_SGAlgt_561R ComConf_ComSignal_SGAlgt_561R


#if (defined SGEscFlgFlt_561R) /* To prevent double declaration */
#error SGEscFlgFlt_561R already defined
#endif /* #if (defined SGEscFlgFlt_561R) */

#define SGEscFlgFlt_561R ComConf_ComSignal_SGEscFlgFlt_561R

#if (defined Com_SGEscFlgFlt_561R) /* To prevent double declaration */
#error Com_SGEscFlgFlt_561R already defined
#endif /* #if (defined Com_SGEscFlgFlt_561R) */

#define Com_SGEscFlgFlt_561R ComConf_ComSignal_SGEscFlgFlt_561R


#if (defined SGGearShiftPrevn_561R) /* To prevent double declaration */
#error SGGearShiftPrevn_561R already defined
#endif /* #if (defined SGGearShiftPrevn_561R) */

#define SGGearShiftPrevn_561R ComConf_ComSignal_SGGearShiftPrevn_561R

#if (defined Com_SGGearShiftPrevn_561R) /* To prevent double declaration */
#error Com_SGGearShiftPrevn_561R already defined
#endif /* #if (defined Com_SGGearShiftPrevn_561R) */

#define Com_SGGearShiftPrevn_561R ComConf_ComSignal_SGGearShiftPrevn_561R


#if (defined SGTcsCtrlActv_561R) /* To prevent double declaration */
#error SGTcsCtrlActv_561R already defined
#endif /* #if (defined SGTcsCtrlActv_561R) */

#define SGTcsCtrlActv_561R ComConf_ComSignal_SGTcsCtrlActv_561R

#if (defined Com_SGTcsCtrlActv_561R) /* To prevent double declaration */
#error Com_SGTcsCtrlActv_561R already defined
#endif /* #if (defined Com_SGTcsCtrlActv_561R) */

#define Com_SGTcsCtrlActv_561R ComConf_ComSignal_SGTcsCtrlActv_561R


#if (defined SGTcsFlgFlt_561R) /* To prevent double declaration */
#error SGTcsFlgFlt_561R already defined
#endif /* #if (defined SGTcsFlgFlt_561R) */

#define SGTcsFlgFlt_561R ComConf_ComSignal_SGTcsFlgFlt_561R

#if (defined Com_SGTcsFlgFlt_561R) /* To prevent double declaration */
#error Com_SGTcsFlgFlt_561R already defined
#endif /* #if (defined Com_SGTcsFlgFlt_561R) */

#define Com_SGTcsFlgFlt_561R ComConf_ComSignal_SGTcsFlgFlt_561R


#if (defined SGEngPAmbAir_609R) /* To prevent double declaration */
#error SGEngPAmbAir_609R already defined
#endif /* #if (defined SGEngPAmbAir_609R) */

#define SGEngPAmbAir_609R ComConf_ComSignal_SGEngPAmbAir_609R

#if (defined Com_SGEngPAmbAir_609R) /* To prevent double declaration */
#error Com_SGEngPAmbAir_609R already defined
#endif /* #if (defined Com_SGEngPAmbAir_609R) */

#define Com_SGEngPAmbAir_609R ComConf_ComSignal_SGEngPAmbAir_609R


#if (defined SGEngT_609R) /* To prevent double declaration */
#error SGEngT_609R already defined
#endif /* #if (defined SGEngT_609R) */

#define SGEngT_609R ComConf_ComSignal_SGEngT_609R

#if (defined Com_SGEngT_609R) /* To prevent double declaration */
#error Com_SGEngT_609R already defined
#endif /* #if (defined Com_SGEngT_609R) */

#define Com_SGEngT_609R ComConf_ComSignal_SGEngT_609R


#if (defined SGEngineSoakTime_609R) /* To prevent double declaration */
#error SGEngineSoakTime_609R already defined
#endif /* #if (defined SGEngineSoakTime_609R) */

#define SGEngineSoakTime_609R ComConf_ComSignal_SGEngineSoakTime_609R

#if (defined Com_SGEngineSoakTime_609R) /* To prevent double declaration */
#error Com_SGEngineSoakTime_609R already defined
#endif /* #if (defined Com_SGEngineSoakTime_609R) */

#define Com_SGEngineSoakTime_609R ComConf_ComSignal_SGEngineSoakTime_609R


#if (defined SGOBDDrivingCycleStatus_609R) /* To prevent double declaration */
#error SGOBDDrivingCycleStatus_609R already defined
#endif /* #if (defined SGOBDDrivingCycleStatus_609R) */

#define SGOBDDrivingCycleStatus_609R ComConf_ComSignal_SGOBDDrivingCycleStatus_609R

#if (defined Com_SGOBDDrivingCycleStatus_609R) /* To prevent double declaration */
#error Com_SGOBDDrivingCycleStatus_609R already defined
#endif /* #if (defined Com_SGOBDDrivingCycleStatus_609R) */

#define Com_SGOBDDrivingCycleStatus_609R ComConf_ComSignal_SGOBDDrivingCycleStatus_609R


#if (defined SGOBDWarmUpCycleStatus_609R) /* To prevent double declaration */
#error SGOBDWarmUpCycleStatus_609R already defined
#endif /* #if (defined SGOBDWarmUpCycleStatus_609R) */

#define SGOBDWarmUpCycleStatus_609R ComConf_ComSignal_SGOBDWarmUpCycleStatus_609R

#if (defined Com_SGOBDWarmUpCycleStatus_609R) /* To prevent double declaration */
#error Com_SGOBDWarmUpCycleStatus_609R already defined
#endif /* #if (defined Com_SGOBDWarmUpCycleStatus_609R) */

#define Com_SGOBDWarmUpCycleStatus_609R ComConf_ComSignal_SGOBDWarmUpCycleStatus_609R


#if (defined SGAmbAirTemp_641R) /* To prevent double declaration */
#error SGAmbAirTemp_641R already defined
#endif /* #if (defined SGAmbAirTemp_641R) */

#define SGAmbAirTemp_641R ComConf_ComSignal_SGAmbAirTemp_641R

#if (defined Com_SGAmbAirTemp_641R) /* To prevent double declaration */
#error Com_SGAmbAirTemp_641R already defined
#endif /* #if (defined Com_SGAmbAirTemp_641R) */

#define Com_SGAmbAirTemp_641R ComConf_ComSignal_SGAmbAirTemp_641R


/* External Tx Signal IDs (no group signals) defines */
#if (defined SGEngNIdleReq_321T) /* To prevent double declaration */
#error SGEngNIdleReq_321T already defined
#endif /* #if (defined SGEngNIdleReq_321T) */

#define SGEngNIdleReq_321T ComConf_ComSignal_SGEngNIdleReq_321T

#if (defined Com_SGEngNIdleReq_321T) /* To prevent double declaration */
#error Com_SGEngNIdleReq_321T already defined
#endif /* #if (defined Com_SGEngNIdleReq_321T) */

#define Com_SGEngNIdleReq_321T ComConf_ComSignal_SGEngNIdleReq_321T


#if (defined SGEngTqIndDecReqdByTrsm_321T) /* To prevent double declaration */
#error SGEngTqIndDecReqdByTrsm_321T already defined
#endif /* #if (defined SGEngTqIndDecReqdByTrsm_321T) */

#define SGEngTqIndDecReqdByTrsm_321T ComConf_ComSignal_SGEngTqIndDecReqdByTrsm_321T

#if (defined Com_SGEngTqIndDecReqdByTrsm_321T) /* To prevent double declaration */
#error Com_SGEngTqIndDecReqdByTrsm_321T already defined
#endif /* #if (defined Com_SGEngTqIndDecReqdByTrsm_321T) */

#define Com_SGEngTqIndDecReqdByTrsm_321T ComConf_ComSignal_SGEngTqIndDecReqdByTrsm_321T


#if (defined SGEngTqIndLmtdByTrsm_321T) /* To prevent double declaration */
#error SGEngTqIndLmtdByTrsm_321T already defined
#endif /* #if (defined SGEngTqIndLmtdByTrsm_321T) */

#define SGEngTqIndLmtdByTrsm_321T ComConf_ComSignal_SGEngTqIndLmtdByTrsm_321T

#if (defined Com_SGEngTqIndLmtdByTrsm_321T) /* To prevent double declaration */
#error Com_SGEngTqIndLmtdByTrsm_321T already defined
#endif /* #if (defined Com_SGEngTqIndLmtdByTrsm_321T) */

#define Com_SGEngTqIndLmtdByTrsm_321T ComConf_ComSignal_SGEngTqIndLmtdByTrsm_321T


#if (defined SGTrsmCluStAct_321T) /* To prevent double declaration */
#error SGTrsmCluStAct_321T already defined
#endif /* #if (defined SGTrsmCluStAct_321T) */

#define SGTrsmCluStAct_321T ComConf_ComSignal_SGTrsmCluStAct_321T

#if (defined Com_SGTrsmCluStAct_321T) /* To prevent double declaration */
#error Com_SGTrsmCluStAct_321T already defined
#endif /* #if (defined Com_SGTrsmCluStAct_321T) */

#define Com_SGTrsmCluStAct_321T ComConf_ComSignal_SGTrsmCluStAct_321T


#if (defined SGTrsmMsgCnt_321T) /* To prevent double declaration */
#error SGTrsmMsgCnt_321T already defined
#endif /* #if (defined SGTrsmMsgCnt_321T) */

#define SGTrsmMsgCnt_321T ComConf_ComSignal_SGTrsmMsgCnt_321T

#if (defined Com_SGTrsmMsgCnt_321T) /* To prevent double declaration */
#error Com_SGTrsmMsgCnt_321T already defined
#endif /* #if (defined Com_SGTrsmMsgCnt_321T) */

#define Com_SGTrsmMsgCnt_321T ComConf_ComSignal_SGTrsmMsgCnt_321T


#if (defined SGTrsmNInp_321T) /* To prevent double declaration */
#error SGTrsmNInp_321T already defined
#endif /* #if (defined SGTrsmNInp_321T) */

#define SGTrsmNInp_321T ComConf_ComSignal_SGTrsmNInp_321T

#if (defined Com_SGTrsmNInp_321T) /* To prevent double declaration */
#error Com_SGTrsmNInp_321T already defined
#endif /* #if (defined Com_SGTrsmNInp_321T) */

#define Com_SGTrsmNInp_321T ComConf_ComSignal_SGTrsmNInp_321T


#if (defined SGEngTqIndIncReqdByTrsm_337T) /* To prevent double declaration */
#error SGEngTqIndIncReqdByTrsm_337T already defined
#endif /* #if (defined SGEngTqIndIncReqdByTrsm_337T) */

#define SGEngTqIndIncReqdByTrsm_337T ComConf_ComSignal_SGEngTqIndIncReqdByTrsm_337T

#if (defined Com_SGEngTqIndIncReqdByTrsm_337T) /* To prevent double declaration */
#error Com_SGEngTqIndIncReqdByTrsm_337T already defined
#endif /* #if (defined Com_SGEngTqIndIncReqdByTrsm_337T) */

#define Com_SGEngTqIndIncReqdByTrsm_337T ComConf_ComSignal_SGEngTqIndIncReqdByTrsm_337T


#if (defined SGTrsmFlgFlt_337T) /* To prevent double declaration */
#error SGTrsmFlgFlt_337T already defined
#endif /* #if (defined SGTrsmFlgFlt_337T) */

#define SGTrsmFlgFlt_337T ComConf_ComSignal_SGTrsmFlgFlt_337T

#if (defined Com_SGTrsmFlgFlt_337T) /* To prevent double declaration */
#error Com_SGTrsmFlgFlt_337T already defined
#endif /* #if (defined Com_SGTrsmFlgFlt_337T) */

#define Com_SGTrsmFlgFlt_337T ComConf_ComSignal_SGTrsmFlgFlt_337T


#if (defined SGTrsmFlgShiftProgs_337T) /* To prevent double declaration */
#error SGTrsmFlgShiftProgs_337T already defined
#endif /* #if (defined SGTrsmFlgShiftProgs_337T) */

#define SGTrsmFlgShiftProgs_337T ComConf_ComSignal_SGTrsmFlgShiftProgs_337T

#if (defined Com_SGTrsmFlgShiftProgs_337T) /* To prevent double declaration */
#error Com_SGTrsmFlgShiftProgs_337T already defined
#endif /* #if (defined Com_SGTrsmFlgShiftProgs_337T) */

#define Com_SGTrsmFlgShiftProgs_337T ComConf_ComSignal_SGTrsmFlgShiftProgs_337T


#if (defined SGTrsmGearAct_337T) /* To prevent double declaration */
#error SGTrsmGearAct_337T already defined
#endif /* #if (defined SGTrsmGearAct_337T) */

#define SGTrsmGearAct_337T ComConf_ComSignal_SGTrsmGearAct_337T

#if (defined Com_SGTrsmGearAct_337T) /* To prevent double declaration */
#error Com_SGTrsmGearAct_337T already defined
#endif /* #if (defined Com_SGTrsmGearAct_337T) */

#define Com_SGTrsmGearAct_337T ComConf_ComSignal_SGTrsmGearAct_337T


#if (defined SGTrsmGearTar_337T) /* To prevent double declaration */
#error SGTrsmGearTar_337T already defined
#endif /* #if (defined SGTrsmGearTar_337T) */

#define SGTrsmGearTar_337T ComConf_ComSignal_SGTrsmGearTar_337T

#if (defined Com_SGTrsmGearTar_337T) /* To prevent double declaration */
#error Com_SGTrsmGearTar_337T already defined
#endif /* #if (defined Com_SGTrsmGearTar_337T) */

#define Com_SGTrsmGearTar_337T ComConf_ComSignal_SGTrsmGearTar_337T


#if (defined SGTrsmMILReq_337T) /* To prevent double declaration */
#error SGTrsmMILReq_337T already defined
#endif /* #if (defined SGTrsmMILReq_337T) */

#define SGTrsmMILReq_337T ComConf_ComSignal_SGTrsmMILReq_337T

#if (defined Com_SGTrsmMILReq_337T) /* To prevent double declaration */
#error Com_SGTrsmMILReq_337T already defined
#endif /* #if (defined Com_SGTrsmMILReq_337T) */

#define Com_SGTrsmMILReq_337T ComConf_ComSignal_SGTrsmMILReq_337T


#if (defined SGTrsmStGearLvr_337T) /* To prevent double declaration */
#error SGTrsmStGearLvr_337T already defined
#endif /* #if (defined SGTrsmStGearLvr_337T) */

#define SGTrsmStGearLvr_337T ComConf_ComSignal_SGTrsmStGearLvr_337T

#if (defined Com_SGTrsmStGearLvr_337T) /* To prevent double declaration */
#error Com_SGTrsmStGearLvr_337T already defined
#endif /* #if (defined Com_SGTrsmStGearLvr_337T) */

#define Com_SGTrsmStGearLvr_337T ComConf_ComSignal_SGTrsmStGearLvr_337T


#if (defined SGTrsmStGearMode_337T) /* To prevent double declaration */
#error SGTrsmStGearMode_337T already defined
#endif /* #if (defined SGTrsmStGearMode_337T) */

#define SGTrsmStGearMode_337T ComConf_ComSignal_SGTrsmStGearMode_337T

#if (defined Com_SGTrsmStGearMode_337T) /* To prevent double declaration */
#error Com_SGTrsmStGearMode_337T already defined
#endif /* #if (defined Com_SGTrsmStGearMode_337T) */

#define Com_SGTrsmStGearMode_337T ComConf_ComSignal_SGTrsmStGearMode_337T


#if (defined SGTrsmTOil_337T) /* To prevent double declaration */
#error SGTrsmTOil_337T already defined
#endif /* #if (defined SGTrsmTOil_337T) */

#define SGTrsmTOil_337T ComConf_ComSignal_SGTrsmTOil_337T

#if (defined Com_SGTrsmTOil_337T) /* To prevent double declaration */
#error Com_SGTrsmTOil_337T already defined
#endif /* #if (defined Com_SGTrsmTOil_337T) */

#define Com_SGTrsmTOil_337T ComConf_ComSignal_SGTrsmTOil_337T


#if (defined SGTrsmTOilWrnLmpReq_337T) /* To prevent double declaration */
#error SGTrsmTOilWrnLmpReq_337T already defined
#endif /* #if (defined SGTrsmTOilWrnLmpReq_337T) */

#define SGTrsmTOilWrnLmpReq_337T ComConf_ComSignal_SGTrsmTOilWrnLmpReq_337T

#if (defined Com_SGTrsmTOilWrnLmpReq_337T) /* To prevent double declaration */
#error Com_SGTrsmTOilWrnLmpReq_337T already defined
#endif /* #if (defined Com_SGTrsmTOilWrnLmpReq_337T) */

#define Com_SGTrsmTOilWrnLmpReq_337T ComConf_ComSignal_SGTrsmTOilWrnLmpReq_337T


/* External Rx Group Signal IDs defines */
/* External Tx Group Signal IDs defines */
/* External Rx Signal Group IDs defines */
/* External Tx Signal Group IDs defines */
#endif /* (!defined COM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES) */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/** @} doxygen end group definition */
#endif /* if !defined( COM_SYMBOLIC_NAMES_PB_CFG_H ) */
/*==================[end of file]===========================================*/
