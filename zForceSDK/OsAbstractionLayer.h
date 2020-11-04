/*! \file
 * \brief Os Abstraction Layer.
 *
 * This structure contains the overrides and is always instantiated at the
 *  beginning of execution when using the library.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(ZFORCE_OSABSTRACTIONLAYER_H) && !defined(CONTAINS_OSABSTRACTIONLAYER)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

typedef void zForceMutex;     //!< Typecast to underlying (system) type.
typedef void zForceSemaphore; //!< Typecast to underlying (system) type.
typedef void zForceThread;    //!< Typecast to underlying (system) type.

/*!
 * \sa struct zForceThreadWrapper
 */
typedef struct zForceThreadWrapper zForceThreadWrapper;
/*!
 * \brief Wrapper for threads.
 */
struct zForceThreadWrapper
{
    zForceThread * zForceThread;        //!< Thread pointer.
    void       ( * EntryPoint)(void *); //!< Entry function for the thread.
    void         * Arguments;           //!< Arguments for the entry function.
};

/*!
 * \sa struct OsAbstractionLayer
 */
typedef struct OsAbstractionLayer OsAbstractionLayer;
/*!
 * \brief Overrides for OS Functions.
 */
struct OsAbstractionLayer
{
#endif // !defined(ZFORCE_OSABSTRACTIONLAYER_H) && !defined(CONTAINS_OSABSTRACTIONLAYER)
#if !defined(ZFORCE_OSABSTRACTIONLAYER_H) || defined(CONTAINS_OSABSTRACTIONLAYER)
    /*!
     * \brief Allocate memory area. The memory area is not nulled.
     *
     * Allocate memory area. The memory area is not nulled.
     * \n\n
     * On failure, errno is set.
     * - ::EOUTOFMEMORY
     * - ::EILLEGALMEMORYSIZE
     *
     * \param size Size of the requested memory area in bytes.
     *
     * \return Pointer to allocated memory area or NULL for failure. See errno.
     */
    void   * ( * Malloc)(size_t size);

    /*!
     * \brief Free previously allocated memory area.
     *
     * Free previously allocated memory area.
     *
     * \param memoryPointer Pointer to memory area to free.
     *
     * \return No return value.
     */
    void     ( * Free)(void * memoryPointer);

    /*!
     * \brief Reallocate previously allocated memory area with a new size.
     *
     * Reallocate previously allocated memory area with a new size.
     * \n\n
     * On failure, errno is set.
     * - ::EOUTOFMEMORY
     * - ::EILLEGALMEMORYSIZE
     *
     * \param memoryPointer Pointer to memory area or NULL to allocate a new one.
     * \param size Size of the new area.
     *
     * \return Pointer to memory area. Can point to a new location.
     */
    void   * ( * Realloc)(void * memoryPointer, size_t size);

    /*!
     * \brief Allocate memory area, setting all memory to the supplied pattern.
     *
     * Allocate memory area, setting all memory to the supplied pattern.
     * \n\n
     * On failure, errno is set.
     * - ::EOUTOFMEMORY
     * - ::EILLEGALMEMORYSIZE
     *
     * \param size Size of the requested memory area in bytes.
     * \param pattern 1-byte pattern to fill the memory with.
     *
     * \return Pointer to allocated memory area or NULL for failure. See errno.
     */
    void   * ( * MallocWithPattern)(size_t size, uint8_t pattern);

