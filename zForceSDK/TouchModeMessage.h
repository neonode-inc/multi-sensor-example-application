/*! \file
 * \brief A TouchModeMessage sets the touch mode for the device.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018-2020 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_TOUCHMODEMESSAGE_TOUCHMODEMESSAGE_H) && !defined(CONTAINS_TOUCHMODEMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a touch mode message.
 *
 * This structure represents a message that decides the touch mode.
 */
struct TouchModeMessage
{
#endif // !defined(MESSAGE_TOUCHMODEMESSAGE_TOUCHMODEMESSAGE_H) && !defined(CONTAINS_TOUCHMODEMESSAGE)
#if !defined(MESSAGE_TOUCHMODEMESSAGE_TOUCHMODEMESSAGE_H) || defined(CONTAINS_TOUCHMODEMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    TouchModes TouchMode;             //!< Which Touch Mode is currently active?
    bool       HasTouchMode;          //!< True if the message contained this value.
    uint32_t   ClickOnTouchTime;      //!< How long to wait for before a touch is clicked in Click on Touch Mode.
    bool       HasClickOnTouchTime;   //!< True if the message contained this value.
    uint32_t   ClickOnTouchRadius;    //!< How far the touch has to move before it is switched to Normal Mode.
    bool       HasClickOnTouchRadius; //!< True if the message contained this value.
#endif // !defined(MESSAGE_TOUCHMODEMESSAGE_TOUCHMODEMESSAGE_H) || defined(CONTAINS_TOUCHMODEMESSAGE)
#if !defined(MESSAGE_TOUCHMODEMESSAGE_TOUCHMODEMESSAGE_H) && !defined(CONTAINS_TOUCHMODEMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for TouchModeMessage.
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
 * \return Pointer to TouchModeMessage.
 */
DLLINTERNAL TouchModeMessage * TouchModeMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_TOUCHMODEMESSAGE_TOUCHMODEMESSAGE_H
#endif // !defined(MESSAGE_TOUCHMODEMESSAGE_TOUCHMODEMESSAGE_H) && !defined(CONTAINS_TOUCHMODEMESSAGE)

