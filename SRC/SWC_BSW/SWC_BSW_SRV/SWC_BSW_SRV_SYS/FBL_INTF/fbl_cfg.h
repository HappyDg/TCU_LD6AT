/* -----------------------------------------------------------------------------
  Filename:    fbl_cfg.h
  Description: Toolversion: 06.02.00.01.50.02.99.00.00.00
               
               Serial Number: CBD1500299
               Customer Info: Valeo Systèmes de Contrôle Moteur
                              Package: FBL Vector SLP3 - for predevelopment projects without car manufacturer specific characteristics
                              Micro: TC265
                              Compiler: Hightec 4.6.3.1
               
               
               Generator Fwk   : GENy 
               Generator Module: GenTool_GenyFblCanBase
               
               Configuration   : C:\Vector\CBD1500299_D00_Tricore\Demo\DemoFbl\Config\CBD1500299-Mod-TC265.gny
               
               ECU: 
                       TargetSystem: Hw_TricoreCpu
                       Compiler:     ANSI-C
                       Derivates:    INFINEON_TC265
               
               Channel "Channel0":
                       Databasefile: D:\usr\usage\Delivery\CBD15x\CBD1500299\D00_work\external\Demo\DemoFbl\Config\DemoFBL_Vector_SLP3.dbc
                       Bussystem:    CAN
                       Manufacturer: Vector
                       Node:         Demo

 ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
  C O P Y R I G H T
 -------------------------------------------------------------------------------
  Copyright (c) 2001-2015 by Vector Informatik GmbH. All rights reserved.
 
  This software is copyright protected and proprietary to Vector Informatik 
  GmbH.
  
  Vector Informatik GmbH grants to you only those rights as set out in the 
  license conditions.
  
  All other rights remain with Vector Informatik GmbH.
 -------------------------------------------------------------------------------
 ----------------------------------------------------------------------------- */

#if !defined(__FBL_CFG_H__)
#define __FBL_CFG_H__

/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

#define FBL_ENABLE_STAY_IN_BOOT
#define FBL_WATCHDOG_ON
#define FBL_WATCHDOG_TIME                    (1 / FBL_REPEAT_CALL_CYCLE)
#define FBL_HEADER_ADDRESS                   0xA0000400u
#define FBL_ENABLE_APPL_TASK
#define FBL_ENABLE_MULTIPLE_MODULES
#define FBL_DIAG_BUFFER_LENGTH               4095
#define FBL_DIAG_TIME_P2MAX                  (10 / FBL_REPEAT_CALL_CYCLE)
#define FBL_DIAG_TIME_P3MAX                  (5000 / FBL_REPEAT_CALL_CYCLE)
#define FBL_DISABLE_SLEEPMODE
#define FBL_SLEEP_TIME                       300000
#define kFillChar                            0xFFu
#define FBL_DISABLE_MULTIPLE_MEM_DEVICES
#define FBL_DISABLE_PRESENCE_PATTERN
#define FBL_ENABLE_FBL_START
#define FBL_ENABLE_RESPONSE_AFTER_RESET
#define FBL_DISABLE_USERSUBFUNCTION
#define FBL_DISABLE_USERSERVICE
#define FBL_MTAB_NO_OF_BLOCKS                3
/* Data Processing */
#define FBL_DISABLE_DATA_PROCESSING
#define FBL_DISABLE_ENCRYPTION_MODE
#define FBL_DISABLE_COMPRESSION_MODE
/* Project State */
#define FBL_INTEGRATION                      2
#define FBL_PRODUCTION                       1
#define FBL_PROJECT_STATE                    FBL_INTEGRATION
#define FBL_ENABLE_SYSTEM_CHECK
#define FBL_ENABLE_DEBUG_STATUS
#define FBL_ENABLE_ASSERTION
/* FblLib_Mem */
#define FBL_MEM_PROC_BUFFER_SIZE             0x0100
#define FBL_MEM_VERIFY_SEGMENTATION          0x40
#define FBL_DISABLE_ADAPTIVE_DATA_TRANSFER_RCRRP
#define FBL_DISABLE_PIPELINED_PROGRAMMING
#define FBL_MEM_WRITE_SEGMENTATION           0x0100
#define FBL_ENABLE_UNALIGNED_DATA_TRANSFER
/* CAN Identifier */
#define FBL_CAN_FUNC_RXID                    MK_STDID(0x777)
#define FBL_CAN_RXID                         MK_STDID(0x5a0)
#define FBL_CAN_TXID                         MK_STDID(0x5b0)
#define FBL_ENABLE_STDID_OPTIMIZATION
#define FBL_DISABLE_EXTID_OPTIMIZATION
#define FBL_NUMBER_OF_NODES                  1
#define FBL_NUMBER_OF_CHANNELS               1
#define FBL_DISABLE_BUSTYPE_CANFD

