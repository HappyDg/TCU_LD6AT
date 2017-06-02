/*
 * This is Os_Cfg.h, auto-generated for:
 *   Project: HCU_PATAC_OS
 *   Target:  TriCoreHighTec
 *   Variant: TC23x
 *   Version: 5.0.9
 *   [$UKS 650]
 */
#ifndef OS_CFG_H
#define OS_CFG_H
/* -- Start expansion of <Os_Safe_Cfg.h> -- */
/* -- Start expansion of <Os_Target_Cfg.h> -- */
#define OS_TARGET_TRICOREHIGHTEC
#define OS_TRICORE_UNTRUSTED_MASK 0x1000U
#define OS_CAT1_ID_SWFAIL_vidDefaultIsr ((uint32)INVALID_ISR)
#define OS_INIT_SRC_CANINT6 (0x401U)
#define OS_INIT_SRC_CANINT3 (0x402U)
#define OS_INIT_SRC_CANINT0 (0x403U)
#define OS_INIT_SRC_CAN1INT7 (0x404U)
#define OS_INIT_SRC_CANINT4 (0x405U)
#define OS_INIT_SRC_CANINT1 (0x406U)
#define OS_INIT_SRC_CANINT8 (0x407U)
#define OS_INIT_SRC_CANINT5 (0x408U)
#define OS_INIT_SRC_CANINT2 (0x409U)
#define OS_INIT_SRC_DMACH6 (0x40aU)
#define OS_INIT_SRC_DMACH7 (0x40bU)
#define OS_INIT_SRC_DMACH4 (0x40cU)
#define OS_INIT_SRC_DMACH5 (0x40dU)
#define OS_INIT_SRC_STM0SR0 (0x40eU)
#define OS_INIT_SRC_QSPI3ERR (0x40fU)
#define OS_INIT_SRC_QSPI3PT (0x410U)
#define OS_INIT_SRC_QSPI3U (0x411U)
#define OS_INIT_SRC_QSPI2ERR (0x412U)
#define OS_INIT_SRC_QSPI2PT (0x413U)
#define OS_INIT_SRC_QSPI2U (0x414U)
#define OS_INIT_SRC_GPSR00 (0x415U)
#define OS_INIT_SRC_VADCG0SR0 (0x416U)
#define OS_INIT_SRC_GTMTOM07 (0x417U)
#define OS_INIT_SRC_GTMTIM03 (0x418U)
#define OS_VEC_SRC_CAN_CAN0_INT6_ISR (1U)
#define OS_VEC_SRC_CAN_CAN0_INT3_ISR (2U)
#define OS_VEC_SRC_CAN_CAN0_INT0_ISR (3U)
#define OS_VEC_SRC_CAN_CAN0_INT7_ISR (4U)
#define OS_VEC_SRC_CAN_CAN0_INT4_ISR (5U)
#define OS_VEC_SRC_CAN_CAN0_INT1_ISR (6U)
#define OS_VEC_SRC_CAN_CAN0_INT8_ISR (7U)
#define OS_VEC_SRC_CAN_CAN0_INT5_ISR (8U)
#define OS_VEC_SRC_CAN_CAN0_INT2_ISR (9U)
#define OS_VEC_DMA_ISR_QSPI3RX (10U)
#define OS_VEC_DMA_ISR_QSPI3TX (11U)
#define OS_VEC_DMA_ISR_QSPI2RX (12U)
#define OS_VEC_DMA_ISR_QSPI2TX (13U)
#define OS_VEC_MAIN_OSISR_P_PIM1ms (14U)
#define OS_VEC_SRC_QSPI_QSPI3_ERR_ISR (15U)
#define OS_VEC_SRC_QSPI_QSPI3_PT_ISR (16U)
#define OS_VEC_SRC_QSPI_QSPI3_U_ISR (17U)
#define OS_VEC_SRC_QSPI_QSPI2_ERR_ISR (18U)
#define OS_VEC_SRC_QSPI_QSPI2_PT_ISR (19U)
#define OS_VEC_SRC_QSPI_QSPI2_U_ISR (20U)
#define OS_VEC_TSKSRV_ACTIVATION_MANAGER_IT (21U)
#define OS_VEC_ISR_GRP_0_END_OF_CONV (22U)
#define OS_VEC_SRC_GTM_GTM0_TOM0_7_ISR (23U)
#define OS_VEC_SRC_GTM_GTM0_TIM0_3_ISR (24U)
#define OS_NUM_SRNS (178U)
DECLARE_CAT1_ISR(ISR_GRP_0_END_OF_CONV);  /* [$TargetHT 161] */
DECLARE_CAT1_ISR(SRC_GTM_GTM0_TOM0_7_ISR);  /* [$TargetHT 161] */
DECLARE_CAT1_ISR(SRC_GTM_GTM0_TIM0_3_ISR);  /* [$TargetHT 161] */
DECLARE_CAT1_ISR(SWFAIL_vidDefaultIsr);

