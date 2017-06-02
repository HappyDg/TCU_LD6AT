/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2013)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Can_17_MCanP.c $                                           **
**                                                                           **
**  $CC VERSION : \main\dev_tc23x_as4.0.3\24 $                               **
**                                                                           **
**  $DATE       : 2015-04-17 $                                               **
**                                                                           **
**  AUTHOR    : DL-AUTOSAR-Engineering                                       **
**                                                                           **
**  VENDOR    : Infineon Technologies                                        **
**                                                                           **
**  DESCRIPTION  : This file contains                                        **
**                - CAN driver API implementation                            **
**                - implementation of the interrupt service routines         **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/**  TRACEABILITY: [cover parentID=DS_NAS_CAN_PR912,
DS_NAS_CAN_PR228_1,DS_AS403_CAN365,DS_AS_CAN079
DS_NAS_CAN_PR843,DS_AS_CAN027_CAN028_CAN082_CAN083_CAN424,
SAS_NAS_ALL_PR749,SAS_NAS_ALL_PR102,SAS_NAS_ALL_PR470,
SAS_NAS_ALL_PR128,SAS_NAS_ALL_PR70,SAS_NAS_ALL_PR1652,
SAS_NAS_ALL_PR630_PR631,DS_NAS_CAN_PR1650_PR1654,
DS_NAS_CAN_PR131,DS_NAS_CAN_PR115]    
[/cover]                                                                 **/

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Register definition file for Aurix target */
#include "IfxCan_reg.h"
#include "IfxSrc_reg.h"

/* MCAL header file containing global macros, type definitions and functions 
needed by all MCAL drivers */
#include "Mcal.h"  

/* Include services for suspend/resume interrupts */
#include "SchM_17_McalCfg.h"
#include SCHM_CAN_17_MCANP_HEADER

/* CAN module header file, this includes CAN Module configuration header file */
#include "Can_17_MCanP.h"

/* Include the declarations of CAN callback functions and types */
#include "CanIf_Cbk.h"

/* Include Diagnostic Event Manager header file */
#if (CAN_E_TIMEOUT_DEM_REPORT == CAN_ENABLE_DEM_REPORT)
#include "Dem.h"
#endif

/* Include the declarations of EcuM callback functions and types */
#if (CAN_WAKEUP_CONFIGURED == STD_ON)
#include "EcuM_Cbk.h"
#endif

/* Inclusion of CAN Test Stubs */
#ifdef IFX_CAN_DEBUG02
#include "Test_CanDebug.h"
#endif

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS403_CAN111,DS_NAS_CAN_PR730]            **
**                                                                            **
**               Imported Compiler Switch Check - Version check               **
**                                                                            **
**               [/cover]                                                     **
*******************************************************************************/
/* Version check */

/* Check if the correct version of Can_17_MCanP.h is included */

#ifndef CAN_17_MCANP_AR_RELEASE_MAJOR_VERSION
#error "CAN_17_MCANP_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef CAN_17_MCANP_AR_RELEASE_MINOR_VERSION
#error "CAN_17_MCANP_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#ifndef CAN_17_MCANP_AR_RELEASE_REVISION_VERSION
#error "CAN_17_MCANP_AR_RELEASE_REVISION_VERSION is not defined. "
#endif

#if ( CAN_17_MCANP_AR_RELEASE_MAJOR_VERSION != 4U )
#error "CAN_17_MCANP_AR_RELEASE_MAJOR_VERSION does not match. "
#endif

#if ( CAN_17_MCANP_AR_RELEASE_MINOR_VERSION != 0U )
#error "CAN_17_MCANP_AR_RELEASE_MINOR_VERSION does not match. "
#endif

/* Check for definition of SW version Information */
#ifndef CAN_17_MCANP_SW_MAJOR_VERSION
#error "CAN_17_MCANP_SW_MAJOR_VERSION is not defined. "
#endif

#ifndef CAN_17_MCANP_SW_MINOR_VERSION
#error "CAN_17_MCANP_SW_MINOR_VERSION is not defined. "
#endif

#ifndef CAN_17_MCANP_SW_PATCH_VERSION
#error "CAN_17_MCANP_SW_PATCH_VERSION is not defined. "
#endif

/* Check for Correct inclusion of headers */
#if ( CAN_17_MCANP_SW_MAJOR_VERSION != 2U )
#error "CAN_17_MCANP_SW_MAJOR_VERSION does not match. "
#endif
#if ( CAN_17_MCANP_SW_MINOR_VERSION != 3U )
#error "CAN_17_MCANP_SW_MINOR_VERSION does not match. "
#endif

/* Inter Module Check */
/* Check for the correct version usage in the used modules */

/* Det AUTOSAR Version Info Check */
#if ( CAN_DEV_ERROR_DETECT == STD_ON)
#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error "DET_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef DET_AR_RELEASE_MINOR_VERSION
#error "DET_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#if (IFX_DET_VERSION_CHECK == STD_ON)
#if ( DET_AR_RELEASE_MAJOR_VERSION != CAN_17_MCANP_AR_RELEASE_MAJOR_VERSION )
#error "DET_AR_RELEASE_MAJOR_VERSION does not match. "
#endif
#if ( DET_AR_RELEASE_MINOR_VERSION != CAN_17_MCANP_AR_RELEASE_MINOR_VERSION )
#error "DET_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#endif /* #if (IFX_DET_VERSION_CHECK == STD_ON) */
#endif /* #if ( CAN_DEV_ERROR_DETECT == STD_ON) */

/* Dem AUTOSAR Version Info Check */
#if (CAN_E_TIMEOUT_DEM_REPORT == CAN_ENABLE_DEM_REPORT)
#ifndef DEM_AR_RELEASE_MAJOR_VERSION
#error "DEM_AR_RELEASE_MAJOR_VERSION is not defined. "
#endif

#ifndef DEM_AR_RELEASE_MINOR_VERSION
#error "DEM_AR_RELEASE_MINOR_VERSION is not defined. "
#endif

#if (IFX_DEM_VERSION_CHECK == STD_ON)
#if ( DEM_AR_RELEASE_MAJOR_VERSION != CAN_17_MCANP_AR_RELEASE_MAJOR_VERSION )
#error "DEM_AR_RELEASE_MAJOR_VERSION does not match. "
#endif
#if ( DEM_AR_RELEASE_MINOR_VERSION != CAN_17_MCANP_AR_RELEASE_MINOR_VERSION )
#error "DEM_AR_RELEASE_MINOR_VERSION does not match. "
#endif

#endif /* #if (IFX_DEM_VERSION_CHECK == STD_ON)  */
#endif /* #if (CAN_E_TIMEOUT_DEM_REPORT == CAN_ENABLE_DEM_REPORT) */

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/

/*
For internal debugging only; 
To simulate timeout error;
*/

#ifdef IFX_CAN_DEBUG 
extern volatile uint8 TestCan_DebugMask; 
#endif

#ifdef IFX_CAN_DEBUG01
extern volatile uint32 TestCan_DebugMask01;
#endif

#ifdef IFX_CAN_DEBUG03
extern volatile uint32 TestCan_DebugMask03;
#endif

#ifdef IFX_CAN_DEBUG04
extern volatile uint32 TestCan_DebugMask04;
#endif


/* Panel commands for static allocation */
#define CAN_PANCMD_STATIC_ALLOCATE      ((uint8)2U)

/* Bit field positions of message object control/status register */
#define CAN_MOCTR_RXPND_CLR             (0x00000001U)
#define CAN_MOCTR_TXPND_CLR             (0x00000002U)
#define CAN_MOCTR_RXUPD_CLR             (0x00000004U)
#define CAN_MOCTR_NEWDAT_CLR            (0x00000008U)
#define CAN_MOSTAT_MSGLST_CLR           (0x00000010U)
#define CAN_MOCTR_MSGVAL_CLR            (0x00000020U)
#define CAN_MOCTR_RXEN_CLR              (0x00000080U)
#define CAN_MOCTR_TXRQ_CLR              (0x00000100U)
#define CAN_MOCTR_TXEN1_CLR             (0x00000400U)
#define CAN_MOCTR_DIR_CLR               (0x00000800U)

/* To clear MOSTAT bits - TXEN0, TXRQ and NEWDAT */
#define CAN_MOCTR_WRITE_REQ_CLR         (0x00000308U)

/* To Enable/Disable CAN Node via NCRx.INIT */
#define CAN_NODE_ENABLE                 (0U)
#define CAN_NODE_DISABLE                (1U)

/* To Enable/Disable Transmission via NCRx.TXDIS */
#define CAN_NODE_TX_ENABLE              (0U)
#define CAN_NODE_TX_DISABLE             (1U)

/* Invalid CAN controller Id. Used for mapping non-activated CAN Controllers */
#define CAN_INVALID_HW_CONTROLLER_ID    ((uint8)255)      

/* Bit field position of ALERT bit in Node Status Register */  
#define CAN_NSR_ALERT                   (0x00000020U)

/* Node status register: Mask value for writable bits */
#define CAN_NSR_WRITABLE_VALUE_MASK     (0x3FFU)

/* Bit field positions of Node Control Register */  
#define CAN_NCR_INIT                    (0x00000001U)
#define CAN_NCR_ALIE                    (0x00000008U)
#define CAN_NCR_CCE                     (0x00000040U)
#define CAN_NCR_FDEN                    (0x00000200U)


/* CLKSEL values for selecting clock source via MCR register */
#define CAN_MCR_CLKSEL_NO_CLOCK         (0U)
#define CAN_MCR_CLKSEL_FASYN_CAN        (1U)
#define CAN_MCR_CLKSEL_FERAY_PLL        (4U)


/* Bit field positions of MO FIFO function control Register */
#define CAN_FIFO_MOFCR                  (0x00040001U)
#define CAN_FIFO_MOFCR_MMC_BIT          (0x01U)
#define CAN_FD64BYTES_MOFCR_MMC_BIT     (0x05U)


/* Bit field positions of MO FIFO pointer Register */
#define CAN_MOFGPR_SEL_SHIFT            (24U)
#define CAN_MOFGPR_TOP_SHIFT            (8U)
#define CAN_MOFGPR_CUR_SHIFT            (16U)

/* Macro for MOCTR Setting of Rx FIFO slave objects */
#define CAN_MOCTR_RX_FIFO_SLAVE         (0x00200080U)

/* Macro for MASK */
#define CAN_8BIT_MASK                   (0x000000FFU)

/* Bit field positions of CAN Service Request Control Register */  
#define CAN_SRC_CLRR                    (0x02000000U)
#define CAN_SRC_SRE                     (0x00000400U)

/* Values */
#define CAN_ZERO                        (0U)
#define CAN_ONE                         (1U)
#define CAN_TWO                         (2U)
#define CAN_THREE                       (3U)
#define CAN_FOUR                        (4U)
#define CAN_SIX                         (6U)
#define CAN_SEVEN                       (7U)
#define CAN_EIGHT                       (8U)
#define CAN_NINE                        (9U)
#define CAN_ELEVEN                      (11U)
#define CAN_FIFTEEN                     (15U)
#define CAN_TWENTY_FOUR                 (24U)
#define CAN_THIRTY_TWO                  (32U)
#define CAN_THIRTY_SIX                  (36U)
#define CAN_SIXTY_FOUR                  (64U)

#define CAN_8BITDIV3FACTOR              (0xABU)

/* Values used to calculate Kernel Count and Controller's ID w.r.t Kernel */
#define CAN_KERCNT                      (CAN_NUM_CONTROLLERS_IN_KERNEL1)
#define CAN_NODNKER                     (3U) 

/* Positions */
#define CAN_POS_5                       (5U)
#define CAN_POS_18                      (18U)

/* Bus-off error limit value */
#define CAN_BUSOFF_LIMIT                (0xFFU)

#if ((CAN_RESET_SFR_AT_INIT == STD_ON)||(CAN_DEINIT_API == STD_ON))
#define CAN_KERNEL_RESET_TIMEOUT        (0x40U) 
#endif


/* Shift values for bit fields of Message Object Arbitration Register */
#define CAN_PRI_CLASS_ID_BASED          (2U)
#define CAN_MOAR_ID_STD_SHIFT           (18U)
#define CAN_PRIORITY_ID_BASED           ((uint32)0x80000000U)
#define CAN_USE_EXTENDED_ID             ((uint32)0x20000000U)
#define CAN_FD_EXTENDED_SET             ((uint32)0x40000000U)
#define CAN_FD_STANDARD_SET             ((uint16)0x4000U)

/* Maximum size of the CAN Data */
#define CAN_MAX_DATA_LENGTH          (8U)

/* Maximum size of the CAN FD  */
#define CAN_MAX_FD_LENGTH            (64U)

/* Shift values for storing interrupt enabled status */
#define CAN_RX_INT_SHIFT                (1U)
#define CAN_TX_INT_SHIFT                (2U)

/* Mask for maximum hardware objects per message pending register */
#define CAN_MAX_HWOBJ_PER_MSPND_REG_1   (0x1FU)

/* Number of message pending registers */
#define CAN_NUM_MSPND_REGS              (8U)

/* MSID register value if there is no message pending bit set. */
#define CAN_MSID_NO_MSG_PND_VALUE       (0x00000020U)

/* Macro for shift count of MPN[7:5] bits (indicate MSPND register used) */
#define CAN_MOIPR_MPN_MSPND_SHIFT       (5U)

/* Macro to set MSB for Extended messages */
#define CAN_EXTENDED_MSB_SET            (0x80000000U)

#if (CAN_FD_ENABLE== STD_ON)
#define CAN_MOSize                        (3U)
#define CAN_RXSize                        (64U)
#else
#define CAN_MOSize                        (1U)
#define CAN_RXSize                        (8U)
#endif

#if (CAN_BR_ERAY_PLL_CLKSEL == STD_OFF)
    /* Select fASYN_CAN as the input source */
#define CAN_MCR_CLKSEL         (CAN_MCR_CLKSEL_FASYN_CAN)
#else
    /* Select fERAY as the input source */
#define CAN_MCR_CLKSEL         (CAN_MCR_CLKSEL_FERAY_PLL)
#endif

/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/

/* 
Values for CAN Driver states. 
*/   
/* CAN Driver is NOT initialized. */
#define  CAN_DS_UNINIT                  ((Can_17_MCanP_DriverStateType)0)
/* CAN Driver is initialized. */
#define  CAN_DS_READY                   ((Can_17_MCanP_DriverStateType)1)

/*----------------------Register Address Translation--------------------------*/


/* CAN Service Request Control Registers */
#define CAN_SRC                  ((volatile Ifx_SRC_SRCR*)(void *)&SRC_CANINT0)

/* 
Service Request Node Allocation/Mapping: 

N : Number of CAN Controller in the device

Node X --> Transmit SRN = X
--> Receive SRN = N + X
--> BusOff SRN = (2 * N) + X*Y ; 
Y = 0 for all EP devices, Y = 1 for all HE devices

For Example,

Mapping for TC27x --> N = 4, i.e., 4 CAN Controllers(Nodes):

|------------------|--------------|--------------|--------------|--------------|
|       TC27xCA    | Controller 0 | Controller 1 | Controller 2 | Controller 3 |
|------------------|--------------|--------------|--------------|--------------|
|Transmit interrupt|     SRN0     |      SRN1    |     SRN2     |     SRN3     |
|------------------|--------------|--------------|--------------|--------------|
| Receive interrupt|     SRN4     |      SRN5    |     SRN6     |     SRN7     |
|------------------|--------------|--------------|--------------|--------------|
|BusOff interrupt  |     SRN8     |      SRN9    |     SRN10    |     SRN11    |
*------------------*--------------*--------------*--------------*--------------*

*/

/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/


/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/

#define CAN_17_MCANP_START_SEC_CODE
#include "MemMap.h"

/* Function to initialize CAN Module global variables */
IFX_LOCAL_INLINE void Can_lInitGlobalVar(void);

/* Function to initialize CAN Module clock/timing registers */
IFX_LOCAL_INLINE void Can_lInitClkSetting(void);

#if ((CAN_RESET_SFR_AT_INIT == STD_ON)||(CAN_DEINIT_API == STD_ON))
/* Initializes the Kernel registers to default value */ 
IFX_LOCAL_INLINE void Can_lResetSFR(uint8 KerIdx);
#endif

/* Function to check for CAN module hardware failure */
IFX_LOCAL_INLINE Std_ReturnType Can_lInitDemCheck(void);

/* Function to initialize CAN controllers */
IFX_LOCAL_INLINE void Can_lInitializeController(uint8 ControllerId, 
                                            uint8 HwControllerId);

/* Function to initialize CAN controller status */
IFX_LOCAL_INLINE void Can_lInitControllerStatus(void);

/* Function to initialize message objects */
IFX_LOCAL_INLINE Std_ReturnType Can_lInitMsgObj(void);

/* Function to initialize transmit message objects */
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
IFX_LOCAL_INLINE Std_ReturnType Can_lInitTxMsgObj(void);
#endif 

/* Function to initialize receive message objects */
#if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
IFX_LOCAL_INLINE Std_ReturnType Can_lInitRxMsgObj(void);
#endif

#if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/* checks if the baudrate is configured or not */
static uint8 Can_lSearchBaudrate(uint8 Controller, const uint16 Baudrate);
#endif

/* Function to set CAN controller baudrate */
static void Can_lSetBaudrate(uint8 HwControllerId,
                             uint32 ControllerBaudrate);

/* Function to disable CAN module interrupts */
IFX_LOCAL_INLINE void Can_lDisableInterrupts (uint8 Controller);

/* Function to enable CAN module interrupts */
IFX_LOCAL_INLINE void Can_lEnableInterrupts (uint8 Controller);

/* Function to check DET for Can_17_MCanP_Write API  */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
IFX_LOCAL_INLINE Std_ReturnType Can_lWriteDetCheck(Can_HwHandleType Hth,
                                               const Can_PduType *PduInfo);
#endif

/* Function to clear and enable interrupt service request */
IFX_LOCAL_INLINE void 
  Can_lClearAndEnableInterrupt(uint8 ServiceRequestNumber);

/* Function to program message object for transmission */
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
IFX_LOCAL_INLINE Can_ReturnType Can_lWriteMsgObj(uint8 HthIndex,
                                             uint8 HwObjectId,
                                             const Can_PduType *PduInfo);
#endif

/* Function for handling message reception */
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
static void Can_lReceiveHandler(uint8 HwControllerId);

/* Function to extract data from message object */
#if (CAN_DEV_ERROR_DETECT == STD_ON)
IFX_LOCAL_INLINE Std_ReturnType Can_lRxIsrExtractData(uint8 HwControllerId,
                                                  uint8 HwObjectId,
                                                  uint8 MsgIndex,
                                                  uint8 PndBitPosition);
#else
IFX_LOCAL_INLINE void Can_lRxIsrExtractData(uint8 HwControllerId,
                                        uint8 HwObjectId,
                                        uint8 MsgIndex,
                                        uint8 PndBitPosition);
#endif

/* Function to clear a receive message object */
static void Can_lClearReceivedMsg(uint8 HwControllerId);

/* Function to handle wakeup event */
#if(CAN_WAKEUP_CONFIGURED == STD_ON)
static void Can_lWakeupHandler(uint8 HwControllerId);
#endif
#endif

/* Function to allocate hardware objects to CAN controllers */
static Std_ReturnType Can_lAllocateHwObject(uint8 HwControllerId, 
                                            uint8 HwObjectId);

/* Function to handle CAN Controller state transitions if wakeup is supported */
#if(CAN_WAKEUP_CONFIGURED == STD_ON)
IFX_LOCAL_INLINE void Can_lSetModeWuSupportOn(uint8 Controller,
                                          uint8 HwControllerId,
                                          Can_StateTransitionType Transition);
#endif

/* Function to handle CAN Controller state transitions,
if wakeup is not supported */
IFX_LOCAL_INLINE void Can_lSetModeWuSupportOff(uint8 Controller,
                                           uint8 HwControllerId,
                                           Can_StateTransitionType Transition);

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/* Function for checking wrong parameter (Controller) to an API.
Used in APIs affecting single CAN controller */
static Std_ReturnType Can_lReportDetParamController(uint8 ControllerId,
                                                    uint8 ServiceId);

/* Function to check for CAN driver initialization status for DET checking */
static Std_ReturnType Can_lReportDetUninit(uint8 ServiceId);

/* Function to check for invalid CAN controller state transitions */
IFX_LOCAL_INLINE Std_ReturnType Can_lModeDetCheck(uint8 Controller,
                                            Can_StateTransitionType Transition);

#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */ 

#if (CAN_NUM_RX_FIFO_MAX > 0U)

/* Function to Initialize Rx FIFO Message Objects */
IFX_LOCAL_INLINE Std_ReturnType Can_lRxFifoInit(void);

/* Function to Initialize Rx FIFO Base Message Object */
#if (CAN_STANDARD_ID_ONLY == STD_OFF)       
IFX_LOCAL_INLINE void Can_lRxFifoBaseMOInit(
  const Can_RxFifoConfigType* RxFifoCfgPtr,
  uint16 FifoIndex,
  uint8 FrameType);
#else
IFX_LOCAL_INLINE void Can_lRxFifoBaseMOInit(
  const Can_RxFifoConfigType* RxFifoCfgPtr,
  uint16 FifoIndex);
#endif /* #if (CAN_STANDARD_ID_ONLY == STD_OFF)        */

