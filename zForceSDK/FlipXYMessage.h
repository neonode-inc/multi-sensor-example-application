/*! \file
 * \brief A FlipXYMessage that contains a bool for wether the axes are flipped or not.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_FLIPXYMESSAGE_FLIPXYMESSAGE_H) && !defined(CONTAINS_FLIPXYMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a FlipXY Message.
 *
 * This structure represents a message containing the FlipXY message.
 */
struct FlipXYMessage
{
#endif // !defined(MESSAGE_FLIPXYMESSAGE_FLIPXYMESSAGE_H) && !defined(CONTAINS_FLIPXYMESSAGE)
#if !defined(MESSAGE_FLIPXYMESSAGE_FLIPXYMESSAGE_H) || defined(CONTAINS_FLIPXYMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    bool AxesAreFlipped;   //!< Are the axes flipped?
#endif // !defined(MESSAGE_FLIPXYMESSAGE_FLIPXYMESSAGE_H) || defined(CONTAINS_FLIPXYMESSAGE)
#if !defined(MESSAGE_FLIPXYMESSAGE_FLIPXYMESSAGE_H) && !defined(CONTAINS_FLIPXYMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for FlipXYMessage.
 *
 * Do not use this, but use the Factory creator instead.
 * \n\n
 * On failure, see errno.
 * - ::EOUTOFMEMORY - Out of memory.
 * - ::EINVALIDSIZE - Invalid size.
 *
 * \param messageGroup MessageGroup of Message.
 * \param size If this is used as a base class for another class, set size to non-zero.
 *
 * \return Pointer to FlipXYMessage.
 */
DLLINTERNAL FlipXYMessage * FlipXYMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_FLIPXYMESSAGE_FLIPXYMESSAGE_H
#endif // !defined(MESSAGE_FLIPXYMESSAGE_FLIPXYMESSAGE_H) && !defined(CONTAINS_FLIPXYMESSAGE)


