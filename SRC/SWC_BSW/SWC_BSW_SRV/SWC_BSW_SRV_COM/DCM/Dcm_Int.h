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

#if (!defined DCM_INT_H)
#define DCM_INT_H

/*  MISRA-C:2004 Deviation List
 *
 *  MISRA-1) Deviated Rule: 19.10 (required)
 *     Parameter instance shall be enclosed in parentheses.
 *
 *     Reason:
 *     The macro is used in function parameter declarations and definitions
 *     where the number of parentheses matter.
 */

/*==================[inclusions]=================================================================*/

#include <Dcm.h>
#include <Dcm_Cfg.h>                                            /* Dcm configuration header file */

#include <ComStack_Types.h>                                            /* AUTOSAR standard types */
#include <NvM.h>

#if (DCM_DEV_ERROR_DETECT == STD_ON)
/* Development Error Tracer (DCM_DET_REPORT_ERROR() macros) */
#include <Det.h>
#endif

/*==================[macros]=====================================================================*/


#if (defined DCM_PRECONDITION_ASSERT)
#error DCM_PRECONDITION_ASSERT is already defined
#endif
#if (DCM_PRECONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define DCM_PRECONDITION_ASSERT(Condition, ApiId) \
  DET_PRECONDITION_ASSERT((Condition), DCM_MODULE_ID, DCM_INSTANCE_ID, (ApiId))
#else
#define DCM_PRECONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined DCM_POSTCONDITION_ASSERT)
#error DCM_POSTCONDITION_ASSERT is already defined
#endif
#if (DCM_POSTCONDITION_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define DCM_POSTCONDITION_ASSERT(Condition, ApiId) \
  DET_POSTCONDITION_ASSERT((Condition), DCM_MODULE_ID, DCM_INSTANCE_ID, (ApiId))
#else
#define DCM_POSTCONDITION_ASSERT(Condition, ApiId)
#endif

#if (defined DCM_INVARIANT_ASSERT)
#error DCM_INVARIANT_ASSERT is already defined
#endif
#if (DCM_INVARIANT_ASSERT_ENABLED == STD_ON)
/** \brief Report an assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated
 ** \param[in] ApiId Service ID of the API function */
#define DCM_INVARIANT_ASSERT(Condition, ApiId) \
  DET_INVARIANT_ASSERT((Condition), DCM_MODULE_ID, DCM_INSTANCE_ID, (ApiId))
#else
#define DCM_INVARIANT_ASSERT(Condition, ApiId)
#endif

#if (defined DCM_STATIC_ASSERT)
# error DCM_STATIC_ASSERT is already defined
#endif
#if (DCM_STATIC_ASSERT_ENABLED == STD_ON)
/** \brief Report an static assertion violation to Det
 **
 ** \param[in] Condition Condition which is violated */
# define DCM_STATIC_ASSERT(expr) DET_STATIC_ASSERT(expr)
#else
# define DCM_STATIC_ASSERT(expr)
#endif

#if (defined DCM_UNREACHABLE_CODE_ASSERT)
#error DCM_UNREACHABLE_CODE_ASSERT is already defined
#endif
#if (DCM_UNREACHABLE_CODE_ASSERT_ENABLED == STD_ON)
/** \brief Report an unreachable code assertion violation to Det
 **
 ** \param[in] ApiId Service ID of the API function */
#define DCM_UNREACHABLE_CODE_ASSERT(ApiId) \
  DET_UNREACHABLE_CODE_ASSERT(DCM_MODULE_ID, DCM_INSTANCE_ID, (ApiId))
#else
#define DCM_UNREACHABLE_CODE_ASSERT(ApiId)
#endif

#if !defined(DCM_DEFAULT_SESSION)

/** \brief  Definition of default session if same name is not configured in the DcmDspSessionRow.
 **
 ** If the same name is not configured this macro will be used for checking for default session in
 ** static code. */
#define DCM_DEFAULT_SESSION 1U
#endif /* if (!defined DCM_DEFAULT_SESSION) */

/** @defgroup Macro_Dcm_SecStateType Macros for Dcm_SecStateType
 ** \brief    These macro definitions are used as values for Dcm_SecStateType
 **  @{
 **/

#if (defined DCM_SEC_IDLE)
#error DCM_SEC_IDLE already defined
#endif /* if (defined DCM_SEC_IDLE) */

/** \brief Value for security state if no seed was requested yet or after key was sent. **/
#define DCM_SEC_IDLE 0x00U


#if (defined DCM_SEC_REQ_SEED)
#error DCM_SEC_REQ_SEED already defined
#endif /* if (defined DCM_SEC_REQ_SEED) */

/** \brief Value for security state after seed was requested. **/
#define DCM_SEC_REQ_SEED 0x01U

/* @} *//* End of macros definitions for Dcm_SecStateType */


#if (defined DCM_SID_TESTER_PRESENT)
#error DCM_SID_TESTER_PRESENT already defined
#endif /* if (defined DCM_SID_TESTER_PRESENT) */

/** \brief Definition of service ID of diagnostic service 'Tester Present' **/
#define DCM_SID_TESTER_PRESENT 0x3EU

#if (defined DCM_TESTER_PRESENT_REQ_LEN)
#error DCM_TESTER_PRESENT_REQ_LEN already defined
#endif /* if (defined DCM_TESTER_PRESENT_REQ_LEN) */

/** \brief Length of diagnostic service 'Tester Present' request **/
#define DCM_TESTER_PRESENT_REQ_LEN 0x02U

#if (defined DCM_SID_SESSION_CONTROL)
#error DCM_SID_SESSION_CONTROL already defined
#endif /* if (defined DCM_SID_SESSION_CONTROL) */

/** \brief Definition of service ID of diagnostic service 'Tester Present' **/
#define DCM_SID_SESSION_CONTROL 0x10U

#if (defined DCM_SID_INVALID)
#error DCM_SID_INVALID already defined
#endif /* if (defined DCM_SID_INVALID) */

/** \brief Invalid value for service ID **/
#define DCM_SID_INVALID 0x00U

#if (defined DCM_ZERO_SUBFUNCTION)
#error DCM_ZERO_SUBFUNCTION already defined
#endif /* if (defined DCM_ZERO_SUBFUNCTION) */

/** \brief Definition of a subfunction equal to 0x00 **/
#define DCM_ZERO_SUBFUNCTION 0x00U


#if (defined DCM_SUPPOSRES_BITMASK)
#error DCM_SUPPOSRES_BITMASK already defined
#endif /* if (defined DCM_SUPPOSRES_BITMASK) */

/** \brief Mask to check 'suppress positive response bit' is set in dianostic request **/
#define DCM_SUPPOSRES_BITMASK 0x80U


#if (defined DCM_CLEAR_SUPPOSRES_BIT)
#error DCM_CLEAR_SUPPOSRES_BIT already defined
#endif /* if (defined DCM_CLEAR_SUPPOSRES_BIT) */

/** \brief Definition of mask removing the 'positive response bit' **/
#define DCM_CLEAR_SUPPOSRES_BIT 0x7FU


#if (defined DCM_CLEAR_ROE_PERSISTENCE_BIT)
#error DCM_CLEAR_ROE_PERSISTENCE_BIT already defined
#endif /* if (defined DCM_CLEAR_ROE_PERSISTENCE_BIT) */

/** \brief Definition of mask removing the 'ROE persistence bit' **/
#define DCM_CLEAR_ROE_PERSISTENCE_BIT 0xBFU


#if (defined DCM_SID_RESPONSE_BIT)
#error DCM_SID_RESPONSE_BIT already defined
#endif /* if (defined DCM_SID_RESPONSE_BIT) */

/** \brief Definition of bit mask of a response ID **/
#define DCM_SID_RESPONSE_BIT 0x40U


#if (defined DCM_DIAG_REQ_SID_IND)
#error DCM_DIAG_REQ_SID_IND already defined
#endif /* if (defined DCM_DIAG_REQ_SID_IND) */

/** \brief Index corresponding to service id in diagnostic request **/
#define DCM_DIAG_REQ_SID_IND 0x00U


#if (defined DCM_DIAG_REQ_SUBFUNC_IND)
#error DCM_DIAG_REQ_SUBFUNC_IND already defined
#endif /* if (defined DCM_DIAG_REQ_SUBFUNC_IND) */

/** \brief Index corresponding to service subfunction in diagnostic request **/
#define DCM_DIAG_REQ_SUBFUNC_IND 0x01U


/** \brief Definition of DCM_INSTANCE_ID */
#define DCM_INSTANCE_ID                    0x00

/** \brief Error code for interface timeout */
#define DCM_E_INTERFACE_TIMEOUT            0x01

/** \brief Error code for interface value out of range */
#define DCM_E_INTERFACE_RETURN_VALUE       0x02

/** \brief Error code for interface buffer over flow */
#define DCM_E_INTERFACE_BUFFER_OVERFLOW    0x03

/** \brief Error code for module uninitialization */
#define DCM_E_UNINIT                       0x05

/** \brief Error code for invalid input parameter */
#define DCM_E_PARAM                        0x06

/** \brief Error code for DCM API service invoked with NULL POINTER as parameter */
#define DCM_E_PARAM_POINTER                0x07

/** \brief Error code for NvM Read operation failure */
#define DCM_E_NVM_READ_FAIL                0x08

/** \brief Error code for NvM Write operation failure */
#define DCM_E_NVM_WRITE_FAIL               0x0F

/** \brief Error code for failed write of Prog conditions */
#define DCM_E_SET_PROG_CONDITIONS_FAIL     0x09

/** \brief Error code for invalid Diagnostic Request Length */
#define DCM_E_INVALID_REQLEN               0x0A

/** \brief Error code for ReturnControlToECU when session transition to default occurs */
#define DCM_E_RETURNCONTROLTOECU_FAIL      0x0B

/** \brief Error code for ReturnControlToECU when processing Timeout occurs */
#define DCM_E_RETURNCONTROLTOECU_TIMEOUT   0x0C

/** \brief Error code for failed setting of ROE event activation status*/
#define DCM_E_ROE_ACTIVATE_EVENT_FAIL      0x10

/** \brief Error code for wrong configuration of DcmDspRoeBufSize*/
#define DCM_E_ROE_BUFFER_CONFIG_FAIL       0x0D

/** \brief Error code for failed NvM_CancelJobs() operation */
#define DCM_E_NVM_CANCEL_JOBS_FAILED       0x0E

/** \brief Invalid value for NotifResultType */
#define DCM_INVALID_NTFRSLT                0x78

/** \brief P2StarMaxTime parameter Resolution */
#define DCM_P2STARTIME_RESOLUTION             (10U)

/** \brief Byte shifting in a word */
#define DCM_BYTE_SWAPPING                     (8U)

#if (defined DCM_UDS_SID_ROE)
#error DCM_UDS_SID_ROE already defined
#endif /* if (defined DCM_UDS_SID_ROE) */

/** \brief Service Id for UDS ROE diagnostic service */
#define DCM_UDS_SID_ROE          (0x86U)

#if (defined DCM_ROE_PERSISTENCE_BIT)
#error DCM_ROE_PERSISTENCE_BIT already defined
#endif /* if (defined DCM_ROE_PERSISTENCE_BIT) */

/** \brief Definition of bit mask of a ROE Persistence bit **/
#define DCM_ROE_PERSISTENCE_BIT 0x40U

#if (defined DCM_S3SERVER_TICK_DEFAULT)
#error DCM_S3SERVER_TICK_DEFAULT already defined
#endif /* if (defined DCM_S3SERVER_TICK_DEFAULT) */

/** \brief MainFunction Tick for S3Server Timer */
#define DCM_S3SERVER_TICK_DEFAULT          (5000U/DCM_TASK_TIME)

#if (defined DCM_P2STARMIN_TICK_DEFAULT)
#error DCM_P2STARMIN_TICK_DEFAULT already defined
#endif /* if (defined DCM_P2STARMIN_TICK_DEFAULT) */

/** \brief MainFunction Tick for P2*ServerMin Timer */
#define DCM_P2STARMIN_TICK_DEFAULT         0x00

#if (defined DCM_P2MIN_TICK_DEFAULT)
#error DCM_P2MIN_TICK_DEFAULT already defined
#endif /* if (defined DCM_P2MIN_TICK_DEFAULT) */

/** \brief MainFunction Tick for P2ServerMin Timer */
#define DCM_P2MIN_TICK_DEFAULT             0x00

#if (defined DCM_PROCESS_PAGE_ID_INVALID)
#error DCM_PROCESS_PAGE_ID_INVALID already defined
#endif /* if (defined DCM_PROCESS_PAGE_ID_INVALID) */

/** \brief Invalid value for process page id */
#define DCM_PROCESS_PAGE_ID_INVALID 0xFFU

#if (defined DCM_SEC_TAB_ENTRY_IDX_LOCKED)
#error DCM_SEC_TAB_ENTRY_IDX_LOCKED already defined
#endif /* if (defined DCM_SEC_TAB_ENTRY_IDX_LOCKED) */

/** \brief Invalid value for security table id */
#define DCM_SEC_TAB_ENTRY_IDX_LOCKED 0xFFU

#if (defined DCM_PROCESS_PAGE_DTC_BY_STATUS_MASK_FUNC_ID)
#error DCM_PROCESS_PAGE_DTC_BY_STATUS_MASK_FUNC_ID already defined
#endif /* if (defined DCM_PROCESS_PAGE_DTC_BY_STATUS_MASK_FUNC_ID) */

/** \brief Invalid value for process page id */
#define DCM_PROCESS_PAGE_DTC_BY_STATUS_MASK_FUNC_ID 0x00

#if (defined DCM_PROCESS_PAGE_DTC_SNAPSHOT_RECORD)
#error DCM_PROCESS_PAGE_DTC_SNAPSHOT_RECORD already defined
#endif /* if (defined DCM_PROCESS_PAGE_DTC_SNAPSHOT_RECORD) */

/** \brief Invalid value for process page id */
#define DCM_PROCESS_PAGE_DTC_SNAPSHOT_RECORD 0x01

#if (defined DCM_PROCESS_PAGE_DTC_EXT_DATA_RECORD)
#error DCM_PROCESS_PAGE_DTC_EXT_DATA_RECORD already defined
#endif /* if (defined DCM_PROCESS_PAGE_DTC_EXT_DATA_RECORD) */

/** \brief Invalid value for process page id */
#define DCM_PROCESS_PAGE_DTC_EXT_DATA_RECORD 0x02

#if (defined DCM_PROCESS_PAGE_DTC_SNAPSHOT_IDENTIFICATION)
#error DCM_PROCESS_PAGE_DTC_SNAPSHOT_IDENTIFICATION already defined
#endif /* if (defined DCM_PROCESS_PAGE_DTC_SNAPSHOT_IDENTIFICATION) */

/** \brief Invalid value for process page id */
#define DCM_PROCESS_PAGE_DTC_SNAPSHOT_IDENTIFICATION 0x03

#if (defined DCM_DSPINTERNAL_DCMCONFIRMATION)
#error DCM_DSPINTERNAL_DCMCONFIRMATION already defined
#endif /* if (defined DCM_DSPINTERNAL_DCMCONFIRMATION) */

/** \brief Invalid value for process page id */
#define DCM_DSPINTERNAL_DCMCONFIRMATION 0x00

#if (defined DCM_HSM_DCM_EV_INVALID)
#error DCM_HSM_DCM_EV_INVALID already defined
#endif /* if (defined DCM_HSM_DCM_EV_INVALID) */

/** \brief Invalid value for state machine event */
#define DCM_HSM_DCM_EV_INVALID 0xFFU

/* Getting the number of bytes occupied by bits */
#define DCM_GET_BYTES(Bits)                 (((Bits) + 7U)/8U)
/* Getting the number of bits occupied by given bytes */
#define DCM_GET_BITS(Bytes)                 ((Bytes) * 8U)

/* Checks whether a bit in a byte is set */
#define DCM_IS_BIT_SET(Byte, BitPosition)   (((Byte) & (uint8)(0x01U << (BitPosition))) != 0U)
/* Sets the value of a bit in byte */
#define DCM_SET_BIT(Byte, BitPosition)      ((Byte) |= (uint8)(0x01U <<(BitPosition)))
/* Clears the value of a bit in byte */
#define DCM_CLEAR_BIT(Byte, BitPosition)    ((Byte) &= (uint8)(~(uint8)(0x01U << (BitPosition))))
/* ------------------[ list of AUTOSAR API service IDs ]-----------------------------------------*/
#if (defined DCM_SVCID_STARTOFRECEPTION)
#error DCM_SVCID_STARTOFRECEPTION already defined
#endif /* if (defined DCM_SVCID_STARTOFRECEPTION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_STARTOFRECEPTION.
 */
#define DCM_SVCID_STARTOFRECEPTION 0x00

#if (defined DCM_SERVID_INIT)
#error DCM_SERVID_INIT already defined
#endif /* if (defined DCM_SERVID_INIT) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_INIT.
 */
#define DCM_SERVID_INIT 0x01

#if (defined DCM_SVCID_COPYRXDATA)
#error DCM_SVCID_COPYRXDATA already defined
#endif /* if (defined DCM_SVCID_COPYRXDATA) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_COPYRXDATA.
 */
#define DCM_SVCID_COPYRXDATA 0x02

#if (defined DCM_SVCID_TPRXINDICATION)
#error DCM_SVCID_TPRXINDICATION already defined
#endif /* if (defined DCM_SVCID_TPRXINDICATION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_TPRXINDICATION.
 */
#define DCM_SVCID_TPRXINDICATION 0x03

#if (defined DCM_SVCID_COPYTXDATA)
#error DCM_SVCID_COPYTXDATA already defined
#endif /* if (defined DCM_SVCID_COPYTXDATA) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_COPYTXDATA.
 */
#define DCM_SVCID_COPYTXDATA 0x04

#if (defined DCM_SVCID_TPTXCONFIRMATION)
#error DCM_SVCID_TPTXCONFIRMATION already defined
#endif /* if (defined DCM_SVCID_TPTXCONFIRMATION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_TPTXCONFIRMATION.
 */
#define DCM_SVCID_TPTXCONFIRMATION 0x05

