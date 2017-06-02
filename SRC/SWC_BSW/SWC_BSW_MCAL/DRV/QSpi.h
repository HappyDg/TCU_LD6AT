/************************************************* <AUTO_FILE_HEADER> *************************************************/
/*                                                                                                                    */
/* !Layer           : QSPI                                                                                            */
/*                                                                                                                    */
/* !Component       : QSPI                                                                                            */
/* !Description     : QSPI unit                                                                                       */
/*                                                                                                                    */
/* !Module          : QSPI_API                                                                                        */
/* !Description     : API of QSPI unit                                                                                */
/*                                                                                                                    */
/* !File            : Qspi.h                                                                                          */
/*                                                                                                                    */
/* !Target          : Aurix_TC21x                                                                                     */
/*                                                                                                                    */
/* !Vendor          : Valeo                                                                                           */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT 2012 VALEO                                                                                               */
/* all rights reserved                                                                                                */
/*                                                                                                                    */
/**********************************************************************************************************************/
/* 1 / QSPI_u16GET_VALUE                                                                                              */
/* 2 / QSPI_u16GET_MS_VALUE                                                                                           */
/* 3 / QSPI_s16GET_DIF_CNVN_VALUE                                                                                     */
/* 4 / QSPI_u16GET_DIF_CNVN_VALUE                                                                                     */
/************************************************ </AUTO_FILE_HEADER> *************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S91/LOG/60_ComponentArchive/Archives/COMP_SWC_BSW_MCAL_MPC5616/adc_api.h_v                     $*/
/* $Revision::   1.4                                                                                                $*/
/* $Author::   vbecquet                               $$Date::   18 Jun 2013 18:50:22                                $*/
/**********************************************************************************************************************/

#ifndef QSPI_H
#define QSPI_H

#include "Std_Types.h"
#include "Std_Limits.h"
#include "micro.h"
#include "Os_api.h"

/**********************************************************************************************************************/
/* DEFINES                                                                                                            */
/**********************************************************************************************************************/
/* GLOBALCON register */
#define QSPI_u32GLOBALCON_TQ_DIV_1             (0u << 0)
#define QSPI_u32GLOBALCON_TQ_DIV_2             (1u << 0)
#define QSPI_u32GLOBALCON_TQ_DIV_3             (2u << 0)
#define QSPI_u32GLOBALCON_TQ_DIV_4             (3u << 0)
#define QSPI_u32GLOBALCON_TQ_DIV_5             (4u << 0)
#define QSPI_u32GLOBALCON_SI_DIS               (0u << 9)
#define QSPI_u32GLOBALCON_SI_ENA               (1u << 9)
#define QSPI_u32GLOBALCON_EXPECT_64            (0u << 10)
#define QSPI_u32GLOBALCON_EXPECT_128           (1u << 10)
#define QSPI_u32GLOBALCON_EXPECT_256           (2u << 10)
#define QSPI_u32GLOBALCON_EXPECT_512           (3u << 10)
#define QSPI_u32GLOBALCON_EXPECT_424           (4u << 10)
#define QSPI_u32GLOBALCON_LB_INACTIVE          (0u << 14)
#define QSPI_u32GLOBALCON_LB_ACTIVE            (1u << 14)
#define QSPI_u32GLOBALCON_DEL0_OFF             (0u << 15)
#define QSPI_u32GLOBALCON_DEL0_ON              (1u << 15)
#define QSPI_u32GLOBALCON_STROBE_DLY_1         (0u << 16)
#define QSPI_u32GLOBALCON_STROBE_DLY_2         (1u << 16)
#define QSPI_u32GLOBALCON_STROBE_DLY_3         (2u << 16)
#define QSPI_u32GLOBALCON_SRF_RUN_FIFO_FULL    (0u << 21)
#define QSPI_u32GLOBALCON_SRF_STOP_FIFO_FULL   (1u << 21)
#define QSPI_u32GLOBALCON_STIP_MRST_0          (0u << 22)
#define QSPI_u32GLOBALCON_STIP_MRST_1          (1u << 22)
#define QSPI_u32GLOBALCON_EN_RUN_RQ            (1u << 24)
#define QSPI_u32GLOBALCON_EN_PAUSE_RQ          (0u << 24)
#define QSPI_u32GLOBALCON_MS_MASTER_RX_TX      (0u << 25)
#define QSPI_u32GLOBALCON_MS_SLAVE_RX_TX       (2u << 25)
#define QSPI_u32GLOBALCON_AREN_DIS             (0u << 21)
#define QSPI_u32GLOBALCON_AREN_ENA             (1u << 21)
#define QSPI_u32GLOBALCON_RESETS_STATE_MACHINE (1u << 28)
#define QSPI_u32GLOBALCON_RESETS_TX_FIFO       (2u << 28)
#define QSPI_u32GLOBALCON_RESETS_RX_FIFO       (4u << 28)
#define QSPI_u32GLOBALCON_RESETS_REGISTERS     (8u << 28)

