/*******************************************************************************
**                                                                            **
** Copyright (C) Infineon Technologies (2015)                                 **
**                                                                            **
** All rights reserved.                                                       **
**                                                                            **
** This document contains proprietary information belonging to Infineon       **
** Technologies. Passing on and copying of this document, and communication   **
** of its contents is not permitted without prior written authorization.      **
**                                                                            **
********************************************************************************
**                                                                            **
**  FILENAME  : Spi_PBCfg.c                                                   **
**                                                                            **
**  $CC VERSION : \main\84 $                                                 **
**                                                                            **
**  DATE, TIME: 2017-02-25, 10:31:51                                         **
**                                                                            **
**  GENERATOR : Build b141014-0350                                            **
**                                                                            **
**  AUTHOR    : DL-AUTOSAR-Engineering                                        **
**                                                                            **
**  VENDOR    : Infineon Technologies                                         **
**                                                                            **
**  DESCRIPTION  : SPI configuration generated out of ECU configuration       **
**                 file                                                       **
**                                                                            **
**  MAY BE CHANGED BY USER [yes/no]: no                                       **
**                                                                            **
*******************************************************************************/


/*******************************************************************************
**                      Includes                                              **
*******************************************************************************/

/* Include SPI Module File */
/* [cover parentID=DS_NAS_SPI_PR699,DS_NAS_SPI_PR709] */

#include "Spi.h"
/* Inclusion of Mcal Specific Global Header File */
#include "Mcal.h"

/*******************************************************************************
**                      Private Macro Definitions                             **
*******************************************************************************/
/*******************************************************************************
**                      Imported Compiler Switch Check                        **
*******************************************************************************/
/*******************************************************************************
**                      Private Type Definitions                              **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Declarations                         **
*******************************************************************************/
/*******************************************************************************
**                      Global Constant Definitions                           **
*******************************************************************************/
/* MISRA RULE 87 VIOLATION: Inclusion of MemMap.h in between the code can't
   be avoided as it is required for mapping global variables, constants
   and code
*/
/* Violates MISRA Required Rule 16.9,
            function identifier used without '&' or parenthisized parameter list
           when using function pointer in configurations
*/

/*
                     Container: SpiChannelConfiguration
*/
#define SPI_START_SEC_POSTBUILDCFG
/*
 * To be used for global or static constants (unspecified size)
*/
#include "MemMap.h"
/*
Configuration : Channel Configuration Constant Structure.
The IB Channels are configured first followed by EB.
*/
static const Spi_ChannelConfigType Spi_kChannelConfig0[] =
{
/* IB Channel: TLE8242_1_INIT_CH Configuration */
  {
    /*IB Channels : Number of IB Buffers*/
    /* Default Data, SPI_DEFAULT_DATA */
    (uint32)0x00000000U,
    /* Data Configuration */
    Spi_DataConfig(32U, /* Data Width */
                   SPI_DATA_MSB_FIRST), /* Transfer Start */
    (Spi_NumberOfDataType)24U,
        /* Buffer Type, SPI_CHANNEL_TYPE */
    (uint8)SPI_IB_BUFFER,
  },
/* IB Channel: TLE8242_1_CTRL_CH Configuration */
  {
    /*IB Channels : Number of IB Buffers*/
    /* Default Data, SPI_DEFAULT_DATA */
    (uint32)0x00000000U,
    /* Data Configuration */
    Spi_DataConfig(32U, /* Data Width */
                   SPI_DATA_MSB_FIRST), /* Transfer Start */
    (Spi_NumberOfDataType)228U,
        /* Buffer Type, SPI_CHANNEL_TYPE */
    (uint8)SPI_IB_BUFFER,
  },
/* IB Channel: TLE8242_1_DIAG_CH Configuration */
  {
    /*IB Channels : Number of IB Buffers*/
    /* Default Data, SPI_DEFAULT_DATA */
    (uint32)0x00000000U,
    /* Data Configuration */
    Spi_DataConfig(32U, /* Data Width */
                   SPI_DATA_MSB_FIRST), /* Transfer Start */
    (Spi_NumberOfDataType)16U,
        /* Buffer Type, SPI_CHANNEL_TYPE */
    (uint8)SPI_IB_BUFFER,
  },
/* IB Channel: TLF35584_CH Configuration */
  {
    /*IB Channels : Number of IB Buffers*/
    /* Default Data, SPI_DEFAULT_DATA */
    (uint32)0x00000000U,
    /* Data Configuration */
    Spi_DataConfig(16U, /* Data Width */
                   SPI_DATA_MSB_FIRST), /* Transfer Start */
    (Spi_NumberOfDataType)2U,
        /* Buffer Type, SPI_CHANNEL_TYPE */
    (uint8)SPI_IB_BUFFER,
  },

};

