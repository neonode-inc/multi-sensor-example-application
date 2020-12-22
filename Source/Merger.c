#include "Merger.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <zForceCommon.h>
#include <errno.h>
#include <Message.h>

#define TOUCH_BUF_SIZE 16

typedef enum TouchInfoKey
{
    TouchInfoX = 0,
    TouchInfoY = 1,
    TouchInfoEvent = 2,
    TouchInfoTimestamp = 3,
    TouchInfoSensorPosition = 4
} TouchInfoKey;

void HandleStateUpPending(void);
void HandleStateReset(void);
void PrintStateArbitratorError(TouchInfo * info);
SensorState MapTouchstateToSensorstate(TouchInfo * info);

void TouchBufSyncPushAndPopIndex(void);
int TouchBufGetCurrentLoad(void);
int TouchBufRewriteCurrent(TouchInfo * info);
int TouchBufEmptyCurrent(void);

TouchInfo * MapTouchCoordinates(TouchInfo * output, TouchInfo * input);
TouchInfo * Debounce(TouchInfo * info);
TouchInfo * Deghost(TouchInfo * info);
TouchInfo * WeightedPosition(TouchInfo * info);
TouchInfo * CoordinatesSmoother(TouchInfo * info);
TouchInfo * StateArbitrator(TouchInfo * info);
TouchInfo * FindHistoryBy(TouchInfo * info, TouchInfoKey key, bool searchSame);
bool IsCloserToOppositeSensor(TouchInfo * info);

SensorConfiguration * GetSensorConfigurationForSensorPosition(SensorPosition sensorPosition);
SensorConfiguration * GetOppositeSensorConfiguration(SensorConfiguration * sensorConfiguration);
int GetActiveAreaOverlapY(SensorConfiguration * sensorConfig);

// Local (static) Variables
static const int    touchBufSize = TOUCH_BUF_SIZE;
static TouchInfo    touchBuf[TOUCH_BUF_SIZE] = {0};
static volatile int touchBufPushIndex = 0;
static volatile int touchBufPopIndex = 0;
static volatile int touchBufLoad = 0;
 
static SensorState         global_sensor_state = SensorStateIdle;
static SensorConfiguration sensorConfigurations[NUMBER_OF_SENSORS] = { 0 };

// Global variables
bool    globalTriggerTimeout = false;
int32_t globalTimeoutInMs = GLOBAL_TIMEOUT;
bool    allSensorConfigurationsReceived = false;
int     numberOfSensorConfigurationsReceived = 0;

// Global error shutdown flag
extern volatile bool shutDownNow;

/*  ********** Ring buffer ********** 
 * 
 */

/*  Gets the current push index for the buffer.
 * 
 *  @return touchBufPushIndex.
*/
int TouchBufGetCurrentPushIndex()
{
    return touchBufPushIndex;
}

/*  Sets the pop index to the push index.  */
void TouchBufSyncPushAndPopIndex()
{
    touchBufPopIndex = touchBufPushIndex;
}

/*  Gets the number of elements in buffer.
 * 
 *  @return touchBufLoad.
*/
int TouchBufGetCurrentLoad()
{
    return touchBufLoad;
}

/*  Pops touch at custom position with the option of updating the pop index.
 * 
 *  @return touch, NULL if unsuccessful. 
*/
TouchInfo * TouchBufPopCustom(int offset, bool updatePopIndex)
{
    int index = touchBufPopIndex + offset;

    if(index >= touchBufSize)
    {
        if((index - touchBufSize) < touchBufSize)
        {
            index = index - touchBufSize;
        }
        else
        {
            return NULL;
        }
    }
    else if(index < 0)
    {
        if((index + touchBufSize) > 0)
        {
            index = index + touchBufSize;
        }
        else
        {
            return NULL;
        }
    }

    if(updatePopIndex)
    {
        touchBufPopIndex = index;
    }

    return &touchBuf[index];
}

