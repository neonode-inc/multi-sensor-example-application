/*! \file
 * \brief Brief description of module's purpose.
 *
 * More detailed description of module's purpose
 * that can span more than one line.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(MESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_H) && \
    !defined(CONTAINS_MCUUNIQUEIDENTIFIERMESSAGE)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

 /*!
 * \brief This structure represents a mcu unique identifier message.
 *
 * This structure represents a message which contains the unique mcu identifier of a platform.
 */
struct McuUniqueIdentifierMessage
{
#endif // !defined(.._MCUUNIQUEIDENTIFIERMESSAGE_H) && defined(CONTAINS_MCUUNIQUEIDENTIFIERMESSAGE)
#if !defined(MESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_H) || \
    defined(CONTAINS_MCUUNIQUEIDENTIFIERMESSAGE)
    #define CONTAINS_MESSAGE
    #include <Message.h>
    #undef CONTAINS_MESSAGE
    uint8_t * McuUniqueIdentifier; //!< Mcu identifier.
    uint32_t  BufferSize;          //!< Size of mcu identifier.
#endif // !defined(.._MCUUNIQUEIDENTIFIERMESSAGE_H) || defined(CONTAINS_MCUUNIQUEIDENTIFIERMESSAGE)
#if !defined(MESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_H) && \
    !defined(CONTAINS_MCUUNIQUEIDENTIFIERMESSAGE)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
* \brief Internal constructor for McuUniqueIdentifier.
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
* \return Pointer to McuUniqueIdentifierMessage.
*/
DLLINTERNAL McuUniqueIdentifierMessage * McuUniqueIdentifierMessage_New (MessageGroup messageGroup, uint32_t size);

#ifdef __cplusplus
}
#endif // __cplusplus

#define MESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_MCUUNIQUEIDENTIFIERMESSAGE_H
#endif // !defined(.._MCUUNIQUEIDENTIFIERMESSAGE_H) && !defined(CONTAINS_MCUUNIQUEIDENTIFIERMESSAGE)

