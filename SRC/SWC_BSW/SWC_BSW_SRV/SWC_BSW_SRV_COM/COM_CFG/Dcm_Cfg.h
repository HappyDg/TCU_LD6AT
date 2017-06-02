/**
 * \file
 *
 * \brief AUTOSAR Dcm
 *
 * This file contains the implementation of the AUTOSAR
 * module Dcm.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined DCM_CFG_H)
#define DCM_CFG_H

/*==================[includes]===================================================================*/

#include <Std_Types.h>

/*==================[macros]=====================================================================*/
/*------------------[Defensive programming]---------------------------------*/

#if (defined DCM_DEFENSIVE_PROGRAMMING_ENABLED)
#error DCM_DEFENSIVE_PROGRAMMING_ENABLED is already defined
#endif
/** \brief Defensive programming usage
 **
 ** En- or disables the usage of the defensive programming */
#define DCM_DEFENSIVE_PROGRAMMING_ENABLED   STD_OFF
#if (defined DCM_PRECONDITION_ASSERT_ENABLED)
#error DCM_PRECONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Precondition assertion usage
 **
 ** En- or disables the usage of precondition assertion checks */
#define DCM_PRECONDITION_ASSERT_ENABLED     STD_OFF
#if (defined DCM_POSTCONDITION_ASSERT_ENABLED)
#error DCM_POSTCONDITION_ASSERT_ENABLED is already defined
#endif
/** \brief Postcondition assertion usage
 **
 ** En- or disables the usage of postcondition assertion checks */
#define DCM_POSTCONDITION_ASSERT_ENABLED    STD_OFF
#if (defined DCM_UNREACHABLE_CODE_ASSERT_ENABLED)
#error DCM_UNREACHABLE_CODE_ASSERT_ENABLED is already defined
#endif
/** \brief Unreachable code assertion usage
 **
 ** En- or disables the usage of unreachable code assertion checks */
#define DCM_UNREACHABLE_CODE_ASSERT_ENABLED STD_OFF
#if (defined DCM_INVARIANT_ASSERT_ENABLED)
#error DCM_INVARIANT_ASSERT_ENABLED is already defined
#endif
/** \brief Invariant assertion usage
 **
 ** En- or disables the usage of invariant assertion checks */
#define DCM_INVARIANT_ASSERT_ENABLED        STD_OFF
#if (defined DCM_STATIC_ASSERT_ENABLED)
#error DCM_STATIC_ASSERT_ENABLED is already defined
#endif
/** \brief Static assertion usage
 **
 ** En- or disables the usage of static assertion checks */
#define DCM_STATIC_ASSERT_ENABLED           STD_OFF




#if (defined DcmConf_DcmDslProtocolRow_0_DcmDslProtocolTx_0)
#error DcmConf_DcmDslProtocolRow_0_DcmDslProtocolTx_0 already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDslProtocolRow_0_DcmDslProtocolTx_0 0

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DcmDslProtocolRow_0_DcmDslProtocolTx_0)
#error DcmDslProtocolRow_0_DcmDslProtocolTx_0 already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DcmDslProtocolRow_0_DcmDslProtocolTx_0 0

#if (defined Dcm_DcmDslProtocolRow_0_DcmDslProtocolTx_0)
#error Dcm_DcmDslProtocolRow_0_DcmDslProtocolTx_0 already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DcmDslProtocolRow_0_DcmDslProtocolTx_0 0
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */


#if (defined DCM_NUM_RX_PDU_ID) /* To prevent double declaration */
#error DCM_NUM_RX_PDU_ID already defined
#endif /* if (defined DCM_NUM_RX_PDU_ID) */

#if (defined DcmConf_DcmDslProtocolRow_0_DcmDslProtocolRx_0)
#error DcmConf_DcmDslProtocolRow_0_DcmDslProtocolRx_0 already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDslProtocolRow_0_DcmDslProtocolRx_0 0

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DcmDslProtocolRow_0_DcmDslProtocolRx_0)
#error DcmDslProtocolRow_0_DcmDslProtocolRx_0 already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DcmDslProtocolRow_0_DcmDslProtocolRx_0 0

#if (defined Dcm_DcmDslProtocolRow_0_DcmDslProtocolRx_0)
#error Dcm_DcmDslProtocolRow_0_DcmDslProtocolRx_0 already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DcmDslProtocolRow_0_DcmDslProtocolRx_0 0
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */
#if (defined DcmConf_DcmDslProtocolRow_0_DcmDslProtocolRx_1)
#error DcmConf_DcmDslProtocolRow_0_DcmDslProtocolRx_1 already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDslProtocolRow_0_DcmDslProtocolRx_1 1

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DcmDslProtocolRow_0_DcmDslProtocolRx_1)
#error DcmDslProtocolRow_0_DcmDslProtocolRx_1 already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DcmDslProtocolRow_0_DcmDslProtocolRx_1 1