/*
                    Container: SpiJobConfiguration
*/
/* Notification Function of TLF35584_JOB is NULL_PTR */
/* Notification Function of TLE8242_1_INIT_JOB is NULL_PTR */
/* Notification Function of TLE8242_1_CTRL_JOB is NULL_PTR */
/* Notification Function of TLE8242_1_DIAG_JOB is NULL_PTR */


/*
Configuration: Channel Assignment
*/
/*Channel Assignment of Job: TLF35584_JOB*/
static const Spi_ChannelType TLF35584_JOB_ChannelLinkPtr[] =
{
  SpiConf_SpiChannel_TLF35584_CH,
  SPI_CHANNEL_LINK_DELIMITER
};
/*
Configuration: Channel Assignment
*/
/*Channel Assignment of Job: TLE8242_1_INIT_JOB*/
static const Spi_ChannelType TLE8242_1_INIT_JOB_ChannelLinkPtr[] =
{
  SpiConf_SpiChannel_TLE8242_1_INIT_CH,
  SPI_CHANNEL_LINK_DELIMITER
};
/*
Configuration: Channel Assignment
*/
/*Channel Assignment of Job: TLE8242_1_CTRL_JOB*/
static const Spi_ChannelType TLE8242_1_CTRL_JOB_ChannelLinkPtr[] =
{
  SpiConf_SpiChannel_TLE8242_1_CTRL_CH,
  SPI_CHANNEL_LINK_DELIMITER
};
/*
Configuration: Channel Assignment
*/
/*Channel Assignment of Job: TLE8242_1_DIAG_JOB*/
static const Spi_ChannelType TLE8242_1_DIAG_JOB_ChannelLinkPtr[] =
{
  SpiConf_SpiChannel_TLE8242_1_DIAG_CH,
  SPI_CHANNEL_LINK_DELIMITER
};