/* Function to handle FIFO reception event */
IFX_LOCAL_INLINE void Can_lRxFifoHandler(uint8 HwControllerId,
                                     uint8 HwObjectId);

/* Function to extract data from receive FIFO */
IFX_LOCAL_INLINE void Can_lRxFifoExtractData(uint16 FifoTopBot,
                                         uint8 CurrentMo,
                                         uint8 HwControllerId,
                                         uint16 Hfh,
                                         uint8 Threshold);
#endif /* #if (CAN_NUM_RX_FIFO_MAX > 0U) */

#define CAN_17_MCANP_STOP_SEC_CODE
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/

/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/* The addresses of registers are derived from SFR file included in mcureg.h */

#define CAN_17_MCANP_START_SEC_CONST_8BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

#ifdef CAN_MOD_R_AVAILABLE
/*Number of CAN Controllers per Kernel */
static const uint8 CAN_NUM_CONTROLLERS_IN_KERNEL[] =
{ CAN_NUM_CONTROLLERS_IN_KERNEL1, 
CAN_NUM_CONTROLLERS_IN_DEVICE - CAN_NUM_CONTROLLERS_IN_KERNEL1};
#else
/*Number of CAN Controllers per Kernel */
static const uint8 CAN_NUM_CONTROLLERS_IN_KERNEL[] =
{ CAN_NUM_CONTROLLERS_IN_KERNEL1 };
#endif

#define CAN_17_MCANP_STOP_SEC_CONST_8BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"


#define CAN_17_MCANP_START_SEC_CONST_32BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

#if(CAN_PB_FIXEDADDR == STD_ON)
/* The config pointer is initialised to first instance of configuration */
static const Can_17_MCanP_ConfigType* const Can_kConfigPtr = 
  &Can_17_MCanP_ConfigRoot[0];
#endif

#ifdef CAN_MOD_R_AVAILABLE
#if (CAN_NUM_CONTROLLERS_IN_KERNEL1 == 3U )
/* CAN base address Kernel wise */
static Ifx_CAN* const CAN_KER[] = { &MODULE_CAN, &MODULE_CAN1 };
#else
/* CAN base address Kernel wise */
static Ifx_CAN* const CAN_KER[] = { &MODULE_CAN, &MODULE_CANR };
#endif
#else
/* CAN base address Kernel wise */
static Ifx_CAN* const CAN_KER[] = { &MODULE_CAN };
#endif

/* 
27xCA:
There is only 1 Kernel containing 4 controllers.Hence 4 controllers belong 
to Kernel 0

TC26x:
There is only 1 Kernel containing 5 controllers.Hence 5 controllers belong 
to Kernel 0

29x: 
There are 2 Kernels containing 4 controllers in one and 2 controllers in 
the other. First 4 Controllers belong to Kernel 0 and the next 2 
controllers belong to Kernel 1

23x:
There are 2 Kernels containing 3 controllers in one and 3 controllers in 
the other. First 3 Controllers belong to Kernel 0 and the next 3 
controllers belong to Kernel 1

22x, 21x: 
There is only 1 Kernel containing 3 controllers.Hence 3 controllers belong 
to Kernel 0
*/

#if (CAN_NUM_CONTROLLERS_IN_KERNEL1 == 3U )
/* EP Device */
#define CAN_HEDEVICE                   (0U)
/* Following Macro calculates (x/3) only for x = {0,1,2,3,4,5} */ 
/*IFX_MISRA_RULE_19_07_STATUS=Function-like macro is used to have a 
generic code across devices*/
#define CAN_CALC_KERIDX(x)           ((uint8)(((x)* 3U)>> 3U))
/* Following Macro calculates (x%3) only for x = {0,1,2,3,4,5} */
/*IFX_MISRA_RULE_19_07_STATUS=Function-like macro is used to have a 
generic code across devices*/
#define CAN_CALC_HWCTRLID(x)       ((uint8)((x)- ((((x)* 3U)>> 3U)*3U)))
#endif

#if (CAN_NUM_CONTROLLERS_IN_KERNEL1 == 4U )
/* HE Device */
#define CAN_HEDEVICE                   (1U)
/* Following Macro calculates (x/4) */ 
/*IFX_MISRA_RULE_19_07_STATUS=Function-like macro is used to have a 
generic code across devices*/
#define CAN_CALC_KERIDX(x)          ((uint8)((x)>> 2U))
/* Following Macro calculates (x%4) */
/*IFX_MISRA_RULE_19_07_STATUS=Function-like macro is used to have a 
generic code across devices*/
#define CAN_CALC_HWCTRLID(x)       ((uint8)(((x))& 3U))
#endif

#if (CAN_NUM_CONTROLLERS_IN_KERNEL1 == 5U )
/* HE Device */
#define CAN_HEDEVICE                   (1U)
/* Following Macro calculates (x/5) only for x = {0,1,2,3,4} */ 
/*IFX_MISRA_RULE_19_07_STATUS=Function-like macro is used to have a 
generic code across devices*/
#define CAN_CALC_KERIDX(x)           ((uint8)(((x)* 7U)>> 5U))
/* Following Macro calculates (x%5) only for x = {0,1,2,3,4} */
/*IFX_MISRA_RULE_19_07_STATUS=Function-like macro is used to have a 
generic code across devices*/
#define CAN_CALC_HWCTRLID(x)       ((uint8)((x)- ((((x)* 7U)>> 5U)*5U)))
#endif


#define CAN_17_MCANP_STOP_SEC_CONST_32BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

/******************************************************************************
**                      Private Variable Definitions                         **
******************************************************************************/

#define CAN_17_MCANP_START_SEC_VAR_16BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
/* SW Handle passed by CAN Interface to Can_17_MCanP_Write API. This will 
identify the request in the confirmation callback function, 
CanIf_TxConfirmation(). */
static PduIdType 
  Can_SwObjectHandle[CAN_NUM_KERNELS_IN_DEVICE][CAN_TX_HARDWARE_OBJECTS_MAX];
#endif

#define CAN_17_MCANP_STOP_SEC_VAR_16BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

#define CAN_17_MCANP_START_SEC_VAR_8BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

/* This variable keeps track of number of calls to 
Can_17_MCanP_DisableControllerInterrupts API. It is used to implement 
incremental disable functionality. */  
#if (CAN_DEBUG_SUPPORT == STD_ON)
/*IFX_MISRA_RULE_08_10_STATUS=Can_17_MCanP_InterruptDisableCount variable is 
declared as extern in Can_17_MCanP_Dbg.h, which will be included by 
application for debugging*/
uint8 Can_17_MCanP_InterruptDisableCount[CAN_NUM_CONTROLLER_MAX]; 
#else
static uint8 Can_17_MCanP_InterruptDisableCount[CAN_NUM_CONTROLLER_MAX]; 
#endif

/* This variable stores status of whether interrupts are enabled */  
static uint8 Can_InterruptsEnabledStatus[CAN_NUM_CONTROLLER_MAX];

/* This variable stores CanControllerId corresponding to the 
CAN Controller Id in hardware */  
static uint8 Can_NodeIdMap[CAN_NUM_CONTROLLERS_IN_DEVICE];

/* This variable stores the wakeup event status */  
#if(CAN_WAKEUP_CONFIGURED == STD_ON)
#if (CAN_DEBUG_SUPPORT == STD_ON)
/*IFX_MISRA_RULE_08_10_STATUS=Can_17_MCanP_ControllerWakeupStatus variable is 
declared as extern in Can_17_MCanP_Dbg.h, which will be included by 
application for debugging*/
uint8 Can_17_MCanP_ControllerWakeupStatus[CAN_NUM_CONTROLLER_MAX];
#else
static uint8 Can_17_MCanP_ControllerWakeupStatus[CAN_NUM_CONTROLLER_MAX];
#endif
#endif

/* This flag stores the CAN driver state */
#if (CAN_DEBUG_SUPPORT == STD_ON)
/*IFX_MISRA_RULE_08_10_STATUS=Can_17_MCanP_DriverState variable is 
declared as extern in Can_17_MCanP_Dbg.h, which will be included by 
application for debugging*/
Can_17_MCanP_DriverStateType Can_17_MCanP_DriverState;
#else
static Can_17_MCanP_DriverStateType Can_17_MCanP_DriverState;
#endif

#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
/* Buffer for copying the received data and pass to CanIf */
#if (CAN_FD_ENABLE== STD_ON)
static uint8 Can_RxMessageData
  [CAN_NUM_CONTROLLERS_IN_DEVICE][CAN_SIXTY_FOUR];
#else
static uint8 Can_RxMessageData
  [CAN_NUM_CONTROLLERS_IN_DEVICE][CAN_EIGHT];
#endif
#endif

#if (CAN_NUM_RX_FIFO_MAX > 0U)
/* Buffer for copying the received FIFO data and pass to CanIf */
static uint8 Can_RxFifoMessageData[CAN_NUM_CONTROLLERS_IN_DEVICE][CAN_EIGHT];
#endif

#define CAN_17_MCANP_STOP_SEC_VAR_8BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

#define CAN_17_MCANP_START_SEC_VAR_32BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

#if(CAN_PB_FIXEDADDR == STD_OFF)
/* Pointer to store config pointer */
static const Can_17_MCanP_ConfigType* Can_kConfigPtr;
#endif

/* This variable stores the current state of a CAN controller */  
#if (CAN_DEBUG_SUPPORT == STD_ON)
/*IFX_MISRA_RULE_08_10_STATUS=Can_17_MCanP_ControllerMode[]array variable is 
declared as extern in Can_17_MCanP_Dbg.h, which will be included by 
application for debugging*/
CanIf_ControllerModeType Can_17_MCanP_ControllerMode[CAN_NUM_CONTROLLER_MAX];
#else
static CanIf_ControllerModeType 
  Can_17_MCanP_ControllerMode[CAN_NUM_CONTROLLER_MAX];
#endif

/* MSIMASK register values for Rx Message Objects; They indicate Rx hardware
object numbers assigned to a CAN controller. */

/*IFX_MISRA_RULE_08_07_STATUS=Can_RxMsiMask is accessed in Multiple functions*/
static uint32 Can_RxMsiMask[CAN_NUM_CONTROLLERS_IN_DEVICE][CAN_NUM_MSPND_REGS];

/* MSIMASK register values for Tx Message Objects; They indicate Tx hardware
object numbers assigned to a CAN controller. */
/*IFX_MISRA_RULE_08_07_STATUS=Can_TxMsiMask is accessed in Multiple functions*/
static uint32 Can_TxMsiMask[CAN_NUM_CONTROLLERS_IN_DEVICE][CAN_NUM_MSPND_REGS];


#define CAN_17_MCANP_STOP_SEC_VAR_32BIT
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h" 

/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/

/* Memory map of the CAN driver code */
#define CAN_17_MCANP_START_SEC_CODE
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN223,DS_AS_CAN240,DS_AS_CAN174_CAN175,
DS_AS_CAN407_CAN420_CAN053_CAN091_CAN103_CAN238_CAN239_CAN245_CAN246_CAN250_CAN259_CAN196_CAN197_CAN425_CAN426,
DS_AS403_CAN408,DS_NAS_HE2_CAN_PR2892,DS_NAS_EP_CAN_PR2892,
DS_NAS_HE2_CAN_PR2937,DS_NAS_EP_CAN_PR2937,DS_NAS_HE2_CAN_PR3018,
DS_NAS_EP_CAN_PR3018]                                                         **
**                                                                            **
** Syntax           : void Can_17_MCanP_Init(const Can_17_MCanP_ConfigType*   **
**                                                 Config)                    **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x00                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : Config - Pointer to CAN driver configuration            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Driver Module Initialization function                   **
**                    - This function initializes:                            **
**                    * Static variables, including flags                     **
**                    * CAN HW Unit global hardware settings                  **
**                    * Controller specific settings for each CAN Controller  **
**  All CAN Controllers will be in state CANIF_CS_STOPPED after initialization**
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_Init(const Can_17_MCanP_ConfigType* Config)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Status;
#if (CAN_STANDARD_ID_ONLY != STD_ON)
  volatile uint8 SizeOfCanIdType;
#endif
  uint8 CtrlIndex;

  Status = E_OK; 
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)

#if(CAN_PB_FIXEDADDR == STD_OFF)

  if (NULL_PTR == Config) 
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      CAN_SID_INIT, CAN_E_PARAM_POINTER);

    Status = E_NOT_OK;
  }
#else
  /* Check if the config pointer is initialized to the 
  first instance of the configuration */
  if (Can_kConfigPtr != Config)
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      CAN_SID_INIT, CAN_E_PARAM_POINTER);

    Status = E_NOT_OK;
  }

#endif /* #if(CAN_PB_FIXEDADDR == STD_OFF) */

  if(E_OK == Status)
  {
    /* CAN driver is not in state UNINIT */
    if (CAN_DS_UNINIT != Can_17_MCanP_DriverState)
    {
      /* Report to DET */
      Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
        CAN_SID_INIT, CAN_E_TRANSITION);
      Status = E_NOT_OK;
    }
    else
    {
      /* CAN Controller is not in state UNINIT */
      for(CtrlIndex=CAN_ZERO;CtrlIndex<(Config->CanNumController);CtrlIndex++)
      {
        if(CANIF_CS_UNINIT != Can_17_MCanP_ControllerMode[CtrlIndex])
        {
          /* Report to DET */
          Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
            CAN_SID_INIT, CAN_E_TRANSITION);
          Status = E_NOT_OK;
        }
      }
    }
  }

#if (CAN_STANDARD_ID_ONLY != STD_ON)
  if(E_OK == Status)
  {
    SizeOfCanIdType = (uint8)sizeof(Can_IdType);

    if(SizeOfCanIdType == CAN_TWO)
    {
      Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
        CAN_SID_INIT, CAN_E_CAN_IDTYPE);
      Status = E_NOT_OK;
    }
  }
#endif /* #if (CAN_STANDARD_ID_ONLY != STD_ON) */

  if (E_OK == Status)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  
  {
    /* Store config pointer, such that it can be used throughout CAN driver */
#if(CAN_PB_FIXEDADDR == STD_OFF)
    Can_kConfigPtr = Config;
#else
#if (CAN_DEV_ERROR_DETECT == STD_OFF)
    /* To avoid compiler warning */
    UNUSED_PARAMETER (Config)
#endif
#endif

      /* Initialize CAN Module's private variables */
    Can_lInitGlobalVar();

    /* Initialize clock/timing registers */
    Can_lInitClkSetting();

    /* Check for hardware failure */
    if(E_OK == Can_lInitDemCheck())
    {

      /* Initialize CAN controller status */
      Can_lInitControllerStatus();


      /* Initialize message objects */
      if(E_OK == Can_lInitMsgObj())
      {

        /* Change the driver state to initialized */
        Can_17_MCanP_DriverState = CAN_DS_READY;
      }
    }
  }
}

#if (CAN_DEINIT_API == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_NAS_CAN_PR3027,DS_NAS_CAN_PR3025]         **
**                                                                            **
** Syntax         : void Can_17_MCanP_DeInit(void)                            **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0f                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function De-initializes the CAN Driver.            **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_DeInit (void)
{
 uint32 CLCReadback;
 uint8 ControllerId;
 uint8 HwControllerId;
 uint8 HwCtrlIDKer;
 uint8 BOSrcNum; 
 uint8 RxSrcNum;
 uint8 IntSrcOffset;
 volatile uint8 KerIdx;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
 Std_ReturnType Status;  
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)

 /* Check if CAN driver is initialized */
 Status = Can_lReportDetUninit(CAN_SID_DEINIT);

 if (E_OK == Status)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
 {

  /* Reset the CAN SRC registers for all configured CAN controllers */
  for(ControllerId=CAN_ZERO;
   ControllerId<(Can_kConfigPtr->CanNumController);
   ControllerId++)
  {
   /* check if the CAN controller is activated */
   if(CAN_INVALID_HW_CONTROLLER_ID != 
    Can_kConfigPtr->CanHwControllerIdMap[ControllerId])
   {
    /* Calculate to which kernel, the controller belongs to*/
    HwControllerId = Can_kConfigPtr->CanHwControllerIdMap[ControllerId];
    KerIdx = CAN_CALC_KERIDX(HwControllerId);
    HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);

    /* Calculate the CAN SRC Register Index */
    IntSrcOffset = (KerIdx << CAN_FOUR); 
    BOSrcNum =  (uint8)
     ((uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) << CAN_ONE)
     + (HwCtrlIDKer * CAN_HEDEVICE) + IntSrcOffset);
    RxSrcNum =  (uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) 
     + HwCtrlIDKer + IntSrcOffset);

    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
    PBConfigStructure and is within allowed range.*/
    if (CAN_INTERRUPT == 
     Can_kConfigPtr->CanEventHandlingConfigPtr[ControllerId].CanEventType[2])
    {
     /* Clear interrupt */
     /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
     efficiently access the SFRs */
     CAN_SRC[HwCtrlIDKer + IntSrcOffset].U |= CAN_SRC_CLRR ;
     /* Disable Interrupt */
     /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
     efficiently access the SFRs */
     CAN_SRC[HwCtrlIDKer + IntSrcOffset].U = CAN_ZERO;
    }

    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
    PBConfigStructure and is within allowed range.*/
    if (CAN_INTERRUPT == 
     Can_kConfigPtr->CanEventHandlingConfigPtr[ControllerId].CanEventType[1])
    {
     /* Clear interrupt */
     /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
     efficiently access the SFRs */
     CAN_SRC[RxSrcNum].U |= CAN_SRC_CLRR ;
     /* Disable Interrupt */
     /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
     efficiently access the SFRs */
     CAN_SRC[RxSrcNum].U = CAN_ZERO;
    }

    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
    PBConfigStructure and is within allowed range.*/
    if (CAN_INTERRUPT == 
     Can_kConfigPtr->CanEventHandlingConfigPtr[ControllerId].CanEventType[0])
    {
     /* Clear interrupt */
     /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
     efficiently access the SFRs */
     CAN_SRC[BOSrcNum].U |= CAN_SRC_CLRR ;
     /* Disable Interrupt */
     /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
     efficiently access the SFRs */
     CAN_SRC[BOSrcNum].U = CAN_ZERO;
    }
   }
  }
  /* Initialize CAN Module's private variables */
  Can_lInitGlobalVar();
  /* Disable write-protection of registers with EndInit protection */

  for (KerIdx = CAN_ZERO; KerIdx < CAN_NUM_KERNELS_IN_DEVICE; KerIdx++)
  {

   /* Reset the Kernel registers to default value */
   Can_lResetSFR(KerIdx);

   Mcal_ResetENDINIT();

   /* Disable the CAN hardware unit */
   CAN_KER[KerIdx]->CLC.B.DISR = CAN_ONE;

   /* Read back the CLC register to ensure the CLC register modifications */
   CLCReadback = CAN_KER[KerIdx]->CLC.U;

   /* Enable write-protection of registers with EndInit protection */
   Mcal_SetENDINIT();

   UNUSED_PARAMETER(CLCReadback)

  }

  /* Change the driver state to Uninitialized */
  Can_17_MCanP_DriverState = CAN_DS_UNINIT;
 }

}
#endif

#if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS403_CAN454,DS_AS403_CAN459_CAN460,
DS_AS403_CAN456_CAN457_CAN458]                              **
**                                                                            **
** Syntax           : Std_ReturnType Can_17_MCanP_CheckBaudrate               **
**                          (                                                 **
**                            uint8 Controller,                               **
**                            const uint16 Baudrate                           **
**                          )                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0e                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                    Baudrate -  Baudrate to be checked                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: Baudrate is supported by the CAN Controller     **
**                    - E_NOT_OK: Baudrate is not supported / invalid CAN     **
**                                controller                                  **
**                                                                            **
** Description      : Checks CAN Controller Baudrate                          **
**                                                                            **
*******************************************************************************/
Std_ReturnType Can_17_MCanP_CheckBaudrate(uint8 Controller, 
                                          const uint16 Baudrate)
{
  Std_ReturnType Status;
  uint8 BaudrateCfgIndex;

#if (CAN_DEV_ERROR_DETECT == STD_ON)

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_CHECK_BAUDRATE);

  if(E_OK == Status)
  {
    /* Check if Controller is valid */
    Status = Can_lReportDetParamController(Controller, CAN_SID_CHECK_BAUDRATE);
  }

  if (E_OK == Status)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {  
    /* Check if baudrate is supported/configured */
    BaudrateCfgIndex = Can_lSearchBaudrate(Controller, Baudrate);

    /* check if baudrate is invalid/unsupported */
    if(BaudrateCfgIndex >= Can_kConfigPtr->CanNumBaudrateCfgs[Controller])
    {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
      /* Report invalid baudrate to DET */
      Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
        CAN_SID_CHECK_BAUDRATE, CAN_E_PARAM_BAUDRATE);
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
      Status = E_NOT_OK;
    }
    else
    {
      Status = E_OK;
    }
  }
  return (Status);
}
#endif