/* GLOBALCON1 register */
#define QSPI_u32GLOBALCON1_ERRORENS_ERR_DISA                 (0u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_PARITY_ERR_ENA           (1u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_UNEXP_CFG_ERR_ENA        (2u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_BAUDRATE_ERR_ENA         (4u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_TXFIFO_OVERFLOW_ERR_ENA  (8u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_TXFIFO_UNDERFLOW_ERR_ENA (16u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_RXFIFO_OVERFLOW_ERR_ENA  (32u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_RXFIFO_UNDERFLOW_ERR_ENA (64u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_EXPECT_TIMEOUT_ERR_ENA   (128u << 0)
#define QSPI_u32GLOBALCON1_ERRORENS_SLSI_MISPLACED_ERR_ENA   (256u << 0)
#define QSPI_u32GLOBALCON1_TXEN_DISA                         (0u << 9)
#define QSPI_u32GLOBALCON1_TXEN_ENA                          (1u << 9)
#define QSPI_u32GLOBALCON1_RXEN_DISA                         (0u << 10)
#define QSPI_u32GLOBALCON1_RXEN_ENA                          (1u << 10)
#define QSPI_u32GLOBALCON1_PT1_DISA                          (0u << 11)
#define QSPI_u32GLOBALCON1_PT1_ENA                           (1u << 11)
#define QSPI_u32GLOBALCON1_PT2_DISA                          (0u << 12)
#define QSPI_u32GLOBALCON1_PT2_ENA                           (1u << 12)
#define QSPI_u32GLOBALCON1_USREN_DISA                        (0u << 15)
#define QSPI_u32GLOBALCON1_USREN_ENA                         (1u << 15)
#define QSPI_u32GLOBALCON1_TXFIFOINT_LVL_1                   (0u << 16)
#define QSPI_u32GLOBALCON1_TXFIFOINT_LVL_2                   (1u << 16)
#define QSPI_u32GLOBALCON1_TXFIFOINT_LVL_3                   (2u << 16)
#define QSPI_u32GLOBALCON1_TXFIFOINT_LVL_4                   (3u << 16)
#define QSPI_u32GLOBALCON1_RXFIFOINT_LVL_1                   (0u << 18)
#define QSPI_u32GLOBALCON1_RXFIFOINT_LVL_2                   (1u << 18)
#define QSPI_u32GLOBALCON1_RXFIFOINT_LVL_3                   (2u << 18)
#define QSPI_u32GLOBALCON1_RXFIFOINT_LVL_4                   (3u << 18)
#define QSPI_u32GLOBALCON1_PT1_EVT_BUSY                      (0u << 20)
#define QSPI_u32GLOBALCON1_PT1_EVT_SCLKPC                    (1u << 20)
#define QSPI_u32GLOBALCON1_PT1_EVT_SOF                       (2u << 20)
#define QSPI_u32GLOBALCON1_PT1_EVT_TBE                       (3u << 20)
#define QSPI_u32GLOBALCON1_PT1_EVT_RBF                       (4u << 20)
#define QSPI_u32GLOBALCON1_PT1_EVT_EOF                       (5u << 20)
#define QSPI_u32GLOBALCON1_PT1_EVT_DNA                       (6u << 20)
#define QSPI_u32GLOBALCON1_PT1_EVT_CONT                      (1u << 20)
#define QSPI_u32GLOBALCON1_PT2_EVT_BUSY                      (0u << 23)
#define QSPI_u32GLOBALCON1_PT2_EVT_SCLKPC                    (1u << 23)
#define QSPI_u32GLOBALCON1_PT2_EVT_SOF                       (2u << 23)
#define QSPI_u32GLOBALCON1_PT2_EVT_TBE                       (3u << 23)
#define QSPI_u32GLOBALCON1_PT2_EVT_RBF                       (4u << 23)
#define QSPI_u32GLOBALCON1_PT2_EVT_EOF                       (5u << 23)
#define QSPI_u32GLOBALCON1_PT2_EVT_DNA                       (6u << 23)
#define QSPI_u32GLOBALCON1_PT2_EVT_CONT                      (1u << 23)
#define QSPI_u32GLOBALCON1_TXFM_COMBINED_MOVE                (0u << 26)
#define QSPI_u32GLOBALCON1_TXFM_SINGLE_MOVE                  (1u << 26)
#define QSPI_u32GLOBALCON1_TXFM_BATCH_MOVE                   (2u << 26)
#define QSPI_u32GLOBALCON1_RXFM_COMBINED_MOVE                (0u << 28)
#define QSPI_u32GLOBALCON1_RXFM_SINGLE_MOVE                  (1u << 28)
#define QSPI_u32GLOBALCON1_RXFM_BATCH_MOVE                   (2u << 28)

