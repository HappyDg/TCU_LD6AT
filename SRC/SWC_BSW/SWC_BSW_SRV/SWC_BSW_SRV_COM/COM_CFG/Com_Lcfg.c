
/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]============================================*/

#include <Com_Lcfg.h>
#include <Com_Lcfg_Static.h>
#include <TSAutosar.h>

/* start data section declaration */
#define COM_START_SEC_VAR_NOINIT_UNSPECIFIED
#include <MemMap.h>

/**
 * Internal memory statically allocated upon link-time. Size depends on
 * post build configuration. Memory requirements of post build configuration
 * must be smaller than COM_RAM_SIZE_MAX in order to avoid buffer
 * overflows. Memory is aligned to the the most stringent alignment requirement
 * of any simple data type available on the respective platform, e.g. uint32.
 */
STATIC TS_DefMaxAlignedByteArray(Com_DataMem, COM, VAR_NOINIT, COM_DATA_MEM_SIZE);

/* stop data section declaration */
#define COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
#include <MemMap.h>



/* start data section declaration */
#define COM_START_SEC_CONST_UNSPECIFIED
#include <MemMap.h>

/**
 * Pointer to statically allocated RAM.
 */
CONSTP2VAR(uint8, COM_CONST, COM_VAR_NOINIT) Com_gDataMemPtr =
  (P2VAR(uint8, COM_CONST, COM_VAR_NOINIT))
  ((P2VAR(void, COM_CONST, COM_VAR_NOINIT)) Com_DataMem);

/* stop data section declaration */
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include <MemMap.h>



#define COM_START_SEC_APPL_CODE
#include <MemMap.h>

/* send callouts */

/* receive callouts */

/* TX acknowledge callbacks */

/* TX timeout callbacks */

/* TX error callbacks */

/* RX timeout callbacks */
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAccrPedlRat_273R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGCrsCtrlCtrlActv_289R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGWhlSpdFrntLeRaw_529R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAbsCtrlActv_545R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAlgt_561R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGEngineSoakTime_609R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAmbAirTemp_641R(void);

/* RX acknowledge callbacks */
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAccrPedlRat_273R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGCrsCtrlCtrlActv_289R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGWhlSpdFrntLeRaw_529R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAbsCtrlActv_545R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAlgt_561R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGEngineSoakTime_609R(void);
extern FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAmbAirTemp_641R(void);

#define COM_STOP_SEC_APPL_CODE
#include <MemMap.h>

#define COM_START_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>


#if (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_TX_CALL_OUT_FUNC_PTR_ARRAY_SIZE > 0)
/* send callouts */
CONSTP2VAR(Com_TxCalloutType, AUTOMATIC, COM_APPL_CODE) Com_TxCallouts[COM_TX_CALL_OUT_FUNC_PTR_ARRAY_SIZE] =
{
};
#else /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE > 0) */
CONSTP2VAR(Com_TxCalloutType, AUTOMATIC, COM_APPL_CODE) Com_TxCallouts[1] =
{
    NULL_PTR
};
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE > 0) */


