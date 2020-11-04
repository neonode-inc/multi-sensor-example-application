#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <zForceCommon.h>
#include <OsAbstractionLayer.h>
#include <Queue.h>

#define NUMBER_OF_SENSORS 2                     // Number of sensors connected to the raspberry pi. Example code supports 2 or 4.
#define SENSOR_ORIENTATION_HORIZONTAL 1         // Which orientation the sensors are mounted on the screen. 0 for vertical (on the sides), 1 for horizontal (top and bottom).

static const int32_t hostScreenWidth = 3000;    // Width of the screen which the raspberry pi will be sending touches to, unit is 1/10 mm.
static const int32_t hostScreenHeight = 3000;   // Height of the screen which the raspberry pi will be sending touches to, unit is 1/10 mm.

static const bool verbose = false;

typedef enum SensorPosition
{
    SensorPositionTopLeft = 0,
    SensorPositionBottomLeft = 1,
    SensorPositionTopRight = 2,
    SensorPositionBottomRight = 3
} SensorPosition;

typedef struct SensorConfiguration
{
    SensorPosition  SensorPosition;
    uint32_t        TouchActiveAreaWidth;
    uint32_t        TouchActiveAreaHeight;
    char          * McuUniqueIdentifier;
} SensorConfiguration;

typedef struct TouchInfo
{
    uint32_t              X;
    uint32_t              Y;
    TouchEvent            Event;
    uint64_t              Timestamp;
    SensorConfiguration * SensorConfiguration;
} TouchInfo;

typedef struct SensorGroupHandler
{
    zForceThread   * Thread;
    volatile bool    ShutDownNow;
    Queue          * SensorGroupQueue;
} SensorGroupHandler;

typedef struct IndexedMessage
{
    SensorConfiguration * SensorConfiguration;
    SensorGroupHandler  * SensorGroupHandler;
    uint64_t              Timestamp;
    Message             * Message;
} IndexedMessage;

#endif // COMMON_H