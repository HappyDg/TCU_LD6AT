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


#include "Spi.h"
#include "Dio.h"
#include "Gtm.h"

#include "TLE8242_interface.h"
#include "TLE8242_def.h"
#include "TLE8242.h"

#include "Trim_8242.h"
#include "Trim_8242_App.h"
#include "TLE8242_cfg.h"

/******************************************************************************/
/* MACRO DEFINITION CHECK                                                   */
/******************************************************************************/
#ifndef TLE8242_u8MAX_CH_NR
#error "TLE8242_u8MAX_CH_NR should be defined."
#endif
#ifndef TLE8242_u8CH_NR
#error "TLE8242_u8CH_NR should be defined."
#endif
#ifndef DioConf_DioChannel_M_TLE8242_ENA
#error "DioConf_DioChannel_M_TLE8242_ENA should be defined."
#endif

#if TLE8242_u8CH_NR> 1

#ifndef DioConf_DioChannel_TLE8242_ENA_2
#error "DioConf_DioChannel_TLE8242_ENA_2 should be defined."
#endif
#ifndef SpiConf_SpiChannel_TLE8242_2_DIAG_CH
#error "TLE8242_u8_MAX_VALID_MSG_ID should be defined."
#endif
#ifndef SpiConf_SpiChannel_TLE8242_2_CTRL_CH
#error "SpiConf_SpiChannel_TLE8242_2_CTRL_CH should be defined."
#endif
#ifndef SpiConf_SpiChannel_TLE8242_2_DIAG_CH
#error "TLE8242_u8_MAX_VALID_MSG_ID should be defined."
#endif

#endif

#ifndef SpiConf_SpiSequence_TLE8242_INIT_SEQ
#error "SpiConf_SpiSequence_TLE8242_INIT_SEQ should be defined."
#endif
#ifndef TLE8242_u8_READ_GEN_FLG_MSG_OFFS
#error "TLE8242_u8_READ_GEN_FLG_MSG_OFFS should be defined."
#endif
#ifndef TLE8242_u8_MAX_VALID_MSG_ID
#error "TLE8242_u8_MAX_VALID_MSG_ID should be defined."
#endif
#ifndef SpiConf_SpiChannel_TLE8242_1_CTRL_CH
#error "SpiConf_SpiChannel_TLE8242_1_CTRL_CH should be defined."
#endif
#ifndef SpiConf_SpiChannel_TLE8242_1_DIAG_CH
#error "TLE8242_u8_MAX_VALID_MSG_ID should be defined."
#endif
#ifndef SpiConf_SpiChannel_TLE8242_1_DIAG_CH
#error "TLE8242_u8_MAX_VALID_MSG_ID should be defined."
#endif

#ifndef SpiConf_SpiSequence_TLE8242_CTRL_SEQ
#error "SpiConf_SpiSequence_TLE8242_INIT_SEQ should be defined."
#endif
#ifndef SpiConf_SpiSequence_TLE8242_DIAG_SEQ
#error "SpiConf_SpiSequence_TLE8242_INIT_SEQ should be defined."
#endif


#ifndef TLE8242_u8MAX_NR_FLT
#error "TLE8242_u8MAX_NR_FLT should be defined."
#endif




#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

/************************************************************************************************************************
 *
 * Static variable.
 *
 *
 * ************************************************************************************************************************/

static float32 TLE8242_saf32CnrtTarOld[TLE8242_u8MAX_CH_NR];
static float32 TLE8242_saf32PwmFrqOld[TLE8242_u8MAX_CH_NR];
static uint16 TLE8242_sau16KPOld[TLE8242_u8MAX_CH_NR];
static uint16 TLE8242_sau16KIOld[TLE8242_u8MAX_CH_NR];
static float32 TLE8242_saf32DitherAmplOld[TLE8242_u8MAX_CH_NR];
static float32 TLE8242_saf32DitherFrqOld[TLE8242_u8MAX_CH_NR];
static float32 TLE8242_saf32DutyCycleOld[TLE8242_u8MAX_CH_NR];
static uint8 TLE8242_su8CtrlModOld[TLE8242_u8MAX_CH_NR];

static uint8 TLE8242_su8CurReadChNr[TLE8242_u8CH_NR];
static uint16 TLE8242_su8CurReadCnt[TLE8242_u8CH_NR][8];

