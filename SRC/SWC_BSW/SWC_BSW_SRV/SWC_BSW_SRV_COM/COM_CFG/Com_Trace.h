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
#if (!defined COM_TRACE_H)
#define COM_TRACE_H
/*==================[inclusions]============================================*/



/*==================[macros]================================================*/

#ifndef DBG_COM_EB_CHECKVALUESIZEBOOLEAN_ENTRY
/** \brief Entry point of function Com_EB_CheckValueSizeBoolean() */
#define DBG_COM_EB_CHECKVALUESIZEBOOLEAN_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKVALUESIZEBOOLEAN_EXIT
/** \brief Exit point of function Com_EB_CheckValueSizeBoolean() */
#define DBG_COM_EB_CHECKVALUESIZEBOOLEAN_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_CHECKVALUESIZE8BIT_ENTRY
/** \brief Entry point of function Com_EB_CheckValueSize8Bit() */
#define DBG_COM_EB_CHECKVALUESIZE8BIT_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKVALUESIZE8BIT_EXIT
/** \brief Exit point of function Com_EB_CheckValueSize8Bit() */
#define DBG_COM_EB_CHECKVALUESIZE8BIT_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKVALUESIZE16BIT_ENTRY
/** \brief Entry point of function Com_EB_CheckValueSize16Bit() */
#define DBG_COM_EB_CHECKVALUESIZE16BIT_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKVALUESIZE16BIT_EXIT
/** \brief Exit point of function Com_EB_CheckValueSize16Bit() */
#define DBG_COM_EB_CHECKVALUESIZE16BIT_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKVALUESIZE32BIT_ENTRY
/** \brief Entry point of function Com_EB_CheckValueSize32Bit() */
#define DBG_COM_EB_CHECKVALUESIZE32BIT_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKVALUESIZE32BIT_EXIT
/** \brief Exit point of function Com_EB_CheckValueSize32Bit() */
#define DBG_COM_EB_CHECKVALUESIZE32BIT_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_TX2RXPOSINBYTE_ENTRY
/** \brief Entry point of function Com_EB_Tx2RxPosinByte() */
#define DBG_COM_EB_TX2RXPOSINBYTE_ENTRY(a)
#endif

#ifndef DBG_COM_EB_TX2RXPOSINBYTE_EXIT
/** \brief Exit point of function Com_EB_Tx2RxPosinByte() */
#define DBG_COM_EB_TX2RXPOSINBYTE_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_TX2RXPOSINBIT_ENTRY
/** \brief Entry point of function Com_EB_Tx2RxPosinBit() */
#define DBG_COM_EB_TX2RXPOSINBIT_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_TX2RXPOSINBIT_EXIT
/** \brief Exit point of function Com_EB_Tx2RxPosinBit() */
#define DBG_COM_EB_TX2RXPOSINBIT_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFFBOOL_ENTRY
/** \brief Entry point of function Com_EB_WriteToPduOrSBuffBool() */
#define DBG_COM_EB_WRITETOPDUORSBUFFBOOL_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFFBOOL_EXIT
/** \brief Exit point of function Com_EB_WriteToPduOrSBuffBool() */
#define DBG_COM_EB_WRITETOPDUORSBUFFBOOL_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF8BITUA_ENTRY
/** \brief Entry point of function Com_EB_WriteToPduOrSBuff8BitUA() */
#define DBG_COM_EB_WRITETOPDUORSBUFF8BITUA_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF8BITUA_EXIT
/** \brief Exit point of function Com_EB_WriteToPduOrSBuff8BitUA() */
#define DBG_COM_EB_WRITETOPDUORSBUFF8BITUA_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF8BIT_ENTRY
/** \brief Entry point of function Com_EB_WriteToPduOrSBuff8Bit() */
#define DBG_COM_EB_WRITETOPDUORSBUFF8BIT_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF8BIT_EXIT
/** \brief Exit point of function Com_EB_WriteToPduOrSBuff8Bit() */
#define DBG_COM_EB_WRITETOPDUORSBUFF8BIT_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF16BITUA_ENTRY
/** \brief Entry point of function Com_EB_WriteToPduOrSBuff16BitUA() */
#define DBG_COM_EB_WRITETOPDUORSBUFF16BITUA_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF16BITUA_EXIT
/** \brief Exit point of function Com_EB_WriteToPduOrSBuff16BitUA() */
#define DBG_COM_EB_WRITETOPDUORSBUFF16BITUA_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF16BIT_ENTRY
/** \brief Entry point of function Com_EB_WriteToPduOrSBuff16Bit() */
#define DBG_COM_EB_WRITETOPDUORSBUFF16BIT_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF16BIT_EXIT
/** \brief Exit point of function Com_EB_WriteToPduOrSBuff16Bit() */
#define DBG_COM_EB_WRITETOPDUORSBUFF16BIT_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF32BIT_ENTRY
/** \brief Entry point of function Com_EB_WriteToPduOrSBuff32Bit() */
#define DBG_COM_EB_WRITETOPDUORSBUFF32BIT_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFF32BIT_EXIT
/** \brief Exit point of function Com_EB_WriteToPduOrSBuff32Bit() */
#define DBG_COM_EB_WRITETOPDUORSBUFF32BIT_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFFBYTEARRAY_ENTRY
/** \brief Entry point of function Com_EB_WriteToPduOrSBuffByteArray() */
#define DBG_COM_EB_WRITETOPDUORSBUFFBYTEARRAY_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOPDUORSBUFFBYTEARRAY_EXIT
/** \brief Exit point of function Com_EB_WriteToPduOrSBuffByteArray() */
#define DBG_COM_EB_WRITETOPDUORSBUFFBYTEARRAY_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFUINT8_ENTRY
/** \brief Entry point of function Com_EB_ReadFromPduOrSBuffUint8() */
#define DBG_COM_EB_READFROMPDUORSBUFFUINT8_ENTRY(a)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFUINT8_EXIT
/** \brief Exit point of function Com_EB_ReadFromPduOrSBuffUint8() */
#define DBG_COM_EB_READFROMPDUORSBUFFUINT8_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFSINT8_ENTRY
/** \brief Entry point of function Com_EB_ReadFromPduOrSBuffSint8() */
#define DBG_COM_EB_READFROMPDUORSBUFFSINT8_ENTRY(a)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFSINT8_EXIT
/** \brief Exit point of function Com_EB_ReadFromPduOrSBuffSint8() */
#define DBG_COM_EB_READFROMPDUORSBUFFSINT8_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFUINT16_ENTRY
/** \brief Entry point of function Com_EB_ReadFromPduOrSBuffUint16() */
#define DBG_COM_EB_READFROMPDUORSBUFFUINT16_ENTRY(a)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFUINT16_EXIT
/** \brief Exit point of function Com_EB_ReadFromPduOrSBuffUint16() */
#define DBG_COM_EB_READFROMPDUORSBUFFUINT16_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFSINT16_ENTRY
/** \brief Entry point of function Com_EB_ReadFromPduOrSBuffSint16() */
#define DBG_COM_EB_READFROMPDUORSBUFFSINT16_ENTRY(a)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFSINT16_EXIT
/** \brief Exit point of function Com_EB_ReadFromPduOrSBuffSint16() */
#define DBG_COM_EB_READFROMPDUORSBUFFSINT16_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFUINT32_ENTRY
/** \brief Entry point of function Com_EB_ReadFromPduOrSBuffUint32() */
#define DBG_COM_EB_READFROMPDUORSBUFFUINT32_ENTRY(a)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFUINT32_EXIT
/** \brief Exit point of function Com_EB_ReadFromPduOrSBuffUint32() */
#define DBG_COM_EB_READFROMPDUORSBUFFUINT32_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFSINT32_ENTRY
/** \brief Entry point of function Com_EB_ReadFromPduOrSBuffSint32() */
#define DBG_COM_EB_READFROMPDUORSBUFFSINT32_ENTRY(a)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSBUFFSINT32_EXIT
/** \brief Exit point of function Com_EB_ReadFromPduOrSBuffSint32() */
#define DBG_COM_EB_READFROMPDUORSBUFFSINT32_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSHADOWBUFFER_ENTRY
/** \brief Entry point of function Com_EB_ReadFromPduOrShadowBuffer() */
#define DBG_COM_EB_READFROMPDUORSHADOWBUFFER_ENTRY(a)
#endif