/*  Pops last written touch from buffer.
 * 
 *  @return touch, NULL if buffer is empty.
*/
TouchInfo * TouchBufPopLastWritten()
{
    if(touchBufLoad == 0)
    {
        return NULL;
    }
    
    return &touchBuf[touchBufPushIndex];
}

/*  Pops touch from buffer and updates the pop index.
 * 
 *  @return touch, NULL if buffer is empty.
*/
TouchInfo * TouchBufPop()
{
    if(touchBufLoad == 0)
    {
        return NULL;
    }

    if(--touchBufPopIndex < 0)
    {
        touchBufPopIndex = touchBufLoad - 1;
    }

    return &touchBuf[touchBufPopIndex];
}

/*  Copies touch to buffer at current push index.
 * 
 *  @return push index.
*/
int TouchBufRewriteCurrent(TouchInfo * info)
{
    memcpy(&touchBuf[touchBufPushIndex], info, sizeof(TouchInfo));
    return touchBufPushIndex;
}

/*  Removes current touch.
 * 
 *  @return push index, -1 if buffer is empty.
*/
int TouchBufEmptyCurrent()
{
    if(touchBufLoad == 0)
    {
        return -1;
    }

    if(--touchBufPushIndex < 0)
    {
        touchBufLoad--;
        touchBufPushIndex = touchBufSize;
    }
    return touchBufPushIndex;
}

/*  Push a touch to the ring buffer.
 * 
 *  @return push index.
*/
int TouchBufPush(TouchInfo * info)
{
    if(touchBufLoad == 0)
    {
        touchBufPushIndex = 0;
    }
    else if(++touchBufPushIndex >= touchBufSize)
    {
        touchBufPushIndex = 0;
    }

    if(++touchBufLoad > touchBufSize)
    {
        touchBufLoad = touchBufSize;
    }
        
    return TouchBufRewriteCurrent(info);
}

/*  ********** Touch info processing ********** 
 * 
 */

/*  Tries to find old touch with given key, either matched or unmatched.
 * 
 *  @return history if matched, NULL otherwise.
*/
TouchInfo * FindHistoryBy(TouchInfo * info, TouchInfoKey key, bool searchSame)
{
    TouchBufSyncPushAndPopIndex();
    
    for(int i = 0; i < TouchBufGetCurrentLoad(); i++)
    {
        TouchInfo *history = TouchBufPop();
        if(key == TouchInfoSensorPosition)
        {
            if(searchSame && info->SensorConfiguration->SensorPosition == history->SensorConfiguration->SensorPosition)
            {
                return history;
            }
            else if(info->SensorConfiguration->SensorPosition != history->SensorConfiguration->SensorPosition)
            {
                return history;
            }
        }
        else if(key == TouchInfoEvent)
        {
            if(searchSame && info->Event == history->Event)
            {
                return history;
            }
            else if(info->Event != history->Event)
            {
                return history;
            }
        }
        else if(key == TouchInfoTimestamp)
        {
            if(searchSame && (info->Timestamp == history->Timestamp))
            {
                return history;
            }
            else if(info->Timestamp != history->Timestamp)
            {
                return history;
            }
        }
        else if(key == TouchInfoX)
        {
            if(searchSame && info->X == history->X)
            {
                return history;
            }
            else if(info->X != history->X)
            {
                return history;
            }
        }
        else if(key == TouchInfoY)
        {
            if(searchSame && info->Y == history->Y)
            {
                return history;
            }
            else if(info->Y != history->Y)
            {
                return history;
            }
        }
        else
        {
            printf("Error: failed in 'GetHistoryBy'\n");
        }
    }
    return NULL; // no match.
}

/*  Checks if touch is closer to opposite sensor in Y-axis.
 * 
 *  @return true if touch is closer to oppsite sensor, false if not.
*/
bool IsCloserToOppositeSensor(TouchInfo *info)
{
    int overlapY = GetActiveAreaOverlapY(info->SensorConfiguration);
    if (overlapY < 0)
    {
        return false;
    }

    return info->Y > info->SensorConfiguration->TouchActiveAreaHeight - overlapY / 2;
}