/* TriCore specific ********************************************************** */
#define FLASH_SIZE                           2860
#define FBL_SYSCLK                           100000
#define FBL_COMPARE_REG_VAL                  (FBL_SYSCLK - 1)
#define FBL_PLL_DIVIDER_VALUE                0x638304
#define FBL_ENABLE_READ_ERASED_FLASH
#define FBL_PF0_SIZE                         1024
#define FBL_PF1_SIZE                         1536
#define FBL_PF2_SIZE                         0
#define FBL_PF3_SIZE                         0

#define CAN_TP_FUNC_RXID                     0x0777
#define CAN_TP_RXID                          0x5a0
#define CAN_TP_TXID                          0x5b0

#define FBL_REG_BASE_ADR                     0xF0018000u
#define FBL_CAN_NBTR                         0x4D00u
#define FBL_CAN_CLKDIV                       1023u
#define FBL_CAN_NODE_NUM                     0u
#define FBL_CAN_NPCR                         0x01u
#define kFblCanMCRValue                      0x0002u

#define FBL_CAN_MAX_NUM_NODE                 4u
#define FBL_CAN_RESERVED_NUM_NODE            10u
#define FBL_CAN_MAX_LIST                     8u
#define FBL_CAN_RESERVED_LIST                8u
#define FBL_CAN_MAX_MSPND                    8u
#define FBL_CAN_RESERVED_MSPND               8u
#define FBL_CAN_MAX_MSID                     8u
#define FBL_CAN_RESERVED_MSID                8u
#define FBL_CAN_MAX_NUM_MSGOBJ               256u

/* Manufacturer specific part ************************************************ */
/* FBL multiple nodes support: */
#define FBL_DISABLE_MULTIPLE_NODES
/* kNmEcuNr */
#ifdef VGEN_ENABLE_CAN_DRV
#else
#define kNmEcuNr                             0x7FFFFBFF
#endif

#define FBL_DISABLE_GAP_FILL

#define SWM_DATA_MAX_NOAR                    8
#define FLASHDRIVER_BLOCKINDEX               0x30
#define FBL_SEC_ACCESS_DELAY_TIME            600000
#define FBL_ENABLE_SEC_ACCESS_DELAY
#define FBL_DISABLE_MINIMUM_PROGRAMMING_SEQUENCE
#define FBL_DIAG_ENABLE_ADDR_BASED_DOWNLOAD


/* -----------------------------------------------------------------------------
    &&&~ 
 ----------------------------------------------------------------------------- */

/* User Config File ********************************************************** */
/* Enable development board features */
#define FBL_ENABLE_VECTOR_HW

/* XCP support */
#if defined( VGEN_ENABLE_XCP )
# define FBL_ENABLE_XCP
# define GetXcpDisableState() (!GetXcpEnabled())
#endif
/* User Section ************************************************************** */
#define FBL_ENABLE_CAN_CONFIRMATION
#define FBL_ENABLE_SECMOD_VECTOR
#define FBL_ENABLE_WRAPPER_NV
/* *************************************************************************** */


/* begin Fileversion check */
#ifndef SKIP_MAGIC_NUMBER
#ifdef MAGIC_NUMBER
  #if MAGIC_NUMBER != 200089914
      #error "The magic number of the generated file <C:\Vector\CBD1500299_D00_Tricore\Demo\DemoFbl\Appl\GenData\fbl_cfg.h> is different. Please check time and date of generated files!"
  #endif
#else
  #define MAGIC_NUMBER 200089914
#endif  /* MAGIC_NUMBER */
#endif  /* SKIP_MAGIC_NUMBER */

/* end Fileversion check */

#endif /* __FBL_CFG_H__ */