#if (defined DCM_SERVID_GETSESCTRLTYPE)
#error DCM_SERVID_GETSESCTRLTYPE already defined
#endif /* if (defined DCM_SERVID_GETSESCTRLTYPE) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_GETSESCTRLTYPE.
 */
#define DCM_SERVID_GETSESCTRLTYPE 0x06

#if (defined DCM_SERVID_GETSECURITYLEVEL)
#error DCM_SERVID_GETSECURITYLEVEL already defined
#endif /* if (defined DCM_SERVID_GETSECURITYLEVEL) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_GETSECURITYLEVEL.
 */
#define DCM_SERVID_GETSECURITYLEVEL 0x0D

#if (defined DCM_SERVID_GETACTIVEPROTOCOL)
#error DCM_SERVID_GETACTIVEPROTOCOL already defined
#endif /* if (defined DCM_SERVID_GETACTIVEPROTOCOL) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_GETACTIVEPROTOCOL.
 */
#define DCM_SERVID_GETACTIVEPROTOCOL 0x0F

#if (defined DCM_SERVID_COMMNOCOMMODEENTERED)
#error DCM_SERVID_COMMNOCOMMODEENTERED already defined
#endif /* if (defined DCM_SERVID_COMMNOCOMMODEENTERED) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_COMMNOCOMMODEENTERED.
 */
#define DCM_SERVID_COMMNOCOMMODEENTERED 0x21

#if (defined DCM_SERVID_COMMSILENTCOMMODEENTERED)
#error DCM_SERVID_COMMSILENTCOMMODEENTERED already defined
#endif /* if (defined DCM_SERVID_COMMSILENTCOMMODEENTERED) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_COMMSILENTCOMMODEENTERED.
 */
#define DCM_SERVID_COMMSILENTCOMMODEENTERED 0x22

#if (defined DCM_SERVID_COMMFULLCOMMODEENTERED)
#error DCM_SERVID_COMMFULLCOMMODEENTERED already defined
#endif /* if (defined DCM_SERVID_COMMFULLCOMMODEENTERED) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_COMMFULLCOMMODEENTERED.
 */
#define DCM_SERVID_COMMFULLCOMMODEENTERED 0x23

#if (defined DCM_SERVID_GETVERSIONINFO)
#error DCM_SERVID_GETVERSIONINFO already defined
#endif /* if (defined DCM_SERVID_GETVERSIONINFO) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_GETVERSIONINFO.
 */
#define DCM_SERVID_GETVERSIONINFO 0x24

#if (defined DCM_SERVID_MAINFUNCTION)
#error DCM_SERVID_MAINFUNCTION already defined
#endif /* if (defined DCM_SERVID_MAINFUNCTION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_MAINFUNCTION.
 */
#define DCM_SERVID_MAINFUNCTION 0x25

#if (defined DCM_SVCID_READMEMORY)
#error DCM_SVCID_READMEMORY already defined
#endif /* if (defined DCM_SVCID_READMEMORY) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_READMEMORY.
 */
#define DCM_SVCID_READMEMORY 0x26

#if (defined DCM_SVCID_WRITEMEMORY)
#error DCM_SVCID_WRITEMEMORY already defined
#endif /* if (defined DCM_SVCID_WRITEMEMORY) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_WRITEMEMORY.
 */
#define DCM_SVCID_WRITEMEMORY 0x27

#if (defined DCM_SERVID_DSL_RESPONSEONONEEVENT)
#error DCM_SERVID_DSL_RESPONSEONONEEVENT already defined
#endif /* if (defined DCM_SERVID_DSL_RESPONSEONONEEVENT) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DSL_RESPONSEONONEEVENT.
 */
#define DCM_SERVID_DSL_RESPONSEONONEEVENT 0x28

#if (defined DCM_SERVID_RESETTODEFAULTSESSION)
#error DCM_SERVID_RESETTODEFAULTSESSION already defined
#endif /* if (defined DCM_SERVID_RESETTODEFAULTSESSION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_RESETTODEFAULTSESSION.
 */
#define DCM_SERVID_RESETTODEFAULTSESSION 0x2A

#if (defined DCM_SERVID_DEMTRIGGERONDTC)
#error DCM_SERVID_DEMTRIGGERONDTC already defined
#endif /* if (defined DCM_SERVID_DEMTRIGGERONDTC) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DEMTRIGGERONDTC.
 */
#define DCM_SERVID_DEMTRIGGERONDTC 0x2B

#if (defined DCM_SERVID_TRIGGERONEVENT)
#error DCM_SERVID_TRIGGERONEVENT already defined
#endif /* if (defined DCM_SERVID_TRIGGERONEVENT) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_TRIGGERONEVENT.
 */
#define DCM_SERVID_TRIGGERONEVENT 0x2D

#if (defined DCM_SVCID_REQUESTDOWNLOAD)
#error DCM_SVCID_REQUESTDOWNLOAD already defined
#endif /* if (defined DCM_SVCID_REQUESTDOWNLOAD) */
/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_REQUESTDOWNLOAD.
 */
#define DCM_SVCID_REQUESTDOWNLOAD 0x30

#if (defined DCM_SVCID_REQUESTUPLOAD)
#error DCM_SVCID_REQUESTUPLOAD already defined
#endif /* if (defined DCM_SVCID_REQUESTUPLOAD) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_REQUESTUPLOAD.
 */
#define DCM_SVCID_REQUESTUPLOAD 0x31

#if (defined DCM_SVCID_REQUESTTRANSFEREXIT)
#error DCM_SVCID_REQUESTTRANSFEREXIT already defined
#endif /* if (defined DCM_SVCID_REQUESTTRANSFEREXIT) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_REQUESTTRANSFEREXIT.
 */
#define DCM_SVCID_REQUESTTRANSFEREXIT 0x32

#if (defined DCM_SVCID_READDATALENGTH)
#error DCM_SVCID_READDATALENGTH already defined
#endif /* if (defined DCM_SVCID_READDATALENGTH) */

/** \brief Dsp interface API service ID.
 **
 ** Definition of DCM_SVCID_READDATALENGTH.
 */
#define DCM_SVCID_READDATALENGTH 0x36

#if (defined DCM_SVCID_CONDITIONCHECKREAD_ASYNC)
#error DCM_SVCID_CONDITIONCHECKREAD_ASYNC already defined
#endif /* if (defined DCM_SVCID_CONDITIONCHECKREAD_ASYNC) */

/** \brief Dsp interface API service ID.
 **
 ** Definition of DCM_SVCID_CONDITIONCHECKREAD_ASYNC.
 */
#define DCM_SVCID_CONDITIONCHECKREAD_ASYNC 0x37

#if (defined DCM_SVCID_RETURNCONTROLTOECU)
#error DCM_SVCID_RETURNCONTROLTOECU already defined
#endif /* if (defined DCM_SVCID_RETURNCONTROLTOECU) */

/** \brief Dsp interface API service ID.
 **
 ** Definition of DCM_SVCID_RETURNCONTROLTOECU.
 */
#define DCM_SVCID_RETURNCONTROLTOECU 0x39

#if (defined DCM_SVCID_RESETTODEFAULT)
#error DCM_SVCID_RESETTODEFAULT already defined
#endif /* if (defined DCM_SVCID_RESETTODEFAULT) */

/** \brief Dsp interface API service ID.
 **
 ** Definition of DCM_SVCID_RESETTODEFAULT.
 */
#define DCM_SVCID_RESETTODEFAULT 0x3C

#if (defined DCM_SVCID_FREEZECURRENTSTATE)
#error DCM_SVCID_FREEZECURRENTSTATE already defined
#endif /* if (defined DCM_SVCID_FREEZECURRENTSTATE) */

/** \brief Dsp interface API service ID.
 **
 ** Definition of DCM_SVCID_FREEZECURRENTSTATE.
 */
#define DCM_SVCID_FREEZECURRENTSTATE 0x3A

#if (defined DCM_SVCID_SHORTTERMADJUSTMENT)
#error DCM_SVCID_SHORTTERMADJUSTMENT already defined
#endif /* if (defined DCM_SVCID_SHORTTERMADJUSTMENT) */

/** \brief Dsp interface API service ID.
 **
 ** Definition of DCM_SVCID_SHORTTERMADJUSTMENT.
 */
#define DCM_SVCID_SHORTTERMADJUSTMENT 0x3D

#if (defined DCM_SERVID_DSP_DCMCONFIRMATION)
#error DCM_SERVID_DSP_DCMCONFIRMATION already defined
#endif /* if (defined DCM_SERVID_DSP_DCMCONFIRMATION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DSP_DCMCONFIRMATION.
 */
#define DCM_SERVID_DSP_DCMCONFIRMATION 0x42

#if (defined DCM_SERVID_PROCESSINGDONE)
#error DCM_SERVID_PROCESSINGDONE already defined
#endif /* if (defined DCM_SERVID_PROCESSINGDONE) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_PROCESSINGDONE.
 */
#define DCM_SERVID_PROCESSINGDONE 0x43

#if (defined DCM_SERVID_SETNEGRESPONSE)
#error DCM_SERVID_SETNEGRESPONSE already defined
#endif /* if (defined DCM_SERVID_SETNEGRESPONSE) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_SETNEGRESPONSE.
 */
#define DCM_SERVID_SETNEGRESPONSE 0x44

#if (defined DCM_SERVID_DSD_STARTPAGEDPROCESSING)
#error DCM_SERVID_DSD_STARTPAGEDPROCESSING already defined
#endif /* if (defined DCM_SERVID_DSD_STARTPAGEDPROCESSING) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DSD_STARTPAGEDPROCESSING.
 */
#define DCM_SERVID_DSD_STARTPAGEDPROCESSING 0x45

#if (defined DCM_SERVID_DSD_MANUFACTURERNOTIFICATION)
#error DCM_SERVID_DSD_MANUFACTURERNOTIFICATION already defined
#endif /* if (defined DCM_SERVID_DSD_MANUFACTURERNOTIFICATION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DSD_MANUFACTURERNOTIFICATION.
 */
#define DCM_SERVID_DSD_MANUFACTURERNOTIFICATION 0x46

#if (defined DCM_SERVID_DSD_SUPPLIERNOTIFICATION)
#error DCM_SERVID_DSD_SUPPLIERNOTIFICATION already defined
#endif /* if (defined DCM_SERVID_DSD_SUPPLIERNOTIFICATION) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DSD_SUPPLIERNOTIFICATION.
 */
#define DCM_SERVID_DSD_SUPPLIERNOTIFICATION 0x47

#if (defined DCM_SVCID_DTCSETTINGON)
#error DCM_SVCID_DTCSETTINGON already defined
#endif /* if (defined DCM_SVCID_DTCSETTINGON) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_DTCSETTINGON.
 */
#define DCM_SVCID_DTCSETTINGON 0x48

#if (defined DCM_SVCID_DTCSETTINGOFF)
#error DCM_SVCID_DTCSETTINGOFF already defined
#endif /* if (defined DCM_SVCID_DTCSETTINGOFF) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_DTCSETTINGOFF.
 */
#define DCM_SVCID_DTCSETTINGOFF 0x49

#if (defined DCM_SVCID_SETPROGCONDITIONS)
#error DCM_SVCID_SETPROGCONDITIONS already defined
#endif /* if (defined DCM_SVCID_SETPROGCONDITIONS) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_SETPROGCONDITIONS.
 */
#define DCM_SVCID_SETPROGCONDITIONS 0x4a

#if (defined DCM_SVCID_GETPROGCONDITIONS)
#error DCM_SVCID_GETPROGCONDITIONS already defined
#endif /* if (defined DCM_SVCID_GETPROGCONDITIONS) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_GETPROGCONDITIONS.
 */
#define DCM_SVCID_GETPROGCONDITIONS 0x4b

#if (defined DCM_SVCID_LINKCONTROL)
#error DCM_SVCID_LINKCONTROL already defined
#endif /* if (defined DCM_SVCID_LINKCONTROL) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_LINKCONTROL.
 */
#define DCM_SVCID_LINKCONTROL 0x4c

#if (defined DCM_SVCID_CLEARDTC)
#error DCM_SVCID_CLEARDTC already defined
#endif /* if (defined DCM_SVCID_CLEARDTC) */

/** \brief ClearDTC Rte interface service ID.
 **
 ** Definition of DCM_SVCID_CLEARDTC.
 */
#define DCM_SVCID_CLEARDTC 0x60

#if (defined DCM_SVCID_GETFREEZEFRAMEDATABYDTC)
#error DCM_SVCID_GETFREEZEFRAMEDATABYDTC already defined
#endif /* if (defined DCM_SVCID_GETFREEZEFRAMEDATABYDTC) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_GETFREEZEFRAMEDATABYDTC.
 */
#define DCM_SVCID_GETFREEZEFRAMEDATABYDTC 0x70

#if (defined DCM_SVCID_GETEXTENDEDDATABYDTC)
#error DCM_SVCID_GETEXTENDEDDATABYDTC already defined
#endif /* if (defined DCM_SVCID_GETEXTENDEDDATABYDTC) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_GETEXTENDEDDATABYDTC.
 */
#define DCM_SVCID_GETEXTENDEDDATABYDTC 0x71

#if (defined DCM_SVCID_ENABLEDTCRECORDUPDATE)
#error DCM_SVCID_ENABLEDTCRECORDUPDATE already defined
#endif /* if (defined DCM_SVCID_ENABLEDTCRECORDUPDATE) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SVCID_ENABLEDTCRECORDUPDATE.
 */
#define DCM_SVCID_ENABLEDTCRECORDUPDATE 0x72

#if (defined DCM_SVCID_DISABLEDTCRECORDUPDATE)
#error DCM_SVCID_DISABLEDTCRECORDUPDATE already defined
#endif /* if (defined DCM_SVCID_DISABLEDTCRECORDUPDATE) */

/** \brief Dem_DisableDTCRecordUpdate() DEM interface service ID.
 **
 ** Definition of DCM_SVCID_DISABLEDTCRECORDUPDATE.
 */
#define DCM_SVCID_DISABLEDTCRECORDUPDATE 0x73

#if (defined DCM_SVCID_ACTIVATEEVENT)
#error DCM_SVCID_ACTIVATEEVENT already defined
#endif /* if (defined DCM_SVCID_ACTIVATEEVENT) */

/** \brief ROE ActivateEvent Rte interface service ID.
 **
 ** Definition of DCM_SVCID_ACTIVATEEVENT.
 */
#define DCM_SVCID_ACTIVATEEVENT 0x74

#if (defined DCM_SERVID_DSD_PROCESSPAGE)
#error DCM_SERVID_DSD_PROCESSPAGE already defined
#endif /* if (defined DCM_SERVID_DSD_PROCESSPAGE) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DSD_PROCESSPAGE.
 */
#define DCM_SERVID_DSD_PROCESSPAGE 0x69

#if (defined DCM_SERVID_DSD_UPDATEPAGE)
#error DCM_SERVID_DSD_UPDATEPAGE already defined
#endif /* if (defined DCM_SERVID_DSD_UPDATEPAGE) */

/** \brief AUTOSAR API service ID.
 **
 ** Definition of DCM_SERVID_DSD_UPDATEPAGE.
 */
#define DCM_SERVID_DSD_UPDATEPAGE 0x6A

#if (defined DCM_SVCID_PROCESSSERVICEASYNC)
#error DCM_SVCID_PROCESSSERVICEASYNC already defined
#endif /* if (defined DCM_SVCID_PROCESSSERVICEASYNC) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_PROCESSSERVICEASYNC.
 */
#define DCM_SVCID_PROCESSSERVICEASYNC 0x73

#if (defined DCM_SVCID_ROEONCHANGEOFDID)
#error DCM_SVCID_ROEONCHANGEOFDID already defined
#endif /* if (defined DCM_SVCID_ROEONCHANGEOFDID) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_ROEONCHANGEOFDID.
 */
#define DCM_SVCID_ROEONCHANGEOFDID 0x75



#if (defined DCM_SVCID_NVMWRITEDATA)
#error DCM_SVCID_NVMWRITEDATA already defined
#endif /* if (defined DCM_SVCID_NVMWRITEDATA) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_NVMWRITEDATA.
 */
#define DCM_SVCID_NVMWRITEDATA 0x76


#if (defined DCM_SVCID_NVMREADDATA)
#error DCM_SVCID_NVMREADDATA already defined
#endif /* if (defined DCM_SVCID_NVMREADDATA) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_NVMREADDATA.
 */
#define DCM_SVCID_NVMREADDATA 0x77


#if (defined DCM_SVCID_NVMREADBLOCK)
#error DCM_SVCID_NVMREADBLOCK already defined
#endif /* if (defined DCM_SVCID_NVMREADBLOCK) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_NVMREADBLOCK.
 */
#define DCM_SVCID_NVMREADBLOCK 0x78


#if (defined DCM_SVCID_NVMWRITEBLOCK)
#error DCM_SVCID_NVMWRITEBLOCK already defined
#endif /* if (defined DCM_SVCID_NVMWRITEBLOCK) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_NVMWRITEBLOCK.
 */
#define DCM_SVCID_NVMWRITEBLOCK 0x79


#if (defined DCM_SVCID_NVMCANCELJOBS)
#error DCM_SVCID_NVMCANCELJOBS already defined
#endif /* if (defined DCM_SVCID_NVMCANCELJOBS) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_NVMCANCELJOBS.
 */
#define DCM_SVCID_NVMCANCELJOBS 0x7A


#if (defined DCM_SVCID_NVMGETERRORSTATUS)
#error DCM_SVCID_NVMGETERRORSTATUS already defined
#endif /* if (defined DCM_SVCID_NVMGETERRORSTATUS) */

/** \brief Internal API service ID.
 **
 ** Definition of DCM_SVCID_NVMGETERRORSTATUS.
 */
#define DCM_SVCID_NVMGETERRORSTATUS 0x7B


#if (defined DCM_NUM_DSP_SERVICES)
#error DCM_NUM_DSP_SERVICES already defined
#endif

/* Number of services implemented in Dsp part of Dcm module */
#define DCM_NUM_DSP_SERVICES  5U

