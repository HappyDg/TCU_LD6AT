/**********************************************************************************************************************/
/* !Layer           : SWTST                                                                                           */
/*                                                                                                                    */
/* !Component       : SWTST                                                                                           */
/* !Description     : Management of Software Tests                                                                    */
/*                                                                                                                    */
/* !Module          : SWTST_EVP */
/* !Description     : TBD: description of the contents of this file                                                   */
/*                                                                                                                    */
/* !File            : SWTST_EVP.c */
/*                                                                                                                    */
/* !Target          :  */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/* PVCS Information                                                                                                   */
/* $Archive::   P:/VE_S97/LOG/70_SubProject/Archives/S97_SWA_BSW/SWTST_Mmu.c_v                                      $*/
/* $Revision::   1.1                                                                                                 $*/
/* $Author::   xfeng                                  $$Date::   30 Jun 2014 16:25:20                                $*/
/**********************************************************************************************************************/

#include "Std_Types.h"
#include "SWTST.h"
#include "SWTST_L.h"
#include "EVP.h"
#include "EVP_L.h"

/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/
#define SWTST_vidEVP_CLR_ERR_INFO() \
do \
{ \
   SWTST_u8EVPTstErrId    = 0; \
   SWTST_u32EVPTstErrInfo = 0; \
} \
while(0)

#define SWTST_vidEVP_SET_ERR_INFO(u8ErrId, u32Info) \
do \
{ \
   SWTST_u8EVPTstErrId    = (u8ErrId); \
   SWTST_u32EVPTstErrInfo = (u32Info); \
} \
while(0)


/**********************************************************************************************************************/
/* FUNCTIONS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define SWTST_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************/
/* !FuncName    : SWTST_vidEVPInit */
/* !Description : Initialize SWTST for EVP. */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/**********************************************************************************************************************/
void SWTST_vidEVPInit(void)
{
   uint8 u8LocTstNr;


   SWTST_u8EVPTstNrNm1 = SWTST_ku8EVPTstNrC;

   /* Manage test's resume */
   SWTST_vu8EVPRunngTstNr = SWTST_u8EVPResumeTstNr;
   SWTST_u8EVPResumeTstNr = 0;

   u8LocTstNr = SWTST_vu8EVPRunngTstNr;
   switch (u8LocTstNr)
   {
      case 4:
         /* do some actions */

         // if (/* error */)
         // {
            // SWTST_vbEVPTstErr = TRUE;
         // }
         SWTST_vu8EVPRunngTstNr = 0;
         SWTST_vbEVPTstDone     = TRUE;
         SWTST_u8EVPTstDoneNr   = u8LocTstNr;
         break;

      default:
         /* Do nothing */
         break;
   }
}

