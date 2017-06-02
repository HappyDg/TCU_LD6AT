/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2013)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**   $FILENAME   : Compiler_Cfg.h $                                           **
**                                                                            **
**   $CC VERSION : \main\7 $                                                  **
**                                                                            **
**   $DATE       : 2014-03-17 $                                               **
**                                                                            **
**   AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                            **
**   VENDOR      : Infineon Technologies                                      **
**                                                                            **
**   DESCRIPTION :File contains additional   typedefs that are used for       **
**              bit field structures. Also the tasking intrinsic functions    **
**              are listed here.                                              **
**              Macros given for Modules are not in use.                      **
**                                                                            **
**                                                                            **
**   MAY BE CHANGED BY USER [yes/no]: yes                                     **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**  TRACEABILITY : [cover parentID= SAS_NAS_ALL_PR758,SAS_NAS_ALL_PR755] 
                   [/cover]
*******************************************************************************/


#ifndef COMPILER_CFG_H 
#define COMPILER_CFG_H  

#include "Ifx_Cfg.h"
#include "Mcal_Compiler.h"
#include "Os_Compiler_Cfg.h"

/* 

 * The following memory and pointer classes can be configured per module.

 * Those defines are passed to the compiler abstraction macros in Compiler.h

 */
 


/*******************************************************************************

**                                 MCU                                        **

*******************************************************************************/

/*To be used for code*/

#define MCU_CODE



/*To be used for all global or static variables that are never initialized*/

#define MCU_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define MCU_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define MCU_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define MCU_VAR



/*To be used for global or static constants*/

#define MCU_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define MCU_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define MCU_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define MCU_APPL_CODE



/*******************************************************************************

**                                 PORT                                        *

*******************************************************************************/

/*To be used for code*/

#define PORT_CODE



/*To be used for all global or static variables that are never initialized*/

#define PORT_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define PORT_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define PORT_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define PORT_VAR



/*To be used for global or static constants*/

#define PORT_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define PORT_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define PORT_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define PORT_APPL_CODE



/*******************************************************************************

**                                 DIO                                        **

*******************************************************************************/

/*To be used for code*/

#define DIO_CODE



/*To be used for all global or static variables that are never initialized*/

#define DIO_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define DIO_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define DIO_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define DIO_VAR



/*To be used for global or static constants*/

#define DIO_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define DIO_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define DIO_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define DIO_APPL_CODE



/*******************************************************************************

**                                 ADC                                        **

*******************************************************************************/

/*To be used for code*/

#define ADC_CODE



/*To be used for all global or static variables that are never initialized*/

#define ADC_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define ADC_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define ADC_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define ADC_VAR



/*To be used for global or static constants*/

#define ADC_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define ADC_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define ADC_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define ADC_APPL_CODE



/*******************************************************************************

**                                 GPTA                                        *

*******************************************************************************/

/*To be used for code*/

#define GPTA_CODE



/*To be used for all global or static variables that are never initialized*/

#define GPTA_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define GPTA_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define GPTA_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define GPTA_VAR



/*To be used for global or static constants*/

#define GPTA_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define GPTA_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define GPTA_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define GPTA_APPL_CODE



/*******************************************************************************

**                                 GPT                                        **

*******************************************************************************/

/*To be used for code*/

#define GPT_CODE



/*To be used for all global or static variables that are never initialized*/

#define GPT_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define GPT_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define GPT_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define GPT_VAR



/*To be used for global or static constants*/

#define GPT_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define GPT_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define GPT_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define GPT_APPL_CODE



/*******************************************************************************

**                                 ICU                                        **

*******************************************************************************/

/*To be used for code*/

#define ICU_CODE



/*To be used for all global or static variables that are never initialized*/

#define ICU_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define ICU_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define ICU_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define ICU_VAR



/*To be used for global or static constants*/

#define ICU_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define ICU_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define ICU_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define ICU_APPL_CODE



/*******************************************************************************

**                                 PWM                                        **

*******************************************************************************/

/*To be used for code*/

#define PWM_CODE



/*To be used for all global or static variables that are never initialized*/

#define PWM_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define PWM_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define PWM_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define PWM_VAR



/*To be used for global or static constants*/

#define PWM_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define PWM_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define PWM_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define PWM_APPL_CODE



/*******************************************************************************

**                                 SPI                                        **

*******************************************************************************/

/*To be used for code*/

#define SPI_CODE



