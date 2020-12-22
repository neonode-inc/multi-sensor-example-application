/*! \file
 * This project is aiming to provide a usable example to demonstrate how to use more than one Neonode touch sensor to create a larger area for contactless interaction.
 * This is not a finished product and should not be used as such.
 * \copyright
 * COPYRIGHT NOTICE: (c) 2020 Neonode Technologies AB. All rights reserved.
 *
 */

 // Header Files
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // _WIN32
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <zForceCommon.h>
#include <OsAbstractionLayer.h>
#include <zForce.h>
#include <Message.h>
#include <Device.h>
#include <Queue.h>
#include <Connection.h>
#include <fcntl.h>
#define __STDC_FORMAT_MACROS
#include <inttypes.h>
#include "Version.h"
#include "ErrorString.h"
#include "DumpMessage.h"
#include "Merger.h"

// Helper macros.
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))

#define HIDDEVICEVID "0x1536"     // Vendor ID of Device.
#define HIDDEVICEPID "0x0101"     // Product ID of Device.
#define QUEUE_TIMEOUT 1000

typedef struct Digitizer
{
    int                   SensorIndex;
    Connection          * Connection;
    PlatformDevice      * Platform;
    SensorDevice        * Sensor;
    zForceThread        * Thread;
    bool                  IsConnected;
    volatile bool         ShutDownNow;
    SensorConfiguration * SensorConfiguration;
    SensorGroupHandler  * SensorGroupHandler;
} Digitizer;

static void SignalHandler(int sig);
static void Destroy(void);
static void ShutDownNow(const char * error);
static void SensorThread(void * parameters);
static void SensorGroupThread(void * parameters);
static void SendToHostAsAbsoluteMouse(TouchInfo * info);

static void PrintTouchInfo(TouchInfo * info, int mode);
static void ProcessMessage(IndexedMessage * indexedMessage);
static void EnqueueMessage(Queue * queue, Message * message, SensorConfiguration * sensorConfiguration, uint64_t timestamp);
static void EnqueueIndexedMessage(Queue * queue, IndexedMessage * indexedMessage);

// Local (static) Variables
static zForce             * zForceInstance;
static bool                 zForceInitialized = false;
static Digitizer            digitizers[NUMBER_OF_SENSORS] = { 0 };
static Queue              * mainMessageQueue;
static SensorGroupHandler   groupHandler = { 0 };
static SensorConfiguration  persistentPositions[NUMBER_OF_SENSORS] = { 0 };
static int                  emulatedDevice = -1;
static bool                 sensorPositionsFileExists = false;

// Global error shutdown flag
bool volatile shutDownNow = false;

int main (void)
{
    printf("Version: %d.%d.%d \n", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION);

    const bool resultCode = zForce_Initialize(NULL);

    if (resultCode)
    {
        zForceInitialized = true;
    }
    else
    {
        ShutDownNow("Error: zForce initialization failed.\n");
    }

    // Install the Control-C handler.
    signal(SIGINT, SignalHandler);

    zForceInstance = zForce_GetInstance();

    sensorPositionsFileExists = ReadSensorPositionsFile(persistentPositions);

    mainMessageQueue = Queue_New();
    groupHandler.SensorGroupQueue = Queue_New();

    if (!zForceInstance->OsAbstractionLayer.CreateThread(&groupHandler.Thread, SensorGroupThread, &groupHandler))
    {
        ShutDownNow("Error: Unable to create thread. \n");
    }

    for (int sensorIndex = 0; sensorIndex < NUMBER_OF_SENSORS; sensorIndex++)
    {
        Digitizer * digitizer = &digitizers[sensorIndex];
        SensorConfiguration * config = (SensorConfiguration *)zForceInstance->OsAbstractionLayer.Malloc(sizeof(SensorConfiguration));
        digitizer->SensorConfiguration = config;
        digitizer->SensorIndex = sensorIndex;
        digitizer->SensorConfiguration->SensorPosition = sensorIndex;
        digitizer->SensorGroupHandler = &groupHandler;
        if (!zForceInstance->OsAbstractionLayer.CreateThread(&digitizer->Thread, SensorThread, digitizer))
        {
            ShutDownNow("Error: Unable to create thread. \n");
        }
    }

    // Initialize the emulated absolute mouse.
    emulatedDevice = open("/dev/hidg0", O_RDWR | O_NONBLOCK);
    if(emulatedDevice < 0)
    {
        ShutDownNow("Error: Unable to open hidg0 (absolute mouse). \n");
    }

    for (;;)
    {
        // If the global shutdown variable is set, close the application.
        if (shutDownNow)
        {
            ShutDownNow("Shutting down due to errors.\n");
        }
        // Picking up messages that are posted to the main queue by the sensor and group threads.
        IndexedMessage * indexedMessage = mainMessageQueue->Dequeue(mainMessageQueue, QUEUE_TIMEOUT);
        if (NULL != indexedMessage)
        {
            Message * message = indexedMessage->Message;
            DumpMessage(message);
            message->Destructor(message);
            zForceInstance->OsAbstractionLayer.Free(indexedMessage); // We need to free it as we haven't created an "object" we can call the destructor on.
        }
    }

    Destroy();
}

