/******************************************************************************/
/*                                                                            */
/* !Layer          : BSW                                                      */
/*                                                                            */
/* !Component      : SRV                                                      */
/*                                                                            */
/* !Module         : SPY                                                      */
/* !Description    : Definitions for the component                            */
/*                                                                            */
/* !File           : SPY_CFG.H                                                */
/*                                                                            */
/* !Target         : Hitachi                                                  */
/*                                                                            */
/* !Vendor         : VEMS                                                     */
/*                                                                            */
/* Coding language : H                                                        */
/*                                                                            */
/* COPYRIGHT 2011 VALEO                                                       */
/* all rights reserved                                                        */
/*                                                                            */
/******************************************************************************/
/* PVCS Information                                                           */
/* $Archive::   P:/VE_Onduleur_Gen1_Michelin/LOG/60_ComponentArchive/Archives$*/
/* $Revision::   1.1      $$Author::   hlaos          $$Date::   17 Jan 2012 $*/
/******************************************************************************/
/* !VnrOff : Names imposed by the customer                                    */
/******************************************************************************/

#ifndef _SPY_CFG_H_
#define _SPY_CFG_H_

#include "Std_Types.h"
#include "CCP_Cfg.h"

/*------------------------------------------------------------------------*/
/* Note: the module SPY is compatible with the CCP V2.1 developped        */
/*       by EMD VALEO team                                                */
/*------------------------------------------------------------------------*/

/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
/*                                                                        */
/*                              DEFINE DECLARATIONS                       */
/*                                                                        */
/*------------------------------------------------------------------------*/
/*------------------------------------------------------------------------*/
#define SPY_MAX_ODT                   6
#define SPY_DAQ_LIST                  CCP_u8DAQ_LST_DAQ_FAST
#define SPY_DAQ_EVENT                 CCP_u8DAQ_EVT_EVENT_FAST
#define SPY_MAX_QTY_DATA_POST_EVENT   100
#define SPY_MAX_QTY_DATA_PRE_EVENT    100
#define SPY_MAX_QTY_DATA              (SPY_MAX_QTY_DATA_POST_EVENT + SPY_MAX_QTY_DATA_PRE_EVENT)
#define SPY_NB_SGN                    SPY_MAX_ODT * 7      



extern uint8 SPY_ValueArray[SPY_MAX_QTY_DATA][SPY_NB_SGN];


#endif

/*------------------------------ END OF FILE -----------------------------*/