/*    ********** Brief program flow **********
 *
 *    Sensor thread 1 \
 *           .         \
 *           .          --> Sensor group thread --> Main thread
 *           .         /        ^
 *    Sensor thread n /         |
 *                              v
 *                      --> MergeTouch
 *                      |   |
 *                      |   |- MapTouchCoordinates
 *                      |   v
 *                      |   |- Debounce
 *                      |   v
 *                      |   |- StateArbitrator (see state machine flowchart)
 *                      |   v
 *                      |   |- Deghost
 *                      |   v
 *                      |   |- WeightedPosition
 *                      |   v
 *                      --- |- CoordinatesSmoother
 *
 */

/*  Merge touch and process the touch according to the above flowchart.
 *  This is the single entry point for incoming touch.
 * 
 *  @return processed indexedMessage, NULL if invalidated or error occured.
*/
IndexedMessage * MergeTouch(IndexedMessage * indexedMessage)
{
    // ***** push new data to a TouchInfo struct *****

    TouchMessage * touchMessage = (TouchMessage *)indexedMessage->Message;
    TouchInfo touchNew = {0};
    CopyTouchInfo(&touchNew, 
                    touchMessage->X, touchMessage->Y, 
                    touchMessage->Event, indexedMessage->Timestamp, 
                    indexedMessage->SensorConfiguration);
    
    // ***** pre-process new data ***** 

    TouchInfo touchTemp = {0};
    memcpy(&touchTemp, &touchNew, sizeof(TouchInfo));
    TouchInfo * info = &touchTemp;

    bool isCloserToOppositeSensor = IsCloserToOppositeSensor(info);

    info = MapTouchCoordinates(info, &touchNew);
    if (info == NULL)
    {
        printf("Error: Could not map coordinates, something wrong with configuration.\n");
        shutDownNow = true;
        return NULL;
    }

    TouchBufPush(info);
    
    // ***** Post procesing touch info data *****
 
    if(Debounce(info) == NULL)
    {
        return NULL;
    }

    if(StateArbitrator(info) == NULL)
    {
        return NULL;
    }

    if(Deghost(info) == NULL)
    {
        return NULL;
    }

    if (isCloserToOppositeSensor)
    {
        info = WeightedPosition(info);
    }
    
    info = CoordinatesSmoother(info);

    // ***** assemble data back to the indexedMessage *****
    
    TouchMessage * merged = (TouchMessage *)indexedMessage->Message; // reuse the input IndexedMessage.
    merged->X = info->X;
    merged->Y = info->Y;
    merged->Event = info->Event;

    return indexedMessage;
}

/*  Copy parameters into a Touchinfo struct for later processing. */
void CopyTouchInfo(TouchInfo * dest, 
                    const uint32_t xInput,
                    const uint32_t yInput,
                    const ApplicationTouchEvent eventInput,
                    const uint64_t timestampInput,
                    SensorConfiguration * configurationInput)
{
    dest->X = xInput;
    dest->Y = yInput;
    dest->Event = eventInput;
    dest->Timestamp = timestampInput;
    dest->SensorConfiguration = configurationInput;
}

/*  ********** Sensor orientations **********
 *
 *     HORIZONTAL 1            HORIZONTAL 0 (i.e. vertical)
 *
 *   Top Left  Top Right    Top Left   Top Right
 *    _______  _______          _         _
 *   |c______||______c|        |c|       |c|
 *                             | |       | |
 *                             |_|       |_|
 *    _______  _______          _         _
 *   |c______||______c|        | |       | |
 *                             | |       | |
 *   Btm Left  Btm Right       |c|       |c|
 *
 *                          Btm Left   Btm Right
 *
 * c indicates the connector side of the touch sensor.
*/

