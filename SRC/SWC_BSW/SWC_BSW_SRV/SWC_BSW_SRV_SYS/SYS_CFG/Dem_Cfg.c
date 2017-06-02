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

/* This file contains all definitions of the configuration of the AUTOSAR
 * module Dem that are target independent. */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <TSAutosar.h>                    /* EB specific standard types */
#include <Std_Types.h>                    /* AUTOSAR standard types */
#include <Dem_Int.h>                      /* API and internal declarations,
                                           * dependent and static part */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

CONST(Dem_ConfigType, DEM_CONST) DemConfigSet_0 = {0U};

/*------------------[Freeze frame classes configuration]--------------------*/

/** \brief Indices of element on freeze frame data segment DID_ApmElecValU14 */
STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
  Dem_DataElementIdxDID_ApmElecValU14[1] =
{
  0U, /* ApmElecValU14 */
};

/** \brief Start-bytes of element on freeze frame data segment DID_ApmElecValU14 */
STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
  Dem_DataElementOffsetDID_ApmElecValU14[1] =
{
  0U, /* ApmElecValU14 */
};

/** \brief Indices of element on freeze frame data segment DID_ApmElecValI14 */
STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
  Dem_DataElementIdxDID_ApmElecValI14[1] =
{
  1U, /* ApmElecValI14 */
};

/** \brief Start-bytes of element on freeze frame data segment DID_ApmElecValI14 */
STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
  Dem_DataElementOffsetDID_ApmElecValI14[1] =
{
  0U, /* ApmElecValI14 */
};

/** \brief Indices of element on freeze frame data segment DID_ApmElecValUHV */
STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
  Dem_DataElementIdxDID_ApmElecValUHV[1] =
{
  2U, /* ApmElecValUHV */
};

/** \brief Start-bytes of element on freeze frame data segment DID_ApmElecValUHV */
STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
  Dem_DataElementOffsetDID_ApmElecValUHV[1] =
{
  0U, /* ApmElecValUHV */
};

/** \brief Indices of element on freeze frame data segment DID_ApmElecValIHV */
STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
  Dem_DataElementIdxDID_ApmElecValIHV[1] =
{
  3U, /* ApmElecValIHV */
};

/** \brief Start-bytes of element on freeze frame data segment DID_ApmElecValIHV */
STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
  Dem_DataElementOffsetDID_ApmElecValIHV[1] =
{
  0U, /* ApmElecValIHV */
};

/** \brief Indices of element on freeze frame data segment DID_ApmElecValTemp */
STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
  Dem_DataElementIdxDID_ApmElecValTemp[1] =
{
  4U, /* ApmElecValTemp */
};

/** \brief Start-bytes of element on freeze frame data segment DID_ApmElecValTemp */
STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
  Dem_DataElementOffsetDID_ApmElecValTemp[1] =
{
  0U, /* ApmElecValTemp */
};

/** \brief freeze frame segments (DIDs) */
CONST(Dem_FFSegmentType, DEM_CONST) Dem_FFSegment[DEM_NUM_FFSEGS] =
{
  /* DID_ApmElecValU14 */
  {
    1U,
    DEM_FFS_DID_DID_ApmElecValU14,
    Dem_DataElementIdxDID_ApmElecValU14,
    Dem_DataElementOffsetDID_ApmElecValU14
  },
  /* DID_ApmElecValI14 */
  {
    1U,
    DEM_FFS_DID_DID_ApmElecValI14,
    Dem_DataElementIdxDID_ApmElecValI14,
    Dem_DataElementOffsetDID_ApmElecValI14
  },
  /* DID_ApmElecValUHV */
  {
    1U,
    DEM_FFS_DID_DID_ApmElecValUHV,
    Dem_DataElementIdxDID_ApmElecValUHV,
    Dem_DataElementOffsetDID_ApmElecValUHV
  },
  /* DID_ApmElecValIHV */
  {
    1U,
    DEM_FFS_DID_DID_ApmElecValIHV,
    Dem_DataElementIdxDID_ApmElecValIHV,
    Dem_DataElementOffsetDID_ApmElecValIHV
  },
  /* DID_ApmElecValTemp */
  {
    1U,
    DEM_FFS_DID_DID_ApmElecValTemp,
    Dem_DataElementIdxDID_ApmElecValTemp,
    Dem_DataElementOffsetDID_ApmElecValTemp
  },
};

