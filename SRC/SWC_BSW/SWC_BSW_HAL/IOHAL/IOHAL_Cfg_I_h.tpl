/*INSERTION_TRADOIL*/
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer           : BSW                                                                                             */
/*                                                                                                                    */
/* !Component       : HAL                                                                                             */
/* !Description     : IOHAL Configuration                                                                             */
/*                                                                                                                    */
/* !File            : IOHAL_Cfg_i_h.tpl                                                                               */
/*                                                                                                                    */
/* !Scope           : Public                                                                                          */
/*                                                                                                                    */
/* !Target          : Genecode Tool                                                                                   */
/*                                                                                                                    */       
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : Genecode                                                                                        */
/*                                                                                                                    */
/* COPYRIGHT 2015 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
**********************************************************************************************************************/
'/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer          : BSW                                                                                              */
/*                                                                                                                    */
/* !Component      : HAL                                                                                              */
/*                                                                                                                    */
/* !Module         : IOHAL                                                                                            */
/* !Description    : Configuration of the IOHAL component.                                                            */
/*                                                                                                                    */
/* !File           : IOHAL_Cfg_I.h                                                                                    */
/*                                                                                                                    */
/* !Target         : All                                                                                              */
/*                                                                                                                    */
/* !Vendor         : Valeo                                                                                            */
/*                                                                                                                    */
/* Coding language : C                                                                                                */
/*                                                                                                                    */
/* COPYRIGHT 2015 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* PVCS Information                                                                                                   */
/* $Arc`'hive::                                                                                                      $*/
/* $Rev`'ision::            $$Au`'thor::                  $$D`'ate::                                                 $*/
/**********************************************************************************************************************/
/** `Date()': generated by Genecode `Version()'                                                                       */
/**********************************************************************************************************************/

#ifndef IOHAL_CFG_I_H
#define IOHAL_CFG_I_H

#include "Std_Types.h"

/**********************************************************************************************************************/
/* VARIABLE DECLARATION                                                                                               */
/**********************************************************************************************************************/

#define IOHAL_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

`
IOHAL_CHANNEL AS ChannelName WHERE (DISPLAY = ON ) ORDERBY(INDEX) CONCATE
{
   WHERE(LINKTO{MCAL_READ_FUNCTION_NAME} != "")
   {
      "extern " LINKTO{RETURN_TYP.TYPE_NAME} " IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarRead_" ChannelName ";
"
   }
   WHERE((DIRECTION = OUTPUT) and (LINKTO{MCAL_WRITE_FUNCTION_NAME} != ""))
   {
      "extern " LINKTO{RETURN_TYP.TYPE_NAME} " IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarWrite_" ChannelName ";
"
   }
}
'
#define IOHAL_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define IOHAL_START_SEC_CODE
#include "MemMap.h"

extern void IOHAL_vidCfgInit(void);

#define IOHAL_STOP_SEC_CODE
#include "MemMap.h"


#endif  /* IOHAL_CFG_I_H */

/*--------------------------------------------------- end of file ----------------------------------------------------*/

