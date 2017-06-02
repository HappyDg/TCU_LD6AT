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
#if (!defined DEM_INT_STC_H)
#define DEM_INT_STC_H

/* This file includes all relevant files for providing internal and external
 * static API declarations and type definitions. */

/*==================[inclusions]============================================*/
/* !LINKSTO dsn.Dem.IncludeStr,1 */

#include <Std_Types.h>                            /* AUTOSAR standard types */
#include <Dem_Stc.h>                  /* Module public static declarations */

/*==================[macros]================================================*/

#if (defined DEM_MAXNUM_ORIGINS)
#error DEM_MAXNUM_ORIGINS already defined
#endif
/** \brief Maximal number of configurable event memories/origins */
#define DEM_MAXNUM_ORIGINS 4U

#if (defined DEM_MAX_OCC_ORDER)
#error DEM_MAX_OCC_ORDER already defined
#endif
/** \brief Maximum possible value of occurrence order that can be stored in
 ** EventMemoryEntry.OccOrder
 **
 ** Its value should at least be greater than ::DEM_BSW_ERROR_BUFFER_SIZE and
 ** than the event memory entry sizes.
 */
#define DEM_MAX_OCC_ORDER 65535U


#if (defined DEM_DATA_PADDING_VALUE)
#error DEM_DATA_PADDING_VALUE already defined
#endif
/** \brief Padding value used for extended and freeze frame data */
#define DEM_DATA_PADDING_VALUE 0xFFU

#if (defined DEM_BITFIELD_VALUE_ALL_GROUPS)
#error DEM_BITFIELD_VALUE_ALL_GROUPS already defined
#endif
/** \brief "all groups" value for Dem_DTCSetting */
#define DEM_BITFIELD_VALUE_ALL_GROUPS  0xFFFFFFFFU

/*------------------[defines for debouncing]--------------------------------*/

#ifndef DEM_EVENT_STATUS_UNQUALIFIED
/** \brief Event status is not yet qualified
 **
 ** This is an extension of DEM_EVENT_STATUS_* macros, used for the internal
 ** debouncing status data. */
#define DEM_EVENT_STATUS_UNQUALIFIED   0xFFU
#endif

#if (defined DEM_FDC_VALUE_FAILED)
#error DEM_FDC_VALUE_FAILED already defined
#endif
/** \brief FDC value for a qualified FAILED event */
#define DEM_FDC_VALUE_FAILED     127 /* note: this must be a signed value! */

#if (defined DEM_FDC_VALUE_PASSED)
#error DEM_FDC_VALUE_PASSED already defined
#endif
/** \brief FDC value for a qualified PASSED event */
#define DEM_FDC_VALUE_PASSED    -128 /* note: this must be a signed value! */

/*------------------[defines for ClearDtc]----------------------------------*/

#if (defined DEM_CLEARDTC_STATE_IDLE)
#error DEM_CLEARDTC_STATE_IDLE already defined
#endif
/** \brief Run state value of an async. ClearDtc process: IDLE, NOT RUNNING */
#define DEM_CLEARDTC_STATE_IDLE      0U

#if (defined DEM_CLEARDTC_STATE_RUNNING)
#error DEM_CLEARDTC_STATE_RUNNING already defined
#endif
/** \brief Run state value of an async. ClearDtc process: RUNNING, PENDING */
#define DEM_CLEARDTC_STATE_RUNNING   1U

#if (defined DEM_CLEARDTC_STATE_CANCELLED)
#error DEM_CLEARDTC_STATE_CANCELLED already defined
#endif
/** \brief Run state value of an async. ClearDtc process: RUNNING, CANCELLED */
#define DEM_CLEARDTC_STATE_CANCELLED 2U

#if (defined DEM_CLEARDTC_STATE_FAILED)
#error DEM_CLEARDTC_STATE_FAILED already defined
#endif
/** \brief Run state value of an async. ClearDtc process: RUNNING, FINISHED */
#define DEM_CLEARDTC_STATE_FAILED  3U

#if (defined DEM_CLEARDTC_STATE_FINISHED)
#error DEM_CLEARDTC_STATE_FINISHED already defined
#endif
/** \brief Run state value of an async. ClearDtc process: RUNNING, FINISHED */
#define DEM_CLEARDTC_STATE_FINISHED  4U

/*------------------[Several helper macros]---------------------------------*/

