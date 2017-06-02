
/*
 * Misra-C:2004 Deviations:
 *
 * MISRA-1) Deviated Rule: 19.13 (advisory)
 * The # and ## preprocessor operators should not be used.
 *
 * Reason:
 * ## operator is used for typename generation and improves readability
 * of code.
 *
 *
 * MISRA-2) Deviated Rule: 19.12 (required)
 * There shall be at most one occurrence of the # or ## preprocessor
 * operators in a single macro definition.
 *
 * Reason:
 * Each usage of ## is enclosed by braces and therefore the
 * concatenated macro does not depend on the order of concatenation.
 *
 */

#if (!defined COM_GENAPI_H)
#define COM_GENAPI_H

/**
 * \file
 *
 * \brief AUTOSAR Com
 *
 * This file contains the implementation of the AUTOSAR
 * module Com.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/** @} doxygen end group definition */
#endif /* if !defined( COM_GENAPI_H ) */
/*==================[end of file]===========================================*/
