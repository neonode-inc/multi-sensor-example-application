/*! \file
 * \brief Transport Base class.
 *
 * This module implements the Transport base class. Here we find all that is
 * essential for a Transport.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(TRANSPORT_TRANSPORT_H) && !defined(CONTAINS_TRANSPORT)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

//! \sa ReadWriteThreadStatus
typedef enum ReadWriteThreadStatus ReadWriteThreadStatus;
//! Enum describing the current status of a Read or Write thread.
enum ReadWriteThreadStatus
{
    ThreadIsNotRunning,   //!< Thread is not running.
    ThreadIsInitializing, //!< Thread is Initializing.
    ThreadIsRunning,      //!< Thread is Running.
    ThreadIsTerminating   //!< Thread is Terminating.
};

/*
 * Forward declaration required in order to break the cycle where
 * Transport needs TransportEntry, and
 * TransportEntry needs Transport.
 */
 //! \sa struct TransportEntry
typedef struct TransportEntry TransportEntry;

/*!
 * \sa struct Transport
 */
typedef struct Transport Transport;
/*!
 * \brief Transport struct. This structure represents the base class of
 * all Transport definitions.
 *
 */
struct Transport
{
#endif // !defined(TRANSPORT_TRANSPORT_H) && !defined(CONTAINS_TRANSPORT)
#if !defined(TRANSPORT_TRANSPORT_H) || defined(CONTAINS_TRANSPORT)
    /*!
     * \brief Base pointer to the immediate base Transport class.
     * The inheritance is nested so for example WinSerTransport inherits from
     * SerTransport which inherits from Transport.
     * If Base is a NULL pointer then it is the base Transport class itself.
     */
    Transport           * Base;
    /*!
     * \brief Each Transport is linked to one Connection.
     */
    Connection          * Connection;
    //! A pointer to the global zForce instance.
    zForce              * zForce;
    /*!
     * \brief Connection string.
     * This string contain the type of transport and the option parameters on
     * the following form: type://port=portOption e.g
     * "serial://port=/dev/ttyACM0".
     */
    char                  ConnectionString [TRANSPORTPROTOCOL_MaxOptionParameterLength + 1];
    /*!
     * \brief A flag indicating if the Transport Read and Write threads should
     * terminate (true) or not (false).
     */
    bool                  Terminate;
    /*!
    * \brief A pointer to the Write queue used by EnqueueDataFrame.
    */
    Queue               * WriteQueue;
    /*!
     * \brief A flag indicating if the Transport is open (true) or not (false).
     */
    bool                  IsOpen;
    bool                  Opening;           //!< Transport is in Opening phase.
    zForceThread        * WriteThread;       //!< Write Thread pointer.
    zForceThread        * ReadThread;        //!< Read Thread pointer.
    volatile ReadWriteThreadStatus WriteThreadStatus; //!< Thread is active.
    volatile ReadWriteThreadStatus ReadThreadStatus;  //!< Thread is active.
    /*!
     * \brief Open the generic Transport.
     *
     * This function opens the Transport specified by the ConnectionString.
     * If the ConnectionString contains a port as an options string that port
     * will be used. Open also sets up the Read and Write.
     * \n\n
     * On failure, errno is set.
     * - ::ETHREADCREATEFAILED - Thread creation failed.
     * - ::EOUTOFMEMORY - Out of memory.
     * - ::EBADTHREAD - Bad thread pointer.
     * - ::EQUEUECREATIONFAILED - Queue creation failed.
     * - ::EOPENFAILED - Could not open file.
     * - ::ENOPORTENTRY - No such file or directory.
     * - ::EALREADYOPEN - Specific transport is already opened.
     * - ::ENODEVICEENTRY - No device with that name.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True if successful, false if not, and errno set accordingly.
     */
    bool        ( * Open)(Transport * self);
    /*!
     * \brief Close the generic Transport.
     *
     * On failure, errno is set.
     * - ::ENOTOPENED - Transport is not open.
     * - ::ECLOSEFAILED - Closing file descriptor failed.
     * - ::EBADTHREAD - Bad thread pointer, problem with exiting thread.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True if successful, false if not, and errno set accordingly.
     */
    bool        ( * Close)(Transport * self);
    /*!
     * \brief Function pointer to Transport's Read.
     *
     * On failure, errno is set.
     * - ::ENOTOPENED - Transport is not open.
     * - ::EREADFAILED - Read failed.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     *
     * \param self Pointer to the struct itself.
     *
     * \return A pointer to the read data frame,
     * NULL either if no data frames exist or an error has occurred.
     * Upon error see errno.
     */
    DataFrame * ( * Read)(Transport * self);
    /*!
     * \brief Function pointer to Transport's Write.
     *
     * On failure, errno is set.
     * - ::EWRITEFAILED - Write failed.
     * - ::EPARTIALWRITE - Not all bytes written.
     * - ::ENOTOPENED - Transport is not open.
     *
     * \param self Pointer to the struct itself.
     * \param payload The payload pointer.
     *
     * \return True if success, false if failed. See errno.
     */
    bool        ( * Write)(Transport * self, DataFrame * payload);
    /*!
    * \brief Function pointer to Transport's GetTimeOutValue.
    *
    * \param self Pointer to the struct itself.
    *
    * \return the Transport specific timeout value.
    */
    uint64_t    ( * GetTimeOutValue)(Transport * self);
    /*!
     * \brief Enqueue given dataframe.
     *
     * On failure, errno is set.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue pointer.
     * - ::ENOTOPENED - Transport is not open.
     *
     * \param self Pointer to the struct itself.
     * \param dataFrame the data frame to be put in the Write queue
     *
     * \return True if successful, false if not, and errno set accordingly.
     */
    bool        ( * EnqueueDataFrame)(Transport * self, DataFrame * dataFrame);

