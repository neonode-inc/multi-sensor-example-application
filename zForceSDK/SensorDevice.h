/*! \file
 * \brief Handles requests to the SensorDevice, a meta device.
 *
 * SensorDevice is a meta device as it is not a real device and cannot be
 * instantiated by itself. It contains everything that is shared between all
 * the touch Sensor types, currently CoreDevice, AirDevice and PlusDevice.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2020 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(DEVICE_SENSORDEVICE_SENSORDEVICE_H) && !defined(CONTAINS_SENSORDEVICE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief Struct representing a SensorDevice, a meta device.
 *
 * SensorDevice is a meta device as it is not a real device and cannot be
 * instantiated by itself. It contains everything that is shared between all
 * the touch Sensor types, currently CoreDevice, AirDevice and PlusDevice.
 *
 */
struct SensorDevice
{
#endif // !defined(DEVICE_SENSORDEVICE_SENSORDEVICE_H) && !defined(CONTAINS_SENSORDEVICE)
#if !defined(DEVICE_SENSORDEVICE_SENSORDEVICE_H) || defined(CONTAINS_SENSORDEVICE)
    #define CONTAINS_DEVICE
    #include <Device.h>
    #undef CONTAINS_DEVICE
    CartesianCoordinates    Resolution;             //!< Resolution of the device.
    TouchActiveArea         TouchActiveArea;        //!< Touch Active Area of the device.
    ReverseTouchActiveArea  ReverseTouchActiveArea; //!< Reverse The Touch Active Area of the device.

