/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : Framework                                               */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : IFXSCUCCU.c                                             */
/* !Description     : Framework component managing CCU                        */
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

/******************************************************************************/
#include "IfxScuCcu.h"
#include "IfxScuWdt.h"
#include "IfxStm_reg.h"

/******************************************************************************/

/** \brief Timeout count for the oscillator stability check wait loop.
 *
 */
#define IFXSCUCCU_OSC_STABLECHK_TIME      640U    /*Oscillator stability check timeout count */

/******************************************************************************/
/*                             Prototypes                                     */
/******************************************************************************/
#define IFXSCU_START_SEC_CODE
#include "IFXSCU_MemMap.h"

static void IfxScuCcu_wait (float32 time);
static boolean IfxScuCcu_isOscillatorStable (void);

#define IFXSCU_STOP_SEC_CODE
#include "IFXSCU_MemMap.h"

/******************************************************************************/
/*                          Default Configuration                             */
/******************************************************************************/

#define IFXSCU_START_SEC_CONST_UNSPECIFIED
#include "IFXSCU_MemMap.h"

static const IfxScu_PllStepsConfig pllConfigSteps[] = IFXSCU_CFG_PLL_STEPS;

const IfxScuCcu_Config clockConfig = {
    sizeof (pllConfigSteps) / sizeof (IfxScu_PllStepsConfig),
    (IfxScu_PllStepsConfig *) pllConfigSteps,
    IFXSCU_CFG_PLL_INITIAL_STEP,
    IFXSCU_CFG_CLK_DISTRIBUTION
};

#define IFXSCU_STOP_SEC_CONST_UNSPECIFIED
#include "IFXSCU_MemMap.h"

/******************************************************************************/
/*                           Function                                         */
/******************************************************************************/
#define IFXSCU_START_SEC_CODE
#include "IFXSCU_MemMap.h"

/** \brief get source frequency fSOURCE.
 *
 */
float32 IfxScuCcu_getSourceFrequency (void)
{
    float32 sourcefreq;
    switch (MODULE_SCU.CCUCON0.B.CLKSEL)
    {
    case IfxScu_CCUCON0_CLKSEL_fBack:
        sourcefreq = IfxScuCcu_getEvrFrequency ();
        break;
    case IfxScu_CCUCON0_CLKSEL_fPll:
        sourcefreq = IfxScuCcu_getPllFrequency ();
        break;
    default:
        sourcefreq = 0;
        break;
    }
    return sourcefreq;
}

/** \brief Return the CPU frequency
 *
 */
float32 IfxScuCcu_getCpuFrequency (IfxCpu_ResourceCpu cpu)
{
    float32 frequency = IfxScuCcu_getSriFrequency();
    uint8 cpuDiv = 0;
    switch (cpu)
    {
    case IfxCpu_ResourceCpu_0:
        cpuDiv = MODULE_SCU.CCUCON6.U;
        break;
    default:
        frequency = 0.0;
        break;
    }
    if (cpuDiv != 0)
    {
        frequency = frequency * (cpuDiv / 64);
    }
    return frequency;
}

/** \brief Return the EVR frequency
 *
 */
float32 IfxScuCcu_getEvrFrequency (void)
{
    return IFXSCU_EVR_OSC_FREQUENCY;
}

/** \brief Return the Fmax frequency
 *
 */
float32 IfxScuCcu_getFmaxFrequency (void)   /*TODO this name to be changed to IfxScuCcu_getMaxFrequency */
{
    float32 maxFrequency;
    switch (MODULE_SCU.CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */
        if (MODULE_SCU.CCUCON5.B.MAXDIV == 0)
        {
            maxFrequency = IfxScuCcu_getSourceFrequency ();
        }
        else
            maxFrequency = IfxScuCcu_getSourceFrequency () / MODULE_SCU.CCUCON5.B.MAXDIV;
        break;
    case 1:
        maxFrequency = IfxScuCcu_getSourceFrequency () / 15;
        break;
    case 2:
        maxFrequency = IfxScuCcu_getSourceFrequency () / 30;
        break;
    case 3:
        maxFrequency = IfxScuCcu_getSourceFrequency () / 60;
        break;
    case 4:
        maxFrequency = IfxScuCcu_getSourceFrequency () / 120;
        break;
    default:
        maxFrequency = 0.0;
        break;
    }
    return maxFrequency;
}