#if (defined DEM_BIT_FIELD_VALUE_32)
#error DEM_BIT_FIELD_VALUE_32 already defined
#endif
/** \brief Shifts field with offset, and returns the masked value
 **
 ** Macro is intended for Gbi getter functions.
 **
 */
#define DEM_BIT_FIELD_VALUE_32(field, offset, mask) \
  ((uint32) ((uint32) ((uint32) (field) >> (offset)) & (uint32) (mask)))


#if (defined DEM_IS_BIT_SET_IN_ARRAY)
#error DEM_IS_BIT_SET_IN_ARRAY already defined
#endif
/** \brief Is bit set in an uint8-array */
#define DEM_IS_BIT_SET_IN_ARRAY(Array, Idx) \
  (((Array)[(Idx) / 8U] & ((uint8) (1U << ((Idx) % 8U)))) != 0U)

#if (defined DEM_SET_BIT_IN_ARRAY)
#error DEM_SET_BIT_IN_ARRAY already defined
#endif
/** \brief Set bit in an uint8-array */
#define DEM_SET_BIT_IN_ARRAY(Array, Idx) \
  ((Array)[(Idx) / 8U] |= (uint8)  (1U << ((Idx) % 8U)))

#if (defined DEM_CLR_BIT_IN_ARRAY)
#error DEM_CLR_BIT_IN_ARRAY already defined
#endif
/** \brief Clear bit in an uint8-array */
#define DEM_CLR_BIT_IN_ARRAY(Array, Idx) \
  ((Array)[(Idx) / 8U] &= (uint8) ~((uint8) (1U << ((Idx) % 8U))))


#if (defined DEM_SET_BIT_32)
#error DEM_SET_BIT_32 already defined
#endif
/** \brief Set bit in an uint32 bitfield */
#define DEM_SET_BIT_32(Bitfield, Idx) \
  ((Bitfield) |= (uint32) ((uint32) 1U << (Idx)))

#if (defined DEM_CLR_BIT_32)
#error DEM_CLR_BIT_32 already defined
#endif
/** \brief Clear bit in an uint32 bitfield */
#define DEM_CLR_BIT_32(Bitfield, Idx) \
  ((Bitfield) &= (uint32) ~( (uint32) ((uint32) 1U << (Idx))))


#if (defined DEM_ATOMIC_SET_BIT_IN_ARRAY_8)
#error DEM_ATOMIC_SET_BIT_IN_ARRAY_8 already defined
#endif
/** \brief Set bit in an uint8-array, atomic */
#define DEM_ATOMIC_SET_BIT_IN_ARRAY_8(ByteArray, BitIndex) \
  do \
  { \
    const uint16 idx = (BitIndex); \
    TS_AtomicSetBit_8(&((ByteArray)[idx / 8U]), idx % 8U); \
  } while (0)

#if (defined DEM_ATOMIC_CLR_BIT_IN_ARRAY_8)
#error DEM_ATOMIC_CLR_BIT_IN_ARRAY_8 already defined
#endif
/** \brief Clear bit in an uint8-array, atomic */
#define DEM_ATOMIC_CLR_BIT_IN_ARRAY_8(ByteArray, BitIndex) \
  do \
  { \
    const uint16 idx = (BitIndex); \
    TS_AtomicClearBit_8(&((ByteArray)[idx / 8U]), idx % 8U); \
  } while (0)


#if (defined DEM_ATOMIC_SET_BIT_32)
#error DEM_ATOMIC_SET_BIT_32 already defined
#endif
/** \brief Set bit in an uint32 bitfield, atomic */
#define DEM_ATOMIC_SET_BIT_32(Bitfield, Idx) \
  do { TS_AtomicSetBit_32(&(Bitfield), (Idx)); } while (0)

#if (defined DEM_ATOMIC_CLR_BIT_32)
#error DEM_ATOMIC_CLR_BIT_32 already defined
#endif
/** \brief Clear bit in an uint32 bitfield, atomic */
#define DEM_ATOMIC_CLR_BIT_32(Bitfield, Idx) \
  do { TS_AtomicClearBit_32(&(Bitfield), (Idx)); } while (0)


#if (defined DEM_ATOMIC_SET_BIT_8)
#error DEM_ATOMIC_SET_BIT_8 already defined
#endif
/** \brief Set bit in an uint8 bitfield, atomic */
#define DEM_ATOMIC_SET_BIT_8(Bitfield, Idx) \
  do { TS_AtomicSetBit_8(&(Bitfield), (Idx)); } while (0)

