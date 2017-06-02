/******************************************************************************/
/*                                                                            */
/* !Layer          : Layer                                                    */
/*                                                                            */
/* !Component      : Component                                                */
/* !Description    : Component description                                    */
/*                                                                            */
/* !Module         : MODULE                                                   */
/* !Description    : MODULE description                                       */
/*                                                                            */
/* !File           : MAIN_DemCbk.C                                               */
/*                                                                            */
/* !Scope          : Public                                                   */
/*                                                                            */
/* !Target         : Infineon_tc27                                            */
/*                                                                            */
/* !Vendor         : VALEO                                                    */
/*                                                                            */
/* !Author         : A. Abohassan                                             */
/*                                                                            */
/* Coding language : C                                                        */
/*                                                                            */
/* COPYRIGHT 2006 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   $*/
/* $Revision::  $*/
/******************************************************************************/
/* !VnrOff :                                                                  */
/******************************************************************************/
/******************************************************************************/

#include "MAIN_DemCbk.H"



/******************************************************************************/
/* GLOBAL FUNCTION DEFINITION                                                 */
/******************************************************************************/

#define MAIN_START_SEC_CODE
#include "MAIN_MemMap.h"


/******************************************************************************/
/*                                                                            */
/* !Function    : MAIN_DemDidElementReadApmElecValU14                           */
/* !Description :                                                     */
/* !Number      :                                                  */
/* !Reference   : NONE                                                        */
/* !LastAuthor  : A. Abohassan                                                */
/*                                                                            */
/******************************************************************************/
Std_ReturnType MAIN_DemDidElementReadApmElecValU14( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data)
{
   uint16 u16LocalValue; 
   
   //u16LocalValue = (uint16)DCDCAPI_u8ReadRaw_ApmElecValU14();
   *Data = (uint8)((u16LocalValue & 0xFF00) >> 8);
   Data++;
   *Data = (uint8)(u16LocalValue & 0x00FF);
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !Function    : MAIN_DemDidElementReadApmElecValI14                           */
/* !Description :                                                     */
/* !Number      :                                                  */
/* !Reference   : NONE                                                        */
/* !LastAuthor  : A. Abohassan                                                */
/*                                                                            */
/******************************************************************************/
Std_ReturnType MAIN_DemDidElementReadApmElecValI14( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data)
{
   uint16 u16LocalValue; 
   
   //u16LocalValue = DCDCAPI_u16ReadRaw_ApmElecValI14();
   *Data = (uint8)((u16LocalValue & 0xFF00) >> 8);
   Data++;
   *Data = (uint8)(u16LocalValue & 0x00FF);
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !Function    : MAIN_DemDidElementReadApmElecValUHV                           */
/* !Description :                                                     */
/* !Number      :                                                  */
/* !Reference   : NONE                                                        */
/* !LastAuthor  : A. Abohassan                                                */
/*                                                                            */
/******************************************************************************/
Std_ReturnType MAIN_DemDidElementReadApmElecValUHV( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data)
{
   uint16 u16LocalValue; 
   
   //u16LocalValue = DCDCAPI_u16ReadRaw_ApmElecValUHV();
   *Data = (uint8)((u16LocalValue & 0xFF00) >> 8);
   Data++;
   *Data = (uint8)(u16LocalValue & 0x00FF);
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !Function    : MAIN_DemDidElementReadApmElecValIHV                           */
/* !Description :                                                     */
/* !Number      :                                                  */
/* !Reference   : NONE                                                        */
/* !LastAuthor  : A. Abohassan                                                */
/*                                                                            */
/******************************************************************************/
Std_ReturnType MAIN_DemDidElementReadApmElecValIHV( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data)
{
   uint16 u16LocalValue; 
   
   //u16LocalValue = DCDCAPI_u16ReadRaw_ApmElecValIHV();
   *Data = (uint8)((u16LocalValue & 0xFF00) >> 8);
   Data++;
   *Data = (uint8)(u16LocalValue & 0x00FF);
    return E_OK;
}

/******************************************************************************/
/*                                                                            */
/* !Function    : MAIN_DemDidElementReadApmElecValTemp                           */
/* !Description :                                                     */
/* !Number      :                                                  */
/* !Reference   : NONE                                                        */
/* !LastAuthor  : A. Abohassan                                                */
/*                                                                            */
/******************************************************************************/
Std_ReturnType MAIN_DemDidElementReadApmElecValTemp( P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data)
{
   uint16 u16LocalValue; 
   
   //u16LocalValue = (uint16)DCDCAPI_u8ReadRaw_ApmElecValTemp();
   *Data = (uint8)((u16LocalValue & 0xFF00) >> 8);
   Data++;
   *Data = (uint8)(u16LocalValue & 0x00FF);
    return E_OK;
}

#define MAIN_STOP_SEC_CODE
#include "MAIN_MemMap.h"


/*-------------------------------- end of file -------------------------------*/
