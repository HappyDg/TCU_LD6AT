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
#if (!defined DEM_INT_CFG_H)
#define DEM_INT_CFG_H

/* This file contains the all module internal configuration declarations for
 * the AUTOSAR module Dem that are target independent. */


/*==================[includes]==============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

/*------------------[callback header file inclusions]-----------------------*/

#include <MAIN_DemCbk.h>

/*==================[macros]================================================*/

/*------------------[General]-----------------------------------------------*/

#if (defined DEM_USE_AGING)
#error DEM_USE_AGING already defined
#endif
/** \brief Macro for Enabling/Disabling aging functionality */
#define DEM_USE_AGING   STD_ON

#if (defined DEM_USE_INT_VAL_AREA)
#error DEM_USE_INT_VAL_AREA already defined
#endif
/** \brief Macro for Enabling/Disabling internal value area
 **
 ** In the current implementation the existance of the internal value area
 ** depends on aging only. */
#define DEM_USE_INT_VAL_AREA   DEM_USE_AGING

#if (defined DEM_USE_MAPPED_INT_DATA_ELEMENTS)
#error DEM_USE_MAPPED_INT_DATA_ELEMENTS already defined
#endif
/** \brief Macro for Enabling/Disabling internal data elements mapping */
#define DEM_USE_MAPPED_INT_DATA_ELEMENTS    STD_ON




/*------------------[Defensive programming]---------------------------------*/

#if (defined DEM_DEFENSIVE_PROGRAMMING_ENABLED)
#error DEM_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define DEM_DEFENSIVE_PROGRAMMING_ENABLED   STD_OFF
#if (defined DEM_PRECONDITION_ASSERT_ENABLED)
#error DEM_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define DEM_PRECONDITION_ASSERT_ENABLED     STD_OFF
#if (defined DEM_POSTCONDITION_ASSERT_ENABLED)
#error DEM_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define DEM_POSTCONDITION_ASSERT_ENABLED    STD_OFF
#if (defined DEM_UNREACHABLE_CODE_ASSERT_ENABLED)
#error DEM_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define DEM_UNREACHABLE_CODE_ASSERT_ENABLED STD_OFF
#if (defined DEM_INVARIANT_ASSERT_ENABLED)
#error DEM_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define DEM_INVARIANT_ASSERT_ENABLED        STD_OFF
#if (defined DEM_STATIC_ASSERT_ENABLED)
#error DEM_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define DEM_STATIC_ASSERT_ENABLED           STD_OFF


/*------------------[Callback macros]---------------------------------------*/

#if (defined DEM_CB_TABLE_INIT_MONITOR_SIZE)
#error DEM_CB_TABLE_INIT_MONITOR_SIZE already defined
#endif
/** \brief Size of the generic callback function pointer table for InitMonitor */
#define DEM_CB_TABLE_INIT_MONITOR_SIZE 0U

#if (defined DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE)
#error DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE already defined
#endif
/** \brief Size of the generic lookup table for InitMonitor */
#define DEM_LOOKUP_TABLE_INIT_MONITOR_SIZE 0U

#if (defined DEM_USE_CB_INIT_MONITOR)
#error DEM_USE_CB_INIT_MONITOR already defined
#endif
/** \brief Macro for Enabling/Disabling init monitor callback functionality */
#if (DEM_CB_TABLE_INIT_MONITOR_SIZE > 0U)
#define DEM_USE_CB_INIT_MONITOR STD_ON
#else
#define DEM_USE_CB_INIT_MONITOR STD_OFF
#endif


#if (defined DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE)
#error DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE already defined
#endif
/** \brief Size of the C-callback function pointer table for TriggerOnEventStatus */
#define DEM_C_CALLBACK_TABLE_TRIG_ON_EVST_SIZE 0U

#if (defined DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE)
#error DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE already defined
#endif
/** \brief Size of the RTE-callback function pointer table for TriggerOnEventStatus */
#define DEM_RTE_CALLBACK_TABLE_TRIG_ON_EVST_SIZE 0U