/* ECONz register */
#define QSPI_u32ECON_Q_TIME_QUANTUM_1      (0u << 0)
#define QSPI_u32ECON_Q_TIME_QUANTUM_2      (1u << 0)
#define QSPI_u32ECON_Q_TIME_QUANTUM_3      (2u << 0)
#define QSPI_u32ECON_Q_TIME_QUANTUM_4      (3u << 0)
#define QSPI_u32ECON_Q_TIME_QUANTUM_5      (4u << 0)
#define QSPI_u32ECON_Q_TIME_QUANTUM_6      (5u << 0)
#define QSPI_u32ECON_Q_TIME_QUANTUM_64     (63u << 0)
#define QSPI_u32ECON_A_BIT_SEG1_1          (0u << 6)
#define QSPI_u32ECON_A_BIT_SEG1_2          (1u << 6)
#define QSPI_u32ECON_A_BIT_SEG1_3          (2u << 6)
#define QSPI_u32ECON_A_BIT_SEG1_4          (3u << 6)
#define QSPI_u32ECON_B_BIT_SEG2_0          (0u << 8)
#define QSPI_u32ECON_B_BIT_SEG2_1          (1u << 8)
#define QSPI_u32ECON_B_BIT_SEG2_2          (2u << 8)
#define QSPI_u32ECON_B_BIT_SEG2_3          (3u << 8)
#define QSPI_u32ECON_C_BIT_SEG3_0          (0u << 10)
#define QSPI_u32ECON_C_BIT_SEG3_1          (1u << 10)
#define QSPI_u32ECON_C_BIT_SEG3_2          (2u << 10)
#define QSPI_u32ECON_C_BIT_SEG3_3          (3u << 10)
#define QSPI_u32ECON_CPH_PHASE_0           (0u << 12)
#define QSPI_u32ECON_CPH_PHASE_1           (1u << 12)
#define QSPI_u32ECON_CPOL_POLARITY_LOW     (0u << 13)
#define QSPI_u32ECON_CPOL_POLARITY_HIGH    (1u << 13)
#define QSPI_u32ECON_PAREN_PARITY_DISA     (0u << 14)
#define QSPI_u32ECON_PAREN_PARITY_ENA      (1u << 14)
#define QSPI_u32ECON_BE_PERM_DISA          (0u << 30)
#define QSPI_u32ECON_BE_PERM_16BIT_BIG_END (1u << 30)
#define QSPI_u32ECON_BE_PERM_32BIT_BIG_END (2u << 30)