#if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS403_CAN449,DS_AS403_CAN422,
DS_AS403_CAN461_CAN450_CAN451_CAN452_CAN453]                **
**                                                                            **
** Syntax           : Std_ReturnType Can_17_MCanP_ChangeBaudrate              **
**                          (                                                 **
**                            uint8 Controller,                               **
**                            const uint16 Baudrate                           **
**                          )                                                 **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x0d                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                    Baudrate -  Baudrate to be checked                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: Baudrate change accepted                        **
**                    - E_NOT_OK: Baudrate is not accepted                    **
**                                                                            **
** Description      : Changes the CAN Controller Baudrate                     **
**                                                                            **
*******************************************************************************/
Std_ReturnType Can_17_MCanP_ChangeBaudrate (uint8 Controller, 
                                            const uint16 Baudrate)
{
  const Can_17_MCanP_ControllerBaudrateConfigType *BaudrateCfgPtr;
  const Can_BaudrateConfigPtrType *CanBaudrateCfgPtr;
  uint8 BaudrateCfgIndex;
  uint8 HwControllerId;
  Std_ReturnType Status;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_CHANGE_BAUDRATE);

  if(E_OK == Status)
  {
    /* Check if Controller is valid */
    Status = Can_lReportDetParamController(Controller, CAN_SID_CHANGE_BAUDRATE);

    /* Controller 'might' be invalid. So shouldn't proceed with checking 
    controller state. So do not check for it's state */
    if (E_OK == Status)
    {  
      /* The CAN controller is not in "stopped" state */
      if (Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_STOPPED)
      {
        /* Report invalid state to DET */
        Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID,
          CAN_SID_CHANGE_BAUDRATE, CAN_E_TRANSITION);
        Status = E_NOT_OK ;
      }
    }
  }

  if (E_OK == Status)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  
  {
    /* Check if baudrate is supported/configured */
    BaudrateCfgIndex = Can_lSearchBaudrate(Controller, Baudrate);

#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* check if baudrate is invalid/unsupported */
    if(BaudrateCfgIndex >= Can_kConfigPtr->CanNumBaudrateCfgs[Controller])
    {
      /* Report invalid baudrate to DET */
      Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
        CAN_SID_CHANGE_BAUDRATE, CAN_E_PARAM_BAUDRATE);
      Status = E_NOT_OK;
    }
    else
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
    {
      Status = E_OK;

#if(CAN_WAKEUP_CONFIGURED == STD_ON)
      /* Check if wakeup was detected */
      if(CAN_ONE == Can_17_MCanP_ControllerWakeupStatus[Controller])
      {
        /* Clear wakeup status and report to EcuM */
        Can_17_MCanP_ControllerWakeupStatus[Controller] = CAN_ZERO;
        /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
        EcuM_SetWakeupEvent((EcuM_WakeupSourceType)
          Can_kConfigPtr->CanWakeupSourceIdPtr[Controller]);
      }
#endif

      HwControllerId = Can_kConfigPtr->CanHwControllerIdMap[Controller];
      CanBaudrateCfgPtr = Can_kConfigPtr->CanBaudrateConfigPtr;
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      CanBaudrateCfgPtr += Controller;
      BaudrateCfgPtr = CanBaudrateCfgPtr->Can_kBaudrateConfigPtr;
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      BaudrateCfgPtr += BaudrateCfgIndex;
      /* Set CAN controller baudrate */
      Can_lSetBaudrate(HwControllerId, BaudrateCfgPtr->CanControllerBaudrate);
    }
  }
  return (Status);
}
#endif

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN230,DS_AS_CAN017,
DS_AS_CAN198_CAN199_CAN200,DS_AS403_CAN370,
DS_NAS_CAN_PR764]                 **
**                                                                            **
** Syntax           : Can_ReturnType Can_17_MCanP_SetControllerMode           **
**                                   (                                        **
**                                     uint8 Controller,                      **
**                                     Can_StateTransitionType Transition     **
**                                   )                                        **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x03                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                    Transition - Requested transition                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : CAN_OK - Valid transition                               **
**                    CAN_NOT_OK - Invalid transition                         **
**                                                                            **
** Description      : Performs software triggered state transitions of the    **
**                    CAN Controller State machine                            **
**                                                                            **
*******************************************************************************/
Can_ReturnType Can_17_MCanP_SetControllerMode(uint8 Controller,
                                             Can_StateTransitionType Transition)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Status;
#endif

  Can_ReturnType RetValue;
  uint8 HwControllerId;

#if (CAN_DEV_ERROR_DETECT == STD_ON)

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_SETCONTROLLERMODE);

  if(E_OK == Status)
  {
    /* Check if Controller is valid */
    Status = Can_lReportDetParamController(Controller, 
      CAN_SID_SETCONTROLLERMODE);
    if(E_OK == Status)
    {
      /* Check if requested state transition is valid */
      Status = Can_lModeDetCheck(Controller, Transition);
      if (E_NOT_OK == Status)
      {
        /* Report invalid transition request to DET */
        Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID,
          CAN_SID_SETCONTROLLERMODE, CAN_E_TRANSITION);
      }
    }
  }
  if (E_NOT_OK == Status)
  {
    RetValue = CAN_NOT_OK;
  }
  else
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    RetValue = CAN_OK;

    HwControllerId = Can_kConfigPtr->CanHwControllerIdMap[Controller];

#if(CAN_WAKEUP_CONFIGURED == STD_ON)
    /* Check if wakeup is enabled */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    if(CAN_ZERO != Can_kConfigPtr->CanWakeupSourceIdPtr[Controller])
    {
      /* perform state transition */
      Can_lSetModeWuSupportOn(Controller,HwControllerId,Transition);
    }
    else
#endif
    {
      /* perform state transition */
      Can_lSetModeWuSupportOff(Controller,HwControllerId,Transition);
    }

    /* Notify successful state transition to upper layer */
    CanIf_ControllerModeIndication(Controller,
      Can_17_MCanP_ControllerMode[Controller]);
  }
  return(RetValue);
}

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN231,DS_AS_CAN205_CAN206]            **
**                                                                            **
** Syntax         : void Can_17_MCanP_DisableControllerInterrupts             **
**                                                         (uint8 Controller) **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x04                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Disables CAN Controller Interrupts                      **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_DisableControllerInterrupts (uint8 Controller)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)

  Std_ReturnType Status;

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_DISABLECONTROLLERINTERRUPTS);

  if(E_OK == Status)
  {
    /* Check if Controller is valid */
    Status = Can_lReportDetParamController(Controller, 
      CAN_SID_DISABLECONTROLLERINTERRUPTS); 
  }

  if (E_OK == Status)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  

  {
    /* Disable controller interrupts */
    Can_lDisableInterrupts(Controller);
  }
}

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN232,DS_AS_CAN209_CAN210]            **
**                                                                            **
** Syntax          : void Can_17_MCanP_EnableControllerInterrupts             **
**                                                         (uint8 Controller) **
**                                                                            **
** [/cover]                                                                   **
**                                                                            **
** Service ID       : 0x05                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Enables CAN Controller Interrupts                       **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_EnableControllerInterrupts (uint8 Controller)
{
#if (CAN_DEV_ERROR_DETECT == STD_ON)

  Std_ReturnType Status;

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_ENABLECONTROLLERINTERRUPTS);

  if(E_OK == Status)
  {
    /* Check if Controller is valid */
    Status = Can_lReportDetParamController(Controller, 
      CAN_SID_ENABLECONTROLLERINTERRUPTS);
  }

  if (E_OK == Status)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  

  {
    /* Enable Controller Interrupts */
    Can_lEnableInterrupts(Controller);
  }
}

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_NAS_CAN_PR765_1,DS_AS_CAN233,
DS_AS_CAN100,DS_AS_CAN216,DS_NAS_HE2_CAN_PR2891,
DS_NAS_EP_CAN_PR2891]                                  **
**                                                                            **
** Syntax           : Can_ReturnType Can_17_MCanP_Write                       **
**                                            (                               **
**                                              Can_HwHandleType Hth,         **
**                                              const Can_PduType *PduInfo    **
**                                            )                               **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x06                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant(thread-safe)                                  **
**                                                                            **
** Parameters (in)  : Hth - Hardware Transmit Handler                         **
**                    PduInfo - Pointer to SDU user memory, DLC and Identifier**
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : CAN_OK - Write command has been accepted                **
**                    CAN_BUSY - No message object available or pre-emptive   **
**                               call of Can_17_MCanP_Write that can't be     **
**                               implemented re-entrant                       **
**                    CAN_NOT_OK - development error occured                  **
**                                                                            **
** Description      : Service to transmit CAN frame                           **
**                                                                            **
*******************************************************************************/
Can_ReturnType Can_17_MCanP_Write (Can_HwHandleType Hth,
                                   const Can_PduType *PduInfo)
{
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  uint8 HwObjectId;
  uint8 HthIndex;
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Status;  
#endif

  Can_ReturnType RetValue;

#if (CAN_DEV_ERROR_DETECT == STD_ON)

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_WRITE);

  if (E_OK == Status)
  {
    /* Check for DET */
    Status = Can_lWriteDetCheck(Hth, PduInfo);
  }
  if (E_NOT_OK == Status)
  {
    RetValue = CAN_NOT_OK;
  }
  else
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)

    /* Extract HTH index for accessing corresponding configuration */
#if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
    HthIndex = (uint8)(Hth - Can_kConfigPtr->CanNumRxHwObj);
#else
    HthIndex = Hth;
#endif /* #if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U) */

    /* Extract message object id */
    /* Update message object with the transmit request */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    HwObjectId = Can_kConfigPtr->CanTxHwObjectConfigPtr[HthIndex].MsgObjId;
    RetValue = Can_lWriteMsgObj(HthIndex, HwObjectId, PduInfo);

#else

    /* If no hardware object is configured for tranmission */
    RetValue = CAN_NOT_OK;

#endif /* #if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U) */
  }  
  return(RetValue);
}


/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS_CAN225,DS_AS_CAN441,
DS_AS_CAN110_CAN431_CAN031_CAN178_CAN179]              **
**                                                                            **
** Syntax           : void Can_17_MCanP_MainFunction_Write(void)              **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x01                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Timing           : Variable Cyclic                                         **
**                                                                            **
** Description      : This function performs the polling of TX confirmation   **
**                    when CAN_TX_PROCESSING is set to POLLING                **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_MainFunction_Write(void)
{
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  uint8 CtrlIndex;
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Status;

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_MAINFUNCTION_WRITE);

  if(E_OK == Status)
#else
  if(CAN_DS_UNINIT != Can_17_MCanP_DriverState)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  
  {
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)

    /* Call transmit handler function for each of the CAN controllers
    configured as POLLING mode for transmission successful event handling */
    for(CtrlIndex=CAN_ZERO;CtrlIndex< (uint8)CAN_NUM_CONTROLLER_MAX;CtrlIndex++)
    {
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      if(CAN_POLLING == 
        Can_kConfigPtr->CanEventHandlingConfigPtr[CtrlIndex].CanEventType[2])
      {
        Can_17_MCanP_IsrTransmitHandler
          (Can_kConfigPtr->CanHwControllerIdMap[CtrlIndex]);
      }
    }

#endif /* #if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U) */
  }
}

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS_CAN226,DS_AS_CAN442,
DS_AS_CAN108_CAN180_CAN181]                            **
**                                                                            **
** Syntax           : void Can_17_MCanP_MainFunction_Read(void)               **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x08                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Timing           : Variable Cyclic                                         **
**                                                                            **
** Description      : This function performs the polling of RX indication     **
**                    when CAN_RX_PROCESSING is set to POLLING                **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_MainFunction_Read(void)
{
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
  uint8 CtrlIndex;
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Status; 

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_MAINFUNCTION_READ);

  if(E_OK == Status)
#else
  if(CAN_DS_UNINIT != Can_17_MCanP_DriverState)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  
  {
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))

    /* Call receive handler function for each of the CAN controllers
    configured as POLLING mode for reception successful event handling */

    for(CtrlIndex=CAN_ZERO;CtrlIndex< (uint8)CAN_NUM_CONTROLLER_MAX;CtrlIndex++)
    {
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      if(CAN_POLLING == 
        Can_kConfigPtr->CanEventHandlingConfigPtr[CtrlIndex].CanEventType[1])
      {
        if(CANIF_CS_STARTED == 
          Can_17_MCanP_ControllerMode[CtrlIndex])
        {
          Can_lReceiveHandler(Can_kConfigPtr->CanHwControllerIdMap[CtrlIndex]);
        }
      }
    }

#endif
    /* #if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U)) */
  }
}

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS_CAN109_CAN183_CAN184,DS_AS_CAN227]**
**                                                                            **
** Syntax           : void Can_17_MCanP_MainFunction_BusOff(void)             **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x09                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Timing           : Variable Cyclic                                         **
**                                                                            **
** Description      : This function performs the polling of bus-off events    **
**                    that are configured statically as 'to be polled'        **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_MainFunction_BusOff(void)
{
  uint8 CtrlIndex;

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Status; 

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_MAINFUNCTION_BUSOFF);

  if(E_OK == Status)
#else
  if(CAN_DS_UNINIT != Can_17_MCanP_DriverState)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  
  {
    /* Call busoff handler function for each of the CAN controllers
    configured as POLLING mode for busoff event handling */
    for(CtrlIndex=CAN_ZERO;CtrlIndex< (uint8)CAN_NUM_CONTROLLER_MAX;CtrlIndex++)
    {
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      if(CAN_POLLING ==
        Can_kConfigPtr->CanEventHandlingConfigPtr[CtrlIndex].CanEventType[0])
      {
        Can_17_MCanP_IsrBusOffHandler
          (Can_kConfigPtr->CanHwControllerIdMap[CtrlIndex]);
      }
    }      
  }
}

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS_CAN228,DS_AS_CAN112_CAN185_CAN186]**
**                                                                            **
** Syntax           : void Can_17_MCanP_MainFunction_Wakeup(void)             **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x0A                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Timing           : Variable Cyclic                                         **
**                                                                            **
** Description      : This function performs the polling of wake-up events    **
**                    that are configured statically as 'to be polled'        **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_MainFunction_Wakeup(void)
{
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
#if(CAN_WAKEUP_CONFIGURED == STD_ON)
  uint8 CtrlIndex;
#endif
#endif

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  Std_ReturnType Status; 

  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_MAINFUNCTION_WAKEUP);

  if(E_OK == Status)
#else
  if(CAN_DS_UNINIT != Can_17_MCanP_DriverState)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */  
  {
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))

    /* Call wakeup handler function for each of the CAN controllers
    configured as POLLING mode for wakeup event handling */
#if(CAN_WAKEUP_CONFIGURED == STD_ON)

    for(CtrlIndex=CAN_ZERO;CtrlIndex< (uint8)CAN_NUM_CONTROLLER_MAX;CtrlIndex++)
    {
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      if(CAN_POLLING ==
        Can_kConfigPtr->
        CanEventHandlingConfigPtr[CtrlIndex].CanEventType[CAN_THREE])
      {
        if(CANIF_CS_SLEEP == 
          Can_17_MCanP_ControllerMode[CtrlIndex])
        {
          Can_lWakeupHandler(Can_kConfigPtr->CanHwControllerIdMap[CtrlIndex]);
        }
      }
    }       
#endif

#endif
    /* #if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U)) */
  }
}

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS403_CAN368,DS_AS_CAN033_CAN035]    **
**                                                                            **
** Syntax           : void Can_17_MCanP_MainFunction_Mode(void)               **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x0C                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Timing           : Variable Cyclic                                         **
**                                                                            **
** Description      : This function performs the polling of CAN Controller    **
**                    mode transitions                                        **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_MainFunction_Mode(void)
{
  /* As all the CAN controller state transitions happens synchronously,
  callback function CanIf_ControllerModeIndication is called in the
  context of the API Can_17_MCanP_SetControllerMode itself. Hence this API
  is implemented as an empty function */
}

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_NAS_CAN_PR765_2,DS_AS403_CAN360,
DS_AS403_CAN361,DS_AS_CAN362_CAN363]                   **
**                                                                            **
** Syntax           : Can_ReturnType Can_17_MCanP_CheckWakeup                 **
**                                                         (uint8 Controller) **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : 0x0B                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : CAN_OK - Wakeup was detected for the given controller   **
**                    CAN_NOT_OK - No wakeup was detected for the given       **
**                                 CAN Controller                             **
**                                                                            **
** Description      : This function checks if a wakeup has occurred for the   **
**                    given CAN Controller                                    **
**                                                                            **
*******************************************************************************/
Can_ReturnType Can_17_MCanP_CheckWakeup(uint8 Controller)
{
#if ((CAN_DEV_ERROR_DETECT == STD_ON) && (CAN_WAKEUP_CONFIGURED == STD_ON))
  Std_ReturnType Status;
#endif
  Can_ReturnType RetValue;

  RetValue = CAN_NOT_OK;

#if(CAN_WAKEUP_CONFIGURED == STD_ON)
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* Check if CAN driver is initialized */
  Status = Can_lReportDetUninit(CAN_SID_CHECKWAKEUP);

  if(E_OK == Status)
  {
    /* Check if Controller is valid */
    Status = Can_lReportDetParamController(Controller, CAN_SID_CHECKWAKEUP);
  }
  if(E_OK == Status)
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Check if wakeup was detected */
    if(CAN_ONE == Can_17_MCanP_ControllerWakeupStatus[Controller])
    {
      /* Clear wakeup status and return CAN_OK */
      Can_17_MCanP_ControllerWakeupStatus[Controller] = CAN_ZERO;
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      EcuM_SetWakeupEvent((EcuM_WakeupSourceType)
        Can_kConfigPtr->CanWakeupSourceIdPtr[Controller]);
      RetValue = CAN_OK;
    }
  }
#else
  UNUSED_PARAMETER (Controller)
#endif /* #if(CAN_WAKEUP_CONFIGURED == STD_ON) */
    return(RetValue);  
}

/*******************************************************************************
**                      Interrupt Service Routines                            **
*******************************************************************************/
/*
The CAN Driver modules implement the interrupt service routines for all 
CAN Hardware Unit interrupts that are needed. 
The module Can_Irq.c contains the implementation of interrupt frames. 
The implementation of the interrupt service routine are in this file.  
*/

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS403_CAN418]                        **
**                                                                            **
** Syntax           : void Can_17_MCanP_IsrReceiveHandler                     **
**                                                     (uint8 HwControllerId) **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwControllerId - Associated CAN Controller              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : - This is the interrupt service routine for Receive     **
**                    Interrupt                                               **
**                    - This function checks the CAN Controller status and    **
**                    calls appropriate handler function                      **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_IsrReceiveHandler(uint8 HwControllerId)
{
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))

  /* In STARTED state, upon message reception call receive handler function */
  if(CANIF_CS_STARTED == 
    Can_17_MCanP_ControllerMode[Can_NodeIdMap[HwControllerId]])
  {
    Can_lReceiveHandler(HwControllerId);
  }

#if(CAN_WAKEUP_CONFIGURED == STD_ON)
  /* In SLEEP state, upon message reception call wakeup handler function */
  if(CANIF_CS_SLEEP == 
    Can_17_MCanP_ControllerMode[Can_NodeIdMap[HwControllerId]])
  {
    Can_lWakeupHandler(HwControllerId);
  }
#endif

#else
  UNUSED_PARAMETER (HwControllerId)
#endif
    /* #if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U)) */
}

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN016]                                **
**                                                                            **
** Syntax           : void Can_17_MCanP_IsrTransmitHandler                    **
**                                                     (uint8 HwControllerId) **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwControllerId - Associated CAN Controller              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : - This is the interrupt service routine for Transmit    **
**                    Interrupt                                               **
**                    - In case of successful transmission event, this        **
**                    funciton notifies the upper layer                       **
**                    - This function is also called by the polling function  **
**                    Can_17_MCanP_MainFunction_Write for controllers         **
**                    configured with CanTxProcessing as POLLING              **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_IsrTransmitHandler(uint8 HwControllerId)
{
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  volatile uint32 MsiMaskCopy;
  uint8 HwObjectId;
  uint8 PndBitPosition;
  uint8 MsgIndex;
  uint8 LoopBreak;
  uint8 KerIdx;
  uint8 TxMOIdx;

  /* Calculate to which kernel the Controller belongs to */
  KerIdx = CAN_CALC_KERIDX(HwControllerId);

  /* Save current MSIMASK - which needs to be restored back at the end */
  /* to avoid re-entrancy issue */
  MsiMaskCopy = CAN_KER[KerIdx]->MSIMASK.U;
  LoopBreak = CAN_ZERO;

  /* Loop through all the MSPND registers configured for transmit MOs */
  for (MsgIndex = Can_kConfigPtr->CanTxFirstMspndIdx;
    MsgIndex <= Can_kConfigPtr->CanTxLastMspndIdx;
    MsgIndex++)
  {
    /* Load MSIMASK corresponding to the controller */
    CAN_KER[KerIdx]->MSIMASK.U = Can_TxMsiMask[HwControllerId][MsgIndex];

    /* Check for any pending notification */
    /* To avoid infinite loop in case of hardware error, LoopBreak is used
    with worst case of 32 iterations to process 32 message objects pointed 
    by the given MSIMASK */
    while ((CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX != 
      CAN_MSID_NO_MSG_PND_VALUE) && (LoopBreak < CAN_THIRTY_TWO))
    {
      /* Count the iterations */
      LoopBreak++;

      /* Get the pending bit position */
      PndBitPosition = (uint8)CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX;

      /* Calculate the message object id */
      HwObjectId =  PndBitPosition + 
        (uint8)((MsgIndex) << CAN_MOIPR_MPN_MSPND_SHIFT );

      TxMOIdx = HwObjectId-(Can_kConfigPtr->CanTxHwObjCntKer[KerIdx]);

#if (CAN_FD_ENABLE== STD_ON)
      /* Intention is to divide the TxMOIdx by 3 (CAN_MOSize).
       It is achieved by the expression Q = ((VAL * 0xAB) >> 8) >> 1 */
      TxMOIdx = 
      (uint8)(((uint16)TxMOIdx * (uint16)CAN_8BITDIV3FACTOR) >> CAN_NINE);
#endif

      /* Clear NEWDAT and TXPND */
      CAN_KER[KerIdx]->MO[HwObjectId].CTR.U =
        (CAN_MOCTR_NEWDAT_CLR | CAN_MOCTR_TXPND_CLR);

      /* Clear MSPND bit */
      CAN_KER[KerIdx]->MSPND[MsgIndex].U = 
        ~((unsigned_int)CAN_ONE << PndBitPosition);

      /* Call notification function indicating successful transmission */
      CanIf_TxConfirmation((PduIdType)Can_SwObjectHandle[KerIdx][TxMOIdx]);

    }
  }

  /* Restore the MSIMASK value */
  CAN_KER[KerIdx]->MSIMASK.U  = MsiMaskCopy;
#else
  UNUSED_PARAMETER (HwControllerId)
#endif /* #if (CAN_TX_HARDWARE_OBJECTS_MAX > 0) */
}


