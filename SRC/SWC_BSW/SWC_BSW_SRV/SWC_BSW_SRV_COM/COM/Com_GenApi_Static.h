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
#ifndef COM_GENAPI_STATIC_H_
#define COM_GENAPI_STATIC_H_

/*==================[inclusions]============================================*/

#include <Com_Rules.h>

/*==================[macros]================================================*/

#if (defined COM_GENAPI_RXPDU_RXDMTIMEOUT)     /* To prevent double declaration */
#error COM_GENAPI_RXPDU_RXDMTIMEOUT already defined
#endif /* if (defined COM_GENAPI_RXPDU_RXDMTIMEOUT) */

/** \brief Define COM_GENAPI_RXPDU_RXDMTIMEOUT */
#define COM_GENAPI_RXPDU_RXDMTIMEOUT 2U

#if (defined COM_RXPDU_RXDMTIMEOUT)
#if (COM_GENAPI_RXPDU_RXDMTIMEOUT != COM_RXPDU_RXDMTIMEOUT)
#error COM_GENAPI_RXPDU_RXDMTIMEOUT != COM_RXPDU_RXDMTIMEOUT
#endif /* (COM_GENAPI_RXPDU_RXDMTIMEOUT != COM_RXPDU_RXDMTIMEOUT) */
#endif /* (defined COM_RXPDU_RXDMTIMEOUT) */

/*
 * extract a signal from a 1-byte buffer
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_1(offset, shift, pnData ) \
        ( ((pnData)[0] & (uint8)(0xffU >> (offset))) >> (shift)  \
        )

/*
 * extract a signal from a 2-byte buffer
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_2(offset, shift, pnData ) \
        ( ((uint16)(pnData)[1] >> (shift))                                         \
        | (uint16)((((uint16)(pnData)[0] & (0xffU >> (offset))) << (8U-(shift))))  \
        )

/*
 * extract a signal from a 3-byte buffer
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_3(offset, shift, pnData ) \
        ( ((uint32)(pnData)[2] >> (shift))                                     \
        | ((uint32)(pnData)[1] << (8U-(shift)))                                \
        | (((uint32)(pnData)[0] & ((uint32)0xffU>>(offset))) << (16U-(shift))) \
        )

/*
 * extract a signal from a 4-byte buffer
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_4(offset, shift, pnData ) \
        ( ((uint32)(pnData)[3] >> (shift))                                      \
        | ((uint32)(pnData)[2] << (8U-(shift)))                                 \
        | ((uint32)(pnData)[1] << (16U-(shift)))                                \
        | (((uint32)(pnData)[0] &((uint32)0xffU >> (offset))) << (24U-(shift))) \
        )

/*
 * extract a signal from a 5-byte buffer
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_5(offset, shift, pnData ) \
        ( ((uint32)(pnData)[4] >> (shift))                                       \
        | ((uint32)(pnData)[3] << (8U-(shift)))                                  \
        | ((uint32)(pnData)[2] << (16U-(shift)))                                 \
        | ((uint32)(pnData)[1] << (24U-(shift)))                                 \
        | (((uint32)(pnData)[0] & ((uint32)0xffU >> (offset))) << (32U-(shift))) \
        )

/*
 * extract a 8 bit signal from a 1-byte buffer
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_INT_8(offset, shift, pnData ) \
   COM_EB_EXTRACT_BE_1((offset), (shift), (pnData) )

/*
 * extract a 16 bit signal from a 2-byte buffer
 * NOTE: buffer has to be 2-byte aligned.
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 15)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_INT_16(offset, shift, pnData ) \
        ( (uint16)((*(P2VAR(uint16, AUTOMATIC, COM_VAR_NOINIT))(pnData)) \
              &(uint16)(0xffffU>>(offset)))>>(shift) \
        )

/*
 * extract a 16 bit signal from a 4-byte buffer
 * NOTE: buffer has to be 4-byte aligned.
 *    shift .. right-shift of last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 31)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_BE_INT_32(offset, shift, pnData )                       \
        ( (uint32)((*(P2VAR(uint32, AUTOMATIC, COM_VAR_NOINIT))(pnData))       \
              & (uint32)(0xffffffffU >> (offset))) >> (shift)                  \
        )

/*
 * extract a signal from a 1-byte buffer
 *    mask .. mask for last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_1(mask, offset, pnData )     \
        ( (((pnData)[0] & (uint8)(mask)) >> (offset))  \
        )

/*
 * extract a signal from a 2-byte buffer
 *    mask .. mask for last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_2(mask, offset, pnData )                             \
        ( ((uint16)(pnData)[0] >> (offset))                                    \
        | (uint16)((((uint16)(pnData)[1] & (uint32)(mask)) << (8U-(offset))))  \
        )

/*
 * extract a signal from a 3-byte buffer
 *    mask .. mask for last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_3(mask, offset, pnData )                \
        ( ((uint32)(pnData)[0]>>(offset))                         \
        | ((uint32)(pnData)[1]<<(8U-(offset)))                    \
        | (((uint32)(pnData)[2]&(uint32)(mask))<<(16U-(offset)))  \
        )

/*
 * extract a signal from a 4-byte buffer
 *    mask .. mask for last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_4(mask, offset, pnData )                    \
        ( ((uint32)(pnData)[0] >> (offset))                           \
        | ((uint32)(pnData)[1] << (8U-(offset)))                      \
        | ((uint32)(pnData)[2] << (16U-(offset)))                     \
        | (((uint32)(pnData)[3] & (uint32)(mask)) << (24U-(offset)))  \
        )

/*
 * extract a signal from a 5-byte buffer
 *    mask .. mask for last byte
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_5(mask, offset, pnData )                    \
        ( ((uint32)(pnData)[0] >> (offset))                           \
        | ((uint32)(pnData)[1] << (8U-(offset)))                      \
        | ((uint32)(pnData)[2] << (16U-(offset)))                     \
        | ((uint32)(pnData)[3] << (24U-(offset)))                     \
        | (((uint32)(pnData)[4] & (uint32)(mask)) << (32U-(offset)))  \
        )


/*
 * extract a signal from a 1-byte buffer
 *    mask .. mask for all bytes
 *    offset .. offset of first bit of signal in buffer (0 .. 7)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_INT_8(mask, offset, pnData )  \
   COM_EB_EXTRACT_LE_1(mask, offset, pnData )

/*
 * extract a signal from a 2-byte buffer
 * NOTE: buffer has to be 2-byte aligned.
 *    mask .. mask for all bytes
 *    offset .. offset of first bit of signal in buffer (0 .. 15)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_INT_16(mask, offset, pnData )                        \
        ( (uint16)((*(P2VAR(uint16, AUTOMATIC, COM_VAR_NOINIT))(pnData))       \
              & (uint16)(mask)) >> (offset)                                    \
        )

/*
 * extract a signal from a 4-byte buffer
 * NOTE: buffer has to be 4-byte aligned.
 *    mask .. mask for all bytes
 *    offset .. offset of first bit of signal in buffer (0 .. 31)
 *    pnData .. pointer to buffer
 */
#define COM_EB_EXTRACT_LE_INT_32(mask, offset, pnData )                        \
        ( (uint32)((*(P2VAR(uint32, AUTOMATIC, COM_VAR_NOINIT))(pnData))       \
              & (uint32)(mask)) >> (offset)                                    \
        )

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* COM_GENAPI_STATIC_H_ */

/*==================[end of file]===========================================*/

