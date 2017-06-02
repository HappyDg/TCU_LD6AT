/**********************************************************************************************************************/
/* !Layer           : HAL                                                                                             */
/* !Component       : TLF35584                                                                                        */
/* !Description     : TLF35584 safe supply device management                                                          */
/*                                                                                                                    */
/* !File            : TLF35584.c                                                                                      */
/* !Description     : Send the init frames for TLF35584 configuration                                                 */
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
#include "Std_Limits.h"

#include "SPI.h"
#include "TLF35584.h"
#include "IOHAL.h"
#include "Dio.h"

#define TLF35584_START_SEC_CODE
#include "TLF35584_MemMap.h"

/**********************************************************************************************************************/
/* !FuncName    : TLF35584_vidInit                                                                                    */
/* !Description : Initialization of the TLF35584 variables and Start of SPI sequences                                 */
/*                                                                                                                    */
/* !LastAuthor  : L. Baglin                                                                                           */
/**********************************************************************************************************************/
void TLF35584_vidInit(uint8 u8TLF35584_StepUsed)
{
   uint8 u8LocalCnt;
   
   TLF35584_u8ErrorFrameCnt    = UINT8_MIN;
   TLF35584_u8IndexFrame       = UINT8_MIN;
   TLF35584_u8ChipStepUsed     = u8TLF35584_StepUsed;
   
   /* !Comment: Initialization of SPI Rx Buffer */
   for (u8LocalCnt = 0u; u8LocalCnt < TLF35584_u8TX_FRAME_MAX_NB; u8LocalCnt++)
   {
      TLF35584_au16SpiRxFrame[u8LocalCnt] = UINT16_MIN;
   }

   /* !Comment: Initialization of SPI Frames to Send */
   TLF35584_au16SpiTxFrame[0u] = TLF35584_u16UNLOCK_FRAME1;
   TLF35584_au16SpiTxFrame[1u] = TLF35584_u16UNLOCK_FRAME2;
   TLF35584_au16SpiTxFrame[2u] = TLF35584_u16UNLOCK_FRAME3;
   TLF35584_au16SpiTxFrame[3u] = TLF35584_u16UNLOCK_FRAME4;
   TLF35584_au16SpiTxFrame[4u] = TLF35584_u16DISABLE_WATCHDOGS;
   TLF35584_au16SpiTxFrame[6u] = TLF35584_u16LOCK_FRAME1;
   TLF35584_au16SpiTxFrame[7u] = TLF35584_u16LOCK_FRAME2;
   TLF35584_au16SpiTxFrame[8u] = TLF35584_u16LOCK_FRAME3;
   TLF35584_au16SpiTxFrame[9u] = TLF35584_u16LOCK_FRAME4;

   if (TLF35584_u8ChipStepUsed == TLF35584_u8CHIP_STEP_B)
   {
       /* !Comment: The TLF35584 is a Step B */
       TLF35584_au16SpiTxFrame[5u]  = TLF35584_u16STEP_B_DISA_ERR_MON;
       TLF35584_au16SpiTxFrame[10u] = TLF35584_u16STEP_B_CFG1_NORMAL;
       TLF35584_au16SpiTxFrame[11u] = TLF35584_u16STEP_B_CFG2_NORMAL;
       TLF35584_u8SpiTxFrameMaxNb   = TLF35584_u8FRAME_NB_INIT_STEP_B;
   }
   else
   {
       /* !Comment: The TLF35584 is a Step A */
       TLF35584_au16SpiTxFrame[5u]  = TLF35584_u16STEP_A_DISA_ERR_MON;
       TLF35584_au16SpiTxFrame[10u] = TLF35584_u16STEP_A_CFG_NORMAL;
       TLF35584_u8SpiTxFrameMaxNb   = TLF35584_u8FRAME_NB_INIT_STEP_A;
   }

   /* !Comment: initiates SPI sequence */
   (void)Spi_WriteIB(SpiConf_SpiChannel_TLF35584_CH,
                     (const uint8 *)&TLF35584_au16SpiTxFrame[UINT8_MIN]);
   (void)Spi_AsyncTransmit(SpiConf_SpiSequence_TLF35584_SEQ);
}
/**********************************************************************************************************************/
/* !FuncName    : TLF35584_vidSleepModeActive                                                                                    */
/* !Description : To go to sleep mode                                  */
/*                                                                                                                    */
/* !LastAuthor  : Liping.Liu                                                                                           */
/**********************************************************************************************************************/
void TLF35584_vidSleepModeActive(uint8 u8TLF35584_StepUsed)
{
   uint8 u8LocalCnt;
   
   TLF35584_u8ErrorFrameCnt    = UINT8_MIN;
   TLF35584_u8IndexFrame       = UINT8_MIN;
   TLF35584_u8ChipStepUsed     = u8TLF35584_StepUsed;
   
   /* !Comment: Initialization of SPI Rx Buffer */
   for (u8LocalCnt = 0u; u8LocalCnt < TLF35584_u8TX_FRAME_MAX_NB; u8LocalCnt++)
   {
      TLF35584_au16SpiRxFrame[u8LocalCnt] = UINT16_MIN;
   }

   /* !Comment: Initialization of SPI Frames to Send */
   TLF35584_au16SpiTxFrame[0u] = TLF35584_u16STEP_B_CFG1_STANDBY;
   TLF35584_au16SpiTxFrame[1u] = TLF35584_u16STEP_B_CFG2_STANDBY;
   
   TLF35584_u8SpiTxFrameMaxNb   = 2;

   /* !Comment: initiates SPI sequence */
   (void)Spi_WriteIB(SpiConf_SpiChannel_TLF35584_CH,
                     (const uint8 *)&TLF35584_au16SpiTxFrame[UINT8_MIN]);
   (void)Spi_AsyncTransmit(SpiConf_SpiSequence_TLF35584_SEQ);
}
/**********************************************************************************************************************/
/* !FuncName    : TLF35584_vidSpiEndNotification                                                                      */
/* !Description : End of SEQUENCE notification used to end the remaining                                              */
/*                                                                                                                    */
/* !LastAuthor  : L. Baglin                                                                                           */
/**********************************************************************************************************************/
void TLF35584_vidSpiEndNotification(void)
{
   Std_ReturnType udtLocalRxStatus;

   boolean bLocalEnaSpiTxFrame = TRUE;

   udtLocalRxStatus = Spi_ReadIB(SpiConf_SpiChannel_TLF35584_CH,
                                 (uint8 *)&TLF35584_au16SpiRxFrame[TLF35584_u8IndexFrame]);

   if (  (udtLocalRxStatus == E_OK)
      && (TLF35584_au16SpiRxFrame[TLF35584_u8IndexFrame] == TLF35584_au16SpiTxFrame[TLF35584_u8IndexFrame]))
   {
      TLF35584_u8IndexFrame++;
      if (  (TLF35584_u8IndexFrame == TLF35584_u8FRAME_NB_BEFORE_TEMPO)
         || (TLF35584_u8IndexFrame == TLF35584_u8SpiTxFrameMaxNb))
      {
         /* No New Frame shall be sent */
         bLocalEnaSpiTxFrame = FALSE;
      }
   }
   else
   {
      TLF35584_u8ErrorFrameCnt++;
      bLocalEnaSpiTxFrame = TRUE;
      /* !Comment: Sending of the same SPI sequence */
   }

   if (bLocalEnaSpiTxFrame != FALSE)
   {
      (void)Spi_WriteIB(SpiConf_SpiChannel_TLF35584_CH,
                        (const uint8 *)&TLF35584_au16SpiTxFrame[TLF35584_u8IndexFrame]);
      (void)Spi_AsyncTransmit(SpiConf_SpiSequence_TLF35584_SEQ);
   }
}

