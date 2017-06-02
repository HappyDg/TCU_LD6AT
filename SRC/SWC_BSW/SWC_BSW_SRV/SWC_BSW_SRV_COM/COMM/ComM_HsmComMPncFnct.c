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

/* Implementation of the state handler functions of the state machine
 * ComMPnc.
 *
 * This file contains the implementation of the state functions.  It
 * is generated but must be edited to implement the real actions.  If the
 * state machine model is updated and the code generator regenerates the
 * files the user must manually merge the changes with any existing hand
 * written code.
 */

/* CHECK: RULE 301 OFF (this file is partly generated, some lines may be
 * longer then 100 characters) */

/* MISRA-C:2004 Deviation List
 *
 * MISRA-1) Deviated Rule: 13.7 (required)
 *     Boolean operations whose results are invariant shall not be permitted.
 *
 *     Reason:
 *     This is not a programming error. This approach has been deliberately
 *     selected to apply a common method to access the channel configuration
 *     data in all configuration possibilities.
 *
 * MISRA-2) Deviated Rule: 12.4 (required)
 *     The right-hand operand of a logical '&&' or '||' operator shall
 *     not contain side effects.
 *
 *     Reason:
 *     The functions which are called to calculate the operands do not
 *     have side effects.
 */

/*==================[inclusions]============================================*/

#include <ComM_Trace.h>
#include <ComM_BSW.h>
#include <ComM_Int.h>
#include <ComM_BSW_Cfg.h>

#include <ComM_Hsm.h>  /* state machine driver interface */
#include <ComM_HsmComMPnc.h> /* public statechart model definitions */
#include <ComM_HsmComMPncInt.h> /* internal statechart model definitions */
#include <ComM_Cfg.h>
#include <BswM_ComM.h>
#if (COMM_PNC_SUPPORT == STD_ON)
/* !LINKSTO ComM506_Refine_Com,1 */
#include <Com.h>     /* Com API's */
#endif
#if (COMM_NUM_PNC > 0U)
/*==================[macros]================================================*/

/** \brief Instant access to Pnc Timer */
#define COMM_PNC_TIMER(Pnc)                     \
  COMM_INST_ACCESS(ComM_PncTimer,Pnc)

#if (COMM_T_PNC_PREPARE_SLEEP == 0U)
#define ComM_PncStartTimer(Pnc)       \
  (void) COMM_HSMEMITINST(&ComM_HsmScComMPnc, Pnc, COMM_HSM_COMMPNC_EV_PREPARE_SLEEP_TIMEOUT);
#else
#define ComM_PncStartTimer(Pnc)  \
  COMM_PNC_TIMER(Pnc) = COMM_T_PNC_PREPARE_SLEEP;
#endif

#define ComM_PncStopTimer(Pnc)  \
  COMM_PNC_TIMER(Pnc) = 0U;

/** \brief User ID of a channel. */
#define COMM_NUMCHANNELSOFPNC(pnc)             \
  (COMM_INST_ACCESS(ComM_NumChannelsOfPnc,pnc))

#define COMM_CHANNELSOFPNC(pnc,i)             \
  (COMM_INST_ACCESS(ComM_ChannelsOfPnc,(pnc))[(i)])
/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/
#define COMM_START_SEC_CODE
#include <MemMap.h>

/** \brief Request Full com for all channels of a Pnc
 **
 ** This function requests Full communication for all channels of
 ** a Pnc.
 **
 ** \param[in] Pnc index of Pnc */
STATIC FUNC(void, COMM_CODE)
  ComM_NmNwReqAllChOfPnc (const uint8 pncIdx);

/** \brief Get Eira
 **
 ** This function returns the status of EIRA (when Set TRUE is returned)
 ** of a Pnc */
STATIC FUNC(uint8, COMM_CODE) ComM_PncGetEIRA(
                                COMM_PDL_SF(const uint8 instIdx));

