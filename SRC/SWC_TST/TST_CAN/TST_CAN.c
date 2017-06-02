/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_CAN                                                 */
/* !Description     : Test of CAN component                                   */
/*                                                                            */
/* !File            : TST_CAN.c                                               */
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

#include "Std_Types.h"

#include "TST_CAN.h"

#include "CAN.h"
#include "TSTCAL.h"
#include "TST_CAN.h"

#define TST_START_SEC_TST_VAR
#include "TST_MemMap.h"

uint8  TST_CAN_u8ModeIndicationId;
uint8  TST_CAN_u8TxFrameId;
uint32 TST_CAN_u32BusOffCount;
uint32 TST_CAN_u32CanRxDlc;
uint32 TST_CAN_u32CanRxId;
uint32 TST_CAN_u32CanTxId;
uint32 TST_CAN_u32RxHrh;
uint32 TST_CAN_u32RxConfirmCount;
uint32 TST_CAN_u32TxConfirmCount;
uint32 TST_CAN_u32ModeIndicationMode;
uint8  TST_CAN_au8RxMessageData[8];
uint8  TST_CAN_au8TxMessageData[64];

/* CAN Frame PDU Info With Standard Identifier */
Can_PduType TST_CAN_udtPduInfo[8];

#define TST_STOP_SEC_TST_VAR
#include "TST_MemMap.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"


/******************************************************************************/
/* !FuncName    : TST_CAN_vidInit                                             */
/* !Description : Initialises the TST_CAN data                                */
/*                                                                            */
/* !LastAuthor  : M. Sabry                                                    */
/******************************************************************************/
void TST_CAN_vidInit(void)
{
   uint8          u8LocalCounter;
   uint16         u16LocalBaudrate;
   Std_ReturnType udtLocalStatus;

   TST_CAN_udtPduInfo[0].swPduHandle = 0;
   TST_CAN_udtPduInfo[0].length      = 8;
   TST_CAN_udtPduInfo[0].id          = 0x200;
   TST_CAN_udtPduInfo[0].sdu         = &TST_CAN_au8TxMessageData[0];

   TST_CAN_udtPduInfo[1].swPduHandle = 1;
   TST_CAN_udtPduInfo[1].length      = 8;
   TST_CAN_udtPduInfo[1].id          = 0x201;
   TST_CAN_udtPduInfo[1].sdu         = &TST_CAN_au8TxMessageData[8];

   TST_CAN_udtPduInfo[2].swPduHandle = 2;
   TST_CAN_udtPduInfo[2].length      = 8;
   TST_CAN_udtPduInfo[2].id          = 0x1FF;
   TST_CAN_udtPduInfo[2].sdu         = &TST_CAN_au8TxMessageData[16];

   TST_CAN_udtPduInfo[3].swPduHandle = 3;
   TST_CAN_udtPduInfo[3].length      = 8;
   TST_CAN_udtPduInfo[3].id          = 0x302;
   TST_CAN_udtPduInfo[3].sdu         = &TST_CAN_au8TxMessageData[24];

   TST_CAN_udtPduInfo[4].swPduHandle = 4;
   TST_CAN_udtPduInfo[4].length      = 8;
   TST_CAN_udtPduInfo[4].id          = 0x55;
   TST_CAN_udtPduInfo[4].sdu         = &TST_CAN_au8TxMessageData[32];

   TST_CAN_udtPduInfo[5].swPduHandle = 5;
   TST_CAN_udtPduInfo[5].length      = 8;
   TST_CAN_udtPduInfo[5].id          = 0x66;
   TST_CAN_udtPduInfo[5].sdu         = &TST_CAN_au8TxMessageData[40];

   TST_CAN_udtPduInfo[6].swPduHandle = 6;
   TST_CAN_udtPduInfo[6].length      = 8;
   TST_CAN_udtPduInfo[6].id          = 0x77;
   TST_CAN_udtPduInfo[6].sdu         = &TST_CAN_au8TxMessageData[48];

   TST_CAN_udtPduInfo[7].swPduHandle = 7;
   TST_CAN_udtPduInfo[7].length      = 8;
   TST_CAN_udtPduInfo[7].id          = 0x88;
   TST_CAN_udtPduInfo[7].sdu         = &TST_CAN_au8TxMessageData[56];
   TST_CAN_u8TxFrameId            = 4; // Tx frames on CAN 1 are 4, 5, 6 nd 7
   TST_CAN_u8ModeIndicationId     = 0;
   TST_CAN_u32BusOffCount         = 0;
   TST_CAN_u32CanRxDlc            = 0;
   TST_CAN_u32CanRxId             = 0;
   TST_CAN_u32CanTxId             = 0;
   TST_CAN_u32ModeIndicationMode  = 0;
   TST_CAN_u32RxHrh               = 0;
   TST_CAN_u32RxConfirmCount      = 0;
   TST_CAN_u32TxConfirmCount      = 0;

   for (u8LocalCounter = 0; u8LocalCounter < 8; u8LocalCounter++)
   {
      TST_CAN_au8RxMessageData[u8LocalCounter] = 0x00;
   }
   for (u8LocalCounter = 0; u8LocalCounter < 64; u8LocalCounter++)
   {
      TST_CAN_au8TxMessageData[u8LocalCounter] = u8LocalCounter;
   }

   /* Initialize CAN 0 Baudrate */
   if (TST_CAN_ku8FirstCanBaudrate == 1)
   {
      u16LocalBaudrate = 500;
   }
   else
   {
      u16LocalBaudrate = 1000;
   }

   /* Put the CAN controller 0 into stopped state */
   /* Can_SetControllerMode(Can_17_MCanPConf_CanController_CanController_0,
                         CAN_T_STOP);
 */
   /* check Baudrate 1Mbps for CanController 0 */
  /*  udtLocalStatus = Can_CheckBaudrate
                       (Can_17_MCanPConf_CanController_CanController_0,
                        u16LocalBaudrate);
   if (E_OK == udtLocalStatus)
   {
 */      /* If baudrate is configured then change baudrate */
 /*      udtLocalStatus = Can_ChangeBaudrate
                          (Can_17_MCanPConf_CanController_CanController_0,
                           u16LocalBaudrate);
   }
  */ 
   /* Put the CAN controllers into started state */
  /*  Can_SetControllerMode(Can_17_MCanPConf_CanController_CanController_0,
                         CAN_T_START);
 */
   /* Initialize CAN 1 Baudrate */
  /*  if (TST_CAN_ku8SecondCanBaudrate == 1)
   {
      u16LocalBaudrate = 500;
   }
   else
   {
      u16LocalBaudrate = 1000;
   } */

   /* Put the CAN controller 1 into stopped state */
  /*  Can_SetControllerMode(Can_17_MCanPConf_CanController_CanController_1,
                         CAN_T_STOP);

 */   /* check Baudrate 1Mbps for CanController_0 */
  /*  udtLocalStatus = Can_CheckBaudrate
                       (Can_17_MCanPConf_CanController_CanController_1,
                        u16LocalBaudrate);
   if (E_OK == udtLocalStatus)
   {
   */    /* If baudrate is configured then change baudrate */
   /*    udtLocalStatus = Can_ChangeBaudrate
                          (Can_17_MCanPConf_CanController_CanController_1,
                           u16LocalBaudrate);
   }
   */
   /* Put the CAN controllers into started state */
   /* Can_SetControllerMode(Can_17_MCanPConf_CanController_CanController_1,
                         CAN_T_START);
 */
}

