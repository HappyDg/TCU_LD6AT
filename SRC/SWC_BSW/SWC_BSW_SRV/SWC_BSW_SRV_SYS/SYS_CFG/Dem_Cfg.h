/**
 * \file
 *
 * \brief AUTOSAR Dem
 *
 * This file contains the implementation of the AUTOSAR
 * module Dem.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined DEM_CFG_H)
#define DEM_CFG_H

/* This file contains all target independent public configuration declarations
 * for the AUTOSAR module Dem. */


/*==================[includes]==============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <Dem_IntErrId.h>        /* BSW Event ID symbols */
#include <Dem_IntEvtId.h>        /* SW-C Event ID symbols */


/*==================[macros]================================================*/

/*------------------[DTC configuration]-------------------------------------*/

#if (defined DEM_NO_DTC)
#error DEM_NO_DTC already defined
#endif
/** \brief No DTC (neither UDS nor OBD) configured for event */
#define DEM_NO_DTC                 0U

#if (defined DEM_NO_DTC_FUNCTIONAL_UNIT)
#error DEM_NO_DTC_FUNCTIONAL_UNIT already defined
#endif
/** \brief No DTC functional unit configured for event */
#define DEM_NO_DTC_FUNCTIONAL_UNIT 0U

/*------------------[General]-----------------------------------------------*/

#if (defined DEM_VERSION_INFO_API)
#error DEM_VERSION_INFO_API already defined
#endif
/** \brief Switch, indicating if Version Info is activated for Dem */
#define DEM_VERSION_INFO_API         STD_OFF

#if (defined DEM_DTC_STATUS_AVAILABILITY_MASK)
#error DEM_DTC_STATUS_AVAILABILITY_MASK already defined
#endif
/** \brief DTC status availability mask */
#define DEM_DTC_STATUS_AVAILABILITY_MASK    9U

#if (defined DEM_STATUS_BIT_STORAGE_TF)
#error DEM_STATUS_BIT_STORAGE_TF already defined
#endif
/** \brief Switch, indicating if permanent storage of the "TestFailed" status bit is activated */
#define DEM_STATUS_BIT_STORAGE_TF    STD_ON

#if (defined DEM_USE_PERMANENT_STORAGE)
#error DEM_USE_PERMANENT_STORAGE already defined
#endif
/** \brief Switch, indicating if Permanent storage of event memory entries in NvM is activated for
 ** Dem */
#define DEM_USE_PERMANENT_STORAGE    STD_ON

#if (defined DEM_OPCYC_NVSTORAGE)
#error DEM_OPCYC_NVSTORAGE already defined
#endif
/** \brief Switch, indicating if permanent storage of operation cycle entries
 ** to NVRAM is enabled */
#define DEM_OPCYC_NVSTORAGE          STD_OFF

#if (defined DEM_OPCYCLESTATE)
#error DEM_OPCYCLESTATE already defined
#endif
/** \brief Macro to get the operation cycle states based on permanent storage
 ** of operation cycle entries to NVRAM */
#define DEM_OPCYCLESTATE             Dem_OpCycleState

#if (defined DEM_NUM_DEBOUNCE_COUNTER_PERM)
#error DEM_NUM_DEBOUNCE_COUNTER_PERM already defined
#endif
/** \brief Number of counter debounced events with permanent debounce
 ** counter storage
 **/
#define DEM_NUM_DEBOUNCE_COUNTER_PERM  0U

#if (defined DEM_NVM_BLOCK_ID_INVALID)
#error DEM_NVM_BLOCK_ID_INVALID already defined
#endif
/** \brief NvM block Id does not exist as it is not configured */
#define DEM_NVM_BLOCK_ID_INVALID      0U

#if (defined DEM_NVM_BLOCK_ID_DEFAULT)
#error DEM_NVM_BLOCK_ID_DEFAULT already defined
#endif
/** \brief NvM block Id for Dem default block */
#define DEM_NVM_BLOCK_ID_DEFAULT  NvM_DEM

#if (defined DEM_TYPE_OF_ORIGIN_SUPPORTED)
#error DEM_TYPE_OF_ORIGIN_SUPPORTED already defined
#endif
/** \brief Supported origin types
 **
 ** This macro is only exported and not used internally.
 ** It is derived from ::DEM_MAX_NUMBER_EVENT_ENTRY_PRI,
 ** ::DEM_MAX_NUMBER_EVENT_ENTRY_SEC, ::DEM_MAX_NUMBER_EVENT_ENTRY_MIR, and
 ** ::DEM_MAX_NUMBER_EVENT_ENTRY_PER.
 **
 ** \note Macro name is still existing for compatibility reasons with AR2.1.
 **/
