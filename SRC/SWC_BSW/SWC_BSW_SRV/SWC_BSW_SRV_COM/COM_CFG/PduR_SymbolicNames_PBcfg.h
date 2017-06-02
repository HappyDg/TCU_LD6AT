/**
 * \file
 *
 * \brief AUTOSAR PduR
 *
 * This file contains the implementation of the AUTOSAR
 * module PduR.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if (!defined PDUR_SYMBOLIC_NAMES_PBCFG_H)
#define PDUR_SYMBOLIC_NAMES_PBCFG_H

/*==================[includes]==============================================*/

/*==================[macros]================================================*/
/* -------------------- Routing path: 0 ECM1_273R */
#if (defined PduRConf_PduRSrcPdu_ECM1_273R_S)
#error PduRConf_PduRSrcPdu_ECM1_273R_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_ECM1_273R_S 0U /* SRC CanIf-LO-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECM1_273R_S)
#error ECM1_273R_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECM1_273R_S 0U

#if (defined PduR_ECM1_273R_S)
#error PduR_ECM1_273R_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_ECM1_273R_S 0U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/* PduRConf_PduRDestPdu_ECM1_273R_D not defined since it is not enabled.*/


/* -------------------- Routing path: 1 ECM2_289R */
#if (defined PduRConf_PduRSrcPdu_ECM2_289R_S)
#error PduRConf_PduRSrcPdu_ECM2_289R_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_ECM2_289R_S 1U /* SRC CanIf-LO-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECM2_289R_S)
#error ECM2_289R_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECM2_289R_S 1U

#if (defined PduR_ECM2_289R_S)
#error PduR_ECM2_289R_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_ECM2_289R_S 1U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/* PduRConf_PduRDestPdu_ECM2_289R_D not defined since it is not enabled.*/


/* -------------------- Routing path: 2 TCU1_321T */
#if (defined PduRConf_PduRSrcPdu_TCU1_321T_S)
#error PduRConf_PduRSrcPdu_TCU1_321T_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_TCU1_321T_S 0U /* SRC Com-UP-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined TCU1_321T_S)
#error TCU1_321T_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define TCU1_321T_S 0U

#if (defined PduR_TCU1_321T_S)
#error PduR_TCU1_321T_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_TCU1_321T_S 0U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_TCU1_321T_D)
#error PduRConf_PduRDestPdu_TCU1_321T_D is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_TCU1_321T_D 0U /* DEST CanIf-LO-IF */


/* -------------------- Routing path: 3 TCU2_337T */
#if (defined PduRConf_PduRSrcPdu_TCU2_337T_S)
#error PduRConf_PduRSrcPdu_TCU2_337T_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_TCU2_337T_S 1U /* SRC Com-UP-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined TCU2_337T_S)
#error TCU2_337T_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define TCU2_337T_S 1U

#if (defined PduR_TCU2_337T_S)
#error PduR_TCU2_337T_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_TCU2_337T_S 1U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_TCU2_337T_D)
#error PduRConf_PduRDestPdu_TCU2_337T_D is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_TCU2_337T_D 1U /* DEST CanIf-LO-IF */


/* -------------------- Routing path: 4 ABS1_529R */
#if (defined PduRConf_PduRSrcPdu_ABS1_529R_S)
#error PduRConf_PduRSrcPdu_ABS1_529R_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_ABS1_529R_S 2U /* SRC CanIf-LO-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ABS1_529R_S)
#error ABS1_529R_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ABS1_529R_S 2U

#if (defined PduR_ABS1_529R_S)
#error PduR_ABS1_529R_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_ABS1_529R_S 2U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/* PduRConf_PduRDestPdu_ABS1_529R_D not defined since it is not enabled.*/


/* -------------------- Routing path: 5 ABS2_545R */
#if (defined PduRConf_PduRSrcPdu_ABS2_545R_S)
#error PduRConf_PduRSrcPdu_ABS2_545R_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_ABS2_545R_S 3U /* SRC CanIf-LO-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ABS2_545R_S)
#error ABS2_545R_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ABS2_545R_S 3U

