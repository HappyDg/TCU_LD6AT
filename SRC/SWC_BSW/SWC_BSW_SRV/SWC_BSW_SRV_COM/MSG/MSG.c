/******************************************************************************/
/*                                                                            */
/* !Layer           : COM                                                     */
/*                                                                            */
/* !Module          : MSG                                                     */
/* !Description     : COM Messages checks and callouts                        */
/*                                                                            */
/* !File            : MSG.C                                                   */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* !Author          : A. Abohassan                                            */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2016 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::             $$Author::   ogarot        $$Date::               $*/
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/

#include "Std_Types.h"

#include "MSG.h"
#include "MSG_L.h"

#include "CanIf.h"
#include "CanTp.h"
#include "Com.h"
#include "BSW.h"

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/

/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/

#define MSG_START_SEC_CODE
#include "MSG_MemMap.h"

/* RX timeout callbacks */
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGWhlSpdFrntLeRaw_529R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAbsCtrlActv_545R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAccrPedlRat_273R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGCrsCtrlCtrlActv_289R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAlgt_561R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGEngineSoakTime_609R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAmbAirTemp_641R(void);


/* RX acknowledge callbacks */
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGWhlSpdFrntLeRaw_529R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAbsCtrlActv_545R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAccrPedlRat_273R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGCrsCtrlCtrlActv_289R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAlgt_561R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGEngineSoakTime_609R(void);
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAmbAirTemp_641R(void);

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/


/******************************************************************************/
/*                                                                            */
/* !Function    : MSG_vidInit                                                 */
/* !Description : Init                                                        */
/* !Number      : Msg.1                                                       */
/* !Reference   : NONE                                                        */
/* !LastAuthor  : A. Abohassan                                                */
/*                                                                            */
/******************************************************************************/
void MSG_vidInit(void)
{
/*----------------------------------------------------------------------------*/
/* COM MSG TCU Rx frames counters Init                                     */
/*----------------------------------------------------------------------------*/
   BSW_u32CbkRxAckCnt_SGABS1 = 0;
   BSW_u32CbkRxAckCnt_SGABS2 = 0;
   BSW_u32CbkRxAckCnt_SGECM1 = 0;
   BSW_u32CbkRxAckCnt_SGECM2 = 0;
   BSW_u32CbkRxAckCnt_SGESC1 = 0;
   BSW_u32CbkRxAckCnt_SGECM3 = 0;
   BSW_u32CbkRxAckCnt_SGIP1 = 0;


/*----------------------------------------------------------------------------*/
/* COM MSG TCU Rx frames Timeout Init                                      */
/*----------------------------------------------------------------------------*/
   BSW_u32CbkRxTOutCnt_SGABS1 = 0;
   BSW_u32CbkRxTOutCnt_SGABS2 = 0;
   BSW_u32CbkRxTOutCnt_SGECM1 = 0;
   BSW_u32CbkRxTOutCnt_SGECM2 = 0;
   BSW_u32CbkRxTOutCnt_SGESC1 = 0;
   BSW_u32CbkRxTOutCnt_SGECM3 = 0;
   BSW_u32CbkRxTOutCnt_SGIP1 = 0;


   BSW_bCbkRxTOutFlag_SGABS1 = FALSE;
   BSW_bCbkRxTOutFlag_SGABS2 = FALSE;
   BSW_bCbkRxTOutFlag_SGECM1 = FALSE;
   BSW_bCbkRxTOutFlag_SGECM2 = FALSE;
   BSW_bCbkRxTOutFlag_SGESC1 = FALSE;
   BSW_bCbkRxTOutFlag_SGECM3 = FALSE;
   BSW_bCbkRxTOutFlag_SGIP1 = FALSE;


}






