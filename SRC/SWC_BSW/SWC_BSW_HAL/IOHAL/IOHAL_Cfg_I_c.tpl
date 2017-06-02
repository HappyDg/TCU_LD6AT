/*INSERTION_TRADOIL*/
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Layer           : BSW                                                                                             */
/*                                                                                                                    */
/* !Component       : HAL                                                                                             */
/* !Description     : IOHAL Configuration                                                                             */
/*                                                                                                                    */
/* !File            : IOHAL_Cfg_I_c.tpl                                                                               */
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
/* !Description    : Configuration of the IOHAL component.                                                            */
/*                                                                                                                    */
/* !File           : IOHAL_Cfg_I.c                                                                                    */
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

#include "IOHAL_Api.h"
#include "IOHAL_Cfg.h"
#include "IOHAL_Cfg_I.h"

#define IOHAL_udtSCALE(input, factor, shift, offset)  (shift>0?(((sint32)input * factor) << shift) + (sint32)offset:(((sint32)input * factor) >> -shift) + (sint32)offset)
#define IOHAL_udtMIN(a, b) ( ( (a) > (b) ) ? (b) : (a) )
#define IOHAL_udtMAX(a, b) ( ( (a) > (b) ) ? (a) : (b) )
#define IOHAL_udtCLAMP(a, b, c) ( ( (a) < (b) ) ? (b) : ( ( (a) > (c) ) ? (c) : (a) ) )

`
IOHAL_CFG_RW AS cfg_rw WHERE ((.IOHAL_CHANNEL WHERE (LINKTO == cfg_rw) COUNT ) > 0 )
{
   "#include "'"` READ_FUNC_HEADER_FILE_DECLARATION '"`
}
'

/**********************************************************************************************************************/
/* VARIABLE DECLARATION                                                                                               */
/**********************************************************************************************************************/

#define IOHAL_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

`
IOHAL_CHANNEL AS ChannelName WHERE (DISPLAY= ON)  ORDERBY(INDEX) CONCATE
{
   WHERE(LINKTO{MCAL_READ_FUNCTION_NAME} != "")
   {
   "" LINKTO{RETURN_TYP.TYPE_NAME} " IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarRead_" ChannelName ";
"
   }
   WHERE((DIRECTION = OUTPUT) and (LINKTO{MCAL_WRITE_FUNCTION_NAME} != ""))
   {
   "" LINKTO{RETURN_TYP.TYPE_NAME} " IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarWrite_" ChannelName ";
"
   }
}
'
#define IOHAL_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define IOHAL_START_SEC_CODE
#include "MemMap.h"

void IOHAL_vidCfgInit(void)
{

`
IOHAL_CHANNEL AS ChannelName WHERE (DISPLAY= ON)  ORDERBY(INDEX) CONCATE
{
   WHERE(LINKTO{MCAL_READ_FUNCTION_NAME} != "")
   {
   "   IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarRead_" ChannelName " = 0;
"
   }
   WHERE((DIRECTION = OUTPUT) and (LINKTO{MCAL_WRITE_FUNCTION_NAME} != ""))
   {
   "   IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarWrite_" ChannelName " = 0;
"
   }
}
'
}


/**********************************************************************************************************************/
/* LOCAL FUNCTION DEFINITION                                                                                          */
/**********************************************************************************************************************/

