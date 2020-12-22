/*! \file
 * \brief A ReflectiveEdgeFilterMessage contains the modes the Device is set to.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_REFLECTIVEEDGEFILTERMESSAGE_REFLECTIVEEDGEFILTERMESSAGE_H) && \
            !defined(CONTAINS_REFLECTIVEEDGEFILTERMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a operation mode message.
 *
 * This structure represents a message that turns on a filter that
 * reduces the chance of ghost touches if there is highly reflective
 * surface outside of the touch active area.
 */
struct ReflectiveEdgeFilterMessage
{
#endif // !defined(MESSAGE_REFLECTIVEEDGEFILTERMESSAGE_REFLECTIVEEDGEFILTERMESSAGE_H) &&
//        !defined(CONTAINS_REFLECTIVEEDGEFILTERMESSAGE)
#if !defined(MESSAGE_REFLECTIVEEDGEFILTERMESSAGE_REFLECTIVEEDGEFILTERMESSAGE_H) || \
    defined(CONTAINS_REFLECTIVEEDGEFILTERMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    bool FilterIsOn; //!< Is the filter on?
#endif // !defined(MESSAGE_REFLECTIVEEDGEFILTERMESSAGE_REFLECTIVEEDGEFILTERMESSAGE_H) ||
//         defined(CONTAINS_REFLECTIVEEDGEFILTERMESSAGE)
#if !defined(MESSAGE_REFLECTIVEEDGEFILTERMESSAGE_REFLECTIVEEDGEFILTERMESSAGE_H) && \
    !defined(CONTAINS_REFLECTIVEEDGEFILTERMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for ReflectiveEdgeFilterMessage.
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
 * \return Pointer to ReflectiveEdgeFilterMessage.
 */
DLLINTERNAL ReflectiveEdgeFilterMessage * ReflectiveEdgeFilterMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_REFLECTIVEEDGEFILTERMESSAGE_REFLECTIVEEDGEFILTERMESSAGE_H
#endif // !defined(MESSAGE_REFLECTIVEEDGEFILTERMESSAGE_REFLECTIVEEDGEFILTERMESSAGE_H) &&
//        !defined(CONTAINS_REFLECTIVEEDGEFILTERMESSAGE)