#ifndef DBG_COM_EB_READFROMPDUORSHADOWBUFFER_EXIT
/** \brief Exit point of function Com_EB_ReadFromPduOrShadowBuffer() */
#define DBG_COM_EB_READFROMPDUORSHADOWBUFFER_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_CALCULATEFILTER_ENTRY
/** \brief Entry point of function Com_EB_CalculateFilter() */
#define DBG_COM_EB_CALCULATEFILTER_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CALCULATEFILTER_EXIT
/** \brief Exit point of function Com_EB_CalculateFilter() */
#define DBG_COM_EB_CALCULATEFILTER_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_SETBUFFERUINT32_ENTRY
/** \brief Entry point of function Com_EB_SetBufferUInt32() */
#define DBG_COM_EB_SETBUFFERUINT32_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_SETBUFFERUINT32_EXIT
/** \brief Exit point of function Com_EB_SetBufferUInt32() */
#define DBG_COM_EB_SETBUFFERUINT32_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOUPPERLAYER_ENTRY
/** \brief Entry point of function Com_EB_WriteToUpperLayer() */
#define DBG_COM_EB_WRITETOUPPERLAYER_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_WRITETOUPPERLAYER_EXIT
/** \brief Exit point of function Com_EB_WriteToUpperLayer() */
#define DBG_COM_EB_WRITETOUPPERLAYER_EXIT(a,b,c)
#endif

#ifndef DBG_COM_RESETFILERONEEVERYN_ENTRY
/** \brief Entry point of function Com_ResetFilerOneEveryN() */
#define DBG_COM_RESETFILERONEEVERYN_ENTRY(a)
#endif

#ifndef DBG_COM_RESETFILERONEEVERYN_EXIT
/** \brief Exit point of function Com_ResetFilerOneEveryN() */
#define DBG_COM_RESETFILERONEEVERYN_EXIT(a)
#endif

#ifndef DBG_COM_CLEARIPDUGROUPVECTOR_ENTRY
/** \brief Entry point of function Com_ClearIpduGroupVector() */
#define DBG_COM_CLEARIPDUGROUPVECTOR_ENTRY(a)
#endif

#ifndef DBG_COM_CLEARIPDUGROUPVECTOR_EXIT
/** \brief Exit point of function Com_ClearIpduGroupVector() */
#define DBG_COM_CLEARIPDUGROUPVECTOR_EXIT(a)
#endif

#ifndef DBG_COM_EB_HANDLEPDUGROUPRX_ENTRY
/** \brief Entry point of function Com_EB_HandlePduGroupRx() */
#define DBG_COM_EB_HANDLEPDUGROUPRX_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_HANDLEPDUGROUPRX_EXIT
/** \brief Exit point of function Com_EB_HandlePduGroupRx() */
#define DBG_COM_EB_HANDLEPDUGROUPRX_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_HANDLEPDUGROUPTX_ENTRY
/** \brief Entry point of function Com_EB_HandlePduGroupTx() */
#define DBG_COM_EB_HANDLEPDUGROUPTX_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_HANDLEPDUGROUPTX_EXIT
/** \brief Exit point of function Com_EB_HandlePduGroupTx() */
#define DBG_COM_EB_HANDLEPDUGROUPTX_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_CHECKIPDUGROUPVECTOR_ENTRY
/** \brief Entry point of function Com_EB_CheckIpduGroupVector() */
#define DBG_COM_EB_CHECKIPDUGROUPVECTOR_ENTRY(a)
#endif

#ifndef DBG_COM_EB_CHECKIPDUGROUPVECTOR_EXIT
/** \brief Exit point of function Com_EB_CheckIpduGroupVector() */
#define DBG_COM_EB_CHECKIPDUGROUPVECTOR_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_NOTIFYRECEIVERS_ENTRY
/** \brief Entry point of function Com_EB_NotifyReceivers() */
#define DBG_COM_EB_NOTIFYRECEIVERS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_NOTIFYRECEIVERS_EXIT
/** \brief Exit point of function Com_EB_NotifyReceivers() */
#define DBG_COM_EB_NOTIFYRECEIVERS_EXIT(a)
#endif

#ifndef DBG_COM_EB_HANDLERXIPDU_START_ENTRY
/** \brief Entry point of function Com_EB_HandleRxIPdu_Start() */
#define DBG_COM_EB_HANDLERXIPDU_START_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_HANDLERXIPDU_START_EXIT
/** \brief Exit point of function Com_EB_HandleRxIPdu_Start() */
#define DBG_COM_EB_HANDLERXIPDU_START_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_HANDLERXIPDU_ENABLERXDM_ENTRY
/** \brief Entry point of function Com_EB_HandleRxIPdu_EnableRxDM() */
#define DBG_COM_EB_HANDLERXIPDU_ENABLERXDM_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_HANDLERXIPDU_ENABLERXDM_EXIT
/** \brief Exit point of function Com_EB_HandleRxIPdu_EnableRxDM() */
#define DBG_COM_EB_HANDLERXIPDU_ENABLERXDM_EXIT(a,b)
#endif


#ifndef DBG_COM_EB_HANDLERXSIG_W_F_A_A_NOTI_ENTRY
/** \brief Entry point of function Com_EB_HandleRxSig_W_F_A_A_Noti() */
#define DBG_COM_EB_HANDLERXSIG_W_F_A_A_NOTI_ENTRY(a)
#endif

#ifndef DBG_COM_EB_HANDLERXSIG_W_F_A_A_NOTI_EXIT
/** \brief Exit point of function Com_EB_HandleRxSig_W_F_A_A_Noti() */
#define DBG_COM_EB_HANDLERXSIG_W_F_A_A_NOTI_EXIT(a)
#endif

#ifndef DBG_COM_EB_HANDLERXSIGNALSDMUBONLY_ENTRY
/** \brief Entry point of function Com_EB_HandleRxSignalsDMUBOnly() */
#define DBG_COM_EB_HANDLERXSIGNALSDMUBONLY_ENTRY(a)
#endif

#ifndef DBG_COM_EB_HANDLERXSIGNALSDMUBONLY_EXIT
/** \brief Exit point of function Com_EB_HandleRxSignalsDMUBOnly() */
#define DBG_COM_EB_HANDLERXSIGNALSDMUBONLY_EXIT(a)
#endif

#ifndef DBG_COM_EB_RXDMQUEUE_ENTRY
/** \brief Entry point of function Com_EB_RxDMQueue() */
#define DBG_COM_EB_RXDMQUEUE_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_RXDMQUEUE_EXIT
/** \brief Exit point of function Com_EB_RxDMQueue() */
#define DBG_COM_EB_RXDMQUEUE_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_HANDLERXIPDU_ENTRY
/** \brief Entry point of function Com_EB_HandleRxIPdu() */
#define DBG_COM_EB_HANDLERXIPDU_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_EB_HANDLERXIPDU_EXIT
/** \brief Exit point of function Com_EB_HandleRxIPdu() */
#define DBG_COM_EB_HANDLERXIPDU_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_HANDLERXSIGNALSWITHBUFFER_ENTRY
/** \brief Entry point of function Com_EB_HandleRxSignalsWithBuffer() */
#define DBG_COM_EB_HANDLERXSIGNALSWITHBUFFER_ENTRY(a)
#endif

#ifndef DBG_COM_EB_HANDLERXSIGNALSWITHBUFFER_EXIT
/** \brief Exit point of function Com_EB_HandleRxSignalsWithBuffer() */
#define DBG_COM_EB_HANDLERXSIGNALSWITHBUFFER_EXIT(a)
#endif

