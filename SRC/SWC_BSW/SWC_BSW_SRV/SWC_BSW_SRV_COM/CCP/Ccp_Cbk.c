/******************************************************************************/
/* !Layer           : COM                                                     */
/* !Component       : Ccp                                                     */
/* !Description     : Ccp                                                     */
/*                                                                            */
/* !File            : Ccp_Cbk.c                                               */
/* !Description     : Callbacks of CCP                                        */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT VALEO all rights reserved                                        */
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#include "Ccp_Cbk.h"


#define CCP_START_SEC_CODE
#include "MemMap.h"

/******************************************************************************/
/* !FuncName    : Ccp_RxIndication                                            */
/*                                                                            */
/* !LastAuthor  : Ahmed Abohassan                                             */
/******************************************************************************/
void Ccp_RxIndication_CRO(PduIdType     RxPduId,
                          PduInfoType  *PduInfoPtr)
{
   CCP_UsrRxInd_CRO(RxPduId, PduInfoPtr);
}

/******************************************************************************/
/* !FuncName    : Ccp_TxConfirmation                                          */
/*                                                                            */
/* !LastAuthor  : Ahmed Abohassan                                             */
/******************************************************************************/
void Ccp_TxConfirmation_1ms(PduIdType TxPduId)
{
   CCP_vidUsrTxConfirmation_DAQ_FAST();
}

void Ccp_TxConfirmation_10ms(PduIdType TxPduId)
{
   CCP_vidUsrTxConfirmation_DAQ_MEDIUM();
}

void Ccp_TxConfirmation_100ms(PduIdType TxPduId)
{
   CCP_vidUsrTxConfirmation_DAQ_SLOW();
}

void Ccp_TxConfirmation_DTO(PduIdType TxPduId)
{
   CCP_UsrTxConf_DTO(TxPduId);
}


#define CCP_STOP_SEC_CODE
#include "MemMap.h"
/*------------------------------- end of file --------------------------------*/