/*  Map coordinates from each sensor to the entire screen active area.
 * 
 *  @return processed input, NULL if error occurs.
*/
TouchInfo * MapTouchCoordinates(TouchInfo *output, TouchInfo *input)
{
    if (SENSOR_ORIENTATION_HORIZONTAL)
    {
        if (output->SensorConfiguration->SensorPosition == SensorPositionTopLeft)
        {
            output->X = input->X;
            output->Y = input->Y;
        }
        else if (output->SensorConfiguration->SensorPosition == SensorPositionTopRight)
        {
            SensorConfiguration * topLeftConfig = GetSensorConfigurationForSensorPosition(SensorPositionTopLeft);
            if (topLeftConfig == NULL)
            {
                return NULL;
            }

            // Add top left width to x and invert x since the sensor is flipped.
            output->X = topLeftConfig->TouchActiveAreaWidth + (output->SensorConfiguration->TouchActiveAreaWidth - input->X);
            output->Y = input->Y;
        }
        else if (output->SensorConfiguration->SensorPosition == SensorPositionBottomLeft)
        {
            SensorConfiguration * topLeftConfig = GetSensorConfigurationForSensorPosition(SensorPositionTopLeft);
            if (topLeftConfig == NULL)
            {
                return NULL;
            }
            int overlapY = GetActiveAreaOverlapY(input->SensorConfiguration);
            if (overlapY < 0)
            {
                return NULL;
            }

            // Add top left height to y and invert y since the coordinates should increase the closer they get to the sensor.
            output->X = input->X;
            output->Y = (input->SensorConfiguration->TouchActiveAreaHeight - input->Y) + topLeftConfig->TouchActiveAreaHeight - overlapY;
        }
        else if (output->SensorConfiguration->SensorPosition == SensorPositionBottomRight)
        {
            SensorConfiguration * bottomLeftConfig = GetSensorConfigurationForSensorPosition(SensorPositionBottomLeft);
            SensorConfiguration * topRightConfig = GetSensorConfigurationForSensorPosition(SensorPositionTopRight);
            if (bottomLeftConfig == NULL  || topRightConfig == NULL)
            {
                return NULL;
            }
            int overlapY = GetActiveAreaOverlapY(input->SensorConfiguration);
            if (overlapY < 0)
            {
                return NULL;
            }

            // Add bottom left width to x and invert x since the sensor is flipped.
            // Add top right height to y, reduce with overlap and invert y since the coordinates should increase the closer they get to the sensor.
            output->X = bottomLeftConfig->TouchActiveAreaWidth + (input->SensorConfiguration->TouchActiveAreaWidth - input->X);
            output->Y = (input->SensorConfiguration->TouchActiveAreaHeight - input->Y) + topRightConfig->TouchActiveAreaHeight - overlapY;
        }
        else
        {
            printf("Error: sensor position not recognized %d\t%d\n",
                output->SensorConfiguration->SensorPosition, input->SensorConfiguration->SensorPosition);
            return NULL;
        }
    }
    else // Vertical sensor orientation.
    {
        if (output->SensorConfiguration->SensorPosition == SensorPositionTopLeft)
        {
            // Swap x and y because of vertical orientation.
            output->X = input->Y;
            output->Y = input->X;
        }
        else if (output->SensorConfiguration->SensorPosition == SensorPositionTopRight)
        {
            SensorConfiguration * topLeftConfig = GetSensorConfigurationForSensorPosition(SensorPositionTopLeft);
            if (topLeftConfig == NULL)
            {
                return NULL;
            }
            int overlapY = GetActiveAreaOverlapY(input->SensorConfiguration);
            if (overlapY < 0)
            {
                return NULL;
            }

            // Swap x and y because of vertical orientation.
            // Add top left height, reduce with overlap and invert y since the coordinates should increase the closer they get to the sensor.
            output->X = (input->SensorConfiguration->TouchActiveAreaHeight - input->Y) + topLeftConfig->TouchActiveAreaHeight - overlapY;
            output->Y = input->X;
        }
        else if (output->SensorConfiguration->SensorPosition == SensorPositionBottomLeft)
        {
            SensorConfiguration * topLeftConfig = GetSensorConfigurationForSensorPosition(SensorPositionTopLeft);
            if (topLeftConfig == NULL)
            {
                return NULL;
            }

            // Swap x and y because of vertical orientation.
            // Add top left width and invert x since the sensor is flipped.
            output->X = input->Y;
            output->Y = (input->SensorConfiguration->TouchActiveAreaWidth - input->X) + topLeftConfig->TouchActiveAreaWidth;
        }
        else if (output->SensorConfiguration->SensorPosition == SensorPositionBottomRight)
        {
            SensorConfiguration * topRightConfig = GetSensorConfigurationForSensorPosition(SensorPositionTopRight);
            SensorConfiguration * bottomLeftConfig = GetSensorConfigurationForSensorPosition(SensorPositionBottomLeft);
            if (topRightConfig == NULL || bottomLeftConfig == NULL)
            {
                return NULL;
            }
            int overlapY = GetActiveAreaOverlapY(input->SensorConfiguration);
            if (overlapY < 0)
            {
                return NULL;
            }

            // Swap x and y because of vertical orientation.
            // Add bottom left height, reduce with overlap and invert y since the coordinates should increase the closer they get to the sensor.
            // Add top right width and invert x since the sensor is flipped.
            output->X = (input->SensorConfiguration->TouchActiveAreaHeight - input->Y) + bottomLeftConfig->TouchActiveAreaHeight - overlapY;
            output->Y = (input->SensorConfiguration->TouchActiveAreaWidth - input->X) + topRightConfig->TouchActiveAreaWidth;
        }
        else
        {
            printf("Error: sensor position not recognized %d\t%d\n",
                output->SensorConfiguration->SensorPosition, input->SensorConfiguration->SensorPosition);
            return NULL;
        }
    }

    return output;
}

