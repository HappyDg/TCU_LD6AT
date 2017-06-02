/******************************************************************************
**                                                                           **
** Copyright (C) Infineon Technologies (2014)                                **
**                                                                           **
** All rights reserved.                                                      **
**                                                                           **
** This document contains proprietary information belonging to Infineon      **
** Technologies. Passing on and copying of this document, and communication  **
** of its contents is not permitted without prior written authorization.     **
**                                                                           **
*******************************************************************************
**                                                                           **
**  $FILENAME   : Gtm.h $                                                    **
**                                                                           **
**  $CC VERSION : \main\dev_tc23x\8 $                                        **
**                                                                           **
**  $DATE       : 2015-06-02 $                                               **
**                                                                           **
**  AUTHOR      : DL-AUTOSAR-Engineering                                     **
**                                                                           **
**  VENDOR      : Infineon Technologies                                      **
**                                                                           **
**  DESCRIPTION : This file contains                                         **
**                functionality of <> driver.                                **
**                                                                           **
**  MAY BE CHANGED BY USER [yes/no]: No                                      **
**                                                                           **
******************************************************************************/

/*  TRACEABILITY:
[cover parentID=DS_NAS_GTM_PR128,SAS_NAS_ALL_PR746,DS_NAS_GTM_PR748]
[/cover]
*/

#ifndef GTM_H
#define GTM_H

/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/
  /* Include Standard Types */
#include "Std_Types.h"

/* Include sfr file */
#include "IfxGtm_reg.h"

/* Inclusion of Module configuration file */
#include "Gtm_Cfg.h"

/* Global functions like Set/Reset END INIT protection bit,
  Enable/Disable interrupts, Atomic write function */
#include "Mcal.h"

/* MISRA Rule Violation 19.1, 19.15, 3.4:
   a) Header file 'MemMap.h' repeatedly included but does not have a standard
      include guard. Memmap.h file is prepared according to Autosar rules and
      this cannot be avoided.
   b) Unrecognized pragma 'section' will be ignored. Linker specific keywords.
*/


/* MISRA Rule Violation 11.3:
   SFR file has address(unsigned int) to Sfr type conversion. This causes
   MISRA violation 11.3. This cannot be avoided.*/


/*******************************************************************************
**                      Global Macro Definitions                              **
*******************************************************************************/

#define GTM_VALUE_ZERO (0U)
#define GTM_ONE (1)
#define GTM_ZERO (0)

#define GTM_ZERO_U (0U)
#define GTM_ONE_U (1U)
#define GTM_TWO_U (2U)
#define GTM_SIXTEEN_U (16U)
#define GTM_EIGHT_U (8U)
#define GTM_THREE_UL (3UL)

/* These defines are used for the TIMUsage element in Gtm_TimConfigType  */
#define GTM_DRIVER_COMPLEX (0U)
#define GTM_DRIVER_ICU     (1U)
#define GTM_DRIVER_GPT     (2U)
#define GTM_DRIVER_PWM     (3U)
#define GTM_DRIVER_PWM_MOD     (1U)
#define GTM_TOM_DRIVER_COMPLEX (3U)
#define GTM_TIM_DRIVER_COMPLEX (2U)

/*To indicate when GTM channel is not used by the other driver modules*/
#define GTM_TIM_CH_NOT_USEDBY_ICU    (0xFFU)
#define GTM_TOM_CH_NOT_USEDBY_GPT_PWM    (0xFFU)


/* Sleep Mode */
#define GTM_SLEEP_ENABLE  (1U)
#define GTM_SLEEP_DISABLE (0U)

/* SRE bit of SRC register */
#define GTM_BIT_SRE (10)
#define GTM_BIT_SRE_MASK (0x400U)


/* Configurable Clocks */
#define GTM_CONFIGURABLE_CLOCK_0   (0U)
#define GTM_CONFIGURABLE_CLOCK_1   (1U)
#define GTM_CONFIGURABLE_CLOCK_2   (2U)
#define GTM_CONFIGURABLE_CLOCK_3   (3U)
#define GTM_CONFIGURABLE_CLOCK_4   (4U)
#define GTM_CONFIGURABLE_CLOCK_5   (5U)
#define GTM_CONFIGURABLE_CLOCK_6   (6U)
#define GTM_CONFIGURABLE_CLOCK_7   (7U)

/* Fixed Clock */
#define GTM_FIXED_CLOCK_0 (0U)
#define GTM_FIXED_CLOCK_1 (1U)
#define GTM_FIXED_CLOCK_2 (2U)
#define GTM_FIXED_CLOCK_3 (3U)
#define GTM_FIXED_CLOCK_4 (4U)


/* To set a sub-module as not configured*/
#define GTM_SETUNUSED8  ((uint8)(((uint8)0x01)<< 7))
#define GTM_SETUNUSED32 ((uint32)(1UL << 7))


/* To derive information from the Global Channel Number Type Structure */
#define GTM_MODULE_ID_MSK  (0xC0U)
#define GTM_MODULE_NO_MSK  (0x3CU)
#define GTM_TGC_NO_MSK  (0x03U)

#define GTM_MODULE_ID_POS  (6U)
#define GTM_MODULE_NO_POS  (2U)
#define GTM_TGCAGC_NO_POS  (0U)

#define GTM_TOM_SL_POS     (11)
#define GTM_TOM_OSM_POS    (26)
#define GTM_ACTTB_TBTRIG_POS (24)



#define GTM_SET_BIT (1UL)
#define GTM_TIM_CH_TO_EN_BIT (0x40000000UL)
#define GTM_UPPER_HALFWORD (16U)
#define GTM_ENABLE_CLK (2UL)
#define GTM_CMU_BITS_PER_CLK (2U)
#define GTM_TIMER_MASK (0x00FFFFFFU)
#define GTM_CLEAR_CONTENT (0UL)
#define GTM_BIT_SET (1UL)
#define GTM_TIM_TO_BIT_RESET (0x3FFFFFFFUL)
#define GTM_ZERO_UL (0UL)
#define GTM_TIM_TOV_MASK (0x0000FF00UL)
#define GTM_TIM_TDUV_POS (0)
#define GTM_TIM_TDUV_SIZE (8)
#define GTM_TIM_TCS_MASK (0x70000000U)
#define GTM_TIM_TCS_POS (28U)
#define GTM_TIM_TOCNT_MASK (0x000000FFU)

#define GTM_TBU_CHAN_STATUS (3UL)
#define GTM_TBU_CHAN_ENABLE (2UL)
#define GTM_BITS_PER_TBU (2U)
#define GTM_TBU_BASE_MASK (0x07FFFFFFUL)
#define GTM_TIMER_VAL_200 (0x200UL)

#define GTM_TOM_TGC0_CHOSEN (8U)
#define GTM_TOM_TGC1_CHOSEN (16U)
#define GTM_TOM_ENABLE (2UL)
#define GTM_TOM_BITS_PER_CHAN (2U)
#define GTM_TOM_CHAN_DISABLE (1UL)
#define GTM_TOM_FUPD_START (16U)

#define GTM_OSM_REQUIRED (1U)
#define GTM_OSM_NOT_REQUIRED (0U)


#define GTM_TGC0 (0U)
#define GTM_TGC1 (1U)



/* Module Identification */
#define GTM_TOM  (0U)



/* Defines for API Gtm_CtrlMcsIntrpt */
#define GTM_ENABLE_INTERRUPT  (0U)
#define GTM_DISABLE_INTERRUPT (1U)