/*To be used for all global or static variables that are never initialized*/

#define SPI_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define SPI_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define SPI_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define SPI_VAR



/*To be used for global or static constants*/

#define SPI_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define SPI_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define SPI_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define SPI_APPL_CODE



/*******************************************************************************

**                                 CAN                                        **

*******************************************************************************/

/*To be used for code*/

#define CAN_CODE



/*To be used for all global or static variables that are never initialized*/

#define CAN_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define CAN_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define CAN_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define CAN_VAR



/*To be used for global or static constants*/

#define CAN_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define CAN_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define CAN_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define CAN_APPL_CODE



/*******************************************************************************

**                                 WDG                                        **

*******************************************************************************/

/*To be used for code*/

#define WDG_CODE



/*To be used for all global or static variables that are never initialized*/

#define WDG_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define WDG_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define WDG_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define WDG_VAR



/*To be used for global or static constants*/

#define WDG_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define WDG_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define WDG_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define WDG_APPL_CODE



/*******************************************************************************

**                                 CANTRCV                                     *

*******************************************************************************/

/*To be used for code*/

#define CANTRCV_CODE



/*To be used for all global or static variables that are never initialized*/

#define CANTRCV_VAR_NOINIT 



/*To be used for all global or static variables that are initialized only after power on reset*/

#define CANTRCV_VAR_POWER_ON_INIT 



/* To be used for all global or static variables that have at least one of the 

following properties:

-accessed bitwise

-frequently used

-high number of accesses in source code*/

#define CANTRCV_VAR_FAST 



/*To be used for global or static variables that are initialized after every 

reset.*/

#define CANTRCV_VAR



/*To be used for global or static constants*/

#define CANTRCV_CONST



/*To be used for references on application data (expected to be in RAM or ROM) passed via API*/

#define CANTRCV_APPL_DATA



/*To be used for references on application constants (expected to be certainly in ROM, for instance pointer of Init-function) passed via API*/

#define CANTRCV_APPL_CONST



/*To be used for references on application functions. (e.g. call back function pointers)*/

#define CANTRCV_APPL_CODE

/******************************************************************************/
/* !Comment: List of MCAL patch used                                          */
/******************************************************************************/
#define VALEO_PATCH_MCAL_SPI_REMOVE_DEM
#define VALEO_PATCH_MCAL_DRV_USE_SCHM
#define VALEO_PATCH_MCAL_ICU_MOVE_DECLARATION
#define VALEO_PATCH_MCAL_ICU_FIX_ETXERN_INLINE
#define VALEO_PATCH_MCAL_FIX_ISR_MNGT
#define VALEO_PATCH_MCAL_PWM_NOTIF_ON_0_AND_100_PERCENT

#define _GCC_C_WIN32X86_

#define TS_ARCH_FAMILY TS_TRICORE
#define TS_ARCH_DERIVATE TC277

/*this file shall not be modified by the user, CONST_CFG shall be defined in Ifx_Cfg.h */
#ifndef CONST_CFG
#define CONST_CFG               const     /* configuration constants are stored in ROM */
#endif

#define IFX_EXTERN              extern

/* !Comment: definition of keyword "inline" for 3.0 AUTOSAR release           */
//<<#define INLINE


#pragma section ".bss"

/*Start: Common definitions ********************************************** */
extern unsigned int __A0_MEM[];         /**< center of A0 addressable area */
extern unsigned int __A1_MEM[];         /**< center of A1 addressable area */
extern unsigned int __A8_MEM[];         /**< center of A8 addressable area */

/*End: Common definitions ************************************************ */

/*Start: Core 0 definitions ********************************************** */
extern unsigned long __clear_table[];  /* clear table entry */
extern unsigned long __copy_table[];   /* copy table entry  */

extern unsigned long __power_on_clear_table[];  /* power on clear table entry */
extern unsigned long __power_on_copy_table[];   /* power on copy table entry  */

/*C extern defintions */
extern unsigned int __USTACK0[];        /**< user stack end */
extern unsigned int __USTACK0_END[];    /**< user stack start */
extern unsigned int __ISTACK0[];        /**< interrupt stack end */
extern unsigned int __INTTAB_CPU0[];    /**< Interrupt vector table */
extern unsigned int __TRAPTAB_CPU0[];   /**< trap table */
extern unsigned int __CSA0[];           /**< context save area 1 begin */
extern unsigned int __CSA0_END[];       /**< context save area 1 begin */

