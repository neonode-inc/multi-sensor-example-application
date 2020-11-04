/*! \file
 * \brief An OffsetMessage that contains the Offset a Device is set to.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_OFFSETMESSAGE_OFFSETMESSAGE_H) && !defined(CONTAINS_OFFSETMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents an offset message.
 *
 * This structure represents a message containing offset information.
 */
struct OffsetMessage
{
#endif // !defined(MESSAGE_OFFSETMESSAGE_OFFSETMESSAGE_H) && !defined(CONTAINS_OFFSETMESSAGE)
#if !defined(MESSAGE_OFFSETMESSAGE_OFFSETMESSAGE_H) || defined(CONTAINS_OFFSETMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint32_t OffsetX;    //!< X Offset.
    bool     HasOffsetX; //!< Is the X Offset reported?
    uint32_t OffsetY;    //!< Y Offset.
    bool     HasOffsetY; //!< Is the Y Offset reported?
#endif // !defined(MESSAGE_OFFSETMESSAGE_OFFSETMESSAGE_H) || defined(CONTAINS_OFFSETMESSAGE)
#if !defined(MESSAGE_OFFSETMESSAGE_OFFSETMESSAGE_H) && !defined(CONTAINS_OFFSETMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for OffsetMessage.
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
 * \return Pointer to OffsetMessage.
 */
DLLINTERNAL OffsetMessage * OffsetMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_OFFSETMESSAGE_OFFSETMESSAGE_H
#endif // !defined(MESSAGE_OFFSETMESSAGE_OFFSETMESSAGE_H) && !defined(CONTAINS_OFFSETMESSAGE)