#if (defined DEM_ATOMIC_CLR_BIT_8)
#error DEM_ATOMIC_CLR_BIT_8 already defined
#endif
/** \brief Clear bit in an uint8 bitfield, atomic */
#define DEM_ATOMIC_CLR_BIT_8(Bitfield, Idx) \
  do { TS_AtomicClearBit_8(&(Bitfield), (Idx)); } while (0)


#if (defined DEM_ATOMIC_ASSIGN_8)
#error DEM_ATOMIC_ASSIGN_8 already defined
#endif
/** \brief Clear bit in an uint8 bitfield, atomic */
#define DEM_ATOMIC_ASSIGN_8(to, from) TS_AtomicAssign8((to), (from))

#if (defined DEM_ATOMIC_ASSIGN_32)
#error DEM_ATOMIC_ASSIGN_32 already defined
#endif
/** \brief Clear bit in an uint8 bitfield, atomic */
#define DEM_ATOMIC_ASSIGN_32(to, from) TS_AtomicAssign32((to), (from))


#if (defined DEM_IS_BIT_SET)
#error DEM_IS_BIT_SET already defined
#endif
/** \brief Logical expression of the condition, that at least one bit, set in
 ** "Mask", is set in "Byte"
 */
#define DEM_IS_BIT_SET(Byte, Mask) \
  (((Byte) & (Mask)) != 0U)

#if (defined DEM_BITS_SET)
#error DEM_BITS_SET already defined
#endif

/** \brief Logical expression of the condition, that all bits, set in
 ** "Mask", are set in "Byte"
 */
#define DEM_BITS_SET(Byte, Mask) \
  (((Byte) & (Mask)) == (Mask))

#if (defined DEM_IS_UNMASKED_BIT_SET)
#error DEM_IS_UNMASKED_BIT_SET already defined
#endif
/** \brief Logical expression of the condition, that at least one unmasked bit
 ** is set in "Byte"
 */
#define DEM_IS_UNMASKED_BIT_SET(Byte, Mask) \
  (((Byte) & (uint8)(~((uint8)(Mask)))) != 0U)

#if (defined DEM_SET_MASK)
#error DEM_SET_MASK already defined
#endif
/** \brief Non-atomic 'set bit by mask' macro */
#define DEM_SET_MASK(to, mask) \
  (to) |= (mask)

#if (defined DEM_CLR_MASK)
#error DEM_CLR_MASK already defined
#endif
/** \brief Non-atomic 'clear bit by mask' macro */
#define DEM_CLR_MASK_8(to, mask) \
  (to) &= (uint8)(~(mask))

#if (defined DEM_ATOMIC_SET_MASK)
#error DEM_ATOMIC_SET_MASK already defined
#endif
/** \brief Atomic 'set bits by mask' macro
 *
 *  This macro is intended to be replaced by platform macros that can use fast
 *  optimized locking mechanism (e.g. INT lock).
 */
#define DEM_ATOMIC_SET_MASK(to, set_mask)       \
  do                                            \
  {                                             \
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0(); \
    DEM_SET_MASK((to), (set_mask));             \
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();  \
  } while(0)

#if (defined DEM_ATOMIC_CLR_MASK)
#error DEM_ATOMIC_CLR_MASK already defined
#endif
/** \brief Atomic 'clear bit by mask' macro
 *
 *  This macro is intended to be replaced by platform macros that can use fast
 *  optimized locking mechanism (e.g. INT lock).
 */
#define DEM_ATOMIC_CLR_MASK(to, clr_mask)       \
  do                                            \
  {                                             \
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0(); \
    DEM_CLR_MASK_8((to), (clr_mask));           \
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();  \
  } while(0)

#if (defined DEM_ATOMIC_CHNG_MASK)
#error DEM_ATOMIC_CHNG_MASK already defined
#endif
/** \brief Atomic 'clear bit by mask macro'
 *
 *  This macro is intended to be supported by platform macros that can use fast
 *  optimized locking mechanism (e.g. INT lock).
 */
#define DEM_ATOMIC_CHNG_MASK(to, set_mask, clr_mask) \
  do                                                 \
  {                                                  \
    SchM_Enter_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();      \
    DEM_SET_MASK((to), (set_mask));                  \
    DEM_CLR_MASK_8((to), (clr_mask));                \
    SchM_Exit_Dem_SCHM_DEM_EXCLUSIVE_AREA_0();       \
  } while(0)