/** \brief Return the FSI frequency in Hz.
 *
 */
float32 IfxScuCcu_getFsiFrequency (void)
{
    float32 frequency;
    Ifx_SCU_CCUCON0 ccucon0 = MODULE_SCU.CCUCON0;
    if (ccucon0.B.FSIDIV == 0)
    {
        frequency = 0;
    }
    else
    {
        frequency = IfxScuCcu_getSriFrequency ();
        if ((ccucon0.B.FSIDIV == 1) || (ccucon0.B.SRIDIV == 1) || (ccucon0.B.SRIDIV == 2))
        {
            frequency = frequency / ccucon0.B.FSIDIV;
        }
    }
    return frequency;
}

/** \brief Return the FSI2 frequency in Hz.
 *
 */
float32 IfxScuCcu_getFsi2Frequency (void)
{
    float32 frequency;
    Ifx_SCU_CCUCON0 ccucon0 = MODULE_SCU.CCUCON0;
    if (ccucon0.B.FSIDIV == 0)
    {
        frequency = 0;
    }
    else
    {
        frequency = IfxScuCcu_getSriFrequency ();
        if ((ccucon0.B.FSIDIV == 1) || (ccucon0.B.SRIDIV == 1) || (ccucon0.B.SRIDIV == 2))
        {
            frequency = frequency / ccucon0.B.FSIDIV;
        }
    }
    return frequency;
}



/** \brief Return the fosc frequency.
 *
 */
float32 IfxScuCcu_getOscFrequency (void)
{
    if (MODULE_SCU.CCUCON1.B.INSEL == IfxScu_CCUCON1_INSEL_fOsc1)
    {
        return IFXSCU_EVR_OSC_FREQUENCY;
    }
    else if (MODULE_SCU.CCUCON1.B.INSEL == IfxScu_CCUCON1_INSEL_fOsc0)
    {
        return IFX_CFG_SCU_XTAL_FREQUENCY;
    }
    else
    {
        /* Reserved values, this */
        return 0.0;
    }
}

/** \brief Return the fosc0 frequency.
 *
 */
float32 IfxScuCcu_getOsc0Frequency (void)
{
    return IFX_CFG_SCU_XTAL_FREQUENCY;
}

/** \brief Return the system PLL frequency.
 *
 */
float32 IfxScuCcu_getPllFrequency (void)
{
    Ifx_SCU *scu = &MODULE_SCU;
    float32 oscFreq;
    float32 freq;

    oscFreq = IfxScuCcu_getOscFrequency ();

    if (scu->PLLSTAT.B.VCOBYST == 1)
    {
        /* Prescaler mode */
        freq = oscFreq / (scu->PLLCON1.B.K1DIV + 1);
    }
    else if (scu->PLLSTAT.B.FINDIS == 1)
    {
        /* Free running mode */
        freq = IFXSCU_VCO_BASE_FREQUENCY / (scu->PLLCON1.B.K2DIV + 1);
    }
    else
    {
        /* Normal mode */
        freq = (oscFreq * (scu->PLLCON0.B.NDIV + 1)) / ((scu->PLLCON1.B.K2DIV + 1) * (scu->PLLCON0.B.PDIV + 1));
    }
    return freq;
}

/** \brief get PLL VCO frequency.
 *
 */
float32 IfxScuCcu_getPllVcoFrequency (void)
{
    float32 vcoFreq;

    if (MODULE_SCU.PLLSTAT.B.FINDIS == 1)
    {
        /* Free running mode */
        vcoFreq = IFXSCU_VCO_BASE_FREQUENCY;
    }
    else
    {
        /* Normal mode */
        vcoFreq = (IfxScuCcu_getOscFrequency () * (MODULE_SCU.PLLCON0.B.NDIV + 1)) / (MODULE_SCU.PLLCON0.B.PDIV + 1);
    }
    return vcoFreq;
}

/** \brief get K3 divider for the PLL module.
 *
 */
float32 IfxScuCcu_getPll2Frequency ()
{
    float32 pll2Frequency;

    pll2Frequency = IfxScuCcu_getPllVcoFrequency () / (SCU_PLLERAYCON1.B.K3DIV + 1);

    return pll2Frequency;
}


/** \brief set K3 divider for the PLL module.
 *
 */
