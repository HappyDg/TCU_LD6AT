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
/* Author::   gsun5                               Date::   Jan 10, 2017                               */
/**********************************************************************************************************************/
#include "TLE8242_interface.h"
#include "TLE8242.h"
#include "TLE8242_def.h"
#include "MAIN_L.h"

#include "VADC.h"
#include "DIO_WrapAPI.h"
/*
 *
 * Macro check
 * */

#ifndef TLE8242_u8_FLT_SC_BIT
#error "TLE8242_u8_FLT_SC_BIT should be defined before used."
#endif
#ifndef TLE8242_u8_FLT_SCS_TST_BIT
#error "TLE8242_u8_FLT_SCS_TST_BIT should be defined before used."
#endif
#ifndef TLE8242_u8_FLT_OFF_TST_BIT
#error "TLE8242_u8_FLT_OFF_TST_BIT should be defined before used."
#endif
#ifndef TLE8242_u8_FLT_OL_ON_BIT
#error "TLE8242_u8_FLT_OL_ON_BIT should be defined before used."
#endif
#ifndef TLE8242_u8_FLT_OL_OFF_BIT
#error "TLE8242_u8_FLT_OL_OFF_BIT should be defined before used."
#endif
#ifndef TLE8242_u32FCLKIPT
#error "TLE8242_u32FCLKIPT should be defined before used."
#endif
#ifndef TLE8242_u8_MAX_VALID_DIV_N
#error "TLE8242_u8_MAX_VALID_DIV_N should be defined before used."
#endif
#ifndef TLE8242_u8_MAX_VALID_DIV_M
#error "TLE8242_u8_MAX_VALID_DIV_M should be defined before used."
#endif
#ifndef TLE8242_u32_MAX_VALID_KP
#error "TLE8242_u32_MAX_VALID_KP should be defined before used."
#endif
#ifndef TLE8242_u32_MAX_VALID_KI
#error "TLE8242_u32_MAX_VALID_KI should be defined before used."
#endif
#ifndef TLE8242_u32_MAX_VALID_CRNT_SETPOINT
#error "TLE8242_u32_MAX_VALID_CRNT_SETPOINT should be defined before used."
#endif

#ifndef TLE8242_u8DITHER_SETPOINT_TO_CURRENT_POINT
#error "TLE8242_u8DITHER_SETPOINT_TO_CURRENT_POINT should be defined before used."
#endif
#ifndef TLE8242_u8_MAX_VALID_DITHER_STEPS
#error "TLE8242_u8_MAX_VALID_DITHER_STEPS should be defined before used."
#endif




static uint16 TLE8242_su16ScsSts = 0;
static uint16 TLE8242_su16ScSts = 0;
static uint16 TLE8242_su16OpenLoadSts = 0;




#define TLE8242_START_SEC_CODE
#include "MemMap.h"
/*
 * function declaration.
 * */

uint32 TLE8242_u32CnvCrntToSetPoint(float32 f32CrntTar)
{
	float32 f32LocLocTmp;
	uint32 u16Locsetpoint;


	f32LocLocTmp = f32CrntTar * 2048;
	f32LocLocTmp = f32LocLocTmp * TLE8242_kf32R_Shunt;
	f32LocLocTmp = f32LocLocTmp / 320;

	f32LocLocTmp += 0.5;

	u16Locsetpoint = (uint32)f32LocLocTmp;
	return (u16Locsetpoint);

}
float32 TLE8242_f32CnvpointToCrnt(uint32 setpoint)
{
	float32 f32LocLocTmp;

	f32LocLocTmp = setpoint * 320;
	f32LocLocTmp = f32LocLocTmp/2048;
	f32LocLocTmp = f32LocLocTmp/TLE8242_kf32R_Shunt;

	return (f32LocLocTmp);

}
//SPI Message #0 - IC Version / Manufacturer
Tle8242ICManufIDTyp TLE8242_stGetIcManufID (uint8 u8LocChIdx)
{
    return (Tle8242ICManufIDTyp)(TLE8242_astSpiRx[u8LocChIdx/8].ICVersionManufacturer.bits.udtICManufID);
}
Tle8242VersNrTyp TLE8242_stGetVersNr (uint8 u8LocChIdx)
{
    return (Tle8242VersNrTyp)(TLE8242_astSpiRx[u8LocChIdx/8].ICVersionManufacturer.bits.udtVersionNumber);
}


