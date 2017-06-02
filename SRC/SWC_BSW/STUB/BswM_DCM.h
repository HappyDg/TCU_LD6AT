/*------------------------------------------------------------------------------
|                                                                              |
|  Copyright (C) BMW Group 2011                                                |
|                                                                              |
|  MODULE    : BswM_DCM.h                                                      |
|                                                                              |
|  PROJECT   : BMW AUTOSAR Core                                                |
|                                                                              |
|  PURPOSE   :                                                                 |
|                                                                              |
|  REMARKS   : ---                                                             |
|                                                                              |
|                                                                              |
|------------------------------------------------------------------------------|
|  DISCLAIMER:                                                                 |
|  As the program is not fully tested and qualified for series production      |
|  use, the user shall not be entitled to use the program in connection        |
|  with any series production. BMW provides the user with the program only     |
|  as sample application (for testing purposes).                               |
|                                                                              |
-------------------------------------------------------------------------------*/
#define I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#ifndef I_KNOW_THAT_THIS_CODE_IS_NOT_FOR_PRODUCTION
#error "the program must not be used in connection with series production"
#endif


#if (!defined BSWM_DCM_H)
#define BSWM_DCM_H

/*==================[includes]===============================================*/

#include <BswM.h>   /* Module public API         */

/*==================[macros]=================================================*/

/* empty */

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

// #define BSWM_START_SEC_CODE
// #include <MemMap.h>

/** \brief Requests communication modes (Called by DCM).
 **
 ** This function is called by DCM to request communication modes.
 **
 ** Precondition: None
 **
 ** \param[in]    Network       - The communication channel that the diagnostic
 **                               mode corresponds to.
 **               RequestedMode - The requested diagnostic communication mode.
 ** \param[inout] None.
 ** \param[out]   None.
 **
 ** \ServiceID{6}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, BSWM_CODE) BswM_Dcm_RequestCommunicationMode(
  NetworkHandleType Network,
  Dcm_CommunicationModeType RequestedMode
);

/** \brief Requests diagnostic modes (Called by DCM).
 **
 ** This function is called by DCM to request diagnostic modes.
 **
 ** Precondition: None
 **
 ** \param[in]    RequestedMode - The requested diagnostic session mode.
 ** \param[inout] None.
 ** \param[out]   None.
 **
 ** \ServiceID{8}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, BSWM_CODE) BswM_Dcm_RequestSessionMode
(
  Dcm_SesCtrlType RequestedMode
);

/** \brief Requests a reset of the ECU (Called by DCM).
 **
 ** This function is called by DCM to request a reset of the ECU.
 **
 ** Precondition: None
 **
 ** \param[in]    RequestedMode - The requested DCM reset mode.
 ** \param[inout] None.
 ** \param[out]   None.
 **
 ** \ServiceID{7}
 ** \Reentrancy{Reentrant}
 ** \Synchronicity{Synchronous} */
extern FUNC(void, BSWM_CODE) BswM_Dcm_RequestResetMode
(
  Dcm_ResetModeType RequestedMode
);

// #define BSWM_STOP_SEC_CODE
// #include <MemMap.h>


/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

#endif /* if !defined( BSWM_DCM_H ) */
/*==================[end of file]============================================*/