#ifndef DBG_COM_EB_HANDLERXSIGNALGROUPS_ENTRY
/** \brief Entry point of function Com_EB_HandleRxSignalGroups() */
#define DBG_COM_EB_HANDLERXSIGNALGROUPS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_HANDLERXSIGNALGROUPS_EXIT
/** \brief Exit point of function Com_EB_HandleRxSignalGroups() */
#define DBG_COM_EB_HANDLERXSIGNALGROUPS_EXIT(a)
#endif


#ifndef DBG_COM_EB_INITRXSIGNALSWITHFILTER_ENTRY
/** \brief Entry point of function Com_EB_InitRxSignalsWithFilter() */
#define DBG_COM_EB_INITRXSIGNALSWITHFILTER_ENTRY(a)
#endif

#ifndef DBG_COM_EB_INITRXSIGNALSWITHFILTER_EXIT
/** \brief Exit point of function Com_EB_InitRxSignalsWithFilter() */
#define DBG_COM_EB_INITRXSIGNALSWITHFILTER_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_INITRXIPDU_ENTRY
/** \brief Entry point of function Com_EB_InitRxIPdu() */
#define DBG_COM_EB_INITRXIPDU_ENTRY(a)
#endif

#ifndef DBG_COM_EB_INITRXIPDU_EXIT
/** \brief Exit point of function Com_EB_InitRxIPdu() */
#define DBG_COM_EB_INITRXIPDU_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALGOUPUPDATEBITANDDM_ENTRY
/** \brief Entry point of function Com_EB_CheckRxSignalGoupUpdateBitAndDM() */
#define DBG_COM_EB_CHECKRXSIGNALGOUPUPDATEBITANDDM_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALGOUPUPDATEBITANDDM_EXIT
/** \brief Exit point of function Com_EB_CheckRxSignalGoupUpdateBitAndDM() */
#define DBG_COM_EB_CHECKRXSIGNALGOUPUPDATEBITANDDM_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALUPDATEBITANDDM_ENTRY
/** \brief Entry point of function Com_EB_CheckRxSignalUpdateBitAndDM() */
#define DBG_COM_EB_CHECKRXSIGNALUPDATEBITANDDM_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALUPDATEBITANDDM_EXIT
/** \brief Exit point of function Com_EB_CheckRxSignalUpdateBitAndDM() */
#define DBG_COM_EB_CHECKRXSIGNALUPDATEBITANDDM_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_RXDMSIGNALGROUPQUEUE_ENTRY
/** \brief Entry point of function Com_EB_RxDMSignalGroupQueue() */
#define DBG_COM_EB_RXDMSIGNALGROUPQUEUE_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_RXDMSIGNALGROUPQUEUE_EXIT
/** \brief Exit point of function Com_EB_RxDMSignalGroupQueue() */
#define DBG_COM_EB_RXDMSIGNALGROUPQUEUE_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_RXDMSIGNALQUEUE_ENTRY
/** \brief Entry point of function Com_EB_RxDMSignalQueue() */
#define DBG_COM_EB_RXDMSIGNALQUEUE_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_RXDMSIGNALQUEUE_EXIT
/** \brief Exit point of function Com_EB_RxDMSignalQueue() */
#define DBG_COM_EB_RXDMSIGNALQUEUE_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_ENABLESIGNALBASEDDMFLAG_ENTRY
/** \brief Entry point of function Com_EB_EnableSignalBasedDMFlag() */
#define DBG_COM_EB_ENABLESIGNALBASEDDMFLAG_ENTRY(a)
#endif

#ifndef DBG_COM_EB_ENABLESIGNALBASEDDMFLAG_EXIT
/** \brief Exit point of function Com_EB_EnableSignalBasedDMFlag() */
#define DBG_COM_EB_ENABLESIGNALBASEDDMFLAG_EXIT(a)
#endif

#ifndef DBG_COM_EB_ENABLESIGNALGROUPBASEDDMFLAG_ENTRY
/** \brief Entry point of function Com_EB_EnableSignalGroupBasedDMFlag() */
#define DBG_COM_EB_ENABLESIGNALGROUPBASEDDMFLAG_ENTRY(a)
#endif

#ifndef DBG_COM_EB_ENABLESIGNALGROUPBASEDDMFLAG_EXIT
/** \brief Exit point of function Com_EB_EnableSignalGroupBasedDMFlag() */
#define DBG_COM_EB_ENABLESIGNALGROUPBASEDDMFLAG_EXIT(a)
#endif

#ifndef DBG_COM_EB_DISABLESIGNALANDSIGNALGROUPBASEDDMFLAG_ENTRY
/** \brief Entry point of function Com_EB_DisableSignalAndSignalGroupBasedDMFlag() */
#define DBG_COM_EB_DISABLESIGNALANDSIGNALGROUPBASEDDMFLAG_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_DISABLESIGNALANDSIGNALGROUPBASEDDMFLAG_EXIT
/** \brief Exit point of function Com_EB_DisableSignalAndSignalGroupBasedDMFlag() */
#define DBG_COM_EB_DISABLESIGNALANDSIGNALGROUPBASEDDMFLAG_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_SENDUPONSENDAPICALL_ENTRY
/** \brief Entry point of function Com_EB_SendUponSendApiCall() */
#define DBG_COM_EB_SENDUPONSENDAPICALL_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_SENDUPONSENDAPICALL_EXIT
/** \brief Exit point of function Com_EB_SendUponSendApiCall() */
#define DBG_COM_EB_SENDUPONSENDAPICALL_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_NTIMESSENDQUEUE_ENTRY
/** \brief Entry point of function Com_EB_NTimesSendQueue() */
#define DBG_COM_EB_NTIMESSENDQUEUE_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_NTIMESSENDQUEUE_EXIT
/** \brief Exit point of function Com_EB_NTimesSendQueue() */
#define DBG_COM_EB_NTIMESSENDQUEUE_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_CALCULATETM_ENTRY
/** \brief Entry point of function Com_EB_CalculateTM() */
#define DBG_COM_EB_CALCULATETM_ENTRY(a)
#endif

#ifndef DBG_COM_EB_CALCULATETM_EXIT
/** \brief Exit point of function Com_EB_CalculateTM() */
#define DBG_COM_EB_CALCULATETM_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_PERIODICSENDQUEUE_ENTRY
/** \brief Entry point of function Com_EB_PeriodicSendQueue() */
#define DBG_COM_EB_PERIODICSENDQUEUE_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_PERIODICSENDQUEUE_EXIT
/** \brief Exit point of function Com_EB_PeriodicSendQueue() */
#define DBG_COM_EB_PERIODICSENDQUEUE_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_SEND_PDU_ENTRY
/** \brief Entry point of function Com_EB_Send_Pdu() */
#define DBG_COM_EB_SEND_PDU_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_SEND_PDU_EXIT
/** \brief Exit point of function Com_EB_Send_Pdu() */
#define DBG_COM_EB_SEND_PDU_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_HANDLEMDT_ENTRY
/** \brief Entry point of function Com_EB_HandleMDT() */
#define DBG_COM_EB_HANDLEMDT_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_HANDLEMDT_EXIT
/** \brief Exit point of function Com_EB_HandleMDT() */
#define DBG_COM_EB_HANDLEMDT_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_HANDLETXIPDU_START_ENTRY
/** \brief Entry point of function Com_EB_HandleTxIPdu_Start() */
#define DBG_COM_EB_HANDLETXIPDU_START_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_HANDLETXIPDU_START_EXIT
/** \brief Exit point of function Com_EB_HandleTxIPdu_Start() */
#define DBG_COM_EB_HANDLETXIPDU_START_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_HANDLETXIPDU_STOP_ENTRY
/** \brief Entry point of function Com_EB_HandleTxIPdu_Stop() */
#define DBG_COM_EB_HANDLETXIPDU_STOP_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_HANDLETXIPDU_STOP_EXIT
/** \brief Exit point of function Com_EB_HandleTxIPdu_Stop() */
#define DBG_COM_EB_HANDLETXIPDU_STOP_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_CHECKTXIPDU_ENTRY
/** \brief Entry point of function Com_EB_CheckTxIpdu() */
#define DBG_COM_EB_CHECKTXIPDU_ENTRY(a)
#endif