//SPI Message #1 - Control Method and Fault Mask Configuration
boolean TLE8242_bGetFltMaskEna (uint8 u8LocChIdx)
{
    return ((boolean)TLE8242_astSpiRx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.bFME);
}
void TLE8242_vidSetFltMaskEna (uint8 u8LocChIdx, boolean bLocFME)
{
    TLE8242_astSpiTx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.bFME = bLocFME;
}
void TLE8242_vidSetFltMask (uint8 u8LocChIdx, Tle8242FaultMaskType stLocFM)
{
    uint8 U8LocTmp = TLE8242_astSpiTx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.udtFM;
    U8LocTmp &= ~(1<<(7-u8LocChIdx%8));
    U8LocTmp |= (stLocFM<<(7-u8LocChIdx%8));

    TLE8242_astSpiTx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.udtFM = U8LocTmp;
}
Tle8242FaultMaskType TLE8242_bGetFltMask (uint8 u8LocChIdx)
{
    return (Tle8242FaultMaskType)((TLE8242_astSpiRx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.udtFM&(1<<(7-u8LocChIdx%8))));
}
boolean TLE8242_bGetFltMaskRstB (uint8 u8LocChIdx)
{
    return (boolean)(TLE8242_astSpiRx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.bFMR);
}

void TLE8242_vidSetFltMaskRstB (uint8 u8LocChIdx, boolean bLocFMR)
{
    TLE8242_astSpiTx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.bFMR = bLocFMR;
}
void TLE8242_vidSetCtrlMod (uint8 u8LocChIdx, Tle8242CtrlModTyp stLocCM)
{
    uint8 U8LocTmp = TLE8242_astSpiTx[u8LocChIdx / 8].ControlMethodandFaultMaskConfiguration.bits.udtCM;
    U8LocTmp &= ~(1 << (7 - u8LocChIdx % 8));
    U8LocTmp |= (stLocCM << (7 - u8LocChIdx % 8));

    TLE8242_astSpiTx[u8LocChIdx / 8].ControlMethodandFaultMaskConfiguration.bits.udtCM = U8LocTmp;
}
Tle8242CtrlModTyp TLE8242_stGetCtrlMod (uint8 u8LocChIdx)
{
    return ((Tle8242CtrlModTyp)(TLE8242_astSpiRx[u8LocChIdx/8].ControlMethodandFaultMaskConfiguration.bits.udtCM&(1<<(7-u8LocChIdx%8))) >>(7-u8LocChIdx%8));
}
void TLE8242_vidSetDisgTmr(uint8 u8LocChIdx, Tle8242DiagTmrDivTyp diag_tmr)
{
    uint8 u8LocChipIdx;

    u8LocChipIdx = u8LocChIdx / 8;

    TLE8242_astSpiTx[u8LocChipIdx].ControlMethodandFaultMaskConfiguration.bits.udtDIAG_TMR = diag_tmr;
}
Tle8242DiagTmrDivTyp TLE8242_stGetDisgTmr(uint8 u8LocChIdx )
{
    uint8 u8LocChipIdx;

    u8LocChipIdx = u8LocChIdx / 8;

    return (TLE8242_astSpiRx[u8LocChipIdx].ControlMethodandFaultMaskConfiguration.bits.udtDIAG_TMR);
}
//SPI Message #2 - Diagnostic Configuration (u8LocChIdx 0-3)
//SPI Message #3 - Diagnostic Configuration (u8LocChIdx 4-7)

void TLE8242SetScsRetry (uint8 u8LocChIdx, uint8 u8LocScsRetry)
{
    //TLE8242_astSpiTx[u8LocChIdx/8].DiagnosticConfigurationchannel[u8LocChIdx%8/4]
}
// Todo void TLE8242SetShortBatThreshold (uint8 u8LocChIdx, ShortBatThresholdType sb);
// Todo ShortBatThresholdType TLE8242_bGetScsFltThreshold (uint8 u8LocChIdx);
// Todo ShortBatRetryType TLE8242_bGetScsFltRetry (uint8 u8LocChIdx);

