/*
* Copyright (c) 2002-2007 Nokia Corporation and/or its subsidiary(-ies).
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
* Description:  EikSrv keysound map.
*
*/

#ifndef __EIKKEYSOUNDMAP_H__
#define __EIKKEYSOUNDMAP_H__

#include <e32base.h>
#include <w32std.h>

class TSKey
    {
public:
    void Set(TInt aKeyCode, TInt aRepeatType, TInt aSid);
public:
    TInt iKeyCode;
    TInt iSid;
    };

// CEikSoundStack - implements a single sound map

NONSHARABLE_CLASS(CEikKeySoundMap) : public CArrayFixFlat<TSKey>
    {
public:
    static CEikKeySoundMap* NewL();
    ~CEikKeySoundMap();
    void InternalizeL(RReadStream& aStream, TInt aIndex, TInt aUid);
    TBool Find(TSKey& aKey);
    TInt ContextResourceId();
    void SetContextResourceId(TInt aContextResId);
private:
    CEikKeySoundMap();
private:
    TInt iContextResourceId;
    };


// CEikKeySoundStack - provides logic for searching sound maps

NONSHARABLE_CLASS(CEikKeySoundStack) : public CArrayPtrFlat<CEikKeySoundMap>
    {
public:
    static CEikKeySoundStack* NewL();
    ~CEikKeySoundStack();
    TBool Find(TInt aScanCode, TInt aRepeat, TInt& aSid);
private:
    CEikKeySoundStack();
    TInt iPreviousRepeat;
    };

#endif
