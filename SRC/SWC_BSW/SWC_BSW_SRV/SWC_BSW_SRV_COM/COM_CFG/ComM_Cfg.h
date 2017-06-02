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
/* !LINKSTO ComM456,1 */
#if (!defined COMM_CFG_H)
#define COMM_CFG_H

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 8.8 (required)
 *     An external object or function shall be declared in one
 *     and only one file.
 *
 *     Reason:
 *     The files SchM_ComM.h and ComM_Cfg.h contain declarations of
 *     ComM_MainFunction_x. This is due to the issue reported in
 *     http://www.autosar.org/bugzilla/show_bug.cgi?id=53853
 *     and should be fixed in a future version of the Rte.
 */

/*==================[includes]==============================================*/

/* !LINKSTO ComM466,1 */
#include <Std_Types.h>




/*==================[macros]================================================*/
/* *** General feature flags *** */

#if (defined COMM_SERVICE_API_NONE)
#error COMM_SERVICE_API_NONE already defined
#endif
/** \brief Definition that no default service API is set **/
#define COMM_SERVICE_API_NONE   0U

#if (defined COMM_SERVICE_API_ASR32)
#error COMM_SERVICE_API_ASR32 already defined
#endif
/** \brief Definition that AUTOSAR 3.2 service API is set as default **/
#define COMM_SERVICE_API_ASR32 32U

#if (defined COMM_SERVICE_API_ASR40)
#error COMM_SERVICE_API_ASR40 already defined
#endif
/** \brief Definition that AUTOSAR 4.0 service API is set as default **/
#define COMM_SERVICE_API_ASR40 40U

#if (defined COMM_ENABLE_ASR32_SERVICE_API)
#error COMM_ENABLE_ASR32_SERVICE_API already defined
#endif
/** \brief Definition whether AUTOSAR 3.2 service API for ComM is enabled **/
#define COMM_ENABLE_ASR32_SERVICE_API                   STD_OFF

#if (defined COMM_ENABLE_ASR40_SERVICE_API)
#error COMM_ENABLE_ASR40_SERVICE_API already defined
#endif
/** \brief Definition whether AUTOSAR 4.0 service API for ComM is enabled **/
#define COMM_ENABLE_ASR40_SERVICE_API                   STD_OFF

#if (defined COMM_DEFAULT_ASR_SERVICE_API)
#error COMM_DEFAULT_ASR_SERVICE_API already defined
#endif
/** \brief Definition of default service API **/
#define COMM_DEFAULT_ASR_SERVICE_API                    COMM_SERVICE_API_ASR40



#if (defined ComMConf_ComMChannel_ComMChannel_0)
#error ComMConf_ComMChannel_ComMChannel_0 already defined
#endif
/** \brief Symbolic name for the ComM channel "ComMChannel_0" */
#define ComMConf_ComMChannel_ComMChannel_0   0U

#if (!defined COMM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ComMChannel_0)
#error ComMChannel_0 already defined
#endif

/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) 0 */
#define ComMChannel_0                     0U

#if (defined ComM_ComMChannel_0)
#error ComM_ComMChannel_0 already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define ComM_ComMChannel_0   0U
#endif /* COMM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */




#if (defined ComMConf_ComMUser_ComMUser_0)
#error ComMConf_ComMUser_ComMUser_0 already defined
#endif

/** \brief Symbolic name for the ComM user "ComMUser_0" */
#define ComMConf_ComMUser_ComMUser_0   0U

#if (!defined COMM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ComMUser_0)
#error ComMUser_0 already defined
#endif

/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) 0 */
#define ComMUser_0                     0U

#if (defined ComM_ComMUser_0)
#error ComM_ComMUser_0 already defined
#endif

/** \brief Export symbolic name value with module abbreviation as prefix
 ** only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define ComM_ComMUser_0   0U
#endif /* COMM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */



/** \brief Enable/disable development error detection */
#define COMM_DEV_ERROR_DETECT             STD_OFF

/** \brief Enable/disable the version info API */
#define COMM_VERSION_INFO_API             STD_OFF

/** \brief Minimum time duration in ms, spent in the Full Communication
 * Mode */
#define COMM_T_MIN_FULL_COM_MODE_DURATION 5000U

/** \brief Check if Rte is used in ComM */
#define COMM_INCLUDE_RTE                  STD_OFF

/** \brief Check if Dcm usage is enabled in ComM */
#define COMM_DCM_ENABLED                  STD_ON

/** \brief Wake up of one channel shall lead to a wake up of all channels if
 * switch is enabled. */
#define COMM_SYNCHRONOUS_WAKE_UP          STD_OFF

/** \brief mode limitation functionality for channel shall lead to limit mode changing if
 * switch is enabled. **/
#define COMM_MODE_LIMITATION_ENABLED      STD_OFF

/** \brief mode inhibition affects the ECU or not. **/
#define COMM_ECU_GROUP_CLASSIFICATION     3U

/** \brief wakeup inhibition functionality for channel shall limit wakeup if
 * switch is enabled. **/
#define COMM_WAKEUP_INHIBITION_ENABLED    STD_OFF

/** \brief signal if the port interface ComM_CurrentChannelRequest is used */
#define COMM_CURRENTCHANNELREQUEST_ENABLED  STD_OFF


#if (defined COMM_NVM_ENABLED)
#error COMM_NVM_ENABLED already defined
#endif

/** \brief Enable/Disable NvM support */
#define COMM_NVM_ENABLED                  STD_OFF



/** \brief Number of ComM communication channels */
#define COMM_NUM_CHANNELS                 1U

/** \brief Number of ComM users */
#define COMM_NUM_USERS                    1U

/** \brief Flag indicating if Nm access is needed at all.
 *
 * ComM does not need to call Nm if no ComM channel is configured to used
 * either Nm variant PASSIVE or FULL. */
#define COMM_NM_ACCESS_NEEDED             STD_OFF

/** \brief Flag indicating if CanSm access is needed at all. */
#define COMM_CANSM_ACCESS_NEEDED          STD_ON

/** \brief Flag indicating if FrSm access is needed at all. */
#define COMM_FRSM_ACCESS_NEEDED           STD_OFF

/** \brief Flag indicating if LinSm access is needed at all. */
#define COMM_LINSM_ACCESS_NEEDED          STD_OFF

/** \brief Flag indicating if EthSm access is needed at all. */
#define COMM_ETHSM_ACCESS_NEEDED          STD_OFF

/** \brief Flag indicating if there is at least one channel of variant
 * "full" */
#define COMM_NM_VARIANT_FULL_NEEDED       STD_OFF

/** \brief Flag indicating if there is at least one channel of variant
 * "passive" */
#define COMM_NM_VARIANT_PASSIVE_NEEDED    STD_OFF

/** \brief Flag indicating if there is at least one channel of variant
 * "light" */
#define COMM_NM_VARIANT_LIGHT_NEEDED      STD_OFF

/** \brief Flag indicating if there is at least one channel of variant
 * "none" */
#define COMM_NM_VARIANT_NONE_NEEDED       STD_ON

/** \brief Flag indicating if only channels of variant "full" are
 * configured */
#define COMM_NM_VARIANT_FULL_ONLY         STD_OFF

/** \brief Flag indicating if only channels of variant "light" ore "none" are
 * configured */
#define COMM_NM_VARIANT_LIGHT_NONE_ONLY   STD_ON

/** \brief Flag indicating if there is at least one channel of bustype
 * "internal" */
#define COMM_BUSTYPE_INTERNAL_NEEDED      STD_OFF


/** \brief NM channel connected to the ComM channel */
#define COMM_NM_CHANNEL_OF_CHANNEL(idx)   0xFFU /* no NM channel associated */