//SPI Message #4 - Diagnostic Read (u8LocChIdx 0-3)
//SPI Message #5 - Diagnostic Read (u8LocChIdx 4-7)

boolean TLE8242_bGetScFlt (uint8 u8LocChIdx)  // short ground
{
	static uint8 u8LocChipIdx, u8LocMsgIdx, u8ChIdx, u8FltBitIdx, u8FltTstBitIdx;
	static boolean bLocFlt;

	u8LocChipIdx = u8LocChIdx / 8;
	u8ChIdx = (u8LocChIdx % 8);
	u8LocMsgIdx = u8ChIdx / 4;
	u8FltBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_SC_BIT;

	u8FltTstBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_OFF_TST_BIT;
	if ((TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data & (1 << u8FltTstBitIdx)) >> u8FltTstBitIdx)
	{
		bLocFlt = (TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data & (1 << u8FltBitIdx)) >> u8FltBitIdx;
		if (bLocFlt)
		{
			TLE8242_su16ScSts |= 1 << u8LocChIdx;
		}
		else
		{
			TLE8242_su16ScSts &= ~(1 << u8LocChIdx);
		}

	}

	return (TLE8242_su16ScSts & (1 << u8LocChIdx)) >> u8LocChIdx;
}
boolean TLE8242_bGetScsFlt (uint8 u8LocChIdx) // short battary
{
    static uint8 u8LocChipIdx, u8LocMsgIdx,u8ChIdx, u8FltBitIdx, u8FltTstBitIdx;
    static boolean bLocFlt;

    u8LocChipIdx = u8LocChIdx/8;
    u8ChIdx = (u8LocChIdx%8);
    u8LocMsgIdx = u8ChIdx/4;
    u8FltBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_SCS_BIT;
    u8FltTstBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_SCS_TST_BIT;

    if((TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data&(1<<u8FltTstBitIdx)) >> u8FltTstBitIdx)
    {
      bLocFlt = (TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data&(1<<u8FltBitIdx)) >> u8FltBitIdx;
      if(bLocFlt)
      {
    	TLE8242_su16ScsSts |= 1 << u8LocChIdx;
      }
      else
      {
    	TLE8242_su16ScsSts &= ~(1 << u8LocChIdx);
      }

    }

    return (TLE8242_su16ScsSts & (1 << u8LocChIdx)) >> u8LocChIdx;
}
boolean TLE8242_bGetOffTst (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx, u8LocMsgIdx,u8ChIdx, u8FltBitIdx;

    u8LocChipIdx = u8LocChIdx/8;
    u8ChIdx = (u8LocChIdx%8);
    u8LocMsgIdx = u8ChIdx/4;
    u8FltBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_OFF_TST_BIT;

    return ((TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data&(1<<u8FltBitIdx)) >> u8FltBitIdx);
}
boolean TLE8242_bGetScsTst (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx, u8LocMsgIdx,u8ChIdx, u8FltBitIdx;

    u8LocChipIdx = u8LocChIdx/8;
    u8ChIdx = (u8LocChIdx%8);
    u8LocMsgIdx = u8ChIdx/4;
    u8FltBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_SCS_TST_BIT;

    return ((TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data&(1<<u8FltBitIdx)) >> u8FltBitIdx);
}
boolean TLE8242_bGetOpenLoadGateOn (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx, u8LocMsgIdx,u8ChIdx, u8FltBitIdx;

    u8LocChipIdx = u8LocChIdx/8;
    u8ChIdx = (u8LocChIdx%8);
    u8LocMsgIdx = u8ChIdx/4;
    u8FltBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_OL_ON_BIT;

    return ((TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data&(1<<u8FltBitIdx)) >> u8FltBitIdx);
}
boolean TLE8242_bGetOpenLoadGateOff (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx, u8LocMsgIdx,u8ChIdx, u8FltBitIdx;

    u8LocChipIdx = u8LocChIdx/8;
    u8ChIdx = (u8LocChIdx%8);
    u8LocMsgIdx = u8ChIdx/4;
    u8FltBitIdx = ((3-(u8ChIdx%4))*6) + TLE8242_u8_FLT_OL_OFF_BIT;

    return ((TLE8242_astSpiRx[u8LocChipIdx].DiagnosticReadchannel[u8LocMsgIdx].u32Data&(1<<u8FltBitIdx)) >> u8FltBitIdx);
}
boolean TLE8242_bGetChOpenLoadFlt(uint8 u8LocChIdx)
{
	return (TLE8242_bGetOpenLoadGateOff(u8LocChIdx) || TLE8242_bGetOpenLoadGateOn(u8LocChIdx));
}
//SPI Message #6 - PWM Offset (u8LocChIdx 0-3)
//SPI Message #7 - PWM Offset (u8LocChIdx 4-7)
//SPI Message #8 - Main Period Set