float32 IfxScuCcu_setPll2Frequency (float32 pll2Freq)
{
    uint16 endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword ();
    uint32 pll2Div = (uint32) ((IfxScuCcu_getPllVcoFrequency () / pll2Freq) - 1);
    {
        IfxScuWdt_clearSafetyEndinit (endinitSfty_pw);
        SCU_PLLCON1.B.K3DIV = pll2Div;
        IfxScuWdt_setSafetyEndinit (endinitSfty_pw);
    }
    return IfxScuCcu_getPll2Frequency ();
}

/** \brief Return the ERAY PLL frequency.
 *
 */
float32 IfxScuCcu_getPllErayFrequency (void)
{
    Ifx_SCU *scu = &MODULE_SCU;
    float32 oscFreq;
    float32 freq;

    oscFreq = IfxScuCcu_getOscFrequency ();

    if (scu->PLLERAYSTAT.B.VCOBYST == 1)
    {
        /* Prescaler mode */
        freq = oscFreq / (scu->PLLERAYCON1.B.K1DIV + 1);
    }
    else if (scu->PLLERAYSTAT.B.FINDIS == 1)
    {
        /* Free running mode */
        freq = IFXSCU_VCO_BASE_FREQUENCY / (scu->PLLERAYCON1.B.K2DIV + 1);
    }
    else
    {
        /* Normal mode */
        freq = (oscFreq * (scu->PLLERAYCON0.B.NDIV + 1)) / (scu->PLLERAYCON1.B.K2DIV + 1);
    }
    return freq;
}

/** \brief Return the system timer frequency.
 *
 */
float32 IfxScuCcu_getStmFrequency (void)
{
    float32 freq;
    uint32 stmdiv = MODULE_SCU.CCUCON1.B.STMDIV;
    freq = IfxScuCcu_getFmaxFrequency () / stmdiv;

    return freq;
}

/** \brief Return the SPB frequency.
 *
 */
float32 IfxScuCcu_getSpbFrequency (void)
{
    float32 spbFrequency;
    switch (MODULE_SCU.CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */
        if ((MODULE_SCU.CCUCON0.B.SPBDIV == 0) || (MODULE_SCU.CCUCON0.B.SPBDIV == 1))
        {
            spbFrequency = 0.0;
        }
        else
        {
            spbFrequency = IfxScuCcu_getSourceFrequency () / MODULE_SCU.CCUCON0.B.SPBDIV;
        }
        break;
    case 1:
        spbFrequency = IfxScuCcu_getSourceFrequency () / 30;
        break;
    case 2:
        spbFrequency = IfxScuCcu_getSourceFrequency () / 60;
        break;
    case 3:
        spbFrequency = IfxScuCcu_getSourceFrequency () / 120;
        break;
    case 4:
        spbFrequency = IfxScuCcu_getSourceFrequency () / 240;
        break;
    default:
        spbFrequency = 0.0;
        break;
    }
    return spbFrequency;
}

/** \brief Return the BBB frequency.
 *
 */
float32 IfxScuCcu_getBbbFrequency (void)
{
    float32 bbbFrequency;
    switch (MODULE_SCU.CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */
        if (MODULE_SCU.CCUCON2.B.BBBDIV == 0)
        {
            bbbFrequency = 0.0;
        }
        else
        {
            bbbFrequency = IfxScuCcu_getSourceFrequency () / MODULE_SCU.CCUCON2.B.BBBDIV;
        }
        break;
    case 1:
        bbbFrequency = IfxScuCcu_getSourceFrequency () / 30;
        break;
    case 2:
        bbbFrequency = IfxScuCcu_getSourceFrequency () / 60;
        break;
    case 3:
        bbbFrequency = IfxScuCcu_getSourceFrequency () / 120;
        break;
    case 4:
        bbbFrequency = IfxScuCcu_getSourceFrequency () / 240;
        break;
    default:
        bbbFrequency = 0.0;
        break;
    }
    return bbbFrequency;
}

/** \brief Return the Baud1 frequency in Hz.
 *
 */
//<<float32 IfxScuCcu_getBaud1Frequency (void)
//<<{
//<<    float32 frequency;
//<<    Ifx_SCU_CCUCON0 ccucon0 = MODULE_SCU.CCUCON0;
//<<    if (ccucon0.B.BAUD1DIV == 0)
//<<    {
//<<        frequency = 0;
//<<    }
//<<    else
//<<    {
//<<        frequency = IfxScuCcu_getFmaxFrequency () / ccucon0.B.BAUD1DIV;
//<<    }
//<<    return frequency;
//<<}