/* !LINKSTO HisComM0001_Refine1,1, HisComM0002_Refine1,1, HisComM0003_Refine1,1 */
/** \brief Bus type of ComM channel */
#define COMM_BUSTYPE_OF_CHANNEL(idx)      COMM_BUS_TYPE_CAN
#define COMM_BUSTYPE_OF_CHANNEL_DYNAMIC   STD_OFF

/** \brief Nm variant of ComM channel */
/* !LINKSTO HisComM0001_Refine1,1, HisComM0002_Refine1,1, HisComM0003_Refine1,1 */
#define COMM_NM_VARIANT_OF_CHANNEL(idx)    COMM_NM_NONE_VARIANT
#define COMM_NM_VARIANT_OF_CHANNEL_DYNAMIC STD_OFF




/** \brief Number of users of ComM channel, ComMChannel_0,
* ID=0 */
#define COMM_NUM_USERS_OF_CHANNEL_0 1U

/** \brief Number of users of ComM channel */
#define COMM_NUM_USERS_OF_CHANNEL(idx)    COMM_NUM_USERS_OF_CHANNEL_0

#define COMM_PNC_RELEASE_CHANNEL    COMM_NO_INTERNAL_AND_EXTERNAL_REQUESTS


/*------------------[Pnc configuration]-------------------------------------*/
/** \brief General Support for Partial network cluster (Pnc) */
#define COMM_PNC_SUPPORT                  STD_OFF

/** \brief Support for Partial network cluster gateway */
#define COMM_PNC_GW_ENABLED               STD_OFF


/** \brief Number of Partial network cluster (Pnc) */
#define COMM_NUM_PNC                      0U






/** \brief Number of unique Rx EIRA Signals */
#define COMM_NUM_RX_EIRA_SIGNALS      0U

/** \brief Number of unique Tx EIRA Signals */
#define COMM_NUM_TX_EIRA_SIGNALS      0U

/** \brief Number of bytes required to store the received status
 ** of unique Rx EIRA signal assigned for all PNCs */
#if (COMM_NUM_RX_EIRA_SIGNALS > 0U)
#define COMM_SIGNAL_STATUS_BYTES (((COMM_NUM_RX_EIRA_SIGNALS - 1U ) / 8U) + 1U)
#else
#define COMM_SIGNAL_STATUS_BYTES 0U
#endif

/*--------[ COMM_NUM_USERS_OF_PNC( ) ]---------*/
/** \brief Number of users of Pnc */
#define COMM_NUM_USERS_OF_PNC(idx)    (ComM_NumUsersOfPnc[(idx)])

/*--------[ COMM_NUM_CHANNEL_OF_PNC_X ]---------*/


/** \brief Number of Pnc needed by user ComMUser_0, ID=0 */
#define COMM_NUM_PNC_OF_USER_0 0U


/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/* hide declaration in own header if included by ComM itself and RTE is
 * enabled */
#if ((!defined(COMM_INTERNAL_USAGE)) || (COMM_INCLUDE_RTE == STD_OFF))

#define COMM_START_SEC_CODE
#include <MemMap.h>

/* If Rte usage is enabled in the ComM configuration the declaration of these
 * functions are provided by Rte_ComM.h. */

/** \brief Main function for channel 0 */
/* Deviation MISRA-1 */
extern FUNC(void, COMM_CODE) ComM_MainFunction_0(void);

#define COMM_STOP_SEC_CODE
#include <MemMap.h>

#endif

#if (COMM_PNC_SUPPORT == STD_ON)

#define COMM_START_SEC_CODE
#include <MemMap.h>

/** \brief COM Callback function indicates reception of an RX-EIRA
 **
 ** This function is called from the COM module in case the PDU including the
 ** eira signal is received.
 **
 ** \note called in interrupt context */


#define COMM_STOP_SEC_CODE
#include <MemMap.h>

#endif

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* if !defined( COMM_CFG_H ) */
