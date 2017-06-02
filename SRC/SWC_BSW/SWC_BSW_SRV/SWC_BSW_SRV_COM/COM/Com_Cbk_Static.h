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
#if (!defined COM_CBK_STATIC_H)
#define COM_CBK_STATIC_H


/*==================[inclusions]=============================================*/

#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#define COM_START_SEC_CODE
#include <MemMap.h>

/**
 * \brief Com_TriggerTransmit - copy data to PDU-router memory
 *
 * a function to be used to fetch data from the COM immediately
 * Preconditions:
 * - COM should be initialized
 *
 * \param[in] ComTxPduId - ID of the PDU which's data shall be copied
 * \param[in] PduInfoPtr - Contains a pointer to a buffer (SduDataPtr) to where the SDU
 * shall be copied to. On return, the service will indicate the length of
 * the copied SDU data in SduLength.
 * \return
 * \retval E_OK: SDU has been copied and SduLength indicates the
 * number of copied bytes.
 * \retval E_NOT_OK: No SDU has been copied. PduInfoPtr must not be
 * used since it may contain a NULL pointer or point to invalid data.
 *
 * \ServiceID{0x41}
 * \Reentrancy{Re-entrant for different values of ComTxPduId only.}
 * \Synchronicity{Synchronous}
 */
extern FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit
(
   PduIdType ComTxPduId,
   P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
);


/**
 * \brief Com_RxIndication - Signal the COM a PDU has arrived
 *
 * This functions signals the COM that a PDU has arrived
 * Preconditions:
 * - COM should be initialized
 *
 * \param[in] ComRxPduId - ID of the received I-PDU.
 * \param[in] PduInfoPtr - Contains the length (SduLength) of the received I-PDU and a pointer to
 * a buffer (SduDataPtr) containing the I-PDU.
 * \return
 * \retval None
 *
 * \ServiceID{0x42}
 * \Reentrancy{Re-entrant for different values of ComRxPduId only.}
 * \Synchronicity{Synchronous}
 */
extern FUNC(void, COM_CODE) Com_RxIndication
(
   PduIdType ComRxPduId,
   P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr
);


/**
 * \brief Com_TxConfirmation
 *
 * Function to signal the COM that an IPDU has been transmitted
 * Preconditions:
 * - COM should be initialized
 *
 * \param[in] ComTxPduId - ID of the PDU which was transmitted successfully
 * \return
 * \retval None
 *
 * \ServiceID{0x40}
 * \Reentrancy{Re-entrant for different values of ComTxPduId only.}
 * \Synchronicity{Synchronous}
 */
extern FUNC(void, COM_CODE ) Com_TxConfirmation
(
   PduIdType ComTxPduId
);


#define COM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/



/*==================[internal function definitions]==========================*/

#endif /* if !defined( COM_CBK_STATIC_H ) */
/*==================[end of file]============================================*/
