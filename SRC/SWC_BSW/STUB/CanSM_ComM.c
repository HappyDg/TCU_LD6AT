#ifndef CANSM_COMM_H
#define CANSM_COMM_H

#include "Std_Types.h"
#include "CanSM_ComM.h"
#include "ComStack_Types.h"

typedef uint8 ComM_ModeType;

FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComMode (
  NetworkHandleType network,
  ComM_ModeType ComM_Mode
)
{
   Std_ReturnType retval = E_OK;
}

FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComMode (
  NetworkHandleType network,
  P2VAR(ComM_ModeType, AUTOMATIC, CANSM_APPL_DATA) ComM_ModePtr
)
{
   Std_ReturnType retval = E_OK;
}

#endif /*CANSM_COMM_H*/