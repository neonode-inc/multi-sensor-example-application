/*! \file
 * \brief Main structure for the SDK library.
 *
 * This structure contains the overrides and is always instantiated at the
 *  beginning of execution when using the library.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(ZFORCE_ZFORCE_H) && !defined(CONTAINS_ZFORCE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCEOMMON_H
#ifndef ZFORCE_OSABSTRACTIONLAYER_H
    #error Please include "OsAbstractionLayer.h" before this file.
#endif // ZFORCE_OSABSTRACTIONLAYER_H

/*!
 * \sa struct zForce
 */
typedef struct zForce zForce;
/*!
 * \brief Main struct.
 */
struct zForce
{
#endif // !defined(ZFORCE_ZFORCE_H) && !defined(CONTAINS_ZFORCE)
#if !defined(ZFORCE_ZFORCE_H) || defined(CONTAINS_ZFORCE)
    OsAbstractionLayer OsAbstractionLayer; //!< Abstracted OS Functions.
    /*!
     * \brief Destructor frees all resources including itself.
     *
     * \param self Pointer to the struct itself.
     *
     * \return No return value.
     */
    void           ( * Destructor)(zForce * self);
#endif // !defined(ZFORCE_ZFORCE_H) || defined(CONTAINS_ZFORCE)
#if !defined(ZFORCE_ZFORCE_H) && !defined(CONTAINS_ZFORCE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Get a zForce Instance.
 *
 * Get a zForceInstance. This is a singleton so subsequent calls returns the
 * same instance.
 * \n\n
 * On error, errno is set.
 * - ::EZFORCENOTINITIALIZED - zForce not initialized.
 * - ::EMUTEXNOTINITIALIZED - Internal Error. Mutex not initialized.
 * - ::EMUTEXLOCKFAILED - Internal Error. Mutex Lock failed.
 *
 * \return Pointer to zForce structure.
 */
DLLEXTERNAL zForce * zForce_GetInstance (void);

/*!
 * \brief Initializes zForce.
 *
 * Initializes the zForce SDK. Must be called only once.
 * \n\n
 * On error, errno is set.
 * - ::EALREADYINITIALIZED - zForce_Initialize has already been called.
 * - ::EMUTEXINITIALIZATIONFAILED - Failed initializing mutex.
 * - ::EZFORCEINITIALIZATIONFAILED - zForce Initialization failed.
 * - ::EZFORCENOTINITIALIZED - zForce not Initialized.
 *
 * \param osAbstractionLayer Pointer to OsAbstractionLayer instance or NULL.
 *                           Non-NULL members of the OsAbstractionLayer are
 *                           copied so the supplied instance of
 *                           OsAbstractionLayer can be freed by the caller
 *                           after this call returns. If this argument is NULL,
 *                           or any members of the supplied OsAbstractionLayer
 *                           instance are NULL, default / OS specific functions
 *                           are used instead.
 *
 * \return True if successful, false if not, and errno set accordingly.
 *         See above for errno values.
 */
DLLEXTERNAL bool     zForce_Initialize (OsAbstractionLayer * osAbstractionLayer);

/*!
 * \brief Uninitializes zForce.
 *
 * Unitializes zForce, freeing all allocated resources. No part of the zForce
 * SDK should be used after this call.
 * \n\n
 * On error, errno is set.
 * - ::EMUTEXDESTROYFAILED - Mutex Destroy failed.
 * - ::EBADMUTEX - Bad Mutex pointer.
 *
 * \return No return value.
 */
DLLEXTERNAL void     zForce_Uninitialize (void);

/*!
 * \brief Retrieves a pointer to the zForce errno.
 *
 * Retrieves the pointer to the errno value of the C library the zForce SDK was compiled with,
 * which is not always the same as the program utilizing the zForce SDK was compiled with.
 * Example of this is if you in Windows compile your program in Debug mode. The zForce SDK DLL
 * will access one errno, and the application has a separate errno value.
 *
 * \return A pointer to the errno value.
 */

DLLEXTERNAL int *    zForce_ErrnoLocation (void);

#ifdef __cplusplus
}
#endif // __cplusplus

//! Macro to retrieve (or set) the errno value. Works the same as normal errno.
#define zForceErrno (*zForce_ErrnoLocation())

#define ZFORCE_ZFORCE_H
#endif // !defined(ZFORCE_ZFORCE_H) && !defined(CONTAINS_ZFORCE)