#if (defined Dcm_DcmDslProtocolRow_0_DcmDslProtocolRx_1)
#error Dcm_DcmDslProtocolRow_0_DcmDslProtocolRx_1 already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DcmDslProtocolRow_0_DcmDslProtocolRx_1 1
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Definition of number of reception(Rx) Pdu Ids **/
#define DCM_NUM_RX_PDU_ID                    2U

#if (defined DCM_NUM_PROTOCOL)       /* To prevent double declaration */
#error DCM_NUM_PROTOCOL already defined
#endif /* if (defined DCM_NUM_PROTOCOL) */

/** \brief Definition of number of protocols  **/
#define DCM_NUM_PROTOCOL                     1U

#if (defined DcmConf_DcmDslProtocol_DcmDslProtocolRow_0)
#error DcmConf_DcmDslProtocol_DcmDslProtocolRow_0 already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDslProtocol_DcmDslProtocolRow_0 DCM_UDS_ON_CAN

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DcmDslProtocolRow_0)
#error DcmDslProtocolRow_0 already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DcmDslProtocolRow_0 DCM_UDS_ON_CAN

#if (defined Dcm_DcmDslProtocolRow_0)
#error Dcm_DcmDslProtocolRow_0 already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DcmDslProtocolRow_0 DCM_UDS_ON_CAN
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined DCM_NUM_BUFFER) /* To prevent double declaration */
#error DCM_NUM_BUFFER already defined
#endif /* if (defined DCM_NUM_BUFFER) */

/** \brief Definition of number of buffers **/
#define DCM_NUM_BUFFER                       3U


#if (defined DCM_NUM_TX_PDU_ID) /* To prevent double declaration */
#error DCM_NUM_TX_PDU_ID already defined
#endif /* if (defined DCM_NUM_TX_PDU_ID) */

/** \brief Definition of number of Transmission(Tx) Pdu Ids **/
#define DCM_NUM_TX_PDU_ID                    1U

#if (defined DCM_NUM_CONF_PDU_ID) /* To prevent double declaration */
#error DCM_NUM_CONF_PDU_ID already defined
#endif /* if (defined DCM_NUM_CONF_PDU_ID) */

/** \brief Definition of number of Transmission(Tx) Confirmation Pdu Ids **/
#define DCM_NUM_CONF_PDU_ID                    1U

#if (defined DCM_NUM_SID_TABLE) /* To prevent double declaration */
#error DCM_NUM_SID_TABLE already defined
#endif /* if (defined DCM_NUM_SID_TABLE) */

/** \brief Number Service ID table entries configured **/
#define DCM_NUM_SID_TABLE                    1U

#if (defined DCM_NUM_SES_TAB_ENTRY) /* To prevent double declaration */
#error DCM_NUM_SES_TAB_ENTRY already defined
#endif /* if (defined DCM_NUM_SES_TAB_ENTRY) */

/** \brief Number of configured diagnostic sessions **/
#define DCM_NUM_SES_TAB_ENTRY                4U

#if (defined DCM_NUM_SEC_TAB_ENTRY) /* To prevent double declaration */
#error DCM_NUM_SEC_TAB_ENTRY already defined
#endif /* if (defined DCM_NUM_SEC_TAB_ENTRY) */

/** \brief Number of configured security levels **/
#define DCM_NUM_SEC_TAB_ENTRY                0U

#if (defined DCM_NUM_ROUTINES) /* To prevent double declaration */
#error DCM_NUM_ROUTINES already defined
#endif /* if (defined DCM_NUM_ROUTINES) */


/** \brief Number of Routines configured **/
#define DCM_NUM_ROUTINES 0U


#if (defined DCM_NUM_ROUTINE_INFO) /* To prevent double declaration */
#error DCM_NUM_ROUTINE_INFO already defined
#endif /* if (defined DCM_NUM_ROUTINE_INFO) */

/** \brief Number of DcmDspRoutineInfos referenced by DcmDspRoutines **/
#define DCM_NUM_ROUTINE_INFO                1U

#if (defined DCM_NUM_COMCONTROL_ALL_CHANNEL) /* To prevent double declaration */
#error DCM_NUM_COMCONTROL_ALL_CHANNEL already defined
#endif /* if (defined DCM_NUM_COMCONTROL_ALL_CHANNEL) */

/** \brief Number of Communication Control All channels **/
#define DCM_NUM_COMCONTROL_ALL_CHANNEL                0U

#if (defined DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL) /* To prevent double declaration */
#error DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL already defined
#endif /* if (defined DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL) */

/** \brief Number of Communication Control Specific channels **/
#define DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL                0U


#if (defined DCM_DSP_POWER_DOWN_TIME) /* To prevent double declaration */
#error DCM_DSP_POWER_DOWN_TIME already defined
#endif /* if (defined DCM_DSP_POWER_DOWN_TIME) */

