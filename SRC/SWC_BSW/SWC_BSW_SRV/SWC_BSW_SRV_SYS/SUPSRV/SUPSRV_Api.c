/******************************************************************************/
/* !Layer           : SRV                                                     */
/* !Component       : SUPSRV                                                  */
/* !Description     : Supplier Services component                             */
/*                                                                            */
/* !File            : SUPSRV_Api.c                                            */
/* !Description     : SUPSRV services definition                              */
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

#include "FBL_INTF_Cfg.h"
#include "RSTSRV.h"
#include "STARTUP.h"
#include "SUPSRV.h"
#include "SUPSRV_Cfg.h"
#include "SWFAIL.h"


/******************************************************************************/
/* DATA DEFINITION                                                            */
/******************************************************************************/

#define SUPSRV_START_SEC_VAR_INIT_UNSPECIFIED
#include "SUPSRV_MemMap.h"

/* SUPSRV_enuRequest is a multicore variable                                  */
/* written by core 1 and read by core 2 => shall be mapped in non cached area */
uint8 SUPSRV_enuRequest = SUPSRV_NO_ACTION;

#define SUPSRV_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "SUPSRV_MemMap.h"


/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

#define SUPSRV_START_SEC_CODE
#include "SUPSRV_MemMap.h"

/******************************************************************************/
/* !FuncName    : SUPSRV_udtReadTlf35584Version                               */
/* !Description : This API is used to get the TLF35584 Version of the loader. */
/*                                                                            */
/* !LastAuthor  : F. Tremel                                                   */
/******************************************************************************/

Std_ReturnType SUPSRV_udtReadFblTlf35584Version
(
   uint16 *u16Tlf35584Version  /* !Comment : pointer for the output      */
)
{
   Std_ReturnType udtLocalStatus;
//
//
//   if (FBL_INTF_bCheckExchangeAreaAddress() == TRUE)
//   {
//      *u16Tlf35584Version = FBL_INTF_u16Tlf35584Version;
//      udtLocalStatus      = E_OK;
//   }
//   else
//   {
//      udtLocalStatus = E_NOT_OK;
//      SWFAIL_vidSoftwareErrorHook();
//   }
   return(udtLocalStatus);
}

/******************************************************************************/
/* !FuncName    : SUPSRV_vidMainfunction                                      */
/* !Description : Main function of the SUPSRV component                       */
/*                                                                            */
/* !LastAuthor  : J. Soufflet                                                 */
/******************************************************************************/
void SUPSRV_vidMainfunction(void)
{
   switch (SUPSRV_enuRequest)
   {
      case SUPSRV_NO_ACTION:
         break;

//      case SUPSRV_ENTER_REPROG_MODE:
//         if (SAFEWDGM_udtDisableTlfGetStatus() == E_OK)
//       {
//          SAFEMECH_Mpu_vidDisableMPU();
//
//          SUPSRV_vidJumpToLoader();
//
//          /* !Comment: No return from this function. On error, performs a reset      */
//          RSTSRV_vidPerformReset(RSTSRV_udtHARDWARE_RESET);
//       }
//       break;
//
//    case SUPSRV_PROD_TEST:
//       if (SAFEWDGM_udtDisableTlfGetStatus() == E_OK)
//       {
//          SAFEMECH_Mpu_vidDisableMPU();
//
//          STARTUP_vidReqAllRamClearAtInit();
//          CallTprodStart(0);
//
//          /* !Comment: No return from this function. On error, performs a reset      */
//          RSTSRV_vidPerformReset(RSTSRV_udtHARDWARE_RESET);
//       }
//       break;
//       
      default:
         SUPSRV_enuRequest = SUPSRV_NO_ACTION;
         SWFAIL_vidSoftwareErrorHook();
         break;
   }
}

/******************************************************************************/
/* !FuncName    : SUPSRV_vidEnterReprogMode                                   */
/* !Description : This API is used to jump to loader to enter in reprog mode  */
/*                                                                            */
/* !LastAuthor  : F. Tremel                                                   */
/******************************************************************************/
void SUPSRV_vidEnterReprogMode(uint16 u16MicroControllerTemp)
{
//   COMPILER_UNUSED_PARAMETER(u16MicroControllerTemp);
//   SUPSRV_enuRequest = SUPSRV_ENTER_REPROG_MODE;
//   SAFEWDGM_vidDisableTlfRequest();
}

/******************************************************************************/
/* !FuncName    : SUPSRV_vidJumpToLoader                                      */
/* !Description : This API is used to jump to loader                          */
/*                                                                            */
/* !LastAuthor  : J. Soufflet                                                 */
/******************************************************************************/
void SUPSRV_vidJumpToLoader(void)
{
   tFblPermanentReset* fblPermanentResetPtr;
   tFblStrtFctPermanentReset fblStartFct;  
   
   STARTUP_vidReqAllRamClearAtInit();

   fblPermanentResetPtr = (tFblPermanentReset*) FBL_PERMANENT_RESET_PTR_ADDR;

   if ((vuint32)fblPermanentResetPtr->FblStartFct == (vuint32)~(fblPermanentResetPtr->kFblStartFctAddrInv))
   {
      fblStartFct = fblPermanentResetPtr->FblStartFct;
      fblStartFct();
   }
}

/******************************************************************************/
/* !FuncName    : SUPSRV_udtJumpToProdTest                                    */
/* !Description : This API is used to jump into Tprod                         */
/*                                                                            */
/* !LastAuthor  : A. Ibrahim                                                  */
/******************************************************************************/
Std_ReturnType SUPSRV_udtJumpToProdTest
(
   uint8 u8TprodParameter    /* !Comment: Third Parameter, Specific for Test  */
)
{
//   COMPILER_UNUSED_PARAMETER(u8TprodParameter);
//   SUPSRV_enuRequest = SUPSRV_PROD_TEST;
//   SAFEWDGM_vidDisableTlfRequest();
   return(E_OK);
}


#define SUPSRV_STOP_SEC_CODE
#include "SUPSRV_MemMap.h"


/*-------------------------------- end of file -------------------------------*/
