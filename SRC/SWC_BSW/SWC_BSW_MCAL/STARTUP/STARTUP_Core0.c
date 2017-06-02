/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : STARTUP                                                 */
/* !Description     : Start-up                                                */
/*                                                                            */
/* !File            : STARTUP_Core0.c                                         */
/* !Description     : Start-up software of Core 0                             */
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

#include "Std_Types.h"
#include "IfxCpu.h"
#include "IfxCpu_reg.h"
#include "Dma.h"
#include "EcuM.h"
#include "IfxScuWdt.h"
#include "IfxScu_reg.h"
#include "Ifx_Cfg.h"
#include "MAIN.h"
#include "Mcal.h"
#include "Mcu.h"
#include "Os_api.h"
#include "RSTSRV.h"
#include "STARTUP.h"
#include "Wdg.h"

extern void SWFAIL_vidTrapVectTbl(void);

extern void MAIN_core0_main(void);
//extern void IfxCpu_Trap_vectorTable0(void);

#pragma section ".inttab.osinterrupts" a
extern const uint32 const Os_InterruptVectorTable[];
#pragma section

#if (MCU_PB_FIXEDADDR == STD_ON)

#define MCU_START_SEC_CONST_32BIT
#include "MemMap.h"

extern const Mcu_ConfigType * const Mcu_kConfigPtr;

#define MCU_STOP_SEC_CONST_32BIT
#include "MemMap.h"

#endif


#if (MCU_PB_FIXEDADDR == STD_OFF)

#define MCU_START_SEC_VAR_INIT_32BIT
#include "MemMap.h"

extern const Mcu_ConfigType * Mcu_kConfigPtr;

#define MCU_STOP_SEC_VAR_INIT_32BIT
#include "MemMap.h"

#endif

