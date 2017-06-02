/**********************************************************************************************************************/
/* !Layer           : MCAL                                                                                            */
/*                                                                                                                    */
/* !Component       : VADC                                                                                            */
/* !Description     : Versatile Analog to Digital Converter Driver                                                    */
/*                                                                                                                    */
/* !Module          : VADC_Target                                                                                     */
/* !Description     : Versatile Analog to Digital Converter Driver private declarations/definitions (target specific) */
/*                                                                                                                    */
/* !File            : VADC_Target.h                                                                                   */
/*                                                                                                                    */
/* !Target          : AURIX TC27x                                                                                     */
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

#ifndef VADC_TARGET_H
#define VADC_TARGET_H

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
#define VADC_u8GROUP_NB_MAX         2
#define VADC_u32CHANNELS_NB_MAX     12

/* Channels definition for module interfaces */
#define VADC_snAN00_CH AN0_00
#define VADC_snAN01_CH AN0_01
#define VADC_snAN02_CH AN0_02
#define VADC_snAN03_CH AN0_03
#define VADC_snAN04_CH AN0_04
#define VADC_snAN05_CH AN0_05
#define VADC_snAN06_CH AN0_06
#define VADC_snAN07_CH AN0_07
#define VADC_snAN08_CH AN0_08
#define VADC_snAN09_CH AN0_09
#define VADC_snAN10_CH AN0_10
#define VADC_snAN11_CH AN0_11
#define VADC_snAN12_CH AN1_00
#define VADC_snAN13_CH AN1_01
#define VADC_snAN14_CH AN1_02
#define VADC_snAN15_CH AN1_03
#define VADC_snAN16_CH AN1_04
#define VADC_snAN17_CH AN1_05
#define VADC_snAN18_CH AN1_06
#define VADC_snAN19_CH AN1_07
#define VADC_snAN20_CH AN1_08
#define VADC_snAN21_CH AN1_09
#define VADC_snAN22_CH AN1_10
#define VADC_snAN23_CH AN1_11


#define VADC_u8AN0_00_IDX ((0 << 4) | 0)
#define VADC_u8AN0_01_IDX ((0 << 4) | 1)
#define VADC_u8AN0_02_IDX ((0 << 4) | 2)
#define VADC_u8AN0_03_IDX ((0 << 4) | 3)
#define VADC_u8AN0_04_IDX ((0 << 4) | 4)
#define VADC_u8AN0_05_IDX ((0 << 4) | 5)
#define VADC_u8AN0_06_IDX ((0 << 4) | 6)
#define VADC_u8AN0_07_IDX ((0 << 4) | 7)
#define VADC_u8AN0_08_IDX ((0 << 4) | 8)
#define VADC_u8AN0_09_IDX ((0 << 4) | 9)
#define VADC_u8AN0_10_IDX ((0 << 4) | 10)
#define VADC_u8AN0_11_IDX ((0 << 4) | 11)

#define VADC_u8AN1_00_IDX ((1 << 4) | 0)
#define VADC_u8AN1_01_IDX ((1 << 4) | 1)
#define VADC_u8AN1_02_IDX ((1 << 4) | 2)
#define VADC_u8AN1_03_IDX ((1 << 4) | 3)
#define VADC_u8AN1_04_IDX ((1 << 4) | 4)
#define VADC_u8AN1_05_IDX ((1 << 4) | 5)
#define VADC_u8AN1_06_IDX ((1 << 4) | 6)
#define VADC_u8AN1_07_IDX ((1 << 4) | 7)
#define VADC_u8AN1_08_IDX ((1 << 4) | 8)
#define VADC_u8AN1_09_IDX ((1 << 4) | 9)
#define VADC_u8AN1_10_IDX ((1 << 4) | 10)
#define VADC_u8AN1_11_IDX ((1 << 4) | 11)

/* Definition of channels index per ADC */
#define VADC_u8AN00_IDX (0)
#define VADC_u8AN01_IDX (1)
#define VADC_u8AN02_IDX (2)
#define VADC_u8AN03_IDX (3)
#define VADC_u8AN04_IDX (4)
#define VADC_u8AN05_IDX (5)
#define VADC_u8AN06_IDX (6)
#define VADC_u8AN07_IDX (7)
#define VADC_u8AN08_IDX (8)
#define VADC_u8AN09_IDX (9)
#define VADC_u8AN10_IDX (10)
#define VADC_u8AN11_IDX (11)

#define VADC_u8AN12_IDX (16)
#define VADC_u8AN13_IDX (17)
#define VADC_u8AN14_IDX (18)
#define VADC_u8AN15_IDX (19)
#define VADC_u8AN16_IDX (20)
#define VADC_u8AN17_IDX (21)
#define VADC_u8AN18_IDX (22)
#define VADC_u8AN19_IDX (23)
#define VADC_u8AN20_IDX (24)
#define VADC_u8AN21_IDX (25)
#define VADC_u8AN22_IDX (26)
#define VADC_u8AN23_IDX (27)

#define VADC_u16AN00_MSK (1u << (VADC_u8AN00_IDX & 15u))
#define VADC_u16AN01_MSK (1u << (VADC_u8AN01_IDX & 15u))
#define VADC_u16AN02_MSK (1u << (VADC_u8AN02_IDX & 15u))
#define VADC_u16AN03_MSK (1u << (VADC_u8AN03_IDX & 15u))
#define VADC_u16AN04_MSK (1u << (VADC_u8AN04_IDX & 15u))
#define VADC_u16AN05_MSK (1u << (VADC_u8AN05_IDX & 15u))
#define VADC_u16AN06_MSK (1u << (VADC_u8AN06_IDX & 15u))
#define VADC_u16AN07_MSK (1u << (VADC_u8AN07_IDX & 15u))
#define VADC_u16AN08_MSK (1u << (VADC_u8AN08_IDX & 15u))
#define VADC_u16AN09_MSK (1u << (VADC_u8AN09_IDX & 15u))
#define VADC_u16AN10_MSK (1u << (VADC_u8AN10_IDX & 15u))
#define VADC_u16AN11_MSK (1u << (VADC_u8AN11_IDX & 15u))
#define VADC_u16AN12_MSK (1u << (VADC_u8AN12_IDX & 15u))
#define VADC_u16AN13_MSK (1u << (VADC_u8AN13_IDX & 15u))
#define VADC_u16AN14_MSK (1u << (VADC_u8AN14_IDX & 15u))
#define VADC_u16AN15_MSK (1u << (VADC_u8AN15_IDX & 15u))
#define VADC_u16AN16_MSK (1u << (VADC_u8AN16_IDX & 15u))
#define VADC_u16AN17_MSK (1u << (VADC_u8AN17_IDX & 15u))
#define VADC_u16AN18_MSK (1u << (VADC_u8AN18_IDX & 15u))
#define VADC_u16AN19_MSK (1u << (VADC_u8AN19_IDX & 15u))
#define VADC_u16AN20_MSK (1u << (VADC_u8AN20_IDX & 15u))
#define VADC_u16AN21_MSK (1u << (VADC_u8AN21_IDX & 15u))
#define VADC_u16AN22_MSK (1u << (VADC_u8AN22_IDX & 15u))
#define VADC_u16AN23_MSK (1u << (VADC_u8AN23_IDX & 15u))

#endif /* VADC_TARGET_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
