/*! \file
 * \copyright
 * COPYRIGHT NOTICE: (c) 2018 Neonode Technologies AB. All rights reserved.
 *
 * \sa zForce.h
 */

#if !defined(ZFORCE_WINDOWS_OSABSTRACTIONLAYER_WINDOWS_H)

#ifndef ZFORCECOMMON_H
    #error Please include "zForceCommon.h" before this file.
#endif // ZFORCECOMMON_H

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*!
 * \brief Windows Specific Initialization of OsAbstractionLayer.
 */
DLLINTERNAL bool        OsAbstractionLayerOs_Initialize(OsAbstractionLayer * osAbstractionLayer,
                                                        OsAbstractionLayer * osAbstractionLayerOsSpecific);

#ifdef __cplusplus
}
#endif // __cplusplus

#define ZFORCE_WINDOWS_OSABSTRACTIONLAYER_WINDOWS_H
#endif // !defined(ZFORCE_WINDOWS_OSABSTRACTIONLAYER_WINDOWS_H)

