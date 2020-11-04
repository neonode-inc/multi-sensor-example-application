/*! \file
 * \brief A DisableMessage that disables a Device.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_DISABLEMESSAGE_DISABLEMESSAGE_H) && !defined(CONTAINS_DISABLEMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a disable message.
 *
 * This structure represents a message which indicates if
 * the scanning on a device is turned off.
 */
struct DisableMessage
{
#endif // !defined(MESSAGE_DISABLEMESSAGE_DISABLEMESSAGE_H) && !defined(CONTAINS_DISABLEMESSAGE)
#if !defined(MESSAGE_DISABLEMESSAGE_DISABLEMESSAGE_H) || defined(CONTAINS_DISABLEMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    bool Disabled; //!< Is Device Disabled.
#endif // !defined(MESSAGE_DISABLEMESSAGE_DISABLEMESSAGE_H) || defined(CONTAINS_DISABLEMESSAGE)
#if !defined(MESSAGE_DISABLEMESSAGE_DISABLEMESSAGE_H) && !defined(CONTAINS_DISABLEMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for DisableMessage.
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
 * \return Pointer to DisableMessage.
 */
DLLINTERNAL DisableMessage * DisableMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_DISABLEMESSAGE_DISABLEMESSAGE_H
#endif // !defined(MESSAGE_DISABLEMESSAGE_DISABLEMESSAGE_H) && !defined(CONTAINS_DISABLEMESSAGE)