#if (defined DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE)
#error DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE already defined
#endif
/** \brief Size of the C-lookup table for TriggerOnEventStatus */
#define DEM_C_LOOKUP_TABLE_TRIG_ON_EVST_SIZE 0U

#if (defined DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE)
#error DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE already defined
#endif
/** \brief Size of the RTE-lookup table for TriggerOnEventStatus */
#define DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVST_SIZE 0U

#if (defined DEM_USE_CB_TRIG_ON_EVST)
#error DEM_USE_CB_TRIG_ON_EVST already defined
#endif
/** \brief Macro for Enabling/Disabling trigger on event status callback
 ** functionality */

#define DEM_USE_CB_TRIG_ON_EVST STD_OFF


#if (defined DEM_CB_TABLE_TRIG_ON_DTCST_SIZE)
#error DEM_CB_TABLE_TRIG_ON_DTCST_SIZE already defined
#endif
/** \brief Size of the C-callback function pointer table for TriggerOnDTCEventStatus */
#define DEM_CB_TABLE_TRIG_ON_DTCST_SIZE 0U

#if (defined DEM_USE_CB_TRIG_ON_DTCST)
#error DEM_USE_CB_TRIG_ON_EVST already defined
#endif
/** \brief Macro for Enabling/Disabling trigger on DTC event status callback
 ** functionality */

#define DEM_USE_CB_TRIG_ON_DTCST STD_OFF


#if (defined DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE )
#error DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE  already defined
#endif
/** \brief Size of the C-callback function pointer table for TriggerOnEventDataChanged */
#define DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE  0U

#if (defined DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE)
#error DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE already defined
#endif
/** \brief Size of the RTE-callback function pointer table for TriggerOnEventDataChanged */
#define DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE 0U

#if (defined DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE)
#error DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE already defined
#endif
/** \brief Size of the C-lookup table for TriggerOnEventDataChanged */
#define DEM_C_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE 0U

#if (defined DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE)
#error DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE already defined
#endif
/** \brief Size of the RTE-lookup table for TriggerOnEventDataChanged */
#define DEM_RTE_LOOKUP_TABLE_TRIG_ON_EVDAT_SIZE 0U

#if (defined DEM_USE_CB_TRIG_ON_EVDAT)
#error DEM_USE_CB_TRIG_ON_EVDAT already defined
#endif
/** \brief Macro for Enabling/Disabling trigger on event data changed callback functionality */
#if ( (DEM_RTE_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U) || \
      (DEM_C_CB_TABLE_TRIG_ON_EVDAT_SIZE > 0U) )
#define DEM_USE_CB_TRIG_ON_EVDAT STD_ON
#else
#define DEM_USE_CB_TRIG_ON_EVDAT STD_OFF
#endif


#if (defined DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE )
#error DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE  already defined
#endif
/** \brief Size of the C-callback function pointer table for ClearEventAllowed */
#define DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE  0U

#if (defined DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE)
#error DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE already defined
#endif
/** \brief Size of the RTE-callback function pointer table for ClearEventAllowed */
#define DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE 0U

#if (defined DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE)
#error DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE already defined
#endif
/** \brief Size of the C-lookup table for ClearEventAllowed */
#define DEM_C_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE 0U

#if (defined DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE)
#error DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE already defined
#endif
/** \brief Size of the RTE-lookup table for ClearEventAllowed */
#define DEM_RTE_LOOKUP_TABLE_CLEAR_EVENT_ALLOWED_SIZE 0U

#if (defined DEM_USE_CB_CLEAR_EVENT_ALLOWED)
#error DEM_USE_CB_CLEAR_EVENT_ALLOWED already defined
#endif
/** \brief Macro for Enabling/Disabling ClearEventAllowed callback functionality */
#if ( (DEM_RTE_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE > 0U) || \
      (DEM_C_CB_TABLE_CLEAR_EVENT_ALLOWED_SIZE > 0U) )