#ifndef DBG_COM_EB_CHECKTXIPDU_EXIT
/** \brief Exit point of function Com_EB_CheckTxIpdu() */
#define DBG_COM_EB_CHECKTXIPDU_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_PDUBUFFER_ENTRY
/** \brief Entry point of function Com_EB_InitTxIPdu_PduBuffer() */
#define DBG_COM_EB_INITTXIPDU_PDUBUFFER_ENTRY(a)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_PDUBUFFER_EXIT
/** \brief Exit point of function Com_EB_InitTxIPdu_PduBuffer() */
#define DBG_COM_EB_INITTXIPDU_PDUBUFFER_EXIT(a)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_SIGNALGROUPS_ENTRY
/** \brief Entry point of function Com_EB_InitTxIPdu_SignalGroups() */
#define DBG_COM_EB_INITTXIPDU_SIGNALGROUPS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_SIGNALGROUPS_EXIT
/** \brief Exit point of function Com_EB_InitTxIPdu_SignalGroups() */
#define DBG_COM_EB_INITTXIPDU_SIGNALGROUPS_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_HANDLEFLAGS_ENTRY
/** \brief Entry point of function Com_EB_InitTxIPdu_HandleFlags() */
#define DBG_COM_EB_INITTXIPDU_HANDLEFLAGS_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_HANDLEFLAGS_EXIT
/** \brief Exit point of function Com_EB_InitTxIPdu_HandleFlags() */
#define DBG_COM_EB_INITTXIPDU_HANDLEFLAGS_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_SIGNALS_ENTRY
/** \brief Entry point of function Com_EB_InitTxIPdu_Signals() */
#define DBG_COM_EB_INITTXIPDU_SIGNALS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_SIGNALS_EXIT
/** \brief Exit point of function Com_EB_InitTxIPdu_Signals() */
#define DBG_COM_EB_INITTXIPDU_SIGNALS_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_GROUPSIGNALS_ENTRY
/** \brief Entry point of function Com_EB_InitTxIPdu_GroupSignals() */
#define DBG_COM_EB_INITTXIPDU_GROUPSIGNALS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_GROUPSIGNALS_EXIT
/** \brief Exit point of function Com_EB_InitTxIPdu_GroupSignals() */
#define DBG_COM_EB_INITTXIPDU_GROUPSIGNALS_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_STARTIPDU_ENTRY
/** \brief Entry point of function Com_EB_StartIPdu() */
#define DBG_COM_EB_STARTIPDU_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_STARTIPDU_EXIT
/** \brief Exit point of function Com_EB_StartIPdu() */
#define DBG_COM_EB_STARTIPDU_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_HANDLETXIPDU_ENTRY
/** \brief Entry point of function Com_EB_HandleTxIPdu() */
#define DBG_COM_EB_HANDLETXIPDU_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_EB_HANDLETXIPDU_EXIT
/** \brief Exit point of function Com_EB_HandleTxIPdu() */
#define DBG_COM_EB_HANDLETXIPDU_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_ENTRY
/** \brief Entry point of function Com_EB_InitTxIPdu() */
#define DBG_COM_EB_INITTXIPDU_ENTRY(a)
#endif

#ifndef DBG_COM_EB_INITTXIPDU_EXIT
/** \brief Exit point of function Com_EB_InitTxIPdu() */
#define DBG_COM_EB_INITTXIPDU_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_TXDMQUEUE_ENTRY
/** \brief Entry point of function Com_EB_TxDMQueue() */
#define DBG_COM_EB_TXDMQUEUE_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_TXDMQUEUE_EXIT
/** \brief Exit point of function Com_EB_TxDMQueue() */
#define DBG_COM_EB_TXDMQUEUE_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_TXDM_TMNONE_ENTRY
/** \brief Entry point of function Com_EB_TxDM_TMNone() */
#define DBG_COM_EB_TXDM_TMNONE_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_TXDM_TMNONE_EXIT
/** \brief Exit point of function Com_EB_TxDM_TMNone() */
#define DBG_COM_EB_TXDM_TMNONE_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_TXCONFIRMATIONS_ENTRY
/** \brief Entry point of function Com_EB_TxConfirmations() */
#define DBG_COM_EB_TXCONFIRMATIONS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_TXCONFIRMATIONS_EXIT
/** \brief Exit point of function Com_EB_TxConfirmations() */
#define DBG_COM_EB_TXCONFIRMATIONS_EXIT(a)
#endif

#ifndef DBG_COM_EB_CLEARTXUPDATEBITS_ENTRY
/** \brief Entry point of function Com_EB_ClearTxUpdateBits() */
#define DBG_COM_EB_CLEARTXUPDATEBITS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_CLEARTXUPDATEBITS_EXIT
/** \brief Exit point of function Com_EB_ClearTxUpdateBits() */
#define DBG_COM_EB_CLEARTXUPDATEBITS_EXIT(a)
#endif

#ifndef DBG_COM_EB_MDTQUEUE_ENTRY
/** \brief Entry point of function Com_EB_MdtQueue() */
#define DBG_COM_EB_MDTQUEUE_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_MDTQUEUE_EXIT
/** \brief Exit point of function Com_EB_MdtQueue() */
#define DBG_COM_EB_MDTQUEUE_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT8_ENTRY
/** \brief Entry point of function Com_EB_FilterAndWriteUint8() */
#define DBG_COM_EB_FILTERANDWRITEUINT8_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT8_EXIT
/** \brief Exit point of function Com_EB_FilterAndWriteUint8() */
#define DBG_COM_EB_FILTERANDWRITEUINT8_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT16_ENTRY
/** \brief Entry point of function Com_EB_FilterAndWriteUint16() */
#define DBG_COM_EB_FILTERANDWRITEUINT16_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT16_EXIT
/** \brief Exit point of function Com_EB_FilterAndWriteUint16() */
#define DBG_COM_EB_FILTERANDWRITEUINT16_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT32_ENTRY
/** \brief Entry point of function Com_EB_FilterAndWriteUint32() */
#define DBG_COM_EB_FILTERANDWRITEUINT32_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT32_EXIT
/** \brief Exit point of function Com_EB_FilterAndWriteUint32() */
#define DBG_COM_EB_FILTERANDWRITEUINT32_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITESINT8_ENTRY
/** \brief Entry point of function Com_EB_FilterAndWriteSint8() */
#define DBG_COM_EB_FILTERANDWRITESINT8_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITESINT8_EXIT
/** \brief Exit point of function Com_EB_FilterAndWriteSint8() */
#define DBG_COM_EB_FILTERANDWRITESINT8_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITESINT16_ENTRY
/** \brief Entry point of function Com_EB_FilterAndWriteSint16() */
#define DBG_COM_EB_FILTERANDWRITESINT16_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITESINT16_EXIT
/** \brief Exit point of function Com_EB_FilterAndWriteSint16() */
#define DBG_COM_EB_FILTERANDWRITESINT16_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITESINT32_ENTRY
/** \brief Entry point of function Com_EB_FilterAndWriteSint32() */
#define DBG_COM_EB_FILTERANDWRITESINT32_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITESINT32_EXIT
/** \brief Exit point of function Com_EB_FilterAndWriteSint32() */
#define DBG_COM_EB_FILTERANDWRITESINT32_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT8N_ENTRY
/** \brief Entry point of function Com_EB_FilterAndWriteUint8N() */
#define DBG_COM_EB_FILTERANDWRITEUINT8N_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERANDWRITEUINT8N_EXIT
/** \brief Exit point of function Com_EB_FilterAndWriteUint8N() */
#define DBG_COM_EB_FILTERANDWRITEUINT8N_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_SENDSIGNAL_FILTERANDWRITE_ENTRY
/** \brief Entry point of function Com_EB_SendSignal_FilterAndWrite() */
#define DBG_COM_EB_SENDSIGNAL_FILTERANDWRITE_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_EB_SENDSIGNAL_FILTERANDWRITE_EXIT
/** \brief Exit point of function Com_EB_SendSignal_FilterAndWrite() */
#define DBG_COM_EB_SENDSIGNAL_FILTERANDWRITE_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_COM_EB_SENDSIGNAL_ENTRY
/** \brief Entry point of function Com_EB_SendSignal() */
#define DBG_COM_EB_SENDSIGNAL_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_EB_SENDSIGNAL_EXIT
/** \brief Exit point of function Com_EB_SendSignal() */
#define DBG_COM_EB_SENDSIGNAL_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_COM_EB_UPDATESHADOWSIGNALSETTRIG_ENTRY
/** \brief Entry point of function Com_EB_UpdateShadowSignalSetTrig() */
#define DBG_COM_EB_UPDATESHADOWSIGNALSETTRIG_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_UPDATESHADOWSIGNALSETTRIG_EXIT
/** \brief Exit point of function Com_EB_UpdateShadowSignalSetTrig() */
#define DBG_COM_EB_UPDATESHADOWSIGNALSETTRIG_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_UPDATESHADOWSIGNAL_ENTRY
/** \brief Entry point of function Com_EB_UpdateShadowSignal() */
#define DBG_COM_EB_UPDATESHADOWSIGNAL_ENTRY(a,b,c)
#endif 