#define OS_CAT1_ID_ISR_GRP_0_END_OF_CONV (1U)
#define OS_CAT1_ID_SRC_GTM_GTM0_TOM0_7_ISR (2U)
#define OS_CAT1_ID_SRC_GTM_GTM0_TIM0_3_ISR (3U)

/* -- End expansion of <Os_Target_Cfg.h> -- */

#define OS_NUM_APPMODES (2U)
#define OS_NUM_APPLICATIONS (1U)
#define OS_NUM_SPINLOCKS (0U)
#define OS_NUM_TRUSTED_FUNCTIONS (0U)
#define OS_NUM_EVENTS (0U)
#define OS_NUM_TASKS (15U)
#define OS_NUM_ISRS (21U)
#define OS_NUM_RESOURCES (1U)
#define OS_NUM_ALARMS (0U)
#define OS_NUM_SCHEDULETABLES (2U)
#define OS_NUM_TRACEPOINTS (1U)
#define OS_NUM_TASKTRACEPOINTS (0U)
#define OS_NUM_INTERVALS (0U)
#define OS_NUM_TRACECATEGORIES (0U)
#define OS_TRACE_CATEGORY_ALWAYS ((Os_TraceCategoriesType)(0x80000000UL))
#define OS_TRACE_CATEGORY_NEVER  ((Os_TraceCategoriesType)(0x00000000UL))

