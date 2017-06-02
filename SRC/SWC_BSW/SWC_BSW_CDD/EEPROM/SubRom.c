/**
*   @file    SubRom.c
*   @version 1.0.0
*
*   @brief   SubRom - Implements the SubRom driver functionality.
*   @details Implements the SubRom driver. 
*
*   @{
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

#include "Std_Types.h"

#include "IOHAL.h"
#include "Dio.h"
#include "SubRom.h"

EepOpeStatus OpeStatus = IDLE;

/*================================================================================================*/
/**
* @brief   This function is called in order to Init the subrom.
* @details 
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void SubRom_Init(void)
{
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CS, 0);
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CLK, 1);
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_W, 1);
	OpeStatus = IDLE;
	delay_us(POWERON);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to set the CS to working mode.
* @details In BR93H66-W spec, high level "1" means enable CS, low level means disable CS.
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void Set_CS(void)
{
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CS,1);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to clear the CS to disable mode.
* @details In BR93H66-W spec, high level "1" means enable CS, low level means disable CS.
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void Clr_CS(void)
{
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CS, 0);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to set the clock to high level "1".
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void Set_SCK(void)
{
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CLK, 1);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to clear the clock to low level "0".
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void Clr_SCK(void)
{
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CLK, 0);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to set the MOSI to high level "1".
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void Set_MOSI(void)
{
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_W, 1);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to clear the MOSI to low level "0".
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void Clr_MOSI(void)
{
	Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_W, 0);
}

/*================================================================================================*/
/**
* @brief   This function is called in order to read the state of MISO.
* @details 1 means high level, 0 means low level
*
* @param[in]      no.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
unsigned char Read_MISO(void)
{
	unsigned char subrom_r;
	
	subrom_r = !Dio_ReadChannel(DioConf_DioChannel_M_SUBROM_R);
	
	return subrom_r;
}

/*================================================================================================*/
/**
* @brief   This function is called in order to get delay, the unit is us.
* @details 
*
* @param[in]      us		the number of delay
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void delay_us(unsigned int us)
{
	unsigned int k = 0;
	unsigned int j = 0;
	
	for(k=us; k>0; k--)
	{
		for(j=93; j>0; j--)
		{
			asm("nop");
		}
	}
}

/*================================================================================================*/
/**
* @brief   This function is called in order to enable or disable write operation.
*
* @param[in]      enable	ENABLE: enable write operation, DISABLE: disable write operation
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void SpiWriteSwith(unsigned char enable)
{
	int i = 0;
	unsigned short wrCmd = 0;
	unsigned short cycle = (2 + 2 + 8)*4;
	
	/* HEADER = first clock + start bit */
	if(enable)
	{
		wrCmd = (HEADER<<10) | (WEN<<8) | 0xff; /* address is 1 1 * * * * * * when enable   */ 
	}
	else
	{
		wrCmd = (HEADER<<10) | (WDS<<8) | 0x3f; /* address is 0 0 * * * * * *  when disable */
	}
	
	Clr_MOSI();
	delay_us(WRITE_SWITCH_TIME);
	Clr_SCK();
	delay_us(WAITCS_TIME);
	Set_CS();
	
	for(i=0; i<cycle; i++)
	{
		if((i%4) >= 2)
		{
			Set_SCK();
		}
		else
		{
			Clr_SCK();
		}		
		if((wrCmd>>(12 - i/4 - 1))&0x01)
		{
			Set_MOSI();
		}
		else
		{
			Clr_MOSI();
		}
		delay_us(WRITE_SWITCH_TIME);
	}
	
	Clr_SCK();
	delay_us(WRITE_SWITCH_TIME);
	Clr_CS();
	delay_us(WRITE_SWITCH_TIME);
	Set_SCK();
}

/*================================================================================================*/
/**
* @brief   This function is called in order to wait for write operation finished.
* @details 1 means high level, 0 means low level
*
* @param[in]
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void SpiWaitWriteFinish(void)
{
	unsigned long i;
	
	delay_us(WRITE_TIME); /* wait CS to stable */
	Set_CS();
	
	for(i=0; i<WRITETIMEOUT; i++)
	{
		if(Read_MISO())
		{
			OpeStatus = DONE;
			return;
		}
	}
	
	OpeStatus = DONE;
}

