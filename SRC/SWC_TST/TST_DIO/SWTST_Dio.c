/**********************************************************************************************************************/
/* !Layer           : SWTST                                                                                           */
/*                                                                                                                    */
/* !Component       : SWTST                                                                                           */
/* !Description     : Management of Software Tests                                                                    */
/*                                                                                                                    */
/* !Module          : SWTST_DIO */
/* !Description     : TBD: description of the contents of this file                                                   */
/*                                                                                                                    */
/* !File            : SWTST_Dio.c */
/*                                                                                                                    */
/* !Target          : Infineon_tc27 */
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
#include "Dio.h"

#include "DIO_WrapAPI.h"

#include "RbBaseSw.h"

/**********************************************************************************************************************/
/* MACRO FUNCTIONS                                                                                                    */
/**********************************************************************************************************************/
#define SWTST_vidDIO_CLR_ERR_INFO() \
do \
{ \
   SWTST_u8DioTstErrId    = 0; \
   SWTST_u32DioTstErrInfo = 0; \
} \
while(0)

#define SWTST_vidDIO_SET_ERR_INFO(u8ErrId, u32Info) \
do \
{ \
   SWTST_u8DioTstErrId    = (u8ErrId); \
   SWTST_u32DioTstErrInfo = (u32Info); \
} \
while(0)


/**********************************************************************************************************************/
/* FUNCTIONS DEFINITION                                                                                               */
/**********************************************************************************************************************/
#define SWTST_START_SEC_CODE
#include "MemMap.h"

/**********************************************************************************************************************/
/* !FuncName    : SWTST_vidDioInit */
/* !Description : Initialize SWTST for Dio. */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/**********************************************************************************************************************/
void SWTST_vidDioInit(void)
{
   uint8 u8LocTstNr;


   SWTST_u8DioTstNrNm1 = SWTST_ku8DioTstNrC;

   /* Manage test's resume */
   SWTST_vu8DioRunngTstNr = SWTST_u8DioResumeTstNr;
   SWTST_u8DioResumeTstNr = 0;

   u8LocTstNr = SWTST_vu8DioRunngTstNr;
   switch (u8LocTstNr)
   {
      case 4:
         /* do some actions */

         // if (/* error */)
         // {
            // SWTST_vbDioTstErr = TRUE;
         // }
         // SWTST_vu8DioRunngTstNr = 0;
         // SWTST_vbDioTstDone     = TRUE;
         // SWTST_u8DioTstDoneNr   = u8LocTstNr;
         break;

      default:
         /* Do nothing */
         break;
   }
}

/**********************************************************************************************************************/
/* !FuncName    : SWTST_vidDioMngTest */
/* !Description : Manage Dio tests. */
/*                It allows to handle the activation of tests in only 1 location.                                     */
/*                This function can be executed in a periodic task or in the background.                              */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/**********************************************************************************************************************/

//uint8 Temp_Bin = 0;
//uint8 Pin_Index = 0;

uint16 Max_CpuLoad;
uint16 CpuLoad;