/* [MISRA 2004 Rule 19.7] */ /*lint -estring(961, OS_TICKS2*) */
#define OS_NUM_COUNTERS (2U)
#define OSCYCLEDURATION (5) /* [$UKS 1224] */
#define OSCYCLESPERSECOND (200000000U) /* [$UKS 1225] */
#define OSSWTICKDURATION (5) /* [$UKS 1226] */
#define OSSWTICKSPERSECOND (200000000U) /* [$UKS 1227] */
#define OS_TICKS2NS_MAIN_OSCNT_PIM1ms(ticks) ((PhysicalTimeType)((ticks) * 1000000U)) /* [$UKS 843] */
#define OS_TICKS2US_MAIN_OSCNT_PIM1ms(ticks) ((PhysicalTimeType)((ticks) * 1000U)) /* [$UKS 843] */
#define OS_TICKS2MS_MAIN_OSCNT_PIM1ms(ticks) ((PhysicalTimeType)((ticks) * 1U)) /* [$UKS 843] */
#define OS_TICKS2SEC_MAIN_OSCNT_PIM1ms(ticks) ((PhysicalTimeType)((ticks) / 1000U)) /* [$UKS 843] */
#define OSMAXALLOWEDVALUE_MAIN_OSCNT_PIM1ms (65535U) /* [$UKS 219] */
#define OSTICKSPERBASE_MAIN_OSCNT_PIM1ms (1U) /* [$UKS 220] */
#define OSTICKDURATION_MAIN_OSCNT_PIM1ms OS_TICKS2NS_MAIN_OSCNT_PIM1ms(1U) /* [$UKS 221] */
#define OSMINCYCLE_MAIN_OSCNT_PIM1ms (1U) /* [$UKS 222] */
#define OS_TICKS2NS_MAIN_OSCNT_PIM50ms(ticks) ((PhysicalTimeType)((ticks) * 50000000U)) /* [$UKS 843] */
#define OS_TICKS2US_MAIN_OSCNT_PIM50ms(ticks) ((PhysicalTimeType)((ticks) * 50000U)) /* [$UKS 843] */
#define OS_TICKS2MS_MAIN_OSCNT_PIM50ms(ticks) ((PhysicalTimeType)((ticks) * 50U)) /* [$UKS 843] */
#define OS_TICKS2SEC_MAIN_OSCNT_PIM50ms(ticks) ((PhysicalTimeType)((ticks) / 20U)) /* [$UKS 843] */
#define OSMAXALLOWEDVALUE_MAIN_OSCNT_PIM50ms (65535U) /* [$UKS 219] */
#define OSTICKSPERBASE_MAIN_OSCNT_PIM50ms (2U) /* [$UKS 220] */
#define OSTICKDURATION_MAIN_OSCNT_PIM50ms OS_TICKS2NS_MAIN_OSCNT_PIM50ms(1U) /* [$UKS 221] */
#define OSMINCYCLE_MAIN_OSCNT_PIM50ms (1U) /* [$UKS 222] */
#define OSMAXALLOWEDVALUE OSMAXALLOWEDVALUE_SystemCounter /* [$UKS 215] */
#define OSTICKSPERBASE OSTICKSPERBASE_SystemCounter /* [$UKS 216] */
#define OSMINCYCLE OSMINCYCLE_SystemCounter /* [$UKS 218] */
#define OSTICKDURATION OSTICKDURATION_SystemCounter /* [$UKS 217] */
#define OS_NUM_CORES (1U)
#define OS_NUM_OS_CORES (1U)
#define OS_CORE_ID_MASTER (0U)  /* [$UKS 1609] */


/* ------------------------------------------------- */
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_START_SEC_CALLOUT_CODE
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_CALLOUT_CODE) StartupHook_MAIN_OSAPP(void) /* [$UKS 401] */;
extern FUNC(void, OS_CALLOUT_CODE) ShutdownHook_MAIN_OSAPP(StatusType Error) /* [$UKS 405] */;
extern FUNC(void, OS_CALLOUT_CODE) ErrorHook_MAIN_OSAPP(StatusType Error) /* [$UKS 450] */;
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_STOP_SEC_CALLOUT_CODE
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */

