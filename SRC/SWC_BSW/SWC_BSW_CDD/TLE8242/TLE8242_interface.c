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
#include "TLE8242_def.h"
#include "MAIN_L.h"

/*
 * function declaration.
 * */

#define TLE8242_START_SEC_CODE
#include "MemMap.h"
//SPI Message #0 - IC Version / Manufacturer
Tle8242ICManufIDType TLE8242GetICManufID (uint8 channel)
{
    return (Tle8242ICManufIDType)TLE8242_au32SpiRx[channel/8].ICVersionManufacturer.bits.ICManufID;
}
Tle8242VersionNumberType TLE8242GetVersionNumber (uint8 channel)
{
    return (Tle8242VersionNumberType)TLE8242_au32SpiRx[channel/8].ICVersionManufacturer.bits.VersionNumber;
}


//SPI Message #1 - Control Method and Fault Mask Configuration
bool TLE8242GetFaultMaskEnable (uint8 channel)
{
    return (bool)TLE8242_au32SpiRx[channel/8].ControlMethodandFaultMaskConfiguration.bits.FME;
}
void TLE8242SetFaultMaskEnable (uint8 channel, bool fme)
{
    TLE8242_au32SpiTx[channel/8].ControlMethodandFaultMaskConfiguration.bits.FME = fme;
}
void TLE8242SetFaultMask (uint8 channel, Tle8242FaultMaskType fm)
{
    uint8 tmp = TLE8242_au32SpiTx[channel/8].ControlMethodandFaultMaskConfiguration.bits.FM;
    tmp &= ~(1<<(7-channel%8));
    tmp |= (fm<<(7-channel%8));

    TLE8242_au32SpiTx[channel/8].ControlMethodandFaultMaskConfiguration.bits.FM = tmp;
}
Tle8242FaultMaskType TLE8242GetFaultMask (uint8 channel)
{
    return (Tle8242FaultMaskType)TLE8242_au32SpiRx[channel/8].ControlMethodandFaultMaskConfiguration.bits.FM&(1<<(7-channel%8));
}
bool TLE8242GetFaultMaskResetb (uint8 channel)
{
    return (bool)TLE8242_au32SpiRx[channel/8].ControlMethodandFaultMaskConfiguration.bits.FMR;
}

void TLE8242SetFaultMaskResetb (uint8 channel, bool fmr)
{
    TLE8242_au32SpiTx[channel/8].ControlMethodandFaultMaskConfiguration.bits.FMR = fmr;
}
void TLE8242SetControlMode (uint8 channel, Tle8242ControlModeType cm)
{
    uint8 tmp = TLE8242_au32SpiTx[channel / 8].ControlMethodandFaultMaskConfiguration.bits.CM;
    tmp &= ~(1 << (7 - channel % 8));
    tmp |= (cm << (7 - channel % 8));

    TLE8242_au32SpiTx[channel / 8].ControlMethodandFaultMaskConfiguration.bits.CM = tmp;
}
Tle8242ControlModeType TLE8242GetControlMode (uint8 channel)
{
    return (Tle8242ControlModeType)TLE8242_au32SpiRx[channel/8].ControlMethodandFaultMaskConfiguration.bits.CM&(1<<(7-channel%8));
}
void TLE8242SetDIAG_TMR(uint8 channel, Tle8242DiagTimerDivType diag_tmr)
{
    uint8 chip_index;

    chip_index = channel / 8;

    TLE8242_au32SpiTx[chip_index].ControlMethodandFaultMaskConfiguration.bits.DIAG_TMR = diag_tmr;
}
Tle8242DiagTimerDivType TLE8242GetDIAG_TMR(uint8 channel )
{
    uint8 chip_index;

    chip_index = channel / 8;

    return TLE8242_au32SpiRx[chip_index].ControlMethodandFaultMaskConfiguration.bits.DIAG_TMR;
}
//SPI Message #2 - Diagnostic Configuration (channel 0-3)
//SPI Message #3 - Diagnostic Configuration (channel 4-7)

void TLE8242SetShortBatRetry (uint8 channel, uint8 sb_retry)
{
    //TLE8242_au32SpiTx[channel/8].DiagnosticConfigurationchannel[channel%8/4]
}
// Todo void TLE8242SetShortBatThreshold (uint8 channel, ShortBatThresholdType sb);
// Todo ShortBatThresholdType TLE8242GetShortBatThreshold (uint8 channel);
// Todo ShortBatRetryType TLE8242GetShortBatRetry (uint8 channel);