    /*!
     * \brief Initialize Mutex.
     *
     * Initialize Mutex.
     * \n\n
     * On failure, errno is set.
     * - ::EMUTEXINITIALIZATIONFAILED - Mutex Initialization failed.
     * - ::EBADMUTEX - Pointer supplied is NULL.
     *
     * \param [out] zForceMutex Pointer to a zForceMutex pointer.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * InitializeMutex)(zForceMutex ** zForceMutex);

    /*!
     * \brief Lock Mutex.
     *
     * Lock Mutex.
     * \n\n
     * On failure, errno is set.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param zForceMutex Pointer to zForceMutex instance.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * LockMutex)(zForceMutex * zForceMutex);

    /*!
     * \brief Unlock Mutex.
     *
     * Unlock Mutex.
     * \n\n
     * On failure, errno is set.
     * - ::EMUTEXUNLOCKFAILED - Mutex Unlock failed.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param zForceMutex Pointer to zForceMutex instance.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * UnlockMutex)(zForceMutex * zForceMutex);

    /*!
     * \brief Destroy Mutex.
     *
     * Destroy Mutex.
     * \n\n
     * On failure, errno is set.
     * - ::EMUTEXDESTROYFAILED - Mutex Destroy failed.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param zForceMutex Pointer to zForceMutex instance.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * DestroyMutex)(zForceMutex * zForceMutex);

    /*!
     * \brief Initialize Semaphore.
     *
     * Initialize Semaphore and set it to initialValue.
     * The initial value is 0 for blocking and positive value for
     * not currently blocking regardless of underlying implementation.
     * For example for a queue, an initial value of 0 is desirable as the
     * queue is empty initially.
     * \n\n
     * On failure, errno is set.
     * - ::ESEMAPHOREINITIALIZATIONFAILED - Semaphore Initialization failed.
     * - ::EVALUEOVERFLOW - Timeout value too large.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     *
     * \param [out] zForceSemaphore Pointer to zForceSemaphore pointer.
     * \param initialValue Initial value to set the Semaphore to.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * InitializeSemaphore)
                 (zForceSemaphore ** zForceSemaphore, uint32_t initialValue);

    /*!
     * \brief Wait for Semaphore
     *
     * Wait for Semaphore. Blocks until count is incremented.
     * No guarantee of order if multiple threads are waiting for the same
     * Semaphore.
     * \n\n
     * On failure, errno is set.
     * - ::ESEMAPHOREWAITFAILED - Semaphore Wait failed.
     * - ::EFAILEDGETTINGTIME - Failed getting time.
     * - ::EINTERRUPTED - Interrupted before timeout.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     *
     * \param zForceSemaphore Semaphore to wait for.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * WaitForSemaphore)(zForceSemaphore * zForceSemaphore,
                                 uint32_t timeoutMs);

    /*!
     * \brief Increment Semaphore.
     *
     * Increment Semaphore by 1.
     * \n\n
     * On failure, errno is set.
     * - ::ESEMAPHOREINCREMENTFAILED - Generic Semaphore Increment error.
     * - ::EVALUEOVERFLOW - Semaphore would overflow if incremented.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     *
     * \param zForceSemaphore Semaphore to increment.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * IncrementSemaphore)(zForceSemaphore * zForceSemaphore);

    /*!
     * \brief Destroy Semaphore.
     *
     * Destroy Semaphore. Regardless of return code, the Semaphore
     * should no longer be used.
     * \n\n
     * On failure, errno is set.
     * - ::ESEMAPHOREDESTROYFAILED - Semaphore Destroy failed.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     *
     * \param zForceSemaphore Semaphore to wait for.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * DestroySemaphore)(zForceSemaphore * zForceSemaphore);

    /*!
     * \brief Get time in MilliSeconds.
     *
     * The only requirement on this time is that it is a time that does not
     * change according to timezone changes or daylight time changes.
     * There is no requirement on this being number of milliseconds since
     * some specified time in history.
     *
     * \return Unsigned 64-bit value representing time in MilliSeconds.
     */
    uint64_t ( * GetTimeMilliSeconds)(void);

    /*!
     * \brief Create Thread and run it.
     *
     * Create Thread and run it.
     * \n\n
     * On failure, errno is set.
     * - ::ETHREADCREATEFAILED - Thread Creation Failed.
     * - ::EOUTOFMEMORY - Out of memory.
     * - ::EBADTHREAD - Bad Thread pointer.
     *
     * \param [out] zForceThread Pointer to zForceThread pointer.
     * \param entryPoint The entrypoint of the code to run.
     * \param arguments Pointer to arguments passed to the thread.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * CreateThread)(zForceThread ** zForceThread,
                               void ( * entryPoint)(void *),
                               void * arguments);

    /*!
     * \brief Wait for Thread to exit.
     *
     * Waits for Thread to exit. This function should normally never be called
     * other than internally in the library.
     * Blocks until Thread has exited, possibly forever.
     * \n\n
     * On failure, errno is set.
     * - ::EBADTHREAD - Bad Thread pointer.
     *
     * \param zForceThread zForceThread to wait for.
     *
     * \return True for success, False for failure. See errno.
     */
    bool     ( * WaitForThreadExit)(zForceThread * zForceThread);

    /*!
     * \brief Sleep for a specified amount of MilliSeconds.
     *
     * Suspends the execution of the current thread for the specified amount of
     * MilliSeconds.
     *
     * \param milliSeconds Amount of MilliSeconds to Sleep.
     *
     * \return No return value.
     */
    void     ( * Sleep)(uint32_t milliSeconds);
#endif // !defined(ZFORCE_OSABSTRACTIONLAYER_H) || defined(CONTAINS_OSABSTRACTIONLAYER)
#if !defined(ZFORCE_OSABSTRACTIONLAYER_H) && !defined(CONTAINS_OSABSTRACTIONLAYER)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

DLLINTERNAL bool OsAbstractionLayer_Initialize (OsAbstractionLayer * osAbstractionLayer,
                                                OsAbstractionLayer * userSuppliedOsAbstractionLayer);

DLLINTERNAL void OsAbstractionLayer_ThreadWrapper (zForceThreadWrapper * wrapper);

#ifdef __cplusplus
}
#endif // __cplusplus

#define ZFORCE_OSABSTRACTIONLAYER_H
#endif // !defined(ZFORCE_OSABSTRACTIONLAYER_H) && !defined(CONTAINS_OSABSTRACTIONLAYER)