/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS_CAN020_CAN272_CAN274]             **
**                                                                            **
** Syntax           : void Can_17_MCanP_IsrBusOffHandler(uint8 HwControllerId)**
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwControllerId - Associated CAN Controller              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : - This function is the core part of the interrupt       **
**                    service routine for handling and reporting bus-off event**
**                    - This function is also called by the polling function  **
**                    Can_17_MCanP_MainFunction_BusOff for controllers        **
**                    configured with CanBusoffProcessing as POLLING          **
**                                                                            **
*******************************************************************************/
void Can_17_MCanP_IsrBusOffHandler(uint8 HwControllerId)
{
  uint8 BoffStatus;
  uint8 ControllerId;
  uint8 KerIdx;
  uint8 HwCtrlIDKer;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);
  HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);
  /*
  Bus-off error check:
  ---------------------
  The ALERT bit is set upon the occurrence of one of the following events
  (the same events which also trigger an alert interrupt if ALIE is set):
  1. A change of bit NSRx.BOFF
  2. A change of bit NSRx.EWRN
  3. A List Length Error, which also sets bit NSRx.LLE
  4. A List Object Error, which also sets bit NSRx.LOE
  5. Bit INIT has been set by hardware

  Note: 
  - List error occurance is ruled out because list is not changed at run 
  time by the driver. So LOE and LLE bits need not be checked.

  - Points 1,2 and 5 constitute BusOff condition
  In the driver EWRN level is set to be equal to BOFF error level. 
  So when EWRN triggers ALERT bit, it also means bus-off.
  When bus-off happens, INIT is set by "hardware".

  So is it enough to check ALERT bit alone to see if there was bus-off 
  event triggered? No. Resetting of EWRN and/or BOFF also triggers 
  ALERT bit to be set. To differentiate this scenario, both ALERT 
  and INIT bit should be checked.
  */

  /* Extract the INIT bit status of the controller */
  BoffStatus = (uint8)CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT;

  /* Controller moved to bus-off state */
  if (((CAN_KER[KerIdx]->N[HwCtrlIDKer].SR.U & CAN_NSR_ALERT) == CAN_NSR_ALERT )
    && (BoffStatus == CAN_ONE))   
  {
    /* Reset ALERT bit */       
    CAN_KER[KerIdx]->N[HwCtrlIDKer].SR.U = 
      (~((uint32)CAN_NSR_ALERT)) & CAN_NSR_WRITABLE_VALUE_MASK ;

    /* Extract corresponding CanControllerId */
    ControllerId = Can_NodeIdMap[HwControllerId];

    /* Avoid un-intended bus-off notification */
    /* Notify busoff only if it occured in STARTED state of the controller */
    if(CANIF_CS_STARTED == Can_17_MCanP_ControllerMode[ControllerId])
    {
      /* Set current controller state to STOPPED */
      Can_17_MCanP_ControllerMode[ControllerId] = CANIF_CS_STOPPED ;

      /* Notify the bus-off event to upper layer */
      CanIf_ControllerBusOff(ControllerId);
    }

  }
}

/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/

/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE void Can_lInitGlobalVar(void)          **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Initializes global variables of CAN driver              **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lInitGlobalVar(void)
{
  uint16 Index;
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
  uint8 HwIndex;
#endif
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  volatile uint8 KerIdx;
#endif
  uint8 MspndIndex;

  /* Clear interrupt status and disable count */
  for (Index = CAN_ZERO; Index < (Can_kConfigPtr->CanNumController); Index++)
  {
    Can_17_MCanP_InterruptDisableCount[Index] = CAN_ZERO;
    Can_InterruptsEnabledStatus[Index] = CAN_ZERO;
    /* Initialize the CAN controller status to Uninitialised state */
    Can_17_MCanP_ControllerMode[Index] = CANIF_CS_UNINIT;
  
#if (CAN_WAKEUP_CONFIGURED == STD_ON)
    /* Clear wakeup status flag */
    Can_17_MCanP_ControllerWakeupStatus[Index] = CAN_ZERO;
#endif

  }

#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  /* Clear software pdu handle array */
  for (KerIdx = CAN_ZERO; KerIdx < CAN_NUM_KERNELS_IN_DEVICE; KerIdx++)
  {
    for (Index = CAN_ZERO; Index < CAN_TX_HARDWARE_OBJECTS_MAX; Index++)
    {
      Can_SwObjectHandle[KerIdx][Index] = CAN_ZERO; 
    }
  }
#endif /* #if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U) */

  for (Index = CAN_ZERO; Index < CAN_NUM_CONTROLLERS_IN_DEVICE; Index++)
  {
    /* Initialize controllelr mapping array to Invalid Controller Id */
    Can_NodeIdMap[Index] = CAN_INVALID_HW_CONTROLLER_ID;

    /* Initialize MSIMASK arrays */
    for (MspndIndex = CAN_ZERO; MspndIndex < CAN_NUM_MSPND_REGS; MspndIndex++)
    {
      Can_TxMsiMask[Index][MspndIndex]=(uint32)CAN_ZERO;
      Can_RxMsiMask[Index][MspndIndex]=(uint32)CAN_ZERO;
    }
  }

#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
  for (HwIndex = CAN_ZERO; HwIndex < CAN_NUM_CONTROLLERS_IN_DEVICE; HwIndex++)
  {
    for (Index = CAN_ZERO; Index < CAN_RXSize; Index++)
    {
      Can_RxMessageData[HwIndex][Index] = CAN_ZERO ;
    }
  }
#endif

#if (CAN_NUM_RX_FIFO_MAX > 0U)
  for (HwIndex = CAN_ZERO; HwIndex < CAN_NUM_CONTROLLERS_IN_DEVICE; HwIndex++)
  {
    for (Index = CAN_ZERO; Index < CAN_EIGHT; Index++)
    {
      Can_RxFifoMessageData[HwIndex][Index] = CAN_ZERO ;
    }
  }
#endif
}

/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE void Can_lInitClkSetting(void)         **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Initializes clock control register, fractional divider  **
**                    register and module control register                    **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lInitClkSetting(void)
{
  volatile uint32 ReadBack; /* For readback of CLC register */
  volatile uint8 KerIdx;
  ReadBack = CAN_ZERO;

  for (KerIdx = CAN_ZERO; KerIdx < CAN_NUM_KERNELS_IN_DEVICE; KerIdx++)
  {

    /* Disable write-protection of registers with EndInit protection */
    Mcal_ResetENDINIT();

    /* Enable the CAN hardware unit */
    CAN_KER[KerIdx]->CLC.B.DISR = CAN_ZERO;

    /* Read back the CLC register to ensure the CLC register modifications */
    ReadBack = CAN_KER[KerIdx]->CLC.U;

    /* Enable/Disable sleep mode based on the need for wakeup detection */
#if(CAN_WAKEUP_CONFIGURED == STD_ON)
    /* MultiCAN+ Module should be able to receive frames to detect wakeup */
    CAN_KER[KerIdx]->CLC.B.EDIS = CAN_ONE;
    /* Read back the CLC register to ensure the CLC register modifications */
    ReadBack = CAN_KER[KerIdx]->CLC.U;
#endif
    /* Enable write-protection of registers with EndInit protection */
    Mcal_SetENDINIT();

#if (CAN_RESET_SFR_AT_INIT == STD_ON)
    /* Reset the Kernel registers to default value */
    Can_lResetSFR(KerIdx);
#endif

    /* Select fASYN_CAN or fERAY as the input source */
    CAN_KER[KerIdx]->MCR.B.CLKSEL = CAN_MCR_CLKSEL;

    /* Disable write-protection of registers with EndInit protection */
    Mcal_ResetENDINIT();

    /* Setup CAN module timer clock */ 
    /* CAN_CLC should be written before writing to CAN_FDR */
    CAN_KER[KerIdx]->FDR.U = (uint32)Can_kConfigPtr->CanFdrSetting ;

    /* Enable write-protection of registers with EndInit protection */
    Mcal_SetENDINIT();

  }


  UNUSED_PARAMETER(ReadBack)
}

#if ((CAN_RESET_SFR_AT_INIT == STD_ON)||(CAN_DEINIT_API == STD_ON))
/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE void Can_lResetSFR(uint8 KerIdx)       **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : uint8 KerIdx                                            **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Initializes the Kernel registers to default value       **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lResetSFR(uint8 KerIdx)
{
  volatile uint32 ReadBack; /* Readback of KRST register */
  uint32 TimeOutVal; /* Time out value for Kernel Reset to happen */
  uint32 KerRstStat; /* Kernel Reset Status */
  ReadBack = CAN_ZERO;

    /* Disable write-protection of registers with EndInit protection */
    Mcal_ResetENDINIT();

    /* Request a Kernel Reset */
    CAN_KER[KerIdx]->KRST0.B.RST = CAN_ONE;

    /* Read back to ensure the KRST0 register modifications */
    ReadBack = CAN_KER[KerIdx]->KRST0.U;

    /* Request a Kernel Reset */
    CAN_KER[KerIdx]->KRST1.B.RST = CAN_ONE;

    /* Read back to ensure the KRST1 register modifications */
    ReadBack = CAN_KER[KerIdx]->KRST1.U;

    /* Enable write-protection of registers with EndInit protection */
    Mcal_SetENDINIT();

    /* Time out value for Kernel Reset is loaded */
    TimeOutVal = CAN_KERNEL_RESET_TIMEOUT;
    do
    {
      TimeOutVal--;
#ifdef IFX_CAN_DEBUG04
      KerRstStat = TestCan_DebugMask04;
#else
      KerRstStat = CAN_KER[KerIdx]->KRST0.B.RSTSTAT;
#endif
    }  
    while ((KerRstStat == CAN_ZERO) && (TimeOutVal > CAN_ZERO));

    /* Disable write-protection of registers with EndInit protection */
    Mcal_ResetENDINIT();
    /* Clear the Kernel Reset Status */
    CAN_KER[KerIdx]->KRSTCLR.B.CLR = CAN_ONE;
    /* Read back to ensure the KRSCLR register modifications */
    ReadBack = CAN_KER[KerIdx]->KRSTCLR.U;

    /* Enable write-protection of registers with EndInit protection */
    Mcal_SetENDINIT();
 

  UNUSED_PARAMETER(ReadBack)
}
#endif
/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_AS_CAN176,DS_AS403_CAN371_CAN281,
DS_AS_CAN029_CAN092_CAN295_CAN296_CAN297,DS_AS_CAN084,
DS_NAS_CAN_PR919]                                      **
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Can_lInitDemCheck(void) **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: CAN RAM initialization completed before timeout **
**                    - E_NOT_OK: CAN RAM initialization did not complete     **
**                                before timeout                              **
**                                                                            **
** Description      : Checks for completion of CAN RAM initialization.        **
**                    In case of hardware failure, reports to DEM.            **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Std_ReturnType Can_lInitDemCheck(void)
{
  uint32 TimeOutIndex;
  Std_ReturnType RetVal;
  volatile uint8 KerIdx;

  RetVal = E_OK;

  for (KerIdx = CAN_ZERO; KerIdx < CAN_NUM_KERNELS_IN_DEVICE; KerIdx++)
  {

    /* The CAN RAM is automatically initialized after reset by the list 
    controller in order to ensure correct list pointers in each message object.
    End of the CAN RAM initialization is indicated by bit PANCTR.BUSY 
    becoming inactive */
    TimeOutIndex = CAN_TIMEOUT_DURATION;

#ifdef IFX_CAN_DEBUG01
    while (((CAN_KER[KerIdx]->PANCTR.B.BUSY | TestCan_DebugMask01) == CAN_ONE)
      && (TimeOutIndex != CAN_ZERO))
#else
    while ((CAN_KER[KerIdx]->PANCTR.B.BUSY == CAN_ONE) && 
      (TimeOutIndex != CAN_ZERO))
#endif
    {
      TimeOutIndex--;
    }
    if (TimeOutIndex == CAN_ZERO)
    {
      /* The detection of production code errors cannot be switched off. 
      This requirement will be violated as per HIS requirements */

      /* Report hardware errors and failures to DEM */
#if (CAN_E_TIMEOUT_DEM_REPORT == CAN_ENABLE_DEM_REPORT)
      Dem_ReportErrorStatus((Dem_EventIdType)CAN_E_TIMEOUT, 
        DEM_EVENT_STATUS_FAILED);
#endif

      RetVal = E_NOT_OK;
    }
  }

  return(RetVal);
}

/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE void Can_lInitializeController         **
**                                             (                              **
**                                               uint8 ControllerId,          **
**                                               uint8 HwControllerId         **
**                                             )                              **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : ControllerId - CAN Controller Id as per configuration   **
**                    HwControllerId - Corresponding CAN Controller Id in     **
**                                     hardware                               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Initializes CAN Controller Registers and Enables CAN    **
**                    Controller Interrupts                                   **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lInitializeController(uint8 ControllerId, 
                                            uint8 HwControllerId)
{
  uint8 KerIdx;
  uint8 HwCtrlIDKer;
  uint8 BOSrcNum; 
  uint8 RxSrcNum;
  uint8 IntSrcOffset;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);
  HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);
  IntSrcOffset = (KerIdx << CAN_FOUR); 
  BOSrcNum =  (uint8)
    ((uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) << CAN_ONE)
    + (HwCtrlIDKer * CAN_HEDEVICE) + IntSrcOffset);
  RxSrcNum =  (uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) 
    + HwCtrlIDKer + IntSrcOffset);

  /* 
  - Enable Configuration Change - NBTR, NPCR, NECNT can be written
  - Take controller out of CAN traffic i.e put it in "stopped" state 
  - Enable Alert Interrupt. Used to detect bus off 
  */ 
  CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.U |= ( CAN_NCR_INIT | CAN_NCR_ALIE | 
    CAN_NCR_CCE );  

#if (CAN_FD_ENABLE== STD_ON)

  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  if(NULL_PTR != 
    Can_kConfigPtr->CanFDConfigParamPtr[ControllerId].Can_kFDConfigParamPtr)
  {
    CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.FDEN = CAN_ONE; 

    /* Set Fast Node Bit Timing value */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    CAN_KER[KerIdx]->N[HwCtrlIDKer].FBTR.U = 
      Can_kConfigPtr->CanFDConfigParamPtr[ControllerId].
      Can_kFDConfigParamPtr->CanControllerFDBaudrate;

    /* Set Transceiver Delay Compensation Offset values */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    CAN_KER[KerIdx]->N[HwCtrlIDKer].TDCR.U = 
      Can_kConfigPtr->CanFDConfigParamPtr[ControllerId].
      Can_kFDConfigParamPtr->CanControllerTxDelayComp;
  }

#endif

  /* Loopback and receive input pin selection setting */  
  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  CAN_KER[KerIdx]->N[HwCtrlIDKer].PCR.U = 
    (uint32)Can_kConfigPtr->CanNpcrPtr[ControllerId].Can_NPCRValue;

  /* Assign alert interrupt (for bus-off indication) to an SRN */
  CAN_KER[KerIdx]->N[HwCtrlIDKer].IPR.B.ALINP = BOSrcNum; 

  /* Set error warning limit to 255 so that no warning interrupt is generated
  Only bus-off error is of interest */
  CAN_KER[KerIdx]->N[HwCtrlIDKer].ECNT.B.EWRNLVL = CAN_BUSOFF_LIMIT ;

  /* Disable Configuration Change - NBTR, NPCR, NECNT can only be read */
  CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.CCE = CAN_ZERO; 


  /* For hardware controller Id, map the corresponding CanControllerId */
  Can_NodeIdMap[HwControllerId]=ControllerId;


  /* Initialize default controller baudrate */   
  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  Can_lSetBaudrate(HwControllerId, Can_kConfigPtr->
    CanDefaultBaudrateConfigPtr[ControllerId].CanControllerBaudrate);

  /* Enable the CAN controller interrupts */
  /* Refer section "Service Request Node Allocation/Mapping" for SRN mapping */

  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  if (CAN_INTERRUPT == 
    Can_kConfigPtr->CanEventHandlingConfigPtr[ControllerId].CanEventType[2])
  {
    Can_lClearAndEnableInterrupt((uint8)(HwCtrlIDKer + IntSrcOffset));
  }

  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  if (CAN_INTERRUPT == 
    Can_kConfigPtr->CanEventHandlingConfigPtr[ControllerId].CanEventType[1])
  {
    Can_lClearAndEnableInterrupt((uint8)RxSrcNum);
  }

  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  if (CAN_INTERRUPT == 
    Can_kConfigPtr->CanEventHandlingConfigPtr[ControllerId].CanEventType[0])
  {
    Can_lClearAndEnableInterrupt((uint8)BOSrcNum);
  }


}

/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Can_lInitMsgObj(void)   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: Message object allocation successful            **
**                    - E_NOT_OK: Message object allocation failed            **
**                                                                            **
** Description      : Calls local functions to initialize transmit, receive   **
**                    and FIFO message objects                                **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Std_ReturnType Can_lInitMsgObj(void)
{
  Std_ReturnType RetVal;

#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  /* Initialize transmit message objects */
  RetVal = Can_lInitTxMsgObj();
  if(E_OK == RetVal)
#endif
  {
#if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
    /* Initialize receive message objects */
    RetVal = Can_lInitRxMsgObj();
    if(E_OK == RetVal)
#endif
    {
#if (CAN_NUM_RX_FIFO_MAX > 0U)
      /* Initialize the Rx FIFO message objects */
      RetVal = Can_lRxFifoInit();
#endif 
    }
  }  
  return(RetVal);
}

#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Can_lInitTxMsgObj(void) **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: Message object allocation successful            **
**                    - E_NOT_OK: Message object allocation failed            **
**                                                                            **
** Description      : Initializes transmit message objects                    **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Std_ReturnType Can_lInitTxMsgObj(void)
{
  const Can_TxHwObjectConfigType *TxHwObjCfgPtr;
  uint16 HwObjIndex;
  uint8 HwObjectId;
  uint8 HwControllerId;
  uint8 KerIdx;
  Std_ReturnType RetVal;
#if (CAN_FD_ENABLE== STD_ON)
  uint8 HwCtrlIDKer;
#endif

  TxHwObjCfgPtr = Can_kConfigPtr->CanTxHwObjectConfigPtr;
  RetVal = E_OK;

  /* Loop through all the transmit hardware object configurations */
  for ( 
    HwObjIndex=CAN_ZERO;
    (HwObjIndex < Can_kConfigPtr->CanNumTxHwObj)&&(E_OK==RetVal); 
  HwObjIndex++
    )
  {
    /* Extract HwControllerId from the configuration */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    HwControllerId = TxHwObjCfgPtr[HwObjIndex].HwControllerId;
    /* Calculate to which kernel, the controller belongs to*/
    KerIdx = CAN_CALC_KERIDX(HwControllerId);

#if (CAN_FD_ENABLE== STD_ON)
    HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);
#endif


    /* only if associated controller is activated */
    if(CAN_INVALID_HW_CONTROLLER_ID != HwControllerId)
    {
#if (CAN_MULTIPLEXED_TRANSMISSION == STD_OFF)
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      HwObjectId = TxHwObjCfgPtr[HwObjIndex].MsgObjId;
#else
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      for(HwObjectId = TxHwObjCfgPtr[HwObjIndex].MsgObjId;
        (HwObjectId <= TxHwObjCfgPtr[HwObjIndex].MsgObjIdLast)&&(E_OK==RetVal);
        HwObjectId+=CAN_MOSize)
#endif
      {
#ifdef IFX_CAN_DEBUG02
        TestCan_SetMOAllocationErrorType(TESTCAN_TX_MO_ERROR);
#endif

        /* allocate message object to the associated controller */
        RetVal = Can_lAllocateHwObject(HwControllerId, HwObjectId);

        if(E_OK == RetVal)
        {

#if (CAN_FD_ENABLE== STD_ON)

          if(CAN_ONE == 
            CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.FDEN)
          {
            /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
            if(CAN_ONE == 
              Can_kConfigPtr->
              CanFDConfigParamPtr[Can_NodeIdMap[HwControllerId]].
              Can_kFDConfigParamPtr->CanControllerTxBRS)
            {
              CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.BRS = CAN_ONE;
            }

            /* In order to support higher than 8 data bytes payload 
            (e.g 64bytes data payload),
             CAN FD 64 bytes message mode is selected */

            CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.MMC = 
              CAN_FD64BYTES_MOFCR_MMC_BIT;

            /* When CAN FD 64 bytes message mode is selected, additional 
            message objects would be used to store the extra data bytes. 
            The additional message objects used are specified by the pointer 
            on MOFGPR.BOT and MOFGPR.TOP register bits */

            /* The additional message objects chosen to store the extra data 
            bytes must not take part in CAN communication i.e they are allocated
            to a list that does not belong to an active CAN node */

            CAN_KER[KerIdx]->MO[HwObjectId].FGPR.B.BOT =
              ((uint16)HwObjectId +  (uint16)CAN_ONE);
            CAN_KER[KerIdx]->MO[HwObjectId].FGPR.B.TOP =
              ((uint16)HwObjectId +  (uint16)CAN_TWO);

          }

#endif
          /* Set message pending number field (MPN) */    
          CAN_KER[KerIdx]->MO[HwObjectId].IPR.B.MPN = HwObjectId;

          /* Set the corresponding bit in MSIMASK array */
          Can_TxMsiMask[HwControllerId][(HwObjectId >> CAN_POS_5)] |=
            ((uint32)1 << (HwObjectId & CAN_MAX_HWOBJ_PER_MSPND_REG_1));

          /* Set interrupt service node */
          CAN_KER[KerIdx]->MO[HwObjectId].IPR.B.TXINP = (uint8)
            CAN_CALC_HWCTRLID(HwControllerId);

          /* Enable transmit interrupt */
          CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.TXIE = CAN_ONE ;

          /* Set message priority class */
          /* (for acceptance filtering based on CAN identifier) */
          CAN_KER[KerIdx]->MO[HwObjectId].AR.B.PRI = CAN_PRI_CLASS_ID_BASED;

          /* - Enable hardware object 
          - Set the direction of hardware object to transmit. 
          - FIFO not used. So set TXEN1 bit permanently. 
          */
          CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = ~((uint32)
            (CAN_MOCTR_DIR_CLR | 
            CAN_MOCTR_TXEN1_CLR |
            CAN_MOCTR_MSGVAL_CLR));
        }
      }
    }
  }
  return (RetVal);
}
#endif