/*---[Freeze frame class DemFreezeFrameClass_0]---*/

/** \brief Indices of segments on freeze frame class DemFreezeFrameClass_0 to ::Dem_FFSegment[] */
STATIC CONST(Dem_FFSegIdxType, DEM_CONST) Dem_FFSegIdxDemFreezeFrameClass_0[5] =
{
  0U, /* DID_ApmElecValU14 */
  1U, /* DID_ApmElecValI14 */
  2U, /* DID_ApmElecValUHV */
  3U, /* DID_ApmElecValIHV */
  4U, /* DID_ApmElecValTemp */
};

/** \brief Start-bytes of segments on freeze frame class DemFreezeFrameClass_0 */
STATIC CONST(Dem_FFStartByteType, DEM_CONST)
  Dem_FFStartByteDemFreezeFrameClass_0[5] =
{
  0U, /* DID_ApmElecValU14 */
  2U, /* DID_ApmElecValI14 */
  4U, /* DID_ApmElecValUHV */
  6U, /* DID_ApmElecValIHV */
  8U, /* DID_ApmElecValTemp */
};

/** \brief Array containing all freeze frame classes */
CONST(Dem_FFClassType, DEM_CONST) Dem_FFClass[DEM_NUM_FFCLS] =
{
  {
    5U, /* number of segments */
    Dem_FFSegIdxDemFreezeFrameClass_0,
    Dem_FFStartByteDemFreezeFrameClass_0
  },
};

/*------------------[Freeze frame record number classes configuration]------*/

/*------------------[Extended data classes configuration]-------------------*/

/** \brief Indices of element on extended data segment EXTDATAREC_0 */
STATIC CONST(Dem_DataElementIdxType, DEM_CONST)
  Dem_DataElementIdxEXTDATAREC_0[2] =
{
  DEM_INT_VAL_IDX_AGECTR,
  DEM_INT_VAL_IDX_OCCCTR,
};

/** \brief Start-bytes of element on extended data segment EXTDATAREC_0 */
STATIC CONST(Dem_DataElementOffsetType, DEM_CONST)
  Dem_DataElementOffsetEXTDATAREC_0[2] =
{
  0U, /* DEM_AGINGCTR */
  0U, /* DEM_OCCCTR */
};

/** \brief Extended data segments (Records) */
CONST(Dem_EDSegmentType, DEM_CONST) Dem_EDSegment[DEM_NUM_EDSEGS] =
{
  /* EXTDATAREC_0 */
  {
    2U,
    DEM_EDS_NUM_EXTDATAREC_0,
    TRUE,
    Dem_DataElementIdxEXTDATAREC_0,
    Dem_DataElementOffsetEXTDATAREC_0
  },
};

/*---[Extended data class DemExtendedDataClass_0]---*/

/** \brief Indices of segments on extended data class DemExtendedDataClass_0 to ::Dem_EDSegment[] */
STATIC CONST(Dem_EDSegIdxType, DEM_CONST) Dem_EDSegIdxDemExtendedDataClass_0[1] =
{
  0U, /* EXTDATAREC_0 */
};

/** \brief Start-bytes of segments on extended data class DemExtendedDataClass_0 */
STATIC CONST(Dem_EDStartByteType, DEM_CONST)
  Dem_EDStartByteDemExtendedDataClass_0[1] =
{
  0U, /* EXTDATAREC_0 */
};

/** \brief Array containing all extended data classes */
CONST(Dem_EDClassType, DEM_CONST) Dem_EDClass[DEM_NUM_EDCLS] =
{
  {
    1U, /* number of segments */
    Dem_EDSegIdxDemExtendedDataClass_0,
    Dem_EDStartByteDemExtendedDataClass_0
  },
};

/*------------------[Data element classes configuration]--------------------*/

/** \brief Array containing all data elements */
CONST(Dem_DataElementType, DEM_CONST) Dem_DataElement[DEM_NUM_EXT_CS_DATAELEMENTS] =
{
  /* ApmElecValU14 */
  {
    2U,
    &MAIN_DemDidElementReadApmElecValU14
  },
  /* ApmElecValI14 */
  {
    2U,
    &MAIN_DemDidElementReadApmElecValI14
  },
  /* ApmElecValUHV */
  {
    2U,
    &MAIN_DemDidElementReadApmElecValUHV
  },
  /* ApmElecValIHV */
  {
    2U,
    &MAIN_DemDidElementReadApmElecValIHV
  },
  /* ApmElecValTemp */
  {
    2U,
    &MAIN_DemDidElementReadApmElecValTemp
  },
};

