#include "Fls_17_Pmu.h"
#include "Std_Types.h"
#include "SWTST.h"
#include "SWTST_L.h"

#include "Fee_Cfg.h"
#include "Fee.h"
#include "NvM.h"
#include "App_Stub4NVM.h"
#include "nvm_DataIntern.h"

#include "Dem.h"
//#include "did_datatype.h"

#include "MemIf.h"

#define DEBUG_NVM

typedef struct BlockInfo
{
	uint8 BlockId;
	uint8 BlockType;
	uint32 BlockSize;
	uint8 * pRamBuffer;
} BlockInfoType;

#define NVM_TOTAL_BLOCKNUM 13

/**********************************************************************************************************************/
/* FUNCTIONS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define SWTST_START_SEC_CODE
#include "MemMap.h"

 BlockInfoType Nvm_Temp_BlockInfo[NVM_TOTAL_BLOCKNUM] = 
{
	{
		1, 
		1,
		2,
		0  /*(uint8)NvM_ConfigurationId */
	},
	{
		2,
		0,
		92,
		0  /*(uint8)Dem_NvData */
	},
	{
		3,
		0,
		1024,
		Native_HCU_DTC_Block_RAMAddress
	},
	{
		4,
		0,
		1024,
		Native_DCDC_DTC_Block_RAMAddress
	},
	{
		5,
		0,
		2048,
		Native_Calib_Block_RamAddress
	},
	{
		6,
		0,
		64,
		Native_AppReserved_Block1_RamAddress
	},
	{
		7,
		0,
		64,
		Native_AppReserved_Block2_RamAddress
	},
	{
		8,
		0,
		128,
		Native_AppReserved_Block3_RamAddress
	},
	{
		9,
		0,
		128,
		Native_AppReserved_Block4_RamAddress
	},
	{
		10,
		0,
		512,
		Native_AppReserved_Block5_RamAddress
	},
	{
		11,
		0,
		1024,
		Native_AppReserved_Block6_RamAddress
	},
	{
		12,
		0,
		2048,
		Native_AppReserved_Block7_RamAddress
	},
	{
		13,
		0,
		128,
		Dcm_NvData
	}	
};
	
#define NVM_BLOCK_NUM4DEM 2
#define NVM_BLOCK_NUM4GMLAN 3

#ifdef DEBUG_NVM
uint8 Nvm_ReadFlag = 1;
uint8 Nvm_WriteFlag = 1;
uint16 Nvm_BlockId = 0;
uint8 Nvm_ReadDatabuffer[2048];
uint8 Nvm_WriteDataBuffer[2048];
uint16 Nvm_Count = 0;
uint8 Nvm_DataSetIndex = 0;
uint8 Nvm_EraseImmediateFlag = 0;
uint8 Nvm_ReadAllFlag = 1;
uint8 Nvm_WriteAllFlag = 1;
uint8 Nvm_CanWriteAll = 1;
uint8 NvM_PamanentRAM = 0;
uint8 Nvm_debugauto = 0;
uint8 Nvm_InvalideateFlag = 1;
uint8 Nvm_GetStatus = 1;
uint8 Nvm_BlockErrorStatus = 0;
uint8 Nvm_RestoreDefaultValue = 1;

uint8 Fls_EraseFlag = 1;
#endif


void Fls_17_Pmu_Test_Init(void)
{
	uint32 index = 0;

	for(index = 0; index < 2048; index++)
	{
		Nvm_WriteDataBuffer[index] = (uint8)(index & 0xFF);
	}

	for (index = 0; index < 120; index++)
	{
	
	}
}

void Fls_Update_buffer(uint8 BlockID, uint8 Flag)
{
	uint8 index = BlockID -1;
	uint8* pTemp_Buffer = Nvm_Temp_BlockInfo[index].pRamBuffer;
	uint32 Temp_BufferSize = Nvm_Temp_BlockInfo[index].BlockSize;
	uint32 Count = 0;

	if((BlockID == 1) || (BlockID == 2))
	{
		return;
	}

	
      if(Flag == 0)
      	{
		pTemp_Buffer[0] = BlockID;

		Nvm_WriteDataBuffer[0] = 0x55;
		
		for(Count = 1; Count < Temp_BufferSize; Count++)
		{
			pTemp_Buffer[Count] = (uint8)(Count & 0xFF);

			Nvm_WriteDataBuffer[Count] = (uint8)(Count & 0xFF);
		}
      	}
	else
	{
		for(Count = 0; Count < Temp_BufferSize; Count++)
		{
			pTemp_Buffer[Count] = 0XFF;

			Nvm_ReadDatabuffer[Count] = 0xFF;
		}
	}
}

