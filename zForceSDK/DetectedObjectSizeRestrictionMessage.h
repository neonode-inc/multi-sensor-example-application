/*! \file
 * \brief A DetectedObjectSizeRestrictionMessage contains Detected Object
 * Size Restrictions of a Device.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_H) && \
    !defined(CONTAINS_DETECTEDOBJECTSIZERESTRICTIONMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a detected object size restriction message.
 *
 * This structure represents a message which indicates if a device has
 * detected object size restriction on and for which maximum and minimum sizes.
 */
struct DetectedObjectSizeRestrictionMessage
{
#endif // !defined(.._DETECTEDOBJECTSIZERESTRICTIONMESSAGE_H) && !defined(CONTAINS_DETECTEDOBJECTSIZERESTRICTIONMESSAGE)
#if !defined(MESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_H) || \
    defined(CONTAINS_DETECTEDOBJECTSIZERESTRICTIONMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint32_t MinimumSize;    //!< Minimum size for device to detect.
    uint32_t MaximumSize;    //!< Maximum size for device to detect.
    bool     HasMinimumSize; //!< Is minimum size valid.
    bool     HasMaximumSize; //!< Is maximum size valid.
#endif // !defined(..__DETECTEDOBJECTSIZERESTRICTIONMESSAGE_H) || defined(CONTAINS_DETECTEDOBJECTSIZERESTRICTIONMESSAGE)
#if !defined(MESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_H) && \
    !defined(CONTAINS_DETECTEDOBJECTSIZERESTRICTIONMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*! Internal constructor for DetectedObjectSizeRestrictionMessage.
 * \brief Internal constructor for DetectedObjectSizeRestrictionMessage.
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
 * \return Pointer to DetectedObjectSizeRestrictionMessage.
 */
DLLINTERNAL DetectedObjectSizeRestrictionMessage * DetectedObjectSizeRestrictionMessage_New
                                                       (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_DETECTEDOBJECTSIZERESTRICTIONMESSAGE_H
#endif // !defined(.._DETECTEDOBJECTSIZERESTRICTIONMESSAGE_H) && !defined(CONTAINS_DETECTEDOBJECTSIZERESTRICTIONMESSAGE)