/* ------------------------------------------------- */
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_START_SEC_CODE_LIB
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(StatusType, OS_CODE) Os_IncrementCounter_MAIN_OSCNT_PIM1ms(void);
extern FUNC(StatusType, OS_CODE) Os_IncrementCounter_MAIN_OSCNT_PIM50ms(void);
extern FUNC(void, OS_CODE) Os_Entry_OSTSK_S_RTMCLD_CPU_LOAD_MNG(void);
extern FUNC(void, OS_CODE) Os_Entry_OSTSK_S_WTDG_REFRESH_WATCHDOG(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_WATCHDOG(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_POWER_DOWN(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_POWER_UP(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_1000MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_200MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_100MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_50MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_20MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_10MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_5MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_2MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_TIME_1MS(void);
extern FUNC(void, OS_CODE) Os_Entry_TASK_INIT(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT6_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT3_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT0_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT7_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT4_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT1_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT8_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT5_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_CAN_CAN0_INT2_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_DMA_ISR_QSPI3RX(void);
extern FUNC(void, OS_CODE) Os_Entry_DMA_ISR_QSPI3TX(void);
extern FUNC(void, OS_CODE) Os_Entry_DMA_ISR_QSPI2RX(void);
extern FUNC(void, OS_CODE) Os_Entry_DMA_ISR_QSPI2TX(void);
extern FUNC(void, OS_CODE) Os_Entry_MAIN_OSISR_P_PIM1ms(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_QSPI_QSPI3_ERR_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_QSPI_QSPI3_PT_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_QSPI_QSPI3_U_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_QSPI_QSPI2_ERR_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_QSPI_QSPI2_PT_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_SRC_QSPI_QSPI2_U_ISR(void);
extern FUNC(void, OS_CODE) Os_Entry_TSKSRV_ACTIVATION_MANAGER_IT(void);
/* [MISRA 2004 Rule 19.1] */ /*lint -save -esym(961, 19.1) */
#define OS_STOP_SEC_CODE_LIB
#include "MemMap.h" /* [MISRA 2004 Rule 19.15] */ /*lint !e537 !e451 */
/*lint -restore */


/* -- End expansion of <Os_Safe_Cfg.h> -- */





/* -------- AppMode declarations --------- */
#define OS_NOAPPMODE ((AppModeType)0U)
#define OSDEFAULTAPPMODE ((AppModeType)1U)  /* [$UKS 381] [$UKS 383] */

/* ----- OS-Application declarations ----- */
#define MAIN_OSAPP ((ApplicationType)1U) /* [$UKS 412] */

/* -------- Event declarations --------- */

/* -------- Task declarations --------- */

#define OSTSK_S_RTMCLD_CPU_LOAD_MNG (&Os_const_tasks[0U])
DeclareTask(OSTSK_S_RTMCLD_CPU_LOAD_MNG)
#define OSTSK_S_WTDG_REFRESH_WATCHDOG (&Os_const_tasks[1U])
DeclareTask(OSTSK_S_WTDG_REFRESH_WATCHDOG)
#define TASK_WATCHDOG (&Os_const_tasks[2U])
DeclareTask(TASK_WATCHDOG)
#define TASK_POWER_DOWN (&Os_const_tasks[3U])
DeclareTask(TASK_POWER_DOWN)
#define TASK_POWER_UP (&Os_const_tasks[4U])
DeclareTask(TASK_POWER_UP)
#define TASK_TIME_1000MS (&Os_const_tasks[5U])
DeclareTask(TASK_TIME_1000MS)
#define TASK_TIME_200MS (&Os_const_tasks[6U])
DeclareTask(TASK_TIME_200MS)
#define TASK_TIME_100MS (&Os_const_tasks[7U])
DeclareTask(TASK_TIME_100MS)
#define TASK_TIME_50MS (&Os_const_tasks[8U])
DeclareTask(TASK_TIME_50MS)
#define TASK_TIME_20MS (&Os_const_tasks[9U])
DeclareTask(TASK_TIME_20MS)
#define TASK_TIME_10MS (&Os_const_tasks[10U])
DeclareTask(TASK_TIME_10MS)
#define TASK_TIME_5MS (&Os_const_tasks[11U])
DeclareTask(TASK_TIME_5MS)
#define TASK_TIME_2MS (&Os_const_tasks[12U])
DeclareTask(TASK_TIME_2MS)
#define TASK_TIME_1MS (&Os_const_tasks[13U])
DeclareTask(TASK_TIME_1MS)
#define TASK_INIT (&Os_const_tasks[14U])
DeclareTask(TASK_INIT)

/* -------- ISR declarations --------- */
#define SRC_CAN_CAN0_INT6_ISR (&Os_const_isrs[0U])
DeclareISR(SRC_CAN_CAN0_INT6_ISR)
#define SRC_CAN_CAN0_INT3_ISR (&Os_const_isrs[1U])
DeclareISR(SRC_CAN_CAN0_INT3_ISR)
#define SRC_CAN_CAN0_INT0_ISR (&Os_const_isrs[2U])
DeclareISR(SRC_CAN_CAN0_INT0_ISR)
#define SRC_CAN_CAN0_INT7_ISR (&Os_const_isrs[3U])
DeclareISR(SRC_CAN_CAN0_INT7_ISR)
#define SRC_CAN_CAN0_INT4_ISR (&Os_const_isrs[4U])
DeclareISR(SRC_CAN_CAN0_INT4_ISR)
#define SRC_CAN_CAN0_INT1_ISR (&Os_const_isrs[5U])
DeclareISR(SRC_CAN_CAN0_INT1_ISR)
#define SRC_CAN_CAN0_INT8_ISR (&Os_const_isrs[6U])
DeclareISR(SRC_CAN_CAN0_INT8_ISR)
#define SRC_CAN_CAN0_INT5_ISR (&Os_const_isrs[7U])
DeclareISR(SRC_CAN_CAN0_INT5_ISR)
#define SRC_CAN_CAN0_INT2_ISR (&Os_const_isrs[8U])
DeclareISR(SRC_CAN_CAN0_INT2_ISR)
#define DMA_ISR_QSPI3RX (&Os_const_isrs[9U])
DeclareISR(DMA_ISR_QSPI3RX)
#define DMA_ISR_QSPI3TX (&Os_const_isrs[10U])
DeclareISR(DMA_ISR_QSPI3TX)
#define DMA_ISR_QSPI2RX (&Os_const_isrs[11U])
DeclareISR(DMA_ISR_QSPI2RX)
#define DMA_ISR_QSPI2TX (&Os_const_isrs[12U])
DeclareISR(DMA_ISR_QSPI2TX)
#define MAIN_OSISR_P_PIM1ms (&Os_const_isrs[13U])
DeclareISR(MAIN_OSISR_P_PIM1ms)
#define SRC_QSPI_QSPI3_ERR_ISR (&Os_const_isrs[14U])
DeclareISR(SRC_QSPI_QSPI3_ERR_ISR)
#define SRC_QSPI_QSPI3_PT_ISR (&Os_const_isrs[15U])
DeclareISR(SRC_QSPI_QSPI3_PT_ISR)
#define SRC_QSPI_QSPI3_U_ISR (&Os_const_isrs[16U])
DeclareISR(SRC_QSPI_QSPI3_U_ISR)
#define SRC_QSPI_QSPI2_ERR_ISR (&Os_const_isrs[17U])
DeclareISR(SRC_QSPI_QSPI2_ERR_ISR)
#define SRC_QSPI_QSPI2_PT_ISR (&Os_const_isrs[18U])
DeclareISR(SRC_QSPI_QSPI2_PT_ISR)
#define SRC_QSPI_QSPI2_U_ISR (&Os_const_isrs[19U])
DeclareISR(SRC_QSPI_QSPI2_U_ISR)
#define TSKSRV_ACTIVATION_MANAGER_IT (&Os_const_isrs[20U])
DeclareISR(TSKSRV_ACTIVATION_MANAGER_IT)

/* -------- Resource declarations --------- */
#define RES_SCHEDULER (&Os_const_resources[0U])
DeclareResource(RES_SCHEDULER)

/* -------- Counter declarations --------- */
#define MAIN_OSCNT_PIM1ms (&Os_const_counters[0U])
DeclareCounter(MAIN_OSCNT_PIM1ms)
#define MAIN_OSCNT_PIM50ms (&Os_const_counters[1U])
DeclareCounter(MAIN_OSCNT_PIM50ms)

/* -------- Alarm declaration --------- */

/* -------- ScheduleTable declaration --------- */

#define MAIN_OSSCT_PIM1ms (&Os_const_scheduletables[0U])
#define OS_DURATION_MAIN_OSSCT_PIM1ms (100U)
DeclareScheduleTable(MAIN_OSSCT_PIM1ms)
#define MAIN_OSSCT_PIM50ms (&Os_const_scheduletables[1U])
#define OS_DURATION_MAIN_OSSCT_PIM50ms (20U)
DeclareScheduleTable(MAIN_OSSCT_PIM50ms)

/* -------- Tracepoint declarations --------- */
#define OSApp_MAIN_OSAPP (1U)

/* -------- TaskTracepoint declarations --------- */

/* -------- Interval declarations --------- */

/* -------- Filtered APIs --------- */
#define Os_LogTracepoint(TpointID,Category) /* never */
#define Os_LogTracepointValue(TpointID,Value,Category) /* never */
#define Os_LogTracepointData(TpointID,Data,Length,Category) /* never */
#define Os_LogTaskTracepoint(TTpointID,Category) /* never */
#define Os_LogTaskTracepointValue(TTpointID,Value,Category) /* never */
#define Os_LogTaskTracepointData(TTpointID,Data,Length,Category) /* never */
#define Os_LogIntervalStart(IntervalID,Category) /* never */
#define Os_LogIntervalStartValue(IntervalID,Value,Category) /* never */
#define Os_LogIntervalStartData(IntervalID,Data,Length,Category) /* never */
#define Os_LogIntervalEnd(IntervalID,Category) /* never */
#define Os_LogIntervalEndValue(IntervalID,Value,Category) /* never */
#define Os_LogIntervalEndData(IntervalID,Data,Length,Category) /* never */
#ifndef OS_TRACE_NAMESPACE_PURE /* [$UKS 1154] */
/* [MISRA 2004 Rule 19.7] */ /*lint -estring(961, LogTrace* ,LogTaskTrace* ,LogInterval*) */  #define LogTracepoint(TpointID,Category) Os_LogTracepoint(TpointID,Category)
  #define LogTracepointValue(TpointID,Value,Category) Os_LogTracepointValue(TpointID,Value,Category)
  #define LogTracepointData(TpointID,Data,Length,Category) Os_LogTracepointData(TpointID,Data,Length,Category)
  #define LogTaskTracepoint(TTpointID,Category) Os_LogTaskTracepoint(TTpointID,Category)
  #define LogTaskTracepointValue(TTpointID,Value,Category) Os_LogTaskTracepointValue(TTpointID,Value,Category)
  #define LogTaskTracepointData(TTpointID,Data,Length,Category) Os_LogTaskTracepointData(TTpointID,Data,Length,Category)
  #define LogIntervalStart(IntervalID,Category) Os_LogIntervalStart(IntervalID,Category)
  #define LogIntervalStartValue(IntervalID,Value,Category) Os_LogIntervalStartValue(IntervalID,Value,Category)
  #define LogIntervalStartData(IntervalID,Data,Length,Category) Os_LogIntervalStartData(IntervalID,Data,Length,Category)
  #define LogIntervalEnd(IntervalID,Category) Os_LogIntervalEnd(IntervalID,Category)
  #define LogIntervalEndValue(IntervalID,Value,Category) Os_LogIntervalEndValue(IntervalID,Value,Category)
  #define LogIntervalEndData(IntervalID,Data,Length,Category) Os_LogIntervalEndData(IntervalID,Data,Length,Category)
#endif

#define Os_Cat1_ISR_GRP_0_END_OF_CONV (38U)
#define Os_Cat1_SRC_GTM_GTM0_TOM0_7_ISR (39U)
#define Os_Cat1_SRC_GTM_GTM0_TIM0_3_ISR (40U)
/* [MISRA 2004 Rule 19.12] */ /*lint -save -esym(960, 19.12) */
/* [MISRA 2004 Rule 19.13] */ /*lint -save -esym(961, 19.13) */
#define Os_LogCat1ISRStart(IsrId)  /* [$UKS 1036] [$UKS 1037] [$UKS 1177] */
/*lint -restore */
/*lint -restore */
/* [MISRA 2004 Rule 19.12] */ /*lint -save -esym(960, 19.12) */
/* [MISRA 2004 Rule 19.13] */ /*lint -save -esym(961, 19.13) */
#define Os_LogCat1ISREnd(IsrId)  /* [$UKS 1038] [$UKS 1039] [$UKS 1178] */
/*lint -restore */
/*lint -restore */

#ifndef OS_TRACE_NAMESPACE_PURE /* [$UKS 1154] */
  #define LogCat1ISRStart Os_LogCat1ISRStart
  #define LogCat1ISREnd Os_LogCat1ISREnd
#endif
#endif /* OS_CFG_H */
