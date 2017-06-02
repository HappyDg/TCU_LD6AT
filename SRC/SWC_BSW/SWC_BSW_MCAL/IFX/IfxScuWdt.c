/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : Framework                                               */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : IFXSCUWDT.c                                             */
/* !Description     : Framework component managing WDT                        */
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

#include "IfxScuWdt.h"
#include "IfxCpu.h"

/**
 * \brief Reset password of watchdog module.
 */
#define IFXSCUWDT_RESET_PASSWORD        (0x3CU)

/******************************************************************************/
/*                           Function prototypes                              */
/******************************************************************************/
#define IFXSCU_START_SEC_CODE
#include "IFXSCU_MemMap.h"

void IfxScuWdt_initConfig (IfxScuWdt_Config * p_cfg)
{
    p_cfg->password = IFXSCUWDT_RESET_PASSWORD;
    p_cfg->reload = 0xFFFC;
    p_cfg->inputFrequency = IfxScu_WDTCON1_IR_divBy16384;
    p_cfg->disableWatchdog = FALSE;
    p_cfg->enableSmuRestriction = FALSE;
    p_cfg->enableAutomaticPasswordChange = FALSE;
    p_cfg->enableTimerCheck = FALSE;
    p_cfg->enableTimerCheckTolerance = FALSE;
    p_cfg->clrInternalResetFlag = FALSE;
}

void IfxScuWdt_initCpuWatchdog (Ifx_SCU_WDTCPU * wdt, IfxScuWdt_Config * p_cfg)
{
    Ifx_SCU_WDTCPU_CON0 wdt_con0;
    Ifx_SCU_WDTCPU_CON1 wdt_con1;

    /* Read Config_0 register and clear wdt_con1 variable */
    wdt_con0.U = wdt->CON0.U;
    wdt_con1.U = 0;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK = 0;
        wdt_con0.B.PW ^= 0x003F;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Initialize CON0 register, with modify access, with user defined parameters
     * Clear ENDINT bit to unprotect CON1 register for initialization
     * see Table 3 (Modify Access Bit Pattern Requirements) */
    wdt_con0.B.ENDINIT = 0;
    wdt_con0.B.LCK = 1;
    wdt_con0.B.PW = p_cfg->password;    //user defined password
    wdt_con0.B.REL = p_cfg->reload; //user defined reload value

    /* Modify access ready - write WDT_CON0 register */
    wdt->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been cleared */
    while (wdt->CON0.B.ENDINIT == 1)
    {
    }
    /* Initialize CON1 register */
    switch (p_cfg->inputFrequency)
    {
    case IfxScu_WDTCON1_IR_divBy16384:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy256:
        wdt_con1.B.IR0 = 1;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy64:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 1;
        break;
    }
    wdt_con1.B.DR = p_cfg->disableWatchdog ? 1 : 0;
    wdt_con1.B.UR = p_cfg->enableSmuRestriction ? 1 : 0;
    wdt_con1.B.PAR = p_cfg->enableAutomaticPasswordChange ? 1 : 0;
    wdt_con1.B.TCR = p_cfg->enableTimerCheck ? 1 : 0;
    wdt_con1.B.TCTR = p_cfg->enableTimerCheckTolerance ? 1 : 0;

    /* Finally write CON1 with user defined configuration */
    wdt->CON1.U = wdt_con1.U;

    /* Initialization finished - set CPU ENDINIT protection */
    IfxScuWdt_setCpuEndinit (p_cfg->password);
}