/*  Remove unwanted fast up-then-down or down-then-up event.
 *  Those event can occur when sensors are interfere with each other.
 * 
 *  @return processed info, NULL if touch meets condition of unwanted touch.
*/
TouchInfo * Debounce(TouchInfo *info)
{
    // search for different event
    TouchInfo * history = FindHistoryBy(info, TouchInfoEvent, SEARCH_UNMATCH);

    if (history == NULL)
        return info;

    if (GetTimestampDiff(info, history) < DEBOUNCE_INTERVAL)
    {
        if (info->Event == App_UpEvent && history->Event == App_DownEvent)
        {
            if (verbose)
            {
                printf("Debounce removed up event. \n");
            }

            info->Event = App_MoveEvent;
            TouchBufRewriteCurrent(info);
            return NULL;
        }
        else if (info->Event == App_DownEvent && history->Event == App_UpEvent)
        {
            if (verbose)
            {
                printf("Debounce removed down event. \n");
            }

            info->Event = App_MoveEvent;
            TouchBufRewriteCurrent(info);
            return NULL;
        }
    }

    return info;
}

/*  Remove unwanted 'jump' event where a new coordinates suddenly appears to be
 *  at a far away place and then disappear shortly after.
 *  This can happen when a certain stray light caught by one sensor and
 *  interpret as a new touch.
 * 
 *  @return processed info, NULL if touch meets condition of unwanted touch.
*/
TouchInfo * Deghost(TouchInfo *info)
{
    if (info->Event == App_UpEvent)
    {
        return info;
    }

    // ***** search for different event *****
    TouchBufSyncPushAndPopIndex();
    TouchInfo * history = TouchBufPop();

    if (history == NULL)
    {
        return info;
    }

    if ((info->X == history->X) && (info->Y == history->Y))
    {
        return info;
    }

    float distance = sqrtf(pow(abs(info->X - history->X), 2) +
                           pow(abs(info->Y - history->Y), 2)) /
                     10;

    uint32_t time_diff = GetTimestampDiff(info, history);

    if (time_diff < 1)
    {
        time_diff = 1;
    }

    if (distance / time_diff > 5)
    { // too fast movement is sketchy, do not put into the buffer.
        TouchBufEmptyCurrent();

        if (verbose)
        {
            printf("\ndeghost %f mm for %d ms\t\t\tx %d\ty %d\n", distance, time_diff, info->X, info->Y);
        }

        return NULL;
    }
    else
    {
        if (time_diff > 100)
        { // very long interval
            if (verbose)
            {
                printf("t0 %d, t-1 %d\n", GetMillisecond(info->Timestamp), GetMillisecond(history->Timestamp));
            }
        }
        if (distance > 0 && info->Event != App_DownEvent)
        {
            if (verbose)
            {
                printf("%f mm for %d ms\n", distance, time_diff);
            }
        }
    }

    return info;
}