#if (defined PduR_ABS2_545R_S)
#error PduR_ABS2_545R_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_ABS2_545R_S 3U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/* PduRConf_PduRDestPdu_ABS2_545R_D not defined since it is not enabled.*/


/* -------------------- Routing path: 6 ESC1_561R */
#if (defined PduRConf_PduRSrcPdu_ESC1_561R_S)
#error PduRConf_PduRSrcPdu_ESC1_561R_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_ESC1_561R_S 4U /* SRC CanIf-LO-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ESC1_561R_S)
#error ESC1_561R_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ESC1_561R_S 4U

#if (defined PduR_ESC1_561R_S)
#error PduR_ESC1_561R_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_ESC1_561R_S 4U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/* PduRConf_PduRDestPdu_ESC1_561R_D not defined since it is not enabled.*/


/* -------------------- Routing path: 7 ECM3_609R */
#if (defined PduRConf_PduRSrcPdu_ECM3_609R_S)
#error PduRConf_PduRSrcPdu_ECM3_609R_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_ECM3_609R_S 5U /* SRC CanIf-LO-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined ECM3_609R_S)
#error ECM3_609R_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define ECM3_609R_S 5U

#if (defined PduR_ECM3_609R_S)
#error PduR_ECM3_609R_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_ECM3_609R_S 5U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/* PduRConf_PduRDestPdu_ECM3_609R_D not defined since it is not enabled.*/


/* -------------------- Routing path: 8 IP1_641R */
#if (defined PduRConf_PduRSrcPdu_IP1_641R_S)
#error PduRConf_PduRSrcPdu_IP1_641R_S is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_IP1_641R_S 6U /* SRC CanIf-LO-IF */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined IP1_641R_S)
#error IP1_641R_S is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define IP1_641R_S 6U

#if (defined PduR_IP1_641R_S)
#error PduR_IP1_641R_S is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_IP1_641R_S 6U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

/* PduRConf_PduRDestPdu_IP1_641R_D not defined since it is not enabled.*/


/* -------------------- Routing path: 9 Dcm_Phy_Tx */
#if (defined PduRConf_PduRSrcPdu_Dcm_Phy_Tx)
#error PduRConf_PduRSrcPdu_Dcm_Phy_Tx is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_Dcm_Phy_Tx 0U /* SRC Dcm-UP-TP */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dcm_Phy_Tx)
#error Dcm_Phy_Tx is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define Dcm_Phy_Tx 0U

#if (defined PduR_Dcm_Phy_Tx)
#error PduR_Dcm_Phy_Tx is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_Dcm_Phy_Tx 0U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_Dcm_Phys_Tx_CanTpTxNSdu)
#error PduRConf_PduRDestPdu_Dcm_Phys_Tx_CanTpTxNSdu is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_Dcm_Phys_Tx_CanTpTxNSdu 0U /* DEST CanTp-LO-TP */


/* -------------------- Routing path: 10 Dcm_Phy_Rx */
#if (defined PduRConf_PduRSrcPdu_Dcm_Phy_Rx)
#error PduRConf_PduRSrcPdu_Dcm_Phy_Rx is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_Dcm_Phy_Rx 0U /* SRC CanTp-LO-TP */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dcm_Phy_Rx)
#error Dcm_Phy_Rx is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define Dcm_Phy_Rx 0U

#if (defined PduR_Dcm_Phy_Rx)
#error PduR_Dcm_Phy_Rx is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_Dcm_Phy_Rx 0U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_Dcm_Phy_Rx)
#error PduRConf_PduRDestPdu_Dcm_Phy_Rx is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_Dcm_Phy_Rx 0U /* DEST Dcm-UP-TP */


/* -------------------- Routing path: 11 Dcm_Func_Rx */
#if (defined PduRConf_PduRSrcPdu_Dcm_Func_Rx)
#error PduRConf_PduRSrcPdu_Dcm_Func_Rx is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRSrcPdu_Dcm_Func_Rx 1U /* SRC CanTp-LO-TP */

