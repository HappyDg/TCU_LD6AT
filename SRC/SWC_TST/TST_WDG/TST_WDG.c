/******************************************************************************/
/* !Layer           : APPLI                                                   */
/* !Component       : TST_WDG                                                 */
/* !Description     : Demo Software to Test WDG APIs                          */
/*                                                                            */
/* !File            : TST_WDG.c                                               */
/* !Description     : Demo Software to Test WDG APIs                          */
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
#include "Wdg_17_Scu.h"

#include "TST_WDG.h"

#define TST_START_SEC_TST_VAR
#include "TST_MemMap.h"

boolean TST_WDG_bDisableWdgCore0;
boolean TST_WDG_bDisableWdgCore1;

#define TST_STOP_SEC_TST_VAR
#include "TST_MemMap.h"

#define TST_START_SEC_TST_CODE
#include "TST_MemMap.h"

/******************************************************************************/
/* !FuncName    : TST_WDG_vidInit                                             */
/* !Description : Initialization of TST_WDG variables                         */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_WDG_vidInit(void)
{
   TST_WDG_bDisableWdgCore0 = FALSE;
   TST_WDG_bDisableWdgCore1 = 0;
}

/******************************************************************************/
/* !FuncName    : TST_WDG_vidRefreshWdgCore0Tst                               */
/* !Description : Stop Refresh of the WDG0 if enable                          */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_WDG_vidRefreshWdgCore0Tst(void)
{
   if (TST_WDG_bDisableWdgCore0 != FALSE)
   {
      while(1);
   }
}

/******************************************************************************/
/* !FuncName    : TST_WDG_vidRefreshWdgCore1Tst                               */
/* !Description : Stop Refresh of the WDG1 if enable                          */
/*                                                                            */
/* !LastAuthor  : L. Baglin                                                   */
/******************************************************************************/
void TST_WDG_vidRefreshWdgCore1Tst(void)
{
   if (TST_WDG_bDisableWdgCore1 != FALSE)
   {
	  while(1);
   }
}

#define TST_STOP_SEC_TST_CODE
#include "TST_MemMap.h"

/*------------------------------ end of file ---------------------------------*/

