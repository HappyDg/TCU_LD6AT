/******************************************************************************/
/*                                                                            */
/* !Layer          : BSW                                                      */
/*                                                                            */
/* !Component      : SRV                                                      */
/*                                                                            */
/* !Module         : SPY                                                      */
/* !Description    : Definitions for the component                            */
/*                                                                            */
/* !File           : SPY_DAQ.C                                                */
/*                                                                            */
/* !Target         : Hitachi                                                  */
/*                                                                            */
/* !Vendor         : VEMS                                                     */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2011 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   P:/VE_Onduleur_Gen1_Michelin/LOG/60_ComponentArchive/Archives$*/
/* $Revision::   1.3      $$Author::   hlaos          $$Date::   30 Jan 2012 $*/
/******************************************************************************/
/* !VnrOff : Names imposed by the customer                                    */
/******************************************************************************/
/* DAQ.1 / SPY_vidInit                                                        */
/* DAQ.2 / SPY_vidDaqListTxInit                                               */
/* DAQ.3 / SPY_bWrOdt                                                         */
/* DAQ.4 / SPY_vidDaqListStopd                                                */
/* DAQ.5 / SPY_vidWrBuf                                                       */
/* DAQ.6 / SPY_vidStopDataAcq                                                 */
/******************************************************************************/

#include "spy.h"
#include "spy_l.h"
#include "spy_cfg.h"

#include "CCP.h"
#include "CCP_L.h"
#include "CCP_Cfg.h"
#include "CCP_USR.h"
#include "CCPUSR.h"
#include "CCPUSR_Cfg.h"
#include "CCPUSR_CANIF_CFG.h"

//#include "os_api.h"
#include "Os.h"
#include "micro.h"



/**********************************************************************************************************************/
/* TYPEDEF                                                                                                            */
/**********************************************************************************************************************/
typedef enum
{
   SPY_enuSTT_INIT      = 0,
   SPY_enuSTT_RUNNING   = 1,
   SPY_enuSTT_STARTED   = 2,
   SPY_enuSTT_FINISHED  = 3,
   SPY_enuSTT_STOPPED   = 4,
   SPY_enuSTT_UPLOADING = 5,
   SPY_enuSTT_STORED    = 6
}
SPY_tenuStt;


/**********************************************************************************************************************/
/* DEFINES DEFINITION                                                                                                 */
/**********************************************************************************************************************/
#define SPY_u16NR_OF_SMPLS      SPY_MAX_QTY_DATA
#define SPY_u16NR_OF_RMNG_SMPLS SPY_MAX_QTY_DATA_POST_EVENT


