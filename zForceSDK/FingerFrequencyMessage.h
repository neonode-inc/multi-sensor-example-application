/*! \file
 * \brief A FingerFrequencyMessage.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_FINGERFREQUENCYMESSAGE_FINGERFREQUENCYMESSAGE_H) && !defined(CONTAINS_FINGERFREQUENCYMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a finger frequency message.
 *
 * This structure represents a message containing finger frequency.
 */
struct FingerFrequencyMessage
{
#endif // !defined(MESSAGE_FINGERFREQUENCYMESSAGE_FINGERFREQUENCYMESSAGE_H) && !defined(CONTAINS_FINGERFREQUENCYMESSAGE)
#if !defined(MESSAGE_FINGERFREQUENCYMESSAGE_FINGERFREQUENCYMESSAGE_H) || defined(CONTAINS_FINGERFREQUENCYMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint32_t Frequency; //!< Frequency.
#endif // !defined(MESSAGE_FINGERFREQUENCYMESSAGE_FINGERFREQUENCYMESSAGE_H) || defined(CONTAINS_FINGERFREQUENCYMESSAGE)
#if !defined(MESSAGE_FINGERFREQUENCYMESSAGE_FINGERFREQUENCYMESSAGE_H) && !defined(CONTAINS_FINGERFREQUENCYMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for FingerFrequencyMessage.
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
 * \return Pointer to FingerFrequencyMessage.
 */
DLLINTERNAL FingerFrequencyMessage * FingerFrequencyMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_FINGERFREQUENCYMESSAGE_FINGERFREQUENCYMESSAGE_H
#endif // !defined(MESSAGE_FINGERFREQUENCYMESSAGE_FINGERFREQUENCYMESSAGE_H) && !defined(CONTAINS_FINGERFREQUENCYMESSAGE)

