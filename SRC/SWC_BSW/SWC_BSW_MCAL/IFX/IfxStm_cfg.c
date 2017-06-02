/******************************************************************************/
/* !Layer           : MCAL                                                    */
/* !Component       : Framework                                               */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : IFXSTM_CFG.c                                            */
/* !Description     : Configuration of framework component managing STM       */
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

/******************************************************************************/
/*                           Include                                          */
/******************************************************************************/
#include "IfxStm_cfg.h"
#include "Ifx_Types.h"
/******************************************************************************/
/*                       Exported Constants                                   */
/******************************************************************************/
#define IFXSTM_START_SEC_CONST_UNSPECIFIED
#include "IFXSTM_MemMap.h"

const IfxModule_IndexMap IfxStm_cfg_indexMap[IFXSTM_COUNT] = {
    {&MODULE_STM0, IfxStm_ResourceStm_0},
};

#define IFXSTM_STOP_SEC_CONST_UNSPECIFIED
#include "IFXSTM_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
