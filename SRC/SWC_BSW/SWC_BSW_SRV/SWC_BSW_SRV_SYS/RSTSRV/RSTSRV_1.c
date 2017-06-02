/******************************************************************************/
/* !Layer           : SRVL                                                    */
/* !Component       : RSTSRV                                                  */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : RSTSRV_1.c                                              */
/* !Description     : Internal functions of RSTSRV Component                  */
/*                                                                            */
/* !Reference       : V03 NT 07 02929                                         */
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
#include "Std_Limits.h"
#include "DEVHAL.h"
//#include "NvMIf.h"
#include "RSTSRV.h"
#include "RSTSRV_Private.h"
#include "SWFAIL.h"


#define RSTSRV_START_SEC_CODE
#include "RSTSRV_MemMap.h"

/******************************************************************************/
/* !FuncName    : RSTSRV_vidInitEntry                                         */
/* !Description :                                                             */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void RSTSRV_vidInitEntry(void)
{
   uint32 u32LocalHotResetCtr;


   u32LocalHotResetCtr = 1u + ( (uint32)RSTSRV_u16HotResetCtr);
   if (u32LocalHotResetCtr > 65535u)
   {
      u32LocalHotResetCtr = 65535u;
   }
   RSTSRV_u16HotResetCtr = (uint16)u32LocalHotResetCtr;

   /* Equivalent to a Write Now */
   //(void)NvMIf_WritePRAMBlock(NvM_BSW_BLOCK_RESET);
}

/******************************************************************************/
/* !FuncName    : RSTSRV_vidPowerDownEntry                                    */
/* !Description :                                                             */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void RSTSRV_vidPowerDownEntry(void)
{

   RSTSRV_u16HotResetCtr = UINT16_MIN;
   //NvMIf_vidSetRamBlockStatus(NvM_BSW_BLOCK_RESET, TRUE);
}

/******************************************************************************/
/* !FuncName    : RSTSRV_vidMainFunction                                      */
/* !Description : 5s after init, resets are no more considered as consecutive */
/*                No more need to force to enter the reprog mode              */
/*                                                                            */
/* !LastAuthor  : J. Soufflet                                                 */
/******************************************************************************/
void RSTSRV_vidMainFunction(void)
{
//<<   if (DEVHAL_bCheckEmulCard() == TRUE)
{
      if (RSTSRV_u16TimeAfterInit < 50U) /* 50 * 100ms = 5s */
   {
         RSTSRV_u16TimeAfterInit++;
   }
   else
   {
         RSTSRV_u16ConsecutiveRstCtr = 0;
      }
   }
}

#define RSTSRV_STOP_SEC_CODE
#include "RSTSRV_MemMap.h"

/*------------------------------- end of file --------------------------------*/
