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
#ifndef COM_CORE_RXUPDATEBIT_H_
#define COM_CORE_RXUPDATEBIT_H_
/*==================[inclusions]============================================*/


#include <TSAutosar.h>          /* EB specific standard types */
#include <Com_Api.h>                /* get module interface */
#include <Com_Lcfg_Static.h>    /* declaration of the callback arrays */

#if (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL)

#if (COM_DEV_ERROR_DETECT == STD_ON)
#include <Det.h>                /* get development error tracer interface */
#endif /* (COM_DEV_ERROR_DETECT == STD_ON) */

/*==================[version check]=========================================*/

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/


#define COM_START_SEC_CODE
#include <MemMap.h>


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_CheckRxSignalGoupUpdateBitAndDM - handles update bit and DM of
 * Rx signals groups
 * this function evaluates the update bit and DM of Rx signals groups and
 * returns whether the value has to be replaced or not
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalGPtr - reference to the description of the signal group
 * \param[in] IPduPtr - reference to the description of the signal group
 * \retval TRUE if the signal was updated, else FALSE
 */

TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_CheckRxSignalGoupUpdateBitAndDM
(
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */

/** \brief Com_EB_CheckRxSignalUpdateBitAndDM - handles update bit and DM of
 * Rx signals this function evaluates the update bit and DM of Rx signals and
 * returns whether the value has to be replaced or not
 * Preconditions:
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr - reference to the description of the signal
 * \param[in] IPduPtr - reference to the description of the signal
 * \retval TRUE if the signal was updated, else FALSE
 */

TS_MOD_PRIV_DECL FUNC(boolean, COM_CODE) Com_EB_CheckRxSignalUpdateBitAndDM
(
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);


#if (COM_RX_SIGNAL_BASED_DM == STD_ON)

#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_RxDMSignalGroupQueue - "rewind" the RxDM timeout for a
 * signal group
 * This function starts a timeout for the Rx deadline monitoring of a
 * signal group
 * Preconditions:
 * - must only be invoked within a critical section
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalGPtr pointer to configuration of the Rx signal group to
 * start deadline monitoring
 * \param[in] TimeOutOffset - value which shall be used for "rewind"
 * \retval None
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_RxDMSignalGroupQueue
(
   P2CONST(ComRxSignalGroupType, AUTOMATIC, COM_APPL_CONST) SignalGPtr,
   Com_RxDMNextDueTimeType TimeOutOffset
);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


/** \brief Com_EB_RxDMSignalQueue - "rewind" the RxDM timeout for a signal
 * This function starts a timeout for the Rx deadline monitoring of a signal
 * Preconditions:
 * - must only be invoked within a critical section
 * - prior to this call, the COM must be initialized.
 * \param[in] SignalPtr pointer to configuration of the Rx signal to start
 * deadline monitoring
  * \param[in] TimeOutOffset - value which shall be used for "rewind"
 * \retval None
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE) Com_EB_RxDMSignalQueue
(
   P2CONST(ComRxSignalType, AUTOMATIC, COM_APPL_CONST) SignalPtr,
   Com_RxDMNextDueTimeType TimeOutOffset
);

/** \brief Com_EB_EnableSignalBasedDMFlag - sets up signal based DM
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \retval None
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE)Com_EB_EnableSignalBasedDMFlag
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);


#if (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE)
/** \brief Com_EB_EnableSignalGroupBasedDMFlag - sets up signal group based DM
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \retval None
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE)Com_EB_EnableSignalGroupBasedDMFlag
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr
);
#endif /* (COM_RX_SIGNAL_GROUP_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


/** \brief Com_EB_DisableSignalAndSignalGroupBasedDMFlag - disables
 * signal(group) based DM
 * Preconditions:
 * - prior to this call, the COM module shall be initialized
 * \param[in] IPduPtr - configuration of the I-Pdu
 * \param[in] Initialize - defines if timeout flag shall be cleared
 * \retval None
 */
TS_MOD_PRIV_DECL FUNC(void, COM_CODE)Com_EB_DisableSignalAndSignalGroupBasedDMFlag
(
   P2CONST(ComRxIPduType, AUTOMATIC, COM_APPL_CONST) IPduPtr,
   boolean Initialize
);

#endif /* (COM_RX_SIGNAL_BASED_DM == STD_ON) */


#define COM_STOP_SEC_CODE
#include <MemMap.h>

#endif /* (COM_UPDATE_BIT_RX_CONFIG != COM_UPDATE_BIT_ABSENT_FOR_ALL) */


#endif /* COM_CORE_RXUPDATEBIT_H_ */
/*==================[end of file]===========================================*/

