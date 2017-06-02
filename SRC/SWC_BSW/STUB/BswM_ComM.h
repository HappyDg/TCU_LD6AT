#ifndef BASEM_COMM_H
#define BASEM_COMM_H

#include "ComStack_Types.h"

typedef uint8 ComM_ModeType;


extern FUNC(void, BSWM_CODE) BswM_ComM_CurrentMode
(
  NetworkHandleType Network,
  ComM_ModeType RequestedMode
);

extern FUNC(void, BSWM_CODE) BswM_ComM_CurrentPNCMode
(
  PNCHandleType PNC,
  ComM_PncModeType RequestedMode
);

#endif /*BASEM_COMM_H*/
