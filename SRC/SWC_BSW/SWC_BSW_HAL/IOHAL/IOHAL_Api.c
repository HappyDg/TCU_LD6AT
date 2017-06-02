/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer          : BSW                                                                                              */
/*                                                                                                                    */
/* !Component      : HAL                                                                                              */
/*                                                                                                                    */
/* !Module         : IOHAL                                                                                            */
/* !Description    : APIs of the IOHAL component                                                                      */
/*                                                                                                                    */
/* !File           : IOHAL_Api.c                                                                                      */            
/*                                                                                                                    */
/* !Target         : All                                                                                              */
/*                                                                                                                    */
/* !Vendor         : Valeo                                                                                            */
/*                                                                                                                    */
/* Coding language : C                                                                                                */
/*                                                                                                                    */
/* COPYRIGHT 2013 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
***********************************************************************************************************************/
/* 1 / IOHAL_vidInit                                                                                                  */
/**********************************************************************************************************************/
   
#include "IOHAL_Api.h"
#include "IOHAL_Cfg.h"
#include "IOHAL_Cfg_I.h"

/**********************************************************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                                                         */
/**********************************************************************************************************************/

#define IOHAL_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Description: Initializes all internal IOHAL variables.                                                            */
/* !Number     : 1                                                                                                    */
/*                                                                                                                    */
/* !LastAuthor : KELK (TELNET)                                                                                        */
/**********************************************************************************************************************/
void IOHAL_vidInit(void)
{
	IOHAL_vidCfgInit();
}

#define IOHAL_STOP_SEC_CODE
#include "MemMap.h"


/*--------------------------------------------------- end of file ----------------------------------------------------*/