/** \brief Send the status of PNC(s) via Com signal(s)
 **
 ** A PNC may contain references to more than one TX EIRA Com Signal.
 ** Therefore, this function sends the updated EIRA to all Com Signals
 ** which are referenced by this PNC.
 **
 ** Some PNCs may not reference a TX EIRA Com signal.
 ** Therefore, this function also masks out the bits corresponding
 ** to PNCs which do not reference this Com signal before sending.
 **/
STATIC FUNC(void, COMM_CODE) ComM_PncSendSignal
(
  COMM_PDL_SF(const uint8 instIdx)
);

/** \brief Set the PNC active status of all channels of a PNC */
STATIC FUNC(void, COMM_CODE) ComM_SetChannelActiveStatus
(
  COMM_PDL_SF(const uint8 PncIdx),
  boolean Status
);

#define COMM_STOP_SEC_CODE
#include <MemMap.h>
/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

#define COMM_START_SEC_VAR_INIT_16
#include <MemMap.h>

/** \brief Time counter value for checking the Prepare Sleep
 ** timeout for different Pnc */
STATIC VAR(uint16, COMM_VAR) ComM_PncTimer[COMM_NUM_PNC];

#define COMM_STOP_SEC_VAR_INIT_16
#include <MemMap.h>

/*==================[external function definitions]=========================*/

#define COMM_START_SEC_CODE
#include <MemMap.h>

/* ************************ state functions ******************************* */

/* ************************************************************************
 * State: PncTop
 * Parent state: none
 * Init substate: PncNoCom
 * Transitions originating from this state:
 */


/* ************************************************************************
 * State: PncFullCom
 * Parent state: PncTop
 * Init substate: PncPrepareSleep
 * Transitions originating from this state:
 */


/* ************************************************************************
 * State: PncPrepareSleep
 * Parent state: PncFullCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PncPrepareSleep -> PncReadySleep: COMCBK[ComM_PncGetEIRA() == 1]/
 *                       StopTimer(ComMPncPrepareSleepTimer);
 * 2) PncPrepareSleep -> PncRequested: FULL_COM_REQ_BY_COMM_USER[]/
 *                       StopTimer(ComMPncPrepareSleepTimer);
 * 3) PncPrepareSleep -> PncNoComNotify: PREPARE_SLEEP_TIMEOUT[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMPncSfPncPrepareSleepEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  /* entry action
   * 'BswM_ComM_CurrentPncMode(PNC_ID, PNC_PREPARE_SLEEP); =>ComM908
   * StartTimer(TIMEOUT, ComMPncPrepareSleepTimer); =>ComM952' */
  BswM_ComM_CurrentPNCMode(ComM_PncID[COMM_INST(instIdx)], PNC_PREPARE_SLEEP);
  ComM_PncStartTimer(instIdx);
}
FUNC(boolean, COMM_CODE) ComM_HsmComMPncSfPncPrepareSleepGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  /* guard condition 'ComM_PncGetEIRA() == 1'
   * for COMCBK[...]/StopTimer(ComMPncPrepareSleepTimer);
   * external transition to state PncReadySleep */
  return (ComM_PncGetEIRA(COMM_PL_SF(instIdx)) != 0U) ? TRUE : FALSE;
}
FUNC(void, COMM_CODE) ComM_HsmComMPncSfPncPrepareSleepAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION1_ENTRY(COMM_INST(instIdx));
  /* action 'StopTimer(ComMPncPrepareSleepTimer);'
   * for COMCBK[ComM_PncGetEIRA() == 1]/...
   * external transition to state PncReadySleep */
  ComM_PncStopTimer(instIdx);
  DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION1_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMPncSfPncPrepareSleepAction2(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION2_ENTRY(COMM_INST(instIdx));
  /* action 'StopTimer(ComMPncPrepareSleepTimer);'
   * for FULL_COM_REQ_BY_COMM_USER[]/...
   * external transition to state PncRequested */
  ComM_PncStopTimer(instIdx);
  DBG_COMM_HSMCOMMPNCSFPNCPREPARESLEEPACTION2_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: PncReadySleep
 * Parent state: PncFullCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PncReadySleep -> PncPrepareSleep: COMCBK[ComM_PncGetEIRA() == 0]/
 * 2) PncReadySleep -> PncRequested: FULL_COM_REQ_BY_COMM_USER[]/
 */

