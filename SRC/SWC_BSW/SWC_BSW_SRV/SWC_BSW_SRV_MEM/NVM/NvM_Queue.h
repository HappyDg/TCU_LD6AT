/**
 * \file
 *
 * \brief AUTOSAR NvM
 *
 * This file contains the implementation of the AUTOSAR
 * module NvM.
 *
 * \author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
 *
 * Copyright 2005 - 2013 Elektrobit Automotive GmbH
 * All rights exclusively reserved for Elektrobit Automotive GmbH,
 * unless expressly agreed to otherwise.
 */
#if ( !defined NVM_QUEUE_H )
#define NVM_QUEUE_H

/*==================[inclusions]============================================*/

#include <TSAutosar.h>            /* EB specific standard types             */
#include <NvM_Int_Types.h>        /* NvM specific internal types            */

#include <NvM_Cfg.h>              /* Contains generated configuration       */
                                  /* data.                                  */

/*==================[macros]================================================*/

/** \brief this value indicates that the queue is empty. */
#define NVM_QUEUE_IS_EMPTY              0U

/** \brief this value indicates that at least one request is queued. */
#define NVM_QUEUE_REQUEST_QUEUED        1U

/*==================[type definitions]======================================*/

/*==================[external function declarations]========================*/

#define NVM_START_SEC_CODE
#include <MemMap.h>

/** \brief Inserts a job request into the Standard Queue.
 **
 ** \param[in]  BlockId: ID of the requested block, range: 0..255
 ** \param[in]  DataAddress: address of a temporary user data RAM block.
 **             range: 0..size of NVM_APPL_DATA
 ** \param[in]  NvMRequestAsyncPtr: address of the first state function of the
 **             asynchronous part of the API function.
 **
 **/
extern FUNC( Std_ReturnType,NVM_CODE ) NvM_Queue_InsertStandard
(
  NvM_BlockIdType                         BlockId,
  P2VAR ( uint8,AUTOMATIC,NVM_APPL_DATA ) DataAddress,
  NvM_CurrentFunctionPtrType              NvMRequestAsyncPtr
);

/** \brief Removes the first entry of the queue.
 **        It is called after an asynchronous API request has been finished.
 **        This function requires that NvM_GlobalBlockNumber is set correctly.
 **        Therefore it must be used only in the asynchronous part of a
 **        service.
 **/
extern FUNC( void,NVM_CODE ) NvM_Queue_RemoveFirstItem( void );

/** \brief Checks if the standard queue is full.
 **        It is called before a new request is inserted into the queue.
 **
 **        The function reserves one queue element for ReadAll and WriteAll
 **        requests.
 **
 ** \param[in]  BlockId: ID of the requested block, range: 0..65535
 ** \revtal E_OK: standare queue is not full.
 ** \retval E_NOT_OK: standard queue is full.
 **/
extern FUNC( uint8,NVM_CODE ) NvM_Queue_CheckFullStandard
(
  NvM_BlockIdType BlockId
);

/** \brief Checks if the immediate queue and the standard queue is empty.
 **
 **        It is used in the NvM_MainFunction(), NvM_ReadAll() and NvM_WriteAll()
 **        to check if a request is inserted in the immediate queue or the
 **        standard queue.
 **
 ** \revtal NVM_QUEUE_IS_EMPTY: Both queues are empty.
 ** \retval NVM_QUEUE_REQUEST_QUEUED: At least one request is queued.
 **/
extern FUNC( uint8,NVM_CODE ) Nvm_Queue_CheckEmpty( void );

/** \brief Moves the first entry in the queue one position down.
 **        It is called when the Ram to Mirror copy has failed
 **        NVM_REPEAT_MIRROR_OPERATIONS times.
 **        This function interchanges the first request in the queue
 **        and the next request so that the next job in the queue is processed
 **        before the processing of the previous job is restarted.
 **
 ** \revtal E_OK: The request has been replaced by another.
 ** \revtal E_NOT_OK: There are no requests to replace.
 **/
extern FUNC(Std_ReturnType, NVM_CODE) NvM_Queue_PullDownFirstItem(void);

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

#if ( NVM_JOB_PRIORITIZATION == STD_ON )

/** \brief Insert a job request into the Immediate Queue.
 **        If the required NVRAM Block has immediate priority
 **        the API function request is inserted into the Immediate Queue
 **        else into the Standard Queue.  This function is only called
 **        in case the configuration parameter NvMJobPrioritization is set to STD_ON.
 **
 ** \param[in]  BlockId: ID of the requested block, range: 0..255
 ** \param[in]  DataAddress: address of a temporary user data RAM block.
 **             range: 0..size of NVM_APPL_DATA
 ** \param[in]  NvMRequestAsyncPtr: Address of the first state function of the
 **             asynchronous part of the API function.
 **/
