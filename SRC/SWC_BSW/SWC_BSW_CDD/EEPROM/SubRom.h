/**
*   @file    SubRom.h
*   @version 1.0.0
*
*   @brief   SubRom driver header file.
*   @details This file is the header containing all the necessary information 
     for SubRom.
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

#ifndef SUBROM_H
#define SUBROM_H

#define	BLOCK_LENGTH	128
#define	DISABLE_SUBROM	0
#define ENABLE_SUBROM	1
#define POWERON	350
#define READ_TIME	350
#define WRITE_SWITCH_TIME	350
#define WRITE_TIME	350
#define WAITCS_TIME	500
#define WRITETIMEOUT 38000
#define HEADER	1

/* Eeprom Operation Mode */
typedef enum tagEepOpeMode
{
					/* Command       Ope code     Address                   Data                  */     
	READ = 2u,		/* Read          10           A7,A6,A5,A4,A3,A2,A1,A0   D15 to D0(READ DATA)  */
	WEN = 0u,		/* Write enable  00           1 1 * * * * * *                                 */
	WRITE = 1u,		/* Write         01           A7,A6,A5,A4,A3,A2,A1,A0   D15 to D0(WRITE DATA) */
	WRAL = 0u,		/* Write all     00           0 1 * * * * * B0          D15 to D0(WRITE DATA) */
	WDS = 0u		/* Write disable 00           0 0 * * * * * *                                 */
}EepOpeMode;

/* Eeprom Operation Status */
typedef enum tagEepOpeStatus
{
	IDLE = 0x00,
	DONE = 0x01,
	BUSY = 0x0f,
	ACCEPTED = 0x10,
	VALID = 0x11,
	FAULT = 0x1f,
	TOOLONG = 0xf0,
	TOOSHORT = 0xf1,
	INVALID = 0xff
}EepOpeStatus;

extern EepOpeStatus OpeStatus;

void delay_us(unsigned int us);

void SubRom_Init(void);

void Set_CS(void);

void Clr_CS(void);

void Set_SCK(void);

void Clr_SCK(void);

void Set_MOSI(void);

void Clr_MOSI(void);

unsigned char Read_MISO(void);

void SpiWriteSwith(unsigned char enable);

unsigned short SpiReadOneData(unsigned long addr);

void SpiWriteOneData(unsigned long addr, unsigned short WrData);

void SpiBurstRead(unsigned long addr, unsigned short *ptr, unsigned long length);

void SpiBurstWrite(unsigned long addr, unsigned short *ptr, unsigned long length);

void SpiWriteAll(unsigned char blockID, unsigned short *ptr);

void SpiWaitWriteFinish(void);

unsigned char SpiGetOpeStatus(void);

#endif