/*  Sets up a sensor and runs the message loop.  */
static void SensorThread(void *parameters)
{
    Digitizer * digitizer = (Digitizer *)parameters;
    const char * connectionStringBase = "hidpipe://vid="HIDDEVICEVID",pid="HIDDEVICEPID",index=%d";

    const size_t connectionStringMaxLength = strlen(connectionStringBase) + 3;
    char * connectionString = (char *)zForceInstance->OsAbstractionLayer.MallocWithPattern(connectionStringMaxLength, 0); // Allows up to 99 devices.

    snprintf(connectionString, connectionStringMaxLength - 1, connectionStringBase, digitizer->SensorConfiguration->SensorPosition);
    digitizer->Connection = Connection_New (
        connectionString, // Transport
        "asn1://",        // Protocol
        "Streaming");     // DataFrame type. Both Transport and Protocol must support the same.
    if (NULL == digitizer->Connection)
    {
        free(connectionString);
        printf("Sensor %d: Unable to create connection: (%d) %s.\n",
            digitizer->SensorIndex,
            zForceErrno,
            ErrorString(zForceErrno));
        shutDownNow = true;
        return;
    }
    free (connectionString);
    printf("Sensor %d: Connection created.\n", digitizer->SensorIndex);

    printf("Sensor %d: Connecting to Device.\n", digitizer->SensorIndex);
   
    const bool connectionAttemptResult = digitizer->Connection->Connect(digitizer->Connection);

    if (!connectionAttemptResult)
    {
        printf("Sensor %d: Unable to connect to device: (%d) %s\n",
            digitizer->SensorIndex,
            zForceErrno,
            ErrorString(zForceErrno));
        shutDownNow = true;
        return;
    }

    // Wait for Connection response to arrive within 1000 seconds.
    ConnectionMessage * connectionMessage =
        digitizer->Connection->ConnectionQueue->Dequeue(digitizer->Connection->ConnectionQueue, 1000000);

    if (NULL == connectionMessage)
    {
        printf("Sensor %d: No Connection Message Received.\n", digitizer->SensorIndex);
        printf("   Reason: %s\n", ErrorString(zForceErrno));
        shutDownNow = true;
        return;
    }

    printf("Sensor %d: Devices: %d\n", digitizer->SensorIndex, digitizer->Connection->NumberOfDevices);
    
    digitizer->Platform = (PlatformDevice *)digitizer->Connection->FindDevice(digitizer->Connection, Platform, 0);

    if (NULL == digitizer->Platform)
    {
        printf("Sensor %d: No Platform device found.\n", digitizer->SensorIndex);
        shutDownNow = true;
        return;
    }

    // Find the first Sensor type device (Core/Air/Plus).
    digitizer->Sensor = (SensorDevice*)digitizer->Connection->FindDevice(digitizer->Connection, Sensor, 0);
    
    if (NULL == digitizer->Sensor)
    {
        printf("Sensor %d: No Sensor device found.\n", digitizer->SensorIndex);
        shutDownNow = true;
        return;
    }

    if (!digitizer->Sensor->SetOperationModes(digitizer->Sensor,
        DetectionMode | SignalsMode | LedLevelsMode | DetectionHidMode | GesturesMode,
        DetectionMode))
    {
        printf("Sensor %d: SetOperationModes error (%d) %s.\n", digitizer->SensorIndex, zForceErrno, ErrorString(zForceErrno));
        shutDownNow = true;
        return;
    }

    bool operationModeMessageReceived = false;
    bool enableMessageReceived = false;
    bool touchActiveAreaMessageReceived = false;
    bool mcuUniqueIdentifierMessageReceived = false;
    bool numberOfTrackedObjectsMessageReceived = false;

    while (!digitizer->ShutDownNow)
    {
        // Check if sensor disconnected.
        if (!digitizer->Connection->IsConnected)
        {
            printf("Sensor %d: Connection error (%d) %s.\n", digitizer->SensorIndex, zForceErrno, ErrorString(zForceErrno));
            shutDownNow = true;
            return;
        }
        // This is where we run the dequeue-loop, and put the message into the other queue along with the index, unless it's one of those types, and we haven't already processed this message type.
        Message * message = digitizer->Connection->DeviceQueue->Dequeue(digitizer->Connection->DeviceQueue, QUEUE_TIMEOUT);
        if (NULL != message)
        {
            switch (message->MessageType)
            {
                case OperationModesMessageType:
                    if (!operationModeMessageReceived)
                    {
                        operationModeMessageReceived = true;

                        if (!digitizer->Platform->GetMcuUniqueIdentifier(digitizer->Platform))
                        {
                            printf("Sensor %d: GetMcuUniqueIdentifier error (%d) %s.\n", digitizer->SensorIndex, zForceErrno, ErrorString(zForceErrno));
                            shutDownNow = true;
                        }

                        message->Destructor (message);
                    }
                    else
                    {
                        // This message was received but we have already processed it. Probably the main loop or somewhere else that requested this. Send it to them for handling.
                        EnqueueMessage(mainMessageQueue, message, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                    }
                break;
                case McuUniqueIdentifierMessageType:
                    if (!mcuUniqueIdentifierMessageReceived)
                    {
                        mcuUniqueIdentifierMessageReceived = true;

                        McuUniqueIdentifierMessage * mcuUniqueIdentifierMessage = (McuUniqueIdentifierMessage *)message;

                        digitizer->SensorConfiguration->McuUniqueIdentifier = (char*)zForceInstance->OsAbstractionLayer.MallocWithPattern(mcuUniqueIdentifierMessage->BufferSize * 2 + 1, 0);
                        char * ptr = digitizer->SensorConfiguration->McuUniqueIdentifier;
                        for (uint32_t i = 0; i < mcuUniqueIdentifierMessage->BufferSize; i++)
                        {
                            ptr += sprintf(ptr, "%02X", mcuUniqueIdentifierMessage->McuUniqueIdentifier[i]); 
                        }

                        // Check if sensor positions file exists, if it does, use the position from the file.
                        if (sensorPositionsFileExists)
                        {
                            bool positionFound = false;
                            for (int i = 0; i < NUMBER_OF_SENSORS; i++)
                            {
                                if (strcmp(persistentPositions[i].McuUniqueIdentifier, digitizer->SensorConfiguration->McuUniqueIdentifier) == 0)
                                {
                                    digitizer->SensorConfiguration->SensorPosition = persistentPositions[i].SensorPosition;
                                    positionFound = true;
                                }
                            }
                            // If sensor position is missing for given MCUID, print error and create new file.
                            if (!positionFound)
                            {
                                printf("Error: Could not find sensor MCUID: %s in sensor_positions.csv file. \n", digitizer->SensorConfiguration->McuUniqueIdentifier);
                                sensorPositionsFileExists = false;
                            }
                        }

                        if (!digitizer->Sensor->GetTouchActiveArea(digitizer->Sensor))
                        {
                            printf("Sensor %d: GetTouchActiveArea error (%d) %s.\n", digitizer->SensorIndex, zForceErrno, ErrorString(zForceErrno));
                            shutDownNow = true;
                        }

                        message->Destructor(message);
                    }
                    else
                    {
                        // This message was received but we have already processed it. Probably the main loop or somewhere else that requested this. Send it to them for handling.
                        EnqueueMessage(mainMessageQueue, message, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                    }
                break;
                case TouchActiveAreaMessageType:
                    if (!touchActiveAreaMessageReceived)
                    {
                        touchActiveAreaMessageReceived = true;

                        TouchActiveAreaMessage * touchActiveAreaMessage = (TouchActiveAreaMessage *)message;

                        if (touchActiveAreaMessage->HasX)
                        {
                            digitizer->SensorConfiguration->TouchActiveAreaWidth = touchActiveAreaMessage->UpperBoundaryX - touchActiveAreaMessage->LowerBoundaryX;
                        }

                        if (touchActiveAreaMessage->HasY)
                        {
                            digitizer->SensorConfiguration->TouchActiveAreaHeight = touchActiveAreaMessage->UpperBoundaryY - touchActiveAreaMessage->LowerBoundaryY;
                        }

                        if (!digitizer->Sensor->SetNumberOfTrackedObjects(digitizer->Sensor, 1))
                        {
                            printf("Sensor %d: SetNumberOfTrackedObjects error (%d) %s.\n", digitizer->SensorIndex, zForceErrno, ErrorString(zForceErrno));
                            shutDownNow = true;
                        }

                        message->Destructor(message);
                    }
                    else
                    {
                        // This message was received but we have already processed it. Probably the main loop or somewhere else that requested this. Send it to them for handling.
                        EnqueueMessage(mainMessageQueue, message, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                    }
                break;
                case NumberOfTrackedObjectsMessageType:
                    if (!numberOfTrackedObjectsMessageReceived)
                    {
                        numberOfTrackedObjectsMessageReceived = true;

                        if (!digitizer->Sensor->SetEnable (digitizer->Sensor, true, 0))
                        {
                            printf("Sensor %d: SetEnable error (%d) %s.\n", digitizer->SensorIndex, zForceErrno, ErrorString(zForceErrno));
                            shutDownNow = true;
                        }

                        message->Destructor(message);
                    }
                    else
                    {
                        // This message was received but we have already processed it. Probably the main loop or somewhere else that requested this. Send it to them for handling.
                        EnqueueMessage(mainMessageQueue, message, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                    }
                break;
                case EnableMessageType:
                    if (!enableMessageReceived)
                    {
                        /* We are enabled and can now receive notifications */
                        enableMessageReceived = true;

                        // Send message to sensor group queue to signal that the sensor is ready.
                        EnqueueMessage(digitizer->SensorGroupHandler->SensorGroupQueue, message, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                    }
                    else
                    {
                        // This message was received but we have already processed it. Probably the main loop or somewhere else that requested this. Send it to them for handling.
                        EnqueueMessage(mainMessageQueue, message, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                    }
                break;
                case TouchMessageType:
                {
                    TouchMessage * touchMessage = (TouchMessage *)message;
                    EnqueueMessage(digitizer->SensorGroupHandler->SensorGroupQueue, (Message *)touchMessage, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                }
                break;
                default:
                    // All other messages are simply sent to the main loop queue.
                    EnqueueMessage(mainMessageQueue, message, digitizer->SensorConfiguration, zForceInstance->OsAbstractionLayer.GetTimeMilliSeconds());
                break;
            }
        }
    }
}

/*  Runs the message loop for a sensor group.  */
static void SensorGroupThread(void * parameters)
{
    SensorGroupHandler * sensorGroupHandler = (SensorGroupHandler *)parameters;
    IndexedMessage * indexedMessage = NULL;

    while (!sensorGroupHandler->ShutDownNow)
    {
        if(globalTriggerTimeout)
        {
            globalTriggerTimeout = false;
            indexedMessage = sensorGroupHandler->SensorGroupQueue->Dequeue (
                sensorGroupHandler->SensorGroupQueue, globalTimeoutInMs);
            if(indexedMessage == NULL)   // true when timeout
            {
                TimeoutCallback();
                TouchInfo * info = TouchBufPopLastWritten();
                if (verbose)
                {
                    PrintTouchInfo(info, 0);
                }
                SendToHostAsAbsoluteMouse(info);
            }
            else
            {
                ProcessMessage(indexedMessage);
            }
        }
        else
        {
            indexedMessage = sensorGroupHandler->SensorGroupQueue->Dequeue (sensorGroupHandler->SensorGroupQueue, QUEUE_TIMEOUT);
            if (NULL != indexedMessage)
            {
                // This is where the magic happens that de-duplicates touches from right/left, before sending them along to the Main Thread's queue.
                // You can either modify the IndexedMessage, or you can create a new one (don't forget to free the other one).
                // The IndexedMessage is mutable, as is the Message object.
                // IMPORTANT: ALWAYS use either your own malloc()/free() OR the OsAbstractionLayer-functions. This goes for everywhere.
                // The following two are identical:

                // Using the EnqueueIndexMessage() helper function.
                // EnqueueIndexedMessage(sensorGroupHandler->SensorGroupQueue, indexedMessage);
                // printf("SensorGroupThread: \t%s\n", GetSensorPositionName(indexedMessage->SensorConfiguration->SensorPosition));

                // Using EnqueueMessage() like we do everywhere else.
                // EnqueueMessage(sensorGroupHandler->SensorGroupQueue, indexedMessage->Message, indexedMessage->SensorConfiguration->SensorPosition, indexedMessage->SensorGroupHandler->SensorGroup, indexedMessage->Timestamp);
                // zForceInstance->OsAbstractionLayer.Free(indexedMessage);

                // IMPORTANT: Messages are fire-and-forget, so it's up to the receiver to destroy / free them.

                ProcessMessage(indexedMessage);
            }
        }
    }
}

/*  Creates a IndexedMessage struct and queues it from given parameters.  */
static void EnqueueMessage(Queue * queue, Message * message, SensorConfiguration * sensorConfiguration, uint64_t timestamp)
{
    IndexedMessage * indexedMessage = zForceInstance->OsAbstractionLayer.Malloc(sizeof(IndexedMessage));
    indexedMessage->SensorConfiguration = sensorConfiguration;
    indexedMessage->SensorGroupHandler = &groupHandler;
    indexedMessage->Timestamp = timestamp;
    indexedMessage->Message = message;
    EnqueueIndexedMessage(queue, indexedMessage);
}

/*  Queues a IndexedMessage struct.  */
static void EnqueueIndexedMessage(Queue * queue, IndexedMessage * indexedMessage)
{
    if (!queue->Enqueue (queue, indexedMessage))
    {
        printf("Error: Failed queueing message.\n");
        shutDownNow = true;
    }
}

/*  Makes sure configurations are done, getting the touches ready for sending to host and deallocates the messages.  */
static void ProcessMessage(IndexedMessage * indexedMessage)
{
    Message * message = indexedMessage->Message;

    // Enable message is the last message after setting up each sensor. Check configuration and enable touch handling when all configurations are done.
    if (message->MessageType == EnableMessageType)
    {
        printf("Configuration for sensor position %s is: \n", GetSensorPositionName(indexedMessage->SensorConfiguration->SensorPosition));
        printf("Width: %d \n", indexedMessage->SensorConfiguration->TouchActiveAreaWidth);
        printf("Height: %d \n", indexedMessage->SensorConfiguration->TouchActiveAreaHeight);
        printf("MCUID: %s \n", indexedMessage->SensorConfiguration->McuUniqueIdentifier);

        if (!AddSensorConfiguration(*(indexedMessage->SensorConfiguration)))
        {
            shutDownNow = true;
            return;
        }

        // Create or overwrite sensor positions file if it does not exist or missing information.
        if (allSensorConfigurationsReceived && !sensorPositionsFileExists)
        {
            SensorConfiguration writeConfigs[NUMBER_OF_SENSORS] = { 0 };
            for (int i = 0; i < NUMBER_OF_SENSORS; i++)
            {
                writeConfigs[i] = *(digitizers[i].SensorConfiguration);
            }
            
            if (!WriteSensorPositionsFile(writeConfigs))
            {
                shutDownNow = true;
                return;
            }
        }
    }
    else if (message->MessageType == TouchMessageType && allSensorConfigurationsReceived)
    {
        IndexedMessage * pending = MergeTouch(indexedMessage);

        if(NULL != pending)
        {
            TouchMessage * touchMessage = (TouchMessage *)(indexedMessage->Message);
            TouchInfo info = {0};
            ApplicationTouchEvent appEvent = ConvertTouchEvent(touchMessage->Event);
            CopyTouchInfo(&info, 
                            touchMessage->X, touchMessage->Y, 
                            appEvent, indexedMessage->Timestamp, 
                            indexedMessage->SensorConfiguration);
            if (verbose)
            {
                PrintTouchInfo(&info, 0);
            }
            SendToHostAsAbsoluteMouse(&info);
        }
    }

    message->Destructor (message);
    zForceInstance->OsAbstractionLayer.Free (indexedMessage);
}

/*  Prints out various information for given touch depending on mode.  */
static void PrintTouchInfo(TouchInfo * info, int mode)
{
    char * eventString = GetTouchStateName(info->Event);
    uint32_t t = GetMillisecond(info->Timestamp);

    if(mode == 0)
    {
        printf("%d.%s%d \t",t/1000, (t%1000)<100?(t%1000)<10?"00":"0":"", t%1000);

        printf ("%8d\t %8d\t %7s\n", info->X, info->Y, eventString);
    }
    else if(mode == 1)
    {
        if(info->Event == App_DownEvent)
        {
            printf("%d.%s%d \t",t/1000, (t%1000)<100?(t%1000)<10?"00":"0":"", t%1000);
            printf ("___/");
            fflush(stdout);
        }
        else if(info->Event == App_MoveEvent)
        {
            printf ("-");
            fflush(stdout);
        }
        else if(info->Event == App_UpEvent)
        {
            printf ("\\___\n\n");
        }
        else
        {}
    }
}

/*  Converts the touch coordinates to absolute mouse coordinates and sends them to the host.  */
static void SendToHostAsAbsoluteMouse(TouchInfo * info)
{
    if(emulatedDevice < 0)
    {
        emulatedDevice = open("/dev/hidg0", O_RDWR | O_NONBLOCK);
        if(emulatedDevice < 0)
        {
            printf("Error: Unable to open hidg0 (absolute mouse). \n");
            shutDownNow = true;
            return;
        }
    }

    uint8_t data[5] = {0};
    switch(info->Event)
    {
        case App_DownEvent: data[0] = 1; break;     // button press
        case App_MoveEvent: data[0] = 1; break;     // button press
        default: data[0] = 0;                   // button release
    }

    double normX = 1.0 * info->X / hostScreenWidth;
    double normY = 1.0 * info->Y / hostScreenHeight;

    uint16_t x = INT16_MAX * MIN(normX, 1.0);
    uint16_t y = INT16_MAX * MIN(normY, 1.0);
    
    data[1] = x & 0xFF;
    data[2] = x >> 8;
    data[3] = y & 0xFF;
    data[4] = y >> 8;
    ssize_t written = write(emulatedDevice, data, 5);

    if(written < 0)
    {
        perror("Error: Writing to hidg0 (absolute mouse)");
    }
}

/*  We will let the user quit the program by pressing Control-C. In such an event SignalHandler will be called.  */
static void SignalHandler (int sig)
{
    (void)sig;
    ShutDownNow("User input shutdown signal. \n");
}

/*  Close the threads gracefully and free resources.  */
static void Destroy(void)
{
    // Signal Sensor threads to exit.
    for (int sensorIndex = 0; sensorIndex < NUMBER_OF_SENSORS; sensorIndex++)
    {
        Digitizer * digitizer = &digitizers[sensorIndex];
        if (digitizer->Thread != NULL)
        {
            digitizer->ShutDownNow = true;
        }
    }

    // Wait for them to exit and free their resources.
    for (int sensorIndex = 0; sensorIndex < NUMBER_OF_SENSORS; sensorIndex++)
    {
        Digitizer * digitizer = &digitizers[sensorIndex];
        if (digitizer->Thread != NULL)
        {
            zForceInstance->OsAbstractionLayer.WaitForThreadExit(digitizer->Thread);
            digitizer->Thread = NULL;
        }
        if (digitizer->SensorConfiguration != NULL)
        {
            if (digitizer->SensorConfiguration->McuUniqueIdentifier != NULL)
            {
                zForceInstance->OsAbstractionLayer.Free(digitizer->SensorConfiguration->McuUniqueIdentifier);
            }
            zForceInstance->OsAbstractionLayer.Free(digitizer->SensorConfiguration);
        }
        if (persistentPositions[sensorIndex].McuUniqueIdentifier != NULL)
        {
            zForceInstance->OsAbstractionLayer.Free(persistentPositions[sensorIndex].McuUniqueIdentifier);
        }
    }

    // Signal Sensor Group thread to exit.
    if (groupHandler.Thread != NULL)
    {
        groupHandler.ShutDownNow = true;
    }

    // Wait for it to exit, and destroy the queue.
    if (groupHandler.Thread != NULL)
    {
        zForceInstance->OsAbstractionLayer.WaitForThreadExit(groupHandler.Thread);
        groupHandler.Thread = NULL;
        groupHandler.SensorGroupQueue->Destructor(groupHandler.SensorGroupQueue);
    }

    // Destroy the main message queue.
    mainMessageQueue->Destructor(mainMessageQueue);

    if (zForceInitialized)
    {
        zForce_Uninitialize();
        zForceInitialized = false;
    }
}

/*  Prints out given error and closes down the application.  */
static void ShutDownNow(const char * error)
{
    printf("%s", error);
    Destroy();
    printf("\nClosing the application... \n");
    exit(-1);
}