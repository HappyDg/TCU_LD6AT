/**
*   @file    RbBaseSw.h
*   @version 1.0.0
*
*   @brief   Rb Base Software interface header file.
*   @details This file is the header containing all the necessary information 
     for Rb Base Software.
*/
/*==================================================================================================
*   Project              : Shengrui TCU
*   Peripheral           : External Eeprom
*   Hardware Type        : BR93H66-W
*
*   SW Version           : 1.0.0
*
*   (c) Copyright 2017 Valeo
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef RB_BASE_SW_H
#define RB_BASE_SW_H

#define	MIN_READ_BYTE	1
#define	MAX_READ_BYTE	40
#define	MIN_READ_ADDR	0
#define	MAX_READ_ADDR	255

extern void ShrExp_SubRom_Init(void);


extern void ShrExp_Get_SbrmIntBuffer(unsigned char * status, unsigned short * dat_p, unsigned long numDat);

extern void ShrExp_Read_SbrmData(unsigned char * status, unsigned long adStart, unsigned long numDat);

extern void ShrExp_Get_SbrmStatus(unsigned char * status);

extern void ShrExp_Clear_SbrmStatus(void);

#endif
