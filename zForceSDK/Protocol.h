/*! \file
 * \brief This module implements the Protocol base class.
 *
 * This module implements the Protocol base class. Here we find all that is
 * essential for a Protocol.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(PROTOCOL_PROTOCOL_H) && !defined(CONTAINS_PROTOCOL)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \sa struct Protocol
 */
typedef struct Protocol Protocol;
/*!
 * \brief This structure represents the base class of all protocol
 * definitions.
 *
 * This structure represents the base class of all protocol definitions.
 * The data and functions contained within the structure's fields are the
 * essentials which are common to all such definitions.
 */
struct Protocol
{
#endif // !defined(PROTOCOL_PROTOCOL_H) && !defined(CONTAINS_PROTOCOL)
#if !defined(PROTOCOL_PROTOCOL_H) || defined(CONTAINS_PROTOCOL)
    Protocol      * Base; //!< The immediate base class of this Protocol class.
    Connection    * Connection;  //!< Each Protocol is linked to one connection.
    //! A counter used for giving responses a unique serial number.
    //! Serial numbers start at 1 and strictly increase with each response.
    uint64_t        ResponseSerialNumber;

    //! A counter used for giving notifications a unique serial number.
    //! Serial numbers start at 1 and strictly increase with each notification.
    uint64_t        NotificationSerialNumber;

    //! The destructor for this class.
    void        ( * Destructor)(Protocol * self);

    //! Protocol Specific method to destroy any potential Protocol Specific Data
    //! stored in a Device;
    void        ( * DestroyPrivateDeviceData)(Protocol * self,
                                              void * privateDeviceData);

    zForce        * zForce; //!< A pointer to the global zForce instance.

    /*!
     * \brief Perform protocol specific processing upon connection.
     *
     * \param self Pointer to the struct itself.
     *
     * \return true upon success. Otherwise false which
     *         indicates failure and the errno variable should be inspected for
     *         the reason why.
     */
    bool        ( * Connect)(Protocol * self);

    /*!
     * \brief Perform protocol specific processing upon disconnection.
     *
     * \param self Pointer to the struct itself.
     *
     * \return true upon success. Otherwise false which
     *         indicates failure and the errno variable should be inspected for
     *         the reason why.
     */
    bool        ( * Disconnect)(Protocol * self);

    /*!
     * \brief Give a data frame to Protocol for processing.
     *
     * \param self Pointer to the struct itself.
     * \param dataFrame DataFrame pointer.
     *
     * \return true if the data frame has been decoded. Otherwise false which
     *         indicates failure and the errno variable should be inspected for
     *         the reason why.
     */
    bool        ( * DecodeDataFrame) (Protocol * self, DataFrame * dataFrame);
#if 0
    /*!
     * \brief Create a DeviceCount request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateDeviceCountRequest) (Protocol * self,
                                               Device * device,
                                               MessageAction action,
                                               uint32_t totalNumberOfDevices,
                                               bool HasTotalNumberOfDevices,
                                               uint32_t coreDevices,
                                               bool HasCoreDevices,
                                               uint32_t airDevices,
                                               bool HasAirDevices,
                                               uint32_t plusDevices,
                                               bool HasPlusDevices,
                                               uint32_t lightingDevices,
                                               bool HasLightingDevices);
#endif // 0
    /*!
     * \brief Create a Resolution request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param x X axis value if this is a set action.
     * \param hasX X axis value present flag if this is a set action.
     * \param y Y axis value if this is a set action.
     * \param hasY Y axis value present flag if this is a set action.
     * \param z Z axis value if this is a set action.
     * \param hasZ Z axis value present flag if this is a set action.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateResolutionRequest) (Protocol * self,
                                              Device * device,
                                              MessageAction action,
                                              uint32_t x,
                                              bool hasX,
                                              uint32_t y,
                                              bool hasY,
                                              uint32_t z,
                                              bool hasZ);
    /*!
     * \brief Create a TouchActiveArea request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param lowerBoundaryX X axis value of lower boundary.
     * \param lowerBoundaryY Y axis value of lower boundary.
     * \param upperBoundaryX X axis value of upper boundary.
     * \param upperBoundaryY Y axis value of upper boundary.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateTouchActiveAreaRequest) (Protocol * self,
                                                   Device * device,
                                                   MessageAction action,
                                                   uint32_t lowerBoundaryX,
                                                   uint32_t upperBoundaryX,
                                                   bool xIsValid,
                                                   uint32_t lowerBoundaryY,
                                                   uint32_t upperBoundaryY,
                                                   bool yIsValid);

    /*!
    * \brief Create a ReverseTouchActiveArea request.
    *
    * On error, errno is set.
    * - ::ENOTSUPPORTED - Operation not supported.
    * - ::EPROTOCOLERROR - Generic protocol error.
    * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
    *
    * \param self Pointer to the struct itself.
    * \param device Pointer to the Device from which the request originated.
    * \param action Indication of what type of action this message refers to.
    * \param reverseX X axis direction reversal flag.
    * \param reverseY Y axis direction reversal flag.
    *
    * \return Pointer to data frame if it it worked,
    *         NULL if it didn't. See errno.
    */
    DataFrame * ( * CreateReverseTouchActiveAreaRequest) (Protocol * self,
                                                          Device * device,
                                                          MessageAction action,
                                                          bool xIsReversed,
                                                          bool yIsReversed);

