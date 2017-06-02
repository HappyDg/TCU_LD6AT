/**
 * \file
 *
 * \brief AUTOSAR MemIf
 *
 * This file contains the implementation of the AUTOSAR
 * module MemIf.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#ifndef MEMIF_TYPES_H
#define MEMIF_TYPES_H

/*==================[inclusions]============================================*/

/* Include module version information and publish them to drivers which only
 * include MemIf_Types.h */
#include <MemIf_Version.h>

/*==================[macros]================================================*/

/** \brief Device ID for "broadcast"
 **
 ** In case the parameter given as device ID is MEMIF_BROADCAST_ID,
 ** the memory abstraction interface shall iterate over all underlying
 ** devices and return their combined status. */
#define MEMIF_BROADCAST_ID 255U

/*==================[type definitions]======================================*/

/* !LINKSTO MemIf009,1 */
/** \brief Type definition of the MemIf status type
 **
 ** This type denotes the current status of the underlying abstraction module
 ** and device driver. It shall be used as the return value of the
 ** corresponding driver's "GetStatus" function. */
typedef enum
{
  /** \brief The underlying abstraction module or device driver has not been
   * initialized (yet). */
  MEMIF_UNINIT,
  /** \brief The underlying abstraction module or device driver is currently
   * idle. */
  MEMIF_IDLE,
  /** \brief The underlying abstraction module or device driver is currently
   * busy. */
  MEMIF_BUSY,
  /** \brief The underlying abstraction module is busy with internal
   * management operations.
   *
   * The underlying device driver can be busy or idle. */
  MEMIF_BUSY_INTERNAL
} MemIf_StatusType;

/** \brief Type definition of the MemIf job result type
 **
 ** This type denotes the result of the last job. */
typedef enum
{
  /** \brief The job has been finished successfully. */
  MEMIF_JOB_OK,
  /** \brief The job has not been finished successfully. */
  MEMIF_JOB_FAILED,
  /** \brief The job has not yet been finished. */
  MEMIF_JOB_PENDING,
  /** \brief The job has been canceled. */
  MEMIF_JOB_CANCELED,
  /** \brief The requested block is inconsistent, it may contain corrupted
   * data. */
  MEMIF_BLOCK_INCONSISTENT,
  /** \brief The requested block has been marked as invalid, the requested
   * operation can not be performed. */
  MEMIF_BLOCK_INVALID
} MemIf_JobResultType;

/** \brief Type definition for the operation mode
 **
 ** The operation mode of the underlying abstraction modules and device
 ** drivers. */
typedef enum
{
  /** \brief The underlying memory abstraction modules and drivers are working
   * in slow mode. */
  MEMIF_MODE_SLOW,
  /** \brief The underlying memory abstraction modules and drivers are working
   * in fast mode. */
  MEMIF_MODE_FAST
} MemIf_ModeType;

#endif /* MEMIF_TYPES_H */
/*==================[end of file]===========================================*/
