/*
* Copyright (c) 2002 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  Avkon Sound Map
*
*/

// AKNSOUNDMAP.H
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// AknSoundMap - maps a set of keys to SID's


#if !defined(__AKNSOUNDMAP_H__)
#define __AKNSOUNDMAP_H__

#include <e32base.h>
#include <w32std.h>
#include <barsread.h>

class TSKey
    {
public:
    void Set(TInt aKeyCode, TInt aRepeatType, TInt aSid);
public:
    TInt iKeyCode;
    TInt iSid;
    };

// CAknSoundStack - implements a single sound map

class CAknKeySoundMap : public CArrayFixFlat<TSKey>
    {
public:
    static CAknKeySoundMap* NewL();
    ~CAknKeySoundMap();
    void ConstructFromResourceL(TResourceReader& aReader);
    TBool Find(TSKey& aKey);
private:
    CAknKeySoundMap();
    };


// CAknKeySoundStack - provides logic for searching sound maps

class CAknKeySoundStack : public CArrayPtrFlat<CAknKeySoundMap>
    {
public:
    static CAknKeySoundStack* NewL();
    ~CAknKeySoundStack();
    TBool Find(const TKeyEvent& aKeyEvent, TInt& aSid);
private:
    CAknKeySoundStack();
    TKeyEvent iPreviousEvent;
    };

#endif