Tle8242SampleSummMethodType TLE8242_stGetSampleSummaryMethod (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,u8ChIdx ;

    u8LocChipIdx = u8LocChIdx/8;
    u8ChIdx = (u8LocChIdx%8);

    return ((Tle8242SampleSummMethodType)TLE8242_astSpiRx[u8LocChipIdx].MainPeriodSet[u8ChIdx].bits.SAM);
}
void TLE8242_vidSetSampleSummMethod (uint8 u8LocChIdx, Tle8242SampleSummMethodType stSAM)
{
    uint8 u8LocChipIdx,u8ChIdx;

    u8LocChipIdx = u8LocChIdx/8;
    u8ChIdx = (u8LocChIdx%8);

    TLE8242_astSpiTx[u8LocChipIdx].MainPeriodSet[u8ChIdx].bits.SAM = stSAM;
}
void TLE8242_vidSetPWMFrq(uint8 u8LocChIdx, float32 f32LocFrq)
{
    uint8 u8LocBestM=0, u8LocIdx;
    uint16 u8LocBestN=79, u8LocM, u8LocN, au8LocDivM[4] = { 32, 64, 128, 512 };
    float32 f32LocDis, f32LocfrqReal, f32LocBestDis = f32LocFrq;
    uint8 u8LocEndLoop = 0;

    if(TLE8242_kf32ChopperFrqMinThd > f32LocFrq)
    {
        f32LocFrq = TLE8242_kf32ChopperFrqMinThd;
    }
    else if(TLE8242_kf32ChopperFrqMaxThd <  f32LocFrq)
    {
        f32LocFrq = TLE8242_kf32ChopperFrqMaxThd;
    }
    f32LocBestDis = f32LocFrq;

    for (u8LocIdx = 0; u8LocIdx < 4; ++u8LocIdx)
    {
        u8LocM = au8LocDivM[u8LocIdx];
        u8LocN = TLE8242_u32FCLKIPT/(f32LocFrq*u8LocM);
        f32LocfrqReal = TLE8242_u32FCLKIPT/(u8LocM*u8LocN);
        f32LocDis = __fabsf(f32LocFrq - f32LocfrqReal);
        if (f32LocDis < f32LocBestDis)
        {
            f32LocBestDis = f32LocDis;
            u8LocBestN = u8LocN;
            u8LocBestM = u8LocIdx;
        }
        if (f32LocDis < 100)
        {
            u8LocEndLoop = 1;
            break;
        }

        if (1 == u8LocEndLoop)
        {
            break;
        }
    }
    TLE8242_vidSetDivN(u8LocChIdx, u8LocBestN);
    TLE8242_vidSetDivM(u8LocChIdx, u8LocBestM);

}
float32 TLE8242_f32GetPwmFrq(uint8 u8LocChIdx)
{

    return (TLE8242_u32FCLKIPT/(TLE8242_u32GetDivN(u8LocChIdx)*TLE8242_u32GetDivM(u8LocChIdx)));
}