/*------------------[bit definition for RTE- & C-callback function]---------*/

#if (defined DEM_GEN_CB_INIT_MONITOR)
#error DEM_GEN_CB_INIT_MONITOR already defined
#endif
/** \brief Mask value for property of Init monitor General-callback function */
#define DEM_GEN_CB_INIT_MONITOR                      0x01U


#if (defined DEM_RTE_CB_TRIG_ON_EVST)
#error DEM_RTE_CB_TRIG_ON_EVST already defined
#endif
/** \brief Mask value for property of Trigger on event status RTE-callback
 ** function
 */
#define DEM_RTE_CB_TRIG_ON_EVST                      0x02U

#if (defined DEM_C_CB_TRIG_ON_EVST)
#error DEM_C_CB_TRIG_ON_EVST already defined
#endif
/** \brief Mask value for property of Trigger on event status C-callback
 ** function
 */
#define DEM_C_CB_TRIG_ON_EVST                        0x04U


#if (defined DEM_RTE_CB_TRIG_ON_EVDAT)
#error DEM_RTE_CB_TRIG_ON_EVDAT already defined
#endif
/** \brief Mask value for property of Trigger on event data changed
 ** RTE-callback function
 */
#define DEM_RTE_CB_TRIG_ON_EVDAT                     0x08U

#if (defined DEM_C_CB_TRIG_ON_EVDAT)
#error DEM_C_CB_TRIG_ON_EVDAT already defined
#endif
/** \brief Mask value for property of Trigger on event data changed
 ** C-callback function
 */
#define DEM_C_CB_TRIG_ON_EVDAT                       0x10U


#if (defined DEM_RTE_CB_CLEAR_EVENT_ALLOWED)
#error DEM_RTE_CB_CLEAR_EVENT_ALLOWED already defined
#endif
/** \brief Mask value for property of Clear event allowed RTE-callback function */
#define DEM_RTE_CB_CLEAR_EVENT_ALLOWED               0x20U

#if (defined DEM_C_CB_CLEAR_EVENT_ALLOWED)
#error DEM_C_CB_CLEAR_EVENT_ALLOWED already defined
#endif
/** \brief Mask value for property of Clear event allowed C-callback function */
#define DEM_C_CB_CLEAR_EVENT_ALLOWED                 0x40U


#if (defined DEM_GEN_CB_FAULT_DETECTION_CTR)
#error DEM_GEN_CB_FAULT_DETECTION_CTR already defined
#endif
/** \brief Mask value for property of FDC General-callback function */
#define DEM_GEN_CB_FAULT_DETECTION_CTR               0x80U

/*==================[type definitions]======================================*/

/*------------------[Dem_EventKindType]-------------------------------------*/

/** \brief Type for Dem_GbiEventKind() */
typedef uint8 Dem_EventKindType;

#if (defined DEM_EVENT_KIND_BSW)
#error DEM_EVENT_KIND_BSW already defined
#endif
/** \brief Event kind BSW */
#define DEM_EVENT_KIND_BSW           0x00U

#if (defined DEM_EVENT_KIND_SWC)
#error DEM_EVENT_KIND_SWC already defined
#endif
/** \brief Event kind SWC */
#define DEM_EVENT_KIND_SWC           0x01U

/** \brief Debounce algorithm type */
typedef enum
{
  DEM_DEBOUNCE_MONITOR,
                   /**< value/index signaling "monitor internal" debouncing */
  DEM_DEBOUNCE_COUNTERBASED,
                        /**< value/index signaling counter based debouncing */
  DEM_DEBOUNCE_TIMEBASED,
                           /**< value/index signaling time based debouncing */
  DEM_DEBOUNCE_FREQUENCYBASED,
                      /**< value/index signaling frequency based debouncing */
  DEM_MAXNUM_DEBOUNCECLASSES
           /**< Maximal number of different configurable debouncing classes */
} Dem_DebounceType;

/** \brief This type is used for the state-values of the initialization state
 ** of the Dem
 */
typedef enum {
  DEM_UNINITIALIZED,                            /**< Dem is not initialized */
  DEM_PREINITIALIZED,                           /**< Dem is pre-initialized */
  DEM_INITIALIZED,                             /**< Dem is full initialized */
  DEM_POSTINITIALIZED                          /**< Dem is post-initialized */
} Dem_InitializationStateType;