    /*!
    * \brief Create a FlipXY request.
    *
    * On error, errno is set.
    * - ::ENOTSUPPORTED - Operation not supported.
    * - ::EPROTOCOLERROR - Generic protocol error.
    * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
    *
    * \param self Pointer to the struct itself.
    * \param device Pointer to the Device from which the request originated.
    * \param action Indication of what type of action this message refers to.
    * \param flip the X and Y axes.
    *
    * \return Pointer to data frame if it it worked,
    *         NULL if it didn't. See errno.
    */
    DataFrame * ( * CreateFlipXYRequest) (Protocol * self, Device * device, MessageAction action, bool axesAreFlipped);

    /*!
    * \brief Create a ReflectiveEdgeFilter request.
    *
    * On error, errno is set.
    * - ::ENOTSUPPORTED - Operation not supported.
    * - ::EPROTOCOLERROR - Generic protocol error.
    * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
    *
    * \param self Pointer to the struct itself.
    * \param device Pointer to the Device from which the request originated.
    * \param action Indication of what type of action this message refers to.
    * \param isFilterOn true if the filter is on, otherwise false.
    * \return Pointer to data frame if it it worked,
    *         NULL if it didn't. See errno.
    */
    DataFrame * ( * CreateReflectiveEdgeFilterRequest) (Protocol * self, Device * device, MessageAction action, 
                                                                                                    bool isFilterOn);

    /*!
    * \brief Create a MergeTouches request.
    *
    * On error, errno is set.
    * - ::ENOTSUPPORTED - Operation not supported.
    * - ::EPROTOCOLERROR - Generic protocol error.
    * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
    *
    * \param self Pointer to the struct itself.
    * \param device Pointer to the Device from which the request originated.
    * \param action Indication of what type of action this message refers to.
    * \param areTouchesMerged true if the reported touches are merged, otherwise false.
    *
    * \return Pointer to data frame if it it worked,
    *         NULL if it didn't. See errno.
    */
    DataFrame * ( * CreateMergeTouchesRequest) (Protocol * self, Device * device, MessageAction action, 
                                                                                                bool areTouchesMerged);

    /*!
    * \brief Create a DetectionMode request.
    *
    * On error, errno is set.
    * - ::ENOTSUPPORTED - Operation not supported.
    * - ::EPROTOCOLERROR - Generic protocol error.
    * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
    *
    * \param self Pointer to the struct itself.
    * \param device Pointer to the Device from which the request originated.
    * \param action Indication of what type of action this message refers to.
    *
    * \return Pointer to data frame if it it worked,
    *         NULL if it didn't. See errno.
    */
    DataFrame * ( * CreateDetectionModeRequest) (Protocol * self, Device * device, MessageAction action);