/*================================================================================================*/
/**
* @brief   This function is called in order to read one data at request address.
* @details 1 means high level, 0 means low level
*
* @param[in]      addr      The request address.
*
* @return unsigned short
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
unsigned short SpiReadOneData(unsigned long addr)
{
	int i = 0;
	unsigned short reData = 0;
	unsigned short wrCmd = 0;
	unsigned short cycle = (2 + 2 + 8 + 1 + 16)*4;
	
	OpeStatus = BUSY;
	
	/* HEADER = first clock + start bit */
	/* read command consists of header, read instruction and address */
	wrCmd = (HEADER<<10) | (READ<<8) | addr;

	Clr_MOSI();
	delay_us(READ_TIME);
	Clr_SCK();
	delay_us(WAITCS_TIME);
	Set_CS();
	
	for(i=0; i<cycle; i++)
	{
		if((i%4) >= 2)
		{
			Set_SCK();
		}
		else
		{
			Clr_SCK();
		}
		if(i < 48) /* send read command */
		{		
			if((wrCmd>>(12 - (i-1)/4 - 1))&0x01)
			{
				Set_MOSI();
			}
			else
			{
				Clr_MOSI();
			}
		}
		else /* read data from MISO */
		{
			Clr_MOSI();
			if(i >= 52)	/* ignore sync bit */
			{
				if((i%4) == 0)
				{
					reData <<= 1;
					if(Read_MISO())
					{
						reData |= 0x01;
					}
					else
					{
						
					}
				}
				else
				{
					
				}
			}
			else
			{
				
			}
		}
		delay_us(READ_TIME);
	}
	
	Clr_SCK();
	delay_us(READ_TIME);
	Set_MOSI();
	delay_us(READ_TIME);
	Set_SCK();
	delay_us(READ_TIME);
	Clr_CS();
	
	OpeStatus = DONE;
	
	return reData;
}

/*================================================================================================*/
/**
* @brief   This function is called in order to write one data at request address.
* @details 1 means high level, 0 means low level
*
* @param[in]      addr      The request address.
* @param[in]      WrData    The data to be write(one data consists of 2 bytes here).
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void SpiWriteOneData(unsigned long addr, unsigned short WrData)
{
	int i = 0;
	unsigned short cycle = (2 + 2 + 8 + 16)*4;
	unsigned short wrCmd = 0;
	
	OpeStatus = BUSY;
	
	//SpiWriteSwith(ENABLE);	/* Enable write operation first */
	
	/* HEADER = first clock + start bit */
	/* write command consists of header, write instruction and address */
	wrCmd = (HEADER<<10) | (WRITE<<8) | addr;

	Clr_MOSI();
	delay_us(WRITE_TIME);
	Clr_SCK();
	delay_us(WAITCS_TIME);
	Set_CS();
	
	for(i=0; i<cycle; i++)
	{
		if((i%4) >= 2)
		{
			Set_SCK();
		}
		else
		{
			Clr_SCK();
		}
		if(i < 48) /* send write command */
		{
			
			if((wrCmd>>(12 - i/4 - 1))&0x01)
			{
				Set_MOSI();
			}
			else
			{
				Clr_MOSI();
			}
		}
		else	/* write data */
		{
			if((i%4) == 0)
			{
				if(WrData&0x8000)
				{
					Set_MOSI();
				}
				else
				{
					Clr_MOSI();
				}
				WrData <<= 1;
			}
			else
			{
				
			}
		}
		delay_us(WRITE_TIME);
	}
	
	Clr_MOSI();
	delay_us(WAITCS_TIME);
	Clr_SCK();
	Clr_CS();
	delay_us(WRITE_TIME);
	Set_SCK();
	
	SpiWaitWriteFinish();
	Clr_CS();
	Set_MOSI();
	
	//SpiWriteSwith(DISABLE);	/* Disable write operation after write operation */
}

/*================================================================================================*/
/**
* @brief   This function is called in order to read multiple data at request address.
* @details 1 means high level, 0 means low level
*
* @param[in]      addr      The request address.
* @param[in]      ptr    	The pointer of data buffer to be stored.
* @param[in]      length    The length of of data to be read.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void SpiBurstRead(unsigned long addr, unsigned short *ptr, unsigned long length)
{
	int i = 0;
	unsigned short reData = 0;
	unsigned short wrCmd = 0;
	unsigned short cycle = (2 + 2 + 8 + 1 + 16*length)*4;
	
	OpeStatus = BUSY;
	
	/* HEADER = first clock + start bit */
	/* read command consists of header, read instruction and address */
	wrCmd = (HEADER<<10) | (READ<<8) | addr;

	Clr_MOSI();
	delay_us(READ_TIME);
	Clr_SCK();
	delay_us(WAITCS_TIME);
	Set_CS();
	
	for(i=0; i<cycle; i++)
	{
		if((i%4) >= 2)
		{
			Set_SCK();
		}
		else
		{
			Clr_SCK();
		}
		if(i < 48) /* send read command */
		{		
			if((wrCmd>>(12 - i/4 - 1))&0x01)
			{
				Set_MOSI();
			}
			else
			{
				Clr_MOSI();
			}
		}
		else /* read data from MISO */
		{
			Clr_MOSI();
			if(i >= 52)
			{
				if((i%4) == 0)
				{
					reData <<= 1;
					if(Read_MISO())
					{
						reData |= 0x01;
					}
					else
					{
						
					}
				}
				else
				{
					
				}
				if(((i-52)%64) == 62)
				{
					*ptr++ = reData;
					reData = 0;
				}
				else
				{
					
				}
			}
			else
			{
				
			}
		}
		delay_us(READ_TIME);
	}

	Clr_SCK();
	delay_us(READ_TIME);
	Set_MOSI();
	delay_us(READ_TIME);
	Set_SCK();
	delay_us(READ_TIME);
	Clr_CS();

	OpeStatus = DONE;
}