#if (!defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES)
#if (defined Dcm_Func_Rx)
#error Dcm_Func_Rx is already defined
#endif
/** \brief Export symbolic name value without prefix (AUTOSAR version <= 3.1 rev4) */
#define Dcm_Func_Rx 1U

#if (defined PduR_Dcm_Func_Rx)
#error PduR_Dcm_Func_Rx is already defined
#endif
/** \brief Export symbolic name value with module abbreviation as prefix only (3.1 rev4 < AUTOSAR version <= AUTOSAR 4.0 rev2) */
#define PduR_Dcm_Func_Rx 1U
#endif /* !defined PDUR_DONT_PROVIDE_LEGACY_SYMBOLIC_NAMES */

#if (defined PduRConf_PduRDestPdu_Dcm_Func_Rx)
#error PduRConf_PduRDestPdu_Dcm_Func_Rx is already defined
#endif
/** \brief Export symbolic name value */
#define PduRConf_PduRDestPdu_Dcm_Func_Rx 1U /* DEST Dcm-UP-TP */



/* Define vendor specific destination PDU IDs of adjacent modules */
#if (defined PDUR_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES)

/* -------------------- Routing path: 0 ECM1_273R */
/* PDURSA_ECM1_273R   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_ECM1_273R 0U /* DEST Com-UP-IF */

/* -------------------- Routing path: 1 ECM2_289R */
/* PDURSA_ECM2_289R   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_ECM2_289R 1U /* DEST Com-UP-IF */

/* -------------------- Routing path: 2 TCU1_321T */
#define PDURSA_TCU1_321T 0U /* SRC Com-UP-IF */
#define PDURDA_TCU1_321T 6U /* DEST CanIf-LO-IF DIRECT */

/* -------------------- Routing path: 3 TCU2_337T */
#define PDURSA_TCU2_337T 1U /* SRC Com-UP-IF */
#define PDURDA_TCU2_337T 7U /* DEST CanIf-LO-IF DIRECT */

/* -------------------- Routing path: 4 ABS1_529R */
/* PDURSA_ABS1_529R   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_ABS1_529R 2U /* DEST Com-UP-IF */

/* -------------------- Routing path: 5 ABS2_545R */
/* PDURSA_ABS2_545R   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_ABS2_545R 3U /* DEST Com-UP-IF */

/* -------------------- Routing path: 6 ESC1_561R */
/* PDURSA_ESC1_561R   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_ESC1_561R 4U /* DEST Com-UP-IF */

/* -------------------- Routing path: 7 ECM3_609R */
/* PDURSA_ECM3_609R   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_ECM3_609R 5U /* DEST Com-UP-IF */

/* -------------------- Routing path: 8 IP1_641R */
/* PDURSA_IP1_641R   SRC CanIf-LO-IF  Not defined since the configuration does not supply this ID */
#define PDURDA_IP1_641R 6U /* DEST Com-UP-IF */

/* -------------------- Routing path: 9 Dcm_Phy_Tx */
#define PDURSA_Dcm_Phys_CanTpTxNSdu 0U /* SRC Dcm-UP-TP */
#define PDURDA_Dcm_Phys_CanTpTxNSdu 0U /* DEST CanTp-LO-TP */

/* -------------------- Routing path: 10 Dcm_Phy_Rx */
#define PDURSA_Dcm_Phys_CanTpRxNSdu 0U /* SRC CanTp-LO-TP */
#define PDURDA_Dcm_Phys_CanTpRxNSdu 0U /* DEST Dcm-UP-TP */

/* -------------------- Routing path: 11 Dcm_Func_Rx */
#define PDURSA_Dcm_Func_CanTpRxNSdu 1U /* SRC CanTp-LO-TP */
#define PDURDA_Dcm_Func_CanTpRxNSdu 1U /* DEST Dcm-UP-TP */

#endif /* defined PDUR_PROVIDE_ADJACENT_MODULE_VENDOR_SYMBOLIC_NAMES */

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

/*==================[end of file]===========================================*/
#endif /* if !defined( PDUR_SYMBOLIC_NAMES_PBCFG_H ) */
