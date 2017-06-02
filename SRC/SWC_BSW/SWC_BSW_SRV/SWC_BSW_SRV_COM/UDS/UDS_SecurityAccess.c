/******************************************************************************/
/*                                                                            */
/* !Layer           : SRV                                                     */
/*                                                                            */
/* !Component       : UDS                                                     */
/* !Description     :                                                         */
/*                                                                            */
/* !File            : UDS_SecurityAccess.c                                    */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2011 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive:                                                                 $*/
/* $Revision::            $$Author::                  $$Date::               $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/******************************************************************************/

#include "Std_Types.h"
#include "Dcm_Types.h" 
#include "IfxStm_regdef.h"
#include "UDS.h"

/******************************************************************************/
/* LOCAL FUNCTION DECLERATION                                                 */
/******************************************************************************/
/******************************************************************************/
#define UDS_START_SEC_CODE
#include "memmap.h"

static uint32 UDS_u32CalcKeyValue(void);

#define UDS_STOP_SEC_CODE
#include "memmap.h"

/******************************************************************************/
/* LOCAL VARIABLES DEFINITION                                                 */
/******************************************************************************/
#define UDS_START_SEC_VAR_UNSPECIFIED
#include "memmap.h"

static uint32 UDS_u32SaSeed = 0;
static const uint32 UDS_ku32LocLevel01 = 0xB356A523;

#define UDS_STOP_SEC_VAR_UNSPECIFIED
#include "memmap.h"

/******************************************************************************/
/* LOCAL FUNCTION DEFINITION                                                  */
/******************************************************************************/
/******************************************************************************/
/*                             BEGIN MAP IN REPROG RAM                        */
/******************************************************************************/
#define UDS_START_SEC_CODE
#include "memmap.h"

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_u32GenerateSeed                                         */
/* !Description : Get a random value for seed generation.                     */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
static uint32 UDS_u32GenerateSeed(void)
{
   uint32 u32LocalSeedValue;
   
   u32LocalSeedValue = STM0_TIM0.U;
   u32LocalSeedValue ^= UDS_ku32LocLevel01;
   u32LocalSeedValue = ( u32LocalSeedValue << 7 ) | ( u32LocalSeedValue >> 24 );
   
   return u32LocalSeedValue;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_u32CalcKeyValue                                         */
/* !Description : Calculation of key based on seed previously generated       */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
static uint32 UDS_u32CalcKeyValue(void)
{
   uint32  u32LocalKeyValue;

   u32LocalKeyValue = ( UDS_u32SaSeed >> 9 ) | ( UDS_u32SaSeed  <<  22 );
   u32LocalKeyValue = (uint32)(u32LocalKeyValue + u32LocalKeyValue + u32LocalKeyValue);
   
   u32LocalKeyValue = u32LocalKeyValue ^ UDS_ku32LocLevel01;

   u32LocalKeyValue = ( u32LocalKeyValue << 14 ) | ( u32LocalKeyValue >> 17 );

   return (u32LocalKeyValue);
}

/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bRequestSeed                                            */
/* !Description : Request a seed                                              */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bRequestSeed(uint8 *Data, Dcm_NegativeResponseCodeType *ErrorCode)
{  
   /* Generate seed */
   UDS_u32SaSeed = UDS_u32GenerateSeed();
  
   /* Write seed in transmission buffer */
   *Data = (uint8)((UDS_u32SaSeed & 0xFF000000) >> 24);
   Data++;
   *Data = (uint8)((UDS_u32SaSeed & 0x00FF0000) >> 16);
   Data++;
   *Data = (uint8)((UDS_u32SaSeed & 0x0000FF00) >> 8 );
   Data++;
   *Data = (uint8) (UDS_u32SaSeed & 0x000000FF);
   Data++;
   
   *ErrorCode = DCM_E_OK;
   
   return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !FuncName    : UDS_bRequestSeed                                            */
/* !Description : Compare key to authorize or not the unlocking               */
/* !Number      : 0                                                           */
/* !Reference   : NONE                                                        */
/*                                                                            */
/******************************************************************************/
/* !LastAuthor  : M Bras-Rabiller                                             */
/******************************************************************************/
Std_ReturnType UDS_bSendKey(uint8 *reqData)
{
   uint32 u32LocalReceivedKey;
   uint32 u32LocalKey;
   Std_ReturnType bLocalReturnVal;

   u32LocalReceivedKey =
     ((((uint32)reqData[0]) << 24) & 0xFF000000UL)
   + ((((uint32)reqData[1]) << 16) & 0x00FF0000UL)
   + ((((uint32)reqData[2]) <<  8) & 0x0000FF00UL)
   + ((((uint32)reqData[3])      ) & 0x000000FFUL);

   /* Calculate key locally and compare it to received key.    */
   u32LocalKey = UDS_u32CalcKeyValue();

   if ((u32LocalKey == u32LocalReceivedKey) || 
       (UDS_SecurAccessBenchOnC != 0))
   {
      bLocalReturnVal = E_OK;
   }
   else
   {
      bLocalReturnVal = E_NOT_OK;
   }
   
   return bLocalReturnVal;
}

#define UDS_STOP_SEC_CODE
#include "memmap.h"

/*-------------------------------- end of file -------------------------------*/
