/*! \file
 * \brief A NumberOfTrackedObjectsMessage.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_H) && \
    !defined(CONTAINS_NUMBEROFTRACKEDOBJECTSMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a number of tracked objects message.
 *
 * This structure represents a message which indicates
 * the number of objects to be tracked by a device.
 */
struct NumberOfTrackedObjectsMessage
{
#endif // !defined(.._NUMBEROFTRACKEDOBJECTSMESSAGE_H) && !defined(CONTAINS_NUMBEROFTRACKEDOBJECTSMESSAGE)
#if !defined(MESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_H) || \
    defined(CONTAINS_NUMBEROFTRACKEDOBJECTSMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint32_t NumberOfTrackedObjects;  //!< Tracked object count.
#endif // !defined(.._NUMBEROFTRACKEDOBJECTSMESSAGE_H) || defined(CONTAINS_NUMBEROFTRACKEDOBJECTSMESSAGE)
#if !defined(MESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_H) && \
    !defined(CONTAINS_NUMBEROFTRACKEDOBJECTSMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for NumberOfTrackedObjectsMessage.
 *
 * Do not use this, but use the Factory creator instead.
 * \n\n
 * On failure, see errno.
 * - ::EOUTOFMEMORY - Out of memory.
 * - ::EINVALIDSIZE - Invalid size.
 *
 * \param messageGroup MessageGroup of Message.
 * \param size If this is used as a base class for another class, set size to
 *             non-zero.
 *
 * \return Pointer to NumberOfTrackedObjectsMessage.
 */
DLLINTERNAL NumberOfTrackedObjectsMessage * NumberOfTrackedObjectsMessage_New (MessageGroup messageGroup,
                                                                               uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_NUMBEROFTRACKEDOBJECTSMESSAGE_H
#endif // !defined(.._NUMBEROFTRACKEDOBJECTSMESSAGE_H) && !defined(CONTAINS_NUMBEROFTRACKEDOBJECTSMESSAGE)