static uint8 TLE8242_su8CurVld[TLE8242_u8CH_NR][2];
uint16 TLE8242_su16FltSts[TLE8242_u8MAX_CH_NR][6];
// for ctrl message.
static uint8 TLE8242_su8MsgSndCnt[TLE8242_u8CH_NR];

#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
#define TLE8242_START_SEC_CODE
#include "MemMap.h"
/**********************************************************************************************************************/
/* !FuncName    : TLE8242_vidInit                                                                                    */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidInit(void)
{
  	/*Trim function ini*/
	Trim_InitGainAndOffset();
  
    TLE8242_astInitTxBuf[0][0].u32Data = (uint32)TLE8242_astSpiTx[0].ControlMethodandFaultMaskConfiguration.u32Data;
    TLE8242_astInitTxBuf[0][1].u32Data = (uint32)TLE8242_astSpiTx[0].DiagnosticConfigurationchannel[0].u32Data;
    TLE8242_astInitTxBuf[0][2].u32Data = (uint32)TLE8242_astSpiTx[0].DiagnosticConfigurationchannel[1].u32Data;
    TLE8242_astInitTxBuf[0][3].u32Data= (uint32)TLE8242_astSpiTx[0].PWMOffsetchannel0_3.u32Data;
    TLE8242_astInitTxBuf[0][4].u32Data = (uint32)TLE8242_astSpiTx[0].PWMOffsetchannel4_7.u32Data;

#if TLE8242_u8CH_NR> 1
    //TLE8242_astInitTxBuf[1][0].u32Data = (uint32)TLE8242_astSpiTx[0].ControlMethodandFaultMaskConfiguration.u32Data;
    //TLE8242_astInitTxBuf[1][1].u32Data = (uint32)TLE8242_astSpiTx[0].DiagnosticConfigurationchannel[0].u32Data;
    //TLE8242_astInitTxBuf[1][2].u32Data = (uint32)TLE8242_astSpiTx[0].DiagnosticConfigurationchannel[1].u32Data;
    //TLE8242_astInitTxBuf[1][3].u32Data = (uint32)TLE8242_astSpiTx[0].PWMOffsetchannel0_3.u32Data;
    //TLE8242_astInitTxBuf[1][4].u32Data = (uint32)TLE8242_astSpiTx[0].PWMOffsetchannel4_7.u32Data;
#endif

    Dio_WriteChannel(DioConf_DioChannel_M_TLE8242_ENA, STD_ON);
#if TLE8242_u8CH_NR> 1
    //Dio_WriteChannel(DioConf_DioChannel_TLE8242_ENA_2, STD_ON);
#endif

#if TLE8242_bUSE_INT_BUF == 1

    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_INIT_CH, (const uint8 *) TLE8242_astInitTxBuf[0]);
#if TLE8242_u8CH_NR> 1
    //Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const uint8 *) TLE8242_kastInitTxBuf[1]);
#endif

#else
    Spi_SetupEB(SpiConf_SpiChannel_TLE8242_1_INIT_CH, (const Spi_DataType*) &TLE8242_astInitTxBuf[0][0],(const Spi_DataType*) & TLE8242_astInitRxBuf[0][0], TLE8242_u8MAX_FRM_INIT_CH_1);
#if TLE8242_u8CH_NR> 1
    //Spi_SetupEB(SpiConf_SpiChannel_TLE8242_2_INIT_CH, (const Spi_DataType*) &TLE8242_kastInitTxBuf[1][0], (const Spi_DataType*) & TLE8242_kastInitRxBuf[1][0], TLE8242_u8MAX_FRM_INIT_CH_2);
#endif
#endif
    Spi_AsyncTransmit(SpiConf_SpiSequence_TLE8242_INIT_SEQ);

    //set the register then output phase sync signal.
    Gtm_SetTomCounterCn0(0, 1, 0);//Phase_sync1
#if TLE8242_u8CH_NR> 1
    //Gtm_SetAtomCounterCn0(0, 0, 0); //Phase_sync2
#endif
}