/*
Configuration: Job Configuration Constant Structure.
*/
static const Spi_JobConfigType Spi_kJobConfig0[] =
{

/* Job: TLF35584_JOB Configuration */
  {
   /* Job End Notification: Spi_JobEndNotification, SPI118 */
    NULL_PTR,
    /* User given name outside the naming convention */
    /* Spi_ChannelLinkPtr */
    TLF35584_JOB_ChannelLinkPtr,
    /* Baud Rate (625000 Hz) Hw configuration Parameters */
    Spi_BaudRateParams(/*TQ*/(0x1U), /*Q*/(0x3U),
              /*A*/(0x3U), /*B*/(0x1U), /*C*/(0x3U)),

    /* Time Delay Configuration */
      (uint32)Spi_DelayParams(/*IPRE*/0x00U,/*IDLE*/ 0x03U,
        /*LPRE*/0x02U, /*LEAD*/0x03U,
        /*TPRE*/0x02U, /*TRAIL*/0x03U),

    SPI_CS_HW, /* Hw CS Pin is Selected */

    /*CS Active level Polarity*/
    SPI_CS_POLARITY_LOW,

 /* Shift Clock Configuration : Clock Idle Polarity: SPI_SHIFT_CLOCK_IDLE_LEVEL,
                                  Clock Phase: SPI_DATA_SHIFT_EDGE */
    Spi_ShiftClkConfig(SPI_CLK_IDLE_LOW,
                      SPI_DATA_SHIFT_TRAIL),
   /* Job Priority escalated to Maximum as it is mapped
      to one or more non-interruptible sequence */
    SPI_JOB_PRIORITY_3,

    /* Spi HW Unit. bit[7:4]: Channel no, bit[3:0]: hw module no */
      (uint8)((uint8)SPI_QSPI_CHANNEL0 << 4U) | (SPI_QSPI2_INDEX),

    /* Channel Based Chip Select */
    (uint8)0U,
    
    /* Spi Parity Selection */
    (uint8)SPI_QSPI_PARITY_UNUSED,
    
  },
/* Job: TLE8242_1_INIT_JOB Configuration */
  {
   /* Job End Notification: Spi_JobEndNotification, SPI118 */
    NULL_PTR,
    /* User given name outside the naming convention */
    /* Spi_ChannelLinkPtr */
    TLE8242_1_INIT_JOB_ChannelLinkPtr,
    /* Baud Rate (10000000 Hz) Hw configuration Parameters */
    Spi_BaudRateParams(/*TQ*/(0x0U), /*Q*/(0x0U),
              /*A*/(0x1U), /*B*/(0x0U), /*C*/(0x2U)),

    /* Time Delay Configuration */
      (uint32)Spi_DelayParams(/*IPRE*/0x01U,/*IDLE*/ 0x05U,
        /*LPRE*/0x00U, /*LEAD*/0x05U,
        /*TPRE*/0x00U, /*TRAIL*/0x02U),

    SPI_CS_HW, /* Hw CS Pin is Selected */

    /*CS Active level Polarity*/
    SPI_CS_POLARITY_LOW,

 /* Shift Clock Configuration : Clock Idle Polarity: SPI_SHIFT_CLOCK_IDLE_LEVEL,
                                  Clock Phase: SPI_DATA_SHIFT_EDGE */
    Spi_ShiftClkConfig(SPI_CLK_IDLE_LOW,
                      SPI_DATA_SHIFT_TRAIL),
   /* Job Priority escalated to Maximum as it is mapped
      to one or more non-interruptible sequence */
    SPI_JOB_PRIORITY_3,

    /* Spi HW Unit. bit[7:4]: Channel no, bit[3:0]: hw module no */
      (uint8)((uint8)SPI_QSPI_CHANNEL12 << 4U) | (SPI_QSPI3_INDEX),

    /* Channel Based Chip Select */
    (uint8)1U,

    /* Spi Parity Selection */
    (uint8)SPI_QSPI_PARITY_UNUSED,
    
  },
/* Job: TLE8242_1_CTRL_JOB Configuration */
  {
   /* Job End Notification: Spi_JobEndNotification, SPI118 */
    NULL_PTR,
    /* User given name outside the naming convention */
    /* Spi_ChannelLinkPtr */
    TLE8242_1_CTRL_JOB_ChannelLinkPtr,
    /* Baud Rate (10000000 Hz) Hw configuration Parameters */
    Spi_BaudRateParams(/*TQ*/(0x0U), /*Q*/(0x0U),
              /*A*/(0x1U), /*B*/(0x0U), /*C*/(0x2U)),

    /* Time Delay Configuration */
      (uint32)Spi_DelayParams(/*IPRE*/0x01U,/*IDLE*/ 0x05U,
        /*LPRE*/0x00U, /*LEAD*/0x05U,
        /*TPRE*/0x00U, /*TRAIL*/0x02U),

    SPI_CS_HW, /* Hw CS Pin is Selected */

    /*CS Active level Polarity*/
    SPI_CS_POLARITY_LOW,

 /* Shift Clock Configuration : Clock Idle Polarity: SPI_SHIFT_CLOCK_IDLE_LEVEL,
                                  Clock Phase: SPI_DATA_SHIFT_EDGE */
    Spi_ShiftClkConfig(SPI_CLK_IDLE_LOW,
                      SPI_DATA_SHIFT_TRAIL),
   /* Job Priority escalated to Maximum as it is mapped
      to one or more non-interruptible sequence */
    SPI_JOB_PRIORITY_3,

    /* Spi HW Unit. bit[7:4]: Channel no, bit[3:0]: hw module no */
      (uint8)((uint8)SPI_QSPI_CHANNEL12 << 4U) | (SPI_QSPI3_INDEX),

    /* Channel Based Chip Select */
    (uint8)1U,

    /* Spi Parity Selection */
    (uint8)SPI_QSPI_PARITY_UNUSED,
    
  },
/* Job: TLE8242_1_DIAG_JOB Configuration */
  {
   /* Job End Notification: Spi_JobEndNotification, SPI118 */
    NULL_PTR,
    /* User given name outside the naming convention */
    /* Spi_ChannelLinkPtr */
    TLE8242_1_DIAG_JOB_ChannelLinkPtr,
    /* Baud Rate (10000000 Hz) Hw configuration Parameters */
    Spi_BaudRateParams(/*TQ*/(0x0U), /*Q*/(0x0U),
              /*A*/(0x1U), /*B*/(0x0U), /*C*/(0x2U)),

    /* Time Delay Configuration */
      (uint32)Spi_DelayParams(/*IPRE*/0x01U,/*IDLE*/ 0x05U,
        /*LPRE*/0x00U, /*LEAD*/0x05U,
        /*TPRE*/0x00U, /*TRAIL*/0x02U),

    SPI_CS_HW, /* Hw CS Pin is Selected */

    /*CS Active level Polarity*/
    SPI_CS_POLARITY_LOW,

 /* Shift Clock Configuration : Clock Idle Polarity: SPI_SHIFT_CLOCK_IDLE_LEVEL,
                                  Clock Phase: SPI_DATA_SHIFT_EDGE */
    Spi_ShiftClkConfig(SPI_CLK_IDLE_LOW,
                      SPI_DATA_SHIFT_TRAIL),
   /* Job Priority escalated to Maximum as it is mapped
      to one or more non-interruptible sequence */
    SPI_JOB_PRIORITY_3,

    /* Spi HW Unit. bit[7:4]: Channel no, bit[3:0]: hw module no */
      (uint8)((uint8)SPI_QSPI_CHANNEL12 << 4U) | (SPI_QSPI3_INDEX),

    /* Channel Based Chip Select */
    (uint8)1U,

    /* Spi Parity Selection */
    (uint8)SPI_QSPI_PARITY_UNUSED,
    
  }
};

