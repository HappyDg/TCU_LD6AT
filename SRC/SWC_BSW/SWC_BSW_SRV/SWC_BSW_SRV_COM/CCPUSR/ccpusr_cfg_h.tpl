/*INSERTION_TRADOIL*/
/******************************************************************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCPUSR_CFG_H                                            */
/* !Description     : Template of CCP Configuration header file (user part)   */
/*                                                                            */
/* !File            : CCPUSR_CFG_H.TPL                                        */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : Genecode Tool                                           */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : OIL                                                     */
/*                                                                            */
/* COPYRIGHT 2009 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::                                                                $*/
/* $Revision::                                                               $*/
/* $Author::                                          $$Date::               $*/
/******************************************************************************/
'/***************************** <AUTO_FILE_HEADER> *****************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCPUSR_CFG                                              */
/* !Description     : Configuration of the user part                          */
/*                                                                            */
/* !File            : CCPUSR_CFG.H                                            */
/*                                                                            */
/* !Scope           : Public                                                  */
/*                                                                            */
/* !Target          : All                                                     */
/*                                                                            */
/* !Vendor          : Valeo                                                   */
/*                                                                            */
/* Coding language  : C                                                       */
/*                                                                            */
/* COPYRIGHT 2009 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/**************************** </AUTO_FILE_HEADER> *****************************/
/* PVCS Information                                                           */
/* $Arc`'hive::                                                                $*/
/* $Rev`'ision::                                                               $*/
/* $Aut`'hor::                                          $$Da`'te::               $*/
/******************************************************************************/
/* Generated on `Date()' by Genecode `Version()'                       */
/******************************************************************************/

#ifndef CCPUSR_CFG_H
#define CCPUSR_CFG_H

#include "CCP_Typ.h"
#include "CCP_Cfg.h"
#include "ComStack_Types.h"
#include "CanIf.h"
#include "CCPUSR_CanIf_Cfg.h"

`
CCP CONCATE
{
   INCLUDE_FILES AS incFile ONEPERLINE
   {
      '#include "` incFile '"`
   }
}
'
/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
#define CCPUSR_CANIF_DTO_TX_ID        `CCP{CANIF_DTO_TX_ID}'
#define CCPUSR_CANIF_DEVAID_DTO_TX_ID `CCP{CANIF_DEVAID_DTO_TX_ID}'
`
CCP WHERE (CAL_PAGE_SERVICES = TRUE) ONEPERLINE
{
   "#define CCPUSR_DFLT_CALIB_PAGE_ADDR 0x" hex(DFLT_CALIB_PAGE_ADDR) "
"  "#define CCPUSR_DFLT_CALIB_PAGE_EXTN " DFLT_CALIB_PAGE_EXTN
}
'

#define CCPUSR_NB_WRITABLE_ZONE ` CCP_WRITABLE_MEMORY_ZONE COUNT '
#define CCPUSR_NB_READ_ONLY_ZONE ` CCP_READ_ONLY_MEMORY_ZONE COUNT '


/* Calibration areas infos */
#define CCPUSR_START_ADDRESS_OF_CALIBRATION_IN_ROM ` CCP_CALIBRATION_MAPPING{ADDRESS_START_IN_ROM} '
#define CCPUSR_START_ADDRESS_OF_CALIBRATION_IN_RAM ` CCP_CALIBRATION_MAPPING{ADDRESS_START_IN_RAM} '
#define CCPUSR_CALIBRATION_SIZE                    ` CCP_CALIBRATION_MAPPING{CALIBRATION_SIZE} '

/* Tx Confirmation function for DAQ lists */
`
CCP WHERE (DAQ_LIST_SERVICES == TRUE) ONEPERLINE
{
   .DAQ_LIST ORDERBY(FileOrder()) CONCATE
   {
      '#define ` CANIF_TX_CONF_FCT ' CCPUSR_vidDaqListTxConf
`     '#define ` CANIF_DEVAID_TX_CONF_FCT ' CCPUSR_vidDaqListTxConf
`
   }
}
'

/* Tx Confirmation ID for DAQ lists = to daq list number */
`
CCP WHERE (DAQ_LIST_SERVICES == TRUE) ONEPERLINE
{
   .DAQ_LIST ORDERBY(FileOrder()) CONCATE
   {
      '#define ` CANIF_TX_CONF_ID " " counter()'
`     '#define ` CANIF_DEVAID_TX_CONF_ID " " CANIF_TX_CONF_ID'
`
   }
}
'

/******************************************************************************/
/* CONSTANTS DECLARATION                                                      */
/******************************************************************************/
#define CCP_START_SEC_CONST_UNSPECIFIED
#include "Ccp_MemMap.h"

/* !Comment: CAN ID for all DAQ lists                                         */
extern CONST(PduIdType, CCP_CONST) CCPUSR_kaudtDaqMsgID[CCP_u8DAQ_NO_LISTS];
extern CONST(PduIdType, CCP_CONST) CCPUSR_kaudtDevaidDaqMsgID[CCP_u8DAQ_NO_LISTS];

#define CCP_STOP_SEC_CONST_UNSPECIFIED
#include "Ccp_MemMap.h"


#endif /* CCPUSR_CFG_H */

/*-------------------------------- end of file -------------------------------*/