void TLE8242_vidSetDivN (uint8 u8LocChIdx, DividerNType u32LocDivN)
{
    uint8 u8LocChipIdx, u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    TLE8242_astSpiTx[u8LocChipIdx].MainPeriodSet[u8ChIdx].bits.DividerN = (u32LocDivN>TLE8242_u8_MAX_VALID_DIV_N)?TLE8242_u8_MAX_VALID_DIV_N:u32LocDivN;

}
DividerNType TLE8242_u32GetDivN (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    return ((DividerNType)TLE8242_astSpiRx[u8LocChipIdx].MainPeriodSet[u8ChIdx].bits.DividerN);

}
void TLE8242_vidSetDivM (uint8 u8LocChIdx, DividerMType u32LocDivM)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    TLE8242_astSpiTx[u8LocChipIdx].MainPeriodSet[u8ChIdx].bits.DividerM = (u32LocDivM>TLE8242_u8_MAX_VALID_DIV_M)?TLE8242_u8_MAX_VALID_DIV_M:u32LocDivM;

}
DividerMType TLE8242_u32GetDivM (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;
    uint16 au8LocDivM[4] = { 32, 64, 128, 512 };

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    return ((DividerMType)(au8LocDivM[TLE8242_astSpiRx[u8LocChipIdx].MainPeriodSet[u8ChIdx].bits.DividerM]));

}

//SPI Message #9 - Control Variable Set (KP and KI)
KPType TLE8242_u32GetKP (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    return ((KPType)TLE8242_astSpiRx[u8LocChipIdx].ControlVariableSetKPandKI[u8ChIdx].bits.kp);

}
void TLE8242_vidSetKP (uint8 u8LocChIdx, KPType u32LocKP)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    TLE8242_astSpiTx[u8LocChipIdx].ControlVariableSetKPandKI[u8ChIdx].bits.kp =  (TLE8242_u32_MAX_VALID_KP < u32LocKP)?TLE8242_u32_MAX_VALID_KP:u32LocKP;

}
KIType TLE8242_u32GetKI (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    return ((KIType)TLE8242_astSpiRx[u8LocChipIdx].ControlVariableSetKPandKI[u8ChIdx].bits.ki);

}
void TLE8242_vidSetKI (uint8 u8LocChIdx, KIType u32Locki)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    TLE8242_astSpiTx[u8LocChipIdx].ControlVariableSetKPandKI[u8ChIdx].bits.ki = (TLE8242_u32_MAX_VALID_KI < u32Locki)?TLE8242_u32_MAX_VALID_KI:u32Locki;

}
//SPI Message #10 - Current and Dither Amplitude Set

void TLE8242_vidSetDitherStepSize (uint8 u8LocChIdx, DitherstepsizeType u16StepSize)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    TLE8242_astSpiTx[u8LocChipIdx].CurrentandDitherAmplitudeSet[u8ChIdx].bits.Ditherstepsize = (u16StepSize>TLE8242_u32_MAX_VALID_CRNT_SETPOINT)?TLE8242_u32_MAX_VALID_CRNT_SETPOINT:u16StepSize;

}
void TLE8242_vidSetOptEnaDeactive (uint8 u8LocChIdx, Tle8242OptEnableDeactiveType stEN)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    TLE8242_astSpiTx[u8LocChipIdx].CurrentandDitherAmplitudeSet[u8ChIdx].bits.EN = stEN;

}
void TLE8242_vidSetCrntTarBuf (uint8 u8LocChIdx, CurrentsetpointType f32LocCrntTar)
{
    uint8 u8LocChipIdx,  u8ChIdx;
    uint16 u16SetPoint;


    u16SetPoint = TLE8242_u32CnvCrntToSetPoint(f32LocCrntTar);

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);


    TLE8242_astSpiTx[u8LocChipIdx].CurrentandDitherAmplitudeSet[u8ChIdx].bits.Currentsetpoint = (u16SetPoint > TLE8242_u32_MAX_VALID_CRNT_SETPOINT)?TLE8242_u32_MAX_VALID_CRNT_SETPOINT:u16SetPoint;

}

CurrentsetpointType TLE8242_f32GetCrntTar (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    return ((CurrentsetpointType)(TLE8242_f32CnvpointToCrnt(TLE8242_astSpiRx[u8LocChipIdx].CurrentandDitherAmplitudeSet[u8ChIdx].bits.Currentsetpoint)));

}



