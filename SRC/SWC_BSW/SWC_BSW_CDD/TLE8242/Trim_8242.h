#ifndef TRIM_8242_H
#define TRIM_8242_H

#include "Std_Types.h"
#include "Trim_data.h"

#define TRIM_PARAMETER_MAGNIFY     15 
#define CurrentPerLSB              0.9765625

#define TLE8242_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
typedef struct
{
	uint16 HighRealValue;
	uint16 LowRealValue;
} TrimPoint;


typedef struct 
{
	sint32 grd_grd;
	sint32 grd_ofs;
	sint32 ofs_grd;
	sint32 ofs_ofs;		
	sint32 scale_factor; 
} EOL_DATA;


typedef struct 
{
	sint32 gain;
	sint32 offset;
} GainOfset;

#define TLE8242_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define TLE8242_START_SEC_CODE
#include "MemMap.h"
extern void Trim_InitGainAndOffset(void);
extern uint16 Trim_CalculateGainAndOffset(uint8 index,uint16 target_current);


extern GainOfset GainAndOffset[8];
#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"

#endif