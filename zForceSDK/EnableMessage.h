/*! \file
 * \brief An EnableMessage that enables a Device.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_ENABLEMESSAGE_ENABLEMESSAGE_H) && !defined(CONTAINS_ENABLEMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents an enable message.
 *
 * This structure represents a message which indicates if
 * the scanning on a device is turned on and if it is continous or
 * has a defined number of messages to send set.
 */
struct EnableMessage
{
#endif // !defined(MESSAGE_ENABLEMESSAGE_ENABLEMESSAGE_H) && !defined(CONTAINS_ENABLEMESSAGE)
#if !defined(MESSAGE_ENABLEMESSAGE_ENABLEMESSAGE_H) || defined(CONTAINS_ENABLEMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    bool     Enabled;          //!< Is Device Enabled.
    bool     ContinuousMode;   //!< Is Device set to Continuous Mode.
    uint32_t NumberOfMessages; //!< Number Of Messages.
#endif // !defined(MESSAGE_ENABLEMESSAGE_ENABLEMESSAGE_H) || defined(CONTAINS_ENABLEMESSAGE)
#if !defined(MESSAGE_ENABLEMESSAGE_ENABLEMESSAGE_H) && !defined(CONTAINS_ENABLEMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for EnableMessage.
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
 * \return Pointer to EnableMessage.
 */
DLLINTERNAL EnableMessage * EnableMessage_New (MessageGroup messageGroup,
                                               uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_ENABLEMESSAGE_ENABLEMESSAGE_H
#endif // !defined(MESSAGE_ENABLEMESSAGE_ENABLEMESSAGE_H) && !defined(CONTAINS_ENABLEMESSAGE)

