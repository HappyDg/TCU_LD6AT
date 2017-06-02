/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

#if(!defined CANTP_CFG_H)
#define CANTP_CFG_H

/* CanTp_Cfg.h shall define constant and customizable data for module configuration
   at pre-compile time.
 */
/* !LINKSTO CanTp.ASR40.CANTP001, 1 */
/*==================[includes]===============================================*/
#include <TSAutosar.h>      /* EB specific standard types */
#include <ComStack_Types.h> /* typedefs for AUTOSAR com stack */

/*==================[macros]=================================================*/

/** \brief switch for supporting PbcgfM module */

#define CANTP_PBCFGM_SUPPORT_ENABLED      STD_OFF
#define CANTP_ISVALIDCONFIG_MMAP_ENABLED  STD_OFF



/** \brief Switch for DET usage */
#define CANTP_DEV_ERROR_DETECT            STD_OFF

/** \brief Switch for GetVersionInfo API */
#define CANTP_VERSION_INFO_API            STD_OFF

/** \brief Defines if receive cancellation API is available. */
#define CANTP_RX_CANCELLATION_API          STD_OFF

/** \brief Defines if transmit cancellation API is available. */
#define CANTP_TX_CANCELLATION_API          STD_OFF

/** \brief Handling of N_SA values
 **
 ** The macro CANTP_DYNAMIC_NSA_ENABLED is used to specify if N_SA values are fix values,
 ** which are specified at configuration time (normal Autosar behaviour) or
 ** it is possible to change the N_SA values for each
 ** Pdu at runtime. If enabled, change at runtime is possible.
 */
#define CANTP_DYNAMIC_NSA_ENABLED   STD_OFF
#define CANTP_DYNAMIC_NSA_API       STD_OFF

/** \brief defines if CanTp_ChangeParameter() is enabled */
#define CANTP_CHANGE_PARAMETER_REQ_API    STD_OFF

/* jumptable related macros */

/** \brief Jumptable support is deactivated */
#define CANTP_JUMPTABLE_OFF             0U
/** \brief Jumptable support is activated and module acts as server */
#define CANTP_JUMPTABLE_SERVER          1U
/** \brief Jumptable support is activated and module acts as client */
#define CANTP_JUMPTABLE_CLIENT          2U

/** \brief General CanTp jumptable support */
#define CANTP_JUMPTABLE_SUPPORT           STD_OFF

/** \brief CanTp jumptable mode
 **
 ** This macro defines the current jumptable mode (not supported, server,
 ** client).
 */
#define CANTP_JUMPTABLE_MODE              CANTP_JUMPTABLE_OFF

/** \brief CanTp jumptable support: SchM used as macro
 **
 ** This macro defines, if the SchM functions shall be accessed via function
 ** pointers in the exit jumptable (value STD_ON) or if macros are defined
 ** and used for them (value STD_OFF).
 */
#define CANTP_EXIT_JUMPTABLE_WITH_SCHM    STD_OFF

/** \brief CanTp jumptable configuration
 **
 ** This macro defines if the current CanTp shall provide the entry jumptable
 ** to the application (value STD_ON) or if the CanTp functions are provided
 ** (value STD_OFF).
 */
#define CANTP_PROVIDE_JUMPTABLE           STD_OFF

/** \brief Defines if the CanTp provides all of its API functions
 **
 ** This macro defines if the CanTp shall provide all of its API functions. If
 ** jumptable support is on and wrapper macros shall be used, this macro has
 ** the value STD_OFF. Otherwise it is STD_ON.
 */
#define CANTP_PROVIDE_API_FUNCTIONS       STD_ON

/** \brief defines if general purpose timer is enabled for timeout handling of the channels */
#define CANTP_USE_GPT  STD_OFF

/** \brief Maximum number TX channels supported.
 */
#define CANTP_MAX_TX_CHANNELS 10U

/** \brief Maximum number RX channels supported.
 */
#define CANTP_MAX_RX_CHANNELS 10U

/** \brief Maximum number TX N-SDUs supported.
 */
#define CANTP_MAX_TX_NSDUS 10U

/** \brief Maximum number RX N-SDUs supported.
 */
#define CANTP_MAX_RX_NSDUS 10U

/** \brief Maximum number flow control PDUs supported.
 */
#define CANTP_MAX_FC_PDUS 10U

/* ----- Pre-processor switch to enable/diable relocateable postbuild config ----- */
#if(CANTP_PBCFGM_SUPPORT_ENABLED == STD_ON)
#define CANTP_RELOCATABLE_CFG_ENABLE  STD_OFF
#else
#define CANTP_RELOCATABLE_CFG_ENABLE  STD_ON
#endif

/** \brief Compile time verification value */
#define CANTP_CFG_SIGNATURE 3746009740U

/** \brief Compile time Published information configuration verification value */
#define CANTP_PUBLIC_INFO_SIGNATURE 1103003787U




/*------------------[Defensive programming]---------------------------------*/

#if (defined CANTP_DEFENSIVE_PROGRAMMING_ENABLED)
#error CANTP_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define CANTP_DEFENSIVE_PROGRAMMING_ENABLED   STD_OFF

#if (defined CANTP_PRECONDITION_ASSERT_ENABLED)
#error CANTP_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define CANTP_PRECONDITION_ASSERT_ENABLED     STD_OFF

#if (defined CANTP_POSTCONDITION_ASSERT_ENABLED)
#error CANTP_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define CANTP_POSTCONDITION_ASSERT_ENABLED    STD_OFF

#if (defined CANTP_UNREACHABLE_CODE_ASSERT_ENABLED)
#error CANTP_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define CANTP_UNREACHABLE_CODE_ASSERT_ENABLED STD_OFF

#if (defined CANTP_INVARIANT_ASSERT_ENABLED)
#error CANTP_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define CANTP_INVARIANT_ASSERT_ENABLED        STD_OFF

#if (defined CANTP_STATIC_ASSERT_ENABLED)
#error CANTP_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define CANTP_STATIC_ASSERT_ENABLED           STD_OFF



/*====================[Symbolic Names]=======================================*/

/*==================[type definitions]=======================================*/

/*==================[external constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]=========================================*/

/*==================[external function declarations]=========================*/
#define CANTP_START_SEC_CODE
#include <MemMap.h>

  

#define CANTP_STOP_SEC_CODE
#include <MemMap.h>
/*==================[end of file]============================================*/
#endif /* if !defined( CANTP_CFG_H ) */

