/*
* Copyright (c) 2006 Nokia Corporation and/or its subsidiary(-ies).
* All rights reserved.
* This component and the accompanying materials are made available
* under the terms of "Eclipse Public License v1.0"
* which accompanies this distribution, and is available
* at the URL "http://www.eclipse.org/legal/epl-v10.html".
*
* Initial Contributors:
* Nokia Corporation - initial contribution.
*
* Contributors:
*
* Description:  Panic codes for aknhlist library.
*
*/


#ifndef AKNHLISTPANIC_H
#define AKNHLISTPANIC_H


/** Panic codes used throughout the code in aknhlist library.
    These panics have a category of AKNHLIST. */
enum TAknHListPanic
    {
    /** Invalid item ID. The client has used an item ID to refer to some
        non-existing item. This panic is raised, for example, when client
        uses an ID of item that has already been removed from the list. */
    EAknHListPanicInvalidItemID      = 0,
    /** Invalid item type. The client has referred to item an item of wrong
        type. This is raised, for example, when client tries to add an item
        into a leaf item. */
    EAknHListPanicInvalidItemType    = 1
    };


#endif // AKNHLISTPANIC_H