/** \brief Return the Baud2 frequency in Hz.
 *
 */
float32 IfxScuCcu_getBaud2Frequency (void)
{
    float32 frequency;
    Ifx_SCU_CCUCON0 ccucon0 = MODULE_SCU.CCUCON0;
    if (ccucon0.B.BAUD2DIV == 0)
    {
        frequency = 0;
    }
    else
    {
        frequency = IfxScuCcu_getFmaxFrequency () / ccucon0.B.BAUD2DIV;
    }
    return frequency;
}


/** \brief Return the SRI frequency in Hz.
 *
 */
float32 IfxScuCcu_getSriFrequency (void)
{
    float32 sriFrequency;
    switch (MODULE_SCU.CCUCON0.B.LPDIV)
    {
    case 0:                    /*Not in low power mode */
        if (MODULE_SCU.CCUCON0.B.SRIDIV == 0)
        {
            sriFrequency = 0.0;
        }
        else
        {
            sriFrequency = IfxScuCcu_getSourceFrequency () / MODULE_SCU.CCUCON0.B.SRIDIV;
        }
        break;
    case 1:
        sriFrequency = IfxScuCcu_getSourceFrequency () / 30;
        break;
    case 2:
        sriFrequency = IfxScuCcu_getSourceFrequency () / 60;
        break;
    case 3:
        sriFrequency = IfxScuCcu_getSourceFrequency () / 120;
        break;
    case 4:
        sriFrequency = IfxScuCcu_getSourceFrequency () / 240;
        break;
    default:
        sriFrequency = 0.0;
        break;
    }
    return sriFrequency;
}

/** \brief Set the SPB frequency.
 *
 */
float32 IfxScuCcu_setCpuFrequency (IfxCpu_ResourceCpu cpu, float32 cpuFreq)
{
   uint16 endinitSfty_pw;
   float32 sriFreq;
   uint32 cpuDiv;

   sriFreq = IfxScuCcu_getSriFrequency();

   if (cpuFreq >= sriFreq)
   {
      cpuDiv = 0;
   }
   else
   {
      cpuDiv = (cpuFreq * 64) / sriFreq;
   }

   endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword();

   {
      IfxScuWdt_clearSafetyEndinit(endinitSfty_pw);

      switch (cpu) {
      case IfxCpu_ResourceCpu_0:
         MODULE_SCU .CCUCON6.U = cpuDiv;
         break;
      default:
         break;
      }

      IfxScuWdt_setSafetyEndinit(endinitSfty_pw);
   }
   if (cpuDiv != 0)
   {
      sriFreq = sriFreq * (cpuDiv / 64);
   }
   return sriFreq;
}


/** \brief Set the SPB frequency.
 *
 */
float32 IfxScuCcu_setSpbFrequency (float32 spbFreq)
{
    /* TODO: check whether it is necessary to disable trap and/or the safety */
    uint16 l_EndInitPW;
    uint16 l_SEndInitPW;
    float32 inputFreq = IfxScuCcu_getSourceFrequency ();
    uint32 spbDiv = inputFreq / spbFreq;
    spbDiv = __maxu (spbDiv, 2);
    spbDiv = spbDiv & 0x2U;     /* only even dividers */

    l_EndInitPW = IfxScuWdt_getCpuWatchdogPassword ();
    l_SEndInitPW = IfxScuWdt_getSafetyWatchdogPassword ();

    IfxScuWdt_clearCpuEndinit (l_EndInitPW);
    SCU_TRAPDIS.U = SCU_TRAPDIS.U | 0x3E0;
    IfxScuWdt_setCpuEndinit (l_EndInitPW);

    IfxScuWdt_clearSafetyEndinit (l_SEndInitPW);
    SCU_CCUCON0.B.SPBDIV = spbDiv;
    IfxScuWdt_setSafetyEndinit (l_SEndInitPW);

    IfxScuWdt_clearCpuEndinit (l_EndInitPW);
    SCU_TRAPDIS.U = SCU_TRAPDIS.U & ~0x3E0;
    IfxScuWdt_setCpuEndinit (l_EndInitPW);

    return IfxScuCcu_getSpbFrequency ();
}

