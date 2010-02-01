/*
* Copyright (c) 2008 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Common constants for soft notifications.
*
*/

#ifndef AKNSOFTNOTECONSTS_H
#define AKNSOFTNOTECONSTS_H


// CONSTANTS

// Custom soft notification sub types:
//
/// Soft notification parameter identification for custom soft notification.
const TInt KAknSoftNotificationCustom   = 0x0001;
/// Soft notification parameter identification for dynamic soft notification.
const TInt KAknSoftNotificationDynamic  = 0x0002;


/// Dynamic soft notification events:
enum TAknDynamicSNoteEvent
    {
    EAknDynamicSNoteEventAccepted = 1,  // Soft notification was accepted.
    EAknDynamicSNoteEventCanceled,      // Soft notification was canceled.
    };

#endif // AKNSOFTNOTECONSTS_H
