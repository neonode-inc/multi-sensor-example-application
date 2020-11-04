/*! \file
 * \brief Transport module to connect to devices over Hid Pipe.
 *
 * Allows connections to devices using Hid Pipe.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(TRANSPORT_HIDPIPETRANSPORT_HIDPIPETRANSPORT_H) && !defined(CONTAINS_HIDPIPETRANSPORT)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \sa struct HidPipeTransport
 */
typedef struct HidPipeTransport HidPipeTransport;
/*!
 * \brief Struct containing the HidPipeTransport information.
 *
 * HidPipeTransport contains the Transport base, a pointer to the base
 * Transport class.
 *
 */
struct HidPipeTransport
{
#endif // !defined(TRANSPORT_HIDPIPETRANSPORT_HIDPIPETRANSPORT_H) && !defined(CONTAINS_HIDPIPETRANSPORT)
#if !defined(TRANSPORT_HIDPIPETRANSPORT_HIDPIPETRANSPORT_H) || defined(CONTAINS_HIDPIPETRANSPORT)
    #define CONTAINS_TRANSPORT
    #include <Transport.h>
    #undef CONTAINS_TRANSPORT
    void * Private;  //!< Private members of HidPipeTransport.
#endif // !defined(TRANSPORT_HIDPIPETRANSPORT_HIDPIPETRANSPORT_H) || defined(CONTAINS_HIDPIPETRANSPORT)
#if !defined(TRANSPORT_HIDPIPETRANSPORT_HIDPIPETRANSPORT_H) && !defined(CONTAINS_HIDPIPETRANSPORT)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
* \brief Internal call to add a HidPipeTransport to the list of
* available transports.
*
* This is the method used to add a HidPipeTransport which
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
* \return True if the HidPipeTransport has been added. Otherwise false which
*         indicates failure and the errno variable should be inspected for the
*         reason why.
*/
DLLINTERNAL bool HidPipeTransport_AddHidPipeTransportEntry (void);

#ifdef __cplusplus
}
#endif // __cplusplus

#define TRANSPORT_HIDPIPETRANSPORT_HIDPIPETRANSPORT_H
#endif // !defined(TRANSPORT_HIDPIPETRANSPORT_HIDPIPETRANSPORT_H) && !defined(CONTAINS_HIDPIPETRANSPORT)

