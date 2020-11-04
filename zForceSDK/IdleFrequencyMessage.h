/*! \file
 * \brief An IdleFrequencyMessage.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_IDLEFREQUENCYMESSAGE_IDLEFREQUENCYMESSAGE_H) && !defined(CONTAINS_IDLEFREQUENCYMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents an idle frequency message.
 *
 * This structure represents a message containing idle frequency.
 */
struct IdleFrequencyMessage
{
#endif // !defined(MESSAGE_IDLEFREQUENCYMESSAGE_IDLEFREQUENCYMESSAGE_H) && !defined(CONTAINS_IDLEFREQUENCYMESSAGE)
#if !defined(MESSAGE_IDLEFREQUENCYMESSAGE_IDLEFREQUENCYMESSAGE_H) || defined(CONTAINS_IDLEFREQUENCYMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint32_t Frequency; //!< Frequency.
#endif // !defined(MESSAGE_IDLEFREQUENCYMESSAGE_IDLEFREQUENCYMESSAGE_H) || defined(CONTAINS_IDLEFREQUENCYMESSAGE)
#if !defined(MESSAGE_IDLEFREQUENCYMESSAGE_IDLEFREQUENCYMESSAGE_H) && !defined(CONTAINS_IDLEFREQUENCYMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for IdleFrequencyMessage.
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
 * \return Pointer to IdleFrequencyMessage.
 */
DLLINTERNAL IdleFrequencyMessage * IdleFrequencyMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_IDLEFREQUENCYMESSAGE_IDLEFREQUENCYMESSAGE_H
#endif // !defined(MESSAGE_IDLEFREQUENCYMESSAGE_IDLEFREQUENCYMESSAGE_H) && !defined(CONTAINS_IDLEFREQUENCYMESSAGE)