/*
                     Container: Spi_SequenceConfiguration
*/
/* Notification Function of Sequence: TLF35584_SEQ */
extern void TLF35584_vidSpiEndNotification(void);
/* Notification Function of Sequence: TLE8242_INIT_SEQ is NULL_PTR */
/* Notification Function of Sequence: TLE8242_CTRL_SEQ is NULL_PTR */
/* Notification Function of Sequence: TLE8242_DIAG_SEQ is NULL_PTR */

/*
Configuration: Job Assignment
*/
/* Job Assignment of Sequence: TLF35584_SEQ */
static const Spi_JobType TLF35584_SEQ_JobLinkPtr[] =
{
  SpiConf_SpiJob_TLF35584_JOB,
  SPI_JOB_LINK_DELIMITER
};
/*
Configuration: Job Assignment
*/
/* Job Assignment of Sequence: TLE8242_INIT_SEQ */
static const Spi_JobType TLE8242_INIT_SEQ_JobLinkPtr[] =
{
  SpiConf_SpiJob_TLE8242_1_INIT_JOB,
  SPI_JOB_LINK_DELIMITER
};
/*
Configuration: Job Assignment
*/
/* Job Assignment of Sequence: TLE8242_CTRL_SEQ */
static const Spi_JobType TLE8242_CTRL_SEQ_JobLinkPtr[] =
{
  SpiConf_SpiJob_TLE8242_1_CTRL_JOB,
  SPI_JOB_LINK_DELIMITER
};
/*
Configuration: Job Assignment
*/
/* Job Assignment of Sequence: TLE8242_DIAG_SEQ */
static const Spi_JobType TLE8242_DIAG_SEQ_JobLinkPtr[] =
{
  SpiConf_SpiJob_TLE8242_1_DIAG_JOB,
  SPI_JOB_LINK_DELIMITER
};