FUNC(void, COMM_CODE) ComM_HsmComMPncSfPncReadySleepEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPENTRY_ENTRY(COMM_INST(instIdx));
  /* entry action 'BswM_ComM_CurrentPncMode(PNC_ID, PNC_READY_SLEEP);=>ComM908 */
  BswM_ComM_CurrentPNCMode(ComM_PncID[COMM_INST(instIdx)], PNC_READY_SLEEP);
  DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(boolean, COMM_CODE) ComM_HsmComMPncSfPncReadySleepGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPGUARD1_ENTRY(COMM_INST(instIdx));
  /* guard condition 'ComM_PncGetEIRA() == 0'
   * for COMCBK[...]/
   * external transition to state PncPrepareSleep */
  ret =  (ComM_PncGetEIRA(COMM_PL_SF(instIdx)) == 0U) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMPNCSFPNCREADYSLEEPGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: PncRequested
 * Parent state: PncFullCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 * 1) PncRequested -> PncReadySleep: NO_COM_REQ_BY_ALL_COMM_USER[]/
 *      Com_SendSignal(ERA_PNC_ID, 0);
 *      ComM_RequestNoComChannels(PNC_ID);
 *      if (COMM_NO_INTERNAL_REQUESTS) ComM_SetChannelActiveStatus(FALSE);
 */

FUNC(void, COMM_CODE) ComM_HsmComMPncSfPncRequestedEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  /* entry action
   * 'BswM_ComM_CurrentPNCMode(PNC_ID, PNC_REQUESTED); =>ComM908
   * Com_SendSignal(EIRA_PNC_ID, 1); =>ComM930
   * ComM_NmNwReqAllChOfPnc(PNC_ID); ==>ComM980
   * ComM_SetChannelActiveStatus(TRUE);
   */
  const uint8 Index = (uint8)(ComM_PncID[COMM_INST(instIdx)] >> 3U);
  const uint8 EiraMask = (uint8)(0x01U << (ComM_PncID[COMM_INST(instIdx)] & 7U));

  DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDENTRY_ENTRY(COMM_INST(instIdx));

  ComM_SetChannelActiveStatus(COMM_INST(instIdx), TRUE);

  BswM_ComM_CurrentPNCMode(ComM_PncID[COMM_INST(instIdx)], PNC_REQUESTED);
  /* ComM930: When entering the PNC sub state PNC_REQUESTED
   * the API Com_SendSignal() shall be called with the value '1' for the bit
   * representing this PNC for the Com signal assigned to this PNC with
   * ComMPncComSignalDirection "TX".
   */

  /* First, set the bit corresponding to this PNC in the EIRA to be sent */
  ComM_TxEira[Index] |= EiraMask;

  /* Now, send the status via the assigned Com signal(s) */
  ComM_PncSendSignal(COMM_INST(instIdx));

  ComM_NmNwReqAllChOfPnc(COMM_INST(instIdx));

  DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDENTRY_EXIT(COMM_INST(instIdx));
}
FUNC(void, COMM_CODE) ComM_HsmComMPncSfPncRequestedAction1(
  COMM_PDL_SF(const uint8 instIdx))
{
  /* action 'Com_SendSignal(ERA_PNC_ID, 0);
   * if (COMM_NO_INTERNAL_REQUESTS) ComM_SetChannelActiveStatus(FALSE);'
   * for NO_COM_REQ_BY_ALL_COMM_USER[]/...
   * external transition to state PncReadySleep */
  const uint8 Index  = (uint8)(ComM_PncID[COMM_INST(instIdx)] >> 3U);
  const uint8 EiraMask = (uint8)(~(uint8)(0x01U << (ComM_PncID[COMM_INST(instIdx)] & 7U)));

  DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDACTION1_ENTRY(COMM_INST(instIdx));

  /* ComM960: When entering the PNC sub state PNC_READY_SLEEP from
   * PNC_REQUESTED, the API Com_SendSignal() shall be called with the value '0'
   * for the bit representing this PNC for all Com signals assigned to this PNC
   * with ComMPncComSignalDirection "TX".
   */

  /* First, clear the bit corresponding to this PNC in the EIRA to be sent */
  ComM_TxEira[Index] &= EiraMask;

  /* Now, send the status via the assigned Com signal(s) */
  ComM_PncSendSignal(COMM_INST(instIdx));

#if (COMM_PNC_RELEASE_CHANNEL == COMM_NO_INTERNAL_REQUESTS)
  /* !LINKSTO ComM.EB.ReadySleepFullComRelease,1 */
  ComM_SetChannelActiveStatus(COMM_INST(instIdx), FALSE);
#endif

  DBG_COMM_HSMCOMMPNCSFPNCREQUESTEDACTION1_EXIT(COMM_INST(instIdx));
}