#if (COM_RX_CALL_OUT_FUNC_PTR_ARRAY_SIZE > 0)
/* receive callouts */
CONSTP2VAR(Com_RxCalloutType, AUTOMATIC, COM_APPL_CODE) Com_RxCallouts[COM_RX_CALL_OUT_FUNC_PTR_ARRAY_SIZE] =
{
};
#else /* (COM_RX_CALL_OUT_FUNC_PTR_ARRAY_SIZE > 0) */
CONSTP2VAR(Com_RxCalloutType, AUTOMATIC, COM_APPL_CODE) Com_RxCallouts[1] =
{
    NULL_PTR
};
#endif /* (COM_RX_CALL_OUT_FUNC_PTR_ARRAY_SIZE > 0) */
#endif /* (COM_CALL_OUT_FUNC_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_CBK_TX_ACK_PTR_ARRAY_SIZE > 0)
CONSTP2VAR(Com_CbkTxAck_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxAck_Array[COM_CBK_TX_ACK_PTR_ARRAY_SIZE] =
{
};
#else /* (COM_CBK_TX_ACK_PTR_ARRAY_SIZE > 0) */
CONSTP2VAR(Com_CbkTxAck_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxAck_Array[1] =
{
    NULL_PTR
};
#endif /* (COM_CBK_TX_ACK_PTR_ARRAY_SIZE > 0) */
#endif /* (COM_CBK_TX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_TX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_CBK_TX_T_OUT_ARRAY_SIZE > 0)
CONSTP2VAR(Com_CbkTxTOut_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxTOut_Array[COM_CBK_TX_T_OUT_ARRAY_SIZE] =
{
};
#else /* (COM_CBK_TX_T_OUT_ARRAY_SIZE > 0) */
CONSTP2VAR(Com_CbkTxTOut_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxTOut_Array[1] =
{
    NULL_PTR
};
#endif /* (COM_CBK_TX_T_OUT_ARRAY_SIZE > 0) */
#endif /* (COM_CBK_TX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_TX_ERR_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_CBK_TX_ERR_PTR_ARRAY_SIZE > 0)
CONSTP2VAR(Com_CbkTxErr_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxErr_Array[COM_CBK_TX_ERR_PTR_ARRAY_SIZE] =
{
};
#else /* (COM_CBK_TX_ERR_PTR_ARRAY_SIZE > 0) */
CONSTP2VAR(Com_CbkTxErr_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkTxErr_Array[1] =
{
    NULL_PTR
};
#endif /* (COM_CBK_TX_ERR_PTR_ARRAY_SIZE > 0) */
#endif /* (COM_CBK_TX_ERR_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_CBK_RX_ACK_PTR_ARRAY_SIZE > 0)
CONSTP2VAR(Com_CbkRxAck_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkRxAck_Array[COM_CBK_RX_ACK_PTR_ARRAY_SIZE] =
{
     &BSW_vidCbkRxAck_SGAccrPedlRat_273R
    ,&BSW_vidCbkRxAck_SGCrsCtrlCtrlActv_289R
    ,&BSW_vidCbkRxAck_SGWhlSpdFrntLeRaw_529R
    ,&BSW_vidCbkRxAck_SGAbsCtrlActv_545R
    ,&BSW_vidCbkRxAck_SGAlgt_561R
    ,&BSW_vidCbkRxAck_SGEngineSoakTime_609R
    ,&BSW_vidCbkRxAck_SGAmbAirTemp_641R
};
#else /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE > 0)) */
CONSTP2VAR(Com_CbkRxAck_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkRxAck_Array[1] =
{
    NULL_PTR
};
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE > 0)) */
#endif /* (COM_CBK_RX_ACK_PTR_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#if (COM_CBK_RX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE)
#if (COM_CBK_RX_T_OUT_ARRAY_SIZE > 0)
CONSTP2VAR(Com_CbkRxTOut_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkRxTOut_Array[COM_CBK_RX_T_OUT_ARRAY_SIZE] =
{
     &BSW_vidCbkRxTOut_SGAccrPedlRat_273R
    ,&BSW_vidCbkRxTOut_SGCrsCtrlCtrlActv_289R
    ,&BSW_vidCbkRxTOut_SGWhlSpdFrntLeRaw_529R
    ,&BSW_vidCbkRxTOut_SGAbsCtrlActv_545R
    ,&BSW_vidCbkRxTOut_SGAlgt_561R
    ,&BSW_vidCbkRxTOut_SGEngineSoakTime_609R
    ,&BSW_vidCbkRxTOut_SGAmbAirTemp_641R
};
#else /* (COM_CBK_RX_T_OUT_ARRAY_SIZE > 0) */
CONSTP2VAR(Com_CbkRxTOut_Type, AUTOMATIC, COM_RTE_CODE) Com_CbkRxTOut_Array[1] =
{
    NULL_PTR
};
#endif /* (COM_CBK_RX_T_OUT_ARRAY_SIZE > 0) */
#endif /* (COM_CBK_RX_T_OUT_ARRAY_SIZE_MAX != COM_INDEX_NONE) */


#define COM_STOP_CONFIG_DATA_UNSPECIFIED
#include <MemMap.h>


/* start data section declaration */
#define COM_START_SEC_CONST_32
#include <MemMap.h>

/**
 * Variable holding link-time configuration
 */
CONST(uint32, COM_CONST) Com_LcfgSignature = COM_LCFG_SIGNATURE;

/* stop data section declaration */
#define COM_STOP_SEC_CONST_32
#include <MemMap.h>

/** @} doxygen end group definition */
/*==================[end of file]===========================================*/