/** \brief This type is for global counting of event Ids
 **
 ** This is done to avoid an overflow, if exactly 255 event Ids are used.
 **
 ** Note: It is derived from the maximal size of the type ::Dem_EventIdType.
 */
typedef uint16 Dem_EvIdMaxType;

/** \brief This type is for local counting of event Ids
 **
 ** This is done to avoid an overflow, if exactly 255 event Ids are used.
 **
 ** Note: It is derived from the maximal size of the type ::Dem_EventIdType.
 */
typedef uint16_least Dem_EvIdLeastType;

/** \brief Return values of function Dem_GetEvIdByDTC() */
typedef enum
{
  DEM_EIBD_OK,                                      /**< Matching DTC found */
  DEM_EIBD_WRONG_DTC,                                      /**< Invalid DTC */
  DEM_EIBD_WRONG_DTCORIGIN                      /**< Mismatch in DTC origin */
} Dem_ReturnGetEvIdByDTCType;

/** \brief Event memory entry size type */
typedef uint8 Dem_SizeEvMemEntryType;

/*------------------[definitions for Data Element/FF/ED class types]--------*/

/*------------------[definitions for Data Element type]---------------------*/

/** \brief Index of data element type
 **
 ** Index concerning ::Dem_DataElement[]. The range of this type is limited by
 ** the data element references possible (equals 255).
 **
 ** Note: Maximum number (FFSegment.NumFFDataElements and EDSegment.NumEDDataElements)
 ** also uses this type, as the value fits into this range.
 */
typedef uint8 Dem_DataElementIdxType;

/** \brief Offset for data element
 **
 ** Offset will not be greater than 255.
 ** This is derived from the maximum size of a FF segment / ED segment.
 */
typedef uint8 Dem_DataElementOffsetType;

/** \brief C/RTE-Callback function prototype for getting data element values
 **
 ** Note: In case of ::E_NOT_OK is returned by data value callback function,
 ** the Dem fills the missing data with the padding value 0xFF, reports the
 ** development error ::DEM_E_NODATAAVAILABLE to the DET and continuous his
 ** normal operation.
 */
typedef P2FUNC(Std_ReturnType, DEM_APPL_CODE, Dem_CbFuncPtrReadData) (
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);

/** \brief Layout information of data elements
 **
 ** This does not include data elements of type DemInternalDataElementClass.
 ** Indices of DemInternalDataElementClass type data elements starts after
 ** that of DemExternalCSDataElementClass.
 */
typedef struct
{
  const uint8 Size;                               /**< Size of data element */
  const Dem_CbFuncPtrReadData Callback;   /**< Data value callback function */
} Dem_DataElementType;

/*------------------[definitions for FF segment types]----------------------*/

/** \brief Layout information of freeze frame segments (DIDs) */
typedef struct
{
  const Dem_DataElementIdxType NumFFDataElements;
                                               /**< Number of data elements */
  const uint16 DataId;          /**< DID identifier of freeze frame segment */
  CONSTP2CONST(Dem_DataElementIdxType, AUTOMATIC, DEM_CONST) DataElementIdx;
              /**< Indices to data elements (array - ::Dem_DataElementType) */
  CONSTP2CONST(Dem_DataElementOffsetType, AUTOMATIC, DEM_CONST)
    DataElementOffset;              /**< Positions of data elements (array) */
} Dem_FFSegmentType;

/** \brief Index of freeze frame segment type
 **
 ** Index concerning ::Dem_FFSegments[]. The range of this type is limited by
 ** the configuration (parameter DemDidClass).
 **
 ** Note: The range for FF segments per FF class is defined by multiplicity
 ** of DemDidClassRef (equals 255).
 ** Maximum number (FFClass.NumFFSegs) also uses this type, as the value
 ** fits into this range.
 */
typedef uint8 Dem_FFSegIdxType;

/** \brief Start Byte of freeze frame segment type
 **
 ** Start bytes will not be greater than 255.
 ** Dem_DltGetMostRecentFreezeFrameRecordData() indirectly limits the size of
 ** a freeze frame (which is the sum of all assigned DID sizes) to maximal
 ** 255 by its parameter 'BufSize'.
 */
typedef uint8 Dem_FFStartByteType;

/*------------------[definitions for FF class types]------------------------*/