/** \brief DCM_DET_REPORT_ERROR() determines whether errors are detected
 **
 ** In development mode, this macro evaluates to its parameter, which is a boolean value with
 ** TRUE indicating an error.
 **
 ** In production mode this macro always evaluates to 0, thus disabling error detection.
*/
#if (DCM_DEV_ERROR_DETECT == STD_ON)
#define DCM_DET_REPORT_ERROR(ServiceId,ErrorCode)                       \
  ((void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID, (ServiceId), (ErrorCode)))
#endif /* DCM_DEV_ERROR_DETECT == STD_ON */

#if (defined DCM_DTC_AND_STATUS_SNGL_RCD_LEN)
#error DCM_DTC_AND_STATUS_SNGL_RCD_LEN already defined
#endif /* if (defined DCM_DTC_AND_STATUS_SNGL_RCD_LEN) */

/** \brief Definition of length of single DTC and Status record in response
     message of Service 0x19 - Subfunction 0x02(Report DTC by status mask) **/
#define DCM_DTC_AND_STATUS_SNGL_RCD_LEN (0x04U)

#if (defined DCM_DTC_SNAPSHOT_SNGL_RCD_LEN)
#error DCM_DTC_SNAPSHOT_RECORD_SNGL_RCD_LEN already defined
#endif /* if (defined DCM_DTC_SNAPSHOT_SNGL_RCD_LEN) */

/** \brief Definition of length of single DTC Snapshot record in response
     message of Service 0x19 - Subfunction 0x03(Report DTC Snapshot Record Identification) **/
#define DCM_DTC_SNAPSHOT_SNGL_RCD_LEN (0x04U)

#if (defined DCM_DTC_EXT_RECORD_NUM_LEN)
#error DCM_DTC_EXT_RECORD_NUM_LEN already defined
#endif /* if (defined DCM_DTC_EXT_RECORD_NUM_LEN) */

/** \brief Definition of length of DTC Extended record number **/
#define DCM_DTC_EXT_RECORD_NUM_LEN (0x01U)

#if (defined DCM_NUM_STD_SERVICES)
#error DCM_NUM_STD_SERVICES already defined
#endif /* if (defined DCM_NUM_STD_SERVICES) */

/** \brief Definition of number of DCM services which do not
     access RTE interface  **/
#define DCM_NUM_STD_SERVICES (0x02U)

#if (defined DCM_SID_ECU_RESET)
#error DCM_SID_ECU_RESET already defined
#endif /* if (defined DCM_SID_ECU_RESET) */

/** \brief Definition of service id of Ecu Reset service  **/
#define DCM_SID_ECU_RESET (0x11U)

#if (defined DCM_SID_READ_DTC_INFORMATION)
#error DCM_SID_READ_DTC_INFORMATION already defined
#endif /* if (defined DCM_SID_READ_DTC_INFORMATION) */

/** \brief Definition of service id of ReadDTCInformation  **/
#define DCM_SID_READ_DTC_INFORMATION (0x19U)

#if (defined DCM_SID_CLR_DIAG_INFORMATION)
#error DCM_SID_CLR_DIAG_INFORMATION already defined
#endif /* if (defined DCM_SID_CLR_DIAG_INFORMATION) */

/** \brief Definition of service id of ClearDiagnosticInformation  **/
#define DCM_SID_CLR_DIAG_INFORMATION (0x14U)

#if (defined DCM_SID_DCM_CONFIRMATION)
#error DCM_SID_DCM_CONFIRMATION already defined
#endif /* if (defined DCM_SID_CLR_DIAG_INFORMATION) */

/** \brief Definition of service id of Dcm_Confirmation callout  **/
#define DCM_SID_DCM_CONFIRMATION (0x29U)

#if (defined DCM_INVALID_SESSION)
#error DCM_INVALID_SESSION already defined
#endif/* #if (defined DCM_INVALID_SESSION) */

/** \brief Invalid value for Diagnostics Session entered  **/
#define DCM_INVALID_SESSION 0U

#if (defined DCM_FUNCTIONAL_TYPE)
#error DCM_FUNCTIONAL_TYPE already defined
#endif /* if (defined DCM_FUNCTIONAL_TYPE) */

/** \brief Definition of value for functional request **/
#define DCM_FUNCTIONAL_TYPE 1U


#if (defined DCM_PHYSICAL_TYPE)
#error DCM_PHYSICAL_TYPE already defined
#endif /* if (defined DCM_PHYSICAL_TYPE) */

 /** \brief Definition of value for physical request **/
#define DCM_PHYSICAL_TYPE   0U


#if (defined DCM_SES_LVL_NON_DEF)
#error DCM_SES_LVL_NON_DEF already defined
#endif /* if (defined DCM_SES_LVL_NON_DEF) */

/** \brief Value for a non-default session level **/
#define DCM_SES_LVL_NON_DEF 0x00U


#if (defined DCM_SEC_SEND_KEY)
#error DCM_SEC_SEND_KEY already defined
#endif /* if (defined DCM_SEC_COMP_KEY) */

/** \brief Value for security state if no seed was requested yet or after key
 ** was sent. **/
#define DCM_SEC_SEND_KEY 0x00U
#if (defined DCM_DID_DMC_LOW_LIMIT)
#error DCM_DID_DMC_LOW_LIMIT already defined
#endif /* if (defined DCM_DID_DMC_LOW_LIMIT) */

/** \brief Dynamic Did lower limit **/
#define DCM_DID_DMC_LOW_LIMIT (0xF200U)


#if (defined DCM_DID_DMC_UP_LIMIT)
#error DCM_DID_DMC_UP_LIMIT already defined
#endif /* if (defined DCM_DID_DMC_UP_LIMIT) */

/** \brief Dynamic Did upper limit **/
#define DCM_DID_DMC_UP_LIMIT (0xF3FFU)


#if (defined DCM_DID_OBD_LOW_LIMIT)
#error DCM_DID_OBD_LOW_LIMIT already defined
#endif /* if (defined DCM_DID_OBD_LOW_LIMIT) */

/** \brief OBD Did lower limit **/
#define DCM_DID_OBD_LOW_LIMIT (0xF400U)


#if (defined DCM_DID_OBD_UP_LIMIT)
#error DCM_DID_OBD_UP_LIMIT already defined
#endif /* if (defined DCM_DID_OBD_RANGE2) */

/** \brief OBD Did upper limit **/
#define DCM_DID_OBD_UP_LIMIT (0xF8FFU)


#if (defined DCM_DID_STD_RW_LOW_LIMIT)
#error DCM_DID_STD_RW_LOW_LIMIT already defined
#endif /* if (defined DCM_DID_STD_RW_LOW_LIMIT) */

/** \brief Standard Read/Write Did lower limit **/
#define DCM_DID_STD_RW_LOW_LIMIT (0x00FFU)


#if (defined DCM_DID_STD_RW_UP_LIMIT)
#error DCM_DID_STD_RW_UP_LIMIT already defined
#endif /* if (defined DCM_DID_STD_RW_UP_LIMIT) */

/** \brief Standard Read/Write Did upper limit **/
#define DCM_DID_STD_RW_UP_LIMIT (0xF1FFU)


#if (defined DCM_DID_STD_READ_LOW_LIMIT)
#error DCM_DID_STD_READ_LOW_LIMIT already defined
#endif /* if (defined DCM_DID_STD_READ_LOW_LIMIT) */

/** \brief Standard read only Did lower limit **/
#define DCM_DID_STD_READ_LOW_LIMIT (0xF900U)


#if (defined DCM_DID_STD_READ_UP_LIMIT)
#error DCM_DID_STD_READ_UP_LIMIT already defined
#endif /* if (defined DCM_DID_STD_READ_UP_LIMIT) */

/** \brief Standard read only Did upper limit **/
#define DCM_DID_STD_READ_UP_LIMIT (0xFEFFU)

#if (defined DCM_DID_SUP_LOW_LIMIT)
#error DCM_DID_SUP_LOW_LIMIT already defined
#endif /* if (defined DCM_DID_SUP_LOW_LIMIT) */
/** \brief System Supplier Specific Did lower limit **/
#define DCM_DID_SUP_LOW_LIMIT (0xFD00U)

#if (defined DCM_DID_SUP_UP_LIMIT)
#error DCM_DID_SUP_UP_LIMIT already defined
#endif /* if (defined DCM_DID_SUP_UP_LIMIT) */
/** \brief System Supplier Specific Did upper limit **/
#define DCM_DID_SUP_UP_LIMIT (0xFEFFU)

#if (defined DCM_DID_ID_SIZE)
#error DCM_DID_ID_SIZE already defined
#endif /* if (defined DCM_DID_ID_SIZE) */

/** \brief Length of DID Identifier in bytes **/
#define DCM_DID_ID_SIZE 0x02U

/** \brief Specifies the status of a routine  **/
#if (defined DCM_ROUTINE_INACTIVE)
#error DCM_ROUTINE_INACTIVE already defined
#endif/* #if (defined DCM_ROUTINE_INACTIVE) */
#define DCM_ROUTINE_INACTIVE 0x0U

#if (defined DCM_ROUTINE_STARTED)
#error DCM_ROUTINE_STARTED already defined
#endif/* #if (defined DCM_ROUTINE_STARTED) */
#define DCM_ROUTINE_STARTED  0x1U

#if (defined DCM_ROUTINE_STOPPED)
#error DCM_ROUTINE_STOPPED already defined
#endif/* #if (defined DCM_ROUTINE_STOPPED) */
#define DCM_ROUTINE_STOPPED  0x2U

#if (defined DCM_MESSAGE_TYPE_MASK)
#error DCM_MESSAGE_TYPE_MASK already defined
#endif/* #if (defined DCM_MESSAGE_TYPE_MASK) */

/** \brief Mask to get the Message type from 'CommunicationType' parameter  **/
#define DCM_MESSAGE_TYPE_MASK 0x03U


#if (defined DCM_SUBNET_NUMBER_MASK)
#error DCM_SUBNET_NUMBER_MASK already defined
#endif/* #if (defined DCM_SUBNET_NUMBER_MASK) */

/** \brief Mask to get the subnet number from 'CommunicationType' parameter  **/
#define DCM_SUBNET_NUMBER_MASK 0xF0U

#if (defined DCM_0X28_COMM_MODE_INVALID)
#error DCM_0X28_COMM_MODE_INVALID already defined
#endif/* #if (defined DCM_0X28_COMM_MODE_INVALID) */

/** \brief Invalid value for the Communication mode requested  **/
#define DCM_0X28_COMM_MODE_INVALID 0xFFU

#if (DCM_ROE_ENABLED == STD_ON)
#if (defined DCM_ROE_START)
#error DCM_ROE_START already defined
#endif/* #if (defined DCM_ROE_START) */

/** \brief Event Type startResponseOnEvent for ResponseOnEvent Service  **/
#define DCM_ROE_START 0x05U

#if (defined DCM_ROE_STOP)
#error DCM_ROE_STOP already defined
#endif/* #if (defined DCM_ROE_STOP) */

/** \brief Event Type stopResponseOnEvent for ResponseOnEvent Service  **/
#define DCM_ROE_STOP 0x00U

#if (defined DCM_ROE_ONDTC_STATUS_CHANGE)
#error DCM_ROE_ONDTC_STATUS_CHANGE already defined
#endif/* #if (defined DCM_ROE_ONDTC_STATUS_CHANGE) */

/** \brief Event Type onDTCStatusChange for ResponseOnEvent Service  **/
#define DCM_ROE_ONDTC_STATUS_CHANGE 0x01U

#if (defined DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER)
#error DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER already defined
#endif/* #if (defined DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER) */

/** \brief Event Type onChangeOfDataIdentifier for ResponseOnEvent Service  **/
#define DCM_ROE_ONCHANGE_OF_DATA_IDENTIFIER 0x03U

#if (defined DCM_ROE_ONDTC_STATUS_CHANGE_RES_LEN)
#error DCM_ROE_ONDTC_STATUS_CHANGE_RES_LEN already defined
#endif/* #if (defined DCM_ROE_ONDTC_STATUS_CHANGE_RES_LEN) */

/** \brief Response Length of Event Type onDTCStatusChange for ResponseOnEvent Service  **/
#define DCM_ROE_ONDTC_STATUS_CHANGE_RES_LEN 0x08U

#if (defined DCM_ROE_ON_CHANGE_DID_RES_LEN)
#error DCM_ROE_ON_CHANGE_DID_RES_LEN already defined
#endif/* #if (defined DCM_ROE_ON_CHANGE_DID_RES_LEN) */

/** \brief Response Length of Event Type onChangeOfDataIdentifier for ResponseOnEvent Service  **/
#define DCM_ROE_ON_CHANGE_DID_RES_LEN 0x09U

#if (defined DCM_ROE_REPORT_ACTIVATED_EVENTS)
#error DCM_ROE_REPORT_ACTIVATED_EVENTS already defined
#endif/* #if (defined DCM_ROE_REPORT_ACTIVATED_EVENTS) */

/** \brief Event Type reportActivatedEvents for ResponseOnEvent Service  **/
#define DCM_ROE_REPORT_ACTIVATED_EVENTS 0x04U

#if (defined DCM_ROE_CLEAR)
#error DCM_ROE_CLEAR already defined
#endif/* #if (defined DCM_ROE_CLEAR) */

/** \brief Event Type clearResponseOnEvent for ResponseOnEvent Service  **/
#define DCM_ROE_CLEAR 0x06U

#if (defined DCM_ROE_SUBFUNCTION_0x03_IDX)
#error DCM_ROE_SUBFUNCTION_0x03_IDX already defined
#endif/* #if (defined DCM_ROE_SUBFUNCTION_0x03_IDX) */

/** \brief The index value for accessing the information of ROE subfunction 0x03  **/
#define DCM_ROE_SUBFUNCTION_0x03_IDX 0x01U

#if (defined DCM_ROE_SUBFUNCTION_0x01_IDX)
#error DCM_ROE_SUBFUNCTION_0x01_IDX already defined
#endif/* #if (defined DCM_ROE_SUBFUNCTION_0x01_IDX) */

/** \brief The index value for accessing the information of ROE subfunction 0x01  **/
#define DCM_ROE_SUBFUNCTION_0x01_IDX 0x00U

#if (defined DCM_ROE_INVALID_FINAL_RES)
#error DCM_ROE_INVALID_FINAL_RES already defined
#endif/* #if (defined DCM_ROE_INVALID_FINAL_RES) */

/** \brief Value for invalid final ROE response **/
#define DCM_ROE_INVALID_FINAL_RES 0x00U

#if (defined DCM_ROE_EVENTTYPE_IDX)
#error DCM_ROE_EVENTTYPE_IDX already defined
#endif/* #if (defined DCM_ROE_EVENTTYPE_IDX) */

/** \brief index value for accessing info of ROE EventType from Dcm_RoeData **/
#define DCM_ROE_EVENTTYPE_IDX 0x00U

#if (defined DCM_ROE_EVENTWINDOWTIME_IDX)
#error DCM_ROE_EVENTWINDOWTIME_IDX already defined
#endif/* #if (defined DCM_ROE_EVENTWINDOWTIME_IDX) */

/** \brief index value for accessing info of ROE eventWindowTime from Dcm_RoeData **/
#define DCM_ROE_EVENTWINDOWTIME_IDX 0x01U

#if (defined DCM_ROE_EVENTTYPERECORD0_0x03_IDX)
#error DCM_ROE_EVENTTYPERECORD0_0x03_IDX already defined
#endif/* #if (defined DCM_ROE_EVENTTYPERECORD0_0x03_IDX) */

/** \brief index value for accessing info of EventTypeRecord[0] of 0x03 event from Dcm_RoeData **/
#define DCM_ROE_EVENTTYPERECORD0_0x03_IDX 0x02U

#if (defined DCM_ROE_EVENTTYPERECORD1_0x03_IDX)
#error DCM_ROE_EVENTTYPERECORD1_0x03_IDX already defined
#endif/* #if (defined DCM_ROE_EVENTTYPERECORD1_0x03_IDX) */

/** \brief index value for accessing info of EventTypeRecord[1] of 0x03 event from Dcm_RoeData **/
#define DCM_ROE_EVENTTYPERECORD1_0x03_IDX 0x03U

#if (defined DCM_ROE_EVENTTYPERECORD0_0x01_IDX)
#error DCM_ROE_EVENTTYPERECORD0_0x01_IDX already defined
#endif/* #if (defined DCM_ROE_EVENTTYPERECORD0_0x01_IDX) */

/** \brief index value for accessing info of EventTypeRecord[0] of 0x01 event from Dcm_RoeData **/
#define DCM_ROE_EVENTTYPERECORD0_0x01_IDX 0x02U

#if (defined DCM_ROE_SERVICETORESPOND0_0x01_IDX)
#error DCM_ROE_SERVICETORESPOND0_0x01_IDX already defined
#endif/* #if (defined DCM_ROE_SERVICETORESPOND0_0x01_IDX) */

/** \brief index value for accessing info of ServiceToRespond[0] of 0x01 event from Dcm_RoeData **/
#define DCM_ROE_SERVICETORESPOND0_0x01_IDX 0x03U

#if (defined DCM_ROE_SERVICETORESPOND1_0x01_IDX)
#error DCM_ROE_SERVICETORESPOND1_0x01_IDX already defined
#endif/* #if (defined DCM_ROE_SERVICETORESPOND1_0x01_IDX) */

/** \brief index value for accessing info of ServiceToRespond[1] of 0x01 event from Dcm_RoeData **/
#define DCM_ROE_SERVICETORESPOND1_0x01_IDX 0x04U

#if (defined DCM_ROE_SERVICETORESPOND2_0x01_IDX)
#error DCM_ROE_SERVICETORESPOND2_0x01_IDX already defined
#endif/* #if (defined DCM_ROE_SERVICETORESPOND2_0x01_IDX) */

/** \brief index value for accessing info of ServiceToRespond[2] of 0x01 event from Dcm_RoeData **/
#define DCM_ROE_SERVICETORESPOND2_0x01_IDX 0x05U

#if (defined DCM_ROE_SERVICETORESPOND0_0x03_IDX)
#error DCM_ROE_SERVICETORESPOND0_0x03_IDX already defined
#endif/* #if (defined DCM_ROE_SERVICETORESPOND0_0x03_IDX) */

