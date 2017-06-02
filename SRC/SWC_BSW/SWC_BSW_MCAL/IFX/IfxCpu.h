/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : Framework                                               */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : IFXCPU.h                                                */
/* !Description     : Framework component to manage CPU                       */
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

#ifndef IFX_CPU_H
#define IFX_CPU_H
/******************************************************************************/
#include "IfxCpu_cfg.h"
#include "IfxSrc_reg.h"
#include "IfxScu_reg.h"
#include "IfxScuWdt.h"

/******************************************************************************/
/*                           Enum                                             */
/******************************************************************************/
/** \addtogroup IfxLld_Cpu_Core
 * \{  */

/** \brief Enumeration for the Cpu mode.
 *
 */
typedef enum
{
    IfxCpu_CoreMode_halt,
    IfxCpu_CoreMode_run,
    IfxCpu_CoreMode_idle,
    IfxCpu_CoreMode_sleep,
    IfxCpu_CoreMode_stby,
    IfxCpu_CoreMode_unknown
} IfxCpu_CoreMode;

/** Performance conunter modes
 *
 */
typedef enum
{
    IfxCpu_CounterMode_normal = 0,  /**< \brief Normal counter mode:the counter increments on their respective triggers */
    IfxCpu_CounterMode_task = 1     /**< \brief Normal counter mode:additional gating control from the debug unit which allows the data gathered in the performance counters to be filtered by some specific criteria */
}IfxCpu_CounterMode;

/** Performance counter result
 *
 */
typedef struct
{
    struct{
        uint32 counter;  /**< \brief Counter value */
        boolean overlfow;  /**< \brief Sticky overflow */
    }instruction;           /**< \brief Instruction counter */
    struct{
        uint32 counter;  /**< \brief Counter value */
        boolean overlfow;  /**< \brief Sticky overflow */
    }clock;                 /**< \brief CPU clock counter */
    struct{
        uint32 counter;  /**< \brief Counter value */
        boolean overlfow;  /**< \brief Sticky overflow */
    }counter1;              /**< \brief Multi counter 1 */
    struct{
        uint32 counter;  /**< \brief Counter value */
        boolean overlfow;  /**< \brief Sticky overflow */
    }counter2;              /**< \brief Multi counter 2 */
    struct{
        uint32 counter;  /**< \brief Counter value */
        boolean overlfow;  /**< \brief Sticky overflow */
    }counter3;              /**< \brief Multi counter 3*/
} IfxCpu_Perf;

/** \}  */

/******************************************************************************/
/*                       Function prototypes                                  */
/******************************************************************************/
#define IFXCPU_START_SEC_CODE
#include "IFXCPU_MemMap.h"

/** \addtogroup IfxLld_Cpu_Core
 * \{  */

/** \brief API to get the address for CPU HW module register memory map.
 *
 * \param cpu Resource index of the CPU.
 *
 * \return CPU module register address.
 */
IFX_EXTERN Ifx_CPU *IfxCpu_getAddress (IfxCpu_ResourceCpu cpu);

/** \brief API to get resource index of the CPU of the caller.
 *
 * \return Resource index of the CPU.
 */
IFX_LOCAL_INLINE uint32 IfxCpu_getCoreId (void);

/** \brief API to get current mode of CPU.
 *
 * \param cpu Pointer to the CPU HW module (register memory map).
 *
 * \return Current mode of the CPU.
 */
IFX_EXTERN IfxCpu_CoreMode IfxCpu_getCoreMode (Ifx_CPU * cpu);

/** \brief API to get the resource index of the CPU specified.
 *
 * \param cpu Pointer to the CPU HW module (register memory map).
 *
 * \return Resource index of the CPU.
 */
IFX_EXTERN IfxCpu_ResourceCpu IfxCpu_getIndex (Ifx_CPU * cpu);

/** \brief API to initialize the context save area of the CPU where this is called.
 *
 * This API can initialize the CSA of the host CPU where this API is called. This API
 * shall not be used to initialize the CSA of another CPU.
 *
 * \param csaBegin Pointer to start of context save area.
 * \param csaEnd Pointer to end of context save area.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_initCSA (uint32 * csaBegin, uint32 * csaEnd);

/** \brief API to set mode of the CPU.
 *
 * \param cpu Pointer to the CPU HW module (register memory map).
 * \param mode CPU mode to be set by this API.
 *
 * \return Success status of the activity (setting the core mode).
 * \retval TRUE: If the activity can't be performed.
 * \retval FALSE: If the activity successfully be performed.
 */