/*------------------[DTC groups configuration]------------------------------*/

/** \brief Array containing the DTC group values */
CONST(Dem_DTCGroupType, DEM_CONST) Dem_DTCGroups[DEM_NUM_DTC_GROUPS] =
{
    DemConf_DemGroupOfDTC_DEM_DTC_GROUP_EMISSION_REL_DTCS,
  DemConf_DemGroupOfDTC_DEM_DTC_GROUP_POWERTRAIN_DTCS,
  DemConf_DemGroupOfDTC_DEM_DTC_GROUP_CHASSIS_DTCS,
  DemConf_DemGroupOfDTC_DEM_DTC_GROUP_BODY_DTCS,
  DemConf_DemGroupOfDTC_DEM_DTC_GROUP_NETWORK_COM_DTCS,
};

/*------------------[Events configuration]----------------------------------*/

/** \brief Event configuration description table (uses 'bit packing scheme) */
CONST(Dem_EventDescType, DEM_CONST) Dem_EventDesc[DEM_NUMBER_OF_EVENTS] =
{
  { 0U, 0U, 0U },                                 /* invalid event id entry */
  { /* event: APPL_E_DDVFD_HVLowVoltage */
    0x001800U                                                  /* DTC value */
    | ( (uint32)(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U) << DEM_DTCORIGIN_OFFSET )
                                                           /* Origin of DTC */
    | ( (uint32)DEM_DTCGRP_IDX_POWERTRAIN_DTCS << DEM_DTCGROUP_OFFSET )
                                                            /* Group of DTC */
    | ( (uint32)0U << DEM_IMMEDIATESTORAGE_OFFSET )
                                              /* Immediate storage disabled */
    ,
    0U                                     /* No severity specified for DTC */
    | ( (uint32)0U << DEM_ENABLEPRESTORAGE_OFFSET )  /* Prestorage disabled */
    | ( (uint32)DEM_FFCLS_IDX_DemFreezeFrameClass_0 << DEM_FFCLASSIDX_OFFSET )
                                                      /* Freeze frame class */
    | ( (uint32)1U << DEM_FFRECINFO_OFFSET )
                                         /* Maximal number of freeze frames */
    | ( (uint32)DEM_EDCLS_IDX_DemExtendedDataClass_0 << DEM_EDCLASSIDX_OFFSET )
                                                     /* Extended data class */
    | ( (uint32)DEM_OPCYC_POWER << DEM_OPCYCLEIDX_OFFSET )
                                                      /* Operation cycle Id */
    | ( (uint32)40U << DEM_AGINGCYCLES_OFFSET )
                                               /* Limit of DTC aging cycles */
    | ( (uint32)DEM_EVENT_KIND_SWC << DEM_EVENTKIND_OFFSET )
                                                       /* Event kind is SWC */
    | ( (uint32)0U << DEM_EVENTFAILURECLASSIDX_OFFSET )
                                    /* Index of failure class configuration */
    ,
    0U     /* No enable conditions (refer to 'Number of enable conditions') */
    | ( (uint32)0U << DEM_NUMENCOND_OFFSET )
                                             /* Number of enable conditions */
    | ( (uint32)0U << DEM_INDICATORUSED_OFFSET )
                                               /* No warning indicator used */
    | ( (uint32)0U << DEM_PRIORITY_OFFSET )
                            /* Internal event priority (0 = most important) */
    | ( (uint32)DEM_DEBOUNCE_COUNTERBASED << DEM_DEBOUNCEALGO_OFFSET )
                                          /* Counter based event debouncing */
    | ( (uint32)0U << DEM_DEBOUNCEIDX_OFFSET )
                                /* Index of debouncing configuration/status */
    | ( (uint32)0U << DEM_DTCFUNCTIONALUNIT_OFFSET )
                                                     /* DTC Functional Unit */
    | ( (uint32)DEM_NUM_AGINGCYCLES << DEM_AGINGCYCLEIDX_OFFSET )
                                                       /* No aging cycle Id */
  },
  { /* event: APPL_E_DDVFD_HVHighVoltage */
    0x001801U                                                  /* DTC value */
    | ( (uint32)(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U) << DEM_DTCORIGIN_OFFSET )
                                                           /* Origin of DTC */
    | ( (uint32)DEM_DTCGRP_IDX_POWERTRAIN_DTCS << DEM_DTCGROUP_OFFSET )
                                                            /* Group of DTC */
    | ( (uint32)0U << DEM_IMMEDIATESTORAGE_OFFSET )
                                              /* Immediate storage disabled */
    ,
    0U                                     /* No severity specified for DTC */
    | ( (uint32)0U << DEM_ENABLEPRESTORAGE_OFFSET )  /* Prestorage disabled */
    | ( (uint32)DEM_FFCLS_IDX_DemFreezeFrameClass_0 << DEM_FFCLASSIDX_OFFSET )
                                                      /* Freeze frame class */
    | ( (uint32)1U << DEM_FFRECINFO_OFFSET )
                                         /* Maximal number of freeze frames */
    | ( (uint32)DEM_EDCLS_IDX_DemExtendedDataClass_0 << DEM_EDCLASSIDX_OFFSET )
                                                     /* Extended data class */
    | ( (uint32)DEM_OPCYC_POWER << DEM_OPCYCLEIDX_OFFSET )
                                                      /* Operation cycle Id */
    | ( (uint32)40U << DEM_AGINGCYCLES_OFFSET )
                                               /* Limit of DTC aging cycles */
    | ( (uint32)DEM_EVENT_KIND_SWC << DEM_EVENTKIND_OFFSET )
                                                       /* Event kind is SWC */
    | ( (uint32)0U << DEM_EVENTFAILURECLASSIDX_OFFSET )
                                    /* Index of failure class configuration */
    ,
    0U     /* No enable conditions (refer to 'Number of enable conditions') */
    | ( (uint32)0U << DEM_NUMENCOND_OFFSET )
                                             /* Number of enable conditions */
    | ( (uint32)0U << DEM_INDICATORUSED_OFFSET )
                                               /* No warning indicator used */
    | ( (uint32)0U << DEM_PRIORITY_OFFSET )
                            /* Internal event priority (0 = most important) */
    | ( (uint32)DEM_DEBOUNCE_COUNTERBASED << DEM_DEBOUNCEALGO_OFFSET )
                                          /* Counter based event debouncing */
    | ( (uint32)1U << DEM_DEBOUNCEIDX_OFFSET )
                                /* Index of debouncing configuration/status */
    | ( (uint32)0U << DEM_DTCFUNCTIONALUNIT_OFFSET )
                                                     /* DTC Functional Unit */
    | ( (uint32)DEM_NUM_AGINGCYCLES << DEM_AGINGCYCLEIDX_OFFSET )
                                                       /* No aging cycle Id */
  },
  { /* event: APPL_E_DDVFD_HiOVPPermanentFauSts */
    0x001802U                                                  /* DTC value */
    | ( (uint32)(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U) << DEM_DTCORIGIN_OFFSET )
                                                           /* Origin of DTC */
    | ( (uint32)DEM_DTCGRP_IDX_POWERTRAIN_DTCS << DEM_DTCGROUP_OFFSET )
                                                            /* Group of DTC */
    | ( (uint32)0U << DEM_IMMEDIATESTORAGE_OFFSET )
                                              /* Immediate storage disabled */
    ,
    0U                                     /* No severity specified for DTC */
    | ( (uint32)0U << DEM_ENABLEPRESTORAGE_OFFSET )  /* Prestorage disabled */
    | ( (uint32)DEM_FFCLS_IDX_DemFreezeFrameClass_0 << DEM_FFCLASSIDX_OFFSET )
                                                      /* Freeze frame class */
    | ( (uint32)1U << DEM_FFRECINFO_OFFSET )
                                         /* Maximal number of freeze frames */
    | ( (uint32)DEM_EDCLS_IDX_DemExtendedDataClass_0 << DEM_EDCLASSIDX_OFFSET )
                                                     /* Extended data class */
    | ( (uint32)DEM_OPCYC_POWER << DEM_OPCYCLEIDX_OFFSET )
                                                      /* Operation cycle Id */
    | ( (uint32)40U << DEM_AGINGCYCLES_OFFSET )
                                               /* Limit of DTC aging cycles */
    | ( (uint32)DEM_EVENT_KIND_SWC << DEM_EVENTKIND_OFFSET )
                                                       /* Event kind is SWC */
    | ( (uint32)0U << DEM_EVENTFAILURECLASSIDX_OFFSET )
                                    /* Index of failure class configuration */
    ,
    0U     /* No enable conditions (refer to 'Number of enable conditions') */
    | ( (uint32)0U << DEM_NUMENCOND_OFFSET )
                                             /* Number of enable conditions */
    | ( (uint32)0U << DEM_INDICATORUSED_OFFSET )
                                               /* No warning indicator used */
    | ( (uint32)0U << DEM_PRIORITY_OFFSET )
                            /* Internal event priority (0 = most important) */
    | ( (uint32)DEM_DEBOUNCE_COUNTERBASED << DEM_DEBOUNCEALGO_OFFSET )
                                          /* Counter based event debouncing */
    | ( (uint32)2U << DEM_DEBOUNCEIDX_OFFSET )
                                /* Index of debouncing configuration/status */
    | ( (uint32)0U << DEM_DTCFUNCTIONALUNIT_OFFSET )
                                                     /* DTC Functional Unit */
    | ( (uint32)DEM_NUM_AGINGCYCLES << DEM_AGINGCYCLEIDX_OFFSET )
                                                       /* No aging cycle Id */
  },
  { /* event: APPL_E_DDVFD_HiUVPPermanentFauSts */
    0x001803U                                                  /* DTC value */
    | ( (uint32)(DEM_DTC_ORIGIN_PRIMARY_MEMORY - 1U) << DEM_DTCORIGIN_OFFSET )
                                                           /* Origin of DTC */
    | ( (uint32)DEM_DTCGRP_IDX_POWERTRAIN_DTCS << DEM_DTCGROUP_OFFSET )
                                                            /* Group of DTC */
    | ( (uint32)0U << DEM_IMMEDIATESTORAGE_OFFSET )
                                              /* Immediate storage disabled */
    ,
    0U                                     /* No severity specified for DTC */
    | ( (uint32)0U << DEM_ENABLEPRESTORAGE_OFFSET )  /* Prestorage disabled */
    | ( (uint32)DEM_FFCLS_IDX_DemFreezeFrameClass_0 << DEM_FFCLASSIDX_OFFSET )
                                                      /* Freeze frame class */
    | ( (uint32)1U << DEM_FFRECINFO_OFFSET )
                                         /* Maximal number of freeze frames */
    | ( (uint32)DEM_EDCLS_IDX_DemExtendedDataClass_0 << DEM_EDCLASSIDX_OFFSET )
                                                     /* Extended data class */
    | ( (uint32)DEM_OPCYC_POWER << DEM_OPCYCLEIDX_OFFSET )
                                                      /* Operation cycle Id */
    | ( (uint32)40U << DEM_AGINGCYCLES_OFFSET )
                                               /* Limit of DTC aging cycles */
    | ( (uint32)DEM_EVENT_KIND_SWC << DEM_EVENTKIND_OFFSET )
                                                       /* Event kind is SWC */
    | ( (uint32)0U << DEM_EVENTFAILURECLASSIDX_OFFSET )
                                    /* Index of failure class configuration */
    ,
    0U     /* No enable conditions (refer to 'Number of enable conditions') */
    | ( (uint32)0U << DEM_NUMENCOND_OFFSET )
                                             /* Number of enable conditions */
    | ( (uint32)0U << DEM_INDICATORUSED_OFFSET )
                                               /* No warning indicator used */
    | ( (uint32)0U << DEM_PRIORITY_OFFSET )
                            /* Internal event priority (0 = most important) */
    | ( (uint32)DEM_DEBOUNCE_COUNTERBASED << DEM_DEBOUNCEALGO_OFFSET )
                                          /* Counter based event debouncing */
    | ( (uint32)3U << DEM_DEBOUNCEIDX_OFFSET )
                                /* Index of debouncing configuration/status */
    | ( (uint32)0U << DEM_DTCFUNCTIONALUNIT_OFFSET )
                                                     /* DTC Functional Unit */
    | ( (uint32)DEM_NUM_AGINGCYCLES << DEM_AGINGCYCLEIDX_OFFSET )
                                                       /* No aging cycle Id */
  },
};

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*------------------[Enable conditions configuration]-----------------------*/

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>


