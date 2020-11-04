/*! \file
 * \brief A TouchActiveAreaMessage contains the Touch Active Area of a Device.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_TOUCHACTIVEAREAMESSAGE_TOUCHACTIVEAREAMESSAGE_H) && !defined(CONTAINS_TOUCHACTIVEAREAMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a touch active area message.
 *
 * This structure represents a message which indicates what touch active area
 * a device uses.
 */
struct TouchActiveAreaMessage
{
#endif // !defined(MESSAGE_TOUCHACTIVEAREAMESSAGE_TOUCHACTIVEAREAMESSAGE_H) && !defined(CONTAINS_TOUCHACTIVEAREAMESSAGE)
#if !defined(MESSAGE_TOUCHACTIVEAREAMESSAGE_TOUCHACTIVEAREAMESSAGE_H) || defined(CONTAINS_TOUCHACTIVEAREAMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    #define CONTAINS_TOUCHACTIVEAREA
    #include <zForceTypes.h>
    #undef CONTAINS_TOUCHACTIVEAREA
#endif // !defined(MESSAGE_TOUCHACTIVEAREAMESSAGE_TOUCHACTIVEAREAMESSAGE_H) || defined(CONTAINS_TOUCHACTIVEAREAMESSAGE)
#if !defined(MESSAGE_TOUCHACTIVEAREAMESSAGE_TOUCHACTIVEAREAMESSAGE_H) && !defined(CONTAINS_TOUCHACTIVEAREAMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for TouchActiveAreaMessage.
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
 * \return Pointer to TouchActiveAreaMessage.
 */
DLLINTERNAL TouchActiveAreaMessage * TouchActiveAreaMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_TOUCHACTIVEAREAMESSAGE_TOUCHACTIVEAREAMESSAGE_H
#endif // !defined(MESSAGE_TOUCHACTIVEAREAMESSAGE_TOUCHACTIVEAREAMESSAGE_H) && !defined(CONTAINS_TOUCHACTIVEAREAMESSAGE)