IFX_EXTERN boolean IfxCpu_setCoreMode (Ifx_CPU * cpu, IfxCpu_CoreMode mode);

/** \brief API to set the program counter for the CPU specified.
 *
 * \param cpu pointer to the CPU HW module (register memory map).
 * \param programCounter Program counter value to be set
 *
 * \return success status of the activity (setting program counter value).
 * \retval TRUE: If the activity can't be performed.
 * \retval FALSE: If the activity successfully be performed.
 */
IFX_EXTERN boolean IfxCpu_setProgramCounter (Ifx_CPU * cpu, uint32 programCounter);

/** \brief API to set the program counter for the CPU specified and start the CPU.
 *
 * This function sets the program counter to the specified value and set the mode of the
 * CPU to running mode.
 *
 * \param cpu pointer to the CPU HW module (register memory map).
 * \param programCounter Program counter value to start the CPU
 *
 * \return success status of the activity (setting program counter value).
 * \retval TRUE: If the activity can't be performed.
 * \retval FALSE: If the activity successfully be performed.
 */
IFX_EXTERN boolean IfxCpu_startCore (Ifx_CPU * cpu, uint32 programCounter);

/** \}  */

/** \addtogroup IfxLld_Cpu_Interrupt
 * \{  */

/** \brief API to get the status of global interrupt enable (ICR.IE) for the CPU which calls this API.
 *
 * This API provides the status of CPU where this API is called.
 *
 * \return Status of global interrupt enable bit.
 * \retval TRUE: Global interrupts enabled.
 * \retval FALSE: Global interrupts disabled.
 */
IFX_LOCAL_INLINE boolean IfxCpu_areInterruptsEnabled (void);

/** \brief API to disable global interrupt and return the previous status.
 *
 * This API can be used only to disable the global interrupts of caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \return Previous status of global interrupt enable bit.
 * \retval TRUE: Previously, global interrupts enabled.
 * \retval FALSE: Previously, global interrupts disabled.
 */
IFX_LOCAL_INLINE boolean IfxCpu_disableInterrupts (void);

/** \brief API to enable global interrupt.
 *
 * This API simply enables the global interrupt.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_enableInterrupts (void);

/** \brief API to restore global interrupt with that of the passed parameter.
 *
 * This API can be used only to disable the global interrupts of caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \param enabled Previous status of the global interrupt enable bit.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_restoreInterrupts (boolean enabled);

/** \} */

/** \addtogroup IfxLld_Cpu_Cache
 * \{  */

/** \brief API to enable or bypass the data cache for the CPU which calls this API.
 *
 * This API can be used only to enable or bypass the data cache of caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \param enable Command to enable or bypass the data cache.
 * TRUE: Enable the data cache.
 * FALSE: Bypass the data cache.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_setDataCache (boolean enable);

/** \brief API to enable or bypass the program cache for the CPU which calls this API.
 *
 * This API can be used only to enable or bypass the program cache of caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \param enable Command to enable or bypass the program cache.
 * TRUE: Enable the program cache.
 * FALSE: Bypass the program cache.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_setProgramCache (boolean enable);

/** \} */

/** \addtogroup IfxLld_Cpu_PerformanceCounter
 * \{  */

/** \brief API to read the clock counter for the CPU which calls this API.
 *
 * This API can be used to read clock counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \return Counter value. 0 to 0x7FFFFFFF.
 *
 */
IFX_LOCAL_INLINE uint32 IfxCpu_getClockCounter (void);

/** \brief API to read the instruction counter for the CPU which calls this API.
 *
 * This API can be used to read instruction counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \return Counter value. 0 to 0x7FFFFFFF.
 *
 */
IFX_LOCAL_INLINE uint32 IfxCpu_getInstructionCounter (void);

/** \brief API to get sticky overflow bit of clock counter for the CPU, which calls this API.
 *
 * This API can be used to get sticky overflow bit of clock counter of only the caller CPU.
 * It cannot be used for this activity towards other CPUs.
 * This API also clears the sticky overflow after the read. While reading the sticky bit this API disables
 * the counter for short time. (otherwise sticky bit cannot be cleared). This API shall be used after
 * reading the counter.
 *
 * \return Status of sticky overflow bit.
 * \retval TRUE: Sticky overflow bit is set.
 * \retval FALSE: Sticky overflow bit is reset.
 *
 */
IFX_LOCAL_INLINE boolean IfxCpu_getClockCounterStickyOverflow (void);

