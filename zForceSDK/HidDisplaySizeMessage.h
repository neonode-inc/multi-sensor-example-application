/*! \file
 * \brief A HidDisplaySizeMessage that contains the Hid Display Size.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_HIDDISPLAYSIZEMESSAGE_HIDDISPLAYSIZEMESSAGE_H) && !defined(CONTAINS_HIDDISPLAYSIZEMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a Hid Display Size Message.
 *
 * This structure represents a message containing the Hid Display Size.
 */
struct HidDisplaySizeMessage
{
#endif // !defined(MESSAGE_HIDDISPLAYSIZEMESSAGE_HIDDISPLAYSIZEMESSAGE_H) && !defined(CONTAINS_HIDDISPLAYSIZEMESSAGE)
#if !defined(MESSAGE_HIDDISPLAYSIZEMESSAGE_HIDDISPLAYSIZEMESSAGE_H) || defined(CONTAINS_HIDDISPLAYSIZEMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint32_t SizeX;      //!< X Size.
    bool     HasSizeX;   //!< Is the X Size reported?
    uint32_t SizeY;      //!< Y Size.
    bool     HasSizeY;   //!< Is the Y Size reported?
#endif // !defined(MESSAGE_HIDDISPLAYSIZEMESSAGE_HIDDISPLAYSIZEMESSAGE_H) || defined(CONTAINS_HIDDISPLAYSIZEMESSAGE)
#if !defined(MESSAGE_HIDDISPLAYSIZEMESSAGE_HIDDISPLAYSIZEMESSAGE_H) && !defined(CONTAINS_HIDDISPLAYSIZEMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for HidDisplaySizeMessage.
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
 * \return Pointer to HidDisplaySizeMessage.
 */
DLLINTERNAL HidDisplaySizeMessage * HidDisplaySizeMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_HIDDISPLAYSIZEMESSAGE_HIDDISPLAYSIZEMESSAGE_H
#endif // !defined(MESSAGE_HIDDISPLAYSIZEMESSAGE_HIDDISPLAYSIZEMESSAGE_H) && !defined(CONTAINS_HIDDISPLAYSIZEMESSAGE)