/* BACON register */
#define QSPI_u32BACON_CS_0      (0u << 28)
#define QSPI_u32BACON_CS_1      (1u << 28)
#define QSPI_u32BACON_CS_2      (2u << 28)
#define QSPI_u32BACON_CS_3      (3u << 28)
#define QSPI_u32BACON_CS_4      (4u << 28)
#define QSPI_u32BACON_CS_5      (5u << 28)
#define QSPI_u32BACON_CS_6      (6u << 28)
#define QSPI_u32BACON_CS_7      (7u << 28)
#define QSPI_u32BACON_CS_8      (8u << 28)
#define QSPI_u32BACON_CS_9      (9u << 28)
#define QSPI_u32BACON_CS_10     (10u << 28)
#define QSPI_u32BACON_CS_11     (11u << 28)
#define QSPI_u32BACON_CS_12     (12u << 28)
#define QSPI_u32BACON_CS_13     (13u << 28)
#define QSPI_u32BACON_CS_14     (14u << 28)
#define QSPI_u32BACON_CS_15     (15u << 28)

#define QSPI_u32BACON_DL_1  (0u << 23)
#define QSPI_u32BACON_DL_2  (1u << 23)
#define QSPI_u32BACON_DL_3  (2u << 23)
#define QSPI_u32BACON_DL_4  (3u << 23)
#define QSPI_u32BACON_DL_5  (4u << 23)
#define QSPI_u32BACON_DL_6  (5u << 23)
#define QSPI_u32BACON_DL_7  (6u << 23)
#define QSPI_u32BACON_DL_8  (7u << 23)
#define QSPI_u32BACON_DL_9  (8u << 23)
#define QSPI_u32BACON_DL_10 (9u << 23)
#define QSPI_u32BACON_DL_11 (10u << 23)
#define QSPI_u32BACON_DL_12 (11u << 23)
#define QSPI_u32BACON_DL_13 (12u << 23)
#define QSPI_u32BACON_DL_14 (13u << 23)
#define QSPI_u32BACON_DL_15 (14u << 23)
#define QSPI_u32BACON_DL_16 (15u << 23)
#define QSPI_u32BACON_DL_17 (16u << 23)
#define QSPI_u32BACON_DL_18 (17u << 23)
#define QSPI_u32BACON_DL_19 (18u << 23)
#define QSPI_u32BACON_DL_20 (19u << 23)
#define QSPI_u32BACON_DL_21 (20u << 23)
#define QSPI_u32BACON_DL_22 (21u << 23)
#define QSPI_u32BACON_DL_23 (22u << 23)
#define QSPI_u32BACON_DL_24 (23u << 23)
#define QSPI_u32BACON_DL_25 (24u << 23)
#define QSPI_u32BACON_DL_26 (25u << 23)
#define QSPI_u32BACON_DL_27 (26u << 23)
#define QSPI_u32BACON_DL_28 (27u << 23)
#define QSPI_u32BACON_DL_29 (28u << 23)
#define QSPI_u32BACON_DL_30 (29u << 23)
#define QSPI_u32BACON_DL_31 (30u << 23)
#define QSPI_u32BACON_DL_32 (31u << 23)

#define QSPI_u32BACON_BYTE_BIT_LENGTH     (0u << 22)
#define QSPI_u32BACON_BYTE_BYTE_LENGTH    (1u << 22)
#define QSPI_u32BACON_MSB_LSB_FIRST      (0u << 21)
#define QSPI_u32BACON_MSB_MSB_FIRST      (1u << 21)
#define QSPI_u32BACON_UINT_PT1_EVT_ENA   (0u << 20)
#define QSPI_u32BACON_UINT_PT1_EVT_DISA  (1u << 20)

#define QSPI_u32BACON_PARTYP_EVEN_PARITY  (0u << 19)
#define QSPI_u32BACON_PARTYP_ODD_PARITY   (1u << 19)

#define QSPI_u32BACON_TRAIL_1_UNIT          (0u << 16)
#define QSPI_u32BACON_TRAIL_2_UNIT          (1u << 16)
#define QSPI_u32BACON_TRAIL_3_UNIT          (2u << 16)
#define QSPI_u32BACON_TRAIL_4_UNIT          (3u << 16)
#define QSPI_u32BACON_TRAIL_5_UNIT          (4u << 16)
#define QSPI_u32BACON_TRAIL_6_UNIT          (5u << 16)
#define QSPI_u32BACON_TRAIL_7_UNIT          (6u << 16)
#define QSPI_u32BACON_TRAIL_8_UNIT          (7u << 16)