#define DEM_USE_CB_CLEAR_EVENT_ALLOWED STD_ON
#else
#define DEM_USE_CB_CLEAR_EVENT_ALLOWED STD_OFF
#endif


#if (defined DEM_CB_TABLE_GET_FDC_SIZE)
#error DEM_CB_TABLE_GET_FDC_SIZE already defined
#endif
/** \brief Size of the generic callback function pointer table for GetFaultDetectionCounter */
#define DEM_CB_TABLE_GET_FDC_SIZE 0U

#if (defined DEM_LOOKUP_TABLE_GET_FDC_SIZE)
#error DEM_LOOKUP_TABLE_GET_FDC_SIZE already defined
#endif
/** \brief Size of the generic lookup table for GetFaultDetectionCounter */
#define DEM_LOOKUP_TABLE_GET_FDC_SIZE 0U

#if (defined DEM_USE_CB_GET_FDC)
#error DEM_USE_CB_GET_FDC already defined
#endif
/** \brief Macro for Enabling/Disabling fault detection counter callback
 ** functionality */
#if (DEM_CB_TABLE_GET_FDC_SIZE > 0U)
#define DEM_USE_CB_GET_FDC STD_ON
#else
#define DEM_USE_CB_GET_FDC STD_OFF
#endif

/*------------------[DTC groups configuration]------------------------------*/

/* Symbolic names of internal DTC group indices */

#if (defined DEM_DTCGRP_IDX_EMISSION_REL_DTCS)
#error DEM_DTCGRP_IDX_EMISSION_REL_DTCS already defined
#endif
/** \brief Symbolic name of DTC group EMISSION_REL_DTCS index */
#define DEM_DTCGRP_IDX_EMISSION_REL_DTCS               0U

#if (defined DEM_DTCGRP_IDX_POWERTRAIN_DTCS)
#error DEM_DTCGRP_IDX_POWERTRAIN_DTCS already defined
#endif
/** \brief Symbolic name of DTC group POWERTRAIN_DTCS index */
#define DEM_DTCGRP_IDX_POWERTRAIN_DTCS                 1U

#if (defined DEM_DTCGRP_IDX_CHASSIS_DTCS)
#error DEM_DTCGRP_IDX_CHASSIS_DTCS already defined
#endif
/** \brief Symbolic name of DTC group CHASSIS_DTCS index */
#define DEM_DTCGRP_IDX_CHASSIS_DTCS                    2U

#if (defined DEM_DTCGRP_IDX_BODY_DTCS)
#error DEM_DTCGRP_IDX_BODY_DTCS already defined
#endif
/** \brief Symbolic name of DTC group BODY_DTCS index */
#define DEM_DTCGRP_IDX_BODY_DTCS                       3U

#if (defined DEM_DTCGRP_IDX_NETWORK_COM_DTCS)
#error DEM_DTCGRP_IDX_NETWORK_COM_DTCS already defined
#endif
/** \brief Symbolic name of DTC group NETWORK_COM_DTCS index */
#define DEM_DTCGRP_IDX_NETWORK_COM_DTCS                4U

#if (defined DEM_DTCGRP_IDX_NO_DTC)
#error DEM_DTCGRP_IDX_NO_DTC already defined
#endif
/** \brief Symbolic name of DTC group index for events without a DTC */
#define DEM_DTCGRP_IDX_NO_DTC  (DEM_DTCGRP_IDX_NETWORK_COM_DTCS + 1U)

#if (defined DEM_DTCGRP_IDX_INVALID)
#error DEM_DTCGRP_IDX_INVALID already defined
#endif
/** \brief Symbolic name of invalid DTC group index */
#define DEM_DTCGRP_IDX_INVALID  (DEM_DTCGRP_IDX_NO_DTC + 1U)

#if (defined DEM_NUM_DTC_GROUPS)
#error DEM_NUM_DTC_GROUPS already defined
#endif
/** \brief Number of DTC groups */
#define DEM_NUM_DTC_GROUPS 5U