/**********************************************************************************************************************/
/* !FuncName    : TLE8242_vidSetDitherAmp                                                                                    */
/* !Description :                                  */
/* This function should be called after TLE8242_vidSetDitherFrq(), because the ampl is related to the dither frequency.       */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242_vidSetDitherAmpBuf(uint8 u8LocChIdx, float32 f32LocCrnt)
{

    uint16 u16LocSteps, u16LocSetPoint;

    u16LocSteps = TLE8242_u16GetStepsNr(u8LocChIdx);
    u16LocSetPoint = (uint16)((float)((TLE8242_u32CnvCrntToSetPoint(f32LocCrnt/u16LocSteps))*TLE8242_u8DITHER_SETPOINT_TO_CURRENT_POINT/2)+0.5);

    TLE8242_vidSetDitherStepSize(u8LocChIdx, u16LocSetPoint);
}
float32 TLE8242_f32GetDitherAmp(uint8 u8LocChIdx)
{
    uint16 u16LocDitherSteps;
    float32 f32LocCrnt;

    u16LocDitherSteps = TLE8242_u16GetStepsNr(u8LocChIdx);
    f32LocCrnt = (TLE8242_f32CnvpointToCrnt(TLE8242_u16GetDitherStepSize(u8LocChIdx)) / TLE8242_u8DITHER_SETPOINT_TO_CURRENT_POINT);
    return f32LocCrnt;
}

DitherstepsizeType TLE8242_u16GetDitherStepSize (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    return (DitherstepsizeType)TLE8242_astSpiRx[u8LocChipIdx].CurrentandDitherAmplitudeSet[u8ChIdx].bits.Ditherstepsize;

}
Tle8242OptEnableDeactiveType TLE8242GetOptEnableDeactive (uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    return (Tle8242OptEnableDeactiveType)TLE8242_astSpiRx[u8LocChipIdx].CurrentandDitherAmplitudeSet[u8ChIdx].bits.EN;

}

//SPI Message #11 - Dither Period Set

void TLE8242_vidSetDitherFrqBuf(uint8 u8LocChIdx, float32 f32LocFrq)
{
    uint16 u16LocDitherSteps;
    float32 pwmfrq;

    if (0 == f32LocFrq)
    {
        u16LocDitherSteps = 0;
    }
    else
    {
        pwmfrq = TLE8242_f32GetPwmFrq(u8LocChIdx);
        u16LocDitherSteps = (pwmfrq / (f32LocFrq * 4)) + 0.5;
    }

    TLE8242SetNumberOfSteps(u8LocChIdx, u16LocDitherSteps);
}

float32 TLE8242GetDitherFrq(uint8 u8LocChIdx)
{
    uint16 u16LocDitherSteps;
    float32 pwmfrq, dithfrq;

    pwmfrq = TLE8242_f32GetPwmFrq(u8LocChIdx);
    u16LocDitherSteps = TLE8242_u16GetStepsNr(u8LocChIdx);
    dithfrq = (pwmfrq / (u16LocDitherSteps * 4));
    return dithfrq;
}

uint8 TLE8242_u16GetStepsNr(uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;
    uint8 steps;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    steps = TLE8242_astSpiRx[u8LocChipIdx].DitherPeriodSet[u8ChIdx].bits.Numberofsteps;
    if(0 == steps)
    {
        steps = TLE8242_astSpiTx[u8LocChipIdx].DitherPeriodSet[u8ChIdx].bits.Numberofsteps;
    }
    return steps;
}
void TLE8242SetNumberOfSteps(uint8 u8LocChIdx, uint8 numberofsteps)
{
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);
    TLE8242_astSpiTx[u8LocChipIdx].DitherPeriodSet[u8ChIdx].bits.Numberofsteps = (numberofsteps>TLE8242_u8_MAX_VALID_DITHER_STEPS)?TLE8242_u8_MAX_VALID_DITHER_STEPS:numberofsteps;
}

boolean TLE8242GetDitherEnabled(uint8 u8LocChIdx)
{
    uint16 u16LocDitherSteps, u16LocDitherAmp;
    boolean bLocEna = 0;

    u16LocDitherSteps = TLE8242_u16GetStepsNr(u8LocChIdx);
    u16LocDitherAmp = TLE8242_u16GetDitherStepSize(u8LocChIdx);

    if((0 == u16LocDitherSteps) || (0 == u16LocDitherAmp))
    {
        bLocEna = 0;
    }
    else
    {
        bLocEna = 1;
    }
    return bLocEna;
}

//SPI Message #12 - Max / Min Current Read
//SPI Message #13 - Average Current Read Over Dither Period