/* Defines for identifying the offsets of TGC and TOM Modules */
#define GTM_TOM_TGC_OFFSET (0x200UL)
/*#define GTM_TOM_TGC_OFFSET (0x40UL >> 2)*/
#define GTM_TOM_MODULE_OFFSET (0x800UL)
/*#define GTM_TOM_MODULE_OFFSET (0x800UL >> 2)*/
/*Check if atleast one Channel is used by GTM complex driver*/
#if ((GTM_NO_OF_TIM_CH_CONF_NOTIF > 0U)  ||(GTM_NO_OF_TOM_CH_CONF_NOTIF > 0U))

#define GTM_MOD_CH_CONFIGURED (1U)

#endif

/*Check if GMT is used by atleast one driver*/
#if ((GTM_NO_OF_TOM_CH_CONF_NOTIF > 0U) ||                                    \
                                   (GTM_TOM_USED_BY_OTHER_DRIVERS == (STD_ON)))

#define GTM_TOM_MODULE_USED (STD_ON)

#endif


#if ((GTM_ICU_MODULE_USED == (STD_ON)) || (GTM_NO_OF_TIM_CH_CONF_NOTIF > 0U))

#define GTM_TIM_MODULE_USED (STD_ON)

#endif
/*******************************************************************************
                           Global Type Definitions
*******************************************************************************/

/* TOM structures added to easier the acces to BStep registers*/

  typedef volatile struct
  {
    Ifx_GTM_TOM_CH_CTRL CTRL;           /**< \brief 0, TOM Channel 0 Control
                                                           Register */
    Ifx_GTM_TOM_CH_SR0 SR0;      /**< \brief 4, TOM Channel 0 CCU0 Compare
                                    Shadow Register */
    Ifx_GTM_TOM_CH_SR1 SR1;      /**< \brief 8, TOM Channel 0 CCU1 Compare
                                     Shadow Register */
    Ifx_GTM_TOM_CH_CM0 CM0;      /**< \brief C, TOM Channel 0 CCU0 Compare
                                     Register */
    Ifx_GTM_TOM_CH_CM1 CM1;      /**< \brief 10, TOM Channel 0 CCU1 Compare
                                     Register */
    Ifx_GTM_TOM_CH_CN0 CN0;      /**< \brief 14, TOM Channel 0 CCU0
                                                            Counter Register */
    Ifx_GTM_TOM_CH_STAT STAT;    /**< \brief 18, TOM Channel Status Register */
    Ifx_GTM_TOM_CH_IRQ_NOTIFY IRQ_NOTIFY;   /**< \brief 1C, TOM Channel 0
                                            Interrupt Notification Register */
    Ifx_GTM_TOM_CH_IRQ_EN IRQ_EN;       /**< \brief 20, TOM Channel 0
                                                  Interrupt Enable Register */
    Ifx_GTM_TOM_CH_IRQ_FORCINT IRQ_FORCINT; /**< \brief 24, TOM Channel 0
                                                           Software Interrupt
                                                       Generation Register */
    Ifx_GTM_TOM_CH_IRQ_MODE IRQ_MODE;   /**< \brief 28, TOM IRQ Mode
                                                   Configuration Register */
    uint8 reserved_2C[20];    /**< \brief 2C */
  }Ifx_GTM_TOM_CH_TYPE;

  typedef volatile struct
  {
    Ifx_GTM_TOM_TGC0_GLB_CTRL GLB_CTRL;    /**< \brief 30, TOM TGC0 Global
                                                           Control Register */
    Ifx_GTM_TOM_TGC0_ACT_TB ACT_TB;    /**< \brief 34, TOM TGC0 Action Time
                                                           Base Register */
    Ifx_GTM_TOM_TGC0_FUPD_CTRL FUPD_CTRL;  /**< \brief 38, TOM TGC0 Force
                                                  Update Control Register */
    Ifx_GTM_TOM_TGC0_INT_TRIG INT_TRIG;    /**< \brief 3C, TOM TGC0 Internal
                                                 Trigger Control Register */
    uint8 reserved_tgc0[48];
    Ifx_GTM_TOM_TGC0_ENDIS_CTRL ENDIS_CTRL;    /**< \brief 70, TOM TGC0
                                             Enable/Disable Control Register */
    Ifx_GTM_TOM_TGC0_ENDIS_STAT ENDIS_STAT;    /**< \brief 74, TOM TGC0
                                              Enable/Disable Status Register */
    Ifx_GTM_TOM_TGC0_OUTEN_CTRL OUTEN_CTRL;    /**< \brief 78, TOM TGC0
                                               Output Enable Control Register */
    Ifx_GTM_TOM_TGC0_OUTEN_STAT OUTEN_STAT;    /**< \brief 7C, TOM TGC0
                                                Output Enable Status Register */
    uint8 reserved_tgc1[432];
  } Ifx_GTM_TOM_TGC_TYPE;

  typedef volatile struct
  {
    uint8 reserved_tom0[48];
    Ifx_GTM_TOM_TGC_TYPE TGC[2];
    uint8 reserved_tgc2[976];
  } Ifx_GTM_TOM_TGCx;


  typedef volatile struct
  {
    Ifx_GTM_TOM_CH_TYPE CH[16];
    uint8 reserved_tom1[1024];
   }Ifx_GTM_TOM_CHx;



  typedef volatile union
  {
      /* For Accessing TOM TGC registers */
      Ifx_GTM_TOM_TGCx TOM_TGC[GTM_NO_OF_TOM_MODULES];
      /* For Accessing TOM channels */
      Ifx_GTM_TOM_CHx TOM_CH[GTM_NO_OF_TOM_MODULES];
      /* For accessing all contents */
      Ifx_GTM_TOM TOM[GTM_NO_OF_TOM_MODULES];
  /*IFX_MISRA_RULE_18_04_STATUS= Unions are used to simplify the SFR access*/
  } Ifx_GTM_TOMx;

/*TOM structures Ends */




