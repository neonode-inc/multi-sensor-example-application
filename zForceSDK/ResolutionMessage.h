/*! \file
 * \brief A ResolutionMessage that contains the Resolution a Device is set to.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_RESOLUTIONMESSAGE_RESOLUTIONMESSAGE_H) && !defined(CONTAINS_RESOLUTIONMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a resolution message.
 *
 * This structure represents a message containing resolution information.
 */
struct ResolutionMessage
{
#endif // !defined(MESSAGE_RESOLUTIONMESSAGE_RESOLUTIONMESSAGE_H) && !defined(CONTAINS_RESOLUTIONMESSAGE)
#if !defined(MESSAGE_RESOLUTIONMESSAGE_RESOLUTIONMESSAGE_H) || defined(CONTAINS_RESOLUTIONMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    #define CONTAINS_CARTESIANCOORDINATES
    #include <zForceTypes.h>
    #undef CONTAINS_CARTESIANCOORDINATES
#endif //!defined(MESSAGE_RESOLUTIONMESSAGE_RESOLUTIONMESSAGE_H) || defined(CONTAINS_RESOLUTIONMESSAGE)
#if !defined(MESSAGE_RESOLUTIONMESSAGE_RESOLUTIONMESSAGE_H) && !defined(CONTAINS_RESOLUTIONMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for ResolutionMessage.
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
 * \return Pointer to ResolutionMessage.
 */
DLLINTERNAL ResolutionMessage * ResolutionMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_RESOLUTIONMESSAGE_RESOLUTIONMESSAGE_H
#endif // !defined(MESSAGE_RESOLUTIONMESSAGE_RESOLUTIONMESSAGE_H) && !defined(CONTAINS_RESOLUTIONMESSAGE)

