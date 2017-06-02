/******************************************************************************/
/* !Layer           : SRV                                                     */
/* !Component       : SUPSRV                                                  */
/* !Description     : Supplier Services component                             */
/*                                                                            */
/* !File            : SUPSRV.h                                                */
/* !Description     : SUPSRV services declaration                             */
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

#ifndef SUPSRV_H
#define SUPSRV_H

#include "Std_Types.h"

#include "v_cfg.h"
#include "v_def.h"
#include "fbl_ap.h"


/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
#define SUPSRV_NO_ACTION                0
#define SUPSRV_ENTER_REPROG_MODE        1
#define SUPSRV_PROD_TEST                2


/******************************************************************************/
/* DATA DECLARATION                                                           */
/******************************************************************************/

#define SUPSRV_START_SEC_VAR_INIT_UNSPECIFIED
#include "SUPSRV_MemMap.h"

/* SUPSRV_enuRequest is a multicore variable                                  */
/* written by core 1 and read by core 2 => shall be mapped in non cached area */
extern uint8 SUPSRV_enuRequest;

#define SUPSRV_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SUPSRV_MemMap.h"


/******************************************************************************/
/* GLOBAL FUNCTION DECLARATION                                                */
/******************************************************************************/

#define SUPSRV_START_SEC_CODE
#include "SUPSRV_MemMap.h"

Std_ReturnType SUPSRV_udtReadFblTlf35584Version(uint16 *u16Tlf35584Version);
void           SUPSRV_vidEnterReprogMode(uint16 u16MicroControllerTemp);
void           SUPSRV_vidJumpToLoader(void);
Std_ReturnType SUPSRV_udtJumpToProdTest(uint8 u8TprodParameter);
void           SUPSRV_vidMainfunction(void);

#define SUPSRV_STOP_SEC_CODE
#include "SUPSRV_MemMap.h"


#endif /* SUPSRV_H */

/*------------------------------- end of file --------------------------------*/
