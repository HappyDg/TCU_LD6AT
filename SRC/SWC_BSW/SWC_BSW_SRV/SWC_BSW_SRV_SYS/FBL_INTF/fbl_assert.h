/***********************************************************************************************************************
 *  FILE DESCRIPTION
 *  ------------------------------------------------------------------------------------------------------------------*/
/** \file
 *  \brief        System specific assertion defines
 *
 *  --------------------------------------------------------------------------------------------------------------------
 *  COPYRIGHT
 *  --------------------------------------------------------------------------------------------------------------------
 *  \par Copyright
 *  \verbatim
 *  Copyright (c) 2015 by Vector Informatik GmbH.                                                  All rights reserved.
 *
 *                This software is copyright protected and proprietary to Vector Informatik GmbH.
 *                Vector Informatik GmbH grants to you only those rights as set out in the license conditions.
 *                All other rights remain with Vector Informatik GmbH.
 *  \endverbatim
 */
/**********************************************************************************************************************/

/***********************************************************************************************************************
 *  AUTHOR IDENTITY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Name                          Initials      Company
 *  --------------------------------------------------------------------------------------------------------------------
 *  Christian Baeuerle            CB            Vector Informatik GmbH
 *  Armin Happel                  Hp            Vector Informatik GmbH
 *  Andre Caspari                 Ci            Vector Informatik GmbH
 *  Markus Feninger               Fr            Vector Informatik GmbH
 *  Marco Riedl                   Rie           Vector Informatik GmbH
 *  Ralf Haegenlaeuer             HRf           Vector Informatik GmbH
 *  --------------------------------------------------------------------------------------------------------------------
 *  REVISION HISTORY
 *  --------------------------------------------------------------------------------------------------------------------
 *  Version    Date        Author  Change Id        Description
 *  --------------------------------------------------------------------------------------------------------------------
 *  01.00.00   2007-08-02  Hp                       Creation
 *  01.01.00   2011-01-13  CB                       Added kFblSysAssertServiceMainHandlerInvalid and
 *                                                  kFblSysAssertRepeatedCallOnConcludedService
 *  01.02.00   2014-05-28  Ci                       Converted to normal include file
 *                                                  Added include for OEM specific assertion defines
 *  02.46.00   2015-03-06  Fr                       Adapted version to match fbl_def.h
 *                                                  Added CW specific assertion defines and
 *                                                  kFblSysAssertInitializationFailed
 *  02.47.00   2015-03-13  Rie     ESCAN00081579    No changes
 *  02.48.00   2015-04-16  HRf     ESCAN00082470    No changes
 *  02.49.00   2015-04-16  CB      ESCAN00082486    No changes
 **********************************************************************************************************************/

/***********************************************************************************************************************
 *  DEFINITION OF ASSERTION CODES (SYSTEM)
 **********************************************************************************************************************/

/* Note: System assertions are only allowed in the range from 0x00-0x7F. Others are reserved. */

/* 0x00-0x1F: General FBL assertions */
#define kFblSysAssertMissingForcedRCRRP               0x00u

#define kFblSysAssertInitializationFailed             0x10u

/* 0x20-0x3F: Internal assertions */
#define kFblSysAssertServiceReqBeforeResp             0x20u
#define kFblSysAssertServiceMainHandlerInvalid        0x21u

/* 0x40-0x4F: Generated data assertions */
#define kFblSysAssertWdBufferOverflow                 0x40u

/* 0x50-0x6F: User parameter assertions */
#define kFblSysAssertParameterOutOfRange              0x50u

#define kFblSysAssertRepeatedCallOnConcludedService   0x60u

/* 0x70-0x7F: Communication wrapper assertions */
#define kFblSysAssertStateNotIdle                     0x70u
#define kFblSysAssertNoBufferAvailable                0x71u

/* 0x80-0xFF: OEM specific */
//MATW - Start
//#include "fbl_assert_oem.h"
//MATW - End
/***********************************************************************************************************************
 *  END OF FILE: FBL_ASSERT.H
 **********************************************************************************************************************/