/** \brief Minimum stand-by time the server will remain in the power-down sequence **/
#define DCM_DSP_POWER_DOWN_TIME                10U

#if (defined DCM_PAGEDBUFFER_ENABLED)   /* To prevent double declaration */
#error DCM_PAGEDBUFFER_ENABLED already defined
#endif /* if (defined DCM_PAGEDBUFFER_ENABLED) */

/** \brief Definition if paged buffer handling is enabled **/
#define DCM_PAGEDBUFFER_ENABLED              STD_ON

#if (defined DCM_PAGED_BUFFER_TIMEOUT) /* To prevent double declaration */
#error DCM_PAGED_BUFFER_TIMEOUT already defined
#endif /* if (defined DCM_PAGED_BUFFER_TIMEOUT) */

/** \brief Definition of Timeout for Paged buffer transmission.  This timeout
 ** is counted in units of DCM_TASK_TIME **/
#define DCM_PAGED_BUFFER_TIMEOUT             5U

#if (defined DCM_DEV_ERROR_DETECT)
#error DCM_DEV_ERROR_DETECT already defined
#endif
/** \brief Switch, indicating if development error detection is activated for
 ** DCM */
#define DCM_DEV_ERROR_DETECT                 STD_OFF
#if (defined DCM_DIAG_RESP_MAX_NUM_RESP_PEND )  /* To prevent double declaration */
#error DCM_DIAG_RESP_MAX_NUM_RESP_PEND already defined
#endif /* #if (defined DCM_DIAG_RESP_MAX_NUM_RESP_PEND ) */

/** \brief Maximum number of Pending responses possible **/
#define DCM_DIAG_RESP_MAX_NUM_RESP_PEND      5U

#if (defined DCM_VERSION_INFO_API)
#error DCM_VERSION_INFO_API already defined
#endif
/** \brief Switch, indicating if Dcm_GetVersionInfo() API is activated for
 ** DCM */
#define DCM_VERSION_INFO_API                 STD_ON
#if (defined DCM_INCLUDE_RTE)
#error DCM_INCLUDE_RTE already defined
#endif
/** \brief Switch, indicating if RTE is available and can be used from DCM */
#define DCM_INCLUDE_RTE                      STD_OFF
#if (defined DCM_SECURITYACCESS_STRICT)
#error DCM_SECURITYACCESS_STRICT already defined
#endif
/** \brief Switch, indicating whether the strict SecurityAccess mechanism is activated for the DCM */
#define DCM_SECURITYACCESS_STRICT                      STD_OFF
#if (defined DCM_MODEDECLARATION_SUPPORT)
#error DCM_MODEDECLARATION_SUPPORT already defined
#endif
/** \brief Switch, indicating if Mode declaration support is enabled and SchM switch APIs
 ** are generated by RTE to be used for notifying mode switches to mode users */
#define DCM_MODEDECLARATION_SUPPORT                      STD_OFF
#if (defined DCM_MODE_DECLARATION_OEM_BL) /* To prevent double declaration */
#error DCM_MODE_DECLARATION_OEM_BL already defined
#endif /* if (defined DCM_MODE_DECLARATION_OEM_BL) */

/** \brief Indicates, if OEM boot support and mode declaration is enabled */
#define DCM_MODE_DECLARATION_OEM_BL           STD_OFF
#if (defined DCM_MODE_DECLARATION_SYS_BL) /* To prevent double declaration */
#error DCM_MODE_DECLARATION_SYS_BL already defined
#endif /* if (defined DCM_MODE_DECLARATION_SYS_BL) */

/** \brief Indicates, if SYS boot support and mode declaration is enabled */
#define DCM_MODE_DECLARATION_SYS_BL           STD_OFF

#if (defined DCM_COMCONTROL_LOOKUP_SIZE) /* To prevent double declaration */
#error DCM_COMCONTROL_LOOKUP_SIZE already defined
#endif /* if (defined DCM_COMCONTROL_LOOKUP_SIZE) */

/** \brief Size of array Dcm_ComControlLookUpTable[] */
#define DCM_COMCONTROL_LOOKUP_SIZE 1U

/** \brief Switch, indicating availability of timing values in positive response of 0x10 and JumpFromBL */
#define DCM_TIMING_VALUES_IN_POSITIVE_RESPONSE                      STD_OFF
#if (defined DCM_ASYNC_SERVICE_HANDLER)
#error DCM_ASYNC_SERVICE_HANDLER already defined
#endif
/** \brief Switch, indicating if Async service handler is available */
#define DCM_ASYNC_SERVICE_HANDLER                      STD_OFF
#if (defined DCM_ASYNC_DID_SERVICES)
#error DCM_ASYNC_DID_SERVICES already defined
#endif
/** \brief Switch, indicating if either of services 0x22, 0x2E or 0x2F use an Async service handler */
#define DCM_ASYNC_DID_SERVICES                      STD_OFF