/** \brief Layout information of freeze frame classes */
typedef struct
{
  const Dem_FFSegIdxType NumFFSegs;
                                /**< Number of freeze frame segments (DIDs) */
  CONSTP2CONST(Dem_FFSegIdxType, AUTOMATIC, DEM_CONST) FFSegIdx;
        /**< Indices to freeze frame segments (array - ::Dem_FFSegmentType) */
  CONSTP2CONST(Dem_FFStartByteType, AUTOMATIC, DEM_CONST) StartByte;
                            /**< Positions of freeze frame segments (array) */
} Dem_FFClassType;

/** \brief Index of freeze frame class type
 **
 ** NumFFClass variables are also of this type.
 */
typedef uint8 Dem_FFClassIdxType;

/** \brief  Freeze frame size type
 **
 ** Freeze frame class size will not be greater than 255.
 ** There are checks for DemFreezeFrameClass and DemDidClass which limit their
 ** sizes to 255.
 */
typedef uint8 Dem_SizeFFType;

/*------------------[definitions for FF record numeration class types]------*/

/** \brief Layout information of freeze frame record numeration classes */
typedef struct
{
  const Dem_FFIdxType NumFFRecs;        /**< Number of freeze frame records */
  CONSTP2CONST(Dem_FFIdxType, AUTOMATIC, DEM_CONST) Dem_FFRecNumClassIdx;
                                    /**< Pointer to array of record numbers */
} Dem_FFRecNumerationClassType;

/*------------------[definitions for ED segment types]----------------------*/

/** \brief Layout information of extended data segments (Records) */
typedef struct
{
  const Dem_DataElementIdxType NumEDDataElements;
                                               /**< Number of data elements */
  const uint8 RecNum;                      /**< Extended data Record Number */
  const boolean Update;             /**< Extended data Record update status */
  CONSTP2CONST(Dem_DataElementIdxType, AUTOMATIC, DEM_CONST) DataElementIdx;
              /**< Indices to data elements (array - ::Dem_DataElementType) */
  CONSTP2CONST(Dem_DataElementOffsetType, AUTOMATIC, DEM_CONST)
    DataElementOffset;              /**< Positions of data elements (array) */
} Dem_EDSegmentType;

/** \brief Index of extended data segment type
 **
 ** Index concerning ::Dem_EDSegments[]. The range of this type is limited by
 ** the record number (equals 1 byte).
 **
 ** Note: The range for ED segments per ED class is defined by ISO14229-1
 ** (ED RecordNumber = 0x01 ... 0xFE).
 ** Maximum number (EDClass.NumEDSegs) also uses this type, as the value
 ** fits into this range..
 */
typedef uint8 Dem_EDSegIdxType;

/** \brief Start Byte of extended data segment type
 **
 ** Start bytes will not be greater than 255.
 ** Dem_DltGetAllExtendedDataRecords() indirectly limits the size of a
 ** extended data (which is the sum of all assigned ED record sizes)
 ** to maximal 255 by its parameter 'BufSize'.
 */
typedef uint8 Dem_EDStartByteType;

/*------------------[definitions for ED class types]------------------------*/

/** \brief Layout information of extended data classes */
typedef struct
{
  const Dem_EDSegIdxType NumEDSegs;
                            /**< Number of extended data segments (Records) */
  CONSTP2CONST(Dem_EDSegIdxType, AUTOMATIC, DEM_CONST) EDSegIdx;
       /**< Indices to extended data segments (array - ::Dem_EDSegmentType) */
  CONSTP2CONST(Dem_EDStartByteType, AUTOMATIC, DEM_CONST) StartByte;
                           /**< Positions of extended data segments (array) */
} Dem_EDClassType;

/** \brief Index of extended data class type
 **
 ** NumEDClass variables are also of this type.
 */
typedef uint8 Dem_EDClassIdxType;

/** \brief  Extended data size type
 **
 ** Extended data class size will not be greater than 255.
 ** There are checks for DemExtendedDataClass and DemExtendedDataRecordClass
 ** which limit their sizes to 255.
 */
typedef uint8 Dem_SizeEDType;

/*---------------[definitions for notifications messages]-------------------*/

/** \brief Data type for notification "OnEventStatusChanged" */
typedef struct
{
  Dem_EventIdType       EventId;
  Dem_DTCStatusMaskType OldStatusMask;
  Dem_DTCStatusMaskType NewStatusMask;
} Dem_EventStatusChangedMsgType;

/** \brief Pointer type for notification "OnEventStatusChanged" */
typedef P2VAR(Dem_EventStatusChangedMsgType, TYPEDEF, DEM_VAR_NOINIT)
  Dem_EventStatusChangedMsgPtrType;