/******************************************************************************/
/* !FuncName    : TST_CAN_vidControllerBusOff                                 */
/* !Description : Bus Off Callback function                                   */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_CAN_vidControllerBusOff(uint8 ControllerId)
{
   COMPILER_UNUSED_PARAMETER(ControllerId);
   TST_CAN_u32BusOffCount++;
}

/******************************************************************************/
/* !FuncName    : TST_CAN_vidControllerModeIndication                         */
/* !Description : Controller Mode Indication Callback function                */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_CAN_vidControllerModeIndication(uint8 ControllerId,
                                        CanIf_ControllerModeType ControllerMode)
{
   TST_CAN_u8ModeIndicationId    = ControllerId;
   TST_CAN_u32ModeIndicationMode = ControllerMode;
}

/******************************************************************************/
/* !FuncName    : TST_CAN_vidTxFrame                                          */
/* !Description : Tx Frame function                                           */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_CAN_vidTxFrame(void)
{
   uint8 u8LocalCounter;
   uint8 u8LocalByteOffset;

   Can_17_MCanP_Write(TST_CAN_u8TxFrameId + 2, &TST_CAN_udtPduInfo[TST_CAN_u8TxFrameId]);

   TST_CAN_u8TxFrameId++;
   if (TST_CAN_u8TxFrameId >= 8)
   {
      TST_CAN_u8TxFrameId = 4;
   }

   u8LocalByteOffset = TST_CAN_u8TxFrameId * 8;

   for (u8LocalCounter = 0; u8LocalCounter < 8; u8LocalCounter++)
   {
      TST_CAN_au8TxMessageData[u8LocalByteOffset + u8LocalCounter]++;
   }
}

/******************************************************************************/
/* !FuncName    : TST_CAN_vidReceiveMessage                                   */
/* !Description : CCP Receive Frame function                                  */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_CAN_vidReceiveMessage(uint8 u8Id, uint8* pu8Message)
{
   uint8 u8LocalByteIndex;

   COMPILER_UNUSED_PARAMETER(u8Id);

   for (u8LocalByteIndex = 0; u8LocalByteIndex < 8; u8LocalByteIndex++)
   {
      pu8Message[u8LocalByteIndex] = TST_CAN_au8RxMessageData[u8LocalByteIndex];
   }
}

/******************************************************************************/
/* !FuncName    : TST_CAN_vidSendMessage                                      */
/* !Description : CCP Send Frame function                                     */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_CAN_vidSendMessage(uint8 u8Id, uint8* pu8Message)
{
   uint8 u8LocalByteIndex;
   uint8 u8LocalOffset;

   u8LocalOffset = u8Id * 8;

   for (u8LocalByteIndex = 0; u8LocalByteIndex < 8; u8LocalByteIndex++)
   {
      TST_CAN_au8TxMessageData[u8LocalOffset + u8LocalByteIndex] =
         pu8Message[u8LocalByteIndex];
   }
   Can_17_MCanP_Write(u8Id + 2, &TST_CAN_udtPduInfo[u8Id]);
}

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

/*------------------------------- end of file --------------------------------*/