#if (defined DCM_READ_DID_BLOCK_ID_CONFIGURED) /* To prevent double declaration */
#error DCM_READ_DID_BLOCK_ID_CONFIGURED already defined
#endif /* if (defined DCM_READ_DID_BLOCK_ID_CONFIGURED) */

/** \brief Indicates, if a DID is configured with read access and having signal with Data Access
 **  Interface as block-id */
#define DCM_READ_DID_BLOCK_ID_CONFIGURED           STD_OFF
#if (defined DCM_WRITE_DID_BLOCK_ID_CONFIGURED) /* To prevent double declaration */
#error DCM_WRITE_DID_BLOCK_ID_CONFIGURED already defined
#endif /* if (defined DCM_WRITE_DID_BLOCK_ID_CONFIGURED) */



/** \brief Indicates, if a DID is configured with write access and having signal with Data Access
 **  Interface as block-id */
#define DCM_WRITE_DID_BLOCK_ID_CONFIGURED           STD_OFF
#if (defined DCM_JUMP_TO_BL_ENABLED) /* To prevent double declaration */
#error DCM_JUMP_TO_BL_ENABLED already defined
#endif /* if (defined DCM_JUMP_TO_BL_ENABLED) */

/** \brief Indicates, if SYS or OEM boot support is enabled */
#define DCM_JUMP_TO_BL_ENABLED           STD_OFF
#if (defined DCM_ENDIANNESS_CONVERSION) /* To prevent double declaration */
#error DCM_ENDIANNESS_CONVERSION already defined
#endif /* if (defined DCM_ENDIANNESS_CONVERSION) */
/** \brief Indicates, if endianness conversion is enabled */
#define DCM_ENDIANNESS_CONVERSION           STD_OFF
#if (defined DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION)
#error DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION already defined
#endif
/** \brief Switch, for the optimized service handling of ReadDTCInformation(0x19),
 ** Subfunction 0x06.
 ** Handling of sub service reportDTCExtendedDataRecordByDTCNumber (0x06) of service
 ** ReadDTCInformation (0x19) is optimized if Dem provides the size of UDS Extended data record
 ** number along with the extended data bytes size (according to AUTOSAR R4.1) */
#define DCM_GET_SIZEOFEDRBYDTC_OPTIMIZATION                 STD_OFF
#if (defined DCM_RTE_TABLE_DID_SERVICES_SIZE)
#error DCM_RTE_TABLE_DID_SERVICES_SIZE already defined
#endif
/** \brief Did Services count */
#define DCM_RTE_TABLE_DID_SERVICES_SIZE   1U

#if (defined DCM_RTE_TABLE_ROUTINE_SERVICES_SIZE)
#error DCM_RTE_TABLE_ROUTINE_SERVICES_SIZE already defined
#endif
/** \brief Routine Services count */
#define DCM_RTE_TABLE_ROUTINE_SERVICES_SIZE   1U


#if (defined DCM_HSM_INST_MULTI_ENABLED)
#error DCM_HSM_INST_MULTI_ENABLED already defined
#endif
/** \brief Switch, indicating if multiple instances support is enabled */
#define DCM_HSM_INST_MULTI_ENABLED           STD_OFF
#if (defined DCM_TASK_TIME) /* To prevent double declaration */
#error DCM_TASK_TIME already defined
#endif /* if (defined DCM_TASK_TIME) */

/** \brief Definition for periodic cyclic task time in milliseconds */
#define DCM_TASK_TIME             10U


/** \brief Definition of number of channel Identifiers configured. */
#define DCM_NUM_CHANNELID 1U

#if (defined DCM_NUM_DID) /* To prevent double declaration */
#error DCM_NUM_DID already defined
#endif /* if (defined DCM_NUM_DID) */

/** \brief Number of DID configured */
#define DCM_NUM_DID             0U

#if (defined DCM_ROE_PRECONF_SUPPORT) /* To prevent double declaration */
#error DCM_ROE_PRECONF_SUPPORT already defined
#endif /* if (defined DCM_ROE_PRECONF_SUPPORT) */

/** \brief Indicates, if pre-configuration support is enabled */
#define DCM_ROE_PRECONF_SUPPORT           STD_OFF
#if (defined DCM_ROE_PRECONF_ONCHANGEOFDID_SUPPORT)       /* To prevent double declaration */
#error DCM_ROE_PRECONF_ONCHANGEOFDID_SUPPORT already defined
#endif /* if (defined DCM_ROE_PRECONF_ONCHANGEOFDID_SUPPORT) */

/** \brief Indicates, if OnChangeOfDid event is configured  **/
#define DCM_ROE_PRECONF_ONCHANGEOFDID_SUPPORT     STD_ON
#if (defined DCM_NUM_PRECONF_EVENT)
#error DCM_NUM_PRECONF_EVENT already defined
#endif /* if (defined DCM_NUM_PRECONF_EVENT) */

/** \brief Number of pre configured events */
#define DCM_NUM_PRECONF_EVENT   0U

