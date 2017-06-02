/**********************************************************************************************************************/
/* !Layer           : HAL                                                                                             */
/* !Component       : TLF35584                                                                                        */
/* !Description     : TLF35584 safe supply device management                                                          */
/*                                                                                                                    */
/* !File            : TLF35584_Def.c                                                                                  */
/* !Description     : Data definition of TLF35584 component                                                           */
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

#include "Std_Types.h"
#include "TLF35584.h"

/**********************************************************************************************************************/
/* DATA DECLARATION                                                                                                   */
/**********************************************************************************************************************/

#define TLF35584_START_SEC_VAR_CLEARED_8BIT
#include "TLF35584_MemMap.h"

uint8 TLF35584_u8ChipStepUsed;
uint8 TLF35584_u8ErrorFrameCnt;
uint8 TLF35584_u8IndexFrame;
uint8 TLF35584_u8SpiTxFrameMaxNb;

#define TLF35584_STOP_SEC_VAR_CLEARED_8BIT
#include "TLF35584_MemMap.h"


#define TLF35584_START_SEC_VAR_CLEARED_16BIT
#include "TLF35584_MemMap.h"

uint16 TLF35584_au16SpiTxFrame[TLF35584_u8TX_FRAME_MAX_NB];
uint16 TLF35584_au16SpiRxFrame[TLF35584_u8TX_FRAME_MAX_NB];
uint16 TLF35584_au16SpiSleepModeFrame;

#define TLF35584_STOP_SEC_VAR_CLEARED_16BIT
#include "TLF35584_MemMap.h"

/*--------------------------------------------------- END OF FILE ----------------------------------------------------*/