float32 TLE8242_f32GetCrntFb(uint8 u8LocChIdx, Tle8242CurrentType stTtype)
{
    boolean u8LocEna;
    Tle8242CtrlModTyp stLocMod;
    float32 f32LocFb;
    uint8 u8LocChipIdx,  u8ChIdx;
    uint32 u32LocCrntRaw, u32LocRat;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);
    u8LocEna = TLE8242GetDitherEnabled(u8LocChIdx);
    stLocMod = TLE8242_stGetCtrlMod(u8LocChIdx);

    switch (stTtype)
    {
    case TLE8242_MIN_CRNT:
        u32LocCrntRaw = TLE8242_astSpiRx[u8LocChipIdx].MaxMinCurrentRead[u8ChIdx].bits.Min;
        break;
    case TLE8242_MAX_CRNT:
        u32LocCrntRaw = TLE8242_astSpiRx[u8LocChipIdx].MaxMinCurrentRead[u8ChIdx].bits.Max;
        break;
    case TLE8242_AVG_CRNT:
        u32LocCrntRaw = TLE8242_astSpiRx[u8LocChipIdx].AverageCurrentReadOverDitherPeriod[u8ChIdx].bits.AverageDitherCurrent;
        break;
    default:
        break;
    }

    if ((TLE8242_DIRECT_PWM_MOD == stLocMod) && (512 == TLE8242_u32GetDivM(u8LocChIdx)))
    {
        if (TLE8242_AVG_CRNT == stTtype)
        {
            if (u8LocEna)
            {
                uint8 steps = TLE8242_u16GetStepsNr(u8LocChIdx);

                u32LocRat = 16 * 4 * steps;
            }
            else
            {
                u32LocRat = 16;
            }
        }
        else
        {
            u32LocRat = 4;
        }
    }
    else
    {
        if (TLE8242_AVG_CRNT == stTtype)
        {
            if (u8LocEna)
            {
                uint8 steps = TLE8242_u16GetStepsNr(u8LocChIdx);

                u32LocRat = (16 * steps);
            }
            else
            {
                u32LocRat = (4);
            }
        }
        else
        {
            u32LocRat = 1;
        }
    }
    f32LocFb = TLE8242_f32CnvpointToCrnt(u32LocCrntRaw) / u32LocRat;

    return f32LocFb;
}
Tle8242ValidType TLE8242_bGetCrntVld(uint8 u8LocChIdx, Tle8242CurrentType stTtype)
{
    Tle8242ValidType valid;
    uint8 u8LocChipIdx,  u8ChIdx;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    switch (stTtype)
    {
    case TLE8242_MIN_CRNT:
        valid = TLE8242_astSpiRx[u8LocChipIdx].MaxMinCurrentRead[u8ChIdx].bits.Valid;
        break;
    case TLE8242_MAX_CRNT:
        valid = TLE8242_astSpiRx[u8LocChipIdx].MaxMinCurrentRead[u8ChIdx].bits.Valid;
        break;
    case TLE8242_AVG_CRNT:
        valid = TLE8242_astSpiRx[u8LocChipIdx].AverageCurrentReadOverDitherPeriod[u8ChIdx].bits.Valid;
        break;
    default:
        break;
    }
    return valid;
}
//SPI Message #14 - Autozero Trigger / Read
//SPI Message #15 - PWM Duty Cycle
void TLE8242_vidSetPwmDutyCycle(uint8 u8LocChIdx, float32 f32LocDuty)
{

    uint8 u8LocChipIdx,  u8ChIdx;
    uint32 u8LocM,u8LocN;
    uint32 u32LocDuty;

        u8LocChipIdx = u8LocChIdx / 8;
        u8ChIdx = (u8LocChIdx % 8);

        u8LocM = TLE8242_u32GetDivM(u8LocChIdx);
        u8LocN = TLE8242_u32GetDivN(u8LocChIdx);
        u32LocDuty = u8LocM*u8LocN*f32LocDuty;


        TLE8242_astSpiTx[u8LocChipIdx].PWMDutyCycle[u8ChIdx].bits.bRW = 1;
        TLE8242_astSpiTx[u8LocChipIdx].PWMDutyCycle[u8ChIdx].bits.Pwmdutycycle = u32LocDuty;
}