#if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN236_CAN237]                         **
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Can_lInitRxMsgObj(void) **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: Message object allocation successful            **
**                    - E_NOT_OK: Message object allocation failed            **
**                                                                            **
** Description      : Initializes receive message objects                     **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Std_ReturnType Can_lInitRxMsgObj(void)
{
  const Can_RxHwObjectConfigType *RxHwObjCfgPtr;
  uint16 HwObjIndex;
  uint8 HwObjectId;
  uint8 HwControllerId;
  uint8 KerIdx;
  Std_ReturnType RetVal;
#if (CAN_FD_ENABLE== STD_ON)
  uint8 HwCtrlIDKer;
#endif

  RetVal = E_OK;
  RxHwObjCfgPtr = Can_kConfigPtr->CanRxHwObjectConfigPtr;

  /* Loop through all the receive hardware object configurations */
  for (HwObjIndex = CAN_ZERO; 
    (HwObjIndex < Can_kConfigPtr->CanNumRxHwObj)&&(E_OK==RetVal); 
    HwObjIndex++)
  {
    /* extract associated controller from the configuration */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    HwControllerId = RxHwObjCfgPtr[HwObjIndex].HwControllerId;
    /* Calculate to which kernel, the controller belongs to*/
    KerIdx = CAN_CALC_KERIDX(HwControllerId);
#if (CAN_FD_ENABLE== STD_ON)
    HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);
#endif

    /* only if the associated ocntroller is activated */
    if(CAN_INVALID_HW_CONTROLLER_ID != HwControllerId)
    {
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      HwObjectId = RxHwObjCfgPtr[HwObjIndex].MsgObjId;
#ifdef IFX_CAN_DEBUG02
      TestCan_SetMOAllocationErrorType(TESTCAN_RX_MO_ERROR);
#endif

      /* allocate the message object to the associated controller */
      RetVal = Can_lAllocateHwObject(HwControllerId, HwObjectId);

      /* Allocate hardware object from list */
      if(E_OK == RetVal)
      {

#if (CAN_FD_ENABLE== STD_ON)

        if(CAN_ONE == 
          CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.FDEN)
        {
          CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.FDF = CAN_ONE;
          CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.BRS = CAN_ONE;
        }

        /* In order to support higher than 8 data bytes payload 
        (e.g 64bytes data payload), CAN FD 64 bytes message mode is selected */

        CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.MMC = 
          CAN_FD64BYTES_MOFCR_MMC_BIT;

        /* When CAN FD 64 bytes message mode is selected, additional 
        message objects would be used to store the extra data bytes. 
        The additional message objects used are specified by the pointer 
        on MOFGPR.BOT and MOFGPR.TOP register bits */

        /* The additional message objects chosen to store the extra data bytes 
        must not take part in CAN communication i.e they are allocated 
        to a list that does not belong to an active CAN node */

        CAN_KER[KerIdx]->MO[HwObjectId].FGPR.B.BOT = 
          ((uint16)HwObjectId +  (uint16)CAN_ONE);
        CAN_KER[KerIdx]->MO[HwObjectId].FGPR.B.TOP = 
          ((uint16)HwObjectId +  (uint16)CAN_TWO);

#endif


        /* Set message pending number field (MPN) */    
        CAN_KER[KerIdx]->MO[HwObjectId].IPR.B.MPN = HwObjectId;

#if (CAN_STANDARD_ID_ONLY == STD_OFF)
        /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
        if (RxHwObjCfgPtr[HwObjIndex].FrameType != CAN_ID_STANDARD)
        {
          /* Set ID value, ID type and message priority class (to acceptance 
          filtering based on CAN identifier) */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
          CAN_KER[KerIdx]->MO[HwObjectId].AR.U = (unsigned_int)
            (CAN_PRIORITY_ID_BASED | 
            CAN_USE_EXTENDED_ID | (RxHwObjCfgPtr[HwObjIndex].MsgId));

          /* Set filter mask value */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
          CAN_KER[KerIdx]->MO[HwObjectId].AMR.B.AM = 
            RxHwObjCfgPtr[HwObjIndex].MaskRef;

          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
          if (RxHwObjCfgPtr[HwObjIndex].FrameType == CAN_ID_MIXED)
          {
            /* Receive both standard and extended IDs */
            CAN_KER[KerIdx]->MO[HwObjectId].AMR.B.MIDE = CAN_ZERO ;
          }
        }
        else
#endif /* #if (CAN_STANDARD_ID_ONLY == STD_OFF) */
        {
          /* Set ID value, ID type and message priority class (to acceptance 
          filtering based on CAN identifier) */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
          CAN_KER[KerIdx]->MO[HwObjectId].AR.U = (unsigned_int)
            (CAN_PRIORITY_ID_BASED | 
            ((uint32)RxHwObjCfgPtr[HwObjIndex].MsgId << 
            CAN_MOAR_ID_STD_SHIFT));

          /* Set filter mask value */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
          CAN_KER[KerIdx]->MO[HwObjectId].AMR.B.AM = (unsigned_int)
            (RxHwObjCfgPtr[HwObjIndex].MaskRef << CAN_POS_18);
        }
        /* Set interrupt service node */
        CAN_KER[KerIdx]->MO[HwObjectId].IPR.B.RXINP = 
          (CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) + 
          (CAN_CALC_HWCTRLID(HwControllerId));

        /* Enable receive interrupt for this hardware object */ 
        CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.RXIE = CAN_ONE ;

        /*  Set the direction of hardware object to Receive. */
        CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = CAN_MOCTR_DIR_CLR ;

        /* Set the corresponding bit in MSIMASK array */
        Can_RxMsiMask[HwControllerId][(HwObjectId >> CAN_POS_5)] |=
          ((uint32)1 << (HwObjectId & CAN_MAX_HWOBJ_PER_MSPND_REG_1));

        /* Enable hardware object */
        CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = ~((uint32)
          (CAN_MOCTR_RXEN_CLR
          | CAN_MOCTR_MSGVAL_CLR));
      }
    }   
  } 
  return (RetVal);  
}
#endif

#if (CAN_NUM_RX_FIFO_MAX > 0U)
/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Can_lRxFifoInit(void)   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: Message object allocation successful            **
**                    - E_NOT_OK: Message object allocation failed            **
**                                                                            **
** Description      : Initializes receive FIFO structure                      **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Std_ReturnType Can_lRxFifoInit(void)
{
  const Can_RxFifoConfigType *RxFifoCfgPtr ;
  uint16 FifoIndex;
  uint8 HwObjectId;  
  uint8 HwControllerId;
  uint8 KerIdx;
  uint8 FifoThreshold;
  uint8 FifoSize;
  uint8 FifoTop;  
  uint8 SlaveIndex;
  uint8 FifoBottom;
  Std_ReturnType RetVal;

  RetVal = E_OK;

  /* Copy receive FIFO configuration pointer */
  RxFifoCfgPtr = Can_kConfigPtr->RxFifoConfigPtr ;

  /* configure all Receive FIFO Haraware objects */
  for (FifoIndex = CAN_ZERO; 
    (FifoIndex < Can_kConfigPtr->CanNumRxFifo)&&(E_OK==RetVal);
    FifoIndex++)
  {
    /* Extract associated CAN controller Id */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    HwControllerId = RxFifoCfgPtr[FifoIndex].HwControllerId;
    /* Calculate to which kernel, the controller belongs to*/
    KerIdx = CAN_CALC_KERIDX(HwControllerId);

    /* Check if associated CAN controller is activated */
    if(CAN_INVALID_HW_CONTROLLER_ID != HwControllerId)
    {
      /* Extract message object mapped for FIFO base object */
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      HwObjectId = RxFifoCfgPtr[FifoIndex].HwObjectId;

#ifdef IFX_CAN_DEBUG02
      TestCan_SetMOAllocationErrorType(TESTCAN_RXFIFO_BASE_MO_ERROR);
#endif

      /* Allocate the message object to assocaited controller */
      RetVal = Can_lAllocateHwObject(HwControllerId, HwObjectId);

      if(E_OK == RetVal)
      {
        /* Set MSIMASK bit corresponding to the message object */
        Can_RxMsiMask[HwControllerId][(HwObjectId >> CAN_POS_5)] |=
          ((uint32)1 << (HwObjectId & CAN_MAX_HWOBJ_PER_MSPND_REG_1));

        /* Initialize receive FIFO base message object */
#if (CAN_STANDARD_ID_ONLY == STD_OFF)       
        /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
        Can_lRxFifoBaseMOInit(RxFifoCfgPtr, FifoIndex, 
          RxFifoCfgPtr[FifoIndex].FrameType);
#else
        Can_lRxFifoBaseMOInit(RxFifoCfgPtr, FifoIndex);
#endif

        /* Calculate Threshold, TOP and BOT values based on configuration */
        /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
        FifoThreshold = RxFifoCfgPtr[FifoIndex].RxFifoThreshold;
        /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
        FifoSize      = RxFifoCfgPtr[FifoIndex].RxFifoSize ;
        FifoBottom    = HwObjectId ;
        FifoTop       = HwObjectId + (FifoSize - CAN_ONE);
        FifoThreshold = FifoBottom + FifoThreshold;

        /* If Size and Threshold is same Set BOT as SEL */
        if(FifoThreshold > FifoTop)
        {
          FifoThreshold = FifoBottom ;
        }

        /* Update SEL, TOP, CUR and BOT to the message object MOFGPR */
        CAN_KER[KerIdx]->MO[HwObjectId].FGPR.U = 
          (unsigned_int)(((uint32)FifoThreshold << CAN_MOFGPR_SEL_SHIFT) |
          ((uint32)FifoBottom    << CAN_MOFGPR_CUR_SHIFT) |
          ((uint32)FifoTop       << CAN_MOFGPR_TOP_SHIFT) |
          ((uint32)FifoBottom));

        /* Set MMC and OVIE bits in MOFCR */    
        CAN_KER[KerIdx]->MO[HwObjectId].FCR.U = CAN_FIFO_MOFCR;    

        /* Set interrupt service node --> Refer section "Service Request Node 
        Allocation/Mapping" for SRN mapping */
        /* Receive FIFO interrupt request is generated on interrupt node TXINP
        of the receive FIFO base MO */
        /* Assigned SRN is the receive SRN of the corresponding CAN controller*/
        CAN_KER[KerIdx]->MO[HwObjectId].IPR.B.TXINP = 
          (CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) + 
          (CAN_CALC_HWCTRLID(HwControllerId));

        /*  Set the direction of hardware object to Receive. */
        CAN_KER[KerIdx]->MO[HwObjectId].CTR.U  = CAN_MOCTR_DIR_CLR ;

        /* Enable hardware object */
        CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = ~((uint32)
          (CAN_MOCTR_RXEN_CLR | 
          CAN_MOCTR_MSGVAL_CLR));

        /* Loop through all the slave objects of this receive FIFO structure */
        for (SlaveIndex = HwObjectId+1U;
          (SlaveIndex<=FifoTop)&&(E_OK==RetVal);
          SlaveIndex++)
        {
#ifdef IFX_CAN_DEBUG02
          TestCan_SetMOAllocationErrorType(TESTCAN_RXFIFO_SLAVE_MO_ERROR);
#endif

          /* Allocate the slave objects to associated controller */
          RetVal = Can_lAllocateHwObject(HwControllerId, SlaveIndex);

          if(E_OK == RetVal)
          {
            /* Set MSGVAL and Clear RXEN bit */
            CAN_KER[KerIdx]->MO[SlaveIndex].CTR.U =
              (uint32)CAN_MOCTR_RX_FIFO_SLAVE;
          }
        }
      }
    }
  }
  return (RetVal);
}
#endif /* #if (CAN_NUM_RX_FIFO_MAX > 0U) */

#if (CAN_NUM_RX_FIFO_MAX > 0U)
/*******************************************************************************
** Syntax           : #if (CAN_STANDARD_ID_ONLY == STD_OFF)                   **
**                      IFX_LOCAL_INLINE void Can_lRxFifoBaseMOInit           **
**                           (                                                **
**                             const Can_RxFifoConfigType* RxFifoCfgPtr,      **
**                             uint16 FifoIndex,                              **
**                             uint8 FrameType                                **
**                           )                                                **
**                    #else                                                   **
**                      IFX_LOCAL_INLINE void Can_lRxFifoBaseMOInit           **
**                           (                                                **
**                             const Can_RxFifoConfigType* RxFifoCfgPtr,      **
**                             uint8 FifoIndex                                **
**                           )                                                **
**                    #endif                                                  **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : RxFifoCfgPtr - Pointer to Receive FIFO Configuration    **
**                    HwObjectId - Message Object Id                          **
**                    FrameType - Message Id Type                             **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Initializes receive FIFO base message object            **
**                                                                            **
*******************************************************************************/
#if (CAN_STANDARD_ID_ONLY == STD_OFF)
IFX_LOCAL_INLINE void Can_lRxFifoBaseMOInit(
  const Can_RxFifoConfigType* RxFifoCfgPtr,
  uint16 FifoIndex,
  uint8 FrameType)
#else
IFX_LOCAL_INLINE void Can_lRxFifoBaseMOInit(
  const Can_RxFifoConfigType* RxFifoCfgPtr,
  uint16 FifoIndex)
#endif
{
  uint8 HwObjectId;
  uint8 KerIdx;

  /* Calculate to which kernel, the controller belongs to*/
  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  KerIdx = 
    CAN_CALC_KERIDX(Can_kConfigPtr->RxFifoConfigPtr[FifoIndex].HwControllerId);

  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  HwObjectId = RxFifoCfgPtr[FifoIndex].HwObjectId;
  /* Set message pending number field (MPN) */    
  CAN_KER[KerIdx]->MO[HwObjectId].IPR.B.MPN = HwObjectId;

#if (CAN_STANDARD_ID_ONLY == STD_OFF)
  /* Check if FIFO is of type EXTENDED or MIXED Id */
  if (FrameType != CAN_ID_STANDARD)
  {
    /* Set ID value, ID type and message priority class (to acceptance 
    filtering based on CAN identifier) */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    CAN_KER[KerIdx]->MO[HwObjectId].AR.U = 
      (unsigned_int)(CAN_PRIORITY_ID_BASED | CAN_USE_EXTENDED_ID |  
      (uint32)(RxFifoCfgPtr[FifoIndex].MsgId));

    /* Set filter mask value */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    CAN_KER[KerIdx]->MO[HwObjectId].AMR.B.AM =
      RxFifoCfgPtr[FifoIndex].MaskRef;

    if (FrameType == CAN_ID_MIXED)
    {
      /* Receive both standard and extended IDs */
      CAN_KER[KerIdx]->MO[HwObjectId].AMR.B.MIDE = CAN_ZERO ;
    }
  }
  else
#endif /* #if (CAN_STANDARD_ID_ONLY == STD_OFF) */
  {
    /* If FIFO is of type STANDARD id */
    /* Set ID value, ID type and message priority class (to acceptance 
    filtering based on CAN identifier) */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    CAN_KER[KerIdx]->MO[HwObjectId].AR.U = 
      (unsigned_int)(CAN_PRIORITY_ID_BASED | 
      ((uint32)((RxFifoCfgPtr[FifoIndex].MsgId) << 
      CAN_MOAR_ID_STD_SHIFT )));
    /* Set filter mask value */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    CAN_KER[KerIdx]->MO[HwObjectId].AMR.B.AM = (unsigned_int)
      RxFifoCfgPtr[FifoIndex].MaskRef << CAN_POS_18;
  }
}
#endif /* #if (CAN_NUM_RX_FIFO_MAX > 0U) */

/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE void Can_lInitControllerStatus(void)   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : None                                                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Calls function to initialize CAN controllers            **
**                    Initializes CAN controller state and wakeup status      **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lInitControllerStatus(void)
{
  uint8 ControllerId;

  /* for all configured CAN controllers */
  for(ControllerId=CAN_ZERO;
    ControllerId<(Can_kConfigPtr->CanNumController);
    ControllerId++)
  {
    /* check if the CAN controller is activated */
    if(CAN_INVALID_HW_CONTROLLER_ID != 
      Can_kConfigPtr->CanHwControllerIdMap[ControllerId])
    {
      /* Initialize the CAN controller registers */
      Can_lInitializeController(ControllerId,
        Can_kConfigPtr->CanHwControllerIdMap[ControllerId]);
    }

    /* Initialize the CAN controller status to STOPPED state */
    Can_17_MCanP_ControllerMode[ControllerId] = CANIF_CS_STOPPED;

#if (CAN_WAKEUP_CONFIGURED == STD_ON)
    /* Clear wakeup status flag */
    Can_17_MCanP_ControllerWakeupStatus[ControllerId] = CAN_ZERO ;
#endif
  }
}