/* TIM structures added to easier the acces to BStep registers*/
  typedef volatile struct
  {
    Ifx_GTM_TIM_CH_GPR0 CH_GPR0; /**< \ TIM Channel 0 General
                                                       Purpose 0 Register */
    Ifx_GTM_TIM_CH_GPR1 CH_GPR1;    /**< \brief 4, TIM Channel 0
                                                General Purpose 1 Register */
    Ifx_GTM_TIM_CH_CNT CH_CNT;      /**< \brief 8, TIM Channel 0
                                                  SMU Counter Register */
    Ifx_GTM_TIM_CH_ECNT CH_ECNT;    /**< \brief C, TIM Channel 0
                                                   Edge Counter Register */
    Ifx_GTM_TIM_CH_CNTS CH_CNTS;    /**< \brief 10, TIM Channel 0
                                              SMU Shadow Counter Register */
    Ifx_GTM_TIM_CH_TDUC CH_TDUC;    /**< \brief 14, TIM Channel 0
                                                       TDUC Register */
    Ifx_GTM_TIM_CH_TDUV CH_TDUV;    /**< \brief 18, TIM Channel 0
                                                           TDUV Register */
    Ifx_GTM_TIM_CH_FLT_RE CH_FLT_RE;       /**< \brief 1C, GTM_TIM Channel 0
                                               Filter Parameter 0 Register */
    Ifx_GTM_TIM_CH_FLT_FE CH_FLT_FE;       /**< \brief 20, TIM Channel 0 Filter
                                                     Parameter 1 Register */
    Ifx_GTM_TIM_CH_CTRL CH_CTRL;    /**< \brief 24, TIM Channel 0
                                                            Control Register */
    Ifx_GTM_TIM_CH_ECTRL CH_ECTRL;      /**< \brief 28, TIM Channel 0 External
                                                   Capture Control Register */
    Ifx_GTM_TIM_CH_IRQ_NOTIFY CH_IRQ_NOTIFY;   /**< \brief 2C, TIM Channel 0
                                Interrupt Notification Register */
    Ifx_GTM_TIM_CH_IRQ_EN CH_IRQ_EN;       /**< \brief 30, TIM Channel 0
                                   Interrupt Enable Register */
    Ifx_GTM_TIM_CH_IRQ_FORCINT CH_IRQ_FORCINT; /**< \brief 34, TIM Channel 0
                                         Software Interrupt Force Register */
    Ifx_GTM_TIM_CH_IRQ_MODE CH_IRQ_MODE;   /**< \brief 38, TIM IRQ Mode
                                                Configuration Register */
    Ifx_GTM_TIM_CH_EIRQ_EN CH_EIRQ_EN;     /**< \brief 3C, TIM Channel 0
                                       Error Interrupt Enable Register */
    uint8 reserved_40[64];          /**< \brief 40 */

  }Ifx_GTM_TIM_CH_TYPE;

  typedef volatile struct
  {
    Ifx_GTM_TIM_IN_SRC IN_SRC;       /**< \brief 78, TIM_IN_SRC Long Name */
    Ifx_GTM_TIM_RST RST;             /**< \brief 7C, TIM Global Software
                                                           Reset Register */
  }Ifx_GTM_TIM_IN_SRC_RESET_TYPE;

   typedef volatile struct
  {
    Ifx_GTM_TIM_CH_TYPE CH[8];
    uint8 reserved_tim1[1024];
  }Ifx_GTM_TIM_CHx;

  typedef volatile struct
  {
      uint8 reserved_tim2[120];
      Ifx_GTM_TIM_IN_SRC_RESET_TYPE IN_SRC_RESET;
      uint8 reserved_tim3[1920];
  }Ifx_GTM_TIM_IN_SRC_RSTx;

   typedef volatile union
   {
      /* For Accessing TIM IN_SRC and RST registers */
      Ifx_GTM_TIM_IN_SRC_RSTx IN_SRC_RST[GTM_NO_OF_TIM_MODULES];
      /* For Accessing TIM channels */
      Ifx_GTM_TIM_CHx CH_TIM[GTM_NO_OF_TIM_MODULES];
      /* For accessing all contents */
      Ifx_GTM_TIM TIM[GTM_NO_OF_TIM_MODULES];
  /*IFX_MISRA_RULE_18_04_STATUS= Unions are used to simplify the SFR access*/
  } Ifx_GTM_TIMx;
/*TIM structures ends*/





/* Enum of all the clocks */
  typedef enum
  {
    GTM_CONFIGURABLE_CLOCK0,
    GTM_CONFIGURABLE_CLOCK1,
    GTM_CONFIGURABLE_CLOCK2,
    GTM_CONFIGURABLE_CLOCK3,
    GTM_CONFIGURABLE_CLOCK4,
    GTM_CONFIGURABLE_CLOCK5,
    GTM_CONFIGURABLE_CLOCK6,
    GTM_CONFIGURABLE_CLOCK7,
    GTM_EXTERNAL_CLOCK0,
    GTM_EXTERNAL_CLOCK1,
    GTM_EXTERNAL_CLOCK2,
    GTM_FIXED_CLOCKS
  }Gtm_ClockSourceType;


/* Enum of all the configurable clocks */
  typedef enum
  {
    GTM_CONFIGURABLE_CLK0,
    GTM_CONFIGURABLE_CLK1,
    GTM_CONFIGURABLE_CLK2,
    GTM_CONFIGURABLE_CLK3,
    GTM_CONFIGURABLE_CLK4,
    GTM_CONFIGURABLE_CLK5,
    GTM_CONFIGURABLE_CLK6,
    GTM_CONFIGURABLE_CLK7
  }Gtm_ConfigurableClockType;


/* Used by Gtm_SetTomOutput function */
  typedef enum
  {
    GTM_LOW,
    GTM_HIGH
  }Gtm_OutputLevelType;


  typedef enum
  {
    TOM_GLB_CTRL,
    TOM_ACT_TB,
    TOM_FUPD_CTRL,
    TOM_INT_TRIG,
    TOM_RESERVED_0,
    TOM_RESERVED_1,
    TOM_RESERVED_2,
    TOM_RESERVED_3,
    TOM_RESERVED_4,
    TOM_RESERVED_5,
    TOM_RESERVED_6,
    TOM_RESERVED_7,
    TOM_RESERVED_8,
    TOM_RESERVED_9,
    TOM_RESERVED_10,
    TOM_RESERVED_11,
    TOM_ENDIS_CTRL,
    TOM_ENDIS_STAT,
    TOM_OUTEN_CTRL,
    TOM_OUTEN_STAT
  }Gtm_TomTimerRegistersType;


/* Type to provide the Filter Rising and Falling Edge Values */
  typedef struct
  {
    uint32 FltRisingEdge;
    uint32 FltFallingEdge;
  }Gtm_TimFilterType;

  /*********************** Memory MAP START **********************/

  /* Internal Type definition for TBU */
  typedef Ifx_GTM_TBU_CH0_CTRL Gtm_TbuChCtrlType;
  typedef Ifx_GTM_TBU_CH0_BASE Gtm_TbuChBaseType;

  typedef struct
  {
    Gtm_TbuChCtrlType CH_CTRL;          /* TBU Channel 0 Control Register*/
    Gtm_TbuChBaseType CH_BASE;          /* TBU Channel 0 Base Register   */
  }Gtm_TbuChType;

  typedef struct
  {
    Ifx_GTM_TBU_CHEN CHEN;         /* TBU Global Channel Enable Register */
    Gtm_TbuChType GtmTbuCh[GTM_NO_OF_TBU_CHANNELS];
  }Gtm_TbuType;



/*********************** Memory MAP END**********************/
/* Type for Port Configuration */
typedef struct
{
  uint32 TimInSel[GTM_NO_OF_TIM_MODULES];
  uint32 ToutSel[GTM_NO_OF_TOUTSEL_REGISTERS];
}Gtm_PortConfigType;


/* Type for Filter Configuration */
typedef struct
{
  uint32 TimRisingEdgeFilter;   /* Rising Edge Filter Value */
  uint32 TimFallingEdgeFilter;  /* Falling Edge Filter Value */

}Gtm_TimFltType;


  /* Type for TIM Configuration */
  typedef struct
  {
    uint8 TimUsage;         /* Bit coded information for TIM usage*/
    uint8  TimIrqEn;        /* Irq Enable and mode configuration  */
    uint8  TimErrIrqEn;            /* Error Irq Enable and mode
                   configuration  */
    uint8 TimExtCapSrc;            /* TIM channel External Capture Source*/
    uint32 TimCtrlValue;           /* TIM Control value           */
    const Gtm_TimFltType * GtmTimFltPtr;  /* Pointer to Filter configuration */
    uint32 TimCntsValue;           /* configured value for CNTS          */
    uint32 TimTduValue;            /* Timeout detection configuration    */
    uint32 TimInSrcSel;            /* TIM channel input source selection*/

  }Gtm_TimConfigType;

  /* Type for TIM Usage by other modules*/
  typedef struct
  {
  /*Structure to hold the information about the GTM submodules (TIM/TOM)
                                 usage by other drivers(ICU/GPT/PWM)*/

    uint8 Gtm_TimUsage[GTM_CHANNELS_PER_TIM_MODULE]; /* 1-D since only
                                    once TIM module is available for TC234*/
    uint8 Gtm_TomUsage[GTM_NO_OF_TOM_MODULES][GTM_CHANNELS_PER_TOM_MODULE];

  }Gtm_ModUsageConfigType;



/* Gpt channel status */
typedef enum
{
  GTM_GPT_CHANNEL_STARTED,
  GTM_GPT_WRONG_PARAM,
  GTM_GPT_CHANNEL_BUSY
}Gtm_GptChannelStatusType;


