/******************************************************************************/
/*                                                                            */
/* !Layer           : Application                                             */
/*                                                                            */
/* !Module          : STD                                                     */
/* !Description     : Types                                                   */
/*                                                                            */
/* !File            : Type.h                                                  */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2014 VALEO                                                       */
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

#ifndef _TYPE_H_
#define _TYPE_H_

#include "Std_Types.h"

typedef boolean   bit;
typedef boolean   bool;

/* Old type declaration */
typedef uint8     ub;
typedef sint8     sb;
typedef uint16    uw;
typedef sint16    sw;
typedef uint32    u4;
typedef sint32    s4;

/* New type declaration */
typedef uint8     u8;
typedef sint8     s8;
typedef uint16    u16;
typedef sint16    s16;
typedef uint32    u32;
typedef sint32    s32;

#define fixe

#endif /* _TYPE_H_ */

/*-------------------------------- end of file -------------------------------*/
