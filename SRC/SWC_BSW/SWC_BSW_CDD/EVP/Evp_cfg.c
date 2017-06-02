/******************************************************************************/
/* !Layer           : HAL                                                     */
/* !Component       : EVP                                                     */
/* !Description     : EVP safe supply device management                       */
/*                                                                            */
/* !File            : EVP_Def.c                                               */
/* !Description     : Data definition of EVP component.                       */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  :  C                                                      */
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
#include "Evp_api.h"

/******************************************************************************/
/* CONSTANTS DEFINITION                                                       */
/******************************************************************************/

#define EVP_START_SEC_CONST_UNSPECIFIED
#include "EVP_MemMap.h"
const EVP_tstGrp EVP_akstGrp[EVP_u8NB_GROUP] =
{
    {
       EVP_pstGET_TGC_PTR(GRP_0),
       EVP_pstGET_CH_PTR(GRP_0),
       {
           EVP_stCH_INIT_CFG(ADC_TRIG_0),
           EVP_stCH_INIT_CFG(ADC_TRIG_1),
           {0,0,0,0},
           {0,0,0,0},
           {0,0,0,0},
           {0,0,0,0}
       },
       EVP_u32GRP_0_UPDATE_ENABLE,
       EVP_u32GRP_0_UPDATE_DISABLE,
       EVP_u32GRP_0_SIZE
    }
};
#define EVP_STOP_SEC_CONST_UNSPECIFIED
#include "EVP_MemMap.h"

/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/

/*------------------------------ end of file ---------------------------------*/
