/******************************************************************************/
/*                                                                            */
/* !Layer          : MCAL                                                     */
/*                                                                            */
/* !Component      : MAIN                                                     */
/*                                                                            */
/* !Module         : MAIN_DRV                                                 */
/* !Description    : Abstraction of register file declaration name            */
/*                                                                            */
/* !File           : MICRO.H                                                  */
/*                                                                            */
/* !Scope          : Private                                                  */
/*                                                                            */
/* !Target         : Infineon TC264D                                          */
/*                                                                            */
/* !Vendor         : Valeo                                                    */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2010 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::             $$Author::   ogarot        $$Date::               $*/
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#ifndef MICRO_H
#define MICRO_H

#include "Ifx_reg.h"

#define IFX_P_OMR_PCL0_OFF (16)

/* TriBoard-TC26xx : P33.6 ... P33.13 --> LED D501 ... D508 */

#define MAX_LED               8  /* number of available LEDs */
#define LED_PIN_NR            6  /* pin number of first used LED */
#define MASK_ALL_LEDS         ((1 << MAX_LED) - 1)

/* OMR is WO ==> don't use load-modify-store access! */
/* set PSx pin */
#define LED_PIN_SET(x)        (1 << (LED_PIN_NR + (x)))
/* set PCLx pin */
#define LED_PIN_RESET(x)      (1 << (LED_PIN_NR + IFX_P_OMR_PCL0_OFF + (x)))
#define LED_ON(x)          (portLED->OMR.U = LED_PIN_RESET(x))
#define LED_OFF(x)            (portLED->OMR.U = LED_PIN_SET(x))
/* set PCLx and PSx pin to 1 ==> toggle pin state */
#define LED_TOGGLE(x)         (portLED->OMR.U = LED_PIN_RESET(x) | LED_PIN_SET(x))
#define INIT_LEDS          {\
   /* initialise all LEDs (P33.6 .. P33.13) */\
   portLED->IOCR4.B.PC6 = 0x10;  /* OUT_PPGPIO */\
   portLED->IOCR4.B.PC7 = 0x10;  /* OUT_PPGPIO */\
   portLED->IOCR8.U = 0x80808080;   /* OUT_PPGPIO */\
   portLED->IOCR12.B.PC12 = 0x10;   /* OUT_PPGPIO */\
   portLED->IOCR12.B.PC13 = 0x10;   /* OUT_PPGPIO */\
   /* all LEDs OFF */\
   portLED->OMR.U = (MASK_ALL_LEDS << LED_PIN_NR);\
}

extern Ifx_P * const portLED;

#endif  /* MICRO_H */

/*-------------------------------- end of file -------------------------------*/