#define DEM_TYPE_OF_ORIGIN_SUPPORTED 1U

#if (defined DEM_DEV_ERROR_DETECT)
#error DEM_DEV_ERROR_DETECT already defined
#endif
/* !LINKSTO Dem113,1 */
/** \brief Switch, indicating if development error detection is activated for
 ** Dem */
#define DEM_DEV_ERROR_DETECT         STD_OFF

#if (defined DEM_TYPE_OF_DTC_SUPPORTED)
#error DEM_TYPE_OF_DTC_SUPPORTED already defined
#endif
/** \brief Returned DTC translation format by Dem_GetTranslationType()
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_TYPE_OF_DTC_SUPPORTED    DEM_DTC_TRANSLATION_ISO15031_6

#if (defined DEM_INCLUDE_RTE)
#error DEM_INCLUDE_RTE already defined
#endif
/** \brief Switch, indicating if RTE is available and can be used from Dem */
#define DEM_INCLUDE_RTE              STD_OFF

#if (defined DEM_DCM_ENABLED)
#error DEM_DCM_ENABLED already defined
#endif
/** \brief Switch, indicating whether Dcm module should be a part of Dem */
#define DEM_DCM_ENABLED              STD_ON

#if (defined DEM_GET_SIZEOFEDRBYDTC_OPTIMIZATION)
#error DEM_GET_SIZEOFEDRBYDTC_OPTIMIZATION already defined
#endif
/** \brief Switch, indicating optimization for calculating size in
 ** Dem_GetSizeOfExtendedDataRecordByDTC() provided to the Dcm */
#define DEM_GET_SIZEOFEDRBYDTC_OPTIMIZATION      STD_OFF

#if (defined DEM_TRIGGER_FIM_REPORTS)
#error DEM_TRIGGER_FIM_REPORTS already defined
#endif
/** \brief Switch, indicating if notification to FiM is activated for Dem */
#define DEM_TRIGGER_FIM_REPORTS      STD_OFF

#if (defined DEM_TRIGGER_DCM_REPORTS)
#error DEM_TRIGGER_DCM_REPORTS already defined
#endif
/** \brief Switch, indicating if notification to Dcm is activated for Dem */
#define DEM_TRIGGER_DCM_REPORTS      STD_OFF


#if (defined DEM_USE_DYNAMIC_DTCS)
#error DEM_USE_DYNAMIC_DTCS already defined
#endif
/** \brief Macro for Enabling/Disabling dynamic DTC fetching */
#define DEM_USE_DYNAMIC_DTCS   STD_OFF

#if (defined DEM_USE_EVENT_DISPLACEMENT)
#error DEM_USE_EVENT_DISPLACEMENT already defined
#endif
/** \brief Switch, indicating if event displacement support is activated for
 ** Dem */
#define DEM_USE_EVENT_DISPLACEMENT   STD_ON

#ifndef DEM_STATUS_BIT_AGING_AND_DISPLACEMENT
/** \brief The "TestFailedSinceLastClear" status bits are reset to 0, if
 ** aging or displacement applies (like done for the "ConfirmedDTC" status
 ** bits) */
#define DEM_STATUS_BIT_AGING_AND_DISPLACEMENT  0x00U
#endif

#ifndef DEM_STATUS_BIT_NORMAL
/** \brief The aging and displacement has no impact on the
 ** "TestFailedSinceLastClear" status bits */
#define DEM_STATUS_BIT_NORMAL                  0x01U
#endif

#if (defined DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR)
#error DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR already defined
#endif
/** \brief Switch, indicating if the aging and displacement mechanism shall be
 ** applied to the "TestFailedSinceLastClear" status bits */
#define DEM_STATUS_BIT_HANDLING_TESTFAILEDSINCELASTCLEAR \
  DEM_STATUS_BIT_AGING_AND_DISPLACEMENT

#if (defined DEM_CLRRESP_VOLATILE)
#error DEM_CLRRESP_VOLATILE already defined
#endif
#define DEM_CLRRESP_VOLATILE            0U

#if (defined DEM_CLRRESP_NONVOLATILE_TRIGGER)
#error DEM_CLRRESP_NONVOLATILE_TRIGGER already defined
#endif
#define DEM_CLRRESP_NONVOLATILE_TRIGGER 1U

