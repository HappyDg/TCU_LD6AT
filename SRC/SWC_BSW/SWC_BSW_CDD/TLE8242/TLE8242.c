/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           :                                                                                            */
/*                                                                                                                    */
/* !Component       :                                                                                             */
/* !Description     :     unit                                                                                    */
/*                                                                                                                    */
/* !Module          :                                                                                             */
/* !Description     :                                                                           */
/*                                                                                                                    */
/* !File            : TLE8242.c                                                                                  */
/*                                                                                                                    */
/* !Target          :                                                                                      */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* 1 /                                                                                    */
/* 2 /                                                                                        */
/* 3 /                                                                                           */
/* 4 /                                                                                           */
/* 5 /                                                                                          */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* Archive::                        */
/* Revision::   0.1                                                                                                */
/* Author::   gsun5                               Date::   Jan 18, 2017                               */
/**********************************************************************************************************************/
#include "Std_Types.h"
#include "Std_Limits.h"

#include "SPI.h"
#include "dio.h"
#include "tle8242_i.h"
#include "gtm.h"
#include "BSW.h"
#include "MAIN_L.h"


/************************************************************************************************************************
 *
 * Static variable.
 *
 *
 * ************************************************************************************************************************/
#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

static uint8 TLE8242CurReadChanNum[NUMBER_OF_TLE8242];
uint16 TLE8242CurReadCnt[NUMBER_OF_TLE8242][8];

#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
/**********************************************************************************************************************/
/* !FuncName    : TLE8242_VidInit                                                                                    */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
#define TLE8242_START_SEC_CODE
#include "MemMap.h"
void TLE8242_VidInit(void)
{
    /*Trim function ini*/
	Trim_InitGainAndOffset();
	
	TLE8242_au32InitTxBuff[0][0].data = (uint32)TLE8242_au32SpiTx[0].ControlMethodandFaultMaskConfiguration.data;
    TLE8242_au32InitTxBuff[0][1].data = (uint32)TLE8242_au32SpiTx[0].DiagnosticConfigurationchannel[0].data;
    TLE8242_au32InitTxBuff[0][2].data = (uint32)TLE8242_au32SpiTx[0].DiagnosticConfigurationchannel[1].data;
    TLE8242_au32InitTxBuff[0][3].data= (uint32)TLE8242_au32SpiTx[0].PWMOffsetchannel0_3.data;
    TLE8242_au32InitTxBuff[0][4].data = (uint32)TLE8242_au32SpiTx[0].PWMOffsetchannel4_7.data;

#if NUMBER_OF_TLE8242> 1
/*     Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const uint8 *) &TLE8242_au32SpiTx[1].ControlMethodandFaultMaskConfiguration);
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const uint8 *) &TLE8242_au32SpiTx[1].DiagnosticConfigurationchannel[0]);
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const uint8 *) &TLE8242_au32SpiTx[1].DiagnosticConfigurationchannel[1]);
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const uint8 *) &TLE8242_au32SpiTx[1].PWMOffsetchannel0_3);
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const uint8 *) &TLE8242_au32SpiTx[1].PWMOffsetchannel4_7);
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const uint8 *) &dummy); */
#endif

    Dio_WriteChannel(DioConf_DioChannel_M_TLE8242_ENA, STD_ON);
#if NUMBER_OF_TLE8242> 1
    //Dio_WriteChannel(DioConf_DioChannel_TLE8242_ENA_2, STD_ON);
#endif

    Gtm_SetTomCounterCn0(0, 1, 0);//Phase_sync1
#if NUMBER_OF_TLE8242> 1
    //Gtm_SetAtomCounterCn0(0, 0, 0);//Phase_sync2
#endif
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_INIT_CH, (const uint8 *) TLE8242_au32InitTxBuff[0]);
    Spi_AsyncTransmit(SpiConf_SpiSequence_TLE8242_INIT_SEQ);
}

/**********************************************************************************************************************/
/* !FuncName    : TLE8242_VidConvMsgInfo                                                                                    */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_VidConvMsgInfo(Tle8242DummyMsgID* data, const uint8 length, const uint8 chip_index)
{
    uint8 i, channel;
    uint32 * addr, addr1;

    addr1 = ((uint32*) (&(TLE8242_au32SpiRx[chip_index])));
    for (i = 0; i < length; i++)
    {
        if (ReadGenericFlagMsgID == data[i].bits.MsgID)
    {
            //Todo, here should not multiply by 4, because for a uint32 type pinter, the pointer add by one, the address should add by 4, this should be done by compiler.
            // but could not find the root cause, will be solved later.
            addr = addr1 + ReadGenericFlagMSgOFFSET * 4;
        }
        else if (data[i].bits.MsgID < MAX_VALID_MSG_ID)
        {
            addr = addr1 + data[i].bits.MsgID * 4;
        }
        else
        {
        }
        memcpy(addr, &data[i], 4);
    }
}