void IfxScuWdt_initSafetyWatchdog (Ifx_SCU_WDTS * wdt, IfxScuWdt_Config * p_cfg)
{
    Ifx_SCU_WDTS_CON0 wdt_con0;
    Ifx_SCU_WDTS_CON1 wdt_con1;

    /* Read Config_0 register and clear wdt_con1 variable */
    wdt_con0.U = wdt->CON0.U;
    wdt_con1.U = 0;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK = 0;
        wdt_con0.B.PW ^= 0x003F;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Initialize CON0 register, with modify access, with user defined parameters
     * Clear ENDINT bit to unprotect CON1 register for initialization
     * see Table 3 (Modify Access Bit Pattern Requirements) */
    wdt_con0.B.ENDINIT = 0;
    wdt_con0.B.LCK = 1;
    wdt_con0.B.PW = p_cfg->password;    //user defined password
    wdt_con0.B.REL = p_cfg->reload; //user defined reload value

    /* Modify access ready - write WDT_CON0 register */
    wdt->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been cleared */
    while (wdt->CON0.B.ENDINIT == 1)
    {

    }
    /* Initialize CON1 register */
    switch (p_cfg->inputFrequency)
    {
    case IfxScu_WDTCON1_IR_divBy16384:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy256:
        wdt_con1.B.IR0 = 1;
        wdt_con1.B.IR1 = 0;
        break;
    case IfxScu_WDTCON1_IR_divBy64:
        wdt_con1.B.IR0 = 0;
        wdt_con1.B.IR1 = 1;
        break;
    }
    wdt_con1.B.DR = p_cfg->disableWatchdog ? 1 : 0;
    wdt_con1.B.UR = p_cfg->enableSmuRestriction ? 1 : 0;
    wdt_con1.B.PAR = p_cfg->enableAutomaticPasswordChange ? 1 : 0;
    wdt_con1.B.TCR = p_cfg->enableTimerCheck ? 1 : 0;
    wdt_con1.B.TCTR = p_cfg->enableTimerCheckTolerance ? 1 : 0;
    wdt_con1.B.CLRIRF = p_cfg->clrInternalResetFlag ? 0 : 1;

    /* Finally write CON1 with user defined configuration */
    wdt->CON1.U = wdt_con1.U;

    /* Initialization finished - set Safety ENDINIT protection */
    IfxScuWdt_setSafetyEndinit (p_cfg->password);
}

void IfxScuWdt_clearCpuEndinit (uint16 password)
{
    IfxScuWdt_clearCpuEndinitInline (&MODULE_SCU.WDTCPU[IfxCpu_getCoreId ()], password);
}

void IfxScuWdt_setCpuEndinit (uint16 password)
{
    IfxScuWdt_setCpuEndinitInline (&MODULE_SCU.WDTCPU[IfxCpu_getCoreId ()], password);
}

void IfxScuWdt_serviceCpuWatchdog (uint16 password)
{
    IfxScuWdt_setCpuEndinit (password);
}

void IfxScuWdt_changeCpuWatchdogPassword (uint16 password, uint16 newPassword)
{
    Ifx_SCU_WDTCPU *watchdog = &MODULE_SCU.WDTCPU[IfxCpu_getCoreId ()];

    /* Read Config_0 register */
    Ifx_SCU_WDTCPU_CON0 wdt_con0;
    wdt_con0.U = watchdog->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK = 0;
        wdt_con0.B.PW = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        watchdog->CON0.U = wdt_con0.U;
    }

    /* Set new Password, ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK = 1;
    wdt_con0.B.PW = newPassword;
    watchdog->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (watchdog->CON0.B.ENDINIT == 0)
    {
    }
}

void IfxScuWdt_enableCpuWatchdog (uint16 password)
{
    /* Select CPU Watchdog based on Core Id */
    uint32 coreId = IfxCpu_getCoreId ();
    Ifx_SCU_WDTCPU *wdt = &MODULE_SCU.WDTCPU[coreId];

    IfxScuWdt_clearCpuEndinit (password);
    wdt->CON1.B.DR = 0;         //Clear DR bit in Config_1 register
    IfxScuWdt_setCpuEndinit (password);
}

void IfxScuWdt_disableCpuWatchdog (uint16 password)
{
    /* Select CPU Watchdog based on Core Id */
    uint32 coreId = IfxCpu_getCoreId ();
    Ifx_SCU_WDTCPU *wdt = &MODULE_SCU.WDTCPU[coreId];

    IfxScuWdt_clearCpuEndinit (password);
    wdt->CON1.B.DR = 1;         //Set DR bit in Config_1 register
    IfxScuWdt_setCpuEndinit (password);
}

