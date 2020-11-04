/*! \file
 * \brief A MergeTouchesMessage sets the mode for the device to handle all simultaneous touching 
 * objects as one large object.
 * 
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_MERGETOUCHESMESSAGE_MERGETOUCHESMESSAGE_H) && !defined(CONTAINS_MERGETOUCHESMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a merge touches message.
 *
 * This structure represents a message that decides if the
 * touching objects should be merged into one touch.
 */
struct MergeTouchesMessage
{
#endif // !defined(MESSAGE_MERGETOUCHESMESSAGE_MERGETOUCHESMESSAGE_H) && !defined(CONTAINS_OPERATIONMODESMESSAGE)
#if !defined(MESSAGE_MERGETOUCHESMESSAGE_MERGETOUCHESMESSAGE_H) || defined(CONTAINS_OPERATIONMODESMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    bool AreTouchesMerged; //!< Are touches merged?
#endif // !defined(MESSAGE_MERGETOUCHESMESSAGE_MERGETOUCHESMESSAGE_H) || defined(CONTAINS_OPERATIONMODESMESSAGE)
#if !defined(MESSAGE_MERGETOUCHESMESSAGE_MERGETOUCHESMESSAGE_H) && !defined(CONTAINS_OPERATIONMODESMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for MergeTouchesMessage.
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
 * \return Pointer to MergeTouchesMessage.
 */
DLLINTERNAL MergeTouchesMessage * MergeTouchesMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_MERGETOUCHESMESSAGE_MERGETOUCHESMESSAGE_H
#endif // !defined(MESSAGE_MERGETOUCHESMESSAGE_MERGETOUCHESMESSAGE_H) && !defined(CONTAINS_OPERATIONMODESMESSAGE)