/**********************************************************************************************************************/
/* !FuncName    : TLE8242_VidCtrlPreManagement                                                                                    */
/* !Description :                                  */
/*  This function will parse the reponse spi message back, and put it to the right place.                               */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_VidParseResponse(void)
{
    uint8 i , channel, index, spi_cha = SpiConf_SpiChannel_TLE8242_1_CTRL_CH;
    Std_ReturnType udtLocalRxStatus;
    static init_channel_read = 0;
    uint8 valid, valid1;


    for ( i = 0; i < NUMBER_OF_TLE8242; ++i)
    {
        Spi_ReadIB(SpiConf_SpiChannel_TLE8242_1_INIT_CH+i, (uint8 *) TLE8242_au32InitRxBuff[i]);
        Spi_ReadIB(SpiConf_SpiChannel_TLE8242_1_CTRL_CH+i, (uint8 *) TLE8242_au32CtrlRxBuff[i]);
        Spi_ReadIB(SpiConf_SpiChannel_TLE8242_1_DIAG_CH+i, (uint8 *) TLE8242_au32DiagRxBuff[i]);
        TLE8242_VidConvMsgInfo(TLE8242_au32InitRxBuff[i], TLE8242_au8_channel_buff_deepth_cfg[i], i);
        TLE8242_VidConvMsgInfo(TLE8242_au32CtrlRxBuff[i], TLE8242_au8_channel_buff_deepth_cfg[i+1], i);
        TLE8242_VidConvMsgInfo(TLE8242_au32DiagRxBuff[i], TLE8242_au8_channel_buff_deepth_cfg[i+2], i);
   
        // As for TLE8242, only can read one channel one time, can not send 8 frames to get all the current feedback, you will get nothing.
        //
        valid = TLE8242GetCurValid(TLE8242CurReadChanNum[i], AvgCurrent);
        valid1 = TLE8242GetCurValid(TLE8242CurReadChanNum[i], MaxCurrent);

        if (valid)
        {
            TLE8242AvgCurma[TLE8242CurReadChanNum[i]] = TLE8242GetCurrentFeedback(TLE8242CurReadChanNum[i], AvgCurrent);
        }
        if (valid1)
        {
            TLE8242MaxCurma[TLE8242CurReadChanNum[i]] = TLE8242GetCurrentFeedback(TLE8242CurReadChanNum[i], MaxCurrent);
            TLE8242MinCurma[TLE8242CurReadChanNum[i]] = TLE8242GetCurrentFeedback(TLE8242CurReadChanNum[i], MinCurrent);
        }
        //Todo this should be a calbration.
        if (valid1 || valid || TLE8242CurReadCnt[i][TLE8242CurReadChanNum[i]] > 100)
        {
            TLE8242CurReadCnt[i][TLE8242CurReadChanNum[i]] = 0;
            TLE8242CurReadChanNum[i]++;

            if (TLE8242CurReadChanNum[i] > (TLE8242_au8ChanNumPerChip[i]-1))
            {
                TLE8242CurReadChanNum[i] = 0;
            }
        }
   }




}
/**********************************************************************************************************************/
/* !FuncName    : TLE8242_vidFaultDet                                                                                    */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidFaultDet(void)
{

}

