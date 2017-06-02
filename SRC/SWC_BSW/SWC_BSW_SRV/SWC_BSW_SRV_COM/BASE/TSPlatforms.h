#if (!defined TSPLATFORMS_H)
#define TSPLATFORMS_H

/**
 * \file
 *
 * \brief AUTOSAR Platforms
 *
 * This file contains the implementation of the AUTOSAR
 * module Platforms.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */

/*==================[inclusions]=============================================*/

#include "Std_Types.h"     /* AUTOSAR standard types */
/*==================[type definitions]=======================================*/

typedef uint16 TS_IntStatusType;

/*==================[macros]=================================================*/

/* check for the correct compiler definition (from Compiler.h) */
#if (!(defined _GCC_C_WIN32X86_) && !(defined _VC_C_WIN32X86_))
#error wrong compiler: (!= _GCC_C_WIN32X86_ || _VC_C_WIN32X86_)
#endif

/* \brief definition of derivate names for this architecture */
#define TS_WIN32X86 1U

#if (defined TS_IntDisable)
#error "TS_IntDisable already defined"
#endif

/** \brief Disables interrupts and returns previous state.
 **
 ** This macro disables all interrupts.
 ** The previous interrupt locking status is returned. */

#define TS_IntDisableInternal(s) 42
 
#define TS_IntDisable(s) TS_IntDisableInternal(s)

#if (defined TS_IntRestore)
#error "TS_IntRestore already defined"
#endif

/** \brief Restores interrupt lock state
 **
 ** This macro restores the interrupt locking status to a state
 ** returned by a previous call to TS_IntDisable(). */
#define TS_IntRestoreInternal(s)
 
#define TS_IntRestore(s) TS_IntRestoreInternal(s)

/*==================[external function declarations]=========================*/

/** \brief Disables interrupts and returns previous state.
 **
 ** This function disables all interrupts by using the OS API.
 ** This is the only option, since this code can only run under the
 ** Windows simulator. */
 
/* extern TS_IntStatusType TS_IntDisableInternal(void); */

/** \brief Restores interrupt lock state
 **
 ** This function restores the interrupt locking status to a state
 ** returned by a previous call to TS_IntDisable().
 **
 ** \param[in] status the status previously saved in a call to
 ** TS_IntDisableInternal */
 
/* extern void TS_IntRestoreInternal(TS_IntStatusType status); */

#endif /* if (!defined TSPLATFORMS_H) */