/**********************************************************************************************************************/
/* !FuncName    : TLE8242_f32GetPwmDutyCycle                                                                                    */
/* !Argument    : uint8                                                                      */
/* !Description :                                  */
/*                                                                                                                    */
/* !LastAuthor  : gsun5                                                                                          */
/* !Date        : May 3, 2017 11:06:40 AM                                                         */
/**********************************************************************************************************************/
float32 TLE8242_f32GetPwmDutyCycle(uint8 u8LocChIdx)
{
    uint8 u8LocChipIdx,  u8ChIdx;
    uint32 u32LocM,u32LocN, u32LocDutyRaw;
    float32 u32LocDuty;

    u8LocChipIdx = u8LocChIdx / 8;
    u8ChIdx = (u8LocChIdx % 8);

    if (TLE8242_CRNT_CTRL_MOD == TLE8242_stGetCtrlMod(u8LocChIdx))
    {
        u32LocM = TLE8242_u32GetDivM(u8LocChIdx);
    }
    else
    {
        u32LocM = 32;
    }
    u32LocN = TLE8242_u32GetDivN(u8LocChIdx);

    u32LocDutyRaw = TLE8242_astSpiRx[u8LocChipIdx].PWMDutyCycle[u8ChIdx].bits.Pwmdutycycle;

    u32LocDuty = ((float32)u32LocDutyRaw)/(u32LocM*u32LocN);

    if(u32LocDuty > 1.0)
    {
        u32LocDuty = 1.0;
    }

    return u32LocDuty;

}
//SPI Message #16 - Current Profile Detection Setup 1
//SPI Message #17 - Current Profile Detection Setup 2
//SPI Message #18 - Current Profile Detection Feedback
//SPI Message #19 - Read Generic Flag Bits
boolean TLE8242_bGetGenericFalg(uint8 u8LocChIdx, Tle8242GenericFlagType stType)
{
    uint8 u8LocChipIdx;
    boolean bLocRes;

    u8LocChipIdx = u8LocChIdx / 8;

    switch (stType)
    {
    case TLE8242_GENERIC_OVER_VOL:
        bLocRes = TLE8242_astSpiRx[u8LocChipIdx].ReadGenericFlagBits.bits.OV;
        break;
    case TLE8242_GENERIC_PHASE_SYNC:
        bLocRes = TLE8242_astSpiRx[u8LocChipIdx].ReadGenericFlagBits.bits.PS;
        break;
    case TLE8242_GENERIC_ENABLE:
        bLocRes = TLE8242_astSpiRx[u8LocChipIdx].ReadGenericFlagBits.bits.RB_L;
        break;
    case TLE8242_GENERIC_RESET:
        bLocRes = TLE8242_astSpiRx[u8LocChipIdx].ReadGenericFlagBits.bits.RB_L;
        break;
    default:
        bLocRes = 0;
        break;
    }

    return bLocRes;
}


// overload and underload detect.
boolean TLE8242_bGetChOverLoadFlt(uint8 u8LocChIdx)
{
	boolean bLocFlt = 0;

	if(0 != TLE8242_af32TarCnrtMa[u8LocChIdx])
	{
		bLocFlt = (((TLE8242_af32TarCnrtMa[u8LocChIdx] - TLE8242_af32AvgCrntMa[u8LocChIdx])/TLE8242_af32TarCnrtMa[u8LocChIdx]) > TLE8242_kf32OverUnderLoadThd);
	}
	return bLocFlt;
}
boolean TLE8242_bGetChUnderLoadFlt(uint8 u8LocChIdx)
{
	boolean bLocFlt = 0;

	if(0 != TLE8242_af32TarCnrtMa[u8LocChIdx])
	{
		bLocFlt = (((TLE8242_af32AvgCrntMa[u8LocChIdx] - TLE8242_af32TarCnrtMa[u8LocChIdx])/TLE8242_af32TarCnrtMa[u8LocChIdx]) > TLE8242_kf32OverUnderLoadThd);
	}
	return bLocFlt;
}
boolean TLE8242_bGetChGenFlt(uint8 u8LocChIdx)
{
	// Todo:don't know how to do this for now.
	return 0;
}

//end
#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"






