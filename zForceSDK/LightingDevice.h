/*! \file
 * \brief Handles requests to the LightingDevice.
 *
 * LightingDevice contains system-level requests, like getting the
 * MCU Unique Identifier, etc.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(DEVICE_LIGHTINGDEVICE_LIGHTINGDEVICE_H) && !defined(CONTAINS_LIGHTINGDEVICE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief Struct representing a LightingDevice.
 *
 * LightingDevices only task is to handle lighting such as RGB LEDs etc.
 *
 */
struct LightingDevice
{
#endif // !defined(DEVICE_LIGHTINGDEVICE_LIGHTINGDEVICE_H) && !defined(CONTAINS_LIGHTINGDEVICE)
#if !defined(DEVICE_LIGHTINGDEVICE_LIGHTINGDEVICE_H) || defined(CONTAINS_LIGHTINGDEVICE)
    #define CONTAINS_DEVICE
    #include <Device.h>
    #undef CONTAINS_DEVICE
#endif // !defined(DEVICE_LIGHTINGDEVICE_LIGHTINGDEVICE_H) || defined(CONTAINS_LIGHTINGDEVICE)
#if !defined(DEVICE_LIGHTINGDEVICE_LIGHTINGDEVICE_H) && !defined(CONTAINS_LIGHTINGDEVICE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal call used to create a LightingDevice.
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
DLLINTERNAL LightingDevice * LightingDevice_New (Connection * connection,
                                                 DeviceType deviceType,
                                                 uint32_t deviceIndex,
                                                 size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define DEVICE_LIGHTINGDEVICE_LIGHTINGDEVICE_H
#endif // !defined(DEVICE_LIGHTINGDEVICE_LIGHTINGDEVICE_H) && !defined(CONTAINS_LIGHTINGDEVICE)