#if (defined DEM_CLRRESP_NONVOLATILE_FINISH)
#error DEM_CLRRESP_NONVOLATILE_FINISH already defined
#endif
#define DEM_CLRRESP_NONVOLATILE_FINISH  2U

#if (defined DEM_CLEAR_DTC_BEHAVIOR)
#error DEM_CLEAR_DTC_BEHAVIOR already defined
#endif
/** \brief Behaviour of ClearDTC */
#define DEM_CLEAR_DTC_BEHAVIOR  DEM_CLRRESP_VOLATILE

/*------------------[Freeze frame configuration]----------------------------*/

/* Symbolic names of configured freeze frame data IDs */

#if (defined DEM_FFS_DID_DID_ApmElecValU14)
#error DEM_FFS_DID_DID_ApmElecValU14 already defined
#endif
/** \brief Symbolic name of data ID DID_ApmElecValU14 */
#define DEM_FFS_DID_DID_ApmElecValU14 64768U

#if (defined DEM_FFS_DID_DID_ApmElecValI14)
#error DEM_FFS_DID_DID_ApmElecValI14 already defined
#endif
/** \brief Symbolic name of data ID DID_ApmElecValI14 */
#define DEM_FFS_DID_DID_ApmElecValI14 64769U

#if (defined DEM_FFS_DID_DID_ApmElecValUHV)
#error DEM_FFS_DID_DID_ApmElecValUHV already defined
#endif
/** \brief Symbolic name of data ID DID_ApmElecValUHV */
#define DEM_FFS_DID_DID_ApmElecValUHV 64770U

#if (defined DEM_FFS_DID_DID_ApmElecValIHV)
#error DEM_FFS_DID_DID_ApmElecValIHV already defined
#endif
/** \brief Symbolic name of data ID DID_ApmElecValIHV */
#define DEM_FFS_DID_DID_ApmElecValIHV 64771U

#if (defined DEM_FFS_DID_DID_ApmElecValTemp)
#error DEM_FFS_DID_DID_ApmElecValTemp already defined
#endif
/** \brief Symbolic name of data ID DID_ApmElecValTemp */
#define DEM_FFS_DID_DID_ApmElecValTemp 64772U

#if (defined DEM_FF_RECNUM_CALCULATED)
#error DEM_FF_RECNUM_CALCULATED already defined
#endif
/** \brief Freeze frame records will be numbered consecutive starting by 1 in
 ** their chronological order */
#define DEM_FF_RECNUM_CALCULATED     0x00U

#if (defined DEM_FF_RECNUM_CONFIGURED)
#error DEM_FF_RECNUM_CONFIGURED already defined
#endif
/** \brief Freeze frame records will be numbered based on the given
 ** configuration in their chronological order */
#define DEM_FF_RECNUM_CONFIGURED     0x01U

#if (defined DEM_FREEZE_FRAME_REC_NUMERATION_TYPE)
#error DEM_FREEZE_FRAME_REC_NUMERATION_TYPE already defined
#endif
/** \brief Type of assignment of freeze frame record numbers
 **
 ** This switch defines the type for assigning freeze frame record numbers for
 ** event-specific freeze frame records.
 **/
#define DEM_FREEZE_FRAME_REC_NUMERATION_TYPE  DEM_FF_RECNUM_CALCULATED

#if (defined DEM_MAX_NUMBER_PRESTORED_FF)
#error DEM_MAX_NUMBER_PRESTORED_FF already defined
#endif
/** \brief Maximum number of available prestored freeze frames
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_MAX_NUMBER_PRESTORED_FF 0U

/*------------------[Extended data configuration]---------------------------*/

/* Symbolic names of configured extended data record numbers */

#if (defined DEM_EDS_NUM_EXTDATAREC_0)
#error DEM_EDS_NUM_EXTDATAREC_0 already defined
#endif
/** \brief Symbolic name of extended data EXTDATAREC_0 */
#define DEM_EDS_NUM_EXTDATAREC_0 1U

/*------------------[Fault confirmation configurations]---------------------*/

#if (defined DEM_NUM_FAILURECYCLES)
#error DEM_NUM_FAILURECYCLES already defined
#endif
/** \brief Number of fault confirmation configurations */
#define DEM_NUM_FAILURECYCLES 1U

#if (defined DEM_EVENTFAILURECOUNTER_BUFFER_SIZE)
#error DEM_EVENTFAILURECOUNTER_BUFFER_SIZE already defined
#endif
/** \brief Maximal number of event failure counter buffer entries */
#define DEM_EVENTFAILURECOUNTER_BUFFER_SIZE 0U