#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>


/*------------------[Warning indicators configuration]----------------------*/







/*------------------[Debouncing configuration]------------------------------*/


/** \brief Counter based debouncing configuration description table */
CONST(Dem_DebounceCounterCfgType, DEM_CONST)
  Dem_DebounceCounterCfg[DEM_NUM_DEBOUNCE_COUNTER] =
{
  { /* event: APPL_E_DDVFD_HVLowVoltage */
    255U,
    255U,
    -1,
    10,
    0,
    0,
    FALSE,
    FALSE,
  },
  { /* event: APPL_E_DDVFD_HVHighVoltage */
    255U,
    255U,
    -1,
    10,
    0,
    0,
    FALSE,
    FALSE,
  },
  { /* event: APPL_E_DDVFD_HiOVPPermanentFauSts */
    255U,
    255U,
    -1,
    10,
    0,
    0,
    FALSE,
    FALSE,
  },
  { /* event: APPL_E_DDVFD_HiUVPPermanentFauSts */
    255U,
    255U,
    -1,
    10,
    0,
    0,
    FALSE,
    FALSE,
  },
};

/** \brief Time based debouncing configuration description table */
/* none */

/** \brief Frequency based debouncing configuration description table */
/* none */

/*------------------[Fault confirmation configuration]----------------------*/

