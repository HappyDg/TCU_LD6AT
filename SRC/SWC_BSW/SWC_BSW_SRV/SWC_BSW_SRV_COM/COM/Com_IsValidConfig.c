/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */


/*==================[inclusions]=============================================*/

#include <Com_Trace.h>
#include <TSAutosar.h>          /* EB specific standard types */
#include <ComStack_Types.h>     /* AUTOSAR standard types */
#include <Com_Api_Static.h>     /* module public static API */
#include <Com_Priv.h>           /* public intra module API */
#include <TSPBConfig_Signature.h> /* TS_PlatformSigIsValid */

/*==================[macros]=================================================*/

/*==================[type definitions]=======================================*/

/*==================[external function declarations]=========================*/

#if (COM_ISVALIDCONFIG_MMAP_ENABLED == STD_ON)
#define COM_START_SEC_CODE_CC_BLOCK
#include <MemMap.h>
#else
#define COM_START_SEC_CODE
#include <MemMap.h>
#endif

FUNC(Std_ReturnType, COM_CODE) Com_IsValidConfig
(
   P2CONST(void, AUTOMATIC,COM_APPL_CONST) ConfigPtr
)
{
   Std_ReturnType retval = E_NOT_OK;

   DBG_COM_ISVALIDCONFIG_ENTRY(ConfigPtr);

   /* check for NULL_PTR */
   if (NULL_PTR != ConfigPtr)
   {
      CONSTP2CONST(Com_ConfigType, AUTOMATIC, COM_APPL_CONST) TmpCfgPtr =
         (P2CONST(Com_ConfigType, AUTOMATIC, COM_APPL_CONST)) ConfigPtr;

      /* check platform signature */
      if (TRUE == TS_PlatformSigIsValid(TmpCfgPtr->ComPlatformSignature))
      {
         /* check pre-compile time signature */
         if (COM_CFG_SIGNATURE == TmpCfgPtr->ComCfgSignature)
         {
            /* check link-time signature */
            if (Com_LcfgSignature == TmpCfgPtr->ComLcfgSignature)
            {
               /* check published information signature */
               if (COM_PUBLIC_INFO_SIGNATURE == TmpCfgPtr->ComPublicInfoSignature)
               {
                  /* Indicate that the configuration is valid */
                  retval = E_OK;
               }
            }
         }
      }
   }


   DBG_COM_ISVALIDCONFIG_EXIT(retval,ConfigPtr);
   return retval;
}                               /* Com_IsValidConfig */

#if (COM_ISVALIDCONFIG_MMAP_ENABLED == STD_ON)
#define COM_STOP_SEC_CODE_CC_BLOCK
#include <MemMap.h>
#else
#define COM_STOP_SEC_CODE
#include <MemMap.h>
#endif

/*==================[internal function declarations]=========================*/

/*==================[external constants]=====================================*/

/*==================[internal constants]=====================================*/

/*==================[external data]==========================================*/

/*==================[internal data]==========================================*/

/*==================[external function definitions]==========================*/

/*==================[internal function definitions]==========================*/

/*==================[end of file]============================================*/