/*
Configuration: Sequence Configuration Constant Structure.
*/
static const Spi_SequenceConfigType Spi_kSequenceConfig0[] =
{   /* Sequence: TLF35584_SEQ Configuration */
  {
    /* Spi_SeqEndNotification */
    &TLF35584_vidSpiEndNotification,
    /* User given name outside the naming convention */    /* Spi_JobLinkPtr */
    TLF35584_SEQ_JobLinkPtr,
    /* User given name outside the naming convention */
    /* Sequences that share jobs with this sequence */
    NULL_PTR,
     /* This holds the total number of jobs linked to this sequence */
    1U,
  },
  /* Sequence: TLE8242_INIT_SEQ Configuration */
  {
    /* Spi_SeqEndNotification */
    NULL_PTR,
    /* User given name outside the naming convention */    /* Spi_JobLinkPtr */
    TLE8242_INIT_SEQ_JobLinkPtr,
    /* User given name outside the naming convention */
    /* Sequences that share jobs with this sequence */
    NULL_PTR,
     /* This holds the total number of jobs linked to this sequence */
    1U,
  },
  /* Sequence: TLE8242_CTRL_SEQ Configuration */
  {
    /* Spi_SeqEndNotification */
    NULL_PTR,
    /* User given name outside the naming convention */    /* Spi_JobLinkPtr */
    TLE8242_CTRL_SEQ_JobLinkPtr,
    /* User given name outside the naming convention */
    /* Sequences that share jobs with this sequence */
    NULL_PTR,
     /* This holds the total number of jobs linked to this sequence */
    1U,
  },
  /* Sequence: TLE8242_DIAG_SEQ Configuration */
  {
    /* Spi_SeqEndNotification */
    NULL_PTR,
    /* User given name outside the naming convention */    /* Spi_JobLinkPtr */
    TLE8242_DIAG_SEQ_JobLinkPtr,
    /* User given name outside the naming convention */
    /* Sequences that share jobs with this sequence */
    NULL_PTR,
     /* This holds the total number of jobs linked to this sequence */
    1U,
  }
};

static const Spi_DmaConfigType Spi_kDmaConfig0[]=
{

  { /* QSPI0 Module Hw Dma Config */
    DMA_CHANNEL1,  /* Tx */    DMA_CHANNEL0   /* Rx */  },

  { /* QSPI1 Module Hw Dma Config */
    DMA_CHANNEL3,  /* Tx */    DMA_CHANNEL2   /* Rx */  },

  { /* QSPI2 Module Hw Dma Config */
    DMA_CHANNEL5,  /* Tx */    DMA_CHANNEL4   /* Rx */  },

  { /* QSPI3 Module Hw Dma Config */
    DMA_CHANNEL7,  /* Tx */    DMA_CHANNEL6   /* Rx */  },

};