#if (defined DCM_DSP_USE_MEMORY_ID) /* To prevent double declaration */
#error DCM_DSP_USE_MEMORY_ID already defined
#endif /* if (defined DCM_DSP_USE_MEMORY_ID) */

/** \brief Indicates presence of multiple memory devices to read/write from memory */
#define DCM_DSP_USE_MEMORY_ID             STD_OFF
#if (defined DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER)
#error DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER already defined
#endif /* if (defined DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER) */

/** \brief Indicates AddressAndLengthFormatIdentifier is configured or not */
#define DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER             STD_OFF

#if (defined DCM_NUM_MEMORY_IDINFO)
#error DCM_NUM_MEMORY_IDINFO defined
#endif /* if (defined DCM_NUM_MEMORY_IDINFO) */

/** \brief Number of MemoryIdInfos configured */
#define DCM_NUM_MEMORY_IDINFO   0U

#if (defined DCM_NUM_DID_DATA) /* To prevent double declaration */
#error DCM_NUM_DID_DATA already defined
#endif /* if (defined DCM_NUM_DID_DATA) */

/** \brief Number of DID Datas configured */
#define DCM_NUM_DID_DATA             0U

#if (defined DCM_DID_REF_COUNT) /* To prevent double declaration */
#error DCM_DID_REF_COUNT already defined
#endif /* if (defined DCM_DID_REF_COUNT) */

/** \brief Total number of references of each DID */
#define DCM_DID_REF_COUNT             0U

#if (defined DCM_READ_DID_MAX) /* To prevent double declaration */
#error DCM_READ_DID_MAX already defined
#endif /* if (defined DCM_DID_REFS) */

/** \brief Maximum number of Dids that can be requested in a single read */
#define DCM_READ_DID_MAX             1U

#if (defined DCM_DATA_MAX_SIZE) /* To prevent double declaration */
#error DCM_DATA_MAX_SIZE already defined
#endif /* if (defined DCM_DATA_MAX_SIZE) */

/** \brief Maximum size of the signal configured in bytes */
#define DCM_DATA_MAX_SIZE      0U

#if (defined DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED)
#error DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED already defined
#endif
/** \brief Switch, indicating if Service request manufacturer notification is available */
#define DCM_REQUEST_MANUFACTURER_NOTIFICATION_ENABLED       STD_OFF
#if (defined DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED)
#error DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED already defined
#endif
/** \brief Switch, indicating if Service request supplier notification is available */
#define DCM_REQUEST_SUPPLIER_NOTIFICATION_ENABLED       STD_OFF
#if (defined DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE)
#error DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE already defined
#endif
/** \brief Service request manufacturer notification count */
#define DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE   0U

#if (defined DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE)
#error DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE already defined
#endif
/** \brief Service request supplier notification count */
#define DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE   0U


/** \brief Macro to check that if common buffer is used for Rx and Tx */
#define DCM_COMMON_BUFF_CONFIGURED STD_OFF


#if (DCM_INCLUDE_RTE == STD_OFF)
/*------------------[definitions of session levels]----------------------------------------------*/
#if (defined DcmConf_DcmDspSession_DCM_DEFAULT_SESSION)
#error DcmConf_DcmDspSession_DCM_DEFAULT_SESSION already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDspSession_DCM_DEFAULT_SESSION 1U

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DCM_DEFAULT_SESSION)
#error DCM_DEFAULT_SESSION already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DCM_DEFAULT_SESSION 1U

#if (defined Dcm_DCM_DEFAULT_SESSION)
#error Dcm_DCM_DEFAULT_SESSION already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DCM_DEFAULT_SESSION 1U
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */
#if (defined DcmConf_DcmDspSession_DCM_EXTENDED_DIAGNOSTIC_SESSION)
#error DcmConf_DcmDspSession_DCM_EXTENDED_DIAGNOSTIC_SESSION already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDspSession_DCM_EXTENDED_DIAGNOSTIC_SESSION 3U

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DCM_EXTENDED_DIAGNOSTIC_SESSION)
#error DCM_EXTENDED_DIAGNOSTIC_SESSION already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DCM_EXTENDED_DIAGNOSTIC_SESSION 3U

#if (defined Dcm_DCM_EXTENDED_DIAGNOSTIC_SESSION)
#error Dcm_DCM_EXTENDED_DIAGNOSTIC_SESSION already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DCM_EXTENDED_DIAGNOSTIC_SESSION 3U
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */
#if (defined DcmConf_DcmDspSession_DCM_PROGRAMMING_SESSION)
#error DcmConf_DcmDspSession_DCM_PROGRAMMING_SESSION already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDspSession_DCM_PROGRAMMING_SESSION 2U

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DCM_PROGRAMMING_SESSION)
#error DCM_PROGRAMMING_SESSION already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DCM_PROGRAMMING_SESSION 2U