/** \brief Compute the fractional divider register.
 *
 * \param moduleFreq Specifies the requested module frequency in Hz
 * \param realModuleFreq This parameter is set by the function to the module frequency (Hz)
 * coresponding to the returned fdr value.
 *
 * \return fdr register value.
 */
uint32 IfxScuCcu_calculateFDR (float32 moduleFreq, float32 * realModuleFreq)
{
    uint32 stepN, stepF;
    boolean normalDiv;
    float32 freqN, freqF;
    Ifx_SCU_FDR fdr;
    fdr.U = 0;
    float32 fsys = IfxScuCcu_getSpbFrequency ();

    /* Normal divider mode */
    stepN = (uint32) __minf (__maxf (0, 1024.0 - (fsys / moduleFreq)), 1023);
    freqN = fsys / (1024 - stepN);

    /* Fractional divider mode */
    stepF = (uint32) __minf (((moduleFreq * 1024) / fsys), 1023);
    freqF = (fsys * stepF) / 1024;

    normalDiv = (__absf (moduleFreq - freqN) <= __absf (moduleFreq - freqF));
    *realModuleFreq = (normalDiv != 0) ? freqN : freqF;
    fdr.B.STEP = (normalDiv != 0) ? stepN : stepF;
    fdr.B.DM = (normalDiv != 0) ? 1 : 2;
    return fdr.U;
}

float32 IfxScuCcu_getModuleFrequency (uint32 fdrU)
{
    float32 fsys = IfxScuCcu_getSpbFrequency ();
    float32 result;
    Ifx_SCU_FDR fdr;
    fdr.U = fdrU;
    if (fdr.B.DM == 1)
    {
        result = fsys / (1024 - fdr.B.STEP);
    }
    else if (fdr.B.DM == 2)
    {
        result = (fsys * fdr.B.STEP) / 1024;
    }
    else
    {
        result = 0;
    }
    return result;
}

/** \brief API to initialize the SCU Clock Control Unit.
 *
 */