/**********************************************************************************************************************/
/* !FuncName    : TLE8242_VidConvMsgInfo                                                                                    */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidConvMsgInfo(TLE8242_DummyMsgID* pLocAddrSrc, const uint8 u8Loclen, const uint8 u8LocChipIdx)
{
    uint8 u8LocIdx, u8LocChIdx;
    uint32 * pLocAddr = 0;
    uint32 * pLocAddr1 = 0;

    pLocAddr1 = ((uint32*) (&(TLE8242_astSpiRx[u8LocChipIdx])));
    for (u8LocIdx = 0; u8LocIdx < u8Loclen; u8LocIdx++)
    {
        if (TLE8242_u8_READ_GEN_FLG_MSG_ID_7BIT == pLocAddrSrc[u8LocIdx].bits.udtMsgID)
        {
            pLocAddr = pLocAddr1 + TLE8242_u8_READ_GEN_FLG_MSG_OFFS;
        }
        else if (pLocAddrSrc[u8LocIdx].bits.udtMsgID < TLE8242_u8_MAX_VALID_MSG_ID)
        {
            pLocAddr = pLocAddr1 + pLocAddrSrc[u8LocIdx].bits.udtMsgID;
        }
        else
        {
        }
		if (0 != pLocAddr)
		{
			memcpy(pLocAddr, &pLocAddrSrc[u8LocIdx], 4);
		}
    }
}