/**********************************************************************************************************************/
/* FUNCTIONS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define STARTUP_START_SEC_CODE
#include "STARTUP_MemMap.h"
extern void cstart(void);
#define STARTUP_STOP_SEC_CODE
#include "STARTUP_MemMap.h"

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_WDGLIB_START_SEC_CODE
#include "MemMap.h"
#else
#define IFX_MCAL_WDGLIB_START_SEC_CODE_ASIL_B
#include "Ifx_MemMap.h"
#endif

#if (IFX_SAFETLIB_USED == STD_OFF)
extern void Mcal_lResetSafetyENDINIT(void);
extern void Mcal_lSetSafetyENDINIT(void);
#endif

#if (IFX_MCAL_USED == STD_ON)
#define MCAL_WDGLIB_STOP_SEC_CODE
#include "MemMap.h"
#else
#define IFX_MCAL_WDGLIB_STOP_SEC_CODE_ASIL_B
#include "Ifx_MemMap.h"
#endif

#define STARTUP_START_SEC_CODE
#include "STARTUP_MemMap.h"

/******************************************************************************/
/* !FuncName    : STARTUP_Core0_start                                         */
/* !Description : Startup Function of Core 0                                  */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void STARTUP_Core0_start(void)
{
   uint16 u16LocalWdtPassword;
   sint32 *ps32LocalPrevCsa;
   sint32 s32LocalLoopCount;
   sint32 s32LocalNnOfCsas;
   uint32 u32LocalPcxi;
   uint32 u32LocalSegmentNr, u32LocalSegmentIdx, u32LocalPcxiVal = 0;
   uint32 u32LocalStackPointer;
   StatusType          udtLocSts;
   uint32   * pu32Dest;

   /* Initialization of SDA base pointers */
   __setareg(a0, __SDATA1_0);
   __setareg(a1, __SDATA2_0);
   __setareg(a8, __SDATA3_0);

   /* Load user stack pointer */
   u32LocalStackPointer = (uint32)(__USTACK0) & STACK_ALIGN;
   __setareg(sp, u32LocalStackPointer);
   __dsync();

   /* Load interupt stack pointer                          */
   __mtcr(CPU_ISP, u32LocalStackPointer);
    __dsync();

   /* Set the PSW to its reset value in case of a warm start,clear PSW.IS */
   __mtcr(CPU_PSW, STARTUP_CORE0_PSW_DEFAULT);
   __isync() ;

   /* Set the PCXS and PCXO to its reset value in case of a warm start */
   u32LocalPcxi  = __mfcr(CPU_PCXI);
   u32LocalPcxi &= STARTUP_CORE0_PCX_O_S_DEFAULT; /*0xfff00000; */
   __mtcr(CPU_PCXI, u32LocalPcxi);

   /* Setup the context save area linked list. */
   /* First calculate nr of CSAs in this area  */
   s32LocalNnOfCsas = ((sint32 *) __CSA0_END - (sint32 *) __CSA0) >> 4;
   ps32LocalPrevCsa = (sint32 *) __CSA0;

   for (s32LocalLoopCount = 0;
        s32LocalLoopCount < s32LocalNnOfCsas;
        s32LocalLoopCount++)
   {
      /* Store null pointer in last CSA (= very first time!) */
      *ps32LocalPrevCsa = u32LocalPcxiVal;
      /* get segment number */
      u32LocalSegmentNr = EXTRACT((sint32)ps32LocalPrevCsa, 28, 4) << 16;
      /* get idx number */
      u32LocalSegmentIdx = EXTRACT((sint32)ps32LocalPrevCsa, 6, 16);
      /* calculate valid pcxi value */
      u32LocalPcxiVal = u32LocalSegmentNr | u32LocalSegmentIdx;
      /* if this is the last csa, then we store the new pcxi value to LCX */
      if (s32LocalLoopCount == 0)
        __mtcr (CPU_LCX, u32LocalPcxiVal);
      /* next CSA */
      ps32LocalPrevCsa += 16;
   }
   /* Store actual pcxi value to the FCX (this is our first free context) */
   __mtcr (CPU_FCX, u32LocalPcxiVal);
   __isync() ;

   /* Clear the ENDINIT bit in the WDT_CON0 register */
   u16LocalWdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[0]);  
   IfxScuWdt_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[0], u16LocalWdtPassword);
   /* Load Base Address of Trap Vector Table               */
   __mtcr(CPU_BTV, (uint32)SWFAIL_vidTrapVectTbl);
   IfxScuWdt_setCpuEndinitInline(&MODULE_SCU.WDTCPU[0], u16LocalWdtPassword);

   u16LocalWdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[0]);
   IfxScuWdt_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[0], u16LocalWdtPassword);
   /* Load Base Address of Interrupt Vector Table.         */
   __mtcr(CPU_BIV, (uint32)&Os_InterruptVectorTable);

   /* Load interupt stack pointer                          */
   //__mtcr(CPU_ISP, ((uint32)&__USTACK0) & STACK_ALIGN);
   __mtcr(CPU_ISP, (uint32)__ISTACK0);

   /* Enable Program Cache */
   IfxCpu_setProgramCache(STARTUP_CORE0_ENA_PCACHE);
   /* Enable Data Cache if Configured */
   IfxCpu_setDataCache(STARTUP_CORE0_ENA_DCACHE);
   /* Set the ENDINIT bit in the WDT_CON0 register again to enable the write-protection and to prevent a time-out. */
   IfxScuWdt_setCpuEndinitInline(&MODULE_SCU.WDTCPU[0], u16LocalWdtPassword);

   for (pu32Dest = (uint32 *)__USTACK0_END;  (uint32)pu32Dest < (uint32)__USTACK0; pu32Dest++)
   {
      *pu32Dest = 0x55AA55AA;
   }

   DMA_vidStartDeInit();

   /* Initialization of C runtime variables excepting the uncleared RAM which is initialized regarding reset Type */
   Mcal_Gnu_CopyTable((uint32)&__clear_table, (uint32)&__copy_table);

   RSTSRV_vidInit();
   if ((RSTSRV_udtReadResetState() == RSTSRV_udtSOFTWARE_RESET) || (STARTUP_bAllRamClearAtInitReq == TRUE))
   {
      Mcal_Gnu_CopyTable((uint32)&__power_on_clear_table, (uint32)&__power_on_copy_table);
      STARTUP_bAllRamClearAtInitReq = FALSE;
   }
   RSTSRV_vidPermanentResetProtect();

   u16LocalWdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[0]);
   IfxScuWdt_clearCpuEndinitInline(&MODULE_SCU.WDTCPU[0], u16LocalWdtPassword);
   Os_InitializeInterruptTable();
   Os_InitializeServiceRequests();
   IfxScuWdt_setCpuEndinitInline(&MODULE_SCU.WDTCPU[0], u16LocalWdtPassword);

   /* Disable of internal Core0 Watchdog and internal Safety Watgdog          */
   u16LocalWdtPassword = IfxScuWdt_getCpuWatchdogPasswordInline(&MODULE_SCU.WDTCPU[0]);
   IfxScuWdt_disableCpuWatchdog(u16LocalWdtPassword);  
   IfxScuWdt_disableSafetyWatchdog(IfxScuWdt_getSafetyWatchdogPassword());
     
   /* Start Cores */
   /* !Trace_To: REQ_0350 */
   //Os_StartCore(0, &udtLocSts);

   /* Initialize MCU Clock */
   Mcu_kConfigPtr = &Mcu_ConfigRoot[0];
   /* Parameter 0 is chosen here by default, the first clock configuration */
   Mcu_InitClock(0);

   /* Wait till PLL lock */
   while(Mcu_GetPllStatus() == 0);

   /* Distribute the clock */
   Mcu_DistributePllClock();

   /* Below piece of code is a workaround due to the hardware bug for system reset on WDG overflow */
   Mcal_ResetENDINIT();
   SCU_TRAPDIS.B.SMUT = 0;
   Mcal_SetENDINIT();

   #if (IFX_SAFETLIB_USED == STD_OFF)
   Mcal_lResetSafetyENDINIT();
   SMU_KEYS.U    = 0xbc;
   SMU_CMD.U     = 0x00;
   SMU_AGCF3_0.U = 0x00000000;
   SMU_AGCF3_1.U = 0x001E0000;
   SMU_AGCF3_2.U = 0x001E0000;
   Mcal_lSetSafetyENDINIT();
   #endif
   
   EcuM_Init();

   __debug();
   RSTSRV_vidPerformReset(RSTSRV_udtSOFTWARE_RESET);
}

#define STARTUP_STOP_SEC_CODE
#include "STARTUP_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
