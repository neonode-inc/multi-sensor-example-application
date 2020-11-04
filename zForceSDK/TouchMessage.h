/*! \file
 * \brief An TouchMessage contains the Data of a Touch.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_TOUCHMESSAGE_TOUCHMESSAGE_H) && !defined(CONTAINS_TOUCHMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \brief This structure represents a touch message.
 *
 * This structure represents a message containing touch information.
 */
struct TouchMessage
{
#endif // !defined(MESSAGE_TOUCHMESSAGE_TOUCHMESSAGE_H) && !defined(CONTAINS_TOUCHMESSAGE)
#if !defined(MESSAGE_TOUCHMESSAGE_TOUCHMESSAGE_H) || defined(CONTAINS_TOUCHMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint32_t         Id;             //!< Id of the Touch.
    TouchEvent       Event;          //!< Event of the Touch.
    #define CONTAINS_CARTESIANCOORDINATES
    #include <zForceTypes.h>
    #undef CONTAINS_CARTESIANCOORDINATES
    uint32_t         SizeX;          //!< Size of the object on the X axis.
    bool             HasSizeX;       //!< Is the size reported for X?
    uint32_t         SizeY;          //!< Size of the object on the Y axis.
    bool             HasSizeY;       //!< Is the size reported for Y?
    uint32_t         SizeZ;          //!< Size of the object on the Z axis.
    bool             HasSizeZ;       //!< Is the size reported for Z?
    TouchOrientation Orientation;    //!< Orientation of the object.
    bool             HasOrientation; //!< Is Orientation reported?
    uint32_t         Confidence;     //!< Detection confidence.
    bool             HasConfidence;  //!< Is Confidence reported?
    uint32_t         Pressure;       //!< Pressure of the object.
    bool             HasPressure;    //!< Is Pressure reported?
    uint64_t         Timestamp;      //!< Message timestamp.
    bool             HasTimestamp;   //!< Is Timestamp reported?
#endif // !defined(MESSAGE_TOUCHMESSAGE_TOUCHMESSAGE_H) || defined(CONTAINS_TOUCHMESSAGE)
#if !defined(MESSAGE_TOUCHMESSAGE_TOUCHMESSAGE_H) && !defined(CONTAINS_TOUCHMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Internal constructor for TouchMessage.
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
 * \return Pointer to TouchMessage.
 */
DLLINTERNAL TouchMessage * TouchMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_TOUCHMESSAGE_TOUCHMESSAGE_H
#endif //!defined(MESSAGE_TOUCHMESSAGE_TOUCHMESSAGE_H) && !defined(CONTAINS_TOUCHMESSAGE)