/** \brief index value for accessing info of ServiceToRespond[0] of 0x03 event from Dcm_RoeData **/
#define DCM_ROE_SERVICETORESPOND0_0x03_IDX 0x04U

#if (defined DCM_ROE_SERVICETORESPOND1_0x03_IDX)
#error DCM_ROE_SERVICETORESPOND1_0x03_IDX already defined
#endif/* #if (defined DCM_ROE_SERVICETORESPOND1_0x03_IDX) */

/** \brief index value for accessing info of ServiceToRespond[1] of 0x03 event from Dcm_RoeData **/
#define DCM_ROE_SERVICETORESPOND1_0x03_IDX 0x05U

#if (defined DCM_ROE_SERVICETORESPOND2_0x03_IDX)
#error DCM_ROE_SERVICETORESPOND2_0x03_IDX already defined
#endif/* #if (defined DCM_ROE_SERVICETORESPOND2_0x03_IDX) */

/** \brief index value for accessing info of ServiceToRespond[2] of 0x03 event from Dcm_RoeData **/
#define DCM_ROE_SERVICETORESPOND2_0x03_IDX 0x06U

#if (defined DCM_ROE_REQUESTEDDID_0x03_IDX)
#error DCM_ROE_REQUESTEDDID_0x03_IDX already defined
#endif/* #if (defined DCM_ROE_REQUESTEDDID_0x03_IDX) */

/** \brief index value for accessing requested DID index of 0x03 event from Dcm_RoeData **/
#define DCM_ROE_REQUESTEDDID_0x03_IDX 0x07U

#if (defined DCM_ROE_INVALID_DATA)
#error DCM_ROE_INVALID_DATA already defined
#endif/* #if (defined DCM_ROE_INVALID_DATA) */

/** \brief Invalid data during initialisation  **/
#define DCM_ROE_INVALID_DATA 0xFFU

#if (defined DCM_ROE_INIT_DATA)
#error DCM_ROE_INIT_DATA already defined
#endif/* #if (defined DCM_ROE_INIT_DATA) */

/** \brief Init data during initialisation  **/
#define DCM_ROE_INIT_DATA 0x00U

#if (DCM_ROE_PRECONF_SUPPORT == STD_ON)
#if (defined DCM_ROE_PRECONF_ONCHANGEDID_EVENT_IDX)
#error DCM_ROE_PRECONF_ONCHANGEDID_EVENT_IDX already defined
#endif/* #if (DCM_ROE_PRECONF_ONCHANGEDID_EVENT_IDX) */

/** \brief index value for accessing the ROE Pre-configuration of OnChangeOfDataIdentifier **/
#define DCM_ROE_PRECONF_ONCHANGEDID_EVENT_IDX 0x00U
#endif

#endif


/* DID NvM Operation IDs  */

#if (defined DCM_DIDNVMOPERATION_NONE)
#error DCM_DIDNVMOPERATION_NONE already defined
#endif/* #if (defined DCM_DIDNVMOPERATION_NONE) */

/** \brief DID NvM Operation ID for no operation     **/
#define DCM_DIDNVMOPERATION_NONE          0x00U


#if (defined DCM_DIDNVMOPERATION_READNVMDATA)
#error DCM_DIDNVMOPERATION_READNVMDATA already defined
#endif/* #if (defined DCM_DIDNVMOPERATION_READNVMDATA) */

/** \brief DID NvM Operation ID for reading NvM data **/
#define DCM_DIDNVMOPERATION_READNVMDATA   0x01U


#if (defined DCM_DIDNVMOPERATION_WRITENVMDATA)
#error DCM_DIDNVMOPERATION_WRITENVMDATA already defined
#endif/* #if (defined DCM_DIDNVMOPERATION_WRITENVMDATA) */

/** \brief DID NvM Operation ID for writing NvM data  */
#define DCM_DIDNVMOPERATION_WRITENVMDATA  0x02U


#if (DCM_HSM_INST_MULTI_ENABLED == STD_ON)
#define DCM_TX_DATA_STATE(a)              Dcm_HsmInfo[(a)].txDataState
#define DCM_HSM_INFO(a)                   Dcm_HsmInfo[(a)]
#define DCM_NR_BUFFER(a)                  Dcm_NRCBufferConfig[(a)]
#define DCM_SEC_DELAY_COUNTER(a)          Dcm_HsmInfo[(a)].securityDelayCounter
#define DCM_EXCEED_NO_OF_ATTEMPTS(a)      Dcm_HsmInfo[(a)].exceededNumberOfAttempts
#define DCM_HSM_CONFIG(a)                 Dcm_HsmConfig[(a)]
/* Deviation MISRA-1 */
#define DCM_PL_START_TIMER(a, b)          a, b
/* Deviation MISRA-1 */
#define DCM_PL_CONFIRMATION(a, b)         a, b
/* Deviation MISRA-1 */
#define DCM_PL_CALL_INDICATION(a, b)      a, b
/* Deviation MISRA-1 */
#define DCM_PL_CALL_SERVICE(a, b)         a, b
/* Deviation MISRA-1 */
#define DCM_PDL_DISPATCH_SERVICE_REQ(a)   a
/* Deviation MISRA-1 */
#define DCM_CUR_PROTOCOL_ID(a)            a
/* Deviation MISRA-1 */
#define DCM_CUR_INST_ID(a)                a
/* Deviation MISRA-1 */
#define DCM_SES_TAB_CONFIG(a)             Dcm_SesTabConfig[(a)]
#else
#define DCM_TX_DATA_STATE(a)              Dcm_HsmInfo[0].txDataState
#define DCM_HSM_INFO(a)                   Dcm_HsmInfo[0]
#define DCM_NR_BUFFER(a)                  Dcm_NRCBufferConfig[0]
#define DCM_SEC_DELAY_COUNTER(a)          Dcm_HsmInfo[0].securityDelayCounter
#define DCM_EXCEED_NO_OF_ATTEMPTS(a)      Dcm_HsmInfo[0].exceededNumberOfAttempts
#define DCM_HSM_CONFIG(a)                 Dcm_HsmConfig[0]
/* Deviation MISRA-1 */
#define DCM_PL_START_TIMER(a, b)          b
/* Deviation MISRA-1 */
#define DCM_PL_CONFIRMATION(a, b)         b
/* Deviation MISRA-1 */
#define DCM_PL_CALL_INDICATION(a, b)      b
/* Deviation MISRA-1 */
#define DCM_PL_CALL_SERVICE(a, b)         b
#define DCM_PDL_DISPATCH_SERVICE_REQ(a)   void
#define DCM_CUR_PROTOCOL_ID(a)            0
#define DCM_CUR_INST_ID(a)                0
#define DCM_SES_TAB_CONFIG(a)             Dcm_SesTabConfig[0]
#endif

/* Wrapper function used for parameter typecasting
 * while accessing DCM_HSMEMITINST. */
#define DCM_HSMEMITINST_WRAPPER(a,b,c)\
  DCM_HSMEMITINST((a),((uint8)(b)),(c))
#define DCM_HSMEMITTOSELFINST_WRAPPER(a,b,c)\
  DCM_HSMEMITTOSELFINST((a),((uint8)(b)),(c))

#define DCM_ROE_NO_EVENT 0U
#define DCM_ROE_NORMAL_EVENT 1U
#define DCM_ROE_FINAL_RESPONSE_01 2U
#define DCM_ROE_FINAL_RESPONSE_03 3U

/*==================[type definitions]===========================================================*/

/** \brief Type definition for ROE event queue state */
typedef uint8 Dcm_ROEEnqueueEventType;

/** \brief Type definition for time base of the Dcm Module **/
typedef uint16 Dcm_TimeBaseConfigType;

/** \brief Different types of timing parameters
 **
 ** This type is used for the INTERNAL Dcm_GetSesTimingValues() to get values of configured default
 ** timing parameters, values of current active timing parameters or values of configured timing
 ** parameter limits. */
typedef enum
{
  DCM_DEFAULT,
  DCM_CURRENT,
  DCM_LIMITS
}
Dcm_TimerModeType;

/* !LINKSTO Dcm549,1 */
/** \brief State of a buffer in the Dcm module **/
typedef enum
{
  /** \brief Buffer is currently not in use */
  DCM_BUF_IDLE,
  /** \brief Buffer is used for reception */
  DCM_BUF_RX,
  /** \brief Buffer is used for response on event processing */
  DCM_BUF_ROE,
  /** \brief Buffer is used for transmission */
  DCM_BUF_TX
}
Dcm_BufferStateType;

/* !LINKSTO Dcm549,1 */
/** \brief Type to indicate whether diagnostic session allows to jump to Bootloader **/
typedef enum
{
  /** \brief Diagnostic session doesn't allow to jump to Bootloader **/
  DCM_NO_BOOT,
  /** \brief Diagnostic session allows to jump to OEM Bootloader **/
  DCM_OEM_BOOT,
  /** \brief Diagnostic session allows to jump to System Supplier Bootloader **/
  DCM_SYS_BOOT
}
Dcm_SessionForBootType;

/* !LINKSTO Dcm549,1 */
/** \brief Type of messages handled by Dcm **/
typedef enum
{
  /** \brief ROE **/
  DCM_ROE,
  /** \brief ROE final response**/
  DCM_ROE_FINAL,
  /** \brief Periodic Responses **/
  DCM_PR,
  /** \brief Other Normal messages **/
  DCM_NORMAL
}
Dcm_MessageType;

/* !LINKSTO Dcm549,1 */
/** \brief Type to indicate the state of ROEProcessing **/
typedef enum
{
  /** \brief No processing in progress **/
  DCM_ROE_NONE,
  /** \brief Processing enqueued **/
  DCM_ROE_QUEUED,
  /** \brief Processing in progress **/
  DCM_ROE_PROCESSING
}
Dcm_ROEProcessingType;

/* !LINKSTO Dcm549,1 */
/** \brief Entry of a session table **/
typedef struct
{
  /** \brief Extended Timeout for sending response pending message in this session
   * (P2*ServerMax) **/
  uint32 P2StarMaxTime;
  /** \brief Parameter indicating whether diagnostic session allows to jump to Bootloader **/
  Dcm_SessionForBootType SessionForBoot;
  /** \brief Timeout for sending response pending message in this session (P2ServerMax) **/
  uint16 P2MaxTime;
  /** \brief Diagnostic session type **/
  uint8 SesCtrl;
#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
  /** \brief Diagnostic session type generated by Rte **/
  uint8 RteSesMode;
#endif
}
Dcm_SesTabEntryConfigType;


/** \brief Entry in the communication channels table **/
typedef struct
{
  /** \brief network id of the communication channel **/
  NetworkHandleType networkId;
  /** \brief current communication mode of the channel **/
  Dcm_CommunicationModeType communicationMode;
}
Dcm_ChannelTabEntryType;


/** \brief Table of available session configurations **/
typedef struct
{
  /** \brief Pointer to array of session level configuration information **/
  P2CONST(Dcm_SesTabEntryConfigType, TYPEDEF, DCM_CONST) SessionEntries;
  /** \brief Number of configured sessions **/
  uint8 NumEntries;
  /** \brief Index to default session **/
  uint8 DefSessionIndex;
}
Dcm_SesTabConfigType;

/** \brief Different types access interfaces of DcmDspSecurity
 */
typedef enum
{
  /* The DCM will access the Security data using an R-Port requiring asynchronous CS Interface */
  DCM_USE_SECURITY_ASYNCH_CLIENT_SERVER,
  /* The DCM will access the Security data using the functions that are defined in parameters of
     type EcucFunctionNameDef; OpStatus is existing as IN parameter */
  DCM_USE_SECURITY_ASYNCH_FUNC,
  /* The DCM will access the Security Data using an R-Port requiring a synchronous CS Interface */
  DCM_USE_SECURITY_SYNCH_CLIENT_SERVER,
  /* The DCM will access the Security Data using the functions that are defined in parameters of
     type EcucFunctionNameDef; OpStatus parameter is not existing in the prototype */
  DCM_USE_SECURITY_SYNCH_FUNC
}
Dcm_SecurityAccesType;

/** \brief State of an authentication sequence (seed is already requested or not).
 *
 * Possible values:
 * - ::DCM_SEC_IDLE (=0) Value for security state if no seed was requested yet or after key was sent
 * - ::DCM_SEC_REQ_SEED (=1) Value for security state after seed was requested */
typedef uint8 Dcm_SecStateType;

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
/** \brief ComMChannel Id type for DcmDspComControlAllChannel **/
typedef uint8 Dcm_ComControlAllChannelType;
#endif

/** \brief Type of function to get seed value if ADRSize > 0(Async operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SecurityGetSeedFncADRAsync) (
  P2CONST(uint8, AUTOMATIC, DCM_VAR) SecurityAccessDataRecord,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to get seed value if ADRSize > 0(Sync and User operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SecurityGetSeedFncADRSync) (
  P2CONST(uint8, AUTOMATIC, DCM_VAR) SecurityAccessDataRecord,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to get seed value for ADRSize not > 0 (Async operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SecurityGetSeedFncAsync) (
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to get seed value for ADRSize not > 0 (Sync and User operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SecurityGetSeedFncSync) (
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to send Compare Key value (Async operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SecurityCompareKeyFncAsync) (
  P2CONST(uint8, AUTOMATIC, DCM_VAR) Key,
  Dcm_OpStatusType OpStatus);

/** \brief Type of function to send comapre key value (Sync and User operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SecurityCompareKeyFncSync) (
  P2CONST(uint8, AUTOMATIC, DCM_VAR) Key);

/** \brief Type of SchM Switch function for DcmCommunicationControl **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_SchMSwitchComControlFunctionType)(uint8 mode);

/** \brief Entry of a security level table **/
typedef struct
{
  /** \brief Delay time started after failed security access attempts and only after this time
             elapses a 'SecurityAccess' can be requested again **/
  uint32 DelayTime;
  Dcm_SecurityGetSeedFncADRSync   SecurityGetSeedFncADRSync; /**< ptr to DcmDspSecurityGetSeedFnc()
                                                  for userfnc. and sync operation for ADRSize > 0**/
  Dcm_SecurityGetSeedFncADRAsync  SecurityGetSeedFncADRAsync; /**< ptr to DcmDspSecurityGetSeedFnc()
                                                    for async operation for ADRSize > 0**/
  Dcm_SecurityGetSeedFncSync      SecurityGetSeedFncSync; /**< ptr to DcmDspSecurityGetSeedFnc()
                                           for userfnc. and sync operation for ADRSize not > 0**/
  Dcm_SecurityGetSeedFncAsync     SecurityGetSeedFncAsync; /**< ptr to DcmDspSecurityGetSeedFnc()
                                                       for async operation for ADRSize not > 0**/
  Dcm_SecurityCompareKeyFncSync   SecurityCompareKeyFncSync; /**< ptr to
                                 DcmDspSecurityComapreKeyFnc() for userfnc. and sync operation**/
  Dcm_SecurityCompareKeyFncAsync  SecurityCompareKeyFncAsync; /**< ptr to
                                             DcmDspSecurityComapreKeyFnc() for async operation**/
  Dcm_SecurityAccesType           SecAccessInterface; /**< Security access interface type **/
  /** \brief Value of this security level **/
  uint8  SecLevel;
  /** \brief Size of seed in bytes **/
  uint32  SeedSize;
  /** \brief Size of key in bytes **/
  uint32  KeySize;
  /** \brief Number of attempts until a delay will be activated **/
  uint8  AttDelay;
  /** \brief ADR Size **/
  uint32  ADRSize;
}
Dcm_SecTabEntryConfigType;

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
typedef struct
{
  /** \brief Network Id **/
  uint8 ComMChannelId;

  /** \brief Subnet Number which controls the specific ComMChannel **/
  uint8 SubnetNumber;
}
Dcm_ComControlSpecificChannelType;

typedef struct
{
  /** \brief Network Id **/
  uint8 ComMChannelId;

  /** \brief pointer to SchM Switch for DcmCommunicationControl **/
  Dcm_SchMSwitchComControlFunctionType SchMSwitchComControl;
}
Dcm_ComControlLookupType;
#endif

/** \brief Table of available security level configurations **/
typedef struct
{
  /** \brief Pointer to array of security level configuration information **/
  P2CONST(Dcm_SecTabEntryConfigType, TYPEDEF, DCM_CONST) Entries;
  /** \brief Number of configured security levels **/
  uint8                                                    NumEntries;
}
Dcm_SecTabConfigType;


/** \brief This type contains status information about a specific buffer. */
typedef struct
{
  /** \brief Length of valid data in bytes stored in this buffer
   *
   * The length information is used for reception and transmission.*/
  PduLengthType       filledLen;

  /** \brief Holds index of valid data in bytes to be transmitted in this buffer */
  PduLengthType       dataMark;

  /** \brief Holds index of Confirmed data in bytes in this buffer */
  PduLengthType       confirmedDataMark;

  /** \brief State of this buffer */
  Dcm_BufferStateType state;

  /** \brief RxPduId which was used to fill the buffer
   *
   * Only valid if the buffer state is DCM_BUF_RX or DCM_BUF_ROE */
  PduIdType           originatingRxPduId;

} Dcm_BufferInfoType;

/** \brief This type contains the configuration inforamtion a buffer used for communication. **/
typedef struct
{
  /** \brief location of buffer **/
  Dcm_MsgType ptrBuffer;
  /** \brief status information for this buffer configuration **/
  P2VAR(Dcm_BufferInfoType, TYPEDEF, DCM_VAR) bufferInfo;
  /** \brief Size of this buffer **/
  PduLengthType size;
}
Dcm_BufferConfigType;

/** \brief This type contains the information needed while processing service
 * ReadDTCInforamtion(0x19) **/
typedef struct
{
  /** \brief Count of number of DTCs processed **/
  uint16 DTCCount;
  /** \brief Requested Freeze frame or Extended Data record number **/
  uint8  ReqRecNum;
  /** \brief Currently processed DTC Record(Extended Data Record or Freeze Frame Record) number **/
  uint8  DTCRecNum;
}
Dcm_ReadDTCInfoContextType;

