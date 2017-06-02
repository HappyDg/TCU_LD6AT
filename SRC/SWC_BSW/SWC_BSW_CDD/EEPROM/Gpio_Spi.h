/**
*   @file    Gpio_Spi.h
*   @version 1.0.0
*
*   @brief   Gpio_Spi - GPIO Emulation Spi abstration layer header file.
*   @details This file is the header containing all the necessary information 
     for Gpio Emulation Spi.
*/
/*==================================================================================================
*   Project              : Shengrui TCU
*   Peripheral           : Gpio
*
*   SW Version           : 1.0.0
*
*   (c) Copyright 2017 Valeo
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef GPIO_SPI_H
#define GPIO_SPI_H

void GpioSpiWriteOneData(unsigned long addr, unsigned short WrPara);

unsigned short GpioSpiReadOneData(unsigned long addr);

void GpioSpiBurstRead(unsigned long addr, unsigned short *ptr, unsigned long length);

void GpioSpiBurstWrite(unsigned long addr, unsigned short *ptr, unsigned long length);

#endif
