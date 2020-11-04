/*! \file
 * \brief Base Device class.
 *
 * A Device is used to make requests to the unit.
 * Subclasses of this implement that actual functionality.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(DEVICE_DEVICE_H) && !defined(CONTAINS_DEVICE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief Brief Device base class.
 *
 * All Device types inherit this base struct.
 */
struct Device
{
#endif // !defined(DEVICE_DEVICE_H) && !defined(CONTAINS_DEVICE)
#if !defined(DEVICE_DEVICE_H) || defined(CONTAINS_DEVICE)
    zForce     * zForce;      //!< Pointer to zForce.
    Connection * Connection;  //!< The Connection this Device is part of.
    DeviceType   DeviceType;  //!< Which type of Device this is.
    uint32_t     DeviceIndex; //!< Which Device Index this device has.
    //! Future: List of Storage Devices. Will change type during implementation.
    Device    ** StorageDevices;
    uint32_t     NumberOfStorageDevices;   //!< Number of Storage Devices.
    void       * PrivateProtocolData;      //!< Private Protocol Data.
    /*!
     * \brief Destructor.
     *
     * Destructs the Device and all base structs.
     *
     * \param self Pointer to the struct itself.
     *
     * \return No return value.
     */
    void         ( * Destructor)(Device * self);
#endif // !defined(DEVICE_DEVICE_H) || defined(CONTAINS_DEVICE)
#if !defined(DEVICE_DEVICE_H) && !defined(CONTAINS_DEVICE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal call to get a new Device with the specified Type and Index.
 *
 * On failure, errno is set.
 * - ::EOUTOFMEMORY - Out of memory.
 * - ::EBADCONNECTION - Bad Connection pointer.
 * - ::EUNKNOWNDEVICETYPE - Uknown device type. Make sure USE_XXX is defined.
 *
 * \param connection The Connection the Device is associated with.
 * \param deviceType Which DeviceType to create.
 * \param deviceIndex Which Device Index to set.
 *
 * \return A pointer to the new Device.
 */
DLLINTERNAL Device * Device_GetInstance (Connection * connection,
                                         DeviceType deviceType,
                                         uint32_t deviceIndex);

/*!
 * \brief Internal call used only by Device and subclasses to create a new base
 * Device.
 *
 * On failure, errno is set.
 * - ::EOUTOFMEMORY - Out of memory.
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
DLLINTERNAL Device * Device_New (Connection * connection,
                                 DeviceType deviceType,
                                 uint32_t deviceIndex,
                                 size_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

// Violating Barr 4.2d but we have an exception.
#if defined(USE_PLATFORMDEVICE) || !defined(COMPILING_ZFORCE_SDK)
    #include <PlatformDevice.h>
#endif // defined(USE_PLATFORMDEVICE) || !defined(COMPILING_ZFORCE_SDK)

#if defined(USE_SENSORDEVICE) || !defined(COMPILING_ZFORCE_SDK)
    #include <SensorDevice.h>
#endif // defined(USE_SENSORDEVICE) || !defined(COMPILING_ZFORCE_SDK)

#if defined(USE_COREDEVICE) || !defined(COMPILING_ZFORCE_SDK)
    #include <CoreDevice.h>
#endif // defined(USE_COREDEVICE) || !defined(COMPILING_ZFORCE_SDK)

#if defined(USE_AIRDEVICE) || !defined(COMPILING_ZFORCE_SDK)
    #include <AirDevice.h>
#endif // defined(USE_AIRDEVICE) || !defined(COMPILING_ZFORCE_SDK)

#if defined(USE_PLUSDEVICE) || !defined(COMPILING_ZFORCE_SDK)
    #include <PlusDevice.h>
#endif // defined(USE_PLUSDEVICE) || !defined(COMPILING_ZFORCE_SDK)

#if defined(USE_LIGHTINGDEVICE) || !defined(COMPILING_ZFORCE_SDK)
    #include <LightingDevice.h>
#endif // defined(USE_LIGHTINGDEVICE) || !defined(COMPILING_ZFORCE_SDK)

#define DEVICE_DEVICE_H
#endif // !defined(DEVICE_DEVICE_H) && !defined(CONTAINS_DEVICE)

