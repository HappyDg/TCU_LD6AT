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
**  $FILENAME   : Mcal_DmaLib.h $                                            **
**                                                                           **
**  $CC VERSION : \main\23 $                                                 **
**                                                                           **
**  $DATE       : 2015-03-16 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This header file exports Mcal Dma library                  **
                  type definitions and functions                             **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

#ifndef MCAL_DMALIB_H
#define MCAL_DMALIB_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
#include "Std_Types.h"
#include "IfxDma_reg.h"
#include "IfxScu_reg.h"
#include "IfxCpu_reg.h"
#include "IfxSrc_reg.h"
#include "Mcal.h"


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/
/* Dma CHCFGR register Transfer reload mask */
#define DMA_CHCFGR_TREL_MASK (0xFFFFC000U)
/* Dma CHCFGR register Channel datawidth mask */
#define DMA_CHCFGR_CHDW_MASK (~0x00E00000U)
/* Dma Channel Control register bit positions */
#define DMA_TSR_ECH_BIT_POS (16U)
#define DMA_TSR_DCH_BIT_POS (17U)
#define DMA_CHCSR_SCH_BIT_POS (31U)
#define DMA_CHCFGR_BLKM_BIT_POS (16U)

/* Dma channel status register ICH bit position */
#define DMA_CHCSR_ICH_BIT_POS (18U)

/* Dma channel interrupt control register bit positions */
#define DMA_CHCSR_CICH_POS (26U)
#define DMA_TSR_CTL_POS (18U)
#define DMA_CHCSR_CWRP_POS (25U)

/* Error status register error bits mask */
#define DMA_ERRSR_ERRORMASK (((uint32)1U << 16U) |((uint32)1U << 17U) |  \
            ((uint32)1U << 20U) | ((uint32)1U << 21U) | ((uint32)1U << 24U)  | \
            ((uint32)1U << 25U) | ((uint32)1U << 26U))

/* Macro to Clear WRP Buffer, Dma Channel , TRL Interrupt flags */
#define DMA_CHCSR_CLR_INTFLAGS (0x06000000U)
#define DMA_TSR_CLR_INTFLAGS (0x00040000U)
/* Dma ADICR register interrut control,
   enable transaction request lost clear mask */
#define DMA_ADICR_INTCT_ETRL_CLR_MASK (~0x0C800000U)

/* Dma CHCFGR  reset value */
#define DMA_CHCFGR_RESETVAL (0x00000000U)
/* Dma address control reset value */
#define DMA_ADDR_CTRL_RESETVAL (~0x000FFFFFU)
/* Mask to clear SCH in CHCSR */
#define DMA_CHCSR_SCH_CLR_MASK (~0x80000000U)

#define DMA_CLRE_RESETVAL (0x07330000U)
#define DMA_ERRINTR_ENABLE (0x00000001U)
#define DMA_EER_RESETVAL (0x05030000U)

/* DMA Channel Control Setting for 16 Bit data Width */
#define DMA_CHDW_16BIT    ((uint32)0x1U << 21U)

/* DMA Channel Control Setting for 32 Bit data Width */
#define DMA_CHDW_32BIT    ((uint32)0x2U << 21U)

/* DMA Channel Control Setting for 8 Bit data Width */
#define DMA_CHDW_8BIT    ((uint32)0x0U)

/* DMA Regsiter Start Address Mapping */
#define DMA_MODULE   ((Ifx_DMA volatile *)(void *)&(MODULE_DMA))

/* Dma SRC register addresses */
#define SRC_DMACH0ADDR ((Ifx_SRC_SRCR_Bits volatile *)(void *)&SRC_DMA_DMA0_CH0)

/*******************************************************************************
**                      Global Type Definitions                               **
*******************************************************************************/

/*
Type : Dma_StatusType
This type defines a range of specific status for Dma Driver.
It informs about the Dma status and can be obtained
*/
typedef unsigned int Dma_StatusType;