void SWTST_vidDioMngTest(void)
{
   uint8   u8LocTstNr;
   boolean bLocDone;


   if (SWTST_kbDioTstEnaC == TRUE)
   {
      u8LocTstNr = SWTST_ku8DioTstNrC;
   }
   else
   {
      u8LocTstNr = 0;
   }
   if (u8LocTstNr != SWTST_u8DioTstNrNm1)
   {
      /* !Comment: manage switch of test:  stop previous test */
      switch (SWTST_u8DioTstNrNm1)
      {
         default:
            /* Do nothing */
            break;
      }
      /* !Comment: reset global variables */
      SWTST_vbDioTstDone     = FALSE;
      SWTST_vbDioTstErr      = FALSE;
      SWTST_vu8DioRunngTstNr = 0;
      SWTST_u8DioTstDoneNr   = 0;
      /* !Comment: manage switch of test:  start new test       */
      /*           following actions will be executed only once */
      switch (u8LocTstNr)
      {
         case 1:
            /* Test: Run a single action. */
            /******************************/
            /* do some actions */

            // if (/* error */)
            // {
               // SWTST_vbDioTstErr = TRUE;
            // }
            SWTST_vbDioTstDone   = TRUE;
            SWTST_u8DioTstDoneNr = u8LocTstNr;
            break;

         case 2:
            /* Test: Run continuous periodic actions (never ends unless test number is changed). */
            /*************************************************************************************/
	      Dio_WriteChannel(DioConf_DioChannel_M_SOL_HS_DEN_1,             SWTST_kbDioWrM_SOL_HS_DEN_1);  
	      Dio_WriteChannel(DioConf_DioChannel_M_SOL_HS_CMD_1,             SWTST_kbDioWrM_SOL_HS_CMD_1); 
		Dio_WriteChannel(DioConf_DioChannel_M_KEY_LOCK_CMD,             SWTST_kbDioWrM_KEY_LOCK_CMD);
		Dio_WriteChannel(DioConf_DioChannel_M_SHIFT_LOCK_CMD,             SWTST_kbDioWrM_SHIFT_LOCK_CMD);	

		Dio_WriteChannel(DioConf_DioChannel_M_SOL_HS_DEN_2,        SWTST_kbDioWrM_SOLENOID_HS_DEN_2);
		Dio_WriteChannel(DioConf_DioChannel_M_SOL_HS_CMD_2,             SWTST_kbDioWrM_SOLENOID_HS_CMD_2); 
		Dio_WriteChannel(DioConf_DioChannel_M_REV_LAMP_REL_CMD,             SWTST_kbDioWrM_REV_LAMP_REL_CMD); 
		Dio_WriteChannel(DioConf_DioChannel_M_STARTER_REL_CMD,             SWTST_kbDioWrM_STARTER_REL_CMD); 

		Dio_WriteChannel(DioConf_DioChannel_M_SBC_WAK,                       SWTST_kbDioWrM_SBC_WAK);
		Dio_WriteChannel(DioConf_DioChannel_M_SUPPLY_WDI, 		SWTST_kbDioWrM_SUPPLY_WDI);
		Dio_WriteChannel(DioConf_DioChannel_M_SUPPLY_ERROR,         SWTST_KbDioWrM_SUPPLY_ERROR);
		Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_W,              SWTST_kbDioWrM_SUBROM_W);
		Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CS,              SWTST_kbDioWrM_SUBROM_CS);
		Dio_WriteChannel(DioConf_DioChannel_M_SUBROM_CLK,              SWTST_kbDioWrM_SUBROM_CLK);
		Dio_WriteChannel(DioConf_DioChannel_M_TLE8242_ENA,            SWTST_kbDioWrM_TLE8242_ENA);
		Dio_WriteChannel(DioConf_DioChannel_M_TLE8242_PHASE_SYNC, SWTST_kbDioWrM_TLE8242_PHASE_SYNC);

		//Dio_WriteChannel(DioConf_DioChannel_M_RESERVED_SW_1, SWTST_bDioWrM_RESERVED_SW_1);
		//Dio_WriteChannel(DioConf_DioChannel_M_RESERVED_SW_2, SWTST_bDioWrM_RESERVED_SW_2);


		SWTST_bDioRdM_MANUAL_DOWN  = Dio_ReadChannel(DioConf_DioChannel_M_MANUAL_DOWN);		
		SWTST_bDioRdM_FOOT_BRAKE  = Dio_ReadChannel(DioConf_DioChannel_M_FOOT_BRAKE);	
		SWTST_bDioRdM_SNOW_MODE  = Dio_ReadChannel(DioConf_DioChannel_M_SNOW_MODE);
		SWTST_bDioRdM_SPORT_MODE  = Dio_ReadChannel(DioConf_DioChannel_M_SPORT_MODE);
		SWTST_bDioRdM_HAND_BRAKE  = Dio_ReadChannel(DioConf_DioChannel_M_HAND_BRAKE);
		SWTST_bDioRdM_RESERVED_SW_1  = Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_1);
		SWTST_bDioRdM_RESERVED_SW_2  = Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_2);
		SWTST_bDioRdM_RESERVED_SW_3  = Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_3);
		SWTST_bDioRdM_RESERVED_SW_4  = Dio_ReadChannel(DioConf_DioChannel_M_RESERVED_SW_4);
		SWTST_bDioRdM_REV_LAMP_REL_DIAG  = Dio_ReadChannel(DioConf_DioChannel_M_REV_LAMP_REL_DIAG);
		SWTST_bDioRdM_STARTER_REL_DIAG  = Dio_ReadChannel(DioConf_DioChannel_M_STARTER_REL_DIAG);
		SWTST_bDioRdM_IGN_INPUT  = Dio_ReadChannel(DioConf_DioChannel_M_IGN_INPUT);
		SWTST_bDioRdM_SUPPLY_SAFE_STATE  = Dio_ReadChannel(DioConf_DioChannel_M_SUPPLY_SAFE_STATE);
		SWTST_bDioRdM_SUBROM_R  = Dio_ReadChannel(DioConf_DioChannel_M_SUBROM_R);
		SWTST_bDioRdM_TLE8242_FAULT  = Dio_ReadChannel(DioConf_DioChannel_M_TLE8242_FAULT);
		SWTST_bDioRdM_MANUAL_UP  = Dio_ReadChannel(DioConf_DioChannel_M_MANUAL_UP);
		SWTST_bDioRdM_MANUAL_MODE  = Dio_ReadChannel(DioConf_DioChannel_M_MANUAL_MODE);
		SWTST_bDioRdM_SHIFT_LOCK_DIAG  = Dio_ReadChannel(DioConf_DioChannel_M_SHIFT_LOCK_DIAG);
		SWTST_bDioRdM_KEY_LOCK_DIAG  = Dio_ReadChannel(DioConf_DioChannel_M_KEY_LOCK_DIAG);
		
	      SWTST_vu8DioRunngTstNr = u8LocTstNr;
            u8LocTstNr = 0;
		//test the DIO wrapper API for customer
		//ShrExp_Get_Switch(Pin_Index, &Temp_Bin); 