    /*!
    * \brief Create a McuUniqueIdentifier request.
    *
    * On error, errno is set.
    * - ::ENOTSUPPORTED - Operation not supported.
    * - ::EPROTOCOLERROR - Generic protocol error.
    * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
    *
    * \param self Pointer to the struct itself.
    * \param device Pointer to the Device from which the request originated.
    * \param action Indication of what type of action this message refers to.
    * \param identifier Pointer to the Identifier array to set.
    * \param bufferSize Buffer size.
    *
    * \return Pointer to data frame if it it worked,
    *         NULL if it didn't. See errno.
    */
    DataFrame * ( * CreateMcuUniqueIdentifierRequest) (Protocol * self, Device * device, MessageAction action,
                                                       uint8_t * identifier, uint32_t bufferSize);

    /*!
     * \brief Create an Enable request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param continuousMode Set to true for continuous mode.
     * \param numberOfMessages When in non-continuous mode, specifies how many
     *                         Messages to receive before the Device disables
     *                         itself. May not be 0 when continuousMode ==
     *                         false.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateEnableRequest) (Protocol * self,
                                          Device * device,
                                          MessageAction action,
                                          bool continuousMode,
                                          uint32_t numberOfMessages);
    /*!
     * \brief Create an OperationModes request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param modeMask Indication of which modes have values in this call.
     * \param modeValues Optional values for modes. See the modeMask argument.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateOperationModesRequest) (Protocol * self,
                                                  Device * device,
                                                  MessageAction action,
                                                  OperationModes modeMask,
                                                  OperationModes modeValues);
    /*!
     * \brief Create a Disable request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateDisableRequest) (Protocol * self,
                                           Device * device,
                                           MessageAction action);
    /*!
     * \brief Create a FingerFrequency request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param frequency The value to set if this is a set action.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateFingerFrequencyRequest) (Protocol * self,
                                                   Device * device,
                                                   MessageAction action,
                                                   uint32_t frequency);
    /*!
     * \brief Create an IdleFrequency request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param frequency The value to set if this is a set action.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateIdleFrequencyRequest) (Protocol * self,
                                                 Device * device,
                                                 MessageAction action,
                                                 uint32_t frequency);
    /*!
     * \brief Create a DetectedObjectSizeRestriction request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param maximumSizeEnabled Maximum size enabling flag.
     * \param maximumSize The maximum object size for detection.
     * \param minimumSizeEnabled Minimum size enabling flag.
     * \param minimumSize The minimum object size for detection.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateDetectedObjectSizeRestrictionRequest)
                     (Protocol * self,
                      Device * device,
                      MessageAction action,
                      bool maximumSizeEnabled,
                      uint32_t maximumSize,
                      bool minimumSizeEnabled,
                      uint32_t minimumSize);

    /*!
     * \brief Create a NumberOfTrackedObjects request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param numberOfTrackedObjects Tracked object count.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateNumberOfTrackedObjectsRequest)
                        (Protocol * self,
                         Device * device,
                         MessageAction action,
                         uint32_t numberOfTrackedObjects);

    /*!
     * \brief Create an Offset request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param offsetX The X Offset.
     * \param offsetXIsValid The X Offset is valid, i.e. you want to set it.
     * \param offsetY The Y Offset.
     * \param offsetYIsValid The Y Offset is valid, i.e. you want to set it.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateOffsetRequest) (Protocol * self, Device * device, MessageAction action,
                                                                            uint32_t offsetX, bool offsetXIsValid,
                                                                            uint32_t offsetY, bool offsetYIsValid);

    /*!
     * \brief Create a HidDisplaySize request.
     *
     * On error, errno is set.
     * - ::ENOTSUPPORTED - Operation not supported.
     * - ::EPROTOCOLERROR - Generic protocol error.
     * - ::EOUTOFMEMORY - Could not dynamically allocate memory.
     *
     * \param self Pointer to the struct itself.
     * \param device Pointer to the Device from which the request originated.
     * \param action Indication of what type of action this message refers to.
     * \param sizeX The X Size.
     * \param sizeXIsValid The X Size is valid, i.e. you want to set it.
     * \param sizeY The Y Size.
     * \param sizeYIsValid The Y Size is valid, i.e. you want to set it.
     *
     * \return Pointer to data frame if it it worked,
     *         NULL if it didn't. See errno.
     */
    DataFrame * ( * CreateHidDisplaySizeRequest) (Protocol * self, Device * device, MessageAction action,
                                                                   uint32_t sizeX, bool sizeXIsValid,
                                                                   uint32_t sizeY, bool sizeYIsValid);

#endif // !defined(PROTOCOL_PROTOCOL_H) || defined(CONTAINS_PROTOCOL)
#if !defined(PROTOCOL_PROTOCOL_H) && !defined(CONTAINS_PROTOCOL)
};