/** \brief Failure cycle and failure counter threshold configuration */
CONST(Dem_EventFailureCycleCfgType, DEM_CONST)
  Dem_EventFailureCycleCfg[DEM_NUM_FAILURECYCLES] =
{
  {
    DEM_OPCYC_POWER,
    1U
  },
};

/*------------------[RTE / C-callback notifications]------------------------*/

/** \brief Event callback property table */
CONST(Dem_CbPropertyType, DEM_CONST) Dem_CbProperty[DEM_NUMBER_OF_EVENTS] =
{
  0U,                                             /* invalid event id entry */
  /* event: APPL_E_DDVFD_HVLowVoltage */
    /* no init monitor callback */ /* no trigger on event status callback(s) */ /* no trigger on event data changed callback */ /* no clearEventAllowed callback */ /* DEM-internal fault detection counter */ DEM_ZERO_END,
  /* event: APPL_E_DDVFD_HVHighVoltage */
    /* no init monitor callback */ /* no trigger on event status callback(s) */ /* no trigger on event data changed callback */ /* no clearEventAllowed callback */ /* DEM-internal fault detection counter */ DEM_ZERO_END,
  /* event: APPL_E_DDVFD_HiOVPPermanentFauSts */
    /* no init monitor callback */ /* no trigger on event status callback(s) */ /* no trigger on event data changed callback */ /* no clearEventAllowed callback */ /* DEM-internal fault detection counter */ DEM_ZERO_END,
  /* event: APPL_E_DDVFD_HiUVPPermanentFauSts */
    /* no init monitor callback */ /* no trigger on event status callback(s) */ /* no trigger on event data changed callback */ /* no clearEventAllowed callback */ /* DEM-internal fault detection counter */ DEM_ZERO_END,
};

