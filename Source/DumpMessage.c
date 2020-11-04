/*! \file
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 * \sa file://DumpMessage.h
 */

// Header Files
#ifdef _WIN32
#include <windows.h>
#endif // _WIN32
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inttypes.h>
#include <zForceCommon.h>
#include <Message.h>
#include "ErrorString.h"
#include "DumpMessage.h"

static void DumpEnableMessage (Message * message);
static void DumpDisableMessage (Message * message);
static void DumpOperationModesMessage (Message * message);
static void DumpResolutionMessage (Message * message);
static void DumpTouchActiveArea (Message * message);
static void DumpReverseTouchActiveArea (Message * message);
static void DumpMcuUniqueIdentifier (Message * message);
// static void DumpTouchMessage (Message * message);
static void DumpNumberOfTrackedObjectsMessage (Message * message);
static void DumpFingerFrequencyMessage (Message * message);
static void DumpIdleFrequencyMessage (Message * message);
static void DumpDetectedObjectSizeRestrictionMessage (Message * message);
static void DumpOffsetMessage (Message * message);
static void DumpHidDisplaySizeMessage (Message * message);
static void DumpFlipXYMessage (Message * message);
static void DumpReflectiveEdgeFilterMessage (Message * message);
static void DumpMergeTouchesMessage (Message * message);
static void DumpMessageError (Message * message);

// Exported Functions

/*!
 * \sa DumpMessage.h
 */
void DumpMessage (Message * message)
{
    // printf ("Message Serial Number = %" PRIu64 "\n", message->SerialNumber);

    switch (message->MessageType)
    {
        case EnableMessageType:
            DumpEnableMessage (message);
        break;

        case DisableMessageType:
            DumpDisableMessage (message);
        break;

        case OperationModesMessageType:
            DumpOperationModesMessage (message);
        break;

        case ResolutionMessageType:
            DumpResolutionMessage (message);
        break;

        case ReverseTouchActiveAreaMessageType:
            DumpReverseTouchActiveArea (message);
        break;

        case TouchActiveAreaMessageType:
            DumpTouchActiveArea (message);
        break;

        case TouchMessageType:
            DumpTouchMessage (message);
        break;

        case McuUniqueIdentifierMessageType:
            DumpMcuUniqueIdentifier(message);
         break;

        case NumberOfTrackedObjectsMessageType:
            DumpNumberOfTrackedObjectsMessage (message);
        break;

        case FingerFrequencyMessageType:
            DumpFingerFrequencyMessage (message);
        break;

        case IdleFrequencyMessageType:
            DumpIdleFrequencyMessage (message);
        break;

        case DetectedObjectSizeRestrictionMessageType:
            DumpDetectedObjectSizeRestrictionMessage (message);
        break;

        case OffsetMessageType:
            DumpOffsetMessage (message);
        break;

        case HidDisplaySizeMessageType:
            DumpHidDisplaySizeMessage (message);
        break;

        case FlipXYMessageType:
            DumpFlipXYMessage (message);
        break;

        case ReflectiveEdgeFilterMessageType:
			DumpReflectiveEdgeFilterMessage(message);
        break;

		case MergeTouchesMessageType:
			DumpMergeTouchesMessage(message);
        break;

        default:
            printf ("Unknown Message received!\n");
        break;
    }

}

// Local (static) Functions.
static void DumpEnableMessage (Message * message)
{
    EnableMessage * enableMessage = (EnableMessage *)message;

    printf ("Enable Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        printf ("  Enabled: %s.\n", enableMessage->Enabled ? "Yes" : "No");
        printf ("  Continuous: %s.\n", enableMessage->ContinuousMode ? "Yes" : "No");
        printf ("  NumberOfMessages: %d.\n", enableMessage->NumberOfMessages);
    }

}

static void DumpMcuUniqueIdentifier(Message * message)
{
    McuUniqueIdentifierMessage * mcuUniqueIdentifierMessage = (McuUniqueIdentifierMessage *)message;

    printf ("Mcu Unique Identifier Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        printf("Mcu Unique Identifier is: ");
        for (uint32_t i = 0; i < mcuUniqueIdentifierMessage->BufferSize; i++)
        {
            printf("%02X", mcuUniqueIdentifierMessage->McuUniqueIdentifier[i]);
        }
        printf("\n");
    }
}

static void DumpDisableMessage (Message * message)
{
    DisableMessage * disableMessage = (DisableMessage *)message;

    printf ("Disable Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        printf ("  Disabled: %s.\n", disableMessage->Disabled ? "Yes" : "No");
    }

}