/*------------------[Freeze frame configuration]----------------------------*/
/* Size of the freeze frame class DemFreezeFrameClass_0 in bytes: 10 */

#if (defined DEM_MAXSIZE_FFCLS)
#error DEM_MAXSIZE_FFCLS already defined
#endif
/** \brief Maximum size of a freeze frame class in bytes */
#define DEM_MAXSIZE_FFCLS 10U

/* Symblic names of internal freeze frame class indices */
#if (defined DEM_FFCLS_IDX_DemFreezeFrameClass_0)
#error DEM_FFCLS_IDX_DemFreezeFrameClass_0 already defined
#endif
/** \brief Symbolic name of freeze frame class DemFreezeFrameClass_0 index */
#define DEM_FFCLS_IDX_DemFreezeFrameClass_0           0U


#if (defined DEM_NUM_FFCLS)
#error DEM_NUM_FFCLS already defined
#endif
/** \brief Number of different freeze frame classes */
#define DEM_NUM_FFCLS 1U

#if (defined DEM_NUM_FFSEGS)
#error DEM_NUM_FFSEGS already defined
#endif
/** \brief Number of different freeze frame segments */
#define DEM_NUM_FFSEGS 5U

/*------------------[Freeze frame record number configuration]--------------*/

/*------------------[Prestored freeze frame configuration]------------------*/

#if (defined DEM_PFF_ZERO_END)
#error DEM_PFF_ZERO_END already defined
#endif
/** \brief Zero value to be added to each size, whose involved patterns could
 ** be none */
#define DEM_PFF_ZERO_END                  0U

#if (defined DEM_SIZE_PFF_ENTRY_DATA)
#error DEM_SIZE_PFF_ENTRY_DATA already defined
#endif
/** \brief Size of dynamic PFF entry data
 **
 ** All FF sizes of events with enabled prestorage are added.
 **/
#define DEM_SIZE_PFF_ENTRY_DATA \
  (DEM_PFF_ZERO_END)

/*------------------[Extended data configuration]---------------------------*/
/* Size of the extended data class DemExtendedDataClass_0 in bytes: 2 */

#if (defined DEM_MAXSIZE_EDCLS)
#error DEM_MAXSIZE_EDCLS already defined
#endif
/** \brief Maximum size of a extended data class in bytes */
#define DEM_MAXSIZE_EDCLS 2U

/* Symbolic names of internal extended data class indices */

#if (defined DEM_EDCLS_IDX_DemExtendedDataClass_0)
#error DEM_EDCLS_IDX_DemExtendedDataClass_0 already defined
#endif
/** \brief Symbolic name of extended data class DemExtendedDataClass_0 index */
#define DEM_EDCLS_IDX_DemExtendedDataClass_0          0U

#if (defined DEM_NUM_EDCLS)
#error DEM_NUM_EDCLS already defined
#endif
/** \brief Number of different extended data classes */
#define DEM_NUM_EDCLS 1U

#if (defined DEM_NUM_EDSEGS)
#error DEM_NUM_EDSEGS already defined
#endif
/** \brief Number of different extended data segments */
#define DEM_NUM_EDSEGS 1U

/*------------------[Data elements configuration]---------------------------*/

#if (defined DEM_NUM_EXT_CS_DATAELEMENTS)
#error DEM_NUM_EXT_CS_DATAELEMENTS already defined
#endif
/** \brief Number of different data elements of type DemExternalCSDataElementClass */
#define DEM_NUM_EXT_CS_DATAELEMENTS 5U

#if (defined DEM_INT_VAL_IDX_OCCCTR)
#error DEM_INT_VAL_IDX_OCCCTR already defined
#endif
/** \brief Macro for internal data element 'Occurence counter' */
#define DEM_INT_VAL_IDX_OCCCTR    DEM_NUM_EXT_CS_DATAELEMENTS

#if (defined DEM_INT_VAL_IDX_AGECTR)
#error DEM_INT_VAL_IDX_AGECTR already defined
#endif
/** \brief Macro for internal data element 'Aging counter' */
#define DEM_INT_VAL_IDX_AGECTR    (DEM_NUM_EXT_CS_DATAELEMENTS + 1U)