/* ************************************************************************
 * State: PncNoCom
 * Parent state: PncTop
 * Init substate: PncNoComInit
 * Transitions originating from this state:
 * 1) PncNoCom -> PncReadySleep: COMCBK[ComM_PncGetEIRA() == 1]/
 * 2) PncNoCom -> PncPrepareSleep:
 *                ECUM_WAKEUP_IND[ComMSynchronousWakeUp == TRUE]/
 * 3) PncNoCom -> PncRequested: FULL_COM_REQ_BY_COMM_USER[]/
 */

FUNC(boolean, COMM_CODE) ComM_HsmComMPncSfPncNoComGuard1(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD1_ENTRY(COMM_INST(instIdx));

  /* guard condition 'ComM_PncGetEIRA() == 1'
   * for COMCBK[...]/
   * external transition to state PncReadySleep */
  ret =  (ComM_PncGetEIRA(COMM_PL_SF(instIdx)) != 0U) ? TRUE : FALSE;

  DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD1_EXIT(ret, COMM_INST(instIdx));
  return ret;
}
FUNC(boolean, COMM_CODE) ComM_HsmComMPncSfPncNoComGuard2(
  COMM_PDL_SF(const uint8 instIdx))
{
  boolean ret;
  DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD2_ENTRY(COMM_INST(instIdx));

  /* guard condition 'ComMSynchronousWakeUp == TRUE'
   * for ECUM_WAKEUP_IND[...]/
   * external transition to state PncPrepareSleep */
#if (COMM_HSM_INST_MULTI_ENABLED == STD_ON)
  TS_PARAM_UNUSED(instIdx);
#endif
  /* Deviation MISRA-1 */
  ret = (COMM_SYNCHRONOUS_WAKE_UP == STD_ON) ? TRUE : FALSE;
  DBG_COMM_HSMCOMMPNCSFPNCNOCOMGUARD2_EXIT(ret, COMM_INST(instIdx));
  return ret;
}

/* ************************************************************************
 * State: PncNoComInit
 * Parent state: PncNoCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */


/* ************************************************************************
 * State: PncNoComNotify
 * Parent state: PncNoCom
 * Init substate: none, this is a leaf state
 * Transitions originating from this state:
 */