/**********************************************************************************************************************/
/* !FuncName    : TLE8242_vidCtrlManagement                                                                                    */
/* !Description :                                  */
/* This function will update the control message and send to tle8242, should be called at the end of 1ms.
 * For TLE8242, if no parameter change, we should not send any write commands, for now we choose internal buffer,
 * so we just send message #0, later will try to send the read command if no change for this parameter.
 *             */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidCtrlManagement(void)
{
    uint8 i,j, message_index[2] = { 0, 0 };
    uint8 chip_index, channel_index;
    uint8 conf_changed[NUMBER_OF_TLE8242] = { 0
#if NUMBER_OF_TLE8242 > 1
            , 0
#endif
};

    if(BSW_bTle8242Flag)
	{
		for (i = 0; i < NUMBER_OF_TLE8242_CHANNEL; ++i)
		{
			chip_index = i / 8;
			channel_index = i % 8;
			TLE8242SetPWMFrq(i, TLE8242PWMFrq[i]);
			TLE8242_au32CtrlTxBuff[chip_index][message_index[chip_index]++].data = (uint32)TLE8242_au32SpiTx[chip_index].MainPeriodSet[channel_index].data;

			TLE8242SetKP(i, TLE8242KP[i]);
			TLE8242SetKI(i, TLE8242KI[i]);
			TLE8242_au32CtrlTxBuff[chip_index][message_index[chip_index]++].data = (uint32)TLE8242_au32SpiTx[chip_index].ControlVariableSetKPandKI[channel_index].data;

			TLE8242SetDitherFrq(i, TLE8242DitherFreq[i]);
			TLE8242_au32CtrlTxBuff[chip_index][message_index[chip_index]++].data = (uint32)TLE8242_au32SpiTx[chip_index].DitherPeriodSet[channel_index].data;

			if (DirectPWMMode == TLE8242OpenLoopC[i])
			{
				TLE8242SetControlMode(i, DirectPWM);
				TLE8242SetPWMDutyCycle(i, TLE8242DutyCycleC[i]);
				TLE8242_au32CtrlTxBuff[chip_index][message_index[chip_index]++].data = (uint32)TLE8242_au32SpiTx[chip_index].PWMDutyCycle[channel_index].data;
			}
			else
			{
				TLE8242SetControlMode(i, CurrentControl);

				TLE8242SetCurrentTarget(i, TLE8242Target[i]);
				TLE8242SetDitherAMPL(i, TLE8242DitherAmpl[i]);
				TLE8242_au32CtrlTxBuff[chip_index][message_index[chip_index]++].data = (uint32)TLE8242_au32SpiTx[chip_index].CurrentandDitherAmplitudeSet[channel_index].data;
			}

		
		}
	}
	else
	{
		
	}


    for (i = 0; i < NUMBER_OF_TLE8242; ++i)
    {
        TLE8242_au32CtrlTxBuff[i][message_index[i]++].data = (uint32)TLE8242_au32SpiTx[i].MaxMinCurrentRead[TLE8242CurReadChanNum[i]].data;
        TLE8242_au32CtrlTxBuff[i][message_index[i]++].data = (uint32)TLE8242_au32SpiTx[i].AverageCurrentReadOverDitherPeriod[TLE8242CurReadChanNum[i]].data;
        if (1 == conf_changed[i])
        {
            TLE8242_au32CtrlTxBuff[i][message_index[i]++].data = (uint32) TLE8242_au32SpiTx[i].ControlMethodandFaultMaskConfiguration.data;
        }
        TLE8242CurReadCnt[i][TLE8242CurReadChanNum[i]]++;

    }
    for (j = message_index[0]; j < MAX_FRAME_NUM_OF_CTRL_CHANNEL_1; j++)
    {
        TLE8242_au32CtrlTxBuff[0][j].data = 0;
    }
/*     for (j = message_index[1]; j < MAX_FRAME_NUM_OF_CTRL_CHANNEL_2; j++)
    {
        TLE8242_au32CtrlTxBuff[1][j].data = 0;
    } */


    // TODO need one more buffer for setting the control mode
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_CTRL_CH, (const uint8 *) TLE8242_au32CtrlTxBuff[0]);

#if NUMBER_OF_TLE8242> 1
    //TLE8242_au32CtrlTxBuff[1][message_index[1]++].data = (uint32)TLE8242_au32SpiTx[1].ControlMethodandFaultMaskConfiguration.data;
    //Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_CTRL_CH, (const uint8 *) TLE8242_au32CtrlTxBuff[1]);
#endif

    if(TLE8242_au32CtrlTxBuff[0][0].bits.MsgID != 0)
   {
        Spi_AsyncTransmit(SpiConf_SpiSequence_TLE8242_CTRL_SEQ);
   }
}
/**********************************************************************************************************************/
/* !FuncName    : TLE8242_vidDiagManagement                                                                                    */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidDiagManagement(void)
{

    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_DIAG_CH, (const uint8 *) &TLE8242_au32DiagTxBuff[0]);

#if NUMBER_OF_TLE8242> 1
    //Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_DIAG_CH, (const uint8 *) &TLE8242_au32DiagTxBuff[1]);
#endif

    Spi_AsyncTransmit(SpiConf_SpiSequence_TLE8242_DIAG_SEQ);
}

#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"