extern FUNC( Std_ReturnType,NVM_CODE ) NvM_Queue_InsertImmediate
(
  NvM_BlockIdType                         BlockId,
  P2VAR ( uint8,AUTOMATIC,NVM_APPL_DATA ) DataAddress,
  NvM_CurrentFunctionPtrType              NvMRequestAsyncPtr
);

/** \brief Saves the context of a multi-block request interrupted by
 **        an immediate write request.
 **
 **        The function searches for a multi-block request in the standard
 **        priority job and inserts the interrupted block number and the 
 **        next asynchronous function pointer into the corresponding queue item.
 **        Thus, the multi-block request can be properly resumed.
 **/
extern FUNC(void, NVM_CODE) NvM_Queue_UpdateMultiblockQueueItem(void);

#endif

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#define NVM_STOP_SEC_CODE
#include <MemMap.h>

/*==================[internal function declarations]========================*/

/*==================[external constants]====================================*/

/*==================[internal constants]====================================*/

/*==================[external data]=========================================*/

#define NVM_START_SEC_VAR_NO_INIT_8
#include <MemMap.h>

/** \brief Indicates the array index of the first entry in the Standard Queue. */
extern VAR( uint8,NVM_VAR_NOINIT ) NvM_Queue_IndexStandard;

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

#if ( ( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ))
/** \brief Indicates the index to the front of the Immediate Queue. */
extern VAR( uint8,NVM_VAR_NOINIT ) NvM_Queue_IndexImmediate;
/** \brief The number of elements in the Immediate Queue. */
extern VAR( uint8,NVM_VAR_NOINIT ) NvM_Queue_CountImmediate;
#endif

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#define NVM_STOP_SEC_VAR_NO_INIT_8
#include <MemMap.h>


#define NVM_START_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/** \brief NvM standard queue for storing the job requests with standard priority.
 **
 **        It queues the standard priority requests.
 **        One element in this queue is reserved for multiblock requests.
 **/
extern VAR( NvM_QueueItemType, NVM_VAR ) NvM_Queue_Standard[NVM_SIZE_STANDARD_JOB_QUEUE];

#if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1)

#if ( ( NVM_JOB_PRIORITIZATION == STD_ON ) && ( NVM_NUMBER_OF_IMMEDIATE_PRIORITY_BLOCKS > 0U ))
/** \brief NvM immediate queue for storing write job requests with immediate priority.
 **
 **        The Immediate Queue is implemented as a circular queue with two variables
 **        controlling the insertion and removal of elements to and from the queue.
 **        Jobs are inserted at the tail of the queue and are removed from the front.
 **
 **        The variable 'NvM_Queue_IndexImmediate' points to the front of the queue and
 **        at any time points to the current job in immediate queue which is being serviced.
 **        It is increased by 1 whenever a job is removed from the queue.
 **        If 'NvM_Queue_IndexImmediate' points at the end of the queue and a job is removed,
 **        'NvM_Queue_IndexImmediate' is set to zero (circular queue handling).
 **
 **        The variable 'NvM_Queue_CountImmediate' stores the number of jobs currently present
 **        in the queue. It is incremented each time a new job is inserted into the queue
 **        and is decreased by 1 each time a job is removed from the queue.
 **
 **        A new job is inserted in the queue at the position given by
 **        (NvM_Queue_IndexImmediate + NvM_Queue_CountImmediate) % NVM_SIZE_IMMEDIATE_JOB_QUEUE
 **
 **        A job is removed from the queue by updating NvM_Queue_IndexImmediate to
 **        (NvM_Queue_IndexImmediate + 1) % NVM_SIZE_IMMEDIATE_JOB_QUEUE
 **
 **        The queue-empty status is indicated by 'NvM_Queue_CountImmediate = 0' and queue-full
 **        status is indicated by 'NvM_Queue_CountImmediate = NVM_SIZE_IMMEDIATE_JOB_QUEUE'
 **/
extern VAR( NvM_QueueItemType, NVM_VAR ) NvM_Queue_Immediate[NVM_SIZE_IMMEDIATE_JOB_QUEUE];
#endif

#endif /* #if (NVM_API_CONFIG_CLASS != NVM_API_CONFIG_CLASS_1) */

#define NVM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include <MemMap.h>

/*==================[internal data]=========================================*/

/*==================[external function definitions]=========================*/

/*==================[internal function definitions]=========================*/

#endif /* if !defined( NVM_QUEUE_H ) */
/*==================[end of file]===========================================*/
