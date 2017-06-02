#ifndef CANSM_COMM_H
#define CANSM_COMM_H

#include "ComStack_Types.h"

typedef uint8 ComM_ModeType;

extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComMode (
  NetworkHandleType network,
  ComM_ModeType ComM_Mode
);

extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComMode (
  NetworkHandleType network,
  P2VAR(ComM_ModeType, AUTOMATIC, CANSM_APPL_DATA) ComM_ModePtr
);

#endif /*CANSM_COMM_H*/