/*  Make a weight adjusted position in the overlapping zone among sensors.
 *  The basic concept is to trust the positon coming from a closer sensor.
 * 
 *  @return processed info.
*/
TouchInfo * WeightedPosition(TouchInfo * info)
{
    TouchInfo * history = FindHistoryBy(info, TouchInfoSensorPosition, SEARCH_UNMATCH);
    if(history != NULL && history->Event != App_UpEvent)
    {
        if(verbose)
        {
            printf("was %d now %d\n", info->X, (info->X + history->X * 4) / 5);
        }
        info->X = (info->X + history->X * 4) / 5; // use 20% of current position and 80% of history.
        info->Y = (info->Y + history->Y * 4) / 5; // use 20% of current position and 80% of history.
    }
    
    return info;
}

/*  Smooth the eventual coordinates by a simple rolling average method.
 * 
 *  @return processed info.
*/
TouchInfo * CoordinatesSmoother(TouchInfo * info)
{   // Rolling average the coordinates.
    int xTotal = info->X;
    int yTotal = info->Y;
    const uint32_t sampleSize = 8;
    uint32_t samples = 1;

    TouchBufSyncPushAndPopIndex();
    for(uint32_t i = 0; i < sampleSize - 1; i++)
    {
        TouchInfo * history = TouchBufPop();
        if(history != NULL && (history->Event == App_MoveEvent || history->Event == App_DownEvent))
        {
            samples++;
            xTotal += history->X;
            yTotal += history->Y;
        }
        else
        {
            break;
        }
    }

    info->X = xTotal / samples;
    info->Y = yTotal / samples;

    if(verbose)
    {
        printf("size %d\tx %d\ty %d\n", samples, info->X, info->Y);
    }

    return info;
}

/*  Adds sensor configuration to internal array and sets flag when all configurations are added. The configuartions are used for mapping coordniates.
 * 
 *  @return true on success, false on fail.
*/
bool AddSensorConfiguration(SensorConfiguration sensorConfiguration)
{
    for (int i = 0; i < numberOfSensorConfigurationsReceived; i++)
    {
        if (sensorConfigurations[i].SensorPosition == sensorConfiguration.SensorPosition)
        {
            printf("Error: duplicate configurations of sensor position: %s. \n", GetSensorPositionName(sensorConfiguration.SensorPosition));
            return false;
        }
    }

    sensorConfigurations[numberOfSensorConfigurationsReceived++] = sensorConfiguration;

    if (numberOfSensorConfigurationsReceived == NUMBER_OF_SENSORS)
    {
        allSensorConfigurationsReceived = true;
        printf("Sensor configurations done. \n");
    }

    return true;
}

/*  Gets the sensor configuration for a certain sensor position. 
 * 
 *  @return SensorConfiguration * if found, NULL otherwise.
*/
SensorConfiguration * GetSensorConfigurationForSensorPosition(SensorPosition sensorPosition)
{
    for (int i = 0; i < NUMBER_OF_SENSORS; i++)
    {
        if (sensorConfigurations[i].SensorPosition == sensorPosition)
        {
            return &sensorConfigurations[i];
        }
    }
    return NULL;
}