/*Wrapper macros for the tool specific definitions */
#if defined(IFX_USE_SW_MANAGED_INT)
#define __INTTAB0    ((unsigned int)__INTTAB_CPU0 | (unsigned int)0x1FE0)
#else
#define __INTTAB0    __INTTAB_CPU0
#endif /*defined(IFX_USE_SW_MANAGED_INT) */

#define __TRAPTAB0   __TRAPTAB_CPU0

#define __SDATA1_0   __A0_MEM
#define __SDATA2_0   __A1_MEM
#define __SDATA3_0   __A8_MEM
/*End: Core 0 definitions *****************************************************/

/*Start: Core 1 definitions ***************************************************/
extern unsigned int __USTACK1[];        /**< user stack end */
extern unsigned int __USTACK1_END[];    /**< user stack start */
extern unsigned int __ISTACK1[];        /**< interrupt stack end */
extern unsigned int __INTTAB_CPU1[];    /**< Interrupt vector table */
extern unsigned int __TRAPTAB_CPU1[];   /**< trap table */
extern unsigned int __CSA1[];           /**< context save area 1 begin */
extern unsigned int __CSA1_END[];       /**< context save area 1 begin */

/*Wrapper macros for the tool specific definitions */
#if defined(IFX_USE_SW_MANAGED_INT)
#define __INTTAB1    ((unsigned int)__INTTAB_CPU1 | (unsigned int)0x1FE0)
#else
#define __INTTAB1    __INTTAB_CPU1
#endif /*defined(IFX_USE_SW_MANAGED_INT) */

#define __TRAPTAB1   __TRAPTAB_CPU1

#define __SDATA1_1   __A0_MEM
#define __SDATA2_1   __A1_MEM
#define __SDATA3_1   __A8_MEM
/*End: Core 1 definitions *****************************************************/

/*Start: Core 2 definitions ***************************************************/
extern unsigned int __USTACK2[];        /**< user stack end */
extern unsigned int __ISTACK2[];        /**< interrupt stack end */
extern unsigned int __INTTAB_CPU2[];    /**< Interrupt vector table */
extern unsigned int __TRAPTAB_CPU2[];   /**< trap vector table */
extern unsigned int __CSA2[];           /**< context save area 1 begin */
extern unsigned int __CSA2_END[];       /**< context save area 1 begin */

/*Wrapper macros for the tool specific definitions */
#if defined(IFX_USE_SW_MANAGED_INT)
#define __INTTAB2    ((unsigned int)__INTTAB_CPU2 | (unsigned int)0x1FE0)
#else
#define __INTTAB2    __INTTAB_CPU2
#endif /*defined(IFX_USE_SW_MANAGED_INT) */

#define __TRAPTAB2   __TRAPTAB_CPU2

#define __SDATA1_2   __A0_MEM
#define __SDATA2_2   __A1_MEM
#define __SDATA3_2   __A8_MEM
/*End: Core 2 definitions *****************************************************/
#pragma section
/******************************************************************************/

#define COMPILER_VERSION     0
#define COMPILER_REVISION    0

//dbg

/* Comment: Macro to declare interrupts */
#define DECLARE_IT(isr)                                         \
void __attribute__ ((interrupt_handler)) isr();                 \
void isr(void)

//dbg

#define COMPILER_UNUSED_PARAMETER(udtVariable) \
do	\
{ \
	if ((udtVariable) != 0)	\
	{ \
	} \
} \
while(0)

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Configuration data                                    **
*******************************************************************************/
/** Store a single bit.
*/
#define __putbit(value,address,bitoffset ) __imaskldmst(address, value, bitoffset,1)

/** Convert context pointer to address pointer
 * \param[in] cx context pointer
 * \return address pointer
*/
IFX_LOCAL_INLINE void *__cx_to_addr (uint32 cx)
{
    uint32 seg_nr = __extru (cx, 16, 4);
    return (void *) __insert (seg_nr << 28, cx, 6, 16);
}

/** Convert address pointer to context pointer
 * \param[in] addr address pointer
 * \return context pointer
*/
IFX_LOCAL_INLINE uint32 __addr_to_cx (void *addr)
{
    uint32 seg_nr, seg_idx;
    seg_nr = __extru ((int) addr, 28, 4) << 16;
    seg_idx = __extru ((int) addr, 6, 16);
    return seg_nr | seg_idx;
}

#endif /* COMPILER_CFG_H */

