/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_SPI                                                 */
/* !Description     : Demo Software to Test SPI APIs                          */
/*                                                                            */
/* !File            : TST_SPI.c                                               */
/* !Description     : Demo Software to Test SPI APIs                          */
/*                                                                            */
/* !Reference       :                                                         */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT VALEO all rights reserved                                        */
/******************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 ******************************************************************************/
#include "Std_Types.h"
#include "Std_Limits.h"
 
#include "TST_SPI.h"
#include "SPI.h"
#include "OS.h"
//#include "INTBSL.h"

#define TST_START_SEC_TST_VAR
#include "TST_MemMap.h"

uint16 TST_SPI_u16SendData_TJA1145;
uint16 TST_SPI_u16EndSeqNotifCounter_TJA1145;
#define TST_STOP_SEC_TST_VAR
#include "TST_MemMap.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

/******************************************************************************/
/* !FuncName    : TST_SPI_vidInit                                             */
/* !Description : Initialization of TST_SPI variables                         */
/*                                                                            */
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
void TST_SPI_vidInit(void)
{
   TST_SPI_u16SendData_TJA1145 = 0xFF05;

   //INTBSL_vidENA_IT(SRC_SPI2_ERR_ISR);
   //INTBSL_vidENA_IT(SRC_SPI2_PHASE_T_ISR);
   //INTBSL_vidENA_IT(SRC_SPI2_USER_ISR);
   //INTBSL_vidENA_IT(DMA_ISR_QSPI2RX);
   //INTBSL_vidENA_IT(DMA_ISR_QSPI2TX);
}

/******************************************************************************/
/* !FuncName    : TST_SPI_vidSendFrameSeq                                     */
/* !Description : Send the frame sequence required                            */
/*                                                                            */
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/


/******************************************************************************/
/* !FuncName    : TST_SPI_vidTLF35584FramesManagement                         */
/* !Description : Manage which frame sequence to be sent                      */
/*                                                                            */
/* !LastAuthor  : A. Elkhazragy                                               */
/******************************************************************************/
void TST_SPI_vidMainFunction(void)
{
   Spi_WriteIB(SpiConf_SpiChannel_TLF35584_CH, (const uint8 *) &TST_SPI_u16SendData_TJA1145);
   Spi_AsyncTransmit(SpiConf_SpiSequence_TLF35584_SEQ);
}

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

/*------------------------------ end of file ---------------------------------*/