// Exported Functions

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief This is the Protocol factory function.
 *
 * This is the Protocol class factory function. A new Protocol structure is
 * allocated and if this succeeds the fields of the structure are populated
 * using the arguments passed to the constructor.
 * \n\n
 * Should allocation fail, NULL will be returned and errno is set as follows:
 * - ::EOUTOFMEMORY - Memory allocation failed.
 * - ::EBADNAME - The protocolString does not have a protocol name of the
 *                correct format.
 * - ::EUNKNOWNPROTOCOL - There is no defined protocol with a name which
 *                       matches the name in protocolString.
 * - ::EBADCONNECTION - The connection pointer is not valid.
 * - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
 *                        critical section. This should not happen.
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 *
 * \param connection A pointer to the Connection instance that will be used
 *                   with this protocol.
 * \param protocolString  A pointer to a NUL terminated char string holding a
 *                        unique human readable identifer. The contents of the
 *                        string are copied to the Protocol structucture.
 *                        The length of the string as measured by strlen should
 *                        be at most MAX_ENTRY_NAME_LENGTH chars.
 * \param dataFrameType An identifying string that determines the type of data
 *                      frames this protocol should traffic in.
 *
 * \return Returns a pointer the allocated Protocol structure upon success,
 *         otherwise a NULL pointer is returned and errno is set accordingly.
 */
DLLEXTERNAL Protocol * Protocol_GetInstance (Connection * connection,
                                             char * protocolString,
                                             char * dataFrameType);

/*!
 * \brief Add a new protocol to the list of those available.
 *
 * This is the method used to find inform the zForce SDK of protocols which
 * can be used for communication.
 * \n\n
 * Upon error the errno variable is set as follows:
 * - ::EALREADYADDED - A protocol matching the name and data frame type has
 *                     already been added.
 * - ::EOUTOFMEMORY - The memory used to store protocol details has been
 *                    exhausted.
 * - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
 *                        critical section. This should not happen.
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 * \param protocolEntry The description of the protocol to add.
 *
 * \return true if the protocol has been added. Otherwise false which indicates
 *         failure and the errno variable should be inspected for the reason
 *         why.
 */
DLLEXTERNAL bool Protocol_AddProtocol (ProtocolEntry * protocolEntry);

/*!
 * \brief Initialize the Protocol module.
 *
 * Perform the initialization of the Protocol module.
 * \n\n
 * Upon error the errno variable is set as follows:
 * - ::EALREADYINITIALIZED - A previous initialization is still in effect.
 *
 * \return true upon success, false otherwise.
 */
DLLINTERNAL bool Protocol_Initialize (void);

/*!
 * \brief Unitialize the Protocol module.
 *
 * Perform the uninitialization of the Protocol module.
 * Any allocated resources are deallocated.
 *
 * \return No return value.
 */
DLLINTERNAL void Protocol_Uninitialize (void);

#ifdef __cplusplus
}
#endif // __cplusplus

#define PROTOCOL_PROTOCOL_H
#endif // !defined(PROTOCOL_PROTOCOL_H) && !defined(CONTAINS_PROTOCOL)