static const Spi_HWModuleConfigType Spi_kModuleConfig0[]=
{
  /* QSPI0 Module */
  {
    SPI_0_NOT_CONFIGURED,
    SPI_0_NOT_CONFIGURED,
    NULL_PTR,
  },
  /* QSPI1 Module */
  {
    SPI_1_NOT_CONFIGURED,
    SPI_1_NOT_CONFIGURED,
    NULL_PTR,
  },
  /* QSPI2 Module */
  {
      /*Clock Settings:Sleep Control Disabled*/
      SPI_CLK_SLEEP_DISABLE,
      SPI_QSPI2_MRIS_SEL,
      &Spi_kDmaConfig0[2U],
  },
  /* QSPI3 Module */
  {
      /*Clock Settings:Sleep Control Disabled*/
      SPI_CLK_SLEEP_DISABLE,
      SPI_QSPI3_MRIS_SEL,
      &Spi_kDmaConfig0[3U],
  },
};


static const Spi_BaudrateEconType Spi_kBaudrateEcon0[]=
{
  {
    Spi_BaudRateECON(0x3U, 0x3U, 0x1U, 0x3U,
    SPI_DATA_SHIFT_TRAIL,
    SPI_CLK_IDLE_LOW,
    SPI_QSPI_PARITY_DISABLE),
    (uint8)((uint8)SPI_QSPI_CHANNEL0 << 4U) | (SPI_QSPI2_INDEX)
  },
  {
    Spi_BaudRateECON(0x0U, 0x1U, 0x0U, 0x2U,
    SPI_DATA_SHIFT_TRAIL,
    SPI_CLK_IDLE_LOW,
    SPI_QSPI_PARITY_DISABLE),
    (uint8)((uint8)SPI_QSPI_CHANNEL12 << 4U) | (SPI_QSPI3_INDEX)
  }
};

const Spi_ConfigType Spi_ConfigRoot[1U] =
{
  {
    Spi_kChannelConfig0,
    Spi_kJobConfig0,
    Spi_kSequenceConfig0,
    {
      &Spi_kModuleConfig0[0U],
      &Spi_kModuleConfig0[1U],
      &Spi_kModuleConfig0[2U],
      &Spi_kModuleConfig0[3U],
    },
    Spi_kBaudrateEcon0,
    (Spi_JobType)(sizeof(Spi_kJobConfig0) / sizeof(Spi_JobConfigType)),
    (Spi_ChannelType)(sizeof(Spi_kChannelConfig0) / \
                      sizeof(Spi_ChannelConfigType)),
    (Spi_SequenceType)(sizeof(Spi_kSequenceConfig0) / \
                                        sizeof(Spi_SequenceConfigType)),
    (uint8)(sizeof(Spi_kBaudrateEcon0) / sizeof(Spi_BaudrateEconType)),
  }
};


#define SPI_STOP_SEC_POSTBUILDCFG
/* Allows to map variables, constants and code of modules to individual
  memory sections.*/
/*IFX_MISRA_RULE_19_01_STATUS=File inclusion after pre-processor directives is
allowed only for MemMap.h*/  
#include "MemMap.h"

/*******************************************************************************
**                      Global Variable Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Constant Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Private Variable Definitions                          **
*******************************************************************************/
/*******************************************************************************
**                      Global Function Definitions                           **
*******************************************************************************/
/*******************************************************************************
**                      Private Function Definitions                          **
*******************************************************************************/
/* General Notes */
/*
SPI095: The code file structure shall not be defined within this specification
completely. At this point it shall be pointed out that the code-file structure
shall include the following file named:
- Spi_Lcfg.c – for link time and for post-build configurable parameters and
- Spi_PBcfg.c – for post build time configurable parameters.
These files shall contain all link time and post-build time configurable
parameters.
This file shall contain all link time and post-build time configurable
parameters.
For the implementation of VariantPC, the implementation stores the
pre compile time parameters that have to be defined as constants in this file.

SPI123: In this configuration, all Sequences declared are considered as Non
Interruptible Sequences. That means, their dedicated parameter
SPI_INTERRUPTIBLE_SEQUENCE (see SPI064 & SPI106) could be omitted or the
FALSE value should be used as default.

*/