#ifndef DBG_COM_EB_UPDATESHADOWSIGNAL_EXIT
/** \brief Exit point of function Com_EB_UpdateShadowSignal() */
#define DBG_COM_EB_UPDATESHADOWSIGNAL_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_SENDSIGNALGROUP_ENTRY
/** \brief Entry point of function Com_EB_SendSignalGroup() */
#define DBG_COM_EB_SENDSIGNALGROUP_ENTRY(a,b,c)
#endif 

#ifndef DBG_COM_EB_SENDSIGNALGROUP_EXIT
/** \brief Exit point of function Com_EB_SendSignalGroup() */
#define DBG_COM_EB_SENDSIGNALGROUP_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_SENDSIGNALGROUPARRAY_ENTRY
/** \brief Entry point of function Com_EB_SendSignalGroupArray() */
#define DBG_COM_EB_SENDSIGNALGROUPARRAY_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_EB_SENDSIGNALGROUPARRAY_EXIT
/** \brief Exit point of function Com_EB_SendSignalGroupArray() */
#define DBG_COM_EB_SENDSIGNALGROUPARRAY_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_COM_EB_CALCULATESIGNALGROUPTM_ENTRY
/** \brief Entry point of function Com_EB_CalculateSignalGroupTM() */
#define DBG_COM_EB_CALCULATESIGNALGROUPTM_ENTRY(a,b,c)
#endif 

#ifndef DBG_COM_EB_CALCULATESIGNALGROUPTM_EXIT
/** \brief Exit point of function Com_EB_CalculateSignalGroupTM() */
#define DBG_COM_EB_CALCULATESIGNALGROUPTM_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_CALCULATESIGNALGROUPTMTX_ENTRY
/** \brief Entry point of function Com_EB_CalculateSignalGroupTMTx() */
#define DBG_COM_EB_CALCULATESIGNALGROUPTMTX_ENTRY(a,b,c)
#endif 

#ifndef DBG_COM_EB_CALCULATESIGNALGROUPTMTX_EXIT
/** \brief Exit point of function Com_EB_CalculateSignalGroupTMTx() */
#define DBG_COM_EB_CALCULATESIGNALGROUPTMTX_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_WRITESHADOWBUFFER_ENTRY
/** \brief Entry point of function Com_EB_WriteShadowBuffer() */
#define DBG_COM_EB_WRITESHADOWBUFFER_ENTRY(a,b,c)
#endif 

#ifndef DBG_COM_EB_WRITESHADOWBUFFER_EXIT
/** \brief Exit point of function Com_EB_WriteShadowBuffer() */
#define DBG_COM_EB_WRITESHADOWBUFFER_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_CALCULATEGROUPSIGNALTM_ENTRY
/** \brief Entry point of function Com_EB_CalculateGroupSignalTM() */
#define DBG_COM_EB_CALCULATEGROUPSIGNALTM_ENTRY(a,b,c,d)
#endif 

#ifndef DBG_COM_EB_CALCULATEGROUPSIGNALTM_EXIT
/** \brief Exit point of function Com_EB_CalculateGroupSignalTM() */
#define DBG_COM_EB_CALCULATEGROUPSIGNALTM_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_DEINIT_ENTRY
/** \brief Entry point of function Com_DeInit() */
#define DBG_COM_DEINIT_ENTRY()
#endif

#ifndef DBG_COM_DEINIT_EXIT
/** \brief Exit point of function Com_DeInit() */
#define DBG_COM_DEINIT_EXIT()
#endif

#ifndef DBG_COM_EB_FILTERONEEVERYN_ENTRY
/** \brief Entry point of function Com_EB_FilterOneEveryN() */
#define DBG_COM_EB_FILTERONEEVERYN_ENTRY(a)
#endif

#ifndef DBG_COM_EB_FILTERONEEVERYN_EXIT
/** \brief Exit point of function Com_EB_FilterOneEveryN() */
#define DBG_COM_EB_FILTERONEEVERYN_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_FILTERBOOLEAN_ENTRY
/** \brief Entry point of function Com_EB_FilterBoolean() */
#define DBG_COM_EB_FILTERBOOLEAN_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_FILTERBOOLEAN_EXIT
/** \brief Exit point of function Com_EB_FilterBoolean() */
#define DBG_COM_EB_FILTERBOOLEAN_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERUINT8_ENTRY
/** \brief Entry point of function Com_EB_FilterUint8() */
#define DBG_COM_EB_FILTERUINT8_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_FILTERUINT8_EXIT
/** \brief Exit point of function Com_EB_FilterUint8() */
#define DBG_COM_EB_FILTERUINT8_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERSINT8_ENTRY
/** \brief Entry point of function Com_EB_FilterSint8() */
#define DBG_COM_EB_FILTERSINT8_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_FILTERSINT8_EXIT
/** \brief Exit point of function Com_EB_FilterSint8() */
#define DBG_COM_EB_FILTERSINT8_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERUINT16_ENTRY
/** \brief Entry point of function Com_EB_FilterUint16() */
#define DBG_COM_EB_FILTERUINT16_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_FILTERUINT16_EXIT
/** \brief Exit point of function Com_EB_FilterUint16() */
#define DBG_COM_EB_FILTERUINT16_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERSINT16_ENTRY
/** \brief Entry point of function Com_EB_FilterSint16() */
#define DBG_COM_EB_FILTERSINT16_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_FILTERSINT16_EXIT
/** \brief Exit point of function Com_EB_FilterSint16() */
#define DBG_COM_EB_FILTERSINT16_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERUINT32_ENTRY
/** \brief Entry point of function Com_EB_FilterUint32() */
#define DBG_COM_EB_FILTERUINT32_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_FILTERUINT32_EXIT
/** \brief Exit point of function Com_EB_FilterUint32() */
#define DBG_COM_EB_FILTERUINT32_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_FILTERSINT32_ENTRY
/** \brief Entry point of function Com_EB_FilterSint32() */
#define DBG_COM_EB_FILTERSINT32_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_FILTERSINT32_EXIT
/** \brief Exit point of function Com_EB_FilterSint32() */
#define DBG_COM_EB_FILTERSINT32_EXIT(a,b,c)
#endif

#ifndef DBG_COM_GETCONFIGURATIONID_ENTRY
/** \brief Entry point of function Com_GetConfigurationId() */
#define DBG_COM_GETCONFIGURATIONID_ENTRY()
#endif

