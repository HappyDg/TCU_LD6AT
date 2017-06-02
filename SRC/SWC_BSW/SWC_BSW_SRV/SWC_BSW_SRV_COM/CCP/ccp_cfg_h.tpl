/*INSERTION_TRADOIL*/
/******************************************************************************/
/*                                                                            */
/* !Layer           : SRVL                                                    */
/*                                                                            */
/* !Component       : CCP                                                     */
/*                                                                            */
/* !Module          : CCP_CFG_H                                               */
/* !Description     : Template of CCP Configuration header file               */
/*                                                                            */
/* !File            : CCP_CFG_H.TPL                                           */
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
/* !Module          : CCP_CFG                                                 */
/* !Description     : Configuration of the Component                          */
/*                                                                            */
/* !File            : CCP_CFG.h                                               */
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

#ifndef CCP_CFG_H
#define CCP_CFG_H

#include "CCP_Typ.h"

/******************************************************************************/
/* DEFINES                                                                    */
/******************************************************************************/
/* !MComment: optional services activation                                    */
`
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_DAQ_LIST "
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_SEED_KEY "
   WHERE (PROTECTION_SERVICES == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (PROTECTION_SERVICES == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_TEST     "
   WHERE (TEST_SERVICE == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (TEST_SERVICE == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_DNLD6    "
   WHERE (DOWNLOAD6_SERVICE == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (DOWNLOAD6_SERVICE == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_SHO_UPLD "
   WHERE (SHORT_UPLOAD_SERVICE == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (SHORT_UPLOAD_SERVICE == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_SSN_STS  "
   WHERE (SESSION_STATUS_SERVICES == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (SESSION_STATUS_SERVICES == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_CAL_PAGE "
   WHERE (CAL_PAGE_SERVICES == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (CAL_PAGE_SERVICES == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_CKS      "
   WHERE (CHECKSUM_SERVICE == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (CHECKSUM_SERVICE == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_MOVE     "
   WHERE (MOVE_SERVICE == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (MOVE_SERVICE == FALSE)
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_PROG     "
   WHERE (PROGRAM_SERVICES == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (PROGRAM_SERVICES == FALSE)
   {
      "CCP_coDEACVD"
   }
}
'
/* !MComment: asynchronous response activation                                */
`
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_CKS_ASYNC_RESP  "
   WHERE (   (CHECKSUM_SERVICE == TRUE)
         and (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{CHECKSUM_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (CHECKSUM_SERVICE == FALSE)
         or (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{CHECKSUM_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_MOVE_ASYNC_RESP "
   WHERE (   (MOVE_SERVICE == TRUE)
         and (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{MOVE_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (MOVE_SERVICE == FALSE)
         or (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{MOVE_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coSRV_DNLD_ASYNC_RESP "
   WHERE (   (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{DOWNLOAD_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{DOWNLOAD_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_DNLD6_ASYNC_RESP "
   WHERE (   (DOWNLOAD6_SERVICE == TRUE)
         and (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{DOWNLOAD6_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (DOWNLOAD6_SERVICE == FALSE)
         or (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{DOWNLOAD6_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coSRV_UPLD_ASYNC_RESP "
   WHERE (   (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{UPLOAD_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{UPLOAD_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_SHO_UPLD_ASYNC_RESP "
   WHERE (   (SHORT_UPLOAD_SERVICE == TRUE)
         and (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{SHORT_UPLOAD_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (SHORT_UPLOAD_SERVICE == FALSE)
         or (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{SHORT_UPLOAD_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_PROG_ASYNC_RESP "
   WHERE (   (PROGRAM_SERVICES == TRUE)
         and (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{PROGRAM_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (PROGRAM_SERVICES == FALSE)
         or (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{PROGRAM_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coOPT_SRV_CLR_MEM_ASYNC_RESP "
   WHERE (   (PROGRAM_SERVICES == TRUE)
         and (ASYNCHRONOUS_RESPONSE == TRUE)
         and (ASYNCHRONOUS_RESPONSE{CLEAR_MEMORY_SERVICE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (PROGRAM_SERVICES == FALSE)
         or (ASYNCHRONOUS_RESPONSE == FALSE)
         or (ASYNCHRONOUS_RESPONSE{CLEAR_MEMORY_SERVICE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coASYNC_RESP "
   WHERE (ASYNCHRONOUS_RESPONSE == TRUE)
   {
      "CCP_coACVD"
   }
   WHERE (ASYNCHRONOUS_RESPONSE == FALSE)
   {
      "CCP_coDEACVD"
   }
}
'
/* !MComment: features activation                                             */
`
CCP ONEPERLINE
{
   "#define CCP_coCAL_STORE_FEATURE "
   WHERE (   (SESSION_STATUS_SERVICES == TRUE)
         and (SESSION_STATUS_SERVICES{CAL_STORE_FEATURE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (SESSION_STATUS_SERVICES == FALSE)
         or (SESSION_STATUS_SERVICES{CAL_STORE_FEATURE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coDAQ_RESU_FEATURE  "
   WHERE (   (SESSION_STATUS_SERVICES == TRUE)
         and (SESSION_STATUS_SERVICES{DAQ_RESUME_FEATURE} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (SESSION_STATUS_SERVICES == FALSE)
         or (SESSION_STATUS_SERVICES{DAQ_RESUME_FEATURE} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
'
/* !Comment: additional status information requested                          */
`
CCP ONEPERLINE
{
   "#define CCP_coADDL_STS "
   WHERE (   (SESSION_STATUS_SERVICES == TRUE)
         and (SESSION_STATUS_SERVICES{ADDITIONAL_STATUS} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (SESSION_STATUS_SERVICES == FALSE)
         or (SESSION_STATUS_SERVICES{ADDITIONAL_STATUS} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
'
/* !MComment: station address                                                 */
`
CCP ONEPERLINE
{
   "#define CCP_u8STN_ADR_MSB 0x0"
   WHERE (STATION_ADDRESS_CHECK == "INTERNAL")
   {
      hex(STATION_ADDRESS_CHECK{STATION_ADDRESS} / 256)
   }
   WHERE (STATION_ADDRESS_CHECK == "EXTERNAL")
   {
      "00"
   }
}
CCP ONEPERLINE
{
   "#define CCP_u8STN_ADR_LSB 0x0"
   WHERE (STATION_ADDRESS_CHECK == "INTERNAL")
   {
      hex(STATION_ADDRESS_CHECK{STATION_ADDRESS} % 256)
   }
   WHERE (STATION_ADDRESS_CHECK == "EXTERNAL")
   {
      "00"
   }
}
CCP ONEPERLINE
{
   "#define CCP_coSLAVE_STN_ADR_USR "
   WHERE (STATION_ADDRESS_CHECK == "INTERNAL")
   {
      "CCP_coDEACVD"
   }
   WHERE (STATION_ADDRESS_CHECK == "EXTERNAL")
   {
      "CCP_coACVD"
   }
}
'
/* !MComment: device identifier                                               */
#define CCP_u8SLAVE_DEV_ID_TYPE `CCP{DEVICE_ID_DATA_TYPE}'
`
CCP ONEPERLINE
{
   WHERE (  (DEVICE_ID == "INTERNAL_UINT8")
         or (DEVICE_ID == "INTERNAL_UINT16")
         or (DEVICE_ID == "INTERNAL_UINT32")
         or (DEVICE_ID == "INTERNAL_ARRAY_UINT8")
         or (DEVICE_ID == "INTERNAL_STRING"))
   {
      '#define CCP_coSLAVE_DEV_ID_USR  CCP_coDEACVD
`     '#define CCP_u8SLAVE_DEV_ID_LEN  ((uint8)sizeof(CCP_kaudtDevId))
`     '#define CCP_u32SLAVE_DEV_ID_ADR ((uint32)(&CCP_kaudtDevId[0]))
`     '#define CCP_u8SLAVE_DEV_ID_EXTN 0`
   }
   WHERE (DEVICE_ID == "EXTERNAL")
   {
      "#define CCP_coSLAVE_DEV_ID_CBK  CCP_coACVD"
   }
}
'
/* !Comment: resources availability                                           */
#define CCP_u8RES_CFG \
`
CCP ONEPERLINE
{
   "   (CCP_u8CAL_AVL | "
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      "CCP_u8DAQ_AVL"
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "CCP_u8DAQ_UNAVL"
   }
   " | "
   WHERE (PROGRAM_SERVICES == TRUE)
   {
      "CCP_u8PGM_AVL"
   }
   WHERE (PROGRAM_SERVICES == FALSE)
   {
      "CCP_u8PGM_UNAVL"
   }
   ")"
}
'
/* !Comment: resources protection                                             */
#define CCP_u8PROTN_CFG \
`
CCP ONEPERLINE
{
   "   ("
   WHERE (   (PROTECTION_SERVICES == TRUE)
         and (PROTECTION_SERVICES{LOCKED_CALIB} == TRUE))
   {
      "CCP_u8CAL_PROTD"
   }
   WHERE (  (PROTECTION_SERVICES == FALSE)
         or (PROTECTION_SERVICES{LOCKED_CALIB} == FALSE))
   {
      "CCP_u8CAL_UNPROTD"
   }
   " | "
   WHERE (   (PROTECTION_SERVICES == TRUE)
         and (PROTECTION_SERVICES{LOCKED_DAQ_LIST} == TRUE))
   {
      "CCP_u8DAQ_PROTD"
   }
   WHERE (  (PROTECTION_SERVICES == FALSE)
         or (PROTECTION_SERVICES{LOCKED_DAQ_LIST} == FALSE))
   {
      "CCP_u8DAQ_UNPROTD"
   }
   " | "
   WHERE (   (PROTECTION_SERVICES == TRUE)
         and (PROTECTION_SERVICES{LOCKED_PROGRAM} == TRUE))
   {
      "CCP_u8PGM_PROTD"
   }
   WHERE (  (PROTECTION_SERVICES == FALSE)
         or (PROTECTION_SERVICES{LOCKED_PROGRAM} == FALSE))
   {
      "CCP_u8PGM_UNPROTD"
   }
   ")"
}
'
/* !Comment: check of DAQ list initialization status                          */
`
CCP ONEPERLINE
{
   "#define CCP_coDAQ_ININ_STS_CHK "
   WHERE (   (DAQ_LIST_SERVICES == TRUE)
         and (DAQ_LIST_SERVICES{CHECK_DAQ_INITIALISATION_STATUS} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (DAQ_LIST_SERVICES == FALSE)
         or (DAQ_LIST_SERVICES{CHECK_DAQ_INITIALISATION_STATUS} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
'
/* !Comment: manage DAQ list dynamic CAN identifier                           */
`
CCP ONEPERLINE
{
   "#define CCP_coDAQ_DYN_CAN_ID "
   WHERE (   (DAQ_LIST_SERVICES == TRUE)
         and (DAQ_LIST_SERVICES{DAQ_DYNAMIC_CAN_ID} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (DAQ_LIST_SERVICES == FALSE)
         or (DAQ_LIST_SERVICES{DAQ_DYNAMIC_CAN_ID} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
'
/* !Comment: manage DAQ list extended CAN identifier                          */
`
CCP ONEPERLINE
{
   "#define CCP_coDAQ_MNG_EXTD_CAN_ID "
   WHERE (   (DAQ_LIST_SERVICES == TRUE)
         and (DAQ_LIST_SERVICES{DAQ_DYNAMIC_CAN_ID} == TRUE))
   {
      WHERE (DAQ_LIST_SERVICES{DAQ_DYNAMIC_CAN_ID{DAQ_MANAGE_EXTENDED_CAN_ID}} == TRUE)
      {
         "CCP_coACVD"
      }
      WHERE (DAQ_LIST_SERVICES{DAQ_DYNAMIC_CAN_ID{DAQ_MANAGE_EXTENDED_CAN_ID}} == FALSE)
      {
         "CCP_coDEACVD"
      }
   }
   WHERE (  (DAQ_LIST_SERVICES == FALSE)
         or (DAQ_LIST_SERVICES{DAQ_DYNAMIC_CAN_ID} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
'
/* !Comment: select 1 DAQ list per Event/1 Event per DAQ list                 */
`
CCP ONEPERLINE
{
   "#define CCP_coDAQ_LIST_ID_EQ_EVT_ID "
   WHERE (   (DAQ_LIST_SERVICES == TRUE)
         and (DAQ_LIST_SERVICES{LIST_ID_EQ_EVENT_ID} == TRUE))
   {
      "CCP_coACVD"
   }
   WHERE (  (DAQ_LIST_SERVICES == FALSE)
         or (DAQ_LIST_SERVICES{LIST_ID_EQ_EVENT_ID} == FALSE))
   {
      "CCP_coDEACVD"
   }
}
'
#define CCP_u8DAQ_NO_EVE_CHNS ` DAQ_EVENT COUNT '

/* !Comment: List of DAQ list                                                 */
`
DAQ_LIST AS daqLst ONEPERLINE
{
   "#define CCP_u8DAQ_LST_" daqLst " " counter()
}
'
/* !Comment: List of DAQ list events                                          */
`
DAQ_EVENT AS daqEvt ONEPERLINE
{
   "#define CCP_u8DAQ_EVT_" daqEvt " " counter()
}
'
#define CCP_u8DAQ_NO_LISTS ` DAQ_LIST COUNT '

#define CCP_u16DAQ_NO_ELMS ` DAQ_LIST SUM {NUMBER_OF_ODT * 7} '

/* !Comment: maximum size of ODT elements                                     */
`
CCP ONEPERLINE
{
   "#define CCP_coDAQ_ELM_SIZE_MAX "
   WHERE (DAQ_LIST_SERVICES == TRUE)
   {
      WHERE (DAQ_LIST_SERVICES{MAX_DATA_SIZE} == "U8")
      {
         "CCP_coDAQ_ELM_SIZE_MAX_8_BITS"
      }
      WHERE (DAQ_LIST_SERVICES{MAX_DATA_SIZE} == "U16")
      {
         "CCP_coDAQ_ELM_SIZE_MAX_16_BITS"
      }
      WHERE (DAQ_LIST_SERVICES{MAX_DATA_SIZE} == "U32")
      {
         "CCP_coDAQ_ELM_SIZE_MAX_32_BITS"
      }
   }
   WHERE (DAQ_LIST_SERVICES == FALSE)
   {
      "CCP_coDAQ_ELM_SIZE_MAX_8_BITS"
   }
}
'
/* !Comment: data acquisition method (whole list or per ODT)                  */
`
CCP ONEPERLINE
{
   "#define CCP_coDAQ_FILL_WHOLE_LIST "
   WHERE (   (DAQ_LIST_SERVICES == TRUE)
         and (DAQ_LIST_FILLING_MODE == "WHOLE_DAQ_LIST"))
   {
      "CCP_coACVD"
   }
   WHERE (  (DAQ_LIST_SERVICES == FALSE)
         or (DAQ_LIST_FILLING_MODE != "WHOLE_DAQ_LIST"))
   {
      "CCP_coDEACVD"
   }
}
'

/******************************************************************************/
/* CONSTANTS DECLARATION                                                      */
/******************************************************************************/
#define CCP_START_SEC_CONST_UNSPECIFIED
#include "CCP_MemMap.h"

/* !Comment: device identifier                                                */
`
CCP ONEPERLINE
{
   WHERE (DEVICE_ID == "INTERNAL_UINT8")
   {
      "extern CONST(uint8, CCP_CONST) CCP_kaudtDevId[1];"
   }
   WHERE (DEVICE_ID == "INTERNAL_UINT16")
   {
      "extern CONST(uint16, CCP_CONST) CCP_kaudtDevId[1];"
   }
   WHERE (DEVICE_ID == "INTERNAL_UINT32")
   {
      "extern CONST(uint32, CCP_CONST) CCP_kaudtDevId[1];"
   }
   WHERE (DEVICE_ID == "INTERNAL_ARRAY_UINT8")
   {
      "extern CONST(uint8, CCP_CONST) CCP_kaudtDevId[" DEVICE_ID{VALUE COUNT} "];"
   }
   WHERE (DEVICE_ID == "INTERNAL_STRING")
   {
      "extern CONST(uint8, CCP_CONST) CCP_kaudtDevId[sizeof("'"` DEVICE_ID{VALUE} '"`")];"
   }
}
'
#define CCP_STOP_SEC_CONST_UNSPECIFIED
#include "CCP_MemMap.h"


#endif /* CCP_CFG_H */

/*-------------------------------- end of file -------------------------------*/