#if(CAN_WAKEUP_CONFIGURED == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS403_CAN384_CAN262,DS_AS403_CAN257_CAN266,
DS_AS403_CAN264,DS_AS403_CAN268]                            **
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE void Can_lSetModeWuSupportOn           **
**                                   (                                        **
**                                       uint8 Controller,                    **
**                                       uint8 HwControllerId,                **
**                                     Can_StateTransitionType Transition     **
**                                     )                                      **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant (for different controllers)                   **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller (CanControllerId)**
**                    HwControllerId - Associated hardware CAN Controller Id  **
**                    Transition - Requested transition                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
** Description      : Performs software triggered state transitions of the    **
**                    CAN Controller State machine when wakeup support is     **
**                    enabled                                                 **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lSetModeWuSupportOn(uint8 Controller,
                                          uint8 HwControllerId,
                                          Can_StateTransitionType Transition)
{
#if(CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  uint8 HohIndex;
  uint8 FirstTxMo;
  uint8 NumTxMo;
#endif
  uint8 KerIdx;
  uint8 HwCtrlIDKer;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);
  HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);

  switch (Transition)
  {
  case CAN_T_START :
    {
      /* Clear old transmit requests, if any */
#if(CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      FirstTxMo = Can_kConfigPtr->
        CanControllerMOMapConfigPtr[Controller].ControllerMOMap[2];
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      NumTxMo = Can_kConfigPtr->
        CanControllerMOMapConfigPtr[Controller].ControllerMOMap[3];
      for(HohIndex=0U; HohIndex<NumTxMo; HohIndex++)
      {
        CAN_KER[KerIdx]->MO[FirstTxMo].CTR.U = 
          (uint32)(CAN_MOCTR_WRITE_REQ_CLR);
        FirstTxMo++;
      }
#endif

      /* Enable transmission */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.TXDIS = CAN_NODE_TX_ENABLE;

      /* Clear receive message object to avoid old (unintended) notification */
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
      Can_lClearReceivedMsg(HwControllerId);
#endif

      /* Enable CAN controller */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT = CAN_NODE_ENABLE;

      /* Set current mode to STARTED */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_STARTED;

      break;
    }
  case CAN_T_SLEEP :
    {
      /* Clear receive message object to avoid old (unintended) notification */
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
      Can_lClearReceivedMsg(HwControllerId);
#endif

      /* Enable CAN controller */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT = CAN_NODE_ENABLE;

      /* Clear wakeup status */
      Can_17_MCanP_ControllerWakeupStatus[Controller] = CAN_ZERO;

      /* Set current mode to SLEEP */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_SLEEP;

      break;
    }
  case CAN_T_STOP :
    {
      /* Disable transmission */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.TXDIS = CAN_NODE_TX_DISABLE;

      /* Disable CAN controller */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT = CAN_NODE_DISABLE;

      /* Set current mode to STOPPED */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_STOPPED;

      break;
    }
  default:    /* case CAN_T_WAKEUP */
    {
      /* Disable CAN controller */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT = CAN_NODE_DISABLE;

      /* Set current mode to STOPPED */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_STOPPED;

      break;
    }
  }
}
#endif /* #if(CAN_WAKEUP_CONFIGURED == STD_ON) */

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN261_CAN273_CAN282,DS_AS_CAN265,
DS_AS_CAN263_CAN283]                                        **
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE void Can_lSetModeWuSupportOff          **
**                                   (                                        **
**                                       uint8 Controller,                    **
**                                       uint8 HwControllerId,                **
**                                     Can_StateTransitionType Transition     **
**                                     )                                      **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant (for different controllers)                   **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller (CanControllerId)**
**                    HwControllerId - Associated hardware CAN Controller Id  **
**                    Transition - Requested transition                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : void                                                    **
**                                                                            **
** Description      : Performs software triggered state transitions of the    **
**                    CAN Controller State machine when wakeup support is     **
**                    Disabled                                                **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lSetModeWuSupportOff(uint8 Controller, 
                                           uint8 HwControllerId,
                                           Can_StateTransitionType Transition)
{
#if(CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  uint8 HohIndex;
  uint8 FirstTxMo;
  uint8 NumTxMo;
#endif
  uint8 KerIdx;
  uint8 HwCtrlIDKer;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);
  HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);

  switch (Transition)
  {
  case CAN_T_START :
    {
      /* Clear old transmit requests, if any */
#if(CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      FirstTxMo = Can_kConfigPtr->
        CanControllerMOMapConfigPtr[Controller].ControllerMOMap[2];
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      NumTxMo = Can_kConfigPtr->
        CanControllerMOMapConfigPtr[Controller].ControllerMOMap[3];

      for(HohIndex = CAN_ZERO; HohIndex < NumTxMo; HohIndex++)
      {
        CAN_KER[KerIdx]->MO[FirstTxMo].CTR.U = 
          (uint32)(CAN_MOCTR_WRITE_REQ_CLR);
        FirstTxMo++;
      }
#endif

      /* Clear receive message object to avoid old (unintended) notification */
#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
      Can_lClearReceivedMsg(HwControllerId);
#endif

      /* Enable CAN controller */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT = CAN_NODE_ENABLE;

      /* Set current mode to STARTED */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_STARTED;
      break;
    }
  case CAN_T_SLEEP :
    {
      /* Set current mode to SLEEP */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_SLEEP;
      break;
    }
  case CAN_T_STOP :
    {
      /* Disable CAN controller */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT = CAN_NODE_DISABLE;
      /* Set current mode to STOPPED */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_STOPPED;
      break;
    }
  default:  /* case CAN_T_WAKEUP */
    {
      /* Set current mode to STOPPED */
      Can_17_MCanP_ControllerMode[Controller] = CANIF_CS_STOPPED;
      break;
    }
  }
}

#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
/*******************************************************************************
** Syntax           : void Can_lClearReceivedMsg(uint8 HwControllerId)        **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwControllerId - Associated CAN Controller              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Clears receive message objects to avoid any unintended  **
**                    notification                                            **
**                                                                            **
*******************************************************************************/
static void Can_lClearReceivedMsg(uint8 HwControllerId)
{
  volatile uint32 MsiMaskCopy;
  uint8 HwObjectId;
  uint8 PndBitPosition;
  uint8 MsgIndex;
  uint8 KerIdx;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);

  /* Save current MSIMASK - which needs to be restored back at the end */
  /* to avoid re-entrancy issue */
  MsiMaskCopy = CAN_KER[KerIdx]->MSIMASK.U;

  /* Loop through each of the MSPND register to check for pending notification*/
  for (MsgIndex = 0U;
    MsgIndex <= Can_kConfigPtr->CanRxLastMspndIdx;
    MsgIndex++)
  {
    /* Load corresponding MSIMASK to register */
    CAN_KER[KerIdx]->MSIMASK.U = Can_RxMsiMask[HwControllerId][MsgIndex];

    /* Check for any penidng notification */
    if (CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX != CAN_MSID_NO_MSG_PND_VALUE)
    {
      /* Get the pending bit position */
      PndBitPosition = CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX;

      /* Calculate the message object id */
      HwObjectId = PndBitPosition + 
        ((uint8)((MsgIndex) << CAN_MOIPR_MPN_MSPND_SHIFT));

      /* Clear NEWDAT and RXPND bit */
      CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = 
        CAN_MOCTR_NEWDAT_CLR | CAN_MOCTR_RXPND_CLR;

      /* Clear MSPND bit */
      CAN_KER[KerIdx]->MSPND[MsgIndex].U =
        ~((unsigned_int)CAN_ONE << PndBitPosition);
    }
  }
  /* Restore the MSIMASK value */
  CAN_KER[KerIdx]->MSIMASK.U = MsiMaskCopy;
}
#endif 
/*#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U)) */

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS403_CAN409_CAN410_CAN411_CAN412]        **
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Can_lModeDetCheck       **
**                                   (                                        **
**                                       uint8 Controller,                    **
**                                     Can_StateTransitionType Transition     **
**                                     )                                      **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller Id               **
**                    Transition - Requested transition                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - Valid transition                                 **
**                    E_NOT_OK - Invalid transition                           **
**                                                                            **
** Description      : Checks the validity of software triggered CAN           **
**                    Controller state transition                             **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Std_ReturnType Can_lModeDetCheck(uint8 Controller,
                                             Can_StateTransitionType Transition)
{
  Std_ReturnType RetVal;

  RetVal = E_OK;

  switch (Transition)
  {
  case CAN_T_START :
    {
      /* if current mode is not STOPPED */
      if (Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_STOPPED)
      {
        RetVal = E_NOT_OK;
      }
      break ;
    }
  case CAN_T_SLEEP :
    {
      /* if current mode is neither SLEEP nor STOPPED */
      if((Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_SLEEP) &&
        (Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_STOPPED))
      {
        RetVal = E_NOT_OK;
      }
      break ;
    }
  case CAN_T_STOP :
    {
      /* if current mode is neither STARTED nor STOPPED */
      if((Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_STARTED) &&
        (Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_STOPPED))
      {
        RetVal = E_NOT_OK;
      }
      break ;      
    } 
  case CAN_T_WAKEUP :
    {
      /* if current mode is neither SLEEP nor STOPPED */
      if((Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_SLEEP) &&
        (Can_17_MCanP_ControllerMode[Controller] != CANIF_CS_STOPPED))
      {
        RetVal = E_NOT_OK;
      }
      break ;  
    }  
  default:
    {
      /* Invalid state is requested */
      RetVal = E_NOT_OK;
    }
  }
  return(RetVal);
}
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_NAS_CAN_PR759_PR760_PR761,
DS_AS_CAN202_CAN049]                                   **
**                                                                            **
** Syntax     :IFX_LOCAL_INLINE void Can_lDisableInterrupts (uint8 Controller)**
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Disables CAN Controller Interrupts                      **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lDisableInterrupts (uint8 Controller)
{
  uint8 HwControllerId;
  uint8 BOSrcNum; 
  uint8 RxSrcNum;
  uint32 TxSreVal;
  uint32 RxSreVal;
  uint8 KerIdx;
  uint8 HwCtrlIDKer;
  uint8 IntSrcOffset;


  /* Enter Critical Section */
  SchM_Enter_Can_17_MCanP_CanDisInt();

  if (Can_17_MCanP_InterruptDisableCount[Controller] == CAN_ZERO)
  {          
    HwControllerId = Can_kConfigPtr->CanHwControllerIdMap[Controller];
    /* Calculate to which kernel, the controller belongs to*/
    KerIdx = CAN_CALC_KERIDX(HwControllerId);
    HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);
    IntSrcOffset = (KerIdx << CAN_FOUR); 

    /* Store the interrupt enable/disable status */  
    /* Refer section "Service Request Node Allocation/Mapping" for SRN mapping*/
    BOSrcNum =  (uint8)
      ((uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) << CAN_ONE)
      + (HwCtrlIDKer * CAN_HEDEVICE) + IntSrcOffset);
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    TxSreVal = (uint32)CAN_SRC[HwCtrlIDKer + IntSrcOffset].B.SRE << 
      CAN_TX_INT_SHIFT;

    RxSrcNum =  (uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) +
      HwCtrlIDKer + IntSrcOffset);
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    RxSreVal = (uint32)CAN_SRC[RxSrcNum].B.SRE << CAN_RX_INT_SHIFT;

    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    Can_InterruptsEnabledStatus[Controller] = (uint8) (TxSreVal | RxSreVal |
      (uint32)CAN_SRC[BOSrcNum].B.SRE);

    /* Disable the interrupts relatd to this controller */
    /* Refer section "Service Request Node Allocation/Mapping" for SRN mapping*/

    /* Clear transmit interrupt */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
    CAN_SRC[BOSrcNum].B.SRE = CAN_ZERO;
    /* Clear receive interrupt */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
    CAN_SRC[RxSrcNum].B.SRE = CAN_ZERO;
    /* Clear busoff interrupt */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
    CAN_SRC[HwCtrlIDKer + IntSrcOffset].B.SRE = CAN_ZERO;
  }

  /* Count the number of times Can_17_MCanP_DiableControllerInterrupts API
  is called */
  Can_17_MCanP_InterruptDisableCount[Controller]++;

  /* Exit Critical Section */
  SchM_Exit_Can_17_MCanP_CanDisInt();
}

/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_NAS_CAN_PR759_PR760_PR761,
DS_AS_CAN204_CAN208_CAN050]                            **
**                                                                            **
** Syntax       :IFX_LOCAL_INLINE void Can_lEnableInterrupts(uint8 Controller)**
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Disables CAN Controller Interrupts                      **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lEnableInterrupts(uint8 Controller)
{
  uint8 HwControllerId;
  uint8 BOSrcNum; 
  uint8 RxSrcNum;
  uint8 KerIdx;
  uint8 HwCtrlIDKer;
  uint8 IntSrcOffset;

  /* Enter Critical Section */
  SchM_Enter_Can_17_MCanP_CanEnInt();

  /* No action shall be performed when Can_17_MCanP_DisableControllerInterrupts
  has not been called before. */
  if (Can_17_MCanP_InterruptDisableCount[Controller] > CAN_ZERO)
  {

    /* Incremental disable/enable count */
    Can_17_MCanP_InterruptDisableCount[Controller]-- ;

    if (Can_17_MCanP_InterruptDisableCount[Controller] == CAN_ZERO)
    {
      HwControllerId = Can_kConfigPtr->CanHwControllerIdMap[Controller];

      /* Calculate to which kernel, the controller belongs to*/
      KerIdx = CAN_CALC_KERIDX(HwControllerId);
      HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);
      IntSrcOffset = (KerIdx << CAN_FOUR); 

      /* Restore the status of interrupts */    
      /* Refer section "Service Request Node Allocation/Mapping" for 
      SRN mapping*/
      BOSrcNum =  (uint8)
        ((uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) << CAN_ONE)
        + (HwCtrlIDKer * CAN_HEDEVICE) + IntSrcOffset);
      RxSrcNum =  (uint8)((CAN_NUM_CONTROLLERS_IN_KERNEL[KerIdx]) 
        + HwCtrlIDKer + IntSrcOffset);

      /* Restore transmit interrupt */
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
      CAN_SRC[HwCtrlIDKer + IntSrcOffset].B.SRE = 
        (Can_InterruptsEnabledStatus[Controller] >> CAN_TX_INT_SHIFT ) & 
        CAN_ONE;

      /* Restore receive interrupt */
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
      CAN_SRC[RxSrcNum].B.SRE = 
        (Can_InterruptsEnabledStatus[Controller] >> CAN_RX_INT_SHIFT ) & 
        CAN_ONE;

      /* Restore busoff interrupt */
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
      CAN_SRC[BOSrcNum].B.SRE = 
        Can_InterruptsEnabledStatus[Controller] & CAN_ONE;
    }
  }
  /* Exit Critical Section */
  SchM_Exit_Can_17_MCanP_CanEnInt();
}

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN217_CAN218_CAN219]                  **
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE Std_ReturnType Can_lWriteDetCheck      **
**                                            (                               **
**                                              Can_HwHandleType Hth,         **
**                                              const Can_PduType *PduInfo    **
**                                            )                               **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Hth - Hardware Transmit Handler                         **
**                    PduInfo - Pointer to SDU user memory, DLC and Identifier**
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : E_OK - No Development Error                             **
**                    E_NOT_OK - Development Error detected and reported      **
**                                                                            **
** Description      : Handles DET checks for Can_17_MCanP_Write API           **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Std_ReturnType Can_lWriteDetCheck(Can_HwHandleType Hth,
                                               const Can_PduType *PduInfo)
{
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
#if (CAN_STANDARD_ID_ONLY != STD_ON)
  const Can_TxHwObjectConfigType *TxHwObjCfgPtr;
  uint8 HthIndex;
#endif
#endif
  Std_ReturnType RetVal;

#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  RetVal = E_OK;
#endif

  /* Check if 'Hth' is a valid transmit handle */
#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
#if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
  if((Hth < Can_kConfigPtr->CanNumRxHwObj) || 
    (Hth >= (Can_kConfigPtr->CanNumRxHwObj + 
    Can_kConfigPtr->CanNumTxHwObj)))
#else
  if (Hth >= Can_kConfigPtr->CanNumTxHwObj)
#endif
#endif
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      CAN_SID_WRITE, CAN_E_PARAM_HANDLE);
    RetVal = E_NOT_OK;
  }

#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  /* Check if PduInfo is a null pointer */
  else if (PduInfo == NULL_PTR)
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      CAN_SID_WRITE, CAN_E_PARAM_POINTER);
    RetVal = E_NOT_OK;      
  }
#if (CAN_FD_ENABLE== STD_OFF)
  /* check if DLC is greater than 8 */
  else if (PduInfo->length > CAN_MAX_DATA_LENGTH )
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      CAN_SID_WRITE, CAN_E_PARAM_DLC);
    RetVal = E_NOT_OK;      
  }
#endif 
#if (CAN_FD_ENABLE== STD_ON)
  /* Valid CAN FD lengths: 0-8,12,16,20,24,32,48,64 bytes */
  else if ((PduInfo->length > CAN_MAX_DATA_LENGTH)&&
    (PduInfo->length <= CAN_MAX_FD_LENGTH))
  {
    if ((PduInfo->length > CAN_TWENTY_FOUR)? 
      (PduInfo->length & CAN_FIFTEEN):(PduInfo->length & CAN_THREE))
    {
      /* Report to DET */
      Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
        CAN_SID_WRITE, CAN_E_PARAM_DLC);
      RetVal = E_NOT_OK; 
    }
  }
  else if (PduInfo->length > CAN_MAX_FD_LENGTH)
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      CAN_SID_WRITE, CAN_E_PARAM_DLC);
    RetVal = E_NOT_OK; 
  }
#endif   
  /* Check if sdu is a null pointer */
  else if (PduInfo->sdu == NULL_PTR)
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      CAN_SID_WRITE, CAN_E_PARAM_POINTER);
    RetVal = E_NOT_OK;      
  }
  else
  {
#if (CAN_STANDARD_ID_ONLY != STD_ON)
    /* Extract HTH index */
#if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
    HthIndex = (uint8)(Hth - Can_kConfigPtr->CanNumRxHwObj);
#else
    HthIndex = Hth;
#endif

    TxHwObjCfgPtr = Can_kConfigPtr->CanTxHwObjectConfigPtr;

    /* Check for invalid message type */
    /* [1] Standard id was configured for the hardware object,
    but extended id is requested for transmission */
    /* [2] Extended id was configured for the hardware object,
    but standard id is requested for transmission */
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    if (((TxHwObjCfgPtr[HthIndex].FrameType == CAN_ID_EXTENDED) &&
      (((PduInfo->id) & CAN_EXTENDED_MSB_SET) == CAN_ZERO)) ||
      ((TxHwObjCfgPtr[HthIndex].FrameType == CAN_ID_STANDARD) &&
      (((PduInfo->id) & CAN_EXTENDED_MSB_SET) != CAN_ZERO)))
    {
      /* Report to DET */
      Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
        CAN_SID_WRITE, CAN_E_PARAM_MSGID);
      RetVal = E_NOT_OK;
    }
#endif /* #if (CAN_STANDARD_ID_ONLY != STD_ON) */
  }
#else
  UNUSED_PARAMETER (Hth)
    UNUSED_PARAMETER (PduInfo)
#endif /* #if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U) */

    return(RetVal);
}
#endif

#if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_NAS_CAN_PR759_PR760_PR761,
DS_AS_CAN011_CAN212_CAN213_CAN214_CAN275_CAN059_CAN076_CAN276]**
**                                                                            **
** Syntax           : IFX_LOCAL_INLINE Can_ReturnType Can_lWriteMsgObj        **
**                                            (                               **
**                                              uint8 HthIndex,               **
**                                              uint8 HwObjectId,             **
**                                              const Can_PduType *PduInfo    **
**                                            )                               **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HthIndex - HTH index in the configuration structure     **
**                    HwObjectId - Message Object Id                          **
**                    PduInfo - Pointer to SDU user memory, DLC and Identifier**
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : CAN_OK - Write command has been accepted                **
**                    CAN_BUSY - No message object available or pre-emptive   **
**                               call of Can_17_MCanP_Write that can't be     **
**                               implemented re-entrant                       **
**                    CAN_NOT_OK - development error occured                  **
**                                                                            **
** Description      : Programs Message Object for transmission                **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE Can_ReturnType Can_lWriteMsgObj(uint8 HthIndex,
                                             uint8 HwObjectId,
                                             const Can_PduType *PduInfo)
{
  volatile uint8 *MoData0_3;
  volatile uint8 *MoData4_7;
#if (CAN_FD_ENABLE== STD_ON)
  volatile uint8 *MoData8_35;
  volatile uint8 *MoData36_63;
  uint8 Index2;
  uint8 Index3;
  uint8 HwCtrlIDKer;
#endif
  uint8 Index;
  uint8 Index1;
  uint8 TxMOIdx;

  Can_ReturnType RetVal;
  uint8 KerIdx;
  uint8 MsgDLC;
  volatile uint8 CanCtrStat;

  RetVal = CAN_OK;
  Index1 = CAN_ZERO;

  /* Calculate to which kernel, the controller belongs to*/
  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  KerIdx = 
    CAN_CALC_KERIDX(Can_kConfigPtr->CanTxHwObjectConfigPtr[HthIndex].
    HwControllerId);

#if (CAN_FD_ENABLE== STD_ON)
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    HwCtrlIDKer = 
    CAN_CALC_HWCTRLID(Can_kConfigPtr->CanTxHwObjectConfigPtr[HthIndex].
    HwControllerId);
#endif
  /* Enter Critical Section */
  SchM_Enter_Can_17_MCanP_CanWrMO();

  /* Check for free message object confgiured for the HTH */
#if(CAN_MULTIPLEXED_TRANSMISSION == STD_ON)
  while
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    ((((CAN_KER[KerIdx]->MO[HwObjectId].STAT.U) & 
    (CAN_MOCTR_RXUPD_CLR | CAN_MOCTR_TXRQ_CLR)) != CAN_ZERO) && 
    (HwObjectId < 
    (Can_kConfigPtr->CanTxHwObjectConfigPtr[HthIndex].MsgObjIdLast)))
  {
    HwObjectId+=CAN_MOSize;
  }
#endif

#ifdef IFX_CAN_DEBUG 
  CanCtrStat = TestCan_DebugMask; 
#else 
  CanCtrStat = 
    (uint8)(CAN_KER[KerIdx]->MO[HwObjectId].STAT.U & CAN_MOCTR_RXUPD_CLR); 
#endif 

  /* Check if hardware transmit object is busy with another transmit request */
  if (CanCtrStat== CAN_ZERO ) 
  {
    /* Signal mutex for Hth */
    CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = ~((uint32)CAN_MOCTR_RXUPD_CLR);

    /* Exit Critical Section */
    SchM_Exit_Can_17_MCanP_CanWrMO();

    /* The CAN driver writes ID and DLC in the appropriate hardware 
    registers and triggers the transmission. */

    /* Check if a pre-emptive call of Can_Write has been issued, that cannot be
    handled re-entrant (i.e. a Can_17_MCanP_Write call with the same HTH)*/
    if ((CAN_KER[KerIdx]->MO[HwObjectId].STAT.U & CAN_MOCTR_TXRQ_CLR) == 
      CAN_ZERO)
    {
#if (CAN_STANDARD_ID_ONLY == STD_OFF)    
      /* Check if extended id is requested for transmission */
      if (PduInfo->id & CAN_EXTENDED_MSB_SET)
      {
        /* Set ID value, ID type and message priority class  */
        CAN_KER[KerIdx]->MO[HwObjectId].AR.U = 
          CAN_PRIORITY_ID_BASED | CAN_USE_EXTENDED_ID ;
        CAN_KER[KerIdx]->MO[HwObjectId].AR.B.ID = PduInfo->id ;
#if (CAN_FD_ENABLE== STD_ON)        
        if (PduInfo->id & CAN_FD_EXTENDED_SET)
        {
          if(CAN_ONE == CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.FDEN)
          {
            CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.FDF = CAN_ONE;
          }
        }
#endif
      } 
      else 
#endif      
        /* Standard id is requested for transmission */
      {
        /* Set ID value, ID type and message priority class  */
        CAN_KER[KerIdx]->MO[HwObjectId].AR.U = CAN_PRIORITY_ID_BASED;
        CAN_KER[KerIdx]->MO[HwObjectId].AR.B.ID = 
          (unsigned_int)((uint32)PduInfo->id << CAN_MOAR_ID_STD_SHIFT) ;
#if (CAN_FD_ENABLE== STD_ON)        
        if (PduInfo->id & CAN_FD_STANDARD_SET)
        {
          if(CAN_ONE == CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.FDEN)
          {
            CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.FDF = CAN_ONE;
          }
        }
#endif
      }

      MsgDLC = PduInfo->length;
      /*Message length varies from DLC when FD is enabled and 
      DLC is greater than 8.
      DLC of 9,10,11,12,13,14,15 corresponds to 
      message length 12,16,20,24,32,48,64 respectively */ 
#if (CAN_FD_ENABLE== STD_ON)
      if (PduInfo->length > CAN_EIGHT)
      {
        MsgDLC = (PduInfo->length > CAN_TWENTY_FOUR)? 
          ((PduInfo->length >> CAN_FOUR)+ CAN_ELEVEN):
        ((PduInfo->length >> CAN_TWO) + CAN_SIX);
      }
#endif

      /* Assign DLC */
      CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.DLC = MsgDLC ;

      /* Update data bytes */
      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData0_3= 
        (volatile uint8 *)(void *)&CAN_KER[KerIdx]->MO[HwObjectId].DATAL.U;
      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData4_7 = 
        (volatile uint8 *)(void *)&CAN_KER[KerIdx]->MO[HwObjectId].DATAH.U;

#if (CAN_FD_ENABLE== STD_ON)
      /* For a 64 byte message, data bytes 0-7 are stored in the message object,
      similar to a standard message object, data bytes 8-35 are stored 
      in the message object to which MOFGPR.BOT refers to and 
      data bytes 36-63 are stored in the message object to which MOFGPR.TOP 
      refers to Data byte 0 refers to the first byte transferred within 
      a CAN frame. */

      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData8_35 = (volatile uint8 *)
        (void *)&CAN_KER[KerIdx]->MO[HwObjectId + CAN_ONE];
      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData36_63 = (volatile uint8 *)
        (void *)&CAN_KER[KerIdx]->MO[HwObjectId + CAN_TWO];

      Index2 = CAN_ZERO;
      Index3 = CAN_ZERO;

#endif   


      for(Index=CAN_ZERO; Index < PduInfo->length; Index++)
      {
        if (CAN_FOUR > Index)
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          MoData0_3[Index] = PduInfo->sdu[Index];
        }
        if ((CAN_FOUR <= Index)&& (CAN_EIGHT > Index))
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          MoData4_7[Index1] = PduInfo->sdu[Index];
          Index1++;
        }

#if (CAN_FD_ENABLE== STD_ON)
        if ((CAN_EIGHT <= Index)&& (CAN_THIRTY_SIX > Index))
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          MoData8_35[Index2] = PduInfo->sdu[Index];
          Index2++;
        }
        if (CAN_THIRTY_SIX <= Index)
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          MoData36_63[Index3] = PduInfo->sdu[Index];
          Index3++;
        }