#ifndef DBG_COM_GETCONFIGURATIONID_EXIT
/** \brief Exit point of function Com_GetConfigurationId() */
#define DBG_COM_GETCONFIGURATIONID_EXIT(a)
#endif

#ifndef DBG_COM_GETSTATUS_ENTRY
/** \brief Entry point of function Com_GetStatus() */
#define DBG_COM_GETSTATUS_ENTRY()
#endif

#ifndef DBG_COM_GETSTATUS_EXIT
/** \brief Exit point of function Com_GetStatus() */
#define DBG_COM_GETSTATUS_EXIT(a)
#endif

#ifndef DBG_COM_INIT_ENTRY
/** \brief Entry point of function Com_Init() */
#define DBG_COM_INIT_ENTRY(a)
#endif

#ifndef DBG_COM_INIT_EXIT
/** \brief Exit point of function Com_Init() */
#define DBG_COM_INIT_EXIT(a)
#endif

#ifndef DBG_COM_IPDUGROUPCONTROL_ENTRY
/** \brief Entry point of function Com_IpduGroupControl() */
#define DBG_COM_IPDUGROUPCONTROL_ENTRY(a,b)
#endif

#ifndef DBG_COM_IPDUGROUPCONTROL_EXIT
/** \brief Exit point of function Com_IpduGroupControl() */
#define DBG_COM_IPDUGROUPCONTROL_EXIT(a,b)
#endif

#ifndef DBG_COM_ISVALIDCONFIG_ENTRY
/** \brief Entry point of function Com_IsValidConfig() */
#define DBG_COM_ISVALIDCONFIG_ENTRY(a)
#endif

#ifndef DBG_COM_ISVALIDCONFIG_EXIT
/** \brief Exit point of function Com_IsValidConfig() */
#define DBG_COM_ISVALIDCONFIG_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_ROUTESIGNALHELPER_ENTRY
/** \brief Entry point of function Com_EB_RouteSignalHelper() */
#define DBG_COM_EB_ROUTESIGNALHELPER_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_ROUTESIGNALHELPER_EXIT
/** \brief Exit point of function Com_EB_RouteSignalHelper() */
#define DBG_COM_EB_ROUTESIGNALHELPER_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_SETGROUPSIGNALTMSFLAGOFSIGNALGROUP_ENTRY
/** \brief Entry point of function Com_EB_SetGroupSignalTMSFlagOfSignalGroup() */
#define DBG_COM_EB_SETGROUPSIGNALTMSFLAGOFSIGNALGROUP_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_SETGROUPSIGNALTMSFLAGOFSIGNALGROUP_EXIT
/** \brief Exit point of function Com_EB_SetGroupSignalTMSFlagOfSignalGroup() */
#define DBG_COM_EB_SETGROUPSIGNALTMSFLAGOFSIGNALGROUP_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_ROUTESIGNALGROUP_ENTRY
/** \brief Entry point of function Com_EB_RouteSignalGroup() */
#define DBG_COM_EB_ROUTESIGNALGROUP_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_ROUTESIGNALGROUP_EXIT
/** \brief Exit point of function Com_EB_RouteSignalGroup() */
#define DBG_COM_EB_ROUTESIGNALGROUP_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_ROUTESIGNAL_ENTRY
/** \brief Entry point of function Com_EB_RouteSignal() */
#define DBG_COM_EB_ROUTESIGNAL_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_ROUTESIGNAL_EXIT
/** \brief Exit point of function Com_EB_RouteSignal() */
#define DBG_COM_EB_ROUTESIGNAL_EXIT(a,b)
#endif

#ifndef DBG_COM_MAINFUNCTIONROUTESIGNALS_ENTRY
/** \brief Entry point of function Com_MainFunctionRouteSignals() */
#define DBG_COM_MAINFUNCTIONROUTESIGNALS_ENTRY()
#endif

#ifndef DBG_COM_MAINFUNCTIONROUTESIGNALS_EXIT
/** \brief Exit point of function Com_MainFunctionRouteSignals() */
#define DBG_COM_MAINFUNCTIONROUTESIGNALS_EXIT()
#endif

#ifndef DBG_COM_EB_CHECKRXDMTABLE_ENTRY
/** \brief Entry point of function Com_EB_CheckRxDMTable() */
#define DBG_COM_EB_CHECKRXDMTABLE_ENTRY()
#endif

#ifndef DBG_COM_EB_CHECKRXDMTABLE_EXIT
/** \brief Exit point of function Com_EB_CheckRxDMTable() */
#define DBG_COM_EB_CHECKRXDMTABLE_EXIT()
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALDMTABLE_ENTRY
/** \brief Entry point of function Com_EB_CheckRxSignalDMTable() */
#define DBG_COM_EB_CHECKRXSIGNALDMTABLE_ENTRY()
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALDMTABLE_EXIT
/** \brief Exit point of function Com_EB_CheckRxSignalDMTable() */
#define DBG_COM_EB_CHECKRXSIGNALDMTABLE_EXIT()
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALGROUPDMTABLE_ENTRY
/** \brief Entry point of function Com_EB_CheckRxSignalGroupDMTable() */
#define DBG_COM_EB_CHECKRXSIGNALGROUPDMTABLE_ENTRY()
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALGROUPDMTABLE_EXIT
/** \brief Exit point of function Com_EB_CheckRxSignalGroupDMTable() */
#define DBG_COM_EB_CHECKRXSIGNALGROUPDMTABLE_EXIT()
#endif

#ifndef DBG_COM_MAINFUNCTIONRX_ENTRY
/** \brief Entry point of function Com_MainFunctionRx() */
#define DBG_COM_MAINFUNCTIONRX_ENTRY()
#endif

#ifndef DBG_COM_MAINFUNCTIONRX_EXIT
/** \brief Exit point of function Com_MainFunctionRx() */
#define DBG_COM_MAINFUNCTIONRX_EXIT()
#endif

#ifndef DBG_COM_EB_CHECKTMSFORPDU_ENTRY
/** \brief Entry point of function Com_EB_CheckTMSforPdu() */
#define DBG_COM_EB_CHECKTMSFORPDU_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKTMSFORPDU_EXIT
/** \brief Exit point of function Com_EB_CheckTMSforPdu() */
#define DBG_COM_EB_CHECKTMSFORPDU_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_TMSWITCH_ENTRY
/** \brief Entry point of function Com_EB_TMSwitch() */
#define DBG_COM_EB_TMSWITCH_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_EB_TMSWITCH_EXIT
/** \brief Exit point of function Com_EB_TMSwitch() */
#define DBG_COM_EB_TMSWITCH_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_EB_CHECKPERIODICSENDFORPDU_ENTRY
/** \brief Entry point of function Com_EB_CheckPeriodicSendforPdu() */
#define DBG_COM_EB_CHECKPERIODICSENDFORPDU_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKPERIODICSENDFORPDU_EXIT
/** \brief Exit point of function Com_EB_CheckPeriodicSendforPdu() */
#define DBG_COM_EB_CHECKPERIODICSENDFORPDU_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKNTIMESSENDFORPDU_ENTRY
/** \brief Entry point of function Com_EB_CheckNTimesSendforPdu() */
#define DBG_COM_EB_CHECKNTIMESSENDFORPDU_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKNTIMESSENDFORPDU_EXIT
/** \brief Exit point of function Com_EB_CheckNTimesSendforPdu() */
#define DBG_COM_EB_CHECKNTIMESSENDFORPDU_EXIT(a,b,c)
#endif