#if 0

		ShrExp_Get_Switch(SWTST_kbDioRd_SwitchIdx, &SWTST_kbDioRd_SwitchValue); 

		ShrExp_Set_SolenoidFeed(SWTST_kbDioWr_Set_SolenoidFeedIdx, SWTST_kbDioWr_Set_SolenoidFeedOnOff);

		ShrExp_Set_StartEnable(SWTST_kbDioWr_Set_StartEnableOnOff);

		ShrExp_Set_Relay(SWTST_kbDioWr_Set_RelayOnOff);

		ShrExp_Set_OnOffSolenoid(SWTST_kbDioWr_Set_OnOffSolenoidIdx, SWTST_kbDioWr_Set_OnOffSolenoidOnOff);
#endif
            break;

         case 3:
            /* Test: Run periodic actions until end conditions are reached. */
            /****************************************************************/
            SWTST_vu8DioRunngTstNr = u8LocTstNr;
            break;

         case 4:
            /* Test: Generate a reset and resume the test after the reset by doing a single action during init. */
            /****************************************************************************************************/
            SWTST_u8DioResumeTstNr = u8LocTstNr;
            //ResetMicro();
            break;

         case 5:
            /* Test: Test sequence. */
            /****************************************************************/
            //bLocDone = SWTST_bDioTstSeqExample();
            //if (bLocDone == FALSE)
            //{
            //   SWTST_vbDioTstErr = TRUE;
            //}
            SWTST_vbDioTstDone   = TRUE;
            SWTST_u8DioTstDoneNr = u8LocTstNr;
            break;
			
	   case 6:
	   /*******************************************
		TCU project, test the DIO wrapper API
	   *******************************************/
		ShrExp_Get_Switch(SWTST_kbDioRd_SwitchIdx, &SWTST_kbDioRd_SwitchValue); 

		ShrExp_Set_SolenoidFeed(SWTST_kbDioWr_Set_SolenoidFeedIdx, SWTST_kbDioWr_Set_SolenoidFeedOnOff);

		ShrExp_Set_StartEnable(SWTST_kbDioWr_Set_StartEnableOnOff);

		ShrExp_Set_Relay(SWTST_kbDioWr_Set_RelayOnOff);

		ShrExp_Set_OnOffSolenoid(SWTST_kbDioWr_Set_OnOffSolenoidIdx, SWTST_kbDioWr_Set_OnOffSolenoidOnOff);

		Shrexp_get_CpuLd(&CpuLoad, &Max_CpuLoad);
		
		break;
		
	   case 7:
	   	
	   	ShrExp_Clear_SbrmStatus();
	 	break;
		
         default:
            /* Do nothing */
            break;
      }
      SWTST_u8DioTstNrNm1 = u8LocTstNr;
   }
}

/**********************************************************************************************************************/
/* !FuncName    : SWTST_vidDioPeriodicTaskExample */
/* !Description : Example of periodic actions.                                                                        */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/**********************************************************************************************************************/
void SWTST_vidDioPeriodicTaskExample(void)
{
   uint8 u8LocTstNr;


   u8LocTstNr = SWTST_vu8DioRunngTstNr;
   switch (u8LocTstNr)
   {
      case 2:
         /* do some actions (never ends unless test number is changed) */
         break;

      // case 3:
         // if (/* end of test not reached */)
         // {
            // /* do some actions */
         // }
         // else
         // {
            // if (/* error */)
            // {
               // SWTST_vbDioTstErr = TRUE;
            // }
            // SWTST_vu8DioRunngTstNr = 0;
            // SWTST_vbDioTstDone     = TRUE;
            // SWTST_u8DioTstDoneNr   = u8LocTstNr;
         // }
         // break;

      default:
         /* Do nothing */
         break;
   }
}

/**********************************************************************************************************************/
/* !FuncName    : SWTST_bDioTstSeqExample */
/* !Description : Example of test sequence.                                                                           */
/*                                                                                                                    */
/* !Reference   : NONE                                                                                                */
/* !Trace_To    : NONE                                                                                                */
/*                                                                                                                    */
/* !LastAuthor  :                                                                                                     */
/**********************************************************************************************************************/
boolean SWTST_bDioTstSeqExample(void)
{
   // SWTST_vidDIO_CLR_ERR_INFO();

   // /* step 1 */
   // if (/* error */)
   // {
      // SWTST_vidDIO_SET_ERR_INFO(1, /* wrong value detected */);
      // return(FALSE);
   // }

   // /* step 2 */
   // if (/* error */)
   // {
      // SWTST_vidDIO_SET_ERR_INFO(2, /* wrong value detected */);
      // return(FALSE);
   // }

   // /* step 3 */
   // if (/* error */)
   // {
      // SWTST_vidDIO_SET_ERR_INFO(3, /* wrong value detected */);
      // return(FALSE);
   // }

   return(TRUE);
}
#define SWTST_STOP_SEC_CODE
#include "MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