/* Type for TOM TGC configuration */
typedef struct
{
  uint16 GtmTomUpdateEn;      /* Update enable configured value */
  uint16 GtmTomEndisCtrl;     /* Endis Control configured value */
  uint16 GtmTomEndisStat;     /* Endis Status configured value  */
  uint16 GtmTomOutenCtrl;     /* Outen Control configured value */
  uint16 GtmTomOutenStat;     /* Outen status configured value  */
  uint32 GtmTomFupd;          /* FUPD configured value          */
}Gtm_TomTgcConfigGroupType;


/* Type for TOM TGC configuration */
typedef struct
{
  uint16 GtmTomIntTrig;     /* Internal Trigger configured value */
  uint32 GtmTomActTb;       /* ACT TB configured value    */
  /* This will be NULL_PTR if none of the channels in this TGC is
     configured for Complex Driver */
  const Gtm_TomTgcConfigGroupType * GtmTomTgcConfigGrpPtr;
}Gtm_TomTgcConfigType;

/* Type for TOM channel configuration */
typedef struct
{
  uint8 GtmTomIrqEn;          /* Interrupt Enable configured value */
  uint16 GtmTomCn0Value;      /* CN0 configured value       */
  uint16 GtmTomCm0Value;      /* CM0 configured value       */
  uint16 GtmTomCm1Value;      /* CM1 configured value       */
  uint16 GtmTomSr0Value;      /* SR0 configured value       */
  uint16 GtmTomSr1Value;      /* SR1 configured value       */
}Gtm_TomChannelConfigType;


/* Type for TOM configuration */
typedef struct
{
  uint8 TomUsage;     /* Bit coded information for TOM configuration */
  uint8 GtmTomIrqMode;       /* Interrupt Mode configured value */
  /* Only CLK and SL field will be updated when used in GPT/PWM mode */
  uint32 GtmTomControlWord;
  /* This will be NULL_PTR for Channel used by GPT/PWM */
  const Gtm_TomChannelConfigType * GtmTomChannelCfgPtr;
}Gtm_TomConfigType;


/* Type for External Clock */
typedef struct
{
  uint32  CmuEclkNum;  /* External Clock Numerator Value */
  uint32  CmuEclkDen;  /* External Clock Denominator Value */
}Gtm_ExtClkType;

/* Type for Clock Settings configuration */
typedef struct
{
  uint32 GtmClockEnable;     /* Clock Enable configured value */
  uint32 GtmCmuClkCnt[8];    /* CMU clock divider value       */
  uint32 GtmFxdClkControl; /* Fixed clock divider value  */
  Gtm_ExtClkType GtmEclk[3]; /* External clock divider value  */
}Gtm_ClockSettingType;


/* Type for General configuration */
typedef struct
{
  uint16  GtmCtrlValue;  /* Updated by GtmEnRSTAndForceIntFunctionality,
       GtmAeiTimeOutMode and GtmAeiTimeOutValue */
  uint16   GtmIrqEnable;  /* Updated by Contents of GtmAEIInterrupts . */
}Gtm_GeneralConfigType;


/* Type for TBU configuration */
typedef struct
{
  uint8  TbuChannelCtrl;  /* Lower 4 Bits - Ctrl Info.. Bit 5 - Channel Enable*/
  uint32 TbuBaseValue;    /* TBU base value */
}Gtm_TbuConfigType;


/* Type for Module configuration */
typedef struct
{
  /* Module Sleep Enable configuration */
  uint8 GtmModuleSleepEnable;
  uint32 GtmGclkNum;         /* Global Clock Numerator value     */
  uint32 GtmGclkDen;         /* Global Clock Denominator value   */
  uint32 GtmAccessEnable0;   /* Access Enable 0 configured value */
  uint32 GtmAccessEnable1;   /* Access Enable 1 configured value */
  /* Bit coded information specifies the driver that uses the channel
     2 - COMPLEX, 1- ICU */
  uint16 GtmTimModuleUsage[((GTM_MAX_TIM_CHANNELS -1U)/16U) + 1U];
  /* Bit coded information specifies if the channel is configured or not */
  uint8 GtmTimUsage[((GTM_MAX_TIM_CHANNELS -1U)/32U) + 1U];
  const Gtm_TimConfigType *GtmTimConfigPtr; /* Pointer to TIM configuration */
  /* Bit coded information specifies if the TGC is configured or not */
  uint8 GtmTomTgcUsage[(     \
    ((GTM_NO_OF_TOM_MODULES * GTM_NO_OF_TGC_PER_MODULE) - 1U)/32U\
          )+1U];
  const Gtm_TomTgcConfigType *GtmTomTgcConfigPtr ; /* Ptr to TOM TGC Config  */
  /* Bit coded information specifies the driver that uses the channel
     3 - COMPLEX, 1- PWM  2- GPT */
  uint32 GtmTomModuleUsage[((GTM_MAX_TOM_CHANNELS -1U)/16U) + 1U];
  /* Bit coded information specifies if the channel is configured or not */
  uint32 GtmTomUsage[((GTM_MAX_TOM_CHANNELS -1U)/32U) + 1U];
  const Gtm_TomConfigType *GtmTomConfigPtr; /* Pointer to TOM configuration */
  /* Pointer to GTM (TIM/TOM) usage configuration*/
  const Gtm_ModUsageConfigType *GtmModUsageConfigPtr;
  const Gtm_GeneralConfigType *GtmGeneralConfigPtr;/* Ptr to General Config  */
  /* Will be NULL_PTR if Tbu is not configured */
  const Gtm_TbuConfigType *GtmTbuConfigPtr; /* Pointer to TBU configuration*/
  /* Upper Nibble represents Trigger 1 and Lower Nibble Trigger 0 */
  const uint8 * GtmAdcConnectionsPtr;
  /* TTCAN Trigger configuration */
  uint16 GtmTtcanTriggers[((GTM_NO_OF_TTCAN_TRIGGERS - 1U)/8U) + 1U];
}Gtm_ModuleConfigType;



/* Notification Type for GTM dependent modules*/
typedef void (*Gtm_ModNotificationPtrType)(uint8 ChannelNo);

#ifdef GTM_MOD_CH_CONFIGURED
/* Notification Type for GTM complex driver configuration*/
typedef void (*Gtm_NotificationPtrType)(uint8 ModuleType, uint8 ModuleNo,
                   uint8 ChannelNo,uint16 IrqNotifVal);

/* GTM Notification configuration for TIM and TOM */
typedef struct
{
  #if (GTM_NO_OF_TIM_CH_CONF_NOTIF > 0U)
  Gtm_NotificationPtrType TimNotifUsage[GTM_NO_OF_TIM_CH_CONF_NOTIF];
  #endif
  #if (GTM_NO_OF_TOM_CH_CONF_NOTIF > 0U)
  Gtm_NotificationPtrType TomNotifUsage[GTM_NO_OF_TOM_CH_CONF_NOTIF];
  #endif
}Gtm_NotificationConfigType;

#endif




/* GTM root Configuration */
typedef struct Gtm_ConfigType
{
  const Gtm_ClockSettingType  * GtmClockSettingPtr; /* Ptr to Clock Setting */
  const Gtm_PortConfigType *GtmPortConfigPtr; /* Ptr to Port Configuration  */
  const Gtm_ModuleConfigType *GtmModuleConfigPtr; /* Module config Ptr      */
}Gtm_ConfigType;



/*******************************************************************************
**        Global Variable Declarations                                        **
*******************************************************************************/
#define MCU_START_SEC_POSTBUILDCFG
#include "MemMap.h"
/* Declaration of GTM Post Build Configuration */
extern const Gtm_ConfigType Gtm_ConfigRoot[GTM_CONFIG_COUNT];
#define MCU_STOP_SEC_POSTBUILDCFG
#include "MemMap.h"