#ifndef DBG_COM_EB_CHECKMDTFORPDU_ENTRY
/** \brief Entry point of function Com_EB_CheckMdtforPdu() */
#define DBG_COM_EB_CHECKMDTFORPDU_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKMDTFORPDU_EXIT
/** \brief Exit point of function Com_EB_CheckMdtforPdu() */
#define DBG_COM_EB_CHECKMDTFORPDU_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_CHECKTXDMFORPDU_ENTRY
/** \brief Entry point of function Com_EB_CheckTxDMforPdu() */
#define DBG_COM_EB_CHECKTXDMFORPDU_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_CHECKTXDMFORPDU_EXIT
/** \brief Exit point of function Com_EB_CheckTxDMforPdu() */
#define DBG_COM_EB_CHECKTXDMFORPDU_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_HANDLEDEFERREDTXCONFIRM_ENTRY
/** \brief Entry point of function Com_EB_HandleDeferredTxConfirm() */
#define DBG_COM_EB_HANDLEDEFERREDTXCONFIRM_ENTRY(a)
#endif

#ifndef DBG_COM_EB_HANDLEDEFERREDTXCONFIRM_EXIT
/** \brief Exit point of function Com_EB_HandleDeferredTxConfirm() */
#define DBG_COM_EB_HANDLEDEFERREDTXCONFIRM_EXIT(a)
#endif

#ifndef DBG_COM_EB_HANDLE_SEND_PDU_ENTRY
/** \brief Entry point of function Com_EB_Handle_Send_Pdu() */
#define DBG_COM_EB_HANDLE_SEND_PDU_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_EB_HANDLE_SEND_PDU_EXIT
/** \brief Exit point of function Com_EB_Handle_Send_Pdu() */
#define DBG_COM_EB_HANDLE_SEND_PDU_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_MAINFUNCTIONTX_ENTRY
/** \brief Entry point of function Com_MainFunctionTx() */
#define DBG_COM_MAINFUNCTIONTX_ENTRY()
#endif

#ifndef DBG_COM_MAINFUNCTIONTX_EXIT
/** \brief Exit point of function Com_MainFunctionTx() */
#define DBG_COM_MAINFUNCTIONTX_EXIT()
#endif

#ifndef DBG_COM_RECEIVESHADOWSIGNAL_ENTRY
/** \brief Entry point of function Com_ReceiveShadowSignal() */
#define DBG_COM_RECEIVESHADOWSIGNAL_ENTRY(a,b)
#endif

#ifndef DBG_COM_RECEIVESHADOWSIGNAL_EXIT
/** \brief Exit point of function Com_ReceiveShadowSignal() */
#define DBG_COM_RECEIVESHADOWSIGNAL_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_BOOLEAN_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Boolean() */
#define DBG_COM_EB_READVALUE_BOOLEAN_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_BOOLEAN_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Boolean() */
#define DBG_COM_EB_READVALUE_BOOLEAN_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT8_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Uint8() */
#define DBG_COM_EB_READVALUE_UINT8_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT8_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Uint8() */
#define DBG_COM_EB_READVALUE_UINT8_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT16_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Uint16() */
#define DBG_COM_EB_READVALUE_UINT16_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT16_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Uint16() */
#define DBG_COM_EB_READVALUE_UINT16_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT32_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Uint32() */
#define DBG_COM_EB_READVALUE_UINT32_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT32_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Uint32() */
#define DBG_COM_EB_READVALUE_UINT32_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_SINT8_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Sint8() */
#define DBG_COM_EB_READVALUE_SINT8_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_SINT8_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Sint8() */
#define DBG_COM_EB_READVALUE_SINT8_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_SINT16_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Sint16() */
#define DBG_COM_EB_READVALUE_SINT16_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_SINT16_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Sint16() */
#define DBG_COM_EB_READVALUE_SINT16_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_SINT32_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Sint32() */
#define DBG_COM_EB_READVALUE_SINT32_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_SINT32_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Sint32() */
#define DBG_COM_EB_READVALUE_SINT32_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT8N_ENTRY
/** \brief Entry point of function Com_EB_ReadValue_Uint8N() */
#define DBG_COM_EB_READVALUE_UINT8N_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_UINT8N_EXIT
/** \brief Exit point of function Com_EB_ReadValue_Uint8N() */
#define DBG_COM_EB_READVALUE_UINT8N_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_ENTRY
/** \brief Entry point of function Com_EB_ReadValue() */
#define DBG_COM_EB_READVALUE_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_READVALUE_EXIT
/** \brief Exit point of function Com_EB_ReadValue() */
#define DBG_COM_EB_READVALUE_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALDM_ENTRY
/** \brief Entry point of function Com_EB_CheckRxSignalDM() */
#define DBG_COM_EB_CHECKRXSIGNALDM_ENTRY()
#endif

#ifndef DBG_COM_EB_CHECKRXSIGNALDM_EXIT
/** \brief Exit point of function Com_EB_CheckRxSignalDM() */
#define DBG_COM_EB_CHECKRXSIGNALDM_EXIT(a)
#endif

#ifndef DBG_COM_RECEIVESIGNALGENERIC_ENTRY
/** \brief Entry point of function Com_ReceiveSignalGeneric() */
#define DBG_COM_RECEIVESIGNALGENERIC_ENTRY(a,b)
#endif

#ifndef DBG_COM_RECEIVESIGNALGENERIC_EXIT
/** \brief Exit point of function Com_ReceiveSignalGeneric() */
#define DBG_COM_RECEIVESIGNALGENERIC_EXIT(a,b,c)
#endif

#ifndef DBG_COM_RECEIVESIGNALGROUP_ENTRY
/** \brief Entry point of function Com_ReceiveSignalGroup() */
#define DBG_COM_RECEIVESIGNALGROUP_ENTRY(a)
#endif

#ifndef DBG_COM_RECEIVESIGNALGROUP_EXIT
/** \brief Exit point of function Com_ReceiveSignalGroup() */
#define DBG_COM_RECEIVESIGNALGROUP_EXIT(a,b)
#endif

#ifndef DBG_COM_RECEIVESIGNALGROUPARRAY_ENTRY
/** \brief Entry point of function Com_ReceiveSignalGroupArray() */
#define DBG_COM_RECEIVESIGNALGROUPARRAY_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_RECEIVESIGNALGROUPARRAY_EXIT
/** \brief Exit point of function Com_ReceiveSignalGroupArray() */
#define DBG_COM_RECEIVESIGNALGROUPARRAY_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_RECEPTIONDMCONTROL_ENTRY
/** \brief Entry point of function Com_ReceptionDMControl() */
#define DBG_COM_RECEPTIONDMCONTROL_ENTRY(a)
#endif

#ifndef DBG_COM_RECEPTIONDMCONTROL_EXIT
/** \brief Exit point of function Com_ReceptionDMControl() */
#define DBG_COM_RECEPTIONDMCONTROL_EXIT(a)
#endif

#ifndef DBG_COM_EB_HANDLERXCONFIRM_ENTRY
/** \brief Entry point of function Com_EB_HandleRxConfirm() */
#define DBG_COM_EB_HANDLERXCONFIRM_ENTRY(a)
#endif

#ifndef DBG_COM_EB_HANDLERXCONFIRM_EXIT
/** \brief Exit point of function Com_EB_HandleRxConfirm() */
#define DBG_COM_EB_HANDLERXCONFIRM_EXIT(a)
#endif

#ifndef DBG_COM_RXINDICATION_ENTRY
/** \brief Entry point of function Com_RxIndication() */
#define DBG_COM_RXINDICATION_ENTRY(a,b)
#endif

#ifndef DBG_COM_RXINDICATION_EXIT
/** \brief Exit point of function Com_RxIndication() */
#define DBG_COM_RXINDICATION_EXIT(a,b)
#endif

#ifndef DBG_COM_SENDSIGNAL_ENTRY
/** \brief Entry point of function Com_SendSignal() */
#define DBG_COM_SENDSIGNAL_ENTRY(a,b)
#endif

#ifndef DBG_COM_SENDSIGNAL_EXIT
/** \brief Exit point of function Com_SendSignal() */
#define DBG_COM_SENDSIGNAL_EXIT(a,b,c)
#endif

