/*! \file
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017 Neonode Technologies AB. All rights reserved.
 *
 */
#ifndef ZFORCECOMMON_H
#define ZFORCECOMMON_H

// DLLEXTERNAL is for members visible outside the Shared Library.
// DLLINTERNAL is for members visible only inside the Shared Library.
// MODULEINTERNAL is for members visible only inside the module.

#ifdef _WIN32
    #ifdef COMPILING_ZFORCE_SDK
        #define DLLEXTERNAL __declspec(dllexport)
    #else
        #define DLLEXTERNAL __declspec(dllimport)
    #endif // COMPILING_ZFORCE_SDK
    #define DLLINTERNAL
    #define MODULEINTERNAL static
#elif defined (__clang__) || __GNUC__ > 4
    #define DLLEXTERNAL __attribute__ ((visibility ("default")))
    #define DLLINTERNAL __attribute__ ((visibility ("hidden")))
    #define MODULEINTERNAL static
#else
    #error Unsupported compiler.
#endif // _WIN32

// Violates Barr 4.2d "No header file shall contain a #include statement."
// We have a rule exclusion.
#include <zForceTypes.h>

// Macros used to expand OS defines into path/file that can be #included.
#define OSINCLUDE1(x) #x           //!< Macro used to expand OS defines.
#define OSINCLUDE(x) OSINCLUDE1(x) //!< Macro used to expand OS defines.

/*!
 * \defgroup GenericErrors 300 - 399 Generic Errors
 * 300 - 399 Generic Errors.
 * \{
 */
#define ENOTALLOWED                    300 //!< Not allowed.
#define EALREADYINITIALIZED            301 //!< Already initialized.
#define EVALUEOVERFLOW                 302 //!< Value overflow.
#define EFAILEDGETTINGTIME             303 //!< Failed getting current time.
#define EINTERRUPTED                   304 //!< Interrupted.
#define ENOTSUPPORTED                  305 //!< Operation not supported.
#define EINVALIDSIZE                   306 //!< Invalid size.
#define EINVALIDINPUT                  307 //!< Invalid input.
/*! \} */

/*!
 * \defgroup MemoryErrors 400 - 499 Memory Errors
 * 400 - 499 Memory Errors.
 * \{
 */
#define EOUTOFMEMORY                   400 //!< Out of memory.
#define EILLEGALMEMORYSIZE             401 //!< Illegal memory size.
/*! \} */

/*!
 * \defgroup MutexSemaphoreErrors 500 - 599 Mutex and Semaphore Errors
 * 500 - 599 Mutex and Semaphore Errors.
 * \{
 */
#define EMUTEXNOTINITIALIZED           500 //!< Mutex not initialized.
#define EMUTEXINITIALIZATIONFAILED     501 //!< Mutex Initialization failed.
#define EMUTEXLOCKFAILED               502 //!< Mutex Lock failed.
#define EMUTEXUNLOCKFAILED             503 //!< Mutex Unlock failed.
#define EMUTEXDESTROYFAILED            504 //!< Mutex Destroy failed.
#define EBADMUTEX                      505 //!< Bad Mutex Pointer.
#define ESEMAPHORENOTINITIALIZED       506 //!< Semaphore not initialized.
#define ESEMAPHOREINITIALIZATIONFAILED 507 //!< Semaphore Initialization failed.
#define ESEMAPHOREWAITFAILED           508 //!< Wait for Semaphore failed.
#define ESEMAPHOREINCREMENTFAILED      509 //!< Increment Semaphore failed.
#define ESEMAPHOREDESTROYFAILED        510 //!< Destroy Semaphore failed.
#define EBADSEMAPHORE                  511 //!< Bad Semaphore Pointer.
#define ESEMAPHOREWAITTIMEDOUT         512 //!< Semaphore Wait timed out.
/*! \} */

/*!
 * \defgroup ThreadErrors 600 - 699 Thread Errors
 * 600 - 699 Thread Errors.
 * \{
 */
