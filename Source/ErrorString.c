/*! \file
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 * \sa file://ErrorString.h
 */

// Header Files
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <stdint.h>
#include <stdbool.h>
#include <zForceCommon.h>
#include "ErrorString.h"

// Exported Functions

/*!
 * \sa ErrorString.h
 */

char * ErrorString (int errorCode)
{
    char * str;

    switch (errorCode)
    {
        case ENOTALLOWED:
            str = "Not allowed.";
        break;

        case EALREADYINITIALIZED:
            str = "Already initialized.";
        break;

        case EVALUEOVERFLOW:
            str = "Value overflow.";
        break;

        case EFAILEDGETTINGTIME:
            str = "Failed getting current time.";
        break;

        case EINTERRUPTED:
            str = "Interrupted.";
        break;

        case ENOTSUPPORTED:
            str = "Operation not supported.";
        break;

        case EINVALIDSIZE:
            str = "Invalid size.";
        break;

        case EINVALIDINPUT:
            str = "Invalid input.";
        break;

        case EOUTOFMEMORY:
            str = "Out of memory.";
        break;

        case EMUTEXNOTINITIALIZED:
            str = "Mutex not initialized.";
        break;

        case EMUTEXINITIALIZATIONFAILED:
            str = "Mutex Initialization failed.";
        break;

        case EMUTEXLOCKFAILED:
            str = "Mutex Lock failed.";
        break;

        case EMUTEXUNLOCKFAILED:
            str = "Mutex Unlock failed.";
        break;

        case EMUTEXDESTROYFAILED:
            str = "Mutex Destroy failed.";
        break;

        case EBADMUTEX:
            str = "Bad Mutex Pointer.";
        break;

        case ESEMAPHORENOTINITIALIZED:
            str = "Semaphore not initialized.";
        break;

        case ESEMAPHOREINITIALIZATIONFAILED:
            str = "Semaphore Initialization failed.";
        break;

        case ESEMAPHOREWAITFAILED:
            str = "Wait for Semaphore failed.";
        break;

        case ESEMAPHOREINCREMENTFAILED:
            str = "Increment Semaphore failed.";
        break;

        case ESEMAPHOREDESTROYFAILED:
            str = "Destroy Semaphore failed.";
        break;

        case EBADSEMAPHORE:
            str = "Bad Semaphore Pointer.";
        break;

        case ESEMAPHOREWAITTIMEDOUT:
            str = "Semaphore Wait timed out.";
        break;

        case ETHREADCREATEFAILED:
            str = "Thread creation failed.";
        break;

        case EBADTHREAD:
            str = "Bad Thread Pointer.";
        break;

        case EQUEUECREATIONFAILED:
            str = "Queue Creation failed.";
        break;

        case EENQUEUEFAILED:
            str = "Enqueue failed.";
        break;

        case EDEQUEUEFAILED:
            str = "Dequeue failed.";
        break;

        case EDEQUEUETIMEDOUT:
            str = "Dequeue Timeout.";
        break;

        case EBADQUEUE:
            str = "Bad Queue Pointer.";
        break;

        case EZFORCENOTINITIALIZED:
            str = "zForce not Initialized.";
        break;

        case EZFORCEINITIALIZATIONFAILED:
            str = "zForce Initialization failed.";
        break;

        case EBADCONNECTION:
            str = "Given connection not valid.";
        break;

        case EDEVICENOTFOUND:
            str = "Device not found in list.";
        break;

        case EMESSAGEFILTERALREADYSET:
            str = "Message filter already set.";
        break;

        case EALREADYCONNECTED:
            str = "Already connected.";
        break;

        case ENOTCONNECTED:
            str = "Not connected.";
        break;

        case ERECEIVETIMEOUT:
            str = "Timeout receiving response.";
        break;

        case EUNKNOWNDEVICETYPE:
            str = "Unknown device type.";
        break;

        case EALREADYINPROGRESS:
            str = "Previous message in progress.";
        break;

        case EUNKNOWNTRANSPORT:
            str = "No such Transport with that name.";
        break;

        case EALREADYOPEN:
            str = "Transport already open.";
        break;

        case ENOTOPENED:
            str = "Transport is not open.";
        break;

        case EWRITEFAILED:
            str = "Write failed.";
        break;

        case EPARAMETERSTRINGTOOLONG:
            str = "Parameter string is too long.";
        break;

        case ECLOSEFAILED:
            str = "Closing the file descriptor failed.";
        break;

        case EOPENFAILED:
            str = "Could not open file.";
        break;

        case ENOPORTENTRY:
            str = "No such file or directory.";
        break;

        case EREADFAILED:
            str = "Read failed.";
        break;

        case EPARTIALWRITE:
            str = "Not all bytes written.";
        break;

        case EUNKNOWNPROTOCOL:
            str = "No such Protocol with that name.";
        break;

        case EALREADYADDED:
            str = "Protocol/Transport already added.";
        break;

        case EBADNAME:
            str = "Incorrect name format.";
        break;

        case EPROTOCOLERROR:
            str = "Generic protocol error.";
        break;

        case EUNKNOWNMESSAGETYPE:
            str = "Unknown Message Type.";
        break;

        case EUNKNOWNMESSAGEGROUP:
            str = "Unknown Message Group.";
        break;

        default:
            str = "Unknown error code";
        break;
    }

    return str;
}