/**********************************************************************************************************************/
/* !FuncName    : SWTST_vidEVPMngTest */
/* !Description : Manage EVP tests. */
/*                It allows to handle the activation of tests in only 1 location.                                     */
/*                This function can be executed in a periodic task or in the background.                              */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/**********************************************************************************************************************/
void SWTST_vidEVPMngTest(void)
{
   uint8   u8LocTstNr;
   boolean bLocDone;
   boolean bLocSts;
   uint32  u32LocGrpIdx;
   uint32  u32LocChanIdx;  


   if (SWTST_kbEVPTstEnaC == TRUE)
   {
      u8LocTstNr = SWTST_ku8EVPTstNrC;
   }
   else
   {
      u8LocTstNr = 0;
   }
   if (u8LocTstNr != SWTST_u8EVPTstNrNm1)
   {
      /* !Comment: manage switch of test:  stop previous test */
      switch (SWTST_u8EVPTstNrNm1)
      {
         default:
            /* Do nothing */
            break;
      }
      /* !Comment: reset global variables */
      SWTST_vbEVPTstDone     = FALSE;
      SWTST_vbEVPTstErr      = FALSE;
      SWTST_vu8EVPRunngTstNr = 0;
      SWTST_u8EVPTstDoneNr   = 0;
      /* !Comment: manage switch of test:  start new test       */
      /*           following actions will be executed only once */
      switch (u8LocTstNr)
      {
         case 1:
            /* Test: Run a single action. */
            /******************************/
            /* do some actions */
 /*           if (bLocSts != TRUE)
            {
               SWTST_vbEVPTstErr = TRUE;
            } */
            SWTST_vbEVPTstDone   = TRUE;
            SWTST_u8EVPTstDoneNr = u8LocTstNr;
            break;

         case 2:
            /* Test: Run continuous periodic actions (never ends unless test number is changed). */
            /*************************************************************************************/
            for (u32LocGrpIdx = 0; u32LocGrpIdx < EVP_u8NB_GROUP; u32LocGrpIdx++)
            {
               EVP_au32Prd[u32LocGrpIdx] = SWTST_aku32Prd[u32LocGrpIdx];
               for (u32LocChanIdx = 0; u32LocChanIdx < EVP_u32GRP_SIZE_MAX; u32LocChanIdx++)
               {
                  EVP_au16Duty[u32LocGrpIdx][u32LocChanIdx] = SWTST_aku16Duty[u32LocGrpIdx][u32LocChanIdx];
               }
            }
            SWTST_vbEVPTstErr = !bLocSts;
            SWTST_vu8EVPRunngTstNr = u8LocTstNr;
            u8LocTstNr = 0;
            break;

         case 3:
            /* Test: Run periodic actions until end conditions are reached. */
            /****************************************************************/
            SWTST_vu8EVPRunngTstNr = u8LocTstNr;
            break;

         case 4:
            /* Test: Generate a reset and resume the test after the reset by doing a single action during init. */
            /****************************************************************************************************/
            SWTST_u8EVPResumeTstNr = u8LocTstNr;
            //ResetMicro();
            break;

         case 5:
            /* Test: Test sequence. */
            /****************************************************************/
            // bLocDone = SWTST_bEVPTstSeqExample();
            // if (bLocDone == FALSE)
            // {
               // SWTST_vbEVPTstErr = TRUE;
            // }
            // SWTST_vbEVPTstDone   = TRUE;
            // SWTST_u8EVPTstDoneNr = u8LocTstNr;
            break;

         default:
            /* Do nothing */
            break;
      }
      SWTST_u8EVPTstNrNm1 = u8LocTstNr;
   }
}

/**********************************************************************************************************************/
/* !FuncName    : SWTST_vidEVPPeriodicTaskExample */
/* !Description : Example of periodic actions.                                                                        */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/*********************************************************************************************************************/
void SWTST_vidEVPPeriodicTaskExample(void)
{
   // uint8 u8LocTstNr;


   // u8LocTstNr = SWTST_vu8EVPRunngTstNr;
   // switch (u8LocTstNr)
   // {
      // case 2:
         // do some actions (never ends unless test number is changed)
         // break;

      // case 3:
         // if (/* end of test not reached)
         // {
            // do some actions
         // }
         // else
         // {
            // if (/* error)
            // {
               // SWTST_vbEVPTstErr = TRUE;
            // }
            // SWTST_vu8EVPRunngTstNr = 0;
            // SWTST_vbEVPTstDone     = TRUE;
            // SWTST_u8EVPTstDoneNr   = u8LocTstNr;
         // }
         // break;

      // default:
         // Do nothing
         // break;
   // } */
}

/**********************************************************************************************************************/
/* !FuncName    : SWTST_bEVPTstSeqExample */
/* !Description : Example of test sequence.                                                                           */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/**********************************************************************************************************************/
boolean SWTST_bEVPTstSeqExample(void)
{
   // SWTST_vidEVP_CLR_ERR_INFO();

   // /* step 1 */
   // if (/* error */)
   // {
      // SWTST_vidEVP_SET_ERR_INFO(1, /* wrong value detected */);
      // return(FALSE);
   // }

   // /* step 2 */
   // if (/* error */)
   // {
      // SWTST_vidEVP_SET_ERR_INFO(2, /* wrong value detected */);
      // return(FALSE);
   // }

   // /* step 3 */
   // if (/* error */)
   // {
      // SWTST_vidEVP_SET_ERR_INFO(3, /* wrong value detected */);
      // return(FALSE);
   // }

   return(TRUE);
}
#define SWTST_STOP_SEC_CODE
#include "MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
