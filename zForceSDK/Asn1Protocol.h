/*! \file
 * \brief Implementation of Neonode's ASN.1 based protocol.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2020 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(PROTOCOL_ASN1PROTOCOL_ASN1PROTOCOL_H) && !defined(CONTAINS_ASN1PROTOCOL)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

//! \sa Asn1InitializationStatus
typedef enum Asn1InitializationStatus Asn1InitializationStatus;
//! Enum describing if initialization messages has been sent and received.
enum Asn1InitializationStatus
{
    Asn1Uninitialized = 0, //!< Initialization sequence not completed.
    Asn1Initialized        //!< Initialization sequence completed.
};

//! \sa Asn1Protocol
typedef struct Asn1Protocol Asn1Protocol;
/*!
 * \brief This structure represents the ASN.1 protocol class.
 */
struct Asn1Protocol
{
#endif // !defined(PROTOCOL_ASN1PROTOCOL_ASN1PROTOCOL_H) && !defined(CONTAINS_ASN1PROTOCOL)
#if !defined(PROTOCOL_ASN1PROTOCOL_ASN1PROTOCOL_H) || defined(CONTAINS_ASN1PROTOCOL)
    #define CONTAINS_PROTOCOL
    #include <Protocol.h>
    #undef CONTAINS_PROTOCOL
    Asn1InitializationStatus InitializationStatus; //!< Initialization status.
    void                   * Private;              //!< Private members.
#endif // !defined(PROTOCOL_ASN1PROTOCOL_ASN1PROTOCOL_H) || defined(CONTAINS_ASN1PROTOCOL)
#if !defined(PROTOCOL_ASN1PROTOCOL_ASN1PROTOCOL_H) && !defined(CONTAINS_ASN1PROTOCOL)
};

// Exported Functions (prefixed with module name and underscore)

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Adds the ASN.1 Protocol to the ProtocolTable.
 *
 * Upon error the errno variable is set as follows:
 * - ::EALREADYADDED - The ASN.1 protocol has already been added.
 * - ::EOUTOFMEMORY - The memory used to store protocol details has been
 *                    exhausted.
 * - ::EMUTEXLOCKFAILED - We couldn't lock a mutex we need for an internal
 *                        critical section. This should not happen.
 * - ::EBADMUTEX - We tried to use a mutex internally but it wasn't a valid
 *                 mutex. This should not happen.
 * - ::EALREADYINITIALIZED - Protocol already initialized.
 *
 * \return True upon success, otherwise return false in which case see errno.
 */
DLLINTERNAL bool Asn1Protocol_Initialize (void);

#ifdef __cplusplus
}
#endif // __cplusplus

#define PROTOCOL_ASN1PROTOCOL_ASN1PROTOCOL_H
#endif // !defined(PROTOCOL_ASN1PROTOCOL_ASN1PROTOCOL_H) && !defined(CONTAINS_ASN1PROTOCOL)