//SPI Message #4 - Diagnostic Read (channel 0-3)
//SPI Message #5 - Diagnostic Read (channel 4-7)

bool TLE8242GetShortGround (uint8 channel)
{
    uint8 chip_index, msg_index,channel_index, bit_index;

    chip_index = channel/8;
    channel_index = (channel%8);
    msg_index = channel_index/4;
    bit_index = ((3-channel_index)*6);

    return (bool)TLE8242_au32SpiRx[chip_index].DiagnosticReadchannel[msg_index].data&(ShortGroundBit<<bit_index);
}
bool TLE8242GetShortBat (uint8 channel)
{
    uint8 chip_index, msg_index,channel_index, bit_index;

    chip_index = channel/8;
    channel_index = (channel%8);
    msg_index = channel_index/4;
    bit_index = ((3-channel_index)*6);

    return (bool)TLE8242_au32SpiRx[chip_index].DiagnosticReadchannel[msg_index].data&(ShortBatBit<<bit_index);
}
bool TLE8242GetOFF_TST (uint8 channel)
{
    uint8 chip_index, msg_index,channel_index, bit_index;

    chip_index = channel/8;
    channel_index = (channel%8);
    msg_index = channel_index/4;
    bit_index = ((3-channel_index)*6);

    return (bool)TLE8242_au32SpiRx[chip_index].DiagnosticReadchannel[msg_index].data&(OFFTSTBit<<bit_index);
}
bool TLE8242GetSB_TST (uint8 channel)
{
    uint8 chip_index, msg_index,channel_index, bit_index;

    chip_index = channel/8;
    channel_index = (channel%8);
    msg_index = channel_index/4;
    bit_index = ((3-channel_index)*6);

    return (bool)TLE8242_au32SpiRx[chip_index].DiagnosticReadchannel[msg_index].data&(ShortBatTstBit<<bit_index);
}
bool TLE8242GetOpenLoadGateOn (uint8 channel)
{
    uint8 chip_index, msg_index,channel_index, bit_index;

    chip_index = channel/8;
    channel_index = (channel%8);
    msg_index = channel_index/4;
    bit_index = ((3-channel_index)*6);

    return (bool)TLE8242_au32SpiRx[chip_index].DiagnosticReadchannel[msg_index].data&(OLONBit<<bit_index);
}
bool TLE8242GetOL_OFF (uint8 channel)
{
    uint8 chip_index, msg_index,channel_index, bit_index;

    chip_index = channel/8;
    channel_index = (channel%8);
    msg_index = channel_index/4;
    bit_index = ((3-channel_index)*6);

    return (bool)TLE8242_au32SpiRx[chip_index].DiagnosticReadchannel[msg_index].data&(OLOFFBit<<bit_index);
}

//SPI Message #6 - PWM Offset (channel 0-3)
//SPI Message #7 - PWM Offset (channel 4-7)
//SPI Message #8 - Main Period Set

Tle8242SampleSummMethodType TLE8242GetSampleSummMethod (uint8 channel)
{
    uint8 chip_index, channel_index;

    chip_index = channel/8;
    channel_index = (channel%8);

    return (Tle8242SampleSummMethodType)TLE8242_au32SpiRx[chip_index].MainPeriodSet[channel_index].bits.SAM;
}
void TLE8242SetSampleSummMethod (uint8 channel, Tle8242SampleSummMethodType sam)
{
    uint8 chip_index, channel_index;

    chip_index = channel/8;
    channel_index = (channel%8);

    TLE8242_au32SpiTx[chip_index].MainPeriodSet[channel_index].bits.SAM = sam;
}
void TLE8242SetPWMFrq(uint8 channel, float frq)
{
    uint8  bestm = 0, m, i;
    uint16 bestn = 0, n, divm[4] = { 32, 64, 128, 512 };
    float dis, f, bestdis = frq;
    uint8 endLoop = 0;

    if(TLE8242ChopperFrqMinC > frq)
    {
        frq = TLE8242ChopperFrqMinC;
    }
    else if(TLE8242ChopperFrqMaxC <  frq)
    {
        frq = TLE8242ChopperFrqMaxC;
    }
    bestdis = frq;

    for ( i = 0; i < 4; ++i)
    {
        m = divm[i];
        n = TLE8242FCLK/(frq*m);
            f = TLE8242FCLK / (m * n);
            dis = fabsf(frq - f);
            if (dis < bestdis)
            {
                bestdis = dis;
                bestn = n;
                bestm = i;
            }
        if (dis < 100)
            {
                endLoop = 1;
                break;
            }

        if (1 == endLoop)
        {
            break;
        }
    }
    TLE8242SetDividerN(channel, bestn);
    TLE8242SetDividerM(channel, bestm);

}
float TLE8242GetPWMFrq(uint8 channel)
{

    return (TLE8242FCLK/(TLE8242GetDividerN(channel)*TLE8242GetDividerM(channel)));
}

