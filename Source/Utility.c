#include "Utility.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zForce.h>

/*  ********** File handling ********** 
 *
 */

/*  Reads the sensor_positions.csv containing the MCU unique identifiers and sensor positions. 
 * 
 *  @return true if it successfully reads out the number of sensor positions equal to NUMBER_OF_SENSORS, otherwise false.
*/
bool ReadSensorPositionsFile(SensorConfiguration sensorConfigs[])
{
    int sensorIndex = 0;
    FILE *configFile;
    bool result = false;
    zForce * zForceInstance = zForce_GetInstance();

    if (zForceInstance == NULL)
    {
        return result;
    }

    if ((configFile = fopen("sensor_positions.csv", "r")))
    {
        char line[MAX_FILE_STRING_SIZE];
        while (fgets(line, MAX_FILE_STRING_SIZE, configFile))
        {
            int valueIndex = 0;
            char *values = strtok(line, ",");
            while (values != NULL)
            {
                int len = strlen(values);
                if (len > 0 && values[len - 1] == '\n')
                {
                    values[len - 1] = 0; // remove \n character.
                }

                if (valueIndex == 0)
                {
                    sensorConfigs[sensorIndex].SensorPosition = atoi(values);
                }
                else if (valueIndex == 1)
                {
                    sensorConfigs[sensorIndex].McuUniqueIdentifier = (char*)zForceInstance->OsAbstractionLayer.MallocWithPattern(strlen(values) + 1, 0);
                    strcpy(sensorConfigs[sensorIndex].McuUniqueIdentifier, values);
                    break;
                }
                valueIndex++;
                values = strtok(NULL, ",");
            }
            sensorIndex++;
            if (sensorIndex == NUMBER_OF_SENSORS)
            {
                result = true;
                break;
            }
        }
        fclose(configFile);
    }
    return result;
}

/*  Writes the given SensorConfigurations MCU unique identifiers and sensor positions to the sensor_positions.csv file.
 * 
 *  @return true on success, false on fail.
*/
bool WriteSensorPositionsFile(SensorConfiguration sensorConfigs[])
{
    FILE *configFile;
    if ((configFile = fopen("sensor_positions.csv", "w")))
    {
        printf("Creating sensor_positions.csv file.\n");
        for (int i = 0; i < NUMBER_OF_SENSORS; i++)
        {
            fprintf(configFile, "%d,%s\n", sensorConfigs[i].SensorPosition, sensorConfigs[i].McuUniqueIdentifier);
        }
        fclose(configFile);
    }
    else
    {
        perror("Error: Writing sensor positions file");
        return false;
    }
    return true;
}

/*  ********** Timestamps ********** 
 *
 */

/*  Calculates the milliseconds for given timestamp.
 * 
 *  @return the timestamp in milliseconds.
*/
uint32_t GetMillisecond(uint64_t timestamp)
{
    uint64_t u = timestamp;
    unsigned long w = u % 1000000000;
    unsigned millisec = w % 1000;
    w /= 1000;
    unsigned sec = w % 100;
    w /= 100;
    unsigned min = w % 100;

    return (min*60+sec)*1000+millisec;
}

/*  Calculates and prints out year, month, day, hour, min, sec, millisec for given timestamp.  */
void PrintDateTimeFromUTC(uint64_t timestamp)
{
    uint64_t u = timestamp;
    unsigned long w = u % 1000000000;
    unsigned millisec = w % 1000;
    w /= 1000;
    unsigned sec = w % 100;
    w /= 100;
    unsigned min = w % 100;
    unsigned hour = w / 100;
    unsigned long v = w / 1000000000;
    unsigned day = v % 100;
    v /= 100;
    unsigned month = v % 100;
    unsigned year = v / 100;
    printf("%d-%d-%d %d'%d\"%d:%d\t", year, month, day, hour, min, sec, millisec);
}

/*  Gets the difference between two timestamps in milliseconds.
 * 
 *  @return the difference in milliseconds.
*/
uint32_t GetTimestampDiff(TouchInfo * info, TouchInfo * history)
{
    return GetMillisecond(info->Timestamp) - GetMillisecond(history->Timestamp);
}