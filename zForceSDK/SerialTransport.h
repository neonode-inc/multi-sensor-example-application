/*! \file
 * \brief Serial Transport class.
 *
 * This module implements the Serial Transport class. Here we find all that is
 * essential for a Serial Transport.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(TRANSPORT_SERIALTRANSPORT_SERIALTRANSPORT_H) && !defined(CONTAINS_SERIALTRANSPORT)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \sa struct SerialTransport
 */
typedef struct SerialTransport SerialTransport;
/*!
 * \brief Struct containing the SerialTransport information.
 *
 * SerialTransport contains the Transport base, a pointer to the base Transport
 * class.
 *
 */
struct SerialTransport
{
#endif // !defined(TRANSPORT_SERIALTRANSPORT_SERIALTRANSPORT_H) && !defined(CONTAINS_SERIALTRANSPORT)
#if !defined(TRANSPORT_SERIALTRANSPORT_SERIALTRANSPORT_H) || defined(CONTAINS_SERIALTRANSPORT)
    #define CONTAINS_TRANSPORT
    #include <Transport.h>
    #undef CONTAINS_TRANSPORT
    int FileDescriptor; //!< Instance-specific file descriptor.
#endif // !defined(TRANSPORT_SERIALTRANSPORT_SERIALTRANSPORT_H) || defined(CONTAINS_SERIALTRANSPORT)
#if !defined(TRANSPORT_SERIALTRANSPORT_SERIALTRANSPORT_H) && !defined(CONTAINS_SERIALTRANSPORT)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
* \brief Internal call to add a SerialTransport to the list of
* available transports.
*
* This is the method used to add a SerialTransport which
* can be used for communication.
* \n\n
* Upon error the errno variable is set as follows:
* - ::EALREADYADDED - A Transport matching the name and data frame type has
*                     already been added.
* - ::EOUTOFMEMORY - The memory used to store Transport details has been
*                    exhausted.
* - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
*                        critical section. This should not happen.
* - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
*                 mutex. This should not happen.
* - ::EPARAMETERSTRINGTOOLONG - The option parameter string is longer than the
*                               MaxOptionParameterLength.
*
* \return True if the SerialTransport has been added. Otherwise false which
*         indicates failure and the errno variable should be inspected for the
*         reason why.
*/
DLLINTERNAL bool SerialTransport_AddSerialTransportEntry (void);

#ifdef __cplusplus
}
#endif // __cplusplus

/*!
 * \brief Buffer size used when reading.
 */
#define RECEIVEBUFFERSIZE 128

#define TRANSPORT_SERIALTRANSPORT_SERIALTRANSPORT_H
#endif // !defined(TRANSPORT_SERIALTRANSPORT_SERIALTRANSPORT_H) && !defined(CONTAINS_SERIALTRANSPORT)