/* ========================================================================== */
/* CAN TCU/ Functions Rx Timeout callbacks                                 */
/* ========================================================================== */


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxTOut_SGWhlSpdFrntLeRaw_529R */
/* !Trigger     : COM after 3 missing Rx 10 ms signals                        */
/* !Description : COM RX timeout callback for ABS1 */
/* !Number      : BSW.1                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Abohassan                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGWhlSpdFrntLeRaw_529R(void)
{
   BSW_bCbkRxTOutFlag_SGABS1 = TRUE;
   BSW_u32CbkRxTOutCnt_SGABS1++;
}


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxTOut_SGAbsCtrlActv_545R */
/* !Trigger     : COM after 3 missing Rx 10 ms signals                        */
/* !Description : COM RX timeout callback for ABS2 */
/* !Number      : BSW.3                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Abohassan                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAbsCtrlActv_545R(void)
{
   BSW_bCbkRxTOutFlag_SGABS2 = TRUE;
   BSW_u32CbkRxTOutCnt_SGABS2++;
}


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxTOut_SGAccrPedlRat_273R */
/* !Trigger     : COM after 3 missing Rx 10 ms signals                        */
/* !Description : COM RX timeout callback for ECM1 */
/* !Number      : BSW.5                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Abohassan                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAccrPedlRat_273R(void)
{
   BSW_bCbkRxTOutFlag_SGECM1 = TRUE;
   BSW_u32CbkRxTOutCnt_SGECM1++;
}


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxTOut_SGCrsCtrlCtrlActv_289R */
/* !Trigger     : COM after 3 missing Rx 10 ms signals                        */
/* !Description : COM RX timeout callback for ECM2 */
/* !Number      : BSW.7                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Abohassan                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGCrsCtrlCtrlActv_289R(void)
{
   BSW_bCbkRxTOutFlag_SGECM2 = TRUE;
   BSW_u32CbkRxTOutCnt_SGECM2++;
}


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxTOut_SGAlgt_561R */
/* !Trigger     : COM after 3 missing Rx 10 ms signals                        */
/* !Description : COM RX timeout callback for ESC1 */
/* !Number      : BSW.9                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Abohassan                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAlgt_561R(void)
{
   BSW_bCbkRxTOutFlag_SGESC1 = TRUE;
   BSW_u32CbkRxTOutCnt_SGESC1++;
}


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxTOut_SGEngineSoakTime_609R */
/* !Trigger     : COM after 3 missing Rx 20 ms signals                        */
/* !Description : COM RX timeout callback for ECM3 */
/* !Number      : BSW.11                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Abohassan                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGEngineSoakTime_609R(void)
{
   BSW_bCbkRxTOutFlag_SGECM3 = TRUE;
   BSW_u32CbkRxTOutCnt_SGECM3++;
}


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxTOut_SGAmbAirTemp_641R */
/* !Trigger     : COM after 3 missing Rx 20 ms signals                        */
/* !Description : COM RX timeout callback for IP1 */
/* !Number      : BSW.13                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : A. Abohassan                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxTOut_SGAmbAirTemp_641R(void)
{
   BSW_bCbkRxTOutFlag_SGIP1 = TRUE;
   BSW_u32CbkRxTOutCnt_SGIP1++;
}


/* ========================================================================== */
/* CAN TCU/ Functions Rx acknowledge callbacks                             */
/* ========================================================================== */


/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxAck_SGWhlSpdFrntLeRaw_529R */
/* !Trigger     : COM signal unpacking from I-PDU                             */
/* !Description : COM RX acknowledge callback for ABS1 */
/* !Number      : BSW.2                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : Shenghan.chen                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGWhlSpdFrntLeRaw_529R(void)
{
   BSW_bCbkRxTOutFlag_SGABS1 = FALSE;
   BSW_u32CbkRxAckCnt_SGABS1++;
}
/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxAck_SGAbsCtrlActv_545R */
/* !Trigger     : COM signal unpacking from I-PDU                             */
/* !Description : COM RX acknowledge callback for ABS2 */
/* !Number      : BSW.4                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : Shenghan.chen                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAbsCtrlActv_545R(void)
{
   BSW_bCbkRxTOutFlag_SGABS2 = FALSE;
   BSW_u32CbkRxAckCnt_SGABS2++;
}
/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxAck_SGAccrPedlRat_273R */
/* !Trigger     : COM signal unpacking from I-PDU                             */
/* !Description : COM RX acknowledge callback for ECM1 */
/* !Number      : BSW.6                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : Shenghan.chen                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAccrPedlRat_273R(void)
{
   BSW_bCbkRxTOutFlag_SGECM1 = FALSE;
   BSW_u32CbkRxAckCnt_SGECM1++;
}
/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxAck_SGCrsCtrlCtrlActv_289R */
/* !Trigger     : COM signal unpacking from I-PDU                             */
/* !Description : COM RX acknowledge callback for ECM2 */
/* !Number      : BSW.8                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : Shenghan.chen                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGCrsCtrlCtrlActv_289R(void)
{
   BSW_bCbkRxTOutFlag_SGECM2 = FALSE;
   BSW_u32CbkRxAckCnt_SGECM2++;
}
/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxAck_SGAlgt_561R */
/* !Trigger     : COM signal unpacking from I-PDU                             */
/* !Description : COM RX acknowledge callback for ESC1 */
/* !Number      : BSW.10                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : Shenghan.chen                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAlgt_561R(void)
{
   BSW_bCbkRxTOutFlag_SGESC1 = FALSE;
   BSW_u32CbkRxAckCnt_SGESC1++;
}
/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxAck_SGEngineSoakTime_609R */
/* !Trigger     : COM signal unpacking from I-PDU                             */
/* !Description : COM RX acknowledge callback for ECM3 */
/* !Number      : BSW.12                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : Shenghan.chen                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGEngineSoakTime_609R(void)
{
   BSW_bCbkRxTOutFlag_SGECM3 = FALSE;
   BSW_u32CbkRxAckCnt_SGECM3++;
}
/******************************************************************************/
/*                                                                            */
/* !FuncName    : BSW_vidCbkRxAck_SGAmbAirTemp_641R */
/* !Trigger     : COM signal unpacking from I-PDU                             */
/* !Description : COM RX acknowledge callback for IP1 */
/* !Number      : BSW.14                                                      */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : Shenghan.chen                                                */
/******************************************************************************/
FUNC(void, COM_APPL_CODE) BSW_vidCbkRxAck_SGAmbAirTemp_641R(void)
{
   BSW_bCbkRxTOutFlag_SGIP1 = FALSE;
   BSW_u32CbkRxAckCnt_SGIP1++;
}

#define MSG_STOP_SEC_CODE
#include "MSG_MemMap.h"

/*-------------------------------- end of file -------------------------------*/
