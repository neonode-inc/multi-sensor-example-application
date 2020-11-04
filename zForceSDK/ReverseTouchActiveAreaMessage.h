/*! \file
 * \brief A ReverseTouchActiveAreaMessage contains the Touch Active Area of a Device.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_H) && \
    !defined(CONTAINS_REVERSETOUCHACTIVEAREAMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a reverse touch active area message.
 *
 * This structure represents a message which indicates what reverse touch active area
 * a device uses.
 */
struct ReverseTouchActiveAreaMessage
{
#endif // !defined(.._REVERSETOUCHACTIVEAREAMESSAGE_H) && !defined(CONTAINS_REVERSETOUCHACTIVEAREAMESSAGE)
#if !defined(MESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_H) || \
    defined(CONTAINS_REVERSETOUCHACTIVEAREAMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    #define CONTAINS_REVERSETOUCHACTIVEAREA
    #include <zForceTypes.h>
    #undef CONTAINS_REVERSETOUCHACTIVEAREA
#endif // !defined(.._REVERSETOUCHACTIVEAREAMESSAGE_H) || defined(CONTAINS_REVERSETOUCHACTIVEAREAMESSAGE)
#if !defined(MESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_H) && \
    !defined(CONTAINS_REVERSETOUCHACTIVEAREAMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for ReverseTouchActiveAreaMessage.
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
 * \return Pointer to ReverseTouchActiveAreaMessage.
 */
DLLINTERNAL ReverseTouchActiveAreaMessage * ReverseTouchActiveAreaMessage_New (MessageGroup messageGroup,
                                                                               uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_REVERSETOUCHACTIVEAREAMESSAGE_H
#endif // !defined(.._REVERSETOUCHACTIVEAREAMESSAGE_H) && !defined(CONTAINS_REVERSETOUCHACTIVEAREAMESSAGE)

