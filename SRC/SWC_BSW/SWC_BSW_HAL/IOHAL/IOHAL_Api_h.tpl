/*INSERTION_TRADOIL*/
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer           : BSW                                                                                             */
/*                                                                                                                    */
/* !Component       : HAL                                                                                             */
/* !Description     : IOHAL Configuration                                                                             */
/*                                                                                                                    */
/* !File            : IOHAL_Api_h.tpl                                                                                 */
/*                                                                                                                    */
/* !Scope           : Public                                                                                          */
/*                                                                                                                    */
/* !Target          : Genecode Tool                                                                                   */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : Genecode                                                                                        */
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
**********************************************************************************************************************/
'/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer          : BSW                                                                                              */
/*                                                                                                                    */
/* !Component      : HAL                                                                                              */
/*                                                                                                                    */
/* !Module         : IOHAL                                                                                            */
/* !Description    : Declaration of the API functions of the IOHAL component                                          */          
/*                                                                                                                    */
/* !File           : IOHAL_Api.h                                                                                      */
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
/* PVCS Information                                                                                                   */
/* $Archive::   P:/AG1_Gearbox/LOG/10_TCU/60_ComponentArchive/Archives/COMP_B                                        $*/
/* $Revision::   1.1      $$Author::   bmolis         $$Date::   16 Oct 2009                                         $*/
/**********************************************************************************************************************/

#ifndef IOHAL_API_H
#define IOHAL_API_H

#include "Std_Types.h"

/**********************************************************************************************************************/
/* MACRO FUNCTIONS DECLARATION                                                                                        */
/**********************************************************************************************************************/
#define IOHAL_vidWrite(snChannel, udtValue)     \
   IOHAL_vidWriteUdt_##snChannel(udtValue)

#define IOHAL_udtRead(snChannel)                \
   IOHAL_udtRead_##snChannel()

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
/**********************************************************************************************************************/
/* Abstraction layer for all IOHAL channels                                                                           */
/**********************************************************************************************************************/
`
IOHAL_CHANNEL AS ChannelName WHERE ((DIRECTION = INPUT) and (LINKTO{MCAL_READ_FUNCTION_NAME} != "")) ONEPERLINE
{
   "#define IOHAL_udtRead_" ChannelName "() IOHAL_" SIGNAL_TYPE_ABBR "Read_" ChannelName "()"
}


IOHAL_CHANNEL AS ChannelName WHERE ((DIRECTION = OUTPUT) and (LINKTO{MCAL_WRITE_FUNCTION_NAME} != "")) ONEPERLINE
{
   "#define IOHAL_vidWriteUdt_" ChannelName "(udtValue) IOHAL_vidWrite_" ChannelName "(udtValue);"
}

IOHAL_CHANNEL AS ChannelName WHERE ((DIRECTION = OUTPUT) and (LINKTO{MCAL_READ_FUNCTION_NAME} != "")) ONEPERLINE
{
   "#define IOHAL_udtRead_" ChannelName "() IOHAL_"  SIGNAL_TYPE_ABBR "Read_" ChannelName "()"
}
'

/**********************************************************************************************************************/
/* FUNCTIONS DECLARATION                                                                                              */
/**********************************************************************************************************************/
#define IOHAL_START_SEC_CODE
#include "MemMap.h"

extern void IOHAL_vidInit(void);

/**********************************************************************************************************************/
/* Supported Read and Write functions for different HAL channels                                                      */
/**********************************************************************************************************************/
`
IOHAL_CHANNEL AS ChannelName WHERE ((DIRECTION = INPUT) and (LINKTO{MCAL_READ_FUNCTION_NAME} != "")) ONEPERLINE
{
   "extern " SIGNAL_TYPE_NAME " IOHAL_" SIGNAL_TYPE_ABBR "Read_" ChannelName "(void);"
}


IOHAL_CHANNEL AS ChannelName WHERE ((DIRECTION = OUTPUT) and (LINKTO{MCAL_WRITE_FUNCTION_NAME} != "")) ONEPERLINE
{
   "extern void IOHAL_vidWrite_" ChannelName "(" SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "Value);"
}

IOHAL_CHANNEL AS ChannelName WHERE ((DIRECTION = OUTPUT) and (LINKTO{MCAL_READ_FUNCTION_NAME} != "")) ONEPERLINE
{
   "extern " SIGNAL_TYPE_NAME " IOHAL_" SIGNAL_TYPE_ABBR "Read_" ChannelName "(void);"
}
'
#define IOHAL_STOP_SEC_CODE
#include "MemMap.h"


#endif /* IOHAL_API_H */

/*-------------------------------- end of file -----------------------------------------------------------------------*/
