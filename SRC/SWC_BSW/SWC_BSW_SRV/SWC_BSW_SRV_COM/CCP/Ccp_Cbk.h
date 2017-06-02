/******************************************************************************/
/* !Layer           : COM                                                     */
/* !Component       : Ccp                                                     */
/* !Description     : Ccp                                                     */
/*                                                                            */
/* !File            : Ccp_Cbk.h                                               */
/* !Description     : header for Callbacks of CCP                             */
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

#ifndef CCP_CBK_H
#define CCP_CBK_H

#include "CanIf.h"

#define CanIf_CCP_FAST          TxPdu_CCP_TX_200 /* CAN Id 0x200 */
#define CanIf_CCP_MEDIUM        TxPdu_CCP_TX_201 /* CAN Id 0x201 */
#define CanIf_CCP_SLOW          TxPdu_CCP_TX_1ff /* CAN Id 0x1FF */
#define CanIf_CCP_DTO           TxPdu_CCP_TX_302 /* CAN Id 0x302 */
#define CanIf_CCP_CRO           RxPdu_CCP_RX_301 /* CAN Id 0x301 */

#define CanIf_CCP_DEVAID_FAST   TxPdu_CCP_TX_200 /* CAN Id 0x200 */
#define CanIf_CCP_DEVAID_MEDIUM TxPdu_CCP_TX_201 /* CAN Id 0x201 */
#define CanIf_CCP_DEVAID_SLOW   TxPdu_CCP_TX_1ff /* CAN Id 0x1FF */
#define CanIf_CCP_DEVAID_DTO    TxPdu_CCP_TX_302 /* CAN Id 0x302 */
#define CanIf_CCP_DEVAID_CRO    RxPdu_CCP_RX_301 /* CAN Id 0x301 */

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/
void Ccp_RxIndication_CRO(    PduIdType     RxPduId,
                              PduInfoType  *PduInfoPtr);
void Ccp_TxConfirmation_1ms(  PduIdType     TxPduId);
void Ccp_TxConfirmation_10ms( PduIdType     TxPduId);
void Ccp_TxConfirmation_100ms(PduIdType     TxPduId);
void Ccp_TxConfirmation_DTO(  PduIdType     TxPduId);

/*******************************************************************************
**                    Imported  Function Declarations                         **
*******************************************************************************/
extern void CCP_UsrTxConf_DTO(       PduIdType CanTxPduId);
extern void CCP_UsrTxConf_Devaid_DTO(PduIdType CanTxPduId);
extern void CCP_UsrRxInd_CRO(        PduIdType RxPduId, PduInfoType * PduInfoPtr);
extern void CCP_UsrRxInd_Devaid_CRO( PduIdType RxPduId, PduInfoType * PduInfoPtr);
extern void CCP_vidUsrTxConfirmation_DAQ_FAST(void);
extern void CCP_vidUsrTxConfirmation_DAQ_MEDIUM(void);
extern void CCP_vidUsrTxConfirmation_DAQ_SLOW(void);


#endif  /*END OF CCP_CBK_H */