/*------------------[Memory size configuration]-----------------------------*/

/* !LINKSTO dsn.Dem.ErrorQueueOpt,1 */
#if (defined DEM_BSW_ERROR_BUFFER_SIZE)
#error DEM_BSW_ERROR_BUFFER_SIZE already defined
#endif
/** \brief Maximal number of error-queue entries
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_BSW_ERROR_BUFFER_SIZE 10U

/* DEM_DTC_ORIGIN_PRIMARY_MEMORY - Event APPL_E_DDVFD_HVLowVoltage: aging counter value + DemExtendedDataClass_0 + 1 * DemFreezeFrameClass_0 = 11 */
/* DEM_DTC_ORIGIN_PRIMARY_MEMORY - Event APPL_E_DDVFD_HVHighVoltage: aging counter value + DemExtendedDataClass_0 + 1 * DemFreezeFrameClass_0 = 11 */
/* DEM_DTC_ORIGIN_PRIMARY_MEMORY - Event APPL_E_DDVFD_HiOVPPermanentFauSts: aging counter value + DemExtendedDataClass_0 + 1 * DemFreezeFrameClass_0 = 11 */
/* DEM_DTC_ORIGIN_PRIMARY_MEMORY - Event APPL_E_DDVFD_HiUVPPermanentFauSts: aging counter value + DemExtendedDataClass_0 + 1 * DemFreezeFrameClass_0 = 11 */

/* entry data sizes (IntVal + ED + Num * FF) of prm memory:  11 11 11 11 */
/* entry data sizes (IntVal + ED + Num * FF) of sec memory:  */
/* entry data sizes (IntVal + ED + Num * FF) of mir memory:  */

#if (defined DEM_SIZE_GATE_ENTRY_DATA_PRIMARY)
#error DEM_SIZE_GATE_ENTRY_DATA_PRIMARY already defined
#endif
/** \brief Gate entry size for primary memory
 **
 ** If immediate storage is enabled for any of the events in primary memory
 ** then this size is maximum of the highest primary event memory size
 ** considering IntVal, extended data and freeze frames.
 ** If maximum calculated size is 0, then default 1 is used.
 */
#define DEM_SIZE_GATE_ENTRY_DATA_PRIMARY   11U

#if (defined DEM_SIZE_GATE_ENTRY_DATA_SECONDARY)
#error DEM_SIZE_GATE_ENTRY_DATA_SECONDARY already defined
#endif
/** \brief Gate entry size for secondary memory
 **
 ** If immediate storage is enabled for any of the events in secondary memory
 ** then this size is maximum of the highest secondary event memory size
 ** considering IntVal, extended data and freeze frames.
 ** If maximum calculated size is 0, then default 1 is used.
 */
#define DEM_SIZE_GATE_ENTRY_DATA_SECONDARY 1U

#if (defined DEM_SIZE_GATE_ENTRY_DATA_MIRROR)
#error DEM_SIZE_GATE_ENTRY_DATA_MIRROR already defined
#endif
/** \brief Gate entry size for mirror memory
 **
 ** If immediate storage is enabled for any of the events in mirror memory
 ** then this size is maximum of the highest mirror event memory size
 ** considering IntVal, extended data and freeze frames.
 ** If maximum calculated size is 0, then default 1 is used.
 */
#define DEM_SIZE_GATE_ENTRY_DATA_MIRROR    1U

#if (defined DEM_SIZE_GATE_ENTRY_DATA_PERMANENT)
#error DEM_SIZE_GATE_ENTRY_DATA_PERMANENT already defined
#endif
/** \brief Gate entry size for permanent memory
 **
 ** As this event memory type is not supported this shall be default 1.
 */
#define DEM_SIZE_GATE_ENTRY_DATA_PERMANENT 1U

#if (defined DEM_USE_IMMEDIATE_NV_STORAGE)
#error DEM_USE_IMMEDIATE_NV_STORAGE already defined
#endif
/** \brief Switch, indicating if Immediate storage of event memory entries in
 ** NvM is activated for Dem
 **
 ** This can be the case if any DTC is configured to be stored immediately, or
 ** if ClearDTC behavior is configured to non-volatile triggered or finished.
 */
#define DEM_USE_IMMEDIATE_NV_STORAGE    STD_OFF

#if (defined DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES)
#error DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES already defined
#endif
/* !LINKSTO Dem.NvStorageEmptyEvMemEntries.Config,1 */
/** \brief Switch, indicating if empty event memory entries will be
 ** initialized in NVRAM
 **
 ** If the restoration of an event memory entry from NvM was not successful,
 ** this switch controls (esp. for ::DEM_USE_IMMEDIATE_NV_STORAGE = ON) if
 ** this entry is initialized with default values during next shutdown.
 */
