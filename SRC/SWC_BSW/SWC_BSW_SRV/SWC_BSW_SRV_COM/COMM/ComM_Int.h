/**
 * \file
 *
 * \brief AUTOSAR ComM
 *
 * This file contains the implementation of the AUTOSAR
 * module ComM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined COMM_INT_H)
#define COMM_INT_H

/*==================[inclusions]============================================*/

#include <ComM_BSW_Types.h>
#include <ComM_HsmComM.h>

/*==================[macros]================================================*/

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/** \brief Proxy function for SchM_Enter_ComM_SCHM_COMM_EXCLUSIVE_AREA_0
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation unit ComM.c
 **
 ** \return No return value. */
FUNC(void, COMM_CODE) ComM_Enter_SCHM_COMM_EXCLUSIVE_AREA_0 (
  void);

/** \brief Proxy function for SchM_Exit_ComM_SCHM_COMM_EXCLUSIVE_AREA_0
 **
 ** This function was introduced to avoid RTE includes
 ** within compilation unit ComM.c
 **
 ** \return No return value. */
FUNC(void, COMM_CODE) ComM_Exit_SCHM_COMM_EXCLUSIVE_AREA_0 (
  void);

/** \brief Evaluate ComM Communication Channels
 ** This function checks the ComM channel mode and emits specific event
 ** related to ComMode.
 ** If the ComM_CurrentChannelRequest RTE interface is enabled, it also
 ** signals the current state of this interface to the RTE.
 ** \param[in] Channel Network channel on which the mode transition
 ** has occurred. */
FUNC(void, COMM_CODE) ComM_EvaluateChannel
(
  const uint8 Channel
);

/** \brief Wrapper function to get the number of users of a channel.
 *
 * Accessor function to retrieve the number of users of a given channel
 *
 * \param[in] Channel Network channel of interest
 * \return The number of users of the given channel
 */
FUNC(uint8, COMM_CODE) ComM_EB_GetNumUsersOfChannel
(
    const uint8 Channel
);

/** \brief Wrapper function to access the ComM_UsersOfChannel array
 *
 * Accessor function of the 2D ComM_UsersOfChannel array. The array
 * contains all users of all channels.
 *
 * \param[in] Channel Network channel of interest
 * \param[in] User The user position within the ComM_UsersOfChannel array
 * \return The ID of the user at the given user position of a channel
 */
FUNC(uint8, COMM_CODE) ComM_EB_GetUsersOfChannel
(
    const uint8 Channel,
    const uint8 User
);

/** \brief Wrapper function to access the ComM_UserRequestedComMode array
 *
 * Accessor function to retrieve the requested communication mode of a
 * given user.
 *
 * \param[in] User A user Id
 * \return The requested communication mode of a given user
 */
FUNC(ComM_ASR40_ModeType, COMM_CODE) ComM_EB_GetUserRequestedComMode
(
    const uint8 User
);

/** \brief Wrapper function to access the ComM_RequestedComMode array
 *
 * Accessor function to set the current requested communication mode.
 *
 * \param[in] Channel Network channel of interest
 * \param[in] ComMode The requested communication mode
 */
FUNC(void, COMM_CODE) ComM_EB_SetRequestedComMode
(
    const uint8 Channel,
    ComM_ASR40_ModeType ComMode
);

#if (COMM_INCLUDE_RTE == STD_ON)
#if (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE)

/** \brief Signal mode of a channel to a specific user via RTE
 *
 * The function receives a user and translates its channel mode into
 * the values expected by the RTE. The reported values depend
 * on the AUTOSAR service API selected as default.
 *
 * \param[in] User  User of channel whose mode must be reported via RTE */
FUNC(void, COMM_CODE) ComM_RteNotify(
    uint8               User,
    ComM_ASR40_ModeType CurComMMode
);

#endif /* (COMM_DEFAULT_ASR_SERVICE_API != COMM_SERVICE_API_NONE) */

#if (COMM_ENABLE_ASR32_SERVICE_API == STD_ON)

/** \brief Signal mode of a channel to a specific user via RTE
 *
 * The function receives a user and translates its channel mode into
 * the ASR32 values expected by the RTE.
 *
 * \param[in] User  User of channel whose mode must be reported via RTE */
FUNC(void, COMM_CODE) ComM_ASR32_RteNotify(
    uint8               User,
    ComM_ASR32_ModeType CurComMMode
);

#endif /* (COMM_ENABLE_ASR32_SERVICE_API == STD_ON) */

#if (COMM_ENABLE_ASR40_SERVICE_API == STD_ON)

/** \brief Signal mode of a channel to a specific user via RTE
 *
 * The function receives a user and translates its channel mode into
 * the ASR40 values expected by the RTE.
 *
 * \param[in] User  User of channel whose mode must be reported via RTE */
FUNC(void, COMM_CODE) ComM_ASR40_RteNotify(
    uint8               User,
    ComM_ASR40_ModeType CurComMMode
);

#endif /* (COMM_ENABLE_ASR40_SERVICE_API == STD_ON) */
#endif /* (COMM_INCLUDE_RTE == STD_ON) */

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( COMM_INT_H ) */
/*==================[end of file]===========================================*/