    /*!
     * \brief Destructor frees all the resources that have been allocated.
     *
     */
    void        ( * Destructor )(Transport * self);
#endif // !defined(TRANSPORT_TRANSPORT_H) || defined(CONTAINS_TRANSPORT)
#if !defined(TRANSPORT_TRANSPORT_H) && !defined(CONTAINS_TRANSPORT)
};

// Exported Functions (prefixed with module name and underscore)

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief This is the Transport factory function.
 *
 * This is the Transport class factory function. A new Transport structure is
 * allocated and if this succeeds the fields of the structure are populated
 * using the arguments passed to the constructor.
 * \n\n
 * Should allocation fail, NULL will be returned and errno is set as follows:
 * - ::EOUTOFMEMORY - Memory allocation failed.
 * - ::EBADNAME - The connectionString does not have a Transport name of the
 *                correct format.
 * - ::EBADCONNECTION - The connection pointer is not valid.
 * - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
 *                        critical section. This should not happen.
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 * - ::EUNKNOWNTRANSPORT - Unknown transport.
 *
 * \param connection A pointer to the Connection instance that will be used
 *                   with this Transport.
 * \param connectionString  A pointer to a NUL terminated char string holding a
 *                        unique human readable identifer. The contents of the
 *                        string are copied to the Transport structure.
 *                        The length of the string as measured by strlen should
 *                        be at most TRANSPORTPROTOCOL_MaxEntryNameLength chars.
 * \param dataFrameType An identifying string that determines the type of data
 *                      frames this Transport should traffic in.
 *
 * \return Returns a pointer the allocated Transport structure upon success,
 *         otherwise a NULL pointer is returned and errno is set accordingly.
 */

DLLEXTERNAL Transport * Transport_GetInstance (Connection * connection, char * connectionString, char * dataFrameType);

/*!
 * \brief Add a new Transport to the list of those available.
 *
 * This is the method used to find inform the zForce SDK of Transports which
 * can be used for communication.
 * \n\n
 * Upon error the errno variable is set as follows:
 * - ::EALREADYADDED - A Transport matching the name and data frame type has
 *                     already been added.
 * - ::EOUTOFMEMORY - The memory used to store Transport details has been
 *                    exhausted.
 * - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
 *                        critical section. This should not happen.
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 * - ::EPARAMETERSTRINGTOOLONG - The option parameter string is longer than the
 *                               MaxOptionParameterLength.
 *
 * \param transportEntry The description of the Transport to add.
 *
 * \return True if the Transport has been added. Otherwise false which indicates
 *         failure and the errno variable should be inspected for the reason
 *         why.
 */
DLLEXTERNAL bool Transport_AddTransport(TransportEntry * transportEntry);

/*!
 * \brief Initialize the Transport module.
 *
 * Perform the initialization of the Transport module.
 * \n\n
 * Upon error the errno variable is set as follows:
 * - ::EALREADYINITIALIZED - A previous initialization is still in effect.
 * - ::EALREADYADDED - A Transport matching the name and data frame type has
 *                     already been added.
 * - ::EOUTOFMEMORY - The memory used to store Transport details has been
 *                    exhausted.
 * - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
 *                        critical section. This should not happen.
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 * - ::EPARAMETERSTRINGTOOLONG - The option parameter string is longer than the
 *                               MaxOptionParameterLength.
 *
 * \return True upon success, false otherwise.
 */
DLLINTERNAL bool Transport_Initialize (void);

/*!
 * \brief Uninitialize the Transport module.
 *
 * Perform the uninitialization of the Transport module.\n
 * Any allocated resources are deallocated.
 * \n\n
 * Upon error the errno variable is set as follows:
 *
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 *
 * \return No return value.
 */
DLLINTERNAL void Transport_Uninitialize (void);

#ifdef USE_SERIALTRANSPORT
    DLLINTERNAL bool SerialTransport_AddSerialTransportEntry (void);
#endif // USE_SERIALTRANSPORT

#ifdef USE_HIDPIPETRANSPORT
    DLLINTERNAL bool HidPipeTransport_AddHidPipeTransportEntry (void);
#endif // USE_HIDPIPETRANSPORT

#ifdef __cplusplus
}
#endif // __cplusplus

#define TRANSPORT_TRANSPORT_H
#endif // !defined(TRANSPORT_TRANSPORT_H) && !defined(CONTAINS_TRANSPORT)

