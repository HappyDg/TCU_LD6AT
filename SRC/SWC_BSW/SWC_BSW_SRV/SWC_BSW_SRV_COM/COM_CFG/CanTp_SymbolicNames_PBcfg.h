/**
 * \file
 *
 * \brief AUTOSAR CanTp
 *
 * This file contains the implementation of the AUTOSAR
 * module CanTp.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if(!defined CANTP_SYMBOLICNAMES_PBCFG_H)
#define CANTP_SYMBOLICNAMES_PBCFG_H

/*==================[includes]==============================================*/

/*==================[macros]================================================*/

/* Generate macros for CanTpRxNSdus */

/*------------------------ PhyCanTpRxNSdu_0---------------------------------- */

/** \brief Export symbolic name value for Dcm_Physical_PhyCanTpRxNSdu_0 */
#define CanTpConf_CanTpRxNSdu_PhyCanTpRxNSdu_0   0U

#if(!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define Dcm_Physical_PhyCanTpRxNSdu_0             0U
/** \brief Export symbolic name value with module abbreviation as prefix only 
 *         (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)
 */
#define CanTp_Dcm_Physical_PhyCanTpRxNSdu_0       0U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Export symbolic name value for Dcm_Physical_PhyCanTpRxNSdu_0_CanTpRxNPdu */
#define CanTpConf_Dcm_Physical_PhyCanTpRxNSdu_0_CanTpRxNPdu  0U

#if (!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4)        */
#define Dcm_Physical_PhyCanTpRxNSdu_0_CanTpRxNPdu             0U
/** \brief Export symbolic name value with module abbreviation as prefix only 
           (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)                               */
#define CanTp_Dcm_Physical_PhyCanTpRxNSdu_0_CanTpRxNPdu       0U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Export symbolic name value for Dcm_Physical_PhyCanTpRxNSdu_0_CanTpTxFcNPdu */
#define CanTpConf_Dcm_Physical_PhyCanTpRxNSdu_0_CanTpTxFcNPdu   1U

#if (!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4)        */
#define Dcm_Physical_PhyCanTpRxNSdu_0_CanTpTxFcNPdu             1U
/** \brief Export symbolic name value with module abbreviation as prefix only 
           (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)                               */
#define CanTp_Dcm_Physical_PhyCanTpRxNSdu_0_CanTpTxFcNPdu       1U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/*------------------------ Dcm_Func_Rx_CanTpRxNSdu---------------------------------- */

/** \brief Export symbolic name value for Dcm_Functional_Dcm_Func_Rx_CanTpRxNSdu */
#define CanTpConf_CanTpRxNSdu_Dcm_Func_Rx_CanTpRxNSdu   1U

#if(!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define Dcm_Functional_Dcm_Func_Rx_CanTpRxNSdu             1U
/** \brief Export symbolic name value with module abbreviation as prefix only 
 *         (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)
 */
#define CanTp_Dcm_Functional_Dcm_Func_Rx_CanTpRxNSdu       1U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Export symbolic name value for Dcm_Functional_Dcm_Func_Rx_CanTpRxNSdu_CanTpRxNPdu */
#define CanTpConf_Dcm_Functional_Dcm_Func_Rx_CanTpRxNSdu_CanTpRxNPdu  1U

#if (!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4)        */
#define Dcm_Functional_Dcm_Func_Rx_CanTpRxNSdu_CanTpRxNPdu             1U
/** \brief Export symbolic name value with module abbreviation as prefix only 
           (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)                               */
#define CanTp_Dcm_Functional_Dcm_Func_Rx_CanTpRxNSdu_CanTpRxNPdu       1U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */


/* generate macros for CanTpTxNSdus */


/*------------------------ Dcm_Phys_Tx_CanTpTxNSdu---------------------------------- */

/** \brief Export symbolic name value for Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu */
#define CanTpConf_CanTpTxNSdu_Dcm_Phys_Tx_CanTpTxNSdu           0U

#if(!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu                     0U
/** \brief Export symbolic name value with module abbreviation as prefix only 
 *         (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)
 */
#define CanTp_Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu               0U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Export symbolic name value for Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpRxFcNPdu */
#define CanTpConf_Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpRxFcNPdu  0U

#if (!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4)        */
#define Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpRxFcNPdu            0U
/** \brief Export symbolic name value with module abbreviation as prefix only 
           (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)                               */
#define CanTp_Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpRxFcNPdu      0U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/** \brief Export symbolic name value for Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpTxNPdu */
#define CanTpConf_Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpTxNPdu   0U

#if (!defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4)        */
#define Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpTxNPdu             0U
/** \brief Export symbolic name value with module abbreviation as prefix only 
           (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2)                               */
#define CanTp_Dcm_Physical_Dcm_Phys_Tx_CanTpTxNSdu_CanTpTxNPdu       0U
#endif /* !defined CANTP_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( CANTP_SYMBOLICNAMES_PBCFG_H ) */
/*==================[end of file]===========================================*/
