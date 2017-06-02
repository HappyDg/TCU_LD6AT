#ifndef BASEM_COMM_H
#define BASEM_COMM_H

#include "Std_Types.h"
#include "BswM_ComM.h"
#include "ComStack_Types.h"

typedef uint8 ComM_ModeType;

typedef enum
{
  /** \brief PNC is requested by a local ComM user */
  PNC_REQUESTED = 0U,
  /** \brief PNC is requested by a remote ComM user */
  PNC_READY_SLEEP,
  /** \brief PNC is active with no deadline monitoring */
  PNC_PREPARE_SLEEP,
  /** \brief PNC does not communicate */
  PNC_NO_COMMUNICATION,
  /** \brief PNC is able to communicate */
  PNC_FULL_COMMUNICATION
} ComM_PncModeType;

FUNC(void, BSWM_CODE) BswM_ComM_CurrentMode
(
  NetworkHandleType Network,
  ComM_ModeType RequestedMode
)
{
}

FUNC(void, BSWM_CODE) BswM_ComM_CurrentPNCMode
(
  PNCHandleType PNC,
  ComM_PncModeType RequestedMode
)
{
}

#endif /*BASEM_COMM_H*/