#if (defined Dcm_DCM_PROGRAMMING_SESSION)
#error Dcm_DCM_PROGRAMMING_SESSION already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DCM_PROGRAMMING_SESSION 2U
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */
#if (defined DcmConf_DcmDspSession_DCM_ALL_SESSION_LEVEL)
#error DcmConf_DcmDspSession_DCM_ALL_SESSION_LEVEL already defined
#endif
/** \brief Export symbolic name value */
#define DcmConf_DcmDspSession_DCM_ALL_SESSION_LEVEL 255U

#if (!defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined DCM_ALL_SESSION_LEVEL)
#error DCM_ALL_SESSION_LEVEL already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define DCM_ALL_SESSION_LEVEL 255U

#if (defined Dcm_DCM_ALL_SESSION_LEVEL)
#error Dcm_DCM_ALL_SESSION_LEVEL already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) **/
#define Dcm_DCM_ALL_SESSION_LEVEL 255U
#endif /* !defined DCM_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/*------------------[definitions of security levels]----------------------------------------------*/

#endif /* if (DCM_INCLUDE_RTE == STD_OFF) */

#if (defined DCM_ROE_ENABLED) /* To prevent double declaration */
#error DCM_ROE_ENABLED already defined
#endif /* if (defined DCM_ROE_ENABLED) */

/** \brief Indicates, if ROE service is enabled */
#define DCM_ROE_ENABLED           STD_OFF
#if (defined DCM_ROE_DID_BUF_SIZE) /* To prevent double declaration */
#error DCM_ROE_DID_BUF_SIZE already defined
#endif /* if (defined DCM_ROE_DID_BUF_SIZE) */

/** \brief TheSize of the buffer used to manage internally OnChangeOfDataIdentifier subservice */
#define DCM_ROE_DID_BUF_SIZE           0U
#if (defined DCM_ROE_INIT_ON_DSC) /* To prevent double declaration */
#error DCM_ROE_INIT_ON_DSC already defined
#endif /* if (defined DCM_ROE_INIT_ON_DSC) */

/** \brief If the ROE functionality is re-initialized on reception of service DiagnosticSessionControl */
#define DCM_ROE_INIT_ON_DSC           STD_OFF
#if (defined DCM_ROE_PERSISTENCE) /* To prevent double declaration */
#error DCM_ROE_PERSISTENCE already defined
#endif /* if (defined DCM_ROE_PERSISTENCE) */

/** \brief If the ROE persistence feature support is enabled */
#define DCM_ROE_PERSISTENCE           STD_OFF
#if (defined DCM_ROE_NVM_BLOCK_ID) /* To prevent double declaration */
#error DCM_ROE_NVM_BLOCK_ID already defined
#endif /* if (defined DCM_ROE_NVM_BLOCK_ID) */

/** \brief Block Id of NvM to store ROE Data for persistence */
#define DCM_ROE_NVM_BLOCK_ID           0xFFU
#if (defined DCM_ROE_QUEUE_ENABLED) /* To prevent double declaration */
#error DCM_ROE_QUEUE_ENABLED already defined
#endif /* if (defined DCM_ROE_QUEUE_ENABLED) */

/** \brief ROE transmission queue is enabled or not */
#define DCM_ROE_QUEUE_ENABLED           STD_OFF
#if (defined DCM_ROE_INTER_MSG_TIME) /* To prevent double declaration */
#error DCM_ROE_INTER_MSG_TIME already defined
#endif /* if (defined DCM_ROE_INTER_MSG_TIME) */

/** \brief The minimum time between two consecutive ROE transmissions */
#define DCM_ROE_INTER_MSG_TIME           0U
#if (defined DCM_INT_MANAGED_DIDS) /* To prevent double declaration */
#error DCM_INT_MANAGED_DIDS already defined
#endif /* if (defined DCM_INT_MANAGED_DIDS) */

#define DCM_INT_MANAGED_DIDS           STD_ON
#if (defined DCM_EXT_MANAGED_DIDS) /* To prevent double declaration */
#error DCM_EXT_MANAGED_DIDS already defined
#endif /* if (defined DCM_EXT_MANAGED_DIDS) */

#define DCM_EXT_MANAGED_DIDS           STD_OFF
/*------------------[Services configured]--------------------------------------------------------*/

#if (defined DCM_DSP_USE_SERVICE_0X3E ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X3E already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X3E) */

#define DCM_DSP_USE_SERVICE_0X3E           STD_ON
#if (defined DCM_DSP_USE_SERVICE_0X14 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X14 already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X14) */

#define DCM_DSP_USE_SERVICE_0X14           STD_ON
#if (defined DCM_DSP_USE_SERVICE_0X19 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X19 already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X19) */

#define DCM_DSP_USE_SERVICE_0X19           STD_ON
#if (defined DCM_DSP_USE_SERVICE_0X27 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X27 already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X27) */

