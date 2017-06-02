/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : OVC                                                                                             */
/*                                                                                                                    */
/* !Component       : OVC                                                                                             */
/* !Description     : OVC unit                                                                                        */
/*                                                                                                                    */
/* !Module          : OVC                                                                                             */
/* !Description     : API of OVC unit                                                                                 */
/*                                                                                                                    */
/* !File            : OVC.h                                                                                           */
/*                                                                                                                    */
/* !Target          : Aurix_TC27x                                                                                     */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/

#ifndef OVC_H
#define OVC_H

#include "Std_Types.h"
#include "Mcal.h"
#include "Dio.h"
#include "IfxScuWdt.h"
//#include "INTBSL.h"
#include "IntrinsicsGnuc.h"
#include "MATHSRV.h"
//#include "os_drv_isr.h"
#include "Os.h"
#include "OVC.h"
#include "DEVHAL_Cfg.h"
#include "Wdg.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
#define OVC_u8CORE_0_1_2 7
#define OVC_u8CORE_0     1
#define OVC_u8CORE_0_1   3 
#define OVC_u8CORE_0_2   5
#define OVC_u8CORE_1     2
#define OVC_u8CORE_1_2   6
#define OVC_u8CORE_2     4 


#define OVC_u32SIZE_32B_MASK   (~((OVC_u32SIZE_32B_VALUE - 1u) >> 5))
#define OVC_u32SIZE_64B_MASK   (~((OVC_u32SIZE_64B_VALUE - 1u) >> 5))
#define OVC_u32SIZE_128B_MASK  (~((OVC_u32SIZE_128B_VALUE - 1u) >> 5))
#define OVC_u32SIZE_256B_MASK  (~((OVC_u32SIZE_256B_VALUE - 1u) >> 5))
#define OVC_u32SIZE_512B_MASK  (~((OVC_u32SIZE_512B_VALUE - 1u) >> 5)) 
#define OVC_u32SIZE_1KB_MASK   (~((OVC_u32SIZE_1KB_VALUE - 1u) >> 5))
#define OVC_u32SIZE_2KB_MASK   (~((OVC_u32SIZE_2KB_VALUE - 1u) >> 5))
#define OVC_u32SIZE_4KB_MASK   (~((OVC_u32SIZE_4KB_VALUE - 1u) >> 5))
#define OVC_u32SIZE_8KB_MASK   (~((OVC_u32SIZE_8KB_VALUE - 1u) >> 5))
#define OVC_u32SIZE_16KB_MASK  (~((OVC_u32SIZE_16KB_VALUE - 1u) >> 5))
#define OVC_u32SIZE_32KB_MASK  (~((OVC_u32SIZE_32KB_VALUE - 1u) >> 5))
#define OVC_u32SIZE_64KB_MASK  (~((OVC_u32SIZE_64KB_VALUE - 1u) >> 5))
#define OVC_u32SIZE_128KB_MASK (~((OVC_u32SIZE_128KB_VALUE - 1u) >> 5))

#define OVC_u32SIZE_32B_VALUE   32u
#define OVC_u32SIZE_64B_VALUE   64u
#define OVC_u32SIZE_128B_VALUE  128u
#define OVC_u32SIZE_256B_VALUE  256u
#define OVC_u32SIZE_512B_VALUE  512u
#define OVC_u32SIZE_1KB_VALUE   1024u
#define OVC_u32SIZE_2KB_VALUE   2048u
#define OVC_u32SIZE_4KB_VALUE   4096u
#define OVC_u32SIZE_8KB_VALUE   8192u
#define OVC_u32SIZE_16KB_VALUE  16384u
#define OVC_u32SIZE_32KB_VALUE  32768u
#define OVC_u32SIZE_64KB_VALUE  65536u
#define OVC_u32SIZE_128KB_VALUE 131072u 

#define OVC_u32ADDR_CACHED_FLASH_MSB    0x80
#define OVC_u32ADDR_NONCACHED_FLASH_MSB 0xA0
#define OVC_u32ADDR_EMEM_MSB            0xBF
#define OVC_u32CACHED_TO_NONCACHED_MASK 0x20000000UL

#define OVC_u32SYSTEM_CLOCK_MHZ 100
#define _SOFTWARE_DEVAID_

#define OVC_u8NB_CFG 3

/**********************************************************************************************************************/
/* TYPEDEF                                                                                                            */
/**********************************************************************************************************************/
typedef struct
{
	uint32 *           pu32Src;
	uint32 *           pu32Dest;
	sint32             s32Size;
	boolean            bEna;
	uint8              u8Cores;
	boolean            bToInit;
} OVC_tstBlk;

/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/
/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description : Get the start value for a timeout                                                                   */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
#define OVC_u32GET_TIMEOUT_START() ((uint32)MODULE_STM0.TIM0.U)

/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description : Checks if the specified timeout is elapsed                                                          */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
/* !Comment: Wait for the specified time (in us) */
#define OVC_bTIMEOUT_ELAPSED(u32Start, u32Dur) \
   ( (((uint32)((uint32)MODULE_STM0.TIM0.U  - (u32Start))) < ((uint32)(OVC_u32SYSTEM_CLOCK_MHZ * (u32Dur)))) \
   ? FALSE \
   : TRUE)

/**********************************************************************************************************************/
/* INTERNAL MACRO FUNCTIONS                                                                                           */
/**********************************************************************************************************************/
#ifndef _SOFTWARE_DEVAID_
	#define OVC_u8GET_CFG_IDX() (((SCU_CHIPID.B.EEA) == 0x01u) ? 1:0)
#else
	#define OVC_u8GET_CFG_IDX() (2)
#endif

#define OVC_u32GET_MASK_SIZE(u32Size) ((~((u32Size - 1u) >> 5)))

#define OVC_u8GET_MEM(pu32Dest) (OVC_aku8GetMemId[(((uint32)(pu32Dest) + 0x01000000u) >> 28)])

/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/
#define OVC_START_SEC_CONST_UNSPECIFIED
#include "OVC_MemMap.h"

extern const uint8 OVC_aku8GetMemId[16];
extern const OVC_tstBlk OVC_akstCfg[OVC_u8NB_CFG][1];

#define OVC_STOP_SEC_CONST_UNSPECIFIED
#include "OVC_MemMap.h"


/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/

#define OVC_START_SEC_CODE
#include "OVC_MemMap.h"

extern void OVC_vidCopy(uint32 * pu32Src, uint32 * pu32Dest, sint32 s32Size);
extern void OVC_vidInit(void);
extern uint32 OVC_u32GetPhysPage(uint32 * pu32LogAddr);

#define OVC_STOP_SEC_CODE
#include "OVC_MemMap.h"

#endif /* OVC_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