#if (defined DEM_INT_VAL_IDX_OVFIND)
#error DEM_INT_VAL_IDX_OVFIND already defined
#endif
/** \brief Macro for internal data element 'Overflow indication' */
#define DEM_INT_VAL_IDX_OVFIND    (DEM_NUM_EXT_CS_DATAELEMENTS + 2U)

#if (defined DEM_INT_VAL_IDX_EVSIGNIF)
#error DEM_INT_VAL_IDX_EVSIGNIF already defined
#endif
/** \brief Macro for internal data element 'Event significance' */
#define DEM_INT_VAL_IDX_EVSIGNIF  (DEM_NUM_EXT_CS_DATAELEMENTS + 3U)

/*------------------[Events configuration]----------------------------------*/

/* Static value width in bits used for Dem_EventDescType */

#if (defined DEM_UDS_DTC_WIDTH)
#error DEM_UDS_DTC_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of DTC */
#define DEM_UDS_DTC_WIDTH              24U

#if (defined DEM_DTCORIGIN_WIDTH)
#error DEM_DTCORIGIN_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of DTC origin */
#define DEM_DTCORIGIN_WIDTH            2U

#if (defined DEM_DTCGROUP_WIDTH)
#error DEM_DTCGROUP_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of DTC group */
#define DEM_DTCGROUP_WIDTH             5U

#if (defined DEM_IMMEDIATESTORAGE_WIDTH)
#error DEM_IMMEDIATESTORAGE_WIDTH already defined
#endif
/** \brief Number of bits to hold the status of Immediate storage */
#define DEM_IMMEDIATESTORAGE_WIDTH     1U

#if (defined DEM_DTCSEVERITY_WIDTH)
#error DEM_DTCSEVERITY_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of DTC severity */
#define DEM_DTCSEVERITY_WIDTH          2U

#if (defined DEM_ENABLEPRESTORAGE_WIDTH)
#error DEM_ENABLEPRESTORAGE_WIDTH already defined
#endif
/** \brief Number of bits to hold the status of Prestorage */
#define DEM_ENABLEPRESTORAGE_WIDTH     1U

#if (defined DEM_DEBOUNCEALGO_WIDTH)
#error DEM_DEBOUNCEALGO_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Debounce algorithm */
#define DEM_DEBOUNCEALGO_WIDTH         2U

/* Configurational value width in bits used for Dem_EventDescType */

#if (defined DEM_FFCLASSIDX_WIDTH)
#error DEM_FFCLASSIDX_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Freeze frame class index */
#define DEM_FFCLASSIDX_WIDTH           1U

#if (defined DEM_FFRECINFO_WIDTH)
#error DEM_FFRECINFO_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of maximum number of freeze frames */
#define DEM_FFRECINFO_WIDTH            1U

#if (defined DEM_EDCLASSIDX_WIDTH)
#error DEM_EDCLASSIDX_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Extended data class index */
#define DEM_EDCLASSIDX_WIDTH           1U

#if (defined DEM_OPCYCLEIDX_WIDTH)
#error DEM_OPCYCLEIDX_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Operation cycele index */
#define DEM_OPCYCLEIDX_WIDTH           1U

#if (defined DEM_AGINGCYCLES_WIDTH)
#error DEM_AGINGCYCLES_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of number of Aging cycles */
#define DEM_AGINGCYCLES_WIDTH          6U

#if (defined DEM_EVENTKIND_WIDTH)
#error DEM_EVENTKIND_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Event kind */
#define DEM_EVENTKIND_WIDTH            1U

#if (defined DEM_EVENTFAILURECLASSIDX_WIDTH)
#error DEM_EVENTFAILURECLASSIDX_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Event failure class index */
#define DEM_EVENTFAILURECLASSIDX_WIDTH 1U

#if (defined DEM_ENCONDIDX_WIDTH)
#error DEM_ENCONDIDX_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Enable condition index */
#define DEM_ENCONDIDX_WIDTH            1U

