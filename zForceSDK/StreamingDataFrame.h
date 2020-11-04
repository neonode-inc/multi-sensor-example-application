/*! \file
 * \brief StreamingDataFrame.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#if !defined(DATAFRAME_STREAMINGDATAFRAME_H) && !defined(CONTAINS_STREAMINGDATAFRAME)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

/*!
 * \sa struct StreamingDataFrame
 */
typedef struct StreamingDataFrame StreamingDataFrame;
/*!
 * \brief Struct containing the StreamingDataFrame information.
 *
 * StreamingDataFrame contains the DataFrame base, a pointer to the data and
 * its length.
 *
 */
struct StreamingDataFrame
{
#endif // !defined(DATAFRAME_STREAMINGDATAFRAME_H) && !defined(CONTAINS_STREAMINGDATAFRAME)
#if !defined(DATAFRAME_STREAMINGDATAFRAME_H) || defined(CONTAINS_STREAMINGDATAFRAME)
    #define CONTAINS_DATAFRAME
    #include <DataFrame.h>
    #undef CONTAINS_DATAFRAME
    uint8_t * Data;   //!< Pointer to the data.
    uint32_t  Length; //!< Length of the data.
#endif // !defined(DATAFRAME_STREAMINGDATAFRAME_H) || defined(CONTAINS_STREAMINGDATAFRAME)
#if !defined(DATAFRAME_STREAMINGDATAFRAME_H) && !defined(CONTAINS_STREAMINGDATAFRAME)
};

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Create a new StreamingDataFrame.
 *
 * Creates a new streaming data frame and all the resources needed.
 * \n\n
 * On failure, errno is set.
 * - ::EOUTOFMEMORY - Memory allocation failed.
 *
 * \return Return a pointer to the allocated StreamingDataFrame upon success,
 *         otherwise a NULL pointer is returned and errno is set accordingly.
 */
DLLEXTERNAL StreamingDataFrame * StreamingDataFrame_New (uint64_t relativeTimeoutMilliSeconds, uint32_t length);

#ifdef __cplusplus
}
#endif // __cplusplus

/*!
 * \brief The streaming DataFrameType.
 */
#define STREAMINGDATAFRAMETYPE "Streaming"

#define DATAFRAME_STREAMINGDATAFRAME_H
#endif // !defined(DATAFRAME_STREAMINGDATAFRAME_H) && !defined(CONTAINS_STREAMINGDATAFRAME)