#define DCM_DSP_USE_SERVICE_0X27           STD_OFF
#if (defined DCM_DSP_USE_SERVICE_0X10 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X10  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X10 ) */

#define DCM_DSP_USE_SERVICE_0X10           STD_ON
#if (defined DCM_DSP_USE_SERVICE_0X22 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X22  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X22 ) */

#define DCM_DSP_USE_SERVICE_0X22           STD_OFF
#if (defined DCM_0X23_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X23_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X23_SVC_ENABLED ) */

#define DCM_0X23_SVC_ENABLED           STD_OFF
#if (defined DCM_0X3D_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X3D_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X3D_SVC_ENABLED ) */

#define DCM_0X3D_SVC_ENABLED           STD_OFF
#if (defined DCM_DSP_USE_SERVICE_0X2E ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X2E  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X2E ) */

#define DCM_DSP_USE_SERVICE_0X2E           STD_OFF
#if (defined DCM_DSP_USE_SERVICE_0X2F ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X2F  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X2F ) */

#define DCM_DSP_USE_SERVICE_0X2F           STD_OFF
#if (defined DCM_DSP_USE_SERVICE_0X31 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X31  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X31 ) */

#define DCM_DSP_USE_SERVICE_0X31           STD_OFF
#if (defined DCM_DSP_USE_SERVICE_0X11 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X11  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X11 ) */

#define DCM_DSP_USE_SERVICE_0X11           STD_ON
#if (defined DCM_0X34_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X34_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X34_SVC_ENABLED ) */

#define DCM_0X34_SVC_ENABLED           STD_OFF
#if (defined DCM_0X35_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X35_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X35_SVC_ENABLED ) */

#define DCM_0X35_SVC_ENABLED           STD_OFF
#if (defined DCM_0X36_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X36_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X36_SVC_ENABLED ) */

#define DCM_0X36_SVC_ENABLED           STD_OFF
#if (defined DCM_0X37_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X37_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X37_SVC_ENABLED ) */

#define DCM_0X37_SVC_ENABLED           STD_OFF
#if (defined DCM_0X28_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X28_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X28_SVC_ENABLED ) */

#define DCM_0X28_SVC_ENABLED           STD_ON
#if (defined DCM_0X87_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X87_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X87_SVC_ENABLED ) */

#define DCM_0X87_SVC_ENABLED           STD_OFF
#if (defined DCM_DSP_USE_SERVICE_0X86 ) /* To prevent double declaration */
#error DCM_DSP_USE_SERVICE_0X86  already defined
#endif /* if (defined DCM_DSP_USE_SERVICE_0X86 ) */

#define DCM_DSP_USE_SERVICE_0X86           STD_OFF
#if (defined DCM_0X85_SVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X85_SVC_ENABLED  already defined
#endif /* if (defined DCM_0X85_SVC_ENABLED ) */

#define DCM_0X85_SVC_ENABLED           STD_ON
#if (defined DCM_EXTSVC_ENABLED ) /* To prevent double declaration */
#error DCM_EXTSVC_ENABLED  already defined
#endif /* if (defined DCM_EXTSVC_ENABLED ) */

/** \brief External handler is configured for any service or not */
#define DCM_EXTSVC_ENABLED           STD_OFF
/*------------------[Sub Services configured ]----------------------------------------------------*/

#if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x01 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x01  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x01 ) */

/** \brief Subservice 0x01 for 0x10 enabled or not */
#define DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x01           STD_ON

#if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x02 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x02  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x02 ) */

/** \brief Subservice 0x02 for 0x10 enabled or not */
#define DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x02           STD_ON

#if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x03 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x03  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x03 ) */

/** \brief Subservice 0x03 for 0x10 enabled or not */
#define DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x03           STD_ON

#if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2B ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2B  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2B ) */

/** \brief Subservice 0x2B for 0x10 enabled or not */
#define DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2B           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2C ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2C  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2C ) */

/** \brief Subservice 0x2C for 0x10 enabled or not */
#define DCM_DSP_SUBSERVICE_DIAGNOSTICSESSIONCONTROL_0x2C           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_HARDRESET_0x01 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_HARDRESET_0x01  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_HARDRESET_0x01 ) */

/** \brief Subservice 0x01 for 0x11 enabled or not */
#define DCM_DSP_SUBSERVICE_HARDRESET_0x01           STD_ON

#if (defined DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 ) */

/** \brief Subservice 0x02 for 0x11 enabled or not */
#define DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02           STD_ON

#if (defined DCM_DSP_SUBSERVICE_SOFTRESET_0x03 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_SOFTRESET_0x03  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_SOFTRESET_0x03 ) */

/** \brief Subservice 0x03 for 0x11 enabled or not */
#define DCM_DSP_SUBSERVICE_SOFTRESET_0x03           STD_ON

#if (defined DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 ) */

/** \brief Subservice 0x04 for 0x11 enabled or not */
#define DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04           STD_ON

#if (defined DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 ) */