#define DEM_NV_STORAGE_EMPTY_EVMEM_ENTRIES    STD_ON

#if (defined DEM_IMMEDIATE_CLEARED)
#error DEM_IMMEDIATE_CLEARED already defined
#endif
/** \brief Immediate storage configuration value: store CLEARED entries */
#define DEM_IMMEDIATE_CLEARED 0U

#if (defined DEM_IMMEDIATE_CHANGED)
#error DEM_IMMEDIATE_CHANGED already defined
#endif
/** \brief Immediate storage configuration value: store ALL entries */
#define DEM_IMMEDIATE_CHANGED 1U

#if (defined DEM_IMMEDIATE_NV_STORAGE_TYPE)
#error DEM_IMMEDIATE_NV_STORAGE_TYPE already defined
#endif
/** \brief Immediate storage configuration */
#define DEM_IMMEDIATE_NV_STORAGE_TYPE    DEM_IMMEDIATE_CLEARED

#if (defined DEM_IMMEDIATE_NV_STORAGE_LIMIT)
#error DEM_IMMEDIATE_NV_STORAGE_LIMIT already defined
#endif
/** \brief Immediate NvM storage limit
 **
 ** Defines the maximum number of occurrences, a specific event memory entry
 ** is allowed, to be stored in NVRAM immediately.
 ** Its value is set to 0 when the immediate storage limit feature is
 ** disabled by the user. In that case, there is no limit for the storage to
 ** NVRAM and whenever the entry gets updated, it can be stored immediately
 ** to NVRAM if immediate storage is enabled for it.
 **/
#define DEM_IMMEDIATE_NV_STORAGE_LIMIT     0U

#if (defined DEM_ZERO_END)
#error DEM_ZERO_END already defined
#endif
/** \brief Zero value to be added to each size, whose involved patterns could
 ** be none */
#define DEM_ZERO_END                  0U

#if (defined DEM_SIZE_ENTRY_DATA_PRIMARY)
#error DEM_SIZE_ENTRY_DATA_PRIMARY already defined
#endif
/** \brief Size of dynamic primary entry data
 **
 ** The N (primary memory entry number) maximal sizes are added.
 **
 ** \note The DEM_ZERO_END is not necessary here, because primary event memory
 **       is always > 0.
 **/
#define DEM_SIZE_ENTRY_DATA_PRIMARY   \
  (11U + 11U + 11U + 11U)

#if (defined DEM_SIZE_ENTRY_DATA_SECONDARY)
#error DEM_SIZE_ENTRY_DATA_SECONDARY already defined
#endif
/** \brief Size of dynamic secondary entry data
 **
 ** The N (secondary memory entry number) maximal sizes are added.
 **/
#define DEM_SIZE_ENTRY_DATA_SECONDARY \
  (DEM_ZERO_END)

#if (defined DEM_SIZE_ENTRY_DATA_MIRROR)
#error DEM_SIZE_ENTRY_DATA_MIRROR already defined
#endif
/** \brief Size of dynamic mirror entry data
 **
 ** The N (mirror memory entry number) maximal sizes are added.
 **/
#define DEM_SIZE_ENTRY_DATA_MIRROR    \
  (DEM_ZERO_END)

#if (defined DEM_SIZE_ENTRY_DATA_PERMANENT)
#error DEM_SIZE_ENTRY_DATA_PERMANENT already defined
#endif
/** \brief Size of dynamic permanent entry data
 **
 ** The N (permanent memory entry number) maximal sizes are added.
 **/
#define DEM_SIZE_ENTRY_DATA_PERMANENT DEM_ZERO_END

/*------------------[Events configuration]----------------------------------*/

