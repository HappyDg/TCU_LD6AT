/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : DMA                                                                                             */
/*                                                                                                                    */
/* !Component       : DMA                                                                                             */
/* !Description     : DMA unit                                                                                        */
/*                                                                                                                    */
/* !Module          : DMA_API                                                                                         */
/* !Description     : API of DMA unit                                                                                 */
/*                                                                                                                    */
/* !File            : DMA.h                                                                                           */
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

#ifndef DMA_H
#define DMA_H

#include "Std_Types.h"
#include "Std_Limits.h"
#include "micro.h"
#include "Os_api.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
/* CLC register */
#define DMA_u32CLC_DISR_ENA             (0u << 0)
#define DMA_u32CLC_DISR_DISA            (1u << 0)
#define DMA_u32CLC_DISS_MASK            (1u << 1)
#define DMA_u32CLC_EDIS_SLEEP_MOD_ENA   (0u << 3)
#define DMA_u32CLC_EDIS_SLEEP_MOD_DISA  (1u << 3)

/* MEMCON register */
#define DMA_u32MEMCON_INTERR_MASK       (1u << 2)
#define DMA_u32MEMCON_INTERR_RAM_ERR    (1u << 2)
#define DMA_u32MEMCON_INTERR_NO_ERR     (0u << 2)
#define DMA_u32MEMCON_RMWERR_MASK       (1u << 4)
#define DMA_u32MEMCON_RMWERR_RMW_ERR    (1u << 4)
#define DMA_u32MEMCON_RMWERR_NO_ERR     (0u << 4)
#define DMA_u32MEMCON_DATAERR_MASK      (1u << 6)
#define DMA_u32MEMCON_DATAERR_RMW_ERR   (1u << 6)
#define DMA_u32MEMCON_DATAERR_NO_ERR    (0u << 6)
#define DMA_u32MEMCON_PMIC_MASK         (1u << 8)
#define DMA_u32MEMCON_PMIC_ALLOW_ACC    (1u << 8)
#define DMA_u32MEMCON_PMIC_FORBID_ACC   (0u << 8)
#define DMA_u32MEMCON_ERRDIS_MASK       (1u << 9)
#define DMA_u32MEMCON_ERRDIS_NO_SPB_ERR (1u << 9)
#define DMA_u32MEMCON_ERRDIS_SPB_ERR    (0u << 9)

/* DMA_CLREx (x = 0-1) DMA Clear Error Register x */
#define DMA_u32CLRE_CSER_CLR             (1u << 16)
#define DMA_u32CLRE_CDER_CLR             (1u << 17)
#define DMA_u32CLRE_CSPBER_CLR           (1u << 20)
#define DMA_u32CLRE_CSRIER_CLR           (1u << 21)
#define DMA_u32CLRE_CRAMER_CLR           (1u << 24)
#define DMA_u32CLRE_CSLLER_CLR           (1u << 25)
#define DMA_u32CLRE_CDLLER_CLR           (1u << 26)



/**********************************************************************************************************************/
/* TYPEDEF                                                                                                            */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/
/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description :                                                                                                     */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
#define DRV_START_SEC_CODE
#include "DRV_MemMap.h"
extern void DMA_vidStartDeInit(void);
extern boolean DMA_vidChckDeInit(void);
#define DRV_STOP_SEC_CODE
#include "DRV_MemMap.h"

#endif /* DMA_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
