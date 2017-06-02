/**********************************************************************************************************************/
/* !Layer           : HAL                                                                                             */
/* !Component       : TLF35584                                                                                        */
/* !Description     : TLF35584 safe supply device management                                                          */
/*                                                                                                                    */
/* !File            : TLF35584.h                                                                                      */
/* !Description     : Header file for TLF35584 component                                                              */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/

#ifndef TLF35584_H
#define TLF35584_H

#include "Std_Types.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
#define TLF35584_u8CHIP_STEP_A            00u
#define TLF35584_u8CHIP_STEP_B            01u

#define TLF35584_u8FRAME_NB_BEFORE_TEMPO  10u
#define TLF35584_u8FRAME_NB_INIT_STEP_A   11u
#define TLF35584_u8FRAME_NB_INIT_STEP_B   12u
#define TLF35584_u8TX_FRAME_MAX_NB        12u

#define TLF35584_u16UNLOCK_FRAME1         0x8756u
#define TLF35584_u16UNLOCK_FRAME2         0x87DEu
#define TLF35584_u16UNLOCK_FRAME3         0x86ADu
#define TLF35584_u16UNLOCK_FRAME4         0x8625u
#define TLF35584_u16DISABLE_WATCHDOGS     0x8D27u
#define TLF35584_u16STEP_A_DISA_ERR_MON   0x8811u
#define TLF35584_u16STEP_B_DISA_ERR_MON   0x8A01u
#define TLF35584_u16LOCK_FRAME1           0x87BEu
#define TLF35584_u16LOCK_FRAME2           0x8668u
#define TLF35584_u16LOCK_FRAME3           0x877Du
#define TLF35584_u16LOCK_FRAME4           0x8795u
#define TLF35584_u16STEP_A_CFG_NORMAL     0x9DD5u
#define TLF35584_u16STEP_B_CFG1_NORMAL    0xABD5u
#define TLF35584_u16STEP_B_CFG2_NORMAL    0xAC2Bu

#define TLF35584_u16STEP_B_CFG1_STANDBY   0xABD9u
#define TLF35584_u16STEP_B_CFG2_STANDBY   0xAC27u

/**********************************************************************************************************************/
/* DATA DECLARATION                                                                                                   */
/**********************************************************************************************************************/

#define TLF35584_START_SEC_VAR_CLEARED_8BIT
#include "TLF35584_MemMap.h"

extern uint8 TLF35584_u8ChipStepUsed;
extern uint8 TLF35584_u8ErrorFrameCnt;
extern uint8 TLF35584_u8IndexFrame;
extern uint8 TLF35584_u8SpiTxFrameMaxNb;

#define TLF35584_STOP_SEC_VAR_CLEARED_8BIT
#include "TLF35584_MemMap.h"


#define TLF35584_START_SEC_VAR_CLEARED_16BIT
#include "TLF35584_MemMap.h"

extern uint16 TLF35584_au16SpiTxFrame[TLF35584_u8TX_FRAME_MAX_NB];
extern uint16 TLF35584_au16SpiRxFrame[TLF35584_u8TX_FRAME_MAX_NB];
extern uint16 TLF35584_au16SpiSleepModeFrame;

#define TLF35584_STOP_SEC_VAR_CLEARED_16BIT
#include "TLF35584_MemMap.h"


/**********************************************************************************************************************/
/* FUNCTIONS DECLARATION                                                                                              */
/**********************************************************************************************************************/

#define TLF35584_START_SEC_CODE
#include "TLF35584_MemMap.h"

extern void TLF35584_vidInit(uint8 u8TLF35584_StepUsed);
extern void TLF35584_vidSpiEndNotification(void);
extern void TLF35584_vidManagement(void);
extern void TLF35584_vidSleepModeActive(uint8 u8TLF35584_StepUsed);

#define TLF35584_STOP_SEC_CODE
#include "TLF35584_MemMap.h"

#endif /* TLF35584_H */

/*--------------------------------------------------- END OF FILE ----------------------------------------------------*/
