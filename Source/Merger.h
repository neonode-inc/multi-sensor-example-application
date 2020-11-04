#ifndef MERGER_H
#define MERGER_H

#include <stdint.h>
#include <stdbool.h>
#include "Utility.h"

#define DEBOUNCE_INTERVAL (100)
#define GLOBAL_TIMEOUT (100)
#define SEARCH_MATCH 1
#define SEARCH_UNMATCH 0

typedef enum SensorState
{
    SensorStateIdle = 0,
    SesnorStateDownPending,
    SensorStateDown,
    SensorStateMove,
    SensorStateUpPending,
    SensorStateUp
}SensorState;

extern bool    globalTriggerTimeout;
extern int32_t globalTimeoutInMs;
extern bool    allSensorConfigurationsReceived;
extern int     numberOfSensorConfigurationsReceived;

/*  Adds sensor configuration to internal array and sets flag when all configurations are added. The configuartions are used for mapping coordniates.
 * 
 *  @return true on success, false on fail.
*/
bool AddSensorConfiguration(SensorConfiguration sensorConfiguration);

/*  Merge touch and process the touch according to the above flowchart.
 *  This is the single entry point for incoming touch.
 * 
 *  @return processed indexedMessage, NULL if invalidated or error occured.
*/
IndexedMessage * MergeTouch(IndexedMessage * indexedMessage);

/*  Gets the current push index for the buffer.
 * 
 *  @return touchBufPushIndex.
*/
int TouchBufGetCurrentPushIndex(void);

/*  Pops touch at custom position with the option of updating the pop index.
 * 
 *  @return touch, NULL if unsuccessful. 
*/
TouchInfo * TouchBufPopCustom(int offset, bool updatePopIndex);

/*  Pops last written touch from buffer.
 * 
 *  @return touch, NULL if buffer is empty.
*/
TouchInfo * TouchBufPopLastWritten(void);

/*  Pops touch from buffer and updates the pop index.
 * 
 *  @return touch, NULL if buffer is empty.
*/
TouchInfo * TouchBufPop(void);

/*  Push a touch to the buffer and updates the push index.
 * 
 *  @return push index.
*/
int TouchBufPush(TouchInfo * info);

/*  Copy parameters into a Touchinfo struct for later processing. */
void CopyTouchInfo(TouchInfo * dest, 
                    const uint32_t xInput,
                    const uint32_t yInput,
                    const TouchEvent eventInput,
                    const uint64_t timestampInput,
                    SensorConfiguration * configurationInput);

/*  Timeout handle function. Resets the internal state machine.  */
void TimeoutCallback(void);

/*  Sets the timeout flags.  */
void TriggerTimeout(int32_t timeout);

/*  Prints out the timestamp and state for a touch.  */
void DumpTouchInfo(TouchInfo * info);

/*  Gets a string describing the sensor position.  */
const char * GetSensorPositionName(SensorPosition sensorPosition);

/*  Gets a string describing the touch state.  */
char * GetTouchStateName(TouchEvent event);

#endif // MERGER_H