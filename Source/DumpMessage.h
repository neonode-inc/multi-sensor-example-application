/*! \file
 * \brief Dump message contents.
 *
 * \copyright
 * COPYRIGHT NOTICE: (c) 2017-2018 Neonode Technologies AB. All rights reserved.
 *
 */

#ifndef DUMPMESSAGE_H
#define DUMPMESSAGE_H

// Exported Functions

/*!
 * \brief Dump a message's contents.
 *
 * Display the contents of a message on stdout.
 * \param message The message to be displayed.
 * \return No return value.
 */
void DumpMessage (Message * message);
void DumpTouchMessage (Message * message);

#endif // DUMPMESSAGE_H