boolean IfxScuCcu_init (const IfxScuCcu_Config * cfg)
{
    uint8 smuTrapEnable;
    uint16 endinit_pw, endinitSfty_pw;
    boolean status = 0;

    endinit_pw = IfxScuWdt_getCpuWatchdogPassword ();
    endinitSfty_pw = IfxScuWdt_getSafetyWatchdogPassword ();

    {                           /* Disable TRAP for SMU (oscillator watchdog and unlock detection) */
        IfxScuWdt_clearCpuEndinit (endinit_pw);
        smuTrapEnable = SCU_TRAPDIS.B.SMUT;
        SCU_TRAPDIS.B.SMUT = 1U;
        IfxScuWdt_setCpuEndinit (endinit_pw);
    }

    {                           /* Select fback (fosc-evr) as CCU input clock */
        IfxScuWdt_clearSafetyEndinit (endinitSfty_pw);

        while (SCU_CCUCON0.B.LCK)
        {                       /*Wait till ccucon0 lock is set */
            /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
        }
        SCU_CCUCON0.B.CLKSEL = 0;   /*Select the EVR as fOSC for the clock distribution*/
        SCU_CCUCON0.B.UP = 1;   /*Update the ccucon0 register */

        /* Disconnet PLL (SETFINDIS=1): oscillator clock is disconnected from PLL */
        SCU_PLLCON0.B.SETFINDIS = 1;
        /*Now PLL is in free running mode*/

        /* Select Clock Source as PLL input clock */
        while (SCU_CCUCON0.B.LCK)
        {                       /*Wait till ccucon0 lock is set */
            /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
        }
        SCU_CCUCON1.B.INSEL = 1;    /*Select oscillator OSC0 as clock to PLL */
        SCU_CCUCON1.B.UP = 1;   /*Update the ccucon0 register */

        status |= IfxScuCcu_isOscillatorStable ();

        IfxScuWdt_setSafetyEndinit (endinitSfty_pw);
    }

    if (status == 0)
    {                           /*Start the PLL configuration sequence */
        uint8 pllStepsCount;

        /*Setting up P N and K2 values equate pll to evr osc freq */
        {
            {                   /*Set the K2 divider value for the step corresponding to step count */
                IfxScuWdt_clearSafetyEndinit (endinitSfty_pw);

                while (!SCU_PLLSTAT.B.K2RDY)
                {               /*Wait until K2 divider is ready */
                    /*No "timeout" required because Safety Endinit will give a trap */
                }

                SCU_PLLCON1.B.K2DIV = cfg->pllInitialStep.k2Initial;

                if ((SCU_PLLCON0.B.PDIV != cfg->pllInitialStep.pDivider) ||
                    (SCU_PLLCON0.B.NDIV != cfg->pllInitialStep.nDivider))
                {
                    /*change P and N divider values */
                    SCU_PLLCON0.B.PDIV = cfg->pllInitialStep.pDivider;
                    SCU_PLLCON0.B.NDIV = cfg->pllInitialStep.nDivider;

                    /* Disable oscillator disconnect feature
                     * in case of PLL unlock, PLL stays connected to fref */
                    SCU_PLLCON0.B.OSCDISCDIS = 1;
                    /* Connect PLL to fREF as oscillator clock is connected to PLL   */
                    SCU_PLLCON0.B.CLRFINDIS = 1;

                    IfxScuCcu_wait (0.000050F); /*Wait for 50us */

                    /* Restart PLL lock detection (RESLD = 1) */
                    SCU_PLLCON0.B.RESLD = 1;

                    while (!SCU_PLLSTAT.B.VCOLOCK)
                    {           /* Wait for PLL lock */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }

                    SCU_PLLCON0.B.VCOBYP = 0;   /*VCO bypass disabled */

                    while (SCU_CCUCON0.B.LCK)
                    {           /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }
                    SCU_CCUCON0.B.CLKSEL = 0x01;
                    /*Configure the clock distribution */
                    while (SCU_CCUCON0.B.LCK)
                    {           /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }
                    {           /*Write CCUCON0 configuration */
                        Ifx_SCU_CCUCON0 ccucon0;
                        ccucon0.U = SCU_CCUCON0.U & ~cfg->clockDistribution.ccucon0.mask;
                        /*update with configured value */
                        ccucon0.U |= (cfg->clockDistribution.ccucon0.mask & cfg->clockDistribution.ccucon0.value);
                        ccucon0.B.CLKSEL = 0x01;    /*  Select fpll as CCU input clock, even if this was not selected by configuration */
                        ccucon0.B.UP = 1;
                        SCU_CCUCON0 = ccucon0;
                    }

                    while (SCU_CCUCON1.B.LCK)
                    {           /*Wait till ccucon registers can be written with new value */
                        /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                    }
                    {           /*Write CCUCON1 configuration */
                        Ifx_SCU_CCUCON1 ccucon1;
                        ccucon1.U = SCU_CCUCON1.U & ~cfg->clockDistribution.ccucon1.mask;
                        /*update with configured value */
                        ccucon1.U |= (cfg->clockDistribution.ccucon1.mask & cfg->clockDistribution.ccucon1.value);
                        ccucon1.B.INSEL = 1;
                        ccucon1.B.UP = 1;
                        SCU_CCUCON1 = ccucon1;
                    }
                    IfxScuCcu_wait (cfg->pllInitialStep.waitTime);  /*Wait for configured initial time */

                    {           /*Write CCUCON2 configuration */
                        Ifx_SCU_CCUCON2 ccucon2;
                        ccucon2.U = SCU_CCUCON2.U & ~cfg->clockDistribution.ccucon2.mask;
                        /*update with configured value */
                        ccucon2.U |= (cfg->clockDistribution.ccucon2.mask & cfg->clockDistribution.ccucon2.value);
                        SCU_CCUCON2 = ccucon2;
                    }

                    {           /*Write CCUCON5 configuration */
                        Ifx_SCU_CCUCON5 ccucon5;
                        ccucon5.U = SCU_CCUCON5.U & ~cfg->clockDistribution.ccucon5.mask;
                        /*update with configured value */
                        ccucon5.U |= (cfg->clockDistribution.ccucon5.mask & cfg->clockDistribution.ccucon5.value);
                        SCU_CCUCON5 = ccucon5;
                    }

                    {           /*Write CCUCON6 configuration */
                        Ifx_SCU_CCUCON6 ccucon6;
                        ccucon6.U = SCU_CCUCON6.U & ~cfg->clockDistribution.ccucon6.mask;
                        /*update with configured value */
                        ccucon6.U |= (cfg->clockDistribution.ccucon6.mask & cfg->clockDistribution.ccucon6.value);
                        SCU_CCUCON6 = ccucon6;
                    }
                }

                IfxScuWdt_setSafetyEndinit (endinitSfty_pw);
            }

        }

        /*Start Pll ramp up sequence */
        for (pllStepsCount = 0; pllStepsCount < cfg->numOfPllDividerSteps; pllStepsCount++)
        {                       /*iterate through number of pll steps */
            {
                IfxScuWdt_clearSafetyEndinit (endinitSfty_pw);
                /*Configure K2 divider */
                while (!SCU_PLLSTAT.B.K2RDY)
                {               /*Wait until K2 divider is ready */
                    /*No "timeout" required, because if it hangs, Safety Endinit will give a trap */
                }

                /*Now set the K2 divider value for the step corresponding to step count */
                SCU_PLLCON1.B.K2DIV = cfg->pllDividerStep[pllStepsCount].k2Step;
                IfxScuWdt_setSafetyEndinit (endinitSfty_pw);
            }

            /*call the hook function if configured */
            if (cfg->pllDividerStep[pllStepsCount].hookFunction != (IfxScu_PllStepsFunctionHook) 0)
            {
                cfg->pllDividerStep[pllStepsCount].hookFunction ();
            }
            /*Wait for waitCounter corresponding to the pll step */
            IfxScuCcu_wait (cfg->pllDividerStep[pllStepsCount].waitTime);
        }
    }
    {                           /* Enable oscillator disconnect feature */
        IfxScuWdt_clearSafetyEndinit (endinitSfty_pw);
        SCU_PLLCON0.B.OSCDISCDIS = 0U;
        IfxScuWdt_setSafetyEndinit (endinitSfty_pw);
    }
    {                           /* Enable VCO unlock Trap if it was disabled before */
        IfxScuWdt_clearCpuEndinit (endinit_pw);
        SCU_TRAPDIS.B.SMUT = smuTrapEnable;
        IfxScuWdt_setCpuEndinit (endinit_pw);
    }
    return status;
}