/*------------------[pointer types]-----------------------------------------*/

/** \brief Pointer to ::Dem_EntryDataType */
typedef P2VAR(Dem_EntryDataType, TYPEDEF, DEM_VAR_NOINIT)
  Dem_EntryDataPtrType;

/** \brief Pointer to const ::Dem_EntryDataType */
typedef P2CONST(Dem_EntryDataType, TYPEDEF, DEM_VAR_NOINIT)
  Dem_EntryDataPtrConstType;

/*--------------------------------------------------------------------------*/

/** \brief Type for value of Aging cycles */
typedef uint8 Dem_AgingCyclesType;

/** \brief Type for Priority */
typedef uint8 Dem_PriorityType;

/** \brief Static event/DTC description type
 **
 ** The 'bit packing scheme' is used. Access to the values is possible with
 ** the getter functions like Dem_GbiDTC().
 */
typedef struct
{
  uint32 EvConf1;
  /**< 1. Word of the event description bit-package:
   *
   * - d[24]: DTC (DTC value)
   * - oo:    DTCOrigin
   * - ggggg: DTCGroup            (var size - 3 to 5 bit according to configuration)
   * - i:     ImmediateStorage
   *
   * Memory layout:
   * xxxx xxxx  xxxx xxxx  xxxx xxxx  xxxx xxxx
   * iggg ggoo  dddd dddd  dddd dddd  dddd dddd */

  uint32 EvConf2;
  /**< 2. Word of the event description bit-package:
   *
   * - ss:   DTCSeverity
   * - p:    EnablePrestorage
   * - tttt: FFClassIdx           (var size - max. 8 bit according to type)
   * - nnnn: FFRecInfo            (var size - max. 8 bit according to ISO14229-1)
   * - eeee: EDClassIdx           (var size - max. 8 bit according to type)
   * - oooo: OpCycleIdx           (var size - max. 8 bit according to type)
   * - a[7]: AgingCycles          (var size - max. 8 bit according to configuration)
   * - k   : EventKind
   * - f[5]: EventFailureClassIdx (var size - max. 16 bit according to configuration)
   *
   * Memory layout:
   * xxxx xxxx  xxxx xxxx  xxxx xxxx  xxxx xxxx
   * ffff fkaa  aaaa aooo  oeee ennn  nttt tpss */

  uint32 EvConf3;
  /**< 3. Word of the event description bit-package:
   *
   * - cccc: EnCondIdx            (var size)
   * - ee:   NumEnCond            (var size - max. 8 bit according to configuration)
   * - i:    IndicatorUsed
   * - ppp:  Priority             (var size) (deactivated in this version)
   * - dd:   DebounceAlgo
   * - y[8]: DebounceIdx          (var size - max. 16 bit according to EventIdType)
   * - u[8]: DTCFuncUnit          (var size - max. 8 bit according to ISO14229-1)
   * - aaaa: AgingCycleIdx        (var size - max. 8 bit according to type)
   *
   * Memory layout:
   * xxxx xxxx  xxxx xxxx  xxxx xxxx  xxxx xxxx
   * aaaa uuuu  uuuu yyyy  yyyy ddpp  piee cccc */
} Dem_EventDescType;

/** \brief This type is used as index type for the enable conditions
 **
 ** Its size (uint8) is given by API Dem_SetEnableCondition().
 **
 ** NumEnCond values are also of this type.
 */
typedef uint8 Dem_EnableConditionIdType;

/** \brief This type is used as index type for the error-queue
 **
 ** Its size (uint8) is given by configuration. */
typedef uint8 Dem_ErrorQueueIdxType;

/** \brief Type for error-queue entries
 **
 ** - e[15]: event Id             (limited by configuration)
 ** - s:     passed/failed status (as per ::Dem_EventStatusType)
 **
 ** Memory layout:
 ** xxxx xxxx  xxxx xxxx
 ** seee eeee  eeee eeee */
typedef uint16 Dem_ErrorQueueEntryType;

/** \brief Type for event failure cycle configuration */
typedef struct
{
  Dem_OperationCycleIdType    EventFailureCycleIdx;   /**< Failure cycle Id */
  Dem_FailureCycleCounterType EventFailureCycleCounterThreshold;
                       /**< Number of failure cycles for fault confirmation */
} Dem_EventFailureCycleCfgType;

