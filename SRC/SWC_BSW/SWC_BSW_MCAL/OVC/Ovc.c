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
/* !File            : OVC.c                                                                                           */
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
/* 1 / OVC_vidInit                                                                                                    */
/* 2 / OVC_vidCopy                                                                                                    */
/* 3 / OVC_u32GetPhysPage                                                                                             */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5676/adc_api.h_v                     $*/
/* $Revision::   1.10                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/
#include "Std_Types.h"
#include "Emem.h"
#include "Ovc.h"
#include "IfxCpu.h"
#include "IfxScuWdt.h"


/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
#define OVC_u32AVL_CORE_MASK ((1u << (sizeof(OVC_akpstModule) / sizeof(Ifx_OVC *))) - 1u)

#define OVC_u32OVCCON_DCINVAL_NOP    0u
#define OVC_u32OVCCON_DCINVAL_INVLD  (1u << 18)
#define OVC_u32OVCCON_OVSTRT_NOP     0u
#define OVC_u32OVCCON_OVSTRT_ACTVT   (1u << 16)
#define OVC_u32OVCCON_OVCONF_RDY     (1u << 24)
#define OVC_u32OVCCON_POVCONF_WR_ENA (1u << 25)
#define OVC_u32OVCCON_OVSTP_DEACTVT  (1u << 17)

/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/
#define OVC_START_SEC_CONST_UNSPECIFIED
#include "OVC_MemMap.h"
Ifx_OVC * const OVC_akpstModule[] =
{
#ifdef MODULE_OVC0
   &MODULE_OVC0
#ifdef MODULE_OVC1
   , &MODULE_OVC1
#ifdef MODULE_OVC2
   , &MODULE_OVC2
#ifdef MODULE_OVC3
   , &MODULE_OVC3
#endif
#endif
#endif
#endif
};
#define OVC_STOP_SEC_CONST_UNSPECIFIED
#include "OVC_MemMap.h"

/**********************************************************************************************************************/
/* FUNCTIONS                                                                                                          */
/**********************************************************************************************************************/
#define OVC_START_SEC_CODE
#include "OVC_MemMap.h"
/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : OVC_vidInit                                                                                        */
/*                                                                                                                    */
/* !Description : Initializes OVC                                                                                     */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : Reset                                                                                                  */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void OVC_vidInit(void)
{
   uint32              u32LocBlkIdx;
   const OVC_tstBlk  * pudtBlk;
   Ifx_OVC_BLK         stLocBlk;
   uint16              u16LocPwd;


   /* !Comment: Overlay Registers are Safety Endinit Protected                */
   u16LocPwd = IfxScuWdt_getSafetyWatchdogPassword();
   IfxScuWdt_clearSafetyEndinit(u16LocPwd);

   /* !Comment: Stop overlay                                                */
   MODULE_SCU.OVCCON.B.OVSTRT = 0;
   MODULE_SCU.OVCCON.B.OVSTP  = 1;
   MODULE_SCU.OVCCON.U        = 0;
   IfxScuWdt_setSafetyEndinit(u16LocPwd);

   for (u32LocBlkIdx = 0; u32LocBlkIdx < sizeof(OVC_akstCfg) / (OVC_u8NB_CFG * sizeof(OVC_tstBlk)); u32LocBlkIdx++)
   {
      //>>Wdg_vidRefreshWatchdog();
      pudtBlk = &OVC_akstCfg[OVC_u8GET_CFG_IDX()][u32LocBlkIdx];
      if (  (((uint32)pudtBlk->pu32Src >> 24) == OVC_u32ADDR_CACHED_FLASH_MSB)
         || (((uint32)pudtBlk->pu32Src >> 24) == OVC_u32ADDR_NONCACHED_FLASH_MSB))
      {
         /* !Comment: Works only for FLASH as source */
         if (pudtBlk->bToInit == TRUE)
         {
            if (((uint32)pudtBlk->pu32Dest >> 24) == OVC_u32ADDR_EMEM_MSB)
            {
               /* !Comment: EMEM is the destination */
               //>>EMEM_vidUnlock(pudtBlk->pu32Dest, (uint32) pudtBlk->s32Size);
            }
            OVC_vidCopy(pudtBlk->pu32Src, pudtBlk->pu32Dest, pudtBlk->s32Size);
         }

         stLocBlk.RABR.B.OBASE = ((((uint32)pudtBlk->pu32Dest) & 0x003FFFFFu) >> 5);
         stLocBlk.RABR.B.OMEM  = OVC_u8GET_MEM(pudtBlk->pu32Dest);
         stLocBlk.RABR.B.OVEN  = pudtBlk->bEna; 
         stLocBlk.OTAR.B.TBASE = ((((uint32)pudtBlk->pu32Src) & 0x0FFFFFFFu) >> 5);
         stLocBlk.OMASK.B.OMASK = OVC_u32GET_MASK_SIZE(pudtBlk->s32Size);

         if ((pudtBlk->u8Cores & OVC_u8CORE_0) != 0)
         {
            MODULE_OVC0.BLK[u32LocBlkIdx].RABR.U  = stLocBlk.RABR.U;
            MODULE_OVC0.BLK[u32LocBlkIdx].OTAR.U  = stLocBlk.OTAR.U;
            MODULE_OVC0.BLK[u32LocBlkIdx].OMASK.U = stLocBlk.OMASK.U;
            MODULE_OVC0.OSEL.U |= (1u << u32LocBlkIdx);        
         }
/*       if ((pudtBlk->u8Cores & OVC_u8CORE_1) != 0)
         {
            MODULE_OVC1.BLK[u32LocBlkIdx].RABR.U  = stLocBlk.RABR.U;
            MODULE_OVC1.BLK[u32LocBlkIdx].OTAR.U  = stLocBlk.OTAR.U;
            MODULE_OVC1.BLK[u32LocBlkIdx].OMASK.U = stLocBlk.OMASK.U;
            MODULE_OVC1.OSEL.U |= (1u << u32LocBlkIdx);        
         }*/
/*       if ((pudtBlk->u8Cores & OVC_u8CORE_2) != 0)
         {

            MODULE_OVC2.BLK[u32LocBlkIdx].RABR.U  = stLocBlk.RABR.U;
            MODULE_OVC2.BLK[u32LocBlkIdx].OTAR.U  = stLocBlk.OTAR.U;
            MODULE_OVC2.BLK[u32LocBlkIdx].OMASK.U = stLocBlk.OMASK.U;   
            MODULE_OVC2.OSEL.U |= (1u << u32LocBlkIdx);
         }*/
      }
   }
   u16LocPwd = IfxScuWdt_getSafetyWatchdogPassword();
   IfxScuWdt_clearSafetyEndinit(u16LocPwd);
   MODULE_SCU.OVCENABLE.U |= 0x1;
   __dsync();
   MODULE_SCU.OVCCON.U = 0x1;
   __dsync();
   MODULE_SCU.OVCCON.U = 0x40001;
   __dsync();
   MODULE_SCU.OVCCON.U = 0x10001;
   __dsync();
   MODULE_SCU.OVCCON.U = 0x03010001;
   __dsync();
   IfxScuWdt_setSafetyEndinit(u16LocPwd);
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : OVC_vidCopy                                                                                         */
/*                                                                                                                    */
/* !Description : Copy an area to another                                                                             */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : Reset                                                                                                  */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void OVC_vidCopy(uint32 * pu32Src, uint32 * pu32Dest, sint32 s32Size)
{
	sint32 s32NbLoop;

	
   if (s32Size > 0)
   {
      s32Size   = (sint32)((uint32)(s32Size + 3) >> 2);
		s32NbLoop = (sint32)(((uint32)s32Size + 7u) >> 3u);

      switch(s32Size & 7u)
      {
         case 0:  do {  *pu32Dest++ = *pu32Src++;
         case 7:        *pu32Dest++ = *pu32Src++;
         case 6:        *pu32Dest++ = *pu32Src++;
         case 5:        *pu32Dest++ = *pu32Src++;
         case 4:        *pu32Dest++ = *pu32Src++;
         case 3:        *pu32Dest++ = *pu32Src++;
         case 2:        *pu32Dest++ = *pu32Src++;
         case 1:        *pu32Dest++ = *pu32Src++;
                     } while(--s32NbLoop > 0);
      }
	}
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : OVC_u32GetPhysPage                                                                                  */
/*                                                                                                                    */
/* !Description : Returns the physical address of one logical address                                                 */
/* !Number      : 3                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : Runnable                                                                                               */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
uint32 OVC_u32GetPhysPage(uint32 * pu32LogAddr)
{
   uint32 u32LocBlkIdx;
   uint32 u32Start;
   uint32 u32LogAd;


   u32LogAd = (uint32)pu32LogAddr;
   if ((u32LogAd >> 24) == OVC_u32ADDR_CACHED_FLASH_MSB)
   {
      u32LogAd += ((OVC_u32ADDR_NONCACHED_FLASH_MSB - OVC_u32ADDR_CACHED_FLASH_MSB) << 24);
   }
   for (u32LocBlkIdx = 0; u32LocBlkIdx < sizeof(OVC_akstCfg) / (OVC_u8NB_CFG * sizeof(OVC_tstBlk)); u32LocBlkIdx++)
   {
      u32Start = (uint32)OVC_akstCfg[OVC_u8GET_CFG_IDX()][u32LocBlkIdx].pu32Src;
      if ((u32Start <= u32LogAd) && ((u32Start + OVC_akstCfg[OVC_u8GET_CFG_IDX()][u32LocBlkIdx].s32Size) > u32LogAd))
      {
         return((uint32)OVC_akstCfg[OVC_u8GET_CFG_IDX()][u32LocBlkIdx].pu32Dest);
      }
   }
   return((uint32)pu32LogAddr);
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : OVC_u32GetPhysPage                                                                                  */
/*                                                                                                                    */
/* !Description : Returns the physical address of one logical address                                                 */
/* !Number      : 3                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !Trigger  : Runnable                                                                                               */
/*                                                                                                                    */
/* !LastAuthor  :  E. Moas                                                                                            */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
uint32 OVC_u32GetPhysAddr(uint8 * pu8LogAddr)
{
   uint32             u32LocBlkIdx;
   uint32             u32Start;
   uint32             u32LogAd;
   uint32             u32LocLogAd;
   uint32             u32CoreIdMsk;
   const OVC_tstBlk * pstBlk;
   uint32             u32Osel;


   u32LogAd = (uint32)pu8LogAddr;
   /* go to non-cached */
   u32LogAd |= OVC_u32CACHED_TO_NONCACHED_MASK;
   u32CoreIdMsk = IfxCpu_getCoreId();
   if (u32CoreIdMsk < (sizeof(OVC_akpstModule) / sizeof(Ifx_OVC *)))
   {
      u32Osel      = OVC_akpstModule[u32CoreIdMsk]->OSEL.U; 
      u32CoreIdMsk = 1u << u32CoreIdMsk;
      pstBlk       = &OVC_akstCfg[OVC_u8GET_CFG_IDX()][0];
      for (u32LocBlkIdx = 0; u32LocBlkIdx < sizeof(OVC_akstCfg) / (OVC_u8NB_CFG * sizeof(OVC_tstBlk)); u32LocBlkIdx++)
      {
         u32Start    = (uint32)pstBlk->pu32Src | OVC_u32CACHED_TO_NONCACHED_MASK;
         u32LocLogAd = u32LogAd & (~(pstBlk->s32Size - 1));
         if (u32Start == u32LocLogAd)
         {
            if ((pstBlk->bEna == TRUE) && ((u32Osel & (1u << u32LocBlkIdx)) != 0) && ((pstBlk->u8Cores & u32CoreIdMsk) != 0))
            {
               return((u32LogAd & (pstBlk->s32Size - 1)) | (uint32)(pstBlk->pu32Dest));
            }
            else
            {
               return((uint32)pu8LogAddr);
            }
         }
         pstBlk++;
      }
   }
   return((uint32)pu8LogAddr);
}
#define OVC_STOP_SEC_CODE
#include "OVC_MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