#ifndef DBG_COM_SENDSIGNALGROUP_ENTRY
/** \brief Entry point of function Com_SendSignalGroup() */
#define DBG_COM_SENDSIGNALGROUP_ENTRY(a)
#endif

#ifndef DBG_COM_SENDSIGNALGROUP_EXIT
/** \brief Exit point of function Com_SendSignalGroup() */
#define DBG_COM_SENDSIGNALGROUP_EXIT(a,b)
#endif

#ifndef DBG_COM_SENDSIGNALGROUPARRAY_ENTRY
/** \brief Entry point of function Com_SendSignalGroupArray() */
#define DBG_COM_SENDSIGNALGROUPARRAY_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_SENDSIGNALGROUPARRAY_EXIT
/** \brief Exit point of function Com_SendSignalGroupArray() */
#define DBG_COM_SENDSIGNALGROUPARRAY_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_SETIPDUGROUP_ENTRY
/** \brief Entry point of function Com_SetIpduGroup() */
#define DBG_COM_SETIPDUGROUP_ENTRY(a,b,c)
#endif

#ifndef DBG_COM_SETIPDUGROUP_EXIT
/** \brief Exit point of function Com_SetIpduGroup() */
#define DBG_COM_SETIPDUGROUP_EXIT(a,b,c)
#endif

#ifndef DBG_COM_SWITCHIPDUTXMODE_ENTRY
/** \brief Entry point of function Com_SwitchIpduTxMode() */
#define DBG_COM_SWITCHIPDUTXMODE_ENTRY(a,b)
#endif

#ifndef DBG_COM_SWITCHIPDUTXMODE_EXIT
/** \brief Exit point of function Com_SwitchIpduTxMode() */
#define DBG_COM_SWITCHIPDUTXMODE_EXIT(a,b)
#endif

#ifndef DBG_COM_TRIGGERIPDUSEND_ENTRY
/** \brief Entry point of function Com_TriggerIPDUSend() */
#define DBG_COM_TRIGGERIPDUSEND_ENTRY(a)
#endif

#ifndef DBG_COM_TRIGGERIPDUSEND_EXIT
/** \brief Exit point of function Com_TriggerIPDUSend() */
#define DBG_COM_TRIGGERIPDUSEND_EXIT(a)
#endif

#ifndef DBG_COM_TRIGGERTRANSMIT_ENTRY
/** \brief Entry point of function Com_TriggerTransmit() */
#define DBG_COM_TRIGGERTRANSMIT_ENTRY(a,b)
#endif

#ifndef DBG_COM_TRIGGERTRANSMIT_EXIT
/** \brief Exit point of function Com_TriggerTransmit() */
#define DBG_COM_TRIGGERTRANSMIT_EXIT(a,b,c)
#endif

#ifndef DBG_COM_TXCONFIRMATION_ENTRY
/** \brief Entry point of function Com_TxConfirmation() */
#define DBG_COM_TXCONFIRMATION_ENTRY(a)
#endif

#ifndef DBG_COM_TXCONFIRMATION_EXIT
/** \brief Exit point of function Com_TxConfirmation() */
#define DBG_COM_TXCONFIRMATION_EXIT(a)
#endif

#ifndef DBG_COM_UPDATESHADOWSIGNAL_ENTRY
/** \brief Entry point of function Com_UpdateShadowSignal() */
#define DBG_COM_UPDATESHADOWSIGNAL_ENTRY(a,b)
#endif

#ifndef DBG_COM_UPDATESHADOWSIGNAL_EXIT
/** \brief Exit point of function Com_UpdateShadowSignal() */
#define DBG_COM_UPDATESHADOWSIGNAL_EXIT(a,b)
#endif

#ifndef DBG_COM_RECEIVESIGNALGROUP_REPLACE_ENTRY
/** \brief Entry point of function Com_ReceiveSignalGroup_Replace() */
#define DBG_COM_RECEIVESIGNALGROUP_REPLACE_ENTRY(a,b)
#endif

#ifndef DBG_COM_RECEIVESIGNALGROUP_REPLACE_EXIT
/** \brief Exit point of function Com_ReceiveSignalGroup_Replace() */
#define DBG_COM_RECEIVESIGNALGROUP_REPLACE_EXIT(a,b,c)
#endif

#ifndef DBG_COM_SETUPRXSIGNALGROUP_ENTRY
/** \brief Entry point of function Com_SetupRxSignalGroup() */
#define DBG_COM_SETUPRXSIGNALGROUP_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_SETUPRXSIGNALGROUP_EXIT
/** \brief Exit point of function Com_SetupRxSignalGroup() */
#define DBG_COM_SETUPRXSIGNALGROUP_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_COM_SETUPRXSIGNALGROUPARRAY_ARRAY_ENTRY
/** \brief Entry point of function Com_CopyRxSignalGroupArray_Array() */
#define DBG_COM_SETUPRXSIGNALGROUPARRAY_ARRAY_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_COM_SETUPRXSIGNALGROUPARRAY_ARRAY_EXIT
/** \brief Exit point of function Com_CopyRxSignalGroupArray_Array() */
#define DBG_COM_SETUPRXSIGNALGROUPARRAY_ARRAY_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_COM_SETUPRXSIGNALGROUPARRAY_SHADOW_ENTRY
/** \brief Entry point of function Com_CopyRxSignalGroupArray_Shadow() */
#define DBG_COM_SETUPRXSIGNALGROUPARRAY_SHADOW_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_SETUPRXSIGNALGROUPARRAY_SHADOW_EXIT
/** \brief Exit point of function Com_CopyRxSignalGroupArray_Shadow() */
#define DBG_COM_SETUPRXSIGNALGROUPARRAY_SHADOW_EXIT(a,b,c,d,e)
#endif

#ifndef DBG_COM_COPYRXSIGNALGROUPARRAY_ENTRY
/** \brief Entry point of function Com_CopyRxSignalGroupArray() */
#define DBG_COM_COPYRXSIGNALGROUPARRAY_ENTRY(a,b,c,d)
#endif

#ifndef DBG_COM_COPYRXSIGNALGROUPARRAY_EXIT
/** \brief Exit point of function Com_CopyRxSignalGroupArray() */
#define DBG_COM_COPYRXSIGNALGROUPARRAY_EXIT(a,b,c,d)
#endif

#ifndef DBG_COM_SETUPTXSIGNALGROUP_ENTRY
/** \brief Entry point of function Com_SetupTxSignalGroup() */
#define DBG_COM_SETUPTXSIGNALGROUP_ENTRY(a,b,c,d,e)
#endif

#ifndef DBG_COM_SETUPTXSIGNALGROUP_EXIT
/** \brief Exit point of function Com_SetupTxSignalGroup() */
#define DBG_COM_SETUPTXSIGNALGROUP_EXIT(a,b,c,d,e,f)
#endif

#ifndef DBG_COM_EB_HANDLEPDURXDM_ENTRY
/** \brief Entry point of function Com_EB_HandlePduRxDM() */
#define DBG_COM_EB_HANDLEPDURXDM_ENTRY(a,b)
#endif

#ifndef DBG_COM_EB_HANDLEPDURXDM_EXIT
/** \brief Exit point of function Com_EB_HandlePduRxDM() */
#define DBG_COM_EB_HANDLEPDURXDM_EXIT(a,b)
#endif

#ifndef DBG_COM_EB_HANDLETXCONFIRMATIONS_ENTRY
/** \brief Entry point of function Com_EB_HandleTxConfirmations() */
#define DBG_COM_EB_HANDLETXCONFIRMATIONS_ENTRY(a)
#endif

#ifndef DBG_COM_EB_HANDLETXCONFIRMATIONS_EXIT
/** \brief Exit point of function Com_EB_HandleTxConfirmations() */
#define DBG_COM_EB_HANDLETXCONFIRMATIONS_EXIT(a)
#endif

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[external data]=========================================*/

#endif /* (!defined COM_TRACE_H) */
/*==================[end of file]===========================================*/