FUNC(void, COMM_CODE) ComM_HsmComMPncSfPncNoComNotifyEntry(
  COMM_PDL_SF(const uint8 instIdx))
{
  DBG_COMM_HSMCOMMPNCSFPNCNOCOMNOTIFYENTRY_ENTRY(COMM_INST(instIdx));

  /* entry action
   * 'BswM_ComM_CurrentPncMode(PNC_ID, PNC_NO_COMMUNICATION); =>ComM908 
   *  if (COMM_NO_INTERNAL_AND_EXTERNAL_REQUESTS) ComM_SetChannelActiveStatus(FALSE)';
   */
  BswM_ComM_CurrentPNCMode(ComM_PncID[COMM_INST(instIdx)], PNC_NO_COMMUNICATION);
  
#if (COMM_PNC_RELEASE_CHANNEL == COMM_NO_INTERNAL_AND_EXTERNAL_REQUESTS)
  /* !LINKSTO ComM.EB.NoComRelease,1 */
  ComM_SetChannelActiveStatus(COMM_INST(instIdx), FALSE);
#endif

  DBG_COMM_HSMCOMMPNCSFPNCNOCOMNOTIFYENTRY_EXIT(COMM_INST(instIdx));
}


/*==================[internal function definitions]=========================*/

STATIC FUNC(void, COMM_CODE) ComM_NmNwReqAllChOfPnc
(
  const uint8 pncIdx
)
{
  uint8_least chIdx;

  DBG_COMM_NMNWREQALLCHOFPNC_ENTRY(pncIdx);

  for (chIdx = 0U; chIdx < COMM_NUMCHANNELSOFPNC(pncIdx); chIdx++)
  {
    const uint8 Channel = COMM_CHANNELSOFPNC(pncIdx,chIdx);
    if(ComM_PncNmRequest[Channel]==TRUE)
    {
      (void)COMM_HSMEMITINST(&ComM_HsmScComM, Channel, COMM_HSM_COMM_EV_PNC_NM_REQUEST);
    }
  }
#if (COMM_HSM_INST_MULTI_ENABLED == STD_OFF)
  TS_PARAM_UNUSED(pncIdx);
#endif
  DBG_COMM_NMNWREQALLCHOFPNC_EXIT(pncIdx);
}

STATIC FUNC(uint8, COMM_CODE) ComM_PncGetEIRA
(
  COMM_PDL_SF(const uint8 instIdx)
)
{
  const uint8 Index  = (uint8) (ComM_PncID[COMM_INST(instIdx)] >> 3U);
  const uint8 EiraMask = (uint8)(0x01U << (ComM_PncID[COMM_INST(instIdx)] & 7U));
  boolean ret;

  DBG_COMM_PNCGETEIRA_ENTRY(COMM_INST(instIdx));

  ret = ((uint8)(ComM_RxEira[Index] & EiraMask));

  DBG_COMM_PNCGETEIRA_EXIT(ret,COMM_INST(instIdx));

  return ret;
}

STATIC FUNC(void, COMM_CODE) ComM_PncSendSignal
(
  COMM_PDL_SF(const uint8 instIdx)
)

{
  uint8 i;
  uint8 TxEira[COMM_PN_INFO_LENGTH];

  DBG_COMM_PNCSENDSIGNAL_ENTRY(COMM_INST(instIdx));

  /* A PNC may contain references to more than one TX EIRA Com Signal.
   * Therefore, the updated EIRA has to be sent to all Com Signals
   * which are referenced by this PNC.
   */
  for (i = 0U; i < ComM_PncTxEiraSignalMap[COMM_INST(instIdx)].NumTxSignal; i++)
  {
    /* Get the index of this signal in the list of Tx EIRA signals
     * assigned to this PNC */
    const uint8 SigIndex = ComM_PncTxEiraSignalMap[COMM_INST(instIdx)].TxSignalList[i];
    uint8 j;

    /* Some PNCs may not reference this TX EIRA Com signal.
     * Therefore, the bits corresponding to PNCs which do not
     * reference this Com signal have to be masked out before sending.
     */
    for (j = 0U; j < COMM_PN_INFO_LENGTH; j++)
    {
      TxEira[j] = ComM_TxEira[j] & ComM_PncTxEiraMask[SigIndex][j];
    }

    (void)Com_SendSignal(ComM_TxComSignalCfg[SigIndex], TxEira);
  }

  DBG_COMM_PNCSENDSIGNAL_EXIT(COMM_INST(instIdx));
}

