/**********************************************************************************************************************/
/* !Layer           : APPLI                                                                                           */
/* !Component       : TST_DET                                                                                         */
/* !Description     : Code to be able to test the Det component                                                       */
/*                                                                                                                    */
/* !File            : TST_DET.c                                                                                       */
/* !Description     : Code to be able to test the Det component                                                       */
/*                                                                                                                    */
/* !Reference       :                                                                                                 */
/*                                                                                                                    */
/* !Target          : ALL                                                                                             */
/*                                                                                                                    */
/* Coding language  : C                                                                                               */
/*                                                                                                                    */
/* COPYRIGHT VALEO all rights reserved                                                                                */
/**********************************************************************************************************************/
/* Dimension Informations
 * %PCMS_HEADER_SUBSTITUTION_START:%
 * The PID has this format: <Product ID>:<Item ID>.<Variant>-<Item Type>;<Revision>
 * %PID:%
 * %PCMS_HEADER_SUBSTITUTION_END:%
 **********************************************************************************************************************/

#include "Std_Types.h"
#include "Det.h"
#include "TST_DET.h"

#define TST_START_SEC_TST_VAR
#include "TST_MemMap.h"

uint8 TST_DET_u8ApiId;
uint8 TST_DET_u8ErrorId;
uint8 TST_DET_u8InstanceId;
uint16 TST_DET_u16ModuleId;
uint16 TST_DET_u16NbOfRecordToAdd;

#define TST_STOP_SEC_TST_VAR
#include "TST_MemMap.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

/**********************************************************************************************************************/
/* !FuncName    : TST_DET_vidInit                                                                                     */
/* !Description : TST_DET initialization                                                                              */
/*                                                                                                                    */
/* !LastAuthor  : L. Voilmy                                                                                           */
/**********************************************************************************************************************/
void TST_DET_vidInit(void)
{
   TST_DET_u16NbOfRecordToAdd = 0;
   TST_DET_u16ModuleId        = 0xFF;
   TST_DET_u8InstanceId       = 0x22;
   TST_DET_u8ApiId            = 0x33;
   TST_DET_u8ErrorId          = 0x44;
}

/**********************************************************************************************************************/
/* !FuncName    : TST_DET_vidmainFunction                                                                             */
/* !Description : Add a new Det Record                                                                                */
/*                                                                                                                    */
/* !LastAuthor  : L. Voilmy                                                                                           */
/**********************************************************************************************************************/
void TST_DET_vidMainFunction(void)
{
   if(TST_DET_u16NbOfRecordToAdd != 0)
   {
      //Det_ReportError(TST_DET_u16ModuleId, TST_DET_u8InstanceId, TST_DET_u8ApiId, TST_DET_u8ErrorId);
      TST_DET_u16NbOfRecordToAdd--;
   }
}

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

/*---------------------------------------------------- end of file ---------------------------------------------------*/
