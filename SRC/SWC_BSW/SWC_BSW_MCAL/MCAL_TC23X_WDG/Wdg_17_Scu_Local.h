/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2013)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Wdg_17_Scu_Local.h $                                       **
**                                                                           **
**  $CC VERSION : \main\dev_tc23x_as4.0.3\12 $                               **
**                                                                           **
**  $DATE       : 2015-05-27 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains enable and disable functionalities of   **
**                TOM channels of WDG driver.                                **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

 
#ifndef WDG_17_SCU_LOCAL_H
#define WDG_17_SCU_LOCAL_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

#include "Std_Types.h"
#include "Wdg_17_Scu.h"

/* Gtm related information are brought in from here */
#include "Gtm.h"

/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Max Reload Value for TOM channel*/
#define WDG_TOM_MAX_VAL                (0x0000FFFFU)

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_ALL_PR128][/cover]              **
** Syntax      : IFX_LOCAL_INLINE  void Wdg_lDisableGtmTomChannel(            **
**                                                     uint8 GtmModuleNumber, **
**                                                     uint8 GtmChannelNumber)* 
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-reentrant                                           **
**                                                                            **
** Parameters(in)   : GtmModuleNumber - TOM number                            **
**                    GtmChannelNumber - TOM channel number                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function disable TOM channel                       **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Wdg_lDisableGtmTomChannel(uint8 GtmModuleNumber, 
                                      uint8 GtmChannelNumber)
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in 
  header files*/
{
  if(GtmChannelNumber < GTM_TOM_TGC0_CHOSEN)
  {
    (*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_TGC[GtmModuleNumber]. \
                                 TGC[GTM_TGC0].ENDIS_STAT.U =   \
     (unsigned_int)(GTM_TOM_CHAN_DISABLE <<  \
                        (GTM_TOM_BITS_PER_CHAN * GtmChannelNumber));
  }
  else
  {
    (*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_TGC[GtmModuleNumber]. \
                                  TGC[GTM_TGC1].ENDIS_STAT.U =   \
     (unsigned_int)(GTM_TOM_CHAN_DISABLE <<  \
         (GTM_TOM_BITS_PER_CHAN * (GtmChannelNumber -  \
                                       GTM_TOM_CHANNELS_PER_TGC)));
  }
}

/*******************************************************************************
**                                                                            **
** Syntax           :  IFX_LOCAL_INLINE void Wdg_lEnableGtmTomChannel(        **
**                                                     uint8 GtmModuleNumber, * 
**                                                     uint8 GtmChannelNumber,**
**                                                     uint32 Ticks)          **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-reentrant                                           **
**                                                                            **
** Parameters(in)   : GtmModuleNumber - TOM number                            **
**                    GtmChannelNumber - TOM channel number                   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : none                                                    **
**                                                                            **
** Description      : This function to enable TOM channel                     **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Wdg_lEnableGtmTomChannel(uint8 GtmModuleNumber,
                                           uint8 GtmChannelNumber,uint32 Ticks)
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in 
  header files*/
{
  /* Set the TOM timer channel Counter CN0 to 0 */
  ((*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_CH[GtmModuleNumber].
                             CH[GtmChannelNumber].CN0.U) = (uint32)0x00U;

  /* Load the TOM timer channel CM0 with callback time period */
  ((*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_CH[GtmModuleNumber].
                     CH[GtmChannelNumber].CM0.U) = (uint32)Ticks;
  /* Load the TOM timer channel SR register with callback time period */
  ((*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_CH[GtmModuleNumber].
                  CH[GtmChannelNumber].SR0.U) = (uint32)Ticks;
  /* Check channel belongs to TGC0/TGC1 */ 
  if(GtmChannelNumber < GTM_TOM_TGC0_CHOSEN)
  {    
    (*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_TGC[GtmModuleNumber].
                 TGC[GTM_TGC0].ENDIS_STAT.U =(unsigned_int)
                 (GTM_TOM_ENABLE <<(GTM_TOM_BITS_PER_CHAN * GtmChannelNumber));
  }
  else
  {
    (*(Ifx_GTM_TOMx*)(void*)(MODULE_GTM.TOM)).TOM_TGC[GtmModuleNumber].
                                            TGC[GTM_TGC1].ENDIS_STAT.U =  \
          (unsigned_int)(GTM_TOM_ENABLE << (GTM_TOM_BITS_PER_CHAN *		\
                              (GtmChannelNumber - GTM_TOM_CHANNELS_PER_TGC)));
  }
}

/*******************************************************************************
** Syntax           : IFX_NLINE void Wdg_lDisableGtmChannel(uint8 GtmArrayIdx,**
**                                       uint8 GtmModuleNumber,               **
**                                       uint8 GtmChannelNumber)              **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-reentrant                                           **
**                                                                            **
** Parameters (in)  : uint8 GtmArrayIdx, uint8 GtmModuleNumber,               **
**                    uint8 GtmChannelNumber                                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Function to disable GTM Channel                         **
**                                                                            **
*******************************************************************************/
IFX_INLINE void Wdg_lDisableGtmChannel(uint8 GtmArrayIdx, uint8 GtmModuleNumber,
                                     uint8 GtmChannelNumber)
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in 
  header files*/
{
  UNUSED_PARAMETER(GtmArrayIdx)
   /* Disable the TOM timer channel */
 Wdg_lDisableGtmTomChannel(GtmModuleNumber,GtmChannelNumber);
}  
   
/*******************************************************************************
** Syntax           : IFX_INLINE void Wdg_lEnableGtmChannel(uint8 GtmArrayIdx,**
**                                       uint8 GtmModuleNumber,               **
**                                       uint8 GtmChannelNumber,              **
**                                       uint32 GtmTicks)                     **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-reentrant                                           **
**                                                                            **
** Parameters (in)  : uint8 GtmArrayIdx, uint8 GtmModuleNumber,               * 
**                    uint8 GtmChannelNumber, uint32 GtmTicks                 **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Function to enable GTM Channel                          **
**                                                                            **
*******************************************************************************/
IFX_INLINE void Wdg_lEnableGtmChannel(uint8 GtmArrayIdx, uint8 GtmModuleNumber,
                                    uint8 GtmChannelNumber, uint32 GtmTicks)  
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in 
  header files*/
{  
   /* Note: unused parameter : uint8 GtmArrayIdx */
   UNUSED_PARAMETER(GtmArrayIdx)   
   /* Enable the TOM timer channel */
   Wdg_lEnableGtmTomChannel(GtmModuleNumber,GtmChannelNumber,GtmTicks);
} 



/*******************************************************************************
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Wdg_lGtmConfigCheck(void)*
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-reentrant                                           **
**                                                                            **
** Parameters(in)   : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK or E_NOT_OK                                        **
**                                                                            **
** Description      : This function checks that the (hardware specific)       **
**                    contents of the GTM configuration is within the         **
**                    allowed boundaries.                                     **
**                                                                            **
*******************************************************************************/
#if (WDG_DEV_ERROR_DETECT == STD_ON)
IFX_LOCAL_INLINE Std_ReturnType Wdg_lGtmConfigCheck(void)
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in 
  header files*/
{
  uint8 Ret_Val;
  uint8 CoreId;
  uint8 GtmArrayIdx;
  Ret_Val = E_OK;
  
  CoreId = Mcal_GetCoreId();
 
  /* Get GTM index */
  GtmArrayIdx = Wdg_kConfigPtr->WdgQmIndex[CoreId];
    /* Check for correct Module, Channel is selceted and
      The timer reload values are within the range of the hardware */
    if((Wdg_kConfigPtr->GtmConf[GtmArrayIdx].FastServiceGtmCbkTicks>
                                                     WDG_TOM_MAX_VAL)||
     (Wdg_kConfigPtr->GtmConf[GtmArrayIdx].SlowServiceGtmCbkTicks>
                                                    WDG_TOM_MAX_VAL))
    {
      Ret_Val = E_NOT_OK;
    }
  
 return (Ret_Val);

}

#endif
/*(WDG_DEV_ERROR_DETECT == STD_ON) */

#endif 
/* WDG_17_SCU_LOCAL_H */