/** \brief API to get sticky overflow bit of instruction counter for the CPU, which calls this API.
 *
 * This API can be used to get sticky overflow bit of instruction counter of only the caller CPU.
 * It cannot be used for this activity towards other CPUs.
 * This API also clears the sticky overflow after the read. While reading the sticky bit this API disables
 * the counter for short time. (otherwise sticky bit cannot be cleared). This API shall be used after
 * reading the counter.
 *
 * \return Status of sticky overflow bit.
 * \retval TRUE: Sticky overflow bit is set.
 * \retval FALSE: Sticky overflow bit is reset.
 *
 */
IFX_LOCAL_INLINE boolean IfxCpu_getInstructionCounterStickyOverflow (void);

/** \brief API to enable or disable performance counter for the CPU which calls this API.
 *
 * This API can be used to enable or disable performance counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \param enable Command to enable or disable the performance counter.
 * TRUE: Enable the performance counter.
 * FALSE: Disable the performance counter.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_setPerformanceCountersEnableBit (uint32 enable);

/** \brief API to update clock counter for the CPU which calls this API.
 *
 * This API can be used to update clock counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \param count Counter value to be updated. 0 to 0x7FFFFFFF.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_updateClockCounter (uint32 count);

/** \brief API to update instruction counter for the CPU which calls this API.
 *
 * This API can be used to update instruction counter of only the caller CPU. It cannot be
 * used for this activity towards other CPUs.
 *
 * \param count Counter value to be updated. 0 to 0x7FFFFFFF.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_updateInstructionCounter (uint32 count);

/** \} */

/******************************************************************************/
/*                         Inline Functions                                   */
/******************************************************************************/

/** \brief API to get resource index of the CPU of the caller.
 *
 */
IFX_LOCAL_INLINE uint32 IfxCpu_getCoreId (void)
{
    Ifx_CPU_CORE_ID reg;
    reg.U = __mfcr (CPU_CORE_ID);
    return reg.B.CORE_ID;
}

/** \brief API to initialize the context save area of the CPU where this is called.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_initCSA (uint32 * csaBegin, uint32 * csaEnd)
{
    uint32 k;
    uint32 nxt_cxi_val = 0;
    uint32 *prvCsa = 0U;
    uint32 *nxtCsa = csaBegin;

    for (k = 0; k < (((uint32) csaEnd - (uint32) csaBegin) / 64); k++)
    {
        nxt_cxi_val = ((uint32) nxtCsa & (0XF << 28)) >> 12 | ((uint32) nxtCsa & (0XFFFF << 6)) >> 6;
        if (k == 0)
        {
            __mtcr (CPU_FCX, nxt_cxi_val);  /* store the new pcxi value to LCX */
        }
        else
        {
            *prvCsa = nxt_cxi_val;  /* Store null pointer in last CSA (= very first time!) */
        }
        prvCsa = (uint32 *) nxtCsa;
        nxtCsa += 16;           /* next CSA */
    }
    *prvCsa = 0;
    __mtcr (CPU_LCX, nxt_cxi_val);  /* Last context save area is pointed in LCX to know if there is CSA depletion */
}

/** \brief API to get the status of global interrupt enable (ICR.IE) for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE boolean IfxCpu_areInterruptsEnabled (void)
{
    Ifx_CPU_ICR reg;
    reg.U = __mfcr (CPU_ICR);
    return reg.B.IE != 0;
}

/** \brief API to disable global interrupt and return the previous status.
 *
 */
IFX_LOCAL_INLINE boolean IfxCpu_disableInterrupts (void)
{
    boolean enabled;
    enabled = IfxCpu_areInterruptsEnabled ();
    __disable ();
    __nop ();
    return enabled;
}

/** \brief API to enable global interrupt.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_enableInterrupts (void)
{
    __enable ();
}

/** \brief API to restore global interrupt with that of the passed parameter.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_restoreInterrupts (boolean enabled)
{
    if (enabled != FALSE)
    {
        __enable ();
    }
}

/** \brief API to enable or bypass the data cache for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_setDataCache (boolean enable)
{
    uint32 coreId = IfxCpu_getCoreId ();
    uint16 wdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline (&MODULE_SCU.WDTCPU[coreId]);
    /*PCACHE enable steps */
    {                           /* Step 1: Set PCBYP to 0 if cache is enabled */
        IfxScuWdt_clearCpuEndinitInline (&MODULE_SCU.WDTCPU[coreId], wdtPassword);
        Ifx_CPU_DCON0 dcon0;
        dcon0.U = 0;
        dcon0.B.DCBYP = enable ? 0 : 1; /*depending on the enable bypas bit is reset/set */
        __mtcr (CPU_DCON0, dcon0.U);
        IfxScuWdt_clearCpuEndinitInline (&MODULE_SCU.WDTCPU[coreId], wdtPassword);
    }
    /* Step 2: Call Isync */
    __isync ();
}