/** \brief Subservice 0x05 for 0x11 enabled or not */
#define DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05           STD_ON

#if (defined DCM_0X28_0X00_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X28_0X00_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X28_0X00_SSVC_ENABLED ) */

/** \brief Subservice 0x00 for 0x28 enabled or not */
#define DCM_0X28_0X00_SSVC_ENABLED           STD_OFF

#if (defined DCM_0X28_0X01_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X28_0X01_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X28_0X01_SSVC_ENABLED ) */

/** \brief Subservice 0x01 for 0x28 enabled or not */
#define DCM_0X28_0X01_SSVC_ENABLED           STD_ON

#if (defined DCM_0X28_0X02_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X28_0X02_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X28_0X02_SSVC_ENABLED ) */

/** \brief Subservice 0x02 for 0x28 enabled or not */
#define DCM_0X28_0X02_SSVC_ENABLED           STD_ON

#if (defined DCM_0X28_0X03_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X28_0X03_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X28_0X03_SSVC_ENABLED ) */

/** \brief Subservice 0x03 for 0x28 enabled or not */
#define DCM_0X28_0X03_SSVC_ENABLED           STD_OFF

#if (defined DCM_0X19_0X01_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X19_0X01_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X19_0X01_SSVC_ENABLED ) */

/** \brief Subservice 0x01 for 0x19 enabled or not */
#define DCM_0X19_0X01_SSVC_ENABLED           STD_ON

#if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 ) */

/** \brief Subservice 0x02 for 0x19 enabled or not */
#define DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02           STD_ON

#if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 ) */

/** \brief Subservice 0x03 for 0x19 enabled or not */
#define DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03           STD_ON

#if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 ) */

/** \brief Subservice 0x04 for 0x19 enabled or not */
#define DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04           STD_ON

#if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 ) */

/** \brief Subservice 0x06 for 0x19 enabled or not */
#define DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06           STD_ON

#if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A ) */

/** \brief Subservice 0x0A for 0x19 enabled or not */
#define DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A           STD_ON

#if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 ) */

/** \brief Subservice 0x05 for 0x86 enabled or not */
#define DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 ) */

/** \brief Subservice 0x00 for 0x86 enabled or not */
#define DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 ) */

/** \brief Subservice 0x01 for 0x86 enabled or not */
#define DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 ) */

/** \brief Subservice 0x03 for 0x86 enabled or not */
#define DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04 ) */

/** \brief Subservice 0x04 for 0x86 enabled or not */
#define DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 ) */

/** \brief Subservice 0x06 for 0x86 enabled or not */
#define DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06           STD_OFF

#if (defined DCM_0X85_0X01_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X85_0X01_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X85_0X01_SSVC_ENABLED ) */

/** \brief Subservice 0x01 for 0x85 enabled or not */
#define DCM_0X85_0X01_SSVC_ENABLED           STD_ON

#if (defined DCM_0X85_0X02_SSVC_ENABLED ) /* To prevent double declaration */
#error DCM_0X85_0X02_SSVC_ENABLED  already defined
#endif /* if (defined DCM_0X85_0X02_SSVC_ENABLED ) */

/** \brief Subservice 0x02 for 0x85 enabled or not */
#define DCM_0X85_0X02_SSVC_ENABLED           STD_ON

#if (defined DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_LINKCONTROL_0x01  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 ) */

#define DCM_DSP_SUBSERVICE_LINKCONTROL_0x01           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_LINKCONTROL_0x02  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 ) */

#define DCM_DSP_SUBSERVICE_LINKCONTROL_0x02           STD_OFF

#if (defined DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 ) /* To prevent double declaration */
#error DCM_DSP_SUBSERVICE_LINKCONTROL_0x03  already defined
#endif /* if (defined DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 ) */

#define DCM_DSP_SUBSERVICE_LINKCONTROL_0x03           STD_OFF

#if (defined DCM_BSWM_API_ENABLED ) /* To prevent double declaration */
#error DCM_BSWM_API_ENABLED  already defined
#endif /* if defined (DCM_BSWM_API_ENABLED ) */

/** \brief BswM-Dcm interaction enabled or not */
#define DCM_BSWM_API_ENABLED           STD_ON
/*==================[type definitions]===========================================================*/

/*------------------[Dcm_ConfigType]----------------------------------------*/

/** \brief This type of the external data structure shall contain the post
 **  build initialization data for the Dcm.
 **
 ** \note Type is unused, as only pre-compile time support is implemented. */
typedef uint8 Dcm_ConfigType;

/*==================[external function declarations]=============================================*/


extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DefaultSessionModeEntry(void);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ExtendedDiagnosticSessionModeEntry(void);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ProgrammingSessionModeEntry(void);



/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Configuration structure */
extern CONST(Dcm_ConfigType, DCM_CONST) DcmConfigSet_0;

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* if !defined( DCM_CFG_H ) */
/*==================[end of file]================================================================*/