#define ETHREADCREATEFAILED            600 //!< Thread creation failed.
#define EBADTHREAD                     601 //!< Bad Thread Pointer.
 /*! \} */

/*!
 * \defgroup QueueErrors 700 - 799 Queue Errors
 * 700 - 799 Queue Errors.
 * \{
 */
#define EQUEUECREATIONFAILED           700 //!< Queue Creation failed.
#define EENQUEUEFAILED                 701 //!< Enqueue failed.
#define EDEQUEUEFAILED                 702 //!< Dequeue failed.
#define EDEQUEUETIMEDOUT               703 //!< Dequeue Timeout.
#define EBADQUEUE                      704 //!< Bad Queue Pointer.
 /*! \} */

/*!
 * \defgroup zForceErrors 800 - 899 zForce Errors
 * 800 - 899 zForce Errors.
 * \{
 */
#define EZFORCENOTINITIALIZED          800 //!< zForce not Initialized.
#define EZFORCEINITIALIZATIONFAILED    801 //!< zForce Initialization failed.
 /*! \} */

/*!
 * \defgroup ConnectionErrors 900 - 999 Connection Errors
 * 900 - 999 Connection Errors.
 * \{
 */
#define EBADCONNECTION                 900 //!< Given connection not valid.
#define EDEVICENOTFOUND                901 //!< Device not found in list.
#define EMESSAGEFILTERALREADYSET       902 //!< Message filter already set.
#define EALREADYCONNECTED              903 //!< Already connected.
#define ENOTCONNECTED                  904 //!< Not connected.
#define ERECEIVETIMEOUT                905 //!< Timeout receiving response.
 /*! \} */

/*!
 * \defgroup DeviceErrors 1000 - 1099 Device Errors
 * 1000 - 1099 Device Errors.
 * \{
 */
#define EUNKNOWNDEVICETYPE             1000 //!< Unknown device type.
#define EALREADYINPROGRESS             1001 //!< Previous message in progress.
 /*! \} */

/*!
 * \defgroup TransportErrors 1100 - 1199 Transport Errors
 * 1100 - 1199 Transport Errors.
 * \{
 */
//! No such Transport with that name.
#define EUNKNOWNTRANSPORT              1100
#define EALREADYOPEN                   1101 //!< Transport already open.
#define ENOTOPENED                     1102 //!< Transport is not open.
#define EWRITEFAILED                   1103 //!< Write failed.
#define EPARAMETERSTRINGTOOLONG        1104 //!< Parameter string is too long.
//! Closing the file descriptor failed.
#define ECLOSEFAILED                   1105
#define EOPENFAILED                    1106 //!< Open failed.
#define ENOPORTENTRY                   1107 //!< No such file or directory.
#define EREADFAILED                    1108 //!< Read failed.
#define EPARTIALWRITE                  1109 //!< Not all bytes written.
#define ENODEVICEENTRY                 1110 //!< No device with that name.
 /*! \} */

/*!
 * \defgroup ProtocolErrors 1200 - 1299 Protocol Errors
 * 1200 - 1299 Protocol Errors.
 * \{
 */
//! No such Protocol with that name.
#define EUNKNOWNPROTOCOL               1200
//! Protocol/Transport already added.
#define EALREADYADDED                  1201
#define EBADNAME                       1202 //!< Incorrect name format.
#define EPROTOCOLERROR                 1203 //!< Generic protocol error.
 /*! \} */

/*!
 * \defgroup MessageErrors 1300 - 1399 Message Errors
 * 1300 - 1399 Message Errors.
 * \{
 */
#define EUNKNOWNMESSAGETYPE            1300 //!< Unknown Message Type.
#define EUNKNOWNMESSAGEGROUP           1301 //!< Unknown Message Group.
 /*! \} */

// Barr 4.2d violation and exclusion.
#include <zForceConfig.h>

#endif // ZFORCECOMMON_H

