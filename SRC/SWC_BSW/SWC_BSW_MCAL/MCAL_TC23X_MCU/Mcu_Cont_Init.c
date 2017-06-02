#include "Mcu_Cont_Init.h"
#include "Mcu.h"

#include "IfxSmu_reg.h"
#include "IfxScu_reg.h"

#define MCU_START_SEC_CODE
#include "MemMap.h"

void Mcu_Cont_Init(void)
{
   /* Initialize MCU Clock */
   /* Parameter 0 is chosen here by default, the first clock configuration */
   Mcu_InitClock(0);

   /* Wait till PLL lock */
   while(Mcu_GetPllStatus() == 0);

   /* Distribute the clock */
   Mcu_DistributePllClock();

   /* Below piece of code is a workaround due to the hardware bug for
      system reset on WDG overflow */
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
}

#define MCU_STOP_SEC_CODE
#include "MemMap.h"