/* ROE Event setup */
#define DCM_ROE_EVENT_SETUP (0x00U)
/* ROE Event started */
#define DCM_ROE_EVENT_STARTED (0x01U)
 /* ROE Event cleared */
#define DCM_ROE_EVENT_CLEARED (0x02U)

/* ROE async handling state  ROE_POLLING_IDLE */
#define ROE_POLLING_IDLE (0x00U)
/* ROE async handling state  ROE_POLLING_ACTIVE */
#define ROE_POLLING_ACTIVE (0x01U)
/* ROE async handling state  ROE_POLLING_POSTPONED */
#define ROE_POLLING_POSTPONED (0x02U)

/** \brief Type of external service functions for diagnostic requests **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ExternalServiceFunctionType)(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

typedef P2FUNC(boolean, DCM_APPL_CODE, Dcm_ModeRuleFunctionType) (P2VAR(uint8, AUTOMATIC, DCM_VAR) Nrc);

/** \brief Type of external Subservice functions  **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ExternalSubServiceFunctionType)(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Type of callback function used to confirm a transmissin to the diagnostic application **/
typedef P2FUNC(void, DCM_APPL_CODE, Dcm_DcmConfirmationType)(
  Dcm_IdContextType idContext, PduIdType dcmRxPduId, Dcm_ConfirmationStatusType status);

/** \brief Type of process page function **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ProcessPageFuncType)(
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Type of internal service functions for diagnostic requests **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_InternalServiceFunctionType)(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Type of internal Subservice functions **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_InternalSubServiceFunctionType)(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief This type contains configuration for a single Subservice **/
typedef struct
{
  /** \brief Pointer to array of allowed sub service sessions **/
  P2CONST(Dcm_SesCtrlType, TYPEDEF, DCM_CONST) SubSesCtrls;

  /** \brief Pointer to array of allowed sub service security levels **/
  P2CONST(Dcm_SecLevelType, TYPEDEF, DCM_CONST) SubSecLevels;

  /** \brief Pointer to External Subservice function **/
  Dcm_ExternalSubServiceFunctionType ExtSrvHandler;

  /** \brief Pointer to Internal Subservice function **/
  Dcm_InternalSubServiceFunctionType IntSrvHandler;

  /** \brief Pointer to Mode rule function **/
  Dcm_ModeRuleFunctionType ModeRuleSubSrvFunction;

  /** \brief Subservice id **/
  uint8 SubServiceId;

  /** \brief Number of sessions types for which this subservice may be executed **/
  uint8 NumSubSesCtrls;

  /** \brief Number of security levels for which this subservice is allowed **/
  uint8 NumSubSecLevels;
}
Dcm_SubSidTabEntryConfigType;

/** \brief This type contains configuration for a single service ID **/
typedef struct
{

  /** \brief Pointer to array of allowed sessions **/
  P2CONST(Dcm_SesCtrlType, TYPEDEF, DCM_CONST) SesCtrls;

  /** \brief Pointer to array of allowed security levels **/
  P2CONST(Dcm_SecLevelType, TYPEDEF, DCM_CONST) SecLevels;

  /** \brief Pointer to array of Subservices configuration **/
  P2CONST(Dcm_SubSidTabEntryConfigType, TYPEDEF, DCM_CONST) SubServices;

  /** \brief Pointer to External service function **/
  Dcm_ExternalServiceFunctionType ExtSrvHandler;

  /** \brief Pointer to Internal service function **/
  Dcm_InternalServiceFunctionType IntSrvHandler;

  /** \brief Pointer to Mode rule function **/
  Dcm_ModeRuleFunctionType ModeRuleSrvFunction;

  /** \brief Service id of this entry **/
  uint8 ServiceId;

  /** \brief Number of sessions types for which this service may be executed **/
  uint8 NumSesCtrls;

  /** \brief Number of security levels for which this service is allowed **/
  uint8 NumSecLevels;

  /** \brief Number of subservices of this service **/
  uint8 NumSubServices;

  /** \brief subfunction is available **/
  boolean SubfuncAvail;

  /** \brief Asynchronous execution of Service is available **/
  boolean AsyncServiceExecution;
}
Dcm_SidTabEntryConfigType;

/** \brief State of data for a particular Tx PduId **/
typedef enum
{
  /** \brief no data available (yet) **/
  DCM_NO_TX_DATA,
  /** \brief data is ready to be transmitted **/
  DCM_TX_DATA_READY,
  /** \brief an error occured while sending **/
  DCM_TX_DATA_NOT_OK
}
Dcm_TxDataStateType;

/** \brief 'Response Pending' transmission status */
typedef enum
{
  /* No 'Response Pending' transmission is active */
  DCM_RP_NO_DATA,
  /* 'Response Pending' Tx Confirmation is pending */
  DCM_RP_PENDING_CONF,
  /* Tx Confirmation received for 'Response Pending' */
  DCM_RP_CONFIRMED_TX
}
Dcm_RpTxStatusType;
/** \brief State of the jump to bootloader process */

/* There is no jump to the bootloader in progress or a jump is in preparation. */
#define DCM_PREPARE_JUMP 0U
/* An immediate RequestCorrectlyReceivedResponsePending NRC needs to be transmitted and
   the Dcm is waiting for the confirmation of this transmission from the PduR. */
#define DCM_FIRST_RCRRP_PENDING 1U
/* All prerequisites for a bootloader jump are fulfilled, the Programming Conditions are being
   set and in case this setting is successful, a reboot will follow. */
#define DCM_JUMP_IN_PROGRESS 2U

typedef uint8 Dcm_jumpToBLExecutionType;

/** \brief This type contains the the most frequently used context information for DCM state
 * machine **/
typedef struct
{
  /** \brief Timer value of general protocol timer no 2 **/
  uint32 timer2;

  /** \brief Timer value of timer generating the event that causes the transition from
   *         HSM state "WaitForFullComProcess" to "Finishing" **/
  uint32 timerTx;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
  /** \brief Timer value of timer generating the event that causes the transition from
   *         HSM state "PgBufProcessing" to "CancelPgBufProcessing" **/
  uint32 timerPgBuf;
#endif /* DCM_PAGEDBUFFER_ENABLED */

   /** \brief Security delay counter for the Hsm **/
  uint32 securityDelayCounter;

 /** \brief message Context for requests **/
  Dcm_MsgContextType msgContext;

  /** \brief Counter of resp. data sent via paged buffer processing **/
  PduLengthType sentLength;

  /** \brief Pointer to currently used TxBuffer (allows a separate NRC buffer) **/
  P2CONST(Dcm_BufferConfigType, TYPEDEF, DCM_CONST) curTxBuffer;

   /** \brief State of the data for this Tx Pdu Id **/
  Dcm_TxDataStateType txDataState;

  /** \brief 'Response Pending' transmission status **/
  Dcm_RpTxStatusType responsePendingTxStatus;

 /** \brief Timer value of general protocol timer no 3 **/
  uint16 timer3;

  /** \brief Timer value of Dsp retry timer **/
  uint16 retryTimer;

  /** \brief Timer value of retry timer to wait for Full Com **/
  uint16 retryTimerTxEn;

  /** \brief Reception Pdu Id used by this Hsm **/
  PduIdType rxPduId;

  /** \brief Handle Id used by the DCM for transmission of responses **/
  PduIdType txPduId;

  /** \brief Handle Id used by the Lower Layer to confirm the transmission **/
  PduIdType txConfirmationPduId;

  /** \brief Index of currently active diagnostic session; Indexes the array
   **  Dcm_SesTabEntryConfig[] **/
  uint8 sesTabIdx;

  /** \brief Index of new diagnostic session; Indexes the array Dcm_SesTabEntryConfig[]**/
  uint8 sesTabIdxNew;

  /** \brief Index of currently active security level;
             Indexes the array Dcm_SecTabConfig.Entries[] **/
  uint8 secTabIdx;

  /** \brief Index of currently requested security level; **/
  uint8 reqSecTabIdx;

  /** \brief Index of the currently active serviceId; Indexes the array Dcm_SidTabEntryConfig[] **/
  uint8 sidTabEntryInd;

  /** \brief Indicates S3 timer needs to be restarted after processing a diagnostic request **/
  boolean s3Restart;

   /** \brief sessionControlType from diagnosticSessionControl request */
  Dcm_MsgItemType newSesCtrl;
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
  /** \brief Currently entered Diagnostics Session **/
  Dcm_SesCtrlType confirmedDiagSession;
#endif
  /** \brief Last requested security level */
  Dcm_SecLevelType requestedSecLevel;
#if (DCM_MODEDECLARATION_SUPPORT == STD_OFF)
  /** \brief Currently requested reset mode */
  Dcm_ResetModeType requestedResetMode;

  /** \brief Currently confirmed reset mode */
  Dcm_ResetModeType confirmedResetMode;

  /** \brief Currently requested Communication mode */
  Dcm_CommunicationModeType requestedCommunicationMode;

  /** \brief Currently confirmed Communication mode */
  Dcm_CommunicationModeType confirmedCommunicationMode;
#endif
  /** \brief Id of service request handled by the state machine **/
  uint8 serviceId;

  /** \brief Id of subservice request handled by the state machine **/
  uint8 subServiceId;

  /** \brief Index of the currently active sub-service; Indexes the array
   **  Dcm_SubSidTabEntryConfig[] **/
  uint8 subServiceIdIdx;

  /** \brief Negative response code occured during processing of the request **/
  Dcm_NegativeResponseCodeType negativeResponseCode;

  /** \brief Id of ProcessPage() function to be called during paged processing
   **
   ** Indexes the array of paged buffer processing functions.
   ** Set to DCM_PROCESS_PAGE_ID_INVALID (=0xFF) if paged processing is not active.
   **/
  uint8 processPageFuncId;

  /** \brief Response Pending counter **/
  uint8 rpCntr;

  /** \brief Status of number of security access attempts **/
  boolean exceededNumberOfAttempts;

  /** \brief Indicates if Jump to bootloader mode request is accepted **/
  boolean jumpToBLSupport;

  /** \brief Indicates if Jump to bootloader request is pending **/
  Dcm_jumpToBLExecutionType jumpToBLExecution;

  /** \brief Indicates if Jump to bootloader request has been inhibited 
   ** due to a pending previously started SetProgConditions() call **/
  boolean jumpToBLInhibited;

  /** \brief Type of service request handled by the state machine
   **
   ** - TRUE  : If service processed is DSP service
   ** - FALSE : If service processed is RTE/CentralDiag Service */
  boolean dspService;

  /** \brief Status of ControlDTCSettings
   **
   ** - TRUE  : DTCSettings are disabled
   ** - FALSE : DTCSettings are enabled */
  boolean dtcDisableStatus;

  /** \brief opState to communicate to an asynchronous service handler **/
  Dcm_OpStatusType asyncServiceOpState;

  /** \brief Status of failures before dispatching a service request
   **
   ** - TRUE  : Initial request validations successful
   ** - FALSE : Initial request validations failed */
  boolean requestValidationStatus;
}
Dcm_HsmInfoType;

/** \brief This type contains configuration of the service ID tables. **/
typedef struct
{
  /** \brief Pointer to array of service functions included in this table. */
  P2CONST(Dcm_SidTabEntryConfigType, TYPEDEF, DCM_CONST) Entries;

  /** \brief number of service entries in this table */
  uint8                                                  NumEntries;
}
Dcm_SidTabConfigType;

/** \brief ROE transmission type selected for protocol **/
typedef enum
{
  /** \brief No transmission type is selected for ROE */
  DCM_ROE_NOTYPE,
  /** \brief TYPE1 is selected for transmission of ROE */
  DCM_ROE_TYPE1,
  /** \brief TYPE2 is selected for transmission of ROE */
  DCM_ROE_TYPE2
}
Dcm_ProtocolTransType;

/** \brief This type contains the configuration information for TxPduIds, Protocols and HSM
 ** instances. **/
typedef struct
{
  /** \brief ROE transmission type selected for this protocol(TYPE1/TYPE2).**/
  Dcm_ProtocolTransType roeTransmissionType;

  /** \brief This parameter is used to guarantee that the response
     is available on the bus before reaching P2.
   **/
  uint16 P2ServerAdjustTime;

  /** \brief This parameter is used to gurantee that the DCM response
  is available on the bus before reaching P2*.
  **/
  uint16 P2StarServerAdjustTime;

  /** \brief protocol type (UDS, OBD) **/
  Dcm_ProtocolType protocolType;

  /** \brief priority of this protocol **/
  uint8 priority;

  /** \brief ID of related service table; Indexes the array Dcm_SidTabConfig[] **/
  uint8 sidTabId;

  /** \brief ID of associated buffer used for this TxPduId; Indexes the array Dcm_BufferConfig[] **/
  uint8 txBufferId;

  /** \brief Indicates whether EndianessConversion is enabled or not **/
  boolean endianessConversion;

  /** \brief Specifying if the ECU should send a response pending before transitioning to BL **/
  boolean sendRespPendOnTransToBoot;
}
Dcm_HsmConfigType;

/** \brief This type contains the configuration information for each reception (Rx) Pdu Id of the
 ** Dcm module. **/
typedef struct
{
  /** \brief Tester source address configured per protocol **/
  uint16 TesterSourceAddr;

  /** \brief addressing Type for this Pdu Id **/
  uint8 addrType;

  /** \brief ID of associated buffer used for this Rx Pdu Id: Indexes the array
   **  Dcm_BufferConfig[] **/
  uint8 rxBufferId;

  /** \brief ID of associated protocol for this Rx Pdu Id **/
  uint8 protocolId;

  /** \brief ID of associated Main connection for this Rx Pdu Id **/
  uint8 connectionId;

  /** \brief Index of Channel Identifier in Dcm_ChannelId[] **/
  uint8 channelIdIndex;
}
Dcm_RxPduIdConfigType;

/** \brief This type contains the configuration information for each Main connection Tx Pdu Ids for the
 ** Dcm module. **/
typedef struct
{
  /** \brief Handle Id used by the DCM for transmission of responses **/
  PduIdType txPduId;

  /** \brief Handle Id used by the Lower Layer to confirm the transmission **/
  PduIdType txConfirmationPduId;
}
Dcm_TxPduIdConfigType;

/** \brief State of reception (Rx) Pdu Id of the Dcm module **/
typedef enum
{
  /** \brief Rx Pdu Id is not in use **/
  DCM_RX_PDU_ID_IDLE,
  /** \brief Rx Pdu Id occupied **/
  DCM_RX_PDU_ID_BUSY
}
Dcm_RxPduIdStateType;

/** \brief Pointer to SidTabEntryConfigType */
typedef P2CONST(Dcm_SidTabEntryConfigType, AUTOMATIC, DCM_CONST) Dcm_SidTabEntryConfigPtrType;

/** \brief The type of service request on a Data Identifier(DID) */
typedef enum
{
  /* ReadDID Service request */
  DCM_DID_OP_READ,
  /* WriteDID Service request */
  DCM_DID_OP_WRITE,
  /* IOControl Service request */
  DCM_DID_OP_IOCONTROL
}Dcm_DidOpType;

/** \brief States of Dcm Init after Jump to BL */
typedef enum
{
  /* ComM full communication mode change is pending  */
  DCM_COMM_MODE_CONF_PENDING,
  /* Tx Confirmation pending for the response transmitted  */
  DCM_TX_CONF_PENDING,
  /* Tx Confirmation received for the response transmitted */
  DCM_RES_TX_CONF_OK,
  /* Dcm_SetProgConditions() result Pending or NotOk */
  DCM_SET_PROGCONDITIONS_PENDING,
  /* Normal processing enabled */
  DCM_NORMAL_PROC
}
Dcm_BLInitStatusType;

/** \brief Type for Did Access Information.
 ** It lists the permissions like access, session permissions and security permissions
 ** available for a Did **/
typedef struct
{
  /**< Pointer to array of allowed security levels for accessing the DID **/
  P2CONST(Dcm_SecLevelType, TYPEDEF, DCM_CONST) SecLevels;
  /**< Pointer to array of allowed sessions for accessing the DID**/
  P2CONST(Dcm_SesCtrlType, TYPEDEF, DCM_CONST) SesCtrls;
  uint8   NumSecLevels;  /**< Number of security levels for which this DID can be accessed **/
  uint8   NumSesCtrls;   /**< Number of sessions types for which this DID can be accessed **/
  boolean Enabled;       /**< Acces is enabled for the DID **/
}Dcm_DidAccessInfoType;

/** \brief  This type contains the configuration information for each signals configured in a Did
 **/
typedef struct
{
  uint16 DataPos;  /**< Position in bits of the DID data **/
  uint16 DspDataIndex;  /**< Index to the Data array **/
}
Dcm_DidSignalType;

/** \brief Type of function for actiavte/deactivate ROE Event using user function interface **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RoeActivateFncType) (
  uint8 RoeEventId, Dcm_RoeStateType RoeState);

/** \brief  This type contains the configuration information for each Did Services of the Dcm
 ** module. **/
typedef struct
{
  Dcm_DidAccessInfoType ReadAccess; /**< Read access information **/
  Dcm_DidAccessInfoType WriteAccess; /**< Write access information **/
  Dcm_DidAccessInfoType ControlAccess; /**< Control access information **/
  /**< Pointer to references array for this DID. */
  P2CONST(uint16, TYPEDEF, DCM_CONST) DidReferences;
  /**< Pointer to array of signal configurations for this DID. */
  P2CONST(Dcm_DidSignalType, TYPEDEF, DCM_CONST) Signals;
  Dcm_RoeActivateFncType RoeActivateFnc; /**< ptr to ActivateEvent() **/
  uint16 NumSignals;  /**< Number of signals configured in this DID **/
  uint16 Did;  /**< Identifier of the DID **/
  uint8 NumRefDids;  /**< Number of refered Dids **/
  uint8 RoeEventId; /**< Indicates ROE EventId for a Did **/
  boolean ExtRoeSupport; /**< Indicates whether DcmDspDidExtRoe is configured **/
  boolean FreezeCurrentStateEnable; /**< Indicates whether FreezeCurrentState operation
                                                           ** is enabled **/
  boolean ResetToDefaultEnable; /**< Indicates whether ResetToDefault operation is enabled **/
  boolean ShortTermAdjustmentEnable; /**< Indicates whether ShortTermAdjustment operation
                                                             ** is enabled **/
  boolean ReturnControlToEcuEnable; /**< Indicates whether ReturnControlToEcu operation
                                                             ** is enabled **/
}
Dcm_DidServicesType;