static void DumpOperationModesMessage (Message * message)
{
    OperationModesMessage * operationModesMessage =
        (OperationModesMessage *) message;
    OperationModes          mask;
    OperationModes          values;

    printf ("Operation Modes Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        mask = operationModesMessage->Mask;
        values = operationModesMessage->Values;

        printf ("Modes reported:\n");

        if (NoOperationMode == mask)
        {
            printf ("   No mode set.\n");
        }

        if (DetectionMode & mask)
        {
            printf ("   Detection mode %s.\n",
                    (DetectionMode & values) ? "on" : "off");
        }

        if (SignalsMode & mask)
        {
            printf ("   Signals mode %s.\n",
                    (SignalsMode & values) ? "on" : "off");
        }

        if (LedLevelsMode & mask)
        {
            printf ("   LED levels mode %s.\n",
                    (LedLevelsMode & values) ? "on" : "off");
        }

        if (DetectionHidMode & mask)
        {
            printf ("   Detection HID mode %s.\n",
                    (DetectionHidMode & values) ? "on" : "off");
        }

        if (GesturesMode & mask)
        {
            printf ("   Gestures mode %s.\n",
                    (GesturesMode & values) ? "on" : "off");
        }

        printf ("End of report.\n");
    }

}

static void DumpResolutionMessage (Message * message)
{
    ResolutionMessage * resolutionMessage = (ResolutionMessage *)message;
    printf ("Resolution Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }

    if (resolutionMessage->HasX || resolutionMessage->HasY ||
        resolutionMessage->HasZ)
    {
        if (resolutionMessage->HasX)
        {
            printf ("  X: %8d", resolutionMessage->X);
        }

        if (resolutionMessage->HasX && resolutionMessage->HasY)
        {
            printf (", ");
        }

        if (resolutionMessage->HasY)
        {
            printf ("Y: %8d", resolutionMessage->Y);
        }

        if (resolutionMessage->HasZ &&
            (resolutionMessage->HasX || resolutionMessage->HasY))
        {
            printf (", ");
        }

        if (resolutionMessage->HasZ)
        {
            printf ("Z: %8d", resolutionMessage->Z);
        }

    }

    printf (".\n");
}

static void DumpReflectiveEdgeFilterMessage(Message * message)
{
	ReflectiveEdgeFilterMessage * reflectiveEdgeFilterMessage = (ReflectiveEdgeFilterMessage *)message;
	printf("ReflectiveEdgeFilter Message received.\n");

	if (message->Error)
	{
		DumpMessageError(message);
	}

	if (NULL != reflectiveEdgeFilterMessage)
	{
        printf("The reflective edge filter is %s.\n", reflectiveEdgeFilterMessage->FilterIsOn ? "on" : "off");
	}

}

static void DumpMergeTouchesMessage(Message * message)
{
	MergeTouchesMessage * mergeTouchesMessage = (MergeTouchesMessage *)message;
	printf("MergeTouches Message received.\n");

	if (message->Error)
	{
		DumpMessageError(message);
	}

	if (NULL != mergeTouchesMessage)
	{
        printf("The touches are %s.\n", mergeTouchesMessage->AreTouchesMerged ? "merged" : "not merged");
	}

}

static void DumpReverseTouchActiveArea (Message * message)
{
    ReverseTouchActiveAreaMessage * reverseTouchActiveAreaMessage;

    printf ("Reverse Touch Active Area Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        reverseTouchActiveAreaMessage = (ReverseTouchActiveAreaMessage *) message;

        printf ("  X reversed is %s\n",
        reverseTouchActiveAreaMessage->XIsReversed ? "true" : "false");

        printf ("  Y reversed is %s\n",
        reverseTouchActiveAreaMessage->YIsReversed ? "true" : "false");
    }
}

static void DumpFlipXYMessage (Message * message)
{
    FlipXYMessage * flipXYMessage;

    printf ("Flip XY Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        flipXYMessage = (FlipXYMessage *) message;

        printf ("  FlipXY is %s\n",
        flipXYMessage->AxesAreFlipped ? "true" : "false");
    }
    
}

static void DumpTouchActiveArea (Message * message)
{
    TouchActiveAreaMessage * touchActiveAreaMessage;

    printf ("Touch Active Area Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        touchActiveAreaMessage = (TouchActiveAreaMessage *) message;

        if (touchActiveAreaMessage->HasX)
        {
            printf ("   X lower boundary = %u",
                   touchActiveAreaMessage->LowerBoundaryX);
            printf ("   X upper boundary = %u\n",
                   touchActiveAreaMessage->UpperBoundaryX);
        }

        if (touchActiveAreaMessage->HasY)
        {
            printf ("   Y lower boundary = %u",
                   touchActiveAreaMessage->LowerBoundaryY);
            printf ("   Y upper boundary = %u\n",
                   touchActiveAreaMessage->UpperBoundaryY);
        }

    }

}

void DumpTouchMessage (Message * message)
{
    TouchMessage * touchMessage = (TouchMessage *)message;
    char         * eventString = NULL;

    if (message->Error)
    {
        DumpMessageError (message);
    }

    switch (touchMessage->Event)
    {
        case DownEvent:
            eventString = "Down";
        break;

        case MoveEvent:
            eventString = "Move";
        break;

        case UpEvent:
            eventString = "Up";
        break;

        case InvalidEvent:
            eventString = "Invalid";
        break;

        case GhostEvent:
            eventString = "Ghost";
        break;

        default:
            eventString = "Unknown";
        break;
    }

    printf ("Id: %2d, Event: %7s", touchMessage->Id,
            eventString);

    if (touchMessage->HasX || touchMessage->HasY ||
        touchMessage->HasZ)
    {
        printf (", ");

        if (touchMessage->HasX)
        {
            printf ("X: %8d", touchMessage->X);
        }

        if (touchMessage->HasX && touchMessage->HasY)
        {
            printf (", ");
        }

        if (touchMessage->HasY)
        {
            printf ("Y: %8d", touchMessage->Y);
        }

        if (touchMessage->HasZ &&
            (touchMessage->HasX || touchMessage->HasY))
        {
            printf (", ");
        }

        if (touchMessage->HasZ)
        {
            printf ("Z: %8d", touchMessage->Z);
        }
    }

    if (touchMessage->HasSizeX || touchMessage->HasSizeY ||
        touchMessage->HasSizeZ)
    {
        printf (", ");
        if (touchMessage->HasSizeX)
        {
            printf ("X Size: %8d", touchMessage->SizeX);
        }

        if (touchMessage->HasSizeX && touchMessage->HasSizeY)
        {
            printf (", ");
        }

        if (touchMessage->HasSizeY)
        {
            printf ("Y Size: %8d", touchMessage->SizeY);
        }

        if (touchMessage->HasSizeZ &&
            (touchMessage->HasSizeX || touchMessage->HasSizeY))
        {
            printf (", ");
        }

        if (touchMessage->HasSizeZ)
        {
            printf ("Z Size: %8d", touchMessage->SizeZ);
        }

    }

    printf (".\n");
}

static void DumpNumberOfTrackedObjectsMessage (Message * message)
{
    NumberOfTrackedObjectsMessage * numberOfTrackedObjectsMessage
        = (NumberOfTrackedObjectsMessage *)message;

    printf ("Number Of Tracked Objects Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        printf ("  Number: %u.\n",
                numberOfTrackedObjectsMessage->NumberOfTrackedObjects);
    }

}