void IfxScuWdt_changeCpuWatchdogReload (uint16 password, uint16 reload)
{
    /* Select CPU Watchdog based on Core Id */
    uint32 coreId = IfxCpu_getCoreId ();
    Ifx_SCU_WDTCPU *wdt = &MODULE_SCU.WDTCPU[coreId];

    /* Read Config_0 register */
    Ifx_SCU_WDTCPU_CON0 wdt_con0;
    wdt_con0.U = wdt->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK = 0;
        wdt_con0.B.PW = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Set new Reload value, set ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK = 1;
    wdt_con0.B.REL = reload;
    wdt->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (wdt->CON0.B.ENDINIT == 0)
    {
    }
}

uint16 IfxScuWdt_getCpuWatchdogPassword (void)
{
    return IfxScuWdt_getCpuWatchdogPasswordInline (&MODULE_SCU.WDTCPU[IfxCpu_getCoreId ()]);
}

void IfxScuWdt_clearSafetyEndinit (uint16 password)
{
    IfxScuWdt_clearSafetyEndinitInline (password);
}

void IfxScuWdt_setSafetyEndinit (uint16 password)
{
    IfxScuWdt_setSafetyEndinitInline (password);
}

void IfxScuWdt_serviceSafetyWatchdog (uint16 password)
{
    IfxScuWdt_setSafetyEndinit (password);
}

void IfxScuWdt_changeSafetyWatchdogPassword (uint16 password, uint16 newPassword)
{
    Ifx_SCU_WDTS *watchdog = &MODULE_SCU.WDTS;

    /* Read Config_0 register */
    Ifx_SCU_WDTS_CON0 wdt_con0;
    wdt_con0.U = watchdog->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK = 0;
        wdt_con0.B.PW = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        watchdog->CON0.U = wdt_con0.U;
    }

    /* Set new Password, ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK = 1;
    wdt_con0.B.PW = newPassword;
    watchdog->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (watchdog->CON0.B.ENDINIT == 0)
    {
    }
}

void IfxScuWdt_enableSafetyWatchdog (uint16 password)
{
    IfxScuWdt_clearSafetyEndinit (password);
    SCU_WDTS_CON1.B.DR = 0;     //Clear DR bit in Config_1 register
    IfxScuWdt_setSafetyEndinit (password);
}

void IfxScuWdt_disableSafetyWatchdog (uint16 password)
{
    IfxScuWdt_clearSafetyEndinit (password);
    SCU_WDTS_CON1.B.DR = 1;     //Set DR bit in Config_1 register
    IfxScuWdt_setSafetyEndinit (password);
}

void IfxScuWdt_changeSafetyWatchdogReload (uint16 password, uint16 reload)
{
    /* Initialize pointer to Safety Watchdog */
    Ifx_SCU_WDTS *wdt = &MODULE_SCU.WDTS;

    /* Read Config_0 register */
    Ifx_SCU_WDTS_CON0 wdt_con0;
    wdt_con0.U = wdt->CON0.U;

    if (wdt_con0.B.LCK)
    {
        /* see Table 1 (Password Access Bit Pattern Requirements) */
        wdt_con0.B.ENDINIT = 1;
        wdt_con0.B.LCK = 0;
        wdt_con0.B.PW = password;

        /* Password ready. Store it to WDT_CON0 to unprotect the register */
        wdt->CON0.U = wdt_con0.U;
    }

    /* Set new Reload value, set ENDINT and LCK bit in Config_0 register */
    wdt_con0.B.ENDINIT = 1;
    wdt_con0.B.LCK = 1;
    wdt_con0.B.REL = reload;
    wdt->CON0.U = wdt_con0.U;

    /* read back ENDINIT and wait until it has been set */
    while (wdt->CON0.B.ENDINIT == 0)
    {
    }
}

uint16 IfxScuWdt_getSafetyWatchdogPassword (void)
{
    return IfxScuWdt_getSafetyWatchdogPasswordInline ();
}

#define IFXSCU_STOP_SEC_CODE
#include "IFXSCU_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