/** \brief Type of function for reading the DID using sender-receiver, user function and
  *  synch interface **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ReadDataFncTypeSync) (
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Data);

/** \brief Type of RTE_Call_Xxx function for reading the Data of a DID signal */
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ReadDataFncTypeAsync) (
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Data);

/** \brief Type of function for writing the DID in case of fixed length data **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_WriteDataFixedTypeSync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) Data,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function for writing the DID in case of variable length data **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_WriteDataVariableTypeSync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) Data,
  uint16 DataLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of Rte_Call_Xxx function for writing the DID in case of fixed length data **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_WriteDataFixedTypeAsync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) Data,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);

/** \brief Type of Rte_Call_Xxx function for writing the DID in case of variable length data **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_WriteDataVariableTypeAsync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) Data,
  uint16 DataLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);

/** \brief Type of Rte_Result_Xxx function for writing the DID **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RteResultWriteDataType) (
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function for reading the length of the DID Data **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ReadDataLengthType) (
  P2VAR(uint16, AUTOMATIC, DCM_VAR) DataLength);

/** \brief Type of function to check if the DID can be read (Sync and User operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ConditionCheckReadTypeSync) (
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to check if the DID can be read (Async operations) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ConditionCheckReadTypeAsync) (
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request application to freeze the current state of an IOControl
      (Sync operation) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_FreezeCurrentStateSync) (
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request to application to adjust the IO signal (Sync operation)
    with fixed length data**/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ShortTermAdjustmentFixedTypeSync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) ControlOptionRecord,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request to application to adjust the IO signal (Sync operation)
    with variable length data **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ShortTermAdjustmentVariableTypeSync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) ControlOptionRecord,
  uint16 DataLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request to application to reset an IOControl to default value
      (Sync operation) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ResetToDefaultSync) (
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request to application to return control to ECU of an IOControl
      (Sync operation) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ReturnControlToEcuSync) (
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request application to freeze the current state of an IO Control
      (Async operation) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_FreezeCurrentStateAsync) (
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request to application to adjust the IO signal (Async operation)
    and fixed length data **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ShortTermAdjustmentFixedTypeAsync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) ControlOptionRecord,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request to application to adjust the IO signal (Async operation)
    and variable length data**/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ShortTermAdjustmentVariableTypeAsync) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) ControlOptionRecord,
  uint16 DataLength,
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request application to reset an IOControl to default value
     (Async operation) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ResetToDefaultAsync) (
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of function to request to application to return control to ECU of an IOControl
        (Async operation) **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_ReturnControlToEcuAsync) (
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Different data types access of data belonging to DcmDspDataType for a Did
 */
typedef enum
{
  /* type of the signal is boolean */
  DCM_TYPE_BOOLEAN,
  /* type of the signal is sint16 */
  DCM_TYPE_SINT16,
  /* type of the signal is sint32 */
  DCM_TYPE_SINT32,
  /* type of the signal is sint8 */
  DCM_TYPE_SINT8,
  /* type of the signal is uint16 */
  DCM_TYPE_UINT16,
  /* type of the signal is uint32 */
  DCM_TYPE_UINT32,
  /* type of the signal is uint8 */
  DCM_TYPE_UINT8
}
Dcm_DidDataByteType;

/** \brief Different types access interfaces of DcmDspData for a Did
 */
typedef enum
{
  /* The DCM will access the Data using the NVRAM Apis */
  DCM_USE_BLOCK_ID,
  /* The DCM will access the Data using an R-Port requiring a asynchronous ClientServertInterface */
  DCM_USE_DATA_ASYNCH_CLIENT_SERVER,
  /* The DCM will access the Data using the functions that are defined in parameters of type
     EcucFunctionNameDef; OpStatus is existing as IN parameter */
  DCM_USE_DATA_ASYNCH_FUNC,
  /* The DCM will access the Data using an Port requiring a SenderReceiverInteface */
  DCM_USE_DATA_SENDER_RECEIVER,
  /* The DCM will access the Data using an R-Port requiring a synchronous ClientServertInterface */
  DCM_USE_DATA_SYNCH_CLIENT_SERVER,
  /* The DCM will access the Data using the functions that are defined in parameters of type
     EcucFunctionNameDef; OpStatus parameter is not existing in the prototype */
  DCM_USE_DATA_SYNCH_FUNC,
  /* The DCM will access the Data using a direct access to IoHwAb */
  DCM_USE_ECU_SIGNAL
}
Dcm_DidDataAccesType;

/** \brief  This type contains the configuration information for datas belonging to a Did
**/
typedef struct
{

  Dcm_ConditionCheckReadTypeSync  ConditionCheckReadSync; /**< ptr to ConditionCheckRead() for
                                                           userfnc. and sync operation**/
  Dcm_ConditionCheckReadTypeAsync ConditionCheckReadAsync; /**< ptr to ConditionCheckRead() for
                                                       async operation**/
  Dcm_ReadDataLengthType          ReadDataLength; /**< ptr to ReadDataLength for userfnc
                                                       and sync operation**/
  Dcm_ReadDataFncTypeSync         ReadDataFncSync; /**< ptr to ReadData() for
                                                        DCM_USE_DATA_SYNCH_FUNC, Sender-Receiver and
                                                        USE_DATA_SYNCH_CLIENT_SERVER interface**/
  Dcm_ReadDataFncTypeAsync        ReadDataFncAsync; /**< ptr to ReadData() for
                                                         DCM_USE_DATA_ASYNCH_FUNC and
                                                         USE_DATA_ASYNCH_CLIENT_SERVER interface**/
  Dcm_WriteDataFixedTypeSync      WriteFixedDataSync; /**< ptr to WriteData() for fixed length data
                                                       in synch and user type **/
  Dcm_WriteDataVariableTypeSync   WriteVariableDataSync; /**< ptr to WriteData() for variable length
                                                          data in synch and user type**/
  Dcm_WriteDataFixedTypeAsync     WriteFixedLengthDataAsync; /**< ptr to WriteData() for fixed
                                                             length data for async operation**/
  Dcm_WriteDataVariableTypeAsync  WriteVarLengthDataAsync; /**< ptr to WriteData() for variable
                                                           length data for async operation**/
  Dcm_RteResultWriteDataType      ResultWriteData;    /**< ptr to result of WriteData() for
                                                           async operation**/
  Dcm_FreezeCurrentStateSync      FreezeCurrentStateSync; /**< ptr to FreezeCurrentState() to freeze
                                                           the current state of an IOControl and
                                                           sync operation**/
  Dcm_FreezeCurrentStateAsync     FreezeCurrentStateAsync; /**< ptr to FreezeCurrentState() to
                                                            freeze the current state of an IOControl
                                                            and async operation**/
  Dcm_ShortTermAdjustmentFixedTypeSync      ShortTermAdjustmentFixedSync; /**< ptr to
                                                                           ShortTermAdjustment()
                                                                           for userfnc, fixed
                                                                           length and sync
                                                                           operation**/
  Dcm_ShortTermAdjustmentVariableTypeSync   ShortTermAdjustmentVariableSync; /**< ptr to
                                                                             ShortTermAdjustment()
                                                                             for userfnc, variable
                                                                             length and sync
                                                                             operation**/
  Dcm_ShortTermAdjustmentFixedTypeAsync     ShortTermAdjustmentFixedAsync; /**< ptr to
                                                                           ShortTermAdjustment(),
                                                                           fixed length  to adjust
                                                                           the IO signal async
                                                                           operation**/
  Dcm_ShortTermAdjustmentVariableTypeAsync  ShortTermAdjustmentVariableAsync; /**< ptr to
                                                                             ShortTermAdjustment()
                                                                             for userfnc, variable
                                                                             length and async
                                                                             operation**/
  Dcm_ResetToDefaultSync          ResetToDefaultSync; /**< ptr to ResetToDefault() to reset an
                                                           IOControl to default value and sync
                                                           operation**/
  Dcm_ResetToDefaultAsync         ResetToDefaultAsync; /**< ptr to ResetToDefault() to reset an
                                                            IOControl to default value and async
                                                            operation**/
  Dcm_ReturnControlToEcuSync      ReturnControlToEcuSync; /**< ptr to ReturnControlToEcu() to return
                                                            control to ECU of an IOControl and sync
                                                            operation**/
  Dcm_ReturnControlToEcuAsync     ReturnControlToEcuAsync; /**< ptr to ReturnControlToEcu() to
                                                              return control to ECU of an IOControl
                                                              and async operation**/
  Dcm_DidDataByteType             DataType; /**< Data type of signal >**/
  Dcm_DidDataAccesType            AccessInterface; /**< Data access interface type **/
  uint16                          DataLength; /**< Length of the data in bits **/
  NvM_BlockIdType                 NvRamBlockId; /**< Identifier of NVMBlock **/
  boolean                         FixedLength; /**< Indicates whether the data length is fixed **/
}
Dcm_DidDataType;

/** \brief  This type contains the different stages of processing a Did request
 */
typedef enum
{
  /* The state for checking the request data */
  DCM_DID_REQUEST_CHECK,
  /* The state for processing the request data */
  DCM_DID_REQUEST_PROCESSING,
  /* The state for PENDING read operation */
  DCM_DID_READ_PENDING,
  /* Invalid state */
  DCM_DID_REQUEST_INVALID
} Dcm_DidRequestProcessingStType;

/** \brief Different Contexts while reading a Did using the service 0x22
 */
typedef enum
{
  /* State for checking the conditions for reading DID*/
  DCM_DID_READ_CONDITION,
  /* State for reading DID*/
  DCM_DID_READ,
  /* State for reading referenced DIDs*/
  DCM_DID_READ_REF,
  /* Invalid case*/
  DCM_DID_READ_INVALID,
  /* Cancel case*/
  DCM_DID_READ_CANCEL
}
Dcm_DidReadProcessingStType;

/** \brief This type contains the different stages of processing a referenced Did read
 */
typedef enum
{
  /* State for checking the conditions for reading referenced DID*/
  DCM_DID_REF_READ_CONDITION,
  /* State for reading referenced DID*/
  DCM_DID_REF_READ,
  /* Invalid case*/
  DCM_DID_REF_INVALID,
  /* Cancel case*/
  DCM_DID_REF_CANCEL
}
Dcm_RefDidProcessingStType;

/** \brief Different Contexts while checking condition for reading a Did Signal using the
     service 0x22
 */
typedef enum
{
  /* Condition check call for reading signal*/
  DCM_DID_SIG_CONDITION_CALL,
  /* ReadDataLength call for signal */
  DCM_DID_SIG_READDATA_LEN_CALL,
  /* Reading a signal*/
  DCM_DID_SIG_READ,
  /* Cancel reading a signal*/
  DCM_DID_SIG_READ_CANCEL
}
Dcm_DidReadSigConditionStType;

/** \brief  This type contains the different stages of processing an asynchronous Did signal read
 */
typedef enum
{
  /* ReadData call in async read */
  DCM_DID_SIGNAL_CALL,
  /* Reading result call in async read */
  DCM_DID_SIGNAL_RESULT,
  /* Invalid case*/
  DCM_DID_SIGNAL_INVALID
}
Dcm_DidAsynchSignalStType;

/** \brief  This type contains the different stages of returning control of signal to Ecu
 */
typedef enum
{
  /* Invalid case */
  DCM_RET_CTRL_INACTIVE,
  /* Returning control to Ecu for a signal is finished */
  DCM_RET_CTRL_FINISHED,
  /* Returning control to Ecu for a signal is Pending */
  DCM_RET_CTRL_PENDING
}
Dcm_DidReturnControlToEcuStatusType;

/** \brief  This type contains the context information for the service 0x22.
**/
typedef struct
{
  boolean InitSignalProcessing; /* Specifies if the signal is being processed for the first time */
  Dcm_MsgType BuffPtr;/* Pointer to the Recieved Dids */
  Dcm_DidReadProcessingStType DidReadProcessingSt; /* State of currently processed DID */
  /* State of currently processed DID signal read condition */
  Dcm_DidReadSigConditionStType DidReadSigConditionSt;
  Dcm_RefDidProcessingStType RefDidProcessingSt; /* State of currently processed referenced DID */
  Dcm_DidAsynchSignalStType DidAsynchSignalSt; /* State of currently processed asynch signal */
  Dcm_DidAsynchSignalStType DidNvmDataSt; /* State of currently processed Nvm data */
  uint16 DidCount; /* Number of DIDs for currently processed Read DID request */
  uint16 DidInd; /* Index of DID currently being processed */
  uint16 SignalInd; /* Index of DID Signal currently being processed */
  uint16 RefDidInd; /* Index of referenced DID currently being processed */
  uint16 NumSignalTotalBytes;/* Total number of bytes occupied by total signals in a DID */
  Dcm_NegativeResponseCodeType NrcCondtions;/* holds the global NRC for the currently processed
                                            read DID request */
}
Dcm_ReadDIDContextType;

/** \brief  This type holds the context information of a WriteDid request
 */
typedef struct
{
  boolean InitSignalProcessing; /* Specifies if the signal is being processed for the first time */
  uint16 SignalInd; /* Index of DID Signal currently being processed */
  /* Overall processing state of Read DID request */
  Dcm_DidRequestProcessingStType RequestProcessingSt;
  Dcm_DidAsynchSignalStType DidAsynchSignalSt; /* State of currently processed asynch signal */
  Dcm_DidAsynchSignalStType DidNvmDataSt; /* State of currently processed NVM data */
}
Dcm_WriteDIDContextType;

/** \brief  This type holds the context information of an IOControl request
 */
typedef struct
{
  boolean InitSignalProcessing; /* Specifies if the signal is being processed for the first time */
  uint8 IOControlParameter; /* Describes how the server shall control its inputs or outputs */
  uint16 DidIndex; /* Index of DID currently being processed */
  uint16 SignalInd; /* Index of DID Signal currently being processed */
  /* Overall processing state of Read DID request */
  Dcm_DidRequestProcessingStType RequestProcessingSt;
}
Dcm_IOControlDIDContextType;

/** \brief  This type holds the context information of an IOControl ReturnControlToEcu subfunction
 */
typedef struct
{
  uint16 returnToEcuSigInd; /* Index of DID Signal currently being returning control to ECU */
  uint16 didIndex; /* Index of the Did in the table Dcm_DidTable */
  uint16 timeoutCount; /* Processing time allowed for returncontroltoecu completion */
  Dcm_DidReturnControlToEcuStatusType returnCtrlToECUStatus; /* status of return control of
                                                                signal to Ecu */
}
Dcm_IOReturnControlToEcuStatusType;

/** \brief Pointer to const DataId array */
typedef P2CONST(uint16, AUTOMATIC, DCM_APPL_CONST) Dcm_DataIdPtrConstType;

/** \brief Type of service function for internally handling the routine
 ** control service calls for start, stop and requestResults sub-functions **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RoutineFncHandlerType) (
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA)pMsgContext,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief This type contains the configuration information for each Routine Services of the Dcm
 ** module. **/
typedef struct
{
  /** \brief Reference to DcmDspSecurityRow Security levels allowed to control this RID **/
  P2CONST(Dcm_SecLevelType, TYPEDEF, DCM_CONST) SecurityLevelRef;

  /** \brief Reference to DcmDspSessionRow Sessions allowed to control this RID **/
  P2CONST(Dcm_SesCtrlType, TYPEDEF, DCM_CONST) SessionRef;

  /** \brief Number of Security levels allowed to control this RID **/
  uint8 NumSesLevels;

  /** \brief Number of Sessions allowed to control this RID **/
  uint8 NumSecLevels;
}
Dcm_DspRoutineServicesInfoType;

/** \brief This type contains the configuration for each Routine Services of the Dcm
 ** module. **/
typedef struct
{

  /** \brief Function name handler for request to application the results of a routine **/
  Dcm_RoutineFncHandlerType RequestResultsFncHandler;

  /** \brief Function name handler for request to application to start a routine **/
  Dcm_RoutineFncHandlerType StartFncHandler;

  /** \brief Function name handler for request to application to stop a routine **/
  Dcm_RoutineFncHandlerType StopFncHandler;

  /** \brief Reference to DcmDspRoutineInfo containing information on this routine **/
  P2CONST(Dcm_DspRoutineServicesInfoType, TYPEDEF, DCM_CONST) RoutineInfoRef;

  /** \brief 2 bytes Identifier of the RID **/
  uint16 Identifier;

  /** \brief Indicates if the datalength of the optional record in the
   **  RoutineControl request and response is fixed **/
  boolean FixedLength;

  /** \brief If this parameter is set to true, the DCM uses a port requiring a PortInterface **/
  boolean UsePort;

}
Dcm_DspRoutineServicesType;

/** \brief Type of service function request to application for provision of seed value **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RteGetSeedType) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) SecurityAccessDataRecord,
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_VAR) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_VAR) ErrorCode);

/** \brief Type of service function request to application for comparing key **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RteCompareKeyType) (
  P2CONST(uint8, AUTOMATIC, DCM_CONST) Key,
  Dcm_OpStatusType OpStatus);

/** \brief Different States of Data Transfer. To specify whether Upload or Download is active.
 */
typedef enum
{
  /* No Upload or Download is registered */
  DCM_TRANSFER_IDLE,
  /* Download is registered by the service '0x34' */
  DCM_TRANSFER_DOWNLOAD,
  /* Upload is registered by the service '0x35' */
  DCM_TRANSFER_UPLOAD
}
Dcm_DataTransferStateType;

/** \brief This type contains the information for data transfer services(0x34,0x35,0x36,0x37)
 ** module. **/
typedef struct
{
  uint32 MemAddres; /**< Address to/from data to be download/upload **/
  uint32 MemSize; /**< Size of data to be download/upload **/
  uint32 MemTransfered; /**< Total Size of data transfered in the transfer request. **/
  uint32 CurrMemTransfered; /**< Total Size of data transfered in the current transfer request. **/
  Dcm_DataTransferStateType TransState; /**< To specify whether Upload or Download is active. **/
  uint8 BlockSequenceCounter; /**< For error handling in transfer data services. **/
}
Dcm_DataTransferType;

/** \brief  This type contains the configuration information for RequestDownload(0x34),
     RequestUpload(0x35) services.
**/
typedef struct
{
  uint32 MemRangeLow;  /**< Lower Range of memory for Downloading/Uploading **/
  uint32 MemRangeHigh;  /**< Upper Range of memory for Downloading/Uploading **/
  P2CONST(Dcm_SecLevelType, TYPEDEF, DCM_CONST) DldSecLevels;
                     /**< Pointer to array of allowed security levels for Download/Upload memory **/
  uint8 NumDldSecLevels;  /**< Number of security levels for which this Memory can be
                           Downloaded/Uploaded **/
}
Dcm_TransferConfigType;

/** \brief  This type contains the configuration information for ReadMemoryByAddress(0x23) and
            WriteMemoryByAddress(0x3D).**/
typedef struct
{
  uint32 MemoryRangeLow;  /**< Low memory address of a range allowed for reading/writing **/
  uint32 MemoryRangeHigh;  /**< High memory address of a range allowed for reading/writing **/
  P2CONST(Dcm_SecLevelType, TYPEDEF, DCM_CONST) MemSecLevels;
          /**< Pointer to array of security levels needed for read/write access in this memory **/
  uint8 NumMemSecLevels;  /**< Number of security levels for for which this memory read/write
                                access is provided **/
}
Dcm_MemoryRangeInfoType;

typedef struct
{

  P2CONST(Dcm_MemoryRangeInfoType, TYPEDEF, DCM_CONST) WriteMemoryRangeInfo;
                               /* Pointer to the range of memory address allowed for writing */
  P2CONST(Dcm_MemoryRangeInfoType, TYPEDEF, DCM_CONST) ReadMemoryRangeInfo;
                               /* Pointer to the range of memory address allowed for reading */
  uint16 numberofWriteRangeInfo; /*Number of 'WriteMemoryRangeInfos' configured */
  uint16 numberofReadRangeInfo; /*Number of 'ReadMemoryRangeInfos' configured */
  uint8 MemoryIDValue; /* Value of memory identifier used to select the desired memory device */
}
Dcm_MemoryIdInfoType;


/** \brief This type contains the information for Link Control service of the Dcm module.
 */
typedef struct
{
  uint8 baudrateIdentifier; /**< holds Fixed baudrate indentifier **/
  uint8 linkBaudrateRecord[3]; /**< holds baudrate mapped to baudrate indentifier **/
}
Dcm_LinkControlBaudrateType;

/** \brief Type of service function for request indication
 ** Two types of indicatiin functionality
 ** 1) Request Notification for Manufacturer
 ** 2) Request Notification for Supplier **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RteIndicationType) (
  uint8 SID,
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData,
  uint16 DataSize,
  uint8 ReqType,
  uint16 SourceAddress,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode);

/** \brief Type of service function for Confirmation **/
typedef P2FUNC(Std_ReturnType, DCM_APPL_CODE, Dcm_RteConfirmationType) (
  uint8 SID,
  uint8 ReqType,
  uint16 SourceAddress,
  Dcm_ConfirmationStatusType ConfirmationStatus);

/** \brief This type contains the configuration information for Notification functionality **/
typedef struct
{
  Dcm_RteIndicationType Indication; /**< ptr to Indication() **/
  Dcm_RteConfirmationType Confirmation; /**< ptr to Confirmation() **/
}
Dcm_RteRequestNotificationType;

/* if internally managed DIDs are configured and ROE is enabled */
#if ((DCM_INT_MANAGED_DIDS == STD_ON) && (DCM_ROE_ENABLED == STD_ON))
/** \brief  This type contains the context information for checking change in DID value.
**/
typedef struct
{
  Dcm_DidReadSigConditionStType DidReadSigConditionSt; /* State of currently processed DID signal
                                                          read condition */
  Dcm_DidAsynchSignalStType DidNvmDataSt; /* State of currently processed Nvm data */
  uint16 SignalInd; /* Index of DID Signal currently being processed */
  Dcm_MsgItemType SavedDIDData[DCM_ROE_DID_BUF_SIZE]; /* Buffer for storing the latest data of the
                                                         DID being monitored */
  Dcm_MsgItemType NewDIDData[DCM_ROE_DID_BUF_SIZE]; /* Buffer for storing the comparing data of the
                                                       DID being monitored */
}
Dcm_ChangeInDIDContextType;
#endif /* #if ((DCM_INT_MANAGED_DIDS == STD_ON) && (DCM_ROE_ENABLED == STD_ON)) */

#if ((DCM_ROE_PRECONF_SUPPORT == STD_ON) && (DCM_ROE_ENABLED == STD_ON))
/** \brief  This type contains the configuration information for each pre-configuration for
 ** ROE service of the Dcm module. **/
typedef struct
{
  uint8 EventWindowTime;  /**< EventWindowTime of the event **/
  Dcm_RoeStateType InitialStatus;  /**< Event initial status **/
  uint16 DID;  /**< referenced DID from the event request */
  PduIdType RxPduId; /**< RxPduId on which the ResponseOnEvent Start Request is simulated. */
}
Dcm_RoeEventPreConfigType;
#endif /* #if ((DCM_ROE_PRECONF_SUPPORT == STD_ON) && (DCM_ROE_ENABLED == STD_ON)) */

#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)

typedef uint8 Dcm_DidNvmOperationType;

/** \brief Type contains signal Buffer and the lock status */
typedef struct
{
  /** Array for holding the read/write data for a signal */
  uint8 SignalBuffer[DCM_DATA_MAX_SIZE];

  /** Indicate id of block used for reading/writing */
  NvM_BlockIdType BlockId;

  /** Indicate NvM service that is keeping the buffer locked */
  Dcm_DidNvmOperationType NvMService;
}
Dcm_SignalBufferContextType;

#endif /* #if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

/*==================[external function declarations]=============================================*/

#define DCM_START_SEC_CODE
#include <MemMap.h>

/** \brief Validate and dispatch service request dependent on the service Id to the respective
 **        service function.
 **
 ** This function has to be called from within the Hsm!
 **/
extern FUNC(void, DCM_CODE) Dcm_DsdInternal_DispatchSvcReq(
                                        DCM_PDL_DISPATCH_SERVICE_REQ(uint8 instIdx));

/** \brief Service Processing function for service handlers
 **
 ** This function is called from within Dcm_DsdInternal_DispatchSvcReq()
 **/
extern FUNC(void, DCM_CODE) Dcm_DspInternal_SvcFunc(
  uint8 instIdx,
  Dcm_OpStatusType  OpStatus);

/* EB extension */
/** \brief DCM cancels the processing of currently executed diagnostic service
 **/
extern FUNC(void, DCM_APPL_CODE) Dcm_DspInternal_CancelProcessing(void);

/** \brief This function confirms the successful transmission or a transmission error of a
 **        diagnostic service.
 **
 ** \param idContext Current context identifier which can be used to retrieve the relation between
 **        request and confirmation. Within the confirmation, the Dcm_MsgContext is no more
 **        available, so the idContext can be used to represent this relation. The idContext is
 **        alsopart of the Dcm_MsgContext.
 **
 ** \param dcmRxPduId DcmRxPduId on which the request was received. The source of the request can
 **        have consequences for message processing.
 **
 ** \param status Status indication about confirmation (differentiate failure indication and normal
 **        confirmation) (::DCM_RES_POS_OK, ::DCM_RES_POS_NOT_OK, ::DCM_RES_NEG_OK,
 **        ::DCM_RES_NEG_NOT_OK)
 **/

extern FUNC(void, DCM_CODE) Dcm_DspInternal_DcmConfirmation(
  Dcm_IdContextType idContext, PduIdType dcmRxPduId, Dcm_ConfirmationStatusType status);

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/** \brief Start a segmented transmission of a response
 ** With this API, the application gives the complete response length to DCM nd starts PagedBuffer
 ** handling.
 ** Complete response length information (in bytes) is given in pMsgContext->resDataLen
 **
 ** \param[in] pMsgContext Message-related information for one diagnostic protocol identifier.
 **/
 extern FUNC(void, DCM_CODE) Dcm_DsdInternal_StartPagedProcessing(
  P2CONST(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Request transmission of filled page
 **
 ** \param[in] FilledPageLen By application filled size (in Bytes) of Page
 **/
extern FUNC(void, DCM_CODE) Dcm_DsdInternal_ProcessPage(PduLengthType FilledPageLen);

 /** \brief Function for updating the buffer used in Paged buffering mechanism
 **
 ** \param[in] PagedBufPtr Pointer to the buffer in which data is to be filled
 ** \param[in] PageLen Length of the buffer
 **/
extern FUNC(void, DCM_CODE) Dcm_DspInternal_UpdatePage(
    Dcm_MsgType PagedBufPtr,
    PduLengthType PageLen);

/** \brief DCM informs application, that processing of paged buffer was cancelled due to errors
 **/
extern FUNC(void, DCM_APPL_CODE) Dcm_DspInternal_CancelPagedBufferProcessing(void);
#endif

#if(DCM_DSP_USE_SERVICE_0X3E == STD_ON)
/** \brief Indicate Dcm module that client is still connected
** This service is used to keep diagnostic sessions alive which differ from the default session.
**
** \param[in] OpStatus Operation state of the function.
** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
**/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TesterPresent_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* (DCM_DSP_USE_SERVICE_0X3E == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X14 == STD_ON)
/** \brief Implement DEM access service 0x14
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearDiagnosticInformation_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* (DCM_DSP_USE_SERVICE_0X14 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X19 == STD_ON)
/** \brief Implement DEM access service 0x19-dispatcher
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDTCInformation_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if (DCM_0X19_0X01_SSVC_ENABLED == STD_ON)
/** \brief UDS service 0x19-0x01
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_reportNumberOfDTCByStatusMask_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if (DCM_0X19_0X01_SSVC_ENABLED == STD_ON)*/

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON)
/** \brief UDS service 0x19-0x02
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDTCByStatusMask_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x02 == STD_ON)*/

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)
/** \brief UDS service 0x19-0x03
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDtcSnapshotRecordIdentification_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x03 == STD_ON)*/


#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)
/** \brief UDS service 0x19-0x04
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDtcSnapshotRecordByDtcNumber_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x04 == STD_ON)*/

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)
/** \brief UDS service 0x19-x06
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportDtcExtendedDataRecordByDtcNumber_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x06 == STD_ON)*/