static void DumpFingerFrequencyMessage (Message * message)
{
    FingerFrequencyMessage * fingerFrequencyMessage =
        (FingerFrequencyMessage *)message;

    printf ("Finger Frequency Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        printf ("  Frequency: %d.\n", fingerFrequencyMessage->Frequency);
    }

}

static void DumpIdleFrequencyMessage (Message * message)
{
    IdleFrequencyMessage * idleFrequencyMessage =
        (IdleFrequencyMessage *)message;

    printf ("Idle Frequency Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        printf ("  Frequency: %d.\n", idleFrequencyMessage->Frequency);
    }

}

static void DumpDetectedObjectSizeRestrictionMessage (Message * message)
{
    DetectedObjectSizeRestrictionMessage * sizeMessage =
        (DetectedObjectSizeRestrictionMessage *) message;

    printf ("Detected Object Size Restriction Message Received \n");

    printf ("MinimumSize Enabled : %s \n",
            (sizeMessage->HasMinimumSize == true) ? "True" : "False");

    if (sizeMessage->HasMinimumSize)
    {
        printf ("MinimumSize : %u \n", sizeMessage->MinimumSize);
    }

    printf ("MaximumSize Enabled : %s \n",
            (sizeMessage->HasMaximumSize == true) ? "True" : "False");

    if (sizeMessage->HasMaximumSize)
    {
        printf ("MaximumSize : %u \n", sizeMessage->MaximumSize);
    }

}

static void DumpOffsetMessage (Message * message)
{
    OffsetMessage * offsetMessage = (OffsetMessage *)message;

    printf ("Offset Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {
        if (true == offsetMessage->HasOffsetX)
        {
            printf ("  OffsetX: %d.\n", offsetMessage->OffsetX);
        }

        if (true == offsetMessage->HasOffsetY)
        {
            printf ("  OffsetY: %d.\n", offsetMessage->OffsetY);
        }
    }

}

static void DumpHidDisplaySizeMessage (Message * message)
{
    HidDisplaySizeMessage * hidDisplaySizeMessage = (HidDisplaySizeMessage *)message;

    printf ("HidDisplaySize Message received.\n");

    if (message->Error)
    {
        DumpMessageError (message);
    }
    else
    {

        if (true == hidDisplaySizeMessage->HasSizeX)
        {
            printf ("  SizeX: %d.\n", hidDisplaySizeMessage->SizeX);
        }

        if (true == hidDisplaySizeMessage->HasSizeY)
        {
            printf ("  SizeY: %d.\n", hidDisplaySizeMessage->SizeY);
        }

    }

}

static void DumpMessageError (Message * message)
{
    printf ("**  Error: (%d) %s\n",
            message->ErrorCode,
            ErrorString (message->ErrorCode));
}
