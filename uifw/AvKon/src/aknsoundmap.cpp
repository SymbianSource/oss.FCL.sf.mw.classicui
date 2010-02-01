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
* Description:  Sound Map
*
*/


// AKNSOUNDMAP.CPP
//
// Copyright (c) 1997-2000 Symbian Ltd.  All rights reserved.
//

// AknSoundMap - maps a set of keys to SID's


#include "AknSoundMap.h"
#include <avkon.hrh>


const TInt KAknKeySoundMapGranularity = 4;
const TInt KAknSKeyGranularity = 16;

// class TSkey - SKey definition
// Keycode and Repeat are stored as a single code, to enable fast searching
void TSKey::Set(TInt aKeyCode, TInt aRepeatType, TInt aSid)
    {
    iSid = aSid;
    iKeyCode = aKeyCode + (aRepeatType << 16);
    }


CAknKeySoundMap* CAknKeySoundMap::NewL()
    {
    CAknKeySoundMap* self = new(ELeave)CAknKeySoundMap();
    return self;
    }

CAknKeySoundMap::~CAknKeySoundMap()
    {
    }

CAknKeySoundMap::CAknKeySoundMap()
:CArrayFixFlat<TSKey>(KAknSKeyGranularity)
    {
    }


void CAknKeySoundMap::ConstructFromResourceL(TResourceReader& aReader)
    {
    TInt count = aReader.ReadInt16();
    for (TInt ii=0; ii<count; ii++)
        {
        TInt sid = aReader.ReadInt16();
        TInt key = aReader.ReadUint16();
        TInt type = aReader.ReadInt8();
        TSKey sKey;
        sKey.Set(key, type, sid);
        TKeyArrayFix sidKey(_FOFF(TSKey, iKeyCode), ECmpTInt);
        InsertIsqL(sKey, sidKey);
        }
    }

TBool CAknKeySoundMap::Find(TSKey& aKey)
    {
    TKeyArrayFix sidKey(_FOFF(TSKey, iKeyCode), ECmpTInt);
    TInt index;
    if (FindIsq(aKey, sidKey, index) == 0)
        {
        aKey.iSid = At(index).iSid;
        return ETrue;
        }
    return EFalse;
    }


// CAknKeySoundStack


CAknKeySoundStack* CAknKeySoundStack::NewL()
    {
    CAknKeySoundStack* self = new(ELeave)CAknKeySoundStack();
    return self;
    }

CAknKeySoundStack::~CAknKeySoundStack()
    {
    ResetAndDestroy();
    }


CAknKeySoundStack::CAknKeySoundStack()
:CArrayPtrFlat<CAknKeySoundMap>(KAknKeySoundMapGranularity)
    {
    }

TBool CAknKeySoundStack::Find(const TKeyEvent& aKeyEvent, TInt& aSid)
    {
    TSKey key;
    // Decide on key-repeat type to check for
    if (aKeyEvent.iRepeats == 0)
        {
        key.Set(aKeyEvent.iCode, ESKeyTypeShort, 0);
        }
    else
        {
        if (iPreviousEvent.iRepeats == 0)
            {
            key.Set(aKeyEvent.iCode, ESKeyTypeLong, 0);
            }
        else
            {
            key.Set(aKeyEvent.iCode, ESKeyTypeRepeat, 0);
            }
        }

    iPreviousEvent = aKeyEvent;

    // Check in top layer
    TInt index = Count();
    while (index)
        {
        index--;
        CAknKeySoundMap* map = At(index);
        if (map->Find(key))
            {
            if (key.iSid == EAvkonSIDNoSound)
                return EFalse;
            else if (key.iSid == EAvkonSIDDefaultSound)
                {
                // Go direct to play default sound
                index = 1;
                continue;
                }
            else
                {
                aSid = key.iSid;
                return ETrue;
                }
            }
        }
    return EFalse;
    }

// End of File