FUNC(void, COMM_CODE) ComM_PncProcessTimers(void)
{
  /* No *_least type for a loop variable as the variable is also used as
     an argument whose underlying type is uint8  */
  uint8 PncIdx;

  DBG_COMM_PNCPROCESSTIMERS_ENTRY();

  for (PncIdx = 0U ; PncIdx < COMM_NUM_PNC ; PncIdx++)
  {
    if (COMM_PNC_TIMER(PncIdx) > 0U)
    {
      --COMM_PNC_TIMER(PncIdx);
      if (COMM_PNC_TIMER(PncIdx) == 0U)
      {
        /* timeout events are generated outside of transitions, therefore do
         * not use the EMITTOSELF function */
        (void)COMM_HSMEMITINST(
          &ComM_HsmScComMPnc, PncIdx, COMM_HSM_COMMPNC_EV_PREPARE_SLEEP_TIMEOUT);
      }
    }
  }

  DBG_COMM_PNCPROCESSTIMERS_EXIT();
}

STATIC FUNC(void, COMM_CODE) ComM_SetChannelActiveStatus
(
  COMM_PDL_SF(const uint8 PncIdx),
  boolean Status
)
{
  uint8_least ChIdx;
  DBG_COMM_SETCHANNELACTIVESTATUS_ENTRY(COMM_INST(PncIdx), Status);

  if (TRUE == Status)
  {
    ComM_BitArraySet(ComM_PncActiveStatus, PncIdx);
  }
  else
  {
    ComM_BitArrayClear(ComM_PncActiveStatus, PncIdx);
  }

  for (ChIdx = 0U; ChIdx < COMM_NUMCHANNELSOFPNC(PncIdx); ChIdx++)
  {
    const uint8 Channel = COMM_CHANNELSOFPNC(PncIdx, ChIdx);

    if (TRUE == Status)
    {
      ComM_BitArraySet(ComM_ChannelActiveStatus, Channel);
    }
    else
    {
      /* A channel may be associated with multiple PNCs.
         Don't clear the bit-array unless all PNCs corresponding to this
         channel enters PNC_NO_COMMUNICATION. */

      boolean AllInNoCom = TRUE;
      uint8_least PncPos;

      /* Find the highest ComMode of PNCs correspond to this channel */
      for(PncPos = 0U; PncPos < ComM_NumPncOfCh[Channel]; ++PncPos)
      {
        uint8 Idx;
        uint8 PncIDIdx = 0U;

        /* Find index from PNCIDs, since PNCIDs are generated in
           sorted order */
        for (Idx = 0U; Idx < COMM_NUM_PNC; ++Idx)
        {
          if(ComM_PNCsOfChannel[Channel][PncPos] == ComM_PncID[Idx] )
          {
            PncIDIdx = Idx;
          }
        }
        /* Deviation MISRA-2 <+2> */
        if( ComM_BitArrayIsBitSet(ComM_PncActiveStatus, PncIDIdx) )
        {
          /* If there is at least one PNC which was internally
           * requested, set the flag to false.
           */
          AllInNoCom = FALSE;
          break;
        }
      }

      if(TRUE == AllInNoCom)
      {
        /* Clear the bit array as all PNCs correspond to this channel
           are in PNC_NO_COMMUNICATION */
        ComM_BitArrayClear(ComM_ChannelActiveStatus, Channel);
      }
    }

    /* Set Event REQ_STATUS_CHANGED, to trigger change in Channel state
       machine if any */
    (void)COMM_HSMEMITINST(&ComM_HsmScComM, Channel, COMM_HSM_COMM_EV_REQ_STATUS_CHANGED);
  }


  DBG_COMM_SETCHANNELACTIVESTATUS_EXIT(COMM_INST(PncIdx), Status);

}

#define COMM_STOP_SEC_CODE
#include <MemMap.h>
#endif /* (COMM_NUM_PNC > 0U) */
/*==================[end of file]===========================================*/