void Fls_17_Pmu_debug(void)
{
#ifdef DEBUG_NVM
	uint8 Temp_ErrorStatus;
	uint8 index = 0;
	uint32 BlockSize = 0;
	//uint8 * PTemp_buffer;
	
	if(Nvm_debugauto == 0)
	{
		// test the testcase27
		if(Fls_EraseFlag == 0)
		{
			Fls_17_Pmu_Erase(0x00,0x10000);
			Fls_EraseFlag = 1;
			Fls_17_Pmu_Write(0x10000, Nvm_WriteDataBuffer, 32);
			
		}
		
		if(Nvm_InvalideateFlag == 0)
		{
			NvM_InvalidateNvBlock(Nvm_BlockId);
			Nvm_InvalideateFlag = 1;
		}

		if(Nvm_GetStatus == 0)
		{
			NvM_GetErrorStatus(Nvm_BlockId, &Nvm_BlockErrorStatus);
			Nvm_GetStatus = 1;
		}

		if(Nvm_RestoreDefaultValue == 0)
		{
			NvM_RestoreBlockDefaults(Nvm_BlockId, Nvm_ReadDatabuffer);
			Nvm_RestoreDefaultValue = 1;
		}

		if (Nvm_WriteFlag == 0)
		{
			//first step for write: update the RAM buffer
			Fls_Update_buffer(Nvm_BlockId, 0);
			
			NvM_GetErrorStatus(Nvm_BlockId, &Temp_ErrorStatus);
			
			if(Temp_ErrorStatus != NVM_REQ_PENDING)
			{
				// third step for write: if the block is dataset type, set the data index;
				if(Nvm_Temp_BlockInfo[(Nvm_BlockId-1)].BlockType == 2)
				{
					NvM_SetDataIndex(Nvm_BlockId, Nvm_DataSetIndex);
				}

				//forth step for write: write the block
				if(NvM_PamanentRAM == 1)
				{
					NvM_WriteBlock(Nvm_BlockId, 0);
				}
				else
				{
					NvM_WriteBlock(Nvm_BlockId, Nvm_WriteDataBuffer);
				}
				
				Nvm_WriteFlag = 1;
			}
			else if(Temp_ErrorStatus == NVM_REQ_CANCELED)
			{
				
			}
			else
			{
	
			}
		}

		if (Nvm_ReadFlag == 0)
		{
			//First step for write: get the block's status;
			NvM_GetErrorStatus(Nvm_BlockId, &Temp_ErrorStatus);
			if(Temp_ErrorStatus != NVM_REQ_PENDING)
			{
				// just for reading test: clear the RAM buffer
				Fls_Update_buffer(Nvm_BlockId, 1);
				
				if(Nvm_Temp_BlockInfo[(Nvm_BlockId-1)].BlockType == 2)
				{
					NvM_SetDataIndex(Nvm_BlockId, Nvm_DataSetIndex);
				}
				
				//second step for read: read the block;
				if(NvM_PamanentRAM == 1)
				{
					NvM_ReadBlock(Nvm_BlockId, 0);
				}
				else
				{
					NvM_ReadBlock(Nvm_BlockId, Nvm_ReadDatabuffer);
				}
				
				Nvm_ReadFlag = 1;
			}
			else if(Temp_ErrorStatus == NVM_REQ_CANCELED)
			{
				
			}
			else
			{

			}
		}

		if(Nvm_WriteAllFlag == 0)
		{
			for(index = 1; index <= NVM_TOTAL_BLOCKNUM; index++)
			{
				Fls_Update_buffer(index, 0);
				NvM_SetRamBlockStatus(index, TRUE);
			}
			
			NvM_WriteAll();

			Nvm_WriteAllFlag = 1;
		}

		if(Nvm_ReadAllFlag == 0)
		{
			for(index = 1; index <= NVM_TOTAL_BLOCKNUM; index++)
			{
				Fls_Update_buffer(index, 1);
				NvM_SetRamBlockStatus(index, FALSE);
			}
			
			//first step for readall
			NvM_ReadAll();

			Nvm_ReadAllFlag = 1;
		}
	}
	else
	{
			
	}
#endif
}


#define SWTST_STOP_SEC_CODE
#include "MemMap.h"
