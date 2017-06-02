/**
*   @file    Gpio_Spi.c
*   @version 1.0.0
*
*   @brief   Gpio_Spi - Implements the GPIO emulation spi driver functionality.
*   @details Implements the Gpio emulation spi driver. 
*
*   @{
*/
/*==================================================================================================
*   Project              : Shengrui TCU
*   Peripheral           : Gpio
*   Dependencies         : 
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

#include "Gpio_Spi.h"
#include "SubRom.h"

/*================================================================================================*/
/**
* @brief   This function is called in order to write one data in MOSI.
* @details 
*
* @param[in]      addr      The request address.
* @param[in]      WrPara		the one data to be write
*
* @return no
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void GpioSpiWriteOneData(unsigned long addr, unsigned short WrPara)
{
	SpiWriteOneData(addr, WrPara);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to read one data in MISO.
* @details 
*
* @param[in]      addr      The request address.
*
* @return unsigned short
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
unsigned short GpioSpiReadOneData(unsigned long addr)
{
	return SpiReadOneData(addr);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to read multiple data at request address.
* @details 1 means high level, 0 means low level
*
* @param[in]      addr      The request address.
* @param[in]      ptr    	The pointer of data buffer to be stored.
* @param[in]      length    The length of data to be read.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void GpioSpiBurstRead(unsigned long addr, unsigned short *ptr, unsigned long length)
{
	SpiBurstRead(addr, ptr, length);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to write multiple data at request address.
* @details 1 means high level, 0 means low level
*
* @param[in]      addr      The request address.
* @param[in]      ptr    	The pointer of data buffer to be wrote.
* @param[in]      length    The length of data to be wrote.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void GpioSpiBurstWrite(unsigned long addr, unsigned short *ptr, unsigned long length)
{
	SpiBurstWrite(addr, ptr, length);
}

#ifdef __cplusplus
}
#endif