void TLE8242SetDividerN (uint8 channel, DividerNType dividern)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    TLE8242_au32SpiTx[chip_index].MainPeriodSet[channel_index].bits.DividerN = (dividern>MAX_VALID_DIV_N)?MAX_VALID_DIV_N:dividern;

}
DividerNType TLE8242GetDividerN (uint8 channel)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    return (DividerNType)TLE8242_au32SpiRx[chip_index].MainPeriodSet[channel_index].bits.DividerN;

}
void TLE8242SetDividerM (uint8 channel, DividerMType dividerm)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    TLE8242_au32SpiTx[chip_index].MainPeriodSet[channel_index].bits.DividerM = (dividerm>MAX_VALID_DIV_M)?MAX_VALID_DIV_M:dividerm;

}
DividerMType TLE8242GetDividerM (uint8 channel)
{
    uint8 chip_index, channel_index;
    uint16 divm[4] = { 32, 64, 128, 512 };

    chip_index = channel / 8;
    channel_index = (channel % 8);

    return (DividerMType)(divm[TLE8242_au32SpiRx[chip_index].MainPeriodSet[channel_index].bits.DividerM]);

}

//SPI Message #9 - Control Variable Set (KP and KI)
KPType TLE8242GetKP (uint8 channel)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    return (KPType)TLE8242_au32SpiRx[chip_index].ControlVariableSetKPandKI[channel_index].bits.kp;

}
void TLE8242SetKP (uint8 channel, KPType kp)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    TLE8242_au32SpiTx[chip_index].ControlVariableSetKPandKI[channel_index].bits.kp =  (MAX_VALID_KP < kp)?MAX_VALID_KP:kp;

}
KIType TLE8242GetKI (uint8 channel)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    return (KIType)TLE8242_au32SpiRx[chip_index].ControlVariableSetKPandKI[channel_index].bits.ki;

}
void TLE8242SetKI (uint8 channel, KIType ki)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    TLE8242_au32SpiTx[chip_index].ControlVariableSetKPandKI[channel_index].bits.ki = (MAX_VALID_KI < ki)?MAX_VALID_KI:ki;

}
//SPI Message #10 - Current and Dither Amplitude Set

void TLE8242SetDitherstepsize (uint8 channel, DitherstepsizeType ditherstepsize)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    TLE8242_au32SpiTx[chip_index].CurrentandDitherAmplitudeSet[channel_index].bits.Ditherstepsize = (ditherstepsize>MAX_VALID_CURRENT_SETPOINT)?MAX_VALID_CURRENT_SETPOINT:ditherstepsize;

}
void TLE8242SetOptEnableDeactive (uint8 channel, Tle8242OptEnableDeactiveType en)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    TLE8242_au32SpiTx[chip_index].CurrentandDitherAmplitudeSet[channel_index].bits.EN = en;

}
void TLE8242SetCurrentTarget (uint8 channel, CurrentsetpointType targetCurrent)
{
    uint8 chip_index, channel_index;
    uint16 setpoint = ConvertCurTatToSetPoint(targetCurrent);

    chip_index = channel / 8;
    channel_index = (channel % 8);

    TLE8242_au32SpiTx[chip_index].CurrentandDitherAmplitudeSet[channel_index].bits.Currentsetpoint = (setpoint > MAX_VALID_CURRENT_SETPOINT)?MAX_VALID_CURRENT_SETPOINT:setpoint;

}