    /*!
     * \brief Ask the Device if it is enabled.
     *
     * Ask the Device if it is enabled. Also reports if the device is in
     * continuous mode and number of messages left to receive.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetEnable)(SensorDevice * self);

    /*!
     * \brief Enable the device.
     *
     * Enable the device and set it to either continuous mode or a specified
     * number of messages. Not all protocols handle non-continuous mode.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     * - ::EINVALIDINPUT - Continuous cannot be false when numberOfMessages = 0.
     *
     * \param self Pointer to the struct itself.
     * \param continuousMode Set to true for continuous mode.
     * \param numberOfMessages When in non-continuous mode, specifies how many
     *                         Messages to receive before the Device disables
     *                         itself. May not be 0 when continuousMode ==
     *                         false.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetEnable)(SensorDevice * self, bool continuousMode, uint32_t numberOfMessages);

    /*!
     * \brief Ask the Device if it is disabled.
     *
     * Ask the device if it is disabled.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetDisable)(SensorDevice * self);

    /*!
     * \brief Disable the device.
     *
     * Disable the device. Messages will stop arriving as soon as the Device
     * processes the request, but Messages already in progress will still arrive
     * as normal.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetDisable)(SensorDevice * self);

    /*!
     * \brief Get the current Operating Modes of the Device.
     *
     * Gets the current Operating Modes of the Device as two bitmasks.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetOperationModes)(SensorDevice * self);

    /*!
     * \brief Set the current Operating Modes of the Device.
     *
     * Sets the current Operating Modes of the Device as two bitmasks.
     * Setting the modeMask bit for a specific Mode to 1 changes it to
     * become the corresponding bit in modeValues but setting the bit to 0
     * does not change it.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     * - ::EINVALIDINPUT - The modeMask and/or modeValue fields try to set bits
     *                     that are not defined.
     *
     * \param self Pointer to the struct itself.
     * \param modeMask A bit set to 1 means set to the corresponding bit in
     *                 the modeValue field and 0 means do not change this bit.
     * \param modeValue The value to set the bits to.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetOperationModes)(SensorDevice * self, OperationModes modeMask, OperationModes modeValues);

    /*!
     * \brief Get the current Resolution of the Device.
     *
     * Gets the current Resolution of the Device.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetResolution)(SensorDevice * self);

    /*!
     * \brief Set the current Resolution of the Device.
     *
     * Sets the current Resolution of the Device.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param x The Resolution of the X axis.
     * \param xIsValid Set to true to change this value or false to ignore
     *                 it. Ignored on a Device that does not allow it.
     * \param y The Resolution of the Y axis.
     * \param yIsValid Set to true to change this value or false to ignore
     *                 it. Ignored on a Device that does not allow it.
     * \param z The Resolution of the Z axis.
     * \param zIsValid Set to true to change this value or false to ignore
     *                 it. Ignored on a Device that does not allow it.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetResolution)(SensorDevice * self, uint32_t x, bool xIsValid,
                                                 uint32_t y, bool yIsValid,
                                                 uint32_t z, bool zIsValid);

    /*!
     * \brief Gets the current reverse setting for the Touch Active Area.
     *
     * Gets the current reverse setting for the Touch Active Area.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetReverseTouchActiveArea)(SensorDevice * self);

    /*!
     * \brief Reverse the Touch Active Area of the Device.
     *
     * Reverse the Touch Active Area of the Device.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     * - ::EINVALIDINPUT - Lower boundary input values must be lower than upper.
     *
     * \param self Pointer to the struct itself.
     * \param xIsReversed True to reverse the X axis.
     * \param yIsReversed True to reverse the Y axis.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetReverseTouchActiveArea)(SensorDevice * self, bool xIsReversed, bool yIsReversed);

    /*!
     * \brief Gets the current FlipXY setting.
     *
     * Gets the current FlipXY setting.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool( * GetFlipXY)(SensorDevice * self);

    /*!
     * \brief Sets the FlipXY setting.
     *
     * Enables/Disables flipping the X-axis and Y-axis.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or Device.
     * - ::EINVALIDINPUT - Lower boundary input values must be lower than upper.
     *
     * \param self Pointer to the struct itself.
     * \param axesAreflipped True to flip the axes.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetFlipXY)(SensorDevice * self, bool axesAreFlipped);

    /*!
     * \brief Gets the current ReflectiveEdgeFilter setting.
     *
     * Gets the current ReflectiveEdgeFilter setting.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool( * GetReflectiveEdgeFilter)(SensorDevice * self);

    /*!
     * \brief Sets the ReflectiveEdgeFilter setting.
     *
     * Enables/Disables the ReflectiveEdgeFilter.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or Device.
     * - ::EINVALIDINPUT - Lower boundary input values must be lower than upper.
     *
     * \param self Pointer to the struct itself.
     * \param isFilterOn is true if the filter is on, otherwise false.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetReflectiveEdgeFilter)(SensorDevice * self, bool isFilterOn);

    /*!
     * \brief Gets the current MergeTouches setting.
     *
     * Gets the current MergeTouches setting.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool( * GetMergeTouches)(SensorDevice * self);

    /*!
     * \brief Sets the MergeTouches setting.
     *
     * Enables/Disables the MergeTouches setting in the sensor.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or Device.
     * - ::EINVALIDINPUT - Lower boundary input values must be lower than upper.
     *
     * \param self Pointer to the struct itself.
     * \param areTouchesMerged is true if the touches are merged, otherwise false.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetMergeTouches)(SensorDevice * self, bool areTouchesMerged);

    /*!
     * \brief Get the current Touch Active Area of the Device.
     *
     * Gets the current Touch Active Area of the Device.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetTouchActiveArea)(SensorDevice * self);

    /*!
     * \brief Set the current Touch Active Area of the Device.
     *
     * Sets the current Touch Active Area of the Device.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     * - ::EINVALIDINPUT - Lower boundary input values must be lower than upper.
     *
     * \param self Pointer to the struct itself.
     * \param lowerBoundaryX The lower boundary for the X axis to set.
     * \param upperBoundaryX The upper boundary for teh X axis to set.
     * \param xIsValid Set to true to change the values or false to ignore.
     * \param lowerBoundaryY The lower boundary for the Y axis to set.
     * \param upperBoundaryY The upper boundary for teh Y axis to set.
     * \param yIsValid Set to true to change the values or false to ignore.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetTouchActiveArea)(SensorDevice * self, uint32_t lowerBoundaryX, uint32_t upperBoundaryX, bool xIsValid,
                                                      uint32_t lowerBoundaryY, uint32_t upperBoundaryY, bool yIsValid);

    /*!
     * \brief Get the current Detected Object Size Restriction of the Device.
     *
     * Gets the current Detected Object Size Restriction.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetDetectedObjectSizeRestriction)(SensorDevice * self);

    /*!
     * \brief Set the current Detected Object Size Restriction of the Device.
     *
     * Sets the current Detected Object Size Restriction of the device.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     * - ::EINVALIDINPUT - Lower boundary input values must be lower than upper.
     *
     * \param self Pointer to the struct itself.
     * \param minimumSize The minimum object size to detect by device.
     * \param maximumSize The maximum object size to detect by device.
     * \param minimumSizeIsValid Set to True to alter minimumSize detection.
     * \param maximumSizeIsValid Set to True to alter maximumSize detection.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetDetectedObjectSizeRestriction)(SensorDevice * self,
                                               uint32_t minimumSize,
                                               uint32_t maximumSize,
                                               bool minimumSizeIsValid,
                                               bool maximumSizeIsValid);

    /*!
     * \brief Get the number of tracked objects.
     *
     * Get the number of tracked objects.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetNumberOfTrackedObjects) (SensorDevice * self);

    /*!
     * \brief Set the number of tracked objects.
     *
     * Set the number of tracked objects.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param numberOfTrackedObjects Tracked object count.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetNumberOfTrackedObjects) (SensorDevice * self,
                                         uint32_t numberOfTrackedObjects);

    /*!
     * \brief Get the X and Y offsets.
     *
     * Get the X and Y offsets.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetOffset) (SensorDevice * self);

    /*!
     * \brief Set the X and Y offsets.
     *
     * Set the X and Y offsets.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param offsetX X Offset.
     * \param offsetXIsValid Offset X is valid, i.e. you want to set X Offset.
     * \param offsetY Y Offset.
     * \param offsetYIsValid Offset Y is valid, i.e. you want to set Y Offset.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetOffset) (SensorDevice * self, uint32_t offsetX, bool offsetXIsValid,
                                              uint32_t offsetY, bool offsetYIsValid);

    /*!
     * \brief Get the Hid Display Size.
     *
     * Get the Hid Display Size.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetHidDisplaySize) (SensorDevice * self);

    /*!
     * \brief Set the Hid Display Size.
     *
     * Set the Hid Display Size.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param sizeX X Size.
     * \param sizeXIsValid X Size is valid, i.e. you want to set Size X.
     * \param sizeY Y Size.
     * \param sizeYIsValid Y Size is valid, i.e. you want to set Size Y.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetHidDisplaySize) (SensorDevice * self, uint32_t sizeX, bool sizeXIsValid,
                                                      uint32_t sizeY, bool sizeYIsValid);

    /*!
     * \brief Get the Touch Mode.
     *
     * Get the Touch Mode.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetTouchMode) (SensorDevice * self);

    /*!
     * \brief Set the Touch Mode.
     *
     * Set the Touch Mode.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param touchMode Touch Mode to set.
     * \param touchModeIsValid Touch Mode is valid, i.e. you want to set Touch Mode.
     * \param clickOnTouchTime Click on Touch Time in ms.
     * \param clickOnTouchTimeIsValid Click On Touch Time is valid, i.e. you want to set Click On Touch Time.
     * \param clickOnTouchRadius Click on Touch Radius in ms.
     * \param clickOnTouchRadiusIsValid Click On Touch Radius is valid, i.e. you want to set Click On Touch Radius.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetTouchMode) (SensorDevice * self, TouchModes touchMode, bool touchModeIsValid,
                                                 uint32_t clickOnTouchTime, bool clickOnTouchTimeIsValid,
                                                 uint32_t clickOnTouchRadius, bool clickOnTouchRadiusIsValid);

#endif // !defined(DEVICE_SENSORDEVICE_SENSORDEVICE_H) || defined(CONTAINS_SENSORDEVICE)
#if !defined(DEVICE_SENSORDEVICE_SENSORDEVICE_H) && !defined(CONTAINS_SENSORDEVICE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal call used to create a new SensorDevice.
 *
 * On failure, errno is set.
 * - ::EINVALIDSIZE - Invalid size.
 *
 * \param connection The Connection the Device is associated with.
 * \param deviceType Which DeviceType to create.
 * \param deviceIndex Which Device Index to set.
 * \param size If this is used as a base class for another class, set size to
 *             non-zero.
 *
 * \return A pointer to the new Device.
 */
DLLINTERNAL SensorDevice * SensorDevice_New (Connection * connection, DeviceType deviceType, uint32_t deviceIndex,
                                                                                             size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define DEVICE_SENSORDEVICE_SENSORDEVICE_H
#endif // !defined(DEVICE_SENSORDEVICE_SENSORDEVICE_H) && !defined(CONTAINS_SENSORDEVICE)