/** \brief Check if oscillator is stable.
 *
 */
static boolean IfxScuCcu_isOscillatorStable (void)
{
    uint16 endinitPw = IfxScuWdt_getCpuWatchdogPassword ();
    sint32 TimeoutCtr = IFXSCUCCU_OSC_STABLECHK_TIME;
    boolean status = 0;

    /* Mode External Crystal / Ceramic Resonator Mode and External Input Clock.
     * The oscillator Power-Saving Mode is not entered
     */
    SCU_OSCCON.B.MODE = 0U;
    SCU_OSCCON.B.OSCVAL = 7;

    /* The Oscillator Watchdog of the PLL is cleared and restarted */
    SCU_OSCCON.B.OSCRES = 1U;

    /* wait until PLLLV and PLLHV flags are set */
    while ((SCU_OSCCON.B.PLLLV == 0) || (SCU_OSCCON.B.PLLHV == 0))
    {
        if ((--TimeoutCtr) == 0)
        {
            status = 1;
            break;
        }
    }

    {                           /* clear and then set SMU trap (oscillator watchdog and unlock detection) */
        IfxScuWdt_clearCpuEndinit (endinitPw);
        SCU_TRAPCLR.B.SMUT = 1U;    /* TODO Can this be removed? */
        SCU_TRAPDIS.B.SMUT = 1U;    /* TODO Can this be removed? */
        IfxScuWdt_setCpuEndinit (endinitPw);
    }
    return status;
}

/*IfxScuCcu_wait shall not use STM in future, because we can guarantee that STM is enabled after reset but
 * If PLL init is called for changing the frequency during runtime, there is no guarantee that STM is enabled*/
static void IfxScuCcu_wait (float32 time)
{
    uint32 stmCount = (uint32) (IfxScuCcu_getStmFrequency () * time);
    uint32 stmCountBegin = STM0_TIM0.U;
    while ((uint32) (STM0_TIM0.U - stmCountBegin) < stmCount)
    {
        /* There is no need to check overflow of the STM timer.
         * When counter after overflow subtracted with counter before overflow,
         * the subtraction result will be as expected, as long as both are unsigned 32 bits
         * eg: stmCountBegin= 0xFFFFFFFE (before overflow)
         *     stmCountNow = 0x00000002 (before overflow)
         *     diff= stmCountNow - stmCountBegin = 4 as expected.*/
    }
}

#define IFXSCU_STOP_SEC_CODE
#include "IFXSCU_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