/**********************************************************************************************************************/
/* !FuncName    : TLE8242_vidCtrlPreManagement                                                                                    */
/* !Description :                                  */
/*  This function will parse the reponse spi message back, and put it to the right place.                               */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidParseResponse(void)
{
    uint8 u8LocIdx , u8LocChIdx;
    //Std_ReturnType udtLocalRxStatus;
    static uint8 su8LocInitChRed = 0;


    for ( u8LocIdx = 0; u8LocIdx < TLE8242_u8CH_NR; ++u8LocIdx)
    {

        if(0 == su8LocInitChRed)
        {
#if TLE8242_bUSE_INT_BUF == 1
            Spi_ReadIB(SpiConf_SpiChannel_TLE8242_1_INIT_CH+u8LocIdx, (uint8 *) TLE8242_astInitRxBuf[u8LocIdx]);
#endif
            TLE8242_vidConvMsgInfo(TLE8242_astInitRxBuf[u8LocIdx], TLE8242_kau8ChBufSizeCfg[u8LocIdx], u8LocIdx);
            su8LocInitChRed = 1;
        }

#if TLE8242_bUSE_INT_BUF == 1
        Spi_ReadIB(SpiConf_SpiChannel_TLE8242_1_CTRL_CH+u8LocIdx, (uint8 *) TLE8242_astCtrlRxBuf[u8LocIdx]);
        Spi_ReadIB(SpiConf_SpiChannel_TLE8242_1_DIAG_CH+u8LocIdx, (uint8 *) TLE8242_astDiagRxBuf[u8LocIdx]);
#endif

        TLE8242_vidConvMsgInfo(TLE8242_astCtrlRxBuf[u8LocIdx], TLE8242_su8MsgSndCnt[u8LocIdx], u8LocIdx);
        //TLE8242_vidConvMsgInfo(TLE8242_astDiagRxBuf[u8LocIdx], TLE8242_kau8ChBufSizeCfg[u8LocIdx+4], u8LocIdx);
        TLE8242_vidConvMsgInfo(TLE8242_astDiagRxBuf[u8LocIdx], TLE8242_kau8ChBufSizeCfg[2], u8LocIdx);


        // As for TLE8242, only can read one channel one time, can not send 8 frames to get all the current feedback, you will get nothing.
        //

        u8LocChIdx = TLE8242_su8CurReadChNr[u8LocIdx] + u8LocIdx*8;
        TLE8242_su8CurVld[u8LocIdx][0] = TLE8242_bGetCrntVld(u8LocChIdx, TLE8242_AVG_CRNT);
        TLE8242_su8CurVld[u8LocIdx][1] = TLE8242_bGetCrntVld(u8LocChIdx, TLE8242_MAX_CRNT);



        if (TLE8242_su8CurVld[u8LocIdx][0])
        {
            //TLE8242_af32AvgCrntMa[u8LocChIdx] = TLE8242_f32RvsTrimTar(u8LocChIdx, TLE8242_f32GetCrntFb(u8LocChIdx, AvgCurrent), TEMP_s16PhysTempPcb>>4);
			//TLE8242_af32AvgCrntMa[u8LocChIdx] = Trim_Feedback_CalculateGainAndOffset(u8LocChIdx,TLE8242_f32GetCrntFb(u8LocChIdx, AvgCurrent));
			TLE8242_af32AvgCrntMa[u8LocChIdx] =  TLE8242_f32GetCrntFb(u8LocChIdx, TLE8242_AVG_CRNT);
        }
        if (TLE8242_su8CurVld[u8LocIdx][1])
        {
            //TLE8242_af32MaxCnrtMa[u8LocChIdx] = TLE8242_f32RvsTrimTar(u8LocChIdx, TLE8242_f32GetCrntFb(u8LocChIdx, MaxCurrent), TEMP_s16PhysTempPcb>>4);
            //TLE8242_af32MinCnrtMa[u8LocChIdx] = TLE8242_f32RvsTrimTar(u8LocChIdx, TLE8242_f32GetCrntFb(u8LocChIdx, MinCurrent), TEMP_s16PhysTempPcb>>4);
			TLE8242_af32MaxCnrtMa[u8LocChIdx] = TLE8242_f32GetCrntFb(u8LocChIdx, TLE8242_MAX_CRNT); //Trim_Feedback_CalculateGainAndOffset(u8LocChIdx,TLE8242_f32GetCrntFb(u8LocChIdx, MaxCurrent));
			TLE8242_af32MinCnrtMa[u8LocChIdx] = TLE8242_f32GetCrntFb(u8LocChIdx, TLE8242_MIN_CRNT); //Trim_Feedback_CalculateGainAndOffset(u8LocChIdx,TLE8242_f32GetCrntFb(u8LocChIdx, MinCurrent));
        }
        //Todo this should be a calibration.

		TLE8242_af32PwmDutyFb[u8LocChIdx] = TLE8242_f32GetPwmDutyCycle(u8LocChIdx);
		
        if (TLE8242_su8CurVld[u8LocIdx][0] || TLE8242_su8CurVld[u8LocIdx][1] || TLE8242_su8CurReadCnt[u8LocIdx][TLE8242_su8CurReadChNr[u8LocIdx]] > TLE8242_kau8ReadCrntRetMax)
        {
            TLE8242_su8CurReadCnt[u8LocIdx][TLE8242_su8CurReadChNr[u8LocIdx]] = 0;
            TLE8242_su8CurReadChNr[u8LocIdx]++;

            if (TLE8242_su8CurReadChNr[u8LocIdx] >= (TLE8242_kau8ChNrPerChip[u8LocIdx]))
            {
                TLE8242_su8CurReadChNr[u8LocIdx] = 0;
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
    uint8 u8LocChIdx = 0, u8LocFltIdx = 0, u8LocRes;
    Dem_EventIdType u8LocEveIdx ;


    for ( u8LocChIdx = 0; u8LocChIdx < TLE8242_u8MAX_CH_NR; u8LocChIdx++)
    {
        for(u8LocFltIdx = 0; u8LocFltIdx < TLE8242_u8MAX_NR_FLT; u8LocFltIdx++)
        {
        	 u8LocEveIdx = TLE8242_tstFltDev.astChDemID[u8LocChIdx].audtIdxType[u8LocFltIdx];
        	 u8LocRes = TLE8242_tstFltDev.astFltFct[u8LocFltIdx](u8LocChIdx);
        	 TLE8242_su16FltSts[u8LocChIdx][u8LocFltIdx] = u8LocRes;

        	//Dem_SetEventStatus(u8LocEveIdx , (u8LocRes)?DEM_EVENT_STATUS_PREFAILED:DEM_EVENT_STATUS_PREPASSED);
        }
    }

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
    uint8 u8LocIdx,u8LocIdx1;
    uint8 u8LocChipIdx, u8LocChIdx;
    static uint16 su16LocDitherFrqChg = 0;
    boolean bLocFltSts, bLocFltSts1;
    uint8 au8LocCfgChg[TLE8242_u8CH_NR] = { 0
#if TLE8242_u8CH_NR > 1
            , 0
#endif
};
    TLE8242_su8MsgSndCnt[0] = 0;
    /* TLE8242_su8MsgSndCnt[1] = 0; */

    for (u8LocIdx = 0; u8LocIdx < TLE8242_u8MAX_CH_NR; ++u8LocIdx)
    {
        u8LocChipIdx = u8LocIdx / 8;
        u8LocChIdx = u8LocIdx % 8;
        if (TLE8242_saf32PwmFrqOld[u8LocIdx] != TLE8242_au16PwmFrq[u8LocIdx])
        {
            TLE8242_saf32PwmFrqOld[u8LocIdx] = TLE8242_au16PwmFrq[u8LocIdx];
            TLE8242_vidSetPWMFrq(u8LocIdx, TLE8242_au16PwmFrq[u8LocIdx]);
            TLE8242_astCtrlTxBuf[u8LocChipIdx][TLE8242_su8MsgSndCnt[u8LocChipIdx]++].u32Data = (uint32) TLE8242_astSpiTx[u8LocChipIdx].MainPeriodSet[u8LocChIdx].u32Data;
        }
        if ((TLE8242_sau16KPOld[u8LocIdx] != TLE8242_kau16KP[u8LocIdx]) || (TLE8242_sau16KIOld[u8LocIdx] != TLE8242_kau16KI[u8LocIdx]))
        {
            TLE8242_sau16KPOld[u8LocIdx] = TLE8242_kau16KP[u8LocIdx];
            TLE8242_sau16KIOld[u8LocIdx] = TLE8242_kau16KI[u8LocIdx];
            TLE8242_vidSetKP(u8LocIdx, TLE8242_kau16KP[u8LocIdx]);
            TLE8242_vidSetKI(u8LocIdx, TLE8242_kau16KI[u8LocIdx]);
            TLE8242_astCtrlTxBuf[u8LocChipIdx][TLE8242_su8MsgSndCnt[u8LocChipIdx]++].u32Data =
                            (uint32) TLE8242_astSpiTx[u8LocChipIdx].ControlVariableSetKPandKI[u8LocChIdx].u32Data;
        }
        if(TLE8242_stGetCtrlMod(u8LocIdx) != TLE8242_au8OpenLoop[u8LocIdx])
        {
            TLE8242_vidSetCtrlMod(u8LocIdx, TLE8242_au8OpenLoop[u8LocIdx]);
 			TLE8242_su8CtrlModOld[u8LocIdx] = TLE8242_au8OpenLoop[u8LocIdx];
            au8LocCfgChg[u8LocChipIdx]= 1;
        }
        if (TLE8242_u8_DIRECT_MOD == TLE8242_stGetCtrlMod(u8LocIdx))
        {
			if(TLE8242_saf32DutyCycleOld[u8LocIdx] != TLE8242_af32DutyCycle[u8LocIdx])
			{
			    TLE8242_saf32DutyCycleOld[u8LocIdx] = TLE8242_af32DutyCycle[u8LocIdx];
            	TLE8242_vidSetPwmDutyCycle(u8LocIdx, TLE8242_af32DutyCycle[u8LocIdx]);
            	TLE8242_astCtrlTxBuf[u8LocChipIdx][TLE8242_su8MsgSndCnt[u8LocChipIdx]++].u32Data = (uint32) TLE8242_astSpiTx[u8LocChipIdx].PWMDutyCycle[u8LocChIdx].u32Data;        
			}
		}
        else
        {
            // when seting the dither ampl, we need to know the dither frequency, for now we prefer to use the value in the rx buff, which is the tle8242 real number of steps
            // but for the TLE8242_astSpiRx, it will be updated the next cycle, so we use this static variable "su16LocDitherFrqChg" to update the dither ampl next cycle.

            // If there is a scgnd/scbat fault, we need to set the target to 0ma, to switch off the lsd.
            //Dem_GetEventFailed(TLE8242_tstFltDev.astChDemID[u8LocIdx].audtIdxType[TLE8242_SHORT_TO_GND], &bLocFltSts);
            //Dem_GetEventFailed(TLE8242_tstFltDev.astChDemID[u8LocIdx].audtIdxType[TLE8242_SHORT_TO_BATT], &bLocFltSts1);
			bLocFltSts  = TLE8242_su16FltSts[u8LocIdx][TLE8242_SHORT_TO_GND];
			bLocFltSts1 = TLE8242_su16FltSts[u8LocIdx][TLE8242_SHORT_TO_BATT];
			
			if(bLocFltSts || bLocFltSts1)
            {
              TLE8242_af32TarCnrtMa[u8LocIdx] = 0;
            }

            if((su16LocDitherFrqChg&(1<<u8LocIdx))||(TLE8242_saf32CnrtTarOld[u8LocIdx] != TLE8242_af32TarCnrtMa[u8LocIdx]) || \
				(TLE8242_saf32DitherAmplOld[u8LocIdx] != TLE8242_af32DitherAmplMa[u8LocIdx]))
            {	
            	if(0 != TLE8242GetDitherFrq(u8LocIdx))
            	{
					TLE8242_saf32DitherAmplOld[u8LocIdx] = TLE8242_af32DitherAmplMa[u8LocIdx];
					TLE8242_vidSetDitherAmpBuf(u8LocIdx, TLE8242_af32DitherAmplMa[u8LocIdx]);
                    su16LocDitherFrqChg &= ~(1<<u8LocIdx);
            	}

				TLE8242_saf32CnrtTarOld[u8LocIdx] = TLE8242_af32TarCnrtMa[u8LocIdx];
                //TLE8242_af32TarCnrtAftTrimMa[u8LocIdx] = TLE8242_f32CalcTrimTar(u8LocIdx, TLE8242_af32TarCnrtMa[u8LocIdx], TEMP_s16PhysTempPcb>>4);
                TLE8242_af32TarCnrtAftTrimMa[u8LocIdx] = TLE8242_af32TarCnrtMa[u8LocIdx];//Trim_CalculateGainAndOffset(u8LocIdx, TLE8242_af32TarCnrtMa[u8LocIdx]);
                TLE8242_vidSetCrntTarBuf(u8LocIdx, TLE8242_af32TarCnrtAftTrimMa[u8LocIdx]);
                TLE8242_astCtrlTxBuf[u8LocChipIdx][TLE8242_su8MsgSndCnt[u8LocChipIdx]++].u32Data = (uint32) TLE8242_astSpiTx[u8LocChipIdx].CurrentandDitherAmplitudeSet[u8LocChIdx].u32Data;
            }
        }

        if(TLE8242_saf32DitherFrqOld[u8LocIdx] != TLE8242_af32DitherFrq[u8LocIdx])
        {
            TLE8242_saf32DitherFrqOld[u8LocIdx] = TLE8242_af32DitherFrq[u8LocIdx];
            TLE8242_vidSetDitherFrqBuf(u8LocIdx, TLE8242_af32DitherFrq[u8LocIdx]);
            TLE8242_astCtrlTxBuf[u8LocChipIdx][TLE8242_su8MsgSndCnt[u8LocChipIdx]++].u32Data = (uint32) TLE8242_astSpiTx[u8LocChipIdx].DitherPeriodSet[u8LocChIdx].u32Data;
            /*
             * If the channel's dither frequency had changed, the ampl should be calc ref to the new dither frequency.
             * */
            su16LocDitherFrqChg |= (1<<u8LocIdx);
        }
    }

    for (u8LocIdx = 0; u8LocIdx < TLE8242_u8CH_NR; ++u8LocIdx)
    {
        TLE8242_astCtrlTxBuf[u8LocIdx][TLE8242_su8MsgSndCnt[u8LocIdx]++].u32Data = (uint32)TLE8242_astSpiTx[u8LocIdx].MaxMinCurrentRead[TLE8242_su8CurReadChNr[u8LocIdx]].u32Data;
        TLE8242_astCtrlTxBuf[u8LocIdx][TLE8242_su8MsgSndCnt[u8LocIdx]++].u32Data = (uint32)TLE8242_astSpiTx[u8LocIdx].AverageCurrentReadOverDitherPeriod[TLE8242_su8CurReadChNr[u8LocIdx]].u32Data;
        if (1 == au8LocCfgChg[u8LocIdx])
        {
            au8LocCfgChg[u8LocIdx] = 0;
            TLE8242_astCtrlTxBuf[u8LocIdx][TLE8242_su8MsgSndCnt[u8LocIdx]++].u32Data = (uint32) TLE8242_astSpiTx[u8LocIdx].ControlMethodandFaultMaskConfiguration.u32Data;
        }
        for (u8LocChIdx = 0; u8LocChIdx < TLE8242_kau8ChNrPerChip[u8LocIdx]; u8LocChIdx++)
        {
            TLE8242_astSpiTx[u8LocIdx].PWMDutyCycle[u8LocChIdx].bits.bRW = 0;
            TLE8242_astCtrlTxBuf[u8LocIdx][TLE8242_su8MsgSndCnt[u8LocIdx]++].u32Data = (uint32)TLE8242_astSpiTx[u8LocIdx].PWMDutyCycle[u8LocChIdx].u32Data;
        }
        TLE8242_su8CurReadCnt[u8LocIdx][TLE8242_su8CurReadChNr[u8LocIdx]]++;
    }
#if TLE8242_bUSE_INT_BUF == 1
    for (u8LocIdx1 = TLE8242_su8MsgSndCnt[0]; u8LocIdx1 < TLE8242_u8MAX_FRM_CTRL_CH_1; u8LocIdx1++)
    {
        TLE8242_astCtrlTxBuf[0][u8LocIdx1].u32Data = 0;
    }
	Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_CTRL_CH, (const uint8 *) TLE8242_astCtrlTxBuf[0]);
	
#if TLE8242_u8CH_NR> 1
    for (u8LocIdx1 = TLE8242_su8MsgSndCnt[1]; u8LocIdx1 < TLE8242_u8MAX_FRM_CTRL_CH_2; u8LocIdx1++)
    {
        TLE8242_astCtrlTxBuf[1][u8LocIdx1].u32Data = 0;
    }
    
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_2_CTRL_CH, (const uint8 *) TLE8242_astCtrlTxBuf[1]);
#endif
    if((TLE8242_astCtrlTxBuf[0][0].bits.udtMsgID != 0) || (TLE8242_astCtrlTxBuf[1][0].bits.udtMsgID != 0))
    {
        Spi_AsyncTransmit(SpiConf_SpiSequence_TLE8242_CTRL_SEQ);
    }
#else
    TLE8242_astCtrlTxBuf[0][TLE8242_su8MsgSndCnt[0]++].u32Data = 0;
    Spi_SetupEB(SpiConf_SpiChannel_TLE8242_1_CTRL_CH, (const Spi_DataType*) &TLE8242_astCtrlTxBuf[0][0], (Spi_DataType *) &TLE8242_astCtrlRxBuf[0][0], TLE8242_su8MsgSndCnt[0]);
#if TLE8242_u8CH_NR> 1
    TLE8242_astCtrlTxBuf[1][TLE8242_su8MsgSndCnt[1]++].u32Data = 0;
    //Spi_SetupEB(SpiConf_SpiChannel_TLE8242_2_CTRL_CH, (const Spi_DataType*) &TLE8242_astCtrlTxBuf[1][0], (Spi_DataType *) &TLE8242_astCtrlRxBuf[1][0], TLE8242_su8MsgSndCnt[1]);
#endif
    Spi_AsyncTransmit(SpiConf_SpiSequence_TLE8242_CTRL_SEQ);
#endif
}
/**********************************************************************************************************************/
/* !FuncName    : TLE8242_vidDiagManagement                                                                                    */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidDiagManagement(void)
{
#if TLE8242_bUSE_INT_BUF == 1
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_DIAG_CH, (const uint8 *) &TLE8242_kastDiagTxBuf[0]);

#if TLE8242_u8CH_NR> 1
    Spi_WriteIB(SpiConf_SpiChannel_TLE8242_1_DIAG_CH, (const uint8 *) &TLE8242_kastDiagTxBuf[1]);
#endif
#else
    Spi_SetupEB(SpiConf_SpiChannel_TLE8242_1_DIAG_CH, (const Spi_DataType*) &TLE8242_kastDiagTxBuf[0][0], (Spi_DataType *) &TLE8242_astDiagRxBuf[0][0], TLE8242_u8MAX_FRM_DIAG_CH_1);

#if TLE8242_u8CH_NR> 1
    Spi_SetupEB(SpiConf_SpiChannel_TLE8242_2_DIAG_CH, (const Spi_DataType*) &TLE8242_kastDiagTxBuf[1][0], (Spi_DataType *) &TLE8242_astDiagRxBuf[1][0], TLE8242_u8MAX_FRM_DIAG_CH_2);
#endif
#endif
    Spi_AsyncTransmit(SpiConf_SpiSequence_TLE8242_DIAG_SEQ);
}

#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"