/**********************************************************************************************************************/
/* !FuncName    : TLF35584_vidManagement                                                                              */
/* !Description : Send the "Go to normal mode" sequences                                                              */
/*                                                                                                                    */
/* !LastAuthor  : L. Baglin                                                                                           */
/**********************************************************************************************************************/

void TLF35584_vidManagement(void)
{
   if (TLF35584_u8IndexFrame == TLF35584_u8FRAME_NB_BEFORE_TEMPO)
   {
      (void)Spi_WriteIB(SpiConf_SpiChannel_TLF35584_CH,
                        (const uint8 *)&TLF35584_au16SpiTxFrame[TLF35584_u8IndexFrame]);
      (void)Spi_AsyncTransmit(SpiConf_SpiSequence_TLF35584_SEQ);
   }


	if(Dio_ReadChannel(DioConf_DioChannel_M_IGN_INPUT) == 0) 
	{
		TLF35584_vidSleepModeActive(TLF35584_u8CHIP_STEP_B);
	}

#if 0    //cyg
   if (Dio_ReadChannel(DioConf_DioChannel_EN_PWMIC_PSU) == STD_ON)
   {
      //TLF35584_vidSleepModeActive(TLF35584_u8CHIP_STEP_B);
   }
#endif
}

#define TLF35584_STOP_SEC_CODE
#include "TLF35584_MemMap.h"

/*--------------------------------------------------- END OF FILE ----------------------------------------------------*/