#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)
/** \brief UDS service 0x19-x0A
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportSupportedDtcs_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if (DCM_DSP_SUBSERVICE_READDTCINFORMATION_0x0A == STD_ON)*/
#endif /* (DCM_DSP_USE_SERVICE_0X19 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X27 == STD_ON)
/** \brief Provide a means of access data or diagnostic services, which restricted access for
 **        securtiy reasons.
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SecurityAccessControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* (DCM_DSP_USE_SERVICE_0X27 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X10 == STD_ON)
/** \brief Enable different diagnostic sessions on the Dcm
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

/** \brief Generic subservice handler for UDS service DiagnosticSessionControl (0x10)
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DiagnosticSessionControlCommon_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* (DCM_DSP_USE_SERVICE_0X10 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X31 == STD_ON)
/** \brief Provides a means to start, stop or obtain the results of a routine
 **        identified by a 2-byte routineIdentifier
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RoutineControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* (DCM_DSP_USE_SERVICE_0X31 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X11 == STD_ON)
/** \brief Provides a means to allow an external tester to request a server reset
 **
 ** \param[in] OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ECUReset_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON)
/** \brief UDS service 0x11-0x01
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_HardReset_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_DSP_SUBSERVICE_HARDRESET_0x01 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON)
/** \brief UDS service 0x11-0x02
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_KeyOffOnReset_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_DSP_SUBSERVICE_KEYOFFONRESET_0x02 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON)
/** \brief UDS service 0x11-0x03
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SoftReset_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_DSP_SUBSERVICE_SOFTRESET_0x03 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON)
/** \brief UDS service 0x11-0x04
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_EnableRapidPowerShutDown_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_DSP_SUBSERVICE_ENABLERAPIDPOWERSHUTDOWN_0x04 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON)
/** \brief UDS service 0x11-0x05
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DisableRapidPowerShutDown_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_DSP_SUBSERVICE_DISABLERAPIDPOWERSHUTDOWN_0x05 == STD_ON)*/
#endif /* (DCM_DSP_USE_SERVICE_0X11 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X2E == STD_ON)
/** \brief The generic service handler for UDS service 0x2E
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteDataByIdentifier_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_DSP_USE_SERVICE_0X2E == STD_ON) */

#if(DCM_0X23_SVC_ENABLED == STD_ON)
/** \brief The generic service handler for UDS service 0x23
 **
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 ** \param[in]    OpStatus Operation state of the function.
 **
 ** \retval DCM_PENDING           Operation did not complete, it must be called again
 ** \retval DCM_E_DONE            Operation completed
 **/
/* This is the generic service handler for UDS service 0x23 */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadMemoryByAddress_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_0X23_SVC_ENABLED == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X22 == STD_ON)
/** \brief The generic service handler for UDS service 0x22
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDataByIdentifier_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_DSP_USE_SERVICE_0X22 == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
/** \brief The generic service handler for UDS service 0x2F
 **
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 ** \param[in]    opState Operation state of the function.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_InputOutputControlByIdentifier_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext
  );

/** \brief Function to perform return control to ECU on Session Transition to default session
 **
 ** \param[inout] NONE
 ** \param[in]    NONE
 **/
extern FUNC(void, DCM_CODE) Dcm_DspInternal_ReturnControlToEcuforallSignals(void);

#endif /* #if(DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

#if(DCM_0X3D_SVC_ENABLED == STD_ON)
/** \brief The generic service handler for UDS service 0x3D
 **
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 ** \param[in]    OpStatus Operation state of the function.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 **/
/* This is the generic service handler for UDS service 0x3D */
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_WriteMemoryByAddress_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_0X3D_SVC_ENABLED == STD_ON) */

#if(DCM_DSP_USE_SERVICE_0X86 == STD_ON)

/** \brief The generic service handler for UDS service 0x86
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ResponseOnEvent_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 == STD_ON)
/** \brief UDS service 0x86-0x05
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StartROE_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x05 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 == STD_ON)
/** \brief UDS service 0x86-0x01
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnDTCStatusChange_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x01 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 == STD_ON)
/** \brief UDS service 0x86-0x03
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_OnChangeOfDataIdentifier_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x03 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04 == STD_ON)
/** \brief UDS service 0x86-0x04
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReportActivatedEvents_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x04 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 == STD_ON)
/** \brief UDS service 0x86-0x00
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_StopROE_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif/*#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x00 == STD_ON)*/

#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 == STD_ON)
/** \brief UDS service 0x86-0x06
 **
 ** \param[in]    OpStatus Operation state for internal Dcm Service function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ClearROE_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_DSP_SUBSERVICE_RESPONSEONEVENT_0x06 == STD_ON)*/
#endif /* #if(DCM_DSP_USE_SERVICE_0X86 == STD_ON) */

#if(DCM_0X85_SVC_ENABLED == STD_ON)
/** \brief The generic service handler for UDS service 0x85
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ControlDTCSetting_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_0X85_0X01_SSVC_ENABLED == STD_ON)
/** \brief UDS service 0x85-0x01
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DTCSettingTypeOn_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_0X85_0X01_SSVC_ENABLED == STD_ON)*/



#if(DCM_0X85_0X02_SSVC_ENABLED == STD_ON)
/** \brief UDS service 0x85-0x02
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DTCSettingTypeOff_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /*#if(DCM_0X85_0X02_SSVC_ENABLED == STD_ON)*/

#endif /* #if(DCM_0X85_SVC_ENABLED == STD_ON) */

#if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
/** \brief Handles Reading a signal for the services ReadDataByIdentifier(0x22),
           ResponseOnEvent(0x86) and InputOutputControlByIdentifier(0x2F)
 **
 ** \param[in] dataIndex Index of the Did in the table Dcm_DidTable
 ** \param[in] OpStatus Operation state for internal Dcm Service function
 ** \param[inout] didNvmReadDataSt Information related to NVM Read Data state
 ** \param[out] signalBuffer Pointer to where the data is read
 ** \param[out] nrc NRC occured due to read
 **
 ** \retval E_OK                Reading is ok
 ** \retval E_NOT_OK            Reading is not ok
 ** \retval DCM_E_PENDING       Operation did not complete, it must be called again
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_ReadDidSignalData(
  uint16 dataIndex,
  P2VAR(Dcm_DidAsynchSignalStType, AUTOMATIC, DCM_VAR) didNvmReadDataSt,
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) signalBuffer,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, AUTOMATIC) nrc,
  Dcm_OpStatusType OpStatus);
#endif /* #if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if(DCM_0X28_SVC_ENABLED == STD_ON)
/** \brief The generic service handler for UDS service 0x28
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 ** \retval DCM_E_FORCE_RCRRP  The DCM shall send an "response pending" immediately
 ** \retval DCM_E_PROCESS_PAGE One page is ready to be given to the PduR
 **/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_CommunicationControl_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_0X28_0X00_SSVC_ENABLED == STD_ON)
/** \brief The Internal service handler for UDS service 0x28-0x00
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **
 **/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_EnableRxAndTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_0X28_0X00_SSVC_ENABLED == STD_ON) */

#if(DCM_0X28_0X01_SSVC_ENABLED == STD_ON)
/** \brief The Internal service handler for UDS service 0x28-0x01
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **
 **/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_EnableRxAndDisableTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_0X28_0X01_SSVC_ENABLED == STD_ON) */

#if(DCM_0X28_0X02_SSVC_ENABLED == STD_ON)
/** \brief The Internal service handler for UDS service 0x28-0x02
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **
 **/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DisableRxAndEnableTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_0X28_0X02_SSVC_ENABLED == STD_ON) */

#if(DCM_0X28_0X03_SSVC_ENABLED == STD_ON)
/** \brief The Internal service handler for UDS service 0x28-0x03
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, it must be called again
 **
 **/

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_DisableRxAndTx_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_0X28_0X03_SSVC_ENABLED == STD_ON) */

