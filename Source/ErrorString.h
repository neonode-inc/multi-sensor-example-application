/*! \file
 * \brief Convert error codes into human readable English language strings.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#ifndef ERRORSTRING_H
#define ERRORSTRING_H

// Exported Functions

/*!
 * \brief Convert an error code to a string.
 *
 * Convert an error code into a human readable English language string.
 * \param message The error code to be converted.
 * \return A pointer to a NUL terminated character string.
 */
char * ErrorString (int errorCode);

#endif // ERRORSTRING_H