#if (defined DEM_MAX_NUMBER_EVENT_ENTRY_PRI)
#error DEM_MAX_NUMBER_EVENT_ENTRY_PRI already defined
#endif
/** \brief Maximum number of events which can be stored in the primary memory
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_MAX_NUMBER_EVENT_ENTRY_PRI 4U

#if (defined DEM_MAX_NUMBER_EVENT_ENTRY_SEC)
#error DEM_MAX_NUMBER_EVENT_ENTRY_SEC already defined
#endif
/** \brief Maximum number of events which can be stored in the secondary
 ** memory
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_MAX_NUMBER_EVENT_ENTRY_SEC 0U

#if (defined DEM_MAX_NUMBER_EVENT_ENTRY_MIR)
#error DEM_MAX_NUMBER_EVENT_ENTRY_MIR already defined
#endif
/** \brief Maximum number of events which can be stored in the mirror memory
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_MAX_NUMBER_EVENT_ENTRY_MIR 0U

#if (defined DEM_MAX_NUMBER_EVENT_ENTRY_PER)
#error DEM_MAX_NUMBER_EVENT_ENTRY_PER already defined
#endif
/** \brief Maximum number of events which can be stored in the permanent memory
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_MAX_NUMBER_EVENT_ENTRY_PER 0U

#if (defined DEM_NUMBER_OF_EVENTS)
#error DEM_NUMBER_OF_EVENTS already defined
#endif
/** \brief Number of events which are present in the system
 **
 ** Calculated by number of event IDs listed in Dem_IntErrId.h and
 ** Dem_IntEvtId.h including ::DEM_EVENT_ID_INVALID.
 **
 ** \note Macro name is still existing for compatibility reasons with AR2.1.
 **/
#define DEM_NUMBER_OF_EVENTS 5U

#if (defined DEM_NUM_SWC_EVENTS)
#error DEM_NUM_SWC_EVENTS already defined
#endif
/** \brief Number of SW-C events present in the system
 **/
#define DEM_NUM_SWC_EVENTS 4U

/*------------------[DTC groups configuration]------------------------------*/

/* Symbolic names of configured DTC groups */

#if (defined DemConf_DemGroupOfDTC_DEM_DTC_GROUP_EMISSION_REL_DTCS)
#error DemConf_DemGroupOfDTC_DEM_DTC_GROUP_EMISSION_REL_DTCS already defined
#endif
/** \brief Export symbolic name value of DTC group OBD-relevant */
#define DemConf_DemGroupOfDTC_DEM_DTC_GROUP_EMISSION_REL_DTCS 0x000000U

#if (defined DEM_DTC_GROUP_EMISSION_REL_DTCS)
#error DEM_DTC_GROUP_EMISSION_REL_DTCS already defined
#endif
/** \brief Export PREDEFINED symbolic name value (without prefix) as per definition of ::Dem_DTCGroupType in SWS */
#define DEM_DTC_GROUP_EMISSION_REL_DTCS 0x000000U

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dem_DEM_DTC_GROUP_EMISSION_REL_DTCS)
#error Dem_DEM_DTC_GROUP_EMISSION_REL_DTCS already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define Dem_DEM_DTC_GROUP_EMISSION_REL_DTCS 0x000000U
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DemConf_DemGroupOfDTC_DEM_DTC_GROUP_POWERTRAIN_DTCS)
#error DemConf_DemGroupOfDTC_DEM_DTC_GROUP_POWERTRAIN_DTCS already defined
#endif
/** \brief Export symbolic name value of DTC group powertrain */
#define DemConf_DemGroupOfDTC_DEM_DTC_GROUP_POWERTRAIN_DTCS   0x000FFFU

#if (defined DEM_DTC_GROUP_POWERTRAIN_DTCS)
#error DEM_DTC_GROUP_POWERTRAIN_DTCS already defined
#endif
/** \brief Export PREDEFINED symbolic name value (without prefix) as per definition of ::Dem_DTCGroupType in SWS */
#define DEM_DTC_GROUP_POWERTRAIN_DTCS   0x000FFFU

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dem_DEM_DTC_GROUP_POWERTRAIN_DTCS)
#error Dem_DEM_DTC_GROUP_POWERTRAIN_DTCS already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define Dem_DEM_DTC_GROUP_POWERTRAIN_DTCS   0x000FFFU
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DemConf_DemGroupOfDTC_DEM_DTC_GROUP_CHASSIS_DTCS)
#error DemConf_DemGroupOfDTC_DEM_DTC_GROUP_CHASSIS_DTCS already defined
#endif
/** \brief Export symbolic name value of DTC group chassis */
#define DemConf_DemGroupOfDTC_DEM_DTC_GROUP_CHASSIS_DTCS      0x003FFFU

