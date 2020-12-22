#ifndef UTILITY_H
#define UTILITY_H

#include "Common.h"
#include <stdbool.h>

#define MAX_FILE_STRING_SIZE 100

/*  Reads the sensor_positions.csv file containing the MCU unique identifiers and sensor positions. 
 * 
 *  @return true if it successfully reads out the number of sensor positions equal to NUMBER_OF_SENSORS, otherwise false.
*/
bool ReadSensorPositionsFile(SensorConfiguration sensorConfigs[]);

/*  Writes the given SensorConfigurations MCU unique identifiers and sensor positions to the sensor_positions.csv file.
 * 
 *  @return true on success, false on fail.
*/
bool WriteSensorPositionsFile(SensorConfiguration sensorConfigs[]);

/*  Gets the difference between two timestamps in milliseconds.
 * 
 *  @return the difference in milliseconds.
*/
uint32_t GetTimestampDiff(TouchInfo * info, TouchInfo * history);

/*  Calculates the milliseconds for given timestamp.
 * 
 *  @return the timestamp in milliseconds.
*/
uint32_t GetMillisecond(uint64_t timestamp);

/*  Calculates and prints out year, month, day, hour, min, sec, millisec for given timestamp.  */
void PrintDateTimeFromUTC(uint64_t timestamp);

/*  Converts the SDK touch event to an application event type.  */
ApplicationTouchEvent ConvertTouchEvent(TouchEvent event);

#endif // UTILITY_H