/** \brief Type for event failure counter buffer */
typedef struct
{
  Dem_EventIdType             EventId;           /**< Event Id of the entry */
  Dem_FailureCycleCounterType FailureCycleCounter;
                                                 /**< Event failure counter */
} Dem_EventFailureCycleCounterBufferType;

/*==================[external function declarations]========================*/

#define DEM_START_SEC_CODE
#include <MemMap.h>

/*------------------[static internal function prototypes]-------------------*/

/** \brief Function to shift entry data
 **
 ** \param[in] EntryData
 ** \param[in] offset
 ** \param[in] width
 **
 ** \Reentrancy{Non reentrant}
 ** \Synchronicity{Synchronous}
 */
extern FUNC(void, DEM_CODE) Dem_ShiftData(
  Dem_EntryDataPtrType        EntryData,
  const Dem_SizeEntryDataType offset,
  Dem_SizeEntryDataType       width);

#define DEM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#define DEM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Array holding the sizes of the 3 event memories */
extern CONST(Dem_SizeEvMemEntryType, DEM_CONST)
  Dem_SizeEventMem[DEM_MAXNUM_ORIGINS];

/** \brief Array holding the sizes of the 3 event mem. entry data areas */
extern CONST(Dem_SizeEntryDataType, DEM_CONST)
  Dem_SizeEntryData[DEM_MAXNUM_ORIGINS];

/** \brief Array holding the pointers to the 3 event mem. entry data areas */
extern CONSTP2VAR(Dem_EntryDataType, DEM_CONST, DEM_VAR_NOINIT)
  Dem_EntryData[DEM_MAXNUM_ORIGINS];

/** \brief Array holding the pointers to the 3 event mem. entry data free
 ** positions
 */
extern CONSTP2VAR(Dem_SizeEntryDataType, DEM_CONST, DEM_VAR_NOINIT)
  Dem_EntryDataFreePos[DEM_MAXNUM_ORIGINS];

/** \brief Pointer to the prestored freeze frame data area */
extern CONSTP2VAR(Dem_EntryDataType, DEM_CONST, DEM_VAR_NOINIT)
  Dem_PFFEntryData;

#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Status of the Dem
 **
 ** This flag is used to store the initialization state of the Dem. It's only
 ** be modified (written) by the functions Dem_PreInit(), Dem_Init() and
 ** Dem_Shutdown().
 */
extern VAR(Dem_InitializationStateType, DEM_VAR) Dem_InitializationState;

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

#define DEM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Status of record-filter
 **
 ** This variable is used from freeze frame record-based filter functions.
 **
 ** It holds the FF record index of current record filter entry
 */
extern VAR(uint8, DEM_VAR_NOINIT) Dem_RecordFilterRecNumIdx;

#define DEM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Lock for Dcm access
 **
 ** This variable is used as a semaphore to prevent the Dem_MainFunction()
 ** from interrupting Dcm access functions and the ED/FF getter functions.
 */
extern VAR(uint8, DEM_VAR_NOINIT) Dem_EvMemReadAccessSemaphore;

/** \brief EventId of record update disabled DTC
 **
 ** It holds the EventId corresponding to the DTC locked via
 ** Dem_DisableDTCRecordUpdate()
 */
extern VAR(Dem_EventIdType, DEM_VAR_NOINIT) Dem_EvIdOfRecordUpdateDisabledDTC;

/** \brief Record filter entry index
 **
 ** This variable is used from freeze frame record-based filter functions.
 **
 ** It holds the current event memory index set by Dem_SetFreezeFrameRecordFilter().
 */
extern VAR(Dem_SizeEvMemEntryType, DEM_VAR_NOINIT) Dem_RecordFilterEntryIdx;

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

#define DEM_START_SEC_VAR_NO_INIT_32
#include <MemMap.h>

/** \brief Bits encode whether DTC setting is allowed for
 ** the specific DTC group
 **
 ** bits 1..(N-1) DEM_DTCGRP_IDX_<>: 1=enabled, 0=disabled
 ** bit N ::DEM_DTCGRP_IDX_NO_DTC  : always enabled (1)
 **                                  for events with no DTC configured
 */
extern VAR(uint32, DEM_VAR_NOINIT) Dem_DTCSettingAllowed;

#define DEM_STOP_SEC_VAR_NO_INIT_32
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( DEM_INT_STC_H ) */
/*==================[end of file]===========================================*/