#if (defined DEM_DTC_GROUP_CHASSIS_DTCS)
#error DEM_DTC_GROUP_CHASSIS_DTCS already defined
#endif
/** \brief Export PREDEFINED symbolic name value (without prefix) as per definition of ::Dem_DTCGroupType in SWS */
#define DEM_DTC_GROUP_CHASSIS_DTCS      0x003FFFU

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dem_DEM_DTC_GROUP_CHASSIS_DTCS)
#error Dem_DEM_DTC_GROUP_CHASSIS_DTCS already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define Dem_DEM_DTC_GROUP_CHASSIS_DTCS      0x003FFFU
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DemConf_DemGroupOfDTC_DEM_DTC_GROUP_BODY_DTCS)
#error DemConf_DemGroupOfDTC_DEM_DTC_GROUP_BODY_DTCS already defined
#endif
/** \brief Export symbolic name value of DTC group body */
#define DemConf_DemGroupOfDTC_DEM_DTC_GROUP_BODY_DTCS         0x007FFFU

#if (defined DEM_DTC_GROUP_BODY_DTCS)
#error DEM_DTC_GROUP_BODY_DTCS already defined
#endif
/** \brief Export PREDEFINED symbolic name value (without prefix) as per definition of ::Dem_DTCGroupType in SWS */
#define DEM_DTC_GROUP_BODY_DTCS         0x007FFFU

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dem_DEM_DTC_GROUP_BODY_DTCS)
#error Dem_DEM_DTC_GROUP_BODY_DTCS already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define Dem_DEM_DTC_GROUP_BODY_DTCS         0x007FFFU
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DemConf_DemGroupOfDTC_DEM_DTC_GROUP_NETWORK_COM_DTCS)
#error DemConf_DemGroupOfDTC_DEM_DTC_GROUP_NETWORK_COM_DTCS already defined
#endif
/** \brief Export symbolic name value of DTC group network communication */
#define DemConf_DemGroupOfDTC_DEM_DTC_GROUP_NETWORK_COM_DTCS  0x00BFFFU

#if (defined DEM_DTC_GROUP_NETWORK_COM_DTCS)
#error DEM_DTC_GROUP_NETWORK_COM_DTCS already defined
#endif
/** \brief Export PREDEFINED symbolic name value (without prefix) as per definition of ::Dem_DTCGroupType in SWS */
#define DEM_DTC_GROUP_NETWORK_COM_DTCS  0x00BFFFU

#if (!defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dem_DEM_DTC_GROUP_NETWORK_COM_DTCS)
#error Dem_DEM_DTC_GROUP_NETWORK_COM_DTCS already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define Dem_DEM_DTC_GROUP_NETWORK_COM_DTCS  0x00BFFFU
#endif /* !defined DEM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/*------------------[Warning indicators configuration]----------------------*/

/* Symbolic names of configured warning indicator IDs */


#if (defined DEM_NUMBER_OF_INDICATORS)
#error DEM_NUMBER_OF_INDICATORS already defined
#endif
/** \brief Number of warning indicators which are present in the system
 **
 ** \note Macro name is conform to the vague definition in chapter 10 of SWS.
 **/
#define DEM_NUMBER_OF_INDICATORS 0U


#if (defined DEM_NUM_EVENT_INDICATOR_USED)
#error DEM_NUM_EVENT_INDICATOR_USED already defined
#endif
/** \brief Number of all events which are configured for warning indicator */
#define DEM_NUM_EVENT_INDICATOR_USED 0U


#if (defined DEM_NUM_BSWEVENT_INDICATOR_USED)
#error DEM_NUM_BSWEVENT_INDICATOR_USED already defined
#endif
/** \brief Number of BSW events which are configured for warning indicator */
#define DEM_NUM_BSWEVENT_INDICATOR_USED 0U

#if (defined DEM_NUM_INDICATOR_LINKS)
#error DEM_NUM_INDICATOR_LINKS already defined
#endif
/** \brief Number of warning indicator links */
#define DEM_NUM_INDICATOR_LINKS   0U

/*------------------[Enable conditions configuration]-----------------------*/

/* Symbolic names of configured enable conditions */


#if (defined DEM_NUM_ENABLECONDITIONS)
#error DEM_NUM_ENABLECONDITIONS already defined
#endif
/** \brief Number of enable conditions */
#define DEM_NUM_ENABLECONDITIONS 0U

/*------------------[Operation and aging cycles configuration]--------------*/

#ifndef DEM_PROCESS_OPCYC_STATE
/** \brief Operation cycle processing is triggered by START/END */
#define DEM_PROCESS_OPCYC_STATE        0x00U
#endif

#ifndef DEM_PROCESS_OPCYC_COUNTER
/** \brief Operation cycle processing is triggered by collecting an external
 ** counter value */
#define DEM_PROCESS_OPCYC_COUNTER      0x01U
#endif

