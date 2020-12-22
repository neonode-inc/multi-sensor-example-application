/*! \file
 * \brief Handles connections.
 *
 * Handles connections, acts as the glue between devices, protocols and
 * transports. Also handles queues to notify software about incoming messages.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2020 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(CONNECTION_CONNECTION_H) && !defined(CONTAINS_CONNECTION)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

//! Connection events.
enum ConnectionStatus
{
    Connected,      //!< Status changed to Connected.
    Disconnected,   //!< Status changed to Disconnected.
    ConnectionFault //!< Connection Fault.
};
//! \sa enum ConnectionStatus
typedef enum ConnectionStatus ConnectionStatus;

//! \sa struct ConnectionMessage
typedef struct ConnectionMessage ConnectionMessage;
//! Connection messages struct.
struct ConnectionMessage
{
    ConnectionStatus ConnectionStatus; //!< New status of Connection.
    uint32_t         ErrorCode;        //!< Error code if connection error.
    void         ( * Destructor)(ConnectionMessage * self); //!< Destructor.
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
* \brief Internal call used to create a new ConnectionMessage.
*
* On failure, errno is set.
* - ::EOUTOFMEMORY - Out of memory.
*
* \param connectionStatus ConnectionStatus of message.
* \param errorCode ErrorCode of message.
*
* \return A pointer to the new ConnectionMessage.
*/
DLLINTERNAL ConnectionMessage * ConnectionMessage_New (
    ConnectionStatus connectionStatus, uint32_t errorCode);

#ifdef __cplusplus
}
#endif // __cplusplus

//! \sa struct Connection
typedef struct Connection Connection;
//! The main Connection struct.
struct Connection
{
#endif // !defined(CONNECTION_CONNECTION_H) && !defined(CONTAINS_CONNECTION)
#if !defined(CONNECTION_CONNECTION_H) || defined(CONTAINS_CONNECTION)
    zForce      * zForce;             //!< Pointer to zForce instance.
    Transport   * Transport;          //!< Transport this Connection uses.
    Protocol    * Protocol;           //!< Protocol this Connection uses.
    Queue       * ConnectionQueue;    //!< Queue to report Connection events.
    Queue       * DeviceQueue;        //!< Queue to report Device events.
    Device     ** Devices;            //!< List of Devices.
    uint32_t      NumberOfDevices;    //!< Number of Devices detected.
    bool          IsConnected;        //!< Connected to unit.
    zForceMutex * MessageFilterMutex; //!< Message Filter Mutex.
    Device      * FilterDevice;       //!< Which Device the filter is set to.
    MessageType   FilterMessageType;  //!< Which Message the filter is set to.
    //! Serial number of last processed response message.
    uint64_t      LastResponseSerialNumber;

