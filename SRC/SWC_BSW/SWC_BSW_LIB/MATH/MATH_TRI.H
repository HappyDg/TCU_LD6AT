/******************************************************************************/
/*                                                                            */
/* !Layer          : SERVICES                                                 */
/*                                                                            */
/* !Component      : MATH                                                     */
/*                                                                            */
/* !Module         : MATH_TRI                                                 */
/* !Description    : Mathematical functions : Trigonometry                    */
/*                                                                            */
/* !File           : MATH_TRI.H                                               */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : All                                                      */
/*                                                                            */
/* !Vendor         : Valeo                                                    */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2006 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   P:/VE_Onduleur_Gen2_Sofraci/LOG/60_ComponentArchive/Archives/COMP_SWC_BSWSH72/MATH_TRI.H_v  $  */
/* $Revision::   1.2      $$Author::   ogarot         $$Date::   20 Feb 2013 $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/

#ifndef MATH_TRI_H
#define MATH_TRI_H

#include "Std_Types.h"

#include "rtwtypes.h"

/******************************************************************************/
/* PROTOTYPES                                                                 */
/******************************************************************************/
#ifndef __RTWTYPES_H__
/*============================================================================*
 * Fixed width word size data types:                                          *
 *   int8_T, int16_T, int32_T     - signed 8, 16, or 32 bit integers          *
 *   uint8_T, uint16_T, uint32_T  - unsigned 8, 16, or 32 bit integers        *
 *   real32_T, real64_T           - 32 and 64 bit floating point numbers      *
 *============================================================================*/
typedef sint8     int8_T;
typedef uint8     uint8_T;
typedef sint16    int16_T;
typedef uint16    uint16_T;
typedef sint32    int32_T;
typedef uint32    uint32_T;
typedef float32   real32_T;
typedef float64   real64_T;
#endif

#define MATH_START_SEC_CODE
#include "MATH_MemMap.h"

extern sint16 MathSinus(uint16 angle);
extern sint16 MathCosinus(uint16 angle);
extern sint16 MathArcsinus(sint16 arc);
extern sint16 MathArccosinus(sint16 arc);
extern sint32 MathTangente(sint16 sinus,sint16 cosinus);
extern sint16 MathArctangente(sint32 tangente);
extern void MathSinusCosinus(uint16 angle, sint16 *sinResult, sint16 *cosResult);

extern void LIBTRIG_Sin_Outputs_wrapper(const int16_T  *Theta, int16_T  *Sin);
extern void LIBTRIG_Cos_Outputs_wrapper(const int16_T  *Theta, int16_T  *Cos);
extern void LIBTRIG_SinCos_Outputs_wrapper(const int16_T  *Theta, int16_T  *Sin, int16_T  *Cos);
extern void LIBTRIG_Arctan_Outputs_wrapper(const int32_T  *Tangente, int16_T  *Theta);

#define MATH_STOP_SEC_CODE
#include "MATH_MemMap.h"

/******************************************************************************/
/* TYPES DECLARATION                                                          */
/******************************************************************************/
typedef uint16 MathAngleType;

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
#define MATH_SINUS_SHIFT                  (uint16)8
#define MATH_SINUS_MODULO                 (uint16)0x00FF
#define MATH_SINUS_OF_PI_DIV_2            (uint16)32768

#define MATH_ARCSINUS_SHIFT               (uint16)8
#define MATH_ARCSINUS_MODULO              (uint16)0x00FF

#define MATH_PI                           (uint16)32767
#define MATH_PI_DIV_2                     (uint16)16383
#define MATH_2_PI                         (uint16)65535

#define MATH_TANGENTE_1                   (uint32)65536
#define MATH_TANGENTE_8                   (uint32)(65536*8)
#define MATH_TANGENTE_1024                (uint32)(65536*1024)

#define MATH_TANGENTE_MODULO              (uint16)0x00FF

#define MATH_TANGENTE_8_SHIFT_INDEX       (uint16)11
#define MATH_TANGENTE_8_SHIFT_RESTE       (uint16)3
#define MATH_TANGENTE_8_INDEX_OFFSET      (uint16)32

#define MATH_TANGENTE_1024_SHIFT_INDEX    (uint16)18
#define MATH_TANGENTE_1024_SHIFT_RESTE    (uint16)10
#define MATH_TANGENTE_1024_INDEX_OFFSET   (uint16)2

/******************************************************************************/
/* DATAS DECLARATION                                                          */
/******************************************************************************/

#define MATH_START_SEC_CONST_UNSPECIFIED
#include "MATH_MemMap.h"

extern const sint16 mathSinusTable[257];
extern const sint16 mathArcsinusTable[257];
extern const uint16 mathArctangenteTable1[257];
extern const uint16 mathArctangenteTable2[257];
extern const uint16 mathArctangenteTable3[257];

#define MATH_STOP_SEC_CONST_UNSPECIFIED
#include "MATH_MemMap.h"

#endif /* MATH_TRI_H */

/*-------------------------------- end of file -------------------------------*/