/*---[INIT_MONITOR]---*/

#if (DEM_CB_TABLE_INIT_MONITOR_SIZE != 0U)
/** \brief Generic callback function pointer table for InitMonitor */
CONST(Dem_CbFuncPtrInitMonitorType, DEM_CONST)
  Dem_CbFuncPtrInitMonitor[DEM_CB_TABLE_INIT_MONITOR_SIZE] =
{
};
#endif

#if (DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE != 0U)
/** \brief Generic lookup table for InitMonitor */
CONST(Dem_EventIdType, DEM_CONST)
  Dem_CbLookupTableInitMonitor[DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE] =
{
};
#endif

/*---[TRIGGER_ON_EVENT_STATUS]---*/

#if (DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE != 0U)
/** \brief C-Callback function pointer table for TriggerOnEventStatus */
CONST(Dem_CbFuncPtrTrigOnEvStType, DEM_CONST)
  Dem_CbFuncPtrTrigOnEvSt[DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE] =
{
};
#endif

#if (DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE != 0U)
/** \brief C-Lookup table for TriggerOnEventStatus */
CONST(Dem_CbLookupTableType, DEM_CONST)
  Dem_CbLookupTableTrigOnEvSt[DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE] =
{
};
#endif

#if (DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE != 0U)
/** \brief RTE-Callback function pointer table for TriggerOnEventStatus */
CONST(Dem_RteFuncPtrTrigOnEvStType, DEM_CONST)
  Dem_RteFuncPtrTrigOnEvSt[DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE] =
{
};
#endif