#define GTM_START_SEC_VAR_32BIT
#include "MemMap.h"
/*IFX_MISRA_RULE_08_08_STATUS= Gtm_kConfigPtr is 
 declared extern only here and is defined in Gtm.c. This violation is 
 reported incorrectly by PC-lint tool*/
extern Gtm_ConfigType const *Gtm_kConfigPtr;
#define GTM_STOP_SEC_VAR_32BIT
#include "MemMap.h"

/*******************************************************************************
**        Global Function Declarations                                        **
*******************************************************************************/
#define GTM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Syntax : void Gtm_Init(const Gtm_ConfigType *ConfigPtr)                    **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       non reentrant                                            **
**                                                                            **
** Parameters (in):  ConfigPtr - Pointer to configuration set                 **
**                                                                            **
** Parameters (out): none                                                     **
**                                                                            **
** Return value:     none                                                     **
**                                                                            **
** Description :     This routine initializes the GTM module.                 **
**     This routine must be called before executing ICU / PWM /               **
**     GPT driver.                                                            **
**     The intention of this function is to make the                          **
**     configuration settings for GTM driver                                  **
**     also enable Interrupt Request for all resources that is                **
**     used across ICU/PWM/GPT and GTM modules.                               **
**     Clock Setting for GTM module clock and clock bus                       **
**     configuration will be done in this                                     **
**     function.                                                              **
**                                                                            **
*******************************************************************************/
extern void Gtm_Init(const Gtm_ConfigType *ConfigPtr);

#if (GTM_DEINIT_API_ENABLE == STD_ON)

/*******************************************************************************
** Syntax : void Gtm_DeInit (void)                                            **
**                                                                            **
** Service ID:    None                                                        **
**                                                                            **
** Sync/Async:    Synchronous                                                 **
**                                                                            **
** Reentrancy:    Non-reentrant                                               **
**                                                                            **
** Parameters (in):   None                                                    **
**                                                                            **
** Parameters (out):  None                                                    **
**                                                                            **
** Return value:      None                                                    **
**                                                                            **
** Description :  This service shall de-initialize GTM Module                 **
**                                                                            **
*******************************************************************************/
extern void Gtm_DeInit(void);

#endif

/*******************************************************************************
** Syntax : void Gtm_IsrTomModule(uint8 ModuleNo, uint8 ChannelNumber)        **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - TOM Module Number                             **
**     ChannelNumber - Channel number (0,2,4,6,8,10,12,14)                    **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     All TOM Interrupt sources are mapped to this function.   **
**     On an interrupt request from TOM isr, channel number and               **
**     module number are passed as parameter. Since 2 interrupt               **
**     sources are mapped  to one Interrupt node, the parameter               **
**     to this function will be an even number only.                          **
*******************************************************************************/
extern void Gtm_IsrTomModule(uint8 ModuleNo, uint8 ChannelNumber);

/*******************************************************************************
** Syntax : void Gtm_IsrTimModule(uint8 ModuleNo, uint8 ChannelNumber)        **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo: TIM Module Number                              **
**     ChannelNumber - Channel number (0 to 7)                                **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     All TIM Interrupt sources are mapped to this function.   **
**     On an interrupt request from TIM isr, channel number and               **
**     module number are passed as parameter. Notification                    **
**     function if configured, will be called                                 **
*******************************************************************************/
extern void Gtm_IsrTimModule(uint8 ModuleNo, uint8 ChannelNumber);



/*******************************************************************************
** Syntax : void Gtm_IsrTim0Channel(                                          **
**       uint8 ChannelNumber                                                  **
**       )                                                                    **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber - Channel number (0 to 7)                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     All TIM0 Interrupt sources are mapped to this function.  **
**     On an interrupt request from TIM isr, channel number is                **
**     sent as parameter.                                                     **
*******************************************************************************/
extern void Gtm_IsrTim0Channel(uint8 ChannelNumber);


/*******************************************************************************
** Syntax : void Gtm_IsrTim1Channel(                                          **
**       uint8 ChannelNumber                                                  **
**       )                                                                    **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber - Channel number (0 to 7)                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     All TIM1 Interrupt sources are mapped to this function.  **
**     On an interrupt request from TIM isr, channel number is                **
**     sent as parameter.    **
*******************************************************************************/
extern void Gtm_IsrTim1Channel(uint8 ChannelNumber);

/*******************************************************************************
** Syntax : void Gtm_IsrTim2Channel(                                         **
**                            uint8 ChannelNumber                             **
**                                   )                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber - Channel number (0 to 7)                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     All TIM2 Interrupt sources are mapped to this function.  **
**                   On an interrupt request from TIM isr, channel number is  **
**                   sent as parameter.                                       **
*******************************************************************************/
extern void Gtm_IsrTim2Channel(uint8 ChannelNumber);


/*******************************************************************************
** Syntax : void Gtm_IsrTim3Channel(                                         **
**                            uint8 ChannelNumber                             **
**                                   )                                        **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ChannelNumber - Channel number (0 to 7)                  **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     All TIM3 Interrupt sources are mapped to this function.  **
**                   On an interrupt request from TIM isr, channel number is  **
**                   sent as parameter.                                       **
*******************************************************************************/
extern void Gtm_IsrTim3Channel(uint8 ChannelNumber);


/*******************************************************************************
** Syntax : void Gtm_ModifyOutputCtrl (uint8 TimerModule, uint8 ModuleNo,     **
**          uint8 ChannelNo, boolean ToEnable)                                **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  TimerModule 0 TOM                                    **
**                   ModuleNo TOM Module Number                             **
**                   ChannelNo TOM Channel Number                           **
**                   ToEnable TRUE Enable TOM Output                     **
**                              FALSE Disable TOM Output                   **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This service enables/disables the TOM Channel output.    **
*******************************************************************************/
extern void Gtm_ModifyOutputCtrl (uint8 TimerModule, uint8 ModuleNo,
                                    uint8 ChannelNo, boolean ToEnable);