CurrentsetpointType TLE8242GetCurrentTarget (uint8 channel)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    return (CurrentsetpointType)ConvertSetPointToCurTar(TLE8242_au32SpiRx[chip_index].CurrentandDitherAmplitudeSet[channel_index].bits.Currentsetpoint);

}
/**********************************************************************************************************************/
/* !FuncName    : TLE8242SetDitherAMPL                                                                                    */
/* !Description :                                  */
/* This function should be called after TLE8242SetDitherFrq(), because the ampl is related to the dither frequency.       */
/* !LastAuthor  : gsun5                                                                                          */
/**********************************************************************************************************************/
void TLE8242SetDitherAMPL(uint8 channel, float target)
{
    uint16 dithstps, setpoint;

    dithstps = TLE8242GetNumberOfSteps(channel);
    setpoint = (uint16)((float)((ConvertCurTatToSetPoint(target/dithstps))*DitherStepRatioToCurrentStepPoint/2)+0.5);
	


    TLE8242SetDitherstepsize(channel, setpoint);

}
float TLE8242GetDitherAMPL(uint8 channel)
{
    uint16 dithstps;
    float target;

    dithstps = TLE8242GetNumberOfSteps(channel);
    //target = (ConvertSetPointToCurTar(TLE8242GetDitherstepsize(channel)) / DitherStepRatioToCurrentStepPoint);
	target = (ConvertSetPointToCurTar2(TLE8242GetDitherstepsize(channel) * dithstps));
    return target;
}

DitherstepsizeType TLE8242GetDitherstepsize (uint8 channel)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    return (DitherstepsizeType)TLE8242_au32SpiRx[chip_index].CurrentandDitherAmplitudeSet[channel_index].bits.Ditherstepsize;

}
Tle8242OptEnableDeactiveType TLE8242GetOptEnableDeactive (uint8 channel)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    return (Tle8242OptEnableDeactiveType)TLE8242_au32SpiRx[chip_index].CurrentandDitherAmplitudeSet[channel_index].bits.EN;

}

//SPI Message #11 - Dither Period Set

void TLE8242SetDitherFrq(uint8 channel, float frq)
{
    uint16 dithstps;
    float pwmfrq;

    if (0 == frq)
    {
        dithstps = 0;
    }
    else
    {
    pwmfrq = TLE8242GetPWMFrq(channel);
    dithstps = (pwmfrq / (frq * 4)) + 0.5;
    }

    TLE8242SetNumberOfSteps(channel, dithstps);
}

float TLE8242GetDitherFrq(uint8 channel)
{
    uint16 dithstps;
    float pwmfrq, dithfrq;

    pwmfrq = TLE8242GetPWMFrq(channel);
    dithstps = TLE8242GetNumberOfSteps(channel);
    dithfrq = (pwmfrq / (dithstps * 4));
    return dithfrq;
}

uint8 TLE8242GetNumberOfSteps(uint8 channel)
{
    uint8 chip_index, channel_index;
    uint8 steps;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    steps = TLE8242_au32SpiRx[chip_index].DitherPeriodSet[channel_index].bits.Numberofsteps;
    if(0 == steps)
    {
        steps = TLE8242_au32SpiTx[chip_index].DitherPeriodSet[channel_index].bits.Numberofsteps;
    }
    return steps;
}
void TLE8242SetNumberOfSteps(uint8 channel, uint8 numberofsteps)
{
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);
    TLE8242_au32SpiTx[chip_index].DitherPeriodSet[channel_index].bits.Numberofsteps = (numberofsteps>MAX_VALID_DITHER_STEPS)?MAX_VALID_DITHER_STEPS:numberofsteps;
}

bool TLE8242GetDitherEnabled(uint8 channel)
{
    uint16 ditherstep, ditherampl;
    bool enable = 0;

    ditherstep = TLE8242GetNumberOfSteps(channel);
    ditherampl = TLE8242GetDitherAMPL(channel);
	

    if((0 == ditherstep) || (0 == ditherampl))
    {

		enable = 0;
    }
    else
    {
        enable = 1;
    }
    return enable;
}

//SPI Message #12 - Max / Min Current Read
//SPI Message #13 - Average Current Read Over Dither Period

