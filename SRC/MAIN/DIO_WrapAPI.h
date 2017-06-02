
#include "Std_Types.h"

extern void Dio_WrapAPI_Init(void);

extern void ShrExp_Get_Switch(uint8 idx, uint8 *b);

extern void ShrExp_Get_Speed( uint8 idx, uint16 *n, uint8 *sDir, uint8 *bSply, uint8 *stDiaRdy, uint8 *stDiaDsbc);
extern void Shrexp_set_Speed ( uint8 nPlsPerRe[]);

extern void ShrExp_Get_Position(uint8 idx, uint16 *rDuty, uint8 *bSply, uint8 *stDiaRdy, uint8 *stDiaDsbc);

extern void ShrExp_Set_Position(uint8 stPos, uint8 stQual);

extern void ShrExp_Get_ADValue(uint8 idx, uint16 *p, uint8 *bSply);

extern void ShrExp_Get_ResistanceValue(uint32 *p, uint8 *bSply);


extern void ShrExp_Get_Battery(uint16 *u);

extern void ShrExp_Get_Ignition(uint16 *u, uint8 *b);

extern void ShrExp_Get_PressureAD(uint16 *p, uint8 *bSply);

extern void ShrExp_Set_SolenoidFeed(uint8 idx, uint8 b);
extern void ShrExp_Get_SolenoidFeed( uint8 idx, uint8 *s, uint16 *u, uint8 *stDiaRdy, uint8 *stDiaDsbc);

extern void ShrExp_Set_StartEnable(uint8 b);
extern void ShrExp_Get_StartEnable( uint8 * stDiaRdy, uint8 *stDiaDsbc);

extern void ShrExp_Set_Relay(uint8 b);
extern void ShrExp_Get_Relay(uint8 * stDiaRdy, uint8 *stDiaDsbc);

extern void ShrExp_Set_OnOffSolenoid(uint8 idx, uint8 b);
extern void ShrExp_Get_OnOffSolenoid( uint8 idx, uint8 * stDiaRdy, uint8 *stDiaDsbc);

extern void Shrexp_get_CpuLd ( uint16 *rCpuLd, uint16 *rCpuLdMax );

extern void Dio_Get_PCBTemp( sint16 *Temp);