/*
CD_DMA088:Range of specific error mask values that have to be
          passed to extract the error status
*/
/*
Type : Dma_ErrorMaskType
Specifies the identification for a Error
*/
typedef unsigned int Dma_ErrorMaskType;

/*
CD_DMA089:Error status for DMA Driver.
*/
/*
Type : Dma_ErrorStatusType
This type defines a range of specific status for Dma Driver.
It informs about the Dma Error status and can be obtained.
*/
typedef unsigned int Dma_ErrorStatusType;

/*
Type : Dma_ChannelType
Specifies the identification for a Channel.
*/
typedef enum {
  DMA_CHANNEL0        =   0U,
  DMA_CHANNEL1        =   1U,
  DMA_CHANNEL2        =   2U,
  DMA_CHANNEL3        =   3U,
  DMA_CHANNEL4        =   4U,
  DMA_CHANNEL5        =   5U,
  DMA_CHANNEL6        =   6U,
  DMA_CHANNEL7        =   7U,
  DMA_CHANNEL8        =   8U,
  DMA_CHANNEL9        =   9U,
  DMA_CHANNEL10       =  10U,
  DMA_CHANNEL11       =  11U,
  DMA_CHANNEL12       =  12U,
  DMA_CHANNEL13       =  13U,
  DMA_CHANNEL14       =  14U,
  DMA_CHANNEL15       =  15U,
  DMA_CHANNEL16       =  16U,
  DMA_CHANNEL17       =  17U,
  DMA_CHANNEL18       =  18U,
  DMA_CHANNEL19       =  19U,
  DMA_CHANNEL20       =  20U,
  DMA_CHANNEL21       =  21U,
  DMA_CHANNEL22       =  22U,
  DMA_CHANNEL23       =  23U,
  DMA_CHANNEL24       =  24U,
  DMA_CHANNEL25       =  25U,
  DMA_CHANNEL26       =  26U,
  DMA_CHANNEL27       =  27U,
  DMA_CHANNEL28       =  28U,
  DMA_CHANNEL29       =  29U,
  DMA_CHANNEL30       =  30U,
  DMA_CHANNEL31       =  31U,
  DMA_CHANNEL32       =  32U,
  DMA_CHANNEL33       =  33U,
  DMA_CHANNEL34       =  34U,
  DMA_CHANNEL35       =  35U,
  DMA_CHANNEL36       =  36U,
  DMA_CHANNEL37       =  37U,
  DMA_CHANNEL38       =  38U,
  DMA_CHANNEL39       =  39U,
  DMA_CHANNEL40       =  40U,
  DMA_CHANNEL41       =  41U,
  DMA_CHANNEL42       =  42U,
  DMA_CHANNEL43       =  43U,
  DMA_CHANNEL44       =  44U,
  DMA_CHANNEL45       =  45U,
  DMA_CHANNEL46       =  46U,
  DMA_CHANNEL47       =  47U,
  DMA_CHANNEL48       =  48U,
  DMA_CHANNEL49       =  49U,
  DMA_CHANNEL50       =  50U,
  DMA_CHANNEL51       =  51U,
  DMA_CHANNEL52       =  52U,
  DMA_CHANNEL53       =  53U,
  DMA_CHANNEL54       =  54U,
  DMA_CHANNEL55       =  55U,
  DMA_CHANNEL56       =  56U,
  DMA_CHANNEL57       =  57U,
  DMA_CHANNEL58       =  58U,
  DMA_CHANNEL59       =  59U,
  DMA_CHANNEL60       =  60U,
  DMA_CHANNEL61       =  61U,
  DMA_CHANNEL62       =  62U,
  DMA_CHANNEL63       =  63U,
  DMA_CHANNEL64       =  64U,
  DMA_CHANNEL65       =  65U,
  DMA_CHANNEL66       =  66U,
  DMA_CHANNEL67       =  67U,
  DMA_CHANNEL68       =  68U,
  DMA_CHANNEL69       =  69U,
  DMA_CHANNEL70       =  70U,
  DMA_CHANNEL71       =  71U,
  DMA_CHANNEL72       =  72U,
  DMA_CHANNEL73       =  73U,
  DMA_CHANNEL74       =  74U,
  DMA_CHANNEL75       =  75U,
  DMA_CHANNEL76       =  76U,
  DMA_CHANNEL77       =  77U,
  DMA_CHANNEL78       =  78U,
  DMA_CHANNEL79       =  79U,
  DMA_CHANNEL80       =  80U,
  DMA_CHANNEL81       =  81U,
  DMA_CHANNEL82       =  82U,
  DMA_CHANNEL83       =  83U,
  DMA_CHANNEL84       =  84U,
  DMA_CHANNEL85       =  85U,
  DMA_CHANNEL86       =  86U,
  DMA_CHANNEL87       =  87U,
  DMA_CHANNEL88       =  88U,
  DMA_CHANNEL89       =  89U,
  DMA_CHANNEL90       =  90U,
  DMA_CHANNEL91       =  91U,
  DMA_CHANNEL92       =  92U,
  DMA_CHANNEL93       =  93U,
  DMA_CHANNEL94       =  94U,
  DMA_CHANNEL95       =  95U,
  DMA_CHANNEL96       =  96U,
  DMA_CHANNEL97       =  97U,
  DMA_CHANNEL98       =  98U,
  DMA_CHANNEL99       =  99U,
  DMA_CHANNEL100      = 100U,
  DMA_CHANNEL101      = 101U,
  DMA_CHANNEL102      = 102U,
  DMA_CHANNEL103      = 103U,
  DMA_CHANNEL104      = 104U,
  DMA_CHANNEL105      = 105U,
  DMA_CHANNEL106      = 106U,
  DMA_CHANNEL107      = 107U,
  DMA_CHANNEL108      = 108U,
  DMA_CHANNEL109      = 109U,
  DMA_CHANNEL110      = 110U,
  DMA_CHANNEL111      = 111U,
  DMA_CHANNEL112      = 112U,
  DMA_CHANNEL113      = 113U,
  DMA_CHANNEL114      = 114U,
  DMA_CHANNEL115      = 115U,
  DMA_CHANNEL116      = 116U,
  DMA_CHANNEL117      = 117U,
  DMA_CHANNEL118      = 118U,
  DMA_CHANNEL119      = 119U,
  DMA_CHANNEL120      = 120U,
  DMA_CHANNEL121      = 121U,
  DMA_CHANNEL122      = 122U,
  DMA_CHANNEL123      = 123U,
  DMA_CHANNEL124      = 124U,
  DMA_CHANNEL125      = 125U,
  DMA_CHANNEL126      = 126U,
  DMA_CHANNEL127      = 127U,
  DMA_CHANNEL_INVALID = 0xFFU,  
}Dma_ChannelType;

