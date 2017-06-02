#ifndef TRIM_8242_App_H
#define TRIM_8242_App_H

#include "Std_Types.h"

#define TLE8242_START_SEC_CODE
#include "MemMap.h"

extern void Trim_Feedback_InitGainAndOffset(void);
extern uint16 Trim_Feedback_CalculateGainAndOffset(uint8 index,uint16 feedback_current);

#define TLE8242_STOP_SEC_CODE
#include "MemMap.h"

#endif