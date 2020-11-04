/*! \file
 * \brief Handles requests to the PlatformDevice.
 *
 * PlatformDevice contains system-level requests, like getting the
 * MCU Unique Identifier, etc.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(DEVICE_PLATFORMDEVICE_PLATFORMDEVICE_H) && !defined(CONTAINS_PLATFORMDEVICE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief Struct representing a PlatformDevice.
 *
 * PlatformDevice contains system-level requests, like getting the
 * MCU Unique Identifier, etc.
 *
 */
struct PlatformDevice
{
#endif // !defined(DEVICE_PLATFORMDEVICE_PLATFORMDEVICE_H) && !defined(CONTAINS_PLATFORMDEVICE)
#if !defined(DEVICE_PLATFORMDEVICE_PLATFORMDEVICE_H) || defined(CONTAINS_PLATFORMDEVICE)
    #define CONTAINS_DEVICE
    #include <Device.h>
    #undef CONTAINS_DEVICE

    /*!
     * \brief Get the current finger frequency.
     *
     * Get the current finger frequency.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \return True for success, false for failure. See errno.
     */
    bool ( * GetFingerFrequency)(PlatformDevice * self);

    /*!
     * \brief Set the finger frequency.
     *
     * Set the current finger frequency.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param frequency The frequency to set.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetFingerFrequency)(PlatformDevice * self, uint32_t frequency);

    /*!
     * \brief Get the current idle frequency.
     *
     * Get the current finger frequency.
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
    bool ( * GetIdleFrequency)(PlatformDevice * self);

    /*!
     * \brief Set the idle frequency.
     *
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param frequency The frequency to set.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetIdleFrequency)(PlatformDevice * self, uint32_t frequency);

    /*!
     * \brief Get the Mcu Unique Identifier from the platform.
     *
     * Get the Mcu Unique Identifier from the platform.
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
    bool ( * GetMcuUniqueIdentifier)(PlatformDevice * self);

    /*!
     * \brief Set the Mcu Unique Identifier from the platform.
     *
     * Set the Mcu Unique Identifier from the platform.
     * \n\n
     * On failure, errno is set.
     * - ::EALREADYINPROGRESS - Another request is currently in progress.
     * - ::ENOTSUPPORTED - This request is not supported by this protocol and/or
     *                     Device.
     *
     * \param self Pointer to the struct itself.
     * \param identifier Pointer to the Identifier array to set.
     * \param length Buffer size.
     *
     * \return True for success, false for failure. See errno.
     */
    bool ( * SetMcuUniqueIdentifier)(PlatformDevice * self, uint8_t * identifier, uint32_t bufferSize);

#endif // !defined(DEVICE_PLATFORMDEVICE_PLATFORMDEVICE_H) || defined(CONTAINS_PLATFORMDEVICE)
#if !defined(DEVICE_PLATFORMDEVICE_PLATFORMDEVICE_H) && !defined(CONTAINS_PLATFORMDEVICE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal call used to create a new PlatformDevice.
 *
 * On failure, errno is set.
 * - ::EINVALIDSIZE - Invalid size
 *
 * \param connection The Connection the Device is associated with.
 * \param deviceType Which DeviceType to create.
 * \param deviceIndex Which Device Index to set.
 * \param size If this is used as a base class for another class, set size to
 *             non-zero.
 *
 * \return A pointer to the new Device.
 */
DLLINTERNAL PlatformDevice * PlatformDevice_New (Connection * connection, DeviceType deviceType, uint32_t deviceIndex,
                                                 size_t size);

#ifdef __cplusplus
}
#endif // _cplusplus

#define DEVICE_PLATFORMDEVICE_PLATFORMDEVICE_H
#endif // !defined(DEVICE_PLATFORMDEVICE_PLATFORMDEVICE_H) && !defined(CONTAINS_PLATFORMDEVICE)