#if (DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE != 0U)
/** \brief RTE-Lookup table for TriggerOnEventStatus */
CONST(Dem_EventIdType, DEM_CONST)
  Dem_RteLookupTableTrigOnEvSt[DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE] =
{
};
#endif

/*---[TRIGGER_ON_DTC_STATUS]---*/

#if (DEM_CB_TABLE_TRIG_ON_DTCST_SIZE != 0U)
/** \brief Generic callback function pointer table for TriggerOnDTCStatus */
CONST(Dem_CbFuncPtrTrigOnDTCStType, DEM_CONST)
  Dem_CbFuncPtrTrigOnDTCSt[DEM_CB_TABLE_TRIG_ON_DTCST_SIZE] =
{
};
#endif

/*---[TRIGGER_ON_EVENT_DATA_CHANGED]---*/

#if (DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
/** \brief C-Callback function pointer table for TriggerOnEventDataChanged */
CONST(Dem_CbFuncPtrTrigOnEvDatType, DEM_CONST)
  Dem_CbFuncPtrTrigOnEvDat[DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE] =
{
};
#endif

#if (DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
/** \brief C-Lookup table for TriggerOnEventDataChanged */
CONST(Dem_CbLookupTableType, DEM_CONST)
  Dem_CbLookupTableTrigOnEvDat[DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE] =
{
};
#endif

#if (DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
/** \brief RTE-Callback function pointer table for TriggerOnEventDataChanged */
CONST(Dem_RteFuncPtrTrigOnEvDatType, DEM_CONST)
  Dem_RteFuncPtrTrigOnEvDat[DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE] =
{
};
#endif

#if (DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE != 0U)
/** \brief RTE-Lookup table for TriggerOnEventDataChanged */
CONST(Dem_EventIdType, DEM_CONST)
  Dem_RteLookupTableTrigOnEvDat[DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE] =
{
};
#endif

/*---[CLEAR_EVENT_ALLOWED]---*/

#if (DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
/** \brief C-Callback function pointer table for ClearEventAllowed */
CONST(Dem_CbFuncPtrClearEventAllowedType, DEM_CONST)
  Dem_CbFuncPtrClearEventAllowed[DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
{
};
#endif

#if (DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
/** \brief C-Lookup table for ClearEventAllowed */
CONST(Dem_CbLookupTableType, DEM_CONST)
  Dem_CbLookupTableClearEventAllowed[DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
{
};
#endif

#if (DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
/** \brief RTE-Callback function pointer table for ClearEventAllowed */
CONST(Dem_CbFuncPtrClearEventAllowedType, DEM_CONST)
  Dem_RteFuncPtrClearEventAllowed[DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
{
};
#endif

#if (DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE != 0U)
/** \brief RTE-Lookup table for ClearEventAllowed */
CONST(Dem_EventIdType, DEM_CONST)
  Dem_RteLookupTableClearEventAllowed[DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE] =
{
};
#endif

/*---[GET_FDC]---*/

#if (DEM_CB_TABLE_GET_FDC_SIZE != 0U)
/** \brief Generic callback function pointer table for GetFaultDetectionCounter */
CONST(Dem_CbFuncPtrGetFDCType, DEM_CONST)
  Dem_CbFuncPtrGetFDC[DEM_CB_TABLE_GET_FDC_SIZE] =
{
};
#endif

#if (DEM_LOOKUP_TABLE_GET_FDC_SIZE != 0U)
/** \brief Generic lookup table for GetFaultDetectionCounter */
CONST(Dem_EventIdType, DEM_CONST)
  Dem_CbLookupTableGetFDC[DEM_LOOKUP_TABLE_GET_FDC_SIZE] =
{
};
#endif

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