#if (defined DEM_OPERATION_CYCLE_PROCESSING)
#error DEM_OPERATION_CYCLE_PROCESSING already defined
#endif
/** \brief Operation cycle processing mode
 **
 ** This processing mode defines whether the operation cycles are triggered by
 ** START/END reports via Dem_SetOperationCycleState(), or collecting an
 ** external counter value via Dem_SetOperationCycleCntValue().
 **
 ** \note Macro name is NOT present in SWS. This is as per bugzilla ticket
 ** #47189.
 **/
#define DEM_OPERATION_CYCLE_PROCESSING DEM_PROCESS_OPCYC_STATE

#ifndef DEM_PROCESS_AGINGCTR_INTERN
/** \brief Aging counter processing is triggered internally */
#define DEM_PROCESS_AGINGCTR_INTERN      0x00U
#endif

#ifndef DEM_PROCESS_AGINGCTR_EXTERN
/** \brief Aging counter processing is triggered by collecting an external
 ** counter value */
#define DEM_PROCESS_AGINGCTR_EXTERN      0x01U
#endif

#if (defined DEM_AGINGCYCLE_COUNTER_PROCESSING)
#error DEM_AGINGCYCLE_COUNTER_PROCESSING already defined
#endif
/** \brief Aging counter processing mode
 **
 ** This processing mode defines whether aging is triggered via
 ** Dem_SetOperationCycleState() and Dem_SetAgingCycleState(), or via an
 ** external counter value reported by Dem_SetAgingCycleCounterValue().
 **/
#define DEM_AGINGCYCLE_COUNTER_PROCESSING DEM_PROCESS_AGINGCTR_INTERN

#if (defined DEM_PROCESS_OCCCTR_CDTC)
#error DEM_PROCESS_OCCCTR_CDTC already defined
#endif
/** \brief Occurrence counter processing is triggered after the fault confirmation
 ** was successfull */
#define DEM_PROCESS_OCCCTR_CDTC    0x00U

#if (defined DEM_PROCESS_OCCCTR_TF)
#error DEM_PROCESS_OCCCTR_TF already defined
#endif
/** \brief Occurrence counter processing is triggered by the TestFailed bit only */
#define DEM_PROCESS_OCCCTR_TF      0x01U

#if (defined DEM_OCCURRENCE_COUNTER_PROCESSING)
#error DEM_OCCURRENCE_COUNTER_PROCESSING already defined
#endif
/** \brief Occurrence counter processing mode
 **
 ** This switch defines the consideration of the fault confirmation process for the
 ** occurrence counter.
 **/
#define DEM_OCCURRENCE_COUNTER_PROCESSING  DEM_PROCESS_OCCCTR_CDTC

/* Symbolic names of configured operation cycle types */

#if (defined DEM_OPCYC_POWER_TYPE)
#error DEM_OPCYC_POWER_TYPE already defined
#endif
/** \brief Symbolic name of configured operation cycle type DEM_OPCYC_POWER for DEM_OPCYC_POWER.
 ** Not used in the current implementation */
#define DEM_OPCYC_POWER_TYPE                 2U

/* Symbolic names of configured operation cycles and failure cycles */

#if (defined DEM_OPCYC_POWER)
#error DEM_OPCYC_POWER already defined
#endif
/** \brief Symbolic name of operation cycle DEM_OPCYC_POWER */
#define DEM_OPCYC_POWER                 0U

#if (defined DEM_NUM_OPCYCLES)
#error DEM_NUM_OPCYCLES already defined
#endif
/** \brief Number of operation cycles */
#define DEM_NUM_OPCYCLES 1U

/* Symbolic names of configured aging cycles */

#if (defined DEM_NUM_AGINGCYCLES)
#error DEM_NUM_AGINGCYCLES already defined
#endif
/** \brief Number of aging cycles
 **
 ** For these cycles, aging will not be performed based on the operation cycle
 ** of the respective event.
 **
 ** The value is always 0, if ::DEM_USE_AGING is switched off. */
#define DEM_NUM_AGINGCYCLES 0U

/*==================[type definitions]======================================*/

/*------------------[Dem_ConfigType]----------------------------------------*/

/** \brief This type of the external data structure shall contain the post
 **  build initialization data for the Dem.
 **
 ** \note Type is unused, as only pre-compile time support is implemented. */
typedef uint8 Dem_ConfigType;

/*==================[external function declarations]========================*/



/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Configuration structure */
extern CONST(Dem_ConfigType, DEM_CONST) DemConfigSet_0;

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( DEM_CFG_H ) */
/*==================[end of file]===========================================*/