/*******************************************************************************
** Syntax          : void Gtm_InitCheck (const Gtm_ConfigType* ConfigPtr)     **
**                                                                            **
** Service ID      :    None                                                  **
**                                                                            **
** Sync/Async      :    Synchronous                                           **
**                                                                            **
** Reentrancy      :    Non Reentrant                                         **
**                                                                            **
** Parameters (in) :    ConfigPtr - Pointer to GTM Driver configuration set   **
**                                                                            **
** Parameters (out):    None                                                  **
**                                                                            **
** Return value    :    E_OK - if initialization comparison is success        **
**                      E_NOT_OK - if initialization comparison fails         **
**                                                                            **
** Description     : This routine verifies the initialization the GTM driver. **
**                                                                            **
*******************************************************************************/
Std_ReturnType Gtm_InitCheck (const Gtm_ConfigType* ConfigPtr);

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/
/* Api's for Complex Usage */
/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1092_3]
** Syntax : void Gtm_SetTomHostTrigger(uint8 ModuleNo, uint8 TgcNumber)       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - TOM Module Number (0 - 2)                     **
**                   TgcNumber - TGC number (0 - 1)                           **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This INLINE function sets the Host Trigger Bit         **
**                   corresponding to the Tgc                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTomHostTrigger(uint8 ModuleNo, 
                                                                uint8 TgcNumber)
{
     (*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_TGC[ModuleNo].                     \
                          TGC[TgcNumber].GLB_CTRL.U|= (unsigned_int)GTM_SET_BIT;
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1096_3]
** Syntax : void Gtm_SetTomCounterCn0(                                        **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo,                              **
**                              uint16 Cn0Value)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   Cn0Value - CN0 Value to write                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This INLINE function sets the value of CN0 of the TOM  **
**                   channel with the value given by Cn0Value                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTomCounterCn0(
       uint8 ModuleNo,
       uint8 ChannelNo,
       uint16 Cn0Value
      )
{
  /* Get the Channel Register Pointer */


  ((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[ModuleNo].CH[ChannelNo].CN0.U) = \
     (unsigned_int)Cn0Value;

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1098_1]
** Syntax : uint16 Gtm_GetTomCounterCn0(                                      **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     CN0 value                                                **
**                                                                            **
** Description :     This INLINE function gets the value of CN0 of the TOM  **
**                   channel.                                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint16 Gtm_GetTomCounterCn0(uint8 ModuleNo,
                                                                uint8 ChannelNo)
{
  /* Get the Channel Register Pointer */


  return((uint16)((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).                          \
      TOM_CH[ModuleNo].CH[ChannelNo].CN0.U));

}



/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1096_1]
** Syntax : void Gtm_SetTomCompareValCm0(                                     **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo,                              **
**                              uint16 Cm0Value)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   Cm0Value - CM0 Value to write                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This INLINE function sets the value of CM0 of the TOM  **
**                   channel with the value given by Cm0Value                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTomCompareValCm0(
     uint8 ModuleNo,
     uint8 ChannelNo,
     uint16 Cm0Value)
{
  /* Get the Channel Register Pointer */

  ((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[ModuleNo].CH[ChannelNo].CM0.U) =  \
     (unsigned_int)Cm0Value;

}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1098_5]
** Syntax : uint16 Gtm_GetTomCompareValCm0(                                   **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     CM0 value                                                **
**                                                                            **
** Description :     This INLINE function gets the value of CM0 of the TOM  **
**                   channel.                                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint16 Gtm_GetTomCompareValCm0(uint8 ModuleNo, 
          uint8 ChannelNo)
{
  /* Get the Channel Register Pointer */

  return((uint16)((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).     \
        TOM_CH[ModuleNo].CH[ChannelNo].CM0.U));

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1096_2]
** Syntax : void Gtm_SetTomCompareValCm1(                                     **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo,                              **
**                              uint16 Cm1Value)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   Cm1Value - CM1 Value to write                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This INLINE function sets the value of CM1 of the TOM  **
**                   channel with the value given by Cm1Value                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTomCompareValCm1(
       uint8 ModuleNo,
       uint8 ChannelNo,
       uint16 Cm1Value
         )
{
  /* Get the Channel Register Pointer */

  ((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[ModuleNo].         \
         CH[ChannelNo].CM1.U) = (uint32)Cm1Value;

}



/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1098_6]
** Syntax : uint16 Gtm_GetTomCompareValCm1(                                   **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     CM1 Value                                                **
**                                                                            **
** Description :     This INLINE function gets the value of CM1 of the TOM  **
**                   channel.                                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint16 Gtm_GetTomCompareValCm1(uint8 ModuleNo, 
          uint8 ChannelNo)
{
  /* Get the Channel Register Pointer */

  return((uint16)((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).     \
        TOM_CH[ModuleNo].CH[ChannelNo].CM1.U));

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1096_4]
** Syntax : void Gtm_SetTomShadowValSr0(                                      **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo,                              **
**                              uint16 Sr0Value)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   Sr0Value - SR0 Value to write                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This INLINE function sets the value of SR0 of the TOM  **
**                   channel with the value given by Sr0Value                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTomShadowValSr0(
    uint8 ModuleNo,
    uint8 ChannelNo,
    uint16 Sr0Value
        )
{
  /* Get the Channel Register Pointer */

  ((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[ModuleNo].CH[ChannelNo].SR0.U) = \
     (unsigned_int)Sr0Value;

}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1098_3]
** Syntax : _IFXEXTERN_ IFX_INLINE uint16 Gtm_GetTomShadowValSr0(             **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     SR0 value                                                **
**                                                                            **
** Description :     This INLINE function gets the value of SR0 of the TOM  **
**                   channel.                                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS=Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint16 Gtm_GetTomShadowValSr0(uint8 ModuleNo, 
         uint8 ChannelNo)
{
  /* Get the Channel Register Pointer */

  return((uint16)((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).     \
      TOM_CH[ModuleNo].CH[ChannelNo].SR0.U));

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1096_5]
** Syntax : _IFXEXTERN_ IFX_INLINE Gtm_SetTomShadowValSr1(                    **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo,                              **
**                              uint16 Sr1Value)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   Sr1Value - SR1 Value to write                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This INLINE function sets the value of SR1 of the TOM  **
**                   channel with the value given by Sr1Value                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTomShadowValSr1(
    uint8 ModuleNo,
    uint8 ChannelNo,
    uint16 Sr1Value
        )
{
  /* Get the Channel Register Pointer */

  ((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[ModuleNo].CH[ChannelNo].SR1.U) = \
     (unsigned_int)Sr1Value;

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1098_4]
** Syntax : uint16 Gtm_GetTomShadowValSr1(                                    **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     SR1 value                                                **
**                                                                            **
** Description :     This INLINE function gets the value of SR1 of the TOM  **
**                   channel.                                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint16 Gtm_GetTomShadowValSr1(uint8 ModuleNo, 
         uint8 ChannelNo)
{
  /* Get the Channel Register Pointer */

  return((uint16)((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).
      TOM_CH[ModuleNo].CH[ChannelNo].SR1.U));

}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1098_2]
** Syntax : Gtm_OutputLevelType Gtm_GetTomOutputState(uint8 ModuleNo,         **
**                                                    uint8 ChannelNo)        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Output state                                             **
**                                                                            **
** Description :     Inline function to get the TOM Output                    **
*******************************************************************************/
/* Channel must be enabled prior to calling this */
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE Gtm_OutputLevelType Gtm_GetTomOutputState(uint8 ModuleNo,
         uint8 ChannelNo)
{
  /* Get the Channel Register Pointer */

  /* Returns the OUT bit of the channel Status register */
  return((Gtm_OutputLevelType)\
  (((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_CH[ModuleNo].CH[ChannelNo].STAT.U) \
        & GTM_BIT_SET));

}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1100]
** Syntax : void Gtm_SetTimCounterShadowValCnts(                              **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo                               **
**                              uint32 CntsValue)                             **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   CntsValue - CNTS value to set                            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to set CNTS value of the corresponding   **
**                   TIM Channel. The Channel must either be in  TIPM or TBCM **
**                   for using this API, else there will be no effect of this **
**                   API                                                      **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTimCounterShadowValCnts(
      uint8 ModuleNo,
      uint8 ChannelNo,
      uint32 CntsValue
         )
{
  (*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].                        \
           CH[ChannelNo].CH_CNTS.U = (unsigned_int)(CntsValue & GTM_TIMER_MASK);

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1101_1]
** Syntax : uint32 Gtm_GetTimCounterShadowValCnts(                            **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to get CNTS value of the corresponding   **
**                   TIM Channel.                                             **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint32 Gtm_GetTimCounterShadowValCnts(uint8 ModuleNo,
          uint8 ChannelNo)
{

  return((uint32)(*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).
          CH_TIM[ModuleNo].CH[ChannelNo].CH_CNTS.U);
}



/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1101_2]
** Syntax : uint32 Gtm_GetTimCounterValCnt(                                   **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to get CNT value of the corresponding    **
**                   TIM Channel.                                             **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint32 Gtm_GetTimCounterValCnt(uint8 ModuleNo, 
          uint8 ChannelNo)
{
  return((uint32)((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).    \
     CH_TIM[ModuleNo].CH[ChannelNo].CH_CNT.U));
}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1101_3]
** Syntax : uint32 Gtm_GetTimGeneralPurposeRegGpr0(                           **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to get GPR0 value of the corresponding   **
**                   TIM Channel.                                             **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint32 Gtm_GetTimGeneralPurposeRegGpr0(uint8 ModuleNo,
    uint8 ChannelNo)
{
  return((uint32)((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].       \
    CH[ChannelNo].CH_GPR0.U));
}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1101_4]
** Syntax : uint32 Gtm_GetTimGeneralPurposeRegGpr1(                           **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to get GPR1 value of the corresponding   **
**                   TIM Channel.                                             **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint32 Gtm_GetTimGeneralPurposeRegGpr1(uint8 ModuleNo,
    uint8 ChannelNo)
{
  return((uint32)((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).     \
         CH_TIM[ModuleNo].CH[ChannelNo].CH_GPR1.U));
}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1102_4]
** Syntax : void Gtm_SetTimTimeoutVal(                                        **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo                               **
**                              uint8 TimeOutDuration)                        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   TimeOutDuration - value for timeout detection            **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to set the Timeout duration for the TIM  **
**                   Channel to the parameter TimeOutDuration.                **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTimTimeoutVal(
     uint8 ModuleNo,
     uint8 ChannelNo,
     uint8 TimeOutDuration
      )
{
  Mcal_SetAtomic(
  (sint32*)&((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].
   CH[ChannelNo].CH_TDUV), (sint32)(TimeOutDuration), (sint32)GTM_TIM_TDUV_POS,
          GTM_TIM_TDUV_SIZE);

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1102_2]
** Syntax : void Gtm_EnableTimTimeoutDetection(                               **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to enable Timeout detection for the TIM  **
**                   Channel.                                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_EnableTimTimeoutDetection(uint8 ModuleNo,
       uint8 ChannelNo)
{
  (*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].CH[ChannelNo].CH_CTRL.U |=
      (unsigned_int)GTM_TIM_CH_TO_EN_BIT;

}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1102_1]
** Syntax : void Gtm_DisableTimTimeoutDetection(                              **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to disable Timeout detection for the TIM **
**                   Channel.                                                 **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_DisableTimTimeoutDetection(uint8 ModuleNo,
        uint8 ChannelNo)
{
  (*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].CH[ChannelNo].\
                              CH_CTRL.U &=(unsigned_int)(GTM_TIM_TO_BIT_RESET);
}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1102_3]
** Syntax : void Gtm_SelectTimTimeoutClock(                                   **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo                               **
**                              Gtm_ConfigurableClockType ClockSource)        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                   ClockSource - Clock Source for Timeout detection         **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to select the clock source used for      **
**                   Timeout detection for the TIM Channel.                   **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SelectTimTimeoutClock(
    uint8 ModuleNo,
    uint8 ChannelNo,
    Gtm_ConfigurableClockType ClockSource
    )
{
  uint32 RegVal;
  RegVal =  (*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].
                                                        CH[ChannelNo].CH_TDUV.U;
  RegVal &= ~GTM_TIM_TCS_MASK;
  RegVal |= ((uint32)ClockSource) << GTM_TIM_TCS_POS;

  (*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].CH[ChannelNo].CH_TDUV.U =\
       (unsigned_int)RegVal;
}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1103]
** Syntax : uint8 Gtm_GetTimCurrentTimeoutVal(                                **
**                              uint8 ModuleNo,                               **
**                              uint8 ChannelNo)                              **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     TimeOut value is ticks                                   **
**                                                                            **
** Description :     Inline function to return the current Timeout value for  **
**                   Timeout detection for the TIM Channel.                   **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint8 Gtm_GetTimCurrentTimeoutVal(uint8 ModuleNo,
      uint8 ChannelNo)
{

  return((uint8)(((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).    \
  CH_TIM[ModuleNo].CH[ChannelNo].CH_TDUC.U & GTM_TIM_TOCNT_MASK) ));
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1106_1]
** Syntax : void Gtm_EnableTbuChannel(uint8 TbuChannelNo)                     **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  TbuChannelNo - TBU Channel Number                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to enable the TBU Channel.               **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_EnableTbuChannel(uint8 TbuChannelNo)
{
  if(TbuChannelNo < GTM_NO_OF_TBU_CHANNELS)
  {
    GTM_TBU_CHEN.U |=  \
    (unsigned_int)(GTM_TBU_CHAN_ENABLE << (TbuChannelNo * GTM_BITS_PER_TBU));
  }
  else
  {
    /* Do Nothing */
  }
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1106_2]
** Syntax : void Gtm_DisableTbuChannel(uint8 TbuChannelNo)                    **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  TbuChannelNo - TBU Channel Number                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to disable the TBU Channel.              **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_DisableTbuChannel(uint8 TbuChannelNo)
{
  if(TbuChannelNo < GTM_NO_OF_TBU_CHANNELS)
  {
    GTM_TBU_CHEN.U &= (unsigned_int)\
                  (~(GTM_TBU_CHAN_ENABLE << (TbuChannelNo * GTM_BITS_PER_TBU)));
  }
  else
  {
    /* Do Nothing */
  }
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1106]
** Syntax : boolean Gtm_GetTbuChannelStatus(uint8 TbuChannelNo)               **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  TbuChannelNo - TBU Channel Number                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     ChannelStatus - TRUE  - TBU channel is enabled           **
**                                   FALSE - TBU channel is disabled          **
**                                                                            **
** Description :     Inline function to get the enabled status of TBU Channel.**
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE boolean Gtm_GetTbuChannelStatus(uint8 TbuChannelNo)
{
  boolean ChannelStatus;
  uint8 ChannelPos;

  ChannelStatus = FALSE;
  /* Check if it is a valid TBU channel */
  if(TbuChannelNo < GTM_NO_OF_TBU_CHANNELS)
  {
    /* Extract the Channel Enable information from TBU CHEN register for
       individual channels */
    /* TbuChannelNo << 1 is done to  multiply TbuChannelNo by 2, since 2 bits
       are provided for each TBU channel */
    ChannelPos = (TbuChannelNo << 1);
    if(Mcal_Extract(GTM_TBU_CHEN.U, ChannelPos, 2U) > 0)
    {
      /* Return true if the channel is enabled */
      ChannelStatus = TRUE;
    }
  }
  else
  {
    /* Do Nothing */
  }
  return(ChannelStatus);
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1109]
** Syntax : uint32 Gtm_GetTbuTimerValue(uint8 TbuChannelNo)                   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  TbuChannelNo - TBU Channel Number                        **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     Base Timer Value                                         **
**                                                                            **
** Description :     Inline function to read the Base timer value of a TBU    **
**     Channel.       **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint32 Gtm_GetTbuTimerValue(uint8 TbuChannelNo)
{
  uint32 RetVal;


  if(TbuChannelNo < GTM_NO_OF_TBU_CHANNELS)
  {
    /* MISRA Rule Violation 11.5, 1.2 and 11.4
       Cast away const/volatile from a pointer or reference
       Unusual pointer cast (incompatible indirect types)
       cast from pointer to pointer
       Casting of TBU to Gtm_TbuType is done to change to base type of TBU
       as the type defined in SFR file is not flexible to provide an arrayed
       approach for accessing the TBU channels. */

    RetVal =((Gtm_TbuType*)&(MODULE_GTM.TBU))->GtmTbuCh[TbuChannelNo].CH_BASE.U\
    & GTM_TBU_BASE_MASK;

  }
  else
  {
    RetVal = GTM_CLEAR_CONTENT;
  }
  return(RetVal);
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1092_1]
** Syntax : void Gtm_EnableTomChannel(uint8 ModuleNo, uint8 ChannelNo)        **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel Number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to enable the TOM Channel.               **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_EnableTomChannel(uint8 ModuleNo,uint8 ChannelNo)
{
  if(ChannelNo < GTM_TOM_TGC0_CHOSEN)
  {
    (*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_TGC[ModuleNo].                     \
            TGC[GTM_TGC0].ENDIS_STAT.U =   (unsigned_int)                     \
                        (GTM_TOM_ENABLE << (GTM_TOM_BITS_PER_CHAN * ChannelNo));
  }
  else if(ChannelNo < GTM_TOM_TGC1_CHOSEN)
  {
    (*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_TGC[ModuleNo].\
                                               TGC[GTM_TGC1].ENDIS_STAT.U =   \
        (unsigned_int)(GTM_TOM_ENABLE <<  (GTM_TOM_BITS_PER_CHAN *\
                                      (ChannelNo - GTM_TOM_CHANNELS_PER_TGC)));
  }
  else
  {
    /* Do Nothing */
  }
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1092_2]
** Syntax : void Gtm_DisableTomChannel(uint8 ModuleNo, uint8 ChannelNo)       **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel Number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to disable the TOM Channel.              **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_DisableTomChannel(uint8 ModuleNo,
                                                                uint8 ChannelNo)
{
  if(ChannelNo < GTM_TOM_TGC0_CHOSEN)
  {
    (*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_TGC[ModuleNo].\
              TGC[GTM_TGC0].ENDIS_STAT.U = (unsigned_int)\
                  (GTM_TOM_CHAN_DISABLE << (GTM_TOM_BITS_PER_CHAN * ChannelNo));
  }
  else if(ChannelNo < GTM_TOM_TGC1_CHOSEN)
  {
    (*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_TGC[ModuleNo].\
                                               TGC[GTM_TGC1].ENDIS_STAT.U =   \
        (unsigned_int)(GTM_TOM_CHAN_DISABLE << \
        (GTM_TOM_BITS_PER_CHAN * (ChannelNo - GTM_TOM_CHANNELS_PER_TGC)));
  }
  else
  {
    /* Do Nothing */
  }
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1096_6]
** Syntax : void Gtm_EnableTomCoherantUpdate(uint8 ModuleNo, uint8 ChannelNo) **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - Module Number                                 **
**                   ChannelNo - Channel Number                               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     Inline function to Enable Coherant update for TOM Channel**
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_EnableTomCoherantUpdate(uint8 ModuleNo,
     uint8 ChannelNo)
{
 (*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_TGC[ModuleNo].    \
   TGC[ChannelNo/ GTM_TOM_CHANNELS_PER_TGC].GLB_CTRL.U =         \
   (unsigned_int)(GTM_TOM_ENABLE << ((GTM_TOM_BITS_PER_CHAN *        \
  (ChannelNo % GTM_TOM_CHANNELS_PER_TGC)) + GTM_TOM_FUPD_START));
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1092_5]
** Syntax : void Gtm_TrigActTimebase (uint8 TimerModule, uint8 ModuleNo,      **
**                                    uint8 GroupNo)                          **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo TOM Module Number                             **
**                   GroupNo TGC Number                                     **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This service sets Action Timebase trigger request for the**
**     corresponding TGC of the TOM module.                                   **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_TrigActTimebase (uint8 TimerModule,
                                                  uint8 ModuleNo, uint8 GroupNo)
{
  if ((TimerModule == GTM_TOM) && (GroupNo < GTM_NO_OF_TGC_PER_MODULE))
  {
      ((*(Ifx_GTM_TOMx*)(MODULE_GTM.TOM)).TOM_TGC[ModuleNo].\
         TGC[GroupNo].ACT_TB.U) |= (unsigned_int)(1UL << GTM_ACTTB_TBTRIG_POS);
  }
}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1104]
** Syntax : void Gtm_SetTimFilterThreshold (uint8 ModuleNo,uint8 ChannelNo,   **
**               uint32 FltRisingEdge, uint32 FltFallingEdge)                 **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo TIM Module Number                             **
**                   ChannelNo -> Channel Number                              **
**                   FltRisingEdge -> Filter Threshold for Rising Edge        **
**                   FltFallingEdge -> Filter Threshold for Falling Edge      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This service sets Action Timebase trigger request for the**
**     corresponding TGC of the TOM module.                                   **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_SetTimFilterThreshold (uint8 ModuleNo,
      uint8 ChannelNo,uint32 FltRisingEdge, uint32 FltFallingEdge)
{
  ((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].                        \
                                     CH[ChannelNo].CH_FLT_RE.U) = FltRisingEdge;
  ((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).CH_TIM[ModuleNo].\
                                   CH[ChannelNo].CH_FLT_FE.U) = FltFallingEdge;

}

/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1105]
** Syntax : void Gtm_GetTimFilterThreshold (uint8 ModuleNo, uint8 ChannelNo,  **
**                                          Gtm_TimFilterType* FltValuePtr)   **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo TIM Module Number                             **
**                   ChannelNo Channel Number                               **
**                   FltValuePtr->FltRisingEdge Filter Threshold for Rising **
**                                                Edge                        **
**                   FltValuePtr->FltFallingEdge Filter Threshold for       **
**                                                 Falling Edge               **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value:     None                                                     **
**                                                                            **
** Description :     This service retrieves the Filter rising and falling     **
**                   edge parameters.                                         **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE void Gtm_GetTimFilterThreshold (uint8 ModuleNo, 
     uint8 ChannelNo,Gtm_TimFilterType* FltValuePtr)
{
  /* Updates the Filter parameters in the structure FltValuePtr */
  FltValuePtr->FltRisingEdge  = ((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).\
                                   CH_TIM[ModuleNo].CH[ChannelNo].CH_FLT_RE.U);
  FltValuePtr->FltFallingEdge = ((*(Ifx_GTM_TIMx*)(MODULE_GTM.TIM)).\
                                   CH_TIM[ModuleNo].CH[ChannelNo].CH_FLT_FE.U);


}


/*******************************************************************************
** Traceability : [cover parentID=DS_NAS_GTM_PR1093,
DS_NAS_HE1_GTM_PR1095,DS_NAS_HE2_GTM_PR1095]
** Syntax : IFX_INLINE uint32 Gtm_GetTimerRegisters(                          **
**              uint8 ModuleNo,uint8 GroupNo, Gtm_TimerRegistersType RegName) **
** [/cover]                                                                   **
**                                                                            **
** Service ID:       none                                                     **
**                                                                            **
** Sync/Async:       Synchronous                                              **
**                                                                            **
** Reentrancy:       reentrant                                                **
**                                                                            **
** Parameters (in):  ModuleNo - TOM Module Number                             **
**                   GroupNo - TOM TGC number                                 **
**                   RegName - Name of the Register to be read                **
**                   ModType - 0(GTM_TOM) -  TOM Channel                      **
**                                                                            **
** Parameters (out): None                                                     **
**                                                                            **
** Return value :    RegVal - Register Value                                  **
**                                                                            **
** Description :     This service returns the register values of the requested**
**     register                                                               **
*******************************************************************************/
/*IFX_MISRA_RULE_08_05_STATUS= Allowed for IFX_INLINE functions defined in 
 header files*/
_IFXEXTERN_ IFX_INLINE uint32 Gtm_GetTomTimerRegisters( uint8 ModuleNo,
         uint8 GroupNo, Gtm_TomTimerRegistersType RegName)
{
  volatile uint32* RegPtr;
  volatile uint32 RegVal;

  RegVal = 0UL;



    /* Set the base address to the first Register of TOM TGC */
    RegPtr = (uint32*)&GTM_TOM0_TGC0_GLB_CTRL;

    /* Get the value of the Requested register by adding the Index to the base
       address */
    RegVal = *(RegPtr + ((GTM_TOM_TGC_OFFSET * GroupNo) + \
       (GTM_TOM_MODULE_OFFSET * ModuleNo) + (unsigned_int)RegName));



  return(RegVal);
}

#define GTM_STOP_SEC_CODE
#include "MemMap.h"


#endif
 /* #ifndef GTM_H */
