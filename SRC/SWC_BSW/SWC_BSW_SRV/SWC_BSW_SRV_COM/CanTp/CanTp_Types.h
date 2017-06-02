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

#if(!defined CANTP_TYPES_H)
#define CANTP_TYPES_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>         /* EB AUTOSAR standard types */
#include <ComStack_Types.h>    /* AUTOSAR ComStack types */

/*==================[macros]================================================*/

/** \brief max length of N-PDU in bytes */
#define CANTP_NPDU_LENGTH_MAX     8U

/** \brief minimum length of N-PDU in bytes
 **
 ** The smallest N-PDU must at least have 1 byte header and 1 byte data (SF, CF).
 ** FC frames will have at least a header of 3 bytes.
 */
#define CANTP_NPDU_LENGTH_MIN     2U

/** \brief Number of bytes in the internal channel pointer data buffer */
#define CANTP_NSDU_LENGTH_MAX     7U

/** \brief Channel mode types */
#define CANTP_MODE_FULL_DUPLEX  0U
#define CANTP_MODE_HALF_DUPLEX  1U

/** \brief Type of Gpt callback type. */
#define CANTP_GPT_CALLBACK           0U
#define CANTP_MAINFUNCTION_CALLBACK  1U

/*==================[type definitions]======================================*/

/** \brief Type to define indication for upper layer status. */
typedef enum
{
  CANTP_ULIND_NONE,
  CANTP_ULIND_STATUS
} CanTp_ULIndicationType;

/** \brief Type to hold channel state information. */
typedef VAR(uint8, TYPEDEF) CanTp_ChStateType;

/** \brief Type of CanTp Channel administration. */
typedef struct
{
  /* STmin counter for MainFunction callback */
  VAR(uint32, TYPEDEF) MfCounterTicks;
  /* handled N-Sdu */
  VAR(PduIdType, TYPEDEF) NSduId;
  /* Id of Tx Confirmation handled on channel release */
  VAR(PduIdType, TYPEDEF) PostTxConfNPduId;
  /* Id of Rx Indication handled on channel release */
  VAR(PduIdType, TYPEDEF) PostRxIndNSduId;
  /* total message length */
  VAR(uint16, TYPEDEF) TotalLength;
  /* Actual buffer size provided by upper layer.
     RX: Buffer available for receiving data.
     TX: Amount of bytes ready to transmit.
   */
  VAR(uint16, TYPEDEF) ActualBufferSize;
  /* transmitted/received length */
  VAR(uint16, TYPEDEF) ProcessedLength;
  /* timeout counter */
  VAR(uint16, TYPEDEF) Ticks;
  /* ticks to countdown before channel release */
  VAR(uint16, TYPEDEF) PostTicks;
  /* Incoming RX N-PDU length while channel was locked */
  VAR(uint8, TYPEDEF) PostRxIndLength;
  /* Incoming RX N-PDU while channel was locked */
  VAR(uint8, TYPEDEF) PostRxIndData[CANTP_NPDU_LENGTH_MAX];
  /* Stores the frame type of the postponed frame. */
  VAR(uint8, TYPEDEF) PostRxIndFrameType;
  /* ind. flag for upper layer */
  VAR(uint8, TYPEDEF) ChannelLockFlag;
  /* flag indicating Rx indication handling on channel release */
  VAR(boolean, TYPEDEF) PostRxIndFlag;
  /* flag indicating Tx confirmation handling on channel release */
  VAR(boolean, TYPEDEF) PostTxConfFlag;
  /* flag indicating STmin timeout handling on channel release */
  VAR(boolean, TYPEDEF) PostSTminFlag;
  /* channel state */
  VAR(CanTp_ChStateType, TYPEDEF) State;
  /* current Transmit block size */
  VAR(uint8, TYPEDEF) BlockSize;
  /* transmitted blocks */
  VAR(uint8, TYPEDEF) ProcessedBlockFrames;
  /* counter for wait frames */
  VAR(uint8, TYPEDEF) WftCounter;
  /* sequence number for CF */
  VAR(uint8, TYPEDEF) SequenceNumber;
  /* for Tx Channels only */
  VAR(uint8, TYPEDEF) StMin;
  /* Temporary buffer
     RX: Incoming FF and SF will be stored until processed by upper layer.
     TX: Stores the frame which will be transmitted next.
   */
  VAR(uint8, TYPEDEF) TempBuffer[CANTP_NSDU_LENGTH_MAX];
  /* Temporary buffer length indicates the amount of bytes in the buffer. */
  VAR(uint8, TYPEDEF) TempLength;
  /* length of data to transmit */
  VAR(uint8, TYPEDEF) CanIfDLC;
  /* data to transmit via CanIf */
  VAR(uint8, TYPEDEF) CanIfData[CANTP_NPDU_LENGTH_MAX];
} CanTp_ChannelType;

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/



/*==================[end of file]===========================================*/

#endif /* if !defined( CANTP_TYPES_H ) */