#define QSPI_u32BACON_TPRE_LENGTH_1          (0u << 13)
#define QSPI_u32BACON_TPRE_LENGTH_4          (1u << 13)
#define QSPI_u32BACON_TPRE_LENGTH_16         (2u << 13)
#define QSPI_u32BACON_TPRE_LENGTH_64         (3u << 13)
#define QSPI_u32BACON_TPRE_LENGTH_256        (4u << 13)
#define QSPI_u32BACON_TPRE_LENGTH_424        (5u << 13)
#define QSPI_u32BACON_TPRE_LENGTH_4096       (6u << 13)
#define QSPI_u32BACON_TPRE_LENGTH_16384      (7u << 13)

#define QSPI_u32BACON_LEAD_1_UNIT          (0u << 10)
#define QSPI_u32BACON_LEAD_2_UNIT          (1u << 10)
#define QSPI_u32BACON_LEAD_3_UNIT          (2u << 10)
#define QSPI_u32BACON_LEAD_4_UNIT          (3u << 10)
#define QSPI_u32BACON_LEAD_5_UNIT          (4u << 10)
#define QSPI_u32BACON_LEAD_6_UNIT          (5u << 10)
#define QSPI_u32BACON_LEAD_7_UNIT          (6u << 10)
#define QSPI_u32BACON_LEAD_8_UNIT          (7u << 10)

#define QSPI_u32BACON_LPRE_LENGTH_1          (0u << 7)
#define QSPI_u32BACON_LPRE_LENGTH_4          (1u << 7)
#define QSPI_u32BACON_LPRE_LENGTH_16         (2u << 7)
#define QSPI_u32BACON_LPRE_LENGTH_64         (3u << 7)
#define QSPI_u32BACON_LPRE_LENGTH_256        (4u << 7)
#define QSPI_u32BACON_LPRE_LENGTH_424        (5u << 7)
#define QSPI_u32BACON_LPRE_LENGTH_4096       (6u << 7)
#define QSPI_u32BACON_LPRE_LENGTH_16384      (7u << 7)

#define QSPI_u32BACON_IDLE_1_UNIT          (0u << 4)
#define QSPI_u32BACON_IDLE_2_UNIT          (1u << 4)
#define QSPI_u32BACON_IDLE_3_UNIT          (2u << 4)
#define QSPI_u32BACON_IDLE_4_UNIT          (3u << 4)
#define QSPI_u32BACON_IDLE_5_UNIT          (4u << 4)
#define QSPI_u32BACON_IDLE_6_UNIT          (5u << 4)
#define QSPI_u32BACON_IDLE_7_UNIT          (6u << 4)
#define QSPI_u32BACON_IDLE_8_UNIT          (7u << 4)

#define QSPI_u32BACON_IPRE_LENGTH_1          (0u << 1)
#define QSPI_u32BACON_IPRE_LENGTH_4          (1u << 1)
#define QSPI_u32BACON_IPRE_LENGTH_16         (2u << 1)
#define QSPI_u32BACON_IPRE_LENGTH_64         (3u << 1)
#define QSPI_u32BACON_IPRE_LENGTH_256        (4u << 1)
#define QSPI_u32BACON_IPRE_LENGTH_424        (5u << 1)
#define QSPI_u32BACON_IPRE_LENGTH_4096       (6u << 1)
#define QSPI_u32BACON_IPRE_LENGTH_16384      (7u << 1)

#define QSPI_u32BACON_LAST_LAST           (1u << 0)
#define QSPI_u32BACON_LAST_NOT_LAST       (0u << 0)

#define SPI_HW_MODULE  ((volatile Ifx_QSPI *)(void *) &(MODULE_QSPI0))

/**********************************************************************************************************************/
/* TYPEDEF                                                                                                            */
/**********************************************************************************************************************/


/**********************************************************************************************************************/
/* VARIABLES                                                                                                          */
/**********************************************************************************************************************/

/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/
/************************************************ <AUTO_MACRO_HEADER> *************************************************/
/*                                                                                                                    */
/* !Description :                                                                                                     */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/************************************************ </AUTO_MACRO_HEADER> ************************************************/
/* !LastAuthor  :  E. Moas                                                                                            */
/*********************************************** <AUTO_MACRO_PROTOTYPE> ***********************************************/

#endif /* QSPI_H */

/*---------------------------------------------------- end of file ---------------------------------------------------*/