    /*!
     * \brief Destructor.
     *
     * On error, errno is set.
     * - ::ENOTCONNECTED - The connection is not connected.
     * - ::EMUTEXDESTROYFAILED - OsAbstractionLayer Mutex Destroy failed.
     * - ::EBADMUTEX - OsAbstractionLayer Bad Mutex pointer.
     * - ::EBADQUEUE - Bad Queue pointer.
     * - ::EMUTEXNOTINITIALIZED - Queue Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Queue Mutex Lock failed.
     * - ::ESEMAPHORENOTINITIALIZED - Queue Semaphore not initialized.
     * - ::ESEMAPHOREDESTROYFAILED - Queue Destroy Semaphore failed.
     *
     * \param self Pointer to the struct itself.
     *
     * \return No return value.
     */
    void      ( * Destructor)(Connection * self);
    /*!
     * \brief Internal call to add a Device to the Device list.
     *
     * On error, errno is set.
     * - ::EOUTOFMEMORY - Memory exhaustion.
     *
     * \param self Pointer to the struct itself.
     * \param device The Device to add.
     *
     * \return True if successful, false if not. See errno.
     */
    bool      ( * AddDevice)(Connection * self, Device * device);
    /*!
     * \brief Find a Device with a specified Type/Index combination.
     *
     * Find a Device with a specificed Type/Index combination.\n
     * For Platform and Lighting devices, the Type/Index are searched for
     * directly.\n
     * For Core, Air and Plus devices, the Type/Index are also searched for
     * directly, but they can also be found using a meta Sensor device type.
     * Sensor is not a real device type, and contains all functionality that is
     * shared between all Sensor types (Core, Air and Plus).\n
     * Type = Sensor, Index = 0 is the first Sensor in the list,\n
     * Type = Sensor, Index = 1 is the second Sensor.
     * The "real" Device Index is not used for this search when searching for a
     * Sensor.
     * \n\n
     * Examples:
     * A unit that contains 1 Platform Device, 2 Core Devices, 1 Air Device and
     * 1 Lighting Device:\n
     * To find the Platform Device, look for Type = Platform, Index = 0.\n
     * To find the Lighting Device, look for Type = Lighting, Index = 0.\n
     * To find the first Core Device, look for Type = Core, Index = 0.\n
     * To find the second Core Device, look for Type = Core, Index = 1.\n
     * To find the Air Device, look for Type = Air, Index = 0.\n
     * An alternative is to look for Sensor Devices 0, 1 and 2, and then
     * looking at the type of the returned Device.\n
     * There is no guarantee that the Sensor Devices are returned in
     * the same order every time.
     * \n\n
     * On error, errno is set.
     * - ::EDEVICENOTFOUND - Device with specified Type/Index not found.
     * - ::EUNKNOWNDEVICETYPE - Unknown Device Type.
     *
     * \param self Pointer to the struct itself.
     * \param deviceType The Device Type to find.
     * \param deviceIndex The Device Index to find.
     *
     * \return The Device or NULL if error. See errno.
     */
    Device *  ( * FindDevice)(Connection * self, DeviceType deviceType,
                             uint32_t deviceIndex);
    /*!
     * \brief Internal call to receive a DataFrame from the Transport layer.
     *
     * Internal call to receive a DataFrame from the Transport layer.
     * \n\n
     * On failure, errno is set.
     * \param self Pointer to the struct itself.
     * \param dataFrame The received DataFrame.
     *
     * \return True if successful, false if failed. See errno.
     */
    bool      ( * ReceiveDataFrame)(Connection * self, DataFrame * dateFrame);
    /*!
     * \brief Internal call to send a DataFrame using the Transport layer.
     *
     * On failure, errno is set.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue pointer.
     * - ::ENOTCONNECTED - Not connected.
     *
     * \param self Pointer to the struct itself.
     * \param dataFrame The DataFrame to send.
     *
     * \return True if successful, false if failed. See errno.
     */
    bool      ( * SendDataFrame)(Connection * self, DataFrame * dataFrame);
    /*!
     * \brief Internal call to set the Message Filter.
     *
     * On failure, errno is set.
     * - ::EMESSAGEFILTERALREADYSET - Message filter set previously.
     * - ::EMUTEXNOTINITIALIZED - Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::EMUTEXUNLOCKFAILED - Mutex Unlock failed.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param self Pointer to the struct itself.
     * \param device The Device to set the filter to.
     * \param messageType The MessageType to set the filter to.
     *
     * \return True if successful, false if failed. See errno.
     */
    bool      ( * SetMessageFilter)(Connection * self, Device * device,
                                   MessageType messageType);
    /*!
     * \brief Internal call to clear the Message Filter.
     *
     * This function will always clear the filter, even if it was not set
     * to begin with so this function cannot fail.
     * \n\n
     * On failure, errno is set.
     * - ::EMUTEXNOTINITIALIZED - Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::EMUTEXUNLOCKFAILED - Mutex Unlock failed.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param self Pointer to the struct itself.
     *
     * \return No return value.
     */
    void      ( * ClearMessageFilter)(Connection * self);
    /*!
     * \brief Internal call to Enqueue a Message on the Device Queue.
     *
     * On failure, errno is set.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue pointer.
     * - ::EMUTEXNOTINITIALIZED - Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::EBADMUTEX - Bad Mutex pointer.
     * - ::EMUTEXUNLOCKFAILED - Mutex Unlock failed.
     *
     * \param self Pointer to the struct itself.
     * \param device The Device the message corresponds to.
     * \param message The Message to enqueue.
     *
     * \return True if successful, false if failed. See errno.
     */
    bool      ( * EnqueueMessage)(Connection * self, Device * device,
                                 Message * message);
    /*!
     * \brief Connect to the unit.
     *
     * Connect to the unit using the previously specified Protocol and
     * Transport.
     * This call asynchronously starts the connection process.
     * The call exits immediately and if there is a direct connection problem,
     * for example that the connection is already established, then the call
     * exits with false and errno is set.
     * If there is no immediate error, the call returns true but the connection
     * cannot be considered established until the ConnectionQueue has returned
     * with a message saying status Connected.
     * \n\n
     * Errno list:
     * - ::EALREADYCONNECTED - The Connection is already established.
     * - ::EALREADYOPEN - Transport already open.
     * - ::ETHREADCREATEFAILED - Thread Creation Failed.
     * - ::EOUTOFMEMORY - Out of memory.
     * - ::EBADTHREAD - Bad Thread pointer.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EMUTEXNOTINITIALIZED - Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::EMUTEXUNLOCKFAILED - Mutex Unlock failed.
     * - ::EZFORCENOTINITIALIZED - zForce not Initialized.
     * \n\n
     * \sa ConnectionStatus
     *
     * \param self Pointer to the struct itself.
     *
     * \return True if successful, false if failed. See errno.
     */
    bool      ( * Connect)(Connection * self);
    /*!
     * \brief Disconnect from the unit.
     *
     * Disconnect the connection. This call is asynchronous and cannot be
     * considered complete until the ConnectionQueue has reported status
     * Disconnected.
     * \n\n
     * On failure, errno is set.
     * - ::ENOTCONNECTED - The Connection not connected.
     * - ::ENOTOPENED - Transport is not open.
     * - ::ECLOSEFAILED - Closing file descriptor failed.
     * - ::EBADTHREAD - Bad thread pointer, problem with exiting thread.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue Pointer.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     * - ::EBADMUTEX - Bad Mutex pointer.
     * \n\n
     * \sa ConnectionStatus
     *
     * \param self Pointer to the struct itself.
     *
     * \return True if successful, false if failed. See errno.
     */
    bool      ( * Disconnect)(Connection * self);
    /*!
     * \brief Internal call to signal a Timeout.
     *
     * Internal call to signal a Timeout has occured on this Connection.
     * \n\n
     * On failure, errno is set.
     * - ::ERECEIVETIMEOUT - Timeout received.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue Pointer.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     * - ::EBADMUTEX - Bad Mutex pointer.
     * - ::EMUTEXNOTINITIALIZED - Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::EMUTEXUNLOCKFAILED - Mutex Unlock failed.
     *
     * \param self Pointer to the struct itself.
     *
     * \return No return value.
     */
    void      ( * UnknownCommand)(Connection * self);
    /*!
     * \brief Internal call to signal an Unknown Command.
     *
     * Internal call to signal reception of Unknown Command on this Connection.
     * \n\n
     * On failure, errno is set.
     * - ::ERECEIVETIMEOUT - Timeout received.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue Pointer.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     * - ::EBADMUTEX - Bad Mutex pointer.
     * - ::EMUTEXNOTINITIALIZED - Mutex not initialized.
     * - ::EMUTEXLOCKFAILED - Mutex Lock failed.
     * - ::EMUTEXUNLOCKFAILED - Mutex Unlock failed.
     *
     * \param self Pointer to the struct itself.
     *
     * \return No return value.
     */
    void      ( * Timeout)(Connection * self);
    /*!
     * \brief Internal call to set the Timeout.
     *
     * Sets the timeout.
     * \n\n
     * On failure, errno is set.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue Pointer.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param self Pointer to the struct itself.
     * \param relativeTimeoutMilliSeconds Number of MilliSeconds to set it to.
     *
     * \return No return value.
     */
    void      ( * SetTimeout)(Connection * self,
                             uint64_t relativeTimeoutMilliSeconds);
    /*!
     * \brief Internal call to signal that the connection is established.
     *
     * On failure, errno is set.
     * - ::EENQUEUEFAILED - Generic enqueue error.
     * - ::EOUTOFMEMORY - Memory allocation failed.
     * - ::EBADQUEUE - Bad Queue Pointer.
     * - ::EBADSEMAPHORE - Bad Semaphore pointer.
     * - ::EBADMUTEX - Bad Mutex pointer.
     *
     * \param self Pointer to the struct itself.
     *
     * \return No return value.
     */
    void      ( * SignalConnectionEstablished)(Connection * self);
#endif // !defined(CONNECTION_CONNECTION_H) || defined(CONTAINS_CONNECTION)
#if !defined(CONNECTION_CONNECTION_H) && !defined(CONTAINS_CONNECTION)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Create a new Connection.
 *
 * This call does not actually connect, it just creates the binding between the
 * Protocol and Transport.
 *
 * On failure, errno is set.
 * - ::EUNKNOWNTRANSPORT - Unknown transport.
 * - ::EOUTOFMEMORY - Out of memory.
 * - ::EBADNAME - The protocolString does not have a protocol name of the
 *                correct format.
 * - ::EUNKNOWNPROTOCOL - There is no defined protocol with a name which
 *                       matches the name in protocolString.
 * - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
 *                        critical section. This should not happen.
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 *
 * Each Transport and Protocol has its own options.
 *
 * Example to connect to a sensor over Hid using Asn1 as protocol.
 *
 * HidPipeTransport (hidpipe) has the following options:
 *
 * - vid - Vendor ID. Current neonode sensors have VID 0x1536.\n
 * - pid - Product ID. Current neonode sensors have PID 0x0101.\n
 * - index - If the computer has multiple connected Neonode sensors,
 *        the first one has index 0, the second has index 1, etc.
 *        Note: The order is decided by the Operating System.
 *
 * Asn1Protocol (asn1) currently has no options.
 *
 * StreamingDataFrame (Streaming) is the DataFrame type used by both
 * HidPipeTransport and Asn1Protocol.
 *
 * MyConnection = Connection_New (\n
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 * "hidpipe://vid=0x1536,pid=0x0101,index=0",\n
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 * "asn1://",\n
 * &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
 * "Streaming");\n
 *
 * \param connectionString A Transport specific connection string.
 * \param protocolString A Protocol specific prototocol string.
 * \param dataFrameType Which Data Frame Type the Transport and Protocol uses.
 *
 * \return Connection pointer or NULL if failed. See errno.
 */
DLLEXTERNAL Connection * Connection_New (char * connectionString,
                                         char * protocolString,
                                         char * dataFrameType);

#ifdef __cplusplus
}
#endif // __cplusplus

#define CONNECTION_CONNECTION_H
#endif // !defined(CONNECTION_CONNECTION_H) && !defined(CONTAINS_CONNECTION)

