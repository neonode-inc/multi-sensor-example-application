/*! \file
 * \brief Generic Queue handling.
 *
 * Generic Queue handling. Receiver is responsible to destroy message after
 * dequeuing.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(QUEUE_QUEUE_H) && !defined(CONTAINS_QUEUE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \sa struct Queue
 */
typedef struct Queue Queue;
/*!
 * \brief The Queue struct.
 */
struct Queue
{
#endif // !defined(QUEUE_QUEUE_H) && !defined(CONTAINS_QUEUE)
#if !defined(QUEUE_QUEUE_H) || defined(CONTAINS_QUEUE)
    zForce   * zForce; //!< Pointer to zForce.
    void     * QueuePrivate; //!< Private Queue data.
    /*!
     * \brief Destroys the Queue, freeing any resources but NOT contents.
     *
     * On failure, errno is set.
     * - ::EMUTEXNOTINITIALIZED - Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::ESEMAPHORENOTINITIALIZED - Semaphore not initialized.
     * - ::ESEMAPHOREDESTROYFAILED - Destroy Semaphore failed.
     * - ::EBADQUEUE - Bad Queue pointer.
     *
     * \param self Pointer to the Queue itself.
     *
     * \return No return value.
     */
    void   ( * Destructor)(Queue * self);
    /*!
     * \brief Add an entry to the queue.
     *
     * The data is not copied, the pointer is passed in the queue entry.
     * \n\n
     * On failure, errno is set.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue Pointer.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param self Pointer to the struct itself.
     * \param payload The payload pointer to add.
     *
     * \return True if success, False if failed. See errno.
     */
    bool   ( * Enqueue)(Queue * self, void * payload);
    /*!
     * \brief Get the first entry from the queue.
     *
     * Gets the first payload pointer in the queue, optionally with a timeout
     * for how long to wait for something to be put in the queue.
     * Timeout is specificed in milliseconds.
     * Using a timeout value of 0 means don't wait at all, return either a
     * payload pointer or an error code.
     * \n\n
     * On failure, errno is set.
     * - ::EDEQUEUEFAILED - Generic dequeue error.
     * - ::EBADQUEUE - Bad Queue Pointer.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param self Pointer to the struct itself.
     * \param timeoutMilliSeconds Timeout in milliseconds.
     *
     * \return Pointer to payload. On error, pointer is NULL. See errno.
     */
    void * ( * Dequeue)(Queue * self, uint32_t timeoutMilliSeconds);
#endif // !defined(QUEUE_QUEUE_H) || defined(CONTAINS_QUEUE)
#if !defined(QUEUE_QUEUE_H) && !defined(CONTAINS_QUEUE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Create a new Queue.
 *
 * Creates a new queue and all queue resources needed.
 * \n\n
 * On failure, errno is set.
 * - ::EOUTOFMEMORY - Memory allocation failed.
 * - ::EQUEUECREATIONFAILED - Queue creation failed.
 * - ::EBADMUTEX - Bad Mutex pointer.
 * - ::EBADSEMAPHORE - Bad Semaphore pointer.
 *
 * \return A pointer to the new Queue.
 */
DLLEXTERNAL Queue * Queue_New (void);

#ifdef __cplusplus
}
#endif // __cplusplus

#define QUEUE_QUEUE_H
#endif // !defined(QUEUE_QUEUE_H) && !defined(CONTAINS_QUEUE)