/*================================================================================================*/
/**
* @brief   This function is called in order to write multiple data at request address.
* @details 1 means high level, 0 means low level
*
* @param[in]      addr      The request address.
* @param[in]      ptr    	The pointer of data buffer to be wrote.
* @param[in]      length    The length of of data to be wrote.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void SpiBurstWrite(unsigned long addr, unsigned short *ptr, unsigned long length)
{
	int i = 0;
	
	SpiWriteSwith(ENABLE_SUBROM);	/* Enable write operation first */
	
	for(i=0; i<length; i++)
	{
		SpiWriteOneData(addr++, *ptr++);
	}
	SpiWriteSwith(DISABLE_SUBROM);	/* Disable write operation after write operation */
}


/*================================================================================================*/
/**
* @brief   This function is called in order to simultaneously write a whole block with 128 words data.
* @details Data is writen in bulk at a write time of only Max. 10ms(Max. 5ms:BR93H66RFVM-WC) in
		   conformity with tE/W. When writing data to all addresses, designate each block by B2,B1 and
		   B0, and execute write. Write time is Max. 10ms(Max. 5ms:BR93H66RFVM-WC). 
*
* @param[in]      blockID   The block ID to be writen(this Eeprom just the bit0 is available).
* @param[in]      ptr    	The pointer of data buffer to be wrote.
*
* @return void
*
* @implements BR93H66-W.
*/
/*================================================================================================*/
void SpiWriteAll(unsigned char blockID, unsigned short *ptr)
{
	int i = 0, j = 0;
	unsigned short cycle = (2 + 2 + 8 + 16)*4;
	unsigned short wrCmd = 0;
	
	OpeStatus = BUSY;
	
	SpiWriteSwith(ENABLE_SUBROM);	/* Enable write operation first */
	
	/* HEADER = first clock + start bit */
	/* write command consists of header, write instruction and address */
	/* check the datasheet, the bit7 and bit6 must be 0, 1, bit0 is the block to be written, other bits are available by either “H” or “L”*/
	wrCmd = (HEADER<<10) | (WRAL<<8) | 0x7e | (blockID & 0x01);

	Clr_MOSI();
	delay_us(WRITE_TIME);
	Clr_SCK();
	delay_us(WAITCS_TIME);
	Set_CS();
	
	for(i=0; i<cycle; i++)
	{
		if((i%4) >= 2)
		{
			Set_SCK();
		}
		else
		{
			Clr_SCK();
		}
		if(i < 48) /* send write command */
		{
			if((wrCmd>>(12 - i/4 - 1))&0x01)
			{
				Set_MOSI();
			}
			else
			{
				Clr_MOSI();
			}
		}
		else /* write data */
		{
			if(i == 48)
			{
				wrCmd = *ptr;
			}
			if((i%4) == 0)
			{
				if(wrCmd&0x8000)
				{
					Set_MOSI();
				}
				else
				{
					Clr_MOSI();
				}
				wrCmd <<= 1;
			}
			else
			{
				
			}
		}
		delay_us(WRITE_TIME);
	}
	
	Clr_MOSI();
	delay_us(WAITCS_TIME);
	Clr_SCK();
	Clr_CS();
	delay_us(WRITE_TIME);
	Set_SCK();
	
	SpiWaitWriteFinish();
	Clr_CS();
	Set_MOSI();
	
	SpiWriteSwith(DISABLE_SUBROM);	/* Disable write operation after write operation */
}

/*================================================================================================*/
/**
* @brief   This function is called in order to get current operation status.
* @details 	IDLE = 0x00,
*			DONE = 0x01,
*			BUSY = 0x0f,
*			ACCEPTED = 0x10,
*			VALID = 0x11,
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
unsigned char SpiGetOpeStatus(void)
{
	return (unsigned char)OpeStatus;
}

#ifdef __cplusplus
}
#endif