#endif /* #if(DCM_0X28_SVC_ENABLED == STD_ON) */

#if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X31 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
/** \brief The function for copying any bits of data from a valid source buffer to valid
    destination buffer
 **
 ** \param[in] SourceBuffer Pointer to source buffer
 ** \param[in] SourceStartPosition Start bit position of data in source buffer
 ** \param[in] DestStartPosition Start bit position of data in destination buffer
 ** \param[in] SizeToCopy Size of data in bits
 ** \param[out] DestBuffer Pointer to destination buffer
 **
 **/
extern FUNC(void, DCM_CODE) Dcm_DspInternal_CopySignalData(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) SourceBuffer,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer,
  uint16 SourceStartPosition, uint16 DestStartPosition,
  uint16 SizeToCopy);

#endif /* #if ((DCM_DSP_USE_SERVICE_0X2E == STD_ON) || (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X31 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
     (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

#if (DCM_DSP_USE_SERVICE_0X31 == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspInternal_ShiftBitsInBuffer(
  P2VAR(Dcm_MsgItemType, AUTOMATIC, DCM_APPL_DATA) buffer,
  uint16 fromPosition, uint16 toPosition, uint16 noOfBits , boolean clearJunkBits);
#endif /* DCM_DSP_USE_SERVICE_0X31 == STD_ON  */

#if(DCM_0X34_SVC_ENABLED == STD_ON)

/** \brief The generic service handler for UDS service 0x34
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestDownloadHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_0X34_SVC_ENABLED == STD_ON) */

#if(DCM_0X35_SVC_ENABLED == STD_ON)

/** \brief The generic service handler for UDS service 0x35
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestUploadHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_0X35_SVC_ENABLED == STD_ON) */

#if(DCM_0X36_SVC_ENABLED == STD_ON)

/** \brief The generic service handler for UDS service 0x36
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransferDataHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_0X36_SVC_ENABLED == STD_ON) */

#if(DCM_0X37_SVC_ENABLED == STD_ON)

/** \brief The generic service handler for UDS service 0x37
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_RequestTransferExitHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_0X37_SVC_ENABLED == STD_ON) */

#if(DCM_0X87_SVC_ENABLED == STD_ON)

/** \brief The generic service handler for UDS service 0x87
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_LinkControlHandler_SvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON)

/** \brief The generic Subservice handler for UDS service 0x87-0x01
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, It must be called again.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_FixedBaudrateVerification_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);
#endif /* #if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x01 == STD_ON) */
#if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON)

/** \brief The generic Subservice handler for UDS service 0x87-0x02
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, It must be called again.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_SpecificBaudrateVerification_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x02 == STD_ON) */
#if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON)

/** \brief The generic Subservice handler for UDS service 0x87-0x03
 **
 ** \param[in]    OpStatus Operation state of the function.
 ** \param[inout] pMsgContext Message related information for one diagnsotic protocol identifier.
 **
 ** \retval DCM_E_DONE         Operation completed
 ** \retval DCM_E_PENDING      Operation did not complete, It must be called again.
 **/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_DspInternal_TransitionBaudrate_SSvcH(
  Dcm_OpStatusType OpStatus,
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext);

#endif /* #if(DCM_DSP_SUBSERVICE_LINKCONTROL_0x03 == STD_ON) */
#endif /* #if(DCM_DSP_USE_SERVICE_0X87 == STD_ON) */

/** \brief The function for handling the final ROE response up on expiry of eventWindowTime
 **
 ** \param[in]    instIdx Instance Index corresponding to ROE message.
 **
 **/
#if(DCM_ROE_ENABLED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_DspInternal_FinalRoeResponse(
  uint8 instIdx);

extern FUNC(void, DCM_CODE) Dcm_DspInternal_GetCommonDidSignalMask(
   uint16 DidIdx);
#endif /* #if(DCM_ROE_ENABLED == STD_ON) */


/** \brief  The function to release Rx and Tx buffers correspoding to a protocol instance
 **
 ** \param[in] instIdx The Instance Index for which rx and tx buffers need to be cleared.
 **
 **/
extern FUNC(void, DCM_CODE) Dcm_ReleaseRxTxBuffers(const uint8 instIdx);

#define DCM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]=============================================*/

/*==================[external constants]=========================================================*/

#define DCM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/** \brief Table of diagnostic sessions
 *
 * Configuration information of session states. **/
extern CONST(Dcm_SesTabConfigType, DCM_CONST) Dcm_SesTabConfig[DCM_NUM_PROTOCOL];

/** \brief Table of diagnostic security levels **/
extern CONST(Dcm_SecTabConfigType, DCM_CONST) Dcm_SecTabConfig;

/** \brief Global array holding the configuration for each reception(Rx) Pdu Id **/
extern CONST(Dcm_RxPduIdConfigType, DCM_CONST) Dcm_RxPduIdConfig[DCM_NUM_RX_PDU_ID];

/** \brief Global array holding the configuration information for each Main connection Tx Pdu Ids **/
extern CONST(Dcm_TxPduIdConfigType, DCM_CONST) Dcm_TxPduIds[DCM_NUM_TX_PDU_ID];

/** \brief Global array holding the configuration for TxPduIds, Protocols
 ** and HSM instances **/
extern CONST(Dcm_HsmConfigType, DCM_CONST) Dcm_HsmConfig[DCM_NUM_PROTOCOL];

/** \brief Global array holding the buffer configuration for each buffer **/
extern CONST(Dcm_BufferConfigType, DCM_CONST) Dcm_BufferConfig[DCM_NUM_BUFFER];

/** \brief Global array holding the buffer configuration for each NRC buffer **/
extern CONST(Dcm_BufferConfigType, DCM_CONST) Dcm_NRCBufferConfig[DCM_NUM_PROTOCOL];

#if (DCM_NUM_SID_TABLE > 0U)
/** \brief Global array holding the configuration for the service Id table **/
extern CONST(Dcm_SidTabConfigType, DCM_CONST) Dcm_SidTabConfig[DCM_NUM_SID_TABLE];
#endif

#if (DCM_NUM_SES_TAB_ENTRY > 0U)
/** \brief Global array holding the diagnostic session row configuration
 *
 * Holds configuration information of all available session states. **/
extern CONST(Dcm_SesTabEntryConfigType, DCM_CONST) Dcm_SesTabEntryConfig[DCM_NUM_SES_TAB_ENTRY];
#endif

#if (DCM_MODEDECLARATION_SUPPORT == STD_ON)
#if (DCM_NUM_COMCONTROL_ALL_CHANNEL > 0U)
/* Array of configuration information for Com Control All Channels */
extern CONST(Dcm_ComControlAllChannelType, DCM_CONST)
  Dcm_ComControlAllChannel[DCM_NUM_COMCONTROL_ALL_CHANNEL];
#endif

#if (DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL > 0U)
/* Array of configuration information for Com Control Specific Channels */
extern CONST(Dcm_ComControlSpecificChannelType, DCM_CONST)
  Dcm_ComControlSpecificChannel[DCM_NUM_COMCONTROL_SPECIFIC_CHANNEL];
#endif

#if (DCM_COMCONTROL_LOOKUP_SIZE > 0U)
/* Array of configuration information for Com Control lookup with Channels and SchM APIs */
extern CONST(Dcm_ComControlLookupType, DCM_CONST)
  Dcm_ComControlLookUpTable[DCM_COMCONTROL_LOOKUP_SIZE];
#endif
#endif  /* #if (DCM_MODEDECLARATION_SUPPORT == STD_ON) */

#if (DCM_DSP_PRECONF_ADDRESS_LENGTH_FORMATIDENTIFIER == STD_ON)
/** \brief Global array holding SupportedAddressAndLengthFormatIdentifier configuration
 *
 * Holds configuration information of all Supported AddressAndLengthFormatIdentifiers. **/
extern CONST(uint8, DCM_CONST)
  Dcm_SupportedAddAndLenFormatIds[DCM_NUM_ADDR_LENGTH_FORMAT_IDENTIFIER];
#endif

/*-----------------[DID Table]---------------------------------------*/
#if DCM_NUM_DID > 0
/** \brief Configuration of Dids */
extern CONST(Dcm_DidServicesType,DCM_CONST) Dcm_DidTable[DCM_NUM_DID];
#endif

#if DCM_NUM_DID_DATA > 0
/** \brief Configuration of Data Signals */
extern CONST(Dcm_DidDataType,DCM_CONST) Dcm_DidDataTable[DCM_NUM_DID_DATA];
#endif

#if (DCM_NUM_ROUTINES > 0U)
/** \brief Global array holding the configuration for each routines **/
extern CONST(Dcm_DspRoutineServicesType, DCM_CONST) Dcm_DspRoutineConfig[DCM_NUM_ROUTINES];
#endif

#if (DCM_NUM_ROUTINE_INFO > 0U)
/** \brief Global array holding the configuration information for each routines **/
extern CONST(Dcm_DspRoutineServicesInfoType, DCM_CONST)
       Dcm_DspRoutineInfoConfig[DCM_NUM_ROUTINE_INFO];
#endif

/*-----------------[Write/Read Memory Table]---------------------------------------*/
#if (DCM_NUM_MEMORY_IDINFO > 0U)
/** \brief Global array holding the configuration information for Writing/Reading memory **/
extern CONST(Dcm_MemoryIdInfoType,DCM_CONST) Dcm_MemoryIdInfoAndIdValueTable[DCM_NUM_MEMORY_IDINFO];
#endif

/*-----------------[ROE-PreConfiguration]------------------------------------*/
#if ((DCM_ROE_ENABLED == STD_ON) && (DCM_ROE_PRECONF_SUPPORT == STD_ON))
/** \brief Configuration of ROE event pre-configuration */
extern CONST(Dcm_RoeEventPreConfigType,DCM_CONST)
  Dcm_RoeEventPreConfiguration[DCM_NUM_PRECONF_EVENT];
#endif

#define DCM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/*==================[internal constants]=========================================================*/

/*==================[external data]==============================================================*/

#define DCM_START_SEC_VAR_INIT_8
#include <MemMap.h>

/** \brief Variable to hold DCM initialization state */
extern VAR(boolean, DCM_VAR) Dcm_Initialized;

#if (DCM_PAGEDBUFFER_ENABLED == STD_ON)
/** \brief Variable to hold Paged Buffer cancellation flag */
extern VAR(boolean, DCM_VAR) Dcm_CancelPagedProcessing;
#endif /* #if (DCM_PAGEDBUFFER_ENABLED == STD_ON) */

/** \brief Status of Request Process (True - Request ongoing, false - request completed) */
extern VAR(boolean, DCM_VAR) Dcm_ReqProcessing;

/** \brief Inhibts jumping to the BL to avoid ProgConditions corruption
          (TRUE - jump to BL not allowed, FALSE - jump to BL allowed) */
extern VAR(boolean, DCM_VAR) Dcm_InhibitJmpToBL;

#define DCM_STOP_SEC_VAR_INIT_8
#include <MemMap.h>

#define DCM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Variable to hold current protocol id. */
extern VAR(uint8, DCM_VAR) Dcm_CurProtocolId;

/** \brief Flag to enable/disable the diagnostic response transmission. */
extern VAR(boolean, DCM_VAR) Dcm_TxEnabled[DCM_NUM_CHANNELID];

/** \brief Flag to enable/disable the diagnostic request reception. */
extern VAR(boolean, DCM_VAR) Dcm_RxEnabled[DCM_NUM_CHANNELID];

/* If atlest one routine is configured */
#if (DCM_NUM_ROUTINES > 0U)

/** \brief Global array holding the status information of each routines **/
extern VAR(uint8, DCM_CONST) Dcm_DspRoutineStatus[DCM_NUM_ROUTINES];

#endif/* #if (DCM_NUM_ROUTINES > 0U) */

/** \brief Global variable holding the status information of LinkControl service Request Status **/
extern VAR(boolean, DCM_VAR) Dcm_DspLinkControlRequestStatus;

#if (DCM_ROE_ENABLED == STD_ON)
#if (DCM_INT_MANAGED_DIDS == STD_ON)
/** \brief Variable to holds status of ROE internal DID comparision for first time */
extern VAR(boolean, DCM_VAR) Dcm_ROEInternalDidsComparision;
#endif /* #if (DCM_INT_MANAGED_DIDS == STD_ON) */
#if (DCM_ROE_PERSISTENCE == STD_ON)
/** \brief Variable to holds status of ROE persistence Read memory */
extern VAR(boolean, DCM_VAR) Dcm_ROEPersistenceReadCall;
#endif /* #if (DCM_ROE_PERSISTENCE == STD_ON) */

/** \brief Global variable holding the PollingState of ROE (Idle,Postponed,Active) **/
extern VAR(uint8, DCM_VAR) Dcm_RoePollAsyncState;

#endif /* #if (DCM_ROE_ENABLED == STD_ON) */

/** \brief Variable holding states of Dcm Init after Jump to BL  **/
extern VAR(Dcm_BLInitStatusType, DCM_VAR) Dcm_BLInitStatus;

#define DCM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>

#if(DCM_ROE_ENABLED == STD_ON)

#define DCM_START_SEC_VAR_NO_INIT_16
#include <MemMap.h>

/** \brief Global variable holding the value of DcmDspRoeInterMessageTime **/
extern VAR(uint16, DCM_VAR) Dcm_RoeInterMsgTime;

#define DCM_STOP_SEC_VAR_NO_INIT_16
#include <MemMap.h>

#define DCM_START_SEC_VAR_NO_INIT_32
#include <MemMap.h>

/** \brief Global variable holding the value of eventWindowTime **/
extern VAR(uint32, DCM_VAR) Dcm_RoeEventWindowTime[2];

#define DCM_STOP_SEC_VAR_NO_INIT_32
#include <MemMap.h>

#endif/* #if(DCM_ROE_ENABLED == STD_ON) */


#define DCM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Status of ROE Processing (DCM_ROE_NONE -  No processing in progress
 * DCM_ROE_QUEUED - Processing enqueued, DCM_ROE_PROCESSING - Processing in progress)
 */
extern VAR(Dcm_ROEProcessingType, DCM_VAR) Dcm_ROEProcessing;

/** \brief Flag to enqueue ROE event */
extern VAR(Dcm_ROEEnqueueEventType, DCM_VAR) Dcm_ROEEnqueueEvent;

/** \brief Array holding the channel identifiers configured  **/
extern VAR(Dcm_ChannelTabEntryType, DCM_VAR) Dcm_ChannelId[DCM_NUM_CHANNELID];

#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>


#define DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief Global variable holding the value of RxPduId on which the request was received **/
extern VAR(PduIdType, DCM_VAR) Dcm_RxPduIdBL;

/** \brief Pointer to configuration of current active protocol. */
extern P2CONST(Dcm_HsmConfigType, DCM_VAR, DCM_CONST) Dcm_CurHsmConfig;

/** \brief Array to hold the status information for each diagnostic buffer */
extern VAR(Dcm_BufferInfoType, DCM_VAR) Dcm_BufferInfo[DCM_NUM_BUFFER];

/** \brief Array to hold the status information for each NRC buffer */
extern VAR(Dcm_BufferInfoType, DCM_VAR) Dcm_NRCBufferInfo[DCM_NUM_PROTOCOL];

#if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON))
 /** \brief Array to hold information regarding the processing of Services 0x22, 0x86 and 0x2F. */
extern VAR(Dcm_ReadDIDContextType, DCM_VAR) Dcm_ReadDIDContext[DCM_NUM_PROTOCOL];
#endif /* #if((DCM_DSP_USE_SERVICE_0X22 == STD_ON) || (DCM_DSP_USE_SERVICE_0X86 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)) */

/** \brief Array to hold the HSM information for each protocol. */
extern VAR(Dcm_HsmInfoType, DCM_VAR) Dcm_HsmInfo[DCM_NUM_PROTOCOL];

/** \brief Array to hold the status of a RxPduId */
extern VAR(Dcm_RxPduIdStateType, DCM_VAR) Dcm_RxPduIdState[DCM_NUM_RX_PDU_ID];

/** \brief Dcm_DataTransferContext is used to hold information regarding the processing of
 * the service RequestDownload(0x34),RequestUpload(0x35).*/
extern VAR(Dcm_DataTransferType, DCM_VAR) Dcm_DataTransferContext[DCM_NUM_PROTOCOL];

#if(DCM_DSP_USE_SERVICE_0X2F == STD_ON)
/** \brief Dcm_ReturnControlToEcuContext is used to hold information regarding the processing of
 * returning control to ECU for signals */
extern VAR(Dcm_IOReturnControlToEcuStatusType, DCM_VAR) Dcm_ReturnControlToEcuContext;
#endif

#if (DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE != 0U)
/** \brief RTE-Callback function pointer table for Manufacturer Notification */
extern CONST (Dcm_RteRequestNotificationType, DCM_CONST)
  Dcm_RteManufacturerNotificationTable[DCM_RTE_TABLE_REQUEST_MANUFACTURER_SIZE];
#endif

#if (DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE != 0U)
/** \brief RTE-Callback function pointer table for Supplier Notification */
extern CONST (Dcm_RteRequestNotificationType, DCM_CONST)
  Dcm_RteSupplierNotificationTable[DCM_RTE_TABLE_REQUEST_SUPPLIER_SIZE];
#endif

/** \brief Allows the integrator to store relevant information prior to jumping to bootloader  */
extern VAR(Dcm_ProgConditionsType, DCM_VAR) ProgConditions;


#if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
    (DCM_DSP_USE_SERVICE_0X2F == STD_ON)

extern VAR(Dcm_SignalBufferContextType, DCM_VAR) Dcm_SignalBufferContext;

#endif /* #if (DCM_DSP_USE_SERVICE_0X22 == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2E == STD_ON) || \
              (DCM_DSP_USE_SERVICE_0X2F == STD_ON) */

#define DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]==============================================================*/

/*==================[external function definitions]==============================================*/

/*==================[internal function definitions]==============================================*/

#endif /* if !defined( DCM_INT_H ) */
/*==================[end of file]================================================================*/