/**********************************************************************************************************************/
/* VARIABLES DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define SPY_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"
   uint8       SPY_au8Smpls[SPY_MAX_QTY_DATA][SPY_NB_SGN];
   uint8 **    SPY_ppu8DaqListElmAdr;
   SPY_tenuStt SPY_enuStt;    
#define SPY_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"


/**********************************************************************************************************************/
/* FUNCTIONS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define SPY_START_SEC_CODE
#include "MemMap.h"

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SPY_vidInit                                                                                         */
/*                                                                                                                    */
/* !Description : Initialisation of SPY module                                                                        */
/* !Number      : 1                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !LastAuthor  :                                                                                                     */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void SPY_vidInit(void)
{
   SPY_u16NrOfElmsToTx       = 0;
   SPY_u16DaqListFirstElmIdx = 0;
   SPY_ppu8DaqListElmAdr     = NULL_PTR;
   SPY_u16SmplIdx            = 0;
   SPY_u16TrigSmplIdx        = 0;
   SPY_u16RmngSmplIdx        = SPY_u16NR_OF_RMNG_SMPLS;
   SPY_bBufFull              = FALSE;
   SPY_enuStt                = SPY_enuSTT_INIT;
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SPY_vidDaqListTxInit                                                                                */
/*                                                                                                                    */
/* !Description : Initialisation of DAQ parameters for SPY module                                                     */
/* !Number      : 2                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !LastAuthor  :                                                                                                     */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void SPY_vidDaqListTxInit(uint8 u8ListIdx, uint8 **ppu8DaqListElmAdr, uint16 u16FirstElmIdx, uint8 u8OdtLstIdx)
{
   if (u8ListIdx == SPY_DAQ_EVENT)
   {
      SPY_u16DaqListFirstElmIdx = u16FirstElmIdx;
      SPY_ppu8DaqListElmAdr     = &ppu8DaqListElmAdr[u16FirstElmIdx];
      SPY_u16NrOfElmsToTx       = (u8OdtLstIdx + 1) * 7;
      if ((SPY_enuStt == SPY_enuSTT_STOPPED) || (SPY_enuStt == SPY_enuSTT_INIT))
      {
         SPY_enuStt = SPY_enuSTT_RUNNING;
      }
   }
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SPY_bWrOdt                                                                                          */
/*                                                                                                                    */
/* !Description : Sends data from the buffer SPY_au8Smpls                                                             */
/* !Number      : 3                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !LastAuthor  :                                                                                                     */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
boolean SPY_bWrOdt(uint8 u8ListIdx, uint16 u16FirstElmIdx, uint8 *pu8BufDst)
{
   boolean      bLocWrDone;
   uint16_least u16LocTrigSmplIdx;
   uint16_least u16LocSmplIdx;
   uint16_least u16LocElmAdrIdx;
   uint8      * pu8LocalBufSrc;


   bLocWrDone = FALSE;
   if (  (u8ListIdx == SPY_DAQ_EVENT)
      && (SPY_bBufFull == TRUE)
      )
   {
      SPY_enuStt        = SPY_enuSTT_UPLOADING;
      u16LocElmAdrIdx   = u16FirstElmIdx - SPY_u16DaqListFirstElmIdx;
      u16LocTrigSmplIdx = SPY_u16TrigSmplIdx;
      pu8LocalBufSrc    = &SPY_au8Smpls[u16LocTrigSmplIdx][u16LocElmAdrIdx];

      *pu8BufDst++ = *pu8LocalBufSrc++;
      *pu8BufDst++ = *pu8LocalBufSrc++;
      *pu8BufDst++ = *pu8LocalBufSrc++;
      *pu8BufDst++ = *pu8LocalBufSrc++;
      *pu8BufDst++ = *pu8LocalBufSrc++;
      *pu8BufDst++ = *pu8LocalBufSrc++;
      *pu8BufDst   = *pu8LocalBufSrc;

      if (u16LocElmAdrIdx + 7 >= SPY_u16NrOfElmsToTx)
      {
         u16LocTrigSmplIdx++;
         if (u16LocTrigSmplIdx >= SPY_u16NR_OF_SMPLS)
         {
            u16LocTrigSmplIdx = 0;
         }
         SPY_u16TrigSmplIdx = u16LocTrigSmplIdx;

         u16LocSmplIdx = SPY_u16SmplIdx + 1;
         if (u16LocSmplIdx >= SPY_u16NR_OF_SMPLS)
         {
            SPY_bBufFull  = FALSE;
            u16LocSmplIdx = 0;
            SPY_enuStt    = SPY_enuSTT_FINISHED;
         }
         SPY_u16SmplIdx = u16LocSmplIdx;
      }

      bLocWrDone = TRUE;
   }
   return(bLocWrDone);
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SPY_vidDaqListStopd                                                                                 */
/*                                                                                                                    */
/* !Description : Stops SPY module                                                                                    */
/* !Number      : 4                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !LastAuthor  :                                                                                                     */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void SPY_vidDaqListStopd(uint8 u8ListIdx)
{
   if (u8ListIdx == SPY_DAQ_EVENT)
   {
      SPY_u16NrOfElmsToTx = 0;
      SPY_bBufFull        = FALSE;
      SPY_enuStt          = SPY_enuSTT_STOPPED;
   }
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SPY_vidWrBuf                                                                                        */
/*                                                                                                                    */
/* !Description : Stores data to buffer SPY_au8Smpls                                                                  */
/* !Number      : 5                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !LastAuthor  :                                                                                                     */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void SPY_vidWrBuf(void)
{
   uint16_least u16LocSmplIdx;
   uint16_least u16LocIdx;
   uint16_least u16LocRmngSmplIdx;
   uint16_least u16LocNrOfElms;
   uint8      * pu8Dest;
   uint8     ** ppu8Src;


   u16LocSmplIdx  = SPY_u16SmplIdx;
   u16LocNrOfElms = SPY_u16NrOfElmsToTx;
   if (  (u16LocNrOfElms != 0)
      && (SPY_bBufFull == FALSE)
      )
   {
      pu8Dest    = &SPY_au8Smpls[u16LocSmplIdx][0];
      ppu8Src    = &SPY_ppu8DaqListElmAdr[0];
      u16LocIdx  = (u16LocNrOfElms + 7) >> 3;

      switch(u16LocNrOfElms & 7)
      {
         case 0:  do {  *pu8Dest++ = **ppu8Src++;
         case 7:        *pu8Dest++ = **ppu8Src++;
         case 6:        *pu8Dest++ = **ppu8Src++;
         case 5:        *pu8Dest++ = **ppu8Src++;
         case 4:        *pu8Dest++ = **ppu8Src++;
         case 3:        *pu8Dest++ = **ppu8Src++;
         case 2:        *pu8Dest++ = **ppu8Src++;
         case 1:        *pu8Dest++ = **ppu8Src++;
                      } while(--u16LocIdx > 0);
      }

      u16LocSmplIdx++;
      if (u16LocSmplIdx >= SPY_u16NR_OF_SMPLS)
      {
         u16LocSmplIdx = 0;
      }
      SPY_u16SmplIdx = u16LocSmplIdx;

      u16LocRmngSmplIdx = SPY_u16RmngSmplIdx;
      if (u16LocRmngSmplIdx < SPY_u16NR_OF_RMNG_SMPLS)
      {
         u16LocRmngSmplIdx++;
         if (u16LocRmngSmplIdx >= SPY_u16NR_OF_RMNG_SMPLS)
         {
            SPY_u16TrigSmplIdx = u16LocSmplIdx;
            SPY_u16SmplIdx     = 0;
            SPY_bBufFull       = TRUE; /* Shall be done after setting SPY_u16TrigSmplIdx & SPY_u16SmplIdx */
                                       /* to avoid issue if SPY_bWrOdt preempts this function             */
            SPY_enuStt = SPY_enuSTT_STORED;
         }
         SPY_u16RmngSmplIdx = u16LocRmngSmplIdx; /* Shall be done after setting SPY_bBufFull to avoid */
                                                 /* issue if SPY_vidTrig preempts this function       */
      }
   }
}

/*********************************************** <AUTO_FUNCTION_HEADER> ***********************************************/
/*                                                                                                                    */
/* !FuncName    : SPY_vidStopDataAcq                                                                                  */
/*                                                                                                                    */
/* !Description : Stores data to buffer SPY_au8Smpls                                                                  */
/* !Number      : 6                                                                                                   */
/* !Reference   : NONE                                                                                                */
/*                                                                                                                    */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/********************************************** </AUTO_FUNCTION_HEADER> ***********************************************/
/* !LastAuthor  :                                                                                                     */
/********************************************* <AUTO_FUNCTION_PROTOTYPE> **********************************************/
void SPY_vidStopDataAcq(void)
{
   if (  (SPY_bBufFull == FALSE)
      && (SPY_u16SmplIdx >= SPY_u16NR_OF_RMNG_SMPLS)
      && (  (SPY_enuStt == SPY_enuSTT_RUNNING)
         || (SPY_enuStt == SPY_enuSTT_FINISHED)
         )
      )
   {
      SPY_u16RmngSmplIdx = 0;
      SPY_enuStt         = SPY_enuSTT_STARTED;
   }
}

#define SPY_STOP_SEC_CODE
#include "MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