/*  Gets the sensor configuration opposite of given configuration in Y axis.
 * 
 *  @return SensorConfiguration * if found, NULL otherwise.
*/
SensorConfiguration * GetOppositeSensorConfiguration(SensorConfiguration * sensorConfiguration)
{
    if (SENSOR_ORIENTATION_HORIZONTAL)
    {
        if (sensorConfiguration->SensorPosition == SensorPositionTopLeft)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionBottomLeft);
        }
        else if (sensorConfiguration->SensorPosition == SensorPositionTopRight)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionBottomRight);
        }
        else if (sensorConfiguration->SensorPosition == SensorPositionBottomLeft)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionTopLeft);
        }
        else if (sensorConfiguration->SensorPosition == SensorPositionBottomRight)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionTopRight);
        }
    }
    else
    {
        if (sensorConfiguration->SensorPosition == SensorPositionTopLeft)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionTopRight);
        }
        else if (sensorConfiguration->SensorPosition == SensorPositionTopRight)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionTopLeft);
        }
        else if (sensorConfiguration->SensorPosition == SensorPositionBottomLeft)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionBottomRight);
        }
        else if (sensorConfiguration->SensorPosition == SensorPositionBottomRight)
        {
            return GetSensorConfigurationForSensorPosition(SensorPositionBottomLeft);
        }
    }

    return NULL;
}

/*  Calculates the overlap in Y axis between given sensor configuration and it's Y axis opposite configuration.
 * 
 *  @return overlapY.
*/
int GetActiveAreaOverlapY(SensorConfiguration * sensorConfig)
{
    SensorConfiguration * oppositeConfig = GetOppositeSensorConfiguration(sensorConfig);
    if (oppositeConfig == NULL)
    {
        printf("Error: Can't find opposite configuration for sensor position: %s \n", GetSensorPositionName(sensorConfig->SensorPosition));
        shutDownNow = true;
        return -1;
    }

    int hostActiveAreaHeight = SENSOR_ORIENTATION_HORIZONTAL ? hostScreenHeight : hostScreenWidth;

    int overlapY = (hostActiveAreaHeight - sensorConfig->TouchActiveAreaHeight - oppositeConfig->TouchActiveAreaHeight);

    if (overlapY > 0)
    {
        printf("Error: Gap in touch active area. \n");
        shutDownNow = true;
        return -1;
    }
    
    return abs(overlapY);
}

/*    ********** State machine [StateArbitrator] ********** 
 *
 *      Idle  ->  DownPending  ->  Down  ---------
 *        ^            /\           |            |
 *        |           /  \          v            v
 *        |<----------    ------>  Move  ->  UpPending
 *        |                                      |
 *        |                                      v
 *        -------------------------------------  Up
 */

/*  State machine for handling touches from multiple sensors.
 * 
 *  @return processed info, NULL if error occurs.
*/
TouchInfo * StateArbitrator(TouchInfo * info)
{
    SensorState state = MapTouchstateToSensorstate(info);
    
    if(global_sensor_state == SensorStateIdle)
    {
        if(state == SensorStateDown || state == SensorStateMove)
        {
            global_sensor_state = SesnorStateDownPending;
        }
        else
        {
            PrintStateArbitratorError(info);
            return NULL;
        }
    }

    else if(global_sensor_state == SesnorStateDownPending)
    {
        if(state == SensorStateDown || state == SensorStateMove)
        {
            global_sensor_state = SensorStateDown;
        }
        else if(state == SensorStateUp)
        {
            // Debounce(); // TODO: deal with Up without Down.
            HandleStateUpPending();
        }
        else
        {
            PrintStateArbitratorError(info);
            return NULL;
        }
    }

    else if(global_sensor_state == SensorStateDown || global_sensor_state == SensorStateMove)
    {
        if(state == SensorStateDown || state == SensorStateMove)
        {
            global_sensor_state = SensorStateMove;
        }
        else if(state == SensorStateUp)
        {
            HandleStateUpPending();
        }
        else
        {
            PrintStateArbitratorError(info);
            return NULL;
        }
    }

    else if(global_sensor_state == SensorStateUpPending)
    {
        if(state == SensorStateDown || state == SensorStateMove)
        {
            global_sensor_state = SensorStateMove;
        }
        else if(state == SensorStateUp)
        {
            global_sensor_state = SensorStateUp;
        }
        else
        {
            PrintStateArbitratorError(info);
            return NULL;
        }
    }

    else if(global_sensor_state == SensorStateUp)
    {
        if(state == SensorStateDown || state == SensorStateMove)
        {
            if(Debounce(info) != NULL)
            {
                HandleStateUpPending();
            }
        }
    }
    else
    {
        PrintStateArbitratorError(info);
        return NULL;
    }

    if(global_sensor_state == SensorStateDown || global_sensor_state == SensorStateMove || global_sensor_state == SensorStateUp)
    {
        switch(global_sensor_state)
        {
            case SensorStateDown: info->Event = App_DownEvent; break;
            case SensorStateMove: info->Event = App_MoveEvent; break;
            case SensorStateUp: info->Event = App_UpEvent; HandleStateReset(); break;
            default: PrintStateArbitratorError(info); return NULL;
        }
        TouchBufRewriteCurrent(info); 
    }
    else
    {
        return NULL;
    }

    return info;
}

