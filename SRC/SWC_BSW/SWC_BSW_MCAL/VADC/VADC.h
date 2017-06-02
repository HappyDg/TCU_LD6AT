/**********************************************************************************************************************/
/* !Layer           : MCAL                                                                                            */
/*                                                                                                                    */
/* !Component       : VADC                                                                                            */
/* !Description     : Versatile Analog to Digital Converter Driver                                                    */
/*                                                                                                                    */
/* !Module          : VADC                                                                                            */
/* !Description     : Versatile Analog to Digital Converter Driver interfaces                                         */
/*                                                                                                                    */
/* !File            : VADC.h                                                                                          */
/*                                                                                                                    */
/* !Target          : AURIX TC2x                                                                                      */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/

#ifndef VADC_H
#define VADC_H

#include "IfxVadc_reg.h"
#include "VADC_Cfg.h"
#include "VADC_L.h"

/**********************************************************************************************************************/
/* MACRO FUNCTIONS DEFINITION                                                                                         */
/**********************************************************************************************************************/
#define VADC_u16GET_VALUE(snChannel) \
   VADC_u16GET_VALUE_M1(snChannel)

   #define VADC_u16GET_VALUE_M1(snChannel) \
      VADC_u16GET_VALUE_M2(VADC_sn##snChannel##_CH)

   #define VADC_u16GET_VALUE_M2(snChannel) \
      VADC_u16GET_VALUE_M3(snChannel)

   #define VADC_u16GET_VALUE_M3(snChannel) \
      VADC_u16GET_VALUE_M4(VADC_sn##snChannel##_CH)

   #define VADC_u16GET_VALUE_M4(snChannel) \
      VADC_u16GET_VALUE_M5(snChannel)

   #define VADC_u16GET_VALUE_M5(snChannel) \
      VADC_u16GET_VALUE_M6(VADC_u8##snChannel##_IDX)

   #define VADC_u16GET_VALUE_M6(u8Channel) \
      (MODULE_VADC.G[(u8Channel) >> 4].RES[(u8Channel) & 0x0F].B.RESULT)
	  
	  
/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description : Checks if the specified timeout is elapsed                                                          */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/
/* !Comment: Wait for the specified time (in us) */
#define VADC_u16READ_VALUE(snChannel)  \
   M1_VADC_u16READ_VALUE(VADC_u8##snChannel##_RES_IDX)
   
 #define M1_VADC_u16READ_VALUE(snChannel)  \
   M2_VADC_u16READ_VALUE(snChannel)

   #define M2_VADC_u16READ_VALUE(u8Channel)  \
   M3_VADC_u16READ_VALUE(u8Channel)

    #define M3_VADC_u16READ_VALUE(u8Channel) (VADC_au16ConvRes[u8Channel])

/**********************************************************************************************************************/
/* FUNCTIONS DECLARATION                                                                                              */
/**********************************************************************************************************************/
#define VADC_START_SEC_CODE
#include "VADC_MemMap.h"

void VADC_vidInit(void);
void VADC_vidEna(void);

#define VADC_STOP_SEC_CODE
#include "VADC_MemMap.h"

#endif /* VADC_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
