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
#if (!defined COM_FILTER_H)
#define COM_FILTER_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Rules.h>          /* Generated configuration + derived rules */

#if (COM_FILTER_AVAILABLE == STD_ON)
#include <Com_Api.h>            /* Module public API */

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

#define COM_START_SEC_CODE
#include <MemMap.h>

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

#if (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_FilterBoolean
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);
#endif /* (COM_SIGNAL_TYPE_BOOLEAN_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_FilterUint8
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT8_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_FilterSint8
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);
#endif /* (COM_SIGNAL_TYPE_SINT8_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_FilterUint16
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_FilterSint16
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);
#endif /* (COM_SIGNAL_TYPE_SINT16_ENABLE == STD_ON) */

#if (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_FilterUint32
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);
#endif /* (COM_SIGNAL_TYPE_UINT32_ENABLE == STD_ON) */


#if (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON)
TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_FilterSint32
(
   P2CONST(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr
);
#endif /* (COM_SIGNAL_TYPE_SINT32_ENABLE == STD_ON) */

/** \brief Com_EB_CreateFilterProp - initializes the internal
 * structure for the representation of filter
 * \param[out] ComFilterPropPtr - pointer where the result shall be stored
 * \param[in] ComOldValueRef - reference to buffer of filter
 * \param[in] ComFilterRef - reference to filter configuration
 * \param[in] ComFilterType - type of the filter
 * \retval None
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_CreateFilterProp
(
   P2VAR(ComCommonFilterPropertiesType, AUTOMATIC, AUTOMATIC) ComFilterPropPtr,
   ComSignalBufferRefType ComOldValueRef,
   ComFilterRefType ComFilterRef,
   uint8 ComFilterType
);

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#define COM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* (COM_FILTER_AVAILABLE == STD_ON) */
#endif /* COM_FILTER_H */
/*==================[end of file]===========================================*/