#endif 
      }

      TxMOIdx = HwObjectId-(Can_kConfigPtr->CanTxHwObjCntKer[KerIdx]);
#if (CAN_FD_ENABLE== STD_ON)
      /* Intention is to divide the TxMOIdx by 3 (CAN_MOSize).
       It is achieved by the expression Q = ((VAL * 0xAB) >> 8) >> 1 */
      TxMOIdx = 
      (uint8)(((uint16)TxMOIdx * (uint16)CAN_8BITDIV3FACTOR) >> CAN_NINE);
#endif

      /* Mark the hardware object for transmission. */                     
      CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = 
        ~((uint32)CAN_MOCTR_WRITE_REQ_CLR) ;

      /* Store the software pdu handle number */
      Can_SwObjectHandle[KerIdx][TxMOIdx] = PduInfo->swPduHandle;
    }
    else 
    {
      /* Hardware object is busy transmitting */
      RetVal = CAN_BUSY ;
    } 

    /* Release the mutex for Hth */
    CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = CAN_MOCTR_RXUPD_CLR ;

  }  
  else  
  {
    /* hardware object busy with another transmit request */
    /* Exit Critical Section */
    SchM_Exit_Can_17_MCanP_CanWrMO();

    RetVal = CAN_BUSY ;
  }
  return(RetVal);
}
#endif /* #if (CAN_TX_HARDWARE_OBJECTS_MAX > 0U) */

#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
/*******************************************************************************
** Syntax           : static void Can_lReceiveHandler(uint8 HwControllerId)   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwControllerId - Associated CAN Controller              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : - This function is the core part of the interrupt       **
**                    service routine for Receive Interrupt                   **
**                    - In case of successful reception event, this           **
**                    funciton calls the function Can_lRxIsrExtractData to    **
**                    extract data from the message object and notify upper   **
**                    layer                                                   **
**                    - This function is also called by the polling function  **
**                    Can_17_MCanP_MainFunction_Read for controllers          **
**                    configured with CanRxProcessing as POLLING              **
**                                                                            **
*******************************************************************************/
static void Can_lReceiveHandler(uint8 HwControllerId)
{
  volatile uint32 MsiMaskCopy;
  uint8 HwObjectId;
  uint8 PndBitPosition;
  uint8 MsgIndex;
  uint8 KerIdx;
  uint8 LoopBreak32;
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  uint8 LoopBreak;
  Std_ReturnType Status;
  LoopBreak = CAN_ZERO;
#endif


  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);

  /* Save current MSIMASK - which needs to be restored back at the end */
  /* to avoid re-entrancy issue */
  MsiMaskCopy = CAN_KER[KerIdx]->MSIMASK.U;

  /* Loop for all the MSPND registers corresponding to recive MOs */
  for (MsgIndex = CAN_ZERO;
    ((MsgIndex <= Can_kConfigPtr->CanRxLastMspndIdx)
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    && (LoopBreak == CAN_ZERO)
#endif
    );
  MsgIndex++)
  {
    LoopBreak32 = CAN_ZERO;
    /* Load MSIMASK corresponding to the controller */
    CAN_KER[KerIdx]->MSIMASK.U = Can_RxMsiMask[HwControllerId][MsgIndex];

    /* Check for any penidng notification */
    /* To avoid infinite loop in case of hardware error, LoopBreak is used
    with worst case of 32 iterations to process 32 message objects pointed 
    by the given MSIMASK */
    while ((CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX != 
      CAN_MSID_NO_MSG_PND_VALUE) &&
      (LoopBreak32 < CAN_THIRTY_TWO)
#if (CAN_DEV_ERROR_DETECT == STD_ON)
      && (LoopBreak == CAN_ZERO)
#endif
      )
    {
      /* Count the iterations */
      LoopBreak32++;

      /* Get the pending bit position */
      PndBitPosition = CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX ;

      /* Calculate the message object id */
      HwObjectId = PndBitPosition + 
        ((uint8)((MsgIndex) << CAN_MOIPR_MPN_MSPND_SHIFT));


#if (CAN_NUM_RX_FIFO_MAX > 0U)
      /* Check whether received HwObjectId is Receive FIFO base object */
      if (CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.MMC == CAN_FIFO_MOFCR_MMC_BIT)
      {
        /* Call receive fifo handler */
        Can_lRxFifoHandler(HwControllerId,HwObjectId);

        /* Reset MSPND bit */
        CAN_KER[KerIdx]->MSPND[MsgIndex].U = 
          ~((unsigned_int)CAN_ONE << PndBitPosition);
      }
      else
#endif /* #if (CAN_NUM_RX_FIFO_MAX > 0U) */ 
      {
        /* Extract the required infomation from the message object */
#if (CAN_DEV_ERROR_DETECT == STD_OFF)
        Can_lRxIsrExtractData(HwControllerId,
          HwObjectId,MsgIndex,PndBitPosition);
#else
        Status = Can_lRxIsrExtractData(HwControllerId,
          HwObjectId,MsgIndex,PndBitPosition);
        if(E_NOT_OK == Status)
        {
          LoopBreak = CAN_ONE;
        }
#endif
      }
    }
  }
  /* Restore the MSIMASK value */
  CAN_KER[KerIdx]->MSIMASK.U  = MsiMaskCopy;
}
#endif 
/* #if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U)) */

#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
/*******************************************************************************
** TRACEABILITY     : [cover parentID=DS_NAS_CAN_PR766_PR768,DS_NAS_CAN_PR97,
DS_AS403_CAN395,DS_AS403_CAN423,
DS_AS_CAN060_CAN299_CAN300,DS_AS_CAN012,
DS_AS_CAN443_CAN444_CAN396,DS_AS403_CAN279]            **
**                                                                            **
** Syntax           :                                                         **
**                                                                            **
**      #if (CAN_DEV_ERROR_DETECT == STD_ON)                                  **
**      IFX_LOCAL_INLINE Std_ReturnType Can_lRxIsrExtractData                 **
**                                     (                                      **
**                                       uint8 HwControllerId,                **
**                                       uint8 HwObjectId,                    **
**                                       uint8 MsgIndex,                      **
**                                       uint8 PndBitPosition                 **
**                                     )                                      **
**      #else                                                                 **
**      IFX_LOCAL_INLINE void Can_lRxIsrExtractData                           **
**                           (                                                **
**                             uint8 HwControllerId,                          **
**                             uint8 HwObjectId,                              **
**                             uint8 MsgIndex,                                **
**                             uint8 PndBitPosition                           **
**                           )                                                **
**      #endif                                                                **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwObjectId - Message Object Id                          **
**                    MsgIndex - MSPND Register Index                         **
**                    PndBitPosition - Bit Position within MSPND Register     **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function extracts data from the message object     **
**                    and notifies upper layer                                **
**                                                                            **
*******************************************************************************/
#if (CAN_DEV_ERROR_DETECT == STD_ON)
IFX_LOCAL_INLINE Std_ReturnType Can_lRxIsrExtractData(uint8 HwControllerId,
                                                  uint8 HwObjectId,
                                                  uint8 MsgIndex,
                                                  uint8 PndBitPosition)
#else
IFX_LOCAL_INLINE void Can_lRxIsrExtractData(uint8 HwControllerId,
                                        uint8 HwObjectId,
                                        uint8 MsgIndex,
                                        uint8 PndBitPosition)
#endif
{
  volatile uint8 *MoData0_3;
  volatile uint8 *MoData4_7;
#if (CAN_FD_ENABLE== STD_ON)
  volatile uint8 *MoData8_35;
  volatile uint8 *MoData36_63;
  uint8 MoDataIndex2;
  uint8 MoDataIndex3;
  const uint8 CAN_MAPPING_DLC_FD_LENGTH[]= {12U,16U,20U,24U,32U,48U,64U};
#endif

  uint32 TempMoctr;
  Can_IdType MessageId;
  uint8 MoDataIndex;
  uint8 MoDataIndex1;
  uint8 MessageDlc;
  uint8 MessageLength;
  uint8 LoopBreak2; /* To avoid infinte loop */
  uint8 KerIdx;
  uint8 RxObjOffset;
  uint8 Hrh; 
#if (CAN_LPDU_RX_CALLOUT == STD_ON)
  boolean RetVal;
#endif
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  uint8 LoopBreak; /* To exit the loop in case of development error */
  Std_ReturnType Status;

  Status = E_OK;
  MessageDlc = CAN_ZERO;
  MessageId = CAN_ZERO;
  LoopBreak = CAN_ZERO;
#endif
  LoopBreak2 = CAN_ZERO;
  MoDataIndex1 = CAN_ZERO;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);


#if (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
  RxObjOffset = Can_kConfigPtr->CanRxHwObjCntKer[KerIdx];
#else
  RxObjOffset = CAN_ZERO;
#endif
  Hrh = RxObjOffset + HwObjectId;
#if (CAN_FD_ENABLE== STD_ON)
  /* Intention is to divide the Hrh by 3 (CAN_MOSize). It is achieved by the
  expression Q = ((VAL * 0xAB) >> 8) >> 1 */
  Hrh = (uint8)(((uint16)Hrh * (uint16)CAN_8BITDIV3FACTOR) >> CAN_NINE);
#endif

  do
  {
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    /* check for message object over-writing */
    if (CAN_KER[KerIdx]->MO[HwObjectId].STAT.U & CAN_MOSTAT_MSGLST_CLR)
    {
      /* Clear MSGLST, NEWDAT and RXPND */
      CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = (CAN_MOSTAT_MSGLST_CLR | 
        CAN_MOCTR_NEWDAT_CLR | CAN_MOCTR_RXPND_CLR);

      /* Clear MSPND bit */
      CAN_KER[KerIdx]->MSPND[MsgIndex].U =
        ~((unsigned_int)CAN_ONE << PndBitPosition);

      /* Report to DET */
      Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
        CAN_SID_RECEIVEISR, CAN_E_DATALOST);
      Status = E_NOT_OK;

      LoopBreak = CAN_ONE;
    }
    else
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */
    {
      /* Clear NEWDAT and RXPND */
      CAN_KER[KerIdx]->MO[HwObjectId].CTR.U = 
        (CAN_MOCTR_NEWDAT_CLR | CAN_MOCTR_RXPND_CLR);

#if (CAN_STANDARD_ID_ONLY == STD_OFF) 
      /* Check if extended id is received */
      if (CAN_KER[KerIdx]->MO[HwObjectId].AR.B.IDE == CAN_ONE) 
      {
        /* extract message Id and set MSBit */
        MessageId = (Can_IdType)
          (CAN_KER[KerIdx]->MO[HwObjectId].AR.B.ID | CAN_EXTENDED_MSB_SET);
      }
      else /* Standard frame */
#endif /* #if (CAN_STANDARD_ID_ONLY == STD_OFF)  */
      {
        /* extract message id */
      MessageId =(Can_IdType)((uint32)CAN_KER[KerIdx]->MO[HwObjectId].AR.B.ID >>
        CAN_MOAR_ID_STD_SHIFT) ;
      }
      /* Extract DLC */
      MessageDlc = (uint8) CAN_KER[KerIdx]->MO[HwObjectId].FCR.B.DLC;
      MessageLength = MessageDlc;
      /* Message length varies from DLC when FD is enabled and 
      DLC is greater than 8.
      DLC of 9,10,11,12,13,14,15 corresponds to 
      message length 12,16,20,24,32,48,64 respectively */ 
      if(MessageDlc > CAN_EIGHT)
      {
#if (CAN_FD_ENABLE== STD_OFF)
        MessageLength = CAN_EIGHT;
        MessageDlc = CAN_EIGHT;
#else
        MessageLength = CAN_MAPPING_DLC_FD_LENGTH[MessageDlc-CAN_NINE];
#endif  
      }


      /* Extract received data bytes */
      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData0_3 = 
        (volatile uint8 *)(void *)&CAN_KER[KerIdx]->MO[HwObjectId].DATAL.U;
      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData4_7 = 
        (volatile uint8 *)(void *)&CAN_KER[KerIdx]->MO[HwObjectId].DATAH.U;

#if (CAN_FD_ENABLE== STD_ON)
      /* For a 64 byte message, data bytes 0-7 are stored in the message object,
      similar to a standard message object, data bytes 8-35 are stored 
      in the message object to which MOFGPR.BOT refers to and 
      data bytes 36-63 are stored in the message object to which MOFGPR.TOP 
      refers to Data byte 0 refers to the first byte transferred within a 
      CAN frame. */
      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData8_35 = (volatile uint8 *)
        (void *)&CAN_KER[KerIdx]->MO[HwObjectId + CAN_ONE];
      /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
      MoData36_63 = (volatile uint8 *)
        (void *)&CAN_KER[KerIdx]->MO[HwObjectId + CAN_TWO];

      MoDataIndex2 = CAN_ZERO;
      MoDataIndex3 = CAN_ZERO;

#endif      


      for(MoDataIndex=CAN_ZERO; MoDataIndex < MessageLength; MoDataIndex++)
      {
        if (CAN_FOUR > MoDataIndex)
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          Can_RxMessageData[HwControllerId][MoDataIndex] = 
            MoData0_3[MoDataIndex];
        }
        if ((CAN_FOUR <= MoDataIndex)&& (CAN_EIGHT > MoDataIndex))
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          Can_RxMessageData[HwControllerId][MoDataIndex] = 
            MoData4_7[MoDataIndex1];
          MoDataIndex1++;
        }
#if (CAN_FD_ENABLE== STD_ON)
        if ((CAN_EIGHT <= MoDataIndex)&& (CAN_THIRTY_SIX > MoDataIndex))
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          Can_RxMessageData[HwControllerId][MoDataIndex] = 
            MoData8_35[MoDataIndex2];
          MoDataIndex2++;
        }
        if (CAN_THIRTY_SIX <= MoDataIndex)
        {
          /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
          Can_RxMessageData[HwControllerId][MoDataIndex] = 
            MoData36_63[MoDataIndex3];
          MoDataIndex3++;
        }
#endif 
      }


      LoopBreak2++;

      /* Clear MSPND bit */
      CAN_KER[KerIdx]->MSPND[MsgIndex].U =
        ~((unsigned_int)CAN_ONE << PndBitPosition);
    }
    /* If NEWDAT or RXUPD bit is set --> Message object got/getting updated */
    /* In such a case the extracted information will not be consistent */
    /* Hence, information needs to be re-extracted from the message object */

#ifdef IFX_CAN_DEBUG03
    TempMoctr = 
      CAN_KER[KerIdx]->MO[HwObjectId].STAT.U | TestCan_DebugMask03;
#else
    TempMoctr = CAN_KER[KerIdx]->MO[HwObjectId].STAT.U;
#endif

  }while(((((TempMoctr & CAN_MOCTR_NEWDAT_CLR) != CAN_ZERO) ||
    ((TempMoctr & CAN_MOCTR_RXUPD_CLR)  != CAN_ZERO)) 
    &&
    (LoopBreak2 <= CAN_TWO))
#if (CAN_DEV_ERROR_DETECT == STD_ON)
    && (LoopBreak == CAN_ZERO)
#endif
    );

#if (CAN_DEV_ERROR_DETECT == STD_ON)
  /* In all the cases of (LoopBreak2 > CAN_TWO), development error is reported,
  as MSGLST bit will be set */
  if(E_OK == Status)
#endif
  {
    /* The condition (LoopBreak2 > CAN_TWO) indicates data inconsistency, i.e.,
    the message object is getting updated while the data is being copied to 
    the user buffer. Since the data in the user buffer is inconsistent in 
    this case, CanIf_RxIndication and Receive L-PDU callout will not be 
    called; The function is exited to avoid blocking.
    According to AUTOSAR: "The system designer shall assure that 
    the runtime for message reception (interrupt driven or polling) 
    correlates with the fastest possible reception in the system."
    This also implies the need for having correct interrupt priorities to 
    ensure that the interrupt latency is within tolerable limits */
    if(LoopBreak2 <= CAN_TWO)
    {
#if (CAN_LPDU_RX_CALLOUT == STD_ON)
      /* Call receive L-PDU callout function if configured */
      RetVal = Can_kConfigPtr->Can_LPduRxCalloutFuncPtr(Hrh,
        MessageId, 
        MessageDlc, 
        &Can_RxMessageData[HwControllerId][CAN_ZERO]);

      /* Notification function CanIf_RxIndication should be called only if the 
      callout function returns true */
      if(TRUE == RetVal)
#endif
      {
        /* Call the notification function */
        CanIf_RxIndication((Can_HwHandleType)(Hrh),
          MessageId, 
          MessageDlc, 
          &Can_RxMessageData[HwControllerId][CAN_ZERO]);
      }
    }
  }
#if (CAN_DEV_ERROR_DETECT == STD_ON)
  return (Status);
#endif
}
#endif 
/* #if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U)) */