`
IOHAL_CHANNEL AS ChannelName WHERE (((DIRECTION = INPUT) and (LINKTO{MCAL_READ_FUNCTION_NAME} != ""))or((DIRECTION = OUTPUT) and (LINKTO{MCAL_READ_FUNCTION_NAME} != ""))) ONEPERLINE
{
"
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Description: Read from the " LINKTO " channel (" ChannelName ")                                                   */
/*                                                                                                                    */
/**********************************************************************************************************************/
" SIGNAL_TYPE_NAME " IOHAL_" SIGNAL_TYPE_ABBR "Read_" ChannelName "(void)
{
"
   "   " LINKTO{RETURN_TYP.TYPE_NAME} " " LINKTO{PARAM_TYP.TYPE_ABBR} "LocalValue = (" LINKTO{RETURN_TYP.TYPE_NAME} ")" LINKTO{MCAL_READ_FUNCTION_NAME} "(" MCAL_CHANNEL_NAME "" LINKTO{MCAL_READ_ADDITIONAL_PARAMETERS}");
"
   WHERE(LINKTO = ADC)
   {
      "   " LINKTO{PARAM_TYP.TYPE_ABBR} "LocalValue = " LINKTO{PARAM_TYP.TYPE_ABBR} "LocalValue >> 0;
"
   }
   WHERE(DISPLAY = ON)
   {
      "   IOHAL_" LINKTO{RETURN_TYP.TYPE_ABBR} "VarRead_" ChannelName " = " LINKTO{PARAM_TYP.TYPE_ABBR} "LocalValue;
"
   }
   WHERE(HAL_SCALING == "OFF")
   {
      "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalScale = (" SIGNAL_TYPE_NAME ")" LINKTO{PARAM_TYP.TYPE_ABBR} "LocalValue;
"
   }
   WHERE((HAL_SCALING == "ON") and (HAL_SCALING.READ_FUNCTION == "IOHAL_udtSCALE" ))
   {
      "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalScale = (" SIGNAL_TYPE_NAME ")IOHAL_udtSCALE(" LINKTO{PARAM_TYP.TYPE_ABBR} "LocalValue," HAL_SCALING.READ_FACTOR "," HAL_SCALING.READ_SHIFT "," HAL_SCALING.READ_OFFSET ");
"
   }
   WHERE((HAL_SCALING == "ON") and (HAL_SCALING.READ_FUNCTION != "IOHAL_udtSCALE" ))
   {
      "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalScale = (" SIGNAL_TYPE_NAME ")" HAL_SCALING.READ_FUNCTION "(" LINKTO{PARAM_TYP.TYPE_ABBR} "LocalValue);
"
   }
   WHERE((HAL_CLAMPING == "OFF") or ((HAL_CLAMPING.MIN_VALUE == "") and (HAL_CLAMPING.MAX_VALUE == "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalOutput = (" SIGNAL_TYPE_NAME ")" SIGNAL_TYPE_ABBR "LocalScale;
"
   }
   WHERE((HAL_CLAMPING == "ON") and ((HAL_CLAMPING.MIN_VALUE != "") and (HAL_CLAMPING.MAX_VALUE == "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalOutput = IOHAL_udtMAX(" SIGNAL_TYPE_ABBR "LocalScale," HAL_CLAMPING.MIN_VALUE ");
"
   }
   WHERE((HAL_CLAMPING == "ON") and ((HAL_CLAMPING.MIN_VALUE == "") and (HAL_CLAMPING.MAX_VALUE != "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalOutput = IOHAL_udtMIN(" SIGNAL_TYPE_ABBR "LocalScale," HAL_CLAMPING.MAX_VALUE ");
"
   }
   WHERE((HAL_CLAMPING == "ON") and ((HAL_CLAMPING.MIN_VALUE != "") and (HAL_CLAMPING.MAX_VALUE != "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalOutput = IOHAL_udtCLAMP(" SIGNAL_TYPE_ABBR "LocalScale," HAL_CLAMPING.MIN_VALUE "," HAL_CLAMPING.MAX_VALUE ");
"
   }
"   return " SIGNAL_TYPE_ABBR "LocalOutput;
}"
}

IOHAL_CHANNEL AS ChannelName WHERE ((DIRECTION = OUTPUT) and (LINKTO{MCAL_WRITE_FUNCTION_NAME} != "")) ONEPERLINE
{
"
/**********************************************************************************************************************/
/*                                                                                                                    */
/* !Description: Write to the " LINKTO " pin (" ChannelName ")                                                        */
/*                                                                                                                    */
/**********************************************************************************************************************/
""void IOHAL_vidWrite_" ChannelName "(" SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "Value)
{
"   
   WHERE((HAL_CLAMPING == "OFF") or ((HAL_CLAMPING.MIN_VALUE == "") and (HAL_CLAMPING.MAX_VALUE == "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalInput = (" SIGNAL_TYPE_NAME ")" SIGNAL_TYPE_ABBR "Value;
"
   }
   WHERE((HAL_CLAMPING == "ON") and ((HAL_CLAMPING.MIN_VALUE != "") and (HAL_CLAMPING.MAX_VALUE == "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalInput = IOHAL_udtMAX(" SIGNAL_TYPE_ABBR "Value," HAL_CLAMPING.MIN_VALUE ");
"
   }
   WHERE((HAL_CLAMPING == "ON") and ((HAL_CLAMPING.MIN_VALUE == "") and (HAL_CLAMPING.MAX_VALUE != "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalInput = IOHAL_udtMIN(" SIGNAL_TYPE_ABBR "Value," HAL_CLAMPING.MAX_VALUE ");
"
   }
   WHERE((HAL_CLAMPING == "ON") and ((HAL_CLAMPING.MIN_VALUE != "") and (HAL_CLAMPING.MAX_VALUE != "")))
   {
   "   " SIGNAL_TYPE_NAME " " SIGNAL_TYPE_ABBR "LocalInput = IOHAL_udtCLAMP(" SIGNAL_TYPE_ABBR "Value," HAL_CLAMPING.MIN_VALUE "," HAL_CLAMPING.MAX_VALUE ");
"
   }
   WHERE(HAL_SCALING == "OFF")
   {
      "   " LINKTO{RETURN_TYP.TYPE_NAME} " " LINKTO{PARAM_TYP.TYPE_ABBR}"LocalScale = (" LINKTO{RETURN_TYP.TYPE_NAME} ")" SIGNAL_TYPE_ABBR "LocalInput;
"
   }
   WHERE((HAL_SCALING == "ON") and (HAL_SCALING.WRITE_FUNCTION == "IOHAL_udtSCALE" ))
   {
      "   " LINKTO{RETURN_TYP.TYPE_NAME} " " LINKTO{PARAM_TYP.TYPE_ABBR}"LocalScale = (" LINKTO{RETURN_TYP.TYPE_NAME} ")IOHAL_udtSCALE(" SIGNAL_TYPE_ABBR "LocalInput," HAL_SCALING.WRITE_FACTOR ","  HAL_SCALING.WRITE_SHIFT "," HAL_SCALING.WRITE_OFFSET ");
"
   }
   WHERE((HAL_SCALING == "ON") and (HAL_SCALING.WRITE_FUNCTION != "IOHAL_udtSCALE" ))
   {
      "   " LINKTO{RETURN_TYP.TYPE_NAME} " " LINKTO{PARAM_TYP.TYPE_ABBR}"LocalScale = (" LINKTO{RETURN_TYP.TYPE_NAME} ")" HAL_SCALING.WRITE_FUNCTION "(" SIGNAL_TYPE_ABBR "LocalInput);
"
   }

   "   " LINKTO{MCAL_WRITE_FUNCTION_NAME} "(" MCAL_CHANNEL_NAME "," LINKTO{PARAM_TYP.TYPE_ABBR} "LocalScale" LINKTO{MCAL_WRITE_ADDITIONAL_PARAMETERS} ");
"

   WHERE(DISPLAY = ON)
   {
      "   IOHAL_" LINKTO{PARAM_TYP.TYPE_ABBR} "VarWrite_" ChannelName " = " LINKTO{PARAM_TYP.TYPE_ABBR} "LocalScale;
"
   }
"}"
}

'

#define IOHAL_STOP_SEC_CODE
#include "MemMap.h"

/*--------------------------------------------------- end of file ----------------------------------------------------*/