/*******************************************************************************
**                      Global Constant Declarations                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Variable Declarations                          **
*******************************************************************************/

/*******************************************************************************
**                      Global Function Declarations                          **
*******************************************************************************/

/*Memory Map of the Code*/
#define MCAL_DMALIB_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Syntax           : void Mcal_DmaEnableIntr                                 **
** (                                                                          **
**   uint32 Module                                                            **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Module - Hw module no.                                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Function to Enable Dma Hw channel Interrupt             **
*******************************************************************************/
extern void  Mcal_DmaEnableIntr(Dma_ChannelType Channel);

/*******************************************************************************
** Syntax           :  void Mcal_DmaDisableIntr                               **
** (                                                                          **
**   uint32 Module                                                            **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Module - Hw module no.                                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Function to Enable Dma Hw channel Interrupt             **
*******************************************************************************/
extern void Mcal_DmaDisableIntr(Dma_ChannelType Channel);
/*******************************************************************************
** Syntax           :  void Mcal_DmaCfgNoOfMovesPerTransfer                   **
** (                                                                          **
**   Dma_ChannelType Channel, uint8 NoOfMoves                                 **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                NoOfMoves - No of Dma Moves (logical no)                    **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Function to configure the No of Dma moves per transfer  **
*******************************************************************************/
extern void Mcal_DmaCfgNoOfMovesPerTransfer(
                                     Dma_ChannelType Channel, uint8 NoOfMoves);

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1790_PR1791_1][/cover]
** Syntax           : IFX_INLINE void Mcal_DmaSetSourceAddr                   **
** (                                                                          **
**   Dma_ChannelType Channel, uint32 Address                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                    Address - Source address                                **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Update the Dma Source address register.                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaSetSourceAddr(Dma_ChannelType Channel,
                                                uint32 Address)
{
  uint32 RemapAddress;
  RemapAddress = Mcal_GetDsprReMapAddress(Address);
  MODULE_DMA.CH[Channel].SADR.U = (uint32)RemapAddress;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1790_PR1791_2 ][/cover]
** Syntax           : void Mcal_DmaSetDestAddr                                **
** (                                                                          **
**   Dma_ChannelType Channel, uint32 Address                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                    Address - Destination address                           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Update the Dma Destination address register.            **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaSetDestAddr(Dma_ChannelType Channel ,
                                              uint32 Address)
{
  uint32 RemapAddress;
  RemapAddress = Mcal_GetDsprReMapAddress(Address);
  MODULE_DMA.CH[Channel].DADR.U  = (uint32)RemapAddress;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1790_PR1791_3 ][/cover]
** Syntax           :  void Mcal_DmaSetTxCount                                **
** (                                                                          **
**   Dma_ChannelType Channel, uint32 ReloadValue                              **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                    ReloadValue - Transfer count value                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Update the Dma transmit count in Channel control register.
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaSetTxCount(Dma_ChannelType Channel ,
                                             uint32 ReloadValue)
{
  /*
  This contains the number of DMA transfers for DMA transaction of DMA
  channel 0n. This 14-bit transfer count value is loaded into CHCSRz.TCOUNT
  at the start of a DMA transaction (when TSRz.CH becomes set
  and CHCSRz.TCOUNT = 0). TREL can be written during a running DMA
  transaction because TCOUNT will be updated (decremented) during the DMA
  transaction.
  If TREL = 0 or if TREL = 1, TCOUNT will be loaded with 1 when a new
  transaction is started (at least one DMA transfer must be executed
  per DMA transaction).
  */

  uint32 temp;

  temp = MODULE_DMA.CH[Channel].CHCFGR.U  ;
  temp &= DMA_CHCFGR_TREL_MASK   ;
  temp |= ReloadValue;
  MODULE_DMA.CH[Channel].CHCFGR.U  = temp;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1791_1]        [/cover]
** Syntax           :  void Mcal_DmaEnableHwTransfer                          **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Update the Dma ECH bit in transaction state register    **
***                   for channel to enable Hardware Transaction request.     **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaEnableHwTransfer(Dma_ChannelType Channel)
{
  /*
    Hardware Transaction Request :
    Enable Hardware Transfer Request for DMA Channel 0n
  */
  MODULE_DMA.TSR[Channel].U  |=
                              (uint32)((uint32)1U << DMA_TSR_ECH_BIT_POS);
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1792_1 ]       [/cover]
** Syntax           :  void Mcal_DmaDisableHwTransfer                         **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Update the Dma DCH bit in transaction state register for**
**                     channel to disable the  Hardware Transaction request.  **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaDisableHwTransfer(Dma_ChannelType Channel)
{
  /*
    Hardware Transaction Request :
    Disable Hardware Transfer Request for DMA Channel 0n
  */
  MODULE_DMA.TSR[Channel].U  |=
                                    ((uint32)1U << DMA_TSR_DCH_BIT_POS);
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1790_1]        [/cover]
** Syntax           : void Mcal_DmaStartTransaction                           **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Update the  SCH bit in Channel control and status       **
**                    register to trigger the  Software Transaction request.  **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaStartTransaction(Dma_ChannelType Channel)
{
  /*
   When setting CHCSRz.SCH,  TSRz.CH becomes set to indicate that a
   DMA request is pending for DMA channel z
  */
  MODULE_DMA.CH[Channel].CHCSR.U  |=
                                     ((uint32)1U << DMA_CHCSR_SCH_BIT_POS);
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR96_1 ]        [/cover]
** Syntax           :  Dma_ErrorStatusType Mcal_DmaGetTransReqLostFlag        **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Dma_ErrorStatusType - Dma error status                  **
**                                                                            **
** Description      : Returns the Transaction request lost flag.              **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE Dma_ErrorStatusType Mcal_DmaGetTransReqLostFlag
                                          (Dma_ChannelType Channel)
{
  return
    ((uint32)MODULE_DMA.TSR[Channel].B.TRL);
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1794_1 ]        [/cover]
** Syntax           :  Dma_ErrorStatusType Mcal_DmaGetMoveEngErrFlags         **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Dma_ErrorStatusType - Dma error status                  **
**                                                                            **
** Description      : Returns the move engine error flags.                    **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE Dma_ErrorStatusType Mcal_DmaGetMoveEngErrFlags(
                                                          uint8 MoveEngine)
{
  /*
  The Error Status Register indicates if the DMA controller could
  not answer to a request because the previous request was not terminated.
  It detects following MEx errors
  SER (Source Error), DER (Destination Error)
  FPIER (FPI Bus Error), SRIER (SRI Bus Error), PERER (Peripheral Error)
  Return:
  0 : indicates No Error
  1 : indicates Error occured
  */
  uint32 ErrMask;

  ErrMask = DMA_ERRSR_ERRORMASK; /* TBD chk */
  if(MoveEngine==0)
  return ((Dma_ErrorStatusType) ( ((MODULE_DMA.BLK0.ERRSR.U \
                          & (ErrMask)) > (uint8)0) ? (uint8)1U : (uint8)0));
  else
  return ((Dma_ErrorStatusType) ( ((MODULE_DMA.BLK1.ERRSR.U \
                          & (ErrMask)) > (uint8)0) ? (uint8)1U : (uint8)0));
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1796_1 ]       [/cover]
** Syntax           :  void Mcal_DmaClrErrFlags                               **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Clear the Transaction request flag.                     **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaClrErrFlags(Dma_ChannelType Channel)
{
  MODULE_DMA.TSR[Channel].B.CTL = 1U;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1789_1 ]      [/cover]
** Syntax           :  void Mcal_DmaResetDmaChannel                           **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Reset the dma channels.                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaResetDmaChannel(Dma_ChannelType Channel)
{
  MODULE_DMA.TSR[Channel].B.RST = 1U;
  /* User Note: In ideal case it is better to wait for the channels to reset*/
  /* Wait For Channel to Reset */
  while (( MODULE_DMA.TSR[Channel].B.RST ) != 0U )
  {
  }
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR122_15]        [/cover]
** Syntax           :  void Mcal_DmaSetDataWidth                              **
** (                                                                          **
**   Dma_ChannelType Channel, uint32 DataWidth                                **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                    DataWidth - channel Data width                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Update the Dma channel datawidth in Channel             **
**                    configuration register.                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaSetDataWidth(Dma_ChannelType Channel,
                                               uint32 DataWidth)
{
  MODULE_DMA.CH[Channel].CHCFGR.U  =
    ((MODULE_DMA.CH[Channel].CHCFGR.U  & (DMA_CHCFGR_CHDW_MASK)) |
                (DataWidth << 21U));
}


/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1793_2 ]        [/cover]
** Syntax           :  Dma_StatusType Mcal_DmaGetTransferIntStatus            **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Returns the channel control and status register         **
**                    ICH bit flag.                                           **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE Dma_StatusType Mcal_DmaGetTransferIntStatus(
                                                  Dma_ChannelType Channel)
{
  /*
   This indicates that channel 0n has raised an interrupt for TCOUNT = IRDV
   or if TCOUNT has been decremented (depending on ADICR.INTCT[0].
   0 A channel interrupt has not been detected.
   1 A channel interrupt has been detected.
  */
  return ((Dma_StatusType)
            ((uint32)MODULE_DMA.CH[Channel].CHCSR.U
                           >> DMA_CHCSR_ICH_BIT_POS) & 0x1U);
}

/*******************************************************************************
** Traceability     : [cover parentID=]        [/cover]                       **
** Syntax           :  Dma_StatusType Mcal_DmaGetIntStatus                    **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Returns the channel control register Error flag.        **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE Dma_StatusType Mcal_DmaGetIntStatus(
                                                 Dma_ChannelType Channel)
{

  return ((Dma_StatusType)
            ((uint32)MODULE_DMA.CH[Channel].CHCSR.U& 0x000F0000U));
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1796_2 ]        [/cover]
** Syntax           :  void Mcal_DmaChClrIntrFlags                            **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Clear WRP Buffer Interrupt, Dma Channel Interrupt and   **
**                    TRL flags.                                              **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaChClrIntrFlags(Dma_ChannelType Channel)
{
  MODULE_DMA.CH[Channel].CHCSR.U  =
    MODULE_DMA.CH[Channel].CHCSR.U  | DMA_CHCSR_CLR_INTFLAGS;

   MODULE_DMA.TSR[Channel].U  =
    MODULE_DMA.TSR[Channel].U  | DMA_TSR_CLR_INTFLAGS;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1802_1 ]       [/cover]
** Syntax           :  void Mcal_DmaDisableChIntrTrigger                      **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Disables the Channel Interrupt Trigger.                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaDisableChIntrTrigger
(
  Dma_ChannelType Channel
)
{
  MODULE_DMA.CH[Channel].CHCSR.B.SIT = 0U;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1802_2 ]        [/cover]
** Syntax           :  void Mcal_DmaEnableChIntrTrigger                       **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Enable the Channel Interrupt Trigger.                   **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaEnableChIntrTrigger(Dma_ChannelType Channel)
{
   MODULE_DMA.CH[Channel].CHCSR.B.SIT = 1U;
}


/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR122_1 ]        [/cover]
** Syntax           :  void Mcal_DmaCfgIntControl                             **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Configures Channel Interrupt Control with the
**                    given value                                             **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaCfgIntControl(Dma_ChannelType Channel,
                                                  uint32 value)
{
  value = value & 0x3U;
  MODULE_DMA.CH[Channel].ADICR.B.INTCT  = value ;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR122_2   ]     [/cover]
** Syntax           :  void Mcal_DmaChClrIntctEtrlFlags                       **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Clear the Channel Interrupt control flags.              **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaChClrIntctEtrlFlags(Dma_ChannelType Channel)
{
  MODULE_DMA.CH[Channel].ADICR.U =
                        MODULE_DMA.CH[Channel].ADICR.U  &
                        (DMA_ADICR_INTCT_ETRL_CLR_MASK) ;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR122_3 ]        [/cover]
** Syntax           :  void Mcal_DmaChClrCtlCfg                               **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Clear the bitfields pertaining to different Channel     **
**                    control registers.                                      **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaChClrCtlCfg(Dma_ChannelType Channel)
{
  MODULE_DMA.CH[Channel].CHCFGR.U  = DMA_CHCFGR_RESETVAL;

  MODULE_DMA.CH[Channel].CHCSR.U  =
  MODULE_DMA.CH[Channel].CHCSR.U  & (DMA_CHCSR_SCH_CLR_MASK);

  MODULE_DMA.TSR[Channel].U  =
  (MODULE_DMA.TSR[Channel].U  &  ((~((uint32)1U<<DMA_TSR_ECH_BIT_POS)) |
                                  ( (uint32)1U<<DMA_TSR_DCH_BIT_POS)));

}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR122_4 ]        [/cover]
** Syntax           :  void Mcal_DmaClrAdcr                                   **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Clear the Address control part of ADICR .               **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaClrAdcr(Dma_ChannelType Channel)
{
  MODULE_DMA.CH[Channel].ADICR.U  =
  MODULE_DMA.CH[Channel].ADICR.U  &   DMA_ADDR_CTRL_RESETVAL;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR122_5 ]        [/cover]
** Syntax           :  void Mcal_DmaSetAdicr                                  **
** (                                                                          **
**   Dma_ChannelType Channel, uint32 value                                    **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Channel - Dma channel no.                               **
**                    value  - Address and interrupt control register value   **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : update Address and interrupt control register.          **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaSetAdicr
(
  Dma_ChannelType Channel,
  uint32 value
)
{
  MODULE_DMA.CH[Channel].ADICR.U  = value;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR122_6 ]        [/cover]
** Syntax           :  void Mcal_DmaEnTransReqLostIntr                        **
** (                                                                          **
**   uint32 DmaChannel                                                        **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : DmaChannel - Dma channel no.                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Function to enable the Dma Error interrupt.             **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaEnTransReqLostIntr(Dma_ChannelType Channel)
{
  /* DMA Error (Transaction req lost intr) enable  */
  MODULE_DMA.CH[Channel].ADICR.B.ETRL = 1U;
}

/*******************************************************************************
** Traceability     : [cover parentID=SAS_NAS_MCALLIB_PR1786 ]        [/cover]
** Syntax           :  void Mcal_DmaCfgMeErrIntr                              **
** (                                                                          **
**   uint32 Enable                                                            **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Enable :  1 - Enable ME Error Interrupt.  0 - Disable   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Function to enable/Disable the Dma ME Error interrupt.  **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaCfgMeErrIntr(uint8 Enable)
{
  /* DMA ME Eror Intr enable/Disable  */
  /* Errata fix,.. DMA_TC.016 in BC step
    Byte and Half-word Write Accesses to specific Registers not supported
  */
  MODULE_DMA.ERRINTR.U |=  Enable;
}

/*******************************************************************************
** Traceability     :                                                         **
** Syntax           :  void Mcal_DmaGetTransferCount                          **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Enable :  1 - Enable ME Error Interrupt.  0 - Disable   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Function to enable/Disable the Dma ME Error interrupt.  **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE uint32 Mcal_DmaGetTransferCount(Dma_ChannelType Channel)
{
  /*
    Hardware Transaction Request :
    Enable Hardware Transfer Request for DMA Channel 0n
  */
  return (MODULE_DMA.CH[Channel].CHCSR.B.TCOUNT);
}

/*******************************************************************************
** Traceability     :                                                         **
** Syntax           :  void Mcal_DmaClrIntrTriggerFlag                        **
** (                                                                          **
**   Dma_ChannelType Channel                                                  **
** )                                                                          **
**                                                                            **
** Service ID       : NA                                                      **
**                                                                            **
** Sync/Async       : Asynchronous                                            **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Enable :  1 - Enable ME Error Interrupt.  0 - Disable   **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None.                                                   **
**                                                                            **
** Description      : Function to enable/Disable the Dma ME Error interrupt.  **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for inline functions defined in header
 files*/
_IFXEXTERN_ IFX_INLINE void Mcal_DmaClrIntrTriggerFlag(Dma_ChannelType Channel)
{
  /*
    Clear the ICH bit in CHCSR
  */
  MODULE_DMA.CH[Channel].CHCSR.B.CICH = 1U;
}

/*Memory Map of the Code*/
#define MCAL_DMALIB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* MCAL_DMALIB_H  */