/** \brief API to enable or bypass the program cache for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_setProgramCache (boolean enable)
{
    uint32 coreId = IfxCpu_getCoreId ();
    uint16 wdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline (&MODULE_SCU.WDTCPU[coreId]);
    /*PCACHE enable steps */
    {                           /* Step 1: Set PCBYP to 0 if cache is enabled */
        IfxScuWdt_clearCpuEndinitInline (&MODULE_SCU.WDTCPU[coreId], wdtPassword);
        Ifx_CPU_PCON0 pcon0;
        pcon0.U = 0;
        pcon0.B.PCBYP = enable ? 0 : 1; /*depending on the enable bypass bit is reset/set */
        __mtcr (CPU_PCON0, pcon0.U);
        IfxScuWdt_clearCpuEndinitInline (&MODULE_SCU.WDTCPU[coreId], wdtPassword);
    }
    /* Step 2: Call Isync */
    __isync ();
    if (enable)
    {                           /* Step 3: Initiate invalidation of current cache contents if any */
        Ifx_CPU_PCON1 pcon1;
        pcon1.U = 0;
        pcon1.B.PCINV = 1;
        __mtcr (CPU_PCON1, pcon1.U);
    }
}

/** \brief API to read the performance counter for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE uint32 IfxCpu_getPerformanceCounter (uint32 address)
{
    Ifx_CPU_CCNT ccnt;
    ccnt.U = __mfcr (address);
    return ccnt.B.CountValue;
}

/** \brief API to read the clock counter for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE uint32 IfxCpu_getClockCounter (void)
{
    return IfxCpu_getPerformanceCounter (CPU_CCNT);
}

/** \brief API to read the instruction counter for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE uint32 IfxCpu_getInstructionCounter (void)
{
    return IfxCpu_getPerformanceCounter (CPU_ICNT);
}

/** \brief API to get sticky overflow bit of performance counter for the CPU, which calls this API.
 * This is generic function to get sticky overflow bit of any performance counters
 *
 * FIXME To be discussed (Alann-Ashok). I think there is not use case to disable the counters while getting the overflow bit, the overflow bit has only a meaning when coherent to the counter value.
 * This mean that this function only make sense if the counter are disabled previously. Reseting the overflow flag here has also no sense
 */
IFX_LOCAL_INLINE boolean IfxCpu_getPerformanceCounterStickyOverflow (uint32 address)
{
    Ifx_CPU_CCNT ccnt;
    Ifx_CPU_CCTRL cctrl;
    boolean enableBit;

    /*store the enable bit value */
    cctrl.U = __mfcr (CPU_CCTRL);
    enableBit = cctrl.B.CE;

    /*disable the counters for short time */
    cctrl.B.CE = 0;
    __mtcr (CPU_CCTRL, cctrl.U);

    ccnt.U = __mfcr (address);
    __mtcr (address, ccnt.B.CountValue);    /*By writing only the count value the overflow bit is cleared */

    /*restore the enable bit */
    cctrl.B.CE = enableBit;
    __mtcr (CPU_CCTRL, cctrl.U);

    return ccnt.B.SOvf;
}

/** \brief API to get sticky overflow bit of clock counter for the CPU, which calls this API.
 *
 */
IFX_LOCAL_INLINE boolean IfxCpu_getClockCounterStickyOverflow (void)
{
    return IfxCpu_getPerformanceCounterStickyOverflow (CPU_CCNT);
}

/** \brief API to get sticky overflow bit of instruction counter for the CPU, which calls this API.
 *
 */
IFX_LOCAL_INLINE boolean IfxCpu_getInstructionCounterStickyOverflow (void)
{
    return IfxCpu_getPerformanceCounterStickyOverflow (CPU_ICNT);
}

