/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_CAN                                                 */
/* !Description     : Test of CAN component                                   */
/*                                                                            */
/* !File            : TST_CAN.h                                               */
/* !Description     : Test of CAN component APIs                              */
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

#ifndef TST_CAN_H
#define TST_CAN_H

#include "Std_Types.h"
#include "CAN.h"
#include "CANIF.h"

/******************************************************************************/
/* DEFINE DECLARATIONS                                                        */
/******************************************************************************/
#define CCP_DAQ_BASE_FAST    0
#define CCP_DAQ_BASE_MEDIUM  1
#define CCP_DAQ_BASE_SLOW    2
#define CCP_DTO              3
#define CCP_CRO              4
#define CCP_CRO_ID           0x301


/******************************************************************************/
/* FUNCTION DECLARATIONS                                                      */
/******************************************************************************/

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

void TST_CAN_vidInit(void);
void TST_CAN_vidControllerBusOff(uint8 ControllerId);
void TST_CAN_vidControllerModeIndication(uint8 ControllerId,
                                         CanIf_ControllerModeType ControllerMode);
void TST_CAN_vidTxFrame(void);
void TST_CAN_vidReceiveMessage(uint8 u8Id, uint8* pu8Message);
void TST_CAN_vidSendMessage(uint8 u8Id, uint8* pu8Message);

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

#endif /* TST_CAN_H */

/*------------------------------- end of file --------------------------------*/