float TLE8242GetCurrentFeedback(uint8 channel, Tle8242CurrentType type)
{
    bool ditherenable;
    Tle8242ControlModeType mode;
    float feedback;
    uint8 chip_index, channel_index;
    uint16  ratio;
	uint32 currentraw = 0; 

    chip_index = channel / 8;
    channel_index = (channel % 8);
    ditherenable = TLE8242GetDitherEnabled(channel);
    mode = TLE8242GetControlMode(channel);

    switch (type)
    {
    case MinCurrent:
        currentraw = TLE8242_au32SpiRx[chip_index].MaxMinCurrentRead[channel_index].bits.Min;
        break;
    case MaxCurrent:
        currentraw = TLE8242_au32SpiRx[chip_index].MaxMinCurrentRead[channel_index].bits.Max;
        break;
    case AvgCurrent:
        currentraw = TLE8242_au32SpiRx[chip_index].AverageCurrentReadOverDitherPeriod[channel_index].bits.AverageDitherCurrent;
        break;
    default:
        break;
    }

    if ((DirectPWM == mode) && (512 == TLE8242GetDividerM(channel)))
    {
        if (AvgCurrent == type)
        {
            if (ditherenable)
            {
                uint8 steps = TLE8242GetNumberOfSteps(channel);

                ratio = 16 * 4 * steps;				
            }
            else
            {
                ratio = 16;
            }
        }
        else
        {
            ratio = 4;
        }
    }
    else
    {
        if (AvgCurrent == type)
        {
            if (ditherenable)
            {
                uint8 steps = TLE8242GetNumberOfSteps(channel);

                ratio = (16 * steps);				
            }
            else
            {
                ratio = (4);
            }
        }
        else
        {
            ratio = 1;
        }		
    }
    feedback = ConvertSetPointToCurTar(currentraw) / ratio ;

    return feedback;
}
Tle8242ValidType TLE8242GetCurValid(uint8 channel, Tle8242CurrentType type)
{
    Tle8242ValidType valid = 0;
    uint8 chip_index, channel_index;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    switch (type)
    {
    case MinCurrent:
        valid = TLE8242_au32SpiRx[chip_index].MaxMinCurrentRead[channel_index].bits.Valid;
        break;
    case MaxCurrent:
        valid = TLE8242_au32SpiRx[chip_index].MaxMinCurrentRead[channel_index].bits.Valid;
        break;
    case AvgCurrent:
        valid = TLE8242_au32SpiRx[chip_index].AverageCurrentReadOverDitherPeriod[channel_index].bits.Valid;
        break;
    default:
        break;
    }
    return valid;
}
//SPI Message #14 - Autozero Trigger / Read
//SPI Message #15 - PWM Duty Cycle
void TLE8242SetPWMDutyCycle(uint8 channel, float duty)
{

        uint8 chip_index, channel_index;
        uint32 m,n;

        chip_index = channel / 8;
        channel_index = (channel % 8);

        m = 32;
        n = TLE8242GetDividerN(channel);

        TLE8242_au32SpiTx[chip_index].PWMDutyCycle[channel_index].bits.Pwmdutycycle = m*n*duty;

}

float TLE8242GetPWMDutyCycle(uint8 channel)
{
    uint8 chip_index, channel_index;
    uint32 m,n, duty_raw;
    float duty;

    chip_index = channel / 8;
    channel_index = (channel % 8);

    if (CurrentControl == TLE8242GetControlMode(channel))
    {
    m = TLE8242GetDividerM(channel);
    }
    else
    {
        m = 32;
    }
    n = TLE8242GetDividerN(channel);

    duty_raw = TLE8242_au32SpiTx[chip_index].PWMDutyCycle[channel_index].bits.Pwmdutycycle;

    duty = duty_raw/(m*n);

    return duty;

}
//SPI Message #16 - Current Profile Detection Setup 1
//SPI Message #17 - Current Profile Detection Setup 2
//SPI Message #18 - Current Profile Detection Feedback
//SPI Message #19 - Read Generic Flag Bits
bool TLE8242GetGenericFalg(uint8 channel, Tle8242GenericFlagType type)
{
    uint8 chip_index;
    bool res;

    chip_index = channel / 8;

    switch (type)
    {
    case GenericOverVol:
        res = TLE8242_au32SpiRx[chip_index].ReadGenericFlagBits.bits.OV;
        break;
    case GenericPhaseSync:
        res = TLE8242_au32SpiRx[chip_index].ReadGenericFlagBits.bits.PS;
        break;
    case GenericEnable:
        res = TLE8242_au32SpiRx[chip_index].ReadGenericFlagBits.bits.RB_L;
        break;
    case GenericReset:
        res = TLE8242_au32SpiRx[chip_index].ReadGenericFlagBits.bits.RB_L;
        break;
    default:
        res = 0;
        break;
    }

    return res;
}

#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"
//end