#if (defined DEM_NUMENCOND_WIDTH)
#error DEM_NUMENCOND_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of number of enable conditions */
#define DEM_NUMENCOND_WIDTH            1U

#if (defined DEM_INDICATORUSED_WIDTH)
#error DEM_INDICATORUSED_WIDTH already defined
#endif
/** \brief Number of bits to hold the status of Indicators */
#define DEM_INDICATORUSED_WIDTH        1U

#if (defined DEM_PRIORITY_WIDTH)
#error DEM_PRIORITY_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Internal priority */
#define DEM_PRIORITY_WIDTH             1U

#if (defined DEM_DEBOUNCEIDX_WIDTH)
#error DEM_DEBOUNCEIDX_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of Debounce index */
#define DEM_DEBOUNCEIDX_WIDTH          3U

#if (defined DEM_DTCFUNCTIONALUNIT_WIDTH)
#error DEM_DTCFUNCTIONALUNIT_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of DTC functional unit */
#define DEM_DTCFUNCTIONALUNIT_WIDTH    1U

#if (defined DEM_AGINGCYCLEIDX_WIDTH)
#error DEM_AGINGCYCLEIDX_WIDTH already defined
#endif
/** \brief Number of bits to hold the value of relative Aging cycle index
 *
 * The invalid value :: DEM_NUM_AGINGCYCLES is also included in the width. */
#define DEM_AGINGCYCLEIDX_WIDTH        2U

/*------------------[Warning indicators configuration]----------------------*/

#if (defined DEM_NUM_HEALINGCYC_COUNTER_INFO_ELEMENTS)
#error DEM_NUM_HEALINGCYC_COUNTER_INFO_ELEMENTS already defined
#endif
/** \brief Number of healing cycle-counter information elements */
#define DEM_NUM_HEALINGCYC_COUNTER_INFO_ELEMENTS 0

#if (defined DEM_NUM_FAILURECYC_COUNTER_INFO_ELEMENTS)
#error DEM_NUM_FAILURECYC_COUNTER_INFO_ELEMENTS already defined
#endif
/** \brief Number of failure cycle-counter information elements */
#define DEM_NUM_FAILURECYC_COUNTER_INFO_ELEMENTS 0

/*------------------[Enable conditions configuration]-----------------------*/

#if (defined DEM_NUM_ENCOND_LINKS)
#error DEM_NUM_ENCOND_LINKS already defined
#endif
/** \brief Number of enable condition links */
#define DEM_NUM_ENCOND_LINKS   0U

/*------------------[Debouncing configuration]------------------------------*/

#if (defined DEM_NUM_DEBOUNCE_COUNTER)
#error DEM_NUM_DEBOUNCE_COUNTER already defined
#endif
/** \brief Number of counter based debounced events */
#define DEM_NUM_DEBOUNCE_COUNTER   4U

#if (defined DEM_NUM_DEBOUNCE_TIME)
#error DEM_NUM_DEBOUNCE_TIME already defined
#endif
/** \brief Number of counter based debounced events */
#define DEM_NUM_DEBOUNCE_TIME      0U

#if (defined DEM_NUM_DEBOUNCE_FREQUENCY)
#error DEM_NUM_DEBOUNCE_FREQUENCY already defined
#endif
/** \brief Number of counter based debounced events */
#define DEM_NUM_DEBOUNCE_FREQUENCY 0U

/*------------------[Fault confirmation configuration]----------------------*/

#if (defined DEM_NO_FAULT_CONFIRMATION)
#error DEM_NO_FAULT_CONFIRMATION already defined
#endif
/** \brief Symbolic name for failure class index if default configuration is used */
#define DEM_NO_FAULT_CONFIRMATION 1U

/*------------------[Immediate storage configuration]-----------------------*/


/*------------------[Dynamic DTC configuration]-----------------------------*/


/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( DEM_INT_CFG_H ) */
/*==================[end of file]===========================================*/
