/*! \file
 * \brief Handles requests to the CoreDevice.
 *
 * CoreDevice is a specific implementation of a SensorDevice for zForce Core(TM).
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(DEVICE_SENSORDEVICE_COREDEVICE_COREDEVICE_H) && !defined(CONTAINS_COREDEVICE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief Struct representing a CoreDevice.
 *
 * Struct representing a CoreDevice. CoreDevice is a specific
 * implementation of a SensorDevice for zForce Core(TM).
 *
 */
struct CoreDevice
{
#endif // !defined(DEVICE_SENSORDEVICE_COREDEVICE_COREDEVICE_H) && !defined(CONTAINS_COREDEVICE)
#if !defined(DEVICE_SENSORDEVICE_COREDEVICE_COREDEVICE_H) || defined(CONTAINS_COREDEVICE)
    #define CONTAINS_SENSORDEVICE
    #include <SensorDevice.h>
    #undef CONTAINS_SENSORDEVICE
#endif // !defined(DEVICE_SENSORDEVICE_COREDEVICE_COREDEVICE_H) || defined(CONTAINS_COREDEVICE)
#if !defined(DEVICE_SENSORDEVICE_COREDEVICE_COREDEVICE_H) && !defined(CONTAINS_COREDEVICE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal call used to create a new CoreDevice.
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
DLLINTERNAL CoreDevice * CoreDevice_New (Connection * connection,
                                         DeviceType deviceType,
                                         uint32_t deviceIndex, size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define DEVICE_SENSORDEVICE_COREDEVICE_COREDEVICE_H
#endif // !defined(DEVICE_SENSORDEVICE_COREDEVICE_COREDEVICE_H) && !defined(CONTAINS_COREDEVICE)

