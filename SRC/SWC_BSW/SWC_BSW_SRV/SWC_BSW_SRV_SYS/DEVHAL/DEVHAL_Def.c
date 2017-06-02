/******************************************************************************/
/* !Layer           : HAL                                                     */
/* !Component       : DEVHAL                                                  */
/* !Description     : DEVHAL Component                                        */
/*                                                                            */
/* !File            : DEVHAL_Def.c                                            */
/* !Description     : DEVHAL data definition                                  */
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
 * %PID: %
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#include "Std_Types.h"
#include "DEVHAL_Def.h"
#include "IfxOvc_reg.h"
#include "IfxOvc_regdef.h"

/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/

#define DEVHAL_START_SEC_VAR_CLEARED_BOOLEAN
#include "DEVHAL_MemMap.h"

boolean DEVHAL_bIsFlsLoaderInitialized;
boolean DEVHAL_bIsFlsLoaderErasing;
boolean DEVHAL_bIsFlsLoaderErased;
boolean DEVHAL_bIsFlsLoaderCopied;
boolean DEVHAL_bIsInitialized;

#define DEVHAL_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "DEVHAL_MemMap.h"

#define DEVHAL_START_SEC_VAR_CLEARED_8BIT
#include "DEVHAL_MemMap.h"

uint8 DEVHAL_u8CheckEngineState;

#define DEVHAL_STOP_SEC_VAR_CLEARED_8BIT
#include "DEVHAL_MemMap.h"

#define DEVHAL_START_SEC_VAR_INIT_UNSPECIFIED
#include "DEVHAL_MemMap.h"

#define DEVHAL_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "DEVHAL_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