#if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U))
#if(CAN_WAKEUP_CONFIGURED == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN364_CAN269_CAN270_CAN271]           **
**                                                                            **
** Syntax           : static void Can_lWakeupHandler(uint8 HwControllerId)    **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwControllerId - Associated CAN Controller              **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function is the core part of the interrupt         **
**                    service routine for Receive Interrupt used for detection**
**                    and reporting of wakeup event                           **
**                    - This function is also called by the polling function  **
**                    Can_17_MCanP_MainFunction_Wakeup for controllers        **
**                    configured with CanWakeupProcessing as POLLING          **
**                                                                            **
*******************************************************************************/
static void Can_lWakeupHandler(uint8 HwControllerId)
{
  volatile uint32 MsiMaskCopy;
  EcuM_WakeupSourceType WakeupSourceId;
  uint8 ControllerId;
  uint8 HwObjectId;
  uint8 PndBitPosition;
  uint8 MsgIndex;
  uint8 LoopBreak;
  uint8 KerIdx;
  uint8 HwCtrlIDKer;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);
  HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);

  /* Save current MSIMASK - which needs to be restored back at the end */
  /* to avoid re-entrancy issue */
  MsiMaskCopy = CAN_MSIMASK.U ;
  LoopBreak = CAN_ZERO;

  /* Extract the coreesponding CanControllerId */
  ControllerId = Can_NodeIdMap[HwControllerId];

  /* Loop through all MSPND registers configured for receive message object */
  for (MsgIndex = CAN_ZERO;
    ((MsgIndex <= Can_kConfigPtr->CanRxLastMspndIdx) && 
    (LoopBreak == CAN_ZERO));
  MsgIndex++)
  {
    /* Load the MSIMASK corresponding to the controller */
    CAN_KER[KerIdx]->MSIMASK.U = Can_RxMsiMask[HwControllerId][MsgIndex];

    /* Check for any pending notification */
    if (CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX != CAN_MSID_NO_MSG_PND_VALUE)
    {
      /* Get the pending bit position */
      PndBitPosition = CAN_KER[KerIdx]->MSID[MsgIndex].B.INDEX ;

      /* Calculate the message object id */
      HwObjectId = PndBitPosition + (uint8)
        ((MsgIndex) << CAN_MOIPR_MPN_MSPND_SHIFT);

      /* Clear NEWDAT and RXPND bit */
      CAN_KER[KerIdx]->MO[HwObjectId].CTR.U =
        CAN_MOCTR_NEWDAT_CLR | CAN_MOCTR_RXPND_CLR;

      /* Clear MSPND bit */
      CAN_KER[KerIdx]->MSPND[MsgIndex].U =
        ~((unsigned_int)CAN_ONE << PndBitPosition);

      /* Extract corresponding wakeup source id */
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      WakeupSourceId = (EcuM_WakeupSourceType)
        Can_kConfigPtr->CanWakeupSourceIdPtr[ControllerId];

      /* Disable the CAN controller */
      CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.INIT = CAN_NODE_DISABLE;

      /* Set CAN controller mode to STOPPED */
      Can_17_MCanP_ControllerMode[ControllerId] = CANIF_CS_STOPPED;

      /* Set CAN controller wakeup status */
      Can_17_MCanP_ControllerWakeupStatus[ControllerId] = CAN_ONE;

      /* Call EcuM function to check for wakeup event */
      EcuM_CheckWakeup(WakeupSourceId);

      /* Exit the loop to avoid multiple wakeup notifications for the same 
      CAN controller */
      LoopBreak = CAN_ONE;
    }
  }

  /* Restore the MSIMASK value */
  CAN_KER[KerIdx]->MSIMASK.U  = MsiMaskCopy;
}
#endif /* #if(CAN_WAKEUP_CONFIGURED == STD_ON) */
#endif
/* #if((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)||(CAN_NUM_RX_FIFO_MAX > 0U)) */

/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE void Can_lClearAndEnableInterrupt      **
**                                         (                                  **
**                                           uint8 ServiceRequestNumber       **
**                                         )                                  **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : ServiceRequestNumber - Service Request Number           **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function clears and enables interrupt              **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lClearAndEnableInterrupt(uint8 
                                               ServiceRequestNumber)
{
  /* It is not advisable to clear a pending service request flag SRR 
  (writing CLRR = 1) and enable the corresponding service request node 
  SRN (writing SRE = 1) simultaneously at the same write access to the 
  Service Request Control Register. If this should happen, an unintended 
  interrupt request may be generated.
  */
  /* Clear interrupt */
  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
  CAN_SRC[ServiceRequestNumber].U |= CAN_SRC_CLRR ;
  /* Enable interrupt */
  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic is used to 
    efficiently access the SFRs */
  CAN_SRC[ServiceRequestNumber].U |= CAN_SRC_SRE ;
}


#if (CAN_NUM_RX_FIFO_MAX > 0U)
/*******************************************************************************
** Syntax         : IFX_LOCAL_INLINE void Can_lRxFifoHandler(uint8 HwObjectId)**
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : HwObjectId - Message Object Id                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Recieve event handler for Receive FIFO                  **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lRxFifoHandler(uint8 HwControllerId,
                                     uint8 HwObjectId)
{
  uint16 FifoIndex;
  uint8 CurrentHardwareObject;
  uint8 FifoTop;
  uint8 FifoBottom;
  uint8 Threshold;
  uint8 NewThreshold;
  uint8 Temp;
  uint8 CurrentThreshold;
  uint16 Hfh;
  uint8 BreakLoop;
  uint8 KerIdx;
  uint16 FifoTopBot;

  Hfh = CAN_ZERO;
  Threshold = CAN_ZERO;
  BreakLoop = CAN_ZERO;

  /* Extract threshold of the current FIFO based on HwObjectId  */
  for(FifoIndex = CAN_ZERO;
    ((FifoIndex < Can_kConfigPtr->CanNumRxFifo) && (BreakLoop == CAN_ZERO));
    FifoIndex++)
  {
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    if((Can_kConfigPtr->RxFifoConfigPtr[FifoIndex].HwObjectId == HwObjectId) &&
      (Can_kConfigPtr->RxFifoConfigPtr[FifoIndex].HwControllerId == 
      HwControllerId) &&
      (Can_kConfigPtr->RxFifoConfigPtr[FifoIndex].HwControllerId 
      != CAN_INVALID_HW_CONTROLLER_ID))
    {
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      Threshold = Can_kConfigPtr->RxFifoConfigPtr[FifoIndex].RxFifoThreshold;
      Hfh = FifoIndex;
      BreakLoop = CAN_ONE;
    }
  }

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);


  /* Calculate the hfh (hardware fifo handle) number */
#if ((CAN_RX_HARDWARE_OBJECTS_MAX > 0U)&&(CAN_TX_HARDWARE_OBJECTS_MAX > 0U))
  Hfh = Hfh + Can_kConfigPtr->CanNumRxHwObj + Can_kConfigPtr->CanNumTxHwObj;
#elif (CAN_RX_HARDWARE_OBJECTS_MAX > 0U)
  Hfh = Hfh + Can_kConfigPtr->CanNumRxHwObj;
#elif (CAN_TX_HARDWARE_OBJECTS_MAX > 0U)
  Hfh = Hfh + Can_kConfigPtr->CanNumTxHwObj;
#endif

  /* Extract the Current Hardwareobject number, TOP and BOT of the base FIFO */
  FifoTop = 
    (uint8)((CAN_KER[KerIdx]->MO[HwObjectId].FGPR.U >> CAN_MOFGPR_TOP_SHIFT)
    & CAN_8BIT_MASK);
  FifoBottom = (uint8)(CAN_KER[KerIdx]->MO[HwObjectId].FGPR.U & CAN_8BIT_MASK);

  /* extract CurrentThreshold */
  CurrentThreshold = 
    (uint8)((CAN_KER[KerIdx]->MO[HwObjectId].FGPR.U >> CAN_MOFGPR_SEL_SHIFT)
    & CAN_8BIT_MASK);

  if((CurrentThreshold - FifoBottom ) < Threshold)
  { 
    Temp = Threshold -(CurrentThreshold - FifoBottom);
    CurrentHardwareObject = (FifoTop - Temp)+ CAN_ONE;
  }
  else
  {
    CurrentHardwareObject = CurrentThreshold - Threshold;
  }

  /* FifoTop & FifoBottom values are stored in the FifoTopBot variable
  to reduce the number of input parameters to the Can_lRxFifoExtractData
  function */

  FifoTopBot = 
  (uint16)((uint16)((uint16)FifoTop << CAN_EIGHT)|(uint16)FifoBottom);

  /* Extract data from the message object */
  Can_lRxFifoExtractData(FifoTopBot, CurrentHardwareObject, 
    HwControllerId,Hfh, Threshold);

  /* Calculate new threshold */
  NewThreshold = CurrentThreshold + Threshold;

  /* If NewThreshold is beyond TOP, reset it as per circuler linked list */
  if(NewThreshold > FifoTop)
  {
    Temp = FifoTop - CurrentThreshold ;      
    NewThreshold = FifoBottom + ((Threshold -Temp)-CAN_ONE);
  } 

  /* Update new threshold */
  CAN_KER[KerIdx]->MO[HwObjectId].FGPR.B.SEL = NewThreshold;
}
#endif /* #if (CAN_NUM_RX_FIFO_MAX > 0U) */

#if (CAN_NUM_RX_FIFO_MAX > 0U)
/*******************************************************************************
** Syntax           : IFX_LOCAL_INLINE void Can_lRxFifoExtractData            **
**                                       (                                    **
**                                          uint16 FifoTopBot,                **
**                                          uint8 CurrentMo,                  **
**                                          uint8 HwControllerId,             **
**                                          uint8 Hfh,                        **
**                                          uint8 Threshold                   **
**                                        )                                   **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : FifoTop - FIFO Top Message Object                       **
**                    FifoBottom - FIFO Bottom Message Object                 **
**                    CurrentMo - Associated Message Object                   **
**                    Hfh - Hardware FIFO Handler                             **
**                    Threshold - Receive FIFO Threshold                      **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : This function extracts data from the message object     **
**                    and notifies upper layer                                **
**                                                                            **
*******************************************************************************/
IFX_LOCAL_INLINE void Can_lRxFifoExtractData(uint16 FifoTopBot,
                                         uint8 CurrentMo,
                                         uint8 HwControllerId,
                                         uint16 Hfh,
                                         uint8 Threshold)
{
  volatile uint8 *MoData;
  Can_IdType MessageId;
  uint8 MoDataIndex;
  uint8 MessageDlc;
  uint8 Count;
  uint8 KerIdx;
  uint8 FifoTop;
  uint8 FifoBottom;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);

  /* Extract the FifoTop & FifoBottom values from FifoTopBot */
  FifoBottom = (uint8)(FifoTopBot & CAN_8BIT_MASK);
  FifoTop = (uint8)((uint8)(FifoTopBot >> CAN_EIGHT) & CAN_8BIT_MASK);

  for (Count = CAN_ZERO; Count < Threshold; Count++)
  {
    /* Extract the Message Id of the Current Message Object */ 
#if (CAN_STANDARD_ID_ONLY == STD_OFF) 

    /*  Extended frame */
    if (CAN_KER[KerIdx]->MO[CurrentMo].AR.B.IDE == CAN_ONE) 
    {
      /* Extract Message Id and set MSBit */
      MessageId = (Can_IdType)
        (CAN_KER[KerIdx]->MO[CurrentMo].AR.B.ID) | CAN_EXTENDED_MSB_SET;
    }
    else 

      /* Standard frame */
#endif /* #if (CAN_STANDARD_ID_ONLY == STD_OFF)  */
    {
      MessageId = (uint32)CAN_KER[KerIdx]->MO[CurrentMo].AR.B.ID >> 
        CAN_MOAR_ID_STD_SHIFT ;
    }

    /* Extract DLC */
    MessageDlc = (uint8) CAN_KER[KerIdx]->MO[CurrentMo].FCR.B.DLC;

    if(MessageDlc > CAN_EIGHT)
    {
      MessageDlc = CAN_EIGHT;
    }

    /* Extract Recived message Data */
    /*IFX_MISRA_RULE_11_05_STATUS= To efficiently access the SFR's 
      uint32* is typecasted to unit8* via void pointer */
    MoData = (volatile uint8 *)(void *)&CAN_KER[KerIdx]->MO[CurrentMo].DATAL.U;

    for(MoDataIndex=0U;MoDataIndex<MessageDlc;MoDataIndex++)
    {
      /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
      Can_RxFifoMessageData[HwControllerId][MoDataIndex] = MoData[MoDataIndex];
    }

    /* Notify the upper layer */
    CanIf_RxIndication((Can_HwHandleType)Hfh,
      MessageId, 
      MessageDlc, 
      &Can_RxFifoMessageData[HwControllerId][CAN_ZERO]);

    CurrentMo++;

    /* If CurrentMo goes beyond TOP, Set CurrentMo to FifoBottom */
    if(CurrentMo > FifoTop)
    {
      CurrentMo = FifoBottom;
    }
  }/* End of for loop */

}
#endif /* #if (CAN_NUM_RX_FIFO_MAX > 0U) */

#if (CAN_CHANGE_BAUDRATE_API == STD_ON)
/*******************************************************************************
** Syntax           : static uint8 Can_lSearchBaudrate                        **
**                          (                                                 **
**                            uint8 Controller,                               **
**                            const uint16 Baudrate                           **
**                          )                                                 **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : Controller - Associated CAN Controller                  **
**                    Baudrate - Baudrate to be checked                       **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : uint8 : Baudrate configuration index                    **
**                                                                            **
** Description      : Checks if the CAN Controller Baudrate is configured or  **
**                    not                                                     **
**                                                                            **
*******************************************************************************/
static uint8 Can_lSearchBaudrate(uint8 Controller, const uint16 Baudrate)
{
  const Can_17_MCanP_ControllerBaudrateConfigType *BaudrateCfgPtr;
  const Can_BaudrateConfigPtrType *CanBaudrateCfgPtr;
  uint8 BaudrateCfgIndex;
  uint8 BreakLoop;

  BaudrateCfgIndex = CAN_ZERO;
  BreakLoop = CAN_ZERO;

  /* Get the baudrate configuration index */
  CanBaudrateCfgPtr = Can_kConfigPtr->CanBaudrateConfigPtr;
  /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
  CanBaudrateCfgPtr += Controller;

  while((BaudrateCfgIndex < Can_kConfigPtr->CanNumBaudrateCfgs[Controller]) &&
    (BreakLoop == CAN_ZERO))
  {
    BaudrateCfgPtr = CanBaudrateCfgPtr->Can_kBaudrateConfigPtr;
    /*IFX_MISRA_RULE_17_04_STATUS=Pointer arithmetic used due to 
        PBConfigStructure and is within allowed range.*/
    BaudrateCfgPtr += BaudrateCfgIndex;

    /* check if baudrate is configured */
    if(BaudrateCfgPtr->CanControllerBaudrateCfg == Baudrate)
    {
      BreakLoop = CAN_ONE;
    }
    else
    {
      BaudrateCfgIndex++;
    }
  }

  return (BaudrateCfgIndex);
}
#endif

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN419]                                **
**                                                                            **
** Syntax           : static void Can_lSetBaudrate                            **
**                                               (                            **
**                                                 uint8 HwControllerId,      **
**                                                 uint32 ControllerBaudrate  **
**                                               )                            **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : ControllerId - CAN Controller Id                        **
**                    ControllerBaudrate - Register setting corresponding     **
**                                         to the baudrate                    **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : None                                                    **
**                                                                            **
** Description      : Initializes the Node Bit Timing Register                **
**                                                                            **
*******************************************************************************/
static void Can_lSetBaudrate(uint8 HwControllerId, 
                             uint32 ControllerBaudrate)
{
  uint8 KerIdx;
  uint8 HwCtrlIDKer;

  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);
  HwCtrlIDKer = CAN_CALC_HWCTRLID(HwControllerId);

  /* 
  - Enable Configuration Change - NBTR, NPCR, NECNT can be written
  - Take controller out of CAN traffic i.e put it in "stopped" state 
  - Enable Alert Interrupt. Used to detect bus off 
  */ 
  CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.CCE = CAN_ONE ;

  /* Set Node Bit Timing value */
  CAN_KER[KerIdx]->N[HwCtrlIDKer].BTR.U = ControllerBaudrate ;

  /* Disable Configuration Change - NBTR, NPCR, NECNT can only be read */
  CAN_KER[KerIdx]->N[HwCtrlIDKer].CR.B.CCE = CAN_ZERO ; 
}

/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN280]                                **
**                                                                            **
** Syntax           : static Std_ReturnType Can_lAllocateHwObject             **
**                                          (                                 **
**                                            uint8 AssociatedController,     **
**                                            uint8 HwObjectId                **
**                                          )                                 **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Non-Reentrant                                           **
**                                                                            **
** Parameters (in)  : AssociatedController - CAN Controller Id                **
**                    HwObjectId - Message Object Id                          **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: Message object allocation successful            **
**                    - E_NOT_OK: Message object allocation failed            **
**                                                                            **
** Description      : Allocates the Message Object to corresponding CAN       **
**                    CAN Controller List                                     **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_lAllocateHwObject(uint8 HwControllerId, 
                                            uint8 HwObjectId)
{
  uint32 TimeOutIndex;
  Std_ReturnType RetVal;
  uint8 TempPanar2;
  uint8 KerIdx;

  RetVal = E_OK;
  /* Calculate to which kernel, the controller belongs to*/
  KerIdx = CAN_CALC_KERIDX(HwControllerId);

  /* Give command to allocate the hardware object to its associated controller
  Note: Controller 0 ==> List 1 and Controller 1 ==> List 2 */
  TempPanar2 = (CAN_CALC_HWCTRLID(HwControllerId)) + CAN_ONE;
  CAN_KER[KerIdx]->PANCTR.B.PANAR2 = TempPanar2;
  CAN_KER[KerIdx]->PANCTR.B.PANAR1 = HwObjectId;
  CAN_KER[KerIdx]->PANCTR.B.PANCMD = CAN_PANCMD_STATIC_ALLOCATE;

  /* Wait until hardware object is allocated to the controller */
  TimeOutIndex = CAN_TIMEOUT_DURATION;

#ifdef IFX_CAN_DEBUG02
  while (((CAN_KER[KerIdx]->PANCTR.B.BUSY | TestCan_lAllocateHwObject()) == 
    CAN_ONE) && (TimeOutIndex != CAN_ZERO))
#else
  while ((CAN_KER[KerIdx]->PANCTR.B.BUSY == CAN_ONE) 
    && (TimeOutIndex != CAN_ZERO))
#endif
  {
    TimeOutIndex-- ;
  }

  /* The detection of production code errors cannot be switched off. 
  This requirement will be violated in case of HIS requirements */    
  if (TimeOutIndex == CAN_ZERO)
  {
    /* Report hardware errors and failures to DEM */
#if (CAN_E_TIMEOUT_DEM_REPORT == CAN_ENABLE_DEM_REPORT)
    Dem_ReportErrorStatus((Dem_EventIdType)CAN_E_TIMEOUT, 
      DEM_EVENT_STATUS_FAILED);
#endif

    RetVal = E_NOT_OK;
  }
  return(RetVal);
}

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** TRACEABILITY: [cover parentID=DS_AS_CAN089]                                **
**                                                                            **
** Syntax       : static Std_ReturnType Can_lReportDetUninit(uint8 ServiceId) **
**                                                                            **
**                    [/cover]                                                **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : ServiceId - Service Id of the calling API               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: CAN Driver is initialized                       **
**                    - E_NOT_OK: CAN Driver is not initialized               **
**                                                                            **
** Description      : Checks the status of CAN driver initialization          **
**                    If CAN driver is not initialized, reports to DET        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_lReportDetUninit(uint8 ServiceId)
{
  Std_ReturnType RetVal;
  RetVal = E_OK;

  /* Check if CAN driver is un-initialized */
  if(CAN_DS_UNINIT == Can_17_MCanP_DriverState)
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      ServiceId, CAN_E_UNINIT);
    RetVal = E_NOT_OK;
  }

  return(RetVal);
}
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */

#if (CAN_DEV_ERROR_DETECT == STD_ON)
/*******************************************************************************
** Syntax           : static Std_ReturnType Can_lReportDetParamController     **
**                                                      (                     **
**                                                        uint8 ControllerId, **
**                                                        uint8 ServiceId     **
**                                                      )                     **
**                                                                            **
**                                                                            **
** Service ID       : None                                                    **
**                                                                            **
** Sync/Async       : Synchronous                                             **
**                                                                            **
** Reentrancy       : Reentrant                                               **
**                                                                            **
** Parameters (in)  : ControllerId - Associated CAN Controller Id             **
**                    ServiceId - Service Id of the calling API               **
**                                                                            **
** Parameters (out) : None                                                    **
**                                                                            **
** Return value     : Std_ReturnType                                          **
**                    - E_OK: ControllerId is valid                           **
**                    - E_NOT_OK: ControllerId is invalid                     **
**                                                                            **
** Description      : Checks if ControllerId is a valid CAN Controller Id     **
**                    If ControllerId is not valid, then report to DET        **
**                                                                            **
*******************************************************************************/
static Std_ReturnType Can_lReportDetParamController(uint8 ControllerId,
                                                    uint8 ServiceId)
{
  Std_ReturnType RetVal;

  /* 'ControllerId' is out of range */
  if(ControllerId >= Can_kConfigPtr->CanNumController)
  {
    RetVal = E_NOT_OK ; 
  }
  /* Check if corresponding CAN controller is not activated */
  else if(CAN_INVALID_HW_CONTROLLER_ID == 
    Can_kConfigPtr->CanHwControllerIdMap[ControllerId])
  {
    RetVal = E_NOT_OK ; 
  }
  else
  {
    RetVal = E_OK;
  }

  if(E_NOT_OK == RetVal)
  {
    /* Report to DET */
    Det_ReportError(CAN_17_MCANP_MODULE_ID, CAN_17_MCANP_INSTANCE_ID, 
      ServiceId, CAN_E_PARAM_CONTROLLER); 
  }

  return(RetVal);
}
#endif /* #if (CAN_DEV_ERROR_DETECT == STD_ON) */

#define CAN_17_MCANP_STOP_SEC_CODE
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directive is
 allowed only for MemMap.h*/
#include "MemMap.h"