/** \brief API to enable or disable performance counter for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_setPerformanceCountersEnableBit (uint32 enable)
{
    Ifx_CPU_CCTRL cctrl;
    cctrl.U = __mfcr (CPU_CCTRL);
    cctrl.B.CE = enable;
    __mtcr (CPU_CCTRL, cctrl.U);
}

/** \brief API to update performance counter for the CPU which calls this API.
 * This is generic function to update any of the performance counters
 *
 * FIXME To be discussed (Alann-Ashok). It might be better to enable / disable the counters using a separate 
 * function, to enable synchornous start of performance measurements
 */
IFX_LOCAL_INLINE void IfxCpu_updatePerformanceCounter (uint32 address, uint32 count)
{
    Ifx_CPU_CCTRL cctrl;
    boolean enableBit;
    /*Disable the counters */
    cctrl.U = __mfcr (CPU_CCTRL);
    enableBit = cctrl.B.CE;
    cctrl.B.CE = 0;
    __mtcr (CPU_CCTRL, cctrl.U);

    /*Update the counter value */
    count &= ~(1U << 31);       /*clear sticky overflow bit if set */
    __mtcr (address, count);

    /*restore the enable bit */
    cctrl.B.CE = enableBit;
    __mtcr (CPU_CCTRL, cctrl.U);
}

/** \brief API to update clock counter for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_updateClockCounter (uint32 count)
{
    IfxCpu_updatePerformanceCounter (CPU_CCNT, count);
}

/** \brief API to update instruction counter for the CPU which calls this API.
 *
 */
IFX_LOCAL_INLINE void IfxCpu_updateInstructionCounter (uint32 count)
{
    IfxCpu_updatePerformanceCounter (CPU_ICNT, count);
}


/** \brief Reset and start instruction, clock and multi counters
 *
 * Reset and start CCNT, ICNT, M1CNT, M2CNT, M3CNT. the overflow bits are cleared.
 */
IFX_LOCAL_INLINE void IfxCpu_resetAndStartCounters (IfxCpu_CounterMode mode)
{
    Ifx_CPU_CCTRL cctrl;
    cctrl.U = __mfcr (CPU_CCTRL);
    /*Disable the counters */
    cctrl.B.CE = 0;
    __mtcr (CPU_CCTRL, cctrl.U);

    /* reset the counters */
    __mtcr (CPU_CCNT, 0);
    __mtcr (CPU_ICNT, 0);
    __mtcr (CPU_M1CNT, 0);
    __mtcr (CPU_M2CNT, 0);
    __mtcr (CPU_M3CNT, 0);

    /*Enable the counters, set the counter mode */
    cctrl.B.CE = 1;
    cctrl.B.CM = mode;
    __mtcr (CPU_CCTRL, cctrl.U);
}

/** \brief Stop instruction and clock counters, return their values
 *
 * Stop CCNT, ICNT, M1CNT, M2CNT, M3CNT and return their values;
 * \Note The CCTRL is reset to 0, for more accurate measurements and has to be initialized again before strating the next performance measurement.
 *
 */
IFX_LOCAL_INLINE IfxCpu_Perf IfxCpu_stopCounters (void)
{
    IfxCpu_Perf result;
    /*Disable the counters, reset the control reg */
    /* Use inline assembly to ensure constant implementation, and execution of the measurement routines */
    __stopPerfCounters();

    Ifx_CPU_CCNT ccnt;
    ccnt.U = __mfcr (CPU_CCNT);
    result.clock.counter = ccnt.B.CountValue;
    result.clock.overlfow = ccnt.B.SOvf;

    Ifx_CPU_ICNT icnt;
    icnt.U = __mfcr (CPU_ICNT);
    result.instruction.counter = icnt.B.CountValue;
    result.instruction.overlfow = icnt.B.SOvf;

    Ifx_CPU_M1CNT m1cnt;
    m1cnt.U = __mfcr (CPU_M1CNT);
    result.counter1.counter = m1cnt.B.CountValue;
    result.counter1.overlfow = m1cnt.B.SOvf;

    Ifx_CPU_M2CNT m2cnt;
    m2cnt.U = __mfcr (CPU_M2CNT);
    result.counter2.counter = m2cnt.B.CountValue;
    result.counter2.overlfow = m2cnt.B.SOvf;

    Ifx_CPU_M3CNT m3cnt;
    m3cnt.U = __mfcr (CPU_M3CNT);
    result.counter3.counter = m3cnt.B.CountValue;
    result.counter3.overlfow = m3cnt.B.SOvf;
    return result;
}

#define IFXCPU_STOP_SEC_CODE
#include "IFXCPU_MemMap.h"

#endif /* IFX_CPU_H */

/*-------------------------------- end of file -------------------------------*/
