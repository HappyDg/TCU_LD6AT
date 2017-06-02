/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : STARTUP                                                 */
/* !Description     : Start-up                                                */
/*                                                                            */
/* !File            : STARTUP.c                                               */
/* !Description     : Start-up software                                       */
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
#include "Mcal_TcLib.h"
#include "RSTSRV.h"
#include "STARTUP.h"

#include "v_cfg.h"
#include "v_def.h"
#include "applvect.h"

/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/
/* STARTUP_bAllRamClearAtInitReq shall have a fixed address in uncleared RAM  */
#define STARTUP_START_SEC_ALL_RAM_CLEAR_AT_INIT_FLAG
#include "STARTUP_MemMap.h"

boolean STARTUP_bAllRamClearAtInitReq;

#define STARTUP_STOP_SEC_ALL_RAM_CLEAR_AT_INIT_FLAG
#include "STARTUP_MemMap.h"

/******************************************************************************/
/* CONSTANTS DEFINITION                                                       */
/******************************************************************************/

/* Boot Mode Header 0 sections to inform linker to locate them at 0x80000000  */
#define STARTUP_START_SEC_BMHD_0
#include "STARTUP_MemMap.h"

/* Boot Mode Header 0 sections to inform linker to locate them at 0x80000000  */
/* STADBM has to be initialized if Alternate Boot Mode is used.               */
/* Else first user code has to be placed at 0x80000020                        */
const uint32 STARTUP_BootModeHeader_0[0x08u] =
{
   0xA0000020ul,   /* STADBM:first user code in Alternate Boot Mode */
   0xB3590070ul,   /* BMI = 0070h BMHDID = B359h */
   0xA001FFC0ul,   /* ChkStart */
   0xA001FFDFul,   /* ChkEnd */
   0x1788B88Eul,   /* CRCrange */
   0xE8774771ul,   /* !CRCrange */
   0xF1E93922ul,   /* CRChead */
   0x0E16C6DDul    /* !CRChead */
};

#define STARTUP_STOP_SEC_BMHD_0
#include "STARTUP_MemMap.h"


/* Boot Mode Header 1 sections to inform linker to locate them at 0x80020000  */
#define STARTUP_START_SEC_BMHD_1
#include "STARTUP_MemMap.h"

/* STADBM has to be initialized if Alternate Boot Mode is used.               */
/* Else first user code has to be placed at 0x80000020                        */
const uint32 STARTUP_BootModeHeader_1[0x08u] =
{
   0x00000000,   /* STADBM:first user code in Alternate Boot Mode */
   0xB3590070,   /* BMI = 0070h BMHDID = B359h */
   0x00000000,   /* ChkStart */
   0x00000000,   /* ChkEnd */
   0x00000000,   /* CRCrange */
   0x00000000,   /* !CRCrange */
   0x791EB864,   /* CRChead */
   0x86E1479B    /* !CRChead */
};

#define STARTUP_STOP_SEC_BMHD_1
#include "STARTUP_MemMap.h"

#define STARTUP_START_SEC_FBL_SIGNATURE
#include "STARTUP_MemMap.h"

/* FBL signature: FBL P2017 (c) 2014 Valeo */
const uint8 STARTUP_FblSignature[32u] =
{   
    0x46u, 0x42u, 0x4cu, 0x20u, 0x50u, 0x32u, 0x30u, 0x31u,
    0x37u, 0x20u, 0x28u, 0x63u, 0x29u, 0x20u, 0x32u, 0x30u,
    0x31u, 0x34u, 0x20u, 0x56u, 0x61u, 0x6cu, 0x65u, 0x6fu,
    0x00u, 0x55u, 0xAAu, 0x5Au, 0x00u, 0x00u, 0x00u, 0x00u
};

#define STARTUP_STOP_SEC_FBL_SIGNATURE
#include "STARTUP_MemMap.h"

#define STARTUP_START_SEC_ACMSA
#include "STARTUP_MemMap.h"
const uint32 AppCalibMarkerStartArea = 0x5A5A5A5Aul;
#define STARTUP_STOP_SEC_ACMSA
#include "STARTUP_MemMap.h"

#define STARTUP_START_SEC_ACMEA
#include "STARTUP_MemMap.h"
const uint32 AppCalibMarkerEndArea = 0x5A5A5A5Aul;
#define STARTUP_STOP_SEC_ACMEA
#include "STARTUP_MemMap.h"

/******************************************************************************/
/* FUNCTIONS DEFINITION                                                       */
/******************************************************************************/

#define STARTUP_START_SEC_RESET_CODE
#include "STARTUP_MemMap.h"

/******************************************************************************/
/* !FuncName    : STARTUP_START                                               */
/* !Description : Reset function (Entry point of Core 0)                      */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
/* This function is not downloaded when a bootloader is present               */
/* The Core 0 start function called by this STARTUP_START function and by the */
/* bootloader must be the sames.                                              */
/* - Here the called function is cstart                                       */
/* - bootloader call the function define in RESETVECT in FBL_INTF_Cfg.h file  */
void STARTUP_START(void)
{
   __asm("movh.a  %a15,hi:ApplIntJmpTable");
   __asm("lea     %a15,[%a15]lo:ApplIntJmpTable");
   __asm("ld.a    %a15,[%a15]");
   __asm("isync");
   __asm("ji      %a15");
}

#define STARTUP_STOP_SEC_RESET_CODE
#include "STARTUP_MemMap.h"


#define STARTUP_START_SEC_CODE
#include "STARTUP_MemMap.h"
/******************************************************************************/
/* !FuncName    : cstart                                                      */
/* !Description : Called by the StartCore (entry point of Core 1 and 2)       */
/*                                                                            */
/* !LastAuthor  : J. Soufflet                                                 */
/******************************************************************************/
void cstart(void)
{
   __setareg(sp, __USTACK0);
   __dsync();
   __non_return_call(STARTUP_Core0_start);
}


/******************************************************************************/
/* !FuncName    : STARTUP_vidReqAllRamClearAtInit                             */
/* !Description : Requests to clear all RAM on next init                      */
/*                                                                            */
/* !LastAuthor  : J. Soufflet                                                 */
/******************************************************************************/
void STARTUP_vidReqAllRamClearAtInit(void)
{
   STARTUP_bAllRamClearAtInitReq = TRUE;
}

#define STARTUP_STOP_SEC_CODE
#include "STARTUP_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