/*  Sets the timeout flags.  */
void TriggerTimeout(int32_t timeout)
{
    globalTriggerTimeout = true;
    globalTimeoutInMs = timeout;
}

/*  Timeout handle function. Resets the internal state machine.  */
void TimeoutCallback()
{
    global_sensor_state = SensorStateUp;
    TouchInfo * info = TouchBufPopLastWritten();
    info->Event = App_UpEvent;
    TouchBufRewriteCurrent(info); 
    HandleStateReset();
}

/*  Convert touch events to state machine events.
 * 
 *  @return processed state.
*/
SensorState MapTouchstateToSensorstate(TouchInfo * info)
{
    SensorState state = SensorStateIdle;
    switch(info->Event)
    {
        case App_DownEvent: state = SensorStateDown; break;
        case App_MoveEvent: state = SensorStateMove; break;
        case App_UpEvent: state = SensorStateUp; break;
        default: break;
    }
    return state;
}

/*  Sets the internal state to up pending and triggers timeout.  */ 
void HandleStateUpPending()
{
    global_sensor_state = SensorStateUpPending;
    TriggerTimeout(GLOBAL_TIMEOUT);
}

/*  Resets the internal state to idle.  */ 
void HandleStateReset()
{
    global_sensor_state = SensorStateIdle;
}

/*  Print out state machine error for given touch.  */ 
void PrintStateArbitratorError(TouchInfo * info)
{
    global_sensor_state = SensorStateIdle;
    printf("Error: Faulty StateArbitrator touch state: %s\t", GetTouchStateName(info->Event));
}

/*  ********** Helper functions ********** 
 *
 */

/*  Prints out the timestamp and state for a touch.  */
void DumpTouchInfo(TouchInfo * info)
{
    uint32_t t = info->Timestamp;
    printf("%d.%s%d \t",t/1000, (t%1000)<100?(t%1000)<10?"00":"0":"", t%1000);
    printf("%s\n", GetTouchStateName(info->Event));
}

/*  Gets a string describing the sensor position.  */
const char * GetSensorPositionName(SensorPosition sensorPosition)
{
    static const char * positionName = NULL;
    switch (sensorPosition)
    {
        case SensorPositionTopLeft:
            positionName = "Top Left";
        break;
        case SensorPositionTopRight:
            positionName = "Top Right";
        break;
        case SensorPositionBottomLeft:
            positionName = "Bottom Left";
        break;
        case SensorPositionBottomRight:
            positionName = "Bottom Right";
        break;
        default:
            positionName = "Unknown Position";
        break;
    }
    return positionName;
}

/*  Gets a string describing the touch state.  */
char * GetTouchStateName(ApplicationTouchEvent event)
{
    char         * eventString = NULL;
    switch (event)
    {
        case App_DownEvent:
            eventString = "****";
        break;

        case App_MoveEvent:
            eventString = "....";
        break;

        case App_UpEvent:
            eventString = "====";
        break;

        case App_DownPendingEvent:
            eventString = "**";
        break;

        case App_UpPendingEvent:
            eventString = "==";
        break;

        case App_InvalidEvent:
            eventString = "Invalid";
        break;

        case App_GhostEvent:
            eventString = "Ghost";
        break;

        default:
            eventString = "Unknown";
        break;
    }
    return eventString;
}