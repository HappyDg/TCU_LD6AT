/**
*   @file    RbBaseSw.h
*   @version 1.0.0
*
*   @brief   Rb Base Software interface.
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
#ifdef __cplusplus
extern "C"
{
#endif

#include <string.h>
#include "RbBaseSw.h"
#include "SubRom.h"
#include "Gpio_Spi.h"

unsigned short g_ucIntRamArray[50] = {};

/*================================================================================================*/
/**
* @brief   This function provides the access to the internal RAM buffer provided for the SubRom
		   module.
* @details The internal RAM buffer is initialized at power on with 0xFF and is only updated by 
*		   request of customer SW by calling the interface ShrExp_Read_SurmData()(copy data from
*		   SubRom to internal buffer). The main purpose of this internal RAM buffer is to provide
*		   asynchronous access to the SubRom data. The customer software is responsible to check
*		   the status of the SubRom by calling the interface ShrExp_Get_SbrmStatus() before calling
*		   the ShrExp_Get_SbrmIntbuffer() for reading the buffer content to ensure that the 
*		   previousread request is finished.
*
* @param[in]      status		the status of the request

								BUSY = 0x0f
								VALID = 0x11
								TOOLONG = 0xf0
								TOOSHORT = 0xf1
								INVALID = 0xff
								
                  dat_p			pointer to data
				  numDat		number of SubRom data elements
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void ShrExp_SubRom_Init(void)
{
	g_ucIntRamArray[0] = 0;
}

void ShrExp_Get_SbrmIntBuffer(unsigned char *status, unsigned short *dat_p, unsigned long numDat)
{
	if(*status == BUSY )
	{
		return;
	}
	else
	{
		
	}
	
	if(numDat > MAX_READ_BYTE)
	{
		*status = TOOLONG;
	}
	else if(numDat < MIN_READ_BYTE)
	{
		*status = TOOSHORT;
	}
	else
	{
		*status = VALID;
	}
	
	if(*status == VALID)
	{
		memcpy(dat_p, g_ucIntRamArray, numDat*sizeof(unsigned short));
		memset(g_ucIntRamArray, 0, sizeof(g_ucIntRamArray));
		*status = IDLE;
	}
	else
	{
	
	}
}

/*================================================================================================*/
/**
* @brief   This function is called in order to trigger the SubRom communication itself.
* @details The customer software is responsible for providing suitable start address and number of 
           data elements. If the request was accepted, the function will start an internal 
		   state machine, which will handle the request. The status of the state machine can be 
		   checked by calling the interface ShrExp_Get_SurmStatus(). After the request is issued 
		   and the status of the state machine is done the request was executed succeffully.
*
* @param[in]      status		the current operation status
*				  adStart		the start address of the data to be read
*				  numDat		the number of the data to be read
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void ShrExp_Read_SbrmData(unsigned char * status, unsigned long adStart, unsigned long numDat)
{
	if(*status == BUSY )
	{
		return;
	}
	else
	{
		
	}
	
	if(numDat > MAX_READ_BYTE)
	{
		*status = TOOLONG;	/* length too long */
	}
	else if(numDat < MIN_READ_BYTE)
	{
		*status = TOOSHORT;	/* length too short */
	}
	else
	{
		
	}
	
	if(adStart <= MAX_READ_ADDR)
	{
		*status = ACCEPTED;	/* address is ok, operation is accepted */
	}
	else
	{
		
	}
	if(*status == ACCEPTED)
	{
		GpioSpiBurstRead(adStart, g_ucIntRamArray, numDat);		
	}
	else
	{
		
	}
}

/*================================================================================================*/
/**
* @brief   This function is called in order to get current operation status.
* @details 	IDLE = 0x00,
*			DONE = 0x01,
*			BUSY = 0x0f,
*			ACCEPTED = 0x10,
*			VALID = 0x11,
*			FAULT = 0x1f,
*			TOOLONG = 0xf0,
*			TOOSHORT = 0xf1,
*			INVALID = 0xff
*
* @param[in]      no
*
* @return unsigned char
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void ShrExp_Get_SbrmStatus(unsigned char *status)
{
	*status = SpiGetOpeStatus();
}

/*================================================================================================*/
/**
* @brief   This function is called in order to abort current read operation
* @details 	
*
* @param[in]      no
*
* @return	no
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void ShrExp_Clear_SbrmStatus(void)
{
	SubRom_Init();
	memset(g_ucIntRamArray, 0, sizeof(g_ucIntRamArray));
}

#ifdef __cplusplus
}
#endif
